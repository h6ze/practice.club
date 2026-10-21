#include "stack.hh"

namespace {

#if defined(_M_X64)

    [[nodiscard]] bool step_leaf(CONTEXT& context) noexcept {
        __try {
            const DWORD64 caller = *reinterpret_cast<DWORD64*>(context.Rsp);
            if (!caller) return false;

            context.Rip = caller;
            context.Rsp += sizeof(DWORD64);

            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return false;
        }
    }

    [[nodiscard]] bool step(CONTEXT& context) noexcept {
        __try {
            DWORD64 image_base = 0;
            PRUNTIME_FUNCTION entry = RtlLookupFunctionEntry(context.Rip, &image_base, nullptr);
            if (!entry) return step_leaf(context);

            PVOID handler_data = nullptr;
            DWORD64 establisher = 0;
            RtlVirtualUnwind(UNW_FLAG_NHANDLER, image_base, context.Rip, entry, &context, &handler_data, &establisher, nullptr);

            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return false;
        }
    }

#endif

}

void crash::walk(const CONTEXT& start, frame_list& out) noexcept {
    out.count = 0;

#if defined(_M_X64)
    CONTEXT context = start;

    while (out.count < frame_list::capacity) {
        if (!context.Rip) break;

        out.frames[out.count++] = static_cast<uintptr_t>(context.Rip);

        const DWORD64 previous = context.Rsp;
        if (!step(context)) break;
        if (context.Rsp < previous) break;
    }
#else
    out.frames[out.count++] = static_cast<uintptr_t>(start.Eip);
#endif
}

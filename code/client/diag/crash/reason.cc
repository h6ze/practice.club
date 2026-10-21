#include "reason.hh"

namespace {

    struct code_entry { DWORD code; const char* name; const char* detail; };

    constexpr code_entry codes[] = {
        { EXCEPTION_ACCESS_VIOLATION, "access violation", "touched memory the process does not own" },
        { EXCEPTION_ARRAY_BOUNDS_EXCEEDED, "array bounds exceeded", "indexed past the end of a bounds checked array" },
        { EXCEPTION_BREAKPOINT, "breakpoint", "hit an int3, usually a debug trap left in code" },
        { EXCEPTION_DATATYPE_MISALIGNMENT, "datatype misalignment", "read or wrote through an unaligned pointer" },
        { EXCEPTION_FLT_DENORMAL_OPERAND, "float denormal operand", "an operand was too small to represent" },
        { EXCEPTION_FLT_DIVIDE_BY_ZERO, "float divide by zero", "divided a float by zero" },
        { EXCEPTION_FLT_INEXACT_RESULT, "float inexact result", "the result could not be represented exactly" },
        { EXCEPTION_FLT_INVALID_OPERATION, "float invalid operation", "an unsupported floating point operation" },
        { EXCEPTION_FLT_OVERFLOW, "float overflow", "the exponent exceeded the type" },
        { EXCEPTION_FLT_STACK_CHECK, "float stack check", "the floating point stack was left unbalanced" },
        { EXCEPTION_FLT_UNDERFLOW, "float underflow", "the exponent fell below the type" },
        { EXCEPTION_ILLEGAL_INSTRUCTION, "illegal instruction", "executed an opcode this cpu does not implement" },
        { EXCEPTION_IN_PAGE_ERROR, "in page error", "a page could not be brought into memory" },
        { EXCEPTION_INT_DIVIDE_BY_ZERO, "integer divide by zero", "divided an integer by zero" },
        { EXCEPTION_INT_OVERFLOW, "integer overflow", "the result did not fit the destination" },
        { EXCEPTION_INVALID_DISPOSITION, "invalid disposition", "an exception handler returned a bad disposition" },
        { EXCEPTION_NONCONTINUABLE_EXCEPTION, "noncontinuable exception", "execution resumed after a fatal exception" },
        { EXCEPTION_PRIV_INSTRUCTION, "privileged instruction", "executed a ring zero instruction in user mode" },
        { EXCEPTION_SINGLE_STEP, "single step", "the trap flag was set" },
        { EXCEPTION_STACK_OVERFLOW, "stack overflow", "ran out of stack, usually unbounded recursion" },
        { EXCEPTION_GUARD_PAGE, "guard page violation", "touched a guard page" },
        { EXCEPTION_INVALID_HANDLE, "invalid handle", "passed a closed or bogus handle to the kernel" },
        { 0xE06D7363, "unhandled c++ exception", "a throw left the process with no matching catch" },
        { 0xC0000409, "security check failure", "a stack cookie or control flow guard check failed" },
        { 0xC0000374, "heap corruption", "the heap metadata was overwritten" },
        { 0x80000003, "breakpoint", "hit an int3, usually a debug trap left in code" },
        { 0xE0000001, "terminate called", "std::terminate ran, an uncaught throw or a failed noexcept" },
        { 0xE0000002, "pure virtual call", "a virtual method was called during construction or destruction" },
        { 0xE0000003, "invalid crt parameter", "a crt function rejected its arguments" },
        { 0xE0000004, "abort", "the crt called abort" },
    };

}

crash::reason crash::reason_of(DWORD code) noexcept {
    for (const auto& entry : codes)
        if (entry.code == code) return { entry.name, entry.detail };

    return { "unknown exception", "no description for this status code" };
}

const char* crash::access_kind(ULONG_PTR operation) noexcept {
    if (operation == 0) return "reading";
    if (operation == 1) return "writing";
    if (operation == 8) return "executing";

    return "accessing";
}

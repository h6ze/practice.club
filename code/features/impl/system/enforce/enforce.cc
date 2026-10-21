#include <features/features.hh>
#include <chrono>
#include <features/impl/helpers.hh>

namespace features {

    void enforcement_domain::tick() {
        if (!enforcement_setup.is_enabled) return;

        using clock = std::chrono::steady_clock;

        static clock::time_point last;
        const clock::time_point now = clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count() < tune::enforce_every_ms) return;

        last = now;

        const int wanted = enforcement_setup.level;

        game::dispatch::post([wanted]() {
            sdk::APlayerState* state = detail::own_state();
            if (!state) return;

            const int ceiling = sdk::hw2::max_level_of(state);
            const int level = ceiling > 0 && wanted > ceiling ? ceiling : wanted;

            if (sdk::hw2::level_of(state) != level) sdk::hw2::call_set_level(state, level);
        });
    }

}

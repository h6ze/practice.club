#pragma once
#include <features/features.hh>
#include <sdk/unreal/view/players.hh>

namespace features::detail {

    [[nodiscard]] inline bool is_paintable(const game::player& subject) {
        if (subject.is_local || !subject.is_alive || !subject.frame.is_valid) return false;
        if (visuals_setup.is_enemy_only && !subject.is_enemy) return false;

        return subject.distance <= visuals_setup.max_distance;
    }

    template <class fn> inline void each_subject(fn apply) {
        for (const game::player& subject : game::players::all())
            if (is_paintable(subject)) apply(subject);
    }

}

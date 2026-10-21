#pragma once
#include <string>
#include <vector>
#include <sdk/unreal/engine.hh>

namespace game {

    struct player {
        sdk::APlayerState* player_state = nullptr;
        sdk::APawn* pawn = nullptr;

        std::string name;
        int team = -1;
        int kills = 0;
        int deaths = 0;
        int level = 0;

        double health = 0.0;
        double max_health = 0.0;

        bool is_local = false;
        bool is_alive = false;
        bool is_enemy = false;

        sdk::FVector origin;
        sdk::FVector feet;
        sdk::FVector head;

        float distance = 0.0f;
        sdk::box frame;

        [[nodiscard]] float health_fraction() const noexcept {
            return max_health > 0.0 ? static_cast<float>(health / max_health) : 0.0f;
        }
    };

    namespace players {

        void refresh();

        [[nodiscard]] const std::vector<player>& all();
        [[nodiscard]] const player* local();

    }

}

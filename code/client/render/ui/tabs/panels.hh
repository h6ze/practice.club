#pragma once
#include <features/features.hh>

namespace render::panels {

    void draw_board(features::field_board& board);

    void draw_player_pick(const features::match_snapshot& seen);

    void draw_match_tab();

    void draw_bots_tab();
    void draw_streaks_tab();

    void draw_kit_tab();
    void draw_modes_tab();

    void draw_career_tab();

    void draw_online_tab();
    void draw_media_tab();

    void draw_world_tab();

}

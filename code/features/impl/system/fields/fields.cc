#include <features/features.hh>
#include <features/impl/helpers.hh>

namespace features {

    void fields_domain::tick() {
        if (detail::is_fields_pass_queued.exchange(true)) return;

        game::dispatch::post([]() {
            for (field_board* board : boards::every) {
                if (!detail::is_idle(*board)) detail::sync_board(*board);

                board->is_watched = false;
            }

            detail::is_fields_pass_queued = false;
        });
    }

    void fields_domain::release(field_board& board) {
        for (int i = 0; i < board.count; ++i) board.state[i].is_held = false;
    }

    void fields_domain::release_all() {
        for (field_board* board : boards::every) release(*board);

        logger::success("[ fields ] every hold let go -> the next pass puts the games own nigger back");
    }

}

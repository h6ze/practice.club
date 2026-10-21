#include <features/features.hh>
#include <features/impl/helpers.hh>

namespace features {

    void visuals_domain::boxes() {
        detail::each_subject([](const game::player& subject) { paint::corner_box(subject); });
    }

    void visuals_domain::names() {
        detail::each_subject([](const game::player& subject) { paint::name(subject); });
    }

    void visuals_domain::health() {
        detail::each_subject([](const game::player& subject) { paint::health(subject); });
    }

    void visuals_domain::distance() {
        detail::each_subject([](const game::player& subject) { paint::distance(subject); });
    }

    void visuals_domain::snaplines() {
        detail::each_subject([](const game::player& subject) { paint::snapline(subject); });
    }

    void visuals_domain::head_dots() {
        detail::each_subject([](const game::player& subject) { paint::head_dot(subject); });
    }

}

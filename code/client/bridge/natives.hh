#pragma once
#include <sdk/core/reflect/object.hh>

namespace game::natives {

    using thunk = void (*)(void* context, void* stack, void* result);

    thunk swap(sdk::UFunction* function, thunk replacement);

    void restore_all();

}

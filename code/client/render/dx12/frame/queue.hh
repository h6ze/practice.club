#pragma once
#include <d3d12.h>

namespace render::queue {

    [[nodiscard]] bool ensure(ID3D12Device* device);
    void unhook();

    [[nodiscard]] ID3D12CommandQueue* borrowed();

}

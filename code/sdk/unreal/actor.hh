#pragma once
#include <sdk/core/math.hh>
#include <sdk/core/reflect/object.hh>

namespace sdk {

    struct USceneComponent : UObject {
        [[nodiscard]] FVector RelativeLocation() const noexcept;
        [[nodiscard]] FRotator RelativeRotation() const noexcept;
    };

    struct APawn;

    struct AActor : UObject {
        [[nodiscard]] USceneComponent* RootComponent() const noexcept;
        [[nodiscard]] AActor* Owner() const noexcept;
        [[nodiscard]] APawn* Instigator() const noexcept;

        [[nodiscard]] FVector origin() const noexcept;
    };

}

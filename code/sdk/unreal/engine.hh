#pragma once
#include <sdk/core/container.hh>
#include "actor.hh"

namespace sdk {

    struct UNetDriver : UObject {
        [[nodiscard]] UObject* ServerConnection() const noexcept;
        [[nodiscard]] std::int32_t client_count() const noexcept;
        [[nodiscard]] FName NetDriverName() const noexcept;
    };

    struct AController;
    struct APlayerState;

    struct APawn : AActor {
        [[nodiscard]] APlayerState* PlayerState() const noexcept;
        [[nodiscard]] AController* Controller() const noexcept;
    };

    struct APlayerState : AActor {
        [[nodiscard]] APawn* PawnPrivate() const noexcept;
        [[nodiscard]] std::string PlayerNamePrivate() const;
    };

    struct AController : AActor {
        [[nodiscard]] APawn* Pawn() const noexcept;
        [[nodiscard]] APlayerState* PlayerState() const noexcept;
        [[nodiscard]] FName StateName() const noexcept;
        [[nodiscard]] FRotator ControlRotation() const noexcept;
    };

    struct APlayerController : AController {
        [[nodiscard]] AActor* PlayerCameraManager() const noexcept;
    };

    struct AGameStateBase : AActor {
        [[nodiscard]] TArray<APlayerState*> PlayerArray() const noexcept;
    };

    struct UPlayer : UObject {
        [[nodiscard]] APlayerController* PlayerController() const noexcept;
    };

    struct UGameInstance : UObject {
        [[nodiscard]] UPlayer* local_player(std::int32_t index = 0) const noexcept;
    };

    struct UWorld : UObject {
        [[nodiscard]] UObject* PersistentLevel() const noexcept;
        [[nodiscard]] UNetDriver* NetDriver() const noexcept;
        [[nodiscard]] UObject* DemoNetDriver() const noexcept;
        [[nodiscard]] AGameStateBase* GameState() const noexcept;
        [[nodiscard]] UObject* AuthorityGameMode() const noexcept;
        [[nodiscard]] UGameInstance* OwningGameInstance() const noexcept;

        [[nodiscard]] APlayerController* local_controller() const noexcept;

        [[nodiscard]] TArray<AActor*> level_actors() const noexcept;
    };

}

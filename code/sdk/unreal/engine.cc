#include "engine.hh"
#include <sdk/core/text/encoding.hh>
#include <sdk/core/access.hh>
#include <sdk/offsets.generated.hh>

sdk::UObject* sdk::UNetDriver::ServerConnection() const noexcept {
    return mem::pointer<UObject>(this, offsets::unet_driver::server_connection);
}

std::int32_t sdk::UNetDriver::client_count() const noexcept {
    return mem::read<TArray<void*>>(this, offsets::unet_driver::client_connections, TArray<void*>{}).num();
}

sdk::FName sdk::UNetDriver::NetDriverName() const noexcept {
    return mem::read<FName>(this, offsets::unet_driver::net_driver_name, FName{});
}

sdk::APawn* sdk::APlayerState::PawnPrivate() const noexcept {
    return mem::pointer<APawn>(this, offsets::aplayer_state::pawn_private);
}

std::string sdk::APlayerState::PlayerNamePrivate() const {
    return narrow(mem::read<FString>(this, offsets::aplayer_state::player_name, FString{}));
}

sdk::APlayerState* sdk::APawn::PlayerState() const noexcept {
    return mem::pointer<APlayerState>(this, offsets::apawn::player_state);
}

sdk::AController* sdk::APawn::Controller() const noexcept {
    return mem::pointer<AController>(this, offsets::apawn::controller);
}

sdk::FRotator sdk::AController::ControlRotation() const noexcept {
    return mem::read<FRotator>(this, offsets::acontroller::control_rotation, FRotator{});
}

sdk::APawn* sdk::AController::Pawn() const noexcept {
    return mem::pointer<APawn>(this, offsets::acontroller::pawn);
}

sdk::APlayerState* sdk::AController::PlayerState() const noexcept {
    return mem::pointer<APlayerState>(this, offsets::acontroller::player_state);
}

sdk::FName sdk::AController::StateName() const noexcept {
    return mem::read<FName>(this, offsets::acontroller::state_name, FName{});
}

sdk::AActor* sdk::APlayerController::PlayerCameraManager() const noexcept {
    return mem::pointer<AActor>(this, offsets::aplayer_controller::camera_manager);
}

sdk::TArray<sdk::APlayerState*> sdk::AGameStateBase::PlayerArray() const noexcept {
    return mem::read<TArray<APlayerState*>>(this, offsets::agame_state::player_array, TArray<APlayerState*>{});
}

sdk::APlayerController* sdk::UPlayer::PlayerController() const noexcept {
    return mem::pointer<APlayerController>(this, offsets::uplayer::player_controller);
}

sdk::UPlayer* sdk::UGameInstance::local_player(std::int32_t index) const noexcept {
    const auto players = mem::read<TArray<UPlayer*>>(this, offsets::ugame_instance::local_players, TArray<UPlayer*>{});

    return players.at(index);
}

sdk::UObject* sdk::UWorld::PersistentLevel() const noexcept {
    return mem::pointer<UObject>(this, offsets::uworld::persistent_level);
}

sdk::UNetDriver* sdk::UWorld::NetDriver() const noexcept {
    return mem::pointer<UNetDriver>(this, offsets::uworld::net_driver);
}

sdk::UObject* sdk::UWorld::DemoNetDriver() const noexcept {
    return mem::pointer<UObject>(this, offsets::uworld::demo_net_driver);
}

sdk::AGameStateBase* sdk::UWorld::GameState() const noexcept {
    return mem::pointer<AGameStateBase>(this, offsets::uworld::game_state);
}

sdk::UObject* sdk::UWorld::AuthorityGameMode() const noexcept {
    return mem::pointer<UObject>(this, offsets::uworld::authority_game_mode);
}

sdk::UGameInstance* sdk::UWorld::OwningGameInstance() const noexcept {
    return mem::pointer<UGameInstance>(this, offsets::uworld::owning_game_instance);
}

sdk::TArray<sdk::AActor*> sdk::UWorld::level_actors() const noexcept {
    return mem::read<TArray<AActor*>>(PersistentLevel(), offsets::ulevel::actors, TArray<AActor*>{});
}

sdk::APlayerController* sdk::UWorld::local_controller() const noexcept {
    UGameInstance* instance = OwningGameInstance();
    if (!instance) return nullptr;

    UPlayer* player = instance->local_player();

    return player ? player->PlayerController() : nullptr;
}

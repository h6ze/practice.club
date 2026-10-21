#include "actor.hh"
#include <sdk/core/access.hh>
#include <sdk/offsets.generated.hh>

sdk::FVector sdk::USceneComponent::RelativeLocation() const noexcept {
    return mem::read<FVector>(this, offsets::uscene_component::relative_location, FVector{});
}

sdk::FRotator sdk::USceneComponent::RelativeRotation() const noexcept {
    return mem::read<FRotator>(this, offsets::uscene_component::relative_rotation, FRotator{});
}

sdk::USceneComponent* sdk::AActor::RootComponent() const noexcept {
    return mem::pointer<USceneComponent>(this, offsets::aactor::root_component);
}

sdk::AActor* sdk::AActor::Owner() const noexcept {
    return mem::pointer<AActor>(this, offsets::aactor::owner);
}

sdk::APawn* sdk::AActor::Instigator() const noexcept {
    return mem::pointer<APawn>(this, offsets::aactor::instigator);
}

sdk::FVector sdk::AActor::origin() const noexcept {
    const USceneComponent* root = RootComponent();

    return root ? root->RelativeLocation() : FVector{};
}

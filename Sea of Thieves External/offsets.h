#pragma once
#include <cstdint>

#define OFFSET(name, value) constexpr const uint32_t name = value

namespace offsets
{
	//Global
	OFFSET(GNames, 0x8100bf8);
	OFFSET(GObjects, 0x8105240);
	OFFSET(GWorld, 0x81c8690); //UWorld *

	//UWorld
	OFFSET(PersistentLevel, 0x30); //ULevel *
	OFFSET(OwningGameInstance, 0x1c0); //UGameInstance *

	//ULevel
	OFFSET(Actors, 0xa0); //TArray<AActor *>

	//AActor
	OFFSET(RootComponent, 0x168); //USceneComponent *
	OFFSET(Children, 0x158); //TArray<AActor *>

	//USceneComponent
	OFFSET(RelativeLocation, 0x12c); //FVector

	//UGameInstance
	OFFSET(LocalPlayers, 0x38); //TArray<ULocalPlayer *>

	//UPlayer
	OFFSET(PlayerController, 0x30); //APlayerController *

	//APlayerController
	OFFSET(AcknowledgedPawn, 0x438); //APawn *
	OFFSET(PlayerCameraManager, 0x458); //APlayerCameraManager *

	//APawn
	OFFSET(PlayerState, 0x3e8); //APlayerState *

	//AAthenaCharacter
	OFFSET(HealthComponent, 0x898); //UHealthComponent *

	//UHealthComponent
	OFFSET(MaxHealth, 0xe0); // float
	OFFSET(CurrentHealthInfo, 0xe4); // FCurrentHealthInfo

	//FCurrentHealthInfo
	OFFSET(Health, 0x00); // float

	//APlayerState
	OFFSET(PlayerName, 0x3d0); //FString

	//APlayerCameraManager
	OFFSET(CameraCache, 0x440); //FCameraCacheEntry

	//FCameraCacheEntry
	OFFSET(POV, 0x10); //FMinimalViewInfo

	//FMinimalViewInfo
	OFFSET(Location, 0x0); //FVector
	OFFSET(Rotation, 0xC); //FRotator
	OFFSET(FOV, 0x28); //float
}

#undef OFFSET
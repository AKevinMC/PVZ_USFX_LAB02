// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PVZ_USFX_LAB02GameModeBase.generated.h"

/**
 * 
 */
class AZombie;
class APlant;
UCLASS()
class PVZ_USFX_LAB02_API APVZ_USFX_LAB02GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APVZ_USFX_LAB02GameModeBase();

	FVector SpawnLocationZombie;
	TArray<AZombie*> ArrayZombies;
	AZombie* NuevoZombie;


	TMap<FString, APlant*> MapPlantas;
	APlant* NuevaPlanta;
	FVector SpawnLocationPlant;
	FVector SpawnLocationPlantTemp;

	FTimerHandle Temporizador;

	float TiempoTranscurrido;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void aumentovelocidad();

};

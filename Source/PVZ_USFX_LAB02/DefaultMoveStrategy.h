// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ZombieStrategy.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultMoveStrategy.generated.h"
class AZombie;
class APlant;
UCLASS()
class PVZ_USFX_LAB02_API ADefaultMoveStrategy : public AActor, public IZombieStrategy
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefaultMoveStrategy();

	AZombie* Zombie;
	float TiempoTranscurrido;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Move(AZombie*) override;
};

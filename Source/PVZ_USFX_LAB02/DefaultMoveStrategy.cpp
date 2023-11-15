// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultMoveStrategy.h"
#include "Zombie.h"
// Sets default values
ADefaultMoveStrategy::ADefaultMoveStrategy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADefaultMoveStrategy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultMoveStrategy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADefaultMoveStrategy::Move(AZombie* _zombie, FVector _Objetivo)
{
	Zombie = _zombie;
	 
	//mensaje de log
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("Zombie se mueve de manera default"));
}


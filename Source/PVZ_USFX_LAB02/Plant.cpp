// Fill out your copyright notice in the Description page of Project Settings.


#include "Plant.h"

// Sets default values
APlant::APlant()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshPlanta = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Planta Mesh"));
	RootComponent = MeshPlanta;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PLantaMesh01(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));
	MeshPlanta->SetStaticMesh(PLantaMesh01.Object);

}

// Called when the game starts or when spawned
void APlant::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


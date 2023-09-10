// Fill out your copyright notice in the Description page of Project Settings.


#include "Zombie.h"

// Sets default values
AZombie::AZombie()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshZombie = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Zombie Mesh"));
	RootComponent = MeshZombie;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ZombieMesh01(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_QuadPyramid.Shape_QuadPyramid'"));
	MeshZombie->SetStaticMesh(ZombieMesh01.Object);


	energia = 100;
	Velocidad = 0.02f;

	//InitialLifeSpan = 5; //Para que el actor se destruya

}

// Called when the game starts or when spawned
void AZombie::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector LocalizacionObjetivo = FVector(-550.0f, -850.0f, 20.0f); // Cambia la ubicación objetivo según tus necesidades

	// Calcula la dirección y distancia al objetivo
	FVector Direccion = LocalizacionObjetivo - FVector(-550.0f, 850.0f, 20.0f);

	//FVector Direccion = (LocalizacionObjetivo - this->GetActorLocation()).GetSafeNormal();
	//FVector Direccion = (LocalizacionObjetivo - this->GetActorLocation());

	float DistanciaAlObjetivo = FVector::Dist(LocalizacionObjetivo, this->GetActorLocation());

	// Calcula el desplazamiento en este frame
	float DeltaMove = Velocidad * GetWorld()->DeltaTimeSeconds;

	if (DeltaMove > DistanciaAlObjetivo)
	{
		// Si el desplazamiento excede la distancia al objetivo, mueve directamente al objetivo
		this->SetActorLocation(LocalizacionObjetivo);
	}
	else
	{
		// Mueve el objeto en la dirección calculada
		this->AddActorWorldOffset(Direccion * DeltaMove);
	}

}

void AZombie::morir()
{


	//Destroy();			//El actor se destruye
	//this->Destroy();		//El actor también se destruye
	//SetActorHiddenInGame(true);	//El actor sólo desaparece
}


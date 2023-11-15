// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultMoveStrategy.h"
#include "Zombie.h"
#include <Kismet/GameplayStatics.h>
#include "Plant.h"
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

	TiempoTranscurrido += DeltaTime;

	
}

void ADefaultMoveStrategy::Move(AZombie* _zombie)
{
	Zombie = _zombie;
	TArray<AActor*> Plantas; // array donde se guardan todos los actores de la clase APlant

	// aqui se llena el array con todos los actores de la clase APlant
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlant::StaticClass(), Plantas);

	// recorrer el array Plantas y comparar la posicion x de cada planta con la posicion x del zombie
	for (int32 i = 0; i < Plantas.Num(); i++)
	{
		// comparar la posicion x de la Planta con la del zombie
		if (Plantas[i]->GetActorLocation().X == Zombie->GetActorLocation().X) {
			// si la posicion x de la planta es igual a la del zombie, entonces la planta es el objetivo
			Zombie->LocalizacionObjetivo = Plantas[i]->GetActorLocation();
			// calcula la direccion y distancia al objetivo
			Zombie->Direccion = (Zombie->LocalizacionObjetivo - Zombie->GetActorLocation()).GetSafeNormal();
			// calcula la distancia al objetivo
			Zombie->DistanciaAlObjetivo = FVector::Dist(Zombie->LocalizacionObjetivo, Zombie->GetActorLocation());
			Zombie->TienePlantaAlFrente = true;

			Zombie->AddObserver(Cast<IObserver>(Plantas[i]));		// se agrega la planta al array de observadores
		}

	}
	//mensaje de log
	//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("Zombie se mueve de manera default"));
}


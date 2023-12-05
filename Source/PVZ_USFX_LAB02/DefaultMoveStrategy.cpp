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
	
}


void ADefaultMoveStrategy::Move(AZombie* _zombie)
{
    AZombie* Zombie = _zombie;
    APlant* PlantaCercanaY = nullptr;
    TArray<AActor*> Plantas;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlant::StaticClass(), Plantas);

    float DistanciaMinimaY = MAX_FLT; // Inicializa con un valor muy grande

    for (int32 i = 0; i < Plantas.Num(); i++)
    {
        // comparar la posicion x de la Planta con la del zombie
        if (FMath::IsNearlyEqual(Plantas[i]->GetActorLocation().X, Zombie->GetActorLocation().X, 0.1f))
        {
            float DistanciaEnY = FMath::Abs(Plantas[i]->GetActorLocation().Y - Zombie->GetActorLocation().Y);

            // Compara la distancia en Y para encontrar la planta más cercana en ese eje
            if (DistanciaEnY < DistanciaMinimaY)
            {
                DistanciaMinimaY = DistanciaEnY;
                PlantaCercanaY = Cast<APlant>(Plantas[i]);
            }
            Zombie->AddObserver(Cast<IObserver>(Plantas[i]));  // se agrega la planta al array de observadores
        }
    }

    // Verifica si se encontró alguna planta cercana en Y
    if (PlantaCercanaY != nullptr)
    {
        // Ahora PlantaCercanaY apunta a la planta más cercana en el eje Y
        Zombie->LocalizacionObjetivo = PlantaCercanaY->GetActorLocation();

        // calcula la direccion y distancia al objetivo
        Zombie->Direccion = (Zombie->LocalizacionObjetivo - Zombie->GetActorLocation()).GetSafeNormal();
        Zombie->DistanciaAlObjetivo = FVector::Dist(Zombie->LocalizacionObjetivo, Zombie->GetActorLocation());

        Zombie->TienePlantaAlFrente = true; // Bandera Para que vaya a la casa
    }
    else
    {
        Zombie->TienePlantaAlFrente = false; // Si no se encontró una planta al frente
    }
}
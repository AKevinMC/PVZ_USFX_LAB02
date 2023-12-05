// Fill out your copyright notice in the Description page of Project Settings.


#include "SaltoTigreMoveStrategy.h"
#include "Zombie.h"
#include <Kismet/GameplayStatics.h>
#include "Plant.h"
// Sets default values
ASaltoTigreMoveStrategy::ASaltoTigreMoveStrategy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    TiempoTranscurrido = 0.0f;

}

// Called when the game starts or when spawned
void ASaltoTigreMoveStrategy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASaltoTigreMoveStrategy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    TiempoTranscurrido += DeltaTime;
}

void ASaltoTigreMoveStrategy::Move(AZombie* _zombie)
{
    AZombie* Zombie = _zombie;
    APlant* PlantaCercanaY = nullptr;
    Zombie->Velocidad = 1000.0f;
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
            Zombie->AddObserver(Cast<IObserver>(Plantas[i])); // se agrega la planta al array de observadores
        }
    }

    // Verifica si se encontró alguna planta cercana en Y
    if (PlantaCercanaY != nullptr)
    {
        // calcula la Localizacion y distancia al objetivo si no la tiene
        if (Zombie->Direccion.Z == 0.0f)
        {
            Zombie->LocalizacionObjetivo = PlantaCercanaY->GetActorLocation();
            Zombie->DistanciaAlObjetivo = FVector::Dist(Zombie->LocalizacionObjetivo, Zombie->GetActorLocation());
        }

        // Ahora PlantaCercanaY apunta a la planta más cercana en el eje Y
        Zombie->LocalizacionObjetivo = PlantaCercanaY->GetActorLocation() + FVector(0.0f, 0.0f, Zombie->DistanciaAlObjetivo / 2);

        // calcula la direccion y distancia al objetivo
        Zombie->Direccion = (Zombie->LocalizacionObjetivo - Zombie->GetActorLocation()).GetSafeNormal();
        Zombie->DistanciaAlObjetivo = FVector::Dist(Zombie->LocalizacionObjetivo, Zombie->GetActorLocation());

        Zombie->TienePlantaAlFrente = true; // Bandera Para que vaya a la casa

    }
    else
    {
        // Si no se encontró una planta al frente, restablecer la bandera
        Zombie->TienePlantaAlFrente = false;
    }
}




									//Giro hacia la planta

//void ASaltoTigreMoveStrategy::Move(AZombie* _zombie)
//{
//    AZombie* Zombie = _zombie;
//    Zombie->Velocidad = 1000.0f;
//    TArray<AActor*> Plantas;
//    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlant::StaticClass(), Plantas);
//
//    for (int32 i = 0; i < Plantas.Num(); i++)
//    {
//        // comparar la posicion x de la Planta con la del zombie
//        if (FMath::IsNearlyEqual(Plantas[i]->GetActorLocation().X, Zombie->GetActorLocation().X, 0.1f))
//        {
//            // si la posicion x de la planta es igual a la del zombie, entonces la planta es el objetivo
//            Zombie->LocalizacionObjetivo = Plantas[i]->GetActorLocation();
//
//            // calcula la direccion y distancia al objetivo
//            Zombie->Direccion = (Zombie->LocalizacionObjetivo - Zombie->GetActorLocation()).GetSafeNormal();
//            // calcula la distancia al objetivo
//            Zombie->DistanciaAlObjetivo = FVector::Dist(Zombie->LocalizacionObjetivo, Zombie->GetActorLocation());
//
//            Zombie->TienePlantaAlFrente = true;
//
//            Zombie->AddObserver(Cast<IObserver>(Plantas[i])); // se agrega la planta al array de observadores
//
//            // Realiza el giro hacia la planta
//            FRotator NewRotation = FRotationMatrix::MakeFromX(Zombie->Direccion).Rotator();
//            Zombie->SetActorRotation(FMath::RInterpTo(Zombie->GetActorRotation(), NewRotation, GetWorld()->GetDeltaSeconds(), 2.0f));
//        }
//    }
//}

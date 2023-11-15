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
    Zombie = _zombie;
    Zombie->Velocidad = 1000.0f;
    TArray<AActor*> Plantas;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlant::StaticClass(), Plantas);

    for (int32 i = 0; i < Plantas.Num(); i++)
    {
        // comparar la posicion x de la Planta con la del zombie
        if (FMath::IsNearlyEqual(Plantas[i]->GetActorLocation().X, Zombie->GetActorLocation().X, 0.1f))
        {
            // guardar la ubicacion inicial del zombie y la distancia inicial y no entrar más al if
            if (Zombie->DistanciaInicial == 0.0f)
            {
                Zombie->UbicacionInicial = Zombie->GetActorLocation();
                Zombie->DistanciaInicial = FVector::Dist(Zombie->UbicacionInicial, Plantas[i]->GetActorLocation());
            }

            // si la posicion x de la planta es igual a la del zombie, entonces la planta es el objetivo
            float AlturaSaltoInicial = Zombie->AlturaSalto; // Almacena la altura de salto inicial

            Zombie->LocalizacionObjetivo = Plantas[i]->GetActorLocation() + FVector(0.0f, 0.0f, Zombie->AlturaSalto);
            
            // Calcula la distancia recorrida en el salto
            float DistanciaRecorrida = FVector::Dist(Zombie->UbicacionInicial, Zombie->GetActorLocation());

            // Ajusta la altura del objetivo en función de la velocidad y la proporción recorrida
            
                Zombie->AlturaSalto = FMath::Max(AlturaSaltoInicial * (1.0f - DistanciaRecorrida / Zombie->DistanciaInicial) * Zombie->Velocidad / 200.0f, 0.0f);
            
            // calcula la direccion y distancia al objetivo
            Zombie->Direccion = (Zombie->LocalizacionObjetivo - Zombie->GetActorLocation()).GetSafeNormal();
            // calcula la distancia al objetivo
            Zombie->DistanciaAlObjetivo = FVector::Dist(Zombie->LocalizacionObjetivo, Zombie->GetActorLocation());
            
            Zombie->TienePlantaAlFrente = true;

            Zombie->AddObserver(Cast<IObserver>(Plantas[i])); // se agrega la planta al array de observadores
        }
    }



    //for (int32 i = 0; i < Plantas.Num(); i++)
    //{
    //    // Comparar la posición x de la Planta con la del zombie
    //    if (FMath::IsNearlyEqual(Plantas[i]->GetActorLocation().X, Zombie->GetActorLocation().X, 0.1f))
    //    {
    //        // Si la posición x de la planta es casi igual a la del zombie, entonces la planta es el objetivo
    //        Zombie->LocalizacionObjetivo = Plantas[i]->GetActorLocation();

    //        // Almacena la posición Z inicial de la planta
    //        float PlantaZInicial = Plantas[i]->GetActorLocation().Z;

    //        float JumpHeight = 200.0f; // Altura máxima del salto
    //        float JumpTime = 2.0f;    // Tiempo total del salto
    //        float JumpProgress = FMath::Clamp(Zombie->JumpTimer / JumpTime, 0.0f, 1.0f); // Progreso lineal

    //        // Ajusta la altura del objetivo utilizando un movimiento lineal para simular un salto
    //        Zombie->LocalizacionObjetivo.Z = FMath::Lerp(Zombie->GetActorLocation().Z, PlantaZInicial + JumpHeight, JumpProgress);

    //        

    //        // Calcula la dirección y distancia al objetivo
    //        Zombie->Direccion = (Zombie->LocalizacionObjetivo - Zombie->GetActorLocation()).GetSafeNormal();
    //        // Calcula la distancia al objetivo
    //        Zombie->DistanciaAlObjetivo = FVector::Dist(Zombie->LocalizacionObjetivo, Zombie->GetActorLocation());
    //        Zombie->TienePlantaAlFrente = true;

    //        Zombie->AddObserver(Cast<IObserver>(Plantas[i])); // Se agrega la planta al array de observadores

    //        // Incrementa el temporizador de salto
    //        Zombie->JumpTimer += TiempoTranscurrido;
    //    }
    //}
}


//
//void ASaltoTigreMoveStrategy::Move(AZombie* _zombie)
//{
//    Zombie = _zombie;
//
//    TArray<AActor*> Plantas;
//    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlant::StaticClass(), Plantas);
//
//    for (int32 i = 0; i < Plantas.Num(); i++)
//    {
//        // Comparar la posición x de la Planta con la del zombie
//        if (FMath::IsNearlyEqual(Plantas[i]->GetActorLocation().X, Zombie->GetActorLocation().X, 0.1f))
//        {
//            // Si la posición x de la planta es casi igual a la del zombie, entonces la planta es el objetivo
//            Zombie->LocalizacionObjetivo = Plantas[i]->GetActorLocation();
//
//            // Ajusta la altura del objetivo utilizando una función sinusoidal para simular un salto
//            float JumpHeight = 50.0f; // Altura máxima del salto
//            float JumpTime = 1.0f; // Tiempo total del salto
//            float JumpProgress = FMath::Sin((PI * Zombie->JumpTimer) / JumpTime); // Función sinusoidal para el progreso del salto
//            Zombie->LocalizacionObjetivo.Z += JumpHeight * JumpProgress;
//
//            // Incrementa el temporizador de salto
//            Zombie->JumpTimer += Zombie->TiempoTranscurrido;
//
//            // Calcula la dirección y distancia al objetivo
//            Zombie->Direccion = (Zombie->LocalizacionObjetivo - Zombie->GetActorLocation()).GetSafeNormal();
//            // Calcula la distancia al objetivo
//            Zombie->DistanciaAlObjetivo = FVector::Dist(Zombie->LocalizacionObjetivo, Zombie->GetActorLocation());
//            Zombie->TienePlantaAlFrente = true;
//
//            Zombie->AddObserver(Cast<IObserver>(Plantas[i])); // Se agrega la planta al array de observadores
//        }
//    }

    //TArray<AActor*> Plantas;
    //UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlant::StaticClass(), Plantas);

    //for (int32 i = 0; i < Plantas.Num(); i++)
    //{
    //    // Comparar la posición x de la Planta con la del zombie
    //    if (FMath::IsNearlyEqual(Plantas[i]->GetActorLocation().X, Zombie->GetActorLocation().X, 0.1f))
    //    {
    //        // Si la posición x de la planta es casi igual a la del zombie, entonces la planta es el objetivo
    //        Zombie->LocalizacionObjetivo = Plantas[i]->GetActorLocation();
    //        // Coloca el objetivo ligeramente por encima de la planta para simular un salto
    //        Zombie->LocalizacionObjetivo.Z += 100.0f; // Ajusta la altura según tus necesidades

    //        // Calcula la dirección y distancia al objetivo
    //        Zombie->Direccion = (Zombie->LocalizacionObjetivo - Zombie->GetActorLocation()).GetSafeNormal();
    //        // Calcula la distancia al objetivo
    //        Zombie->DistanciaAlObjetivo = FVector::Dist(Zombie->LocalizacionObjetivo, Zombie->GetActorLocation());
    //        Zombie->TienePlantaAlFrente = true;

    //        Zombie->AddObserver(Cast<IObserver>(Plantas[i])); // Se agrega la planta al array de observadores
    //    }
    //}

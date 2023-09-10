// Copyright Epic Games, Inc. All Rights Reserved.


#include "PVZ_USFX_LAB02GameModeBase.h"
#include "Spawns.h"
#include "Jugador.h"
#include "Zombie.h"
#include "Plant.h"
#include "Sol.h"

APVZ_USFX_LAB02GameModeBase::APVZ_USFX_LAB02GameModeBase()
{
	DefaultPawnClass = AJugador::StaticClass();//Definiendo el Pawn

	SpawnLocationZombie = FVector(-550.0f, 850.0f, 20.0f);

	TiempoTranscurrido = 0.0f;


}

void APVZ_USFX_LAB02GameModeBase::BeginPlay()
{
	UWorld* const World = GetWorld();

	ASpawns* Spawn1 = GetWorld()->SpawnActor<ASpawns>(ASpawns::StaticClass(), SpawnLocationZombie, FRotator::ZeroRotator);


	//Aparición de los soles
	ASol* Sol1 = GetWorld()->SpawnActor<ASol>(ASol::StaticClass(), FVector(-20.0f, -220.0f, 20.0f), FRotator::ZeroRotator);


	// Genera 5 zombies
	for (int i = 0; i < 5; i++) {
		// Define una posición temporal para el zombie en X
		SpawnLocationZombie.X += 200;
		// Aparicion de los zombies


		NuevoZombie = GetWorld()->SpawnActor<AZombie>(AZombie::StaticClass(), SpawnLocationZombie, FRotator::ZeroRotator);

		NuevoZombie->Velocidad = FMath::FRandRange(0.1, 0.2);
		//NuevoZombie->Velocidad = 0.02f;

		ArrayZombies.Add(NuevoZombie);

	}

				//Aumentando la velocidad con el metodo aumentovelocidad cada 1 segundo
	World->GetTimerManager().SetTimer(Temporizador, this, &APVZ_USFX_LAB02GameModeBase::aumentovelocidad, 1, true);



	//Definiendo la posición de las plantas
	SpawnLocationPlant = FVector(-550.0f, -850.0f, 20.0f);
	SpawnLocationPlantTemp = SpawnLocationPlant;

	// Genera 5 plantas
	for (int i = 0; i < 5; i++)
	{
		//Define una posicion temporal para la planta en X
		SpawnLocationPlantTemp.X += 200;
		for (int j = 0; j < 2; j++)
		{

			// Define una posición temporal para la planta en Y
			SpawnLocationPlantTemp.Y += 180;

			// Genera un nombre para la planta
			FString NombrePlanta = FString::Printf(TEXT("Planta%d"), i + 1);

			// Crea una nueva instancia de APlant en el mundo
			NuevaPlanta = GetWorld()->SpawnActor<APlant>(APlant::StaticClass(), SpawnLocationPlantTemp, FRotator::ZeroRotator);

					 //Asigna un valor aleatorio a la energía de la planta
			NuevaPlanta->energia = FMath::FRandRange(0.0, 10.0);

					// Muestra un mensaje en la consola
			//UE_LOG(LogTemp, Warning, TEXT("Energía de %s: %i"), *NombrePlanta, NuevaPlanta->energia);

					// Muestra un mensaje en la pantalla
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Purple, FString::Printf(TEXT("Energía de %s: %i"), *NombrePlanta, NuevaPlanta->energia));

					// Agrega la planta al contenedor de plantas
			MapPlantas.Add(NombrePlanta, NuevaPlanta);

			// Coloca al actor (planta) en una posición diferente
			//NuevaPlanta->SetActorLocation(FVector(i * 100, 0, 0));

		}
		// Define una posición temporal para la planta en Y

		SpawnLocationPlantTemp.Y = SpawnLocationPlant.Y;
	}


}

void APVZ_USFX_LAB02GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//TiempoTranscurrido += DeltaTime;

	//if (TiempoTranscurrido > 2.0f) {
	//	// Iterar sobre el vector de objetos
	//	for (int i = 0; i < ArrayZombies.Num(); i++) {

	//		ArrayZombies[i]->Velocidad = FMath::FRand() * 0.1f;

	//		//vectorZombies[i]->MovementSpeed += i * 1.0f;

	//	}
	//	TiempoTranscurrido = 0.0f;
	//}

}

void APVZ_USFX_LAB02GameModeBase::aumentovelocidad()
{
	for (int i = 0; i < ArrayZombies.Num(); i++)
	{
		ArrayZombies[i]->Velocidad = +FMath::FRandRange(0, 0.2);
	}
}

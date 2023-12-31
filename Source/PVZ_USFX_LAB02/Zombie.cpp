// Fill out your copyright notice in the Description page of Project Settings.


#include "Zombie.h"
#include "PVZ_USFX_LAB02GameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "Plant.h"
#include "Observer.h"
#include "Planta_Ataque.h"
#include "PartidaObservable.h"
#include "ZombieStrategy.h"
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
	Velocidad = 100.00f;
	Fuerza = 10;
	TienePlantaAlFrente = false;
	DistanciaInicial= 0.0f;	
	//InitialLifeSpan = 5; //Para que el actor se destruya

	LocalizacionObjetivo = FVector(-550.0f, -850.0f, 20.0f); // Cambia la ubicaci�n objetivo seg�n tus necesidades

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
	TiempoTranscurrido += DeltaTime;

	Move();
	
	if (!TienePlantaAlFrente) {
		// si la posicion x de la planta no es igual a la del zombie, entonces el objetivo es la casa del jugador
		LocalizacionObjetivo = FVector(this->GetActorLocation().X, -850.0f, 20.0F);
		// calcula la direccion y distancia al objetivo
		Direccion = (LocalizacionObjetivo - this->GetActorLocation()).GetSafeNormal();
		// calcula la distancia al objetivo
		DistanciaAlObjetivo = FVector::Dist(LocalizacionObjetivo, this->GetActorLocation());
	}

	// Mueve el Zombie si puede moverse y no est� oculto
	if (bCanMove && !this->IsHidden()) {

		Notify();	// notifica a los observadores que esta visible y moviendose

	// Calcula el desplazamiento en este frame
	float DeltaMove = Velocidad * GetWorld()->DeltaTimeSeconds;

		if (DeltaMove > DistanciaAlObjetivo)
		{
			// Si el desplazamiento excede la distancia al objetivo, mueve directamente al objetivo
			this->SetActorLocation(LocalizacionObjetivo);
		}
		else
		{
			// Mueve el objeto en la direcci�n calculada
			this->AddActorWorldOffset(Direccion * DeltaMove);

			// cambiar velocidad cada 1 segundo
			if (TiempoTranscurrido >= 1.0f) {
				VelocidadRandom(90, 150);
				TiempoTranscurrido = 0.0f;
			}
		}
	}
	if (energia <= 0) {
		
		morir();
	};
}

void AZombie::Attack()
{
	//ataque de zombie
}

void AZombie::morir()
{
	for (int32 i = 0; i < Observers.Num(); i++)
	{
		//castear a APlanta_Ataque
		APlanta_Ataque* Plant = Cast<APlanta_Ataque>(Observers[i]);
		Plant->bCanFire = false;
	}
	PartidaObservable->RemoveObserver(this);
		Destroy();
	//Destroy();			//El actor se destruye
	//this->Destroy();		//El actor tambi�n se destruye
	//SetActorHiddenInGame(true);	//El actor s�lo se oculta
}

void AZombie::VelocidadRandom(float V1, float V2)
{
		Velocidad = +FMath::FRandRange(V1, V2);
}

void AZombie::AddObserver(IObserver* Observer)
{
	Observers.Add(Observer);
}

void AZombie::RemoveObserver(IObserver* Observer)
{
	Observers.Remove(Observer);
}

void AZombie::Notify()
{
	for (int32 i = Observers.Num() - 1; i >= 0; i--)
	{
		if (Observers[i]) // si el observador existe
		{
			//Observers[i]->Update();
			APlanta_Ataque* Plant = Cast<APlanta_Ataque>(Observers[i]);
			Plant->bCanFire = true;
		}
		else // si el observador no existe, se elimina del array
		{
			Observers.RemoveAt(i);
		}
	}
}

void AZombie::Update()
{
	Cambiar();
}

void AZombie::SetPartidaObservable(APartidaObservable* _partidaObservable)
{
	PartidaObservable = _partidaObservable;
	PartidaObservable->AddObserver(this);
}

void AZombie::Cambiar()
{
		FString Estado = PartidaObservable->GetEstado();

		if (Estado.Equals("Inicio")){
		
	}
		if (Estado.Equals("Ataque")) {
		bCanMove = true;
	}
		if (Estado.Equals("Pausa"))
		{
		bCanMove = false;
	}
		if (Estado.Equals("FinPartida"))
		{

		bCanMove = false;
		//Destroy();
		
		// mueren despues de 2 segundos al terminar la partida
		// luego se cambiar� cuando le den al boton de reiniciar o salir
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AZombie::morir, 2.0f, false);
		}
}

void AZombie::SetStrategy(IZombieStrategy* _strategy)
{
	Strategy = _strategy;
}

void AZombie::Move()
{
	Strategy->Move(this);
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "Cajado.h"
#include "PaperFlipbookComponent.h"
#include "Engine/World.h"
#include "Magia.h"
#include "Runtime/Engine/Public/TimerManager.h"


// Sets default values
ACajado::ACajado()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Flipbook = CreateDefaultSubobject <UPaperFlipbookComponent>(TEXT("Flipbook"));
	Flipbook->SetCollisionProfileName("NoCollision");
	RootComponent = Flipbook;


}

// Called when the game starts or when spawned
void ACajado::BeginPlay()
{
	Super::BeginPlay();

	AmmoAmount = 3;
}

// Called every frame
void ACajado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ACajado::StartFire()
{
	UE_LOG(LogTemp, Warning, TEXT("START FIRE"));
	//DoFire();
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		DoFire();
		GetWorldTimerManager().SetTimer(KeepShotting, this, &ACajado::DoFire, tempo, true);
	}
}

void ACajado::StopFire()
{
	UE_LOG(LogTemp, Warning, TEXT("STOP FIRE"));
	GetWorldTimerManager().ClearTimer(KeepShotting);
}

void ACajado::DoFire()
{
	if (AmmoAmount > 0)
	{
		UWorld* World = GetWorld();
		if (World != nullptr)
		{
			FActorSpawnParameters SpawnParam;
			AMagia* Magia = World->SpawnActor <AMagia>(MagiaBP, RootComponent->GetComponentLocation(), RootComponent->GetComponentRotation(), SpawnParam);
			AmmoAmount--;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("DO FIRE"));
}

void ACajado::SetAmmoAmount(int NewAmount)
{
	AmmoAmount = NewAmount;
}

int ACajado::GetAmmoAmount()
{
	return AmmoAmount;
}


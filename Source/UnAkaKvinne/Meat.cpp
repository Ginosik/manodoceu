// Fill out your copyright notice in the Description page of Project Settings.

#include "Meat.h"
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"
#include "Personagem.h"


// Sets default values
AMeat::AMeat()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>
		(TEXT("CollisionComp"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMeat::OnOverlapBegin);
	RootComponent = CollisionComp;

	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>
		(TEXT("Sprite"));
	Sprite->SetupAttachment(CollisionComp);
}

// Called when the game starts or when spawned
void AMeat::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMeat::OnOverlapBegin(UPrimitiveComponent * OverlappedComp,
		AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (OtherActor != nullptr && OtherActor->IsA(APersonagem::StaticClass()))
	{
		Destroy();
	}

}


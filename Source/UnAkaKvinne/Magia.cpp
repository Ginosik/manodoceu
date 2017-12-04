// Fill out your copyright notice in the Description page of Project Settings.

#include "Magia.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AMagia::AMagia()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->SetCollisionProfileName("BlockAll");
	CollisionComp->OnComponentHit.AddDynamic(this, &AMagia::OnHit);
	RootComponent = CollisionComp;

	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	Flipbook->SetCollisionProfileName("NoCollision");
	Flipbook->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->MaxSpeed = 2000.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 0.01f;

}

// Called when the game starts or when spawned
void AMagia::BeginPlay()
{
	Super::BeginPlay();

	Damage = FMath::RandRange(1, 10);
	
}

// Called every frame
void AMagia::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMagia::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("HIT"));
	Destroy();
}


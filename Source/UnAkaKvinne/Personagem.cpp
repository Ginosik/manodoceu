// Fill out your copyright notice in the Description page of Project Settings.

#include "Personagem.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/ChildActorcomponent.h"
#include "Cajado.h"

APersonagem::APersonagem()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera->OrthoWidth = 2048.0f;
	Camera->SetupAttachment(CameraBoom);

	Cajado = CreateDefaultSubobject <UChildActorComponent>(TEXT("Cajado"));
	Cajado->SetupAttachment(GetSprite());

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void APersonagem::BeginPlay()
{
	Super::BeginPlay();

	if (MagoParado) {
		GetSprite()->SetFlipbook(MagoParado);
	}
}

void APersonagem::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Move", this, &APersonagem::Move);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APersonagem::Jump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APersonagem::StartFire);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APersonagem::StopFire);

	PlayerInputComponent->BindAction("Switch", IE_Pressed, this, &APersonagem::SwitchGun);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &APersonagem::TouchStarted);

	PlayerInputComponent->BindTouch(IE_Released, this, &APersonagem::TouchStopped);
}

void APersonagem::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateFlipbook();
}

void APersonagem::UpdateFlipbook()
{

	if (GetVelocity().X != 0)
	{
		GetSprite()->SetFlipbook(MagoAndando);
		if (GetVelocity().X > 0) 
		{
			GetSprite()->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
		else if (GetVelocity().X < 0)
		{
			GetSprite()->SetWorldRotation(FRotator(0.0f, 180.0f, 0.0f));
		}
	}
	else
	{
		GetSprite()->SetFlipbook(MagoParado);
	}

}

void APersonagem::StartFire()
{
	if (bIsWithGun)
	{
		if (Cajado->GetChildActor()->IsA(ACajado::StaticClass()))
		{
			ACajado* CajadoCast = Cast<ACajado>(Cajado->GetChildActor());
			CajadoCast->StartFire();
		}
	}
}

void APersonagem::StopFire()
{
	if (Cajado != nullptr)
	{
		if (Cajado->GetChildActor()->IsA(ACajado::StaticClass()))
		{
			ACajado* CajadoCast = Cast<ACajado>(Cajado->GetChildActor());
			CajadoCast->StopFire();	
		}
	}
}

void APersonagem::Move(float Value)
{
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void APersonagem::TouchStarted(const ETouchIndex::Type FinderIndex, const FVector Location)
{

	Jump();

}

void APersonagem::TouchStopped(const ETouchIndex::Type FinderIndex, const FVector Location)
{

	StopJumping();

}

void APersonagem::SwitchGun()
{
	if (Cajado != nullptr && Cajado->GetNumChildrenComponents() > 0)
	{
		Cajado->DestroyChildActor();
	}
	else if (Cajado != nullptr && Cajado->GetNumChildrenComponents() == 0)
	{
		Cajado->CreateChildActor();
	}
}





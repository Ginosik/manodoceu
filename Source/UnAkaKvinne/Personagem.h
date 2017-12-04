// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Personagem.generated.h"

/**
 * 
 */
UCLASS()
class UNAKAKVINNE_API APersonagem : public APaperCharacter 
{
	GENERATED_BODY()
	
public:

	APersonagem();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent*
		PlayerInputComponent) override;

	virtual void Tick(float DeltaSeconds) override;

	void UpdateFlipbook();

	void StartFire();

	void StopFire();

private:

	UPROPERTY(EditAnywhere) class USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere) class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere) class UPaperFlipbook* MagoParado;
	UPROPERTY(EditAnywhere) class UPaperFlipbook* MagoAndando;
	UPROPERTY(EditAnywhere) class UChildActorComponent* Cajado;
	
	void Move(float Value);

	void TouchStarted(const ETouchIndex::Type FinderIndex,
		const FVector Location);

	void TouchStopped(const ETouchIndex::Type FinderIndex,
		const FVector Location);

	void SwitchGun();

	bool bIsWithGun = true;
};

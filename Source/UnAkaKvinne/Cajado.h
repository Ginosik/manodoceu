// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cajado.generated.h"

UCLASS()
class UNAKAKVINNE_API ACajado : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACajado();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void StartFire();
	virtual void StopFire();
	virtual void DoFire();
	void SetAmmoAmount(int NewAmount);
	int	GetAmmoAmount();

private:

	UPROPERTY(EditAnywhere) int AmmoAmount;

	UPROPERTY(EditAnywhere) class UPaperFlipbookComponent* Flipbook;

	UPROPERTY(EditAnywhere) TSubclassOf<class AMagia> MagiaBP;

	FTimerHandle KeepShotting;

	float tempo = 1.0f;
	
};

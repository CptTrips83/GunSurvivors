// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "TopDownCharacter.h"


#include "Enemy.generated.h"

UCLASS()
class GUNSURVIVORS_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPaperFlipbookComponent* Flipbook;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ATopDownCharacter* Player;	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsAlive = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool CanFollow = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MovementSpeed = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float StopDistance = 20.0f;
	
	AEnemy();

protected:
	virtual void BeginPlay() override;
	void TryMoveTowardsPlayer(float DeltaTime);
	void UpdateFlipbookRotation();

public:	
	virtual void Tick(float DeltaTime) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GUNSURVIVORS_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	int Score = 0;

	AMyGameMode();

	virtual void BeginPlay() override;

	void SetScore(int NewScore);
	void AddScore(int AddAmount);
};

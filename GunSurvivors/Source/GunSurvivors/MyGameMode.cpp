// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"

AMyGameMode::AMyGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	SetScore(0);
}

void AMyGameMode::SetScore(int NewScore)
{
	Score = (NewScore > 0) ? NewScore : 0;
}

void AMyGameMode::AddScore(int AddAmount)
{
	int NewScore = Score + AddAmount;
	SetScore(NewScore);
}

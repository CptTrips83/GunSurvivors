
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Enemy.h"
#include "MyGameMode.h"
#include "Engine/TimerHandle.h"
#include "TopDownCharacter.h"
#include "Kismet/GameplayStatics.h"

#include "EnemySpawner.generated.h"

UCLASS()
class GUNSURVIVORS_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemy> EnemyActorToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnDistance = 400.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int TotalEnemyCount = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DifficultySpikeInterval = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTimeMinimum = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DecreaseTimeValue = 0.05;
	
	FTimerHandle SpawnTimerHandle;

	ATopDownCharacter* Player;
	AMyGameMode* GameMode;
	
	AEnemySpawner();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	void OnSpawnTimeout();
	void TryIncreaseDifficulty();
	void StartSpawning();
	void StopSpawning();
	void SpawnEnemy();

	void SetupEnemy(AEnemy* Enemy);

	UFUNCTION()
	void OnEnemyDied();
};

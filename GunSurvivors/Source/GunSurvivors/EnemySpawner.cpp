
#include "EnemySpawner.h"

AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	StartSpawning();
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::StartSpawning()
{
	GetWorldTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&AEnemySpawner::OnSpawnTimeout,
		SpawnTime,
		true,
		SpawnTime
		);	
}
void AEnemySpawner::StopSpawning()
{
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
}

void AEnemySpawner::OnSpawnTimeout()
{
	SpawnEnemy();
}

void AEnemySpawner::TryIncreaseDifficulty()
{
	// Increase Difficulty
	TotalEnemyCount += 1;
	// Check if TotalEnemyCount DifficultySpike is reached
	if (TotalEnemyCount % DifficultySpikeInterval != 0) return;
		
	if (SpawnTime <= SpawnTimeMinimum) return;
		
	SpawnTime -= DecreaseTimeValue;

	SpawnTime = (SpawnTime < SpawnTimeMinimum) ? SpawnTimeMinimum : SpawnTime;
	
	StopSpawning();
	StartSpawning();
}

void AEnemySpawner::SpawnEnemy()
{
    // Spawn Enemy

	// Get Random Position from Circle
	FVector2D RandomPosition = FVector2D(FMath::VRand());	

	// Normalize Random Position
	RandomPosition.Normalize();

	// Multiply Random Position By SpawnDistance
	RandomPosition *= SpawnDistance;

	const FVector SpawnLocation = GetActorLocation() + FVector(RandomPosition.X, 0.0f, RandomPosition.Y);
	
	AEnemy *Enemy = GetWorld()->SpawnActor<AEnemy>(
		EnemyActorToSpawn,
		SpawnLocation,
		FRotator::ZeroRotator
		);

	if(!Enemy) return;	
	
	TryIncreaseDifficulty();
}

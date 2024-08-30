
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

void AEnemySpawner::SpawnEnemy()
{
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
	
}

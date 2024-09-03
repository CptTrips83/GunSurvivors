
#include "EnemySpawner.h"

#include "GameFramework/GameMode.h"

AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	Player = Cast<ATopDownCharacter>(
		UGameplayStatics::GetActorOfClass(GetWorld(), ATopDownCharacter::StaticClass())
		);

	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	
	GameMode = Cast<AMyGameMode>(GameModeBase);		
	
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

	SetupEnemy(Enemy);
	
	TryIncreaseDifficulty();
}

void AEnemySpawner::SetupEnemy(AEnemy* Enemy)
{
	if(!Enemy) return;

	Enemy->Player = Player;
	Enemy->CanFollow = true;

	Enemy->EnemyDiedDelegate.AddDynamic(this, &AEnemySpawner::OnEnemyDied);
}

void AEnemySpawner::OnEnemyDied()
{
	int AddScore = 10;
	GameMode->AddScore(10);

	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, FString::Printf(TEXT("Score: %d"), GameMode->Score));
}

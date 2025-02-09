
#include "Enemy.h"

#include "Kismet/GameplayStatics.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	Flipbook->SetupAttachment(GetRootComponent());
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy::TryMoveTowardsPlayer(const float DeltaTime)
{
	if(!IsAlive) return;
	if(!CanFollow) return;
	if(!Player) return;

	const FVector CurrentLocation = GetActorLocation();
	const FVector PlayerLocation = Player->GetActorLocation();

	FVector DirectionToPlayer = PlayerLocation - CurrentLocation;
	const float DistanceToPlayer = DirectionToPlayer.Length();

	if(DistanceToPlayer < StopDistance) return;

	DirectionToPlayer.Normalize();

	const FVector NewLocation = CurrentLocation + (DirectionToPlayer * MovementSpeed * DeltaTime);

	SetActorLocation(NewLocation);
}

void AEnemy::UpdateFlipbookRotation() const
{
	if(!IsAlive) return;
	
	const FVector CurrentLocation = GetActorLocation();
	const FVector PlayerLocation = Player->GetActorLocation();

	float FlipbookXScale = Flipbook->GetComponentScale().X;

	if((PlayerLocation.X - CurrentLocation.X) >= 0.0f)
	{
		FlipbookXScale = 1;
	}
	else if((PlayerLocation.X + PlayerLocation.X) < 0.0f)
	{
		FlipbookXScale = -1;
	}

	Flipbook->SetWorldScale3D(FVector(FlipbookXScale, 1.0f, 1.0f));
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TryMoveTowardsPlayer(DeltaTime);
	UpdateFlipbookRotation();
}

void AEnemy::Die()
{
	if(!IsAlive) return;
	IsAlive = false;
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Flipbook->SetFlipbook(DeadFlipbookAsset);
	Flipbook->SetTranslucentSortPriority(-5);

	EnemyDiedDelegate.Broadcast();

	float DestroyTime = 10.0f;
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AEnemy::OnDestroyTimeout, 1.0f, false, DestroyTime);
}

void AEnemy::OnDestroyTimeout()
{
	Destroy();
}




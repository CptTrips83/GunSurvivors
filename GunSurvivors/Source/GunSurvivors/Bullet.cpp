
#include "Bullet.h"

#include "Enemy.h"

ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(SphereComp);

	BulletSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Bullet"));
	BulletSprite->SetupAttachment(GetRootComponent());

	MovementDirection = FVector2D(1.0f, 0.0f);
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OverlapBegin);
}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TryMoveBullet(DeltaTime);
}

void ABullet::TryMoveBullet(float DeltaTime)
{
	if(!IsLaunched)
	{
		return;
	}
	FVector CurrentLocation = GetActorLocation();
	FVector2D DistanceToMove = MovementDirection * MovementSpeed * DeltaTime;
	FVector NewLocation = CurrentLocation + FVector(DistanceToMove.X, 0.0f, DistanceToMove.Y);

	SetActorLocation(NewLocation);
}



void ABullet::Launch(const FVector2D Direction, const float Speed)
{
	if(IsLaunched) return;

	MovementDirection = Direction;
	MovementSpeed = Speed;
	IsLaunched = true;

	float DeleteTime = 10.0f;
	GetWorldTimerManager().SetTimer(DeleteTimer, this, &ABullet::OnDeleteTimerTimeout, 1.0f, false, DeleteTime);
}

void ABullet::OnDeleteTimerTimeout()
{
	Destroy();
}

void ABullet::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy *Enemy = Cast<AEnemy>(OtherActor);

	if(!Enemy) return;
	if(!Enemy->IsAlive) return;

	DisableBullet();
	Enemy->Die();
}

void ABullet::DisableBullet()
{
	if(IsDisabled) return;

	IsDisabled = true;

	SphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BulletSprite->DestroyComponent();
}


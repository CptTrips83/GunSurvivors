
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

	if(!Player)
	{
	    Player = Cast<ATopDownCharacter>(
	    	UGameplayStatics::GetActorOfClass(GetWorld(), ATopDownCharacter::StaticClass())
	    	);
	}	
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


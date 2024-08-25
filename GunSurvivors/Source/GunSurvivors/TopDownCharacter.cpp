

#include "TopDownCharacter.h"

ATopDownCharacter::ATopDownCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(Capsule);

	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	Flipbook->SetupAttachment(GetRootComponent());
}

void ATopDownCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(const APlayerController *PlayerController = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem *Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
	
}

void ATopDownCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!CanMove)
	{
		return;		
	}
	if(MovementDirection.Length() > 0.0f)
	{
		if(MovementDirection.Length() > 1.0f)
		{
			MovementDirection.Normalize();
		}

		const FVector2D DistanceToMove = MovementDirection * MovementSpeed * DeltaTime;

		const FVector CurrentLocation = GetActorLocation();
		const FVector NewLocation = CurrentLocation + FVector(DistanceToMove.X, 0.0f, DistanceToMove.Y);

		SetActorLocation(NewLocation);
	}
}

void ATopDownCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(
			MoveAction,
			ETriggerEvent::Triggered,
			this,
			&ATopDownCharacter::MoveTriggerd
			);
		EnhancedInputComponent->BindAction(
			MoveAction,
			ETriggerEvent::Canceled,
			this,
			&ATopDownCharacter::MoveCompleted
			);
		EnhancedInputComponent->BindAction(
			MoveAction,
			ETriggerEvent::Completed,
			this,
			&ATopDownCharacter::MoveCompleted
			);
		EnhancedInputComponent->BindAction(
			ShootAction,
			ETriggerEvent::Triggered,
			this,
			&ATopDownCharacter::Shoot
			);
		EnhancedInputComponent->BindAction(
			ShootAction,
			ETriggerEvent::Started,
			this,
			&ATopDownCharacter::Shoot
			);
	}
}

void ATopDownCharacter::MoveTriggerd(const FInputActionValue& Value)
{
	const FVector2d MoveActionValue = Value.Get<FVector2d>();

	if(CanMove)
	{
		MovementDirection = MoveActionValue;
	}
}
void ATopDownCharacter::MoveCompleted(const FInputActionValue& Value)
{
	MovementDirection = FVector2d::ZeroVector;
}

void ATopDownCharacter::Shoot(const FInputActionValue& Value)
{
	
}


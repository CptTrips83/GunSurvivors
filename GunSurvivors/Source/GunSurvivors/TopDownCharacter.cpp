

#include "TopDownCharacter.h"

ATopDownCharacter::ATopDownCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(Capsule);

	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	Flipbook->SetupAttachment(GetRootComponent());

	GunParent = CreateDefaultSubobject<USceneComponent>(TEXT("Gun Parent"));
	GunParent->SetupAttachment(GetRootComponent());

	GunSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Gun Sprite"));
	GunSprite->SetupAttachment(GunParent);

	BulletSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSpawnPosition"));
	BulletSpawnPosition->SetupAttachment(GunSprite);
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

bool ATopDownCharacter::TryMoveCharacter(const float DeltaTime)
{
	const float MoveDirectionLength = MovementDirection.Length();
	
	if(!CanMove || FMath::IsNearlyZero(MoveDirectionLength))
	{
		return false;
	}

	if(MoveDirectionLength > 1.0f)
	{
		MovementDirection.Normalize();
	}

	const FVector2D DistanceToMove = MovementDirection * MovementSpeed * DeltaTime;

	const FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = CurrentLocation + FVector(DistanceToMove.X, 0.0f, DistanceToMove.Y);

	if(!IsInMapBounds(NewLocation.X, NewLocation.Z))
	{
		return false;
	}
	
	SetActorLocation(NewLocation);
	return true;
}

/**
 * Updates the animation of the character based on the movement direction.
 * If the movement direction is non-zero, the flipbook for walking is set as the selected flipbook.
 * If the selected flipbook is null, the method returns.
 * The selected flipbook is set as the flipbook for the character.
 *
 * @see UPaperFlipbookComponent::SetFlipbook()
 */
void ATopDownCharacter::UpdateAnimation()
{
	UPaperFlipbook* SelectedFlipbook = FlipbookIdle;

	if(!MovementDirection.IsZero())
	{
		SelectedFlipbook = FlipbookWalk;
	}

	if(!SelectedFlipbook)
	{
		return;
	}
	Flipbook->SetFlipbook(SelectedFlipbook);
}

void ATopDownCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TryMoveCharacter(DeltaTime);	
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
			&ATopDownCharacter::MoveTriggered
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

/**
 * Updates the character's rotation based on the movement direction.
 * If the movement direction is negative on the X-axis, the character's Flipbook is flipped horizontally.
 * If the movement direction is positive on the X-axis, the character's Flipbook is not flipped.
 */
void ATopDownCharacter::UpdateCharacterRotation() const
{
	const FVector FlipbookScale = Flipbook->GetComponentScale();
	if(MovementDirection.X < 0.0f)
	{
		Flipbook->SetWorldScale3D(FVector(-1.0f, FlipbookScale.Y, FlipbookScale.Y));
	}
	else if(MovementDirection.X > 0.0f)
	{
		Flipbook->SetWorldScale3D(FVector(1.0f, FlipbookScale.Y, FlipbookScale.Y));
	}
}

void ATopDownCharacter::MoveTriggered(const FInputActionValue& Value)
{
	const FVector2d MoveActionValue = Value.Get<FVector2d>();

	if(CanMove)
	{
		MovementDirection = MoveActionValue;
		
		UpdateAnimation();
		UpdateCharacterRotation();
	}
}
void ATopDownCharacter::MoveCompleted(const FInputActionValue& Value)
{
	MovementDirection = FVector2d::ZeroVector;
	UpdateAnimation();
}

void ATopDownCharacter::Shoot(const FInputActionValue& Value)
{
	
}

/**
 * Checks if the given coordinates are within the bounds of the map.
 *
 * @param XPos - The X coordinate to check.
 * @param ZPos - The Z coordinate to check.
 * @return true if the coordinates are within the map bounds, false otherwise.
 */
bool ATopDownCharacter::IsInMapBounds(const float XPos, const float ZPos) const
{
	return ((XPos > HorizontalLimits.X) && (XPos < HorizontalLimits.Y))
		&& ((ZPos > VerticalLimits.X) && (ZPos < VerticalLimits.Y));	
}


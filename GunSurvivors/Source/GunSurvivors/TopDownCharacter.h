// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/SceneComponent.h"
#include "PaperSpriteComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/Controller.h"
#include "Engine/TimerHandle.h"

#include "TopDownCharacter.generated.h"

UCLASS()
class GUNSURVIVORS_API ATopDownCharacter : public APawn
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent* Flipbook;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* GunParent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* GunSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* BulletSpawnPosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputMappingContext *InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction *MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction *ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* FlipbookIdle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* FlipbookWalk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D HorizontalLimits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D VerticalLimits;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed = 100.0f;

	UPROPERTY(BlueprintReadWrite)
	FVector2D MovementDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanMove = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanShoot = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShootCooldownDuration = 0.3f;

	FTimerHandle ShootCooldownTimer;
	
	ATopDownCharacter();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void UpdateCharacterRotation() const;

	void MoveTriggered(const FInputActionValue& Value);
	void MoveCompleted(const FInputActionValue& Value);

	void Shoot(const FInputActionValue& Value);

	bool IsInMapBounds(float XPos, float ZPos) const;

private:

	
	
	APlayerController* PlayerController;

	/**
 * Updates the character's rotation based on the movement direction.
 * If the movement direction is negative on the X-axis, the character's Flipbook is flipped horizontally.
 * If the movement direction is positive on the X-axis, the character's Flipbook is not flipped.
 */
	bool TryMoveCharacter(float DeltaTime);
	/**
 * Updates the animation of the character based on the movement direction.
 * If the movement direction is non-zero, the flipbook for walking is set as the selected flipbook.
 * If the selected flipbook is null, the method returns.
 * The selected flipbook is set as the flipbook for the character.
 *
 * @see UPaperFlipbookComponent::SetFlipbook()
 */
	void UpdateAnimation();

	/**
	 * \brief Updates the rotation of the GunParent component based on the mouse position in the world.
	 *
	 * This function is called in the Tick function of the ATopDownCharacter class to continuously update the rotation of the GunParent component.
	 * The updated rotation is calculated using the player's mouse position in the world.
	 *
	 * \note This function assumes that the PlayerController and GunParent components are valid.
	 * If the PlayerController is not valid, the function will return early without updating the rotation.
	 *
	 * \see ATopDownCharacter::Tick()
	 * \see ATopDownCharacter::PlayerController
	 * \see ATopDownCharacter::GunParent
	 */
	void UpdateGunParentRotation() const;

	void OnShootCooldownTimeout();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"


#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/Controller.h"

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
	float MovementSpeed = 100.0f;

	UPROPERTY(BlueprintReadWrite)
	FVector2D MovementDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanMove = true;
	
	ATopDownCharacter();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void UpdateCharacterRotation() const;

	void MoveTriggered(const FInputActionValue& Value);
	void MoveCompleted(const FInputActionValue& Value);

	void Shoot(const FInputActionValue& Value);

private:
	/**
	 * Tries to move the character based on the given DeltaTime.
	 *
	 * @param DeltaTime The time since the last frame was rendered.
	 * @return True if character has been moved, false otherwise.
	 */
	bool TryMoveCharacter(float DeltaTime);
	/**
	 * Updates the character's animation based on the current movement direction.
	 *
	 * This method is called every frame to update the character's animation based on the current movement direction.
	 * If the character is moving, the animation will be set to the walking flipbook. If the character is not moving, the
	 * animation will be set to the idle flipbook. If no flipbook is set, this method will return without doing anything.
	 *
	 * @see FlipbookIdle
	 * @see FlipbookWalk
	 * @see Flipbook
	 */
	void UpdateAnimation();
};


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "PaperSpriteComponent.h"
#include "Engine/TimerHandle.h"
#include "Bullet.generated.h"

UCLASS()
class GUNSURVIVORS_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UPaperSpriteComponent* BulletSprite;

	UPROPERTY(BlueprintReadWrite)
	FVector2D MovementDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed = 300.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsLaunched = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsDisabled = false;
	
	FTimerHandle DeleteTimer;
	
	ABullet();

	virtual void BeginPlay() override;
	void TryMoveBullet(float DeltaTime);

	virtual void Tick(float DeltaTime) override;

	void Launch(FVector2D Direction, float Speed);

	void OnDeleteTimerTimeout();

	UFUNCTION()
	void OverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
		);

	void DisableBullet();
};

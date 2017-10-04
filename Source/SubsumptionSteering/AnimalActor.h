// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <Runtime/Core/Public/HAL/RunnableThread.h>
#include <Runtime/Core/Public/HAL/Runnable.h>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BehaviorArbiter.h"
#include "AnimalActor.generated.h"

UCLASS()
class SUBSUMPTIONSTEERING_API AAnimalActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnimalActor();
	void InflictDamage(AAnimalActor*);
	bool IsDead() {
		return health <= 0;
	}
	FVector target;
	float maxVelocity = 10.f;
	FVector desiredVelocity;
	float mass = 10.f;
	float maxForce = 10.f;
	float maxSpeed = 3.f;
	float wanderAngle = 0.f;
	float slowingRadius = 300.f;
	FVector velocity;
	FVector position;
	int32 health = 100;
	UPROPERTY(EditAnywhere, Category = State)
	int32 hitPoints = 6;
	FHitResult traceHitResult;
	TArray<FHitResult> sphereHitResult;
	FRunnableThread* traceWorkerThread;
	FRunnableThread* sphereWorkerThread;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type) override;
	void SteeringBehavior();
	void WanderBehavior();
	void BehaviorUpdate();
	FVector Seek(FVector target);

	BehaviorArbiter *behaviorArbiter;
	FTimerHandle behaviorTimer;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

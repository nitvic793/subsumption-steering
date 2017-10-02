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
	FVector target;
	float maxVelocity = 10.f;
	FVector desiredVelocity;
	float mass = 10.f;
	float maxForce = 10.f;
	float maxSpeed = 3.f;
	float wanderAngle = 0.f;
	float slowingRadius = 300.f;
	UPROPERTY(EditAnywhere, Category="State")
	int32 health = 100;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void RunTraceThread();
	void SteeringBehavior();
	void WanderBehavior();
	void BehaviorUpdate();
	FVector Seek(FVector target);
	FVector velocity;
	FVector position;
	BehaviorArbiter *behaviorArbiter;
	FTimerHandle behaviorTimer;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};

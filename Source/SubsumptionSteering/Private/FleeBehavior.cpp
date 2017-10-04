// Fill out your copyright notice in the Description page of Project Settings.

#include "FleeBehavior.h"
#include "Utility.h"
#include <Runtime/Engine/Classes/Engine/World.h>
#include <Runtime/Engine/Classes/Engine/EngineTypes.h>
#include "AnimalActor.h"

FleeBehavior::FleeBehavior(AActor* actr)
	:BehaviorInterface(actr)
{
	priority = 7;
}

FleeBehavior::~FleeBehavior()
{
}

void FleeBehavior::Start(std::function<void(BehaviorInterface*)> callback)
{
	auto animal = (AAnimalActor*)actor;
	AActor *hostile = nullptr;
	bool isAttackerNearby = false;
	for (auto hitResult : animal->sphereHitResult) {
		auto hitActor = hitResult.GetActor();
		if (hitActor == nullptr)continue;
		if (hitActor->IsA<AAnimalActor>()) {
			hostile = hitActor;
			isAttackerNearby = true;
			break;
		}
	}
	if (hostile == nullptr)return;
	auto delta = animal->GetActorLocation() - hostile->GetActorLocation();
	FVector direction;
	float length;
	delta.ToDirectionAndLength(direction, length);

	if (animal->health <= 20 && isAttackerNearby && length < 300.f) {
		callback(this);
	}
}

void FleeBehavior::RunBehavior(float deltaTime)
{
	position = actor->GetActorLocation();
	float angle = position.CosineAngle2D(target);
	auto rotator = FRotationMatrix::MakeFromX(position - target).Rotator();
	actor->SetActorRotation(rotator);
	auto delta = target - position;
	desiredVelocity = delta.GetSafeNormal() * maxVelocity;
	FVector steering = desiredVelocity - velocity;
	steering = -steering;
	steering = steering.GetClampedToMaxSize2D(maxForce);
	steering = steering / mass;
	velocity = Utility::Truncate(velocity + steering, maxSpeed);//.GetClampedToMaxSize2D(maxSpeed);
	position = position + velocity; 
	actor->SetActorLocation(position);
}
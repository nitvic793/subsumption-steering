// Fill out your copyright notice in the Description page of Project Settings.

#include "FleeBehavior.h"
#include "Utility.h"
#include <Runtime/Engine/Classes/Engine/World.h>
#include <Runtime/Engine/Classes/Engine/EngineTypes.h>
#include "AnimalActor.h"

FleeBehavior::FleeBehavior(AActor* actr)
	:BehaviorInterface(actr)
{
	priority = 4;
}

FleeBehavior::~FleeBehavior()
{
}

void FleeBehavior::Start(std::function<void(BehaviorInterface*)> callback)
{
	auto animal = (AAnimalActor*)actor;
	if (animal->health < 20) {
		callback(this);
	}
}

void FleeBehavior::RunBehavior()
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
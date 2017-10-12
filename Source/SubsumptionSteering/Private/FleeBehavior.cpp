// Fill out your copyright notice in the Description page of Project Settings.

#include "FleeBehavior.h"
#include "Utility.h"
#include <Runtime/Engine/Classes/Engine/World.h>
#include <Runtime/Engine/Classes/Engine/EngineTypes.h>
#include "AnimalActor.h"
#include "FoodItemActor.h"

FleeBehavior::FleeBehavior(AActor* actr)
	:BehaviorInterface(actr)
{
	priority = 7;
	maxVelocity = 15.f;
}

FleeBehavior::~FleeBehavior()
{
}

void FleeBehavior::Start(std::function<void(BehaviorInterface*)> callback)
{
	auto animal = (AAnimalActor*)actor;
	AActor *hostile = nullptr;
	AActor *food = nullptr;
	bool isAttackerNearby = false;
	for (auto hitResult : animal->sphereHitResult) {
		auto hitActor = hitResult.GetActor();
		if (hitActor == nullptr)continue;
		if (hitActor->IsA<AAnimalActor>()) {
			hostile = hitActor;
			isAttackerNearby = true;
			break;
		}
		else if (hitActor->IsA<AFoodItemActor>()) {
			float distance = Utility::GetDistanceBetweenActors(actor, hitActor);
			if (food == nullptr)
			{
				food = hitActor;
			}
			else
			{
				float currentDistance = Utility::GetDistanceBetweenActors(actor, food);
				if (distance < currentDistance) {
					food = hitActor;
				}
			}
		}
	}
	if (hostile == nullptr || food == nullptr)return;
	auto delta = animal->GetActorLocation() - hostile->GetActorLocation();
	FVector direction;
	float length;
	delta.ToDirectionAndLength(direction, length);

	if (animal->health <= 20 && length < 1000.f && Utility::GetDistanceBetweenActors(actor, food) < 300.f) {
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
	position.Z = 80.f;
	actor->SetActorLocation(position);
}
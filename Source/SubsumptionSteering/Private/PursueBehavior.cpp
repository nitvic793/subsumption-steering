// Fill out your copyright notice in the Description page of Project Settings.

#include "PursueBehavior.h"
#include "Utility.h"
#include "AnimalActor.h"
#include "FoodItemActor.h"

PursueBehavior::PursueBehavior(AActor* actr)
	:BehaviorInterface(actr)
{
	priority = 5;
}

PursueBehavior::~PursueBehavior()
{
}

void PursueBehavior::Start(std::function<void(BehaviorInterface*)> callback)
{
	bool foundActor = false;
	bool foundFood = false;
	auto animal = (AAnimalActor*)actor;
	AActor* hostile = nullptr;
	AActor* food = nullptr;
	for (auto hitResult : animal->sphereHitResult) {
		auto hitActor = hitResult.GetActor();
		if (hitActor == nullptr)continue;
		if (hitActor->IsA<AAnimalActor>()) {
			foundActor = true;
			auto targetAnimal = (AAnimalActor*)hitActor;
			target = hitActor->GetActorLocation();
			targetVelocity = targetAnimal->velocity;
			hostile = hitActor;
		}
		else if (hitActor->IsA<AFoodItemActor>()) {
			foundFood = true; 
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

	if (foundActor && foundFood && animal->health >= 70) {
		if (Utility::GetDistanceBetweenActors(actor, hostile) < 600.f && Utility::GetDistanceBetweenActors(actor, food) < 600.f)
		{
			callback(this);
		}
	}

}

void PursueBehavior::RunBehavior(float deltaTime)
{
	const int TIME = 3;
	position = actor->GetActorLocation();
	auto futurePosition = target + targetVelocity * TIME;
	target = futurePosition;

	float angle = position.CosineAngle2D(target);
	auto rotator = FRotationMatrix::MakeFromX(target - position).Rotator();
	actor->SetActorRotation(rotator);
	auto delta = target - position;
	float distance = Utility::Length(delta);
	desiredVelocity = delta.GetSafeNormal() * maxVelocity;

	FVector steering = desiredVelocity - velocity;
	steering = steering.GetClampedToMaxSize2D(maxForce);
	steering = steering / mass;
	velocity = Utility::Truncate(velocity + steering, maxSpeed);//.GetClampedToMaxSize2D(maxSpeed);
	position = position + velocity;
	actor->SetActorLocation(position);
	SyncInfo();
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackBehavior.h"
#include "AnimalActor.h"
#include "FoodItemActor.h"
#include "Utility.h"

AttackBehavior::AttackBehavior(AActor* actr)
	:BehaviorInterface(actr)
{
	priority = 6;
}

AttackBehavior::~AttackBehavior()
{
}

void AttackBehavior::Start(std::function<void(BehaviorInterface*)> callback)
{
	auto animal = (AAnimalActor*)actor;
	AActor* food = nullptr;
	targetAnimal = nullptr;
	bool isAttackerNearby = false;
	for (auto hitResult : animal->sphereHitResult) {
		auto hitActor = hitResult.GetActor();
		if (hitActor == nullptr)continue;
		if (hitActor->IsA<AAnimalActor>()) {
			isAttackerNearby = true;
			targetAnimal = hitActor;
		}
		if (hitActor->IsA<AFoodItemActor>()) {
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

	if (targetAnimal == nullptr || food == nullptr)return;
	position = actor->GetActorLocation();
	auto delta = position - targetAnimal->GetActorLocation();
	FVector direction;
	float length;
	delta.ToDirectionAndLength(direction, length);
	float foodDistance = Utility::GetDistanceBetweenActors(actor, food);
	if (animal->health > 20 && isAttackerNearby && length < 120.f && foodDistance < 600.f) {
		callback(this);
	}
	//callback(this);
}

void AttackBehavior::RunBehavior(float deltaTime)
{
	if (targetAnimal == nullptr)return;
	auto animal = (AAnimalActor*)actor;
	if (currentTime > 0.6f) {
		currentTime = 0.f;
		animal->InflictDamage((AAnimalActor*)targetAnimal);
	}
	else {
		currentTime += deltaTime;
	}
}
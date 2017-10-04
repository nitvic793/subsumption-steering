// Fill out your copyright notice in the Description page of Project Settings.

#include "EatBehavior.h"
#include "AnimalActor.h"
#include "FoodItemActor.h"

EatBehavior::EatBehavior(AActor* actr)
	:BehaviorInterface(actr)
{
	priority = 4;
}

EatBehavior::~EatBehavior()
{
}

void EatBehavior::Start(std::function<void(BehaviorInterface*)> callback)
{
	auto animal = (AAnimalActor*)actor;
	AFoodItemActor *food = nullptr;
	for (auto hitResult : animal->sphereHitResult) {
		auto hitActor = hitResult.GetActor();
		if (hitActor == nullptr)continue;
		if (hitActor->IsA<AFoodItemActor>()) {
			food = (AFoodItemActor*)hitActor;
			break;
		}
	}
	if (food == nullptr)return;

	float length = 0;
	auto foodLocation = food->GetActorLocation();
	position = actor->GetActorLocation();
	auto delta = position - foodLocation;
	FVector direction;
	delta.ToDirectionAndLength(direction, length);
	if (length < 100)
		callback(this);
}

void EatBehavior::RunBehavior()
{

}
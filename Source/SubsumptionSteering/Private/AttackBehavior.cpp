// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackBehavior.h"
#include "AnimalActor.h"

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
	AAnimalActor* targetAnimal = nullptr;
	bool isAttackerNearby = false;
	for (auto hitResult : animal->sphereHitResult) {
		auto hitActor = hitResult.GetActor();
		if (hitActor == nullptr)continue;
		if (hitActor->IsA<AAnimalActor>()) {
			isAttackerNearby = true;
			targetAnimal = (AAnimalActor*)hitActor;
			break;
		}
	}
	if (targetAnimal == nullptr)return;
	position = actor->GetActorLocation();
	auto delta = position - targetAnimal->GetActorLocation();
	FVector direction;
	float length;
	delta.ToDirectionAndLength(direction, length);
	if (animal->health > 20 && isAttackerNearby && length < 120) {
		callback(this);
	}
	//callback(this);
}

void AttackBehavior::RunBehavior()
{

}
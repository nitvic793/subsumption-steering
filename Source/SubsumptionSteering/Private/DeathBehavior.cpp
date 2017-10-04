// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathBehavior.h"
#include "AnimalActor.h"

DeathBehavior::DeathBehavior(AActor* actr)
	:BehaviorInterface(actr)
{
	priority = 99;
}

DeathBehavior::~DeathBehavior()
{
}

void DeathBehavior::Start(std::function<void(BehaviorInterface*)> callback) 
{
	auto animal = (AAnimalActor*)actor;
	if (animal->IsDead()) {
		callback(this);
	}
}

void DeathBehavior::RunBehavior(float deltaTime) {
	auto animal = (AAnimalActor*)actor;
	animal->Destroy();
	//Do nothing when dead
}
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
	if (animal->health <= 0) {
		callback(this);
	}
}

void DeathBehavior::RunBehavior() {
	//Do nothing when dead
}
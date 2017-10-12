// Fill out your copyright notice in the Description page of Project Settings.

#include "EvadeBehavior.h"
#include "AnimalActor.h"
#include "WallActor.h"
#include "Utility.h"
#include <Runtime/Engine/Classes/Engine/StaticMeshActor.h>
#include <Runtime/Engine/Classes/Engine/World.h>
#include <Runtime/Engine/Classes/Engine/EngineTypes.h>
#include "EngineUtils.h"

EvadeBehavior::EvadeBehavior(AActor* actr)
	:BehaviorInterface(actr)
{
	priority = 9;
	floor = nullptr;
}

EvadeBehavior::~EvadeBehavior()
{
}

void EvadeBehavior::Start(std::function<void(BehaviorInterface*)> callback)
{
	FVector location = actor->GetActorLocation();
	if (location.X < -1360.f || location.X > 5700.f || location.Y > 6420.f || location.Y < -1210.f) {
		callback(this);
	}
}

void EvadeBehavior::RunBehavior(float deltaTime)
{
	//Respwan somewhere within bounds
	FVector loc(900.f, 900.f, 80.f);
	actor->SetActorLocation(loc);
}
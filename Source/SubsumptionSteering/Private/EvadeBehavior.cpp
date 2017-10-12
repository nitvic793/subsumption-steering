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
	for (TActorIterator<AStaticMeshActor> ActorItr(actor->GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		AStaticMeshActor *Mesh = *ActorItr;
		if (Mesh->GetName() == "Floor") {
			Mesh->ActorHasTag(FName(TEXT("test")));
			floor = Mesh;
		}
	}
	FVector origin, box;
	floor->GetActorBounds(false, origin, box);
	auto location = floor->GetActorLocation();
	UE_LOG(LogTemp, Log, TEXT("Bound %f %f %f %f %f %f"), origin.X, origin.Y, box.X, box.Y, location.X, location.Y);
}

void EvadeBehavior::RunBehavior(float deltaTime)
{

}
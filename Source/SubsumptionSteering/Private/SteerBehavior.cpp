// Fill out your copyright notice in the Description page of Project Settings.

#include "SteerBehavior.h"
#include "Utility.h"
#include <Runtime/Engine/Classes/Engine/World.h>
#include <Runtime/Engine/Classes/Engine/EngineTypes.h>

SteerBehavior::SteerBehavior(AActor* actor)
	:BehaviorInterface(actor)
{
	priority = 1;
	velocity = FVector(5, 0, 0);
	target = FVector(600, 600, 80);
}

SteerBehavior::~SteerBehavior()
{
}

void SteerBehavior::Start(std::function<void(BehaviorInterface*)> callback)
{
	if (HasTarget(target)) {
		callback(this);
	}
}

bool SteerBehavior::HasTarget(FVector& OutVector)
{
	UWorld* world = actor->GetWorld();
	const FName TraceTag("SphereTrace");
	world->DebugDrawTraceTag = TraceTag;
	FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, actor);
	TraceParams.bTraceComplex = false;
	TraceParams.TraceTag = TraceTag;
	//TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = false;
	float maxDistance = 1000.f;
	//Ignore Actors
	TraceParams.AddIgnoredActor(actor);
	FVector start = this->actor->GetActorLocation();
	FVector end = actor->GetActorRotation().Vector() * maxDistance;
	float sphereRadius = 800.f;
	FCollisionObjectQueryParams ObjectTraceParams;
	ObjectTraceParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	//Re-initialize hit info
	auto HitOut = FHitResult(ForceInit);
	world->LineTraceSingleByObjectType(
		HitOut,
		start,
		end,
		ObjectTraceParams,
		TraceParams
	);
	/*world->SweepSingleByObjectType(
	HitOut,
	start,
	end,
	FQuat(),
	ECollisionChannel::ECC_WorldDynamic,
	FCollisionShape::MakeSphere(sphereRadius),
	TraceParams
	);*/
	auto otherActor = HitOut.GetActor();
	if (otherActor != nullptr) {
		OutVector = HitOut.GetActor()->GetActorLocation();
		return true;
	}
	return false;
}

void SteerBehavior::RunBehavior()
{
	position = actor->GetActorLocation();
	float angle = position.CosineAngle2D(target);
	auto rotator = FRotationMatrix::MakeFromX(target - position).Rotator();
	actor->SetActorRotation(rotator);
	auto delta = target - position;
	float distance = Utility::Length(delta);
	if (distance < slowingRadius)
	{
		desiredVelocity = delta.GetSafeNormal() * maxVelocity * (distance / slowingRadius);
	}
	else
	{
		desiredVelocity = delta.GetSafeNormal() * maxVelocity;
	}
	FVector steering = desiredVelocity - velocity;
	steering = steering.GetClampedToMaxSize2D(maxForce);
	steering = steering / mass;
	velocity = Utility::Truncate(velocity + steering, maxSpeed);//.GetClampedToMaxSize2D(maxSpeed);
	position = position + velocity;
	actor->SetActorLocation(position);
}

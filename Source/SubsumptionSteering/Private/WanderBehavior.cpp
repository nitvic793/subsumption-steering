// Fill out your copyright notice in the Description page of Project Settings.

#include "WanderBehavior.h"
#include "AnimalActor.h"

const float Length(const FVector& v)
{
	float l;
	FVector f;
	v.ToDirectionAndLength(f, l);
	return l;
}

void SetAngle(FVector& v, float angle)
{
	float l = Length(v);
	v.X = FMath::Cos(angle) * l;
	v.Y = FMath::Sin(angle) * l;
}

FVector Truncate(FVector vector, float max)
{
	float length;
	FVector f;
	vector.ToDirectionAndLength(f, length);
	float i = max / length;
	i = (i < 1.f) ? i : 1.0;
	vector = vector * i;
	return vector;
}

WanderBehavior::WanderBehavior(AActor* actor)
	:BehaviorInterface(actor)
{
	priority = 2;
	velocity = FVector(5, 0, 0);
	target = FVector(600, 600, 80);
}

WanderBehavior::~WanderBehavior()
{
}

void WanderBehavior::Start(std::function<void(BehaviorInterface*)> callback)
{
	callback(this);
}


void WanderBehavior::RunBehavior(float deltaTime)
{
	const float CIRCLE_DISTANCE = 50.f;
	const float CIRCLE_RADIUS = 5.f;
	const float ANGLE_CHANGE = 2.f;
    position = actor->GetActorLocation();
	FVector circleCenter = velocity;
	circleCenter.Normalize();
	circleCenter = circleCenter * CIRCLE_DISTANCE;
	FVector displacement(0, -1, 0);
	displacement = displacement * CIRCLE_RADIUS;
	SetAngle(displacement, wanderAngle);
	wanderAngle += (FMath::RandRange(0.f, 1.f) * ANGLE_CHANGE) - (ANGLE_CHANGE * 0.5f);
	FVector wanderForce = circleCenter + displacement;

	FVector steering = wanderForce;
	steering = steering.GetClampedToMaxSize2D(maxForce);
	steering = steering / mass;
	velocity = Truncate(velocity + steering, maxSpeed);//.GetClampedToMaxSize2D(maxSpeed);
	position = position + velocity;

	float angle = actor->GetActorLocation().CosineAngle2D(position);
	auto rotator = FRotationMatrix::MakeFromX(position - actor->GetActorLocation()).Rotator();
	actor->SetActorLocation(position);
	actor->SetActorRotation(rotator);
	SyncInfo();
}




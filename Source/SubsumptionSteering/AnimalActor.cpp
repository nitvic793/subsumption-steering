// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimalActor.h"
#include <Runtime/Engine/Classes/Engine/World.h>
#include <Runtime/Engine/Public/TimerManager.h>



// Sets default values
AAnimalActor::AAnimalActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	target = FVector(600, 600, 80);
	velocity = FVector(5, 0, 0);
	behaviorArbiter = new BehaviorArbiter(this);
}

// Called when the game starts or when spawned
void AAnimalActor::BeginPlay()
{
	Super::BeginPlay();
	behaviorArbiter->StartBehavior();
	GetWorld()->GetTimerManager().SetTimer(behaviorTimer, this, &AAnimalActor::BehaviorUpdate, 0.5f, true, 1.f);
}

void AAnimalActor::BehaviorUpdate() 
{
	behaviorArbiter->UpdateBehavior();
}

//FVector Truncate(FVector vector, float max)
//{
//	float length;
//	FVector f;
//	vector.ToDirectionAndLength(f, length);
//	float i = max / length;
//	i = (i < 1.f) ? i : 1.0;
//	vector = vector * i;
//	return vector;
//}
//
//const float Length(const FVector& v)
//{
//	float l;
//	FVector f;
//	v.ToDirectionAndLength(f, l);
//	return l;
//}
//
//void SetAngle(FVector& v, float angle)
//{
//	float l = Length(v);
//	v.X = FMath::Cos(angle) * l;
//	v.Y = FMath::Sin(angle) * l;
//}

void AAnimalActor::SteeringBehavior()
{
	//position = GetActorLocation();
	//float angle = position.CosineAngle2D(target);
	//auto rotator = FRotationMatrix::MakeFromX(target - position).Rotator();
	//SetActorRotation(rotator);
	//auto delta = target - position;
	//float distance = Length(delta);
	//if (distance < slowingRadius)
	//{
	//	desiredVelocity = delta.GetSafeNormal() * maxVelocity * (distance / slowingRadius);
	//}
	//else
	//{
	//	desiredVelocity = delta.GetSafeNormal() * maxVelocity;
	//}
	//FVector steering = desiredVelocity - velocity;
	//steering = steering.GetClampedToMaxSize2D(maxForce);
	//steering = steering / mass;
	//velocity = Truncate(velocity + steering, maxSpeed);//.GetClampedToMaxSize2D(maxSpeed);
	//position = position + velocity;
	//SetActorLocation(position);
}



void AAnimalActor::WanderBehavior()
{
	//const float CIRCLE_DISTANCE = 20.f;
	//const float CIRCLE_RADIUS = 10.f;
	//const float ANGLE_CHANGE = 2.f;
	//position = GetActorLocation();
	//FVector circleCenter = velocity;
	//circleCenter.Normalize();
	//circleCenter = circleCenter * CIRCLE_DISTANCE;
	//FVector displacement(0, -1, 0);
	//displacement = displacement * CIRCLE_RADIUS; 
	//SetAngle(displacement, wanderAngle);
	//wanderAngle += (FMath::RandRange(0.f, 1.f) * ANGLE_CHANGE) - (ANGLE_CHANGE * 0.5f);
	//FVector wanderForce = circleCenter + displacement;

	//FVector steering = wanderForce;
	//steering = steering.GetClampedToMaxSize2D(maxForce);
	//steering = steering / mass;
	//velocity = Truncate(velocity + steering, maxSpeed);//.GetClampedToMaxSize2D(maxSpeed);
	//position = position + velocity;

	//float angle = GetActorLocation().CosineAngle2D(position);
	//auto rotator = FRotationMatrix::MakeFromX(position - GetActorLocation()).Rotator();
	//SetActorLocation(position);
	//SetActorRotation(rotator);	
}


FVector AAnimalActor::Seek(FVector target)
{
	return FVector();
}

// Called every frame
void AAnimalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//SteeringBehavior();
	WanderBehavior();
	//Add Timer code here to update behavior 
	behaviorArbiter->RunBehavior();
}

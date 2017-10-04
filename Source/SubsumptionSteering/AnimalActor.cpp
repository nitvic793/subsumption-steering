// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimalActor.h"
#include <Runtime/Engine/Classes/Engine/World.h>
#include <Runtime/Engine/Public/TimerManager.h>

class LineTraceWorker : public FRunnable
{
public:
	LineTraceWorker(AAnimalActor* actr) :
		actor(actr)
	{
	}
	uint32 Run()
	{
		UWorld* world = actor->GetWorld();
		const FName TraceTag("LineTrace");
		world->DebugDrawTraceTag = TraceTag;
		FCollisionQueryParams TraceParams(FName(TEXT("LineTrace")), true, actor);
		TraceParams.bTraceComplex = false;
		TraceParams.TraceTag = TraceTag;
		//TraceParams.bTraceAsyncScene = true;
		TraceParams.bReturnPhysicalMaterial = false;
		float maxDistance = 1000.f;
		//Ignore Actors
		TraceParams.AddIgnoredActor(actor);
		float sphereRadius = 800.f;
		FCollisionObjectQueryParams ObjectTraceParams;
		ObjectTraceParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		//Re-initialize hit info
		auto HitOut = FHitResult(ForceInit);
		while (true) {
			if (shouldStop)
				return 0;
			mMutex.Lock();
			FVector start = this->actor->GetActorLocation();
			FVector end = start + (actor->GetActorRotation().Vector() * maxDistance) + FVector(0, 0, 80.f);
			bool didTrace = world->LineTraceSingleByObjectType(
				HitOut,
				start,
				end,
				ObjectTraceParams,
				TraceParams
			);
			actor->traceHitResult = HitOut;
			mMutex.Unlock();
		}

		auto otherActor = HitOut.GetActor();
		return 0;
	}

	void Stop() {
		shouldStop = true;
		FRunnable::Stop();
	}
protected:
	bool shouldStop = false;
	FCriticalSection mMutex;
	AAnimalActor* actor;
};

class SphereCollisionWorker : public FRunnable
{
public:
	SphereCollisionWorker(AAnimalActor* actr) :
		actor(actr)
	{
	}
	uint32 Run()
	{
		UWorld* world = actor->GetWorld();
		const FName TraceTag("LineTrace");
		world->DebugDrawTraceTag = TraceTag;
		FCollisionQueryParams TraceParams(FName(TEXT("LineTrace")), true, actor);
		TraceParams.bTraceComplex = false;
		TraceParams.TraceTag = TraceTag;
		//TraceParams.bTraceAsyncScene = true;
		TraceParams.bReturnPhysicalMaterial = false;
		float maxDistance = 1000.f;
		//Ignore Actors
		TraceParams.AddIgnoredActor(actor);
		float sphereRadius = 400.f;
		FCollisionObjectQueryParams ObjectTraceParams;
		
		ObjectTraceParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		//Re-initialize hit info
		auto HitOuts = TArray<FHitResult>();
		while (true) {
			if (shouldStop)
				return 0;
			mMutex.Lock();
			FVector start = this->actor->GetActorLocation();
			FVector end = actor->GetActorRotation().Vector() * maxDistance;
			bool didSweep = world->SweepMultiByObjectType(
				HitOuts,
				start,
				end,
				FQuat(),
				ECollisionChannel::ECC_WorldDynamic,
				FCollisionShape::MakeSphere(sphereRadius),
				TraceParams
			);
			actor->sphereHitResult = HitOuts;
			mMutex.Unlock();
		}

		return 0;
	}

	void Stop() {
		shouldStop = true;
		FRunnable::Stop();
	}
protected:
	bool shouldStop = false;
	FCriticalSection mMutex;
	AAnimalActor* actor;
};

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
	traceWorkerThread = FRunnableThread::Create(new LineTraceWorker(this), TEXT("LineTraceThread"));
	sphereWorkerThread = FRunnableThread::Create(new SphereCollisionWorker(this), TEXT("SphereCollisionThread"));
	Super::BeginPlay();
	behaviorArbiter->StartBehavior();
	//Update behavior every 0.1 seconds
	GetWorld()->GetTimerManager().SetTimer(behaviorTimer, this, &AAnimalActor::BehaviorUpdate, 0.05f, true);
}

void AAnimalActor::EndPlay(EEndPlayReason::Type reason) {
	traceWorkerThread->Kill();
	sphereWorkerThread->Kill();
	Super::EndPlay(reason);
}

void AAnimalActor::BehaviorUpdate()
{
	behaviorArbiter->UpdateBehavior();
}

void AAnimalActor::InflictDamage(AAnimalActor* targetAnimal)
{
	targetAnimal->health = targetAnimal->health - this->hitPoints;
}


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
	//WanderBehavior();
	behaviorArbiter->RunBehavior();
}


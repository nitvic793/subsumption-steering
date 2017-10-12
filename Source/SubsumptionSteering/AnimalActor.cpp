// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimalActor.h"
#include <Runtime/Engine/Classes/Engine/World.h>
#include <Runtime/Engine/Public/TimerManager.h>

/*
Line trace thread
*/
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

/*
Sphere collision check thread
*/
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
		float maxDistance = 1200.f;
		//Ignore Actors
		TraceParams.AddIgnoredActor(actor);
		float sphereRadius = 1200.f;
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
			HitOuts.Empty();
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

// Called every frame
void AAnimalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	behaviorArbiter->RunBehavior(DeltaTime); //Let behavior arbiter run the required behavior for the actor.
}


// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorArbiter.h"
#include "SteerBehavior.h"
#include "WanderBehavior.h"

BehaviorArbiter::BehaviorArbiter(AActor *actr)
	:actor(actr)
{
	currentBehavior = nullptr;
	AddBehaviorLevel(STEER, new SteerBehavior(actr));
	AddBehaviorLevel(WANDER, new WanderBehavior(actr));
}

BehaviorArbiter::~BehaviorArbiter()
{
}

void BehaviorArbiter::AddBehaviorLevel(BehaviorEnum name, BehaviorInterface* behavior) {
	behaviorMap.Add(name, behavior);
}
void BehaviorArbiter::StartBehavior() 
{
	for (auto i : behaviorMap) {
		i.Value->Start([&](BehaviorInterface* behavior) {
			behaviorQueue.HeapPush(NodePriority(behavior), NodePriorityPredicate());
		});
	}
}
void BehaviorArbiter::RunBehavior() {
	NodePriority top;
	if (behaviorQueue.Num() == 0)
		top.behavior = nullptr;
	else
		top = behaviorQueue.HeapTop();
	if (top.behavior != nullptr)
		currentBehavior = top.behavior;

	if (currentBehavior != nullptr) {
		currentBehavior->RunBehavior();
	}
	if (behaviorQueue.Num() != 0)
	behaviorQueue.Empty();
}
void BehaviorArbiter::UpdateBehavior() 
{
	for (auto i : behaviorMap) {
		i.Value->Start([&](BehaviorInterface* behavior) {
			behaviorQueue.HeapPush(NodePriority(behavior), NodePriorityPredicate());
		});
	}
}
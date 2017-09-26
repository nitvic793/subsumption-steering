// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorArbiter.h"
#include "SteerBehavior.h"
#include "WanderBehavior.h"

BehaviorArbiter::BehaviorArbiter(AActor *actr)
	:actor(actr)
{
	currentBehavior = nullptr;
	AddBehavior(STEER, new SteerBehavior(actr));
	AddBehavior(WANDER, new WanderBehavior(actr));
}

BehaviorArbiter::~BehaviorArbiter()
{
}

void BehaviorArbiter::AddBehavior(BehaviorEnum name, BehaviorInterface* behavior) {
	behaviorMap.Add(name, behavior);
}
void BehaviorArbiter::StartBehavior() {
	for (auto i : behaviorMap) {
		i.Value->Start([&]() {
			behaviorQueue.HeapPush(NodePriority(i.Value), NodePriorityPredicate());
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
void BehaviorArbiter::UpdateBehavior() {

}
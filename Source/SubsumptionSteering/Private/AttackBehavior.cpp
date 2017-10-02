// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackBehavior.h"

AttackBehavior::AttackBehavior(AActor* actr)
	:BehaviorInterface(actr)
{
}

AttackBehavior::~AttackBehavior()
{
}

void AttackBehavior::Start(std::function<void(BehaviorInterface*)> callback)
{
	callback(this);
}

void AttackBehavior::RunBehavior()
{

}
// Fill out your copyright notice in the Description page of Project Settings.

#include "WanderBehavior.h"

WanderBehavior::WanderBehavior(AActor* actor)
	:BehaviorInterface(actor)
{
	priority = 2;
}

WanderBehavior::~WanderBehavior()
{
}

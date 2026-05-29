// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_NeedsFood.generated.h"

/**
 * 
 */
UCLASS()
class SCHOONOOGHEYORANZOMBIERUNTIME_API UBTD_NeedsFood : public UBTDecorator
{
	GENERATED_BODY()

private:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, Category = "Condition")
	float FoodThreshold{ 5.0f };
};

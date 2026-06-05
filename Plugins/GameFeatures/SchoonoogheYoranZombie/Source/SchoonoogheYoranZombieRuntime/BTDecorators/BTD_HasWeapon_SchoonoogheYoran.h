// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_HasWeapon_SchoonoogheYoran.generated.h"

/**
 * 
 */
UCLASS()
class SCHOONOOGHEYORANZOMBIERUNTIME_API UBTD_HasWeapon_SchoonoogheYoran : public UBTDecorator
{
	GENERATED_BODY()
	
private:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector EquippedWeaponKey;
};

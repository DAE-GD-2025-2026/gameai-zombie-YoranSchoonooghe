// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_LocateItem.generated.h"

/**
 * 
 */
UCLASS()
class SCHOONOOGHEYORANZOMBIERUNTIME_API UBTT_LocateItem : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetItemKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector ItemLocationKey;
	
};

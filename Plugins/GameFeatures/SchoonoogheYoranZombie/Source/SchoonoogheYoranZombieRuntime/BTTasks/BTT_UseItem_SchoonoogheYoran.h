// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Items/BaseItem.h"
#include "BTT_UseItem_SchoonoogheYoran.generated.h"

/**
 * 
 */
UCLASS()
class SCHOONOOGHEYORANZOMBIERUNTIME_API UBTT_UseItem_SchoonoogheYoran : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, Category = "Item")
	TSubclassOf<ABaseItem> ItemClass;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector RequiredItemKey;
};

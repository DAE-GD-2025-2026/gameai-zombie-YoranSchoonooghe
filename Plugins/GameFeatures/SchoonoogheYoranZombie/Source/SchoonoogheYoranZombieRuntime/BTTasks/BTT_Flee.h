// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Flee.generated.h"

/**
 * 
 */
UCLASS()
class SCHOONOOGHEYORANZOMBIERUNTIME_API UBTT_Flee : public UBTTaskNode
{
	GENERATED_BODY()

public:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    
private:
    UPROPERTY(EditAnywhere, Category = "Node")
    float FleeDistance = 1000.0f;

    UPROPERTY(EditAnywhere, Category = "Node")
    float ThresholdDistance = 1000.0f;

    UPROPERTY(EditAnywhere, Category = "Blackboard")
    FBlackboardKeySelector TargetZombieKey;

    UPROPERTY(EditAnywhere, Category = "Blackboard")
    FBlackboardKeySelector FleeLocationKey;
};

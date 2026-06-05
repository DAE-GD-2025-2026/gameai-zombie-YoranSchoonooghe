// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_StopFlee_SchoonoogheYoran.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Survivor/SurvivorPawn.h"

EBTNodeResult::Type UBTT_StopFlee_SchoonoogheYoran::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    APawn* pSurvivor = OwnerComp.GetAIOwner()->GetPawn();
    UBlackboardComponent* pBlackboardComponent = OwnerComp.GetBlackboardComponent();

    if (!pSurvivor || !pBlackboardComponent)
    {
        return EBTNodeResult::Failed;
    }

    Cast<ASurvivorPawn>(pSurvivor)->StopRunning();

    if (!bClearFleeTarget)
    {
        return EBTNodeResult::Succeeded;
    }

    pBlackboardComponent->SetValueAsObject(FleeTargetKey.SelectedKeyName, nullptr);

	return EBTNodeResult::Succeeded;
}

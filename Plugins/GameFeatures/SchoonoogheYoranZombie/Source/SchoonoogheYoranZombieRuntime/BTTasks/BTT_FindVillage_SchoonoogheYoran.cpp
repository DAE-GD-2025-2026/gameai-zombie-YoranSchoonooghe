// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FindVillage_SchoonoogheYoran.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

EBTNodeResult::Type UBTT_FindVillage_SchoonoogheYoran::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    APawn* pSurvivor = OwnerComp.GetAIOwner()->GetPawn();
    if (!pSurvivor)
    {
        return EBTNodeResult::Failed;
    }

    UBlackboardComponent* pBlackboardComponent{ OwnerComp.GetBlackboardComponent() };
    if (!pBlackboardComponent)
    {
        return EBTNodeResult::Failed;
    }

    auto spawnLocation = pBlackboardComponent->GetValueAsVector(SpawnLocationKey.SelectedKeyName);
    FVector targetLocation = spawnLocation + SearchRadius * FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0);

    //SearchRadius += 30.0f;
    Angle += 30.0f * PI / 180.0f;

    pBlackboardComponent->SetValueAsVector(TargetLocationKey.SelectedKeyName, targetLocation);

	return EBTNodeResult::Succeeded;
}

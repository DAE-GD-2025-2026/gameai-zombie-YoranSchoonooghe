// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Flee_SchoonoogheYoran.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Survivor/SurvivorPawn.h"

EBTNodeResult::Type UBTT_Flee_SchoonoogheYoran::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    APawn* pSurvivor = OwnerComp.GetAIOwner()->GetPawn();
    UBlackboardComponent* pBlackboardComponent = OwnerComp.GetBlackboardComponent();

    if (!pSurvivor || !pBlackboardComponent)
    {
        return EBTNodeResult::Failed;
    }

    Cast<ASurvivorPawn>(pSurvivor)->StopRunning();

    AActor* pFleeTarget = Cast<AActor>(pBlackboardComponent->GetValueAsObject(FleeTargetKey.SelectedKeyName));
    if (!pFleeTarget)
    {
        return EBTNodeResult::Failed;
    }

    FVector survivorLocation = pSurvivor->GetActorLocation();
    FVector toFleeTarget = pFleeTarget->GetActorLocation() - survivorLocation;
    if (toFleeTarget.SquaredLength() > ThresholdDistance * ThresholdDistance)
    {
        return EBTNodeResult::Failed;
    }

    FVector fleeDirection = -toFleeTarget.GetSafeNormal();
    FVector fleeLocation = survivorLocation + (fleeDirection * FleeDistance);

    Cast<ASurvivorPawn>(pSurvivor)->StartRunning();
    pBlackboardComponent->SetValueAsVector(FleeLocationKey.SelectedKeyName, fleeLocation);

    return EBTNodeResult::Succeeded;
}

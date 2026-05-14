// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Flee.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

EBTNodeResult::Type UBTT_Flee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    APawn* pSurvivor = OwnerComp.GetAIOwner()->GetPawn();
    UBlackboardComponent* pBlackboardComponent = OwnerComp.GetBlackboardComponent();

    if (!pSurvivor || !pBlackboardComponent)
    {
        return EBTNodeResult::Failed;
    }

    AActor* pZombie = Cast<AActor>(pBlackboardComponent->GetValueAsObject(TargetZombieKey.SelectedKeyName));
    if (!pZombie)
    {
        return EBTNodeResult::Failed;
    }

    FVector survivorLocation = pSurvivor->GetActorLocation();
    FVector toZombie = pZombie->GetActorLocation() - survivorLocation;
    if (toZombie.SquaredLength() > ThresholdDistance * ThresholdDistance)
    {
        return EBTNodeResult::Failed;
    }

    FVector fleeDirection = -toZombie.GetSafeNormal();
    FVector fleeLocation = survivorLocation + (fleeDirection * FleeDistance);

    pBlackboardComponent->SetValueAsVector(FleeLocationKey.SelectedKeyName, fleeLocation);

    return EBTNodeResult::Succeeded;
}

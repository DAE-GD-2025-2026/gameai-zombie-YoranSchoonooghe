// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_LocateItem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTT_LocateItem::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* pBlackboardComponent = OwnerComp.GetBlackboardComponent();

    if (!pBlackboardComponent)
    {
        return EBTNodeResult::Failed;
    }

    AActor* pItem = Cast<AActor>(pBlackboardComponent->GetValueAsObject(TargetItemKey.SelectedKeyName));
    if (!pItem)
    {
        return EBTNodeResult::Failed;
    }

    pBlackboardComponent->SetValueAsVector(ItemLocationKey.SelectedKeyName, pItem->GetActorLocation());

    return EBTNodeResult::Succeeded;
}

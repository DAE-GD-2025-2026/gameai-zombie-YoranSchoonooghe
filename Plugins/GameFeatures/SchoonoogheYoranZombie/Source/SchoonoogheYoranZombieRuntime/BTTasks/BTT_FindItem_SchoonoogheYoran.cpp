// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FindItem_SchoonoogheYoran.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Items/BaseItem.h"
#include "Items/ItemType.h"
#include "SchoonoogheYoranZombieRuntime/StudentPerceptorSchoonoogheYoran.h"

EBTNodeResult::Type UBTT_FindItem_SchoonoogheYoran::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

    auto* pPerceptor = pSurvivor->FindComponentByClass<UStudentPerceptorSchoonoogheYoran>();
    if (!pPerceptor)
    {
        return EBTNodeResult::Failed;
    }

    if (!bIsRequiredItem)
    {
        for (ABaseItem* pItem : pPerceptor->SpottedItems)
        {
            if (pItem && pItem->GetItemType() != EItemType::Garbage)
            {
                pBlackboardComponent->SetValueAsObject(TargetItemKey.SelectedKeyName, pItem);

                return EBTNodeResult::Succeeded;
            }
        }

        return EBTNodeResult::Failed;
    }

    for (ABaseItem* pItem : pPerceptor->SpottedItems)
    {
        auto* pRequiredItem = pBlackboardComponent->GetValueAsClass(RequiredItemKey.SelectedKeyName);

        if (pItem && pItem->IsA(pRequiredItem))
        {
            pBlackboardComponent->SetValueAsObject(TargetItemKey.SelectedKeyName, pItem);

            return EBTNodeResult::Succeeded;
        }
    }

	return EBTNodeResult::Failed;
}

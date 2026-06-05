// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_PickUpItem_SchoonoogheYoran.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Common/InventoryComponent.h"
#include "Items/BaseItem.h"

EBTNodeResult::Type UBTT_PickUpItem_SchoonoogheYoran::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    APawn* pSurvivor = OwnerComp.GetAIOwner()->GetPawn();
    if (!pSurvivor)
    {
        return EBTNodeResult::Failed;
    }

    auto* pInventory = pSurvivor->GetComponentByClass<UInventoryComponent>();
    if (!pInventory)
    {
        return EBTNodeResult::Failed;
    }

    UBlackboardComponent* pBlackboardComponent{ OwnerComp.GetBlackboardComponent() };
    if (!pBlackboardComponent)
    {
        return EBTNodeResult::Failed;
    }

    ABaseItem* pItem = Cast<ABaseItem>(pBlackboardComponent->GetValueAsObject(TargetItemKey.SelectedKeyName));
    if (!pItem)
    {
        return EBTNodeResult::Failed;
    }

    auto pItemsInInventory{ pInventory->GetInventory() };
    for (int index{ 0 }; index < pInventory->GetInventoryCapacity(); ++index)
    {
        if (pItemsInInventory[index]) continue;

        pInventory->GrabItem(index, pItem);
        //pInventory->UseItem(index);

        pBlackboardComponent->ClearValue(TargetItemKey.SelectedKeyName);

        if (pItem->IsA(pBlackboardComponent->GetValueAsClass(RequiredItemKey.SelectedKeyName)))
        {
            pBlackboardComponent->ClearValue(RequiredItemKey.SelectedKeyName);
        }

        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}

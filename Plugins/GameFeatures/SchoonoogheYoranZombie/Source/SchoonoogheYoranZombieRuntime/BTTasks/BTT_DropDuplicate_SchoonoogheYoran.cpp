// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_DropDuplicate_SchoonoogheYoran.h"
#include "AIController.h"
#include "Items/BaseItem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Common/InventoryComponent.h"

EBTNodeResult::Type UBTT_DropDuplicate_SchoonoogheYoran::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* pBlackboardComponent = OwnerComp.GetBlackboardComponent();

	APawn* pSurvivor = OwnerComp.GetAIOwner()->GetPawn();
	if (!pSurvivor)
	{
		return EBTNodeResult::Failed;
	}

	auto* pInventoryComponent = pSurvivor->FindComponentByClass<UInventoryComponent>();
	if (!pInventoryComponent)
	{
		return EBTNodeResult::Failed;
	}

	auto pItemsInInventory = pInventoryComponent->GetInventory();
	for (int i{ 0 }; i < pItemsInInventory.Num() - 1; ++i)
	{
		auto const itemType = pItemsInInventory[i]->GetItemType();

		for (int j{ i + 1 }; j < pItemsInInventory.Num(); ++j)
		{
			if (pItemsInInventory[j]->GetItemType() == itemType)
			{
				pInventoryComponent->RemoveItem(j);

				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}

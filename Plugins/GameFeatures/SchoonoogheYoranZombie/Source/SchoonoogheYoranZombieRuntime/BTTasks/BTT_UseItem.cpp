// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_UseItem.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Common/InventoryComponent.h"

EBTNodeResult::Type UBTT_UseItem::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	for (int i{ 0 }; i < pItemsInInventory.Num(); ++i)
	{
		ABaseItem* pItem{ pItemsInInventory[i] };

		if (!pItem) continue;

		if (pItem->IsA(ItemClass))
		{
			auto* pSurvivorPawn = Cast<ASurvivorPawn>(pSurvivor);

			pItem->UseItem(*pSurvivorPawn);
			pInventoryComponent->RemoveItem(i);

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}

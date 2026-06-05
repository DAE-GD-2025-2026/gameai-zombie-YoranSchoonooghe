// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_HasFullInventory_SchoonoogheYoran.h"
#include "AIController.h"
#include "Common/InventoryComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTD_HasFullInventory_SchoonoogheYoran::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* pBlackboardComponent = OwnerComp.GetBlackboardComponent();

	APawn* pSurvivor = OwnerComp.GetAIOwner()->GetPawn();
	if (!pSurvivor)
	{
		return false;
	}

	auto* pInventoryComponent = pSurvivor->FindComponentByClass<UInventoryComponent>();
	if (!pInventoryComponent)
	{
		return false;
	}

	for (auto* pItem : pInventoryComponent->GetInventory())
	{
		if (!pItem)
		{
			return false;
		}
	}

	return true;
}

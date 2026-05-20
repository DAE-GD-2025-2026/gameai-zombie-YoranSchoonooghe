// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_DropWeapon.h"
#include "AIController.h"
#include "Items/Weapon.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Common/InventoryComponent.h"

EBTNodeResult::Type UBTT_DropWeapon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	auto* pWeapon = pBlackboardComponent->GetValueAsObject(EquippedWeaponKey.SelectedKeyName);
	auto pItemsInInventory = pInventoryComponent->GetInventory();
	for (int i{ 0 }; i < pItemsInInventory.Num(); ++i)
	{
		if (pItemsInInventory[i] == pWeapon)
		{
			pInventoryComponent->RemoveItem(i);
			pBlackboardComponent->SetValueAsObject(EquippedWeaponKey.SelectedKeyName, nullptr);

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}

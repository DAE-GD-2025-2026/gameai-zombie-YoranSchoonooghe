// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_HasWeapon.h"
#include "AIController.h"
#include "Common/InventoryComponent.h"
#include "Items/Weapon.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTD_HasWeapon::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* pBlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	auto* pWeapon = pBlackboardComponent->GetValueAsObject(EquippedWeaponKey.SelectedKeyName);
	if (pWeapon) return true;

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
		if (Cast<AWeapon>(pItem))
		{
			pBlackboardComponent->SetValueAsObject(EquippedWeaponKey.SelectedKeyName, pItem);

			return true;
		}
	}

	return false;
}

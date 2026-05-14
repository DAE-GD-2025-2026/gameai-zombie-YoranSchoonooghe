// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_HasWeapon.h"
#include "AIController.h"
#include "Common/InventoryComponent.h"
#include "Items/Weapon.h"

bool UBTD_HasWeapon::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
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
			return true;
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("RUUUUN!"));
	return false;
}

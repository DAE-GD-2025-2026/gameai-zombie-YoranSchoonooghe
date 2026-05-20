// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_HasAmmo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Items/Weapon.h"

bool UBTD_HasAmmo::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* pBlackboardComponent = OwnerComp.GetBlackboardComponent();

	auto* pWeapon = Cast<AWeapon>(pBlackboardComponent->GetValueAsObject(EquippedWeaponKey.SelectedKeyName));
	if (pWeapon->GetValue() == 0)
	{
		return false;
	}

	return true;
}

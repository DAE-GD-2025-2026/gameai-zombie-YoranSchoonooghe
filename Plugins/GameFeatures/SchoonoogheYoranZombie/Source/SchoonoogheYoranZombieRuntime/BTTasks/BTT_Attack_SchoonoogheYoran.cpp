// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Attack_SchoonoogheYoran.h"
#include "AIController.h"
#include "Common/InventoryComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Items/Weapon.h"

EBTNodeResult::Type UBTT_Attack_SchoonoogheYoran::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* pBlackboardComponent = OwnerComp.GetBlackboardComponent();

	APawn* pSurvivor = OwnerComp.GetAIOwner()->GetPawn();
	if (!pSurvivor)
	{
		return EBTNodeResult::Failed;
	}

	auto* pSurvivorPawn = Cast<ASurvivorPawn>(pSurvivor);

	auto* pWeapon = Cast<AWeapon>(pBlackboardComponent->GetValueAsObject(EquippedWeaponKey.SelectedKeyName));
	pWeapon->UseItem(*pSurvivorPawn);

	return EBTNodeResult::Succeeded;
}

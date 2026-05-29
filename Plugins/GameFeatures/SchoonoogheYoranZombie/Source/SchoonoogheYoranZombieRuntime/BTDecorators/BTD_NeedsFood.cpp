// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_NeedsFood.h"
#include "AIController.h"
#include "Common/StaminaComponent.h"

bool UBTD_NeedsFood::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* pSurvivor = OwnerComp.GetAIOwner()->GetPawn();

	if (!pSurvivor)
	{
		return false;
	}

	UStaminaComponent* pStaminaComponent = pSurvivor->FindComponentByClass<UStaminaComponent>();

	if (pStaminaComponent)
	{
		return pStaminaComponent->GetCurrentStamina() < FoodThreshold;
	}

	return false;
}

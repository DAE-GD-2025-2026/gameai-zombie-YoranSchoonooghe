// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_NeedsFood_SchoonoogheYoran.h"
#include "AIController.h"
#include "Common/StaminaComponent.h"

bool UBTD_NeedsFood_SchoonoogheYoran::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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

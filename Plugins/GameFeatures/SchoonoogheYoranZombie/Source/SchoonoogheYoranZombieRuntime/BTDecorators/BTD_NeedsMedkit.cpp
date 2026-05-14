// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_NeedsMedkit.h"
#include "AIController.h"
#include "Common/HealthComponent.h"

bool UBTD_NeedsMedkit::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* pSurvivor = OwnerComp.GetAIOwner()->GetPawn();

	if (!pSurvivor)
	{
		return false;
	}

	UHealthComponent* pHealthComponent = pSurvivor->FindComponentByClass<UHealthComponent>();

	if (pHealthComponent)
	{
		return pHealthComponent->GetHealth() < HealthThreshold;
	}

	return false;
}

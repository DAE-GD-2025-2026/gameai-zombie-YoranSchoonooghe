// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_TargetIsType_SchoonoogheYoran.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTD_TargetIsType_SchoonoogheYoran::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* pBlackboardComponent = OwnerComp.GetBlackboardComponent();

	auto* pTargetItem = Cast<ABaseItem>(pBlackboardComponent->GetValueAsObject(TargetItemKey.SelectedKeyName));
	if (pTargetItem->GetItemType() == TargetItemType)
	{
		return true;
	}

	return false;
}

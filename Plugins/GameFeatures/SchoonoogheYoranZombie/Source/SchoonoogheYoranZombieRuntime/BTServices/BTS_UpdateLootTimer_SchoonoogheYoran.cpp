// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_UpdateLootTimer_SchoonoogheYoran.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTS_UpdateLootTimer_SchoonoogheYoran::UBTS_UpdateLootTimer_SchoonoogheYoran()
{
}

void UBTS_UpdateLootTimer_SchoonoogheYoran::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    UBlackboardComponent* pBlackboard = OwnerComp.GetBlackboardComponent();

    if (!pBlackboard) return;

    float lastLootTime = pBlackboard->GetValueAsFloat(TimeSinceLoot.SelectedKeyName);

    lastLootTime += DeltaSeconds;

    pBlackboard->SetValueAsFloat(TimeSinceLoot.SelectedKeyName, lastLootTime);
}

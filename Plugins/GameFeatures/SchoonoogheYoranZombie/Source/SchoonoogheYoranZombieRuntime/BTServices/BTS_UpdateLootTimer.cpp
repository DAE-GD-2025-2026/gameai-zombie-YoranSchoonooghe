// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_UpdateLootTimer.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTS_UpdateLootTimer::UBTS_UpdateLootTimer()
{
	//Interval = 1.0f;
	//RandomDeviation = 0.2f;
}

void UBTS_UpdateLootTimer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    UBlackboardComponent* pBlackboard = OwnerComp.GetBlackboardComponent();

    if (!pBlackboard) return;

    float lastLootTime = pBlackboard->GetValueAsFloat(TimeSinceLoot.SelectedKeyName);

    lastLootTime += DeltaSeconds;

    pBlackboard->SetValueAsFloat(TimeSinceLoot.SelectedKeyName, lastLootTime);
}

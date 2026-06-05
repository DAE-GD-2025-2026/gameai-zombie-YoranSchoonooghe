// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_VisitHouse_SchoonoogheYoran.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Village/House/House.h"
#include "SchoonoogheYoranZombieRuntime/StudentPerceptorSchoonoogheYoran.h"

EBTNodeResult::Type UBTT_VisitHouse_SchoonoogheYoran::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    APawn* pSurvivor = OwnerComp.GetAIOwner()->GetPawn();
    if (!pSurvivor)
    {
        return EBTNodeResult::Failed;
    }

    UBlackboardComponent* pBlackboardComponent{ OwnerComp.GetBlackboardComponent() };
    if (!pBlackboardComponent)
    {
        return EBTNodeResult::Failed;
    }

    auto* pPerceptor = pSurvivor->FindComponentByClass<UStudentPerceptorSchoonoogheYoran>();
    if (!pPerceptor)
    {
        return EBTNodeResult::Failed;
    }

    auto* pTargetHouse = pBlackboardComponent->GetValueAsObject(TargetHouseKey.SelectedKeyName);

    if (pTargetHouse)
    {
        pPerceptor->UnexploredHouses.Remove(Cast<AHouse>(pTargetHouse));
    }

    if (pPerceptor->UnexploredHouses.Num() == 0)
    {
        if (bEnableRevisit)
        {
            if (pPerceptor->SpottedHouses.IsEmpty())
            {
                return EBTNodeResult::Failed;
            }

            auto* pHouse = *pPerceptor->SpottedHouses.begin();
            if (!pHouse)
            {
                return EBTNodeResult::Failed;
            }

            pPerceptor->UnexploredHouses.Add(pHouse);
            pBlackboardComponent->SetValueAsObject(FName("TargetHouse"), pHouse);
        }
        else
        {
            pBlackboardComponent->SetValueAsObject(TargetHouseKey.SelectedKeyName, nullptr);
        }

        return EBTNodeResult::Succeeded;
    }
    
    auto* pUnexploredHouse = *pPerceptor->UnexploredHouses.begin();
    pBlackboardComponent->SetValueAsObject(TargetHouseKey.SelectedKeyName, pUnexploredHouse);

	return EBTNodeResult::Succeeded;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPerceptorSchoonoogheYoran.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Zombies/BaseZombie.h"
#include "Items/BaseItem.h"
#include "PurgeZones/PurgeZone.h"
#include "Village/House/House.h"

UStudentPerceptorSchoonoogheYoran::UStudentPerceptorSchoonoogheYoran()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStudentPerceptorSchoonoogheYoran::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto PerceptionComp = GetOwner()->GetComponentByClass<UAIPerceptionComponent>())
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &UStudentPerceptorSchoonoogheYoran::OnPerceptionUpdated);
	}

	AAIController* AIController = Cast<AAIController>(GetOwner()->GetInstigatorController());
	if (!AIController) return;

	UBlackboardComponent* pBlackboardComponent = AIController->GetBlackboardComponent();
	if (!pBlackboardComponent) return;

	pBlackboardComponent->SetValueAsVector(FName("SpawnLocation"), GetOwner()->GetActorLocation());
}

void UStudentPerceptorSchoonoogheYoran::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UpdateUnexploredHouses(DeltaTime);
}

void UStudentPerceptorSchoonoogheYoran::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	AAIController* AIController = Cast<AAIController>(GetOwner()->GetInstigatorController());
	if (!AIController) return;

	UBlackboardComponent* pBlackboardComponent = AIController->GetBlackboardComponent();
	if (!pBlackboardComponent) return;

	if (Cast<ABaseZombie>(Actor))
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			pBlackboardComponent->SetValueAsObject(FName("TargetZombie"), Actor);
		}
	}
	else if (auto* pItem = Cast<ABaseItem>(Actor))
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			auto* pTargetItem = pBlackboardComponent->GetValueAsObject(FName("TargetItem"));
			if (!pTargetItem || Actor->IsA(pBlackboardComponent->GetValueAsClass(FName("RequiredItem"))))
			{
				pBlackboardComponent->SetValueAsObject(FName("TargetItem"), Actor);
			}
			else if (Cast<ABaseItem>(pTargetItem)->GetItemType() == EItemType::Garbage)
			{
				pBlackboardComponent->SetValueAsObject(FName("TargetItem"), Actor);
			}
			else
			{
				SpottedItems.Add(pItem);
			}
		}
	}
	else if (Cast<APurgeZone>(Actor))
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			pBlackboardComponent->SetValueAsObject(FName("PurgeZone"), Actor);
		}
	}
	else if (auto* pHouse = Cast<AHouse>(Actor))
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			if (!SpottedHouses.Contains(pHouse))
			{
				SpottedHouses.Add(pHouse);
				UnexploredHouses.Add(pHouse);

				auto* pTargetHouse = pBlackboardComponent->GetValueAsObject(FName("TargetHouse"));
				if (!pTargetHouse)
				{
					pBlackboardComponent->SetValueAsObject(FName("TargetHouse"), Actor);
				}
			}
		}
	}
}

void UStudentPerceptorSchoonoogheYoran::UpdateUnexploredHouses(float DeltaTime)
{
	elapsedTimeHouses += DeltaTime;

	float const resetHouseThreshold{ 80.0f };
	if (elapsedTimeHouses > resetHouseThreshold)
	{
		AAIController* AIController = Cast<AAIController>(GetOwner()->GetInstigatorController());
		if (!AIController) return;

		UBlackboardComponent* pBlackboardComponent = AIController->GetBlackboardComponent();
		if (!pBlackboardComponent) return;

		auto* pHouse = *SpottedHouses.begin();
		if (!pHouse) return;

		UnexploredHouses.Add(pHouse);
		auto* pTargetHouse = pBlackboardComponent->GetValueAsObject(FName("TargetHouse"));
		if (!pTargetHouse)
		{
			pBlackboardComponent->SetValueAsObject(FName("TargetHouse"), pHouse);
		}

		elapsedTimeHouses = 0.0f;
	}
}

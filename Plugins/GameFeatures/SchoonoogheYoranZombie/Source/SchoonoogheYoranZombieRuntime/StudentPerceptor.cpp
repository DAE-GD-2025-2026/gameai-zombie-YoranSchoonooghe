// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPerceptor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Zombies/BaseZombie.h"
#include "Items/BaseItem.h"
#include "PurgeZones/PurgeZone.h"
#include "Village/House/House.h"

UStudentPerceptor::UStudentPerceptor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStudentPerceptor::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto PerceptionComp = GetOwner()->GetComponentByClass<UAIPerceptionComponent>())
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &UStudentPerceptor::OnPerceptionUpdated);
	}
}

void UStudentPerceptor::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	//GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	//FString::Printf(TEXT("Saw Something!")));

	//auto actorClass = Actor->GetClass();
	//auto label = Actor->GetActorLabel();
	//GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, label);

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
	else if (Cast<ABaseItem>(Actor))
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
			if (!ExploredHouses.Contains(pHouse))
			{
				ExploredHouses.Add(pHouse);
				pBlackboardComponent->SetValueAsObject(FName("TargetHouse"), Actor);
			}
			
			pBlackboardComponent->SetValueAsObject(FName("LastHouse"), Actor);
		}
	}
}

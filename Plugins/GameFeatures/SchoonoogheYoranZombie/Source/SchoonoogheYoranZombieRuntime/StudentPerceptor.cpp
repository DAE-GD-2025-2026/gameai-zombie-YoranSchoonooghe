// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPerceptor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Zombies/BaseZombie.h"

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

	auto zombieActor = Cast<ABaseZombie>(Actor);
	if (zombieActor)
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			pBlackboardComponent->SetValueAsObject(FName("TargetZombie"), Actor);
		}
	}
}

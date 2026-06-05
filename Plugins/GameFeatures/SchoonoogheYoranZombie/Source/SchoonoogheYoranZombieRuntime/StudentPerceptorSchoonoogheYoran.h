// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISense_Damage.h"
#include "Items/BaseItem.h"
#include "Village/House/House.h"
#include "StudentPerceptorSchoonoogheYoran.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SCHOONOOGHEYORANZOMBIERUNTIME_API UStudentPerceptorSchoonoogheYoran : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStudentPerceptorSchoonoogheYoran();
	
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	virtual void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	TSet<ABaseItem*> SpottedItems;
	TSet<AHouse*> SpottedHouses;
	TSet<AHouse*> UnexploredHouses;

private:
	void UpdateUnexploredHouses(float DeltaTime);

	float elapsedTimeHouses{ 0.0f };

};

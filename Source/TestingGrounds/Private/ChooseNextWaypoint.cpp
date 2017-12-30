// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Classes/AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// Get patrol route
	auto PatrolRoute = OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; } // Protect pointer AND return the correct type of result for this function

	// Warn about empty patrol route
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is missing patrol points"), *(OwnerComp.GetAIOwner()->GetPawn()->GetName()))
		return EBTNodeResult::Failed;
	}

	// Set next waypoint
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	auto Index = Blackboard->GetValueAsInt(IndexKey.SelectedKeyName);
	Blackboard->SetValueAsObject(NextWayPointKey.SelectedKeyName, PatrolPoints[Index]);

	// Cycle index
	auto NewIndex = (Index + 1) % PatrolPoints.Num(); // Modulus operator returns a remainder
	Blackboard->SetValueAsInt(IndexKey.SelectedKeyName, NewIndex);

	return EBTNodeResult::Succeeded;
}




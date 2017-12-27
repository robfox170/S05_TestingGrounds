// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Classes/AIController.h"
#include "PatrollingGuard.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// Get patrol points
	auto Patroller = Cast<APatrollingGuard>(OwnerComp.GetAIOwner()->GetPawn());
	auto PatrolPoints = Patroller->PatrolPointsCPP;

	// Set next waypoint
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	auto Index = Blackboard->GetValueAsInt(IndexKey.SelectedKeyName);
	Blackboard->SetValueAsObject(NextWayPointKey.SelectedKeyName, PatrolPoints[Index]);

	// Cycle index
	auto NewIndex = (Index + 1) % PatrolPoints.Num(); // Modulus operator returns a remainder
	Blackboard->SetValueAsInt(IndexKey.SelectedKeyName, NewIndex);

	return EBTNodeResult::Succeeded;
}




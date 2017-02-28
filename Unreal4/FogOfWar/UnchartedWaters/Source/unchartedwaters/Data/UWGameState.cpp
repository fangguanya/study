#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWGameState
// !< Date : 2/27/2017 12:03:53 PM
// !< Author : fanggang

#include "unchartedwaters.h"
#include "UWGameState.h"

AUWGameState::AUWGameState(const FObjectInitializer& objectInitializer)
	:Super(objectInitializer)
{
	StartTime = -1f;
}

float AUWGameState::GetLeftTime() const
{
	if (StartTime > 0.f)
	{
		return FMath::Max(StartTime - GetWorld()->GetTimeSeconds(), 0.f);
	}
	return 0;
}

float AUWGameState::GetElapseTime() const
{
	if (StartTime > 0.f)
	{
		return FMath::Max(GetWorld()->GetTimeSeconds() - StartTime, 0.f);
	}
	return 0;
}

float AUWGameState::GetStartTime() const
{
	return StartTime;
}

int32 AUWGameState::GetTeamKills(int32 TeamIndex) const
{
	if (TeamIndex >= 0 && TeamIndex < TeamKills.Num())
	{
		return TeamKills[TeamIndex];
	}
	return -1;
}

void AUWGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUWGameState, TeamKills);
	DOREPLIFETIME(AUWGameState, StartTime);
}
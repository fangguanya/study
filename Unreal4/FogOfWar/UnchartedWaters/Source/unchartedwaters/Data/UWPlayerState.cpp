#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWPlayerState
// !< Date : 2/27/2017 12:03:53 PM
// !< Author : fanggang

#include "unchartedwaters.h"
#include "UWPlayerState.h"

AUWPlayerState::AUWPlayerState(const FObjectInitializer& objectInitializer)
	:Super(objectInitializer)
{
	TeamIndex = 0;
	TeamPlayerIndex = 0;
	SelectedTemplateID = 0;
}

int32 AUWPlayerState::GetTeamIndex() const
{
	return TeamIndex;
}

void AUWPlayerState::SetTeamIndex(int32 InIndex)
{
	TeamIndex = InIndex;
}

int32 AUWPlayerState::GetTeamPlayerIndex() const
{
	return TeamPlayerIndex;
}

void AUWPlayerState::SetTeamPlayerIndex(int32 InIndex)
{
	TeamPlayerIndex = InIndex;
}

int32 AUWPlayerState::GetTemplateID() const
{
	return SelectedTemplateID;
}

void AUWPlayerState::SetTemplateID(int32 InIndex)
{
	SelectedTemplateID = InIndex;
}

void AUWPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUWPlayerState, TeamIndex);
	DOREPLIFETIME(AUWPlayerState, TeamPlayerIndex);
	DOREPLIFETIME(AUWPlayerState, SelectedTemplateID);
	DOREPLIFETIME(AUWPlayerState, Kills);
	DOREPLIFETIME(AUWPlayerState, Deaths);
	DOREPLIFETIME(AUWPlayerState, Assists);
	DOREPLIFETIME(AUWPlayerState, IncomeCoin);
}
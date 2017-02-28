#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : FTeamData
// !< Date : 2/28/2017 6:45:24 PM
// !< Author : fanggang

#include "Data/UWPlayerState.h"
#include "FTeamData.generated.h"

USTRUCT()
struct FTeamData
{
	GENERATED_USTRUCT_BODY();

	TArray<AUWPlayerState*> Players;
};
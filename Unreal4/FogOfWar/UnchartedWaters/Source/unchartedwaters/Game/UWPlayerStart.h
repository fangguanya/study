#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UMPlayerStart
// !< Date : 2/28/2017 5:50:57 PM
// !< Author : fanggang

#include "GameFramework/PlayerStart.h"
#include "UMPlayerStart.generated.h"

UCLASS()
class AUMPlayerStart : APlayerStart
{
	GENERATED_UCLASS_BODY()

protected:
	UPROPERTY(EditInstanceOnly, Category = UW)
		int32 TeamIndex;
	UPROPERTY(EditInstanceOnly, Category = UW)
		int32 SpawnIndex;
};

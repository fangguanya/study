#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWPlayerCharacter
// !< Date : 2/27/2017 10:42:12 AM
// !< Author : fanggang

#include "UWCharacter.h"
#include "Core/UWPlayerController.h"
#include "UWPlayerCharacter.generated.h"

UCLASS()
class AUWPlayerCharacter : public AUWCharacter
{
	GENERATED_UCLASS_BODY()

protected:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = UW)
		AUWPlayerController
public:

};
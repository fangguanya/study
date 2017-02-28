#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWGameMode
// !< Date : 2/27/2017 10:42:12 AM
// !< Author : fanggang

#include "Game/UWPlayerCharacter.h"
#include "GameFramework/GameMode.h"
#include "UWGameMode.generated.h"

UCLASS()
class AUWPlayerController : public class APlayerController
{
	GENERATED_UCLASS_BODY()

protected:
	UPROPERTY(Replicated)
		AUWPlayerCharacter* PlayerCharacter;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	/* Input actions --- BEGIN */
	void OnClickAction();
	/* Input actions --- END */

public:

};
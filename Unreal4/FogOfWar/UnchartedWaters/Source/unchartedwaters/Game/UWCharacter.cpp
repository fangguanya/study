#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWCharacter
// !< Date : 2/28/2017 10:45:07 AM
// !< Author : fanggang

#include "unchartedwaters.h"
#include "UWCharacter.h"
#include "UnrealNetwork.h"

AUWCharacter::AUWCharacter(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{}

void AUWCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUWCharacter, CharType);
}
#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWSkill
// !< Date : 2/28/2017 3:52:27 PM
// !< Author : fanggang

#include "UWSkill.h"

AUWSkill::AUWSkill(const FObjectInitializer& objectInitializer)
	:Super(objectInitializer)
{

}

bool AUWSkill::GetAttributeCOnfig(FAttributeConfig& InConfig)
{
	// !< TODO : 根据配表或者配置返回属性相关.
	return false;
}
void AUWSkill::SetOwnerCharacter(AUWGameCharacter* InCharacter)
{
	OwnerCharacter = InCharacter;
}
void AUWSkill::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUWSkill, OwnerCharacter);
	DOREPLIFETIME(AUWSkill, SkillState);
}
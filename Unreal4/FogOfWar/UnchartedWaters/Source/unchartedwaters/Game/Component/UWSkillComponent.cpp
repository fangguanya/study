#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWSkillComponent
// !< Date : 2/28/2017 2:14:40 PM
// !< Author : fanggang

#include "UWSkillComponent.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUWSkillComponent, Log, All)


UWSkillComponent::UWSkillComponent(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWSkillComponent::Initialize(AUWGameCharacter* InCharacter)
{
	OwnerCharacter = InCharacter;
}
void UWSkillComponent::AddSkill(AUWSkill* InSkill)
{
	InSkill->SetOwnerCharacter(OwnerCharacter);
	Skills.AddUnique(InSkill);
}
void UWSkillComponent::RemoveSkill(AUWSkill* InSkill)
{
	if (Skills.Remove(InSkill) > 0)
	{
		InSkill->SetOwnerCharacter(nullptr);
	}
}
void UWSkillComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWSkillComponent, OwnerCharacter);
	DOREPLIFETIME(UWSkillComponent, Skills);
}

bool UWSkillComponent::UseSkill_Validate(AUWSkill* InSkill)
{
	return true;
}
void UWSkillComponent::UseSkill_Implementation(AUWSkill* InSkill)
{
	if (!InSkill->IsA(AUWPositiveSkill::StaticClass()))
	{
		return;
	}

	if (!OwnerCharacter->IsAlive())
	{
		return;
	}

	AUWPositiveSkill* PositiveSkill = Cast<AUWPositiveSkill>(InSkill);
	if (OwnerCharacter->Role == ROLE_Authority)
	{
		PositiveSkill->ServerPerformSkill();
	}
	else
	{
		PositiveSkill->ClientPerformSkill();
	}
}
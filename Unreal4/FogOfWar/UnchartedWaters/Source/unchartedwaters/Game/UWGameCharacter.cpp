#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWCharacter
// !< Date : 2/28/2017 10:45:07 AM
// !< Author : fanggang

#include "unchartedwaters.h"
#include "UWCharacter.h"
#include "UnrealNetwork.h"
#include "Game/Component/UWAttributeComponent.h"
#include "Game/Component/UWSkillComponent.h"
#include "Game/Component/UWEquipmentComponent.h"

AUWGameCharacter::AUWGameCharacter(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	AttributeComponent = CreateDefaultSubobject<UWAttributeComponent>(TEXT("AttributeManager"));
	SkillComponent = CreateDefaultSubobject<UWSkillComponent>(TEXT("SkillManager"));
	EquipmentComponent = CreateDefaultSubobject<UWEquipmentComponent>(TEXT("EquipmentManger"));
}

void AUWGameCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUWGameCharacter, AttributeComponent);
	DOREPLIFETIME(AUWGameCharacter, EquipmentComponent);
	DOREPLIFETIME(AUWGameCharacter, SkillComponent);
}

void AUWGameCharacter::SwitchToTemplate(int32 InTemplateID)
{
	AttributeComponent->SwitchToTemplate(InTemplateID);
}

bool AUWGameCharacter::IsAlive()
{
	// !< TODO : ±àÐ´ËÀÍöÂß¼­
	return true;
}
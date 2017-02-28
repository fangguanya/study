#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWEquipComponent
// !< Date : 2/28/2017 11:15:29 AM
// !< Author : fanggang

#include "UWUseableEquipment.h"
#include "UWEquipComponent.h"

DECLARE_LOG_CATEGORY_CLASS(LogUWEquipmentComponent, Log, All);

UWEquipmentComponent::UWEquipmentComponent(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWEquipmentComponent::Initialize(AUWGameCharacter* InCharacter)
{
	OwnerCharacter = InCharacter;
}
void UWEquipmentComponent::AddEquipment(AUWEquipment* InEquipment)
{
	InEquipment->SetOwnerCharacter(OwnerCharacter);
	Equipments.AddUnique(InEquipment);
}
void UWEquipmentComponent::RemoveEquipment(AUWEquipment* InEquipment)
{
	if (Equipments.Remove(InEquipment) > 0)
	{
		InEquipment->SetOwnerCharacter(nullptr);
	}
}
void UWEquipmentComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWEquipmentComponent, OwnerCharacter);
	DOREPLIFETIME(UWEquipmentComponent, Equipments);
}

bool UWEquipmentComponent::UseEquipment_Validate(AUWEquipment* InEquipment)
{
	return true;
}
void UWEquipmentComponent::UseEquipment_Implementation(AUWEquipment* InEquipment)
{
	if (!InEquipment->IsA(AUWUseableEquipment::StaticClass()))
	{
		return;
	}

	if (!OwnerCharacter->IsAlive())
	{
		return;
	}

	AUWUseableEquipment* UseableEquipment = Cast<AUWUseableEquipment>(InEquipment);
	if (OwnerCharacter->Role == ROLE_Authority)
	{
		UseableEquipment->ServerPerformEquipment();
	}
	else
	{
		UseableEquipment->ClientPerformEquipment();
	}
}
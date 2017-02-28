#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWEquipment
// !< Date : 2/28/2017 2:50:39 PM
// !< Author : fanggang

#include "UWEquipment.h"

AUWEquipment::AUWEquipment(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{}
void AUWEquipment::SetOwnerCharacter(AUWGameCharacter* InCharacter)
{
	OwnerCharacter = InCharacter;
}
bool AUWEquipment::GetAttributeCOnfig(FAttributeConfig& InConfig)
{
	// !< TODO : ����һ���������? ����ȫCSV, ߀������CSV���ǳ����Ԅ��޸�DefaultObject?
	return false;
}
void AUWEquipment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUWEquipment, EquipmentType);
	DOREPLIFETIME(AUWEquipment, OwnerCharacter);
}
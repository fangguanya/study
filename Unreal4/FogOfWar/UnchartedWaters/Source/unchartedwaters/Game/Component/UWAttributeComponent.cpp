#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWAttributeComponent
// !< Date : 2/28/2017 11:15:29 AM
// !< Author : fanggang

#include "UWAttributeComponent.h"

DECLARE_LOG_CATEGORY_CLASS(LogUWAttributeComponent, Log, All);
UWAttributeComponent::UWAttributeComponent(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWAttributeComponent::Initialize(AUWGameCharacter* InCharacter, int32 InTemplate, int32 InLevel)
{
	OwnerCharacter = InCharacter;
	OwnerLevel = InLevel;
	TemplateID = InTemplate;
	SyncBaseValues();
}
void UWAttributeComponent::GetCurrentValue(EAttributeType InType) const
{
	return BaseValue[(uint8)InType] + equipValue[(uint8)InType] + SkillValue[(uint8)InType];
}
void UWAttributeComponent::GetBaseValue(EAttributeType InType) const
{
	return BaseValue[(uint8)InType];
}
void UWAttributeComponent::GetEquipValue(EAttributeType InType) const
{
	return EquipValue[(uint8)InType];
}
void UWAttributeComponent::GetSkillValue(EAttributeType InType) const
{
	return SkillValue[(uint8)InType];
}

void UWAttributeComponent::OwnerLevelUp()
{
	OwnerLevel += 1;
	SyncBaseValues();
}
void UWAttributeComponent::AppendEquip(const FAttributeConfig& InConfig)
{
	EquipValue[(uint8)EAttributeType::AT_ATTACK] += InConfig.Attack;
}
void UWAttributeComponent::RemoveEquip(const FAttributeConfig& InConfig)
{
	EquipValue[(uint8)EAttributeType::AT_ATTACK] -= InConfig.Attack;
}
void UWAttributeComponent::AppendSkill(const FAttributeConfig& InConfig)
{
	SkillValue[(uint8)EAttributeType::AT_ATTACK] += InConfig.Attack;
}
void UWAttributeComponent::RemoveSkill(const FAttributeConfig& InConfig)
{
	SkillValue[(uint8)EAttributeType::AT_ATTACK] -= InConfig.Attack;
}
void UWAttributeComponent::GetLevel() 
{ 
	return OwnerLevel; 
}
void UWAttributeComponent::SyncBaseValues()
{
	FAttributeConfig Config;
	GetAttributeConfig(Config);
	BaseValue[(uint8)EAttributeType::AT_ATTACK] = Config.Attack;
}
void UWAttributeComponent::SwitchToTemplate(int32 InTemplateID)
{
	TemplateID = InTemplateID;
	SyncBaseValues();
}
void UWAttributeComponent::GetAttributeConfig(FAttributeConfig& InConfig)
{
	// !< TODO : 读取基础属性配置表, 根据等级进行处理
}

void UWAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWAttributeComponent, BaseValue);
	DOREPLIFETIME(UWAttributeComponent, EquipValue);
	DOREPLIFETIME(UWAttributeComponent, SkillValue);
	DOREPLIFETIME(UWAttributeComponent, OwnerCharacter);
	DOREPLIFETIME(UWAttributeComponent, OwnerLevel);
	DOREPLIFETIME(UWAttributeComponent, TemplateID);
}
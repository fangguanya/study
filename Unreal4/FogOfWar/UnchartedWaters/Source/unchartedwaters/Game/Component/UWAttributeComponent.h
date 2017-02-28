#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWAttributeComponent
// !< Date : 2/28/2017 11:15:22 AM
// !< Author : fanggang
#include "UWGameCharacter.h"
#include "Components/ActorComponent.h"
#include "UWAttributeComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUWAttributeComponent, Log, All);

UENUM(BlueprintType)
enum class EAttributeType : uint8
{
	AT_ATTACK UMETA(DisplayName = "Attack"),
	AT_MAX UMETA(Hidden)
};

// !< TODO : 属性是否要分层?
// !< TODO : 初始属性, 等级属性, 装备属性, 技能属性的配表
UCLASS()
class UWAttributeComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

protected:
	// ID for reading from template-config-csv. (different ship belongs to different template! also used when levelup).
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = UW)
		int32 TemplateID;
	UPROPERTY(Replicated)
		float BaseValue[(uint8)EAttributeType::AT_Max];
	UPROPERTY(Replicated)
		float EquipValue[(uint8)EAttributeType::AT_Max];
	UPROPERTY(Replicated)
		float SkillValue[(uint8)EAttributeType::AT_Max];
	UPROPERTY(Replicated, BlueprintReadOnly)
		AUWGameCharacter* OwnerCharacter;
	UPROPERTY(Replicated)
		int32 OwnerLevel;

public:
	void Initialize(AUWGameCharacter* InCharacter, int32 InTemplate, int32 InLevel);

	UFUNCTION(BlueprintCallable, Category = UW)
		float GetCurrentValue(EAttributeType InType) const;
	UFUNCTION(BlueprintCallable, Category = UW)
		float GetBaseValue(EAttributeType InType) const;
	UFUNCTION(BlueprintCallable, Category = UW)
		float GetEquipValue(EAttributeType InType) const;
	UFUNCTION(BlueprintCallable, Category = UW)
		float GetSkillValue(EAttributeType InType) const;

	UFUNCTION(BlueprintCallable, Category = UW)
		void OwnerLevelUp();
	UFUNCTION(BlueprintCallable, Category = UW)
		void AppendEquip(const FAttributeConfig& InConfig);
	UFUNCTION(BlueprintCallable, Category = UW)
		void RemoveEquip(const FAttributeConfig& InConfig);
	UFUNCTION(BlueprintCallable, Category = UW)
		void AppendSkill(const FAttributeConfig& InConfig);
	UFUNCTION(BlueprintCallable, Category = UW)
		void RemoveSkill(const FAttributeConfig& InConfig);

	UFUNCTION(BlueprintCallable, Category = UW)
		void GetLevel();
	UFUNCTION(BlueprintCallable, Category = UW)
		void SwitchToTemplate(int32 InTemplateID);

public:
	void GetAttributeConfig(FAttributeConfig& InConfig);
	void SyncBaseValues();
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
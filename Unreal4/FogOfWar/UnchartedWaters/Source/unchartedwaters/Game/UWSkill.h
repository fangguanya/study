#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWSkill
// !< Date : 2/28/2017 3:52:20 PM
// !< Author : fanggang

#include "UWGameCharacter.h"
#include "UWSkill.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUWSkill, Log, All);

UENUM()
enum class ESkillState : uint8
{
	Ready,
	NotLearned,
	Cooldown,
	Performing,
	Disabled,
};

// !< TODO : 技能配表搞一下, 技能升级读表等
// !< TODO : 针对主动技能, 被动技能扩展实现下.
UCLASS()
class AUWSkill : public UObject
{
	GENERATED_UCLASS_BODY()

protected:
	UPROPERTY(Replicated)
		ESkillState SkillState;
	UPROPERTY(Replicated, BlueprintReadOnly, Category = UW)
		AUWGameCharacter* OwnerCharacter;

public:
	UFUNCTION(BlueprintCallable, Category = UW)
		bool GetAttributeCOnfig(FAttributeConfig& InConfig);

public:
	void SetOwnerCharacter(AUWGameCharacter* InCharacter);
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

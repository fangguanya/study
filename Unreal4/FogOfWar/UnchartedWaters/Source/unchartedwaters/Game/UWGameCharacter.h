#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWGameCharacter
// !< Date : 2/28/2017 10:44:57 AM
// !< Author : fanggang

#include "UWCharacter.h"
#include "UWAttributeComponent.h"
#include "UWEquipComponent.h"
#include "UWSkillComponent.h"
#include "UWCharacter.generated.h"

// !< TODO : 伤害计算等如何处理呢?
// !< TODO : 战斗相关, 目标选取, 特效播放等等.
// !< TODO : 动画播放相关
UCLASS(ABSTRACT)
class AUWGameCharacter : public AUWCharacter
{
	GENERATED_UCLASS_BODY()

protected:
	UPROPERTY(replicate, VisibleAnywhere, BlueprintReadOnly, Category = UW)
		UWAttributeComponent* AttributeComponent;
	UPROPERTY(replicate, VisibleAnywhere, BlueprintReadOnly, Category = UW)
		UWEquipmentComponent* EquipmentComponent;
	UPROPERTY(replicate, VisibleAnywhere, BlueprintReadOnly, Category = UW)
		UWSkillComponent* SkillComponent;

public:
	UFUNCTION(BlueprintCallable, Category = UW)
		void SwitchToTemplate(int32 InTemplateID);
	UFUNCTION(BlueprintCallable, Category = UW)
		bool IsAlive();

public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
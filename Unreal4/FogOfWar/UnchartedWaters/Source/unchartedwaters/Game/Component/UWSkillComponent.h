#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWSkillComponent
// !< Date : 2/28/2017 2:15:42 PM
// !< Author : fanggang

#include "UWSkillComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUWSkillComponent, Log, All)

UCLASS()
class UWSkillComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

protected:
	UPROPERTY(Replicated, VisibleAnywhere, Category = UW)
		TArray<AUWSkill*> Skills;
	UPROPERTY(Replicated, BlueprintReadOnly)
		AUWGameCharacter* OwnerCharacter;

public:
	void Initialize(AUWGameCharacter* InCharacter);

	UFUNCTION(BlueprintCallable, Category = UW)
		void AddSkill(AUWSkill* InSkill);
	UFUNCTION(BlueprintCallable, Category = UW)
		void RemoveSkill(AUWSkill* InSkill);
	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void UseSkill(AUWSkill* InSkill);

public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
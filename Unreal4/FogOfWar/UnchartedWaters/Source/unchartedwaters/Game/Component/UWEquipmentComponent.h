#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWEquipComponent
// !< Date : 2/28/2017 11:45:13 AM
// !< Author : fanggang

#include "Game/UWEquipment.h"
#include "UWEquipComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUWEquipmentComponent, Log, All)

UCLASS()
class UWEquipmentComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

protected:
	UPROPERTY(Replicated, VisibleAnywhere, Category = UW)
		TArray<AUWEquipment*> Equipments;
	UPROPERTY(Replicated, BlueprintReadOnly)
		AUWGameCharacter* OwnerCharacter;

public:
	void Initialize(AUWGameCharacter* InCharacter);

	UFUNCTION(BlueprintCallable, Category = UW)
		void AddEquipment(AUWEquipment* InEquipment);
	UFUNCTION(BlueprintCallable, Category = UW)
		void RemoveEquipment(AUWEquipment* InEquipment);
	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void UseEquipment(AUWEquipment* InEquipment);

public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

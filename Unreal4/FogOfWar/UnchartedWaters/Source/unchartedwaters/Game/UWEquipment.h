#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWEquipment
// !< Date : 2/28/2017 2:50:31 PM
// !< Author : fanggang

#include "UWEquipment.generated.h"

UENUM(BlueprintType)
enum UWEquipmentType : uint8
{
	Weapon,
	Armor,
	Usable, // !< 可以使用的東西, 比如藥瓶等, 實際是釋放了一個技能, (TODO : 繼承實現)
	// TODO : Add more equip types.
};

// !< TODO : 物品是否有位置一说? 类似War3还是LOL?
UCLASS()
class AUWEquipment : public UObject
{
	GENERATED_UCLASS_BODY()

protected:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = UW)
		UWEquipmentType EquipmentType;
	UPROPERTY(Replicated, BlueprintReadOnly, Category = UW)
		AUWGameCharacter* OwnerCharacter;

public:
	UFUNCTION(BlueprintCallable, Category = UW)
		bool GetAttributeCOnfig(FAttributeConfig& InConfig);

public:
	void SetOwnerCharacter(AUWGameCharacter* InCharacter);
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
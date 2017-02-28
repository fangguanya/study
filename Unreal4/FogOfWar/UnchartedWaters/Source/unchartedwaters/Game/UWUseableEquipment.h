#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWUseableEquipment
// !< Date : 2/28/2017 4:48:32 PM
// !< Author : fanggang

#include "UWEquipment.h"
#include "UWUseableEquipment.generated.h"

UCLASS()
class AUWUseableEquipment : public class AUWEquipment
{
	GENERATED_UCLASS_BODY();

protected:

public:
	UFUNCTION(BlueprintCallable, Category = UW)
		bool CouldUseEquipment();

	void ServerPerformEquipment();
	void ClientPerformEquipment();
};

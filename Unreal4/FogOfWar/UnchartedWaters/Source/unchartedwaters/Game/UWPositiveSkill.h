#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWPositiveSkill
// !< Date : 2/28/2017 5:03:08 PM
// !< Author : fanggang

#include "UWSkill.h"
#include "UWPositiveSkill.generated.h"

UCLASS()
class AUWPositiveSkill : public class AUWSkill
{
	GENERATED_UCLASS_BODY();

protected:

public:
	void ServerPerformSkill();
	void ClientPerformSkill();
};
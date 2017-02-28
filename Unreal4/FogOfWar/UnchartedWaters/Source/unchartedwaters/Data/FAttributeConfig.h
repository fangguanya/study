#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : FAttributeConfig
// !< Date : 2/28/2017 11:29:48 AM
// !< Author : fanggang

#include "FAttributeConfig.generated.h"

USTRUCT()
struct FAttributeConfig : FTableRowBase
{
	GENERATED_USTRUCT_BODY()
		
public:
	UPROPERTY()
		float Attack;
};
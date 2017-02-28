#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWUseableEquipment
// !< Date : 2/28/2017 4:48:48 PM
// !< Author : fanggang

#include "UWUseableEquipment.h"

AUWUseableEquipment::AUWUseableEquipment(const FObjectInitializer& objectInitializer)
	:Super(objectInitializer)
{

}

bool AUWUseableEquipment::CouldUseEquipment()
{
	// TODO : 增加物品使用次数, 或者使用CD的限制
}

void AUWUseableEquipment::ServerPerformEquipment()
{
	// !< TODO : 添加服务器使用
}

void AUWUseableEquipment::ClientPerformEquipment()
{
	// !< TODO : 添加客户端使用
}
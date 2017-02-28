#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWGameInstance
// !< Date : 2/27/2017 12:08:07 PM
// !< Author : fanggang

#include "unchartedwaters.h"
#include "UWGameInstance.h"

UWGameInstance::UWGameInstance(const FObjectInitializer& objectInitializer)
	:Super(objectInitializer)
{

}

UWGameInstance::~UWGameInstance()
{

}

void UWGameInstance::CloseGame()
{
	FGenericPlatformMisc::RequestExit(false);
}
#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWGameInstance
// !< Date : 2/27/2017 12:08:01 PM
// !< Author : fanggang

#include "UWGameInstance.generated.h"

// 存放玩家整体的一些信息, 类似LOL在外面界面就能显示的而跟具体某场战斗无关的数据.(理应包含积分, 充值的钻石的属性!)
UCLASS()
class UWGameInstance : UGameInstance
{
	GENERATED_UCLASS_BODY()

protected:
	// 当前登录的玩家ID
	UPROPERTY(BlueprintReadOnly, Category = UW)
		FString CurrentUserID;
	// 当前登录的玩家名字(UI显示用)
	UPROPERTY(BlueprintReadOnly, Category = UW)
		FString CurrentUserName;

	// !< TODO1 : 增加游戏连接登陆服务器的逻辑, 返回自身属性等等, 并返回游戏服务器(用于匹配或者建房间等)地址
	// !< TODO2 : 增加游戏服务器匹配逻辑.


public:
	~UWGameInstance();

	UFUNCTION(BlueprintCallable, Category = UW)
		void CloseGame();
};
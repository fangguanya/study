#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWGameMode
// !< Date : 2/27/2017 10:42:12 AM
// !< Author : fanggang

#include "Game/UWEquipment.h"
#include "GameFramework/GameMode.h"
#include "UWGameMode.generated.h"

UENUM()
enum class EGameStatus : uint8
{
	EPreGame,
	ECharacterSelect,
	EInGame,
	EPostGame,
};

// !< 游戏内的GameMode, 如果 有登陆场景界面, 单独弄一个LoginGameMode
// !< 注意 : 只运行于服务器, 所以不需要Replicated啦!!!
UCLASS()
class AUWGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	// !< 所有在商店可以购买的商品信息
	UPROPERTY(EditDefaultsOnly, Category = UW)
		TArray<TSubclassOf<AUWEquipment> > StoreEquipments;
};
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

// !< ��Ϸ�ڵ�GameMode, ��� �е�½��������, ����Ūһ��LoginGameMode
// !< ע�� : ֻ�����ڷ�����, ���Բ���ҪReplicated��!!!
UCLASS()
class AUWGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	// !< �������̵���Թ������Ʒ��Ϣ
	UPROPERTY(EditDefaultsOnly, Category = UW)
		TArray<TSubclassOf<AUWEquipment> > StoreEquipments;
};
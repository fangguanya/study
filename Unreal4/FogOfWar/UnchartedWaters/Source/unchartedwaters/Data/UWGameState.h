#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWGameState
// !< Date : 2/27/2017 12:03:42 PM
// !< Author : fanggang

#include "GameFramework/GameState.h"
#include "UWGameState.generated.h"

// !< TODO : 如果有聊天相关, 也可以放在这里!!!
UCLASS()
class AUWGameState : AGameState
{
	GENERATED_UCLASS_BODY()

protected:
	// Make sure every client begins at same time.
	UPROPERTY(Replicated)
		float StartTime;
	// 每个队伍的击杀数信息(详情还是要查看每一个PlayerState了)
	UPROPERTY(Replicated)
		TArray<int32> TeamKills;

public:
	UFUNCTION(BlueprintCallable, Category = UW)
		float GetStartTime() const;
	UFUNCTION(BlueprintCallable, Category = UW)
		float GetLeftTime() const;
	UFUNCTION(BlueprintCallable, Category = UW)
		float GetElapseTime() const;
	UFUNCTION(BlueprintCallable, Category = UW)
		int32 GetTeamKills(int32 TeamIndex) const;

public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
};
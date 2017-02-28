#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWGameState
// !< Date : 2/27/2017 12:03:42 PM
// !< Author : fanggang

#include "GameFramework/GameState.h"
#include "UWGameState.generated.h"

// !< TODO : ������������, Ҳ���Է�������!!!
UCLASS()
class AUWGameState : AGameState
{
	GENERATED_UCLASS_BODY()

protected:
	// Make sure every client begins at same time.
	UPROPERTY(Replicated)
		float StartTime;
	// ÿ������Ļ�ɱ����Ϣ(���黹��Ҫ�鿴ÿһ��PlayerState��)
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
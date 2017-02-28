#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWPlayerState
// !< Date : 2/27/2017 12:03:42 PM
// !< Author : fanggang

#include "GameFramework/PlayerState.h"
#include "UWPlayerState.generated.h"

UCLASS()
class AUWPlayerState : APlayerState
{
	GENERATED_UCLASS_BODY()

protected:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = UW)
		int32 TeamIndex;
	UPROPERTY(Replicated, BlueprintReadOnly, Category = UW)
		int32 TeamPlayerIndex;
	UPROPERTY(Replicated, BlueprintReadOnly, Category = UW)
		int32 SelectedTemplateID;

public:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = UW)
		int32 Kills;
	UPROPERTY(Replicated, BlueprintReadOnly, Category = UW)
		int32 Deaths;
	UPROPERTY(Replicated, BlueprintReadOnly, Category = UW)
		int32 Assists;
	UPROPERTY(Replicated, BlueprintReadOnly, Category = UW)
		int32 IncomeCoin;
	// TODO : 添加其他相关的玩家相关属性

public:
	UFUNCTION(BlueprintCallable, Category = UW)
		int32 GetTeamIndex() const;
	UFUNCTION(BlueprintCallable, Category = UW)
		void SetTeamIndex(int32 InIndex);
	UFUNCTION(BlueprintCallable, Category = UW)
		int32 GetTeamPlayerIndex() const;
	UFUNCTION(BlueprintCallable, Category = UW)
		void SetTeamPlayerIndex(int32 InIndex);
	UFUNCTION(BlueprintCallable, Category = UW)
		int32 GetTemplateID() const;
	UFUNCTION(BlueprintCallable, Category = UW)
		void SetTemplateID(int32 InIndex);

public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

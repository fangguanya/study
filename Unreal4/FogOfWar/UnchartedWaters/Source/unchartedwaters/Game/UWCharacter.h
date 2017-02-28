#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWCharacter
// !< Date : 2/28/2017 10:44:57 AM
// !< Author : fanggang

#include "UWCharacter.generated.h"

UENUM()
enum class ECharacterType : uint8
{
	ECHARTYPE_PLAYER UMETA(DisplayName = "Player"),
	ECHARTYPE_BOT UMETA(DisplayName = "Bot"),

	// !< 可以增加更多类型
};

UCLASS(ABSTRACT)
class AUWCharacter : public APawn
{
	GENERATED_UCLASS_BODY()

protected:
	UPROPERTY(replicated, VisibleAnywhere, BlueprintReadOnly, Category = "UW")
		ECharacterType CharType;

public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
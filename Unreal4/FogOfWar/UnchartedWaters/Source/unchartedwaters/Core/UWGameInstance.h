#pragma once
// !< All right is reserved by HW-Storm Game Studio, Even not mentioned clearly with signature.
// !< This is not a free ware, Please do-not copy it outside of HW-Storm Game Studio
// !< File : UWGameInstance
// !< Date : 2/27/2017 12:08:01 PM
// !< Author : fanggang

#include "UWGameInstance.generated.h"

// �����������һЩ��Ϣ, ����LOL��������������ʾ�Ķ�������ĳ��ս���޹ص�����.(��Ӧ��������, ��ֵ����ʯ������!)
UCLASS()
class UWGameInstance : UGameInstance
{
	GENERATED_UCLASS_BODY()

protected:
	// ��ǰ��¼�����ID
	UPROPERTY(BlueprintReadOnly, Category = UW)
		FString CurrentUserID;
	// ��ǰ��¼���������(UI��ʾ��)
	UPROPERTY(BlueprintReadOnly, Category = UW)
		FString CurrentUserName;

	// !< TODO1 : ������Ϸ���ӵ�½���������߼�, �����������Եȵ�, ��������Ϸ������(����ƥ����߽������)��ַ
	// !< TODO2 : ������Ϸ������ƥ���߼�.


public:
	~UWGameInstance();

	UFUNCTION(BlueprintCallable, Category = UW)
		void CloseGame();
};
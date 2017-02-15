// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HFogOfWarControler.generated.h"

UCLASS()
class FOGOFWAR_API AHFogOfWarControler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHFogOfWarControler();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable)
		void UpdatePlayerPosition(const FVector& pos);
	
public:
	// !< ͬ��ͼ���Դ�
	void SyncTextureContents();
	// !< ��ʼ����Դ
	void InitTextureResource();

private:
	// Should sync to global-material-parameter-collections.
	UPROPERTY(VisibleAnywhere, Category = "FOW")
		FVector WorldMinPosition;
	UPROPERTY(VisibleAnywhere, Category = "FOW")
		FVector WorldMaxPosition;
	UPROPERTY(EditAnywhere, Category = "FOW")
		int32 TextureWidth;
	UPROPERTY(EditAnywhere, Category = "FOW")
		int32 TextureHeight;

	float ScaleX;
	float ScaleY;
	
	// Format : G8 (�Ҷ�ͼ)
	UPROPERTY(VisibleAnywhere, Category = "FOW")
		UTexture2D* DynamicTexture;
	UPROPERTY()
		TArray<uint8> DynamicTexturePixels;

	// Format : G8 (����Ŀ�������ͼ)
	UPROPERTY(EditAnywhere, Category = "FOW")
		UTexture2D* PointTexture;
	UPROPERTY(EditAnywhere, Category = "FOW")
		float PointTextureScale;
	int32 PointTextureWidth;
	int32 PointTextureHeight;
	UPROPERTY()
		TArray<uint8> PointTexturePixels;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HFogOfWarControler.generated.h"

UCLASS(BlueprintType, Blueprintable)
class UNCHARTEDWATERS_API AHFogOfWarControler : public AActor
{
	GENERATED_BODY()
	
public:	
	AHFogOfWarControler();

	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "FOW")
		void RegisterActor(AActor* Actor);
	// Only do circle check.
	UFUNCTION(BlueprintCallable, Category = "FOW")
		bool IsPositionVisible(const FVector& pos);
		
	void UpdatePlayerPosition(const FVector& pos);
	
public:
	// !< 同步图形显存
	void SyncTextureContents();
	// !< 更新场景大小
	void LoadWorldSettings();
	// !< 初始化资源
	void InitTextureResource();
	// !< 重置资源
	void ResetTextureResource();

protected:
	// Update interval
	UPROPERTY(EditAnywhere, Category = "FOW")
		float UpdateIntervalTime;
	// All synced actors
	UPROPERTY(VisibleAnywhere, Category = "FOW")
		TArray<AActor*> Actors;
	// Should sync to global-material-parameter-collections.
	UPROPERTY(VisibleAnywhere, Category = "FOW")
		FBox WorldBounds;
	UPROPERTY(EditAnywhere, Category = "FOW")
		FVector WorldMin;
	UPROPERTY(EditAnywhere, Category = "FOW")
		FVector WorldMax;
	// Actor view distances
	UPROPERTY(EditAnywhere, Category = "FOW")
		float ActorVisibleUnit;
	UPROPERTY(EditAnywhere, Category = "FOW")
		int32 TextureSize;

	float TexelPerWorldUnit;
	float LastUpdateTime;
	
	// Format : G8 (灰度图)
	UPROPERTY()
		TArray<uint8> PassedDynamicTexturePixels;
	UPROPERTY()
		TArray<uint8> DynamicTexturePixels;
	UPROPERTY()
		TArray<uint8> LastDynamicTexturePixels;

	UPROPERTY(VisibleAnywhere, Category = "FOW")
		UTexture2D* DynamicTexture;
	UPROPERTY(VisibleAnywhere, Category = "FOW")
		UTexture2D* LastDynamicTexture;
};

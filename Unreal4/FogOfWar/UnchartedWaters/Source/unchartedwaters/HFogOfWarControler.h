// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HFogOfWarThread.h"
#include "HFogOfWarControler.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFOWController, Log, Log);

UCLASS(BlueprintType, Blueprintable)
class UNCHARTEDWATERS_API AHFogOfWarControler : public AActor
{
	GENERATED_BODY()
	
public:	
	AHFogOfWarControler();
	~AHFogOfWarControler();

	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	virtual void PostLoad() override;
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "FOW")
		void RegisterActor(AActor* Actor);
	UFUNCTION(BlueprintCallable, Category = "FOW")
		void RegisterTracker(AActor* Actor);
	UFUNCTION(BlueprintCallable, Category = "FOW")
		void RemoveActor(AActor* Actor);
	UFUNCTION(BlueprintCallable, Category = "FOW")
		void RemoveTracker(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "FOW")
		bool IsPositionVisible(const FVector& pos);
	
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
	// All synced actors
	UPROPERTY(VisibleAnywhere, Category = "FOW")
		TArray<AActor*> Actors;
	UPROPERTY(VisibleAnywhere, Category = "FOW")
		TArray<AActor*> Trackers;
	UPROPERTY(VisibleAnywhere, Category = "FOW")
		TArray<uint32> RemovedActors;
	UPROPERTY(VisibleAnywhere, Category = "FOW")
		TArray<uint32> RemovedTrackers;

	// Should sync to global-material-parameter-collections.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FOW")
		FBox WorldBounds;
	UPROPERTY(EditAnywhere, Category = "FOW")
		FVector WorldMin;
	UPROPERTY(EditAnywhere, Category = "FOW")
		FVector WorldMax;
	// Actor view distances
	UPROPERTY(EditAnywhere, Category = "FOW")
		float ActorVisibleUnit;
	// Actor view blur distance
	UPROPERTY(EditAnywhere, Category = "FOW")
		float ActorVisibleBlurDistance;
	UPROPERTY(EditAnywhere, Category = "FOW")
		float FOVBias;
	UPROPERTY(EditAnywhere, Category = "FOW")
		bool EnableBlur;
	UPROPERTY(EditAnywhere, Category = "FOW")
		int16 TextureSize;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FOW")
		float BlendDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FOW")
		float BlendAlpha;
	
	// Format : G8 (灰度图)
	UPROPERTY()
		TArray<uint8> DynamicTexturePixels;
	UPROPERTY()
		TArray<uint8> LastDynamicTexturePixels;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FOW")
		UTexture2D* DynamicTexture;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FOW")
		UTexture2D* LastDynamicTexture;
	
protected:
	float BlendStartTime;
	float TexelPerWorldUnit;
	float WorldUnitPerTexel;
	AHFogOfWarThread* Worker;
};

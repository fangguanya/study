// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"

struct UNCHARTEDWATERS_API FHFogOfWarParam
{
	FBox WorldBounds;
	float WorldVisibleRadius;
	float TexelVisibleRadius;
	float WorldBlurRadius;
	float TexelBlurRadius;
	int16 TextureSize;
	float TexelPerWorldUnit;
	float WorldUnitPerTexel;
	float FOVBias;
	bool EnableBlur;
};

struct UNCHARTEDWATERS_API FHFogOfWarTrackingActor
{
	FVector Position;
	TArray<uint8> PassedPixels;
};

// !< 计算FOW阴影区域的线程.
class UNCHARTEDWATERS_API AHFogOfWarThread : public FRunnable
{
protected:
	// !< 线程对象
	FRunnableThread* Thread;
	// !< 停止线程控制
	FThreadSafeCounter StopFlag;
	// !< 所执行碰撞检测的世界
	UWorld* World;
protected:
	bool bWorkFinished;
	bool bUseThread;

public:
	AHFogOfWarThread(UWorld* InWorld, bool InThreaded);
	virtual ~AHFogOfWarThread();

	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();

	void Startup();
	bool IsCalculateFinished();
	void ReCalculate();
	void Shutdown();

	void SetParam(const FHFogOfWarParam& other);
	void SetPlayerActorPosition(uint32 UniqueID, const FVector& Pos);
	void SetTrackActorPosition(uint32 UniqueID, const FVector& Pos);
	void RemovePlayerActor(uint32 UniqueID);
	void RemoveTrackActor(uint32 UniqueID);

	TArray<uint8>& GetFinalPixels() { return FinalPixels; }
	float LastCalculationTime;

protected:
	void UpdateFogTexture();
	void UpdatePlayer(const FVector& Pos);
	void UpdateTracker(FHFogOfWarTrackingActor& Tracker);
	void UpdateFOVPosition(TArray<uint8>& pixels, const FVector& pos, FVector2D texel, const FVector& pos0, FVector2D texel0);
	void Intergrate();

	// !< Blur
	void AddPlayerActorBlurPixel(int16 x, int16 y);

protected:
	// !< 参数
	FHFogOfWarParam FOWParam;

	// !< 1. 当前需要计算的所有世界坐标位置(需要计算FOV, Circle等)
	TMap<uint32, FVector> PlayerActors;
	// !< 2. 当前需要计算行走区域的世界坐标位置(需要计算轨迹, Circle等)
	TMap<uint32, FHFogOfWarTrackingActor> TrackActors;

	// !< 贴图数据(G8灰度图)
	// !< 1. 所有'PlayerActors'的实时可见区域计算
	TArray<uint8> PlayerActorsPixel;
	// !< 2. 合并最终输出的贴图
	TArray<uint8> FinalPixels;
	// !< 待模糊数据
	// !< 1. 所有'PlayerActors'的需要模糊的区域
	TSet<int32> PlayerActorsBlurPoints;
	TArray<uint8> PlayerActorsHorizontalBlurPixels;
};

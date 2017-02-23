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
	int32 TextureSize;
	float TexelPerWorldUnit;
	float WorldUnitPerTexel;
};

struct UNCHARTEDWATERS_API FHFogOfWarTrackingActor
{
	FVector Position;
	TArray<uint8> PassedPixels;
};

// !< ����FOW��Ӱ������߳�.
class UNCHARTEDWATERS_API AHFogOfWarThread : public FRunnable
{
protected:
	// !< �̶߳���
	FRunnableThread* Thread;
	// !< ֹͣ�߳̿���
	FThreadSafeCounter StopFlag;
	// !< ��ִ����ײ��������
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

protected:
	// !< ����
	FHFogOfWarParam FOWParam;

	// !< 1. ��ǰ��Ҫ�����������������λ��(��Ҫ����FOV, Circle��)
	TMap<uint32, FVector> PlayerActors;
	// !< 2. ��ǰ��Ҫ���������������������λ��(��Ҫ����켣, Circle��)
	TMap<uint32, FHFogOfWarTrackingActor> TrackActors;

	// !< ��ͼ����(G8�Ҷ�ͼ)
	// !< 1. ����'PlayerActors'��ʵʱ�ɼ��������
	TArray<uint8> PlayerActorsPixel;
	// !< 3. �ϲ������������ͼ
	TArray<uint8> FinalPixels;
};

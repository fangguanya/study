// Fill out your copyright notice in the Description page of Project Settings.

#include "unchartedwaters.h"
#include "HFogOfWarThread.h"

const uint8 VIEW_VALUE = 255;
const uint8 FOG_VALUE = 0;
const uint8 PASS_VALUE = 100;
const float BLUR_COEFFICIENT[] = { 0.000489f, 0.002403f, 0.009246f, 0.02784f, 0.065602f, 0.120999f, 0.174697f, 0.197448f, 0.174697f, 0.120999f, 0.065602f, 0.02784f, 0.009246f, 0.002403f, 0.000489f };
const int8 BLUR_COEFFICIENT_HALFCOUNT = ARRAY_COUNT(BLUR_COEFFICIENT) / 2;

AHFogOfWarThread::AHFogOfWarThread(UWorld* InWorld, bool InThreaded)
	: Thread(nullptr),
	bWorkFinished(false),
	bUseThread(InThreaded),
	World(InWorld)
{
	LastCalculationTime = 0.f;
}
AHFogOfWarThread::~AHFogOfWarThread()
{
	if (Thread)
	{
		delete Thread;
		Thread = nullptr;
	}
}
void AHFogOfWarThread::Shutdown()
{
	Stop();
	if (Thread)
	{
		Thread->WaitForCompletion();
	}
}
bool AHFogOfWarThread::IsCalculateFinished()
{
	if (!bUseThread)
	{
		UpdateFogTexture();
	}
	return bWorkFinished;
}
void AHFogOfWarThread::ReCalculate()
{
	bWorkFinished = false;
}
void AHFogOfWarThread::Startup()
{
	if (!Thread && bUseThread)
	{
		Thread = FRunnableThread::Create(this, TEXT("AHFOGOFWARTHREAD"), 0U, TPri_BelowNormal);
	}
}
bool AHFogOfWarThread::Init()
{
	return true;
}
uint32 AHFogOfWarThread::Run()
{
	if (!bUseThread)
	{
		return 0;
	}
	FPlatformProcess::Sleep(0.01f);
	while (StopFlag.GetValue() == 0)
	{
		UpdateFogTexture();
		FPlatformProcess::Sleep(0.01f);
	}
	return 0;
}
void AHFogOfWarThread::Stop()
{
	StopFlag.Increment();
}

void AHFogOfWarThread::SetParam(const FHFogOfWarParam& other)
{
	FOWParam.WorldBounds = other.WorldBounds;
	FOWParam.WorldVisibleRadius = other.WorldVisibleRadius;
	FOWParam.TexelVisibleRadius = other.TexelVisibleRadius;
	FOWParam.WorldBlurRadius = other.WorldBlurRadius;
	FOWParam.TexelBlurRadius = other.TexelBlurRadius;
	FOWParam.TextureSize = other.TextureSize;
	FOWParam.TexelPerWorldUnit = other.TexelPerWorldUnit;
	FOWParam.WorldUnitPerTexel = other.WorldUnitPerTexel;
	FOWParam.FOVBias = other.FOVBias;
	FOWParam.EnableBlur = other.EnableBlur;

	PlayerActorsPixel.Init(FOG_VALUE, FOWParam.TextureSize * FOWParam.TextureSize);
	PlayerActorsBlurPoints.Empty(FOWParam.TextureSize * FOWParam.TextureSize);
	PlayerActorsHorizontalBlurPixels.Init(FOG_VALUE, FOWParam.TextureSize * FOWParam.TextureSize);
	FinalPixels.Init(FOG_VALUE, FOWParam.TextureSize * FOWParam.TextureSize);
}
void AHFogOfWarThread::SetPlayerActorPosition(uint32 UniqueID, const FVector& Pos)
{
	FVector* Saved = PlayerActors.Find(UniqueID);
	if (Saved)
	{
		*Saved = Pos;
	}
	else
	{
		PlayerActors.Add(UniqueID, Pos);
	}
}
void AHFogOfWarThread::SetTrackActorPosition(uint32 UniqueID, const FVector& Pos)
{
	FHFogOfWarTrackingActor* Saved = TrackActors.Find(UniqueID);
	if (Saved)
	{
		Saved->Position = Pos;
	}
	else
	{
		FHFogOfWarTrackingActor Tracker;
		Tracker.Position = Pos;
		Tracker.PassedPixels.Init(FOG_VALUE, FOWParam.TextureSize * FOWParam.TextureSize);
		TrackActors.Emplace(UniqueID, Tracker);
	}
}
void AHFogOfWarThread::RemovePlayerActor(uint32 UniqueID)
{
	PlayerActors.Remove(UniqueID);
}
void AHFogOfWarThread::RemoveTrackActor(uint32 UniqueID)
{
	TrackActors.Remove(UniqueID);
}

void AHFogOfWarThread::AddPlayerActorBlurPixel(int16 x, int16 y)
{
	int32 Value = (x << 16) | y;
	if (!PlayerActorsBlurPoints.Contains(Value))
	{
		PlayerActorsBlurPoints.Add(Value);
	}
}

void AHFogOfWarThread::UpdateFogTexture()
{
	if (!bWorkFinished)
	{
		float Start = World->TimeSeconds;
		PlayerActorsPixel.Init(FOG_VALUE, FOWParam.TextureSize * FOWParam.TextureSize);
		PlayerActorsBlurPoints.Empty(FOWParam.TextureSize * FOWParam.TextureSize);
		for (auto Iter : PlayerActors)
		{
			FVector& Pos = Iter.Value;
			UpdatePlayer(Pos);
		}
		for (auto Iter : TrackActors)
		{
			FHFogOfWarTrackingActor& Tracker = Iter.Value;
			UpdateTracker(Tracker);
		}
		Intergrate();
		bWorkFinished = true;
		LastCalculationTime = World->TimeSince(Start);
	}
}

void AHFogOfWarThread::UpdatePlayer(const FVector& Pos)
{
	// !< WARN : 目前简单的根据左下角00, 右上角11来算
	FVector texel3D = (Pos - FOWParam.WorldBounds.Min) * FOWParam.TexelPerWorldUnit;
	FVector2D texel = FVector2D(texel3D.X, texel3D.Y);

	// !< 纹理空间的可视区域
	float minXFlt = texel.X - FOWParam.TexelVisibleRadius;
	float minYFlt = texel.Y - FOWParam.TexelVisibleRadius;
	float maxXFlt = texel.X + FOWParam.TexelVisibleRadius;
	float maxYFlt = texel.Y + FOWParam.TexelVisibleRadius;
	int16 minX = FMath::Clamp<int16>(minXFlt, 0, FOWParam.TextureSize - 1);
	int16 minY = FMath::Clamp<int16>(minYFlt, 0, FOWParam.TextureSize - 1);
	int16 maxX = FMath::Clamp<int16>(maxXFlt, 0, FOWParam.TextureSize - 1);
	int16 maxY = FMath::Clamp<int16>(maxYFlt, 0, FOWParam.TextureSize - 1);

	// !< 进行碰撞检测
	/*
	++++++++
	+------+
	+------+
	+------+
	+------+
	+------+
	+------+
	++++++++
	只用从两条边发射射线进行检测就行, 复杂度为2*(m+n).
	*/
	for (float x = minXFlt - 1; x < maxXFlt + 1; x += 1)
	{
		UpdateFOVPosition(PlayerActorsPixel, Pos, texel, FVector(x * FOWParam.WorldUnitPerTexel + FOWParam.WorldBounds.Min.X, minYFlt * FOWParam.WorldUnitPerTexel + FOWParam.WorldBounds.Min.Y, Pos.Z), FVector2D(x, minYFlt));
		UpdateFOVPosition(PlayerActorsPixel, Pos, texel, FVector((maxXFlt - x + minXFlt) * FOWParam.WorldUnitPerTexel + FOWParam.WorldBounds.Min.X, maxYFlt * FOWParam.WorldUnitPerTexel + FOWParam.WorldBounds.Min.Y, Pos.Z), FVector2D(maxXFlt - x + minXFlt, maxYFlt));
	}
	for (float y = minYFlt - 1; y < maxYFlt + 1; y += 1)
	{
		UpdateFOVPosition(PlayerActorsPixel, Pos, texel, FVector(minXFlt * FOWParam.WorldUnitPerTexel + FOWParam.WorldBounds.Min.X, y * FOWParam.WorldUnitPerTexel + FOWParam.WorldBounds.Min.Y, Pos.Z), FVector2D(minXFlt, y));
		UpdateFOVPosition(PlayerActorsPixel, Pos, texel, FVector(maxXFlt * FOWParam.WorldUnitPerTexel + FOWParam.WorldBounds.Min.X, (maxYFlt - y + minYFlt) * FOWParam.WorldUnitPerTexel + FOWParam.WorldBounds.Min.Y, Pos.Z), FVector2D(maxXFlt, maxYFlt - y + minYFlt));
	}
}
void AHFogOfWarThread::UpdateTracker(FHFogOfWarTrackingActor& Tracker)
{
	// !< WARN : 目前简单的根据左下角00, 右上角11来算
	FVector texel3D = (Tracker.Position - FOWParam.WorldBounds.Min) * FOWParam.TexelPerWorldUnit;
	FVector2D texel = FVector2D(texel3D.X, texel3D.Y);

	// !< 纹理空间的可视区域
	float texelRadius = FOWParam.TexelVisibleRadius;

	float minXFlt = texel.X - texelRadius;
	float minYFlt = texel.Y - texelRadius;
	float maxXFlt = texel.X + texelRadius;
	float maxYFlt = texel.Y + texelRadius;
	int16 minX = FMath::Clamp<int16>(minXFlt, 0, FOWParam.TextureSize - 1);
	int16 minY = FMath::Clamp<int16>(minYFlt, 0, FOWParam.TextureSize - 1);
	int16 maxX = FMath::Clamp<int16>(maxXFlt, 0, FOWParam.TextureSize - 1);
	int16 maxY = FMath::Clamp<int16>(maxYFlt, 0, FOWParam.TextureSize - 1);

	// !< PassedDynamicTexturePixels 记录已经走过(探过)的区域
	for (int16 x = minX; x < maxX; ++x)
	{
		for (int y = minY; y < maxY; ++y)
		{
			float distance = FVector2D::Distance(texel, FVector2D(x, y));
			if (distance < texelRadius)
			{
				Tracker.PassedPixels[y * FOWParam.TextureSize + x] = PASS_VALUE;
			}
		}
	}
}
void AHFogOfWarThread::UpdateFOVPosition(TArray<uint8>& pixels, const FVector& pos, FVector2D texel, const FVector& pos0, FVector2D texel0)
{
	static FCollisionQueryParams fowQueryParams(FName(TEXT("FOW-TRACE")), false);
	static FCollisionObjectQueryParams fowObjectQueryParams(ECollisionChannel::ECC_WorldStatic);

	FHitResult Hit;
	FVector HitDeltaPosition(FLT_MAX, FLT_MAX, pos.Z);
	FVector Normal = pos0 - pos;
	Normal.Normalize();
	if (World->LineTraceSingleByObjectType(Hit, pos, pos0, fowObjectQueryParams, fowQueryParams))
	{
		HitDeltaPosition = Hit.ImpactPoint - pos + FOWParam.FOVBias * Normal;
	}

	bool iterThroughX = true;
	float iterFlag = 1;
	FVector2D texelDelta = texel0 - texel;
	iterFlag = texelDelta.X < 0 ? -1 : 1;
	if (FMath::Abs(texelDelta.Y) > FMath::Abs(texelDelta.X))
	{
		iterThroughX = false;
		iterFlag = texelDelta.Y < 0 ? -1 : 1;
	}

	FVector testPos(ForceInitToZero);
	FVector2D testTexel = texel;
	float texelIncrement = iterFlag * (iterThroughX ? (texel0.Y - texel.Y) / (texel0.X - texel.X) : (texel0.X - texel.X) / (texel0.Y - texel.Y));
	float posIncrement = texelIncrement * FOWParam.WorldUnitPerTexel;
	while (true)
	{
		int16 x = FMath::Clamp<int16>(FMath::RoundToInt(testTexel.X), 0, FOWParam.TextureSize - 1);
		int16 y = FMath::Clamp<int16>(FMath::RoundToInt(testTexel.Y), 0, FOWParam.TextureSize - 1);

		if (iterThroughX)
		{
			bool IsShadow = FMath::Abs(testPos.X) >= FMath::Abs(HitDeltaPosition.X);
			if (!IsShadow && FVector2D::Distance(texel, FVector2D(x, y)) <= FOWParam.TexelVisibleRadius)
			{
				pixels[y * FOWParam.TextureSize + x] = VIEW_VALUE;
				AddPlayerActorBlurPixel(x, y);
			}

			testPos.X += iterFlag * FOWParam.WorldUnitPerTexel;
			testTexel.X += iterFlag;
			testPos.Y += posIncrement;
			testTexel.Y += texelIncrement;
			if (testTexel.X * iterFlag > texel0.X * iterFlag)
			{
				break;
			}
		}
		else
		{
			bool IsShadow = FMath::Abs(testPos.Y) >= FMath::Abs(HitDeltaPosition.Y);
			if (!IsShadow && FVector2D::Distance(texel, FVector2D(x, y)) <= FOWParam.TexelVisibleRadius)
			{
				pixels[y * FOWParam.TextureSize + x] = VIEW_VALUE;
				AddPlayerActorBlurPixel(x, y);
			}

			testPos.Y += iterFlag * FOWParam.WorldUnitPerTexel;
			testTexel.Y += iterFlag;
			testPos.X += posIncrement;
			testTexel.X += texelIncrement;
			if (testTexel.Y * iterFlag > texel0.Y * iterFlag)
			{
				break;
			}
		}
	}
}
void AHFogOfWarThread::Intergrate()
{
	// !< 1. 对可见区域(不包含特殊道具)模糊处理
	if (FOWParam.EnableBlur)
	{
		for (int32 Point : PlayerActorsBlurPoints)
		{
			int16 x = Point >> 16;
			int16 y = Point & 0xFFFFFFFFFFFFFFFF;
			float sum = 0;
			for (int16 i = 0; i < ARRAY_COUNT(BLUR_COEFFICIENT); ++i)
			{
				int16 PixelIndex = x + i - BLUR_COEFFICIENT_HALFCOUNT;
				if (PixelIndex >= 0 && PixelIndex < FOWParam.TextureSize)
				{
					sum += PlayerActorsPixel[y * FOWParam.TextureSize + PixelIndex] * BLUR_COEFFICIENT[i];
				}
			}
			PlayerActorsHorizontalBlurPixels[y * FOWParam.TextureSize + x] = sum;
		}

		for (int32 Point : PlayerActorsBlurPoints)
		{
			int16 x = Point >> 16;
			int16 y = Point & 0xFFFFFFFFFFFFFFFF;
			float sum = 0;
			for (int16 i = 0; i < ARRAY_COUNT(BLUR_COEFFICIENT); ++i)
			{
				int16 PixelIndex = y + i - BLUR_COEFFICIENT_HALFCOUNT;
				if (PixelIndex >= 0 && PixelIndex < FOWParam.TextureSize)
				{
					sum += PlayerActorsHorizontalBlurPixels[PixelIndex * FOWParam.TextureSize + x] * BLUR_COEFFICIENT[i];
				}
			}
			PlayerActorsPixel[y * FOWParam.TextureSize + x] = sum;
		}
	}
	
	// !< 2. 输出到最终贴图
	FinalPixels = TArray<uint8>(PlayerActorsPixel);

	//for (int x = 0; x < FOWParam.TextureSize; ++x)
	//{
	//	for (int y = 0; y < FOWParam.TextureSize; ++y)
	//	{
	//		int32 Index = y * FOWParam.TextureSize + x;
	//		int8 Value = PlayerActorsPixel[Index];
	//		for (auto Iter : TrackActors)
	//		{
	//			FHFogOfWarTrackingActor& Tracker = Iter.Value;
	//			Value = FMath::Clamp(Value + Tracker.PassedPixels[Index], 0, 255);
	//		}
	//		FinalPixels[Index] = Value;
	//	}
	//}
}
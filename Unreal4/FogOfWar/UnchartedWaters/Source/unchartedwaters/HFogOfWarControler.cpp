// Fill out your copyright notice in the Description page of Project Settings.

#include "unchartedwaters.h"
#include "HFogOfWarControler.h"

const uint8 VIEW_VALUE = 255;
const uint8 FOG_VALUE = 0;
const uint8 PASS_VALUE = 100;

DEFINE_LOG_CATEGORY(LogFOWController);

// Sets default values 
AHFogOfWarControler::AHFogOfWarControler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Worker = nullptr;
	TextureSize = 512;
	BlendDuration = 1.0f;
	FOVBias = 1.0f;
}

AHFogOfWarControler::~AHFogOfWarControler()
{
	if (Worker)
	{
		Worker->Shutdown();
		delete Worker;
	}
	Worker = nullptr;
}

void AHFogOfWarControler::BeginDestroy()
{
	Super::BeginDestroy();

	if (Worker)
	{
		Worker->Shutdown();
		delete Worker;
	}
	Worker = nullptr;
}

// Called when the game starts or when spawned
void AHFogOfWarControler::BeginPlay()
{
	Super::BeginPlay();

	Worker = new AHFogOfWarThread(GetWorld(), true);

	FHFogOfWarParam Param;
	Param.TexelBlurRadius = ActorVisibleBlurDistance * TexelPerWorldUnit;
	Param.TexelPerWorldUnit = TexelPerWorldUnit;
	Param.TexelVisibleRadius = ActorVisibleUnit * TexelPerWorldUnit;
	Param.TextureSize = TextureSize;
	Param.WorldBlurRadius = ActorVisibleBlurDistance;
	Param.WorldBounds = WorldBounds;
	Param.WorldUnitPerTexel = WorldUnitPerTexel;
	Param.WorldVisibleRadius = ActorVisibleUnit;
	Param.FOVBias = FOVBias;
	Param.EnableBlur = EnableBlur;
	Worker->SetParam(Param);
	Worker->Startup();

	SyncTextureContents();
}

void AHFogOfWarControler::PostLoad()
{
	Super::PostLoad();

	InitTextureResource();
	LoadWorldSettings();
}

void AHFogOfWarControler::LoadWorldSettings()
{
	WorldBounds.Init();

	// !< Ver 2
	FVector TempMax = WorldMax;
	FVector TempDist = WorldMax - WorldMin;
	TempDist.X = FMath::Max(TempDist.X, TempDist.Y);
	TempDist.Y = FMath::Max(TempDist.X, TempDist.Y);
	TempMax = WorldMin + TempDist;
	WorldBounds = FBox(WorldMin, TempMax);
	// !< Ver 1 TODO : 是否可以搞成自动读取?(但是场景一些对象不需要比如SkyBox等比较坑爹)
	//UWorld *World = GetWorld(); 
	//for (ULevel* Level : World->GetLevels())
	//{
	//	if (Level->bIsVisible)
	//	{
	//		// !< TODO : 修改为使用LevelBoundsActor来进行处理
	//		//FVector LevelCenter = Level->LevelBoundsActor->GetActorLocation();
	//		//FVector LevelSize = Level->LevelBoundsActor->GetActorScale3D();
	//		//FBox LevelBounds(LevelCenter - LevelSize * 0.5, LevelCenter + LevelSize * 0.5);
	//		FBox LevelBounds = FBox(0);
	//		for (int32 ActorIndex = 0; ActorIndex < Level->Actors.Num(); ++ActorIndex)
	//		{
	//			AActor* Actor = Level->Actors[ActorIndex];
	//			if (Actor && Actor->IsLevelBoundsRelevant()) 
	//			{
	//				// Sum up components bounding boxes
	//				FBox ActorBox = Actor->GetComponentsBoundingBox(true);
	//				if (ActorBox.IsValid)
	//				{
	//					LevelBounds += ActorBox;
	//				}
	//			}
	//		}

	//		WorldBounds += LevelBounds;
	//	}
	//}

	// !< WARN : 目前简单默认世界地图包围盒为正方形.
	ensureMsgf(WorldBounds.GetExtent().X - WorldBounds.GetExtent().Y <= FLT_EPSILON, TEXT("World bounds must be SQUARE! current X=%.2f, Y=%.2f"), WorldBounds.GetExtent().X ,WorldBounds.GetExtent().Y);

	TexelPerWorldUnit = (float)TextureSize / WorldBounds.GetSize().X;
	WorldUnitPerTexel = (float)WorldBounds.GetSize().X / TextureSize;
}

void AHFogOfWarControler::ResetTextureResource()
{
	DynamicTexturePixels.Init(FOG_VALUE, TextureSize * TextureSize);
	LastDynamicTexturePixels.Init(FOG_VALUE, TextureSize * TextureSize);
}

void AHFogOfWarControler::InitTextureResource()
{
	DynamicTexture = UTexture2D::CreateTransient(TextureSize, TextureSize, PF_G8);
	DynamicTexture->CompressionSettings = TextureCompressionSettings::TC_Grayscale;
	DynamicTexture->SRGB = 0;
#if WITH_EDITOR
	DynamicTexture->MipGenSettings = TMGS_NoMipmaps;
#endif
	DynamicTexture->UpdateResource();
	LastDynamicTexture = UTexture2D::CreateTransient(TextureSize, TextureSize, PF_G8);
	LastDynamicTexture->CompressionSettings = TextureCompressionSettings::TC_Grayscale;
	LastDynamicTexture->SRGB = 0;
#if WITH_EDITOR
	LastDynamicTexture->MipGenSettings = TMGS_NoMipmaps;
#endif
	LastDynamicTexture->UpdateResource();

	ResetTextureResource();
}

// Called every frame
void AHFogOfWarControler::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	// !< 多线程的模块
	float CurrentTime = GetWorld()->TimeSeconds;
	if (Worker->IsCalculateFinished())
	{
		UE_LOG(LogFOWController, Log, TEXT("FOW Texture update use %.4f seconds"), Worker->LastCalculationTime);
		LastDynamicTexturePixels = TArray<uint8>(DynamicTexturePixels);
		DynamicTexturePixels = TArray<uint8>(Worker->GetFinalPixels());
		BlendStartTime = CurrentTime;

		for (AActor* Actor : Actors)
		{
			Worker->SetPlayerActorPosition(Actor->GetUniqueID(), Actor->GetActorLocation());
		}
		for (AActor* Actor : Trackers)
		{
			Worker->SetTrackActorPosition(Actor->GetUniqueID(), Actor->GetActorLocation());
		}
		for (uint32 id : RemovedActors)
		{
			Worker->RemovePlayerActor(id);
		}
		for (uint32 id : RemovedTrackers)
		{
			Worker->RemoveTrackActor(id);
		}
		RemovedActors.Empty();
		RemovedTrackers.Empty();
		Worker->ReCalculate();
		SyncTextureContents();
	}

	BlendAlpha = FMath::Clamp<float>((CurrentTime - BlendStartTime) / BlendDuration, 0, 1);
}

void AHFogOfWarControler::RegisterActor(AActor* Actor)
{
	Actors.AddUnique(Actor);
}
void AHFogOfWarControler::RegisterTracker(AActor* Actor)
{
	Trackers.AddUnique(Actor);
}
void AHFogOfWarControler::RemoveActor(AActor* Actor)
{
	RemovedActors.AddUnique(Actor->GetUniqueID());
	Actors.Remove(Actor);
}
void AHFogOfWarControler::RemoveTracker(AActor* Actor)
{
	RemovedTrackers.AddUnique(Actor->GetUniqueID());
	Trackers.Remove(Actor);
}

bool AHFogOfWarControler::IsPositionVisible(const FVector& pos)
{
	FVector texel3D = (pos - WorldBounds.Min) * TexelPerWorldUnit;
	FVector2D texel = FVector2D(texel3D.X, texel3D.Y);
	int x = FMath::Clamp<int>(texel.X, 0, TextureSize - 1);
	int y = FMath::Clamp<int>(texel.Y, 0, TextureSize - 1);
	return DynamicTexturePixels[y * TextureSize + x] != FOG_VALUE;
}

void AHFogOfWarControler::SyncTextureContents()
{
	static FUpdateTextureRegion2D WholeTextureRegion(0, 0, 0, 0, TextureSize, TextureSize);
	struct FUpdateTextureSlotData
	{
		FTexture2DResource* Texture2DResource;
		int32 MipIndex;
		FUpdateTextureRegion2D* Region;
		uint32 SrcPitch;
		uint32 SrcBpp;
		uint8* SrcData;
	};
	struct FUpdateTextureRegionData
	{
		TArray<FUpdateTextureSlotData> Slots;
		AHFogOfWarControler *Controller;
	};
	FUpdateTextureRegionData* RegionData = new FUpdateTextureRegionData;
	FUpdateTextureSlotData Slot;
	Slot.Texture2DResource = (FTexture2DResource*)DynamicTexture->Resource;
	Slot.MipIndex = 0;
	Slot.Region = &WholeTextureRegion;
	Slot.SrcPitch = TextureSize;
	Slot.SrcBpp = 1;
	Slot.SrcData = DynamicTexturePixels.GetData();
	RegionData->Slots.Emplace(Slot);

	FUpdateTextureSlotData Slot0;
	Slot0.Texture2DResource = (FTexture2DResource*)LastDynamicTexture->Resource;
	Slot0.MipIndex = 0;
	Slot0.Region = &WholeTextureRegion;
	Slot0.SrcPitch = TextureSize;
	Slot0.SrcBpp = 1;
	Slot0.SrcData = LastDynamicTexturePixels.GetData();
	RegionData->Slots.Emplace(Slot0);

	RegionData->Controller = this;

	ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER(
		SyncTextureContents,
		FUpdateTextureRegionData*, RegionData, RegionData,
		{
			for (FUpdateTextureSlotData& Slot : RegionData->Slots)
			{
				int32 CurrentFirstMip = Slot.Texture2DResource->GetCurrentFirstMip();
				if (Slot.MipIndex >= CurrentFirstMip)
				{
					RHIUpdateTexture2D(
						Slot.Texture2DResource->GetTexture2DRHI(),
						Slot.MipIndex - CurrentFirstMip,
						*Slot.Region,
						Slot.SrcPitch,
						Slot.SrcData
						+ Slot.Region->SrcY * Slot.SrcPitch
						+ Slot.Region->SrcX * Slot.SrcBpp);
				}
			}
	delete RegionData;
		}
	);
}

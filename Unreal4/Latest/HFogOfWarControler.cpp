// Fill out your copyright notice in the Description page of Project Settings.

#include "fogofwar.h"
#include "HFogOfWarControler.h"


// Sets default values
AHFogOfWarControler::AHFogOfWarControler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TextureWidth = 512;
	TextureHeight = 512;
	PointTextureScale = 1.0f;
}

// Called when the game starts or when spawned
void AHFogOfWarControler::BeginPlay()
{
	Super::BeginPlay();

	// !< TODO : 自动处理世界的Bounds范围


	ScaleX = (float)TextureWidth / (WorldMaxPosition.X - WorldMinPosition.X);
	ScaleY = (float)TextureHeight / (WorldMaxPosition.Y - WorldMinPosition.Y);

	InitTextureResource();
}

void AHFogOfWarControler::InitTextureResource()
{
	DynamicTexture = UTexture2D::CreateTransient(TextureWidth, TextureHeight, PF_G8);
	DynamicTexture->CompressionSettings = TextureCompressionSettings::TC_Grayscale;
	DynamicTexture->SRGB = 0;
	DynamicTexture->MipGenSettings = TMGS_NoMipmaps;
	DynamicTexture->UpdateResource();

	DynamicTexturePixels.ResizeTo(TextureWidth * TextureHeight);
	for (int x = 0; x < TextureWidth; ++x)
	{
		for (int y = 0; y < TextureHeight; ++y)
		{
			DynamicTexturePixels[y * TextureWidth + x] = 255;
		}
	}

	PointTextureWidth = PointTexture->GetSizeX();
	PointTextureHeight = PointTexture->GetSizeY();
	PointTexture->Source->GetMipData(PointTexturePixels, 0);
	SyncTextureContents();
}

// Called every frame
void AHFogOfWarControler::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AHFogOfWarControler::UpdatePlayerPosition(const FVector& pos)
{
	// !< 填充内存中的图片内容
	if (PointTexture)
	{
		uint8 SamplePointTexture
		int32 U
	}
}

void AHFogOfWarControler::SyncTextureContents()
{
	static const FUpdateTextureRegion2D WholeTextureRegion(0, 0, 0, 0, TextureWidth, TextureHeight);
	if (DynamicTexture->Resource)
	{
		struct FUpdateTextureRegionData
		{
			FTexture2DResource* Texture2DResource;
			int32 MipIndex;
			uint32 NumRegions;
			FUpdateTextureRegion2D* Regions;
			uint32 SrcPitch;
			uint32 SrcBpp;
			uint8* SrcData;
		};
		FUpdateTextureRegionData* RegionData = new FUpdateTextureRegionData;
		RegionData->Texture2DResource = (FTexture2DResource*)DynamicTexture->Resource;
		RegionData->MipIndex = 0;
		RegionData->NumRegions = 1;
		RegionData->Regions = &WholeTextureRegion;
		RegionData->SrcPitch = TextureWidth;
		RegionData->SrcBpp = 1;
		RegionData->SrcData = DynamicTexturePixels.GetData();

		ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER(
			SyncTextureContents,
			FUpdateTextureRegionData*, RegionData, RegionData,
			{
				for (uint32 RegionIndex = 0; RegionIndex < RegionData->NumRegions; ++RegionIndex)
				{
					int32 CurrentFirstMip = RegionData->Texture2DResource->GetCurrentFirstMip();
					if (RegionData->MipIndex >= CurrentFirstMip)
					{
						RHIUpdateTexture2D(
							RegionData->Texture2DResource->GetTexture2DRHI(),
							RegionData->MipIndex - CurrentFirstMip,
							RegionData->Regions[RegionIndex],
							RegionData->SrcPitch,
							RegionData->SrcData
							+ RegionData->Regions[RegionIndex].SrcY * RegionData->SrcPitch
							+ RegionData->Regions[RegionIndex].SrcX * RegionData->SrcBpp);
					}
				}
				delete RegionData;
			}
		);
	}
}

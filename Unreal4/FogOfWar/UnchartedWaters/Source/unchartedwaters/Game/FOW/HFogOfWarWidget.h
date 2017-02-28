#pragma once

#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"

#include "SFogOfWarWidget.h"
#include "HFogOfWarWidget.generated.h"

UCLASS()
class UHFogOfWarWidget : public UWidget
{
	GENERATED_UCLASS_BODY()
protected:
	TSharedPtr<SFogOfWarWidget> MyFOWWidget;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FOW")
		FSlateBrush WorldBrush;
	UPROPERTY()
		FGetSlateBrush WorldBrushDelegate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FOW")
		FSlateBrush HeroBrush;
	UPROPERTY()
		FGetSlateBrush HeroBrushDelegate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FOW")
		FSlateBrush NPCBrush;
	UPROPERTY()
		FGetSlateBrush NPCBrushDelegate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FOW")
		float HeroSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FOW")
		float NPCSize;

public:
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	const FSlateBrush* ConvertWorldImage(TAttribute<FSlateBrush> InImageAsset) const;
	const FSlateBrush* ConvertHeroImage(TAttribute<FSlateBrush> InImageAsset) const;
	const FSlateBrush* ConvertNPCImage(TAttribute<FSlateBrush> InImageAsset) const;
};

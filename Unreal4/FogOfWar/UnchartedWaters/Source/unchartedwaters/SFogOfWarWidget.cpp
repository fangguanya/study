#include "unchartedwaters.h"
#include "SFogOfWarWidget.h"

DECLARE_CYCLE_STAT(TEXT("OnPaint-SFogOfWarWidget"), STAT_SlateOnPaint_SFogOfWarWidget, STATGROUP_Slate);

void SFogOfWarWidget::SetWorldImage(TAttribute<const FSlateBrush*> InImage)
{
	WorldImage = InImage;
	Invalidate(EInvalidateWidget::Layout);
}
void SFogOfWarWidget::SetHeroImage(TAttribute<const FSlateBrush*> InImage)
{
	HeroImage = InImage;
	Invalidate(EInvalidateWidget::Layout);
}
void SFogOfWarWidget::SetNPCImage(TAttribute<const FSlateBrush*> InImage)
{
	NPCImage = InImage;
	Invalidate(EInvalidateWidget::Layout);
}
void SFogOfWarWidget::SetHeroSize(float InSize)
{
	if (HeroSize != InSize)
	{
		HeroSize = InSize;
		Invalidate(EInvalidateWidget::Layout);
	}
}
void SFogOfWarWidget::SetNPCSize(float InSize)
{
	if (NPCSize != InSize)
	{
		NPCSize = InSize;
		Invalidate(EInvalidateWidget::Layout);
	}
}

void SFogOfWarWidget::Construct(const FArguments& InArgs)
{
	WorldImage = InArgs._WorldImage;
	HeroImage = InArgs._HeroImage;
	NPCImage = InArgs._NPCImage;
	HeroSize = InArgs._HeroSize.Get();
	NPCSize = InArgs._NPCSize.Get();
}

int32 SFogOfWarWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	SCOPE_CYCLE_COUNTER(STAT_SlateOnPaint_SFogOfWarWidget);
	const FSlateBrush* HeroImageBrush = HeroImage.Get();
	if (HeroImageBrush != nullptr && HeroImageBrush->DrawAs != ESlateBrushDrawType::NoDrawType)
	{
		const bool bIsEnabled = ShouldBeEnabled(bParentEnabled);
		const uint32 DrawEffects = bIsEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;

		FVector2D AdjustedSize(AllottedGeometry.GetLocalSize().X - HeroSize * 2, AllottedGeometry.GetLocalSize().Y - HeroSize * 2);

		FPaintGeometry PaintGeom = AllottedGeometry.ToPaintGeometry(FVector2D(HeroSize, HeroSize), AdjustedSize);
		FSlateDrawElement::MakeBox(
			OutDrawElements,
			LayerId,
			PaintGeom,
			HeroImageBrush,
			MyClippingRect,
			DrawEffects);
	}
	return LayerId;
}
FVector2D SFogOfWarWidget::ComputeDesiredSize(float) const
{
	const FSlateBrush* HeroImageBrush = HeroImage.Get();
	if (HeroImageBrush != nullptr)
	{
		return HeroImageBrush->ImageSize;
	}
	return FVector2D::ZeroVector;
}
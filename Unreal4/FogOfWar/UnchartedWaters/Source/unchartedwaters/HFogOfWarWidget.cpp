#include "unchartedwaters.h"
#include "HFogOfWarWidget.h"

#define LOCTEXT_NAMESPACE "UMG"

UHFogOfWarWidget::UHFogOfWarWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, HeroSize(10)
	, NPCSize(10)
{
}

void UHFogOfWarWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	MyFOWWidget->SetHeroSize(HeroSize);
	MyFOWWidget->SetNPCSize(NPCSize);
	TAttribute<const FSlateBrush*> WorldImageBinding = OPTIONAL_BINDING_CONVERT(FSlateBrush, WorldBrush, const FSlateBrush*, ConvertWorldImage);
	MyFOWWidget->SetWorldImage(WorldImageBinding);
	TAttribute<const FSlateBrush*> HeroImageBinding = OPTIONAL_BINDING_CONVERT(FSlateBrush, HeroBrush, const FSlateBrush*, ConvertHeroImage);
	MyFOWWidget->SetHeroImage(HeroImageBinding);
	TAttribute<const FSlateBrush*> NPCImageBinding = OPTIONAL_BINDING_CONVERT(FSlateBrush, WorldBrush, const FSlateBrush*, ConvertNPCImage);
	MyFOWWidget->SetNPCImage(NPCImageBinding);
}

void UHFogOfWarWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	MyFOWWidget.Reset();
}
#if WITH_EDITOR
const FText UHFogOfWarWidget::GetPaletteCategory()
{
	return LOCTEXT("Common", "Common");
}
#endif

TSharedRef<SWidget> UHFogOfWarWidget::RebuildWidget()
{
	MyFOWWidget = SNew(SFogOfWarWidget);
	return MyFOWWidget.ToSharedRef();
}

const FSlateBrush* UHFogOfWarWidget::ConvertWorldImage(TAttribute<FSlateBrush> InImageAsset) const
{
	UHFogOfWarWidget* MutableThis = const_cast<UHFogOfWarWidget*>(this);
	MutableThis->WorldBrush = InImageAsset.Get();
	return &WorldBrush;
}
const FSlateBrush* UHFogOfWarWidget::ConvertHeroImage(TAttribute<FSlateBrush> InImageAsset) const
{
	UHFogOfWarWidget* MutableThis = const_cast<UHFogOfWarWidget*>(this);
	MutableThis->HeroBrush = InImageAsset.Get();
	return &HeroBrush;
}
const FSlateBrush* UHFogOfWarWidget::ConvertNPCImage(TAttribute<FSlateBrush> InImageAsset) const
{
	UHFogOfWarWidget* MutableThis = const_cast<UHFogOfWarWidget*>(this);
	MutableThis->NPCBrush = InImageAsset.Get();
	return &NPCBrush;
}
#undef LOCTEXT_NAMESPACE
#pragma once

#include "SlateCore.h"

class SFogOfWarWidget : public SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(SFogOfWarWidget)
		: _WorldImage(FCoreStyle::Get().GetDefaultBrush())
		, _HeroImage(FCoreStyle::Get().GetDefaultBrush())
		, _NPCImage(FCoreStyle::Get().GetDefaultBrush())
		, _HeroSize(10)
		, _NPCSize(10)
		{}
	SLATE_ATTRIBUTE(const FSlateBrush*, WorldImage)
		SLATE_ATTRIBUTE(const FSlateBrush*, HeroImage)
		SLATE_ATTRIBUTE(const FSlateBrush*, NPCImage)
		SLATE_ATTRIBUTE(float, HeroSize)
		SLATE_ATTRIBUTE(float, NPCSize)
		SLATE_END_ARGS()

public:
	SFogOfWarWidget()
	{
		bCanTick = false;
	}
	void Construct(const FArguments& InArgs);

public:
	void SetWorldImage(TAttribute<const FSlateBrush*> InImage);
	void SetHeroImage(TAttribute<const FSlateBrush*> InImage);
	void SetNPCImage(TAttribute<const FSlateBrush*> InImage);
	void SetHeroSize(float InSize);
	void SetNPCSize(float InSize);

protected:
	TAttribute<const FSlateBrush*> WorldImage;
	TAttribute<const FSlateBrush*> HeroImage;
	TAttribute<const FSlateBrush*> NPCImage;
	float HeroSize;
	float NPCSize;

	// !< TODO : 如果将模型等信息保存, 显示, 加载等??

public:
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	virtual FVector2D ComputeDesiredSize(float) const override;
};
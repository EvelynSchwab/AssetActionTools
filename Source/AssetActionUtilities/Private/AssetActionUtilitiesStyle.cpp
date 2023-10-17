// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetActionUtilitiesStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FAssetActionUtilitiesStyle::StyleInstance = nullptr;

void FAssetActionUtilitiesStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FAssetActionUtilitiesStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FAssetActionUtilitiesStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("AssetActionUtilitiesStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FAssetActionUtilitiesStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("AssetActionUtilitiesStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("AssetActionUtilities")->GetBaseDir() / TEXT("Resources"));

	Style->Set("AssetActionUtilities.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

void FAssetActionUtilitiesStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FAssetActionUtilitiesStyle::Get()
{
	return *StyleInstance;
}

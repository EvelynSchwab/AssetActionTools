// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "AssetActionUtilitiesStyle.h"

class FAssetActionUtilitiesCommands : public TCommands<FAssetActionUtilitiesCommands>
{
public:

	FAssetActionUtilitiesCommands()
		: TCommands<FAssetActionUtilitiesCommands>(TEXT("AssetActionUtilities"), NSLOCTEXT("Contexts", "AssetActionUtilities", "AssetActionUtilities Plugin"), NAME_None, FAssetActionUtilitiesStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};
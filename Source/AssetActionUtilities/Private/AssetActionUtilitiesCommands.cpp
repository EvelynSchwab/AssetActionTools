// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetActionUtilitiesCommands.h"

#define LOCTEXT_NAMESPACE "FAssetActionUtilitiesModule"

void FAssetActionUtilitiesCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Asset Action Utilities", "Bring up the asset action utilities window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE

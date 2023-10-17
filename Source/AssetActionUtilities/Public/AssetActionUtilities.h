// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;
class UEditorUtilityWidget;

class FAssetActionUtilitiesModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:

	void RegisterMenus();
	
	TSharedPtr<class FUICommandList> PluginCommands;

	FString UtilityWidgetReference = TEXT("EditorUtilityWidgetBlueprint'/AssetActionUtilities/EUWBP_AssetActions.EUWBP_AssetActions'");

	UEditorUtilityWidget* SpawnedUtilityWidget = nullptr;
};

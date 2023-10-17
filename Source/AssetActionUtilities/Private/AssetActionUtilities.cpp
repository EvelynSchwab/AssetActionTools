// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetActionUtilities.h"
#include "AssetActionUtilitiesStyle.h"
#include "AssetActionUtilitiesCommands.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "EditorUtilitySubsystem.h"
#include "EditorAssetLibrary.h"

#define LOCTEXT_NAMESPACE "FAssetActionUtilitiesModule"

void FAssetActionUtilitiesModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FAssetActionUtilitiesStyle::Initialize();
	FAssetActionUtilitiesStyle::ReloadTextures();

	FAssetActionUtilitiesCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FAssetActionUtilitiesCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FAssetActionUtilitiesModule::PluginButtonClicked),
		FCanExecuteAction());
	
	
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAssetActionUtilitiesModule::RegisterMenus));
	
}

void FAssetActionUtilitiesModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FAssetActionUtilitiesStyle::Shutdown();

	FAssetActionUtilitiesCommands::Unregister();
	
}

void FAssetActionUtilitiesModule::PluginButtonClicked()
{
	// Try load the editor utility widget
	UObject* UtilityWidgetBP = UEditorAssetLibrary::LoadAsset(UtilityWidgetReference);
	
	// Early return if the widget is invalid
	if (UtilityWidgetBP == nullptr) return;

	UEditorUtilityWidgetBlueprint* UtilityWidget = Cast<UEditorUtilityWidgetBlueprint>(UtilityWidgetBP);

	if (UtilityWidget == nullptr) return;
	
	// Get the editor utility subsystem
	UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();

	SpawnedUtilityWidget = EditorUtilitySubsystem->SpawnAndRegisterTab(UtilityWidget);
}

void FAssetActionUtilitiesModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("Tools");
			Section.AddMenuEntryWithCommandList(FAssetActionUtilitiesCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAssetActionUtilitiesModule, AssetActionUtilities)
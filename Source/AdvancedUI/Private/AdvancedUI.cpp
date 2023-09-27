// Copyright Epic Games, Inc. All Rights Reserved.

#include "AdvancedUI.h"
#include "AdvancedUIConfig.h"
#include "PropertyEditorModule.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"

#define LOCTEXT_NAMESPACE "FAdvancedUIModule"

void FAdvancedUIModule::StartupModule()
{
	RegisterSettings();

	ApplySettings();
}

void FAdvancedUIModule::ShutdownModule()
{
	UnregisterSettings();
}

void FAdvancedUIModule::RegisterSettings()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyModule.RegisterCustomClassLayout(
		"AdvancedUIConfig",
		FOnGetDetailCustomizationInstance::CreateStatic(&FAdvancedUIConfigCustomization::MakeInstance)
	);

	PropertyModule.NotifyCustomizationModuleChanged();

	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	if (SettingsModule == nullptr)
	{
		return;
	}

	UAdvancedUIConfig* Settings = GetMutableDefault<UAdvancedUIConfig>();
	ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings(
		"Editor",
		"Plugins",
		"Advanced UI",
		LOCTEXT("AdvancedUISettingsName", "Advanced UI"),
		LOCTEXT("AdvancedUISettingsDescription", "Configure the Advanced UI plugin"),
		Settings
	);

	if (!SettingsSection.IsValid())
	{
		return;
	}

	SettingsSection->OnModified().BindRaw(this, &FAdvancedUIModule::OnSettingsSaved);
}

void FAdvancedUIModule::UnregisterSettings()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

		PropertyModule.UnregisterCustomClassLayout("AdvancedUIConfig");
	}

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Editor", "Plugins", "Advanced UI");
	}
}

bool FAdvancedUIModule::OnSettingsSaved()
{
	UAdvancedUIConfig* Settings = GetMutableDefault<UAdvancedUIConfig>();
	Settings->SaveConfig();

	ApplySettings(Settings);

	return true;
}

void FAdvancedUIModule::ApplySettings(UAdvancedUIConfig* Settings)
{
	if (Settings == nullptr)
	{
		Settings = GetMutableDefault<UAdvancedUIConfig>();
	}

	FSlateApplication& SlateApp = FSlateApplication::Get();
	SlateApp.SetApplicationScale(Settings->UIScale);
	SlateApp.SetAllowTooltips(!Settings->bDisableSlateToolTips);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAdvancedUIModule, AdvancedUI)

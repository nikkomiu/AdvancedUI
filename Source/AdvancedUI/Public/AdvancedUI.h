// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FAdvancedUIModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

protected:

	void RegisterSettings();
	void UnregisterSettings();

	bool OnSettingsSaved();

	void ApplySettings(UAdvancedUIConfig* Settings = nullptr);
};

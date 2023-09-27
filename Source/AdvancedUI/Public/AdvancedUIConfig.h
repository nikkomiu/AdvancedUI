// Copyright Nikko Miu. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"
#include "AdvancedUIConfig.generated.h"

UCLASS(Config=Editor, DefaultConfig)
class ADVANCEDUI_API UAdvancedUIConfig : public UObject
{
    GENERATED_BODY()

public:

    UAdvancedUIConfig(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}

    UPROPERTY(Config, EditAnywhere, Category = "Advanced UI", meta = (ClampMin = "0.1", ClampMax = "5.0", UIMin = "0.1", UIMax = "2.0", Delta = "0.1"))
    float UIScale = 1.0f;

    UPROPERTY(Config, EditAnywhere, Category = "Advanced UI")
    bool bDisableSlateToolTips = false;
};

class FAdvancedUIConfigCustomization : public IDetailCustomization
{
public:

    virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

    static TSharedRef<IDetailCustomization> MakeInstance()
    {
        return MakeShareable(new FAdvancedUIConfigCustomization);
    }
};

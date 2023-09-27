// Copyright Nikko Miu. All Rights Reserved.

#include "AdvancedUIConfig.h"

#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

void FAdvancedUIConfigCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
    IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Advanced UI", FText::GetEmpty(), ECategoryPriority::Important);

    Category.AddProperty(GET_MEMBER_NAME_CHECKED(UAdvancedUIConfig, UIScale));
    Category.AddProperty(GET_MEMBER_NAME_CHECKED(UAdvancedUIConfig, bDisableSlateToolTips));
}

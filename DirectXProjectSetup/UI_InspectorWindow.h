#pragma once
#include "AUIScreen.h"

class UI_InspectorWindow : public AUIScreen
{
public:
    UI_InspectorWindow(std::string name);
    void DrawUI() override;
};


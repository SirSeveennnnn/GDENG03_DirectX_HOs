#pragma once
#include "AUIScreen.h"

class UI_MenuToolBar : public AUIScreen
{
public:
    UI_MenuToolBar(std::string name);
    void DrawUI() override;
};


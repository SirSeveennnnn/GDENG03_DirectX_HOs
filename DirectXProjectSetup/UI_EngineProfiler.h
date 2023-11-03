#pragma once
#include "AUIScreen.h"
class UI_EngineProfiler : public AUIScreen
{
public:
    UI_EngineProfiler(std::string name);
    void DrawUI() override;

private:
    float mElapsedTime = 0.f;
    float mTimeSinceLastCalc = 0.f;
    float mAverageDeltaTime = 0.f;
    float mFramesPerSecond = 0.f;
    float mFramesSinceLastCalc = 0.f;
};


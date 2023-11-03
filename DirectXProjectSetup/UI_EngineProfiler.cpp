#include "UI_EngineProfiler.h"
#include "EngineTime.h"

UI_EngineProfiler::UI_EngineProfiler(std::string name) : AUIScreen::AUIScreen(name)
{
    
}


void UI_EngineProfiler::DrawUI() {

    mFramesSinceLastCalc += 1.f;
    mTimeSinceLastCalc += EngineTime::getDeltaTime();

    if (mTimeSinceLastCalc >= 1.f) {
        mAverageDeltaTime = mTimeSinceLastCalc / mFramesSinceLastCalc;
        mFramesPerSecond = 1.f / mAverageDeltaTime;
        mFramesSinceLastCalc = 0.f;
        mTimeSinceLastCalc = 0.f;
    }

    ImGuiWindowFlags windowFlags = 64;
 
    ImGui::Begin("GDENG03 Engine Profiler", NULL, windowFlags);
    //ImGui::SetWindowSize(ImVec2(400, 150));
    //ImGui::SetWindowPos(ImVec2(50, GlobalProperties::WINDOW_HEIGHT - 214));
    ImGui::Text("Average time per frame: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(mAverageDeltaTime * 1000.f).c_str());
    ImGui::SameLine();
    ImGui::Text(" ms");

    ImGui::Text("Frames per second: ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(mFramesPerSecond).c_str());

    ImGui::End();
}
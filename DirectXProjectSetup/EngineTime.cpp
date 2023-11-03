#include "EngineTime.h"
EngineTime* EngineTime::instance = nullptr;

void EngineTime::initialize() {
    if (!instance) instance = new EngineTime();
}

double EngineTime::getDeltaTime() {
    std::chrono::duration<double> deltaTime = instance->start - instance->end;
    return deltaTime.count();
}

EngineTime::EngineTime() {}

EngineTime::~EngineTime() {
    delete instance;
}

void EngineTime::logFrameStart() {
    instance->start = std::chrono::system_clock::now();
}

void EngineTime::logFrameEnd() {
    instance->end = instance->start;
}
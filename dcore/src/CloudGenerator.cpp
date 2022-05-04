#include "CloudGenerator.h"
#include "DoveLog.hpp"

CloudGenerator::CloudGenerator() {
    tex.Init();
    tex.Allocate(2048, 2048);
}

CloudGenerator::~CloudGenerator() {
    tex.Release();
}

void CloudGenerator::Generate() {
    DLOG_DEBUG("generating");
}

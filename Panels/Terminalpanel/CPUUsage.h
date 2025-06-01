#ifndef BLUEPRINT_CPUUSAGE_H
#define BLUEPRINT_CPUUSAGE_H

#include <fstream>
#include <string>
#include <unistd.h>
#include <sstream>


class CPUUsage {
public:
    CPUUsage();
    double GetCPUUsage() noexcept;         // 当前进程 CPU 占用率（%）
    double GetMemoryUsageMB() noexcept;    // 当前进程内存占用（MB）

private:
#ifdef _WIN32
    unsigned long long lastCPU, lastSysCPU, lastUserCPU;
    int numProcessors;
    HANDLE self;
#else
    long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;
    long long lastProcTime;
    bool initialized;
#endif
};


#endif //BLUEPRINT_CPUUSAGE_H

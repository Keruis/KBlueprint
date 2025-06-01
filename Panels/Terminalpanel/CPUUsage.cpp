#include "CPUUsage.h"

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>

CPUUsage::CPUUsage() {
    SYSTEM_INFO sysInfo;
    FILETIME ftime, fsys, fuser;

    GetSystemInfo(&sysInfo);
    numProcessors = sysInfo.dwNumberOfProcessors;
    GetSystemTimeAsFileTime(&ftime);
    self = GetCurrentProcess();
    GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);

    lastCPU = *((unsigned long long*)&ftime);
    lastSysCPU = *((unsigned long long*)&fsys);
    lastUserCPU = *((unsigned long long*)&fuser);
}

double CPUUsage::GetCPUUsage() noexcept {
    FILETIME ftime, fsys, fuser;
    unsigned long long now, sys, user;

    GetSystemTimeAsFileTime(&ftime);
    now = *((unsigned long long*)&ftime);

    GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
    sys = *((unsigned long long*)&fsys);
    user = *((unsigned long long*)&fuser);

    double percent = (double)((sys - lastSysCPU) + (user - lastUserCPU));
    percent /= (now - lastCPU);
    percent /= numProcessors;
    percent *= 100;

    lastCPU = now;
    lastUserCPU = user;
    lastSysCPU = sys;

    return percent;
}

double CPUUsage::GetMemoryUsageMB() noexcept {
    PROCESS_MEMORY_COUNTERS memInfo;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo))) {
        return memInfo.WorkingSetSize / (1024.0 * 1024.0);
    }
    return 0.0;
}

#else // Linux

#include <fstream>
#include <string>
#include <unistd.h>

CPUUsage::CPUUsage()
        : lastTotalUser(0), lastTotalUserLow(0), lastTotalSys(0), lastTotalIdle(0),
          lastProcTime(0), initialized(false)
{}

double CPUUsage::GetCPUUsage() noexcept {
    long long totalUser, totalUserLow, totalSys, totalIdle;
    long long procTime = 0;

    std::ifstream fileStat("/proc/stat");
    std::string cpu;
    fileStat >> cpu >> totalUser >> totalUserLow >> totalSys >> totalIdle;
    fileStat.close();

    std::ifstream fileProc("/proc/self/stat");
    std::string dummy;
    for (int i = 0; i < 13; ++i) fileProc >> dummy;
    long long utime, stime;
    fileProc >> utime >> stime;
    fileProc.close();

    procTime = utime + stime;

    if (!initialized) {
        lastTotalUser = totalUser;
        lastTotalUserLow = totalUserLow;
        lastTotalSys = totalSys;
        lastTotalIdle = totalIdle;
        lastProcTime = procTime;
        initialized = true;
        return 0.0;
    }

    long long total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
                      (totalSys - lastTotalSys);
    long long totalTime = total + (totalIdle - lastTotalIdle);
    long long procDiff = procTime - lastProcTime;

    lastTotalUser = totalUser;
    lastTotalUserLow = totalUserLow;
    lastTotalSys = totalSys;
    lastTotalIdle = totalIdle;
    lastProcTime = procTime;

    if (totalTime == 0) return 0.0;
    return (100.0 * procDiff / totalTime);
}

double CPUUsage::GetMemoryUsageMB() noexcept {
    std::ifstream status("/proc/self/status");
    std::string line;
    while (std::getline(status, line)) {
        if (line.rfind("VmRSS:", 0) == 0) {
            long memKB = 0;
            sscanf(line.c_str(), "VmRSS: %ld kB", &memKB);
            return memKB / 1024.0;
        }
    }
    return 0.0;
}

#endif
#ifndef BLUEPRINT_CPUFEATURES_H
#define BLUEPRINT_CPUFEATURES_H

#include <iostream>
#include <vector>
#include <iomanip>
#if defined(_MSC_VER)
    #include <intrin.h>
#elif defined(__GNUC__) || defined(__clang__)
    #include <cpuid.h>
    #include <string>
#endif

namespace CPUFeatures {
    void cpuid(int info[4], int functionId, int subFunctionId = 0) noexcept {
#if defined(_MSC_VER_)
        __cpuidex(info, function_id, subfunction_id);
#else
        __asm__ __volatile__ (
             "cpuid             \n\t"
			: "=a" (info[0]), "=b" (info[1]), "=c" (info[2]), "=d" (info[3])
			: "0" (functionId), "2" (subFunctionId)
        );
#endif
    }

    bool os_avx_supported() {
        int info[4];
        cpuid(info, 1);
        bool os_supports_xsave = (info[2] & (1 << 27)) != 0;
        bool avx_supported = (info[2] & (1 << 28)) != 0;

        if (!(os_supports_xsave && avx_supported))
            return false;

        unsigned long long xcr0 = 0;
#if defined(_MSC_VER)
        xcr0 = _xgetbv(0);
#else
        unsigned int eax, edx;
        __asm__ volatile (".byte 0x0f, 0x01, 0xd0" : "=a"(eax), "=d"(edx) : "c"(0));
        xcr0 = ((unsigned long long)edx << 32) | eax;
#endif
        return (xcr0 & 0x6) == 0x6;
    }

    struct Feature {
        const char* name;
        int cpuid_function;  // CPUID function to call (EAX)
        int cpuid_subfunction; // usually 0
        int reg; // 0:EAX 1:EBX 2:ECX 3:EDX
        int bit;
        bool requires_os_avx; // 是否需要先检测 OS 支持 AVX/XGETBV
        bool requires_avx;    // 是否必须 AVX 才支持
    };

    bool check_feature_cpuid(const Feature& f) {
        // 如果需要os_avx支持而不满足，直接返回false
        if (f.requires_os_avx && !os_avx_supported()) return false;
        int info[4]{0};
        cpuid(info, f.cpuid_function, f.cpuid_subfunction);
        return (info[f.reg] & (1 << f.bit)) != 0;
    }

    bool is_feature_supported(const std::string& name);

    const std::vector<Feature> all_features = {
            // SSE 基础，1/EDX bit 25
            {"SSE",       1, 0, 3, 25, false, false},
            // SSE2，1/EDX bit 26
            {"SSE2",      1, 0, 3, 26, false, false},
            // AVX，1/ECX bit 28，且要OS支持XGETBV
            {"AVX",       1, 0, 2, 28, true,  false},
            // AVX2，7/EBX bit 5，需要OS AVX支持
            {"AVX2",      7, 0, 1, 5,  true,  true},
            // AVX-512F，7/EBX bit 16，需要OS AVX支持
            {"AVX512F",   7, 0, 1, 16, true,  true},
            // BMI1，7/EBX bit 3，需要OS AVX支持
            {"BMI1",      7, 0, 1, 3,  true,  true},
            // BMI2，7/EBX bit 8，需要OS AVX支持
            {"BMI2",      7, 0, 1, 8,  true,  true},
            // FMA，1/ECX bit 12，需要OS AVX支持
            {"FMA",       1, 0, 2, 12, true,  false},
            // ADX，7/EBX bit 19，需要OS AVX支持
            {"ADX",       7, 0, 1, 19, true,  true},
            // SHA，7/ECX bit 29，需要OS AVX支持
            {"SHA",       7, 0, 2, 29, true,  true},
            // AVX512DQ，7/EBX bit 17
            {"AVX512DQ",  7, 0, 1, 17, true,  true},
            // AVX512IFMA，7/EBX bit 21
            {"AVX512IFMA",7, 0, 1, 21, true,  true},
            // AVX512PF，7/EBX bit 26
            {"AVX512PF",  7, 0, 1, 26, true,  true},
            // AVX512ER，7/EBX bit 27
            {"AVX512ER",  7, 0, 1, 27, true,  true},
            // AVX512CD，7/EBX bit 28
            {"AVX512CD",  7, 0, 1, 28, true,  true},
            // AVX512BW，7/EBX bit 30
            {"AVX512BW",  7, 0, 1, 30, true,  true},
            // AVX512VL，7/EBX bit 31
            {"AVX512VL",  7, 0, 1, 31, true,  true},
            // AVX512VBMI，7/ECX bit 1
            {"AVX512VBMI", 7, 0, 2, 1,  true,  true},
            // AVX512VNNI，7/ECX bit 11
            {"AVX512VNNI", 7, 0, 2, 11, true,  true},
            // AVX512BF16，7/EDX bit 5
            {"AVX512BF16", 7, 0, 3, 5,  true,  true},
    };

    bool is_feature_supported(const std::string& name) {
        for (const auto& f : all_features) {
            if (name == f.name)
                return check_feature_cpuid(f);
        }
        // 如果找不到该特征，返回false
        return false;
    }

    struct FeaturePrinter {
        FeaturePrinter() {
            std::cout << "====== CPU 指令集支持检测 ======\n\n";
            std::cout << std::left << std::setw(24) << "特性名称"
                      << std::setw(10) << "支持" << "\n";
            std::cout << std::string(28, '-') << "\n";

            std::cout << std::setw(18) << "SSE"
                      << std::setw(10) << std::boolalpha << true << "\n";

            for (const auto& f : all_features) {
                if (std::string(f.name) == "SSE") continue;
                std::cout << std::setw(18) << f.name
                          << std::setw(10) << std::boolalpha << check_feature_cpuid(f)
                          << "\n";
            }
            std::cout << std::endl;
        }
    } featurePrinterInstance;
}

#endif //BLUEPRINT_CPUFEATURES_H

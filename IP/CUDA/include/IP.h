#ifndef CUDA_BLUEPRINT_IP_H
#define CUDA_BLUEPRINT_IP_H

#include <iostream>
#include <vector>
#include <cstdint>

extern "C" void ConvertToGrayCUDA(
        const uint8_t* r,
        const uint8_t* g,
        const uint8_t* b,
        uint8_t* out,
        int width,
        int height
);

#endif //BLUEPRINT_IP_H

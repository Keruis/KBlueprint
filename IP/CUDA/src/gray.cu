#include <cuda_runtime.h>

__global__
void rgb_to_gray_kernel(
        const unsigned char* r,
        const unsigned char* g,
        const unsigned char* b,
        unsigned char* gray,
        int width,
        int height
) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int total = width * height;

    if (idx < total) {
        float rf = static_cast<float>(r[idx]);
        float gf = static_cast<float>(g[idx]);
        float bf = static_cast<float>(b[idx]);
        float gray_val = 0.299f * rf + 0.587f * gf + 0.114f * bf;
        gray[idx] = static_cast<unsigned char>(gray_val);
    }
}

extern "C"
void ConvertToGrayCUDA(
        const unsigned char* r,
        const unsigned char* g,
        const unsigned char* b,
        unsigned char* out,
        int width,
        int height
) {
    size_t num_pixels = width * height;
    size_t bytes = num_pixels * sizeof(unsigned char);

    unsigned char *d_r, *d_g, *d_b, *d_gray;

    cudaMalloc(&d_r, bytes);
    cudaMalloc(&d_g, bytes);
    cudaMalloc(&d_b, bytes);
    cudaMalloc(&d_gray, bytes);

    cudaMemcpy(d_r, r, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_g, g, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, bytes, cudaMemcpyHostToDevice);

    int blockSize = 256;
    int numBlocks = (num_pixels + blockSize - 1) / blockSize;

    rgb_to_gray_kernel<<<numBlocks, blockSize>>>(d_r, d_g, d_b, d_gray, width, height);
    cudaDeviceSynchronize();

    cudaMemcpy(out, d_gray, bytes, cudaMemcpyDeviceToHost);

    cudaFree(d_r);
    cudaFree(d_g);
    cudaFree(d_b);
    cudaFree(d_gray);
}
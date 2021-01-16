#include "graphics-cuda.h"

using namespace std;

__host__ uint32_t* gpuAlloc(unsigned screen_size) {
    uint32_t* gpu_mem;

    cudaError_t err = cudaMalloc(&gpu_mem, screen_size * 4);
    if (err != cudaSuccess) return NULL;

    return gpu_mem;
};

__host__ void gpuFree(void* gpu_mem) {
    cudaFree(gpu_mem);
}

__host__ unsigned gpuBlit(void* src, void* dst, unsigned screen_size) {
    cudaError_t err = cudaMemcpy(dst, src, screen_size * 4, cudaMemcpyDeviceToHost);
    if (err != cudaSuccess) return 1;
    return 0;
}

__device__ uint32_t getPixColor(unsigned* d_field, unsigned S, unsigned H, unsigned W, unsigned x, unsigned y) {
    unsigned i = y / S;
    unsigned j = x / S;
    if (i >= H || j >= W) return 0;

    if (d_field[i * W + j] <= ALIVE)
        return COLOURS[d_field[i * W + j]];
  
    return 0;
}

__global__ void d_render(uint32_t* buf, unsigned* d_field, unsigned S, unsigned H, unsigned W) {
    const unsigned xPix = blockDim.x * blockIdx.x + threadIdx.x;
    const unsigned yPix = blockDim.y * blockIdx.y + threadIdx.y;
    unsigned pos = W * S * yPix + xPix;
    buf[pos] = getPixColor(d_field, S, H, W, xPix, yPix);
}

__host__ int render(SDL_Surface *screen,
    void* cuda_pixels,
    unsigned* field, unsigned S, unsigned H, unsigned W) {

    uint32_t*buf = (uint32_t*)cuda_pixels;

    unsigned* d_field;
    cudaMalloc((void**)&d_field, (H * W) * sizeof(unsigned));
    cudaMemcpy(d_field, field, (H * W) * sizeof(unsigned), cudaMemcpyHostToDevice);

    const dim3 blocksPerGrid(W, H);
    const dim3 threadsPerBlock(S, S);
    d_render<<<blocksPerGrid, threadsPerBlock>>>(buf, d_field, S, H, W);
    cudaDeviceSynchronize();

    cudaMemcpy(field, d_field, (H * W) * sizeof(unsigned), cudaMemcpyDeviceToHost);
    cudaFree(d_field);

    return gpuBlit(cuda_pixels, screen->pixels, H*W*S*S);
}

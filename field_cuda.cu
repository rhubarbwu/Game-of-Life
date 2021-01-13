#include <stdio.h>

#include <iostream>

#include "field_cuda.h"

using namespace std;

__global__ void d_init(unsigned *d_field, unsigned F) {
    curandState state;
    curand_init((unsigned long long)clock() + 0, threadIdx.x, 0, &state);
    float rand = curand_uniform(&state);
    d_field[threadIdx.x] = rand * MAX < F ? ALIVE : 0;
}

__host__ void initField(unsigned *field, unsigned H, unsigned W, unsigned F) {
    unsigned *d_field;
    cudaMalloc((void **)&d_field, (H * W) * sizeof(unsigned));

    dim3 block_size(H * W);
    dim3 grid_size(1);
    d_init<<<grid_size, block_size>>>(d_field, F);
    cudaDeviceSynchronize();

    cudaMemcpy(field, d_field, (H * W) * sizeof(unsigned), cudaMemcpyDeviceToHost);
    cudaFree(d_field);
}

__global__ void d_transition(unsigned *d_field, unsigned H, unsigned W) {
    unsigned index = threadIdx.x;
    unsigned i = index / W;
    unsigned j = index % W;

    bool left = (j > 0 && d_field[index - 1] == ALIVE);
    bool right = (j < W - 1 && d_field[index + 1] == ALIVE);
    bool above = (i > 0 && d_field[index - W] == ALIVE);
    bool below = (i < H - 1 && d_field[index + W] == ALIVE);

    unsigned neighbours = left + right + above + below;
    __syncthreads();
    if (neighbours / 2 == 1)
        d_field[index] = ALIVE;
    else
        d_field[index] = d_field[index] == 0 ? 0 : d_field[index] - 1;
}

__host__ void transition(unsigned *field, unsigned H, unsigned W) {
    unsigned *d_field;
    cudaMalloc((void **)&d_field, (H * W) * sizeof(unsigned));
    cudaMemcpy(d_field, field, (H * W) * sizeof(unsigned), cudaMemcpyHostToDevice);

    const dim3 block_size(H * W);
    const dim3 grid_size(1);
    d_transition<<<grid_size, block_size>>>(d_field, H, W);
    cudaDeviceSynchronize();

    cudaMemcpy(field, d_field, (H * W) * sizeof(unsigned), cudaMemcpyDeviceToHost);
    cudaFree(d_field);
}
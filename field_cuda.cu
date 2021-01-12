#include <stdio.h>

#include "field_cuda.h"

__global__ void d_init(int *d_field, int fill) {
    curandState state;
    curand_init((unsigned long long)clock() + 0, threadIdx.x, 0, &state);
    float rand = curand_uniform(&state);
    d_field[threadIdx.x] = rand * MAX < fill ? ALIVE : 0;
}

__host__ void initField(int *field, int H, int W, int fill) {
    int *d_field;
    cudaMalloc((void **)&d_field, (H * W) * sizeof(int));

    dim3 block_size(H * W);
    dim3 grid_size(1);
    d_init<<<grid_size, block_size>>>(d_field, fill);
    cudaDeviceSynchronize();

    cudaMemcpy(field, d_field, (H * W) * sizeof(int), cudaMemcpyDeviceToHost);
    cudaFree(d_field);
}

__global__ void d_transition(int *d_field, int H, int W) {
    int index = threadIdx.x;
    int i = index / W;
    int j = index % W;

    bool left = (j > 0 && d_field[index - 1] == ALIVE);
    if (j == 0) left = false;
    bool right = (j < W - 1 && d_field[index + 1] == ALIVE);
    if (j == W - 1) right = false;
    bool above = (i > 0 && d_field[index - W] == ALIVE);
    if (i == 0) above = false;
    bool below = (i < H - 1 && d_field[index + W] == ALIVE);
    if (i == H - 1) below = false;

    int neighbours = left + right + above + below;
    __syncthreads();
    if (neighbours / 2 == 1)
        d_field[index] = ALIVE;
    else
        d_field[index] = d_field[index] == 0 ? 0 : d_field[index] - 1;
}

__host__ void transition(int *field, int H, int W) {
    int *d_field;
    cudaMalloc((void **)&d_field, (H * W) * sizeof(int));

    dim3 block_size(H * W);
    dim3 grid_size(1);

    cudaMemcpy(d_field, field, (H * W) * sizeof(int), cudaMemcpyHostToDevice);

    d_transition<<<grid_size, block_size>>>(d_field, H, W);
    cudaDeviceSynchronize();
    cudaMemcpy(field, d_field, (H * W) * sizeof(int), cudaMemcpyDeviceToHost);
    cudaFree(d_field);
}
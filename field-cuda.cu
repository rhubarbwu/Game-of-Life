#include <curand.h>
#include <curand_kernel.h>

#include "cuda.h"
#include "field-cuda.h"

using namespace std;

__global__ void d_init(unsigned *d_field, unsigned F) {
    curandState state;
    curand_init((unsigned long long)clock() + 0, threadIdx.x, 0, &state);
    float rand = curand_uniform(&state);
    d_field[threadIdx.x] = rand * MAX < F ? ALIVE : 0;
}

__host__ void init_field(unsigned *field, unsigned H, unsigned W, unsigned F) {
    unsigned *d_field;
    cudaMalloc((void **)&d_field, (H * W) * sizeof(unsigned));

    dim3 block_size(H * W);
    dim3 grid_size(1);
    d_init<<<grid_size, block_size>>>(d_field, F);
    cudaDeviceSynchronize();

    cudaMemcpy(field, d_field, (H * W) * sizeof(unsigned), cudaMemcpyDeviceToHost);
    cudaFree(d_field);
}

__global__ void d_transition(unsigned *field, unsigned H, unsigned W) {
    unsigned *prev_field = field;

    unsigned index = threadIdx.x;
    unsigned i = index / W;
    unsigned j = index % W;

    unsigned neighbours = 0;
    NEIGHBOURS

    __syncthreads();
    RULE
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

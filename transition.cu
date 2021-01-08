#include "macros.h"

__global__ void transition(int **field, int H, int W) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;

    bool left = (j > 0 && field[i][j - 1] == ALIVE);
    bool right = (j < W - 1 && field[i][j + 1] == ALIVE);
    bool above = (i > 0 && field[i - 1][j] == ALIVE);
    bool below = (i < H - 1 && field[i + 1][j] == ALIVE);

    int neighbours = left + right + above + below;
    __syncthreads();
    if (i >= H || j >= W) return;
    if (neighbours / 2 == 1) {
        field[i][j] = ALIVE;
    } else {
        field[i][j] = field[i][j] == 0 ? 0 : field[i][j] - 1;
    }
}

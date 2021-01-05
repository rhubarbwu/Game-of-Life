#include <signal.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "helpers.h"
#include "terminal.h"
#include "transition.cu"

int main(int argc, char *argv[]) {
    SANITY;
    ARGUMENTS;

    dim3 block_size(H, W);
    dim3 grid_size(1);

    time_t timer;
    srand((unsigned)time(&timer));

    bool **prev_field, **field;
    cudaMallocManaged(&prev_field, H * sizeof(bool *));
    cudaMallocManaged(&field, H * sizeof(bool *));
    for (int i = 0; i < H; i++) {
        cudaMallocManaged(&prev_field[i], W * sizeof(bool));
        cudaMallocManaged(&field[i], W * sizeof(bool));
    }

    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            prev_field[i][j] = rand() % 100 < O;

    display(prev_field, H, W);

    struct timespec wait_time = {.tv_sec = REFRESH_S, .tv_nsec = REFRESH_NS};
    int r = 0, t = 0;
    while (!interrupted) {
        nanosleep(&wait_time, NULL);
        if (r++ < R * CLOCK_PER_CYCLE)
            continue;
        else
            r = 0;

        transition<<<grid_size, block_size>>>(H, W, prev_field, field);
        cudaDeviceSynchronize();

        if (t++ >= T && T != -1) break;

        clear(H);
        display(field, H, W);

        bool **temp = prev_field;
        prev_field = field;
        field = temp;
    }

    for (int i = 0; i < H; i++) {
        cudaFree(prev_field[i]);
        cudaFree(field[i]);
    }
    cudaFree(prev_field);
    cudaFree(field);

    return 0;
}
#include <signal.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "boilerplate.h"
#include "macros.h"
#include "terminal.h"
#include "transition.cu"

int main(int argc, char *argv[]) {
    SANITY;
    ARGUMENTS;

    dim3 block_size(H, W);
    dim3 grid_size(1);

    time_t timer;
    srand((unsigned)time(&timer));

    int **field;
    cudaMallocManaged(&field, H * sizeof(int *));
    for (int i = 0; i < H; i++)
        cudaMallocManaged(&field[i], W * sizeof(int));

    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            field[i][j] = rand() % 100 < O ? ALIVE : 0;

    display(field, H, W);

    struct timespec wait_time = {.tv_sec = REFRESH_S, .tv_nsec = REFRESH_NS};
    int r = 0, t = 0;
    while (!interrupted) {
        nanosleep(&wait_time, NULL);
        if (r++ < R * CLOCK_PER_CYCLE)
            continue;
        else
            r = 0;

        transition<<<grid_size, block_size>>>(field, H, W);
        cudaDeviceSynchronize();

        if (t++ >= T && T != -1) break;

        clear(H);
        display(field, H, W);
    }

    for (int i = 0; i < H; i++)
        cudaFree(field[i]);
    cudaFree(field);

    return 0;
}

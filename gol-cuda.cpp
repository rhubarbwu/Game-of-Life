#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "boilerplate.h"
#include "field_cuda.h"
#include "macros.h"
#include "terminal.h"

int main(int argc, char *argv[]) {
    SANITY;
    ARGUMENTS;

    time_t timer;
    srand((unsigned)time(&timer));

    int field[H * W];
    initField(field, H, W, O);

    display(field, H, W);

    struct timespec wait_time = {.tv_sec = REFRESH_S, .tv_nsec = REFRESH_NS};
    int r = 0, t = 0;
    while (!interrupted) {
        nanosleep(&wait_time, NULL);
        if (r++ < R * CLOCK_PER_CYCLE)
            continue;
        else
            r = 0;
        transition(field, H, W);
        if (t++ >= T && T != -1) break;

        clear(H);
        display(field, H, W);
    }

    return 0;
}

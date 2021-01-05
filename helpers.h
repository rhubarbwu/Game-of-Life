#define CLOCK_PER_CYCLE CLOCKS_PER_SEC / REFRESH_NS
#define REFRESH_S 0
#define REFRESH_NS 1000
#define Q 113

#define SANITY                                                                                                  \
    if (argc < 6) {                                                                                             \
        printf("usage: game-of-life <graphics-cell-width> <height> <width> <transitions> <period> [<fill>]\n"); \
        exit(1);                                                                                                \
    }                                                                                                           \
    if (signal(SIGINT, sig_handler) == SIG_ERR) {                                                               \
        printf("\ncan't catch SIGINT\n");                                                                       \
        exit(1);                                                                                                \
    }

#define ARGUMENTS                             \
    int graphics = atoi(argv[1]);             \
    int H = atoi(argv[2]), W = atoi(argv[3]); \
    int T = atoi(argv[4]);                    \
    int R = atoi(argv[5]);                    \
    int O = argc == 7 ? atoi(argv[6]) : 10;

bool interrupted = false;
void sig_handler(int signo) {
    interrupted = true;
    (void)signo;
}

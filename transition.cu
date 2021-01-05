__global__ void transition(int H, int W, bool **prev_field, bool **field) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;

    bool left = (j > 0 && prev_field[i][j - 1]);
    bool right = (j < W - 1 && prev_field[i][j + 1]);
    bool above = (i > 0 && prev_field[i - 1][j]);
    bool below = (i < H - 1 && prev_field[i + 1][j]);

    int sum = left + right + above + below;
    if (i < H && j < W)
        field[i][j] = sum / 2 == 1;
}

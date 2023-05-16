#include <stdio.h>

int main() {
    int row, column, row_max, now;
    scanf("%d%d", &row, &column);
    int row_max_index[row], column_min[column], column_min_index[column];
//    long long arr[a][b];
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j) {
            scanf("%d", &now);
            if ((0 == j) || (now > row_max)) {
                row_max = now;
                row_max_index[i] = j;
            } else if (now == row_max) {
                row_max_index[i] = -1;
            }
            if ((0 == i) || (now < column_min[j])) {
                column_min[j] = now;
                column_min_index[j] = i;
            } else if (now == column_min[j]) {
                column_min_index[j] = -1;
            }
        }
    for (int i = 0; i < row; i++) {
        if ((row_max_index[i] != -1) && (column_min_index[row_max_index[i]] == i)) {
            printf("%i %i\n", i, row_max_index[i]);
            break;
        } else if (i == row - 1) printf("none\n");
    }
    return 0;
}

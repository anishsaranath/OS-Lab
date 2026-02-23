#include <stdio.h>
int main() {
    int matrix[10][10], rows, cols, i, j;
    printf("Enter number of rows and columns: ");
    scanf("%d %d", &rows, &cols);
    printf("Enter elements of matrix:\n");
    for(i = 0; i < rows; i++) {
        for(j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("\nSum of rows:\n");
    for(i = 0; i < rows; i++) {
        int row_sum = 0;
        for(j = 0; j < cols; j++) {
            row_sum += matrix[i][j];
        }
        printf("Row %d: %d\n", i+1, row_sum);
    }
    printf("\nSum of columns:\n");
    for(j = 0; j < cols; j++) {
        int col_sum = 0;
        for(i = 0; i < rows; i++) {
            col_sum += matrix[i][j];
        }
        printf("Column %d: %d\n", j+1, col_sum);
    }
   return 0;
}

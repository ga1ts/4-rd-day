#include <stdio.h>
#include <stdlib.h>

#define MAXCOLS 100
#define MAXROWS 100

int read_type(int *type, int *rows, int *cols);
int input_matrix(int **buffer, int rows, int cols);
void output_matrix(int **buffer, int rows, int cols);
void free_array(int **buffer, int type, int cols);
void matrix_sort(int **buffer, int rows, int cols);

int main() {
    int type, cols, rows;
    int **matrix = NULL;
    int *cache_array;

    if (read_type(&type, &rows, &cols)) {  // select_array(matrix, type, rows, cols);

        // printf("Строк: %d Столбцов: %d", rows, cols);

        if (type == 1) {  // Определяем массив классическим способом
            int classic_array[MAXROWS][MAXCOLS];  // Определяем пустой массив максимального размера
                                                  // классическим способом
            int *pointers_array[MAXROWS];  // Определяем массив указателей начал строк под массив выше
            for (int i = 0; i < rows; i++) {
                pointers_array[i] = &classic_array[i][0];  // заполняем массив указателей указателями на
            }
            matrix = pointers_array;
        }

        if (type == 2) {
            matrix = (int **)malloc(MAXROWS * sizeof(int));  // Выделяем память под количество строк
            for (int i = 0; i < rows; i++)
                matrix[i] = (int *)malloc(
                    cols *
                    sizeof(
                        int));  // Выделяем память под строки, заполняем основной массив указателями на строки
        }

        if (type == 3) {
            matrix = (int **)calloc(MAXROWS, sizeof(int));  // Выделяем память под количество строк
            cache_array = (int *)calloc(rows * cols,
                                        sizeof(int));  // Создаем массив с полным выделением памяти rows*cols
            for (int i = 0; i < rows; i++)
                matrix[i] = &cache_array[i * cols];  // Заполняем основной массив указателями начал строк
        }

        if (type == 4) {
            matrix = (int **)calloc(
                MAXROWS + rows * cols,
                sizeof(int));  // Выделяем общую память под массив указателей и под массив rows*cols
            for (int i = 0; i < rows; i++)
                matrix[i] =
                    (int *)(matrix + rows + i * cols);  // Заполняем основной массив указателями начал строк
        }

        if (input_matrix(matrix, rows, cols)) {
            //            printf("\n---------\n");
            output_matrix(matrix, rows, cols);
            printf("\n");
            matrix_sort(matrix, rows, cols);
            output_matrix(matrix, rows, cols);
            if (matrix != NULL) {
                if (type != 3)
                    free_array(matrix, type, cols);
                else if (type == 3) {
                    free(cache_array);
                    free(matrix);
                } else
                    printf("n/a");
            }
        } else
            printf("n/a");
    } else
        printf("n/a");
    return 0;
}

/* Функции */

int read_type(int *type, int *rows, int *cols) {
    float cache, fcols, frows;
    int rtrn1 = 0, rtrn2 = 0, rtrn3 = 0;
    if (scanf("%f", &cache) && cache == (int)cache && cache > 0 && cache <= 4) {
        *type = (int)cache;
        rtrn1 = 1;
    } else
        return 0;  // Считываем способ выделения памяти
    if (scanf("%f", &frows) && frows == (int)frows && frows > 0 && frows <= MAXROWS) {
        *rows = (int)frows;
        rtrn3 = 1;
    } else
        return 0;  // Целое количество строк
    if (scanf("%f", &fcols) && fcols == (int)fcols && fcols > 0 && fcols <= MAXCOLS) {
        *cols = (int)fcols;
        rtrn2 = 1;
    } else
        return 0;  // Целое количество столбцов
    if (rtrn1 && rtrn2 && rtrn3)
        return rtrn1;
    else
        return 0;
}

int input_matrix(int **buffer, int rows, int cols) {
    float cache;
    for (int i = 0; i < rows; i++)
        for (int k = 0; k < cols; k++) {
            if (scanf("%f", &cache) != 1 || cache != (int)cache)
                return 0;
            else
                buffer[i][k] = (int)cache;
        }
    return 1;
}

void output_matrix(int **buffer, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int k = 0; k < cols; k++) {
            printf("%d", buffer[i][k]);
            if (k < cols - 1) printf(" ");
        }
        if (i != rows - 1) printf("\n");
    }
}

void free_array(int **buffer, int type, int cols) {
    if (type == 2) {
        for (int i = 0; i < cols; i++) free(buffer[i]);
        free(buffer);
    }
    if (type == 4) {
        free(buffer);
    }
}

void matrix_sort(int **buffer, int rows, int cols) {
    for (int z = rows; z >= 0; z--) {
        for (int i = 0; i < rows - 1; i++) {
            int *temp = buffer[i];
            int sum = 0;
            int sumnext = 0;
            for (int j = 0; j < cols; j++) {
                sum = sum + buffer[i][j];
                sumnext = sumnext + buffer[i + 1][j];
            }
            if (sumnext < sum) {
                buffer[i] = buffer[i + 1];
                buffer[i + 1] = temp;
            }
        }
    }
}

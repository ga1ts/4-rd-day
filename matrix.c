#include <stdio.h>
#include <stdlib.h>


#define MAXCOLS 100
#define MAXROWS 100

// Объявление функций
int read_type(int* type, int* rows, int* cols);
int input_matrix(int** buffer, int rows, int cols);
void output_matrix(int** buffer, int rows, int cols);
void free_array(int** buffer, int type, int cols);

int main() {
    int type, cols, rows;
    int** matrix = NULL;
    int* cache_array;

    // Считываем тип массива и размеры матрицы (строки и столбцы)
    if (read_type(&type, &rows, &cols)) {
        if (type == 1) {
            int classic_array[MAXROWS][MAXCOLS];
            int* pointers_array[MAXROWS];
            for (int i = 0; i < rows; i++) {
                pointers_array[i] = &classic_array[i][0];
            }
            matrix = pointers_array;
        }
        if (type == 2) {
            matrix = (int**)malloc(rows * sizeof(int*));
            for (int i = 0; i < rows; i++) {
                matrix[i] = (int*)malloc(cols * sizeof(int));
            }
        }
        if (type == 3) {
            matrix = (int**)calloc(rows, sizeof(int*));
            cache_array = (int*)calloc(rows * cols, sizeof(int));
            for (int i = 0; i < rows; i++) {
                matrix[i] = &cache_array[i * cols];
            }
        }

        if (type == 4) {
            matrix = (int**)malloc(rows * sizeof(int*) + rows * cols * sizeof(int));
            for (int i = 0; i < rows; i++) {
                matrix[i] = (int*)(matrix + rows + i * cols);
            }
        }

        // Ввод данных матрицы
        if (input_matrix(matrix, rows, cols)) {
            output_matrix(matrix, rows, cols);
            if (matrix != NULL) {
                if (type != 3)
                    free_array(matrix, type, cols);
                else if (type == 3) {
                    free(cache_array);
                    free(matrix);
                }
                else
                    printf("n/a");
            }
        }
        else
            printf("n/a");
    }
    else
        printf("n/a");
    return 0;
}


/* Считывает тип выделения памяти, количество строк и столбцов */
int read_type(int* type, int* rows, int* cols) {
    float cache, fcols, frows;
    int rtrn1 = 0, rtrn2 = 0, rtrn3 = 0;
    if (scanf("%f", &cache) && cache == (int)cache && cache > 0 && cache <= 4) {
        *type = (int)cache;
        rtrn1 = 1;
    }
    else
        return 0;  
    if (scanf("%f", &frows) && frows == (int)frows && frows > 0 && frows <= MAXROWS) {
        *rows = (int)frows;
        rtrn2 = 1;
    }
    else
        return 0; 
    if (scanf("%f", &fcols) && fcols == (int)fcols && fcols > 0 && fcols <= MAXCOLS) {
        *cols = (int)fcols;
        rtrn3 = 1;
    }
    else
        return 0;  
    if (rtrn1 && rtrn2 && rtrn3)
        return 1;
    else
        return 0;
}

/* Ввод элементов матрицы */
int input_matrix(int** buffer, int rows, int cols) {
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

/* Вывод матрицы */
void output_matrix(int** buffer, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int k = 0; k < cols; k++) {
            printf("%d", buffer[i][k]);  // Выводим элемент
            if (k < cols - 1) printf(" ");  // Добавляем пробел между элементами строки
        }
        if (i != rows - 1) printf("\n");  // Переход на новую строку между строками матрицы
    }
}

/* Освобождение памяти, выделенной под матрицу */
void free_array(int** buffer, int type, int cols) {
    if (type == 2) {  // Освобождение памяти при выделении построчно (тип 2)
        for (int i = 0; i < cols; i++)
            free(buffer[i]);  // Освобождаем каждую строку
        free(buffer);  // Освобождаем массив указателей
    }
    if (type == 4) {  // Освобождение памяти при гибридном выделении (тип 4)
        free(buffer);  // Освобождаем единый блок памяти
    }
}

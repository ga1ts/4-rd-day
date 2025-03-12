#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define NMAX 10

/* Прототипы функций */
int input(int *a, int n);
void output(int *a, int n);
void sort_asc(int *a, int n);

int main() {
    float ifint = 0.0;
    if (scanf("%f", &ifint) && ifint == (int)ifint && ifint >= 1 && ifint <= NMAX) {
        int *data = NULL, n = (int)ifint;  // Создаем указатель на начало массива
        data = (int *)malloc(n * sizeof(int));  // Выделяем память (кол-во ячеек * размер типа)
        if (data != NULL && input(data, n)) {
            sort_asc(data, n);
            output(data, n);
            free(data);
        } else
            printf("n/a");
    } else
        printf("n/a");

    return 0;
}

/* Функции */

void sort_asc(int *a, int n) {  // Сортировка по возрастанию
    int temp;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

/* Функция для ввода массива */
int input(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        char symbol;
        float cache;
        if (scanf("%f", &cache) != 1) return 0;  // Проверка на буквы
        if (cache != (int)cache) return 0;       // Проверка на целочисленность
        *p = (int)cache;
        symbol = getchar();
        if (symbol != ' ')
            if (symbol != '\n' && p - a == n - 1) return 0;  // Проверка на символ после элемента
    }
    return 1;
}
/* Функция для вывода массива */
void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", *a);
        a++;
    }
    printf("\n");
}

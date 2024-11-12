#include <stdio.h>  //Библиотека для работы с функциями ввода-вывода.
#include <stdlib.h> //Библиотека для функций выделения памяти, генерации случайных чисел и т.д.
#include <time.h>   //Библиотека для работы с функцией time() (создание генератора случайных чисел).
#include <ctype.h>  //Библиотека для функций обработки символов (не используется в данном коде, можно убрать).

//Функция для ввода целых положительных чисел
int getInput() {
    int num;
    while (1) { //Бесконечный цикл, который выполняется до тех пор, пока не будет получен корректный ввод.
        if (scanf("%d", &num) == 1 && num > 0) { //Проверка, что введено число и оно неотрицательное.
            return num; //Возвращаем введенное число.
        } else {
            printf("Ошибка: введите положительное целое число: "); //Сообщение об ошибке при неверном вводе.
            while (getchar() != '\n'); //Очистка буфера ввода.
        }
    }
}
int getInput_2() {
    int num;
    while (1) { //Бесконечный цикл, который выполняется до тех пор, пока не будет получен корректный ввод.
        scanf("%d", &num);
        if (num == 1 || num == 2) { //Проверка, что введено число 1 or 2.
            return num; //Возвращаем введенное число.
        } else {
            printf("Ошибка: введите числа 1 или 2: "); //Сообщение об ошибке при неверном вводе.
            while (getchar() != '\n'); //Очистка буфера ввода.
        }
    }
}
int getInput_3() {
    int num;
    while (1) { //Бесконечный цикл, который выполняется до тех пор, пока не будет получен корректный ввод.
        if (scanf("%d", &num) ==  1) { //Проверка, что введено число.
            return num; //Возвращаем введенное число.
        } else {
            printf("Ошибка: введите числа "); //Сообщение об ошибке при неверном вводе.
            while (getchar() != '\n'); //Очистка буфера ввода.
        }
    }
}

//Функция для создания матрицы и заполнения ее случайными числами или через ввод с клавиатуры
void createMatrix(int rows, int cols, int matrix[rows][cols], int random) {
    if (random) { //Если выбран режим случайного заполнения.
        srand(time(NULL)); //Созадние генератора случайных чисел на основе текущего времени.
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = rand() % 20 - 10; //Случайные числа от -10 до 9.
            }
        }
    } else { //Заполнение матрицы пользователем.
        printf("Введите элементы матрицы %dx%d:\n", rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("Элемент [%d][%d]: ", i, j);
                matrix[i][j] = getInput_3(); //Ввод элемента с проверкой.
            }
        }
    }
}

//Функция для нахождения максимального элемента и его индексов
void findMaxElement(int rows, int cols, int matrix[rows][cols], int* maxRow, int* maxCol) {
    int max = matrix[0][0]; //Создание максимального значения первым элементом матрицы.
    *maxRow = 0; //Начальные индексы строки.
    *maxCol = 0; //Начальные индексы столбца.
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] > max) { //Проверка на большее значение.
                max = matrix[i][j]; //Обновление максимального значения.
                *maxRow = i; //Сохранение индекса строки.
                *maxCol = j; //Сохранение индекса столбца.
            }
        }
    }
}

//Функция для создания матрицы B путем удаления строки и столбца с максимальным элементом
void createMatrixB(int rows, int cols, int matrixA[rows][cols], int maxRow, int maxCol, int matrixB[rows-1][cols-1]) {
    int bi = 0, bj; //Индексы для новой матрицы.
    for (int i = 0; i < rows; i++) {
        if (i == maxRow) continue; //Пропуск строки с максимальным элементом.
        bj = 0;
        for (int j = 0; j < cols; j++) {
            if (j == maxCol) continue; //Пропуск столбца с максимальным элементом.
            matrixB[bi][bj] = matrixA[i][j]; //Копирование элемента в новую матрицу.
            bj++;
        }
        bi++;//увеличиваем на 1 индексы для новой матрицы
    }
}

//Функция для печати матрицы
void printMatrix(int rows, int cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]); //Печать элемента с выравниванием по ширине.
        }
        printf("\n"); //Переход на новую строку после каждой строки матрицы.
    }
}

//Функция для подсчета количества строк, содержащих нули
int countRowsWithZeros(int rows, int cols, int matrix[rows][cols]) {
    int count = 0; // Счетчик строк с нулями.
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) { //Проверка наличия нуля в строке.
                count++; //Увеличение счетчика.
                break; //Переход к следующей строке.
            }
        }
    }
    return count; //Возвращение общего количества строк с нулями.
}

//Функция для записи главной диагонали в обратном порядке
void reverseMainDiagonal(int rows, int cols, int matrix[rows][cols]) {
    int minDim = (rows < cols) ? rows : cols; //Определение минимального размера (для квадратной части диагонали).
    for (int i = 0; i < minDim / 2; i++) {
        int temp = matrix[i][i]; //Временная переменная для обмена элементов.
        matrix[i][i] = matrix[minDim - i - 1][minDim - i - 1]; //Обмен элементов.
        matrix[minDim - i - 1][minDim - i - 1] = temp; //Завершение обмена.
    }
}

int main() {
    int rows, cols, choice;

    printf("Введите количество строк: ");
    rows = getInput(); //Ввод количества строк с проверкой.
    printf("Введите количество столбцов: ");
    cols = getInput(); //Ввод количества столбцов с проверкой.

    int matrixA[rows][cols]; //Создание матрицы A.


    
    printf("Выберите способ заполнения матрицы (1 - с клавиатуры, 2 - случайные числа): ");
    choice = getInput_2(); //Ввод выбора способа заполнения.

    createMatrix(rows, cols, matrixA, choice == 2); //Создание матрицы с выбранным способом заполнения.

    printf("Исходная матрица A:\n");
    printMatrix(rows, cols, matrixA); //Печать исходной матрицы.

    int maxRow, maxCol;
    findMaxElement(rows, cols, matrixA, &maxRow, &maxCol); //Поиск максимального элемента и его позиции.

    int matrixB[rows - 1][cols - 1]; //Создание матрицы B с уменьшенными размерами.
    createMatrixB(rows, cols, matrixA, maxRow, maxCol, matrixB); //Создание матрицы B.

    printf("\nМатрица B после удаления строки и столбца с максимальным элементом:\n");
    printMatrix(rows - 1, cols - 1, matrixB); //Печать матрицы B.

    int zeroRows = countRowsWithZeros(rows - 1, cols - 1, matrixB); //Подсчет строк с нулями.
    printf("\nКоличество строк в матрице B с нулями: %d\n", zeroRows); //Печать результата.

    reverseMainDiagonal(rows - 1, cols - 1, matrixB); //Обращение главной диагонали матрицы B.
    printf("\nМатрица B после обращения главной диагонали:\n");
    printMatrix(rows - 1, cols - 1, matrixB); //Печать измененной матрицы B.

    return 0;
}
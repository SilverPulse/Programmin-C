#include <stdio.h>   //Подключение библиотеки для функций ввода/вывода.
#include <stdlib.h>  //Подключение библиотеки для работы с памятью (malloc, free).
#include <time.h>    //Подключение библиотеки для работы с функциями времени (используется для генерации случайных чисел).

//Функция для создания матрицы с вводом с клавиатуры или случайными числами.
int** createMatrix(int rows, int cols, int random) {
    int** matrix = (int**)malloc(rows * sizeof(int));//Динамическое выделение памяти для указателей на строки матрицы.
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));//Динамическое выделение памяти для каждой строки.
    }

    //Заполнение матрицы случайными числами или через ввод с клавиатуры.
    if (random) { // Если выбран режим случайных чисел.
        srand(time(NULL)); //Создание генератора случайных чисел с использованием текущего времени.
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                //Заполнение матрицы числами от -10 до 9.
                matrix[i][j] = rand() % 20 - 10;// % 20 — оператор остатка от деления, который ограничивает полученное число диапазоном от 0 до 19. - 10 — сдвигает диапазон к отрицательным значениям, так что окончательное значение будет от -10 до 9.
            }
        }
    } else { //Если выбран ввод с клавиатуры.
        printf("Введите элементы матрицы %dx%d:\n", rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                scanf("%d", &matrix[i][j]);//Считывание элемента с клавиатуры.
            }
        }
    }

    return matrix; //Возвращение указателя на созданную матрицу.
}

// Функция для создания новой матрицы B путем удаления строки и столбца с максимальным элементом из матрицы A.
int** createMatrixB(int** matrixA, int rows, int cols, int* newRows, int* newCols) {
    int maxRow = 0, maxCol = 0; //Переменные для хранения индексов строки и столбца с максимальным элементом.
    int max = matrixA[0][0]; //Инициализация максимального значения первым элементом матрицы.

    //Поиск максимального элемента и его индексов.
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrixA[i][j] > max) { //Обновление максимума и его позиции.
                max = matrixA[i][j];
                maxRow = i;
                maxCol = j;
            }
        }
    }

    *newRows = rows - 1; //Новое количество строк после удаления одной.
    *newCols = cols - 1; //Новое количество столбцов после удаления одного.
    //Динамическое выделение памяти для новой матрицы.
    int** matrixB = (int**)malloc(*newRows * sizeof(int));
    for (int i = 0; i < *newRows; i++) {
        matrixB[i] = (int*)malloc(*newCols * sizeof(int));
    }

    //Копирование элементов из матрицы A в матрицу B, исключая строку и столбец с максимальным элементом.
    int bi = 0, bj = 0; //Индексы для новой матрицы B.
    for (int i = 0; i < rows; i++) {
        if (i == maxRow) continue; //Пропуск строки с максимальным элементом.
        bj = 0;
        for (int j = 0; j < cols; j++) {
            if (j == maxCol) continue; //Пропуск столбца с максимальным элементом.
            matrixB[bi][bj++] = matrixA[i][j]; //Копирование элемента.
        }
        bi++;
    }

    return matrixB; //Возвращение указателя на новую матрицу B.
}

//Функция для поиска строки, где все элементы по модулю меньше 10.
int findRowWithElementsLessThan10(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        int allLessThan10 = 1; //Флаг, показывающий, что все элементы в строке соответствуют условию.
        for (int j = 0; j < cols; j++) {
            if (abs(matrix[i][j]) >= 10) { //Проверка условия для элемента.
                allLessThan10 = 0; //Сброс флага, если элемент >= 10.
                break; //Прекращение проверки этой строки.
            }
        }
        if (allLessThan10) {
            return i; //Возврат индекса первой найденной строки.
        }
    }
    return -1; //Возврат -1, если такая строка не найдена.
}

//Функция для вычисления произведения элементов строки.
int productOfRow(int* row, int cols) {
    int product = 1; //Создание переменной для хранения произведения.
    for (int i = 0; i < cols; i++) {
        product *= row[i]; //Умножение элементов строки.
    }
    return product; //Возврат произведения.
}

//Функция для поиска минимального произведения среди всех строк матрицы.
int findMinProduct(int** matrix, int rows, int cols) {
    int minProduct = productOfRow(matrix[0], cols); //Начальное минимальное значение (произведение первой строки).
    for (int i = 1; i < rows; i++) {
        int product = productOfRow(matrix[i], cols); //Произведение текущей строки.
        if (product < minProduct) {
            minProduct = product; //Обновление минимального произведения.
        }
    }
    return minProduct; //Возврат минимального произведения.
}

//Функция для вывода матрицы на экран.
void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]); //Печать каждого элемента матрицы.
        }
        printf("\n"); //Переход на следующую строку.
    }
}

//Функция для освобождения памяти, выделенной под матрицу.
void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]); //Освобождение памяти каждой строки.
    }
    free(matrix); //Освобождение памяти для массива указателей.
}

int main() {
    int rows, cols, choice; //Переменные для хранения размеров матрицы и выбора способа заполнения.
    printf("Введите количество строк и столбцов матрицы: ");
    scanf("%d %d", &rows, &cols);

    printf("Выберите способ заполнения матрицы (1 - с клавиатуры, 2 - случайные числа): ");
    scanf("%d", &choice);
    int** matrixA = createMatrix(rows, cols, choice == 2); //Создание матрицы A.

    printf("Исходная матрица:\n");
    printMatrix(matrixA, rows, cols); //Вывод исходной матрицы.

    int newRows, newCols; //Переменные для хранения размеров новой матрицы.
    int** matrixB = createMatrixB(matrixA, rows, cols, &newRows, &newCols); //Создание матрицы B.

    printf("Матрица B после удаления строки и столбца с максимальным элементом:\n");
    printMatrix(matrixB, newRows, newCols); //Печать матрицы B.

    int rowWithLessThan10 = findRowWithElementsLessThan10(matrixB, newRows, newCols); //Поиск строки с элементами по модулю < 10.
    if (rowWithLessThan10 != -1) {
        int product = productOfRow(matrixB[rowWithLessThan10], newCols); //Вычисление произведения элементов этой строки.
        printf("Произведение элементов строки %d с элементами по модулю < 10: %d\n", rowWithLessThan10, product);
    } else {
        printf("Строк с элементами по модулю < 10 не найдено.\n");
    }

    int minProduct = findMinProduct(matrixB, newRows, newCols); //Нахождение минимального произведения строк.
    printf("Минимальное произведение строк: %d\n", minProduct);

    freeMatrix(matrixA, rows); //Освобождение памяти для исходной матрицы A.
    freeMatrix(matrixB, newRows); // свобождение памяти для новой матрицы B.
    return 0; //Завершение программы.
}
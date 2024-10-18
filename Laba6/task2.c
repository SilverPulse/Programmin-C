#include <stdio.h>
#include <stdbool.h>

#define SIZE 10

bool isPrime(int n) { // Функция для проверки, является ли число простым
    if (n <= 1) return false;  // Числа меньше 2 не являются простыми
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;  // Если число делится без остатка, оно не простое
    }
    return true;
}

int reverseNumber(int num) { // Функция для переворота числа
    int reversed = 0;
    while (num != 0) {
        reversed = reversed * 10 + num % 10;  // Переворачиваем число
        num /= 10;
    }
    return reversed;
}

int main() {
    int Z[SIZE] = {1234, 17, 22, 333, 7, 98, 19, 100, 23, 45};
    int Y[SIZE];


    for (int i = 0; i < SIZE; i++) {  // Копирование чисел массива Z в массив Y с их переворотом
        Y[i] = reverseNumber(Z[i]);
    }

    // Удаление простых чисел из массива Z (присваиваем -999)
    for (int i = 0; i < SIZE; i++) {
        if (isPrime(Z[i])) {
            Z[i] = -999;  // Простые числа заменяются на -999
        }
    }

    // Нахождение максимальных и минимальных элементов массивов Z и Y
    int maxZ = Z[0], minZ = Z[0];
    int maxY = Y[0], minY = Y[0];

    for (int i = 1; i < SIZE; i++) {
        // Проверка для массива Z, игнорируя элементы с значением -999
        if (Z[i] != -999) {
            if (Z[i] > maxZ) maxZ = Z[i];
            if (Z[i] < minZ) minZ = Z[i];
        }

        // Проверка для массива Y
        if (Y[i] > maxY) maxY = Y[i];
        if (Y[i] < minY) minY = Y[i];
    }

   printf("Массив Z после удаления простых чисел: ");  // Вывод массивов и их максимальных/минимальных значений
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", Z[i]);
    }
    printf("\n");

    printf("Массив Y с перевернутыми числами: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", Y[i]);
    }
    printf("\n");

    printf("Максимум Z: %d, Минимум Z: %d\n", maxZ, minZ);
    printf("Максимум Y: %d, Минимум Y: %d\n", maxY, minY);

    return 0;
}

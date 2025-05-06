#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_N 512

// Матрицы A, B, C для умножения
int A[MAX_N][MAX_N];
int B[MAX_N][MAX_N];
int C[MAX_N][MAX_N];
int N = 0, thread_count = 0;

// Мьютекс для синхронизации вывода
pthread_mutex_t mutex;

// Функция для очистки потока перед его завершением
void cleanup(void* arg) {
    printf("%s завершает работу корректно (обработчик).\n", (char*)arg);
}

// Функция потока с синхронизированным выводом
void* cleanup_thread(void* arg) {
    char* name = (char*)arg;
    pthread_cleanup_push(cleanup, name);

    // Печать строк с синхронизацией через мьютекс
    for (int i = 0; i < 5; ++i) {
        pthread_mutex_lock(&mutex);
        printf("%s: line %d\n", name, i + 1);
        pthread_mutex_unlock(&mutex);
        sleep(1); // имитация работы
    }

    pthread_cleanup_pop(1);
    return NULL;
}

// Функция для перемножения матриц с использованием потоков
void* multiply_worker(void* arg) {
    int thread_id = *(int*)arg;
    free(arg);

    int rows_per_thread = N / thread_count;
    int start_row = thread_id * rows_per_thread;
    int end_row = (thread_id == thread_count - 1) ? N : start_row + rows_per_thread;

    for (int i = start_row; i < end_row; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return NULL;
}

// Функция для вывода матрицы
void print_matrix(int m[MAX_N][MAX_N], const char* name) {
    printf("Матрица %s:\n", name);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            printf("%d ", m[i][j]);
        printf("\n");
    }
}

// Меню программы
void menu() {
    printf("\nВыберите номер задания:\n");
    printf("7 - Синхронизированный вывод\n");
    printf("8 - Перемножение квадратных матриц NxN\n");
    printf("0 - Выход\n");
    printf("Ваш выбор: ");
}

int main() {
    int choice;
    pthread_t threads[4]; // Массив для потоков
    pthread_mutex_init(&mutex, NULL); // Инициализация мьютекса

    while (1) {
        menu();
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода\n");
            while (getchar() != '\n');
            continue;
        }
        getchar(); // очистка '\n'

        if (choice == 0) break;

        if (choice == 7) {
            // Задание 7: Синхронизированный вывод
            printf("Запускаю родительский и дочерний потоки с синхронизацией...\n");

            pthread_t parent_thread, child_thread;

            // Запуск родительского потока
            pthread_create(&parent_thread, NULL, cleanup_thread, "Родитель");
            // Запуск дочернего потока
            pthread_create(&child_thread, NULL, cleanup_thread, "Дочерний");

            // Ожидание завершения потоков
            pthread_join(parent_thread, NULL);
            pthread_join(child_thread, NULL);

            printf("Оба потока завершили выполнение.\n");
        }
        else if (choice == 8) {
            // Задание 8: Перемножение матриц
            printf("Введите размер матрицы N: ");
            if (scanf("%d", &N) != 1 || N <= 0 || N > MAX_N) {
                printf("Неверный размер матрицы.\n");
                continue;
            }

            printf("Введите количество потоков: ");
            if (scanf("%d", &thread_count) != 1 || thread_count <= 0 || thread_count > N) {
                printf("Неверное количество потоков.\n");
                continue;
            }

            // Заполняем матрицы A и B единицами
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    A[i][j] = B[i][j] = 1;

            // Создание потоков для перемножения матриц
            pthread_t threads[thread_count];
            for (int i = 0; i < thread_count; ++i) {
                int* id = malloc(sizeof(int));
                *id = i;
                pthread_create(&threads[i], NULL, multiply_worker, id);
            }

            // Ожидание завершения всех потоков
            for (int i = 0; i < thread_count; ++i) {
                pthread_join(threads[i], NULL);
            }

            if (N <= 5) {
                print_matrix(A, "A");
                print_matrix(B, "B");
                print_matrix(C, "C");
            } else {
                printf("Матрицы перемножены (N = %d, threads = %d). Вывод отключён (слишком много).\n", N, thread_count);
            }
        }
        else {
            printf("Неверный выбор.\n");
        }
    }

    pthread_mutex_destroy(&mutex); // Уничтожаем мьютекс
    return 0;
}

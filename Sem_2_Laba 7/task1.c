#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_THREADS 50

// Задание 1, 2
void* child_task(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Child thread: line %d\n", i + 1);
    }
    return NULL;
}

// Задание 3
void* print_lines(void* arg) {
    char** lines = (char**)arg;
    for (int i = 0; i < 5; ++i) {
        printf("%s\n", lines[i]);
    }
    return NULL;
}

// Задание 4
void* cancellable_thread(void* arg) {
    char* name = (char*)arg;
    for (int i = 0; i < 5; ++i) {
        printf("%s: line %d\n", name, i + 1);
        sleep(1);
    }
    return NULL;
}

// Задание 5
void cleanup(void* arg) {
    printf("%s завершает работу корректно (обработчик).\n", (char*)arg);
}

void* cleanup_thread(void* arg) {
    char* name = (char*)arg;
    pthread_cleanup_push(cleanup, name);
    for (int i = 0; i < 5; ++i) {
        printf("%s: line %d\n", name, i + 1);
        sleep(1);
    }
    pthread_cleanup_pop(1);
    return NULL;
}

// Задание 6: Sleepsort (исправленная реализация)
void* sleepsort_thread(void* arg) {
    int value = *(int*)arg;
    free(arg);  // Освобождаем память
    usleep(value * 1000);  // миллисекунды
    printf("%d ", value);
    fflush(stdout);
    return NULL;
}

// Меню
void menu() {
    printf("\nВыберите номер задания:\n");
    printf("1 - Создать поток\n");
    printf("2 - Ожидание потока\n");
    printf("3 - Параметры потока\n");
    printf("4 - Завершение нити без ожидания\n");
    printf("5 - Обработка завершения потока\n");
    printf("6 - Sleepsort\n");
    printf("0 - Выход\n");
    printf("Ваш выбор: ");
}

int main() {
    int choice;
    while (1) {
        menu();
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода\n");
            while (getchar() != '\n');
            continue;
        }

        getchar(); // очистка '\n'

        if (choice == 0) break;

        if (choice == 1) {
            // Задание 1
            pthread_t thread;
            pthread_create(&thread, NULL, child_task, NULL);
            for (int i = 0; i < 5; ++i)
                printf("Parent thread: line %d\n", i + 1);
            pthread_join(thread, NULL);
        }

        else if (choice == 2) {
            // Задание 2
            pthread_t thread;
            pthread_create(&thread, NULL, child_task, NULL);
            pthread_join(thread, NULL);
            for (int i = 0; i < 5; ++i)
                printf("Parent thread: line %d\n", i + 1);
        }

        else if (choice == 3) {
            // Задание 3
            pthread_t threads[4];
            char* messages[4][5] = {
                {"T1: Line1", "T1: Line2", "T1: Line3", "T1: Line4", "T1: Line5"},
                {"T2: A", "T2: B", "T2: C", "T2: D", "T2: E"},
                {"T3: X", "T3: Y", "T3: Z", "T3: W", "T3: V"},
                {"T4: 1", "T4: 2", "T4: 3", "T4: 4", "T4: 5"}
            };

            for (int i = 0; i < 4; ++i)
                pthread_create(&threads[i], NULL, print_lines, messages[i]);

            for (int i = 0; i < 4; ++i)
                pthread_join(threads[i], NULL);
        }

        else if (choice == 4) {
            // Задание 4
            pthread_t threads[4];
            char* names[] = {"Thread1", "Thread2", "Thread3", "Thread4"};

            for (int i = 0; i < 4; ++i)
                pthread_create(&threads[i], NULL, cancellable_thread, names[i]);

            sleep(2);
            for (int i = 0; i < 4; ++i)
                pthread_cancel(threads[i]);

            for (int i = 0; i < 4; ++i)
                pthread_join(threads[i], NULL);
        }

        else if (choice == 5) {
            // Задание 5
            pthread_t threads[4];
            char* names[] = {"Thread1", "Thread2", "Thread3", "Thread4"};

            for (int i = 0; i < 4; ++i)
                pthread_create(&threads[i], NULL, cleanup_thread, names[i]);

            sleep(2);
            for (int i = 0; i < 4; ++i)
                pthread_cancel(threads[i]);

            for (int i = 0; i < 4; ++i)
                pthread_join(threads[i], NULL);
        }

        else if (choice == 6) {
            // Задание 6: Sleepsort
            int n;
            printf("Введите количество элементов (до 50): ");
            if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_THREADS) {
                printf("Ошибка: неверное количество.\n");
                while (getchar() != '\n'); // очистка
                continue;
            }

            pthread_t threads[n];

            printf("Введите элементы массива (только положительные целые числа): ");
            for (int i = 0; i < n; ++i) {
                int* value = malloc(sizeof(int));
                if (scanf("%d", value) != 1 || *value < 0) {
                    printf("Ошибка при вводе.\n");
                    free(value);
                    while (getchar() != '\n'); // очистка
                    continue;
                }
                pthread_create(&threads[i], NULL, sleepsort_thread, value);
            }

            while (getchar() != '\n'); // очистка stdin

            for (int i = 0; i < n; ++i)
                pthread_join(threads[i], NULL);

            printf("\n");
        }

        else {
            printf("Неверный выбор.\n");
        }
    }

    return 0;
}

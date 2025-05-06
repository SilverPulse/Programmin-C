Оценка 3:
#include <pthread.h>  //   Для работы с потоками (основные функции pthread)
#include <stdio.h>    //  Стандартный ввод/вывод (printf, scanf)
#include <stdlib.h>   //   Стандартная библиотека (malloc, free)
#include <unistd.h>   //Для sleep(), usleep()
#include <string.h>   //  Для работы со строками

#define MAX_THREADS 50 // Максимальное количество потоков для sleepsort

// Задание 1, 2
void* child_task(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Child thread: line %d\n", i + 1);
    }
    return NULL;
}

// Задание 3
void* print_lines(void* arg) { // Приведение void* к массиву строк
    char** lines = (char**)arg;
    for (int i = 0; i < 5; ++i) {
        printf("%s\n", lines[i]); // Печать каждой строки
    }
    return NULL;
}

// Задание 4
void* cancellable_thread(void* arg) {
    char* name = (char*)arg; // Получаем имя потока
    for (int i = 0; i < 5; ++i) {
        printf("%s: line %d\n", name, i + 1); // Печать с идентификатором
        sleep(1); // Задержка 1 сек (позволяет прервать поток)
    }
    return NULL;
}

// Задание 5
void cleanup(void* arg) {
    printf("%s завершает работу корректно (обработчик).\n", (char*)arg);
}

void* cleanup_thread(void* arg) {
    char* name = (char*)arg;
    pthread_cleanup_push(cleanup, name); // Регистрация обработчика
    for (int i = 0; i < 5; ++i) {
        printf("%s: line %d\n", name, i + 1);
        sleep(1);
    }
    pthread_cleanup_pop(1); // Вызов обработчика (1 - выполнить)
    return NULL;
}

// Задание 6: Sleepsort (исправленная реализация)
void* sleepsort_thread(void* arg) {
    int value = *(int*)arg; // Получаем значение из памяти
    free(arg);  // Освобождаем память
    usleep(value * 1000);  // Задержка пропорциональна значению (мкс)
    printf("%d ", value); // Вывод значения после задержки
    fflush(stdout); // Сброс буфера вывода
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
        if (scanf("%d", &choice) != 1) { // Проверка корректности ввода
            printf("Ошибка ввода\n");
            while (getchar() != '\n'); // Очистка буфера
            continue;
        }

        getchar(); // очистка '\n'

         // Обработка выбора пунктов меню
        if (choice == 0) break; // Выход

        if (choice == 1) {
            // Задание 1
            pthread_t thread;
            pthread_create(&thread, NULL, child_task, NULL); // Создание потока
            for (int i = 0; i < 5; ++i) // ... выполнение родительского потока ...
                printf("Parent thread: line %d\n", i + 1); // ... выполнение родительского потока ...
            pthread_join(thread, NULL); // Ожидание потока
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

оценка 4:
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

график:
![image](https://github.com/user-attachments/assets/ea8b0ae7-e4d3-45c7-884f-82f73ddb4717)



оценка 5:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define MAX_MSG_LEN 128
#define MAX_QUEUE_SIZE 10
#define MAX_CLIENTS 3
#define MAX_SERVERS 2

typedef struct message {
    char content[MAX_MSG_LEN];
    char client_name[32];
} message;

typedef struct queue {
    message messages[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int size;
    pthread_mutex_t lock;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
} queue;

// Инициализация очереди
void queue_init(queue *q) {
    q->front = q->rear = q->size = 0;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->not_full, NULL);
    pthread_cond_init(&q->not_empty, NULL);
}

// Функция производителя (клиента)
int msgSend(queue *q, const char *client_name, const char *msg) {
    pthread_mutex_lock(&q->lock);
    while (q->size >= MAX_QUEUE_SIZE)
        pthread_cond_wait(&q->not_full, &q->lock);

    message *m = &q->messages[q->rear];
    strncpy(m->content, msg, MAX_MSG_LEN - 1);
    m->content[MAX_MSG_LEN - 1] = '\0';
    strncpy(m->client_name, client_name, sizeof(m->client_name) - 1);
    m->client_name[sizeof(m->client_name) - 1] = '\0';

    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->size++;

    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->lock);
    return strlen(m->content);
}

// Функция потребителя (сервера)
int msgRecv(queue *q, char *buf, size_t bufsize, char *client_name) {
    pthread_mutex_lock(&q->lock);
    while (q->size == 0)
        pthread_cond_wait(&q->not_empty, &q->lock);

    message *m = &q->messages[q->front];
    strncpy(buf, m->content, bufsize - 1);
    buf[bufsize - 1] = '\0';
    strncpy(client_name, m->client_name, 31);
    client_name[31] = '\0';

    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    q->size--;

    pthread_cond_signal(&q->not_full);
    pthread_mutex_unlock(&q->lock);
    return strlen(buf);
}

// Глобальная очередь сообщений
queue q;

// Поток клиента
void *client_thread(void *arg) {
    char *name = (char *)arg;
    char msg[256];
    while (1) {
        snprintf(msg, sizeof(msg), "Привет от %s! Время: %ld", name, time(NULL));
        int sent = msgSend(&q, name, msg);
        printf("[КЛИЕНТ %s] Отправлено %d символов в очередь\n", name, sent);
        usleep((rand() % 3 + 1) * 500000); // 0.5–1.5 сек
    }
    return NULL;
}

// Поток сервера
void *server_thread(void *arg) {
    char buf[MAX_MSG_LEN];
    char client_name[32];
    char *name = (char *)arg;
    while (1) {
        int received = msgRecv(&q, buf, sizeof(buf), client_name);
        printf("[СЕРВЕР %s] Получено сообщение от [%s]: %s\n", name, client_name, buf);
        sleep(rand() % 3 + 1); // 1–3 сек
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    queue_init(&q);

    pthread_t clients[MAX_CLIENTS], servers[MAX_SERVERS];
    char client_names[MAX_CLIENTS][16];
    char server_names[MAX_SERVERS][16];

    printf("🚀 Запуск симуляции 'Производитель–Потребитель' с %d клиентами и %d серверами\n\n", MAX_CLIENTS, MAX_SERVERS);

    // Создание клиентов
    for (int i = 0; i < MAX_CLIENTS; i++) {
        snprintf(client_names[i], sizeof(client_names[i]), "Клиент %d", i + 1);
        pthread_create(&clients[i], NULL, client_thread, client_names[i]);
    }

    // Создание серверов
    for (int i = 0; i < MAX_SERVERS; i++) {
        snprintf(server_names[i], sizeof(server_names[i]), "Сервер %d", i + 1);
        pthread_create(&servers[i], NULL, server_thread, server_names[i]);
    }

    // Ожидание потоков (в реальности программа работает бесконечно)
    for (int i = 0; i < MAX_CLIENTS; i++)
        pthread_join(clients[i], NULL);
    for (int i = 0; i < MAX_SERVERS; i++)
        pthread_join(servers[i], NULL);

    return 0;
}

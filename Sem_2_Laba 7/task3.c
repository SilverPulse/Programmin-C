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

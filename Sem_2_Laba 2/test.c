#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
    struct node *next1;
};
typedef struct node node_t;

// Функция для добавления нового узла в список
node_t *addNewNode(node_t *head, int data_n) {
    node_t *newNode = (node_t *)malloc(sizeof(node_t));
    node_t *last = head;
    newNode->data = data_n;
    newNode->next = NULL;
    newNode->next1 = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newNode;
    }

    return head;
}

// Функция для печати списка
void printList(node_t *head) {
    node_t *last = head;
    while (last != NULL) {
        printf("%d ", last->data);
        last = last->next;
    }
    printf("\n");
}

// Функция для связывания двух списков
node_t *linkLists(node_t *head, node_t *head1) {
    node_t *current = head;   // Верхний список
    node_t *current1 = head1; // Нижний список

    if (current == NULL || current1 == NULL) {
        printf("Один из списков пуст.\n");
        return head;
    }

    // Связываем элементы двух списков один-к-одному
    while (current != NULL && current1 != NULL) {
        current1->next1 = current; // Связываем второй список с первым
        current->next1 = current1; // Связываем первый список со вторым

        // Переходим к следующим элементам
        current = current->next;
        current1 = current1->next;
    }

    // Если второй список длиннее первого, связываем оставшиеся элементы между собой
    while (current1 != NULL) {
        if (current1->next != NULL) {
            current1->next1 = current1->next; // Связываем элементы второго списка между собой
        } else {
            current1->next1 = NULL; // Последний элемент указывает на NULL
        }
        current1 = current1->next;
    }

    return head;
}

// Функция для навигации по списку
void navigateList(node_t *S) {
    node_t *current = S;  // Текущий элемент
    node_t *prev = NULL;  // Предыдущий элемент
    char input;

    while (1) {
        printf("Текущее значение: %d\n", current->data);
        printf("Введите команду (D/6 - вправо, A/4 - влево, W/8 - вверх/вниз, Q - выход): ");
        scanf(" %c", &input);

        if (input == 'D' || input == '6') { 
            if (current->next != NULL) {
                prev = current; // Сохраняем текущий элемент как предыдущий
                current = current->next; // Перемещаемся вправо
            } else {
                printf("Достигнут конец списка.\n");
            }
        } else if (input == 'A' || input == '4') { 
            if (prev != NULL) {
                current = prev; // Возвращаемся к предыдущему элементу
                prev = NULL;    // Сбрасываем предыдущий элемент
            } else {
                printf("Невозможно переместиться влево.\n");
            }
        } else if (input == 'W' || input == '8') { 
            if (current->next1 != NULL) {
                node_t *temp = current; // Сохраняем текущий элемент
                current = current->next1; // Перемещаемся вверх/вниз
                prev = temp;              // Устанавливаем предыдущий элемент
            } else {
                printf("Нет связанного элемента в этом направлении.\n");
            }
        } else if (input == 'Q' || input == 'q') { 
            break; // Выход из программы
        } else {
            printf("Неверная команда. Попробуйте снова.\n");
        }
    }
}

// Функция для освобождения памяти списка
void freeList(node_t *head) {
    node_t *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    node_t *head = NULL;  // Первый список
    node_t *head1 = NULL; // Второй список
    node_t *S;            // Указатель для навигации

    // Ввод элементов первого списка
    printf("Введите элементы первого списка (0 для завершения):\n");
    while (1) {
        int tmp;
        scanf("%d", &tmp);
        if (tmp == 0) {
            break;
        }
        head = addNewNode(head, tmp);
    }

    // Ввод элементов второго списка
    printf("Введите элементы второго списка (0 для завершения):\n");
    while (1) {
        int tmp;
        scanf("%d", &tmp);
        if (tmp == 0) {
            break;
        }
        head1 = addNewNode(head1, tmp);
    }

    S = head; 

    // Вывод содержимого списков
    printf("\nПервый список: ");
    printList(head);
    printf("Второй список: ");
    printList(head1);

    // Связывание списков
    linkLists(head, head1);

    printf("\nСписки связаны.\n");

    // Вывод содержимого списков после связывания
    printf("\nПервый список: ");
    printList(head);
    printf("Второй список: ");
    printList(head1);

    // Навигация по спискам
    navigateList(S);

    // Освобождение памяти
    freeList(head);
    freeList(head1);

    return 0;
}
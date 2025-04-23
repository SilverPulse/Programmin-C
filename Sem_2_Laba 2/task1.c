#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addNode(struct node **head, int newData) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    struct node *last = *head;
    newNode->data = newData;
    newNode->next = NULL; //новый узел будет последним, поэтому его следующий будет NULL
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    while (last->next != NULL) { 
        last = last->next;
    }

    //next последнего узла устанавливаем так,чтобы он указывал на newNode
    last->next = newNode;
}

void printList(struct node *node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    struct node *head = NULL; 
    int value;

    printf("Введите целые числа (введите 0 для завершения ввода): \n");
    
    while (1) {
        scanf("%d", &value);
        if (value == 0) {
            break;
        }
        addNode(&head, value);
    }

    printf("Содержимое списка: ");
    printList(head);
2
    struct node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}

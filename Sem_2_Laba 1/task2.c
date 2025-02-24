#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h> // для gettimeofday()

#define N 100

struct Student {
    char name[64];
    int math;
    int physics;
    int informatics;
    int total;
};

struct Student addStudent(const char *name, int math, int physics, int informatics) {
    struct Student newStudent;
    strcpy(newStudent.name, name);
    newStudent.math = math;
    newStudent.physics = physics;
    newStudent.informatics = informatics;
    newStudent.total = math + physics + informatics;
    return newStudent;
}

void printStudentInfo(struct Student student) {
    printf("Имя: %s ; Математика: %d ; Физика: %d ; Информатика: %d ; Общий балл: %d\n",
           student.name, student.math, student.physics, student.informatics, student.total);
}

//сортировка вставками (по убыванию общего балла)
void insertionSort(struct Student arr[], int size) {
    for (int i = 1; i < size; i++) {
        struct Student key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].total < key.total) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

//сортировка Counting Sort (по убыванию общего балла)
void countingSort(struct Student arr[], int size) {
    // Создаем вспомогательный массив C и инициализируем его нулями
    int *C = (int *)calloc(k, sizeof(int));
    
    // Записываем в C[i] количество чисел, равных i
    for (int i = 0; i < n; i++) {
        C[A[i]]++;
    }
    
    // Записываем в массив A числа в отсортированном порядке
    int index = 0;
    for (int number = 0; number < k; number++) {
        while (C[number] > 0) {
            A[index++] = number;
            C[number]--;
        }
    }
    
    // Освобождаем память, выделенную под массив C
    free(C);
}


//Быстрая сортировка (Quick Sort) (по убыванию общего балла)
void quickSort(struct Student arr[], int low, int high) {
    if (low < high) {
        //Выбираем опорный элемент
        int pivot = arr[high].total;
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr[j].total >= pivot) {
                i++;
                struct Student temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        //меняем опорный элемент с элементом на позиции i+1
        struct Student temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        int pi = i + 1;

        //рекурсивно сортируем левую и правую части
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


void printCPUInfo() {
    printf("\nИнформация о процессоре:\n");
    system
    ("grep 'model name' /proc/cpuinfo | uniq"); 
    system("grep 'cpu MHz' /proc/cpuinfo | uniq");
}

//функция для замера времени
double getCurrentTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

int main() {
    struct Student students[N];
    const char *names[] = {"Иван", "Мария", "Алексей", "Елена", "Дмитрий", 
                           "Ольга", "Сергей", "Анна", "Петр", "Наталья"};

    srand(time(NULL));

    //заполняем массив случайными данными
    for (int i = 0; i < N; i++) {
        int math = rand() % 101;
        int physics = rand() % 101;
        int informatics = rand() % 101;
        students[i] = addStudent(names[i % 10], math, physics, informatics);
    }

    printf("Студенты ДО сортировки:\n");
    for (int i = 0; i < N; i++) {
        printStudentInfo(students[i]);
    }

    int choice;
    printf("Выберите тип сортировки:\n");
    printf("1 - InsertSort\n");
    printf("2 - CountingSort\n");
    printf("3 - QuickSort\n");
    scanf("%d", &choice);

    
    double startTime = getCurrentTime();////////////////

    
    switch (choice) {
        case 1:
            printCPUInfo();
            insertionSort(students, N);
            break;
        case 2:
            printCPUInfo();
            countingSort(students, N);
            break;
        case 3:
            printCPUInfo(); 
            quickSort(students, 0, N - 1);
            break;
        default:
            printf("Неверный выбор,уважаемый господин!\n");
            return 1;
    }

    double endTime = getCurrentTime();///////////

    
    printf("\nВремя работы сортировки: %.6f секунд\n", endTime - startTime);

    //вывод списка после сортировки (для N <= 10)
    if (N <= 100) {
        printf("\nСтуденты ПОСЛЕ сортировки:\n");
        for (int i = 0; i < N; i++) {
            printStudentInfo(students[i]);
        }
    }

    return 0;
}
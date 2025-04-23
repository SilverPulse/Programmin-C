#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DESTINATION_LEN 50
#define FILENAME "Train.dat"

typedef struct {
    char destination[MAX_DESTINATION_LEN];
    int train_number;
    int departure_time[2]; //[часы, минуты]
} TrainRecord;


void createFile(int n) {
    FILE *file = fopen(FILENAME, "wb"); //'wb' открывает файл для записи в бинарном режиме
    if (file == NULL) {
        printf("Ошибка в содержании файла.\n");
        return;
    }

    TrainRecord record;
    for (int i = 0; i < n; i++) {
        printf("\nЗапись #%d:\n", i + 1);
        
        printf("Введите пункт назначения: ");
        scanf("%s", record.destination);
        
        printf("Введите номер поезда: ");
        scanf("%d", &record.train_number);
        
        printf("Введите время отправления (часы минуты): ");
        scanf("%d %d", &record.departure_time[0], &record.departure_time[1]);
        
        fwrite(&record, sizeof(TrainRecord), 1, file);//записываем наши структуры в файл
    }
    
    fclose(file);
    printf("Файл успешно создан с %d записями.\n", n); 
}

// Функция для поиска по указанному полю
void searchInFile() {
    FILE *file = fopen(FILENAME, "rb"); //'rb' открывает файл для чтения в бинарном режиме
    if (file == NULL) {
        printf("Файл не найден. Сначала создайте файл.\n");
        return;
    }

    int choice;
    printf("\nПо какому полю выполнить поиск?\n");
    printf("1 - Пункт назначения\n");
    printf("2 - Номер поезда\n");
    printf("3 - Время отправления\n");
    printf("Выберите поле для поиска (1-3): ");
    scanf("%d", &choice);

    TrainRecord record;
    int found = 0;//изначально флаг установлен в "не найдено"

    switch (choice) {
        case 1: { //поиск по пункту назначения
            char search_dest[MAX_DESTINATION_LEN];
            printf("Введите пункт назначения для поиска: ");
            scanf("%s", search_dest);
            
            while (fread(&record, sizeof(TrainRecord), 1, file)) { //читаем данные в бинарном режиме.блоками с файла. блоками т.е не по одной букве, а слово целиком.
                if (strcmp(record.destination, search_dest) == 0) { //strcmp - функция для ср-я 2 строк, если строки равны,возвращает 0.
                    printf("Найдено: %s, №%d, %02d:%02d\n", 
                           record.destination, record.train_number, 
                           record.departure_time[0], record.departure_time[1]); //%s подставляется строка, %d подставляется цифра,%02d:%02d подставляются два целых числа с ведущими нулямии. 0 отвечает за часы и 1 за минуты в квадратных скобках.
                    found = 1;
                }
            }
            break;
        }
        case 2: { //поиск по номеру поезда
            int search_num;
            printf("Введите номер поезда для поиска: ");
            scanf("%d", &search_num);
            
            while (fread(&record, sizeof(TrainRecord), 1, file)) {
                if (record.train_number == search_num) {
                    printf("Найдено: %s, №%d, %02d:%02d\n", 
                           record.destination, record.train_number, 
                           record.departure_time[0], record.departure_time[1]);
                    found = 1; //флаг который равен 1 если мы нашли соответвующую нашим требованиям запись
                }
            }
            break;
        }
        case 3: { // Поиск по времени отправления
            int hours, minutes;
            printf("Введите время отправления для поиска (часы минуты): ");
            scanf("%d %d", &hours, &minutes);
            
            while (fread(&record, sizeof(TrainRecord), 1, file)) {
                if (record.departure_time[0] == hours && 
                    record.departure_time[1] == minutes) {
                    printf("Найдено: %s, №%d, %02d:%02d\n", 
                           record.destination, record.train_number, 
                           record.departure_time[0], record.departure_time[1]);
                    found = 1;
                }
            }
            break;
        }
        default:
            printf("Неверный выбор.\n");
    }

    if (!found) {
        printf("Записи с указанными параметрами не найдены.\n");
    }

    fclose(file);
}

//Функция для вывода всех записей (для проверки)
void displayAllRecords() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Файл не найден.\n");
        return;
    }

    TrainRecord record;
    printf("\nВсе записи в файле:\n");
    while (fread(&record, sizeof(TrainRecord), 1, file)) {
        printf("%s, №%d, %02d:%02d\n", 
               record.destination, record.train_number, 
               record.departure_time[0], record.departure_time[1]);
    }

    fclose(file);
}

int main() {
    int n, choice;
    
    do {
        printf("\nМеню:\n");
        printf("1 - Создать новый файл с записями\n");
        printf("2 - Поиск по файлу\n");
        printf("3 - Показать все записи (для проверки)\n");
        printf("0 - Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Введите количество записей: ");
                scanf("%d", &n);
                createFile(n);
                break;
            case 2:
                searchInFile();
                break;
            case 3:
                displayAllRecords();
                break;
            case 0:
                printf("Выход из программы.\n");
                break;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 0);
    
    return 0;
}
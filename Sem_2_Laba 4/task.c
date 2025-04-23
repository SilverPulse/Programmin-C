#include <stdio.h>
#include <string.h>
#include <ctype.h>

void reverse_word(char *start, char *end) {
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

void reverse_words_in_line(char *line) {
    char *word_start = line;
    char *current = line; 

    while (*current) {
        if (isalnum((unsigned char)*current)) { 
            current++;
        } else { 
            if (word_start < current) {
                reverse_word(word_start, current - 1);
            }
            word_start = current + 1; 
            current++;
        }
    }

    if (word_start < current) {
        reverse_word(word_start, current - 1); 
    }
}

int main(int argc, char *argv[]) { //argc - количество переданных аргументов  Массив аргументов в виде строк (argv[0] — имя программы, argv[1] — первый аргумент и т. д.).
    printf( "%d" , argc); 
    if (argc < 2) { 
        printf("Использование: %s <имя файла>\n", argv[0]); 
        return 1;

    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Ошибка: Не удалось открыть файл");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) { 
        line[strcspn(line, "\n")] = '\0'; 
        
        reverse_words_in_line(line);  
        printf("%s\n", line);         
    }

    fclose(file);
    return 0;
}
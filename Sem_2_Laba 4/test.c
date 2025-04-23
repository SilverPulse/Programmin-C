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
    char *current = line;//передвигаемся по строке

    while (*current) {
        if (isalnum((unsigned char)*current)) { //символ буквенно-цифровой isalnum | unsigned char - беззнаковый тип данных.
            current++;
        } else { //обработка разделителя
            if (word_start < current) {
                reverse_word(word_start, current - 1);
            }
            word_start = current + 1;  //начало нового слова
            current++;
        }
    }

    if (word_start < current) {
        reverse_word(word_start, current - 1); //переворот последнего   слова
        }
}

int main(int ) {
    FILE *file = fopen("joke.txt", "r");
    if (file == NULL) {
        perror("Ошибка: Не удалось открыть файл");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) { //fgets читает одну строку из файла или пока не заполнит буфер а он 1024(1023 символа + /0)
        line[strcspn(line, "\n")] = '\0';//strcspn находит позицию \n в строке
        
        reverse_words_in_line(line);  
        printf("%s\n", line);         
    }

    fclose(file);
    return 0;
}
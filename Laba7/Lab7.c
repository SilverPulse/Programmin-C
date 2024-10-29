#include <stdio.h>
#include <ctype.h>
#include <string.h>

void swap(char *start, char *end) {
    char temp = *start;
    *start = *end;
    *end = temp;
}
void procWord(char *word) {
    int len = strlen(word);
    if (len > 1) {
        swap(&word[0], &word[len - 1]);
    }
}
int main() {
    char text[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    
    int i = 0;
    char word[100];
    int wordIndex = 0;

    while (text[i] != '\0') {
        if (isalnum(text[i])) { // если текущий символ является буквой или цифрой(функция isanlum возвращает True), то добавляем символ в массив word, увеличивая индекс wordIndex
            word[wordIndex++] = text[i];
        } else {
            if (wordIndex > 0) {
                word[wordIndex] = '\0';  // завершаем строку
                procWord(word);  // обрабатываем слово
                printf("%s", word);  // вывод обработанного слово
                wordIndex = 0;  // сбрасываем индекс слова
            }
            printf("%c", text[i]);  // вывод символа, не являющийся частью слова
        }
        i++;
    }

    // Обработка последнего слова, если строка не заканчивается на пробел
    if (wordIndex > 0) {
        word[wordIndex] = '\0';
        procWord(word);//если в word накопились символы (т.е собрали слово), это слово обрабатывается функцией procWord,и его символы меняются местами.
        printf("%s", word);
    }
    return 0;
}

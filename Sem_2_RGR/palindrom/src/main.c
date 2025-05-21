#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> //для поддержки локали корректной обработки кириллицы.
#include "preprocess.h"
#include "manacher.h"   
#include "utils.h"

int main(int argc, char *argv[]) { //argc — количество аргументов командной строки. argv — массив строк (аргументов), где argv[0] — имя программы, argv[1] — первый аргумент (имя файла).
    setlocale(LC_ALL, ""); // Устанавливает локаль для корректной работы с символами Юникода русскими буквами.

    if (argc != 2) { //Если аргументов меньше или больше 1 (т.е. не указан файл), выводит ошибку и завершает программу с кодом EXIT_FAILURE.
        fprintf(stderr, "Ошибка: необходимо указать имя файла.");
        return EXIT_FAILURE;
    }

    char *text = read_file(argv[1]); //read_file(argv[1]) — читает содержимое файла (имя передано в argv[1]) в строку text.
    if (!text) {
        fprintf(stderr, "Ошибка: не удалось прочитать файл. ");
        return EXIT_FAILURE;
    }

    char *cleaned = preprocess_text(text); //preprocess_text(text) — очищает текст: удаляет пробелы, знаки пунктуации, приводит буквы к одному регистру.
    if (!cleaned || strlen(cleaned) == 0) { //Если результат пуст или содержит только мусор, программа выводит ошибку, освобождает память и завершается.
        fprintf(stderr, "Ошибка: текст пуст или содержит только неалфавитные символы. ");
        free(text);
        return EXIT_FAILURE;
    }

    find_and_print_palindromes(cleaned); // использует алгоритм Манакера для поиска палиндромов в очищенном тексте и выводит их на экран.

    free(cleaned); //Освобождает память, выделенную под text и cleaned.
    free(text); //под text и
    return EXIT_SUCCESS; //Возвращает EXIT_SUCCESS (успешное завершение).
}

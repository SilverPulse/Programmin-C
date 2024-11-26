CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = program

#Объявляем все файлы
OBJ = main_function.o time_structure.o

# Сборка программы
$(TARGET): $(OBJ)
 $(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

#Компиляция main_function.c
main_function.o: main_function.c time_structure.h
 $(CC) $(CFLAGS) -c main_function.c

functions.o: time_structure.c time_structure.h
 $(CC) $(CFLAGS) -c time_structure.c

clean:
 rm -f $(OBJ) $(TARGET)

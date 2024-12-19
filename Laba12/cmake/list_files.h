// standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <dirent.h>


int
get_files_list( char * dir_path, char *** p_filenames, int * nbr_of_files );

int 
del_files_list(char ** filenames, int nbr_of_files);

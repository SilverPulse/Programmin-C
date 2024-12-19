#include <list_files.h>

int main(int argc, char * argv[]){
    
    // check input arguments only path
    if ( argc != 2 ){
        printf("illegal number of arguments!!\n");
        return 1;
    }

    // variables 
    char *  dir_path = argv[1];
    char ** files = NULL;
    int nbr_files = 0; 

    // display input arguments
    printf("%20s : %s\n", "directory path", dir_path);
    
    // get filenames
    get_files_list( dir_path, &files, &nbr_files );

    // release memory
    del_files_list( files, nbr_files ); 

    return 0;
}

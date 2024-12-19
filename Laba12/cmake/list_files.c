//
#include <list_files.h>

int
get_files_list( char * dir_path, char *** p_filenames, int * nbr_of_files ){

    // declaration
    int             i       = 0;
    DIR             * d     = NULL;
	struct dirent   * dir   = NULL;
	int             _nbr_of_files   = 0;
	char            ** filenames    = NULL;

	// open dir
	d = opendir(dir_path);
	assert( d );

	// get the number of files
    while ( (dir = readdir(d)) != NULL ){
        _nbr_of_files++;
    }

    //
    *nbr_of_files = _nbr_of_files - 2; // remove "." and ".."

    // reset the pointer
    rewinddir(d);

    // apply the memory to store filenames
    *p_filenames = (char**) malloc( sizeof(char*) * (int)(*nbr_of_files) );
    assert( *p_filenames );

    filenames = *p_filenames;
    for( i=0; i< *nbr_of_files; i++){
        // apply the memory to store filename
        filenames[i] = (char*) malloc( sizeof(char) * 256 );
        assert( filenames[i] );
        memset(filenames[i], 0x00, 256);    // initialize
    }

    // assign filename into filenames array ( filtering out the "." and ".." )
    char    *filename = NULL;
    int     is_dot = 0;
    i = 0;
    while ( (dir = readdir(d)) != NULL ){
        filename = dir->d_name;
        is_dot = ( strcmp(filename, ".") == 0 ) || ( strcmp(filename, "..") == 0 );
        if ( ! is_dot ){
            printf("(%04d) %s\n", i, filename);
            memcpy( filenames[i], filename, 256 );
            i++;
        }
    }

	//
	closedir(d);

    //
    return 0;
}

int del_files_list(char ** filenames, int nbr_of_files){

    int i = 0;
    for( i=0; i<nbr_of_files; i++){
        free(filenames[i]);
    }
    free(filenames);

    return 0;
}

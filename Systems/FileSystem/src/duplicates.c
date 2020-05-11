/* duplicates.c */

#include "hash.h"
#include "macros.h"
#include "table.h"

#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <errno.h>

/* Globals */

char * PROGRAM_NAME = NULL;

/* Structures */

typedef struct {
    bool count;
    bool quiet;
} Options;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s paths...\n", PROGRAM_NAME);
    fprintf(stderr, "    -c     Only display total number of duplicates\n");
    fprintf(stderr, "    -q     Do not write anything (exit with 0 if duplicate found)\n");
    exit(status);
}

/**
 * Check if path is a directory.
 * @param       path        Path to check.
 * @return      true if Path is a directory, otherwise false.
 */
bool is_directory(const char *path) {
    struct stat temp; 
    bool status = !stat(path, &temp ) && S_ISDIR(temp.st_mode);
    
    return status;
}

/**
 * Check if file is in table of checksums.
 *
 *  If quiet is true, then exit if file is in checksums table.
 *
 *  If count is false, then print duplicate association if file is in
 *  checksums table.
 *
 * @param       path        Path to file to check.
 * @param       checksums   Table of checksums.
 * @param       options     Options.
 * @return      0 if Path is not in checksums, otherwise 1.
 */
size_t check_file(const char *path, Table *checksums, Options *options) {
 
    //Value val = {.string=(char*)path};  
    
    char newHex[HEX_DIGEST_LENGTH]; 

    bool hash = hash_from_file(path, newHex); 

    if(hash){
        // OH: Use Value and table_search to index through table and see if hex digest is in checksums 

        Value *table = table_search(checksums, newHex); 
       
        Value temp; 
        temp.string = strdup(path);  


        table_insert(checksums, newHex, temp, STRING); 
        free(temp.string); 

        //Value *table = table_search(checksums, newHex); 

        if(options->count && table){
            return 1; 
        }

        if((options->quiet && table)){
            exit(0); 
        }
        
       if(!options->count && table){
            printf("%s is a duplicate of%s\n", path, table->string);
            return 1; 
        }

        
         return 0; 
    }
    else{
        return EXIT_FAILURE; 
    }

}

/**
 * Check all entries in directory (recursively).
 * @param       root        Path to directory to check.
 * @param       checksums   Table of checksums.
 * @param       options     Options.
 * @return      Number of duplicate entries in directory.
 */
size_t check_directory(const char *root, Table *checksums, Options *options) {
    int c = 0; //count 

    DIR *directory = opendir(root); 


    if(directory){
        for(struct dirent *i = readdir(directory); i; i = readdir(directory)){
            if( strcmp(i->d_name, ".") == 0 || strcmp( i->d_name, "..") == 0){
                continue; 
            }
        
            char new[strlen(root)+strlen(i->d_name)+2]; 
            sprintf(new, "%s/%s", root, i->d_name); 

        
            if(is_directory(new)){ 
                c =  c+ check_directory(new, checksums, options); 
            }
            else{
                c = c + check_file(new, checksums, options); 
            }
    
        }
    
        closedir(directory);    
        return c; 
    }
    else{
        fprintf(stderr, "%s\n", strerror(errno)); 
        return EXIT_FAILURE; 
    }

}

/* Main Execution */

int main(int argc, char *argv[]) {
    /* Parse command line arguments */
    Options status = {0}; 
    int total = 0; 
    int argNum = 1; 

     for (int flag =1; ( argNum < argc  && strlen(argv[argNum]) > 1 && argv[argNum][0] == '-'); flag++) { 
        if(!strcmp(argv[argNum], "-q")){
            status.quiet = true; 
        }
        else if(!(strcmp(argv[argNum], "-c"))){
            status.count = true; 
        }
        else if(!(strcmp(argv[argNum], "-h"))){
            usage(0); 
        }
        else{
            usage(1); 
        }
        argNum++; 
    }
            

    /* Check each argument */
     
    Table *temp = table_create(0); 

    while (argNum < argc){
        if(is_directory(argv[argNum])){
            total += check_directory(argv[argNum], temp, &status); 
        }
        else{
            total += check_file(argv[argNum], temp, &status); 
        }
        argNum++; 
    }
     

    /* Display count if necessary */

    table_delete(temp); 
    if(status.count){
        printf("%d\n", total); 
    }
    
    if(status.quiet){
        if(total>0){
            exit(0); 
        }
        else{
            exit(1); 
        }
    }

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

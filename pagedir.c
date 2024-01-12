#include "pagedir.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

/**
 * Initializes the page directory so that webpages can be saved in it.
 * Returns true if initialization succeeded, false otherwise.
 */

bool pagedir_init(const char *pageDirectory) {
    DIR *dir = opendir(pageDirectory);

    if(dir){
        /* here we initialize the web crawler data in the directory*/

        char *string = malloc(sizeof(char) * (strlen(pageDirectory) + 10));
        /* checking if the memory allocation is successful*/
        if(string == NULL){
            closedir(dir);
            return false;
        }

        /* concatenate the string toward the crawler function */

        sprintf(string, "%s/.crawler", pageDirectory);

        /* opening string file */
        FILE *fp = fopen(string, "w");
        free(string);

        /*close the directory*/
        closedir(dir);
        fclose(fp);
        return true;
    }
    return false;
}
	// Fill in with your implementation


/**
 * Saves a given webpage to a given page directory with a given document ID.
 */
void pagedir_save(const webpage_t *page, const char *pageDirectory, const int documentID) {
    DIR *dir = opendir(pageDirectory);

    if(dir){
        /*allocate memory to the string*/
        char *string = malloc(sizeof(char) * (strlen(pageDirectory) + sizeof(documentID) + 1));
        /*checking if memory allocation is successful*/
        if (string == NULL){
            closedir(dir);
            return;
        }
        sprintf(string, "%s/%d", pageDirectory, documentID);

        /* creating the file*/
        FILE *fp = fopen(string, "w");
        //printf("saved %s\n", string);
        // tells us that creating the file failed*/
        if(fp == NULL){
            perror(" Creating the File failed.");
            free(string);
            closedir(dir);
            return;
        }

        /*writes the webpage data(url, depth, html) into the file*/
        fprintf(fp,"%s\n%d\n%s\n", page->url, page->depth, page->html);

        // frees memory and closes the directory//
        free(string);
        fclose(fp);
        closedir(dir);
    }
}
	// Fill in with your implementation

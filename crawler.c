#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
// libraries
//
// nexter files
#include "pagedir.h"
#include "url.h"
#include "crawler.h"
#include "curl.h"

/**
 * Parses command-line arguments, placing the corresponding values into the pointer arguments seedURL,
 * pageDirectory and maxDepth. argc and argv should be passed in from the main function.
 */

/*additional functions*/
static void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen);

static void parseArgs(const int argc, char *argv[], char **seedURL, char **pageDirectory, int *maxDepth) {
    /* returns if the criteria is met, else exit program with non-zero value, and prints an error to stderr*/
    /* the purpose or parsing the argument is to extract information from the HTML content*/

    /* check the amount of arguments */
    if(argc < 3){
        fprintf(stderr, "Invalid amount of Arguments \n");
        exit(1);
    }

    /*initialize page directory*/
    if(pagedir_init(argv[2])){
        *pageDirectory = argv[2];
    } else{
        fprintf(stderr, "Page Directory Error");
        exit(1);
    }

    /* convert and validate the max depth */

    int depthVal = atoi(argv[3]);
    if( depthVal >= 0 && depthVal <= 10){
        *maxDepth =  depthVal;
    } else {
        fprintf(stderr, "maxDepth is out of bounds");
        exit(1);
    }

    /* set the seedURL */
    *seedURL = argv[1];
}

/**
 * Crawls webpages given a seed URL, a page directory and a max depth.
 */
static void crawl(char *seedURL, char *pageDirectory, const int maxDepth) {
    hashtable_t *pagesSeen = hashtable_new(20);
    hashtable_insert(pagesSeen, seedURL, seedURL);

    bag_t *pagesToCrawl = bag_new();

    webpage_t *seed = malloc(sizeof(webpage_t));
    if(seed == NULL){
        exit(EXIT_FAILURE);
    }
    seed->url = strdup(seedURL);
    seed->depth = 0;

    bag_insert(pagesToCrawl, seed);


    int doc_id = 1;

    while(pagesToCrawl->length > 0){
        webpage_t *pull = bag_remove(pagesToCrawl);
        printf("%d\n", pagesToCrawl->length);
        //fetch the HTML from the webpage
        pull->html = download(pull->url, &pull->length);
        //if fetching the HTML was successful
        if(pull->html != NULL){
            //save the webpage to the directory
            pagedir_save(pull, pageDirectory, doc_id);
            doc_id++;
            //if the webpage is not at maxDepth
            if(pull->depth < maxDepth){
                //pageScan that HTML
                pageScan(pull, pagesToCrawl, pagesSeen);
            }
            free(pull->html);
        }
        //delete that webpage
        if(pull->url != seedURL){
            free(pull->url);
        }
        free(pull);
        sleep(1);

    }
    hashtable_delete(pagesSeen, NULL);
    bag_delete(pagesToCrawl, NULL);
    //free(seed->url);
    //free(seed);
}

/**
 * Scans a webpage for URLs.
 */
static void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen){
    //while there is another url in the page:
    char *html = page->html;
    char *newURL = strstr(html, "<a ");
    if(newURL == NULL){
        return;
    }
    char* endURL = strstr(newURL, ">");
    if(endURL == NULL){
        return;
    }
    *endURL = '\0';
    
    html = endURL + 1;
    //newURL += 6;
    while(true){
        newURL = strstr(newURL, "href=\"");
        if(newURL == NULL){
            newURL = strstr(html, "<a ");
            if(newURL == NULL){
                return;
            }
            endURL = strstr(newURL, ">");
            if(endURL == NULL){
                return;
            }
            *endURL = '\0';
            html = endURL + 1;
            continue;
        }
        newURL += 6;
        //printf("%s\n", newURL);
        endURL = strstr(newURL, "\"");
        if(endURL == NULL){
            exit(EXIT_FAILURE);
        }
        *endURL = '\0';
        //printf("%s\n", newURL);
        char* ign = strstr(newURL, "#");
        if(ign != NULL){
            *ign = '\0';
            if(ign == newURL){
                newURL = strstr(html, "<a ");
            
                if(newURL == NULL){
                    return;
                }
                endURL = strstr(newURL, ">");
                if(endURL == NULL){
                    return;
                }
                *endURL = '\0';
                html = endURL + 1;
                continue;
            }
        }
        newURL = normalizeURL(page->url, newURL);
        /*if that URL is internal*/
        if(isInternalURL(page->url,newURL)){ 
            /*newURL = normalizeURL(page->url, newURL);*/
            /*insert the webpage into the hashtable*/
            if(hashtable_insert(pagesSeen, newURL, newURL)){
                webpage_t *newPee = (webpage_t *)malloc(sizeof(webpage_t));
                newPee->depth = page->depth + 1;
                newPee->url = newURL;
                /*insert the webpage into the bag*/
                bag_insert(pagesToCrawl, newPee);
                    /*bag_print(pagesToCrawl);*/
            }
            //free(newURL);
        }
        //free(newURL);
        newURL = strstr(html, "<a ");
        if(newURL == NULL){
            return;
        }
        //printf("blah\n");
        endURL = strstr(newURL, ">");
        if(endURL == NULL){
            return;
        }
        else *endURL = '\0';
        //printf("%s\n", newURL);
        html = endURL + 1;
        //newURL += 6;
        
    }
    free(newURL);
}

int main(const int argc, char *argv[]) {
    /* parses arguments and initializes other modules */
   char *seedURL;
   char *pageDirectory;
   int maxDepth;

   parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);
   crawl(seedURL, pageDirectory, maxDepth);

  return 0; 
}

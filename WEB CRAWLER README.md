The Web crawler is a standalone program that crawls the web and retrieves web pages starting from a “seed” URL. It parses the seed webpage, extracts any embedded URLs, then retrieves each of those pages, recursively, but limiting its exploration to a given “depth”.
The crawler will run as follows:

parse the command line, validate parameters, initialize other modules

add seedURL to the bag of webpages to crawl, marked with depth=0

add seedURL to the hashtable of URLs seen so far

while there are more web pages in the bag:

   extract a webpage (URL,depth) item from the bag

   pause for one second

   use pagefetcher to retrieve a web page for that URL

   use pagesaver to write the web page to the pageDirectory with a unique document ID

   if the webpage depth is < maxDepth, explore the webpage to find the links it contains:

       use pagescanner to parse the web page to extract all its embedded URLs

       for each extracted URL:

        normalize the URL (per requirements spec)

        if that URL is internal (per requirements spec):

            try to insert that URL into the *hashtable* of URLs seen;

                if it was already in the table, do nothing;

                if it was added to the table:

                    create a new webpage for that URL, marked with depth+1

                    add that new webpage to the bag of webpages to be crawled
 

Control flow
The Crawler is implemented in one file crawler.c, with four functions.

1. main
The main function simply calls parseArgs and crawl, then exits zero.

2. parseArgs
Given arguments from the command line, extract them into the function parameters; return only if successful.

for pageDirectory, call pagedir_init()
for maxDepth, ensure it is an integer in specified range [0 … 10]
if any trouble is found, print an error to stderr and exit non-zero.
3. crawl
Do the real work of crawling from seedURL to maxDepth and saving pages in pageDirectory. Pseudocode:

initialize the hashtable and add the seedURL

initialize the bag and add a webpage representing the seedURL at depth 0

while bag is not empty:

   pull a web page from the bag

   fetch the HTML for that web page

   if fetch was successful:

       save the web page to pageDirectory

       if the web page is not at maxDepth:

           pageScan that HTML

   delete that web page

delete the hashtable

delete the bag
4. pageScan
This function implements the pagescanner mentioned in the design. Given a web page, scan the given page to extract any links (URLs), ignoring non-internal URLs; for any URL not already seen before (i.e., not in the hashtable), add the URL to both the hashtable pages_seen and to the bag pages_to_crawl. Pseudocode:

while there is another URL in the page:

 if that URL is internal:

   insert the webpage into the hashtable

   if that succeeded:

     create a webpage_t for it

     insert the webpage into the bag

 free the URL
Your pagescanner should extract URLs from links in the webpages' HTML. It's sufficient for this assignment to assume all links are of the format <a href="url">, where url varies. That is, your code should scan for occurrences of <a href="url"> (again, the url part varies) and extract the contained URLs so they can be crawled. Note that link targets come in multiple types: absolute, domain-relative and page-relative. https://en.wikipedia.org/wiki/Dog is an absolute URL, /wiki/Dog is a domain-relative URL and Dog is a page-relative URL. Your page scanner will have to normalize domain-relative and page-relative URLs by expanding them to a full absolute URL. For example, if the current page is http://example.com/foo/bar, /baz should be expanded to http://example.com/baz and quux should be expanded to http://example.com/foo/quux. We have provided code that does this for you in url.c.

Modules from past assignments can be used
Examples: hashtable, set.

Function prototypes
crawler
See crawler.c for explanations.

int main(const int argc, char* argv[]);

static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);

static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);

static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);
pagedir
See pagedir.h for explanations.

bool pagedir_init(const char* pageDirectory);

void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);

how to compile my code for example:

./crawler https://engineering,ucsc.edu/ daweb 2

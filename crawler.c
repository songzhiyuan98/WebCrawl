#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <regex.h>


#include "crawler.h"
#include "curl.h"
#include "pagedir.h"
#include "hashtable.h"
#include "bag.h"
#include "webpage.h"
#include "url.h"
#include <string.h>

/**
 * Parses command-line arguments, placing the corresponding values into the pointer arguments seedURL,
 * pageDirectory and maxDepth. argc and argv should be passed in from the main function.
 */

int globalDocumentIDCounter = 2; //counter id

static void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen);//declare before
										   
static void parseArgs(const int argc, char *argv[], char **seedURL, char **pageDirectory, int *maxDepth)
{
	// determine whether has correct number of parameters
	if (argc != 4)
	{
		fprintf(stderr, "Parameters Error");
		exit(1);
	}

	// assign to pointers
	*seedURL = normalizeURL(argv[1],argv[1]);
	*pageDirectory = argv[2];
	*maxDepth = atoi(argv[3]);

	// determine whether the maxDepth is correct range
	if (*maxDepth < 0 || *maxDepth > 10)
	{
		fprintf(stderr, "Error, MaxDepth has to be in range (0,10)");
		exit(1);
	}

	// determine directory inilized correctly
	if (!pagedir_init(*pageDirectory))
	{
		fprintf(stderr, "Error, pageDirectory initializing failed");
		exit(1);
	}
}

/**
 * Crawls webpages given a seed URL, a page directory and a max depth.
 */
// crawl function
static void crawl(char *seedURL, char *pageDirectory, const int maxDepth)
{
    // Check if seedURL is NULL
    if (seedURL == NULL)
    {
        fprintf(stderr, "Error: seedURL is NULL\n");
        return;  // or exit(1)
    }

    hashtable_t *pagesSeen = hashtable_new(200);
    hashtable_insert_with_id(pagesSeen, seedURL, 1); // one is the initialized id for seedurl

    // create webpage for seedurl
    bag_t *pagesToCrawl = bag_new(); //create a bag structure
    webpage_t *seedPage = webpage_create(seedURL, NULL, 0, 0); 
    bag_insert(pagesToCrawl, seedPage); 

    // when bag is not empty, enter the loop
    while (!bag_is_empty(pagesToCrawl)) //determine whether the bag is empty
    {
        // based on FIFO, extract the front node
        webpage_t *currentPage = bag_extract(pagesToCrawl); //store the node in the new webpage_t
	printf(" Fetched: %s\n", currentPage->url);

        // sleep for one second
        sleep(1);

        // extract HTML from the webpage_t
	size_t len = 0;
	currentPage->html = download(currentPage->url, &len);
	currentPage->length = len;
       	//downlaod HTML from by curl.h

        // if HTML extract sucessfully
        if (currentPage->html != NULL)
        {
            // output URL, depth, HTML to the certain Files
            webpage_save(currentPage, pageDirectory, hashtable_get_document_id(pagesSeen, currentPage->url)); 

            // if do not arrive the max depth
            if (currentPage->depth < maxDepth)
            {
		//scan the page and get urls
                printf("Calling pageScan\n");
		pageScan(currentPage, pagesToCrawl, pagesSeen);
            }

            // delete webpage used before
            webpage_delete(currentPage);
        }
        else
        {
            // Handle the case where download failed
            fprintf(stderr, "Error downloading page: %s\n", currentPage->url);
	    webpage_delete(currentPage); 
        }
    }

    // the loop end the hashtable is empty
    // delete hashtable
    hashtable_delete(pagesSeen);

    // delete bag
    bag_delete(pagesToCrawl);
}



//Scan function to scan the webpage and add to hashtable and bag
static void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen){
	printf(" %d Scanning: %s\n", page->depth, page->url); 
	char *html = page->html;
	regex_t regex;
	regmatch_t matches[2];
	const char *pattern = "<a[^>]*href=\"([^\"]*)\"[^>]*>";

	if (regcomp(&regex, pattern, REG_EXTENDED) != 0){
		fprintf(stderr, "Failed to compile regular expression\n");
		return;
	}

	while (regexec(&regex, html, 2, matches, 0) == 0){
		int length = matches[1].rm_eo - matches[1].rm_so;
		char *temp = strndup(html + matches[1].rm_so, length);

		char *found = normalizeURL(page->url,temp);
		free(temp);
		printf(" %d Found: %s\n",page->depth,found);
		if(isInternalURL(page->url, found)){
			if (hashtable_insert_with_id(pagesSeen, found, globalDocumentIDCounter)) // starting from id two
				{
					// if webpage ws inserted successfully
					webpage_t *newPage = webpage_create(found, NULL, 0, page->depth + 1); //depth + one
					globalDocumentIDCounter++;//count id + one
					// add the new page into the bag
					bag_insert(pagesToCrawl, newPage);
					free(found);
			}
		}
		else{
			printf(" %d IgnExtrn: %s\n", page->depth, found);
		}
		html += matches[1].rm_eo;
	}
}



int main(const int argc, char *argv[])
{
    char *seedURL;
    char *pageDirectory;
    int maxDepth;

    // initialized the parameter
    parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);

    // start the crawl
    crawl(seedURL, pageDirectory, maxDepth);

    return 0; // exit successfully
}


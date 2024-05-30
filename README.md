WebCrawl
Introduction
This project is a web crawler implemented in C. The crawler fetches web pages, parses them to extract URLs, and stores the data. The project is modular and includes several components, each responsible for different aspects of the crawling process.

Project Structure
The project is organized into the following files:

bag.c and bag.h: Implements a bag data structure used to store URLs or other data.

crawler.c and crawler.h: Contains the main logic for the web crawler, including URL fetching and parsing.

curl.c and curl.h: Provides wrapper functions around the libcurl library to simplify HTTP requests.

hashtable.c and hashtable.h: Implements a hashtable data structure used to store and quickly lookup URLs.

pagedir.c and pagedir.h: Manages the storage and retrieval of web pages from the disk.

url.c and url.h: Contains functions for URL manipulation, such as normalization and validation.

webpage.c and webpage.h: Defines the structure of a webpage and provides functions to create, delete, and manipulate web pages.

Makefile: Build instructions for the project.

Dependencies
libcurl: A free and easy-to-use client-side URL transfer library, supporting various protocols including HTTP and HTTPS.

Installation
To build and run this project, you need to have gcc and libcurl installed on your system.

Installing libcurl
On Debian-based systems (e.g., Ubuntu):

sh
Copy code
sudo apt-get update
sudo apt-get install libcurl4-openssl-dev
Building the Project
Navigate to the project directory and run:

sh
Copy code
make
This will compile the source files and produce the executable.

Usage
To run the web crawler, use the following command:

sh
Copy code
./crawler <seedURL> <pageDirectory> <maxDepth>
<seedURL>: The starting URL for the crawler.
<pageDirectory>: The directory where fetched web pages will be stored.
<maxDepth>: The maximum depth to which the crawler will fetch pages.
Code Overview
bag.c and bag.h
Implements a simple bag data structure that can store arbitrary items. This is used for temporarily storing URLs before they are processed.

crawler.c and crawler.h
Contains the main logic for the web crawler. This includes functions to fetch pages, parse them for links, and store the pages.

curl.c and curl.h
Provides a simplified interface to the libcurl library for performing HTTP requests. This includes functions to initialize a curl handle, fetch a webpage, and clean up resources.

hashtable.c and hashtable.h
Implements a hashtable data structure for storing URLs. This helps in quickly checking if a URL has already been visited by the crawler.

pagedir.c and pagedir.h
Manages the storage of web pages on disk. This includes functions to save a webpage to a file and read a webpage from a file.

url.c and url.h
Contains functions for URL manipulation. This includes normalizing URLs, validating URLs, and extracting the hostname from a URL.

webpage.c and webpage.h
Defines the structure of a webpage and provides functions to create, delete, and manipulate web pages. This includes storing the URL, the HTML content, and the depth of the page in the crawl.

Contributing
If you would like to contribute to this project, please fork the repository and submit a pull request. Issues and feature requests are welcome.

License
This project is licensed under the MIT License. See the LICENSE file for details.

Acknowledgements
This project uses the libcurl library for HTTP requests. Thank you to the developers of libcurl for their excellent work.

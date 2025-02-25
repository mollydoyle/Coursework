/* spidey: Simple HTTP Server */

#include "spidey.h"

#include <errno.h>
#include <stdbool.h>
#include <string.h>

#include <unistd.h>

/* Global Variables */
char *Port	      = "9898";
char *MimeTypesPath   = "/etc/mime.types";
char *DefaultMimeType = "text/plain";
char *RootPath	      = "www";

/**
 * Display usage message and exit with specified status code.
 *
 * @param   progname    Program Name
 * @param   status      Exit status.
 */
void usage(const char *progname, int status) {
    fprintf(stderr, "Usage: %s [hcmMpr]\n", progname);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    -h            Display help message\n");
    fprintf(stderr, "    -c mode       Single or Forking mode\n");
    fprintf(stderr, "    -m path       Path to mimetypes file\n");
    fprintf(stderr, "    -M mimetype   Default mimetype\n");
    fprintf(stderr, "    -p port       Port to listen on\n");
    fprintf(stderr, "    -r path       Root directory\n");
    exit(status);
}

/**
 * Parse command-line options.
 *
 * @param   argc        Number of arguments.
 * @param   argv        Array of argument strings.
 * @param   mode        Pointer to ServerMode variable.
 * @return  true if parsing was successful, false if there was an error.
 *
 * This should set the mode, MimeTypesPath, DefaultMimeType, Port, and RootPath
 * if specified.
 */
bool parse_options(int argc, char *argv[], ServerMode *mode) {

    int argind = 1;

    while (argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-') {

        char *arg = argv[argind++];

    	switch (arg[1]) {
	    case 'c':
	    	if (streq(argv[argind], "single")) {
	    	    *mode = SINGLE;
                } else if (streq(argv[argind], "forking")) {
	    	    *mode = FORKING;
	    	} else {
	    	    return false;
	    	}
	    	argind++;
	    	break;
	    case 'h':
	    	usage(argv[0], EXIT_SUCCESS);
	    	break;
	    case 'm':
	    	MimeTypesPath = argv[argind++];
	    	break;
	    case 'M':
	    	DefaultMimeType = argv[argind++];
	    	break;
	    case 'p':
	    	Port = argv[argind++];
	    	break;
	    case 'r':
	    	RootPath = argv[argind++];
	    	break;
	    default:
	        return false;
	    	break;
	}
    }

    return true;
}

/**
 * Parses command line options and starts appropriate server
 **/
int main(int argc, char *argv[]) {

    /* Default Mode is SINGLE */
    ServerMode mode = SINGLE;

    /* Parse command line options */
    bool success = parse_options(argc, argv, &mode);

    if (!success) {
        return EXIT_FAILURE;
    }

    /* Listen to server socket */
    int server_fd = socket_listen(Port);
    if(server_fd < 0){
       return EXIT_FAILURE; 
    } 

    /* Determine the real path of RootPath */
    char buffer[BUFSIZ];
    RootPath = realpath(RootPath, buffer);

    /* Determine real RootPath */
    log("Listening on port %s", Port);
    debug("RootPath        = %s", RootPath);
    debug("MimeTypesPath   = %s", MimeTypesPath);
    debug("DefaultMimeType = %s", DefaultMimeType);
    debug("ConcurrencyMode = %s", mode == SINGLE ? "Single" : "Forking");

    int status;

    /* Start either forking or single HTTP server */
    if (mode == SINGLE) {
       status = single_server(server_fd); 
    }
    else {
        status = forking_server(server_fd);
    }
    
    return status;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */

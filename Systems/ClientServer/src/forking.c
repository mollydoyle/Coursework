/* forking.c: Forking HTTP Server */

#include "spidey.h"

#include <errno.h>
#include <signal.h>
#include <string.h>

#include <unistd.h>

/**
 * Fork incoming HTTP requests to handle the concurrently.
 *
 * @param   sfd         Server socket file descriptor.
 * @return  Exit status of server (EXIT_SUCCESS).
 *
 * The parent should accept a request and then fork off and let the child
 * handle the request.
 **/
int forking_server(int sfd) {
    /* Accept and handle HTTP request */
    while (true) {
    	/* Accept request */
        Request *r;
        
        r = accept_request(sfd);

        if (!r) {
            debug("Unable to allocate request: %s", strerror(errno));
            continue;
        }

	/* Ignore children */

        signal(SIGCHLD, SIG_IGN);

	/* Fork off child process to handle request */
        pid_t pid = fork();

        if (pid < 0) { 
            /* Error */
            fprintf(stderr, "Unable to fork: %s\n", strerror(errno));
            free_request(r);
        }
        else if (pid == 0) {
            /* Child Process */
            Status result;
            result = handle_request(r);
            free_request(r);
            exit(result);

        }
        else {
            /* Parent Process */
            free_request(r);
        }
    }

    /* Close server socket */
    close(sfd);
    return EXIT_SUCCESS;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */

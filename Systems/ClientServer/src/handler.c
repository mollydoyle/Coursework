/* handler.c: HTTP Request Handlers */

#include "spidey.h"

#include <errno.h>
#include <limits.h>
#include <string.h>

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

/* Internal Declarations */
Status handle_browse_request(Request *request);
Status handle_file_request(Request *request);
Status handle_cgi_request(Request *request);
Status handle_error(Request *request, Status status);

/**
 * Handle HTTP Request.
 *
 * @param   r           HTTP Request structure
 * @return  Status of the HTTP request.
 *
 * This parses a request, determines the request path, determines the request
 * type, and then dispatches to the appropriate handler type.
 *
 * On error, handle_error should be used with an appropriate HTTP status code.
 **/
Status  handle_request(Request *r) {

    Status result;

    int errorStatus;

    /* Parse request */
    errorStatus = parse_request(r);

    if (errorStatus == -1) {
        result = handle_error(r, HTTP_STATUS_BAD_REQUEST);
        goto fail;
    }

    /* Determine request path */
    r->path = determine_request_path(r->uri);
    debug("HTTP REQUEST PATH: %s", r->path);

    /* Dispatch to appropriate request handler type based on file type */
    struct stat s;
    if (stat(r->path, &s) == 0) {

        if (S_ISDIR(s.st_mode)) {
            /* Directory */
            debug("HTTP REQUEST TYPE: BROWSE");
            result = handle_browse_request(r);
        }
        else if (S_ISREG(s.st_mode)) {
            /* Executable */
            if (access(r->path, X_OK) == 0) {
                debug("HTTP REQUEST TYPE: CGI");
                result = handle_cgi_request(r);
            }
            /* File */
            else if (access(r->path, R_OK) == 0) {
                debug("HTTP REQUEST TYPE: FILE");
                result = handle_file_request(r);
            }
            else {
                result = handle_error(r, HTTP_STATUS_INTERNAL_SERVER_ERROR);
                goto fail;
            }
        }
        else {
            result = handle_error(r, HTTP_STATUS_INTERNAL_SERVER_ERROR);
            goto fail;
        }
    }
    else {
        result = handle_error(r, HTTP_STATUS_NOT_FOUND);
        goto fail;
    }

    /* Success */
    log("HTTP REQUEST STATUS: %s", http_status_string(result));
    return result;

fail:
    log("HTTP REQUEST STATUS: %s", http_status_string(result));
    return result;
}

/**
 * Handle browse request.
 *
 * @param   r           HTTP Request structure.
 * @return  Status of the HTTP browse request.
 *
 * This lists the contents of a directory in HTML.
 *
 * If the path cannot be opened or scanned as a directory, then handle error
 * with HTTP_STATUS_NOT_FOUND.
 **/
 Status  handle_browse_request(Request *r) {
     struct dirent **entries;
     int n;

     /* Open a directory for reading or scanning */
     n = scandir(r->path, &entries, 0, alphasort);

     if (n < 0) {
         return handle_error(r, HTTP_STATUS_NOT_FOUND);
     }

     /* Write HTTP Header with OK Status and text/html Content-Type */
     fprintf(r->stream, "HTTP/1.0 200 OK\r\n");
     fprintf(r->stream, "Content-Type: text/html\r\n");
     fprintf(r->stream, "\r\n");

     /* For each entry in directory, emit HTML list item */
     fprintf(r->stream, "<ul>\n");
     char fullpath[BUFSIZ];

     /* Bootstrap */
     fprintf(r->stream, "<h1>Client Server Project</h1>");
     fprintf(r->stream, "<h3>Team Members: Molly Doyle and Chase Saca</h3>");
     fprintf(r->stream, "<style>body { background-image: url(\"https://i.picsum.photos/id/1056/3988/2720.jpg\"); }\n.well { margins: 20px 50px 0px 50px; } </style>");
     fprintf(r->stream, "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\" integrity=\"sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u\" crossorigin=\"anonymous\">");
     fprintf(r->stream, "</head><body><ul class=\"well\" style=\"margin: 10px 50px 10px 50px;\">");

     /* Iterate through directory */
     for (int i = 0; i < n; i++) {

         if (strcmp(entries[i]->d_name,".") == 0) {
             free(entries[i]);
             continue;
         }

         if (strcmp(r->uri, "/") == 0) {
             sprintf(fullpath, "%s%s", r->uri, entries[i]->d_name);
         } else {
             sprintf(fullpath, "%s/%s", r->uri, entries[i]->d_name);
         }

         /* List directory/file link */
         fprintf(r->stream, "<li><a href=\"%s\">%s</a></li>\n", fullpath, entries[i]->d_name);
         free(entries[i]);

    }

     free(entries);
     fprintf(r->stream, "</ul>\n");

     /* Return OK */
     return HTTP_STATUS_OK;
 }


/**
 * Handle file request.
 *
 * @param   r           HTTP Request structure.
 * @return  Status of the HTTP file request.
 *
 * This opens and streams the contents of the specified file to the socket.
 *
 * If the path cannot be opened for reading, then handle error with
 * HTTP_STATUS_NOT_FOUND.
 **/
Status  handle_file_request(Request *r) {
    FILE *fs;
    char buffer[BUFSIZ];
    char *mimetype = NULL;
    size_t nread;

    /* Open file for reading */
    fs = fopen(r->path, "r");
    if (!fs) {
        fclose(fs);
        free(mimetype);
        return handle_error(r, HTTP_STATUS_NOT_FOUND);
    }

    /* Determine mimetype */
    mimetype = determine_mimetype(r->path);

    /* Write HTTP Headers with OK status and determined Content-Type */
    fprintf(r->stream, "HTTP/1.0 200 OK\r\n");
    fprintf(r->stream, "Content-Type: %s\r\n", mimetype);
    fprintf(r->stream, "\r\n");

    /* Read from file and write to socket in chunks */
    nread = fread(buffer, 1, BUFSIZ, fs);

    while (nread > 0) {
        fwrite(buffer, 1, nread, r->stream);
        nread = fread(buffer, 1, BUFSIZ, fs);
    }

    /* Close file, deallocate mimetype, return OK */
    fclose(fs);
    free(mimetype);
    return HTTP_STATUS_OK;

}

/**
 * Handle CGI request
 *
 * @param   r           HTTP Request structure.
 * @return  Status of the HTTP file request.
 *
 * This popens and streams the results of the specified executables to the
 * socket.
 *
 * If the path cannot be popened, then handle error with
 * HTTP_STATUS_INTERNAL_SERVER_ERROR.
 **/
Status  handle_cgi_request(Request *r) {
    FILE *pfs;
    char buffer[BUFSIZ];

    /* Export CGI environment variables from request:
     * http://en.wikipedia.org/wiki/Common_Gateway_Interface */
    setenv("DOCUMENT_ROOT", RootPath, 1);
    setenv("QUERY_STRING", r->query, 1);
    setenv("REMOTE_ADDR", r->host, 1);
    setenv("REMOTE_PORT", r->port, 1);
    setenv("REQUEST_METHOD", r->method, 1);
    setenv("REQUEST_URI", r->uri, 1);
    setenv("SCRIPT_FILENAME", r->path, 1);
    setenv("SERVER_PORT", Port, 1);


    /* Export CGI environment variables from request headers */

    for (Header *currheader = r->headers; currheader; currheader = currheader->next) {

        if (strcmp(currheader->name, "Host") == 0) {
            setenv("HTTP_HOST", currheader->data, 1);
        } else if (strcmp(currheader->name, "User-Agent") == 0) {
            setenv("HTTP_USER_AGENT", currheader->data, 1);
        } else if (strcmp(currheader->name, "Accept") == 0) {
            setenv("HTTP_ACCEPT", currheader->data, 1);
        } else if (strcmp(currheader->name, "Accept-Language") == 0) {
            setenv("HTTP_ACCEPT_LANGUAGE", currheader->data, 1);
        } else if (strcmp(currheader->name, "Accept-Encoding") == 0) {
            setenv("HTTP_ACCEPT_ENCODING", currheader->data, 1);
        } else if (strcmp(currheader->name, "Connection") == 0) {
            setenv("HTTP_CONNECTION", currheader->data, 1);
        }

    }

    /* POpen CGI Script */
    pfs = popen(r->path,"r");

    if (!pfs) {
        debug("CGI Request: could not popen\n");
        return handle_error(r, HTTP_STATUS_INTERNAL_SERVER_ERROR);
    }

    /* Copy data from popen to socket */
    size_t nread;
    nread = fread(buffer, 1, BUFSIZ, pfs);

    while (nread > 0) {
        fwrite(buffer, 1, nread, r->stream);
        nread = fread(buffer, 1, BUFSIZ, pfs);
    }

    /* Close popen, return OK */
    pclose(pfs);
    return HTTP_STATUS_OK;
}

/**
 * Handle displaying error page
 *
 * @param   r           HTTP Request structure.
 * @return  Status of the HTTP error request.
 *
 * This writes an HTTP status error code and then generates an HTML message to
 * notify the user of the error.
 **/
Status  handle_error(Request *r, Status status) {
    const char *status_string = http_status_string(status);

    /* Write HTTP Header */
    fprintf(r->stream, "HTTP/1.0 %s\r\n", status_string);
    fprintf(r->stream, "Content-Type: text/html\r\n");
    fprintf(r->stream, "\r\n");

    /* Write HTML Description of Error */
    /* Bootstrap */
    fprintf(r->stream, "<h1> %s </h1>", status_string);
    fprintf(r->stream, "<style>body { background-image: url(\"https://i.picsum.photos/id/1056/3988/2720.jpg\"); }\n.well { margins: 20px 50px 0px 50px; } </style>");
    fprintf(r->stream, "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\" integrity=\"sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u\" crossorigin=\"anonymous\">");
    fprintf(r->stream, "<br><img src=\"https://i.kym-cdn.com/entries/icons/original/000/019/749/catroomguardian.JPG\">");

    /* Return specified status */
    return status;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */

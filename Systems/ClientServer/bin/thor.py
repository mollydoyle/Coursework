#!/usr/bin/env python3

import concurrent.futures
import os
import requests
import sys
import time


# Functions

def usage(status=0):
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname} [-h HAMMERS -t THROWS] URL
    -h  HAMMERS     Number of hammers to utilize (1)
    -t  THROWS      Number of throws per hammer  (1)
    -v              Display verbose output
    ''')
    sys.exit(status)


def hammer(url, throws, verbose, hid):
    ''' Hammer specified url by making multiple throws (ie. HTTP requests).

    - url:      URL to request
    - throws:   How many times to make the request
    - verbose:  Whether or not to display the text of the response
    - hid:      Unique hammer identifier

    Return the average elapsed time of all the throws.
    '''
    elapsed = .0 

    for item in range(throws):
        start = time.time() 
        
        response = requests.get(url)
        
        total = time.time() - start
        elapsed = elapsed + total 

        if(verbose):
            print(response.text)

        print(f"Hammer: {hid}, Throw:\t{item}, Elapsed Time: {total:>.2f}")

    avg = elapsed / throws 

    print(f"Hammer: {hid}, AVERAGE: \t , Elapsed Time: {avg:>.2f}")
        
    return avg


def do_hammer(args):
    ''' Use args tuple to call `hammer` '''
    return hammer(*args)


def main():
    hammers = 1
    throws  = 1
    verbose = False
    url = ''

    # Parse command line arguments
   
    arguments = sys.argv[1:]

    if len(arguments)==0:
        usage(1)

    while arguments:
        arg = arguments.pop(0)
        if arg == '-h':
            try: 
                hammers = int(arguments.pop(0))
            except: 
                usage(1)
        elif arg == '-t':
            try: 
                throws = int(arguments.pop(0))
            except:
                usage(1)
        elif arg == '-v':
            verbose = True
        elif len(arguments) > 0:
            usage(1)
    
    elapsed = 0
    url=arg

    # Create pool of workers and perform throws
    workers = ((url, throws, verbose, hid) for hid in range(hammers))

    with concurrent.futures.ProcessPoolExecutor(hammers) as executor:
        averageTime = executor.map(do_hammer, workers)

    for time in averageTime:
        elapsed += time

    avg = elapsed / hammers
    print(f"TOTAL AVERAGE ELAPSED TIME: {avg:>.2f}")
    

# Main execution

if __name__ == '__main__':
    main()

# vim: set sts=4 sw=4 ts=8 expandtab ft=python:

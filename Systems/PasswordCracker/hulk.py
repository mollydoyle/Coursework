#!/usr/bin/env python3

import concurrent.futures
import hashlib
import os
import string
import sys

# Constants

ALPHABET = string.ascii_lowercase + string.digits

# Functions

def usage(exit_code=0):
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname} [-a ALPHABET -c CORES -l LENGTH -p PATH -s HASHES]
    -a ALPHABET Alphabet to use in permutations
    -c CORES    CPU Cores to use
    -l LENGTH   Length of permutations
    -p PREFIX   Prefix for all permutations
    -s HASHES   Path of hashes file''')
    sys.exit(exit_code)

def md5sum(s):
    ''' Compute md5 digest for given string. '''
    # TODO: Use the hashlib library to produce the md5 hex digest of the given
    # string.

    newMD = hashlib.md5(s.encode())
    return newMD.hexdigest()

def permutations(length, alphabet=ALPHABET):
    ''' Recursively yield all permutations of the given length using the
    provided alphabet. '''
    # TODO: Use yield to create a generator function that recursively produces
    # all the permutations of the given length using the provided alphabet.
    if length == 1: # base case 
        yield from alphabet
    else: 
        for element in alphabet: 
            for p in permutations(length-1, alphabet): # recursive calls 
                p = element + p 
                yield p 

def flatten(sequence):
    ''' Flatten sequence of iterators. '''
    # TODO: Iterate through sequence and yield from each iterator in sequence.
    for i in sequence: 
        yield from i

def crack(hashes, length, alphabet=ALPHABET, prefix=''):
    ''' Return all password permutations of specified length that are in hashes
    by sequentially trying all permutations. '''
    # TODO: Return list comprehension that iterates over a sequence of
    # candidate permutations and checks if the md5sum of each candidate is in
    # hashes.


    perms = permutations(length, alphabet)
    perms = (prefix + p for p in perms)
    return[p for p in perms if md5sum(p) in hashes] #checks each number of hashes if md5 hex digest is equal to any of the permutations 
       

def cracker(arguments):
    ''' Call the crack function with the specified arguments '''
    return crack(*arguments)

def smash(hashes, length, alphabet=ALPHABET, prefix='', cores=1):
    ''' Return all password permutations of specified length that are in hashes
    by concurrently subsets of permutations concurrently.
    '''
    # TODO: Create generator expression with arguments to pass to cracker and
    # then use ProcessPoolExecutor to apply cracker to all items in expression.
    arguments = ((hashes, length-1, alphabet, prefix+letter) for letter in alphabet) # organizes argument tuples following the prefic amoung the specified number of cores 

    #splits argument tuples between different cores 
    with concurrent.futures.ProcessPoolExecutor(cores) as executor: 
       return flatten(executor.map(cracker, arguments))



def main():
    arguments   = sys.argv[1:]
    alphabet    = ALPHABET
    cores       = 1
    hashes_path = 'hashes.txt'
    length      = 1
    prefix      = ''

    # TODO: Parse command line arguments

    while arguments and arguments[0].startswith('-'):
            a = arguments.pop(0)

            if a == '-a':
                alphabet = arguments.pop(0)
            elif a == '-c':
                cores = int(arguments.pop(0))
            elif a == '-l':
                length = int(arguments.pop(0))
            elif a == '-p':
                prefix = arguments.pop(0)
            elif a == '-s':
                hashes = arguments.pop(0)
            elif a == '-h':
                usage(0)
            else:
                usage(1)


    # TODO: Load hashes set
    hash_set = set([line.strip() for line in open(hashes_path)])

    # TODO: Execute crack or smash function

    if cores == 1 or length == 1: 
        passwords = crack(hash_set, length, alphabet, prefix)
    else: 
        passwords = smash(hash_set, length, alphabet, prefix, cores)

    # TODO: Print all found passwords
    
    for x in passwords: 
        print(x)

# Main Execution

if __name__ == '__main__':
    main()

# vim: set sts=4 sw=4 ts=8 expandtab ft=python:

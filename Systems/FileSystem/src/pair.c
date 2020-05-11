/* pair.c: Key/Value Pair */

#include "pair.h"

#include <stdlib.h>
#include <string.h>

/**
 * Create Pair structure.
 * @param   key             Pair's key.
 * @param   value           Pair's value.
 * @param   next            Reference to next pair.
 * @param   type            Pair's value's type.
 * @return  Allocated Pair structure.
 */
Pair *	    pair_create(const char *key, const Value value, Pair *next, Type type) {
    Pair *generated  = calloc(1, sizeof(Pair)); 
   
    generated->type = NUMBER; 
    generated->key = strdup(key); 
    
    generated->next = next; 

    pair_update(generated, value, type); 

    return generated; 

}

/**
 * Delete Pair structure.
 * @param   p               Pair structure.
 * @param   recursive       Whether or not to delete remainder of pairs.
 * return   NULL.
 */
Pair *	    pair_delete(Pair *p, bool recursive) {
    if(p){
        
        if(p->next && recursive){
            pair_delete(p->next, recursive); 
        }
        
        if(p->type == STRING){
            free(p->value.string); 
        }
        

     

        free(p->key); 

        free(p); 
    }
    
    return NULL;
}

/**
 * Update Pair's value.
 * @param   p               Pair structure.
 * @param   value           New value for Pair.
 * @param   type            New value's type.
 */
void        pair_update(Pair *p, const Value value, Type type) {
    if(p){
        if(p->type == STRING){
            free(p->value.string); 
        }

        p->type = type; 

        if(type == STRING){
            p->value.string = strdup(value.string); 
        }
        else{
            p->value.number = value.number; 
        }
    }

}

/**
 * Format Pair by writing to stream.
 * @param   p               Pair structure.
 * @param   stream          File stream to write to.
 */
void        pair_format(Pair *p, FILE *stream) {
    if(p){
        if(p->type == STRING){
            fprintf(stream, "%s\t%s\n", p->key, p->value.string); 
        }
        else{
            fprintf(stream, "%s\t%ld\n", p->key, p->value.number); 
        }
    }
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

/* table.c: Separate Chaining Hash Table */

#include "table.h"
#include "hash.h"
#include "macros.h"

/**
 * Create Table data structure.
 * @param   capacity        Number of buckets in the hash table.
 * @return  Allocated Table structure.
 */
Table *	    table_create(size_t capacity) {
    // all callocs
    Table *new = calloc(1, sizeof(Table)); 

    new->size = 0;
    
    if(new){
        if(capacity> 0) {
           new->capacity = capacity; 
        }
        else{
            new->capacity = DEFAULT_CAPACITY; 
        }

        new->buckets = calloc(new->capacity, sizeof(Pair));  
    
        return new; 
    }
    else{
        return NULL; 
    }
}

/**
 * Delete Table data structure.
 * @param   t               Table data structure.
 * @return  NULL.
 */
Table *	    table_delete(Table *t) {
    if(t){
        for ( size_t i = 0; i < t->capacity; i++){
        
            pair_delete(t->buckets[i].next, true); 
    
        }
    
        free(t->buckets); 
        free(t); 
    }

    return NULL;
}

/**
 * Insert or update Pair into Table data structure.
 * @param   m               Table data structure.
 * @param   key             Pair's key.
 * @param   value           Pair's value.
 * @param   type            Pair's value's type.
 */
void        table_insert(Table *t, const char *key, const Value value, Type type) {
    
    uint64_t hash = hash_from_data(key, strlen(key)) % (t->capacity); 
     
    Pair *temp = &t->buckets[hash]; 
    if(temp){
        //for(Pair *temp = t->buckets[hash].next; temp; temp=temp->next){    scoping issues? 
        while(temp->next){
            temp = temp->next; 
            if(streq(key, temp->key)==true){
                pair_update(temp, value, type); 
                return; 
            }   
        //temp=temp->next; 
        }
    

    
        temp->next = pair_create(key, value, NULL, type); 
        t->size++; 
    }
    
 
}

/**
 * Search Table data structure by key.
 * @param   t               Table data structure.
 * @param   key             Key of the Pair to search for.
 * @return  Pointer to the Value associated with specified key (or NULL if not found).
 */
Value *     table_search(Table *t, const char *key) {
    
    uint64_t hash = hash_from_data(key, strlen(key)) % (t->capacity); 

    Pair *target = t->buckets[hash].next; 
    
    if(target){
        
        while(target){
        //for(Pair *target = t->buckets[hash].next; target; target=target->next){   scoping ? 
            if( streq(key, target->key)==1){
                return &(target->value); 
            }

            target = target->next; 
        }
    }
    
    return NULL;
    
}

/**
 * Remove Pair from Table data structure with specified key.
 * @param   t               Table data structure.
 * @param   key             Key of the Pair to remove.
 * return   Whether or not the removal was successful.
 */
bool        table_remove(Table *t, const char *key) {
    
    uint64_t hash = hash_from_data(key, strlen(key)) % t->capacity; 



    Pair *target = t->buckets[hash].next;
    
    if(target){
        
        Pair *loc = &t->buckets[hash]; 
         
        while(target){
            if(streq(key, target->key)==true){

                loc->next = target->next; 
                pair_delete(target, false); 
                t->size--; 

                return true; 
            }

        
            loc = target; 
            target = target->next;
        // loc = target;

        }
    }
    return false;
}

/**
 * Format all the entries in the Table data structure.
 * @param   m               Table data structure.
 * @param   stream          File stream to write to.
 */
void	    table_format(Table *t, FILE *stream) {
   if(t){ 
        for(size_t i = 0; i < t->capacity; i++){
        
            for(Pair *tab = t->buckets[i].next; tab; tab= tab->next){
            
                pair_format(tab, stream); 
        
            }
    
        }
   }
        
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

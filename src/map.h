#ifndef _MAP_H
#define _MAP_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE  100 // max number of elements


typedef struct hash_map hash_map;

//create hash map
hash_map* hm_create(void);

//free the memory allocated for the hashmap
void hm_destroy(hash_map* map);

//return the item for the given key value
//return NULL if not found
void* hm_get(hash_map* map, const char* key);


//set the item with given key to give non-NULL value
const char* hm_set(hash_map* map, const char* key, void* value);

//return the number of items in a hashtable
size_t hm_length(hash_map* map);

//hash_map iterator
typedef struct{
    const char* currKey;
    void* currValue;

    hash_map* map;   
    size_t currIndex;  
}hash_map_iterator;

//return new hash_map iterator
hash_map_iterator hm_iterator(hash_map* map);

//move to the next entry in the hash_table
bool hm_next(hash_map_iterator* hmit);
#endif

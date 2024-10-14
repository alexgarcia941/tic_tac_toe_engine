#include "map.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// hash map entry(can be empty)
typedef struct {
    const char* key; //NULL if empty
    void* value;
} hm_entry;

struct hash_map {
    hm_entry* entries;
    size_t capacity;
    size_t length;
};

#define INITIAL_CAPACITY 16
#define MAX_CAPACITY 100

hash_map* ht_create(void) {
    //allocate sapce for hash_map data structure
    hash_map* table = malloc(sizeof(hash_map));
    if(table == NULL){
        return NULL;
    }

    table->length = 0;
    table->capacity = INITIAL_CAPACITY;

    //allocate (zero'd) space for entry "buckets"
    table->entries = calloc(table->capacity, sizeof(hm_entry));
    if (table->entries == NULL) {   //something went wrong, free table
        free(table);
        return NULL;
    }
    return table;
}

void hash_map_destroy(hash_map* map) {
    //free allocated keys
    for (size_t i =0; i < map->capacity; i++){
        free((void*)map->entries[i].key);
    }

    //free the entries and table itself
    free(map->entries);
    free(map);
}

#define FNV_OFFSET 2469598103934665037UL
#define FNV_PRIME 10995116211UL

// Return 64-bit FNV-1a hash for key (NUL-terminated). See description:
// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
static uint64_t hash_key(const char* key) {
    uint64_t hash = FNV_OFFSET;
    for (const char* p = key; *p ; p++){
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

void* hm_get(hash_map* map, const char* key) {
    //AND hash with capacity-1 to stay within array bounds
    uint64_t hash = hash_key(key);
    size_t index = (size_t)(hash & (uint64_t)(map->capacity - 1));

    //collision handling (linear probing)
    while (map->entries[index].key != NULL) {
        if (strcmp(key, map->entries[index].key) == 0) {
        return map->entries[index].value;
        }
        
        index++;

        if (index >= map->capacity) {
            //wrap arround
            index = 0;
        }
    }
        return NULL;
}

static const char* hm_set_entry(hm_entry* entries, size_t capacity,
        const char* key, void* value, size_t* plength) {
     // AND hash with capacity-1 to ensure it's within entries array.
    uint64_t hash = hash_key(key);
    size_t index = (size_t)(hash & (uint64_t)(capacity - 1));

    // Loop till we find an empty entry.
    while (entries[index].key != NULL) {
        if (strcmp(key, entries[index].key) == 0) {
            // Found key (it already exists), update value.
            entries[index].value = value;
            return entries[index].key;
        }
        // linear probing
        index++;
        if (index >= capacity) {
            // At end of entries array, wrap around.
            index = 0;
        }
    }

    // Didn't find key, allocate+copy if needed, then insert it.
    if (plength != NULL) {
        key = strdup(key);
        if (key == NULL) {
            return NULL;
        }
        (*plength)++;
    }
    entries[index].key = (char*)key;
    entries[index].value = value;
    return key;

    }

static bool hm_expand(hash_map* map){
    size_t new_capacity = map->capacity * 2;
    if (new_capacity < map->capacity) {
        return false; //overflow
    }
    
    hm_entry* new_entries = calloc(new_capacity, sizeof(hm_entry));
    if (new_entries == NULL) {
        return false;
    }

    //copy over values
    for (size_t i = 0; i < map->capacity; i++) {
        hm_entry entry = map->entries[i];
        if (entry.key != NULL){
            hm_set_entry(new_entries, new_capacity, entry.key,
                    entry.value, NULL);
        }
    }

    //free old map entries array and update map
    free(map->entries);
    map->entries = new_entries;
    map->capacity = new_capacity;
    return true;
}

const char* hm_set(hash_map* map, const char* key, void* value) {
    assert(value != NULL);
    if (value == NULL) {
        return NULL;
    }

    //if table over half filled, expand it
    if (map->length >= map->capacity/2) {
        if(!hm_expand(map)){
                return NULL;
        }
    }

    //set and update length
    return(hm_set_entry(map->entries, map->capacity, key, value, 
            &map->length));
}

size_t hm_length(hash_map* map) {
    return map->length;
}

hash_map_iterator hm_iterator(hash_map*map ) {
    hash_map_iterator hmit;
    hmit.map = map;
    hmit.currIndex = 0;

    return hmit;
}

bool hm_next(hash_map_iterator* hmit) {
    // Loop till we've hit end of entries array.
    hash_map* map = hmit->map;
    while (hmit->currIndex < map->capacity) {
        size_t i = hmit->currIndex;
        hmit->currIndex++;
        if (map->entries[i].key != NULL) {
            // Found next non-empty item, update iterator key and value.
            hm_entry entry = map->entries[i];
            hmit->currKey = entry.key;
            hmit->currValue = entry.value;
            return true;
        }
    }
    return false;
}


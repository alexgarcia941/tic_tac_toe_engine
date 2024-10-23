#include "../src/map.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdlib.h>
#include <criterion/criterion.h>

#define MAX_CAPACITY 128
//make sure map is being initialized correctly
Test(test_init, init_destroy_map){
    hash_map* map = hm_create();
    cr_assert_not_null(map);
    hm_destroy(map);
}

Test(test_set, fill_tree_max){
    hash_map* map = hm_create();
    char buffer[7];
    for (int i = 0; i < /*MAX_CAPACITY/2*/ 50 ; i++ ){
        sprintf(buffer, "Node%d", i);
        int val = i;
        printf("%d",val);

        hm_set(map, buffer, &val);
    }
    printf("About to destroy map\n");
    hm_destroy(map);
}

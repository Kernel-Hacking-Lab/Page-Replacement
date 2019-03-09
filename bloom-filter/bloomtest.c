#include<iostream>
#include<stdlib.h>
#include "bloom.h"
#include<unistd.h>

int main(){
    struct bloom bloom;
    bloom_init(&bloom, 900, 0.01);
    bloom.ready = 1;

    sleep(1);

    int val = 10;

    bloom_add(&bloom, &val, 4);

    if (bloom_check(&bloom, &val, 4)) {
        printf("It may be there!\n");
    }

    for(int i = 0; i < 100; i++){
        val = i;
        bloom_add(&bloom, &val, 4);
    }

    for(int i = 101; i < 120; i++){
        val = i;
        if (bloom_check(&bloom, &val, 4)) {
            printf("%d may be there!\n", val);
        }
    }

}
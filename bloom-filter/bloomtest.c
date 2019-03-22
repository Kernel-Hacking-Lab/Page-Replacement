#include<iostream>
#include<stdlib.h>
#include "bloom.h"
#include<unistd.h>

int main(){
    struct bloom bloom;
    bloom_init(&bloom, 1000, 0.1);
    bloom.ready = 1;

    printf("Number of bits = %d\n", bloom.bits);

    int val = 10;

    bloom_add(&bloom, &val, 4);

    if (bloom_check(&bloom, &val, 4)) {
        printf("It may be there!\n");
    }

    for(int i = 0; i < 100; i++){
        val = i;
        bloom_add(&bloom, &val, 4);
    }

    for(int i = 101; i < 1000000; i++){
        val = i;
        if (bloom_check(&bloom, &val, 4)) {
            printf("%d may be there!\n", val);
        }
    }

}
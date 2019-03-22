#include<iostream>
#include<stdlib.h>
#include "counting_bloom.h"
#include<unistd.h>

int main(){
    struct bloom bloom;
    bloom_init(&bloom, 1000, 0.1);
    bloom.ready = 1;

    printf("Number of shorts = %d\n", bloom.shorts);

    int val = 10;

    bloom_add(&bloom, &val, 4);

    printf("Freq of %d is %d\n", val, bloom_check(&bloom, &val, 4));


    for(int i = 0; i < 100; i++){
        val = i;
        bloom_add(&bloom, &val, 4);
        bloom_add(&bloom, &val, 4);
    }

    for(int i = 0; i < 200; i++){
        val = i;
        printf("Freq of %d is %d\n", val, bloom_check(&bloom, &val, 4));
    }

}
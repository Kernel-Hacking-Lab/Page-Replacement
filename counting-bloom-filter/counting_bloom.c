/*
 *  Copyright (c) 2012-2019, Jyri J. Virkki
 *  All rights reserved.
 *
 *  This file is under BSD license. See LICENSE file.
 */

/*
 * Refer to bloom.h for documentation on the public interfaces.
 */

#include <assert.h>
#include <fcntl.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "counting_bloom.h"
#include "murmurhash2.h"

#define MAKESTRING(n) STRING(n)
#define STRING(n) #n


int short_add(unsigned short * buf,
                                   unsigned int x)
{
  buf[x] += 1;        // expensive memory access
  return 1;
}


int bloom_add(struct bloom * bloom,
                           const void * buffer, int len)
{
  if (bloom->ready == 0) {
    printf("bloom at %p not initialized!\n", (void *)bloom);
    return -1;
  }

  register unsigned int a = murmurhash2(buffer, len, 0x9747b28c);
  register unsigned int b = murmurhash2(buffer, len, a);
  register unsigned int x;
  register unsigned int i;

//   printf("Add hashes %d, %d\n", a, b);
  for (i = 0; i < bloom->hashes; i++) {
    x = (a + i*b) % bloom->shorts;
    short_add(bloom->bf, x);
  }

  return 1;
}

int bloom_check(struct bloom * bloom,
                           const void * buffer, int len)
{
  if (bloom->ready == 0) {
    printf("bloom at %p not initialized!\n", (void *)bloom);
    return -1;
  }

  register int estimate = 0;
  register unsigned int a = murmurhash2(buffer, len, 0x9747b28c);
  register unsigned int b = murmurhash2(buffer, len, a);
  register unsigned int x;
  register unsigned int i;
//   printf("Check hashes %d, %d\n", a, b);

  for (i = 0; i < bloom->hashes; i++) {
    x = (a + i*b) % bloom->shorts;
    estimate =+ bloom->bf[x];
  }

  return estimate;
}

int bloom_init(struct bloom * bloom, int entries, double error)
{
  bloom->ready = 0;

  if (entries < 1000 || error == 0) {
    return 1;
  }

  bloom->entries = entries;
  bloom->error = error;

  double num = log(bloom->error);
  double denom = 0.480453013918201; // ln(2)^2
  bloom->spe = -(num / denom);

  double dentries = (double)entries;
  bloom->shorts = (int)(dentries * bloom->spe);

  bloom->hashes = (int)ceil(0.693147180559945 * bloom->spe);  // ln(2)

  bloom->bf = (unsigned short *)calloc(bloom->shorts, sizeof(unsigned short));
  if (bloom->bf == NULL) {                                   // LCOV_EXCL_START
    return 1;
  }                                                          // LCOV_EXCL_STOP

  bloom->ready = 1;
  return 0;
}


void bloom_print(struct bloom * bloom)
{
  printf("bloom at %p\n", (void *)bloom);
  printf(" ->entries = %d\n", bloom->entries);
  printf(" ->error = %f\n", bloom->error);
  printf(" ->shorts = %d\n", bloom->shorts);
  printf(" ->shorts per elem = %f\n", bloom->spe);
  printf(" ->hash functions = %d\n", bloom->hashes);
}


void bloom_free(struct bloom * bloom)
{
  if (bloom->ready) {
    free(bloom->bf);
  }
  bloom->ready = 0;
}


int bloom_reset(struct bloom * bloom)
{
  if (!bloom->ready) return 1;
  memset(bloom->bf, 0, bloom->shorts);
  return 0;
}


const char * bloom_version()
{
  return MAKESTRING(BLOOM_VERSION);
}

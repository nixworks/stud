/**
  * Copyright 2011 Bump Technologies, Inc. All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without modification, are
  * permitted provided that the following conditions are met:
  *
  *    1. Redistributions of source code must retain the above copyright notice, this list of
  *       conditions and the following disclaimer.
  *
  *    2. Redistributions in binary form must reproduce the above copyright notice, this list
  *       of conditions and the following disclaimer in the documentation and/or other materials
  *       provided with the distribution.
  *
  * THIS SOFTWARE IS PROVIDED BY BUMP TECHNOLOGIES, INC. ``AS IS'' AND ANY EXPRESS OR IMPLIED
  * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
  * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL BUMP TECHNOLOGIES, INC. OR
  * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
  * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
  * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  * The views and conclusions contained in the software and documentation are those of the
  * authors and should not be interpreted as representing official policies, either expressed
  * or implied, of Bump Technologies, Inc.
  *
  **/

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stddef.h>

/* Tweak these for potential memory/throughput tradeoffs */
#define DEF_RING_SLOTS 16
#define DEF_RING_DATA_LEN 16384

typedef struct bufent {
    char *data;
    char *ptr;
    size_t left;
    struct bufent *next;
} bufent;

typedef struct ringbuffer {
    bufent *slots;
    bufent *head; // reads from the head
    bufent *tail; // writes to the tail
    int used;
    int num_slots;
    int data_len;
    size_t bytes_written;
} ringbuffer;

void ringbuffer_init(ringbuffer *rb, int num_slots, int data_len);
void ringbuffer_cleanup(ringbuffer *rb);

char * ringbuffer_read_next(ringbuffer *rb, int * length);
void ringbuffer_read_skip(ringbuffer *rb, int length);
void ringbuffer_read_pop(ringbuffer *rb);

char * ringbuffer_write_ptr(ringbuffer *rb);
void ringbuffer_write_append(ringbuffer *rb, int length);

int ringbuffer_size(ringbuffer *rb);
int ringbuffer_capacity(ringbuffer *rb);
int ringbuffer_is_empty(ringbuffer *rb);
int ringbuffer_is_full(ringbuffer *rb);

int ringbuffer_bytes_written(const ringbuffer *rb);
int ringbuffer_bytes_pending(const ringbuffer *rb);

#endif /* RINGBUFFER_H */

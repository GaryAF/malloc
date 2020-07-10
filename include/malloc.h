/*
** EPITECH PROJECT, 2020
** PSU_2019_malloc
** File description:
** malloc
*/
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include<unistd.h>
#include <math.h>
#include <string.h>

#pragma once
typedef struct	s_chunk t_chunk;

struct	s_chunk
{
    t_chunk	*prev;
    t_chunk	*next;
    size_t	size;
    bool is_free;
    void *adress;
};

void *malloc(size_t size);
void *init(size_t const size);
t_chunk *new_case(size_t const size, t_chunk *tmp);
void *bestfit(size_t const size , t_chunk *mem);
int power_of_two(size_t const size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
t_chunk	*find_chunk(t_chunk *tmp, void *ptr);
void* calloc(size_t first , size_t two);



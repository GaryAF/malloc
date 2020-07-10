/*
** EPITECH PROJECT, 2020
** PSU_2019_malloc
** File description:
** malloc
*/

#include "include/malloc.h"
t_chunk	*start = NULL;

void*bestfit(size_t const size, t_chunk *tmp)
{
    t_chunk *copy = tmp;
    int stop = 0;
    int small = 0;
    void* position = NULL;

    if (copy == NULL)
        return (NULL);

    for (; copy->next != NULL; copy = copy->next) {
        if (copy->is_free == true && size <= copy->size && stop == 0) {
            stop = 1;
            small = copy->size;
            position = copy->adress;
        }
        if (copy->is_free == true && size <= copy->size && copy->size < small) {
            position = copy->adress;
            copy->is_free = false;
        }
    }
    return position;
}

void *malloc(size_t size)
{
    t_chunk *chunk;
    if (size <= 0)
        return (NULL);
    size = power_of_two(size);

    if (start == NULL) {
        if ((start = init(size)) == NULL)
	        return (NULL);
        return (start->adress);
    }
    if ((chunk = bestfit(size, start)) != NULL)
        return (chunk->adress);
    else {
        if ((chunk = new_case(size, start)) != NULL)
            return chunk->adress;
        return (NULL);
    }
    return (NULL);
}

void *init(size_t const size)
{
    int i = 2;
    for (; getpagesize() * i < size; i+= 2){}
    t_chunk *init = sbrk(getpagesize() * i);

    if (init == (void *)-1)
        return NULL;
    init->size = size;
    init->next = NULL;
    init->prev = NULL;
    init->adress = (void*)init + sizeof(t_chunk);
    init->is_free = false;
    return init;
}

t_chunk *new_case(size_t const size, t_chunk *tmp)
{
    int i = 2;
    for (; getpagesize() * i < size; i+= 2){}
    t_chunk *new = sbrk(getpagesize() * i);
    t_chunk *copy = tmp;
    while (copy->next != NULL) {
        copy = copy->next;
    }
    if (new == (void *) -1)
        return (NULL);
    new->is_free = false;
    new->next = NULL;
    new->prev = copy;
    new->adress = (void*)new +sizeof(t_chunk);
    new->size = size;
    return new;
}

int power_of_two(size_t const size)
{
    int result = 2;

    if (size == 0)
        return 1;
    while (result < size) {
        result = result + result;
    }
    return (result);
}

void free(void *ptr)
{
    t_chunk *new = start;

    for (new; new!=NULL; new = new->next) {
        if (new->adress == ptr)
            new->is_free = true;
    }
}

t_chunk	*find_chunk(t_chunk *tmp, void *ptr)
{
    if (ptr == NULL)
        return (NULL);
    while (tmp != NULL) {
        if (tmp->adress == ptr)
	    return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}

void* calloc(size_t first , size_t two)
{
    size_t total = first * two;
    char *stock = malloc(total);

    if (total == 0 || first == 0 || two == 0)
        return NULL;
    return (memset(stock, 0, total));
}

void *realloc(void *ptr, size_t size)
{
    t_chunk	*blk;
    void *dest;

    if (!ptr)
        return (malloc(size));
    if (size == 0) {
        free(ptr);
        return (NULL);
    }
    blk = (t_chunk*)((char*)ptr - sizeof(t_chunk));
    if (blk->is_free)
        return (NULL);
    if (blk->size >= size + sizeof(t_chunk))
        return (ptr);
    dest = malloc(size);
    if (dest)
        memcpy(dest, (char*)blk + sizeof(t_chunk), blk->size);
    free(ptr);
    return (dest);
}
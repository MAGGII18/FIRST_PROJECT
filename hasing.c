#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node 
{
    char *key;
    struct node *next;
} node;
/* Hashset structure */
typedef struct {
    size_t n_buckets;
    node **buckets;
    size_t size;
} hashset;
static unsigned long hash_str(const char *str) {
    unsigned long h=5381;
    char c;
    while ((c=*str++))
        h =h * 33 + (unsigned char)c;
    return h;
}

//Create a new hashset 
hashset *hashset_create(size_t n) 
{
    if (n == 0) n = 101;  // default small prime
    hashset *h = malloc(sizeof(hashset));
    if (!h) return NULL;

    h->buckets = calloc(n, sizeof(node*));
    if (!h->buckets) {
        free(h);
        return NULL;
    }

    h->n_buckets = n;
    h->size = 0;
    return h;
}

/* Add a key to hashset (ignore if already present) */
void hashset_add(hashset *h, const char *key) {
    if (!h || !key) return;

    size_t idx = hash_str(key) % h->n_buckets;
    node *cur = h->buckets[idx];

    while (cur) {
        if (strcmp(cur->key, key) == 0) return;  // already exists
        cur = cur->next;
    }

    // add new node at head
    node *new_node = malloc(sizeof(node));
    new_node->key = strdup(key);
    new_node->next = h->buckets[idx];
    h->buckets[idx] = new_node;
    h->size++;
}

/* Check if hashset contains a key */
int hashset_contains(hashset *h, const char *key) {
    if (!h || !key) return 0;

    size_t idx = hash_str(key) % h->n_buckets;
    node *cur = h->buckets[idx];

    while (cur) {
        if (strcmp(cur->key, key) == 0) return 1;
        cur = cur->next;
    }

    return 0;
}

//Get number of unique keys in hashset 
size_t hashset_size(hashset *h) {
    if (!h) return 0;
    return h->size;
}

// Count common keys between two hashsets 
size_t hashset_intersection(hashset *a, hashset *b) {
    if (!a || !b) return 0;

    hashset *small = a, *big = b;
    if (hashset_size(a) > hashset_size(b)) {
        small = b;
        big = a;
    }

    size_t count = 0;
    for (size_t i = 0; i < small->n_buckets; i++) {
        node *cur = small->buckets[i];
        while (cur) {
            if (hashset_contains(big, cur->key)) count++;
            cur = cur->next;
        }
    }
    return count;
}

/* Free memory used by hashset */
void hashset_free(hashset *h) {
    if (!h) return;

    for (size_t i = 0; i < h->n_buckets; i++) {
        node *cur = h->buckets[i];
        while (cur) {
            node *next = cur->next;
            free(cur->key);
            free(cur);
            cur = next;
        }
    }

    free(h->buckets);
    free(h);
}
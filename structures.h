#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Definition data structures

typedef struct ListNode {
    void *data;
    struct ListNode *next;
} ListNode;

typedef struct DListNode {
    void *data;
    struct DListNode *next;
    struct DListNode *prev;
} DListNode;

typedef struct Stack {
    void **data;
    int top;
    int capacity;
} Stack;

typedef struct Queue {
    void **data;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

typedef struct HashNode {
    char *key;
    void *value;
    struct HashNode *next;
} HashNode;

typedef struct HashTable {
    int capacity;
    int size;
    HashNode **buckets;
} HashTable;


// List functions

static inline ListNode* list_create_node(void *data) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (!node) return NULL;
    node->data = data;
    node->next = NULL;
    return node;
}

static inline void list_insert_front(ListNode **head, void *data) {
    ListNode *node = list_create_node(data);
    if (!node) return;
    node->next = *head;
    *head = node;
}

static inline void* list_remove_front(ListNode **head) {
    if (!head || !*head) return NULL;
    ListNode *temp = *head;
    void *data = temp->data;
    *head = temp->next;
    free(temp);
    return data;
}

static inline void list_free(ListNode *head) {
    while (head) {
        ListNode *temp = head;
        head = head->next;
        free(temp);
    }
}


// Stack (LIFO) functions

static inline Stack* stack_create(int capacity) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if (!s) return NULL;
    s->data = (void **)malloc(sizeof(void *) * capacity);
    if (!s->data) {
        free(s);
        return NULL;
    }
    s->top = -1;
    s->capacity = capacity;
    return s;
}

static inline bool stack_is_empty(Stack *s) {
    return s->top == -1;
}

static inline bool stack_is_full(Stack *s) {
    return s->top == s->capacity - 1;
}

static inline void stack_push(Stack *s, void *data) {
    if (stack_is_full(s)) {
        s->capacity *= 2;
        void **new_data = (void **)realloc(s->data, sizeof(void *) * s->capacity);
        if (!new_data) return;
        s->data = new_data;
    }
    s->data[++s->top] = data;
}

static inline void* stack_pop(Stack *s) {
    if (stack_is_empty(s)) return NULL;
    return s->data[s->top--];
}

static inline void* stack_peek(Stack *s) {
    if (stack_is_empty(s)) return NULL;
    return s->data[s->top];
}

static inline void stack_free(Stack *s) {
    if (s) {
        free(s->data);
        free(s);
    }
}


// Queue (FIFO) functions

static inline Queue* queue_create(int capacity) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (!q) return NULL;
    q->data = (void **)malloc(sizeof(void *) * capacity);
    if (!q->data) {
        free(q);
        return NULL;
    }
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    q->capacity = capacity;
    return q;
}

static inline bool queue_is_empty(Queue *q) {
    return q->size == 0;
}

static inline void queue_enqueue(Queue *q, void *data) {
    if (q->size == q->capacity) {
        int new_capacity = q->capacity * 2;
        void **new_data = (void **)malloc(sizeof(void *) * new_capacity);
        if (!new_data) return;
        for (int i = 0; i < q->size; i++) {
            new_data[i] = q->data[(q->front + i) % q->capacity];
        }
        free(q->data);
        q->data = new_data;
        q->front = 0;
        q->rear = q->size - 1;
        q->capacity = new_capacity;
    }
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = data;
    q->size++;
}

static inline void* queue_dequeue(Queue *q) {
    if (queue_is_empty(q)) return NULL;
    void *data = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return data;
}

static inline void* queue_peek(Queue *q) {
    if (queue_is_empty(q)) return NULL;
    return q->data[q->front];
}

static inline void queue_free(Queue *q) {
    if (q) {
        free(q->data);
        free(q);
    }
}


// Hash Tables functions

static inline unsigned long hash_function(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

static inline HashTable* hashtable_create(int capacity) {
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
    if (!ht) return NULL;
    ht->capacity = capacity;
    ht->size = 0;
    ht->buckets = (HashNode **)calloc(capacity, sizeof(HashNode *));
    if (!ht->buckets) {
        free(ht);
        return NULL;
    }
    return ht;
}

static inline void hashtable_insert(HashTable *ht, const char *key, void *value) {
    if (!ht || !key) return;
    unsigned long index = hash_function(key) % ht->capacity;
    
    HashNode *current = ht->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return;
        }
        current = current->next;
    }

    HashNode *new_node = (HashNode *)malloc(sizeof(HashNode));
    if (!new_node) return;
    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = ht->buckets[index];
    ht->buckets[index] = new_node;
    ht->size++;
}

static inline void* hashtable_get(HashTable *ht, const char *key) {
    if (!ht || !key) return NULL;
    unsigned long index = hash_function(key) % ht->capacity;

    HashNode *current = ht->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

static inline void hashtable_remove(HashTable *ht, const char *key) {
    if (!ht || !key) return;
    unsigned long index = hash_function(key) % ht->capacity;

    HashNode *current = ht->buckets[index];
    HashNode *prev = NULL;

    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                ht->buckets[index] = current->next;
            }
            free(current->key);
            free(current);
            ht->size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

static inline void hashtable_free(HashTable *ht) {
    if (!ht) return;
    for (int i = 0; i < ht->capacity; i++) {
        HashNode *current = ht->buckets[i];
        while (current) {
            HashNode *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(ht->buckets);
    free(ht);
}

#endif /* DATA_STRUCTURES_H */
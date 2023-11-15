#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <locale.h>


//4.2 (2 балла).Реализовать очередь с приоритетом.Приоритет задается
//целым числом от 0 до 255.
//Реализовать функции для работы с очередью : 1) добавление элемента
//и 2) извлечение элемента : находящегося первым в очереди / с
//указанным приоритетом / с приоритетом не ниже чем заданный.
//В тестирующей программе имитировать генерацию сообщений с
//различным приоритетом и выборку данных с различными условиями.
//Срок сдачи решения : 5 ноября 2023г.

typedef struct PQNode {
    void* data;
    int priority;
    struct PQNode* prev;
    struct PQNode* next;
} PQNode;

typedef struct PQueue {
    PQNode* head;
    PQNode* tail;
} PQueue;

PQueue* pq_new();//Конструктор.
void pq_push(PQueue* pq, void* data, int priority);//Добавление данных с приоритетом, дынне с меньшем приоритетом будут первыми.
void pq_push_copy(PQueue* pq, const void* data, int priority, void* (*data_copy_func)(const void*));//Добавьте копию данных с приоритетом.
void* pq_front_data(PQueue* pq);//Возвращает указатель на данные первого элемента.
int pq_front_priority(PQueue* pq);//Возвращает приоритет первого элемента.
void* pq_data(PQueue* pq, int priority);//Извлечение элемента : с указанным приоритетом / с приоритетом не ниже чем заданный.
void pq_shift(PQueue* pq);//Удалить первый элемент из очереди.
void pq_shift_data(PQueue* pq, void (*data_destructor_func)(void*));//Удалить первый элемент, уничтожает данные.
int pq_is_empty(PQueue* pq);//Проверяет, пуста ли очередь.
unsigned pq_size(PQueue* pq);//Возвращает размер очереди.
void pq_free(PQueue* pq);//Деструктор.
void pq_free_data(PQueue* pq, void (*data_destructor_func)(void*));//Деструктор с уничтожением данных.

//==================================================

int main() {
    PQueue* pQueue = pq_new();

    setlocale(LC_ALL, "rus");

    //Запрос на количество элементов, добавляемых в очередь.
    unsigned int size = 0;
    printf("Количество элементов, добавляемых в очередь: ");
    if (scanf("%u", &size) != 1) {
        printf("Ошибка ввода!\n");
        return 1;
    }

    //Заполнение очереди, данные = (void*)NULL, приоритет случаен, ограничен [0, 255].
    //Данные могут быть любого типа.
    printf("Заполнение очереди элементами.\n");
    int prio = 0;
    for (int i = 0; i < size; i++) {
        prio = rand() % 255;//Приоритет случаен, ограничен [0, 255].
        pq_push(pQueue, NULL, prio);
    }

    printf("Количество элементов в очереди: %d.\n", pq_size(pQueue));

    printf("Извлечение из очреди по приоритету. Приоритет: ");
    if (scanf("%d", &prio) != 1) {
        printf("Ошибка ввода!\n");
        return 1;
    }

    //Ели элемент находят, то выводят его приоритет: "priority: %d.\n";
    //Если элемент находят, то об его извлечении можно судить по изменившемуся  размеру очереди.
    printf("Найденный элемент: %d\n", (int*)pq_data(pQueue, prio));

    printf("Количество элементов в очереди: %d.\n", pq_size(pQueue));

    printf("Очистка очреди.\n");
    pq_free(pQueue);//В случае если элементы содержать данные вызывается функция:
    //void pq_free_data(PQueue* pq, void (*data_destructor_func)(void*));

    return 0;
}

//==================================================

PQNode* pqn_new(void* data, int priority) {
    PQNode* node = (PQNode*)malloc(sizeof(PQNode));

    node->data = data;
    node->priority = priority;
    node->prev = NULL;
    node->next = NULL;

    return node;
}
PQueue* pq_new() {
    PQueue* pq = (PQueue*)malloc(sizeof(PQueue));;

    pq->head = NULL;
    pq->tail = NULL;

    return pq;
}
void pq_push(PQueue* pq, void* data, int priority) {
    PQNode* node = pqn_new(data, priority);

    if (pq_is_empty(pq)) {//Если очередь пуста.
        pq->head = pq->tail = node;
    } else {//Иначе.
        //Последний элемент в очереди.
        PQNode* last = pq->tail;

        //Место вставки с учётом приоритета.
        while (last && last->priority > priority)
            last = last->prev;

        if (!last) {
            node->next = pq->head;
            pq->head->prev = node;
            pq->head = node;
        } else if (last == pq->tail) {
            node->prev = pq->tail;
            pq->tail->next = node;
            pq->tail = node;
        } else {
            node->prev = last;
            node->next = last->next;
            last->next->prev = node;
            last->next = node;
        }
    }
}
void pq_push_copy(PQueue* pq, const void* data, int priority, void* (*data_copy_func)(const void*)) {
    pq_push(pq, data_copy_func(data), priority);
}
void* pq_front_data(PQueue* pq) {
    return pq->head->data;
}
int pq_front_priority(PQueue* pq) {
    return pq->head->priority;
}
void* pq_data(PQueue* pq, int priority) {
    if (pq->head == pq->tail) {//Если в очереди один элемент.
        if (priority <= pq->tail->priority) {
            printf("[1]priority: %d.\n", pq->head->priority);
            void* data = pq->tail->data;
            free(pq->head);
            pq->head = pq->tail = NULL;
            return data;
        }
    } else {//В очереди элементов больше одного.
        PQNode* next = pq->head;
        while (next && next->priority < priority)
            next = next->next;
        
        if (next) {
            if (next != pq->head)
                next->prev->next = next->next;
            else
                pq->head = next->next;

            if (next != pq->tail)
                next->next->prev = next->prev;
            else
                pq->tail = next->prev;

            printf("[2]priority: %d.\n", next->priority);
            void* data = next->data;
            free(next);
            return data;
        }
    }

    return NULL;
}
void pq_shift(PQueue* pq) {

    if (pq->head == pq->tail) {//Если в очереди один элемент.
        free(pq->head);
        pq->head = pq->tail = NULL;
    } else {//В очереди элементов больше одного.
        PQNode* second = pq->head->next;
        second->prev = NULL;
        free(pq->head);
        pq->head = second;
    }
}
void pq_shift_data(PQueue* pq, void (*data_destructor_func)(void*)) {
    data_destructor_func(pq->head->data);
    pq_shift(pq);
}
int pq_is_empty(PQueue* pq) {
    return (pq->head == NULL);
}
unsigned pq_size(PQueue* pq) {
    unsigned size = 0;
    PQNode* node;

    for (node = pq->head; node; node = node->next)
        ++size;

    return size;
}
void pq_free(PQueue* pq) {
    while (!pq_is_empty(pq))
        pq_shift(pq);
}
void pq_free_data(PQueue* pq, void (*data_destructor_func)(void*)) {
    while (!pq_is_empty(pq))
        pq_shift_data(pq, data_destructor_func);
}

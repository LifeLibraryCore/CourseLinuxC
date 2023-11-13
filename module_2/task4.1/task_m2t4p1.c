#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include "Contact.h"
#include <string.h>

//2.1 (3 балла).Написать программу для работы со списком контактов
//(телефонная книга).
//Хранить сведения о Ф.И.О.человека, его месте работы и должности,
//номерах телефона, адресах электронной почты, ссылки на страницы в
//соцсетях и профили в мессенджерах.
//Обязательными для заполнения являются фамилия и имя, остальные
//поля заполняются при необходимости.
//Для хранения данных использовать массивы.
//Программа должна предоставлять возможность добавления,
//редактирования и удаления контакта

typedef struct Node {
    struct Node* next;
    struct Node* prev;
    Contact* data;
} Node;

typedef struct linked_list
{
    Node* head;
    Node* tail;
} linked_list;

int initialize_list(linked_list* list, int count);
int add_item_to_begin(linked_list* list, Contact* item);
int add_item_to_end(linked_list* list, Contact* item);
int add_item_before(linked_list* list, Node* pos, Contact* item);
void print_list(linked_list list);
Node* find_item(linked_list list, Contact* item);
int delete_item(linked_list* list, Node* node);
int drop_list(linked_list* list);

void Menu();
void printContact(const Contact*);//Вывод информации контакта.
void editContact(Contact*);//Редактирование контакта.

linked_list* list;


int main() {
    setlocale(LC_ALL, "rus");

    int size = 0;
    printf("Максимальное количество контактов:");
    if (scanf("%u", &size) != 1) {
        printf("Ошибка ввода!\n");
        return 0;
    }
    if( size < 1) {
        printf("Ошибка size < 1!\n");
        return 0;
    }
    
    list = (linked_list*)malloc(sizeof(linked_list));
    initialize_list(list, size);

    Menu();

    drop_list(list);
}

void Menu() {
    //Меню.
    unsigned int ncom = 0;
    char** com = (char**)malloc(sizeof(char*) * 2);
    com[0] = (char*)malloc(sizeof(char) * 20);
    com[1] = (char*)malloc(sizeof(char) * 20);
    Contact* contact;

    while (1) {
        printf("  [-1] Выход;\n");
        printf("  [1] Редактировать;\n");
        printf("  [2] Создать;\n");
        printf("  [3] Удалить;\n");
        printf("  [4] Вывести;\n Ввод: ");
        if (scanf("%u", &ncom) == 0) { continue; }
        printf("\e[1;1H\e[2J");

        switch (ncom) {
        case -1:
            printf("Выход из меню редактирования контакта!\n");
            return;
            break;
        case 1:
            printf("[1]Введите имя и фамилию контакта: ");
            if (scanf("%s %s", com[0], com[1]) == 2) {
                contact = newContact(com[0], com[1]);
                Node* node = find_item(*list, contact);

                if (node == NULL) {
                    printf("Контакта не существует!\n");
                } else {
                    editContact(node->data);
                }

                free(contact);
                contact = NULL;
            }
            break;
        case 2:
            printf("[2]Введите имя и фамилию создаваемого контакта: ");
            if (scanf("%s %s", com[0], com[1]) == 2) {
                contact = newContact(com[0], com[1]);

                add_item_to_end(list, contact);


                contact = NULL;
            }
            break;
        case 3:
            printf("[2]Введите имя и фамилию удаляемого контакта: ");
            if (scanf("%s %s", com[0], com[1]) == 2) {
                contact = newContact(com[0], com[1]);
                Node* node = find_item(*list, contact);

                if (node == NULL) {
                    printf("Контакта не существует!\n");
                }
                else {
                    delete_item(list, node);
                }

                free(contact);
                contact = NULL;
            }
            break;
        case 4:
            print_list(*list);
            break;
        default:
            printf("Ошибка ввода.\n");
            break;
        }
    }
}

int initialize_list(linked_list* list, int count) {
    list->head = list->tail = NULL;

    char* temp = (char*)malloc(sizeof(char*) * 2);
    for (int i = 0; i < count; ++i) {
        temp[0] = (char)(i + 'A'); temp[1] = '\0';
        add_item_to_end(list, newContact(temp, temp));
    }
    free(temp);
    return 0;
}
int add_item_to_begin(linked_list* list, Contact* item) {
    if (list == NULL) return -1;

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return -2;

    newNode->prev = newNode->next = NULL;
    newNode->data = item;

    if (list->head) {
        list->head->prev = newNode;
        newNode->next = list->head;
        list->head = newNode;
    } else {
        list->head = list->tail = newNode;
    }

    return 0;
}
int add_item_to_end(linked_list* list, Contact* item) {
    if (list == NULL) return -1;

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return -2;

    newNode->prev = newNode->next = NULL;
    newNode->data = item;

    if (list->tail) {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    } else {
        list->head = list->tail = newNode;
    }

    return 0;
}
int add_item_before(linked_list* list, Node* pos, Contact* item) {
    if (list == NULL) return -1;
    if (pos == NULL) return add_item_to_end(list, item);

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return -2;

    newNode->prev = newNode->next = NULL;
    newNode->data = item;

    newNode->next = pos;
    newNode->prev = pos->prev;

    if (pos->prev) {
        pos->prev->next = newNode;
    }

    pos->prev = newNode;

    return 0;
}
void print_list(linked_list list) {
    Node* current = list.head;
    printf("\n");

    while (current) {
        printContact(current->data);
        current = current->next;
    }

    printf("\n");
}
Node* find_item(linked_list list, Contact* item) {
    Node* current = list.head;
    
    while (current) {
        if (strcmp(current->data->name, item->name) == 0 && strcmp(current->data->surname, item->surname) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}
int delete_item(linked_list* list, Node* node) {
    if (node == NULL) return -1;
    if (list == NULL) return -2;

    if (node->prev) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }

    freeContact(node->data);
    free(node);
    return 0;
}
int drop_list(linked_list* list) {
    if (list == NULL) return -2;

    Node* current = list->tail;
    Node* prev;

    int i = 0;

    while (current->prev != NULL) {
        freeContact(current->data);
        current = current->prev;
        i++;
        if (current->next != NULL) {
            free(current->next);
        }
    }

    freeContact(current->data);
    free(current);

    list->head = list->tail = NULL;
}


void printContact(const Contact* contact) {
    printf("\nИмя: %s\nФамилия: %s\n", contact->name, contact->surname);
    printf("Место работы: %s\nДолжность: %s\n", contact->workplace, contact->post);
    printf("Номера телефонов (кол-во [%d]):\n  ", LENGTH_ARR2);
    for(int i = 0; i < LENGTH_ARR2; i++)  printf("%s, ", contact->phoneNumbers[i]);
    printf("\nАдреса электронной почты (кол-во [%d]):\n  ", LENGTH_ARR2);
    for (int i = 0; i < LENGTH_ARR2; i++)  printf("%s, ", contact->emails[i]);
    printf("\nСсылки на страницы в соцсетях (кол-во [%d]):\n  ", LENGTH_ARR2);
    for (int i = 0; i < LENGTH_ARR2; i++)  printf("%s, ", contact->links[i]);
    printf("\nПрофили в мессенджерах (кол-во [%d]):\n  ", LENGTH_ARR2);
    for (int i = 0; i < LENGTH_ARR2; i++)  printf("%s, ", contact->profiles[i]);
    printf("\n\n");
}
void editContact(Contact* contact) {
    unsigned int ncom = 0;
    unsigned int i = 0;
    char* com = (char*)malloc(sizeof(char) * 25);

    while (1) {
        printf("Меню:\n");
        printf("  [-1] Выход;\n");
        printf("  [1] Имя, Фамилия, Место работы, Должность;\n");
        printf("  [2] Номера телефонов;\n");
        printf("  [3] Адреса электронной почты;\n");
        printf("  [4] Ссылки на страницы в соцсетях;\n");
        printf("  [5] Профили в мессенджерах;\nВвод: ");
        if (scanf("%u", &ncom) == 0) { continue; }
        printf("\e[1;1H\e[2J");

        switch (ncom) {
        case -1:
            printf("Выход из меню редактирования контакта!\n");
            return;
            break;
        case 1:
            for (int i = 0; i < 4; i++) {
                switch (i) {
                case 0: printf("Имя. Ввод: "); break;
                case 1: printf("Фамилия. Ввод: "); break;
                case 2: printf("Место работы. Ввод: "); break;
                case 3: printf("Должность. Ввод: "); break;
                }

                if (scanf("%s", com) == 1)
                setCCharArray[i](contact, com);
            }
            break;
        case 2:
            printf("Номер телефона [value number]:");
            if (scanf("%s %u", com, &i) == 2)
                setCCharArray2[0](contact, com, i);
            break;
        case 3:
            printf("Адрес электронной почты [value number]:");
            if (scanf("%s %u", com, &i) == 2)
                setCCharArray2[1](contact, com, i);
            break;
        case 4:
            printf("Ссылка на страницу в соцсетях [value number]:");
            if (scanf("%s %u", com, &i) == 2)
                setCCharArray2[2](contact, com, i);
            break;
        case 5:
            printf("Профиль в мессенджере [value number]:");
            if (scanf("%s %u", com, &i) == 2)
                setCCharArray2[3](contact, com, i);
            break;
        default:
            printf("Ошибка ввода.\n");
            break;
        }
    }

    free(com);
}

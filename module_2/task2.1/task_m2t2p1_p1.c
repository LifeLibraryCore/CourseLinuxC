#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include "Contact.h"

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

void Menu();
void printContact(const Contact*);//Вывод информации контакта.
void editContact(Contact*);//Редактирование контакта.

Contact** contacts = NULL;//Контакты
unsigned int size = 10;//Размер массива
char* temp;


int main() {
    setlocale(LC_ALL, "rus");
    printf("Максимальное количество контактов:");
    if (scanf("%u", &size) != 1) {
        printf("Ошибка ввода!\n");
        return 0;
    }
    if( size < 1) {
        printf("Ошибка size < 1!\n");
        return 0;
    }
    //Созадние массива контактов.
    contacts = (Contact**)malloc(sizeof(Contact*) * size);
    temp = (char*)malloc(sizeof(char*) * 2);
    for (unsigned int i = 0; i < size; i++) {
        temp[0] = (char)(i + 'А'); temp[1] = '\0';
        contacts[i] = newContact(temp, temp);
    }
    

    Menu();

    //Освобождение памяти.
    for (unsigned int i = 0; i < size; i++)
        if (contacts[i] != NULL)
            delContact(contacts[i]);
    free(contacts);
    free(temp);
}

void Menu() {
    //Меню.
    unsigned int ncom = 0;
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
            printf("Введи номер редактируемого контакта: ");
            if (scanf("%u", &ncom) == 1) {
                if (contacts[ncom] == NULL || ncom >= size)
                    printf("Контакта не существует!\n");
                else
                    editContact(contacts[ncom]);
            }
            break;
        case 2:
            printf("Введи номер создаваемого контакта: ");
            if (scanf("%u", &ncom) == 1) {
                if (contacts[ncom] != NULL || ncom >= size)
                    printf("Контакт существует или номер контакта >= size!\n");
                else {
                    temp[0] = ' '; temp[1] = '\0';
                    contacts[ncom] = newContact(temp, temp);
                }
            }
            break;
        case 3:
            printf("Введи номер удаляемого контакта: ");
            if (scanf("%u", &ncom) == 1) {
                if (contacts[ncom] == NULL || ncom >= size)
                    printf("Контакта не существует!\n");
                else {
                    delContact(contacts[ncom]);
                    contacts[ncom] = NULL;
                }
            }
            break;
        case 4:
            for (unsigned int i = 0; i < size; i++)
                if (contacts[i] != NULL)
                    printContact(contacts[i]);
            break;
        default:
            printf("Ошибка ввода.\n");
            break;
        }
    }
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

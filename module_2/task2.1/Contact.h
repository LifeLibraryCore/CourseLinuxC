#include <malloc.h>

const unsigned int LENGTH_ARR2 = 10;//Максимальное количество массивов char в двумерном массиве.

typedef struct {
    char* name;//Имя.
    char* surname;//Фамиялия.
    char* workplace;//Место работы.
    char* post;//Должность.
    char** phoneNumbers;//Номера телефонов.
    char** emails;//Адреса электронной почты.
    char** links;//Ссылки на страницы в соцсетях. 
    char** profiles;//Профили в мессенджерах
} Contact;

Contact* newContact(const char* name, const char* surname);//Конструктор.
int delContact(Contact* contact);//Деструктор.
void setCName(Contact* contact, const char* name);//Установить значения поля структуры.
void setCSurname(Contact* contact, const char* surname);//Установить значения поля структуры.
void setCWorkplace(Contact* contact, const char* workplace);//Установить значения поля структуры.

void setPhoneNumbers(Contact* contact, const char* value, const unsigned int i);
void setEmails(Contact* contact, const char* value, const unsigned int i);
void setLinks(Contact* contact, const char* value, const unsigned int i);
void setProfiles(Contact* contact, const char* value, const unsigned int i);

//==============================new/del==============================

Contact* newContact(const char* name, const char* surname) {
    Contact* temp = (Contact*)malloc(sizeof(Contact));

    //Одномерные массивы.
    temp->name = NULL;
    temp->surname = NULL;
    temp->workplace = NULL;
    temp->post = NULL;

    //Двумерные массивы.
    temp->phoneNumbers = (char**)malloc(sizeof(char*) * LENGTH_ARR2);
    temp->emails = (char**)malloc(sizeof(char*) * LENGTH_ARR2);
    temp->links = (char**)malloc(sizeof(char*) * LENGTH_ARR2);
    temp->profiles = (char**)malloc(sizeof(char*) * LENGTH_ARR2);

    for (int j = 0; j < LENGTH_ARR2; j++) { 
        temp->phoneNumbers[j] = NULL;
        temp->emails[j] = NULL;
        temp->links[j] = NULL;
        temp->profiles[j] = NULL;
    }

    setCName(temp, name);
    setCSurname(temp, surname);

    return temp;
}
int delContact(Contact* contact) {
    if (contact == 0) return -1;

    free(contact->name);
    free(contact->surname);
    if (contact->workplace != NULL) free(contact->workplace);
    if (contact->post != NULL) free(contact->post);

    for (int j = 0; j < LENGTH_ARR2; j++) {
        if (contact->phoneNumbers[j] != NULL) free(contact->phoneNumbers[j]);
        if (contact->emails[j] != NULL) free(contact->emails[j]);
        if (contact->links[j] != NULL) free(contact->links[j]);
        if (contact->profiles[j] != NULL) free(contact->profiles[j]);
    }

    if (contact->phoneNumbers == NULL) free(contact->phoneNumbers);
    if (contact->emails != NULL) free(contact->emails);
    if (contact->links != NULL) free(contact->links);
    if (contact->profiles != NULL) free(contact->profiles);

    free(contact);
    return 0;
}

//==============================set char *array==============================

void setCName(Contact* contact, const char* name) {
    if (contact->name != NULL) free(contact->name);//Проверяет на занятость памяти.

    int lName = 0;//Счётчик/Длинна массива. Описывает кол-во символов в аргументе const char*.
    for (; name[lName] != '\0'; lName++); lName++;
    contact->name = (char*)malloc(sizeof(char) * lName);

    for (int i = 0; i < lName - 1; i++) contact->name[i] = name[i];
    contact->name[lName - 1] = '\0';
}
void setCSurname(Contact* contact, const char* surname) {
    if (contact->surname != NULL) free(contact->surname);

    int lSurname = 0;
    for (; surname[lSurname] != '\0'; lSurname++); lSurname++;
    contact->surname = (char*)malloc(sizeof(char) * lSurname);

    for (int i = 0; i < lSurname - 1; i++) contact->surname[i] = surname[i];
    contact->surname[lSurname - 1] = '\0';
}
void setCWorkplace(Contact* contact, const char* workplace) {
    if (contact->workplace != NULL) free(contact->workplace);

    int lWorkplace = 0;
    for (; workplace[lWorkplace] != '\0'; lWorkplace++); lWorkplace++;
    contact->workplace = (char*)malloc(sizeof(char) * lWorkplace);

    for (int i = 0; i < lWorkplace - 1; i++) contact->workplace[i] = workplace[i];
    contact->workplace[lWorkplace - 1] = '\0';
}
void setCPost(Contact* contact, const char* post) {
    if (contact->post != NULL) free(contact->post);

    int lPost = 0;
    for (; post[lPost] != '\0'; lPost++); lPost++;
    contact->post = (char*)malloc(sizeof(char) * lPost);

    for (int i = 0; i < lPost - 1; i++) contact->post[i] = post[i];
    contact->post[lPost - 1] = '\0';
}

void (*setCCharArray[4])(Contact*, const char*) = {
    setCName,
    setCSurname,
    setCWorkplace,
    setCPost
};

//==============================set char **array==============================

void setPhoneNumbers(Contact* contact, const char* value, const unsigned int i) {
    
    if (i >= LENGTH_ARR2) return;
    if (contact->phoneNumbers[i] != NULL) free(contact->phoneNumbers[i]);

    int length = 0;
    for (; value[length] != '\0'; length++); length++;
    contact->phoneNumbers[i] = (char*)malloc(sizeof(char) * length);

    for (int j = 0; j < length - 1; j++) contact->phoneNumbers[i][j] = value[j];
    contact->phoneNumbers[i][length - 1] = '\0';
}
void setEmails(Contact* contact, const char* value, const unsigned int i) {

    if (i >= LENGTH_ARR2) return;
    if (contact->emails[i] != NULL) free(contact->emails[i]);

    int length = 0;
    for (; value[length] != '\0'; length++); length++;
    contact->emails[i] = (char*)malloc(sizeof(char) * length);

    for (int j = 0; j < length - 1; j++) contact->emails[i][j] = value[j];
    contact->emails[i][length - 1] = '\0';
}
void setLinks(Contact* contact, const char* value, const unsigned int i) {

    if (i >= LENGTH_ARR2) return;
    if (contact->links[i] != NULL) free(contact->links[i]);

    int length = 0;
    for (; value[length] != '\0'; length++); length++;
    contact->links[i] = (char*)malloc(sizeof(char) * length);

    for (int j = 0; j < length - 1; j++) contact->links[i][j] = value[j];
    contact->links[i][length - 1] = '\0';
}
void setProfiles(Contact* contact, const char* value, const unsigned int i) {

    if (i >= LENGTH_ARR2) return;
    if (contact->profiles[i] != NULL) free(contact->profiles[i]);

    int length = 0;
    for (; value[length] != '\0'; length++); length++;
    contact->profiles[i] = (char*)malloc(sizeof(char) * length);

    for (int j = 0; j < length - 1; j++) contact->profiles[i][j] = value[j];
    contact->profiles[i][length - 1] = '\0';
}

void (*setCCharArray2[4])(Contact*, const char*, const unsigned int) = {
    setPhoneNumbers,
    setEmails,
    setLinks,
    setProfiles
};

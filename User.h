#ifndef _USERS_H_
#define _USERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int ID;
    char fullName[32];
    char type[16];
    char username[8];
    char password[16];

}T_User;

void registerNewUser();
void registerNewUserByAdmin();
void deleteUser();
void listUsers();
void saveUsers();
void loadUsers();
T_User login();
char* getUserType();

#endif // _USERS_H_

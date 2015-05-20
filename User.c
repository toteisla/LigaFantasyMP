#include "User.h"

//Private function declarations
static void sortUsers();
static int getLastUserID();
static int usernameUsed( char* username );

//Private vars
static T_User *usr;
static int tam; //Size of usr vector

//Public functions
void listUsers(){
    sortUsers();
    int i;
    char str[ 52 ];
    printf( "\nLista de usuarios:\n" );
    for( i = 0 ; i < tam ; i++){
        sprintf( str, "%02d-%s-%s-%s-%s", usr[i].ID, usr[i].fullName, usr[i].type, usr[i].username, usr[i].password );
        printf( "%s\n", str );
    }
    printf( "\n" );
}

//Register a new user from main menu before log into the system.
void registerNewUser(){
    int ID;
    char fullName[32];
    char username[8];
    char password[16];
    char password2[16];

    printf( "\nIntroduzca su nombre completo(20 caracteres maximo):  \n" );
    gets( fullName );
    fflush( stdin );

    do{
        printf( "\nIntroduzca el username que desee(5 caracteres maximo):  \n" );
        gets( username );
        fflush( stdin );
    }while( usernameUsed( username ));

    do{
        printf( "\nIntroduzca su contraseña(8 carácteres máximo):  \n" );
        gets( password );
        fflush( stdin );

        printf( "\nVuelva a repetir la contraseña para confirmar(8 carácteres máximo):  \n" );
        gets( password2 );
        fflush( stdin );
    }while( strcmp( password, password2) != 0 );

    sortUsers();

    usr = (T_User *) realloc(usr, ( tam + 1 ) * sizeof( T_User ));

    ID = getLastUserID();
    usr[ tam ].ID = ID;
    strcpy( usr[tam].fullName, fullName );
    strcpy( usr[tam].type, "Participante" );
    strcpy( usr[tam].username, username );
    strcpy( usr[tam].password, password );
    tam++;
}

//Regiter a new user from Admin menu. Can choose the type of the new user.
void registerNewUserByAdmin(){
    int op, ID;
    char* aux;
    char strOp[8];
    char fullName[32];
    char username[8];
    char type[16];
    char password[16];
    char password2[16];

    printf( "\nIntroduzca su nombre completo(20 caracteres maximo):  \n" );
    gets( fullName );
    fflush( stdin );

    do{
        printf( "\nIntroduzca el username que desee(5 caracteres maximo):  \n" );
        gets( username );
        fflush( stdin );
    }while( usernameUsed( username ));

    do{
        printf("------------------[Elige el tipo de usuario]------------------ \n");
        puts("1.Administrador.\n");
        puts("2.Cronista.\n");
        puts("3.Participante\n");
        puts("Introduzca una opcion: ");
        gets( strOp );
        aux = strtok( strOp, "\n" );
        fflush( stdin );

        op = atoi( aux );
        switch( op ){
            case 1:
                strcpy(type, "Administrador");
                break;
            case 2:
                strcpy(type, "Cronista");
                break;
            case 3:
                strcpy(type, "Participante");
                break;
            default:
                printf("Opcion incorrecta\n");
        }
    }while( op < 0 || op > 4 );

    do{
        printf( "\nIntroduzca su contraseña(8 carácteres máximo):  \n" );
        gets( password );
        fflush( stdin );

        printf( "\nVuelva a repetir la contraseña para confirmar(8 carácteres máximo):  \n" );
        gets( password2 );
        fflush( stdin );
    }while( strcmp( password, password2) != 0 );

    sortUsers();

    usr = (T_User *) realloc(usr, ( tam + 1 ) * sizeof( T_User ));

    ID = getLastUserID();
    usr[ tam ].ID = ID;
    strcpy( usr[tam].fullName, fullName );
    strcpy( usr[tam].type, type );
    strcpy( usr[tam].username, username );
    strcpy( usr[tam].password, password );
    tam++;
}

//Remove a user and reallocate the vector to fix the empty position.
void deleteUser(){
    int cod, i, aux;

    printf( "\nIntroduzca el codigo del usuario:  \n" );
    scanf( "%d", &cod );
    fflush( stdin );

    for( i=0 ; i < tam ; i++ ){
        if( usr[i].ID == cod ) {
            aux = 1;
            i++;
        }
        if( aux == 1 )
            usr[i-1] = usr[i];
    }
    if(aux == 1)
        usr = ( T_User * ) realloc( usr, ( --tam )*sizeof( T_User ));
}

//Load the user list from 'Usuarios.txt'.
void loadUsers(){
    usr = ( T_User * ) calloc(0, sizeof( T_User ));
	FILE *file;
	int idx = 0;

	if(( file = fopen( "Usuarios.txt" , "r" )) == NULL ){
		printf("ERROR: No existe el archivo 'Usuarios.txt'\n");
	}else{
        //char str[52] , cod[2], fullname[20], type[13], username[5], password[8];
        char str[52];
        char* aux;
        while(fgets(str, 52, file) != NULL){
            T_User a;

            aux = strtok( str, "\n" ); //Take away \n readed from the file.
            strcpy(str, aux);

            aux = strtok( str, "-" );
            a.ID = atoi( aux );

            aux = strtok( NULL, "-" );
            strcpy(a.fullName , aux);

            aux = strtok( NULL, "-" );
            strcpy(a.type , aux);

            aux = strtok( NULL, "-" );
            strcpy(a.username , aux);

            aux = strtok( NULL, "-" );
            strcpy(a.password , aux);

            usr = (T_User *) realloc(usr, ( idx + 1  )* sizeof( T_User ));
            usr[ idx ] = a;
            idx++;
        }
        fclose( file );
        tam = idx;
    }
}

//Save the user list to 'Usuarios.txt'.
void saveUsers(){
    int i;
    char str[60];
    printf("Guardando.\n");
    FILE *file;
    if(( file = fopen( "Usuarios.txt" , "w+" )) == NULL){
        printf("ERROR: Error de lectura/escritura del archivo.");
    }else{
        for( i = 0 ; i < tam ; i++ ){
            sprintf( str, "%02d-%s-%s-%s-%s", usr[i].ID, usr[i].fullName, usr[i].type, usr[i].username, usr[i].password );
            if( i != tam - 1) //Fix the \n on the last line.
                strcat(str, "\n");
            fputs( str, file );
        }
        fclose(file);
    }
}

//Check if the username is in use.
static int usernameUsed( char* username ){
    int i;
    for( i = 0 ; i < tam ; i++ ){
        if( strcmp(usr[i].username, username) == 0){
            printf("Ya existe un usuario con ese username.\n");
            return 1;
        }
    }
    return 0;
}

//Check if the credentials introduced match with the user list.
T_User login(){
    int i;
    char username[20];
    char password[16];

    printf("Introduzca nombre de usuario:  \n");
    gets( username );
    fflush( stdin );

    printf("Introduzca contraseña:  \n");
    gets( password );
    fflush( stdin );

    for( i = 0 ; i < tam ; i++ ){
        if( strcmp(usr[i].username, username) == 0 && strcmp(usr[i].password, password) == 0 )
            return usr[i];
    }
    T_User a = { .ID = -1, .fullName = "Unregistered", .type = "Unregistered", .username = "Unregistered", .password = "Unregistered" };
    return a;
}

//Return the first availible id.
static int getLastUserID(){
    int i;

    sortUsers();
    for( i = 0 ; i < tam ; i++ ){
        if( usr[i].ID != i )
            return i;
    }
}

//Sort the user list by ID.
static void sortUsers(){
    int i, j, auxID;
    char auxName[32];
    char auxUser[8];
    char auxType[16];
    char auxPass[16];

    for( i = 1 ; i <= tam ; i++ ){
        for( j = 0 ; j <= tam - 2 ; j++ ){
            if( usr[j].ID > usr[j+1].ID ){
                auxID = usr[j].ID;
                strcpy(auxName, usr[j].fullName);
                strcpy(auxUser, usr[j].username);
                strcpy(auxType, usr[j].type);
                strcpy(auxPass, usr[j].password);

                usr[j].ID = usr[j+1].ID;
                strcpy(usr[j].fullName, usr[j+1].fullName);
                strcpy(usr[j].username, usr[j+1].username);
                strcpy(usr[j].type, usr[j+1].type);
                strcpy(usr[j].password, usr[j+1].password);

                usr[j+1].ID = auxID;
                strcpy(usr[j+1].fullName, auxName);
                strcpy(usr[j+1].username, auxUser);
                strcpy(usr[j+1].type, auxType);
                strcpy(usr[j+1].password, auxPass);
            }
        }
    }
}




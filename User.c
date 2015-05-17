#include "User.h"

//Private function declarations
static void sortUsers();
static int getLastID();

//Private vars
static T_User *usr;
static int tam; //Size of usr vector

//Public functions
void listUsers(){
    //sortUsers();
    int i;
    char str[ 52 ];
    printf( "\nLista de usuarios:\n" );
    for( i = 0 ; i < tam ; i++){
        sprintf( str, "%02d-%s-%s-%s-%s", usr[i].ID, usr[i].fullName, usr[i].type, usr[i].username, usr[i].password );
        printf( "%s\n", str );
    }
    printf( "\n" );
}

void registerNewUser(){
    char fullName[20];
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

    usr = (T_User *) realloc(usr, ( tam + 1 ) * sizeof( T_User ));
    usr[ tam ].ID = tam;
    strcpy( usr[tam].fullName, fullName );
    strcpy( usr[tam].type, "Participante" );
    strcpy( usr[tam].username, username );
    strcpy( usr[tam].password, password );
    tam++;
}

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

            aux = strtok( str, "\n" ); //Quito el \n del salto de linea
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
            if( i != tam - 1) //Evita una linea vacia al final del archivo
                strcat(str, "\n");
            fputs( str, file );
        }
        fclose(file);
    }
}

int usernameUsed(char* username){
    int i;
    char error[256];
    for( i = 0 ; i < tam ; i++ ){
        if( strcmp(usr[i].username, username) == 0){
            /*
            time_t tiempo = time(0);
            struct tm *tlocal = localtime(&tiempo);
            char output[128];
            strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
            sprintf(error,"[%s]: Se ha intentado anadir un articulo con codigo %d\n ",output,cod);
            add_error(error);
            */
            printf("Ya existe un usuario con ese username.\n");
            return 1;
        }
    }
    return 0;
}

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




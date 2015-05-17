#include <stdlib.h>
#include "User.h"

static void showMainMenu();
static void showUserMenu();
static void showUserMenuTest();
static void showRefereeMenu ();
static void showAdminMenu ();

int main() {
    loadUsers();
    showMainMenu();

	system("pause");
	return 0;
}

static void showMainMenu(){
    int op;
    T_User user;
    do{
        printf("------------------------------------Menu---------------------------------------- \n");

        puts("1.Registro.\n");
        puts("2.Acceso al sistema.\n");
        puts("3.User Module Test.\n");
        puts("4.Salir/Exit.\n");
        puts("Introduzca una opcion: ");
        scanf("%d", &op);
        fflush( stdin );

        switch( op ){
            case 1:
                registerNewUser();
                fflush( stdin );
                break;
            case 2:

                user = login();
                if( user.ID == -1 )
                    printf( "[ERROR]Usuario y contraseña no coinciden.\n" );
                else if( strcmp( user.type, "Administrador" ) == 0 )
                    showAdminMenu();
                else if( strcmp( user.type, "Cronista" ) == 0 )
                    showRefereeMenu();
                 else if( strcmp( user.type, "Participante" ) == 0 )
                    showUserMenu();
                break;
            case 3:
                showUserMenuTest();
                break;
            case 4:
                //guardar_stock();guardar_articulos();
                saveUsers();
                exit(1);
            default:
                printf("Opcion incorrecta\n");
                break;
        }
    }while( op != 4 );
}

static void showUserMenuTest(){
    int op;
    do{
        printf("------------------------------------Menu---------------------------------------- \n");

        puts("1.List Users.\n");
        puts("2.Save Users.\n");
        puts("3.\n");
        puts("4.\n");
        puts("5.\n");
        puts("6.Back\n");
        puts("Introduzca una opcion: ");
        scanf("%d", &op);

        switch( op ){
            case 1:
                listUsers();
                break;
            case 2:
                saveUsers();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                //guardar_stock();guardar_articulos();guardar_almacenes();exit(1);
                break;
            default:
                printf("Opcion incorrecta\n");
                break;
        }
    }while( op != 6 );
}

static void showUserMenu(){
    int op;
    do{
        printf("------------------------------------Menu---------------------------------------- \n");

        puts("1.Crear plantilla.\n");
        puts("2.Configurar Plantilla.\n");
        puts("3.Listar Plantillas.\n");
        puts("4.Eliminar Plantilla.\n");
        puts("5.Ranking.\n");
        puts("6.Salir del programa.\n");
        puts("Introduzca una opcion: ");
        scanf("%d", &op);

        switch( op ){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                //guardar_stock();guardar_articulos();guardar_almacenes();exit(1);
                break;
            default:
                printf("Opcion incorrecta\n");
                break;
        }
    }while( op != 6 );
}

static void showRefereeMenu(){
    int op;
    do{
        printf("------------------------------------Menu---------------------------------------- \n");

        puts("1.Listar equipos.\n");
        puts("2.Valorar Equipos.\n");
        puts("3.Salir/Exit.\n");
        puts("Introduzca una opcion: ");
        scanf("%d", &op);

        switch( op ){
            case 1:
                break;
            case 2:
                break;
            case 3:
                //guardar_stock();guardar_articulos();guardar_almacenes();exit(1);
                break;
            default:
                printf("Opcion incorrecta\n");
                break;
        }
    }while( op != 3 );
}

static void showAdminMenu(){
    int op;
    do{
        printf("------------------------------------Menu---------------------------------------- \n");

        puts("1.Equipos.\n");
        puts("2.Usuarios.\n");
        puts("3.Configuracion\n");
        puts("4.Salir del programa\n");
        puts("Introduzca una opcion: ");
        scanf("%d", &op);

        switch( op ){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                //guardar_stock();guardar_articulos();guardar_almacenes();exit(1);
                break;
            default:
                printf("Opcion incorrecta\n");
                break;
        }
    }while( op != 4 );
}

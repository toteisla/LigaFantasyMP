#include <stdlib.h>
#include "User.h"
#include "Team.h"
#include "Player.h"
#include "Config.h"
#include "Roster.h"

static void showMainMenu();
static void showUserMenu();
static void showUserMenuConfigRoster();
static void showRefereeMenu ();
static void showAdminMenu();
static void showAdminMenuUser();
static void showAdminMenuTeam();
static void showAdminMenuConfig();
static void init();
static void exitProgram();

static T_User user;

int main() {
    init();

    showMainMenu();

	system("pause");
	return 0;
}

static void showMainMenu(){
    int op;
    do{
        printf("------------------------------------Menu---------------------------------------- \n");

        puts("1.Registro.\n");
        puts("2.Acceso al sistema.\n");
        puts("3.Salir/Exit.\n");
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
                exitProgram();
            default:
                printf("Opcion incorrecta\n");
                break;
        }
    }while( op != 3 );
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
        fflush( stdin );

        switch( op ){
            case 1:
                registerNewRoster( user.ID );
                break;
            case 2:
                listRostersByUserID( user.ID );
                showUserMenuConfigRoster();
                break;
            case 3:
                listRostersByUserID( user.ID );
                break;
            case 4:
                deleteRoster( user.ID );
                break;
            case 5:
                showRostersRanking();
                break;
            case 6:
                exitProgram();
            default:
                printf("Opcion incorrecta\n");
                break;
        }
    }while( op != 6 );
}

static void showUserMenuConfigRoster(){
    int op;
    do{
        printf("------------------------------------Menu---------------------------------------- \n");

        puts("1.Lista de jugadores en plantilla.\n");
        puts("2.Lista de jugadores displonibles.\n");
        puts("3.Añadir jugador a plantilla.\n");
        puts("4.Eliminar jugador de plantilla.\n");
        puts("5.volver.\n");
        puts("Introduzca una opcion: ");
        scanf("%d", &op);
        fflush( stdin );

        switch( op ){
            case 1:
                listRostersByUserID( user.ID );
                break;
            case 2:
                listPlayers();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                printf("Opcion incorrecta\n");
                break;
        }
    }while( op != 5 );
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
        fflush( stdin );

        switch( op ){
            case 1:
                listTeams();
                break;
            case 2:
                ratePlayer();
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
        fflush( stdin );

        switch( op ){
            case 1:
                showAdminMenuTeam();
                break;
            case 2:
                showAdminMenuUser();
                break;
            case 3:
                showAdminMenuConfig();
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

static void showAdminMenuConfig(){
    int op;
    do{
        printf("------------------------------------Menu---------------------------------------- \n");

        puts("1.Editar numero maximo de equipos por usuario.\n");
        puts("2.Editar presupuesto inicial.\n");
        puts("3.Editar numero jugadores por equipo \n");
        puts("4.Salir del programa\n");
        puts("Introduzca una opcion: ");
        scanf("%d", &op);
        fflush( stdin );

        switch( op ){
            case 1:
                setMaxTeams();
                break;
            case 2:
                setDefaultInitMoney();
                break;
            case 3:
                setMaxPlayersPerTeam();
                break;
            case 4:
                //exit(1);
                break;
            default:
                printf("Opcion incorrecta\n");
                break;
        }
    }while( op != 4 );
}

static void showAdminMenuUser(){
    int op;
    do{
        printf("------------------------------------Menu---------------------------------------- \n");

        puts("1.Listar usuarios.\n");
        puts("2.Añadir nuevo usuario.\n");
        puts("3.Modificar usuario existente.\n");
        puts("4.Eliminar usuario existente.\n");
        puts("5.Salir del sistema\n");
        puts("Introduzca una opcion: ");
        scanf("%d", &op);
        fflush( stdin );

        switch( op ){
            case 1:
                listUsers();
                break;
            case 2:
                registerNewUserByAdmin();
                break;
            case 3:
                break;
            case 4:
                deleteUser();
                break;
            case 5:
                //exit(1);
                break;
            default:
                printf("Opcion incorrecta\n");
                break;
        }
    }while( op != 5 );
}

static void showAdminMenuTeam(){
    int op;
    do{
        printf("------------------------------------Menu---------------------------------------- \n");

        puts("1.Listar equipos.\n");
        puts("2.Añadir nuevo equipo.\n");
        puts("3.Modificar equipo existente.\n");
        puts("4.Eliminar equipo existente.\n");
        puts("5.Salir del sistema\n");
        puts("Introduzca una opcion: ");
        scanf("%d", &op);
        fflush( stdin );

        switch( op ){
            case 1:
                listTeams();
                break;
            case 2:
                addNewTeam();
                break;
            case 3:
                break;
            case 4:
                deleteTeam();
                break;
            case 5:
                //exit(1);
                break;
            default:
                printf("Opcion incorrecta\n");
                break;
        }
    }while( op != 5 );
}

static void init(){
    loadUsers();
    loadTeams();
    loadPlayers();
    loadConfig();
    loadRosters();
    loadRostersPlayers();
}

static void exitProgram(){
    saveUsers();
    saveTeams();
    saveConfig();
    savePlayers();
    saveRosters();
    //saveRostersPlayers();
    exit(1);
}

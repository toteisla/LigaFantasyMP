#include "Roster.h"

//Private function declarations
static void sortRosters();
static void sortRostersByScore();
static int getLastRosterID();
static int rosterNameUsed( char* rosterName );
static int getNumRostersByUserID( int userID );
static int getNumPlayersInRoster( int rosterID );
static int getIdx( int userID, int rosterID );

//Private vars
static T_Roster *rosters;
static int tamRosters; //Size of rosters vector

static T_RosterPlayers *rPlayers;
static int tamPlayers;

//Public functions
void listRosters(){
    sortRosters();
    int i;
    char str[ 64 ];
    printf( "\nLista de plantillas:\n" );
    for( i = 0 ; i < tamRosters ; i++){
        sprintf( str, "%02d-%03d-%s-%d-%d", rosters[i].userID, rosters[i].rosterID, rosters[i].rosterName, rosters[i].rosterMoney, rosters[i].rosterScore );
        printf( "%s\n", str );
    }
    printf( "\n" );
}

void listRostersByUserID( int userID ){
    sortRosters();
    int i;
    char str[ 64 ];
    printf( "\nLista de plantillas:\n" );
    for( i = 0 ; i < tamRosters ; i++){
        if( rosters[i].userID == userID ){
            sprintf( str, "%d.\n\tNombre: %s\n\tSaldo: %d\n\tPuntuacion: %d", rosters[i].rosterID, rosters[i].rosterName, rosters[i].rosterMoney, rosters[i].rosterScore );
            printf( "%s\n", str );
        }
    }
    printf( "\n" );
}

//Register a new user from main menu before log into the system.
void registerNewRoster( int userID ){
    int ID;
    char rosterName[32];

    if( getNumRostersByUserID( userID ) >= getMaxTeams() )//Check if the user has reach the maxTeams count.
        printf( "\nHa alcanzado el numero maximo de plantillas.\n" );
    else{
        do{
        printf( "\nIntroduzca el nombre para la plantilla(30 caracteres maximo):  \n" );
            gets( rosterName );
            fflush( stdin );
        }while( rosterNameUsed( rosterName ));

        sortRosters();

        rosters = (T_Roster *) realloc(rosters, ( tamRosters + 1 ) * sizeof( T_Roster ));

        ID = getLastRosterID();

        rosters[tamRosters].userID = userID;
        rosters[tamRosters].rosterID = ID;
        strcpy( rosters[tamRosters].rosterName, rosterName );
        rosters[tamRosters].rosterMoney = getDefaultInitMoney();
        rosters[tamRosters].rosterScore = 0;

        tamRosters++;
    }
}

//Remove a roster and reallocate the vector to fix the empty position.
void deleteRoster( int userID ){
    int cod, i, aux;

    listRostersByUserID( userID );

    printf( "\nIntroduzca el codigo de la plantilla:  \n" );
    scanf( "%d", &cod );
    fflush( stdin );

    for( i=0 ; i < tamRosters ; i++ ){
        if( rosters[i].rosterID == cod && rosters[i].userID == userID ) {
            aux = 1;
            i++;
        }
        if( aux == 1 )
            rosters[i-1] = rosters[i];
    }
    if(aux == 1)
        rosters = ( T_Roster * ) realloc( rosters, ( --tamRosters )*sizeof( T_Roster ));
}

//Load the roster list from 'Plantillas.txt'.
void loadRosters(){
    rosters = ( T_Roster * ) calloc(0, sizeof( T_Roster ));
	FILE *file;
	int idx = 0;

	if(( file = fopen( "Plantillas.txt" , "r" )) == NULL ){
		printf("ERROR: No existe el archivo 'Plantillas.txt'\n");
	}else{
        char str[64];
        char* aux;
        while(fgets(str, 64, file) != NULL){
            T_Roster a;

            aux = strtok( str, "\n" ); //Take away \n readed from the file.
            strcpy(str, aux);

            aux = strtok( str, "-" );
            a.userID = atoi( aux );

            aux = strtok( NULL, "-" );
            a.rosterID = atoi( aux );

            aux = strtok( NULL, "-" );
            strcpy(a.rosterName , aux);

            aux = strtok( NULL, "-" );
            a.rosterMoney = atoi( aux );

            aux = strtok( NULL, "-" );
            a.rosterScore = atoi( aux );

            rosters = (T_Roster *) realloc(rosters, ( idx + 1  )* sizeof( T_Roster ));
            rosters[ idx ] = a;
            idx++;
        }
        fclose( file );
        tamRosters = idx;
    }
}

void loadRostersPlayers(){
    rPlayers = ( T_RosterPlayers * ) calloc(0, sizeof( T_RosterPlayers ));
	FILE *file;
	int idx = 0;

	if(( file = fopen( "Jugadores_Plantillas.txt" , "r" )) == NULL ){
		printf("ERROR: No existe el archivo 'Jugadores_Plantillas.txt'\n");
	}else{
        //char str[52] , cod[2], fullname[20], type[13], username[5], password[8];
        char str[8];
        char* aux;
        while(fgets(str, 8, file) != NULL){
            T_RosterPlayers a;

            aux = strtok( str, "\n" ); //Take away \n readed from the file.
            strcpy(str, aux);

            aux = strtok( str, "-" );
            a.playerID = atoi( aux );

            aux = strtok( NULL, "-" );
            a.rosterID = atoi( aux );

            rPlayers = (T_RosterPlayers *) realloc(rPlayers, ( idx + 1  )* sizeof( T_RosterPlayers ));
            rPlayers[ idx ] = a;
            idx++;
        }
        fclose( file );
        tamRosters = idx;
    }
}

//Save the roster list to 'Plantillas.txt'.
void saveRosters(){
    int i;
    char str[60];
    printf("Guardando.\n");
    FILE *file;
    if(( file = fopen( "Plantillas.txt" , "w+" )) == NULL){
        printf("ERROR: Error de lectura/escritura del archivo.");
    }else{
        for( i = 0 ; i < tamRosters ; i++ ){
            sprintf( str, "%02d-%03d-%s-%d-%d", rosters[i].userID, rosters[i].rosterID, rosters[i].rosterName, rosters[i].rosterMoney, rosters[i].rosterScore );
            if( i != tamRosters - 1) //Fix the \n on the last line.
                strcat(str, "\n");
            fputs( str, file );
        }
        fclose(file);
    }
}

//Save the roster players list to 'Jugadroes_Plantillas.txt'.
void saveRostersPlayers(){
    int i, j;
    char str[16];
    printf("Guardando.\n");
    FILE *file;
    if(( file = fopen( "Jugadores_Plantillas.txt" , "w+" )) == NULL){
        printf("ERROR: Error de lectura/escritura del archivo.");
    }else{
        for( i = 0 ; i < tamRosters ; i++ ){
           //[TO-DO]LIST PLAYER IN ROSTER
        }
        fclose(file);
    }
}

//Check if the rosterName is in use.
static int rosterNameUsed( char* rosterName ){
    int i;
    for( i = 0 ; i < tamRosters ; i++ ){
        if( strcmp(rosters[i].rosterName, rosterName) == 0){
            printf("Ya existe una plantilla con ese nombre.\n");
            return 1;
        }
    }
    return 0;
}

//Return the first availible id.
static int getLastRosterID(){
    int i;

    sortRosters();
    for( i = 0 ; i < tamRosters ; i++ ){
        if( rosters[i].rosterID != i )
            return i;
    }
}

//Sort the roster list by rosterID.
static void sortRosters(){
    int i, j, auxUserID, auxRosterID, auxMoney, auxScore;
    char auxName[32];

    for( i = 1 ; i <= tamRosters ; i++ ){
        for( j = 0 ; j <= tamRosters - 2 ; j++ ){
            if( rosters[j].rosterID > rosters[j+1].rosterID ){
                auxUserID = rosters[j].userID;
                auxRosterID = rosters[j].rosterID;
                strcpy(auxName, rosters[j].rosterName);
                auxMoney = rosters[j].rosterMoney;
                auxScore = rosters[j].rosterScore;

                rosters[j].userID = rosters[j+1].userID;
                rosters[j].rosterID = rosters[j+1].rosterID;
                strcpy(rosters[j].rosterName, rosters[j+1].rosterName);
                rosters[j].rosterMoney = rosters[j+1].rosterMoney;
                rosters[j].rosterScore = rosters[j+1].rosterScore;

                rosters[j+1].userID = auxUserID;
                rosters[j+1].rosterID = auxRosterID;
                strcpy(rosters[j+1].rosterName, auxName);
                rosters[j+1].rosterMoney = auxMoney;
                rosters[j+1].rosterScore = auxScore;
            }
        }
    }
}

static void sortRostersByScore(){
    int i, j, auxUserID, auxRosterID, auxMoney, auxScore;
    char auxName[32];

    for( i = 1 ; i <= tamRosters ; i++ ){
        for( j = 0 ; j <= tamRosters - 2 ; j++ ){
            if( rosters[j].rosterScore > rosters[j+1].rosterScore ){
                auxUserID = rosters[j].userID;
                auxRosterID = rosters[j].rosterID;
                strcpy(auxName, rosters[j].rosterName);
                auxMoney = rosters[j].rosterMoney;
                auxScore = rosters[j].rosterScore;

                rosters[j].userID = rosters[j+1].userID;
                rosters[j].rosterID = rosters[j+1].rosterID;
                strcpy(rosters[j].rosterName, rosters[j+1].rosterName);
                rosters[j].rosterMoney = rosters[j+1].rosterMoney;
                rosters[j].rosterScore = rosters[j+1].rosterScore;

                rosters[j+1].userID = auxUserID;
                rosters[j+1].rosterID = auxRosterID;
                strcpy(rosters[j+1].rosterName, auxName);
                rosters[j+1].rosterMoney = auxMoney;
                rosters[j+1].rosterScore = auxScore;
            }
        }
    }
}

static int getNumRostersByUserID( int userID ){
    int i, cont = 0;
    for( i = 0 ; i < tamRosters ; i++ ){
        if( rosters[i].userID == userID )
            cont++;
    }
    return cont;
}

static int getNumPlayersInRoster( int rosterID ){
    int i, cont = 0;
    for( i = 0 ; i < tamRosters ; i++ ){
        if( rosters[i].rosterID == rosterID )
            cont++;
    }
    return cont;
}

void showRostersRanking(){
    sortRostersByScore();

    switch( tamRosters ){
        case 0:
            printf( "No hay plantillas para listar" );
            break;
        case 1:
            printf("1. %s: %d\n", rosters[tamRosters - 1].rosterName, rosters[tamRosters - 1].rosterScore );
            break;
        case 2:
            printf("1. %s: %d\n2. %s: %d\n", rosters[tamRosters - 1].rosterName, rosters[tamRosters - 1].rosterScore,
                   rosters[tamRosters - 2].rosterName, rosters[tamRosters - 2].rosterScore );
            break;
        default:
            printf("1. %s: %d\n2. %s: %d\n3. %s: %d\n", rosters[tamRosters - 1].rosterName, rosters[tamRosters - 1].rosterScore,
                   rosters[tamRosters - 2].rosterName, rosters[tamRosters - 2].rosterScore,
                   rosters[tamRosters - 3].rosterName, rosters[tamRosters - 3].rosterScore );

    }

    sortRosters();
}

void addPlayerToRoster( int userID, int rosterID ){
    int playerID;
    T_Player player;
    listPlayers();

    if( getNumPlayersInRoster( rosterID ) >= getMaxPlayersPerTeam() )
        printf("No puedes tener mas jugadores en el equipo.\n");
    else{
        do{
            printf("Introduce codigo jugador:  \n");
            scanf("%d", &playerID);

            player = getPlayerByID( playerID );
        }while( player.playerID == -1 );

        if( rosters[getIdx(userID, rosterID)].rosterMoney < player.price )
            printf( "No tienes suficiente dinero para comprar este jugador.\n" );
        else{
            printf( "%s ha unido a tu plantilla por %d millones.", player.playerName, player.price );
            //[TO-DO]AÑADIR JUGADOR AL ROSTER
        }
    }
}

static int getIdx( int userID, int rosterID ){
    int i;
    for( i = 0 ; i < tamRosters ; i++ ){
        if( rosters[i].rosterID == rosterID && rosters[i].userID == userID )
            return i;
    }
    return -1;
}

#include "Player.h"

//Private function declarations
static void sortPlayers();
static int getLastPlayerID();
static int getIdxByPlayerID( int playerID );

//Private vars
static T_Player *players;
static int tam; //Size of players vector

//Public functions
void listPlayers(){
    sortPlayers();
    int i;
    char str[ 32 ];
    printf( "\nLista de jugadores:\n" );
    for( i = 0 ; i < tam ; i++){
        sprintf( str, "%d %s %s %d", players[i].playerID, players[i].playerName, getTeamNameByID( players[i].teamID ), players[i].price );
        printf( "%s\n", str );
    }
    printf( "\n" );
}

void listPlayersByTeam(){
    int teamID, i;
    char* teamName;
    char str[ 32 ];
    char auxTeamID[8];

    sortPlayers();

    printf( "\nLista de equpos:\n" );
    listTeams();

    printf( "Introduzca el id del equipo para saber sus jugadores:  \n" );
    gets( auxTeamID );
    fflush( stdin );

    teamID = atoi( auxTeamID );
    printf( "%d", teamID );


    teamName = getTeamNameByID( teamID );
    printf( "\nLista de jugadores del %s:\n", teamName );
    for( i = 0 ; i < tam ; i++){
        if( players[i].teamID == teamID ){
            sprintf( str, "%02d-%s", players[i].playerID, players[i].playerName );
            printf( "%s\n", str );
        }
    }
    printf( "\n" );
}

void ratePlayer(){
    int i, playerID, rate;
    char auxPlayerID[8];
    char auxRate[8];

    listPlayersByTeam();

    do{
        printf( "Introduzca el id del jugador para valorarlo:  \n" );
        gets( auxPlayerID );
        fflush( stdin );

        playerID = atoi( auxPlayerID );
    }while( playerID < 0 || playerID > tam );

    do{
        printf( "Introduzca la valoracion del jugador:  \n" );
        gets( auxRate );
        fflush( stdin );

        rate = atoi( auxRate );
    }while( rate < 0 || rate > 10 );

    players[ getIdxByPlayerID( playerID ) ].rate = rate;
}

//Load the players list from 'Jugadores.txt'.
void loadPlayers(){
    players = ( T_Player * ) calloc(0, sizeof( T_Player ));
	FILE *file;
	int idx = 0;

	if(( file = fopen( "Jugadores.txt" , "r" )) == NULL ){
		printf("ERROR: No existe el archivo 'Jugadores.txt'\n");
	}else{
        char str[52];
        char* aux;
        while(fgets(str, 64, file) != NULL){
            T_Player a;

            aux = strtok( str, "\n" ); //Take away \n readed from the file.
            strcpy(str, aux);

            aux = strtok( str, "-" );
            a.playerID = atoi( aux );

            aux = strtok( NULL, "-" );
            a.teamID = atoi( aux );

            aux = strtok( NULL, "-" );
            strcpy(a.playerName , aux);

            aux = strtok( NULL, "-" );
            a.price = atoi( aux );

            aux = strtok( NULL, "-" );
            a.rate = atoi( aux );

            players = (T_Player *) realloc( players, ( idx + 1  )* sizeof( T_Player ));
            players[ idx ] = a;
            idx++;
        }
        fclose( file );
        tam = idx;
    }
}

//Save the user list to 'Jugadores.txt'.
void savePlayers(){
    int i;
    char str[64];
    printf("Guardando.\n");
    FILE *file;
    if(( file = fopen( "Jugadores.txt" , "w+" )) == NULL){
        printf("ERROR: Error de lectura/escritura del archivo.");
    }else{
        for( i = 0 ; i < tam ; i++ ){
            sprintf( str, "%02d-%02d-%s-%d-%d", players[i].playerID, players[i].teamID, players[i].playerName, players[i].price, players[i].rate );
            if( i != tam - 1) //Fix the \n on the last line.
                strcat(str, "\n");
            fputs( str, file );
        }
        fclose(file);
    }
}

//Sort the player list by ID.
static void sortPlayers(){
    int i, j, auxPID, auxTID, auxPrice, auxRate;
    char auxName[32];

    for( i = 1 ; i <= tam ; i++ ){
        for( j = 0 ; j <= tam - 2 ; j++ ){
            if( players[j].playerID > players[j+1].playerID ){
                auxPID = players[j].playerID;
                auxTID = players[j].teamID;
                strcpy(auxName, players[j].playerName);
                auxPrice = players[j].price;
                auxRate = players[j].rate;

                players[j].playerID = players[j+1].playerID;
                players[j].teamID = players[j+1].teamID;
                strcpy(players[j].playerName, players[j+1].playerName);
                players[j].price = players[j+1].price;
                players[j].rate = players[j+1].rate;

                players[j+1].playerID = auxPID;
                players[j+1].teamID = auxTID;
                strcpy(players[j+1].playerName, auxName);
                players[j+1].price = auxPrice;
                players[j+1].rate = auxRate;
            }
        }
    }
}

static int getIdxByPlayerID( int playerID ){
    int i;
    for( i = 0 ; i <= tam ; i++ ){
        if( players[i].playerID == playerID )
            return i;
    }
}

T_Player getPlayerByID( int playerID ){
    int i;
    for( i = 0 ; i <= tam ; i++ ){
        if( players[i].playerID == playerID )
            return players[i];
    }

    T_Player a = { .playerID = -1, .teamID = -1, .playerName = "NotFound", .price = -1, .rate = -1 };
    return a;
}

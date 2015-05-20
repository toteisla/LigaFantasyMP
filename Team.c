#include "Team.h"

//Private function declarations
static void sortTeams();
static int getLastTeamID();
static int teamNameUsed( char* teamName );

//Private vars
static T_Team *teams;
static int tam; //Size of teams vector

//Public functions
void listTeams(){
    sortTeams();
    int i;
    char str[ 32 ];
    printf( "\nLista de equipos:\n" );
    for( i = 0 ; i < tam ; i++){
        sprintf( str, "%02d-%s", teams[i].ID, teams[i].teamName );
        printf( "%s\n", str );
    }
    printf( "\n" );
}

//Register a new user from main menu before log into the system.
void addNewTeam(){
    int ID;
    char teamName[32];

    do{
        printf( "\nIntroduzca el nombre del equipo(5 caracteres maximo):  \n" );
        gets( teamName );
        fflush( stdin );
    }while( teamNameUsed( teamName ));

    sortTeams();

    teams = ( T_Team * ) realloc( teams, ( tam + 1 ) * sizeof( T_Team ));

    ID = getLastTeamID();
    teams[ tam ].ID = ID;
    strcpy( teams[tam].teamName, teamName );
    tam++;
}

//Remove a user and reallocate the vector to fix the empty position.
void deleteTeam(){
    int cod, i, aux;

    printf( "\nIntroduzca el codigo del equipo:  \n" );
    scanf( "%d", &cod );
    fflush( stdin );

    for( i = 0 ; i < tam ; i++ ){
        if( teams[i].ID == cod ) {
            aux = 1;
            i++;
        }
        if( aux == 1 )
            teams[i-1] = teams[i];
    }
    if(aux == 1)
        teams = ( T_Team * ) realloc( teams, ( --tam )*sizeof( T_Team ));
}

//Load the user list from 'Usuarios.txt'.
void loadTeams(){
    teams = ( T_Team * ) calloc(0, sizeof( T_Team ));
	FILE *file;
	int idx = 0;

	if(( file = fopen( "Equipos.txt" , "r" )) == NULL ){
		printf("ERROR: No existe el archivo 'Equipos.txt'\n");
	}else{
        char str[32];
        char* aux;
        while(fgets(str, 32, file) != NULL){
            T_Team a;

            aux = strtok( str, "\n" ); //Take away \n readed from the file.
            strcpy(str, aux);

            aux = strtok( str, "-" );
            a.ID = atoi( aux );

            aux = strtok( NULL, "-" );
            strcpy(a.teamName , aux);

            teams = ( T_Team * ) realloc(teams, ( idx + 1  )* sizeof( T_Team ));
            teams[ idx ] = a;
            idx++;
        }
        fclose( file );
        tam = idx;
    }
}

//Save the user list to 'Equipos.txt'.
void saveTeams(){
    int i;
    char str[60];
    printf("Guardando.\n");
    FILE *file;
    if(( file = fopen( "Equipos.txt" , "w+" )) == NULL){
        printf("ERROR: Error de lectura/escritura del archivo.");
    }else{
        for( i = 0 ; i < tam ; i++ ){
            sprintf( str, "%02d-%s", teams[i].ID, teams[i].teamName );
            if( i != tam - 1) //Fix the \n on the last line.
                strcat(str, "\n");
            fputs( str, file );
        }
        fclose(file);
    }
}

//Check if the team name is in use.
static int teamNameUsed( char* teamName ){
    int i;
    for( i = 0 ; i < tam ; i++ ){
        if( strcmp( teams[i].teamName, teamName ) == 0){
            printf("Ya existe un equipo con ese nombre.\n");
            return 1;
        }
    }
    return 0;
}

//Return the first availible id.
static int getLastTeamID(){
    int i;

    sortTeams();
    for( i = 0 ; i < tam ; i++ ){
        if( teams[i].ID != i )
            return i;
    }
}

//Sort the user list by ID.
static void sortTeams(){
    int i, j, auxID;
    char auxName[32];

    for( i = 0 ; i <= tam ; i++ ){
        for( j = 0 ; j <= tam - 2 ; j++ ){
            if( teams[j].ID > teams[j+1].ID ){
                auxID = teams[j].ID;
                strcpy(auxName, teams[j].teamName);

                teams[j].ID = teams[j+1].ID;
                strcpy(teams[j].teamName, teams[j+1].teamName);

                teams[j+1].ID = auxID;
                strcpy(teams[j+1].teamName, auxName);
            }
        }
    }
}

T_Team* getTeamList(){
    return teams;
}

char* getTeamNameByID( int teamID ){
    int i;
    for( i = 0 ; i <= tam ; i++ ){
        if( teams[i].ID == teamID )
            return teams[i].teamName;
    }
    return "NotFound";
}



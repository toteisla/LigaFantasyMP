#include "Config.h"

//Private vars
static T_Config config;

//Public functions
//Load the user list from 'Configuracion.txt'.
void loadConfig(){
	FILE *file;

	if(( file = fopen( "Configuracion.txt" , "r" )) == NULL ){
		printf("ERROR: No existe el archivo 'Configuracion.txt'\n");
	}else{
        char str[32];
        char* aux;
        while( fgets(str, 32, file ) != NULL ){

            aux = strtok( str, "\n" ); //Take away \n readed from the file.
            strcpy(str, aux);

            aux = strtok( str, "-" );
            if( strcmp( aux, "n_maximo_equipos") == 0 ){
                aux = strtok( NULL, "-" );
                config.maxTeams = atoi( aux );
            }
            else if( strcmp( aux, "Presupuesto_defecto") == 0 ){
                aux = strtok( NULL, "-" );
                config.defaultInitMoney = atoi( aux );
            }
            else if( strcmp( aux, "N_maximo_jugadores_equipo") == 0 ){
                aux = strtok( NULL, "-" );
                config.maxPlayersPerTeam = atoi( aux );
            }
        }
        fclose( file );
    }
}

//Save the user list to 'Configuracion.txt'.
void saveConfig(){
    char str[32];
    printf("Guardando.\n");
    FILE *file;
    if(( file = fopen( "Configuracion.txt" , "w+" )) == NULL){
        printf("ERROR: Error de lectura/escritura del archivo.");
    }else{
        sprintf( str, "n_maximo_equipos-%d\n", config.maxTeams );
        fputs( str, file );

        sprintf( str, "Presupuesto_defecto-%d\n", config.defaultInitMoney );
        fputs( str, file );

        sprintf( str, "N_maximo_jugadores_equipo-%d", config.maxPlayersPerTeam );
        fputs( str, file );

        fclose(file);
    }
}

void setMaxTeams(){
    char aux[8];

    printf( "Introduzca el nuevo valor:  \n" );
    gets( aux );

    config.maxTeams = atoi( aux );
}

void setDefaultInitMoney(){
    char aux[8];

    printf( "Introduzca el nuevo valor:  \n" );
    gets( aux );

    config.defaultInitMoney = atoi( aux );
}

void setMaxPlayersPerTeam(){
    char aux[8];

    printf( "Introduzca el nuevo valor:  \n" );
    gets( aux );

    config.maxPlayersPerTeam = atoi( aux );
}

int getMaxTeams(){
    return config.maxTeams;
}

int getDefaultInitMoney(){
    return config.defaultInitMoney;
}

int getMaxPlayersPerTeam(){
    return config.maxPlayersPerTeam;
}




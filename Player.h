#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Team.h"

typedef struct {
    int playerID;
    int teamID;
    char playerName[32];
    int price;
    int rate;
}T_Player;

void loadPlayers();
void savePlayers();
void listPlayers();
void listPlayersByTeam();
void ratePlayer();
void buyPlayer();
char* getPlayerNameByID( int playerID );
int checkPlayerByID( int playerID );

#endif // _PLAYER_H_

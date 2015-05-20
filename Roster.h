#ifndef _ROSTER_H_
#define _ROSTER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Config.h"
#include "Player.h"

typedef struct {
    int userID;
    int rosterID;
    char rosterName[32];
    int rosterMoney;
    int rosterScore;
    T_Player* rosterPlayers;
}T_Roster;

void registerNewRoster( int userID );
void deleteRoster( int userID );
void listRosters();
void listRostersByUserID( int userID );
void saveRosters();
void loadRosters();
void showRostersRanking();
void addPlayerToRoster( int userID, int rosterID );

#endif // _ROSTER_H_

#ifndef _TEAMS_H_
#define _TEAMS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int ID;
    char teamName[32];
}T_Team;

void addNewTeam();
void deleteTeam();
void listTeams();
void saveTeams();
void loadTeams();
char* getTeamNameByID( int teamID );
T_Team* getTeamList();

#endif // _TEAMS_H_

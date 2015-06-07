#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int maxTeams;
    int defaultInitMoney;
    int maxPlayersPerTeam;
}T_Config;

void loadConfig();
void saveConfig();
int getMaxTeams();
void setMaxTeams();
int getDefaultInitMoney();
void setDefaultInitMoney();
int getMaxPlayersPerTeam();
void setMaxPlayersPerTeam();
T_Config getConfig();

#endif // _CONFIG_H_

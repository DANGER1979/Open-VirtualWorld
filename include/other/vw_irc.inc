//для IRC
new PlayersChannel[MAX_PLAYERS];

#define MAX_IRC 10
enum ircInfo
{
	iAdmin[24],
	iMOTD[128],
	iPassword[20],
	iNeedPass,
	iLock,
	iPlayers
};
new IRCInfo[MAX_IRC][ircInfo];

stock irc_OnPlayerConnect(playerid)
{
	PlayersChannel[playerid] = MAX_PLAYERS-1;//для IRC
}

stock irc_OnPlayerDisconnect(playerid)
{
	if(PlayersChannel[playerid] < MAX_PLAYERS-1) IRCInfo[PlayersChannel[playerid]][iPlayers] -= 1;
}
//для IRC
stock LoadIRC()
{
	new time = GetTickCount();
	new File: iFile = fopen("Logs/channels.cfg", io_read);//io_readwrite
	if(iFile)
	{
		new arrCoords[5][MAX_STRING];
		new strFromFile[10*MAX_STRING];
		//new idx;
		//while (idx < MAX_IRC)
		for(new idx=0; idx<MAX_IRC; idx++)
		{
			fread(iFile, strFromFile);
			split(strFromFile, arrCoords, '|');
			strmid(IRCInfo[idx][iAdmin], arrCoords[0], 0, strlen(arrCoords[0]), 24);
			strmid(IRCInfo[idx][iMOTD], arrCoords[1], 0, strlen(arrCoords[1]), 128);
			strmid(IRCInfo[idx][iPassword], arrCoords[2], 0, strlen(arrCoords[2]), 20);
			IRCInfo[idx][iNeedPass] = strval(arrCoords[3]);
			IRCInfo[idx][iLock] = strval(arrCoords[4]);
//printf("IRC:%d Admin:%s MOTD: %s Password: %s NeedPass: %d Lock: %d",idx,IRCInfo[idx][iAdmin],IRCInfo[idx][iMOTD],IRCInfo[idx][iPassword],IRCInfo[idx][iNeedPass],IRCInfo[idx][iLock]);
			//idx ++;
		}
		fclose(iFile);
	}
	printf("7/19. [Загрузка каналов IRC]: Было загружено - %d, потрачено - %d (ms)", MAX_IRC, (GetTickCount()-time));
}
stock SaveIRC()
{
	new time = GetTickCount();
	new File: iFile = fopen("Logs/channels.cfg", io_write);
	if(iFile)
	{
		new coordsstring[10*(17 + 24+128+20+1+1+2)];
		for(new idx=0; idx<MAX_IRC; idx++)
		{
			format(coordsstring, sizeof(coordsstring), "%s|%s|%s|%d|%d\n",
			IRCInfo[idx][iAdmin],
			IRCInfo[idx][iMOTD],
			IRCInfo[idx][iPassword],
			IRCInfo[idx][iNeedPass],
			IRCInfo[idx][iLock]);
			//idx ++;
			//fwrite(file, coordsstring);
		    for(new c=0; c<strlen(coordsstring); c++)
			{
				fputchar(iFile, coordsstring[c], false);
		    }
		}
		fclose(iFile);
	}
//ИНФОРМИРОВАНИЕ
	new strtmp[73+2+6];
	format(strtmp, sizeof(strtmp), "7/19. [Сохранение каналов IRC]: Было сохранено - %d, потрачено - %d (ms)", MAX_IRC, (GetTickCount()-time));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
}//для IRC



stock IRC_OnGameModeInit()
{
	IRCInfo[0][iPlayers] = 0; IRCInfo[1][iPlayers] = 0;
	IRCInfo[2][iPlayers] = 0; IRCInfo[3][iPlayers] = 0;
	IRCInfo[4][iPlayers] = 0; IRCInfo[5][iPlayers] = 0;
	IRCInfo[6][iPlayers] = 0; IRCInfo[7][iPlayers] = 0;
	IRCInfo[8][iPlayers] = 0; IRCInfo[9][iPlayers] = 0;
}

stock News_OnGameModeInit()
{
    new name_offer[MAX_PLAYER_NAME];
    new name_hitman[MAX_PLAYER_NAME];
	News[hTaken1] = 0;	News[hTaken2] = 0;	News[hTaken3] = 0;	News[hTaken4] = 0;	News[hTaken5] = 0;//для киллеров
	format(name_offer, sizeof(name_offer), "Nothing");
	strmid(News[hAdd1], name_offer, 0, strlen(name_offer), 24);
	strmid(News[hAdd2], name_offer, 0, strlen(name_offer), 24);
	strmid(News[hAdd3], name_offer, 0, strlen(name_offer), 24);
	strmid(News[hAdd4], name_offer, 0, strlen(name_offer), 24);
	strmid(News[hAdd5], name_offer, 0, strlen(name_offer), 24);
	format(name_hitman, sizeof(name_hitman), "No-One");
	strmid(News[hContact1], name_hitman, 0, strlen(name_hitman), 24);
	strmid(News[hContact2], name_hitman, 0, strlen(name_hitman), 24);
	strmid(News[hContact3], name_hitman, 0, strlen(name_hitman), 24);
	strmid(News[hContact4], name_hitman, 0, strlen(name_hitman), 24);
	strmid(News[hContact5], name_hitman, 0, strlen(name_hitman), 24);
}

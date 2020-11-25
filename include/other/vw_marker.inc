//СИСТЕМА УСТАНОВКИ и СНЯТИЯ МАРКЕРА НА ИГРОКА

//для маркеров
new CurPlayerColorMarker[MAX_PLAYERS];//хранит новый цвет игрока
new OldPlayerColorMarker[MAX_PLAYERS];//хранит новый цвет игрока
new MarkerToPlayer[MAX_PLAYERS];//содержит ID розыскиваемого на которого установил маркер игрок playerid
new MarkerForPlayer[MAX_PLAYERS];//содержит ID копа по индексу розыскиваемого
new gWantedSystem[MAX_PLAYERS];



stock marker_OnPlayerConnect(playerid)
{
	CurPlayerColorMarker[playerid] = COLOR_NEWBIE;
	OldPlayerColorMarker[playerid] = COLOR_DEAD;
	MarkerToPlayer[playerid] = MAX_PLAYERS-1;//для детективов
	MarkerForPlayer[playerid] = MAX_PLAYERS-1;//для детективов
	gWantedSystem[playerid] = 0;
}

stock SetPlayerMarkerForPlayerEx(playerid, showplayerid, color)
{//игроку playerid установить маркер на игрока showplayerid( MarkerToPlayer[playerid] ) цвета color

	//if(IsPlayerNPC(playerid)) { return 1; }
	//if(IsPlayerNPC(showplayerid)) { return 1; }
	if( !IsPlayerConnectedEx(showplayerid) ) return 1;
	if( !gPlayerSpawned[showplayerid] ) return 1;
	//if(GetPlayerColor(showplayerid) == COLOR_TURQUOISE) return 1;

//если маркер устанавилвается на другого игрока, то надо вернуть предыдущему старый цвет
	if(showplayerid != MarkerToPlayer[playerid] && MarkerToPlayer[playerid] != MAX_PLAYERS-1)
	{
		SetPlayerMarkerForPlayer(playerid, MarkerToPlayer[playerid], OldPlayerColorMarker[MarkerToPlayer[playerid]]);//COLOR_ALIVE //вернули старый цвет
	}
	//if(MarkerToPlayer[playerid] == MAX_PLAYERS-1)
	//{   //если маркер на игрока ещё не был установлен (устанавливается впервые), то установить новый цвет
	MarkerToPlayer[playerid] = showplayerid;//записали showplayerid розыскиваемого на которого установил маркер игрок playerid
	MarkerForPlayer[showplayerid] = playerid;//записали игрока playerid который установил маркер на showplayerid
	OldPlayerColorMarker[showplayerid] = GetPlayerColor(showplayerid);//сохранили старый цвет
	CurPlayerColorMarker[showplayerid] = color;//записали новый цвет
	SetPlayerMarkerForPlayer(playerid, showplayerid, color);//установили новый цвет
	//ИНФОРМИРОВАНИЕ
	//////new strings[MAX_STRING];
	format(strings, sizeof(strings), "%s[%d] установил маркер на {%06x}%s[%d]",
		PlayerName(playerid), playerid, color >>> 72, PlayerName(showplayerid), showplayerid);
	//ABroadCast(COLOR_PINK,strings,9);
	SendClientMessage(playerid, COLOR_BRIGHTLYGREEN, strings);
	if(PlayerInfo[showplayerid][pAdmin] >= 6)
	{
		SendClientMessage(showplayerid, COLOR_BRIGHTLYGREEN, strings);
	}
	return 1;
}


stock marker_OnPlayerCommandText(playerid, cmdtext[])
{
	new tmp[MAX_STRING], gMessage[MAX_STRING];
	//new strcmd[MAX_STRING];
	new cmd[20], idx;//, giveplayerid;
	cmd = strtok(cmdtext, idx);//Возвращает  аргумент номер которого указан в переменной &index
	if(!strcmp(cmd, "/marker", true))
	{
        if(PlayerInfo[playerid][pAdmin] != 9)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
            return 1;
        }
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /marker [playerid/PartOfName]");
			return 1;
		}
		giveplayerid = ReturnUser(tmp);// && !IsPlayerNPC(giveplayerid)  && PlayerInfo[giveplayerid][pAdmin] >= 9
		if(IsPlayerConnected(giveplayerid))
		{
		    if(MarkerToPlayer[playerid] == MAX_PLAYERS-1)
			{//playerid - ID игрока, которому нужно показать маркер, giveplayerid - тот кто будет обозначен
				SetPlayerMarkerForPlayerEx(playerid, giveplayerid, ( GetPlayerColor(giveplayerid) & 0xFFFFFF00 ));// 0xFF0000FF COLOR_LIGHTBLUE
				format(strcmd, sizeof(strcmd), "* Маркер на игроке %s[%d] установлен.", PlayerName(giveplayerid), giveplayerid);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);
				//gMarkerFor[playerid] = 1;
			}
			else //if(MarkerToPlayer[playerid] != MAX_PLAYERS-1)
			{
				//SetPlayerMarkerForPlayerEx(playerid, MarkerToPlayer[playerid], COLOR_ALIVE);// 0xFF0000FF
				SetPlayerMarkerForPlayerEx(playerid, MarkerToPlayer[playerid], ACTION_COLOR);
				format(strcmd, sizeof(strcmd), "* Маркер c игрока %s[%d] снят.", PlayerName(giveplayerid), giveplayerid);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);
			}
		}
		//return 1;
	}
	return 1;//0;
}

//������� ��������� � ������ ������� �� ������

//��� ��������
new CurPlayerColorMarker[MAX_PLAYERS];//������ ����� ���� ������
new OldPlayerColorMarker[MAX_PLAYERS];//������ ����� ���� ������
new MarkerToPlayer[MAX_PLAYERS];//�������� ID �������������� �� �������� ��������� ������ ����� playerid
new MarkerForPlayer[MAX_PLAYERS];//�������� ID ���� �� ������� ��������������
new gWantedSystem[MAX_PLAYERS];



stock marker_OnPlayerConnect(playerid)
{
	CurPlayerColorMarker[playerid] = COLOR_NEWBIE;
	OldPlayerColorMarker[playerid] = COLOR_DEAD;
	MarkerToPlayer[playerid] = MAX_PLAYERS-1;//��� ����������
	MarkerForPlayer[playerid] = MAX_PLAYERS-1;//��� ����������
	gWantedSystem[playerid] = 0;
}

stock SetPlayerMarkerForPlayerEx(playerid, showplayerid, color)
{//������ playerid ���������� ������ �� ������ showplayerid( MarkerToPlayer[playerid] ) ����� color

	//if(IsPlayerNPC(playerid)) { return 1; }
	//if(IsPlayerNPC(showplayerid)) { return 1; }
	if( !IsPlayerConnectedEx(showplayerid) ) return 1;
	if( !gPlayerSpawned[showplayerid] ) return 1;
	//if(GetPlayerColor(showplayerid) == COLOR_TURQUOISE) return 1;

//���� ������ ��������������� �� ������� ������, �� ���� ������� ����������� ������ ����
	if(showplayerid != MarkerToPlayer[playerid] && MarkerToPlayer[playerid] != MAX_PLAYERS-1)
	{
		SetPlayerMarkerForPlayer(playerid, MarkerToPlayer[playerid], OldPlayerColorMarker[MarkerToPlayer[playerid]]);//COLOR_ALIVE //������� ������ ����
	}
	//if(MarkerToPlayer[playerid] == MAX_PLAYERS-1)
	//{   //���� ������ �� ������ ��� �� ��� ���������� (��������������� �������), �� ���������� ����� ����
	MarkerToPlayer[playerid] = showplayerid;//�������� showplayerid �������������� �� �������� ��������� ������ ����� playerid
	MarkerForPlayer[showplayerid] = playerid;//�������� ������ playerid ������� ��������� ������ �� showplayerid
	OldPlayerColorMarker[showplayerid] = GetPlayerColor(showplayerid);//��������� ������ ����
	CurPlayerColorMarker[showplayerid] = color;//�������� ����� ����
	SetPlayerMarkerForPlayer(playerid, showplayerid, color);//���������� ����� ����
	//��������������
	//////new strings[MAX_STRING];
	format(strings, sizeof(strings), "%s[%d] ��������� ������ �� {%06x}%s[%d]",
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
	cmd = strtok(cmdtext, idx);//����������  �������� ����� �������� ������ � ���������� &index
	if(!strcmp(cmd, "/marker", true))
	{
        if(PlayerInfo[playerid][pAdmin] != 9)
        {
            SendClientMessage(playerid, COLOR_GREY, "   �� �� ������������ ������������ ��� ������� !");
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
			{//playerid - ID ������, �������� ����� �������� ������, giveplayerid - ��� ��� ����� ���������
				SetPlayerMarkerForPlayerEx(playerid, giveplayerid, ( GetPlayerColor(giveplayerid) & 0xFFFFFF00 ));// 0xFF0000FF COLOR_LIGHTBLUE
				format(strcmd, sizeof(strcmd), "* ������ �� ������ %s[%d] ����������.", PlayerName(giveplayerid), giveplayerid);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);
				//gMarkerFor[playerid] = 1;
			}
			else //if(MarkerToPlayer[playerid] != MAX_PLAYERS-1)
			{
				//SetPlayerMarkerForPlayerEx(playerid, MarkerToPlayer[playerid], COLOR_ALIVE);// 0xFF0000FF
				SetPlayerMarkerForPlayerEx(playerid, MarkerToPlayer[playerid], ACTION_COLOR);
				format(strcmd, sizeof(strcmd), "* ������ c ������ %s[%d] ����.", PlayerName(giveplayerid), giveplayerid);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);
			}
		}
		//return 1;
	}
	return 1;//0;
}

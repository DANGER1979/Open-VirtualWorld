new FollowBy[MAX_PLAYERS];//������ �� �������� �� �� �������������
new FollowTimer[MAX_PLAYERS];//��� ������


stock follow_OnPlayerConnect(playerid)//OnPlayerFollowInit(playerid)
{
	FollowTimer[playerid] = MAX_PLAYERS-1;
	FollowBy[playerid] = MAX_PLAYERS-1;
	SetPVarInt(playerid, "TempFollowBy", -1);
}

stock follow_OnPlayerDeath(playerid)
{
	new GotPVar = GetPVarInt(playerid, "TempFollowBy");
	if(FollowBy[playerid] != MAX_PLAYERS-1)//��� ������
	{
		SetPVarInt(FollowBy[playerid], "TempFollowBy", -1);
		KillTimer(FollowTimer[playerid]);
		FollowTimer[playerid] = MAX_PLAYERS-1;
    	FollowBy[playerid] = MAX_PLAYERS-1;
		SendClientMessage(FollowBy[playerid], COLOR_GREY, "   ��� ����������� ���� !");
    }
	else if(GotPVar != -1)
	{
		TogglePlayerControllableEx(GotPVar, 1);
		SetPVarInt(playerid, "TempFollowBy", -1);
		KillTimer(FollowTimer[GotPVar]);
		FollowTimer[GotPVar] = MAX_PLAYERS-1;
    	FollowBy[GotPVar] = MAX_PLAYERS-1;
		SendClientMessage(GotPVar, COLOR_GREY, "   ��� ������� ���� !");
    }
}

stock follow_OnPlayerSpawn(playerid)
{
	new GotPVar = GetPVarInt(playerid, "TempFollowBy");
	if(FollowBy[playerid] != MAX_PLAYERS-1)//��� ������
	{
		SetPVarInt(FollowBy[playerid], "TempFollowBy", -1);
		KillTimer(FollowTimer[playerid]);
		FollowTimer[playerid] = MAX_PLAYERS-1;
    	FollowBy[playerid] = MAX_PLAYERS-1;
		//SendClientMessage(FollowBy[playerid], COLOR_GREY, "   ��� ����������� ���� !");
    }
	else if(GotPVar != -1)
	{
		TogglePlayerControllableEx(GotPVar, 1);
		SetPVarInt(playerid, "TempFollowBy", -1);
		KillTimer(FollowTimer[GotPVar]);
		FollowTimer[GotPVar] = MAX_PLAYERS-1;
    	FollowBy[GotPVar] = MAX_PLAYERS-1;
		//SendClientMessage(GotPVar, COLOR_GREY, "   ��� ������� ���� !");
    }
}

stock follow_OnPlayerDisconnect(playerid)
{
	if(FollowBy[playerid] != MAX_PLAYERS-1)//��� ������
	{
		OnPlayerAutoInPunish(playerid);

		SetPVarInt(FollowBy[playerid], "TempFollowBy", -1);
		KillTimer(FollowTimer[playerid]);
		FollowTimer[playerid] = MAX_PLAYERS-1;
    	FollowBy[playerid] = MAX_PLAYERS-1;
		SendClientMessage(FollowBy[playerid], COLOR_GREY, "   ��� ����������� ������� ������ !");
    }
    FollowBy[playerid] = MAX_PLAYERS-1;
}

stock follow_OnPlayerEnterVehicle(playerid)
{
	if(FollowBy[playerid] != MAX_PLAYERS-1)
	{
		TogglePlayerControllable(playerid, 0);//�������������
		ClearAnimations(playerid, 1);

		KillTimer(FollowTimer[playerid]); FollowTimer[playerid] = -1;
		FollowTimer[playerid] = SetTimerEx("FollowToPlayerTimer", 1000, 1, "d", playerid);
	}
	else if(IsPlayerControllable[playerid] == 1)
	{//���� ��� ���������, �� �������� �����������
		TogglePlayerControllable(playerid, 0);//false - �������������
		ClearAnimations(playerid, 1);
		//ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,0,0,0,0,1);
		//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	}
}


forward FollowToPlayerTimer(playerid);//��� ������
public FollowToPlayerTimer(playerid)//��������� ������
{   //���������� �� ������� /follow
	//if(	IsPlayerNPC(playerid) ) return 1;
	new timers = GetTickCount();
	//static AnimShot[MAX_PLAYERS];
//��������
//static ������ ��������� ������ 1 ��� � ���������� �� ���������� �������, ������� ��������� ��� ���� �� ��������.
//�.�. �������� ��������� ������� ������ ��� �� ���������� ���������� ����� ������� ��������:
//� ��� ��������� ����������, ������� ������� ���� ��� � � ������� �������� ��������� ���������.
//PS ������ ����������, ������ ��� ��� ���������� �����, �������� ��������� �� �����������.
	if(!IsPlayerConnected(FollowBy[playerid]))
	{
	    KillTimer(FollowTimer[playerid]);
		TogglePlayerControllableEx(playerid, 1);
		ClearAnimations(playerid, 1);

		//new strings[MAX_STRING];
	    format(strings, sizeof(strings), "�� ��������, ������ %s[%d] ������� ������!", PlayerName(FollowBy[playerid]), FollowBy[playerid]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);

        FollowTimer[playerid] = MAX_PLAYERS-1;
		FollowBy[playerid] = MAX_PLAYERS-1;
		//AnimShot[playerid] = false;
		return 1;
	}
	else if(!IsPlayerConnected(playerid))
	{
	    KillTimer(FollowTimer[playerid]);

		//new strings[MAX_STRING];
	    format(strings, sizeof(strings), "������������ %s[%d] ������� ������!", PlayerName(playerid), playerid);
		SendClientMessage(FollowBy[playerid], COLOR_LIGHTBLUE, strings);

		SetPVarInt(FollowBy[playerid], "TempFollowBy", -1);
        FollowTimer[playerid] = MAX_PLAYERS-1;
        //AnimShot[playerid] = false;
		FollowBy[playerid] = MAX_PLAYERS-1;
		return 1;
	}
	else if(FollowBy[playerid] == MAX_PLAYERS-1)
	{
	    KillTimer(FollowTimer[playerid]);

 		TogglePlayerControllableEx(playerid, 1);
		ClearAnimations(playerid, 1);

		SendClientMessage(playerid, COLOR_LIGHTBLUE, "� ����� ������� ��������� ����, �� ��������!");

        FollowTimer[playerid] = MAX_PLAYERS-1;
        //AnimShot[playerid] = false;
	    return 1;
	}
	else if(IsPlayerInAnyVehicle(playerid))
	{
	    KillTimer(FollowTimer[playerid]);

        SendClientMessage(FollowBy[playerid], COLOR_LIGHTBLUE, "��� ����������� � ������! ������ ����������!");

		SetPVarInt(FollowBy[playerid], "TempFollowBy", -1);
        FollowTimer[playerid] = MAX_PLAYERS-1;
        //AnimShot[playerid] = false;
		FollowBy[playerid] = MAX_PLAYERS-1;
	    return 1;
	}
	else if(PlayerInfo[FollowBy[playerid]][pVirtual] != PlayerInfo[playerid][pVirtual]
		|| PlayerInfo[FollowBy[playerid]][pInt] != PlayerInfo[playerid][pInt])
	{
		new Float: X, Float: Y, Float: Z;
		GetPlayerPos(FollowBy[playerid], X, Y, Z);
		SetPlayerPosEx(playerid, X, Y, Z, 0);
		SetPlayerVirtualWorldEx(playerid, PlayerInfo[FollowBy[playerid]][pVirtual]);
		SetPlayerInteriorEx(playerid, PlayerInfo[FollowBy[playerid]][pInt]);
		TogglePlayerControllableEx(playerid, 0);
		//AnimShot[playerid] = false;
		return 1;
	}

	new Float: GotDistance = GetDistanceBetweenPlayers(playerid, FollowBy[playerid]);
 	if(GotDistance < 0.95)
 	{
        TogglePlayerControllableEx(playerid, 0);
        SetPlayerToFacePlayer(playerid, FollowBy[playerid]);
        //AnimShot[playerid] = false;
        return 1;
  	}
 	else if(GotDistance > 10.0)
 	{
 		SetPVarInt(FollowBy[playerid], "TempFollowBy", -1);
        SendClientMessage(FollowBy[playerid], COLOR_LIGHTBLUE, "�� ���� ������� ������ �� �������������! ������ ��������!");
        SendClientMessage(playerid, COLOR_LIGHTBLUE, "��� ������ ���� ������� ������, �� ��������!");
        TogglePlayerControllableEx(playerid, 1);
        ClearAnimations(playerid, 1);
 	    KillTimer(FollowTimer[playerid]);
        FollowTimer[playerid] = MAX_PLAYERS-1;
		FollowBy[playerid] = MAX_PLAYERS-1;
  	}
  	else
  	{
  	    TogglePlayerControllableEx(playerid, 1);
  	    SetPlayerToFacePlayer(playerid, FollowBy[playerid]);
  	    //OnePlayAnim(playerid, "ped", "run_player", 6.0, 1, 1, 1, 1, 0);
  	    //OnePlayAnim(playerid, "ped", "Walk_Wuzi", 6.0, 1, 1, 1, 1, 0);
  	    //OnePlayAnim(playerid, "ped", "WALK_civi", 6.0, 1, 1, 1, 1, 0);
  	    ApplyAnimation(playerid, "PED","RUN_OLD",6.0,1,1,1,1,0);
	}
	TestLog(OPTIM, "FollowToPlayerTimer", GetTickCount(), timers);//new timers = GetTickCount();
  	return 1;
}


//##############################################################################//
//                                                                              //
//                              ������� ����������                             //
//                                                                              //
//##############################################################################//
new WatchingTVCounter[MAX_PLAYERS];



stock spectate_OnPlayerConnect(playerid)
{
	spectateid[playerid] = MAX_PLAYERS-1; spectatorid[playerid] = MAX_PLAYERS-1; Unspec[playerid][sLocal] = FREEROAM;
	gWatchingTV[playerid] = -1;//��� ������� ��
}

stock spectate_OnPlayerStateChange(playerid, newstate)
{
	if(newstate == PLAYER_STATE_ONFOOT)//���� ID ������ ��������� ����� ��������� �� �����
	{   //���� ID ������ ��������� ����� ��������� 1

		//���������� � SetVehicleToRespawnEx
	    if(spectatorid[playerid] != MAX_PLAYERS-1)
	    {   //���� � playerid ���� �����������
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) ) continue;
				if(spectateid[i] == playerid)// - �� � ���� ������
				{	//����������� ���� ��� ��������� �� playerid
		   			PlayerSpectatePlayer(i, playerid);
		   		}
	   		}
		}
	}
	else if(newstate == PLAYER_STATE_DRIVER) //buggy dont finnish  //���� ID ������ ��������� ����� ��������� �� ����
	{	//���� ID ������ ��������� ����� ��������� 2
	    if(spectatorid[playerid] != MAX_PLAYERS-1)
	    {   //���� � playerid ���� �����������
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnected(i) || IsPlayerNPC(i)) continue;
				if( !gPlayerLogged[i] ) continue;
				if(spectateid[i] == playerid)// - �� � ���� ������
				{//����������� ���� �� ������ ��� ��������� �� playerid
		   			PlayerSpectateVehicle(i, nCarID[playerid]);
		   		}
	   		}
		}
	}
	else if(newstate == PLAYER_STATE_PASSENGER)
	{   //���� ID ������ ��������� ����� ��������� 3 - ��������
	    if(spectatorid[playerid] != MAX_PLAYERS-1)
	    {   //���� � playerid ���� �����������
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnected(i) || IsPlayerNPC(i)) continue;
				if( !gPlayerLogged[i] ) continue;
				if(spectateid[i] == playerid)// - �� � ���� ������
				{	//����������� ���� �� ������ ��� ��������� �� playerid
		   			PlayerSpectateVehicle(i, nCarID[playerid]);
		   		}
	   		}
		}
	}
	
	
}

stock spectate_OneSecondTimers(playerid)//����������� ������ 2 �������
{
	if(AFK_IdleTime[playerid] >= 3) return 1;
	if(PlayerInfo[playerid][pAdmin] < 1) return 1;
	if(gWatchingTV[playerid] != -1) return 1;
	new targetid = spectateid[playerid];
	if(targetid == MAX_PLAYERS-1) return 1;//���� ��������� �� ���������� �� ������ ������ � ID
	if(!IsPlayerConnected(targetid)) return 1;//Targetid No connected

	//��� ��
	if(gWatchingTV[playerid] != -1)
	{
		if(IsPlayerConnectedEx(gTranslatorTV))
		{
			WatchingTVCounter[gTranslatorTV] += 1;
			new strtmp[8+10];
		    format(strtmp, sizeof(strtmp), "+~g~$%d", WatchingTVCounter[gTranslatorTV]);
		    GameTextForPlayerEx(gTranslatorTV, strtmp, 5000, 6);
		}
	}
	
	new Float: health;
    GetPlayerHealth(targetid, health);
    new money = GetPlayerMoney(targetid);
	//new strings[MAX_STRING];
	new strtmp[3*38+24+3+3+10+3+5+32+3];
    if(	IsPlayerInAnyVehicle(targetid) &&
		GetPlayerState(targetid) == PLAYER_STATE_DRIVER)
	{
		CrashDetected[playerid] = 62;
	    new carid = nCarID[targetid];
		GetVehicleHealth(carid, VehHealth[carid]);

    	format(strtmp, sizeof(strtmp), "~n~~n~~n~~n~~n~~n~~b~%s ~r~ID:~w~%d\
~n~~g~health:~w~%.0f ~g~money:~w~%d\
~n~~g~VehHEAL:~w~%.0f ~g~Fuel:~w~%.0f",
			PlayerName(targetid),targetid,
			LastHealth[targetid],money,
			VehHealth[carid],
			(VehInfo[carid][cFuel]*100.0/VehicleArray[nCarModel[targetid]-400][GasMax])
			);
	}
	else
	{
		CrashDetected[playerid] = 63;
		format(strtmp, sizeof(strtmp), "~n~~n~~n~~n~~n~~n~~b~%s~r~ID:~w~%d\
~n~~g~health:~w~%.0f ~g~money:~w~%d\
~n~~g~Gun:~w~%d ~g~Ammo:~w~%d",
			PlayerName(targetid),targetid,
			LastHealth[targetid],money,
			GetPlayerWeapon(targetid), GetPlayerAmmo(targetid));
	}
    GameTextForPlayerEx(playerid, strtmp, 2500, 3); // ��� ������� ���������� ����� ��� ������ ������ �� ������ ����
	return 1;
}


stock spectate_OnPlayerInterior(playerid, newinteriorid, oldinteriorid)
{
    if(spectatorid[playerid] != MAX_PLAYERS-1)
    {   //���� � playerid ���� �����������
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;//��������� �� ���������, �� ���������
			if(spectateid[i] == playerid && newinteriorid != oldinteriorid)// - �� � ���� ������
			{	//spectateid[i] = ID ������ �� ������� �� ���������� //����������� ���� �� playerid
				SetPlayerVirtualWorldEx(i, PlayerInfo[playerid][pVirtual]);
				SetPlayerInteriorEx(i, newinteriorid);//PlayerInfo[playerid][pInt]);
				PlayerInfo[i][pLocal] = PlayerInfo[playerid][pLocal];
	   		}
   		}
	}
}


stock ReconOn(playerid, giveplayerid)
{
    if(PlayerInfo[playerid][pJailed] >= 1 && PlayerInfo[playerid][pJailed] <= 3)
    {
		SendClientMessage(playerid, COLOR_GREY, "   �� ���� �� ������ ��������������� ������ ��������, ����� ���������� !");
        return 1;
    }
    if(PlayerCuffed[playerid] != MAX_PLAYERS-1)
    {
		SendClientMessage(playerid, COLOR_GREY, "   �� ���� �� ������ ��������������� ������ ��������, ����� � ��� ������ ��������� !");
        return 1;
    }
	if(PlayerTied[playerid] > 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ��������������� � ������ ������ ��������, ����� ������� !");
        return 1;
	}
	if(PlayerTazed[playerid] > 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ��������������� � ������ ������ ��������, ����� �������� !");
		return 1;
	}
	if(FollowBy[playerid] != MAX_PLAYERS-1)
	{
	    SendClientMessage(playerid, COLOR_GREY, "   �� ���� �� ������ ��������������� ������ �������� !");
	    return 1;
	}

	if(giveplayerid == playerid)
	{
		SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ �������� �� ������ ����!");
		return 1;
	}
    if(	!IsPlayerConnected(giveplayerid) )
	{
		format(strings, sizeof(strings), "   ID:%d ����������� �� �������.", giveplayerid); SendClientMessage(playerid, COLOR_GREY, strings);
		return 1;
	}

	if(spectateid[playerid] == MAX_PLAYERS-1 /*&& CurState[playerid] == PLAYER_STATE_ONFOOT*/)
	{   //���� �� �� �� ��� �� ����������
		GetPlayerHealth(playerid, LastHealth[playerid]);
		GetPlayerPos(playerid, Unspec[playerid][sPx], Unspec[playerid][sPy], Unspec[playerid][sPz]);
		//�������� � Unspec[playerid][sPx] ���� �������
		Unspec[playerid][sInt] = PlayerInfo[playerid][pInt];
		Unspec[playerid][sLocal] = PlayerInfo[playerid][pLocal];
		Unspec[playerid][sVirtual] = PlayerInfo[playerid][pVirtual];
	}
	spectateid[playerid] = giveplayerid;//�������� ID ������ �� ������� �� ����������
	spectatorid[giveplayerid] = playerid;//�������� ID ������ ������� �� ���� ���������

	//TogglePlayerControllableEx(playerid, 0);//������������� - ����� �� ������ ���������
    TogglePlayerSpectatingEx(playerid, 1);//����������� ������ � ����� ������� Ensure that you TogglePlayerSpectatingEx before using PlayerSpectatePlayer.
	SetPlayerVirtualWorldEx(playerid, PlayerInfo[giveplayerid][pVirtual]);
	SetPlayerInteriorEx(playerid, PlayerInfo[giveplayerid][pInt]);
	PlayerInfo[playerid][pLocal] = PlayerInfo[giveplayerid][pLocal];

    if(IsPlayerInAnyVehicle(giveplayerid))
	{
  		PlayerSpectateVehicle(playerid, GetPlayerVehicleID(giveplayerid));//, SPECTATE_MODE_SIDE //��������� ������ ��������� �� ������������ ��������� � ������ ����������
	}
	else
	{
		PlayerSpectatePlayer(playerid, giveplayerid);//, SPECTATE_MODE_FIXED //��������� ������ ��������� �� ������ ������� � ������ ����������

		/*new Float:X, Float:Y, Float:Z;
	  	new Float:X2, Float:Y2, Float:Z2, Float:Ang2;
		GetPlayerPos(giveplayerid, X2, Y2, Z2);
		X = X2;
		Y = Y2;
		Z = Z2;
		GetXYZInFrontOfPlayer(playerid, 2.0, X2,Y2,Z2, Ang2);
		//new Float:angle;
		//GetPlayerFacingAngle(giveplayerid, angle);

		InterpolateCameraPos(playerid, X, Y, Z, X2, Y2, Z2, 10000);*/
		//InterpolateCameraLookAt(playerid, X, Y, Z, 0.0, 0.0, 0.0, 10000);
	}
	//new strings[MAX_STRING];
	//format(strings, sizeof(strings), "%s[%d] SPECTATING to %s[%d]", PlayerName(playerid), playerid, PlayerName(spectateid[playerid]), spectateid[playerid]);
	format(strings, sizeof(strings), "AdmCmd: %s[%d] observation %s[%d]", PlayerName(playerid), playerid, PlayerName(spectateid[playerid]), spectateid[playerid]);
	//SendSystemMessage(COLOR_MAROON, strings, 7);
	SendAllAdminMessage(COLOR_MAROON, strings, 7);
	return 1;
}


stock ReconOff(playerid)
{
	//------------------------------------------------------------------
	TogglePlayerSpectatingEx(playerid, 0);//��������� ����� ����������.
	PlayerInfo[playerid][pVirtual] = Unspec[playerid][sVirtual];
	PlayerInfo[playerid][pInt] = Unspec[playerid][sInt];
	PlayerInfo[playerid][pLocal] = Unspec[playerid][sLocal];
	Unspec[playerid][sLocal] = FREEROAM;

	if(	PlayerInfo[playerid][pChar] > 0 && PlayerInfo[playerid][pChar] != SKIN_DEFAULT
		//&&	( (PlayerInfo[playerid][pTeam] == 1 && gOnDuty[playerid]) ||
 		//	PlayerInfo[playerid][pTeam] == 2)
	  )
	{
		SetSpawnInfoEx(playerid,
			PlayerInfo[playerid][pTeam],
			PlayerInfo[playerid][pChar],
			Unspec[playerid][sPx],
			Unspec[playerid][sPy],
			Unspec[playerid][sPz],
			0.0, -1, -1, -1, -1, -1, -1);//Unspec[playerid][sPz]-1.0
	}
	else
	{
		SetSpawnInfoEx(playerid,
			PlayerInfo[playerid][pTeam],
			PlayerInfo[playerid][pModel],
			Unspec[playerid][sPx],
			Unspec[playerid][sPy],
			Unspec[playerid][sPz],
			0.0, -1, -1, -1, -1, -1, -1);//Unspec[playerid][sPz]-1.0
	}
	//�������� ���������� �� ���������� ���������� ������ � ��������� �������
	//SetPlayerToTeamColor(15);//������� �������������� ����
	//gMedicBill[playerid] = 0;
	SpawnPlayer(playerid);
	CurPos[0][playerid] = Unspec[playerid][sPx];
	CurPos[1][playerid] = Unspec[playerid][sPy];
	CurInt[playerid] = 0;
	
	checkcheat[playerid] = CHEATLIM;//��� ��������
//OnPlayerSetDutyWeapons(playerid);//��������� �-�� ��������� ������
	/*for(new weaponid = 22; weaponid <= 32; weaponid++)//MAX_WEAPONS
	{   //��������� �� ������������� ������
		if(LastAmmo[playerid][weaponid] > 0 && LastAmmo[playerid][weaponid] < 1000)
		{   //�� ���� � ������� ���� �������
			new slot = GetWeaponSlot(weaponid);
			new weapom = LastWeaponInSlot[playerid][slot];
			if(weapom == weaponid)
			{//���� ��������� ������ � ���� ����� ����
				GivePlayerWeapon(playerid, weapon, LastAmmo[playerid][weapon]);//�����
				DetectedGun[playerid][weaponid] = 1;
			}

		}
	}*/
	for(new slot = 2; slot <= 5;  slot++)//MAX_WEAPONS
	{   //��������� �� ������������� ������
		new weaponid = LastWeaponInSlot[playerid][slot];
		if(LastAmmo[playerid][weaponid] > 0 && LastAmmo[playerid][weaponid] < 1000)
		{   //�� ���� � ������� ���� �������
			GivePlayerWeapon(playerid, weaponid, LastAmmo[playerid][weaponid]);
			DetectedGun[playerid][weaponid] = 1;
		}
	}
	spectatorid[spectateid[playerid]] = MAX_PLAYERS-1;
	spectateid[playerid] = MAX_PLAYERS-1;//��������� � ���������

	//��������������
	//////new strings[MAX_STRING];
	//format(strings, sizeof(strings), "spectateid[%d] = %d Team=%d gOnDuty=%d", Playerid,spectateid[playerid], PlayerInfo[playerid][pTeam], gOnDuty[playerid]);
	//SendClientMessage(playerid, COLOR_GREY, strings);
	return 1;
}


stock spectate_OnPlayerCommandText(playerid, cmdtext[])
{
		new tmp[MAX_STRING], strcmd[MAX_STRING];
		new cmd[20], idx, giveplayerid;
		cmd = strtok(cmdtext, idx);//����������  �������� ����� �������� ������ � ���������� &index
        if(//strcmp(PlayerInfo[giveplayerid][pReferal], PlayerName(playerid), true) &&
			!(PlayerInfo[playerid][pAdmin] == 1 || PlayerInfo[playerid][pAdmin] == 3 || PlayerInfo[playerid][pAdmin] >= 5) &&
        	PlayerInfo[playerid][pLeader] == 0)
		{
            SendClientMessage(playerid, COLOR_GREY, "   �� �� ������������ ������������ ��� ������� !");
            //SendClientMessage(playerid, COLOR_GREY, "   ��� ���� ����� �� �������� ����� �������� !");
            return 1;
        }
		if( PlayerInfo[playerid][pLeader] != 0 && PlayerInfo[playerid][pMember] != PlayerInfo[giveplayerid][pMember] &&
			!(PlayerInfo[playerid][pAdmin] == 1 || PlayerInfo[playerid][pAdmin] == 3 || PlayerInfo[playerid][pAdmin] >= 5) )
		{
            SendClientMessage(playerid, COLOR_GREY, "   �� ������������ ��������� ������ �� ������� ����� ������� !");
            return 1;
        }
 		if( PlayerInfo[playerid][pAdmin] == 2 && !IsAGangs(giveplayerid) )
		{
            SendClientMessage(playerid, COLOR_GREY, "   �� ������������ ��������� ������ �� ������� ���� !");
            return 1;
        }
		if(spectateid[playerid] != MAX_PLAYERS-1)
		{
			ReconOff(playerid);
			GameTextForPlayerEx(playerid, "~w~                recon~n~~r~                Off", 5000, 6);
			PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			return 1;
		}
		/*if(gLoading[playerid] || gUnLoading[playerid])
		{
			SendClientMessage(playerid, COLOR_GREY, "   ��������� ��������� ��������/�������� !");
			return 1;
		}*/
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /recon [playerid/PartOfName]");
			return 1;
		}
		giveplayerid = ReturnUser(tmp);//�������� ID ���������� ������

		ReconOn(playerid, giveplayerid);

		format(strcmd, sizeof(strcmd), "SpectatorTimer:%s[%d] Level:%d Warn:%d Bank:$%d Money:$%d Heal:%.0f Drugs:%d Stoned:%d TankFuel:%d",
			PlayerName(giveplayerid), giveplayerid,	PlayerInfo[giveplayerid][pLevel], PlayerInfo[giveplayerid][pWarns], PlayerInfo[giveplayerid][pBank], GetPlayerMoneyH(giveplayerid),
			LastHealth[playerid], PlayerInfo[playerid][pDrugs],
			PlayerStoned[giveplayerid], PlayerInfo[giveplayerid][pFuel]);
		SendClientMessage(playerid, COLOR_GREEN, strcmd);
		//format(strcmd, sizeof(strcmd), "AdmCmd: %s has observation for %s's", PlayerName(playerid), PlayerName(giveplayerid));
		//Log(ADMINLOG, strcmd);
		return 1;
}

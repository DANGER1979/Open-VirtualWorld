//�-�� �� ������ c ���������� ������ ���� ��������� �������
 

stock playerselect_OnPlayerUpdate(playerid, oldkeys, animationid, newstate)
//stock playerselect_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{//���������� ����� ����� �������� ������ �������(������), � ������ ����� �������� � ����, �.�. ���������� ������ ����������� ��� �������
	//if(IsPlayerInAnyVehicle(playerid)) return 1;
	//new newstate = CurState[playerid];
	if(newstate != PLAYER_STATE_ONFOOT) return 1;

	new weapon = GetPlayerWeapon(playerid);
	if(weapon != 0) return 1;

	new newkeys, ud, lr;
    GetPlayerKeys(playerid, newkeys, ud, lr);
	#pragma unused ud
	#pragma unused lr
	//if( PRESSED(KEY_HANDBRAKE+KEY_FIRE) )//KEY_FOOT_AIM_FIRE//KEY_HANDBRAKE+KEY_FIRE = 4+128=132
	if(newkeys == KEY_HANDBRAKE+KEY_FIRE && oldkeys != KEY_HANDBRAKE+KEY_FIRE)
	{//���� ������ ���+���
	    new targetplayer = GetPlayerTargetPlayer(playerid); //Check who a player is aiming at.
		if(targetplayer == INVALID_PLAYER_ID) return 1;//&& targetplayer != 65535
		if( !IsPlayerConnected(targetplayer) ) return 1;
		if( !IsPlayerConnectedEx(targetplayer) ) return 1;

		//new animationid = GetPlayerAnimationIndex(playerid);
		if(animationid == 1136) ClearAnimations(playerid);//���� �������� �������� ��� ����� �����
		playerselect_OnPlayerClick(playerid, targetplayer);

		////new strings[MAX_STRING];
		new Float: distance;
		distance = GetDistanceBetweenPlayers(playerid, targetplayer);
		if(CHECKING[PlayerUpdate] == true)
		{
			format(strings, sizeof(strings), "IsPlayer: %s[%d] LookingAtPlayer3: %s[%d] distance: %.1f speed: %d",
				PlayerName(playerid), playerid, PlayerName(targetplayer), targetplayer, distance, GetPlayerSpeed(targetplayer));
		 	//ABroadCast(ADMINS_MESSAGE_COLOR, strings, 6);
		 	//SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strings, 6);
		 	SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, strings);
	 	}
		//------------------------------------------------------------------
		new VehicleID = 0;
		if( IsPlayerInAnyVehicle(targetplayer) )
		{
			VehicleID = GetPlayerVehicleID(targetplayer);
			distance = GetDistanceToCar(playerid, VehicleID);
		}
		if(VehicleID != 0)
		{
			if(CHECKING[PlayerUpdate] == true)
			{
				format(strings, sizeof(strings), "IsPlayer: %s[%d] LookingAtVehicle3: %d distance: %.1f speed: %d",
					PlayerName(playerid), playerid, VehicleID, distance, GetVehicleSpeed(VehicleID));
		   		//SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strings, 6);
		   		SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, strings);
		   	}
	   		VehicleID = 0;
		}
	}
	return 1;
}


//stock OnPlayerSelectPlayer(playerid, forplayerid)
stock playerselect_OnPlayerClick(playerid, forplayerid)
{   //���������� �� OnPlayerClickPlayer, LookingUpdate
	if(!IsPlayerConnected(forplayerid)) { return 1; }
	if(IsPlayerNPC(forplayerid)) { return 1; }
	//ClearAnimations(playerid);

    SetPVarInt(playerid, "PlayerID", forplayerid);
	new caption[70+1];
    format(caption, sizeof(caption), "�� ������� ������ %s[%d]", PlayerName(forplayerid), forplayerid);

    //items_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);

    MenuOperation[playerid] = 91;
    if(PlayerInfo[playerid][pAdmin] < 1)
	{
		new listitems[] = "�������������\
\n������������� �� �����\
\n�������� �������\
\n������� SMS\
\n��������� �� ��������\
\n�������� ������\
\n�������� ������\
\n�������� ��������\
\n�������� ���������\
\n�����������";
		ShowPlayerDialogEx(playerid, TAB_DIALOG, DIALOG_STYLE_LIST, caption, listitems, "��", "������");
	}
	else
	{
    	new listitems[] = "�������������\
\n������������� �� �����\
\n�������� �������\
\n������� SMS\
\n��������� �� ��������\
\n�������� ������\
\n�������� ������\
\n�������� ��������\
\n�������� ���������\
\n�����������\
\n�������";
		ShowPlayerDialogEx(playerid, TAB_DIALOG, DIALOG_STYLE_LIST, caption, listitems, "��", "������");
	}
	return 1;
}

stock playerselect_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	//#pragma unused listitem
	//#pragma unused inputtext
	if(dialogid != TAB_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response) return 1;
	new msgitem[256+1];
	new giveplayerid = GetPVarInt(playerid, "PlayerID");
	if(MenuOperation[playerid] == 91)
	{
		if(listitem == 0)//�������������
		{
			ShowPlayerNameTagForPlayerEx(giveplayerid, playerid, 1);
			OnePlayAnim(playerid, "RIOT", "RIOT_ANGRY", 4.0, 0, 0, 0, 0, 0);
			format(msgitem, sizeof(msgitem), "%s {EE66EE}������������ ���.", PlayerName(playerid));
			SendClientMessage(giveplayerid, COLOR_WHITE, msgitem);
			PlaySoundForPlayer(playerid, 4803);
		}
		else if(listitem == 1)//������������� �� �����
		{
			format(msgitem, sizeof(msgitem), "%s {EE66EE}������������ ���.", PlayerName(playerid));
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if(i == playerid) continue;
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				if(AFK_IdleTime[i] >= 3) continue;
				if(PlayerInfo[i][pLocal] != PlayerInfo[playerid][pLocal]) continue;
				ShowPlayerNameTagForPlayerEx(i, playerid, 1);
				SendClientMessage(i, COLOR_WHITE, msgitem);
			}
			OnePlayAnim(playerid, "RIOT", "RIOT_ANGRY", 4.0, 0, 0, 0, 0, 0);
			PlaySoundForPlayer(playerid, 4803);
		}
		else if(listitem == 2)//�������� �������
		{
			if(PlayerInfo[playerid][pJailed] > 0)
			{
				playerselect_OnPlayerClick(playerid, giveplayerid);
				SendClientMessage(playerid, COLOR_GREY, "   ���� ��������� �������� ���� �� ��� ������� !");
				return 1;
			}
			if( !IsPlayerConnected(giveplayerid) )
			{
				playerselect_OnPlayerClick(playerid, giveplayerid);
				format(msgitem, sizeof(msgitem), "   ID:%d ����������� �� �������.", giveplayerid);
				SendClientMessage(playerid, COLOR_GREY, msgitem);
				return 1;
			}
			if(!IsPlayerInRangeOfPlayer(8.0, playerid, giveplayerid)
				|| spectateid[playerid] != MAX_PLAYERS-1 || spectateid[giveplayerid] != MAX_PLAYERS-1)
			{
				playerselect_OnPlayerClick(playerid, giveplayerid);
				SendClientMessage(playerid, COLOR_GREY, "   ���� ����� �� ����� � ���� !");
				return 1;
			}
			if(IsPlayerInAnyVehicle(giveplayerid) && GetPlayerState(giveplayerid) == PLAYER_STATE_DRIVER)
			{
				playerselect_OnPlayerClick(playerid, giveplayerid);
				SendClientMessage(playerid, COLOR_GREY, "   ����� ��������� �� ���� ������������� �������� !");
				return 1;
			}
			if(gPlayerBoxing[giveplayerid] == 1)
			{
				playerselect_OnPlayerClick(playerid, giveplayerid);
				SendClientMessage(playerid, COLOR_GREY, "   ����� ��������� �� ����� !");
				return 1;
			}
	    	SetPVarInt(giveplayerid, "gDocuments", 1);
			OnPlayerShowStats(giveplayerid, playerid);
			//format(strcmd, sizeof(strcmd), "* %s ������� %s'� ���� ���������.", PlayerName(playerid), PlayerName(giveplayerid));
			//ProxDetector(playerid, 30.0, strcmd, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
			if(!IsPlayerInAnyVehicle(playerid)) OnePlayAnim(playerid, "TEC", "TEC_reload", 4.0, 0, 1, 1, 0, 0); //OnePlayAnim(playerid, "PED", "ATM",4.1,0,1,1,0,0);
        }
        //��� ���������
        else if(listitem == 3)//�����
        {
			if(SBizInfo[2][sbProducts] <= 0 && !gRealWar)
			{
				playerselect_OnPlayerClick(playerid, giveplayerid);
				GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Phone Company", 5000, 1);
				PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				return 1;
			}
	        format(msgitem, sizeof(msgitem),
				"������� ����� ��������� ��� ������ %s[%d] �� ����� %d.\
				 \n��������� ������ ��������� ���������� $%d.\
				 \n\n\t{8CAA63}�� ��������� ����� ������� OK.",
				 PlayerName(giveplayerid), giveplayerid,
				 PlayerInfo[giveplayerid][pPnumber],
				 SBizInfo[2][sbEntranceCost]);
		    MenuOperation[playerid] = 92;
			ShowPlayerDialogEx(playerid, TAB_DIALOG, DIALOG_STYLE_INPUT, "SMS", msgitem, "OK", "Cancel");
        }
        else if(listitem == 4)//���������
        {
			if(SBizInfo[2][sbProducts] <= 0 && !gRealWar)
			{
				playerselect_OnPlayerClick(playerid, giveplayerid);

				GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Phone Company", 5000, 1);
				PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				return 1;
			}
			if(PlayerInfo[playerid][pJob] == LOADER)
			{
				playerselect_OnPlayerClick(playerid, giveplayerid);

				SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ������������ ��������� �� ����� ������ !");
				return 1;
			}
			Call_OnPlayerSelectPlayer(playerid, giveplayerid);
		}
		else if(listitem == 5)//�������� ������ /pay
		{
			if(PlayerInfo[giveplayerid][pLocal] == 100)
			{
				SendClientMessage(playerid, COLOR_GREY, "   ������ �������� ��������� � ����� !");
				return 1;
			}
			if(PlayerInfo[playerid][pLevel] < 2)
			{
				SendClientMessage(playerid, COLOR_GREY, "   �� ������ ����� ������� 2, ����� ���������� ������.");
				return 1;
			}
			if(GetPlayerMoneyH(playerid) < 0 || PlayerInfo[playerid][pBank] < 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   � ��� ������������ ��������� ������! �� �� ������ ���� ���������� ������");
				return 1;
			}
			if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ �������� ������ ������ ����!"); return 1; }
		    if( !IsPlayerConnected(giveplayerid) )
			{
				playerselect_OnPlayerClick(playerid, giveplayerid);

				format(msgitem, sizeof(msgitem), "   ID:%d ����������� �� �������.", giveplayerid);
				SendClientMessage(playerid, COLOR_GREY, msgitem);
				return 1;
			}
			if(!IsPlayerInRangeOfPlayer(8.0, playerid, giveplayerid)
				|| spectateid[playerid] != MAX_PLAYERS-1 || spectateid[giveplayerid] != MAX_PLAYERS-1)
			{
				playerselect_OnPlayerClick(playerid, giveplayerid);
				SendClientMessage(playerid, COLOR_GREY, "   ���� ����� �� ����� � ���� !");
				return 1;
			}
			//SetPVarInt(playerid, "PlayerID", giveplayerid);
			MenuOperation[playerid] = 93;
	 		ShowPlayerDialogEx(playerid, TAB_DIALOG, DIALOG_STYLE_INPUT, "Give Money", "������� ����� ��������. \n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
        }
       	else if(listitem == 6)//�������� ������ /givegun
        {
            CMD_givegun(playerid, giveplayerid);
        }
       	else if(listitem == 7)//�������� ��������
        {
	        if( PlayerInfo[playerid][pRespect] < 20)//(OnlineRecord*100/100))// && PlayerInfo[playerid][pAdmin] < 7
	        {
				format(msgitem, sizeof(msgitem), "   � ��� %d ����� ��������. ���������� %d �����!",
					PlayerInfo[playerid][pRespect], 20); //(OnlineRecord*100/100));
				SendClientMessage(playerid, COLOR_GREY, msgitem);
				SendClientMessage(playerid, COLOR_GREY, "   ����� ������� �������� �� ������ ������������� � ���� �� �����");
				return 1;
	        }
	        if( PlayerInfo[playerid][pRespectDay] == getdate())// && PlayerInfo[playerid][pAdmin] < 7
	        {
				SendClientMessage(playerid, COLOR_GREY, "   �� ������� ��� �������� ��� �������� ����-��!");
				return 1;
	        }
		    if(giveplayerid == playerid)// && PlayerInfo[playerid][pAdmin] != 9
			{
				SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ �������� �������� ������ ���� !");
				return 1;
			}
			//if(PlayerInfo[playerid][pAdmin] < 7) PlayerInfo[playerid][pRespect] -= 1;
			//SetPlayerShowBattery(playerid, 1, PlayerInfo[playerid][pRespect], ((PlayerInfo[playerid][pLevel]+1)*4) );
			PlayerInfo[giveplayerid][pRespect] += 1;
			if(PlayerInfo[playerid][pAdmin] < 7) PlayerInfo[playerid][pRespectDay] = getdate();
			//SetPlayerShowBattery(giveplayerid, 1, PlayerInfo[giveplayerid][pRespect], ((PlayerInfo[giveplayerid][pLevel]+1)*4) );
			format(msgitem, sizeof(msgitem), "   B� �������� %s'� ��� ��������.", PlayerName(giveplayerid));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
			format(msgitem, sizeof(msgitem), "   B� �������� ��������������� �� %s'�.", PlayerName(playerid));
			SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
			SetPlayerShowBattery(giveplayerid, 1, PlayerInfo[giveplayerid][pRespect], 100);
			SendClientMessage(giveplayerid, COLOR_GREY, "   ��� 15 ����� �������� �� ������� ������ ��������� ������ �������.");
        }
       	else if(listitem == 8)//�������� ���������
        {
	        if( PlayerInfo[playerid][pRespect] < 20)//(OnlineRecord*40/100))// && PlayerInfo[playerid][pAdmin] < 7
	        {
				format(msgitem, sizeof(msgitem), "   � ��� %d ����� ��������. ���������� %d �����!",
					PlayerInfo[playerid][pRespect], 20);//(OnlineRecord*40/100));
				SendClientMessage(playerid, COLOR_GREY, msgitem);
				SendClientMessage(playerid, COLOR_GREY, "   ����� ������� �������� �� ������ ������������� � ���� �� �����");
				return 1;
	        }
	        if( PlayerInfo[playerid][pRespectDay] == getdate())// && PlayerInfo[playerid][pAdmin] < 7
	        {
				SendClientMessage(playerid, COLOR_GREY, "   �� ������� ��� �������� ����-�� ���������!");
				return 1;
	        }
		    if(giveplayerid == playerid)// && PlayerInfo[playerid][pAdmin] != 9
			{
				SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ �������� ��������� ������ ���� !");
				return 1;
			}
			//if(PlayerInfo[playerid][pAdmin] < 7) PlayerInfo[playerid][pRespect] -= 1;
			//SetPlayerShowBattery(playerid, 1, PlayerInfo[playerid][pRespect], ((PlayerInfo[playerid][pLevel]+1)*4) );
			if(PlayerInfo[giveplayerid][pRespect] > 0) PlayerInfo[giveplayerid][pRespect] -= 1;
			if(PlayerInfo[playerid][pAdmin] < 7) PlayerInfo[playerid][pRespectDay] = getdate();
			//SetPlayerShowBattery(giveplayerid, 1, PlayerInfo[giveplayerid][pRespect], ((PlayerInfo[giveplayerid][pLevel]+1)*4) );
			format(msgitem, sizeof(msgitem), "   B� �������� %s'� ��� ���������.", PlayerName(giveplayerid));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
			format(msgitem, sizeof(msgitem), "   B� �������� ��������� �� %s'�.", PlayerName(playerid));
			SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
			SetPlayerShowBattery(giveplayerid, 1, PlayerInfo[giveplayerid][pRespect], 100);
			SendClientMessage(giveplayerid, COLOR_GREY, "   ��� ����� 15 ����� �������� �� �� ������� ������ ��������� ������ �������.");
        }
       	else if(listitem == 9)//�����������
        {
			OnePlayAnim(playerid, "GANGS", "hndshkba", 4.3, 0, 0, 0, 0, 0);
			format(msgitem, sizeof(msgitem), "%s {EE66EE}���������� � ����.", PlayerName(playerid));
			SendClientMessage(giveplayerid, COLOR_WHITE, msgitem);
        }
       	else if(listitem == 10)//�������
        {
           	//Adminka(playerid, giveplayerid, listitem, inputtext);
           	//admins_OnDialogResponse(playerid, ADMINS_DIALOG, response, listitem, inputtext);
           	admin_OnPlayerClick(playerid, giveplayerid);
        }
	}
	else if(MenuOperation[playerid] == 92)// /sms
	{
		SMS_OnPlayerSelectPlayer(playerid, giveplayerid, inputtext);
	}
	else if(MenuOperation[playerid] == 93)//�������� ������ /pay
	{
		if(!strlen(inputtext))
		{
			MenuOperation[playerid] = 93;
	 		ShowPlayerDialogEx(playerid, TAB_DIALOG, DIALOG_STYLE_INPUT, "Give Money", "������� ����� ��������. \n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
			return 1;
		}
		new moneys = strval(inputtext);
		if(moneys > 1000 && PlayerInfo[playerid][pLevel] < 3)
		{
			MenuOperation[playerid] = 93;
	 		ShowPlayerDialogEx(playerid, TAB_DIALOG, DIALOG_STYLE_INPUT, "Give Money", "������� ����� ��������. \n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
			SendClientMessage(playerid, COLOR_GREY, "   �� ������ ����� ������� 3, ����� ���������� ����� 1000$");
			return 1;
		}
		if(moneys < 1000 || moneys > 1000000)//80000
		{
			MenuOperation[playerid] = 93;
	 		ShowPlayerDialogEx(playerid, TAB_DIALOG, DIALOG_STYLE_INPUT, "Give Money", "������� ����� ��������. \n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");
		    SendClientMessage(playerid, COLOR_GREY, "   ����� ������ ���� �� ���� 1000, � �� ���� 1000000 �� ���.");
		    return 1;
		}

		new playermoney = GetPlayerMoneyH(playerid);
		if(moneys > 0 && playermoney >= moneys)
		{
			GivePlayerMoneyH(fpay+PlayerInfo[giveplayerid][pSQLID], playerid, -moneys);//(0 - moneys)
			OnPlayerStatsUpdate(giveplayerid, 255);
			GivePlayerMoneyH(fpay+PlayerInfo[playerid][pSQLID], giveplayerid, moneys);
			OnPlayerStatsUpdate(playerid, 255);
			format(msgitem, sizeof(msgitem), "   B� �������� %s'�(id: %d), $%d.", PlayerName(giveplayerid),giveplayerid, moneys);
			SendClientMessage(playerid, COLOR_LILAC, msgitem);
			format(msgitem, sizeof(msgitem), "   B� �������� $%d �� %s(id: %d).", moneys, PlayerName(playerid), playerid);
			SendClientMessage(giveplayerid, COLOR_LILAC, msgitem);
			format(msgitem, sizeof(msgitem), "Sender %s has paid $%d to %s", PlayerName(playerid), moneys, PlayerName(giveplayerid));
			//Log(PAY,strcmd);
			if(moneys > 100000)	SendAllAdminMessage(COLOR_MAROON, msgitem, 1);
			PlaySoundForPlayer(giveplayerid, SOUND_AMMUNATION_BUY_WEAPON);//1052
			format(msgitem, sizeof(msgitem), "* %s ������ ������� �������� ��� %s.", PlayerName(playerid), PlayerName(giveplayerid));
			ProxDetector(playerid, 30.0, msgitem, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		}
		else
		{
			MenuOperation[playerid] = 93;
	 		ShowPlayerDialogEx(playerid, TAB_DIALOG, DIALOG_STYLE_INPUT, "Give Money", "������� ����� ��������. \n\n\t{8CAA63}�� ��������� ����� ������� OK.", "OK", "Cancel");

			SendClientMessage(playerid, COLOR_GREY, "   � ��� ��� ������� �������� ��� ����� !");
			return 1;
		}
	}
	else if(MenuOperation[playerid] == 94)
	{

	}
	return 1;
}


//��� ����� BloodBowl
new gCountdownDerbyTimer;//��� ����� BloodBowl

new gBloodBowlDoor = 0;//��� ������ �����

//��� ����� BloodBowl
new DerbiRand;
new TotalDerby = 0;
new gDerbyStarted = 0;
new derbycountdown = 16;//��� ������


new DerbyScore[MAX_PLAYERS];
//new gInDerbyBloodBowl[MAX_PLAYERS];
//��� ����� BloodBowl �����

#define MAX_DCP 33
new Float:DerbyCheckpoints[MAX_DCP][3] = {//���������� ��������
{-1435.02,1015.82,1024.54},
{-1504.81,996.37,1035.05},
{-1471.78,984.24,1025.67},
{-1315.33,981.91,1027.39},
{-1427.85,972.07,1024.07},
{-1437.80,993.85,1023.94},
{-1465.74,1012.45,1025.91},
{-1422.12,983.66,1023.74},
{-1472.57,1004.76,1025.95},
{-1295.22,1009.43,1034.69},
{-1396.9435,995.7874,1024.1089},
{-1465.7242,990.6259,1025.3236},
{-1456.2925,945.8786,1035.0167},
{-1424.7693,978.4643,1023.8688},
{-1403.0361,1022.5313,1025.3733},
{-1380.2181,1041.8391,1029.9764},
{-1410.5017,1048.2596,1034.5385},
{-1433.1271,995.2460,1024.1692},
{-1362.8341,976.3920,1023.9725},
{-1348.4768,1018.8869,1025.5570},
{-1367.3169,997.1184,1024.0800},
{-1393.2432,981.6196,1023.8686},
{-1402.0856,1012.7029,1024.3936},
{-1438.9412,985.3898,1024.0051},
{-1446.1256,1003.5920,1024.3228},
{-1434.8112,1025.1431,1025.9443},
{-1448.6874,1046.1256,1035.7034},
{-1397.5297,1060.5244,1038.5371},
{-1328.2136,1040.3771,1036.1522},
{-1303.0540,968.0173,1034.9291},
{-1362.1974,931.8026,1036.3180},
{-1417.7750,951.9228,1027.7034},
{-1397.1796,964.5116,1024.8696}
};

//��� ����� BloodBowl
stock bloodbowl_OnPlayerConnect(playerid)
{
	DerbyScore[playerid] = 0;
	gInDerbyBloodBowl[playerid] = 0;
}


//==============================================================================


forward BloodBowlCountdownTimer();//��� ����� BloodBowl ������
public BloodBowlCountdownTimer()//��� ����� BloodBowl STEP3
{   //�������� ������ ������� ����������� �� OnPlayerPickUpPickup
	new timers = GetTickCount();
	derbycountdown --;//15
	//new strings[MAX_STRING];
	if(derbycountdown <= 0)
	{
		derbycountdown = 0;
		if(gCountdownDerbyTimer != -1) { KillTimer(gCountdownDerbyTimer); gCountdownDerbyTimer = -1; }//� ����� �������
		StartDerby();//������ �����
	}
	else if(derbycountdown > 0 && derbycountdown <= 3)//��� ������������� � ������
	{
		format(strings, sizeof(strings), "%d", derbycountdown);

	   	for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i)) continue;
			if(gInDerbyBloodBowl[i])
			{   //���� ����� ������������� � �����
				SetCameraBehindPlayer(i);
				PlaySoundForPlayer(i, SOUND_RACE_321);
				GameTextForPlayerEx(i, strings, 750, 3);
				TogglePlayerControllableEx(i, 0);//�������������
			}
		}
	}
	else if(derbycountdown > 3 && derbycountdown <= 9)//��� ������������� � ������
	{

	   	for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			if(gInDerbyBloodBowl[i])
			{   //���� ����� ������������� � �����
				TogglePlayerControllableEx(i, 0);//�������������
			}
		}
	}
	else if(derbycountdown == 10 ||
		 	derbycountdown == 15)
	{

	   	for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			if( !gInDerbyBloodBowl[i] ) continue;
			//���� ����� ������������� � �����
			if(gInDerbyBloodBowl[i]) TogglePlayerControllableEx(i, 0);//�������������
			format(strings, sizeof(strings), "~r~Blood Bowl ~w~STARTING IN ~y~%d ~w~SECONDS", derbycountdown);
			GameTextForPlayerEx(i, strings, 2500, 4);
		}
	}
	else if(derbycountdown == 20 ||
		 	derbycountdown == 25 ||
		 	derbycountdown == 30 ||
		 	derbycountdown == 40 ||
		 	derbycountdown == 50 ||
		 	derbycountdown == 60 ||
		 	derbycountdown == 70 ||
		 	derbycountdown == 80 ||
		 	derbycountdown == 90)
	{
		format(strings, sizeof(strings), "����� {FF0000}Blood Bowl{FF6600} �������� ����� %d ������.", derbycountdown);

	   	for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			//if( !gInDerbyBloodBowl[i] ) continue;
			//���� ����� ������������� � �����
			if(gInDerbyBloodBowl[i]) TogglePlayerControllableEx(i, 0);//�������������
			SendClientMessage(i, COLOR_ORANGE, strings);
		}
		//format(strings, sizeof(strings), "����� {FF0000}Blood Bowl{FF6600} �������� ����� %d ������.", derbycountdown);
		//SendClientMessageToAll(COLOR_ORANGE, strings);

	}
	TestLog(OPTIM, "BloodBowlCountdownTimer", GetTickCount(), timers);//new timers = GetTickCount();
}
stock StartDerby()//��� ����� BloodBowl STEP4
{   //����������� �� BloodBowlCountdownTimer
    //GameTextForAll("~W~GO", 2000, 5);

   	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i)) continue;
		if(gInDerbyBloodBowl[i])
		{   //��������� ���� �������� � �����
			TogglePlayerControllableEx(i, 1);//����������
			PlaySoundForPlayer(i, SOUND_RACE_GO);
			GameTextForPlayerEx(i, "~W~GO", 750, 5);
		}
	}
	gDerbyStarted = 1;
}
stock BloodBowlEnterCheckpoint(playerid)//��� ����� BloodBowl STEP5
{   //���������� �� OnPlayerEnterRaceCheckpoint
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;
	nCarID[playerid] = GetPlayerVehicleID(playerid);
	if(!IsInDerbyCar(nCarID[playerid])) return 1;
	if(!gDerbyStarted) return 1;
	if(!gInDerbyBloodBowl[playerid]) return 1;

	DerbiRand = random(sizeof(DerbyCheckpoints));

   	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
		if(gInDerbyBloodBowl[i])
		{   //��������� ���� �������� � �����
			DisablePlayerRaceCheckpoint(i);
			SetPlayerRaceCheckpoint(i,2,
				DerbyCheckpoints[DerbiRand][0],DerbyCheckpoints[DerbiRand][1],DerbyCheckpoints[DerbiRand][2],
				DerbyCheckpoints[DerbiRand][0],DerbyCheckpoints[DerbiRand][1],DerbyCheckpoints[DerbiRand][2],
				6.0);
			PlaySoundForPlayer(i, SOUND_CHECKPOINT_AMBER);
		}
	}
	PlayerInfo[playerid][pCarTime] += 8;
	DerbyScore[playerid] += (1 + 10*(TotalDerby*TotalDerby-1));//compcost
	return 1;
}

//stock BloodBowlTimer(playerid)//��� ����� BloodBowl //��� ����� 8ball
stock bloodbowl_OneSecondTimers(playerid)
{   //���������� �� ���������� ������� OnPlayerCallTime
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;
	if(!gInDerbyBloodBowl[playerid]) return 1;//��� ����� BloodBowl STEP6
	if(!gDerbyStarted) return 1;
	
	PlayerInfo[playerid][pCarTime] --;
	new strTime[80+6+5+2+2];
	format(strTime, sizeof(strTime), "~p~Time   ~w~%s~n~~p~Money   ~g~$%d~n~~p~Members   ~w~%d~n~~p~CountDown   ~w~%d",
		TimeConverter(PlayerInfo[playerid][pCarTime]), DerbyScore[playerid], TotalDerby, derbycountdown);
	PlayerTextDrawSetStringEx(playerid, txdCarTime[playerid], strTime);

	if(PlayerInfo[playerid][pCarTime] <= 0 || PlayerInfo[playerid][pCarTime] >= 60)
	{   //���� ����� ����� ��� �� �������
		PlayerInfo[playerid][pParam2] = 0; gParameter2[playerid] = 0;
		SetPlayerShowScale(playerid, 2, PlayerInfo[playerid][pParam2], 50);

		//RemovePlayerFromVehicle(playerid);
		SetVehicleToRespawnEx(playerid, nCarID[playerid]);
		DisablePlayerRaceCheckpoint(playerid);

		SetPlayerVirtualWorldEx(playerid, 0);
	    SetPlayerInteriorEx(playerid, 0);
		PlayerInfo[playerid][pLocal] = FREEROAM;
		SetPlayerPosEx(playerid, -2119.5925,-443.8909,35.5313, 90.0);
		//ResetPlayerWeaponsEx(playerid);

		TotalDerby --;
		if(PlayerInfo[playerid][pCarTime] <= 0)
		{
			//KillTimer(updatederbytimer); updatederbytimer = -1;
			if(TotalDerby <= 0)
			{//���� ���-�� �������� ����� 0 � �� ��������
				gDerbyStarted = 0;//�������� ���� - ����� �����������
				TotalDerby = 0;//�������� ����� ���-�� �������� 0
				//SendClientMessageToAll(COLOR_BRIGHTLYGREEN, "����� BloodBowl �������. � ���������� ����������� �����.");
				SendAllAdminMessage(COLOR_BRIGHTLYGREEN, "����� BloodBowl �������. � ���������� ����������� �����.", 1);
			}
			//SendClientMessage(playerid, COLOR_BRIGHTLYGREEN, "� ��� ����������� �����. �� �������� ������� ����� BloodBowl.");

		   	for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				if( !gInDerbyBloodBowl[i] ) continue;
			 	//SendClientMessageToAll(COLOR_BRIGHTLYGREEN, strings);
		    	format(strings, sizeof(strings), "BloodBowl: {FFFFFF}%s[%d]{00FF00} ������� ������� ����� � ���-������. �������: ����������� �����", PlayerName(playerid), playerid);
			 	SendClientMessage(i, COLOR_BRIGHTLYGREEN, strings);
			}
		}
		else if(PlayerInfo[playerid][pCarTime] >= 60)
		{
			new money = DerbyScore[playerid] + random(501);
			GivePlayerMoneyB(fbloodbowl, playerid, money);//  *DutyFiveMinuts
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "������� � ����� BloodBowl {FFFFFF}%s[%d]{FF9900}. ����� �������� ��������� {33AA33}$%d.", PlayerName(playerid), playerid, money);//���������������
			SendClientMessageToAll(COLOR_LIGHTORANGE, strings);
			if(TotalDerby <= 0)
			{//����� ����� ������������� ������ ����� ����� ������� � ��� ��������� � �����
				//KillTimer(updatederbytimer); updatederbytimer = -1;
				gDerbyStarted = 0;//�������� ���� - ����� �����������
				TotalDerby = 0;//�������� ����� ���-�� �������� 0
				//SendClientMessageToAll(COLOR_BRIGHTLYGREEN, "����� BloodBowl �������. ��������� ����������� ������ ������.");
				SendAllAdminMessage(COLOR_BRIGHTLYGREEN, "����� BloodBowl �������. ��������� ����������� ������ ������.", 1);
			}
		}
		DerbyScore[playerid] = 0;
		PlayerInfo[playerid][pCarTime] = 0;
		gInDerbyBloodBowl[playerid] = 0;//�������� ���� - ����� �� � �����
		gTextDrawHideCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
	}
	return 1;
}

stock bloodbowl_VehicleEnterPickUp(playerid, pickupid)
{
	if(pickupid == PickupID[MAX_PLAYER_PICKUPS] && IsPlayerInRangeOfPoint(playerid, 8.0, Pickups[pickupid][p_x],Pickups[pickupid][p_y],Pickups[pickupid][p_z]) )
	{//��� ����� BloodBowl STEP0
		if(gInDerbyBloodBowl[playerid] && IsPlayerInAnyVehicle(playerid))
		{
			RepairVehicleEx(playerid, nCarID[playerid]);
			DestroyPickupEx(PickupID[0]);
			new rand = random(sizeof(RepairPickups));
			PickupID[0] = SetPickupEx(RepairPickups[rand][dp_model], RepairPickups[rand][dp_type], RepairPickups[rand][dp_x],RepairPickups[rand][dp_y],RepairPickups[rand][dp_z],15);
		}
		//return 1;
	}
}

stock bloodbowl_OnPlayerPickUp(playerid)
{
	if( !IsPlayerInRangeOfPoint(playerid, 2.2, -2110.5586,-444.1488,38.8344) ) return 1;
//���� Blood Bowl int15 ��� ����� � ��
	if(gBloodBowlDoor == 1)
	{
		GameTextForPlayerEx(playerid, "~r~Closed", 5000, 1);
		return 1;
	}
	if(PlayerInfo[playerid][pCarTime] > 0)
	{
		//GameTextForPlayerEx(playerid, "~r~Closed", 5000, 1);
		//return 1;
       	SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ������������ � ����� � �������� �� �������!");
		return 1;
	}
	/*if(GetPlayerMoneyH(playerid) < 0)
	{
       	SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ����������� � ����� c ��������� ��������!");
           return 1;
	}*/
	if(TotalDerby >= sizeof(DerbyCar)-1)
	{
		//GameTextForPlayerEx(playerid, "~r~Closed", 5000, 1);
		//return 1;
       	SendClientMessage(playerid, COLOR_GREY, "   ������� ����� ��������! ��������� ����� ��� �� ������");
		return 1;
	}
	//������ ���� � ������ ������, � ������ ����� �� � �����.
	SetPlayerInteriorEx(playerid, 15);
	SetPlayerPosEx(playerid, -1443.5195,935.5099,1036.5830, 0.0);
	SetPlayerVirtualWorldEx(playerid, 15);
	PlayerInfo[playerid][pLocal] = 212;

   	new vehicleid = 0;	new seat;
   	//������� ���� ����������� �� ������������ ������
	for(new v=0; v<sizeof(DerbyCar); v++)//sizeof(DerbyCar)
	{
	    //if(GetVehicleModel(DerbyCar[v]) < 400) continue;
	    //if(VehInfo[DerbyCar[v]][cModel] < 400) continue;
	    if(!IsValidVehicle(DerbyCar[v])) continue;
	    if(GetSeatVehiclePlayer(DerbyCar[v], 0) == INVALID_PLAYER_ID)
	    {   //���� ����� 0 - ��������
			vehicleid = DerbyCar[v];
			seat = 0;
   			//goto PutPlayer;//����� �� �������� � ��������� ����
   			break;
	    }
	}
	if(vehicleid == 0)
	{
		DisablePlayerRaceCheckpoint(playerid);

		SetPlayerVirtualWorldEx(playerid, 0);
	    SetPlayerInteriorEx(playerid, 0);
		PlayerInfo[playerid][pLocal] = FREEROAM;
		SetPlayerPosEx(playerid, -2119.5925,-443.8909,35.5313, 90.0);
		//ResetPlayerWeaponsEx(playerid);

		DerbyScore[playerid] = 0;
		PlayerInfo[playerid][pCarTime] = 0;
		gInDerbyBloodBowl[playerid] = 0;//�������� ���� - ����� �� � �����
       	SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ����������� � ����� ��� ����� ������!");
		return 1;
	}
	//----------------------------------------------------------------------
//PutPlayer:
	PutPlayerInVehicleEx(playerid, vehicleid, seat);

	gInDerbyBloodBowl[playerid] = 1;
	TotalDerby ++;
	PlayerInfo[playerid][pCarTime] = 30;//������ ���������� ���,
	//�.�. ����� ����� ����� ������ ��� �� ������ ������ ������ ��. � ������ ������� ��� �� �������� � �������� ����������� �����
	DerbyScore[playerid] = 0;

	new dlgitem[48+88+89+84+95+49];
	strcat(dlgitem, "\t\t\t\t\tWelcome to {FF0000}Blood Bowl{FFFFFF}");
	strcat(dlgitem, "\n\n� ������ ���������� � ���� ���� 30 ������, ������� ����� ������ ������ �����������.");
	strcat(dlgitem, "\n������� ����� ����������� �����, ����� ��������� ��� ����� (+8 ���. �� ������ ������).");
	strcat(dlgitem, "\n��� ������ � ���������� {FF0000}'�������� ����'{FFFFFF} ������ 1 ���. �� �������.");
	strcat(dlgitem, "\n������� ����������� ����� � ����� �� ��������! ���� ����� �� ������� �������, �� ����������.");
	strcat(dlgitem, "\n�������� ������� �����, ����� �������� ������!");
	//strcat(dlgitem, "\n��� ������� ����� �������� �� ������� HelpTime �� ������.�����!");
	MenuOperation[playerid] = 130;
	ShowPlayerDialogEx(playerid, BLOODBOWL_DIALOG, DIALOG_STYLE_MSGBOX, "������� �����:", dlgitem, "OK", "");
	//GameTextForPlayerEx(playerid, "~w~Welcome to the ~n~~r~Blood Bowl", 2000, 1);
	return 1;
}

stock bloodbowl_OnPlayerStateChange(playerid, newstate)
{
	if(newstate == PLAYER_STATE_ONFOOT)//���� ID ������ ��������� ����� ��������� �� �����
	{   //���� ID ������ ��������� ����� ��������� 1

		if(gInDerbyBloodBowl[playerid])//��� ����� BloodBowl STEP7
		{
			SetVehicleToRespawnEx(playerid, nCarID[playerid]);
			DisablePlayerRaceCheckpoint(playerid);

			SetPlayerVirtualWorldEx(playerid, 0);
		    SetPlayerInteriorEx(playerid, 0);
			PlayerInfo[playerid][pLocal] = FREEROAM;
			SetPlayerPosEx(playerid, -2119.5925,-443.8909,35.5313, 90.0);
			//ResetPlayerWeaponsEx(playerid);

			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				if( !gInDerbyBloodBowl[i] ) continue;
			 	//SendClientMessageToAll(COLOR_BRIGHTLYGREEN, strings);
		    	format(strings, sizeof(strings), "BloodBowl: {FFFFFF}%s[%d]{00FF00} ������� ������� ����� � ���-������. �������: ������� ���������", PlayerName(playerid), playerid);
			 	SendClientMessage(i, COLOR_BRIGHTLYGREEN, strings);
			}
			TotalDerby --;
			if(TotalDerby <= 0)
			{
				//KillTimer(updatederbytimer); updatederbytimer = -1;
				gDerbyStarted = 0;//�������� ���� - ����� �����������
				TotalDerby = 0;//�������� ����� ���-�� �������� 0
				//SendClientMessageToAll(COLOR_BRIGHTLYGREEN, "����� BloodBowl �������. ��������� ������� ������������ �����.");
				SendAllAdminMessage(COLOR_BRIGHTLYGREEN, "����� BloodBowl �������. ��������� ������� ������������ �����.", 1);
			}

			DerbyScore[playerid] = 0;
			PlayerInfo[playerid][pCarTime] = 0;
			gInDerbyBloodBowl[playerid] = 0;//�������� ���� - ����� �� � �����

			gTextDrawHideCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
			//SendClientMessage(playerid, COLOR_BRIGHTLYGREEN, "�� ����� �� ���������� � �������� ������� ����� BloodBowl.");
		}
	}
}

stock bloodbowl_OnPlayerDisconnect(playerid)
{
	if(gInDerbyBloodBowl[playerid])//��� ����� BloodBowl STEP9
	{   //���� ����� � ����� ����� �� ����
		if(GameRestart != 1)
		{
			SetVehicleToRespawnEx(playerid, nCarID[playerid]);

			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				if( !gInDerbyBloodBowl[i] ) continue;
			 	//SendClientMessageToAll(COLOR_BRIGHTLYGREEN, strings);
		    	format(strings, sizeof(strings), "BloodBowl: {FFFFFF}%s[%d]{00FF00} ������� ������� ����� � ���-������. �������: ����� �� ����", PlayerName(playerid), playerid);
			 	SendClientMessage(i, COLOR_BRIGHTLYGREEN, strings);
			}
			TotalDerby --;
			PlayerInfo[playerid][pCarTime] = 0;
			gInDerbyBloodBowl[playerid] = 0;//�������� ���� - ����� �� � �����
			if(TotalDerby <= 0)
			{
				//KillTimer(updatederbytimer); updatederbytimer = -1;
				gDerbyStarted = 0;//�������� ���� - ����� �����������
				TotalDerby = 0;//�������� ����� ���-�� �������� 0
				//SendClientMessageToAll(COLOR_BRIGHTLYGREEN, "����� BloodBowl �������. ��������� ����� �� ����.");
				SendAllAdminMessage(COLOR_BRIGHTLYGREEN, "����� BloodBowl �������. ��������� ����� �� ����.", 1);
			}
		}

	}
}

stock bloodbowl_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
		#pragma unused listitem
		#pragma unused inputtext

//��� ����� 8ball
		if(dialogid != BLOODBOWL_DIALOG) return 1;
//ShowPlayerDialogEx(playerid, BLOODBOWL_DIALOG, DIALOG_STYLE_MSGBOX, "������� �����:", dlgitem, "C����", "�����");
//ShowPlayerDialogEx(playerid, BLOODBOWL_DIALOG, DIALOG_STYLE_MSGBOX, "������� �����:", dlgitem, "OK", "");
		if(response)
		{
			if(MenuOperation[playerid] == 130)//��� ����� BloodBowl STEP2
			{
				gTextDrawShowCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
				new strTime[80+6+5+2+2];
				format(strTime, sizeof(strTime), "~p~Time   ~w~%s~n~~p~Money   ~g~$%d~n~~p~Members   ~w~%d~n~~p~CountDown   ~w~%d",
					TimeConverter(PlayerInfo[playerid][pCarTime]), DerbyScore[playerid], TotalDerby, derbycountdown);
				PlayerTextDrawSetStringEx(playerid, txdCarTime[playerid], strTime);

				for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
					if( !gInDerbyBloodBowl[i] ) continue;
			    	format(strings, sizeof(strings), "BloodBowl: {FFFFFF}%s[%d]{00FF00} ������������� � ����� � ���-������", PlayerName(playerid), playerid);
				 	SendClientMessage(i, COLOR_BRIGHTLYGREEN, strings);
				}

		 		if(TotalDerby == 1)//gDerbyStarted == 0 &&//���� ����� ��� �� ��������, �.�. ����� ��� ������ ������������� � �����
				{//���� �� ������ � �����
		  			derbycountdown = 21;
					TogglePlayerControllableEx(playerid, 0);//�������������
					SetPlayerRaceCheckpoint(playerid, 2, -1394.1741,997.8110,1023.8897, -1394.1741,997.8110,1023.8897, 12.0);
					PlaySoundForPlayer(playerid, SOUND_CHECKPOINT_AMBER);

					DestroyPickupEx(PickupID[MAX_PLAYER_PICKUPS]);
					new rand = random(sizeof(RepairPickups));
					PickupID[MAX_PLAYER_PICKUPS] = SetPickupEx(RepairPickups[rand][dp_model], RepairPickups[rand][dp_type], RepairPickups[rand][dp_x],RepairPickups[rand][dp_y],RepairPickups[rand][dp_z],15);

					gCountdownDerbyTimer = SetTimer("BloodBowlCountdownTimer", 1000, 1);//��������� ������ �������
				}
				else
				{//���� �� ��������������� � ��� ������������ �����
					SetPlayerRaceCheckpoint(playerid, 2,
						DerbyCheckpoints[DerbiRand][0],DerbyCheckpoints[DerbiRand][1],DerbyCheckpoints[DerbiRand][2],
						DerbyCheckpoints[DerbiRand][0],DerbyCheckpoints[DerbiRand][1],DerbyCheckpoints[DerbiRand][2],
						6.0);
					PlaySoundForPlayer(playerid, SOUND_CHECKPOINT_AMBER);
				}
			}
		}
		else//����� �� 8ball trak
		{

		}
		return 1;
}

stock bloodbowl_OnPlayerExitVehicle(playerid)
{
 	if(gInDerbyBloodBowl[playerid])//��� ����� BloodBowl STEP8
	{
		SetVehicleToRespawnEx(playerid, nCarID[playerid]);
	}
}

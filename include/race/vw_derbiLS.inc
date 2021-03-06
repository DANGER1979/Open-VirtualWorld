new MinSpeed[MAX_PLAYERS] = 0;//����������� �������� �� ����� !

//��� ����� 8ball
new debrycar[MAX_PLAYERS] = 0;
new DebryIndex[MAX_PLAYERS] = 0;//�������� �� ��� ��� �����. �������� � �����
new MinSpeedIndicator[MAX_PLAYERS] = 0;

new helptime[MAX_PLAYERS] = 10;
new DerbylCar8ball[8];//������ ����������� �����
new DerbyCarCounter = 0;//������� ����������� ����� ��� ����� � ����� ��� � ��

//==============================================================================
//��� ����� 8ball ������


//��� ����� 8ball
stock derbiLS_OnPlayerConnect(playerid)
{
	MinSpeed[playerid] = 0;//�������� min speed
    gInDerby8ball[playerid] = 0;//����������� ������ �� �����
    helptime[playerid] = 10;//��������������� ��������������� �����

}
stock derbiLS_OnPlayerDisconnect(playerid)
{
	if(gInDerby8ball[playerid])//��� ����� 8ball
	{
		EndDerbiLS(playerid);
	}
}
stock derbiLS_OnPlayerStateChange(playerid, oldstate)
{
	if(oldstate == PLAYER_STATE_DRIVER)//�� ������ ����� ������ �� ������ ��� ��������� PLAYER_STATE_ONFOOT
	{   //���� ����� ��� �� ���� � ������ � ������� ��� ��������
		if(gInDerby8ball[playerid])//��� ����� 8ball
		{
			EndDerbiLS(playerid);
        }
	}
}

stock derbiLS_OnPlayerPickUp(playerid)
{
	if( IsPlayerInRangeOfPoint(playerid, 2.2, 2695.6235,-1704.6960,11.8438) ||
		IsPlayerInRangeOfPoint(playerid, 2.2, 2729.6138,-1828.2534,12.0438) )
	{   //���� 8ball Track
		if(PlayerInfo[playerid][pCarTime] > 0)
		{
			GameTextForPlayerEx(playerid, "~r~Closed", 5000, 1);
			return 1;
		}
        /*if(PlayerInfo[playerid][pCarLic] == 0)//����� (�������� �� ��������)
		{
        	SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ����������� � ����� ��� ��������!");
            return 1;
		}*/
		if(GetPlayerMoneyH(playerid) < 0)
		{
        	SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ����������� � ����� c ��������� ��������!");
            return 1;
		}
        /*if(PlayerInfo[playerid][pCarLic] == 0)//����� (�������� �� ��������)
		{
        	SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ����������� � ����� ��� ��������!");
        	//SetPlayerFacingAngle(playerid, 90.0);
		    //SetPlayerPosEx(playerid, 2693.1243, -1700.4734, 10.5309);
            return 1;
		}*/
	    GameTextForPlayerEx(playerid, "~w~Welcome to the ~n~~y~8ball Track LS", 5000, 1);
		SetPlayerInteriorEx(playerid, 7);
		SetPlayerPosEx(playerid, -1403.8553,-256.3585,1043.6501, 0.0);
		SetPlayerVirtualWorldEx(playerid, 7);
		PlayerInfo[playerid][pLocal] = 211;
		StartDerbiLS(playerid);
	}
	return 1;
}



stock EndDerbiLS(playerid)//��� ����� 8ball
{
	PlayerInfo[playerid][pParam2] = 0; gParameter2[playerid] = 0;
	SetPlayerShowScale(playerid, 2, PlayerInfo[playerid][pParam2], 50);

	DisablePlayerRaceCheckpoint(playerid);//��������� ��������� ��������
	if(DerbyCarCounter > 0)
	{
		DerbyCarCounter --;
	   	VehInfo[debrycar[playerid]][cType] = 0;
	   	VehInfo[debrycar[playerid]][cDist] = 0;
	   	DestroyVehicleEx(debrycar[playerid], 2);//������� ����
	}
	else
	{
		//SendClientMessage(playerid, COLOR_GREY, "   ��� ��������� ������ ���������� !");
		ABroadCast(COLOR_MAROON, "   ��� ��������� ������ ���������� !", 9);
	}
	//��������� ���������
	SetPVarInt(playerid, "PlayerProgressCount", 0);//������� ����� �� �����
	MinSpeed[playerid] = 0;//�������� min speed
	gInDerby8ball[playerid] = 0;//����������� ������ �� �����
	helptime[playerid] = 10;//��������������� ��������������� �����
	//����� �� 8ball Track LS int7

	SetPlayerVirtualWorldEx(playerid, 0);
	SetPlayerInteriorEx(playerid, 0);
	PlayerInfo[playerid][pLocal] = FREEROAM;
	//SetPlayerPosEx(playerid, 2693.1243,-1700.4734,10.5309, 90.0);
	SetPlayerPosEx(playerid, 2728.0933,-1834.9763,10.3494, 180.0);

	gTextDrawHideCarTime[playerid] = true;
	gTextDrawShowSpeed[playerid] = true;
	OnPlayerTextDrawStateChange(playerid);

	PlaySoundForPlayer(playerid, SOUND_RACE_321);
}

//stock DerbiLSTimer(playerid)//��� ����� BloodBowl //��� ����� 8ball
stock derbiLS_OneSecondTimers(playerid)
{   //���������� �� ���������� ������� OnPlayerCallTime
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;
	if(!gInDerby8ball[playerid]) return 1;//��� ����� 8ball STEP4

	CrashDetected[playerid] = 19;
//��� ��������� minspeed ������ 3 �������
	if(MinSpeedIndicator[playerid] < 3) MinSpeedIndicator[playerid] ++;
	else { MinSpeedIndicator[playerid] = 0; MinSpeed[playerid] ++; }

	new velocity = GetVehicleSpeed(nCarID[playerid]);
	//�������� �� ����������� �������� !
	if(velocity < MinSpeed[playerid])
	{
		helptime[playerid] --;
	}

//������ �� ����
	GetVehicleHealth(debrycar[playerid], VehHealth[debrycar[playerid]]);
	//���� ����� �� � ����. ����������� �����.���� ����� �� ���������� � �����!
	if( GetPlayerState(playerid) != PLAYER_STATE_DRIVER ||
		helptime[playerid] == 0 ||
		VehHealth[debrycar[playerid]] <= 250.0)
	{
		EndDerbiLS(playerid);
	}

	new strtmp[100];
	if(helptime[playerid] > 6)
	{
		format(strtmp, sizeof(strtmp),
		"~g~MinSpeed:~w~ %d~n~~g~HelpTime: ~w~%d~n~~g~CP: ~w~%d ~y~/17",
		MinSpeed[playerid],helptime[playerid],GetPVarInt(playerid, "PlayerProgressCount"));
	}
	else if(helptime[playerid] >= 4 && helptime[playerid] <= 6)
	{
		format(strtmp, sizeof(strtmp),
		"~g~MinSpeed:~w~ %d~n~~g~HelpTime: ~y~%d~n~~g~CP: ~w~%d ~y~/17",
		MinSpeed[playerid],helptime[playerid],GetPVarInt(playerid, "PlayerProgressCount"));
	}
	else //if(helptime[playerid] < 4)
	{
		format(strtmp, sizeof(strtmp),
		"~g~MinSpeed:~w~ %d~n~~g~HelpTime: ~r~%d~n~~g~CP: ~w~%d ~y~/17",
		MinSpeed[playerid],helptime[playerid],GetPVarInt(playerid, "PlayerProgressCount"));
	}
	PlayerTextDrawSetStringEx(playerid, txdCarTime[playerid], strtmp);
	return 1;
}


stock derbiLS_EnterRaceCheckpoint(playerid)//��� ����� 8ball STEP3
{   //���������� �� OnPlayerEnterRaceCheckpoint
	if(gInDerby8ball[playerid] != 1) return 1;
	if(GetPVarInt(playerid, "PlayerProgressCount") > 15)
	{
		//######################################################################
		//
		//    � �� �������� ������� �� ����� (� �� ���� ����� ���� �����
		// ������������ ����� ���������) �� ��������� ����� ��� ����� ����� ����
		// � ����� ������ ������ ����� �������� �� �������:
		// new money = HealtchCar * helptime[playerid] + random(15);
		// ������������ ����� �������� 1014$ (��� 100hp * 10� + 14)
		// ����������� ����� �������� 26$ (��� 26hp * 1� + 0)
		//
		//######################################################################
		if(VehHealth[debrycar[playerid]] <= 1000.0)
		{
			new per = floatround(VehHealth[debrycar[playerid]])/100;//1000/100=10
			new money = 200 + (per + helptime[playerid])*per + random(201);
		// ������������ ����� �������� ��� 200 + (10+10)*10 + 200 = 600
		// ����������� ����� �������� ��� 200 + (2.6+1)*2.6 + 0 = 210
			GivePlayerMoneyB(f8ball, playerid, money);

			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "������� � ����� 8ball {FFFFFF}%s[%d]{FF9900}. ����� �������� ��������� {33AA33}$%d", PlayerName(playerid), playerid, money);//���������������
			SendClientMessageToAll(COLOR_LIGHTORANGE, strings);
		}
		EndDerbiLS(playerid);
        GameTextForPlayerEx(playerid, "~r~Mission ~g~Complite", 1500, 1);
        return 1;
	}
	if(GetPVarInt(playerid, "PlayerProgressCount") == 15)//23(��� 12 ������) 15(��� 8 ������)
	{
        SetPlayerRaceCheckpoint(playerid, 1, -1398.99,-200.72,1043.0, -1398.99,-200.72,1043.0, 10);
        DebryIndex[playerid] = 0;
	}
	//--------------------------------------------------------------------------
	if(DebryIndex[playerid] == 1)
	{
        SetPlayerRaceCheckpoint(playerid, 0, -1263.34,-208.10,1050.65, -1529.32,-200.19,1050.69, 10);
        DebryIndex[playerid] = 2;
    }
    else if(DebryIndex[playerid] == 2)
	{
        SetPlayerRaceCheckpoint(playerid, 0, -1529.32,-200.19,1050.69, -1263.34,-208.10,1050.65, 10);
        DebryIndex[playerid] = 1;
    }
	PlaySoundForPlayer(playerid, SOUND_RACE_321);
	GivePVarInt(playerid, "PlayerProgressCount", +1);
    return 1;
}

//��� ����� 8ball �����


stock StartDerbiLS(playerid)//��� ����� 8ball STEP1
{   //���������� �� OnPlayerPickUpPickup
	//new strings[MAX_STRING];
	if(DerbyCarCounter < sizeof(DerbylCar8ball))//8
	{
		new modelid;
		if(DerbyCarCounter == 0 || DerbyCarCounter == 4) { modelid = 494; debrycar[playerid] = CreateVehicleEx(modelid, -1408.538, -257.894, 1043.557, 347.873,random(15),random(15), (CARSPAWN*60)); }
		else if(DerbyCarCounter == 1 || DerbyCarCounter == 5) { modelid = 502; debrycar[playerid] = CreateVehicleEx(modelid, -1407.328, -257.4488, 1043.4770, 349.95,random(15),random(15), (CARSPAWN*60)); }
		else if(DerbyCarCounter == 2 || DerbyCarCounter == 6) { modelid = 503; debrycar[playerid] = CreateVehicleEx(modelid, -1404.163, -254.950, 1043.52, 350.85,random(15),random(15), (CARSPAWN*60)); }
		else if(DerbyCarCounter == 3 || DerbyCarCounter == 7) { modelid = 502; debrycar[playerid] = CreateVehicleEx(modelid, -1400.754, -257.394, 1043.534, 351.96,random(15),random(15), (CARSPAWN*60)); }
		if(debrycar[playerid] > GetMaxVehicles) GetMaxVehicles = debrycar[playerid];

		VehInfo[debrycar[playerid]][cType] = 950 + DerbyCarCounter;
		LinkVehicleToInterior(debrycar[playerid], 7);
		SetVehicleVirtualWorldEx(debrycar[playerid], PlayerInfo[playerid][pVirtual]);

		//DerbylCar8ball[DerbyCarCounter] = debrycar[playerid];//AdminCars[1] = 343,AdminCars[2] = 344
		SetVehicleParams(debrycar[playerid],//playerid,
			VEHICLE_PARAMS_ON,VEHICLE_PARAMS_ON,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF);

		for(new car = 0; car<sizeof(DerbylCar8ball); car++)
		{	//���� ��������� ������
		    if(DerbylCar8ball[car] != 0) continue;
			DerbylCar8ball[car] = debrycar[playerid];
			break;
		}
		DerbyCarCounter ++;

		PutPlayerInVehicleEx(playerid, debrycar[playerid], 0);

		new dlgitem[33+76+92+107+71+84+67];
  		strcat(dlgitem, "\t\t\t\t\tWelcome to 8ball Track");
		strcat(dlgitem, "\n\n� ������ ����� ��� ����� 10 ������ ���������������� �������(HelpTime),");
		strcat(dlgitem, "\n������� ���������� ��� �������������� �������� � ������, ���� ���� �������� ���� MinSpeed.");
		strcat(dlgitem, "\nMinSpeed - ��� ����������� �������� �� �����. ��� ��������� �����. ��� �������� ���������� ������������.");
		strcat(dlgitem, "\n� ������, ���� HelpTime ��������� �� ����, �� ����� ��� ��� ��������.");
		strcat(dlgitem, "\n��� ������ ��� ���������� �������� 8 ������(16 ���������� � + �������� ��������).");
		strcat(dlgitem, "\n��� ������� ����� �������� �� ������� HelpTime �� ������. �����!");
		MenuOperation[playerid] = 129;
		ShowPlayerDialogEx(playerid, DERBILS_DIALOG,DIALOG_STYLE_MSGBOX, "������� �����:",dlgitem, "C����", "�����");//��� ����� 8ball STEP2
	}
	else
	{
		format(strings, sizeof(strings), "Error7: Vehicle not Spawned. DerbyCarCounter=%d >= %d", DerbyCarCounter, sizeof(DerbylCar8ball));
		Log(ERROR, strings);
		EndDerbiLS(playerid);
	}
}

stock derbiLS_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
		#pragma unused listitem
		#pragma unused inputtext

//��� ����� 8ball
		if(dialogid != DERBILS_DIALOG) return 1;
//ShowPlayerDialogEx(playerid, DERBILS_DIALOG, DIALOG_STYLE_MSGBOX, "������� �����:", dlgitem, "C����", "�����");
//ShowPlayerDialogEx(playerid, DERBILS_DIALOG, DIALOG_STYLE_MSGBOX, "������� �����:", dlgitem, "OK", "");
		if(response)
		{
			SetPVarInt(playerid, "gShowDialog", -1);
			if(MenuOperation[playerid] == 129)//��� ����� 8ball STEP2
			{
				SetPlayerRaceCheckpoint(playerid, 0, -1529.32,-200.19,1050.69, -1263.34,-208.10,1050.65, 10);
	            DebryIndex[playerid] = 1;//������ ������ �� 1 ��������
	            gInDerby8ball[playerid] = 1;
	            PlaySoundForPlayer(playerid, SOUND_RACE_GO);//������ �� ����� !
	            SetPVarInt(playerid, "PlayerProgressCount", 0);//�������� ��������� !
	            MinSpeed[playerid] = 0;//�������� min speed
	            helptime[playerid] = 10;//��������������� ��������������� �����
	            //PlayerInfo[playerid][pCarTime]
				gTextDrawShowCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
			}
		}
		else//����� �� 8ball trak
		{
			SetPVarInt(playerid, "gShowDialog", -1);
			if(MenuOperation[playerid] == 129)
			{
				EndDerbiLS(playerid);
			}
		}
		return 1;
}


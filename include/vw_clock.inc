stock TogglePlayerClockEx(playerid, toggle)
{
    if(toggle == 1)
    {//���� ������ ������ �� ���������
//if(gTextDrawShowClock[playerid] == true && TextDrawShowClock[playerid] == false)
//{//���� ���� ���������� �� ����� � ��������� �� �������
		SetPVarInt(playerid, "gPlayerClock", 1);//��� DeveloperMenu, ����� ������ ����
		gTextDrawShowClock[playerid] = true;//���������� ����� ����� ��������� ���������
		OnPlayerTextDrawStateChange(playerid);
		//return
		TogglePlayerClock(playerid, 0);//false - ��������� //��������� ������� ���� �� ������
		SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, "������ ��������");
	}
    else
    {
		SetPVarInt(playerid, "gPlayerClock", 0);
		gTextDrawHideClock[playerid] = true;//������ �� ����������
		OnPlayerTextDrawStateChange(playerid);
		//return
		TogglePlayerClock(playerid, 1);//true - �������� ������� ����
		SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, "������ ���������");
    }
}

stock clock_OnGameModeInit()
{//��� ������ ��������� ������� ����
	new lH, lM, lS;	gettime(lH,lM,lS);//FixHour(lH);
	SetWorldTime(lH);
	/*for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnectedEx(i))
		{
	        SetPlayerTime(i, lH, lM);
			TogglePlayerClockEx(i, 0);
		}
	}*/
/*
		new hour = strval(tmp);

		new lH, lM, lS;	gettime(lH,lM,lS);
		////FixHour(hour);
		SetWorldTime(hour);
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
		    if(IsPlayerConnectedEx(i))
			{
		        SetPlayerTime(i, hour, lM);
			}
		}
		format(strcmd, sizeof(strcmd), "   B���� ���� ����������� �� %d �����.", hour);
		SendClientMessageToAll(COLOR_RED, strcmd);
*/
}

stock clock_OnPlayerSpawn(playerid)
{
	//��� �����
    //SetPlayerTime(playerid, worldTime,minuteT);
    //TogglePlayerClock(playerid, 0);//��������� ������� ���� �� ������
	// if they ever return to class selection make them spawn select again first
	//if(TextDrawShowClock[playerid] == true)
	//{
	new lH, lM, lS;	gettime(lH,lM,lS);//FixHour(hour);
	//SetWorldTime(lH);���������� ��� ������� �������
    SetPlayerTime(playerid, lH, lM);
    TogglePlayerClockEx(playerid, 1);
    //}
}

new DrunkL[MAX_PLAYERS];
new LDrunkL[MAX_PLAYERS];
new FPS[MAX_PLAYERS];
//forward GetPlayerFPS(playerid);
stock GetPlayerFPS(playerid)
{
    DrunkL[playerid] = GetPlayerDrunkLevel(playerid);
    if(DrunkL[playerid] < 100)
    {
        SetPlayerDrunkLevel(playerid, 2000);
    }
    else
    {
        if(LDrunkL[playerid] != DrunkL[playerid])
        {
            FPS[playerid] = LDrunkL[playerid] - DrunkL[playerid];
            LDrunkL[playerid] = DrunkL[playerid];
            if(FPS[playerid] > 0 && FPS[playerid] < 256)
            {
			    //new strtmp[8+3];
			 	//format(strtmp, sizeof(strtmp), "fps: %d", FPS[playerid]-1);
				//SendClientMessage(playerid, 0xAFAFAFAA, strtmp);
                return FPS[playerid]-1;
            }
        }
    }
    return 0;
}

new fps[MAX_PLAYERS];
stock clock_OneSecondTimers(playerid)
{
//��� ������� ������
 	if(TextDrawShowClock[playerid] == true)//if(gPlayerClock == 1)//������ ���  GetPVar ������������ 	//if(GetPVarInt(giveplayerid, "gPlayerClock") == 1)
	{
		new timestr[256];
		new lH, lM, lS;		gettime(lH,lM,lS); //FixHour(lH);
		new ly, lmm, ld;	getdate(ly,lmm,ld);
		/*format(timestr, sizeof(timestr), "%02d.%02d.%04d", ld,lmm,ly);//������������� �������� ������ � �����
		TextDrawSetStringEx(txdDate,timestr);//�������� � TextDraw Clock2
		
		format(timestr, sizeof(timestr), "%02d:%02d", lH,lM);//:%02d , Sec
		TextDrawSetStringEx(txdTimeDisp, timestr);//�������� � ��������� ������� �������� �������

		format(timestr, sizeof(timestr), "%02d", lS);//������������� �������� ������ � �����
		TextDrawSetStringEx(txdSecondsTime, timestr);//�������� � TextDraw Clock2*/

		new tmp = GetPlayerFPS(playerid); if(tmp != 0) fps[playerid] = tmp;
		format(timestr, sizeof(timestr), "online: %d(%d) %02d fps ping: %02d ms",
			numplayers, OnlineRecord, fps[playerid], GetPlayerPing(playerid));
		PlayerTextDrawSetStringEx(playerid, txdSecondsTime[playerid], timestr);
		
		//format(timestr, sizeof(timestr), "%s~n~%02d %s %04d", GetFullWeekDay(ld,lmm,ly), ld,GetMonth(lmm),ly);
		format(timestr, sizeof(timestr), "%s~n~%02d %s %04d", GetFullWeekDay(ld,lmm,ly), ld,GetMonth(lmm),ly);
		TextDrawSetStringEx(txdDate, timestr);//�������� � TextDraw Clock2

		format(timestr, sizeof(timestr), "%02d:%02d", lH,lM);//
		TextDrawSetStringEx(txdTimeDisp, timestr);
	}
	/*else// if(gPlayerClock == 0)
	{
		TextDrawSetStringEx(txdTimeDisp, " ");
		TextDrawSetStringEx(txdSecondsTime, " ");
		TextDrawSetStringEx(txdDate, " ");
	}*/
//��� ������� �����
}

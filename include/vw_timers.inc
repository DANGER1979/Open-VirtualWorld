//#include <a_samp>
//##############################################################################//
//                                                                              //
//                          �������������� ��������                             //
//                                                                              //
//##############################################################################//
//new starttimer;
//new gStartCountdown;
//new gCountdownCSTimer;
//new gUpdatecstimer;

//new gOffsettimer = -1;

/*
new onesecondtimers;
new onesecondtimers2;
new onesecondtimers3;
new onesecondtimers4;
new oneminutstimer;
new fiveminutstimers;
new fifteenminutstimers;

new carupgradetimer;
new loadcarupgradetimer;
*/


//##############################################################################//
//                                                                              //
//                                 �ר�����                                     //
//                                                                              //
//##############################################################################//
new checktimedamage[MAX_PLAYERS];//������� ��� �������������� ��������� ��� ������

enum SavePosEnum// ���������� ������� //��� PlayerIdleKick15Timer //��� ��������
{
    Float:LastX,
    Float:LastY,
    Float:LastZ
};
new SavePos[MAX_PLAYERS][SavePosEnum];//���������������� ������ 15 �����
//##############################################################################//
//#                                                                            #//
//#                           ����������� �������  (1)                         #//
//#                                                                            #//
//##############################################################################//

/*

forward OneMinutsTimer();
public OneMinutsTimer()
{
	new timers = GetTickCount();
	//--------------------------------------------------------------------------
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		//if( !IsPlayerConnected(i) ) continue;
		if( IsPlayerNPC(i) ) continue;
  	    //if( !gPlayerLogged[i] ) continue;
	    //if( !gPlayerSpawned[i] ) continue;



	}
	//--------------------------------------------------------------------------
	TestLog(OPTIM, "OneMinutsTimer", GetTickCount(), timers);
}

forward OnFiveMinutsTimer();
public OnFiveMinutsTimer()
{
	new timers = GetTickCount();
	//--------------------------------------------------------------------------
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		//if( !IsPlayerConnected(i) ) continue;
		if( IsPlayerNPC(i) ) continue;
  	    //if( !gPlayerLogged[i] ) continue;
	    //if( !gPlayerSpawned[i] ) continue;
	    
#if defined vw_speedometer
		roadblock_OnFiveMinutsTimer(i);
#endif

	}
	//--------------------------------------------------------------------------
	TestLog(OPTIM, "OnFiveMinutsTimer", GetTickCount(), timers);
}

*/

//stock PlayerIdleKick15Timer(playerid)
stock timers_FifteenMinutsTimer(playerid)
{//���������� �� OnFifteenMinutsTimer()
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	if( PlayerInfo[playerid][pAdmin] >= 6 || PlayerInfo[playerid][pAccount] == 365) return 1;
	//if( TutTimeCounter[playerid] > 0) continue;
    if( IsInNPCVehicle( nCarID[playerid] ) )
    {
		if(GetPVarInt(playerid, "gIdleKick") == 1)
		{   //���� ����� �� ������������
			//new strings[MAX_STRING];
			if(PlayerInfo[playerid][pAdmin] < 9 && PlayerInfo[playerid][pAccount] == 0)
			{
				format(strings, sizeof(strings), "%s[%d] kicked, reason: enter NPC Vehicle > %d minutes", PlayerName(playerid),playerid,idletime);
				SendSystemMessage(COLOR_MAROON, strings, 1);
				Log(KICK,strings);
				SetPVarInt(playerid, "gIdleKick", 0);
				IsKicked[playerid] = 1;
				return 1;
			}
		}
		SetPVarInt(playerid, "gIdleKick", 1);//������� ���� - ����� �������� � �����
	}
   	if(lH > 8)
   	{   //�� ������ ����
		if( PlayerInfo[playerid][pMember] == DoD || PlayerInfo[playerid][pJailed] == 10)
    	{//���� � ����� ����������� �� ����
			if(IsPlayerInArea(playerid, specialzone[0])) return 1;
		}
		else if(PlayerInfo[playerid][pMember] == DoH)
		{//������� � ���������
			if( IsAtHospital(playerid) ) return 1;
		}
		else if(PlayerInfo[playerid][pMember] == DoJ)
		{//������ ������������� � �����
			//if(IsPlayerInArea(playerid, specialzone[7])) continue;
			if(PlayerInfo[playerid][pLocal] == 241) return 1;
		}
		else if(PlayerInfo[playerid][pMember] == DoE)
		{	//������������ � ��
       		if( IsPlayerInRangeOfPoint(playerid, 100.0, -2032.6810,-117.4816,1035.1719) ) return 1;
		}
		else if(PlayerInfo[playerid][pJob] == CARDEALER)
		{//����������� � ��
			if(IsPlayerInArea(playerid, specialzone[8])) return 1;
		}
	}
	if(IsPlayerInRangeOfPoint(playerid, 5.0, SavePos[playerid][LastX], SavePos[playerid][LastY], SavePos[playerid][LastZ]))
	{   //���� ����� �� ������������
		//new strings[MAX_STRING];
		if(gLoading[playerid]) return 1;
		if(gUnLoading[playerid]) return 1;
		if(PlayerInfo[playerid][pAdmin] < 9 && PlayerInfo[playerid][pAccount] == 0)
		{
			format(strings, sizeof(strings), "%s[%d] kicked, reason: idle one place > %d min", PlayerName(playerid),playerid, idletime);
			SendSystemMessage(COLOR_MAROON, strings, 1);
			Log(KICK, strings);
			IsKicked[playerid] = 1;
			return 1;
		}
	}
	GetPlayerPos(playerid, SavePos[playerid][LastX], SavePos[playerid][LastY], SavePos[playerid][LastZ]);
	return 1;
}

//���������� ������� � ������ � ������ �������
stock OneHourTimer()//���������� ������ ��� �� SyncTime(), ����������� ������ ������
{
	new timers = GetTickCount();

	//Election();
	//if(switcher == 0) {	Election();	switcher = 1; }
	//else { Election_OneDayTimer(); switcher = 0; }
	//--------------------------------------------------------------------------
//���� �������� ����
	new tmpday;// = getdate();
	getdate(_,_,tmpday);
	if(	(tmpday > LastDay)//���� ������� ���� ������ ��� ����������
		|| (tmpday == 1 && (LastDay == 28 || LastDay == 29 || LastDay == 30 || LastDay == 31))//��� ������� ���� ����� 1 � ���������� ����� 30 ��� 31
	  )//� ���������� ���������� ������� �� ����� ���������
	{
		//Election_OneDayTimer();
		LastDay = tmpday;//�������� ���������� ��������
	}
	//--------------------------------------------------------------------------
  	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i)) continue;
		if( !gPlayerSpawned[i] ) continue;
		if( AFK_IdleTime[i] >= 3 &&//���� � ��� ���������� � �� ��������� ��, �����
			(PlayerInfo[i][pAdmin] != 9 && PlayerInfo[i][pAccount] != 365)) continue;
		if(PlayerInfo[i][pLevel] <= 3)
		{
			SendClientMessage(i, COLOR_YELLOW, "����������� ��������� �������� �� ������� �������� /tutorial");
			SendClientMessage(i, COLOR_GREEN, "���������� ��� ��������� ������� � ������ ������ ����� ��� ������ ������� /help ��� ������� H");
			//SendClientMessage(i, COLOR_GREEN, "������� ������ ����� �������� /changepass.");
			//SendClientMessage(i, COLOR_GREEN, "����������� �������� ��� ����� "#FORUM" �� ��� �� ������� ��� ����������� ����������!");

			/*new weburl[64];
			GetServerVarAsString("weburl", weburl, sizeof(weburl));
			format(strings, sizeof(strings), "�� ����� %s (�� ������� �����) ����� ��������� ����,", weburl);
			SendClientMessage(i, COLOR_GREEN, strings);
			SendClientMessage(i, COLOR_GREEN, "����� ������ ������� ������, VIP ������� ��� ����� ����, �������� ������������ (USE: /donat)");
			SendClientMessage(i, COLOR_GREEN, "����� ������ ������������ �������-�������� (USE: /viphelp)");
			SendClientMessage(i, COLOR_GREEN, "������ ������ �� ��������� �������, ������� �������!");*/
		}
	}
	TestLog(OPTIM, "OneHourTimer", GetTickCount(), timers);//new timers = GetTickCount();
}

//##############################################################################//
//#                                                                            #//
//#                    ������� ����������� ��� ������ ������                   #//
//#                                                                            #//
//##############################################################################//


stock timers_OnGameModeInit()
{
//������� 16 - 6%
	//gStartCountdown = 1;
	//starttimer = SetTimer("StartTimers", 300, 1);
	SetTimer("tLoadCarUpgrade", 2500, 0);//RespawnAllCars//��� �������� ���� ����������� ������ ����� 2.5 ������
}

forward tLoadCarUpgrade();//��� �������� ���� ������
public tLoadCarUpgrade()//���������� �� ������� GameModeInit
{
	RespawnAllCars();
#if defined vw_fuel
	FuelAllCars();//���������� ���������� ���������� ��������� ������ (��������� ��� �������� ������������������)
#endif
	//SendClientMessageToAll(COLOR_GREEN, "   B�� ��������� ����� �����������! ������� ���� !");
	//KillTimer(loadcarupgradetimer);
	//loadcarupgradetimer = -1;

	//==========================================================================
	//cargoship_OnGameModeInit();
	//airdefence_OnGameModeInit();
 	//==========================================================================
	//new strings[MAX_STRING];
	//format(strings, sizeof(strings), "loadfs vw_pirateisland");
	//SendRconCommand(strings);

	//format(strings, sizeof(strings), "loadfs vw_ferriswheel");
	//SendRconCommand(strings);

	//format(strings, sizeof(strings), "loadfs flymode");
	//SendRconCommand(strings);

}
/*
stock timers_OnGameModeExit()
{
	KillTimer(onesecondtimers);
	KillTimer(oneminutstimer);
	KillTimer(fiveminutstimers);
}

stock timers_OnPlayerConnect(playerid)
{
	//KillTimer(introtimer[playerid]); introtimer[playerid] = -1;

	oneseconds[playerid] = 0;//������� ��� 1-���������� ���������
	twoseconds[playerid] = 0;//������� ��� 2-����������� �������
	threeseconds[playerid] = 0;
	oneminuts[playerid] = 0;
	fiveminuts[playerid] = 0;
	fifteenminuts[playerid] = 0;
	onehour[playerid] = 0;
}
*/

stock RespawnAllCars()
{//���������� �� tLoadCarUpgrade � �� ������� /res
	new unoccupied[MAX_VEHICLES-1];
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
   //���� ������
		if( !IsPlayerConnectedEx(i) ) continue;
       	if(IsPlayerInAnyVehicle(i))	unoccupied[nCarID[i]] = 1;//�������� ����� ������
    }
	//for(new carid = 1; carid<GetMaxVehicles; carid++)//(MAX_VEHICLES-1)
	for(new carid = GetVehiclePoolSize(); carid > 0; carid--)//Gets the highest vehicleid currently in use on the server.
	//GetMaxVehicles ���������������� ��� �������� �����, ���� ����� ������� ������ ��������, �� �������� �� �����
	{
		if(!IsValidVehicle(carid)) continue;//������� �� ������������ ��������.
		//VehicleArray[GetVehicleModel(car)-400][Category] != Trailers)
		//��������: ������� �� ��������� ������������ ����� ����� �� ����� �� ���� ������
		/*if( unoccupied[carid] == 1 || unoccupied[IsVehicleAttachedToTrailer(carid)] == 1)//���������� ���������� ���������� ��������� ������ (��������� ��� �������� ������������������)
	 	{   //������� ����� �� ���������

		}*/
 		if(IsInNPCVehicle(carid) || IsInDerbyCar(carid))
 		{//��� ������ �������� ������ � ����
			//new engine, lights, alarm, doors, bonnet, boot, objective;
			//GetVehicleParams(carid, engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParams(carid, //-1,
				VEHICLE_PARAMS_ON, VEHICLE_PARAMS_ON, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF);
		}
		else if(!unoccupied[carid])
		{   //���� ����� �����
			//if(VehInfo[carid][cType] < 950)
			//{
				gVehicleSpawn[carid] = 1;
				SetVehicleToRespawn(carid);//��������: ����� ����� ��������� ��������� � ���������� �������� �� 1000
				VehInfo[carid][cFuel] = float(VehicleArray[VehInfo[carid][cModel]-400][GasMax]);
				//LastVehHealth[playerid] = 1000;
			/*}
			else
			{
				//gVehicleSpawn[carid] = 1;
				SetVehiclePosEx(carid, VehInfo[carid][cLocX], VehInfo[carid][cLocY], VehInfo[carid][cLocZ]);
		    	SetVehicleZAngleEx(carid, VehInfo[carid][cAng]);
			}*/
		}
	}
}
/*
forward StartTimers();
public StartTimers()//����������� ������ 300 �� ����� ��� ������ ����
{
	if(gStartCountdown == 1)
	{
		onesecondtimers = SetTimer("OneSecondTimers", 1000, 1);
		gStartCountdown = 2;
	}
	else if(gStartCountdown == 2)
	{
		//onesecondtimers2 = SetTimer("OneSecondTimers2", 1000, 1);//��� ���������� ����� � ��� �c���������� �� ����������, ��� ������� //�������� �� ������� �������� //�������� ��������� �����
		gStartCountdown = 3;
	}
	else if(gStartCountdown == 3)
	{
		//onesecondtimers3 = SetTimer("OneSecondTimers3", 1000, 1);
		gStartCountdown = 4;
	}
	else if(gStartCountdown == 4)
	{
		//onesecondtimers4 = SetTimer("OneSecondTimers4", 1000, 1);
		gStartCountdown = 5;
	}
	else if(gStartCountdown == 5)
	{
		oneminutstimer = SetTimer("OneMinutsTimer", 60000, 1);//��������� ������ 60 ������ ������� SyncTime
		gStartCountdown = 6;
	}
	else if(gStartCountdown == 6)
	{
		fiveminutstimers = SetTimer("OnFiveMinutsTimer", 300000, 1);//����������� ������ 5 �����
		gStartCountdown = 7;
	}
	else if(gStartCountdown == 7)
	{
		//fifteenminutstimers = SetTimer("OnFifteenMinutsTimer", 900000, 1);//��������� ������ 150 �����
		gStartCountdown = 0;
		KillTimer(starttimer); starttimer = -1;
	}
}
*/
//##############################################################################//
//                                                                              //
//                    �������������� ���������������� �������                   //
//                                                                              //
//##############################################################################//



stock SyncTime()//���������� ������ ������ �� OneMinutsTimer ��� ������������� �������
{//�������� ������ ����� �����, ������ ����� �� ����� �� ������
	new tmphour;//, tmpminute, tmpsecond;
	//new tmpyear, tmpmonth, tmpday;

	gettime(tmphour, _, _);//�������� ����� �� �����
	//FixHour(tmphour);//��������������� ��� �� �������� timeshift � �������� � shifthour
	//�������� �� ����� ����
	if((tmphour > ghour)//���� ������� ��� ������ ��� ����������
		|| (tmphour == 0 && ghour == 23) &&//��� ������� ��� ����� 0 � ���������� ����� 23
		SynchronizerSaved == 0)//� ���������� ���������� ������� �� ����� ���������
	{
		SynchronizerSaved = 1;//��������� ���������������� ����������
		OneHourTimer();//����������� ��
		ghour = tmphour;//�������� ���������� ��������
		//���� ���� �������� ����� �� �����
		if(gRrealTime == 1)	SetWorldTime(ghour);//���������� ���� ���
	}
}


//##############################################################################//
//                                                                              //
//                               ��������� �������                              //
//                                                                              //
//##############################################################################//











//##############################################################################//
//#                                                                            #//
//#                              ������� �������                               #//
//#                                                                            #//
//##############################################################################//






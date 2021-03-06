/*
 *            VW_FireMan 1.2
 *       (c) Copyright 2009-2013 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (danger1979@mail.ru)
 * @date      : 01.09.2013
 * @update    : 3.10.2013
 *
 * This file is provided as is (no warranties).
 *
 */
/*#if defined _VW_FireMan_included
	#endinput
#endif
#define _VW_FireMan_included
#pragma library VW_FireMan*/

//#include "../include/vw_mapicon"

//addcar 407,-2022.9017,93.2527,28.1273,267.5354,-1,-1
//407,-2022.7889,93.1777,28.3769,267.7189,3,1


#define MAX_FLAMES 100						//100 maxmimal flames
//#define BurnOthers						//������ ������ ����� ������ ����, ���� ��� �������� �������� ������?
#define EarnMoney							// Do you want to earn money for extinguish a fire?
#define FireMessageColor 0x00FF55FF			// color used for the extinguish-message

#define FLAME_ZONE 					1.0     //1.2 ������ � ������� �� ��������� ������ ���� �� ������� ������� � �������
#define ONFOOT_RADIUS				1.0		//1.5 ������ � ������� �� ������ �������� ����� � �����
#define PISSING_WAY					1.0		//2.0 ������ � ������� �� ������ �������� ����� ��������
#define CAR_RADIUS					3.0		//8.0 ������ � ������� �� ������ �������� ����� Firetruck/SWAT Van
#define Z_DIFFERENCE				2.0		//2.5 ������, ������� ����� ��� �������� �������. ���������� �� ���������
#define EXTINGUISH_TIME_VEHICLE		5		//1 ����������� ����� ����� �������� ����� �� firetruck (seconds)
#define EXTINGUISH_TIME_ONFOOT		10		//4 ����������� ����� ����� �������� ����� ������������� (seconds)
#define EXTINGUISH_TIME_PEEING		60		//10 ����������� ����� ����� �������� ����� �������� (seconds)
#define EXTINGUISH_TIME_PLAYER		3		//3 ����������� ����� ����� �������� ������ (seconds)

new Float:PlayerOnFireHP[MAX_PLAYERS];
new PlayerOnFire[MAX_PLAYERS];

new ExtTimer[MAX_PLAYERS];
forward RemoveFireTimer(playerid, flameid);

new PlayerOnFireTimer[MAX_PLAYERS];
forward BurningTimer(playerid);

new PlayerOnFireTimer2[MAX_PLAYERS];
forward StopPlayerBurning(playerid);

enum FlameInfo
{
	Flame_id,//������ �� ������� ����
	Flame_Exists,//-1//��������� �� ���� ��� ����, ��� �����
	Float:Flame_pos[3],//������ ���������� ����
	Smoke[5],//������ �� �������� ����
	Flame_Time
}
new FlameArray[MAX_FLAMES][FlameInfo];

new LastRandFlame;


//##############################################################################//
//                                                                              //
//                                ����� ����������                              //
//                                                                              //
//##############################################################################//

stock fireman_OnPlayerConnect(playerid)
{
	PlayerOnFireHP[playerid] = 100.0;
	PlayerOnFire[playerid] = 0;
	ExtTimer[playerid] = -1;
	PlayerOnFireTimer[playerid] = -1;
	PlayerOnFireTimer2[playerid] = -1;
}

stock fireman_OnPlayerDisconnect(playerid)
{
	KillTimer(PlayerOnFireTimer[playerid]); PlayerOnFireTimer[playerid] = -1;
	KillTimer(PlayerOnFireTimer2[playerid]); PlayerOnFireTimer2[playerid] = -1;
}

stock fireman_OnPlayerDeath(playerid, killerid, reason)
{
	#pragma unused killerid
	if(reason == 37)
	{
		if(PlayerOnFire[playerid] == 1)//��� ���������� ������
		{
			StopPlayerBurning(playerid);
			SendClientMessage(playerid, COLOR_RED, "�� ������� � ����!");
		}//��� ���������� �����
	}
}
stock fireman_OnGameModeInit()
{
	for(new f; f < MAX_FLAMES; f++)
	{
		FlameArray[f][Flame_Exists] = -1;
	}
	print("  vw_fireman 1.2 By: DANGER1979");
	print("_____________________________________________");
	print(" ");
}

stock fireman_OnPlayerStateChange(playerid, newstate)
{

	if(newstate != PLAYER_STATE_DRIVER) return 1;
	new vehicleid = nCarID[playerid];//nCarID[playerid] = GetPlayerVehicleID(playerid);//����������� � player_OnPlayerStateChange(playerid, newstate, oldstate)
	new modelid = nCarModel[playerid];//����������� � player_OnPlayerStateChange(playerid, newstate, oldstate)
	if(IsInAmbulanceCar(vehicleid))//��� �������
	{
	    if(	IsPermitToRider(playerid) ||
			PlayerInfo[playerid][pJob] == FIREMAN)
		{
	    	//if(gOnDuty[playerid] == 1) { }
	    	//else { RemovePlayerFromVehicleEx(playerid); SendClientMessage(playerid, COLOR_GREY, "   �� - �� �� ��������� !"); return 1; }
		}
	    else
		{
			if(modelid == 407 || modelid == 544)
			{
		        //RemovePlayerFromVehicleEx(playerid);
		        SendClientMessage(playerid, COLOR_GREY, "   �� �� �������� !");

		    }
			else
			{
				//RemovePlayerFromVehicleEx(playerid);
				SendClientMessage(playerid, COLOR_GREY, "   �� �� ��������� !");
				//return 1;
			}
		}
	}
	return 1;
}
//��� ���������� �����



//stock AddRandFire5Timer()
stock fireman_FiveMinutsTimer()
{   //���������� �� FiveMinutsTimer
	if((FireCounter < 1) || weathers[wethindex] == 8 || weathers[wethindex] == 16) return 1;
	//new timers = GetTickCount();
	//CrashDetected[i] = 61;
	//3 - ��� ���� ����� ��������� ����������� ��� ��� �� ������
	new Float:tmpX, Float:tmpY, Float:tmpZ;
	new tcity[20], tregion[20], sRegion[86];//23+20+20+3+20�=�86

	//SendFireBrigadeMessage(tmpX,tmpY,tmpZ, "Begin AddRandFire");

	//new rand = random(3);
	//static LastRandFlame;
	new rand = random(100+100+MAX_SBIZ);//MAX_HOUSE + 100+MAX_BIZ + 100+MAX_SBIZ
	while(rand == LastRandFlame ||
		IsFlameExists(rand) ||
		(rand >= MAX_HOUSE && rand < 100) ||
		(rand >= MAX_BIZ && rand < 200) )
	{//���� ����� �������� ����� ������� ��� ����� �������� ����� ������������� ����
		rand = random(100+100+MAX_SBIZ);//�� ������������ ������
	}
	LastRandFlame = rand;//�������� ��, ��� � ��� �����

	//format(sRegion, sizeof(sRegion), "LastRandFlame: %d", LastRandFlame);
	//SendFireBrigadeMessage(tmpX,tmpY,tmpZ, sRegion);

	if(rand >= 0 && rand < MAX_HOUSE)
	{//���� ����� ������ ���
		//CrashDetected[i] = 62;
		new house = rand;

    	tmpX = HouseInfo[house][hEntranceX];
		tmpY = HouseInfo[house][hEntranceY];
		tmpZ = HouseInfo[house][hEntranceZ];
		tcity = GetPointInZoneName(tmpX,tmpY,tmpZ);
		for(new j=0; j<MAX_TURFS; j++)
		{
			if( IsPointInRegion(tmpX,tmpY,tmpZ, j) )
			{
				strmid(tregion, regions[j][region_name], 0, strlen(regions[j][region_name]), 20);
				break;
			}
		}
		format(sRegion, sizeof(sRegion), "�.%s, ��.%s, �.%d - %s", tcity, tregion, house+1, HouseInfo[house][hDiscription]);
    }
	else if(rand >= 100 && rand < 100+MAX_BIZ)
	{
		//CrashDetected[i] = 63;
		new bouse = rand-100;

		tmpX = BizInfo[bouse][bEntranceX];
		tmpY = BizInfo[bouse][bEntranceY];
		tmpZ = BizInfo[bouse][bEntranceZ];
		tcity = GetPointInZoneName(tmpX,tmpY,tmpZ);
		for(new j=0; j<MAX_TURFS; j++)
		{
			if( IsPointInRegion(tmpX,tmpY,tmpZ, j) )
			{
				strmid(tregion, regions[j][region_name], 0, strlen(regions[j][region_name]), 20);
				break;
			}
		}
		format(sRegion, sizeof(sRegion), "�.%s, ��.%s, �.%d - %s", tcity, tregion, bouse+1, BizInfo[bouse][bDiscription]);
    }
	else if(rand >= 200 && rand < 200+MAX_SBIZ)
    {
		//CrashDetected[i] = 63;

		new sbouse = rand-200;

		tmpX = SBizInfo[sbouse][sbEntranceX];
		tmpY = SBizInfo[sbouse][sbEntranceY];
		tmpZ = SBizInfo[sbouse][sbEntranceZ];
		tcity = GetPointInZoneName(tmpX,tmpY,tmpZ);
		for(new j=0; j<MAX_TURFS; j++)
		{
			if( IsPointInRegion(tmpX,tmpY,tmpZ, j) )
			{
				strmid(tregion, regions[j][region_name], 0, strlen(regions[j][region_name]), 20);
				break;
			}
		}
		format(sRegion, sizeof(sRegion), "�.%s, ��.%s, �.%d - %s", tcity, tregion, sbouse+1, SBizInfo[sbouse][sbDiscription]);
	}
	else
	{
		//CrashDetected[i] = 64;
		return 1;
	}
	AddFireAndSmoke(rand,tmpX,tmpY,tmpZ);
	SendFireBrigadeMessage(tmpX,tmpY,tmpZ, sRegion);
	//TestLog(OPTIM, "AddRandFire", GetTickCount(), timers, 1);
	return 1;
}


//stock OnFireUpdateTimer(playerid)
stock fireman_OneSecondTimers(playerid)
{   //���������� �� ���������� �������

	if(PlayerOnFire[playerid] == 1 && !CanPlayerBurn(playerid, 1)) { StopPlayerBurning(playerid); }
	//���� ����� ����� � ���������� �� ������� ���������, �� ����������

	if(Pissing_at_Flame(playerid) != -1 || Aiming_at_Flame(playerid) != -1)
	{//���� ����� ������ �� ����� �� ����� ��� ����� � ����� ������� �� ����
		CrashDetected[playerid] = 32;

		GameTextForPlayerEx(playerid, " ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~r~~h~Flame ahead", 1500, 6);

		if( ExtTimer[playerid] == -1 && ( (Aiming_at_Flame(playerid) != -1 && Pressing(playerid) & KEY_FIRE ) ||
			Pissing_at_Flame(playerid) != -1))
		{
		    new value, time;
			//new Float:x, Float:y, Float:z;
		    if(Pissing_at_Flame(playerid) != -1)
		    {   //���� ����� ������
				value = Pissing_at_Flame(playerid);//�������� �� ����
				time = EXTINGUISH_TIME_PEEING;//10 ������
			}
			else if(Aiming_at_Flame(playerid) != -1)
			{   //���� ����� �����
				value = Aiming_at_Flame(playerid);//�������� �� ����
				if(GetPlayerWeapon(playerid) == 41)
				{   //��� ������������� ��������� �����
					CreateExplosion(FlameArray[value][Flame_pos][0], FlameArray[value][Flame_pos][1], FlameArray[value][Flame_pos][2], 2, 5);
					//continue;
					return 1;
				}
				//--------------------------------------------------------------
				if(IsPlayerInAnyVehicle(playerid)) time = EXTINGUISH_TIME_VEHICLE;
				else time = EXTINGUISH_TIME_ONFOOT;//4 �������
			}
			if(value < -1) { time = EXTINGUISH_TIME_PLAYER; }
			//����  �� ���� ����� �� �����, �� 3 �������

			time = time*1000;//��������� � �����������
			/*if(value >= -1)//���� �� ���� ����� �� ������
			{   //��������� ��� ����� ������ �������
				x = FlameArray[value][Flame_pos][0];
			    y = FlameArray[value][Flame_pos][1];
			    z = FlameArray[value][Flame_pos][2];
			    DestroyTheSmokeFromFlame(value);
			    FlameArray[value][Smoke][0] = AddSmoke(x, y, z);
			    FlameArray[value][Smoke][1] = AddSmoke(x+1, y, z);
			    FlameArray[value][Smoke][2] = AddSmoke(x-1, y, z);
			    FlameArray[value][Smoke][3] = AddSmoke(x, y+1, z);
			    FlameArray[value][Smoke][4] = AddSmoke(x, y-1, z);
				SetTimerEx("DestroyTheSmokeFromFlame", time, 0, "d", value);//��������� ������� ������ ����� EXTINGUISH_TIME_ONFOOT=4 ������
				//����� ������ ���
			}*/
			//KillTimer(ExtTimer[playerid]); ExtTimer[playerid] = -1;
			ExtTimer[playerid] = SetTimerEx("RemoveFireTimer", time, 0, "dd", playerid, value);//��������� ������� ������ ����� EXTINGUISH_TIME_ONFOOT=4 ������
			//����� ������ �����
		}
	}
	//==========================================================================
	if(CanPlayerBurn(playerid) && IsAtFlame(playerid)) { SetPlayerBurn(playerid); }//����� �������� �����

#if defined BurnOthers//���� ��������� ������ ������� ���������� �� �������������
	new Float:x, Float:y, Float:z;
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnected(i) || !IsPlayerNPC(i)) continue;
  	    if(playerid == i) continue;
	  	if(CanPlayerBurn(i) && PlayerOnFire[playerid] == 1 && !PlayerOnFire[i])
    	{
		  	GetPlayerPos(i, x, y, z);
			if(IsPlayerInRangeOfPoint(playerid, 1, x, y, z))
			{
			    SetPlayerBurn(i);
			}
		}
	}
#endif
	//--------------------------------------------------------------------------
	for(new f=0; f<MAX_FLAMES; f++)
	{
		if(FlameArray[f][Flame_Exists] != -1)
		{//��������� ��� ������������ ����
			if((GetTickCount()-FlameArray[f][Flame_Time]) > 600000)
			{//���� ����� ������ ������ 600 ������(10 �����)
				KillTimer(ExtTimer[playerid]);
				ExtTimer[playerid] = -1;
//�� �����,
				for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) ) continue;
					CrashDetected[i] = 33;
					if(	(PlayerInfo[i][pMember] == DoH && gOnDuty[i] == 1)
						|| (PlayerInfo[i][pJob] == FIREMAN && gJobDuty[i] == 1)
					  )
					{
						//PlaySoundForPlayer(i, 3401);
						//SendClientMessageEx(i, COLOR_PINK, "B��� ������� SAMD: �����");
						//SendClientMessageEx(i, COLOR_PINK, message);
						//SendRetreatOfAlertMessage(i, FlameArray[f][Flame_Exists]);

						RemovePlayerMapIcon(i, MAX_PLAYER_ICONS);
						SendClientMessageEx(i, COLOR_PINK, "B��� ������� SAMD: �����");
						new rand = FlameArray[f][Flame_Exists];
						if(rand >= 0 && rand < MAX_HOUSE)
						{
							new house = rand;
							format(strings, sizeof(strings), "��� %s[%d] ��������� %s ������", HouseInfo[house][hDiscription], house, HouseInfo[house][hOwner]);
						}
						else if(rand >= 100 && rand < 100+MAX_BIZ)
						{
							new bouse = rand-100;
							format(strings, sizeof(strings), "������ %s[%d] ��������� %s ������", BizInfo[bouse][bDiscription], bouse, BizInfo[bouse][bOwner]);
						}
						else if(rand >= 200 && rand < 200+MAX_SBIZ)
						{
							new sbouse = rand-200;
							format(strings, sizeof(strings), "�������� %s[%d] ��������� %s �������", SBizInfo[sbouse][sbDiscription], sbouse, SBizInfo[sbouse][sbOwner]);
						}
						SendClientMessageEx(i, COLOR_PINK, strings);
					}
				}
			    KillFireAndSmoke(f);
			}
		}
	}
	return 1;
}

public RemoveFireTimer(playerid, flameid)//���������� ������ ������� �� OnFireUpdateTimer(���������� �������) ���
{   //������� ������ ����
//flameid - ������ ����
//���� ����� ������
	if(flameid < -1 && Aiming_at_Flame(playerid) == flameid) { StopPlayerBurning(flameid+MAX_PLAYERS); }//���� �� ���� ������ � ���, ��� ����� � ���
	else if(flameid < -1 && Pissing_at_Flame(playerid) == flameid) { StopPlayerBurning(flameid+MAX_PLAYERS); }
//����� ���� ����� �����
	else if( FlameArray[flameid][Flame_Exists] != -1//���� ����� ��� ����������
		 	&& ( (Pressing(playerid) & KEY_FIRE && Aiming_at_Flame(playerid) == flameid ) ||//���� ������ ������� ����� � ����� ����� � ����� � �������� ������
			(Pissing_at_Flame(playerid) == flameid))//���� ����� ����� � ����� � ������� �������� �������
		)
	{
		//new sendername[MAX_PLAYER_NAME];
		//GetPlayerName(playerid, sendername, sizeof(sendername));
	    if(Pissing_at_Flame(playerid) == flameid)
		{//���� �� ���� ������ � ���, ��� ����� � ���
			SendClientMessage(playerid, FireMessageColor, "* �� �������� �����! *");

		}
		else if(Aiming_at_Flame(playerid) == flameid)
		{//���� �� ���� ������ � ���, ��� ����� � ���
			SendClientMessage(playerid, FireMessageColor, "* �� �������� �����! *");

		}
		SendRetreatOfAlertMessage(playerid, flameid);
		RemovePlayerMapIcon(playerid, MAX_PLAYER_ICONS);
	    KillFireAndSmoke(flameid);

	    if(	(PlayerInfo[playerid][pMember] == DoH && gOnDuty[playerid] == 1)
			|| (PlayerInfo[playerid][pJob] == FIREMAN && gJobDuty[playerid] == 1)
		  )
	    {
			//GivePlayerMoneyH(ffamily+PlayerInfo[playerid][pMember], playerid, (500+PlayerInfo[Offer[playerid]][pFireSkill]));
			GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, (500+PlayerInfo[playerid][pFireSkill]));
			BizInfo[0][bTill] -= 500+PlayerInfo[playerid][pFireSkill]; BizInfo[0][bImport] += 500+PlayerInfo[playerid][pFireSkill];
			//IncreaseRank(playerid, 10);

			PlayerInfo[playerid][pFireSkill] += 5;
			if(PlayerInfo[playerid][pFireSkill] == 50)
			{
				SendClientMessage(playerid, COLOR_YELLOW, "* ���� ����� ��������� ������ ������ 2. �� ��������� ������ �������������� �� �������.");
				GivePlayerMoneyH(fjob+PlayerInfo[playerid][pJob], playerid, 500); BizInfo[0][bTill] -= 500; BizInfo[0][bImport] += 500;
			}
			else if(PlayerInfo[playerid][pFireSkill] == 100)
			{
				SendClientMessage(playerid, COLOR_YELLOW, "* ���� ����� ��������� ������ ������ 3. �� ��������� ������ �������������� �� �������.");
                GivePlayerMoneyH(fjob+PlayerInfo[playerid][pJob], playerid, 1000); BizInfo[0][bTill] -= 1000; BizInfo[0][bImport] += 1000;
			}
			else if(PlayerInfo[playerid][pFireSkill] == 200)
			{
				SendClientMessage(playerid, COLOR_YELLOW, "* ���� ����� ��������� ������ ������ 4.�� ��������� ������ �������������� �� �������.");
                GivePlayerMoneyH(fjob+PlayerInfo[playerid][pJob], playerid, 2000); BizInfo[0][bTill] -= 2000; BizInfo[0][bImport] += 2000;
				}
			else if(PlayerInfo[playerid][pFireSkill] == 400)
			{
				SendClientMessage(playerid, COLOR_YELLOW, "* ���� ����� ��������� ������ ������ 5. �� ��������� ������ �������������� �� �������.");
				GivePlayerMoneyH(fjob+PlayerInfo[playerid][pJob], playerid, 4000); BizInfo[0][bTill] -= 4000; BizInfo[0][bImport] += 4000;
			}
		}
	}
	KillTimer(ExtTimer[playerid]);
	ExtTimer[playerid] = -1;
}

/*stock GetFireID(Float:X, Float:Y, Float:Z, &Float:dist)
{
	new id = -1;
	dist = 99999.99;
	for(new i; i < MAX_FLAMES; i++)
	{
		new dis2 = GetDistanceBetweenPoints(X,Y,Z, FlameArray[i][Flame_pos][0],FlameArray[i][Flame_pos][1],FlameArray[i][Flame_pos][2])
	    if(dis2 < dist)
	    {
	        dist = dis2;
	        id = i;
		}
	}
	return id;
}*/

stock CanPlayerBurn(playerid, val = 0)
{//���� ����� ����� ����������, �.�. ��� ���� � �� � �������� ������ � ���� �� �����, �� ������� 1
	if( !IsPlayerInWater(playerid) &&
		GetPlayerSkin(playerid) != 277 &&
		GetPlayerSkin(playerid) != 278 &&
		GetPlayerSkin(playerid) != 279 &&
		((val == 0 && PlayerOnFire[playerid] == 0) || (val == 1 && PlayerOnFire[playerid] == 1)))
	{ return 1; }
	return 0;
}

/* //Uncomment or copy to your script.
forward CanBurn(playerid);
public CanBurn(playerid)
{
	if(...)
	{
		return 1;
	}
	return -1; // IMPORTANT!
}

*/

stock SetPlayerBurn(playerid)
{//��������� ������
    SetPlayerAttachedObjectEx(playerid, FIRE_OBJECT_SLOT, 18690, 2, -1, 0, -1.9, 0, 0);
	PlayerOnFire[playerid] = 1;
	GetPlayerHealth(playerid, PlayerOnFireHP[playerid]);

	KillTimer(PlayerOnFireTimer[playerid]); PlayerOnFireTimer[playerid] = -1;
	PlayerOnFireTimer[playerid] = SetTimerEx("BurningTimer", 91, 1, "d", playerid);//��������� ����������� ������ ����� 91 �����������

	//KillTimer(PlayerOnFireTimer2[playerid]); PlayerOnFireTimer2[playerid] = -1;
	PlayerOnFireTimer2[playerid] = SetTimerEx("StopPlayerBurning", 7000, 0, "d", playerid);//��������� ������� ������ ����� 7 ������
//SendClientMessage(playerid, FireMessageColor, "SetPlayerBurn");
	return 1;
}

public BurningTimer(playerid)
{//���� ����� ����� �� ��������� ��� �������� �� -1 ������ 91 �����������
	if(PlayerOnFire[playerid] == 1)
	{
	    new Float:hp;
	    GetPlayerHealth(playerid, hp);
	    if(hp < PlayerOnFireHP[playerid])
	    {
	        PlayerOnFireHP[playerid] = hp;
		}
		SetPlayerHealthEx(playerid, (LastHealth[playerid]-1.0));
	    PlayerOnFireHP[playerid] -= 1.0;
	}
	else { KillTimer(PlayerOnFireTimer[playerid]); KillTimer(PlayerOnFireTimer2[playerid]); }
}

public StopPlayerBurning(playerid)
{
	KillTimer(PlayerOnFireTimer[playerid]);
	PlayerOnFire[playerid] = 0;
	RemovePlayerAttachedObject(playerid, FIRE_OBJECT_SLOT);
}
stock Aiming_at_Flame(playerid)
{//���������� ID ����, ����� � ������� ��������� �����

	new id = -1;
	new Float:dis2, Float:dis = 99999.99;
	new Float:px, Float:py, Float:pz,
		Float:cx,Float:cy,Float:cz,
		Float:fx,Float:fy,Float:fz;

	GetPlayerCameraPos(playerid, cx, cy, cz);
	GetPlayerCameraFrontVector(playerid, fx, fy, fz);
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnected(i) || !IsPlayerNPC(i)) continue;
	    if(	PlayerOnFire[i] == 1 &&//���� ����� �����
			(IsInWaterCar(playerid) || HasExtinguisher(playerid) ||
			GetPlayerWeapon(playerid) == 41))
	    {
	        GetPlayerPos(i, px, py, pz);
	        dis2 = GetDistanceCameraToPoint(cx,cy,cz, fx,fy,fz, px,py,pz);
	        if(dis2 < dis)
	        {
				dis = dis2;
	    		id = i;
	//��������������
	//new strings[256+1];
	//format(strings, sizeof(strings), "1.Aiming_at_Flame[%d]: %.1f", id, dis2);
	//SendClientMessageToAll(0xFFFFFF, strings);
			}
		}
	}
	if(id != -1) { return id-MAX_PLAYERS; }
	//-----------------------------------------------
    if(	IsInWaterCar(playerid) ||//���� ������ ����� ������ �����
		HasExtinguisher(playerid) ||//���� � ������ ������, ������� ����� ������ ����� � ����� �� � ������
		GetPlayerWeapon(playerid) == 41)//���� � ������ ��������, �� ����� �����
    {
		for(new f=0; f<MAX_FLAMES; f++)
		{
			if(FlameArray[f][Flame_Exists] != -1)
			{
				dis2 = GetDistanceCameraToPoint(cx,cy,cz, fx,fy,fz, FlameArray[f][Flame_pos][0], FlameArray[f][Flame_pos][1], FlameArray[f][Flame_pos][2]+Z_DIFFERENCE);
				if(IsPlayerInAnyVehicle(playerid) && dis2 < CAR_RADIUS && dis2 < dis)
				{
				    dis = dis2;
				    id = f;
	//��������������
	//new strings[256+1];
	//format(strings, sizeof(strings), "2.Aiming_at_Flame[%d]: %.1f", id, dis2);
	//SendClientMessageToAll(0xFFFFFF, strings);
				}
				else if(!IsPlayerInAnyVehicle(playerid) && dis2 < ONFOOT_RADIUS && dis2 < dis)
				{
				    dis = dis2;
				    id = f;
	//��������������
	//new strings[256+1];
	//format(strings, sizeof(strings), "3.Aiming_at_Flame[%d]: %.1f", id, dis2);
	//SendClientMessageToAll(0xFFFFFF, strings);
				}
			}
		}
	}
	if(id != -1)
	{//���� ����� �� ����� ��, ������������� ���������
		if(//���� ����� � ������ �� ���������� ������ 50 �
			( IsPlayerInAnyVehicle(playerid) && !IsPlayerInRangeOfPoint(playerid, 50, FlameArray[id][Flame_pos][0], FlameArray[id][Flame_pos][1], FlameArray[id][Flame_pos][2]) )	||
			( !IsPlayerInAnyVehicle(playerid) && !IsPlayerInRangeOfPoint(playerid, 5, FlameArray[id][Flame_pos][0], FlameArray[id][Flame_pos][1], FlameArray[id][Flame_pos][2]) )
		  )//���� ����� �� � ������, �� ���������� ������ 5 �
		{ id = -1; }
	}
	//��������������
	//new strings[256+1];
	//format(strings, sizeof(strings), "Aiming_at_Flame: %d", id);
	//SendClientMessageToAll(0xFFFFFF, strings);
	return id;
}
stock Pissing_at_Flame(playerid)
{//���������� ID ����, ����� � ������� ������ � ��������� � ONFOOT_RADIUS
	new id = -1;
	new Float:dis2, Float:dis = 99999.99;
	new Float:x,Float:y,Float:z,
		Float:x1,Float:y1,Float:z1,Float:a;
	GetXYZInFrontOfPlayer(playerid, 1.0, x,y,z, a);//���������� ����� �� 1 � ����� �������
	z -= Z_DIFFERENCE;//������� Z �� 2.5
	if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_PISSING && !IsPlayerInAnyVehicle(playerid) )
	{//���� ����� ������ //���� ����� �� � ������
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnected(i) || !IsPlayerNPC(i)) continue;
		    if(PlayerOnFire[i] == 1)
		    {//��������� ���� ��� �����
		        GetPlayerPos(i, x1, y1, z1);
		        if(IsPlayerInRangeOfPoint(playerid, ONFOOT_RADIUS, x1, y1, z1))
		        {
		    		id = i;
				}
			}
		}
		if(id != -1) { return id-MAX_PLAYERS; }
		//���� ���� �� ����� �� ������� ��� ��-500
		//----------------------------------------------------------------------
		for(new f=0; f<MAX_FLAMES; f++)
		{
			if(FlameArray[f][Flame_Exists] != -1)
			{//��������� ��� ������������ ����
			    dis2 = GetDistanceBetweenPoints(x,y,z, FlameArray[f][Flame_pos][0],FlameArray[f][Flame_pos][1],FlameArray[f][Flame_pos][2]);
			    if(dis2 < PISSING_WAY && dis2 < dis)//������� ����� ������� ����� � ������
				{//���� ���������� ������ ������� � ������� �� ������ �������� ����� �������� � ���������� ������ 99999.99
				    id = f;
				    dis = dis2;
				}
			}
		}
	}
	return id;
}
stock GetFlameSlot()
{//���������� ������ ������� �� ������������� ����, �.�. ��������� ����
	for(new f=0; f<MAX_FLAMES; f++)
	{
		if(FlameArray[f][Flame_Exists] == -1) { return f; }
	}
	return -1;
}

stock AddFireAndSmoke(flameid, Float:X, Float:Y, Float:Z)//, objectid=18690
{//��������� �����
	new slot = GetFlameSlot();
	if(slot == -1) { return slot; }
	FlameArray[slot][Flame_Exists] = flameid;
	FlameArray[slot][Flame_Time] = GetTickCount();
	FlameArray[slot][Flame_pos][0] = X;
	FlameArray[slot][Flame_pos][1] = Y;
	FlameArray[slot][Flame_pos][2] = Z - 2.0;// - Z_DIFFERENCE;
	//FlameArray[slot][Flame_id] = CreateObjectEx(objectid, FlameArray[slot][Flame_pos][0], FlameArray[slot][Flame_pos][1], FlameArray[slot][Flame_pos][2], 0.0,0.0,0.0, 200.0);
	FlameArray[slot][Flame_id] = CreateObjectEx(18690, FlameArray[slot][Flame_pos][0], FlameArray[slot][Flame_pos][1], FlameArray[slot][Flame_pos][2], 0.0,0.0,0.0);

	FlameArray[slot][Smoke][0] = CreateObjectEx(18727, X, Y, Z, 0.0,0.0,0.0);
	FlameArray[slot][Smoke][1] = CreateObjectEx(18727, X+1.0, Y, Z, 0.0,0.0,0.0);
	FlameArray[slot][Smoke][2] = CreateObjectEx(18727, X-1.0, Y, Z, 0.0,0.0,0.0);
	FlameArray[slot][Smoke][3] = CreateObjectEx(18727, X, Y+1.0, Z, 0.0,0.0,0.0);
	FlameArray[slot][Smoke][4] = CreateObjectEx(18727, X, Y-1.0, Z, 0.0,0.0,0.0);

	//��������������
	//new strings[256+1];
	//format(strings, sizeof(strings), "AddFire: %.4f, %.4f, %.4f", FlameArray[slot][Flame_pos][0], FlameArray[slot][Flame_pos][1], FlameArray[slot][Flame_pos][2]);
	//SendClientMessageToAll(0xFFFFFF, strings);
	return slot;
}
//��������: ������������� ������� ����� �������
stock KillFireAndSmoke(flameid)
{//������� �����
 	DestroyObjectEx(FlameArray[flameid][Flame_id], 18);

	FlameArray[flameid][Flame_Exists] = -1;
	FlameArray[flameid][Flame_pos][0] = 0.0;
	FlameArray[flameid][Flame_pos][1] = 0.0;
	FlameArray[flameid][Flame_pos][2] = 0.0;
    for(new o; o<5; o++)
	{
		DestroyObjectEx(FlameArray[flameid][Smoke][o], 19);
		FlameArray[flameid][Smoke][o] = 0;//INVALID_OBJECT_ID
	}
}


//##############################################################################//
//                                                                              //
//                               ������� ���������                              //
//                                                                              //
//##############################################################################//
stock SendFireBrigadeMessage(Float:X, Float:Y, Float:Z, const message[])
{
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(	(PlayerInfo[i][pMember] == DoH && gOnDuty[i] == 1)
			|| (PlayerInfo[i][pJob] == FIREMAN && gJobDuty[i] == 1)
		  )
		{
			//PlaySoundForPlayer(i, 3401);
			SendClientMessageEx(i, COLOR_PINK, "B��� ������� SAMD: {FFFFFF}�����");
			SendClientMessageEx(i, COLOR_PINK, message);
			SendClientMessageEx(i, COLOR_GREY, "HAMEK: � ��� 10 �����, ����� ��������� ���� � �������� �����");

			RemovePlayerMapIcon(i, MAX_PLAYER_ICONS);
			SetPlayerMapIcon(i, MAX_PLAYER_ICONS, X,Y,Z, 20, 0, MAPICON_GLOBAL);//19
		}
	}
}

//##############################################################################//
//                                                                              //
//                             ������������� �������                            //
//                                                                              //
//##############################################################################//
stock IsAtFlame(playerid)
{   //���������� ����� ���� ����� � �������� 1.2 � �� ������ � ��� ������
	for(new f=0; f<MAX_FLAMES; f++)
	{
	    if(FlameArray[f][Flame_Exists] != -1)
		{//��������� ��� ������������ ������
			if(	(!IsPlayerInAnyVehicle(playerid) && IsPlayerInRangeOfPoint(playerid, FLAME_ZONE, FlameArray[f][Flame_pos][0], FlameArray[f][Flame_pos][1], FlameArray[f][Flame_pos][2]+Z_DIFFERENCE)) ||
	   			IsPlayerInRangeOfPoint(playerid, FLAME_ZONE, FlameArray[f][Flame_pos][0], FlameArray[f][Flame_pos][1], FlameArray[f][Flame_pos][2]+Z_DIFFERENCE-1.0)
			  )//���� ����� � �������� 1.2 � �� ������ � ��� ������, �� ������� 1
		    { return 1;	}
		}
	}
	return 0;
}

stock IsInWaterCar(playerid)
{   //���������� ����� ���� ������ ����� ������ �����
    if(nCarModel[playerid] == 407 || nCarModel[playerid] == 601) { return 1; }
	return 0;
}
stock HasExtinguisher(playerid)
{//���������� ����� ���� � ������ ������, ������� ����� ������ ����� � ����� �� � ������
    if(GetPlayerWeapon(playerid) == 42 && !IsPlayerInAnyVehicle(playerid)) { return 1; }
	return 0;
}
stock IsFlameExists(flameid)
{
	for(new f=0; f<MAX_FLAMES; f++)
	{
		if(FlameArray[f][Flame_Exists] == flameid)
		{//��������� ��� ����� �� ������� ������������� ������
			return 1;
		}
	}
	return 0;
}


stock fireman_OnPlayerPickUp(playerid, pickupid)
{
	if( pickupid != PickupID[15]) return 1;
	if(PlayerInfo[playerid][pInt] != 0) return 1;
	if(PlayerInfo[playerid][pVirtual] != 0) return 1;
	if(PlayerInfo[playerid][pLocal] != FREEROAM) return 1;
	if( !IsPlayerInRangeOfPoint(playerid, 2.1, Pickups[pickupid][p_x],Pickups[pickupid][p_y],Pickups[pickupid][p_z]) ) return 1;

	if(gOnDuty[playerid])
	{   //���� ��� � �� �� ��������� � �� � �������
		SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ����� ��� ������, ����� ����� �� ������!!!!");
		return 1;
	}
	/*if(gJobDuty[playerid])
	{   //���� ��� � �� �� ��������� � �� � �������
		SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ����� ��� ������, ����� ����� �� ���������!!!!");
		return 1;
	}*/
	if(PlayerInfo[playerid][pJob] != 0 && PlayerInfo[playerid][pJob] != FIREMAN)
	{
		format(strings, sizeof(strings), "������������: {0080FF}�� �� ������ {FFFFFF}%s{0080FF}. ����� ��������� (USE: /quitjob).", GetPlayerJob(playerid) ); //���������
		SendClientMessage(playerid, COLOR_GREEN, strings);
		return 1;
	}
       /*if(SBizInfo[56][sbTill] <= 0)
       {
     		SendClientMessage(playerid, COLOR_GREY, "   ��������, ��������� �������. � ����� ��� �����.");
     		return 1;
       }*/
	if(gJobDuty[playerid])//if(PlayerInfo[playerid][pJob] == FIREMAN)
	{
		//MenuOperation[playerid] = 165);
		ShowPlayerDialogGap(playerid, FIREMAN_DIALOG, DIALOG_STYLE_MSGBOX, "���������� ��������","�� ������������� ������� ��������� ������� ����?","��","���");
	}
	else
	{
		//MenuOperation[playerid] = 166);
		new dlgitem[] = "����� ������ ������ ��������� ����������:\
\n1. �������� �� �������� ������� (��������� ����� ������� ��) � ����� �� ���������\
\n2. ��������� ������ � ������ (���������� �� ����� ��� ����� 5 �����)\
\n3. ����� � �������� ������ (ID:407) � ����������� ������\
\n4. ������ ������ (�� ���)\
\n\n�� ������ �����������, ����� ������ ������?";
		ShowPlayerDialogGap(playerid, FIREMAN_DIALOG, DIALOG_STYLE_MSGBOX, "���������� ��������",dlgitem,"��","���");
	}
	return 1;
}
stock fireman_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
		#pragma unused listitem
		#pragma unused inputtext
		if(dialogid != FIREMAN_DIALOG) return 1;//��� ���������� STEP2
//ShowPlayerDialogGap(playerid, FIREMAN_DIALOG, DIALOG_STYLE_MSGBOX, "���������� ����������","�� ������� ������ ������ ���������?","��","���");
	    if(response)
	    {
  			//if(MenuOperation[playerid] == 166)
   			if(PlayerInfo[playerid][pJob] == FIREMAN)//��� ���������� STEP10
			{
			   	if(gJobDuty[playerid]) { FireCounter --; }
				if(FireCounter <= 0) { FireCounter = 0; }
	         	PlayerInfo[playerid][pJob] = 0; gJobDuty[playerid] = 0;
	         	//WoodsmanLoading[playerid] = false;
	           	SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
	      		SendClientMessage(playerid, COLOR_GREEN, "������������: {0080FF}�� �������� ������ ���������!");
	      		//if(IsPlayerAttachedObjectSlotUsed(playerid, OBJECT_SLOT)) RemovePlayerAttachedObject(playerid, OBJECT_SLOT);
	      		//DisablePlayerCheckpointEx(playerid);
	      		//nCarID[playerid] = 0; nCarModel[playerid] = 0;
	            //JobAmmount[playerid] = 0;
	       	}
			else
			{
				PlayerInfo[playerid][pJob] = FIREMAN; gJobDuty[playerid] = 1;
	    		SetPlayerSkinEx(playerid, 278);
	    		GivePlayerWeaponEx(playerid, 42, 100);//������������
				FireCounter ++;
	          	SendClientMessage(playerid, COLOR_GREEN, "������������: {0080FF}�� ������ ������ ���������!");
	          	SendClientMessage(playerid, COLOR_GREEN, "������������: {0080FF}������ � Firetruck(������: 407)!");
      		}
        }
        else
        {


        }
		return 1;
}

stock SendRetreatOfAlertMessage(playerid, reason)
{
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(i == playerid) continue;
		if(	(PlayerInfo[i][pMember] == DoH && gOnDuty[i] == 1)
			|| (PlayerInfo[i][pJob] == FIREMAN && gJobDuty[i] == 1)
		  )
		{
			RemovePlayerMapIcon(i, MAX_PLAYER_ICONS);
			//PlaySoundForPlayer(i, 3401);
			SendClientMessageEx(i, COLOR_PINK, "B��� ������� SAMD: �����");
			format(strings, sizeof(strings), "����� %d ������� %s %s[%d]", reason, GetPlayerRanks(playerid), PlayerName(playerid), playerid);
			SendClientMessageEx(i, COLOR_PINK, strings);
		}
	}
}

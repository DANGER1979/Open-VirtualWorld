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
//#define BurnOthers						//Другие игроки будут гореть тоже, если они касаются горящего игрока?
#define EarnMoney							// Do you want to earn money for extinguish a fire?
#define FireMessageColor 0x00FF55FF			// color used for the extinguish-message

#define FLAME_ZONE 					1.0     //1.2 радиус в котором Вы начинаете гореть если Вы слишком близкие к пламени
#define ONFOOT_RADIUS				1.0		//1.5 радиус в котором Вы можете погасить пламя в футах
#define PISSING_WAY					1.0		//2.0 радиус в котором Вы можете погасить пламя писанием
#define CAR_RADIUS					3.0		//8.0 радиус в котором Вы можете погасить пламя Firetruck/SWAT Van
#define Z_DIFFERENCE				2.0		//2.5 высота, которая важна для точности тушения. пожалуйста не изменяйте
#define EXTINGUISH_TIME_VEHICLE		5		//1 необходимое время чтобы погасить огонь из firetruck (seconds)
#define EXTINGUISH_TIME_ONFOOT		10		//4 необходимое время чтобы погасить огонь огнетушителем (seconds)
#define EXTINGUISH_TIME_PEEING		60		//10 необходимое время чтобы погасить огонь писанием (seconds)
#define EXTINGUISH_TIME_PLAYER		3		//3 необходимое время чтобы погасить игрока (seconds)

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
	Flame_id,//хранит ИД объекта огня
	Flame_Exists,//-1//аписываем ИД дома или биза, что горит
	Float:Flame_pos[3],//хранит координаты огня
	Smoke[5],//хранит ИД объектов дыма
	Flame_Time
}
new FlameArray[MAX_FLAMES][FlameInfo];

new LastRandFlame;


//##############################################################################//
//                                                                              //
//                                БЛОКИ АВТОЗАМЕНЫ                              //
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
		if(PlayerOnFire[playerid] == 1)//для пожарников начало
		{
			StopPlayerBurning(playerid);
			SendClientMessage(playerid, COLOR_RED, "Вы сгорели в огне!");
		}//для пожарников конец
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
	new vehicleid = nCarID[playerid];//nCarID[playerid] = GetPlayerVehicleID(playerid);//считывается в player_OnPlayerStateChange(playerid, newstate, oldstate)
	new modelid = nCarModel[playerid];//считывается в player_OnPlayerStateChange(playerid, newstate, oldstate)
	if(IsInAmbulanceCar(vehicleid))//для медиков
	{
	    if(	IsPermitToRider(playerid) ||
			PlayerInfo[playerid][pJob] == FIREMAN)
		{
	    	//if(gOnDuty[playerid] == 1) { }
	    	//else { RemovePlayerFromVehicleEx(playerid); SendClientMessage(playerid, COLOR_GREY, "   Вы - не на Дежурстве !"); return 1; }
		}
	    else
		{
			if(modelid == 407 || modelid == 544)
			{
		        //RemovePlayerFromVehicleEx(playerid);
		        SendClientMessage(playerid, COLOR_GREY, "   Вы не Пожарный !");

		    }
			else
			{
				//RemovePlayerFromVehicleEx(playerid);
				SendClientMessage(playerid, COLOR_GREY, "   Вы не Спасатель !");
				//return 1;
			}
		}
	}
	return 1;
}
//для пожарников конец



//stock AddRandFire5Timer()
stock fireman_FiveMinutsTimer()
{   //вызывается из FiveMinutsTimer
	if((FireCounter < 1) || weathers[wethindex] == 8 || weathers[wethindex] == 16) return 1;
	//new timers = GetTickCount();
	//CrashDetected[i] = 61;
	//3 - для того чтобы увеличить вероятность что дом не сгорит
	new Float:tmpX, Float:tmpY, Float:tmpZ;
	new tcity[20], tregion[20], sRegion[86];//23+20+20+3+20 = 86

	//SendFireBrigadeMessage(tmpX,tmpY,tmpZ, "Begin AddRandFire");

	//new rand = random(3);
	//static LastRandFlame;
	new rand = random(100+100+MAX_SBIZ);//MAX_HOUSE + 100+MAX_BIZ + 100+MAX_SBIZ
	while(rand == LastRandFlame ||
		IsFlameExists(rand) ||
		(rand >= MAX_HOUSE && rand < 100) ||
		(rand >= MAX_BIZ && rand < 200) )
	{//если новое значение равно старому или новое значение равно существуещему огну
		rand = random(100+100+MAX_SBIZ);//то генерировать заново
	}
	LastRandFlame = rand;//записали то, что у нас горит

	//format(sRegion, sizeof(sRegion), "LastRandFlame: %d", LastRandFlame);
	//SendFireBrigadeMessage(tmpX,tmpY,tmpZ, sRegion);

	if(rand >= 0 && rand < MAX_HOUSE)
	{//если будет гореть дом
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
		format(sRegion, sizeof(sRegion), "г.%s, ул.%s, д.%d - %s", tcity, tregion, house+1, HouseInfo[house][hDiscription]);
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
		format(sRegion, sizeof(sRegion), "г.%s, ул.%s, д.%d - %s", tcity, tregion, bouse+1, BizInfo[bouse][bDiscription]);
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
		format(sRegion, sizeof(sRegion), "г.%s, ул.%s, д.%d - %s", tcity, tregion, sbouse+1, SBizInfo[sbouse][sbDiscription]);
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
{   //вызывается из секундного таймера

	if(PlayerOnFire[playerid] == 1 && !CanPlayerBurn(playerid, 1)) { StopPlayerBurning(playerid); }
	//если игрок горит и возгорание от игроков выключено, то остановить

	if(Pissing_at_Flame(playerid) != -1 || Aiming_at_Flame(playerid) != -1)
	{//если игрок писает на какой то огонь или рядом с огнём смотрит на него
		CrashDetected[playerid] = 32;

		GameTextForPlayerEx(playerid, " ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~r~~h~Flame ahead", 1500, 6);

		if( ExtTimer[playerid] == -1 && ( (Aiming_at_Flame(playerid) != -1 && Pressing(playerid) & KEY_FIRE ) ||
			Pissing_at_Flame(playerid) != -1))
		{
		    new value, time;
			//new Float:x, Float:y, Float:z;
		    if(Pissing_at_Flame(playerid) != -1)
		    {   //если игрок писает
				value = Pissing_at_Flame(playerid);//записали Ид огня
				time = EXTINGUISH_TIME_PEEING;//10 секунд
			}
			else if(Aiming_at_Flame(playerid) != -1)
			{   //если игрок тушит
				value = Aiming_at_Flame(playerid);//записали Ид огня
				if(GetPlayerWeapon(playerid) == 41)
				{   //при использовании балончика взрыв
					CreateExplosion(FlameArray[value][Flame_pos][0], FlameArray[value][Flame_pos][1], FlameArray[value][Flame_pos][2], 2, 5);
					//continue;
					return 1;
				}
				//--------------------------------------------------------------
				if(IsPlayerInAnyVehicle(playerid)) time = EXTINGUISH_TIME_VEHICLE;
				else time = EXTINGUISH_TIME_ONFOOT;//4 секунды
			}
			if(value < -1) { time = EXTINGUISH_TIME_PLAYER; }
			//если  ИД огня какой то игрок, то 3 секунды

			time = time*1000;//переводим в милисекунды
			/*if(value >= -1)//если ИД огня какой то объект
			{   //добавляем дым после начала тушения
				x = FlameArray[value][Flame_pos][0];
			    y = FlameArray[value][Flame_pos][1];
			    z = FlameArray[value][Flame_pos][2];
			    DestroyTheSmokeFromFlame(value);
			    FlameArray[value][Smoke][0] = AddSmoke(x, y, z);
			    FlameArray[value][Smoke][1] = AddSmoke(x+1, y, z);
			    FlameArray[value][Smoke][2] = AddSmoke(x-1, y, z);
			    FlameArray[value][Smoke][3] = AddSmoke(x, y+1, z);
			    FlameArray[value][Smoke][4] = AddSmoke(x, y-1, z);
				SetTimerEx("DestroyTheSmokeFromFlame", time, 0, "d", value);//запускаем разовый таймер через EXTINGUISH_TIME_ONFOOT=4 секунд
				//чтобы убрать дым
			}*/
			//KillTimer(ExtTimer[playerid]); ExtTimer[playerid] = -1;
			ExtTimer[playerid] = SetTimerEx("RemoveFireTimer", time, 0, "dd", playerid, value);//запускаем разовый таймер через EXTINGUISH_TIME_ONFOOT=4 секунд
			//чтобы убрать огонь
		}
	}
	//==========================================================================
	if(CanPlayerBurn(playerid) && IsAtFlame(playerid)) { SetPlayerBurn(playerid); }//игрок получает ожоги

#if defined BurnOthers//если разрешено другим игрокам загораться от загоревшегося
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
		{//сканируем все существующие огни
			if((GetTickCount()-FlameArray[f][Flame_Time]) > 600000)
			{//если время пожаро больше 600 секунд(10 минут)
				KillTimer(ExtTimer[playerid]);
				ExtTimer[playerid] = -1;
//то тушим,
				for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) ) continue;
					CrashDetected[i] = 33;
					if(	(PlayerInfo[i][pMember] == DoH && gOnDuty[i] == 1)
						|| (PlayerInfo[i][pJob] == FIREMAN && gJobDuty[i] == 1)
					  )
					{
						//PlaySoundForPlayer(i, 3401);
						//SendClientMessageEx(i, COLOR_PINK, "Bсем машинам SAMD: Пожар");
						//SendClientMessageEx(i, COLOR_PINK, message);
						//SendRetreatOfAlertMessage(i, FlameArray[f][Flame_Exists]);

						RemovePlayerMapIcon(i, MAX_PLAYER_ICONS);
						SendClientMessageEx(i, COLOR_PINK, "Bсем машинам SAMD: Отбой");
						new rand = FlameArray[f][Flame_Exists];
						if(rand >= 0 && rand < MAX_HOUSE)
						{
							new house = rand;
							format(strings, sizeof(strings), "Дом %s[%d] владельца %s сгорел", HouseInfo[house][hDiscription], house, HouseInfo[house][hOwner]);
						}
						else if(rand >= 100 && rand < 100+MAX_BIZ)
						{
							new bouse = rand-100;
							format(strings, sizeof(strings), "Бизнес %s[%d] владельца %s сгорел", BizInfo[bouse][bDiscription], bouse, BizInfo[bouse][bOwner]);
						}
						else if(rand >= 200 && rand < 200+MAX_SBIZ)
						{
							new sbouse = rand-200;
							format(strings, sizeof(strings), "Компания %s[%d] владельца %s сгорела", SBizInfo[sbouse][sbDiscription], sbouse, SBizInfo[sbouse][sbOwner]);
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

public RemoveFireTimer(playerid, flameid)//вызывается каждую секунду из OnFireUpdateTimer(секундного таймера) при
{   //убирает объект огня
//flameid - индекс огня
//если тушим игрока
	if(flameid < -1 && Aiming_at_Flame(playerid) == flameid) { StopPlayerBurning(flameid+MAX_PLAYERS); }//если ИД огня совпал с тем, что ближе к нам
	else if(flameid < -1 && Pissing_at_Flame(playerid) == flameid) { StopPlayerBurning(flameid+MAX_PLAYERS); }
//иначе если тушим пожар
	else if( FlameArray[flameid][Flame_Exists] != -1//если огонь ещё существует
		 	&& ( (Pressing(playerid) & KEY_FIRE && Aiming_at_Flame(playerid) == flameid ) ||//если нажата клавиша ОГОНЬ и игрок рядом с огнём и способен тушить
			(Pissing_at_Flame(playerid) == flameid))//если игрок рядом с огнём и введена анимация писания
		)
	{
		//new sendername[MAX_PLAYER_NAME];
		//GetPlayerName(playerid, sendername, sizeof(sendername));
	    if(Pissing_at_Flame(playerid) == flameid)
		{//если ИД огня совпал с тем, что ближе к нам
			SendClientMessage(playerid, FireMessageColor, "* Вы записали огонь! *");

		}
		else if(Aiming_at_Flame(playerid) == flameid)
		{//если ИД огня совпал с тем, что ближе к нам
			SendClientMessage(playerid, FireMessageColor, "* Вы погасили огонь! *");

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
				SendClientMessage(playerid, COLOR_YELLOW, "* Ваше Навык Пожарного теперь Уровня 2. Вы получаете больше вознаграждение за тушиние.");
				GivePlayerMoneyH(fjob+PlayerInfo[playerid][pJob], playerid, 500); BizInfo[0][bTill] -= 500; BizInfo[0][bImport] += 500;
			}
			else if(PlayerInfo[playerid][pFireSkill] == 100)
			{
				SendClientMessage(playerid, COLOR_YELLOW, "* Ваше Навык Пожарного теперь Уровня 3. Вы получаете больше вознаграждение за тушиние.");
                GivePlayerMoneyH(fjob+PlayerInfo[playerid][pJob], playerid, 1000); BizInfo[0][bTill] -= 1000; BizInfo[0][bImport] += 1000;
			}
			else if(PlayerInfo[playerid][pFireSkill] == 200)
			{
				SendClientMessage(playerid, COLOR_YELLOW, "* Ваше Навык Пожарного теперь Уровня 4.Вы получаете больше вознаграждение за тушиние.");
                GivePlayerMoneyH(fjob+PlayerInfo[playerid][pJob], playerid, 2000); BizInfo[0][bTill] -= 2000; BizInfo[0][bImport] += 2000;
				}
			else if(PlayerInfo[playerid][pFireSkill] == 400)
			{
				SendClientMessage(playerid, COLOR_YELLOW, "* Ваше Навык Пожарного теперь Уровня 5. Вы получаете больше вознаграждение за тушиние.");
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
{//если игрок может загореться, т.е. вне воды и не в пожарной одежде и пока не горит, то вернуть 1
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
{//поджигаем игрока
    SetPlayerAttachedObjectEx(playerid, FIRE_OBJECT_SLOT, 18690, 2, -1, 0, -1.9, 0, 0);
	PlayerOnFire[playerid] = 1;
	GetPlayerHealth(playerid, PlayerOnFireHP[playerid]);

	KillTimer(PlayerOnFireTimer[playerid]); PlayerOnFireTimer[playerid] = -1;
	PlayerOnFireTimer[playerid] = SetTimerEx("BurningTimer", 91, 1, "d", playerid);//запускаем бесконечный таймер через 91 милисекунду

	//KillTimer(PlayerOnFireTimer2[playerid]); PlayerOnFireTimer2[playerid] = -1;
	PlayerOnFireTimer2[playerid] = SetTimerEx("StopPlayerBurning", 7000, 0, "d", playerid);//запускаем разовый таймер через 7 секунд
//SendClientMessage(playerid, FireMessageColor, "SetPlayerBurn");
	return 1;
}

public BurningTimer(playerid)
{//если игрок горит то уменьшаем его здоровье на -1 каждые 91 милисекунду
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
{//возвращает ID огня, рядом с которым находится игрок

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
	    if(	PlayerOnFire[i] == 1 &&//если игрок горит
			(IsInWaterCar(playerid) || HasExtinguisher(playerid) ||
			GetPlayerWeapon(playerid) == 41))
	    {
	        GetPlayerPos(i, px, py, pz);
	        dis2 = GetDistanceCameraToPoint(cx,cy,cz, fx,fy,fz, px,py,pz);
	        if(dis2 < dis)
	        {
				dis = dis2;
	    		id = i;
	//ИНФОРМИРОВАНИЕ
	//new strings[256+1];
	//format(strings, sizeof(strings), "1.Aiming_at_Flame[%d]: %.1f", id, dis2);
	//SendClientMessageToAll(0xFFFFFF, strings);
			}
		}
	}
	if(id != -1) { return id-MAX_PLAYERS; }
	//-----------------------------------------------
    if(	IsInWaterCar(playerid) ||//если машина может тушить пожар
		HasExtinguisher(playerid) ||//если у игрока оружие, которое может тушить пожар и игрок не в машине
		GetPlayerWeapon(playerid) == 41)//если у игрока балончик, то будет взрыв
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
	//ИНФОРМИРОВАНИЕ
	//new strings[256+1];
	//format(strings, sizeof(strings), "2.Aiming_at_Flame[%d]: %.1f", id, dis2);
	//SendClientMessageToAll(0xFFFFFF, strings);
				}
				else if(!IsPlayerInAnyVehicle(playerid) && dis2 < ONFOOT_RADIUS && dis2 < dis)
				{
				    dis = dis2;
				    id = f;
	//ИНФОРМИРОВАНИЕ
	//new strings[256+1];
	//format(strings, sizeof(strings), "3.Aiming_at_Flame[%d]: %.1f", id, dis2);
	//SendClientMessageToAll(0xFFFFFF, strings);
				}
			}
		}
	}
	if(id != -1)
	{//если какой то нашли то, дополнительно проверяем
		if(//если игрок в машине но расстояние больше 50 м
			( IsPlayerInAnyVehicle(playerid) && !IsPlayerInRangeOfPoint(playerid, 50, FlameArray[id][Flame_pos][0], FlameArray[id][Flame_pos][1], FlameArray[id][Flame_pos][2]) )	||
			( !IsPlayerInAnyVehicle(playerid) && !IsPlayerInRangeOfPoint(playerid, 5, FlameArray[id][Flame_pos][0], FlameArray[id][Flame_pos][1], FlameArray[id][Flame_pos][2]) )
		  )//если игрок не в машине, но расстояние больше 5 м
		{ id = -1; }
	}
	//ИНФОРМИРОВАНИЕ
	//new strings[256+1];
	//format(strings, sizeof(strings), "Aiming_at_Flame: %d", id);
	//SendClientMessageToAll(0xFFFFFF, strings);
	return id;
}
stock Pissing_at_Flame(playerid)
{//возвращает ID огня, рядом с которым писает и находится в ONFOOT_RADIUS
	new id = -1;
	new Float:dis2, Float:dis = 99999.99;
	new Float:x,Float:y,Float:z,
		Float:x1,Float:y1,Float:z1,Float:a;
	GetXYZInFrontOfPlayer(playerid, 1.0, x,y,z, a);//координаты точки за 1 м перед игроком
	z -= Z_DIFFERENCE;//опускам Z на 2.5
	if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_PISSING && !IsPlayerInAnyVehicle(playerid) )
	{//если игрок писает //если игрок не в машине
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnected(i) || !IsPlayerNPC(i)) continue;
		    if(PlayerOnFire[i] == 1)
		    {//сканируем всех кто горит
		        GetPlayerPos(i, x1, y1, z1);
		        if(IsPlayerInRangeOfPoint(playerid, ONFOOT_RADIUS, x1, y1, z1))
		        {
		    		id = i;
				}
			}
		}
		if(id != -1) { return id-MAX_PLAYERS; }
		//если кого то нашли то вернуть его ИД-500
		//----------------------------------------------------------------------
		for(new f=0; f<MAX_FLAMES; f++)
		{
			if(FlameArray[f][Flame_Exists] != -1)
			{//сканируем все существующие огни
			    dis2 = GetDistanceBetweenPoints(x,y,z, FlameArray[f][Flame_pos][0],FlameArray[f][Flame_pos][1],FlameArray[f][Flame_pos][2]);
			    if(dis2 < PISSING_WAY && dis2 < dis)//находим самый ближний огонь к игроку
				{//если расстояние меньше радиуса в котором Вы можете погасить пламя писанием и расстояние меньше 99999.99
				    id = f;
				    dis = dis2;
				}
			}
		}
	}
	return id;
}
stock GetFlameSlot()
{//возвращает индекс объекта не существующего огня, т.е. свободный слот
	for(new f=0; f<MAX_FLAMES; f++)
	{
		if(FlameArray[f][Flame_Exists] == -1) { return f; }
	}
	return -1;
}

stock AddFireAndSmoke(flameid, Float:X, Float:Y, Float:Z)//, objectid=18690
{//добавляет огонь
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

	//ИНФОРМИРОВАНИЕ
	//new strings[256+1];
	//format(strings, sizeof(strings), "AddFire: %.4f, %.4f, %.4f", FlameArray[slot][Flame_pos][0], FlameArray[slot][Flame_pos][1], FlameArray[slot][Flame_pos][2]);
	//SendClientMessageToAll(0xFFFFFF, strings);
	return slot;
}
//ВНИМАНИЕ: перепроверить удаляет чужие объекты
stock KillFireAndSmoke(flameid)
{//убирает огонь
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
//                               ФУНКЦИИ СООБЩЕНИЙ                              //
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
			SendClientMessageEx(i, COLOR_PINK, "Bсем машинам SAMD: {FFFFFF}Пожар");
			SendClientMessageEx(i, COLOR_PINK, message);
			SendClientMessageEx(i, COLOR_GREY, "HAMEK: У вас 10 минут, чтобы добраться туда и потушить пожар");

			RemovePlayerMapIcon(i, MAX_PLAYER_ICONS);
			SetPlayerMapIcon(i, MAX_PLAYER_ICONS, X,Y,Z, 20, 0, MAPICON_GLOBAL);//19
		}
	}
}

//##############################################################################//
//                                                                              //
//                             ПЕРЕГРУЖЕННЫЕ ФУНКЦИИ                            //
//                                                                              //
//##############################################################################//
stock IsAtFlame(playerid)
{   //возвращает верно если игрок в радиуесе 1.2 м от пожара и вне машины
	for(new f=0; f<MAX_FLAMES; f++)
	{
	    if(FlameArray[f][Flame_Exists] != -1)
		{//сканируем все существующие пожары
			if(	(!IsPlayerInAnyVehicle(playerid) && IsPlayerInRangeOfPoint(playerid, FLAME_ZONE, FlameArray[f][Flame_pos][0], FlameArray[f][Flame_pos][1], FlameArray[f][Flame_pos][2]+Z_DIFFERENCE)) ||
	   			IsPlayerInRangeOfPoint(playerid, FLAME_ZONE, FlameArray[f][Flame_pos][0], FlameArray[f][Flame_pos][1], FlameArray[f][Flame_pos][2]+Z_DIFFERENCE-1.0)
			  )//если игрок в радиуесе 1.2 м от пожара и вне машины, то вернуть 1
		    { return 1;	}
		}
	}
	return 0;
}

stock IsInWaterCar(playerid)
{   //возвращает верно если машина может тушить пожар
    if(nCarModel[playerid] == 407 || nCarModel[playerid] == 601) { return 1; }
	return 0;
}
stock HasExtinguisher(playerid)
{//возвращает верно если у игрока оружие, которое может тушить пожар и игрок не в машине
    if(GetPlayerWeapon(playerid) == 42 && !IsPlayerInAnyVehicle(playerid)) { return 1; }
	return 0;
}
stock IsFlameExists(flameid)
{
	for(new f=0; f<MAX_FLAMES; f++)
	{
		if(FlameArray[f][Flame_Exists] == flameid)
		{//сканируем все слоты на наличие существуещего пожара
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
	{   //если коп и не на дежурстве и не в розыске
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете взять эту работу, когда вышли на службу!!!!");
		return 1;
	}
	/*if(gJobDuty[playerid])
	{   //если коп и не на дежурстве и не в розыске
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете взять эту работу, когда вышли на дежурство!!!!");
		return 1;
	}*/
	if(PlayerInfo[playerid][pJob] != 0 && PlayerInfo[playerid][pJob] != FIREMAN)
	{
		format(strings, sizeof(strings), "Работодатель: {0080FF}Вы на работе {FFFFFF}%s{0080FF}. Чтобы уволиться (USE: /quitjob).", GetPlayerJob(playerid) ); //сообщение
		SendClientMessage(playerid, COLOR_GREEN, strings);
		return 1;
	}
       /*if(SBizInfo[56][sbTill] <= 0)
       {
     		SendClientMessage(playerid, COLOR_GREY, "   Извените, лесопилка закрыта. В кассе нет денег.");
     		return 1;
       }*/
	if(gJobDuty[playerid])//if(PlayerInfo[playerid][pJob] == FIREMAN)
	{
		//MenuOperation[playerid] = 165);
		ShowPlayerDialogGap(playerid, FIREMAN_DIALOG, DIALOG_STYLE_MSGBOX, "Раздевалка пожарных","Вы действительно желаете закончить рабочий день?","Да","Нет");
	}
	else
	{
		//MenuOperation[playerid] = 166);
		new dlgitem[] = "Чтобы начать работу пожарника необходимо:\
\n1. приехать на пожарную станцию (находится возле вокзала СФ) и выйти на дежурство\
\n2. дождаться вызова о пожаре (оповещение не ранее чем через 5 минут)\
\n3. сесть в пожарную машину (ID:407) и отправиться тушить\
\n4. начать тущить (На ЛКМ)\
\n\nВы хотите переодеться, чтобы начать работу?";
		ShowPlayerDialogGap(playerid, FIREMAN_DIALOG, DIALOG_STYLE_MSGBOX, "Раздевалка пожарных",dlgitem,"Да","Нет");
	}
	return 1;
}
stock fireman_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
		#pragma unused listitem
		#pragma unused inputtext
		if(dialogid != FIREMAN_DIALOG) return 1;//для пожарников STEP2
//ShowPlayerDialogGap(playerid, FIREMAN_DIALOG, DIALOG_STYLE_MSGBOX, "Раздевалка пожарников","Вы желаете начать работу пожарника?","Да","Нет");
	    if(response)
	    {
  			//if(MenuOperation[playerid] == 166)
   			if(PlayerInfo[playerid][pJob] == FIREMAN)//для пожарников STEP10
			{
			   	if(gJobDuty[playerid]) { FireCounter --; }
				if(FireCounter <= 0) { FireCounter = 0; }
	         	PlayerInfo[playerid][pJob] = 0; gJobDuty[playerid] = 0;
	         	//WoodsmanLoading[playerid] = false;
	           	SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
	      		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы окончили работу Пожарника!");
	      		//if(IsPlayerAttachedObjectSlotUsed(playerid, OBJECT_SLOT)) RemovePlayerAttachedObject(playerid, OBJECT_SLOT);
	      		//DisablePlayerCheckpointEx(playerid);
	      		//nCarID[playerid] = 0; nCarModel[playerid] = 0;
	            //JobAmmount[playerid] = 0;
	       	}
			else
			{
				PlayerInfo[playerid][pJob] = FIREMAN; gJobDuty[playerid] = 1;
	    		SetPlayerSkinEx(playerid, 278);
	    		GivePlayerWeaponEx(playerid, 42, 100);//Огнетушитель
				FireCounter ++;
	          	SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы начали работу Пожарного!");
	          	SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Сядьте в Firetruck(модель: 407)!");
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
			SendClientMessageEx(i, COLOR_PINK, "Bсем машинам SAMD: Отбой");
			format(strings, sizeof(strings), "Пожар %d потушил %s %s[%d]", reason, GetPlayerRanks(playerid), PlayerName(playerid), playerid);
			SendClientMessageEx(i, COLOR_PINK, strings);
		}
	}
}

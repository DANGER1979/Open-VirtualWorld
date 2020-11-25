//##############################################################################//
//                                                                              //
//                              СИСТЕМА ОПЬЯНЕНИЯ                               //
//                                                                              //
//##############################################################################//

//для баров
new PlayerDrunk[MAX_PLAYERS];
new PlayerDrunkTime[MAX_PLAYERS];
new PlayerStoned[MAX_PLAYERS];//Игрок Одурманенный



stock drunk_OnPlayerConnect(playerid)
{
	PlayerDrunk[playerid] = 0; PlayerDrunkTime[playerid] = 0;//для баров
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//для меню начало
stock SetPlayerDrunkInBar(playerid, money, Float: increment, const drink[])
{//SetPlayerDrunkInBar(playerid, 6, 15.0, "beer");
	//new strings[MAX_STRING];
	//new Float:health;//для баров и закусочных
	//GetPlayerHealth(playerid, health);
	new Float:health = LastHealth[playerid];//для баров и закусочных
	if(GetPlayerMoneyH(playerid) < money)
	{
	    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
		return 1;
	}
	if(	PlayerInfo[playerid][pLocal] < 100+MAX_BIZ)
		//PlayerInfo[playerid][pLocal] != 243 && PlayerInfo[playerid][pLocal] != 244)
	{   //если это не Особняк LCN или Не Особняк Yakudza
		if(BizInfo[GetBizLocation(playerid)-100][bProducts] <= 0 && !gRealWar)
		{   //BizInfo[243-100=143][bProducts], а у нас только 78,
	        GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Bar", 5000, 1);
		    PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
		    return 1;
	    }
		OnGangsExtortionBiz(GetBizLocation(playerid)-100, money);
		//BizInfo[PlayerInfo[playerid][pLocal]-100][bProducts] --;
	}
	if(!strcmp(drink, "beer", true))
	{
		PlayerDrunk[playerid] += 1;
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER);//также добавляет опьянение
	}
	else if(!strcmp(drink, "vodka", true))
	{
		PlayerDrunk[playerid] += 2;
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);
	}
	else if(!strcmp(drink, "whiskey", true))
	{
		PlayerDrunk[playerid] += 3;
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER);
	}
	//--------------------------------------------------------------------------
	if(health >= 100.0) { PlayerInfo[playerid][pParam2] -= floatround(increment); }
	else
	{
		if(PlayerInfo[playerid][pAlcoholPerk] > 0)
		{
			new Float: hp = 2.0*PlayerInfo[playerid][pAlcoholPerk] + increment;
			SetPlayerHealthEx(playerid, (health + hp));
			PlayerInfo[playerid][pParam2] -= floatround(health + hp);
			SetPlayerDrunkLevel(playerid, PlayerDrunk[playerid]*1000/PlayerInfo[playerid][pAlcoholPerk]);
		}
	   	else
		{
			SetPlayerHealthEx(playerid, (health + increment));
			PlayerInfo[playerid][pParam2] -= floatround(health + increment);
			SetPlayerDrunkLevel(playerid, PlayerDrunk[playerid]*1000);
		}
	}
	if(PlayerInfo[playerid][pParam2] < operator2) gParameter2[playerid] = 0;//опускаме - нет больше потребности
	if(PlayerInfo[playerid][pParam2] <= 0) PlayerInfo[playerid][pParam2] = 0;//обнуляем
	SetPlayerShowScale(playerid, 2, PlayerInfo[playerid][pParam2], operator2);
	//--------------------------------------------------------------------------
	if(GetPlayerDrunkLevel(playerid) >= 5000)
	{
		GameTextForPlayerEx(playerid, "~w~You are~n~~p~Drunk", 3500, 1);
	}
	//Пьяный уровень автоматически уменьшится примерно 26 очков в секунду)
	//Уровни свыше 2000 делают пьяным игроком. Max уровень - 50000.
	//Если пьяный уровень - над 5000, радар игрока будет исчезнут.

	PlayerInfo[playerid][pCash] -= money;
	PlaySoundForPlayer(playerid, SOUND_PART_MISSION_COMPLETE);
	ResetPlayerMoney(playerid);//чтобы не отображать игровых -100 при каждой смерти
	gConsumingMoney[playerid] = 2;
	GivePlayerMoney(playerid, PlayerInfo[playerid][pCash]);
	LastMoney[playerid] = PlayerInfo[playerid][pCash];

	ApplyAnimation(playerid, "BAR", "dnk_stndM_loop",4.1,0,1,1,0,0);
	format(strings, sizeof(strings), "* %s drinks a %s.", PlayerName(playerid), drink);//не переводить
	ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
	return 1;
}
stock drunk_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(PlayerDrunk[playerid] >= 5 && ispassenger == 0)
	{
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
       		if(WantedPoints[playerid] > 25) break;
			if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
			if(i == playerid) continue;
			if(spectateid[i] != MAX_PLAYERS-1) continue;
		    if(!IsACop(i)) continue;
		    if(!gOnDuty[i]) continue;
		    //if( !IsPlayerInAnyVehicle(i) ) continue;
			//if( !IsInCopCar(nCarID[i]) ) continue;
			//if(nCarID[playerid] == nCarID[i]) continue;//если игрок не сидит в машине полицмена
			if(	!IsPlayerInRangeOfPlayer(60.0, playerid, i) ) continue;

			WantedPoints[playerid] += 25;
			new strtmp[64];
			format(strtmp, sizeof(strtmp), " Вождение в состоянии Алкогольного Опьянения [%d]", vehicleid);
			SetPlayerCriminal(DoT, playerid, i, strtmp);
			SendTeamMessage(DoT, COLOR_DARKTURQUOISE, "   USE: /pdd [16] [1-2] [playerid/PartOfName]");
       	    break;
   		}
	}
}


//stock PlayerDrunkAndStonedTimer(playerid)//выполняется каждую секунду
stock drunk_OneSecondTimers2(playerid)
{   //выполняется из OneSecondTimers
	if(AFK_IdleTime[playerid] >= 3) return 1;
	if(gPlayerSpawned[playerid] == 0) return 1;
	if(PlayerDrunk[playerid] >= 5)//для опьянения
	{
		CrashDetected[playerid] = 58;
	    PlayerDrunkTime[playerid] += 1;
	    if(PlayerDrunkTime[playerid] >= 10)
	    {   //каждые 10 секунд поворачиваем игрока
	        PlayerDrunkTime[playerid] = 0;
	        new Float:angle;
			GetPlayerFacingAngle(playerid, angle);
			if(IsPlayerInAnyVehicle(playerid))
			{
/*#define PLAYER_STATE_NONE						(0)
#define PLAYER_STATE_ONFOOT						(1)
#define PLAYER_STATE_DRIVER						(2)
#define PLAYER_STATE_PASSENGER					(3)
#define PLAYER_STATE_EXIT_VEHICLE				(4) // (used internally)
#define PLAYER_STATE_ENTER_VEHICLE_DRIVER		(5) // (used internally)
#define PLAYER_STATE_ENTER_VEHICLE_PASSENGER	(6) // (used internally)
#define PLAYER_STATE_WASTED						(7)
#define PLAYER_STATE_SPAWNED					(8)
#define PLAYER_STATE_SPECTATING					(9)
#define PLAYER_STATE_KILLED 					(10)*/
			    if(CurState[playerid] == PLAYER_STATE_DRIVER)//2
			    {
			    	SetVehicleZAngleEx(nCarID[playerid], angle + 25);
				}
			}
			else ApplyAnimation(playerid, "PED","WALK_DRUNK",4.1,0,1,0,0,0);
		    //PlayerDrunk[playerid] --;
	    }
	}
	//------------------------------------------------------------------
	if(PlayerStoned[playerid] >= 5)//Игрок Одурманенный наркотиком
	{
		CrashDetected[playerid] = 59;
        PlayerStoned[playerid] ++;
	    if(PlayerStoned[playerid] >= 25)
	    {   //каждые 20 секунд ломка
	        PlayerStoned[playerid] = 5;
	        new Float: angle;
			GetPlayerFacingAngle(playerid, angle);
			if(IsPlayerInAnyVehicle(playerid))
			{
			    if(CurState[playerid] == PLAYER_STATE_DRIVER)//2
			    {
			    	SetVehicleZAngleEx(nCarID[playerid], angle + 25);
				}
			}
			else
			{
				SetPlayerFacingAngle(playerid, angle + 90);
				ApplyAnimation(playerid, "CRACK","crckidle1",4.1,0,1,1,0,0);
			}
	    }
	    //-------------------------
	    if(LastHealth[playerid] < 100.0)
	    {
			PlayerStoned[playerid] = 0;
	    }
	}
	return 1;
}



stock drunk_OneMinutsTimer(playerid)
{  
	//if(AFK_IdleTime[playerid] >= 3) return 1;
	if(gPlayerSpawned[playerid] == 0) return 1;
    if(PlayerDrunk[playerid] > 0)
	{
		PlayerDrunk[playerid] --;
		if(PlayerDrunk[playerid] <= 0)
		{
			PlayerDrunkTime[playerid] = 0;
			GameTextForPlayerEx(playerid, "~p~Drunk effect~n~~w~Gone", 3500, 1);
		}
	}
    if(PlayerStoned[playerid] > 0)
	{
		PlayerStoned[playerid] --;
		if(PlayerStoned[playerid] <= 0) GameTextForPlayerEx(playerid, "~p~Stone effect~n~~w~Gone", 3500, 1);
	}
	return 1;
}

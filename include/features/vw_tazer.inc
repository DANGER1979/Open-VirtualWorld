
//##############################################################################//
//                                                                              //
//                              СИСТЕМА ЭЛЕКТРОШОКА                             //
//                                                                              //
//##############################################################################//


stock tazer_OnPlayerGiveDamage(playerid, damagedid, weaponid)
{
	if( weaponid == 0 && //!IsFireArm(weaponid) && // /tazer
		CurState[playerid] == PLAYER_STATE_ONFOOT &&
		GetPVarInt(playerid, "Tazer") == 1 &&
		IsPlayerAttachedObjectSlotUsed(playerid, TAZER_SLOT))
	{
	    if(	PlayerTazed[damagedid] != 1 &&
			PlayerCuffed[damagedid] >= MAX_PLAYERS-1 &&
			PlayerTied[damagedid] <= 0 &&
			!IsPlayerInAnyVehicle(damagedid) &&
			!(PlayerInfo[playerid][pMember] == DoD && PlayerInfo[damagedid][pJailed] != 10 &&//у НГ не действует на всех кроме зэков
			PlayerInfo[damagedid][pMember] != PlayerInfo[playerid][pMember])
		  )
	    {
			//format(strcmd, sizeof(strcmd), "* %s[%d] уже Оглушён.", PlayerName(damagedid), damagedid);
			//format(strcmd, sizeof(strcmd), "* %s[%d] уже в Наручниках.", PlayerName(damagedid), damagedid);
			//format(strcmd, sizeof(strcmd), "* %s[%d] уже Связан.", PlayerName(damagedid), damagedid);
	        //SendClientMessage(playerid, COLOR_GREY, "   Вы не можете парализовать пассажира автомобиля !");
	        //SendClientMessage(playerid, COLOR_GREY, "   Не можете оглушить Полицейских / ФБР на дежурстве !");// / Национальную Гвардию
	        //SendClientMessage(playerid, COLOR_GREY, "   Вы можете оглушить только заключенных !");// / Национальную Гвардию
			if((GetTickCount()-GetPVarInt(playerid, "UseTazerTime")) < 10000)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы можете использовать шокер только раз в 10 секунд.");
			}
			else
			{

				SetPVarInt(playerid, "UseTazerTime", GetTickCount());
				TogglePlayerControllableEx(damagedid, 0);//обездвиживает когда не в машине
				PlayerTazed[damagedid] = 1;
				PlayerTazeTime[damagedid] = 30;
				ClearAnimations(damagedid, 1);
				ApplyAnimation(damagedid, "CRACK", "crckdeth3",4.1,0,1,1,1,0);
				GameTextForPlayerEx(damagedid, "~r~Tazed", 2500, 3);
				gTextDrawShowBlind[damagedid] = true; OnPlayerTextDrawStateChange(damagedid);

				SetTimerEx("tHidePlayerBlind", 3000, 0, "d", damagedid);
				if(gTagForPlayer[playerid] != 0)
				{   //если переключатель ника стоит в положении включено
					format(strings, sizeof(strings), "* %s Парализовал %s'а на %d секунд.",
						PlayerName(playerid), PlayerName(damagedid), PlayerTazeTime[damagedid]);
					ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
				}
			}
		}
	}
}


stock tazer_OneSecondTimers(playerid)//TazedCuffedTied(playerid)
{
	if(!gPlayerSpawned[playerid]) return 1;
	if(PlayerTazed[playerid] >= 1)
	{	//для команды /tazer
		CrashDetected[playerid] = 20;
	    if(PlayerTazeTime[playerid] <= 0 && PlayerCuffed[playerid] == MAX_PLAYERS-1)
	    {   //если время 180 секунд наручников вышло
	        PlayerTazed[playerid] = 0;
	        PlayerTazeTime[playerid] = 0;
	        //PlayerTazeTime[playerid] = 1;
	        TogglePlayerControllableEx(playerid, 1);
			if(!IsPlayerInAnyVehicle(playerid)) ClearAnimations(playerid, 1);
			//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	    }
    	else PlayerTazeTime[playerid] -= 1;
	}
	else if(PlayerCuffed[playerid] < MAX_PLAYERS-1)// == 2 // == 3
	{   //для команды /cuff и /fc
		CrashDetected[playerid] = 21;
	    if(PlayerCuffedTime[playerid] <= 0)
	    {
	        GameTextForPlayerEx(playerid, "~r~You broke the Cuffs, you are free!", 2500, 3);
	        PlayerCuffed[playerid] = MAX_PLAYERS-1;
	        PlayerCuffedTime[playerid] = 0;

	        if(IsPlayerAttachedObjectSlotUsed(playerid, CUFF_SLOT)) RemovePlayerAttachedObject(playerid, CUFF_SLOT);
	        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

	        TogglePlayerControllableEx(playerid, 1);
			if(!IsPlayerInAnyVehicle(playerid)) ClearAnimations(playerid, 1);
			//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	    }
	    else PlayerCuffedTime[playerid] -= 1;
	}
	else if(PlayerTied[playerid] >= 1)
	{	//для команды /tie
		CrashDetected[playerid] = 22;
	    if(PlayerTiedTime[playerid] <= 0)
	    {   //если время 180 секунд наручников вышло
	        PlayerTied[playerid] = 0;
	        PlayerTiedTime[playerid] = 0;
	        TogglePlayerControllableEx(playerid, 1);
	    }
	    else PlayerTiedTime[playerid] -= 1;
	}
	return 1;
}

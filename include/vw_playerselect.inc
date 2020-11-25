//ф-ии по работе c выделением игрока путём наведения курсора
 

stock playerselect_OnPlayerUpdate(playerid, oldkeys, animationid, newstate)
//stock playerselect_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{//вызывается когда игрок нажимает правую клавишу(пробел), а другой игрок попадает в цель, т.е. появляется зелёный треугольник над головой
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
	{//если нажата ПКМ+ЛКМ
	    new targetplayer = GetPlayerTargetPlayer(playerid); //Check who a player is aiming at.
		if(targetplayer == INVALID_PLAYER_ID) return 1;//&& targetplayer != 65535
		if( !IsPlayerConnected(targetplayer) ) return 1;
		if( !IsPlayerConnectedEx(targetplayer) ) return 1;

		//new animationid = GetPlayerAnimationIndex(playerid);
		if(animationid == 1136) ClearAnimations(playerid);//надо добавить проверку что игрок стоит
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
{   //вызывается из OnPlayerClickPlayer, LookingUpdate
	if(!IsPlayerConnected(forplayerid)) { return 1; }
	if(IsPlayerNPC(forplayerid)) { return 1; }
	//ClearAnimations(playerid);

    SetPVarInt(playerid, "PlayerID", forplayerid);
	new caption[70+1];
    format(caption, sizeof(caption), "Вы выбрали игрока %s[%d]", PlayerName(forplayerid), forplayerid);

    //items_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);

    MenuOperation[playerid] = 91;
    if(PlayerInfo[playerid][pAdmin] < 1)
	{
		new listitems[] = "Поздороваться\
\nПоздороваться со всеми\
\nПоказать паспорт\
\nПослать SMS\
\nПозвонить по телефону\
\nПередать деньги\
\nПередать оружие\
\nВыразить уважение\
\nВыразить презрение\
\nПопрощаться";
		ShowPlayerDialogEx(playerid, TAB_DIALOG, DIALOG_STYLE_LIST, caption, listitems, "Ок", "Отмена");
	}
	else
	{
    	new listitems[] = "Поздороваться\
\nПоздороваться со всеми\
\nПоказать паспорт\
\nПослать SMS\
\nПозвонить по телефону\
\nПередать деньги\
\nПередать оружие\
\nВыразить уважение\
\nВыразить презрение\
\nПопрощаться\
\nАдминка";
		ShowPlayerDialogEx(playerid, TAB_DIALOG, DIALOG_STYLE_LIST, caption, listitems, "Ок", "Отмена");
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
		if(listitem == 0)//Поздороваться
		{
			ShowPlayerNameTagForPlayerEx(giveplayerid, playerid, 1);
			OnePlayAnim(playerid, "RIOT", "RIOT_ANGRY", 4.0, 0, 0, 0, 0, 0);
			format(msgitem, sizeof(msgitem), "%s {EE66EE}приветствует Вас.", PlayerName(playerid));
			SendClientMessage(giveplayerid, COLOR_WHITE, msgitem);
			PlaySoundForPlayer(playerid, 4803);
		}
		else if(listitem == 1)//Поздороваться со всеми
		{
			format(msgitem, sizeof(msgitem), "%s {EE66EE}приветствует Вас.", PlayerName(playerid));
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
		else if(listitem == 2)//Показать паспорт
		{
			if(PlayerInfo[playerid][pJailed] > 0)
			{
				playerselect_OnPlayerClick(playerid, giveplayerid);
				SendClientMessage(playerid, COLOR_GREY, "   Ваши документы отобраны пока вы под арестом !");
				return 1;
			}
			if( !IsPlayerConnected(giveplayerid) )
			{
				playerselect_OnPlayerClick(playerid, giveplayerid);
				format(msgitem, sizeof(msgitem), "   ID:%d отсутствует на сервере.", giveplayerid);
				SendClientMessage(playerid, COLOR_GREY, msgitem);
				return 1;
			}
			if(!IsPlayerInRangeOfPlayer(8.0, playerid, giveplayerid)
				|| spectateid[playerid] != MAX_PLAYERS-1 || spectateid[giveplayerid] != MAX_PLAYERS-1)
			{
				playerselect_OnPlayerClick(playerid, giveplayerid);
				SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не рядом с Вами !");
				return 1;
			}
			if(IsPlayerInAnyVehicle(giveplayerid) && GetPlayerState(giveplayerid) == PLAYER_STATE_DRIVER)
			{
				playerselect_OnPlayerClick(playerid, giveplayerid);
				SendClientMessage(playerid, COLOR_GREY, "   Игрок находится за рулём транспортного средства !");
				return 1;
			}
			if(gPlayerBoxing[giveplayerid] == 1)
			{
				playerselect_OnPlayerClick(playerid, giveplayerid);
				SendClientMessage(playerid, COLOR_GREY, "   Игрок находится на ринге !");
				return 1;
			}
	    	SetPVarInt(giveplayerid, "gDocuments", 1);
			OnPlayerShowStats(giveplayerid, playerid);
			//format(strcmd, sizeof(strcmd), "* %s показал %s'у свои Документы.", PlayerName(playerid), PlayerName(giveplayerid));
			//ProxDetector(playerid, 30.0, strcmd, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
			if(!IsPlayerInAnyVehicle(playerid)) OnePlayAnim(playerid, "TEC", "TEC_reload", 4.0, 0, 1, 1, 0, 0); //OnePlayAnim(playerid, "PED", "ATM",4.1,0,1,1,0,0);
        }
        //Для телефонов
        else if(listitem == 3)//смска
        {
			if(SBizInfo[2][sbProducts] <= 0 && !gRealWar)
			{
				playerselect_OnPlayerClick(playerid, giveplayerid);
				GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Phone Company", 5000, 1);
				PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				return 1;
			}
	        format(msgitem, sizeof(msgitem),
				"Введите текст сообщения для игрока %s[%d] на номер %d.\
				 \nСтоимость одного сообщения составляет $%d.\
				 \n\n\t{8CAA63}По окончанию ввода нажмите OK.",
				 PlayerName(giveplayerid), giveplayerid,
				 PlayerInfo[giveplayerid][pPnumber],
				 SBizInfo[2][sbEntranceCost]);
		    MenuOperation[playerid] = 92;
			ShowPlayerDialogEx(playerid, TAB_DIALOG, DIALOG_STYLE_INPUT, "SMS", msgitem, "OK", "Cancel");
        }
        else if(listitem == 4)//позвонить
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

				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете пользоваться телефоном во время работы !");
				return 1;
			}
			Call_OnPlayerSelectPlayer(playerid, giveplayerid);
		}
		else if(listitem == 5)//Передать деньги /pay
		{
			if(PlayerInfo[giveplayerid][pLocal] == 100)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Данная операция запрещена в БАНКе !");
				return 1;
			}
			if(PlayerInfo[playerid][pLevel] < 2)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы должны иметь уровень 2, чтобы передавать деньги.");
				return 1;
			}
			if(GetPlayerMoneyH(playerid) < 0 || PlayerInfo[playerid][pBank] < 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас зафиксирован минусовой баланс! Вы не можете пока передовать деньги");
				return 1;
			}
			if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "   Вы не можете передать деньги самому себе!"); return 1; }
		    if( !IsPlayerConnected(giveplayerid) )
			{
				playerselect_OnPlayerClick(playerid, giveplayerid);

				format(msgitem, sizeof(msgitem), "   ID:%d отсутствует на сервере.", giveplayerid);
				SendClientMessage(playerid, COLOR_GREY, msgitem);
				return 1;
			}
			if(!IsPlayerInRangeOfPlayer(8.0, playerid, giveplayerid)
				|| spectateid[playerid] != MAX_PLAYERS-1 || spectateid[giveplayerid] != MAX_PLAYERS-1)
			{
				playerselect_OnPlayerClick(playerid, giveplayerid);
				SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не рядом с Вами !");
				return 1;
			}
			//SetPVarInt(playerid, "PlayerID", giveplayerid);
			MenuOperation[playerid] = 93;
	 		ShowPlayerDialogEx(playerid, TAB_DIALOG, DIALOG_STYLE_INPUT, "Give Money", "Введите сумму перевода. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
        }
       	else if(listitem == 6)//Передать оружие /givegun
        {
            CMD_givegun(playerid, giveplayerid);
        }
       	else if(listitem == 7)//Выразить уважение
        {
	        if( PlayerInfo[playerid][pRespect] < 20)//(OnlineRecord*100/100))// && PlayerInfo[playerid][pAdmin] < 7
	        {
				format(msgitem, sizeof(msgitem), "   У вас %d очков уважения. Необходимо %d очков!",
					PlayerInfo[playerid][pRespect], 20); //(OnlineRecord*100/100));
				SendClientMessage(playerid, COLOR_GREY, msgitem);
				SendClientMessage(playerid, COLOR_GREY, "   Чтобы поднять уважение вы можете поучаствовать в боях на ринге");
				return 1;
	        }
	        if( PlayerInfo[playerid][pRespectDay] == getdate())// && PlayerInfo[playerid][pAdmin] < 7
	        {
				SendClientMessage(playerid, COLOR_GREY, "   Вы сегодня уже выразили своё уважение кому-то!");
				return 1;
	        }
		    if(giveplayerid == playerid)// && PlayerInfo[playerid][pAdmin] != 9
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете выражать уважение самому себе !");
				return 1;
			}
			//if(PlayerInfo[playerid][pAdmin] < 7) PlayerInfo[playerid][pRespect] -= 1;
			//SetPlayerShowBattery(playerid, 1, PlayerInfo[playerid][pRespect], ((PlayerInfo[playerid][pLevel]+1)*4) );
			PlayerInfo[giveplayerid][pRespect] += 1;
			if(PlayerInfo[playerid][pAdmin] < 7) PlayerInfo[playerid][pRespectDay] = getdate();
			//SetPlayerShowBattery(giveplayerid, 1, PlayerInfo[giveplayerid][pRespect], ((PlayerInfo[giveplayerid][pLevel]+1)*4) );
			format(msgitem, sizeof(msgitem), "   Bы выразили %s'у своё уважение.", PlayerName(giveplayerid));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
			format(msgitem, sizeof(msgitem), "   Bы получили признательность от %s'а.", PlayerName(playerid));
			SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
			SetPlayerShowBattery(giveplayerid, 1, PlayerInfo[giveplayerid][pRespect], 100);
			SendClientMessage(giveplayerid, COLOR_GREY, "   При 15 очках уважения вы сможете менять репутацию другим игрокам.");
        }
       	else if(listitem == 8)//Выразить презрение
        {
	        if( PlayerInfo[playerid][pRespect] < 20)//(OnlineRecord*40/100))// && PlayerInfo[playerid][pAdmin] < 7
	        {
				format(msgitem, sizeof(msgitem), "   У вас %d очков уважения. Необходимо %d очков!",
					PlayerInfo[playerid][pRespect], 20);//(OnlineRecord*40/100));
				SendClientMessage(playerid, COLOR_GREY, msgitem);
				SendClientMessage(playerid, COLOR_GREY, "   Чтобы поднять уважение вы можете поучаствовать в боях на ринге");
				return 1;
	        }
	        if( PlayerInfo[playerid][pRespectDay] == getdate())// && PlayerInfo[playerid][pAdmin] < 7
	        {
				SendClientMessage(playerid, COLOR_GREY, "   Вы сегодня уже изменяли кому-то репутацию!");
				return 1;
	        }
		    if(giveplayerid == playerid)// && PlayerInfo[playerid][pAdmin] != 9
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете выражать презрение самому себе !");
				return 1;
			}
			//if(PlayerInfo[playerid][pAdmin] < 7) PlayerInfo[playerid][pRespect] -= 1;
			//SetPlayerShowBattery(playerid, 1, PlayerInfo[playerid][pRespect], ((PlayerInfo[playerid][pLevel]+1)*4) );
			if(PlayerInfo[giveplayerid][pRespect] > 0) PlayerInfo[giveplayerid][pRespect] -= 1;
			if(PlayerInfo[playerid][pAdmin] < 7) PlayerInfo[playerid][pRespectDay] = getdate();
			//SetPlayerShowBattery(giveplayerid, 1, PlayerInfo[giveplayerid][pRespect], ((PlayerInfo[giveplayerid][pLevel]+1)*4) );
			format(msgitem, sizeof(msgitem), "   Bы выразили %s'у своё презрение.", PlayerName(giveplayerid));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
			format(msgitem, sizeof(msgitem), "   Bы получили презрение от %s'а.", PlayerName(playerid));
			SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
			SetPlayerShowBattery(giveplayerid, 1, PlayerInfo[giveplayerid][pRespect], 100);
			SendClientMessage(giveplayerid, COLOR_GREY, "   При менее 15 очках уважения вы не сможете менять репутацию другим игрокам.");
        }
       	else if(listitem == 9)//Попрощаться
        {
			OnePlayAnim(playerid, "GANGS", "hndshkba", 4.3, 0, 0, 0, 0, 0);
			format(msgitem, sizeof(msgitem), "%s {EE66EE}попрощался с Вами.", PlayerName(playerid));
			SendClientMessage(giveplayerid, COLOR_WHITE, msgitem);
        }
       	else if(listitem == 10)//Админка
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
	else if(MenuOperation[playerid] == 93)//Передать деньги /pay
	{
		if(!strlen(inputtext))
		{
			MenuOperation[playerid] = 93;
	 		ShowPlayerDialogEx(playerid, TAB_DIALOG, DIALOG_STYLE_INPUT, "Give Money", "Введите сумму перевода. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
			return 1;
		}
		new moneys = strval(inputtext);
		if(moneys > 1000 && PlayerInfo[playerid][pLevel] < 3)
		{
			MenuOperation[playerid] = 93;
	 		ShowPlayerDialogEx(playerid, TAB_DIALOG, DIALOG_STYLE_INPUT, "Give Money", "Введите сумму перевода. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
			SendClientMessage(playerid, COLOR_GREY, "   Вы должны иметь уровень 3, чтобы передавать свыше 1000$");
			return 1;
		}
		if(moneys < 1000 || moneys > 1000000)//80000
		{
			MenuOperation[playerid] = 93;
	 		ShowPlayerDialogEx(playerid, TAB_DIALOG, DIALOG_STYLE_INPUT, "Give Money", "Введите сумму перевода. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		    SendClientMessage(playerid, COLOR_GREY, "   Сумма должна быть не ниже 1000, и не выше 1000000 за раз.");
		    return 1;
		}

		new playermoney = GetPlayerMoneyH(playerid);
		if(moneys > 0 && playermoney >= moneys)
		{
			GivePlayerMoneyH(fpay+PlayerInfo[giveplayerid][pSQLID], playerid, -moneys);//(0 - moneys)
			OnPlayerStatsUpdate(giveplayerid, 255);
			GivePlayerMoneyH(fpay+PlayerInfo[playerid][pSQLID], giveplayerid, moneys);
			OnPlayerStatsUpdate(playerid, 255);
			format(msgitem, sizeof(msgitem), "   Bы передали %s'у(id: %d), $%d.", PlayerName(giveplayerid),giveplayerid, moneys);
			SendClientMessage(playerid, COLOR_LILAC, msgitem);
			format(msgitem, sizeof(msgitem), "   Bы получили $%d от %s(id: %d).", moneys, PlayerName(playerid), playerid);
			SendClientMessage(giveplayerid, COLOR_LILAC, msgitem);
			format(msgitem, sizeof(msgitem), "Sender %s has paid $%d to %s", PlayerName(playerid), moneys, PlayerName(giveplayerid));
			//Log(PAY,strcmd);
			if(moneys > 100000)	SendAllAdminMessage(COLOR_MAROON, msgitem, 1);
			PlaySoundForPlayer(giveplayerid, SOUND_AMMUNATION_BUY_WEAPON);//1052
			format(msgitem, sizeof(msgitem), "* %s перевёл немного наличных для %s.", PlayerName(playerid), PlayerName(giveplayerid));
			ProxDetector(playerid, 30.0, msgitem, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		}
		else
		{
			MenuOperation[playerid] = 93;
	 		ShowPlayerDialogEx(playerid, TAB_DIALOG, DIALOG_STYLE_INPUT, "Give Money", "Введите сумму перевода. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");

			SendClientMessage(playerid, COLOR_GREY, "   У вас нет столько наличных для этого !");
			return 1;
		}
	}
	else if(MenuOperation[playerid] == 94)
	{

	}
	return 1;
}


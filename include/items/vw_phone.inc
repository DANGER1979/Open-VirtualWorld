//для телефонов
new playeridMobileCall[MAX_PLAYERS];//id игрока кому сделан звонок и id игрока кем сделан звонок
new CallCost[MAX_PLAYERS];//стоимость всего разговора
new gPhoneOnline[MAX_PLAYERS];//телефон выключен
new gCellTimeCounter[MAX_PLAYERS];//счётчик времени разговора
new cchargetime = 60;//время при котором происходит списывания callcost по телефону


new Float:Telephone[47][3] = {
{-1697.0389,1334.8060,7.1797},
{-1688.7664,1359.2323,7.1722},
{-1661.2637,1397.7579,7.1722},
{-1964.0696,162.3964,27.6875},
{-1965.2167,162.3911,27.6875},
{-1966.2723,162.3976,27.6875},
{-1967.3297,162.3855,27.6875},
{2278.7866,2528.4956,10.8203},
{2278.7710,2526.6565,10.8203},
{2278.7834,2524.9622,10.8203},
{-2419.3674,717.7355,35.1719},
{1721.1857,-1720.3369,13.5410},
{1721.1970,-1721.2969,13.5452},
{1723.0861,-1721.2853,13.5470},
{1723.0792,-1720.2955,13.5390},
{638.1630,-1229.1355,18.0870},
{637.9344,-1227.5426,18.1330},
{338.8757,-1397.2609,14.2232},
{339.9344,-1397.6611,14.3896},
{339.5494,-1398.7960,14.3888},
{338.5794,-1398.6755,14.3754},
{355.3488,-1365.1289,14.4659},
{356.8065,-1364.4772,14.4849},
{523.1823,-1526.4501,14.8032},
{522.3278,-1525.6112,14.7490},
{523.0820,-1524.7758,14.6954},
{523.9950,-1525.5625,14.7462},
{523.1561,-1517.2479,14.6005},
{522.3231,-1516.4448,14.5962},
{523.0453,-1515.5686,14.5915},
{524.0080,-1516.4518,14.5963},
{523.1635,-1517.2472,14.6005},
{278.0701,-1630.6086,33.3104},
{279.6537,-1630.8873,33.3106},
{2166.3948,-1154.9231,24.8756},
{2166.4006,-1155.7961,24.8618},
{2069.4753,-1766.5579,13.5628},
{2069.4114,-1767.8278,13.5622},
{303.0597,-1592.8389,32.8478},
{302.0926,-1592.7163,32.8099},
{296.7140,-1573.7665,33.4634},
{295.1407,-1573.5374,33.4441},
{379.8264,170.0236,1008.3828},
{381.5215,170.0084,1008.3828},
{383.2478,170.0071,1008.3828},
{2259.2505,-1211.7010,23.9688},
{2257.7051,-1211.6669,23.9688}
};


stock phone_OnPlayerConnect(playerid)
{
	playeridMobileCall[playerid] = MAX_PLAYERS-1; CallCost[playerid] = 0; gPhoneOnline[playerid] = 0;gCellTimeCounter[playerid] = 0;//для телефонов
}

stock phone_OnPlayerDeath(playerid)
{
	new caller = playeridMobileCall[playerid];//для телефонов
	if(caller != MAX_PLAYERS-1)
	{
		//если игрока принявшего звонок убили во время телефонного разговора
		SendClientMessage(caller,  COLOR_GREY, "   Телефон не отвечает...");
		gCellTimeCounter[caller] = 0;

		playeridMobileCall[playerid] = MAX_PLAYERS-1;
		gCellTimeCounter[playerid] = 0;
	}
}

//stock OnPlayerKeyTelephone(playerid, newkeys)
//stock phone_OnPlayerKeyState(playerid, newkeys)
stock phone_OnPlayerKeyState_YES(playerid)//if(newkeys & KEY_YES)
{
		if(playeridMobileCall[playerid] != MAX_PLAYERS-1)
		{
			//SendClientMessage(playerid, COLOR_GREY, "   Вы - уже на вызове...");
			return 1;
		}
		//--------------------------------------------------------------
		format(strings, sizeof(strings), "$%08d", PlayerInfo[playerid][pBank]);
		PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);
		SetPVarInt(playerid, "gChatSwitcher", Off);
		GameTextForPlayerEx(playerid, "~w~                Real Chat~n~~r~                On", 5000, 6);
		//PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
		//--------------------------------------------------------------
		//PlaySoundForPlayer(playerid, 3402);
		for(new j=0, i; j<MaxPlayers; j++)
		{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			if(playeridMobileCall[i] == playerid)
			{   //сканируем всех которые мне позвонили
				playeridMobileCall[playerid] = i; //записали ID того кто вам звонит, т.е. своего собеседника
				gCellTimeCounter[i] = 1;//начало стоимости разговора у того кто позвонил
				CallCost[i] = SBizInfo[2][sbEntranceCost];//callcost;//прибавляем по 100$
				//подняли трубку вышли на связь записали ID сделавшего звонок
				format(strings, sizeof(strings), "* %s поднял трубку.", PlayerName(playerid));
				SendClientMessage(playeridMobileCall[playerid],  COLOR_LILAC, strings);

				//TextDrawBackgroundColor(txdVehicleIcon[playerid], 0x00000033);
				/*TextDrawTextSize(txdVehicleIcon[playeridMobileCall[playerid]], 120.0, 120.0);// Text size is the Width:Height
		    	TextDrawSetPreviewRot(txdVehicleIcon[playeridMobileCall[playerid]], 0.0, 0.0, 0.0);
				TextDrawSetPreviewModel(txdVehicleIcon[playeridMobileCall[playerid]], GetPlayerSkin(playerid));
				TextDrawShowForPlayer(playeridMobileCall[playerid], txdVehicleIcon[playeridMobileCall[playerid]]);

				TextDrawTextSize(txdVehicleIcon[playerid], 120.0, 120.0);// Text size is the Width:Height
		    	TextDrawSetPreviewRot(txdVehicleIcon[playerid], 0.0, 0.0, 0.0);
				TextDrawSetPreviewModel(txdVehicleIcon[playerid], GetPlayerSkin(playeridMobileCall[playerid]));
				TextDrawShowForPlayer(playerid, txdVehicleIcon[playerid]);*/

				SendClientMessage(playeridMobileCall[playerid], COLOR_GREY, "HAMEK: Вы теперь можите использовать F6 без '/', чтобы говорить по вашему телефону.");
				if( !IsPlayerInAnyVehicle(playerid) )
				{
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
					SetPlayerAttachedObjectEx(playerid, MOBILE_SLOT, 330, 6); // 4 = слот, 330 = модель телефона, 6 = правая рука
				}
				else ApplyAnimation(playerid, "CAR_CHAT", "carfone_in", 4.0,0,1,1,1,0);
				//RingTone[playerid] = 0;
				return 1;//чтобы после первого найденного телефона небыло срабатываний
			}
		}
		return 1;
}

stock phone_OnPlayerKeyState_NO(playerid)//else if(newkeys & KEY_NO)
{
		if(playeridMobileCall[playerid] == MAX_PLAYERS-1)
		{
			//SendClientMessage(playerid, COLOR_GREY, "   Вы - уже на вызове...");
			return 1;
		}
		new caller = playeridMobileCall[playerid];//playeridMobileCall[133]=3
		//ID того с кем вы говорите
		if(IsPlayerConnected(caller) && caller != INVALID_PLAYER_ID)
		{   //если собеседник в игре //ЕСЛИ у игрока есть какой то собеседник
			//PlaySoundForPlayer(caller, 3402);
			if(playeridMobileCall[caller] == playerid)//если Собеседник ещё на вызове с вами
			{   //playeridMobileCall[3] = 133 == 133

				//TextDrawHideForPlayer(playerid, txdVehicleIcon[playerid]);
				//TextDrawHideForPlayer(playeridMobileCall[playerid], txdVehicleIcon[playeridMobileCall[playerid]]);

				format(strings, sizeof(strings), "* %s повесил трубку.", PlayerName(playerid));
				//ProxDetector(caller, 10.0, strcmd, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
			    for(new t=0; t<sizeof(Telephone); t++)
			    {   //если собеседник стоит у таксофона
					if(IsPlayerInRangeOfPoint(playerid, 1.35, Telephone[t][0], Telephone[t][1], Telephone[t][2]))
					{
						//TogglePlayerControllableEx(caller, true);//освобождает
						strmid(strings, "* Собеседник повесил трубку", 0, strlen("* Собеседник повесил трубку"), 255);
						break;
					}
					if(IsPlayerInRangeOfPoint(caller, 1.35, Telephone[t][0], Telephone[t][1], Telephone[t][2]))
					{
						TogglePlayerControllableEx(caller, true);//освобождает
						break;
					}
				}
				SendClientMessage(caller,  COLOR_LILAC, strings);
				gCellTimeCounter[caller] = 0;
				playeridMobileCall[caller] = MAX_PLAYERS-1;

				if(!IsPlayerInAnyVehicle(caller))
				{
					SetPlayerSpecialAction(caller, SPECIAL_ACTION_STOPUSECELLPHONE);
					RemovePlayerAttachedObject(caller, MOBILE_SLOT);
					//ClearAnimations(caller, 1);
				}
			}
		}
	    for(new t=0; t< sizeof(Telephone); t++)
	    {
			if(IsPlayerInRangeOfPoint(playerid, 1.35, Telephone[t][0], Telephone[t][1], Telephone[t][2]))
			{
				TogglePlayerControllableEx(playerid, 1);//освобождает
				break;
			}
		}

		playeridMobileCall[playerid] = MAX_PLAYERS-1;
		gCellTimeCounter[playerid] = 0;
		SendClientMessage(playerid,  COLOR_GREY, "   Ваш телефон находится в кармане.");
		if(!IsPlayerInAnyVehicle(playerid))
		{
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
			RemovePlayerAttachedObject(playerid, MOBILE_SLOT);
			//ClearAnimations(playerid, 1);
		}
		return 1;
}


//stock CallCellTimer(playerid)//для телефонов
stock phone_OneSecondTimers(playerid)//для телефонов
{   //вызывается из OneSecondTimers
    if(gCellTimeCounter[playerid] > 0)//для телефонов //можно засунуть в минутный таймер
	{//начало разговора
		if(gCellTimeCounter[playerid] >= cchargetime)
		{   //если досчитали до 60
			gCellTimeCounter[playerid] = 1;//освободить переменную
			if(playeridMobileCall[playeridMobileCall[playerid]] == playerid)
			{//если id игрока которому сделан сделан звонок игроком
				CallCost[playerid] += SBizInfo[2][sbEntranceCost];//callcost;//прибавляем по 100 каждую минуту
			    //format(strings, sizeof(strings), "~r~%d~w~: ~g~$%d",gCellTimeCounter[playerid],CallCost[playerid]);
			    //GameTextForPlayerEx(playerid, strings, 15000, 6);
			}   //т.е. минута стоит 6000$
		}
		gCellTimeCounter[playerid] += 1;
		format(strings, sizeof(strings), "~r~%d~w~: ~g~$%d",gCellTimeCounter[playerid],CallCost[playerid]);
    	GameTextForPlayerEx(playerid, strings, 15000, 6);
	}
	else
	{
		if(CallCost[playerid] > 0)
		{   //если таймер обнулился и стоимость разговора больше нуля
			CrashDetected[playerid] = 30;
			if(PlayerInfo[playerid][pJailed] < 1)
			{//производим оплату разговора
				GivePlayerMoneyH(fsbiz+2, playerid, -CallCost[playerid]);
				OnGangsExtortionSBiz(2, CallCost[playerid]);
				SBizInfo[2][sbProducts] --;
			}
			CallCost[playerid] = 0;
		}
	}
}


//Для телефонов
stock Call_OnPlayerSelectPlayer(playerid, clickedplayerid)
{
	if(playeridMobileCall[playerid] != MAX_PLAYERS-1)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы уже приняли вызов...");
		return 1;
	}
	playeridMobileCall[playerid] = clickedplayerid; //caller connecting
	if(playerid == clickedplayerid)
	{
		playeridMobileCall[playerid] = MAX_PLAYERS-1;
		SetPVarInt(playerid, "PlayerID", MAX_PLAYERS-1);//SetPVarInt(playerid, "PlayerID", -1);
		SendClientMessage(playerid, COLOR_GREY, "   Bы не можете звонить самому себе...");//
		return 1;
	}
	if(GetPlayerMoneyH(playerid) < 100)//для экономики
	{
		playeridMobileCall[playerid] = MAX_PLAYERS-1;
		SendClientMessage(playerid, COLOR_GREY, "   У Вас нет $100 на руках !!!");
		return 1;
	}
	if(PlayerInfo[playerid][pMuted] > GetTickCount())
	{
		playeridMobileCall[playerid] = MAX_PLAYERS-1;
		format(strings, sizeof(strings), "   Вы не можете разговаривать по телефону. Вы заглушены на %d дней !", PlayerInfo[playerid][pMuted] - getdate());
		SendClientMessage(playerid, COLOR_SYSTEM, strings);
		return 1;
	}
    for(new t=0; t< sizeof(Telephone); t++)
    {
		if(!IsPlayerInAnyVehicle(playerid) &&
			IsPlayerInRangeOfPoint(playerid, 1.35, Telephone[t][0], Telephone[t][1], Telephone[t][2]))
		{
			//--------------------------------------------------------------
			format(strings, sizeof(strings), "$%08d", PlayerInfo[playerid][pBank]);
			PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);
			SetPVarInt(playerid, "gChatSwitcher", Off);
			GameTextForPlayerEx(playerid, "~w~                Real Chat~n~~r~                On", 5000, 6);
			//PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			//--------------------------------------------------------------
			PlaySoundForPlayer(playerid, SOUND_MOBILE_DIALING);//набираем номер
			TogglePlayerControllableEx(playerid, 0);//обездвиживает
			if( IsPlayerConnectedEx(clickedplayerid) )
			{
		        if(PlayerInfo[clickedplayerid][pPnumber] <= 0 || gPhoneOnline[clickedplayerid] != 0)
				{   //если у игрока нет телефона //если игрок выключил телефон
					TogglePlayerControllableEx(playerid, true);//освобождает
		            SendClientMessage(playerid, COLOR_GREY, "   Абонент недоступен !");
					playeridMobileCall[playerid] = MAX_PLAYERS-1;
		            return 1;
		        }
				if(playeridMobileCall[clickedplayerid] == MAX_PLAYERS-1)
				{   //если телефон свободен
					//new phonenumb == 755;
					//PlaySoundForPlayer(clickedplayerid, SOUND_DOOR_BUZER);
					PlaySoundForPlayer(clickedplayerid, SOUND_MOBRING);
					SendClientMessage(clickedplayerid, COLOR_LILAC, "Tелефонный 3вонок. Введите /pickup или нажмите клавишу ~k~~CONVERSATION_YES~, чтобы поднять трубку");
					//------------------------------------------------------------------
					//format(strings, sizeof(strings), "* %s набрал номер на таксофоне.", PlayerName(playerid));
					//ProxDetector(playerid, 10.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
					SendClientMessage(playerid, COLOR_GREY, "HAMEK: Введите /hangup или нажмите клавишу ~k~~CONVERSATION_NO~, чтобы опустить трубку");

					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
					SetPlayerAttachedObjectEx(playerid, MOBILE_SLOT, 330, Right_hand); // 4 = слот, 330 = модель телефона, 6 = правая рука
					return 1;
				}
				else {
					TogglePlayerControllableEx(playerid, true);//освобождает
					SendClientMessage(playerid, COLOR_GREY, "   Абонент уже принял вызов. Перезвоните позже...");
				}
			}
			else {
				TogglePlayerControllableEx(playerid, true);//освобождает
				SendClientMessage(playerid, COLOR_GREY, "   Абонент находится вне зоны действия сети !");
			}
			playeridMobileCall[playerid] = MAX_PLAYERS-1;
			return 1;
		}
	}
	//==========================================================================
	if(PlayerInfo[playerid][pPnumber] == 0)
	{
		playeridMobileCall[playerid] = MAX_PLAYERS-1;
		SendClientMessage(playerid, COLOR_GREY, "   У вас нет телефона !");
		return 1;
	}
	if(gPhoneOnline[playerid] == 1)// && PlayerInfo[playerid][pAdmin] < 1
	{
		playeridMobileCall[playerid] = MAX_PLAYERS-1;
		SendClientMessage(playerid, COLOR_GREY, "   У Вас выключен Телефон (USE: /togphone, чтобы включить)");
		return 1;
	}
	PlaySoundForPlayer(playerid, SOUND_MOBILE_DIALING);//набираем номер
    //new strings[MAX_STRING];
	if( IsPlayerConnectedEx(clickedplayerid) )
	{
        if(PlayerInfo[clickedplayerid][pPnumber] <= 0)
		{   //если у игрока нет телефона //если игрок выключил телефон
			SendClientMessage(playerid, COLOR_GREY, "   Абонент не зарегистрирован в мобильной сети или не имеет средства связи !");
			playeridMobileCall[playerid] = MAX_PLAYERS-1;
            return 1;
        }
        if(gPhoneOnline[clickedplayerid] > 0)
		{   //если у игрока нет телефона //если игрок выключил телефон
            SendClientMessage(playerid, COLOR_GREY, "   Абонент недоступен !");
			playeridMobileCall[playerid] = MAX_PLAYERS-1;
            return 1;
        }
		if(playeridMobileCall[clickedplayerid] == MAX_PLAYERS-1)
		{   //если телефон свободен
			//--------------------------------------------------------------
			format(strings, sizeof(strings), "$%08d", PlayerInfo[playerid][pBank]);
			PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);
			SetPVarInt(playerid, "gChatSwitcher", Off);
			GameTextForPlayerEx(playerid, "~w~                Real Chat~n~~r~                On", 5000, 6);
			//PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			//--------------------------------------------------------------
			PlaySoundForPlayer(clickedplayerid, SOUND_MOBRING);//звонит телефон
			format(strings, sizeof(strings), "Tелефонный 3вонок от {FFFFFF}%s[%d]. {AFAFAF}Введите /pickup или нажмите клавишу ~k~~CONVERSATION_YES~, чтобы поднять трубку",
				PlayerName(playerid), playerid);//PlayerInfo[playerid][pPnumber]);
			SendClientMessage(clickedplayerid, COLOR_LILAC, strings);
			//------------------------------------------------------------------
			//format(strings, sizeof(strings), "* %s достал свой телефон.", PlayerName(playerid));
			//SendClientMessage(playerid, COLOR_LILAC, strings);
			SendClientMessage(playerid, COLOR_GREY, "HAMEK: Введите /hangup или нажмите клавишу ~k~~CONVERSATION_NO~, чтобы опустить трубку");
			if(!IsPlayerInAnyVehicle(playerid))
			{
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
				SetPlayerAttachedObjectEx(playerid, MOBILE_SLOT, 330, Right_hand); // 4 = слот, 330 = модель телефона, 6 = правая рука
			}
			else ApplyAnimation(playerid, "CAR_CHAT", "carfone_in", 4.0,0,1,1,1,0);
			return 1;
		}
		else SendClientMessage(playerid, COLOR_GREY, "   Абонент уже принял вызов. Перезвоните позже...");
	}
	else  SendClientMessage(playerid, COLOR_GREY, "   Абонент находится вне зоны действия сети !");
	playeridMobileCall[playerid] = MAX_PLAYERS-1;
	return 1;
}


stock SMS_OnPlayerSelectPlayer(playerid, clickedplayerid, const inputtext[])
{
	if(PlayerInfo[playerid][pMuted] > GetTickCount())
	{
		format(strings, sizeof(strings), "   Вы не можете писать SMS-сообщения. Вы заглушены на %d дней !", PlayerInfo[playerid][pMuted] - getdate());
		SendClientMessage(playerid, COLOR_SYSTEM, strings);
		return 1;
	}
 	/*if(playeridMobileCall[playerid] != MAX_PLAYERS-1)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете во время разговора писать SMS-сообщения !");
		return 1;
	}
	playeridMobileCall[playerid] = clickedplayerid; //caller connecting
	if(playerid == clickedplayerid)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Bы не можете писать SMS самому себе...");//
		return 1;
	}
	if(GetPlayerMoneyH(playerid) < 1000)
	{
		SendClientMessage(playerid, COLOR_GREY, "   У вас не достаточно денег!");
		return 1;
	}*/
 	//==========================================================================
	if(PlayerInfo[playerid][pPnumber] == 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   У вас нет телефона !");
		return 1;
	}
	if(gPhoneOnline[playerid] == 1)// && PlayerInfo[playerid][pAdmin] < 1
	{
		SendClientMessage(playerid, COLOR_GREY, "   У Вас выключен Телефон (USE: /togphone, чтобы включить)");
		return 1;
	}
	if(!strlen(inputtext) || strlen(inputtext) > 87)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Ваше сообщение не может быть отправлено, т.к. кол-во символов больше 87 или пусто!");
		return 1;
	}
	//new strings[MAX_STRING];
	if( IsPlayerConnectedEx(clickedplayerid) )
	{
        if(PlayerInfo[clickedplayerid][pPnumber] <= 0)
		{   //если у игрока нет телефона //если игрок выключил телефон
			SendClientMessage(playerid, COLOR_GREY, "   Абонент не зарегистрирован в мобильной сети или не имеет средства связи !");
            return 1;
        }
        if(gPhoneOnline[clickedplayerid] > 0)
		{   //если у игрока нет телефона //если игрок выключил телефон
            SendClientMessage(playerid, COLOR_GREY, "   Абонент недоступен !");
            return 1;
        }
        if(GetPlayerMoneyH(playerid) < SBizInfo[2][sbEntranceCost])
        {
			format(strings, sizeof(strings), "   У вас нет $%d наличных !", SBizInfo[2][sbEntranceCost]);
			SendClientMessage(playerid, COLOR_GREY, strings);
            return 1;
        }
        PlaySoundForPlayer(clickedplayerid, SOUND_ROULETTE_NO_CASH);
		//format(strings, sizeof(strings), "SMS: {FFFFFF}%s,{CC99FF}Отправитель:{FFFFFF}%s[%d] {CC99FF}Ph:{FFFFFF}%d", inputtext, PlayerName(playerid), playerid, PlayerInfo[playerid][pPnumber]);
		format(strings, sizeof(strings), "SMS: {FFFFFF}%s,{CC99FF}Отправитель:{FFFFFF}%s[%d]", inputtext, PlayerName(playerid), playerid);
		ProxDetectorTelephone(clickedplayerid, COLOR_YELLOW, strings);
		SendClientMessage(playerid, COLOR_GREY, "   Текстовое Сообщение Отправлено.");
		if(PlayerInfo[playerid][pJailed] < 1)
		{
			GivePlayerMoneyH(fsbiz+2, playerid, -SBizInfo[2][sbEntranceCost]);//callcost);
			OnGangsExtortionSBiz(2, SBizInfo[2][sbEntranceCost]);//callcost);
			SBizInfo[2][sbProducts] --;
		}
		//}
		//else SendClientMessage(playerid, COLOR_GREY, "   Абонент уже принял вызов. Перезвоните позже...");
	}
	else  SendClientMessage(playerid, COLOR_GREY, "   Абонент находится вне зоны действия сети !");
	//playeridMobileCall[playerid] = MAX_PLAYERS-1;
	return 1;
}

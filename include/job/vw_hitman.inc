//для киллеров
new gGotHit[MAX_PLAYERS];//заказ принят по индексу цели - цель заказана
new GotChaseHitID[MAX_PLAYERS];//ID цели по id киллера
new GetChaseKillerID[MAX_PLAYERS];//ID киллера по id цели
new OrderReady[MAX_PLAYERS];
new ConnectedToPC[MAX_PLAYERS];


stock hitman_OnPlayerConnect(playerid)
{
//для киллеров
	gGotHit[playerid] = 0;
	GotChaseHitID[playerid] = MAX_PLAYERS-1; GetChaseKillerID[playerid] = MAX_PLAYERS-1;
	OrderReady[playerid] = 0; ConnectedToPC[playerid] = 0;
}

//для киллеров
stock hitman_OnPlayerStateChange(playerid, newstate)
{
	PlayerInfo[playerid][pMember] != Hitman) return 1;
	if(newstate != PLAYER_STATE_WASTED)  return 1;
//выполняется сразу после смерти игрока
//если ID нового состояния равно состоянию 7
	if(GotChaseHitID[playerid] >= MAX_PLAYERS-1) return 1;
   	if(	IsPlayerConnected(GotChaseHitID[playerid])
		&& gGotHit[GotChaseHitID[playerid]] == 1
		&& PlayerInfo[GotChaseHitID[playerid]][pHeadValue] > 0)
   	{	//если заказ принят и /если цена за голову > 0
		PlayerInfo[playerid][pProfSkill] -= 5;
		if(PlayerInfo[GotChaseHitID[playerid]][pPurposeMurder] > 0)//для киллеров
		{
			//PlayerInfo[playerid][pRespect] --;
			GivePlayerMoneyB(ffamily+PlayerInfo[playerid][pMember], playerid, (-PlayerInfo[GotChaseHitID[playerid]][pHeadValue]/2) );
		}
		format(strings, sizeof(strings), "Hitman %s не выполнил заказ на %s'a",
			PlayerName(playerid), PlayerName( GotChaseHitID[playerid] ) );
		SendFamilyMessage(Hitman, strings);
		//PlayerInfo[GotChaseHitID[playerid]][pHeadValue] = 0;
		gGotHit[GotChaseHitID[playerid]] = 0;//освободили - заказ не принят
   		GetChaseKillerID[GotChaseHitID[playerid]] = MAX_PLAYERS-1;//освободили ID киллера по id цели
   		GotChaseHitID[playerid] = MAX_PLAYERS-1;//освободили ID цели киллера
	}
	return 1;
}

stock hitman_OnPlayerDisconnect(playerid)
{
	//==========================================================================
	//для киллеров
    if(GetChaseKillerID[playerid] < MAX_PLAYERS-1 && GameRestart != 1)
    {//если для вас установлен киллер, т.е. какой то килер взял на вас заказ
        if(	IsPlayerConnected(GetChaseKillerID[playerid]) &&
			PlayerInfo[GetChaseKillerID[playerid]][pMember] == Hitman)
        {   //если Киллер ещё в игре
   			format(strings, sizeof(strings), "Ваша цель: %s[%d] покинула зону досягаемости!!! (%s)", PlayerName(playerid), playerid, strreason);
			SendClientMessage(GetChaseKillerID[playerid], COLOR_CERISE, strings);

    		gGotHit[playerid] = 0;//освободили - заказ не принят по индексу цели
    		GotChaseHitID[GetChaseKillerID[playerid]] = MAX_PLAYERS-1;//освободили ID цели по индексу киллера
    		GetChaseKillerID[playerid] = MAX_PLAYERS-1;//освободили ID киллера по id цели
		}
    }
}

stock hitman_OnPlayerPickUp(playerid, pickupid)
{
	if( IsPlayerInRangeOfPoint(playerid, 1.9, -684.9224,939.5638,13.6328))
	{	//для киллеров
		CrashDetected[playerid] = 98;
		if(gParameter2[playerid] == 1)
		{
			SendClientMessage(playerid, COLOR_GREY, "    В отчаянии Вы не можете получить задание, сесть в авто или выйти на дежурство !");
			SendClientMessage(playerid, COLOR_GREY, "    Вам необходимо развлечься: посетите клубы и потанцуйте !");
			return 1;
		}
		if(gRealWar)
		{
			SendClientMessage(playerid, COLOR_GREY, "    Активизирован режим игры RealWar ! Вы не можете выйти на дежурство!");
			return 1;
		}
		if(gJobDuty[playerid])
		{   //если коп и не на дежурстве и не в розыске
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете выйти на дежурство, когда вышли на работу.");
			return 1;
		}
		if(PlayerInfo[playerid][pMember] == Hitman && !GetPVarInt(playerid, "gInRacing"))
		{
			PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			if(gOnDuty[playerid] == 0)
	        {
	        	/*PlayerInfo[playerid][pTeam] = 2;*/
				SetPlayerSkinEx(playerid, PlayerInfo[playerid][pChar]);
				gOnDuty[playerid] = 1;
			}
			else //if(gOnDuty[playerid] == 1)
			{
				/*PlayerInfo[playerid][pTeam] = 3;*/
				SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
				gOnDuty[playerid] = 0;
			}
		}
		new cost;
	    if(OrderReady[playerid] > 0)
	    {
			ResetPlayerWeaponsEx(playerid);//сбросить оружие
	        switch(OrderReady[playerid])
	        {
	            case 1:
	            {   //|(1) ($5000) Rank 1: Knife(200), Desert Eagle(2400), MP5(10000), Shotgun(2400), Rifle(1000)
	                //GivePlayerWeaponEx(playerid, 4, 1); GivePlayerWeaponEx(playerid, 24, 30); GivePlayerWeaponEx(playerid, 29, 450);
					//GivePlayerWeaponEx(playerid, 25, 60); GivePlayerWeaponEx(playerid, 33, 20);
					GivePlayerWeaponEx(playerid, 4, 1); GivePlayerWeaponEx(playerid, 23, 60);
					cost = 1060;//для экономики
	            }
	            case 2:
	            {   //|(2) ($6000) Rank 2: Knife, Silenced 9mm(1200), Sniper(10/5000 2*5000=10000
	                GivePlayerWeaponEx(playerid, 4, 1); GivePlayerWeaponEx(playerid, 23, 20);
					GivePlayerWeaponEx(playerid, 34, 10);
					cost = 1140;
	            }
	            case 3:
	            {   //|(3) ($6000) Rank 3: Knife, Silenced, Shotgun, Sniper(10000)
	                GivePlayerWeaponEx(playerid, 4, 1); GivePlayerWeaponEx(playerid, 23, 40); //GivePlayerWeaponEx(playerid, 25, 60);
					GivePlayerWeaponEx(playerid, 34, 20);
					cost = 1380;
	            }
	            case 4:
	            {   //|(4) ($8000) Rank 4: Knife, Silenced, MP5, Sniper
	               	GivePlayerWeaponEx(playerid, 4, 1); GivePlayerWeaponEx(playerid, 23, 80); //GivePlayerWeaponEx(playerid, 29, 450);
					GivePlayerWeaponEx(playerid, 34, 40);
					cost = 2140;
	            }
	            case 5:
	            {   //|(5) ($8000) Rank 6: Knife, Silenced, MP5, Shotgun, Sniper
	                GivePlayerWeaponEx(playerid, 4, 1); GivePlayerWeaponEx(playerid, 23, 160); //GivePlayerWeaponEx(playerid, 29, 450);
					//GivePlayerWeaponEx(playerid, 25, 60);
					GivePlayerWeaponEx(playerid, 34, 80);
					cost = 2380;
				}
	            case 6:
	            {   //|(6) ($8500) Rank 8: Knife, Desert Eagle, MP5, Shotgun, AK47(14000), Sniper
	                GivePlayerWeaponEx(playerid, 4, 1); GivePlayerWeaponEx(playerid, 23, 320); //GivePlayerWeaponEx(playerid, 24, 30); //GivePlayerWeaponEx(playerid, 29, 450);
					//GivePlayerWeaponEx(playerid, 25, 60); GivePlayerWeaponEx(playerid, 30, 480);
					GivePlayerWeaponEx(playerid, 34, 160);
					cost = 3900;
				}
	            case 7:
	            {   //|(7) ($8500) Rank 8: Knife(200), Desert Eagle(2400), MP5(10000), Shotgun(2400), M4(18000), Sniper(10000)
	                GivePlayerWeaponEx(playerid, 4, 1); GivePlayerWeaponEx(playerid, 23, 640); //GivePlayerWeaponEx(playerid, 24, 30); //GivePlayerWeaponEx(playerid, 29, 450);
					//GivePlayerWeaponEx(playerid, 25, 60); GivePlayerWeaponEx(playerid, 31, 480);
					GivePlayerWeaponEx(playerid, 34, 320);
					cost = 4300;
	            }
	        }
	        new Float:rating[MAX_PLAYERS];
	        if(PlayerInfo[playerid][pDeaths] == 0) PlayerInfo[playerid][pDeaths] = 1;
			rating[playerid] = PlayerInfo[playerid][pKills]/PlayerInfo[playerid][pDeaths];//Возвращает абсолютное значение вещественного числа.
			if(rating[playerid] <= 0) rating[playerid] = 1;
			if(PlayerInfo[playerid][pRank] <= 0) PlayerInfo[playerid][pRank] = 1;
			new money = floatround( float(cost) / (rating[playerid]*PlayerInfo[playerid][pRank]) );
			//float - используется для того, чтобы полулить результат дробного деления, а не целочисленного
			//float - преобразовывает целое в вещественную
			GivePlayerMoneyH(fsbiz+9, playerid, -money);
			//SBizInfo[9][sbTill] += money/2;//перечислили деньги в биз General Store за покупку пакетов киллеров
			//BizInfo[0][bProducts] += money/2;//перечислили деньги в БАНК
			BizInfo[0][bTill] += money/2; BizInfo[0][bExport] += money/2;
			format(strings, sizeof(strings), "* %s поднял Пакет %d с Заказом на сумму $%d с учётом рейтинга и ранга.", PlayerName(playerid), OrderReady[playerid], money);
			ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
			OrderReady[playerid] = 0;
		}
		//return 1;
	}//Hitman delivery stuff
}

stock SearchingHit(playerid)//для киллеров
{   // выполняется при вводе текста Contracts
	new searchhit = 0;
	new DialogIDCounter = 0; for(new d=0; d<MAX_DLGITEMS; d++) DialogID[playerid][d] = -1;
	new bigmsgitem[2048];//25*(42 + 2+24+3+10)
	//new tmp[16];
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if(searchhit >= MAX_DLGITEMS) break;
		if( !IsPlayerConnectedEx(i) ) continue;
		if( PlayerInfo[i][pGunLic] != 1 && !gRealWar) continue;
		if( gGotHit[i] != 0) continue;//заказ ещё не взят//обнуляется при входе
		if(PlayerInfo[i][pHeadValue] <= 0) continue;
		if(PlayerInfo[i][pAccount] != 0) continue;
		//сканируем все головы за которые назначено вознагражданеие
   		searchhit ++;//поднимаем флаг для поиска контрактов - есть контракты
   		DialogID[playerid][DialogIDCounter] = i;
   		//if(PlayerInfo[i][pGunLic] == 1) tmp = "имеется";
   		//else tmp = "отсутствует";
		format(bigmsgitem, sizeof(bigmsgitem), "%s%d\tЦель: %s[%d]\tВознаграждение: $%d\n",// Лицензия: %s
			bigmsgitem, searchhit, PlayerName(i), i, PlayerInfo[i][pHeadValue]);//, tmp
		DialogIDCounter ++;
		if(DialogIDCounter >= 25) break;
	}
	if(searchhit < 1) { SendClientMessage(playerid, COLOR_GREY, "   Нет доступных контрактов!"); return 1; }
	if(IsPlayerInArea(playerid, specialzone[6]))
	{
		MenuOperation[playerid] = 96;
		new TextRow[65];
		format(TextRow, sizeof(TextRow), "Hitman Agency Contracts: %d", searchhit);
		ShowPlayerDialogEx(playerid, HITMAN_DIALOG, DIALOG_STYLE_LIST, TextRow, bigmsgitem, "OK", "Cancel");
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не находитесь в особняке !");
	}
	return 1;
}

stock hitman_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
			//#pragma unused listitem
			#pragma unused inputtext
			if(dialogid != HITMAN_DIALOG) return 1;
			SetPVarInt(playerid, "gShowDialog", -1);
			if(!response)
			{
			    SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Вы закрыли свой изношенный ПК и отключились от сервера Агентства.");
      			ConnectedToPC[playerid] = 0;
			 	return 1;
			}
			new msgitem[256+1];
			//new giveplayerid;
///portable
//ShowPlayerDialogEx(playerid, HITMAN_DIALOG, DIALOG_STYLE_LIST, "Hitman Agency", listitems, "OK", "Cancel");
//"News\nContracts\nGivehit\nOrder\nRating\nLogout";
			if(MenuOperation[playerid] == 95)
			{
				if(listitem == 0)//News
				{
					new dlgitem[512];
					SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: News [number] [text] or News delete [number] or News delete all");
					format(msgitem, sizeof(msgitem), "1. %s :: \tHitman: %s", News[hAdd1], News[hContact1]);
					strins(dlgitem, msgitem, strlen(dlgitem));
					format(msgitem, sizeof(msgitem), "\n2. %s :: \tHitman: %s", News[hAdd2], News[hContact2]);
					strins(dlgitem, msgitem, strlen(dlgitem));
					format(msgitem, sizeof(msgitem), "\n3. %s :: \tHitman: %s", News[hAdd3], News[hContact3]);
					strins(dlgitem, msgitem, strlen(dlgitem));
					format(msgitem, sizeof(msgitem), "\n4. %s :: \tHitman: %s", News[hAdd4], News[hContact4]);
					strins(dlgitem, msgitem, strlen(dlgitem));
					format(msgitem, sizeof(msgitem), "\n5. %s :: \tHitman: %s", News[hAdd5], News[hContact5]);
					strins(dlgitem, msgitem, strlen(dlgitem));
					if(strlen(dlgitem) >= sizeof(dlgitem) || strlen(dlgitem) <= 0)
					{
						//ИНФОРМИРОВАНИЕ
						format(msgitem, sizeof(msgitem), "Error11: Hitman Agency News %s[%d], strlen(listitems): %d, sizeof(listitems): %d",
							PlayerName(playerid), playerid, strlen(dlgitem), sizeof(dlgitem));
						Log(ERROR, msgitem);
						return 1;
					}
					ShowPlayerDialogEx(playerid, HITMAN_DIALOG, DIALOG_STYLE_LIST, "Hitman Agency News", dlgitem, "OK", "Cancel");
				}
				else if(listitem == 1)//Contracts
				{
					ConnectedToPC[playerid] = 0;
				    if(GotChaseHitID[playerid] < MAX_PLAYERS-1)
				    {   //если ID цели киллера уже установлено на какое-то значение
				        SendClientMessage(playerid, COLOR_GREY, "   У Вас уже есть Цель !");
						return 1;
				    }
					SearchingHit(playerid);//запусить ф-ию поиска контрактов
				}
				else if(listitem == 2)//Order
				{
					ConnectedToPC[playerid] = 0;
			        if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
			        {
				        SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на оружие!");
					    return 1;
			        }
				    if(PlayerInfo[playerid][pRank] < 2)
					{
				        SendClientMessage(playerid, COLOR_GREY, "   Вам пока не доступны пакеты с оружием !");
				        return 1;
					}
				    if(OrderReady[playerid] > 0)
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   Вы уже заказали пакет !");
				        return 1;
				    }
					if( gParameter5[playerid] == 1 )
					{
						SendClientMessage(playerid, COLOR_GREY, "   У Вас нету сил, чтобы держать оружие!");
						SendClientMessage(playerid, COLOR_GREY, "   Вам необходимо добраться до кровати и поспать!");
						return 1;
					}

					new dlgitem[62+47+56+52+61+70+69];//398
					new DialogIDCounter = 0;
					for(new i=0; i<MAX_DLGITEMS; i++) DialogID[playerid][i] = -1;
				    if(PlayerInfo[playerid][pRank] >= 2)
					{   //для экономики
						strcat(dlgitem, "1. \t$1600 \tRank 2: Knife, Silenced");//strcat(dlgitem, "1. \t$1600 \tRank 1: Knife, Desert Eagle, MP5, Shotgun, Rifle");
						DialogID[playerid][0] = DialogIDCounter;
						DialogIDCounter ++;
					}
				    if(PlayerInfo[playerid][pRank] >= 3)
					{
						strcat(dlgitem, "\n2. \t$1140 \tRank 3: Knife, Silenced, Sniper");//strcat(dlgitem, "\n2. \t$1140 \tRank 2: Knife, Silenced, Sniper");
						DialogID[playerid][1] = DialogIDCounter;
						DialogIDCounter ++;
					}
				    if(PlayerInfo[playerid][pRank] >= 5)
					{
						strcat(dlgitem, "\n3. \t$1380 \tRank 5: Knife, Silenced, Sniper");//strcat(dlgitem, "\n3. \t$1380 \tRank 3: Knife, Silenced, Shotgun, Sniper");
						DialogID[playerid][2] = DialogIDCounter;
						DialogIDCounter ++;
					}
				    if(PlayerInfo[playerid][pRank] >= 7)
					{
						strcat(dlgitem, "\n4. \t$2140 \tRank 7: Knife, Silenced, Sniper");//strcat(dlgitem, "\n4. \t$2140 \tRank 4: Knife, Silenced, MP5, Sniper");
						DialogID[playerid][3] = DialogIDCounter;
						DialogIDCounter ++;
					}
				    if(PlayerInfo[playerid][pRank] >= 9)
					{
						strcat(dlgitem, "\n5. \t$2380 \tRank 9: Knife, Silenced, Sniper");//strcat(dlgitem, "\n5. \t$2380 \tRank 5: Knife, Silenced, MP5, Shotgun, Sniper");
						DialogID[playerid][4] = DialogIDCounter;
						DialogIDCounter ++;
					}
				    if(PlayerInfo[playerid][pRank] >= 10)
					{
						strcat(dlgitem, "\n6.\t$3900 \tRank 10: Knife, Silenced, Sniper");//strcat(dlgitem, "\n6.\t$3900 \tRank 6: Knife, Desert Eagle, MP5, Shotgun, AK47, Sniper");
						DialogID[playerid][5] = DialogIDCounter;
						DialogIDCounter ++;
					}
				    if(PlayerInfo[playerid][pRank] >= 10)
					{
						strcat(dlgitem, "\n7. \t$4300 \tRank 10: Knife, Silenced, Sniper");//strcat(dlgitem, "\n7. \t$4300 \tRank 6: Knife, Desert Eagle, MP5, Shotgun, M4, Sniper");
						DialogID[playerid][6] = DialogIDCounter;
						//DialogIDCounter ++;
					}
					MenuOperation[playerid] = 97;
					ShowPlayerDialogEx(playerid, HITMAN_DIALOG, DIALOG_STYLE_LIST, "Available Packages", dlgitem, "OK", "Cancel");
				}
				else if(listitem == 3)//Rating
				//else if((strcmp("Rating", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("Rating")))
				{
					ConnectedToPC[playerid] = 0;
					new dlgitem[1024];
					strins(dlgitem, "id \tname \t\t\tlevel \trank\trating\n______________________________________________________________________\n", strlen(dlgitem));
					new Float:rating[MAX_PLAYERS];
					for(new j=0, i; j<MaxPlayers; j++)	{
						i = PLIDs[j];
						if( !IsPlayerConnectedEx(i) ) continue;
						if(PlayerInfo[i][pMember] == Hitman)
						{
					        if(PlayerInfo[i][pDeaths] == 0) PlayerInfo[i][pDeaths] = 1;
			                rating[i] = PlayerInfo[i][pKills]/PlayerInfo[i][pDeaths];//Возвращает абсолютное значение вещественного числа.
							if(strlen(PlayerName(i)) < 13) format(msgitem, sizeof(msgitem), "%d \t%s \t\t%d \t%d \t%.1f\n", i, PlayerName(i), PlayerInfo[i][pLevel], PlayerInfo[i][pRank], rating[i]);
							else format(msgitem, sizeof(msgitem), "%d \t%s \t%d \t%d \t%.1f\n", i, PlayerName(i), PlayerInfo[i][pLevel], PlayerInfo[i][pRank], rating[i]);
							strins(dlgitem, msgitem, strlen(dlgitem));
						}
					}
					strins(dlgitem, "\n______________________________________________________________________\n", strlen(dlgitem));
					if(strlen(dlgitem) >= sizeof(dlgitem) || strlen(dlgitem) <= 0)
					{
						//ИНФОРМИРОВАНИЕ
						format(msgitem, sizeof(msgitem), "Error12: Agency's Ratings %s[%d], strlen(listitems): %d, sizeof(listitems): %d",
							PlayerName(playerid), playerid, strlen(dlgitem), sizeof(dlgitem));
						Log(ERROR, msgitem);
						return 1;
					}
					ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, "Agency's Ratings", dlgitem, "OK", "");
				}
			}
			else if(MenuOperation[playerid] == 96)
			{//Contracts
				SetPVarInt(playerid, "PlayerID", DialogID[playerid][listitem]);
				new hitid = DialogID[playerid][listitem];
				PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				if(hitid == playerid)
				{
					SendClientMessage(playerid, COLOR_GREY, "  Вы не можете взять заказ на самого себя !");
					return 1;
				}
			    if( !IsPlayerConnectedEx(hitid) )
			    {
			        SendClientMessage(playerid, COLOR_GREY, "   Цель вне досягаемости !");
			        return 1;
			    }
			    if(	IsPlayerInRangeOfPlayer(500.0, playerid, hitid) )
			    {
			        SendClientMessage(playerid, COLOR_GREY, "   Цель слишком близко !");
			        return 1;
			    }
    			format(msgitem, sizeof(msgitem), "Hitman %s, принял заказ на убийство: %s[%d], за $%d.", PlayerName(playerid), PlayerName(hitid), hitid, PlayerInfo[hitid][pHeadValue]);
    			SendFamilyMessage(Hitman, msgitem);
    			GotChaseHitID[playerid] = hitid;//ID цели
    			GetChaseKillerID[hitid] = playerid;//ID киллера - охотника на цель
    			gGotHit[hitid] = 1;//заказ принят по индексу цели - цель заказана
    			hitid = MAX_PLAYERS-1;//освободили ID цели

    			format(msgitem, sizeof(msgitem), "Hitman принял заказ на убийство: %s[%d]. Обеспечьте ему охрану.", PlayerName(hitid), hitid);
    			SendFamilyMessage(FBI, msgitem);
    			//hitfound = 0;//освободили контракты просмотрены
			}
			else if(MenuOperation[playerid] == 97)
			{
				if(listitem == DialogID[playerid][0])
			    //if((strcmp("1", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("1")))
				{
				    if(PlayerInfo[playerid][pRank] < 2) { SendClientMessage(playerid, COLOR_GREY, "   Ваш Ранг - не достаточно высок, чтобы Заказывать этот Пакет !"); return 1; }
				    if(GetPlayerMoneyH(playerid) > 1600)
				    {   //для экономики
				        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Вы Заказали Пакет 1 ($1600). Он будет доставлен в Здание Агентства.");
				        OrderReady[playerid] = 1;
				    }
				    else
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   Вы не можете позволить себе этот Пакет !");
				    }
				}
				else if(listitem == DialogID[playerid][1])
				{
				    if(PlayerInfo[playerid][pRank] < 2) { SendClientMessage(playerid, COLOR_GREY, "   Ваш Ранг - не достаточно высок, чтобы Заказывать этот Пакет !"); return 1; }
				    if(GetPlayerMoneyH(playerid) > 1140)
				    {
				        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Вы заказали себе пакет 2 ($1400). Он будет доставлен в Здание Агентства.");
				        OrderReady[playerid] = 2;
				    }
				    else
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   Вы не можете позволить себе этот Пакет !");
				    }
				}
				else if(listitem == DialogID[playerid][2])
				{
				    if(PlayerInfo[playerid][pRank] < 3) { SendClientMessage(playerid, COLOR_GREY, "   Ваш Ранг - не достаточно высок, чтобы Заказывать этот Пакет !"); return 1; }
				    if(GetPlayerMoneyH(playerid) > 1380)
				    {
				        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Вы заказали себе пакет 3 ($1380). Он будет доставлен в Здание Агентства.");
				        OrderReady[playerid] = 3;
				    }
				    else
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   Вы не можете позволить себе этот Пакет !");
				    }
				}
				else if(listitem == DialogID[playerid][3])
				{
				    if(PlayerInfo[playerid][pRank] < 4) { SendClientMessage(playerid, COLOR_GREY, "   Ваш Ранг - не достаточно высок, чтобы Заказывать этот Пакет !"); return 1; }
				    if(GetPlayerMoneyH(playerid) > 2140)
				    {
				        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Вы заказали себе пакет 4 ($2140). Он будет доставлен в Здание Агентства.");
				        OrderReady[playerid] = 4;
				    }
				    else
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   Вы не можете позволить себе этот Пакет !");
				    }
				}
				else if(listitem == DialogID[playerid][4])
				{
				    if(PlayerInfo[playerid][pRank] < 6) { SendClientMessage(playerid, COLOR_GREY, "   Ваш Ранг - не достаточно высок, чтобы Заказывать этот Пакет !"); return 1; }
				    if(GetPlayerMoneyH(playerid) > 2380)
				    {
				        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Вы заказали себе пакет 5 ($2380). Он будет доставлен в Здание Агентства.");
				        OrderReady[playerid] = 5;
				        return 1;
				    }
				    else
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   Вы не можете позволить себе этот Пакет !");
				    }
				}
				else if(listitem == DialogID[playerid][5])
				{
				    if(PlayerInfo[playerid][pRank] < 8) { SendClientMessage(playerid, COLOR_GREY, "   Ваш Ранг - не достаточно высок, чтобы Заказывать этот Пакет !"); return 1; }
				    if(GetPlayerMoneyH(playerid) > 3900)
				    {
				        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Вы заказали себе пакет 6 ($3900). Он будет доставлен в Здание Агентства.");
				        OrderReady[playerid] = 6;
				    }
				    else
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   Вы не можете позволить себе этот Пакет !");
				    }
				}
				else if(listitem == DialogID[playerid][6])
				{
				    if(PlayerInfo[playerid][pRank] < 10) { SendClientMessage(playerid, COLOR_GREY, "   Ваш Ранг - не достаточно высок, чтобы Заказывать этот Пакет !"); return 1; }
				    if(GetPlayerMoneyH(playerid) > 4300)
				    {
				        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Вы Заказали Пакет 7 ($4300). Он будет доставлен в Здание Агентства.");
				        OrderReady[playerid] = 7;
				    }
				    else
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   Вы не можете позволить себе этот Пакет !");
				    }
				}
			}
			return 1;
}

stock hitman_OnPlayerDeath(playerid, killerid)//Hitman_OnPlayerDeath(playerid, killerid)
{   //вызывается из OnPlayerDeath
	if(killerid == INVALID_PLAYER_ID) return 0;
    if(!IsPlayerConnectedEx(killerid)) return 0;
    if(PlayerInfo[killerid][pMember] != Hitman) return 0;
	if(PlayerInfo[playerid][pHeadValue] <= 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "Hitman Agency: на этого игрока не назначена цена за голову.");
		return 0;
	}
	if(PlayerInfo[killerid][pInt] != 0 || PlayerInfo[killerid][pLocal] != FREEROAM)
	{
		SendClientMessage(playerid, COLOR_GREY, "Hitman Agency: Убитый игрок находился в интерьере или локации.");
		return 0;
	}
	if(GotChaseHitID[killerid] != playerid)
	{
		SendClientMessage(playerid, COLOR_GREY, "Hitman Agency: Убитый игрок не соответствует вашей цели.");
		return 0;
	}

	//new strings[MAX_STRING];
    if( PlayerInfo[playerid][pPurposeMurder] == 301)
   	{
        if(PlayerInfo[playerid][pBikeLic] == 1) { PlayerInfo[playerid][pBikeLic] = 0; }
        if(PlayerInfo[playerid][pCarLic] == 1) { PlayerInfo[playerid][pCarLic] = 0; }
		if(PlayerInfo[playerid][pFlyLic] == 1) { PlayerInfo[playerid][pFlyLic] = 0; }
		if(PlayerInfo[playerid][pBoatLic] == 1) { PlayerInfo[playerid][pBoatLic] = 0; }
        if(PlayerInfo[playerid][pFishLic] == 1) { PlayerInfo[playerid][pFishLic] = 0; }
        if(PlayerInfo[playerid][pGunLic] == 1) { PlayerInfo[playerid][pGunLic] = 0; SetPlayerToTeamColor(6); }
		SendClientMessage(playerid, 0x88EE88FF, "Hitman Agency: все ваши ЛИЦЕНЗИИ отобраны.");
		IncreaseRank(killerid, 25);
    }
	else if( PlayerInfo[playerid][pPurposeMurder] >= 0 && PlayerInfo[playerid][pPurposeMurder] < MAX_HOUSE &&
			PlayerInfo[playerid][pHouse] != NOT_KEY &&
			PlayerInfo[playerid][pSQLID] == HouseInfo[PlayerInfo[playerid][pHouse]][hOwned])
	{
		new house = PlayerInfo[playerid][pHouse];
		//HouseInfo[house][hHel] = 0;
		//HouseInfo[house][hTV] = 0;
		//HouseInfo[house][hCloth] = 0;
		HouseInfo[house][hLock] = 0;
		HouseInfo[house][hOwned] = 0;
		HouseInfo[house][hLock] = 0;
		//HouseInfo[house][hRentabil] = 0;
		strmid(HouseInfo[house][hOwner], "The State", 0, strlen("The State"), 255);
		SaveHouse(house);

		for(new limit = 0; limit < 5; limit++)
		{
			if(MyHouse[playerid][limit] != house) continue;
			MyHouse[playerid][limit] = NOT_KEY;
		}
		PlayerInfo[playerid][pHouse] = NOT_KEY;//cбросили ключи //ВНИМАНИЕ нельзя т.к. домов может быть больше 1
		//OnPlayerStatsUpdate(playerid);

		format(strings, sizeof(strings), "%s has sell house %d for $%d. reason: killed by %s",
			PlayerName(playerid), house, HouseInfo[house][hBuyPrice],
			PlayerName(killerid));
		Log(BUY,strings);

		new text_info[19+20+24];
    	format(text_info, sizeof(text_info), "[ %s ]", HouseInfo[house][hDiscription]);
		//Update3DTextLabelText(text3D[house], 0x88EE88FF, strings);
		Update3DTextLabelEx(hEntranceText3D[house], 0x88EE88FF, text_info);

		format(strings, sizeof(strings), "Hitman Agency: ваш ДОМ продан за $%d",HouseInfo[house][hBuyPrice]);
		SendClientMessage(playerid, 0x88EE88FF, strings);
		IncreaseRank(killerid, 25);
	}
	else if(PlayerInfo[playerid][pPurposeMurder] >= 100 && PlayerInfo[playerid][pPurposeMurder] < 100+MAX_BIZ)
	{//если был заказан на биз, то снести первый
		new bouse;
		for(new limit = 0; limit < 10; limit++)
		{
			if(MyBizz[playerid][limit] == NOT_KEY) continue;
			bouse = MyBizz[playerid][limit];
			MyBizz[playerid][limit] = NOT_KEY;
			break;
		}
		if(bouse == 0)
		{
			SendClientMessage(killerid, 0x88EE88FF, "Hitman Agency: заказ не выполнен. Причина: у игрока отсутствует бизнес");
			return 1;
		}
		OnBizInit(bouse);
		SaveBiz(bouse);
		//OnPlayerStatsUpdate(playerid);

		/*format(strings, sizeof(strings), "%s has sell biz %d for $%d. reason: killed by %s",
			PlayerName(playerid), bouse, BizInfo[bouse][bBuyPrice],
			PlayerName(killerid));*/
		format(strings, sizeof(strings), "%s has sell biz %d reason: killed by %s",
			PlayerName(playerid), bouse, PlayerName(killerid));
		Log(BUY,strings);

		new text_info[19+20+24];
    	format(text_info, sizeof(text_info), "[ %s ]",BizInfo[bouse][bDiscription]);
		//Update3DTextLabelText(text3D[MAX_HOUSE+bouse], 0xEEEE88FF, strings);
		Update3DTextLabelEx(bEntranceText3D[bouse], 0xEEEE88FF, text_info);

		//format(strings, sizeof(strings), "Hitman Agency: ваш БИЗНЕС продан за $%d", BizInfo[bouse][bBuyPrice]);
		SendClientMessage(playerid, 0x88EE88FF, "Hitman Agency: ваш БИЗНЕС продан");
		IncreaseRank(killerid, 25);
	}
	else if(PlayerInfo[playerid][pPurposeMurder] >= 200 && PlayerInfo[playerid][pPurposeMurder] < 200+MAX_SBIZ)
	{
		//для владения несколькими бизами
#if defined vw_sql//#endif
		new ToBase[44+24];
		new sbouse;// = PlayerInfo[playerid][pBizz]-100;
		//format(ToBase, sizeof(ToBase), "SELECT `ID` FROM `sbizz` WHERE `Owner`='%s'",PlayerName(playerid));
		format(ToBase, sizeof(ToBase), "SELECT `ID` FROM `sbizz` WHERE `Owned`=%d LIMIT 1", PlayerInfo[playerid][pSQLID]);
		mysql_query(ToBase); mysql_store_result();
		if(mysql_num_rows() > 0 && mysql_retrieve_row())
	 	{
	 		new Field[20];
			mysql_fetch_field_row(Field, "ID");	sbouse = strval(Field)-1;
		}
		mysql_free_result();
#endif
		new sbouse;
		for(new limit = 0; limit < 20; limit++)
		{
			if(MyCompany[playerid][limit] == NOT_KEY) continue;
			sbouse = MyCompany[playerid][limit];
			MyCompany[playerid][limit] = NOT_KEY;
			break;
		}
		if(sbouse == 0)
		{
			SendClientMessage(killerid, 0x88EE88FF, "Hitman Agency: заказ не выполнен. Причина: у игрока отсутствует компания");
			return 1;
		}
		OnSBizInit(sbouse);
		SaveSBiz(sbouse);

		PlayerInfo[playerid][pBizz] = NOT_KEY;
		//OnPlayerStatsUpdate(playerid);

		/*format(strings, sizeof(strings), "%s has sell sbiz %d for $%d. reason: killed by %s",
			PlayerName(playerid), bouse, SBizInfo[bouse][sbBuyPrice],
			PlayerName(killerid));*/
		format(strings, sizeof(strings), "%s has sell sbiz %d reason: killed by %s",
			PlayerName(playerid), sbouse, PlayerName(killerid));
		Log(BUY,strings);

		new text_info[19+20+24];
    	format(text_info, sizeof(text_info), "[ %s ]",SBizInfo[sbouse][sbDiscription]);
		//Update3DTextLabelText(text3D[MAX_HOUSE+MAX_BIZ+bouse], 0xEEEE88FF, strings);
		Update3DTextLabelEx(sbEntranceText3D[sbouse], 0xEEEE88FF, text_info);

		format(strings, sizeof(strings), "Hitman Agency: ваша КОМПАНИЯ продана за $%d", SBizInfo[sbouse][sbBuyPrice]);
		SendClientMessage(playerid, 0x88EE88FF, strings);
		IncreaseRank(killerid, 25);
	}
	else
	{
		IncreaseRank(killerid, 1);
		SendClientMessage(playerid, 0x88EE88FF, "Вы стали жертвой Hitman Agancy");
	}
	if(IsACop(playerid)) IncreaseRank(killerid, 10);

	FamilyInfo[0+PlayerInfo[killerid][pMember]][fBank] += PlayerInfo[playerid][pHeadValue]/2;
	GivePlayerMoneyB(ffamily+PlayerInfo[killerid][pMember], killerid, PlayerInfo[playerid][pHeadValue]/2 );

	format(strings, sizeof(strings), "Hitman Agency: Вам перечислено на счёт в банке $%d за выполнение заказа !", PlayerInfo[playerid][pHeadValue]/2);
	SendClientMessage(killerid, COLOR_MAROON, strings);
	format(strings, sizeof(strings), "Hitman %s выполнил заказ на %s'a", PlayerName(killerid),PlayerName(playerid));
	SendFamilyMessage(Hitman, strings);

	PlayerInfo[playerid][pHeadValue] = 0;
	PlayerInfo[playerid][pPurposeMurder] = 0;
	gGotHit[playerid] = 0;//освободили - заказ не принят
	GetChaseKillerID[playerid] = MAX_PLAYERS-1;//освободили ID киллера
	GotChaseHitID[killerid] = MAX_PLAYERS-1;//освободили ID цели киллера
	return 1;
}


stock right(source[], len)//для киллеров
{   //вызывается по команде news
	new retval[MAX_STRING], srclen;
	srclen = strlen(source);
	strmid(retval, source, srclen - len, srclen, MAX_STRING);
	return retval;
}



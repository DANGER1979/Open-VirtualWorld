//##############################################################################//
//                                                                              //
//                                 СПИСКИ КОМАНД                                //
//                                                                              //
//##############################################################################//


stock command_help(playerid)//LISTCOMMAND(playerid);
{
	new listitems[] = "1. Основные\n2. Чат\n3. Авто\n4. Помощь по работе\n5. Помощь по фракциям\n6. Лидерам\n7. Прочее";//\nДом\nБизнесы и компании
	ShowPlayerDialogEx(playerid, LISTCMD_DIALOG, DIALOG_STYLE_LIST, "COMMAND - наберите команду для информации", listitems, "OK", "Назад");
}

stock command_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	backcmd_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	gencommands_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	
	if(dialogid != LISTCMD_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response) { LIST(playerid); return 1; }//PlaySoundForPlayer(playerid, 5202);
	//--------------------------------------------------------------------------
	//new strcmd[MAX_STRING];
	if(listitem == 0) GeneralCMD(playerid); //Основные
	else if(listitem == 1) ChatCMD(playerid);//Чат
	else if(listitem == 2) CarCMD(playerid);//Авто
	else if(listitem == 3) job_command(playerid);//Помощь по работе
	else if(listitem == 4) family_command(playerid);//Помощь по фракциям
	else if(listitem == 5) LeaderCMD(playerid);//Лидерам
	else if(listitem == 6) OtherCMD(playerid);//Прочее
	return 1;
}
stock GeneralCMD(playerid)
{
	new listitems[307];
	strcat(listitems, "/stats - статистика игрока");
	strcat(listitems, "\n/spawnchange - переключатель между доступными точками возрождения");
	strcat(listitems, "\n/givegun - взять оружие из домашнего шкафчика");
	strcat(listitems, "\n/show - показать/скрыть все панели на экране");
	//strcat(listitems, "\n/changepass - поменять пароль");
	//strcat(listitems, "\n/changeorigin - поменять место рождения");
	//strcat(listitems, "\n/info - информация о моде и сервере");
	//strcat(listitems, "\n/servernetstats - показать сервера networkstats");
	//strcat(listitems, "\n/netstats - показать ваш собственный networkstats");
	ShowPlayerDialogEx(playerid, COMMANDS_DIALOG, DIALOG_STYLE_LIST, "*** GENERAL COMMANDS ***", listitems, "OK", "Назад");
}

stock ChatCMD(playerid)
{
	new dlgitem[55+71+27+92+62+33+28];
	strcat(dlgitem, "\n/o - общий чат, если включен. Диапазон не ограничен.");
	strcat(dlgitem, "\n/l - локальный чат. Диапазон в пределах всей локации, т.е. интерьера");
	strcat(dlgitem, "\n/s - крик. Диапазон 60 м");
	strcat(dlgitem, "\n/me - Позволяет Вам выражать Ваши мысли или действия другим игрокам. Диапазон 30 м");
	strcat(dlgitem, "\n/w - приватный чат с игроком по указанному ID. Диапазон 8 м");
	strcat(dlgitem, "\n/b - non-rp чат. Диапазон 60 м");
	strcat(dlgitem, "\n/clearchat - очистить чат");
	ShowPlayerDialogEx(playerid, BACKCMD_DIALOG, DIALOG_STYLE_MSGBOX, "*** CHAT COMMANDS ***", dlgitem, "OK", "Назад");
}
stock CarCMD(playerid)
{
	new listitems[703];
	strcat(listitems, "\n/lock(Left_Alt+Space) - открыть/закрыть автомобиль");//Left_Alt+Space
	strcat(listitems, "\n/parking("#VEHICLE_LOOKLEFT") - запарковать автомобиль");// listitems, RusToGame("~k~~VEHICLE_LOOKLEFT~"));//num4
	strcat(listitems, "\n/unparking("#VEHICLE_LOOKRIGHT") - распарковать автомобиль");//num6 //~k~~VEHICLE_LOOKRIGHT~
	strcat(listitems, "\n/fillcar - залить 20 л. топлива из канистры");
	strcat(listitems, "\n/rentcar - арендовать автомобиль в автосалоне");
	strcat(listitems, "\n/engine(2) - завести/заглушить двигатель");//2 //~k~~TOGGLE_SUBMISSIONS~
	strcat(listitems, "\n/boot - открыть/закрыть багажник");
	strcat(listitems, "\n/bonnet - открыть/закрыть капот");
	strcat(listitems, "\n/alarm - включить/выключить сигнализацию");
	strcat(listitems, "\n/lights(H+Left_Alt) - включить/выключить свет");
	strcat(listitems, "\n/eject - выбросить игрока с вашего автомобиля");
	strcat(listitems, "\n/carinfo - посмотреть информацию о автомобилях");
	strcat(listitems, "\n/redraft - переоформить авто на другого(сидя на вод.месте)");
	strcat(listitems, "\n/findcar - найти своё авто");
	strcat(listitems, "\n/firstlook - вид от первого лица");
	ShowPlayerDialogEx(playerid, BACKCMD_DIALOG, DIALOG_STYLE_MSGBOX, "CAR HELP - наберите команду для информации", listitems, "OK", "Назад");
}
stock OtherCMD(playerid)
{
	new dlgitem[607];
	strcat(dlgitem, "\n/pay - передать наличные деньги другому игроку");
	strcat(dlgitem, "\n/contract - Заказать у киллера человека за указанную сумму");
	strcat(dlgitem, "\n/votekick - проголосовать за кик игрока при отсутствии администраторов на сервере");
	//strcat(dlgitem, "\n/votemode - проголосовать за ДМ режим: RealWar");
	strcat(dlgitem, "\n/question - задать вопрос по игре Хелперам");
	strcat(dlgitem, "\n/report - пожаловаться на читера Модераторам");
	strcat(dlgitem, "\n/fix radio - включить радио в машине если оно вдруг пропало");
	strcat(dlgitem, "\n/charity - убрать с экрана  деньги добавленные читом");
	strcat(dlgitem, "\n/id - узнать ид игрока по части ника");
	strcat(dlgitem, "\n/score - показать распределение очков");
	strcat(dlgitem, "\n/firstlook - вид от первого лица");
	strcat(dlgitem, "\n/sound - прослушать звуки GTA");
	//strcat(dlgitem, "\n/ad - рекламировать что-либо. Не рекламируйте глупые вещи! Реклама платная");
	//strcat(dlgitem, "\n/givekey - доверить ключи игроку от личного автомобиля");
	ShowPlayerDialogEx(playerid, BACKCMD_DIALOG, DIALOG_STYLE_MSGBOX, "*** OTHER COMMANDS ***", dlgitem, "OK", "Назад");
}


stock LeaderCMD(playerid)
{
    if(PlayerInfo[playerid][pLeader] >= TEAM_GROVE || (PlayerInfo[playerid][pMember] >= TEAM_GROVE && PlayerInfo[playerid][pRank] == 12))
    {
		new dlgitem[445+201+233+70] = "/invite - взять игрока во фракцию\
\n/uninvite - уволить игрока из фракции\
\n/giverank - дать доступный ранг\
\n/ranks - посмотреть Online игроков фракции\
\n/check - посмотреть статистику своего члена фракции\
\n/familymoney - касса фракции\
\n/familyrank - максимальный ранг для автопрокачки\
\n/blacklist - добавить в чёрный список\
\n/removeblacklist - удалить из чёрного списка\
\n/recon(/uncon) - следить за членами своей фракции";

		strcat(dlgitem, "\n/opencompany - создать клан\
\n/closecompany - удалить клан\
\n/slogan - лозунг партии\
\n/enterclan - войти в клан\
\n/exitclan - выйти из клана\
\n/clanmoney - касса клана\
\n/clan - чат клана");

		strcat(dlgitem, "\nНе забываем, что вы должны: 1. иметь микрофон,\
\n2. быть в TeamSpeak,\n3. писать на форуме в своей теме фракции \
\nкаждую неделю объявление о наборе.\
\nПри не выполнении данных условий,\nгейм-админ вас может снять с должности\
\nДля получения 6+ ранга во фракциях необходимо иметь ник Имя_Фамилия");
		ShowPlayerDialogEx(playerid, BACKCMD_DIALOG, DIALOG_STYLE_MSGBOX, "* LEADER HELP * наберите команду для информации", dlgitem, "OK", "Назад");
	}
	else SendClientMessage(playerid, COLOR_GREY, "   Вы не Лидер!");
}

stock gencommands_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if(dialogid != COMMANDS_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response)
	{
		command_help(playerid);
		return 1;
	}
	//new msgitem[256+1];
	if(listitem == 0)///stats
	{
	    SetPVarInt(playerid, "gDocuments", 0);
		OnPlayerShowStats(playerid, playerid);
	}
	else if(listitem == 1)///spawnchange
	{
		family_spawnchange(playerid);
	}
	else if(listitem == 2)///givegun
	{
        if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
        {
	        GeneralCMD(playerid); SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на оружие!");
		    return 1;
        }
		if( IsAFamilyMember(playerid) || IsAGangs(playerid) )
		{
			if(PlayerInfo[playerid][pLocal] == 243 || PlayerInfo[playerid][pLocal] == 244)
			{
				if(!GetPVarInt(playerid, "gGetHomeWeapon"))
		        {
					OnPlayerSetDutyWeapons(playerid);//запускаем ф-ию установки оружия
				}
				else { GeneralCMD(playerid); SendClientMessage(playerid, COLOR_GREY, "   Вы уже взяли оружие !"); }
				return 1;
			}
		}
		if(PlayerInfo[playerid][pHouse] != NOT_KEY)
		{
			new hkey = PlayerInfo[playerid][pHouse];
			if(IsPlayerInRangeOfPoint(playerid, 12.0, HouseInfo[hkey][hExitX], HouseInfo[hkey][hExitY], HouseInfo[hkey][hExitZ]))
			{
				if(!GetPVarInt(playerid, "gGetHomeWeapon"))
		        {
					OnPlayerSetHomeWeapons(playerid);//запускаем ф-ию установки оружия
				}
				else { GeneralCMD(playerid); SendClientMessage(playerid, COLOR_GREY, "   Вы уже взяли оружие !!"); }
				return 1;
			}
		}
		SendClientMessage(playerid, COLOR_GREY, "   Взять оружие из шкафчика можно только в доме 1 раз!"); //return 1; }
	}
	else if(listitem == 3)//	/show
	{
		CMD_show(playerid);
	}
	/*else if(listitem == 4)//	/changepass
	{
		if(GetPVarInt(playerid, "PasswordHasEdited") == getdate() && PlayerInfo[playerid][pAdmin] < 5)
		{
			format(msgitem, sizeof(msgitem), "CEPBEP: {33AA33}playerid:%d уже сегодня производил отправку пароля. Нельзя так часто менять пароль!", playerid);
			SendClientMessage(playerid, COLOR_RED, msgitem);
			GeneralCMD(playerid);
			return 1;
		}
		new dlgitem[93+24];
	    format(dlgitem, sizeof(dlgitem), "{FFFFFF}%s{A9C4E4}\nПожалуйста, придумайте \nлегко запоминаемый пароль \nи введите его ниже:", PlayerName(playerid));
		ShowPlayerDialogEx(playerid, CHANGEPASS_DIALOG, DIALOG_STYLE_INPUT, "Смена пароля", dlgitem, "Change", "");//RegistrationSTEP16
	}
	else if(listitem == 5)//	/changeorigin
	{
		if(PlayerInfo[playerid][pAdmin] != 9 && PlayerInfo[playerid][pAccount] == 0)
		{
			GeneralCMD(playerid); SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
			return 1;
		}
	    format(msgitem, sizeof(msgitem), "CEPBEP: {800000}Какой Ваш Областной Центр (Страна) %s? Please enter your Origin:", PlayerName(playerid));
		SendClientMessage(playerid, COLOR_YELLOW, msgitem);
    	new listitems[160+142+127+85] = "{FFFFFF}1\t{00FF00}Минск\n{FFFFFF}2\t{00FF00}Гродно\n{FFFFFF}3\t{00FF00}Гомель\n{FFFFFF}4\t{00FF00}Могилёв\n{FFFFFF}5\t{00FF00}Витебск\n{FFFFFF}6\t{00FF00}Брест";
		strcat(listitems, "\n{FFFFFF}7\t{00FF00}Россия\n{FFFFFF}8\t{00FF00}Украина\n{FFFFFF}9\t{00FF00}Литва\n{FFFFFF}10\t{00FF00}Латвия\n{FFFFFF}11\t{00FF00}Эстония");
		strcat(listitems, "\n{FFFFFF}12\t{00FF00}Молдова\n{FFFFFF}13\t{00FF00}Болгария\n{FFFFFF}14\t{00FF00}Казахстан\n{FFFFFF}15\t{00FF00}Башкирия");
		strcat(listitems, "\n{FFFFFF}16\t{00FF00}Израиль\n{FFFFFF}17\t{00FF00}Италия\n{FFFFFF}18\t{00FF00}Германия");
		ShowPlayerDialogEx(playerid, 4, DIALOG_STYLE_LIST, "3/4. Регистрация", listitems, "OK", "Cancel");
	}
	else if(listitem == 6)//	/info
	{
	    ServerInfo(playerid);
	}*/
	return 1;
}
stock backcmd_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != BACKCMD_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response)
	{
		command_help(playerid);
		return 1;
	}
	PlaySoundForPlayer(playerid, 5202);
	return 1;
}
//==============================================================================

//для экономики
stock HireCost(carid)//вызывается по команде /rentcar
{   //возвращает цену на арндованную тачку
	if(carid == RentCar[0]) return 950;//Rent car Infernus
	else if(carid == RentCar[1]) return 1050;//Rent car Bullet
	else if(carid == RentCar[2]) return 350;//Rent car Comet
	else if(carid == RentCar[3]) return 450; //Rent car Banshee
	else if(carid == RentCar[4]) return 950; //Rent car Turismo
	else if(carid == RentCar[5]) return 1050; //Rent car Cheetah
	else if(RentCar[6] <= carid <= RentCar[11]) return 150; //Rent car kart
	return 0;
}

stock Lotto(number)//Ф-ция вызывается после startlotto
{
	new JackpotFallen = 0;
	//new strings[MAX_STRING];
	new winner[MAX_PLAYER_NAME];
	format(strings, sizeof(strings), "Lottery News: Сегодня выигрышный номер: %d.", number);
    SendClientMessageToAll(COLOR_RED, strings);
    for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
	    if(PlayerInfo[i][pLottoNr] > 0)
	    {
		    if(PlayerInfo[i][pLottoNr] == number)
		    {
		        JackpotFallen = 1;
		        GetPlayerName(i, winner, sizeof(winner));
				format(strings, sizeof(strings), "Lottery News: %s взял Jackpot в $%d со своим Лоторейным Билетом под номером %d.", winner, Jackpot, PlayerInfo[i][pLottoNr]);
				SendClientMessageToAll(COLOR_LIGHTBLUE, strings);
				format(strings, sizeof(strings), "Lottery News: Bы Выйграли $%d с вашим Лотерейным Билетом под номером %d.", Jackpot, PlayerInfo[i][pLottoNr]);
				SendClientMessage(i, COLOR_LIGHTBLUE, strings);
				GivePlayerMoneyB(fjackpot, i, Jackpot);
		    }
		    else SendClientMessage(i, COLOR_GREY, "Lottery News: Вы не выйграли сейчас, может повезёт потом.");
		}
		PlayerInfo[i][pLottoNr] = 0;//обнуляем после розыгрыша
	}
	if(JackpotFallen == 1)
	{
	    new rand = 2500+random(25000);//для экономики
	    Jackpot = rand;
	    format(strings, sizeof(strings), "Lottery News: Назначен Новый Jackpot: $%d.", Jackpot);
	}
	else
	{
	    new rand = 150+random(1500); //для экономики
	    Jackpot += rand;
	    format(strings, sizeof(strings), "Lottery News: Jackpot поднят до $%d.", Jackpot);
	}
	SendClientMessageToAll(COLOR_YELLOW, strings);
	SaveSettingsSQL();
	return 1;
}

stock JoinChannel(playerid, number, const irc_pass[])//вызывается по команде /irc join
{
	if(IsPlayerConnected(playerid))
	{
		if(!strcmp(IRCInfo[number][iPassword], irc_pass, true))
		{
			JoinChannelNr(playerid, number);
		}
	    else
	    {
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {800000}Неверный пароль !");
		}
	}
}
//для IRC
stock JoinChannelNr(playerid, number)//вызывается по команде /irc и из ф-ии JoinChannel
{
	if(IsPlayerConnected(playerid))
	{
	    //new strings[MAX_STRING];
		if(PlayersChannel[playerid] < MAX_PLAYERS-1)
	    {
			format(strings, sizeof(strings), "* %s вышел с канала.", PlayerName(playerid));
			SendIRCMessage(PlayersChannel[playerid], COLOR_GREEN, strings);
			IRCInfo[PlayersChannel[playerid]][iPlayers] -= 1;
	    }
		new channel = number;
		channel += 1;
	    PlayersChannel[playerid] = number;
	    IRCInfo[PlayersChannel[playerid]][iPlayers] += 1;
		if(!strcmp(IRCInfo[number][iAdmin],PlayerName(playerid), true))
		{
		    format(strings, sizeof(strings), "* Bы вошли на IRC канал %d, как Администратор.", channel);
			SendClientMessage(playerid, COLOR_YELLOW, strings);
		}
		else
		{
		    format(strings, sizeof(strings), "* Bы присоединились к каналу IRC %d, Администратор: %s.", channel, IRCInfo[number][iAdmin]);
			SendClientMessage(playerid, COLOR_YELLOW, strings);
		}
		format(strings, sizeof(strings), "MOTD: %s.", IRCInfo[number][iMOTD]);
		SendClientMessage(playerid, COLOR_YELLOW, strings);
		format(strings, sizeof(strings), "* %s присоединился к каналу.", PlayerName(playerid));
		SendIRCMessage(number, COLOR_GREEN, strings);
	}
	return 1;
}

//##############################################################################//
//            ВЫПОЛНЯЮТСЯ ПРИ ВВОДЕ КОМАНДЫ ИЗ OnPlayerCommandText()            //
//##############################################################################//





stock CMD_givegun(playerid, giveplayerid)
{
	new strcmd[MAX_STRING];
	if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
	{
       	playerselect_OnPlayerClick(playerid, giveplayerid);
        SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на оружие!");
	    return 1;
	}
    if(giveplayerid == playerid)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете передать оружие самому себе !");
		return 1;
	}
    if( !IsPlayerConnected(giveplayerid) )
	{
		format(strcmd, sizeof(strcmd), "   ID:%d отсутствует на сервере.", giveplayerid);
		SendClientMessage(playerid, COLOR_GREY, strcmd);
		return 1;
	}
	if(!IsPlayerInRangeOfPlayer(8.0, playerid, giveplayerid)
		|| spectateid[playerid] != MAX_PLAYERS-1 || spectateid[giveplayerid] != MAX_PLAYERS-1)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не рядом с Вами !");
		return 1;
	}
	if(PlayerInfo[giveplayerid][pGunLic] != 1 && !gRealWar)
	{
		SendClientMessage(playerid, COLOR_GREY, "   У игрока отсутствует лицензия на оружие!");
		return 1;
	}
	if(IsPlayerInAnyVehicle(giveplayerid))
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете передать оружие игроку в транспорте !");
		return 1;
	}
    if(	(PlayerInfo[playerid][pMember] >= DoT && PlayerInfo[playerid][pMember] <= DoD)
		// || (PlayerInfo[playerid][pMember] >= LCN && PlayerInfo[playerid][pMember] <= DoJ)
	  )
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете передать бесплатное оружие !");
		return 1;
	}
    if(gInTerrorsCount[playerid] || gInCTerrorsCount[playerid])
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете передавать оружие, находясь в Paintbal'е!");
		return 1;
	}
	new weaponid = GetPlayerWeapon(playerid);
	if(LastAmmo[playerid][weaponid] < 1)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете передать оружие c кол-ом патронов меньше 1 !");
		return 1;
	}
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if(WantedPoints[playerid] > 6) break;
		if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
		if(i == playerid) continue;
		if(spectateid[i] != MAX_PLAYERS-1) continue;
	    if(!IsACop(i)) continue;
	    if(!gOnDuty[i]) continue;
	    //if( !IsPlayerInAnyVehicle(i) ) continue;
		//if( !IsInCopCar(nCarID[i]) ) continue;
		//if(nCarID[playerid] == nCarID[i]) continue;//если игрок не сидит в машине полицмена
		if(	!IsPlayerInRangeOfPlayer(60.0, playerid, i) ) continue;
   	    WantedPoints[playerid] += 6;
		SetPlayerCriminal(FBI, playerid, i, " Незаконные действия в отношении огнестрельного оружия");
		SendTeamMessage(FBI, COLOR_DARKTURQUOISE, "   USE: /pun [295] [1-3] [playerid/PartOfName]");
   	    break;
	}
	format(strcmd, sizeof(strcmd), "   Bы передали %s'у %s c %d патронами.", PlayerName(giveplayerid), WeaponName(weaponid), LastAmmo[playerid][weaponid]);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);
	format(strcmd, sizeof(strcmd), "   Bы получили от %s'а %s c %d патронами.", PlayerName(playerid), WeaponName(weaponid), LastAmmo[playerid][weaponid]);
	SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, strcmd);

	GivePlayerWeaponEx(giveplayerid, LastWeapon[playerid], LastAmmo[playerid][LastWeapon[playerid]]);
	RemovePlayerWeaponEx(playerid, LastWeapon[playerid]);//GetPlayerWeapon(playerid)
	return 1;
}

stock CMD_check(playerid, playername[])
{
//new cmd[20], idx, tmp[MAX_STRING], gMessage[MAX_STRING];

		new giveplayerid;
		new strcmd[MAX_STRING];
		giveplayerid = ReturnUser(playername);

		/*if(giveplayerid == playerid)// && !IsPlayerNPC(giveplayerid)
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /check [playerid/PartOfName]");
			return 1;
		}*/
		if( IsPlayerConnectedEx(giveplayerid) )
		{
		    if( PlayerInfo[playerid][pAdmin] < 1 && (PlayerInfo[giveplayerid][pMember] != PlayerInfo[playerid][pMember])
				&& PlayerInfo[playerid][pMember] != DoJ && PlayerInfo[playerid][pAdmin] < 1)
		    {
				SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не является членом вашей организации !");
				return 1;
			}
    		SetPVarInt(playerid, "gDocuments", 0);
			OnPlayerShowStats(playerid, giveplayerid);
			return 1;
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не присоединился к игре !");
			//mysql_real_escape_string(playername, playername);
			if(CheckExistPlayer(playerid, playername) == 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Это имя не зарегистрировано или указано не верно !");
				return 1;
			}
			new ToBase[50+MAX_PLAYER_NAME];
			format(ToBase, sizeof(ToBase), "SELECT * FROM `players` WHERE `Name` = '%s' LIMIT 1", playername);
			mysql_query(ToBase);// - делаем запрос
			mysql_store_result();// - получаем результат.
			if(mysql_num_rows() > 0)
			{
		   		giveplayerid = MAX_PLAYERS-2;
				if(mysql_retrieve_row()) OnPlayerLoadParameters(giveplayerid, playername);//загружаем данные в массив MAX_PLAYERS-2
			}
			mysql_free_result();

		    if( (PlayerInfo[giveplayerid][pMember] != PlayerInfo[playerid][pMember])
				&& PlayerInfo[playerid][pMember] != DoJ && PlayerInfo[playerid][pAdmin] < 1)
		    {
				SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не является членом вашей организации !");
				return 1;
			}
			format(strcmd, sizeof(strcmd), "*** %s ***____________________________________________________________________________", playername);
			SendClientMessage(playerid, COLOR_GREEN, strcmd);
    		SetPVarInt(playerid, "gDocuments", 2);
			OnPlayerShowStats(playerid, giveplayerid);
			OnPlayerInit(giveplayerid);
		}
		return 1;
}
stock CMD_skydive(playerid, giveplayerid, height)
{
		new strcmd[MAX_STRING];
	    if( !IsPlayerConnected(giveplayerid) )
		{
			format(strcmd, sizeof(strcmd), "   ID:%d отсутствует на сервере.", giveplayerid); SendClientMessage(playerid, COLOR_GREY, strcmd);
			return 1;
		}
	    if(PlayerInfo[playerid][pJailed] > 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Этого игрока нельзя в данный момент подкинуть !");
			return 1;
		}
		new Float:rx, Float:ry, Float:rz;
		GetPlayerPos(giveplayerid, rx, ry, rz);
		GivePlayerWeaponEx(giveplayerid, 46, 0);
		SetPlayerPosEx(giveplayerid, rx,ry,rz+height, 0);

		format(strcmd, sizeof(strcmd), "AdmCmd: %s has sent %s on height %d m.", PlayerName(playerid), PlayerName(giveplayerid), height);
	//Log(ADMINLOG, strcmd);
		SendClientMessage(giveplayerid, COLOR_RED, strcmd);
		SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strcmd, 5);
		return 1;
}
stock CMD_fourdive(playerid, giveplayerid, height)
{
		new strcmd[MAX_STRING];
	    if( !IsPlayerConnected(giveplayerid) )
		{
			format(strcmd, sizeof(strcmd), "   ID:%d отсутствует на сервере.", giveplayerid); SendClientMessage(playerid, COLOR_GREY, strcmd);
			return 1;
		}
	    if(PlayerInfo[playerid][pJailed] > 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Этого игрока нельзя в данный момент подкинуть !");
			return 1;
		}
		new Float:rx, Float:ry, Float:rz;
		GetPlayerPos(giveplayerid, rx, ry, rz);
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			if(!IsPlayerInRangeOfPoint(i, 30.0, rx, ry, rz)) continue;
			GivePlayerWeaponEx(i, 46, 0);
			new randX = random(10);
			new randY = random(10);
			SetPlayerPosEx(i, rx+randX,ry+randY,rz+height, 0);
			//SetPlayerInteriorEx(i, 0);

			format(strcmd, sizeof(strcmd), "AdmCmd: %s has sent %s on height %d m.", PlayerName(playerid), PlayerName(i), height);
			//Log(ADMINLOG, strcmd);
			SendClientMessage(i, COLOR_RED, strcmd);
		}
		GivePlayerWeaponEx(playerid, 46, 0);
		SetPlayerPosEx(playerid, rx,ry,rz+height, 0);
		SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strcmd, 5);
		return 1;
}
stock CMD_slap(playerid, giveplayerid)
{
		new strcmd[MAX_STRING];
	    if( !IsPlayerConnected(giveplayerid) )
		{
			format(strcmd, sizeof(strcmd), "   ID:%d отсутствует на сервере.", giveplayerid); SendClientMessage(playerid, COLOR_GREY, strcmd);
			return 1;
		}
       	if(IsPlayerInAnyVehicle(giveplayerid) || GetPlayerInterior(giveplayerid) != 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Игрок должен находится Не в Машине и Не в Интерьере!");//
			return 1;
		}
		new Float:slx, Float:sly, Float:slz;
		GetPlayerHealth(giveplayerid, LastHealth[giveplayerid]);
		GetPlayerPos(giveplayerid, slx, sly, slz);
		SetPlayerPos(giveplayerid, slx, sly, slz+5.0);
		PlayerPlaySound(giveplayerid, SOUND_PUNCH_PED, slx, sly, slz+5.0);
		PlaySoundForPlayer(playerid, SOUND_SLAP);//Хлопок по попе

		format(strcmd, sizeof(strcmd), "   Вы были шлёпнуты %s'ом (LastHealth: %.1f)", PlayerName(playerid), LastHealth[giveplayerid]);
		SendClientMessage(giveplayerid, COLOR_GREY, strcmd);

		format(strcmd, sizeof(strcmd), "AdmCmd: %s[%d] был шлёпнут %s'ом (LastHealth: %.1f)", PlayerName(giveplayerid), giveplayerid, PlayerName(playerid), LastHealth[giveplayerid]);
		SendAllAdminMessage(COLOR_RED, strcmd, 1);
		return 1;
}

stock CMD_ban(playerid, giveplayerid, giveplayername[], days, inputtext[])
{
		new strcmd[MAX_STRING];
		if(IsPlayerConnected(giveplayerid))
		{
			if(PlayerInfo[playerid][pAdmin] < 5 && PlayerInfo[giveplayerid][pAdmin] > 0)
			{
			    SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены наказывать админов !");
			    return 1;
			}
			PlayerInfo[giveplayerid][pWarns] = getdate() + days;//Получает текущий день в году
			BanList(PlayerName(playerid), giveplayerid, PlayerInfo[giveplayerid][pWarns], inputtext);
			PlayerInfo[giveplayerid][pLevel] = -999;

			format(strcmd, sizeof(strcmd), "AdmCmd: %s был забанен %s'ом на %d дней, причина: %s", PlayerName(giveplayerid), PlayerName(playerid), days, inputtext);
			//Log(BAN,strcmd);
			new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
			format(strcmd, sizeof(strcmd), "{AFAFAF}[%d:%02d:%02d] {FF0000}%s", lH,lM,lS, strcmd);
			SendClientMessageToAll(COLOR_RED, strcmd);
			IsKicked[giveplayerid] = 1;
		}
	    else if( !IsPlayerConnected(giveplayerid) && giveplayerid != playerid)
	    {
			SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не присоединился к игре !");
			if(CheckExistPlayer(playerid, giveplayername) == 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Это имя не зарегистрировано или указано не верно !");
				return 1;
			}
			giveplayerid = MAX_PLAYERS-2;
			new ToBase[364];//144 + 24 + 1+2 + 16 + 12+10 + 24 + 128 + 3 = 364
			new Field[20];
			format(ToBase, sizeof(ToBase), "SELECT `IP`,`Level`,`AdminLevel` FROM `players` WHERE `Name`='%s' LIMIT 1", giveplayername);
			mysql_query(ToBase); mysql_store_result();
			if(mysql_num_rows() > 0)
			{
				if(mysql_retrieve_row())
				{
					mysql_fetch_field_row(PlayerInfo[giveplayerid][pIP], "IP");
					mysql_fetch_field_row(Field, "Level"); PlayerInfo[giveplayerid][pLevel] = strval(Field);
					mysql_fetch_field_row(Field, "AdminLevel"); PlayerInfo[giveplayerid][pAdmin] = strval(Field);
				}
			}
		    if(PlayerInfo[giveplayerid][pLevel] == -999)
			{
				mysql_free_result();
				SendClientMessage(playerid, COLOR_GREY, "   Указанный игрок уже забанен !");
				return 1;
			}
			if(PlayerInfo[playerid][pAdmin] < 5 && PlayerInfo[giveplayerid][pAdmin] > 0)
			{
			    SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены наказывать админов !");
			    return 1;
			}
			mysql_free_result();

			//new ToBase[81 + 3+3+MAX_PLAYER_NAME];
			format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Level`=-999, `Warns`=%d  WHERE `Name` = '%s'",
				getdate() + days,  giveplayername);
			mysql_query(ToBase);
			//------------------------------------------------------------------
			PlayerInfo[giveplayerid][pWarns] = getdate() + days;//Получает текущий день в году

//BanList(PlayerName(playerid), giveplayerid, PlayerInfo[giveplayerid][pWarns], strtmp);
			new date[12], time[10];
			new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
			new ly, lmm, ld; getdate(ly,lmm,ld);
			format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
			format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

			//new ToBase[142 + 24 + 1+2 + 16 + 12+10 + 24 + 128 + 3];
			format(ToBase, sizeof(ToBase), "INSERT INTO `banlist` (Player,AdminLevel,`Level`,`IP`,`Date`,`Time`,Admin,Reason,Days) VALUES ('%s', %d, %d, '%s', '%s', '%s', '%s', '%s', %d)",
				giveplayername, PlayerInfo[giveplayerid][pAdmin], PlayerInfo[giveplayerid][pLevel],
				PlayerInfo[giveplayerid][pIP], date, time, PlayerName(playerid), inputtext, days);
			mysql_query(ToBase);
			//BanList(PlayerName(playerid), giveplayerid, PlayerInfo[giveplayerid][pWarns], strtmp);//только для онлайн
			PlayerInfo[giveplayerid][pLevel] = -999;
			//------------------------------------------------------------------
			format(strcmd, sizeof(strcmd), "AdmCmd: %s был забанен %s'ом на %d дней, причина: %s", giveplayername, PlayerName(playerid), days, inputtext);
			format(strcmd, sizeof(strcmd), "{AFAFAF}[%d:%02d:%02d] {FF0000}%s", lH,lM,lS, strcmd);
			SendClientMessageToAll(COLOR_RED, strcmd);

			OnPlayerInit(giveplayerid);
		}
		return 1;
}
stock CMD_warn(playerid, giveplayerid, giveplayername[], inputtext[])
{
		new strcmd[MAX_STRING];
		new days = BANTIME;
		if(IsPlayerConnected(giveplayerid))
		{
			if(PlayerInfo[playerid][pAdmin] < 5 && PlayerInfo[giveplayerid][pAdmin] > 0)
			{
			    SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены наказывать админов !");
			    return 1;
			}
			PlayerInfo[giveplayerid][pWarns] += 1;
			if(PlayerInfo[giveplayerid][pWarns] >= 3)
			{
				PlayerInfo[giveplayerid][pWarns] = getdate() + days;//Получает текущий день в году
				format(strcmd, sizeof(strcmd), "AdmCmd: %s был забанен %s'ом на "#BANTIME" дня, причина: %s(3 Warns)", PlayerName(giveplayerid), PlayerName(playerid), inputtext);
				//Log(BAN,strcmd);
				//new strtmp[];
				strcat(inputtext, "(3 Warns)", 128);
				BanList(PlayerName(playerid), giveplayerid, PlayerInfo[giveplayerid][pWarns], inputtext);
				PlayerInfo[giveplayerid][pLevel] = -999;

				new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
				format(strcmd, sizeof(strcmd), "[%d:%02d:%02d] {FF0000}%s", lH,lM,lS, strcmd);
				SendClientMessageToAll(COLOR_GREY, strcmd);
				IsKicked[giveplayerid] = 1;
				return 1;
			}
			format(strcmd, sizeof(strcmd), "Bы предупреждены %s'ом, причина: %s", PlayerName(playerid), inputtext);
			SendClientMessage(giveplayerid, ADMINS_MESSAGE_COLOR, strcmd);
			format(strcmd, sizeof(strcmd), "%s дал warn %s'у, причина: %s", PlayerName(playerid), PlayerName(giveplayerid), inputtext);
			//Log(WARN, strcmd);
			WarnList(PlayerName(playerid), giveplayerid, PlayerInfo[giveplayerid][pWarns], inputtext);
			SendAllAdminMessage(COLOR_RED, strcmd, 5);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, strcmd);
			//return 1;
		}
	    else if( !IsPlayerConnected(giveplayerid) && giveplayerid != playerid)
	    {
			SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не присоединился к игре !");
			if(CheckExistPlayer(playerid, giveplayername) == 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Это имя не зарегистрировано или указано не верно !");
				return 1;
			}
			giveplayerid = MAX_PLAYERS-2;
			new ToBase[364];//144 + 24 + 1+2 + 16 + 12+10 + 24 + 128 + 3 = 364
			new Field[20];
			format(ToBase, sizeof(ToBase), "SELECT `IP`,`Level`,`AdminLevel`,`Warns` FROM `players` WHERE `Name`='%s' LIMIT 1", giveplayername);
			mysql_query(ToBase); mysql_store_result();
			if(mysql_num_rows() > 0)
			{
				if(mysql_retrieve_row())
				{
					mysql_fetch_field_row(PlayerInfo[giveplayerid][pIP], "IP");
					mysql_fetch_field_row(Field, "Level"); PlayerInfo[giveplayerid][pLevel] = strval(Field);
					mysql_fetch_field_row(Field, "AdminLevel"); PlayerInfo[giveplayerid][pAdmin] = strval(Field);
					mysql_fetch_field_row(Field, "Warns"); PlayerInfo[giveplayerid][pWarns] = strval(Field);
				}
			}
		    if(PlayerInfo[giveplayerid][pLevel] == -999)
			{
				mysql_free_result();
				SendClientMessage(playerid, COLOR_GREY, "   Указанный игрок уже забанен !");
				return 1;
			}
			if(PlayerInfo[playerid][pAdmin] < 7 && PlayerInfo[giveplayerid][pAdmin] > 0)
			{
			    SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены наказывать админов !");
			    return 1;
			}
			mysql_free_result();

			PlayerInfo[giveplayerid][pWarns] += 1;
			if(PlayerInfo[giveplayerid][pWarns] >= 3)
			{
				//new ToBase[81 + 3+3+MAX_PLAYER_NAME];
				format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Level`=-999, `Warns`=%d  WHERE `Name` = '%s'",
					getdate() + days,  giveplayername);
				mysql_query(ToBase);
				//------------------------------------------------------------------
				PlayerInfo[giveplayerid][pWarns] = getdate() + days;//Получает текущий день в году

	//BanList(PlayerName(playerid), giveplayerid, PlayerInfo[giveplayerid][pWarns], strtmp);
				new date[12], time[10];
				new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
				new ly, lmm, ld; getdate(ly,lmm,ld);
				format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
				format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

				//new ToBase[142 + 24 + 1+2 + 16 + 12+10 + 24 + 128 + 3];
				format(ToBase, sizeof(ToBase), "INSERT INTO `banlist` (Player,AdminLevel,`Level`,`IP`,`Date`,`Time`,Admin,Reason,Days) VALUES ('%s', %d, %d, '%s', '%s', '%s', '%s', '%s', %d)",
					giveplayername, PlayerInfo[giveplayerid][pAdmin], PlayerInfo[giveplayerid][pLevel],
					PlayerInfo[giveplayerid][pIP], date, time, PlayerName(playerid), inputtext, PlayerInfo[giveplayerid][pWarns]);
				mysql_query(ToBase);
				//BanList(PlayerName(playerid), giveplayerid, PlayerInfo[giveplayerid][pWarns], strtmp);//только для онлайн
				PlayerInfo[giveplayerid][pLevel] = -999;
				//------------------------------------------------------------------
				format(strcmd, sizeof(strcmd), "AdmCmd: %s был забанен %s'ом на %d дней, причина: %s(3 Warns)", giveplayername, PlayerName(playerid), days, inputtext);
				format(strcmd, sizeof(strcmd), "{AFAFAF}[%d:%02d:%02d] {FF0000}%s", lH,lM,lS, strcmd);
				SendClientMessageToAll(COLOR_RED, strcmd);
			}
			else
			{
				format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Warns`=`Warns`+1  WHERE `Name` = '%s'", giveplayername);
				mysql_query(ToBase);
			}
			format(strcmd, sizeof(strcmd), "%s дал warn %s'у, причина: %s", PlayerName(playerid), giveplayername, inputtext);
			Log(WARN, strcmd); SendAllAdminMessage(COLOR_RED, strcmd, 5);

			//------------------------------------------------------------------
			new date[12], time[10];
			new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
			new ly, lmm, ld; getdate(ly,lmm,ld);
			format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
			format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);
			//new ToBase[142 + 24 + 1+2 + 16 + 12+10 + 24 + 128 + 3];
			format(ToBase, sizeof(ToBase), "INSERT INTO `warnlist` (Player,AdminLevel,`Level`,`IP`,`Date`,`Time`,Admin,Reason,Days) VALUES ('%s', %d, %d, '%s', '%s', '%s', '%s', '%s', %d)",
				giveplayername, PlayerInfo[giveplayerid][pAdmin], PlayerInfo[giveplayerid][pLevel],
				PlayerInfo[giveplayerid][pIP], date, time, PlayerName(playerid), inputtext, PlayerInfo[giveplayerid][pWarns]);
			mysql_query(ToBase);
			//------------------------------------------------------------------

			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, strcmd);
			OnPlayerInit(giveplayerid);
		}
		return 1;
}
stock CMD_losewarn(playerid, giveplayerid, giveplayername[], inputtext[])
{
	new strcmd[MAX_STRING];
	if(IsPlayerConnected(giveplayerid))
	{
		if(PlayerInfo[giveplayerid][pWarns] < 1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Указанный игрок не имеет предупреждений, чтобы снять !");
			return 1;
		}
		if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "   Вы не можете снять Наказание с самого себя!"); return 1; }
		PlayerInfo[giveplayerid][pWarns] -= 1;
		format(strcmd, sizeof(strcmd), "%s снял warn с %s'а", PlayerName(playerid), PlayerName(giveplayerid));
		Log(WARN, strcmd); SendAllAdminMessage(COLOR_RED, strcmd, 5);
		SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, strcmd);
		return 1;
	}
    else if( !IsPlayerConnected(giveplayerid) && giveplayerid != playerid)
    {
		format(strcmd, sizeof(strcmd), "   ID:%d отсутствует на сервере.", giveplayerid);
		SendClientMessage(playerid, COLOR_GREY, strcmd);

		if(CheckExistPlayer(playerid, giveplayername) == 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Это имя не зарегистрировано или указано не верно !");
			return 1;
		}
		giveplayerid = MAX_PLAYERS-2;
		new ToBase[364];//144 + 24 + 1+2 + 16 + 12+10 + 24 + 128 + 3 = 364
		new Field[20];
		format(ToBase, sizeof(ToBase), "SELECT `Warns` FROM `players` WHERE `Name`='%s' LIMIT 1", giveplayername);
		mysql_query(ToBase); mysql_store_result();
		if(mysql_num_rows() > 0)
		{
			if(mysql_retrieve_row())
			{
				mysql_fetch_field_row(Field, "Warns"); PlayerInfo[giveplayerid][pWarns] = strval(Field);
			}
		}
	    if(PlayerInfo[giveplayerid][pWarns] <= 0)
		{
			mysql_free_result();
			SendClientMessage(playerid, COLOR_GREY, "   Указанный игрок не имеет предупреждений, чтобы снять !");
			return 1;
		}
		mysql_free_result();

		format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Warns`=`Warns`-1  WHERE `Name` = '%s'", giveplayername);
		mysql_query(ToBase);

		format(strcmd, sizeof(strcmd), "%s снял warn с %s'а, причина: %s", PlayerName(playerid), giveplayername, inputtext);
		Log(WARN, strcmd); SendAllAdminMessage(COLOR_RED, strcmd, 5);
		SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, strcmd);
		OnPlayerInit(giveplayerid);
    }
	return 1;
}
stock CMD_mute(playerid, giveplayerid, const inputtext[])
{
	new strcmd[MAX_STRING];
    if( !IsPlayerConnected(giveplayerid) )
	{
		format(strcmd, sizeof(strcmd), "   ID:%d отсутствует на сервере.", giveplayerid);
		SendClientMessage(playerid, COLOR_GREY, strcmd);
		return 1;
	}

	MenuOperation[playerid] = 160;
	SetPVarInt(playerid, "Action", 8);

	if(PlayerInfo[giveplayerid][pMuted] <= 0 || PlayerInfo[giveplayerid][pMuted] < GetTickCount())
	{//если игрок не заглушен
		//SendClientMessage(playerid, COLOR_GREY, "   Игрок не заглушен!");
		new minuts = strval(inputtext);
		//if(days < 1 || days > (365-getdate()) )
		if(minuts < 1 || minuts > 1440)
		{
			SetPVarInt(playerid, "InputCounter", 1);
			format(strcmd, sizeof(strcmd), "Введите кол-во минут [1-%d] наказания!!! \n\n\t{8CAA63}По окончанию ввода нажмите OK.",
				1440);
			ShowPlayerDialogEx(playerid, ADMINS_DIALOG, DIALOG_STYLE_INPUT, PlayerName(giveplayerid), strcmd, "OK", "Cancel");
			return 1;
		}

		PlayerInfo[giveplayerid][pMuted] = GetTickCount() + minuts*60*1000;//переводим минуты в милисекунды
		format(strcmd, sizeof(strcmd), "AdmCmd: %s был заглушен %s'ом на %d минут", PlayerName(giveplayerid), PlayerName(playerid), minuts);
		Log(CHAT,strcmd);
		//ABroadCast(COLOR_RED,strcmd,1);
		new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
		format(strcmd, sizeof(strcmd), "[%d:%02d:%02d] %s", lH,lM,lS, strcmd);
		SendClientMessageToAll(COLOR_RED, strcmd);
	}
	else //if(PlayerInfo[giveplayerid][pMuted] > getdate())
	{
		if(!strlen(inputtext))
		{//[days/0-off]
			SetPVarInt(playerid, "InputCounter", 1);
			format(strcmd, sizeof(strcmd), "%s был заглушен на %d минут.\n\
\nВведите 0 дней, \nчтобы снять наказание!!!! \n\n\t{8CAA63}По окончанию ввода нажмите OK.",
				PlayerName(giveplayerid), floatround( ((PlayerInfo[giveplayerid][pMuted]-GetTickCount())/1000.0)/60.0 )
				);//getDate(PlayerInfo[giveplayerid][pMuted]),
			ShowPlayerDialogEx(playerid, ADMINS_DIALOG, DIALOG_STYLE_INPUT, PlayerName(giveplayerid), strcmd, "OK", "Cancel");
			return 1;
		}
		new days = strval(inputtext);
		if(days != 0)
		{
			SetPVarInt(playerid, "InputCounter", 1);
			format(strcmd, sizeof(strcmd), "%s был заглушен на %d минут.\n\
\nЧисло не должно быть отлично от 0, \nчтобы снять наказание!!!!! \n\n\t{8CAA63}По окончанию ввода нажмите OK.",
				//PlayerName(giveplayerid), getDate(PlayerInfo[giveplayerid][pMuted]), 365-getdate());
				PlayerName(giveplayerid), floatround( ((PlayerInfo[giveplayerid][pMuted]-GetTickCount())/1000.0)/60.0 ));
			ShowPlayerDialogEx(playerid, ADMINS_DIALOG, DIALOG_STYLE_INPUT, PlayerName(giveplayerid), strcmd, "OK", "Cancel");
			return 1;
		}
		PlayerInfo[giveplayerid][pMuted] = 0;
		format(strcmd, sizeof(strcmd), "AdmCmd: %s был разглушен %s'ом", PlayerName(giveplayerid), PlayerName(playerid));
		Log(CHAT,strcmd);
		//ABroadCast(ADMINS_MESSAGE_COLOR,strcmd,1);
		new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
		format(strcmd, sizeof(strcmd), "[%d:%02d:%02d] %s", lH,lM,lS, strcmd);
		SendClientMessageToAll(COLOR_RED, strcmd);
	}
	return 1;
}
stock CMD_freeze(playerid, giveplayerid)
{
	new strcmd[MAX_STRING];
	if(IsPlayerControllable[giveplayerid] == 1)
	{
		//if(IsPlayerAttachedObjectSlotUsed(giveplayerid, CUFF_SLOT)) RemovePlayerAttachedObject(giveplayerid, CUFF_SLOT);
		//SetPlayerSpecialAction(giveplayerid, SPECIAL_ACTION_NONE);

		TogglePlayerControllableEx(giveplayerid, 1);

		/*PlayerCuffed[giveplayerid] = MAX_PLAYERS-1;
		PlayerCuffedTime[giveplayerid] = 0;
		PlayerTied[giveplayerid] = 0;
		PlayerTiedTime[giveplayerid] = 0;*/

		format(strcmd, sizeof(strcmd), "AdmCmd: %s defrosting %s's", PlayerName(giveplayerid), PlayerName(playerid));
  		Log(ADMINLOG, strcmd);
		SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strcmd, 4);
	}
	else
	{
		TogglePlayerControllableEx(giveplayerid, 0);//обездвиживает

		/*PlayerCuffed[giveplayerid] = MAX_PLAYERS-1;
		PlayerCuffedTime[giveplayerid] = 0;
		PlayerTied[giveplayerid] = 0;
		PlayerTiedTime[giveplayerid] = 0;*/

		format(strcmd, sizeof(strcmd), "AdmCmd: %s it is frozen %s's", PlayerName(giveplayerid), PlayerName(playerid));
  		Log(ADMINLOG, strcmd);
		SendAllAdminMessage(COLOR_RED, strcmd, 4);
	}
}

stock CMD_spectate(playerid, giveplayerid)
{
	new strcmd[MAX_STRING];
	if(GetPVarInt(playerid, "gSpectating") == 0)
	{
		//if(IsPlayerAttachedObjectSlotUsed(giveplayerid, CUFF_SLOT)) RemovePlayerAttachedObject(giveplayerid, CUFF_SLOT);
		//SetPlayerSpecialAction(giveplayerid, SPECIAL_ACTION_NONE);

		TogglePlayerSpectatingEx(giveplayerid, 1);//включаем режим спектатора
		
		//AttachCameraToPlayerObject(playerid, noclipdata[playerid][flyobject]);
        SetPlayerCameraPos(playerid, 1528.2993,-984.7744,100.2264);
		SetPlayerCameraLookAt(playerid, 1313.8358,-779.9300,89.8182, CAMERA_CUT);
		
		format(strcmd, sizeof(strcmd), "AdmCmd: %s ON spectatemode %s's", PlayerName(giveplayerid), PlayerName(playerid));
  		Log(ADMINLOG, strcmd);
		SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strcmd, 4);
	}
	else
	{
		TogglePlayerSpectatingEx(giveplayerid, 0);//выключаем режим спектатора

		format(strcmd, sizeof(strcmd), "AdmCmd: %s OFF spectatemode %s's", PlayerName(giveplayerid), PlayerName(playerid));
  		Log(ADMINLOG, strcmd);
		SendAllAdminMessage(COLOR_RED, strcmd, 4);
	}
}

stock CMD_jail(playerid, giveplayerid, time, camera)
{
		new strcmd[MAX_STRING];
		ResetPlayerWeaponsEx(giveplayerid);
		WantedPoints[giveplayerid] = 0;
		//WantLawyerTime[giveplayerid] = 0;//услуги адвоката не нужны
		if( (time < 60 || time > 180)
			&& !(PlayerInfo[playerid][pMember] == DoJ && PlayerInfo[playerid][pRank] == 8)
			&& PlayerInfo[playerid][pAdmin] != 3
			&& PlayerInfo[playerid][pAdmin] != 9)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете установить время меньше 60 минут или больше 180 !");
			return 1;
		}
		if(IsPlayerInArea(playerid, checkCoords[CP_LSPD]))
		{// Jail spot LSPD int6'
			PlayerInfo[giveplayerid][pJailed] = 1;
			SetPlayerInteriorEx(giveplayerid, 6);
   			new rand = camera;
			SetPlayerPosEx(giveplayerid, JailSpawnLS[rand][0],JailSpawnLS[rand][1],JailSpawnLS[rand][2], JailSpawnLS[rand][3]);
			SetPlayerWorldBoundsEx(giveplayerid, checkCoords[CP_LSPD][maxx], checkCoords[CP_LSPD][minx], checkCoords[CP_LSPD][maxy], checkCoords[CP_LSPD][miny]);
			SetPVarInt(giveplayerid, "gWorldBounds", 1);
		}
		else if(IsPlayerInArea(playerid, checkCoords[CP_SFPD]))
		{// Jail spot SFPD int10
			PlayerInfo[giveplayerid][pJailed] = 2;
			SetPlayerInteriorEx(giveplayerid, 10);
   			new rand = camera;
			SetPlayerPosEx(giveplayerid, JailSpawnSF[rand][0],JailSpawnSF[rand][1],JailSpawnSF[rand][2], JailSpawnSF[rand][3]);
			SetPlayerWorldBoundsEx(giveplayerid, checkCoords[CP_SFPD][maxx], checkCoords[CP_SFPD][minx], checkCoords[CP_SFPD][maxy], checkCoords[CP_SFPD][miny]);
			SetPVarInt(giveplayerid, "gWorldBounds", 1);
		}
		else if(IsPlayerInArea(playerid, checkCoords[CP_LVPD_UPFLOOR]) || IsPlayerInArea(playerid, checkCoords[CP_LVPD_DOWNFLOOR]))
		{// Jail spot LVPD int3
			PlayerInfo[giveplayerid][pJailed] = 3;
			SetPlayerInteriorEx(giveplayerid, 3);
   			new rand = camera;
			SetPlayerPosEx(giveplayerid, JailSpawnLV[rand][0],JailSpawnLV[rand][1],JailSpawnLV[rand][2], JailSpawnLV[rand][3]);
			SetPlayerWorldBoundsEx(giveplayerid, checkCoords[CP_LVPD_DOWNFLOOR][maxx], checkCoords[CP_LVPD_DOWNFLOOR][minx], checkCoords[CP_LVPD_DOWNFLOOR][maxy], checkCoords[CP_LVPD_DOWNFLOOR][miny]);
			SetPVarInt(giveplayerid, "gWorldBounds", 1);
		}
		else
		{
			PlayerInfo[giveplayerid][pJailed] = 3;
			SetPlayerInteriorEx(giveplayerid, 3);
   			new rand = camera;
			SetPlayerPosEx(giveplayerid, JailSpawnLV[rand][0],JailSpawnLV[rand][1],JailSpawnLV[rand][2], JailSpawnLV[rand][3]);
			SetPlayerWorldBoundsEx(giveplayerid, checkCoords[CP_LVPD_DOWNFLOOR][maxx], checkCoords[CP_LVPD_DOWNFLOOR][minx], checkCoords[CP_LVPD_DOWNFLOOR][maxy], checkCoords[CP_LVPD_DOWNFLOOR][miny]);
			SetPVarInt(giveplayerid, "gWorldBounds", 1);
		}
		PlayerInfo[giveplayerid][pJailTime] = time;//*60;
		format(strcmd, sizeof(strcmd), "* Вы Заключили в тюрьму %s'а на %d минут", PlayerName(giveplayerid), time);
		SendClientMessage(playerid, COLOR_BLUEGREY, strcmd);
		format(strcmd, sizeof(strcmd), "* Вы были Заключены в тюрьму %s'ом на %d минут.", PlayerName(playerid), time );
		SendClientMessage(giveplayerid, COLOR_BLUEGREY, strcmd);
		format(strcmd, sizeof(strcmd), "AdmCmd: %s has jailed %s's for %d minutes", PlayerName(playerid), PlayerName(giveplayerid), time);
		Log(ADMINLOG, strcmd);
	    //SetPlayerWorldBoundsEx(giveplayerid,20000.0000,-20000.0000,20000.0000,-20000.0000); //Reset world to player
	    return 1;
}
stock CMD_prison(playerid, giveplayerid, time)
{
		new strcmd[MAX_STRING];
		WantedPoints[giveplayerid] = 0;
		WantedLevel[giveplayerid] = 0;
		SetPlayerWantedLevel(giveplayerid, WantedLevel[giveplayerid]);//убрали звёзды
		PlayerInfo[giveplayerid][pJailed] = 10;
		PlayerInfo[giveplayerid][pJailTime] = time;//3600;
		if(PlayerInfo[giveplayerid][pSex] == Male) PlayerInfo[giveplayerid][pChar] = 62;//скин зэка
		SetPlayerPosEx(giveplayerid, 268.7055,1883.8724,-30.0938, 175.4435);
		format(strcmd, sizeof(strcmd), "* Вы поместили %s'а в Fort DeMorgan на %d минут.", PlayerName(giveplayerid), PlayerInfo[giveplayerid][pJailTime]);
		SendClientMessage(playerid, COLOR_BLUEGREY, strcmd);
		format(strcmd, sizeof(strcmd), "* Вы помещены в форт ДеМорган Админом %s'ом на %d минут.", PlayerName(playerid), PlayerInfo[giveplayerid][pJailTime]);
		SendClientMessage(giveplayerid, COLOR_BLUEGREY, strcmd);
		GameTextForPlayerEx(giveplayerid, "~w~Welcome to ~n~~r~Fort DeMorgan", 5000, 3);
		format(strcmd, sizeof(strcmd), "AdmCmd: %s has placed in fort DeMorgan %s's for %d minutes.", PlayerName(playerid), PlayerName(giveplayerid), PlayerInfo[giveplayerid][pJailTime]);
  		Log(ADMINLOG, strcmd);
		//SetPlayerWorldBoundsEx(giveplayerid, 337.5694,101.5826,1940.9759,1798.7453); //285.3481,96.9720,1940.9755,1799.0811
	    return 1;
}
stock CMD_kick(playerid, giveplayerid, inputtext[])
{
	new reason = strval(inputtext);
	new strtmp[64];
	if(reason == 1) strmid(strtmp, "реклама", 0, strlen("реклама"), 64);
	else if(reason == 2) strmid(strtmp, "оскорбления", 0, strlen("оскорбления"), 64);
	else if(reason == 3) strmid(strtmp, "флуд", 0, strlen("флуд"), 64);
	else if(reason == 4) strmid(strtmp, "ник", 0, strlen("ник"), 64);
	else if(reason == 5) strmid(strtmp, "бессмертие тачки", 0, strlen("бессмертие тачки"), 64);
	else if(reason == 6) strmid(strtmp, "пополнение жизни тачки", 0, strlen("пополнение жизни тачки"), 64);
	else if(reason == 7) strmid(strtmp, "АФК больше 5 минут", 0, strlen("АФК больше 5 минут"), 64);
	else if(reason == 8) strmid(strtmp, "бессмертие", 0, strlen("бессмертие"), 64);
	else if(reason == 9) strmid(strtmp, "пополнение брони", 0, strlen("пополнение брони"), 64);
	else if(reason == 10) strmid(strtmp, "пополнение жизни", 0, strlen("пополнение жизни"), 64);
	else if(reason == 11) strmid(strtmp, "использование телепортов в тачку", 0, strlen("использование телепортов в тачку"), 64);
	else if(reason == 12) strmid(strtmp, "бесконечные патроны", 0, strlen("бесконечные патроны"), 64);
	else if(reason == 13) strmid(strtmp, "стрельба без перезарядки", 0, strlen("стрельба без перезарядки"), 64);
	else if(reason == 14) strmid(strtmp, "использование телепортов", 0, strlen("использование телепортов"), 64);
	else if(reason == 15) strmid(strtmp, "чит денег", 0, strlen("чит денег"), 64);
	else if(reason == 16) strmid(strtmp, "airbag", 0, strlen("airbag"), 64);
	else if(reason == 17) strmid(strtmp, "использование макросов", 0, strlen("использование макросов"), 64);
	else strmid(strtmp, inputtext, 0, strlen(inputtext), 255);

	new strcmd[MAX_STRING];
	format(strcmd, sizeof(strcmd), "AdmCmd: %s был кикнут %s'ом, причина: %s", PlayerName(giveplayerid), PlayerName(playerid), strtmp);
	Log(KICK,strcmd);
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	format(strcmd, sizeof(strcmd), "[%d:%02d:%02d] %s", lH,lM,lS, strcmd);
	SendClientMessageToAll(COLOR_RED, strcmd);
	IsKicked[giveplayerid] = 1;
	return 1;
}





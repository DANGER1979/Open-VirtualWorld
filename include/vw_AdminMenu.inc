
stock AdminMenu(playerid, forplayerid)
{
	new caption[70+1];
    format(caption, sizeof(caption), "Вы выбрали игрока %s[%d]", PlayerName(forplayerid), forplayerid);

	new listitems[3500];
	strcat(listitems, "/admin(/a) - админ чат\
	\n/restart - рестарт сервера\
	\n/NPCrestart - рестарт ботов\
	\n/gate - откр/закр ворота\
	\n/open - откр/закр двери\
	\n/savesettings - сохранить настройки сервера\
	\n/savehouses - сохранить дома\
	\n/savebizz - сохранить бизы\
	\n/savesbizz - сохранить компании\
	\n/savefamilies - сохранить фракции\
	\n/savecars - сохранить тачки");
	
	strcat(listitems, "	\n/logout - сохранить данные игрока\
	\n/logoutall - сохранить данные всех игроков\
	\n/storehouse - отредактировать склад\
	\n/edit - отредактировать бизнес/компанию\
	\n/asellhouse - продать дом\
	\n/asellbiz - продать биз\
	\n/SPP - тп по координатам\
	\n/sethp /setarmour\
	\n/fw /bk /dn /up /lt /rt - сдвиг на 2м\
	\n/gotols /gotosf /gotolv - тп в город");

	strcat(listitems, "\n/makeleader - сделать лидером\
	\n/setfamily - установить банду/фракцию\
	\n/SetFamilyBank - установить кассу фракции\
	\n/setmaterial - установить кол. материалов\
	\n/setfamilymembers - откорректировать кол-во членов\
	\n/giveturf - выдать зону\
	\n/raspredturf - рандомно распределить все зоны\
	\n/setjob - установить работу\
	\n/setmoney - установить деньги на руках\
	\n/setvehhp - установить здоровье тачки");

	strcat(listitems, "\n/skydive - подбросить в небо игрока\
	\n/fourdive - подбросить всех вокруг игрока\
	\n/slap - пихнуть игрока\
	\n/warn - сделать предупреждение\
	\n/losewarn - снять предупреждение\
	\n/mute - заглушить/разглушить\
	\n/jail - посадить в камеру\
	\n/prison - посадить на зону\
	\n/kick - кикнуть игрока\
	\n/ban - забанить игрока\
	\n/banip - забанить по ip игрока\
	\n/qban - быстрый бан\
	\n/plremove - удалить учётную запись\
	\n/getdist - расстояние до игрока");

	strcat(listitems, "\n/resetneed - сбросить потребности\
	\n/setupgrade - установить улучшение\
	\n/setexp - установить опыт\
	\n/setbank - установить деньги на карточке\
	\n/givebank - дать денег на карточку\
	\n/setdeposit - установить размер депозита\
	\n/sethouse - установить ключи от дома\
	\n/setbizz - установить ключи от биза");

	strcat(listitems, "\n/setaccount - установить тип аккаунта\
	\n/setcontract - установить время контракта\
	\n/setstd - установить болезнь\
	\n/setwins - установить кол-во побед\
	\n/setloses - установить кол-во поражений\
	\n/setcrim - установить кол-во преступлений\
	\n/setarrested - установить кол-во аррестов\
	\n/clearwanted - очистить розыск\
	\n/setsex - установить пол\
	\n/nameoff - вкл/выкл ники игроков");

	if( strlen(listitems) > sizeof(listitems) )
	{
		format(strings, sizeof(strings), "AdmWarning: strlen(info):%d > sizeof(listitems):%d", strlen(listitems), sizeof(listitems));
		SendAllAdminMessage(COLOR_MAROON, strings, 3);
	 	return 1;
	}
	if( strlen(caption) > sizeof(caption) )
	{
		format(strings, sizeof(strings), "AdmWarning: strlen(caption):%d > sizeof(caption):%d", strlen(caption), sizeof(caption));
		SendAllAdminMessage(COLOR_MAROON, strings, 3);
	 	return 1;
	}
	ShowPlayerDialogEx(playerid, ADMIN_MENU_DIALOG, DIALOG_STYLE_LIST, caption, listitems, "Ок", "Назад");
	return 1;
}


stock AdminMenu_DialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	//#pragma unused listitem
	//#pragma unused inputtext
	if(dialogid != ADMIN_MENU_DIALOG) return 1;// && dialogid != H_DIALOG
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response)
	{
		DeletePVar(playerid, "Action");
		/*DeletePVar(playerid, "InputValue");
		DeletePVar(playerid, "InputCounter");
		DeletePVar(playerid, "ForPlayerID");*/
		new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
		admin_OnPlayerClick(playerid, giveplayerid);//PlayerMenu(playerid);
		return 1;
	}
	new msgitem[256+1];
	new Float:pX, Float:pY, Float:pZ, Float:pA; //new Float:ang;
	//new Float:vX, Float:vY, Float:vZ;//, Float:vA;
	new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
	/*if(!IsPlayerAdmin(playerid))
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
		return 1;
	}*/

	/*if(CHECKING == 1)
	{//ИНФОРМИРОВАНИЕ
	format(strings, sizeof(strings), "admin_OnDialogResponse(playerid:%d, giveplayerid:%d, \
Action:%d, InputCounter:%d) InputValue:%d",
playerid, giveplayerid,
GetPVarInt(playerid, "Action"), GetPVarInt(playerid, "InputCounter"), strval(inputtext));
GetPVarInt(playerid, "InputValue"), GetPVarInt(giveplayerid, "InputValue"));
	SendClientMessage(playerid, COLOR_PURPLE, strings);
	}*/
//==============================================================================
	if(GetPVarInt(playerid, "Action") == 0)
	{//если операция ещё не выбрана, т.е. это ввод первого параметра
	    //не забыть обнулить при окончанию ввода параметров
		//if(dialogid == DEVELOPER_DIALOG)
		SetPVarInt(playerid, "Action", listitem+1);//записали выбранную операцию
		//else  SetPVarInt(playerid, "Action", listitem+100);//записали выбранную операцию

		DeletePVar(playerid, "InputCounter");//очистили от предыдущих операций
	}
	new operation = GetPVarInt(playerid, "Action");
//------------------------------------------------------------------------------
	if(operation == 1)
	{

	}
	//==========================================================================
	else DeletePVar(playerid, "Action");
	GivePVarInt(playerid, "InputCounter", +1);//счётчик кол-ва входов в данную обработку
	//format(strings, sizeof(strings), "admin_OnDialogResponse(playerid:%d, giveplayerid:%d, Action:%d, InputCounter:%d)", playerid, giveplayerid, GetPVarInt(playerid, "Action"), GetPVarInt(playerid, "InputCounter") );
	//SendClientMessage(playerid, COLOR_GREEN, strings);
	return 1;
}



stock admin_OnPlayerCommandText(playerid, cmdtext[])
{
	new gMessage[MAX_STRING]; new strcmd[MAX_STRING]; new tmp[MAX_STRING];
	new cmd[20], idx, giveplayerid;
	cmd = strtok(cmdtext, idx);//Возвращает  аргумент номер которого указан в переменной &index
	if(!strcmp(cmd, "/admin", true) || !strcmp(cmd, "/a", true))
	{
        /*if(PlayerInfo[playerid][pAdmin] < 1)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
            return 1;
        }*/
		gMessage = strrest(cmdtext, idx);
		if(!strlen(gMessage) || strlen(gMessage) > 128-35)
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: (/a)dmin [admin chat]");
			return 1;
		}
		SendAdminsMessage(playerid, gMessage);
		PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
	}
	else if(!strcmp(cmd, "/restart", true))
	{
        //if(PlayerInfo[playerid][pAdmin] < 5)
        //{
         //   SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
        //    return 1;
        //}
 		/*tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			print("\n========================================================================");
			print("AdmCmd: GameMode Restart Begin");

			//CallLocalFunction("OnRemoteRestartServer", "si", PlayerName(playerid), 4);
			OnRemoteRestartServer(PlayerName(playerid), 4);
			return 1;
		}
		print("\n========================================================================");
		print("AdmCmd: GameMode Restart Begin");
		//CallLocalFunction("OnRemoteRestartServer", "si", PlayerName(playerid), strval(tmp));
		OnRemoteRestartServer(PlayerName(playerid), strval(tmp));*/

		GameModeExit();
	}
 	else if(!strcmp(cmd, "/NPCrestart", true) || !strcmp(cmd, "/NPCres", true))
	{
        if( //PlayerInfo[playerid][pAdmin] != 5 && PlayerInfo[playerid][pAdmin] != 6 &&//может крашить сервер
			PlayerInfo[playerid][pAdmin] != 9)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
            return 1;
        }
		//foreach(Bot, i)
		for(new i=0; i<GetMaxPlayers(); i++)
		{
			if( !IsPlayerConnected(i) ) continue;
			if( !IsPlayerNPC(i) ) continue;
			CallRemoteFunction("OnRemotePlayerSpawn", "i", i);//может крашить сервер
		}
		format(strcmd, sizeof(strcmd), "AdmCmd: %s рестартнул NPC транспорт.", PlayerName(playerid));
		SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strcmd, 5);
		//return 1;
	}
	else if(!strcmp(cmd, "/gate", true))//для ворот начало
	{
		gate_OnPlayerCommandText(playerid);
		//----------------------------------------------------------------------
       	if(IsPlayerInRangeOfPoint(playerid, 8.0, 211.6222,1811.9565,21.8594) ||
			IsPlayerInRangeOfPoint(playerid, 8.0, 246.4324,1861.1317,14.0840) )
       	{   //если ты возле одного из пультов
			if(PlayerInfo[playerid][pVirtual] != 0) return 1;
			if(PlayerInfo[playerid][pJailed] == 10)
	        {
	            SendClientMessage(playerid, COLOR_GREY, "   Вы не можете воспользоваться этой командой когда заключённый !");
		        return 1;
	        }
//1-КПП, 2-Вход в бункер, 3-Нижний Пульт, 4-Дверь туннеля, 5-Пропускной Пункт 2, 6-Офицерская комната, 7-Камера Заключённых, 8-Ракетная шахта, 9-Вентиляция, 10-Среднее КПП, 11-Заднее КПП
			tmp = strtok(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_WHITE, "/gate [number (1-11)(0 - All Close)]");
				SendClientMessage(playerid, COLOR_GREY, "1-КПП, 2-Вход в бункер, 3-Нижний Пульт, 4-Дверь туннеля, 5-Пропускной Пункт 2");
				SendClientMessage(playerid, COLOR_GREY, "6-Офицерская комната, 7-Камера Заключённых, 8-Ракетная шахта, 9-Вентиляция,");
				SendClientMessage(playerid, COLOR_GREY, "10-Среднее КПП, 11-Заднее КПП");
				return 1;
			}
			new number = strval(tmp);
			if(number < 0 || number > 11) {
				SendClientMessage(playerid, COLOR_GREY, "   Номер Ворот может быть 1-11(0 - All Close)");
				return 1;
			}
			if(number == 0)
			{//закрыть все ворота
       			if(!IsPlayerInRangeOfPoint(playerid, 8.0, 211.6222,1811.9565,21.8594))
		        {
		            SendClientMessage(playerid, COLOR_GREY, "   Закрыть все ворота можно только с верхнего пульта !");
			        return 1;
		        }
				if((GetTickCount() - GetPVarInt(playerid, "ChatTime")) < 10000)
				{
					SendClientMessage(playerid, COLOR_RED, "CEPBEP: {800000}Вы можете использовать команду только раз в 10 секунд.");
				    return 1;
				}

       			ApplyAnimation(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
				MoveObjectEx(oNGgate1,96.800,1921.0000,18.200, 1.0);
				gGateStatus[1] = 0;//закрыто
				//------------------------------------------------------
				MoveObjectEx(oNGgate2,213.9,1875.4,14.0, 0.5);
				gGateStatus[2] = 0;//закрыто
				//------------------------------------------------------
				MoveObjectEx(oNGgate3,238.45,1872.2806,10.6, 0.5);
				gGateStatus[3] = 0;//закрыто
				//------------------------------------------------------
				MoveObjectEx(oNGgate4,256.3,1843.6,9.6, 0.5);
				gGateStatus[4] = 0;//закрыто
				//------------------------------------------------------
				MoveObjectEx(oNGgate5,248.7,1841.9,8.2, 0.5);
				gGateStatus[5] = 0;//закрыто
				//------------------------------------------------------
				MoveObjectEx(oNGgate6,233.7,1823.0,6.8, 0.5);
				gGateStatus[6] = 0;//закрыто
				//------------------------------------------------------
				MoveObjectEx(oNGgate7,283.35,1869.5,9.5, 0.5);
				gGateStatus[7] = 0;//закрыто
				//------------------------------------------------------
				MoveObjectEx(oNGgate8,268.7,1864.0,8.5, 2.5);
				gGateStatus[8] = 0;//закрыто
				//------------------------------------------------------
				MoveObjectEx(oNGgate10,135.1046, 1941.5570, 21.7132, 2.5);
				gGateStatus[22] = 0;//закрыто
				//------------------------------------------------------
				MoveObjectEx(oNGgate11,286.0753, 1821.1231, 20.0406, 2.5);
				gGateStatus[23] = 0;//закрыто
				//------------------------------------------------------
				SendClientMessage(playerid, COLOR_YELLOW, "Все Ворота Военной базы закроются через 5 секунд");
				return 1;
			}
			else if(number == 1)
			{
			   	if(gGateStatus[1] == 0)
			   	{   //ворота на военную базу
					MoveObjectEx(oNGgate1,96.800,1924.600,18.200, 2.5);
					gGateStatus[1] = 1;//открыто
				}
			   	else
				{
					MoveObjectEx(oNGgate1,96.800,1921.0000,18.200, 1.0);
					gGateStatus[1] = 0;//закрыто
				}
			}
			else if(number == 2)
			{
			   	if(gGateStatus[2] == 0)
			   	{   //ворота на военную базу
					MoveObjectEx(oNGgate2,213.9,1875.4,10.0, 0.5);
					gGateStatus[2] = 1;//открыто
				}
			   	else
				{
					MoveObjectEx(oNGgate2,213.9,1875.4,14.0, 0.5);
					gGateStatus[2] = 0;//закрыто
				}
			}
			else if(number == 3)
			{
			   	if(gGateStatus[3] == 0)
			   	{   //ворота ко второй камере для наблюдений
					MoveObjectEx(oNGgate3,238.45,1872.2806,14.5, 0.5);
					gGateStatus[3] = 1;//открыто
				}
			   	else
				{
					MoveObjectEx(oNGgate3,238.45,1872.2806,10.6, 0.5);
					gGateStatus[3] = 0;//закрыто
				}
			}
			else if(number == 4)
			{
			   	if(gGateStatus[4] == 0)
			   	{   //большие ворота откр. изнутри
					MoveObjectEx(oNGgate4,256.3,1843.6,5.8, 0.5);
					gGateStatus[4] = 1;//открыто
				}
			   	else
				{
					MoveObjectEx(oNGgate4,256.3,1843.6,9.6, 0.5);
					gGateStatus[4] = 0;//закрыто
				}
			}
			else if(number == 5)
			{
			   	if(gGateStatus[5] == 0)
			   	{   //ворота рядом с большими откр. снаружи
					MoveObjectEx(oNGgate5,248.7,1841.9,12.1, 0.5);
					gGateStatus[5] = 1;//открыто
				}
			   	else
				{
					MoveObjectEx(oNGgate5,248.7,1841.9,8.2, 0.5);
					gGateStatus[5] = 0;//закрыто
				}
			}
			else if(number == 6)
			{
				if(PlayerInfo[playerid][pRank] < 7)
		        {
		            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту дверь !");
		            return 1;
		        }
			   	if(gGateStatus[6] == 0)
			   	{   //ворота в штаб
					MoveObjectEx(oNGgate6,233.7,1823.0,10.7, 0.5);
					gGateStatus[6] = 1;//открыто
				}
			   	else
				{
					MoveObjectEx(oNGgate6,233.7,1823.0,6.8, 0.5);
					gGateStatus[6] = 0;//закрыто
				}
			}
			else if(number == 7)
			{
			   	if(gGateStatus[7] == 0)
			   	{   //ворота на спаун зэков
					MoveObjectEx(oNGgate7,283.35,1869.5,12.5, 0.5);
					gGateStatus[7] = 1;//открыто
				}
			   	else
				{
					MoveObjectEx(oNGgate7,283.35,1869.5,9.5, 0.5);
					gGateStatus[7] = 0;//закрыто
				}
			}
			else if(number == 8)
	   		{ 	//CreateObjectEx(5856,268.7,1864.0,8.5,0.0,0.0,90.0);//ролеты на нижний уровень зоны
				if(PlayerInfo[playerid][pRank] < 7)
		        {
		            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту дверь !");
		            return 1;
		        }
			   	if(gGateStatus[8] == 0)
			   	{   //ворота на нижний уровень
					MoveObjectEx(oNGgate8,268.7,1864.0,12.3, 1.5);
					gGateStatus[8] = 1;//открыто
				}
			   	else
				{
					MoveObjectEx(oNGgate8,268.7,1864.0,8.5, 2.5);
					gGateStatus[8] = 0;//закрыто
				}
			}
			else if(number == 9)
			{   //дверь отстойника из камеры зоны 51
			   	if(gGateStatus[0] == 0)
			   	{
	        		ApplyAnimation(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
					SetObjectRot(oNGgate9, 0.0, 0.0, -90.0);
					PlaySoundForObject(oNGgate9, 1145);
					gGateStatus[0] = 1;//открыто
				}
			   	else
				{
        			ApplyAnimation(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
					SetObjectRot(oNGgate9, 0.0, 0.0, 0.0);
					PlaySoundForObject(oNGgate9, 1145);
					gGateStatus[0] = 0;//закрыто
				}
			}
			else if(number == 10)
			{   //ворото со стороны КПП
			   	if(gGateStatus[22] == 0)
			   	{   //ворота на военную базу
			   		ApplyAnimation(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
					MoveObjectEx(oNGgate10,121.6946, 1941.5570, 21.7132, 2.5);
					gGateStatus[22] = 1;//открыто
				}
			   	else
				{
					ApplyAnimation(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
					MoveObjectEx(oNGgate10,135.1046, 1941.5570, 21.7132, 2.5);
					gGateStatus[22] = 0;//закрыто
				}
			}
			else if(number == 11)
			{   //ворото со стороны КПП
			   	if(gGateStatus[23] == 0)
			   	{   //ворота на военную базу
			   		ApplyAnimation(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
					MoveObjectEx(oNGgate11,286.0753, 1833.9332, 20.04062, 2.5);
					gGateStatus[23] = 1;//открыто
				}
			   	else
				{
					ApplyAnimation(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);
					MoveObjectEx(oNGgate11,286.0753, 1821.1231, 20.0406, 2.5);
					gGateStatus[23] = 0;//закрыто
				}
			}
		}
		//return 1;
	}//для ворот конец
	else if(!strcmp(cmd, "/open", true))
	{
		if(PlayerInfo[playerid][pAdmin] < 5)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
			return 1;
	    }

        for(new h = 0; h < MAX_HOUSE; h++)
		{
			if(	!IsPlayerInRangeOfPoint(playerid, 3.0,
					HouseInfo[h][hEntranceX],
					HouseInfo[h][hEntranceY],
					HouseInfo[h][hEntranceZ]) &&
				!IsPlayerInRangeOfPoint(playerid, 3,
					HouseInfo[h][hExitX],
					HouseInfo[h][hExitY],
					HouseInfo[h][hExitZ]) ) continue;
			if(PlayerInfo[playerid][pSQLID] != HouseInfo[h][hOwned]//strcmp(PlayerName(playerid), HouseInfo[h][hOwner], true)
			&& PlayerInfo[playerid][pAdmin] < 5)
			{
				//GameTextForPlayerEx(playerid, "~r~You Dont Have A Key", 5000, 6);
				//SendClientMessage(playerid, COLOR_GREY, "   Вы НЕ владелец дома!");
				continue;
			}
			if(HouseInfo[h][hLock] == 1)
			{
				HouseInfo[h][hLock] = 0;
				GameTextForPlayerEx(playerid, "~w~Door ~g~Unlocked", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
				return 1;
			}
			else
			{
				HouseInfo[h][hLock] = 1;
				GameTextForPlayerEx(playerid, "~w~Door ~r~Locked", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
				return 1;
			}
		}
		for(new b=0; b<MAX_BIZ; b++)
		{
			if(	!IsPlayerInRangeOfPoint(playerid, 3.0,
					BizInfo[b][bEntranceX],
					BizInfo[b][bEntranceY],
						BizInfo[b][bEntranceZ]) &&
				!IsPlayerInRangeOfPoint(playerid, 3.0,
					BizInfo[b][bExitX],
					BizInfo[b][bExitY],
					BizInfo[b][bExitZ]) ) continue;
			if(PlayerInfo[playerid][pSQLID] != BizInfo[b][bOwned]//strcmp(PlayerName(playerid), BizInfo[b][bOwner], true)
			&& PlayerInfo[playerid][pAdmin] < 5)
			{
				//GameTextForPlayerEx(playerid, "~r~You Dont Have A Key", 5000, 6)
				continue;
			}
			if(BizInfo[b][bLock] == 1)
			{
				BizInfo[b][bLock] = 0;
				GameTextForPlayerEx(playerid, "~w~Bussiness ~g~Open", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
				return 1;
			}
			else
			{
				BizInfo[b][bLock] = 1;
				GameTextForPlayerEx(playerid, "~w~Bussiness ~r~Closed", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
				return 1;
			}
		}
		for(new sb=0; sb<MAX_SBIZ; sb++)
		{
			if(	!IsPlayerInRangeOfPoint(playerid, 3.0,
					SBizInfo[sb][sbEntranceX],
					SBizInfo[sb][sbEntranceY],
					SBizInfo[sb][sbEntranceZ]) ) continue;
			if(PlayerInfo[playerid][pSQLID] != SBizInfo[sb][sbOwned]//strcmp(PlayerName(playerid), SBizInfo[sb][sbOwner], true)
			&& PlayerInfo[playerid][pAdmin] < 5)
			{
				//GameTextForPlayerEx(playerid, "~r~You Dont Have A Key", 5000, 6)
				continue;
			}
			//для владения несколькими бизами
			if(SBizInfo[sb][sbLock] == 1)
			{
				SBizInfo[sb][sbLock] = 0;
				GameTextForPlayerEx(playerid, "~w~Bussiness ~g~Open", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
				break;
			}
			else
			{
				SBizInfo[sb][sbLock] = 1;
				GameTextForPlayerEx(playerid, "~w~Bussiness ~r~Closed", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
				break;
			}
		}
		//----------------------------------------------------------------------
		if(IsPlayerInRangeOfPoint(playerid, 20.0,193.0012,1931.4508,18.0406))
		{
			if(PlayerInfo[playerid][pMember] != DoD)
			{
				GameTextForPlayerEx(playerid, "~r~You Dont Have A Key", 5000, 6);
				return 1;
			}
			if(gBarracksLockDoor == 1)
			{
				gBarracksLockDoor = 0;
				GameTextForPlayerEx(playerid, "~w~Barracks Officers Door ~g~Open", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
			else
			{
				gBarracksLockDoor = 1;
				GameTextForPlayerEx(playerid, "~w~Barracks Officers Door ~r~Closed", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
		}
		else if(IsPlayerInRangeOfPoint(playerid, 20.0,1170.6339,1355.4663,10.9219))
		{
			if(PlayerInfo[playerid][pMember] != DoH)
			{
				GameTextForPlayerEx(playerid, "~r~You Dont Have A Key", 5000, 6);
				return 1;
			}
			if(gHospitalLockDoor == 1)
			{
				gHospitalLockDoor = 0;
				GameTextForPlayerEx(playerid, "~w~Hospital Door ~g~Open", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
			else
			{
				gHospitalLockDoor = 1;
				GameTextForPlayerEx(playerid, "~w~Hospital Door ~r~Closed", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
		}
		else if( IsPlayerInRangeOfPoint(playerid, 2.0, 1122.9260,-2037.0017,69.8939) ||
		    	IsPlayerInRangeOfPoint(playerid, 3.0,  965.0754,-53.1345,1001.1246) )
		{
			if(	PlayerInfo[playerid][pMember] != LCN)
			{
				GameTextForPlayerEx(playerid, "~r~You Dont Have A Key", 5000, 6);
				return 1;
			}
			if(gLCNLockDoor == 1)
			{
				gLCNLockDoor = 0;
				GameTextForPlayerEx(playerid, "~w~La Cosa Nostra Mansion ~g~Open", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
			else
			{
				gLCNLockDoor = 1;
				GameTextForPlayerEx(playerid, "~w~La Cosa Nostra Mansion ~r~Closed", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
		}
		else if( IsPlayerInRangeOfPoint(playerid, 2.0, -2192.6372,647.4218,49.4375) ||
		    	IsPlayerInRangeOfPoint(playerid, 3.0,  -2158.5637,642.5848,1052.3750) )
		{
			if(	PlayerInfo[playerid][pMember] != Yakuza)
			{
				GameTextForPlayerEx(playerid, "~r~You Dont Have A Key", 5000, 6);
				return 1;
			}
			if(gYLockDoor == 1)
			{
				gYLockDoor = 0;
				GameTextForPlayerEx(playerid, "~w~Yakudza Mansion ~g~Open", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
 			else
			{
				gYLockDoor = 1;
				GameTextForPlayerEx(playerid, "~w~Yakudza Mansion ~r~Closed", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
		}
		else if( IsPlayerInRangeOfPoint(playerid, 2.0, -2426.2612,338.0038,37.0000) ||
		    	IsPlayerInRangeOfPoint(playerid, 3.0,  390.1595,173.7057,1008.3828) )
		{
			if(PlayerInfo[playerid][pMember] != DoJ)
			{
				GameTextForPlayerEx(playerid, "~r~You Dont Have A Key", 5000, 6);
				return 1;
			}
			if(gCityHallLockDoor == 1)
			{
				gCityHallLockDoor = 0;
				GameTextForPlayerEx(playerid, "~w~City Hall ~g~Open", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
 			else
			{
				gCityHallLockDoor = 1;
				GameTextForPlayerEx(playerid, "~w~City Hall ~r~Closed", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
		}
		else if( IsPlayerInRangeOfPoint(playerid, 2.0, 1042.4713,1010.4932,11.1000) ||
				IsPlayerInRangeOfPoint(playerid, 3.0,  2151.5686,1602.9343,1002.0717) )
		{
			if(PlayerInfo[playerid][pMember] != SAN)
			{
				GameTextForPlayerEx(playerid, "~r~You Dont Have A Key", 5000, 6);
				return 1;
			}
			if(PlayerInfo[playerid][pRank] < 8)
			{
			    SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть 8 Ранга !");
			    return 1;
			}
			if(gCNNStudioLockDoor == 1)
			{
				gCNNStudioLockDoor = 0;
				GameTextForPlayerEx(playerid, "~w~CNN Studio ~g~Open", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
   			else
			{
				gCNNStudioLockDoor = 1;
				GameTextForPlayerEx(playerid, "~w~CNN Studio ~r~Closed", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
		}
		else if(IsPlayerInRangeOfPoint(playerid, 100.0,-2032.6810,-117.4816,1035.1719))
		{
			if(PlayerInfo[playerid][pMember] == DoE)
			{
				GameTextForPlayerEx(playerid, "~r~You Dont Have A Key", 5000, 6);
				return 1;
			}
			if(gSchoolLockDoor == 1)
			{
				gSchoolLockDoor = 0;
				GameTextForPlayerEx(playerid, "~w~School Door ~g~Open", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
    		else
			{
				gSchoolLockDoor = 1;
				GameTextForPlayerEx(playerid, "~w~School Door ~r~Closed", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
		}
#if defined vw_races//#endif
		else if( !IsPlayerInRangeOfPoint(playerid, 2.2, -2110.5586,-444.1488,38.8344) )//вход Blood Bowl int15 для дерби в СФ
		{
			if(gBloodBowlDoor == 1)
			{
				gBloodBowlDoor = 0;
				GameTextForPlayerEx(playerid, "~w~BloodBowl ~g~Open", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
			else
			{
				DerbiRand = 0;
				TotalDerby = 0;
				gDerbyStarted = 0;
				derbycountdown = 15;
				//derbycountdown = 0;
				KillTimer(gCountdownDerbyTimer); gCountdownDerbyTimer = -1;//и сразу убиваем

				for(new j=0, i; j<MaxPlayers; j++)	{//GetPlayerPoolSize
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) ) continue;
					if( !gInDerbyBloodBowl[i] ) continue;
					DisablePlayerRaceCheckpoint(i);

					SetPlayerVirtualWorldEx(i, 0);
				    SetPlayerInteriorEx(i, 0);
					PlayerInfo[i][pLocal] = FREEROAM;
					SetPlayerPosEx(i, -2119.5925,-443.8909,35.5313, 90.0);

					DerbyScore[i] = 0;
					PlayerInfo[i][pCarTime] = 0;
					gInDerbyBloodBowl[i] = 0;//опускаем флаг - игрок не в гонке
				}
				for(new v=0; v<sizeof(DerbyCar); v++)
				{
					SetVehicleToRespawnEx(playerid, DerbyCar[v]);
				}

				gBloodBowlDoor = 1;
				GameTextForPlayerEx(playerid, "~w~BloodBowl ~r~Closed", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
		}
		else if( !IsPlayerInRangeOfPoint(playerid, 2.2, 1099.4869,1601.4949,12.5469) )  //вход Stunting Track(Kickstart)
		{
			if(gKickStartDoor == 1)
			{
				gKickStartDoor = 0;
				GameTextForPlayerEx(playerid, "~w~KickStart ~g~Open", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
			else
			{
				for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
				    if(i == playerid) continue;
					if(!IsPlayerConnectedEx(i)) continue;// || !gPlayerSpawned[i]
					if(!gInDerbyKickStart[i]) continue;
					gTextDrawHideCarTime[i] = true; OnPlayerTextDrawStateChange(playerid);
					TimeSecRide[i] = 0;
					gInDerbyKickStart[i] = 0;
					if(PickupScore[i] > 0) GivePlayerMoneyH(fkickstart, i, PickupScore[i]*50);
					PickupScore[i] = 0;
				}
				for(new v=0; v<sizeof(IntCar); v++)
				{
					SetVehicleToRespawnEx(playerid, IntCar[v]);
				}
				for(new i=0; i<GREEN_PACKAGE; i++)
			 	{
			  		if(EasyPickup[i] != -1)
			    	{
						DestroyPickupEx(EasyPickup[i]); EasyPickup[i] = -1;
					}
					if(i >= YELLOW_PACKAGE) continue;
			    	if(MediumPickup[i] != -1)
			    	{
						DestroyPickupEx(MediumPickup[i]); MediumPickup[i] = -1;
					}
					if(i >= RED_PACKAGE) continue;
			    	if(HardPickup[i] != -1)
			    	{
						DestroyPickupEx(HardPickup[i]); HardPickup[i] = -1;
					}
				}
				gKickStarted = 0;
				KickStartProgress = 0;
				//SendClientMessageToAll(COLOR_ORANGE, "Заезд {FF0000}Kick Start{FF6600} закончился.");
				SendAllAdminMessage(COLOR_ORANGE, "Заезд {FF0000}Kick Start{FF6600} закончился.", 1);

				gKickStartDoor = 1;
				GameTextForPlayerEx(playerid, "~w~KickStart ~r~Closed", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
		}
#endif
		else if( !IsPlayerInRangeOfPoint(playerid, 2.2, 2196.8855,1677.1884,12.4672) )//Caligula's Casino
		{
			if(gCasinoLockDoor == 1)
			{
				gCasinoLockDoor = 0;
				GameTextForPlayerEx(playerid, "~w~Casino Door ~r~Closed", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
			else
			{
				gCasinoLockDoor = 1;
				GameTextForPlayerEx(playerid, "~w~Casino Door ~g~Open", 5000, 6);
				PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			}
		}
	}
	else if(!strcmp(cmd, "/savesettings", true))
	{
        if(PlayerInfo[playerid][pAdmin] != 5 && PlayerInfo[playerid][pAdmin] != 6
		&& PlayerInfo[playerid][pAdmin] != 7 && PlayerInfo[playerid][pAdmin] != 9)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
            return 1;
        }
#if defined vw_sql//#endif
		SaveSettingsSQL();
#else
		SaveSettings();
#endif

		//return 1;
	}
	else if(!strcmp(cmd, "/savehouses", true))
	{
        if(PlayerInfo[playerid][pAdmin] != 5 && PlayerInfo[playerid][pAdmin] != 6
		&& PlayerInfo[playerid][pAdmin] != 7 && PlayerInfo[playerid][pAdmin] != 9)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
            return 1;
        }
#if defined vw_sql//#endif
		SaveHousesSQL();
#else
		HouseInfo_Save();
#endif
		//return 1;
	}
	else if(!strcmp(cmd, "/savebizz", true))
	{
        if(PlayerInfo[playerid][pAdmin] != 5 && PlayerInfo[playerid][pAdmin] != 6
		&& PlayerInfo[playerid][pAdmin] != 7 && PlayerInfo[playerid][pAdmin] != 9)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
            return 1;
        }
#if defined vw_sql//#endif
		SaveBizSQL();
#else
		BizInfo_Save();
#endif
		//return 1;
	}
	else if(!strcmp(cmd, "/savesbizz", true))
	{
        if(PlayerInfo[playerid][pAdmin] != 5 && PlayerInfo[playerid][pAdmin] != 6
		&& PlayerInfo[playerid][pAdmin] != 7 && PlayerInfo[playerid][pAdmin] != 9)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
            return 1;
        }
#if defined vw_sql//#endif
		SaveSBizSQL();
#else
		SBizInfo_Save();
#endif
		//return 1;
	}
	else if(!strcmp(cmd, "/savefamilies", true))
	{
        if(PlayerInfo[playerid][pAdmin] != 5 && PlayerInfo[playerid][pAdmin] != 6
		&& PlayerInfo[playerid][pAdmin] != 7 && PlayerInfo[playerid][pAdmin] != 9)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
            return 1;
        }
#if defined vw_sql//#endif
		SaveFamiliesSQL("CEPBEP");
		SaveClansSQL("CEPBEP");
#endif
		//return 1;
	}
	else if(!strcmp(cmd, "/savecars", true))
	{
        if(PlayerInfo[playerid][pAdmin] != 5 && PlayerInfo[playerid][pAdmin] != 6
		&& PlayerInfo[playerid][pAdmin] != 7 && PlayerInfo[playerid][pAdmin] != 9)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
            return 1;
        }
#if defined vw_sql//#endif
		SaveCarSQL();
#endif
		//return 1;
	}
	else if(!strcmp(cmd, "/logout", true))
	{
        if(	PlayerInfo[playerid][pAdmin] != 5 && PlayerInfo[playerid][pAdmin] != 6 &&
			PlayerInfo[playerid][pAdmin] != 7 && PlayerInfo[playerid][pAdmin] != 9)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
            return 1;
        }
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /logout [playerid/PartOfName]");
			return 1;
		}
		giveplayerid = ReturnUser(tmp);
	    if( !IsPlayerConnected(giveplayerid) )
		{
			format(strcmd, sizeof(strcmd), "   ID:%d отсутствует на сервере.", giveplayerid);
			SendClientMessage(playerid, COLOR_GREY, strcmd);
			return 1;
		}
#if defined vw_sql//#endif
		OnPlayerStatsUpdate(giveplayerid, 255);
#endif
		SendClientMessage(playerid, COLOR_GREY, "   Все данные по игроку были сохранены.");
		//return 1;
	}
	else if(!strcmp(cmd, "/logoutall", true))
	{
        if(PlayerInfo[playerid][pAdmin] != 5 && PlayerInfo[playerid][pAdmin] != 6
		&& PlayerInfo[playerid][pAdmin] != 7 && PlayerInfo[playerid][pAdmin] != 9)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
            return 1;
        }
        //CallLocalFunction("OnRemoteLogoutServer", "s", CREATOR);
#if defined vw_sql//#endif
        //OnRemoteLogoutServer();

	 	for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			if( !gPlayerSpawned[i] ) continue;
			OnPlayerStatsUpdate(i, 254);
			SendClientMessage(i, COLOR_GREY, "   Ваши Данные были сохранены.");
		}
#else
		SaveSettings();
		HouseInfo_Save();
		BizInfo_Save();
		SBizInfo_Save();
#endif

        format(strcmd, sizeof(strcmd), "AdmCmd: %s OnRemoteLogoutServer", PlayerName(playerid));
		Log(ADMINLOG, strcmd);

		//if(CHECKING == 6)
		//{
			//new stats[160]; mysql_stat(stats); print(stats);
//Uptime: 6295623  Threads: 23  Questions: 145255209  Slow queries: 7589  Opens: 10950323  Flush tables: 1  Open tables: 64  Queries per second avg: 23.72
			//SendAllAdminMessage(COLOR_LIGHTBLUE, stats, 6);
		//}
		//return 1;
	}
	//==========================================================================
	//BUSINESS COMMANDS
	//==========================================================================

	else if(!strcmp(cmd, "/storehouse", true) || !strcmp(cmd, "/sh", true))
	{//BizInfo[80][bOwned] != 0 &&
		if(PlayerInfo[playerid][pSQLID] != BizInfo[80][bOwned]//strcmp(PlayerName(playerid), BizInfo[80][bOwner], true)
			&& PlayerInfo[playerid][pAdmin] < 6)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не являетесь владельцем склада !");
			return 1;
		}
		new parameter[20];
		parameter = strtok(cmdtext, idx);
		if(!strlen(parameter))
		{
			SendClientMessage(playerid, COLOR_HERBAL, "|________________ Store House ________________|");
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /storehouse [name] [value]");
			SendClientMessage(playerid, COLOR_GREY, "Available parameters: Metal, Textiles, Provisions, Tree, Fuel");
			SendClientMessage(playerid, COLOR_HERBAL, "|_________________________________________|");
			return 1;
		}

		new strtmp[9+3]; new value;
		if(!strcmp(parameter, "Metal", true))
	    {
			tmp = strtok(cmdtext, idx);
			if(!strlen(tmp))
			{
				format(strcmd, sizeof(strcmd), "LimitMetal: %d", LimitMetal);
				SendClientMessage(playerid, COLOR_RED, strcmd);
				return 1;
			}
			value = strval(tmp);
			LimitMetal = value;
		}
	    else if(!strcmp(parameter, "Textiles", true))
	    {
			tmp = strtok(cmdtext, idx);
			if(!strlen(tmp))
			{
				format(strcmd, sizeof(strcmd), "LimitTextiles: %d", LimitMetal);
				SendClientMessage(playerid, COLOR_RED, strcmd);
				return 1;
			}
			value = strval(tmp);
			LimitTextiles = value;
		}
	    else if(!strcmp(parameter, "Provisions", true))
	    {
			tmp = strtok(cmdtext, idx);
			if(!strlen(tmp))
			{
				format(strcmd, sizeof(strcmd), "LimitProvisions: %d", LimitMetal);
				SendClientMessage(playerid, COLOR_RED, strcmd);
				return 1;
			}
			value = strval(tmp);
			LimitProvisions = value;
		}
		else if(!strcmp(parameter, "Tree", true))
	    {
			tmp = strtok(cmdtext, idx);
			if(!strlen(tmp))
			{
				format(strcmd, sizeof(strcmd), "LimitTree: %d", LimitMetal);
				SendClientMessage(playerid, COLOR_RED, strcmd);
				return 1;
			}
			value = strval(tmp);
			LimitTree = value;
		}
		else if(!strcmp(parameter, "Fuel", true))
	    {
			tmp = strtok(cmdtext, idx);
			if(!strlen(tmp))
			{
				format(strcmd, sizeof(strcmd), "LimitFuel: %d", LimitMetal);
				SendClientMessage(playerid, COLOR_RED, strcmd);
				return 1;
			}
			value = strval(tmp);
			LimitFuel = value;
		}
		format(strtmp, sizeof(strtmp), "Biz: %d", 80);
		format(strcmd, sizeof(strcmd), "AdmCmd: %s has corrected %s to %d for %s", PlayerName(playerid), parameter, value, strtmp);
		Log(ADMINLOG,  strcmd);
		SendClientMessage(playerid, COLOR_RED, strcmd);
		//return 1;
	}//"/storehouse" - конец
	else if(!strcmp(cmd, "/edit", true))
	{
		if(PlayerInfo[playerid][pAdmin] != 6 && PlayerInfo[playerid][pAdmin] != 7 &&
			PlayerInfo[playerid][pAdmin] != 9)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
			return 1;
		}
		new parameter[20];
		parameter = strtok(cmdtext, idx);
		if(!strlen(parameter))
		{
			SendClientMessage(playerid, COLOR_HERBAL, "|__________________ Edit __________________|");
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /edit [name] [value] (Used for Businesses)");// (Used for Houses and Businesses)
			SendClientMessage(playerid, COLOR_GREY, "Available parameters: Price, Level, Entrance, BuyProd, SellProd, Till");
			SendClientMessage(playerid, COLOR_GREY, "Available parameters: Metal, Textiles, Provisions, Tree, Fuel, Products");
			SendClientMessage(playerid, COLOR_GREY, "Available parameters: Worker, Import, Export, Salary, Expenses");
			SendClientMessage(playerid, COLOR_HERBAL, "|_________________________________________|");
			return 1;
		}
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /edit [name] [ammount]");
			return 1;
		}
		new value = strval(tmp);

		new strtmp[9+3];
		for(new b=0; b<MAX_BIZ; b++)
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.0, BizInfo[b][bEntranceX], BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ]))
			{
				if(value >= 0)
				{
					if(!strcmp(parameter, "price", true))
				    {
						BizInfo[b][bBuyPrice] = value;
					}
				    else if(!strcmp(parameter, "level", true))
				    {
						BizInfo[b][bLevel] = value;
					}
				    else if(!strcmp(parameter, "entrance", true))
				    {
						BizInfo[b][bEntranceCost] = value;
					}

					else if(!strcmp(parameter, "Metal", true))
				    {
						BizInfo[b][bMetal] = value;
					}
					else if(!strcmp(parameter, "Textiles", true))
				    {
						BizInfo[b][bTextiles] = value;
					}
					else if(!strcmp(parameter, "Provisions", true))
				    {
						BizInfo[b][bProvisions] = value;
					}
					else if(!strcmp(parameter, "Tree", true))
				    {
						BizInfo[b][bTree] = value;
					}
					else if(!strcmp(parameter, "Fuel", true))
				    {
						BizInfo[b][bFuel] = value;
					}
					else if(!strcmp(parameter, "Products", true))
				    {
						BizInfo[b][bProducts] = value;
					}

					else if(!strcmp(parameter, "BuyProd", true))
				    {
						BizInfo[b][bBuyProd] = value;
					}
					else if(!strcmp(parameter, "SellProd", true))
				    {
						BizInfo[b][bSellProd] = value;
					}
					else if(!strcmp(parameter, "Till", true))
				    {
						BizInfo[b][bTill] = value;
					}

					else if(!strcmp(parameter, "Worker", true))
				    {
						BizInfo[b][bWorker] = value;
					}
					else if(!strcmp(parameter, "Import", true))
				    {
						BizInfo[b][bImport] = value;
					}
					else if(!strcmp(parameter, "Export", true))
				    {
						BizInfo[b][bExport] = value;
					}
					else if(!strcmp(parameter, "Salary", true))
				    {
						BizInfo[b][bSalary] = value;
					}
					else if(!strcmp(parameter, "Expenses", true))
				    {
						BizInfo[b][bExpenses] = value;
					}
#if defined vw_sql//#endif
					SaveBiz(b);
#endif
					format(strtmp, sizeof(strtmp), "Biz: %d", b);
					if(b == 80) UpdateStoreHouse();
					else if(b == 81) UpdateOceanDock();
					break;//return 1;
				}
				//break;
			}
		}
		for(new sb=0; sb<MAX_SBIZ; sb++)
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.0, SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ]))
			{
				if(value >= 0)
				{
					if(!strcmp(parameter, "Price", true))
				    {
						SBizInfo[sb][sbBuyPrice] = value;
					}
				    else if(!strcmp(parameter, "Level", true))
				    {
						SBizInfo[sb][sbLevel] = value;
					}
				    else if(!strcmp(parameter, "Entrance", true))
				    {
						SBizInfo[sb][sbEntranceCost] = value;
					}
					else if(!strcmp(parameter, "Products", true))
				    {
						SBizInfo[sb][sbProducts] = value;
					}
					else if(!strcmp(parameter, "BuyProd", true))
				    {
						SBizInfo[sb][sbBuyProd] = value;
					}
					else if(!strcmp(parameter, "SellProd", true))
				    {
						SBizInfo[sb][sbSellProd] = value;
					}
					else if(!strcmp(parameter, "Till", true))
				    {
						SBizInfo[sb][sbTill] = value;
					}
					else if(!strcmp(parameter, "Worker", true))
				    {
						SBizInfo[sb][sbWorker] = value;
					}
					else if(!strcmp(parameter, "Import", true))
				    {
						SBizInfo[sb][sbImport] = value;
					}
					else if(!strcmp(parameter, "Export", true))
				    {
						SBizInfo[sb][sbExport] = value;
					}
					else if(!strcmp(parameter, "Salary", true))
				    {
						SBizInfo[sb][sbSalary] = value;
					}
					else if(!strcmp(parameter, "Expenses", true))
				    {
						SBizInfo[sb][sbExpenses] = value;
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "  Ошибка имя параметра или такого параметра у этого бизнеса не существует!");
						return 1;
					}
#if defined vw_sql//#endif
					SaveSBiz(sb);
#endif
					format(strtmp, sizeof(strtmp), "SBiz: %d", sb);
					break; //return 1;
				}
			}
		}
		format(strcmd, sizeof(strcmd), "AdmCmd: %s has corrected %s to %d for %s", PlayerName(playerid), parameter, value, strtmp);
		Log(ADMINLOG, strcmd);
		SendClientMessage(playerid, COLOR_RED, strcmd);
		//return 1;
	}//"/edit" - конец
	else if(!strcmp(cmd, "/asellhouse", true))
	{
		if(PlayerInfo[playerid][pMember] == DoJ)
		{
	        if(PlayerInfo[playerid][pRank] != 10)
			{
			    SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть 10 Ранга !");
			    return 1;
			}
			for(new h = 0; h < MAX_HOUSE; h++)
			{   //находим у какого дома стоит сейчас игрок
				if(IsPlayerInRangeOfPoint(playerid, 3.0, HouseInfo[h][hEntranceX], HouseInfo[h][hEntranceY], HouseInfo[h][hEntranceZ]))
				{   //если игрок у входа в дом
					//отбираем ключи у владельца
					new playername[MAX_PLAYER_NAME];
					strmid(playername, HouseInfo[h][hOwner], 0, strlen(HouseInfo[h][hOwner]), 255);
		            giveplayerid = ReturnUser( playername );
					if(giveplayerid == playerid)
					{
						SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /asellhouse");
						return 1;
					}
					if( !IsPlayerConnected(giveplayerid) )
					{
						if(CheckExistPlayer(playerid, playername) == 0)
						{
							SendClientMessage(playerid, COLOR_GREY, "   Это имя не зарегистрировано или указано не верно !");
							return 1;
						}
#if defined vw_sql//#endif
						new ToBase[86+10+24];
						format(ToBase, sizeof(ToBase), "UPDATE `players` SET `House` = "#NOT_KEY" WHERE `House`=%d", h);//снять ключ от дома у всех арендаторов
						//mysql_query(ToBase);
						db_free_result(db_query(db_VW, ToBase));

						SendClientMessage(playerid, COLOR_OLIVE, "Все выселены.");

						format(ToBase, sizeof(ToBase), "UPDATE `players` SET `House` = "#NOT_KEY", `Bank`=`Bank`+%d WHERE `Name`='%s'",
							HouseInfo[h][hBuyPrice], playername);//вернуть деньги за дом владельцу
						//mysql_query(ToBase);
						db_free_result(db_query(db_VW, ToBase));
#endif
					}
					else
					{
						for(new limit = 0; limit < 5; limit++)
						{
							if(MyHouse[giveplayerid][limit] != h) continue;
							MyHouse[giveplayerid][limit] = NOT_KEY;
						}
						PlayerInfo[giveplayerid][pHouse] = NOT_KEY;//ВНИМАНИЕ нельзя т.к. домов может быть больше 1
						GivePlayerMoneyB(fhouse+h, giveplayerid, HouseInfo[h][hBuyPrice]);
						//OnPlayerStatsUpdate(giveplayerid);
					}
					//------------------------------------------------------
					//SaveCarInfo();
					strmid(HouseInfo[h][hOwner], "The State", 0, strlen("The State"), 255);
					HouseInfo[h][hHel] = 0;
					HouseInfo[h][hCloth] = 0;
					HouseInfo[h][hTV] = 0;
					HouseInfo[h][hLock] = 1;
					HouseInfo[h][hOwned] = 0;
					HouseInfo[h][hRent] = 100;
					//HouseInfo[h][hRentabil] = 1;
					//HouseInfo[house][hTill] = 500;
#if defined vw_sql//#endif
					SaveHouseSQL(h);
#endif
					format(strcmd, sizeof(strcmd), "%s has sell house %d for $%d", PlayerName(playerid), h, HouseInfo[h][hBuyPrice]);
	                Log(BUY,strcmd);

					new text_info[7+20];
			    	format(text_info, sizeof(text_info), "[ %s ]", HouseInfo[h][hDiscription]);
					Update3DTextLabelEx(hEntranceText3D[h], 0x88EE88FF, text_info);

					format(strcmd, sizeof(strcmd), "~y~Congratulations~n~~w~You have sold your property for ~n~~g~$%d", HouseInfo[h][hBuyPrice]);
					GameTextForPlayerEx(playerid, strcmd, 10000, 3);
					break;
				}
			}
			IncreaseRank(playerid, 1);
		}
		else if(PlayerInfo[playerid][pAdmin] == 7 || PlayerInfo[playerid][pAdmin] == 9)
		{
			tmp = strtok(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /asellhouse [houseid]");
				return 1;
			}
			new house = strval(tmp);
			//отбираем ключи у владельца
			new playername[MAX_PLAYER_NAME];
			strmid(playername, HouseInfo[house][hOwner], 0, strlen(HouseInfo[house][hOwner]), 255);
            giveplayerid = ReturnUser( playername );
			if(giveplayerid == playerid)
			{
				SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /asellhouse [houseid]");
				return 1;
			}
			if( !IsPlayerConnected(giveplayerid) )
			{
				/*if(CheckExistPlayer(playerid, playername) == 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Это имя не зарегистрировано или указано не верно !");
					return 1;
				}*/
#if defined vw_sql//#endif
				new ToBase[76+10+24];
				format(ToBase, sizeof(ToBase), "UPDATE `players` SET `House`="#NOT_KEY" WHERE `House`=%d", house);
				//mysql_query(ToBase);
				db_free_result(db_query(db_VW, ToBase));
				SendClientMessage(playerid, COLOR_OLIVE, "Все выселены.");

				format(ToBase, sizeof(ToBase), "UPDATE `players` SET `House`="#NOT_KEY", `Bank`=`Bank`+%d WHERE `Name`='%s'",
					HouseInfo[house][hBuyPrice],
					playername);
				//mysql_query(ToBase);
				db_free_result(db_query(db_VW, ToBase));
#endif
			}
			else
			{
				for(new limit = 0; limit < 5; limit++)
				{
					if(MyHouse[giveplayerid][limit] != house) continue;
					MyHouse[giveplayerid][limit] = NOT_KEY;
				}
				PlayerInfo[giveplayerid][pHouse] = NOT_KEY;//ВНИМАНИЕ нельзя т.к. домов может быть больше 1
				GivePlayerMoneyB(house, giveplayerid, HouseInfo[house][hBuyPrice]);
				//OnPlayerStatsUpdate(giveplayerid);
			}
			//------------------------------------------------------
			strmid(HouseInfo[house][hOwner], "The State", 0, strlen("The State"), 255);
			//HouseInfo[house][hHel] = 0;
			//HouseInfo[house][hCloth] = 0;
			//HouseInfo[house][hTV] = 0;
			HouseInfo[house][hLock] = 1;
			HouseInfo[house][hOwned] = 0;
			//HouseInfo[house][hRent] = 100;
			//HouseInfo[house][hRentabil] = 0;
			//HouseInfo[house][hTill] = 500;
#if defined vw_sql//#endif
			SaveHouseSQL(house);
//#endif
			PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
			format(strcmd, sizeof(strcmd), "AdmCmd: %s has sell house %d for $%d", PlayerName(playerid), house, HouseInfo[house][hBuyPrice]);
			Log(ADMINLOG, strcmd);

			GameTextForPlayerEx(playerid, "~w~You have sold this house", 5000, 3);

			new text_info[19+20+24];
	    	format(text_info, sizeof(text_info), "[ %s ]",HouseInfo[house][hDiscription]);
			//Update3DTextLabelText(text3D[house], 0x88EE88FF, strcmd);
			Update3DTextLabelEx(hEntranceText3D[house], 0x88EE88FF, text_info);

		}
		else SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
		//return 1;
	}
	else if(!strcmp(cmd, "/asellbiz", true))
	{
		if(PlayerInfo[playerid][pAdmin] == 7 || PlayerInfo[playerid][pAdmin] == 9)
		{
			tmp = strtok(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /asellbiz [bizid]");//[playerid/PartOfName]
				return 1;
			}
			new biz = strval(tmp);
			//отбираем ключи у владельца
			new playername[MAX_PLAYER_NAME];
			strmid(playername, BizInfo[biz][bOwner], 0, strlen(BizInfo[biz][bOwner]), 24);
            giveplayerid = ReturnUser( playername );
			/*if(giveplayerid == playerid)
			{
				SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /asellbiz [bizid]");
				return 1;
			}*/
			if( !IsPlayerConnected(giveplayerid) )
			{
				/*if(CheckExistPlayer(playerid, playername) == 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Это имя не зарегистрировано или указано не верно !");
					return 1;
				}*/
#if defined vw_sql//#endif
				new ToBase[76+10+24];
				/*format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Bizz`="#NOT_KEY", `Bank`=`Bank`+%d WHERE `Name`='%s'",
					BizInfo[biz][bBuyPrice],
					playername);*/
				format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Bizz`="#NOT_KEY" WHERE `Name`='%s'", playername);
				//mysql_query(ToBase);
				db_free_result(db_query(db_VW, ToBase));
#endif
			}
			else
			{
				for(new limit = 0; limit < 10; limit++)
				{
					if(MyBizz[giveplayerid][limit] != biz) continue;
					MyBizz[giveplayerid][limit] = NOT_KEY;
				}
				PlayerInfo[giveplayerid][pBizz] = NOT_KEY;//для владения несколькими бизами
				//GivePlayerMoneyB(fbiz+biz, giveplayerid, BizInfo[biz][bBuyPrice]);
				//OnPlayerStatsUpdate(giveplayerid);
			}
			//--------------------------------------------------------------
			OnBizInit(biz);

			PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
			format(strcmd, sizeof(strcmd), "AdmCmd: %s has sell biz %d", PlayerName(playerid), biz);
			Log(ADMINLOG, strcmd);

			new text_info[19+20+24];
	    	format(text_info, sizeof(text_info), "[ %s ]",BizInfo[biz][bDiscription]);
			//Update3DTextLabelText(text3D[MAX_HOUSE+biz], 0xEEEE88FF, strcmd);
			Update3DTextLabelEx(bEntranceText3D[biz], 0xEEEE88FF, text_info);

			format(strcmd, sizeof(strcmd), "~w~You have sold the Business");
			GameTextForPlayerEx(playerid, strcmd, 10000, 3);
			SaveBiz(biz);
		}
		else SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
		//return 1;
	}
	else if(!strcmp(cmd, "/asellsbiz", true))
	{
		if(PlayerInfo[playerid][pAdmin] == 7 || PlayerInfo[playerid][pAdmin] == 9)
		{
			tmp = strtok(cmdtext, idx);
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /asellsbiz [sbizid]");
				return 1;
			}
			new sbiz = strval(tmp);
			//отбираем ключи у владельца
			new playername[MAX_PLAYER_NAME];
			strmid(playername, SBizInfo[sbiz][sbOwner], 0, strlen(SBizInfo[sbiz][sbOwner]), 255);
			giveplayerid = ReturnUser( playername );
			/*if(giveplayerid == playerid)
			{
				SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /asellsbiz [sbizid]");
				return 1;
			}*/
			if( !IsPlayerConnected(giveplayerid) )
			{
				/*if(CheckExistPlayer(playerid, playername) == 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Это имя не зарегистрировано или указано не верно !");
					return 1;
				}*/
#if defined vw_sql//#endif
				new ToBase[76+10+24];
				/*format(ToBase, sizeof(ToBase),
					"UPDATE `players` SET `Bizz`="#NOT_KEY",`Bank`=`Bank`+%d WHERE `Name`='%s'",
					SBizInfo[sbiz][sbBuyPrice],	playername);*/
				format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Bizz`="#NOT_KEY" WHERE `Name`='%s'",	playername);
				//mysql_query(ToBase);
				db_free_result(db_query(db_VW, ToBase));
#endif
			}
			else
			{
				for(new limit = 0; limit < 20; limit++)
				{
					if(MyCompany[giveplayerid][limit] != sbiz) continue;
					MyCompany[giveplayerid][limit] = NOT_KEY;
				}
				PlayerInfo[giveplayerid][pBizz] = NOT_KEY;//для владения несколькими бизами
				//if(sbiz < 36) GivePlayerMoneyB(fsbiz+sbiz, giveplayerid, SBizInfo[sbiz][sbBuyPrice]);
				//OnPlayerStatsUpdate(giveplayerid);
			}
			//--------------------------------------------------------------
			OnSBizInit(sbiz);
			PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
			format(strcmd, sizeof(strcmd), "AdmCmd: %s has sell sbiz %d", PlayerName(playerid), sbiz);
   			Log(ADMINLOG, strcmd);

			new text_info[19+20+24];
	    	format(text_info, sizeof(text_info), "[ %s ]",SBizInfo[sbiz][sbDiscription]);
			//Update3DTextLabelText(text3D[MAX_HOUSE+MAX_BIZ+sbiz], 0xEEEE88FF, strcmd);
			Update3DTextLabelEx(sbEntranceText3D[sbiz], 0xEEEE88FF, text_info);

			format(strcmd, sizeof(strcmd), "~w~You have sold the Business");
			GameTextForPlayerEx(playerid, strcmd, 10000, 3);
			SaveSBiz(sbiz);
			return 1;
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
		}
		//return 1;
	}
	else if(!strcmp(cmd, "/SetPlayerPos", true) || !strcmp(cmd, "/SPP", true))//Сравнивает две строки друг с другом
	{
        if(PlayerInfo[playerid][pAdmin] < 6)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
            return 1;
        }
		new Float:x, Float:y, Float:z, Float:Ang;
		new Array[4][MAX_STRING];
		Array[0] = strtoko(cmdtext, idx, ',');
		if(!strlen(Array[0]))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /SPP [X],[Y],[Z],[Ang]");//,[Ang]
			return 1;
		}
		x = floatstr(Array[0]);//Конвертирует строку в соответствующее вещественное число.

		Array[1] = strtoko(cmdtext, idx, ',');
		if(!strlen(Array[1]))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /SPP [X],[Y],[Z],[Ang]");//,[Ang]
			return 1;
		}
		y = floatstr(Array[1]);

		Array[2] = strtoko(cmdtext, idx, ',');
		if(!strlen(Array[2]))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /SPP [X],[Y],[Z],[Ang]");//,[Ang]
			return 1;
		}
		z = floatstr(Array[2]);

		Array[3] = strtoko(cmdtext, idx, ',');
		Ang = floatstr(Array[3]);

		if(IsPlayerInAnyVehicle(playerid))
		{
			SetVehiclePosEx(nCarID[playerid],x,y,z);//перемещаем данный автомобиль в назначенную точку (вместе с игроком естесстенно);
			SetVehicleZAngleEx(nCarID[playerid], Ang);
		}
		else
		{
			SetPlayerPosEx(playerid, x,y,z, Ang);//перемещаем только игрока на указанные координаты (без машины=)  )
		}//конец

		format(strcmd, sizeof(strcmd), "SetPos(%d, %.4f, %.4f, %.4f)", playerid, x, y, z);
		SendClientMessage(playerid, COLOR_GRAYWHITE, strcmd);
		format(strcmd, sizeof(strcmd), "SetAngle(%d, %.4f)", playerid, Ang);
		SendClientMessage(playerid, COLOR_GRAYWHITE, strcmd);
		//return 1;
	}
	
	else if(!strcmp(cmd, "/sethp", true))
	{
		if(PlayerInfo[playerid][pAdmin] != 4 && PlayerInfo[playerid][pAdmin] != 6 && PlayerInfo[playerid][pAdmin] != 7 && PlayerInfo[playerid][pAdmin] != 9)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
			return 1;
		}
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /sethp [playerid/PartOfName] [health]");
			return 1;
		}
		giveplayerid = ReturnUser(tmp);
		tmp = strtok(cmdtext, idx);
		if(floatstr(tmp) > 255.0)
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /sethp [playerid/PartOfName] [health]");
			return 1;
		}
		new Float: health = strval(tmp);
	    if( !IsPlayerConnected(giveplayerid) )
		{
			format(strcmd, sizeof(strcmd), "   ID:%d отсутствует на сервере.", giveplayerid); SendClientMessage(playerid, COLOR_GREY, strcmd);
			return 1;
		}
		SetPlayerHealthEx(giveplayerid, health);
		format(strcmd, sizeof(strcmd), "AdmCmd: %s set %s's %.0f health", PlayerName(playerid), PlayerName(giveplayerid), health);
		Log(ADMINLOG, strcmd);
		ABroadCast(COLOR_RED, strcmd, 9);
		//return 1;
	}
	else if(!strcmp(cmd, "/setarmor", true))
	{
        if(PlayerInfo[playerid][pAdmin] != 4 && PlayerInfo[playerid][pAdmin] != 9)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
		    return 1;
		}
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /setarmor [playerid/PartOfName] [armor]");
			return 1;
		}
		giveplayerid = ReturnUser(tmp);
		tmp = strtok(cmdtext, idx);
		new Float: health = strval(tmp);
	    if( !IsPlayerConnected(giveplayerid) )
		{
			format(strcmd, sizeof(strcmd), "   ID:%d отсутствует на сервере.", giveplayerid); SendClientMessage(playerid, COLOR_GREY, strcmd);
			return 1;
		}
		SetPlayerArmourEx(giveplayerid, health);//giveplayerid - playerid, health - armour
		format(strcmd, sizeof(strcmd), "AdmCmd: %s set %s's %.1f armours", PlayerName(playerid), PlayerName(giveplayerid), health);
  		Log(ADMINLOG, strcmd);
		//return 1;
	}
	else if(!strcmp(cmd, "/fw", true))//сдвигает влево на 2 пункта по оси у
	{
        if(PlayerInfo[playerid][pAdmin] < 6)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
            return 1;
        }
		new Float:slx, Float:sly, Float:slz;
		GetPlayerPos(playerid, slx,sly,slz);
		SetPlayerPosEx(playerid, slx,sly+2.0,slz, 0);
		//return 1;
	}
	else if(!strcmp(cmd, "/bk", true))//сдвигает влево на 2 пункта по оси у
	{
        if(PlayerInfo[playerid][pAdmin] < 6)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
            return 1;
        }
		new Float:slx, Float:sly, Float:slz;
		GetPlayerPos(playerid, slx, sly, slz);
		SetPlayerPosEx(playerid, slx,sly-2.0,slz, 0);
		//return 1;
	}
	else if(!strcmp(cmd, "/dn", true))//опускает игрока на 2 пункта по оси
	{
        if(PlayerInfo[playerid][pAdmin] < 6)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
            return 1;
        }
		new Float:slx, Float:sly, Float:slz;
		GetPlayerPos(playerid, slx, sly, slz);
		SetPlayerPosEx(playerid, slx,sly,slz-3.0, 0);
		//return 1;
	}
	else if(!strcmp(cmd, "/up", true))//подымает игрока на 2 пункта по оси
	{
        if(PlayerInfo[playerid][pAdmin] < 6)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
            return 1;
        }
		new Float:slx, Float:sly, Float:slz;
		GetPlayerPos(playerid, slx, sly, slz);
		SetPlayerPosEx(playerid, slx,sly,slz+3.0, 0);
		//return 1;
	}
	else if(!strcmp(cmd, "/lt", true))//сдвигает влево на 2 пункта по оси у
	{
        if(PlayerInfo[playerid][pAdmin] < 6)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
            return 1;
        }
		new Float:slx, Float:sly, Float:slz;
		GetPlayerPos(playerid, slx, sly, slz);
		SetPlayerPosEx(playerid, slx-2.0,sly,slz, 0);

		//return 1;
	}
	else if(!strcmp(cmd, "/rt", true))
	{
        if(PlayerInfo[playerid][pAdmin] < 6)
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
            return 1;
        }
		new Float:slx, Float:sly, Float:slz;
		GetPlayerPos(playerid, slx, sly, slz);
		SetPlayerPosEx(playerid, slx+2.0,sly,slz, 0);
		//return 1;
	}
	else if(!strcmp(cmd, "/gotols", true))
	{
        if(PlayerInfo[playerid][pAdmin] != 5 && PlayerInfo[playerid][pAdmin] != 9)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
		    return 1;
		}
		if(CurState[playerid] == PLAYER_STATE_DRIVER)//если вы за рулём
		{
			SetVehiclePosEx(nCarID[playerid], 1529.6,-1691.2,13.3);
		}
		else
		{
			SetPlayerPosEx(playerid, 1529.6,-1691.2,13.3, 0);
		}
		SendClientMessage(playerid, COLOR_GRAD1, "   Вы телепортировались в LS !");
		SetPlayerInteriorEx(playerid, 0);
		SetPlayerVirtualWorldEx(playerid, 0);
		PlayerInfo[playerid][pLocal] = FREEROAM;
		//return 1;
	}
	else if(!strcmp(cmd, "/gotosf", true))
	{
        if(PlayerInfo[playerid][pAdmin] != 5 && PlayerInfo[playerid][pAdmin] != 9)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
		    return 1;
		}
		if(CurState[playerid] == PLAYER_STATE_DRIVER)
		{
			SetVehiclePosEx(nCarID[playerid], -1983.7242,138.2387,27.6875);
		}
		else SetPlayerPosEx(playerid, -1983.7242,138.2387,27.6875, 0);
		SendClientMessage(playerid, COLOR_GRAD1, "   Вы телепортировались в SF !");
		SetPlayerInteriorEx(playerid, 0);
		SetPlayerVirtualWorldEx(playerid, 0);
		PlayerInfo[playerid][pLocal] = FREEROAM;
		//return 1;
	}
	else if(!strcmp(cmd, "/gotolv", true))
	{
        if(PlayerInfo[playerid][pAdmin] != 5 && PlayerInfo[playerid][pAdmin] != 9)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
		    return 1;
		}
		//if(CurState[playerid] == PLAYER_STATE_DRIVER)
		if(IsPlayerInAnyVehicle(playerid))
		{
			SetVehiclePosEx(nCarID[playerid], 1699.2, 1435.1, 10.7);
		}
		else SetPlayerPosEx(playerid, 1699.2,1435.1,10.7, 0);
		SendClientMessage(playerid, COLOR_GRAD1, "   Вы телепортировались в LV !");
		SetPlayerInteriorEx(playerid, 0);
		SetPlayerVirtualWorldEx(playerid, 0);
		PlayerInfo[playerid][pLocal] = FREEROAM;
		//return 1;
	}
	else if(!strcmp(cmd, "/makeleader", true))
	{
		/*if( PlayerInfo[playerid][pAdmin] != 2 && PlayerInfo[playerid][pAdmin] != 5 &&
			PlayerInfo[playerid][pAdmin] != 6 && PlayerInfo[playerid][pAdmin] != 7 &&
			PlayerInfo[playerid][pLeader] != DoJ &&
			PlayerInfo[playerid][pAdmin] != 9)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
			return 1;
		}*/
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /makeleader [playerid/PartOfName] [Number(1-19)(0-UnInvite)]");

			SendClientMessage(playerid, COLOR_GRAYWHITE, "Банды: Grove Street("#TEAM_GROVE"), The Ballas("#TEAM_BALLAS"), Varios Los Aztecas("#TEAM_AZTEC"), Los Santos Vagos("#TEAM_VAGOS")");
			SendClientMessage(playerid, COLOR_GRAYWHITE, "Банды: Da Nang Boys("#TEAM_NANG"), San Fierro Rifa("#TEAM_RIFA "), The Traids("#TEAM_TRIAD"), Bikers("#TEAM_BIKER"), The Mafia("#TEAM_MAFIA")");

			SendClientMessage(playerid, COLOR_GRAYWHITE, "Депортамент: DoT("#DoT"), FBI("#FBI"), DoD("#DoD"), DoH("#DoH"), DoJ("#DoJ"), DoE("#DoE")");
			SendClientMessage(playerid, COLOR_GRAYWHITE, "Семьи: LaCosaNostra("#LCN"), Yakuza("#Yakuza")");
			SendClientMessage(playerid, COLOR_GRAYWHITE, "Агентства: Hitman("#Hitman"), SAN("#SAN")");
			return 1;
		}
		giveplayerid = ReturnUser(tmp);
		new playername[MAX_PLAYER_NAME];
		strmid(playername, tmp, 0, strlen(tmp), MAX_PLAYER_NAME);

		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /makeleader [playerid/PartOfName] [Number(1-19)(0-UnInvite)]");

			SendClientMessage(playerid, COLOR_GRAYWHITE, "Банды: Grove Street("#TEAM_GROVE"), The Ballas("#TEAM_BALLAS"), Varios Los Aztecas("#TEAM_AZTEC"), Los Santos Vagos("#TEAM_VAGOS")");
			SendClientMessage(playerid, COLOR_GRAYWHITE, "Банды: Da Nang Boys("#TEAM_NANG"), San Fierro Rifa("#TEAM_RIFA "), The Traids("#TEAM_TRIAD"), Bikers("#TEAM_BIKER"), The Mafia("#TEAM_MAFIA")");

			SendClientMessage(playerid, COLOR_GRAYWHITE, "Депортамент: DoT("#DoT"), FBI("#FBI"), DoD("#DoD"), DoH("#DoH"), DoJ("#DoJ"), DoE("#DoE")");
			SendClientMessage(playerid, COLOR_GRAYWHITE, "Семьи: LaCosaNostra("#LCN"), Yakuza("#Yakuza")");
			SendClientMessage(playerid, COLOR_GRAYWHITE, "Агентства: Hitman("#Hitman"), SAN("#SAN")");
			return 1;
		}
		new family = strval(tmp);

		if( (family < TEAM_GROVE || family > DoE) && family != TEAM_NONE) { SendClientMessage(playerid, COLOR_GREY, "   Не допустима цифра менее "#TEAM_GROVE", или больше "#DoE"!"); return 1; }

   	 	/*if( PlayerInfo[playerid][pLeader] == DoJ && PlayerInfo[playerid][pAdmin] != 5 && PlayerInfo[playerid][pAdmin] != 7
			&& family != TEAM_NONE)
   	 	{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены назначать лидеров! Только снимать при нарушениях!");
			return 1;
   	 	}*/
   	 	if( PlayerInfo[playerid][pLeader] == DoJ && //PlayerInfo[playerid][pAdmin] == 5 &&
			(family >= TEAM_GROVE && family <= TEAM_MAFIA) && family != TEAM_NONE)
   	 	{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены назначать лидеров банд! Можно назначать только лидеров фракций!");
			return 1;
   	 	}
   	 	/*if( PlayerInfo[playerid][pLeader] == DoJ && PlayerInfo[playerid][pAdmin] != 5 &&
			family != TEAM_NONE &&
			((family >= TEAM_GROVE && family <= TEAM_MAFIA) ||
			family == LCN || family == Yakuza || family == Hitman)
		  )
   	 	{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены назначать лидеров банд! Можно назначать только лидеров министерств!");
			return 1;
   	 	}*/
        if( PlayerInfo[playerid][pAdmin] == 2 &&
        	!(family >= TEAM_GROVE && family <= TEAM_MAFIA) && family != TEAM_NONE)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены назначать лидеров фракции!  Можно назначать только лидеров банд!");
		    return 1;
		}

		if( strcmp(FamilyInfo[family][fLeader], "No-One", true) && PlayerInfo[playerid][pAdmin] < 6)
		{//если лидер какой то есть
			format(strcmd, sizeof(strcmd), "AdmCmd: Действующий лидер %s фракции %s. Вы не можете назначить второго лидера!",
				FamilyInfo[family][fLeader], GetFamilyName(family));
			SendClientMessage(playerid, COLOR_GREY, strcmd);
			return 1;
		}

	    if( !IsPlayerConnected(giveplayerid) && giveplayerid != playerid)
	    {   //если снимается неиграющий с поста лидера
			SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не присоединился к игре !");

			if( PlayerInfo[playerid][pAdmin] != 2 && PlayerInfo[playerid][pAdmin] != 5 && PlayerInfo[playerid][pAdmin] != 7 && PlayerInfo[playerid][pAdmin] != 9)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
				return 1;
			}
			if(CheckExistPlayer(playerid, playername) == 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Это имя не зарегистрировано или указано не верно !");
				return 1;
			}
#if defined vw_sql//#endif
    		giveplayerid = MAX_PLAYERS-2;
			//if(mysql_retrieve_row()) OnPlayerLoadParameters(giveplayerid, playername);
			OnPlayerLoadParameters(giveplayerid, playername);
#endif

	   	 	if(family == TEAM_NONE)
	   	 	{//если снимаем лидерку
				format(strcmd, sizeof(strcmd), "AdmCmd: %s лишил Лидерки %s'а фракции %s.", PlayerName(playerid), playername, GetFamilyName(PlayerInfo[giveplayerid][pLeader]));
				Log(INVITE,strcmd);
				PlayerInfo[giveplayerid][pLeader] = 0;
				SendClientMessage(giveplayerid, COLOR_RED, strcmd);
				SendClientMessage(playerid, COLOR_RED, strcmd);
				//UninvitePlayerid(playerid, giveplayerid, PlayerName(giveplayerid));//не уволнять

				OnPlayerSaveParameters(giveplayerid, playername);
				/*format(strcmd, sizeof(strcmd), "   Bы лишили Лидерки %s'а. Ранг остался прежним.", playername);
				SendClientMessage(playerid, COLOR_RED, strcmd);
				format(strcmd, sizeof(strcmd), "   Вы были лишены лидерки фракции %s'а админом %s. Ранг остался прежним.", playername, PlayerName(playerid));
				SendClientMessage(playerid, COLOR_RED, strcmd);*/
				return 1;
	   	 	}
	 		if(	PlayerInfo[giveplayerid][pMember] > 0 && PlayerInfo[giveplayerid][pMember] < MAX_FAMILY
			  	&& PlayerInfo[playerid][pAdmin] != 9)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Игрок уже состоит в какой-то фракции!");
				return 1;
			}
			MakeLeader(playerid, giveplayerid, playername, family);
			//if(PlayerInfo[playerid][pMember] == DoJ) strmid(FamilyInfo[family][fLeader], playername, 0, strlen(playername), MAX_PLAYER_NAME);
			OnPlayerSaveParameters(giveplayerid, playername);
			OnPlayerInit(giveplayerid);//очистка
			return 1;
		}//not connected
		else if(IsPlayerConnectedEx(giveplayerid))
		{
			if( PlayerInfo[playerid][pLeader] != DoJ &&
				PlayerInfo[playerid][pAdmin] < 5 && PlayerInfo[playerid][pAdmin] != 2)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
				return 1;
			}
#if defined vw_sql//#endif
			/*new ToBase[64+24+2];
			format(ToBase, sizeof(ToBase), "SELECT `IND` FROM `blacklist` WHERE `Player`='%s' AND Family=%d", PlayerName(giveplayerid), DoE+1);
			mysql_query(ToBase); mysql_store_result();
			if(mysql_num_rows() > 0)
		 	{
				mysql_free_result();
	       		SendClientMessage(playerid, COLOR_GREY, "   Нельзя назначать игроков находящихся в Админском Чёрном Списке !");
				return 1;
			}
			mysql_free_result();*/

			new ToBase[64+24+2];
			format(ToBase, sizeof(ToBase), "SELECT `IND` FROM `blacklist` WHERE `Player`='%s' AND `Family`=%d", PlayerName(giveplayerid), DoE+1);
			new DBResult:db_result = db_query(db_VW, ToBase);
			if(db_num_rows(db_result))
		 	{
				db_free_result(db_result);
	       		SendClientMessage(playerid, COLOR_GREY, "   Нельзя назначать игроков находящихся в Админском Чёрном Списке !");
				return 1;
			}
			db_free_result(db_result);
#endif
	   	 	if(family == TEAM_NONE)
	   	 	{//если снимаем лидерку
				format(strcmd, sizeof(strcmd), "AdmCmd: %s лишил Лидерки %s'а из фракции %s. Ранг остался прежним.",
					PlayerName(playerid), PlayerName(giveplayerid), GetFamilyName(PlayerInfo[giveplayerid][pLeader]));
				PlayerInfo[giveplayerid][pLeader] = 0;
				Log(INVITE,strcmd);
				SendClientMessage(giveplayerid, COLOR_RED, strcmd);
				SendClientMessage(playerid, COLOR_RED, strcmd);

				//format(strcmd, sizeof(strcmd), "   Bы лишили Лидерки %s'а. Ранг остался прежним.", PlayerName(giveplayerid));
				//SendClientMessage(playerid, COLOR_RED, strcmd);
				return 1;
	   	 	}
	 		if(PlayerInfo[giveplayerid][pMember] > 0 && PlayerInfo[giveplayerid][pMember] < MAX_FAMILY)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Игрок уже состоит в какой-то фракции. Для начала необходимо ему уволиться (USE: /uninvite)!");
				return 1;
			}
		    if(	PlayerInfo[playerid][pAdmin] != 2 && PlayerInfo[playerid][pAdmin] != 5 &&
				PlayerInfo[playerid][pAdmin] != 6 && PlayerInfo[playerid][pAdmin] != 7 && PlayerInfo[playerid][pAdmin] != 9)
		    {
		   	 	new adminid = -1;
				for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) ) continue;
					//если игрок подключен
					if(PlayerInfo[i][pAdmin] != 5) continue;// && PlayerInfo[i][pAdmin] < 10
					if(AFK_IdleTime[i] >= 3) continue;
					adminid = i;
				}
		   	 	if( adminid == -1)// && PlayerInfo[playerid][pAdmin] != 2
		   	 	{
					SendClientMessage(playerid, COLOR_GREY, "   Нет гейм-админов, чтобы принять ваше предложение !");
					return 1;
		   	 	}
				Offer[adminid] = giveplayerid;
				SetPVarInt(adminid, "ProposedFamily", family);

				new msgitem[MAX_STRING+39];
				format(msgitem, sizeof(msgitem), "%s[%d]\
\nпредлогает сделать %s[%d] лидером фракции %s[%d]\
\n\nВыберите Accept, чтобы принять.", PlayerName(playerid), playerid, PlayerName(giveplayerid), giveplayerid, GetFamilyName(family), family);

				MenuOperation[adminid] = 14;
				ShowPlayerDialogEx(adminid, ACCEPT_DIALOG, DIALOG_STYLE_MSGBOX, "Make Leader", msgitem, "Accept", "Cancel");
			}
			else MakeLeader(playerid, giveplayerid, PlayerName(giveplayerid), family);
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   Нельзя назначать Offline лидеров!");
			//return 1;
		}
		//return 1;
	}
	//==========================================================================
	//для банд начало
	else if(!strcmp(cmd, "/setfamily", true))
	{
        if(	PlayerInfo[playerid][pAdmin] != 7 &&
			PlayerInfo[playerid][pAdmin] != 9)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
		    return 1;
		}
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /setfamily [number] [playerid/PartOfName]");
			return 1;
		}
		new family = strval(tmp);
		if(family != 0 && (family < TEAM_GROVE || family > DoE))
		{
			SendClientMessage(playerid, COLOR_GREY, "Hомер может быть от "#TEAM_GROVE" до "#DoE"! Сделать гражданским: 0 !");
			return 1;
		}
		tmp = strtok(cmdtext, idx);
		giveplayerid = ReturnUser(tmp);

		if(PlayerInfo[giveplayerid][pMember] >= TEAM_GROVE)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Игрок находится в Организации (USE: /uninvite)!");
			return 1;
		}
	    if( !IsPlayerConnected(giveplayerid) )
		{
			format(strcmd, sizeof(strcmd), "   ID:%d отсутствует на сервере.", giveplayerid); SendClientMessage(playerid, COLOR_GREY, strcmd);
			return 1;
		}
		if(PlayerInfo[giveplayerid][pMember] > 0) FamilyInfo[PlayerInfo[giveplayerid][pMember]][fMembers] --;
		PlayerInfo[giveplayerid][pMember] = family;
		FamilyInfo[family][fMembers] ++;

        format(strcmd, sizeof(strcmd), "* %s сделал Bас членом %s.", PlayerName(playerid), GetFamilyName(family));
       	SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, strcmd);
		format(strcmd, sizeof(strcmd), "AdmCmd: %s set %s's fraction %s", PlayerName(playerid), PlayerName(giveplayerid), GetFamilyName(family));
       	SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);
  		Log(ADMINLOG, strcmd);

		InviteList(playerid, PlayerName(giveplayerid), family, PlayerInfo[giveplayerid][pRank], 1);
		//return 1;
	}
	else if(!strcmp(cmd, "/SetFamilyBank", true) || !strcmp(cmd, "/SFB", true))///families
	{
		if(PlayerInfo[playerid][pAdmin] != 7 && PlayerInfo[playerid][pAdmin] != 9)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
		    return 1;
		}
        tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
        {
            SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /SetFamilyBank [gangs] [ammount]");
            return 1;
        }
        new family = strval(tmp);
      	if(family < TEAM_GROVE || family > DoE)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Номер может быть от "#TEAM_GROVE" до "#DoE" !");
			return 1;
		}
		if(FamilyInfo[family][NumberFamily] == 0)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Этот № не Востребован пока !");//Этот FamilyNr не Требуется пока
		    return 1;
		}
        tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
        {
            SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /SetFamilyBank [gangs] [ammount]");
            return 1;
        }
        new ammount = strval(tmp);
        if(ammount < 0) { SendClientMessage(playerid, COLOR_GREY, "   Значение не может быть меньше 0 !"); return 1; }
		FamilyInfo[family][fBank] = ammount;
		format(strcmd, sizeof(strcmd), "AdmCmd: %s set Gangs %d fBank $%d.", PlayerName(playerid), family, ammount);
       	SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);
  		Log(ADMINLOG, strcmd);
		//return 1;
	}
	else if(!strcmp(cmd, "/setmaterial", true) || !strcmp(cmd, "/sm", true))
	{
		if(	PlayerInfo[playerid][pAdmin] != 6 &&
			PlayerInfo[playerid][pAdmin] != 7 &&
			PlayerInfo[playerid][pAdmin] != 9)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
		    return 1;
		}
        tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
        {
            SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /setmaterial [gangs] [ammount]");

			SendClientMessage(playerid, COLOR_GRAYWHITE, "Банды: Grove Street("#TEAM_GROVE"), The Ballas("#TEAM_BALLAS"), Varios Los Aztecas("#TEAM_AZTEC"), Los Santos Vagos("#TEAM_VAGOS")");
			SendClientMessage(playerid, COLOR_GRAYWHITE, "Банды: Da Nang Boys("#TEAM_NANG"), San Fierro Rifa("#TEAM_RIFA "), The Traids("#TEAM_TRIAD"), Bikers("#TEAM_BIKER"), The Mafia("#TEAM_MAFIA")");

			SendClientMessage(playerid, COLOR_GRAYWHITE, "Депортамент: DoT("#DoT"), FBI("#FBI"), DoD("#DoD"), DoH("#DoH"), DoJ("#DoJ"), DoE("#DoE")");
			SendClientMessage(playerid, COLOR_GRAYWHITE, "Семьи: LaCosaNostra("#LCN"), Yakuza("#Yakuza")");
			SendClientMessage(playerid, COLOR_GRAYWHITE, "Агентства: Hitman("#Hitman"), SAN("#SAN")");
			return 1;
        }
        new family = strval(tmp);
      	if(family < TEAM_GROVE || family > DoE)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Номер может быть от "#TEAM_GROVE" до "#DoE" !");
			return 1;
		}
		if(FamilyInfo[family][NumberFamily] == 0)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Этот № не Востребован пока !");//Этот FamilyNr не Требуется пока
		    return 1;
		}
        tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
        {
            SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /setmaterial [gangs] [ammount]");
            return 1;
        }
        new ammount = strval(tmp);
        if(ammount < 0) { SendClientMessage(playerid, COLOR_GREY, "   Значение не может быть меньше 0 !"); return 1; }
		FamilyInfo[family][fMaterial] = ammount;
		format(strcmd, sizeof(strcmd), "AdmCmd: %s set Gangs %d fMaterial $%d.", PlayerName(playerid), family, ammount);
       	SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);
  		Log(ADMINLOG, strcmd);
		//return 1;
	}
	else if(!strcmp(cmd, "/setfamilymembers", true) || !strcmp(cmd, "/sfm", true))
	{
        if(	PlayerInfo[playerid][pLeader] != DoJ &&
			PlayerInfo[playerid][pAdmin] != 5 &&
			PlayerInfo[playerid][pAdmin] != 9)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
		    return 1;
		}
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /setfamilymembers [GangNr] [amount]");// [Code]
			return 1;
		}
		new family = strval(tmp);
      	if(family < TEAM_GROVE || family > DoE)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Номер может быть от "#TEAM_GROVE" до "#DoE" !");
			return 1;
		}
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /setfamilymembers [GangNr] [amount]");// [code]
			return 1;
		}
		new amount;
		amount = strval(tmp);
		if(amount < 0 || amount > 43) { SendClientMessage(playerid, COLOR_GREY, "   Количество не может быть менее 0 или больше 43 !"); return 1; }
		FamilyInfo[family][fMembers] = amount;

		//format(strcmd, sizeof(strcmd), "AdmCmd: %s установил Количество членов Банды %s - %d ", PlayerName(playerid), FamilyInfo[family][fName], amount);
		SaveFamiliesSQL(PlayerName(playerid));

		format(strcmd, sizeof(strcmd), "AdmCmd: %s set Gang: %s, Members: %d", PlayerName(playerid), FamilyInfo[family][fName], amount);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);
		Log(ADMINLOG,  strcmd);
		//return 1;
	}

	else if(!strcmp(cmd, "/giveturf", true))
	{
        if(PlayerInfo[playerid][pAdmin] != 2 && PlayerInfo[playerid][pAdmin] != 9)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
		    return 1;
		}
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /giveturf [GangsNr]");
			return 1;
		}
		new family = strval(tmp);
		if((family < TEAM_GROVE || family > TEAM_MAFIA) && PlayerInfo[playerid][pAdmin] != 9)
		{
			SendClientMessage(playerid, COLOR_GREY, "Hомер может быть от "#TEAM_GROVE" до "#TEAM_MAFIA"!");
			return 1;
		}
		if(FamilyInfo[family][NumberFamily] == 0 && PlayerInfo[playerid][pAdmin] != 9)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Этот FamilyNr не Востребован пока !");//Этот FamilyNr не Требуется пока
		    return 1;
		}
		new found = 0;
		for(new t=0; t<MAX_TURFS;t++)
		{   //сканируем все зоны
			if(IsPlayerInRegion(playerid, t))//если вы находитесь в КАКОЙ ТО зоне
			{
			    found = t+1;
				strmid(TurfInfo[t][zOwner], FamilyInfo[family][fName], 0, strlen(FamilyInfo[family][fName]), 255);//установить имя банды для той зоны
				TurfInfo[t][zFamily] = family;
				TurfInfo[t][zColor] = FamilyInfo[family][fColor];//присваиваем этой зоне новый цвет
				for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) ) continue;
					//сканируем всех игрок которым необходимо выводить данную информацию
					if(IsAGangs(i) || IsAFamilyMember(i) || PlayerInfo[i][pAdmin] == 2)
					{
						for(new tt = 0; tt < MAX_TURFS; tt++)//для зон банд MAX_TURFS
						{
							GangZoneHideForPlayer(i, Turfs[tt]);//спрятать зону Turfs[gangzone] для показа в другом цвете
							GangZoneShowForPlayer(i, Turfs[tt], TurfInfo[tt][zColor]);//Показать зону для игрока в том цвете которой она счас является
						}
						format(strcmd, sizeof(strcmd), "GangZone Message: квартал %s[%d] установлен банде %s", regions[t][region_name], t, FamilyInfo[family][fName]);
						SendClientMessage(i, FamilyInfo[family][fColor], strcmd);
					}
				}
				HasZoneAttacker[t] = 0;
				HasTakingZones[t] = 0;
				taketurfbackcount[t] = 0;
				TurfInfo[t][zFlash] = 0;
				taketurfcount[t] = TimeTakeZone;//устанавливаем время заново
				for(new b=0; b<MAX_BIZ; b++)
				{   //сканируем все бизы что находятся в данной зоне
					if( IsPointInRegion(BizInfo[b][bEntranceX], BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ], t) )//если биз находится в координатах по строке j из массива zones
					{   //если биз находится в данной зоне
						//strmid( BizInfo[b][bExtortion], FamilyInfo[family][fName], 0, 20, 255);
						BizInfo[b][bExtortion] = FamilyInfo[family][NumberFamily];
						SaveBiz(b);//сохраняем только те бизы, что в данной зоне
					}
				}
				for(new sb=0; sb<MAX_SBIZ; sb++)
				{   //сканируем все бизы что находятся в данной зоне
					if( IsPointInRegion(SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ], t) )//если биз находится в координатах по строке j из массива zones
					{   //если биз находится в данной зоне
						//strmid( SBizInfo[sb][sbExtortion], FamilyInfo[family][fName], 0, 20, 255);
						SBizInfo[sb][sbExtortion] = FamilyInfo[family][NumberFamily];
						SaveSBiz(sb);
					}
				}
				break;
			}
		}
		if(found > 0)
		{
      		SaveTurfsSQL();
			//SaveBizSQL();
			//SaveSBizSQL();
			format(strcmd, sizeof(strcmd), "AdmCmd: %s установил банде %s Turf: %d.", PlayerName(playerid), FamilyInfo[family][fName], found-1);
			Log(ADMINLOG,  strcmd);
			SendAllAdminMessage(COLOR_LIGHTBLUE, strcmd, 2);

		}
		else
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Вы не находитесь в Turf !");
		}
		//ИНФОРМИРОВАНИЕ
		//format(strcmd, sizeof(strcmd), "Turf: %s, zColor: %d", TurfInfo[200][zName], HexToInt( TurfInfo[200][zColor] ) );
		//ABroadCast(COLOR_MAROON, strcmd, 9);
		//SendClientMessageToAll(COLOR_YELLOW, strcmd);
		//return 1;
	}
	else if(!strcmp(cmd, "/raspredturf", true))
	{
        if(PlayerInfo[playerid][pAdmin] != 9)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
		    return 1;
		}
        for(new family = TEAM_GROVE; family <= TEAM_MAFIA; family++)
        {   //сканируем все банды
			for(new j=0; j<MAX_TURFS;j++)
			{   //сканируем все зоны
	        	if(TurfInfo[j][zFamily] == FamilyInfo[family][NumberFamily])
	        	{   //если эта зона принадлежит номеру этой банды
					for(new b=0; b<MAX_BIZ; b++)
					{   //сканируем все бизы что находятся в данной зоне
						if( IsPointInRegion(BizInfo[b][bEntranceX], BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ], j) )//если биз находится в координатах по строке j из массива zones
						{   //если биз находится в данной зоне
							//strmid( BizInfo[b][bExtortion], FamilyInfo[family][fName], 0, 20, 20);
							BizInfo[b][bExtortion] = FamilyInfo[family][NumberFamily];
							SaveBiz(b);
						}
					}
					for(new sb=0; sb<MAX_SBIZ; sb++)
					{   //сканируем все бизы что находятся в данной зоне
						if( IsPointInRegion(SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ], j) )//если биз находится в координатах по строке j из массива zones
						{   //если биз находится в данной зоне
							//strmid( SBizInfo[sb][sbExtortion], FamilyInfo[family][fName], 0, 20, 20);
							SBizInfo[sb][sbExtortion] = FamilyInfo[family][NumberFamily];
							SaveSBiz(sb);
						}
					}
				}
			}
		}
		ABroadCast(COLOR_LIGHTBLUE, "   Biz и SBiz скорректированы.", 9);
		//ИНФОРМИРОВАНИЕ
		//format(strcmd, sizeof(strcmd), "Turf: %s, zColor: %d", TurfInfo[200][zName], HexToInt( TurfInfo[200][zColor] ) );
		//ABroadCast(COLOR_MAROON, strcmd, 9);
		//SendClientMessageToAll(COLOR_YELLOW, strcmd);
		//return 1;
	}
	else if(!strcmp(cmd, "/resetturf", true))
	{
        if(PlayerInfo[playerid][pAdmin] != 9)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду!");
		    return 1;
		}
		for(new j=0; j<MAX_TURFS; j++)
		{
			//strmid(TurfInfo[j][zOwner], "No-One", 0, strlen("No-One"), 8);
			TurfInfo[j][zFamily] = 0;
			TurfInfo[j][zColor] = FamilyInfo[0][fColor];
			strmid(TurfInfo[j][zName], regions[j][region_name], 0, strlen(regions[j][region_name]), 20);
		}
		for(new b=0; b<MAX_BIZ; b++)
		{   //сканируем все бизы что находятся в данной зоне
			//strmid( BizInfo[b][bExtortion], "No-One", 0, 20, 20);
			BizInfo[b][bExtortion] = 0;
		}
		for(new sb=0; sb<MAX_SBIZ; sb++)
		{   //сканируем все бизы что находятся в данной зоне
			//strmid( SBizInfo[sb][sbExtortion], "No-One", 0, 20, 20);
			SBizInfo[sb][sbExtortion] = 0;
		}
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			//сканируем всех игрок которым необходимо выводить данную информацию
			if(IsAGangs(i) || IsAFamilyMember(i) || PlayerInfo[i][pAdmin] == 2)
			{
				for(new jj = 0; jj < MAX_TURFS; jj++)//для зон банд MAX_TURFS
				{
					GangZoneHideForPlayer(i, Turfs[jj]);
					GangZoneShowForPlayer(i, Turfs[jj], TurfInfo[jj][zColor]);
				}
			}
		}
		SaveTurfsSQL();
		ABroadCast(COLOR_LIGHTBLUE, "   Turfs скорректированы.", 9);
		//return 1;
	}
	//для банд конец

	else if(!strcmp(cmd, "/sound", true))
	{
		sound_ShowDialog(playerid);
		//return 1;
	}
	else if(!strcmp(cmd, "/nameoff", true))//для скрытия ников
	{
		if(	!(PlayerInfo[playerid][pMember] == SAN && PlayerInfo[playerid][pRank] >= 11) &&
			PlayerInfo[playerid][pAdmin] != 9)
		{
            SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
            return 1;
        }

        if(gTogNameTag == 1)
        {
        	gTogNameTag = 0;
			gTagForPlayer[playerid] = 0;
  		 	for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if(IsPlayerNPC(i)) continue;
				if(!gPlayerSpawned[i]) continue;
				if(PlayerInfo[i][pMember] == Hitman) continue;
				ShowPlayerNameTagForPlayerEx(playerid, i, 0);//для игрока playerid показать ники всех игроков
			}
	    	GameTextForPlayer(playerid, "~W~Nametags ~G~OFF", 5000, 5);
	    }
	    else
	    {
        	gTogNameTag = 1;
        	gTagForPlayer[playerid] = 0;
  		 	for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if(IsPlayerNPC(i)) continue;
				if(!gPlayerSpawned[i]) continue;
				if(PlayerInfo[i][pMember] == Hitman) continue;
				ShowPlayerNameTagForPlayerEx(playerid, i, 1);//для игрока playerid показать ники всех игроков
			}
	    	GameTextForPlayer(playerid, "~W~Nametags ~G~ON", 5000, 5);
	    }
	    return 1;
	}
	
	return 1;//0;
}


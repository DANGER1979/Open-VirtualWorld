//##############################################################################//
//                                                                              //
//               ВЫПОЛНЯЕТСЯ ПРИ СТАРТЕ РЕЖИМА ИЗ GameModeInit()                //
//                                                                              //
//##############################################################################//

		
//------------------------------------------------------------------------------





//##############################################################################//
//                                                                              //
//                           СПИСКИ ДЛЯ СТАТИСТИКИ                              //
//                                                                              //
//##############################################################################//
stock FinaceList(playerid, receipts, consuption, operation)//
{//receipts - доход, consuption - расход
	//if(TEST[61] != 0) return 1;//при 0 ф-ия работает
	//if(TEST[61] == 0) return 1;

#if defined STRIKEARENA_7777
	new timers = GetTickCount();

	/*new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld;	getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);*/

	/*new ToBase[140 +  14+12+10+11+24+10+10+10+10];
	format(ToBase, sizeof(ToBase), "INSERT INTO `finance` (`Article`,`Date`,`Time`,`ID`,`Name`,`Cash`,`Bank`,`Receipts`,`Consuption`) VALUES (%d,'%s','%s',%d,'%s',%d,%d,%d,%d)",
		operation, date, time, PlayerInfo[playerid][pSQLID], PlayerName(playerid), PlayerInfo[playerid][pCash], PlayerInfo[playerid][pBank], receipts, consuption);
	mysql_query(ToBase);*/

	new ToBase[185+1];//116 + 3+10+24+10+10+6+6 = 185
	format(ToBase, sizeof(ToBase), "INSERT INTO `finance` (`Article`,`ID`,`Name`,`Cash`,`Bank`,`Receipts`,`Consuption`) VALUES (%d,%d,'%s',%d,%d,%d,%d)",
		operation, PlayerInfo[playerid][pSQLID], PlayerName(playerid), PlayerInfo[playerid][pCash], PlayerInfo[playerid][pBank], receipts, consuption);
	mysql_query(ToBase);

	new strtmp[50];//26+24 = 50
	strcat(strtmp, "FinaceList ");
	strcat(strtmp, PlayerName(playerid));
	TestLog(OPTIM, strtmp, GetTickCount(), timers);//new timers = GetTickCount();

#else
	#pragma unused playerid
	#pragma unused receipts
	#pragma unused consuption
	#pragma unused operation
#endif
	return 1;
}

stock CriminalList(playerid, turner[], const reason[], status)//108 ms -  938 ms
{//playerid - убийца
//0 - ничего, 1 - преступление, 2 - арест, 3 - перевод
	//if(TEST[62] != 0) return 1;
	//if(TEST[62] == 0) return 1;

#if defined STRIKEARENA_7777
	new timers = GetTickCount();

	new playername[MAX_PLAYER_NAME];
	if(playerid != MAX_PLAYERS-1)
	{
		GetPlayerName(playerid, playername, sizeof(playername));
	}
	else strmid(playername, "CEPBEP", 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);

	new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld;	getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

	new ToBase[328+1];//118 +  12+10+11+24+24+128+1 = 328
	format(ToBase, sizeof(ToBase), "INSERT INTO `criminallist` (`Date`,`Time`,`ID`,Player,Turner,Reason,`Status`) VALUES ('%s','%s',%d,'%s','%s','%s',%d)",
		date, time, PlayerInfo[playerid][pSQLID], playername, turner, reason, status);
	mysql_query(ToBase);

	new strtmp[50];//26+24 = 50
	strcat(strtmp, "CriminalList ");
	strcat(strtmp, PlayerName(playerid));
	TestLog(OPTIM, strtmp, GetTickCount(), timers);//new timers = GetTickCount();

//#elseif defined STRIKEARENA_7778

#else
	#pragma unused playerid
	#pragma unused turner
	#pragma unused reason
	#pragma unused status
#endif


	return 1;
}

stock KillList(playerid, killerid, family, rank, reason)//100 ms - 824 ms
{//playerid - убитый
	//if(TEST[63] != 0) return 1;

#if defined STRIKEARENA_7777

	if(gRealWar) return 1;
	if(gPlayerBoxing[killerid]) return 1;
	if(gInTerrorsCount[killerid]) return 1;
	if(gInCTerrorsCount[killerid]) return 1;
	if(LastKill[killerid] == playerid) return 1;// || LastKill[killerid] == MAX_PLAYERS-1

	/*if(TEST[63] == 0)
	{
	    new strtmp[45+24+3+24+3+32+3];
		format(strtmp, sizeof(strtmp), "player:%s[%d], killer:%s[%d], weapon: %s[%d]",
			PlayerName(playerid), playerid, PlayerName(killerid), killerid, GetDeathReason(killerid, reason), reason);
		Log(KILL, strtmp);
		return 1;
	}*/

	new timers = GetTickCount();

	new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld;	getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

	new ToBase[215];//128 +  12+10+24+11+24+2+2+2 = 215
	format(ToBase, sizeof(ToBase), "INSERT INTO `killlist` (`Date`,`Time`,`Player`,`ID`,`Killer`,`Family`,`Rank`,`Weapon`) VALUES ('%s','%s','%s',%d,'%s',%d,%d,%d)",
		date, time, PlayerName(playerid),
		PlayerInfo[killerid][pSQLID], PlayerName(killerid), family, rank, reason);
	mysql_query(ToBase);

	new strtmp[50];//26+24 = 50
	strcat(strtmp, "KillList ");
	strcat(strtmp, PlayerName(playerid));
	TestLog(OPTIM, strtmp, GetTickCount(), timers);//new timers = GetTickCount();

#else
	#pragma unused playerid
	#pragma unused killerid
	#pragma unused family
	#pragma unused rank
	#pragma unused reason
#endif
	return 1;
}

stock InviteList(playerid, giveplayername[], family, rank, status)
{//status 0 - уволен, 1 - принят
#if defined STRIKEARENA_7777

	new playername[MAX_PLAYER_NAME];
	if(playerid != MAX_PLAYERS-1 && playerid != MAX_PLAYERS-2)
	{
		GetPlayerName(playerid, playername, sizeof(playername));
	}
	else strmid(playername, "CEPBEP", 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);

	if(!strcmp(playername, giveplayername, true)) return 1;//если сам себя принял, то в лог не писать

	new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld;	getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

	new ToBase[126 +  12+10+24+24+2+2+1];
	format(ToBase, sizeof(ToBase), "INSERT INTO `invitelist` (`Date`, `Time`, Player, Leader, Family, Rank, `Status`) VALUES ('%s', '%s', '%s', '%s', %d, %d, %d)",
		date, time, giveplayername, playername, family, rank, status);
	mysql_query(ToBase);

#else
	#pragma unused playerid
	#pragma unused giveplayername
	#pragma unused family
	#pragma unused rank
	#pragma unused status
#endif
	return 1;
}

stock BlackList(playerid, family, giveplayername[], reason[])
{
	//if(forplayerid == INVALID_PLAYER_ID) return 1;

#if defined STRIKEARENA_7777

	new playername[MAX_PLAYER_NAME];
	GetPlayerName(playerid, playername, sizeof(playername));

	new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld; getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

	new ToBase[109 + 12+10+24+2+24+128];
	format(ToBase, sizeof(ToBase), "INSERT INTO `blacklist` (`Date`,`Time`, Player,Family,Leader, Reason) VALUES ('%s','%s', '%s',%d,'%s', '%s')",
		date, time, giveplayername, family, playername, reason);
	mysql_query(ToBase);

#else
	#pragma unused playerid
	#pragma unused family
	#pragma unused giveplayername
	#pragma unused reason
#endif
}

stock WarnList(adminname[], forplayerid, days, const reason[])
{
#if defined STRIKEARENA_7777
	new playername[MAX_PLAYER_NAME];
	if(IsPlayerConnected(forplayerid))
	{
		GetPlayerName(forplayerid, playername, sizeof(playername));
	}
	new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld;	getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

	new ToBase[142 + 24 + 1+2 + 16 + 12+10 + 24 + 128 + 3];
	format(ToBase, sizeof(ToBase), "INSERT INTO `warnlist` (Player,AdminLevel,`Level`,IP,`Date`,`Time`,Admin,Reason,Days) VALUES ('%s', %d, %d, '%s', '%s', '%s', '%s', '%s', %d)",
		playername, PlayerInfo[forplayerid][pAdmin], PlayerInfo[forplayerid][pLevel],
		PlayerInfo[forplayerid][pIP], date, time, adminname, reason, days);
	mysql_query(ToBase);
#else
	#pragma unused adminname
	#pragma unused forplayerid
	#pragma unused days
	#pragma unused reason
#endif
}

stock BanList(adminname[], forplayerid, days, const reason[])
{
#if defined STRIKEARENA_7777

	new playername[MAX_PLAYER_NAME];
	if(IsPlayerConnected(forplayerid))
	{
		GetPlayerName(forplayerid, playername, sizeof(playername));
	}

	new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld;	getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

	new ToBase[142 + 24 + 1+2 + 16 + 12+10 + 24 + 128 + 3];
	format(ToBase, sizeof(ToBase), "INSERT INTO `banlist` (Player,AdminLevel,`Level`,IP,`Date`,`Time`,Admin,Reason,Days) VALUES ('%s', %d, %d, '%s', '%s', '%s', '%s', '%s', %d)",
		playername, PlayerInfo[forplayerid][pAdmin], PlayerInfo[forplayerid][pLevel],
		PlayerInfo[forplayerid][pIP], date, time, adminname, reason, days);
	mysql_query(ToBase);

/*#if defined STRIKEARENA_7778
	new playername[MAX_PLAYER_NAME];
	if(IsPlayerConnected(forplayerid))
	{
		GetPlayerName(forplayerid, playername, sizeof(playername));
	}
	new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld;	getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

	new ToBase[142 + 24 + 1+2 + 16 + 12+10 + 24 + 128 + 3];
	format(ToBase, sizeof(ToBase), "INSERT INTO `banlist` (Player,AdminLevel,`Level`,IP,`Date`,`Time`,Admin,Reason,Days) VALUES ('%s', %d, %d, '%s', '%s', '%s', '%s', '%s', %d)",
		playername, PlayerInfo[forplayerid][pAdmin], PlayerInfo[forplayerid][pLevel],
		PlayerInfo[forplayerid][pIP], date, time, adminname, reason, days);
	mysql_query(ToBase);
#elseif defined STRIKEARENA_7777*/

#else
	#pragma unused adminname
	#pragma unused forplayerid
	#pragma unused days
	#pragma unused reason
#endif

}

stock UnBanList(playername[], adminid, reason[])
{

#if defined STRIKEARENA_7777
	new adminname[MAX_PLAYER_NAME];
	GetPlayerName(adminid, adminname, sizeof(adminname));

	new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld;	getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

	//mysql_real_escape_string(playername, playername);
	//mysql_real_escape_string(date, date);
	//mysql_real_escape_string(time, time);
	//mysql_real_escape_string(adminname, adminname);
	//mysql_real_escape_string(reason, reason);

	new ToBase[98 + 24 + 12+10 + 24 + 128];
	format(ToBase, sizeof(ToBase), "INSERT INTO `unbanlist` (Player,`Date`,`Time`,Admin,Reason) VALUES ('%s', '%s', '%s', '%s', '%s')",
		playername,
		date, time,
		adminname, reason);
	mysql_query(ToBase);

	//format(strings, sizeof(strings), "[%d:%02d:%02d] AdmCmd: %s was unbanned by %s's.",  lH,lM,lS, playername, adminname);
	//Log(BAN,strcmd);
	//format(strcmd, sizeof(strcmd), "[%d:%02d:%02d] %s", lH,lM,lS, strcmd);
	//SendClientMessageToAll(COLOR_RED, strings);

/*#if defined STRIKEARENA_7778
	new adminname[MAX_PLAYER_NAME];
	GetPlayerName(adminid, adminname, sizeof(adminname));

	new date[12], time[10];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld;	getdate(ly,lmm,ld);
	format(date, sizeof(date), "%04d-%02d-%02d", ly,lmm,ld);
	format(time, sizeof(time), "%02d:%02d:%02d", lH,lM,lS);

	//mysql_real_escape_string(playername, playername);
	//mysql_real_escape_string(date, date);
	//mysql_real_escape_string(time, time);
	//mysql_real_escape_string(adminname, adminname);
	//mysql_real_escape_string(reason, reason);

	new ToBase[98 + 24 + 12+10 + 24 + 128];
	format(ToBase, sizeof(ToBase), "INSERT INTO `unbanlist` (Player,`Date`,`Time`,Admin,Reason) VALUES ('%s', '%s', '%s', '%s', '%s')",
		playername,
		date, time,
		adminname, reason);
	mysql_query(ToBase);

	//format(strings, sizeof(strings), "[%d:%02d:%02d] AdmCmd: %s was unbanned by %s's.",  lH,lM,lS, playername, adminname);
	//Log(BAN,strcmd);
	//format(strcmd, sizeof(strcmd), "[%d:%02d:%02d] %s", lH,lM,lS, strcmd);
	//SendClientMessageToAll(COLOR_RED, strings);
#elseif defined STRIKEARENA_7777*/

#else
	#pragma unused playername
	#pragma unused adminid
	#pragma unused reason
#endif

}

stock list_OnPlayerDisconnect(playerid)
{
	//для монитора
	PlayerInfo[playerid][pOffline] = getdate();//записали день выхода с серва
//TestLog(OPTIM, "OnPlayerDisconnect1.1", GetTickCount(), timers, 1);
	new ToBase[87];//60 + 3+24 = 87
    if(PlayerInfo[playerid][pSQLID] > 0)
    {
		format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Offline`=%d WHERE `ID`=%d",
			PlayerInfo[playerid][pOffline], PlayerInfo[playerid][pSQLID]);
	}
	else
	{
		format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Offline`=%d WHERE `Name`='%s'",
			PlayerInfo[playerid][pOffline], PlayerName(playerid));
	}
	mysql_query(ToBase);
}



stock NetList(playerid)
{
	new dlgitem[50*(13+24+3+5)];
	new str[13+24+3+5];
	new count;
	new stats[418+1];
	new playername[MAX_PLAYER_NAME];
	strins(dlgitem, "______________________________\nNetList:\n",strlen(dlgitem));
	//for(new j=0, i; j<MaxPlayers; j++)	{
		//i = PLIDs[j];
	for(new i=0; i<GetMaxPlayers(); i++) {
		if( !IsPlayerConnected(i) ) continue;
		if( IsPlayerNPC(i) ) continue;
		if(count >= 50) break;
        GetPlayerNetworkStats(i, stats, sizeof(stats)); // get your own networkstats
		new mss = strval(findParam(stats, "Messages sent: "));
		if( (mss - nMessages[i]) < 10) continue;

		GetPlayerName(i, playername, sizeof(playername));
		format(str, sizeof(str), "%d\t%s\t%d\n", i, playername, (mss - nMessages[i]));
		strins(dlgitem, str, strlen(dlgitem));
  		count++;
	}
	strins(dlgitem, "\n______________________________\n", strlen(dlgitem), 35);
	if(strlen(dlgitem) >= sizeof(dlgitem) || strlen(dlgitem) <= 0)
	{
		//ИНФОРМИРОВАНИЕ
		new strtmp[56+4+4+12];
		format(strtmp, sizeof(strtmp), "Error: NetList strlen(dlgitem): %d, sizeof(dlgitem): %d",
			strlen(dlgitem), sizeof(dlgitem));
		Log(ERROR, strtmp);
		return 1;
	}
	ShowPlayerDialogGap(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, "     id         name                              messages", dlgitem, "OK", "");
	return 1;
}

//для серийников
stock SerialList(playerid)
{
	new dlgitem[30*(15+2+20+64)];
	//new strings[MAX_STRING];
	//strins(dlgitem, "______________________________\nSerialList:\n",strlen(dlgitem));
	new serialid[64];//164
	new playername[MAX_PLAYER_NAME];
	new count;
	//for(new i=0; i<GetMaxPlayers(); i++)//сканируем всех
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		//if( IsPlayerNPC(i) ) continue;
		//if(count >= 30) break;
		gpci(i, serialid, sizeof(serialid));
		GetPlayerName(i, playername, sizeof(playername));
		if(strlen(playername) < 14) format(strings, sizeof(strings), "%d\t%s\t\t%s\n", i, playername, serialid);
		else format(strings, sizeof(strings), "%d\t%s\t%s\n", i, playername, serialid);
		strins(dlgitem, strings, strlen(dlgitem), strlen(strings));
  		count++;
	}//DIALOG_STYLE_LIST
	//strins(dlgitem, "\n______________________________\n", strlen(dlgitem), 35);
	if(strlen(dlgitem) >= sizeof(dlgitem) || strlen(dlgitem) <= 0)
	{
		//ИНФОРМИРОВАНИЕ
		new strtmp[59+4+4+12];
		format(strtmp, sizeof(strtmp), "Error: SerialList strlen(dlgitem): %d, sizeof(dlgitem): %d",
			strlen(dlgitem), sizeof(dlgitem));
		//ShowPlayerDialogGap(playerid, 101, DIALOG_STYLE_MSGBOX, "SerialList", strtmp, "OK", "");
		//SendClientMessage(playerid, 0x6EF83CFF, strtmp);
		Log(ERROR, strtmp);
		return 1;
	}
	ShowPlayerDialogGap(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, "     id         name                              serial", dlgitem, "OK", "");
	return 1;
}


//##############################################################################//
//                                                                              //
//                  СПИСКИ сформированные из базы данных                         //
//                                                                              //
//##############################################################################//


stock ShowPlayerBans(playerid)
{
	if(!IsPlayerConnected(playerid)) return 1;
	new GetStepPlayer = GetPVarInt(playerid, "TempStep");

	new Field[24], Data[1024];
	new CurrentStatus;
	new idx = GetStepPlayer;
	new TempName[MAX_PLAYER_NAME];
	new BaseID, TimeForBan, Money, House, Biz;

	new ToBase[128];
	format(ToBase, sizeof(ToBase), "SELECT Name,ID,Warns,Cash,House,Bizz FROM `players` WHERE Level=-999 AND Warns>%d LIMIT %d, %d", getdate(), GetStepPlayer, GetStepPlayer+21);
	mysql_query(ToBase); new Step = GetStepPlayer+20;
	mysql_store_result();
	if(mysql_num_rows() > 0)
 	{
 		new ResultRow[2024];
 	    strcat(ResultRow, "ID \tName \t\t\tBanTime \tCash \tHouse \tBizz\n______________________________________________________________________\n");
		while(mysql_fetch_row_format(Data, "|"))
		{
		    if(idx >= Step)
		    {
				SetPVarInt(playerid, "TempStep", idx);
				new info[24+3];
				new curdate = getdate();//Получает текущий день в году
				format(info, sizeof(info), "BANS LIST ON THE %d DAY", curdate);
		        ShowPlayerDialogEx(playerid, BANLIST_DIALOG, DIALOG_STYLE_MSGBOX, info, ResultRow, "Next", "Cancel");
		        mysql_free_result();
				return 1;
		    }
  			mysql_fetch_field_row(Field, "Name");
            strmid(TempName, Field, 0, strlen(Field), MAX_PLAYER_NAME);
            mysql_fetch_field_row(Field, "ID");
            BaseID = strval(Field);
            mysql_fetch_field_row(Field, "Warns");
            TimeForBan = strval(Field);
           	mysql_fetch_field_row(Field, "Cash");
            Money = strval(Field);
           	mysql_fetch_field_row(Field, "House");
            House = strval(Field);
           	mysql_fetch_field_row(Field, "Bizz");
            Biz = strval(Field);
			if(strlen(TempName) == 13)
			{
            	format(ResultRow, sizeof(ResultRow), "%s%d \t%s \t\t%d \t\t%d \t%d \t%d\n", ResultRow,BaseID,TempName,TimeForBan,Money,House,Biz);
            }
			else if(strlen(TempName) < 13)
			{
            	format(ResultRow, sizeof(ResultRow), "%s%d \t%s \t\t%d \t\t%d \t%d \t%d\n", ResultRow,BaseID,TempName,TimeForBan,Money,House,Biz);
            }
            else
            {
                format(ResultRow, sizeof(ResultRow), "%s%d \t%s \t%d \t\t%d \t%d \t%d\n", ResultRow,BaseID,TempName,TimeForBan,Money,House,Biz);
            }
			idx ++;
		}
		CurrentStatus = GetPVarInt(playerid, "TempStep");
		if(GetStepPlayer != 0 && CurrentStatus < Step)
		{
		    SetPVarInt(playerid, "TempStep", CurrentStatus-20);
			mysql_free_result();
			new info[24+3];
			new curdate = getdate();//Получает текущий день в году
			format(info, sizeof(info), "BANS LIST ON THE %d DAY", curdate);
			ShowPlayerDialogEx(playerid, BANLIST_DIALOG, DIALOG_STYLE_MSGBOX, info, ResultRow, "Back", "Cancel");
			return 1;
		}
		else
		{
			mysql_free_result();
			new info[24+3];
			new curdate = getdate();//Получает текущий день в году
			format(info, sizeof(info), "BANS LIST ON THE %d DAY", curdate);
			ShowPlayerDialogEx(playerid, BANLIST_DIALOG, DIALOG_STYLE_MSGBOX, info, ResultRow, "Update", "Cancel");
			return 1;
		}
	}
	else { LIST(playerid); SendClientMessage(playerid, COLOR_GREY, "   Бан лист пуст!"); }
	return 1;
}
stock BANLIST_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != BANLIST_DIALOG) return 1;//44
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response)
	{
	    DeletePVar(playerid, "TempStep");
     	LIST(playerid);
	 	return 1;
	}
	//new msgitem[256+1];
	//new giveplayerid;
//ShowPlayerDialogEx(playerid, BANLIST_DIALOG, DIALOG_STYLE_MSGBOX, "BANS LIST", ResultRow, "Back", "Cancel");
	SetPVarInt(playerid, "gShowDialog", -1);
	ShowPlayerBans(playerid);
	return 1;
}




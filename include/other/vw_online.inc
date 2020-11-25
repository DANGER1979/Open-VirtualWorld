new OnlineRecordDate[24];
new OnlineRecordTime[24];
new OnlineRecord;

new LastWeekOnline[2][24];//дата
new LastOnline;//кол-во часов наигранных всеми игроками за прошлую неделю перезаписывается //если 23 вечера и сегодня понедельник
new WeekOnline;//кол-во часов наигранных всеми игроками за неделю

//файл всегда содержит 3 строки

stock online_OnGameModeInit()
{
	new time = GetTickCount();
	if( !fexist("Logs/online.ini") ) { ClearOnline(); return 1; }
	new File: oFile = fopen("Logs/online.ini", io_read);
	if( !oFile ) { return 1; }
	new idx;
    new strFromFile[35+2+2+4+2+2+2+3 + 12];
	while( fread(oFile, strFromFile) )
	{
		new arrCoords[3][24];
		if(idx == 0) {
			split(strFromFile, arrCoords, ',');
			strmid(OnlineRecordDate, arrCoords[0], 0, strlen(arrCoords[0]) );
			strmid(OnlineRecordTime, arrCoords[1], 0, strlen(arrCoords[1]) );
			OnlineRecord = strval(arrCoords[2]);
		}
		else if(idx == 1) {
			split(strFromFile, arrCoords, ',');
			strmid(LastWeekOnline[0], arrCoords[0], 0, strlen(arrCoords[0]) );
			strmid(LastWeekOnline[1], arrCoords[1], 0, strlen(arrCoords[1]) );
			LastOnline = strval(arrCoords[2]); }
		else if(idx == 2) { split(strFromFile, arrCoords, ','); WeekOnline = strval(arrCoords[2]); }
		//else if(idx == 3) { split(strFromFile, arrCoords, ','); WipeDay = strval(arrCoords[2]); }
		idx ++;
	}
	fclose(oFile);
	printf("15/19. [Загрузка онлайна]: Было загружено - %d, потрачено - %d (ms)", idx, (GetTickCount()-time));
	return 1;
}
stock SaveOnline()
{
	new File: oFile = fopen("Logs/online.ini", io_write);
	if( !oFile ) { return 1; }
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld; getdate(ly,lmm,ld);
	new coordsstring[70];
	format(coordsstring, sizeof(coordsstring), "%s,%s,%d\n",
		OnlineRecordDate, OnlineRecordTime, OnlineRecord);
	fwrite(oFile, coordsstring);
	format(coordsstring, sizeof(coordsstring), "%s,%s,%d\n",
		LastWeekOnline[0], LastWeekOnline[1], LastOnline);
	fwrite(oFile, coordsstring);
	format(coordsstring, sizeof(coordsstring), "%02d/%02d/%04d,%02d:%02d:%02d,%d\n",
		ld,lmm,ly, lH,lM,lS, WeekOnline);
	fwrite(oFile, coordsstring);
	//format(coordsstring, sizeof(coordsstring), "%02d/%02d/%04d,%02d:%02d:%02d,%d\n",
	//	ld,lmm,ly, lH,lM,lS, WipeDay);
	//fwrite(oFile, coordsstring);
	fclose(oFile);
	printf("Сохранение онлайна успешно завершено");
	return 1;
}
stock ClearOnline()
{
	new lH, lM, lS;	gettime(lH,lM,lS);
	new ly, lmm, ld; getdate(ly,lmm,ld);
	format(OnlineRecordDate, sizeof(OnlineRecordDate), "%02d/%02d/%04d", ld,lmm,ly);
	format(OnlineRecordTime, sizeof(OnlineRecordTime), "%02d:%02d:%02d", lH,lM,lS);
	OnlineRecord = 1;
	format(LastWeekOnline[0], 24, "%02d/%02d/%04d", ld,lmm,ly);
	format(LastWeekOnline[1], 24, "%02d:%02d:%02d", lH,lM,lS);
	LastOnline = 1;
	WeekOnline = 1;
	//WipeDay = getdate();
	SaveOnline();
	SendClientMessageToAll(COLOR_RED, "   Очистка онлайна успешна выполнена. ");
	//return 1;
}


stock CheckOnline()//Проверка онлайна STEP1
{   //вызывается каждый час из SyncTime
//если 23 вечера и сегодня понедельник
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld; getdate(ly,lmm,ld);
	format(LastWeekOnline[0], 24, "%02d/%02d/%04d", ld,lmm,ly);
	format(LastWeekOnline[1], 24, "%02d:%02d:%02d", lH,lM,lS);
	LastOnline = WeekOnline;
	WeekOnline = 0;

	if(!gCheckOnline) return 1;
	SendClientMessageToAll(COLOR_PINK, "Проверка онлайна начата!!!");

	//если сегодня 23:00 понедельник
	//mysql_query("SELECT * FROM `players` WHERE `Member`>="#DoT" AND `ConnectTime`-`Online`<14");// AND `Level`>0
	new query[166+3+2+2+2];
	format(query, sizeof(query), "SELECT * FROM `players` WHERE `Account`<%d AND \
(( `Member`>=%d AND `Member`<>%d AND (`ConnectTime`-`Online`)<7 ) OR ( `Member`=%d AND (`ConnectTime`-`Online`)<5 ))",
		getdate(),
		DoT, SAN,//для всех фракций кроме SAN минимальное допустимое время 7 и более часов в неделю
		SAN);
	mysql_query(query);
	mysql_store_result();//нашли всех лидеров у кого онлайн меньше 14 за неделю

	new Field[24]; //new idx;
	new Data[128 + 178+57+24+65+85+82 + 24 +12];//431
	while(mysql_fetch_row_format(Data, "|"))
	{   //ysql_fetch_row_format - выбирает целую строчку из установленного результата.
		new playername[MAX_PLAYER_NAME];//new Online;
		mysql_fetch_field_row(Field, "Name"); strmid(playername, Field, 0, strlen(Field), 24);
		//mysql_real_escape_string(playername, playername);
		new giveplayerid = ReturnUser( playername );
		if( !IsPlayerConnected(giveplayerid) )
		{
			giveplayerid = MAX_PLAYERS-2;
			OnPlayerLoadParameters(giveplayerid, playername);
		}

		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "%s {FFFFFF}%s[%d]: {FFFF00}покинул фракцию %s из-за низкого онлайна: %dч. за неделю.",
			GetPlayerRanks(giveplayerid), playername, giveplayerid, GetPlayerMembers(giveplayerid), PlayerInfo[giveplayerid][pConnectTime]-PlayerInfo[giveplayerid][pOnline]);
		OOCNews(COLOR_HERBAL, "|_____________________________________ Правительственное сообщение _____________________________________|");
		OOCNews(COLOR_LIGHTBLUE, strings);
		//OOCNews(COLOR_HERBAL, "|__________________________________________________________________________________________________________|");
		UninvitePlayerid(MAX_PLAYERS-1, giveplayerid, playername);

		if( !IsPlayerConnected(giveplayerid) ) { OnPlayerSaveParameters(giveplayerid, playername); OnPlayerInit(giveplayerid); }
		//else OnPlayerStatsUpdate(giveplayerid);
		//idx ++;
	}
	mysql_free_result();

	SaveFamiliesSQL("CEPBEP");
	SendClientMessageToAll(COLOR_PINK, "Проверка онлайна закончена!!!");
	return 1;
}



//##############################################################################//
//                                                                              //
//                               УДАЛЁННЫЕ ФУНКЦИИ                              //
//                                                                              //
//##############################################################################//


//SpawnSTEP15
/*forward remote_GameModeExitFunc();
public remote_GameModeExitFunc()//запускается через 4 секунды после вводы команды restart из GameModeInitExitFunc
{

	textdraw_OnGameModeExit();//	OnDestroyTextDraw();
	//--------------------------------------------------------------
	KillTimer(fifteenminutstimers); fifteenminutstimers = -1;
	KillTimer(fiveminutstimers); fiveminutstimers = -1;
	KillTimer(oneminutstimer); oneminutstimer = -1;
	KillTimer(onesecondtimers); onesecondtimers = -1;
	KillTimer(onesecondtimers2); onesecondtimers2 = -1;
	KillTimer(onesecondtimers3); onesecondtimers3 = -1;
	KillTimer(onesecondtimers4); onesecondtimers4 = -1;

	KillTimer(gCountdowntimer); gCountdowntimer = -1;
	KillTimer(endracetimer); endracetimer = -1;
	KillTimer(carupgradetimer); carupgradetimer = -1;
	KillTimer(loadcarupgradetimer);	loadcarupgradetimer = -1;

	KillTimer(PDgateCloseLStimer); PDgateCloseLStimer = -1;
	KillTimer(PDbarrierCloseSFtimer); PDbarrierCloseSFtimer = -1;
	KillTimer(DoDgateCloseTimer); DoDgateCloseTimer = -1;

	KillTimer(gCountdownDerbyTimer); gCountdownDerbyTimer = -1;
	KillTimer(gCountdownCSTimer); gCountdownCSTimer = -1;//для контры
	KillTimer(gUpdatecstimer); gUpdatecstimer = -1;
	KillTimer(gMoveCountdown); gMoveCountdown = -1;

	KillTimer(gReminder); gReminder = -1;
	KillTimer(ElevatorBoostTimer); ElevatorBoostTimer = -1;
	KillTimer(gOffsettimer); gOffsettimer = -1;

	SendClientMessageToAll(COLOR_RESTARTING, "KillTimers");
	print("KillTimers завершено");
	//--------------------------------------------------------------
	dropweapon_OnGameModeExit();//для выпадения оружия
print("dropweapon завершено");
	ferriswheel_OnGameModeExit();
print("ferriswheel завершено");
	firstlook_OnFilterScriptExit();
print("firstlook завершено");
	backweapon_OnGameModeExit();
print("weaponback завершено");
	migalka_OnGameModeExit();
print("migalka завершено");
	poster_OnGameModeExit();
print("poster завершено");
	//airdefence_OnGameModeExit();
	UnloadContent();
	//------------------------
	if(GameRestart == 1) GameModeExit(); //Эта функция завершает текущий режим игры, запускает OnGameModeExit
	//и либо перезапускает его, либо запускает следующий режим, согласно Вашей конфигурации в server.cfg.
	else
	{
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "exit");//, giveplayerid
		SendRconCommand(strings);
	}
}*/



//public OnRemoteResetServer(const playername[])
forward OnRemoteResetServer();
public OnRemoteResetServer()//ВАЙП
{
	/*mysql_query("TRUNCATE `players`");//очистка таблицы в ручную
	mysql_query("TRUNCATE `banlist`");
	mysql_query("TRUNCATE `blacklist`");
	mysql_query("TRUNCATE `clans`");
	mysql_query("TRUNCATE `criminallist`");
	mysql_query("TRUNCATE `election`");
	mysql_query("TRUNCATE `finance`");
	mysql_query("TRUNCATE `invitelist`");
	mysql_query("TRUNCATE `killlist`");
	mysql_query("TRUNCATE `lastrounds`");
	mysql_query("TRUNCATE `unbanlist`");
	mysql_query("TRUNCATE `warnlist`");*/

	db_query(db_VW, "delete from `players` where 1");
	db_query(db_VW, "delete from `banlist` where 1");
	db_query(db_VW, "delete from `blacklist` where 1");
	db_query(db_VW, "delete from `clans` where 1");
	db_query(db_VW, "delete from `criminallist` where 1");
	db_query(db_VW, "delete from `election` where 1");
	db_query(db_VW, "delete from `finance` where 1");
	db_query(db_VW, "delete from `invitelist` where 1");
	db_query(db_VW, "delete from `killlist` where 1");
	db_query(db_VW, "delete from `lastrounds` where 1");
	db_query(db_VW, "delete from `unbanlist` where 1");
	db_query(db_VW, "delete from `warnlist` where 1");

	//drop table `TableToClear`;
	//create table `TableToClear` (Code integer not null, Name char (50) not null);

	new curdate = getdate();//Получает текущую дату на сервере, которая запишется в переменные &year, &month и &day.
	for(new h = 0; h < MAX_HOUSE; h++)
	{
		strmid(HouseInfo[h][hOwner], "The State", 0, strlen("The State"), 255);//меняем имя владельца на The State
		HouseInfo[h][hHel] = 0;
		HouseInfo[h][hCloth] = 0;
		HouseInfo[h][hTV] = 0;
		HouseInfo[h][hLock] = 0;
		HouseInfo[h][hOwned] = 0;
		HouseInfo[h][hRent] = 10000;
		//HouseInfo[h][hRentabil] = 0;
		HouseInfo[h][hTill] = 0;
		HouseInfo[h][hDate] = curdate;
	}
	SaveHousesSQL();
	//------------------------------------------------------------------
	for(new b=0; b<MAX_BIZ; b++)
	{
		BizInfo[b][bOwned] = 0;
		strmid(BizInfo[b][bOwner], "The State", 0, strlen("The State"), 20);//меняем имя владельца на The State
		//strmid(BizInfo[b][bExtortion], "No-One", 0, strlen("No-One"), 20);//меняем имя владельца на The State
		BizInfo[b][bExtortion] = 0;
		BizInfo[b][bEntranceCost] = 0;
		BizInfo[b][bTill] = 100;
		BizInfo[b][bLevel] = 1;
		BizInfo[b][bLock] = 0;
		BizInfo[b][bMetal] = 0;
		BizInfo[b][bTextiles] = 0;
		BizInfo[b][bProvisions] = 0;
		BizInfo[b][bTree] = 0;
		BizInfo[b][bFuel] = 0;
		BizInfo[b][bProducts] = 100;
		BizInfo[b][bBuyProd] = 40;
		BizInfo[b][bSellProd] = 50;//15 для экономики
		BizInfo[b][bDate] = curdate;
		BizInfo[b][bInkas] = 0;
		BizInfo[b][bImport] = 0;
		BizInfo[b][bExport] = 0;
		BizInfo[b][bWorker] = 0;
		BizInfo[b][bSalary] = 1;
	}
	BizInfo[0][bTill] = 1000000000;
	BizInfo[0][bBuyProd] = 5;
	BizInfo[0][bSellProd] = 10;

	SBizInfo[54][sbBuyProd] = 40;//MushroomVault
	SBizInfo[54][sbSellProd] = 60;
//СКЛАД
	BizInfo[80][bBuyProd] = 20;
	BizInfo[80][bSellProd] = 30;
	BizInfo[80][bTill] = 1000000;
	BizInfo[80][bInkas] = 1000000;
//ПОРТ
	BizInfo[81][bBuyProd] = 80;//цена покупки товаров ПОРТом
	BizInfo[81][bSellProd] = 10;//цена продажи сырья
	BizInfo[81][bTill] = 1000000;//чтобы грузчики могли работать
	BizInfo[81][bInkas] = 1000000;
	SaveBizSQL();
	//------------------------------------------------------------------
	for(new sb=0; sb<MAX_SBIZ; sb++)
	{
		SBizInfo[sb][sbOwned] = 0;
		strmid(SBizInfo[sb][sbOwner], "The State", 0, strlen("The State"), 20);//меняем имя владельца на The State
		//strmid(SBizInfo[sb][sbExtortion], "No-One", 0, strlen("No-One"), 20);//меняем имя владельца на No-One
		SBizInfo[sb][sbExtortion] = 0;
		SBizInfo[sb][sbEntranceCost] = 0;
		SBizInfo[sb][sbTill] = 0;
		SBizInfo[sb][sbLevel] = 1;
		SBizInfo[sb][sbLock] = 0;
		SBizInfo[sb][sbProducts] = 100;
		SBizInfo[sb][sbBuyProd] = 1;
		SBizInfo[sb][sbSellProd] = 10;//15 для экономики
		SBizInfo[sb][sbDate] = curdate;
		SBizInfo[sb][sbInkas] = 0;
		SBizInfo[sb][sbImport] = 0;
		SBizInfo[sb][sbExport] = 0;
		SBizInfo[sb][sbWorker] = 0;
		SBizInfo[sb][sbSalary] = 1;
	}//для экономики
	SBizInfo[0][sbEntranceCost] = 100;//100 начальная стоимость аренды тачки
	SBizInfo[1][sbEntranceCost] = 100;//100 начальная стоимость аренды тачки

	SBizInfo[2][sbEntranceCost] = 10;//100 начальная стоимость 1 минуты разговора
	SBizInfo[3][sbEntranceCost] = 1;//начальная цена 1 л топлива
	SBizInfo[4][sbEntranceCost] = 17;//173 начальная цена 1кВт эл-ва
	SBizInfo[7][sbEntranceCost] = 3;//25 начальная стоимость 1-го символа рекламы
	SBizInfo[8][sbEntranceCost] = 500;//500 начальная стоимость возврата машины к дому

	/*SBizInfo[17][sbBuyProd] = 50;//Oil Company
	SBizInfo[17][sbSellProd] = 60;
	SBizInfo[3][sbBuyProd] = 70;//	Gas Company
	SBizInfo[3][sbSellProd] = 80;*/

	for(new sb = GAS_STATION; sb < PARKING; sb++)
	{
		SBizInfo[sb][sbProducts] = 1000;
		SBizInfo[sb][sbBuyProd] = 40;//GasStation
		SBizInfo[sb][sbSellProd] = 50;
		SBizInfo[sb][sbInkas] = 100000;
	}//для экономики

	for(new sb = PARKING; sb < PARKING+sizeof(Parking); sb++)
	{
		SBizInfo[sb][sbProducts] = 0;
	}//для экономики

	SBizInfo[52][sbTill] = 100000;//ферма
	SBizInfo[52][sbInkas] = 100000;
	SBizInfo[55][sbTill] = 100000;//шахта
	SBizInfo[55][sbInkas] = 100000;
	SaveSBizSQL();
	//------------------------------------------------------------------
	FamilyInfo[0][fInterior] = 0;
	for(new t=0; t<MAX_FAMILY; t++)//sizeof(FamilyInfo)
	{
		strmid(FamilyInfo[t][fLeader], "No-One", 0, strlen("No-One"), 20);
		FamilyInfo[t][fMembers] = 0;
		FamilyInfo[t][fBank] = 0;
		FamilyInfo[t][fRank] = 11;
		FamilyInfo[t][fAlliance] = TEAM_NONE;
		//strmid(FamilyInfo[t][fAlliance], "0000000000000000000", 0, 20, 20);
		FamilyInfo[t][fWar] = TEAM_NONE;
		//strmid(FamilyInfo[t][fWar], "0000000000000000000", 0, 20, 20);
		FamilyInfo[t][fMaterial] = 0;
	}
	FamilyInfo[DoD][fMaterial] = 2000;
	SaveFamiliesSQL("CEPBEP");
 	//------------------------------------------------------------------
	for(new vid=1; vid<MAX_VEHICLES-1; vid++)
	{
		VehInfo[vid][cInsur] = 0;
		DestroyVehicleEx(vid, 10);
	}
	SaveCarSQL();
	//------------------------------------------------------------------
	Jackpot = 1000;
	StatusJob[5] = 0;//разрешить CarJacker
	StatusJob[11] = 1;//запретить Inkassator
	//TAX = 0;
	TaxValue = 1;
	gCheckProp = 7;
	ANTIVEHHEALTH = 1;
	ANTIHEALTH = 1;
	FuelCost = 1.0;
	SaveSettingsSQL();
	//------------------------------------------------------------------
	//new strtmp[25+24];
	//format(strtmp, sizeof(strtmp), "AdmCmd: %s Full resetted", playername);
	//Log(ADMINLOG, strtmp);
	//SendClientMessage(playerid, COLOR_GREY, "   Вся недвижимость продана !");
	SendClientMessageToAll(COLOR_YELLOW, "   Вся недвижимость продана !");

	//format(strtmp, sizeof(strtmp), "AdmCmd: %s has done reset server", playername);
	//Log(ADMINLOG,  strtmp);
	//return 1;

}
forward OnRemoteRestartServer(const playername[], rtime);
public OnRemoteRestartServer(const playername[], rtime)//перегружает мод
{//вызываются из удалённых фс (filterscripts)
	new strtmp[46+24+10];
	format(strtmp, sizeof(strtmp), "~r~%s~b~~n~~w~Please wait ~n~~w~%d~b~ seconds", playername, rtime);
	//wtime = rtime;
	GameTextForAll(strtmp, 4000, 4);

	GameRestart = 1;
	GameModeInitExitFunc(rtime);

	format(strtmp, sizeof(strtmp), "AdmCmd: %s has done restart mode", playername);
	Log(ADMINLOG,  strtmp);
	//return 1;
}

//SpawnSTEP14
stock GameModeInitExitFunc(rtime)//вызывается при команде /restart (рестарт)
{
//начинаем длительное сохранение
//ВНИМАНИЕ может быть рассинхронизация данных
	SaveSettingsSQL();
	SaveOnline();
	SaveHousesSQL();
	SaveBizSQL();
	SaveSBizSQL();
	SaveFamiliesSQL("CEPBEP");
	SaveClansSQL("CEPBEP");
	//SaveTurfsSQL("CEPBEP");
	SaveCarSQL();

	for(new i = GetMaxPlayers() - 1; i >= 0; --i)
	{
		if(!IsPlayerConnectedEx(i) || !gPlayerSpawned[i] || spectateid[i] != MAX_PLAYERS-1) continue;
		//PlayerInfo[i][pInt] = GetPlayerInterior(i);
		//PlayerInfo[i][pVirtual] = GetPlayerVirtualWorld(i);
		//GetPlayerPos(i, PlayerInfo[i][pPos_x],PlayerInfo[i][pPos_y],PlayerInfo[i][pPos_z]);
		//для сохранения оружия
		//Вариант 2
		PlayerInfo[i][pGun1] = 0; PlayerInfo[i][pAmmo1] = 0;
		PlayerInfo[i][pGun2] = 0; PlayerInfo[i][pAmmo2] = 0;
		PlayerInfo[i][pGun3] = 0; PlayerInfo[i][pAmmo3] = 0;
		PlayerInfo[i][pGun4] = 0; PlayerInfo[i][pAmmo4] = 0;
		for(new weaponid = 22; weaponid <= 32; weaponid++)//MAX_WEAPONS
		{   //сканируем всё огнестрельное оружие
			if(LastAmmo[i][weaponid] > 0 && LastAmmo[i][weaponid] < 1000)
			{   //записываем те виды в которых есть патроны
				//по тем пушкам что есть в слотах
				new slot = GetWeaponSlot(weaponid);
				if(slot == 2 && LastWeaponInSlot[i][slot] == weaponid)
				{ PlayerInfo[i][pGun1] = weaponid; PlayerInfo[i][pAmmo1] = LastAmmo[i][weaponid]; }
				else if(slot == 3 && LastWeaponInSlot[i][slot] == weaponid)
				{ PlayerInfo[i][pGun2] = weaponid; PlayerInfo[i][pAmmo2] = LastAmmo[i][weaponid]; }
				//если пуха принадлежит слоту 2 и в этом слоте куплен дробовик
				else if(slot == 4 && LastWeaponInSlot[i][slot] == weaponid)
				{ PlayerInfo[i][pGun3] = weaponid; PlayerInfo[i][pAmmo3] = LastAmmo[i][weaponid]; }
				else if(slot == 5 && LastWeaponInSlot[i][slot] == weaponid)
				{ PlayerInfo[i][pGun4] = weaponid; PlayerInfo[i][pAmmo4] = LastAmmo[i][weaponid]; }
			}
		}
		RemovePlayerAllAttachedObjectEx(i);
	}
	print("Сохранение успешно завершено");

	SetTimer("remote_GameModeExitFunc", rtime*1000, 0);//запускаем разовый таймер на выход из мода через 4 сек
	SendClientMessageToAll(COLOR_RESTARTING, "remote_GameModeExitFunc");

	//new strings[MAX_STRING];
	//format(strings, sizeof(strings), "unloadfs vw_pirateisland");
	//SendRconCommand(strings);

	//format(strings, sizeof(strings), "unloadfs vw_ferriswheel");
	//SendRconCommand(strings);

	//format(strings, sizeof(strings), "unloadfs flymode");
	//SendRconCommand(strings);
}



forward OnRemoteLogoutServer();
public OnRemoteLogoutServer()//сохраняет данные без рестарта
{//вызываются из удалённых фс (filterscripts)
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if( !gPlayerSpawned[i] ) continue;
		OnPlayerStatsUpdate(i, 255);
		SendClientMessage(i, COLOR_GREY, "   Ваши Данные были сохранены.");
	}
	SaveSettingsSQL();
	SaveOnline();
	SaveHousesSQL();
	SaveBizSQL();
	SaveSBizSQL();
	SaveFamiliesSQL("CEPBEP");
	SaveClansSQL("CEPBEP");
	SaveCarSQL();
	return 1;
}

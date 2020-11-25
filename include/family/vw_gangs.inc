/*
 *            VW_GANGS v1.0
 *       (c) Copyright 2009-2020 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (danger1979@mail.ru)
 * @date      : 19.05.2020
 * @update    : 19.05.2020
 *
 * This file is provided as is (no warranties).
 *
 */
 
new HasZoneAttacker[MAX_TURFS];//содержит номер атакующей банды
new HasTakingZones[MAX_TURFS];//содержит номер принимающей банды
new HasLeftZone[MAX_PLAYERS];//флаг проверка покидания зоны
new taketurfcount[MAX_TURFS];//счётчик секунд нахождения в зоне должен быть не в самом счётчике а глобальным
new taketurfbackcount[MAX_TURFS];//счётчик убийств на зоне

stock gangs_OnGameModeInit()
{

/*
#define TEAM_NONE 	0
#define TEAM_GROVE 	1
#define TEAM_BALLAS 2
#define TEAM_AZTEC 	3
#define TEAM_VAGOS 	4
#define TEAM_NANG 	5
#define TEAM_RIFA 	6
#define TEAM_TRIAD 	7
#define TEAM_BIKER 	8
#define TEAM_MAFIA 	9
*/

	LoadTurfsSQL();
	return 1;
}


stock gangs_OnPlayerExitedMenu(playerid, Menu:Current)
{
	//==========================================================================
	if(Current == mGangsVacancies)
	{
		HideMenuForPlayerEx(Current,playerid);
		//TogglePlayerControllableEx(playerid, 1);
		ShowMenuForPlayerEx(mJobMenu1_9,playerid);//то установить основное меню
	}
}
stock gangs_OnPlayerSelectedMenuRow(playerid, row, Menu:Current)
{
	//new Menu:Current = GetPlayerMenu(playerid);//получить ID меню
	if(Current == mGangsVacancies)
	{
		switch(row)
		{
			case 0..8://1-9
			{
        		/*if(PlayerInfo[playerid][pMember] != 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы находитесь уже в группе! (USE: /uninvite, чтобы уволиться)");
				}*/
				//else
				if(PlayerInfo[playerid][pLeader] == TEAM_GROVE+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
				}
				else if(
						//(PlayerInfo[playerid][pDrugsSkill] < 500 && PlayerInfo[playerid][pMember] != TEAM_GROVE+row) &&
						//(PlayerInfo[playerid][pGunSkill] < 100 && PlayerInfo[playerid][pMember] != TEAM_GROVE+row) &&
						PlayerInfo[playerid][pRespect] < (OnlineRecord*100/100)
					   )
				{
					//SendClientMessage(playerid, COLOR_GREY, "   Ваш навык наркодилера меньше 500 !");
					//SendClientMessage(playerid, COLOR_GREY, "   Ваш навык оружейника меньше 100 !");
					format(strings, sizeof(strings), "   Ваше уважение %d меньше %d !", PlayerInfo[playerid][pRespect], (OnlineRecord*100/100));
					SendClientMessage(playerid, COLOR_GREY, strings);
				}
				else if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на оружие !");
				}
			    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != TEAM_GROVE+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob, чтобы уйти с работы)!");
				}
			    else if(PlayerInfo[playerid][pMember] == TEAM_GROVE+row && PlayerInfo[playerid][pProfSkill] < 400
					&& FamilyInfo[TEAM_GROVE+row][fMembers] > 1 )
				{//если во фракции 2 и более человек, то проверить у кого скил достиг 400, а если игрок 1 во фракции то просто дать возможностьстать лидером
					SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
				}
				else
				{
#if defined vw_sql//#endif
				    new ToBase[49+2];
					format(ToBase, sizeof(ToBase), "SELECT `Leader` FROM `players` WHERE `Leader`=%d", TEAM_GROVE+row);// LIMIT 1
					mysql_query(ToBase); mysql_store_result();
					if(mysql_num_rows() == 0)
					{
						if(FamilyInfo[TEAM_GROVE+row][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, TEAM_GROVE+row);
						else if(PlayerInfo[playerid][pMember] == TEAM_GROVE+row && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, TEAM_GROVE+row);
					}
					mysql_free_result();
#endif
					if(!strcmp(FamilyInfo[TEAM_GROVE+row][fLeader], "No-One", true))
					{
						MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), TEAM_GROVE+row);
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
					}

				}
				ShowMenuForPlayerEx(mGangsVacancies, playerid);
			}
			case 9://10 UnInvite
			{//178.124.35.222
			    if(PlayerInfo[playerid][pMember] == 0)
			    {
        			SendClientMessage(playerid, COLOR_GREY, "   Вы не являетесь членом организации !");
				}
				else if(GetPVarInt(playerid, "gShowDialog") != -1)
			    {
        			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете в данный момент уволиться! Закройте диалоговое окно!");
				}
				else if(PlayerInfo[playerid][pAccount] == 0)
				{
        			SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
				}
				else
				{
					//new family = PlayerInfo[playerid][pMember];
					format(strings, sizeof(strings), "* Вы подали в отставку. Вы теперь снова Гражданский.", PlayerName(playerid));
					SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
					UninvitePlayerid(MAX_PLAYERS-1, playerid, PlayerName(playerid));
					//format(strings, sizeof(strings), "AdmCmd: %s has uninvited from Faction %d.", PlayerName(playerid), family);
					//Log(INVITE,strings);
				}
				ShowMenuForPlayerEx(mGangsVacancies, playerid);
			}
		}
	}
}
stock gangs_OnPlayerConnect(playerid)
{
	HasLeftZone[playerid] = MAX_TURFS;//флаг проверка покидания зоны
}

stock gangs_OnPlayerSpawn(playerid)//для зон банд
{
	for(new j=0; j<MAX_TURFS; j++)//для зон банд MAX_TURFS
	{
		if(	IsAGangs(playerid) || IsAFamilyMember(playerid)	|| PlayerInfo[playerid][pAdmin] == 2)
		{   //сканируем все зоны которые моргают
			if(TurfInfo[j][zFlash] == 1)
			{
				GangZoneFlashForPlayer(playerid, Turfs[j], FamilyInfo[HasZoneAttacker[j]][fColor]);
			}
		}
	}
}

stock gangs_OnPlayerDisconnect(playerid)//для зон банд
{
 	for(new t=0; t<MAX_TURFS; t++)//для зон банд 132 MAX_TURFS
	{
		GangZoneHideForPlayer(playerid, t);//спрятать все зоны
	}
}
//=============== [ TAKE GANGS TURF ] ==============================
stock gangs_OnPlayerDeath(playerid, killerid)//для зон банд
{   //вызывается из OnPlayerDeath
	if( gRealWar ) return 1;
	if(killerid == INVALID_PLAYER_ID) return 1;
	if(!IsAGangs(playerid)) { return 1; }

//чтобы можно было выбрать спаун
    //TogglePlayerSpectatingEx(playerid, 1);
    //PlayerSpectatePlayer(playerid, killerid);
    
	if(	!IsAGangs(killerid) ||
		GetPlayerState(killerid) != PLAYER_STATE_ONFOOT) { return 1; }
	if(IsZoneAttacker(killerid)) return 1;
	for(new j=0; j<MAX_TURFS-1; j++)//для зон банд 132 MAX_TURFS
	{   //сканируем все зоны
		if(IsPlayerInRegion(playerid, j))// && gPlayerSpawned[playerid] == 1==1
		{   //если игрок находится в какой то зоне j
			//=============== [ TAKE OTHER GANGS TURF ] ============================
	        if(	PlayerInfo[playerid][pMember] == TurfInfo[j][zFamily] &&
				PlayerInfo[killerid][pMember] != TurfInfo[j][zFamily] &&
				(PlayerInfo[killerid][pMember] == HasZoneAttacker[j] ||
				HasZoneAttacker[j] == TEAM_NONE)	)
	        {   //если зона принадлежит банде в которой находится убитый игрок
				//и не принадлежит банде в которой находится киллер
				//и киллер принадлежит атакующей банде или зона не атакована
				//заваёвывание начало
			    taketurfbackcount[j] ++;
				if((taketurfbackcount[j] == GANGAREA_WARNINGS && taketurfbackcount[j] < GANGAREA_TAKE))
				{   //если убито 1 Не Грув то мерцание зоны
					AttackedGangsTurf(killerid, j);
					HasTakingZones[j] = PlayerInfo[playerid][pMember];
					HasZoneAttacker[j] = PlayerInfo[killerid][pMember];
					//записали номер атакующей банды по j зоне
				}
			}
			break;
		}
	}
	//ИНФОРМИРОВАНИЕ
	//format(strings, sizeof(strings), "OnPlayerGangWar(playerid:%d, killerid:%d)", playerid, killerid);
	//ABroadCast(COLOR_MAROON, strings, 9);
	return 1;
}
stock AttackedGangsTurf(playerid, gangzone)//playerid = killerid
{   //вызывется из gangs_OnPlayerDeath
	//new strings[MAX_STRING];
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
	    if(	IsAGangs(i)	|| IsAFamilyMember(i) )
	    {
			format(strings, sizeof(strings), "GangZone Message: квартал %s[%d] атакован бандой %s",
				regions[gangzone][region_name], gangzone, FamilyInfo[PlayerInfo[playerid][pMember]][fName]);
			SendClientMessage(i, FamilyInfo[PlayerInfo[playerid][pMember]][fColor], strings);
			GangZoneFlashForPlayer(i, Turfs[gangzone], FamilyInfo[PlayerInfo[playerid][pMember]][fColor]);
			TurfInfo[gangzone][zFlash] = 1;//мигает
			IncreaseRank(playerid, 1);
		}
	}
	//ИНФОРМИРОВАНИЕ
	//format(strings, sizeof(strings), "AttackedGangsTurf(playerid:%d)", playerid);
	//ABroadCast(COLOR_MAROON, strings, 9);
	return 1;
}//GangZoneStopFlashForAll

stock IsZoneAttacker(playerid)
{
//если уже какая зона атакована этой бандой
	for(new j=0; j<MAX_TURFS-1; j++)//для зон банд 132 MAX_TURFS
	{//сканируем все зоны, которые атакует эта банда
		if(HasZoneAttacker[j] == PlayerInfo[playerid][pMember])	return 1;
	}
	return 0;
}

//stock TakeGangsTurfTimer(playerid)
stock gangs_OneSecondTimers(playerid)
{   //вызывается из OneSecondTimers
	if(	!IsAGangs(playerid) ) return 1;
	if( GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return 1;//&& AFK_IdleTime[playerid] < 3

	//new strings[MAX_STRING];
	//сначало надо узнать в какой зоне находится игрок для этого сканируем все зоны
	for(new j=0; j<MAX_TURFS-1; j++)//для зон банд MAX_TURFS=229 //пропускаем Zone 51 [228]
	{//за вычетом последней зоны 51
	    if(j == LCN_TURF1 || j == LCN_TURF2 || j == Yakuz_TURF) continue; //пропускаем базу ЛКН и Якудз
		if(IsPlayerInRegion(playerid, j))
		{   //если игрок из банды находится в зоне j
			CrashDetected[playerid] = 31;

		    if(HasLeftZone[playerid] == j)
			{   //если предыдущая зона равна через секунду тому же значению
			//if((taketurfbackcount[j] >= GANGAREA_WARNINGS && taketurfbackcount[j] < GANGAREA_TAKE) || TurfInfo[j][zFamily] == 0)// && j!=232
				if((HasZoneAttacker[j] >= TEAM_GROVE && HasZoneAttacker[j] <= TEAM_MAFIA)//если зона атакована
				|| (TurfInfo[j][zFamily] == TEAM_NONE && j != (MAX_TURFS-1)) )//или зона нейтральная и не является военной базой или
				{
				    if(HasZoneAttacker[j] == PlayerInfo[playerid][pMember])
				    {   //если зона атакована этой бандой
						//ведем отсчёт захвата
					    format(strings, sizeof(strings), "~g~|~r~%s~g~|~n~~p~%d", regions[j][region_name], taketurfcount[j]);
						GameTextForPlayerEx(playerid, strings, 1500, 6);
						if(taketurfcount[j] <= 0)
						{   //если счётчик досчитал до 0
							TakeGangsTurf(playerid, j);//запускаем ф-ию захвата зоны
							taketurfcount[j] = TimeTakeZone;//востановить значение счётчика
						}
						taketurfcount[j] --;//общий таймер по данной зоне
					}
					else if(HasTakingZones[j] == PlayerInfo[playerid][pMember])
					//иначе если игрок принадлежит атакованной банде
					{
					    format(strings, sizeof(strings), "~g~|~r~%s~g~|~n~~p~%d", regions[j][region_name], taketurfcount[j]);
						GameTextForPlayerEx(playerid, strings, 1500, 6);
						if(taketurfcount[j] >= TimeTakeZone)
						{   //если счётчик досчитал до максимума
							GangZoneStopFlashForAll(HasLeftZone[playerid]);//остановить анимацию у всех игроков предыдущей зоны
							TurfInfo[j][zFlash] = 0;
							HasTakingZones[j] = 0;
							taketurfcount[j] = TimeTakeZone;//востановить значение счётчика
							HasZoneAttacker[j] = TEAM_NONE;//сбросить номер атакующей банды
							taketurfbackcount[j] = 0;//сбросить счётчик захвата
						}
						taketurfcount[j] ++;//общий таймер по данной зоне
					}
				}
			}
		    else if(HasLeftZone[playerid] != j)//если игрок вошёл в др. зону
		    {//если зона в которой находится игрок не равна предыдущей, т.е. он изменил зону
				if(taketurfbackcount[j] == 0 && TurfInfo[j][zFamily] == TEAM_NONE && j != (MAX_TURFS-1) )
				{   //если зона не атакована и зона нейтральная 			и не является военной базой или
				    taketurfbackcount[j] ++;
					if(taketurfbackcount[j] == GANGAREA_WARNINGS)
					{   //сработает только 1 раз
						AttackedGangsTurf(playerid, j);
						HasTakingZones[j] = TEAM_NONE;
						HasZoneAttacker[j] = PlayerInfo[playerid][pMember];
						//записали номер атакующей банды по j зоне
					}
				}
			}
			//переменная хранящая номер зоны в которой находится игрок
			HasLeftZone[playerid] = j;//сохраняем постоянно значение для проверки выхода из зоны
		}
	}
	return 1;
}
stock TakeGangsTurf(playerid, gangzone)//playerid = killerid,
{//вызывается из TakeGangsTurfTimer
	//new strings[MAX_STRING];
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		//сканируем всех игрок которым необходимо выводить данную информацию
		if( IsAGangs(i) || IsAFamilyMember(i) )
		{
			format(strings, sizeof(strings), "GangZone Message: %s захватил квартал %s[%d]", PlayerName(playerid), regions[gangzone][region_name], gangzone);
			SendClientMessage(i, FamilyInfo[PlayerInfo[playerid][pMember]][fColor], strings);
			GangZoneStopFlashForAll(Turfs[gangzone]);//остановить анимацию
			TurfInfo[gangzone][zColor] = FamilyInfo[PlayerInfo[playerid][pMember]][fColor];
			//GangZoneHideForPlayer(i, Turfs[gangzone]);//спрятать зону Turfs[gangzone] для показа в другом цвете
			GangZoneShowForPlayer(i, Turfs[gangzone], TurfInfo[gangzone][zColor]);//присваиваем это зоне новый цвет
			TurfInfo[gangzone][zFamily] = PlayerInfo[playerid][pMember];
			HasZoneAttacker[gangzone] = TEAM_NONE;
			HasTakingZones[gangzone] = TEAM_NONE;
			taketurfbackcount[gangzone] = 0;
			TurfInfo[gangzone][zFlash] = 0;
			taketurfcount[gangzone] = TimeTakeZone;//устанавливаем время заново

			IncreaseRank(playerid, 1);
		}
	}

	for(new b=0; b<MAX_BIZ; b++)
	{   //сканируем все бизы что находятся в данной зоне
		if( IsPointInRegion(BizInfo[b][bEntranceX], BizInfo[b][bEntranceY], BizInfo[b][bEntranceZ], gangzone) )//если дом находится в координатах по строке j из массива zones
		{   //если биз находится в данной зоне
			//strmid( BizInfo[b][bExtortion], FamilyInfo[PlayerInfo[playerid][pMember]][fName], 0, 20, 255);
			BizInfo[b][bExtortion] = PlayerInfo[playerid][pMember];
		}
	}
	for(new sb=0; sb<MAX_SBIZ; sb++)
	{   //сканируем все бизы что находятся в данной зоне
		if( IsPointInRegion(SBizInfo[sb][sbEntranceX], SBizInfo[sb][sbEntranceY], SBizInfo[sb][sbEntranceZ], gangzone) )//если дом находится в координатах по строке j из массива zones
		{   //если биз находится в данной зоне
			//strmid( SBizInfo[sb][sbExtortion], FamilyInfo[PlayerInfo[playerid][pMember]][fName], 0, 20, 255);
			SBizInfo[sb][sbExtortion] = PlayerInfo[playerid][pMember];
		}
	}
    SaveTurfsSQL();
	return 1;
}



stock OnPlayerKeyCheckFireKey(playerid, newkeys, oldkeys)
{   //вызывается из OnPlayerKeyStateChange при изминении состояния клавиш
	//#pragma unused oldkeys
	//if(newkeys & KEY_FIRE)
	//if(PRESSED(KEY_FIRE))//1 нажатие = 2 срабатывания
	//((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
	if(newkeys == KEY_FIRE && oldkeys != KEY_FIRE)
	{//сработает только когда нажмётся клавиша
//для бомб начало
		new weaponid = GetPlayerWeapon(playerid);
		new ammo = GetPlayerAmmo(playerid);
		new Float:bomb_X, Float:bomb_Y, Float:bomb_Z, Float:bomb_A;
		if(weaponid == 39)//если в руках взрыв пакет //40 - детонатор
 		{	//ставим бомбу на растоянии 2.5 от себя
			if(GetPVarInt(playerid, "gBomb") == 0)
		    {//чтобы можно было переставлять бомбу
				//RemovePlayerWeaponEx(playerid, weaponid);//GetPlayerWeapon(playerid)
				SetPlayerAmmo(playerid, weaponid, ammo-1);
				DetectedGun[playerid][weaponid] = 1;
				//LastWeaponInSlot[playerid][GetWeaponSlot(weaponid)] = 0;
				LastAmmo[playerid][weaponid] = ammo-1;

				SetPVarInt(playerid, "gBomb", 1);
				GetXYZInFrontOfPlayer(playerid, 2.5, bomb_X,bomb_Y,bomb_Z, bomb_A);
		   		SetPVarFloat(playerid, "bomb_X", bomb_X);
		   		SetPVarFloat(playerid, "bomb_Y", bomb_Y);
		   		SetPVarFloat(playerid, "bomb_Z", bomb_Z);
				SendClientMessage(playerid, COLOR_GREY, "   Бомба установлена!");
				LastWeapon[playerid] = 39;
				//поднимаем флаг бомба установлена
			}
		}
		else if(weaponid == 39 || weaponid == 40 || LastWeapon[playerid] == 40 || LastWeapon[playerid] == 39)
		{
			if(GetPVarInt(playerid, "gBomb") == 1)
			{//если бомба установлена
				SetPVarInt(playerid, "gBomb", 0);//взрываем бомбу
				CreateExplosion(GetPVarFloat(playerid, "bomb_X"),GetPVarFloat(playerid, "bomb_Y"),GetPVarFloat(playerid, "bomb_Z"), 7, 25.0);//радиус взрыва самой бомбы = 8м
				SendClientMessage(playerid, COLOR_RED, "   Бомба взорвана!");
				SendClientMessage(playerid, COLOR_GREY, "   Захват зон разрешён с 18:00 до 23:00 ч по серверному времени!");//в рабочие дни
				SendClientMessage(playerid, COLOR_GREY, "   Допускается одновременно захватывать только одну зону!");
				//=============== [ TAKE OTHER GANGS TURF ] ============================
				//для зон банд
				new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
				//new remainder = (getdate()-8)%7;//остаток от деления на 7  && remainder == 0
				//где 8 - это числов первой субботы в году
				//new remainder = (getdate()-1)%7;//остаток от деления на 7  && remainder == 0
				//где 1 - это числов первого воскресенья в году
				if(	IsAGangs(playerid) &&
					lH >= 18 && lH < 23
				  )//если чётное число
				{
					if(IsZoneAttacker(playerid)) return 1;
					for(new j=0; j<MAX_TURFS-1; j++)//для зон банд 132 MAX_TURFS
					{   //определяем в какой зоне счас игрок и взрыв

					    //если игрок в какой то зоне и в этой же зоне установлена бомба и эта зона не нейтральная и зона не принадлежит банде в которой находится терорист
						if(	IsPlayerInRegion(playerid, j) && TurfInfo[j][zFamily] != 0 && PlayerInfo[playerid][pMember] != TurfInfo[j][zFamily] &&
							IsPointInRegion(GetPVarFloat(playerid, "bomb_X"), GetPVarFloat(playerid, "bomb_Y"), GetPVarFloat(playerid, "bomb_Z"), j) &&//бомба в это йзоне
							HasZoneAttacker[j] == TEAM_NONE)
						{   //зона не атакована

						    //если уже какая зона атакована этой бандой

						    taketurfbackcount[j] ++;
							if((taketurfbackcount[j] == GANGAREA_WARNINGS && taketurfbackcount[j] < GANGAREA_TAKE))
							{   //если убито 1 Не Грув то мерцание зоны
								AttackedGangsTurf(playerid, j);
								HasTakingZones[j] = TurfInfo[j][zFamily];
								HasZoneAttacker[j] = PlayerInfo[playerid][pMember];//тем самым запустили отсчёт времени
								//записали номер атакующей банды по j зоне
							}
							break;
						}
					}
				}
			}
		}

//для бомб конец
		//----------------------------------------------------------------------
		if(KEYSTATE == 1)
		{
			format(strings, sizeof(strings), "OnPlayerKeyCheckFireKey(newkeys:%d, oldkeys:%d) LastWeapon:%d", newkeys, oldkeys, LastWeapon[playerid]);
			SendClientMessage(playerid, COLOR_YELLOW, strings);
		}
	}
	return 1;
}



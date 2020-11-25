//для экономики
new DutyFiveMinuts = 30;//300 стоимость дежурства в течени 5 минут

//для вояк
new MilitaryCounter = 0;

//для медиков
new MedicCounter = 0;

//для invite
new SelectChar[MAX_PLAYERS];//флаг для команд в чате done next
new SelectCharID[MAX_PLAYERS];
new SelectCharPlace[MAX_PLAYERS];
new ChosenSkin[MAX_PLAYERS];



enum hNews//для Агентства Хитман
{
	hTaken1,
	hTaken2,
	hTaken3,
	hTaken4,
	hTaken5,
	hAdd1[128],
	hAdd2[128],
	hAdd3[128],
	hAdd4[128],
	hAdd5[128],
	hContact1[128],
	hContact2[128],
	hContact3[128],
	hContact4[128],
	hContact5[128]
};
new News[hNews];

/*
static const color_fractions[] =
{
	0x0000003C,//0xF6F6F63C(белый 60 прозрачность) /0x0000003C(черный 60 прозрачность)  [0xFF000069]
	TEAM_GROVE_COLOR,
	TEAM_BALLAS_COLOR,
	TEAM_AZTECAS_COLOR,
	TEAM_VAGOS_COLOR,
	TEAM_NANG_COLOR,
	TEAM_RIFA_COLOR,
	TEAM_TRIADS_COLOR,
	TEAM_BIKERS_COLOR,
	TEAM_MAFIA_COLOR,

	COLOR_DARKTURQUOISE,//0xF6F6F63C(белый 60 прозрачность) /0x0000003C(черный 60 прозрачность)  [0xFF000069]
	COLOR_PALEPURPLE,
	COLOR_EMERALD,
	COLOR_MAUVE,
	COLOR_MAUVE,
	COLOR_VIOLET,
	COLOR_CERISE,
	COLOR_HERBAL,
	COLOR_BROWN,
	COLOR_LIGHTORANGE,
	COLOR_LIGHTBROWN
};*/


stock family_OnGameModeInit()
{
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
	
	//устанавливаем всем бандам их цвета (переписываем загруженные из файла) и не меняем их ни когда
	FamilyInfo[TEAM_NONE][fColor] = 0x0000003C;//0xF6F6F63C(белый 60 прозрачность) /0x0000003C(черный 60 прозрачность)  [0xFF000069]
	FamilyInfo[TEAM_GROVE][fColor] = TEAM_GROVE_COLOR;
	FamilyInfo[TEAM_BALLAS][fColor] = TEAM_BALLAS_COLOR;
	FamilyInfo[TEAM_AZTEC][fColor] = TEAM_AZTECAS_COLOR;
	FamilyInfo[TEAM_VAGOS][fColor] = TEAM_VAGOS_COLOR;
	FamilyInfo[TEAM_NANG][fColor] = TEAM_NANG_COLOR;
	FamilyInfo[TEAM_RIFA][fColor] = TEAM_RIFA_COLOR;
	FamilyInfo[TEAM_TRIAD][fColor] = TEAM_TRIADS_COLOR;
	FamilyInfo[TEAM_BIKER][fColor] = TEAM_BIKERS_COLOR;
	FamilyInfo[TEAM_MAFIA][fColor] = TEAM_MAFIA_COLOR;

	FamilyInfo[DoT][fColor] = COLOR_DARKTURQUOISE;//0xF6F6F63C(белый 60 прозрачность) /0x0000003C(черный 60 прозрачность)  [0xFF000069]
	FamilyInfo[FBI][fColor] = COLOR_PALEPURPLE;
	FamilyInfo[DoD][fColor] = COLOR_EMERALD;
	FamilyInfo[DoH][fColor] = COLOR_MAUVE;
	FamilyInfo[LCN][fColor] = COLOR_VIOLET;
	FamilyInfo[Yakuza][fColor] = COLOR_CERISE;
	FamilyInfo[DoJ][fColor] = COLOR_HERBAL;
	FamilyInfo[Hitman][fColor] = COLOR_BROWN;
	FamilyInfo[SAN][fColor] = COLOR_LIGHTORANGE;
	FamilyInfo[DoE][fColor] = COLOR_LIGHTBROWN;
	
	LoadFamiliesSQL();
}


stock family_OnPlayerExitedMenu(playerid, Menu:Current)
{
	if(Current == mVacancies)
	{
		HideMenuForPlayerEx(Current,playerid);
		//TogglePlayerControllableEx(playerid, 1);
		ShowMenuForPlayerEx(mJobMenu1_9,playerid);//то установить основное меню
	}
}

stock family_OnPlayerSelectedMenuRow(playerid, row, Menu:Current)
{
	//new Menu:Current = GetPlayerMenu(playerid);//получить ID меню
	if(Current == mVacancies)
	{
		switch(row)
		{
			case 0://1 DoT
			{
				if(PlayerInfo[playerid][pLeader] == DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
				}
				else if(//PlayerInfo[playerid][pTrashSkill] < 400 &&
						PlayerInfo[playerid][pMember] != DoT+row &&
						PlayerInfo[playerid][pRespect] < (OnlineRecord*200/100))
				{
					//SendClientMessage(playerid, COLOR_GREY, "   Ваш навык водителя мусоровоза меньше 400 !");
					format(strings, sizeof(strings), "   Ваше уважение %d меньше %d !", PlayerInfo[playerid][pRespect], (OnlineRecord*200/100));
					SendClientMessage(playerid, COLOR_GREY, strings);
				}
				else if(PlayerInfo[playerid][pCarLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует водительская лицензия !");
				}
				else if(PlayerInfo[playerid][pFlyLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на полёты !");
				}
				else if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на оружие !");
				}
			    else if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pMember] != DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы уже состоите в какой-то фракции. Для начала увольтесь (USE: /uninvite)!");
				}
			    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob)!");
				}
			    else if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pProfSkill] < 400
					&& FamilyInfo[DoT+row][fMembers] > 1 )
				{
					SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
				}
				else
				{
#if defined vw_sql//#endif
				    new ToBase[49+2];
					format(ToBase, sizeof(ToBase), "SELECT `Leader` FROM `players` WHERE `Leader`=%d", DoT+row);// LIMIT 1
					/*mysql_query(ToBase); mysql_store_result();
					if(mysql_num_rows() == 0)
					{
						if(FamilyInfo[DoT+row][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row);
						//если место лидера пусто
						else if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row);
						//если игрок находится в этой фракции, чтобы не терять профскилл
					}
					mysql_free_result();*/
					new DBResult:db_result = db_query(db_VW, ToBase);
					if(db_num_rows(db_result) == 0)
					{
						if(FamilyInfo[DoT+row][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row);
						//если место лидера пусто
						else if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row);
						//если игрок находится в этой фракции, чтобы не терять профскилл
					}
					db_free_result(db_result);
#endif
					if(!strcmp(FamilyInfo[DoT+row][fLeader], "No-One", true))
					{//если лидер нет, т.е. имя лидера фракции равно "No-One"
						if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row);
						else if(FamilyInfo[DoT+row][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row); //если место лидера пусто
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
					}

				}
				ShowMenuForPlayerEx(mVacancies, playerid);
			}
			case 1://2 FBI
			{
				if(PlayerInfo[playerid][pLeader] == DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
				}
				else if(//PlayerInfo[playerid][pMinerSkill] < 400 &&
						PlayerInfo[playerid][pMember] != DoT+row &&
						PlayerInfo[playerid][pRespect] < (OnlineRecord*200/100))
				{
					//SendClientMessage(playerid, COLOR_GREY, "   Ваш навык шахтёра меньше 400 !");
     				format(strings, sizeof(strings), "   Ваше уважение %d меньше %d !", PlayerInfo[playerid][pRespect], (OnlineRecord*200/100));
					SendClientMessage(playerid, COLOR_GREY, strings);
				}
				else if(PlayerInfo[playerid][pCarLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует водительская лицензия !");
				}
				else if(PlayerInfo[playerid][pFlyLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на полёты !");
				}
				else if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на оружие !");
				}
			    else if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pMember] != DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы уже состоите в какой-то фракции. Для начала увольтесь (USE: /uninvite)!");
				}
			    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob)!");
				}
			    else if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pProfSkill] < 400
					&& FamilyInfo[DoT+row][fMembers] > 1 )
				{
					SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
				}
				else
				{
					if(!strcmp(FamilyInfo[DoT+row][fLeader], "No-One", true))
					{//если лидер нет, т.е. имя лидера фракции равно "No-One"
						if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row);
						else if(FamilyInfo[DoT+row][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row); //если место лидера пусто
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
					}
				}
				ShowMenuForPlayerEx(mVacancies, playerid);
			}
			case 2://3 DoD
			{
				if(PlayerInfo[playerid][pLeader] == DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
				}
				else if(//PlayerInfo[playerid][pLoadSkill] < 400 &&
						PlayerInfo[playerid][pMember] != DoT+row &&
						PlayerInfo[playerid][pRespect] < (OnlineRecord*200/100))
				{
					//SendClientMessage(playerid, COLOR_GREY, "   Ваш навык грузчика меньше 400 !");
					format(strings, sizeof(strings), "   Ваше уважение %d меньше %d !", PlayerInfo[playerid][pRespect], (OnlineRecord*200/100));
					SendClientMessage(playerid, COLOR_GREY, strings);
				}
				else if(PlayerInfo[playerid][pCarLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует водительская лицензия !");
				}
				else if(PlayerInfo[playerid][pFlyLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на полёты !");
				}
				else if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на оружие !");
				}
			    else if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pMember] != DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы уже состоите в какой-то фракции. Для начала увольтесь (USE: /uninvite)!");
				}
			    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob)!");
				}
			    else if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pProfSkill] < 400
					&& FamilyInfo[DoT+row][fMembers] > 1 )
				{
					SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
				}
				else
				{
					if(!strcmp(FamilyInfo[DoT+row][fLeader], "No-One", true))
					{//если лидер нет, т.е. имя лидера фракции равно "No-One"
						if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row);
						else if(FamilyInfo[DoT+row][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row); //если место лидера пусто
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
					}
				}
				ShowMenuForPlayerEx(mVacancies, playerid);
			}
			case 3://4 DoH
			{
				if(PlayerInfo[playerid][pLeader] == DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
				}
				else if(//PlayerInfo[playerid][pRoadSkill] < 400 &&
						PlayerInfo[playerid][pMember] != DoT+row &&
						PlayerInfo[playerid][pRespect] < (OnlineRecord*200/100))
				{
					//SendClientMessage(playerid, COLOR_GREY, "   Ваш навык ремонтника дорог меньше 400 !");
					format(strings, sizeof(strings), "   Ваше уважение %d меньше %d !", PlayerInfo[playerid][pRespect], (OnlineRecord*200/100));
					SendClientMessage(playerid, COLOR_GREY, strings);
				}
				else if(PlayerInfo[playerid][pCarLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует водительская лицензия !");
				}
				else if(PlayerInfo[playerid][pFlyLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на полёты !");
				}
			    else if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pMember] != DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы уже состоите в какой-то фракции. Для начала увольтесь (USE: /uninvite)!");
				}
			    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob)!");
				}
			    else if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pProfSkill] < 400
					&& FamilyInfo[DoT+row][fMembers] > 1 )
				{
					SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
				}
				else
				{
					if(!strcmp(FamilyInfo[DoT+row][fLeader], "No-One", true))
					{//если лидер нет, т.е. имя лидера фракции равно "No-One"
						if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row);
						else if(FamilyInfo[DoT+row][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row); //если место лидера пусто
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
					}
				}
				ShowMenuForPlayerEx(mVacancies, playerid);

			}
			case 4://5 LCN
			{
				if(PlayerInfo[playerid][pLeader] == DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
				}
				else if(//PlayerInfo[playerid][pDrugsSkill] < 2000 &&
						PlayerInfo[playerid][pMember] != DoT+row &&
						PlayerInfo[playerid][pRespect] < (OnlineRecord*150/100))
				{
					//SendClientMessage(playerid, COLOR_GREY, "   Ваш навык наркодилера меньше 2000 !");
					format(strings, sizeof(strings), "   Ваше уважение %d меньше %d !", PlayerInfo[playerid][pRespect], (OnlineRecord*150/100));
					SendClientMessage(playerid, COLOR_GREY, strings);
				}
				else if(PlayerInfo[playerid][pCarLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует водительская лицензия !");
				}
				else if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на оружие !");
				}
			    else if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pMember] != DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы уже состоите в какой-то фракции. Для начала увольтесь (USE: /uninvite)!");
				}
			    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob)!");
				}
			    else if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pProfSkill] < 400
					&& FamilyInfo[DoT+row][fMembers] > 1 )
				{
					SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
				}
				else
				{
					if(!strcmp(FamilyInfo[DoT+row][fLeader], "No-One", true))
					{//если лидер нет, т.е. имя лидера фракции равно "No-One"
						if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row);
						else if(FamilyInfo[DoT+row][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row); //если место лидера пусто
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
					}
				}
				ShowMenuForPlayerEx(mVacancies, playerid);
			}
			case 5://6 Yakuza
			{
				if(PlayerInfo[playerid][pLeader] == DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
				}
				else if(//PlayerInfo[playerid][pGunSkill] < 400 &&
						PlayerInfo[playerid][pMember] != DoT+row &&
				    	PlayerInfo[playerid][pRespect] < (OnlineRecord*150/100))
				{
					//SendClientMessage(playerid, COLOR_GREY, "   Ваш навык оружейника меньше 400 !");
					format(strings, sizeof(strings), "   Ваше уважение %d меньше %d !", PlayerInfo[playerid][pRespect], (OnlineRecord*150/100));
					SendClientMessage(playerid, COLOR_GREY, strings);
				}
				else if(PlayerInfo[playerid][pCarLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует водительская лицензия !");
				}
				else if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на оружие !");
				}
			    else if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pMember] != DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы уже состоите в какой-то фракции. Для начала увольтесь (USE: /uninvite)!");
				}
			    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob)!");
				}
			    else if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pProfSkill] < 400
					&& FamilyInfo[DoT+row][fMembers] > 1 )
				{
					SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
				}
				else
				{
					if(!strcmp(FamilyInfo[DoT+row][fLeader], "No-One", true))
					{//если лидер нет, т.е. имя лидера фракции равно "No-One"
						if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row);
						else if(FamilyInfo[DoT+row][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row); //если место лидера пусто
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
					}
				}
				ShowMenuForPlayerEx(mVacancies, playerid);
			}
			case 6://7 DoJ
			{
				if(PlayerInfo[playerid][pLeader] == DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
				}
				else if(//PlayerInfo[playerid][pBookmakerSkill] < 100 &&
						PlayerInfo[playerid][pMember] != DoT+row &&
						PlayerInfo[playerid][pRespect] < (OnlineRecord*200/100))
				{
					//SendClientMessage(playerid, COLOR_GREY, "   Ваш навык букмекера меньше 100 !");
					format(strings, sizeof(strings), "   Ваше уважение меньше %d !", (OnlineRecord*400/10));
					SendClientMessage(playerid, COLOR_GREY, strings);
				}
				else if(PlayerInfo[playerid][pCarLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует водительская лицензия !");
				}
			    else if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pMember] != DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы уже состоите в какой-то фракции. Для начала увольтесь (USE: /uninvite)!");
				}
			    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob)!");
				}
				else if(PlayerInfo[playerid][pRespect] < 32)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Для поста губернатора необходимо 32 очка уважения!");
				}
			    else if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pProfSkill] < 400
					&& FamilyInfo[DoT+row][fMembers] > 1 )
				{
					SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
				}
				else
				{
					if(!strcmp(FamilyInfo[DoT+row][fLeader], "No-One", true))
					{//если лидер нет, т.е. имя лидера фракции равно "No-One"
						if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row);
						else if(FamilyInfo[DoT+row][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row); //если место лидера пусто
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
					}
				}
				ShowMenuForPlayerEx(mVacancies, playerid);
			}
			case 7://8 Hitman
			{
				if(PlayerInfo[playerid][pLeader] == DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
				}
				else if(//PlayerInfo[playerid][pJackSkill] < 400 &&
						PlayerInfo[playerid][pMember] != DoT+row &&
     					PlayerInfo[playerid][pRespect] < (OnlineRecord*200/100))
				{
					//SendClientMessage(playerid, COLOR_GREY, "   Ваш навык автоугонщика меньше 400 !");
					format(strings, sizeof(strings), "   Ваше уважение %d меньше %d !", PlayerInfo[playerid][pRespect], (OnlineRecord*200/100));
					SendClientMessage(playerid, COLOR_GREY, strings);
				}
				else if(PlayerInfo[playerid][pCarLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует водительская лицензия !");
				}
				else if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на оружие !");
				}
			    else if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pMember] != DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы уже состоите в какой-то фракции. Для начала увольтесь (USE: /uninvite)!");
				}
			    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob)!");
				}
			    else if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pProfSkill] < 400
					&& FamilyInfo[DoT+row][fMembers] > 1 )
				{
					SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
				}
				else
				{
					if(!strcmp(FamilyInfo[DoT+row][fLeader], "No-One", true))
					{//если лидер нет, т.е. имя лидера фракции равно "No-One"
						if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row);
						else if(FamilyInfo[DoT+row][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row); //если место лидера пусто
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
					}
				}
				ShowMenuForPlayerEx(mVacancies, playerid);
			}
			case 8://9 SAN
			{
				if(PlayerInfo[playerid][pLeader] == DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
				}
				else if(PlayerInfo[playerid][pCourierSkill] < 400 && PlayerInfo[playerid][pMember] != DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Ваш навык курьера меньше 400 !");
				}
				else if(PlayerInfo[playerid][pCarLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует водительская лицензия !");
				}
				else if(PlayerInfo[playerid][pFlyLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на полёты !");
				}
			    else if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pMember] != DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы уже состоите в какой-то фракции. Для начала увольтесь (USE: /uninvite)!");
				}
			    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob)!");
				}
			    else if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pProfSkill] < 400
					&& FamilyInfo[DoT+row][fMembers] > 1 )
				{
					SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
				}
				else
				{
					if(!strcmp(FamilyInfo[DoT+row][fLeader], "No-One", true))
					{//если лидер нет, т.е. имя лидера фракции равно "No-One"
						if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row);
						else if(FamilyInfo[DoT+row][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row); //если место лидера пусто
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
					}
				}
				ShowMenuForPlayerEx(mVacancies, playerid);
			}
			case 9://10 DoE
			{
				if(PlayerInfo[playerid][pLeader] == DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
				}
				else if(PlayerInfo[playerid][pBusSkill] < 400 &&
						PlayerInfo[playerid][pMember] != DoT+row &&
						PlayerInfo[playerid][pRespect] < (OnlineRecord*200/100))
				{
					SendClientMessage(playerid, COLOR_GREY, "   Ваш навык водителя автобуса меньше 400 !");
					format(strings, sizeof(strings), "   Ваше уважение %d меньше %d !", PlayerInfo[playerid][pRespect], (OnlineRecord*200/100));
					SendClientMessage(playerid, COLOR_GREY, strings);
				}
				else if(PlayerInfo[playerid][pCarLic] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует водительская лицензия !");
				}
			    else if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pMember] != DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы уже состоите в какой-то фракции. Для начала увольтесь (USE: /uninvite)!");
				}
			    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != DoT+row)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob)!");
				}
			    else if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pProfSkill] < 400
					&& FamilyInfo[DoT+row][fMembers] > 1 )
				{
					SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
				}
				else
				{
					if(!strcmp(FamilyInfo[DoT+row][fLeader], "No-One", true))
					{//если лидер нет, т.е. имя лидера фракции равно "No-One"
						if(PlayerInfo[playerid][pMember] == DoT+row && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row);
						else if(FamilyInfo[DoT+row][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+row); //если место лидера пусто
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
					}
				}
				ShowMenuForPlayerEx(mVacancies, playerid);
			}
			case 10://UnInvite
			{//178.124.35.222
			    if(PlayerInfo[playerid][pMember] == 0)
			    {
        			SendClientMessage(playerid, COLOR_GREY, "   Вы не являетесь членом организации !");
				}
				else if(GetPVarInt(playerid, "gShowDialog") != -1)
			    {
        			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете в данный момент уволиться! Закройте диалоговое окно!");
				}
				else
				{
					//new member = PlayerInfo[playerid][pMember];
					format(strings, sizeof(strings), "* Вы подали в отставку. Вы теперь снова Гражданский.", PlayerName(playerid));
					SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
					UninvitePlayerid(MAX_PLAYERS-1, playerid, PlayerName(playerid));
					//format(strings, sizeof(strings), "AdmCmd: %s has uninvited from Faction %d.", PlayerName(playerid), member);
					//Log(INVITE,strings);
				}
				ShowMenuForPlayerEx(mVacancies, playerid);
			}
		}
	}
}//для устройства на работу конец

stock family_OnPlayerConnect(playerid)
{
	//ProposedFamily[playerid] = 0;//	Offer[playerid] = MAX_PLAYERS-1;

	//gStatusRegistration[playerid] = 0;//чтобы нельзя было запустить несколько таймеров
	SelectChar[playerid] = 0; SelectCharID[playerid] = 0; SelectCharPlace[playerid] = 0; ChosenSkin[playerid] = 0;//для invite



	CallTime[playerid] = 0; CallTimeCounter[playerid] = 0;

	Offer[playerid] = MAX_PLAYERS-1; //Offer[playerid] = MAX_PLAYERS-1;




	
//для копов
	TicketMoney[playerid] = 0;
	PlayerTazed[playerid] = 0; PlayerTazeTime[playerid] = 0;
	PlayerTied[playerid] = 0; PlayerTiedTime[playerid] = 0;
	PlayerCuffed[playerid] = MAX_PLAYERS-1; PlayerCuffedTime[playerid] = 0;
//ClearCrime(playerid);//нельзя снижать уровень преступности
	new strtmp[] = "********************";
	strmid(PlayerCrime[playerid][pAccusedof], strtmp, 0, strlen(strtmp), 128);
	strmid(PlayerCrime[playerid][pVictim], strtmp, 0, strlen(strtmp), 20);
	strmid(PlayerCrime[playerid][pAccusing], strtmp, 0, strlen(strtmp), 128);
	strmid(PlayerCrime[playerid][pBplayer], strtmp, 0, strlen(strtmp), 20);
	WantedPoints[playerid] = 0;//убрали очки розыска
	WantedLevel[playerid] = 0;//убрали уровень розыска
	SetPlayerWantedLevel(playerid, 0);//убрали звёзды



}


stock family_OnPlayerSpawn(playerid)
{
	if( (PlayerInfo[playerid][pMember] >= DoT && PlayerInfo[playerid][pMember] <= DoH) &&
		(PlayerInfo[playerid][pCrimes] > CriminalLevel))// || PlayerInfo[playerid][pArrested] > CriminalLevel/10
	{
		if(PlayerInfo[playerid][pAccount] == 0)
		{
			format(strings, sizeof(strings), "%s {FFFFFF}%s[%d]: {FFFF00}покинул фракцию %s из-за большого кол-ва преступлений.",
				GetPlayerRanks(playerid), PlayerName(playerid), playerid, GetPlayerMembers(playerid));
			//SendClientMessageToAll(COLOR_LIGHTBLUE, strings);
			OOCNews(COLOR_HERBAL, "|_____________________________________ Правительственное сообщение _____________________________________|");
			OOCNews(COLOR_LIGHTBLUE, strings);
			//OOCNews(COLOR_HERBAL, "|__________________________________________________________________________________________________________|");
			UninvitePlayerid(MAX_PLAYERS-1, playerid, PlayerName(playerid));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Вы теперь снова Гражданский.");
		}
	}
	
//для скрытия ников
	if(PlayerInfo[playerid][pMember] >= Hitman && gTagForPlayer[playerid])
	{
//при старте режима ники всех видны
		gTagForPlayer[playerid] = 0;//поставили, что ник скрыт данного игрока
		//for(new i = 0; i < MAX_PLAYERS; i++) ShowPlayerNameTagForPlayerEx(playerid, i, 1);//для игрока playerid показать ники всех игроков
	}
}

stock family_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	//#pragma unused listitem
	//#pragma unused inputtext
	IncreaseRankDialogResponse(playerid, dialogid, response, listitem, inputtext);
	
	if(dialogid != INVITE_DIALOG) return 1;
	
	if(!response)
	{
		Offer[playerid] = MAX_PLAYERS-1;
		MenuOperation[playerid] = 0;
		return 1;
	}
	new family = PlayerInfo[Offer[playerid]][pMember];
	//----------------------------------------------------------------------
	if(family == TEAM_GROVE) { ChosenSkin[playerid] = 106; }
	else if(family == TEAM_BALLAS) { ChosenSkin[playerid] = 103; }
	else if(family == TEAM_AZTEC) { ChosenSkin[playerid] = 115; }
	else if(family == TEAM_VAGOS) { ChosenSkin[playerid] = 109; }
	else if(family == TEAM_NANG) { ChosenSkin[playerid] = 122; }
	else if(family == TEAM_RIFA) { ChosenSkin[playerid] = 174; }
	else if(family == TEAM_TRIAD) { ChosenSkin[playerid] = 118; }
	else if(family == TEAM_BIKER) { ChosenSkin[playerid] = 248; }
	else if(family == TEAM_MAFIA) { ChosenSkin[playerid] = 112; }
	else if(family == DoT)
	{
		if(PlayerInfo[playerid][pCarLic] == 0) PlayerInfo[playerid][pCarLic] = 1;
		if(PlayerInfo[playerid][pGunLic] == 0) PlayerInfo[playerid][pGunLic] = 1;
		ChosenSkin[playerid] = 280;
	}
	else if(family == FBI)
	{
		if(PlayerInfo[playerid][pGunLic] == 0) PlayerInfo[playerid][pGunLic] = 1;
		ChosenSkin[playerid] = 286;
	}
	else if(family == DoD)
	{
		if(PlayerInfo[playerid][pGunLic] == 0) PlayerInfo[playerid][pGunLic] = 1;
		ChosenSkin[playerid] = 206;
		if(PlayerInfo[playerid][pRank] == 6)
		{
			GivePlayerMoneyB(ffamily+PlayerInfo[Offer[playerid]][pMember], Offer[playerid], DutyFiveMinuts*PlayerInfo[Offer[playerid]][pRank]);//перечислить игроку зарплату
			IncreaseRank(Offer[playerid], 10);
		}
	}
	else if(family == DoH) { ChosenSkin[playerid] = 71; }
	else if(family == LCN) { ChosenSkin[playerid] = 46; }
	else if(family == Yakuza) { ChosenSkin[playerid] = 228; }
	else if(family == DoJ) { ChosenSkin[playerid] = 296; }//если вы МЭР выйти из функции
	else if(family == Hitman) {	ChosenSkin[playerid] = 294;	}
	else if(family == SAN) { ChosenSkin[playerid] = 187; }
	else if(family == DoE) { ChosenSkin[playerid] = 240; }
	else return 1;

	PlayerInfo[playerid][pMember] = family;
	PlayerInfo[playerid][pRank] = 1;
	PlayerInfo[playerid][pProfSkill] = 0;

    SetPlayerSkinEx(playerid, ChosenSkin[playerid]);
    PlayerInfo[playerid][pChar] = ChosenSkin[playerid];
    if(	PlayerInfo[playerid][pMember] >= TEAM_GROVE &&
		PlayerInfo[playerid][pMember] <= TEAM_MAFIA) PlayerInfo[playerid][pModel] = ChosenSkin[playerid];
	OnPlayerSetDutyWeapons(playerid);//запускаем ф-ию установки оружия
	FamilyInfo[family][fMembers] ++;
	//format(strcmd, sizeof(strcmd), "AdmCmd: %s has invite %s's to Faction %d.", PlayerName(playerid), PlayerName(giveplayerid), family);
	//Log(INVITE,strcmd);
#if defined vw_sql//#endif
	InviteList(Offer[playerid], PlayerName(playerid), family, PlayerInfo[playerid][pRank], 1);
#endif
	Offer[playerid] = MAX_PLAYERS-1;
	SendClientMessage(playerid, COLOR_GREY, "   Чтобы покинуть фракцию (USE: /uninvite)");
	return 1;
}

/*
stock invite_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != INVITE_DIALOG) return 1;
	
	if(!response)
	{
		Offer[playerid] = MAX_PLAYERS-1;
		MenuOperation[playerid] = 0;
		return 1;
	}
	///new msgitem[256+1];
	//new giveplayerid;
//ShowPlayerDialogGap(playerid, INVITE_DIALOG, DIALOG_STYLE_MSGBOX, "Invite", msgitem, "Accept", "Cancel");
	//if(MenuOperation[playerid] != 111) return 1;
	new family = SelectCharID[playerid];
	PlayerInfo[playerid][pMember] = family;
	PlayerInfo[playerid][pRank] = 1;
	FamilyInfo[family][fMembers] ++;
	SelectCharID[playerid] = 0;
	SaveFamiliesSQL(PlayerName(playerid));
	SendClientMessage(playerid, COLOR_GREY, "   Чтобы покинуть фракцию (USE: /uninvite)");
	return 1;
}*/



/*
"%s%d\tЦель: %s[%d]\tВознаграждение: $%d\n",
2+2+5+1+24+1+3+1+2+15+1+1+10+2 + 10(на всякий)=80*30=2400
и прабавь +12  new strings[3512];
*/

stock family_OnPlayerDisconnect(playerid, reason)
{
	new strreason[10];
    switch(reason)
    {
        case 0: strcat(strreason, "TimedOut");
        case 1: strcat(strreason, "Leaving");
        case 2: strcat(strreason, "Kicked");
    }

	if(WantedLevel[playerid] > 0 && LevelToCriminality > 0)
	{
		LevelToCriminality --;
		format(strings, sizeof(strings), "Tекущий Уровень Преступности в штате: %d - %s[%d].", LevelToCriminality, PlayerName(playerid), playerid);
		SendTeamMessage(DoT, COLOR_PALEGREEN, strings);
		SendTeamMessage(FBI, COLOR_PALEGREEN, strings);
		SendTeamMessage(DoJ, COLOR_PALEGREEN, strings);
	}
	if((PlayerInfo[playerid][pJailed] >= 1 && PlayerInfo[playerid][pJailed] <= 3)
		&& PlayerInfo[playerid][pArticle] >= 139) { if(LevelToDeliver > 0) LevelToDeliver --; }

	if(PlayerInfo[playerid][pSTD] > 0 && PlayerInfo[playerid][pSTD] < IsNotBeenIll
		&& LevelToEpidemics > 0) LevelToEpidemics --;
	//==========================================================================
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if(!IsPlayerConnected(i)) continue;
        if(playerid != gGotOrder[i]) continue;
		//если игрок на которого у всех есть ордер вышел
		gGotOrder[i] = MAX_PLAYERS-1;
	}

	//==========================================================================
	if(gOnDuty[playerid] == 1)//после деинициализации всех работ
	{
        if(PlayerInfo[playerid][pMember] == DoD)
        {
   			MilitaryCounter --;
   			FamilyInfo[DoD][fMaterial] ++;
        }
        else if(PlayerInfo[playerid][pMember] == DoH)
        {
   			MedicCounter --;
        }
        gOnDuty[playerid] = 0;
        //DeletePVar(playerid, "dutylist");
        strdel(dutylist[playerid], 0, sizeof(dutylist));
	}
}





stock family_OnPlayerDeath(playerid, killerid)
{   //вызывается из OnPlayerDeath
	#pragma unused killerid
	if(gOnDuty[playerid])//перемещено из if(newstate == PLAYER_STATE_WASTED) т.к. не работало переодевание в вояку
	{
		gOnDuty[playerid] = 0;
		//DeletePVar(playerid, "dutylist");
		strdel(dutylist[playerid], 0, sizeof(dutylist));
	}
}



//stock DutyPickUp(playerid)
stock family_OnPlayerPickUp(playerid, pickupid)
{
 	#pragma unused pickupid
	//new strings[MAX_STRING];
	// /duty для выхода на дежурство
/*
	if(	IsPlayerInRangeOfPoint(playerid, 1.9, 254.4151,79.1228,1003.6406) ||//ЛС участок
		IsPlayerInRangeOfPoint(playerid, 1.9, 236.2644,120.0462,1003.2188) ||//СФ участок
		IsPlayerInRangeOfPoint(playerid, 1.9, 215.6492,182.4046,1003.0313))//ЛВ участок
*/
	if(	IsPlayerInRangeOfPoint(playerid, 1.9, 330.0488,-312.5763,1024.6902) ||//ЛС участок
		IsPlayerInRangeOfPoint(playerid, 1.9, 997.4426,348.6700,1004.2559) ||//СФ участок
		IsPlayerInRangeOfPoint(playerid, 1.9, -2466.3848,513.0441,54.5687))//ЛВ участок
	{
		CrashDetected[playerid] = 94;
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
		if(gOnDuty[playerid] == 0 && IsACop(playerid))
       	{
       		/*PlayerInfo[playerid][pTeam] = 1;*/
			PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			if(PlayerInfo[playerid][pMember] == DoT)//IsACop(playerid)
			{
				if(PlayerInfo[playerid][pSex] == Male)
				{
					if(PlayerInfo[playerid][pRank] == 1) PlayerInfo[playerid][pChar] = 280;
					else if(PlayerInfo[playerid][pRank] == 2) PlayerInfo[playerid][pChar] = 280;
					else if(PlayerInfo[playerid][pRank] == 3) PlayerInfo[playerid][pChar] = 281;
					else if(PlayerInfo[playerid][pRank] == 4) PlayerInfo[playerid][pChar] = 281;
					else if(PlayerInfo[playerid][pRank] == 5) PlayerInfo[playerid][pChar] = 267;
					else if(PlayerInfo[playerid][pRank] == 6) PlayerInfo[playerid][pChar] = 267;//267;
					else if(PlayerInfo[playerid][pRank] == 7) PlayerInfo[playerid][pChar] = 266;//266;
					else if(PlayerInfo[playerid][pRank] == 8) PlayerInfo[playerid][pChar] = 266;//265;
					else if(PlayerInfo[playerid][pRank] == 9) PlayerInfo[playerid][pChar] = 265;//265;
					else if(PlayerInfo[playerid][pRank] == 10) PlayerInfo[playerid][pChar] = 282;
					else if(PlayerInfo[playerid][pRank] == 11) PlayerInfo[playerid][pChar] = 283;
					else if(PlayerInfo[playerid][pRank] == 12) PlayerInfo[playerid][pChar] = 288;
				    else PlayerInfo[playerid][pChar] = 280;
				}
				SetPlayerSkinEx(playerid, PlayerInfo[playerid][pChar]);
				TogglePlayerControllableEx(playerid, 1);
				gOnDuty[playerid] = 1;
		    	format(strings, sizeof(strings), "* Инспектор ДПС %s получил Оружие.", PlayerName(playerid));
				ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
				OnPlayerSetDutyWeapons(playerid);//запускаем ф-ию установки членам фракций оружия при спауне,

				GiveDoTEquip(playerid);
			}
			else if(PlayerInfo[playerid][pMember] == FBI)//IsACop(playerid)
			{
				if(PlayerInfo[playerid][pSex] == Male)
				{
					if(PlayerInfo[playerid][pRank] == 1) PlayerInfo[playerid][pChar] = 286;//217
					else if(PlayerInfo[playerid][pRank] == 2) PlayerInfo[playerid][pChar] = 164;//217
					else if(PlayerInfo[playerid][pRank] == 3) PlayerInfo[playerid][pChar] = 286;
					else if(PlayerInfo[playerid][pRank] == 4) PlayerInfo[playerid][pChar] = 285;
					else if(PlayerInfo[playerid][pRank] == 5) PlayerInfo[playerid][pChar] = 286;
					else if(PlayerInfo[playerid][pRank] == 6) PlayerInfo[playerid][pChar] = 285;
					else if(PlayerInfo[playerid][pRank] == 7) PlayerInfo[playerid][pChar] = 286;
					else if(PlayerInfo[playerid][pRank] == 8) PlayerInfo[playerid][pChar] = 285;
					else if(PlayerInfo[playerid][pRank] == 9) PlayerInfo[playerid][pChar] = 286;//166
					else if(PlayerInfo[playerid][pRank] == 10) PlayerInfo[playerid][pChar] = 285;
					else if(PlayerInfo[playerid][pRank] == 11) PlayerInfo[playerid][pChar] = 166;
					else if(PlayerInfo[playerid][pRank] == 12) PlayerInfo[playerid][pChar] = 165;
					else PlayerInfo[playerid][pChar] = 217;
				}
				SetPlayerSkinEx(playerid, PlayerInfo[playerid][pChar]);
				TogglePlayerControllableEx(playerid, 1);
				gOnDuty[playerid] = 1;
		    	format(strings, sizeof(strings), "* Агент ФБР %s получил Оружие.", PlayerName(playerid));
				ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
				OnPlayerSetDutyWeapons(playerid);//запускаем ф-ию установки членам фракций оружия при спауне,

				//GiveDoTEquip(playerid);
			}
		}
		else if(gOnDuty[playerid] == 1 && IsACop(playerid))
		{
			/*PlayerInfo[playerid][pTeam] = 3;*/
			PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			//--------------------------------------------------
			SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
			//--------------------------------------------------
			ResetPlayerWeaponsEx(playerid);
			gOnDuty[playerid] = 0;
			TogglePlayerControllableEx(playerid, 1);
			format(strings, sizeof(strings), "* Офицер %s сдал Оружие.", PlayerName(playerid));
			ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
			GiveDoTEquip(playerid);
		}
		//return 1;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 1.9, 216.2147,1937.9592,13.9359) ||
			IsPlayerInRangeOfPoint(playerid, 1.9, -1349.3029,500.9380,18.2344))// NG duty
	{
		CrashDetected[playerid] = 95;
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
		if(PlayerInfo[playerid][pMember] == DoD && !gInRacing[playerid])
		{
			PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			if(gOnDuty[playerid] == 0 && PlayerInfo[playerid][pRank] >= 2)// && FamilyInfo[DoD][fMaterial] > 1)
	        {
	        	/*PlayerInfo[playerid][pTeam] = 1;*/
				if(PlayerInfo[playerid][pSex] == Male)
				{
					if(PlayerInfo[playerid][pRank] > 6) PlayerInfo[playerid][pChar] = 287;//солдат по форме
					else if(PlayerInfo[playerid][pRank] == 6) PlayerInfo[playerid][pChar] = 179;//бывалый солдат с лычками
				    else PlayerInfo[playerid][pChar] = 206;//солдат в джинсах и зелёной майке
				}
				SetPlayerSkinEx(playerid, PlayerInfo[playerid][pChar]);
				gOnDuty[playerid] = 1;
				MilitaryCounter ++;
				FamilyInfo[DoD][fMaterial] --;
		    	format(strings, sizeof(strings), "%s получил Оружие.", PlayerName(playerid));
				ProxDetector(playerid, 30.0,  strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
				OnPlayerSetDutyWeapons(playerid);//запускаем ф-ию установки членам фракций оружия при спауне,
			}
			else if(gOnDuty[playerid] == 1)
			{
				/*PlayerInfo[playerid][pTeam] = 3;*/
		    	PlayerInfo[playerid][pModel] = 73;//солдат в тапачках бандане и камуфляжных штанах
				SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
				ResetPlayerWeaponsEx(playerid);
				SetPlayerArmourEx(playerid, 0.0);//armour
				gOnDuty[playerid] = 0;
				gJobDuty[playerid] = 0;
				MilitaryCounter --;
				FamilyInfo[DoD][fMaterial] ++;
				//DeletePVar(playerid, "dutylist");
				format(strings, sizeof(strings), "%s сдал Оружие.", PlayerName(playerid));
				ProxDetector(playerid, 30.0,  strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
			}
			//else SendClientMessage(playerid, COLOR_GREY, "   Вы не можете получить оружие, т.к. нету оружия на складе!");
		}
		//return 1;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 1.9, 1165.7561,1353.2611,10.9219))//Медики
	{
		CrashDetected[playerid] = 96;
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
		if(PlayerInfo[playerid][pMember] == DoH && !GetPVarInt(playerid, "gInRacing"))
		{
			PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			if( !IsInAmbulanceCar(nCarID[playerid]) &&
				!IsAtHospital(playerid))
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы должны находится в мед. транспорте или в Госпитале !");
			    return 1;
			}
		    if(gOnDuty[playerid] == 1)
		    {
		    	if(IsPlayerAttachedObjectSlotUsed(playerid, DUTY_SLOT)) RemovePlayerAttachedObject(playerid, DUTY_SLOT);
		    	/*PlayerInfo[playerid][pTeam] = 3;*/
		        SendClientMessage(playerid, COLOR_ORANGE, "   Вы теперь Не на Дежурстве вашей Медицинской Службы и не получаете вызовы больше.");
		        gOnDuty[playerid] = 0;//	gOnDuty[playerid] = 1;
		        MedicCounter --;
  				//DeletePVar(playerid, "dutylist");
  				strdel(dutylist[playerid], 0, sizeof(dutylist));
  				SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
		    }
		    else
		    {
		    	/*PlayerInfo[playerid][pTeam] = 1;*/
				/*if(PlayerInfo[playerid][pSex] == Male)
				{
					if(PlayerInfo[playerid][pRank] == 1) PlayerInfo[playerid][pChar] = 176;//217
					else if(PlayerInfo[playerid][pRank] == 2) PlayerInfo[playerid][pChar] = 176;//217
					else if(PlayerInfo[playerid][pRank] == 3) PlayerInfo[playerid][pChar] = 177;
					else if(PlayerInfo[playerid][pRank] == 4) PlayerInfo[playerid][pChar] = 177;
					else if(PlayerInfo[playerid][pRank] == 5) PlayerInfo[playerid][pChar] = 276;
					else if(PlayerInfo[playerid][pRank] == 6) PlayerInfo[playerid][pChar] = 276;
					else if(PlayerInfo[playerid][pRank] == 7) PlayerInfo[playerid][pChar] = 276;
					else if(PlayerInfo[playerid][pRank] == 8) PlayerInfo[playerid][pChar] = 274;
					else if(PlayerInfo[playerid][pRank] == 9) PlayerInfo[playerid][pChar] = 274;//166
					else if(PlayerInfo[playerid][pRank] == 10) PlayerInfo[playerid][pChar] = 274;
					else if(PlayerInfo[playerid][pRank] == 11) PlayerInfo[playerid][pChar] = 275;
					else if(PlayerInfo[playerid][pRank] == 12) PlayerInfo[playerid][pChar] = 70;
					else PlayerInfo[playerid][pChar] = 176;
				}*/
				if(PlayerInfo[playerid][pSex] == Male)
				{
					if(PlayerInfo[playerid][pRank] == 1) PlayerInfo[playerid][pChar] = 176;//217
					else if(PlayerInfo[playerid][pRank] == 2) PlayerInfo[playerid][pChar] = 176;//217
					else if(PlayerInfo[playerid][pRank] == 3) PlayerInfo[playerid][pChar] = 177;
					else if(PlayerInfo[playerid][pRank] == 4) PlayerInfo[playerid][pChar] = 177;
					else if(PlayerInfo[playerid][pRank] == 5) PlayerInfo[playerid][pChar] = 278;//LV//для пожарников
					else if(PlayerInfo[playerid][pRank] == 6) PlayerInfo[playerid][pChar] = 277;//LS
					else if(PlayerInfo[playerid][pRank] == 7) PlayerInfo[playerid][pChar] = 279;//SF
					else if(PlayerInfo[playerid][pRank] == 8) PlayerInfo[playerid][pChar] = 274;
					else if(PlayerInfo[playerid][pRank] == 9) PlayerInfo[playerid][pChar] = 274;//166
					else if(PlayerInfo[playerid][pRank] == 10) PlayerInfo[playerid][pChar] = 274;
					else if(PlayerInfo[playerid][pRank] == 11) PlayerInfo[playerid][pChar] = 275;
					else if(PlayerInfo[playerid][pRank] == 12) PlayerInfo[playerid][pChar] = 70;
					else PlayerInfo[playerid][pChar] = 176;
				}
				SetPlayerSkinEx(playerid, PlayerInfo[playerid][pChar]);
		        //SendClientMessage(playerid, COLOR_ORANGE, "   Вы теперь на Дежурстве вашей Медицинской Службы и получаете вызовы от нуждающихся людей.");
		        gOnDuty[playerid] = 1;
		        SetPlayerAttachedObjectEx(playerid, DUTY_SLOT, 327, Right_hand, 0.030460,-0.06,-0.200000, 28.326126,350.425476,0.0, 4.0,4.0,4.0);

		        MedicCounter ++;
				OnPlayerSetDutyWeapons(playerid);
   				format(strings, sizeof(strings), "Mедик {FFFFFF}%s[%d]", PlayerName(playerid), playerid);
   				SendClientMessage(playerid, COLOR_MAUVE, strings);
				new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
				//format(strings, sizeof(strings), "{AFAFAF}[%d:%02d:%02d] {FF00FF}%s\n", lH,lM,lS, strings);
				//SetPVarString(playerid, "dutylist", strings);
				format(dutylist[playerid], sizeof(dutylist), "{AFAFAF}[%d:%02d:%02d] {FF00FF}%s\n", lH,lM,lS, strings);
		    }
		}
		//return 1;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 1.9, 355.0240,212.9054,1008.3828))//Губернатор
	{
		CrashDetected[playerid] = 97;
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
		if(PlayerInfo[playerid][pMember] == DoJ && !GetPVarInt(playerid, "gInRacing"))
		{
			PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
			//if( !IsPlayerInArea(playerid, specialzone[7]) )
			if(PlayerInfo[playerid][pLocal] != 241)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы должны находится в Мэрии !");
			    return 1;
			}
		    if(gOnDuty[playerid] == 1)
		    {
		    	/*PlayerInfo[playerid][pTeam] = 3;*/
		        SendClientMessage(playerid, COLOR_ORANGE, "   Вы теперь Не на Дежурстве.");
		        gOnDuty[playerid] = 0;
  				SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
  				//DeletePVar(playerid, "dutylist");
		    }
		    else
		    {
		    	/*PlayerInfo[playerid][pTeam] = 1;*/
				if(PlayerInfo[playerid][pSex] == Male)
				{
					if(PlayerInfo[playerid][pRank] == 1) PlayerInfo[playerid][pChar] = 163;//217
					else if(PlayerInfo[playerid][pRank] == 2) PlayerInfo[playerid][pChar] = 17;//217
					else if(PlayerInfo[playerid][pRank] == 3) PlayerInfo[playerid][pChar] = 17;
					else if(PlayerInfo[playerid][pRank] == 4) PlayerInfo[playerid][pChar] = 163;
					else if(PlayerInfo[playerid][pRank] == 5) PlayerInfo[playerid][pChar] = 17;
					else if(PlayerInfo[playerid][pRank] == 6) PlayerInfo[playerid][pChar] = 57;
					else if(PlayerInfo[playerid][pRank] == 7) PlayerInfo[playerid][pChar] = 57;
					else if(PlayerInfo[playerid][pRank] == 8) PlayerInfo[playerid][pChar] = 57;
					else if(PlayerInfo[playerid][pRank] == 9) PlayerInfo[playerid][pChar] = 295;//166
					else if(PlayerInfo[playerid][pRank] == 10) PlayerInfo[playerid][pChar] = 295;
					else if(PlayerInfo[playerid][pRank] == 11) PlayerInfo[playerid][pChar] = 295;
					else if(PlayerInfo[playerid][pRank] == 12) PlayerInfo[playerid][pChar] = 147;
					else PlayerInfo[playerid][pChar] = 163;
				}
				SetPlayerSkinEx(playerid, PlayerInfo[playerid][pChar]);
		        SendClientMessage(playerid, COLOR_ORANGE, "   Вы теперь на Дежурстве.");
		        gOnDuty[playerid] = 1;
		        //MedicCounter ++;
				OnPlayerSetDutyWeapons(playerid);
		    }
		}
		//return 1;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 1.9, 2161.7534,1606.5365,999.9727))//Репортеры
	{
		CrashDetected[playerid] = 99;
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
		if(PlayerInfo[playerid][pMember] == SAN && !GetPVarInt(playerid, "gInRacing"))
		{
			PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
            if(!IsPlayerInRangeOfPoint(playerid, 10.0, 2164.4080,1600.1506,999.9773))
			{
			    SendClientMessage(playerid, COLOR_GREY, "   Вы не в Здания Редакции Новостей !");
			    return 1;
			}
		    if(gOnDuty[playerid] == 1)
		    {
		    	/*PlayerInfo[playerid][pTeam] = 3;*/
		        SendClientMessage(playerid, COLOR_ORANGE, "   Вы теперь Не на Дежурстве Агентства Новостей.");
		        gOnDuty[playerid] = 0;
				//DeletePVar(playerid, "dutylist");
				strdel(dutylist[playerid], 0, sizeof(dutylist));
  				SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
		    }
		    else
		    {
		    	/*PlayerInfo[playerid][pTeam] = 1;*/
				if(PlayerInfo[playerid][pSex] == Male)
				{
					if(PlayerInfo[playerid][pRank] == 1) PlayerInfo[playerid][pChar] = 188;//217
					else if(PlayerInfo[playerid][pRank] == 2) PlayerInfo[playerid][pChar] = 188;//217
					else if(PlayerInfo[playerid][pRank] == 3) PlayerInfo[playerid][pChar] = 188;
					else if(PlayerInfo[playerid][pRank] == 4) PlayerInfo[playerid][pChar] = 188;
					else if(PlayerInfo[playerid][pRank] == 5) PlayerInfo[playerid][pChar] = 261;
					else if(PlayerInfo[playerid][pRank] == 6) PlayerInfo[playerid][pChar] = 20;
					else if(PlayerInfo[playerid][pRank] == 7) PlayerInfo[playerid][pChar] = 20;
					else if(PlayerInfo[playerid][pRank] == 8) PlayerInfo[playerid][pChar] = 185;
					else if(PlayerInfo[playerid][pRank] == 9) PlayerInfo[playerid][pChar] = 184;//166
					else if(PlayerInfo[playerid][pRank] == 10) PlayerInfo[playerid][pChar] = 184;
					else if(PlayerInfo[playerid][pRank] == 11) PlayerInfo[playerid][pChar] = 24;
					else if(PlayerInfo[playerid][pRank] == 12) PlayerInfo[playerid][pChar] = 227;
					else PlayerInfo[playerid][pChar] = 188;
				}
				SetPlayerSkinEx(playerid, PlayerInfo[playerid][pChar]);
		        gOnDuty[playerid] = 1;
				OnPlayerSetDutyWeapons(playerid);
	 			format(strings, sizeof(strings), "Репортёр {FFFFFF}%s[%d]", PlayerName(playerid), playerid);
 				SendClientMessage(playerid, COLOR_GOLDEN, strings);
				new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
				//format(strings, sizeof(strings), "{AFAFAF}[%d:%02d:%02d] {FFCC00}%s\n", lH,lM,lS, strings);
				//SetPVarString(playerid, "dutylist", strings);
				format(dutylist[playerid], sizeof(dutylist), "{AFAFAF}[%d:%02d:%02d] {FFCC00}%s\n", lH,lM,lS, strings);
		    }
		}
		//return 1;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 1.9, -2036.0894,-116.7846,1035.1719))//Лицензоры
	{
		CrashDetected[playerid] = 100;
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
		if(PlayerInfo[playerid][pMember] == DoE && !GetPVarInt(playerid, "gInRacing"))
		{
			PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
       		if(!IsPlayerInRangeOfPoint(playerid, 100.0,-2032.6810,-117.4816,1035.1719) && PlayerInfo[playerid][pAdmin] != 9)
	  		{
				SendClientMessage(playerid, COLOR_GREY, "   Вы должны находиться в автошколе !");
				return 1;
			}
		    if(gOnDuty[playerid] == 1)
		    {
		    	/*PlayerInfo[playerid][pTeam] = 3;*/
		        SendClientMessage(playerid, COLOR_ORANGE, "   Вы теперь Не на Дежурстве.");
		        gOnDuty[playerid] = 0;
  				//DeletePVar(playerid, "dutylist");
  				strdel(dutylist[playerid], 0, sizeof(dutylist));
  				SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
		    }
		    else
		    {
		    	/*PlayerInfo[playerid][pTeam] = 1;*/
				if(PlayerInfo[playerid][pSex] == Male)
				{
					if(PlayerInfo[playerid][pRank] == 1) PlayerInfo[playerid][pChar] = 60;//217
					else if(PlayerInfo[playerid][pRank] == 2) PlayerInfo[playerid][pChar] = 250;//217
					else if(PlayerInfo[playerid][pRank] == 3) PlayerInfo[playerid][pChar] = 250;
					else if(PlayerInfo[playerid][pRank] == 4) PlayerInfo[playerid][pChar] = 250;
					else if(PlayerInfo[playerid][pRank] == 5) PlayerInfo[playerid][pChar] = 250;
					else if(PlayerInfo[playerid][pRank] == 6) PlayerInfo[playerid][pChar] = 250;
					else if(PlayerInfo[playerid][pRank] == 7) PlayerInfo[playerid][pChar] = 170;
					else if(PlayerInfo[playerid][pRank] == 8) PlayerInfo[playerid][pChar] = 170;
					else if(PlayerInfo[playerid][pRank] == 9) PlayerInfo[playerid][pChar] = 240;//166
					else if(PlayerInfo[playerid][pRank] == 10) PlayerInfo[playerid][pChar] = 240;
					else if(PlayerInfo[playerid][pRank] == 11) PlayerInfo[playerid][pChar] = 189;
					else if(PlayerInfo[playerid][pRank] == 12) PlayerInfo[playerid][pChar] = 171;
					else PlayerInfo[playerid][pChar] = 60;
				}
				SetPlayerSkinEx(playerid, PlayerInfo[playerid][pChar]);
		        gOnDuty[playerid] = 1;
				OnPlayerSetDutyWeapons(playerid);
	  			format(strings, sizeof(strings), "Инструктор {FFFFFF}%s[%d]", PlayerName(playerid), playerid);
 				SendClientMessage(playerid, COLOR_LIGHTBROWN, strings);
				new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
				//format(strings, sizeof(strings), "{AFAFAF}[%d:%02d:%02d] {FFCC99}%s\n", lH,lM,lS, strings);
				//SetPVarString(playerid, "dutylist", strings);
				format(dutylist[playerid], sizeof(dutylist), "{AFAFAF}[%d:%02d:%02d] {FFCC99}%s\n", lH,lM,lS, strings);
			}
		}
		//return 1;
	}
	//==========================================================================
	else if(IsPlayerInRangeOfPoint(playerid, 1.9, -253.5860,2596.9019,62.8582))//Дорожники
	{
		CrashDetected[playerid] = 100;
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
		if(gOnDuty[playerid])
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете выйти на работу когда вышли на дежурство.");
			return 1;
		}
		if(PlayerInfo[playerid][pJob] == ROADWORKER && !GetPVarInt(playerid, "gInRacing"))//для ремонтников
		{
			PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
		    if(gJobDuty[playerid] == 1)
		    {
		        SendClientMessage(playerid, COLOR_ORANGE, "   Вы теперь Не на Дежурстве вашей Дорожной Службы и не получаете вызовы больше.");
		        gJobDuty[playerid] = 0;
		        //RoadWorkerCounter -= 1;
				//DeletePVar(playerid, "dutylist");
				strdel(dutylist[playerid], 0, sizeof(dutylist));
  				if(PlayerInfo[playerid][pSex] == Male) SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
		    }
		    else
		    {
		        //SendClientMessage(playerid, COLOR_ORANGE, "   Вы теперь на Дежурстве вашей АвтоРемонтной Службы и получаете вызовы от нуждающихся людей.");
		        gJobDuty[playerid] = 1;
		        //RoadWorkerCounter += 1;
   				format(strings, sizeof(strings), "Дорожный ремонтник {FFFFFF}%s[%d]", PlayerName(playerid), playerid);
				SendClientMessage(playerid, COLOR_ORANGE, strings);
				new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
				//format(strings, sizeof(strings), "{AFAFAF}[%d:%02d:%02d] {B8860B}%s\n", lH,lM,lS, strings);
				//SetPVarString(playerid, "dutylist", strings);
				format(dutylist[playerid], sizeof(dutylist), "{AFAFAF}[%d:%02d:%02d] {B8860B}%s\n", lH,lM,lS, strings);
  				if(PlayerInfo[playerid][pSex] == Male) SetPlayerSkinEx(playerid, 260);
		    }
		}
		//return 1;
	}

	/*else if(IsPlayerInRangeOfPoint(playerid, 1.9, -2052.5383,149.0857,28.8359))//для автоугонщиков
	{
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
		if(gOnDuty[playerid])
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете выйти на работу когда вышли на дежурство.");
			return 1;
		}
		if(PlayerInfo[playerid][pJob] == CARJACKER && !GetPVarInt(playerid, "gInRacing"))//для автомехаников
		{
			PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
		    if(gJobDuty[playerid] == 1)
		    {
		        SendClientMessage(playerid, COLOR_ORANGE, "   Вы теперь Не на Дежурстве.");
		        gJobDuty[playerid] = 0;
		        MechanicsCounter -= 1;
  				//DeletePVar(playerid, "dutylist");
  				strdel(dutylist[playerid], 0, sizeof(dutylist));
  				if(PlayerInfo[playerid][pSex] == Male) SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
		    }
		    else
		    {
		        //SendClientMessage(playerid, COLOR_ORANGE, "   Вы теперь на Дежурстве вашей АвтоРемонтной Службы и получаете вызовы от нуждающихся людей.");
		        gJobDuty[playerid] = 1;
		        MechanicsCounter += 1;
   				format(strings, sizeof(strings), "Mеханик {FFFFFF}%s[%d]", PlayerName(playerid), playerid);
   				//JobNews(COLOR_ORANGE,strings);
   				SendClientMessage(playerid, COLOR_ORANGE, strings);
				new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
				//format(strings, sizeof(strings), "{AFAFAF}[%d:%02d:%02d] {FFCC00}%s\n", lH,lM,lS, strings);
				//SetPVarString(playerid, "dutylist", strings);
				format(dutylist[playerid], sizeof(dutylist), "{AFAFAF}[%d:%02d:%02d] {FFCC00}%s\n", lH,lM,lS, strings);
  				if(PlayerInfo[playerid][pSex] == Male) SetPlayerSkinEx(playerid, 50);
		    }
		}
		//return 1;
	}*/
	/*if(CHECKING == 1)
	{
		//ИНФОРМИРОВАНИЕ
		////new strings[MAX_STRING];
		format(strings, sizeof(strings), "DutyPickUp(playerid:%d)", playerid);
		SendClientMessage(playerid, COLOR_YELLOW, strings);
	}*/
	return 1;
}



//stock OnPayCheck(playerid)
stock family_OneMinutsTimer(playerid)
{
//для экономики
//вызывается каждую минуту из OneMinutsTimer
	if(AFK_IdleTime[playerid] >= 3) return 1;
	if(gPlayerSpawned[playerid] == 0) return 1;
	//------------------------------------------------------------------
	if( IsAGangs(playerid) || IsAFamilyMember(playerid) ||
		PlayerInfo[playerid][pMember] == Hitman ||
		PlayerInfo[playerid][pMember] == DoE ||
		PlayerInfo[playerid][pMember] == 0) return 1;

	//для начисления зарплаты
	new level = PlayerInfo[playerid][pLevel];
	if(level <= 2) PlayerInfo[playerid][pPayCheck] += 3;// увеличиваем зарплату на 1
	else if(level >= 3 && level <= 4) PlayerInfo[playerid][pPayCheck] += 6;
	else if(level >= 5 && level <= 6) PlayerInfo[playerid][pPayCheck] += 9;
	else if(level >= 7 && level <= 8) PlayerInfo[playerid][pPayCheck] += 12;
	else if(level >= 9 && level <= 10) PlayerInfo[playerid][pPayCheck] += 15;
	else if(level >= 11 && level <= 12) PlayerInfo[playerid][pPayCheck] += 18;
	else if(level >= 13 && level <= 14) PlayerInfo[playerid][pPayCheck] += 21;
	else if(level >= 15 && level <= 16) PlayerInfo[playerid][pPayCheck] += 24;
	else if(level >= 17 && level <= 18) PlayerInfo[playerid][pPayCheck] += 27;
	else if(level >= 19 && level <= 20) PlayerInfo[playerid][pPayCheck] += 30;
	else if(level >= 21 && level <= 22) PlayerInfo[playerid][pPayCheck] += 33;
	else if(level >= 23) PlayerInfo[playerid][pPayCheck] += 36;

	new rank = PlayerInfo[playerid][pRank];
	if(rank == 1) PlayerInfo[playerid][pPayCheck] += 3;// увеличиваем зарплату на 1
	else if(rank == 2) PlayerInfo[playerid][pPayCheck] += 6;
	else if(rank == 3) PlayerInfo[playerid][pPayCheck] += 9;
	else if(rank == 4) PlayerInfo[playerid][pPayCheck] += 12;
	else if(rank == 5) PlayerInfo[playerid][pPayCheck] += 15;
	else if(rank == 6) PlayerInfo[playerid][pPayCheck] += 18;
	else if(rank == 7) PlayerInfo[playerid][pPayCheck] += 21;
	else if(rank == 8) PlayerInfo[playerid][pPayCheck] += 24;
	else if(rank == 9) PlayerInfo[playerid][pPayCheck] += 27;
	else if(rank == 10) PlayerInfo[playerid][pPayCheck] += 30;
	else if(rank == 11) PlayerInfo[playerid][pPayCheck] += 33;
	else if(rank == 12) PlayerInfo[playerid][pPayCheck] += 36;
	//--------------------------------------------------------------
	return 1;
}

//stock OnPayOfDuty5Timer(playerid)
stock family_OnFiveMinutsTimer(playerid)
{
	new strtmp[MAX_STRING];
	//для проверки времени игры (если вы играли больше 35 минут т.е. больше половины часа)
	/*if(PlayerInfo[playerid][pMember] == DoT && gOnDuty[playerid] == 1 && AFK_IdleTime[playerid] < 3)//каждые 5 минут начисляем деньги
	{
   		if(
		   	(IsPlayerInZone(playerid, 0)) || //LS
			(IsPlayerInZone(playerid, 3)) ||  //SF
			(IsPlayerInZone(playerid, 7)) //LV
		   )
  		{
			IncreaseRank(playerid, 1);
			FamilyInfo[DoD][fBank] -= DutyFiveMinuts*PlayerInfo[playerid][pRank];
	    	GivePlayerMoneyB(ffamily+PlayerInfo[playerid][pMember], playerid, DutyFiveMinuts*PlayerInfo[playerid][pRank]);//перечислить игроку зарплату
			format(strtmp, sizeof(strtmp), "Bам перечислено $%d за дежурство в участке !", DutyFiveMinuts*PlayerInfo[playerid][pRank]);
			SendClientMessage(playerid, COLOR_ORANGE, strtmp);
			FamilyInfo[DoT][fMaterial] += 5;
			//SaveFamiliesSQL(PlayerName(playerid));
		}
	}*/
//TestLog(OPTIM, "FiveMinutsTimer_0", GetTickCount(), timers);
	if(PlayerInfo[playerid][pMember] == DoD && AFK_IdleTime[playerid] < 3)//каждые 5 минут начисляем деньги военным
	{
		if(IsPlayerInArea(playerid, specialzone[0]) && FamilyInfo[DoD][fBank] > 0)
		{
			//SendClientMessage(playerid, COLOR_BROWNGREEN, "Заключённые:");
			new found;
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) ) continue;
				if(PlayerInfo[i][pJailed] != 10) continue;
				if(IsPlayerInArea(i, specialzone[0]))
				{
					found ++;
				}
			}
			if(!found) return 1;
			IncreaseRank(playerid, 1);
			FamilyInfo[DoD][fBank] -= found*DutyFiveMinuts*PlayerInfo[playerid][pRank];
	    	GivePlayerMoneyB(ffamily+PlayerInfo[playerid][pMember], playerid, found*DutyFiveMinuts*PlayerInfo[playerid][pRank]);//перечислить игроку зарплату
			format(strtmp, sizeof(strtmp), "Bам перечислено {33AA33}$%d{339966} за охрану зоны !", DutyFiveMinuts*PlayerInfo[playerid][pRank]);
			SendClientMessage(playerid, COLOR_EMERALD, strtmp);
			FamilyInfo[DoD][fMaterial] += 50*found;
			//SaveFamiliesSQL(PlayerName(playerid));
		}
//TestLog(OPTIM, "FiveMinutsTimer_1", GetTickCount(), timers);
	}
	else if(PlayerInfo[playerid][pMember] == DoH && AFK_IdleTime[playerid] < 3)//каждые 5 минут начисляем деньги военным
	{
		if( IsAtHospital(playerid)  && FamilyInfo[DoH][fBank] > 0 )
		{
			IncreaseRank(playerid, 1);
			FamilyInfo[DoH][fBank] -= DutyFiveMinuts*PlayerInfo[playerid][pRank];
	    	GivePlayerMoneyB(ffamily+PlayerInfo[playerid][pMember], playerid, DutyFiveMinuts*PlayerInfo[playerid][pRank]);//перечислить игроку зарплату
			format(strtmp, sizeof(strtmp), "Bам перечислено {33AA33}$%d{FF00FF} за дежурство в больнице !", DutyFiveMinuts*PlayerInfo[playerid][pRank]);
			SendClientMessage(playerid, COLOR_MAUVE, strtmp);
			//FamilyInfo[DoH][fMaterial] += 5;
			//SaveFamiliesSQL(PlayerName(playerid));
//TestLog(OPTIM, "FiveMinutsTimer_2", GetTickCount(), timers);
		}
	}
	else if(PlayerInfo[playerid][pMember] == DoJ && AFK_IdleTime[playerid] < 3)//каждые 5 минут начисляем деньги военным
	{
		//if(IsPlayerInArea(playerid, specialzone[7]))
		if(PlayerInfo[playerid][pLocal] == 241 && FamilyInfo[DoJ][fBank] > 0)
		{
			IncreaseRank(playerid, 1);
			FamilyInfo[DoJ][fBank] -= DutyFiveMinuts*PlayerInfo[playerid][pRank];
	    	GivePlayerMoneyB(ffamily+PlayerInfo[playerid][pMember], playerid, DutyFiveMinuts*PlayerInfo[playerid][pRank]);//перечислить игроку зарплату
			format(strtmp, sizeof(strtmp), "Bам перечислено {33AA33}$%d{99CC00} за приём посетителей в Мэрии !", DutyFiveMinuts*PlayerInfo[playerid][pRank]);
			SendClientMessage(playerid, COLOR_HERBAL, strtmp);
//TestLog(OPTIM, "FiveMinutsTimer_3", GetTickCount(), timers);
		}
	}
	else if(PlayerInfo[playerid][pMember] == DoE && AFK_IdleTime[playerid] < 3)//каждые 5 минут начисляем деньги военным
	{
   		if( IsPlayerInRangeOfPoint(playerid, 100.0, -2032.6810,-117.4816,1035.1719) && FamilyInfo[DoE][fBank] > 0 )
  		{
  			IncreaseRank(playerid, 1);
  			FamilyInfo[DoE][fBank] -= DutyFiveMinuts*PlayerInfo[playerid][pRank];
	    	GivePlayerMoneyB(ffamily+PlayerInfo[playerid][pMember], playerid, DutyFiveMinuts*PlayerInfo[playerid][pRank]);//перечислить игроку зарплату
			format(strtmp, sizeof(strtmp), "Bам перечислено {33AA33}$%d{FFCC99} за дежурство в АвтоШколе !", DutyFiveMinuts*PlayerInfo[playerid][pRank]);
			SendClientMessage(playerid, COLOR_LIGHTBROWN, strtmp);
			//FamilyInfo[DoE][fMaterial] += 500;
			//SaveFamiliesSQL(PlayerName(playerid));
//TestLog(OPTIM, "FiveMinutsTimer_4", GetTickCount(), timers);
		}
	}
	return 1;
}


stock family_spawnchange(playerid)
{
		if(spectateid[playerid] != MAX_PLAYERS-1)// && PlayerInfo[playerid][pAdmin] < 1
		{
			GeneralCMD(playerid); SendClientMessage(playerid, COLOR_GREY, "   Вы - Наблюдатель, не можете изменить точку Возрождения прямо сейчас !");
			return 1;
		}
		if(PlayerInfo[playerid][pMember] == 0)
		{
			GeneralCMD(playerid); SendClientMessage(playerid, COLOR_GREY, "   Изменение точки Возрождения доступно только для фракций !");
			return 1;
		}
		if(PlayerInfo[playerid][pMember] == DoT)// && gOnDuty[playerid] == 1
		{
			if(gSpawn[playerid] == 0)
			{
				gSpawn[playerid] = 1;
				SendClientMessage(playerid, COLOR_GREY, "   Вы будете теперь появляться в LSPD !");
				SetPVarInt(playerid, "SpawnChange", 1);
				return 1;
			}
			if(gSpawn[playerid] == 1)
			{
				gSpawn[playerid] = 2;
				SendClientMessage(playerid, COLOR_GREY, "   Вы теперь будете возрождаться в SFPD !");
				SetPVarInt(playerid, "SpawnChange", 1);
				return 1;
			}
			if(gSpawn[playerid] == 2)
			{
				gSpawn[playerid] = 3;
				SendClientMessage(playerid, COLOR_GREY, "   Вы теперь будете возрождаться в LVPD !");
				SetPVarInt(playerid, "SpawnChange", 1);
				return 1;
			}
			if(gSpawn[playerid] == 3)
			{
				gSpawn[playerid] = 1;
				SendClientMessage(playerid, COLOR_GREY, "   Вы будете теперь появляться в LSPD !");
				SetPVarInt(playerid, "SpawnChange", 1);
				return 1;
			}
		}
		else if(PlayerInfo[playerid][pMember] == FBI)// && gOnDuty[playerid] == 1
		{
			if(gSpawn[playerid] == 0)
			{
				gSpawn[playerid] = 1;
				SendClientMessage(playerid, COLOR_GREY, "   Вы будете теперь появляться в SFPD !");
				SetPVarInt(playerid, "SpawnChange", 1);
				return 1;
			}
			if(gSpawn[playerid] == 1)
			{
				gSpawn[playerid] = 2;
				SendClientMessage(playerid, COLOR_GREY, "   Вы теперь будете возрождаться в LVPD !");
				SetPVarInt(playerid, "SpawnChange", 1);
				return 1;
			}
			if(gSpawn[playerid] == 2)
			{
				gSpawn[playerid] = 3;
				SendClientMessage(playerid, COLOR_GREY, "   Вы будете теперь появляться в LSPD !");
				SetPVarInt(playerid, "SpawnChange", 1);
				return 1;
			}
			if(gSpawn[playerid] == 3)
			{
				gSpawn[playerid] = 1;
				SendClientMessage(playerid, COLOR_GREY, "   Вы теперь будете возрождаться в SFPD !");
				SetPVarInt(playerid, "SpawnChange", 1);
				return 1;
			}
		}
		else if(PlayerInfo[playerid][pMember] == DoD)
		{
			if(gSpawn[playerid] == 0)
			{
				gSpawn[playerid] = 1;
				SendClientMessage(playerid, COLOR_GREY, "   Вы теперь будете возрождаться на Военной Базе !");
				SetPVarInt(playerid, "SpawnChange", 1);
				return 1;
			}
			if(gSpawn[playerid] == 0)
			{
				gSpawn[playerid] = 1;
				SendClientMessage(playerid, COLOR_GREY, "   Вы будете теперь появляться на АвиаБазе !");
				SetPVarInt(playerid, "SpawnChange", 1);
				return 1;
			}
			if(gSpawn[playerid] == 1)
			{
				gSpawn[playerid] = 2;
				SendClientMessage(playerid, COLOR_GREY, "   Вы будете теперь появляться на Авианосце в SF !");
				SetPVarInt(playerid, "SpawnChange", 1);
				return 1;
			}
			if(gSpawn[playerid] == 2)
			{
				gSpawn[playerid] = 3;
				SendClientMessage(playerid, COLOR_GREY, "   Вы теперь будете возрождаться на Военной Базе !");
				SetPVarInt(playerid, "SpawnChange", 1);
				return 1;
			}
			if(gSpawn[playerid] == 2)
			{
				gSpawn[playerid] = 1;
				SendClientMessage(playerid, COLOR_GREY, "   Вы будете теперь появляться на АвиаБазе !");
				SetPVarInt(playerid, "SpawnChange", 1);
				return 1;
			}
		}
		else if(PlayerInfo[playerid][pMember] == DoH)
		{
			if(gSpawn[playerid] == 0)
			{
				gSpawn[playerid] = 1;
				SendClientMessage(playerid, COLOR_GREY, "   Вы теперь будете возрождаться в Центральной Больнице ЛС !");
				SetPVarInt(playerid, "SpawnChange", 1);
				return 1;
			}
			if(gSpawn[playerid] == 1)
			{
				gSpawn[playerid] = 2;
				SendClientMessage(playerid, COLOR_GREY, "   Вы теперь будете возрождаться в Больнице ЛС !");
				SetPVarInt(playerid, "SpawnChange", 1);
				return 1;
			}
			if(gSpawn[playerid] == 2)
			{
				gSpawn[playerid] = 3;
				SendClientMessage(playerid, COLOR_GREY, "   Вы теперь будете возрождаться в Больнице СФ !");
				SetPVarInt(playerid, "SpawnChange", 1);
				return 1;
			}
			if(gSpawn[playerid] == 3)
			{
				gSpawn[playerid] = 4;
				SendClientMessage(playerid, COLOR_GREY, "   Вы теперь будете возрождаться в Больнице ЛВ !");
				SetPVarInt(playerid, "SpawnChange", 1);
				return 1;
			}
			if(gSpawn[playerid] == 4)
			{
				gSpawn[playerid] = 1;
				SendClientMessage(playerid, COLOR_GREY, "   Вы теперь будете возрождаться в Центральной Больнице ЛС !");
				SetPVarInt(playerid, "SpawnChange", 1);
				return 1;
			}
		}
		else if(PlayerInfo[playerid][pMember] == DoE)
		{
			if(gSpawn[playerid] == 0)
			{
				gSpawn[playerid] = 1;
				SendClientMessage(playerid, COLOR_GREY, "   Вы теперь будете возрождаться в Автошколе !");
				SetPVarInt(playerid, "SpawnChange", 1);
				return 1;
			}
			if(gSpawn[playerid] == 1)
			{
				gSpawn[playerid] = 2;
				SendClientMessage(playerid, COLOR_GREY, "   Вы теперь будете возрождаться в Заброшенном Аэро !");
				SetPVarInt(playerid, "SpawnChange", 1);
				return 1;
			}
			if(gSpawn[playerid] == 2)
			{
				gSpawn[playerid] = 1;
				SendClientMessage(playerid, COLOR_GREY, "   Вы теперь будете возрождаться в Автошколе !");
				SetPVarInt(playerid, "SpawnChange", 1);
				return 1;
			}
		}
        //else SendClientMessage(playerid, COLOR_GREY, "   Вы не на дежурстве !");
		return 1;
}



stock family_command(playerid)//FamilyHelp(playerid)
{
	new bigmsgitem[1673];//определяется опытным путём по ошибкам в чате
	if(PlayerInfo[playerid][pMember] == DoT)	{	//если ДПС
		strins(bigmsgitem, "\n\t*** RPSA *** Дорожная Полиция Штата Сан-Андреас \n/pdd - повесить на игрока нарушение согласно ПДД", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/wanted - список разыскиваемых игроков штата Сан-Андреас \n/frisk - обыскать игрока", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/gate - открыть ворота Участка", strlen(bigmsgitem));
		strins(bigmsgitem, "\n(/rb)roadblock - установить дорожный блок \n(/drb)/destroyrb - удалить дорожный блок \n"#VEHICLE_TURRETUP" - бросить шипы \n"#VEHICLE_TURRETDOWN" - убрать шипы \n(/dst)/destroystrip 0 - убрать все шипы", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/tazer - достать шокер \n/forcecuff - запихнуть в машину \n/cuff - одеть наручники \n/uncuff - снять наручники \n/gps - в поисковом вертолёте", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/find - найти игрока \n/findcar - найти машину \n/ticket - выписать штраф игроку с указанием причины \n/arrest - арестовать игрока с указанием времени ареста \n/follow - конвой", strlen(bigmsgitem));
		strins(bigmsgitem, "\n(/gov)ernment - правительственное сообщение \n(/d)epartments - канал депортамента \n(/r)adio - рация \n(/m)egaphone - мегафон в полицейском автомобиле", strlen(bigmsgitem));
	}
	else if(PlayerInfo[playerid][pMember] == FBI)	{
		strins(bigmsgitem, "\n\t*** FBI *** Федеральное Бюро Расследований \n/find - найти игрока\n/pun - повесить на игрока нарушение согласно УК СА", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/wanted - список разыскиваемых игроков штата Сан-Андреас", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/gate - открыть ворота Участка", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/tazer - достать шокер \n/forcecuff - запихнуть в машину \n/cuff - одеть наручники \n/uncuff - снять наручники", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/frisk - обыскать игрока \n/take - отобрать оружие или наркотические вещества", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/ticket - выписать штраф игроку с указанием причины\n/arrest - арестовать игрока с указанием времени ареста", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/ram - взломать дверь \n"#VEHICLE_TURRETUP" - бросить шипы \n"#VEHICLE_TURRETDOWN" - убрать шипы \n(/dst)/destroystrip 0 - убрать все шипы \n/follow - конвой", strlen(bigmsgitem));
		if(!IsEvenNumber(PlayerInfo[playerid][pRank])) {
			strins(bigmsgitem, "\n/order - выписать ордер/разрешение на арест/снятия розыска/освобождение заключенного", strlen(bigmsgitem));
			strins(bigmsgitem, "\n/bigears - вкл/выкл прослушивание", strlen(bigmsgitem));// \n/showtag - скрыть ник
		}
		if(PlayerInfo[playerid][pRank] == 12)
		{
			strins(bigmsgitem, "\n/order - выписать ордер/разрешение на арест/снятия розыска/освобождение заключенного \n/jail - пересадить в другую камеру/уменьшить срок", strlen(bigmsgitem));
		}
		strins(bigmsgitem, "\n(/gov)ernment - правительственное сообщение \n(/d)epartments - канал депортамента \n(/r)adio - рация \n(/m)egaphone - мегафон в полицейском автомобиле", strlen(bigmsgitem));
	}
	else if(PlayerInfo[playerid][pMember] == DoD)	{	//если военный
		strins(bigmsgitem, "\n\t*** NG *** Национальная Гвардия \n/find - найти игрока\n/gate - открыть с пульта ворота \n/camera - камера наблюдения с пульта и кабинета Генерала", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/deliver - перевести на зону арестованного из КПЗ \n/jailstats - статистика зоны \n/follow - конвой", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/tazer - достать электрошокер \n/forcecuff - запихнуть в машину \n/cuff - одеть наручники \n/uncuff - снять наручники", strlen(bigmsgitem));
		strins(bigmsgitem, "\n(/gov)ernment - правительственное сообщение \n(/d)epartments - канал депортамента \n(/r)adio - рация \n(/m)egaphone - мегафон в автомобиле", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/pun - повесить на игрока нарушение согласно УК СА (статьи 413,438,445)", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/order - выдать разрешение на освобождение заключённого(адвокату) \n/spawnchange - изменить место появления после смерти.", strlen(bigmsgitem));
    	strins(bigmsgitem, "\n\t*** Rank >7 *** \n/repair - починить \n/refill - заправить \n/open - открыть/закрыть барак", strlen(bigmsgitem));
	}
	else if(PlayerInfo[playerid][pMember] == DoH)	{   //если в спасателях
		strins(bigmsgitem, "\n\t*** MoH *** Министерство Здравохранения \n/heal - полечить игрока/выдать медицинское освидетельствование \n/open - открыть/закрыть больницу", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/healstats - просмотерть уровень Эпидемии \n/tazer - достать шокер \n/gps - в поисковом вертолёте", strlen(bigmsgitem));
		strins(bigmsgitem, "\n(/gov)ernment - правительственное сообщение \n(/d)epartments - канал депортамента \n(/r)adio - рация \n(/m)egaphone - мегафон в автомобиле", strlen(bigmsgitem));
	}
	else if(IsAFamilyMember(playerid)) {
		strins(bigmsgitem, "\n\t*** FAMILY *** Семья \n(/f)amily - семейный чат \n/open - открыть/закрыть особняк \n/tie - связать игрока \n/untie - развязать игрока", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/familymoney - общаг семьи", strlen(bigmsgitem));
	}

    else if(PlayerInfo[playerid][pMember] == DoJ)
	{
		strins(bigmsgitem, "\n\t*** МЭРИЯ *** Правительство \n(/d)epartments - канал депортамента \n/open - открыть/закрыть Мэрию", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/find - найти игрока\n/tazer - достать шокер  \n/finance - проверить финансы", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/wanted - список разыскиваемых \n/jailstats - статистика заключенных \n/healstats - уровень Эпидемии \n/roadstatus - статус мостов", strlen(bigmsgitem));
		strins(bigmsgitem, "\nМигалка на авто - 'H' (Model: 421,551,547,579)", strlen(bigmsgitem));

		if(PlayerInfo[playerid][pRank] == 1) {//Охранник
	    	strins(bigmsgitem, "\n/follow - конвой\n/frisk - обыскать игрока \n/guard - предложить охрану", strlen(bigmsgitem));
			strins(bigmsgitem, "\n/cuff - одеть наручники \n/uncuff - снять наручники", strlen(bigmsgitem));
		}
		if(PlayerInfo[playerid][pRank] == 2) {//Соц.Работник
			strins(bigmsgitem, "\n/order "#SOC_PACKET" - выдача талона на соц.пакет", strlen(bigmsgitem));
		}
		else if(PlayerInfo[playerid][pRank] == 3) {//Юрисконсульт - Адвокат
	    	//strins(bigmsgitem, "\n/bigears - вкл/выкл прослушивание", strlen(bigmsgitem));
	    	strins(bigmsgitem, "\n/jobs - оценить занятость населения (закрыть трудоустройство)", strlen(bigmsgitem));
	    	strins(bigmsgitem, "\n/jobquit - уволить с работы", strlen(bigmsgitem));
			strins(bigmsgitem, "\n/order "#QUIT_JOB" - выдача разрешения на увольнение с работы", strlen(bigmsgitem));
		}
		else if(PlayerInfo[playerid][pRank] == 4) {//Прокурор
			strins(bigmsgitem, "\n(/gov)ernment - правительственное сообщение", strlen(bigmsgitem));
			strins(bigmsgitem, "\n/order - выписать ордер на арест/снятия розыска/освобождение заключенного", strlen(bigmsgitem));
		}
		else if(PlayerInfo[playerid][pRank] == 5) {//Ген.Инспектор - Полиция
			strins(bigmsgitem, "\n/follow - конвой \n/bigears - вкл/выкл прослушивание", strlen(bigmsgitem));//\n/showtag - скрыть ник
			strins(bigmsgitem, "\n/cuff - одеть наручники \n/uncuff - снять наручники", strlen(bigmsgitem));
			strins(bigmsgitem, "\n/frisk - обыскать игрока \n/arrest - арестовать игрока с указанием времени ареста", strlen(bigmsgitem));
			strins(bigmsgitem, "\n/jail - пересадить в другую камеру/уменьшить срок", strlen(bigmsgitem));
		}
		else if(PlayerInfo[playerid][pRank] == 6) {//Маршал - НГ
			strins(bigmsgitem, "\n/follow - конвой \n/frisk - обыскать игрока", strlen(bigmsgitem));//\n/showtag - скрыть ник
			strins(bigmsgitem, "\n/cuff - одеть наручники \n/uncuff - снять наручники", strlen(bigmsgitem));
			strins(bigmsgitem, "\n/deliver - перевести на зону арестованного из КПЗ\n/tazer - достать шокер", strlen(bigmsgitem));
		}
		else if(PlayerInfo[playerid][pRank] == 7) {//Первый зам. - DoT+FBI+DoH
			strins(bigmsgitem, "\n/criminal - оценить уровень криминала", strlen(bigmsgitem));//\n/setcrim - изменить кол-во преступлений
			strins(bigmsgitem, "\n/pdd - повесить на игрока нарушение согласно ПДД", strlen(bigmsgitem));
			strins(bigmsgitem, "\n/pun - повесить на игрока нарушение согласно УК СА", strlen(bigmsgitem));
		}
		else if(PlayerInfo[playerid][pRank] == 8) {//Ген.Прокурор
			strins(bigmsgitem, "\n/clearwanted - снять преступление", strlen(bigmsgitem));
			strins(bigmsgitem, "\n/ticket - выписать штраф игроку с указанием причины", strlen(bigmsgitem));
			strins(bigmsgitem, "\n/jail - пересадить в другую камеру/уменьшить срок", strlen(bigmsgitem));
			strins(bigmsgitem, "\n/bigears - вкл/выкл прослушивание", strlen(bigmsgitem));
		}
		else if(PlayerInfo[playerid][pRank] == 9) {//Солиситор
			strins(bigmsgitem, "\n/permit - выдать разрешение на покупку недвижимости", strlen(bigmsgitem));
		}
		else if(PlayerInfo[playerid][pRank] == 10) {//Сенатор
			strins(bigmsgitem, "\n/checkprop - вкл/выкл аукцион", strlen(bigmsgitem));
			strins(bigmsgitem, "\n/asellhouse - продать дом \n/asellbiz - продать бизнес \n/asellsbiz - продать компанию \n/checkprop - вкл/выкл аукцион", strlen(bigmsgitem));
		}
		else if(PlayerInfo[playerid][pRank] == 11) {//Министр Финансов
			strins(bigmsgitem, "\n/settaxi - установить цену такси\n/settax - установить налог\n/givetax - выписать премию\n/taketax - вернуть деньги в казну", strlen(bigmsgitem));
	    	strins(bigmsgitem, "\n/bigmoney - оценить благосостояние\n/fuelcost - установить коэфициент на покупку топлива", strlen(bigmsgitem));
		}
		if(PlayerInfo[playerid][pLeader] == DoJ) {//Губернатор Штата
			strins(bigmsgitem, "\n/makeleader - назначить лидера одного из департаментов\n/permit - выдать разрешение на покупку недвижимости", strlen(bigmsgitem));// \n/showtag - скрыть ник
		}
	}
    else if(PlayerInfo[playerid][pMember] == Hitman) {
    	strins(bigmsgitem, "\n\t*** КИЛЛЕР *** Агентство Наёмных убийц \n/find - найти игрока\n/portable - портативный компьютерв", strlen(bigmsgitem));
    	strins(bigmsgitem, "\n/tie - свзязать игрока \n/untie - развязать игрока \n(/f)amily - семейный чат \n/showtag - скрыть ник", strlen(bigmsgitem));
    	strins(bigmsgitem, "\n'F' - открыть дверь особняка", strlen(bigmsgitem));
	}
    else if(PlayerInfo[playerid][pMember] == SAN) {
    	strins(bigmsgitem, "\n\t*** РЕПОРТЁР *** Агентство новостей \n/news - разместить новости \n/live - начать прямой эфир \n/tvcam - начать ТВ-трансляцию", strlen(bigmsgitem));
    	strins(bigmsgitem, "\n/paper write - написать газету \n/paper delete - удалить газету ", strlen(bigmsgitem));
    	strins(bigmsgitem, "\n/papers - просмотреть список написанных газет \n/read testpaper - просмотреть написанную газету", strlen(bigmsgitem));
    	strins(bigmsgitem, "\n/startlotto - запустить лото  \n/noooc - отключить общий чат", strlen(bigmsgitem));// \n/transfer - перечислить деньги из студии
    	strins(bigmsgitem, "\n(/f)amily - семейный чат \n/tazer - достать шокер  \n/megaphone - мегафон в авто", strlen(bigmsgitem));
    	strins(bigmsgitem, "\n/quest - создать опрос в игре \n/vote - создать голосование с выводом в статистику", strlen(bigmsgitem));
    	strins(bigmsgitem, "\n/startlinе - запустить бегущую строку \n/stopline - остановить бегущую строку", strlen(bigmsgitem));
    	strins(bigmsgitem, "\n/victorina - запустить/остановить Викторину \n/transfer - перевести деньги", strlen(bigmsgitem));
    	strins(bigmsgitem, "\n/addposter - добавить BigBoard \n/editposter - редактировать \n/poster - указатель", strlen(bigmsgitem));
	}
    else if(PlayerInfo[playerid][pMember] == DoE){
    	strins(bigmsgitem, "\n\t*** ИНСТРУКТОР *** Министерство Образования \n/give - выдать лицензию \n/open - открыть/закрыть автошколу", strlen(bigmsgitem));
    	strins(bigmsgitem, "\n/startlesson - начать урок \n/stoplesson - остановить урок \n/seelesson - посмотреть список сдающих", strlen(bigmsgitem));
    	strins(bigmsgitem, "\n(/d)epartments - канал депортамента \n(/r)adio - рация \n/gov - правительственное сообщение \n/tazer - достать шокер", strlen(bigmsgitem));
	}
	//--------------------------------------------------------------------------
	else if( IsAGangs(playerid) ) {
		strins(bigmsgitem, "\n\t*** GANGS *** Банда \n/gangs - статистика по бандам \n(/f)amily - семейный чат \n/tie - связать \n/untie - развязать игрока \n/spawn - установить спаун", strlen(bigmsgitem));
		if(PlayerInfo[playerid][pRank] >= 11) {
			strins(bigmsgitem, "\n/leaderhelp - основные команды \n/washmoney - отмыть деньги", strlen(bigmsgitem));
		}
	}
	//--------------------------------------------------------------------------
	if(PlayerInfo[playerid][pAdmin] >= 1)	{   //если в админах
		strins(bigmsgitem, "\n\t*** ADMIN *** \n(/a)dmin chat - админский чат \n(/ah)elp - админский help \n/togsys - переключатель системной панели \n/paycheck - уровень ЗП для лвл", strlen(bigmsgitem));///icq - послать сообщение Danger
		strins(bigmsgitem, "\nAlt + NUM6 - поднять чат \nAlt + NUM4 - опустить чат", strlen(bigmsgitem));///icq - послать сообщение Danger

	}
	if(strlen(bigmsgitem) > sizeof(bigmsgitem))
	{
		//ИНФОРМИРОВАНИЕ
		new strtmp[MAX_STRING];
		format(strtmp, sizeof(strtmp), "Error: FAMILY HELP - %s[%d], strlen(bigmsgitem): %d, sizeof(bigmsgitem): %d", PlayerName(playerid), playerid, strlen(bigmsgitem), sizeof(bigmsgitem));
		Log(ERROR, strtmp);
		return 1;
	}
	if(strlen(bigmsgitem) <= 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   FamilyHelp пуст");
		command_help(playerid);//HELP(playerid);
		return 1;
	}
	ShowPlayerDialogEx(playerid, BACKCMD_DIALOG, DIALOG_STYLE_MSGBOX, "FAMILY HELP - наберите команду для информации", bigmsgitem, "OK", "Назад");
	return 1;
}



//##############################################################################//
//                                                                              //
//                               ПРИВАТНЫЕ ФУНКЦИИ                              //
//                                                                              //
//##############################################################################//




stock MakeLeader(adminid, forplayerid, playername[], member)//MAX_PLAYERS-1 - "CEPBEP"
{   //playerid - кем назначен
	//forplayerid - Ид нового лидера
	//member - номер фракции // 0 - при снятии лидера без увольнения
	//if(!IsPlayerConnected(forplayerid)) return 1;

	//new forplayerid = ReturnUser(playername);
	//if(!IsPlayerConnectedEx(forplayerid)) forplayerid = MAX_PLAYERS-2;
	if(IsPlayerNPC(forplayerid)) return 1;
	//if(!gPlayerLogged[forplayerid]) return 1;
	//if(!gPlayerSpawned[forplayerid]) return 1;

	new adminname[MAX_PLAYER_NAME];//имя админа
	if(adminid == MAX_PLAYERS-1 || adminid == MAX_PLAYERS-2)
	{//CityHall
		strmid(adminname, "CEPBEP", 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);
		//if(!IsPlayerInRangeOfPoint(forplayerid, 5.0, 358.2361,166.1549,1008.3828)) return 1;
	}
	else
	{
		//strmid(playername, PlayerName(playerid), 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);
		GetPlayerName(adminid, adminname, MAX_PLAYER_NAME);

	}
	//--------------------------------------------------------------------------
//Выводим из старой фракции
	//new strings[MAX_STRING];
	//в любом случаии снимаем лидерку
	new family = PlayerInfo[forplayerid][pMember];
	if(!strcmp(FamilyInfo[family][fLeader], playername, true) )// && strcmp(adminname, playername, true)
	{   //если вы были лидером какой то организации и вы не сами себя назначили лидером, то освободить там место
#if defined vw_sql//#endif
		ClearFamily(family); //strmid(FamilyInfo[family][fLeader], "No-One", 0, strlen("No-One"), MAX_PLAYER_NAME);
#endif
	}
	//if(IsPlayerConnectedEx(forplayerid))
	//{
	if(member == 0)
	{//снимаем с поста лидера без увольнения
		PlayerInfo[forplayerid][pLeader] = 0;//назначаем игрока лидером данной группы 0-11
		//для снятие лидера без увольнения из фракции
		format(strings, sizeof(strings), "%s лишил Вас Лидерки фракции %s. Ранг остался прежним.", adminname, GetFamilyName(family));
		SendClientMessageEx(forplayerid, COLOR_RED, strings);
		format(strings, sizeof(strings), "Bы лишили Лидерки %s'а из фракции %s.", playername, GetFamilyName(family));
		SendClientMessageEx(adminid, COLOR_RED, strings);
		format(strings, sizeof(strings), "AdmCmd: %s has unleader %s's from Faction %s.", adminname, playername, GetFamilyName(family));
		Log(INVITE,strings);
		return 1;
	}
	//}
//если лидерка берётся на маркере, кроме губера
	if(	member != DoJ && adminid == MAX_PLAYERS-1 &&
		PlayerInfo[forplayerid][pMember] == 0 &&//и вы на данный момент ни где не состоите, т.е. недавно покинули фракцию
		PlayerInfo[forplayerid][pProfSkill] != 0 && getdate() < PlayerInfo[forplayerid][pProfSkill]
		//если профскил не равне нулю и больше текущей даты, т.е. время выжидания вышло
		//&& PlayerInfo[forplayerid][pAdmin] < 5 && PlayerInfo[adminid][pLeader] != DoJ
	  )
	{//getdate() >= PlayerInfo[giveplayerid][pProfSkill] - может вступить
		format(strings, sizeof(strings), "   Вы не можете быть назначены лидером до %s[%d]!",
			getDate(PlayerInfo[forplayerid][pProfSkill]), PlayerInfo[forplayerid][pProfSkill]);
		SendClientMessageEx(forplayerid, COLOR_GREY, strings);
		format(strings, sizeof(strings), "   Вы не можете назначить лидером %s'а до %s[%d]!",
			playername, getDate(PlayerInfo[forplayerid][pProfSkill]), PlayerInfo[forplayerid][pProfSkill]);
		SendClientMessageEx(adminid, COLOR_RED, strings);
		return 1;
	}
///иначе если губернатор даёт, то пропустить проверку на время

	//если игрок покинул фракцию
	if(PlayerInfo[forplayerid][pMember] >= DoT) FamilyInfo[family][fMembers] --;
	//--------------------------------------------------------------------------
//ВВодим в новую фракция
	PlayerInfo[forplayerid][pLeader] = member;//назначаем игрока лидером данной группы 0-11
	PlayerInfo[forplayerid][pMember] = member;//назначаем игрока членом данной группы 0-11
	PlayerInfo[forplayerid][pRank] = 12;//назначаем игроку максимальный ранг

	if(member == TEAM_GROVE) { PlayerInfo[forplayerid][pChar] = 105; /*PlayerInfo[forplayerid][pTeam] = 2;*/ }
	else if(member == TEAM_BALLAS) { PlayerInfo[forplayerid][pChar] = 102; /*PlayerInfo[forplayerid][pTeam] = 2;*/ }
	else if(member == TEAM_AZTEC) { PlayerInfo[forplayerid][pChar] = 114; /*PlayerInfo[forplayerid][pTeam] = 2;*/ }
	else if(member == TEAM_VAGOS) { PlayerInfo[forplayerid][pChar] = 108; /*PlayerInfo[forplayerid][pTeam] = 2;*/ }
	else if(member == TEAM_NANG) { PlayerInfo[forplayerid][pChar] = 121; /*PlayerInfo[forplayerid][pTeam] = 2;*/ }
	else if(member == TEAM_RIFA) { PlayerInfo[forplayerid][pChar] = 173; /*PlayerInfo[forplayerid][pTeam] = 2;*/  }
	else if(member == TEAM_TRIAD) { PlayerInfo[forplayerid][pChar] = 117; /*PlayerInfo[forplayerid][pTeam] = 2;*/ }
	else if(member == TEAM_BIKER) { PlayerInfo[forplayerid][pChar] = 247; /*PlayerInfo[forplayerid][pTeam] = 2;*/ }
	else if(member == TEAM_MAFIA) { PlayerInfo[forplayerid][pChar] = 111; /*PlayerInfo[forplayerid][pTeam] = 2;*/ }

	else if(member == DoT) { PlayerInfo[forplayerid][pChar] = 288; /*PlayerInfo[forplayerid][pTeam] = 1;*/ } //Police Force
	else if(member == FBI) { PlayerInfo[forplayerid][pChar] = 165; /*PlayerInfo[forplayerid][pTeam] = 1;*/ } //FBI/ATF
	else if(member == DoD) { PlayerInfo[forplayerid][pChar] = 287; /*PlayerInfo[forplayerid][pTeam] = 1;*/ } //National Guard
	else if(member == DoH) { PlayerInfo[forplayerid][pChar] = 70; /*PlayerInfo[forplayerid][pTeam] = 1;*/ } //Fire/Ambulance
	else if(member == LCN) { PlayerInfo[forplayerid][pChar] = 98; /*PlayerInfo[forplayerid][pTeam] = 2;*/ } //La Cosa Nostra
	else if(member == Yakuza) { PlayerInfo[forplayerid][pChar] = 49; /*PlayerInfo[forplayerid][pTeam] = 2;*/  } //Yakuza
	else if(member == DoJ) { PlayerInfo[forplayerid][pChar] = 147; /*PlayerInfo[forplayerid][pTeam] = 1;*/ } //Mayor
	else if(member == Hitman) { PlayerInfo[forplayerid][pChar] = 68; /*PlayerInfo[forplayerid][pTeam] = 2;*/ } //Hitmans
	else if(member == SAN) { PlayerInfo[forplayerid][pChar] = 227; /*PlayerInfo[forplayerid][pTeam] = 3;*/ } //News Reporters
	else if(member == DoE) { PlayerInfo[forplayerid][pChar] = 60; /*PlayerInfo[forplayerid][pTeam] = 3;*/ } //Driving/Flying School

	FamilyInfo[member][fMembers] ++;
	//if(IsPlayerConnectedEx(forplayerid))
	//{
#if defined vw_sql//#endif
	//InviteList(playerid, PlayerName(forplayerid), member, PlayerInfo[forplayerid][pRank], 1);
	InviteList(adminid, playername, member, PlayerInfo[forplayerid][pRank], 1);
#endif
	if(!strcmp(FamilyInfo[member][fLeader], "No-One", true))
	{	//если эта организация не имеет лидера, поле должно быть пустым после увольнения предыдущего лидера
		strmid(FamilyInfo[member][fLeader], playername, 0, strlen(playername), MAX_PLAYER_NAME);
	}
	SetPlayerSkinEx(forplayerid, PlayerInfo[forplayerid][pChar]);
	//OnPlayerStatsUpdate(forplayerid);//запустить ф-ию сохранения параметров игрока

	if(PlayerInfo[forplayerid][pAdmin] < 7 && family != member) PlayerInfo[forplayerid][pProfSkill] = 0;
	format(strings, sizeof(strings), "   Bы были назначены %s'ом в Фракцию %s", adminname, GetFamilyName(member));
	SendClientMessageEx(forplayerid, COLOR_RED, strings);
	format(strings, sizeof(strings), "   Bы передали управление %s'у Фракцией %s.", playername, GetFamilyName(member));
	SendClientMessageEx(adminid, COLOR_RED, strings);

	//format(strings, sizeof(strings), "AdmCmd: %s has given %s's control to Faction %d.", playername, PlayerName(forplayerid), member);
	//Log(INVITE,strings);
	//}
	//else OnPlayerSaveParameters(forplayerid, playername);
#if defined vw_sql//#endif
	SaveFamiliesSQL(adminname);
#endif
	//--------------------------------------------------------------------------
	return 1;
}
stock UninvitePlayerid(playerid, forplayerid, giveplayername[])//для увольнения
{
    if(PlayerInfo[forplayerid][pMember] == 0)
    {
    	//SendClientMessage(forplayerid, COLOR_GREY, "   Этот игрок не является членом организации !");
		return 1;
	}

	new family = PlayerInfo[forplayerid][pMember];
	FamilyInfo[family][fMembers] --;

	if(PlayerInfo[forplayerid][pAdmin] <= 5) PlayerInfo[forplayerid][pProfSkill] = getdate()+1;//во всех случаях ставим 1 день задержки

	if(PlayerInfo[forplayerid][pLeader] >= TEAM_GROVE)
	{
		if(!strcmp(FamilyInfo[family][fLeader], giveplayername, true))
		{   //если имя игрока совпало с именем лидера
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "%s {FFFFFF}%s[%d]: {FFFF00}покинул фракцию %s.",
				GetPlayerRanks(forplayerid), giveplayername, forplayerid, GetPlayerMembers(forplayerid));
			//OOCNews(COLOR_HERBAL, "|_____________________________________ Правительственное сообщение _____________________________________|");
			SendClientMessageToAll(COLOR_HERBAL, "|_____________________________________ Правительственное сообщение _____________________________________|");
			//OOCNews(COLOR_LIGHTBLUE, strings);
			SendClientMessageToAll(COLOR_LIGHTBLUE, strings);
#if defined vw_sql//#endif
			ClearFamily(family);
#endif
		}
		if(PlayerInfo[forplayerid][pAdmin] < 2 && playerid != MAX_PLAYERS-1) PlayerInfo[forplayerid][pProfSkill] = getdate()+5;
//только когда кто то (не СЕРВЕР) увольняет выдать ожидание 5 дней
		PlayerInfo[forplayerid][pLeader] = 0;
	}
#if defined vw_sql//#endif
	SaveFamiliesSQL(giveplayername);
#endif
	if(PlayerInfo[forplayerid][pMember] >= DoT && PlayerInfo[forplayerid][pMember] <= DoD)
	{
		if(PlayerInfo[forplayerid][pGunLic] == 1) { PlayerInfo[forplayerid][pGunLic] = 0; SetPlayerToTeamColor(13); }
	}
    else if(PlayerInfo[forplayerid][pMember] == DoE && PlayerInfo[forplayerid][pAdmin] < 6)
    {
		if(PlayerInfo[forplayerid][pCarLic] == 1) PlayerInfo[forplayerid][pCarLic] = 1+10;
		if(PlayerInfo[forplayerid][pBikeLic] == 1) PlayerInfo[forplayerid][pBikeLic] = 1+10;
		if(PlayerInfo[forplayerid][pFlyLic] == 1) PlayerInfo[forplayerid][pFlyLic] = 1+10;
		if(PlayerInfo[forplayerid][pBoatLic] == 1) PlayerInfo[forplayerid][pBoatLic] = 1+10;
		if(PlayerInfo[forplayerid][pFishLic] == 1) PlayerInfo[forplayerid][pFishLic] = 1+10;
		if(PlayerInfo[forplayerid][pGunLic] == 1) { PlayerInfo[forplayerid][pGunLic] = 1+10; SetPlayerToTeamColor(14); }
    }
#if defined vw_sql//#endif
	InviteList(playerid, giveplayername, PlayerInfo[forplayerid][pMember], PlayerInfo[forplayerid][pRank], 0);
#endif
	PlayerInfo[forplayerid][pCarTime] = 0;
	QuitJob(forplayerid);

	PlayerInfo[forplayerid][pMats] = 0;//обнуляем кол-во материалов при смене работы
	/*PlayerInfo[forplayerid][pTeam] = 3;*/
	PlayerInfo[forplayerid][pMember] = 0;
	PlayerInfo[forplayerid][pRank] = 0;
	PlayerInfo[forplayerid][pChar] = SKIN_DEFAULT;
	//записываем дату когда человек может вступить во фракцию
	//для проверка на возможность сегодня вступления в новую фракцию

    if(IsPlayerConnected(forplayerid))
    {
    	ResetPlayerWeaponsEx(forplayerid);//забрать оружие
		//gMedicBill[forplayerid] = 0;

		if(gOnDuty[forplayerid] == 1)
		{
	        if(PlayerInfo[forplayerid][pMember] == DoD)
	        {
	   			MilitaryCounter --;
	        }
	        else if(PlayerInfo[forplayerid][pMember] == DoH)
	        {
	   			MedicCounter --;
	        }
	        gOnDuty[forplayerid] = 0;
	        //DeletePVar(forplayerid, "dutylist");
	        strdel(dutylist[forplayerid], 0, sizeof(dutylist));
		}
		SetSpawnInfoEx(forplayerid,
			PlayerInfo[forplayerid][pTeam],
			PlayerInfo[forplayerid][pModel],
			CurPos[0][forplayerid],
			CurPos[1][forplayerid],
			CurPos[2][forplayerid],
			0.0, -1, -1, -1, -1, -1, -1);
		SpawnPlayer(forplayerid);//переразмещает игрока в стартовой позиции,
	}
	return 1;
}



stock GetFamilyName(family)
{
	new ltext[36];
//#define TEAM_NONE 	0
    if(family == TEAM_GROVE) { ltext = "Grove Street"; }//"Police"
	else if(family == TEAM_BALLAS) { ltext = "The Ballas"; }//"FBI"
	else if(family == TEAM_AZTEC) { ltext = "Varios Los Aztecas"; }//"National Guard"
	else if(family == TEAM_VAGOS) { ltext = "Los Santos Vagos"; }//"Ambulance" Medical Center
	else if(family == TEAM_NANG) { ltext = "Da Nang Boys"; }
	else if(family == TEAM_RIFA) { ltext = "San Fierro Rifa"; }
	else if(family == TEAM_TRIAD) { ltext = "The Traids"; }//"Mayor"Правительство
	else if(family == TEAM_BIKER) { ltext = "Bikers"; }//"Hitmen Agency"
	else if(family == TEAM_MAFIA) { ltext = "The Russian Mafia"; }//"CNN Studio"

    else if(family == DoT) { ltext = "[DoT] Министерство Транспорта"; }//"Police"
	else if(family == FBI) { ltext = "[FBI] Федеральное Бюро Раследований"; }//"FBI"
	else if(family == DoD) { ltext = "[DoD] Министерство Обороны"; }//"National Guard"
	else if(family == DoH) { ltext = "[DoH] Министерство Здравохранения"; }//"Ambulance" Medical Center
	else if(family == LCN) { ltext = "[LCN] La Cosa Nostra"; }
	else if(family == Yakuza) { ltext = "[Yakuza] Yakuza"; }
	else if(family == DoJ) { ltext = "[DoJ] Министерство Юстиции"; }//"Mayor"Правительство
	else if(family == Hitman) { ltext = "[Hitman] Заказное Агенство"; }//"Hitmen Agency"
	else if(family == SAN) { ltext = "[SAN] Служба Новостей"; }//"CNN Studio"
	else if(family == DoE) { ltext = "[DoE] Министерство Образования"; }//"License Faction"
	else if(family == DoE+1) { ltext = "Админский"; }
	else { ltext = "Гражданский"; }
	return ltext;
}
stock GetPlayerLeaders(playerid)
{
	new ltext[20];
	new family = PlayerInfo[playerid][pLeader];
    if(family == TEAM_GROVE) { ltext = "Grove Street"; }//"Police"
	else if(family == TEAM_BALLAS) { ltext = "The Ballas"; }//"FBI"
	else if(family == TEAM_AZTEC) { ltext = "Varios Los Aztecas"; }//"National Guard"
	else if(family == TEAM_VAGOS) { ltext = "Los Santos Vagos"; }//"Ambulance" Medical Center
	else if(family == TEAM_NANG) { ltext = "Da Nang Boys"; }
	else if(family == TEAM_RIFA) { ltext = "San Fierro Rifa"; }
	else if(family == TEAM_TRIAD) { ltext = "The Traids"; }//"Mayor"Правительство
	else if(family == TEAM_BIKER) { ltext = "Bikers"; }//"Hitmen Agency"
	else if(family == TEAM_MAFIA) { ltext = "The Russian Mafia"; }//"CNN Studio"

    else if(family == DoT) { ltext = "ДПС"; }//"Police"
	else if(family == FBI) { ltext = "ФБР"; }//"FBI"
	else if(family == DoD) { ltext = "Нац.Гвардия"; }//"National Guard"
	else if(family == DoH) { ltext = "МЧС"; }//"Ambulance" Medical Center
	else if(family == LCN) { ltext = "La Cosa Nostra"; }
	else if(family == Yakuza) { ltext = "Yakuza"; }
	else if(family == DoJ) { ltext = "Правительство"; }//"Mayor"Правительство
	else if(family == Hitman) { ltext = "Заказное Агенство"; }//"Hitmen Agency"
	else if(family == SAN) { ltext = "Служба Новостей"; }//"CNN Studio"
	else if(family == DoE) { ltext = "Мин.Образования"; }//"License Faction"
	else { ltext = "Отсутствует"; }
	return ltext;
}


forward GetFamily(playerid);
public GetFamily(playerid)
{
	return PlayerInfo[playerid][pMember];
}

forward GetFamilyRank(playerid);
public GetFamilyRank(playerid)
{
	return PlayerInfo[playerid][pRank];
}


/*stock GetPlayerMembers(playerid)
{
	new mtext[20];
	new family = PlayerInfo[playerid][pMember];
	if(family > 0 && family < MAX_FAMILY)
	{
		strmid(mtext, FamilyInfo[family][fName], 0, strlen(FamilyInfo[family][fName]), 20);
	}
	else mtext = "Civilian";
	return mtext;
}*/
stock GetPlayerMembers(playerid)
{
	new mtext[20];
	new family = PlayerInfo[playerid][pMember];
	if(family > 0 && family < MAX_FAMILY)
	{
		strmid(mtext, GetFamilyName(family), 0, strlen(FamilyInfo[family][fName]), 20);
	}
	else mtext = "Civilian";
	return mtext;
}

/*new PlayerRanks[20][13][50] =
{
	{"","","","","","","","","","","","",""}, // закрытая фракция
	{"","Новито","Плэйя","Хастла","Килла","Юонг","Гангста","О.Г","Мобста","Де кинг","Легенд", "Madd Dogg", "Big Daddy"}, // грув
	{"","Блайд","Бастер","Крэкер","Гун бро ","Ап бро","Гангстер","Федерал блок","Фолкс","Райч нига","Биг вилли", "Madd Dogg", "Big Daddy"}, // баллас
    {"","Перро","Тирадор","Геттор","Лас Геррас","Мирандо","Сабио","Инвасор","Тессорерро","Нестро","Падре", "Madd Dogg", "Big Daddy"}, // ацтек
    {"","Новито","Ординарио","Локал","Верификадо","Бандито","V.E.G","Ассесино","Лидер V. E. G.","Падрино","Падре", "Madd Dogg", "Big Daddy"}, // вагос
    {"","","","","","","","","","","","", ""}, // закрытая фракция
    {"","Ладрон","Новато","Амиго","Мачо","Джуниор","Эрмано","Бандидо","Ауторидид","Аджунто","Падре", "Madd Dogg", "Big Daddy"}, // рифа
    {"","","","","","","","","","","","", ""}, // закрытая фракция
    {"","","","","","","","","","","","", ""}, // закрытая фракция
    {"","","","","","","","","","","","", ""}, // закрытая фракция
    {"","Рядовой","Младший капрал","Капрал","Офицер","Сержант","Младший лейтенант","Лейтенант","Капитан","Заместитель инспектора","Инспектор","Заместитель шефа","Шеф полиции"}, // полиция
    {"","Стажёр","Агент FBI","Агент CID","Рядовой SWAT","Спец.Агент CID","Сержант SWAT","Секретный Агент CID","Лейтенант SWAT","Начальник CID","Капитан SWAT","Зам.Директора FBI", "Директор FBI"}, //FBI
    {"","Рядовой","| Мл. Сержант","|| Сержант","||| Ст. Сержант","== Старшина","* Прапорщик","*|* Лейтенант","**|** Капитан","|*| Майор","|**| Подполковник","*|*|* Полковник", "~*~ Генерал"}, // Армия DOD
    {"","Санитар","Врач","Зав. Отделением","Начальник Службы","Зав.Больницы ЛВ","Зав.Больницы ЛС","Зав.Больницы СФ","Главврач ЛВ","Главврач ЛС","Главврач СФ","Зам.Мин. Здравохранения","Министр Здравохранения"}, //больница
    {"","Салага","Мошенник","Вышибала","Гангстер","Секретарь","Подручный","Капо","Консильери","Правая рука","Дон","Казначей","Крестный отец"}, // LCN
    {"","Новобранец","Юнец","Вакасю","Кёдай","Сятэйгасира","Вакагасира","Со-Хонбутё","Камбу","Оядзи","Сайко Комон","Оябун Кобун","Кумитё"}, // Якудза
    {"","Телохранитель","Соц.Работник","Юрисконсульт","Депутат","Прокурор","Маршал","Первый зам","Ген.Прокурор","Солиситор","Сенатор","Министр Финансов","Губернатор Штата"}, // Правительство
    {"","Послушник","Адепт","Палач","Слаер","Ассасин","Агент тени","Наставник","Информатор","Ситис","Советник","Ст.Советник","Старец"}, // Хитманы
    {"","Стажер","Ассистент","Оператор","Журналист","Шоу-мен","Критик","Сценарист","Редактор","Режиссёр","Главный редактор","Вице-президент SAN","Президент [SAN]"}, // Сан невс
    {"","Практикант","Ассистент Инстр-ра","Инстр-р по Вождению","Инстр-р по Плаванию","Инстр-р по Полётам","Старший Инструктор","Менеджер","Старший Менеджер","Мастер","Старший Мастер","Зам.Мин.Образования","Министр Образования"} // инструкторы
};*/

stock IsAGangs(playerid)//если ты PoliceMen/FBI Agent или лидер команд 1/2 то вернуть 1 иначе 0
{
    new leader = PlayerInfo[playerid][pLeader];
    new member = PlayerInfo[playerid][pMember];
    if(member >= TEAM_GROVE && member <= TEAM_MAFIA) { return 1; }
	if(leader >= TEAM_GROVE && leader <= TEAM_MAFIA) { return 1; }
	return 0;
}

stock GetPlayerRanks(playerid)
{
	new rtext[20];
    if(IsAGangs(playerid))
    {
  		if(PlayerInfo[playerid][pLeader] != 0) { rtext = "Босс"; }
	   	else if(PlayerInfo[playerid][pRank] == 1) { rtext = "Укурок";  }
		else if(PlayerInfo[playerid][pRank] == 2) { rtext = "Салага";  }
		else if(PlayerInfo[playerid][pRank] == 3) { rtext = "Панк"; }
		else if(PlayerInfo[playerid][pRank] == 4) { rtext = "Бандит"; }
		else if(PlayerInfo[playerid][pRank] == 5) { rtext = "Отвязанный"; }
		else if(PlayerInfo[playerid][pRank] == 6) { rtext = "Шестёрка"; }
	   	else if(PlayerInfo[playerid][pRank] == 7) { rtext = "Чудило";  }
		else if(PlayerInfo[playerid][pRank] == 8) { rtext = "Вышибало";  }
		else if(PlayerInfo[playerid][pRank] == 9) { rtext = "Грамила"; }
		else if(PlayerInfo[playerid][pRank] == 10) { rtext = "Информатор"; }
		else if(PlayerInfo[playerid][pRank] == 11) { rtext = "Правая рука"; }
		else if(PlayerInfo[playerid][pRank] == 12) { rtext = "Босс"; }
		else { rtext = "Салага"; }
	}
	else if(PlayerInfo[playerid][pMember] == DoT)//PD Ranks
	{//    {"","Рядовой","Младший капрал","Капрал","Офицер","Сержант","Младший лейтенант","Лейтенант","Капитан","Заместитель инспектора","Инспектор","Заместитель шефа","Шеф полиции"}, // полиция
		if(PlayerInfo[playerid][pLeader] == DoT) { rtext = "Начальник ДПС"; }
	    else if(PlayerInfo[playerid][pRank] == 1) { rtext = "Кадет"; }
		else if(PlayerInfo[playerid][pRank] == 2) { rtext = "Капрал"; }
		else if(PlayerInfo[playerid][pRank] == 3) { rtext = "Сержант"; }
		else if(PlayerInfo[playerid][pRank] == 4) { rtext = "Пом.Патрульного"; }
		else if(PlayerInfo[playerid][pRank] == 5) { rtext = "Патрульный"; }
        else if(PlayerInfo[playerid][pRank] == 6) { rtext = "Офицер"; }
	    else if(PlayerInfo[playerid][pRank] == 7) { rtext = "Коммисар"; }
		else if(PlayerInfo[playerid][pRank] == 8) { rtext = "Инспектор"; }
		else if(PlayerInfo[playerid][pRank] == 9) { rtext = "Ст.Инспектор"; }
		else if(PlayerInfo[playerid][pRank] == 10) { rtext = "Нач.Патруля"; }
		else if(PlayerInfo[playerid][pRank] == 11) { rtext = "Заместитель шефа"; }
        else if(PlayerInfo[playerid][pRank] == 12) { rtext = "Шеф полиции"; }
		else { rtext = "Кадет"; }
	}
	else if(PlayerInfo[playerid][pMember] == FBI)//FBI Ranks
	{ //   {"","Стажёр","Агент FBI","Агент CID","Рядовой SWAT","Спец.Агент CID","Сержант SWAT","Секретный Агент CID","Лейтенант SWAT","Начальник CID","Капитан SWAT","Зам.Директора FBI", "Директор FBI"}, //FBI
		if(PlayerInfo[playerid][pLeader] == FBI) { rtext = "Директор FBI"; }
	    else if(PlayerInfo[playerid][pRank] == 1) { rtext = "Стажёр"; }
		else if(PlayerInfo[playerid][pRank] == 2) { rtext = "Агент FBI"; }//Детектив ФБР
		else if(PlayerInfo[playerid][pRank] == 3) { rtext = "Агент CID"; }
		else if(PlayerInfo[playerid][pRank] == 4) { rtext = "Рядовой SWAT"; }
		else if(PlayerInfo[playerid][pRank] == 5) { rtext = "Спец.Агент CID"; }
	    else if(PlayerInfo[playerid][pRank] == 6) { rtext = "Сержант SWAT"; }
	    else if(PlayerInfo[playerid][pRank] == 7) { rtext = "Секретный Агент CID"; }//
		else if(PlayerInfo[playerid][pRank] == 8) { rtext = "Лейтенант SWAT"; }//Детектив ФБР
		else if(PlayerInfo[playerid][pRank] == 9) { rtext = "Начальник CID"; }
		else if(PlayerInfo[playerid][pRank] == 10) { rtext = "Капитан SWAT"; }
		else if(PlayerInfo[playerid][pRank] == 11) { rtext = "Зам.Директора FBI"; }
	    else if(PlayerInfo[playerid][pRank] == 12) { rtext = "Директор FBI"; }
		else { rtext = "Стажёр"; }
	}
	else if(PlayerInfo[playerid][pMember] == DoD)//NG Ranks
	{
		if(PlayerInfo[playerid][pLeader] == DoD) { rtext = "~*~ Генерал"; }
	    else if(PlayerInfo[playerid][pRank] == 1) { rtext = "Рядовой"; }
		else if(PlayerInfo[playerid][pRank] == 2) { rtext = "| Мл. Сержант"; }
		else if(PlayerInfo[playerid][pRank] == 3) { rtext = "|| Сержант"; }
		else if(PlayerInfo[playerid][pRank] == 4) { rtext = "||| Ст. Сержант"; }
		else if(PlayerInfo[playerid][pRank] == 5) { rtext = "== Старшина"; }
	    else if(PlayerInfo[playerid][pRank] == 6) { rtext = "* Прапорщик"; }
	    else if(PlayerInfo[playerid][pRank] == 7) { rtext = "*|* Лейтенант"; }
		else if(PlayerInfo[playerid][pRank] == 8) { rtext = "**|** Капитан"; }
		else if(PlayerInfo[playerid][pRank] == 9) { rtext = "|*| Майор"; }
		else if(PlayerInfo[playerid][pRank] == 10) { rtext = "|**| Подполковник"; }
		else if(PlayerInfo[playerid][pRank] == 11) { rtext = "*|*|* Полковник"; }
	    else if(PlayerInfo[playerid][pRank] == 12) { rtext = "~*~ Генерал"; }
		else { rtext = "Рядовой"; }
	}
	else if(PlayerInfo[playerid][pMember] == DoH)
	{
		if(PlayerInfo[playerid][pLeader] == DoH) { rtext = "Министр Здравохран"; }
	    else if(PlayerInfo[playerid][pRank] == 1) { rtext = "Санитар"; }
		else if(PlayerInfo[playerid][pRank] == 2) { rtext = "Врач"; }
		else if(PlayerInfo[playerid][pRank] == 3) { rtext = "Зав. Отделением"; }
		else if(PlayerInfo[playerid][pRank] == 4) { rtext = "Начальник Службы"; }
		else if(PlayerInfo[playerid][pRank] == 5) { rtext = "Зав.Больницы ЛВ"; }
	    else if(PlayerInfo[playerid][pRank] == 6) { rtext = "Зав.Больницы ЛС"; }
	    else if(PlayerInfo[playerid][pRank] == 7) { rtext = "Зав.Больницы СФ"; }
		else if(PlayerInfo[playerid][pRank] == 8) { rtext = "Главврач ЛВ"; }
		else if(PlayerInfo[playerid][pRank] == 9) { rtext = "Главврач ЛС"; }
		else if(PlayerInfo[playerid][pRank] == 10) { rtext = "Главврач СФ"; }
		else if(PlayerInfo[playerid][pRank] == 11) { rtext = "Зам.Мин. Здравохран"; }
	    else if(PlayerInfo[playerid][pRank] == 12) { rtext = "Министр Здравохран"; }
		else { rtext = "Стажер"; }
	}
    else if(PlayerInfo[playerid][pMember] == LCN)
    {
    	if(PlayerInfo[playerid][pLeader] == LCN) { rtext = "Крестный отец"; }
       	else if(PlayerInfo[playerid][pRank] == 1) { rtext = "Салага"; }
		else if(PlayerInfo[playerid][pRank] == 2) { rtext = "Мошенник"; }
		else if(PlayerInfo[playerid][pRank] == 3) { rtext = "Вышибала"; }
		else if(PlayerInfo[playerid][pRank] == 4) { rtext = "Гангстер"; }
		else if(PlayerInfo[playerid][pRank] == 5) { rtext = "Секретарь"; }
 		else if(PlayerInfo[playerid][pRank] == 6) { rtext = "Подручный"; }
       	else if(PlayerInfo[playerid][pRank] == 7) { rtext = "Капо"; }
		else if(PlayerInfo[playerid][pRank] == 8) { rtext = "Консильери"; }
		else if(PlayerInfo[playerid][pRank] == 9) { rtext = "Правая рука"; }
		else if(PlayerInfo[playerid][pRank] == 10) { rtext = "Дон"; }
		else if(PlayerInfo[playerid][pRank] == 11) { rtext = "Казначей"; }
		else if(PlayerInfo[playerid][pRank] == 12) { rtext = "Крестный отец"; }
		else { rtext = "Салага"; }
	}
    else if(PlayerInfo[playerid][pMember] == Yakuza)
    {
    	if(PlayerInfo[playerid][pLeader] == Yakuza) { rtext = "Кумитё"; }
       	else if(PlayerInfo[playerid][pRank] == 1) { rtext = "Новобранец"; }
		else if(PlayerInfo[playerid][pRank] == 2) { rtext = "Юнец"; }
		else if(PlayerInfo[playerid][pRank] == 3) { rtext = "Вакасю"; }
		else if(PlayerInfo[playerid][pRank] == 4) { rtext = "Кёдай"; }
		else if(PlayerInfo[playerid][pRank] == 5) { rtext = "Сятэйгасира"; }
 		else if(PlayerInfo[playerid][pRank] == 6) { rtext = "Вакагасира"; }
       	else if(PlayerInfo[playerid][pRank] == 7) { rtext = "Со-Хонбутё"; }
		else if(PlayerInfo[playerid][pRank] == 8) { rtext = "Камбу"; }
		else if(PlayerInfo[playerid][pRank] == 9) { rtext = "Оядзи"; }
		else if(PlayerInfo[playerid][pRank] == 10) { rtext = "Сайко Комон"; }
		else if(PlayerInfo[playerid][pRank] == 11) { rtext = "Оябун Кобун"; }
 		else if(PlayerInfo[playerid][pRank] == 12) { rtext = "Кумитё"; }
		else { rtext = "Новобранец"; }
	}
    else if(PlayerInfo[playerid][pMember] == DoJ)
    {
    	if(PlayerInfo[playerid][pLeader] == DoJ) { rtext = "Губернатор Штата"; }
		else if(PlayerInfo[playerid][pRank] == 1) { rtext = "Телохранитель"; }
		else if(PlayerInfo[playerid][pRank] == 2) { rtext = "Соц.Работник"; }
		else if(PlayerInfo[playerid][pRank] == 3) { rtext = "Юрисконсульт"; }
		else if(PlayerInfo[playerid][pRank] == 4) { rtext = "Депутат"; }
		else if(PlayerInfo[playerid][pRank] == 5) { rtext = "Прокурор"; }
		else if(PlayerInfo[playerid][pRank] == 6) { rtext = "Маршал"; }
		else if(PlayerInfo[playerid][pRank] == 7) { rtext = "Первый зам."; }
		else if(PlayerInfo[playerid][pRank] == 8) { rtext = "Ген.Прокурор"; }
		else if(PlayerInfo[playerid][pRank] == 9) { rtext = "Солиситор"; }
		else if(PlayerInfo[playerid][pRank] == 10) { rtext = "Сенатор"; }
		else if(PlayerInfo[playerid][pRank] == 11) { rtext = "Министр Финансов"; }
		else if(PlayerInfo[playerid][pRank] == 12) { rtext = "Губернатор Штата"; }
		else { rtext = "Охранник"; }
	}
	else if(PlayerInfo[playerid][pMember] == Hitman)//Hitman Ranks
	{
		if(PlayerInfo[playerid][pLeader] == Hitman) { rtext = "Старец"; }
	    else if(PlayerInfo[playerid][pRank] == 1) { rtext = "Послушник"; }
		else if(PlayerInfo[playerid][pRank] == 2) { rtext = "Адепт"; }
		else if(PlayerInfo[playerid][pRank] == 3) { rtext = "Палач"; }
		else if(PlayerInfo[playerid][pRank] == 4) { rtext = "Слаер"; }
		else if(PlayerInfo[playerid][pRank] == 5) { rtext = "Ассасин"; }
	    else if(PlayerInfo[playerid][pRank] == 6) { rtext = "Агент тени"; }
	    else if(PlayerInfo[playerid][pRank] == 7) { rtext = "Наставник"; }
		else if(PlayerInfo[playerid][pRank] == 8) { rtext = "Информатор"; }
		else if(PlayerInfo[playerid][pRank] == 9) { rtext = "Ситис"; }
		else if(PlayerInfo[playerid][pRank] == 10) { rtext = "Советник"; }
		else if(PlayerInfo[playerid][pRank] == 11) { rtext = "Ст.Советник"; }
	    else if(PlayerInfo[playerid][pRank] == 12) { rtext = "Старец"; }//Старец Гор //Владыка
		else { rtext = "Послушник"; }
	}
	else if(PlayerInfo[playerid][pMember] == SAN)//News Ranks
	{
		if(PlayerInfo[playerid][pLeader] == Hitman) { rtext = "Президент [SAN]"; }
	    else if(PlayerInfo[playerid][pRank] == 1) { rtext = "Стажер"; }
		else if(PlayerInfo[playerid][pRank] == 2) { rtext = "Ассистент"; }
		else if(PlayerInfo[playerid][pRank] == 3) { rtext = "Оператор"; }
		else if(PlayerInfo[playerid][pRank] == 4) { rtext = "Журналист"; }
		else if(PlayerInfo[playerid][pRank] == 5) { rtext = "Шоу-мен"; }
		else if(PlayerInfo[playerid][pRank] == 6) { rtext = "Критик"; }
	    else if(PlayerInfo[playerid][pRank] == 7) { rtext = "Сценарист"; }
		else if(PlayerInfo[playerid][pRank] == 8) { rtext = "Редактор"; }
		else if(PlayerInfo[playerid][pRank] == 9) { rtext = "Режиссёр"; }
		else if(PlayerInfo[playerid][pRank] == 10) { rtext = "Главный редактор"; }
		else if(PlayerInfo[playerid][pRank] == 11) { rtext = "Вице-президент SAN"; }
		else if(PlayerInfo[playerid][pRank] == 12) { rtext = "Президент [SAN]"; }
		else { rtext = "Стажер"; }
	}
	else if(PlayerInfo[playerid][pMember] == DoE)//Driving/Flying School Ranks
	{
		if(PlayerInfo[playerid][pLeader] == DoE) { rtext = "Министр Образования"; }
	    else if(PlayerInfo[playerid][pRank] == 1) { rtext = "Практикант"; }
		else if(PlayerInfo[playerid][pRank] == 2) { rtext = "Ассистент Инстр-ра"; }
		else if(PlayerInfo[playerid][pRank] == 3) { rtext = "Инстр-р по Вождению"; }
		else if(PlayerInfo[playerid][pRank] == 4) { rtext = "Инстр-р по Плаванию"; }
		else if(PlayerInfo[playerid][pRank] == 5) { rtext = "Инстр-р по Полётам"; }
		else if(PlayerInfo[playerid][pRank] == 6) { rtext = "Старший Инструктор"; }
	    else if(PlayerInfo[playerid][pRank] == 7) { rtext = "Менеджер"; }
		else if(PlayerInfo[playerid][pRank] == 8) { rtext = "Старший Менеджер"; }
		else if(PlayerInfo[playerid][pRank] == 9) { rtext = "Мастер"; }
		else if(PlayerInfo[playerid][pRank] == 10) { rtext = "Старший Мастер"; }
		else if(PlayerInfo[playerid][pRank] == 11) { rtext = "Зам.Мин.Образования"; }
		else if(PlayerInfo[playerid][pRank] == 12) { rtext = "Министр Образования"; }
		else { rtext = "Практикант"; }
	}
	else
	{
	    if(PlayerInfo[playerid][pRank] == 1) { rtext = "Rank 1"; }
		else if(PlayerInfo[playerid][pRank] == 2) { rtext = "Rank 2"; }
		else if(PlayerInfo[playerid][pRank] == 3) { rtext = "Rank 3"; }
		else if(PlayerInfo[playerid][pRank] == 4) { rtext = "Rank 4"; }
		else if(PlayerInfo[playerid][pRank] == 5) { rtext = "Rank 5"; }
	    else if(PlayerInfo[playerid][pRank] == 6) { rtext = "Rank 6"; }
	    else if(PlayerInfo[playerid][pRank] == 7) { rtext = "Rank 7"; }
		else if(PlayerInfo[playerid][pRank] == 8) { rtext = "Rank 8"; }
		else if(PlayerInfo[playerid][pRank] == 9) { rtext = "Rank 9"; }
		else if(PlayerInfo[playerid][pRank] == 10) { rtext = "Rank 10"; }
		else if(PlayerInfo[playerid][pRank] == 11) { rtext = "Rank 11"; }
	    else if(PlayerInfo[playerid][pRank] == 12) { rtext = "Rank 12"; }
		else rtext = "Ранг Неизвестен";
	}
	return rtext;
}

stock ShowPlayersRanks(playerid)
{   //ф-ия отправки сообщения всем игрокам находящимся в заданом радиусе в зависимости от удалённсти разными цветами
	//new strings[MAX_STRING];
	/*new ftext[20];
    if(PlayerInfo[playerid][pMember] == DoT) ftext = "Road Police";//"Police"
 	else if(PlayerInfo[playerid][pMember] == FBI) ftext = "FBI";//"FBI"
 	else if(PlayerInfo[playerid][pMember] == DoD) ftext = "National Guard";//"National Guard"
	else if(PlayerInfo[playerid][pMember] == DoH) ftext = "FEMA";//"Ambulance" Medical Center
	else if(PlayerInfo[playerid][pMember] == LCN) ftext = "LCN";
	else if(PlayerInfo[playerid][pMember] == Yakuza) ftext = "Yakuza";
	else if(PlayerInfo[playerid][pMember] == DoJ) ftext = "Government";//"Mayor"
	else if(PlayerInfo[playerid][pMember] == Hitman) ftext = "Hitmen Agency";//"Hitmen Agency"
	else if(PlayerInfo[playerid][pMember] == SAN) ftext = "CNN Studio";//"CNN Studio"
	else if(PlayerInfo[playerid][pMember] == DoE) ftext  = "License Faction";//"License Faction"
	else ftext = "None";*/
	new msgitem[(25+24+2+2+32)*20];//1700
	strins(msgitem, "id \tname \t\t\tlevel \trank\tjob title\n______________________________________________________________________\n", strlen(msgitem));
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(PlayerInfo[i][pMember] == PlayerInfo[playerid][pMember])
		{
			if(strlen(PlayerName(i)) < 13) format(strings, sizeof(strings), "%d \t%s \t\t%d \t%d \t%s\n", i, PlayerName(i), PlayerInfo[i][pLevel], PlayerInfo[i][pRank], GetPlayerRanks(i));
			else format(strings, sizeof(strings), "%d \t%s \t%d \t%d \t%s\n", i, PlayerName(i), PlayerInfo[i][pLevel], PlayerInfo[i][pRank], GetPlayerRanks(i));
			strins(msgitem, strings, strlen(msgitem));
		}
	}
	strins(msgitem, "\n______________________________________________________________________\n", strlen(msgitem));
	if(strlen(msgitem) >= sizeof(msgitem))
	{
		//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "Error38: ShowPlayersRanks - %s[%d], strlen(msgitem): %d, sizeof(msgitem): %d", PlayerName(playerid), playerid, strlen(msgitem), sizeof(msgitem));
		Log(ERROR, strings);
		return 1;
	}
	if(strlen(msgitem) <= 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   ShowPlayersRanks пуст");
		return 1;
	}
	format(strings, sizeof(strings), "Show Players %s Ranks", GetPlayerMembers(playerid));
	ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, strings, msgitem, "OK", "");
	return 1;
}



stock IncreaseRank(playerid, amount)//автопрокачка рангов
{//повышение ранга
	new PlayerRank;
	PlayerInfo[playerid][pProfSkill] += amount;
	new msgitem[163];//104 + 33 + 24 + 2
	if(PlayerInfo[playerid][pProfSkill] >= 400 && PlayerInfo[playerid][pProfSkill] <= 430)
	{
		strcat(msgitem, "* Ваш Профессиональный Навык теперь Уровня 5,\nВы можете занимать руководящую должность фракции.\n");
		PlayerRank = 11;
	}//11-12
	else if(PlayerInfo[playerid][pProfSkill] >= 300 && PlayerInfo[playerid][pProfSkill] <= 330)
	{
		strcat(msgitem, "* Ваш Профессиональный Навык Уровня 4,\nВы можете занимать определённые должности с 10 ранга.\n");
		PlayerRank = 10;
	}
	else if(PlayerInfo[playerid][pProfSkill] >= 250 && PlayerInfo[playerid][pProfSkill] <= 280)
	{
		strcat(msgitem, "* Ваш Профессиональный Навык Уровня 4,\nВы можете занимать определённые должности с 9 ранга.\n");
		PlayerRank = 9;
	}
	else if(PlayerInfo[playerid][pProfSkill] >= 200 && PlayerInfo[playerid][pProfSkill] <= 230)
	{
		strcat(msgitem, "* Ваш Профессиональный Навык теперь Уровня 4,\nВы можете занимать определённые должности с 8 ранга.\n");
		PlayerRank = 8;
	}
	else if(PlayerInfo[playerid][pProfSkill] >= 175 && PlayerInfo[playerid][pProfSkill] <= 305)
	{
		strcat(msgitem, "* Ваш Профессиональный Навык Уровня 3,\nВы можете занимать определённые должности с 7 ранга.\n");
		PlayerRank = 7;
	}
	else if(PlayerInfo[playerid][pProfSkill] >= 150 && PlayerInfo[playerid][pProfSkill] <= 180)
	{
		strcat(msgitem, "* Ваш Профессиональный Навык Уровня 3,\nВы можете занимать определённые должности с 6 ранга.\n");
		PlayerRank = 6;
	}
	else if(PlayerInfo[playerid][pProfSkill] >= 125 && PlayerInfo[playerid][pProfSkill] <= 155)
	{
		strcat(msgitem, "* Ваш Профессиональный Навык теперь Уровня 3,\nВы можете занимать определённые должности с 5 ранга.\n");
		PlayerRank = 5;
	}
	else if(PlayerInfo[playerid][pProfSkill] >= 75 && PlayerInfo[playerid][pProfSkill] <= 105)
	{
		strcat(msgitem, "* Ваш Профессиональный Навык Уровня 2,\nВы можете занимать определённые должности с 4 ранга.\n");
		PlayerRank = 4;
	}
	else if(PlayerInfo[playerid][pProfSkill] >= 50 && PlayerInfo[playerid][pProfSkill] <= 80)
	{
		strcat(msgitem, "* Ваш Профессиональный Навык теперь Уровня 2,\nВы можете занимать определённые должности с 3 ранга.\n");
		PlayerRank = 3;
	}
	else return 1;

	if(PlayerInfo[playerid][pRank] < PlayerRank)
	{
		if(PlayerRank > FamilyInfo[PlayerInfo[playerid][pMember]][fRank])
		{
			format(strings, sizeof(strings), "Лидер фракции установил максимальный ранг для автопрокачки: %d",
				FamilyInfo[ PlayerInfo[playerid][pMember] ][fRank]);
			SendClientMessage(playerid, COLOR_GREY, strings);
			return 1;
		}
		format(msgitem, sizeof(msgitem), "%s\n%s Вы хотите поднять ранг до %d?",
			msgitem, PlayerName(playerid), PlayerRank);
		if(strlen(msgitem) >= sizeof(msgitem))
		{
			//ИНФОРМИРОВАНИЕ
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "Error: IncreaseRank %s[%d], strlen(msgitem): %d, sizeof(msgitem): %d",
				PlayerName(playerid), playerid, strlen(msgitem), sizeof(msgitem));
			Log(ERROR, strings);
			return 1;
		}
		if(strlen(msgitem) <= 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   IncreaseRank пуст");//COLOR_BLUEGREY
			return 1;
		}
		ShowPlayerDialogEx(playerid, RANK_DIALOG, DIALOG_STYLE_MSGBOX, "IncreaseRank", msgitem, "ДА", "НЕТ");
	}
	return 1;
}
stock IncreaseRankDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != RANK_DIALOG) return 1;
	
	if(!response)
	{
		return 1;
	}
	new msgitem[256+1];
	//new giveplayerid;
//ShowPlayerDialogEx(playerid, 67, DIALOG_STYLE_MSGBOX, "IncreaseRank", msgitem, "ДА", "НЕТ");
	new PlayerRank;
	if(PlayerInfo[playerid][pProfSkill] >= 400)
	{
		//strcat(msgitem, "* Ваш Профессиональный Навык теперь Уровня 5,\nВы можете занимать руководящую должность фракции.\n");
		PlayerRank = 11;
	}//11-12
	else if(PlayerInfo[playerid][pProfSkill] >= 300)
	{
		//strcat(msgitem, "* Ваш Профессиональный Навык Уровня 4,\nВы можете занимать определённые должности с 10 ранга.\n");
		PlayerRank = 10;
	}
	else if(PlayerInfo[playerid][pProfSkill] >= 250)
	{
		//strcat(msgitem, "* Ваш Профессиональный Навык Уровня 4,\nВы можете занимать определённые должности с 9 ранга.\n");
		PlayerRank = 9;
	}
	else if(PlayerInfo[playerid][pProfSkill] >= 200)
	{
		//strcat(msgitem, "* Ваш Профессиональный Навык теперь Уровня 4,\nВы можете занимать определённые должности с 8 ранга.\n");
		PlayerRank = 8;
	}
	else if(PlayerInfo[playerid][pProfSkill] >= 175)
	{
		//strcat(msgitem, "* Ваш Профессиональный Навык Уровня 3,\nВы можете занимать определённые должности с 7 ранга.\n");
		PlayerRank = 7;
	}
	else if(PlayerInfo[playerid][pProfSkill] >= 150)
	{
		//strcat(msgitem, "* Ваш Профессиональный Навык Уровня 3,\nВы можете занимать определённые должности с 6 ранга.\n");
		PlayerRank = 6;
	}
	else if(PlayerInfo[playerid][pProfSkill] >= 125)
	{
		//strcat(msgitem, "* Ваш Профессиональный Навык теперь Уровня 3,\nВы можете занимать определённые должности с 5 ранга.\n");
		PlayerRank = 5;
	}
	else if(PlayerInfo[playerid][pProfSkill] >= 75)
	{
		//strcat(msgitem, "\t* Ваш Профессиональный Навык Уровня 2,\nВы можете занимать определённые должности с 4 ранга.\n");
		PlayerRank = 4;
	}
	else if(PlayerInfo[playerid][pProfSkill] >= 50)
	{
		//strcat(msgitem, "\t* Ваш Профессиональный Навык теперь Уровня 2,\nВы можете занимать определённые должности с 3 ранга.\n");
		PlayerRank = 3;
	}
	
	if(PlayerInfo[playerid][pLeader] == 0) PlayerInfo[playerid][pRank] = PlayerRank;
	format(msgitem, sizeof(msgitem), "   Bам присвоен Ранг %d", PlayerRank);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
	return 1;
}
stock ReductionRank(playerid, amount)//автопрокачка рангов
{//понижение ранга
	if(PlayerInfo[playerid][pMember] == 0) return 1;

	new PlayerRank;
	PlayerInfo[playerid][pProfSkill] += amount;
	new msgitem[163];//104 + 33 + 24 + 2
	//////new strings[MAX_STRING];
	if( PlayerInfo[playerid][pProfSkill] < 0)
	{
		PlayerInfo[playerid][pProfSkill] = 0;
		format(msgitem, sizeof(msgitem), "%s {FFFFFF}%s[%d]: {FFFF00}покинул фракцию %s.",
			GetPlayerRanks(playerid), PlayerName(playerid), playerid, GetPlayerMembers(playerid));
		//SendClientMessageToAll(COLOR_LIGHTBLUE, strings);
		OOCNews(COLOR_HERBAL, "|_____________________________________ Правительственное сообщение _____________________________________|");
		OOCNews(COLOR_LIGHTBLUE, msgitem);
		//OOCNews(COLOR_HERBAL, "|__________________________________________________________________________________________________________|");
		UninvitePlayerid(MAX_PLAYERS-1, playerid, PlayerName(playerid));
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Вы теперь снова Гражданский.");
		return 1;
	}
	else if(PlayerInfo[playerid][pProfSkill] < 50)
	{
		strcat(msgitem, "* Ваш Профессиональный Навык теперь Уровня 1,\nВы можете занимать определённые должности с 2 ранга.\n");
		PlayerRank = 2;
	}
	else if(PlayerInfo[playerid][pProfSkill] < 75)
	{
		strcat(msgitem, "* Ваш Профессиональный Навык Уровня 2,\nВы можете занимать определённые должности с 3 ранга.\n");
		PlayerRank = 3;
	}
	else if(PlayerInfo[playerid][pProfSkill] < 125)
	{
		strcat(msgitem, "* Ваш Профессиональный Навык теперь Уровня 2,\nВы можете занимать определённые должности с 4 ранга.\n");
		PlayerRank = 4;
	}
	else if(PlayerInfo[playerid][pProfSkill] < 150)
	{
		strcat(msgitem, "* Ваш Профессиональный Навык Уровня 3,\nВы можете занимать определённые должности с 5 ранга.\n");
		PlayerRank = 5;
	}
	else if(PlayerInfo[playerid][pProfSkill] < 175)
	{
		strcat(msgitem, "* Ваш Профессиональный Навык Уровня 3,\nВы можете занимать определённые должности с 6 ранга.\n");
		PlayerRank = 6;
	}
	else if(PlayerInfo[playerid][pProfSkill] < 200)
	{
		strcat(msgitem, "* Ваш Профессиональный Навык теперь Уровня 3,\nВы можете занимать определённые должности с 7 ранга.\n");
		PlayerRank = 7;
	}
	else if(PlayerInfo[playerid][pProfSkill] < 250)
	{
		strcat(msgitem, "* Ваш Профессиональный Навык Уровня 4,\nВы можете занимать определённые должности с 8 ранга.\n");
		PlayerRank = 8;
	}
	else if(PlayerInfo[playerid][pProfSkill] < 300)
	{
		strcat(msgitem, "* Ваш Профессиональный Навык Уровня 4,\nВы можете занимать определённые должности с 9 ранга.\n");
		PlayerRank = 9;
	}
	else if(PlayerInfo[playerid][pProfSkill] < 400)
	{
		strcat(msgitem, "* Ваш Профессиональный Навык теперь Уровня 4,\nВы можете занимать определённые должности с 10 ранга.\n");
		PlayerRank = 10;
	}//11-12
	SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
	if(PlayerInfo[playerid][pRank] > PlayerRank)
	{
		PlayerInfo[playerid][pRank] = PlayerRank;
		format(msgitem, sizeof(msgitem), "   Bы понижены до %d-го Ранга", PlayerRank);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
	}
	return 1;
}


stock GiveDoTEquip(playerid)
{   //вызывается из family_OnPlayerPickUp//DutyPickUp(playerid)
	/*if(PlayerInfo[playerid][pMember] != DoT)// && PlayerInfo[playerid][pAdmin] != 9
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Road Policemen San-Andreas !");
		return 1;
	}*/
	if(GetPVarInt(playerid, "Equipped") == 0)
	{
		new skin = GetPlayerSkin(playerid);//PlayerInfo[playerid][pChar]
		//if(GetPVarInt(playerid, "Equipped") != 0) return SendClientMessage(playerid, COLOR_INTERFACE_BODY, "Вы уже оснащены!");
        if(	(skin >= 265 && skin <= 266) ||
			(skin >= 280 && skin <= 282))
		{	//return 1;//SendClientMessage(playerid, COLOR_GREY, "Эта команда пригодна только для служителей закона(скин 265-266,280-282).");
	        //SetPlayerAttachedObjectEx(playerid, 1, 19142, Spine, 0.0709,0.038,0.0, 0.0,0.0,0.0, 1.14,1.11,1.07);//Броник
	        //SetPlayerAttachedObjectEx(playerid, 1, 19142, Spine, 0.0649,0.0329,0.0140, 0.00,-2.59,0.00, 1.03,1.14,1.06);
			if(skin == 265) SetPlayerAttachedObjectEx(playerid, 1, 19142, Spine, 0.0719,0.0319,0.0000, 0.00,0.00,0.00, 1.00,1.00,1.00);
			else if(skin == 266) SetPlayerAttachedObjectEx(playerid, 1, 19142, Spine, 0.0589,0.0319,0.0000, 0.00,0.00,0.00, 1.00,1.00,1.00);
			else if(skin == 280) SetPlayerAttachedObjectEx(playerid, 1, 19142, Spine, 0.0619,0.0429,0.0059, 0.00,0.00,0.00, 1.08,1.06,1.03);
			else if(skin == 281) SetPlayerAttachedObjectEx(playerid, 1, 19142, Spine, 0.0619,0.0429,0.0059, 0.00,0.00,0.00, 1.08,1.06,1.03);
			else if(skin == 282) SetPlayerAttachedObjectEx(playerid, 1, 19142, Spine, 0.0619,0.0449,0.0109, 0.00,0.00,0.00, 1.13,1.09,1.07);
			else { return SendClientMessage(playerid, COLOR_GREY, "   Обмундирование для вашего скина не предусмотрено !"); }

	        SetPlayerAttachedObjectEx(playerid, 2, 19141, Head, 0.1009,0.006,0.0, 0.0,0.0,0.0, 1.31,0.98,1.11);//Шлем
	        SetPlayerAttachedObjectEx(playerid, TAZER_SLOT, 18642, Left_thigh, 0.1,0.0,-0.11, 0.0,-90.0,90.0);//Tazer на поясе
	        SetPlayerAttachedObjectEx(playerid, 4, 18637, Left_forearm, 0.35,0.0,0.0, 0.0,0.0,180.0);//Щит

	        //GivePlayerWeaponEx(playerid, 3, 1);//дубинка
	        SetPlayerArmourEx(playerid, 100.0);//броня
	        SetPVarInt(playerid, "Equipped", 1);
	        SendClientMessage(playerid, COLOR_LIGHTBLUE, "Вы надели обмундирование!");
        }
	}
	else
	{
        //if(GetPVarInt(playerid, "Equipped") != 1) return SendClientMessage(playerid, COLOR_INTERFACE_BODY, "Вы больше неоснащенны!");
        new Float: armour;
        GetPlayerArmour(playerid, armour);
        if(armour > 0)
        {
            RemovePlayerAttachedObject(playerid, 1);
            SetPlayerArmourEx(playerid, 0.0);
        }
        RemovePlayerAttachedObject(playerid, 2);
        RemovePlayerAttachedObject(playerid, TAZER_SLOT);
        RemovePlayerAttachedObject(playerid, 4);
        new data_weapon[13][2];
        for (new i; i < 13; i++)
        {
            GetPlayerWeaponData(playerid, i, data_weapon[i][0], data_weapon[i][1]);
        }
        ResetPlayerWeaponsEx(playerid);
        for (new i; i < 13; i++)
        {
            if(i == 1) continue;
            GivePlayerWeaponEx(playerid, data_weapon[i][0], data_weapon[i][1]);
        }
        SetPVarInt(playerid, "Equipped", 0);
        SendClientMessage(playerid, COLOR_LIGHTBLUE, "Вы сняли обмундирование.");
	}
	return 1;
}



// Описание ф-ии Установки цвета игрока в зависимости от выбранной группы
stock SetPlayerToTeamColor(reason)//вызывается если кто то конектится, т.е. постоянно
{   //вызывается из cs_OnPlayerCommandText, CSExit, OnPlayerConnect, OnPlayerSpawn
	#pragma unused reason
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(gInTerrorsCount[i]) { //SetPlayerTeam(i, 5);
			SetPlayerColor(i, COLOR_RED); }
		else if(gInCTerrorsCount[i]) { //SetPlayerTeam(i, 6);
			SetPlayerColor(i, COLOR_BLUE); }
		else if(PlayerInfo[i][pJob] == TRUCKER) { SetPlayerColor(i, COLOR_ORANGE); }
		else
		{
 			if(gPlayerSpawned[i] == 1)
			{
				if(MarkerToPlayer[i] != MAX_PLAYERS-1) continue;//пропускаем игроков которые установили на кого то маркер
				//if(MarkerForPlayer[i] != MAX_PLAYERS-1) continue;//пропускаем игроков на которых установили маркер
				//if(CurPlayerColorMarker[i] == COLOR_MAROON) continue;//пропускаем игроков бирюзового цвета

				new member = PlayerInfo[i][pMember];
				if(member == TEAM_GROVE) { SetPlayerColor(i, TEAM_GROVE_COLOR); }
				else if(member == TEAM_BALLAS) { SetPlayerColor(i, TEAM_BALLAS_COLOR); }
				else if(member == TEAM_AZTEC) { SetPlayerColor(i, TEAM_AZTECAS_COLOR); }
				else if(member == TEAM_VAGOS) { SetPlayerColor(i, TEAM_VAGOS_COLOR); }
				else if(member == TEAM_NANG) { SetPlayerColor(i, TEAM_NANG_COLOR); }
				else if(member == TEAM_RIFA) { SetPlayerColor(i, TEAM_RIFA_COLOR);  }
				else if(member == TEAM_TRIAD) { SetPlayerColor(i, TEAM_TRIADS_COLOR); }
				else if(member == TEAM_BIKER) { SetPlayerColor(i, TEAM_BIKERS_COLOR); }
				else if(member == TEAM_MAFIA) { SetPlayerColor(i, TEAM_MAFIA_COLOR); }
				else if(member == DoT) { SetPlayerColor(i, FamilyInfo[DoT][fColor]); } //Police Force
				else if(member == FBI) { SetPlayerColor(i, FamilyInfo[FBI][fColor]); } //FBI/ATF
				else if(member == DoD) { SetPlayerColor(i, FamilyInfo[DoD][fColor]); } //National Guard
				else if(member == DoH) { SetPlayerColor(i, FamilyInfo[DoH][fColor]); } //Fire/Ambulance
				else if(member == LCN) { SetPlayerColor(i, FamilyInfo[LCN][fColor]); } //La Cosa Nostra
				else if(member == Yakuza) { SetPlayerColor(i, FamilyInfo[Yakuza][fColor]);  } //Yakuza
				else if(member == DoJ) { SetPlayerColor(i, FamilyInfo[DoJ][fColor]); } //Mayor
				else if(member == Hitman) { SetPlayerColor(i, FamilyInfo[Hitman][fColor]); } //Hitmans
				else if(member == SAN) { SetPlayerColor(i, FamilyInfo[SAN][fColor]); } //News Reporters
				else if(member == DoE) { SetPlayerColor(i,  FamilyInfo[DoE][fColor]); } //Driving/Flying School
				else {
					//if(!gAnticheat[i]) { SetPlayerColor(i, COLOR_NOANTICHEAT); }
					//else
					//{
					if(PlayerInfo[i][pGunLic] != 1 && !gRealWar) { SetPlayerColor(i, COLOR_NEWBIE); }
					else if(member == Hitman) { SetPlayerColor(i, 0xFFFFFF00); }//прозрачный - белый
					else { SetPlayerColor(i, COLOR_ALIVE); }//white - белый
					//}
				}
				//SetPlayerTeam(i, PlayerInfo[i][pTeam]);

				/*if(TEST[4] == 0)
				{
	   				if(PlayerInfo[i][pAdmin] >= 6)
					{
						//ИНФОРМИРОВАНИЕ
					   	format(strings, sizeof(strings), "SetPlayerToTeamColor(%d)", reason);
						SendClientMessage(i, GetPlayerColor(i), strings);
					}
				}*/

			}
			else { SetPlayerColor(i, COLOR_DEAD); }
		}
	}
}


forward GiveFamilyMoney(family, money);
public GiveFamilyMoney(family, money)
{
	FamilyInfo[family][fBank] += money;
	return 1;
}


stock GetPlayerScoreBuyPrice(playerid, buyprice, show)
{   //вызывается из OnPlayerStatsUpdate, т.к. каждый раз когда сохраняются данные по игроку
	#pragma unused show
	new ScoreConnectTime = PlayerInfo[playerid][pConnectTime]*10;//кол-во отыгранных часов * 10
//суммируем все скилы оружия
	new ScoreGunSkills = PlayerInfo[playerid][pGun22Skill] + PlayerInfo[playerid][pGun23Skill] + PlayerInfo[playerid][pGun24Skill] +
		PlayerInfo[playerid][pGun25Skill] + PlayerInfo[playerid][pGun26Skill] + PlayerInfo[playerid][pGun27Skill] +
		PlayerInfo[playerid][pGun28Skill] + PlayerInfo[playerid][pGun29Skill] + PlayerInfo[playerid][pGun30Skill] +
		PlayerInfo[playerid][pGun31Skill] + PlayerInfo[playerid][pGun34Skill];
//суммируем все прокаченные навыки
	new ScorePerks = (PlayerInfo[playerid][pAlcoholPerk] + PlayerInfo[playerid][pDrugPerk] + PlayerInfo[playerid][pMiserPerk] +
		PlayerInfo[playerid][pPainPerk] + PlayerInfo[playerid][pTraderPerk] +
		PlayerInfo[playerid][pHunger] + PlayerInfo[playerid][pLeisure] +
		PlayerInfo[playerid][pContact] + PlayerInfo[playerid][pToilet] +
		PlayerInfo[playerid][pVigour])*100;
//разница между кол-во убитых врагов и кол-вом своих смертей
	new ScoreKillsDeaths = PlayerInfo[playerid][pKills]-PlayerInfo[playerid][pDeaths];
//суммируем все деньги на депозите, на руках, в банке + buyprice: стоимость всей купленной недвижимости
	new Float: ScoreMoney = float(PlayerInfo[playerid][pDeposit]+PlayerInfo[playerid][pCash]+PlayerInfo[playerid][pBank]+buyprice)/1000.0;
//суммируем все скилы работ
	new Float: ScoreSkills1 = PlayerInfo[playerid][pMinerSkill]/2.5 + PlayerInfo[playerid][pLawSkill] +
		PlayerInfo[playerid][pRoadSkill] + PlayerInfo[playerid][pDrugsSkill]/5.0 + PlayerInfo[playerid][pJackSkill] +
		PlayerInfo[playerid][pProfSkill] + PlayerInfo[playerid][pMechSkill] + PlayerInfo[playerid][pFarmSkill] +
		PlayerInfo[playerid][pGunSkill] + PlayerInfo[playerid][pCarSkill] + PlayerInfo[playerid][pInkasSkill];
	new Float: ScoreSkills2 =
		PlayerInfo[playerid][pBookmakerSkill] + PlayerInfo[playerid][pTaxiSkill] + PlayerInfo[playerid][pBusSkill] +
		PlayerInfo[playerid][pCourierSkill] + PlayerInfo[playerid][pTruckSkill] + PlayerInfo[playerid][pTrashSkill] + PlayerInfo[playerid][pLoadSkill] +
		PlayerInfo[playerid][pWoodSkill] + PlayerInfo[playerid][pFishSkill]/10.0 + PlayerInfo[playerid][pFireSkill] + PlayerInfo[playerid][pCookSkill];
//сумируем очки обучения, очки уважения, и + что выше описано
	PlayerInfo[playerid][pScore] = PlayerInfo[playerid][pTut] + PlayerInfo[playerid][pRespect] + ScoreConnectTime + ScoreGunSkills + ScorePerks + ScoreKillsDeaths + floatround(ScoreMoney + ScoreSkills1 + ScoreSkills2);
//устанавливаем игроку уровень
	if(PlayerInfo[playerid][pLevel] >= 0) PlayerInfo[playerid][pLevel] = GetPlayerLevel(playerid, PlayerInfo[playerid][pScore]);

	/*if(show)
	{
		//ИНФОРМИРОВАНИЕ
		new str[87 + 24+4+5+5+5+5+5];//140
		format(str, sizeof(str), "%s:ConnectTime:%d+Money:%.0f+GunSkills:%d+Skills:%.0f+Perks:%d+KillsDeaths:%d=Score:%d",
			PlayerName(playerid), ScoreConnectTime, ScoreMoney, ScoreGunSkills, ScoreSkills1+ScoreSkills2, ScorePerks, ScoreKillsDeaths, Score);
		return str;
	}*/
	return PlayerInfo[playerid][pScore];//выводим в TAB
}
/*
Уровень     Звание			Требуемые очки опыта
0–4			Новичок			0 XP
5–9 		Энтузиаст		3,400 XP
10–14		Опытный			11,900 XP
15–19		Профессионал	25,400 XP
20–24		Мастер			44,200 XP
25–29		Инструктор		70,200 XP
30–39		Элита			103,700 XP
40–49		Король дорог	176,700 XP
50–150		Легенда			249,700 XP
*/
//Вариант 1 (парабола) EXP to Level = 100*(x-1)^(2)+10*(x-1)+600 лучший вариант

stock GetPlayerLevel(playerid, score)
{   //вызывается из GetPlayerScoreBuyPrice
	#pragma unused playerid
	new rtext[32], level;
	if(score >= 241190) { level = 50; rtext = "Легенда"; }
	
	else if(score >= 231480 && score < 241190) { level = 49; rtext = "Король дорог"; }
	else if(score >= 221970 && score < 231480) { level = 48; rtext = "Король дорог"; }
	else if(score >= 212660 && score < 221970) { level = 47; rtext = "Король дорог"; }
	else if(score >= 203550 && score < 212660) { level = 46; rtext = "Король дорог"; }
	else if(score >= 194640 && score < 203550) { level = 45; rtext = "Король дорог"; }
	else if(score >= 185930 && score < 194640) { level = 44; rtext = "Король дорог"; }
	else if(score >= 177420 && score < 185930) { level = 43; rtext = "Король дорог"; }
	else if(score >= 169110 && score < 177420) { level = 42; rtext = "Король дорог"; }
	else if(score >= 161000 && score < 169110) { level = 41; rtext = "Король дорог"; }
	else if(score >= 153090 && score < 161000) { level = 40; rtext = "Король дорог"; }
	
	else if(score >= 145380 && score < 153090) { level = 39; rtext = "Элита"; }
	else if(score >= 137870 && score < 145380) { level = 38; rtext = "Элита"; }
	else if(score >= 130560 && score < 137870) { level = 37; rtext = "Элита"; }
	else if(score >= 123450 && score < 130560) { level = 36; rtext = "Элита"; }
	else if(score >= 116540 && score < 123450) { level = 35; rtext = "Элита"; }
	else if(score >= 109830 && score < 116540) { level = 34; rtext = "Элита"; }
	else if(score >= 103320 && score < 109830) { level = 33; rtext = "Элита"; }
	else if(score >= 97010 && score < 103320) { level = 32; rtext = "Элита"; }
	else if(score >= 90900 && score < 97010) { level = 31; rtext = "Элита"; }
	else if(score >= 84990 && score < 90900) { level = 30; rtext = "Элита"; }
	
	
	else if(score >= 79280 && score < 84990) { level = 29; rtext = "Инструктор"; }
	else if(score >= 73770 && score < 79280) { level = 28; rtext = "Инструктор"; }
	else if(score >= 68460 && score < 73770) { level = 27; rtext = "Инструктор"; }
	else if(score >= 63350 && score < 68460) { level = 26; rtext = "Инструктор"; }
	else if(score >= 58440 && score < 63350) { level = 25; rtext = "Инструктор"; }
	
	else if(score >= 53730 && score < 58440) { level = 24; rtext = "Мастер"; }
	else if(score >= 49220 && score < 53730) { level = 23; rtext = "Мастер"; }
	else if(score >= 44910 && score < 49220) { level = 22; rtext = "Мастер"; }
	else if(score >= 40800 && score < 44910) { level = 21; rtext = "Мастер"; }
	else if(score >= 36890 && score < 40800) { level = 20; rtext = "Мастер"; }
	
	else if(score >= 33180 && score < 36890) { level = 19; rtext = "Профессионал"; }
	else if(score >= 29670 && score < 33180) { level = 18; rtext = "Профессионал"; }
	else if(score >= 26360 && score < 29670) { level = 17; rtext = "Профессионал"; }
	else if(score >= 23250 && score < 26360) { level = 16; rtext = "Профессионал"; }
	else if(score >= 20340 && score < 23250) { level = 15; rtext = "Профессионал"; }
	
	else if(score >= 17630 && score < 20340) { level = 14; rtext = "Опытный"; }
	else if(score >= 15120 && score < 17630) { level = 13; rtext = "Опытный"; }
	else if(score >= 12810 && score < 15120) { level = 12; rtext = "Опытный"; }
	else if(score >= 10700 && score < 1281) { level = 11; rtext = "Опытный"; }
	else if(score >= 8790 && score < 10700) { level = 10; rtext = "Опытный"; }

	else if(score >= 7080 && score < 8790) { level = 9; rtext = "Энтузиаст"; }
	else if(score >= 5570 && score < 7080) { level = 8; rtext = "Энтузиаст"; }
	else if(score >= 4260 && score < 5570) { level = 7; rtext = "Энтузиаст"; }
	else if(score >= 3150 && score < 4260) { level = 6; rtext = "Энтузиаст"; }
	else if(score >= 2240 && score < 3150) { level = 5; rtext = "Энтузиаст"; }

	else if(score >= 1530 && score < 2240) { level = 4; rtext = "Новичок"; }
	else if(score >= 1020 && score < 1530) { level = 3; rtext = "Новичок"; }
	else if(score >= 710 && score < 1020) { level = 2; rtext = "Новичок"; }
	else if(score < 600) { level = 1; rtext = "Новичок"; }
	return level;
}
	
/*stock GetPlayerLevel(playerid, score)
{   //вызывается из OnPlayerStatsUpdate и OnPlayerLogin
	#pragma unused playerid

	new rtext[32], level;
	//new score = PlayerInfo[playerid][pScore];
	if(score >= 183300) { level = 46; rtext = "Supreme Commander"; }//11740
	else if(score >= 172040 && score < 183300) { level = 45; rtext = "General of the Army"; }//11260
	else if(score >= 161250 && score < 172040) { level = 44; rtext = "Lieutenant General"; }//10790
	else if(score >= 150920 && score < 161250) { level = 43; rtext = "Major General"; }//10330
	else if(score >= 141040 && score < 150920) { level = 42; rtext = "Brigadier General"; }//9880
	else if(score >= 131600 && score < 141040) { level = 41; rtext = "General"; }//9440

	else if(score >= 122590 && score < 131600) { level = 40; rtext = "Field Marshall Gold"; }//9010
	else if(score >= 114000 && score < 122590) { level = 39; rtext = "Field Marshall Silver"; }//8590
	else if(score >= 105820 && score < 114000) { level = 38; rtext = "Field Commissar Gold"; }//8180
	else if(score >= 98040 && score < 105820) { level = 37; rtext = "Field Commissar Silver"; }//7780

	else if(score >= 90650 && score < 98040) { level = 36; rtext = "Commissar Gold"; }//7390
	else if(score >= 83640 && score < 90650) { level = 35; rtext = "Commissar Silver"; }//7010

	else if(score >= 77000 && score < 83640) { level = 34; rtext = "Colonel Gold"; }//6640
	else if(score >= 70720 && score < 77000) { level = 33; rtext = "Colonel Silver"; }//6280

	else if(score >= 64790 && score < 70720) { level = 32; rtext = "Lieutenant Colonel Gold"; }//5930
	else if(score >= 59200 && score < 64790) { level = 31; rtext = "Lieutenant Colonel Silver"; }//5590

	else if(score >= 53940 && score < 59200) { level = 30; rtext = "Major Gold"; }//5260
	else if(score >= 49000 && score < 53940) { level = 29; rtext = "Major Silver"; }//4940

	else if(score >= 44370 && score < 49000) { level = 28; rtext = "Captain Gold"; }//4630
	else if(score >= 40040 && score < 44370) { level = 27; rtext = "Captain Silver"; }//4330

	else if(score >= 36000 && score < 40040) { level = 26; rtext = "2nd Lieutenant Gold"; }//4040
	else if(score >= 32240 && score < 36000) { level = 25; rtext = "2nd Lieutenant Silver"; }//3760
	else if(score >= 28750 && score < 32240) { level = 24; rtext = "1st Lieutenant Gold"; }//3490
	else if(score >= 25520 && score < 28750) { level = 23; rtext = "1st Lieutenant Silver"; }//3230

	else if(score >= 22540 && score < 25520) { level = 22; rtext = "Warrant Officer Gold"; }//2980
	else if(score >= 19800 && score < 22540) { level = 21; rtext = "Warrant Officer Silver"; }//2740

	else if(score >= 17290 && score < 19800) { level = 20; rtext = "Chief Petty Officer Gold"; }//2510
	else if(score >= 15000 && score < 17290) { level = 19; rtext = "Chief Petty Officer Silver"; }//2290

	else if(score >= 12920 && score < 15000) { level = 18; rtext = "Sergeant Major of the Army"; }//2080
	else if(score >= 11040 && score < 12920) { level = 17; rtext = "Sergeant Major Gold"; }//1880
	else if(score >= 9350 && score < 11040) { level = 16; rtext = "Sergeant Major Silver"; }//1690

	else if(score >= 7840 && score < 9350) { level = 15; rtext = "Master Sergeant Gold"; }//1510
	else if(score >= 6500 && score < 7840) { level = 14; rtext = "Master Sergeant Silver"; }//1340

	else if(score >= 5320 && score < 6500) { level = 13; rtext = "Sergeant Gold"; }//1180
	else if(score >= 4290 && score < 5320) { level = 12; rtext = "Sergeant Silver"; }//1030

	else if(score >= 3400 && score < 4290) { level = 11; rtext = "Master Corporal Gold"; }//890
	else if(score >= 2640 && score < 3400) { level = 10; rtext = "Master Corporal Silver"; }//760

	else if(score >= 2000 && score < 2640) { level = 9; rtext = "Lance Corporal Gold"; }//640
	else if(score >= 1470 && score < 2000) { level = 8; rtext = "Lance Corporal Silver"; }//530

	else if(score >= 1040 && score < 1470) { level = 7; rtext = "Corporal Gold"; }//430
	else if(score >= 700 && score < 1040) { level = 6; rtext = "Corporal Silver"; }//340

	else if(score >= 440 && score < 700) { level = 5; rtext = "Gunner Gold"; }//260
	else if(score >= 250 && score < 440) { level = 4; rtext = "Gunner Silver"; }//190

	else if(score >= 120 && score < 250) { level = 3; rtext = "Private 1st Class"; }//130
	else if(score >= 40 && score < 120) { level = 2; rtext = "Private 2nd Class"; }//80
	else if(score < 40) { level = 1; rtext = "Recruit"; }//40
	return level;
}*/



stock OnPlayerChangeLevel(playerid)
{
	if(	GetPlayerLevel(playerid, PlayerInfo[playerid][pScore]) > PlayerInfo[playerid][pLevel] &&
		PlayerInfo[playerid][pLevel] > 0)
	{
		if( strcmp(PlayerInfo[playerid][pReferal], "No-One", true) &&//для рефералов
		  	strcmp(PlayerInfo[playerid][pReferal], "0", true))
		{   //если у игрока есть какой то учитель
			new playername[MAX_PLAYER_NAME];
			strmid(playername, PlayerInfo[playerid][pReferal], 0, strlen(PlayerInfo[playerid][pReferal]), MAX_PLAYER_NAME);
			//mysql_real_escape_string(playername, playername);

			if(CheckExistPlayer(playerid, playername) > 0)
			{
				new giveplayerid = ReturnUser( playername );
				if( !IsPlayerConnected(giveplayerid) )
				{
		    		giveplayerid = MAX_PLAYERS-2;
#if defined vw_sql//#endif
		    		new ToBase[52+10+24];
					format(ToBase, sizeof(ToBase), "UPDATE `players` SET Respect=Respect+1 WHERE `Name`='%s'",
						playername);
					//mysql_query(ToBase);
					db_free_result(db_query(db_VW, ToBase));
#endif
				}
				else
				{
					//GivePlayerMoneyB(1, giveplayerid, costlevel);
					PlayerInfo[giveplayerid][pRespect] += 1;
					format(strings, sizeof(strings), "   Bам перечислено очко уважения от вашего ученика %s[%d].", PlayerName(playerid), playerid);
					SendClientMessage(giveplayerid, COLOR_LILAC, strings);
					SetPlayerShowBattery(giveplayerid, 1, PlayerInfo[giveplayerid][pRespect], 100);
				}
			}
		}
	}
}


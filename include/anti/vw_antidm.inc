
stock antidm_OnPlayerDeath(playerid, killerid, reason)
{
	if(!AntiDM) return 1;
	if(killerid == INVALID_PLAYER_ID) return 1;
	CrashDetected[playerid] = 90;
	if(gRealWar) return 1;
	if(gPlayerBoxing[killerid] != 0) return 1;
	if(gInTerrorsCount[killerid] != 0) return 1;
	if(gInCTerrorsCount[killerid] != 0) return 1;
	if(PlayerInfo[playerid][pMember] == PlayerInfo[killerid][pMember] && PlayerInfo[playerid][pMember] != 0)
	{
		//ReductionRank(killerid, -10);
		return 1;
	}
	if(IsACop(killerid) && gOnDuty[killerid]
		&& PlayerInfo[killerid][pMember] != PlayerInfo[playerid][pMember])
	{
		if(FollowBy[playerid] != MAX_PLAYERS-1)
		{
			ReductionRank(killerid, -100);
		}
		else if(WantedPoints[playerid] <= 0)
		{//обнуляется в if(newstate == PLAYER_STATE_WASTED)
			ReductionRank(killerid, -10);
		}
		else if(WantedPoints[playerid] > 0)
		{
			IncreaseRank(killerid, 5); return 1;
		}
	}
	else if(PlayerInfo[killerid][pMember] == DoD
		&& PlayerInfo[killerid][pMember] != PlayerInfo[playerid][pMember])
	{
		if(FollowBy[playerid] != MAX_PLAYERS-1)
		{
			ReductionRank(killerid, -100);
		}
		else if(PlayerInfo[playerid][pJailed] == 10)
		{//1 военная база только нижний уровень
//если убитый зек
//то его нельзя убивать только на нижнем уровне зоны
//а во всех остальных можно
			if( IsPlayerInArea(playerid, specialzone[2]) ) ReductionRank(killerid, -20);
			else
			{
				IncreaseRank(killerid, 10);	return 1;
			}
		}
		else if(IsPlayerInArea(playerid, specialzone[0]) && PlayerInfo[playerid][pJailed] != 10)
		{
			IncreaseRank(killerid, 10);	return 1;
		}
	}
	else if(IsAtHospital(playerid) && PlayerInfo[killerid][pMember] == DoH)
	{
		return 1;
	}
	else if(PlayerInfo[killerid][pMember] == LCN
		&& PlayerInfo[killerid][pMember] != PlayerInfo[playerid][pMember]
		&& PlayerTied[playerid] != 5 && PlayerTied[playerid] != 6 && PlayerTied[playerid] != 8)
	{
		if(PlayerInfo[playerid][pMember] == Yakuza)
		{
			IncreaseRank(killerid, 20);
			return 1;
		}
		if(PlayerInfo[playerid][pJob] == DRUGDEALER || PlayerInfo[playerid][pJob] == ARMSDEALER)
		{
			IncreaseRank(killerid, 1);
			return 1;
		}
		if(IsACop(playerid) || PlayerInfo[playerid][pMember] == DoD)
		{
			IncreaseRank(killerid, 10);
			return 1;
		}
		if(PlayerInfo[playerid][pMember] == DoH || PlayerInfo[playerid][pMember] == SAN || PlayerInfo[playerid][pMember] == DoE)
		{
			ReductionRank(killerid, -50);
		}
		if(PlayerInfo[playerid][pLocal] == 243) return 1;
		if(IsPlayerInArea(playerid, specialzone[3])) return 1;
	}
	else if(PlayerInfo[killerid][pMember] == Yakuza
		&& PlayerInfo[killerid][pMember] != PlayerInfo[playerid][pMember]
		&& PlayerTied[playerid] != 5 && PlayerTied[playerid] != 6 && PlayerTied[playerid] != 8)
	{
		if(PlayerInfo[playerid][pMember] == LCN)
		{
			IncreaseRank(killerid, 20); return 1;
		}
		if(PlayerInfo[playerid][pJob] == DRUGDEALER || PlayerInfo[playerid][pJob] == ARMSDEALER)
		{
			IncreaseRank(killerid, 1); return 1;
		}
		if(IsACop(playerid) || PlayerInfo[playerid][pMember] == DoD)
		{
			IncreaseRank(killerid, 10); return 1;
		}
		if(PlayerInfo[playerid][pMember] == DoH || PlayerInfo[playerid][pMember] == SAN || PlayerInfo[playerid][pMember] == DoE)
		{
			ReductionRank(killerid, -50);
		}
		if(PlayerInfo[playerid][pLocal] == 244) return 1;
		if(IsPlayerInArea(playerid, specialzone[4])) return 1;
	}
	else if(PlayerInfo[killerid][pMember] == DoJ
		&& PlayerInfo[killerid][pMember] != PlayerInfo[playerid][pMember])//CityHall
	{
		if(FollowBy[playerid] != MAX_PLAYERS-1)
		{
			ReductionRank(killerid, -100);
		}
		if(PlayerInfo[playerid][pLocal] == 241)
		{
			IncreaseRank(killerid, 10); return 1;
		}
	}
	else if(PlayerInfo[killerid][pMember] == Hitman
		&& PlayerInfo[killerid][pMember] != PlayerInfo[playerid][pMember])
	{
		if( IsPlayerInArea(playerid, specialzone[5]) ) return 1;//на территории особняка разрешаем киллерам отстреливаться
		if(GotChaseHitID[killerid] == playerid) return 1;
	}
	else if(PlayerInfo[killerid][pMember] == DoE)
	{
		 if(PlayerInfo[playerid][pLocal] == 253) return 1;//DRIVESCHOOL
	}
	/*else if(PlayerInfo[killerid][pJob] == CARDEALER)//CarDealer
	{
		if( IsPlayerInArea(playerid, specialzone[8]) ) return 1;
	}*/
	else if( IsAGangs(killerid)
		&& PlayerInfo[killerid][pMember] != PlayerInfo[playerid][pMember]
		&& PlayerTied[playerid] != 5 && PlayerTied[playerid] != 6 && PlayerTied[playerid] != 8)
	{
		if(IsAGangs(playerid) && PlayerInfo[killerid][pMember] != PlayerInfo[playerid][pMember])
		{
			IncreaseRank(killerid, 20);
			return 1;
		}
	}
	//--------------------------------------------------------------------------
	//new strings[MAX_STRING];
	if( IsPlayerInRangeOfPoint(playerid, 10.0, spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid]) )
	{//координаты спауна
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d]. Убийство по месту спауна: (x: %.4f, y: %.4f, z: %.4f)!",
			PlayerName(killerid), killerid, PlayerName(playerid), playerid, spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid]);
	}
	else if(IsAtHospital(playerid) && IsAtHospital(killerid) && PlayerInfo[killerid][pMember] != DoH )
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d]. Убийство в запрещенном месте: Hospital !", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(PlayerInfo[playerid][pLocal] == 253 && PlayerInfo[killerid][pLocal] == 253 && PlayerInfo[killerid][pMember] != DoE)
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d]. Убийство в запрещенном месте: DriveSchool !", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(PlayerInfo[playerid][pLocal] == 241 && PlayerInfo[killerid][pLocal] == 241 && PlayerInfo[killerid][pMember] != DoJ)
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d]. Убийство в запрещенном месте: CityHall !", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(IsPlayerInArea(playerid, specialzone[6]) && IsPlayerInArea(killerid, specialzone[6]) && PlayerInfo[killerid][pMember] != Hitman)
	{   //если оба игрока были на территории особняка, то ДМ
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d]. Убийство в запрещенном месте: Hitman Mansion!", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(IsPlayerInArea(playerid, specialzone[8]) && IsPlayerInArea(killerid, specialzone[8]) && PlayerInfo[killerid][pJob] != CARDEALER)
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d]. Убийство в запрещенном месте: CarDealer AutoSalon!", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(PlayerInfo[playerid][pLocal] == 254 && PlayerInfo[killerid][pLocal] == 254)//IsPlayerInArea(playerid, specialzone[11])//Motel
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d]. Убийство в запрещенном месте: Motel!", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	//если убили за 1 минуту 2 раза
	else if( (GetTickCount()-GetPVarInt(killerid, "KillTime")) <= 60000 && //5 минут = 300000
		LastKill[killerid] == playerid && LastKill[killerid] != MAX_PLAYERS-1)
	{	//наказание варном
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d]. Повторное Убийство!", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
    else if(	PlayerInfo[playerid][pGunLic] != 1 && IsFireArm(reason)
    			&& !IsAGangs(playerid)//их можно убивать
				&& !IsACop(playerid)//их можно убивать
				&& PlayerInfo[playerid][pMember] != DoD//их можно убивать
				&& PlayerInfo[playerid][pMember] != Hitman//их можно убивать
				//&& PlayerInfo[playerid][pJailed] == 10
				/*((PlayerInfo[playerid][pMember] == DoH && gOnDuty[playerid]) ||//медик
				(PlayerInfo[playerid][pJob] == ROADWORKER && gJobDuty[playerid]) ||//Дорожный рабочий
				(PlayerInfo[playerid][pJob] == CARMECHANIC && gJobDuty[playerid]) ||//автомеханик
				(PlayerInfo[playerid][pJob] == TAXIDRIVER && gJobDuty[playerid]) ||//таксист
				(PlayerInfo[playerid][pJob] == BUSDRIVER && gJobDuty[playerid]))//водитель автобуса*/
		   )
    {   //наказание варном
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d]. Убийство безоружного игрока!", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
    }
	/*else if(PlayerInfo[playerid][pLevel] == 2 && PlayerInfo[playerid][pMember] == 0)
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d]. Убийство новичка 2 уровня!", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}*/
    else return 1;
 	SendClientMessage(killerid, COLOR_RED, strings);
	SendAllAdminMessage(COLOR_RED, strings, 3);

	OnPlayerPunishment(playerid, killerid, reason);

	if(PlayerInfo[playerid][pLevel] <= 1)
	{   //чтобы читаки 1 лвл не могли фейкилом наказывать
		return 1;
	}
	SetPlayerHealthEx(killerid, 0);
	CrashDetected[playerid] = 91;
    return 1;
}

stock antidm_OnPlayerGiveDamage(playerid, damagedid, weaponid)
{
    if(	PlayerInfo[damagedid][pGunLic] != 1 && IsFireArm(weaponid)
		&& !IsAGangs(damagedid)//их можно убивать
		&& !IsACop(damagedid)//их можно убивать
		&& PlayerInfo[damagedid][pMember] != DoD//их можно убивать
		&& PlayerInfo[damagedid][pMember] != Hitman//их можно убивать
		//&& PlayerInfo[playerid][pJailed] == 10
		/*((PlayerInfo[playerid][pMember] == DoH && gOnDuty[playerid]) ||//медик
		(PlayerInfo[playerid][pJob] == ROADWORKER && gJobDuty[playerid]) ||//Дорожный рабочий
		(PlayerInfo[playerid][pJob] == CARMECHANIC && gJobDuty[playerid]) ||//автомеханик
		(PlayerInfo[playerid][pJob] == TAXIDRIVER && gJobDuty[playerid]) ||//таксист
		(PlayerInfo[playerid][pJob] == BUSDRIVER && gJobDuty[playerid]))//водитель автобуса*/
	   )
    {   //наказание варном
		format(strings, sizeof(strings), "Вы стреляете в безоружного %s! При его смерти - будете наказаны!", PlayerName(damagedid));
		SendClientMessage(playerid, COLOR_YELLOW, strings);
    }
}
stock antidm_OnPlayerTakeDamage(playerid, killerid, Float:amount, weaponid, bodypart)
{	//playerid - тот кто получает ущерб
	//killerid - тот кто наносит
	//amount - кол-во нанесенного ущерба
	CrashDetected[playerid] = 82;

	if(!AntiDM) return 1;
	if(killerid == INVALID_PLAYER_ID) return 1;

	/*new Float:health; GetPlayerHealth(playerid, health);
	if(LastHealth[playerid] == health)
	//if(DetectedGiveDamage[playerid] != 0 && WaitGodModDetected[playerid] <= 0)
	{
       	//new strings[MAX_STRING];
		format(strings, sizeof(strings), "AdmWarning: %s[%d]. Подозрение на бессмертие (Damage: %.1f, LastHealth: %.1f)",
			PlayerName(playerid), playerid, amount, LastHealth[playerid]);
		//SendClientMessage(LastDamagedid[playerid], ADMINS_MESSAGE_COLOR, strings);
		SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strings, 6);

		//SetPlayerHealthEx(playerid, (LastHealth[playerid]-amount));

		//DetectedGiveDamage[playerid] = 0;
		//WaitGodModDetected[playerid] = 0;
	}*/

	if(weaponid == 34 && bodypart == BODY_PART_HEAD)
	{
		SetPlayerHealthEx(playerid, 0);
	}
	if(gRealWar) return 1;
	if(gPlayerBoxing[killerid] != 0) return 1;
	if(gInTerrorsCount[killerid] != 0) return 1;
	if(gInCTerrorsCount[killerid] != 0) return 1;
	//if(!IsFireArm(GetPlayerWeapon(killerid))) return 1;
	if(PlayerInfo[playerid][pMember] == PlayerInfo[killerid][pMember] && PlayerInfo[playerid][pMember] != 0)
	{
		//ReductionRank(killerid, -10);
		return 1;
	}

	if(	IsFireArm(weaponid) &&
		PlayerInfo[playerid][pJailed] != 10) checktimedamage[playerid] = GetTickCount();

	GetPlayerHealth(killerid, LastHealth[killerid]);

	new Float: difference;
	if(LastHealth[killerid] >= LastHealth[playerid])
	{//если здоровье киллера больше чем у игрока
		difference = 1.0 + LastHealth[killerid]/LastHealth[playerid];
	}
	else difference = 2.0;
	//==========================================================================
	if( PlayerInfo[playerid][pAccount] == 365)
	{
		SetPlayerHealthEx(killerid, (LastHealth[killerid]-difference*amount));
	}
	if(//если игрок вообще не мог стрелять с оружия
		IsFireArm(weaponid) &&
		(
			PlayerInfo[killerid][pGunLic] != 1 ||//нету лицензии
			//(!gAnticheat[killerid] && !strcmp(php_host, "gta.strikearena.ru", true)) ||//нету античита
			GetPlayerInterior(killerid) != 0 ||//в интерьерах
			(IsPlayerInArea(killerid, specialzone[6]) && PlayerInfo[killerid][pMember] != Hitman) ||//особняк Hitman
			(IsPlayerInArea(killerid, specialzone[8]) && PlayerInfo[killerid][pJob] != CARDEALER) ||//AutoSalon
			(IsAtHospital(killerid) && PlayerInfo[killerid][pMember] != DoH) ||//Hospital
			(PlayerInfo[killerid][pJob] == MINER && gJobDuty[killerid])//для шахтёров
		)
	  )
	{
		SetPlayerHealthEx(killerid, (LastHealth[killerid]-3*amount));
	}
	//--------------------------------------------------------------------------
//тут то что важнее чем убийство в запрещённом месте
	/*if(PlayerInfo[playerid][pMember] == PlayerInfo[killerid][pMember] && PlayerInfo[playerid][pMember] != 0)
	{
		SetPlayerHealthEx(killerid, (LastHealth[killerid]-amount));
	}*/
	if(IsACop(killerid) && gOnDuty[killerid])
	{
		if(FollowBy[playerid] != MAX_PLAYERS-1)
		{//если коп стреляет по подконвойному своему
			SetPlayerHealthEx(killerid, (LastHealth[killerid]-difference*amount));
		}
		else if(WantedPoints[playerid] <= 0)
		{//если коп стреляет в игрока без розыска
   			SetPlayerHealthEx(killerid, (LastHealth[killerid]-difference*amount));
		}
		else if(WantedPoints[playerid] > 0)
		{//разрешить ДМ копам по всем с розыском
			return 1;
		}
	}
	else if(PlayerInfo[killerid][pMember] == DoD)
	{
		if(FollowBy[playerid] != MAX_PLAYERS-1)
		{//если стреляет по подконвойному своему
			SetPlayerHealthEx(killerid, (LastHealth[killerid]-difference*amount));
		}
		else if(PlayerInfo[playerid][pJailed] == 10)
		{//1 военная база только нижний уровень
			if( IsPlayerInArea(playerid, specialzone[2]) )
			{//если НГ стреляет по зэку на нижнем уровне
				SetPlayerHealthEx(killerid, (LastHealth[killerid]-difference*amount));
			}
			else
			{
				return 1;
			}
		}
		else if(IsPlayerInArea(playerid, specialzone[0]) && PlayerInfo[playerid][pJailed] != 10)
		{
			return 1;
		}
	}
	else if(PlayerInfo[killerid][pMember] == DoH)
	{//разрешён ДМ медикам в больницах
		if(IsAtHospital(playerid)) return 1;
	}
	else if(PlayerInfo[killerid][pMember] == LCN)
	{
		if(PlayerInfo[playerid][pMember] == Yakuza)
		{//разрешить ДМ семьям против семей
			return 1;
		}
		if(PlayerInfo[playerid][pLocal] == 243) return 1;//Особняк LCN
		if(IsPlayerInArea(playerid, specialzone[3])) return 1;//база LCN
		if(PlayerInfo[playerid][pMember] == DoH || PlayerInfo[playerid][pMember] == SAN || PlayerInfo[playerid][pMember] == DoE)
		{//если член семьи стреляет по медику, сановцу или интструктору
			SetPlayerHealthEx(killerid, (LastHealth[killerid]-difference*amount));
		}
	}
	else if(PlayerInfo[killerid][pMember] == Yakuza)
	{
		if(PlayerInfo[playerid][pMember] == LCN)
		{
			return 1;
		}
		if(PlayerInfo[playerid][pLocal] == 244) return 1;//Особняк Yakudza
		if(IsPlayerInArea(playerid, specialzone[4])) return 1;//4 база Yakuza
		if(PlayerInfo[playerid][pMember] == DoH || PlayerInfo[playerid][pMember] == SAN || PlayerInfo[playerid][pMember] == DoE)
		{
			SetPlayerHealthEx(killerid, (LastHealth[killerid]-difference*amount));
		}
	}
	else if(PlayerInfo[killerid][pMember] == DoJ)//CityHall
	{
		if(FollowBy[playerid] != MAX_PLAYERS-1)
		{
			SetPlayerHealthEx(killerid, (LastHealth[killerid]-difference*amount));
		}
		if(PlayerInfo[playerid][pLocal] == 241)
		{//разрешить ДМ правительству в Мэрии
			return 1;
		}
	}
	else if(PlayerInfo[killerid][pMember] == Hitman)
	{
		if( IsPlayerInArea(playerid, specialzone[5]) ) return 1;//на территории особняка разрешаем киллерам отстреливаться
		if(GotChaseHitID[killerid] == playerid) return 1;//разрешаем в любом месте выполнять заказы
	}
	else if(PlayerInfo[killerid][pMember] == SAN)
	{//разрешить ДМ сановцам в Студии новостей
		 if(PlayerInfo[playerid][pLocal] == 249) return 1;
	}
	else if(PlayerInfo[killerid][pMember] == DoE)
	{//разрешить ДМ интрукторам в Автошколе
		 if(PlayerInfo[playerid][pLocal] == 253) return 1;//DRIVESCHOOL
	}
	else if(PlayerInfo[killerid][pJob] == CARDEALER)//CarDealer
	{//разрешить ДМ автодиллеам в Автосалоне
		if( IsPlayerInArea(playerid, specialzone[8]) ) return 1;
	}
	else if( IsAGangs(killerid) )
	{
		if(IsAGangs(playerid) && PlayerInfo[killerid][pMember] != PlayerInfo[playerid][pMember])
		{//разрешить ДМ банд
			return 1;
		}
	}
	//--------------------------------------------------------------------------
	//new strings[MAX_STRING];
	if(IsAtHospital(playerid) && IsAtHospital(killerid) && PlayerInfo[killerid][pMember] != DoH )
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d] в запрещенном месте: Hospital !", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(PlayerInfo[playerid][pLocal] == 241 && PlayerInfo[killerid][pLocal] == 241 && PlayerInfo[killerid][pMember] != DoJ)
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d] в запрещенном месте: CityHall !", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(IsPlayerInArea(playerid, specialzone[6]) && IsPlayerInArea(killerid, specialzone[6]) && PlayerInfo[killerid][pMember] != Hitman)
	{   //если оба игрока были на территории особняка, то ДМ
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d] в запрещенном месте: Hitman Mansion!", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(PlayerInfo[killerid][pLocal] == 249 && PlayerInfo[killerid][pMember] != SAN)
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d] в запрещенном месте: CNNStudio !", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(PlayerInfo[playerid][pLocal] == 253 && PlayerInfo[killerid][pLocal] == 253 && PlayerInfo[killerid][pMember] != DoE)
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d] в запрещенном месте: DriveSchool !", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(IsPlayerInArea(playerid, specialzone[8]) && IsPlayerInArea(killerid, specialzone[8]) && PlayerInfo[killerid][pJob] != CARDEALER)
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d] в запрещенном месте: CarDealer AutoSalon!", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(PlayerInfo[playerid][pLocal] == 254 && PlayerInfo[killerid][pLocal] == 254)//IsPlayerInArea(playerid, specialzone[11])//Motel
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d] в запрещенном месте: Motel!", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
    else if(	PlayerInfo[playerid][pGunLic] != 1 && IsFireArm(weaponid)
    			&& !IsAGangs(playerid)//их можно убивать
				&& !IsACop(playerid)//их можно убивать
				&& PlayerInfo[playerid][pMember] != LCN//их можно убивать
				&& PlayerInfo[playerid][pMember] != Yakuza//их можно убивать
				&& PlayerInfo[playerid][pMember] != DoD//их можно убивать
				&& PlayerInfo[playerid][pMember] != Hitman//их можно убивать
				//&& PlayerInfo[playerid][pJailed] == 10
				/*((PlayerInfo[playerid][pMember] == DoH && gOnDuty[playerid]) ||//медик
				(PlayerInfo[playerid][pJob] == ROADWORKER && gJobDuty[playerid]) ||//Дорожный рабочий
				(PlayerInfo[playerid][pJob] == CARMECHANIC && gJobDuty[playerid]) ||//автомеханик
				(PlayerInfo[playerid][pJob] == TAXIDRIVER && gJobDuty[playerid]) ||//таксист
				(PlayerInfo[playerid][pJob] == BUSDRIVER && gJobDuty[playerid]))//водитель автобуса*/
		   )
    {   //наказание варном
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d] безоружного игрока!", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
    }
	else if(PlayerInfo[playerid][pMember] == SAN && (playerid == gTranslatorTV || TalkingLive[playerid] != MAX_PLAYERS-1))
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d] ведущего SAN !", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	else if(PlayerInfo[playerid][pLevel] < 3 && PlayerInfo[playerid][pMember] == 0)
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch новичка {FFFFFF}%s[%d] !", PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}
	//если ненесли ущерб в течении минуты 2 раза
	/*else if( (GetTickCount()-GetPVarInt(killerid, "KillTime")) <= 60000 && //5 минут = 300000
		(GetTickCount()-GetPVarInt(killerid, "KillTime")) >= 1000 &&
		LastKill[killerid] == playerid && LastKill[killerid] != MAX_PLAYERS-1)
	{
		format(strings, sizeof(strings), "CEPBEP: {FFFFFF}%s[%d] {800000}DeathMatch {FFFFFF}%s[%d] повторный!",
			PlayerName(killerid), killerid, PlayerName(playerid), playerid);
	}*/
    else return 1;
 	SendClientMessage(killerid, COLOR_RED, strings);

	SetPlayerHealthEx(killerid, (LastHealth[killerid]-difference*amount));
	CrashDetected[playerid] = 83;
    return 1;
}

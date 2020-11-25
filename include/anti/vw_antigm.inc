stock antiGM_OnPlayerGiveDamage(damagedid, Float:amount)
{
	if(!ANTIGODMOD) return 1;
	if(GetPlayerSpeed(damagedid) > 0) return 1;
	if(amount < 10.0) return 1;
	if(GetPlayerWeaponState(damagedid) == WEAPONSTATE_RELOADING) return 1;

 	WaitGodModDetected[damagedid] = CHEATLIM;//CHEATLIM+2;
	DetectedGiveDamage[damagedid] = floatround(amount);//подняли флаг
	return 0;
}

stock antiGM_OnPlayerTakeDamage(playerid, Float:amount)
{
	if(!ANTIGODMOD) return 1;
	LastHealth[playerid] -= amount;
    //if(playerid == INVALID_PLAYER_ID) return 1;
   	DetectedGiveDamage[playerid] = 0;//опустили флаг, проверку прошёл игроку получил урон.
	//WaitGodModDetected[playerid] = floatround(amount);
	return 0;
}

stock AntiGodModTimer(playerid)
{   //вызывается из OneSecondTimers2
	if(!ANTIGODMOD) return 1;
 	if(gAnticheat[playerid] == 1) return 1;//!strcmp(php_host, "gta.strikearena.ru", true)

	if(AFK_IdleTime[playerid] >= 3) return 1;
	if(IsPlayerInAnyVehicle(playerid)) return 1;

	WaitGodModDetected[playerid] --;
	if(DetectedGiveDamage[playerid] != 0 && WaitGodModDetected[playerid] <= 0)
	{
		CrashDetected[playerid] = 68;
       	//new strings[MAX_STRING];
		format(strings, sizeof(strings), "AdmWarning: %s[%d]. Подозрение на бессмертие (%d здоровья отнял сервер)",//TakeDamage: %d
			PlayerName(playerid), playerid, DetectedGiveDamage[playerid]);//WaitGodModDetected[playerid]
		SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strings, 6);

		SetPlayerHealthEx(playerid, (LastHealth[playerid]-DetectedGiveDamage[playerid]));

		DetectedGiveDamage[playerid] = 0;
		WaitGodModDetected[playerid] = 0;

		//format(strings, sizeof(strings), "%s[%d] kicked, reason: бессмертие", PlayerName(playerid),playerid);
		//Log(CHEAT, strings);
		////Kick(playerid);
	}
	return 1;
}

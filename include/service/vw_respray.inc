
//##############################################################################//
//                                                                              //
//                            ÑÈÑÒÅÌÀ ÏÎÊÐÀÑÊÈ ÀÂÒÎ                             //
//                                                                              //
//##############################################################################//


new PlayerIsAtRespray[MAX_PLAYERS];




stock respray_OnPlayerUpdate(playerid, newstate)//CheckPlayerIsAtResprayUpdate
{
	if(!IsPlayerInAnyVehicle(playerid)) return 1;
	if(newstate != PLAYER_STATE_DRIVER) return 1;
	if(!IsAtVehicleRespray(playerid)) return 1;

	PlayerIsAtRespray[playerid] = CHEATLIM;
	new Float:health; GetVehicleHealth(nCarID[playerid], health);
	if(health > LastVehHealth[playerid] && LastVehHealth[playerid] < 1000.0)
	{   //åñëè çäîðîâüå óâåëè÷èëîñü
   		LastVehHealth[playerid] = 1000.0;

		PlayerInfo[playerid][pCash] -= SBizInfo[13][sbEntranceCost];
		PlaySoundForPlayer(playerid, SOUND_PART_MISSION_COMPLETE);
		ResetPlayerMoney(playerid);//÷òîáû íå îòîáðàæàòü èãðîâûõ -100 ïðè êàæäîé ñìåðòè
		gConsumingMoney[playerid] = 2;
		GivePlayerMoney(playerid, PlayerInfo[playerid][pCash]);
		LastMoney[playerid] = PlayerInfo[playerid][pCash];

		OnGangsExtortionSBiz(13, SBizInfo[13][sbEntranceCost]);
		SBizInfo[13][sbProducts] --;
	}
	//ÈÍÔÎÐÌÈÐÎÂÀÍÈÅ
	/*//new strings[MAX_STRING];
	format(strings, sizeof(strings), "AdmWarning: %s[%d] VehHealth: %.0f (CurrentHealth:%.0f, LastHealth:%.0f)",
		PlayerName(playerid),playerid,
		(health-LastVehHealth[playerid]),
		health, LastVehHealth[playerid]);
	SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strings, 9);*/
	return 1;
}




stock anticleo_OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(	newstate == PLAYER_STATE_DRIVER && oldstate == PLAYER_STATE_PASSENGER )
		 //|| newstate == PLAYER_STATE_PASSENGER && oldstate == PLAYER_STATE_DRIVER)// /fc -
	{
	    if( LastCar[playerid] > 0 && !IsInNPCVehicle(LastCar[playerid]) && !gAnticheat[playerid])
	    {
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ты был кикнут за использование cleo-script");

			format(strings, sizeof(strings), "CEPBEP: %s[%d] kicked, reason: cleo", PlayerName(playerid), playerid);
			SendSystemMessage(COLOR_MAROON, strings, 1);
			Log(KICK, strings);
			if(PlayerInfo[playerid][pAdmin] != 9)
			{
				IsKicked[playerid] = 1;
			}
			return 1;
		}
	}
	return 0;
}



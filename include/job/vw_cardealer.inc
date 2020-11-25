//для автодилеров


stock cardealer_OnPlayerPickUp(playerid, pickupid)
{
 	#pragma unused pickupid
	//--------------------------------------------------------------------------
	if( IsPlayerInRangeOfPoint(playerid, 2.1, -1663.8074,1207.7589,7.2546)//AutoSalon
		|| IsPlayerInRangeOfPoint(playerid, 2.1, 415.6489,2533.6672,19.1484)
		|| IsPlayerInRangeOfPoint(playerid, 2.1, 718.5229,-1476.4646,5.4688) )
	{   //для покупки авто
	    if(Counter3DText >= MAX_3DTEXT_GLOBAL)
	    {
	        SendClientMessage(playerid, COLOR_GREY, "   Кол-во личного транспорта на сервере достигло максимума!");
			return 1;
		}
	    if(GetMaxVehicles >= MAX_VEHICLES-1-sizeof(AdminCars))
	    {
	        SendClientMessage(playerid, COLOR_GREY, "   Кол-во транспорта достигло максимума!");
			return 1;
		}
       	if(IsPlayerInAnyVehicle(playerid))
		{
			SendClientMessage(playerid, COLOR_GREY, "  Вы НЕ должны находиться в транспортном средстве!");
			return 1;
		}
		new giveplayerid = -1;
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			if(PlayerInfo[i][pJailed] != 0) continue;
			if(AFK_IdleTime[i] >= 3) continue;
			if(PlayerInfo[i][pJob] != CARDEALER)  continue;
            giveplayerid = i;
		}
       	if(giveplayerid != -1 && PlayerInfo[playerid][pJob] != CARDEALER && !gRealWar)
		{// && PlayerInfo[playerid][pLevel] > 3
			//format(strings, sizeof(strings), "  Покупка транспортных средств осуществляется только при отсутствии автодилеров! Свяжитесь с %s[%d]", PlayerName(giveplayerid), giveplayerid);
			SendClientMessage(playerid, COLOR_GREY, "  Покупка транспортных средств осуществляется только при отсутствии автодилеров (USE: /cardealer) !");
			return 1;
		}
       	if(numplayers > (GetMaxPlayers()/2) && PlayerInfo[playerid][pLevel] > 3 && !gRealWar)
		{
			format(strings, sizeof(strings), "  Покупка транспортных средств осуществляется при онлайне меньше %d !", (GetMaxPlayers()/2));
			SendClientMessage(playerid, COLOR_GREY, strings);
			return 1;
		}
		//new msgitem[218+32+3+10+6+3+6+3 + 12];
		/*ShowPlayerDialogGap(playerid, 66, DIALOG_STYLE_INPUT, "AutoSalon",
			"Пожалуйста укажите модель транспорта \nи нажмите BUY. \nДля просмотра каталога транспорта введите /carinfo",
			"BUY", "Cancel");*/
		//if(DialogID[playerid][0] != 66)
		//{//чтобы постоянно при подборе пикапа не перезаписывалась MenuOperation[playerid] = 136;
		DialogID[playerid][0] = AutoSalon_DIALOG;
		CarInfo(playerid);
		//}
		//return 1;
	}
	return 1;
}

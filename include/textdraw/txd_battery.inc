//--------------------------------------------------------------------------
//для батарейки
new bool:gTextDrawShowBattery[MAX_PLAYERS];
new bool:gTextDrawHideBattery[MAX_PLAYERS];
new bool:TextDrawShowBattery[MAX_PLAYERS];
//для батарейки
new Text:txdBlackSpeed;
new Text:txdMarkerMinus;
new Text:txdMarkerPlus;
new Text:txdDarkYellowSpeed;
new PlayerText:txdLightYellowSpeed[MAX_PLAYERS];

stock battery_OnGameModeInit()
{

	txdBlackSpeed = TextDrawCreateEx(16.500000, 290.000000, "_");
	TextDrawLetterSize(txdBlackSpeed, 1.000000, 2.381000);
	TextDrawTextSize(txdBlackSpeed, 167.500000, 0.000000);
	TextDrawAlignment(txdBlackSpeed, 0);
	TextDrawColor(txdBlackSpeed, -1);
	TextDrawUseBox(txdBlackSpeed, 1);
	TextDrawBoxColor(txdBlackSpeed, 150);
	TextDrawSetShadow(txdBlackSpeed, 1);
	TextDrawSetOutline(txdBlackSpeed, 1);
	TextDrawBackgroundColor(txdBlackSpeed, 255);
	TextDrawFont(txdBlackSpeed, 1);
	TextDrawSetProportional(txdBlackSpeed, 1);

	txdDarkYellowSpeed = TextDrawCreateEx(30.500000, 295.000000, "_");
	TextDrawLetterSize(txdDarkYellowSpeed, 1.000000, 1.200000);
	TextDrawTextSize(txdDarkYellowSpeed, 153.000000, 0.000000);
	TextDrawAlignment(txdDarkYellowSpeed, 0);
	TextDrawColor(txdDarkYellowSpeed, -1);
	TextDrawUseBox(txdDarkYellowSpeed, 1);
	TextDrawBoxColor(txdDarkYellowSpeed, -65485);
	TextDrawSetShadow(txdDarkYellowSpeed, 0);
	TextDrawSetOutline(txdDarkYellowSpeed, 1);
	TextDrawBackgroundColor(txdDarkYellowSpeed, 255);
	TextDrawFont(txdDarkYellowSpeed, 1);
	TextDrawSetProportional(txdDarkYellowSpeed, 1);

	txdMarkerMinus = TextDrawCreateEx(19.500000, 293.000000, "-");
	TextDrawLetterSize(txdMarkerMinus, 0.500000, 1.500000);
	TextDrawAlignment(txdMarkerMinus, 0);
	TextDrawColor(txdMarkerMinus, -1);
	TextDrawSetShadow(txdMarkerMinus, 0);
	TextDrawSetOutline(txdMarkerMinus, 0);
	TextDrawBackgroundColor(txdMarkerMinus, 255);
	TextDrawFont(txdMarkerMinus, 1);
	TextDrawSetProportional(txdMarkerMinus, 1);

	txdMarkerPlus = TextDrawCreateEx(157.000000, 293.000000, "+");
	TextDrawLetterSize(txdMarkerPlus, 0.500000, 1.500000);
	TextDrawAlignment(txdMarkerPlus, 0);
	TextDrawColor(txdMarkerPlus, -1);
	TextDrawSetShadow(txdMarkerPlus, 0);
	TextDrawSetOutline(txdMarkerPlus, 0);
	TextDrawBackgroundColor(txdMarkerPlus, 255);
	TextDrawFont(txdMarkerPlus, 1);
	TextDrawSetProportional(txdMarkerPlus, 1);

}
stock battery_OnGameModeExit()
{
//для батарейки
	TextDrawDestroyEx(txdBlackSpeed);
	TextDrawDestroyEx(txdDarkYellowSpeed);
	TextDrawDestroyEx(txdMarkerMinus);
	TextDrawDestroyEx(txdMarkerPlus);
}

stock battery_OnPlayerConnect(playerid)
{
	gTextDrawShowBattery[playerid] = false;
	gTextDrawHideBattery[playerid] = false;

	txdLightYellowSpeed[playerid] = CreatePlayerTextDraw(playerid, 29.500000, 287.500000, "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");
	PlayerTextDrawLetterSize(playerid, txdLightYellowSpeed[playerid], 0.138999, 2.438998);
	PlayerTextDrawAlignment(playerid, txdLightYellowSpeed[playerid], 1);
	PlayerTextDrawColor(playerid, txdLightYellowSpeed[playerid], -1);
	PlayerTextDrawSetShadow(playerid, txdLightYellowSpeed[playerid], 0);
	PlayerTextDrawSetOutline(playerid, txdLightYellowSpeed[playerid], 0);
	PlayerTextDrawFont(playerid, txdLightYellowSpeed[playerid], 1);
	PlayerTextDrawSetProportional(playerid, txdLightYellowSpeed[playerid], 1);

}

stock battery_OnPlayerDisconnect(playerid)
{
	if(TextDrawShowBattery[playerid] == true)
	{
		TextDrawHideForPlayer(playerid, txdBlackSpeed);
		TextDrawHideForPlayer(playerid, txdDarkYellowSpeed);
		TextDrawHideForPlayer(playerid, txdMarkerMinus);
		TextDrawHideForPlayer(playerid, txdMarkerPlus);
		PlayerTextDrawHide(playerid, txdLightYellowSpeed[playerid]);
		TextDrawShowBattery[playerid] = false;
	}
//для батарейки
	PlayerTextDrawDestroyEx(playerid, txdLightYellowSpeed[playerid]);
}


stock SetPlayerShowBattery(playerid, indicator_num, indicator, limit)
{
//indicator_num - признак(1 - для уважения, 2 - для оружия)
//indicator - новое значение
//limit - максимальное значение
    if(indicator-1 <= limit)
    {   //если не показан, то показать
    	gTextDrawShowBattery[playerid] = true; OnPlayerTextDrawStateChange(playerid);

		new percent;
	    if(indicator > limit) percent = 100;//limit;
	    else if(indicator < 0) percent = 0;
	    else percent = indicator*100/limit;
		new strtmp[101];
		switch(indicator_num)
		{
		    case 1:
		    {

				if(indicator > indicator6[playerid])
				{
			   		for(new p=0; p<percent-1; p++)
			   		{
						strins(strtmp, "l", strlen(strtmp));
					}
					strins(strtmp, "~g~l", strlen(strtmp));
				}
				else if(indicator < indicator6[playerid])
				{
			   		for(new p=0; p<percent-1; p++)
			   		{
						strins(strtmp, "l", strlen(strtmp));
					}
					strins(strtmp, "~r~l", strlen(strtmp));
				}
				else
				{
			   		for(new p=0; p<percent; p++)
			   		{
						strins(strtmp, "l", strlen(strtmp));
					}
				}
			}
		    case 2:
		    {

				if(indicator > indicator7[playerid])
				{
			   		for(new p=0; p<percent-1; p++)
			   		{
						strins(strtmp, "l", strlen(strtmp));
					}
					strins(strtmp, "~g~l", strlen(strtmp));
				}
				else if(indicator < indicator7[playerid])
				{
			   		for(new p=0; p<percent-1; p++)
			   		{
						strins(strtmp, "l", strlen(strtmp));
					}
					strins(strtmp, "~r~l", strlen(strtmp));
				}
				else
				{
			   		for(new p=0; p<percent; p++)
			   		{
						strins(strtmp, "l", strlen(strtmp));
					}
				}
			}
		}

		PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
		PlayerTextDrawSetStringEx(playerid, txdLightYellowSpeed[playerid],strtmp);
	}
	return 1;
}



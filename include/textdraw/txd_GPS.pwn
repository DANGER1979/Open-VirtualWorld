// система загрузки текстур
new Text:GPS_TD[3];
new PlayerText:GPS_PTD[MAX_PLAYERS][3];

stock GPS_SYSTEM()
{
	//GPS SYSTEM
	GPS_TD[0] = TextDrawCreate(570.9665, 265.3406, "LD_SPAC:white"); // пусто
	TextDrawTextSize(GPS_TD[0], 67.0000, 21.0000);
	TextDrawAlignment(GPS_TD[0], 1);
	TextDrawColor(GPS_TD[0], 1229539839);
	TextDrawBackgroundColor(GPS_TD[0], 255);
	TextDrawFont(GPS_TD[0], 4);
	TextDrawSetProportional(GPS_TD[0], 0);
	TextDrawSetShadow(GPS_TD[0], 0);

	GPS_TD[1] = TextDrawCreate(572.9998, 266.3259, "Навигатор"); // пусто
	TextDrawLetterSize(GPS_TD[1], 0.1416, 0.6210);
	TextDrawAlignment(GPS_TD[1], 1);
	TextDrawColor(GPS_TD[1], -1);
	TextDrawBackgroundColor(GPS_TD[1], 255);
	TextDrawFont(GPS_TD[1], 2);
	TextDrawSetProportional(GPS_TD[1], 1);
	TextDrawSetShadow(GPS_TD[1], 0);

	GPS_TD[2] = TextDrawCreate(571.0004, 286.4962, "LD_SPAC:white"); // пусто
	TextDrawTextSize(GPS_TD[2], 67.0000, 12.0000);
	TextDrawAlignment(GPS_TD[2], 1);
	TextDrawColor(GPS_TD[2], 724249599);
	TextDrawBackgroundColor(GPS_TD[2], 255);
	TextDrawFont(GPS_TD[2], 4);
	TextDrawSetProportional(GPS_TD[2], 0);
	TextDrawSetShadow(GPS_TD[2], 0);
	
}


stock GPS_SYSTEM_PL(playerid)
{
	//GPS SYSTEM
	GPS_PTD[playerid][0] = CreatePlayerTextDraw(playerid, 572.9996, 271.7183,"~y~Тест"); // NAME
	PlayerTextDrawLetterSize(playerid, GPS_PTD[playerid][0], 0.1233, 0.7330);
	PlayerTextDrawAlignment(playerid, GPS_PTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, GPS_PTD[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, GPS_PTD[playerid][0], 255);
	PlayerTextDrawFont(playerid, GPS_PTD[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, GPS_PTD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, GPS_PTD[playerid][0], 0);

	GPS_PTD[playerid][1] = CreatePlayerTextDraw(playerid, 572.9996, 277.9407, "~y~расстояние:_200_M")); // DIST
	PlayerTextDrawLetterSize(playerid, GPS_PTD[playerid][1], 0.1233, 0.7330);
	PlayerTextDrawAlignment(playerid, GPS_PTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, GPS_PTD[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, GPS_PTD[playerid][1], 255);
	PlayerTextDrawFont(playerid, GPS_PTD[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, GPS_PTD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, GPS_PTD[playerid][1], 0);

	GPS_PTD[playerid][2] = CreatePlayerTextDraw(playerid, 572.3334, 288.3554, "LD_SPAC:white"); // MOVE_BOX
	PlayerTextDrawTextSize(playerid, GPS_PTD[playerid][2], 64.0000, 8.2199);
	PlayerTextDrawAlignment(playerid, GPS_PTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, GPS_PTD[playerid][2], 679189247);
	PlayerTextDrawBackgroundColor(playerid, GPS_PTD[playerid][2], 255);
	PlayerTextDrawFont(playerid, GPS_PTD[playerid][2], 4);
	PlayerTextDrawSetProportional(playerid, GPS_PTD[playerid][2], 0);
	PlayerTextDrawSetShadow(playerid, GPS_PTD[playerid][2], 0);
}


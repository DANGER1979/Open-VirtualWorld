// система загрузки экрана заставки во время входа в интерьер
new Text:LOAD_TEXTURE_TD[20];
new PlayerText:LOAD_TEXTURE_PTD[MAX_PLAYERS];

stock ScreenSaver()
{

	LOAD_TEXTURE_TD[0] = TextDrawCreateEx(-5.666600, -9.111100, "Box");
	TextDrawLetterSize(LOAD_TEXTURE_TD[0], 0.000000, 51.099941);
	TextDrawTextSize(LOAD_TEXTURE_TD[0], 673.000000, 0.000000);
	TextDrawAlignment(LOAD_TEXTURE_TD[0], 1);
	TextDrawColor(LOAD_TEXTURE_TD[0], -11403266);
	TextDrawUseBox(LOAD_TEXTURE_TD[0], 1);
	TextDrawBoxColor(LOAD_TEXTURE_TD[0], -1547178497);
	TextDrawSetShadow(LOAD_TEXTURE_TD[0], 0);
	TextDrawSetOutline(LOAD_TEXTURE_TD[0], 0);
	TextDrawBackgroundColor(LOAD_TEXTURE_TD[0], 255);
	TextDrawFont(LOAD_TEXTURE_TD[0], 1);
	TextDrawSetProportional(LOAD_TEXTURE_TD[0], 1);
	TextDrawSetShadow(LOAD_TEXTURE_TD[0], 0);

	LOAD_TEXTURE_TD[1] = TextDrawCreateEx(196.633499, 14.377499, "particle:lamp_shad_64");
	TextDrawLetterSize(LOAD_TEXTURE_TD[1], 0.000000, 0.000000);
	TextDrawTextSize(LOAD_TEXTURE_TD[1], 256.000000, 207.000000);
	TextDrawAlignment(LOAD_TEXTURE_TD[1], 1);
	TextDrawColor(LOAD_TEXTURE_TD[1], -327888);
	TextDrawSetShadow(LOAD_TEXTURE_TD[1], 0);
	TextDrawSetOutline(LOAD_TEXTURE_TD[1], 0);
	TextDrawBackgroundColor(LOAD_TEXTURE_TD[1], 255);
	TextDrawFont(LOAD_TEXTURE_TD[1], 4);
	TextDrawSetProportional(LOAD_TEXTURE_TD[1], 0);
	TextDrawSetShadow(LOAD_TEXTURE_TD[1], 0);
	TextDrawSetSelectable(LOAD_TEXTURE_TD[1], true);

	LOAD_TEXTURE_TD[2] = TextDrawCreateEx(293.000305, 164.778106, "");
	TextDrawLetterSize(LOAD_TEXTURE_TD[2], 0.000000, 0.000000);
	TextDrawTextSize(LOAD_TEXTURE_TD[2], 102.000000, 122.000000);
	TextDrawAlignment(LOAD_TEXTURE_TD[2], 1);
	TextDrawColor(LOAD_TEXTURE_TD[2], 16777215);
	TextDrawSetShadow(LOAD_TEXTURE_TD[2], 0);
	TextDrawSetOutline(LOAD_TEXTURE_TD[2], 0);
	TextDrawBackgroundColor(LOAD_TEXTURE_TD[2], 0);
	TextDrawFont(LOAD_TEXTURE_TD[2], 5);
	TextDrawSetProportional(LOAD_TEXTURE_TD[2], 0);
	TextDrawSetShadow(LOAD_TEXTURE_TD[2], 0);
	TextDrawSetPreviewModel(LOAD_TEXTURE_TD[2], 3872);
	TextDrawSetPreviewRot(LOAD_TEXTURE_TD[2], 258.000000, 190.000000, 255.000000, 0.896700);

	LOAD_TEXTURE_TD[3] = TextDrawCreateEx(208.000106, 182.615097, "");
	TextDrawLetterSize(LOAD_TEXTURE_TD[3], 0.000000, 0.000000);
	TextDrawTextSize(LOAD_TEXTURE_TD[3], 128.000000, 70.000000);
	TextDrawAlignment(LOAD_TEXTURE_TD[3], 1);
	TextDrawColor(LOAD_TEXTURE_TD[3], 16777215);
	TextDrawSetShadow(LOAD_TEXTURE_TD[3], 0);
	TextDrawSetOutline(LOAD_TEXTURE_TD[3], 0);
	TextDrawBackgroundColor(LOAD_TEXTURE_TD[3], 0);
	TextDrawFont(LOAD_TEXTURE_TD[3], 5);
	TextDrawSetProportional(LOAD_TEXTURE_TD[3], 0);
	TextDrawSetShadow(LOAD_TEXTURE_TD[3], 0);
	TextDrawSetPreviewModel(LOAD_TEXTURE_TD[3], 3872);
	TextDrawSetPreviewRot(LOAD_TEXTURE_TD[3], 208.000000, 218.000000, 215.000000, 0.870599);

	LOAD_TEXTURE_TD[4] = TextDrawCreateEx(253.666793, 144.867004, "");
	TextDrawLetterSize(LOAD_TEXTURE_TD[4], 0.000000, 0.000000);
	TextDrawTextSize(LOAD_TEXTURE_TD[4], 106.000000, 131.000000);
	TextDrawAlignment(LOAD_TEXTURE_TD[4], 1);
	TextDrawColor(LOAD_TEXTURE_TD[4], 16777215);
	TextDrawSetShadow(LOAD_TEXTURE_TD[4], 0);
	TextDrawSetOutline(LOAD_TEXTURE_TD[4], 0);
	TextDrawBackgroundColor(LOAD_TEXTURE_TD[4], 0);
	TextDrawFont(LOAD_TEXTURE_TD[4], 5);
	TextDrawSetProportional(LOAD_TEXTURE_TD[4], 0);
	TextDrawSetShadow(LOAD_TEXTURE_TD[4], 0);
	TextDrawSetPreviewModel(LOAD_TEXTURE_TD[4], 3872);
	TextDrawSetPreviewRot(LOAD_TEXTURE_TD[4], 0.000000, 304.000000, 0.000000, 0.896700);

	LOAD_TEXTURE_TD[5] = TextDrawCreateEx(340.300201, 129.696197, "LD_BEAT:chit");
	TextDrawLetterSize(LOAD_TEXTURE_TD[5], 0.000000, 0.000000);
	TextDrawTextSize(LOAD_TEXTURE_TD[5], 19.000000, 23.000000);
	TextDrawAlignment(LOAD_TEXTURE_TD[5], 1);
	TextDrawColor(LOAD_TEXTURE_TD[5], -165);
	TextDrawSetShadow(LOAD_TEXTURE_TD[5], 0);
	TextDrawSetOutline(LOAD_TEXTURE_TD[5], 0);
	TextDrawBackgroundColor(LOAD_TEXTURE_TD[5], 255);
	TextDrawFont(LOAD_TEXTURE_TD[5], 4);
	TextDrawSetProportional(LOAD_TEXTURE_TD[5], 0);
	TextDrawSetShadow(LOAD_TEXTURE_TD[5], 0);

	LOAD_TEXTURE_TD[6] = TextDrawCreateEx(197.966796, 242.525802, "particle:lamp_shad_64");
	TextDrawLetterSize(LOAD_TEXTURE_TD[6], 0.000000, 0.000000);
	TextDrawTextSize(LOAD_TEXTURE_TD[6], 250.000000, -21.000000);
	TextDrawAlignment(LOAD_TEXTURE_TD[6], 1);
	TextDrawColor(LOAD_TEXTURE_TD[6], 7274292);
	TextDrawSetShadow(LOAD_TEXTURE_TD[6], 0);
	TextDrawSetOutline(LOAD_TEXTURE_TD[6], 0);
	TextDrawBackgroundColor(LOAD_TEXTURE_TD[6], 255);
	TextDrawFont(LOAD_TEXTURE_TD[6], 4);
	TextDrawSetProportional(LOAD_TEXTURE_TD[6], 0);
	TextDrawSetShadow(LOAD_TEXTURE_TD[6], 0);

	LOAD_TEXTURE_TD[7] = TextDrawCreateEx(191.966796, 222.199600, "particle:cloudhigh");
	TextDrawLetterSize(LOAD_TEXTURE_TD[7], 0.000000, 0.000000);
	TextDrawTextSize(LOAD_TEXTURE_TD[7], 222.000000, 18.000000);
	TextDrawAlignment(LOAD_TEXTURE_TD[7], 1);
	TextDrawColor(LOAD_TEXTURE_TD[7], -182);
	TextDrawSetShadow(LOAD_TEXTURE_TD[7], 0);
	TextDrawSetOutline(LOAD_TEXTURE_TD[7], 0);
	TextDrawBackgroundColor(LOAD_TEXTURE_TD[7], 255);
	TextDrawFont(LOAD_TEXTURE_TD[7], 4);
	TextDrawSetProportional(LOAD_TEXTURE_TD[7], 0);
	TextDrawSetShadow(LOAD_TEXTURE_TD[7], 0);

	LOAD_TEXTURE_TD[8] = TextDrawCreateEx(424.666900, 227.033203, "TM");
	TextDrawLetterSize(LOAD_TEXTURE_TD[8], 0.158600, 0.666599);
	TextDrawAlignment(LOAD_TEXTURE_TD[8], 1);
	TextDrawColor(LOAD_TEXTURE_TD[8], 6734847);
	TextDrawSetShadow(LOAD_TEXTURE_TD[8], 0);
	TextDrawSetOutline(LOAD_TEXTURE_TD[8], 0);
	TextDrawBackgroundColor(LOAD_TEXTURE_TD[8], -1061093377);
	TextDrawFont(LOAD_TEXTURE_TD[8], 1);
	TextDrawSetProportional(LOAD_TEXTURE_TD[8], 1);
	TextDrawSetShadow(LOAD_TEXTURE_TD[8], 0);

	LOAD_TEXTURE_TD[9] = TextDrawCreateEx(340.300292, 137.577301, "particle:cloudmasked");
	TextDrawLetterSize(LOAD_TEXTURE_TD[9], 0.000000, 0.000000);
	TextDrawTextSize(LOAD_TEXTURE_TD[9], 20.000000, 12.000000);
	TextDrawAlignment(LOAD_TEXTURE_TD[9], 1);
	TextDrawColor(LOAD_TEXTURE_TD[9], 2031393);
	TextDrawSetShadow(LOAD_TEXTURE_TD[9], 0);
	TextDrawSetOutline(LOAD_TEXTURE_TD[9], 0);
	TextDrawBackgroundColor(LOAD_TEXTURE_TD[9], 255);
	TextDrawFont(LOAD_TEXTURE_TD[9], 4);
	TextDrawSetProportional(LOAD_TEXTURE_TD[9], 0);
	TextDrawSetShadow(LOAD_TEXTURE_TD[9], 0);

	LOAD_TEXTURE_TD[10] = TextDrawCreateEx(221.600204, 228.277694, "VIRTUAL");
	TextDrawLetterSize(LOAD_TEXTURE_TD[10], 0.773299, 3.259200);
	TextDrawAlignment(LOAD_TEXTURE_TD[10], 1);
	TextDrawColor(LOAD_TEXTURE_TD[10], -1061109505);
	TextDrawSetShadow(LOAD_TEXTURE_TD[10], 0);
	TextDrawSetOutline(LOAD_TEXTURE_TD[10], 1);
	TextDrawBackgroundColor(LOAD_TEXTURE_TD[10], 6471935);
	TextDrawFont(LOAD_TEXTURE_TD[10], 1);
	TextDrawSetProportional(LOAD_TEXTURE_TD[10], 1);
	TextDrawSetShadow(LOAD_TEXTURE_TD[10], 0);

	LOAD_TEXTURE_TD[11] = TextDrawCreateEx(291.000000, 303.344604, "LOADING");
	TextDrawLetterSize(LOAD_TEXTURE_TD[11], 0.421999, 1.765900);
	TextDrawAlignment(LOAD_TEXTURE_TD[11], 1);
	TextDrawColor(LOAD_TEXTURE_TD[11], 6734335);
	TextDrawSetShadow(LOAD_TEXTURE_TD[11], 0);
	TextDrawSetOutline(LOAD_TEXTURE_TD[11], 0);
	TextDrawBackgroundColor(LOAD_TEXTURE_TD[11], 255);
	TextDrawFont(LOAD_TEXTURE_TD[11], 1);
	TextDrawSetProportional(LOAD_TEXTURE_TD[11], 1);
	TextDrawSetShadow(LOAD_TEXTURE_TD[11], 0);

	LOAD_TEXTURE_TD[12] = TextDrawCreateEx(191.033401, 254.770095, "particle:lamp_shad_64");
	TextDrawLetterSize(LOAD_TEXTURE_TD[12], 0.000000, 0.000000);
	TextDrawTextSize(LOAD_TEXTURE_TD[12], 266.000000, -3.000000);
	TextDrawAlignment(LOAD_TEXTURE_TD[12], 1);
	TextDrawColor(LOAD_TEXTURE_TD[12], 6466753);
	TextDrawSetShadow(LOAD_TEXTURE_TD[12], 0);
	TextDrawSetOutline(LOAD_TEXTURE_TD[12], 0);
	TextDrawBackgroundColor(LOAD_TEXTURE_TD[12], 255);
	TextDrawFont(LOAD_TEXTURE_TD[12], 4);
	TextDrawSetProportional(LOAD_TEXTURE_TD[12], 0);
	TextDrawSetShadow(LOAD_TEXTURE_TD[12], 0);

	LOAD_TEXTURE_TD[13] = TextDrawCreateEx(-179.699905, 370.288299, "particle:cloudmasked");
	TextDrawLetterSize(LOAD_TEXTURE_TD[13], 0.000000, 0.000000);
	TextDrawTextSize(LOAD_TEXTURE_TD[13], 899.000000, 107.000000);
	TextDrawAlignment(LOAD_TEXTURE_TD[13], 1);
	TextDrawColor(LOAD_TEXTURE_TD[13], -120);
	TextDrawSetShadow(LOAD_TEXTURE_TD[13], 0);
	TextDrawSetOutline(LOAD_TEXTURE_TD[13], 0);
	TextDrawBackgroundColor(LOAD_TEXTURE_TD[13], 255);
	TextDrawFont(LOAD_TEXTURE_TD[13], 4);
	TextDrawSetProportional(LOAD_TEXTURE_TD[13], 0);
	TextDrawSetShadow(LOAD_TEXTURE_TD[13], 0);

	LOAD_TEXTURE_TD[14] = TextDrawCreateEx(-54.333198, 357.014495, "particle:lamp_shad_64");
	TextDrawLetterSize(LOAD_TEXTURE_TD[14], 0.000000, 0.000000);
	TextDrawTextSize(LOAD_TEXTURE_TD[14], 745.000000, -27.000000);
	TextDrawAlignment(LOAD_TEXTURE_TD[14], 1);
	TextDrawColor(LOAD_TEXTURE_TD[14], -171);
	TextDrawSetShadow(LOAD_TEXTURE_TD[14], 0);
	TextDrawSetOutline(LOAD_TEXTURE_TD[14], 0);
	TextDrawBackgroundColor(LOAD_TEXTURE_TD[14], 255);
	TextDrawFont(LOAD_TEXTURE_TD[14], 4);
	TextDrawSetProportional(LOAD_TEXTURE_TD[14], 0);
	TextDrawSetShadow(LOAD_TEXTURE_TD[14], 0);

	LOAD_TEXTURE_TD[15] = TextDrawCreateEx(-0.999899, 342.236907, "Box");
	TextDrawLetterSize(LOAD_TEXTURE_TD[15], 0.000000, -0.899900);
	TextDrawTextSize(LOAD_TEXTURE_TD[15], 655.000000, 0.000000);
	TextDrawAlignment(LOAD_TEXTURE_TD[15], 1);
	TextDrawColor(LOAD_TEXTURE_TD[15], -1);
	TextDrawUseBox(LOAD_TEXTURE_TD[15], 1);
	TextDrawBoxColor(LOAD_TEXTURE_TD[15], 6734335);
	TextDrawSetShadow(LOAD_TEXTURE_TD[15], 0);
	TextDrawSetOutline(LOAD_TEXTURE_TD[15], 0);
	TextDrawBackgroundColor(LOAD_TEXTURE_TD[15], 255);
	TextDrawFont(LOAD_TEXTURE_TD[15], 1);
	TextDrawSetProportional(LOAD_TEXTURE_TD[15], 1);
	TextDrawSetShadow(LOAD_TEXTURE_TD[15], 0);

	LOAD_TEXTURE_TD[16] = TextDrawCreateEx(-96.366500, 88.629203, "particle:lamp_shad_64");
	TextDrawLetterSize(LOAD_TEXTURE_TD[16], 0.000000, 0.000000);
	TextDrawTextSize(LOAD_TEXTURE_TD[16], 823.000000, -95.000000);
	TextDrawAlignment(LOAD_TEXTURE_TD[16], 1);
	TextDrawColor(LOAD_TEXTURE_TD[16], 8060735);
	TextDrawSetShadow(LOAD_TEXTURE_TD[16], 0);
	TextDrawSetOutline(LOAD_TEXTURE_TD[16], 0);
	TextDrawBackgroundColor(LOAD_TEXTURE_TD[16], 255);
	TextDrawFont(LOAD_TEXTURE_TD[16], 4);
	TextDrawSetProportional(LOAD_TEXTURE_TD[16], 0);
	TextDrawSetShadow(LOAD_TEXTURE_TD[16], 0);

	LOAD_TEXTURE_TD[17] = TextDrawCreateEx(298.300109, 217.221694, "particle:shad_rcbaron");
	TextDrawLetterSize(LOAD_TEXTURE_TD[17], 0.000000, 0.000000);
	TextDrawTextSize(LOAD_TEXTURE_TD[17], 46.000000, -15.000000);
	TextDrawAlignment(LOAD_TEXTURE_TD[17], 1);
	TextDrawColor(LOAD_TEXTURE_TD[17], -213);
	TextDrawSetShadow(LOAD_TEXTURE_TD[17], 0);
	TextDrawSetOutline(LOAD_TEXTURE_TD[17], 0);
	TextDrawBackgroundColor(LOAD_TEXTURE_TD[17], 255);
	TextDrawFont(LOAD_TEXTURE_TD[17], 4);
	TextDrawSetProportional(LOAD_TEXTURE_TD[17], 0);
	TextDrawSetShadow(LOAD_TEXTURE_TD[17], 0);

	LOAD_TEXTURE_TD[18] = TextDrawCreateEx(339.333496, 227.862899, "WORLD");
	TextDrawLetterSize(LOAD_TEXTURE_TD[18], 0.773299, 3.259200);
	TextDrawAlignment(LOAD_TEXTURE_TD[18], 1);
	TextDrawColor(LOAD_TEXTURE_TD[18], 6734335);
	TextDrawSetShadow(LOAD_TEXTURE_TD[18], 0);
	TextDrawSetOutline(LOAD_TEXTURE_TD[18], 1);
	TextDrawBackgroundColor(LOAD_TEXTURE_TD[18], -1061093377);
	TextDrawFont(LOAD_TEXTURE_TD[18], 1);
	TextDrawSetProportional(LOAD_TEXTURE_TD[18], 1);
	TextDrawSetShadow(LOAD_TEXTURE_TD[18], 0);

	LOAD_TEXTURE_TD[19] = TextDrawCreateEx(285.999908, 306.033294, "/");
	TextDrawLetterSize(LOAD_TEXTURE_TD[19], 5.020299, 1.073099);
	TextDrawAlignment(LOAD_TEXTURE_TD[19], 1);
	TextDrawColor(LOAD_TEXTURE_TD[19], -1547178497);
	TextDrawSetShadow(LOAD_TEXTURE_TD[19], 0);
	TextDrawSetOutline(LOAD_TEXTURE_TD[19], 0);
	TextDrawBackgroundColor(LOAD_TEXTURE_TD[19], 255);
	TextDrawFont(LOAD_TEXTURE_TD[19], 2);
	TextDrawSetProportional(LOAD_TEXTURE_TD[19], 1);
	TextDrawSetShadow(LOAD_TEXTURE_TD[19], 0);

}

stock ScreenSaverBar(playerid)
{

	// Загрузка текстур
	LOAD_TEXTURE_PTD[playerid] = CreatePlayerTextDrawEx(playerid, -4.333300, 338.718383, "Box");
	PlayerTextDrawLetterSize(playerid, LOAD_TEXTURE_PTD[playerid], 0.000000, -0.166266);
	PlayerTextDrawTextSize(playerid, LOAD_TEXTURE_PTD[playerid], -1.589998, 0.000000);
	PlayerTextDrawAlignment(playerid, LOAD_TEXTURE_PTD[playerid], 1);
	PlayerTextDrawColor(playerid, LOAD_TEXTURE_PTD[playerid], -11403265);
	PlayerTextDrawUseBox(playerid, LOAD_TEXTURE_PTD[playerid], 1);
	PlayerTextDrawBoxColor(playerid, LOAD_TEXTURE_PTD[playerid], -1061109505);
	PlayerTextDrawSetShadow(playerid, LOAD_TEXTURE_PTD[playerid], 0);
	PlayerTextDrawSetOutline(playerid, LOAD_TEXTURE_PTD[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, LOAD_TEXTURE_PTD[playerid], 255);
	PlayerTextDrawFont(playerid, LOAD_TEXTURE_PTD[playerid], 1);
	PlayerTextDrawSetProportional(playerid, LOAD_TEXTURE_PTD[playerid], 1);
	PlayerTextDrawSetShadow(playerid, LOAD_TEXTURE_PTD[playerid], 0);

}

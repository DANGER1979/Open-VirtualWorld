//Global Textdraws:

new Text:Accessories[35];
new PlayerText:AccessoriesP[MAX_PLAYERS];

stock LoadAccTD()
{
	Accessories[0] = TextDrawCreateEx(261.833374, 384.118530, "LD_BEAT:chit");
	TextDrawLetterSize(Accessories[0], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[0], 10.666669, 12.859247);
	TextDrawAlignment(Accessories[0], 1);
	TextDrawColor(Accessories[0], 623191551);
	TextDrawSetShadow(Accessories[0], 0);
	TextDrawSetOutline(Accessories[0], 0);
	TextDrawFont(Accessories[0], 4);
	TextDrawSetProportional(Accessories[0], 1);

	Accessories[1] = TextDrawCreateEx(267.166687, 386.607421, "LD_SPAC:white");
	TextDrawLetterSize(Accessories[1], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[1], 114.666641, 7.881468);
	TextDrawAlignment(Accessories[1], 1);
	TextDrawColor(Accessories[1], 623191551);
	TextDrawSetShadow(Accessories[1], 0);
	TextDrawSetOutline(Accessories[1], 0);
	TextDrawFont(Accessories[1], 4);
	TextDrawSetProportional(Accessories[1], 1);

	Accessories[2] = TextDrawCreateEx(376.166778, 384.203704, "LD_BEAT:chit");
	TextDrawLetterSize(Accessories[2], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[2], 10.666670, 12.859247);
	TextDrawAlignment(Accessories[2], 1);
	TextDrawColor(Accessories[2], 623191551);
	TextDrawSetShadow(Accessories[2], 0);
	TextDrawSetOutline(Accessories[2], 0);
	TextDrawFont(Accessories[2], 4);
	TextDrawSetProportional(Accessories[2], 1);

	Accessories[3] = TextDrawCreateEx(263.499969, 390.499938, "LD_SPAC:white");
	TextDrawLetterSize(Accessories[3], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[3], 121.666656, 47.288875);
	TextDrawAlignment(Accessories[3], 1);
	TextDrawColor(Accessories[3], 623191551);
	TextDrawSetShadow(Accessories[3], 0);
	TextDrawSetOutline(Accessories[3], 0);
	TextDrawFont(Accessories[3], 4);
	TextDrawSetProportional(Accessories[3], 1);

	Accessories[4] = TextDrawCreateEx(261.666717, 432.288879, "LD_BEAT:chit");
	TextDrawLetterSize(Accessories[4], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[4], 10.666669, 12.859247);
	TextDrawAlignment(Accessories[4], 1);
	TextDrawColor(Accessories[4], 623191551);
	TextDrawSetShadow(Accessories[4], 0);
	TextDrawSetOutline(Accessories[4], 0);
	TextDrawFont(Accessories[4], 4);
	TextDrawSetProportional(Accessories[4], 1);

	Accessories[5] = TextDrawCreateEx(376.333435, 432.203674, "LD_BEAT:chit");
	TextDrawLetterSize(Accessories[5], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[5], 10.666669, 12.859247);
	TextDrawAlignment(Accessories[5], 1);
	TextDrawColor(Accessories[5], 623191551);
	TextDrawSetShadow(Accessories[5], 0);
	TextDrawSetOutline(Accessories[5], 0);
	TextDrawFont(Accessories[5], 4);
	TextDrawSetProportional(Accessories[5], 1);

	Accessories[6] = TextDrawCreateEx(267.166656, 433.970275, "LD_SPAC:white");
	TextDrawLetterSize(Accessories[6], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[6], 115.000000, 8.711107);
	TextDrawAlignment(Accessories[6], 1);
	TextDrawColor(Accessories[6], 623191551);
	TextDrawSetShadow(Accessories[6], 0);
	TextDrawSetOutline(Accessories[6], 0);
	TextDrawFont(Accessories[6], 4);
	TextDrawSetProportional(Accessories[6], 1);

	Accessories[7] = TextDrawCreateEx(281.333374, 401.955627, "<<<");
	TextDrawLetterSize(Accessories[7], 0.264333, 1.537776);
	TextDrawTextSize(Accessories[7], 10.000000, 23.000000);
	TextDrawAlignment(Accessories[7], 2);
	TextDrawColor(Accessories[7], -1);
	TextDrawUseBox(Accessories[7], 1);
	TextDrawBoxColor(Accessories[7], 8978176);
	TextDrawSetShadow(Accessories[7], 0);
	TextDrawSetOutline(Accessories[7], 0);
	TextDrawBackgroundColor(Accessories[7], 51);
	TextDrawFont(Accessories[7], 3);
	TextDrawSetProportional(Accessories[7], 1);
	TextDrawSetSelectable(Accessories[7], 1);

	Accessories[8] = TextDrawCreateEx(367.833374, 401.955627, ">>>");
	TextDrawLetterSize(Accessories[8], 0.264333, 1.537776);
	TextDrawTextSize(Accessories[8], 10.000000, 23.000000);
	TextDrawAlignment(Accessories[8], 2);
	TextDrawColor(Accessories[8], -1);
	TextDrawUseBox(Accessories[8], 1);
	TextDrawBoxColor(Accessories[8], 8978176);
	TextDrawSetShadow(Accessories[8], 0);
	TextDrawSetOutline(Accessories[8], 0);
	TextDrawBackgroundColor(Accessories[8], 51);
	TextDrawFont(Accessories[8], 3);
	TextDrawSetProportional(Accessories[8], 1);
	TextDrawSetSelectable(Accessories[8], 1);

	Accessories[9] = TextDrawCreateEx(266.166748, 420.622253, "LD_BEAT:chit");
	TextDrawLetterSize(Accessories[9], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[9], 13.000000, 19.496290);
	TextDrawAlignment(Accessories[9], 1);
	TextDrawColor(Accessories[9], 8978431);
	TextDrawSetShadow(Accessories[9], 0);
	TextDrawSetOutline(Accessories[9], 0);
	TextDrawFont(Accessories[9], 4);
	TextDrawSetProportional(Accessories[9], 1);

	Accessories[10] = TextDrawCreateEx(273.000000, 423.855560, "LD_SPAC:white");
	TextDrawLetterSize(Accessories[10], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[10], 28.333343, 13.274065);
	TextDrawAlignment(Accessories[10], 1);
	TextDrawColor(Accessories[10], 8978431);
	TextDrawSetShadow(Accessories[10], 0);
	TextDrawSetOutline(Accessories[10], 0);
	TextDrawFont(Accessories[10], 4);
	TextDrawSetProportional(Accessories[10], 1);

	Accessories[11] = TextDrawCreateEx(294.833404, 420.622222, "LD_BEAT:chit");
	TextDrawLetterSize(Accessories[11], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[11], 13.000000, 19.496290);
	TextDrawAlignment(Accessories[11], 1);
	TextDrawColor(Accessories[11], 8978431);
	TextDrawSetShadow(Accessories[11], 0);
	TextDrawSetOutline(Accessories[11], 0);
	TextDrawFont(Accessories[11], 4);
	TextDrawSetProportional(Accessories[11], 1);

	Accessories[12] = TextDrawCreateEx(368.499969, 420.622222, "LD_BEAT:chit");
	TextDrawLetterSize(Accessories[12], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[12], 13.000000, 19.496290);
	TextDrawAlignment(Accessories[12], 1);
	TextDrawColor(Accessories[12], 8978431);
	TextDrawSetShadow(Accessories[12], 0);
	TextDrawSetOutline(Accessories[12], 0);
	TextDrawFont(Accessories[12], 4);
	TextDrawSetProportional(Accessories[12], 1);

	Accessories[13] = TextDrawCreateEx(347.000030, 423.855529, "LD_SPAC:white");
	TextDrawLetterSize(Accessories[13], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[13], 28.333343, 13.274065);
	TextDrawAlignment(Accessories[13], 1);
	TextDrawColor(Accessories[13], 8978431);
	TextDrawSetShadow(Accessories[13], 0);
	TextDrawSetOutline(Accessories[13], 0);
	TextDrawFont(Accessories[13], 4);
	TextDrawSetProportional(Accessories[13], 1);

	Accessories[14] = TextDrawCreateEx(340.166656, 420.622161, "LD_BEAT:chit");
	TextDrawLetterSize(Accessories[14], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[14], 13.000000, 19.496290);
	TextDrawAlignment(Accessories[14], 1);
	TextDrawColor(Accessories[14], 8978431);
	TextDrawSetShadow(Accessories[14], 0);
	TextDrawSetOutline(Accessories[14], 0);
	TextDrawFont(Accessories[14], 4);
	TextDrawSetProportional(Accessories[14], 1);

	Accessories[15] = TextDrawCreateEx(287.333374, 424.355621, "EXIT");
	TextDrawLetterSize(Accessories[15], 0.259333, 1.346961);
	TextDrawTextSize(Accessories[15], 10.000000, 38.000000);
	TextDrawAlignment(Accessories[15], 2);
	TextDrawColor(Accessories[15], 623191551);
	TextDrawUseBox(Accessories[15], 1);
	TextDrawBoxColor(Accessories[15], 8978176);
	TextDrawSetShadow(Accessories[15], 0);
	TextDrawSetOutline(Accessories[15], 0);
	TextDrawBackgroundColor(Accessories[15], 51);
	TextDrawFont(Accessories[15], 1);
	TextDrawSetProportional(Accessories[15], 1);
	TextDrawSetSelectable(Accessories[15], 1);

	Accessories[16] = TextDrawCreateEx(361.666778, 423.940765, "BUY");
	TextDrawLetterSize(Accessories[16], 0.259333, 1.346961);
	TextDrawTextSize(Accessories[16], 10.000000, 38.000000);
	TextDrawAlignment(Accessories[16], 2);
	TextDrawColor(Accessories[16], 623191551);
	TextDrawUseBox(Accessories[16], 1);
	TextDrawBoxColor(Accessories[16], 8978176);
	TextDrawSetShadow(Accessories[16], 0);
	TextDrawSetOutline(Accessories[16], 0);
	TextDrawBackgroundColor(Accessories[16], 51);
	TextDrawFont(Accessories[16], 1);
	TextDrawSetProportional(Accessories[16], 1);
	TextDrawSetSelectable(Accessories[16], 1);

	Accessories[17] = TextDrawCreateEx(298.166748, 407.314910, "LD_BEAT:chit");
	TextDrawLetterSize(Accessories[17], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[17], 2.333338, 3.318505);
	TextDrawAlignment(Accessories[17], 1);
	TextDrawColor(Accessories[17], 8978431);
	TextDrawSetShadow(Accessories[17], 0);
	TextDrawSetOutline(Accessories[17], 0);
	TextDrawFont(Accessories[17], 4);
	TextDrawSetProportional(Accessories[17], 1);

	Accessories[18] = TextDrawCreateEx(348.166748, 407.314910, "LD_BEAT:chit");
	TextDrawLetterSize(Accessories[18], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[18], 2.333338, 3.318505);
	TextDrawAlignment(Accessories[18], 1);
	TextDrawColor(Accessories[18], 8978431);
	TextDrawSetShadow(Accessories[18], 0);
	TextDrawSetOutline(Accessories[18], 0);
	TextDrawFont(Accessories[18], 4);
	TextDrawSetProportional(Accessories[18], 1);

	Accessories[19] = TextDrawCreateEx(300.000061, 408.144439, "LD_SPAC:white");
	TextDrawLetterSize(Accessories[19], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[19], 49.333332, 2.074054);
	TextDrawAlignment(Accessories[19], 1);
	TextDrawColor(Accessories[19], 8978431);
	TextDrawSetShadow(Accessories[19], 0);
	TextDrawSetOutline(Accessories[19], 0);
	TextDrawFont(Accessories[19], 4);
	TextDrawSetProportional(Accessories[19], 1);

	Accessories[20] = TextDrawCreateEx(344.833374, 410.570465, "LD_BEAT:chit");
	TextDrawLetterSize(Accessories[20], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[20], 2.333338, 3.318505);
	TextDrawAlignment(Accessories[20], 1);
	TextDrawColor(Accessories[20], -1);
	TextDrawSetShadow(Accessories[20], 0);
	TextDrawSetOutline(Accessories[20], 0);
	TextDrawFont(Accessories[20], 4);
	TextDrawSetProportional(Accessories[20], 1);

	Accessories[21] = TextDrawCreateEx(301.500030, 410.570526, "LD_BEAT:chit");
	TextDrawLetterSize(Accessories[21], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[21], 2.333338, 3.318505);
	TextDrawAlignment(Accessories[21], 1);
	TextDrawColor(Accessories[21], -1);
	TextDrawSetShadow(Accessories[21], 0);
	TextDrawSetOutline(Accessories[21], 0);
	TextDrawFont(Accessories[21], 4);
	TextDrawSetProportional(Accessories[21], 1);

	Accessories[22] = TextDrawCreateEx(303.000091, 411.207397, "LD_SPAC:white");
	TextDrawLetterSize(Accessories[22], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[22], 42.999988, 2.074054);
	TextDrawAlignment(Accessories[22], 1);
	TextDrawColor(Accessories[22], -1);
	TextDrawSetShadow(Accessories[22], 0);
	TextDrawSetOutline(Accessories[22], 0);
	TextDrawFont(Accessories[22], 4);
	TextDrawSetProportional(Accessories[22], 1);

	Accessories[23] = TextDrawCreateEx(242.499984, 379.970397, "LD_BEAT:chit");
	TextDrawLetterSize(Accessories[23], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[23], 10.666668, 12.859247);
	TextDrawAlignment(Accessories[23], 1);
	TextDrawColor(Accessories[23], 8978431);
	TextDrawSetShadow(Accessories[23], 0);
	TextDrawSetOutline(Accessories[23], 0);
	TextDrawFont(Accessories[23], 4);
	TextDrawSetProportional(Accessories[23], 1);

	Accessories[24] = TextDrawCreateEx(249.000015, 382.459259, "LD_SPAC:white");
	TextDrawLetterSize(Accessories[24], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[24], 45.333309, 8.296299);
	TextDrawAlignment(Accessories[24], 1);
	TextDrawColor(Accessories[24], 8978431);
	TextDrawSetShadow(Accessories[24], 0);
	TextDrawSetOutline(Accessories[24], 0);
	TextDrawFont(Accessories[24], 4);
	TextDrawSetProportional(Accessories[24], 1);

	Accessories[25] = TextDrawCreateEx(290.000000, 379.970397, "LD_BEAT:chit");
	TextDrawLetterSize(Accessories[25], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[25], 10.666669, 12.859247);
	TextDrawAlignment(Accessories[25], 1);
	TextDrawColor(Accessories[25], 8978431);
	TextDrawSetShadow(Accessories[25], 0);
	TextDrawSetOutline(Accessories[25], 0);
	TextDrawFont(Accessories[25], 4);
	TextDrawSetProportional(Accessories[25], 1);

	Accessories[26] = TextDrawCreateEx(261.499938, 372.088836, "LD_BEAT:chit");
	TextDrawLetterSize(Accessories[26], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[26], 7.333334, 9.125909);
	TextDrawAlignment(Accessories[26], 1);
	TextDrawColor(Accessories[26], -1);
	TextDrawSetShadow(Accessories[26], 0);
	TextDrawSetOutline(Accessories[26], 0);
	TextDrawFont(Accessories[26], 4);
	TextDrawSetProportional(Accessories[26], 1);

	Accessories[27] = TextDrawCreateEx(265.666687, 373.748168, "LD_SPAC:white");
	TextDrawLetterSize(Accessories[27], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[27], 36.999980, 6.222249);
	TextDrawAlignment(Accessories[27], 1);
	TextDrawColor(Accessories[27], -1);
	TextDrawSetShadow(Accessories[27], 0);
	TextDrawSetOutline(Accessories[27], 0);
	TextDrawFont(Accessories[27], 4);
	TextDrawSetProportional(Accessories[27], 1);

	Accessories[28] = TextDrawCreateEx(298.833160, 372.088836, "LD_BEAT:chit");
	TextDrawLetterSize(Accessories[28], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[28], 7.333335, 9.125910);
	TextDrawAlignment(Accessories[28], 1);
	TextDrawColor(Accessories[28], -1);
	TextDrawSetShadow(Accessories[28], 0);
	TextDrawSetOutline(Accessories[28], 0);
	TextDrawFont(Accessories[28], 4);
	TextDrawSetProportional(Accessories[28], 1);

	Accessories[29] = TextDrawCreateEx(383.833465, 380.722229, "LD_BEAT:chit");
	TextDrawLetterSize(Accessories[29], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[29], 2.333338, 3.318505);
	TextDrawAlignment(Accessories[29], 1);
	TextDrawColor(Accessories[29], 8978431);
	TextDrawSetShadow(Accessories[29], 0);
	TextDrawSetOutline(Accessories[29], 0);
	TextDrawFont(Accessories[29], 4);
	TextDrawSetProportional(Accessories[29], 1);

	Accessories[30] = TextDrawCreateEx(384.333343, 382.329620, "LD_SPAC:white");
	TextDrawLetterSize(Accessories[30], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[30], 1.666656, 54.340744);
	TextDrawAlignment(Accessories[30], 1);
	TextDrawColor(Accessories[30], 8978431);
	TextDrawSetShadow(Accessories[30], 0);
	TextDrawSetOutline(Accessories[30], 0);
	TextDrawFont(Accessories[30], 4);
	TextDrawSetProportional(Accessories[30], 1);

	Accessories[31] = TextDrawCreateEx(383.833526, 434.277832, "LD_BEAT:chit");
	TextDrawLetterSize(Accessories[31], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[31], 2.333338, 3.318505);
	TextDrawAlignment(Accessories[31], 1);
	TextDrawColor(Accessories[31], 8978431);
	TextDrawSetShadow(Accessories[31], 0);
	TextDrawSetOutline(Accessories[31], 0);
	TextDrawFont(Accessories[31], 4);
	TextDrawSetProportional(Accessories[31], 1);

	Accessories[32] = TextDrawCreateEx(388.666625, 404.729583, "LD_SPAC:white");
	TextDrawLetterSize(Accessories[32], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[32], 1.666656, 37.333351);
	TextDrawAlignment(Accessories[32], 1);
	TextDrawColor(Accessories[32], -1);
	TextDrawSetShadow(Accessories[32], 0);
	TextDrawSetOutline(Accessories[32], 0);
	TextDrawFont(Accessories[32], 4);
	TextDrawSetProportional(Accessories[32], 1);

	Accessories[33] = TextDrawCreateEx(388.166900, 440.500000, "LD_BEAT:chit");
	TextDrawLetterSize(Accessories[33], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[33], 2.333338, 3.318505);
	TextDrawAlignment(Accessories[33], 1);
	TextDrawColor(Accessories[33], -1);
	TextDrawSetShadow(Accessories[33], 0);
	TextDrawSetOutline(Accessories[33], 0);
	TextDrawFont(Accessories[33], 4);
	TextDrawSetProportional(Accessories[33], 1);

	Accessories[34] = TextDrawCreateEx(388.166870, 402.337066, "LD_BEAT:chit");
	TextDrawLetterSize(Accessories[34], 0.000000, 0.000000);
	TextDrawTextSize(Accessories[34], 2.333338, 3.318505);
	TextDrawAlignment(Accessories[34], 1);
	TextDrawColor(Accessories[34], -1);
	TextDrawSetShadow(Accessories[34], 0);
	TextDrawSetOutline(Accessories[34], 0);
	TextDrawFont(Accessories[34], 4);
	TextDrawSetProportional(Accessories[34], 1);
}

stock LoadAccPTD(playerid)
{
	AccessoriesP[playerid] = CreatePlayerTextDrawEx(playerid, 302.333465, 392.414764, "$100000");
	PlayerTextDrawLetterSize(playerid, AccessoriesP[playerid], 0.342332, 1.653926);
	PlayerTextDrawAlignment(playerid, AccessoriesP[playerid], 1);
	PlayerTextDrawColor(playerid, AccessoriesP[playerid], 8978431);
	PlayerTextDrawSetShadow(playerid, AccessoriesP[playerid], 0);
	PlayerTextDrawSetOutline(playerid, AccessoriesP[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, AccessoriesP[playerid], 51);
	PlayerTextDrawFont(playerid, AccessoriesP[playerid], 1);
	PlayerTextDrawSetProportional(playerid, AccessoriesP[playerid], 1);
}


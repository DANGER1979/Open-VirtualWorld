//��� �����������


stock cardealer_OnPlayerPickUp(playerid, pickupid)
{
 	#pragma unused pickupid
	//--------------------------------------------------------------------------
	if( IsPlayerInRangeOfPoint(playerid, 2.1, -1663.8074,1207.7589,7.2546)//AutoSalon
		|| IsPlayerInRangeOfPoint(playerid, 2.1, 415.6489,2533.6672,19.1484)
		|| IsPlayerInRangeOfPoint(playerid, 2.1, 718.5229,-1476.4646,5.4688) )
	{   //��� ������� ����
	    if(Counter3DText >= MAX_3DTEXT_GLOBAL)
	    {
	        SendClientMessage(playerid, COLOR_GREY, "   ���-�� ������� ���������� �� ������� �������� ���������!");
			return 1;
		}
	    if(GetMaxVehicles >= MAX_VEHICLES-1-sizeof(AdminCars))
	    {
	        SendClientMessage(playerid, COLOR_GREY, "   ���-�� ���������� �������� ���������!");
			return 1;
		}
       	if(IsPlayerInAnyVehicle(playerid))
		{
			SendClientMessage(playerid, COLOR_GREY, "  �� �� ������ ���������� � ������������ ��������!");
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
			//format(strings, sizeof(strings), "  ������� ������������ ������� �������������� ������ ��� ���������� �����������! ��������� � %s[%d]", PlayerName(giveplayerid), giveplayerid);
			SendClientMessage(playerid, COLOR_GREY, "  ������� ������������ ������� �������������� ������ ��� ���������� ����������� (USE: /cardealer) !");
			return 1;
		}
       	if(numplayers > (GetMaxPlayers()/2) && PlayerInfo[playerid][pLevel] > 3 && !gRealWar)
		{
			format(strings, sizeof(strings), "  ������� ������������ ������� �������������� ��� ������� ������ %d !", (GetMaxPlayers()/2));
			SendClientMessage(playerid, COLOR_GREY, strings);
			return 1;
		}
		//new msgitem[218+32+3+10+6+3+6+3 + 12];
		/*ShowPlayerDialogGap(playerid, 66, DIALOG_STYLE_INPUT, "AutoSalon",
			"���������� ������� ������ ���������� \n� ������� BUY. \n��� ��������� �������� ���������� ������� /carinfo",
			"BUY", "Cancel");*/
		//if(DialogID[playerid][0] != 66)
		//{//����� ��������� ��� ������� ������ �� ���������������� MenuOperation[playerid] = 136;
		DialogID[playerid][0] = AutoSalon_DIALOG;
		CarInfo(playerid);
		//}
		//return 1;
	}
	return 1;
}

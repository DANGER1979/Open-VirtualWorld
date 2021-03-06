
//##############################################################################//
//                                                                              //
//                             ������� ������ ����                             //
//                                                                              //
//##############################################################################//

stock RentMyCar_STATE_DRIVER(playerid, vehicleid)//��� ������� ����
{   //���������� �� newstate == PLAYER_STATE_DRIVER
	new sb;
	if(vehicleid >= RentCar[0] && vehicleid <= RentCar[2])
	{   //Car Renting
		sb = 0;
	}
	else if(vehicleid >= RentCar[3] && vehicleid <= RentCar[5])
	{   //Wang Cars
		sb = 1;
	}
	else if(vehicleid >= RentCar[6] && vehicleid <= RentCar[11])
	{   //��� ���������
		sb = 11;
	}
	else return 1;

	if(HireCarID[playerid] == vehicleid) return 1;
	CarPrice[playerid] = 0;//��� �����������

	if(SBizInfo[sb][sbOwned] == 0) CarPrice[playerid] = HireCost(vehicleid);//�������� ���� ������������ �����
	else CarPrice[playerid] = SBizInfo[sb][sbEntranceCost];
	//format(strings, sizeof(strings), "~w~You can Rent this car~n~Cost:~g~$%d~n~~w~To rent type ~g~/rentcar~w~~n~to get out type ~r~/exit",
	//	CarPrice[playerid]);
	//GameTextForPlayerEx(playerid, strings, 5000, 3);
	//-------------------------------------------------------------------------*
	//new money = floatround( VehicleArray[nCarModel[playerid]-400][Virtual_Price]*SBizInfo[sb][sbSellProd]/100.0);//30% ��������� �����
	if(PlayerInfo[playerid][pBank] < CarPrice[playerid] && GetPlayerMoneyH(playerid) < CarPrice[playerid])
	{
	    SendClientMessage(playerid, COLOR_GREY, "   � ��� ��� ���� ����� ����� !");
	    RemovePlayerFromVehicleEx(playerid);
		return 1;
	}
	//CarPrice[playerid] = money;
	SetPVarInt(playerid, "BizID", sb);

	TogglePlayerControllableEx(playerid, 0);//������������� ����� �� ����� ���������
	new msgitem[458];//290 + 32+10+10+28+28 + 60�=�458
	format(msgitem, sizeof(msgitem), "{0080FF}* �� ������ ���������� ���� {FFFFFF}%s\
\n{0080FF}����������: {33AA33}$%d.\
\n\n{AFAFAF}������� Accept, ����� �������.",
		VehicleArray[nCarModel[playerid]-400][Vehicle_Name], CarPrice[playerid]);
	new strtmp[37+24];
	format(strtmp, sizeof(strtmp), "������ ���������� �� %s's", SBizInfo[sb][sbOwner]);
	MenuOperation[playerid] = 27;
	ShowPlayerDialogGap(playerid, RENTCAR_DIALOG, DIALOG_STYLE_MSGBOX, strtmp, msgitem, "Accept", "Exit");
	return 1;
}

stock RentCar_STATE_DRIVER(playerid, vehicleid)//��� ������� ����
{   //���������� �� newstate == PLAYER_STATE_DRIVER
	new sb;
	if(vehicleid >= RentCar[0] && vehicleid <= RentCar[2])
	{   //Car Renting
		sb = 0;
	}
	else if(vehicleid >= RentCar[3] && vehicleid <= RentCar[5])
	{   //Wang Cars
		sb = 1;
	}
	else if(vehicleid >= RentCar[6] && vehicleid <= RentCar[11])
	{   //��� ���������
		sb = 11;
	}
	else return 1;

	if(HireCarID[playerid] == vehicleid) return 1;
	CarPrice[playerid] = 0;//��� �����������

	if(SBizInfo[sb][sbOwned] == 0) CarPrice[playerid] = HireCost(vehicleid);//�������� ���� ������������ �����
	else CarPrice[playerid] = SBizInfo[sb][sbEntranceCost];
	//format(strings, sizeof(strings), "~w~You can Rent this car~n~Cost:~g~$%d~n~~w~To rent type ~g~/rentcar~w~~n~to get out type ~r~/exit",
	//	CarPrice[playerid]);
	//GameTextForPlayerEx(playerid, strings, 5000, 3);
	//-------------------------------------------------------------------------*
	//new money = floatround( VehicleArray[nCarModel[playerid]-400][Virtual_Price]*SBizInfo[sb][sbSellProd]/100.0);//30% ��������� �����
	if(PlayerInfo[playerid][pBank] < CarPrice[playerid] && GetPlayerMoneyH(playerid) < CarPrice[playerid])
	{
	    SendClientMessage(playerid, COLOR_GREY, "   � ��� ��� ���� ����� ����� !");
	    RemovePlayerFromVehicleEx(playerid);
		return 1;
	}
	//CarPrice[playerid] = money;
	SetPVarInt(playerid, "BizID", sb);

	TogglePlayerControllableEx(playerid, 0);//������������� ����� �� ����� ���������
	new msgitem[458];//290 + 32+10+10+28+28 + 60�=�458
	format(msgitem, sizeof(msgitem), "{0080FF}* �� ������ ���������� ���� {FFFFFF}%s\
\n{0080FF}����������: {33AA33}$%d.\
\n\n{AFAFAF}������� Accept, ����� �������.",
		VehicleArray[nCarModel[playerid]-400][Vehicle_Name], CarPrice[playerid]);
	new strtmp[37+24];
	format(strtmp, sizeof(strtmp), "������ ���������� �� %s's", SBizInfo[sb][sbOwner]);
	MenuOperation[playerid] = 27;
	ShowPlayerDialogGap(playerid, RENTCAR_DIALOG, DIALOG_STYLE_MSGBOX, strtmp, msgitem, "Accept", "Exit");
	return 1;
}


stock RentCar_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{   //dialogid  - ������ �� ������� ������
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != RENTCAR_DIALOG) return 1;

	if(MenuOperation[playerid] != 27) return 1;
	if(!gLoading[playerid] && !gUnLoading[playerid])
	{
		TogglePlayerControllableEx(playerid, 1);//�������������
	}

	new msgitem[256+1];
	if(!response)
	{
		iOfferTime[Offer[playerid]] = GetTickCount();
		iOfferTime[playerid] = GetTickCount();
		RemovePlayerFromVehicleEx(playerid);
		//removePlayerFromVehicle(playerid);

		Offer[playerid] = MAX_PLAYERS-1;
		CarPrice[playerid] = 0;

		format(msgitem, sizeof(msgitem), "%s ��������� �� ������ ���������� !", PlayerName(playerid));
		ProxDetector(playerid, 30.0, msgitem, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);

		MenuOperation[playerid] = 0;
		return 1;
	}

//��� ������� ���� //��� ������� ���� �� ��������
	if(CurState[playerid] != PLAYER_STATE_DRIVER)
	{
		RemovePlayerFromVehicleEx(playerid);
        Offer[playerid] = MAX_PLAYERS-1;
		CarPrice[playerid] = 0;
		MenuOperation[playerid] = 0;
		SendClientMessage(playerid, COLOR_GREY, "  �� ������ ���������� �� ������������ �������!");
		return 1;
	}
	//�������� ������ �� �����, �.�. ����� ����� ���� ��� ��� �� ���� ��� �� � ������ �����
	nCarID[playerid] = GetPlayerVehicleID(playerid);
	nCarModel[playerid] = GetVehicleModel(nCarID[playerid]);
	if( !IsInRentCar(nCarID[playerid]) ) { RemovePlayerFromVehicleEx(playerid); return 1; }
	new sb = GetPVarInt(playerid, "BizID");

	if(HireCarID[playerid] < MAX_VEHICLES-1)
	{
	    SendClientMessage(playerid, COLOR_GREY, "   � ��� ��� ���� ������������ ���������� (USE: /cancel rentcar)");
		TogglePlayerControllableEx(playerid, 1);
		RemovePlayerFromVehicleEx(playerid);
		return 1;
	}
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
	    if( !IsPlayerConnectedEx(i) ) continue;
		if(nCarID[playerid] == HireCarID[i])
	    {
		    format(msgitem, sizeof(msgitem), "RentCarID: %d ��� ��������� !", nCarID[playerid]);
		    SendClientMessage(playerid, COLOR_GREY, msgitem);
			TogglePlayerControllableEx(playerid, 1);
			RemovePlayerFromVehicleEx(playerid);
			return 1;
	    }
	}
	//new hirefee = HireCost(nCarID[playerid]);//�������� ���� ������������ �����

	if(SBizInfo[sb][sbProducts] <= 0 && !gRealWar)
	{
		GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Car Renting", 5000, 1);
		PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
		RemovePlayerFromVehicleEx(playerid);
		return 1;
	}
	//��� �������� ����������� ������
	new sbouse = NOT_KEY, found;
	for(new limit = 0; limit < 20; limit++)
	{
		if(MyCompany[playerid][limit] == NOT_KEY) continue;
		sbouse = MyCompany[playerid][limit];
		if(sbouse == sb) { found = 1; break; }
	}
	if(found)//if(PlayerInfo[playerid][pBizz] == (sb+100) )
	{
		GameTextForPlayerEx(playerid, "~w~No charge for the boss", 5000, 3);//��������� ��� �����
		TogglePlayerControllableEx(playerid, 1);
		return 1;
	}
	if(PlayerInfo[playerid][pBank] > CarPrice[playerid])
	{
		GivePlayerMoneyB(fsbiz+sb, playerid, -CarPrice[playerid]);
	}
	else if(GetPlayerMoneyH(playerid) > CarPrice[playerid])
	{
		GivePlayerMoneyH(fsbiz+sb, playerid, -CarPrice[playerid]);
	}
	else
	{
        Offer[playerid] = MAX_PLAYERS-1;
		CarPrice[playerid] = 0;
		MenuOperation[playerid] = 0;
	    SendClientMessage(playerid, COLOR_GREY, "   � ��� ��� ���� ����� ����� !");
	    RemovePlayerFromVehicleEx(playerid);
		return 1;
	}
	//new hirefee = HireCost(GetPlayerVehicleID(playerid));//�������� ���� ������������ �����
	if(SBizInfo[sb][sbOwned] == 0)
	{   //���� ��� ��������� �� ������ ����������� � ��� ���� �����
		//GivePlayerMoneyH(fsbiz+sb, playerid, -CarPrice[playerid]);
		OnGangsExtortionSBiz(sb, CarPrice[playerid]);
	}
	else//����� ����������� � ��� ������������� ��������� ����������
	{
		//GivePlayerMoneyH(fsbiz+sb, playerid, -SBizInfo[sb][sbEntranceCost]);
		OnGangsExtortionSBiz(sb, CarPrice[playerid]);//SBizInfo[sb][sbEntranceCost]);
	}
	SBizInfo[sb][sbProducts] --;
	//--------------------------------------------------------------
	HireCarID[playerid] = nCarID[playerid];
	//�������� � ���������� HireCarID ID ������ � ������ �� ��� �� �������������� �
	TogglePlayerControllableEx(playerid, 1);//����������� ������ ����� ���������
	format(msgitem, sizeof(msgitem), "* �� ���������� ��������� � %s's �� ���� {33AA33}$%d",
		SBizInfo[sb][sbOwner], CarPrice[playerid]);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
	SendClientMessage(playerid, COLOR_GREY, "���������� �� ������ ����(USE: /cancel rentcar)");

	Offer[playerid] = ReturnUser(SBizInfo[sb][sbOwner]);
    if( IsPlayerConnectedEx(Offer[playerid]) )
	{
		format(msgitem, sizeof(msgitem), "* %s ��������� � ��� ��������� �� ���� $%d. ����� ����������� �� ���� ����� ��������.",
			PlayerName(playerid),CarPrice[playerid]);
		SendClientMessage(Offer[playerid], COLOR_LIGHTBLUE, msgitem);
	}
	Offer[playerid] = MAX_PLAYERS-1;
	CarPrice[playerid] = 0;
	MenuOperation[playerid] = 0;
	//TogglePlayerControllableEx(playerid, 1);//����������� ������ ����� ���������
	return 1;
}


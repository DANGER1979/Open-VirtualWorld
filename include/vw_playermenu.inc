

//##############################################################################//
//                                                                              //
//                                  ���� ������                                 //
//                                                                              //
//##############################################################################//
stock PlayerMenu(playerid)
{
	new bigmsgitem[] = "{FFFFFF}1\t{00FF00}����������\
\n{FFFFFF}2\t{00FF00}���������\
\n{FFFFFF}3\t{00FF00}������\
\n{FFFFFF}4\t{00FF00}���������\
\n{FFFFFF}5\t{00FF00}������������\
\n{FFFFFF}6\t{00FF00}���������\
\n{FFFFFF}7\t{00FF00}����� ������";
/*
�������������\
\n������������� �� �����\
\n�������� �������\
\n������� SMS\
\n��������� �� ��������\
\n�������� ������\
\n�������� ������\
\n�������� ��������\
\n�������� ���������\
\n�����������";
*/
//\n{FFFFFF}7\t{00FF00}����� � ��������������";
//\n{FFFFFF}7\t{00FF00}�������";
//\n{FFFFFF}9\t{00FF00}�������� ���";
	new caption[70];
	format(caption, sizeof(caption), "���� ������: %s[%d]", PlayerName(playerid), playerid);
	ShowPlayerDialogGap(playerid, PLMENU_DIALOG, DIALOG_STYLE_LIST, caption, bigmsgitem, "OK", "�����");
}
stock backPMenu_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])//������������� ������� ������ �����
{//���������� � ���� ������ ��� ������� ������ ����� ���� � ���� ������� ID: BACKPLMENU_DIALOG
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != BACKPLMENU_DIALOG) return 1;
	if(!response)
	{
		PlayerMenu(playerid);
		return 1;
	}
	PlaySoundForPlayer(playerid, 5202);
	return 1;
}

stock playermenu_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	backPMenu_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	tog_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	upgrade_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);

	if(dialogid != PLMENU_DIALOG) return 1;
	if(!response) {
		new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
		admin_OnPlayerClick(playerid, giveplayerid);//PlayerMenu(playerid);
		return 1;
	} //PlaySoundForPlayer(playerid, 5202);
	new strcmd[MAX_STRING];
	if(listitem == 0)//�������
	{//����������
    	SetPVarInt(playerid, "gDocuments", 1);
		OnPlayerShowStats(playerid, playerid);
	}
	else if(listitem == 1)
	{//���������
		Items(playerid);
	}
	else if(listitem == 2)
	{//������
		SkillInfo(playerid);
	}
	else if(listitem == 3)
	{ //���������
		PlayerUpgrade(playerid);
	}
	else if(listitem == 4)
	{//������������
		PropertyHelp(playerid);
	}
	else if(listitem == 5)
	{ //������ ���������
		TogHelp(playerid);
	}
	else if(listitem == 6)
	{ //��������� ������������
		if(GetPVarInt(playerid, "PasswordHasEdited") == getdate() && PlayerInfo[playerid][pAdmin] < 5)
		{
			format(strcmd, sizeof(strcmd), "CEPBEP: {33AA33}playerid:%d ��� ������� ���������� �������� ������. ������ ��� ����� ������ ������!", playerid);
			SendClientMessage(playerid, COLOR_RED, strcmd);
			return 1;
		}
		login_ChangePass(playerid);
	}
	return 1;
}
stock TogHelp(playerid)
{
	new listitems[545+8*13+22];

	strcat(listitems, "�������� ������ ���\n");

	if (!gPhoneOnline[playerid]) strcat(listitems, "/togphone - {FF0000}���� �������\n");
	else strcat(listitems, "/togphone - {00FF00}��� �������\n");

	if (!GetPVarInt(playerid, "gNews")) strcat(listitems, "/tognews - {FF0000}���� ��� ��������\n");
	else strcat(listitems, "/tognews - {00FF00}��� ��� ��������\n");

	if (!GetPVarInt(playerid, "gJob")) strcat(listitems, "/togjob{FF0000} - ���� ��������� ���������\n");
	else strcat(listitems, "/togjob{00FF00} - ��� ��������� ���������\n");

	if(!GetPVarInt(playerid, "gSport")) strcat(listitems, "/togsport - {FF0000}���� ���������� �������\n");
	else strcat(listitems, "/togsport - {00FF00}��� ���������� �������\n");

	if (!GetPVarInt(playerid, "gFam")) strcat(listitems, "/togfam - {FF0000}���� �������� �����\n");
	else strcat(listitems, "/togfam - {00FF00}��� �������� �����\n");

	if (!GetPVarInt(playerid, "gHidePM")) strcat(listitems, "/togpm - {FF0000}���� ������ ���������\n");
	else strcat(listitems, "/togpm - {00FF00}��� ������ ���������\n");

	if(!GetPVarInt(playerid, "gOoc")) strcat(listitems, "/togooc - {FF0000}���� ����� ���\n");
	else strcat(listitems, "/togooc - {00FF00}��� ����� ���\n");

	if(!GetPVarInt(playerid, "gSwitcher")) strcat(listitems, "/togSwitcher - {FF0000}���� ���������� ����� ���������\n");
	else strcat(listitems, "/togSwitcher - {00FF00}��� ���������� ����� ���������\n");

	if(TextDrawShowClock[playerid] == true) strcat(listitems, "/togtime - {FF0000}���� ���������� � ���� � �������\n");
	else strcat(listitems, "/togtime - {00FF00}��� ���������� � ���� � �������\n");

	if(TextDrawShowArmour[playerid] == true) strcat(listitems, "/toghp - {FF0000}���� ���������� � �������� � �����\n");
	else strcat(listitems, "/toghp - {00FF00}��� ���������� � �������� � �����\n");

	if(TextDrawShowMessage[playerid] == true) strcat(listitems, "/togsys - {FF0000}���� ��������� ������\n");
	else strcat(listitems, "/togsys - {00FF00}��� ��������� ������\n");

	if(!GetPVarInt(playerid, "gAdmin")) strcat(listitems, "/togadmin - {FF0000}���� ����� ���������\n");
	else strcat(listitems, "/togadmin - {00FF00}��� ����� ���������.\n");

	strcat(listitems, "/audiomsg - {FF0000}����/{00FF00}���{FFFFFF} ��������� � �����������\n");

	strcat(listitems, "/dl - {FF0000}����/{00FF00}���{FFFFFF} ���������� �� ����������");

	ShowPlayerDialogEx(playerid, TOG_DIALOG, DIALOG_STYLE_LIST, "������ ��������� - ������ ��������������", listitems, "OK", "�����");
}
stock tog_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if(dialogid != TOG_DIALOG) return 1;
	if(!response)
	{
		PlayerMenu(playerid);
		return 1;
	}
	if(listitem == 0)
	{
		for(new c = 0; c != 32; c++) SendClientMessage(playerid, -1, " ");
	}
	if(listitem == 1)
	{   //togphone
        /*if(PlayerInfo[playerid][pAdmin] < 1 && PlayerInfo[playerid][pAccount] == 0)
        {
            SendClientMessage(playerid, COLOR_GREY, "   �� �� ������������ ������������ ��� ������� !");
            return 1;
        }*/
		if(gPhoneOnline[playerid] == 0)
		{
			gPhoneOnline[playerid] = 1;
			SendClientMessage(playerid, COLOR_GREY, "   ��� ������� �������� !");
		}
		else
		{
			gPhoneOnline[playerid] = 0;
			SendClientMessage(playerid, COLOR_GREY, "   ��� ������� ������� !");
		}
	}
	else if(listitem == 2)
	{   //tognews
		if(GetPVarInt(playerid, "gNews") == 0)
		{
			SetPVarInt(playerid, "gNews", 1);
			SendClientMessage(playerid, COLOR_GREY, "   ����� �������� �������� !");
		}
		else
		{
			SetPVarInt(playerid, "gNews", 0);
			SendClientMessage(playerid, COLOR_GREY, "   ����� �������� ������� !");
		}
	}
	else if(listitem == 3)
	{   //togjob
		if(GetPVarInt(playerid, "gJob") == 0)
		{
			SetPVarInt(playerid, "gJob", 1);
			SendClientMessage(playerid, COLOR_GREY, "   ������� ��������� ��������� !");
		}
		else
		{
			SetPVarInt(playerid, "gJob", 0);
			SendClientMessage(playerid, COLOR_GREY, "   ������� ��������� �������� !");
		}
	}
	else if(listitem == 4)
	{   //togsport
		if(GetPVarInt(playerid, "gSport") == 0)
		{
			SetPVarInt(playerid, "gSport", 1);
			SendClientMessage(playerid, COLOR_GREY, "   C��������� ������� ��������� !");
		}
		else
		{
			SetPVarInt(playerid, "gSport", 0);
			SendClientMessage(playerid, COLOR_GREY, "   C��������� ������� �������� !");
		}
	}
	else if(listitem == 5)
	{   //togfam
		if(GetPVarInt(playerid, "gFam") == 0)
		{
			SetPVarInt(playerid, "gFam", 1);
			SendClientMessage(playerid, COLOR_GREY, "   �������� ��� �������� !");
		}
		else
		{
			SetPVarInt(playerid, "gFam", 0);
			SendClientMessage(playerid, COLOR_GREY, "   �������� ��� ������� !");
		}
	}
	else if(listitem == 6)
	{   //togpm
		if(GetPVarInt(playerid, "gHidePM") == 0)
		{
			SetPVarInt(playerid, "gHidePM", 1);
			SendClientMessage(playerid, COLOR_GREY, "   Whisper chat channel Disabled !");
		}
		else
		{
			SetPVarInt(playerid, "gHidePM", 0);
			SendClientMessage(playerid, COLOR_GREY, "   Whisper chat channel Enabled !");
		}
	}
	else if(listitem == 7)
	{   //togooc
		if(GetPVarInt(playerid, "gOoc") == 0)
		{
			SetPVarInt(playerid, "gOoc", 1);
			SendClientMessage(playerid, COLOR_GREY, "   ����� ��� �������� !");
		}
		else
		{
			SetPVarInt(playerid, "gOoc", 0);
			SendClientMessage(playerid, COLOR_GREY, "   ����� ��� ������� !");
		}
	}
	else if(listitem == 8)
	{   //togswitcher
		if(GetPVarInt(playerid, "gSwitcher") == 0)
		{
			SetPVarInt(playerid, "gSwitcher", 1);
			SendClientMessage(playerid, COLOR_GREY, "   ���������� ����� ��������� �������� !");
		}
		else
		{
			SetPVarInt(playerid, "gSwitcher", 0);
			SendClientMessage(playerid, COLOR_GREY, "    ���������� ����� ��������� ������� !");
		}
	}
	else if(listitem == 9)
	{   ///togtime
		if(TextDrawShowClock[playerid] == true)
		{
			TextDrawHideForPlayer(playerid, txdTimeDisp);//��� �������
			//TextDrawHideForPlayer(playerid, txdSecondsTime);
			TextDrawHideForPlayer(playerid, txdDate);
			//TextDrawHideForPlayer(playerid, txtServerName);

			PlayerTextDrawHide(playerid, txdBankDisp[playerid]);
			PlayerTextDrawHide(playerid, txdPlayerHealth[playerid]);

			PlayerTextDrawHide(playerid, txdSecondsTime[playerid]);
			PlayerTextDrawHide(playerid, txdPlayerZone[playerid]);
			PlayerTextDrawHide(playerid, txdPlayerRegion[playerid]);
		
			TextDrawShowClock[playerid] = false;
			SendClientMessage(playerid, COLOR_GREY, "   ���������� ���� � ������� ������ !");
		}
		else
		{
			TextDrawShowForPlayer(playerid, txdTimeDisp);//��� �������
			//TextDrawShowForPlayer(playerid, txdSecondsTime);
			TextDrawShowForPlayer(playerid, txdDate);
			//TextDrawShowForPlayer(playerid, txtServerName);

			PlayerTextDrawShow(playerid, txdBankDisp[playerid]);
			//PlayerTextDrawShow(playerid, txdSpeedMark[playerid]);

			PlayerTextDrawShow(playerid, txdPlayerHealth[playerid]);

			PlayerTextDrawShow(playerid, txdSecondsTime[playerid]);
			PlayerTextDrawShow(playerid, txdPlayerZone[playerid]);
			PlayerTextDrawShow(playerid, txdPlayerRegion[playerid]);

			TextDrawShowClock[playerid] = true;
			SendClientMessage(playerid, COLOR_GREY, "   ���������� ���� � ������� ��������� !");
		}
	}
	else if(listitem == 10)
	{   //toghp
		if(TextDrawShowArmour[playerid] == true)
		{
			PlayerTextDrawHide(playerid, txdPlayerHealth[playerid]);
			PlayerTextDrawHide(playerid, txdPlayerArmour[playerid]);
			TextDrawShowArmour[playerid] = false;
			SendClientMessage(playerid, COLOR_GREY, "   ���������� � ����� ������ !");
		}
		else
		{
			PlayerTextDrawShow(playerid, txdPlayerHealth[playerid]);
			PlayerTextDrawShow(playerid, txdPlayerArmour[playerid]);
			TextDrawShowArmour[playerid] = true;
			SendClientMessage(playerid, COLOR_GREY, "   ���������� � ����� ��������� !");
		}
	}
	else if(listitem == 11)
	{   //togsys
        /*if(PlayerInfo[playerid][pAdmin] < 1)
        {
            SendClientMessage(playerid, COLOR_GREY, "   �� �� ������������ ������������ ��� ������� !");
            return 1;
        }*/
		if(TextDrawShowMessage[playerid] == false)
		{
			TextDrawShowForPlayer(playerid, txdSystemMessage);
			TextDrawShowMessage[playerid] = true;
			SendClientMessage(playerid, COLOR_GREY, "   ��������� ������ �������� !");
		}
		else
		{
			TextDrawHideForPlayer(playerid, txdSystemMessage);
			TextDrawShowMessage[playerid] = false;
			SendClientMessage(playerid, COLOR_GREY, "   ��������� ������ ������ !");
		}
	}
	else if(listitem == 12)
	{   ///togadmin
		if(GetPVarInt(playerid, "gAdmin") == 0)
		{
			SetPVarInt(playerid, "gAdmin", 1);
			SendClientMessage(playerid, COLOR_GREY, "   ����� ��������� ������ !");
		}
		else
		{
			SetPVarInt(playerid, "gAdmin", 0);
			SendClientMessage(playerid, COLOR_GREY, "   ����� ��������� ��������� !");
		}
	}
	TogHelp(playerid);
	return 1;
}




stock PlayerUpgrade(playerid)
{
	new DialogIDCounter = 0;
	new listitems[65*12];//65 + 73+55+76+59+67 + 51 + 16�=�462
	for(new d=0; d<MAX_DLGITEMS; d++) DialogID[playerid][d] = -1;

	if(PlayerInfo[playerid][pPupgrade] >= 1)
	{
		if(PlayerInfo[playerid][pLevel] >= 2 &&
			PlayerInfo[playerid][pSHealth] < 50)
		{
			strins(listitems, "Health - ������ ����� �� 5% ������ �������� ��� �����������.\n", strlen(listitems));
			DialogID[playerid][0] = DialogIDCounter;
			DialogIDCounter ++;
		}
	}

	if(PlayerInfo[playerid][pPupgrade] >= 2)
	{

		if(	PlayerInfo[playerid][pLevel] >= 4 &&
			PlayerInfo[playerid][pHunger] < 9)
		{//������������� ����� �����.
			strins(listitems, "Hunger - ����� �� ��� ������ ���������� ����������� � ���.\n", strlen(listitems));
			DialogID[playerid][1] = DialogIDCounter;
			DialogIDCounter ++;
		}

		if(	PlayerInfo[playerid][pLevel] >= 6 &&
			PlayerInfo[playerid][pLeisure] < 9)
		{
			strins(listitems, "Leisure - ��������� ����� ����������� �����������.\n", strlen(listitems));
			DialogID[playerid][2] = DialogIDCounter;
			DialogIDCounter ++;
		}

		if(	PlayerInfo[playerid][pLevel] >= 8 &&
			PlayerInfo[playerid][pContact] < 9)
		{
			strins(listitems, "Contact - ����� �� ��� ������ ���������� ����������� � �������.\n", strlen(listitems));
			DialogID[playerid][3] = DialogIDCounter;
			DialogIDCounter ++;
		}

		if(	PlayerInfo[playerid][pLevel] >= 10 &&
			PlayerInfo[playerid][pToilet] < 9)
		{
			strins(listitems, "Toilet - ��������� ����� ����������� ������.\n", strlen(listitems));
			DialogID[playerid][4] = DialogIDCounter;
			DialogIDCounter ++;
		}

		if(	PlayerInfo[playerid][pLevel] >= 12 &&
			PlayerInfo[playerid][pVigour] < 9)
		{
			strins(listitems, "Vigour - ����� �� ��� ������ ���������� ����������� � ���.\n", strlen(listitems));
			DialogID[playerid][5] = DialogIDCounter;
			DialogIDCounter ++;
		}

		if(	PlayerInfo[playerid][pLevel] >= 14 &&
			PlayerInfo[playerid][pAlcoholPerk] < 9)
		{
			strins(listitems, "Alcoholic - ������ hp �� ������� ���-�� ����� + ������ ��������.\n", strlen(listitems));
			DialogID[playerid][6] = DialogIDCounter;
			DialogIDCounter ++;
		}

		if(PlayerInfo[playerid][pLevel] >= 16 &&
			PlayerInfo[playerid][pDrugPerk] < 9)
		{
			strins(listitems, "DrugAddict - ������ �������� + ��������� � ��������.\n", strlen(listitems));
			DialogID[playerid][7] = DialogIDCounter;
			DialogIDCounter ++;
		}

		if(PlayerInfo[playerid][pLevel] >= 18 && //PlayerInfo[playerid][pJob] == ARMSDEALER &&
			PlayerInfo[playerid][pMiserPerk] < 9)
		{
			strins(listitems, "Miser - ��������� ������ �� ��� ������ ����������.\n", strlen(listitems));
			DialogID[playerid][8] = DialogIDCounter;
			DialogIDCounter ++;
		}

		if(PlayerInfo[playerid][pLevel] >= 20 &&
			PlayerInfo[playerid][pTraderPerk] < 9)
		{
			strins(listitems, "Trade - ������� ������� � 24/7, ���������� � ����������.\n", strlen(listitems));
			DialogID[playerid][9] = DialogIDCounter;
			DialogIDCounter ++;
		}

		if(PlayerInfo[playerid][pLevel] >= 22 && //PlayerInfo[playerid][pMember] == DoH &&
			PlayerInfo[playerid][pPainPerk] < 9)
		{
			strins(listitems, "PainKillers - ����� �����-�� ��� �� 20'/. �������� ������.\n", strlen(listitems));
			DialogID[playerid][10] = DialogIDCounter;
			DialogIDCounter ++;
		}

	}
	if(PlayerInfo[playerid][pLevel] >= 2 &&
		GetPlayerMoneyH(playerid) >= 10000)
	{
		strins(listitems, "Reset Upgrades - �������� ��� ��������� ($10000)\n", strlen(listitems));
		DialogID[playerid][11] = DialogIDCounter;
		DialogIDCounter ++;
		//��������������
		//format(strings, sizeof(strings), "DialogID[playerid][27]: %d", DialogID[playerid][27]);
		//ABroadCast(COLOR_MAROON, strings, 9);
	}

	if(DialogIDCounter <= 0)
	{
		PlayerMenu(playerid);
		SendClientMessage(playerid, COLOR_GREY, "   ��� ��������� ��������� !");
		return 1;
	}

	new caption[70];
	format(caption, sizeof(caption), "*** UPGRADES *** �������� %d ����� ���������", PlayerInfo[playerid][pPupgrade]);
	if(strlen(listitems) > sizeof(listitems))
	{
		//��������������
		format(strings, sizeof(strings), "Error: *** UPGRADES *** %s[%d], strlen(listitems): %d, sizeof(listitems): %d",
			PlayerName(playerid), playerid, strlen(listitems), sizeof(listitems));
		Log(ERROR, strings);
		return 1;
	}

	if(strlen(listitems) <= 0)
	{
		GeneralCMD(playerid); SendClientMessage(playerid, COLOR_GREY, "   UPGRADES ����");//COLOR_BLUEGREY
		return 1;
	}

	ShowPlayerDialogEx(playerid, UPGRADE_DIALOG, DIALOG_STYLE_LIST, caption, listitems, "OK", "�����");
	return 1;
}
stock upgrade_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if(dialogid != UPGRADE_DIALOG) return 1;
	if(!response)
	{
		PlayerMenu(playerid);
		return 1;
	}
	new msgitem[70];
	if(listitem == DialogID[playerid][0])
	{   //strcmp(upgradename, "health", true, strlen(upgradename)) == 0
		PlayerInfo[playerid][pSHealth] += 5.0;
		format(msgitem, sizeof(msgitem), "New Upgrade: +5 �������� ��� ����������� = %.0f", PlayerInfo[playerid][pSHealth]+50.0);
		PlayerInfo[playerid][pPupgrade] -= 1;
		GameTextForPlayerEx(playerid, "~r~-1 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][1])
	{
		PlayerInfo[playerid][pHunger] += 1;
		format(msgitem, sizeof(msgitem), "New Perk Upgrade: ��� ��������� ������ %d-�� ������.", PlayerInfo[playerid][pHunger]);
		PlayerInfo[playerid][pPupgrade] -= 2;
		GameTextForPlayerEx(playerid, "~r~-2 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][2])
	{
		PlayerInfo[playerid][pLeisure] += 1;
		format(msgitem, sizeof(msgitem), "New Perk Upgrade: ��� ��������� ������ %d-�� ������.", PlayerInfo[playerid][pLeisure]);
		PlayerInfo[playerid][pPupgrade] -= 2;
		GameTextForPlayerEx(playerid, "~r~-2 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][3])
	{
		PlayerInfo[playerid][pContact] += 1;
		format(msgitem, sizeof(msgitem), "New Perk Upgrade: ���� ����������� ������ %d-�� ������.", PlayerInfo[playerid][pContact]);
		PlayerInfo[playerid][pPupgrade] -= 2;
		GameTextForPlayerEx(playerid, "~r~-2 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][4])
	{
		PlayerInfo[playerid][pToilet] += 1;
		format(msgitem, sizeof(msgitem), "New Perk Upgrade: ��� ���������� ������ %d-�� ������.", PlayerInfo[playerid][pToilet]);
		PlayerInfo[playerid][pPupgrade] -= 2;
		GameTextForPlayerEx(playerid, "~r~-2 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][5])
	{
		PlayerInfo[playerid][pVigour] += 1;
		format(msgitem, sizeof(msgitem), "New Perk Upgrade: ��� ������������ ������ %d-�� ������.", PlayerInfo[playerid][pVigour]);
		PlayerInfo[playerid][pPupgrade] -= 2;
		GameTextForPlayerEx(playerid, "~r~-2 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][6])// && DialogID[playerid][22] != 0
	{   // && (strcmp(upgradename, "alcoholic", true, strlen(upgradename)) == 0)
		PlayerInfo[playerid][pAlcoholPerk] += 1;
		format(msgitem, sizeof(msgitem), "New Perk Upgrade: ���� ����������� ������������� ������ %d-�� ������.", PlayerInfo[playerid][pAlcoholPerk]);
		PlayerInfo[playerid][pPupgrade] -= 2;
		GameTextForPlayerEx(playerid, "~r~-2 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][7])// && DialogID[playerid][23] != 0
	{   // && (strcmp(upgradename, "drugaddict", true, strlen(upgradename)) == 0)
		PlayerInfo[playerid][pDrugPerk] += 1;
		format(msgitem, sizeof(msgitem), "New Perk Upgrade: ���� ����� ������������� %d-�� ������.", PlayerInfo[playerid][pDrugPerk]);
		PlayerInfo[playerid][pPupgrade] -= 2;
		GameTextForPlayerEx(playerid, "~r~-2 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][8])// && DialogID[playerid][24] != 0
	{   // && (strcmp(upgradename, "miser", true, strlen(upgradename)) == 0)
		PlayerInfo[playerid][pMiserPerk] += 1;
		format(msgitem, sizeof(msgitem), "New Perk Upgrade: ��� ����� �������� %d-�� ������.", PlayerInfo[playerid][pMiserPerk]);
		PlayerInfo[playerid][pPupgrade] -= 2;
		GameTextForPlayerEx(playerid, "~r~-2 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][9])// && DialogID[playerid][25] != 0
	{   // && (strcmp(upgradename, "trader", true, strlen(upgradename)) == 0
		PlayerInfo[playerid][pTraderPerk] += 1;
		format(msgitem, sizeof(msgitem), "New Perk Upgrade: ��� ����� ���������� %d-�� ������.", PlayerInfo[playerid][pTraderPerk]);
		PlayerInfo[playerid][pPupgrade] -= 2;
		GameTextForPlayerEx(playerid, "~r~-2 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][10])// && DialogID[playerid][26] != 0
	{   // && (strcmp(upgradename, "painkillers", true, strlen(upgradename)) == 0)
		PlayerInfo[playerid][pPainPerk] += 1;
		format(msgitem, sizeof(msgitem), "New Perk Upgrade: ��� ����� ������ ������ %d-�� ������.", PlayerInfo[playerid][pPainPerk]);
		PlayerInfo[playerid][pPupgrade] -= 2;
		GameTextForPlayerEx(playerid, "~r~-2 points", 5000, 1);
	}
	else if(listitem == DialogID[playerid][11])// && DialogID[playerid][27] != 0
	{
		PlayerInfo[playerid][pPupgrade] = (PlayerInfo[playerid][pLevel]-1)*2;
		PlayerInfo[playerid][pSHealth] = 0.0;

		PlayerInfo[playerid][pAlcoholPerk] = 0;
		PlayerInfo[playerid][pDrugPerk] = 0;
		PlayerInfo[playerid][pMiserPerk] = 0;
		PlayerInfo[playerid][pPainPerk] = 0;
		PlayerInfo[playerid][pTraderPerk] = 0;

		PlayerInfo[playerid][pHunger] = 0;
		PlayerInfo[playerid][pLeisure] = 0;
		PlayerInfo[playerid][pContact] = 0;
		PlayerInfo[playerid][pToilet] = 0;
		PlayerInfo[playerid][pVigour] = 0;

		GivePlayerMoneyH(ftax, playerid, -10000);//10000 ��� ���������
		if(BizInfo[0][bTill]+10000 < 2147480000) { BizInfo[0][bTill] += 10000; BizInfo[0][bExport] += 10000; }
		//new family = PlayerInfo[Offer[playerid]][pMember];
		//FamilyInfo[0+7][fBank] += recovery;
		format(msgitem, sizeof(msgitem), "Reset Upgrades. B� ������ %d ����(��) ��������� !", PlayerInfo[playerid][pPupgrade]);
	}
	SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
	PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
	PlayerUpgrade(playerid);
	return 1;
}


//�� ��� ����� ������������ ��� ����� ������� /stats ������������ ������� �����
stock OnPlayerShowStats(playerid, targetid)//���������� �� ������� /stats
{   //playerid - ��� ��� �������� ����, targetid - ��� ������������
	new atext[20];
	if(PlayerInfo[targetid][pSex] == Male) { atext = "Male"; }
	else if(PlayerInfo[targetid][pSex] == Female) { atext = "Female"; }
	else atext = "Unknown";

	new otext[20];//��� �����
	if(PlayerInfo[targetid][pOrigin] == 0) { otext = "Minsk"; }
	else if(PlayerInfo[targetid][pOrigin] == 1) { otext = "Grodno"; }
	else if(PlayerInfo[targetid][pOrigin] == 2) { otext = "Gomel"; }
	else if(PlayerInfo[targetid][pOrigin] == 3) { otext = "Mogilev"; }
	else if(PlayerInfo[targetid][pOrigin] == 4) { otext = "Vitebsk"; }
	else if(PlayerInfo[targetid][pOrigin] == 5) { otext = "Brest"; }
	else if(PlayerInfo[targetid][pOrigin] == 6) { otext = "Russia"; }
	else if(PlayerInfo[targetid][pOrigin] == 7) { otext = "Ukraine"; }
	else if(PlayerInfo[targetid][pOrigin] == 8) { otext = "Lithuania"; }
	else if(PlayerInfo[targetid][pOrigin] == 9) { otext = "Latvia"; }
	else if(PlayerInfo[targetid][pOrigin] == 10) { otext = "Estonia"; }
	else if(PlayerInfo[targetid][pOrigin] == 11) { otext = "Moldova"; }
	else if(PlayerInfo[targetid][pOrigin] == 12) { otext = "Bulgaria"; }
	else if(PlayerInfo[targetid][pOrigin] == 13) { otext = "Kazakhstan"; }
	else if(PlayerInfo[targetid][pOrigin] == 14) { otext = "Bashkortostan"; }
	else if(PlayerInfo[targetid][pOrigin] == 15) { otext = "Israil"; }
	else if(PlayerInfo[targetid][pOrigin] == 16) { otext = "Italy"; }
	else if(PlayerInfo[targetid][pOrigin] == 17) { otext = "Germany"; }
	else { otext = "Unknown"; }

	new actext[20];
	if(PlayerInfo[targetid][pAccount] != 0) { actext = "Premium"; }
	else { actext = "None"; }

	//----------------------------------------------------------------------
	new age = GetAgePlayer(PlayerInfo[targetid][pAge])+18+PlayerInfo[targetid][pConnectTime]/12;

	new housekey = PlayerInfo[targetid][pHouse];
	new carid1 = MyCar[targetid][0];
	new carid2 = MyCar[targetid][1];
	new carid3 = MyCar[targetid][2];

	new married[24];
	strmid(married, PlayerInfo[targetid][pMarriedTo], 0, strlen(PlayerInfo[targetid][pMarriedTo]), 24);
	new ptime = PlayerInfo[targetid][pConnectTime];
	new warns = PlayerInfo[targetid][pWarns];
	new cash = GetPlayerMoneyH(targetid);
	new deposit = PlayerInfo[targetid][pDeposit];
	new account = PlayerInfo[targetid][pBank];
	new lotto = PlayerInfo[targetid][pLottoNr];
	new deaths = PlayerInfo[targetid][pDeaths];
	new fishes = PlayerInfo[targetid][pFishes];
	new bigfish = PlayerInfo[targetid][pBiggestFish];
	new accident = PlayerInfo[playerid][pAccident];
	new ticket = PlayerInfo[playerid][pTicket];
	new crimes = PlayerInfo[targetid][pCrimes];
	new arrests = PlayerInfo[targetid][pArrested];
	new warrests = PlayerInfo[targetid][pWantedDeaths];
	new drugs = PlayerInfo[targetid][pDrugs];
	new mats = PlayerInfo[targetid][pMats];
	new mushrooms = PlayerInfo[targetid][pMushroom];
	new wanted = WantedLevel[targetid];
	new level = PlayerInfo[targetid][pLevel];
	new expamount = PlayerInfo[targetid][pRespect];
	new kills = PlayerInfo[targetid][pKills];
	new pnumber = PlayerInfo[targetid][pPnumber];

	new bizkey = PlayerInfo[targetid][pBizz];
	new intir = PlayerInfo[targetid][pInt];
	new local = PlayerInfo[targetid][pLocal];
	new wirtual = PlayerInfo[targetid][pVirtual];

	new Float:lhealth = LastHealth[targetid];
	new Float:shealth;
	GetPlayerHealth(playerid, shealth);

	new payday = PlayerInfo[targetid][pPayTime];
	new paycheck = PlayerInfo[targetid][pPayCheck];
	new std = PlayerInfo[targetid][pSTD];
	//======================================================================
	new text0[8], text1[8], text2[8], text3[8], text4[8], text5[8];
	new coordsstring[128];
	new name[MAX_PLAYER_NAME]; GetPlayerName(targetid, name, sizeof(name));
	if(GetPVarInt(playerid, "gDocuments") == 1)
	{
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "* %s ������� %s'� ���� ���������.", PlayerName(targetid), PlayerName(playerid));
		ProxDetector(targetid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);

		new Float:px, Float:py, Float:pz; GetPlayerPos(targetid, px, py, pz);
		new tcity[20], tregion[20], tcar[32];
		new name_info[2][20]; split(name, name_info, '_');
 		if(housekey != NOT_KEY)
		{
			tcity = GetPointInZoneName(HouseInfo[housekey][hEntranceX], HouseInfo[housekey][hEntranceY], HouseInfo[housekey][hEntranceZ]);
			for(new j=0; j<MAX_TURFS; j++)
			{
				if( IsPointInRegion(HouseInfo[housekey][hEntranceX], HouseInfo[housekey][hEntranceY], HouseInfo[housekey][hEntranceZ], j) )//���� ��� ��������� � ����������� �� ������ j �� ������� zones
				{
					strmid(tregion, regions[j][region_name], 0, strlen(regions[j][region_name]), 20);//��������� �������� �������� �� ������.
					break;
				}
			}
		}
		else
		{
			tcity = "Los Santos"; tregion = "Jefferson";
			strmid(tcar, "None", 0, strlen("None"), 255);//��������� �������� �������� �� ������.
		}//Motel
		if(carid1 <= 0) strmid(tcar, "None", 0, strlen("None"), 32);
		else
		{
			new modelid = VehInfo[carid1][cModel];//GetVehicleModel(carid1);
			strmid(tcar, VehicleArray[modelid-400][Vehicle_Name], 0, strlen(VehicleArray[modelid-400][Vehicle_Name]), 32);//��������� �������� �������� �� ������.
		}
		new JobSkill, JobLevel;
		GetPlayerSkill(targetid, PlayerInfo[targetid][pJob], JobSkill, JobLevel);

		new msgitem[1476];//49+55+58+46+55 +29+ 61*3 + 37+62+37+38+35+46+51+40*7  +  24+2+4+2+4+20+20+2+(3+2+2+3)*3+24+20+1+3+20+20+3+8*6+24*7�=�1476
		strcat(msgitem, "{AFAFAF}________________________________________");
		format(coordsstring, sizeof(coordsstring), "\n{0080FF}���: {FFFFFF}%s\t{0080FF}�������: {FFFFFF}%s", name_info[0], name_info[1]);
		strcat(msgitem, coordsstring);
		format(coordsstring, sizeof(coordsstring), "\n{0080FF}���: {FFFFFF}%s \t\t{0080FF}�������: {FFFFFF}%d", atext, age);
		strcat(msgitem, coordsstring);
		format(coordsstring, sizeof(coordsstring), "\n{0080FF}���������: \t\t{FFFFFF}%d �.(%d �.)", PlayerInfo[targetid][pLevel], PlayerInfo[targetid][pConnectTime]);
		strcat(msgitem, coordsstring);
		format(coordsstring, sizeof(coordsstring), "\n{0080FF}�����: {FFFFFF}%s\t{0080FF}�����: {FFFFFF}%s", tcity, tregion);
		strcat(msgitem, coordsstring);

		if(housekey != NOT_KEY)	{ format(coordsstring, sizeof(coordsstring), "\n{0080FF}� ����: {FFFFFF}%d", housekey+1); strcat(msgitem, coordsstring); }

		if(carid1)	{
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}ID ����1[lock/parking/insur]: {FFFFFF}%d[%d/%d/%d]",
				carid1, VehInfo[carid1][cLock], VehInfo[carid1][cPark], VehInfo[carid1][cInsur]);
			strcat(msgitem, coordsstring);
		}
		if(carid2)	{
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}ID ����2[lock/parking/insur]: {FFFFFF}%d[%d/%d/%d]",
				carid2, VehInfo[carid2][cLock], VehInfo[carid2][cPark], VehInfo[carid2][cInsur]);
			strcat(msgitem, coordsstring);
		}
		if(carid3)	{
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}ID ����3[lock/parking/insur]: {FFFFFF}%d[%d/%d/%d]",
				carid3, VehInfo[carid3][cLock], VehInfo[carid3][cPark], VehInfo[carid3][cInsur]);
			strcat(msgitem, coordsstring);
		}
		if( strcmp(PlayerInfo[targetid][pMarriedTo], "BeSingle", true) )	{
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}� ����� ��: \t\t{FFFFFF}%s", PlayerInfo[targetid][pMarriedTo]);
			strcat(msgitem, coordsstring);
		}
		if( PlayerInfo[targetid][pJob] != 0)
		{
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}��������: {FFFFFF}%s\t{0080FF}Skill: {FFFFFF}%d[%d]", GetPlayerJob(targetid), JobLevel, JobSkill);
			strcat(msgitem, coordsstring);
		}
		if( PlayerInfo[targetid][pMember] > 0 && PlayerInfo[targetid][pMember] < DoT)
		{
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}�����:\t\t{FFFFFF}%s", GetPlayerMembers(targetid));// Post:%s ttext,ftext
			strcat(msgitem, coordsstring);
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}����: \t\t{FFFFFF}%s", GetPlayerRanks(targetid));// Post:%s ttext,ftext
			strcat(msgitem, coordsstring);
		}
		else if( PlayerInfo[targetid][pMember] >= DoT)
		{
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}�����������:\t\t{FFFFFF}%s", GetPlayerMembers(targetid));// Post:%s ttext,ftext
			strcat(msgitem, coordsstring);
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}���������: \t\t{FFFFFF}%s", GetPlayerRanks(targetid));// Post:%s ttext,ftext
			strcat(msgitem, coordsstring);
		}
		format(coordsstring, sizeof(coordsstring), "\n{0080FF}��������: \t\t{FFFFFF}%d", PlayerInfo[targetid][pRespect]);
		strcat(msgitem, coordsstring);

        if(PlayerInfo[targetid][pBikeLic] == 1) { text0 = 	"Bike"; } else { text0 = ""; }//�������� �� ����
        if(PlayerInfo[targetid][pCarLic] == 1) { text1 = 	"Drivers"; } else { text1 = ""; }
		if(PlayerInfo[targetid][pFlyLic] == 1) { text2 = 	"Flying"; } else { text2 = ""; }
		if(PlayerInfo[targetid][pBoatLic] == 1) { text3 = 	"Sailing"; } else { text3 = ""; }
        if(PlayerInfo[targetid][pFishLic] == 1) { text4 = 	"Fishing"; } else { text4 = ""; }
        if(PlayerInfo[targetid][pGunLic] == 1) { text5 = 	"Weapon"; } else { text5 = ""; }

        format(coordsstring, sizeof(coordsstring), "\n{0080FF}Licenses: {FFFFFF}%s %s %s %s %s %s", text0, text1, text2, text3, text4, text5);
		strcat(msgitem, coordsstring);
		strcat(msgitem, "\n{AFAFAF}________________________________________");
		if(gGotOrder[targetid] < MAX_PLAYERS-1 && gGotOrder[targetid] != SOC_PACKET && gGotOrder[targetid] != QUIT_JOB)
		{
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}Order: \t{FFFFFF}%s", PlayerName(gGotOrder[targetid]));
			strcat(msgitem, coordsstring);
		}
		else if(gGotOrder[targetid] < MAX_PLAYERS-1 && gGotOrder[targetid] == SOC_PACKET)
		{
			format(coordsstring, sizeof(coordsstring), "\n{0080FF}���. �����: \t{FFFFFF}%s", PlayerName(gGotOrder[targetid]));
			strcat(msgitem, coordsstring);
		}
		else if(gGotOrder[targetid] < MAX_PLAYERS-1 && gGotOrder[targetid] == QUIT_JOB)
		{
			strcat(msgitem, "\n{0080FF}���������� �� ����������");
		}
		if(PlayerInfo[targetid][pSTD] == IsNotBeenIll)
		{
			strcat(msgitem, "\n{0080FF}���. ������: {FFFFFF}�������");
		}
		if(GetPVarInt(playerid, "gGotPermit") == 1)
		{
			strcat(msgitem, "\n{0080FF}����������: {FFFFFF}House");
		}
		else if(GetPVarInt(playerid, "gGotPermit") == 2)
		{
			strcat(msgitem, "\n{0080FF}����������: {FFFFFF}Business");
		}
		else if(GetPVarInt(playerid, "gGotPermit") == 3)
		{
			strcat(msgitem, "\n{0080FF}����������: {FFFFFF}Company");
		}
		//ShowPlayerDialogGap(playerid, 65, DIALOG_STYLE_MSGBOX, "{0000FF}PASSPORT OF CITIZEN OF THE SAN ANDREAS", msgitem, "Return", "Take");
		ShowPlayerDialogGap(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, "{80FFFF}PASSPORT OF CITIZEN OF THE SAN ANDREAS", msgitem, "OK", "");
		SetPVarInt(playerid, "gDocuments", 0);
    	return 1;
	}
	else //if(GetPVarInt(playerid, "gDocuments") == 2)
	{
		//if(PlayerInfo[playerid][pAdmin] > 0) ShowStats(playerid, targetid);

		format(coordsstring, sizeof(coordsstring), "*** {FFFFFF}%s{33AA33} ***____________________________________________________________________________",name);
		SendClientMessage(playerid, COLOR_GREEN,coordsstring);
		format(coordsstring, sizeof(coordsstring), "gPlayerLogged:%d, gPlayerSpawned:%d, CurState:%d",
			gPlayerLogged[targetid], gPlayerSpawned[targetid], CurState[targetid]);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);

		format(coordsstring, sizeof(coordsstring), "H�������:[$%d] � �����:[$%d] �� ��������:[$%d] PayTime/PayCheck/Online:[%d/%d/%d]",
			cash,account,deposit, payday, paycheck, PlayerInfo[targetid][pConnectTime]-PlayerInfo[targetid][pOnline]);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		format(coordsstring, sizeof(coordsstring), "��������:[%.0f/%.0f] �������:[%d] ���:[%s] �������:[%d] ������:[%s] ������:%d[�har:%d]",
			lhealth,shealth,pnumber,atext,age,otext, PlayerInfo[targetid][pModel], PlayerInfo[targetid][pChar]);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		format(coordsstring, sizeof(coordsstring), "�������:[%d] �����:[%d] ��������:[%d] Warn:[%d] �������:[%s] �����������:[%d]",
			level, ptime, expamount, warns, married, std);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		format(coordsstring, sizeof(coordsstring), "H���������:[%d] ����������:[%d] ��� �������:[%d] ������� ����:[%d] ������:[%d] ���������� �:[%d]",
			drugs,mats,fishes,bigfish, mushrooms,lotto);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		format(coordsstring, sizeof(coordsstring), "C������:[%d] �������:[%d] ���:[%d] �������:[%d] ������������:[%d] ������� �������:%d[%d ���] �������:[%d] ������� ��� �������:[%d]",
			deaths,kills,accident,ticket,crimes,wanted,WantedPoints[targetid]*5,arrests,warrests);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		format(coordsstring, sizeof(coordsstring), "P�����:[%s(duty:%d)] ContractTime:[%d] �������:[%s] ���������:[%s(duty:%d)] ������:%d[%d]",
			GetPlayerJob(targetid), gJobDuty[targetid], PlayerInfo[targetid][pContractTime], GetPlayerMembers(targetid), GetPlayerRanks(targetid), gOnDuty[targetid], PlayerInfo[targetid][pTut], gCheckInMission[targetid]);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		format(coordsstring, sizeof(coordsstring), "������ ����1[lock/parking/insur]: ����1: %d[%d/%d/%d], ����2: %d[%d/%d/%d], ����3: %d[%d/%d/%d]",
			carid1, VehInfo[carid1][cLock], VehInfo[carid1][cPark], VehInfo[carid1][cInsur],
			carid2, VehInfo[carid2][cLock], VehInfo[carid2][cPark], VehInfo[carid2][cInsur],
			carid3, VehInfo[carid3][cLock], VehInfo[carid3][cPark], VehInfo[carid3][cInsur]);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		format(coordsstring, sizeof(coordsstring), "�������������[lock]: %d[%d], �������.����[lock]: %d[%d], ��������: %d, CarTime: %d",
			HireCarID[targetid],iVehicleObjective[HireCarID[targetid]][MAX_PLAYERS-1],
			LastCar[targetid],iVehicleObjective[LastCar[targetid]][MAX_PLAYERS-1],
			GetPlayerSurfingVehicleID(targetid),
			PlayerInfo[targetid][pCarTime]);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		//----------------------------------------------------------------------
		format(coordsstring, sizeof(coordsstring), "K��� �� ����:[%d] K��� �� ����:[%d] ��������:[%d] �������:[%d] ���:[%d]", housekey, bizkey, intir,local,wirtual);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		new AdminLevel = PlayerInfo[targetid][pAdmin];

		new Float:armour;	GetPlayerArmour(targetid, armour);
        new Gun = GetPlayerWeapon(targetid); new Ammo = GetPlayerAmmo(targetid);
		format(coordsstring, sizeof(coordsstring), "A������:[%s] Armour:[%.0f] Gun:[%d] Ammo:[%d] PlayerIP:[%s] AdminLevel:[%d] AFK_IdleSec:[%d]",
			actext,armour,Gun,Ammo, PlayerInfo[targetid][pIP],AdminLevel,AFK_IdleTime[targetid]);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		if(PlayerInfo[targetid][pBikeLic] == 1) { text0 = "Bike"; } else { text0 = ""; }//�������� �� ����
        if(PlayerInfo[targetid][pCarLic] == 1) { text1 = "Drivers"; } else { text1 = ""; }
		if(PlayerInfo[targetid][pFlyLic] == 1) { text2 = "Flying"; } else { text2 = ""; }
		if(PlayerInfo[targetid][pBoatLic] == 1) { text3 = "Sailing"; } else { text3 = ""; }
        if(PlayerInfo[targetid][pFishLic] == 1) { text4 = "Fishing"; } else { text4 = ""; }
        if(PlayerInfo[targetid][pGunLic] == 1) { text5 = "Weapon"; } else { text5 = ""; }
        format(coordsstring, sizeof(coordsstring), "Licenses: %s %s %s %s %s %s", text0, text1, text2, text3, text4, text5);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		format(coordsstring, sizeof(coordsstring), "CallTime:[%d] Marker:[%d] Anticheat:[%d] Team:[%d] Vote:[%d] Controllable:[%d]",
			CallTimeCounter[targetid], MarkerToPlayer[targetid], gAnticheat[targetid], PlayerInfo[targetid][pTeam], PlayerInfo[targetid][pVote], IsPlayerControllable[targetid]);
		SendClientMessage(playerid, COLOR_SYSTEM,coordsstring);
		//}
		SendClientMessage(playerid, COLOR_GREEN, "__________________________________________________________________________________________________________");
	}
	return 1;
}//end OnPlayerShowStats(playerid, targetid)







stock Testing_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
//#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != TEST_DIALOG) return 1;
	if(!response)
	{
		SendClientMessage(playerid, COLOR_RED, "�� ���������� �� ����������� ����� (Kicked)!");
	 	return 1;
	}
	//new msgitem[256+1];
	//new giveplayerid;
//RegistrationSTEP2
//ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "1. �� ����� �� ���� � ������� � ������� �����������.", listitems, "OK", "Cancel");
	PlayerTesting(playerid, listitem);//RegistrationSTEP3
	return 1;
}
//RegistrationSTEP3
stock PlayerTesting(playerid, listitem)
{
	if(MenuOperation[playerid] == 71)
	{
		if(listitem == 2) //2 , �.�. ���� ��� �� ����
		{       //���� ����� ������ 3 ������ ������
			SendClientMessage(playerid, COLOR_GREEN, "�� �������� ���������!");
			new listitems[] = "1. �������� ������, �� ������� �� ���� ��������.\
\n2. C������ � ����������� ����� /report, �������� � ������ ������ ��� ID.\
\n3. ������, ��� ������� � ��� ���������� ����� ��.";
			MenuOperation[playerid] = 72;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "2/15. ����� �� ����� ������ ���������� ���-���������.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "�� �������� ������� (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] ��� ������, �������: �� �������� ������� !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 72)
	{
		if(listitem == 1)
		{
			SendClientMessage(playerid, COLOR_GREEN, "�� �������� ���������!");
			new listitems[] = "1. ��� ���� ������ �����, �.�. �� ���� � ���� ������ �������\
\n2. ��� ���� ������ ������ � ����� �� ��� ������.\
\n3. �� ��� �� ���� ���� ������.";

			MenuOperation[playerid] = 73;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "3/15. ��� ���������� �������� ������ ���������.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "�� �������� ������� (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] ��� ������, �������: �� �������� ������� !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 73)
	{
		if(listitem == 2)
		{
			SendClientMessage(playerid, COLOR_GREEN, "�� �������� ���������!");
			new listitems[] = "1. ������� ��� ����� /report, ���� �� �������.\
\n2. �������� ���, ��� � ��� ���� �� ����������� ��������.\
\n3. ����� ��� �� ������� � ����.\
\n4. ����� ��� �� ������� � ������� ������� �������.\
\n5. ������� ��������� ����� � ������� ������� �������.";
			MenuOperation[playerid] = 74;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "4/15. �� ��������� ���������� ������, � �� �� ���������.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "�� �������� ������� (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] ��� ������, �������: �� �������� ������� !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 74)
	{
		if(listitem == 3 || listitem == 4)
		{
			SendClientMessage(playerid, COLOR_GREEN, "�� �������� ���������!");
			new listitems[] = "1. ������ � /report � �������� ����������.\
\n2. � ��� ��� �����.\
\n3. �� ���� � ���� ������ �������.\
\n4. ������������, �.�. ���� ��� �� ������.";
			MenuOperation[playerid] = 75;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "5/15. � ��� �� ������ ����� ����� � ESC, ����� �������� ������.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "�� �������� ������� (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] ��� ������, �������: �� �������� ������� !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 75)
	{
		if(listitem == 0 || listitem == 3)
		{
			SendClientMessage(playerid, COLOR_GREEN, "�� �������� ���������!");
			new listitems[] = "1. ��������� ��������� ��� ������������ ����� ��������.\
\n2. ����� �� ����, ����� �� ������ ������.\
\n3. ����� �� ������ ����� � ESC � ������ ����.";
			MenuOperation[playerid] = 76;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "6/15. ��� ����� �� ��� ������ �� ����.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "�� �������� ������� (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] ��� ������, �������: �� �������� ������� !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 76)
	{
		if(listitem == 1)
		{
			SendClientMessage(playerid, COLOR_GREEN, "�� �������� ���������!");
			new listitems[] = "1. ����, ���������� �������������� ��������.\
\n2. ����, ���������� ����� ���� Mister, Super, Girl, Pro, New, Man\
\n3. ����, ���������� �������� ������, �������, �����.\
\n4. ������������� � ����������� ����.\
\n5. ��� �������������.";
			MenuOperation[playerid] = 77;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "7/15. ������� ����� ���������� ��������� ������������:", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "�� �������� ������� (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] ��� ������, �������: �� �������� ������� !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 77)
	{
		if(listitem == 4)
		{
			SendClientMessage(playerid, COLOR_GREEN, "�� �������� ���������!");
			new listitems[] = "1. ���� ������� ������������ ��� �����������, ����� ����������.\
\n2. ������������ ������ ���������.\
\n3. ���� ������������ ��� � ������ �� �����.\
\n4. ������ � ����������� � ����������.\
\n5. ������ ������ ������� � ��������.\
\n6. ������ �������������. � �� ���� ������������.\
\n7. ������ ���������.";
			MenuOperation[playerid] = 78;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "8/15. ��� ���������� ������ ������ ���������� ������.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "�� �������� ������� (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] ��� ������, �������: �� �������� ������� !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 78)
	{
		if(listitem == 5)
		{
			SendClientMessage(playerid, COLOR_GREEN, "�� �������� ���������!");
			new listitems[] = "1. �� �������� ������ � �������� � ���������.\
\n2. �� ������������, ����� ������������ � ������ ����.\
\n3. �� �����������, �.�. ����� ������ �������� ������ ����������.\
\n4. ���� ������ ������, �� ������� ��������.\
\n5. ���������, �.�. ��� ������ ������ ������ ����������.\
\n6. �������� � ������ ������������� � ���������.";
			MenuOperation[playerid] = 79;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "9/15. ��� ���������� ������/������� ������� �� �������� ������.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "�� �������� ������� (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] ��� ������, �������: �� �������� ������� !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 79)
	{
		if(listitem == 5)
		{
			SendClientMessage(playerid, COLOR_GREEN, "�� �������� ���������!");
			new listitems[] = "1. ��������� ���-��������� � ������ ���������.\
\n2. ����, ���������, �������� ��� � ����.\
\n3. ������ ������������� �������.\
\n4. ����� �� ����� TS3 � ������ ��� 3-� ������ �����.\
\n5. ������ � ��� ����� ������ /service Rescue 911.\
\n6. ���������� �����������, �.�. ������ ��������� �� �������.";
			MenuOperation[playerid] = 80;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "10/15. ��� ��������/����� � �� ������ ���������.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "�� �������� ������� (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] ��� ������, �������: �� �������� ������� !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 80)
	{
		if(listitem == 4 || listitem == 5)
		{
			SendClientMessage(playerid, COLOR_GREEN, "�� �������� ���������!");
			new listitems[] = "1. � �������� ���������, �.�. ������ �� ������ ����� ������.\
\n2. ������������ ���������.\
\n3. ������ �������� ��������� (F8) � ������� � ��������������.\
\n4. � ��������� �������, ��� �� ��� ����� ��� ������� �������.";
			MenuOperation[playerid] = 81;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "11/15. ��� ���������� ��������� ��������� ���� ������.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "�� �������� ������� (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] ��� ������, �������: �� �������� ������� !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 81)
	{
		if(listitem == 2 || listitem == 3)
		{
			SendClientMessage(playerid, COLOR_GREEN, "�� �������� ���������!");
			new listitems[] = "1. � ����� ������.\
\n2. ��� �� ��������� ���������.\
\n3. ��� ��������� ���������.\
\n4. �� ���� �� �������� � ��������.";
			MenuOperation[playerid] = 82;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "12/15. �� ������ ���������������� ��� ���� �������.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "�� �������� ������� (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] ��� ������, �������: �� �������� ������� !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 82)
	{
		if(listitem == 2)
		{
			SendClientMessage(playerid, COLOR_GREEN, "�� �������� ���������!");
			new listitems[] = "1. ���� ��������.\
\n2. �� ���� �������� ������ �� �����.\
\n3. ������ ��� ����������� �������.\
\n4. ������ �������� � c����� �������������.";
			MenuOperation[playerid] = 83;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "13/15. �� �������� � ���� ����� ����������� � ����������� ���������.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "�� �������� ������� (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] ��� ������, �������: �� �������� ������� !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 83)
	{
		if(listitem == 1 || listitem == 3)
		{
			SendClientMessage(playerid, COLOR_GREEN, "�� �������� ���������!");
			new listitems[] = "1. �������� �������, ������� ��������.\
\n2. �������� �� ����� � �����.\
\n3. ����������� � ��������.\
\n4. ����� ����� �������, ������� �������.";
			MenuOperation[playerid] = 84;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "14/15. ��� ����� ��������, �� ��� ����� � ������ ������.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "�� �������� ������� (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] ��� ������, �������: �� �������� ������� !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 84)
	{
		if(listitem == 2)
		{
			SendClientMessage(playerid, COLOR_GREEN, "�� �������� ���������!");
			new listitems[] = "1. ���� ������, ����� ��������� ������ ��������������.\
\n2. ������ ��������������, ����� �������� �������������� �� ������.\
\n3. �� ������ ������ �������������� ��������� ���� �����������.";
			MenuOperation[playerid] = 85;
			ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "15/15. �� ������, ��� ������������� ��������� ��������� � �������.", listitems, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "�� �������� ������� (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] ��� ������, �������: �� �������� ������� !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	else if(MenuOperation[playerid] == 85)
	{
		if(listitem == 2)
		{
			SendClientMessage(playerid, COLOR_GREEN, "�� �������� ���������! ���� �������.");
			SendClientMessage(playerid, COLOR_GREEN, "��� ����, ��� ���������� ����������� �������� � ����� ������ �����������!");

		    if(TutTimeCounter[playerid] == 0)
		    {   //���� ������� �� ��� � ������ ������ �� ��������, �.�. ������������ ���� 1 �����
				//SetPVarInt(playerid, "gStatusRegistration", 1);//����� ������ ���� ��������� ��������� ��������
		    	//if(GetPVarInt(playerid, "gStatusRegistration"))
		    	if(PlayerInfo[playerid][pConnectTime] == 0 && !GetPVarInt(playerid, "gPlayerAccount"))
				{
					SetPVarInt(playerid, "gOoc", 1); SetPVarInt(playerid, "gNews", 1);
					SetPVarInt(playerid, "gFam", 1); SetPVarInt(playerid, "gHidePM", 0);
					SetPVarInt(playerid, "gSport", 1); SetPVarInt(playerid, "gJob", 1);//��� ����
				}
				TutTimeCounter[playerid] = 1;//��������� ���� ����� ������
				Tutorial(playerid);//RegistrationSTEP4
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "�� �������� ������� (Kicked) !");
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: %s[%d] ��� ������, �������: �� �������� ������� !",
				PlayerName(playerid), playerid);
			IsKicked[playerid] = 1;
		}
	}
	CrashDetected[playerid] = 87;
	return 1;
}

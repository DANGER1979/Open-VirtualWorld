new introtimer[MAX_PLAYERS];

//==============================================================================
//RegistrationSTEP0
stock Rules(playerid)
{
//��������: ����� ������ �� ������ 70 ��������
	new listitems[3715];
	strcat(listitems, "\t\t\t1/6. {0080FF}������� �������. �����������");
	strcat(listitems, "\n1.1. ������������ ��������� ������� �������������.");
	strcat(listitems, "\n1.2. ������������� �����, ������, ����������� ����.");
	strcat(listitems, "\n1.3. ����� ���������� ��������.");
	strcat(listitems, "\n1.4. ���������� ��������� ����������.");
	strcat(listitems, "\n1.5. ���������� ���� ������ �� ������� ������ �����.");
	strcat(listitems, "\n1.6. ��������� � ������������ ����� ������ ��������.");
	strcat(listitems, "\n1.7. ������� ��� ���������� ���-��������.");
	strcat(listitems, "\n1.8. ������������� ������� ������ ����������� ����");
	strcat(listitems, "\n� ����� ������ ������ ��������� �� ��� ���� ��������.");
	strcat(listitems, "\n1.9. ������������ ESC, ����� �� ���� ��� ������������");
	strcat(listitems, "\n� ����� �������� �� ���������, ���������� ������ ��� ������.");
	strcat(listitems, "\n1.10. ������ �� ����� (ESC) � ���� ���������� �����.");
	strcat(listitems, "\n1.11. ���������� ����� ���������� �� �������� ����� �");
	strcat(listitems, "\n��������� ���, ���� ����� �� ��� ������.");
	strcat(listitems, "\n1.12. ��������, ��� ��� ������������ � �������� ����)");
	strcat(listitems, "\n1.13. ���� �� ����� ����������.");
	strcat(listitems, "\n1.14. ������/���������/��������/�������� ����� ��������");
	strcat(listitems, "\n1.15. �������� � ������������� ����� ��� ����� �� ��������");
	strcat(listitems, "\n1.16. ������� � ������,�����,���������,�����,����������.");
	strcat(listitems, "\n1.17. �������� ������� �� �������� �����");
	strcat(listitems, "\n1.18. ������� ������� �� ����� ������.");
	strcat(listitems, "\n\t\t\t2/6. {0080FF}������� �������");
	strcat(listitems, "\n2.1. ��������� ��������� ���������� � ������� � ��� �������������.");
	strcat(listitems, "\n2.2. ��������� ��������� �����������, �������.");
	strcat(listitems, "\n2.3. ��������� ������ ������� (�� ����������� � �������� ��������).");
	strcat(listitems, "\n2.4. ��������� ������� ����� ������ ���������� �������.");
	strcat(listitems, "\n2.5. ��������� ������������� ���-���� (�����, ������, �������).");
	strcat(listitems, "\n2.6. ��������� ����� ��������� ���������� �����.");
	strcat(listitems, "\n\t\t\t3/6. {0080FF}������� �����");
	strcat(listitems, "\n3.1. ��������� ������������ ������������� ��� �������� ����.");
	strcat(listitems, "\n3.2. ��������� ����, ������� �� ���� ������ �������.");
	strcat(listitems, "\n3.3. ��������� ����, ���������� �����������.");
	strcat(listitems, "\n3.4. ��������� ����, ���������� ����� 50 % ��������� ����.");
	//strcat(listitems, "\n3.1. ��������� ���� ���������� �������������� ��������.");
	//strcat(listitems, "\n3.2. ��������� ������������ � ����� ����� ����:");
	//strcat(listitems, "\nMister, Super, Girl, Pro, New, Man, The, Boy, Cool, Best � �.�.");
	//strcat(listitems, "\n3.3. ��������� ���� ���������� �������� ������, �������, �����.");
	//strcat(listitems, "\n3.5. ��������� ������������ �����, �������� �� ��������.");
	strcat(listitems, "\n\t\t\t4/6. {0080FF}����������������� �������");
	strcat(listitems, "\n4.1. ��������� ���������/����������� �������� �������������.");
	strcat(listitems, "\n4.2. ��������� �������������� ������������� � ������.");
	strcat(listitems, "\n4.3. ��������� ���������� ������������� �������.");
	strcat(listitems, "\n4.4. ��������� �������������� ��������.");
	strcat(listitems, "\n\t\t\t5/6. {0080FF}�������� �������");
	strcat(listitems, "\n5.1. ������������� �������������� �������� �������� �������.");
	strcat(listitems, "\n5.2. ������� ����� ��������, ����������� ���-�� ����� ������������");
	strcat(listitems, "\n5.3. �������� ������� ����� ����������� ��� ����� ���������, ");
	strcat(listitems, "\n��� � ����� ��������� ����� (������������ ����������� ������).");
	strcat(listitems, "\n5.4. ������������� ��������� �������� �������: ��������������, ");
	strcat(listitems, "\n���(���������� �� �������),���(��������� ������ �� ��������� �������)");
	strcat(listitems, "\n5.5. ���� �� ���������, ��� �������� ������� ���� ��������� � ���");
	strcat(listitems, "\n��������, ��������� � �������������� ������� �� �����.");
	strcat(listitems, "\n5.6. � ������ ���������� ���-�, �������� ������� ����� ���� ���������.");
	strcat(listitems, "\n\t\t\t6/6. {0080FF}���������� ������");
	strcat(listitems, "\n6.1. ����� ������ ��������� ������� ������, �������� /help");
	strcat(listitems, "\n6.2. ����� ������, ��� �� ��������������� � ����, �������� /admins");
	strcat(listitems, "\n6.3. ����� ������ ������ ��������, ������� /question � ������������� ������");
	strcat(listitems, "\n6.4. ����� ������������ �� ������ �����������, ������� /report,");
	strcat(listitems, "\n������� �� ������ � ������� ��� ����");
	strcat(listitems, "\n6.5. ����� ���������� � ������ ���������������, �������� � /admins");
	strcat(listitems, "\n6.6. ������������ ���� �������� ����� � ����. �� ����� �������.");
	strcat(listitems, "\n_____________________________________________________________________");
	strcat(listitems, "\n{0080FF}���� �� �������� � ������� ���������, ������� ������ 'Accept'.\0");
//RegistrationSTEP1
	new caption[23+64];
	format(caption, sizeof(caption), "Rules of the %s Server", SERVERNAME);
//{0080FF}Rules of the {FFFFFF}{88AA88}V{FFFFFF}irtual {88AA88}W{FFFFFF}orld{0080FF} Server
//Rules of the {88AA88}V{FFFFFF}irtual {88AA88}W{FFFFFF}orld{0080FF} Server
	ShowPlayerDialogGap(playerid, RULES_DIALOG, DIALOG_STYLE_LIST, caption, listitems, "Accept", "Cancel");
}
stock rules_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != RULES_DIALOG) return 1;
//ShowPlayerDialogEx(playerid, 19, DIALOG_STYLE_LIST, "Role Play - "#SERVERNAME": Newspaper", listitems, "YES", "NO");
//ShowPlayerDialogGap(playerid, 19, DIALOG_STYLE_LIST, "{0080FF}Rules of the {FFFFFF}"#SERVERNAME" {0080FF}Server", listitems, "Accept", "Cancel");
	if(!response)
	{
		/*if(!GetPVarInt(playerid, "gPlayerAccount"))// && PlayerInfo[playerid][pDepositDay] == 0
		{
		    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}�� �� ������� ������� ������� - Kicked.");
		    IsKicked[playerid] = 1;
		}
		else
		{
		    help_OnPlayerKeyStateChange(playerid);//HELP(playerid);
		}*/
		help_OnPlayerKeyStateChange(playerid);//HELP(playerid);
 		return 1;
	}
	//------------------------------------------------------------------
//RegistrationSTEP1
	if(!GetPVarInt(playerid, "gPlayerAccount") && gPlayerLogged[playerid] == 0)
	{   //���� ������� �� ���������������  && PlayerInfo[playerid][pDepositDay] == 0
		//SetPVarInt(playerid, "gStatusRegistration", 1);
		if( GetPVarInt(playerid, "Intro") > 0 )//introtimer[playerid] != -1 )
		{
			for(new i; i < sizeof(Intro); i++)
			{
				TextDrawHideForPlayer(playerid, Intro[i]);
			}
			PlayerTextDrawHide(playerid, txdPositionAppend[playerid]);
			if(introtimer[playerid] != -1) { KillTimer(introtimer[playerid]); introtimer[playerid] = -1; }
			SetPVarInt(playerid, "Intro", 0);
		}
		//==============================================================
		if(gTesting == 0)
		{//���� ������������ ���������
	    	//SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �������� � ��������� �������. ��� ������ ����������� ��� ���������� ������ �������������");
			//SendClientMessage(playerid, COLOR_GREEN, "�� �������� ���������! ���� �������.");
			//SendClientMessage(playerid, COLOR_GREEN, "��� ����, ��� ���������� ����������� �������� � ����� ������ �����������!");
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ����, �� �������� � ��������� �������. ��� ������ ����������� ��� ���������� ����������� ��������.");
		    if(TutTimeCounter[playerid] == 0)
		    {   //���� ������� �� ��� � ������ ������ �� ��������, �.�. ������������ ���� 1 �����
				//SetPVarInt(playerid, "gStatusRegistration", 1);//����� ������ ���� ��������� ��������� ��������
		    	//if(GetPVarInt(playerid, "gStatusRegistration"))
		    	if(PlayerInfo[playerid][pConnectTime] == 0 && !GetPVarInt(playerid, "gPlayerAccount"))
				{
					SetPVarInt(playerid, "gOoc", 1);
					SetPVarInt(playerid, "gNews", 1);
					SetPVarInt(playerid, "gFam", 1);
					SetPVarInt(playerid, "gHidePM", 0);
					SetPVarInt(playerid, "gSport", 1);
					SetPVarInt(playerid, "gJob", 1);//��� ����
				}//����� ��� ��������
				TutTimeCounter[playerid] = 1;//��������� ���� ����� ������
				Tutorial(playerid);//RegistrationSTEP4
			}
		}
		else
		{
	    	SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �������� � ��������� �������. ��� ������ ����������� ��� ���������� ������ ������������");
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}����� ������ ���, ��� ���������� �������� ��������� �� ��� �������.");
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}�� ��������� �� ����� ������ �� ����������, ���� ��� �� �������� ������");
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}�� ������ � ��� �� ����� ���������, ����� ��� �� �������.");
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}� ������ ������, �� ������ ����� ������� � ������� � ��� ����� ������� �� ������.");
		    new listitems[] = "1. ����� �� F6, ����� /dutylist � ����� �� Enter.\n2. ����� �� F6, ����� /info � ����� �� Enter.\n3. ����� �� F6, ����� /question [�����] � ����� Enter.";//\n4. ����� �� F6, ����� /report � ����� �� Enter.
			MenuOperation[playerid] = 71;
	        ShowPlayerDialogEx(playerid, TEST_DIALOG, DIALOG_STYLE_LIST, "1/15. ��� �� ������� ����� ������ ������ ��������?", listitems, "OK", "");//RegistrationSTEP2
		}
	}
	return 1;
}


new AboutTimeCounter[MAX_PLAYERS];
stock AboutServer(playerid)
{
	new listitems[520];
    strcat(listitems, "{FFFFFF}1. {00FF00}� �������:");
	strcat(listitems, "{FFFFFF}\n2. {00FF00}������������:");
	strcat(listitems, "{FFFFFF}\n3. {00FF00}������ ����:");
	strcat(listitems, "{FFFFFF}\n4. {00FF00}���� �������:");
	strcat(listitems, "{FFFFFF}\n5. {00FF00}������ ����:");
	strcat(listitems, "{FFFFFF}\n6. {00FF00}�������:");
	strcat(listitems, "{FFFFFF}\n7. {00FF00}���������:");
	strcat(listitems, "{FFFFFF}\n8. {00FF00}��������������� �������:");
	strcat(listitems, "{FFFFFF}\n9. {00FF00}�����:");
	strcat(listitems, "{FFFFFF}\n10.{00FF00}������ � ���:");
	strcat(listitems, "{FFFFFF}\n11.{00FF00}�����, �������� �������:");
	AboutTimeCounter[playerid] = 0;
	ShowPlayerDialogEx(playerid, ABOUT_DIALOG, DIALOG_STYLE_LIST, "� �������", listitems, "OK", "�����");
}

stock about_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if(dialogid != ABOUT_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	if(response && AboutTimeCounter[playerid] == 0)
	{//���� ������� �����
	    AboutServerList(playerid, listitem+1);
	    //help_OnPlayerKeyStateChange(playerid);
	    return 1;
	}
	else if(response && AboutTimeCounter[playerid] > 0)
	{//���� ������ �����
	    AboutTimeCounter[playerid] --;//�������
	    if(AboutTimeCounter[playerid] < 1)
		{
			AboutTimeCounter[playerid] = 0;
			AboutServer(playerid);
			return 1;
		}
	}
	else if(!response && AboutTimeCounter[playerid] == 0)
	{
		help_OnPlayerKeyStateChange(playerid);
		//PlaySoundForPlayer(playerid, 5202);
		return 1;
	}//���� ������ Exit
	else if(!response && AboutTimeCounter[playerid] > 0)
	{//���� ������ �����
	    AboutTimeCounter[playerid] ++;//�������
		if(AboutTimeCounter[playerid] > 11)
		{
			//TogglePlayerSpectatingEx(playerid, 0);//����������� ������ �� ������ �������
	 		//SetPlayerPos(playerid, Unspec[playerid][sPx], Unspec[playerid][sPy], Unspec[playerid][sPz]);
	  		//TogglePlayerControllableEx(playerid, 1);//�����������
			//SetCameraBehindPlayer(playerid);
			PlaySoundForPlayer(playerid, 5202);
			return 1;
		}
	}
	AboutServerList(playerid, AboutTimeCounter[playerid]);
	return 1;
}
stock AboutServerList(playerid, listitem)
{
    AboutTimeCounter[playerid] = listitem;
	//if( AboutTimeCounter[playerid] == 0 || AboutTimeCounter[playerid] > 11 ) PlaySoundForPlayer(playerid, 5202); return 1;
	new bigmsgitem[2681];
	new caption[65];
    if(AboutTimeCounter[playerid] == 1)
    {
        strmid(caption, "1/11. � �������:", 0, 65, 65);
		strins(bigmsgitem, "\nVirtual World � ��� �� ������ RPG-������, ��� ����� ��������� �����", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������� �������� � ���� ����������� ����������� � ����������� ������� ���������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� �������, ��������� ������������� ���������� ��������� � �������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ������ ���������� ���� ������,������ �����, �����������, ������ �� ������,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��������, ��������� ����, �����, ������� ����� ������� �����������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� �������� �������������, ����������� ���������� ������ � ����������� ����������� �����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nVirtual World ���� ��� ���� �� ����� ������ � ��������� online � single ���.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��������, ������������� ������� ������� ��������� �� ������� �� ���� �������,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������ ������������� � ������� �������������� ������ �� ���� ������������� 2,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������� ������� ������������ �� �������� ������� �� ���� ����������� ���������,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nThe Sims �������� ������� ������� ������������,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� �� ���������� ������ Counter-Strike ������������ ��������� ����������� �� Paintball �����.", strlen(bigmsgitem));
	}
    else if(AboutTimeCounter[playerid] == 2)
    {
		strmid(caption, "2/11. ������������:", 0, 65, 65);
		strins(bigmsgitem, "\n������� � �� ��� ����� �������� �� ����������� ������ �� ������ �������� ������ �����", strlen(bigmsgitem));
		strins(bigmsgitem, "\n(���������, �������, ��������, ���.��������). ������������� �� ��Ѩ� ��������������� �� ��� �������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� �� ������� ������� ������ �� ��������(USE:/changepass).", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������ ������ �������� �� ��������� � �������� �������� � ����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ����������� � ������ ������ ����������(����� ��������, ���� �������� � �.�.)", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������ �������� ������: Qfg25L4Nt ������ �������: 123qwe", strlen(bigmsgitem));
	}
    else if(AboutTimeCounter[playerid] == 3)
    {
		strmid(caption, "3/11. ������ ����:", 0, 65, 65);
		strcat(bigmsgitem, "����� �� �������, �� ��������� ���� �����. ��� ���������� ��", strlen(bigmsgitem));
		strcat(bigmsgitem, "\n������������ ���������� ���������� ������� �� ��������� �������.", strlen(bigmsgitem));
		strcat(bigmsgitem, "\n� ������ ����� ������� ����������� ����� ����������� �", strlen(bigmsgitem));
		strcat(bigmsgitem, "\n���������� ��������� ����� ���������� �������.", strlen(bigmsgitem));
		strcat(bigmsgitem, "\n��� ��������� ���������� �������������� �������� /menu. � �������", strlen(bigmsgitem));
		strcat(bigmsgitem, "\n�������� ��������� ����� ����� ������������ ��������� ���������.", strlen(bigmsgitem));
		strcat(bigmsgitem, "\n��� �������� � ������� ��� (F6) ����� ����� �����, �������� /help � �.�.", strlen(bigmsgitem));
		strcat(bigmsgitem, "\n������� /menu, ����� �������� ����� '������ ������'. ���", strlen(bigmsgitem));
		strcat(bigmsgitem, "\n���������� ������ �������� ������, � ����� ������ '�������� ������'", strlen(bigmsgitem));
		strcat(bigmsgitem, "\n��� ��������� ������ �� ���", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� �� ������ �� ��������� � ������ ��������� �� ������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ������ ������ ���� � ��� ����: ������������� ������� �������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��, ��� �������, ���������� ��� ������ ������ � ���������,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ��� �� ������ ������ ������� ��������, ����� ������������� � �����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���� � ��� ����� ������ '���?', �� �������� ����� '������ ����' � ������ ��������.", strlen(bigmsgitem));
	}
    else if(AboutTimeCounter[playerid] == 4)
    {
		strmid(caption, "4/11. ���� �������:", 0, 65, 65);
 		strins(bigmsgitem, "\n1) ������� �������� � ���� ���� (F6) ��� ������ ����� (��������� ����� /) � ����� �������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������ : /help ����� ���������� Enter.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n2) ��� ��������� ��������� ���������� ������� ���� ���� (F6) ������ ������� �� ��������� ����", strlen(bigmsgitem));
		strins(bigmsgitem, "\n(/s � �������), ������� ������ � �������� ���� ���������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���� �� �������� ��� ��� �������� � ���, �� ������ �� ������������ ��������,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� ������ ������ � ���. ��� ���������� ����������� ����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� �� ���������� ������ � ������� ��� �������� /0 (����)", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� ������ ������ ����� ������� /menu, �������� ����� ������ ������, � ����� ����� ���.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n3) ����� ������ ������ ��������� ������ ������� [/help] ��� ������� ������� H", strlen(bigmsgitem));
		strins(bigmsgitem, "\n4) ���� � ��� ����� ��������� �������, �� ������� �� � [/question]", strlen(bigmsgitem));
		strins(bigmsgitem, "\n5) ������ ��� ������ ����� � ����� ����o, ����� [/gps]", strlen(bigmsgitem));
		strins(bigmsgitem, "\n6) ����������� ������ ���� ������� � ���� ��������� 24/7(������� ��������� �� ������).", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� ������ �� ������� ������� ������. ������� �� ���� � ���e���� 1 ����� - 'CellPhone'", strlen(bigmsgitem));
		strins(bigmsgitem, "\n7) � 3 ������ �� ��� ������� ����������� �����������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� ���������� �� ������������� ������� ����� Alt ��� ����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� ��������� ������ ��� ������� ������������ ������� [/help],", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� �������� ����� ��������� �����(��������) � ����������� ����� ����� 10", strlen(bigmsgitem));
		strins(bigmsgitem, "\n8) ����� � ���� �� �� ������� ����� ����������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� �� �������� ����� ������ � ���� �������������(������� ��� � TAB,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������ 2 ���� �� ���, ������� ����� �������������).", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� ��������� ������ ��� ������� ��������� ������� [/help],", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� �������� ����� ��������� �����(��������) � ����������� ����� ����� 11", strlen(bigmsgitem));
	}
    else if(AboutTimeCounter[playerid] == 5)
    {
		strmid(caption, "5/11. ������ ����:", 0, 65, 65);
		strins(bigmsgitem, "\n�� ������� ������� ��������� ���������, ������� ������� ��� �� ��������� ������ ����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� �������� � ����������� ��� ����� ������ ����� $25000, 3 lvl,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� ��������� B(�� ���� ���������), 14 ���� ��������. ��� ��������� ������� F6,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������� '/' (����� ����) � ������� tut. ������ ���������� : [/tut] � ������� Enter", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������,���� �� �� ������ ��������� ��������, �� �������� � ������ �� ����� � ���������(/gps 1013).", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� � ������ �� ������� ������� ������. ������� �� ����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ����� ������� ����� ������ �� ���� ��� �������� �� �������������!", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������, ���� ��� ��������� ���������� ���, �� ��� ����� ������ ����� ��� �������� � ���.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� ����� �������� �� ��������� ���� �������� � �����(/gps 1014)", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� ���������� �� ������(������� �� ������� ������ � ������). ��� �������� ����� ������,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������� ��� �� ����. ����� ��������������� ������� [/jobmanual] � ����������� �������� ���.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ����������� �� ������� ���������. ����� �������� � ���������(/gps 1015)", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� ������ ��������� ������(ID ������ ������� � /jobmanual).", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���� �� ��� �� ������� ����� �� ���������������, �� �� ������������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ������� ���� ����� ����������, �� ������� �� ����� ������������ � �����:", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���������(/gps 1046), �������(/gps 1049), ���������(/gps 1050), ����������(/gps 1051).", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ��� �� ������� ������������� ������� ����� ��� ������� ���������� ����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���� ��������� �������, �� ��������� �� � [/question]", strlen(bigmsgitem));
	}
    else if(AboutTimeCounter[playerid] == 6)
    {
		strmid(caption, "6/11. �������:", 0, 65, 65);
		strins(bigmsgitem, "������� - ����� ������ �������, ������� �� ������. ����� ��������� ��� ��������� SMS, ������� TAB � ��������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��������. ���� ��� ������, ��������� ������, ����� /h (����� �������� - /p). �� ������� �������� ����� ������� �����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� ������� ���-������ � ������� 30 ������, �������� ������� (F6), �������� ������ ����� � ������� �� Enter.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ���� ����� '��������' � ������� 60 ������ - � ������� ������� /s ������ �����. ���� �� ������ �������� ���-������, ", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��������� - ��� ����� '�����': /w id ������ �����. ������ ����� ��������� - 8 ������, � ������ ������ �� ����� �������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���. ���������� ��� ���, ������� �������� ������������ ��� ������� ��������� - /me ������ �����. ���� ��� ����� ", strlen(bigmsgitem));
		strins(bigmsgitem, "\n'����������' ��������� ��� ������, �� ����� ������ ��� ������� /s ����� �������, �.�. �������� ��� ������������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������ �������� ��������� ���� �������� ������ ������ ����� �����. ��� ����, ����� ������� ������� ��� - ������� /0.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ������� ��� ��������, ���� �� ����� ��������� ����� ��������� �����. ����������� ����� ����� ���������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� �� �� ������ ���������� ��������� ������. ������� � ���������(����� ������� �� ����� � �����)", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ����� � ���������� ����� ����� ������ �� ������ ��������� ������ ������, ������ ��� ��� � TAB,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ���� ������ ����� ���������, ����� �� ������ ������ �����.", strlen(bigmsgitem));
	}
    else if(AboutTimeCounter[playerid] == 7)
    {
		strmid(caption, "7/11. ���������:", 0, 65, 65);
		strins(bigmsgitem, "����� ��������� �������� ���������� ��� ���������� ����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���� ����� ����� ������� ����� ��������� ���������� ��� ������� ���� ��� �������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���������� ����� ������ ����� � ����������� � ���������� ���-������ ��� ����������� � �������� ���-���������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���� ������� ���� � ���������� ����������� � ������� 100-150% �� ��������� ����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������� /carinfo �������� ������ � ��� ��������� ���������� � ��� ����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� ���, ��� �������� ������ - ������� � ���� � /carinfo, ����� �� ���� ��������� �����������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ����, ����� ��������� ��������, �� ����� ��������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ���� �� �� ������ ������ ��� ������� �����, �� ��� ���������� �������� ��������� � ���-������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�������� �� ���������� �������� � 1 ������, �������� �� ����� � ������������� �������� �", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��������� - �� 2 ������, �������� �� �������� - � 10 ������. ��������� ������, ������ ����� ��� �� � �������� 24/7.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������ ��� ������ ��������� ��������� ������. �� ��������� ������������ �� �������������� ��������� �� ����� �����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������ ����� ����������� �������� /parking ��� �������� num4.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���� �� � �� ����������� (/unparking ��� �������� num6), � ��� ������ �� ��������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��������� �� �������� ������ ������� �� ����,�.�. �� 1 ���� ���� 100$ �� 45 - 4500$(+100$ �� ������ ���).", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�������� /lock(Alt+Space) ����� �������/������� �����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�������� (/engine) ������� ���������. ��� ����������� �������� �������� (2)", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���������� �������������. �� ��������������� ������, ���� ����� ����� �����������.", strlen(bigmsgitem));
	}
    else if(AboutTimeCounter[playerid] == 8)
    {
		strmid(caption, "8/11. ��������������� �������:", 0, 65, 65);
		strins(bigmsgitem, "\n������� ��������� � ����� �������� ����������. �� ��������� ��� �������������,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������� ������ �� ����������� ���.�������� ������, ������ ��������, ���.������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���� �� ��������� ���, �� ��� ����� ������ ���������� ���, ���� ������������,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��������� ���������� ����� - ������ FBI.  ���� � ���� ���� �������� �����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���� �� ���������, �� ���������� ��� ������ � ��� �� ������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���������� ���.����������� ������� ��� � ��������� ���������� ���� ��������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� � �������� SAN �������� ��������� ��������������� ���������.", strlen(bigmsgitem));
	}
    else if(AboutTimeCounter[playerid] == 9)
    {
		strmid(caption, "9/11. �����:", 0, 65, 65);
		strins(bigmsgitem, "\n����� - ����� ����������� ������� ���� �� �������!", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� ��� �� ������ ���������� �� ��������/����� ���� �� ������ ������, ����� �� ��������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nB�� ��� �� ������ � ��� ������: �� ������ ��������� ���� �������� [/heal]", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ������� ������ �� �������� [/givegun], �������� TV [/tv] ��� ������ ����������� � ����������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� �� ���� �� ������ ������ ���������� �� ����� �� ����", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� ����������� [/service]>>���������� ���� ��������������� ��� � ����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ��������� ������� ���� ����� ����� ������ �� � ������ ������ ���,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ��� ����� ����� ����� ��� ��������� ����� ������ �� ������� � ���������� ���� [/rentroom].", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ����� ��������� ������� ��� �� ��� ������� ������  �������� ������ ���� ����������� ���.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ����� ���� ����� ����� ����� ��������� ��� ��� ��� ����� ����� � ������ ��� [/buy].", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ���� �� ������ ������ ���������� � ������ Los Santos. ���� �� ������ ���,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� �� ������� ��������, ��� ���� ��������� ��� ����� � ����(�� ����� ������,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� ����, �� ����� ������).", strlen(bigmsgitem));
	}
    else if(AboutTimeCounter[playerid] == 10)
    {
		strmid(caption, "10/11. ������ � ���:", 0, 65, 65);
		strins(bigmsgitem, "\n������ � ��� - ��� ����������� � ������� ������� ���� �� ���������� �������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��������� ������/��� ����� ������� � ����������, ������ ����� ����� --> ������� ��� ��������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����������� � ����� ������� ��� ��� �� ������ ����������, ����� [/prop]", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� ������ ������������ ��� ������. [/bizinfo] ���� ����������� �����������  �����,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��������, ������ � ��� ����� ��� �������� ���������� ������ �������, ����� ��� �� �������������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ����� ����� ��������� ����� � �������� ��������, ����������� ��� ����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ������ ����� � ������ ����� ��������� ������� �������, �� ����� ���������� �� 40% �� 49%.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��� ���� ������� �������, ��� ������ �����������, ��� ����� ������� ������ � ��� ������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� ����, ��� ����� �������������� � �����, ��� ���������� ������� �� �����,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� �������� �������. ����� �������� �������������� � ������ �������,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���������� ��������� ������� ������ �� ����� ������. ������ ����� ���������� ���,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n����� �� ���� � ������ ������. �� ���� �� ������� �������� ������ ��-�� �������� ��� ��������� ��,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� �� ������ �������� � ����� �������� ���������� ���� � �������� [/question], ��� � ��������� �������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� �������: �� ������ ������� ������ ���� � ���������, ������� ����� �������� �������� � ����������� ���.", strlen(bigmsgitem));

	}
    else if(AboutTimeCounter[playerid] == 11)
    {
		strmid(caption, "11/11. �����, �������� �������:", 0, 65, 65);
		strins(bigmsgitem, "����������� ������� ��������� ������. ������ - �������� ������ ����� ����. �������� �� ������ �������������� �� ���", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� ������ ������� � ���������; �� ������ ����� ���������� ����������, ���, ������ ��� ��������������� ��������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n���������� ������ �����, ����������� �� ���� �� ����� � ����� ���� ����� �� ������� ��� �����. ����� ����, �����", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ������� ������������� ����� ���������� ������ ����������� ��������� � �����. ������� �� ������������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� ����� ��������� ��������������� ����. ������� ������ ������ ����� ������������ ��� �������� �����: ������ - �����", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� ��� � �������, ������� - �����, ������� �� ����� � �����. ���������� ����� �������� ������� ������ ��������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/pay id �����. ������������ ������ ������������ ����� - 1.000.000 �������� �� 3 ������. ���������� �� ����� � �����", strlen(bigmsgitem));
		strins(bigmsgitem, "\n�� ������� ������, �� �������� ����������� ��������� ������������� ������ ��������: ���������� �� �� ���� �������", strlen(bigmsgitem));
		strins(bigmsgitem, "\n������, ������ �� �� ������� � �������� ��������. ������, ��������� ������ ���� ����������� ������� ����������.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n� ����� ��������� ����� ���������� � ����� ������ ������. � ��� �� ������� ����� ������ � �������� �� ����.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n��������� � ��������� � ������� ����� Alt.", strlen(bigmsgitem));
    }
	if(strlen(bigmsgitem) > sizeof(bigmsgitem))
	{
		//��������������
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "Error8: Tutorial %s[%d], strlen(bigmsgitem): %d, sizeof(bigmsgitem): %d",
			PlayerName(playerid), playerid, strlen(bigmsgitem), sizeof(bigmsgitem));
		Log(ERROR, strings);
		return 1;
	}
	ShowPlayerDialogEx(playerid, ABOUT_DIALOG, DIALOG_STYLE_MSGBOX, caption, bigmsgitem, "�����", "�����");//RegistrationSTEP5
	return 1;
}

/*
���������� ��� ��������� �������. � �� ������ ������� ������ ���� �������� ������ �� ����

1181.1794,-1332.7791,13.5804,267.5658 ; �� ��
1470.6993,-1750.2477,15.4453,2.1933 ; ����� ��
2227.7502,-1143.9991,25.7969,339.3198 ; ������
-2039.2751,-79.0532,35.3203,353.4199 ; ��
-2428.3660,332.3707,36.9969,243.7523 ; ����� ��
-2661.6218,639.6078,14.4531,179.2284 ; �� ��
1611.5840,1817.9027,10.8203,3.7600 ; �� ��
-1641.4799,1207.9347,7.1797,305.8162 ; ���������
2742.8965,-2415.3386,13.6363,73.3673 ; ����
*/


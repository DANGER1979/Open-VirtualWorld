//#include <geolocation>

//��� ����������
#define SERIAL_LENGTH 		20

//native gpci(playerid, serial[], len); //to a_players.inc



stock CheckExistPlayer(playerid, const nameplayer[])
{//���������� ������ ��� �������� ����� � ����
	if(gPlayerLogged[playerid] == 1) return 1;
	if(strlen(nameplayer) < 6 || strlen(nameplayer) >= 20)
	{
		//SendClientMessage(playerid, COLOR_EMERALD, "������������ ���! THE WRONG NAME!");
		return -1;
	}
	new ToBase[79];//55+24�=�79
	format(ToBase, sizeof(ToBase), "SELECT `ID` FROM `players` WHERE `Name` = '%s' LIMIT 1", nameplayer);//playername);//�������� 1676 ms //LIMIT 1 - ��� �������������
	new DBResult:db_result = db_query(db_VW, ToBase);
	switch(db_num_rows(db_result))
	{
		case 0://������� ������ ���� � ���� ������
		{
			db_free_result(db_result);
			SendClientMessageEx(playerid, COLOR_RED, "CEPBEP: {33AA33}������� ������ ���� � ���� ������!");
			return 0;
		}
		case 1://��� ��� ��� ����������������
		{
			db_free_result(db_result);
			SendClientMessageEx(playerid, COLOR_RED, "CEPBEP: {33AA33}��� ��� ��� ����������������!");
			return 1;
		}
		default:
		{
//��������� ����������� � ���������� ��������, ��������� ������ ��������� � ����������
			db_free_result(db_result);
			SendClientMessageEx(playerid, COLOR_RED, "CEPBEP: {33AA33}���� ������ �� �������� (Kicked)!");
		    IsKicked[playerid] = 1;
			return -1;
		}
	}
	return -1;
}

stock rega_OnPlayerConnect(playerid, const nameplayer[])
{
	SetPVarInt(playerid, "mistaking", 3);//������������� 3 ������� �� ���� ������
	if(CheckExistPlayer(playerid, nameplayer) == 0)
	{
		//new str[50+24+3+10];
		//PlayAudioStreamForPlayerEx(playerid, "GTAV_titles.mp3");
		//TextDrawShowForPlayer(playerid, Intro[0]);
		//TextDrawShowForPlayer(playerid, Intro[1]);
		//for(new i = 0; i != 32; i++) SendClientMessage(playerid, -1, " ");
		//SetPVarInt(playerid, "Intro", 0);
		//if(introtimer[playerid] != -1) { KillTimer(introtimer[playerid]); introtimer[playerid] = -1; }
		//introtimer[playerid] = SetTimerEx("ShowIntro", 500, 0, "d", playerid);
		
		RegisterDialog(playerid);//��������� �������� �� ������� � ���� ��������
	}
	else LoginDialog(playerid);
}

stock RegisterDialog(playerid)
{   //���������� �� OnPlayerFinishInterpolateCamera, OnPlayerConnect(playerid)
	TogglePlayerSpectating(playerid, 1);//����������� ������ � ����� �������, ����� �� ��������� ������ ������ ������
//������ ��� ������ �����
	//TextDrawHideForPlayer(playerid, Intro[0]);
	if(introtimer[playerid] != -1) { KillTimer(introtimer[playerid]); introtimer[playerid] = -1; }
	SetPVarInt(playerid, "gPlayerAccount", 2);//������� ������ ��� �������
	new lH, lM, lS;	gettime(lH,lM,lS);//FixHour(hour);
	SetWorldTime(lH);
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
	    if(IsPlayerConnectedEx(i))
		{
	        SetPlayerTime(i, lH, lM);
		}
	}
	SetPVarInt(playerid, "gPlayerAccount", 0);
	//��������� ����
	SetPVarInt(playerid, "gOoc", 0); SetPVarInt(playerid, "gNews", 0);
	SetPVarInt(playerid, "gFam", 0); SetPVarInt(playerid, "gHidePM", 0);
	SetPVarInt(playerid, "gSport", 0); SetPVarInt(playerid, "gJob", 0);//��� ����
	//gMedicBill[playerid] = 0;
	//SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}����������, ������� ���� ������� email (�� ����� 34 ��������) � ������� REGISTER !!!!");
	//AudioMessage(playerid, "����������, ������� ���� ������� email � ������� REGISTER.");

	//Rules(playerid);//RegistrationSTEP0
	RegistrationSTEP6(playerid);
	return 1;
}

stock RegistrationSTEP6(playerid)
{
	GameTextForPlayerExx(playerid, "�����_����������_��", 0, 1);
	
	new bigmsgitem[618];//28 + 51+97+40+41+48+60 + 24+49+44+48  +  64+24�=�618
	strcat(bigmsgitem, "����� ���������� �� ������ ");	strcat(bigmsgitem, SERVERNAME);
	//strcat(bigmsgitem, "\n���� ������� ��� �������\n");
	format(bigmsgitem, sizeof(bigmsgitem), "%s\n{0080FF}������� ������: {FFFFFF}%s{A9C4E4}\n\n", bigmsgitem, PlayerInfo[playerid][pName]);
	strcat(bigmsgitem, "����������, ������� ����� ����� ����������� ����� \n(enter e-mail address recommend on mail.ru).\n");
	strcat(bigmsgitem, "���������, ��� �� ����� ������ �����.\n");
	//strcat(bigmsgitem, "�� ��������� ����� ������� REGISTER.\n\n");
	strcat(bigmsgitem, "��������� ��� �� ������� ������������ ������ \n");
	strcat(bigmsgitem, "� ����� ������� ������ � ������ ������, ��� ����� ������.\n");
	//strcat(bigmsgitem, "�� ����� ������ ����� ������ ���, ������� �� ������\n");
	//strcat(bigmsgitem, "������ � ���� LOGIN ��� �����.\n");
	//strcat(msgitem, "\n{A9C4E4}� ������ ������ ������, \n�� ������� ������������ ��� \n� ������� ������������ ������!");

	strcat(bigmsgitem, "\n{8CAA63}����������:\n");
	strcat(bigmsgitem, "\t- ��� ���� ��� ���������� ������������������\n");
	strcat(bigmsgitem, "\t- ��� �����������, ����������, ��������� ������\n");
	strcat(bigmsgitem, "\t- �������� ���� ������������ � ��������\n");
	strcat(bigmsgitem, "\t- ����� ��������� ����� �� ����� 34 �������\n");
	ShowPlayerDialogEx(playerid, REGISTER_DIALOG, DIALOG_STYLE_INPUT, "1/5. ����������� �����", bigmsgitem, "Register", "");//RegistrationSTEP6 "Login",
}

stock CheckExistMail(const Mail[])
{//��������� ���� �� � ���� ��� ����� �������� ����
	new ToBase[55+34];
	format(ToBase, sizeof(ToBase), "SELECT `Mail` FROM `players` WHERE `Mail`='%s' LIMIT 1", Mail);
/*	mysql_query(ToBase);	mysql_store_result();
	if(mysql_num_rows() > 0) { mysql_free_result(); return 1; }
	else { mysql_free_result(); return 0; }*/
	new DBResult:db_result = db_query(db_VW, ToBase);
	if( db_num_rows(db_result) ) {	db_free_result(db_result); return 1; }
	else { db_free_result(db_result); return 0; }
}

stock rega_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	//#pragma unused listitem
	MaleFemale_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);//RegistrationSTEP8
	CHANGEREGION_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);//RegistrationSTEP10
	REFERAL_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);//RegistrationSTEP11(playerid)
	PASS_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);//RegistrationStep12(playerid)

	if(dialogid != REGISTER_DIALOG) return 1;

	if(!response) { RegistrationSTEP6(playerid); return 1; }
	else//REGISTER
	{
		SetPVarInt(playerid, "Intro", 0);
//RegistrationSTEP6
		if(!GetPVarInt(playerid, "gPlayerAccount") && gPlayerLogged[playerid] == 0)
		{  //���� �� ��� �� ��������� ����������� � �� ������������
			if(!strlen(inputtext) || strlen(inputtext) > 34 || strfind(inputtext, "@", true) == -1)
			{//���� � �������� ���� ����������� ���� "@"
				SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}����������, ������� ���� ������� email (�� ����� 34 ��������) � ������� REGISTER !!!!");
				RegistrationSTEP6(playerid);
				return 1;
			}
			//mysql_real_escape_string(PlayerInfo[playerid][pMail], PlayerInfo[playerid][pMail]);
			if( CheckExistMail(inputtext) )
			{
				SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}����� email ������ ��� ���������� � ����!");// (Kicked)!!!");
				//IsKicked[playerid] = 1;
				RegistrationSTEP6(playerid);
				return 1;
			}
			if(strcmp(php_host, "localhost", true))
			{// ���� �� localhost
				new strHTTP[38 + 24+34];
				format(strHTTP, sizeof(strHTTP), "%s/SendMailVW/CheckMail.php?Mail=%s", HostName, inputtext);
				HTTP(playerid, HTTP_GET, strHTTP, "", "HTTP_CheckOnMail");//RegistrationSTEP7
				return 1;
			}
			else
			{
				strmid(PlayerInfo[playerid][pMail], inputtext, 0, strlen(inputtext), 34);
				RegistrationSTEP8(playerid);
				return 1;
			}
		}
	}
	return 1;
}

stock RegistrationSTEP8(playerid)
{
	new msgitem[89+MAX_PLAYER_NAME];
    format(msgitem, sizeof(msgitem), "\t\t{FFFFFF}%s\n�� ������� {0080FF}(Male){A9C4E4} ��� ������� {FF99CC}(Female) {A9C4E4}?", PlayerInfo[playerid][pName]);
	ShowPlayerDialogEx(playerid, SEX_DIALOG, DIALOG_STYLE_MSGBOX, "2/5. ����������� ����", msgitem, "Male", "Female");//RegistrationSTEP8
}
stock MaleFemale_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != SEX_DIALOG) return 1;
//RegistrationSTEP8
//ShowPlayerDialogEx(playerid, SEX_DIALOG, DIALOG_STYLE_MSGBOX, "����������� �� "#HostName, loginmsg, "Male", "Female");
	if(response)
	{
	    PlayerInfo[playerid][pSex] = Male;
	    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}��, �� ������.");
	}
	else
	{
	    PlayerInfo[playerid][pSex] = Female;
	    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, �� �������.");
	}
    //format(msgitem, sizeof(msgitem), "���� ���� ��������\t%s ?\n\nPlease enter your birthdate\n\nUse: dd.mm.yyyy\tExample: 01.01.1999:", PlayerInfo[playerid][pName]);
	//ShowPlayerDialogEx(playerid, 3, DIALOG_STYLE_INPUT, "����������� �� "#HostName, msgitem, "OK", "Cancel");;//RegistrationSTEP9

	RegistrationSTEP10(playerid);
	return 1;
}

stock RegistrationSTEP10(playerid)
{
	new listitems[600];
    strcat(listitems, "���������� ������� ���� ������(�����):\n");
   	strcat(listitems, "{FFFFFF}1\t{00FF00}�����\n{FFFFFF}2\t{00FF00}�������\n{FFFFFF}3\t{00FF00}������\n{FFFFFF}4\t{00FF00}������\n{FFFFFF}5\t{00FF00}������\n{FFFFFF}6\t{00FF00}����� ���.\n{FFFFFF}7\t{00FF00}�����");
	strcat(listitems, "\n{FFFFFF}8\t{00FF00}������\n{FFFFFF}9\t{00FF00}�������\n{FFFFFF}10\t{00FF00}�����\n{FFFFFF}11\t{00FF00}������\n{FFFFFF}12\t{00FF00}�������");
	strcat(listitems, "\n{FFFFFF}13\t{00FF00}�������\n{FFFFFF}14\t{00FF00}��������\n{FFFFFF}15\t{00FF00}���������\n{FFFFFF}16\t{00FF00}��������");
	strcat(listitems, "\n{FFFFFF}17\t{00FF00}�������\n{FFFFFF}18\t{00FF00}������\n{FFFFFF}19\t{00FF00}��������");
	ShowPlayerDialogEx(playerid, CHANGEREGION_DIALOG, DIALOG_STYLE_LIST, "3/5. ����������� ������ �� �������", listitems, "OK", "");//RegistrationSTEP10
}

stock GetOrigin(origin)
{
	new otext[20];
	new flag[3];
	if(origin == 1) { otext = "Brest";  flag = "BY"; }
	else if(origin == 2) { otext = "Vitebsk";  flag = "BY"; }
	else if(origin == 3) { otext = "Gomel";  flag = "BY"; }
	else if(origin == 4) { otext = "Grodno";  flag = "BY"; }
	else if(origin == 5) { otext = "Mogilev";  flag = "BY"; }
	else if(origin == 6) { otext = "Minsk obl";  flag = "BY"; }
	else if(origin == 7) { otext = "Minsk";  flag = "BY"; }
	else if(origin == 8) { otext = "Russia"; flag = "RU"; }
	else if(origin == 9) { otext = "Ukraina"; flag = "UA"; }
	else if(origin == 10) { otext = "Lithuania"; flag = "LT"; }
	else if(origin == 11) { otext = "Latvia"; flag = "LV"; }
	else if(origin == 12) { otext = "Estonia"; flag = "ES"; }
	else if(origin == 13) { otext = "Moldova"; flag = "MD"; }
	else if(origin == 14) { otext = "Bulgaria"; flag = "BG"; }
	else if(origin == 15) { otext = "Kazakhstan"; flag = "KZ"; }
	else if(origin == 16) { otext = "Bashkortostan"; flag = "BS"; }
	else if(origin == 17) { otext = "Israil"; flag = "IL"; }
	else if(origin == 18) { otext = "Italy"; flag = "IT"; }
	else if(origin == 19) { otext = "Germany"; flag = "DE"; }
	else { otext = "Unknown";  flag = "00"; }
	return flag;
}

stock CHANGEREGION_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	//#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != CHANGEREGION_DIALOG) return 1;
	//new msgitem[256+1];
	//new giveplayerid;
	if(!response)
	{
	    RegistrationSTEP10(playerid);
		return 1;
	}
//RegistrationSTEP10
//ShowPlayerDialogEx(playerid, 4, DIALOG_STYLE_LIST, "����������� �� "#HostName, listitems, "OK", "Cancel");
	if(listitem == 1) {
	    strmid(PlayerInfo[playerid][pOrigin], GetOrigin(listitem), 0, 3, 3);
	    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �� ������.");
	}
	else if(listitem == 2) {
	    strmid(PlayerInfo[playerid][pOrigin], GetOrigin(listitem), 0, 3, 3);
	    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �� ��������.");
	}
	else if(listitem == 3) {
	    strmid(PlayerInfo[playerid][pOrigin], GetOrigin(listitem), 0, 3, 3);
	    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �� ������.");
	}
	else if(listitem == 4) {
	    strmid(PlayerInfo[playerid][pOrigin], GetOrigin(listitem), 0, 3, 3);
	    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �� ������.");
	}
	else if(listitem == 5) {
	    strmid(PlayerInfo[playerid][pOrigin], GetOrigin(listitem), 0, 3, 3);
	    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �� �������.");
	}
	else if(listitem == 6) {
	    strmid(PlayerInfo[playerid][pOrigin], GetOrigin(listitem), 0, 3, 3);//strmid(PlayerInfo[playerid][pAge], "BY", 0, strlen("BY"), 3);//PlayerInfo[playerid][pOrigin] = 0;
	    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �� ������� �������.");
	}
	else if(listitem == 7) {
	    strmid(PlayerInfo[playerid][pOrigin], GetOrigin(listitem), 0, 3, 3);
	    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �� ������.");
	}
	//if(listitem == 0) {
	    //strmid(PlayerInfo[playerid][pAge], "BY", 0, strlen("BY"), 3);//PlayerInfo[playerid][pOrigin] = 0;
	    //PlayerInfo[playerid][pOrigin] = 1;
	    //SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �� ���������� ��������.");
	//}
	else if(listitem == 8) {
	    strmid(PlayerInfo[playerid][pOrigin], GetOrigin(listitem), 0, 3, 3);
	    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �� ������.");
	}
	else if(listitem == 9) {
	    strmid(PlayerInfo[playerid][pOrigin], GetOrigin(listitem), 0, 3, 3);
	    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �� �������.");
	}
	else if(listitem == 10) {
	    strmid(PlayerInfo[playerid][pOrigin], GetOrigin(listitem), 0, 3, 3);
	    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �� �����.");
	}
	else if(listitem == 11) {
	    strmid(PlayerInfo[playerid][pOrigin], GetOrigin(listitem), 0, 3, 3);
	    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �� ������.");
	}
	else if(listitem == 12) {
	    strmid(PlayerInfo[playerid][pOrigin], GetOrigin(listitem), 0, 3, 3);
	    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �� �������.");
	}
	else if(listitem == 13) {
	    strmid(PlayerInfo[playerid][pOrigin], GetOrigin(listitem), 0, 3, 3);
	    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �� �������.");
	}
	else if(listitem == 14) {
	    strmid(PlayerInfo[playerid][pOrigin], GetOrigin(listitem), 0, 3, 3);
	    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �� ��������.");
	}
	else if(listitem == 15) {
	    strmid(PlayerInfo[playerid][pOrigin], GetOrigin(listitem), 0, 3, 3);
	    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �� ����������.");
	}
	else if(listitem == 16) {
	    strmid(PlayerInfo[playerid][pOrigin], GetOrigin(listitem), 0, 3, 3);
	    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �� ��������.");
	}
	else if(listitem == 17) {
	    strmid(PlayerInfo[playerid][pOrigin], GetOrigin(listitem), 0, 3, 3);
	    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �� �������.");
	}
	else if(listitem == 18) {
	    strmid(PlayerInfo[playerid][pOrigin], GetOrigin(listitem), 0, 3, 3);
	    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �� ������.");
	}
	else if(listitem == 19) {
	    strmid(PlayerInfo[playerid][pOrigin], GetOrigin(listitem), 0, 3, 3);
	    SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, ���� �� �� ��������.");
	}
	//------------------------------------------------------------------
	if(PlayerInfo[playerid][pConnectTime] <= 1)
	{
    	RegistrationSTEP11(playerid);
	}
	return 1;
}


stock RegistrationSTEP11(playerid)
{
	new msgitem[318+1];//48+48+24+53+53+64+28�=�318
	strcat(msgitem, "������� ��� ����������, ������� ��������� ���\n");
	strcat(msgitem, "��� �������� ���� ������ (leave field empty).\n");
	strcat(msgitem, "\n{8CAA63}����������:\n");
	strcat(msgitem, "\t- �� ������ ������� ���������� �� ������ �������\n");
	strcat(msgitem, "\t- ��� ����� ������� (USE: accept/cancel referal)\n");
	strcat(msgitem, "\t- �� ������ ��� ������� \n��������� ����� �������� ��������,\n");
	strcat(msgitem, "\t- ���� ���� �� �������.\n");
	ShowPlayerDialogEx(playerid, REFERAL_DIALOG, DIALOG_STYLE_INPUT, "4/5. ����������� ����������", msgitem, "Teacher", "");//RegistrationSTEP11
}
stock REFERAL_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	//#pragma unused inputtext
	if(dialogid != REFERAL_DIALOG) return 1;
	new msgitem[256+1];
	new giveplayerid;
//RegistrationSTEP11
//ShowPlayerDialogEx(playerid, 5, DIALOG_STYLE_INPUT, "����������� �� "#HostName, msgitem, "OK", "Cancel");
	if(!response)
	{
	   	RegistrationSTEP11(playerid);
		return 1;
	}
	if(strlen(inputtext))
	{
	    new playername[MAX_PLAYER_NAME];
		strmid(playername, inputtext, 0, strlen(inputtext), MAX_PLAYER_NAME);
		//mysql_real_escape_string(playername, playername);
		if(CheckExistPlayer(playerid, playername) == 0)
		{
		    format(msgitem, sizeof(msgitem), "CEPBEP: {33AA33}��������, ������� ������ %s ���� � ���� ������.", playername);
   			SendClientMessage(playerid, COLOR_RED, msgitem);

    		RegistrationSTEP11(playerid);
			return 1;
		}
		giveplayerid = ReturnUser(inputtext);
		strmid(PlayerInfo[playerid][pReferal], playername, 0, strlen(playername), MAX_PLAYER_NAME);//��� ���������
		if( IsPlayerConnected(giveplayerid) && gPlayerSpawned[giveplayerid] )
		{
			format(msgitem, sizeof(msgitem), "   %s[%d] �������, ����� �� ���� ��� �����������.", PlayerInfo[playerid][pName], playerid);
			SendClientMessage(giveplayerid, COLOR_LILAC, msgitem);
			format(msgitem, sizeof(msgitem), "   ��� ����� c %s[%d] (USE: (/re)feral).", PlayerInfo[playerid][pName], playerid);
			SendClientMessage(giveplayerid, COLOR_GREY, msgitem);
			format(msgitem, sizeof(msgitem), "   ��� ����� c %s[%d] (USE: (/re)feral).", PlayerName(giveplayerid), giveplayerid);
			SendClientMessage(playerid, COLOR_GREY, msgitem);
		}
	}
	//------------------------------------------------------------------
	if(PlayerInfo[playerid][pConnectTime] == 0 && !GetPVarInt(playerid, "gPlayerAccount"))
	{
    	//SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}�������, ��� ��������� ������. ��������� ������������� �������� ������.");
    	//SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}�������, ��� ��������� ������. ");
		//OnPlayerRegister(playerid);//RegistrationSTEP12 //������ ��

		//SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}���������� ������� ������ �� ����� 20 ��������!!! ��������: ������ ������������ � ��������!!!");

		RegistrationStep12(playerid);
	}
	return 1;//RegistrationStep10
}
stock RegistrationStep12(playerid)
{
	new dlgitem[229];//46+66+22+34+37 +24�=�229
    format(dlgitem, sizeof(dlgitem), "{0080FF}������� ������: {FFFFFF}%s{A9C4E4}\n\
\n����������, ������� ������ ����:\nPlease, enter the Password:\n", PlayerInfo[playerid][pName]);
	strcat(dlgitem, "\n{8CAA63}����������:\n");
	strcat(dlgitem, "\t- ������ �� ����� 20 ��������\n");
	strcat(dlgitem, "\t- ������ ������������ � ��������\n");
	ShowPlayerDialogEx(playerid, PASS_DIALOG, DIALOG_STYLE_INPUT, "5/5. ����������� ������", dlgitem, "Register", "");
}
stock PASS_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	if(dialogid != PASS_DIALOG) return 1;
	if(!response) { RegistrationStep12(playerid); return 1; }
	
	if(!strlen(inputtext)) { RegistrationStep12(playerid); }
	else if(strlen(inputtext) > 20) { SendClientMessage(playerid, COLOR_GRAYWHITE, "������ �� ������ ��������� ������ 20 ��������!"); RegistrationStep12(playerid); }
	else
	{
		for(new i=0; i<strlen(inputtext); i++)
		{
			switch(inputtext[i])
			{
				case '0' .. '9': { continue; }
				case 'A' .. 'Z': { continue; }
				case 'a' .. 'z': { continue; }
				default:
				{   //���� ������� ������� �� 'A' .. 'Z' || 'a' .. 'z'
					SendClientMessage(playerid, COLOR_EMERALD, "ENTERING REJECTED. BAD PASSWORD!");
					SendClientMessage(playerid, COLOR_EMERALD, "Please choose another Password containing only 0-9 A-Z a-z");
					//SendClientMessage(playerid, COLOR_EMERALD, "USE: /changepass [new password]");
					RegistrationStep12(playerid);
				    return 1;
				}
			}
		}
		OnPlayerRegister(playerid, inputtext);//RegistrationSTEP12 //������ ��
	}
	return 1;
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//SpawnSTEP6
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//RegistrationSTEP12
stock OnPlayerRegister(playerid, password[]) // ���������� �� ������� /register
{   //��� �������� ����� ������� ������ - �������� //password - ����������� �������� � ������������ ����
	//#pragma unused password
	if(!IsPlayerConnected(playerid)) return 1;
	new timers = GetTickCount();
	//new newpass[20];
	//format(newpass, sizeof(newpass), "%s", generate_password(6));
	//strmid(PlayerInfo[playerid][pKey], newpass, 0, 7, 20);
	strmid(PlayerInfo[playerid][pKey], password, 0, strlen(password), 20);

	new date[16], date_d, date_m, date_y;
	getdate(date_y, date_m, date_d);
	format(date, sizeof(date), "%02d.%02d.%04d", date_d, date_m, date_y);
	if( strcmp(php_host, "localhost", true) )
	{//���� �� localhost
		new	strHTTP[85 + 24+34+24+20+16+16 + 12];
    	format(strHTTP, sizeof(strHTTP), "%s/SendMailVW/SendMail.php?Mail=%s&PlayerName=%s&Password=%s&IP=%s&DateRegister=%s",
			HostName, PlayerInfo[playerid][pMail], PlayerInfo[playerid][pName],
			PlayerInfo[playerid][pKey], PlayerInfo[playerid][pIP], date);
		HTTP(playerid, HTTP_GET, strHTTP, "", "HTTP_SendMail");//RegistrationSTEP13
		//PlaySoundForPlayer(playerid, 5201);
	}
//	else
//	{
		//new strings[MAX_STRING];
//		format(strings, sizeof(strings), "CEPBEP: {33AA33}������ '{0080FF}%s' {33AA33}������� ������������.", PlayerInfo[playerid][pKey]);//�� �������� (a..z1..2)
//		SendClientMessage(playerid, COLOR_RED, strings);
//	}
	OnPlayerCreateAccount(playerid, PlayerInfo[playerid][pName]);

//------------------------------------------------------------------------------
	new ind, Found, Clothes[MAX_SKINS];//������ ��� �������� ��������
	//pGender = PlayerInfo[playerid][pSex];
	SetPVarInt(playerid, "TypePed", NormalPed);
	for(new i=0; i<MAX_SKINS; i++)//��������� ��� �����
	{
		if(	SkinArray[i][Type_Ped] == GetPVarInt(playerid, "TypePed") &&
			SkinArray[i][Gender] == PlayerInfo[playerid][pSex])
		{   //������� ������ ��������� ������
			Clothes[ind] = i; ind ++; Found = 1;
		}//�������� � ������ ��� ID �����. �������� ���. ���������� �����
	}
	if(Found == 1)
	{   
	    new skin = random(ind-1);
		new SkinID = SkinArray[Clothes[skin]][Skin_ID];
		SetPlayerSkinEx(playerid, SkinID);
		SetPVarInt(playerid, "IsPaid", 0);
	}
//------------------------------------------------------------------------------
	gSpawn[playerid] = 0;
	SetPVarInt(playerid, "SpawnChange", 2);//�������� �� ���� ��� ������(������ ������)
//��� SetPVarInt(playerid, "SpawnChange", 1);

	PlayerInfo[playerid][pReason] = 1;//���� �������� ���������, �.�. ����� ��� �� �������
//TutTimeCounter[playerid] = 0;

	SetPlayerSpawn(playerid);//��������� �-�� ��������� ������ � ��������� ������� ������������ �� ���������� �������
	//��������� ����� OnPlayerLogin(playerid, inputtext); ������� ���������� �� ShowPlayerDialogEx
	OnPlayerStatsUpdate(playerid, 3);//������������ ���� � ���� ����� ��������� ����������, �.�. � OnPlayerLogin ��� �������� ����� �� ����

	//new strings[MAX_STRING];
	//new newpass[20];
	//format(newpass, sizeof(newpass), "%s", generate_password(6));
	//strmid(PlayerInfo[playerid][pKey], newpass, 0, 7, 20);
	//if(strlen(PlayerInfo[playerid][pKey]) < 5) return SendClientMessage(playerid, COLOR_GREY, "   ������ ���������� �������. ���������� � �������������.");

	//new dlgitem[54+67+46+27+55+53+49 +24];
//\n���������� ������� ������ '{0080FF}%s{A9C4E4}' ����:", PlayerInfo[playerid][pName], PlayerInfo[playerid][pKey]);
//�� ��������� ���� ����� ����� ������� ������ � �������� �������\n
//\n\n\t{8CAA63}����������:\n
//\t- ����� �������� ���� ����������� ������ ALT+TAB.\n
//\t- ������ ��������� �� ����� �������� ���������,\n
//\t�� ������, ��� ����� ��������� ��������� �����.

	SetPVarInt(playerid, "gOoc", 1);//����� ��� �������
	SetPVarInt(playerid, "gNews", 1);//����� �������� �������
	SetPVarInt(playerid, "gFam", 1);//�������� ��� �������
	SetPVarInt(playerid, "gSport", 1);//��� ����� �������
	SetPVarInt(playerid, "gJob", 1);//��� ������� �� ��������� �������

	new dlgitem[246];//53+74+24+34+37  +  24�=�246
	format(dlgitem, sizeof(dlgitem), "{0080FF}������� ������: {FFFFFF}%s{A9C4E4} �������\n", PlayerInfo[playerid][pName]);//PlayerInfo[playerid][pKey]);//'{0080FF}%s'{A9C4E4}
	strcat(dlgitem, "\n����������, ����������� ���� ������: \nPlease, confirm its Password:\n");
	strcat(dlgitem, "\n{8CAA63}����������:\n");
	strcat(dlgitem, "\t- ������ �� ����� 20 ��������\n");
	strcat(dlgitem, "\t- ������ ������������ � ��������\n");
	new caption[11+64];
	format(caption, sizeof(caption), "���� �� %s", SERVERNAME);
	ShowPlayerDialogEx(playerid, LOGIN_DIALOG, DIALOG_STYLE_PASSWORD, caption, dlgitem, "Login", "");//RegistrationSTEP14

//��������������
	new strtmp[MAX_STRING];
	format(strtmp, sizeof(strtmp), "End OnPlayerRegister(playerid:%d[%d])", playerid, PlayerInfo[playerid][pSQLID]);
	//SendClientMessageToAll(COLOR_YELLOW, strings);
	//SendClientMessage(playerid, COLOR_GREEN, strings);
	TestLog(OPTIM, strtmp, GetTickCount(), timers);//new timers = GetTickCount();
	return 1;
}//end OnPlayerRegister(playerid, password[])



stock OnPlayerCreateAccount(playerid, const nameplayer[])
{
	new timers = GetTickCount();
	//new newpass[64];
	//format(newpass, sizeof(newpass), "%s", generate_password(6));
	//gpci(playerid, newpass, SERIAL_LENGTH);//sizeof(serialid));
	//strmid(PlayerInfo[playerid][pKey], newpass, 0, strlen(newpass), SERIAL_LENGTH);

	new year, month, day; getdate(year, month, day);
	format(PlayerInfo[playerid][pAge], 12, "%04d-%02d-%02d", year, month, day);
	//strmid(PlayerInfo[playerid][pMail], "mail", 0, strlen("mail"), 34);
	GetPlayerIp(playerid, PlayerInfo[playerid][pIP], 16);
	if( !strcmp(PlayerInfo[playerid][pIP], "127.0.0.1", true) )
	{
		strmid(PlayerInfo[playerid][pIP], "37.212.48.112", 0, strlen("37.212.48.112"), 16);
	}
	/*new country[256], city[256], isp[256];
	GetIPCountry(PlayerInfo[playerid][pIP], country, sizeof(country));	//GetPlayerCountry(playerid, country, sizeof(country));
	GetIPISP(PlayerInfo[playerid][pIP], isp, sizeof(isp)); //GetPlayerISP(playerid, isp, sizeof(isp));
	GetPlayerCity(PlayerInfo[playerid][pIP], city, sizeof(city)); //GetPlayerCity(playerid, city, sizeof(city));
printf("City took %d ms", tickcount()-ticks);
    new str[256];
    format(str, sizeof(str), "%s: country:{FF3300}%s{FFFFFF} | isp:{1975FF}%s{FFFFFF} | city{33CC00}%s", nameplayer, country, isp, city);
    SendClientMessageToAll(-1, str);*/

	new ToBase[166 + 20+34+24+16+1+12+1+2+2+3];
	format(ToBase, sizeof(ToBase), "INSERT INTO `players` (`Name`,`Password`,`Mail`,`IP`,`Sex`,`Age`,`Origin`,`Interior`,`Virtual`,`Local`) VALUES \
('%s', '%s', '%s', '%s', %d, '%s', %d, %d, %d, %d)",
		nameplayer,
		PlayerInfo[playerid][pKey],
		PlayerInfo[playerid][pMail],
		PlayerInfo[playerid][pIP],
		PlayerInfo[playerid][pSex],
		PlayerInfo[playerid][pAge],
		PlayerInfo[playerid][pOrigin],
		PlayerInfo[playerid][pInt],
		PlayerInfo[playerid][pVirtual],
		PlayerInfo[playerid][pLocal]);
	//mysql_query(ToBase);
	db_free_result(db_query(db_VW, ToBase));
	//PlayerInfo[playerid][pSQLID] = mysql_insert_id();

//stock db_insert_id(playerid)//(const playername[])
//{//����� �������������� ������ �� ����������� �� ����
	new query[52 + 24];
	format(query, sizeof(query), "SELECT `ID`,`Name` FROM `players` WHERE `Name`='%s'", nameplayer);
	new DBResult:db_result = db_query(db_VW, query);
	if(db_num_rows(db_result))
	{
		//new Field[11];
		//db_get_field_assoc(db_result, "ID", Field, sizeof(Field) );   PlayerInfo[playerid][pSQLID] = strval(Field);
		PlayerInfo[playerid][pSQLID] = db_get_field_assoc_int(db_result, "ID");
	}
	db_free_result(db_result);

//format(strings, sizeof(strings),  "�������: %s � �������: %s �������� � ����.", nameplayer, PlayerInfo[playerid][pKey]);
//SendClientMessage(playerid, COLOR_SYSTEM, strings);
	
	SetPVarInt(playerid, "gPlayerAccount", 1);//������� ������ �������, �� ������ �� �������//��������� ���� ��� ������������ �� LOGIN �

	new strtmp[29+24+11];
	format(strtmp, sizeof(strtmp), "OnPlayerCreateAccount %s[%d] pass: %s", nameplayer, PlayerInfo[playerid][pSQLID], PlayerInfo[playerid][pKey]);
	TestLog(OPTIM, strtmp, GetTickCount(), timers);//new timers = GetTickCount();
	return PlayerInfo[playerid][pSQLID];
}



//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//SpawnSTEP6
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


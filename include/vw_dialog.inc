#define MAX_DLGITEMS 35//5+10+20
new DialogID[MAX_PLAYERS][MAX_DLGITEMS];



new gDialogStatus[MAX_PLAYERS][5];//для проверки состояния игрока для неповторения меню

stock dialog_OnPlayerConnect(playerid)
{
	gDialogStatus[playerid][0] = 0; gDialogStatus[playerid][1] = 0; gDialogStatus[playerid][2] = 0; gDialogStatus[playerid][3] = 0; gDialogStatus[playerid][4] = 0;
	//SetPVarInt(playerid, "gIdleKick", 0);
	SetPVarInt(playerid, "gShowDialog", -1);
}


//##############################################################################//
//                                                                              //
//                          ИДЕНТИФИКАТОРЫ ДИАЛОГОВ                             //
//                                                                              //
//##############################################################################//
#define REGISTER_DIALOG 1
#define LOGIN_DIALOG 2
#define SEX_DIALOG 3
#define CHANGEPASS_DIALOG 4
#define CHANGEREGION_DIALOG 5
#define REFERAL_DIALOG 6
#define PASS_DIALOG 7
#define PLMENU_DIALOG 8
#define LISTCMD_DIALOG 9
#define BACKCMD_DIALOG 10

#define DoJ_DIALOG 11

#define DRUG_DIALOG 12
#define GOLD_DIALOG 13
#define HOUSE_DIALOG 14
#define JOBMENU_DIALOG 15
#define CLEARWANTED_DIALOG 16
#define BANKOMAT_DIALOG 17
#define RULES_DIALOG 18
#define NEWS_DIALOG 19
#define QUESTION2_DIALOG 20
#define WBE_DIALOG 21
#define JOB_DIALOG 22
#define ACCEPT_DIALOG 23
#define ITEMS_DIALOG 24

#define BANK_DIALOG 25

#define SERVICE_DIALOG 26
#define HEAL_DIALOG 27
#define RACE_DIALOG 28
#define HELP_DIALOG 29
#define LIST_DIALOG 30
#define REPORT_DIALOG 31
#define BACKHELP_DIALOG 32
#define TOG_DIALOG 33
#define EXAM_DIALOG 34
#define TEST_DIALOG 35
#define ANIM_DIALOG 36
#define UPGRADE_DIALOG 37
#define COMMANDS_DIALOG 38
#define NOFUEL_DIALOG 39
#define TAB_DIALOG 40
#define HITMAN_DIALOG 41
#define SKILL_DIALOG 42
#define MDC_DIALOG 43
#define BANLIST_DIALOG 44
#define PARKINGLIFT_DIALOG 45
#define QUESTION1_DIALOG 46
#define ADVENTURE_DIALOG 47
#define SERVICEHELP_DIALOG 48
#define PAINTBALL_DIALOG 49
#define DERBILS_DIALOG 50
#define BLOODBOWL_DIALOG 50
#define INVITE_DIALOG 51
#define LOADER_DIALOG 52
#define LOADER6_DIALOG 53
#define FARMER_DIALOG 54
#define BACKLIST_DIALOG 55
#define TRASHMAN_DIALOG 56
#define DIALOG_ID_PARROT 57
/*#define DIALOG_ID_PARROT 58
#define DIALOG_ID_PARROT 59
#define DIALOG_ID_PARROT 60
#define DIALOG_ID_PARROT 61
#define DIALOG_ID_PARROT 62
#define DIALOG_ID_PARROT 63*/
#define DIALOG_ID_ELEVATOR	64
#define VEHICLE_DIALOG 65
#define AutoSalon_DIALOG 66
#define RANK_DIALOG 67
#define AUTOSCHOOL_DIALOG 68
#define MISSION_DIALOG 69
#define FERMA_DIALOG 70
#define TRUCK_DIALOG 71
#define VACANCIES_DIALOG 72
#define TUTORIAL_DIALOG 73
#define CLANS_DIALOG 74
#define RADIO_DIALOG 75
#define TRANSFER_DIALOG 76
#define PROP_DIALOG 77
#define TAXI_DIALOG 78
#define AUTOREPAIR_DIALOG 79
#define SKINS_DIALOG 80
#define FishVault_DIALOG 81
#define REDRAFT_DIALOG 82
#define MUSHROOMER_DIALOG 83
#define CARINFO_DIALOG 84
#define MINER_DIALOG 85
#define GANGVACANCIES_DIALOG 86
#define ADMINS_DIALOG 87
#define BOOKMAKER_DIALOG 88
#define WOODSMAN_DIALOG 89
#define FIREMAN_DIALOG 90
#define VEHLIST_DIALOG 91
#define SELLCAR_DIALOG 92
#define USEITEMS_DIALOG 93
#define BIGBOARD_DIALOG1 94
#define BIGBOARD_DIALOG2 95
#define JOB2MENU_DIALOG 96
#define BUS_DIALOG 97
#define RENTCAR_DIALOG 98
#define BUYVEHICLE_DIALOG 99

#define ABOUT_DIALOG 100
#define CARMECHANIC_DIALOG 101
#define CALL_DIALOG 102
#define GIVELIC_DIALOG 103
#define BACKPLMENU_DIALOG 104
#define GPS_DIALOG 105
#define GPS_DIALOG2 106
#define SHOP_DIALOG 107
#define FTASK_DIALOG 108
#define BOX_DIALOG 109
#define MEGAPHONE_DIALOG 110
#define CHECK_DIALOG 111
#define BIZ_DIALOG 112
#define FILLCAR_DIALOG 113
#define ADMIN_DIALOG 114
#define BACKADMIN_DIALOG 115
#define DEVELOPER_DIALOG 116
#define PLAYERINFO_DIALOG 117
#define ADMIN_MENU_DIALOG 118
#define HOUSE_CONTROL_MENU 119
#define BIZ_CONTROL_MENU 120
#define EXCHANGE_DIALOG 121
#define TRAFIC_DIALOG 122

#define FBI_DIALOG 123
#define FBI_DIALOG2 124

#define HOTEL_DIALOG 125
#define HOTEL1_DIALOG 126
#define HOTEL2_DIALOG 127
#define HOTEL3_DIALOG 128

#define MAYOR_LIFT 129
#define BAR_DIALOG 130
#define BURGER_DIALOG 131
#define WEAPONMAG_DIALOG 132
#define WEAPONMAG_DIALOG2 133
#define REST_DIALOG 134
#define LIC_DIALOG 135
#define LSPD_DIALOG 136

#define MARRIAGE_DIALOG 137
#define SETINT_DIALOG 138

#define d_accses1   139
#define d_accses2   140
#define d_accses4   142
#define d_items1    143
#define d_items2    144
#define d_items3    145
#define d_items4    146
#define d_male_shop1    147


#define WINDOWS_DIALOG  148
#define DOORS_DIALOG    149

#define SOUND_DIALOG 151

#define DIALOG100 152
#define H_DIALOG 1018
#define TAB_DIALOG2 1019








//##############################################################################//
//                                                                              //
//                                БЛОКИ АВТОЗАМЕНЫ                              //
//                                                                              //
//##############################################################################//



forward ShowPlayerDialogGap(playerid, dialogid, style, caption[], info[], button1[], button2[]);
public ShowPlayerDialogGap(playerid, dialogid, style, caption[], info[], button1[], button2[])
{   //для запрета показа диалога при открытом диалоге
	if(GetPVarInt(playerid, "gShowDialog") != -1)
	{
		format(strings, sizeof(strings), "  dialogid[%d] заблокировано. gShowDialog=%d", dialogid, GetPVarInt(playerid, "gShowDialog"));
		SendClientMessage(playerid, COLOR_GREY, strings);
		return 1;
	}//если диалог у игрока открыт, то выйти, т.е. не загружать заново

	/*if(	CurState[playerid] == PLAYER_STATE_DRIVER &&
		// && GetSeatVehiclePlayer(nCarID[playerid], 0) != INVALID_PLAYER_ID
		GetVehicleSpeed(nCarID[playerid]) > 10)
	{ 	//для запрета показа диалого при скорости машины больше 10
		SetPVarInt(playerid, "gShowDialog", -1);
		//TogglePlayerControllableEx(playerid, 1);//размораживает
		format(strings, sizeof(strings), "  dialogid[%d] заблокировано. Скорость машины больше 10 !", dialogid);
		SendClientMessage(playerid, COLOR_GREY, strings);
 		return 1;
    }*/
	//SetPVarInt(playerid, "gShowDialog", dialogid);
	return ShowPlayerDialogEx(playerid, dialogid, style, caption, info, button1, button2);
}


stock ShowPlayerDialogEx(playerid, dialogid, style, caption[], info[], button1[], button2[])
{   //для проверки переменных диалога с озвучкой
	if(CHECKING[DialogResponse])
 	{
		format(strings, sizeof(strings), "ShowPlayerDialogEx(playerid:%d, dialogid:%d[%d], style:%d, caption:%s)",
			playerid, dialogid, GetPVarInt(playerid, "gShowDialog"), style, caption);
		SendClientMessage(playerid, COLOR_YELLOW, strings);
	}
	if( dialogid != -1 && (!strlen(caption) ||
		//(style == DIALOG_STYLE_LIST && strlen(caption) > 70) ||
		!strlen(info) || !strlen(button1)) )
	{
		SetPVarInt(playerid, "gShowDialog", -1);
		format(strings, sizeof(strings),
"Error3: dialogid:%d strlen(caption):%d[%s], strlen(info):%d, strlen(button1):%d[%s] player:%s",
			dialogid, strlen(caption), caption, strlen(info), strlen(button1), button1, PlayerName(playerid));
		SendClientMessage(playerid, COLOR_GREY, strings);
		Log(ERROR, strings);

		new Float:slx, Float:sly, Float:slz;
		GetPlayerHealth(playerid, LastHealth[playerid]);
		GetPlayerPos(playerid, slx, sly, slz);
		SetPlayerPos(playerid, slx, sly, slz+5.0);
		PlayerPlaySound(playerid, 1130, slx, sly, slz+5.0);//шлепок #define SOUND_PUNCH_PED 	1130

		format(strings, sizeof(strings), "%s[%d] kicked, reason: Error DialogID", PlayerName(playerid),playerid, strings);
		SendSystemMessage(COLOR_MAROON, strings, 1);
		//IsKicked[playerid] = 1;
	 	return 1;
	}

	/*if(dialogid == LOGIN_DIALOG)
	{	//ShowPlayerDialogEx(playerid, LOGIN_DIALOG, DIALOG_STYLE_INPUT, "Регистрация на "#HostName, msgitem, "Login", "Register");
		if(introtimer[playerid] != -1) { KillTimer(introtimer[playerid]); introtimer[playerid] = -1; }
		//SetPVarInt(playerid, "Intro", 0);
	}*/

	SetPVarInt(playerid, "gShowDialog", dialogid);
	PlaySoundForPlayer(playerid, 5201);
	return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
}


stock dialog_OnDialogResponse(playerid, dialogid, inputtext[])
{
	//--------------------------------------------------------------------------
	new msgitem[256+1];
	if(GetPVarInt(playerid, "gShowDialog") != dialogid && dialogid != -1 && dialogid < 1000)
	{	//GetPVarInt(playerid, "gShowDialog") != -1
		format(msgitem, sizeof(msgitem), "Error9: dialogid:%d не соответствует gShowDialog:%d у %s[%d]",
			dialogid, GetPVarInt(playerid, "gShowDialog"), PlayerName(playerid), playerid);
//игрок грузит dialogid:40, а по коду ему должен загрузиться gShowDialog:-1
		//format(msgitem, sizeof(msgitem), "Error3: dialogid:%d strlen(caption):%d[%s], strlen(info):%d, strlen(button1):%d[%s] player:%s",
		//	dialogid, strlen(caption), caption, strlen(info), strlen(button1), button1, PlayerName(playerid));

		Log(ERROR, msgitem);
		SendAllAdminMessage(COLOR_RED, msgitem, 1);
		return 1;
	}
	if(strlen(inputtext) > 128)
	{
		format(msgitem, sizeof(msgitem), "Error10: dialogid:%d strlen:%d", dialogid, strlen(inputtext));
		Log(ERROR, msgitem);
	    return 1;
	}
//РАБОТАЕТ
	while(strfind(inputtext, "%", true) != -1)
	{
		strdel(inputtext, strfind(inputtext, "%", true), strfind(inputtext, "%", true)+2);
	}
	//--------------------------------------------------------------------------
	return 1;
}

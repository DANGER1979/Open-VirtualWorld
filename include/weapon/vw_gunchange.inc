//#include <a_samp>

#define TOTAL_ITEMS_WEAPONS 		42//42//6 * 7
#define SELECTION_ITEMS_WEAPONS 	42//кол-во иконок на странице
#define ITEMS_WEAPON_COL  			6//кол-во столбцов
#define ITEMS_WEAPON_LINE  			7//кол-во строк

//координата левого верхнего угла фона
#define WeaponIcon_X   	16.0
#define WeaponIcon_Y   	118.0
//габарит фона
#define WeaponTex_WIDTH    	114.0
#define WeaponTex_HEIGHT   	0.0
//размер квадрата со скином
#define SPRITE_WEAP_X    	31.0
#define SPRITE_WEAP_Y    	27.0

new Text:WeaponText[TOTAL_ITEMS_WEAPONS];
new Text:WeaponIcon[TOTAL_ITEMS_WEAPONS];
new Text:WeaponHeader;
new Text:WeaponBackground;

enum weaponinfo {
	g_id,
	g_slot,
	g_model,
    g_name[32],
	g_price,
	g_ammo,
    g_sprite[24]
};

#if defined samp03DL//samp03DL_svr_R1_win32

//замениваем weapons на mdl-2005
new WeaponList[TOTAL_ITEMS_WEAPONS][weaponinfo] = {
//{0, 0, 0, 		"Fist", 			100, 1, 	"mdl-2005:0"},
{1, 0, 331, 	"Brass Knuckles", 	100, 1, 	"mdl-2005:1"},
{2, 1, 333, 	"Golf Club", 		10000, 1, 	"mdl-2005:2"},
{3, 1, 334, 	"Nightstick", 		150, 1, 	"mdl-2005:3"},
{4, 1, 335, 	"Knife", 			400, 1,		"mdl-2005:4"},
{5, 1, 336, 	"Baseball bat", 	150, 1, 	"mdl-2005:5"},
{6, 1, 337, 	"Shovel", 			1000, 1, 	"mdl-2005:6"},
{7, 1, 338, 	"Pool Cue", 		200, 1, 	"mdl-2005:7"},
{8, 1, 339, 	"Katana", 			150, 1, 	"mdl-2005:8"},
{9, 1, 341, 	"Chainsaw", 		500, 1, 	"mdl-2005:9"},
	//{10, 10, 321, 	"Purple Dildo", 	1000, 1,	"mdl-2005:10"},
	//{11, 10, 322, 	"Small Vibrator", 	1000, 1,	"mdl-2005:11"},
	//{12, 10, 323, 	"Large Vibrator",	1000, 1,	"mdl-2005:12"},
	{13, 10, 324, 	"Silver Vibrator", 	1000, 1,	"mdl-2005:13"},
{14, 10, 325, 	"Flowers", 			800, 8, 	"mdl-2005:14"},
{15, 10, 326, 	"Cane", 			200, 1, 	"mdl-2005:15"},
{16, 8, 342, 	"Grenade", 			800, 8, 	"mdl-2005:16"},
{17, 8, 343, 	"Tear Gas", 		800, 8, 	"mdl-2005:17"},
{18, 8, 344, 	"Molotov", 			800, 3, 	"mdl-2005:18"},

{22, 2, 346, 	"Colt '45", 		200, 30, 	"mdl-2005:22"},
{23, 2, 347, 	"Silenced", 		1000, 15, 	"mdl-2005:23"},
{24, 2, 348, 	"Desert Eagle", 	1200, 20, 	"mdl-2005:24"},
{25, 3, 349, 	"Shotgun", 			800, 70, 	"mdl-2005:25"},
{26, 3, 350, 	"Sawnoff", 			800, 30, 	"mdl-2005:26"},
{27, 3, 351, 	"S.P.A.S", 			2700, 25,	"mdl-2005:27"},
{28, 4, 352, 	"Micro SMG", 		2400, 70, 	"mdl-2005:28"},
{29, 4, 353, 	"MP5", 				2000, 300,	"mdl-2005:29"},
{30, 5, 355, 	"AK-47", 			5000, 100, 	"mdl-2005:30"},
{31, 5, 356, 	"M4", 				4000, 100, 	"mdl-2005:31"},
{32, 4, 372, 	"Tec-9", 			500, 30, 	"mdl-2005:32"},
{33, 6, 357, 	"Country Rifle", 	4000, 50, 	"mdl-2005:33"},
{34, 6, 358, 	"Sniper Rifle", 	3400, 50, 	"mdl-2005:34"},
{35, 7, 359, 	"RPG", 				24000, 10,	"mdl-2005:35"},
{36, 7, 360, 	"HS Rocket", 		2400, 10, 	"mdl-2005:36"},
{37, 7, 361,	"Flamethrower", 	150, 1, 	"mdl-2005:37"},
{38, 7, 362, 	"Minigun", 			24000, 100, "mdl-2005:38"},
{39, 8, 363, 	"Satchel", 			800, 8, 	"mdl-2005:39"},
{40, 12, 364, 	"Detonator", 		2000, 1, 	"mdl-2005:40"},
{41, 9, 365, 	"Spraycan", 		200, 50, 	"mdl-2005:41"},
{42, 9, 366, 	"Fire Extinguiser", 200, 1, 	"mdl-2005:42"},
{43, 9, 367, 	"Photo Camera", 	500, 1, 	"mdl-2005:43"},
{44, 11, 368, 	"Night Vision", 	2400, 1, 	"mdl-2005:44"},
{45, 11, 369, 	"IR Goggles", 		2400, 1, 	"mdl-2005:45"},
{46, 11, 371, 	"Parachute", 		1000, 1, 	"mdl-2005:46"},

{48, 0, 370, 	"JetPack", 			10000, 1,	"mdl-2005:JetPack"},
{52, 0, 0, 		"CellPhone", 		2400, 1, 	"mdl-2005:CellPhone"}
};

#else//samp037svr_win32

new WeaponList[TOTAL_ITEMS_WEAPONS][weaponinfo] = {
//{0, 0, 0, 		"Fist", 			100, 1, 	"weapons:0"},
{1, 0, 331, 	"Brass Knuckles", 	100, 1, 	"weapons:1"},
{2, 1, 333, 	"Golf Club", 		10000, 1, 	"weapons:2"},
{3, 1, 334, 	"Nightstick", 		150, 1, 	"weapons:3"},
{4, 1, 335, 	"Knife", 			400, 1,		"weapons:4"},
{5, 1, 336, 	"Baseball bat", 	150, 1, 	"weapons:5"},
{6, 1, 337, 	"Shovel", 			1000, 1, 	"weapons:6"},
{7, 1, 338, 	"Pool Cue", 		200, 1, 	"weapons:7"},
{8, 1, 339, 	"Katana", 			150, 1, 	"weapons:8"},
{9, 1, 341, 	"Chainsaw", 		500, 1, 	"weapons:9"},
	//{10, 10, 321, 	"Purple Dildo", 	1000, 1,	"weapons:10"},
	//{11, 10, 322, 	"Small Vibrator", 	1000, 1,	"weapons:11"},
	//{12, 10, 323, 	"Large Vibrator",	1000, 1,	"weapons:12"},
	{13, 10, 324, 	"Silver Vibrator", 	1000, 1,	"weapons:13"},
{14, 10, 325, 	"Flowers", 			800, 8, 	"weapons:14"},
{15, 10, 326, 	"Cane", 			200, 1, 	"weapons:15"},
{16, 8, 342, 	"Grenade", 			800, 8, 	"weapons:16"},
{17, 8, 343, 	"Tear Gas", 		800, 8, 	"weapons:17"},
{18, 8, 344, 	"Molotov", 			800, 3, 	"weapons:18"},

{22, 2, 346, 	"Colt '45", 		200, 30, 	"weapons:22"},
{23, 2, 347, 	"Silenced", 		1000, 15, 	"weapons:23"},
{24, 2, 348, 	"Desert Eagle", 	1200, 20, 	"weapons:24"},
{25, 3, 349, 	"Shotgun", 			800, 70, 	"weapons:25"},
{26, 3, 350, 	"Sawnoff", 			800, 30, 	"weapons:26"},
{27, 3, 351, 	"S.P.A.S", 			2700, 25,	"weapons:27"},
{28, 4, 352, 	"Micro SMG", 		2400, 70, 	"weapons:28"},
{29, 4, 353, 	"MP5", 				2000, 300,	"weapons:29"},
{30, 5, 355, 	"AK-47", 			5000, 100, 	"weapons:30"},
{31, 5, 356, 	"M4", 				4000, 100, 	"weapons:31"},
{32, 4, 372, 	"Tec-9", 			500, 30, 	"weapons:32"},
{33, 6, 357, 	"Country Rifle", 	4000, 50, 	"weapons:33"},
{34, 6, 358, 	"Sniper Rifle", 	3400, 50, 	"weapons:34"},
{35, 7, 359, 	"RPG", 				24000, 10,	"weapons:35"},
{36, 7, 360, 	"HS Rocket", 		2400, 10, 	"weapons:36"},
{37, 7, 361,	"Flamethrower", 	150, 1, 	"weapons:37"},
{38, 7, 362, 	"Minigun", 			24000, 100, "weapons:38"},
{39, 8, 363, 	"Satchel", 			800, 8, 	"weapons:39"},
{40, 12, 364, 	"Detonator", 		2000, 1, 	"weapons:40"},
{41, 9, 365, 	"Spraycan", 		200, 50, 	"weapons:41"},
{42, 9, 366, 	"Fire Extinguiser", 200, 1, 	"weapons:42"},
{43, 9, 367, 	"Photo Camera", 	500, 1, 	"weapons:43"},
{44, 11, 368, 	"Night Vision", 	2400, 1, 	"weapons:44"},
{45, 11, 369, 	"IR Goggles", 		2400, 1, 	"weapons:45"},
{46, 11, 371, 	"Parachute", 		1000, 1, 	"weapons:46"},

{48, 0, 370, 	"JetPack", 			10000, 1,	"weapons:JetPack"},
{52, 0, 0, 		"CellPhone", 		2400, 1, 	"weapons:CellPhone"}
};
#endif




stock CreateWeaponText(ID, Float:Xpos, Float:Ypos, Float:width, Float:height, Text[])
{
	WeaponText[ID] = TextDrawCreateEx(Xpos, Ypos, Text);
	TextDrawBackgroundColor(WeaponText[ID], 255);
	TextDrawFont(WeaponText[ID], 1);
	TextDrawLetterSize(WeaponText[ID], 0.219999, 0.699998);
	TextDrawColor(WeaponText[ID], -1);
	TextDrawSetOutline(WeaponText[ID], 1);
	TextDrawSetProportional(WeaponText[ID], 1);
	TextDrawUseBox(WeaponText[ID], 1);
	TextDrawBoxColor(WeaponText[ID], 255);
	TextDrawTextSize(WeaponText[ID], width, height);
}

stock CreateWeaponIcon(ID, modelname[], Float:Xpos, Float:Ypos)
{
	//WeaponIcon[ID] = TextDrawCreateEx(Xpos, Ypos, "HUD:fist");//Text);//"weapons:30"
	WeaponIcon[ID] = TextDrawCreateEx(Xpos, Ypos, modelname);
	TextDrawBackgroundColor(WeaponIcon[ID], 255);
	TextDrawFont(WeaponIcon[ID], TEXT_DRAW_FONT_SPRITE_DRAW);
	TextDrawLetterSize(WeaponIcon[ID], 0.500000, 1.000000);
	TextDrawColor(WeaponIcon[ID], -1);
	TextDrawSetOutline(WeaponIcon[ID], 0);
	TextDrawSetProportional(WeaponIcon[ID], 1);
	TextDrawSetShadow(WeaponIcon[ID], 1);
	TextDrawUseBox(WeaponIcon[ID], 1);
	TextDrawBoxColor(WeaponIcon[ID], 255);
	TextDrawTextSize(WeaponIcon[ID], SPRITE_WEAP_X, SPRITE_WEAP_Y);
	TextDrawSetSelectable(WeaponIcon[ID], true);
}


stock CreateWeaponBackground()
{
	WeaponBackground = TextDrawCreateEx(631.000000, 110.000000, "~~");
	TextDrawBackgroundColor(WeaponBackground, 255);
	TextDrawFont(WeaponBackground, 1);
	TextDrawLetterSize(WeaponBackground, 0.500000, 24.499998);
	TextDrawColor(WeaponBackground, -1);
	TextDrawSetOutline(WeaponBackground, 0);
	TextDrawSetProportional(WeaponBackground, 1);
	TextDrawSetShadow(WeaponBackground, 1);
	TextDrawUseBox(WeaponBackground, 1);
	TextDrawBoxColor(WeaponBackground, 910773960);
	TextDrawTextSize(WeaponBackground, 9.0, 0.0);
}

stock CreateWeaponHeader()
{
	WeaponHeader = TextDrawCreateEx(220.000000, 110.000000, "Welcome to Ammu-Nation!");
	TextDrawBackgroundColor(WeaponHeader, 255);
	TextDrawFont(WeaponHeader, 2);
	TextDrawLetterSize(WeaponHeader, 0.339998, 0.899999);
	TextDrawColor(WeaponHeader, -1);
	TextDrawSetOutline(WeaponHeader, 1);
	TextDrawSetProportional(WeaponHeader, 1);
}

//==============================================================================

//stock gunchange_CreateWeaponMenu()
//stock gunchange_OnFilterScriptInit()
stock gunchange_OnGameModeInit()
{//создаём только при старте мода или скрипта
	CreateWeaponHeader();
	CreateWeaponBackground();
	for(new i=0, count=0, calculation=0; i < SELECTION_ITEMS_WEAPONS; i++)
	{//заполняем сверху вниз, слева на право, i-счётчик ячеек
		if(i % ITEMS_WEAPON_LINE == 0 && i ^ 0) count++;//если i кратно ITEMS_WEAPON_LINE, то добавляем count=count+1
		//счётчик строк - через каждые ITEMS_WEAPON_LINE - переходим на следующий столбец
		calculation = 30 * (i - (ITEMS_WEAPON_LINE * ((54 + (101 * count)) / 101)));//смещение следующей по Y

		new str[14 + 32+5+6+4+3];
		format(str, sizeof(str), "%s~n~$%d~n~%d",
			WeaponList[i][g_name], WeaponList[i][g_price], WeaponList[i][g_ammo]),
		//print(str);

		CreateWeaponText(i, 							WeaponIcon_X+38 + (101 * count), WeaponIcon_Y+5 + calculation, WeaponTex_WIDTH + (101.0 * count), WeaponTex_HEIGHT, str);
		CreateWeaponIcon(i, WeaponList[i][g_sprite], 	WeaponIcon_X + (101 * count), WeaponIcon_Y + calculation);
	}
}


stock gunchange_OnGameModeExit()
{//уничтожаем только при перезагрузке мода или скрипта
	for(new j = 0; j < GetMaxPlayers(); j++)
	{
		if(!IsPlayerConnected(j)) continue;
		if(GetPVarInt(j, "weapon_active") == 1)
		{
			SetPVarInt(j, "weapon_active", 0);
			TextDrawHideForPlayer(j, WeaponHeader);
			TextDrawHideForPlayer(j, WeaponBackground);
			for(new i=0; i < TOTAL_ITEMS_WEAPONS; i++) TextDrawHideForPlayer(j, WeaponText[i]);
			for(new i=0; i < TOTAL_ITEMS_WEAPONS; i++) TextDrawHideForPlayer(j, WeaponIcon[i]);
			//CancelSelectTextDraw(j);
			//DeletePVar(j, "weapon_active");
		}
	    //SetPVarInt(j, "weapon_active", 0);
	}
    for(new i=0; i < TOTAL_ITEMS_WEAPONS; i++)
	{
    	TextDrawDestroyEx(WeaponText[i]);
    	TextDrawDestroyEx(WeaponIcon[i]);
		WeaponText[i] = Text:INVALID_TEXT_DRAW;
    	WeaponIcon[i] = Text:INVALID_TEXT_DRAW;
    }
   	TextDrawDestroyEx(WeaponBackground);
   	TextDrawDestroyEx(WeaponHeader);
    WeaponBackground = Text:INVALID_TEXT_DRAW;
    WeaponHeader = Text:INVALID_TEXT_DRAW;

}

stock gunchange_ShowWeaponMenu(playerid)
{
	if(GetPVarInt(playerid, "weapon_active") == 1)
	{
		SetPVarInt(playerid, "weapon_active", 0);
		//CancelSelectTextDraw(playerid);
		TextDrawHideForPlayer(playerid, WeaponHeader);
		TextDrawHideForPlayer(playerid, WeaponBackground);
		for(new i=0; i < TOTAL_ITEMS_WEAPONS; i++) TextDrawHideForPlayer(playerid, WeaponText[i]);
		for(new i=0; i < TOTAL_ITEMS_WEAPONS; i++) TextDrawHideForPlayer(playerid, WeaponIcon[i]);
		PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
		return 1;
	}
	SetPVarInt(playerid, "weapon_active", 1);
	SendClientMessage(playerid, -1, "CEPBEP: {00ccff}Если у вас отсутствуют изображения оружия при установки оружия через админку");
    SendClientMessage(playerid, -1, "CEPBEP: {33AA33}Пскопируйте {0080FF}weapons.txd{33AA33} в папку {FFFFFF}GTA San Andreas/models/txd/!");
	SendClientMessage(playerid, -1, "CEPBEP: {33AA33}Cкачать его можно с https://vk.com/samp_virtualworld");

	TextDrawShowForPlayer(playerid, WeaponHeader);
	TextDrawShowForPlayer(playerid, WeaponBackground);
	for(new i=0; i < TOTAL_ITEMS_WEAPONS; i++) TextDrawShowForPlayer(playerid, WeaponText[i]);
	for(new i=0; i < TOTAL_ITEMS_WEAPONS; i++) TextDrawShowForPlayer(playerid, WeaponIcon[i]);
	PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
	SelectTextDraw(playerid, 0xA3B4C5FF);
	return 1;
}
	
/*stock gunchange_OnPlayerConnect(playerid)
{
	#pragma unused playerid
	//gunchange_DestroyWeaponMenu();//иначе будет уничтожать при каждом вхоже игрока

}*/

//Не используйте CancelSelectTextDraw безоговорочно в рамках этой функции обратного вызова. Это приводит к бесконечному циклу.
//public OnPlayerClickTextDraw(playerid, Text:clickedid)//(0xFFFF)
stock gunchange_OnPlayerClickTextDraw(playerid, Text:clickedid)//(0xFFFF)
{
   	//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	//SendClientMessage(playerid, -1, "CEPBEP: {33AA33}OnPlayerClickTextDraw: {00ccff}gunchange");
	
   	if(GetPVarInt(playerid, "weapon_active") == 0) return 1;//если меню не активна, то выйти, т.е. работать только при активной менюшке

	// Handle: They cancelled (with ESC)
	if(clickedid == Text:INVALID_TEXT_DRAW)	//if(!(_:clickedid ^ 0xFFFF))	//if(clickedid == 65535)//(0x00FFFF)
	{
		//SendClientMessage(playerid, -1, "CEPBEP: {33AA33}ПРОВЕРКА{00ccff}2");
        SetPVarInt(playerid, "weapon_active", 0);
 		TextDrawHideForPlayer(playerid, WeaponHeader);
		TextDrawHideForPlayer(playerid, WeaponBackground);
		for(new i=0; i < TOTAL_ITEMS_WEAPONS; i++) TextDrawHideForPlayer(playerid, WeaponText[i]);
		for(new i=0; i < TOTAL_ITEMS_WEAPONS; i++) TextDrawHideForPlayer(playerid, WeaponIcon[i]);
		PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
		//CancelSelectTextDraw(playerid);
		
 		SendClientMessage(playerid, -1, "{00ccff}Вы нажали ESC.");
        return 1;
	}

	for(new i=0; i < TOTAL_ITEMS_WEAPONS; i++)
	{
		if(clickedid == WeaponIcon[i])
		{
		    if(i == 40)
		    {
		    	//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
		    }
		    else if(i == 41)
		    {
		        //SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
				SetPlayerAttachedObject(playerid, MOBILE_SLOT, 330, 6); // 4 = слот, 330 = модель телефона, 6 = правая рука
				SendClientMessage(playerid, 0xFFFFFFFF, "Подсказка: нажми {FFFF00}~k~~PED_SPRINT~{FFFFFF}, чтобы спрятать телефон.");
				/*new str[128];
				strcat(str,"Подсказка: нажми {FFFF00}");
				strcat(str, RusToGame("~k~~PED_SPRINT~"));
				strcat(str, GameToRus("~k~~PED_SPRINT~"));
				strcat(str,"{FFFFFF}, чтобы спрятать телефон.");
				SendClientMessage(playerid, 0xFFFFFFFF, str );*/
		    }
		    else
		    {
				new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
				GivePlayerWeapon(giveplayerid, WeaponList[i][g_id], WeaponList[i][g_ammo]);
				new str[128];
				format(str, sizeof(str), "AdmCmd: %s give %s's getgun %d with %d ammunition", PlayerName(playerid), PlayerName(giveplayerid), WeaponList[i][g_id], WeaponList[i][g_ammo]);
		  		//Log(ADMINLOG, strcmd);
				//SendAllAdminMessage(COLOR_RED, strcmd, 4);
				SendClientMessage(playerid, -1, str);
			}
			//format(str, sizeof(str), "{00ccff}Вы нажали на WeaponIcon[%i]", i);
			//SendClientMessage(playerid, -1, str);
			break;
			//return 1;
		}
	}
	return 1;
}


stock gunchange_OnPlayerKeyState(playerid)//_SPRINT
{
	if(IsPlayerAttachedObjectSlotUsed(playerid, MOBILE_SLOT))
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
		SetTimerEx("STOPUSECELLPHONE", 2000, 0, "d", playerid);//разовый таймер
	}
}

forward STOPUSECELLPHONE(playerid);
public STOPUSECELLPHONE(playerid)
{
	RemovePlayerAttachedObject(playerid, MOBILE_SLOT);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
}

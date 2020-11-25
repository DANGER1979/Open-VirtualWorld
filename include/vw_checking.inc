/*
 *            vw_checking v1.0
 *       (c) Copyright 2017-2018 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (danger1979@mail.ru)
 * @date      : 26.01.2017
 * @update    : 10.11.2018
 *
 * This file is provided as is (no warranties).
 * Тут проверяем не только срабатывание ф-ий, но и присваивание переменных
 */



//#include <a_samp>
//new strings[256+1];



/*
public OnFilterScriptInit()
{
	print("OnFilterScriptInit: vw_inspect");
	print("_____________________________________________");
	print(" ");
	return 0;
}

public OnFilterScriptExit()
{
	print("OnFilterScriptExit: vw_inspect");
	print("_____________________________________________");
	print(" ");
	return 0;
}*/


stock checking_OnGameModeInit() //обязательно прописываем 	SendRconCommand("reloadfs GE");
{
	CHECKING[PlayerConnect] = true;
	CHECKING[PlayerStateChange] = false;
	CHECKING[PlayerRequestClass] = true;
	CHECKING[PlayerRequestSpawn] = false;
	CHECKING[PlayerSpawn] = true;
	CHECKING[PlayerDeath] = false;
	CHECKING[PlayerDisconnect] = false;
	
	CHECKING[VehicleSpawn] = false;
	CHECKING[VehicleDeath] = false;
	CHECKING[PlayerTxt] = false;
	CHECKING[PlayerCommandText] = false;
	CHECKING[PlayerEnterVehicle] = false;
	CHECKING[PlayerExitVehicle] = false;

	CHECKING[PlayerEnterCheckpoint] = false;
	CHECKING[PlayerLeaveCheckpoint] = false;
	CHECKING[PlayerEnterRaceCheckpoint] = false;
	CHECKING[PlayerLeaveRaceCheckpoint] = false;
	CHECKING[RconCommand] = false;
	CHECKING[ObjectMoved] = false;
	CHECKING[PlayerObjectMoved] = false;
	CHECKING[PlayerPickUpPickup] = false;
	CHECKING[VehicleMod] = false;
	CHECKING[EnterExitModShop] = false;
	CHECKING[VehiclePaintjob] = false;
	CHECKING[VehicleRespray] = false;
	CHECKING[VehicleDamageStatusUpdate] = false;
	CHECKING[UnoccupiedVehicleUpdate] = false;
	CHECKING[PlayerSelectedMenuRow] = false;
	CHECKING[PlayerExitedMenu] = false;
	CHECKING[PlayerInteriorChange] = false;
	CHECKING[PlayerKeyStateChange] = false;
	CHECKING[RconLoginAttempt] = false;
	CHECKING[PlayerUpdate] = false;
	CHECKING[PlayerStreamIn] = false;
	CHECKING[PlayerStreamOut] = false;
	CHECKING[VehicleStreamIn] = false;
	CHECKING[VehicleStreamOut] = false;
	CHECKING[ActorStreamIn] = false;
	CHECKING[ActorStreamOut] = false;
	CHECKING[DialogResponse] = false;
	CHECKING[PlayerTakeDamage] = false;
	CHECKING[PlayerGiveDamage] = false;
	CHECKING[PlayerGiveDamageActor] = false;
	CHECKING[PlayerClickMap] = false;
	CHECKING[PlayerClickTextDraw] = false;
	CHECKING[PlayerClickPlayerTextDraw] = false;
	CHECKING[IncomingConnection] = false;
	CHECKING[TrailerUpdate] = false;
	CHECKING[VehicleSirenStateChange] = false;
	CHECKING[PlayerClickPlayer] = false;
	CHECKING[PlayerEditObject] = false;
	CHECKING[PlayerEditAttachedObject] = false;
	CHECKING[PlayerWeaponShot] = false;
	CHECKING[PlayerSelectObject] = false;
	CHECKING[PlayerInfoChange] = false;
	CHECKING[PlayerAnimationChange] = false;
}


stock GetNameCallback(callback)
{
	new Message[32];
	switch(callback)
	{
		case	PlayerConnect: Message = 	"PlayerConnect";
		case	PlayerStateChange: Message = 	"PlayerStateChange";
		case	PlayerRequestClass: Message = 	"PlayerRequestClass";
		case	PlayerRequestSpawn: Message = 	"PlayerRequestSpawn";
		case	PlayerSpawn: Message = 	"PlayerSpawn";
		case	PlayerDeath: Message = 	"PlayerDeath";
		case	PlayerDisconnect: Message = 	"PlayerDisconnect";

		case	VehicleSpawn: Message = 	"VehicleSpawn";
		case	VehicleDeath: Message = 	"VehicleDeath";
		case	PlayerTxt: Message = 	"PlayerTxt";
		case	PlayerCommandText: Message = 	"PlayerCommandText";
		case	PlayerEnterVehicle: Message = 	"PlayerEnterVehicle";
		case	PlayerExitVehicle: Message = 	"PlayerExitVehicle";
		case	PlayerEnterCheckpoint: Message = 	"PlayerEnterCheckpoint";
		case	PlayerLeaveCheckpoint: Message = 	"PlayerLeaveCheckpoint";
		case	PlayerEnterRaceCheckpoint: Message = 	"PlayerEnterRaceCheckpoint";
		case	PlayerLeaveRaceCheckpoint: Message = 	"PlayerLeaveRaceCheckpoint";
		case	RconCommand: Message = 	"RconCommand";
		case	ObjectMoved: Message = 	"ObjectMoved";
		case	PlayerObjectMoved: Message = 	"PlayerObjectMoved";
		case	PlayerPickUpPickup: Message = 	"PlayerPickUpPickup";
		case	VehicleMod: Message = 	"VehicleMod";
		case	EnterExitModShop: Message = 	"EnterExitModShop";
		case	VehiclePaintjob: Message = 	"VehiclePaintjob";
		case	VehicleRespray: Message = 	"VehicleRespray";
		case	VehicleDamageStatusUpdate: Message = 	"VehicleDamageStatusUpdate";
		case	UnoccupiedVehicleUpdate: Message = 	"UnoccupiedVehicleUpdate";
		case	PlayerSelectedMenuRow: Message = 	"PlayerSelectedMenuRow";
		case	PlayerExitedMenu: Message = 	"PlayerExitedMenu";
		case	PlayerInteriorChange: Message = 	"PlayerInteriorChange";
		case	PlayerKeyStateChange: Message = 	"PlayerKeyStateChange";
		case	RconLoginAttempt: Message = 	"RconLoginAttempt";
		case	PlayerUpdate: Message = 	"PlayerUpdate";
		case	PlayerStreamIn: Message = 	"PlayerStreamIn";
		case	PlayerStreamOut: Message = 	"PlayerStreamOut";
		case	VehicleStreamIn: Message = 	"VehicleStreamIn";
		case	VehicleStreamOut: Message = 	"VehicleStreamOut";
		case	ActorStreamIn: Message = 	"ActorStreamIn";
		case	ActorStreamOut: Message = 	"ActorStreamOut";
		case	DialogResponse: Message = 	"DialogResponse";
		case	PlayerTakeDamage: Message = 	"PlayerTakeDamage";
		case	PlayerGiveDamage: Message = 	"PlayerGiveDamage";
		case	PlayerGiveDamageActor: Message = 	"PlayerGiveDamageActor";
		case	PlayerClickMap: Message = 	"PlayerClickMap";
		case	PlayerClickTextDraw: Message = 	"PlayerClickTextDraw";
		case	PlayerClickPlayerTextDraw: Message = 	"PlayerClickPlayerTextDraw";
		case	IncomingConnection: Message = 	"IncomingConnection";
		case	TrailerUpdate: Message = 	"TrailerUpdate";
		case	VehicleSirenStateChange: Message = 	"VehicleSirenStateChange";
		case	PlayerClickPlayer: Message = 	"PlayerClickPlayer";
		case	PlayerEditObject: Message = 	"PlayerEditObject";
		case	PlayerEditAttachedObject: Message = 	"PlayerEditAttachedObject";
		case	PlayerWeaponShot: Message = 	"PlayerWeaponShot";
		case	PlayerSelectObject: Message = 	"PlayerSelectObject";
		case	PlayerInfoChange: Message = 	"PlayerInfoChange";
		case	PlayerAnimationChange: Message = 	"PlayerAnimationChange";
		case	AllPublic: Message = 	"AllPublic";
		default: 	Message = 	"Unknown";
	}
	return Message;
}

stock checking_FunctionCheckList(playerid)
{
	new listitems[32*57];
	//strcat(listitems, "GameModeInit\n");
	//strcat(listitems, "GameModeExit\n");
	//strcat(listitems, "FilterScriptInit\n");
	//strcat(listitems, "FilterScriptExit\n");
	if(!CHECKING[PlayerConnect]) {
		strcat(listitems, 			"1.{FF0000}PlayerConnect\n"); }
	else { strcat(listitems, 		"1.{00FF00}PlayerConnect\n"); }
	if(!CHECKING[PlayerDisconnect]) {
		strcat(listitems, 			"2.{FF0000}PlayerDisconnect\n"); }
	else { strcat(listitems, 		"2.{00FF00}PlayerDisconnect\n"); }
	if(!CHECKING[PlayerSpawn]) {
		strcat(listitems, 			"3.{FF0000}PlayerSpawn\n"); }
	else { strcat(listitems, 		"3.{00FF00}PlayerSpawn\n"); }
	if(!CHECKING[PlayerDeath]) {
		strcat(listitems, 			"4.{FF0000}PlayerDeath\n"); }
	else { strcat(listitems, 		"4.{00FF00}PlayerDeath\n"); }
	if(!CHECKING[VehicleSpawn]) {
		strcat(listitems, 			"5.{FF0000}VehicleSpawn\n");	}
	else { strcat(listitems, 		"5.{00FF00}VehicleSpawn\n"); }
	if(!CHECKING[VehicleDeath]) {
		strcat(listitems, 			"6.{FF0000}VehicleDeath\n");	}
	else { strcat(listitems, 		"6.{00FF00}VehicleDeath\n"); }
	strcat(listitems, "7.PlayerTxt\n");
	strcat(listitems, "8.PlayerCommandText\n");
	if(!CHECKING[PlayerRequestClass]) {
		strcat(listitems, 			"9.{FF0000}PlayerRequestClass\n"); }
	else { strcat(listitems, 		"9.{00FF00}PlayerRequestClass\n"); }
	strcat(listitems, "10.PlayerEnterVehicle\n");
	strcat(listitems, "11.PlayerExitVehicle\n");
	if(!CHECKING[PlayerStateChange]) {
		strcat(listitems, 			"12.{FF0000}PlayerStateChange\n");	}
	else { strcat(listitems, 		"12.{00FF00}PlayerStateChange\n"); }
	strcat(listitems, "13.PlayerEnterCheckpoint\n");
	strcat(listitems, "14.PlayerLeaveCheckpoint\n");
	strcat(listitems, "15.PlayerEnterRaceCheckpoint\n");
	strcat(listitems, "16.PlayerLeaveRaceCheckpoint\n");
	strcat(listitems, "17.RconCommand\n");
	strcat(listitems, "18.PlayerRequestSpawn\n");
	strcat(listitems, "19.ObjectMoved\n");
	strcat(listitems, "20.PlayerObjectMoved\n");
	if(!CHECKING[PlayerPickUpPickup]) {
		strcat(listitems, 			"21.{FF0000}PlayerPickUpPickup\n");	}
	else { strcat(listitems, 		"21.{00FF00}PlayerPickUpPickup\n"); }
	strcat(listitems, "22.VehicleMod\n");
	strcat(listitems, "23.EnterExitModShop\n");
	strcat(listitems, "24.VehiclePaintjob\n");
	strcat(listitems, "25.VehicleRespray\n");
	if(!CHECKING[VehicleDamageStatusUpdate]) {
		strcat(listitems, 			"26.{FF0000}VehicleDamageStatusUpdate\n");	}
	else { strcat(listitems, 		"26.{00FF00}VehicleDamageStatusUpdate\n"); }
	strcat(listitems, "27.UnoccupiedVehicleUpdate\n");
	
	if(!CHECKING[PlayerSelectedMenuRow]) {
		strcat(listitems, 			"28.{FF0000}PlayerSelectedMenuRow\n");	}
	else { strcat(listitems, 		"28.{00FF00}PlayerSelectedMenuRow\n"); }
	if(!CHECKING[PlayerExitedMenu]) {
		strcat(listitems, 			"29.{FF0000}PlayerExitedMenu\n");	}
	else { strcat(listitems, 		"29.{00FF00}PlayerExitedMenu\n"); }

	if(!CHECKING[PlayerInteriorChange]) {
		strcat(listitems, 			"30.{FF0000}PlayerInteriorChange\n");	}
	else { strcat(listitems, 		"30.{00FF00}PlayerInteriorChange\n"); }
	if(!CHECKING[PlayerKeyStateChange]) {
		strcat(listitems, 			"31.{FF0000}PlayerKeyStateChange\n");	} 
	else { strcat(listitems, 		"31.{00FF00}PlayerKeyStateChange\n"); }
	strcat(listitems, "32.RconLoginAttempt\n");
	strcat(listitems, "33.PlayerUpdate\n");
	strcat(listitems, "34.PlayerStreamIn\n");
	strcat(listitems, "35.PlayerStreamOut\n");
	strcat(listitems, "36.VehicleStreamIn\n");
	strcat(listitems, "37.VehicleStreamOut\n");
	strcat(listitems, "38.ActorStreamIn\n");
	strcat(listitems, "39.ActorStreamOut\n");
	if(!CHECKING[DialogResponse]) { 
		strcat(listitems, 			"40.{FF0000}DialogResponse\n");	}
	else { strcat(listitems, 		"40.{00FF00}DialogResponse\n"); }
	strcat(listitems, "41.PlayerTakeDamage\n");
	strcat(listitems, "42.PlayerGiveDamage\n");
	strcat(listitems, "43.PlayerGiveDamageActor\n");
	strcat(listitems, "44.PlayerClickMap\n");
	strcat(listitems, "45.PlayerClickTextDraw\n");
	strcat(listitems, "46.PlayerClickPlayerTextDraw\n");
	strcat(listitems, "47.IncomingConnection\n");
	if(!CHECKING[TrailerUpdate]) {
		strcat(listitems, 			"48.{FF0000}TrailerUpdate\n");	}
	else { strcat(listitems, 		"48.{00FF00}TrailerUpdate\n"); }
	if(!CHECKING[VehicleSirenStateChange]) {
		strcat(listitems, 			"49.{FF0000}VehicleSirenStateChange\n");	}
	else { strcat(listitems, 		"49.{00FF00}VehicleSirenStateChange\n"); }
	strcat(listitems, "50.PlayerClickPlayer\n");
	strcat(listitems, "51.PlayerEditObject\n");
	strcat(listitems, "52.PlayerEditAttachedObject\n");
	strcat(listitems, "53.PlayerWeaponShot\n");
	strcat(listitems, "54.PlayerGiveMoney\n");
	strcat(listitems, "55.PlayerSelectObject\n");
	strcat(listitems, "56.PlayerInfoChange\n");
	
	if(!CHECKING[PlayerAnimationChange]) {
		strcat(listitems, 			"57.{FF0000}PlayerAnimationChange\n");	}
	else { strcat(listitems, 		"57.{00FF00}PlayerAnimationChange\n"); }
	
	if(!CHECKING[AllPublic]) {
		strcat(listitems, 			"58.{FF0000}Включить все\n");	}
	else { strcat(listitems, 		"58.{00FF00}Выключить все\n"); }
	ShowPlayerDialogEx(playerid, CHECK_DIALOG, DIALOG_STYLE_LIST, "Выберите public", listitems, "OK", "Cancel");
	//return 1;
}
//==============================================================================
//#if defined vw_checking

//#endif
//==============================================================================

public OnPlayerConnect(playerid)
{
	if(CHECKING[PlayerConnect])
	{//ИНФОРМИРОВАНИЕ
		//new str[59+3+2+2];
		format(strings, sizeof(strings),"OnPlayerConnect(playerid:%d, newstate:%d, oldstate:%d)",
			playerid, GetPlayerState(playerid), LastState[playerid]);
		//ABroadCast(COLOR_MAROON, strings, 9);
		//SendClientMessageToAll(COLOR_YELLOW, strings);
		//SendClientMessage(playerid, COLOR_MAROON, strings);
		SendClientMessage(playerid, COLOR_PINK, strings);
	}
	#if defined checking_OnPlayerConnect
		return checking_OnPlayerConnect(playerid);
	//#else
	//	return 1; // Allow other scripts to keep processing OnPlayerConnect
//return 1; должен обязательно стоять в основном скрипте или моде
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect checking_OnPlayerConnect
#if defined checking_OnPlayerConnect
	forward checking_OnPlayerConnect(playerid);
#endif

public OnPlayerRequestClass(playerid, classid)
{
	if(CHECKING[PlayerRequestClass])
	{//ИНФОРМИРОВАНИЕ
		//new str[59+3+2+2];
		format(strings, sizeof(strings),"OnPlayerRequestClass(playerid:%d, classid:%d, newstate:%d, oldstate:%d)",
			playerid, classid, GetPlayerState(playerid), LastState[playerid]);
		//ABroadCast(COLOR_MAROON, strings, 9);
		//SendClientMessageToAll(COLOR_YELLOW, strings);
		//SendClientMessage(playerid, COLOR_MAROON, strings);
		SendClientMessage(playerid, COLOR_PINK, strings);
	}

	#if defined checking_OnPlayerRequestClass
		return checking_OnPlayerRequestClass(playerid, classid);
	//#else
	//	return 0; // Allow other scripts to keep processing OnPlayerConnect
//return 1; должен обязательно стоять в основном скрипте или моде
	#endif
}
#if defined _ALS_OnPlayerRequestClass
	#undef OnPlayerRequestClass
#else
	#define _ALS_OnPlayerRequestClass
#endif
#define OnPlayerRequestClass checking_OnPlayerRequestClass
#if defined checking_OnPlayerRequestClass
	forward checking_OnPlayerRequestClass(playerid, classid);
#endif


/*
public OnPlayerRequestSpawn(playerid)
{

	return 0;
}

public OnPlayerDisconnect(playerid, reason)
{

	return 1;
}*/

public OnPlayerSpawn(playerid)
{
	if(CHECKING[PlayerSpawn])
	{//ИНФОРМИРОВАНИЕ
		new Float: plhp;
		GetPlayerHealth(playerid, plhp);//равна
		format(strings, sizeof(strings), "PlayerSpawn(playerid:%d) Health:%.1f[%.1f]", playerid,  plhp, LastHealth[playerid]);
		//SendClientMessage(playerid, -1, strings);
		SendAllAdminMessage(COLOR_MAROON, strings, 6);
	}
	#if defined checking_OnPlayerSpawn
		return checking_OnPlayerSpawn(playerid);
	//#else
	//	return 0; // Allow other scripts to keep processing OnPlayerConnect
//return 1; должен обязательно стоять в основном скрипте или моде
	#endif
}
#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn checking_OnPlayerSpawn
#if defined checking_OnPlayerSpawn
	forward checking_OnPlayerSpawn(playerid);
#endif

/*public OnPlayerDeath(playerid, killerid, reason)
{

	return 1;
}
*/
public OnVehicleSpawn(vehicleid)//Выполняется при спавне транспортного средства или через время спауна установленное при создании тачки.
//спаун выполняется всегда когда тачка входит в стрим область? НЕТ, вообще стрим не при чём
//1. по команде  /res
//2. чит
//3. умерла и спаунится
{
	if(CHECKING[VehicleSpawn])
	{//ИНФОРМИРОВАНИЕ
		new Float: vehhp;
		GetVehicleHealth(vehicleid, vehhp);//равна
		format(strings, sizeof(strings), "OnVehicleSpawn(vehicleid:%d) VehicleHealth:%.1f[%.1f]", vehicleid,  vehhp, VehHealth[vehicleid]);
		//SendClientMessage(playerid, -1, strings);
		SendAllAdminMessage(COLOR_MAROON, strings, 6);
	}
	#if defined checking_OnVehicleSpawn
		return checking_OnVehicleSpawn(vehicleid);
	//#else
	//	return 0; // Allow other scripts to keep processing OnPlayerConnect
//return 1; должен обязательно стоять в основном скрипте или моде
	#endif
}
#if defined _ALS_OnVehicleSpawn
	#undef OnVehicleSpawn
#else
	#define _ALS_OnVehicleSpawn
#endif
#define OnVehicleSpawn checking_OnVehicleSpawn
#if defined checking_OnVehicleSpawn
	forward checking_OnVehicleSpawn(vehicleid);
#endif

public OnVehicleDeath(vehicleid, killerid)//Выполняется при уничтожении транспортного средства,
//как только тачка перевернулась
//попала вводу

//с каким здоровьем умирает пустая тачка
//1. в воде
//2. растреляв
//3. перевернулась
{
	if(CHECKING[VehicleDeath])
	{//ИНФОРМИРОВАНИЕ
		new Float: vehhp;
		GetVehicleHealth(vehicleid, vehhp);//текущее кол-во здоровья
		format(strings, sizeof(strings), "OnVehicleDeath(vehicleid:%d, killerid:%s[%d]) VehicleHealth:%.1f[%.1f]",
			vehicleid, PlayerName(killerid), killerid,
			vehhp, VehHealth[vehicleid]);
		//SendClientMessage(playerid, -1, strings);
		SendAllAdminMessage(COLOR_MAROON, strings, 6);
	}
	
	#if defined checking_OnVehicleDeath
		return checking_OnVehicleDeath(vehicleid, killerid);
	//#else
	//	return 0; // Allow other scripts to keep processing OnPlayerConnect
//return 1; должен обязательно стоять в основном скрипте или моде
	#endif
}
#if defined _ALS_OnVehicleDeath
	#undef OnVehicleDeath
#else
	#define _ALS_OnVehicleDeath
#endif
#define OnVehicleDeath checking_OnVehicleDeath
#if defined checking_OnVehicleDeath
	forward checking_OnVehicleDeath(vehicleid, killerid);
#endif
/*
public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{

	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{

	return 1;
}
*/
/*
public OnPlayerStateChange(playerid, newstate, oldstate)
{//если игрок телепортируется по разным тачка, но не меняет водительское место, то паблик не срабатывает

	if(CHECKING[PlayerStateChange])
	{//ИНФОРМИРОВАНИЕ
		//new str[59+3+2+2];
		format(strings, sizeof(strings),"OnPlayerStateChange(playerid:%d, newstate:%d[%d], oldstate:%d[%d])",
			playerid, newstate, CurState[playerid], oldstate, LastState[playerid]);
		//ABroadCast(COLOR_MAROON, strings, 9);
		//SendClientMessageToAll(COLOR_YELLOW, strings);
		//SendClientMessage(playerid, COLOR_MAROON, strings);
		SendClientMessage(playerid, COLOR_PINK, strings);
	}

	#if defined checking_OnPlayerStateChange
		return checking_OnPlayerStateChange(playerid, newstate, oldstate);
	//#else
	//	return 0; // Allow other scripts to keep processing OnPlayerConnect
//return 1; должен обязательно стоять в основном скрипте или моде
	#endif
}
#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif
#define OnPlayerStateChange checking_OnPlayerStateChange
#if defined checking_OnPlayerStateChange
	forward checking_OnPlayerStateChange(playerid, newstate, oldstate);
#endif
*/

public OnPlayerStateChange(playerid, newstate, oldstate)
{//если игрок телепортируется по разным тачка, но не меняет водительское место, то паблик не срабатывает

	if(CHECKING[PlayerStateChange])
	{//ИНФОРМИРОВАНИЕ
		//new str[59+3+2+2];
		format(strings, sizeof(strings),"OnPlayerStateChange(playerid:%d, newstate:%d[%d], oldstate:%d[%d])",
			playerid, newstate, CurState[playerid], oldstate, LastState[playerid]);
		//ABroadCast(COLOR_MAROON, strings, 9);
		//SendClientMessageToAll(COLOR_YELLOW, strings);
		//SendClientMessage(playerid, COLOR_MAROON, strings);
		SendClientMessage(playerid, COLOR_PINK, strings);
	}
	return CallLocalFunction("checking_OnPlayerStateChange", "ddd", playerid, newstate, oldstate);
}
#if defined _ALS_OnPlayerStateChange
    #error _ALS_OnPlayerStateChange defined
#endif
#define _ALS_OnPlayerStateChange
#define OnPlayerStateChange checking_OnPlayerStateChange

forward checking_OnPlayerStateChange(playerid, newstate, oldstate);




/*
public OnPlayerEnterCheckpoint(playerid)
{

	return 1;
}

public OnPlayerLeaveCheckpoint(playerid)
{

 	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{

	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{

	return 1;
}

//public OnRconCommand(cmd[])
//{
//	//OnPlayerInfoChange(playerid, RconCommand);
//	return 0;
//}

public OnObjectMoved(objectid)
{
	//OnPlayerInfoChange(playerid, ObjectMoved);
	return 0;
}

public OnPlayerObjectMoved(playerid, objectid)
{

	return 1;
}
*/

public OnPlayerPickUpPickup(playerid, pickupid)
{
	if(CHECKING[PlayerPickUpPickup])
	{//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings),"OnPlayerPickUpPickup(playerid:%d, pickupid:%d)",
			playerid, pickupid);
		SendClientMessage(playerid, COLOR_PINK, strings);
	}

	#if defined checking_OnPlayerPickUpPickup
		return checking_OnPlayerPickUpPickup(playerid, pickupid);
	//#else
	//	return 0; // Allow other scripts to keep processing OnPlayerConnect
//return 1; должен обязательно стоять в основном скрипте или моде
	#endif
}
#if defined _ALS_OnPlayerPickUpPickup
	#undef OnPlayerPickUpPickup
#else
	#define _ALS_OnPlayerPickUpPickup
#endif
#define OnPlayerPickUpPickup checking_OnPlayerPickUpPickup
#if defined checking_OnPlayerPickUpPickup
	forward checking_OnPlayerPickUpPickup(playerid, pickupid);
#endif


/*
public OnVehicleMod(playerid, vehicleid, componentid)
{

	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{

	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{

	return 1;
}
*/

public OnPlayerSelectedMenuRow(playerid, row)
{
	if(CHECKING[PlayerSelectedMenuRow])
	{//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings),"OnPlayerSelectedMenuRow(playerid:%d, row:%d)",
			playerid, row);
		SendClientMessage(playerid, COLOR_PINK, strings);
	}

	#if defined check_OnPlayerSelectedMenuRow
		return check_OnPlayerSelectedMenuRow(playerid, row);
	//#else
	//	return 0; // Allow other scripts to keep processing OnPlayerConnect
//return 1; должен обязательно стоять в основном скрипте или моде
	#endif
}
#if defined _ALS_OnPlayerSelectedMenuRow
	#undef OnPlayerSelectedMenuRow
#else
	#define _ALS_OnPlayerSelectedMenuRow
#endif
#define OnPlayerSelectedMenuRow check_OnPlayerSelectedMenuRow
#if defined check_OnPlayerSelectedMenuRow
	forward check_OnPlayerSelectedMenuRow(playerid, row);
#endif

public OnPlayerExitedMenu(playerid)
{
	if(CHECKING[PlayerExitedMenu])
	{//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings),"OnPlayerExitedMenu(playerid:%d)",
			playerid);
		SendClientMessage(playerid, COLOR_PINK, strings);
	}
	
	#if defined checking_OnPlayerExitedMenu
		return checking_OnPlayerExitedMenu(playerid);
	//#else
	//	return 0; // Allow other scripts to keep processing OnPlayerConnect
//return 1; должен обязательно стоять в основном скрипте или моде
	#endif
}
#if defined _ALS_OnPlayerExitedMenu
	#undef OnPlayerExitedMenu
#else
	#define _ALS_OnPlayerExitedMenu
#endif
#define OnPlayerExitedMenu checking_OnPlayerExitedMenu
#if defined checking_OnPlayerExitedMenu
	forward checking_OnPlayerExitedMenu(playerid);
#endif

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	if(CHECKING[PlayerInteriorChange])
	{//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings),"OnPlayerInteriorChange(playerid:%d, newinteriorid:%d, oldinteriorid:%d)",
			playerid, newinteriorid, oldinteriorid);
		SendClientMessage(playerid, COLOR_PINK, strings);
	}

	#if defined checking_OnPlayerInteriorChange
		return checking_OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
	//#else
	//	return 0; // Allow other scripts to keep processing OnPlayerConnect
//return 1; должен обязательно стоять в основном скрипте или моде
	#endif
}
#if defined _ALS_OnPlayerInteriorChange
	#undef OnPlayerInteriorChange
#else
	#define _ALS_OnPlayerInteriorChange
#endif
#define OnPlayerInteriorChange checking_OnPlayerInteriorChange
#if defined checking_OnPlayerInteriorChange
	forward checking_OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
#endif



public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	//if(KEYSTATE == 1 && newkeys != 0 && oldkeys == 0)
	if(CHECKING[PlayerKeyStateChange] && newkeys != 0 && oldkeys == 0)
	{//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "OnPlayerKeyStateChange(playerid:%d, newkeys:%d, oldkeys:%d)",
			playerid, newkeys, oldkeys);
		SendClientMessage(playerid, COLOR_CERISE, strings);
		//Log(SPAWN, strtmp);
	}
	#if defined checking_OnPlayerKeyStateChange
		return checking_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	//#else
//		return 0; // Allow other scripts to keep processing OnPlayerConnect
//return 1; должен обязательно стоять в основном скрипте или моде
	#endif
}
#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange checking_OnPlayerKeyStateChange
#if defined checking_OnPlayerKeyStateChange
	forward checking_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif



//##############################################################################//
//                                                                              //
//                    НОВЫЕ САМОВЫЗЫВАЕМЫЕ ФУНКЦИИ SA-MP 0.3a                   //
//                                                                              //
//##############################################################################//


//This callback was added in SA-MP 0.3a and will not work in earlier versions!
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(CHECKING[DialogResponse])
	{//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "OnDialogResponse(playerid:%d, dialogid:%d, response:%d, listitem:%d, strlen(inputtext):%d)",
			playerid, dialogid, response, listitem, strlen(inputtext));
		SendClientMessage(playerid, COLOR_MAROON, strings);
	}
	if(dialogid == CHECK_DIALOG && response)
	{
		if(CHECKING[listitem+1] == false)
		{
			CHECKING[listitem+1] = true;
			if(listitem+1 == AllPublic)
			{
				for(new i = 0; i < MAX_CALLBACK; i++) CHECKING[i] = true;
			}

			format(strings, sizeof(strings), "%s: is activate", GetNameCallback(listitem+1));
			SendClientMessage(playerid, COLOR_GREEN, strings);

		}
		else
		{
			CHECKING[listitem+1] = false;
			if(listitem+1 == AllPublic)
			{
				for(new i = 0; i < MAX_CALLBACK; i++) CHECKING[i] = false;
			}
			
			format(strings, sizeof(strings), "%s: is deactivate", GetNameCallback(listitem+1));
			SendClientMessage(playerid, COLOR_RED, strings);
		}
	}
	
	#if defined checking_OnDialogResponse
		return checking_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	//#else
	//	return 0; // Allow other scripts to keep processing OnPlayerConnect
//return 1; должен обязательно стоять в основном скрипте или моде
	#endif
}
#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif
#define OnDialogResponse checking_OnDialogResponse
#if defined checking_OnDialogResponse
	forward checking_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif


/*
//This callback was added in SA-MP 0.3a and will not work in earlier versions!
public OnEnterExitModShop(playerid, enterexit, interiorid)//1 if the player entered or 0 if they exited
{    //Эта функция вызывается, когда игрок входит или выходит из тюн-магазина.

	return 1;
}

//This callback was added in SA-MP 0.3a and will not work in earlier versions!
public OnPlayerClickPlayer(playerid, clickedplayerid, source)//для телефонов
{   //Вызывается, когда игрок дважды нажимает на игрока в TAB.

	return 1;
}

//This callback was added in SA-MP 0.3a and will not work in earlier versions!
public OnPlayerStreamIn(playerid, forplayerid)//не работает на AFK игроков
{   //Cрабатывает одновременно у игрока forplayerid создаётся пед игрока playerid на компе.

	return 1;
}

//This callback was added in SA-MP 0.3a and will not work in earlier versions!
public OnPlayerStreamOut(playerid, forplayerid)//не работает на AFK игроков
{

	return 1;
}

//This callback was added in SA-MP 0.3a and will not work in earlier versions!
//public OnRconLoginAttempt(ip[], password[], success)
//{//Эта функция вызывается, когда кто-то пытается войти в RCON в игре; успешно или нет.
	//OnPlayerInfoChange(playerid, RconLoginAttempt);
//	return 0;
//}

//This callback was added in SA-MP 0.3a and will not work in earlier versions!
public OnVehicleStreamIn(vehicleid, forplayerid)
{   //Вызывается при появлении тачки vehicleid в поле зрения игрока forplayerid.

	return 1;
}

//This callback was added in SA-MP 0.3a and will not work in earlier versions!
public OnVehicleStreamOut(vehicleid, forplayerid)
{   //Вызывается при исчезновении стрим тачки в поле зрения игрока.

	return 1;
}

*/
//This callback was added in SA-MP 0.3a and will not work in earlier versions!
//public OnVehicleDamageStatusUpdate(vehicleid, playerid)
stock checking_OnVehicleDamageStatus(vehicleid, playerid)
{   //выполняется при повреждении тачки игроком за водительским местом или при перекраске
	if(CHECKING[VehicleDamageStatusUpdate])
	{//ИНФОРМИРОВАНИЕ
		
		new Float: vehhp;
		GetVehicleHealth(vehicleid, vehhp);//равна
		new modelid = nCarModel[playerid];//GetVehicleModel(vehicleid);
		
		format(strings, sizeof(strings), "OnVehicleDamageStatusUpdate(player:%s[%d] vehicle:%s[%d]) VehicleHealth:%.1f[%.1f]",
			PlayerName(playerid), playerid, VehicleArray[modelid-400][Vehicle_Name], vehicleid, vehhp, VehHealth[vehicleid]);
		SendAllAdminMessage(COLOR_MAROON, strings, 6);
		//SendClientMessage(playerid, COLOR_MAROON, strings);

		new panel, doors, lights, tires;
		new update_msg[128+1];
		GetVehicleDamageStatus(vehicleid,panel,doors,lights,tires);
		format(update_msg,128,"VehicleDamage[ID:%d PN:0x%x DR:0x%x LT:0x%x TR:0x%x]",vehicleid,panel,doors,lights,tires);
		SendClientMessage(playerid,COLOR_MAUVE,update_msg);
	}
	return 1;
}

	/*#if defined checking_OnVehicleDamage
		return checking_OnVehicleDamage(vehicleid, playerid);
	//#else
	//	return 0; // Allow other scripts to keep processing OnPlayerConnect
//return 1; должен обязательно стоять в основном скрипте или моде
	#endif
}
#if defined _ALS_OnVehicleDamageStatusUpdate //warning 200: symbol "_ALS_OnVehicleDamageStatusUpdat" is truncated to 31 characters
	#undef OnVehicleDamageStatusUpdate
#else
	#define _ALS_OnVehicleDamageStatusUpdate
#endif
#define OnVehicleDamageStatusUpdate checking_OnVehicleDamage
#if defined checking_OnVehicleDamage
	forward checking_OnVehicleDamage(vehicleid, playerid);
#endif*/

/*
//##############################################################################//
//                                                                              //
//                    НОВЫЕ САМОВЫЗЫВАЕМЫЕ ФУНКЦИИ SA-MP 0.3c                   //
//                                                                              //
//##############################################################################//


//This callback was added in SA-MP 0.3c R3 and will not work in earlier versions!
public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z)
{//событие происходит когда игрок меняет позицию транспортного средства в котором нет водителя, или игрок сидит в машине пассажиром(второе не совсем понял надо проверять!)

	return 1;
}

//##############################################################################//
//                                                                              //
//                    НОВЫЕ САМОВЫЗЫВАЕМЫЕ ФУНКЦИИ SA-MP 0.3d                   //
//                                                                              //
//##############################################################################//

//This callback was added in SA-MP 0.3d and will not work in earlier versions!
public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)//, Float:ang=0.0
{//OnPlayerClickMap вызывается, когда игрок ставит цель / путевой точки на карте меню паузы (щелкнув правой кнопкой мыши).

	return 1;
}



//This callback was added in SA-MP 0.3d and will not work in earlier versions!
public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{   //вызывается когда игрок playerid наносит урон игроку damagedid

	return 1;
}

//This callback was added in SA-MP 0.3d and will not work in earlier versions!
public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)//при год моде и АФК не вызывается
{    //Эта функция вызывается, когда игрок получает урон.
//Return Values:
//    1 - Callback will not be called in other filterscripts.
//    0 - Allows this callback to be called in other filterscripts.
//    It is always called first in filterscripts so returning 1 there blocks other filterscripts from seeing it

	return 1;
}


//##############################################################################//
//                                                                              //
//                    НОВЫЕ САМОВЫЗЫВАЕМЫЕ ФУНКЦИИ SA-MP 0.3e                   //
//                                                                              //
//##############################################################################//
//This callback was added in SA-MP 0.3e and will not work in earlier versions!
public OnPlayerClickTextDraw(playerid, Text:clickedid)
{//Эта функция вызывается, когда игрок нажимает на TextDraw или отменяет режим выбора с помощью клавиши Escape.

	return 1;
}

//This callback was added in SA-MP 0.3e and will not work in earlier versions!
public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{//Эта функция вызывается, когда игрок нажимает на игрока-TextDraw. Это не вызывается, когда игрок отменяет режим выбора (ESC) - однако, OnPlayerClickTextDraw есть.

	return 1;
}


//This function was added in SA-MP 0.3e and will not work in earlier versions!
public OnPlayerSelectObject(playerid, type, objectid, modelid, Float:fX, Float:fY, Float:fZ)
{//Эта функция вызывается, когда игрок выбирает объект после того, как SelectObject был использован.

	return 1;
}

//This callback was added in SA-MP 0.3e and will not work in earlier versions!
public OnPlayerEditObject(playerid, playerobject, objectid, response,
	Float:fX, Float:fY, Float:fZ, Float:fRotX, Float:fRotY, Float:fRotZ)
{	//вызывается при окончании редактирования объекта или после нажатия сохранения.

}


public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{//вызывается, когда игрок заканчивает редактирование приклееного объекта

	return 1;
}

//##############################################################################//
//                                                                              //
//                    НОВЫЕ САМОВЫЗЫВАЕМЫЕ ФУНКЦИИ SA-MP 0.3z                   //
//                                                                              //
//##############################################################################//

//This callback was added in SA-MP 0.3z and will not work in earlier versions!
public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{// вызывается только для оружия стреляющего пулями когда пуля достигает цели, если стрельбы в небо, то возвращает 0 координаты, а для снайперки вообще не вызывается

 	return 1;
}



//This callback was added in SA-MP 0.3z R2-2 and will not work in earlier versions!
public OnIncomingConnection(playerid, ip_address[], port)
{//вызывается, когда IP-адрес пытается установить соединение с сервером. Для того, чтобы блокировать входящие соединения, используйте BlockIpAddress.
//- Добавлен колбэк "OnIncomingConnection".
//Он сообщает, что игрок пытается подключиться к серверу
//(в консоли раньше писалось: Incoming Connection: IP:PORT",
//теперь можно отследить скриптово; вот только не знаю, как там playerid передаётся, т.к. игрок ещё не подключен и не имеет ID)
	//if(IsPlayerNPC(playerid)) { return 0; }
	//if( !strcmp(ip_address, "127.0.0.1", true) ) { return 0; }
	//if( !strcmp(ip_address, IP_ADRESS, true) ) { return 0; }

	//gCheckDisconnect[playerid] = GetTickCount();
	//strmid(PlayerInfo[playerid][pIP], ip_address, 0, 16, 16);

	return 1;
}

*/
/*
//This callback was added in SA-MP 0.3z R4 and will not work in earlier versions!
public OnTrailerUpdate(playerid, vehicleid)
{//Эта функция вызывается, когда игрок послал обновление прицепа.
	if(CHECKING[TrailerUpdate])
	{//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "OnTrailerUpdate(playerid:%d, trailerid::%d)", playerid, vehicleid);
		SendClientMessage(playerid, -1, strings);
	}
	
	#if defined checking_OnTrailerUpdate
		return checking_OnTrailerUpdate(playerid, vehicleid);
	//#else
//		return 0; // Allow other scripts to keep processing OnPlayerConnect
//return 1; должен обязательно стоять в основном скрипте или моде
	#endif
}
#if defined _ALS_OnTrailerUpdate
	#undef OnTrailerUpdate
#else
	#define _ALS_OnTrailerUpdate
#endif
#define OnTrailerUpdate checking_OnTrailerUpdate
#if defined checking_OnTrailerUpdate
	forward checking_OnTrailerUpdate(playerid, vehicleid);
#endif
*/
/*
//##############################################################################//
//                                                                              //
//                    НОВЫЕ САМОВЫЗЫВАЕМЫЕ ФУНКЦИИ SA-MP 0.3.7                  //
//                                                                              //
//##############################################################################//

public OnActorStreamIn(actorid, forplayerid)
{//Эта функция вызывается, когда актер попадает в область радара клиента-игрока.

	return 1;
}

//This function was added in SA-MP 0.3.7 and will not work in earlier versions!
public OnActorStreamOut(actorid, forplayerid)
{//Эта функция вызывается, когда актер покидает в область радара клиента-игрока.

	return 1;
}

public OnPlayerGiveDamageActor(playerid, damaged_actorid, Float: amount, weaponid, bodypart)
{//вызывается, когда игрок наносит урон актеру.

	return 1;
}
*/
//This callback was added in SA-MP 0.3.7 and will not work in earlier versions!
public OnVehicleSirenStateChange(playerid, vehicleid, newstate)
{//Эта функция вызывается, когда сирена транспортного средства переключается.
	if(CHECKING[VehicleSirenStateChange])
	{//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "OnVehicleSirenStateChange(playerid:%d, vehicleid:%d, newstate:%d)", playerid, vehicleid, newstate);
		SendClientMessage(playerid, -1, strings);
	}
	
	
	#if defined check_OnVehicleSirenStateChange
		return check_OnVehicleSirenStateChange(playerid, vehicleid, newstate);
	//#else
//		return 0; // Allow other scripts to keep processing OnPlayerConnect
//return 1; должен обязательно стоять в основном скрипте или моде
	#endif
}
#if defined _ALS_OnVehicleSirenStateChange
	#undef OnVehicleSirenStateChange
#else
	#define _ALS_OnVehicleSirenStateChange
#endif
#define OnVehicleSirenStateChange check_OnVehicleSirenStateChange
#if defined check_OnVehicleSirenStateChange
	forward check_OnVehicleSirenStateChange(playerid, vehicleid, newstate);
#endif
/*

//##############################################################################//
//#                                                                            #//
//#                    ПОЛЬЗОВАТЕЛЬСКИЕ КОНСОЛЬНЫЕ КОМАНДЫ                     #//
//#                                                                            #//
//##############################################################################//

public OnPlayerCommandText(playerid, cmdtext[])//Выполняется при введении игроком команды.
//playerid	ID пославшего команду игрока.
//cmdtext[]	Текст команды.
{

	return 1;
	//- 0, скрипт передается во все скрипты, после обработки всеми скриптами выводиться собщения 'SERVER: Unknown command'.
//Порядок обработки: филтрскрипты, гейммод.
//Returning '0' is used to inform the server that the command
//has not been successfully processed, and passes it to other scripts.
//If there hasn't been a successful process, then you will get that
//'SERVER: Unknown Command.' error.
}//end OnPlayerCommandText

//##############################################################################//
//#                                                                            #//
//#                  ПОЛЬЗОВАТЕЛЬСКИЕ КОНСОЛЬНЫЕ СООБЩЕНИЯ                     #//
//#                                                                            #//
//##############################################################################//
public OnPlayerText(playerid, text[])//Выполняется при введении игроком текста в чат.
//playerid ID говорящего игрока.
//text[] Текст, посланный игроком.
{

	return 1;
//- 1, обрывание события, сообщение выводится в чат.
}// End OnPlayerText(playerid, text[])

*/

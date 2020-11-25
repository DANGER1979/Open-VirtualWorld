//----------------------------------------------------------
//
//  GRAND LARCENY  1.0
//  A freeroam gamemode for SA-MP 0.3
//
//----------------------------------------------------------
//#include <a_samp>
//#include "../include/grandlarc/gl_common.inc"
//#include "../include/grandlarc/gl_spawns.inc"

//#pragma tabsize 0

//----------------------------------------------------------

#define COLOR_WHITE 		0xFFFFFFFF
#define COLOR_NORMAL_PLAYER 0xFFBB7777

#define SPAWN_EXIT     		0
#define SPAWN_STATION_LS    1
#define SPAWN_HALL_LS   	2
#define SPAWN_BANK_LS   	3
#define SPAWN_HOSPITAL_LS   4
#define SPAWN_SCHOOL_SF    	5


new total_vehicles_from_files=0;

// Class selection globals
new gPlayerSpawnSelection[MAX_PLAYERS];//переключатель спауна
new gPlayerHasSpawnSelected[MAX_PLAYERS];
new gPlayerLastSpawnSelectionTick[MAX_PLAYERS];//ограничитель скорости переключения спаунов


new Text:txtClassSelHelper;

new Text:txtSpawn;

//new thisanimid=0;
//new lastanimid=0;

/*
new Float:gRandomSpawns_StationLS[][4] = {
{1731.0529,-1892.4010,13.5850,295.3309}
};

new Float:gRandomSpawns_BankLS[][4] = {
{iEntrance_Bank,0.0}
};

new Float:gRandomSpawns_CityHallLS[][4] = {
{iEntrance_CityHallLS,0.0}
};

new Float:gRandomSpawns_HospitalLS[][4] = {
{iEntrance_HospitalLS,270.0}
};

new Float:gRandomSpawns_SchoolSF[][4] = {
{iEntrance_SchoolSF,0.0}
};
*/

//----------------------------------------------------------

/*main()
{
	print("\n---------------------------------------");
	print("Running Grand Larceny - by the SA-MP team\n");
	print("---------------------------------------\n");
}*/

//----------------------------------------------------------

stock grandlarc_OnGameModeInit()
{
	new time = GetTickCount();
	//SetGameModeText("Grand Larceny");
	//ShowPlayerMarkers(PLAYER_MARKERS_MODE_GLOBAL);
	//ShowNameTags(1);
	//SetNameTagDrawDistance(40.0);
	//EnableStuntBonusForAll(0);
	//DisableInteriorEnterExits();
	SetWeather(2);
	//SetWorldTime(21);

	SetObjectsDefaultCameraCol(true);
	//UsePlayerPedAnims();
	//ManualVehicleEngineAndLights();
	//LimitGlobalChatRadius(300.0);

	ClassSel_InitTextDraws();

	// Player Class
	//AddPlayerClass(133, 2989.1980,1071.5000,103.4825, 98.0,		-1,-1,-1,-1,-1,-1);//дальнобойщик
	//AddPlayerClass(300, 1958.1356,1172.0969,1146.4017, 8.4784, 	-1,-1,-1,-1,-1,-1);//коп
	//AddPlayerClass(248, 1415.8730,-25.0560,1000.9570, 95.8988, 	-1,-1,-1,-1,-1,-1);//бандит

	AddPlayerClass(133, 2989.1980,1071.5000,103.4825, 98.0,		-1,-1,-1,-1,-1,-1);//дальнобойщик
	AddPlayerClass(300, 2989.1980,1071.5000,103.4825, 98.0, 	-1,-1,-1,-1,-1,-1);//коп
	AddPlayerClass(248, 2989.1980,1071.5000,103.4825, 98.0, 	-1,-1,-1,-1,-1,-1);//бандит

	//AddPlayerClass(308, 2989.1980,1071.5000,103.4825, 98.0,		-1,-1,-1,-1,-1,-1);//медик
	//AddPlayerClass(227, 2989.1980,1071.5000,103.4825, 98.0, 	-1,-1,-1,-1,-1,-1);//репортер
	//AddPlayerClass(73, 2989.1980,1071.5000,103.4825, 98.0, 	-1,-1,-1,-1,-1,-1);//военный
	
	// SPECIAL
	total_vehicles_from_files += LoadStaticVehiclesFromFile("vehicles/trains.txt");
	total_vehicles_from_files += LoadStaticVehiclesFromFile("vehicles/pilots.txt");
	total_vehicles_from_files += LoadStaticVehiclesFromFile("vehicles/taxi.txt");
	
    // LOS SANTOS
    total_vehicles_from_files += LoadStaticVehiclesFromFile("vehicles/ls_law.txt");
    total_vehicles_from_files += LoadStaticVehiclesFromFile("vehicles/ls_airport.txt");
    total_vehicles_from_files += LoadStaticVehiclesFromFile("vehicles/ls_gen_inner.txt");
    total_vehicles_from_files += LoadStaticVehiclesFromFile("vehicles/ls_gen_outer.txt");

    // SAN FIERRO
    total_vehicles_from_files += LoadStaticVehiclesFromFile("vehicles/sf_law.txt");
    total_vehicles_from_files += LoadStaticVehiclesFromFile("vehicles/sf_airport.txt");
    total_vehicles_from_files += LoadStaticVehiclesFromFile("vehicles/sf_gen.txt");

   	// LAS VENTURAS
    total_vehicles_from_files += LoadStaticVehiclesFromFile("vehicles/lv_law.txt");
    total_vehicles_from_files += LoadStaticVehiclesFromFile("vehicles/lv_airport.txt");
    total_vehicles_from_files += LoadStaticVehiclesFromFile("vehicles/lv_gen.txt");

    // OTHER AREAS
    total_vehicles_from_files += LoadStaticVehiclesFromFile("vehicles/whetstone.txt");
    total_vehicles_from_files += LoadStaticVehiclesFromFile("vehicles/bone.txt");
    total_vehicles_from_files += LoadStaticVehiclesFromFile("vehicles/flint.txt");
    total_vehicles_from_files += LoadStaticVehiclesFromFile("vehicles/tierra.txt");
    total_vehicles_from_files += LoadStaticVehiclesFromFile("vehicles/red_county.txt");

    //printf("Total vehicles from files: %d",total_vehicles_from_files);
    printf("0/19. [Загрузка транспорта grandlarc]: Было загружено - %d, потрачено - %d (ms)", total_vehicles_from_files, GetTickCount() - time);
	print("_____________________________________________");
	print(" ");

#if defined NPCs
	for(new i=0; i<sizeof(NPCCar); i++)
	{//инициализруем массив NPCCar[npc_veh] который создан в ФС ботов, т.к. он фс ботов не видит массив мода
		CallRemoteFunction("OnRemoteNPCCar", "i", NPCCar[i]);//может крашить сервер
	}
	new namefs[64];
	format(namefs, sizeof(namefs), "loadfs vw_npcs");
	SendRconCommand(namefs);//загружаем скрипт после создания тачек
#endif
  
	//SendRconCommand("loadfs GE");
	return 1;
}
stock ClassSel_InitTextDraws()
{//вызывается из grandlarc_OnGameModeInit()
    // Init our observer helper text display
 	txtSpawn = TextDrawCreateEx(10.0, 380.0, "Spawn");
	ClassSel_InitCityNameText(txtSpawn);
    
    // Init our observer helper text display
	txtClassSelHelper = TextDrawCreateEx(10.0, 415.0,
	   " Press ~b~~k~~GO_LEFT~ ~w~or ~b~~k~~GO_RIGHT~ ~w~to switch spawn.~n~ Press ~r~~k~~PED_FIREWEAPON~ ~w~to continue.");
	   //" Нажмите ~b~~k~~GO_LEFT~ ~w~или ~b~~k~~GO_RIGHT~ ~w~чтобы выбрать спаун.~n~ Нажмите ~r~~k~~PED_FIREWEAPON~ ~w~чтобы продолжить вход .");
	TextDrawUseBox(txtClassSelHelper, 1);
	TextDrawBoxColor(txtClassSelHelper,0x22222266);
	TextDrawLetterSize(txtClassSelHelper, 0.3,1.0);
	TextDrawTextSize(txtClassSelHelper, 270.0,40.0);
	TextDrawFont(txtClassSelHelper, 2);
	TextDrawSetShadow(txtClassSelHelper, 0);
    TextDrawSetOutline(txtClassSelHelper, 1);
    TextDrawBackgroundColor(txtClassSelHelper, 0x000000FF);
    TextDrawColor(txtClassSelHelper, 0xFFFFFFFF);
}
// Used to init textdraws of city names
stock ClassSel_InitCityNameText(Text:txtInit)
{//подгружаем стиль текстдровов из ClassSel_InitTextDraws()<-grandlarc_OnGameModeInit()
  	TextDrawUseBox(txtInit, 0);
	TextDrawLetterSize(txtInit,1.25,3.0);
	TextDrawFont(txtInit, 0);
	TextDrawSetShadow(txtInit,0);
    TextDrawSetOutline(txtInit,1);
    TextDrawColor(txtInit,0xEEEEEEFF);
    TextDrawBackgroundColor(txtClassSelHelper,0x000000FF);
}

//----------------------------------------------------------

stock grandlarc_OnPlayerConnect(playerid)
{
	//GameTextForPlayer(playerid,"~w~Grand Larceny",3000,4);
  	//SendClientMessage(playerid,COLOR_WHITE,"Welcome to {88AA88}G{FFFFFF}rand {88AA88}L{FFFFFF}arceny");
  	SendClientMessage(playerid,COLOR_WHITE,"Welcome to {0089FC}V{FFFFFF}irtual {0089FC}W{FFFFFF}orld");
  	
  	// class selection init vars
  	gPlayerSpawnSelection[playerid] = -1;//нач. инициализация
	gPlayerHasSpawnSelected[playerid] = 0;//Игрок не выбрал спаун
	gPlayerLastSpawnSelectionTick[playerid] = GetTickCount();
}

//----------------------------------------------------------
//----------------------------------------------------------

stock grandlarc_OnPlayerUpdate(playerid, newstate)
{
	#pragma unused newstate
	// changing cities by inputs
	if( !gPlayerHasSpawnSelected[playerid] && //игрок не выбрал спаун
	    GetPlayerState(playerid) == PLAYER_STATE_SPECTATING 
	    //newstate == PLAYER_STATE_SPECTATING //игрок ещё в режиме зрителя
	   )
	{
	    ClassSel_HandleSpawnSelection(playerid);//постоянно проверяем нажатые клавиша
	}
}
stock ClassSel_HandleSpawnSelection(playerid)
{//вызывается из OnPlayerUpdate //как только игрок законектился постоянно вызывается
	new Keys,ud,lr;
    GetPlayerKeys(playerid,Keys,ud,lr);

    if(gPlayerSpawnSelection[playerid] == -1) {//нач. инициализация переключателя, сработает только 1 раз при коннекте
		ClassSel_SwitchToNextSpawn(playerid);//уст. gPlayerSpawnSelection[playerid] = SPAWN_STATION_LS;
		return;
	}

	// only allow new selection every ~500 ms
//задержка между сменой катсцены, увеличить если не успевает прогрузиться карта
//чтобы игрок не мог менять сцену каждую секунду
	if( (GetTickCount() - gPlayerLastSpawnSelectionTick[playerid]) < 500 ) return;

	if(Keys & KEY_FIRE) {
	    gPlayerHasSpawnSelected[playerid] = 1;//игрок выбрал спаун grandlarc_OnPlayerUpdate перестанет обрабатываться

	    //TextDrawHideForPlayer(playerid, txtSpawn);
	    //TextDrawHideForPlayer(playerid, txtClassSelHelper);

	    TogglePlayerSpectating(playerid, 0);//откл. режим спектатора, чтобы появились кнопки выбора спауна
//ВНИМАНИЕ
//Когда режим зрителя отключен, OnPlayerSpawn будет вызван автоматически,
//если вы хотите восстановить состояние игрока перед просмотром, вам придется справиться с этим в OnPlayerSpawn.
//Обратите также внимание, что игрок также может перейти к выбору класса раньше, если он использовал F4 во время spectate,
//игрок также может умереть в режиме spectate из-за различных сбоев.
// Если вам нужно породить игрока, пока он находится в режиме просмотра, используйте TogglePlayerSpectating, а не SpawnPlayer.
//В противном случае они не будут порождены, а вместо этого покажут игроку полет в воздухе
	    //запуститься grandlarc_OnPlayerRequestClass -> ClassSel_SetupCharSelection(playerid)
	    return;
	}
	if(lr > 0) {
	   ClassSel_SwitchToNextSpawn(playerid);
	}
	else if(lr < 0) {
	   ClassSel_SwitchToPreviousSpawn(playerid);
	}
}
stock ClassSel_SwitchToNextSpawn(playerid)
{//вызывает при нажатии стрелки вправо из ClassSel_HandleSpawnSelection(playerid) <- grandlarc_OnPlayerUpdate(playerid, newstate)
    gPlayerSpawnSelection[playerid]++;
	if(gPlayerSpawnSelection[playerid] > SPAWN_SCHOOL_SF) {//если дошли до конца, то установить начальный
	    gPlayerSpawnSelection[playerid] = SPAWN_EXIT;
	}

	PlayerPlaySound(playerid,1052,0.0,0.0,0.0);
	gPlayerLastSpawnSelectionTick[playerid] = GetTickCount();
	ClassSel_SetupSelectedCity(playerid);
}
stock ClassSel_SwitchToPreviousSpawn(playerid)
{//вызывается при нажатии стрелки влево из ClassSel_HandleSpawnSelection(playerid) <- grandlarc_OnPlayerUpdate(playerid, newstate)
    gPlayerSpawnSelection[playerid]--;
	if(gPlayerSpawnSelection[playerid] < SPAWN_EXIT) {
	    gPlayerSpawnSelection[playerid] = SPAWN_SCHOOL_SF;
	}
	
	PlayerPlaySound(playerid,1053,0.0,0.0,0.0);
	gPlayerLastSpawnSelectionTick[playerid] = GetTickCount();
	ClassSel_SetupSelectedCity(playerid);
}

stock ClassSel_SetupSelectedCity(playerid)////вызывается при нажатии стрелок на клаве
{//выбор спауна из ClassSel_SwitchToNextSpawn или ClassSel_SwitchToPreviousSpawn <- ClassSel_HandleSpawnSelection <- grandlarc_OnPlayerUpdate
//new strtmp[256];
//format(strtmp, sizeof(strtmp), "Begin ClassSel_SetupSelectedCity(playerid: %d, Int: %d[%d], Virt: %d[%d], Loc: %d)",
//		playerid, GetPlayerInterior(playerid), PlayerInfo[playerid][pInt], GetPlayerVirtualWorld(playerid), PlayerInfo[playerid][pVirtual], PlayerInfo[playerid][pLocal]);
//SendClientMessage(playerid, -1, strtmp);

	if(gPlayerSpawnSelection[playerid] == -1) {//при попутки переключателю принять -1  установить 0
		gPlayerSpawnSelection[playerid] = SPAWN_EXIT;
	}
	//--------------------------------------------------------------------------
	if(gPlayerSpawnSelection[playerid] == SPAWN_EXIT) {
		//PlayAudioStreamForPlayerEx(playerid, "GTAV_titles.mp3");
		
		//SetPlayerInterior(playerid,0);
   		/*SetPlayerCameraPos(playerid,1630.6136,-2286.0298,110.0);
		SetPlayerCameraLookAt(playerid,1887.6034,-1682.1442,47.6167);*/
		spawnPos[0][playerid] = PlayerInfo[playerid][pPos_x];
		spawnPos[1][playerid] = PlayerInfo[playerid][pPos_y];
		spawnPos[2][playerid] = PlayerInfo[playerid][pPos_z];
		
		SetPlayerInterior(playerid, PlayerInfo[playerid][pInt]);
		SetPlayerVirtualWorld(playerid, PlayerInfo[playerid][pVirtual]);
		SetPlayerPos(playerid, spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid]);

//нач. поз. движения камеры
	   	new Float:X1 = PlayerInfo[playerid][pPos_x];
		new Float:Y1 = PlayerInfo[playerid][pPos_y];
		GetXYInFrontOfPoint(15.0, 45, X1,Y1);
//конеч. поз. движения камеры
	   	new Float:X2 = PlayerInfo[playerid][pPos_x];
		new Float:Y2 = PlayerInfo[playerid][pPos_y];
		GetXYInFrontOfPoint(15.0, -45, X2,Y2);
//InterpolateCameraPos передвигает по сути само тело игрока, т.к. getplayerpos получает координаты
//и по сути значит блокирует SetPlayerPosEx SetPlayerInterior
//поэтому для того чтобы тело переместить в одну точку. а камеру в другую лучше использоваться SetPlayerCameraPos SetPlayerCameraLookAt
     	InterpolateCameraPos(playerid, X1,Y1,PlayerInfo[playerid][pPos_z]+15.0,	X2,Y2,PlayerInfo[playerid][pPos_z]+15.0, 5000);
		InterpolateCameraLookAt(playerid,	PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z],
			PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z], 5000);
   		//SetPlayerCameraPos(playerid, X2,Y2,PlayerInfo[playerid][pPos_z]+5.0);
		//SetPlayerCameraLookAt(playerid, PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z]);

	    TextDrawSetString(txtSpawn, "Place Output");
	}
	else if(gPlayerSpawnSelection[playerid] == SPAWN_STATION_LS) {
//1733.7374,-1890.5610,13.5850
		/*SetPlayerInterior(playerid,0);
   		SetPlayerCameraPos(playerid,-1300.8754,68.0546,129.4823);
		SetPlayerCameraLookAt(playerid,-1817.9412,769.3878,132.6589);*/
		spawnPos[0][playerid] = 1733.7374;
		spawnPos[1][playerid] = -1890.5610;
		spawnPos[2][playerid] = 13.5850;
		
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerPos(playerid, spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid]);
		
		InterpolateCameraPos(playerid, 1819.678710, -1836.177490, 31.484165, 1821.906372, -1940.021118, 28.839412, 5000);
		InterpolateCameraLookAt(playerid, 1815.383789, -1838.218017, 29.938304, 1817.262939, -1938.574340, 27.679508, 5000);
   		//SetPlayerCameraPos(playerid, 1821.906372, -1940.021118, 28.839412);
		//SetPlayerCameraLookAt(playerid, 1817.262939, -1938.574340, 27.679508);

//InterpolateCameraPos(playerid, 1957.158447,1179.158935,1147.138793, 1957.158447,1179.158935,1147.138793, 1000);
//InterpolateCameraLookAt(playerid, 1957.990600,1174.261840,1146.567504, 1957.990600,1174.261840,1146.567504, 1000);

	    TextDrawSetString(txtSpawn, "Station LS");
	}
	else if(gPlayerSpawnSelection[playerid] == SPAWN_HALL_LS) {
		/*SetPlayerInterior(playerid,0);
   		SetPlayerCameraPos(playerid,1310.6155,1675.9182,110.7390);
		SetPlayerCameraLookAt(playerid,2285.2944,1919.3756,68.2275);*/
		spawnPos[0][playerid] = 1481.1011;
		spawnPos[1][playerid] = -1770.8237;
		spawnPos[2][playerid] = 18.8957;
//1481.1011,-1770.8237,18.8957//,0.0
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerPos(playerid, spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid]);
		
		InterpolateCameraPos(playerid, 1484.195800, -1521.485717, 250.584548, 1479.419433, -1724.466674, 25.719228, 5000);
		InterpolateCameraLookAt(playerid, 1484.236572, -1524.949584, 246.978988, 1479.423339, -1729.148315, 23.963518, 5000);
   		//SetPlayerCameraPos(playerid, 1479.419433, -1724.466674, 25.719228);
		//SetPlayerCameraLookAt(playerid, 1479.423339, -1729.148315, 23.963518);

		TextDrawSetString(txtSpawn, "CityHall LS");
	}
	else if(gPlayerSpawnSelection[playerid] == SPAWN_BANK_LS) {
//1570.4503,-1337.4324,16.6844//,0.0
		//SetPlayerInterior(playerid,0);
   		/*SetPlayerCameraPos(playerid,1630.6136,-2286.0298,110.0);
		SetPlayerCameraLookAt(playerid,1887.6034,-1682.1442,47.6167);*/
		spawnPos[0][playerid] = 1570.4503;
		spawnPos[1][playerid] = -1337.4324;
		spawnPos[2][playerid] = 16.6844;
		
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerPos(playerid, spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid]);

		InterpolateCameraPos(playerid, 1654.224975, -1205.325927, 239.839233, 1575.375000, -1320.118164, 17.891624, 5000);
		InterpolateCameraLookAt(playerid, 1651.998046, -1208.978881, 237.251388, 1573.741821, -1324.843750, 17.853773, 5000);
   		//SetPlayerCameraPos(playerid, 1575.375000, -1320.118164, 17.891624);
		//SetPlayerCameraLookAt(playerid, 1573.741821, -1324.843750, 17.853773);


		TextDrawSetString(txtSpawn, "Bank LS");
	}
	else if(gPlayerSpawnSelection[playerid] == SPAWN_HOSPITAL_LS) {
//1172.2830,-1323.3102,15.3943
		//SetPlayerInterior(playerid,0);
   		/*SetPlayerCameraPos(playerid,-1300.8754,68.0546,129.4823);
		SetPlayerCameraLookAt(playerid,-1817.9412,769.3878,132.6589);*/
		spawnPos[0][playerid] = 1172.2830;
		spawnPos[1][playerid] = -1323.3102;
		spawnPos[2][playerid] = 15.3943;
		
	   	new Float:X1 = 1172.2830;
		new Float:Y1 = -1323.3102;
		new Float:A1 = 270+45; if(A1 > 360) A1 = A1 - 360;
		GetXYInFrontOfPoint(92.4, A1, X1,Y1);

	   	new Float:X2 = 1172.2830;
		new Float:Y2 = -1323.3102;
		new Float:A2 = 270-45; if(A2 < 0) A2 = 360 + A2;
		GetXYInFrontOfPoint(92.4, A2, X2,Y2);

		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerPos(playerid, spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid]);
		
     	InterpolateCameraPos(playerid, 	X1,Y1,15.3943+30.0,	X2,Y2,15.3943+30.0, 5000);
		InterpolateCameraLookAt(playerid, iEntrance_HospitalLS, iEntrance_HospitalLS, 5000);
   		//SetPlayerCameraPos(playerid, X2,Y2,15.3943+30.0);
		//SetPlayerCameraLookAt(playerid, iEntrance_HospitalLS);

		TextDrawSetString(txtSpawn, "Hospital LS");
	}
	else if(gPlayerSpawnSelection[playerid] == SPAWN_SCHOOL_SF) {
//-2077.8477,-114.1004,35.4840
		//SetPlayerInterior(playerid,0);
   		//SetPlayerCameraPos(playerid,1310.6155,1675.9182,110.7390);
		//SetPlayerCameraLookAt(playerid,2285.2944,1919.3756,68.2275);
		spawnPos[0][playerid] = -2077.84770;
		spawnPos[1][playerid] = -114.1004;
		spawnPos[2][playerid] = 35.4840;
		
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerPos(playerid, spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid]);
		
		InterpolateCameraPos(playerid, -1915.521484, -12.559217, 72.576377, -2083.793945, -92.086784, 49.244571, 5000);
		InterpolateCameraLookAt(playerid, -1919.225708, -15.730045, 71.469734, -2081.657470, -96.239341, 47.458122, 5000);
   		//SetPlayerCameraPos(playerid, -2083.793945, -92.086784, 49.244571);
		//SetPlayerCameraLookAt(playerid, -2081.657470, -96.239341, 47.458122);
		

		TextDrawSetString(txtSpawn, "School SF");
	}
	//ВНИМАНИЕ  тут нельзя SetSpawnInfo - спаунит сразу
	//SetSpawnInfo(playerid, 0, PlayerInfo[playerid][pModel],
	//	spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid], 0.0,
	//	-1, -1, -1, -1, -1, -1);
	
//new strtmp[256];
//format(strtmp, sizeof(strtmp), "End ClassSel_SetupSelectedCity(playerid: %d, Int: %d[%d], Virt: %d[%d], Loc: %d)",
//		playerid,  GetPlayerInterior(playerid), PlayerInfo[playerid][pInt], GetPlayerVirtualWorld(playerid), PlayerInfo[playerid][pVirtual], PlayerInfo[playerid][pLocal]);
//SendClientMessage(playerid, -1, strtmp);

}
//----------------------------------------------------------
//----------------------------------------------------------
//new player_request[MAX_PLAYERS];

//----------------------------------------------------------

//stock grandlarc_OnPlayerRequestClass(playerid, classid)
forward grandlarc_OnPlayerRequestClass(playerid, classid);
public grandlarc_OnPlayerRequestClass(playerid, classid)
{//Выполняется: 1. иногда при коннекте, 2. или после выхода из режима спектатора, 3. а также всегда при выборе игроком класса (скина).
//ИНФОРМИРОВАНИЕ
//new strtmp[256];
//format(strtmp, sizeof(strtmp), "grandlarc_OnPlayerRequestClass(playerid:%d, classid:%d, state:%d(SPECTATE:9))", playerid, classid, GetPlayerState(playerid));
//SendClientMessage(playerid, -1, strtmp);
	//#pragma unused classid
	//if(IsPlayerNPC(playerid)) return 1;

	if(gPlayerHasSpawnSelected[playerid])
	{//если игрок выбрал спаун, то переходим к выбору скина или роли
		ClassSel_SetupCharSelection(playerid, classid);
		
		/*if(player_request[playerid] == 0)
		{
		    SetPlayerSpawn(playerid);
			player_request[playerid] = 1;
		}*/
		//SpawnPlayer(playerid);
		
		//TextDrawSetString(txtClassSelHelper,
		//	" Press ~b~~k~~GO_LEFT~ ~w~or ~b~~k~~GO_RIGHT~ ~w~to switch roleplay.~n~ Press ~r~~k~~PED_JUMPING~ ~w~to spawn.");
		return 1;
	}
	else
	{//если ф-ия запустилась раньше коннекта и игрок не в режиме спектатора, а скорее всего в состоянии 0
		if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING) {
			TogglePlayerSpectating(playerid, 1);//включаем режим спектатора

    		TextDrawShowForPlayer(playerid, txtSpawn);
    		TextDrawShowForPlayer(playerid, txtClassSelHelper);//отображаем помощь по выбору спауна

    		gPlayerSpawnSelection[playerid] = -1;
		}
  	}
	return 0;
}

stock ClassSel_SetupCharSelection(playerid, classid)//выбор роли, режиме зрителя выключен
{//вызывается из grandlarc_OnPlayerRequestClass
//проблема в том, что стример не загружает объекты во время выбора класса
//OnPlayerRequestClass также не пашет TextDrawSetString
//ИНФОРМИРОВАНИЕ
//new strtmp[256];
//format(strtmp, sizeof(strtmp), "Begin ClassSel_SetupCharSelectio(playerid: %d, classid: %d, Int: %d[%d], Virt: %d[%d], Loc: %d)",
//		playerid, classid, GetPlayerInterior(playerid), PlayerInfo[playerid][pInt], GetPlayerVirtualWorld(playerid), PlayerInfo[playerid][pVirtual], PlayerInfo[playerid][pLocal]);
//SendClientMessage(playerid, -1, strtmp);

   	//if(gPlayerSpawnSelection[playerid] == SPAWN_EXIT) {
   	if(classid == 0) {
		//SetPlayerInterior(playerid,11);
		/*SetPlayerPos(playerid,508.7362,-87.4335,998.9609);
		SetPlayerFacingAngle(playerid,0.0);
    	SetPlayerCameraPos(playerid,508.7362,-83.4335,998.9609);
		SetPlayerCameraLookAt(playerid,508.7362,-87.4335,998.9609);*/
//vw_carriage
		//SetPlayerInterior(playerid, 0);
		//SetPlayerVirtualWorld(playerid, PlayerInfo[playerid][pVirtual]);

		//SetPlayerPos(playerid, 2989.1980,1071.5,103.4825);
		//SetPlayerFacingAngle(playerid, 98.0);
		//ApplyAnimation(playerid, "PED", "SEAT_DOWN",4.1, 0, 0, 0, 1, 0);
   		/*new Float:X = 2989.1980;
		new Float:Y = 1071.5000;
		GetXYInFrontOfPoint(5.0, 98.0, X,Y);
   		SetPlayerCameraPos(playerid,  X,Y, 103.4825);
		SetPlayerCameraLookAt(playerid, 2989.1980,1071.5,103.4825);*/
   		//SetPlayerCameraPos(playerid, 2986.7,1070.3419,103.8534);
		//SetPlayerCameraLookAt(playerid, PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z]);

//нач. поз. движения камеры
	   	new Float:X1 = PlayerInfo[playerid][pPos_x];
		new Float:Y1 = PlayerInfo[playerid][pPos_y];
		GetXYInFrontOfPoint(5.0, 45, X1,Y1);
//конеч. поз. движения камеры
	   	new Float:X2 = PlayerInfo[playerid][pPos_x];
		new Float:Y2 = PlayerInfo[playerid][pPos_y];
		GetXYInFrontOfPoint(5.0, -45, X2,Y2);
//InterpolateCameraPos передвигает по сути само тело игрока, т.к. getplayerpos получает координаты
//и по сути значит блокирует SetPlayerPosEx SetPlayerInterior
//поэтому для того чтобы тело переместить в одну точку. а камеру в другую лучше использоваться SetPlayerCameraPos SetPlayerCameraLookAt

		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerPos(playerid, PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z]);
		SetPlayerFacingAngle(playerid, 0.0);
		//ApplyAnimation(playerid, "PED", "SEAT_DOWN",4.1, 0, 0, 0, 1, 0);

     	InterpolateCameraPos(playerid, X1,Y1,PlayerInfo[playerid][pPos_z]+5.0,	X2,Y2,PlayerInfo[playerid][pPos_z]+1.0, 5000);
		InterpolateCameraLookAt(playerid,	PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z],
			PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z], 5000);

 	    SetSpawnInfo(playerid, 0, 133,
			spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid], 0.0,
			-1, -1, -1, -1, -1, -1);
//интерьер и мир устанавливаем в public OnPlayerSpawn(playerid)

		TextDrawSetString(txtSpawn, "Hurd Truck");
		//GameTextForPlayerEx(playerid, "~y~> ~p~Hurd Truck ~y~<",5000,4);
	}
	//else if(gPlayerSpawnSelection[playerid] == SPAWN_STATION_LS) {
	else if(classid == 1) {
		/*SetPlayerInterior(playerid,3);
		SetPlayerPos(playerid,-2673.8381,1399.7424,918.3516);
		SetPlayerFacingAngle(playerid,181.0);
    	SetPlayerCameraPos(playerid,-2673.2776,1394.3859,918.3516);
		SetPlayerCameraLookAt(playerid,-2673.8381,1399.7424,918.3516);*/
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerPos(playerid, spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid]);

//нач. поз. движения камеры
	   	new Float:X1 = spawnPos[0][playerid];
		new Float:Y1 = spawnPos[1][playerid];
		GetXYInFrontOfPoint(5.0, -45, X1,Y1);
//конеч. поз. движения камеры
	   	new Float:X2 = spawnPos[0][playerid];
		new Float:Y2 = spawnPos[1][playerid];
		GetXYInFrontOfPoint(5.0, 45, X2,Y2);
     	InterpolateCameraPos(playerid, X1,Y1,spawnPos[2][playerid]+4.0,	X2,Y2,spawnPos[2][playerid]+2.0, 5000);
		InterpolateCameraLookAt(playerid, spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid],
			spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid], 5000);

 	    SetSpawnInfo(playerid, 0, 300,
			spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid], 0.0,
			-1, -1, -1, -1, -1, -1);
		TextDrawSetString(txtSpawn, "Cop");
		//GameTextForPlayerEx(playerid, "~y~~y~> ~b~Cop ~y~~y~<",5000,4);
	}
	//else if(gPlayerSpawnSelection[playerid] == SPAWN_HALL_LS) {
	else if(classid == 2) {
		/*SetPlayerInterior(playerid,3);
		SetPlayerPos(playerid,349.0453,193.2271,1014.1797);
		SetPlayerFacingAngle(playerid,286.25);
    	SetPlayerCameraPos(playerid,352.9164,194.5702,1014.1875);
		SetPlayerCameraLookAt(playerid,349.0453,193.2271,1014.1797);*/
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerPos(playerid, spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid]);

//нач. поз. движения камеры
	   	new Float:X1 = spawnPos[0][playerid];
		new Float:Y1 = spawnPos[1][playerid];
		GetXYInFrontOfPoint(5.0, 45, X1,Y1);
//конеч. поз. движения камеры
	   	new Float:X2 = spawnPos[0][playerid];
		new Float:Y2 = spawnPos[1][playerid];
		GetXYInFrontOfPoint(5.0, -45, X2,Y2);
     	InterpolateCameraPos(playerid, X1,Y1,spawnPos[2][playerid]+4.0,	X2,Y2,spawnPos[2][playerid]+3.0, 5000);
		InterpolateCameraLookAt(playerid, spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid],
			spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid], 5000);
			
 	    SetSpawnInfo(playerid, 0, 248,
			spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid], 0.0,
			-1, -1, -1, -1, -1, -1);
		TextDrawSetString(txtSpawn, "Gangster");
		//GameTextForPlayerEx(playerid, "~y~> ~b~~b~Gangster ~y~<",5000,4);
	}
	
   	//else if(gPlayerSpawnSelection[playerid] == SPAWN_BANK_LS) {
   	/*else if(classid == 3) {
		SetPlayerInterior(playerid,11);
		SetPlayerPos(playerid,508.7362,-87.4335,998.9609);
		SetPlayerFacingAngle(playerid,0.0);
    	SetPlayerCameraPos(playerid,508.7362,-83.4335,998.9609);
		SetPlayerCameraLookAt(playerid,508.7362,-87.4335,998.9609);

 	    SetSpawnInfo(playerid, 0, 308,
			spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid], 0.0,
			-1, -1, -1, -1, -1, -1);
		TextDrawSetString(txtSpawn, "Paramedic");
	}
	//else if(gPlayerSpawnSelection[playerid] == SPAWN_HOSPITAL_LS) {
	else if(classid == 4) {
		SetPlayerInterior(playerid,3);
		SetPlayerPos(playerid,-2673.8381,1399.7424,918.3516);
		SetPlayerFacingAngle(playerid,181.0);
    	SetPlayerCameraPos(playerid,-2673.2776,1394.3859,918.3516);
		SetPlayerCameraLookAt(playerid,-2673.8381,1399.7424,918.3516);

 	    SetSpawnInfo(playerid, 0, 227,
			spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid], 0.0,
			-1, -1, -1, -1, -1, -1);
		TextDrawSetString(txtSpawn, "News Man");
	}
	//else if(gPlayerSpawnSelection[playerid] == SPAWN_SCHOOL_SF) {
	else if(classid == 5) {
		SetPlayerInterior(playerid,3);
		SetPlayerPos(playerid,349.0453,193.2271,1014.1797);
		SetPlayerFacingAngle(playerid,286.25);
    	SetPlayerCameraPos(playerid,352.9164,194.5702,1014.1875);
		SetPlayerCameraLookAt(playerid,349.0453,193.2271,1014.1797);
		
 	    SetSpawnInfo(playerid, 0, 73,
			spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid], 0.0,
			-1, -1, -1, -1, -1, -1);
		TextDrawSetString(txtSpawn, "Military Man");
	}*/

//ИНФОРМИРОВАНИЕ
//new strtmp[256];
//format(strtmp, sizeof(strtmp), "End ClassSel_SetupCharSelectio(playerid: %d, classid: %d, Int: %d[%d], Virt: %d[%d], Loc: %d)",
//		playerid, classid, GetPlayerInterior(playerid), PlayerInfo[playerid][pInt], GetPlayerVirtualWorld(playerid), PlayerInfo[playerid][pVirtual], PlayerInfo[playerid][pLocal]);
//SendClientMessage(playerid, -1, strtmp);
}

//----------------------------------------------------------

stock grandlarc_OnPlayerSpawn(playerid)
{
	if(IsPlayerNPC(playerid)) return 1;

	TextDrawHideForPlayer(playerid, txtSpawn);
	TextDrawHideForPlayer(playerid, txtClassSelHelper);

	//TogglePlayerClock(playerid,0);
 	//ResetPlayerMoney(playerid);
	//GivePlayerMoney(playerid, 30000);

	//SetPlayerInteriorEx(playerid,0);
	//SetPlayerVirtualWorldEx(playerid, 0);
//если менять спаун не через SetSpawnInfoEx, то будет банить сервер
	/*new randSpawn = 0;
	if(SPAWN_EXIT == gPlayerSpawnSelection[playerid]) {
 	    SetPlayerPosExEx(playerid, PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z], 0.0);
	}
	else if(SPAWN_STATION_LS == gPlayerSpawnSelection[playerid]) {
 		new Float:X = gRandomSpawns_StationLS[randSpawn][0];
		new Float:Y = gRandomSpawns_StationLS[randSpawn][1];
		new Float:Z = gRandomSpawns_StationLS[randSpawn][2];
		new Float:Ang = gRandomSpawns_StationLS[randSpawn][3];
		GetXYInFrontOfPoint(random(10), Ang, X,Y);
 	    SetPlayerPosExEx(playerid, X,Y,Z,Ang);
 	    //randSpawn = random(sizeof(gRandomSpawns_StationLS));
		//SetPlayerFacingAngle(playerid,gRandomSpawns_StationLS[randSpawn][3]);
	}
	else if(SPAWN_HALL_LS == gPlayerSpawnSelection[playerid]) {
 	    //randSpawn = random(sizeof(gRandomSpawns_CityHallLS));
 	    SetPlayerPosEx(playerid,
		 	gRandomSpawns_CityHallLS[randSpawn][0],
		 	gRandomSpawns_CityHallLS[randSpawn][1],
		 	gRandomSpawns_CityHallLS[randSpawn][2]);
		SetPlayerFacingAngle(playerid,gRandomSpawns_CityHallLS[randSpawn][3]);
	}
	else if(SPAWN_BANK_LS == gPlayerSpawnSelection[playerid]) {
 	    //randSpawn = random(sizeof(gRandomSpawns_BankLS));
 	    SetPlayerPosEx(playerid,
		 	gRandomSpawns_BankLS[randSpawn][0],
		 	gRandomSpawns_BankLS[randSpawn][1],
		 	gRandomSpawns_BankLS[randSpawn][2]);
		SetPlayerFacingAngle(playerid,gRandomSpawns_BankLS[randSpawn][3]);
	}
	else if(SPAWN_HOSPITAL_LS == gPlayerSpawnSelection[playerid]) {
 	    //randSpawn = random(sizeof(gRandomSpawns_HospitalLS));
 	    SetPlayerPosEx(playerid,
		 	gRandomSpawns_HospitalLS[randSpawn][0],
		 	gRandomSpawns_HospitalLS[randSpawn][1],
		 	gRandomSpawns_HospitalLS[randSpawn][2]);
		SetPlayerFacingAngle(playerid,gRandomSpawns_HospitalLS[randSpawn][3]);
	}
	else if(SPAWN_SCHOOL_SF == gPlayerSpawnSelection[playerid]) {
 	    //randSpawn = random(sizeof(gRandomSpawns_SchoolSF));
 	    SetPlayerPosEx(playerid,
		 	gRandomSpawns_SchoolSF[randSpawn][0],
		 	gRandomSpawns_SchoolSF[randSpawn][1],
		 	gRandomSpawns_SchoolSF[randSpawn][2]);
		SetPlayerFacingAngle(playerid,gRandomSpawns_SchoolSF[randSpawn][3]);
	}*/
	
/*
	SetPlayerColor(playerid,COLOR_NORMAL_PLAYER);//см. SetPlayerToTeamColor
	//SetPlayerColor(playerid,COLOR_NORMAL_PLAYER);//отображаем цвет игрока согласно этапа регистрации

//см. PlayerInfo_OnPlayerSpawn(playerid)
	SetPlayerSkillLevel(playerid,WEAPONSKILL_PISTOL,200);
    SetPlayerSkillLevel(playerid,WEAPONSKILL_PISTOL_SILENCED,200);
    SetPlayerSkillLevel(playerid,WEAPONSKILL_DESERT_EAGLE,200);
    SetPlayerSkillLevel(playerid,WEAPONSKILL_SHOTGUN,200);
    SetPlayerSkillLevel(playerid,WEAPONSKILL_SAWNOFF_SHOTGUN,200);
    SetPlayerSkillLevel(playerid,WEAPONSKILL_SPAS12_SHOTGUN,200);
    SetPlayerSkillLevel(playerid,WEAPONSKILL_MICRO_UZI,200);
    SetPlayerSkillLevel(playerid,WEAPONSKILL_MP5,200);
    SetPlayerSkillLevel(playerid,WEAPONSKILL_AK47,200);
    SetPlayerSkillLevel(playerid,WEAPONSKILL_M4,200);
    SetPlayerSkillLevel(playerid,WEAPONSKILL_SNIPERRIFLE,200);

    GivePlayerWeapon(playerid,WEAPON_COLT45,100);
	GivePlayerWeapon(playerid,WEAPON_MP5,100);
	//TogglePlayerClock(playerid, 0);
*/

    // Устанавливает игроку команду 4 при спавне
    SetPlayerTeam(playerid, NO_TEAM);
    
	return 1;
}


//----------------------------------------------------------

stock grandlarc_OnPlayerDeath(playerid, killerid, reason)
{
	#pragma unused reason
    new playercash;

    // if they ever return to class selection make them city
	// select again first
	gPlayerHasSpawnSelected[playerid] = 0;//игрок не выбрал спаун, чтобы при смерти предложить место спауна

	if(killerid == INVALID_PLAYER_ID) {
        ResetPlayerMoney(playerid);
	} else {
		playercash = GetPlayerMoney(playerid);
		if(playercash > 0)  {
			GivePlayerMoney(killerid, playercash);
			ResetPlayerMoney(playerid);
		}
	}
   	return 1;
}

//----------------------------------------------------------

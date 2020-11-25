//
// Used for testing interpolated rotations with MoveObjectEx
// Also used to test AttachObjectToObjectEx
// A cargo ship goes around and visits some route points
//
// SA-MP 0.3d and above
//
// - Kye 2011
//


//#define SOUND_RACE_321 	1056
//#define SOUND_RACE_GO 	1057

//==============================================================================
//для грузового судна //для грузчиков
#define SHIP_MOVE_SPEED         20.0
#define SHIP_DRAW_DISTANCE      300.0
#define SHIP_PAUSE 				300//5 минут

enum ship_info
{
	oModel,
	Float:oX,
	Float:oY,
	Float:oZ,
	Float:orX,
	Float:orY,
	Float:orZ
}

//НЕ ТРОГАТЬ координаты
new Float:gShipHullOrigin[ship_info] =
{5158, 2837.77, -2334.48, 11.9922, 0.0, 0.0, 0.0}; //Исходные координаты 2837.77, -2334.48, 11.9922

#define NUM_SHIP_ATTACHMENTS 9
new Float:gShipAttachment[NUM_SHIP_ATTACHMENTS][ship_info] = {
{5167, 2838.03, -2371.95, 7.29688, 0.0, 0.0, 270.0},//270.0 корма //LOD 5159 0 0 90
{5160, 2829.95, -2479.57, 5.26562, 0.0, 0.0, 270.0},// центр //LOD 5335
{5166, 2829.95, -2479.57, 5.26562, 0.0, 0.0, 270.0},// нос //LOD 5336

{5155, 2838.02, -2358.48, 21.3125, 0.0, 0.0, 270.0},// мостик //LOD 5161

{5156, 2838.04, -2423.88, 10.9609, 0.0, 0.0, 270.0},// нижня палуба //LOD 5162
{5157, 2838.04, -2532.77, 17.0234, 0.0, 0.0, 270.0},// верхняя палуба  //LOD 5163

{5154, 2838.14, -2447.84, 15.75, 0.0, 0.0, 270.0},// Bridge ducts and lights //LOD 5164

{3724, 2838.2, -2407.14, 29.3125, 0.0, 0.0, 270.0},//270.0 Cargo bay area//LOD 5164
{3724, 2838.2, -2488.66, 29.3125, 0.0, 0.0, 90.0}//90.0 Cargo bay area //LOD 5352 0 0 -90
};
//-------------------------------
new gShipCurrentPoint = 1; // current route point the ship is at. We start at route 1
//текущий маршрут указывает судно - в. Мы запускаем в маршруте 1

#define NUM_SHIP_ROUTE_POINTS   13
new Float:gShipRoutePoints[NUM_SHIP_ROUTE_POINTS][6] = {
{2828.0723,-2334.4426,13.6000, 0.0, 0.0, 0.0},//2837.77, -2334.48, 11.9922
{2828.0723,-2534.4426,12.9922, 1.0, 3.0, 45.0},//1

{3178.0723,-2984.4426,13.6020, 0.0, 0.0, 45.0},//2837.77, -2334.48, 11.9922
{3278.0723,-2984.4426,10.9922, -2.0, 3.0, 90.0},//2837.77, -2334.48, 11.9922
{3378.0723,-2984.4426,13.6020, 0.0, 3.0, 125.0},//2837.77, -2334.48, 11.9922

{3928.0723,-2534.4426,11.9922, 3.0, 0.0, 125.0},//2837.77, -2334.48, 11.9922
{3928.0723,-2334.4426,13.6020, 0.0, 3.0, 180.0},//2837.77, -2334.48, 11.9922
{3928.0723,-2134.4426,11.9922, -3.0, 3.0, 225.0},//2837.77, -2334.48, 11.9922

{3778.0723,-1854.4426,11.9922, 0.0, 0.0, 225.0},//2837.77, -2334.48, 11.9922
{3578.0723,-1854.4426,13.6020, 2.0, 3.0, 270.0},//2837.77, -2334.48, 11.9922
{3378.0723,-1854.4426,11.9922, 0.0, 3.0, 315.0},//2837.77, -2334.48, 11.9922

{3128.0723,-2134.4426,13.6020, -1.0, 0.0, 315.0},
{2828.0723,-2334.4426,13.6000, 0.0, 3.0, 360.0}
};
new gMoveCountdown = -1;
new movecountdown = SHIP_PAUSE;


new gMainShipObjectId;
new gShipsAttachments[NUM_SHIP_ATTACHMENTS];
//==============================================================================
stock cargoship_OnGameModeInit()
{
	//для грузового судна начало
	gMainShipObjectId = CreateObjectEx(gShipHullOrigin[oModel],
					 		gShipRoutePoints[0][0],
							gShipRoutePoints[0][1],
							gShipRoutePoints[0][2],
							gShipRoutePoints[0][3],
							gShipRoutePoints[0][4],
							gShipRoutePoints[0][5]);
	new x=0;
	while(x < NUM_SHIP_ATTACHMENTS) {
	    gShipsAttachments[x] = CreateObjectEx(gShipAttachment[x][oModel],
				 			gShipAttachment[x][oX],
							gShipAttachment[x][oY],
							gShipAttachment[x][oZ],
							gShipAttachment[x][orX],//сразу создаём его под правильным углом
							gShipAttachment[x][orY],
							gShipAttachment[x][orZ]);//просто создаём объект
		AttachObjectToObjectEx(gShipsAttachments[x], gMainShipObjectId,//присоединяем gShipsAttachments[x] к gMainShipObjectId
							gShipAttachment[x][oX] - gShipHullOrigin[oX],
							gShipAttachment[x][oY] - gShipHullOrigin[oY],
							gShipAttachment[x][oZ] - gShipHullOrigin[oZ],
							gShipAttachment[x][orX],
							gShipAttachment[x][orY],
							gShipAttachment[x][orZ]);
		x++;
	}
    /*x=0;
	while(x != NUM_SHIP_ROUTE_POINTS) {
		for(new i=0; i<GetMaxPlayers(); i++)
		{
			if( !IsPlayerConnected(i)) continue;
			RemovePlayerMapIcon(i, MAX_PLAYER_ICONS-x);
			SetPlayerMapIcon(i,	MAX_PLAYER_ICONS-x,
					 	gShipRoutePoints[x][0],
						gShipRoutePoints[x][1],
						gShipRoutePoints[x][2],
						0,	COLOR_RED,	MAPICON_GLOBAL_CHECKPOINT);
						//20, 0, MAPICON_GLOBAL);//19
		}
		x++;
	}*/
	if(gMoveCountdown != -1) { KillTimer(gMoveCountdown); gMoveCountdown = -1; }	//movecountdown = SHIP_PAUSE;
	gMoveCountdown = SetTimer("CargoShipCountdownTimer",1000,1);
	//для грузового судна конец
	print(" ");
	print("   vw_cargoship 1.2 By: Kye 2011&Danger1979");
	print("_____________________________________________");
	print(" ");
}

stock cargoship_OnPlayerConnect(playerid)
{
//"Clean" CargoShip1LS[0.3d] //для грузчиков //для грузового судна
	RemoveBuildingForPlayerEx(playerid, 5167, 2838.03, -2371.95, 7.29688, 0.25);// корма
	RemoveBuildingForPlayerEx(playerid, 5159, 2838.03, -2371.95, 7.29688, 0.25); //LOD 5159 0 0 90

	RemoveBuildingForPlayerEx(playerid, 5160, 2829.95, -2479.57, 5.26562, 0.25);// центр
	RemoveBuildingForPlayerEx(playerid, 5335, 2829.95, -2479.57, 5.26562, 0.25);//LOD 5335

	RemoveBuildingForPlayerEx(playerid, 5166, 2829.95, -2479.57, 5.26562, 0.25);// нос
	RemoveBuildingForPlayerEx(playerid, 5336, 2829.95, -2479.57, 5.26562, 0.25);//LOD 5336

	RemoveBuildingForPlayerEx(playerid, 5155, 2838.02, -2358.48, 21.3125, 0.25);// мостик
	RemoveBuildingForPlayerEx(playerid, 5161, 2838.02, -2358.48, 21.3125, 0.25);//LOD 5161

	RemoveBuildingForPlayerEx(playerid, 5158, 2837.77, -2334.48, 11.9922, 0.25); // краны под шлюпки
	RemoveBuildingForPlayerEx(playerid, 5336, 2837.77, -2334.48, 11.9922, 0.25); //LOD 5336 0 0 0

	RemoveBuildingForPlayerEx(playerid, 5156, 2838.04, -2423.88, 10.9609, 0.25);// нижня палуба
	RemoveBuildingForPlayerEx(playerid, 5162, 2838.04, -2423.88, 10.9609, 0.25);//LOD 5162

	RemoveBuildingForPlayerEx(playerid, 5157, 2838.04, -2532.77, 17.0234, 0.25);// верхняя палуба
	RemoveBuildingForPlayerEx(playerid, 5163, 2838.04, -2532.77, 17.0234, 0.25); //LOD 5163

	RemoveBuildingForPlayerEx(playerid, 5165, 2838.03, -2520.19, 18.4141, 0.25);// верхняя палуба

	RemoveBuildingForPlayerEx(playerid, 5154, 2838.14, -2447.84, 15.75, 0.25);// Bridge ducts and lights
	RemoveBuildingForPlayerEx(playerid, 5164, 2838.14, -2447.84, 15.75, 0.25); //LOD 5164

	RemoveBuildingForPlayerEx(playerid, 3724, 2838.2, -2407.14, 29.3125, 0.25);// Cargo bay area
	RemoveBuildingForPlayerEx(playerid, 5164, 2838.2, -2407.14, 29.3125, 0.25);//LOD 5164

	RemoveBuildingForPlayerEx(playerid, 3724, 2838.2, -2488.66, 29.3125, 0.25);// Cargo bay area
	RemoveBuildingForPlayerEx(playerid, 5352, 2838.2, -2488.66, 29.3125, 0.25);// Cargo bay area//LOD 5164
}

//для грузового судна //для грузчиков
forward CargoShipCountdownTimer();
public CargoShipCountdownTimer()//CargoShipCountdownTimer
{//запускается каждую секунду в течении 30 секунд, надо чтобы за это время объект заканчивал своё движения
	movecountdown --;//15
	switch(movecountdown)
	{
		case 0:
		{
			if(gMoveCountdown != -1) { KillTimer(gMoveCountdown); gMoveCountdown = -1;	movecountdown = SHIP_PAUSE; }
			MoveObjectEx(gMainShipObjectId,gShipRoutePoints[gShipCurrentPoint][0],
			                           gShipRoutePoints[gShipCurrentPoint][1],
									   gShipRoutePoints[gShipCurrentPoint][2]+0.01,
									   SHIP_MOVE_SPEED / 2.0, // slower for the first route
									   gShipRoutePoints[gShipCurrentPoint][3],
									   gShipRoutePoints[gShipCurrentPoint][4],
									   gShipRoutePoints[gShipCurrentPoint][5]);

			new strtmp[3];
			format(strtmp, sizeof(strtmp), "%d", movecountdown);
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
   //выводим всем игрокам
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				if(PlayerInfo[i][pJob] == LOADER)
				{
					PlaySoundForPlayer(i, SOUND_RACE_GO);
				}
			}

		    /*format(strings, sizeof(strings), "Корабль вывез товаров на сумму $%d.", 140000);
		    SendClientMessageToAll(COLOR_DARKBLUE, strings);

		    format(strings, sizeof(strings), "Штат покинуло %d туристов", 4);
		    SendClientMessageToAll(COLOR_DARKRED, strings);*/
    /*new tempdebug[256+1];
    format(tempdebug,256,"Судно - в маршруте на точку: %d [%.2f,%.2f,%.2f, %.2f,%.2f,%.2f]", gShipCurrentPoint,
			gShipRoutePoints[gShipCurrentPoint][0],
			gShipRoutePoints[gShipCurrentPoint][1],
			gShipRoutePoints[gShipCurrentPoint][2],
			gShipRoutePoints[gShipCurrentPoint][3],
			gShipRoutePoints[gShipCurrentPoint][4],
			gShipRoutePoints[gShipCurrentPoint][5]);
    SendClientMessageToAll(0xFFFFFFFF,tempdebug);*/
		}
		case 3,2,1://для приготовления к старту
		{
			new strtmp[3];
			format(strtmp, sizeof(strtmp), "%d", movecountdown);
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
   //выводим всем игрокам
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				if(PlayerInfo[i][pJob] == LOADER)
				{
					PlaySoundForPlayer(i, SOUND_RACE_321);
					GameTextForPlayerEx(i, strtmp, 750, 5);
				}
			}
		}
		case 5://для приготовления к старту
		{
			PlaySoundForPlayersInRange(3201, 200.0,
							gShipRoutePoints[gShipCurrentPoint][0],
							gShipRoutePoints[gShipCurrentPoint][1],
							gShipRoutePoints[gShipCurrentPoint][2]);
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				if(PlayerInfo[i][pJob] == LOADER)
		   		{
		   			PlaySoundForPlayer(i, 3200);
					SendClientMessage(i, COLOR_RED, "   Грузовое судно отплывает через 5 секунд !");
				}
			}
		}
		case 10://для приготовления к старту
		{
			PlaySoundForPlayersInRange(3201, 200.0,
							gShipRoutePoints[gShipCurrentPoint][0],
							gShipRoutePoints[gShipCurrentPoint][1],
							gShipRoutePoints[gShipCurrentPoint][2]);
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				if(PlayerInfo[i][pJob] == LOADER)
		   		{   //gOnDuty[i] == 0
					PlaySoundForPlayer(i, 3201);
					SendClientMessage(i, COLOR_LIGHTBLUE, "   Грузовое судно отплывает через 10 секунд !");
				}
			}
		}
		case 15,20,30,40,50,60,90,120://для общего информирования
		{
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				if(PlayerInfo[i][pJob] == LOADER)
		   		{   //gOnDuty[i] == 0
		   			new strtmp[43+3];
					format(strtmp, sizeof(strtmp), "~w~CARGO SHIP STARTING IN ~y~%d ~w~SECONDS", movecountdown);
					GameTextForPlayerEx(i,strtmp, 2000, 4);
				}
			}
		}
	}
}
stock cargoship_OnObjectMoved(objectid)
{   //вызывается из OnObjectMoved //каждые 2 минуты и 30 секунд корабль уплывает
//60/2.5 = 24 рейса за час
	if(objectid != gMainShipObjectId) return 0;

	/*if(gShipCurrentPoint > 0 && !(gShipCurrentPoint % 5)) {
	    //каждую 5 точку проигрывать звук
		PlaySoundForPlayersInRange(6200, 200.0,
						gShipRoutePoints[gShipCurrentPoint][0],
						gShipRoutePoints[gShipCurrentPoint][1],
						gShipRoutePoints[gShipCurrentPoint][2]);
	}*/

    gShipCurrentPoint++;
    if(gShipCurrentPoint == NUM_SHIP_ROUTE_POINTS)
	{//если дошли до конца, то обнулить
		gShipCurrentPoint = 0;
   		MoveObjectEx(gMainShipObjectId,gShipRoutePoints[gShipCurrentPoint][0],
	                           gShipRoutePoints[gShipCurrentPoint][1],
							   gShipRoutePoints[gShipCurrentPoint][2]+0.01,
							   SHIP_MOVE_SPEED / 2.0, // slower for the last route
							   gShipRoutePoints[gShipCurrentPoint][3],
							   gShipRoutePoints[gShipCurrentPoint][4],
							   gShipRoutePoints[gShipCurrentPoint][5]);
        return 1;
	}
	if(gShipCurrentPoint == 1) {
	    //Прежде, чем начать первый маршрут мы должны ожидать немного
	    //начинаем отсчёт
		if(gMoveCountdown != -1) { KillTimer(gMoveCountdown); gMoveCountdown = -1; movecountdown = SHIP_PAUSE; }
		gMoveCountdown = SetTimer("CargoShipCountdownTimer",1000,1); // pause at route 0 for 30 seconds

	    //format(strings, sizeof(strings), "В штат прибыло ни-много ни-мало %d туристов.", 14);
	    //SendClientMessageToAll(COLOR_DARKGREEN, strings);
		return 1;
	}
    /*new tempdebug[256+1];
    format(tempdebug,256,"Судно - в маршруте на точку: %d [%.2f,%.2f,%.2f, %.2f,%.2f,%.2f]", gShipCurrentPoint,
			gShipRoutePoints[gShipCurrentPoint][0],
			gShipRoutePoints[gShipCurrentPoint][1],
			gShipRoutePoints[gShipCurrentPoint][2],
			gShipRoutePoints[gShipCurrentPoint][3],
			gShipRoutePoints[gShipCurrentPoint][4],
			gShipRoutePoints[gShipCurrentPoint][5]);
    SendClientMessageToAll(0xFFFFFFFF,tempdebug);*/
    MoveObjectEx(gMainShipObjectId,gShipRoutePoints[gShipCurrentPoint][0],
	                           gShipRoutePoints[gShipCurrentPoint][1],
							   gShipRoutePoints[gShipCurrentPoint][2]+0.01,
							   SHIP_MOVE_SPEED,
							   gShipRoutePoints[gShipCurrentPoint][3],
							   gShipRoutePoints[gShipCurrentPoint][4],
							   gShipRoutePoints[gShipCurrentPoint][5]);

	return 1;
}

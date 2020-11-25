/*
 *            vw_gps 188
 *       (c) Copyright 2009-2019 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (https://vk.com/id174413521)
 * @date      : 13.03.2019
 * @update    : 18.03.2019
 *
 * This file is provided as is (no warranties).
 * thank by Gamer_Z
 */

//закоментировать инклюды при подключении в мод


#define NAN (Float:0x7FFFFFFF)
#define MAX_DOTS 500

//#define GPS_FILTERSCRIPT
// This is a comment
// uncomment the line below if you want to write a filterscript

//#define GPS_DEBUG

/*
#if defined GPS_FILTERSCRIPT
#include <a_samp>
#include <streamer>
#include <RouteConnector>
#endif
*/

//массив для хранени данных о маршруте, который состоит из гангзон
enum RouteInformation
{
    RouteID,//принимает значение 1 если игроку создан маршрут, или 0 если нет. это ID динамического массива, не путать с NodeID
	PolygonID,//принимает значение 1 если игроку создан маршрут, или 0 если нет. это ID динамического массива, не путать с NodeID
    Zones[1024], //ID созданных ганг-зон //There is a limit of 1024 gangzones.
    ZonesSize,//кол-во созданный ганг зон для прокладки маршрута, нужно для циклов
    Calculating,//тригер, что путь этому игроку проложен
    Destination,//ID узла конечной точки
    bool:IsInGPS_Polygon//тригер: игрок на маршруте или ушёл с маршрута
};
new Storage[MAX_PLAYERS][RouteInformation];//по индексу игрока хранит ID зоны

//у каждого игрока своя конечная точка
new DestinationNodeID[MAX_PLAYERS] = {-1, ...};//по индексу игрока хранит NodeID узла конечной точки = NearestNodeFromPoint(1345.2018,746.1505,10.2350);


//очень сильно увеличивают память
//new PlayerZones[MAX_PLAYERS][MAX_DOTS];// = {-1, ...}; по индексу игрока хранит все узлы в маршруте
//new Text3D:GPSLabels[MAX_PLAYERS][MAX_DOTS];
//new GPSObjects[MAX_PLAYERS][MAX_DOTS];


#if defined GPS_FILTERSCRIPT

public OnFilterScriptInit()
{
	for(new playerid = 0; playerid < GetMaxPlayers(); playerid++)
	{
		if(!IsPlayerConnected(playerid)) continue;
		Storage[playerid][RouteID] = (-1);
		Storage[playerid][PolygonID] = (-1);
		Storage[playerid][ZonesSize] = 0;
		Storage[playerid][Calculating] = 0;
		Storage[playerid][Destination] = (-1);
		Storage[playerid][IsInGPS_Polygon] = false;
		//for(new x; x < MAX_DOTS; x++) PlayerZones[playerid][x] = -1;
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "Click on the map and then enter the command /gps");
	}
	print("   vw_gps 188 By: Gamer_Z");
	print("_____________________________________________");
	print(" ");
	return 1;
}

public OnFilterScriptExit()
{

	DestroyAllDynamicObjects();
	DestroyAllDynamicMapIcons();
	DestroyAllDynamic3DTextLabels();

	//возможно надо по полной чистить для MAX_PLAYERS, т.к. может зайти игрок и для его ИД уже будет создан 3дтекст
	//for(new playerid = 0; playerid < GetMaxPlayers(); playerid++)
	for(new playerid = 0; playerid < MAX_PLAYERS; ++playerid)
	{
		//if(!IsPlayerConnected(playerid)) continue;
		DisableGPS(playerid);
		
		if(Storage[playerid][RouteID] >= 0)
		{//удаляем массив для этого игрока
			DeleteArray(Storage[playerid][RouteID]);
		}
  		if(Storage[playerid][PolygonID] != (-1))
		{
			DestroyDynamicArea(Storage[playerid][PolygonID]);
			Storage[playerid][PolygonID] = (-1);
		}
		Storage[playerid][Calculating] = 0;
	}
	return 1;
}

/*stock strtok(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}

	new offset = index;
	new result[20];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}*/

#endif

stock gps_trucker(playerid, trailerid)
{
 	if(Storage[playerid][Calculating])
    {
        SendClientMessage(playerid,0xFFFF00FF,"Пожалуйста, подождите, прежде чем выбрать ваш следующий пункт назначения!");
        return 1;
    }

//находим ближайший к конечной точке узел
	new biz, sbiz;
	if(Cargo[trailerid][tWhere] >= 100)//куда
	{
		sbiz = Cargo[trailerid][tWhere]-100;//куда
		DestinationNodeID[playerid] = NearestNodeFromPoint(SBizInfo[sbiz][sbEntranceX],	SBizInfo[sbiz][sbEntranceY], SBizInfo[sbiz][sbEntranceZ]);//км
	}
	else
	{
		biz = Cargo[trailerid][tWhere];//куда
		DestinationNodeID[playerid] = NearestNodeFromPoint(BizInfo[biz][bEntranceX], BizInfo[biz][bEntranceY], BizInfo[biz][bEntranceZ]);//км
	}
    if(DestinationNodeID[playerid] == -1)
    {
        //SendClientMessage(playerid,0xFF0000FF,"Пункт назначения вне зоны покрытия.");
		SendClientMessage(playerid,0xFF0000FF,"Вы не указали на карте пункт назначения. Попробуйте ещё раз.");
        return 1;
    }
    //if(Storage[playerid][Destination] != -1)
    //{
	DisableGPS(playerid);
    //}
    //new NearestPlayerNodeID = NearestPlayerNode(playerid);//находим ближайший к игроку узел, а не к конечной точке

	new NearestPointNodeID;//находим ближайший к начальной точке узел
	if(Cargo[trailerid][tWhence] >= 100)//откуда
	{
		sbiz = Cargo[trailerid][tWhence]-100;//откуда
		NearestPointNodeID = NearestNodeFromPoint(SBizInfo[sbiz][sbEntranceX],	SBizInfo[sbiz][sbEntranceY], SBizInfo[sbiz][sbEntranceZ]);//км
	}
	else
	{
		biz = Cargo[trailerid][tWhence];//откуда
		NearestPointNodeID = NearestNodeFromPoint(BizInfo[biz][bEntranceX], BizInfo[biz][bEntranceY], BizInfo[biz][bEntranceZ]);//км
	}
    if(NearestPointNodeID == -1)
    {
        SendClientMessage(playerid,0xFF0000FF,"Начальная точка не доступна. Попробуйте выбрать другую.");
        return 1;
    }
    if(CalculatePath(NearestPointNodeID, DestinationNodeID[playerid], playerid, .GrabNodePositions = true))
    {//создаём маршрут из ближайшего узла от игрока к ID узла конечной точки
        Storage[playerid][Calculating] = 1;
        SendClientMessage(playerid,0xFFFF00FF,"Соединение со спутниками установлено!");

		//new trailerid;//, trailermodel;
		//if(IsTrailerAttachedToVehicle(nCarID[playerid])) { trailerid = nTrailerID[playerid]; }
		//else { trailerid = nCarID[playerid]; }

        //new strtmp[MAX_STRING];
       	//format(strtmp, sizeof(strtmp), "Длина маршрута по дорогам составляет %.1f м", Cargo[trailerid][tDistance] );
        //SendClientMessage(playerid, -1, strtmp);
    }
    else
    {
        SendClientMessage(playerid,0xFF0000FF,"Произошла ошибка... Попробуйте еще раз!");
    }
    return 1;
}



stock gps_OnPlayerConnect(playerid)
//public OnPlayerConnect(playerid)
{
	GPS_OnOff[playerid] = 1;//временнно для навигатора

	//gps_AddPlayer(playerid);//будем добавлять только при активации GPS
	Storage[playerid][RouteID] = (-1);
	Storage[playerid][PolygonID] = (-1);
	Storage[playerid][ZonesSize] = 0;
	Storage[playerid][Calculating] = 0;
	Storage[playerid][Destination] = (-1);
	Storage[playerid][IsInGPS_Polygon] = false;
	//for(new x; x < MAX_DOTS; x++) PlayerZones[playerid][x] = -1;
	
	/*#if defined gps_OnPlayerConnect
		return gps_OnPlayerConnect(playerid);
	#else
		return 0; // Allow other scripts to keep processing OnPlayerConnect
	#endif*/
}
/*#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect gps_OnPlayerConnect
#if defined gps_OnPlayerConnect
	forward gps_OnPlayerConnect(playerid);
#endif*/

stock gps_OnPlayerDisconnect(playerid, reason)
//public OnPlayerDisconnect(playerid, reason)
{
	#pragma unused reason
	gps_RemovePlayer(playerid);
	if(Storage[playerid][PolygonID] != (-1))
	{
		DestroyDynamicArea(Storage[playerid][PolygonID]);
		Storage[playerid][PolygonID] = (-1);
	}
	if(Storage[playerid][ZonesSize] != 0)
	{
        for(new i = 0; i < Storage[playerid][ZonesSize]; ++i)
        {
            //GangZoneHideForAll(Storage[playerid][Zones][i]);
            GangZoneHideForPlayer(playerid, Storage[playerid][Zones][i]);
            GangZoneDestroy(Storage[playerid][Zones][i]);
        }
		Storage[playerid][ZonesSize] = 0;
	}
/*
	#if defined gps_OnPlayerDisconnect
		return gps_OnPlayerDisconnect(playerid, reason);
	#else
		return 0; // Allow other scripts to keep processing OnPlayerConnect
	#endif
*/
}
/*
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect gps_OnPlayerDisconnect
#if defined gps_OnPlayerDisconnect
	forward gps_OnPlayerDisconnect(playerid, reason);
#endif
*/

stock gps_OnPlayerDeath(playerid, killerid, reason)
//public OnPlayerDeath(playerid, killerid, reason)
{
	#pragma unused killerid
	#pragma unused reason
	
	DisableGPS(playerid);
	Storage[playerid][Calculating] = 0;
	/*#if defined gps_OnPlayerDeath
		return gps_OnPlayerDeath(playerid, killerid, reason);
	#else
		return 0; // Allow other scripts to keep processing OnPlayerConnect
	#endif*/
}
/*#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath gps_OnPlayerDeath
#if defined gps_OnPlayerDeath
	forward gps_OnPlayerDeath(playerid, killerid, reason);
#endif*/


stock gps_OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
//public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
    /*if(Storage[playerid][Calculating] == 0)
    {
        if(Storage[playerid][Destination] != (-1) || Storage[playerid][PolygonID] !=(-1))
		{
			DestroyDynamicArea(Storage[playerid][PolygonID]);
			for(new i = 0; i < Storage[playerid][IconsSize]; ++i)
			{
			    DestroyDynamicMapIcon(Storage[playerid][Icons][i]);
			}
			Storage[playerid][PolygonID] = (-1);
			Storage[playerid][ZonesSize] = 0;
			Storage[playerid][Calculating] = 0;
			Storage[playerid][Destination] = (-1);
			
		}
		DestinationNodeID[playerid] = NearestNodeFromPoint(fX,fY,fZ);
	}*/
	//if(DestinationNodeID[playerid] != -1) return 1;
	DestinationNodeID[playerid] = NearestNodeFromPoint(fX,fY,fZ);
	return 1;

	/*#if defined gps_OnPlayerClickMap
		return gps_OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ);
	#else
		return 0; // Allow other scripts to keep processing OnPlayerConnect
	#endif*/
}
/*#if defined _ALS_OnPlayerClickMap
	#undef OnPlayerClickMap
#else
	#define _ALS_OnPlayerClickMap
#endif
#define OnPlayerClickMap gps_OnPlayerClickMap
#if defined gps_OnPlayerClickMap
	forward gps_OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ);
#endif*/

stock gps_OnPlayerCommandText(playerid)
{
 	if(Storage[playerid][Calculating])
    {
        SendClientMessage(playerid,COLOR_YELLOW,"Пожалуйста, подождите, прежде чем выбрать ваш следующий пункт назначения!");
        return 1;
    }
    if(DestinationNodeID[playerid] == -1)
    {
        //SendClientMessage(playerid,COLOR_RED,"Пункт назначения вне зоны покрытия.");
		SendClientMessage(playerid,COLOR_RED,"Вы не указали на карте пункт назначения. Попробуйте ещё раз.");
        return 1;
    }
    //if(Storage[playerid][Destination] != -1)
    //{
	DisableGPS(playerid);
    //}
    new NearestPlayerNodeID = NearestPlayerNode(playerid);//находим ближайший к игроку узел, а не к конечной точке
    if(NearestPlayerNodeID == -1)
    {
        SendClientMessage(playerid,COLOR_RED,"Вы вне зоны видимости. Попробуйте выехать на дорогу.");
        return 1;
    }
    if(CalculatePath(NearestPlayerNodeID, DestinationNodeID[playerid], playerid, .GrabNodePositions = true))
    {//создаём маршрут из ближайшего узла от игрока к ID узла конечной точки
        Storage[playerid][Calculating] = 1;
        SendClientMessage(playerid,COLOR_YELLOW,"Соединение со спутниками установлено!");
    }
    else
    {
        SendClientMessage(playerid,COLOR_RED,"Произошла ошибка... Попробуйте еще раз!");
    }
    return 1;
}
/*
public OnPlayerCommandText(playerid, cmdtext[])
{
	//new cmd[256+1];	new	idx;
	//cmd = strtok(cmdtext, idx);
	//if(strcmp("/changer", cmd, true) == 0)
	if(strcmp("/gps", cmdtext, true, 10) == 0)
	{
		gps_OnPlayerCommandText(playerid);
		
		if(Storage[playerid][Calculating])
	    {
	        SendClientMessage(playerid,COLOR_YELLOW,"Пожалуйста, подождите, прежде чем выбрать ваш следующий пункт назначения!");
	        return 1;
	    }
	    if(DestinationNodeID[playerid] == -1)
	    {
	        //SendClientMessage(playerid,COLOR_RED,"Пункт назначения вне зоны покрытия.");
			SendClientMessage(playerid,COLOR_RED,"Вы не указали на карте пункт назначения. Попробуйте ещё раз.");
	        return 1;
	    }
	    //if(Storage[playerid][Destination] != -1)
	    //{
		DisableGPS(playerid);
	    //}
	    new NearestPlayerNodeID = NearestPlayerNode(playerid);//находим ближайший к игроку узел, а не к конечной точке
	    if(NearestPlayerNodeID == -1)
	    {
	        SendClientMessage(playerid,COLOR_RED,"Вы вне зоны видимости. Попробуйте выйти на дорогу.");
	        return 1;
	    }
	    if(CalculatePath(NearestPlayerNodeID, DestinationNodeID[playerid], playerid, .GrabNodePositions = true))
	    {//создаём маршрут из ближайшего узла от игрока к ID узла конечной точки
	        Storage[playerid][Calculating] = 1;
	        SendClientMessage(playerid,COLOR_YELLOW,"Соединение со спутниками установлено!");
	    }
	    else
	    {
	        SendClientMessage(playerid,COLOR_RED,"Произошла ошибка... Попробуйте еще раз!");
	    }
	    return 1;
	}
	//return 0;
//}

	#if defined gps_OnPlayerCMDText
		return gps_OnPlayerCMDText(playerid, cmdtext);
	#else
		return 0; // Allow other scripts to keep processing OnPlayerConnect
	#endif
}
#if defined _ALS_OnPlayerCommandText
	#undef OnPlayerCommandText
#else
	#define _ALS_OnPlayerCommandText
#endif
#define OnPlayerCommandText gps_OnPlayerCMDText
#if defined gps_OnPlayerCMDText
	forward gps_OnPlayerCMDText(playerid, cmdtext[]);
#endif*/

#define MAP_ICON_DRAW_DISTANCE 500.0
#define NODE_DRAW_DISTANCE 45.0
/*
#define CONNECTION_DRAW_DISTANCE 15.0
#define CONNECTION_COLOR COLOR_RED// There is no node color here. Change it in the code below.
*/
public GPS_WhenRouteIsCalculated(routeid,node_id_array[],amount_of_nodes,Float:distance,Float:Polygon[],Polygon_Size,Float:NodePosX[],Float:NodePosY[],Float:NodePosZ[])
{//routeid = playerid //вызывается 1 раз после запуска CalculatePath
#if defined GPS_DEBUG//#endif
	DestroyAllDynamicObjects();
	DestroyAllDynamicMapIcons();
	DestroyAllDynamic3DTextLabels();
#endif
	new playerid = routeid;
	new trailerid;//, trailermodel;
	if(IsTrailerAttachedToVehicle(nCarID[playerid])) { trailerid = nTrailerID[playerid]; }
	else { trailerid = nCarID[playerid]; }
	Cargo[trailerid][tDistance] = distance;
	//SetPVarFloat(playerid, varname[], Float:float_value);

	new strtmp[MAX_STRING];
	format(strtmp, sizeof(strtmp), "Продолжайте движение %.1f м", Cargo[trailerid][tDistance] );
	SendClientMessage(playerid, -1, strtmp);

//для каждого игрока routeid
	Storage[routeid][RouteID] = StoreRouteArray(amount_of_nodes, node_id_array);//записали ИД массива узлов всего маршрута, чтобы по этому указатели можно было очистить память от массива
    Storage[routeid][Calculating] = 0;
    if(amount_of_nodes > 1)
    {//если кол-во точек в маршруте больше 1

        for(new i = 0; i < amount_of_nodes; ++i)//amount_of_nodes
		//for(new i = 0; i < MAX_DOTS; ++i)//amount_of_nodes
        {//перебираем все узлы из созданного массива node_id_array
#if defined GPS_DEBUG//#endif
//создаём указатели на дороге
 	    	new Float:X,Float:Y,Float:Z,Float:A,Float:Ax,Float:Ay,Float:Az;
		    GetNodePos(node_id_array[i],X,Y,Z);//возвращает координаты узла
		    if(i < amount_of_nodes-3)
		    {
		        GetNodePos(node_id_array[i+3],Ax,Ay,Az);
		    	A = floatabs(270.0 - atan2( Ax-X,Ay-Y));
		    	//GPSObjects[playerid][i] =
				CreateDynamicObject(1318,X,Y,Z+0.2,0.0,90.0,A);
		    }
			else if(i < amount_of_nodes-2)
		    {
		        GetNodePos(node_id_array[i+2],Ax,Ay,Az);
		    	A = floatabs(270.0 - atan2( Ax-X,Ay-Y));
		    	//GPSObjects[playerid][i] =
				CreateDynamicObject(1318,X,Y,Z+0.2,0.0,90.0,A);
		    }
			else if(i < amount_of_nodes-1)
		    {
		        GetNodePos(node_id_array[i+1],Ax,Ay,Az);
		    	A = floatabs(270.0 - atan2( Ax-X,Ay-Y));
		    	//GPSObjects[playerid][i] =
				CreateDynamicObject(1318,X,Y,Z+0.2,0.0,90.0,A);
		    }
		    else
		    {//если
		        //GPSObjects[playerid][i] =
				CreateDynamicObject(1318,X,Y,Z+0.2,0.0,0.0,0.0);//создём стрелку вертикально вниз
		    }
		    //------------------------------------------------------------------
		    new connections = GetConnectedNodes(i);//возвращает кол-во вхождений в данный узел, т.е. линии соединений между узлами
			/*if(connections == 0)
			{
			    //printf("Found node without connections: %d",i);
			    //new id = CreateDynamicMapIcon(NodePosX[i],NodePosY[i],NodePosZ[i],53,0,_,_,_,7000);//53 - иконка финиша
			    //Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, id, E_STREAMER_STYLE, MAPICON_GLOBAL);
			}
			else*/
			if(//connections >= 3 &&
					IsNodeIntersection(node_id_array[i]) == 1)
			{//там где больше 3 входов в один узел, т.е. это перекрёсток ставим иконку на радаре
//CreateDynamicMapIcon(Float:x, Float:y, Float:z, type, color, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_MAP_ICON_SD, style = MAPICON_LOCAL, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0);
			    //CreateDynamicMapIcon(NodePosX[i],NodePosY[i],NodePosZ[i],56,COLOR_LIGHTBLUE,0,0,routeid,MAP_ICON_DRAW_DISTANCE);
			    //CreateDynamicMapIcon(NodePosX[i],NodePosY[i],NodePosZ[i],56,0,0,_,_,MAP_ICON_DRAW_DISTANCE);
			    //DestroyDynamic3DTextLabel()
			    format(str,sizeof(str),"{0080FF}NODE ID: {FFFF00}%d[%d]\n{0080FF}{%.5f,%.5f,%.5f}", node_id_array[i], i, NodePosX[i],NodePosY[i],NodePosZ[i]);
		    	//GPSLabels[playerid][i] =
				CreateDynamic3DTextLabel(str,COLOR_WHITE,X,Y,Z+1.2,NODE_DRAW_DISTANCE,_,_,0,0,_,_,NODE_DRAW_DISTANCE+20.0);
			}
			else
			{
			    format(str,sizeof(str),"NODE ID: {FFFF00}%d[%d]\n{FFFFFF}{%.5f,%.5f,%.5f}", node_id_array[i], i, NodePosX[i],NodePosY[i],NodePosZ[i]);
		    	//GPSLabels[playerid][i] =
				CreateDynamic3DTextLabel(str,COLOR_WHITE,X,Y,Z+1.2,NODE_DRAW_DISTANCE,_,_,0,0,_,_,NODE_DRAW_DISTANCE+20.0);
			}
//подписываем узлы
		    //new str[168];

		    //printf("Point(%d)=NodeID(%d)",i,node_id_array[i]);*/
#endif
		    //------------------------------------------------------------------
		    new metod;
            if(i == amount_of_nodes-1) break;
//для более плавного соединения гангзон
 		    new Float:X1,Float:Y1, Float:X2,Float:Y2; //floatround(NodePosX[i], floatround_tozero)
 		    //new Float:nPosX1=NodePosX[i], Float:nPosY1=NodePosY[i], Float:nPosX2=NodePosX[i+1], Float:nPosY2=NodePosY[i+1];
 		    new nPosX1=floatround(NodePosX[i],floatround_round); new nPosY1=floatround(NodePosY[i],floatround_round);
			new nPosX2=floatround(NodePosX[i+1],floatround_round); new nPosY2=floatround(NodePosY[i+1],floatround_round);

            if(nPosX1 == nPosX2 && nPosY1 < nPosY2) { X1 = nPosX1-15.0; Y1 = nPosY1; X2 = nPosX2; Y2 = nPosY2; metod = 1; }
           	else if(nPosX1 < nPosX2 && nPosY1 == nPosY2) { X1 = nPosX1; Y1 = nPosY1; X2 = nPosX2; Y2 = nPosY2+15.0; metod = 2; }
           	else if(nPosX1 == nPosX2 && nPosY1 > nPosY2) { X1 = nPosX2; Y1 = nPosY2; X2 = nPosX1+15.0; Y2 = nPosY1; metod = 3; }
           	else if(nPosX1 > nPosX2 && nPosY1 == nPosY2) { X1 = nPosX2; Y1 = nPosY2-15.0; X2 = nPosX1; Y2 = nPosY1; metod = 4; }

            else if((nPosY2-nPosY1)>(nPosX2-nPosX1) && nPosX1 < nPosX2 && nPosY1 < nPosY2 && (nPosX2-nPosX1)<15.0) { X1 = nPosX1-15.0; Y1 = nPosY1; X2 = nPosX1; Y2 = nPosY2; metod = 11; }
           	else if((nPosX2-nPosX1)>(nPosY1-nPosY2) && nPosX1 < nPosX2 && nPosY1 > nPosY2 && (nPosY1-nPosY2)<15.0) { X1 = nPosX1; Y1 = nPosY1; X2 = nPosX2; Y2 = nPosY1+15.0; metod = 12; }
           	else if((nPosY1-nPosY2)>(nPosX1-nPosX2) && nPosX1 > nPosX2 && nPosY1 > nPosY2 && (nPosX1-nPosX2)<15.0) { X1 = nPosX1; Y1 = nPosY2; X2 = nPosX1+15.0; Y2 = nPosY1; metod = 13; }
           	else if((nPosX1-nPosX2)>(nPosY2-nPosY1) && nPosX1 > nPosX2 && nPosY1 < nPosY2 && (nPosY2-nPosY1)<15.0) { X1 = nPosX2; Y1 = nPosY1-15.0; X2 = nPosX1; Y2 = nPosY1; metod = 14; }

           	else if((nPosY2-nPosY1)>(nPosX1-nPosX2) && nPosX1 > nPosX2 && nPosY1 < nPosY2 && (nPosX1-nPosX2)<15.0) { X1 = nPosX1-15.0; Y1 = nPosY1; X2 = nPosX1; Y2 = nPosY2; metod = 21; }
           	else if((nPosX2-nPosX1)>(nPosY2-nPosY1) && nPosX1 < nPosX2 && nPosY1 < nPosY2 && (nPosY2-nPosY1)<15.0) { X1 = nPosX1; Y1 = nPosY1; X2 = nPosX2; Y2 = nPosY1+15.0; metod = 22; }
           	else if((nPosY1-nPosY2)>(nPosX2-nPosX1) && nPosX1 < nPosX2 && nPosY1 > nPosY2 && (nPosX2-nPosX1)<15.0) { X1 = nPosX1; Y1 = nPosY2; X2 = nPosX1+15.0; Y2 = nPosY1; metod = 23; }
           	else if((nPosX1-nPosX2)>(nPosY1-nPosY2) && nPosX1 > nPosX2 && nPosY1 > nPosY2 && (nPosY1-nPosY2)<15.0) { X1 = nPosX2; Y1 = nPosY1-15.0; X2 = nPosX1; Y2 = nPosY1; metod = 24; }

    		else {  X1 = nPosX1; Y1 = nPosY1; X2 = nPosX2; Y2 = nPosY2; metod = 5; }
    		
    		#pragma unused metod
			//format(str, sizeof(str), "NodeID:%d[%d] Metod:%d GangZoneCreate(%.5f,%.5f, %.5f,%.5f) S=%.1f m2", node_id_array[i], i, metod, X1,Y1, X2,Y2, (X2-X1)*(Y2-Y1));
			//SendClientMessage(routeid, -1, str);
			
			if(i >= MAX_DOTS-1) break;
			new zoneid = GangZoneCreate(X1,Y1, X2,Y2);
			Storage[routeid][Zones][i] = zoneid;//по индексу игрока записали ID ганг-зоны
			//new nodeid = node_id_array[i];
			//PlayerZones[nodeid] = i;//по индексу узла порядковый номер маршрута
			//PlayerZones[routeid][i] = nodeid;//по индексу игрока записали ID узла
			GangZoneShowForPlayer(routeid, zoneid, COLOR_LIGHTBLUE);
            //GangZoneFlashForPlayer(routeid, zoneid, 0xAEC8D7FF);
		}//конец цикла

        Storage[routeid][ZonesSize] = amount_of_nodes;//кол-во узлов
        Storage[routeid][Destination] = node_id_array[amount_of_nodes-1];//ID узла конечной точки
        Storage[routeid][PolygonID] = CreateDynamicPolygon(Polygon,.maxpoints = Polygon_Size,.playerid = routeid);//записали указатель на динамический массив полигонов маршрута

        Storage[routeid][IsInGPS_Polygon] = IsPlayerInDynamicArea(routeid,Storage[routeid][PolygonID]) == 1;
        gps_AddPlayer(routeid);

//создаём массив перекрёстков гонки
        new progress = 0,
			checktype = 0,
			Float: SIZE = 12.0;
        GetNodePos(node_id_array[progress],RaceCheckpoints[progress][0],RaceCheckpoints[progress][1],RaceCheckpoints[progress][2]);
        GetNodePos(node_id_array[progress+1],RaceCheckpoints[progress+1][0],RaceCheckpoints[progress+1][1],RaceCheckpoints[progress+1][2]);
        
        SetPlayerRaceCheckpoint(playerid, checktype,
			RaceCheckpoints[progress][0],RaceCheckpoints[progress][1],RaceCheckpoints[progress][2],
			RaceCheckpoints[progress+1][0],RaceCheckpoints[progress+1][1],RaceCheckpoints[progress+1][2],
			SIZE);
		PlaySoundForPlayer(playerid, SOUND_CHECKPOINT_AMBER);
    }
    else
	{
        DestroyDynamicArea(Storage[routeid][PolygonID]);
        for(new i = 0; i < Storage[routeid][ZonesSize]; ++i)
        {
            //GangZoneHideForAll(Storage[routeid][Zones][i]);
			GangZoneHideForPlayer(routeid, Storage[routeid][Zones][i]);
            GangZoneDestroy(Storage[routeid][Zones][i]);
        }
        Storage[routeid][PolygonID] = -1;
        Storage[routeid][ZonesSize] = 0;
		Storage[routeid][Calculating] = 0;
        Storage[routeid][Destination] = -1;
        Storage[routeid][IsInGPS_Polygon] = false;
	}
    return 1;
}

enum DIRECTION
{
	STRAIGHT,
	LEFT_LOW,
	LEFT_HIGH,
	RIGHT_LOW,
	RIGHT_HIGH,
	UTURN_LEFT,
	UTURN_RIGHT
}

public OnPlayerClosestNodeIDChange(playerid,old_NodeID,new_NodeID)
{//вызывается когда игрок достигает узла, где old_NodeID - ID узлов из файла GPS который игрок уже покинул, new_NodeID - текущий новый узел
    if(new_NodeID == -1) return 1;
    if(Storage[playerid][PolygonID] == (-1))  return 1;
    
	if(Storage[playerid][Destination] != -1)
	{
		//new str[256+1];
		//format(str, sizeof(str), "OnPlayerClosestNodeIDChange(%d, old_NodeID:%d, new_NodeID:%d)", playerid, old_NodeID, new_NodeID);
		//SendClientMessage(playerid, -1, str);
		
		//if(new_NodeID == Storage[playerid][Destination])
		if(old_NodeID == Storage[playerid][Destination] || new_NodeID == Storage[playerid][Destination])
		{//если ИД узла в который вошёл игрок совпало с конечной точкой и ИД предыдущий точки также совпало
			DisableGPS(playerid);
			Storage[playerid][Calculating] = 0;
			SendClientMessage(playerid,COLOR_LIGHTBLUE,"Вы прибыли к месту назначения");
		}
		else
		{
			if(!Storage[playerid][IsInGPS_Polygon])
			{//если игрок не вошёл в IsPlayerInDynamicArea, т.е. отклонился от курса
				if(!Storage[playerid][Calculating])
				{//если вычисления ещё не сделаны
					if(CalculatePath(new_NodeID, Storage[playerid][Destination], playerid, .CreatePolygon = true, .GrabNodePositions = true))
					{//создаём новый маршрут от текущего узла до конечной точки
						DisableGPS(playerid);
						Storage[playerid][Calculating] = 1;//вычисления сделаны
					}
				}
			}
			else
			{
			    new idx_oldNodeID;
				//for(new i = 0; i <= i; i++)
				for(new i = 0,j = GetRouteArraySize(Storage[playerid][RouteID]); i < j; ++i)
        		{//перебираем все ячейки 
        		    //if(PlayerZones[playerid][i] == old_NodeID)  {
        		    if(GetRouteAtPos(Storage[playerid][RouteID],i) == old_NodeID) {//находим текущий порядковый номер точки которую мы уже проехали, или индекс в массиве Storage
						idx_oldNodeID = i;
//format(str, sizeof(str), "old_NodeID[%d]:%d", idx, old_NodeID);
//SendClientMessage(playerid, -1, str);
						break;
					}
	            }
			    //GangZoneHideForPlayer(playerid, zoneid);
		     	//GangZoneFlashForPlayer(playerid, zoneid, 0xAEC8D7FF);//сизый  //0x84F231FF);салатовый
		     	//GangZoneStopFlashForPlayer(playerid, zoneid);
				for(new z = 0, zoneid; z <= idx_oldNodeID; z++)
        		{//перебираем все ячейки созданного массива маршрута
			    //удаляем зоны не только те которые покидаем, но и все предыдущие, с пометкой что удалены
			    	//но может удалить зоны чужие
                    zoneid = Storage[playerid][Zones][z];
		            //GangZoneShowForPlayer(playerid, zoneid, 0xAEC8D7FF);//скрываем  все зоны до индекса  текущей точки маршрута
		            GangZoneHideForPlayer(playerid, zoneid);
		            GangZoneDestroy(zoneid);
	            }
	            
				if(IsNodeIntersection( old_NodeID ) == 1) //если текущий ваш узел - перекрёсток
				{
//в момент нахождения на перекрёстке находим следующий перекрёсток по вашему маршруту и уведомляем что на нём делать
			    	new NodeIDs[3], DIRECTION:result;

				    for(new i = idx_oldNodeID+1,j = GetRouteArraySize(Storage[playerid][RouteID])-4; i < j; i++)//GetRouteArraySize получает размер массива с указателем по RouteID
				    {//перебераем весь массив начиная со следующей позиции, чтобы найти перкрёсток и сразу выйти из массива
			        	if(IsNodeIntersection(GetRouteAtPos(Storage[playerid][RouteID],i)) == 1)
		    			{//находим следующий перекрёсток от текущей позиции
							//определяем соседние узлы по маршруту
				            NodeIDs[0] = GetRouteAtPos(Storage[playerid][RouteID],i-1);
							NodeIDs[1] = GetRouteAtPos(Storage[playerid][RouteID],i);//записали ИД перекрёстка
							NodeIDs[2] = GetRouteAtPos(Storage[playerid][RouteID],i+1);

#if defined GPS_DEBUG//#endif
                            new Float:Angle;
							Angle = GetAngleBetweenNodes(NodeIDs[0],NodeIDs[1],NodeIDs[2]);
//format(str, sizeof(str), "%d. Обнаружен Перекрёсток NodeIDs[%d]:%d, Angle: %.1f", new_NodeID,  i,NodeIDs[1], Angle);
//SendClientMessage(playerid, -1, str);
#endif
		            		result = IsLeftStraighRight(NodeIDs[0],NodeIDs[1],NodeIDs[2]);
							SetPlayerGPSRouting(playerid, result, GetDistanceBetweenNodes(new_NodeID, NodeIDs[1]) );//уведомляем что делать на следующем прекрёстке
							
							
					        new progress = i,
								checktype = 0,
								Float: SIZE = 12.0;
					        GetNodePos(NodeIDs[1],RaceCheckpoints[progress][0],RaceCheckpoints[progress][1],RaceCheckpoints[progress][2]);
					        GetNodePos(NodeIDs[2],RaceCheckpoints[progress+1][0],RaceCheckpoints[progress+1][1],RaceCheckpoints[progress+1][2]);

					        SetPlayerRaceCheckpoint(playerid, checktype,
								RaceCheckpoints[progress][0],RaceCheckpoints[progress][1],RaceCheckpoints[progress][2],
								RaceCheckpoints[progress+1][0],RaceCheckpoints[progress+1][1],RaceCheckpoints[progress+1][2],
								SIZE);
							PlaySoundForPlayer(playerid, SOUND_CHECKPOINT_AMBER);
//необходимо уведомлять сразу после прохождения перекрёстка
				        	break;
				        }
				        //not found on list
				    }
			    }
	            /*new str[256+1];
				format(str, sizeof(str), "idx: %d, old_NodeID: %d, zoneid: %d", idx, old_NodeID, zoneid);
				SendClientMessage(playerid, -1, str);*/
			}
		}
	}
	else
	{//если вы прибыли к месту назначения
	    //new i = Storage[playerid][NodeID][old_NodeID]);
		//format(str, sizeof(str), "zoneid: %d[%d]", Storage[playerid][Zones][i], i);
		SendClientMessage(playerid, -1, "DestroyDynamicArea");
	
        DestroyDynamicArea(Storage[playerid][PolygonID]);
        //DestroyAllDynamicObjects();
		//DestroyAllDynamicMapIcons();
		//DestroyAllDynamic3DTextLabels();
        for(new i = 0; i < Storage[playerid][ZonesSize]; ++i)
        {
            //GangZoneHideForAll(Storage[playerid][Zones][i]);
            GangZoneHideForPlayer(playerid, Storage[playerid][Zones][i]);
            GangZoneDestroy(Storage[playerid][Zones][i]);
        }
        Storage[playerid][PolygonID] = (-1);
        Storage[playerid][ZonesSize] = 0;
		//Storage[playerid][Calculating] = 0;//не раскоментировать
        Storage[playerid][Destination] = (-1);
        Storage[playerid][IsInGPS_Polygon] = false;
		gps_RemovePlayer(playerid);
	}
	
    return 1;
}
/*
stock gps_OnPlayerEnterCheckpoint(playerid)
{ 
	if(gInRacing[playerid] && GetPVarInt(playerid, "PlayerProgressCount") >= (gMaxCheckpoints-1)) //Если игрок финишировал...
	{   //если кол-во пройденных меток совпало с максимальным кол-вом в массиве
	    DisablePlayerRaceCheckpoint(playerid);
	    PlaySoundForPlayer(playerid, SOUND_DRIVING_AWARD_TRACK_START);//Включить Музыкальный трек - конец гонки
	}
	else if(gInRacing[playerid] && GetPVarInt(playerid, "PlayerProgressCount") < (gMaxCheckpoints-1))
	{    //Если гонщик ещё не финишировал, установить следующий checkpoint
		GivePVarInt(playerid, "PlayerProgressCount", +1);//счётчик пройденных CP
		SetCheckpoint(playerid, GetPVarInt(playerid, "PlayerProgressCount"), gMaxCheckpoints);//для гонок STEP4
		PlaySoundForPlayer(playerid, SOUND_CHECKPOINT_AMBER);
	}
}
*/


stock SetPlayerGPSRouting(playerid, DIRECTION:direction, Float: distance)//получить угол направления на точку
{   //вызывается из OnPlayerCallTime(playerid)//запускается каждую секунду из OneSecondTimers
	if(GPS_OnOff[playerid] == 0) return 1;
	if(PlayerInfo[playerid][pInt] != 0) return 1;
	if(PlayerInfo[playerid][pVirtual] != 0) return 1;
	new strtmp[20+4];
	switch(direction)
	{
		case STRAIGHT:
		{
			format(strtmp, sizeof(strtmp), "~u~~n~   ~y~%d", floatround(distance));
			format(strings, sizeof(strings), "На перекрёстке через %d м продолжайте движение прямо", floatround(distance));
			SendClientMessage(playerid,-1,strings);
		}
		case LEFT_LOW:
		{
		    format(strtmp, sizeof(strtmp), "~<~ ~y~%d", floatround(distance));
			format(strings, sizeof(strings), "На перекрёстке через %d м возмите левее", floatround(distance));
			SendClientMessage(playerid,-1,strings);
		}
		case LEFT_HIGH:
		{
		    format(strtmp, sizeof(strtmp), "~<~~<~ ~y~%d", floatround(distance));
		    format(strings, sizeof(strings), "На перекрёстке через %d м крутой поворот налево", floatround(distance));
			SendClientMessage(playerid,-1,strings);
		}
		case RIGHT_LOW:
		{
		    format(strtmp, sizeof(strtmp), "~y~%d ~>~", floatround(distance));
		   	format(strings, sizeof(strings), "На перекрёстке через %d м возмите правее", floatround(distance));
			SendClientMessage(playerid,-1,strings);
		}
		case RIGHT_HIGH:
		{
		    format(strtmp, sizeof(strtmp), "~y~%d ~>~~>~", floatround(distance));
		    format(strings, sizeof(strings), "На перекрёстке через %d м крутой поворот направо", floatround(distance));
			SendClientMessage(playerid,-1,strings);
		}
		case UTURN_LEFT:
		{
		    format(strtmp, sizeof(strtmp), "~<~ ~y~%d~n~    ~d~", floatround(distance));
		    format(strings, sizeof(strings), "На перекрёстке через %d м развернитесь налево", floatround(distance));
			SendClientMessage(playerid,-1,strings);
		}
		case UTURN_RIGHT:
		{
			format(strtmp, sizeof(strtmp), "    ~y~%d ~>~~n~~d~", floatround(distance));
			format(strings, sizeof(strings), "На перекрёстке через %d м развернитесь направо", floatround(distance));
			SendClientMessage(playerid,-1,strings);
		}
   	}
	GameTextForPlayerEx(playerid, strtmp, 3500, 4);//3500
	return 1;
}

forward DIRECTION:IsLeftStraighRight(NodeFrom,NodeMiddle,NodeTo, &Float:refAngle=0.0);
stock DIRECTION:IsLeftStraighRight(NodeFrom,NodeMiddle,NodeTo, &Float:refAngle=0.0)
{
    new Float:DeltaX;
    new Float:DeltaY;
    new Float:AdderX;
    new Float:AdderY;
    new Float:Length;
    new Float:CR[9][2];

    GetNodePos(NodeFrom,CR[1][0],CR[1][1],DeltaX);
    GetNodePos(NodeMiddle,CR[0][0],CR[0][1],DeltaX);
    GetNodePos(NodeTo,CR[2][0],CR[2][1],DeltaX);

    DeltaX = CR[1][0] - CR[0][0];
    DeltaY = CR[1][1] - CR[0][1];
    Length = floatsqroot(((DeltaX * DeltaX) + (DeltaY * DeltaY))) + 0.0000000001;
    AdderX = (DeltaX / Length);
    AdderY = (DeltaY / Length);
    CR[3][0] = (CR[0][0] + (AdderX * 30.0));
    CR[3][1] = (CR[0][1] + (AdderY * 30.0));

    DeltaX = CR[2][0] - CR[0][0];
    DeltaY = CR[2][1] - CR[0][1];
    Length = floatsqroot(((DeltaX * DeltaX) + (DeltaY * DeltaY))) + 0.0000000001;
    AdderX = (DeltaX / Length);
    AdderY = (DeltaY / Length);
    CR[4][0] = (CR[0][0] + (AdderX * 30.0));
    CR[4][1] = (CR[0][1] + (AdderY * 30.0));

    DeltaX = CR[3][0] - CR[4][0];
    DeltaY = CR[3][1] - CR[4][1];
    Length = floatsqroot(((DeltaX * DeltaX) + (DeltaY * DeltaY))) + 0.0000000001;
    AdderX = (DeltaX / Length);
    AdderY = (DeltaY / Length);
    CR[8][0] = (CR[4][0] + (AdderX * Length / 2.0));
    CR[8][1] = (CR[4][1] + (AdderY * Length / 2.0));

    DeltaX = CR[8][0] - CR[0][0];
    DeltaY = CR[8][1] - CR[0][1];
    Length = floatsqroot(((DeltaX * DeltaX) + (DeltaY * DeltaY))) + 0.0000000001;
    AdderX = (DeltaX / Length);
    AdderY = (DeltaY / Length);
    CR[7][0] = (CR[0][0] - (AdderX * 30.0));
    CR[7][1] = (CR[0][1] - (AdderY * 30.0));

	new Float:result = (CR[2][0] - CR[1][0]) * (CR[7][1] - CR[1][1]) - (CR[2][1] - CR[1][1]) * (CR[7][0] - CR[1][0]);
	new Float:Angle = floatabs(GetAngleBetweenNodes(NodeFrom,NodeMiddle,NodeTo));
	refAngle = Angle;
    if(result < 0.0)
    {
		if(Angle <= 75.0)
		{
		    return UTURN_LEFT;

		}
		else if(Angle <= 135.0)
		{
			return LEFT_HIGH;

		}
		else if(Angle <= 177.5)
		{
		    return LEFT_LOW;
		}
		else
		{
		    return STRAIGHT;
		}
	}
	else if(result == 0.0)
	{
	    return STRAIGHT;
	}
	else if(result > 0.0)
	{
		if(Angle <= 75.0)
		{
		    return UTURN_RIGHT;
		}
		else if(Angle <= 135.0)
		{
			return RIGHT_HIGH;
		}
		else if(Angle <= 177.5)
		{
		    return RIGHT_LOW;
		}
		else
		{
		    return STRAIGHT;
		}
	}
	return STRAIGHT;
}

public OnPlayerEnterDynamicArea(playerid, areaid)
{//streamer //areaid - это ID маршрута, по сути у каждого игрока свой маршрут, но один, поэтому areaid = 1 для одного игрока на сервере
    if(Storage[playerid][PolygonID] == areaid)
    {//возвращает areaid == 1 если вы вернулись на свою линию маршрута
		//new str[168];
		//format(str, sizeof(str), "OnPlayerEnterDynamicArea(%d, %d)", playerid, areaid);
		//SendClientMessage(playerid, -1, str);
    
        Storage[playerid][IsInGPS_Polygon] = true;//можно сюда записывать areaid
		//SendClientMessage(playerid,COLOR_LIGHTBLUE,"Соединение со спутниками установлено");
    }
    return 1;
}

public OnPlayerLeaveDynamicArea(playerid, areaid)
{//streamer
    if(Storage[playerid][PolygonID] == areaid && Storage[playerid][IsInGPS_Polygon])
    {//если игрок был на маршруте
   		//new str[168];
		//format(str, sizeof(str), "OnPlayerLeaveDynamicArea(%d, %d)", playerid, areaid);
		//SendClientMessage(playerid, -1, str);
    
        if(Storage[playerid][Calculating] == 0)
        {//а расчёт маршрута ещё не сделан
            new PlayerClosest = NearestPlayerNode(playerid);//находим ближайший узел к игроку
            if(PlayerClosest != -1)
            {//если нашли
                if(CalculatePath(PlayerClosest, Storage[playerid][Destination], playerid, .CreatePolygon = true, .GrabNodePositions = true))
                {//прокладываем новый путь
                    DisableGPS(playerid);
                    Storage[playerid][Calculating] = 1;
                }
            }
        }
        Storage[playerid][IsInGPS_Polygon] = false;
		//SendClientMessage(playerid,COLOR_RED,"Вы ушли с маршрута");//сильно флудит
    }
    return 1;
}

stock DisableGPS(playerid)
{
    if(Storage[playerid][Destination] != -1)
    {
        DestroyDynamicArea(Storage[playerid][PolygonID]);
  //не трогать, т.к. будет удалено для всех игроков
        //DestroyAllDynamicObjects();
		//DestroyAllDynamicMapIcons();
		//DestroyAllDynamic3DTextLabels();
		
        for(new i = 0; i < Storage[playerid][ZonesSize]; ++i)
        {
            //GangZoneHideForAll(Storage[playerid][Zones][i]);
            //GangZoneStopFlashForPlayer(playerid, Storage[playerid][Zones][i]);
            GangZoneHideForPlayer(playerid, Storage[playerid][Zones][i]);
            GangZoneDestroy(Storage[playerid][Zones][i]);
        }
        Storage[playerid][PolygonID] = (-1);
        Storage[playerid][ZonesSize] = 0;
		//Storage[playerid][Calculating] = 0;//не раскоментировать
        Storage[playerid][Destination] = (-1);
        Storage[playerid][IsInGPS_Polygon] = false;
		gps_RemovePlayer(playerid);
    }
    return 1;
}



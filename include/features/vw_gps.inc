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

//��������������� ������� ��� ����������� � ���


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

//������ ��� ������� ������ � ��������, ������� ������� �� �������
enum RouteInformation
{
    RouteID,//��������� �������� 1 ���� ������ ������ �������, ��� 0 ���� ���. ��� ID ������������� �������, �� ������ � NodeID
	PolygonID,//��������� �������� 1 ���� ������ ������ �������, ��� 0 ���� ���. ��� ID ������������� �������, �� ������ � NodeID
    Zones[1024], //ID ��������� ����-��� //There is a limit of 1024 gangzones.
    ZonesSize,//���-�� ��������� ���� ��� ��� ��������� ��������, ����� ��� ������
    Calculating,//������, ��� ���� ����� ������ ��������
    Destination,//ID ���� �������� �����
    bool:IsInGPS_Polygon//������: ����� �� �������� ��� ���� � ��������
};
new Storage[MAX_PLAYERS][RouteInformation];//�� ������� ������ ������ ID ����

//� ������� ������ ���� �������� �����
new DestinationNodeID[MAX_PLAYERS] = {-1, ...};//�� ������� ������ ������ NodeID ���� �������� ����� = NearestNodeFromPoint(1345.2018,746.1505,10.2350);


//����� ������ ����������� ������
//new PlayerZones[MAX_PLAYERS][MAX_DOTS];// = {-1, ...}; �� ������� ������ ������ ��� ���� � ��������
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

	//�������� ���� �� ������ ������� ��� MAX_PLAYERS, �.�. ����� ����� ����� � ��� ��� �� ��� ����� ������ 3������
	//for(new playerid = 0; playerid < GetMaxPlayers(); playerid++)
	for(new playerid = 0; playerid < MAX_PLAYERS; ++playerid)
	{
		//if(!IsPlayerConnected(playerid)) continue;
		DisableGPS(playerid);
		
		if(Storage[playerid][RouteID] >= 0)
		{//������� ������ ��� ����� ������
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
        SendClientMessage(playerid,0xFFFF00FF,"����������, ���������, ������ ��� ������� ��� ��������� ����� ����������!");
        return 1;
    }

//������� ��������� � �������� ����� ����
	new biz, sbiz;
	if(Cargo[trailerid][tWhere] >= 100)//����
	{
		sbiz = Cargo[trailerid][tWhere]-100;//����
		DestinationNodeID[playerid] = NearestNodeFromPoint(SBizInfo[sbiz][sbEntranceX],	SBizInfo[sbiz][sbEntranceY], SBizInfo[sbiz][sbEntranceZ]);//��
	}
	else
	{
		biz = Cargo[trailerid][tWhere];//����
		DestinationNodeID[playerid] = NearestNodeFromPoint(BizInfo[biz][bEntranceX], BizInfo[biz][bEntranceY], BizInfo[biz][bEntranceZ]);//��
	}
    if(DestinationNodeID[playerid] == -1)
    {
        //SendClientMessage(playerid,0xFF0000FF,"����� ���������� ��� ���� ��������.");
		SendClientMessage(playerid,0xFF0000FF,"�� �� ������� �� ����� ����� ����������. ���������� ��� ���.");
        return 1;
    }
    //if(Storage[playerid][Destination] != -1)
    //{
	DisableGPS(playerid);
    //}
    //new NearestPlayerNodeID = NearestPlayerNode(playerid);//������� ��������� � ������ ����, � �� � �������� �����

	new NearestPointNodeID;//������� ��������� � ��������� ����� ����
	if(Cargo[trailerid][tWhence] >= 100)//������
	{
		sbiz = Cargo[trailerid][tWhence]-100;//������
		NearestPointNodeID = NearestNodeFromPoint(SBizInfo[sbiz][sbEntranceX],	SBizInfo[sbiz][sbEntranceY], SBizInfo[sbiz][sbEntranceZ]);//��
	}
	else
	{
		biz = Cargo[trailerid][tWhence];//������
		NearestPointNodeID = NearestNodeFromPoint(BizInfo[biz][bEntranceX], BizInfo[biz][bEntranceY], BizInfo[biz][bEntranceZ]);//��
	}
    if(NearestPointNodeID == -1)
    {
        SendClientMessage(playerid,0xFF0000FF,"��������� ����� �� ��������. ���������� ������� ������.");
        return 1;
    }
    if(CalculatePath(NearestPointNodeID, DestinationNodeID[playerid], playerid, .GrabNodePositions = true))
    {//������ ������� �� ���������� ���� �� ������ � ID ���� �������� �����
        Storage[playerid][Calculating] = 1;
        SendClientMessage(playerid,0xFFFF00FF,"���������� �� ���������� �����������!");

		//new trailerid;//, trailermodel;
		//if(IsTrailerAttachedToVehicle(nCarID[playerid])) { trailerid = nTrailerID[playerid]; }
		//else { trailerid = nCarID[playerid]; }

        //new strtmp[MAX_STRING];
       	//format(strtmp, sizeof(strtmp), "����� �������� �� ������� ���������� %.1f �", Cargo[trailerid][tDistance] );
        //SendClientMessage(playerid, -1, strtmp);
    }
    else
    {
        SendClientMessage(playerid,0xFF0000FF,"��������� ������... ���������� ��� ���!");
    }
    return 1;
}



stock gps_OnPlayerConnect(playerid)
//public OnPlayerConnect(playerid)
{
	GPS_OnOff[playerid] = 1;//��������� ��� ����������

	//gps_AddPlayer(playerid);//����� ��������� ������ ��� ��������� GPS
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
        SendClientMessage(playerid,COLOR_YELLOW,"����������, ���������, ������ ��� ������� ��� ��������� ����� ����������!");
        return 1;
    }
    if(DestinationNodeID[playerid] == -1)
    {
        //SendClientMessage(playerid,COLOR_RED,"����� ���������� ��� ���� ��������.");
		SendClientMessage(playerid,COLOR_RED,"�� �� ������� �� ����� ����� ����������. ���������� ��� ���.");
        return 1;
    }
    //if(Storage[playerid][Destination] != -1)
    //{
	DisableGPS(playerid);
    //}
    new NearestPlayerNodeID = NearestPlayerNode(playerid);//������� ��������� � ������ ����, � �� � �������� �����
    if(NearestPlayerNodeID == -1)
    {
        SendClientMessage(playerid,COLOR_RED,"�� ��� ���� ���������. ���������� ������� �� ������.");
        return 1;
    }
    if(CalculatePath(NearestPlayerNodeID, DestinationNodeID[playerid], playerid, .GrabNodePositions = true))
    {//������ ������� �� ���������� ���� �� ������ � ID ���� �������� �����
        Storage[playerid][Calculating] = 1;
        SendClientMessage(playerid,COLOR_YELLOW,"���������� �� ���������� �����������!");
    }
    else
    {
        SendClientMessage(playerid,COLOR_RED,"��������� ������... ���������� ��� ���!");
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
	        SendClientMessage(playerid,COLOR_YELLOW,"����������, ���������, ������ ��� ������� ��� ��������� ����� ����������!");
	        return 1;
	    }
	    if(DestinationNodeID[playerid] == -1)
	    {
	        //SendClientMessage(playerid,COLOR_RED,"����� ���������� ��� ���� ��������.");
			SendClientMessage(playerid,COLOR_RED,"�� �� ������� �� ����� ����� ����������. ���������� ��� ���.");
	        return 1;
	    }
	    //if(Storage[playerid][Destination] != -1)
	    //{
		DisableGPS(playerid);
	    //}
	    new NearestPlayerNodeID = NearestPlayerNode(playerid);//������� ��������� � ������ ����, � �� � �������� �����
	    if(NearestPlayerNodeID == -1)
	    {
	        SendClientMessage(playerid,COLOR_RED,"�� ��� ���� ���������. ���������� ����� �� ������.");
	        return 1;
	    }
	    if(CalculatePath(NearestPlayerNodeID, DestinationNodeID[playerid], playerid, .GrabNodePositions = true))
	    {//������ ������� �� ���������� ���� �� ������ � ID ���� �������� �����
	        Storage[playerid][Calculating] = 1;
	        SendClientMessage(playerid,COLOR_YELLOW,"���������� �� ���������� �����������!");
	    }
	    else
	    {
	        SendClientMessage(playerid,COLOR_RED,"��������� ������... ���������� ��� ���!");
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
{//routeid = playerid //���������� 1 ��� ����� ������� CalculatePath
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
	format(strtmp, sizeof(strtmp), "����������� �������� %.1f �", Cargo[trailerid][tDistance] );
	SendClientMessage(playerid, -1, strtmp);

//��� ������� ������ routeid
	Storage[routeid][RouteID] = StoreRouteArray(amount_of_nodes, node_id_array);//�������� �� ������� ����� ����� ��������, ����� �� ����� ��������� ����� ���� �������� ������ �� �������
    Storage[routeid][Calculating] = 0;
    if(amount_of_nodes > 1)
    {//���� ���-�� ����� � �������� ������ 1

        for(new i = 0; i < amount_of_nodes; ++i)//amount_of_nodes
		//for(new i = 0; i < MAX_DOTS; ++i)//amount_of_nodes
        {//���������� ��� ���� �� ���������� ������� node_id_array
#if defined GPS_DEBUG//#endif
//������ ��������� �� ������
 	    	new Float:X,Float:Y,Float:Z,Float:A,Float:Ax,Float:Ay,Float:Az;
		    GetNodePos(node_id_array[i],X,Y,Z);//���������� ���������� ����
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
		    {//����
		        //GPSObjects[playerid][i] =
				CreateDynamicObject(1318,X,Y,Z+0.2,0.0,0.0,0.0);//����� ������� ����������� ����
		    }
		    //------------------------------------------------------------------
		    new connections = GetConnectedNodes(i);//���������� ���-�� ��������� � ������ ����, �.�. ����� ���������� ����� ������
			/*if(connections == 0)
			{
			    //printf("Found node without connections: %d",i);
			    //new id = CreateDynamicMapIcon(NodePosX[i],NodePosY[i],NodePosZ[i],53,0,_,_,_,7000);//53 - ������ ������
			    //Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, id, E_STREAMER_STYLE, MAPICON_GLOBAL);
			}
			else*/
			if(//connections >= 3 &&
					IsNodeIntersection(node_id_array[i]) == 1)
			{//��� ��� ������ 3 ������ � ���� ����, �.�. ��� ���������� ������ ������ �� ������
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
//����������� ����
		    //new str[168];

		    //printf("Point(%d)=NodeID(%d)",i,node_id_array[i]);*/
#endif
		    //------------------------------------------------------------------
		    new metod;
            if(i == amount_of_nodes-1) break;
//��� ����� �������� ���������� �������
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
			Storage[routeid][Zones][i] = zoneid;//�� ������� ������ �������� ID ����-����
			//new nodeid = node_id_array[i];
			//PlayerZones[nodeid] = i;//�� ������� ���� ���������� ����� ��������
			//PlayerZones[routeid][i] = nodeid;//�� ������� ������ �������� ID ����
			GangZoneShowForPlayer(routeid, zoneid, COLOR_LIGHTBLUE);
            //GangZoneFlashForPlayer(routeid, zoneid, 0xAEC8D7FF);
		}//����� �����

        Storage[routeid][ZonesSize] = amount_of_nodes;//���-�� �����
        Storage[routeid][Destination] = node_id_array[amount_of_nodes-1];//ID ���� �������� �����
        Storage[routeid][PolygonID] = CreateDynamicPolygon(Polygon,.maxpoints = Polygon_Size,.playerid = routeid);//�������� ��������� �� ������������ ������ ��������� ��������

        Storage[routeid][IsInGPS_Polygon] = IsPlayerInDynamicArea(routeid,Storage[routeid][PolygonID]) == 1;
        gps_AddPlayer(routeid);

//������ ������ ����������� �����
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
{//���������� ����� ����� ��������� ����, ��� old_NodeID - ID ����� �� ����� GPS ������� ����� ��� �������, new_NodeID - ������� ����� ����
    if(new_NodeID == -1) return 1;
    if(Storage[playerid][PolygonID] == (-1))  return 1;
    
	if(Storage[playerid][Destination] != -1)
	{
		//new str[256+1];
		//format(str, sizeof(str), "OnPlayerClosestNodeIDChange(%d, old_NodeID:%d, new_NodeID:%d)", playerid, old_NodeID, new_NodeID);
		//SendClientMessage(playerid, -1, str);
		
		//if(new_NodeID == Storage[playerid][Destination])
		if(old_NodeID == Storage[playerid][Destination] || new_NodeID == Storage[playerid][Destination])
		{//���� �� ���� � ������� ����� ����� ������� � �������� ������ � �� ���������� ����� ����� �������
			DisableGPS(playerid);
			Storage[playerid][Calculating] = 0;
			SendClientMessage(playerid,COLOR_LIGHTBLUE,"�� ������� � ����� ����������");
		}
		else
		{
			if(!Storage[playerid][IsInGPS_Polygon])
			{//���� ����� �� ����� � IsPlayerInDynamicArea, �.�. ���������� �� �����
				if(!Storage[playerid][Calculating])
				{//���� ���������� ��� �� �������
					if(CalculatePath(new_NodeID, Storage[playerid][Destination], playerid, .CreatePolygon = true, .GrabNodePositions = true))
					{//������ ����� ������� �� �������� ���� �� �������� �����
						DisableGPS(playerid);
						Storage[playerid][Calculating] = 1;//���������� �������
					}
				}
			}
			else
			{
			    new idx_oldNodeID;
				//for(new i = 0; i <= i; i++)
				for(new i = 0,j = GetRouteArraySize(Storage[playerid][RouteID]); i < j; ++i)
        		{//���������� ��� ������ 
        		    //if(PlayerZones[playerid][i] == old_NodeID)  {
        		    if(GetRouteAtPos(Storage[playerid][RouteID],i) == old_NodeID) {//������� ������� ���������� ����� ����� ������� �� ��� ��������, ��� ������ � ������� Storage
						idx_oldNodeID = i;
//format(str, sizeof(str), "old_NodeID[%d]:%d", idx, old_NodeID);
//SendClientMessage(playerid, -1, str);
						break;
					}
	            }
			    //GangZoneHideForPlayer(playerid, zoneid);
		     	//GangZoneFlashForPlayer(playerid, zoneid, 0xAEC8D7FF);//�����  //0x84F231FF);���������
		     	//GangZoneStopFlashForPlayer(playerid, zoneid);
				for(new z = 0, zoneid; z <= idx_oldNodeID; z++)
        		{//���������� ��� ������ ���������� ������� ��������
			    //������� ���� �� ������ �� ������� ��������, �� � ��� ����������, � �������� ��� �������
			    	//�� ����� ������� ���� �����
                    zoneid = Storage[playerid][Zones][z];
		            //GangZoneShowForPlayer(playerid, zoneid, 0xAEC8D7FF);//��������  ��� ���� �� �������  ������� ����� ��������
		            GangZoneHideForPlayer(playerid, zoneid);
		            GangZoneDestroy(zoneid);
	            }
	            
				if(IsNodeIntersection( old_NodeID ) == 1) //���� ������� ��� ���� - ����������
				{
//� ������ ���������� �� ���������� ������� ��������� ���������� �� ������ �������� � ���������� ��� �� ��� ������
			    	new NodeIDs[3], DIRECTION:result;

				    for(new i = idx_oldNodeID+1,j = GetRouteArraySize(Storage[playerid][RouteID])-4; i < j; i++)//GetRouteArraySize �������� ������ ������� � ���������� �� RouteID
				    {//���������� ���� ������ ������� �� ��������� �������, ����� ����� ��������� � ����� ����� �� �������
			        	if(IsNodeIntersection(GetRouteAtPos(Storage[playerid][RouteID],i)) == 1)
		    			{//������� ��������� ���������� �� ������� �������
							//���������� �������� ���� �� ��������
				            NodeIDs[0] = GetRouteAtPos(Storage[playerid][RouteID],i-1);
							NodeIDs[1] = GetRouteAtPos(Storage[playerid][RouteID],i);//�������� �� ����������
							NodeIDs[2] = GetRouteAtPos(Storage[playerid][RouteID],i+1);

#if defined GPS_DEBUG//#endif
                            new Float:Angle;
							Angle = GetAngleBetweenNodes(NodeIDs[0],NodeIDs[1],NodeIDs[2]);
//format(str, sizeof(str), "%d. ��������� ���������� NodeIDs[%d]:%d, Angle: %.1f", new_NodeID,  i,NodeIDs[1], Angle);
//SendClientMessage(playerid, -1, str);
#endif
		            		result = IsLeftStraighRight(NodeIDs[0],NodeIDs[1],NodeIDs[2]);
							SetPlayerGPSRouting(playerid, result, GetDistanceBetweenNodes(new_NodeID, NodeIDs[1]) );//���������� ��� ������ �� ��������� ���������
							
							
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
//���������� ���������� ����� ����� ����������� ����������
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
	{//���� �� ������� � ����� ����������
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
		//Storage[playerid][Calculating] = 0;//�� ����������������
        Storage[playerid][Destination] = (-1);
        Storage[playerid][IsInGPS_Polygon] = false;
		gps_RemovePlayer(playerid);
	}
	
    return 1;
}
/*
stock gps_OnPlayerEnterCheckpoint(playerid)
{ 
	if(gInRacing[playerid] && GetPVarInt(playerid, "PlayerProgressCount") >= (gMaxCheckpoints-1)) //���� ����� �����������...
	{   //���� ���-�� ���������� ����� ������� � ������������ ���-��� � �������
	    DisablePlayerRaceCheckpoint(playerid);
	    PlaySoundForPlayer(playerid, SOUND_DRIVING_AWARD_TRACK_START);//�������� ����������� ���� - ����� �����
	}
	else if(gInRacing[playerid] && GetPVarInt(playerid, "PlayerProgressCount") < (gMaxCheckpoints-1))
	{    //���� ������ ��� �� �����������, ���������� ��������� checkpoint
		GivePVarInt(playerid, "PlayerProgressCount", +1);//������� ���������� CP
		SetCheckpoint(playerid, GetPVarInt(playerid, "PlayerProgressCount"), gMaxCheckpoints);//��� ����� STEP4
		PlaySoundForPlayer(playerid, SOUND_CHECKPOINT_AMBER);
	}
}
*/


stock SetPlayerGPSRouting(playerid, DIRECTION:direction, Float: distance)//�������� ���� ����������� �� �����
{   //���������� �� OnPlayerCallTime(playerid)//����������� ������ ������� �� OneSecondTimers
	if(GPS_OnOff[playerid] == 0) return 1;
	if(PlayerInfo[playerid][pInt] != 0) return 1;
	if(PlayerInfo[playerid][pVirtual] != 0) return 1;
	new strtmp[20+4];
	switch(direction)
	{
		case STRAIGHT:
		{
			format(strtmp, sizeof(strtmp), "~u~~n~   ~y~%d", floatround(distance));
			format(strings, sizeof(strings), "�� ���������� ����� %d � ����������� �������� �����", floatround(distance));
			SendClientMessage(playerid,-1,strings);
		}
		case LEFT_LOW:
		{
		    format(strtmp, sizeof(strtmp), "~<~ ~y~%d", floatround(distance));
			format(strings, sizeof(strings), "�� ���������� ����� %d � ������� �����", floatround(distance));
			SendClientMessage(playerid,-1,strings);
		}
		case LEFT_HIGH:
		{
		    format(strtmp, sizeof(strtmp), "~<~~<~ ~y~%d", floatround(distance));
		    format(strings, sizeof(strings), "�� ���������� ����� %d � ������ ������� ������", floatround(distance));
			SendClientMessage(playerid,-1,strings);
		}
		case RIGHT_LOW:
		{
		    format(strtmp, sizeof(strtmp), "~y~%d ~>~", floatround(distance));
		   	format(strings, sizeof(strings), "�� ���������� ����� %d � ������� ������", floatround(distance));
			SendClientMessage(playerid,-1,strings);
		}
		case RIGHT_HIGH:
		{
		    format(strtmp, sizeof(strtmp), "~y~%d ~>~~>~", floatround(distance));
		    format(strings, sizeof(strings), "�� ���������� ����� %d � ������ ������� �������", floatround(distance));
			SendClientMessage(playerid,-1,strings);
		}
		case UTURN_LEFT:
		{
		    format(strtmp, sizeof(strtmp), "~<~ ~y~%d~n~    ~d~", floatround(distance));
		    format(strings, sizeof(strings), "�� ���������� ����� %d � ������������ ������", floatround(distance));
			SendClientMessage(playerid,-1,strings);
		}
		case UTURN_RIGHT:
		{
			format(strtmp, sizeof(strtmp), "    ~y~%d ~>~~n~~d~", floatround(distance));
			format(strings, sizeof(strings), "�� ���������� ����� %d � ������������ �������", floatround(distance));
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
{//streamer //areaid - ��� ID ��������, �� ���� � ������� ������ ���� �������, �� ����, ������� areaid = 1 ��� ������ ������ �� �������
    if(Storage[playerid][PolygonID] == areaid)
    {//���������� areaid == 1 ���� �� ��������� �� ���� ����� ��������
		//new str[168];
		//format(str, sizeof(str), "OnPlayerEnterDynamicArea(%d, %d)", playerid, areaid);
		//SendClientMessage(playerid, -1, str);
    
        Storage[playerid][IsInGPS_Polygon] = true;//����� ���� ���������� areaid
		//SendClientMessage(playerid,COLOR_LIGHTBLUE,"���������� �� ���������� �����������");
    }
    return 1;
}

public OnPlayerLeaveDynamicArea(playerid, areaid)
{//streamer
    if(Storage[playerid][PolygonID] == areaid && Storage[playerid][IsInGPS_Polygon])
    {//���� ����� ��� �� ��������
   		//new str[168];
		//format(str, sizeof(str), "OnPlayerLeaveDynamicArea(%d, %d)", playerid, areaid);
		//SendClientMessage(playerid, -1, str);
    
        if(Storage[playerid][Calculating] == 0)
        {//� ������ �������� ��� �� ������
            new PlayerClosest = NearestPlayerNode(playerid);//������� ��������� ���� � ������
            if(PlayerClosest != -1)
            {//���� �����
                if(CalculatePath(PlayerClosest, Storage[playerid][Destination], playerid, .CreatePolygon = true, .GrabNodePositions = true))
                {//������������ ����� ����
                    DisableGPS(playerid);
                    Storage[playerid][Calculating] = 1;
                }
            }
        }
        Storage[playerid][IsInGPS_Polygon] = false;
		//SendClientMessage(playerid,COLOR_RED,"�� ���� � ��������");//������ ������
    }
    return 1;
}

stock DisableGPS(playerid)
{
    if(Storage[playerid][Destination] != -1)
    {
        DestroyDynamicArea(Storage[playerid][PolygonID]);
  //�� �������, �.�. ����� ������� ��� ���� �������
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
		//Storage[playerid][Calculating] = 0;//�� ����������������
        Storage[playerid][Destination] = (-1);
        Storage[playerid][IsInGPS_Polygon] = false;
		gps_RemovePlayer(playerid);
    }
    return 1;
}



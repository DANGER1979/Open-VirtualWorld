/*
 *            vw_player v1.0
 *       (c) Copyright 2017-2018 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (danger1979@mail.ru)
 * @date      : 26.01.2017
 * @update    : 10.11.2018
 *
 * This file is provided as is (no warranties).
 * ���������� � ������������� ����������
 */

//##############################################################################//
//                                                                              //
//                     ����������� ���������� ����������                        //
//                                                                              //
//##############################################################################//
//������������ � ������ ����� ����
new GameRestart = -1;
new numplayers = 0;//������� �������������� �������
new HighestPlayerID = 1;//������������ �� ������ �� �������, �.�. ���-�� ����� +1
/*
//new bigmsgitem[2048];
#define MAX_FUNCTION 65
new TEST[MAX_FUNCTION];
new SWITCH = 1;
new testcount;//������� ��� ������������
new SynchronizerSaved = 0;//��� ������������ ����������

new MySQL_DeBug = 0;
new oldtick;

new bool:OnPlayerUpdate_run = false;


//��� ������ �����
//new npc_counter;//�������


*/

//==============================================================================


/*
new nMessages[MAX_PLAYERS];
*/
//##############################################################################//
//                                                                              //
//                      ����������� ��������� ���������� ������                 //
//                                                                              //
//##############################################################################//
//�� ��� �� ��������� � ������ � � �������� ��������� �� Pvar
//���������� ������� ����� �������������� � ������ �����������, � �� ������ � �����
//����� ��������� �� �������� GetPlayerInterior(playerid)
new CurInt[MAX_PLAYERS]; new LastInt[MAX_PLAYERS];

//����� ��������� �� �������� GetPlayerState(playerid);
new CurState[MAX_PLAYERS]; new LastState[MAX_PLAYERS];

//����� ��������� �� ��������
//nCarID[playerid] = GetPlayerVehicleID(playerid);
//nCarModel[playerid] = GetVehicleModel(nCarID[playerid]);//��������: ����� ��������� ��� �� ��������� �������� � ������ ������� ��� �������� �� 0 �� 400
new nCarID[MAX_PLAYERS], nCarModel[MAX_PLAYERS];//���������������� � OnPlayerStateChange
new LastCar[MAX_PLAYERS], LastDriver[MAX_VEHICLES+1];//��� �������� ���������� �������� ���� ������ MAX_VEHICLES+2, �.�. ID ����� ���������� � 1
//nTrailerID[playerid] = GetVehicleTrailer(nCarID[playerid]);//�������� ID �������� ������������� � ������.
//nTrailerModel[playerid] = VehInfo[trailerid][cModel];//GetVehicleModel(nTrailerID[playerid]);//������ ID ������ ������� �������� ������������� � ������.

new WantedLevel[MAX_PLAYERS];

//!!!�� ���������� �� PVar
new MenuOperation[MAX_PLAYERS];

new gGotOrder[MAX_PLAYERS] = {MAX_PLAYERS-1, ...};//ID ���� �� ���� ������� �����
new Offer[MAX_PLAYERS+MAX_SBIZ+100];//MAX_PLAYERS //������ ID ������������� ������ �� ������� �������

new HireCarID[MAX_PLAYERS];//��� �������� ������ (ID ������) �� ���������� �������


new AFK_IdleTime[MAX_PLAYERS];//��� �������� AwayFromKeyboard
new gAFK_ToggleMode[MAX_PLAYERS];//!!!�� ���������� �� PVar

new gAnticheat[MAX_PLAYERS];

//��� ����� � ����
new TicketMoney[MAX_PLAYERS];
new PlayerTazed[MAX_PLAYERS];
new PlayerTazeTime[MAX_PLAYERS];
new PlayerTied[MAX_PLAYERS];
new PlayerTiedTime[MAX_PLAYERS];
new PlayerCuffed[MAX_PLAYERS] = {MAX_PLAYERS-1, ...};
new PlayerCuffedTime[MAX_PLAYERS];


//!!!�� ���������� �� PVar
new spectateid[MAX_PLAYERS] = {MAX_PLAYERS-1, ...};//spectateid[playerid] = giveplayerid; ID ���� �� ��� �� ���������� �� ������� �����������
new spectatorid[MAX_PLAYERS];//ID ����������� �� ������� ���� ��� �� ��� �� ���������

new gPlayerBoxing[MAX_PLAYERS];//����� � ���

new IsPlayerControllable[MAX_PLAYERS];//�������� ���������

//������� ��������� ���������� � ������

new MinTimeCheckpoint[MAX_PLAYERS];//��� �������� ������������ ������� ���������� �������
new TimeSetCheckpoint[MAX_PLAYERS];
new playerCheckpoint[MAX_PLAYERS];// = {MAX_POINTS, ...};//��� ������������� checkCoords - checkpointType
new CP[MAX_PLAYERS];//��� ��������� ����������
//��� ��������� ����������� ����� �����

//��� �������
new gSpawn[MAX_PLAYERS];//������������� ������ ��� ����� ����� ������
//##############################################################################//
//                                                                              //
//                               ���������� LAST                               //
//                                                                              //
//##############################################################################//
new Float: LastHealth[MAX_PLAYERS] = {100.0, ...};
new Float: VehHealth[MAX_VEHICLES+1]; new Float: LastVehHealth[MAX_PLAYERS];

new Float: LastArmour[MAX_PLAYERS];

new LastKey[MAX_PLAYERS];
new LastMoney[MAX_PLAYERS];
new LastDamagedid[MAX_PLAYERS] = {MAX_PLAYERS-1, ...};//�� ���������� ������ �������� �� ������� ����
new LastIssuerid[MAX_PLAYERS] = {MAX_PLAYERS-1, ...};//�� ���������� ������ ������� ��� ����� ����

new LastWeapon[MAX_PLAYERS], LastStateWeapon[MAX_PLAYERS];//!!!�� ���������� �� PVar
new LastWeaponInSlot[MAX_PLAYERS][13];//��������� ������ � ������ �����
new LastAmmo[MAX_PLAYERS][MAX_WEAPONS+1];//��������� ����������� �� OnPlayerKeyStateChange

new LastKill[MAX_PLAYERS] = {MAX_PLAYERS-1, ...};//�� ���������� ������� ��� ������� ��������� ��

//����� ��������� �� �������� GetPlayerPos
new Float: CurPos[3][MAX_PLAYERS];//���������� ������, ��������� ���������������� � player_OnPlayerUpdate(playerid)
new Float: spawnPos[3][MAX_PLAYERS];//���������� ������ ������ ���������������� � player_OnPlayerSpawn(playerid)
new Float: VehPos[MAX_VEHICLES+1][4];//���������� �����, ��������� ���������������� //���������������� � SetVehiclePosEx

new Float: Mark[3][MAX_PLAYERS];//����� �� �����

new votecount[MAX_PLAYERS];//������� ���-�� ������� �� ���
new CrashDetected[MAX_PLAYERS];

//##############################################################################//
//                                                                              //
//                                    �������                                   //
//                                                                              //
//##############################################################################//

new gPlayerSpawned[MAX_PLAYERS];//���� ����� ����������� !!!�� ���������� �� PVar
new gVehicleSpawn[MAX_VEHICLES+1];
new gPlayerLogged[MAX_PLAYERS];//���� ����� �����������  !!!�� ���������� �� PVar
new gGameText[MAX_PLAYERS];//1 - ����������� ��� �-�� GameTextForPlayerEx, �.�. �� ���������� ��� GameText ���� gGameText == 1
new gTagForPlayer[MAX_PLAYERS];//��� ������ ����� ��� ��������
new IsPlayerTagShow[MAX_PLAYERS][MAX_PLAYERS];//��������� �� PVar
new IsKicked[MAX_PLAYERS]; //new IsBaned[MAX_PLAYERS];
new gCheckDisconnect[MAX_PLAYERS] = 0;//���� ����� ����� �� ������, �� ���� �� �����
new gJobDuty[MAX_PLAYERS];//��� ������ �� ������
new gOnDuty[MAX_PLAYERS];//��� ������ �� ������
new gInTerrorsCount[MAX_PLAYERS];//������������� � ������� ����������
new gInCTerrorsCount[MAX_PLAYERS];//������������� � ������� ����������������
new gInRacing[MAX_PLAYERS];
new gInDerbyBloodBowl[MAX_PLAYERS];
new gInDerby8ball[MAX_PLAYERS] = 0;//�������� �� ������ ������������� � �����
//��� �������������//��� ��������������
new gRobCountdown[MAX_PLAYERS] = {-1, ...};
new gConsumingMoney[MAX_PLAYERS];//���� ����� ������� ������

new gWatchingTV[MAX_PLAYERS];//��� ������� �� !!!�� ���������� �� PVar
new gTranslatorTV = -1;//��� ��


/*
//##############################################################################//
enum TeleportEnum// ������� �������
{
	Flag,
    Float:tX,
    Float:tY,
    Float:tZ,
	Int,
	Virt,
	Loc
};
new Float:TeleportDest[MAX_PLAYERS][TeleportEnum];//��� gotomark getdist

//------------------------------------------------------------------------------
new HouseCar[MAX_PLAYERS];
//new Works[MAX_PLAYERS];//������� ���������
//new ProposedFamily[MAX_PLAYERS];
//-------------------------------


*/

#if defined FILTERSCRIPT
stock player_OnFilterScriptInit()
{
	new time = GetTickCount();
	numplayers = 0;
	HighestPlayerID = 1;

	for(new i = 0; i < GetMaxPlayers(); i++)
	{
		if(!IsPlayerConnected(i)) continue;
		SetPVarInt(i, "ShowMenu", 0);
		numplayers ++;
		if(i > HighestPlayerID) { HighestPlayerID = i+1; }
//��� ��
		new newstate = GetPlayerState(i);
		CurState[i] = newstate;
		LastState[i] = 0;
		if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
		{	//���� ID ������ ��������� ����� ��������� 2//���� ID ������ ��������� ����� ��������� 3 - ��������
			if(newstate == PLAYER_STATE_DRIVER) LastDriver[LastCar[i]] = MAX_PLAYERS-1;
			LastCar[i] = MAX_VEHICLES+1;//����������� ���������� ���������� ������
			nCarID[i] = GetPlayerVehicleID(i);//�������� ID ������ ������ �� ������ ������������� �������
			nCarModel[i] = GetVehicleModel(nCarID[i]);//������ ID ������ ������� ������������� ��������.
		}
		else
		{
			LastCar[i] = 0;
			nCarID[i] = 0; nCarModel[i] = 0;//����������� ����������
			gPlayerSpawned[i] = 1;
		}

		OnPlayerInit(i);
	}

	printf("1/19. [�������� �������� ������]: ��������� - %d (ms)", (GetTickCount()-time));
}
#endif

stock OnPlayerInit(playerid, callback=0, reason=1)//���������� �� OnPlayerConnect � OnPlayerDisconnect
{//������������� ���� ���������� ���� ����������
	#pragma unused reason
	//--------------------------------------------------------------------------
	//for(new i = 0; i != 32; i++) SendClientMessage(playerid, -1, " ");//������� ����
	//--------------------------------------------------------------------------
	/*if( strcmp(php_host, "localhost", true) )//��� ����������
	{
		if(playerid > HighestPlayerID) {
    		format(strings, sizeof(strings), "%s/UpdateMonitor.php", HostName);//stat1.vw-rp.net/UpdateMonitor.php
			HTTP(MAX_PLAYERS-1, HTTP_GET, strings, "", "");
		}
	}*/

	//--------------------------------------------------------------------------

//������ ������//������ ���� �� �����������
	if(!CheckPlayerName(playerid, PlayerName(playerid))
		 //&& strcmp(php_host, "gta.strikearena.ru", true)
      )//������ ����� OnPlayerInit
	{
		IsKicked[playerid] = 1;
		return 1;
	}
////////////////////////////////////////////////////////////////////////////////
	//��������������
	//GetPlayerIp(playerid, PlayerInfo[playerid][pIP], 16);//�������� ip ������ ��� �������� � ������ �� ���
    //format(strings, sizeof(strings), "[join] %s[%d] (IP:%s)", PlayerName(playerid), playerid, PlayerInfo[playerid][pIP]);
	//SendSystemMessage(COLOR_DARKBLUE, strings, 1);
	/*if(!AntiReconnect(playerid))//������ ������ ���� ����� ��������� ip ������
	{
		IsKicked[playerid] = 1;
		return 1;
	}*/
	if(callback == PlayerDisconnect)
	{
		//--------------------------------------------------------------------------
	    if(spectatorid[playerid] != MAX_PLAYERS-1)
	    {   //���� � playerid ���� �����������
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnected(i) || IsPlayerNPC(i)) continue;
				if( !gPlayerLogged[i] ) continue;
				if(spectateid[i] != playerid) continue;
				ReconOff(i);
				TogglePlayerControllableEx(i, 1);
		        gWatchingTV[i] = -1;
	   		}
		}
		//--------------------------------------------------------------------------
		if(HireCarID[playerid] < MAX_VEHICLES-1)
		{   //���� � ������ ��� ���������� ������� ��� ������ �� ����
			UnLockCar(HireCarID[playerid]);//������������ ����� HireCarID
		}
		if(LastCar[playerid] > 0 && LastCar[playerid] < MAX_VEHICLES-1)//������ ���������� LastCar[playerid] !=701 MAX_VEHICLES+1
		{   //���� ���������� LastCar[playerid] �� ���������
			if( !IsInRentCar(LastCar[playerid]) )
			{   //���� ��������� ������ �� ������������
				if(LastDriver[LastCar[playerid]] == playerid)
				{   //���� ��������� �������� ���� ������ ������� �� � ����� ������ �� �� ��� ���� ����������
					LastDriver[LastCar[playerid]] = MAX_PLAYERS-1;
					//����������� ���������� ���������� ������
					//UnLockCar(LastCar[playerid]);
					//������������ ����� ��� ������ �� ������� �����
				}
			}
		}
		//KillTimer(PickupTimer[playerid]);//��� ���������
		RemovePlayerAllAttachedObjectEx(playerid);
		PlayerKillTimer(playerid);
		/*if(strcmp(php_host, "localhost", true) && reason == 1 && GameRestart != 1)
		{// ���� �� localhost
			new strtmp[52+24];
			format(strtmp, sizeof(strtmp), "%s/UpdatePasport.php?Login=%s", HostName, PlayerName(playerid));
			HTTP(playerid, HTTP_GET, strtmp, "", "");
		}*/
	}

//��� ������� �����
	/*if( !strcmp(php_host, "vw-rp.net", true) )
	{
//��� ������ ������ ���� ���� �����
		gTagForPlayer[playerid] = 1;//���������, ��� ��� �� ����� ������� ������
		for(new i = 0; i < MAX_PLAYERS; i++) ShowPlayerNameTagForPlayerEx(playerid, i, 1);//��� ������ playerid �������� ���� ���� �������
	}
	else
	{
//��� ������ ������ ���� ���� �� �����
		gTagForPlayer[playerid] = 0;
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			IsPlayerTagShow[i][playerid] = 0; //�������� ��� ������ playerid ��� ����
		}
	}*/
	//--------------------------------------------------------------------------
//���� ����� 3 ������� ��������� �������, �� �������� ����������
	//if(GetTickCount() >= gCheckDisconnect[playerid] + 3000)
	gCheckDisconnect[playerid] = 0;
	CrashDetected[playerid] = 0;
	gPlayerLogged[playerid] = 0;//1 - ���� ����� �����������
	gPlayerSpawned[playerid] = 0;//1 - ���� ����� �����������
	gSpawn[playerid] = 0;//������������� ������ ��� ����� ����� ������

	votecount[playerid] = 0;//������� ���-�� ������� �� ���
	PingCount[playerid] = 0;//������� ���-�� ������������ ��� ���������� �����

	playerCheckpoint[playerid] = 0;//MAX_POINTS;//��� ��������� ����������� �����
	CP[playerid] = 0; //��� ��������� ����������
	gGotOrder[playerid] = MAX_PLAYERS-1;
	gAFK_ToggleMode[playerid] = 0;	AFK_IdleTime[playerid] = 0;//��� �������� AwayFromKeyboard
	gGameText[playerid] = 0;
	
    SetPVarInt(playerid, "PlayerID", MAX_PLAYERS-1);
	SetPVarInt(playerid, "gOoc", 1);
	SetPVarInt(playerid, "gNews", 1);
	SetPVarInt(playerid, "gFam", 1);
	SetPVarInt(playerid, "gHidePM", 0);
	SetPVarInt(playerid, "gSport", 1);
	SetPVarInt(playerid, "gJob", 1);
	SetPVarInt(playerid, "gSwitcher", 0);
	SetPVarInt(playerid, "OldSkin", SKIN_DEFAULT);
	//------------------------------------------------------------------------------
	//GuardPrice[playerid] = 0;//Offer[playerid] = MAX_PLAYERS-1; //��� ��������������

	CurState[playerid] = 0;
	LastState[playerid] = 0;
	LastDriver[playerid] = MAX_PLAYERS-1;
	LastCar[playerid] = MAX_VEHICLES+1;//����������� ���������� ���������� ������
	nCarID[playerid] = 0;//�������� ID ������ ������ �� ������ ������������� �������
	nCarModel[playerid] = 0;//������ ID ������ ������� ������������� ��������.

//��� �������
	/*strdel(pParrotSentence[playerid][0],0,MAX_STRING);
	strdel(pParrotSentence[playerid][1],0,MAX_STRING);
	strdel(pParrotSentence[playerid][2],0,MAX_STRING);
	strdel(pParrotSentence[playerid][3],0,MAX_STRING);
	strdel(pParrotSentence[playerid][4],0,MAX_STRING);
	strdel(pParrotName,0,20);
	pHasParrot[playerid] = 0;*/

	return 1;
}//END OnPlayerInit


//##############################################################################//
//                                                                              //
//                             ����������� �������                              //
//                                                                              //
//##############################################################################//


stock player_OnPlayerConnect(playerid)
//public OnPlayerConnect(playerid)
{
	numplayers ++;//���-�� ������� �� ������� //����� IsPlayerNPC
	if(playerid > HighestPlayerID) { HighestPlayerID = playerid+1; }
	
	OnPlayerInit(playerid, PlayerConnect);

	SendClientMessage(playerid, COLOR_ORANGE, "Game Editor v1.0 {FFFFFF}");
	SendClientMessage(playerid, COLOR_ORANGE, "(USE: ~k~~GROUP_CONTROL_BWD~) ����� help");
	SendClientMessage(playerid, COLOR_ORANGE, "(USE: ~k~~PED_ANSWER_PHONE~) ��� ������ � ����������� ������");
	SendClientMessage(playerid, COLOR_ORANGE, "(USE: ~k~~TOGGLE_SUBMISSIONS~) ��� ������ � ����������� ����� ���� � ���");
	SendClientMessage(playerid, COLOR_ORANGE, "������� �� ����� � ����� ������� ������� /gps ��� ������������� ��������");
	
    new version[40];
    GetPlayerVersion(playerid, version, sizeof(version));
	if( strcmp(version, "0.3.7-R4", true) )
	{
		new strtmp[69+40];
	    //format(strtmp, sizeof(strtmp), "Your version of SA-MP: %s", version);
	    //SendClientMessage(playerid, 0xFFFFFFFF, strtmp);
	    format(strtmp, sizeof(strtmp), "CEPBEP: {33AA33}���������� �������� ���� ������ SA-MP �� {FFFFFF}%s!", version);
	    SendClientMessage(playerid, COLOR_RED, strtmp);
	    SendClientMessage(playerid, COLOR_GREY, "C������ ��������� ������ SA-MP ����� � http://www.sa-mp.com/download.php");
	    //if( !strcmp(php_host, "gta.strikearena.ru", true) ) { IsKicked[playerid] = 1; return 1; }
	}
	if(Security != 0 && strcmp(PlayerName(playerid), CREATOR, true))
	{
	    SendClientMessage(playerid, COLOR_RED, "A������������ �������� ������ ���� �� ������.");
	    IsKicked[playerid] = 1;
	    return 1;
	}
	return 1;
}

stock player_OnPlayerSpawn(playerid)
{
	//#pragma unused playerid
	StopAudioStreamForPlayer(playerid);

	//SetPlayerCriminal(member, playerid, killed, reason);
	SetPlayerWantedLevel(playerid, WantedLevel[playerid]);//�����

	GetPlayerPos(playerid, spawnPos[0][playerid], spawnPos[1][playerid], spawnPos[2][playerid]);

	ResetPlayerMoney(playerid);//�������� ������ ������ �� 0
	gConsumingMoney[playerid] = CHEATLIM;
	LastHealth[playerid] = 100.0;
	LastState[playerid] = CurState[playerid];
//==============================================================================

	SetPVarInt(playerid, "SpawnSelection", 1);//�� ������ ������ ����� �������� ����� ������ ��� �����
	//����� ������ ��� �� ����������� ���� �� ����� ������, � ������� �������� ����
}


stock player_OnPlayerDisconnect(playerid, reason)
//public OnPlayerDisconnect(playerid, reason)
{
	//#pragma unused reason
	numplayers --;//����� IsPlayerNPC
	if(playerid >= HighestPlayerID+1) HighestPlayerID = playerid - 1;

	OnPlayerInit(playerid, PlayerDisconnect, reason);
	return 1;
}


stock player_OnPlayerDeath(playerid, killerid, reason)
//public OnPlayerDeath(playerid, killerid, reason)
{
	#pragma unused killerid
	#pragma unused reason
	
	//if(	PlayerInfo[playerid][pJailed] == 0 &&
	//	!gPlayerBoxing[playerid] && !gInTerrorsCount[playerid] && !gInCTerrorsCount[playerid])
	//{
	CurState[playerid] = PLAYER_STATE_KILLED;
	//gMedicBill[playerid] = 1;//��������� ���� ��� ����������� �������
	//}
	
	LastKill[killerid] = playerid;//������ ������ ���� � �����
	
	gPlayerSpawned[playerid] = 0;
}

//LastDriver - ����� ������ ��� ��������� ����� �� ������ �����
stock player_OnPlayerStateChange(playerid, newstate, oldstate)
//public OnPlayerStateChange(playerid, newstate, oldstate)
{//�� ���������� ���� ����� ������ ����� �� ����� �����
	//SendAllAdminMessage(COLOR_RED, "CHECKING OnPlayerStateChange !!!", 6);
	if(newstate != oldstate) { CurState[playerid] = newstate; LastState[playerid] = oldstate; }
	if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
	{	//���� ID ������ ��������� ����� ��������� 2//���� ID ������ ��������� ����� ��������� 3 - ��������

		if(newstate == PLAYER_STATE_DRIVER)
		{
			/*if(LastCar[playerid] > 0 && LastCar[playerid] < MAX_VEHICLES+1)
			{   //���� ���������� LastCar[playerid] �� ���������
				if(	LastDriver[LastCar[playerid]] == playerid &&
					nCarID[playerid] != LastCar[playerid])	//���� ���� � ��. ������ �� ���� ���������� ���������� ����������
				{   //���� ��������� �������� ���� ������ ������� �� � ����� ������ �� �� ��� ���� ����������
					LastDriver[LastCar[playerid]] = MAX_PLAYERS-1;//����������� ���������� ���������� ��������
				}
			}*/
			LastDriver[LastCar[playerid]] = MAX_PLAYERS-1;
		}
		LastCar[playerid] = MAX_VEHICLES+1;//����������� ���������� ���������� ������
		nCarID[playerid] = GetPlayerVehicleID(playerid);//����������� � player_OnPlayerStateChange(playerid, newstate, oldstate)
		nCarModel[playerid] = GetVehicleModel(nCarID[playerid]);//����������� � player_OnPlayerStateChange(playerid, newstate, oldstate)
		
		format(strings, sizeof(strings), "~g~%s", VehicleArray[nCarModel[playerid]-400][Vehicle_Name] );
		GameTextForPlayerEx(playerid, strings, 3000, 1);
	}
	/*else if((oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER) &&
			newstate != PLAYER_STATE_DRIVER && newstate != PLAYER_STATE_PASSENGER)//���� ID ������ ��������� ����� ��������� 1( �� �����)
	{   //����������� ������ ����� ������ �� ������
		nCarID[playerid] = 0; nCarModel[playerid] = 0;//����������� ����������
	}*/
	else if(oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)//����������� ����� ������ �� ������
	{	//���� ID ������� ��������� ����� ��������� 2//���� ID ������� ��������� ����� ��������� 3 - ��������
		LastCar[playerid] = nCarID[playerid];
		if(oldstate == PLAYER_STATE_DRIVER) LastDriver[nCarID[playerid]] = playerid;//�������� ID ������ �� ������ � ������� �� �������
		nCarID[playerid] = 0; nCarModel[playerid] = 0;//����������� ����������
	}
}

stock player_InteriorChange(playerid, newinteriorid, oldinteriorid)
//public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	if(newinteriorid != oldinteriorid) { CurInt[playerid] = newinteriorid; LastInt[playerid] = oldinteriorid; }
}

stock player_OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{//���������� ����� ����� playerid ������� ���� ������ damagedid
	LastDamagedid[playerid] = damagedid;
}

stock player_OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{   //��� ��� ���� � ��� �� ����������

	LastIssuerid[playerid] = issuerid;//���������� ���������� ��� ��� ������� ����
	LastHealth[playerid] -= amount;

}

stock player_OnPlayerUpdate(playerid)
//public OnPlayerUpdate(playerid)
{
	new Float:pX, Float:pY, Float:pZ; //new Float:pA, Float:ang;
	GetPlayerPos(playerid, pX, pY, pZ);	//GetPlayerFacingAngle(forplayerid, pA);
    CurPos[0][playerid] = pX;
	CurPos[1][playerid] = pY;
	CurPos[2][playerid] = pZ;
}

stock IsPlayerInRangeOfPointEx(playerid, Float:range, Float:x, Float:y, Float:z)
{
	new Float:distance;
	distance = floatsqroot(
						floatpower(floatsub(x, CurPos[0][playerid]),2)+
						floatpower(floatsub(y, CurPos[1][playerid]),2)+
						floatpower(floatsub(z, CurPos[2][playerid]),2)
					  );
	if( floatcmp(range, distance) != -1) return 1;//IsPlayerInRangeOfPoint(playerid, range, x, y, z);
/* Compare two integers. If the two elements are equal, return 0.
   If the first argument is greater than the second argument, return 1,
   If the first argument is less than the second argument, return -1. */
	else return 0;
}
//##############################################################################


//������� ����� ������� �������, �.�. ��� ����� ���� ��� ��������
stock PlayerKillTimer(playerid)
{
	//KillTimer(stopmusictimer[playerid]); stopmusictimer[playerid] = -1;
	//KillTimer(fixradiotimer[playerid]); fixradiotimer[playerid] = -1;
	//KillTimer(playerblind[playerid]); playerblind[playerid] = -1;
 	KillTimer(gRobCountdown[playerid]); gRobCountdown[playerid] = -1;
	//KillTimer(WeaponTimer[playerid]); WeaponTimer[playerid] = -1;
}





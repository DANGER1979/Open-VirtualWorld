/*  VW Vehicle Functions
 *
 *  (c) Copyright 2009-2020, VW Team
 *
 */


//���� �� ����������� ��� ������������� �� ����� �������, �� ��� ������� ���� ���������������� ������� ���������� ����� ��� �������� �������
new nTrailerID[MAX_PLAYERS], nTrailerModel[MAX_PLAYERS], LastTrailer[MAX_VEHICLES+1];//!!!�� ���������� �� PVar
new LastTrailerCarrier[MAX_VEHICLES+1] = {MAX_PLAYERS-1, ...};
new MyCar[MAX_PLAYERS][3];
new gVehicleLock[MAX_PLAYERS];
new SpecialBleep[MAX_VEHICLES+1];//����������� �������� ������
new benzProv[MAX_VEHICLES+1];//��� ������� �������
new Float:StartTruckHealth[MAX_VEHICLES+1] = {1000.0, ...};// = 1000.0;//100% �������� ��������� ������

//==============================================================================
//������� ��������� �����

//������� ����������� ����� (�������, �������)
enum status_info
{
	st_engine,
	st_lights,
	st_alarm,
	st_doors,
	st_bonnet,
	st_boot,
	st_objective
};
new CarStatus[MAX_VEHICLES+1][status_info];

new Timer_VehAlarm[MAX_VEHICLES];
//������������� ������� CarStatus
stock SetVehicleParams(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective)
{   //���������� �� OnPlayerPickUpPickup, OnPlayerStateChange, OnPlayerKeyStateChange, CreateStaticVehicleEx
//�� ������ ������ ����� ��� �� ��������� ��������� ����������� ���� ��� ������
	//#pragma unused playerid
	CarStatus[vehicleid][st_engine] = engine;
	CarStatus[vehicleid][st_lights] = lights;
	CarStatus[vehicleid][st_alarm] = alarm;
	CarStatus[vehicleid][st_doors] = doors;
	CarStatus[vehicleid][st_bonnet] = bonnet;
	CarStatus[vehicleid][st_boot] = boot;
	CarStatus[vehicleid][st_objective] = objective;
	
    if(alarm)
    {
        KillTimer(Timer_VehAlarm[vehicleid]);
        Timer_VehAlarm[vehicleid] = SetTimerEx("DisableVehicleAlarm", 20000, false, "d", vehicleid);
    }
	return SetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
}
forward DisableVehicleAlarm(vehicleid);
public DisableVehicleAlarm(vehicleid)
{
    new engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
    if(alarm == VEHICLE_PARAMS_ON)
    {
    	SetVehicleParamsEx(vehicleid, engine, lights, VEHICLE_PARAMS_OFF, doors, bonnet, boot, objective);
    }
}


stock GetVehicleParams(vehicleid, &engine, &lights, &alarm, &doors, &bonnet, &boot, &objective)
//stock GetVehicleParams(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective)
{
	GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
	CarStatus[vehicleid][st_engine] = engine;
	CarStatus[vehicleid][st_lights] = lights;
	CarStatus[vehicleid][st_alarm] = alarm;
	CarStatus[vehicleid][st_doors] = doors;
	CarStatus[vehicleid][st_bonnet] = bonnet;
	CarStatus[vehicleid][st_boot] = boot;
	CarStatus[vehicleid][st_objective] = objective;
}
//==============================================================================
//������� ����������� �����

/*
	VEHICLE_DOOR_UNDAMAGED = 0, // ����
	VEHICLE_DOOR_SWINGING, // �������(��������)
	VEHICLE_DOOR_DAMAGED, // ������
	VEHICLE_DOOR_DAMAGED_SWINGING, // ������ � �������(��������)
	VEHICLE_DOOR_FELL_OF // ��������

	VEHICLE_BOOT_UNDAMAGED, // ����
	VEHICLE_BOOT_SWINGING, // �������(��������)
	VEHICLE_BOOT_DAMAGED, // ������
	VEHICLE_BOOT_DAMAGED_SWINGING, // ������ � �������(��������)
	VEHICLE_BOOT_FELL_OF // ��������

	VEHICLE_BONNET_UNDAMAGED, // ����
	VEHICLE_BONNET_SWINGING, // �������(��������)
	VEHICLE_BONNET_DAMAGED, // ������
	VEHICLE_BONNET_DAMAGED_SWINGING, // ������ � �������(��������)
	VEHICLE_BONNET_FELL_OF // ��������

	VEHICLE_WINDSHIELD_UNDAMAGED, // ����
	VEHICLE_WINDSHIELD_CRACKED_1, // ��������
	VEHICLE_WINDSHIELD_CRACKED_2, // ��������
	VEHICLE_WINDSHIELD_DESTROYED // �������

	VEHICLE_TIRE_UNDAMAGED, // ����
	VEHICLE_TIRE_DAMAGED // �������

	VEHICLE_LIGHT_UNDAMAGED, // ����
	VEHICLE_LIGHT_DAMAGED // �������
*/
/*
const windshield_crackedA = 1;
const windshield_crackedB = 2;
const windshielddestroyed = 3;
*/
const undamaged = 0;// ����
const swinging = 1;// ��������
const damaged = 2;// ������
const damaged_swinging = 3;// ������ � ��������
const fell_off = 4;// ��������




//##############################################################################//
//                                                                              //
//             ��� ����� �-�� ��������� ������� ��������� � �������             //
//                   ������� ���������� �� ����� ������������                   //
//                                                                              //
//##############################################################################//

//stock car_OnGameModeInit()//���������� �� OnGameModeInit
stock vehicle_OnGameModeInit()
{   //�-�� ��������� �������������
	new time = GetTickCount();
//����� ���� ������, ��� �� ������ ����������� �������, ��� �� ����� � �����
	//LoadCarSQL();
	LoadCarCounter = 0;//������� ������������ ���������� ��� ������ ����
	VehiclesCounter = 0;//����� ������� ����������� �����
	GetMaxVehicles = 0;
	VehiclesModelsCounter = 0;
	//--------------------------------------------------------------------------

//��� ������� ������� ������ �� ������ ������ ���� ���������� ����� ������������ �������,
//����� �� ������� ���� � �� ����������
//printf("�������� 0");
	//for(new carid = 1; carid<(MAX_VEHICLES-1); carid++)
	for(new carid = GetVehiclePoolSize(); carid != 0; --carid)//Gets the highest vehicleid currently in use on the server.
	{   //GetMaxVehicles ���������������� ��� �������� �����, ���� ����� ������� ������ ��������, �� �������� �� �����
		if(!IsValidVehicle(carid)) continue;//������� �� ������������ ��������.
		new modelid = GetVehicleModel(carid);
		if(modelid < 400) continue;//���������� �� ������������� �����
//printf("�������� carid:%d ������", carid);//�������� �� 774//751//775//814//1073//861//1045

 		LastDriver[carid] = MAX_PLAYERS-1;
		SpecialBleep[carid] = 0;//������� ���������
		benzProv[carid] = 0;//��� ������� ������� ��������
		StartTruckHealth[carid] = 1000.0;//��������� �������� ������ ���������� 1000

		//�������������� VehInfo_OnCarInit(carid);
		VehInfo[carid][cIND] = 0;
		VehInfo[carid][cID] = carid;
		strmid(VehInfo[carid][cKey], "", 0, strlen(""), 12);
		VehInfo[carid][cModel] = modelid;

		//----------------------------------------------------------------------
		new Found = 0;
		for(new vm=0; vm<MAX_VEHICLES; vm++)//MAX_VEHICLES //VehiclesCounter //GetMaxVehicles
		{   //��������� ��� ����� ������� aExistModel, ���� ������ ������ ����������� � ������� aExistModel, �� ������� �� �����
			if(VehInfo[carid][cModel] == aExistModel[vm]) { Found = 1; break; }
		}
	   	if(Found == 0)
	   	{   //���� �� ����� � ����� �� ����� �������, ������� ������ ��������� �������
			VehiclesModelsCounter ++;
			aExistModel[VehiclesModelsCounter] = VehInfo[carid][cModel];
		}
		//----------------------------------------------------------------------

		VehInfo[carid][cType] = 0;
		VehInfo[carid][cOwned] = 0;

    	new Float: pos[4];
    	GetVehiclePos(carid, pos[0], pos[1], pos[2]);
    	GetVehicleZAngle(carid, pos[3]);
	 	VehInfo[carid][cLocX] = pos[0];
	 	VehInfo[carid][cLocY] = pos[1];
		VehInfo[carid][cLocZ] = pos[2];
		VehInfo[carid][cAng] = pos[3];

		VehInfo[carid][cInt] = 0;
		VehInfo[carid][cVirt] = GetVehicleVirtualWorld(carid);
		VehInfo[carid][cLock] = 0;
		VehInfo[carid][cPark] = 0;
		VehInfo[carid][cInsur] = 0;

		//VehInfo[carid][cFuel] = float(VehicleArray[modelid-400][GasMax]);
		VehInfo[carid][cLoad] = 0;
		VehInfo[carid][cLoadType] = 0;
		VehInfo[carid][cDate] = 0;

		//�� ���������� �.�. �������� ��� ����� �����-�� ��������
		if(VehInfo[carid][cColor1] == 0) VehInfo[carid][cColor1] = -1;
		if(VehInfo[carid][cColor2] == 0) VehInfo[carid][cColor2] = -1;
		//if(VehInfo[carid][cPaintjob] == 0) VehInfo[carid][cPaintjob] = 255;

		//�������������� ���������� � ������� VehInfo
		//if(IsValidComponent(componentid, CARMODTYPE_SPOILER))
		VehInfo[carid][cSpoiler] = GetVehicleComponentInSlot(carid, CARMODTYPE_SPOILER);
		//if(IsValidComponent(componentid, CARMODTYPE_HOOD))
		VehInfo[carid][cHood] = GetVehicleComponentInSlot(carid,  CARMODTYPE_HOOD);
		//if(IsValidComponent(componentid, CARMODTYPE_ROOF))
		VehInfo[carid][cRoof] = GetVehicleComponentInSlot(carid, CARMODTYPE_ROOF);
		//if(IsValidComponent(componentid, CARMODTYPE_SIDESKIRT))
		VehInfo[carid][cSideskirt] = GetVehicleComponentInSlot(carid, CARMODTYPE_SIDESKIRT);
		//if(IsValidComponent(componentid, CARMODTYPE_LAMPS))
		VehInfo[carid][cLamps] = GetVehicleComponentInSlot(carid, CARMODTYPE_LAMPS);
		//if(IsValidComponent(componentid, CARMODTYPE_NITRO))
		VehInfo[carid][cNitro] = GetVehicleComponentInSlot(carid, CARMODTYPE_NITRO);
		//if(IsValidComponent(componentid, CARMODTYPE_EXHAUST))
		VehInfo[carid][cExhaust] = GetVehicleComponentInSlot(carid, CARMODTYPE_EXHAUST);
		//if(IsValidComponent(componentid, CARMODTYPE_WHEELS))
		VehInfo[carid][cWheels] = GetVehicleComponentInSlot(carid, CARMODTYPE_WHEELS);
		//if(IsValidComponent(componentid, CARMODTYPE_STEREO))
		VehInfo[carid][cStereos] = GetVehicleComponentInSlot(carid, CARMODTYPE_STEREO);
		//if(IsValidComponent(componentid, CARMODTYPE_HYDRAULICS))
		VehInfo[carid][cHydraulics] = GetVehicleComponentInSlot(carid, CARMODTYPE_HYDRAULICS);
		//if(IsValidComponent(componentid, CARMODTYPE_FRONT_BUMPER))
		VehInfo[carid][cFrontBumper] = GetVehicleComponentInSlot(carid, CARMODTYPE_FRONT_BUMPER);
		//if(IsValidComponent(componentid, CARMODTYPE_REAR_BUMPER))
		VehInfo[carid][cRearBumper] = GetVehicleComponentInSlot(carid, CARMODTYPE_REAR_BUMPER);
		//if(IsValidComponent(componentid, CARMODTYPE_VENT_RIGHT))
		VehInfo[carid][cVentRight] = GetVehicleComponentInSlot(carid, CARMODTYPE_VENT_RIGHT);
		//if(IsValidComponent(componentid, CARMODTYPE_VENT_LEFT))
		VehInfo[carid][cVentLeft] = GetVehicleComponentInSlot(carid, CARMODTYPE_VENT_LEFT);

		DestroyObjectEx(VehInfo[carid][cNeonl]); VehInfo[carid][cNeonl] = 0;//���������� �������,
		DestroyObjectEx(VehInfo[carid][cNeonl]); VehInfo[carid][cNeonr] = 0;//�.�. �� ��������� ����� ���������

		GetVehicleHealth(carid, VehInfo[carid][cHealth]);//�������������� ������� �������� ��������

		//�������������� ����������� � ������� VehInfo
		GetVehicleDamageStatus(carid,
			VehInfo[carid][DamagePanels], VehInfo[carid][DamageDoors],
			VehInfo[carid][DamageLights], VehInfo[carid][DamageTires]);

		//�������������� ������ CarStatus ������ ��� ����� ������� �������� � �������� ��� ��������� �����������
		//new engine, lights, alarm, doors, bonnet, boot, objective;
		//GetVehicleParams(carid, engine, lights, alarm, doors, bonnet, boot, objective);
		//SetVehicleParams(carid, VEHICLE_PARAMS_ON, lights, alarm, doors, bonnet, boot, objective);//�� ���� �������, �.�. ��� ������ ���������
//format(strings, sizeof(strings), "1. carid: %d. engine: %d lights: %d alarm: %d doors: %d bonnet: %d boot: %d objective: %d", carid, engine, lights, alarm, doors, bonnet, boot, objective);
//printf(strings);

		if(carid > GetMaxVehicles) GetMaxVehicles = carid;//������������ �� ����� � ����
		LoadCarCounter ++;
		VehiclesCounter ++;
		//gVehicleSpawn[carid] = 1;

		//if(SetVehicleToRespawn(carid)) printf("�������� carid:%d ���������", carid);//������������ ��� ����������� �������
//��������: SetVehicleToRespawn �� ������ ���� � �-��� �������� ������� ��� ����
		//else printf("����� %d �� ��������������", carid);
	}
	printf("2/19. [�������� �������� ����]: ���� ��������� - %d[%d], ��������� - %d (ms)", LoadCarCounter, VehiclesCounter, (GetTickCount()-time));
	return 1;
}


stock vehicle_OnPlayerConnect(playerid)
{

//��� �����
	//MusicIndex[playerid] = 0;
	LastCar[playerid] = 0;

	HireCarID[playerid] = MAX_VEHICLES-1;
	gVehicleLock[playerid] = 0;//MAX_VEHICLES-1;//��� �����


	nCarID[playerid] = 0; nCarModel[playerid] = 0; nTrailerID[playerid] = 0; nTrailerModel[playerid] = 0;
	MyCar[playerid][0] = 0; MyCar[playerid][1] = 0; MyCar[playerid][2] = 0;
}



stock vehicle_OnVehicleDeath(vehicleid, killerid)
{
	#pragma unused killerid
	gVehicleSpawn[vehicleid] = 1;
	DestroyVehicleEx(vehicleid, 6);

//-------------------------------------------------------------------------------
	new Float:X,Float:Y,Float:Z;
	GetVehiclePos(vehicleid, X, Y, Z);

	/*if(	VehInfo[vehicleid][cPark] == 0 &&
		VehInfo[vehicleid][cInsur] > 0 && //VehHealth[vehicleid] > 250.0 &&
		Z < 1.0)
	{   //���� ����� ������ ��� ����������� ������ 0 �������� ������ 250 � ���� ������ ����
		//if(	(rotX <= -90.0 || rotX >= 90.0) ||//���� ����� ����������
		//	(rotY <= -90.0 || rotY >= 90.0)//������ ����� ����������
		//  )
		//{
//�� ������� �
			//new strings[MAX_STRING];
			format(strings, sizeof(strings),
				"VehicleDeath in water[%d]. LastDriver: %s[%d]. (%.1f, %.1f, %.1f) ����: %.1f, ������: %.1f, ��������: %.1f",
				//"AdmWarning: VehicleDeath [%d]. LastDriver: %s[%d]. ����: %.1f, ������: %.1f, ��������: %.1f",
				vehicleid, PlayerName(LastDriver[vehicleid]), LastDriver[vehicleid],
				X, Y, Z,
				rotX, rotY, rotZ);
			SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strings, 3);

		//gVehicleSpawn[vehicleid] = 1;
		//SetVehicleToRespawn(vehicleid);
		return 1;
		//}
	}*/

//����� ��������� �������� �� ������ �����, �.�. ���� ���� 1 �� ������ ��� ��������� �������
//�� ����� ����� ������ ������ ����� ������ ���� ����� � ����� ����� ������� ����� ��� �-�� �����
	if(	VehInfo[vehicleid][cPark] == 0 && //(VehHealth[vehicleid] <= 250.0 || Z < 1.0) &&
		GetVehicleModel(vehicleid) != 460 && GetVehicleModel(vehicleid) != 539)
	{
		//GetVehicleZAngle(nCarID[playerid], angle);
		/*new Float:rotX,Float:rotY,Float:rotZ;
		GetVehicleRotation(vehicleid, rotX, rotY, rotZ);
		if(VehInfo[vehicleid][cOwned] > 0 && GameRestart != 1)
		{
			new Float: vehhp;
			GetVehicleHealth(vehicleid, vehhp);//�����
			new strtmp[91+24+3+3+3+2+1+3+3+3+3+3];
			format(strtmp, sizeof(strtmp), "vehDeath:%d %s[%s] hp:%.1f park:%d lock:%d insur:%d (%.1f %.1f %.1f) ����:%.1f ������:%.1f",
				vehicleid,
				PlayerName(LastDriver[vehicleid]),
				VehInfo[vehicleid][cOwner],
				vehhp,
				VehInfo[vehicleid][cPark], VehInfo[vehicleid][cLock], VehInfo[vehicleid][cInsur],
				X, Y, Z,
				rotX, rotY);
			Log(DEATH,strtmp);
			SendAllAdminMessage(COLOR_RED, strtmp, 1);
		}*/
		//----------------------------------------------------------------------
		gVehicleSpawn[vehicleid] = 1;
		DestroyVehicleEx(vehicleid, 6);
	}
	/*else
	{
		gVehicleSpawn[vehicleid] = 1;
		SetVehicleToRespawn(vehicleid);
	}*/

}

stock vehicle_OnVehicleSpawn(vehicleid)
{   //�-�� ��������� �������� ������ ����� ��� ������� ������������� ������
//����� ������ ���� � ����� ��������� ��� � �� ������
	/*SetVehicleParams(vehicleid,//������������� ������� �� ������� CarStatus
				CarStatus[vehicleid][st_engine],
				CarStatus[vehicleid][st_lights],
				CarStatus[vehicleid][st_alarm],
				CarStatus[vehicleid][st_doors],
				CarStatus[vehicleid][st_bonnet],
				CarStatus[vehicleid][st_boot],
				CarStatus[vehicleid][st_objective]);*/

	new modelid = GetVehicleModel(vehicleid);
	if(modelid < 400) return 1; //���������� �� ������������� �����
	if(gVehicleSpawn[vehicleid] != 1)
	{//���� ����� �������� �� ����� ������ � �� �� ��������� �������, �.�. ���� ��� �����
		//���� ����� �� ��������������� ��������, �� ������� � �����
		//SetVehiclePosEx(vehicleid, VehInfo[vehicleid][cLocX], VehInfo[vehicleid][cLocY], VehInfo[vehicleid][cLocZ]);
	   	//SetVehicleZAngleEx(vehicleid, VehInfo[vehicleid][cAng]);
	   	LoadCarUpgrade(vehicleid);
		RepairVehicle(vehicleid);
		VehInfo[vehicleid][cFuel] = VehicleArray[modelid-400][GasMax];
		
	   	if(VehInfo[vehicleid][cType] < 1000)
	   	{
			RepairVehicle(vehicleid);
			VehInfo[vehicleid][cFuel] = VehicleArray[modelid-400][GasMax];
		}
		
	}
	else//����� ���� ����� �������� �� ��������� �������
	{
		//��������: �� ���������� ��� ������ �� ����������
		//��������������
		//////new strings[MAX_STRING];
		//format(strings, sizeof(strings), "OnVehicleSpawn(%d)", vehicleid);
		//ABroadCast(COLOR_MAROON, strings, 9);
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			/*if(HireCarID[i] == vehicleid)
			{
				UnLockCar(vehicleid);
				HireCarID[i] = MAX_VEHICLES-1;//���������� ����������
				GameTextForPlayerEx(i, "~w~You no longer ~y~rent a car", 5000, 3);
			}*/
			if(nCarID[i] == vehicleid)
			{   //��������� ���� ��� ����� � ���� �����
				RemovePlayerFromVehicleEx(i);
			}
		}
		SetVehicleNumberPlateEx(vehicleid, modelid);
		LoadCarUpgrade(vehicleid);
		
		/*if(VehInfo[vehicleid][cOwned] > 0 && loadcarupgradetimer == -1)
		{
			new Float:X,Float:Y,Float:Z;
			new Float:rotX,Float:rotY,Float:rotZ;
			GetVehiclePos(vehicleid, X, Y, Z);//���� ����� ������ ������� �������, �� ���������� ����� ����� ������
			//GetVehicleZAngle(nCarID[playerid], angle);
			GetVehicleRotation(vehicleid, rotX, rotY, rotZ);

			new Float: vehhp;
			GetVehicleHealth(vehicleid, vehhp);//�����
			new strtmp[91+24+3+3+3+2+1+3+3+3+3+3];
			format(strtmp, sizeof(strtmp), "vehSpawn %s[%s] id:%d hp:%.1f[%.1f] park:%d lock:%d (%.1f %.1f %.1f) ����:%.1f ������:%.1f",
				PlayerName(LastDriver[vehicleid]),
				VehInfo[vehicleid][cOwner],
				vehicleid,
				vehhp, VehHealth[vehicleid],
				VehInfo[vehicleid][cPark], VehInfo[vehicleid][cLock],
				X, Y, Z,
				rotX, rotY);
			Log(SPAWN,strtmp);
			//SendAllAdminMessage(COLOR_RED, strtmp, 3);
		}*/
		
		gVehicleSpawn[vehicleid] = 0;
		
		
		
	}
	
//����� ������ ���� � ����� ��������� ��� � �� ������
	SetVehicleParamsEx(vehicleid,
				CarStatus[vehicleid][st_engine],
				CarStatus[vehicleid][st_lights],
				CarStatus[vehicleid][st_alarm],
				CarStatus[vehicleid][st_doors],
				CarStatus[vehicleid][st_bonnet],
				CarStatus[vehicleid][st_boot],
				CarStatus[vehicleid][st_objective]);



	if(VehInfo[vehicleid][cPark] != 0)
	{//���� ����� ����������� �� ��� ������������ �� ����� ��������
		SetVehiclePosEx(vehicleid, VehInfo[vehicleid][cLocX], VehInfo[vehicleid][cLocY], VehInfo[vehicleid][cLocZ]);
	   	SetVehicleZAngleEx(vehicleid, VehInfo[vehicleid][cAng]);//GetVehicleZAngle(vehicleid, VehInfo[vehicleid][cAng]);
   	}
   	else
   	{
   		if(VehInfo[vehicleid][cType] >= 1000 && VehPos[vehicleid][2] > 0)//����� �� ������ ������� �������� �����
   		{//���� ����� ������, �� �� ����� ������ �� �����
			SetVehiclePosEx(vehicleid, VehPos[vehicleid][0], VehPos[vehicleid][1], VehPos[vehicleid][2]);
		   	SetVehicleZAngleEx(vehicleid, VehPos[vehicleid][3]);//GetVehicleZAngle(vehicleid, VehPos[vehicleid][3]);
	   	}
	   	else
	   	{//����� ��������� ��� ��� � �� ����, ������ ��� ��������� ����������� � ����������
			if(VehInfo[vehicleid][cType] >= 1000)
			{//����� �� ���������� � ����������
				/*new rand = random(sizeof(VehicleSpawns));
				VehInfo[vehicleid][cLocX] = VehicleSpawns[rand][0];
				VehInfo[vehicleid][cLocY] = VehicleSpawns[rand][1];
				VehInfo[vehicleid][cLocZ] = VehicleSpawns[rand][2];
				VehInfo[vehicleid][cAng] = VehicleSpawns[rand][3];*/
				SetVehiclePosEx(vehicleid, VehInfo[vehicleid][cLocX], VehInfo[vehicleid][cLocY], VehInfo[vehicleid][cLocZ]);
	   			SetVehicleZAngleEx(vehicleid, VehInfo[vehicleid][cAng]);//GetVehicleZAngle(vehicleid, VehInfo[vehicleid][cAng]);
			}
	   	}
   	}

	
	return 1;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//OnPlayerCheckInVehicleTimer
//stock CheckFromVehicleStateChange(playerid, vehicleid)
stock vehicle_OnPlayerStateChange(playerid, newstate, oldstate)
{   
	#pragma unused oldstate
	if(newstate != PLAYER_STATE_DRIVER) return 1;
	//==========================================================================
 	new vehicleid = nCarID[playerid];//nCarID[playerid] = GetPlayerVehicleID(playerid);//����������� � player_OnPlayerStateChange(playerid, newstate, oldstate)
	new modelid = nCarModel[playerid];//����������� � player_OnPlayerStateChange(playerid, newstate, oldstate)
	//----------------------------------------------------------------------
	//��� ������������ ����� ��������� �����
	//new temp = getdate();
	if(VehInfo[vehicleid][cDate] == getdate())
	{   //���� ��� ����� ������� �������
		new giveplayerid = ReturnUser(VehInfo[vehicleid][cOwner]);
		if(	IsPlayerConnected(giveplayerid) &&
			VehInfo[vehicleid][cOwned] > 0 &&
			//VehInfo[vehicleid][cOwned] != PlayerInfo[playerid][pSQLID]
			strcmp(VehInfo[vehicleid][cOwner], PlayerName(playerid), true))
		{   //���� ����� �� ����, � �������� �� �������, �� ��� � �� ����������
			RemovePlayerFromVehicleEx(playerid);
			return 1;
		}
	}//���������� �� ����� �� ���������, ���� ��� �� �����������*
	//----------------------------------------------------------------------
	if(modelid == 463 && IsInBikerCar(vehicleid) && !gRealWar)//��� ��������
	{
	    if(PlayerInfo[playerid][pMember] == TEAM_BIKER) { }
	    else { RemovePlayerFromVehicleEx(playerid); SendClientMessage(playerid, COLOR_GREY, "   ����� ���� ���� � ���������� ����� !"); return 1; }//�� �� ������
	}
	else if(modelid == 462)//��� ���� ����� �� ������ ���� �� ����
	{
		if(	VehInfo[vehicleid][cOwned] == 0 &&
			MyCar[playerid][0] != 0 &&
			MyCar[playerid][1] != 0 &&
			MyCar[playerid][2] != 0)
		{
			 RemovePlayerFromVehicleEx(playerid);
			 SendClientMessage(playerid, COLOR_GREY, "   � ��� ���� ������ ��������� ! ���� ��������� ��� ����������� !");
			 return 1;
		}
	}
	//----------------------------------------------------------------------
	else if(modelid == 488 || modelid == 582)//��� ����������
	{
		if(	!IsPermitToRider(playerid) &&
			PlayerInfo[playerid][pMember] != SAN)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   �� �� �������� �������� !");
		    RemovePlayerFromVehicleEx(playerid); return 1;
		}
		if( //PlayerInfo[playerid][pJob] != CARJACKER &&
			PlayerInfo[playerid][pProfSkill] < 200 && vehicleid == 96)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   ��� ����� ��������� �������� ������, �������� ���, ����� ��������� ���� ������� !");
		    RemovePlayerFromVehicleEx(playerid); return 1;
		}
	}
	//======================================================================
	if(IsInCopCar(vehicleid))//���� �� � ����������� ������
	{
	    if(	IsPermitToRider(playerid) ||
			IsACop(playerid))	{ }
	    else
		{
			RemovePlayerFromVehicleEx(playerid);
			SendClientMessage(playerid, COLOR_GREY, "   �� �� ����������� !");
			return 1;
		}
	}
	else if(IsInNGCar(vehicleid))
	{
	    if(	IsPermitToRider(playerid) ||
			PlayerInfo[playerid][pMember] == DoD)
		{
			/*new counter;
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) ) continue;
				if(PlayerInfo[i][pMember] != DoD) continue;
				if(IsPlayerInArea(i, specialzone[0])) counter ++;
			}
	        if( (modelid == 432 || modelid == 425 || modelid == 520) && counter > 2)// && PlayerInfo[playerid][pJob] != CARJACKER
	        {
		        SendClientMessage(playerid, COLOR_GREY, "   ��������� ������������ ������ ������� ��� ���-�� ������ �� ���� ������ 2 !");
		        RemovePlayerFromVehicleEx(playerid); return 1;
	        }*/

	    	//if(gOnDuty[playerid] == 1) { }
	    	//else {RemovePlayerFromVehicleEx(playerid); SendClientMessage(playerid, COLOR_GREY, "   �� - �� ��� ���������� ��������� ������������ !");}
	        if(modelid == 432 && PlayerInfo[playerid][pRank] < 7 )// && PlayerInfo[playerid][pJob] != CARJACKER
	        {
		        SendClientMessage(playerid, COLOR_GREY, "   ��� ����� ���� 7, ����� ��������� Rhino !");
		        RemovePlayerFromVehicleEx(playerid); return 1;
	        }
	        if(modelid == 425 && PlayerInfo[playerid][pRank] < 8)// && !gOnDuty[playerid] && PlayerInfo[playerid][pJob] != CARJACKER
	        {
		        SendClientMessage(playerid, COLOR_GREY, "   ��� ����� ���� 8, ����� ������ �� Hunter !");
		        RemovePlayerFromVehicleEx(playerid); return 1;
	        }
	        if(modelid == 520 && PlayerInfo[playerid][pRank] < 9)// && !gOnDuty[playerid] && PlayerInfo[playerid][pJob] != CARJACKER
	        {
		        SendClientMessage(playerid, COLOR_GREY, "   ��� ����� ���� 9, ����� ������ �� Hydra !");
		        RemovePlayerFromVehicleEx(playerid); return 1;
	        }
		}
	    else { RemovePlayerFromVehicleEx(playerid); SendClientMessage(playerid, COLOR_GREY, "   �� �� �������������� !"); return 1;}
	}
	//======================================================================
	//��������������
	//format(strings, sizeof(strings), "CheckFromVehicleStateChange(playerid:%d, vehicleid:%d)", playerid, vehicleid);
	//ABroadCast(COLOR_MAROON, strings, 9);
	return 1;
}


//##############################################################################//
//                                                                              //
//                              ��������� �������                               //
//                                                                              //
//##############################################################################//
stock LoadCarUpgrade(vehicleid)//���������� ����� �����
{   //���������� ������� �������� ��� ������ ���� ����� 25 ������
	if(vehicleid <= 0) return 1;
	if(!IsValidVehicle(vehicleid)) return 1;
	//if(VehInfo[vehicleid][cType] < 960) return 1;	//������ ��� ��������� �����

	if(VehInfo[vehicleid][cPaintjob] != 255) ChangeVehiclePaintjob(vehicleid, VehInfo[vehicleid][cPaintjob]);

	if(IsValidComponent(VehInfo[vehicleid][cSpoiler], CARMODTYPE_SPOILER)) AddVehicleComponent(vehicleid, VehInfo[vehicleid][cSpoiler]);
	if(IsValidComponent(VehInfo[vehicleid][cHood], CARMODTYPE_HOOD)) AddVehicleComponent(vehicleid, VehInfo[vehicleid][cHood]);
	if(IsValidComponent(VehInfo[vehicleid][cRoof], CARMODTYPE_ROOF)) AddVehicleComponent(vehicleid, VehInfo[vehicleid][cRoof]);
	if(IsValidComponent(VehInfo[vehicleid][cSideskirt], CARMODTYPE_SIDESKIRT)) AddVehicleComponent(vehicleid, VehInfo[vehicleid][cSideskirt]);
	if(IsValidComponent(VehInfo[vehicleid][cLamps], CARMODTYPE_LAMPS)) AddVehicleComponent(vehicleid, VehInfo[vehicleid][cLamps]);
	if(IsValidComponent(VehInfo[vehicleid][cNitro], CARMODTYPE_NITRO)) AddVehicleComponent(vehicleid, VehInfo[vehicleid][cNitro]);
	if(IsValidComponent(VehInfo[vehicleid][cExhaust], CARMODTYPE_EXHAUST)) AddVehicleComponent(vehicleid, VehInfo[vehicleid][cExhaust]);
	if(IsValidComponent(VehInfo[vehicleid][cWheels], CARMODTYPE_WHEELS)) AddVehicleComponent(vehicleid, VehInfo[vehicleid][cWheels]);
	if(IsValidComponent(VehInfo[vehicleid][cStereos], CARMODTYPE_STEREO)) AddVehicleComponent(vehicleid, VehInfo[vehicleid][cStereos]);
	if(IsValidComponent(VehInfo[vehicleid][cHydraulics], CARMODTYPE_HYDRAULICS)) AddVehicleComponent(vehicleid, VehInfo[vehicleid][cHydraulics]);
	if(IsValidComponent(VehInfo[vehicleid][cFrontBumper], CARMODTYPE_FRONT_BUMPER)) AddVehicleComponent(vehicleid, VehInfo[vehicleid][cFrontBumper]);
	if(IsValidComponent(VehInfo[vehicleid][cRearBumper], CARMODTYPE_REAR_BUMPER)) AddVehicleComponent(vehicleid, VehInfo[vehicleid][cRearBumper]);
	if(IsValidComponent(VehInfo[vehicleid][cVentRight], CARMODTYPE_VENT_RIGHT)) AddVehicleComponent(vehicleid, VehInfo[vehicleid][cVentRight]);
	if(IsValidComponent(VehInfo[vehicleid][cVentLeft], CARMODTYPE_VENT_LEFT)) AddVehicleComponent(vehicleid, VehInfo[vehicleid][cVentLeft]);

	SetVehicleHealth(vehicleid, VehInfo[vehicleid][cHealth]);

	UpdateVehicleDamageStatus(vehicleid, VehInfo[vehicleid][DamagePanels],
				VehInfo[vehicleid][DamageDoors], VehInfo[vehicleid][DamageLights],
				VehInfo[vehicleid][DamageTires]);//�������� ����������� ����������

	SetVehicleParams(vehicleid,//������������� ������� �� ������� CarStatus, �.�. ����������� ���� ����� �������� 0 ��� ��� ��� ��� ��� ����������
				CarStatus[vehicleid][st_engine],
				CarStatus[vehicleid][st_lights],
				CarStatus[vehicleid][st_alarm],
				CarStatus[vehicleid][st_doors],
				CarStatus[vehicleid][st_bonnet],
				CarStatus[vehicleid][st_boot],
				CarStatus[vehicleid][st_objective]);

//����� �������� �� ��������� �� �������� -1
/*format(strings, sizeof(strings), "2. carid: %d. engine: %d lights: %d alarm: %d doors: %d bonnet: %d boot: %d objective: %d", vehicleid,
				CarStatus[vehicleid][st_engine],
				CarStatus[vehicleid][st_lights],
				CarStatus[vehicleid][st_alarm],
				CarStatus[vehicleid][st_doors],
				CarStatus[vehicleid][st_bonnet],
				CarStatus[vehicleid][st_boot],
				CarStatus[vehicleid][st_objective]);
printf(strings);*/

	LastDriver[vehicleid] = MAX_PLAYERS-1;
	SpecialBleep[vehicleid] = 0;//������� ���������
	benzProv[vehicleid] = 0;//��� ������� ������� ��������
	StartTruckHealth[vehicleid] = 1000.0;//���������� � ���������� ��� ���������� �������� �������� �����
	return 1;
}

stock OnLockDoorsInit(playerid)//����������� �� OnPlayerSpawn
//stock car_OnPlayerSpawn(playerid)
{   //�-�� ��������� �������� ������ ����� ��� ������� ������������� ������
    if(!IsPlayerConnected(playerid) || IsPlayerNPC(playerid)) return 1;
	for(new vid=1; vid<=GetMaxVehicles; vid++)
	{
		if(VehInfo[vid][cLock] == 1 || VehInfo[vid][cLock] == 11)//��������� ��� �������� �����
		{   //���� ���� ������ - ����� �������
			SetVehicleParamsForPlayerEx(vid, playerid, 0, 1);//��������� �����, ���� ����� ������� ����������� ���������
		}
	}
	//��������������
	//////new strings[MAX_STRING];
	//format(strings, sizeof(strings), "OnLockDoorsInit(%d)", playerid);
	//ABroadCast(COLOR_MAROON, strings, 9);
	return 1;
}


stock OnCarTow(vehicleid, housekey)//���������� ������ �� ���� � ���� �� ������� /towcar
{
	if(vehicleid <= 0) return 0;
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(IsPlayerInVehicle(i, vehicleid) || HireCarID[i] == vehicleid)//Rent Car
		{   //���� � ���� ������ ��� �� ����� ��� ��� ��� ������������ �����
			//LastDriver[carid] = i;//MAX_PLAYERS-1;
			return 0;
		}
	}

	SBizInfo[8][sbTill] += SBizInfo[8][sbEntranceCost];//����������� ������ � ��� Tow Car Service
	SBizInfo[8][sbExport] += SBizInfo[8][sbEntranceCost];
	SBizInfo[8][sbProducts] --;

	VehInfo[vehicleid][cPark] = 0;
	if(housekey != NOT_KEY)
	{
		SetVehiclePosEx(vehicleid, HouseCarSpawns[housekey][0], HouseCarSpawns[housekey][1], HouseCarSpawns[housekey][2]);//����������� ������ � ����
		SetVehicleZAngleEx(vehicleid, HouseCarSpawns[housekey][3]);//���������� ��������� ����
	}
	LastDriver[vehicleid] = MAX_PLAYERS-1;
	return 1;
}

stock OnCarRespawn(vehicleid, housekey)//���������� ������ ���� ��� ��������� � ����� ����������� �� ������� /fixcar
{
	if(vehicleid <= 0) return 0;
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(IsPlayerInVehicle(i, vehicleid) || HireCarID[i] == vehicleid)//Rent Car
		{   //���� ����� ����� � ���� ������ ��� ��� ������������ �����
			//LastDriver[carid] = MAX_PLAYERS-45;//455 MAX_PLAYERS+1
			return 0;
		}
	}
	OnGangsExtortionSBiz(8, 10*SBizInfo[8][sbEntranceCost]);
	SBizInfo[8][sbProducts] --;

	RepairVehicle(vehicleid);
	VehInfo[vehicleid][cPark] = 0;

	//VehInfo[vehicleid][cFuel] = VehicleArray[GetVehicleModel(vehicleid)-400][GasMax];
	if(housekey != NOT_KEY)
	{
		SetVehiclePosEx(vehicleid, HouseCarSpawns[housekey][0], HouseCarSpawns[housekey][1], HouseCarSpawns[housekey][2]);//����������� ������ � ����
		SetVehicleZAngleEx(vehicleid, HouseCarSpawns[housekey][3]);//���������� ��������� ����
	}
	LastDriver[vehicleid] = MAX_PLAYERS-1;
	return 1;
}


//------------------------------------------------
//forward VehicleCreateEx(playerid, worldid, interiorid, modelid, Float:spawn_x,Float:spawn_y,Float:spawn_z,Float:angle_z,color1,color2,carspawntime);
stock vehicle_SpawnInfrontOfPlayer(playerid, vehiclemodel, color1, color2)
{
	new Float: x, Float:y, Float:z;
	new Float: facing;
	new Float: distance;

    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, facing);

    new Float:size_x,Float:size_y,Float:size_z;
	GetVehicleModelInfo(vehiclemodel, VEHICLE_MODEL_INFO_SIZE, size_x, size_y, size_z);//�������� ������� �����

	distance = size_x + 0.5;

  	x += (distance * floatsin(-facing, degrees));
    y += (distance * floatcos(-facing, degrees));

	facing += 90.0;
	if(facing > 360.0) facing -= 360.0;

	new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
	new str[128];
	format(str, sizeof(str), "AdmCmd: %s give %s's Vehicle %d",
		PlayerName(playerid), PlayerName(giveplayerid),	vehiclemodel);
 		//Log(ADMINLOG, str);
	//SendAllAdminMessage(COLOR_RED, strcmd, 4);
	SendClientMessage(playerid, COLOR_RED, str);

	new Float: temp_z = z + (size_z*0.25);
	new vw = PlayerInfo[playerid][pVirtual];
	new interior = CurInt[playerid];

	//new carid = VehicleCreateEx(playerid,vw,interior,vehiclemodel,x,y,temp_z,facing,color1,color2,-1);
	//new carid = CreateVehicleEx(vehiclemodel,x,y,temp_z,facing,color1,color2,-1);
	//SetVehicleVirtualWorldEx(carid, PlayerInfo[playerid][pVirtual]);
	//LinkVehicleToInteriorEx(carid, CurInt[playerid]);
	//VehInfo[carid][cOwned] = playerid;
	//strmid(VehInfo[carid][cOwner], PlayerName(playerid), 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);
	//CreatedCarCounter ++;
	//VehInfo[carid][cColor1] = color1;
	//VehInfo[carid][cColor2] = color2;
	//return carid;
	return VehicleCreateEx(playerid,vw,interior,vehiclemodel,x,y,temp_z,facing,color1,color2,-1);
}

new AdminCars[20];//������ ����������� ����� �������� veh MAX_VEHICLES-1
stock GetAdminCar(vehicleid)
{//���������� ������ � ������� ��������� �����
	if(vehicleid == 0) return -1;
	for(new c = 0; c < sizeof(AdminCars); c++)
	{
	    if(AdminCars[c] == vehicleid)
	    {
			return c;
	    }
	}
	return -1;
}



//##############################################################################//
//                                                                              //
//                             ПЕРЕГРУЖЕННЫЕ ФУНКЦИИ                            //
//                                                                              //
//##############################################################################//
//ф-ии которые на конце имеют Ex, внутри которых сразу инициализируются переменные



//ф-ия удалённого создания тачки, игрок что её вызвал хозяин тачки
forward VehicleCreateEx(playerid, worldid, interiorid, modelid, Float:spawn_x,Float:spawn_y,Float:spawn_z,Float:angle_z,color1,color2,carspawntime);
public VehicleCreateEx(playerid, worldid, interiorid, modelid, Float:spawn_x,Float:spawn_y,Float:spawn_z,Float:angle_z,color1,color2,carspawntime)
{//вызывает основную фи-ю создания тачки CreateVehicleEx
	/*if(CreatedCarCounter >= sizeof(AdminCars))
	{
		//format(strcmd, sizeof(strcmd), "Error: AdmVehicle not Spawned. %d >= %d", CreatedCarCounter, sizeof(AdminCars));
		//Log(ERROR, strcmd); //Пошлите errormsg частным образом каждому администратору
		SendClientMessage(playerid, COLOR_RED, "Error24: Достигнут предел установки машин");
		return 0;
	}*/
	new vehicleid = CreateVehicleEx(modelid,spawn_x,spawn_y,spawn_z,angle_z,color1,color2,carspawntime);
	if(vehicleid > GetMaxVehicles) GetMaxVehicles = vehicleid;
	VehInfo[vehicleid][cType] = 960 + CreatedCarCounter;
	SetVehicleVirtualWorldEx(vehicleid, worldid);
	LinkVehicleToInteriorEx(vehicleid, interiorid);

	/*for(new car = 0; car<sizeof(AdminCars); car++)
	{	//ищим свободную ячейку
	    if(AdminCars[car] != 0) continue;
		AdminCars[car] = vehicleid;//AdminCars[1] = 343,AdminCars[2] = 344
		break;
	}*/
	VehInfo[vehicleid][cOwned] = playerid;
	strmid(VehInfo[vehicleid][cOwner], PlayerName(playerid), 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);

	CreatedCarCounter ++;

	format(strings, sizeof(strings), "AdmCmd: %s has spawned VehicleID: %d (model: %d)", PlayerName(playerid), vehicleid, VehInfo[vehicleid][cModel]);
	Log(VEHLOG, strings);
	SendAllAdminMessage(COLOR_RED, strings, 4);
	return vehicleid;
}

//ф-ия инициализации массива VehInfo CarStatus
stock CreateVehicleEx(modelid, Float:spawn_x,Float:spawn_y,Float:spawn_z,Float:angle_z,color1,color2,carspawntime)
{   //вызывается из StartDerbiLS и по команде /veh
	new vehicleid = CreateVehicle(modelid,spawn_x,spawn_y,spawn_z,angle_z,color1,color2,carspawntime,0);//0 - сирена

	VehInfo[vehicleid][cModel] = modelid;
 	VehInfo[vehicleid][cLocX] = spawn_x;
 	VehInfo[vehicleid][cLocY] = spawn_y;
	VehInfo[vehicleid][cLocZ] = spawn_z;
	VehInfo[vehicleid][cAng] = angle_z;

	VehInfo[vehicleid][cPark] = 0;
	VehInfo[vehicleid][cInsur] = 0;
	VehInfo[vehicleid][cDist] = 0;//обнуляем пробег
	VehInfo[vehicleid][cFuel] = float(VehicleArray[modelid-400][GasMax]);//GasMax;
	VehInfo[vehicleid][cLoad] = 0;
	VehInfo[vehicleid][cLoadType] = 0;
	VehInfo[vehicleid][cDate] = 0;
	VehInfo[vehicleid][cColor1] = color1;
	VehInfo[vehicleid][cColor2] = color2;
	VehInfo[vehicleid][cPaintjob] = 255;
	VehInfo[vehicleid][cSpoiler] = 0;
	VehInfo[vehicleid][cHood] = 0;
	VehInfo[vehicleid][cRoof] = 0;
	VehInfo[vehicleid][cSideskirt] = 0;
	VehInfo[vehicleid][cLamps] = 0;
	VehInfo[vehicleid][cNitro] = 0;
	VehInfo[vehicleid][cExhaust] = 0;
	VehInfo[vehicleid][cWheels] = 0;
	VehInfo[vehicleid][cStereos] = 0;
	VehInfo[vehicleid][cHydraulics] = 0;
	VehInfo[vehicleid][cFrontBumper] = 0;
	VehInfo[vehicleid][cRearBumper] = 0;
	VehInfo[vehicleid][cVentRight] = 0;
	VehInfo[vehicleid][cVentLeft] = 0;
	VehInfo[vehicleid][cHealth] = 1000.0;
	VehInfo[vehicleid][DamagePanels] = 0;
	VehInfo[vehicleid][DamageDoors] = 0;
	VehInfo[vehicleid][DamageLights] = 0;
	VehInfo[vehicleid][DamageTires] = 0;

	gVehicleSpawn[vehicleid] = 1;

	CarStatus[vehicleid][st_engine] = VEHICLE_PARAMS_ON;
	CarStatus[vehicleid][st_lights] = VEHICLE_PARAMS_OFF;
	CarStatus[vehicleid][st_alarm] = VEHICLE_PARAMS_OFF;
	CarStatus[vehicleid][st_doors] = VEHICLE_PARAMS_OFF;
	CarStatus[vehicleid][st_bonnet] = VEHICLE_PARAMS_OFF;
	CarStatus[vehicleid][st_boot] = VEHICLE_PARAMS_OFF;
	CarStatus[vehicleid][st_objective] = VEHICLE_PARAMS_OFF;
	SetVehicleParams(vehicleid,//-1,
		VEHICLE_PARAMS_ON,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF);

 	VehHealth[vehicleid] = 1000.0;

	VehPos[vehicleid][0] = spawn_x;
	VehPos[vehicleid][1] = spawn_y;
	VehPos[vehicleid][2] = spawn_z;
	VehPos[vehicleid][3] = angle_z;
	return vehicleid;
}


//stock DestroyVehicleEx(vehicleid, reason)
forward DestroyVehicleEx(vehicleid, reason);//reason может быть номер ф-ии с которой происходит удаление
public DestroyVehicleEx(vehicleid, reason)//ф-ия удаления тачки с сервера и базы DialogResponse=40
{//вызывается из OnVehicleDeath, SaveCarSQL и при админских командах
	/*if(CHECKING == 3)
	{
		//ИНФОРМИРОВАНИЕ
		//////new strings[MAX_STRING];
		format(strings, sizeof(strings), "DestroyVehicleID:%d Insur:%d reason:%d", vehicleid, VehInfo[vehicleid][cInsur], reason);
		SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strings, 1);
		//Log(DEATH,strings);
	}*/
    //--------------------------------------------------------------------------
	if(vehicleid <= 0) return 1;
	//if(GetVehicleModel(vehicleid) < 400) return 1;
	if(!IsValidVehicle(vehicleid)) return 1;
/*
//для мусорщиков
	DestroyObjectEx(Trash1[vehicleid], 11);
	DestroyObjectEx(Trash2[vehicleid], 11);
	DestroyObjectEx(Box1[vehicleid], 11);
	DestroyObjectEx(Box2[vehicleid], 11);
//для дровосеков
	DestroyObjectEx(Wood1[vehicleid], 11);
	DestroyObjectEx(Wood2[vehicleid], 11);
	DestroyObjectEx(Wood3[vehicleid], 11);
*/

	//if(VehInfo[vehicleid][cType] > 0 && VehInfo[vehicleid][cType] < 950) return 1;//не удалять халявну тачки
	//но удалять купленые и дерби 8ball
    //--------------------------------------------------------------------------
	/*if(VehInfo[vehicleid][cInsur] > 0 && (getdate()-VehInfo[vehicleid][cDate]) <= DestroyDate)
	{//если кол-во страховок больше нуля и при этом время жизни тачки меньше 15
  		VehInfo[vehicleid][cInsur] -= 1;//каждый час будет отнимать страховку
  		return 1;
	}*/
    //--------------------------------------------------------------------------
	CreatedCarCounter --;
	//для удаления админских тачек
	/*if(GetAdminCar(vehicleid) != -1)
	{

		if(VehInfo[vehicleid][cOwned] > 0)
		{
			DestroyDynamic3DTextLabel(number3D[vehicleid]);
			Counter3DText --;
		}
		AdminCars[GetAdminCar(vehicleid)] = 0;
		//format(strings, sizeof(strings), "Admin Vehicle: destroyed vehicle ID:%d killer:%s[%d]", vehicleid, PlayerName(killerid), killerid);
		//Log(DEATH,strings);
		//SendAllAdminMessage(COLOR_RED, strings, 4);
	}*/
	//if(VehInfo[vehicleid][cPark] != 0) return 1;//закоментировно, т.к. при проверки даты не должны учитываться
	/*for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(	VehInfo[vehicleid][cOwned] > 0 &&
			VehInfo[vehicleid][cOwned] == PlayerInfo[i][pSQLID]	)
		{
		   if(vehicleid == MyCar[i][0]) MyCar[i][0] = 0;//освобождаем у него переменную
		   else if(vehicleid == MyCar[i][1]) MyCar[i][1] = 0;
		   else if(vehicleid == MyCar[i][2]) MyCar[i][2] = 0;
		   break;
		}
	}*/
	/*if(VehInfo[vehicleid][cOwned] > 0)
	{
		DestroyDynamic3DTextLabel(number3D[vehicleid]);
		Counter3DText --;

		//ИНФОРМИРОВАНИЕ
		//////new strings[MAX_STRING];
		if(reason != 10)
		{
			format(strings, sizeof(strings), "DestroyVehicleEx: %s[%d] date:%d[%d] Park:%d reason:%d",//Dist:%d
				VehInfo[vehicleid][cOwner], vehicleid,
				getdate(), VehInfo[vehicleid][cDate],
				VehInfo[vehicleid][cPark], //VehInfo[vehicleid][cDist],
				reason);
			//ABroadCast(COLOR_GREY, strings, 9);
			SendAllAdminMessage(COLOR_RED, strings, 1);
			Log(DEATH,strings);
		}
	}*/

	/*new ToBase[48+11];
	format(ToBase, sizeof(ToBase), "DELETE FROM `vehicles` WHERE `IND` = %d LIMIT 1", VehInfo[vehicleid][cIND]);
//printf("vehicleid: %d, VehInfo[vehicleid][cIND]: %d",vehicleid, VehInfo[vehicleid][cIND]);
	mysql_query(ToBase);*/

	DestroyVehicle(vehicleid);
	VehInfo_OnCarInit(vehicleid);
	VehiclesCounter --;
	return 1;
}



stock SetVehiclePosEx(vehicleid, Float:x, Float:y, Float:z)
{
	if(VehInfo[vehicleid][cOwned] > 0 && VehInfo[vehicleid][cType] >= 1000)
	{
		VehInfo[vehicleid][cLocX] = x;
		VehInfo[vehicleid][cLocY] = y;
		VehInfo[vehicleid][cLocZ] = z;
	}
	VehPos[vehicleid][0] = x;
	VehPos[vehicleid][1] = y;
	VehPos[vehicleid][2] = z;

	new playerid = LastDriver[vehicleid];
	CurPos[0][playerid] = x;
	CurPos[1][playerid] = y;
	CurPos[2][playerid] = z;
	//checkcheat[playerid] = CHEATLIM;

	return SetVehiclePos(vehicleid, x, y, z+0.1);
}
stock SetVehicleZAngleEx(vehicleid, Float:z_angle)
{
	if(VehInfo[vehicleid][cOwned] > 0 && VehInfo[vehicleid][cType] >= 1000)
	{
		VehInfo[vehicleid][cAng] = z_angle;
	}
	VehPos[vehicleid][3] = z_angle;
	return SetVehicleZAngle(vehicleid, z_angle);
}
stock LinkVehicleToInteriorEx(vehicleid, interiorid)
{
	if(vehicleid <= 0) return 1;
	VehInfo[vehicleid][cInt] = interiorid;
	LinkVehicleToInterior(vehicleid, interiorid);
	return 1;
}
stock SetVehicleVirtualWorldEx(vehicleid, worldid)
{
	if(vehicleid <= 0) return 1;
	VehInfo[vehicleid][cVirt] = worldid;
	SetVehicleVirtualWorld(vehicleid, worldid);
	return 1;
}
stock RepairVehicleEx(playerid, vehicleid)
{
	if(IsPlayerConnected(playerid)) LastVehHealth[playerid] = 1000.0;
    RepairVehicle(vehicleid);//чиним тачку
}
stock RepairAllCars()
{
	for(new car = 1; car<GetMaxVehicles; car++)//(MAX_VEHICLES-1)
	{
		//for(new i=0; i<GetMaxPlayers(); i++)//HighestPlayerID
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			//if( !IsPlayerConnected(i) ) continue;
	       	if(IsPlayerInVehicle(i, car) && GetPlayerState(i) == PLAYER_STATE_DRIVER)
	       	{
	       		RepairVehicleEx(i, car);
	       	}
	    }
	}
}

stock SetVehicleToRespawnEx(playerid, vehicleid)
{
	if(vehicleid <= 0) return 1;
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
       	if(IsPlayerInVehicle(i, vehicleid))
       	{
			RemovePlayerFromVehicleEx(i);
       	}
	}
	LastVehHealth[playerid] = 1000.0;
	if(vehicleid == nCarID[playerid])
	{
		if(IsTrailerAttachedToVehicle(nCarID[playerid]))
		{	//проверяет была ли машины прикреплена к трейлеру.
			DetachTrailerFromVehicleEx(nCarID[playerid]);//отсоединили прицеп
		    //GameTextForPlayerEx(playerid, "~r~Detach ~w~Trailer ~y~From Vehicle!",3000,1);//послать сообщение
			nTrailerID[playerid] = 0; nTrailerModel[playerid] = 0;
			gTrailerAttached[playerid] = 0;
		}
		nCarID[playerid] = 0; nCarModel[playerid] = 0;
	}
	else if(vehicleid == nTrailerID[playerid] )
	{
		nTrailerID[playerid] = 0; nTrailerModel[playerid] = 0;
		gTrailerAttached[playerid] = 0;
	}
	gVehicleSpawn[vehicleid] = 1;
	return SetVehicleToRespawn(vehicleid);
}



new iVehicleObjective[MAX_VEHICLES+1][MAX_PLAYERS];
stock SetVehicleParamsForPlayerEx(vehicleid, playerid, objective, doorslocked)
{
	if(vehicleid <= 0) return 1;
	SetVehicleParamsForPlayer(vehicleid, playerid, objective, doorslocked);
	iVehicleObjective[vehicleid][playerid] = objective;
	iVehicleObjective[vehicleid][MAX_PLAYERS-1] = doorslocked;	//MAX_PLAYERS-1 - константа, т.к. устанавливается для всех игроков
	return 1;
}
stock SetVehicleHealthEx(playerid, vehicleid, Float:health)
{
	if(health > 1.0)
	{
		SetPVarInt(playerid, "DetectedVehHealth", 1);
		LastVehHealth[playerid] = health;
		SetVehicleHealth(vehicleid, health);
	}
}
forward PutPlayerInVehicleEx(playerid, vehicleid, seatid);
public PutPlayerInVehicleEx(playerid, vehicleid, seatid)
//stock PutPlayerInVehicleEx(playerid, vehicleid, seatid=0)
{
	//if (vehicleid)
	if(IsValidVehicle(vehicleid))
	{
		//CheckInCar[playerid] = 2;
		new Float:cwx2,Float:cwy2,Float:cwz2;
		GetVehiclePos(vehicleid, cwx2, cwy2, cwz2);
		CurPos[0][playerid] = cwx2;
		CurPos[1][playerid] = cwy2;
		CurPos[2][playerid] = cwz2;
		//checkcheat[playerid] = CHEATLIM;
		nCarID[playerid] = vehicleid;
		nCarModel[playerid] = GetVehicleModel(vehicleid);
		return PutPlayerInVehicle(playerid, vehicleid, seatid);
	}
	return 0;
}

//stock RemovePlayerFromVehicleEx(playerid)
stock removePlayerFromVehicle(playerid)
{
	if( !IsPlayerInAnyVehicle(playerid) ) return 0;
	if(CHECKING == 3)
	{
		//////new strings[MAX_STRING];
		format(strings, sizeof(strings), "RemovePlayerFromVehicle: %d [EjectCounter:%d]", playerid, EjectCounter[playerid]);
		SendClientMessageToAll(COLOR_YELLOW, strings);
	}
	//if( GetPVarInt(playerid, "gShowDialog") != -1) return 0;
	/*new vehicleid = nCarID[playerid];
	if(PlayerInfo[playerid][pJob] == CARJACKER)
	{//не выкидывать из тачки в случаях когда тачке
		modelid = VehInfo[vehicleid][cModel];//GetVehicleModel(vid);
		if(modelid < 400) return 1;
		if(VehInfo[vehicleid][cPark] == 0) return 1;//не запаркована
		if(VehInfo[vehicleid][cType] >= 1000) return 1;//не халявная
		//if(GetVehicleSpeed(vehicleid) == 0) return 1;//не в движении
		//if(VehInfo[vehicleid][cOwned] == PlayerInfo[playerid][pSQLID]) return 1;//своя
		//if(VehInfo[vehicleid][cDate] != getdate()) return 1;//куплена не сегодня
		//if(VehicleArray[modelid-400][Category] == Motorcycle && PlayerInfo[playerid][pBikeLic] == 1) return 1;//мотоциклы есть лицка
   		//if(VehicleArray[modelid-400][Category] == Airplane && PlayerInfo[playerid][pFlyLic] == 1) return 1;
		//if(VehicleArray[modelid-400][Category] == Boats && PlayerInfo[playerid][pBoatLic] == 1) return 1;
		//if(VehicleArray[modelid-400][Category] != Public_Service) return 1;
		//if(VehicleArray[modelid-400][Category] != State_Transport) return 1;//пропускаем боевой транспорт
		//if( !(modelid == 407 || modelid == 425 || modelid == 432 || modelid == 447 || modelid == 476 ||modelid == 520 || modelid == 564) ) return 1;
		return 1;
	}
	if(PlayerInfo[playerid][pMember] == DoT && gOnDuty[playerid]) return 1;*/

	//CrashDetected[playerid] = 53;

	RemovePlayerFromVehicle(playerid);//Эта функция выкидывает игрока из транспортного средства
	EjectCounter[playerid] ++;//для PlayerCheckInCarTimer(playerid, vehicleid) --> OnPlayerCheckInVehicleTimer

	GetPlayerPos(playerid,
		CurPos[0][playerid],
		CurPos[1][playerid],
		CurPos[2][playerid]);
	checkcheat[playerid] = CHEATLIM;
	return 1;
}

/*
    Высадить игрока из указанного транспортного средства:
    Вернет false - если указанный игрок не сидит в машине
    Вернет true - если все прошло успешно
*/
stock RemovePlayerFromVehicleEx(playerid)
//stock removePlayerFromVehicle(playerid)
{
    if( !IsPlayerInAnyVehicle(playerid) ) return 0;
    new vehicleid = GetPlayerVehicleID(playerid);
    if( vehicleid == INVALID_VEHICLE_ID ) return 0;

    new Float: pos[4], Float: sideAngle;
    GetVehiclePos(vehicleid, pos[0], pos[1], pos[2]);
    GetVehicleZAngle(vehicleid, pos[3]);
    switch( GetPlayerVehicleSeat(playerid) )
    {
        case 0,2: sideAngle = pos[3] - 180.0;
        default: sideAngle = pos[3];
    }
	new Float:plocx = pos[0] + 3.0 * floatcos( sideAngle, degrees );
    new Float:plocy = pos[1] + 3.0 * floatsin( sideAngle, degrees );
    new Float:plocz = pos[2] + 0.3;
    SetPlayerPosEx( playerid, plocx,plocy,plocz, pos[3]);
    return 1;
}

/*
    Высадить водителя из указанного транспортного средства:
    Вернет false - если в указанном транспорте нет водителя
    Вернет true - если все прошло успешно
*/
stock RemoveDriverFromVehicle(carid)
{
    new mp = GetMaxPlayers(), driver=-1;
    for(new playerid; playerid < mp; playerid++)
    {   //находим игрока за рулём
        if(!IsPlayerConnected(playerid)) continue;
        if(GetPlayerVehicleID(playerid) != carid) continue;
        if(GetPlayerVehicleSeat(playerid) != 0) continue;
        driver = playerid;
        break;
    }
    if(driver == -1) return 0; // В транспорте нет водителя
    new Float:x,Float:y,Float:z,Float:a;
    GetVehiclePos(carid,x,y,z);
    GetVehicleZAngle(carid,a);
    new passenger[3] = {-1,-1,-1};    // Хватит для любого транспорта, кроме автобусов
    for(new playerid; playerid < mp; playerid++)
    {	//находим всех пассажиров
        if(!IsPlayerConnected(playerid)) continue;
        if(GetPlayerVehicleID(playerid) != carid) continue;
        if(playerid == driver) continue;
        passenger[GetPlayerVehicleSeat(playerid)-1] = playerid;
    }
    gVehicleSpawn[carid] = 1;
    SetVehicleToRespawn(carid);
    SetVehiclePos(carid,x,y,z);
    SetVehicleZAngle(carid,a);
    for(new i; i < sizeof(passenger); i++)
    {
        if(passenger[i] != -1)
        PutPlayerInVehicleEx(passenger[i],carid,i+1);
    }
    return 1;
}

stock IsValidComponent(componentid, component_slot)
{
	if(	componentid >= 1000 && componentid <= 1193 &&
	//if(	componentid > 0 && componentid <= 9999 &&
		GetVehicleComponentType(componentid) == component_slot) return 1;
	//if( GetVehicleComponentInSlot(vehicleid, GetVehicleComponentType(componentid)) != componentid ) // Check if the vehicle has no nitro
//чтобы не устанавливать нитрок, когда она уже установлена
	return 0;
}


stock SetVehicleNumberPlateEx(vehicleid, modelid)
{//вызывается из OnVehicleSpawn
	if(modelid < 400) return 0;
    if(	VehicleArray[modelid-400][Category] != Airplane &&
    	VehicleArray[modelid-400][Category] != Helicopters &&
    	VehicleArray[modelid-400][Category] != Rail_Transport &&
    	VehicleArray[modelid-400][Category] != RC_Vehicles &&
    	VehicleArray[modelid-400][Category] != Trailers &&
    	VehicleArray[modelid-400][Category] != Bicycle &&
    	//VehicleArray[modelid-400][Category] != Scooter &&
		VehicleArray[modelid-400][Category] != Boats &&
    	VehicleArray[modelid-400][Category] != Motorcycle)
	{   //modelid == 463 - харлей
		new sign[3];
		new ZONEID;
		new Float:cx,Float:cy,Float:cz;
		GetVehiclePos(vehicleid, cx, cy, cz);
		for(new j=0; j<MAX_ZONES; j++)
		{
			if(IsPointInZone(cx, cy, cz, j))//если координаты машины находятся в координатах по строке j из массива zones
			{
				ZONEID = j;//strmid(city, zones[j][zone_name], 0, strlen(zones[j][zone_name]), 255);//Извлекает диапазон символов из строки.
			}
		}
	    switch(ZONEID)//zones[j][zone_id]
		{
	        case 0: sign = "LS";
	        case 1: sign = "FC";
			case 2: sign = "WS";
			case 3: sign = "SF";
			case 4: sign = "TR";
			case 5: sign = "TR";
			case 6: sign = "BC";
			case 7: sign = "LV";
			case 8: sign = "RC";
		}
		new numberplate[32];
		format(numberplate, sizeof(numberplate), "SA{000000}%03d{0080FF}%s",vehicleid,sign);//{FF0000}SA
		if( strlen(numberplate) > sizeof(numberplate) )  return 0;
		//format(numberplate, sizeof(numberplate), "%s\n{0000FF}%d",VehInfo[vehicleid][cOwner], vehicleid);
		return SetVehicleNumberPlate(vehicleid, numberplate);//Устанавливает номерной знак для данного транспортного средства.
//Эта функция не имеет внутренней проверки ошибок. Не назначайте специальные номерные знаки автомобилям без места для установки (лодки, самолеты и т. Д.),
//Так как это приведет к некоторому ненужному времени обработки на клиенте.
//Для того, чтобы изменения вступили в силу, транспортное средство должно быть повторно создано или повторно загружено.
//На каждой номерной табличке (включая встроенные цвета) есть предел 32 символа.
//Длина текста, которая может быть видна на номерной табличке, составляет от 9 до 10 символов, больше символов приведет к разделению текста.
	}
	return 0;
}


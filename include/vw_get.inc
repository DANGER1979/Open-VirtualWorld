//##############################################################################//
//                                                                              //
//                               ФУНКЦИИ ПОЛУЧЕНИЯ                              //
//                                                                              //
//##############################################################################//
//начинаются на Get


stock GetPlayerNear(playerid, wanted)//вызывается по командам /tazer /arrest
{
	new Float: maxdistance = 99999.99;
	new Float: distance;
	new PlayerID = -1;
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(i != playerid && WantedLevel[i] >= wanted)
		{   //сканируем всех у кого розыск от указанного значения и выше
			distance = GetDistanceBetweenPlayers(playerid, i);
			if(distance < maxdistance && distance != 0.00)
			//если дистанция меньше предыдущей и оба игрока в игре
			{   //сканируем всех игроков находящихся как можно ближе к playerid
				maxdistance = distance;
				PlayerID = i;
			}
		}
	}
	return PlayerID;//возвращает ID самому близкого игрока
}

stock GetPlayerInVehicle(vehicleid)
{
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnected(i)) continue;
		if( IsPlayerInVehicle(i, vehicleid)) return i;
	}
	return INVALID_PLAYER_ID;
}

stock GetSeatVehiclePlayer(vehicleid, seatid)
{   //получить ID игрока который сидит на данном месте
//не работает в одном месте с PutPlayerInVehicle, только в следующей проверке
	//foreach(Player, i)
	//for(new i=0; i<GetMaxPlayers(); i++)	{
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnected(i)) continue;// || IsPlayerNPC(i)
		if( IsPlayerInVehicle(i, vehicleid))//IsPlayerInAnyVehicle(i)
		{	//сканируем всех кто находится в данной тачке
       		if(GetPlayerVehicleSeat(i) == seatid && GetPlayerVehicleSeat(i) != -1)
       		{   //Will also return 0 if the player is not in a vehicle!
   	        	//ИНФОРМИРОВАНИЕ
				//new str[256+1];
				//format(str, sizeof(str), "GetPlayerVehicleSeat(playerid: %d) = %d", i, GetPlayerVehicleSeat(i));
				//SendClientMessageToAll(COLOR_YELLOW, str);
   	        	return i;
			}
	    }
	}
	return INVALID_PLAYER_ID;
}



stock GetDeathReason(killerid, reason)
{
	new Message[32];
	if(killerid != INVALID_PLAYER_ID)
	{
		switch(reason)
		{
			case 0: Message = "Unarmed";
			case 1: Message = "Brass Knuckles";
			case 2: Message = "Golf Club";
			case 3: Message = "Night Stick";
			case 4: Message = "Knife";
			case 5: Message = "Baseball Bat";
			case 6: Message = "Shovel";
			case 7: Message = "Pool Cue";
			case 8: Message = "Katana";
			case 9: Message = "Chainsaw";
			case 10: Message = "Dildo";
			case 11: Message = "Dildo";
			case 12: Message = "Vibrator";
			case 13: Message = "Vibrator";
			case 14: Message = "Flowers";
			case 15: Message = "Cane";
			case 22: Message = "Pistol";
			case 23: Message = "Silenced Pistol";
			case 24: Message = "Desert Eagle";
			case 25: Message = "Shotgun";
			case 26: Message = "Sawn-off Shotgun";
			case 27: Message = "Combat Shotgun";
			case 28: Message = "MAC-10";
			case 29: Message = "MP5";
			case 30: Message = "AK-47";
			case 31:
			{
				if(GetPlayerState(killerid) == PLAYER_STATE_DRIVER)
				{
					switch(GetVehicleModel(GetPlayerVehicleID(killerid)))
					{
						case 447: Message = "Sea Sparrow Machine Gun";
						default: Message = "M4";
					}
				}
				else
				{
					Message = "M4";
				}
			}
			case 32: Message = "TEC-9";
			case 33: Message = "Rifle";
			case 34: Message = "Sniper Rifle";
			case 37: Message = "Fire";
			case 38:
			{
				if(GetPlayerState(killerid) == PLAYER_STATE_DRIVER)
				{
					switch(GetVehicleModel(GetPlayerVehicleID(killerid)))
					{
						case 425: Message = "Hunter Machine Gun";
						default: Message = "Minigun";
					}
				}
				else
				{
					Message = "Minigun";
				}
			}
			case 41: Message = "Spraycan";
			case 42: Message = "Fire Extinguisher";
			case 49: Message = "Vehicle Collision";
			case 50:
			{
				if(GetPlayerState(killerid) == PLAYER_STATE_DRIVER)
				{
					switch(GetVehicleModel(GetPlayerVehicleID(killerid)))
					{
						case 417, 425, 447, 465, 469, 487, 488, 497, 501, 548, 563: Message = "Helicopter Blades";
						default: Message = "Vehicle Collision";
					}
				}
				else Message = "Vehicle Collision";
			}
			case 51:
			{
				if(GetPlayerState(killerid) == PLAYER_STATE_DRIVER)
				{
					switch(GetVehicleModel(GetPlayerVehicleID(killerid)))
					{
						case 425: Message = "Hunter Rockets";
						case 432: Message = "Rhino Turret";
						case 520: Message = "Hydra Rockets";
						default: Message = "Explosion";
					}
				}
				else
				{
					Message = "Explosion";
				}
			}
			default: Message = "Unknown";
		}
	}
	if(killerid == INVALID_PLAYER_ID)
	{
		switch (reason)
		{
			case 53: Message = "Drowned";
			case 54: Message = "Collision";
			default: Message = "Died";
		}
	}
	return Message;
}

//------------------------------------------------------------------------------
forward Float: GetDistanceBetweenPlayers(playerid, targetid);
public Float: GetDistanceBetweenPlayers(playerid, targetid)
{   //ф-ия получения растояние между игроками
	if(!IsPlayerConnected(playerid) || !IsPlayerConnected(targetid)) return 0.0;
	new Float:X, Float:Y, Float:Z;
	GetPlayerPos(targetid,X,Y,Z);
	return GetPlayerDistanceFromPoint(playerid, X, Y, Z);
}

forward Float: GetDistanceToCar(playerid, vehicleid);
public Float: GetDistanceToCar(playerid, vehicleid)
{	//возвращает растояние от игрока до машины
	new Float:X, Float:Y, Float:Z;
	GetVehiclePos(vehicleid, X, Y, Z);
	return GetPlayerDistanceFromPoint(playerid, X, Y, Z);
}


forward Float: GetDistanceBetweenPoints(Float:x1,Float:y1,Float:z1, Float:x2,Float:y2,Float:z2);
public Float:GetDistanceBetweenPoints(Float:x1,Float:y1,Float:z1, Float:x2,Float:y2,Float:z2) //By Gabriel "Larcius" Cordes
{
	//return floatsqroot( floatpower(floatsub(x1,x2),2)+floatpower(floatsub(y1,y2),2)+floatpower(floatsub(z1,z2),2) );
	return VectorSize(x1-x2, y1-y2, z1-z2);
}
/*stock Float: GetDistanceBetweenPoints(Float:x1,Float:y1,Float:z1, Float:x2,Float:y2,Float:z2)
{
    return VectorSize(x1-x2, y1-y2, z1-z2);
}*/
stock GetPointOnVector(Float:Distance, Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2, &Float:x3, &Float:y3, &Float:z3)
{//получить точку на которую смотри игрок
	x3 = x1 + Distance * (x2 - x1);
	y3 = y1 + Distance * (y2 - y1);
	z3 = z1 + Distance * (z2 - z1);
}

forward Float: GetDistanceCameraToPoint(Float:CamX,Float:CamY,Float:CamZ, Float:FrX,Float:FrY,Float:FrZ, Float:ObjX,Float:ObjY,Float:ObjZ);
public Float:GetDistanceCameraToPoint(Float:CamX,Float:CamY,Float:CamZ, Float:FrX,Float:FrY,Float:FrZ, Float:ObjX,Float:ObjY,Float:ObjZ)
{   //возвращает растояние от точки куда смотрит игрок до объекта
	// get distance from camera to target - получаем растояние от камеры до точки
	//new Float: TGTDistance = floatsqroot((CamX - ObjX)*(CamX - ObjX) + (CamY - ObjY)*(CamY - ObjY) + (CamZ - ObjZ)*(CamZ - ObjZ));
	new Float: TGTDistance = GetDistanceBetweenPoints(CamX,CamY,CamZ, ObjX,ObjY,ObjZ);

	new Float:tmpX, Float:tmpY, Float:tmpZ;
	tmpX = CamX + FrX * TGTDistance;
	tmpY = CamY + FrY * TGTDistance;
	tmpZ = CamZ + FrZ * TGTDistance;
	//ИНФОРМИРОВАНИЕ
	/*new str[256+1];
	new Float: camPos[3];
	format(str, sizeof(str), "CameraPos(%.1f): %.1f[%.1f], %.1f[%.1f], %.1f[%.1f]",
		TGTDistance,//возвращает позицию куда смотрит игрок
		tmpX, FlameArray[0][Flame_pos][0],
		tmpY, FlameArray[0][Flame_pos][1],
		tmpZ, FlameArray[0][Flame_pos][2]);
	SendClientMessageToAll(0xFFFF00FF, str);*/

	//ИНФОРМИРОВАНИЕ
	//new str[256+1];
	//format(str, sizeof(str), "DistanceCameraTargetToLocation: %.4f", GetDistanceBetweenPoints(tmpX,tmpY,tmpZ, ObjX,ObjY,ObjZ));
	//SendClientMessageToAll(0xFFFFFF, str);
	//return floatsqroot((tmpX - ObjX)*(tmpX - ObjX) + (tmpY - ObjY)*(tmpY - ObjY) + (tmpZ - ObjZ)*(tmpZ - ObjZ));
	return GetDistanceBetweenPoints(tmpX,tmpY,tmpZ, ObjX,ObjY,ObjZ);
}

stock GetXYInring(Float:X0,Float:Y0, radius, &Float:X,&Float:Y, Float:alpha)//, speed
{//получает координаты точки на дуге окружности
//X0,Y0 - координаты центра дуги
//radius - радиус дуги
//X,Y - координаты точки на дуге окружности
//alpha - угол от центра к точке
	X = X0 + ((radius+8) * floatsin(-alpha, degrees));//радиус окружности по оси X -
	//(radius+8) - больше вытянут по X(элипс)
	Y = Y0 + (radius * floatcos(-alpha, degrees));//радиус окружности по оси Y
	//new str[MAX_STRING];
	//format(str, sizeof(str), "alpha: %.1f, speed: %d", alpha, speed);
	//SendClientMessageToAll(COLOR_GREY, str);
}
//------------------------------------------------------------------------------
stock GetXYZInfront(Float:distance, Float:angle, Float:pitch, &Float:x, &Float:y, &Float:z)
{	//pitch - это угол наклона (тангаж) транспорта
    x += (distance * floatsin(-angle, degrees));
    y += (distance * floatcos(-angle, degrees));
    z += (distance * floatsin(pitch, degrees));
}
stock GetXYZInrear(Float:distance, Float:angle, Float:pitch, &Float:x, &Float:y, &Float:z)
{	//pitch - это угол наклона (тангаж) транспорта
    x -= (distance * floatsin(-angle, degrees));
    y -= (distance * floatcos(-angle, degrees));
    z -= (distance * floatsin(pitch, degrees));
}
//------------------------------------------------------------------------------
stock GetXYInFrontOfPoint(Float:distance, Float:angle, &Float:x, &Float:y)
{   //получить координаты точки на растоянии
    x += floatmul(distance, floatsin(-angle, degrees));//(distance * floatsin(-angle, degrees));
    y += floatmul(distance, floatcos(-angle, degrees));//(distance * floatcos(-angle, degrees));
/*

1221.712768,-1401.752807,23.536178
	   	new Float:X2 = 1172.2830; //1172,2830 + 92,4*sin(270+120) = 1218,483
		new Float:Y2 = -1323.3102;//-1323,3102 + 92,4*sin(270+120) = -1277,1102
		GetXYInFrontOfPoint(92.4, 270.0+120.0, X2,Y2);

1221.712768,-1262.036132,23.536178, 1221.712768,-1401.752807,23.536178
	   	new Float:X2 = 1172.2830; //1172,2830 + 92,4*sin(270-120) = 1218,483
		new Float:Y2 = -1323.3102;//-1323,3102 + 92,4*sin(270-120) = -1277,1102
		GetXYInFrontOfPoint(92.0, 270.0-120.0, X2,Y2);
		

		
 */
}
stock GetXYInrearOfPoint(Float:distance, Float:angle, &Float:x, &Float:y)
{   //получить координаты за указанной точкой
    //new Float:z, Float:angle;
 	//GetPlayerPos(playerid, x, y, z);
	//GetVehicleZAngle(LastCar[playerid], A);
    x -= (distance * floatsin(-angle, degrees));
    y -= (distance * floatcos(-angle, degrees));
}
//------------------------------------------------------------------------------
stock GetXYZInFrontOfPlayer(playerid, Float:distance, &Float:x,&Float:y,&Float:z,&Float:angle)
{//возвращает координаты и угол точки на растоянии distance от игрока
	GetPlayerPos(playerid, x, y ,z);
	if(IsPlayerInAnyVehicle(playerid)) GetVehicleZAngle(GetPlayerVehicleID(playerid),angle);
	else GetPlayerFacingAngle(playerid, angle);
	x += (distance * floatsin(-angle, degrees));
	y += (distance * floatcos(-angle, degrees));
}
stock GetXYInFrontOfVehicle(vehicleid, Float:distance, &Float:x,&Float:y,&Float:z,&Float:angle)
{   //получить координаты перед машной
 	GetVehiclePos(vehicleid, x, y, z);
	GetVehicleZAngle(vehicleid, angle);
    x += (distance * floatsin(-angle, degrees));
    y += (distance * floatcos(-angle, degrees));
}


stock GetPlayerCameraPosEx(playerid, Float: distance, &Float:rX, &Float:rY, &Float:rZ)
{   //не работает на ботов и не видно игроков которые не застримились
     new Float: camPos[6];
     GetPlayerCameraPos(playerid, camPos[3], camPos[4], camPos[5]);
     GetPlayerCameraFrontVector(playerid, camPos[0], camPos[1], camPos[2]);
     rX = camPos[3] + floatmul(camPos[0], distance);//camPos[0]*distance;
     rY = camPos[4] + floatmul(camPos[1], distance);//camPos[1]*distance;
     rZ = camPos[5] + floatmul(camPos[2], distance);//camPos[2]*distance;
}//возвращает позицию точку куда смотрит игрок


stock GetAgePlayer(const tmp[])
{   //возврашает кол-во лет в зависимости от введённой даты
	//new tmp[] = "05.04.1879";
	new arrCoords[3][5];
	split(tmp, arrCoords, '.');
	new yyyy = strval(arrCoords[0]);
	new mm = strval(arrCoords[1]);
	new dd = strval(arrCoords[2]);
	new year, month, day;
	getdate(year, month, day);
	new check = year - yyyy;
	//-----------------------------------------------------------------
	if(mm > month)//04>03
	{
	    check -= 1;//30-1=29
	}
	else if(mm == month && dd > day)//05>01
	{
	    check -= 1;//30-1=29
	}
	return check;
}
stock getDate(yday, spliter = '.')
{   //возвращает дату ввиде строки
	new day, month, year;
	getdate(year, _, _);
	switch(yday)
	{
	    case 1..31:
		{
			day = yday;
			month = 1;
  		}
  		case 32..59:
		{
			day = yday-31;
			month = 2;
		}
  		case 60..90:
		{
			day = yday-31-28;
			month = 3;
		}
  		case 91..120:
		{
			day = yday-31-28-31;
			month = 4;
		}
  		case 121..151:
		{
			day = yday-31-28-31-30;
			month = 5;
		}
  		case 152..181:
		{
			day = yday-31-28-31-30-31;
			month = 6;
		}
  		case 182..212:
		{
			day = yday-31-28-31-30-31-30;
			month = 7;
		}
  		case 213..243:
		{
			day = yday-31-28-31-30-31-30-31;
			month = 8;
		}
  		case 244..273:
		{
			day = yday-31-28-31-30-31-30-31-31;
			month = 9;
		}
  		case 274..304:
		{
			day = yday-31-28-31-30-31-30-31-31-30;
			month = 10;
		}
  		case 305..334:
		{
			day = yday-31-28-31-30-31-30-31-31-30-31;
			month = 11;
		}
  		case 335..365:
		{
			day = yday-31-28-31-30-31-30-31-31-30-31-30;
			month = 12;
		}
	}
	new fDate[27+1];//17+2+1+2+1+4 = 27
	format(fDate, sizeof(fDate), "%02d%c%02d%c%04d", day, spliter, month, spliter, year);
    return (fDate);
}

stock GetDistanceCarToPoint(vehicleid, Float:X, Float:Y, Float:Z)//для антирадара
{   //возвращает растояние от тачки до точки
	return floatround(GetVehicleDistanceFromPoint(vehicleid, X, Y, Z));
}
stock GetPlayerSpeed(playerid)
{
    new Float: v[3];
    GetPlayerVelocity(playerid, v[0], v[1], v[2]);
	return 	floatround
			(
				floatsqroot
				(
					floatpower(v[0]*100.0,2) +
					floatpower(v[1]*100.0,2) +
					floatpower(v[2]*100.0,2)
				), floatround_floor//округляем в нижнее значение
			);
}
stock GetPlayerSpeedXY(playerid)
{
    new Float: v[3];
    GetPlayerVelocity(playerid, v[0], v[1], v[2]);
	return 	floatround
			(
				floatsqroot(
					floatpower(v[0]*100.0,2) +	floatpower(v[1]*100.0,2)
				), floatround_floor//округляем в нижнее значение
			);
}
/*Узнает для транспорта его текущую моментальную скорость в м/ч.
  vehicleid    игровой ИД транспорта
  Вернет скорость в М/Ч.*/
stock GetVehicleSpeed(vehicleid)
{
	new Float: v[3];
	GetVehicleVelocity(vehicleid, v[0], v[1], v[2]);
	return 	floatround( 100.0 * floatsqroot(
			floatpower(v[0],2) +
			floatpower(v[1],2) +
			floatpower(v[2],2)),
			floatround_floor);//округляем в нижнее значение
}
stock GetVehicleSpeedXY(vehicleid)
{
	new Float: v[3];
	GetVehicleVelocity(vehicleid, v[0], v[1], v[2]);
	return 	floatround( 100.0 *
				floatsqroot(
					floatpower(v[0],2) + floatpower(v[1],2)
				),
			floatround_floor);//округляем в нижнее значение
}

stock GetWeaponSlot(weaponid)
{
	switch(weaponid)
	{
		case 0,1: return 0;
		case 2..9: return 1;
		case 22..24: return 2;
		case 25..27: return 3;
		case 28,29,32: return 4;
		case 30,31: return 5;
		case 33,34: return 6;
		case 35,36,37,38: return 7;
		case 16..18,39: return 8;
		case 41..43: return 9;
		case 10..15: return 10;
		case 44..46: return 11;
		case 40: return 12;
	}
	return -1;
}

//GetVehicleRotation Created by IllidanS4
stock GetVehicleRotation(vehicleid,&Float:rx,&Float:ry,&Float:rz){
	new Float:qw,Float:qx,Float:qy,Float:qz;
	GetVehicleRotationQuat(vehicleid,qw,qx,qy,qz);
	rx = asin(2*qy*qz-2*qx*qw);
	ry = -atan2(qx*qz+qy*qw,0.5-qx*qx-qy*qy);
	rz = -atan2(qx*qy+qz*qw,0.5-qx*qx-qz*qz);
}

//stock GetVehicleRotation(vehicleid, &Float:heading, &Float:attitude, &Float:bank)
/*stock GetVehicleRotation(vehicleid, &Float:attitude, &Float:bank, &Float:heading)//возвращаем в более удобной форме, чтобы для объектов шло сначало rotX а потом rotY
{
//GetVehicleRotationQuat - возможно не корректно работает когда игрока нету в тачке
//Тангаж (attitude) - это вращение вокруг оси X. для объектов RotY
//Крен (bank) - вращение вокруг оси Y. для объектов RotX
//Рысканье (heading) - вращение вокруг оси Z. для объектов RotZ. Принимает значения от -180 до +180

    new Float:quat_w,Float:quat_x,Float:quat_y,Float:quat_z;
    GetVehicleRotationQuat(vehicleid,quat_w,quat_x,quat_y,quat_z);
	ConvertNonNormaQuatToEuler(quat_w,quat_x,quat_z,quat_y, heading, attitude, bank);//кай попутал местами quat_z и quat_y. Исправил.
	//attitude = -1*bank;
	bank = -1*bank;//тангаж домножил на -1, т.к. почему-то положительный тангаж определялся как отрицательный.
    return 1;
}*/

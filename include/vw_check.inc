//##############################################################################//
//                                                                              //
//                               ФУНКЦИИ ПРОВЕРКИ                               //
//                                                                              //
//##############################################################################//
//начинаются на Is Check

stock IsValidObjectModel(modelid)
{
	// Created by Y_Less.
	static modeldat[] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -128,
		-515899393, -134217729, -1, -1, 33554431, -1, -1, -1, -14337, -1, -33,
		127, 0, 0, 0, 0, 0, -8388608, -1, -1, -1, -16385, -1, -1, -1, -1, -1,
		-1, -1, -33, -1, -771751937, -1, -9, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, 33554431, -25, -1, -1, -1, -1, -1, -1,
		-1073676289, -2147483648, 34079999, 2113536, -4825600, -5, -1, -3145729,
		-1, -16777217, -63, -1, -1, -1, -1, -201326593, -1, -1, -1, -1, -1,
		-257, -1, 1073741823, -133122, -1, -1, -65, -1, -1, -1, -1, -1, -1,
		-2146435073, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1073741823, -64, -1,
		-1, -1, -1, -2635777, 134086663, 0, -64, -1, -1, -1, -1, -1, -1, -1,
		-536870927, -131069, -1, -1, -1, -1, -1, -1, -1, -1, -16384, -1,
		-33554433, -1, -1, -1, -1, -1, -1610612737, 524285, -128, -1,
		2080309247, -1, -1, -1114113, -1, -1, -1, 66977343, -524288, -1, -1, -1,
		-1, -2031617, -1, 114687, -256, -1, -4097, -1, -4097, -1, -1,
		1010827263, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -32768, -1, -1, -1, -1, -1,
		2147483647, -33554434, -1, -1, -49153, -1148191169, 2147483647,
		-100781080, -262145, -57, 134217727, -8388608, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1048577, -1, -449, -1017, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1835009, -2049, -1, -1, -1, -1, -1, -1,
		-8193, -1, -536870913, -1, -1, -1, -1, -1, -87041, -1, -1, -1, -1, -1,
		-1, -209860, -1023, -8388609, -2096897, -1, -1048577, -1, -1, -1, -1,
		-1, -1, -897, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1610612737,
		-3073, -28673, -1, -1, -1, -1537, -1, -1, -13, -1, -1, -1, -1, -1985,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1056964609, -1, -1, -1,
		-1, -1, -1, -1, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-236716037, -1, -1, -1, -1, -1, -1, -1, -536870913, 3, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -2097153, -2109441, -1, 201326591, -4194304, -1, -1,
		-241, -1, -1, -1, -1, -1, -1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, -32768, -1, -1, -1, -2, -671096835, -1, -8388609, -66323585, -13,
		-1793, -32257, -247809, -1, -1, -513, 16252911, 0, 0, 0, -131072,
		33554383, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8356095, 0, 0, 0, 0, 0,
		0, -256, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-268435449, -1, -1, -2049, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		92274627, -65536, -2097153, -268435457, 591191935, 1, 0, -16777216, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 127
	};
	if ((modelid >= 0) && ((modelid / 32) < sizeof (modeldat)) && (modeldat[modelid / 32] & (1 << (modelid % 32))))
	{
	    return 1;
	}
	return 0;
}
/*stock IsNumeric(const strNumeric[])
{
	for(new i = 0, j = strlen(strNumeric); i < j; i++)
	{
		if(strNumeric[i] > '9' || strNumeric[i] < '0') return 0;
	}
	return 1;
}*/

//Has also a fix to use "-" and "+" in the beginning of the number.
stock IsNumeric(const str[])
{
	new length = strlen(str);
	if(length == 0) return 0;
	for(new i = 0; i < length; i++)
    {
		if((str[i] > '9' || str[i] < '0' && str[i] != '-' && str[i] != '+') // Not a number,'+' or '-'
             || (str[i] == '-' && i != 0)                                             // A '-' but not at first.
             || (str[i] == '+' && i != 0)                                             // A '+' but not at first.
		   ) return 0;
    }
	if(length == 1 && (str[0] == '-' || str[0] == '+')) return 0;
	return 1;
}

/*
stock IsKeyJustDown(key, newkeys, oldkeys)
{   //возвращает верно если произошло нажатие
	if((newkeys & key) && !(oldkeys & key)) { return 1; }
	return 0;
}*/
stock IsPlayerOnLine(playerid, Float:x2,Float:y2, Float:x3,Float:y3)
{   //возвращает верно когда игрок находится на линии (x2,y2; x3,y3)
	new Float:x1, Float:y1, Float:z1;
	GetPlayerPos(playerid, x1, y1, z1);
	new Float: nCheck = (x2-x1)*(y2-y3) - (y2-y1)*(x2-x3);
//Значение nCheck = 0, если точка 1 лежит на прямой, проходящей через точки a и c.
//nCheck > 0, если точка 1 находится справа от прямой.
//nCheck < 0, если точка 1 находится слева от прямой.
	if(nCheck == 0.0) return 1;//возвращает верно если игрок на линии
	return 0;
}
stock IsVehicleOnLine(vehicleid, Float:x2,Float:y2, Float:x3,Float:y3)
{   //возвращает верно когда игрок находится на линии (x2,y2; x3,y3)
	new Float:x1, Float:y1, Float:z1;
	GetVehiclePos(vehicleid, x1, y1, z1);
	new Float: nCheck = (x2-x1)*(y2-y3) - (y2-y1)*(x2-x3);
//Значение nCheck = 0, если точка 1 лежит на прямой, проходящей через точки 2 и 3.
//nCheck > 0, если точка 1 находится справа от прямой.
//nCheck < 0, если точка 1 находится слева от прямой.
	if(nCheck == 0.0) return 1;//возвращает верно если игрок на линии
	return 0;
}

stock IsPlayerWeapon(playerid)
{
	/*new weapons[13][2];
	for (new i = 0; i <= 12; i++)
	{
	    GetPlayerWeaponData(playerid, i, weapons[i][0], weapons[i][1]);
	}*/

    new weaponID = GetPlayerWeapon(playerid);
	if(weaponID > 0 && weaponID <= 46) return 1;
	else return 0;
}
stock IsCbugWeapon(playerid)
{
    new weaponID = GetPlayerWeapon(playerid);
    if(weaponID == 22 || weaponID == 24 || weaponID == 25 || weaponID == 27)
	{
    	return 1;
	}
    return 0;
}
stock IsFireArm(weaponid)
{
	if(weaponid >= 22 && weaponid <= 38) return 1;
	else return 0;
}
stock IsACloseWeapon( weaponid )
{
	if(	/*weaponid == 9 ||//пила
		weaponid == 35 || weaponid == 36 || weaponid == 37 ||*/
		weaponid == 38||//миниган
		weaponid == 44 || weaponid == 45)//очки ночного видиния
	{
	    return 1;
	}
	return 0;
}

stock IsAtClothShop(playerid)//для магазинов одежды
{
	if(IsPlayerInRangeOfPoint(playerid, 2.1, 258.8886,-41.5371,1002.0234))
	{//раздевалка в доме
	    return 1;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 2.1, 181.4370,-88.0596,1002.0234))
	{//Zip(18)
	    return 66;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 2.1, 217.4765,-98.6483,1005.2578))
	{//Binco(int15) 
	    return 69;
	}
	if(IsPlayerInRangeOfPoint(playerid, 2.1, 214.3295,-41.4755,1002.0234))
	{//Suburban(1)
	    return 72;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 2.1, 215.7261,-155.5914,1000.5234))
	{//Didier Sachs(14)
	    return 75;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 2.1, 199.8198,-127.5023,1003.5152))
	{//ProLaps(3)
	    return 76;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 2.1, 214.4470,-7.6471,1001.2109))
	{//Victim(5)
	    return 1;
	}
	return 0;
}


stock IsAtCookPlace(playerid)//возвращает 1 если игрок в зоне кухни
{
    if(IsPlayerInRangeOfPoint(playerid, 3.0, 376.4466,-60.9574,1001.5078) || IsPlayerInRangeOfPoint(playerid, 3.0, 378.1215,-57.4928,1001.5078))
	{//Burgershot int 10
	    return 1;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 3.0, 374.1185,-113.6361,1001.4922) || IsPlayerInRangeOfPoint(playerid, 3.0, 377.7971,-113.7668,1001.4922))
	{//Well Stacked Pizza int 5
	    return 2;
	}
    else if(IsPlayerInRangeOfPoint(playerid, 3.0, 369.9786,-4.0798,1001.8589))
    {//Cluckin Bell  int 9
        return 3;
    }
	return 0;
}



stock IsAtLoadingBay(playerid)//для грузовичков продуктов
{
	if(IsPlayerInRangeOfPoint(playerid, 30.0, 2788.4929,-2436.3022,13.7721)//LOS_SANTOS
	|| IsPlayerInRangeOfPoint(playerid, 50.0, -1831.2034,1407.7167,7.3070)//SAN_FIERRO
	|| IsPlayerInRangeOfPoint(playerid, 15.0, 1087.2208,1889.5250,10.9336)//LAS_VENTURAS
	|| IsPlayerInRangeOfPoint(playerid, 30.0, -535.5635,-543.7636,25.6448))//RED_COUNTY
	{
		//GameTextForPlayerEx(playerid, "~w~Is At ~b~LoadingBay ~n~~w~(USE: ~r~/buyprods~w~)", 5000, 6);
		//PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
		return 1;
	}
	return 0;
}
stock IsAtCandyMachines(playerid)
{//конфеты
    for(new i=0; i<sizeof(CandyMachines); i++)
    {
		if(IsPlayerInRangeOfPoint(playerid, 3.0, CandyMachines[i][0],CandyMachines[i][1],CandyMachines[i][2]))
		{
			return 1;
		}
	}
	return 0;
}
stock IsAtSprunkMachines(playerid)
{//сода
    for(new i=0; i<sizeof(SprunkMachines); i++)
    {
		if(IsPlayerInRangeOfPoint(playerid, 3.0, SprunkMachines[i][0],SprunkMachines[i][1],SprunkMachines[i][2]))
		{
			return 1;
		}
	}
	return 0;
}
stock IsAtVehicleRespray(playerid)
{
    for(new i=0; i<sizeof(arVehicleRespray); i++)
    {
		if( IsPlayerInRangeOfPoint(playerid, 15.0, arVehicleRespray[i][0],arVehicleRespray[i][1],arVehicleRespray[i][2]) )
		{
			return 1;
		}
	}
	return 0;
}

//--------------------------------------------------------------------------------------------------
//отвязал проверку от ID
//СПИСОК МАШИН ПРИВЯЗАНЫХ К ID //для поиска
new IntCar[12];
new DerbyCar[10];//для дерби BloodBowl

//new TruckCar[13];
//new Trailer[25];
new RentCar[12];
new BikerCar[6];
//new Skimmer[7];


stock IsInIntCar(vehicleid)
{
	if(	vehicleid==IntCar[0] || vehicleid==IntCar[1] || vehicleid==IntCar[2] ||
		vehicleid==IntCar[3] || vehicleid==IntCar[4] || vehicleid==IntCar[5] ||
		vehicleid==IntCar[6] || vehicleid==IntCar[7] || vehicleid==IntCar[8] ||
		vehicleid==IntCar[9] || vehicleid==IntCar[10] || vehicleid==IntCar[11] ||

		vehicleid==DerbyCar[0] || vehicleid==DerbyCar[1] || vehicleid==DerbyCar[2] ||
		vehicleid==DerbyCar[3] || vehicleid==DerbyCar[4] || vehicleid==DerbyCar[5] ||
		vehicleid==DerbyCar[6] || vehicleid==DerbyCar[7] || vehicleid==DerbyCar[8] ||
		vehicleid==DerbyCar[9])
	{	return 1;	}
	return 0;
}
stock IsInDerbyCar(vehicleid)
{
	if(	vehicleid==DerbyCar[0] || vehicleid==DerbyCar[1] || vehicleid==DerbyCar[2] ||
		vehicleid==DerbyCar[3] || vehicleid==DerbyCar[4] || vehicleid==DerbyCar[5] ||
		vehicleid==DerbyCar[6] || vehicleid==DerbyCar[7] || vehicleid==DerbyCar[8] ||
		vehicleid==DerbyCar[9])
	{	return 1;	}
	return 0;
}
stock IsInRentCar(vehicleid)
{
	if(	vehicleid==RentCar[0] || vehicleid==RentCar[1] || vehicleid==RentCar[2] ||
		vehicleid==RentCar[3] || vehicleid==RentCar[4] || vehicleid==RentCar[5] ||
		vehicleid==RentCar[6] || vehicleid==RentCar[7] || vehicleid==RentCar[8] ||
		vehicleid==RentCar[9] || vehicleid==RentCar[10] || vehicleid==RentCar[11])
	{	return 1;	}
	return 0;
}
stock IsInBikerCar(vehicleid)
{
	if(	vehicleid==BikerCar[0] || vehicleid==BikerCar[1] || vehicleid==BikerCar[2] ||
		vehicleid==BikerCar[3] || vehicleid==BikerCar[4] || vehicleid==BikerCar[5])
	{	return 1;	}
	return 0;
}

//------------------------------------------------------------------------------

stock IsPlayerConnectedEx(playerid)
{
	if(playerid < 0 || playerid >= MAX_PLAYERS)
	{
		return 0;
	}
    if ( playerid & 0xFFFF0000 ) return 0;

	if( IsPlayerConnected(playerid) &&
		playerid != INVALID_PLAYER_ID &&
		!IsPlayerNPC(playerid)
		//&& gPlayerLogged[playerid] == 1
	 	// && gPlayerSpawned[playerid] == 1
		// && GetPlayerState(playerid) != PLAYER_STATE_NONE
	  )
	{
		return 1;
	}
	else { return 0; }
}

/*stock IsSeedPickup(pickupid)
{
	for(new p; p<MAX_POLE; p++)
	{
		if(pickupid == SeedPickup[p]) return 1;
	}
	return 0;
}*/


stock IsPlayerInWater(playerid)
{//возвращает верно если игрок находится вводе
	new anim_id = GetPlayerAnimationIndex(playerid);
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	if(
		((anim_id >= 1538 && anim_id <= 1544) || anim_id == 1062 || anim_id == 1250) && (z <= 0.0 || (z <= 41.0 && IsPlayerInAreaEx(playerid, -1387,-473, 2025,2824))) ||
		((anim_id >= 1538 && anim_id <= 1544) || anim_id == 1062 || anim_id == 1250) && (z <= 2.0 || (z <= 39.0 && IsPlayerInAreaEx(playerid, -1387,-473, 2025,2824)))
	  )
	{ return 1;	}
 	return 0;
}
stock IsPlayerApplyAnimation(playerid, const animation[])
{
	new anim_id = GetPlayerAnimationIndex(playerid);
    if(!anim_id) return 0;
    else
    {
        new animlib[32], animname[32];
        GetAnimationName(anim_id, animlib, sizeof(animlib), animname, sizeof(animname));
        if( !strcmp(animname, animation, true, strlen(animation)) ) return anim_id;
//strcmp((const string1[], const string2[], bool:ignorecase, length)
//string1	The first str to compare.
//string2	The second str to compare.
//ignorecase (optional)	When set to true, the case doesn't matter - HeLLo is the same as Hello. When false, they're not the same.
//length (optional)	When this length is set, the first x chars will be compared - doing "Hello" and "Hell No" with a length of 4 will say it's the same str.
//Returns
//-1 - если строка 1 находится в строке 2 раньше заявленной длины, 1 - позже.
//-1 если string1 предшествует string2
//1 если string1 приходит после string2
//0 если строки - те же (для matched длины).
//Эта функция также возвращает 0 если любая строка пустая.
    }
    return 0;
}
stock IsPlayerInRangeOfPlayer(Float:radi, playerid, targetid)
{   //возвращает верно в случаи если растояние от playerid до targetid меньше указанного
	if(!IsPlayerConnected(playerid)) return 0;
	if(!IsPlayerConnected(targetid)) return 0;
	//if(IsPlayerNPC(playerid)) return 0;
	//if(IsPlayerNPC(targetid)) return 0;
	new Float:posx, Float:posy, Float:posz;
	GetPlayerPos(targetid, posx, posy, posz);
  	if(IsPlayerInRangeOfPoint(playerid, radi, posx, posy, posz))
	{
		return 1;
	}
	return 0;
}

stock IsPointInArea(Float:x,Float:y,Float:z, Float:area[6])
{
	if(x > area[0] && x < area[3] && y > area[1] && y < area[4] && z > area[2] && z < area[5]) return 1;
	return 0;
}
//для УСТАНОВКИ КОНТРОЛЬНЫХ МЕТОК и для УСТАНОВКИ ИКОНОК НА КАРТЕ
stock IsPlayerInArea(playerid, Float:area[6])//возвращает верно каждую секунду
{   //если игрок находится в прямоугольном кубе ограниченной координатами из массива area
	if(!IsPlayerConnected(playerid)) return 0;
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	if(x > area[0] && x < area[3] && y > area[1] && y < area[4] && z > area[2] && z < area[5]) return 1;
	return 0;
}
stock IsPlayerInAreaEx(playerid, Float:x_min,Float:x_max, Float:y_min,Float:y_max)//возвращает верно каждую секунду
{   //если игрок находится в прямоугольном кубе ограниченной координатами из массива area
	if(!IsPlayerConnected(playerid)) return 0;
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	#pragma unused z
	if(x > x_min && x < x_max && y > y_min && y < y_max) return 1;
	return 0;
}

stock IsVehicleInArea(vehicleid, Float:area[6])//возвращает верно каждую секунду
{   //если игрок находится в прямоугольном кубе ограниченной координатами из массива area
	//if(	!vehicleid )	return 0;
	//if(	!GetVehicleModel(vehicleid) )	return 0;

	new Float:x, Float:y, Float:z;
	GetVehiclePos(vehicleid, x, y, z);
	if(x > area[0] && x < area[3] && y > area[1] && y < area[4] && z > area[2] && z < area[5]) return 1;
	return 0;
}
stock IsPlayerFacingToPoint(playerid, Float:X, Float:Y, Float:dOffset)
{	//dOffset - допустимый диапазон угла
	if(!IsPlayerConnected(playerid)) return 0;
	new Float:pX, Float:pY, Float:pZ, Float:pA, Float:ang;
	GetPlayerPos(playerid, pX, pY, pZ);
	GetPlayerFacingAngle(playerid, pA);

	if( pY > Y ) ang = (-acos((pX - X) / floatsqroot((pX - X)*(pX - X) + (pY - Y)*(pY - Y))) - 90.0);
	else if( pY < Y && pX < X ) ang = (acos((pX - X) / floatsqroot((pX - X)*(pX - X) + (pY - Y)*(pY - Y))) - 450.0);
	else if( pY < Y ) ang = (acos((pX - X) / floatsqroot((pX - X)*(pX - X) + (pY - Y)*(pY - Y))) - 90.0);

	if(AngleInRangeOfAngle(-ang, pA, dOffset)) return 1;
	return 0;
}


stock IsPlayerLookingAtPlayer2(playerid, forplayerid)
{   //возварщает верно (1) если игрок forplayerid находится в поле зрения игрока playerid
	//playerid Игрока, который смотрит на кого-нибудь.
	//forplayerid Игрока, который увиден.
	if( !IsPlayerConnected(playerid) )	return 0;
	if( !IsPlayerConnected(forplayerid) )	return 0;
	if(playerid == forplayerid)	return 0;

	new Float: vectorX,	Float: vectorY,	Float: vectorZ,
		Float: camPos[3],
		Float: projection[3];

	//GetPlayerCameraPos(playerid, camPos[0], camPos[1], camPos[2]);
	GetPlayerPos(playerid, camPos[0], camPos[1], camPos[2]);
	GetPlayerCameraFrontVector(playerid, vectorX, vectorY, vectorZ);

	new Float: distance = GetPlayerDistanceFromPoint(forplayerid, camPos[0], camPos[1], camPos[2]);
	projection[0] = camPos[0] + vectorX * distance;
	projection[1] = camPos[1] + vectorY * distance;
	projection[2] = camPos[2] + vectorZ * distance;

	new Float:X,Float:Y,Float:Z;
	GetPlayerPos(forplayerid, X, Y, Z);
	if( (projection[0]>(X-0.25)) && (projection[0]<(X+0.25)) &&
		(projection[1]>(Y-0.25)) && (projection[1]<(Y+0.25)) &&
		(projection[2]>(Z)) && (projection[2]<(Z+2.0)) ) return 1;
	return 0;
}

stock IsPlayerLookingAtPlayer3(playerid, forplayerid, Float:ViewWidth, Float:ViewHeight)
{
	if( !IsPlayerConnected(playerid) )	return 0;
	if( !IsPlayerConnected(forplayerid) )	return 0;
	if(playerid == forplayerid)	return 0;

	new Float:V[3], Float:VA[2], Float: C[3], Float: CA[2];

	GetPlayerCameraFrontVector(playerid,V[0],V[1],V[2]);
	GetPlayerPos(playerid,C[0],C[1],C[2]);
	//GetPlayerCameraPos(playerid, C[0],C[1],C[2]);

	C[2] += 2.0;
	for(new i = 0; i < 3; i++) { V[i] = floatadd(V[i], C[i]); }

	new Float:X,Float:Y,Float:Z;
	GetPlayerPos(forplayerid, X, Y, Z);

	CA[0] = atan2(X-C[0], Y-C[1]);
	if(CA[0] > 360.0) CA[0] = floatsub(CA[0], 360.0);
	else if(CA[0] < 0) CA[0] = floatadd(CA[0], 360.0);

	CA[1] = atan2(Y-C[1], Z-C[2]);
	if(CA[1] > 360.0) CA[1] = floatsub(CA[1], 360.0);
	else if(CA[1] < 0) CA[1] = floatadd(CA[1], 360.0);

	VA[0] = atan2(V[0]-C[0], V[1]-C[1]);
	if(VA[0] > 360.0) VA[0] = floatsub(VA[0], 360.0);
	else if(VA[0] < 0) VA[0] = floatadd(VA[0], 360.0);

	VA[1] = atan2(V[1]-C[1], V[2]-C[2]);
	if(VA[1] > 360.0) VA[1] = floatsub(VA[1], 360.0);
	else if(VA[1] < 0) VA[1] = floatadd(VA[1], 360.0);

	if(	(VA[0] > (CA[0] - ViewWidth)) &&
		(VA[0] < (CA[0] + ViewWidth)) &&
		(VA[1] > (CA[1] - ViewHeight)) &&
		(VA[1] < (CA[1] + ViewHeight))) return 1;
	if((CA[0] - ViewWidth) < 0)
	{
	    VA[0] -= 360.0;
		if(	(VA[0] > (CA[0] - ViewWidth)) &&
			(VA[0] < (CA[0] + ViewWidth)) &&
			(VA[1] > (CA[1] - ViewHeight)) &&
			(VA[1] < (CA[1] + ViewHeight))) return 1;
	}
	else if((CA[0] + ViewWidth) > 360.0)
	{
	    VA[0] += 360.0;
		if(	(VA[0] > (CA[0] - ViewWidth)) &&
			(VA[0] < (CA[0] + ViewWidth)) &&
			(VA[1] > (CA[1] - ViewHeight)) &&
			(VA[1] < (CA[1] + ViewHeight))) return 1;
	}
	return 0;
}

stock IsPlayerLookingAtVehicle(playerid, vehicleid)
{   //возварщает верно (1) если тачка vehicleid находится в поле зрения игрока playerid
//playerid 		Игрока, который смотрит на что-нибудь.
//vehicleid 	тачка, которая увидена.
	if( !IsPlayerConnected(playerid) )	return 0;
	if(	!vehicleid )	return 0;
	if(	!GetVehicleModel(vehicleid) )	return 0;

	new Float: vectorX,	Float: vectorY,	Float: vectorZ,
		Float: camPos[3],
		Float: projection[3];

	GetPlayerCameraFrontVector(playerid, vectorX, vectorY, vectorZ);
	GetPlayerCameraPos(playerid, camPos[0], camPos[1], camPos[2]);
	//GetPlayerPos(playerid, camPos[0], camPos[1], camPos[2]);

	// Looks like we need distance, damnit! This is the 3D distance since we are working in a 3D space.
	new Float: distance = GetVehicleDistanceFromPoint(vehicleid, camPos[0], camPos[1], camPos[2]);
	projection[0] = camPos[0] + vectorX * distance;
	projection[1] = camPos[1] + vectorY * distance;
	projection[2] = camPos[2] + vectorZ * distance;

	new Float:X,Float:Y,Float:Z;
	GetVehiclePos(vehicleid, X, Y, Z);
	new Float: tmpdis = floatsqroot(floatpower((projection[0]-X),2) + floatpower((projection[1]-Y),2) + floatpower((projection[2]-Z),2));
//printf("2. distance[%d]: %f[ %f ]", vehicleid, distance, tmpdis );
	if(tmpdis < (distance/10.0)) return 1;//distance/6.0 - радиус вокруг точки
	return 0;
}
stock IsPlayerLookingAtVehicle2(playerid, vehicleid)
{   //возварщает верно (1) если игрок forplayerid находится в поле зрения игрока playerid
	//playerid Игрока, который смотрит на кого-нибудь.
	//forplayerid Игрока, который увиден.
	if( !IsPlayerConnected(playerid) )	return 0;
	if(	!vehicleid )	return 0;
	if(	!GetVehicleModel(vehicleid) )	return 0;

	new Float: vectorX,	Float: vectorY,	Float: vectorZ,
		Float: camPos[3],
		Float: projection[3];

	GetPlayerCameraPos(playerid, camPos[0], camPos[1], camPos[2]);
	//GetPlayerPos(playerid, camPos[0], camPos[1], camPos[2]);
	GetPlayerCameraFrontVector(playerid, vectorX, vectorY, vectorZ);

	new Float: distance = GetVehicleDistanceFromPoint(vehicleid, camPos[0], camPos[1], camPos[2]);
	projection[0] = camPos[0] + vectorX * distance;
	projection[1] = camPos[1] + vectorY * distance;
	projection[2] = camPos[2] + vectorZ * distance;

	new Float:X,Float:Y,Float:Z;
	GetVehiclePos(vehicleid, X, Y, Z);
	if( (projection[0]>(X-0.25)) && (projection[0]<(X+0.25)) &&
		(projection[1]>(Y-0.25)) && (projection[1]<(Y+0.25)) &&
		(projection[2]>(Z)) && (projection[2]<(Z+2.0)) ) return 1;
	return 0;
}
stock IsPlayerLookingAtVehicle3(playerid, vehicleid, Float:ViewWidth, Float:ViewHeight)
{
	if( !IsPlayerConnected(playerid) )	return 0;
	if(	!vehicleid )	return 0;
	if(	!GetVehicleModel(vehicleid) )	return 0;

	new Float:V[3], Float:VA[2], Float: C[3], Float: CA[2];

	GetPlayerCameraFrontVector(playerid,V[0],V[1],V[2]);
	//GetPlayerPos(playerid,C[0],C[1],C[2]);
//printf("1. C[0]: %.1f, C[1]: %.1f, C[2]: %.1f", C[0],C[1],C[2]);
	GetPlayerCameraPos(playerid, C[0],C[1],C[2]);//GetPlayerCameraPos на +2.0 выше чем GetPlayerPos
//printf("2. C[0]: %.1f, C[1]: %.1f, C[2]: %.1f", C[0],C[1],C[2]);
	C[2] -= 1.0;//+2.0 если используем GetPlayerPos
	for(new i = 0; i < 3; i++) { V[i] = floatadd(V[i], C[i]); }

	new Float:X,Float:Y,Float:Z;
	GetVehiclePos(vehicleid, X, Y, Z);

	CA[0] = atan2(X-C[0], Y-C[1]);
	if(CA[0] > 360.0) CA[0] = floatsub(CA[0], 360.0);
	else if(CA[0] < 0) CA[0] = floatadd(CA[0], 360.0);

	CA[1] = atan2(Y-C[1], Z-C[2]);
	if(CA[1] > 360.0) CA[1] = floatsub(CA[1], 360.0);
	else if(CA[1] < 0) CA[1] = floatadd(CA[1], 360.0);

	VA[0] = atan2(V[0]-C[0], V[1]-C[1]);
	if(VA[0] > 360.0) VA[0] = floatsub(VA[0], 360.0);
	else if(VA[0] < 0) VA[0] = floatadd(VA[0], 360.0);

	VA[1] = atan2(V[1]-C[1], V[2]-C[2]);
	if(VA[1] > 360.0) VA[1] = floatsub(VA[1], 360.0);
	else if(VA[1] < 0) VA[1] = floatadd(VA[1], 360.0);

	if(	(VA[0] > (CA[0] - ViewWidth)) &&
		(VA[0] < (CA[0] + ViewWidth)) &&
		(VA[1] > (CA[1] - ViewHeight)) &&
		(VA[1] < (CA[1] + ViewHeight))) return 1;
	if((CA[0] - ViewWidth) < 0)
	{
	    VA[0] -= 360.0;
		if(	(VA[0] > (CA[0] - ViewWidth)) &&
			(VA[0] < (CA[0] + ViewWidth)) &&
			(VA[1] > (CA[1] - ViewHeight)) &&
			(VA[1] < (CA[1] + ViewHeight))) return 1;
	}
	else if((CA[0] + ViewWidth) > 360.0)
	{
	    VA[0] += 360.0;
		if(	(VA[0] > (CA[0] - ViewWidth)) &&
			(VA[0] < (CA[0] + ViewWidth)) &&
			(VA[1] > (CA[1] - ViewHeight)) &&
			(VA[1] < (CA[1] + ViewHeight))) return 1;
	}
	return 0;
}
/*
stock IsPlayerLookingAtPoint(playerid, Float:x, Float:y, Float:z)
{   //возварщает верно (1) если игрок playerid смотрит в точку
	if(!IsPlayerConnected(playerid)) return 0;
	new	Float: distance,
		Float: vectorX,	Float: vectorY,	Float: vectorZ,
		Float: camPos[2][3],
		Float: projection[3];

	//GetPlayerCameraPos(playerid, camPos[0], camPos[1], camPos[2]);
	GetPlayerPos(playerid, camPos[0][0], camPos[0][1], camPos[0][2]);
	GetPlayerCameraUpVector(playerid, camPos[1][0], camPos[1][1], camPos[1][2]);
	camPos[0][0] += camPos[1][0];
	camPos[0][1] += camPos[1][2];
	camPos[0][2] += camPos[1][2];
	GetPlayerCameraFrontVector(playerid, vectorX, vectorY, vectorZ);

	new Float: distance = GetPlayerDistanceFromPoint(forplayerid, camPos[0], camPos[1], camPos[2]);

	projection[0] = camPos[0][0] + vectorX * distance;
	projection[1] = camPos[0][1] + vectorY * distance;
	projection[2] = camPos[0][2] + vectorZ * distance;

	if( (projection[0]>(x-0.25)) && (projection[0]<(x+0.25)) &&
		(projection[1]>(y-0.25)) && (projection[1]<(y+0.25)) &&
		(projection[2]>(z)) && (projection[2]<(z+2.0)) ) return 1;
	return 0;
}

stock IsPlayerLookingAtPoint2(playerid,Float:X,Float:Y,Float:Z, Float:ViewWidth, Float:ViewHeight)
{
	new Float:c[3], Float: pa[2], Float:ca[2], Float: p[3];
	GetPlayerCameraFrontVector(playerid,V[0],V[1],V[2]);
	GetPlayerPos(playerid,C[0],C[1],C[2]);
	C[2] += 2.0;
	for(new i = 0; i < 3; i++) { c[i] = floatadd(c[i],p[i]); }

	CA[0] = atan2(X-C[0],Y-C[1]);
	if(CA[0] > 360) CA[0] = floatsub(CA[0],360);
	else if(CA[0] < 0) CA[0] = floatadd(CA[0],360);

	CA[1] = atan2(Y-C[1],Z-C[2]);
	if(CA[1] > 360) CA[1] = floatsub(CA[1],360);
	else if(CA[1] < 0) CA[1] = floatadd(CA[1],360);

	VA[0] = atan2(V[0]-C[0],V[1]-C[1]);
	if(VA[0] > 360) VA[0] = floatsub(VA[0],360);
	else if(VA[0] < 0) VA[0] = floatadd(VA[0],360);

	VA[1] = atan2(V[1]-C[1],V[2]-C[2]);
	if(VA[1] > 360) VA[1] = floatsub(VA[1],360);
	else if(VA[1] < 0) VA[1] = floatadd(VA[1],360);

	if(	(VA[0] > (CA[0]-ViewWidth)) &&
		(VA[0] < (CA[0]+ViewWidth)) &&
		(VA[1] > (CA[1]-ViewHeight)) &&
		(VA[1] < (CA[1]+ViewHeight))) return 1;
	if((CA[0] - ViewWidth) < 0)
	{
	    VA[0] -= 360.0;
		if(	(VA[0] > (CA[0]-ViewWidth)) &&
			(VA[0] < (CA[0]+ViewWidth)) &&
			(VA[1] > (CA[1]-ViewHeight)) &&
			(VA[1] < (CA[1]+ViewHeight))) return 1;
	}
	else if((CA[0] + ViewWidth) > 360)
	{
	    VA[0] += 360.0;
		if(	(VA[0] > (CA[0]-ViewWidth)) &&
			(VA[0] < (CA[0]+ViewWidth)) &&
			(VA[1] > (CA[1]-ViewHeight)) &&
			(VA[1] < (CA[1]+ViewHeight))) return 1;
	}
	return 0;
}
*/
stock IsVehicleInTriangle(playerid, vehicleid, Float:height, Float:alfa)
{
	new Float:coords[3][3];
	GetPlayerPos(playerid, coords[0][0], coords[0][1], coords[0][2]);//Вершина A
    new Float:route;//наклон треугольника
   	GetPlayerFacingAngle(playerid, route);

  	new Float:Xt, Float:Yt, Float:Zt;//искомая точка
	GetVehiclePos(vehicleid, Xt, Yt, Zt);

	new Float: c = height / floatcos((alfa/2), degrees);//сторона противоположная вершине С
	new Float: b = c;

	new Float: Angle = route + alfa/2.0;
    coords[1][0] = coords[0][0] + (c * floatsin(-Angle, degrees));//координаты вершины B
    coords[1][1] = coords[0][1] + (c * floatcos(-Angle, degrees));

	Angle = route - alfa/2.0;
    coords[2][0] = coords[0][0] + (b * floatsin(-Angle, degrees));//координаты вершины C
    coords[2][1] = coords[0][1] + (b * floatcos(-Angle, degrees));

	new Float: xnew, Float: ynew;
	new Float: xold, Float: yold;
	new Float: x1, Float: y1, Float: x2, Float: y2;
	new inside = 0;
	new npoints = sizeof(coords);
	if(npoints < 3) return 0;
	xold = coords[npoints-1][0];
	yold = coords[npoints-1][1];
	for(new i=0; i<npoints; i++)
	{
		xnew = coords[i][0];
		ynew = coords[i][1];
		if(xnew > xold)
		{
			x1 = xold; y1 = yold;
			x2 = xnew; y2 = ynew;
		}
		else
		{
			x2 = xold; y2 = yold;
			x1 = xnew; y1 = ynew;
		}
		if((xnew < Xt) == (Xt <= xold)         // edge "open" at left end
           && (Yt-y1)*(x2-x1) < (y2-y1)*(Xt-x1))
		{
			inside = !inside;
		}
		xold = xnew;
		yold = ynew;
	}
	return inside;
}
/*printf("%d",
    IsPointInPolygon(point_X, point_Y, // Here you have to fill in the coordinates of the points
				    402.31, 944.28, // (X, Y) - Polygon side A on graph
				    1011.81, 1388.28, // (X, Y) - Polygon side B on graph
				    1797.5, 1208.28, // (X, Y) - Polygon side C on graph
				    2186.37, 666.28, // (X, Y) - Polygon side D on graph
				    1718.13, 1138.28, // (X, Y) - Polygon side E on graph
				    1232.44, 1218.28, // (X, Y) - Polygon side F on graph
				    1470.52, 358.28, // (X, Y) - Polygon side G on graph
				    359.45, 228.28, // (X, Y) - Polygon side H on graph
				    1091.17, 720.28 // (X, Y) - Polygon side I on graph)
				);*/
stock IsPointInPolygon(Float: point_X, Float: point_Y, { Float, _ }: ...)
{
    #define MAX_POINT (32)

    new
        args_Total = numargs(),
        polygon_Sides = (args_Total - 2) / 2
    ;
    if((args_Total - 2) & 0b1 || MAX_POINTS <= polygon_Sides || polygon_Sides < 3)
        return 0;

    new
        Float: polygon_Data[2][MAX_POINTS],
        cross_Total
    ;
    #undef MAX_POINT

    for(new i = 2, j; i < args_Total; i += 2, ++j)
    {
        polygon_Data[0][j] = Float: getarg(i);
        polygon_Data[1][j] = Float: getarg(i + 1);
    }
    for(new i, j = polygon_Sides - 1; i < polygon_Sides; j = i, ++i)
    {
        if(polygon_Data[1][i] < point_Y && polygon_Data[1][j] >= point_Y || polygon_Data[1][j] < point_Y && polygon_Data[1][i] >= point_Y)
        {
            if(polygon_Data[0][i] + (point_Y - polygon_Data[1][i]) / (polygon_Data[1][j] - polygon_Data[1][i]) * (polygon_Data[0][j] - polygon_Data[0][i]) < point_X)
            {
                cross_Total++;
            }
        }
    }
    return cross_Total & 0b1;
}

stock IsPointInRangeOfPoint(Float:px, Float:py, Float:pz, Float:range, Float:x, Float:y, Float:z)
{	//ф-ия проверки нахождения тачки в заданном радиусе относительно указанных координат
	px -= x;   py -= y;   pz -= z;
	return ((px * px) + (py * py) + (pz * pz)) < (range * range);
}

/*stock IsVehicleInRangeOfPoint(vehicleid, Float:range, Float:x, Float:y, Float:z)
{	//ф-ия проверки нахождения тачки в заданном радиусе относительно указанных координат
	new Float:px, Float:py, Float:pz;
	GetVehiclePos(vehicleid, px, py, pz);
	px -= x;   py -= y;   pz -= z;
	return ((px * px) + (py * py) + (pz * pz)) < (range * range);
}*/
stock IsVehicleInRangeOfPoint(vehicleid,Float:range,Float:x,Float:y,Float:z)
{	//ф-ия проверки нахождения тачки в заданном радиусе относительно указанных координат
    if(vehicleid == INVALID_VEHICLE_ID) return 0;

    new Float:DistantaCar = GetVehicleDistanceFromPoint(vehicleid, x, y, z);

    if(DistantaCar <= range) return 1;
    return 0;
}



stock IsVehicleAttachedToTrailer(vehicleid)//Обнаружено длительное выполнение обратного вызова (зависание или проблема производительности)
{   //получить ID тачки прицепленной к чему либо
	//for(new carid = 1; carid<(MAX_VEHICLES-1); carid++)
	for(new carid = GetVehiclePoolSize(); carid > 0; carid--)//Gets the highest vehicleid currently in use on the server.
	//GetMaxVehicles перезаписывается при создании тачек, если тачка создана другим скриптом, то работать не будет
	{
		if(!IsValidVehicle(carid)) continue;//создано ли транспортное средство.
		if(IsTrailerAttachedToVehicle(carid))
		{   //работает правильно толко тогда, когда в тягаче сидит человек
	     	if( vehicleid == GetVehicleTrailer(carid) )
       		{
				//ИНФОРМИРОВАНИЕ
				//new str[MAX_STRING];
				//format(str, sizeof(str), "IsVehicleAttachedToTrailer(%d) - %d", vehicleid, car);
				//ABroadCast(COLOR_MAROON, str, 9);
   	        	return carid;//если данная тачка к чему то прицеплена то вернуть её ID
			}
	    }
	}
	
	/*for(new j = 0; j != -1; j = StreamedVehicle[playerid][j])
	{	//каждая ячейка массива должна быть ссылкой на индекс следующей ячейки
		if(StreamedVehicle[playerid][j] == -1) continue;
		if(index > 20) break;
		//format(strcmd, sizeof(strcmd), "StreamVeh[pl:%d][idx:%d]: %d (start: %d, count: %d)\n", playerid, j, StreamedVehicle[playerid][j], StreamVehStart[playerid], StreamVehCount[playerid]);
		format(strcmd, sizeof(strcmd), "StreamVeh[pl:%d][idx:%d]: %d (count: %d)\n", playerid, j, StreamedVehicle[playerid][j], StreamVehCount[playerid]);
		strins(dlgitem, strcmd, strlen(dlgitem));
		//printf("array[%d][%d]: %d, start: %d, count: %d", i, vid, StreamedVehicle[i][vid], start, count);
		index ++;
	}*/
	
	return 0;
}
stock IsInBike(vehicleid)//возвращает 1 если игрок за рулём вело и мотороллера на то что не требует прав
{   //запускается каждую секунду
 	new carmodelid = GetVehicleModel(vehicleid);//Узнает ID модели данного транспортного средства.
	if(	//carmodelid==448 || carmodelid==462 ||//скутеры
		carmodelid==481 || carmodelid==509 ||
		carmodelid==510 )
	{   //если модель велосипеда или мотороллера
		return 1;
	}
	return 0;
}
stock IsInBoat(vehicleid)//возвращает 1 если игрок за штурвалом лодки
{
 	new carmodelid = GetVehicleModel(vehicleid);
	if(carmodelid==430 || carmodelid==446 || carmodelid==452 || carmodelid==453 ||
		carmodelid==454 || carmodelid==472 || carmodelid==473 || carmodelid==484 ||
		carmodelid==493 || carmodelid==595)
	{  return 1; }
	return 0;
}
//IsAirVehicle
stock IsInPlane(vehicleid)//возвращает 1 если игрок за штурвалом воздушного судна
{   //запускается каждую секунду
 	new carmodelid = GetVehicleModel(vehicleid);//Узнает ID модели данного транспортного средства.
	if(	carmodelid==460 || carmodelid==476 || (carmodelid>=511)&&(carmodelid<=513) ||
		carmodelid==519 || carmodelid==520 || carmodelid==553 || carmodelid==577 ||
		carmodelid==592 || carmodelid==593 || carmodelid==417 || carmodelid==425 ||
		carmodelid==447 || carmodelid==469 || carmodelid==487 || carmodelid==488 ||
		carmodelid==497 || carmodelid==548 || carmodelid==563)//вертолёты
	{ return 1; }
	return 0;
}
stock IsInMotorcycle(vehicleid)
{   //запускается каждую секунду
 	new carmodelid = GetVehicleModel(vehicleid);
	if(	carmodelid==461 || carmodelid==463 || carmodelid==468 || carmodelid==471 ||
		carmodelid==521 || carmodelid==522 || carmodelid==523 || carmodelid==581 ||
		carmodelid==586 )
	{ return 1; }//carmodelid==523 - полицейский мотоцыкл  || carmodelid==463 - харлей
	return 0;
}
stock IsInCopCar(vehicleid)//возвращает 1 если игрок в полицейской машине
{   //проверять обязательно по модели (для {523,"HPV1000",Motorcycle,None})
 	new carmodelid = GetVehicleModel(vehicleid);//Узнает ID модели данного транспортного средства.
	if( carmodelid==427 || carmodelid==430 || carmodelid==472 || carmodelid==490 ||
		carmodelid==497 || carmodelid==523 || carmodelid==528 ||
		(carmodelid>=596)&&(carmodelid<=599) || carmodelid==601 )
	{	return 1;	}//carmodelid==523 - полицейский мотоцыкл
	return 0;
}
//в 4 разра медленная
/*stock IsInCopCar(vehicleid)//возвращает 1 если игрок в полицейской машине
{ //проверять обязательно по модели (для {523,"HPV1000",Motorcycle,None})
    new Operative[] = { 427, 430, 472, 490, 497, 523, 528, 596, 597, 598, 599, 601 };
    for(new i = 0; i < sizeof(Operative); i++)
    {
		if(GetVehicleModel(vehicleid) == Operative[i]) { return 1; }
    }
    return 0;
}*/
//для военных
stock IsInNGCar(vehicleid)//возвращает 1 если игрок в армейской машине
{
	new carmodelid = GetVehicleModel(vehicleid);//Узнает ID модели данного транспортного средства.
	if(	carmodelid==425 || carmodelid==432 || carmodelid==433 || carmodelid==470 ||
		carmodelid==520 || carmodelid==548 || carmodelid==595)
	{  //Hunter			//Rhino 			//Barracks			//Patriot 			//Hydra			//Cargobob          //Launch
		return 1;
	}
	return 0;
}
stock IsInAmbulanceCar(vehicleid)//возвращает 1 если игрок в машине Скорой помощи/Вертолёте/Самалёте
{
	new carmodelid = GetVehicleModel(vehicleid);//Узнает ID модели данного транспортного средства.
	//возращает 0 если нету такого ИД
	if(carmodelid==416 || carmodelid==447 || carmodelid==563 || carmodelid==407 || carmodelid==544) { return 1; }// || carmodelid==460
	//carmodelid==416 || carmodelid==490
	return 0;
}

stock IsInNewsCar(vehicleid)//возвращает 1 если игрок в продуктовом грузовичке
{
	new carmodelid = GetVehicleModel(vehicleid);//Узнает ID модели данного транспортного средства.
	if(carmodelid==488 || carmodelid==582) { return 1; }
	return 0;
}


stock IsTunTeleport(playerid)
{
	if(	IsPlayerInRangeOfPoint(playerid, 7.5, -1936.06,244.56,34.46) ||//SF TransFender
		IsPlayerInRangeOfPoint(playerid, 7.5, -2728.09,217.90,4.48) || //SF WhealArch
		IsPlayerInRangeOfPoint(playerid, 7.5, 2644.95,-2040.48,13.57) ||//LS LocoLow
		IsPlayerInRangeOfPoint(playerid, 7.5, 1041.52,-1024.84,32.11) ||//LS TransFender
		IsPlayerInRangeOfPoint(playerid, 7.5, 2386.37,1048.74,10.82)//LV TransFender
	  )
	{ return 1; }
	return 0;
}



stock IsPlayerAimingAt(playerid, Float:radius, Float:x, Float:y, Float:z)
{   //возвращает верно если игрок смотри на точку
	new Float:cx,Float:cy,Float:cz,
		Float:fx,Float:fy,Float:fz;
	GetPlayerCameraPos(playerid, cx, cy, cz);
	GetPlayerCameraFrontVector(playerid, fx, fy, fz);
	return (radius >= DistanceCameraTargetToLocation(cx,cy,cz, fx,fy,fz, x,y,z));
}
stock IsEvenNumber(number)
{   //возвращает 1, если число четное.
	if(number%2 == 0) return 1;
	return 0;
}

stock CheckPlayerName(playerid, name[])
{//вызывается из OnPlayerInit
// скопируем 3 символа из строки RunString, начиная с 15 индекса, в начало строки strings
//не правильный код //memcpy( strings, RunString, 15 *4, 3 *4 ); // 4 = кол-во байт в одной ячейке
//memcpy (
//    strings, // это массив ячеек, в начало которого будут копироваться байты
//    RunString, // это массив ячеек, с которого будут копироваться байты (источник)
//    (15) * 4, // копировать нужно с 15-ой ячейки (с 60-го байта) массива RunString
//    (3) * 4 // скопировать нужно всего 3 ячейки (всего 12 байт)
//);
//memcpy( strings, RunString[15], 0, (3) * 4 );

	//--------------------------------------------------------------------------
	if(strlen(name) < 6 || strlen(name) >= 20)
	{
		SendClientMessage(playerid, COLOR_EMERALD, "НЕПРАВИЛЬНОЕ ИМЯ! THE WRONG NAME!");
		SendClientMessage(playerid, COLOR_EMERALD, "Пожалуйста выберите другой Name (в окне клиента) содержащее 6-20 символов(6-20 chars)");
		SendClientMessage(playerid, COLOR_EMERALD, "Используйте /quit, чтобы выйти из игры (USE: /q)");

/*format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: BAD NICKNAME!",
	PlayerName(playerid), playerid);
Log(KICK, strings);*/
	    return 0;
	}
    /*if(	strfind(name, "_", true) == -1)//Вхождение подстроки, -1 - если не найдено.
    {   //или
		if(!strcmp(name, CREATOR, true)) { }
		else
		{
			SendClientMessage(playerid, COLOR_EMERALD, "НЕПРАВИЛЬНОЕ ИМЯ! THE WRONG NAME!");
			SendClientMessage(playerid, COLOR_EMERALD, "Имя не содержит знак '_'. Пожалуйста используйте Имя_Фамилия (пример: Jon_Smith)");//Surname Given Names
			SendClientMessage(playerid, COLOR_EMERALD, "Используйте /quit, чтобы выйти из игры (USE: /q)");
		    return 0;
	    }
	}*/
	//new underscorecount = 0;//счетчик символа '_'
	//new expectinguppercase = 1;//флаг ожидания верхнего регистра
	//new expectingdowncase = 1;
	//new strings[MAX_STRING];
	for(new i=0; i<strlen(name); i++)
	{   //Turok_Xxx
		switch(name[i])
		{
			case 'A' .. 'Z': { /*expectingdowncase = 1; expectinguppercase = 1;*/ continue; }
			case 'a' .. 'z': { /*expectingdowncase = 1;*/ continue; } //если name[i] = 'a' .. 'z'
			case '_': { continue; }
			default:
			{   //если символы отличны от 'A' .. 'Z' || 'a' .. 'z'
				SendClientMessage(playerid, COLOR_EMERALD, "НЕПРАВИЛЬНОЕ ИМЯ! THE WRONG NAME!");
				SendClientMessage(playerid, COLOR_EMERALD, "Пожалуйста выберите другой Name (в окне клиента), содержащую только a-z A-Z");// [ ]
				SendClientMessage(playerid, COLOR_EMERALD, "Используйте /quit, чтобы выйти из игры (USE: /q)");
/*format(strings, sizeof(strings), "CEPBEP: %s[%d] был кикнут, причина: BAD NICKNAME!!!!!!!!",
	PlayerName(playerid), playerid);
Log(KICK, strings);*/
			    return 0;
			}
		}
/*
		if(name[i] == name[i+1] && name[i] == name[i+2])
		{
			SendClientMessage(playerid, COLOR_EMERALD, "НЕПРАВИЛЬНОЕ ИМЯ! THE WRONG NAME!");
			SendClientMessage(playerid, COLOR_EMERALD, "Ваше Name (в окне клиента) не принимается. Пожалуйста используйте Ролевое (РП) Имя (ex: Antonio_Banderas)");//Surname Given Names
			SendClientMessage(playerid, COLOR_EMERALD, "Используйте /quit, чтобы выйти из игры (USE: /q)");
		    return 0;
		}
		if(expectinguppercase == 1)
		{	//если символ '_' уже найден
			if(name[i] < 'A' || name[i] > 'Z')
			{   //следующий символ маленькая буква
				SendClientMessage(playerid, COLOR_EMERALD, "НЕПРАВИЛЬНОЕ ИМЯ! THE WRONG NAME!");
				SendClientMessage(playerid, COLOR_EMERALD, "Ошибка верхнего регистра. Caps Lock OFF. Пожалуйста используйте Имя_Фамилия (ex: Bertie_Higgins)");//Surname Given Names
				SendClientMessage(playerid, COLOR_EMERALD, "Используйте /quit, чтобы выйти из игры (USE: /q)");
				return 0;
			}
			expectinguppercase = 0;//ожидающий верхний регистр
			continue;
		}
		if(name[i] == '_')
		{
			if(underscorecount == 1)
			{   //если символ '_' уже найден
				SendClientMessage(playerid, COLOR_EMERALD, "НЕПРАВИЛЬНОЕ ИМЯ! THE WRONG NAME!");
				SendClientMessage(playerid, COLOR_EMERALD, "Name (в окне клиента) содержит больше одного знака '_'.  Пожалуйста используйте Имя_Фамилия (ex: Mylene_Farmer)");//Surname Given Names
				SendClientMessage(playerid, COLOR_EMERALD, "Используйте /quit, чтобы выйти из игры (USE: /q)");
			    return 0;
			}
			else
			{
				if(i == (strlen(name)-1))
				{  	//если символ '_' найден в конце
					SendClientMessage(playerid, COLOR_EMERALD, "НЕПРАВИЛЬНОЕ ИМЯ! THE WRONG NAME!");
					SendClientMessage(playerid, COLOR_EMERALD, "Name (в окне клиента) содержит знак '_' не в положенном месте. Пожалуйста используйте Имя_Фамилия (ex: Avril_Lavigne)");//Surname Given Names
					SendClientMessage(playerid, COLOR_EMERALD, "Используйте /quit, чтобы выйти из игры (USE: /q)");
				    return 0;
				}
				underscorecount = 1;
				expectinguppercase = 1;
			}
			continue;
		}
		if(expectingdowncase == 1)
		{	//если символ '_' уже найден
			if(name[i] < 'a' || name[i] > 'z')
			{   //если следующий символ большая буква
				SendClientMessage(playerid, COLOR_EMERALD, "НЕПРАВИЛЬНОЕ ИМЯ! THE WRONG NAME!");
				SendClientMessage(playerid, COLOR_EMERALD, "Все буквы должны быть маленькие, кроме заглавных. Пожалуйста используйте Имя_Фамилия(ex: Andru_Donnalds)");//Surname Given Names
				SendClientMessage(playerid, COLOR_EMERALD, "Используйте /quit, чтобы выйти из игры (USE: /q)");
				return 0;
			}
			expectingdowncase = 0;//ожидающий нижний регистр
			continue;
		}
*/
	}
	//--------------------------------------------------------------------------
/*
	new agree_counter, vowel_counter;
	new letter[20];
 	//создаем массив из букв в имени
	for(new i=0; i<strlen(name); i++)
	{
		strmid(letter,name,i,i+1,strlen(name));
		if(strfind(letter, "a", true) != -1 ||
		    strfind(letter, "e", true) != -1 ||
		    strfind(letter, "i", true) != -1 ||
		    strfind(letter, "o", true) != -1 ||
		    strfind(letter, "u", true) != -1 ||
		    strfind(letter, "y", true) != -1)
	    {   //если гласная
			agree_counter = 0;
			vowel_counter ++;//счётчик подряд идущих гласных
			//printf("vowel i = %d letter = %s", i, letter);
			if(vowel_counter > 3)
			{
				SendClientMessage(playerid, COLOR_EMERALD, "НЕПРАВИЛЬНОЕ ИМЯ! THE WRONG NAME!");
				SendClientMessage(playerid, COLOR_EMERALD, "Ваш Name (в окне клиента) не принимается. Пожалуйста используйте Ролевое (РП) Имя (пример: Adriano_Celentano)");//Surname Given Names
				SendClientMessage(playerid, COLOR_EMERALD, "Используйте /quit, чтобы выйти из игры (USE: /q)");
			    return 0;
			}
		}
		else if(strfind(letter, "b", true) != -1 ||
	    strfind(letter, "c", true) != -1 ||
	    strfind(letter, "d", true) != -1 ||
	    strfind(letter, "f", true) != -1 ||
	    strfind(letter, "g", true) != -1 ||
	    strfind(letter, "h", true) != -1 ||
	    strfind(letter, "j", true) != -1 ||
	    strfind(letter, "k", true) != -1 ||
	    strfind(letter, "l", true) != -1 ||
	    strfind(letter, "m", true) != -1 ||
	    strfind(letter, "n", true) != -1 ||
	    strfind(letter, "p", true) != -1 ||
	    strfind(letter, "q", true) != -1 ||
	    strfind(letter, "r", true) != -1 ||
	    strfind(letter, "s", true) != -1 ||
	    strfind(letter, "t", true) != -1 ||
	    strfind(letter, "v", true) != -1 ||
	    strfind(letter, "w", true) != -1 ||
	    strfind(letter, "x", true) != -1 ||
	    strfind(letter, "z", true) != -1)
		{	//если согласная
			vowel_counter = 0;
			agree_counter ++;//счётчик подряд идущих согласных
			//printf("agree i = %d letter = %s",i,letter);
			if(agree_counter > 3)
			{
				SendClientMessage(playerid, COLOR_EMERALD, "НЕПРАВИЛЬНОЕ ИМЯ! THE WRONG NAME!");
				SendClientMessage(playerid, COLOR_EMERALD, "Ваш Name (в окне клиента) не принимается. Пожалуйста используйте Ролевое (РП) Имя (пример: Antonio_Banderas)");//Surname Given Names
				SendClientMessage(playerid, COLOR_EMERALD, "Используйте /quit, чтобы выйти из игры (USE: /q)");
			    return 0;
			}
		}
		else
		{
			agree_counter = 0;//счётчик согласных
			vowel_counter = 0;//счётчик гласных
		}
	}
	//==========================================================================
	new FirstName[16];	new LastName[16];
    strmid(FirstName, name, 0, strfind(name, "_", true), sizeof(FirstName) );
	if(strlen(FirstName) < 3)
	{   //если длина имени меньше 3 символов
		SendClientMessage(playerid, COLOR_EMERALD, "НЕПРАВИЛЬНОЕ ИМЯ! THE WRONG NAME!");
		SendClientMessage(playerid, COLOR_EMERALD, "Пожалуйста выберите другое Имя содержащее 3-16 символа (3-16 chars)");//3-21
		SendClientMessage(playerid, COLOR_EMERALD, "Используйте /quit, чтобы выйти из игры (USE: /q)");
	    return 0;
	}
	//format(strings, sizeof(strings), "Имя %s - принято !", FirstName);
	//SendClientMessage(playerid, COLOR_SYSTEM, strings);
	//--------------------------------------------------------------------------
	strmid(LastName, name, strfind(name, "_", true)+1, strlen(name), sizeof(LastName) );
	if(strlen(LastName) < 3)
	{ 	//если длина фамилии меньше 3 символов
		SendClientMessage(playerid, COLOR_EMERALD, "НЕПРАВИЛЬНОЕ ИМЯ! THE WRONG NAME!");
		SendClientMessage(playerid, COLOR_EMERALD, "Пожалуйста выберите другую Фамилия содержащую 3-16 символа (3-16 chars)");//3-21
		SendClientMessage(playerid, COLOR_EMERALD, "Используйте /quit, чтобы выйти из игры (USE: /q)");
	    return 0;
	}
	//format(strings, sizeof(strings), "Фамилия %s - принято !", LastName);
	//SendClientMessage(playerid, COLOR_SYSTEM, strings);
	//--------------------------------------------------------------------------
	if(!strcmp(LastName, FirstName, true))
	{   //если имя равно фимилии
		SendClientMessage(playerid, COLOR_EMERALD, "НЕПРАВИЛЬНОЕ ИМЯ! THE WRONG NAME!");
		SendClientMessage(playerid, COLOR_EMERALD, "Ваше Имя НЕ должно быть таким же как Фамилия");
		SendClientMessage(playerid, COLOR_EMERALD, "Используйте /quit, чтобы выйти из игры (USE: /q)");
	    return 0;
	}
*/
	return 1;
}

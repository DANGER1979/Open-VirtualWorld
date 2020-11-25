/*======================================================================================================*
* This Weapon-Drop Include is made by Jeffry!                                                      		*
*                                                                                                       *
*                                                                                                       *
* Made in April 2011. Updated in June 2013                                                             	*
*                                                                                                       *
* Your Rights:                                                                                          *
*                                                                                                       *
* -You are allowed to modify this Include, aslong as you DO NOT remove credits or re-upload it.			*
*                                                                                                       *
* -You are NOT allowed to re-upload this Filterscript.                                                  *
* -You are NOT allowed to claim this as your own.                                                       *
* -You are NOT allowed to remove any credits.                                                           *
*                                                                                                       *
* Thank you.                                                                                            *
* Have fun. I would be happy if you give me /credits.  :D                                               *
* 			                                                                                            *
*=======================================================================================================*/
//#include <a_samp>
//для выпадения оружия

/*default_weapon_radius
35.0,//22
35.0,//23
45.0,//24
40.0,//25
35.0,//26
40.0,//27
45.0,//28
35.0,//29
70.0,//30
90.0,//31
35.0,//32
90.0,//33
200.0,//34
*/
//-------------------------Definitions that you may change---------------------------------------------------------------------------------------
#define WEAPON_RESPAWN_TIME 30          	  // Время уничтожения пикапа если не поднимется в секундах
#define WEAPON_SLOT 15          	  // кол-во слотов в массиве
new MONEY_BAG_MONEY = 500;         	 	 // -1 = выпадает столько денег, сколько есть у игрока   0 = Выпадение денег выключено   +1 = выпадает столько денег, сколько указано в константе
new MONEY_BAG_MODE = 1;            // 1 = Деньги исходят из убитого игрока  0 = Деньги исходят из сервера
new DRUG_BAG_DRUG = 0;            // -1 = выпадает столько сколько есть у игрока   0 = Выпадение выключено   +1 = выпадает столько, сколько указано в константе
new ForbiddenWeapons[]= { 38, 44, 45 };    // Здесь Вы добавляете ID оружия, которое не хотите чтобы выбрасывалось
//=============The Variables====================================================
new WeaponDrop[MAX_PLAYERS][WEAPON_SLOT];
new WeaponData[MAX_PLAYERS][15][3];//в 13 слот заносятся деньги //в 14 слот заносятся наркотики
new WeaponTimer[MAX_PLAYERS];

//stock dropweapon_GameModeExitFunc()
stock dropweapon_OnGameModeExit()
{
	for(new i=0; i<GetMaxPlayers(); i++)
	{
		OnPlayerRemovePickups(i);
		WeaponTimer[i] = -1;
	}
}

//для выпадения оружия
//forward OnPlayerRemovePickups(playerid);
//public 
//удаляет оружие как только кто то зашёл под тем же ИД
stock OnPlayerRemovePickups(playerid)//запускается сразу после выпадение оружия
{//если игрок выйдет сервера раньше чем сработает таймер, то тогда пикап не уничтожится
//для этого вызываем паблик при выходе

	//if(WeaponTimer[playerid] != -1) KillTimer(WeaponTimer[playerid]);
	//WeaponTimer[playerid] = -1;
	for(new slot=0; slot<WEAPON_SLOT; slot++)
	{
	    if(WeaponDrop[playerid][slot] != -1)
	    {
	        DestroyPickupEx(WeaponDrop[playerid][slot]);
	        WeaponDrop[playerid][slot] = -1;
	 		WeaponData[playerid][slot][0] = -1;
	    	WeaponData[playerid][slot][1] = -1;
	    	WeaponData[playerid][slot][2] = -1;
	    }
	}
	return 1;
}
stock dropweapon_OnPlayerConnect(playerid)
{//если это инициализируется раньше чем запустится таймер, то пикап не исчезнет и подобрать уже потом его нельзя будет
//т.е. если я зайду до того момент как выполнится таймер, то инициализация переменных произойдёт раньше времени
	OnPlayerRemovePickups(playerid);
	/*for(new slot=0; slot<WEAPON_SLOT; slot++)
	{
	    if(WeaponDrop[playerid][slot] != -1)
	    {//удаляем оружие, чтобы небыло конфликта
	        DestroyPickupEx(WeaponDrop[playerid][slot]);
	    }
	    WeaponDrop[playerid][slot] = -1;
	    WeaponData[playerid][slot][0] = -1;//weapon;
	    WeaponData[playerid][slot][1] = -1;//dammo;
	    WeaponData[playerid][slot][2] = -1;//world;
	}
	WeaponTimer[playerid] = -1;*/
}
stock dropweapon_OnPlayerPickUp(playerid, pickupid)
{
    new world = PlayerInfo[playerid][pVirtual];//GetPlayerVirtualWorld(playerid);
	for(new i=0; i<GetMaxPlayers(); i++)
	{
		for(new slot=0; slot<13; slot++)
		{//сканируем слоты оружия
		    if(WeaponDrop[i][slot] == pickupid && WeaponData[i][slot][2] == world)
		    {//сканируем всех игроков, ищем с таким ид пикап
		        WeaponDrop[i][slot] = -1;
		        DestroyPickupEx(pickupid);
		        GivePlayerWeaponEx(playerid, WeaponData[i][slot][0], WeaponData[i][slot][1]);
		    	WeaponData[i][slot][0] = -1;
		    	WeaponData[i][slot][1] = -1;
		    }
		}
		if(WeaponDrop[i][WEAPON_SLOT-2] == pickupid)
		{//если выпадение денег
	        WeaponDrop[i][WEAPON_SLOT-2] = -1;
	        DestroyPickupEx(pickupid);
		    GivePlayerMoneyH(fgun, playerid, WeaponData[i][WEAPON_SLOT-2][0]);
	    	WeaponData[i][WEAPON_SLOT-2][0] = -1;
	    	WeaponData[i][WEAPON_SLOT-2][1] = -1;
		}
		if(WeaponDrop[i][WEAPON_SLOT-1] == pickupid)
		{//если выпадение нарки
	        WeaponDrop[i][WEAPON_SLOT-1] = -1;
	        DestroyPickupEx(pickupid); 
		    PlayerInfo[playerid][pDrugs] += WeaponData[i][WEAPON_SLOT-1][0];
	    	WeaponData[i][WEAPON_SLOT-1][0] = -1;
	    	WeaponData[i][WEAPON_SLOT-1][1] = -1;
		}
	}
}
stock dropweapon_OnPlayerDeath(playerid)
{
	//#pragma unused killerid
	//#pragma unused reason
    OnPlayerRemovePickups(playerid);
	new Float:x, Float:y, Float:z, dropped;
	GetPlayerPos(playerid,x,y,z);
	new world = PlayerInfo[playerid][pVirtual];//GetPlayerVirtualWorld(playerid);
	for(new slot=0; slot<13; slot++)
	{
	    new weapon, ammo;
	    GetPlayerWeaponData(playerid, slot, weapon, ammo);
	    if((ammo > 0 || weapon == 1) && weapon != 0)
	    {
			new model = GetDropWeaponModel(weapon);
			if(model != -1)
			{//записываем по индексу игрока данные по оружию
	        	WeaponData[playerid][slot][0] = weapon;
	        	WeaponData[playerid][slot][1] = ammo;
	        	WeaponData[playerid][slot][2] = world;
	        	dropped ++;
			}
	    }
	}
	//--------------------------------------------------------------------------
	if(MONEY_BAG_MONEY != 0)
	{//если выпадение денег
	    if(MONEY_BAG_MONEY == -1 && GetPlayerMoneyH(playerid) > 0)
		{
			WeaponData[playerid][WEAPON_SLOT-2][0] = GetPlayerMoneyH(playerid);
			if(MONEY_BAG_MODE) GivePlayerMoneyH(fgun, playerid, -WeaponData[playerid][WEAPON_SLOT-2][0]);
			WeaponDrop[playerid][WEAPON_SLOT-2] = SetPickupEx(1550, 1, x, y, z);
			if(dropped <= 0) dropped = 1;
		}
		if(MONEY_BAG_MONEY > 0 && GetPlayerMoneyH(playerid) > 0)
		{
			WeaponData[playerid][WEAPON_SLOT-2][0] = MONEY_BAG_MONEY;
			if(MONEY_BAG_MODE) GivePlayerMoneyH(fgun, playerid, -WeaponData[playerid][WEAPON_SLOT-2][0]);
			WeaponDrop[playerid][WEAPON_SLOT-2] = SetPickupEx(1212, 1, x, y, z);
			if(dropped <= 0) dropped = 1;
		}
	}
	if(DRUG_BAG_DRUG != 0)
	{//если выпадение нарки
	    if(DRUG_BAG_DRUG == -1 && PlayerInfo[playerid][pDrugs] > 0)
		{
			WeaponData[playerid][WEAPON_SLOT-1][0] = PlayerInfo[playerid][pDrugs];
			PlayerInfo[playerid][pDrugs] = 0;
			WeaponDrop[playerid][WEAPON_SLOT-1] = SetPickupEx(1279, 1, x, y, z);
			if(dropped <= 0) dropped = 1;
		}
		if(DRUG_BAG_DRUG > 0 && PlayerInfo[playerid][pDrugs] > 0)
		{
			WeaponData[playerid][WEAPON_SLOT-1][0] = DRUG_BAG_DRUG;
			PlayerInfo[playerid][pDrugs] -= DRUG_BAG_DRUG;
			WeaponDrop[playerid][WEAPON_SLOT-1] = SetPickupEx(1279, 1, x, y, z);
			if(dropped <= 0) dropped = 1;
		}
	}
	//--------------------------------------------------------------------------
	if(dropped > 0)
	{
	    new radius;
	    if(dropped < 3) radius = 1;
		if(dropped < 6) radius = 2;             /*If you want another radius, change it here.*/
		if(dropped <= 8) radius = 3;
		if(dropped > 8) radius = 4;
		new Float:degree, Float:tmp;
		degree = 360.0 / (float(dropped));
		tmp = degree;
		//if(WeaponTimer[playerid] != -1) { KillTimer(WeaponTimer[playerid]); WeaponTimer[playerid] = -1; }
		//WeaponTimer[playerid] = SetTimerEx("OnPlayerRemovePickups", WEAPON_RESPAWN_TIME*1000, 0, "d", playerid);
	    for(new slot=0; slot<13; slot++)
		{
		    if((WeaponData[playerid][slot][1] > 0 || WeaponData[playerid][slot][0] == 1) && WeaponData[playerid][slot][0] > 0)
		    {
				new model = GetDropWeaponModel(WeaponData[playerid][slot][0]);
				if(model != -1)
				{
				    WeaponDrop[playerid][slot] = SetPickupEx(model, 1, x+(floatsin(degree, degrees)*radius), y+(floatcos(degree, degrees)*radius), z, world);
					degree = degree + tmp;
				}
		    }
		}
	}
}


stock GetDropWeaponModel(weaponid)
{
	for(new w=0; w<sizeof(ForbiddenWeapons); w++)
	{
		if(weaponid == ForbiddenWeapons[w])	return -1;
	}
	switch(weaponid)
	{
	    case 1: return 331;
	    case 2: return 333;
	    case 3: return 334;
	    case 4: return 335;
	    case 5: return 336;
	    case 6: return 337;
	    case 7: return 338;
	    case 8: return 339;
	    case 9: return 341;
	    case 10: return 321;
	    case 11: return 322;
	    case 12: return 323;
	    case 13: return 324;
	    case 14: return 325;
	    case 15: return 326;
	    case 16: return 342;
	    case 17: return 343;
	    case 18: return 344;
	    case 22: return 346;
	    case 23: return 347;
	    case 24: return 348;
	    case 25: return 349;
	    case 26: return 350;
	    case 27: return 351;
	    case 28: return 352;
	    case 29: return 353;
	    case 30: return 355;
	    case 31: return 356;
	    case 32: return 372;
	    case 33: return 357;
	    case 34: return 358;
	    case 35: return 359;
	    case 36: return 360;
	    case 37: return 361;
	    case 38: return 362;
	    case 39: return 363;
	    case 40: return 364;
	    case 41: return 365;
	    case 42: return 366;
	    case 43: return 367;
	    case 44: return 368;
	    case 45: return 369;
	    case 46: return 371;
		default: return -1;
	}
	return -1;
}
stock GetDropWeaponName(weaponid)
{
    new wName[32];
    wName="INVALID_WEAPON";
	switch(weaponid)
	{
		case 0: wName="Fist";
		case 1: wName="Brass Knuckles";
	    case 2: wName="Golf Club";
	    case 3: wName="Night Stick";
	    case 4: wName="Knife";
	    case 5: wName="Baseball Bat";
	    case 6: wName="Shovel";
	    case 7: wName="Pool Cue";
	    case 8: wName="Katana";
	    case 9: wName="Chainsaw";
	    case 10: wName="Purple Dildo";
	    case 11: wName="Small White Vibrator";
	    case 12: wName="Large White Vibrator";
	    case 13: wName="Silver Vibrator";
	    case 14: wName="Flowers";
	    case 15: wName="Cane";
		case 16: wName="Grenade";
	    case 17: wName="Tear Gas";
		case 18: wName="Molotov Cocktail";
	 	case 22: wName="9mm";
	    case 23: wName="Silenced 9mm";
	    case 24: wName="Desert Eagle";
	    case 25: wName="Shotgun";
	    case 26: wName="Sawnoff Shotgun";
	    case 27: wName="Combat Shotgun";
	    case 28: wName="Micro SMG";
	    case 29: wName="MP5";
	    case 30: wName="AK 47";
	    case 31: wName="M4";
	    case 32: wName="Tec 9";
	    case 33: wName="Country Rifle";
	    case 34: wName="Sniper Rifle";
	    case 35: wName="Rocket Launcher";
	    case 36: wName="HS Rocket Launcher";
	    case 37: wName="Flamethrower";
	    case 38: wName="Minigun";
	    case 39: wName="Satchel Charge";
	    case 40: wName="Detonator";
	    case 41: wName="Spraycan";
	    case 42: wName="Fire Extinguiser";
	    case 43: wName="Camera";
	    case 44: wName="Night Vision Goggles";
	    case 45: wName="Thermal Goggles";
	    case 46: wName="Parachute";
	    //default: wName="Unknown";
	}
	return wName;
}


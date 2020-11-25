//просто на стенах появятся объекты от выстрелов

//#define FILTERSCRIPT

// remove bullets after __ seconds
#define REMOVE_BULLET_TIME 	(30)
// use streamer (unlimited number of objects, bullets appear after about one second delay)
// remove line to disable
//#define USE_STREAMER

// max number of bullets (will throw an error if there are too many bullets creaded)
#define MAX_BULLETS			(500)

// object used for bullets. some people use 327. by default, a red pool ball is used. you can find some other small objects here: http://gta-sa-mp.de/forum/index.php?page=Objects&objPage=searchName&objSearch=ball
#define OBJECT_BULLET		(3101)//1946

//#include <a_samp>

#if defined USE_STREAMER
	#tryinclude <streamer>
#endif

new bullets_pending;

stock bullet_OnGameModeInit()//public OnFilterScriptInit()
{
	print("   vw_bullet Система отображения выстрелов 1.0 By: kadaradam");
	print("_____________________________________________");
	print(" ");
	return 1;
}

//public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
stock bullet_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	#pragma unused weaponid
	#pragma unused hittype
	#pragma unused hitid
	if(floatround(fX) == 0 && floatround(fY) == 0) return 1;
	//if(PlayerInfo[playerid][pAdmin] < 6) return 1;
	if(weaponid == 22 || weaponid == 23 || weaponid == 24)//23 - Colt 45 (Silenced)
	{
#if !defined STREAMER_TYPE_OBJECT
		if(bullets_pending > MAX_BULLETS) return SendClientMessage(playerid, -1, "Error! Too many bullets... or whatever.");
#endif

		bullets_pending++;
		new bullet;

#if defined STREAMER_TYPE_OBJECT
		bullet = CreateDynamicObject(OBJECT_BULLET, fX, fY, fZ, 0.0, 0.0, 0.0);
#else
		bullet = CreateObject(OBJECT_BULLET, fX, fY, fZ, 0.0, 0.0, 0.0);
#endif
		SetTimerEx("RemoveBullet", REMOVE_BULLET_TIME * 1000, false, "i", bullet);

		new string[128], Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2;
		GetPlayerLastShotVectors(playerid, x1, y1, z1, x2, y2, z2); //Pocetna i krajnja tacka vektora
		new Float:Distance = GetDistanceBetweenPoints(x1, y1, z1, x2, y2, z2); //Duzina vektora
		//format(string, sizeof(string), "Distance from Point no.1 to Point no.2: %f", Distance);
		format(string, sizeof(string), "Расстояние до цели: %f", Distance);
		SendClientMessage(playerid, -1, string);

/*
		new Float:x3, Float:y3, Float:z3, balls = 0, Float:BallDist;
		BallDist = 0.5;
		for(new Float:i = 0.0; i < Distance; i += BallDist)
		{
			GetPointOnVector(i, x1, y1, z1, x2, y2, z2, x3, y3, z3);
			CreatePlayerObjectEx(playerid, OBJECT_BULLET, x3, y3, z3, 0.0,0.0,0.0);
			balls++;
		}
		format(string, sizeof(string), "Balls created: %d", balls);
		SendClientMessage(playerid, -1, string);

		Distance = GetDistanceBetweenPoints(x1, y1, z1, x3, y3, z3); //Duzina vektora
		format(string, sizeof(string), "Distance from Point no.1 to Point no.3: %f", Distance);
		SendClientMessage(playerid, -1, string);
*/
	}
	return 1;
}



forward RemoveBullet(objectid);
public RemoveBullet(objectid)
{
	bullets_pending--;
	#if defined STREAMER_TYPE_OBJECT
		DestroyDynamicObject(objectid);
	#else
		DestroyObject(objectid);
	#endif
}

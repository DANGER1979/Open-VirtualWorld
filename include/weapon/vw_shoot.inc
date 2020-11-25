/*
Bullet cam by kadaradam
Feel free to edit the script, just please keep the credits.

Video:
https://www.youtube.com/watch?v=5x7flKNjCRQ

2014. 02. 11.

Камера отслеживает полёт пули
*/

#include <a_samp>
#define CAMERA_MOVE_TIME 5000
/*
BULLET_HIT_TYPE_NONE            0
BULLET_HIT_TYPE_PLAYER          1
BULLET_HIT_TYPE_VEHICLE         2
BULLET_HIT_TYPE_OBJECT          3
BULLET_HIT_TYPE_PLAYER_OBJECT   4
*/


stock shoot_OnGameModeInit()//public OnFilterScriptInit()
{
	print("   vw_shoot Система отслеживания пули из снайперки 1.0 By: kadaradam");
	print("_____________________________________________");
	print(" ");
	return 1;
}
stock shoot_OnPlayerWeaponShot(playerid, weaponid, hittype)//, hitid, Float:fX, Float:fY, Float:fZ)
//public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	/*#pragma unused hitid
	#pragma unused fX
	#pragma unused fY
	#pragma unused fZ*/
	if(	hittype == BULLET_HIT_TYPE_NONE ||
		hittype == BULLET_HIT_TYPE_PLAYER ||
		hittype == BULLET_HIT_TYPE_VEHICLE ||
		hittype == BULLET_HIT_TYPE_OBJECT ||
		hittype == BULLET_HIT_TYPE_PLAYER_OBJECT)
	{
		if(	weaponid == 34 ||//Sniper Rifle
			weaponid == 35 ||//Rocket Launcher
			weaponid == 36//HS Rocket Launcher
		  )
		{
		    SetPlayerArmedWeaponEx(playerid, 0);
		    TogglePlayerControllableEx(playerid, 0);

			new
				Float:fOPos[3],
				Float:fHPos[3],
				Float:Angle,
				Float:Speed,
				object,
				time
			;
			
		    GetPlayerLastShotVectors(playerid, fOPos[0], fOPos[1], fOPos[2], fHPos[0], fHPos[1], fHPos[2]);
		    GetPlayerFacingAngle(playerid, Angle);

			Speed = VectorSize(fOPos[0]-fHPos[0], fOPos[1]-fHPos[1], fOPos[2]-fHPos[2]) / ( CAMERA_MOVE_TIME / 1000 );//растояние / время = скорость
			
		    object = CreatePlayerObjectEx(playerid, 1636, fOPos[0], fOPos[1], fOPos[2], 0.0, 0.0, 0.0);
		    SetObjectFacePoint(playerid, object, fHPos[0], fHPos[1]);
		    MovePlayerObject(playerid, object, fHPos[0], fHPos[1], fHPos[2], Speed);
		    
		    SetTimerEx("CameraEnd", CAMERA_MOVE_TIME, false, "i", playerid);
		    SetTimerEx("SparkCreate", CAMERA_MOVE_TIME-500, false, "ifffi",  playerid, fHPos[0], fHPos[1], fHPos[2], object);

	    	fHPos[0] -= (1 * floatsin(-Angle, degrees));
	    	fHPos[1] -= (1 * floatcos(-Angle, degrees));
	    	fOPos[0] += (1 * floatsin(-Angle, degrees));
	    	fOPos[1] += (1 * floatcos(-Angle, degrees));

			time = CAMERA_MOVE_TIME + floatround(CAMERA_MOVE_TIME * 0.15, floatround_round);
			
		    InterpolateCameraPos(playerid, fOPos[0], fOPos[1], fOPos[2], fHPos[0], fHPos[1], fHPos[2], time, CAMERA_MOVE);
	    }
    }
	return 1;
}

forward CameraEnd(playerid);
public CameraEnd(playerid)
{
    SetPlayerArmedWeaponEx(playerid, 34);
    TogglePlayerControllableEx(playerid, 1);
    SetCameraBehindPlayer(playerid);
}

forward SparkCreate(playerid, Float:X, Float:Y, Float:Z, objectid);
public SparkCreate(playerid, Float:X, Float:Y, Float:Z, objectid)
{
	SetTimerEx("Spark", 100, false, "i", CreateObjectEx(18717, X, Y, Z - 1.6, 0.0, 0.0, 0.0) );
	DestroyPlayerObjectEx(playerid, objectid);
}

forward Spark(objectid);
public Spark(objectid)
{
	DestroyObjectEx(objectid);
}

stock SetObjectFacePoint(playerid, objectid, Float: X, Float: Y) // By Lorenc_ | http://forum.sa-mp.com/showpost.php?p=1456045&postcount=2563
{
    static
        Float: pX,      Float: fobjX,
        Float: pY,      Float: fobjY,
        Float: fobjZ
    ;
    GetPlayerObjectRot(playerid, objectid, fobjX, fobjY, fobjZ);
    GetPlayerObjectPos(playerid, objectid, pX, pY, fobjZ);

    fobjZ = ( floatadd(atan2(floatsub(Y, pY), floatsub(X, pX)), 270.0) );

    SetPlayerObjectRot(playerid, objectid, fobjX, fobjY, fobjZ);
}

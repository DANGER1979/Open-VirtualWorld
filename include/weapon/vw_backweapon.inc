#include <a_samp>

#define Not_usable 0
#define Spine 1
#define Head 2
#define Left_upper_arm 3
#define Right_upper_arm 4
#define Left_hand 5
#define Right_hand 6
#define Left_thigh 7
#define Right_thigh 8
#define Left_foot 9
#define Right_foot 10
#define Right_calf 11
#define Left_calf 12
#define Left_forearm 13
#define Right_forearm 14
#define Left_clavicle 15
#define Right_clavicle 16
#define Neck 17
#define Jaw 18

stock backweapon_OnGameModeInit()
{
	//--------------------------------------------------------------------------
	print("   vw_backweapon Система оружия за спиной v1.0 By: Cesar_Vialpando");
	print("_____________________________________________");
	print(" ");
	return 1;
}

stock backweapon_OnGameModeExit()
{
	for(new i = 0; i < GetMaxPlayers(); i++)
	{
		if(IsPlayerAttachedObjectSlotUsed(i,0)) RemovePlayerAttachedObject(i,0);
		if(IsPlayerAttachedObjectSlotUsed(i,1)) RemovePlayerAttachedObject(i,1);
		if(IsPlayerAttachedObjectSlotUsed(i,2)) RemovePlayerAttachedObject(i,2);
		if(IsPlayerAttachedObjectSlotUsed(i,3)) RemovePlayerAttachedObject(i,3);
		if(IsPlayerAttachedObjectSlotUsed(i,4)) RemovePlayerAttachedObject(i,4);
	}
	return 1;
}

stock backweapon_OnPlayerDisconnect(playerid)
{
	if(IsPlayerAttachedObjectSlotUsed(playerid,0)) RemovePlayerAttachedObject(playerid,0);
	if(IsPlayerAttachedObjectSlotUsed(playerid,1)) RemovePlayerAttachedObject(playerid,1);
	if(IsPlayerAttachedObjectSlotUsed(playerid,2)) RemovePlayerAttachedObject(playerid,2);
	if(IsPlayerAttachedObjectSlotUsed(playerid,3)) RemovePlayerAttachedObject(playerid,3);
	if(IsPlayerAttachedObjectSlotUsed(playerid,4)) RemovePlayerAttachedObject(playerid,4);
}

stock backweapon_OnPlayerUpdate(playerid)
{
	new weapon[7],weaponammo[7], ArmedWeapon;
	ArmedWeapon = GetPlayerWeapon(playerid);
	for(new slot = 2; slot < 7; slot++)
	{
		GetPlayerWeaponData(playerid, slot, weapon[slot], weaponammo[slot]);
	}
	if(weapon[2] && weaponammo[2] > 0)
	{
		if(ArmedWeapon == weapon[2])
		{
			if(IsPlayerAttachedObjectSlotUsed(playerid,0))
			{
				RemovePlayerAttachedObject(playerid,0);
			}
		}
		else
		{
			if(!IsPlayerAttachedObjectSlotUsed(playerid,0))
			{
				SetPlayerAttachedObject(playerid,0,GetWeaponModel(weapon[2]),Right_thigh, 0.059000,-0.028999,0.138000, -102.999954,-1.299998,2.000000, 0.990000,1.000000,1.000000);
			}
		}
	}
	if(weapon[3] && weaponammo[3] > 0)
	{
		if(ArmedWeapon == weapon[3])
		{
			if(IsPlayerAttachedObjectSlotUsed(playerid,1))
			{
				RemovePlayerAttachedObject(playerid,1);
			}
		}
		else
		{
			if(!IsPlayerAttachedObjectSlotUsed(playerid,1))
			{
				SetPlayerAttachedObject(playerid,1,GetWeaponModel(weapon[3]),Spine, 0.330000,-0.156000,0.189000, 0.000000,-171.799911,0.000000, 1.000000,1.000000,1.000000);
			}
		}
	}
	if(weapon[4] && weaponammo[4] > 0)
	{
		if(ArmedWeapon == weapon[4])
		{
			if(IsPlayerAttachedObjectSlotUsed(playerid,2))
			{
				RemovePlayerAttachedObject(playerid,2);
			}
		}
		else
		{
			if(!IsPlayerAttachedObjectSlotUsed(playerid,2))
			{
				SetPlayerAttachedObject(playerid,2,GetWeaponModel(weapon[4]),Left_thigh, 0.028000,-0.078000,-0.109999, -68.899986,7.600007,9.600001, 1.000000,1.000000,1.000000);
			}
		}
	}
	if(weapon[5] && weaponammo[5] > 0)
	{
		if(ArmedWeapon == weapon[5])
		{
			if(IsPlayerAttachedObjectSlotUsed(playerid,3))
			{
				RemovePlayerAttachedObject(playerid,3);
			}
		}
		else
		{
			if(!IsPlayerAttachedObjectSlotUsed(playerid,3))
			{
				SetPlayerAttachedObject(playerid,3,GetWeaponModel(weapon[5]),Spine, 0.148999,-0.113999,-0.171000, 177.800079,-173.200073,11.800003, 1.000000,1.000000,1.000000);
			}
		}
	}
	if(weapon[6] && weaponammo[6] > 0)
	{
		if(ArmedWeapon == weapon[6])
		{
			if(IsPlayerAttachedObjectSlotUsed(playerid,4))
			{
				RemovePlayerAttachedObject(playerid,4);
			}
		}
		else
		{
			if(!IsPlayerAttachedObjectSlotUsed(playerid,4))
			{
				SetPlayerAttachedObject(playerid,4,GetWeaponModel(weapon[6]),Spine, 0.208000,-0.149000,0.078999, -8.000002,169.599975,-0.600003, 1.000000,1.000000,1.000000);
			}
		}
	}
	return 1;
}

stock GetWeaponModel(weaponid)
{
	switch(weaponid)
	{
		case 22..29:
		    return weaponid+324;

		case 30,31:
		    return weaponid+325;

		case 32:
		    return 372;
		    
		case 33,34:
		    return weaponid+324;

		case 46:
		    return 371;
	}
	return 0;
}

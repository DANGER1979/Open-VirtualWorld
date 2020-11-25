#include <a_samp>

/*

    About: GetVehicleParamsCarDoors fix (beta)
    Author: ziggi

*/

#define FIX_GetVehicleParamsCarDoors 1

enum e_PlayerInfo
{
    e_pi_vehicle,
    e_pi_vehicle_seat,
    bool:e_pi_isdriver,
    e_pi_exit_time,
}
static playerInfo[MAX_PLAYERS][e_PlayerInfo];

enum e_VehicleInfo
{
    e_vi_door[4],
}
static vehicleInfo[MAX_VEHICLES][e_VehicleInfo];

/*
 * FIXES_SetVehicleParamsCarDoors(vehicleid, driver, passenger, backleft, backright)
 *
 * FIXES:
 *     GetVehicleParamsCarDoors
 */

#if defined _ALS_SetVehicleParamsCarDoors
    #error _ALS_SetVehicleParamsCarDoors defined
#endif
native BAD_SetVehicleParamsCarDoors(vehicleid, driver, passenger, backleft, backright) = SetVehicleParamsCarDoors;

#if FIX_GetVehicleParamsCarDoors
    stock FIXES_SetVehicleParamsCarDoors(vehicleid, driver, passenger, backleft, backright)
    {
        if (driver != -1)
        {
            vehicleInfo[vehicleid][e_vi_door][0] = driver;
        }

        if (passenger != -1)
        {
            vehicleInfo[vehicleid][e_vi_door][1] = passenger;
        }

        if (backleft != -1)
        {
            vehicleInfo[vehicleid][e_vi_door][2] = backleft;
        }

        if (backright != -1)
        {
            vehicleInfo[vehicleid][e_vi_door][3] = backright;
        }

        return
            SetVehicleParamsCarDoors(vehicleid,
                vehicleInfo[vehicleid][e_vi_door][0],
                vehicleInfo[vehicleid][e_vi_door][1],
                vehicleInfo[vehicleid][e_vi_door][2],
                vehicleInfo[vehicleid][e_vi_door][3]
            );
    }
    #define _ALS_SetVehicleParamsCarDoors
    #define SetVehicleParamsCarDoors FIXES_SetVehicleParamsCarDoors
#endif


/*
 * FIXES_GetVehicleParamsCarDoors(vehicleid, &driver, &passenger, &backleft, &backright)
 *
 * FIXES:
 *     GetVehicleParamsCarDoors
 */

#if defined _ALS_GetVehicleParamsCarDoors
    #error _ALS_GetVehicleParamsCarDoors defined
#endif
native BAD_GetVehicleParamsCarDoors(vehicleid, &driver, &passenger, &backleft, &backright) = GetVehicleParamsCarDoors;

#if FIX_GetVehicleParamsCarDoors
    stock FIXES_GetVehicleParamsCarDoors(vehicleid, &driver, &passenger, &backleft, &backright)
    {
        driver = vehicleInfo[vehicleid][e_vi_door][0];
        passenger = vehicleInfo[vehicleid][e_vi_door][1];
        backleft = vehicleInfo[vehicleid][e_vi_door][2];
        backright = vehicleInfo[vehicleid][e_vi_door][3];
    }
    #define _ALS_GetVehicleParamsCarDoors
    #define GetVehicleParamsCarDoors FIXES_GetVehicleParamsCarDoors
#endif

/*
 * _FIXES_SetVehiclePCDTimer(vehicleid, driver, passenger, backleft, backright)
 *
 * FIXES:
 *     GetVehicleParamsCarDoors
 */

#if FIX_GetVehicleParamsCarDoors
    forward _FIXES_SetVehiclePCDTimer(vehicleid, driver, passenger, backleft, backright);

    public _FIXES_SetVehiclePCDTimer(vehicleid, driver, passenger, backleft, backright)
    {
        return SetVehicleParamsCarDoors(vehicleid, driver, passenger, backleft, backright);
    }
#endif


/*
 * FIXES_UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires)
 *
 * FIXES:
 *     GetVehicleParamsCarDoors
 */

#if defined _ALS_UpdateVehicleDamageStatus
    #error _ALS_UpdateVehicleDamageStatus defined
#endif
native BAD_UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires) = UpdateVehicleDamageStatus;

#if FIX_GetVehicleParamsCarDoors
    stock FIXES_UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires)
    {
        UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
        SetVehicleParamsCarDoors(vehicleid, -1, -1, -1, -1);
    }
    #define _ALS_UpdateVehicleDamageStatus
    #define UpdateVehicleDamageStatus FIXES_UpdateVehicleDamageStatus
#endif


stock fix_doors_OnPlayerUpdate(playerid)
{
    if (playerInfo[playerid][e_pi_vehicle] != 0)
	{
        new vehicleid = playerInfo[playerid][e_pi_vehicle];
        new animindex = GetPlayerAnimationIndex(playerid);

        // opening
        if ((1043 <= animindex <= 1044 || 1026 <= animindex <= 1027) && playerInfo[playerid][e_pi_vehicle_seat] == -1)
		{
            new model = GetVehicleModel(vehicleid);

            new Float:fX, Float:fY, Float:fZ;
            GetVehiclePos(vehicleid, fX, fY, fZ);

            new Float:v_wide, Float:v_long, Float:v_high;
            GetVehicleModelInfo(model, VEHICLE_MODEL_INFO_SIZE, v_wide, v_long, v_high);

            new Float:v_frontseat[3], Float:v_rearseat[3];
            GetVehicleModelInfo(model, VEHICLE_MODEL_INFO_FRONTSEAT, v_frontseat[0], v_frontseat[1], v_frontseat[2]);
            GetVehicleModelInfo(model, VEHICLE_MODEL_INFO_REARSEAT, v_rearseat[0], v_rearseat[1], v_rearseat[2]);

            new seat = -1;

            if (playerInfo[playerid][e_pi_isdriver])
			{
                if (IsPlayerInRangeOfPoint(playerid, 1.0, fX + v_frontseat[0] / 2 - v_wide / 2, fY + v_frontseat[1], fZ + v_frontseat[2])) {
                    seat = 0;
                } else if (IsPlayerInRangeOfPoint(playerid, 1.0, fX - v_frontseat[0] / 2 + v_wide / 2, fY + v_frontseat[1], fZ + v_frontseat[2])) {
                    seat = 1;
                }
            }
			else
			{
                if (IsPlayerInRangeOfPoint(playerid, 1.0, fX - v_frontseat[0] / 2 + v_wide / 2, fY + v_frontseat[1], fZ + v_frontseat[2])) {
                    seat = 1;
                } else if (IsPlayerInRangeOfPoint(playerid, 1.0, fX + v_rearseat[0] / 2 - v_wide / 2, fY + v_rearseat[1], fZ + v_rearseat[2])) {
                    seat = 2;
                } else if (IsPlayerInRangeOfPoint(playerid, 1.0, fX - v_rearseat[0] / 2 + v_wide / 2, fY + v_rearseat[1], fZ + v_rearseat[2])) {
                    seat = 3;
                }
            }

            if (seat != -1) {
                playerInfo[playerid][e_pi_vehicle_seat] = seat;
                vehicleInfo[vehicleid][e_vi_door][seat] = 1;
                SetVehicleParamsCarDoors(vehicleid, -1, -1, -1, -1);
            }
        }

        // closing
        if (1011 <= animindex <= 1016 && playerInfo[playerid][e_pi_vehicle_seat] != -1)
		{
            new seat = playerInfo[playerid][e_pi_vehicle_seat];
            vehicleInfo[vehicleid][e_vi_door][seat] = 0;
            SetVehicleParamsCarDoors(vehicleid, -1, -1, -1, -1);
        }

        // shuffle
        if (animindex == 1054)
		{
            SetTimerEx("FIXES_SetVehiclePCDTimer", 1000, 0, "ddddd", vehicleid, 0, -1, -1, -1);
        }
    }
}

stock fix_doors_OnPlayerStateChange(playerid, newstate, oldstate)
{
    if (oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
	{
        new vehicleid = playerInfo[playerid][e_pi_vehicle];
        new seat = playerInfo[playerid][e_pi_vehicle_seat];

        playerInfo[playerid][e_pi_vehicle] = 0;

        new bool:isclosed = tickcount() - playerInfo[playerid][e_pi_exit_time] > 1600;
        vehicleInfo[vehicleid][e_vi_door][seat] = isclosed ? 0 : 1;

        SetVehicleParamsCarDoors(vehicleid, -1, -1, -1, -1);
    }
}


stock fix_doors_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
    playerInfo[playerid][e_pi_vehicle] = vehicleid;
    playerInfo[playerid][e_pi_isdriver] = !ispassenger;
    playerInfo[playerid][e_pi_vehicle_seat] = -1;
}

stock fix_doors_OnPlayerExitVehicle(playerid, vehicleid)
{
    playerInfo[playerid][e_pi_exit_time] = tickcount();
}

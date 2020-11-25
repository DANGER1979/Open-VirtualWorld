// -----------------------------------------------------------------------------
// Example Filterscript for the new Stunt Island 2
// ---------------------------------------------
// -----------------------------------------------------------------------------
// Includes
// --------

// SA-MP Include
#include <a_samp>

#include "../include/gl_common.inc"

// Used for chat text messages
#define COLOR_MESSAGE_YELLOW        0xFFDD00AA

public OnPlayerCommandText(playerid, cmdtext[])
{
    new cmd[256+1];
	new idx;
	cmd = strtok(cmdtext, idx);
	
	// Check command text
	if (strcmp("/ssi", cmd, true) == 0)
	{
	    // Set the player interior
		SetPlayerInterior(playerid, 0);
		
		// Check if the player is in any vehicle
		if (IsPlayerInAnyVehicle(playerid))
		{
		    // Set vehicle position and facing angle
		    SetVehiclePos(GetPlayerVehicleID(playerid), -3298.8088 + random(2), 69.2480, 6.0);
		    SetVehicleZAngle(GetPlayerVehicleID(playerid), 270);

			// Link vehicle to interior
			LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
		}
		else
		{
 			// Set player position and facing angle
			SetPlayerPos(playerid, -3393.4006 + random(2), 70.5831, 3.0);
			SetPlayerFacingAngle(playerid, 180);
		}

		// Fix camera position after teleporting
		SetCameraBehindPlayer(playerid);
		
		// Display chat text message to the player
		SendClientMessage(playerid, COLOR_MESSAGE_YELLOW, "* You teleported to Stunt Island 2...");

 		// Send a gametext message to the player
		GameTextForPlayer(playerid, "~b~~h~Stunt Island 2!", 3000, 3);

	    // Exit here
	    return 1;
	}
	
	// Check command text
	if (strcmp("/ssi2", cmd, true) == 0)
	{
	    // Set the player interior
		SetPlayerInterior(playerid, 0);

		// Check if the player is in any vehicle
		if (IsPlayerInAnyVehicle(playerid))
		{
		    // Set vehicle position and facing angle
		    SetVehiclePos(GetPlayerVehicleID(playerid), -3486.7407 + random(2), -4.9404, 163.5978);
		    SetVehicleZAngle(GetPlayerVehicleID(playerid), 270);

			// Link vehicle to interior
			LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
		}
		else
		{
 			// Set player position and facing angle
			SetPlayerPos(playerid, -3486.7407 + random(2), -4.9404, 162.1);
			SetPlayerFacingAngle(playerid, 180);
		}

		// Fix camera position after teleporting
		SetCameraBehindPlayer(playerid);

		// Display chat text message to the player
		SendClientMessage(playerid, COLOR_MESSAGE_YELLOW, "* You teleported to Stunt Island 2...");

 		// Send a gametext message to the player
		GameTextForPlayer(playerid, "~b~~h~Stunt Island 2!", 3000, 3);

	    // Exit here
	    return 1;
	}

	return 0;
}

public OnFilterScriptInit()
{
    // Display information in the Server Console
	print("\n");
	print("  |---------------------------------------------------");
	print("  |--- Stunt Island Filterscript 2 by Matite and Kye");
    print("  |--  Script v1.00");
    print("  |--  Sept 2017");
	print("  |---------------------------------------------------");
	
	CreateSI2Objects();
	CreateSI2Vehicles();
	
    // Exit here
	return 1;
}

//---------------------------------

CreateMapObject(modelid, Float:fX, Float:fY, Float:fZ, Float:fRX, Float:fRY, Float:fRZ)
{
	return CreateObject(modelid, fX, fY, fZ, fRX, fRY, fRZ, 800.0);
}

//---------------------------------
CreateSI2Objects_Jump1()
{
	new TempObjectNumber;
	//TempObjectNumber = CreatePlayerObject(playerid,19667,305.6357,3426.5845,95.3124,0.0000,0.0000,-90.0000,999.0);
	//SetPlayerObjectMaterial(playerid, TempObjectNumber, 0, 19659, "MatTubes", "BlueDirt1", 0);
	
    TempObjectNumber = CreateMapObject(19725, -3466.09790, 0.00000, 160.11690,   0.00000, 14.63400, 0.00000);
	TempObjectNumber = CreateMapObject(19699, -3449.53711, 0.00000, 151.37820,   0.00000, 28.77400, 0.00000);
	TempObjectNumber = CreateMapObject(19725, -3433.45166, 0.00000, 142.01190,   0.00000, 28.93500, 0.00000);
	TempObjectNumber = CreateMapObject(19699, -3419.84497, 0.00000, 130.21831,   0.00000, 41.27800, 0.00000);
	TempObjectNumber = CreateMapObject(19699, -3401.07910, 0.00000, 113.66820,   0.00000, 41.27800, 0.00000);
	TempObjectNumber = CreateMapObject(19730, -3386.93408, 0.00000, 101.86280,   0.00000, 2.32600, 0.00000);
	TempObjectNumber = CreateMapObject(19730, -3374.85718, 0.00000, 101.18830,   0.00000, -41.00000, 0.00000);
	TempObjectNumber = CreateMapObject(19699, -3360.13330, 0.00000, 112.33820,   0.00000, -40.84500, 0.00000);
}

CreateSI2Objects_Jump2()
{
    new TempObjectNumber;
   	TempObjectNumber = CreateMapObject(19699, -3225.82935, 34.91039, 119.27724,   0.00000, 0.00000, 90.00000);
	TempObjectNumber = CreateMapObject(19730, -3225.87671, 78.44610, 120.02410,   0.00000, -40.86800, 90.00000);
	TempObjectNumber = CreateMapObject(19699, -3225.82935, 59.87540, 119.27720,   0.00000, 0.00000, 90.00000);
	TempObjectNumber = CreateMapObject(19699, -3225.84351, 93.34570, 130.97090,   0.00000, -39.56600, 90.00000);
}
CreateSI2Objects_Jump3()
{
    new TempObjectNumber;
   	TempObjectNumber = CreateMapObject(19699, -3246.93042, 209.63574, 141.24167,   0.00000, 0.00000, 90.00000);
	TempObjectNumber = CreateMapObject(19730, -3246.95093, 228.22940, 141.95030,   0.00000, -40.25800, 90.00000);
	TempObjectNumber = CreateMapObject(19730, -3246.96997, 237.74980, 148.71240,   0.00000, -75.49200, 90.00000);
}
CreateSI2Objects_Planks()
{
    new TempObjectNumber;

	TempObjectNumber = CreateMapObject(19454, -3408.86499, 88.85648, 3.93976,   0.00000, -90.00000, 180.36005);
	TempObjectNumber = CreateMapObject(19454, -3395.08374, 104.27094, 8.81837,   0.00000, -90.00000, 89.57999);
	TempObjectNumber = CreateMapObject(19377, -3407.93140, 101.93988, 5.90022,   0.00000, 90.00000, 0.60000);
	TempObjectNumber = CreateMapObject(19377, -3380.88281, 144.36377, 21.14031,   0.00000, 90.00000, 0.00000);
	TempObjectNumber = CreateMapObject(19454, -3381.42383, 104.16142, 11.00772,   0.00000, -90.00000, 89.16000);
	TempObjectNumber = CreateMapObject(19377, -3375.70264, 110.64542, 13.68309,   0.00000, 90.00000, 0.60000);
	TempObjectNumber = CreateMapObject(19454, -3373.96973, 122.83356, 16.32500,   0.00000, -90.00000, 179.39998);
	TempObjectNumber = CreateMapObject(19454, -3373.98413, 136.14369, 18.49867,   0.00000, -90.00000, 179.39998);
	TempObjectNumber = CreateMapObject(19454, -3395.19678, 144.36130, 24.34873,   0.00000, -90.00000, 269.57996);
	TempObjectNumber = CreateMapObject(19454, -3410.35767, 144.08900, 27.07593,   0.00000, -90.00000, 269.57996);
	TempObjectNumber = CreateMapObject(19454, -3427.12329, 144.26988, 29.64600,   0.00000, -90.00000, 269.57996);
	TempObjectNumber = CreateMapObject(19377, -3434.98877, 137.93692, 30.99678,   0.00000, 90.00000, 0.00000);
	TempObjectNumber = CreateMapObject(19454, -3437.02954, 125.46407, 33.52687,   0.00000, -90.00000, 360.23993);
	TempObjectNumber = CreateMapObject(19454, -3437.42505, 111.89342, 36.41106,   0.00000, -90.00000, 360.23993);
	TempObjectNumber = CreateMapObject(19454, -3436.43628, 99.52238, 39.34293,   0.00000, -90.00000, 360.23993);
	TempObjectNumber = CreateMapObject(19454, -3406.09375, 104.76280, 44.38107,   0.00000, -90.00000, 89.57999);
	TempObjectNumber = CreateMapObject(19454, -3393.83350, 104.05559, 47.61376,   0.00000, -90.00000, 89.57999);
	TempObjectNumber = CreateMapObject(19454, -3380.67358, 104.05121, 49.89791,   0.00000, -90.00000, 89.57999);
	TempObjectNumber = CreateMapObject(19454, -3374.00171, 110.63370, 51.61119,   0.00000, -90.00000, -0.36000);
	TempObjectNumber = CreateMapObject(19454, -3374.00879, 124.99303, 54.48635,   0.00000, -90.00000, -0.36000);
	TempObjectNumber = CreateMapObject(19454, -3374.43042, 136.99883, 57.90563,   0.00000, -90.00000, -0.36000);
	TempObjectNumber = CreateMapObject(19454, -3434.72876, 86.29073, 41.77410,   0.00000, -90.00000, 360.23993);
	TempObjectNumber = CreateMapObject(19377, -3382.68188, 141.72795, 60.96520,   0.00000, 90.00000, 0.00000);
}

CreateSI2Objects()
{
	CreateMapObject(19530, -3130.00000, 0.00000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19530, -3130.00049, 140.00000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19531, -3130.00000, 280.00000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19532, -3130.00000, 70.00000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19532, -3130.00000, 210.00000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19533, -3238.75000, 210.00000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19534, -3200.00000, 210.00000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19532, -3200.00000, 280.00000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19534, -3200.00000, 70.00000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19532, -3199.98364, 139.98836, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19534, -3200.00000, 70.00000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19532, -3200.00000, 0.00000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19535, -3277.50000, 210.00000, 4.00000,   0.00000, 0.00000, 270.00000);
	CreateMapObject(19532, -3277.50000, 140.00000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19532, -3277.50000, 280.00000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19532, -3277.50000, 0.00000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19535, -3277.50000, 70.00000, 4.00000,   0.00000, 0.00000, 270.00000);
	CreateMapObject(19545, -3238.75000, 70.00000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19538, -3238.75000, 0.00000, 4.02000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19538, -3238.75000, 140.00000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19538, -3238.74683, 280.02811, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19542, -3052.50000, 0.00000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19541, -3052.50000, 70.00000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19535, -3060.00000, 70.00000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19532, -3060.00000, 0.00000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19532, -3060.00000, 140.00000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19535, -3060.00000, 210.00000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19532, -3060.00000, 280.00000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19542, -3052.50000, 140.00000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19541, -3052.50000, 210.00000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19542, -3052.50000, 280.00000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19540, -3052.50000, -62.50000, 4.00000,   0.00000, 0.00000, 270.00000);
	CreateMapObject(19541, -3060.00000, -62.50000, 4.00000,   0.00000, 0.00000, -90.00000);
	CreateMapObject(19542, -3130.00000, -62.50000, 4.00000,   0.00000, 0.00000, 270.00000);
	CreateMapObject(19541, -3200.00000, -62.50000, 4.00000,   0.00000, 0.00000, -90.00000);
	CreateMapObject(19539, -3238.75000, -62.50000, 4.00000,   0.00000, 0.00000, 270.00000);
	CreateMapObject(19541, -3277.50000, -62.50000, 4.00000,   0.00000, 0.00000, -90.00000);
	CreateMapObject(19540, -3285.00000, -62.50000, 4.00000,   0.00000, 0.00000, 180.00000);
	CreateMapObject(19542, -3410.00049, 0.00000, 4.00000,   0.00000, 0.00000, 270.00000);
	CreateMapObject(19541, -3285.00000, 70.00000, 4.00000,   0.00000, 0.00000, 180.00000);
	CreateMapObject(19543, -3316.25000, 210.00000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19546, -3285.00000, 202.50000, 4.00000,   0.00000, 0.00000, 270.00000);
	CreateMapObject(19540, -3472.50000, 342.50000, 4.00000,   0.00000, 0.00000, 450.00000);
	CreateMapObject(19546, -3285.00000, 0.00000, 4.00000,   0.00000, 0.00000, 270.00000);
	CreateMapObject(19546, -3285.00000, 0.00000, 4.00000,   0.00000, 0.00000, 180.00000);
	CreateMapObject(19542, -3410.00000, 0.00000, 4.00000,   0.00000, 0.00000, 450.00000);
	CreateMapObject(19540, -3472.50000, 0.00000, 4.00000,   0.00000, 0.00000, 180.00000);
	CreateMapObject(19540, -3472.50000, 0.00000, 4.00000,   0.00000, 0.00000, 450.00000);
	CreateMapObject(19547, -3347.50000, 280.00000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19539, -3285.00000, 108.75000, 4.00000,   0.00000, 0.00000, 180.00000);
	CreateMapObject(19542, -3410.00000, 202.50000, 4.00000,   0.00000, 0.00000, 270.00000);
	CreateMapObject(19543, -3378.75000, 210.00000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19543, -3441.25000, 210.00000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19536, -3441.25000, 280.00000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19540, -3472.50000, 202.50000, 4.00000,   0.00000, 0.00000, 180.00000);
	CreateMapObject(19542, -3472.50000, 265.00000, 4.00000,   0.00000, 0.00000, 180.00000);
	CreateMapObject(19541, -3472.50000, 335.00000, 4.00000,   0.00000, 0.00000, 180.00000);
	CreateMapObject(19542, -3410.00000, 342.50000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19535, -3277.50000, 350.00000, 4.00000,   0.00000, 0.00000, 270.00000);
	CreateMapObject(19535, -3200.00000, 350.00000, 4.00000,   0.00000, 0.00000, 180.00000);
	CreateMapObject(19535, -3060.00000, 350.00000, 4.00000,   0.00000, 0.00000, 180.00000);
	CreateMapObject(19532, -3130.00000, 350.00000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19533, -3238.75000, 350.00000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19546, -3285.00000, 342.50000, 4.00000,   0.00000, 0.00000, 180.00000);
	CreateMapObject(19540, -3285.00000, 482.50000, 4.00000,   0.00000, 0.00000, 450.00000);
	CreateMapObject(19542, -3222.50000, 482.50000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19536, -3238.75122, 420.00021, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19541, -3285.00000, 412.50000, 4.00000,   0.00000, 0.00000, 180.00000);
	CreateMapObject(19541, -3052.50000, 350.00000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19540, -3052.50000, 482.50000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19539, -3052.50000, 388.75000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19539, -3083.75000, 482.50000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19541, -3122.50000, 482.50000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19541, -3137.50000, 482.50000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19541, -3152.50000, 482.50000, 4.00000,   0.00000, 0.00000, 90.00000);
	CreateMapObject(19531, -3130.01245, 419.98441, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19543, -3277.50000, 388.75000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19543, -3277.50000, 451.25000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19543, -3200.00000, 388.75000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19543, -3200.00000, 451.25000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19543, -3060.00000, 388.75000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19543, -3060.00000, 451.25000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19539, -3285.00000, 451.25000, 4.00000,   0.00000, 0.00000, 180.00000);
	CreateMapObject(19539, -3052.50000, 451.25000, 4.00000,   0.00000, 0.00000, 0.00000);
	CreateMapObject(10368, -3107.83838, 297.34488, 24.56054,   0.00000, 0.00000, 0.00000);
	CreateMapObject(10377, -2868.24438, -238.24341, 26.45462,   0.00000, 0.00000, 0.00000);
	CreateMapObject(4585, -3491.07324, 0.00000, 61.30460,   0.00000, 0.00000, 0.00000);
	CreateMapObject(4603, -3405.58911, 97.80080, 10.79353,   0.00000, 0.00000, -269.99982);
	CreateMapObject(19530, -3393.56104, 100.72024, -6.11122,   0.00000, 0.00000, 0.00000);
	CreateMapObject(19530, -3516.28223, 102.09190, -7.35393,   0.00000, 0.00000, 0.00000);
	CreateMapObject(8832, -3347.17822, 64.15836, 1.78405,   0.00000, 0.00000, 0.18000);

	CreateMapObject(4585, -3236.90820, 0.00000, 18.69910,   0.00000, 0.00000, 0.00000);
	CreateMapObject(4585, -3237.53320, 174.94870, 40.38210,   0.00000, 0.00000, 0.00000);
	CreateMapObject(10308, -3396.75024, 1.23140, 39.42690,   0.00000, 0.00000, 180.00000);
	CreateMapObject(19716, -3380.79736, -0.03522, 50.34034,   0.00000, 0.00000, 0.00000);

	CreateMapObject(10308, -3239.66382, 66.76080, 48.38653,   0.00000, 0.00000, 269.57983);
	CreateMapObject(19716, -3225.78955, 56.98829, 69.13948,   0.00000, 0.00000, 90.06000);
	CreateMapObject(19716, -3225.78955, 75.71930, 69.13950,   0.00000, 0.00000, 90.06000);
	CreateMapObject(19716, -3225.78955, 39.98830, 69.13950,   0.00000, 0.00000, 90.06000);
	CreateMapObject(4690, -3246.31006, 281.84552, 17.15683,   0.00000, 0.00000, 360.54007);
	CreateMapObject(9907, -3237.63428, 242.10933, 81.36182,   0.00000, 0.00000, -89.87998);

	CreateMapObject(4690, -3246.31006, 281.84552, -133.90215,   0.00000, 0.00000, 360.54007);
	CreateMapObject(19716, -3246.90674, 219.93364, 91.21582,   0.00000, 0.00000, 90.06000);
	CreateMapObject(9907, -3102.14624, 381.39191, 93.07630,   0.00000, 0.00000, -90.00000);
	
	CreateSI2Objects_Jump1();
	CreateSI2Objects_Jump2();
	CreateSI2Objects_Jump3();
	CreateSI2Objects_Planks();

	// Exit here
	return 1;
}

CreateSI2Vehicles()
{
	CreateVehicle(481, -3396.6323, 65.2824, 2.1592, 0.0000, -1, -1, 100);
	CreateVehicle(481, -3394.8513, 65.2776, 2.1592, 0.0000, -1, -1, 100);
	CreateVehicle(481, -3393.0017, 65.1022, 2.1592, 0.0000, -1, -1, 100);
	CreateVehicle(481, -3390.8074, 64.9944, 2.1592, 0.0000, -1, -1, 100);
	CreateVehicle(481, -3396.4329, 61.7688, 2.1592, 0.0000, -1, -1, 100);
	CreateVehicle(481, -3394.3135, 61.7317, 2.1592, 0.0000, -1, -1, 100);
	CreateVehicle(481, -3392.4827, 61.6891, 2.1592, 0.0000, -1, -1, 100);
	CreateVehicle(481, -3390.4846, 61.9325, 2.1592, 0.0000, -1, -1, 100);
	CreateVehicle(481, -3398.6116, 65.2106, 2.1592, 0.0000, -1, -1, 100);
	CreateVehicle(481, -3398.6394, 61.6270, 2.1592, 0.0000, -1, -1, 100);
	CreateVehicle(469, -3421.9714, 131.0383, 62.6804, -181.1401, -1, -1, 100);
	CreateVehicle(469, -3409.8079, 130.9381, 62.6804, -181.1401, -1, -1, 100);
	CreateVehicle(469, -3422.7668, 115.7165, 62.6804, -4.1401, -1, -1, 100);
	CreateVehicle(469, -3409.7246, 115.4408, 62.6804, -4.1401, -1, -1, 100);
	CreateVehicle(522, -3486.9651, 15.8764, 161.5978, 179.8800, -1, -1, 100);
	CreateVehicle(522, -3489.2876, 15.7444, 161.5978, 179.8800, -1, -1, 100);
	CreateVehicle(522, -3491.6292, 15.6526, 161.5978, 179.8800, -1, -1, 100);
	CreateVehicle(522, -3494.0493, 15.6818, 161.5978, 179.8800, -1, -1, 100);
	CreateVehicle(522, -3496.3477, 15.7695, 161.5978, 179.8800, -1, -1, 100);
	CreateVehicle(522, -3497.9700, 10.7264, 161.5978, 269.3997, -1, -1, 100);
	CreateVehicle(522, -3497.9236, 8.5011, 161.5978, 269.3997, -1, -1, 100);
	CreateVehicle(522, -3497.9685, 6.0802, 161.5978, 269.3997, -1, -1, 100);
	CreateVehicle(522, -3498.0918, 3.6834, 161.5978, 269.3997, -1, -1, 100);
	CreateVehicle(522, -3498.2686, 1.4095, 161.5978, 269.3997, -1, -1, 100);
	CreateVehicle(469, -3266.2654, 305.0790, 165.8293, 179.5199, -1, -1, 100);
	CreateVehicle(469, -3254.7788, 305.5163, 165.8293, 179.5199, -1, -1, 100);
	CreateVehicle(522, -3222.6567, -20.9652, 119.0018, 0.0000, -1, -1, 100);
	CreateVehicle(522, -3224.2336, -20.7803, 119.0018, 0.0000, -1, -1, 100);
	CreateVehicle(522, -3225.7671, -20.6788, 119.0018, 9.6600, -1, -1, 100);
	CreateVehicle(522, -3227.3901, -20.8378, 119.0018, 7.3200, -1, -1, 100);
}

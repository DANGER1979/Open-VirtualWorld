//
// Used for testing interpolated rotations with MoveObjectEx
// Also used to test AttachObjectToObjectEx
// The other ferris wheel (that actually spins!)
// Located on the opposite peer at LS
//
// SA-MP 0.3d and above
//
// - Kye 2011
//
/*
 *            VW_Ferriswheel v1.1
 *       (c) Copyright 2009-2013 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (danger1979@mail.ru)
 * @date      : 27.01.2013
 * @update    : 15.08.2013
 *
 * This file is provided as is (no warranties).
 *
 */



//#include <a_samp>
//#include "../include/gl_common.inc" // for PlaySoundForPlayersInRange()
//#include <AntiDeAMX>

#define NUM_FERRIS_CAGES        10
#define FERRIS_WHEEL_ID         18877
#define FERRIS_BASE_ID          18878
#define FERRIS_CAGE_ID          18879
//#define FERRIS_DRAW_DISTANCE    300.0
#define FERRIS_WHEEL_SPEED      0.01

#define FERRIS_WHEEL_Z_ANGLE  	90.0 // This is the heading the entire ferris wheel is at (beware of gimbal lock)

#define forEx(%0,%1) for(new %1=0;%1<%0;%1++)

//new Float:gFerrisOrigin[3] = {832.8393, -2046.1990, 27.0900};
new Float:gFerrisOrigin[3] = {389.7734, -2028.4688, 22.0900};

// Cage offsets for attaching to the main wheel
new Float:gFerrisCageOffsets[NUM_FERRIS_CAGES][3] = {
{0.0699, 0.0600, -11.7500},
{-6.9100, -0.0899, -9.5000},
{11.1600, 0.0000, -3.6300},
{-11.1600, -0.0399, 3.6499},
{-6.9100, -0.0899, 9.4799},
{0.0699, 0.0600, 11.7500},
{6.9599, 0.0100, -9.5000},
{-11.1600, -0.0399, -3.6300},
{11.1600, 0.0000, 3.6499},
{7.0399, -0.0200, 9.3600}
};

// SA-MP objects
new gFerrisWheel;
new gFerrisBase;
new gFerrisCages[NUM_FERRIS_CAGES];



//-------------------------------------------------

new Float:gCurrentTargetYAngle = 0.0; // Angle of the Y axis of the wheel to rotate to.
new gWheelTransAlternate = 0; // Since MoveObjectEx requires some translation target to intepolate
						    // rotation, the world pos target is alternated by a small amount.

stock UpdateWheelTarget()
{
    gCurrentTargetYAngle += 36.0; // There are 10 carts, so 360 / 10
    if(gCurrentTargetYAngle >= 360.0) {
		gCurrentTargetYAngle = 0.0;
    }
	if(gWheelTransAlternate) gWheelTransAlternate = 0;
	else gWheelTransAlternate = 1;
}
//-------------------------------------------------
forward RotateWheel();
public RotateWheel()
{
    UpdateWheelTarget();
    
    new Float:fModifyWheelZPos = 0.0;
    if(gWheelTransAlternate) fModifyWheelZPos = 0.05;
    
    MoveObjectEx( gFerrisWheel, gFerrisOrigin[0], gFerrisOrigin[1], gFerrisOrigin[2]+fModifyWheelZPos,
				FERRIS_WHEEL_SPEED, 0.0, gCurrentTargetYAngle, FERRIS_WHEEL_Z_ANGLE );
}
//-------------------------------------------------
stock ferriswheel_OnGameModeInit()
{
	//AntiDeAMX();
	gFerrisWheel = CreateObjectEx( FERRIS_WHEEL_ID,
								gFerrisOrigin[0], gFerrisOrigin[1], gFerrisOrigin[2],
	  							 0.0, 0.0, FERRIS_WHEEL_Z_ANGLE);

    gFerrisBase = CreateObjectEx( FERRIS_BASE_ID, gFerrisOrigin[0], gFerrisOrigin[1], gFerrisOrigin[2],
	  							 0.0, 0.0, FERRIS_WHEEL_Z_ANGLE);
	  							 
	new x=0;
	while(x != NUM_FERRIS_CAGES) {
        gFerrisCages[x] = CreateObjectEx( FERRIS_CAGE_ID, gFerrisOrigin[0], gFerrisOrigin[1], gFerrisOrigin[2],
	  							 0.0, 0.0, FERRIS_WHEEL_Z_ANGLE);
	  							 
        AttachObjectToObjectEx( gFerrisCages[x], gFerrisWheel,
							  gFerrisCageOffsets[x][0],
							  gFerrisCageOffsets[x][1],
	  						  gFerrisCageOffsets[x][2],
							  0.0, 0.0, FERRIS_WHEEL_Z_ANGLE, 0 );
					
		x++;
	}
	
	SetTimer("RotateWheel",3*1000,0);
	print("   vw_ferriswheel v1.1 By: Kye 2011&Danger1979");
	print("_____________________________________________");
	print(" ");
	return 1;
}


//-------------------------------------------------

stock ferriswheel_OnGameModeExit()
{
	new x=0;
	
    DestroyObjectEx(gFerrisWheel, 25);
    DestroyObjectEx(gFerrisBase, 25);
    
	x=0;
	while(x != NUM_FERRIS_CAGES) {
	    DestroyObjectEx(gFerrisCages[x], 26);
		x++;
	}

	return 1;
}

stock ferriswheel_OnPlayerConnect(playerid)
{
	RemoveBuildingForPlayerEx(playerid, 6463, 389.7734, -2028.4688, 19.8047, 0.5);
	RemoveBuildingForPlayerEx(playerid, 3751, 389.8750, -2035.3828, 29.9531, 50.0);
	RemoveBuildingForPlayerEx(playerid, 6298, 389.7734, -2028.4688, 19.8047, 0.5);
	RemoveBuildingForPlayerEx(playerid, 6461, 389.7734, -2028.5000, 20.1094, 0.5);
	RemoveBuildingForPlayerEx(playerid, 3752, 389.8750, -2028.5000, 32.2266, 50.0);
}
//-------------------------------------------------

stock ferriswheel_OnObjectMoved(objectid)
{
    if(objectid != gFerrisWheel) return 0;
    
    SetTimer("RotateWheel",3*1000,0);
    return 1;
}

//-------------------------------------------------




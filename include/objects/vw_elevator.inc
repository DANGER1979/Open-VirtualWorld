/*
*   Example elevator system for the new LS building.
*
*	Zamaroht 2010
*
*   26/08/2011: Kye: added a sound effect for the elevator starting/stopping.
*/

// Warning: This script uses a total of 45 objects, 22 3D Text Labels and 1 dialog.
/*
 *            vw_elevator v1.1
 *       (c) Copyright 2009-2013 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (danger1979@mail.ru)
 * @date      : 27.01.2013
 * @update    : 19.05.2020
 *
 * This file is provided as is (no warranties).
 *
 */
#include <a_samp>
#include <streamer>

new gLiftStatus, oLift; //для лифта

//==============================================================================
//для ls_elevator //для лифта ЛС
#define elevator_SPEED      (5.0)   // Movement speed of the elevator.
#define DOORS_SPEED         (5.0)   // Movement speed of the doors.
#define elevator_WAIT_TIME	(5000)  // Time in ms that the elevator will wait in each floor before continuing with the queue.
								// Be sure to give enough time for doors to open.
// Private:
#define X_DOOR_CLOSED       (1786.627685)
#define X_DOOR_R_OPENED     (1785.027685)//координата X правой открытой двери
#define X_DOOR_L_OPENED     (1788.227685)
#define GROUND_Z_COORD      (14.511476)
#define elevator_OFFSET     (0.059523)
// ------------------
// Constants:
//-------------------
#define num_floors	(21)  // Time in ms that the elevator will wait in each floor before continuing with the queue.

//static FloorNames[21][] =
new FloorNames[num_floors][] =
{
	/*"Ground Floor",
	"First Floor",
	"Second Floor",
	"Third Floor",
	"Fourth Floor",
	"Fifth Floor",
	"Sixth Floor",
	"Seventh Floor",
	"Eighth Floor",
	"Ninth Floor",
	"Tenth Floor",
	"Eleventh Floor",
	"Twelfth Floor",
	"Thirteenth Floor",
	"Fourteenth Floor",
	"Fifteenth Floor",
	"Sixteenth Floor",
	"Seventeenth Floor",
	"Eighteenth Floor",
	"Nineteenth Floor",
	"Penthouse"*/
"Подвал",
"Первый Этаж",
"Второй Этаж",
"Третий Этаж",
"Четвертый Этаж",
"Пятый Этаж",
"Шестой Этаж",
"Седьмой Этаж",
"Восьмой Этаж",
"Девятый Этаж",
"Десятый Этаж",
"Одиннадцатый Этаж",
"Двенадцатый Этаж",
"Тринадцатый Этаж",
"Четырнадцатый Этаж",
"Пятнадцатый Этаж",
"Шестнадцатый Этаж",
"Семнадцатый Этаж",
"Восемнадцатый Этаж",
"Девятнадцатый Этаж",
"Пентхаус"
};
//static Float:FloorZOffsets[21] =
new Float:FloorZOffsets[num_floors] =
{
    0.0,		// 0.0,
    8.5479,		// 8.5479,
    13.99945,   // 8.5479 + (5.45155 * 1.0),
    19.45100,   // 8.5479 + (5.45155 * 2.0),
    24.90255,   // 8.5479 + (5.45155 * 3.0),
    30.35410,   // 8.5479 + (5.45155 * 4.0),
    35.80565,   // 8.5479 + (5.45155 * 5.0),
    41.25720,   // 8.5479 + (5.45155 * 6.0),
    46.70875,   // 8.5479 + (5.45155 * 7.0),
    52.16030,   // 8.5479 + (5.45155 * 8.0),
    57.61185,   // 8.5479 + (5.45155 * 9.0),
    63.06340,   // 8.5479 + (5.45155 * 10.0),
    68.51495,   // 8.5479 + (5.45155 * 11.0),
    73.96650,   // 8.5479 + (5.45155 * 12.0),
    79.41805,   // 8.5479 + (5.45155 * 13.0),
    84.86960,   // 8.5479 + (5.45155 * 14.0),
    90.32115,   // 8.5479 + (5.45155 * 15.0),
    95.77270,   // 8.5479 + (5.45155 * 16.0),
    101.22425,  // 8.5479 + (5.45155 * 17.0),
    106.67580,	// 8.5479 + (5.45155 * 18.0),
    112.12735	// 8.5479 + (5.45155 * 19.0)
};
// ------------------
// Variables:
//-------------------
new Obj_Elevator, Obj_ElevatorDoors[2],	Obj_FloorDoors[num_floors][2];
new STREAMER_TAG_3D_TEXT_LABEL:Label_Elevator, Text3D:Label_Floors[num_floors];

#define elevator_STATE_IDLE     (0)
#define elevator_STATE_WAITING  (1)
#define elevator_STATE_MOVING   (2)

new ElevatorState;
new ElevatorFloor;  // Если он простаивает или ждет, то это текущий этаж. Если движется, то этаж, на который он движется.

#define INVALID_FLOOR           (-1)

new ElevatorQueue[num_floors];  	// Floors in queue.
new FloorRequestedBy[num_floors];   // FloorRequestedBy[floor_id] = playerid; - Points out who requested which floor.

new ElevatorBoostTimer;     // Timer that makes the elevator move faster after players start surfing the object.

// ------------------
//  Function forwards:
//-------------------
// Public:
forward BoostTimer(floorid);        	// Increases the elevator speed until it reaches 'floorid'.
forward TurnToIdleTimer();
// Private:


stock elevator_OnGameModeInit()//ResetElevatorQueue()
{
	new map_world = 0, map_int = 0;
	oLift = CreateObjectEx(5837,-1813.0000,585.5000,35.9000,0.0,0.0,180.0, map_world, map_int, -1, 100.0,100.0);//для лифта

	// Resets the queue.
	for(new i; i < sizeof(ElevatorQueue); i ++)
	{
	    ElevatorQueue[i] 	= INVALID_FLOOR;
	    FloorRequestedBy[i] = INVALID_PLAYER_ID;
	}
	elevator_Initialize();
	print(" ");
	print("   vw_elevator Система лифтов v1.1 By: Zamaroht&Kye&Danger1979");
	print("_____________________________________________");
	print(" ");
	return 1;
}
//==============================================================================

//для ls_elevator начало
stock elevator_Initialize()// Initializes the elevator.
{
	new map_world = 0, map_int = 0;
	Obj_Elevator 			= CreateObjectEx(18755, 1786.678100, -1303.459472, GROUND_Z_COORD + elevator_OFFSET, 0.0, 0.0, 270.0, map_world, map_int, -1, 100.0,100.0);
	Obj_ElevatorDoors[0] 	= CreateObjectEx(18757, X_DOOR_CLOSED, -1303.459472, GROUND_Z_COORD, 0.0, 0.0, 270.0, map_world, map_int, -1, 100.0,100.0);
	Obj_ElevatorDoors[1] 	= CreateObjectEx(18756, X_DOOR_CLOSED, -1303.459472, GROUND_Z_COORD, 0.0, 0.0, 270.0, map_world, map_int, -1, 100.0,100.0);
	Label_Elevator          = Create3DTextLabelEx("{FFFFFF}Press '{0080FF}~k~~VEHICLE_ENTER_EXIT~{FFFFFF}' to use elevator", 0xFFFFFFAA, 1784.9822, -1302.0426, 13.6491, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0);
	new strtmp[MAX_STRING];
	new Float:z;
	for(new i; i < sizeof(Obj_FloorDoors); i ++)
	{
	    Obj_FloorDoors[i][0] 	= CreateObjectEx(18757, X_DOOR_CLOSED, -1303.171142, GetDoorsZCoordForFloor(i), 0.0, 0.0, 270.0, map_world, map_int, -1, 100.0,100.0);
		Obj_FloorDoors[i][1] 	= CreateObjectEx(18756, X_DOOR_CLOSED, -1303.171142, GetDoorsZCoordForFloor(i), 0.0, 0.0, 270.0, map_world, map_int, -1, 100.0,100.0);
		format(strtmp, sizeof(strtmp), "{CCCCCC}[%s]\n{CCCCCC}Press '{0080FF}~k~~VEHICLE_ENTER_EXIT~{CCCCCC}' to call", FloorNames[i]);
		if(i == 0) z = 13.4713;
		else z = 13.4713 + 8.7396 + ((i-1) * 5.45155);
		Label_Floors[i]         = Create3DTextLabelEx(strtmp, 0xCCCCCCAA, 1783.9799, -1300.7660, z, 10.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0);
		// Label_Elevator, Text3D:Label_Floors[num_floors];
	}
	// Open ground floor doors:
	Floor_OpenDoors(0);
	elevator_OpenDoors();
	return 1;
}

stock elevator_OnGameModeExit()
//public OnFilterScriptExit()
{//все созданные объекты этим скриптом должны быть уничтожены, но не уничтожая объекты созданные модом
	elevator_Destroy();
	return 1;
}

stock elevator_Destroy()
{
	// Destroys the elevator.
	DestroyObjectEx(Obj_Elevator, num_floors);
	DestroyObjectEx(Obj_ElevatorDoors[0], num_floors);
	DestroyObjectEx(Obj_ElevatorDoors[1], num_floors);
	DestroyDynamic3DTextLabel(Label_Elevator); Counter3DText --;
	for(new i; i < sizeof(Obj_FloorDoors); i ++)
	{
	    DestroyObjectEx(Obj_FloorDoors[i][0], num_floors);
		DestroyObjectEx(Obj_FloorDoors[i][1], num_floors);
		Delete3DTextLabel(Label_Floors[i]); Counter3DText --;
	}
	return 1;
}

stock elevator_OpenDoors()
{//двери самого лифта
	// Opens the elevator's doors.
	new Float:x, Float:y, Float:z;
	//GetObjectPos(Obj_ElevatorDoors[0], x, y, z);
	GetDynamicObjectPos(Obj_ElevatorDoors[0], x, y, z);
	MoveObjectEx(Obj_ElevatorDoors[0], X_DOOR_L_OPENED, y, z, DOORS_SPEED);
	MoveObjectEx(Obj_ElevatorDoors[1], X_DOOR_R_OPENED, y, z, DOORS_SPEED);
	return 1;
}
stock elevator_CloseDoors()
{
    // Closes the elevator's doors.
    if(ElevatorState == elevator_STATE_MOVING) return 0;
    new Float:x, Float:y, Float:z;
	//GetObjectPos(Obj_ElevatorDoors[0], x, y, z);
	GetDynamicObjectPos(Obj_ElevatorDoors[0], x, y, z);
	MoveObjectEx(Obj_ElevatorDoors[0], X_DOOR_CLOSED, y, z, DOORS_SPEED);
	MoveObjectEx(Obj_ElevatorDoors[1], X_DOOR_CLOSED, y, z, DOORS_SPEED);
	//PlaySoundForPlayersInRange(SOUND_LIFT_LOOP, 50.0, X_DOOR_CLOSED, -1303.171142, GetDoorsZCoordForFloor(floorid) + 5.0);
	return 1;
}
stock Floor_OpenDoors(floorid)
{//двери которые стоят на каждом этаже, их тоже надо открывать
    // Opens the doors at the specified floor.
	if(floorid == -1) return INVALID_FLOOR;
    MoveObjectEx(Obj_FloorDoors[floorid][0], X_DOOR_L_OPENED, -1303.171142, GetDoorsZCoordForFloor(floorid), DOORS_SPEED);
	MoveObjectEx(Obj_FloorDoors[floorid][1], X_DOOR_R_OPENED, -1303.171142, GetDoorsZCoordForFloor(floorid), DOORS_SPEED);
	PlaySoundForPlayersInRange(SOUND_LIFT_PING, 50.0, X_DOOR_CLOSED, -1303.171142, GetDoorsZCoordForFloor(floorid) + 5.0);
	return 1;
}
stock Floor_CloseDoors(floorid)
{//двери которые стоят на каждом этаже, их тоже надо закрывать
	if(floorid == -1) return INVALID_FLOOR;
    // Closes the doors at the specified floor.
    MoveObjectEx(Obj_FloorDoors[floorid][0], X_DOOR_CLOSED, -1303.171142, GetDoorsZCoordForFloor(floorid), DOORS_SPEED);
	MoveObjectEx(Obj_FloorDoors[floorid][1], X_DOOR_CLOSED, -1303.171142, GetDoorsZCoordForFloor(floorid), DOORS_SPEED);
	PlaySoundForPlayersInRange(SOUND_LIFT_PING, 50.0, X_DOOR_CLOSED, -1303.171142, GetDoorsZCoordForFloor(floorid) + 5.0);
	return 1;
}
stock RemoveFirstQueueFloor()
{
	// Removes the data in ElevatorQueue[0], and reorders the queue accordingly.
	for(new i; i < sizeof(ElevatorQueue) - 1; i ++)
	{
	    ElevatorQueue[i] = ElevatorQueue[i + 1];
	}
	ElevatorQueue[sizeof(ElevatorQueue) - 1] = INVALID_FLOOR;
	return 1;
}
stock AddFloorToQueue(floorid)
{	// Adds 'floorid' at the end of the queue.
	new slot = -1;
	for(new i; i < sizeof(ElevatorQueue); i ++)
	{// Scan for the first empty space:
	    if(ElevatorQueue[i] == INVALID_FLOOR)
	    {
	        slot = i;
	        break;
	    }
	}
	if(slot != -1)
	{
	    ElevatorQueue[slot] = floorid;
     	// If needed, move the elevator.
	    if(ElevatorState == elevator_STATE_IDLE) ReadNextFloorInQueue();
	    return 1;
	}
	return 0;
}


stock IsFloorInQueue(floorid)
{
	// Checks if the specified floor is currently part of the queue.
	for(new i; i < sizeof(ElevatorQueue); i ++)
	{
	    if(ElevatorQueue[i] == floorid) return 1;
	}
	return 0;
}

stock ReadNextFloorInQueue()
{
	// Reads the next floor in the queue, closes doors, and goes to it.
	if(ElevatorState != elevator_STATE_IDLE
		|| ElevatorQueue[0] == INVALID_FLOOR) return 0;
	elevator_CloseDoors();
	Floor_CloseDoors(ElevatorFloor);
	return 1;
}
stock DidPlayerRequestElevator(playerid)
{
	for(new i; i < sizeof(FloorRequestedBy); i ++)
	{
	    if(FloorRequestedBy[i] == playerid) return 1;
	}
	return 0;
}


stock CallElevator(playerid, floorid)// You can use INVALID_PLAYER_ID too.
{
	// Calls the elevator (also used with the elevator dialog).
	if(FloorRequestedBy[floorid] != INVALID_PLAYER_ID
		|| IsFloorInQueue(floorid)) return 0;
	FloorRequestedBy[floorid] = playerid;
	AddFloorToQueue(floorid);
	return 1;
}
forward Float:GetElevatorZCoordForFloor(floorid);
public Float:GetElevatorZCoordForFloor(floorid)
{//floorid не должно принимать -1
	if(floorid == -1) return 0.0;
    return (GROUND_Z_COORD + FloorZOffsets[floorid] + elevator_OFFSET); // A small offset for the elevator object itself.
}

forward Float:GetDoorsZCoordForFloor(floorid);
public Float:GetDoorsZCoordForFloor(floorid)
{
	if(floorid == -1) return 0.0;
	return (GROUND_Z_COORD + FloorZOffsets[floorid]);
}
public TurnToIdleTimer()
{
	ElevatorState = elevator_STATE_IDLE;
	ReadNextFloorInQueue();
	return 1;
}
public BoostTimer(floorid)
{//floorid не должно принимать -1
	// Increases the elevator's speed until it reaches 'floorid'
	StopObjectEx(Obj_Elevator);
	StopObjectEx(Obj_ElevatorDoors[0]);
	StopObjectEx(Obj_ElevatorDoors[1]);
	
	MoveObjectEx(Obj_Elevator, 1786.678100, -1303.459472, GetElevatorZCoordForFloor(floorid), elevator_SPEED);
    MoveObjectEx(Obj_ElevatorDoors[0], X_DOOR_CLOSED, -1303.459472, GetDoorsZCoordForFloor(floorid), elevator_SPEED);
    MoveObjectEx(Obj_ElevatorDoors[1], X_DOOR_CLOSED, -1303.459472, GetDoorsZCoordForFloor(floorid), elevator_SPEED);
	return 1;
}
stock MoveToFloor(floorid)
{//floorid не должно принимать -1
	// Moves the elevator to specified floor (doors are meant to be already closed).
	ElevatorState = elevator_STATE_MOVING;
	ElevatorFloor = floorid;
	// Move the elevator slowly, to give time to clients to sync the object surfing. Then, boost it up:
	MoveObjectEx(Obj_Elevator, 1786.678100, -1303.459472, GetElevatorZCoordForFloor(floorid), 0.25);
    MoveObjectEx(Obj_ElevatorDoors[0], X_DOOR_CLOSED, -1303.459472, GetDoorsZCoordForFloor(floorid), 0.25);
    MoveObjectEx(Obj_ElevatorDoors[1], X_DOOR_CLOSED, -1303.459472, GetDoorsZCoordForFloor(floorid), 0.25);
    DestroyDynamic3DTextLabel(Label_Elevator); Counter3DText --;
    KillTimer(ElevatorBoostTimer); ElevatorBoostTimer = -1;
	ElevatorBoostTimer = SetTimerEx("BoostTimer", 2000, 0, "i", floorid);
	return 1;
}
stock elevator_OnObjectMoved(objectid)
{
    new Float:x, Float:y, Float:z;
	for(new i; i < sizeof(Obj_FloorDoors); i ++)
	{
		if(objectid == Obj_FloorDoors[i][0])
		{
		    //GetObjectPos(Obj_FloorDoors[i][0], x, y, z);
		    GetDynamicObjectPos(Obj_FloorDoors[i][0], x, y, z);
		    if(x < X_DOOR_L_OPENED - 0.5)   // Some floor doors have shut, move the elevator to next floor in queue:
		    {
				MoveToFloor(ElevatorQueue[0]);
				RemoveFirstQueueFloor();
			}
		}
	}
	if(objectid == Obj_Elevator)   // The elevator reached the specified floor.
	{
	    KillTimer(ElevatorBoostTimer); ElevatorBoostTimer = -1; // Kills the timers, in case the elevator reached the floor before boost.
	    if(ElevatorFloor != -1) FloorRequestedBy[ElevatorFloor] = INVALID_PLAYER_ID;
	    elevator_OpenDoors();
	    Floor_OpenDoors(ElevatorFloor);//objectid == 15469
	    //GetObjectPos(Obj_Elevator, x, y, z);
	    GetDynamicObjectPos(Obj_Elevator, x, y, z);
	    Label_Elevator	= Create3DTextLabelEx("{FFFFFF}Press '{0080FF}~k~~VEHICLE_ENTER_EXIT~{FFFFFF}' to use elevator", 0xFFFFFFAA, 1784.9822, -1302.0426, z-0.9, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0);
	    ElevatorState 	= elevator_STATE_WAITING;
	    SetTimer("TurnToIdleTimer", elevator_WAIT_TIME, 0);
	}
}	

stock elevator_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if(dialogid != DIALOG_ID_ELEVATOR) return 1;////else if(dialogid == 72)
	SetPVarInt(playerid, "gShowDialog", -1);	
	if(!response)  return 1;
	if(FloorRequestedBy[listitem] != INVALID_PLAYER_ID || IsFloorInQueue(listitem))
	{
		GameTextForPlayerEx(playerid, "~r~The floor is already in the queue", 3500, 4);
	}
	else if(DidPlayerRequestElevator(playerid))
	{
		GameTextForPlayerEx(playerid, "~r~You already requested the elevator", 3500, 4);
	}
	else CallElevator(playerid, listitem);
	
	parkinglift_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	return 1;
}

stock elevator_OnPlayerKeyStateChange(playerid)//, newkeys)
{
	//if(newkeys & KEY_YES)
	//if(newkeys & KEY_SECONDARY_ATTACK)

    new Float:pos[3];
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
    if(pos[1] < -1301.4 && pos[1] > -1303.2417 && pos[0] < 1786.2131 && pos[0] > 1784.1555)
	{    // He is using the elevator button
        elevator_ShowDialog(playerid);
	}
	else    // Is he in a floor button?
	{
	    if(pos[1] > -1301.4 && pos[1] < -1299.1447 && pos[0] < 1785.6147 && pos[0] > 1781.9902)
	    {
	        // He is most likely using it, check floor:
			new i = 20;
			while(pos[2] < GetDoorsZCoordForFloor(i) + 3.5 && i > 0)
			{
			    i --;
			}
			if(i == 0 && pos[2] < GetDoorsZCoordForFloor(0) + 2.0) i = -1;
			if(i <= 19)
			{
				CallElevator(playerid, i + 1);
				GameTextForPlayerEx(playerid, "~r~Elevator called", 3500, 4);
			}
	    }
	}
}

stock elevator_ShowDialog(playerid)
{
	new strtmp[512];
	for(new i; i < sizeof(ElevatorQueue); i ++)
	{
	    if(FloorRequestedBy[i] != INVALID_PLAYER_ID)
		{
		     strcat(strtmp, "{FF0000}");
		}
	    strcat(strtmp, FloorNames[i]);
	    strcat(strtmp, "\n");
	}
	ShowPlayerDialogEx(playerid, DIALOG_ID_ELEVATOR, DIALOG_STYLE_LIST, "Elevator", strtmp, "Accept", "Cancel");
	return 1;
}



stock elevator_OnPlayerPickUp(playerid, pickupid)
{
 	#pragma unused pickupid
 	
	if(IsPlayerInRangeOfPoint(playerid, 2.1, -1816.4215,585.4880,35.2703)	||
			IsPlayerInRangeOfPoint(playerid, 2.1, -1816.3951,585.4965,235.6703))
	{   //для лифта //lift
		GameTextForPlayerEx(playerid, "~g~Elevator", 2500, 3);
        if(gLiftStatus == 0)
        {
			gLiftStatus = 1;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Лифт поднимается вверх");
			MoveObjectEx(oLift,-1813.0000,585.5000,236.1000,2.0);
			//PlaySoundForObject(oLift, SOUND_SHUTTER_DOOR_SLOW_START);
			PlaySoundForObject(oLift, SOUND_LIFT_LOOP);
		}
		else
		{
			gLiftStatus = 0;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Лифт опускается вниз");
			MoveObjectEx(oLift,-1813.0000,585.5000,35.7000,2.0);
			//PlaySoundForObject(oLift, SOUND_SHUTTER_DOOR_SLOW_START);
			PlaySoundForObject(oLift, SOUND_LIFT_LOOP);
		}
		//return 1;
	}
}




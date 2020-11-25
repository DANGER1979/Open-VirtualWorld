/*
 *            VW_FBI v1.0
 *       (c) Copyright 2009-2020 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (danger1979@mail.ru)
 * @date      : 19.05.2020
 * @update    : 19.05.2020
 *
 * This file is provided as is (no warranties).
 *
 */

#include <a_samp>

new fbr_actor;
new Text3D:fbr_text;

new fix_fbi_spam[MAX_PLAYERS];
new FBI_info_door;
new FBI_info_door_1;

const max_fbi_obj = 19;
new FBI_object[max_fbi_obj];
new FBI_OBJECT_INFO[max_fbi_obj];//тригер

//пикапы лифта только координаты
#define PICKUP_FBI_PARK -2500.6821,526.4040,2556.0002
#define PICKUP_FBI_0 -2485.6914,527.7474,1054.7067
#define PICKUP_FBI_1 -2485.8547,527.7435,54.7067
#define PICKUP_FBI_2 -2486.2859,527.7953,74.7067



//{19134, 23, FBI_PARK, 9, "FBI Парковка", 0xBFF600FF, 60.0, 0},//65 //int24 // пикап лифта парковка
//{19135, 23, FBI_0, 10, "FBI Цокольный этаж", 0xBFF600FF, 60.0, 0},//int20  // пикап лифта 0 этаж
//{19135, 23, FBI_1, 11, "FBI Первый этаж", 0xBFF600FF, 60.0, 0},//int21 // пикап лифта 1 этаж
//{1318, 23, FBI_2, 12, "FBI Второй этаж", 0xBFF600FF, 60.0, 0},//int22  // пикап лифта 2 этаж

static const stock Float:Turnstile[][] = //координаты 3д текстов
{//turnstile - турникет
	{-2459.4885, 526.2885, 54.5687, 88.5538},
	{-2459.4868, 527.8027, 54.5687, 88.5538},
	{-2459.4827, 529.3448, 54.5687, 88.5538},
	{-2462.1028, 529.3026, 54.5687, 272.4589},
	{-2462.1028, 527.8060, 54.5687, 272.4589},
	{-2462.1030, 526.2899, 54.5687, 272.4589}
};//-2462.1052,526.2410,54.5687

//3850 FBI_object[0] Стекло КПП, перемещать под землю вниз по нажатию кнопки (прим.)
//3089 FBI_object[1-3] - дверь деревянная в конференц зал, комнату зама и комнату директора (открывать по желанию на 90 градусов по оси Z)
//1557 FBI_object[4-9] - дверь в оружейку, комнату опознаний (дверь перемещать в стену)

//3089 FBI_object[11-12] - дверь деревянная в конференц зал, комнату зама и комнату директора (открывать по желанию на 90 градусов по оси Z)

//1557 FBI_object[13-15] - двери в допросную
//19302 FBI_object[16-17] - двери камер
//2990 FBI_object[18] - ворота, опускать ВНИЗ

// -- актеры на сиденьях
/*enum FBI_object_INFO
{
	Float:fbiDist,//0 растояние для проверки
//IsPlayerInRangeOfPoint первое место проверки
	Float:fbiX1,//1
	Float:fbiY1,
	Float:fbiZ1,
//IsPlayerInRangeOfPoint второе место проверки
	Float:fbiX2,//4
	Float:fbiY2,
	Float:fbiZ2,

//MoveObjectEx исходные координаты по умолчанию
	Float:fXfbi,//7
	Float:fY,
	Float:fZ,
	Float:frXfbi,//10
	Float:frY,
	Float:frZ,
	
//MoveObjectEx координаты на открытие
	Float:fX,//13
	Float:fY,
	Float:fZ,
	Float:frX,//16
	Float:frY,
	Float:frZ//18
}*/
static const stock Float:FBI_object_moved[max_fbi_obj][] =
{
//на этаже 1
	//стекло
	{1.5, -2460.719970, 527.817382, 54.034049, 	-2460.719970, 527.817382, 54.034049, 	-2460.719970, 527.817382, 54.034049, 0.000000, 0.000012, 179.999954, /* */ -2460.7200, 527.8174, 53.0101, 0.000000, 0.000012, 179.999954}, // -
//3089 FBI_object[1-3] - дверь деревянная в конференц зал, комнату зама и комнату директора (открывать по желанию на 90 градусов по оси Z)
	{1.5, -2463.158935, 531.774169, 54.896751,	-2463.158935, 531.774169, 54.896751, 	-2463.158935, 531.774169, 54.896751, 0.000000, 0.000000, -90.000000, /* */ -2463.158935, 531.774169, 54.896751, 0.000000, 0.000000, 0.0}, // -
	{2.0, -2470.291015, 531.774169, 54.896751,	-2470.291015, 531.774169, 54.896751, 	-2470.291015, 531.774169, 54.896751, 0.000000, 0.000007, -90.000000,/* */-2470.291015, 531.774169, 54.896751, 0.000000, 0.000007,  0.0}, // -
	{2.5, -2479.919677, 531.774169, 54.896751,	-2479.919677, 531.774169, 54.896751, 	-2479.919677, 531.774169, 54.896751, 0.000000, 0.000007, -90.000000,/* */-2479.919677, 531.774169, 54.896751, 0.000000, 0.000007,  0.0}, // -
//1557 FBI_object[4-9] - дверь в оружейку, комнату опознаний (дверь перемещать в стену)
//опознаний
	{1.0, -2478.798339, 523.861633, 54.856712, 	-2478.798339, 523.521301, 54.856712, 	-2476.847900, 523.789978, 53.566722, 0.000000, 0.000000, 900.000000, /* */-2476.847900, 523.789978, 53.566722, 0.000000, 0.000000, 90.000000}, // +
//оружейная
	{1.0, -2465.973632, 523.861633, 54.856712, 	-2465.973632, 523.511413, 54.856712, 	-2464.018310, 523.789978, 53.566722, 0.000000, 0.000000, 900.000000,/* */-2464.018310, 523.789978, 53.566722, 0.000000, 0.000000, 90.000000}, // +
//на лестницу
	{1.0, -2483.489257, 522.441162, 54.856712, 	-2483.429199, 522.260986, 54.856712, 	-2481.557861, 522.359985, 53.566722, 0.000000, -0.000007, 179.999954,/* */-2481.557861, 522.359985, 53.566722, 0.000000, -0.000007, 90.0}, // +

	{2.0, -2467.378173, 521.119934, 53.566722,	-2467.378173, 521.119934, 53.566722, 	-2467.378173, 521.119934, 53.566722, 0.000000, 0.000000, 810.000000,/* */-2467.378173, 521.119934, 53.566722, 0.000000, 0.000000,  0.0}, // -
	{2.0, -2464.018310, 513.989074, 53.566722,	-2464.018310, 513.989074, 53.566722, 	-2464.018310, 513.989074, 53.566722, 0.000000, 0.000000, 810.000000,/* */-2464.018310, 513.989074, 53.566722, 0.000000, 0.000000, 180.000000},// -
	{2.0, -2480.518798, 519.970214, 53.566722,	-2480.518798, 519.970214, 53.566722, 	-2480.518798, 519.970214, 53.566722, 0.000000, 0.000000, 990.000000,/* */-2480.518798, 519.970214, 53.566722, 0.000000, 0.000000, 0.0}, // -
//лестница на этаже 1 FBI_object[10]
	{2.0, -2481.627929, 522.339965, 50.076770,	-2481.627929, 522.339965, 50.076770, 	-2481.627929, 522.339965, 50.076770, 0.000000, -0.000007, 179.999954,/* */-2481.627929, 522.339965, 50.076770, 0.000000, -0.000007, 179.999954}, // -
//-------------------------------------------------------------------------------
//на этаже 2
//3089 FBI_object[11-12] - дверь деревянная в конференц зал, комнату зама и комнату директора (вращаем  на 90 градусов по оси Z)
	{1.5, -2479.488281, 524.031799, 74.856712,	-2479.488281, 524.031799, 74.856712, 	-2477.623779, 523.937377, 74.910736, 0.000000, 0.000000, 89.999847, -2477.623779, 523.937377, 74.910736, 0.000000, 0.000000, 178.7869/* */}, // +
	{2.0, -2467.923828, 526.587585, 74.910659,	-2467.923828, 526.587585, 74.910659, 	-2467.923828, 526.587585, 74.910659, -0.000014, 0.000014, -179.999923,/* */-2467.923828, 526.587585, 74.910659, -0.000014, 0.000014, -90.0}, // -
//-------------------------------------------------------------------------------
//на этаже 0
//1557 FBI_object[13-15] - двери в допросную  (вращаем  на 90 градусов по оси Z)
	{2.0, -2481.557861, 522.390014, 1053.566772,-2481.557861, 522.390014, 1053.566772, 		-2481.557861, 522.390014, 1053.566772, 0.000000, -0.000007, 179.999954, /* */-2481.557861, 522.390014, 1053.566772, 0.000000, -0.000007, 90.0}, // -
//в смотровую
	{1.0, -2478.683837, 523.911315, 1054.775756, 	-2478.683837, 523.550964, 1054.7757567, -2476.757080, 523.780334, 1053.566772, 0.000000, -0.000007, 179.999954,/* */-2476.757080, 523.780334, 1053.566772, 0.000000, -0.000007, 90.0}, // 14 +
//в допросную
	{1.0, -2472.301757, 523.911315, 1054.775756, 	-2472.301757, 523.550964, 1054.775756, 	-2470.355957, 523.770324, 1053.566772, 0.000000, -0.000007, 179.999954,/* */-2470.355957, 523.770324, 1053.566772, 0.000000, -0.000007, 90.0}, // 15
//19302 FBI_object[16-17] - двери камер сдвигаем на +0.09 по оси Z) 	
	{2.0, -2476.965087, 531.541015, 1054.805664, -2476.965087, 531.541015, 1054.805664, 	-2476.965087, 531.541015, 1054.805664, 0.000000, 0.000022, 0.000000,/* */-2478.315087, 531.541015, 1054.8056647, 0.000000, 0.000022, 0.000000}, // 16
	{2.0, -2472.092773, 531.541015, 1054.805664, -2472.092773, 531.541015, 1054.805664, 	-2472.092773, 531.541015, 1054.805664, 0.000000, 0.000037, 0.000000,/* */-2473.442773, 531.541015, 1054.805664, 0.000000, 0.000037, 0.000000}, // 17

//на улице
//2990 FBI_object[18] - ворота, опускать ВНИЗ
	{3.0, -2433.505615, 496.668151, 31.452394, 	-2433.505615, 496.668151, 31.452394, 	-2433.505615, 496.668151, 31.452394, 0.000000, 0.000000, 384.199981,/* */-2433.505615, 496.668151, 25.0912, 0.000000, 0.000000, 384.199981}
};
/*
	FBI_SF_PARK = 24,
	FBI_SF_WORLD0 = 20,
	FBI_SF_WORLD1 = 21,
	FBI_SF_WORLD2 = 22,
*/
stock fbi_OnGameModeInit()
{
	new time = GetTickCount();
	
	fbr_text = Text3D:-1;

/*	new tmpobjid, object_world = -1, object_int = -1;
	#include "../include/mapping/FBI/fbi_0"
	#include "../include/mapping/FBI/fbi_1"
	#include "../include/mapping/FBI/fbi_2"
	#include "../include/mapping/FBI/fbi_ex"
	#include "../include/mapping/FBI/fbi_park"

	// фикс текста фбр
	object_int = -1;
*/

    Create3DTextLabelEx("Заезд в гараж\nПосигнальте", -1, -2438.5261,513.1401,29.9120, 5.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1, 0);//0
    Create3DTextLabelEx("Выезд из гаража\nПосигнальте",-1, -2530.3445,503.3726,2555.5740, 5.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1, FBI_SF_PARK);//24

//------------------------------------------------------------------------------
//Актёры без 3D текста
    fbr_actor = CreateDynamicActorExY("{EE66EE}Получить оружие{FFFFFF}\nНажмите {FF0000}Y{FFFFFF} для взаимодействия",267,
		-2468.5881,518.8029,54.6642,272.7718, false, 80.0, FBI_SF_WORLD1, 0);//21
    ///fbr_actor = CreateDynamicActor(267, -2468.5881,518.8029,54.6642,272.7718, true, 100.0, 21);// В участе фбр оружейка
	//Create3DTextLabelEx("Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, -2466.8452,518.6932,54.5687, 5.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1, 21); //21 FBI сдать табельное оружие
    ApplyActorAnimation(fbr_actor, "PED", "SEAT_DOWN",4.1, 0, 0, 0, 1, 0);


	for(new i; i < 6; i ++)
	{//создаём турникет
	    Create3DTextLabelEx("Приложить пропуск\n{857547}Нажмите Y",-1,
			Turnstile[i][0],Turnstile[i][1],Turnstile[i][2], 5.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0, FBI_SF_WORLD1);//21
	}

	printf("14/19. [Загрузка FBI_object_moved]: Было загружено - %d, потрачено - %d (ms)", max_fbi_obj, GetTickCount() - time);//new time = GetTickCount();
	return 1;
}

stock fbi_OnPlayerConnect(playerid)
{
 	fix_fbi_spam[playerid] = -1;
}

	// пикапы FBI
//	CreatePickup(1318, 23, -2456.1482,503.9088,30.0781, 0); // пикап входа в фби
//	CreatePickup(1318, 23, -2450.5330,514.8558,54.5697, 21); // пикап выхода в фби
//	CreatePickup(1318, 23, -2482.3772,521.9155,51.0857, 21); // пикап который ведет на 0 этаж
//	CreatePickup(1318, 23, -2482.3713,522.8125,1054.5657, 20); // пикап который с 0 ведет на 1 этаж

stock fbi_OnPlayerPickUp(playerid, pickupid)
{
 	#pragma unused pickupid

	if(	IsPlayerInRangeOfPoint(playerid, 2.1, PICKUP_FBI_PARK) ||//-2500.6821,526.4040,2556.0002) ||//парковка
		IsPlayerInRangeOfPoint(playerid, 2.1, PICKUP_FBI_0) ||//-2485.6914,527.7474,1054.7067) ||//цокольный этаж
		IsPlayerInRangeOfPoint(playerid, 2.1, PICKUP_FBI_1) ||//-2485.8547,527.7435,54.7067) ||//этаж 1
		IsPlayerInRangeOfPoint(playerid, 2.1, PICKUP_FBI_2) )//-2486.2859,527.7953,74.7067) )//этаж 2
	{
		new msgitem[] = "Парковка\nЦокольный этаж\nЭтаж 1\nЭтаж 2";//\n\nНажмите Accept, чтобы принять.
		ShowPlayerDialogEx(playerid, FBI_DIALOG, DIALOG_STYLE_LIST, "Лифт в ФБР", msgitem, "Перейти", "Отмена");
		//return 1;
	}
}

stock fbi_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	fbi2_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);

	#pragma unused inputtext
	if(dialogid != FBI_DIALOG) return 1;

	//PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);//выбор этажа
	PlaySoundForPlayer(playerid, SOUND_LIFT_START);//выбор этажа
	//SetPlayerPosEx(playerid, plocx,plocy,plocz, ploca);
	
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response) return 1;



	//new Float:plocx,Float:plocy,Float:plocz,Float:ploca;
	if(listitem == 0)//Level -2 //int24 // пикап лифта парковка
	{
		SetPlayerPosEx(playerid, PICKUP_FBI_PARK, 0.0);//-2500.6821,526.4040,2556.0002, 0.0);
		PlayerInfo[playerid][pLocal] = 24;
		SetPlayerVirtualWorldEx(playerid, FBI_SF_PARK);//24
		SetPlayerInteriorEx(playerid, 0);
	}
	else if(listitem == 1)//Level -1 //int20  // пикап лифта 0 этаж
	{
	//ACP_SetPlayerPos(playerid, 1485.7433,-1748.6017,106.1200);
		//SetPlayerFacingAngle(playerid,0.0);
		SetPlayerPosEx(playerid, PICKUP_FBI_0, 0.0);//-2485.6914,527.7474,1054.7067, 0.0);
		PlayerInfo[playerid][pLocal] = 20;
		SetPlayerVirtualWorldEx(playerid, FBI_SF_WORLD0);//DoJ+1);
		SetPlayerInteriorEx(playerid, 0);
	}
//{19134, 23, -2500.6821,526.4040,2556.0002, FBI-2, "1 этаж\n2 этаж\nПарковка", 0xBFF600FF, 60.0, 0},//65 //int24 // пикап лифта парковка
//{19135, 23, -2485.6914,527.7474,1054.7067, FBI-1, "Цокольный этаж\n1 этаж\n2 этаж", 0xBFF600FF, 60.0, 0},//int20  // пикап лифта 0 этаж
//{19135, 23, -2485.8547,527.7435,54.7067, FBI, "Цокольный этаж\n2 этаж\nПарковка", 0xBFF600FF, 60.0, 0},//int21 // пикап лифта 1 этаж
//{1318, 23, -2486.2859,527.7953,74.7067, FBI+1, "1 этаж\nЦокольный этаж\nПарковка", 0xBFF600FF, 60.0, 0},//int22  // пикап лифта 2 этаж
	else if(listitem == 2)//Level 0 //int21 // пикап лифта 1 этаж
	{
		SetPlayerPosEx(playerid, PICKUP_FBI_1, 0.0);//-2485.8547,527.7435,54.7067, 0.0);
		PlayerInfo[playerid][pLocal] = 21;
		SetPlayerVirtualWorldEx(playerid, FBI_SF_WORLD1);
		SetPlayerInteriorEx(playerid, 0);
	}
	else if(listitem == 3)//Level +1 //int22  // пикап лифта 2 этаж
	{
		SetPlayerPosEx(playerid, PICKUP_FBI_2, 0.0);//-2486.2859,527.7953,74.7067, 0.0);
		PlayerInfo[playerid][pLocal] = 22;
		SetPlayerVirtualWorldEx(playerid, FBI_SF_WORLD2);
		SetPlayerInteriorEx(playerid, 0);
	}
	return 1;
}

stock fbi2_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	#pragma unused listitem
	if(dialogid != FBI_DIALOG2) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response) return 1;
	if(GetPVarInt(playerid, "AmmoFBR"))
	{
		ResetPlayerWeaponsEx(playerid);
		SetPlayerArmourEx(playerid, 0.0);
		PlayerTextDrawHide(playerid, txdPlayerArmour[playerid]);
		PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
		format(strings, sizeof(strings), "* Офицер %s сдал Оружие.", PlayerName(playerid));
		ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		DeletePVar(playerid, "AmmoFBR");
	}
	else
	{
		if(gOnDuty[playerid] == 0)
		{
		    if(fbr_text == Text3D:-1)
		    {
			    fbr_text = Create3DTextLabelEx("Сперва переоденьтесь и заступите на службу!",-1,  -2468.5881,518.8029,54.6642 + 1,10.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1, -1);
				SetTimer("@del_fbr_text", 5000, false);
				ApplyAnimation(playerid, "CARRY","crry_prtial",4.0,0,0,0,0,0,1);
				ApplyActorAnimation(fbr_actor, "PED", "IDLE_CHAT", 4.1, 0, 0, 0, 1, 1);
			}
			SendClientMessage(playerid, COLOR_ERROR, "Сперва переоденьтесь и заступите на службу!");
			return 1;
		}
		SetPVarInt(playerid, "AmmoFBR", 1);
		format(strings, sizeof(strings), "* Офицер %s получил оружие.", PlayerName(playerid));
		ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		OnPlayerSetDutyWeapons(playerid);//запускаем ф-ию установки членам фракций оружия при спауне,
	}
	return 1;
}


stock fbi_OnPlayerKey_DRIVER(playerid)
{//если игрок посигналил
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;
    //if(PlayerInfo[playerid][pVirtual] != 0) return 1;
    //if(IsPlayerControllable[playerid] == 1) return 1;
    
	/*if(IsPlayerInRangeOfPoint(playerid, 3.0, 1041.5198,-1026.6521,32.1016))
	{
		ADD_NUMBER_CAR(playerid);
	}*/
    if(fix_fbi_spam[playerid] < gettime())
    {
	    //if(PlayerInfo[playerid][pMember] != FBI) return 1;
    	new i = 18;
		if(IsPlayerInRangeOfPoint(playerid, 5.0, FBI_object_moved[i][0 + 1], FBI_object_moved[i][1+ 1], FBI_object_moved[i][2+ 1]))
		{
			if(FBI_info_door_1 == 1) return 1;
			//MoveObjectEx(FBI_object[18], -2433.505615,496.668151,25.0912,0.4, 0.000000,0.000000,384.199981);//2990 FBI_object[18] - ворота, опускать ВНИЗ
			MoveObjectEx(FBI_object[i],	FBI_object_moved[i][6 + 7], FBI_object_moved[i][7 + 7], FBI_object_moved[i][8 + 7], 0.5,//2990 FBI_object[18] - ворота, опускаем ВНИЗ
										FBI_object_moved[i][9 + 7], FBI_object_moved[i][10 + 7], FBI_object_moved[i][11 + 7]);
			SetTimer("@FBI_OBJECT_DOOR_1", 40000, false);//через 40 сек закрываем
	        fix_fbi_spam[playerid] = gettime() + 2;//добавляем к текущему времени 2 сек
		}
	}
	if(IsPlayerInRangeOfPoint(playerid, 3.0,-2438.4832,513.7590,29.9063)) // заезд с улицы в ФБР
	{
	    //записываем в координаты спауна при входе
		PlayerInfo[playerid][pPos_x] = -2438.4832,
		PlayerInfo[playerid][pPos_y] = 513.7590,
		PlayerInfo[playerid][pPos_z] = 29.9063;
			
	    //if(PlayerInfo[playerid][pMember] != FBI) return 1;
	    new car = GetPlayerVehicleID(playerid);
	    SetVehicleVirtualWorldEx(car, FBI_SF_PARK);
	    LinkVehicleToInteriorEx(car, 0);
	    SetVehiclePosEx(car, -2517.7698,502.8300,2555.5664);
	    SetVehicleZAngleEx(car, 0.7935);
	    
	    SetPlayerInteriorEx(playerid, 0);
	    SetPlayerVirtualWorldEx(playerid, FBI_SF_PARK);
	}
	if(IsPlayerInRangeOfPoint(playerid, 3.0,-2530.3445,503.3726,2555.5740)) // выезд из ФБР
	{
	    //if(PlayerInfo[playerid][pMember] != FBI) return 1;
	    new car = GetPlayerVehicleID(playerid);
	    SetVehicleVirtualWorldEx(car, 0);
	    LinkVehicleToInteriorEx(car, 0);
	    SetVehiclePosEx(car, -2442.7283,513.0546,29.6232);
	    SetVehicleZAngleEx(car, 186);
	    
	    SetPlayerInteriorEx(playerid, 0);
	    SetPlayerVirtualWorldEx(playerid, 0);
	}
	return 1;
}

@del_fbr_text();
@del_fbr_text()
{
	if(fbr_text != Text3D:-1)
	{
		DestroyDynamic3DTextLabel(fbr_text);
		fbr_text = Text3D:-1;
	}
	return 1;
}

stock fbi_OnPlayerKeyState_YES(playerid)
{
    if(IsPlayerInRangeOfPoint(playerid, 3.0, -2466.8452,518.6932,54.5687))
    {
        if(PlayerInfo[playerid][pMember] == FBI)
        {
			if(GetPVarInt(playerid, "AmmoFBR"))
			{
			    ShowPlayerDialogEx(playerid, FBI_DIALOG2, DIALOG_STYLE_MSGBOX, " ", "Желаете сдать табельное оружие?", "Да", "Нет");
				return 1;
			}
			else
			{
				if(gOnDuty[playerid] == 0)
				{
				    if(fbr_text == Text3D:-1)
				    {
					    fbr_text = Create3DTextLabelEx("Сперва переоденьтесь и заступите на службу!",-1,  -2468.5881,518.8029,54.6642 + 1,10.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1, -1);
						SetTimer("@del_fbr_text", 5000, false);
					}
					SendClientMessage(playerid, COLOR_ERROR, "Сперва переоденьтесь и заступите на службу!");
					return 1;
				}
				SetPVarInt(playerid, "AmmoFBR", 1);
				format(strings, sizeof(strings), "* Офицер %s получил оружие.", PlayerName(playerid));
				ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
				OnPlayerSetDutyWeapons(playerid);//запускаем ф-ию установки членам фракций оружия при спауне,
			}
        }
    }

//------------------------------------------------------------------------------
    if(fix_fbi_spam[playerid] > gettime()) return 1;

	/*if( IsPlayerInRangeOfPoint(playerid, 0.5, -2462.1052,526.2410,54.5687 ) ||
		IsPlayerInRangeOfPoint(playerid, 0.5, -2462.1028,527.7969,54.5687) ||
		IsPlayerInRangeOfPoint(playerid, 0.5, -2462.1030,529.2991,54.5687) ||
		IsPlayerInRangeOfPoint(playerid, 0.5, -2459.4880,529.3116,54.5687) ||
		IsPlayerInRangeOfPoint(playerid, 0.5, -2459.4885,527.8669,54.5687) ||
		IsPlayerInRangeOfPoint(playerid, 0.5, -2459.4885,526.2803,54.5687))*/
	for(new i; i < 6; i ++)
	{//турникет
		if( IsPlayerInRangeOfPoint(playerid, 0.5, Turnstile[i][0],Turnstile[i][1],Turnstile[i][2]))
	  	{//если стоим у место нажатия Y
	   		if(FBI_info_door == 1) return 1;//3850 FBI_object[0] Стекло КПП, перемещать под землю вниз по нажатию кнопки (прим.)
			MoveObjectEx(FBI_object[0],	FBI_object_moved[0][6 + 7], FBI_object_moved[0][7 + 7], FBI_object_moved[0][8 + 7], 0.20,
										FBI_object_moved[0][9 + 7], FBI_object_moved[0][10 + 7], FBI_object_moved[0][11 + 7]);
			SetTimer("@FBI_OBJECT_DOOR", 12000, false);
			ApplyAnimation(playerid,"CRIB","CRIB_Use_Switch",4.0,0,0,0,0,0);
			FBI_info_door = 1;
			return 1;
		}
	}
	for(new i; i < max_fbi_obj; i ++)
	{
		if(	IsPlayerInRangeOfPoint(playerid, FBI_object_moved[i][0], FBI_object_moved[i][0+ 1], FBI_object_moved[i][1+ 1], FBI_object_moved[i][2+ 1]) ||
			IsPlayerInRangeOfPoint(playerid, 0.8, FBI_object_moved[i][3+ 1], FBI_object_moved[i][4+ 1], FBI_object_moved[i][5+ 1]))
		{
		    if(i == 13) return 1;
		    if(i == 0) //3850 FBI_object[0] Стекло КПП, перемещать под землю вниз по нажатию кнопки (прим.)
		    {
		        return 1;
		    }
		    if(PlayerInfo[playerid][pMember] != 11) return 1;
	        FBI_OBJECT_INFO[i] = !FBI_OBJECT_INFO[i];
	        if(i == 11 || i == 12)
	        {//3089 FBI_object[11-12] - дверь деревянная в конференц зал, комнату зама и комнату директора (открывать по желанию на 90 градусов по оси Z)
	            //if(PlayerInfo[playerid][pRank] < 10) return SendErr(playerid, "Доступно с 10 ранга");
				if(i == 11) PlaySoundForPlayer(playerid, SOUND_KEYPAD_PASS);
		        switch(FBI_OBJECT_INFO[i])
		        {
		            case 0: MoveObjectEx(FBI_object[i],	FBI_object_moved[i][0 + 7], FBI_object_moved[i][1 + 7], FBI_object_moved[i][2 + 7], 0.001,
														FBI_object_moved[i][3 + 7], FBI_object_moved[i][4 + 7], FBI_object_moved[i][5 + 7]);
					case 1: MoveObjectEx(FBI_object[i],	FBI_object_moved[i][6 + 7], FBI_object_moved[i][7 + 7], FBI_object_moved[i][8 + 7], 0.001,
														FBI_object_moved[i][9 + 7], FBI_object_moved[i][10 + 7], FBI_object_moved[i][11 + 7]);
		        }
		        ApplyAnimation(playerid,"CRIB","CRIB_Use_Switch",4.0,0,0,0,0,0);
	        }
			else if(i == 16 || i == 17)
			{//19302 FBI_object[16-17] - двери камер
		        switch(FBI_OBJECT_INFO[i])
		        {
		            case 0: MoveObjectEx(FBI_object[i],	FBI_object_moved[i][0 + 7], FBI_object_moved[i][1 + 7], FBI_object_moved[i][2 + 7]+0.09, 0.5,
														FBI_object_moved[i][3 + 7], FBI_object_moved[i][4 + 7], FBI_object_moved[i][5 + 7]);
					case 1: MoveObjectEx(FBI_object[i],	FBI_object_moved[i][6 + 7], FBI_object_moved[i][7 + 7], FBI_object_moved[i][8 + 7]-0.09, 0.5,
														FBI_object_moved[i][9 + 7], FBI_object_moved[i][10 + 7], FBI_object_moved[i][11 + 7]);
		        }
		        ApplyAnimation(playerid,"CRIB","CRIB_Use_Switch",4.0,0,0,0,0,0);
			}
	        else
	        {
//3089 FBI_object[1-3] - дверь деревянная в конференц зал, комнату зама и комнату директора (открывать по желанию на 90 градусов по оси Z)
//1557 FBI_object[4-9] - дверь в оружейку, комнату опознаний (дверь перемещать в стену)

//1557 FBI_object[13-15] - двери в допросную
//2990 FBI_object[18] - ворота, опускать ВНИЗ
				new Float: speed = 0.1;
				if(i >= 4 && i <= 6) { PlaySoundForPlayer(playerid, SOUND_KEYPAD_PASS); speed = 0.03; }
				if(i >= 14 && i <= 15) { PlaySoundForPlayer(playerid, SOUND_KEYPAD_PASS);  speed = 0.03;}

		        switch(FBI_OBJECT_INFO[i])
		        {
		            case 0: MoveObjectEx(FBI_object[i],	FBI_object_moved[i][0 + 7], FBI_object_moved[i][1 + 7], FBI_object_moved[i][2 + 7]+0.03, speed,
														FBI_object_moved[i][3 + 7], FBI_object_moved[i][4 + 7], FBI_object_moved[i][5 + 7]);
					case 1: MoveObjectEx(FBI_object[i],	FBI_object_moved[i][6 + 7], FBI_object_moved[i][7 + 7], FBI_object_moved[i][8 + 7]-0.03, speed,
														FBI_object_moved[i][9 + 7], FBI_object_moved[i][10 + 7], FBI_object_moved[i][11 + 7]);
		        }
		        ApplyAnimation(playerid,"CRIB","CRIB_Use_Switch",4.0,0,0,0,0,0);
			}
	        fix_fbi_spam[playerid] = gettime() + 2;
	        return 1;
		}
	}
	return 1;
}


/*
stock fbi_SecondTimer(playerid) // секундный таймер
{
	if(PlayerInfo[playerid][pFBIUnlock] != 0)
	{
	    PlayerInfo[playerid][pFBIUnlock] --;
	    if(PlayerInfo[playerid][pFBIUnlock] == 0)
	    {
	        SendClientMessage(playerid, 0xAD9B5FFF, "Внимание: пропуск в здание ФБР теперь не действителен");
	    }
	}
}*/

stock fbi_OnObjectMoved(objectid)
{
	StopObjectEx(objectid);
}

@FBI_OBJECT_DOOR();
@FBI_OBJECT_DOOR()
{//3850 FBI_object[0] Стекло КПП, перемещать под землю вниз по нажатию кнопки (прим.)
    MoveObjectEx(FBI_object[0],	FBI_object_moved[0][0 + 7], FBI_object_moved[0][1+ 7], FBI_object_moved[0][2+ 7], 0.1,
								FBI_object_moved[0][3+ 7], FBI_object_moved[0][4+ 7], FBI_object_moved[0][5+ 7]);
    FBI_info_door = 0;
}

@FBI_OBJECT_DOOR_1();
@FBI_OBJECT_DOOR_1()
{
//2990 FBI_object[18] - поднимаем ворота
	new i = 18;
	MoveObjectEx(FBI_object[i],	FBI_object_moved[i][0 + 7], FBI_object_moved[i][1 + 7], FBI_object_moved[i][2 + 7], 0.4,
								FBI_object_moved[i][3 + 7], FBI_object_moved[i][4 + 7], FBI_object_moved[i][5 + 7]);
    FBI_info_door_1 = 0;
}

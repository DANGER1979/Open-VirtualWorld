/*
 *            vw_tuning v1.0
 *       (c) Copyright 2008-2024 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (danger1979@mail.ru)
 * @date      : 1.01.2009
 * @update    : 13.11.2018
 *
 * This file is provided as is (no warranties).
 * это библиотека не обязательна
 * это просто добавляет возможность в любом месте тюнинговать тачку
 */
 

//##############################################################################//
//                                                                              //
//                             СИСТЕМА ТЮНИНГА АВТО                             //
//                                                                              //
//##############################################################################//
 
//для тюнинга начало
#define MAX_COMP 21
//----------Part------------
#define ModelVeh 0//418 - модель машины
#define Colors1 1//-1 - основной цвет машины
#define Colors2 2//-1 - дополнительный цвет машины
#define PaintJob 3
#define Nitro 4
#define Wheels 5
#define Hydraulics 6
#define Spoiler 7
#define Front_Bumper 8
#define Rear_Bumper 9
#define Sideskirt 10
#define Roof 11
#define Exhaust 12
#define Bullbars_Front 13
#define Bullbars_Rear 14
#define Hood 15
#define Vents 16
#define Lamps 17
#define Sign_Front 18
#define Stereos 19
#define Neons 20

/*0 - CARMODTYPE_SPOILER
1 - CARMODTYPE_HOOD
2 - CARMODTYPE_ROOF
3 - CARMODTYPE_SIDESKIRT
4 - CARMODTYPE_LAMPS
5 - CARMODTYPE_NITRO
6 - CARMODTYPE_EXHAUST
7 - CARMODTYPE_WHEELS
8 - CARMODTYPE_STEREO
9 - CARMODTYPE_HYDRAULICS
10 - CARMODTYPE_FRONT_BUMPER
11 - CARMODTYPE_REAR_BUMPER
12 - CARMODTYPE_VENT_RIGHT
13 - CARMODTYPE_VENT_LEFT*/

//----------Cars------------
//#define None 0
//#define Trans_Fender 1
//#define Loco_Low_Co 2
//#define Wheel_Arch_Angels 3
//#define Standard 4 //можно установить цвет нитро колёса гидравлику стерео
#define Most_cars 5
//Lowriders
#define Remington 534
#define Slamvan 535
#define Blade 536
#define Savanna 567
#define Broadway 575
#define Tornado 576
//Tahoma, Voodoo
//Racing Vehicles
#define Uranus 558
#define Jester 559
#define Sultan 560
#define Stratum 561
#define Elegy 562
#define Flash 565
//----------Type------------
#define Alien 1		//"Chrome"	"Chrome_Strip"	"Chrome_Arches"	"Chrome_Trim"	"Oval_Vents"    "Hardtop"
#define X-Flow 2	//"Slamin"  				"Chrome_Flames"	"Wheelcovers"	"Square_Vents"  "Softtop" "Covertible"
//для сохранения тюна
new tunColor1 = 0, tunColor2 = 0;


new Neon = 18647; //ид объекта Neon
new component_count, ComponentID[MAX_COMP], PaintjobID, Paid[MAX_PLAYERS][MAX_COMP];
//new Spoiler_Profi[] = { 405, 589 };
//new Spoiler_Win[] = { 401, 405, 410, 415, 439, 496, 603};
enum componentinfo
{
	compID,//4
	compModel[16],//16
	compPart,//2
	compType[12],
	compCars,//2
	compPrice//4
};
new ComponentArray[194][componentinfo] = {
{1000, "spl_b_mar_m",Spoiler, "Profi",Trans_Fender,400},//405 589
{1001, "spl_b_bab_m",Spoiler, "Win",Trans_Fender,550},//401 405 410 415 439 496 603
{1002, "spl_b_bar_m",Spoiler, "Drag",Trans_Fender,200},//404 418 496
{1003, "spl_b_mab_m",Spoiler, "Alpha",Trans_Fender,250},//401 410 415 439 496
{1004, "bnt_b_sc_m",Hood,	"Champ_Scoop",Trans_Fender,100},//Капот 401 478 589
{1005, "bnt_b_sc_l",Hood,	"Fury_Scoop",Trans_Fender,150},//Капот 401 478 589
{1006, "rf_b_sc_r",Roof,		"Roof_Scoop",Trans_Fender,80},//Крыша 401 418 477 496 589 603
{1007, "wg_l_b_ssk",Sideskirt,Alien,Trans_Fender,500},//Боковые юбки 401 404 410 415 422 439 477 496 589 603
{1008, "nto_b_l",Nitro,		"5_times",Most_cars,500},
{1009, "nto_b_s",Nitro,		"2_times",Most_cars,200},
{1010, "nto_b_tw",Nitro,		"10_times",Most_cars,1000},
{1011, "bnt_b_sc_p_m",Hood,	"Race_Scoop",Trans_Fender,220},//Капот 496
{1012, "bnt_b_sc_p_l",Hood,	"Worx_Scoop",Trans_Fender,250},//Капот 478
{1013, "lgt_b_rspt",Lamps,	"Round_Fog",Trans_Fender,100},//Фары 400 401 404 410 422 439 478 589
{1014, "spl_b_bar_l",Spoiler, "Champ",Trans_Fender,350},//405 542
{1015, "spl_b_bbr_l",Spoiler, "Race",Trans_Fender,500},//542
{1016, "spl_b_bbr_m",Spoiler, "Worx",Trans_Fender,200},//404 418 589
{1017, "wg_r_b_ssk",Sideskirt,X-Flow,Trans_Fender,100},//Боковые юбки  1
{1018, "exh_b_ts",Exhaust,	"Upswept",Trans_Fender,350},//Выхлоп 400 405 415 477 542 589 603
{1019, "exh_b_t",Exhaust,	"Twin",Trans_Fender,300},//Выхлоп 400 401 404 405 410 415 422 477 496 542 603
{1020, "exh_b_l",Exhaust,	"Large",Trans_Fender,250},//Выхлоп 400 401 404 405 410 418 422 477 478 496 542 589 603
{1021, "exh_b_m",Exhaust,	"Medium",Trans_Fender,200},//Выхлоп 400 404 405 410 418 422 477 478 542
{1022, "exh_b_s",Exhaust,	"Small",Trans_Fender,150},//Выхлоп 478
{1023, "spl_b_bbb_m",Spoiler, "Fury",Trans_Fender,350},//405 410 415 439 478 496 603
{1024, "lgt_b_sspt",Lamps,	"Square_Fog",Trans_Fender,50},//Фары 400 410 589 603
{1025, "wheel_or1",Wheels,	"Offroad",Most_cars,1000},//Trans_Fender
{1026, "wg_l_a_s",Sideskirt,Alien,Sultan,480},//0
{1027, "wg_r_a_s",Sideskirt,Alien,Sultan,480},//0
{1028, "exh_a_s",Exhaust,Alien,Sultan,770},
{1029, "exh_c_s",Exhaust,X-Flow,Sultan,680},
{1030, "wg_r_c_s",Sideskirt,X-Flow,Sultan,370},//1
{1031, "wg_l_c_s",Sideskirt,X-Flow,Sultan,370},//1
{1032, "rf_a_s",Roof,Alien,Sultan,170},
{1033, "rf_c_s",Roof,X-Flow,Sultan,120},
{1034, "exh_a_l",Exhaust,Alien,Elegy,790},
{1035, "rf_c_l",Roof,X-Flow,Elegy,150},
{1036, "wg_l_a_l",Sideskirt,Alien,Elegy,500},//0
{1037, "exh_c_l",Exhaust,X-Flow,Elegy,690},
{1038, "rf_a_l",Roof,Alien,Elegy,190},
{1039, "wg_l_c_l",Sideskirt,X-Flow,Elegy,390},//1
{1040, "wg_r_a_l",Sideskirt,Alien,Elegy,500},//0
{1041, "wg_r_c_l",Sideskirt,X-Flow,Elegy,390},//1
{1042, "wg_l_lr_br1",Sideskirt,Alien,Broadway,1000},//0
{1043, "exh_lr_br2",Exhaust,X-Flow,Broadway,500},
{1044, "exh_lr_br1",Exhaust,Alien,Broadway,500},
{1045, "exh_c_f",Exhaust,X-Flow,Flash,510},
{1046, "exh_a_f",Exhaust,Alien,Flash,710},
{1047, "wg_l_a_f",Sideskirt,Alien,Flash,670},//0
{1048, "wg_l_c_f",Sideskirt,X-Flow,Flash,530},//1
{1049, "spl_a_f_r",Spoiler,Alien,Flash,810},
{1050, "spl_c_f_r",Spoiler,X-Flow,Flash,620},
{1051, "wg_r_a_f",Sideskirt,Alien,Flash,810},//0
{1052, "wg_r_c_f",Sideskirt,X-Flow,Flash,530},//1
{1053, "rf_c_f",Roof,X-Flow,Flash,130},
{1054, "rf_a_f",Roof,Alien,Flash,210},
{1055, "rf_a_st",Roof,Alien,Stratum,930},
{1056, "wg_l_a_st",Sideskirt,Alien,Stratum,520},//0
{1057, "wg_l_c_st",Sideskirt,X-Flow,Stratum,430},//1
{1058, "spl_a_st_r",Spoiler,Alien,Stratum,620},
{1059, "exh_c_st",Exhaust,X-Flow,Stratum,720},
{1060, "spl_c_st_r",Spoiler,X-Flow,Stratum,530},
{1061, "rf_c_st",Roof,X-Flow,Stratum,180},
{1062, "wg_r_a_st",Sideskirt,Alien,Stratum,520},//0
{1063, "wg_r_c_st",Sideskirt,X-Flow,Stratum,430},//1
{1064, "exh_a_st",Exhaust,Alien,Stratum,830},
{1065, "exh_a_j",Exhaust,Alien,Jester,850},
{1066, "exh_c_j",Exhaust,X-Flow,Jester,550},
{1067, "rf_a_j",Roof,Alien,Jester,250},
{1068, "rf_c_j",Roof,X-Flow,Jester,200},
{1069, "wg_l_a_j",Sideskirt,Alien,Jester,550},//0
{1070, "wg_l_c_j",Sideskirt,X-Flow,Jester,440},//1
{1071, "wg_r_a_j",Sideskirt,Alien,Jester,550},//0
{1072, "wg_r_c_j",Sideskirt,X-Flow,Jester,440},//1
{1073, "wheel_sr6",Wheels, "Shadow",Most_cars,1100},
{1074, "wheel_sr3",Wheels, "Mega",Most_cars,1030},
{1075, "wheel_sr2",Wheels, "Rimshine",Most_cars,980},
{1076, "wheel_lr4",Wheels, "Wires",Most_cars,1560},
{1077, "wheel_lr1",Wheels, "Classic",Most_cars,1620},
{1078, "wheel_lr3",Wheels, "Twist",Most_cars,1200},
{1079, "wheel_sr1",Wheels, "Cutter",Most_cars,1030},
{1080, "wheel_sr5",Wheels, "Switch",Most_cars,900},
{1081, "wheel_sr4",Wheels, "Grove",Most_cars,1230},
{1082, "wheel_gn1",Wheels, "Import",Most_cars,820},
{1083, "wheel_lr2",Wheels, "Dollar",Most_cars,1560},
{1084, "wheel_lr5",Wheels, "Trance",Most_cars,1000},
{1085, "wheel_gn2",Wheels, "Atomic",Most_cars,770},
{1086, "stereo",Stereos, "Stereo",Most_cars,100},//401
{1087, "hydralics",Hydraulics, "Hydraulic",Most_cars,1500},
{1088, "rf_a_u",Roof,Alien,Uranus,150},
{1089, "exh_c_u",Exhaust,X-Flow,Uranus,650},
{1090, "wg_l_a_u",Sideskirt,Alien,Uranus,450},//0
{1091, "rf_c_u",Roof,X-Flow,Uranus,100},
{1092, "exh_a_u",Exhaust,Alien,Uranus,750},
{1093, "wg_l_c_u",Sideskirt,X-Flow,Uranus,350},//1
{1094, "wg_r_a_u",Sideskirt,Alien,Uranus,450},//0
{1095, "wg_r_c_u",Sideskirt,X-Flow,Uranus,350},//1
{1096, "wheel_gn3",Wheels, "Ahab",Most_cars,1000},
{1097, "wheel_gn4",Wheels, "Virtual",Most_cars,620},
{1098, "wheel_gn5",Wheels, "Access",Most_cars,1140},
{1099, "wg_r_lr_br1",Sideskirt,X-Flow,Broadway,1000},//1
{1100, "misc_c_lr_rem1",Bullbars_Front,Alien,Remington,940},
{1101, "wg_r_lr_rem1",Sideskirt,Alien,Remington,780},//0
{1102, "wg_r_lr_sv",Sideskirt,Alien,Savanna,830},//0
{1103, "rf_lr_bl2",Roof,X-Flow,Blade,3250},
{1104, "exh_lr_bl1",Exhaust,Alien,Blade,1610},
{1105, "exh_lr_bl2",Exhaust,X-Flow,Blade,1540},
{1106, "wg_l_lr_rem2",Sideskirt,X-Flow,Remington,780},//1
{1107, "wg_r_lr_bl1",Sideskirt,Alien,Blade,780},//0
{1108, "wg_l_lr_bl1",Sideskirt,X-Flow,Blade,780},//1
{1109, "bbb_lr_slv1",Bullbars_Rear,Alien,Slamvan,1610},
{1110, "bbb_lr_slv2",Bullbars_Rear,X-Flow,Slamvan,1540},
{1111, "bnt_lr_slv1",Sign_Front,Alien,Slamvan,100},
{1112, "bnt_lr_slv2",Sign_Front,X-Flow,Slamvan,100},
{1113, "exh_lr_slv1",Exhaust,Alien,Slamvan,3340},
{1114, "exh_lr_slv2",Exhaust,X-Flow,Slamvan,3250},
{1115, "fbb_lr_slv1",Bullbars_Front,Alien,Slamvan,2130},
{1116, "fbb_lr_slv2",Bullbars_Front,X-Flow,Slamvan,2050},
{1117, "fbmp_lr_slv1",Front_Bumper,Alien,Slamvan,1040},
{1118, "wg_l_lr_slv1",Sideskirt,Alien,Slamvan,780},//0
{1119, "wg_l_lr_slv2",Sideskirt,X-Flow,Slamvan,940},//1
{1120, "wg_r_lr_slv1",Sideskirt,Alien,Slamvan,780},//0
{1121, "wg_r_lr_slv2",Sideskirt,X-Flow,Slamvan,940},//1
{1122, "wg_l_lr_rem1",Sideskirt,Alien,Remington,780},//0
{1123, "misc_c_lr_rem2",Bullbars_Front,Alien,Remington,860},
{1124, "wg_r_lr_rem2",Sideskirt,X-Flow,Remington,780},//1
{1125, "misc_c_lr_rem3",Bullbars_Front,Alien,Remington,1120},
{1126, "exh_lr_rem1",Exhaust,Alien,Remington,3340},
{1127, "exh_lr_rem2",Exhaust,X-Flow,Remington,3250},
{1128, "rf_lr_bl1",Roof,Alien,Blade,3340},
{1129, "exh_lr_sv1",Exhaust,Alien,Savanna,1650},
{1130, "rf_lr_sv1",Roof,Alien,Savanna,3380},
{1131, "rf_lr_sv2",Roof,X-Flow,Savanna,3290},
{1132, "exh_lr_sv2",Exhaust,X-Flow,Savanna,1590},
{1133, "wg_l_lr_sv",Sideskirt,X-Flow,Savanna,830},//1
{1134, "wg_l_lr_t1",Sideskirt,Alien,Tornado,800},//0
{1135, "exh_lr_t2",Exhaust,X-Flow,Tornado,1500},
{1136, "exh_lr_t1",Exhaust,Alien,Tornado,1000},
{1137, "wg_r_lr_t1",Sideskirt,X-Flow,Tornado,800},//1
{1138, "spl_a_s_b",Spoiler,Alien,Sultan,580},
{1139, "spl_c_s_b",Spoiler,X-Flow,Sultan,470},
{1140, "rbmp_c_s",Rear_Bumper,X-Flow,Sultan,870},
{1141, "rbmp_a_s",Rear_Bumper,Alien,Sultan,980},
//Вентиляция в капоте
{1142, "bntr_b_ov",Vents,Alien,Trans_Fender,100},
{1143, "bntl_b_ov",Vents,Alien,Trans_Fender,100},//401 439 496 603
{1144, "bntr_b_sq",Vents,X-Flow,Trans_Fender,150},//
{1145, "bntl_b_sq",Vents,X-Flow,Trans_Fender,150},//401 439 542 589 603

{1146, "spl_c_l_b",Spoiler,X-Flow,Elegy,490},
{1147, "spl_a_l_b",Spoiler,Alien,Elegy,600},
{1148, "rbmp_c_l",Rear_Bumper,X-Flow,Elegy,890},
{1149, "rbmp_a_l",Rear_Bumper,Alien,Elegy,1000},
{1150, "rbmp_a_f",Rear_Bumper,Alien,Flash,1090},
{1151, "rbmp_c_f",Rear_Bumper,X-Flow,Flash,840},
{1152, "fbmp_c_f",Front_Bumper,X-Flow,Flash,910},
{1153, "bmp_a_f",Front_Bumper,Alien,Flash,1200},
{1154, "rbmp_a_st",Rear_Bumper,Alien,Stratum,1030},
{1155, "fbmp_a_st",Front_Bumper,Alien,Stratum,1030},
{1156, "rbmp_c_st",Rear_Bumper,X-Flow,Stratum,920},
{1157, "fbmp_c_st",Front_Bumper,X-Flow,Stratum,930},
{1158, "spl_c_j_b",Spoiler,X-Flow,Jester,550},
{1159, "rbmp_a_j",Rear_Bumper,Alien,Jester,1050},
{1160, "fbmp_a_j",Front_Bumper,Alien,Jester,1050},
{1161, "rbmp_c_j",Rear_Bumper,X-Flow,Jester,950},
{1162, "spl_a_j_b",Spoiler,Alien,Jester,650},
{1163, "spl_c_u_b",Spoiler,X-Flow,Uranus,450},
{1164, "spl_a_u_b",Spoiler,Alien,Uranus,550},
{1165, "fbmp_c_u",Front_Bumper,X-Flow,Uranus,850},
{1166, "fbmp_a_u",Front_Bumper,Alien,Uranus,950},
{1167, "rbmp_c_u",Rear_Bumper,X-Flow,Uranus,850},
{1168, "rbmp_a_u",Rear_Bumper,Alien,Uranus,950},
{1169, "fbmp_a_s",Front_Bumper,Alien,Sultan,990},
{1170, "fbmp_c_s",Front_Bumper,X-Flow,Sultan,880},
{1171, "fbmp_a_l",Front_Bumper,Alien,Elegy,990},
{1172, "fbmp_c_l",Front_Bumper,X-Flow,Elegy,900},
{1173, "fbmp_c_j",Front_Bumper,X-Flow,Jester,750},
{1174, "fbmp_lr_br1",Front_Bumper,Alien,Broadway,1000},
{1175, "fbmp_lr_br2",Rear_Bumper,X-Flow,Broadway,900},
{1176, "rbmp_lr_br1",Front_Bumper,Alien,Broadway,1000},
{1177, "rbmp_lr_br2",Rear_Bumper,X-Flow,Broadway,900},
{1178, "rbmp_lr_rem2",Rear_Bumper,X-Flow,Remington,2050},
{1179, "fbmp_lr_rem1",Front_Bumper,Alien,Remington,2150},
{1180, "rbmp_lr_rem1",Rear_Bumper,Alien,Remington,2130},
{1181, "fbmp_lr_bl2",Front_Bumper,X-Flow,Blade,2050},
{1182, "fbmp_lr_bl1",Front_Bumper,Alien,Blade,2130},
{1183, "rbmp_lr_bl2",Rear_Bumper,X-Flow,Blade,2040},
{1184, "rbmp_lr_bl1",Rear_Bumper,Alien,Blade,2150},
{1185, "fbmp_lr_rem2",Front_Bumper,X-Flow,Remington,2040},
{1186, "rbmp_lr_sv2",Rear_Bumper,X-Flow,Savanna,2095},
{1187, "rbmp_lr_sv1",Rear_Bumper,Alien,Savanna,2175},
{1188, "fbmp_lr_sv2",Front_Bumper,X-Flow,Savanna,2080},
{1189, "fbmp_lr_sv1",Front_Bumper,Alien,Savanna,2200},
{1190, "fbmp_lr_t2",Front_Bumper,X-Flow,Tornado,1200},
{1191, "fbmp_lr_t1",Front_Bumper,Alien,Tornado,1040},
{1192, "rbmp_lr_t1",Rear_Bumper,Alien,Tornado,940},
{1193, "rbmp_lr_t2",Rear_Bumper,X-Flow,Tornado,1100}
};
//для тюнинга конец
//==============================================================================
//запуск менюшки тюнинга
stock tuning_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{   //dialogid  - диалог на который выйдем
	#pragma unused dialogid
	#pragma unused response
	#pragma unused listitem
	#pragma unused inputtext
	CurState[playerid] = GetPlayerState(playerid);
   	if(CurState[playerid] == PLAYER_STATE_DRIVER)
   	{
		//nCarID[playerid] = GetPlayerVehicleID(playerid);
		//nCarModel[playerid] = GetVehicleModel(nCarID[playerid]);
		if(!IsValidVehicle(nCarID[playerid])) return 1;
		if(nCarModel[playerid] < 400) return 1;
   		if( !IsInPlane(nCarID[playerid]) && !IsInBoat(nCarID[playerid]) &&
			VehicleArray[nCarModel[playerid]-400][Category] != Rail_Transport && //не поезд
			VehicleArray[nCarModel[playerid]-400][Category] != Bicycle && //не велик
			!IsInIntCar(nCarID[playerid]) ) //не дерби
		{
			tunColor1 = 0, tunColor2 = 0;
    	    TogglePlayerControllableEx(playerid, 0);//обездвиживает нельзя двигаться
    	    //SendClientMessage(playerid, COLOR_GREY, "   ПРОВЕРКА!");
			ShowMenuForPlayerEx(mTuningMenu, playerid);
		}
	}
	else SendClientMessage(playerid, COLOR_GREY, "   Вы должны находиться за рулём транспортного средства!");
	return 1;
}



stock tuning_OnPlayerSelectedMenuRow(playerid, row, Menu:Current)
{
	//new Menu:Current = GetPlayerMenu(playerid);//получить ID меню
    new Float:last_x, Float:last_y, Float:last_z, Float:ugol;
	new vehicleid, modelid;
	if(IsPlayerInAnyVehicle(playerid))
	{
		//SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться в транспортном средстве!");
		//т.к. тюн может установиться на другую тачку
		vehicleid = GetPlayerVehicleID(playerid);
		modelid = GetVehicleModel(vehicleid);
		//nCarID[playerid] = GetPlayerVehicleID(playerid);//получить ID машины игрока из списка установленных моделей
		//nCarModel[playerid] = GetVehicleModel(vehicleid);
		//vehicleid = nCarID[playerid];
		//modelid = nCarModel[playerid];
		GetVehiclePos(vehicleid, last_x,last_y,last_z);
		GetVehicleZAngle(vehicleid, ugol);
		ugol = 360 - ugol;//360-90=270
	}
	//HideMenuForPlayerEx(Current, playerid);//меню сами скрываются при выборе пункта
	if(Current == mTuningMenu)
	{
	    switch(row)
		{
	        case 0:
	        {
	            //if(VehicleArray[modelid-400][Category] != State_Transport)
	            //{   // && VehicleArray[modelid-400][Category] != Public_Service
				//tunColor1 = 0, tunColor2 = 0;
				//tunColor1 = VehInfo[vehicleid][cColor1];
				//tunColor2 = VehInfo[vehicleid][cColor2];
				
				ShowMenuForPlayerEx(mColors, playerid);
				SetPlayerCameraPos(playerid, last_x+5.0*floatsin(ugol-45,degrees),last_y+5.0*floatcos(ugol-45,degrees), last_z+1.0);
				SetPlayerCameraLookAt(playerid, last_x,last_y,last_z, CAMERA_MOVE);
				//}
				//else ShowMenuForPlayerEx(mTuningMenu, playerid);
			}
	        case 1:
	        {
				if(VehicleArray[modelid-400][Modifications] == None) ShowMenuForPlayerEx(mTuningMenu, playerid);
	            else //if(VehicleArray[modelid-400][Category] != Public_Service )
	            {   //VehicleArray[modelid-400][Category] != State_Transport &&
					//PaintjobID=0;
					ShowMenuForPlayerEx(mPaintJob, playerid);
					SetPlayerCameraPos(playerid, last_x+5.0*floatsin(ugol-45,degrees),last_y+5.0*floatcos(ugol-45,degrees), last_z+1.0);
					SetPlayerCameraLookAt(playerid, last_x,last_y,last_z, CAMERA_MOVE);
				}
				//else ShowMenuForPlayerEx(mTuningMenu, playerid);
			}
	        case 2:
	        {
				if(VehicleArray[modelid-400][Modifications] == None) ShowMenuForPlayerEx(mTuningMenu, playerid);
				else
				{
					component_count=0;
					ShowMenuForPlayerEx(mNitro, playerid);
					SetPlayerCameraPos(playerid, last_x+4.0*floatsin(ugol-135,degrees),last_y+4.0*floatcos(ugol-135,degrees), last_z+2.0);
					SetPlayerCameraLookAt(playerid, last_x,last_y,last_z, CAMERA_MOVE);
				}
			}
	        case 3:
	        {
				if(VehicleArray[modelid-400][Modifications] == None) ShowMenuForPlayerEx(mTuningMenu, playerid);
				else
				{
					component_count=0;
					ShowMenuForPlayerEx(mWheels, playerid);
					SetPlayerCameraPos(playerid, last_x+5.0*floatsin(ugol-45,degrees),last_y+5.0*floatcos(ugol-45,degrees), last_z);
					SetPlayerCameraLookAt(playerid, last_x,last_y,last_z, CAMERA_MOVE);
				}
			}
	        case 4:
	        {
				if(VehicleArray[modelid-400][Modifications] == None) ShowMenuForPlayerEx(mTuningMenu, playerid);
				else
				{
					component_count=0;
					ShowMenuForPlayerEx(mHydraulics, playerid);
					SetPlayerCameraPos(playerid, last_x+5.0*floatsin(ugol-45,degrees),last_y+5.0*floatcos(ugol-45,degrees), last_z+1.0);
					SetPlayerCameraLookAt(playerid, last_x,last_y,last_z, CAMERA_MOVE);
				}
			}
	        case 5:
	        {
				if(VehicleArray[modelid-400][Modifications] == None) ShowMenuForPlayerEx(mTuningMenu, playerid);
				else
				{
					component_count=0;
					ShowMenuForPlayerEx(mSpoiler, playerid);
					SetPlayerCameraPos(playerid, last_x+4.0*floatsin(ugol-60,degrees),last_y+4.0*floatcos(ugol-60,degrees), last_z+2.0);
					SetPlayerCameraLookAt(playerid, last_x,last_y,last_z, CAMERA_MOVE);
				}
			}
	        case 6:
	        {
				if(VehicleArray[modelid-400][Modifications] == None) ShowMenuForPlayerEx(mTuningMenu, playerid);
				else
				{
					component_count=0;
					ShowMenuForPlayerEx(mFrontBumper, playerid);
					SetPlayerCameraPos(playerid, last_x+5.0*floatsin(ugol+30,degrees),//sin(0)=0
					last_y+5.0*floatcos(ugol+30,degrees),//cos(0)=1
					last_z);//Устанавливает новую позицию камеры игрока.
					SetPlayerCameraLookAt(playerid, last_x,last_y,last_z, CAMERA_MOVE);
					//Устанавливает направление и место, куда будет смотреть камера игрока.
				}
			}
	        case 7:
	        {
				if(VehicleArray[modelid-400][Modifications] == None) ShowMenuForPlayerEx(mTuningMenu, playerid);
				else
				{
					component_count=0;
					ShowMenuForPlayerEx(mRearBumper, playerid);
					SetPlayerCameraPos(playerid, last_x+5.0*floatsin(ugol-150,degrees),last_y+5.0*floatcos(ugol-150,degrees), last_z);
					SetPlayerCameraLookAt(playerid, last_x,last_y,last_z, CAMERA_MOVE);
				}
			}
	        case 8:
	        {
				if(VehicleArray[modelid-400][Modifications] == None) ShowMenuForPlayerEx(mTuningMenu, playerid);
				else
				{
					component_count=0;
					ShowMenuForPlayerEx(mSideskirt, playerid);
					SetPlayerCameraPos(playerid, last_x+5.0*floatsin(ugol-45,degrees),last_y+5.0*floatcos(ugol-45,degrees), last_z);
					SetPlayerCameraLookAt(playerid, last_x,last_y,last_z, CAMERA_MOVE);
				}
			}
	        case 9:
	        {
				if(VehicleArray[modelid-400][Modifications] == None) ShowMenuForPlayerEx(mTuningMenu, playerid);
				else
				{
					component_count=0;
					ShowMenuForPlayerEx(mRoof, playerid);
					SetPlayerCameraPos(playerid, last_x+3.0*floatsin(ugol,degrees),//к кординате x прибавляем смещение по направлению угла
					last_y+3.0*floatcos(ugol,degrees), last_z+1.0);
					SetPlayerCameraLookAt(playerid, last_x,last_y,last_z, CAMERA_MOVE);
				}
			}
	        case 10:
	        {
				if(VehicleArray[modelid-400][Modifications] == None) ShowMenuForPlayerEx(mTuningMenu, playerid);
				else
				{
					component_count=0;
					ShowMenuForPlayerEx(mExhaust, playerid);
					SetPlayerCameraPos(playerid, last_x+5.0*floatsin(ugol-150,degrees),last_y+5.0*floatcos(ugol-150,degrees), last_z-0.3);
					SetPlayerCameraLookAt(playerid, last_x,last_y,last_z, CAMERA_MOVE);
				}
			}
	        case 11://Дополнительные компоненты, для некоторых машин Trans_Fender
	        {
				if(VehicleArray[modelid-400][Modifications] == None) ShowMenuForPlayerEx(mTuningMenu, playerid);
	            else
				{
					ShowMenuForPlayerEx(mNeon, playerid);
					SetPlayerCameraPos(playerid, last_x+5.0*floatsin(ugol-45,degrees),last_y+5.0*floatcos(ugol-45,degrees), last_z);
					SetPlayerCameraLookAt(playerid, last_x,last_y,last_z, CAMERA_MOVE);
				}
			}
		}
	}
	else if(Current == mColors)
	{
		switch(row)
		{
			case 0:
			{
			    tunColor1 ++;
    			format(strings, sizeof(strings), "~w~%d ~y~/~r~%d",tunColor1,tunColor2);
				GameTextForPlayerEx(playerid, strings, 2000, 4);
				ChangeVehicleColor(vehicleid,tunColor1,VehInfo[vehicleid][cColor2]);//HouseInfo[house][hVcol2]
				if(tunColor1>126) tunColor1 = 0;
				Paid[playerid][Colors1] = 0;
				ShowMenuForPlayerEx(mColors, playerid);
			}
			case 1:
			{
				tunColor2 ++;
    			format(strings, sizeof(strings), "~w~%d ~y~/~r~%d",tunColor1,tunColor2);
				GameTextForPlayerEx(playerid, strings, 2000, 4);
				ChangeVehicleColor(vehicleid,VehInfo[vehicleid][cColor1],tunColor2);//HouseInfo[house][hVcol1]
				if(tunColor2>126) tunColor2 = 0;
				Paid[playerid][Colors2] = 0;
				ShowMenuForPlayerEx(mColors, playerid);
			}
			case 2:
			{
				//if(cColor1 != 0 && cColor1 != VehInfo[vehicleid][cColor1])
				VehInfo[vehicleid][cColor1] = tunColor1;//HouseInfo[house][hVcol1]
				//if(cColor2 != 0 && cColor2 != VehInfo[vehicleid][cColor2])
				VehInfo[vehicleid][cColor2] = tunColor2;//HouseInfo[house][hVcol2]
				PlaySoundForPlayer(playerid, SOUND_BUY_CAR_RESPRAY);
				////GivePlayerMoneyH(fsbiz+5, playerid, -150);
//#if defined FILTERSCRIPT

//#else
				//OnGangsExtortionSBiz(5, 150);//перечислили деньги в биз Car Delivery
//#endif
				//if(PlayerInfo[playerid][pJob] == CARMECHANIC) PlayerInfo[playerid][pMats] -= 150;
				Paid[playerid][Colors1] = 1;
				Paid[playerid][Colors2] = 1;
				ShowMenuForPlayerEx(mTuningMenu, playerid);
			}
		}
	}
	else if(Current == mPaintJob)
	{
	  	/*if(carmodel==559 || carmodel== 560 || carmodel== 561 || carmodel==562 || carmodel==565
		|| carmodel== 575 || carmodel== 534 || carmodel== 567 || carmodel== 536 || carmodel== 535 || carmodel== 576 || carmodel== 558)*/
		switch(row)
		{
			case 0://Paint Job 1
			{
				PaintjobID = 0;//Paintjob 1
				ChangeVehiclePaintjob(vehicleid,PaintjobID);
				Paid[playerid][PaintJob] = 0;
				ShowMenuForPlayerEx(mPaintJob, playerid);
			}
			case 1://Paint Job 2
			{
				PaintjobID = 1;
				ChangeVehiclePaintjob(vehicleid,PaintjobID);
				Paid[playerid][PaintJob] = 0;
				ShowMenuForPlayerEx(mPaintJob, playerid);
			}
			case 2://Paint Job 3
			{
				PaintjobID = 2;
				ChangeVehiclePaintjob(vehicleid,PaintjobID);
				Paid[playerid][PaintJob] = 0;
				ShowMenuForPlayerEx(mPaintJob, playerid);
			}
			/*case 3:
			{
				PaintjobID = 4;//J's head
				ChangeVehiclePaintjob(vehicleid,PaintjobID);
				Paid[playerid][PaintJob] = 0;
				ShowMenuForPlayerEx(mPaintJob, playerid);
			}
			case 4:
			{
				PaintjobID = 8;//Metal stuff
				ChangeVehiclePaintjob(vehicleid,PaintjobID);
				Paid[playerid][PaintJob] = 0;
				ShowMenuForPlayerEx(mPaintJob, playerid);
			}
			case 5:
			{
				PaintjobID = 11;//Half missing burnt car
				ChangeVehiclePaintjob(vehicleid,PaintjobID);
				Paid[playerid][PaintJob] = 0;
				ShowMenuForPlayerEx(mPaintJob, playerid);
			}
			case 5:
			{
				PaintjobID = 16;//Bricks
				ChangeVehiclePaintjob(vehicleid,PaintjobID);
				Paid[playerid][PaintJob] = 0;
				ShowMenuForPlayerEx(mPaintJob, playerid);
			}
			case 5:
			{
				PaintjobID = 17;//Window or Gant Bridge toll booths
				//18 - Train lines? //22 - Gant Bridge (seethrough) //25 - Grey carcolor with brown wood (?) down the edge
				ChangeVehiclePaintjob(vehicleid,PaintjobID);
				Paid[playerid][PaintJob] = 0;
				ShowMenuForPlayerEx(mPaintJob, playerid);
			}
			*/
			case 3://Buy $500
			{
				VehInfo[vehicleid][cPaintjob] = PaintjobID;
				//GivePlayerMoneyH(fsbiz+5, playerid, -500);
				//SBizInfo[5][sbTill] += 500;//перечислили деньги в биз Car Delivery
				//SBizInfo[5][sbExport] += 500;
				//if(PlayerInfo[playerid][pJob] == CARMECHANIC) PlayerInfo[playerid][pMats] -= 500;
				PlaySoundForPlayer(playerid, SOUND_BUY_CAR_RESPRAY);
				Paid[playerid][PaintJob] = 1;
				ShowMenuForPlayerEx(mTuningMenu, playerid);
			}
	 	}
	}
	else if(Current == mNitro)
	{
		switch(row)
		{
			case 0:
			{
				//if((PlayerInfo[playerid][pJob] == CARMECHANIC && PlayerInfo[playerid][pMats] > 200)
				 //	|| PlayerInfo[playerid][pJob] != CARMECHANIC
				//	|| PlayerInfo[playerid][pAdmin] >= 6)
				//{   //если у игрока материалов больше чем цены тюна этого компонента
					ShowMenuForPlayerEx(mTuningMenu, playerid);
					ComponentID[Nitro] = 1009;
					//house = HouseCar[playerid];//см. выше
					VehInfo[vehicleid][cNitro] = 1009;
					AddVehicleComponent(vehicleid,ComponentID[Nitro]);
					//GivePlayerMoneyH(fsbiz+5, playerid, -200);
					//SBizInfo[5][sbTill] += 200;//перечислили деньги в биз Car Delivery
					//SBizInfo[5][sbExport] += 200;
					//if(PlayerInfo[playerid][pJob] == CARMECHANIC) PlayerInfo[playerid][pMats] -= 200;
					PlaySoundForPlayer(playerid, SOUND_BUY_CAR_MOD);
					Paid[playerid][Nitro] = 1;
	
				//}
				//else ShowMenuForPlayerEx(mNitro, playerid);
			}
			case 1:
			{
				//if((PlayerInfo[playerid][pJob] == CARMECHANIC && PlayerInfo[playerid][pMats] > 770)
				// 	|| PlayerInfo[playerid][pJob] != CARMECHANIC
				//	|| PlayerInfo[playerid][pAdmin] >= 6)
				//{
					ShowMenuForPlayerEx(mTuningMenu, playerid);
					ComponentID[Nitro] = 1008;
					VehInfo[vehicleid][cNitro] = 1008;
					AddVehicleComponent(vehicleid,ComponentID[Nitro]);
					//GivePlayerMoneyH(fsbiz+5, playerid, -770);
					//SBizInfo[5][sbTill] += 770;//перечислили деньги в биз Car Delivery
					//SBizInfo[5][sbExport] += 770;
					//if(PlayerInfo[playerid][pJob] == CARMECHANIC) PlayerInfo[playerid][pMats] -= 770;
					PlaySoundForPlayer(playerid, SOUND_BUY_CAR_MOD);
					Paid[playerid][Nitro] = 1;
				//}
				//else ShowMenuForPlayerEx(mNitro, playerid);
			}
			case 2:
			{
				//if((PlayerInfo[playerid][pJob] == CARMECHANIC && PlayerInfo[playerid][pMats] > 1000)
				 //	|| PlayerInfo[playerid][pJob] != CARMECHANIC
				//	|| PlayerInfo[playerid][pAdmin] > 4)
				//{
					ShowMenuForPlayerEx(mTuningMenu, playerid);
					ComponentID[Nitro] = 1010;
					VehInfo[vehicleid][cNitro] = 1010;
					AddVehicleComponent(vehicleid,ComponentID[Nitro]);
					//GivePlayerMoneyH(fsbiz+5, playerid, -1000);
					//SBizInfo[5][sbTill] += 1000;//перечислили деньги в биз Car Delivery
					//SBizInfo[5][sbExport] += 1000;
					//if(PlayerInfo[playerid][pJob] == CARMECHANIC) PlayerInfo[playerid][pMats] -= 1000;
					PlaySoundForPlayer(playerid, SOUND_BUY_CAR_MOD);
					Paid[playerid][Nitro] = 1;
				//}
				//else ShowMenuForPlayerEx(mNitro, playerid);
			}
		}
	}
	else if(Current == mWheels)
	{
		switch(row)
		{
			case 0:
			{
				new ind, Found, Amount[194];//массив для хранения найденых
				for(new i=0;i<194;i++)//сканируем все компоненты
				{
					if(ComponentArray[i][compPart] == Wheels){ Amount[ind] = i; ind ++; Found=1; }//записали в массив тот ID соотв колесу
				}	//Amount[16]=98 ind=17  количеству найденых компонентов + 1
				if(component_count == ind) component_count = 0;//сбрасываем
				if(Found == 1)
				{   //если нашли
					ComponentID[Wheels] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Wheels]);
					Paid[playerid][Wheels] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mWheels, playerid);
			}
			case 1:
			{
				//if((PlayerInfo[playerid][pJob] == CARMECHANIC && PlayerInfo[playerid][pMats] > 770)
				// 	|| PlayerInfo[playerid][pJob] != CARMECHANIC
				//	|| PlayerInfo[playerid][pAdmin] >= 6)
				//{
					VehInfo[vehicleid][cWheels] = ComponentID[Wheels];
					//GivePlayerMoneyH(fsbiz+5, playerid, -770);
					//SBizInfo[5][sbTill] += 770;//перечислили деньги в биз Car Delivery
					//SBizInfo[5][sbExport] += 770;
					//if(PlayerInfo[playerid][pJob] == CARMECHANIC) PlayerInfo[playerid][pMats] -= 770;
					//PlaySoundForPlayer(playerid, SOUND_BUY_CAR_MOD);
					PlaySoundForPlayer(playerid, SOUND_FIT_TYRE);
					Paid[playerid][Wheels] = 1;
					ShowMenuForPlayerEx(mTuningMenu, playerid);
				//}
				//else ShowMenuForPlayerEx(mWheels, playerid);
			}
	 	}
	}
	else if(Current == mHydraulics)
	{
		switch(row)
		{
			case 0:
			{
				//if((PlayerInfo[playerid][pJob] == CARMECHANIC && PlayerInfo[playerid][pMats] > 1150)
				// 	|| PlayerInfo[playerid][pJob] != CARMECHANIC
				//	|| PlayerInfo[playerid][pAdmin] >= 6)
				//{
					ComponentID[Hydraulics] = 1087;
					AddVehicleComponent(vehicleid,ComponentID[Hydraulics]);
					VehInfo[vehicleid][cHydraulics] = 1087;
					
					//GivePlayerMoneyH(fsbiz+5, playerid, -1150);
					//SBizInfo[5][sbTill] += 1150;//перечислили деньги в биз Car Delivery
					//SBizInfo[5][sbExport] += 1150;
					//if(PlayerInfo[playerid][pJob] == CARMECHANIC) PlayerInfo[playerid][pMats] -= 1150;
					
					PlaySoundForPlayer(playerid, SOUND_BUY_CAR_MOD);
					Paid[playerid][Hydraulics] = 1;
					ShowMenuForPlayerEx(mTuningMenu, playerid);
				//}
				//else ShowMenuForPlayerEx(mHydraulics, playerid);
			}
	 	}
	}
	else if(Current == mSpoiler)
	{
		switch(row)
		{
			case 0:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)//i - ID модели тачки
				{ if(ComponentArray[i][compPart] == Spoiler && ComponentArray[i][compType] == Alien && ComponentArray[i][compCars] == modelid) { Amount[ind] = i; ind ++; Found=1; break; } }
				if(component_count == ind) component_count = 0;
				if(Found == 1)
				{   //если нашли
					ComponentID[Spoiler] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Spoiler]);
					Paid[playerid][Spoiler] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mSpoiler, playerid);
			}
			case 1:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)
				{ if(ComponentArray[i][compPart] == Spoiler && ComponentArray[i][compType] == X-Flow && ComponentArray[i][compCars] == modelid) { Amount[ind] = i; ind ++; Found=1; break; } }
				if(component_count == ind) component_count = 0;
				if(Found == 1)
				{   //если нашли
					ComponentID[Spoiler] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Spoiler]);
					Paid[playerid][Spoiler] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mSpoiler, playerid);
			}
			case 2:
			{
				//if((PlayerInfo[playerid][pJob] == CARMECHANIC && PlayerInfo[playerid][pMats] > 550)
				// 	|| PlayerInfo[playerid][pJob] != CARMECHANIC
				//	|| PlayerInfo[playerid][pAdmin] >= 6)
				//{
					VehInfo[vehicleid][cSpoiler] = ComponentID[Spoiler];
					//GivePlayerMoneyH(fsbiz+5, playerid, -550);
					//SBizInfo[5][sbTill] += 550;//перечислили деньги в биз Car Delivery
					//SBizInfo[5][sbExport] += 550;
					//if(PlayerInfo[playerid][pJob] == CARMECHANIC) PlayerInfo[playerid][pMats] -= 550;
					PlaySoundForPlayer(playerid, SOUND_BUY_CAR_MOD);
					Paid[playerid][Spoiler] = 1;
					ShowMenuForPlayerEx(mTuningMenu, playerid);
				//}
				//else ShowMenuForPlayerEx(mSpoiler, playerid);
			}
	 	}
	}
	else if(Current == mFrontBumper)
	{
		switch(row)
		{
			case 0:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)
				{ if(ComponentArray[i][compPart] == Front_Bumper && ComponentArray[i][compType] == Alien && ComponentArray[i][compCars] == modelid) { Amount[ind] = i; ind ++; Found=1; break; }	}
				if(component_count == ind) component_count = 0;
				if(Found == 1)
				{   //если нашли
					ComponentID[Front_Bumper] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Front_Bumper]);
					Paid[playerid][Front_Bumper] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mFrontBumper, playerid);
			}
			case 1:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)
				{ if(ComponentArray[i][compPart] == Front_Bumper && ComponentArray[i][compType] == X-Flow && ComponentArray[i][compCars] == modelid) { Amount[ind] = i; ind ++; Found=1; break; } }
				if(component_count == ind) component_count = 0;
				if(Found == 1)
				{   //если нашли
					ComponentID[Front_Bumper] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Front_Bumper]);
					Paid[playerid][Front_Bumper] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mFrontBumper, playerid);
			}
			case 2:
			{
				//if((PlayerInfo[playerid][pJob] == CARMECHANIC && PlayerInfo[playerid][pMats] > 950)
				// 	|| PlayerInfo[playerid][pJob] != CARMECHANIC || PlayerInfo[playerid][pAdmin] >= 6)
				//{
					VehInfo[vehicleid][cFrontBumper] = ComponentID[Front_Bumper];
					//GivePlayerMoneyH(fsbiz+5, playerid, -950);
					//SBizInfo[5][sbTill] += 950;//перечислили деньги в биз Car Delivery
					//SBizInfo[5][sbExport] += 950;
					if(PlayerInfo[playerid][pJob] == CARMECHANIC) PlayerInfo[playerid][pMats] -= 950;
					PlaySoundForPlayer(playerid, SOUND_BUY_CAR_MOD);
					Paid[playerid][Front_Bumper] = 1;
					ShowMenuForPlayerEx(mTuningMenu, playerid);
				//}
				//else ShowMenuForPlayerEx(mFrontBumper, playerid);
			}
	 	}
	}
	else if(Current == mRearBumper)
	{
		switch(row)
		{
			case 0:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)
				{ if(ComponentArray[i][compPart] == Rear_Bumper && ComponentArray[i][compType] == Alien && ComponentArray[i][compCars] == modelid) { Amount[ind] = i; ind ++; Found=1; break; } }
				if(component_count == ind) component_count = 0;
				if(Found == 1)
				{   //если нашли
					ComponentID[Rear_Bumper] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Rear_Bumper]);
					Paid[playerid][Rear_Bumper] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mRearBumper, playerid);
			}
			case 1:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)
				{ if(ComponentArray[i][compPart] == Rear_Bumper && ComponentArray[i][compType] == X-Flow && ComponentArray[i][compCars] == modelid) { Amount[ind] = i; ind ++; Found=1; break; } }
				if(component_count == ind) component_count = 0;
				if(Found == 1)
				{   //если нашли
					ComponentID[Rear_Bumper] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Rear_Bumper]);
					Paid[playerid][Rear_Bumper] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mRearBumper, playerid);
			}
			case 2:
			{
				//if((PlayerInfo[playerid][pJob] == CARMECHANIC && PlayerInfo[playerid][pMats] > 950)
				// 	|| PlayerInfo[playerid][pJob] != CARMECHANIC
				//	|| PlayerInfo[playerid][pAdmin] >= 6)
				//{
					VehInfo[vehicleid][cRearBumper] = ComponentID[Rear_Bumper];
					//GivePlayerMoneyH(fsbiz+5, playerid, -950);
					//SBizInfo[5][sbTill] += 950;//перечислили деньги в биз Car Delivery
					//SBizInfo[5][sbExport] += 950;
					if(PlayerInfo[playerid][pJob] == CARMECHANIC) PlayerInfo[playerid][pMats] -= 950;
					PlaySoundForPlayer(playerid, SOUND_BUY_CAR_MOD);
					Paid[playerid][Rear_Bumper] = 1;
					ShowMenuForPlayerEx(mTuningMenu, playerid);
				//}
				//else ShowMenuForPlayerEx(mRearBumper, playerid);
			}
	 	}
	}
	else if(Current == mSideskirt)
	{
		switch(row)
		{
			case 0:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)
				{ if(ComponentArray[i][compPart] == Sideskirt && ComponentArray[i][compType] == Alien && ComponentArray[i][compCars] == modelid) { Amount[ind] = i; ind ++; Found=1; break; } }
				if(component_count == ind) component_count = 0;
				if(Found == 1)
				{   //если нашли
					ComponentID[Sideskirt] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Sideskirt]);
					Paid[playerid][Sideskirt] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mSideskirt, playerid);
			}
			case 1:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)
				{ if(ComponentArray[i][compPart] == Sideskirt && ComponentArray[i][compType] == X-Flow && ComponentArray[i][compCars] == modelid) { Amount[ind] = i; ind ++; Found=1; break; } }
				if(component_count == ind) component_count = 0;
				if(Found == 1)
				{   //если нашли
					ComponentID[Sideskirt] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Sideskirt]);
					Paid[playerid][Sideskirt] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mSideskirt, playerid);
			}
			case 2:
			{
				//if((PlayerInfo[playerid][pJob] == CARMECHANIC && PlayerInfo[playerid][pMats] > 450)
				// 	|| PlayerInfo[playerid][pJob] != CARMECHANIC
				//	|| PlayerInfo[playerid][pAdmin] >= 6)
				//{
					VehInfo[vehicleid][cSideskirt] = ComponentID[Sideskirt];
					//GivePlayerMoneyH(fsbiz+5, playerid, -900);//2*450
					//SBizInfo[5][sbTill] += 900;//перечислили деньги в биз Car Delivery
					//SBizInfo[5][sbExport] += 900;
					if(PlayerInfo[playerid][pJob] == CARMECHANIC) PlayerInfo[playerid][pMats] -= 900;//2*450
					PlaySoundForPlayer(playerid, SOUND_BUY_CAR_MOD);
					Paid[playerid][Sideskirt] = 1;
					ShowMenuForPlayerEx(mTuningMenu, playerid);
				//}
				//else ShowMenuForPlayerEx(mSideskirt, playerid);
			}
	 	}
	}
	else if(Current == mRoof)
	{
		switch(row)
		{
			case 0:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)
				{ if(ComponentArray[i][compPart] == Roof && ComponentArray[i][compType] == Alien && ComponentArray[i][compCars] == modelid) { Amount[ind] = i; ind ++; Found=1; break; } }
				if(component_count == ind) component_count = 0;
				if(Found)
				{   //если нашли
					ComponentID[Roof] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Roof]);
					Paid[playerid][Roof] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mRoof, playerid);
			}
			case 1:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)
				{ if(ComponentArray[i][compPart] == Roof && ComponentArray[i][compType] == X-Flow && ComponentArray[i][compCars] == modelid) { Amount[ind] = i; ind ++; Found=1; break; } }
				if(component_count == ind) component_count = 0;
				if(Found == 1)
				{   //если нашли
					ComponentID[Roof] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Roof]);
					Paid[playerid][Roof] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mRoof, playerid);
			}
			case 2:
			{
				//if((PlayerInfo[playerid][pJob] == CARMECHANIC && PlayerInfo[playerid][pMats] > 150)
				// 	|| PlayerInfo[playerid][pJob] != CARMECHANIC
				//	|| PlayerInfo[playerid][pAdmin] >= 6)
				//{
					VehInfo[vehicleid][cRoof] = ComponentID[Roof];
					//GivePlayerMoneyH(fsbiz+5, playerid, -150);
					//SBizInfo[5][sbTill] += 150;//перечислили деньги в биз Car Delivery
					//SBizInfo[5][sbExport] += 150;
					if(PlayerInfo[playerid][pJob] == CARMECHANIC) PlayerInfo[playerid][pMats] -= 150;
					PlaySoundForPlayer(playerid, SOUND_BUY_CAR_MOD);
					Paid[playerid][Roof] = 1;
					ShowMenuForPlayerEx(mTuningMenu, playerid);
				//}
				//else ShowMenuForPlayerEx(mRoof, playerid);
			}
	 	}
	}
	else if(Current == mExhaust)
	{
		switch(row)
		{
			case 0:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)
				{ if(ComponentArray[i][compPart] == Exhaust && ComponentArray[i][compType] == Alien && ComponentArray[i][compCars] == modelid) { Amount[ind] = i; ind ++; Found=1; break; } }
				if(component_count == ind) component_count = 0;
				if(Found == 1)
				{   //если нашли
					ComponentID[Exhaust] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Exhaust]);
					Paid[playerid][Exhaust] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mExhaust, playerid);
			}
			case 1:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)
				{ if(ComponentArray[i][compPart] == Exhaust && ComponentArray[i][compType] == X-Flow && ComponentArray[i][compCars] == modelid) { Amount[ind] = i; ind ++; Found=1; break; } }
				if(component_count == ind) component_count = 0;
				if(Found == 1)
				{   //если нашли
					ComponentID[Exhaust] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Exhaust]);
					Paid[playerid][Exhaust] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mExhaust, playerid);
			}
			case 2:
			{
				//if((PlayerInfo[playerid][pJob] == CARMECHANIC && PlayerInfo[playerid][pMats] > 650)
				// 	|| PlayerInfo[playerid][pJob] != CARMECHANIC
				//	|| PlayerInfo[playerid][pAdmin] >= 6)
				//{
					VehInfo[vehicleid][cExhaust] = ComponentID[Exhaust];
					//GivePlayerMoneyH(fsbiz+5, playerid, -650);
					//SBizInfo[5][sbTill] += 650;//перечислили деньги в биз Car Delivery
					//SBizInfo[5][sbExport] += 650;
					if(PlayerInfo[playerid][pJob] == CARMECHANIC) PlayerInfo[playerid][pMats] -= 650;
					PlaySoundForPlayer(playerid, SOUND_BUY_CAR_MOD);
					Paid[playerid][Exhaust] = 1;
					ShowMenuForPlayerEx(mTuningMenu, playerid);
				//}
				//else ShowMenuForPlayerEx(mExhaust, playerid);
			}
	 	}
	}
	else if(Current == mNeon)
	{
		switch(row)
		{
			case 0:
			{
				if(Neon > 18652) Neon = 18647;
    			if(Neon == 18647) format(strings, sizeof(strings), "~r~%d", Neon);
    			else if(Neon == 18648) format(strings, sizeof(strings), "~b~%d", Neon);
    			else if(Neon == 18649) format(strings, sizeof(strings), "~g~%d", Neon);
    			else if(Neon == 18650) format(strings, sizeof(strings), "~y~%d", Neon);
    			else if(Neon == 18651) format(strings, sizeof(strings), "~p~%d", Neon);
    			else if(Neon == 18652) format(strings, sizeof(strings), "~w~%d", Neon);
				GameTextForPlayerEx(playerid, strings, 2000, 4);

				//neon[0] = CreateObjectEx(18648,0,0,0,0,0,0);
				//neon[1] = CreateObjectEx(18648,0,0,0,0,0,0);
				//neon[2] = CreateObjectEx(18648,0,0,0,0,0,0);
				//neon[3] = CreateObjectEx(18648,0,0,0,0,0,0);
				/*AttachObjectToVehicleEx(neon[0], vehicleid, -0.909999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
				AttachObjectToVehicleEx(neon[1], vehicleid, 0.914999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
				AttachObjectToVehicleEx(neon[2], vehicleid, 0.034999, 2.225003, -0.629999, 0.000000, 0.000000, -88.589958);
				AttachObjectToVehicleEx(neon[3], vehicleid, 0.034999, -2.034998, -0.629999, 0.000000, 0.000000, -88.589958);*/

				if( IsValidObjectEx(VehInfo[vehicleid][cNeonl]) ) DestroyObjectEx(VehInfo[vehicleid][cNeonl], 23);
				//if( IsValidObjectEx(VehInfo[vehicleid][cNeonr]) ) DestroyObjectEx(VehInfo[vehicleid][cNeonr], 23);

				//SetPVarInt(playerid, "NeonStatus", 1);
				VehInfo[vehicleid][cNeonl] = CreateObjectEx(Neon, 0.0,0.0,0.0, 0.0,0.0,0.0);
				//VehInfo[vehicleid][cNeonr] = CreateObjectEx(Neon, 0.0,0.0,0.0, 0.0,0.0,0.0);
				//AttachObjectToVehicleEx(VehInfo[vehicleid][cNeonl], vehicleid, -0.5,0.0,-0.50, 0.0,0.0,0.0);
				//AttachObjectToVehicleEx(VehInfo[vehicleid][cNeonr], vehicleid, 0.5,0.0,-0.50, 0.0,0.0,0.0);
				AttachObjectToVehicleEx(VehInfo[vehicleid][cNeonl], vehicleid, 0.0,0.0,-0.50, 0.0,0.0,0.0);
				
				Paid[playerid][Neons] = 0;
				ShowMenuForPlayerEx(mNeon, playerid);
			    Neon ++;
			}
			case 1:
			{
				//if((PlayerInfo[playerid][pJob] == CARMECHANIC && PlayerInfo[playerid][pMats] > 1500)
				// 	|| PlayerInfo[playerid][pJob] != CARMECHANIC
				//	|| PlayerInfo[playerid][pAdmin] >= 6)
				//{
					//VehInfo[vehicleid][cWheels] = ComponentID[Wheels];
					//GivePlayerMoneyH(fsbiz+5, playerid, -1500);
					//SBizInfo[5][sbTill] += 1500;//перечислили деньги в биз Car Delivery
					//SBizInfo[5][sbExport] += 1500;
					//if(PlayerInfo[playerid][pJob] == CARMECHANIC) PlayerInfo[playerid][pMats] -= 1500;
					PlaySoundForPlayer(playerid, SOUND_BUY_CAR_MOD);
					Paid[playerid][Neons] = 1;
					ShowMenuForPlayerEx(mTuningMenu, playerid);
				//}
				//else ShowMenuForPlayerEx(mNeon, playerid);
			}
		}
	}
	/*else if(Current == mOthers)
	{
	    switch(row)
		{
	        case 0:
	        {
				component_count=0;
				ShowMenuForPlayerEx(mBullbarsFront, playerid);
			}
	        case 1:
	        {
				component_count=0;
				ShowMenuForPlayerEx(mBullbarsRear, playerid);
			}
	        case 2:
	        {
				component_count=0;
				ShowMenuForPlayerEx(mHood, playerid);
			}
	        case 3:
	        {
				component_count=0;
				ShowMenuForPlayerEx(mVents, playerid);
			}
	        case 4:
	        {
				component_count=0;
				ShowMenuForPlayerEx(mLamps, playerid);
			}
		}
	}
	else if(Current == mBullbarsFront)
	{
		switch(row)
		{
			case 0:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)
				{   //находим выбранный компонент соот. нашей машине
					if(ComponentArray[i][compPart] == Bullbars_Front && ComponentArray[i][compType] == Alien && ComponentArray[i][compCars] == modelid)	{ Amount[ind] = i; ind ++; Found=1; break; }
				}
				if(component_count == ind) component_count = 0;
				if(Found == 1)
				{   //если нашли
					ComponentID[Bullbars_Front] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Bullbars_Front]);
					Paid[playerid][Bullbars_Front] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mBullbarsFront, playerid);
			}
			case 1:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)
				{ if(ComponentArray[i][compPart] == Bullbars_Front && ComponentArray[i][compType] == X-Flow && ComponentArray[i][compCars] == modelid)	{ Amount[ind] = i; ind ++; Found=1; break; } }
				if(component_count == ind) component_count = 0;
				if(Found == 1)
				{   //если нашли
					ComponentID[Bullbars_Front] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Bullbars_Front]);
					Paid[playerid][Bullbars_Front] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mBullbarsFront, playerid);
			}
			case 2:
			{
				if((PlayerInfo[playerid][pJob] == CARMECHANIC && PlayerInfo[playerid][pMats] > 950)
				 	|| PlayerInfo[playerid][pJob] != CARMECHANIC
					|| PlayerInfo[playerid][pAdmin] >= 6)
				{
					//HideMenuForPlayerEx(mBullbarsFront, playerid);
					VehInfo[vehicleid][cBullbarsFront] = ComponentID[Bullbars_Front];
					//GivePlayerMoneyH(1, playerid, -950);
					//SBizInfo[5][sbTill] += 950;//перечислили деньги в биз Car Delivery
					if(PlayerInfo[playerid][pJob] == CARMECHANIC) PlayerInfo[playerid][pMats] -= 950;
					PlaySoundForPlayer(playerid, SOUND_BUY_CAR_MOD);
					Paid[playerid][Bullbars_Front] = 1;
					ShowMenuForPlayerEx(mTuningMenu, playerid);
				}
				else ShowMenuForPlayerEx(mBullbarsFront, playerid);
			}
	 	}
	}
	else if(Current == mBullbarsRear)
	{
		switch(row)
		{
			case 0:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)
				{ if(ComponentArray[i][compPart] == Bullbars_Rear && ComponentArray[i][compType] == Alien && ComponentArray[i][compCars] == modelid) { Amount[ind] = i; ind ++; Found=1; break; } }
				if(component_count == ind) component_count = 0;
				if(Found == 1)
				{   //если нашли
					ComponentID[Bullbars_Rear] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Bullbars_Rear]);
					Paid[playerid][Bullbars_Rear] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mBullbarsRear, playerid);
			}
			case 1:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)
				{ if(ComponentArray[i][compPart] == Bullbars_Rear && ComponentArray[i][compType] == X-Flow && ComponentArray[i][compCars] == modelid) { Amount[ind] = i; ind ++; Found=1; break; } }
				if(component_count == ind) component_count = 0;
				if(Found == 1)
				{   //если нашли
					ComponentID[Bullbars_Rear] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Bullbars_Rear]);
					Paid[playerid][Bullbars_Rear] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mBullbarsRear, playerid);
			}
			case 2:
			{
				//HideMenuForPlayerEx(mBullbarsRear, playerid);
				VehInfo[vehicleid][cBullbarsRear] = ComponentID[Bullbars_Rear];
				//GivePlayerMoneyH(1, playerid, -950);
				//SBizInfo[5][sbTill] += 950;//перечислили деньги в биз Car Delivery
				PlaySoundForPlayer(playerid, SOUND_BUY_CAR_MOD);
				Paid[playerid][Bullbars_Rear] = 1;
				ShowMenuForPlayerEx(mTuningMenu, playerid);
			}
	 	}
	}
	else if(Current == mHood)
	{
		switch(row)
		{
			case 0:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)
				{ if(ComponentArray[i][compPart] == Hood && ComponentArray[i][compType] == Alien && ComponentArray[i][compCars] == modelid) { Amount[ind] = i; ind ++; Found=1; break; } }
				if(component_count == ind) component_count = 0;
				if(Found == 1)
				{   //если нашли
					ComponentID[Hood] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Hood]);
					Paid[playerid][Hood] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mHood, playerid);
			}
			case 1:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)
				{ if(ComponentArray[i][compPart] == Hood && ComponentArray[i][compType] == X-Flow && ComponentArray[i][compCars] == modelid) { Amount[ind] = i; ind ++; Found=1; break; } }
				if(component_count == ind) component_count = 0;
				if(Found == 1)
				{   //если нашли
					ComponentID[Hood] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Hood]);
					Paid[playerid][Hood] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mHood, playerid);
			}
			case 2:
			{
				//HideMenuForPlayerEx(mHood, playerid);
				VehInfo[vehicleid][cHood] = ComponentID[Hood];
				//GivePlayerMoneyH(1, playerid, -150);
				//SBizInfo[5][sbTill] += 150;//перечислили деньги в биз Car Delivery
				PlaySoundForPlayer(playerid, SOUND_BUY_CAR_MOD);
				Paid[playerid][Hood] = 1;
				ShowMenuForPlayerEx(mTuningMenu, playerid);
			}
	 	}
	}
	else if(Current == mVents)
	{
		switch(row)
		{
			case 0:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)
				{ if(ComponentArray[i][compPart] == Vents && ComponentArray[i][compType] == Alien && ComponentArray[i][compCars] == modelid) { Amount[ind] = i; ind ++; Found=1; break; } }
				if(component_count == ind) component_count = 0;
				if(Found == 1)
				{   //если нашли
					ComponentID[Vents] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Vents]);
					Paid[playerid][Vents] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mVents, playerid);
			}
			case 1:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)
				{ if(ComponentArray[i][compPart] == Vents && ComponentArray[i][compType] == X-Flow && ComponentArray[i][compCars] == modelid) { Amount[ind] = i; ind ++; Found=1; break; } }
				if(component_count == ind) component_count = 0;
				if(Found == 1)
				{   //если нашли
					ComponentID[Vents] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Vents]);
					Paid[playerid][Vents] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mVents, playerid);
			}
			case 2:
			{
				//HideMenuForPlayerEx(mVents, playerid);
				VehInfo[vehicleid][cVentsLeft] = ComponentID[Vents];
				//GivePlayerMoneyH(1, playerid, -150);
				//SBizInfo[5][sbTill] += 150;//перечислили деньги в биз Car Delivery
				PlaySoundForPlayer(playerid, SOUND_BUY_CAR_MOD);
				Paid[playerid][Vents] = 1;
				ShowMenuForPlayerEx(mTuningMenu, playerid);
			}
	 	}
	}
	else if(Current == mLamps)
	{
		switch(row)
		{
			case 0:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)
				{ if(ComponentArray[i][compPart] == Lamps && ComponentArray[i][compType] == Alien && ComponentArray[i][compCars] == modelid) { Amount[ind] = i; ind ++; Found=1; break; } }
				if(component_count == ind) component_count = 0;
				if(Found == 1)
				{   //если нашли
					ComponentID[Lamps] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Lamps]);
					Paid[playerid][Lamps] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mLamps, playerid);
			}
			case 1:
			{
				new ind, Amount[194], Found;
				for(new i=0;i<194;i++)
				{ if(ComponentArray[i][compPart] == Lamps && ComponentArray[i][compType] == X-Flow && ComponentArray[i][compCars] == modelid) { Amount[ind] = i; ind ++; Found=1; break; } }
				if(component_count == ind) component_count = 0;
				if(Found == 1)
				{   //если нашли
					ComponentID[Lamps] = ComponentArray[Amount[component_count]][compID];
					AddVehicleComponent(vehicleid,ComponentID[Lamps]);
					Paid[playerid][Lamps] = 0;
				    component_count ++;
				}
				ShowMenuForPlayerEx(mLamps, playerid);
			}
			case 2:
			{
				//HideMenuForPlayerEx(mLamps, playerid);
				VehInfo[vehicleid][cLamps] = ComponentID[Lamps];
				//GivePlayerMoneyH(1, playerid, -150);
				//SBizInfo[5][sbTill] += 150;//перечислили деньги в биз Car Delivery
				PlaySoundForPlayer(playerid, SOUND_BUY_CAR_MOD);
				Paid[playerid][Lamps] = 1;
				ShowMenuForPlayerEx(mTuningMenu, playerid);
			}
	 	}
	}*/
//для тюнинга конец
}


stock tuning_OnPlayerExitedMenu(playerid, Menu:Current)
{
	//==========================================================================
	//для тюнинга начало
	new vehicleid = GetPlayerVehicleID(playerid);
	//new modelid = GetVehicleModel(vehicleid);

	//new Menu:Current = GetPlayerMenu(playerid);//получить ID меню
	//HideMenuForPlayerEx(Current,playerid);//не трогать, т.к. не будут показываться повторно меню
	if(Current == mColors)
	{
		HideMenuForPlayerEx(Current,playerid);
		ShowMenuForPlayerEx(mTuningMenu, playerid);
		if(Paid[playerid][Colors1] == 1 && Paid[playerid][Colors2] == 1)
		{	//если оплачено
			ChangeVehicleColor(vehicleid,
				VehInfo[vehicleid][cColor1],
				VehInfo[vehicleid][cColor2]);
		}
		else ChangeVehicleColor(vehicleid, VehInfo[vehicleid][cColor1], VehInfo[vehicleid][cColor2]);//установить цвет
	}
	else if(Current == mPaintJob)
	{
		HideMenuForPlayerEx(Current,playerid);
		ShowMenuForPlayerEx(mTuningMenu, playerid);
		if(Paid[playerid][PaintJob] == 0)
		{   //если не оплачено
			if(VehInfo[vehicleid][cPaintjob] >= 0 && VehInfo[vehicleid][cPaintjob] <= 2) ChangeVehiclePaintjob(vehicleid,VehInfo[vehicleid][cPaintjob]);//установить старую
   			else ChangeVehiclePaintjob(vehicleid, 255);//установить старую
		}
	}
	else if(Current == mNitro)
	{   //если находимся в каком то меню
		HideMenuForPlayerEx(Current,playerid);
		ShowMenuForPlayerEx(mTuningMenu, playerid);//всегда cразу после HideMenuForPlayerEx
		if(Paid[playerid][Nitro] == 0)
		{   //если не оплачено
			RemoveVehicleComponent(vehicleid, ComponentID[Nitro]);//удалить текущий компонент
			AddVehicleComponent(vehicleid,VehInfo[vehicleid][cNitro]);//установить старый
		}
	}
	else if(Current == mWheels)
	{
		HideMenuForPlayerEx(Current,playerid);
		ShowMenuForPlayerEx(mTuningMenu, playerid);
		if(Paid[playerid][Wheels] == 0)
		{
			RemoveVehicleComponent(vehicleid, ComponentID[Wheels]);
			AddVehicleComponent(vehicleid,VehInfo[vehicleid][cWheels]);
		}
	}
	else if(Current == mHydraulics)
	{
		HideMenuForPlayerEx(Current,playerid);
		ShowMenuForPlayerEx(mTuningMenu, playerid);
		if(Paid[playerid][Hydraulics] == 0)
		{
			RemoveVehicleComponent(vehicleid, ComponentID[Hydraulics]);
			AddVehicleComponent(vehicleid,VehInfo[vehicleid][cHydraulics]);
		}
	}
	else if(Current == mSpoiler)
	{
		HideMenuForPlayerEx(Current,playerid);
		ShowMenuForPlayerEx(mTuningMenu, playerid);
		if(Paid[playerid][Spoiler] == 0)
		{
			RemoveVehicleComponent(vehicleid, ComponentID[Spoiler]);
			AddVehicleComponent(vehicleid,VehInfo[vehicleid][cSpoiler]);//установить старый
		}
	}
	else if(Current == mFrontBumper)
	{
		HideMenuForPlayerEx(Current,playerid);
		ShowMenuForPlayerEx(mTuningMenu, playerid);
		if(Paid[playerid][Front_Bumper] == 0)
		{
			RemoveVehicleComponent(vehicleid, ComponentID[Front_Bumper]);
			AddVehicleComponent(vehicleid,VehInfo[vehicleid][cFrontBumper]);
		}
	}
	else if(Current == mRearBumper)
	{
		HideMenuForPlayerEx(Current,playerid);
		ShowMenuForPlayerEx(mTuningMenu, playerid);
		if(Paid[playerid][Rear_Bumper] == 0)
		{
			RemoveVehicleComponent(vehicleid, ComponentID[Rear_Bumper]);
			AddVehicleComponent(vehicleid,VehInfo[vehicleid][cRearBumper]);
		}
	}
	else if(Current == mSideskirt)
	{
		HideMenuForPlayerEx(Current,playerid);
		ShowMenuForPlayerEx(mTuningMenu, playerid);
		if(Paid[playerid][Sideskirt] == 0)
		{
			RemoveVehicleComponent(vehicleid, ComponentID[Sideskirt]);
			AddVehicleComponent(vehicleid,VehInfo[vehicleid][cSideskirt]);
		}
	}
	else if(Current == mRoof)
	{
		HideMenuForPlayerEx(Current,playerid);
		ShowMenuForPlayerEx(mTuningMenu, playerid);
		if(Paid[playerid][Roof] == 0)
		{
			RemoveVehicleComponent(vehicleid, ComponentID[Roof]);
			AddVehicleComponent(vehicleid,VehInfo[vehicleid][cRoof]);
		}
	}
	else if(Current == mExhaust)
	{
		HideMenuForPlayerEx(Current,playerid);
		ShowMenuForPlayerEx(mTuningMenu, playerid);
		if(Paid[playerid][Exhaust] == 0)
		{
			RemoveVehicleComponent(vehicleid, ComponentID[Exhaust]);
			AddVehicleComponent(vehicleid,VehInfo[vehicleid][cExhaust]);
		}
	}
	else if(Current == mNeon)
	{
		HideMenuForPlayerEx(Current,playerid);
		ShowMenuForPlayerEx(mTuningMenu, playerid);
		if(Paid[playerid][Neons] == 0)
		{
			if( IsValidObjectEx(VehInfo[vehicleid][cNeonl]) ) DestroyObjectEx(VehInfo[vehicleid][cNeonl], 23);
			if( IsValidObjectEx(VehInfo[vehicleid][cNeonr]) ) DestroyObjectEx(VehInfo[vehicleid][cNeonr], 23);
		}
	}
	else if(Current == mTuningMenu)
	{
		SetCameraBehindPlayer(playerid);//Восстановить камеру на место позади игрока
		//после использования функций, подобных SetPlayerCameraPos.
		TogglePlayerControllableEx(playerid, 1);//иначе выйти из меню и освободить чела
		//if(car-1==house) SaveCarInfo();//запускаем ф-ию сохранения данных
		//если машина в которой сидит автомеханик совпадает с номером дома заказчика
	}//для тюнинга конец
}


stock tuning_OnVehicleRespray(playerid, vehicleid, color1, color2, interiorid)
{
	if(interiorid == 1)
	{   //TransFender   //14 //16 //18
		PlayerInfo[playerid][pCash] -= 150;
		/*if(GetPlayerMoneyH(playerid) > 0)
		{
			OnGangsExtortionSBiz(14, 150);
			SBizInfo[14][sbProducts] --;
		}*/
	}
	else if(interiorid == 2)
	{   //LocoLowCo
		PlayerInfo[playerid][pCash] -= 150;
		/*if(GetPlayerMoneyH(playerid) > 0)
		{
			OnGangsExtortionSBiz(15, 150);
			SBizInfo[15][sbProducts] --;
		}*/
	}
	else if(interiorid == 3)
	{   //Wheel_Arch_Angel
		PlayerInfo[playerid][pCash] -= 150;
		/*if(GetPlayerMoneyH(playerid) > 0)
		{
			OnGangsExtortionSBiz(16, 150);
			SBizInfo[16][sbProducts] --;
		}*/
	}
	VehInfo[vehicleid][cColor1] = color1;
	VehInfo[vehicleid][cColor2] = color2;
}
stock tuning_OnVehiclePaintjob(playerid, vehicleid, paintjobid, interiorid)
{   //Выполняется, когда игрок меняет на машине покраску в гараже
//для тюнинга
	if(interiorid == 1)
	{   //TransFender   //14 //16 //18
		PlayerInfo[playerid][pCash] -= 500;
		/*if(GetPlayerMoneyH(playerid) > 0)
		{
			OnGangsExtortionSBiz(14, 500);
			SBizInfo[14][sbProducts] --;
		}*/
	}
	else if(interiorid == 2)
	{   //LocoLowCo
		PlayerInfo[playerid][pCash] -= 500;
		/*if(GetPlayerMoneyH(playerid) > 0)
		{
			OnGangsExtortionSBiz(15, 500);
			SBizInfo[15][sbProducts] --;
		}*/
	}
	else if(interiorid == 3)
	{   //Wheel_Arch_Angel
		PlayerInfo[playerid][pCash] -= 500;
		/*if(GetPlayerMoneyH(playerid) > 0)
		{
			OnGangsExtortionSBiz(16, 500);
			SBizInfo[16][sbProducts] --;
		}*/
	}
	VehInfo[vehicleid][cPaintjob] = paintjobid;
}

stock tuning_OnVehicleMod(playerid, vehicleid, componentid, interiorid)
{
	//new interiorid = CurInt[playerid];//GetPlayerInterior(playerid);
//для тюнинга
	if(interiorid == 1)
	{   //TransFender   //14 //16 //18
		PlayerInfo[playerid][pCash] -= ComponentArray[componentid-1000][compPrice];
		/*if(GetPlayerMoneyH(playerid) > 0)
		{
			//OnGangsExtortionSBiz(14, ComponentArray[componentid-1000][compPrice]);
			//SBizInfo[14][sbProducts] --;
		}*/
	}
	else if(interiorid == 2)
	{   //LocoLowCo
		PlayerInfo[playerid][pCash] -= ComponentArray[componentid-1000][compPrice];
		/*if(GetPlayerMoneyH(playerid) > 0)
		{
			//OnGangsExtortionSBiz(15, ComponentArray[componentid-1000][compPrice]);
			//SBizInfo[15][sbProducts] --;
		}*/
	}
	else if(interiorid == 3)
	{   //Wheel_Arch_Angel
		PlayerInfo[playerid][pCash] -= ComponentArray[componentid-1000][compPrice];
		/*if(GetPlayerMoneyH(playerid) > 0)
		{
			//OnGangsExtortionSBiz(16, ComponentArray[componentid-1000][compPrice]);
			//SBizInfo[16][sbProducts] --;
		}*/
	}

	if(IsValidComponent(componentid, CARMODTYPE_SPOILER)) VehInfo[vehicleid][cSpoiler] = componentid; //GetVehicleComponentInSlot(vehicleid, CARMODTYPE_SPOILER);
	if(IsValidComponent(componentid, CARMODTYPE_HOOD)) VehInfo[vehicleid][cHood] = componentid; //GetVehicleComponentInSlot(vehicleid,  CARMODTYPE_HOOD);
	if(IsValidComponent(componentid, CARMODTYPE_ROOF)) VehInfo[vehicleid][cRoof] = componentid; //GetVehicleComponentInSlot(vehicleid, CARMODTYPE_ROOF);
	if(IsValidComponent(componentid, CARMODTYPE_SIDESKIRT)) VehInfo[vehicleid][cSideskirt] = componentid; //GetVehicleComponentInSlot(vehicleid, CARMODTYPE_SIDESKIRT);
	if(IsValidComponent(componentid, CARMODTYPE_LAMPS)) VehInfo[vehicleid][cLamps] = componentid; //GetVehicleComponentInSlot(vehicleid, CARMODTYPE_LAMPS);
	if(IsValidComponent(componentid, CARMODTYPE_NITRO)) VehInfo[vehicleid][cNitro] = componentid; //GetVehicleComponentInSlot(vehicleid, CARMODTYPE_NITRO);
	if(IsValidComponent(componentid, CARMODTYPE_EXHAUST)) VehInfo[vehicleid][cExhaust] = componentid; //GetVehicleComponentInSlot(vehicleid, CARMODTYPE_EXHAUST);
	if(IsValidComponent(componentid, CARMODTYPE_WHEELS)) VehInfo[vehicleid][cWheels] = componentid; //GetVehicleComponentInSlot(vehicleid, CARMODTYPE_WHEELS);
	if(IsValidComponent(componentid, CARMODTYPE_STEREO)) VehInfo[vehicleid][cStereos] = componentid; //GetVehicleComponentInSlot(vehicleid, CARMODTYPE_STEREO);
	if(IsValidComponent(componentid, CARMODTYPE_HYDRAULICS)) VehInfo[vehicleid][cHydraulics] = componentid; //GetVehicleComponentInSlot(vehicleid, CARMODTYPE_HYDRAULICS);
	if(IsValidComponent(componentid, CARMODTYPE_FRONT_BUMPER)) VehInfo[vehicleid][cFrontBumper] = componentid; //GetVehicleComponentInSlot(vehicleid, CARMODTYPE_FRONT_BUMPER);
	if(IsValidComponent(componentid, CARMODTYPE_REAR_BUMPER)) VehInfo[vehicleid][cRearBumper] = componentid; //GetVehicleComponentInSlot(vehicleid, CARMODTYPE_REAR_BUMPER);
	if(IsValidComponent(componentid, CARMODTYPE_VENT_RIGHT)) VehInfo[vehicleid][cVentRight] = componentid; //GetVehicleComponentInSlot(vehicleid, CARMODTYPE_VENT_RIGHT);
	if(IsValidComponent(componentid, CARMODTYPE_VENT_LEFT)) VehInfo[vehicleid][cVentLeft] = componentid; //GetVehicleComponentInSlot(vehicleid, CARMODTYPE_VENT_LEFT);
}


stock tuning_OnVehicleDeath(vehicleid, killerid)
{
	#pragma unused killerid
	if(vehicleid <= 0) return 1;
	//if(GetVehicleModel(vehicleid) < 400) return 1;
	if(!IsValidVehicle(vehicleid)) return 1;
	DestroyObjectEx(VehInfo[vehicleid][cNeonl], 22);
	//DestroyObjectEx(VehInfo[vehicleid][cNeonr], 22);

	return 1;
}

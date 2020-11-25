//==============================================================================
//для УСТАНОВКИ КОНТРОЛЬНЫХ МЕТОК или пикапов выхода начало

new CallTime[MAX_PLAYERS];//сек. максимальное время с учётом скорости и дистанции
new CallTimeCounter[MAX_PLAYERS];//счётчик секунд до прибытия в чекпоинт


new GPS_OnOff[MAX_PLAYERS];

new gTutorial[MAX_PLAYERS];//признак что игрок проходит интерактивное обучение


//##############################################################################//
//                                                                              //
//                         ИДЕНТИФИКАТОРЫ CHECKPOINT                            //
//                                                                              //
//##############################################################################//


#define CP_NONE             0
#define CP_BANK             1
#define CP_DRIVESCHOOL      2
#define CP_LSPD             3
#define CP_SFPD             4
#define CP_LVPD_UPFLOOR     5
#define CP_LVPD_DOWNFLOOR   6
#define CP_AMMU1            7
#define CP_AMMU2            8
#define CP_AMMU3            9
#define CP_AMMU4            10
#define CP_AMMU5            11
#define CP_CITYHALL_LS      12
#define CP_CITYHALL_SF      13
//#define CP_DIRTTRACK      13
#define CP_BURGER           14
#define CP_PIZZA            15
#define CP_CLUCKIN          16
#define CP_SHOP1            17
#define CP_SHOP2            18
#define CP_SHOP3            19
#define CP_SHOP4            20
#define CP_SHOP5            21
#define CP_SHOP6            22
#define CP_BAR       		23
#define CP_RESTAURANT_LS	24
#define CP_INN              25
#define CP_PIGPEN           26
#define CP_STRIP			27
#define CP_ALHAMBRA			28
#define CP_JIZZY			29
#define	CP_LCN              30
#define	CP_YAKUZA           31
#define CP_RESTAURANT_SF 	32
#define CP_RESTAURANT_LV    33
#define CP_PUMP    			34
#define CP_BIGBOARD			35
#define CP_SHOP13			36

#define CHECKPOINT_NONE 	0
#define CHECKPOINT_HOME 	1000
#define CHECKPOINT_CAR 		2000

#define MAX_POINTS 36 //для УСТАНОВКИ КОНТРОЛЬНЫХ МЕТОК или пикапов выхода начало
//потом из констант создали массив из 30 ячеек в каждоый ячейке её порядковый номер
new checkpointType[MAX_POINTS] =
{//для каждой отметки - тип отметки
	CP_NONE,
	CP_BANK,//1
	CP_DRIVESCHOOL,
	CP_LSPD,
	CP_SFPD,
	CP_LVPD_UPFLOOR,
	CP_LVPD_DOWNFLOOR,
	CP_AMMU1,
	CP_AMMU2,
	CP_AMMU3,
	CP_AMMU4,
	CP_AMMU5,
	CP_CITYHALL_LS,//12
	CP_CITYHALL_SF,
	//CP_DIRTTRACK,
	CP_BURGER,
	CP_PIZZA,
	CP_CLUCKIN,
	CP_SHOP1,
	CP_SHOP2,
	CP_SHOP3,
	CP_SHOP4,
	CP_SHOP5,
	CP_SHOP6,
	CP_BAR,//23
	CP_RESTAURANT_LS,
	CP_INN,
	CP_PIGPEN,
	CP_STRIP,
	CP_ALHAMBRA,
	CP_JIZZY,
	CP_LCN,
	CP_YAKUZA,
	CP_RESTAURANT_SF,
	CP_RESTAURANT_LV,
	CP_PUMP,
	CP_SHOP13//35
};

enum
{
	CP_CS,//0
	CP_FARMER,//1
	CP_MINER,//2
	//CP_WOODSMAN_1,//3
	CP_WOODSMAN_2,//3
	CP_WOODSMAN_3,//4
	CP_CARMECHANIC,//5
	CP_INKASSATOR,//6
	CP_PAPERBOY,//7
	CP_TRUCKER,//8
	CP_TRASHMAN_1,//9
	CP_TRASHMAN_2,//10
	CP_TRASHMAN_3,//11
	CP_LOADER_1,//12
	CP_LOADER_2//13
}

//КООРДИНАТЫ ОБЛАСТЕЙ для
enum coordsinfo
{
	Float:minx,
	Float:miny,
	Float:minz,
	Float:maxx,
	Float:maxy,
	Float:maxz
}
//создали массив координат куба
new Float:checkCoords[MAX_POINTS][6] = {//координаты прямоугольной зоны Xmin,Ymib,Xmax,Ymax
{0.0,0.0,0.0,	0.0,0.0,0.0},//0
//{2304.6860,-17.3539,26.6422,	2317.4216,0.1194,32.5313},			//1BANK int0
{2141.2192,1627.7097,993.4761,	2147.2849,1642.9860,998.3101},		//1 BANK int1
{-2035.7764,-119.4109,1035.0719,-2021.5208,-103.8329,1038.7968},	//2 DRIVESCHOOL int3
//{216.9938,62.2626,1000.9391,	270.0502,92.7940,1008.7142}, 		//3 LSPD int6
{321.6892,-355.1131,1024.5892,	351.0870,-308.1075,1028.7767}, 		//3 LSPD int10  DoT
{213.9826,107.4353,998.9156,	278.4911,126.7266,1014.2188}, 		//4 SFPD int10
{236.5258,167.0018,1006.8615,	301.9364,197.5542,1013.3210}, 		//5 LVPD_UPFLOOR int3
{187.6964,140.0551,1002.9234,	272.0545,182.8795,1003.3777}, 		//6 LVPD_DOWNFLOOR int3
{284.2660,-41.8062,1001.4156,	300.0135,-31.2208,1005.5156}, 		//7 Ammunation'1 int1
{284.0546,-86.4384,1001.4156, 	302.9315,-56.6674,1005.9922},      	//8 Ammunation'2 int4
{284.5042,-112.3049,1001.4156,	298.1554,-102.9325,1005.5078}, 		//9 Ammunation'3 int6
{302.9706,-144.3256,999.5016,	317.0611,-126.0520,1007.8906}, 		//10 Ammunation'4 int7
{307.0826,-169.8995,999.5010,	318.2753,-159.3242,1004.0703}, 		//11 Ammunation'5 int6
{1467.6180,-1768.8267,2105.1101,1492.4149,-1746.6678,2115.7930}, //12 CityHall_LS int16
{333.0099,144.3696,1008.2893,	393.0099,204.3696,1028.8993},  		//13 CityHall int3
//{-2133.4722,-499.8402,35.3359,	-1965.8245,-397.8190,38.7344},		//Dirt Track int4 для гонки на мотоциклах в СФ
{361.3249,-76.5989,1001.4151,	382.6038,-56.4962,1004.6292},		//14 Burger Shot int10
{367.0539,-133.5534,1001.3995,	380.3097,-112.5686,1005.3676},		//15 Stacked Pizza int5
{363.7762,-11.8327,1001.7589,	381.2052,-6.1205,1005.7109},		//16 Cluckin Bell int9
{-35.0952,-188.7431,1002.5469,	-3.3979,-167.9059,1008.7656}, 		//17 Shop 24/7 (V1) int17
{-13.6634,-33.4464,1002.5494,	11.1310,-1.5829,1008.8979},  		//18 Shop 24/7 (V2) int10
{-39.2296,-92.6993,1002.5469,	-12.9542,-73.7699,1008.9487},		//19 Shop 24/7 (V3) int18
{-39.1961,-142.2416,1003.4469,	-14.0429,-122.4566,1007.3311},		//20 Shop 24/7 (V4) int16
{-36.9258,-32.1881,1002.5573,	-25.8106,-1.8185,1009.0845},		//21 Shop 24/7 (V5) int4
{-37.4347,-58.9940,1002.5469,	-16.2656,-48.4956,1008.7020},		//22 Shop 24/7 (V6) int6
{487.6558,-88.5900,998.6578,	512.0635,-67.7503,1003.0469},     	//23 Mistys Bar int11
{-792.3765,490.6441,1367.2328,	-778.7958,509.9493,1376.1953},     	//24 Restaurant int1
{-229.0718,1393.7872,27.6734,	-217.5199,1412.1871,30.7734},     	//25 Lil' Probe'Inn int18
{1201.1422,-16.6343,1000.8219,	1223.4420,12.6656,1004.6573},      	//26 Club PigPen int2
{1205.7052,-41.1430,1000.8531,	1216.8706,-24.0071,1003.8786},     	//27 Nude Strippers Daily int3
{473.7552,-26.5830,1000.5719,	507.0154,-1.2432,1006.4844},     	//28 Club Alhamdra  int17
{-2679.1392,1400.2057,906.2734,	-2634.2732,1431.7091,928.2813},    	//29 Jizzy's Pleasure Domes int3
{942.1009,-62.7917,1001.0172,	972.2289,-42.7766,1004.6172},     	//30 LCN
{-2171.3596,635.3907,1052.2750,	-2157.4666,646.8592,1061.6328},    	//31 Yakuza
{433.4056,-92.2443,999.4547,	460.5465,-78.9595,1000.7374},     	//32 Restaurant int4
{439.0887,-22.5738,1000.5523,	456.3756,-3.8882,1004.2343},     	//33 Restaurant int1
{674.9909,-465.0170,-25.7172,	687.9073,-451.1561,-25.5141},     	//34 PUMP BAR int1
{-26.9292,-91.6188,1003.5469,	456.4319,515.8829,1006.4753}     	//35 shop13 24/7
};
//создали массив координат установки чекпоинтов
new Float:checkpoints[MAX_POINTS][3] = {//для каждой зоны координаты контрольных отметок
{0.0,0.0,0.0},
//{2316.6165,-10.0126,26.7422},			//BANK int0
{2144.2163,1642.8122,993.5761},			//BANK int1
{-2026.7584,-114.3740,1035.1719},		//DRIVESCHOOL int3
//{250.0502,67.6923,1003.6406},           //LSPD int6
{341.8187,-317.9809,1023.6765}, //Z-1.0          //LSPD int10 DoT
{240.4730,112.8435,1003.2188},			//SFPD int10
{292.4986,180.6359,1007.1794}, 		 	//LVPD up int3
{234.2595,159.4841,1003.0234},			//LVPD down int3
{296.2800,-37.3602,1001.5156}, 			//Ammunation'1 int1
{295.6000,-80.0605,1001.5156},      	//Ammunation'2 int4
{290.2196,-109.6215,1001.5156}, 		//Ammunation'3 int6
{308.0652,-140.5119,999.6016},      	//Ammunation'4 int7
{312.7611,-165.6264,999.6010}, 			//Ammunation'5 int6
{1482.9803,-1750.0305,2105.1101},		//CityHall_LS int16 //1482.9803,-1750.0305,2106.1101
{358.2361,166.1549,1008.3828},			//CityHall_SF int3 358.2360,166.2761,1008.3828,101.6979
//{-2111.5686,-443.9720,38.7344},		//DirtTrack int4 для гонки на мотоциклах в СФ
{376.6057,-68.3676,1001.5151},			//Burger Shot int10
{376.7138,-120.1047,1001.4995},			//Stacked Pizza int5
{370.4730,-6.0164,1001.8589},			//Cluckin Bell int9
{-28.5542,-184.4023,1003.5469}, 		//Shop 24/7 (V1) int17
{2.0517,-29.0135,1003.5494},			//Shop 24/7 (V2) int10
{-26.9264,-89.3450,1003.5469},			//Shop 24/7 (V3) int18
{-21.1814,-138.0265,1003.5469},			//Shop 24/7 (V4) int16
{-30.1156,-28.2309,1003.5573},			//Shop 24/7 (V5) int4
{-22.2079,-54.9859,1003.5469},			//Shop 24/7 (V6) int6
{495.7801,-76.0305,998.7578},     		//Mistys Bar int11
{-782.3854,500.0729,1371.7490},    		//Restaurant int1
{-224.7967,1403.9092,27.7734},     		//Lil' Probe'Inn int18
{1215.8767,-12.5477,1000.9219},      	//Club PigPen int2
{1207.2367,-31.5843,1000.9531},     	//Nude Strippers Daily int3
{499.9627,-18.7895,1000.6719},     		//Club Alhamdra  int17
{-2665.2327,1410.2078,906.2734},      	//Jizzy's Pleasure Domes int3
{968.8436,-46.3599,1001.1172},     		//LCN
{-2160.2898,639.9937,1057.5861},      	//Yakuza
{449.4581,-83.6614,999.5547},    		//Restaurant int4
{449.2562,-17.5881,1001.1328},    		//Restaurant int1
{681.5111,-454.3947,-25.6172},    		//Pump Bar int1
{1394.5411,-25.5809,1000.9470}    		//24/7 int1 vw83
};


stock GetCheckpointType(playerid)//возвращает номер строки из массива checkpointType
{   //для сопоставления checkCoords - checkpointType
	return checkpointType[playerCheckpoint[playerid]];//из массива checkpointType вернуть номер строки по текущей координате игрока
	//где playerCheckpoint[playerid] - номер строки из массива checkCoords, где находится игрок
}//для использования этой ф-ии должны быть определены координаты кубов

stock SetPlayerRaceCheckpointEx(playerid, type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size)
{
	DisablePlayerRaceCheckpoint(playerid);
	return SetPlayerRaceCheckpointEx(playerid, type, x, y, z, nextx, nexty, nextz, size);
}

//stock OnPlayerCheckpointTimer(playerid)//вызывается каждую секунду из OneSecondTimers2
stock checkpoint_OneSecondTimers2(playerid)
{   //устанавливает чекпоинты не только в интерьерах но и в открытом мире
	//if(GetPlayerInterior(playerid) == 0) { return 1; }//закоментировано, т.к. надо чтобы работало и на улице, чтобы правильно повторно отображать
	//для УСТАНОВКИ КОНТРОЛЬНЫХ МЕТОК начало
	for(new j=1; j < MAX_POINTS; j++)//sizeof(checkCoords)
	{
		if( IsPlayerInArea(playerid, checkCoords[j]) )
		{//если игрок находится в координатах по строке j из массива checkCoords, т.е. зашёл в область из массива checkCoords
			if(	playerCheckpoint[playerid] != j &&
				//DriveProgress[playerid] == 0 &&
				CP[playerid] == 0)//если предыдущее задание выполнено)//если чекпоинт ещё 999
			{   //если игроку ещё не установлен этот чекпоинт и он не сдаёт экзамен // || CP[playerid] == CP_TRUCKER
				playerCheckpoint[playerid] = j;//номер строки из массива checkCoords
//то присвоить playerCheckpoint номер строки по текущим координатам игрока нахождения игрока в кубе из массива checkCoords

//ВНИМАНИЕ данные ф-ии не должны быть перегружены, т.к. должны работать всегда и не зависимо ни от чего
				DisablePlayerCheckpoint(playerid);//убить предыдущий CP, чтобы изменился размер
				SetPlayerCheckpoint(playerid, checkpoints[j][0],checkpoints[j][1],checkpoints[j][2], CHECKPOINT_SIZE/3);

				/*if(CHECKING == 1)
				{
					format(strings, sizeof(strings), "Set OnPlayerCheckpointTimer(playerid:%d) playerCheckpoint[playerid] = %d", playerid, playerCheckpoint[playerid]);
					SendClientMessage(playerid, COLOR_RED, strings);
				}*/
			}   //установить новый чекпоинт по строке j из списка checkpoints
		}
		else
		{
			if(playerCheckpoint[playerid] == j)
			{   //игрок вышел из области массива checkCoords и не вошлё ни в какую другую
				if(CP[playerid] == 0) DisablePlayerCheckpoint(playerid);
				playerCheckpoint[playerid] = 0;//MAX_POINTS;

				/*if(CHECKING == 1)
				{
					format(strings, sizeof(strings), "Disable OnPlayerCheckpointTimer(playerid:%d) playerCheckpoint[playerid] = %d", playerid, playerCheckpoint[playerid]);
					SendClientMessage(playerid, COLOR_GREEN, strings);
				}*/
			}
		}
	}
	return 1;
}


stock checkpoint_OnPlayerInterior(playerid)
{
   	if(GPS_OnOff[playerid] == 1 && gTutorial[playerid])
   	{
		DisablePlayerCheckpointEx(playerid);
		SetPVarInt(playerid, "gCheckpointStatus", CHECKPOINT_NONE);
		GPS_OnOff[playerid] = 0;
		GameTextForPlayerEx(playerid, "~r~gps off", 5000, 1);
	}
}



stock SetPlayerCheckpointEx(playerid, Float:x, Float:y, Float:z, Float:size)
{
	DisablePlayerCheckpoint(playerid);//без Ex чтобы не сбрасывать if(CP[playerid] != 0) CP[playerid] = 0;
	//if(GetPVarInt(playerid, "IsPlayerCheckpoint") == 0)
    //{
	SetPVarInt(playerid, "IsPlayerCheckpoint", 1);
	//PlaySoundForPlayer(playerid, SOUND_RACE_321);
	PlaySoundForPlayer(playerid, SOUND_RACE_GO);
	new Float:distance;
    if(CP[playerid] != 0)
    {
    	distance = GetPlayerDistanceFromPoint(playerid, x, y, z);
    	new speed;
    	if( IsPlayerInAnyVehicle(playerid) ) speed = VehicleArray[nCarModel[playerid]-400][MaxSpeed];//м/ч
		else speed = 29;//28.5 максимальная скорость бега с горки роллера или сиджея
		MinTimeCheckpoint[playerid] = 1000*floatround(distance/(speed*1000) * 3600);//милисекунд

	   	TimeSetCheckpoint[playerid] = GetTickCount();
		/*if(CHECKING == 1)
		{
	  		format(strings, sizeof(strings), "%s[%d] SetPlayerCheckpoint %d. Distance: %.1f m. MaxSpeed: %d km/h. MinTime: %d sec",
				PlayerName(playerid),playerid, CP[playerid],
				distance, speed/1000, MinTimeCheckpoint[playerid]/1000);
			//Log(JOB, strings);
			SendClientMessage(playerid, COLOR_YELLOW, strings);
		}*/
	}
	SetPlayerCheckpoint(playerid, x, y, z, size);
    //}
	/*if(CHECKING == 1)
	{
		format(strings, sizeof(strings), "SetPlayerCheckpoint(playerid:%d, x:%.4f, y:%.4f, z:%.4f, size:%.2f) CP:%d", playerid, x, y, z, size, CP[playerid]);
		SendClientMessage(playerid, COLOR_YELLOW, strings);
	}*/
	return floatround(distance);
}

stock DisablePlayerCheckpointEx(playerid)
{//DisablePlayerCheckpoint вызванный два раза подряд сбрасывает размер маркера
	/*if(CHECKING == 1)
	{
		format(strings, sizeof(strings), "DisablePlayerCheckpoint(playerid:%d) CP:%d", playerid, CP[playerid]);
		SendClientMessage(playerid, COLOR_YELLOW, strings);
	}*/
    if(GetPVarInt(playerid, "IsPlayerCheckpoint") == 1)
    {
		SetPVarInt(playerid, "IsPlayerCheckpoint", 0);
		PlaySoundForPlayer(playerid, SOUND_PART_MISSION_COMPLETE);

	  	/*format(strings, sizeof(strings), "%s[%d] DisablePlayerCheckpoint %d. Time: %d[minimum %d] sec",
				PlayerName(playerid),playerid, CP[playerid],
				(GetTickCount()-TimeSetCheckpoint[playerid])/1000, MinTimeCheckpoint[playerid]/1000);
		Log(JOB, strings);*/

		if(CP[playerid] != 0) CP[playerid] = 0;
		//PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
		//PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
   		//PlaySoundForPlayer(i, SOUND_CHECKPOINT_AMBER);
		//PlaySoundForPlayer(playerid, SOUND_AMMUNATION_GUN_COLLISION);

		DisablePlayerCheckpoint(playerid);
	}
}


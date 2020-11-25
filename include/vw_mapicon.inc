//СИСТЕМА УСТАНОВКИ ИКОНОК НА КАРТЕ И СНЯТИЕ

//#include "../include/vw_textdraw"

new nMapIcon[MAX_PLAYERS];//счётчик найденых иконок
new nHouseIcon[MAX_PLAYERS];//счётчик найденых иконок домов


//temp
/*enum icon_info
{
	icid[MAX_PLAYER_ICONS],
	bool:view[MAX_PLAYER_ICONS]//состояние отображения - переключатель стримера
}
new iconPlayer[MAX_PLAYERS][icon_info];
*/
//------------------------------------------------------------------------------
#define MAX_STREAM_ICONS 	146///47+8+30+7+12+31+11 = 146	//MAX_HOUSE=52 - всего иконок в массиве
enum iconsinfo {
	zone_id,
    Float:icon_x,
    Float:icon_y,
    Float:icon_z,
    icon_type
}
/*
30},//Police LS
22},//Hospital
6},//Ammunation 3
17},//1 24-7
45},//для магазинов одежды
10},//Burger Shot 4
14},//Cluckin Bell 4
29},//Stacked Pizza 4
49},//Bar LS
48},//Club A LS
54},//Gym LS
55},//GasStation 1
30},//Police SF
19},//CityHall
27},//Mod garage SF
*/


new Float:MapIcons[MAX_STREAM_ICONS][iconsinfo] = {//для каждой зоны координаты иконок на карте
{MI_LOS_SANTOS,			iEntrance_PoliceLS,	30},//Police LS
{MI_LOS_SANTOS,			iEntrance_HospitalLS,	22},//Hospital LS near Ammu
{MI_LOS_SANTOS,			2029.5945,-1404.6426,17.2512,	22},//Hospital LS near speedway
{MI_LOS_SANTOS,			718.7104,-1494.7347,-0.3410,	9},//Boat Yard (Fishboat)
{MI_LOS_SANTOS,			2166.4712,-1671.8424,15.0743,	23},//Cracker House int5
{MI_LOS_SANTOS,			2200.1199,-1970.2765,13.7841,	42},//для мусорщиков
{MI_LOS_SANTOS,			1498.3601,-1583.0318,13.5466,	50},//Restaurant
{MI_LOS_SANTOS,			575.2432,-1386.8186,14.3096,	50},//Restaurant4

{MI_LOS_SANTOS,		 	2400.5427,-1980.8321,13.5466,	6},//Ammunation 3
{MI_LOS_SANTOS,		 	1368.4923,-1279.7358,13.5466,	6},//Ammunation 4
{MI_LOS_SANTOS,			1833.7707,-1842.5566,13.5781,	17},//1 24-7
{MI_LOS_SANTOS,			1315.5262,-897.9868,39.5778,	17},//3 24-7
{MI_LOS_SANTOS,			1352.3679,-1759.1234,13.5078,	17},//4 24-7
{MI_LOS_SANTOS,			2139.4431,-1191.9460,23.9922,	17},//5 24-7
{MI_LOS_SANTOS,			702.6688,-1778.4446,13.6328,	17},//13 24-7

{MI_LOS_SANTOS,		 	810.4868,-1616.1850,13.5466,	10},//Burger Shot 4
{MI_LOS_SANTOS,		 	1199.2768,-918.1469,43.1230,	10},//Burger Shot 5
{MI_LOS_SANTOS,	 		2419.9328,-1508.9604,24.0,		14},//Cluckin Bell 4
{MI_LOS_SANTOS,	 		2397.8315,-1899.1832,13.5466,	14},//Cluckin Bell 5
{MI_LOS_SANTOS,		 	2105.4880,-1806.5102,13.5544,	29},//Stacked Pizza 4
{MI_LOS_SANTOS,			2310.0244,-1643.4873,14.8268,	49},//Bar LS
{MI_LOS_SANTOS,			1222.2057,-1414.9725,13.3447,	49},//Bar
{MI_LOS_SANTOS,			1952.7180,-2004.0569,13.5469,	49},//Кофейня

{MI_LOS_SANTOS,			1836.8675,-1682.4508,13.3297,	48},//Club A LS
{MI_LOS_SANTOS,			2421.5773,-1219.2744,25.5590,	48},//Club P LS
{MI_LOS_SANTOS,			1322.5630,-1711.5302,13.5469,	48},//Club

{MI_LOS_SANTOS,			2229.9406,-1721.3133,13.5619,	54},//Gym LS
{MI_LOS_SANTOS,			454.2030,-1477.9973,30.8143,	45},//для магазинов одежды Didier Sachs
{MI_LOS_SANTOS,			499.5526,-1360.6258,16.3679,	45},//для магазинов одежды Pro-Laps
{MI_LOS_SANTOS,			1456.5520,-1137.7790,23.9577,	45},//для магазинов одежды Zip
{MI_LOS_SANTOS,			2112.8173,-1211.4687,23.9629,	45},//для магазинов одежды SubUrban
{MI_LOS_SANTOS,			2244.3471,-1665.5544,15.4764,	45},//для магазинов одежды Binco
{MI_LOS_SANTOS,			iEntrance_Accessor,	45},//для магазинов аксесуар

{MI_LOS_SANTOS,			1043.5872,-1042.9121,31.7864,	27},//Mod garage LS TransFender
{MI_LOS_SANTOS,			2651.3069,-2039.4761,13.5500,	27},//Mod garage LS LocoLowCo

{MI_LOS_SANTOS,			999.4829,-918.4880,42.3281,		55},//GasStation 1
{MI_LOS_SANTOS,			1929.5913,-1778.7913,13.5469,	55},//GasStation 2
{MI_LOS_SANTOS,			iEntrance_CityHallLS,			19},//CityHall
{MI_LOS_SANTOS,			iEntrance_CNNStudio,			12},
{MI_LOS_SANTOS,			iEntrance_Accessor,			39},
{MI_LOS_SANTOS,			iEntrance_Port,				9},

{MI_LOS_SANTOS,			iEntrance_Grove,			62},
{MI_LOS_SANTOS,			iEntrance_Ballas,			59},
{MI_LOS_SANTOS,			iEntrance_Aztecas,			58},
{MI_LOS_SANTOS,			iEntrance_Vagos ,			60},
{MI_LOS_SANTOS,			iEntrance_Rifa,				61},
{MI_LOS_SANTOS,			iEntrance_LCN,				26},
//47
//------------------------------------------------------------------------------
{MI_WHETSTONE,			-2203.3616,-2310.0723,31.3750,	22},//Angel Pine Medical Center
//{MI_FLINT_COUNTY,		-21.7914,-1120.9694, 1.0781,51},//Truck
{MI_FLINT_COUNTY,		-1799.7954,1200.3747,25.1194,	11},//TowTruck
{MI_FLINT_COUNTY,		-79.9012,-1171.4628,2.1523,		55},//GasStation 3

{MI_WHETSTONE,			-1562.5527,-2733.0141,48.7434,	17},//6 24-7
{MI_WHETSTONE,			-1622.8103,-2694.8433,48.7427,	55},//20 GasStation 4 AngelPine
{MI_WHETSTONE,			-2233.4854,-2555.9817,31.9219,	55},//GasStation AngelPine
{MI_WHETSTONE,	 		-2093.3273,-2464.3691,30.6250,	6},//Ammunation 9
{MI_WHETSTONE,	 		-2155.1416,-2460.2414,30.8516,	14},//Cluckin Bell 3
//8
//------------------------------------------------------------------------------
{MI_SAN_FIERRO,			iEntrance_SchoolSF,	36},//School
{MI_SAN_FIERRO,			iEntrance_PoliceSF,	30},//Police SF
{MI_SAN_FIERRO,			-2426.2612,338.0038,37.0,		19},//CityHall
{MI_SAN_FIERRO,			iEntrance_HospitalSF,	22},//Hospital SF
//{MI_SAN_FIERRO,			-2026.7308,   67.1673,28.6916,20},//Fire SF
{MI_SAN_FIERRO,			-2111.5686,-443.9720,38.7344,	33},//Дерби
{MI_SAN_FIERRO,			-2177.7671,-42.3047,35.3125,	50},//Restaurant
{MI_SAN_FIERRO,		 	-2625.8500,209.1430,4.6166,		6},//Ammunation 1
{MI_SAN_FIERRO,			-2442.7590,755.4096,35.1719,	17},//2 24-7
{MI_SAN_FIERRO,		 	-2356.1340,1008.0551,50.8983,	10},//Burger Shot 1
{MI_SAN_FIERRO,		 	-2336.8337,-166.8560,35.5545,	10},//Burger Shot 2
{MI_SAN_FIERRO,		 	-1912.4093,827.8978,35.2280,	10},//Burger Shot 3
{MI_SAN_FIERRO,	 		-1816.6280,618.5889,35.1719,	14},//Cluckin Bell 1
{MI_SAN_FIERRO,	 		-2672.3232,259.4920,4.6328,		14},//Cluckin Bell 2
{MI_SAN_FIERRO,		 	-1720.9676,1359.7823,7.1852,	29},//Stacked Pizza 1
{MI_SAN_FIERRO,		 	-1808.7132,945.9166,24.8906,	29},//Stacked Pizza 2
{MI_SAN_FIERRO,			-2242.2236,-88.1949,35.3203,	49},//Bar SF
{MI_SAN_FIERRO,			-2550.7783,193.8659,6.2266,		48},//Club SF
{MI_SAN_FIERRO,			-2625.3300,1412.5000,7.0998,	48},//Club SF
{MI_SAN_FIERRO,			-2270.6347,-155.9015,35.3203,	54},//Gym SF
{MI_SAN_FIERRO,			-1882.2561,866.4976,35.1719,	45},//для магазинов одежды Zip
{MI_SAN_FIERRO,			-2373.7763,910.1751,45.4453,	45},//для магазинов одежды Binco
{MI_SAN_FIERRO,			-2489.8754,-29.0603,25.6172,	45},//для магазинов одежды SubUrban
{MI_SAN_FIERRO,			-1942.8154,237.3040,34.1289,	27},//Mod garage SF TransFender
{MI_SAN_FIERRO,			-2714.6714,223.7548,4.3281,		27},//Mod garage SF Wheel_Arch_Angels
{MI_SAN_FIERRO,			-2034.2131,147.5298,28.8359,	55},//GasStation 6
{MI_SAN_FIERRO,			-2419.8804,967.8728,45.2969,	55},//GasStation 7
{MI_SAN_FIERRO,			-1677.2815,430.2717,7.1797,		55},//GasStation 8
{MI_SAN_FIERRO,			-1436.8766,-526.8726,15.6719,	55},//GasStation 22
{MI_SAN_FIERRO,			iEntrance_FBI,	30},//FBI
{MI_SAN_FIERRO,			iEntrance_Yakudza,	44},
//30
//------------------------------------------------------------------------------
{MI_TIERRA_ROBADA_UP,	-1514.8284, 2519.9355,55.9960,	22},//Medical Center El Quebrados
{MI_TIERRA_ROBADA_UP,	-2187.3662,2416.4893,5.1651,	9},//boat school
{MI_TIERRA_ROBADA_UP,	-1321.5563,2697.5425,50.2663,	55},//GasStation 9
{MI_TIERRA_ROBADA_UP,	-1467.5270,1872.7051,32.6328,	55},//GasStation 10
{MI_TIERRA_ROBADA_UP,	-1508.9592,2609.8745,55.8358,	6},//Ammunation 5
{MI_TIERRA_ROBADA_UP,	-1212.7629,1831.2475,41.9295,	14},//Cluckin Bell 8
{MI_TIERRA_ROBADA_D,	-828.0928,1503.2443,19.6667,	52},//0 BANK $
//7
{MI_BONE_COUNTY,		-320.1530,1049.2471,20.3403,	22},// Fort Carson Medical Center
{MI_BONE_COUNTY,		-53.8978,1188.7588,19.3594,		50},//Restaurant
{MI_BONE_COUNTY,		-181.4806,1034.8153,19.7422,	17},//9 24-7
{MI_BONE_COUNTY,		-88.9813,1378.3249,10.4694,		49},//Lil' Probe'Inn
{MI_BONE_COUNTY,		697.0750,1950.5222,5.5432,		48},//Big Spread Ranch
{MI_BONE_COUNTY,	 	-315.2091,829.8767,14.2419,		6},//Ammunation 10
{MI_BONE_COUNTY,	 	777.2747,1871.4372,4.9067,		6},//Ammunation 11
{MI_BONE_COUNTY,	 	172.5700,1176.3631,14.7643,		14},//Cluckin Bell 6
{MI_BONE_COUNTY,		59.2713,1221.9875,18.8659,		55},//GasStation11
{MI_BONE_COUNTY,		639.6429,1684.5088,7.1875,		55},//GasStation12
{MI_BONE_COUNTY,		406.9748,2449.5771,17.9000,		55},//GasStation20
{MI_BONE_COUNTY,		iEntrance_Barracks,		18},
//12
//------------------------------------------------------------------------------
{MI_LAS_VENTURAS,		iEntrance_HospitalLV,	22},//Hospital LV
{MI_LAS_VENTURAS,		iEntrance_PoliceLV,	30},//Police LV
{MI_LAS_VENTURAS,	 	2158.7312,943.1644,10.8203,		6},//Ammunation 7
{MI_LAS_VENTURAS,	 	2538.7812,2083.8889,10.8203,	6},//Ammunation 8
{MI_LAS_VENTURAS,		2885.0651,2453.5410,11.0690,	17},//7 24-7
{MI_LAS_VENTURAS,		2546.6286,1971.6135,10.8203,	17},//8 24-7
{MI_LAS_VENTURAS,		1936.8431,2307.1413,10.8203,	17},//10 24-7
{MI_LAS_VENTURAS,		2247.7543,2397.4843,10.8203,	17},//11 24-7
{MI_LAS_VENTURAS,		2194.2485,1990.9260,12.2966,	17},//12 24-7
{MI_LAS_VENTURAS,	 	1158.2558,2072.2023,11.0625,	10},//Burger Shot 6
{MI_LAS_VENTURAS,	 	1873.0262,2071.9895,11.0625,	10},//Burger Shot 7
{MI_LAS_VENTURAS,	 	2472.2595,2034.2578,11.0625,	10},//Burger Shot 8
{MI_LAS_VENTURAS,	 	2170.2089,2795.5876,10.8203,	10},//Burger Shot 9
{MI_LAS_VENTURAS,	 	2637.6860,1671.8465,11.0234,	14},//Cluckin Bell 7
{MI_LAS_VENTURAS,	 	2393.2626,2042.5649,10.8203,	14},//Cluckin Bell 9
{MI_LAS_VENTURAS,		2351.7880,2532.5598,10.8203,	29},//Stacked Pizza 5
{MI_LAS_VENTURAS,		2756.2812,2476.4653,11.0625,	29},//Stacked Pizza 8
{MI_LAS_VENTURAS,		2083.3647,2223.7563,11.0234,	29},//Stacked Pizza 9
{MI_LAS_VENTURAS,		2441.2041,2064.5314,10.8203,	49},//CrowBar
{MI_LAS_VENTURAS,		1968.7314,2295.1740,16.4559,	54},//Below the Belt Gym
{MI_LAS_VENTURAS,		2543.3435,1024.6756,10.8203,	48},//Nude Strippers Daily
{MI_LAS_VENTURAS,		2507.4045,1242.6722,10.8203,	48},//The Tamels Goe
{MI_LAS_VENTURAS,		1656.3730,1733.2867,10.8281,	45},//Binco
{MI_LAS_VENTURAS,		2572.0559,1904.2950,11.0234,	45},//Zip'3
{MI_LAS_VENTURAS,		2825.5346,2406.8164,11.0625,	45},//Train Hard
{MI_LAS_VENTURAS,		2635.2903,1129.1829,11.1797,	55},//GasStation13
{MI_LAS_VENTURAS,		2188.3865,2467.6897,11.2422,	55},//GasStation14
{MI_LAS_VENTURAS,		2152.7869,2734.4658,11.1763,	55},//GasStation15
{MI_LAS_VENTURAS,		2119.3271,897.5119,11.1797,		55},//GasStation16
{MI_LAS_VENTURAS,		1597.7955,2219.9819,11.0692,	55},//GasStation17
{MI_LAS_VENTURAS,		1581.8795,1181.0317,12.2125,	55},//GasStation21
//31
//------------------------------------------------------------------------------
{MI_RED_COUNTY,			iEntrance_Store,				38},
{MI_RED_COUNTY,			-49.9002,-269.6879,6.6332,		51},//Truck
{MI_RED_COUNTY,		 	628.7086,-571.7820,17.0885,		30},//RCPD
{MI_RED_COUNTY,		 	2334.0927,61.5121,26.4846,		6},//Ammunation 2
{MI_RED_COUNTY,		 	242.8612,-178.3867,1.5822,		6},//Ammunation 6
{MI_RED_COUNTY,		 	203.4530,-201.9447,1.5779,		29},//Stacked Pizza 3
{MI_RED_COUNTY,			2333.1215,74.9011,26.6210,		29},//Stacked Pizza 6
{MI_RED_COUNTY,			1367.2307,248.4573,19.5669,		29},//Stacked Pizza 7
{MI_RED_COUNTY,			681.6571,-473.8746,16.5363,		49},//Pump Bar
{MI_RED_COUNTY,			1373.9202,468.7967,20.2013,		55},//GasStation18
{MI_RED_COUNTY,			660.5143,-575.3116,16.3359,		55}//GasStation19
//11
};//для УСТАНОВКИ ИКОНОК НА КАРТЕ конец
stock mapicon_OnPlayerConnect(playerid)
{
	PlayerInZone[playerid] = NOT_ZONES;//номер зоны в которой находится игрок для УСТАНОВКИ ИКОНОК НА КАРТЕ
}

//stock OnPlayerMapIconsTimer(playerid)//вызывается каждую секунду
stock mapicon_OneSecondTimers(playerid)
{ 	//для УСТАНОВКИ ИКОНОК НА КАРТЕ
	//if(AFK_IdleTime[playerid] >= 3) return 1;
	if(PlayerInfo[playerid][pInt] != 0) return 1;
	new strtmp[MAX_STRING];
	for(new z=0; z<MAX_ZONES; z++)
	{
		if( IsPlayerInZone(playerid, z) )//!!! //если игрок находится в координатах по строке z из массива zones
		{   //если игрок находится в какой либо из зон
			if(PlayerInZone[playerid] != z)//если иконки для этого игрока не установлены на эту зону
			{//если эта зона не равна предыдущей, т.е. произошла смена зоны

				PlayerTextDrawSetString(playerid, txdPlayerZone[playerid], zones[z][zone_name]);
				format(strtmp, sizeof(strtmp), "~w~WELCOME ~n~TO ~y~%s", zones[z][zone_name]);
				GameTextForPlayerEx(playerid, strtmp, 1000, 4);//6 выводим название зоны RusToGame(strtmp)
				
			    /*for(new row = 0; row < MAX_PLAYER_ICONS; row++)
			    {   //удаляем все предыдущие от 0 до 99
			    	if(row >= MAX_PLAYER_ICONS) break;//пропускаем зарезервированные для пожаров и кольцевых гонок
			    	if(row == MAX_PLAYER_ICONS-MAX_RADARS) continue;
					RemovePlayerMapIcon(playerid, row);
				}*/

				//--------------------------------------------------------------
				nMapIcon[playerid] = 0;
				new IconList[MAX_STREAM_ICONS+MAX_HOUSE];//массив для хранения найденых
				//получаем из массива список иконок соот. данной зоне и заносим их в другой массив
			    for(new row = 0; row < MAX_STREAM_ICONS; row++)
			    {   //сканируем все иконки построчно
					if(MapIcons[row][zone_id] == zones[z][zone_id])
	 				{   //если иконка принадлежит зоне где находится чувак
						IconList[nMapIcon[playerid]] = row;//записываем строку найденой иконки в массиве MapIcons
//ИНФОРМИРОВАНИЕ
//format(strtmp, sizeof(strtmp), "IconList[nMapIcon]: %d[%d]", IconList[nMapIcon[playerid]], nMapIcon[playerid]);
//SendClientMessageEx(playerid, COLOR_PINK, strtmp);

						nMapIcon[playerid] ++;//счётчик найденых иконок
						//if(nMapIcon[playerid] >= MAX_PLAYER_ICONS) break;//если загружено больше 99 то оборвать
					}
				}
			    for(new iconid = 0; iconid < nMapIcon[playerid]; iconid++)//ind - чтобы не устанавливались другие иконки
			    {   //устанавливаем иконки по строке iconid из массива IconList[iconid]
					if(iconid >= MAX_PLAYER_ICONS) { break; } //пропускаем зарезервированные
					RemovePlayerMapIcon(playerid, iconid);
					SetPlayerMapIcon(playerid,
						iconid,
						MapIcons[IconList[iconid]][icon_x],
						MapIcons[IconList[iconid]][icon_y],
						MapIcons[IconList[iconid]][icon_z],
						MapIcons[IconList[iconid]][icon_type],
						0,
						MAPICON_GLOBAL);//MAPICON_LOCAL);
//ИНФОРМИРОВАНИЕ
//format(strtmp, sizeof(strtmp), "SetPlayerMapIcon1: %d", iconid);
//SendClientMessageEx(playerid, COLOR_PINK, strtmp);
		    	}
				//--------------------------------------------------------------
				nHouseIcon[playerid] = 0;
			    for(new h = 0; h < MAX_HOUSE; h++)
			    {   //сканируем все дома построчно
					if(HouseInfo[h][hZone] == zones[z][zone_id])
	 				{   //если дом принадлежит зоне где находится чувак
						IconList[(nMapIcon[playerid]+nHouseIcon[playerid])] = h;//записываем строку найденой иконки в массив
//ИНФОРМИРОВАНИЕ
//format(strtmp, sizeof(strtmp), "IconList[nMapIcon+nHouseIcon]: %d[%d+%d]", IconList[(nMapIcon[playerid]+nHouseIcon[playerid])], nMapIcon[playerid], nHouseIcon[playerid]);
//SendClientMessageEx(playerid, COLOR_PINK, strtmp);
						nHouseIcon[playerid] ++;//счётчик найденых иконок
						//if((nMapIcon[playerid]+nHouseIcon[playerid]) >= MAX_PLAYER_ICONS) break;//если загружено больше 99 то оборвать
					}
				}
//ИНФОРМИРОВАНИЕ
//format(strtmp, sizeof(strtmp), "nMapIcon:%d nHouseIcon:%d", nMapIcon[playerid], nHouseIcon[playerid]);
//SendClientMessageEx(playerid, COLOR_PINK, strtmp);
			    for(new iconid = nMapIcon[playerid]; iconid < (nMapIcon[playerid]+nHouseIcon[playerid]); iconid++)//ind - чтобы не устанавливались другие иконки
			    {   //устанавливаем иконки по строке iconid из массива IconList[iconid]
					if(iconid >= MAX_PLAYER_ICONS) {  break; } //пропускаем зарезервированные
					RemovePlayerMapIcon(playerid, iconid);
					if(HouseInfo[IconList[iconid]][hOwned] == 0)
					{
						SetPlayerMapIcon(playerid,
							iconid,
							HouseInfo[IconList[iconid]][hEntranceX],
							HouseInfo[IconList[iconid]][hEntranceY],
							HouseInfo[IconList[iconid]][hEntranceZ],
							31,	0,	MAPICON_GLOBAL);//чтобы было видно за пределами радара
					}
					else
					{
						SetPlayerMapIcon(playerid,
							iconid,
							HouseInfo[IconList[iconid]][hEntranceX],
							HouseInfo[IconList[iconid]][hEntranceY],
							HouseInfo[IconList[iconid]][hEntranceZ],
							32,	0,	MAPICON_LOCAL);
					}
//ИНФОРМИРОВАНИЕ
//format(strtmp, sizeof(strtmp), "SetPlayerMapIcon2: %d", iconid);
//SendClientMessageEx(playerid, COLOR_PINK, strtmp);
		    	}
				//--------------------------------------------------------------
			    PlayerInZone[playerid] = z;//иконки установлены, чтобы не выполнялось постояннно
/*
SetPlayerMapIcon(playerid, iconid, Float:x, Float:y, Float:z, markertype, color, style)
Style
0: MAPICON_LOCAL                Display in the player's local area(показывается в пределах радара)
//не загромождает радар
1: MAPICON_GLOBAL               Display always(показывается на всю карту)
2: MAPICON_LOCAL_CHECKPOINT     Display in the player's local area and has a checkpoint marker
3: MAPICON_GLOBAL_CHECKPOINT    Display always and has a checkpoint marker(показывает иконку и дополнительно чекпоинт)
//этот чекпоинт не вызывает паблик
//http://forum.sa-mp.com/showthread.php?t=295742&highlight=MAPICON_GLOBAL_CHECKPOINT
*/
   			}
		}
		else
		{//если игрок через секунду остался в той же зоне
			if(PlayerInZone[playerid] == z)
			{
			    for(new row = 0; row < MAX_PLAYER_ICONS; row++)
			    {
			    	if(row >= MAX_PLAYER_ICONS) break;//пропускаем зарезервированные
			    	if(row == MAX_PLAYER_ICONS-32) continue;//#define MAX_RADARS 32
					RemovePlayerMapIcon(playerid, row);
//ИНФОРМИРОВАНИЕ
//format(strtmp, sizeof(strtmp), "RemovePlayerMapIcon: %d", row);
//SendClientMessageEx(playerid, COLOR_PINK, strtmp);
				}
				PlayerInZone[playerid] = NOT_ZONES;
			}
		}
	}
	//--------------------------------------------------------------------------
		
	return 1;
}
/*
new MAP_ICON_COUNTER;
stock SetPlayerMapIconEx((playerid, iconid, Float:x, Float:y, Float:z, markertype, color, style)
{
//если иконка не существует, то поставить
	MAP_ICON_COUNTER++;
	return SetPlayerMapIcon(playerid, iconid, x, y, z, markertype, color, style);
}


stock RemovePlayerMapIconEx(playerid, iconid)
{
//если иконка существует, то удалить
 	MAP_ICON_COUNTER--;
	return RemovePlayerMapIcon(playerid, iconid);
}*/

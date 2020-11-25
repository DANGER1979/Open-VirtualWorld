#define GTFP(%0,%1,%2) 		format(format_str, 144, %1, %2) && GameTextForPlayer(%0, format_str, 5000, 1)
//GTFP(playerid, "~w~Welcome to the ~n~~y~Los Santos Police Department", 5000, 1);

//входы/выходы из интерьера
new gPDLockDoor = 0;//двери полицейских участков закрыты
new gLCNLockDoor = 0;//двери La Cosa Nostra открыты
new gYLockDoor = 0;//двери Yakudza открыты
new gCityHallLockDoor = 0;
new gSchoolLockDoor = 0;
new gBarracksLockDoor = 0;
new gHospitalLockDoor = 0;
new gCNNStudioLockDoor = 0;
new gCasinoLockDoor = 0;//для дверей казино


new gMedicBill[MAX_PLAYERS];//для прохождения лечения после смерти перевести на пивар

//для админки чтобы показать все интерьеры что есть
enum ieInfo
{
	ieDiscription[32],//описание
	ieInt,//ID интерьера
	Float:ieExitX,//координаты выхода
	Float:ieExitY,
	Float:ieExitZ,
	Float:ieExitA
};
new InteriorInfoExample[146][ieInfo] = {
{"24/7_1",17,-25.72,-187.82,1003.55,5.08},
{"24/7_2",10,6.09,-28.9,1003.55,5.04},
{"24/7_3",18,-30.99,-89.68,1003.55,359.84},
{"24/7_4",16,-26.19,-140.92,1003.55,2.91},
{"24/7_5",4,-27.84,-26.67,1003.56,184.31},
{"24/7_6",6,-26.83,-55.58,1003.55,3.95},

{"AmmuNation1",7,315.24,-140.89,999.6,7.42},
{"AmmuNation2",1,285.84,-39.02,1001.52,0.75},
{"AmmuNation3",4,291.76,-80.13,1001.52,290.22},
{"AmmuNation4",6,297.14,-109.87,1001.52,20.23},
{"AmmuNation5",6,316.5,-167.63,999.59,10.3},

{"RyderHouse",2,2447.87,-1704.45,1013.51,314.53},
{"SweetHouse",1,2527.02,-1679.21,1015.5,260.97},
{"JohnsonHouse",3,2496.05,-1695.17,1014.74,179.22},
{"OG_LocHouse",3,512.93,-11.69,1001.57,198.77},
{"PairBurglaryHouses",2,446.63,1397.74,1084.3,343.96},

{"SafeHouse1",5,2233.69,-1112.81,1050.88,8.65},
{"SafeHouse2",6,1211.25,1049.02,359.94,170.93},
{"SafeHouse3",9,2319.13,-1023.96,1050.21,167.4},
{"SafeHouse4",10,2261.1,-1137.88,1050.63,266.88},
{"UnusedSafeHouse",12,2323.71,-1147.65,1050.71,206.54},

{"Warehouse1",18,1290.41,1.95,1001.02,179.94},
{"Warehouse2",1,1412.15,-2.28,1000.92,114.66},
{"Warehouse3",0,2135.2,-2276.28,20.67,318.59},

{"House1",1,224.29,1289.19,1082.14,359.87},
{"House2",2,225.57,1240.06,1082.14,96.29},
{"House3",3,234.61,1187.82,1080.26,349.48},
{"House4",4,261.12,1287.22,1080.26,178.91},
{"House5",5,227.76,1114.38,1080.99,266.26},
{"House6",5,239.28,1114.2,1080.99,270.27},
{"House7",15,295.14,1473.37,1080.26,352.95},

{"House13",4,221.68,1142.5,1082.61,184.96},
{"House14",10,24.38,1341.18,1084.38,8.33},
{"House15",4,-262.18,1456.62,1084.37,82.46},
{"House16",5,22.86,1404.92,1084.43,349.62},
{"House17",5,140.37,1367.88,1083.86,349.24},
{"House18",6,234.28,1065.23,1084.21,4.39},
{"House19",6,-68.51,1353.85,1080.21,3.57},
{"House20",15,-285.25,1471.2,1084.38,85.65},
{"House21",8,-42.53,1408.23,1084.43,172.07},
{"House22",9,84.92,1324.3,1083.86,159.56},
{"House23",9,260.74,1238.23,1084.26,84.31},

{"BikeSchool",0,1168.51,1360.11,10.93,196.59},
{"BikeSchool",3,1494.86,1306.48,1093.3,196.07},
{"DrivingSchool",3,-2031.12,-115.83,1035.17,190.19},

{"LS_PoliceDepartment",6,246.67,65.8,1003.64,7.96},
{"SF_PoliceDepartment",10,246.07,108.97,1003.22,0.29},
{"LV_PoliceDepartment",3,288.47,170.06,1007.18,22.05},

{"GantonGym",5,770.8,-0.7,1000.73,22.86},
{"CobraGym",6,773.89,-47.77,1000.59,10.72},
{"BeltGym",7,773.73,-74.7,1000.65,5.23},

{"BarberShop",3,418.47,-80.46,1001.8,343.24},
{"BarberShop2",2,414.3,-18.8,1001.8,41.43},
{"BarberShop3",12,411.97,-51.92,1001.9,173.34},

{"ZeroRCShop",6,-2240.1,136.97,1035.41,269.1},
{"SexShop",3,-100.27,-22.94,1000.72,17.29},

{"Transfenders",1,621.45,-23.73,1000.92,15.68},
{"LocoLowCo",2,611.35,-77.56,998.0,320.93},
{"WheelArchAngels",3,612.22,-123.9,997.99,266.57},

{"BloodBowlStadium",15,-1417.89,932.45,1041.53,0.7},
{"ViceStadium",16,-1401.07,1265.37,1039.87,178.65},
{"DirtbikeStadium",4,-1421.56,-663.83,1059.56,170.93},
{"KickstartStadium",14,-1420.43,1616.92,1052.53,159.13},
{"Oval_Stadium",1,-1402.66,106.39,1032.27,105.14},
{"8Track_Stadium",7,-1403.01,-250.45,1043.53,355.86},

{"CaligulaCasino",1,2233.94,1711.8,1011.63,184.39},
{"Casino(Redsands_West)",12,1133.35,-7.85,1000.68,165.85},
{"OldVenturasStripCasino",2,2236.7,-1078.95,1049.02,2.57},
{"CasinoFourDragons",10,2016.12,1017.15,996.88,88.01},

{"Brothel",3,974.02,-9.59,1001.15,22.6},
{"Brothel2",3,961.93,-51.91,1001.12,95.54},
{"InsideTrackBetting",3,830.6,5.94,1004.18,125.81},
{"BlastinFoolsRecords",3,1037.83,0.4,1001.28,353.93},
{"BigSpreadRanch",3,1212.15,-28.54,1000.95,170.57},
{"BDup_Apartment",3,1527.05,-12.02,1002.1,350.0},
{"BDup_CrackPalace",2,1523.51,-47.82,1002.27,262.7},

{"PlanningDepartment",3,386.53,173.64,1008.38,63.74},
{"ProLaps",3,206.46,-137.71,1003.09,10.93},
{"LV_Tattoo",3,-201.22,-43.25,1002.27,45.86},
{"SF_Tattoo",17,-202.94,-6.7,1002.27,204.27},

{"Diner1",5,454.99,-107.25,999.44,309.02},
{"PizzaStack",5,372.56,-131.36,1001.49,354.23},
{"WorldOfCoq",1,445.6,-6.98,1000.73,172.21},
{"Victim",5,225.03,-9.18,1002.22,85.53},
{"SubUrban",1,204.12,-46.8,1001.8,357.58},
{"DeniseBedroom",1,245.23,304.76,999.15,273.44},
{"HelenaBarn",3,290.62,309.06,999.15,89.92},
{"BarbaraLove",5,322.5,303.69,999.15,8.17},
{"SF_Garage",1,-2041.23,178.4,28.85,156.22},
{"PigPenStrip",2,1204.67,-13.54,1000.92,350.02},

{"LibertyCity",1,-741.85,493.0,1371.98,71.78},
{"RC_Battlefield",10,-1129.89,1057.54,1346.41,274.53},
{"Burgershot",10,366.02,-73.35,1001.51,292.01},
{"KatieLovenest",2,269.64,305.95,999.15,215.66},
{"AngelPineTrailer",2,1.19,-3.24,999.43,87.57},
{"Zip",18,161.4,-94.24,1001.8,0.79},
{"PleasureDomes",3,-2638.82,1407.34,906.46,94.68},
{"MaddDoggMansion",5,1267.84,-776.96,1091.91,231.34},
{"BigSmokeCrackPalace",2,2536.53,-1294.84,1044.13,254.95},
{"BurningDesireBuilding",5,2350.16,-1181.07,1027.98,99.19},
{"WuZi",1,-2158.67,642.09,1052.38,86.54},
{"AbandonedACtower",10,419.89,2537.12,10.0,67.65},
{"Wardrobe/Changing_room",14,256.9,-41.65,1002.02,85.88},
{"DidierSachs",14,204.17,-165.77,1000.52,181.76},
{"Club",17,493.14,-24.26,1000.68,356.99},
{"Atrium",18,1727.29,-1642.95,20.23,172.42},
{"LS_TattooParlor",16,-202.84,-24.03,1002.27,252.82},
{"ShermanDam",17,-944.24,1886.15,5.01,179.85},
{"JeffersonMotel",15,2217.28,-1150.53,1025.8,273.73},
{"JetInterior",1,1.55,23.32,1199.59,359.91},
{"Pump",1,681.62,-451.89,-25.62,166.17},
{"Binco",15,207.52,-109.74,1005.13,358.62},
{"BudgetInnMotelRoom",12,446.32,509.97,1001.42,330.57},
{"DillimoreGasStation",0,663.06,-573.63,16.34,264.98},
{"LilProbeInn",18,-227.57,1401.55,27.77,269.3},
{"CrackDen",5,227.39,1114.66,1081.0,267.46},
{"JayDiner",4,449.02,-88.99,999.55,89.66},
{"MichelleLoveNest*",4,306.2,307.82,1003.3,203.14},
{"SindaccoAbatoir",1,963.06,2159.76,1011.03,175.31},
{"MillieBedroom",6,345.0,307.18,999.16,193.64},
{"LS_Airport",14,-1864.94,55.73,1055.53,85.85},
{"FrancisIntAirport",14,-1813.21,-58.01,1058.96,335.32},
{"RustyBrownDonuts",17,378.03,-190.52,1000.63,141.02},
{"4DragonsManagerialSuite",11,2003.12,1015.19,33.01,351.58},
{"SecretValleyDiner",6,442.13,-52.48,999.72,177.94},
{"RosenbergOfficeCaligulas",2,2182.2,1628.58,1043.87,224.86},
{"FannyBatter_WhoreHouse",6,748.46,1438.24,1102.95,0.61},
{"ColonelFurhberger",8,2807.36,-1171.7,1025.57,193.71},
{"CluckinBell",9,366.0,-9.43,1001.85,160.53},
{"CamelToe_Safehouse",1,2216.13,-1076.31,1050.48,86.43},
{"CaligulaRoof",1,2268.52,1647.77,1084.23,99.73},
{"VerdantBluffsSafehouse",8,2365.11,-1133.08,1050.88,177.39},
{"Andromada",9,315.45,976.6,1960.85,359.64},
{"FourDragonsJanitorOffice",10,1893.07,1017.9,31.88,86.1},
{"Bar",11,501.96,-70.56,998.76,171.57},
{"Willowfield_Safehouse",11,2283.31,1139.31,1050.9,19.7},
{"PalaminoBank",0,2306.38,-15.24,26.75,274.49},
{"PalaminoDiner",0,2331.9,6.78,26.5,100.24},
{"TorrenoRanch",0,-688.15,942.08,13.63,177.66},
{"ZombotechLobbyArea",0,-1916.13,714.86,46.56,152.28},
{"CryptLS_cemetery",0,818.77,-1102.87,25.79,91.14},
{"BlueberryLiquorStore",0,255.21,-59.68,1.57,1.46},
{"Area69",0,215.15,1874.06,13.14,177.55},
{"MilitaryFuelsDepot",0,2548.48,2823.74,10.82,270.6},
{"OttoAutos",0,-1658.17,1215.0,7.25,103.91},
{"WangCars",0,-1961.63,295.24,35.47,264.49}
};


//##############################################################################//
//#                                                                            #//
//#                          ПЕРЕХОДЫ ПО ИНТЕРЬЕРАМ                            #//
//#                                                                            #//
//##############################################################################//



//#define MAX_HOUSE 52//34
//#define MAX_BIZ 82
//#define MAX_SBIZ 59//51//17+19=36 +11=47
//#define FREEROAM 			255
#define MAX_INT 66//68

//завязываем на ИД пикапа, когда подобрался пикап, определился его ИД и по ИД узнаем у какого интерьера стоит игрок
enum iInfo
{//может быть несколько входов
	iLoc,//0-199 дома, 200-399 бизы, 400-499 компании
	iDiscription[32],//~w~Gun Shop 1 - описание

	iEntranceInt,//1 - интерьер
	Float:iEntranceX,//координаты входа
	Float:iEntranceY,
	Float:iEntranceZ,
	Float:iEntranceA,//угол взгляда после выхода из интерьера
	iEntranceVW,

	iExitInt,//1 - интерьер
	Float:iExitX,//координаты выхода
	Float:iExitY,
	Float:iExitZ,
	Float:iExitA,//угол взгляда после входа в интерьер
	iExitVW,//1 - интерьер

	iLock,//1 - закрыт
	iEntranceCost,//0 - цена входа
	iDate,//дата последнего посещения для собственности как дом, в остальных случаях посещаемость
};//МАССИВ ПЕРЕХОДОВ

/*
enum
{
	//GroveStreet,
	//AccessoriesStore

	BANK_WORLD = MAX_HOUSE+1,
	PORT_WORLD = MAX_HOUSE+81,
//.....
	ACCESSOR_WORLD = MAX_HOUSE+89,
//----------------------------
//ВНИМАНИЕ общественные интерьеры не должны превышать см. const MAX_INT_BENCH = 30;
// Система отеля
	HOTEL_INT = 7, //7 интерьер в отеле
	HOTEL_WORLD = 1, //30 вирт мир в отеле

    POLICE_LS_WORLD = DoT,//10
    POLICE_SF_WORLD = DoT+1,//11
    POLICE_LV_WORLD = DoT+2,//12

	FBI_SF_PARK = 24,
	FBI_SF_WORLD0 = 20,
	FBI_SF_WORLD1 = 21,
	FBI_SF_WORLD2 = 22,

//система больницы
    MEDIC_LS_WORLD1 = 22,//13+20=33
    MEDIC_LS_WORLD2 = 23,//16

    MEDIC_SF_WORLD1 = 24,//14
    MEDIC_SF_WORLD2 = 25,//17

    MEDIC_LV_WORLD1 = 26,//15
    MEDIC_LV_WORLD2 = 27,//18

    MCSA_LS_WORLD1 = 30,
    MCSA_LS_WORLD2 = 31,
    MCSA_LS_WORLD3 = 32,

	DOJ_LS_WORLD1 = 39,
	DOJ_LS_WORLD2 = 40,
	DOJ_LS_WORLD3 = 41
}
*/
//MAX_HOUSE+MAX_BIZ+1

new InteriorInfo[MAX_INT][iInfo] = {
{0, "Motel Down Floor", 0,2233.2930,-1159.7762,26.0906,90.0, 0,		15,2228.3447,-1150.5023,1025.8969,90.0,15,	0,0,0},//1559 Motel Down Floor
{1, "Motel Midle Floor",0,2233.2368,-1159.6725,29.9044,90.0, 0,		15,2193.2273,-1138.6343,1029.8969,180.0,15,	0,0,0},//Motel Midle Floor
{2, "Motel Up Floor", 	0,2193.1313,-1151.2716,33.9240,180.0, 0, 	15,2189.9077,-1179.7893,1033.8896,180.0,15,	0,0,0},//Motel Up Floor
//https://gta.fandom.com/ru/wiki/%D0%9F%D0%BE%D1%80%D1%82%D0%B0%D0%BB:Grand_Theft_Auto:_San_Andreas
{3, "Grove Street", 		0,iEntrance_Grove,180.0,0,		TEAM_GROVE,1869.0273,-2470.0364,1033.5625,0.0,MAX_HOUSE+MAX_BIZ+TEAM_GROVE,	0,0,0},//4
{4, "The Ballas", 			0,iEntrance_Ballas,180.0000,0,	TEAM_BALLAS,1869.0273,-2470.0364,1033.5625,0.0,MAX_HOUSE+MAX_BIZ+TEAM_BALLAS,	0,0,0},//int2
{5, "Varios Los Aztecas", 	0,iEntrance_Aztecas, 288.872,0,	TEAM_AZTEC,1869.0273,-2470.0364,1033.5625,0.0,MAX_HOUSE+MAX_BIZ+TEAM_AZTEC,	0,0,0},
{6, "Los Santos Vagos", 	0,iEntrance_Vagos,228.3235,0,	TEAM_VAGOS,1869.0273,-2470.0364,1033.5625,0.0,MAX_HOUSE+MAX_BIZ+TEAM_VAGOS,	0,0,0},
{7, "San Fierro Rifa", 		0,iEntrance_Rifa,0.0,0,			TEAM_RIFA,1869.0273,-2470.0364,1033.5625,0.0,MAX_HOUSE+MAX_BIZ+TEAM_RIFA,		0,0,0},

{8, "Da Nang Boys", 0,iEntrance_Nang,86.1231,0,		TEAM_NANG,-34.9353,-820.4177,1016.4688, 78.9608,MAX_HOUSE+MAX_BIZ+TEAM_NANG,		0,0,0},
{9, "The Traids", 	0,iEntrance_Triad,172.2558,0,	TEAM_TRIAD,906.9051,-1143.1529,1027.1239, 165.41,MAX_HOUSE+MAX_BIZ+TEAM_TRIAD,	0,0,0},
{10, "Bikers", 		0,iEntrance_Biker,277.2347,0,	TEAM_BIKER,-1976.2394,1057.0684,1063.0779, 273.5192,MAX_HOUSE+MAX_BIZ+TEAM_BIKER,	0,0,0},
{11, "The Mafia", 	0,iEntrance_Mafia,5.4719,0,		TEAM_MAFIA,351.8041,-1587.7388,1038.69, 90.000,MAX_HOUSE+MAX_BIZ+TEAM_MAFIA,		0,0,0},

//{504, "LS Police Department", 1555.5002,-1674.9253,16.2953, 90.0,0, 	6,246.7489,62.5000,1003.6406,0.0,		0,0,0},
//{505, "LSPD Garage", 1568.6418,-1689.9734,6.3188, 175.5158,0, 		6,246.3873,87.9928,1003.6406,179.6283,0,	0,0,0},//1247 11711 1559 ВХОД  в уч. ЛС из гаража
{12, "LS Police Department", 0,iEntrance_PoliceLS,90.0,0, 				DoT,346.5599,-335.9208,1024.6765,0.1769,POLICE_LS_WORLD,	0,0,0},//9
{13, "LSPD Garage", 		0,1568.6418,-1689.9734,6.3188, 175.5158,0, 	DoT,311.3368,-341.2273,1020.6225,359.4339,POLICE_LS_WORLD,	0,0,0},//1247 11711 1559 ВХОД  в уч. ЛС из гаража

//{506, "SF Police Department", -1605.5630,710.7082,14.0672,0.0,0, 		10,246.3969,107.7309,1003.3188,0.0,		0,0,0},
//{507, "SFPD Garage", -1594.2103,716.2173,-4.9063, 270.0,0, 			10,214.2863,121.1713,999.1156, 180.0,0,	0,0,0},//ВХОД  в уч. СФ из гаража
{14, "SF Police Department", 0,iEntrance_PoliceSF,0.0,0,				DoT,1021.0231,346.7713,1004.2559, 356.9413,POLICE_SF_WORLD,		0,0,0},//11//-1605.5630,710.7082,14.0672 - 1021.1658,349.1065,1004.2559
{15, "SFPD Garage", 0,-1594.2103,716.2173,-4.9063, 270.0,0, 			DoT,996.2681,369.1861,1003.7060, 184.3164,POLICE_SF_WORLD,	0,0,0},//-1594.2103,716.2173,-4.9063 - 996.1160,367.4161,1003.6060 ВХОД  в уч. СФ из гаража

{16, "LV Police Department", 0,iEntrance_PoliceLV,0.0,0, 				3,288.6573,167.1678,1007.2719,0.0,POLICE_LV_WORLD,		0,0,0},//13 //1247 1318 11711 1559
{17, "LV Police Department", 0,2287.0569,2432.3826,10.9203, 180.0,0,	3,238.7018,138.9497,1003.2234,0.0,POLICE_LV_WORLD,		0,0,0},
//#define FBI 	11
{18, "FBI", 0,iEntrance_FBI,270.0,0, 									0,-2450.3809,515.0835,54.5697,3.2784,FBI_SF_WORLD1,	0,0,0},//этаж1 переход в инт. fbi_0.inc
{19, "FBI", 0,-2482.3713,522.8125,1054.5657,0.0,FBI_SF_WORLD0, 			0,-2482.3772,521.9155,51.0857,90.0,FBI_SF_WORLD1,		0,0,0},//этаж0
///переход по лестнице с цокольного этажа fbi_0.inc на первый fbi_1.inc

//CreatePickup(1318, 23, -2482.3772,521.9155,51.0857, 21); // пикап который ведет на 0 этаж
//CreatePickup(1318, 23, -2482.3713,522.8125,1054.5657, 20); // пикап который с 0 ведет на 1 этаж

{20, "Barracks", 0,iEntrance_Barracks,91.2041,0,								DoD,195.0423,1930.9695,13.5171, 356.7853,MAX_HOUSE+MAX_BIZ+DoD,	0,0,0},
{21, "Prison", 0,1798.2404,-1578.8049,14.0917,274.1264,0,						DoD,1395.0337,960.5172,3016.7773,98.0875,MAX_HOUSE+MAX_BIZ+DoD,	0,0,0},

//{520, "Hospital LS", 1172.2830,-1323.3102,15.3943,0.0, 				0,1168.6626,1362.2052,11.0293, 180.0,0,	0,0,0},//19132 11711
//{521, "Hospital SF", -2654.9561,640.0498,14.5531,0.0,					0,1168.6626,1362.2052,11.0293, 180.0,0,	0,0,0},//1317 1559
//{522, "Hospital SF Garage", -2594.2395,642.3073,14.4531,0.0, 			0,1165.3844,1346.4550,11.0219, 0.2148,0,	0,0,0},//если игрок находится у входа в больницу SF из гаража
//{523, "Hospital LV", 1607.2955,1815.3499,10.9203,0.0, 				0,1168.6626,1362.2052,11.0293, 180.0,0,	0,0,0},//1317 1559
{22, "Hospital LS", 0,iEntrance_HospitalLS,270.0,0, 							DoH,1389.1150,13.1662,1000.9175,180.0,MEDIC_LS_WORLD1,		0,0,0},//17// пикап в здании больницы
//{DoH, "Hospital LS Garage", 0,1173.0280,-1361.5808,13.9609,259.9784,0,			DoH,1397.4014,-34.7469,1000.9175,357.6965,MEDIC_LS_WORLD1,	0,0,0},///   пикап гаража- пикап лифта 1 этаж
{23, "Hospital LS Level1-2", DoH,1384.4403,-25.8156,1000.9175,0.0,MEDIC_LS_WORLD1, 	DoH,-2088.5310,-161.2691,1055.5968, 90.0,MEDIC_LS_WORLD2,		0,0,0},////  пикап лифта 1 этаж - пикап лифта 2 этаж

{24, "Hospital SF", 0,iEntrance_HospitalSF,180.0,0, 							DoH,1389.1150,13.1662,1000.9175, 177.7371,MEDIC_SF_WORLD1,	0,0,0},//20// пикап в здании больницы
{25, "Hospital SF Garage", 0,-2594.2395,642.3073,14.4531,0.0,0, 				DoH,1397.4014,-34.7469,1000.9175,357.6965,MEDIC_SF_WORLD1, 	0,0,0},///пикап гаража- пикап лифта 1 этаж
{26, "Hospital SF Level1-2", DoH,1384.4403,-25.8156,1000.9175,0.0,MEDIC_SF_WORLD1, 	DoH,-2088.5310,-161.2691,1055.5968, 0.0,MEDIC_SF_WORLD2,		0,0,0},////  пикап лифта 1 этаж - пикап лифта 2 этаж

{27, "Hospital LV", 0,iEntrance_HospitalLV,0.0,0, 								DoH,1389.1150,13.1662,1000.9175,177.7371,MEDIC_LV_WORLD1,		0,0,0},//23// пикап в здании больницы
{28, "Hospital LV Garage", 0,1584.7424,1749.7268,10.8203,174.9461,0,			DoH,1397.4014,-34.7469,1000.9175,357.6965,MEDIC_LV_WORLD1,	0,0,0},///   пикап гаража- пикап лифта 1 этаж
{29, "Hospital LV Level1-2", DoH,1384.4403,-25.8156,1000.9175,0.0,MEDIC_LV_WORLD1,	DoH,-2088.5310,-161.2691,1055.5968, 0.0,MEDIC_LV_WORLD2,		0,0,0},////  пикап лифта 1 этаж - пикап лифта 2 этаж


{30, "MedicalCenter LS", 0,2029.5945,-1404.6426,17.2512,180.0,0, 				DoH,-40.1226,1857.5409,17.6476,270.1563,MCSA_LS_WORLD1,		0,0,0},//17// пикап в здании больницы
{31, "MCSA floor 1 to 2", DoH,-9.1606,1849.5624,17.6476,90.7421,MCSA_LS_WORLD1,	DoH,7.8138,1947.9283,17.6557,91.4306,MCSA_LS_WORLD2,		0,0,0},//17// пикап в здании больницы
{32, "MCSA floor 1 to 3", DoH,-9.3522,1865.4551,17.6476,84.7887,MCSA_LS_WORLD1,	DoH,51.9601,1963.9799,17.6557,88.7147,MCSA_LS_WORLD3,		0,0,0},//17// пикап в здании больницы
{33, "MCSA floor 2 to 3", DoH,7.5475,1963.8838,17.6557,86.6492,MCSA_LS_WORLD2,	DoH,51.8887,1947.8979,17.6557,87.8792,MCSA_LS_WORLD3,		0,0,0},//17// пикап в здании больницы


//{514, "La Cosa Nostra Mansion", 1122.9260,-2037.0017,69.9939, 270.0,			3,965.0754,-53.1345,1001.2000, 90.0,0,	0,0,0},
{34, "La Cosa Nostra Mansion", 0,iEntrance_LCN,89.9549,0,						LCN,1384.9541,-1.6126,1000.9206, 180.0,MAX_HOUSE+MAX_BIZ+LCN,		0,0,0},//26
{35, "La Cosa Nostra Mansion", 0,717.8386,-1276.6028,17.6484,261.7573,0,		LCN,1384.5756,-16.4739,1004.5181, 4.0968,MAX_HOUSE+MAX_BIZ+LCN,	0,0,0},//если игрок находится у входа в особняк LCN крыша

//{39, "Yakudza Mansion SF", 0,-2521.0908,-624.9518,132.8842,0.0,0,				1,-2158.5637,642.5848,1052.3750, 90.0,Yakuza,		0,0,0},
{36, "Yakudza Mansion LS", 0,iEntrance_Yakudza,0.0,0,							Yakuza,-830.5297,1115.5463,1497.1621,2.6750,MAX_HOUSE+MAX_BIZ+Yakuza,		0,0,0},

{37, "City Hall SF", 		0,-2426.2612,338.0038,37.1000,270.0,0, 				3,390.1595,173.7057,1008.3828, 90.0,MAX_HOUSE+MAX_BIZ+DoJ,	0,0,0},//29
{38, "CityHallSF Parking", 	0,-2488.3862,381.4914,27.7676,51.0,0, 				3,366.6021,159.1235,1008.3828,0.0,MAX_HOUSE+MAX_BIZ+DoJ,	0,0,0},//если игрок находится на парковке и входит в мэрию

//{533, "City Hall LS", 1481.1011,-1770.8237,18.7957,0.0, 				3,390.1595,173.7057,1008.3828, 90.0,0,	0,0,0},
{39, "City Hall LS", 0,iEntrance_CityHallLS,0.0,0, 						DoJ,1481.3942,-1768.6542,2106.1101,6.2580,DOJ_LS_WORLD1,	0,0,0},//vw2//DoJ
/*
{43, "CNNStudio LV", 1042.4713,1010.4932,11.1000,0.0,0,					1,2151.5686,1602.9343,1002.0717,270.0,SAN,	0,0,0},//32//если игрок находится у входа в Редакцию Новостей
{43, "Roof CNNStudio", 1030.0594,1010.9195,48.2328,0.0,0,				1,2155.7778,1597.9791,1000.0684,0.0,SAN,	0,0,0},//вход в Редакцию Новостей с крыши
{43, "Parking CNNStudio", 1008.1888,1068.0154,11.0000,3.1802,0,			1,2157.6753,1596.5061,1000.0684, 357.8791,SAN,	0,0,0},//вход в Редакцию Новостей с паркинга
{43, "Basement CNNStudio", 2169.9492,1618.7277,1000.0766, 270.0,SAN,	1,2167.2871,1618.6600,1000.0773,90.0,SAN,	0,0,0},////если игрок находится у входа в подвал Редакции Новостей
*/
//{44, "CNNStudio LS", 0,iEntrance_CNNStudio,7.5031,0,					SAN,1469.6852,-1808.8793,2349.6851,0.0,SAN,	0,0,0},//32//если игрок находится у входа в Редакцию Новостей
//{44, "CNNStudio Floor1-2", SAN,1453.2072,-1802.2932,2349.6951,7.4330,SAN,	SAN,1453.2283,-1801.5675,2643.3000,0.0,SAN,	0,0,0},//лифт
//{44, "ASSEMBLY HALL", SAN,1453.5262,-1794.5765,2643.3000,178.3289,SAN,	SAN,1448.8301,-1814.4724,3234.9810,0.0,SAN,	0,0,0},

{40, "NewsAgency LS", 0,iEntrance_CNNStudio,90.0,0,						0,800.8206,-1328.5050,710.3306,90.0,MAX_HOUSE+MAX_BIZ+SAN,	0,0,0},//32//если игрок находится у входа в Редакцию Новостей
{41, "FOXNews", 0,1654.0929,-1655.2439,22.5156,180.0,0,					SAN,1388.4365,-16.0569,1000.8948,180.0,MAX_HOUSE+MAX_BIZ+41,	0,0,0},//32//если игрок находится у входа в Редакцию Новостей


//{524, "School", -2026.6433,-101.5586,35.2641,0.0, 							3,-2026.9230,-103.7153,1035.2779,180.0,0,	0,0,0}, // Exit School_int3  1314 1559    23
{42, "School SF", 0,iEntrance_SchoolSF,0.0,0, 									DoE,1699.3745,847.5421,1008.4514,0.0,MAX_HOUSE+MAX_BIZ+DoE,	0,0,0}, //36// Exit School_int3  1314 1559    23
{43, "Level 1 To Level 2", DoE,1699.6022,863.3688,1008.4514,186.5395,MAX_HOUSE+MAX_BIZ+DoE, 	DoE,1699.2737,863.6680,1012.6960,178.4972,MAX_HOUSE+MAX_BIZ+DoE,	0,0,0}, // лифт 1 этаж лифт 2 этаж
//{49, "SchoolPoligon", 0,-2029.8828,-120.5207,35.2693, 180.0,0,				DoE,-2029.7716,-119.6176,1035.2719,0.0,DoE,	0,0,0},//38 // Exit School_int3

{44, "Airport LS", 0,1642.3827,-2238.8821,13.4970,180.0,0, 			4,1643.8041,-2319.6848,1020.3306,180.0,MAX_HOUSE+MAX_BIZ+44,	0,0,0},//1317 1559 //int14
//{"LS_Airport",14,-1864.94,55.73,1055.53,85.85},{"FrancisIntAirport",14,-1813.21,-58.01,1058.96,335.32},

{45, "PalaminoBank", 0,2302.9751,-16.1054,26.4844,88.5522,0, 		0,2305.2751,-16.2579,26.7422,266.9449,0,	0,0,0},//bank
{46, "PalaminoBank", 0,2315.5969,1.3799,26.7422,4.6013,0, 			0,2315.4072,-0.5036,26.7422,175.8917,0,		0,0,0},//bank


{47, "8ball Track LS", 0,2695.6235,-1704.6960,11.8438,0.0,0, 		7,-1404.5299,-259.0602,1043.6563,0.0,0,		0,0,0},//1317 1559
{48, "BloodBowl", 0,-2110.5586,-444.1488,38.8344, 90.0,0, 			15,-1463.0767,933.8273,1036.5861,0.0,0,		0,0,0},//1559
{49, "Stunting Track(Kickstart)", 0,1099.4869,1601.4949,12.5469,0.0,0, 14,-1464.6700,1556.1238,1052.5313,0.0,0,	0,0,0},//1559
{50, "Dirt Track LV", 0,1099.4869,1601.4949,12.5469, 180.0,0, 		4,-1443.0554,-581.1879,1055.0472, 0.0,0,	0,0,0},//выход из Dirt Track LV Track int4 (доступно по понедельникам и средам)
{51, "Cracker House", 0,2166.4712,-1671.8424,15.2000, 270.0,0,		5,318.6433,1115.0376,1083.8828,0.0,0,		0,0,0},
{52, "Jizzy", 0,-2660.8396,1421.7869,23.8984,0.0,0,					3,-2660.9045,1417.5636,922.2953,180.0,0,	0,0,0},
{53, "Big Spread Ranch", 0,693.692993,1967.0534,5.6391, 180.0,0,	3,1212.0435,-26.4348,1001.0531,180.0,0,		0,0,0},
{54, "Caligula's Casino", 0,2196.8855,1677.1884,12.4672,0.0,0,		1,2233.9238,1714.5105,1012.4828,0.0,0,		0,0,0},
{55, "Penthouse Suites", 1,2135.7083,1599.4318,1008.4561,270.0,0, 	1,2265.9536,1647.5021,1084.3344,270.0,0,	0,0,0},//BankChangeCaligula's
{56, "Caligula's Roof", 0,2267.9365,1675.9147,95.0219,0.0,0,		1,2264.3945,1675.8087,1090.5453,0.0,0,		0,0,0},//righkt_up_Caligula's
{57, "Caligula's Roof", 0,2267.9998,1619.4830,95.0219,270.0,0,		1,2264.5317,1619.5618,1090.5453,270.0,0,	0,0,0},//left_up_Caligula's
{58, "TheFourDragons", 0,2019.5035,1007.7916,10.9203,270.0,0,		10,2019.0674,1017.8496,996.9750,90.0,0,		0,0,0},
{59, "Generator Hall", 0,-595.1390,2017.7134,60.8391,336.7087,0,	17,-959.6698,1956.4624,9.1000, 180.0,0,		0,0,0},
{60, "Madd Dogg's Grib down", 0,1298.5475,-798.1450,84.2406, 180.0,0,	5,1298.9351,-797.0099,1084.1078,0.0,0,	0,0,0},
{61, "Madd Dogg's Grib up", 0,1259.3564,-785.4312,92.1302, 90.0,0,	5,1260.8229,-785.3531,1092.0063,270.0,0,	0,0,0},
{62, "Sindacco Abbatoir", 0,966.2491,2160.6189,10.9203, 270.0,0,	1,965.1229,2160.1721,1011.1303,90.0,0,		0,0,0},
//{66, "Skyscraper LS", 0,1570.4503,-1337.4324,16.6844,0.0,0, 		0,1548.6342,-1364.0593,326.4183,180.0,0,	0,0,0},//1559 1318
{63, "Skyscraper SF", 0,-1749.2916,873.1477,25.1859, 180.0,0, 		0,-1753.7181,883.8342,295.6010,0.0,0,		0,0,0},
{64, "PrivatRoom", 3,1207.5498,-40.8148,1000.9531,8.5081,78, 		3,1207.6718,-42.1666,1000.9531,182.1773,MAX_HOUSE+77,	0,0,0},//Nude Strippers
{65, "SaltMine", 0,546.3120,880.2810,-41.1199, 252.7,0, 			0,651.3430,865.7960,-83.4509,88.3,0,		0,0,0}//1559 //2 для шахтёров
};


stock interior_OnGameModeInit()
{
	new time = GetTickCount();
	//==========================================================================
	for(new pic = 0; pic < MAX_INT; pic++)
	{   //для установки пикапов не привязанных к ИД
		PickupID[MAX_PLAYER_PICKUPS+pic] = SetPickupEx(19132, 23, InteriorInfo[pic][iEntranceX],InteriorInfo[pic][iEntranceY],InteriorInfo[pic][iEntranceZ], InteriorInfo[pic][iEntranceVW]);
		//PickupID[pic] = CreateDynamicPickup(1559, 23, InteriorInfo[pic][iEntranceX],InteriorInfo[pic][iEntranceY],InteriorInfo[pic][iEntranceZ], 0,
			//InteriorInfo[pic][iExitInt], -1, 300.0); PickupCounter ++;

		Text3DPickupID[MAX_PLAYER_PICKUPS+pic] = Create3DTextLabelEx(InteriorInfo[pic][iDiscription],
				0x88EE88FF, InteriorInfo[pic][iEntranceX],InteriorInfo[pic][iEntranceY],InteriorInfo[pic][iEntranceZ]+0.75,
				80.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, InteriorInfo[pic][iEntranceVW]);


		PickupID[MAX_PLAYER_PICKUPS+pic] = SetPickupEx(1559, 23, InteriorInfo[pic][iExitX],InteriorInfo[pic][iExitY],InteriorInfo[pic][iExitZ]+0.1, InteriorInfo[pic][iExitVW]);

		Text3DPickupID[MAX_PLAYER_PICKUPS+pic] = Create3DTextLabelEx("Выход {FF0000}[EXIT]",
				0xBFF600FF, InteriorInfo[pic][iExitX],InteriorInfo[pic][iExitY],InteriorInfo[pic][iExitZ]+0.75,
				80.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, InteriorInfo[pic][iExitVW]);
	}
	printf("20/19. [Загрузка пикапов интерьеров]: Было загружено - %d[%d], потрачено - %d (ms)", PickupCounter, Counter3DText, GetTickCount() - time);//new time = GetTickCount();
}

//##############################################################################//
//                                                                              //
//                               ФУНКЦИИ ПРОВЕРКИ                               //
//                                                                              //
//##############################################################################//
//начинаются на Is Check
stock IsAtPolice(playerid)//возвращает 1 если игрок в участке
{
	if(PlayerInfo[playerid][pVirtual] == POLICE_LS_WORLD)	return POLICE_LS_WORLD; //sRegion = "LSPD";
	else if(PlayerInfo[playerid][pVirtual] == POLICE_SF_WORLD) return POLICE_SF_WORLD; //sRegion = "SFPD";
	else if(PlayerInfo[playerid][pVirtual] == POLICE_LV_WORLD) return POLICE_LV_WORLD; //sRegion = "LVPD";
/*
	if(IsPlayerInRangeOfPoint(playerid, 30.0,1535.8275,-1678.0283,13.1680)) { return 1; }// Jail spot LSPD int0
	//else if(IsPlayerInRangeOfPoint(playerid, 6.0, 268.3327,77.8972,1001.0391)) { return 1; }// Jail spot LSPD int6
	else if(IsPlayerInArea(playerid, checkCoords[CP_LSPD])) { return 1; }// Jail spot LSPD int6

	else if(IsPlayerInRangeOfPoint(playerid, 30.0, -1589.9442,716.3722,-5.2422)) { return 2; }// Jail spot SFPD int0
	//else if(IsPlayerInRangeOfPoint(playerid, 6.0, 227.2106,114.6068,999.0156))  return 2;// Jail spot SFPD int10
	else if(IsPlayerInArea(playerid, checkCoords[CP_SFPD])) { return 2; }// Jail spot SFPD int10

	else if(IsPlayerInRangeOfPoint(playerid, 30.0, 2287.1213,2428.4788,10.8203)) { return 3; }// Jail spot LVPD int0
	//else if(IsPlayerInRangeOfPoint(playerid, 6.0, 197.2874,179.4189,1003.0234))  return 3;// Jail spot LVPD int3
	else if(IsPlayerInArea(playerid, checkCoords[CP_LVPD_UPFLOOR])) { return 3; }// Jail spot LVPD int3
	else if(IsPlayerInArea(playerid, checkCoords[CP_LVPD_DOWNFLOOR])) { return 3; }// Jail spot LVPD int3
*/
	return 0;
}
stock IsAtHospital(playerid)//возвращает 1 если игрок в больнице
{
	if(PlayerInfo[playerid][pVirtual] == MEDIC_LS_WORLD1) { return MEDIC_LS_WORLD1; }//Hospital LS near Ammu Enter
	else if(PlayerInfo[playerid][pVirtual] == MEDIC_SF_WORLD1) { return MEDIC_SF_WORLD1; } //Hospital SF Enter
	else if(PlayerInfo[playerid][pVirtual] == MEDIC_LV_WORLD1) { return MEDIC_LV_WORLD1; } //Hospital LV Enter
	return 0;
}

stock interior_OnPlayerPickUp(playerid, pickupid)
{
	/*if(	 PlayerInfo[playerid][pVirtual] == 0 &&
		//PlayerInfo[playerid][pLocal] == FREEROAM &&
		PlayerInfo[playerid][pInt] == 0)
	{
		EnterOfInteriorPickUp(playerid, pickupid);//для автовхода в интерьер с несколькими выходами
	}
	else
	{
		ExitOfInteriorPickUp(playerid, pickupid);
	}*/
	
	EnterOfInteriorPickUp(playerid, pickupid);//для автовхода в интерьер с несколькими выходами
	ExitOfInteriorPickUp(playerid, pickupid);
	/*if(InteriorInfo[i][iEntranceInt] != InteriorInfo[i][iExitInt])
	{
		SetPlayerInteriorEx(playerid, 0);
	}
	else
	{
		SetPlayerInteriorEx(playerid, InteriorInfo[i][iExitInt]);
	}*/
}


//##############################################################################//
//                                                                              //
//                               ВХОД В ИНТЕРЬЕРЫ                               //
//                                                                              //
//##############################################################################//
stock EnterOfInteriorPickUp(playerid, pickupid)
{   //вызывается из interior_OnPlayerPickUp(playerid, pickupid) -> PlayerEnterPickUp -> pickup_OnPlayerPickUpPickup -> OnPlayerPickUpPickup
 	#pragma unused pickupid
	//if(PlayerInfo[playerid][pInt] != 0) return 1;
	//if(PlayerInfo[playerid][pVirtual] != 0) return 1;
	//if(PlayerInfo[playerid][pLocal] != FREEROAM) return 1;
	//if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return 1;//не раскоментировать
//------------------------------------------------------------------------------
//"/enter" - начало
	for(new i=0; i<MAX_INT; i++)
	{
		if(	IsPlayerInRangeOfPoint(playerid, 3.0, InteriorInfo[i][iEntranceX],InteriorInfo[i][iEntranceY],InteriorInfo[i][iEntranceZ])
				//&& 	PlayerInfo[playerid][pLocal] == FREEROAM
				&& PlayerInfo[playerid][pVirtual] == InteriorInfo[i][iEntranceVW])
		{
			if(InteriorInfo[i][iLock] == 1)
			{
				//GTFP(playerid, "%s ~r~Closed", InteriorInfo[0][iDiscription]);
				format(strings, sizeof(strings), "%s ~r~Closed", InteriorInfo[0][iDiscription]);
				GameTextForPlayer(playerid, strings, 5000, 1);
				return 1;
			}
			if(PlayerInfo[playerid][pJob] == MINER && InteriorInfo[i][iExitVW] == 545)
			{
				DisablePlayerCheckpointEx(playerid);
				SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы находитесь на месте добычи. {00CC00}(USE: '{0080FF}"#KEY_FOOT_FIRE"{00CC00}' для добычи).");
				//return 1;
			}

			SetPlayerWeather(playerid, 5);
			SetPlayerTime(playerid, 22, 0);

		    //записываем в координаты спауна при входе
			PlayerInfo[playerid][pPos_x] = InteriorInfo[i][iEntranceX],
			PlayerInfo[playerid][pPos_y] = InteriorInfo[i][iEntranceY],
			PlayerInfo[playerid][pPos_z] = InteriorInfo[i][iEntranceZ];

			new Float:X = InteriorInfo[i][iExitX];
			new Float:Y = InteriorInfo[i][iExitY];
			new Float:Z = InteriorInfo[i][iExitZ];
			new Float:Ang = InteriorInfo[i][iExitA];
			GetXYInFrontOfPoint(2.0, Ang, X,Y);

			if(PlayerInfo[playerid][pVirtual] == 0 && PlayerInfo[playerid][pInt] == 0) { SetLoadTexture(playerid); SetPlayerPosC(playerid, X,Y,Z, Ang); }//с замарозкой
			else SetPlayerPosEx(playerid, X,Y,Z, Ang);

			PlayerInfo[playerid][pLocal] = InteriorInfo[i][iLoc];
			SetPlayerInteriorEx(playerid, InteriorInfo[i][iExitInt]);
			SetPlayerVirtualWorldEx(playerid, InteriorInfo[i][iExitVW]);

		    //GTFP(playerid, "~w~Welcome to the ~n~~y~%s",InteriorInfo[0][iDiscription]);
			format(strings, sizeof(strings), "~w~Welcome to the ~n~~y~%s", InteriorInfo[i][iDiscription]);
			GameTextForPlayer(playerid, strings, 5000, 1);
			//OnePlayAnim(playerid, "PED", "WALK_CIVI", 4.1, 0, 1, 1, 0, 0);
			//SetPVarInt(playerid, "Int", InteriorInfo[i][iExitInt]);
			
			//PlaySoundForPlayerInRange(playerid, SOUND_LIFT_PING, 50.0);
			//new Float:pX, Float:pY, Float:pZ; //new Float:pA, Float:ang;
			//GetPlayerPos(forplayerid, pX, pY, pZ);	//GetPlayerFacingAngle(forplayerid, pA);

			PlaySoundForPlayersInRange(SOUND_LIFT_PING, 50.0,InteriorInfo[i][iExitX],InteriorInfo[i][iExitY],InteriorInfo[i][iExitZ]);//проигрывает всем в радиусе 50 м
			break;
		}
	}
//"/enter" - конец
//------------------------------------------------------------------------------

	//для дальнобойщиков STEP0
	/*if(PlayerInfo[playerid][pJob] == TRUCKER && CP[playerid] == CP_TRUCKER)
	{   //если дальнобойщик подобрал пикап //вошёл в интерьер
		DisablePlayerCheckpointEx(playerid);
	   	SendClientMessage(playerid, COLOR_GREY, "   Вы ушли с маршрута ! Поторопитесь !");
	}*/
	if(CHECKING[PlayerPickUpPickup])
	{
		//ИНФОРМИРОВАНИЕ
		////new strings[MAX_STRING];
		format(strings, sizeof(strings), "EnterOfInteriorPickUp(playerid:%d) interior:%d virtual:%d",
			playerid, PlayerInfo[playerid][pInt], PlayerInfo[playerid][pVirtual]);
		//SendClientMessageToAll(COLOR_YELLOW, strings);
		SendClientMessage(playerid, COLOR_YELLOW, strings);
	}
	return 1;
}//END EnterOfInteriorPickUp
//##############################################################################//
//                                                                              //
//                             ВЫХОД ИЗ ИНТЕРЬЕРОВ                              //
//                                                                              //
//##############################################################################//
stock ExitOfInteriorPickUp(playerid, pickupid)
{   //вызывается OnPlayerPickUpPickup
 	#pragma unused pickupid
	if(CHECKING[PlayerPickUpPickup])
	{
		//ИНФОРМИРОВАНИЕ
		////new strings[MAX_STRING];
		format(strings, sizeof(strings), "ExitOfInteriorPickUp(playerid:%d) Interior:%d Virtual:%d", playerid, PlayerInfo[playerid][pInt], PlayerInfo[playerid][pVirtual]);
		//SendClientMessageToAll(COLOR_YELLOW, strings);
		SendClientMessage(playerid, COLOR_YELLOW, strings);
	}
	
//-------------------------------------------------------------------------
//"/exit" - начало
	for(new i=0; i<MAX_INT; i++)
	{
		if( IsPlayerInRangeOfPoint(playerid, 3.0, InteriorInfo[i][iExitX],InteriorInfo[i][iExitY],InteriorInfo[i][iExitZ])
			&& PlayerInfo[playerid][pVirtual] == InteriorInfo[i][iExitVW])
		{//если локация совпадает с виртуальным миром в котором находится игрок
#if defined vw_races//#endif
			if(gInDerby8ball[playerid])//для дерби 8ball
			{
        		EndDerbiLS(playerid);
 				return 1;
			}
 			if(gInDerbyBloodBowl[playerid])//для дерби BloodBowl STEP7
			{
				SetVehicleToRespawnEx(playerid, nCarID[playerid]);
				DisablePlayerRaceCheckpoint(playerid);

				TotalDerby --;
				if(TotalDerby <= 0)
				{
					//KillTimer(updatederbytimer); updatederbytimer = -1;
					gDerbyStarted = 0;//опускаем флаг - гонка закончилась
					TotalDerby = 0;//обнулить общее кол-во гонщиков 0
					//SendClientMessageToAll(COLOR_BRIGHTLYGREEN, "Дерби BloodBowl окончен. Последний покинул стадион.");
					SendAllAdminMessage(COLOR_BRIGHTLYGREEN, "Дерби BloodBowl окончен. Последний покинул стадион.", 1);
				}
				DerbyScore[playerid] = 0;
				PlayerInfo[playerid][pCarTime] = 0;
				gInDerbyBloodBowl[playerid] = 0;//опускаем флаг - игрок не в гонке

				gTextDrawHideCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
				ResetPlayerWeaponsEx(playerid);

			}
			if(gInDerbyKickStart[playerid])
			{
				for(new j=0, idx; j<MaxPlayers; j++)	{
					idx = PLIDs[j];
					if( !IsPlayerConnectedEx(idx) || !gPlayerSpawned[idx] ) continue;
					if( !gInDerbyKickStart[idx] ) continue;
				 	//SendClientMessageToAll(COLOR_BRIGHTLYGREEN, strings);
			    	format(strings, sizeof(strings), "KickStart: {FFFFFF}%s[%d]{00FF00} покинул стадион в Лас-Вентурасе", PlayerName(playerid), playerid);
				 	SendClientMessage(i, COLOR_BRIGHTLYGREEN, strings);
				}
				gTextDrawHideCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);

			    if(PickupScore[playerid] > 0) GivePlayerMoneyH(fkickstart, playerid, PickupScore[playerid]*50);
				TimeSecRide[playerid] = 0;

				gInDerbyKickStart[playerid] = 0;
				PickupScore[playerid] = 0;

				if(gKickStarted == 1 && KickStartProgress < MAX_SCORE)
				{
				    new found = -1;
					for(new j=0, idx; j<MaxPlayers; j++)	{
						idx = PLIDs[j];
						if(!IsPlayerConnectedEx(idx)) continue;
						if(!gInDerbyKickStart[idx]) continue;
						found = idx;
						break;
					}
					if(found == -1)
					{
						gKickStarted = 0;
						KickStartProgress = 0;
						//SendClientMessageToAll(COLOR_ORANGE, "Заезд {FF0000}Kick Start{FF6600} закончился. Последний покинул стадион.");
						SendAllAdminMessage(COLOR_ORANGE, "Заезд {FF0000}KickStart{FF6600} закончился. Последний покинул стадион.", 1);
					}
				}
			}
#endif
//больница
			if(IsAtHospital(playerid) >= MEDIC_LS_WORLD1 && IsAtHospital(playerid) <= MEDIC_LV_WORLD1)
			{
				if(	gHospitalLockDoor == 1 && PlayerInfo[playerid][pMember] != DoH &&
					gMedicBill[playerid] == 0)
				{
					GameTextForPlayerEx(playerid, "Hospital ~r~Closed", 5000, 1);//по англ обязательно
					return 1;
				}
				if(	gMedicBill[playerid] == 1 && PlayerInfo[playerid][pMember] != DoH &&
					LastHealth[playerid] < floatadd(PlayerInfo[playerid][pSHealth], 50.0))
				{
					//format(strings, sizeof(strings), "Hospital: Ждите окончания лечения. Удачного выздоровления!", ЭЭ);
					SendClientMessage(playerid, COLOR_MAUVE, "Hospital: Ждите окончания лечения. Удачного выздоровления!");
					return 1;
				}
			}
			//------------------------------------------------------------------
			new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
			SetPlayerTime(playerid, lH, lM);//возвращаем время в мире
			SetWeather(weathers[wethindex]);//возвращаем погоду
			
			SetPlayerVirtualWorldEx(playerid, InteriorInfo[i][iEntranceVW]);
			SetPlayerInteriorEx(playerid, InteriorInfo[i][iEntranceInt]);

			//if(InteriorInfo[i][iLoc] >= 2 && InteriorInfo[i][iLoc] <= 13) SetPlayerInteriorEx(playerid, InteriorInfo[i][iExitInt]);
			//else if(InteriorInfo[i][iEntranceVW] != InteriorInfo[i][iExitVW]) SetPlayerInteriorEx(playerid, 0);
			//else SetPlayerInteriorEx(playerid, InteriorInfo[i][iExitInt]);

			new Float:X = InteriorInfo[i][iEntranceX];
			new Float:Y = InteriorInfo[i][iEntranceY];
			new Float:Z = InteriorInfo[i][iEntranceZ];
			new Float:Ang = InteriorInfo[i][iEntranceA];
			GetXYInFrontOfPoint(2.0, Ang, X,Y);
			SetPlayerPosEx(playerid, X,Y,Z, Ang);

			PlayerInfo[playerid][pLocal] = FREEROAM;
			//SetPVarInt(playerid, "Int", FREEROAM);
			
			//PlaySoundForPlayerInRange(playerid, SOUND_LOCK_CAR_DOORS, 30.0);
			PlaySoundForPlayersInRange(SOUND_LIFT_PING, 50.0,InteriorInfo[i][iEntranceX],InteriorInfo[i][iEntranceY],InteriorInfo[i][iEntranceZ]);//проигрывает всем в радиусе 50 м
			break;
		}
	}
//"/exit" - конец
	return 1;
}//END ExitOfInteriorPickUp


stock interior_Example(playerid)
{
	new biglistitems[146*(25+12)+30]; new tmp[25+12];
	//strcat(biglistitems, "0. Установить интерьер ID:0\n");
	strcat(biglistitems, "№.\tОписание\t[ID]\n");
	new index = 0;
	for(new i=0; i<146; i++)
	{
		index ++;
  		format(tmp, sizeof(tmp), "%d.\t%s\t[%d]\n", index, InteriorInfoExample[i][ieDiscription], InteriorInfoExample[i][ieInt]);
  		strcat(biglistitems, tmp);
	}
	ShowPlayerDialogEx(playerid, SETINT_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, "Выбирите интерьер", biglistitems, "OK", "Cancel");
}


stock interior_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if(dialogid != SETINT_DIALOG) return 1;
	if(!response)
	{
		SetPlayerInteriorEx(playerid, 0);
		PlaySoundForPlayer(playerid, 5202);
		return 1;
	}
	new ID = listitem-1;
	SetPlayerInteriorEx(playerid, InteriorInfoExample[ID][ieInt]);
	SetPlayerPosEx(playerid, InteriorInfoExample[ID][ieExitX],InteriorInfoExample[ID][ieExitY],InteriorInfoExample[ID][ieExitZ], InteriorInfoExample[ID][ieExitA]);
	//SetPlayerFacingAngle(giveplayerid,InteriorInfoExample[ID][ieExitA]);
	format(strings, sizeof(strings), "AdmCmd: %s set Interior: %d", PlayerName(playerid), InteriorInfoExample[ID][ieInt]);
	//Log(ADMINLOG, msgitem);
	SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, strings);
	return 1;
}

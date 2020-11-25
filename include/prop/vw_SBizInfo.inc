
/*
Пенсионный фонд за 8 часов игры для 1-го уровня составит $-2120
Пенсионный фонд за 20 часов игры для 2-го уровня составит $-980
Пенсионный фонд за 36 часов игры для 3-го уровня составит $6300
Пенсионный фонд за 56 часов игры для 4-го уровня составит $22600
Пенсионный фонд за 80 часов игры для 5-го уровня составит $50800
Пенсионный фонд за 108 часов игры для 6-го уровня составит $93780
Пенсионный фонд за 140 часов игры для 7-го уровня составит $154420
Пенсионный фонд за 176 часов игры для 8-го уровня составит $235600
Пенсионный фонд за 216 часов игры для 9-го уровня составит $340200
Пенсионный фонд за 260 часов игры для 10-го уровня составит $471100
Пенсионный фонд за 308 часов игры для 11-го уровня составит $631180
Пенсионный фонд за 360 часов игры для 12-го уровня составит $823320
Пенсионный фонд за 416 часов игры для 13-го уровня составит $1050400
Пенсионный фонд за 476 часов игры для 14-го уровня составит $1315300
Пенсионный фонд за 540 часов игры для 15-го уровня составит $1620900
Пенсионный фонд за 608 часов игры для 16-го уровня составит $1970080
Пенсионный фонд за 680 часов игры для 17-го уровня составит $2365720
Пенсионный фонд за 756 часов игры для 18-го уровня составит $2810700
Пенсионный фонд за 836 часов игры для 19-го уровня составит $3307900
Пенсионный фонд за 920 часов игры для 20-го уровня составит $3860200
*/


enum sbInfo
{
	//sbID,
	sbOwned,
	sbOwner[MAX_PLAYER_NAME],//64
	sbExtortion,//[20],//MAX_PLAYER_NAME
	sbDiscription[20],
	sbBranch,
	
	Float:sbEntranceX,
	Float:sbEntranceY,
	Float:sbEntranceZ,

	sbBuyPrice,
	sbLevel,

	sbLock,
	sbEntranceCost,//0 - цена топлива например

	sbProducts,
	sbBuyProd,
	sbSellProd,
	sbTill,//количество денег на счету бизнеса
	sbDate,
	sbInkas,

	sbWorker,//кол-во работников
	sbImport,//сколько денег потратил на покупку продуктов
	sbExport,//сколько денег заработал на экспорте
	sbSalary,//зарплата
	sbExpenses//аренда//стоимость хранения товаров 10-50$ в час4
};//0,The State,No-One,0,100,100,0,15,500,271

	/*if($sbizz['TypeProducts'] == Amusements) { $prodname = "Металла";}
	else if($sbizz['TypeProducts'] == Trade) { $prodname = "Текстиля";}
	else if($sbizz['TypeProducts'] == Restaurant) { $prodname = "Продуктов";}
	else if($sbizz['TypeProducts'] == Service) { $prodname = "Дерева";}
	else if($sbizz['TypeProducts'] == Industry) { $prodname = "Топлива";}
	else { $prod = $bizz['Products']; $prodname = "ХерЗнаетЧего"; }*/

//Сырьё
//Металл - основа для производства товаров индустрии развлечений
//#define Amusements 	1//Металл:220/день;
//6*100/26 = 23%
//#define MAX_SBIZ 59-33

//Текстиль - основа для производства товаров розничной торговли
//#define Trade 		2//текстиль:220/день;
//6*100/26 = 23%

//Продовольствие - основа для производства товаров ресторанного бизнеса
//#define Restaurant 	3//продовольствие:220/день;
//5*100/26 = 19%

//Древесины - основа для производства товаров сферы услуг
//#define Service 	4//древесина:220/день
//6*100/26 = 23%

//Нефть - основа для производства товара промышленной сферы
//#define Industry 	5//топливо:220/день
//3*100/26 = 12%

new SBizInfo[MAX_SBIZ][sbInfo] = {
//0
/*	sbProducts,
	sbBuyProd,
	sbSellProd,
	sbTill,//количество денег на счету бизнеса
	sbDate,
	sbInkas,*/
{0, "The State", 0,	"Car Renting",		Amusements,	562.4050,-1289.9952,17.2481,	147250,1,	0,100, 	100,10,15,1000,1,10000,	0,0,0,1,250},//0
{0, "The State", 0,	"Wang Cars",		Amusements,	-1968.5598,296.2695,35.1719,	208412,1,	0,100, 	100,10,15,1000,1,10000,	0,0,0,1,550},
{0, "The State", 0,	"Phone Company",	Trade,		-308.1978,1538.6097,75.5625,	99080,1,	0,10, 	100,10,15,1000,1,10000,	0,0,0,1,420},
{0, "The State", 0,	"Gas Company",		Industry,	-1035.3127,-625.0355,31.5799,	135034,1,	0,1, 	100,10,15,1000,1,10000,	0,0,0,1,270},//3
{0, "The State", 0,	"Coal Company",		Industry,	-1826.3422,41.6017,15.1228,		34979,1,	0,17, 	100,10,15,1000,1,10000,	0,0,0,1,550},//4 //Electro Company
{0, "The State", 0,	"Car Delivery",		Trade,		1939.29,2068.4526,10.8203,		6874,1,		0,100, 	100,10,15,1000,1,10000,	0,0,0,1,900},
{0, "The State", 0,	"House Upgrade",	Trade,		2350.0,-1411.8000,23.9923,		21500,1,	0,100, 	100,10,15,1000,1,10000,	0,0,0,1,110},
{0, "The State", 0,	"CNN Studio",		Trade,		844.656,-1045.5555,25.4300,		171120,1,	0,3, 	100,10,15,1000,1,10000,	0,0,0,1,390},//7
{0, "The State", 0,	"Tow Car Service",	Amusements,	-1799.7954,1200.3747,25.1194,	43775,1,	0,50, 	100,10,15,1000,1,10000,	0,0,0,1,1000},//8
{0, "The State", 0,	"General Store",	Restaurant,	2246.4331,52.4620,26.6671,		475614,1,	0,100, 	100,10,15,1000,1,10000,	0,0,0,1,130},
{0, "The State", 0,	"Paintball Arena",	Trade,		2495.0305,2773.1777,10.8157,	2800,1,		0,100, 	100,10,15,1000,1,10000,	0,0,0,1,100},
{0, "The State", 0,	"Kart Track",		Amusements,	2281.9091,-2364.2790,13.5466,	12550,1,	0,100, 	100,10,15,1000,1,10000,	0,0,0,1,20},
{0, "The State", 0,	"Sprunk Buster",	Restaurant,	172.3173,-152.6194,1.5746,		6600,1,		0,10, 	100,10,15,1000,1,10000,	0,0,0,1,130},
{0, "The State", 0,	"Vehicle Respray",	Service,	1671.5216,1814.3865,10.8203,	324800,1,	0,100, 	100,10,15,1000,1,10000,	0,0,0,1,320},//13
{0, "The State", 0,	"Trans Fender",		Service,	-1942.8154,237.3040,34.1289,	32250,1,	0,100, 	100,10,15,1000,1,10000,	0,0,0,1,350},
{0, "The State", 0,	"LocoLowCompany",	Service,	2651.3069,-2039.4761,13.5500,	3000,1,		0,100, 	100,10,15,1000,1,10000,	0,0,0,1,100},
{0, "The State", 0,	"WheelArchAngels",	Service,	-2714.6714,223.7548,4.3281,		40890,1,	0,100, 	100,10,15,1000,1,10000,	0,0,0,1,310},//16
{0, "The State", 0,	"Oil Company",		Industry,	292.0524,1402.3292,10.2516,		88394,1,	0,1, 	100,10,15,1000,1,10000,	0,0,0,1,180},//17

//18
{0, "The State", 0,	"Gas Station 1",	Industry,	999.4829,-918.4880,42.3281,		213544,1,	0,1, 100,10,15,1000,1,10000,	0,0,0,1,290},//18
{0, "The State", 0,	"Gas Station 2",	Industry,	1929.5913,-1778.7913,13.5469,	37897,1,	0,1, 100,10,15,1000,1,10000,	0,0,0,1,190},
{0, "The State", 0,	"Gas Station 3",	Industry,	-79.9012,-1171.4628,2.1523,		326687,1,	0,1, 100,10,15,1000,1,10000,	0,0,0,1,360},
{0, "The State", 0,	"Gas Station 4",	Industry,	-1622.8103,-2694.8433,48.7427,	22569,1,	0,1, 100,10,15,1000,1,10000,	0,0,0,1,30},
{0, "The State", 0,	"Gas Station 5",	Industry,	-2233.4854,-2555.9817,31.9219,	18917,1,	0,1, 100,10,15,1000,1,10000,	0,0,0,1,30},
{0, "The State", 0,	"Gas Station 6",	Industry,	-2034.2131,147.5298,28.8359,	512082,1,	0,1, 100,10,15,1000,1,10000,	0,0,0,1,530},//23
{0, "The State", 0,	"Gas Station 7",	Industry,	-2419.8804,967.8728,45.2969,	35315,1,	0,1, 100,10,15,1000,1,10000,	0,0,0,1,140},
{0, "The State", 0,	"Gas Station 8",	Industry,	-1677.2815,430.2717,7.1797,		88804,1,	0,1, 100,10,15,1000,1,10000,	0,0,0,1,310},
{0, "The State", 0,	"Gas Station 9",	Industry,	-1321.5563,2697.5425,50.2663,	42856,1,	0,1, 100,10,15,1000,1,10000,	0,0,0,1,30},
{0, "The State", 0,	"Gas Station10",	Industry,	-1467.5270,1872.7051,32.6328,	129014,1,	0,1, 100,10,15,1000,1,10000,	0,0,0,1,110},
{0, "The State", 0,	"Gas Station11",	Industry,	59.2713,1221.9875,18.8659,		223232,1,	0,1, 100,10,15,1000,1,10000,	0,0,0,1,260},
{0, "The State", 0,	"Gas Station12",	Industry,	639.6429,1684.5088,7.1875,		35580,1,	0,1, 100,10,15,1000,1,10000,	0,0,0,1,150},
{0, "The State", 0,	"Gas Station13",	Industry,	2635.2903,1129.1829,11.1797,	30872,1,	0,1, 100,10,15,1000,1,10000,	0,0,0,1,20},
{0, "The State", 0,	"Gas Station14",	Industry,	2188.3865,2467.6897,11.2422,	33646,1,	0,1, 100,10,15,1000,1,10000,	0,0,0,1,110},
{0, "The State", 0,	"Gas Station15",	Industry,	2152.7869,2734.4658,11.1763,	23263,1,	0,1, 100,10,15,1000,1,10000,	0,0,0,1,20},
{0, "The State", 0,	"Gas Station16",	Industry,	2119.3271,897.5119,11.1797,		55372,1,	0,1, 100,10,15,1000,1,10000,	0,0,0,1,100},
{0, "The State", 0,	"Gas Station17",	Industry,	1597.7955,2219.9819,11.0692,	110167,1,	0,1, 100,10,15,1000,1,10000,	0,0,0,1,80},
{0, "The State", 0,	"Gas Station18",	Industry,	1373.9202,468.7967,20.2013,		29835,1,	0,1, 100,10,15,1000,1,10000,	0,0,0,1,50},
{0, "The State", 0,	"Gas Station19",	Industry,	660.5143,-575.3116,16.3359,		33089,1,	0,1, 100,10,15,1000,1,10000,	0,0,0,1,100},//36

{0, "The State", 0,	"Gas Station20",	Industry,	379.3857,2478.8232,16.4844,		13282,1,	0,1, 500,15,30,1000,1,10000,	0,0,0,1,100},//37
{0, "The State", 0,	"Gas Station21",	Industry,	1548.5193,1225.8209,10.8125,	3718,1,		0,1, 500,15,30,1000,1,10000,	0,0,0,1,10},//38
{0, "The State", 0,	"Gas Station22",	Industry,	-1409.3679,-549.0587,14.1484,	38040,1,	0,1, 500,15,30,1000,1,10000,	0,0,0,1,50},//39

//40
{0, "The State", 0,	"Parking 1", 	0,	2115.7712,2413.0168,10.8203,		823320,1,	0,10, 100,10,15,1000,1,10000,	0,0,0,1,1000},//40 //4549165
{0, "The State", 0,	"Parking 2", 	0,	2115.5464,2413.2832,15.1172,		631180,1,	0,10, 100,10,15,1000,1,10000,	0,0,0,1,900},       //102895
{0, "The State", 0,	"Parking 3", 	0,	2115.6311,2413.0044,19.4219,		471100,1,	0,10, 100,10,15,1000,1,10000,	0,0,0,1,800},
{0, "The State", 0,	"Parking 4", 	0,	2115.5940,2413.0134,23.7188,		340200,1,	0,10, 100,10,15,1000,1,10000,	0,0,0,1,700},
{0, "The State", 0,	"Parking 5", 	0,	2115.1726,2413.2993,28.0234,		235600,1,	0,10, 100,10,15,1000,1,10000,	0,0,0,1,600},
{0, "The State", 0,	"Parking 6", 	0,	2115.3237,2413.0818,32.3203,		154420,1,	0,10, 100,10,15,1000,1,10000,	0,0,0,1,500},
{0, "The State", 0,	"Parking 7", 	0,	2115.4504,2412.9502,36.6172,		93780,1,	0,10, 100,10,15,1000,1,10000,	0,0,0,1,400},
{0, "The State", 0,	"Parking 8", 	0,	2115.1326,2412.9907,40.9219,		50800,1,	0,10, 100,10,15,1000,1,10000,	0,0,0,1,300},
{0, "The State", 0,	"Parking 9", 	0,	2115.2695,2413.1448,45.2188,		22600,1,	0,10, 100,10,15,1000,1,10000,	0,0,0,1,200},
{0, "The State", 0,	"Parking10", 	0,	2115.3196,2413.3049,49.5234,		6300,1,		0,10, 100,10,15,1000,1,10000,	0,0,0,1,100},
{0, "The State", 0,	"Parking11", 	0,	2114.9954,2410.1111,60.8169,		6300,1,		0,10, 100,10,15,1000,1,10000,	0,0,0,1,500},//50

//водохранилище
{0, "The State", 0,	"Sherman Dam",	Restaurant,	-597.0029,2021.3996,60.3818,		14025,1,		0,10, 100,10,15,1000,1,10000,	0,0,0,1,230},//51
//для фермеров
{0, "The State", 0,	"Farm",			Trade,		-1210.1460,-1043.3667,128.3897,		566465,1,		0,10, 100,10,15,1000,1,10000,	0,0,0,1,400},//52
//для рыбаловов
{0, "The State", 0,	"Fish Vault",	Restaurant,	359.9126,-2032.1475,7.8359,			2200,1,			0,10, 100,10,15,1000,1,10000,	0,0,0,1,50},//53
//для грибников
{0, "The State", 0,	"MushroomVault",Restaurant,-382.5433,-1439.0052,25.8975,		18393,1,		0,10, 100,10,15,1000,1,10000,	0,0,0,1,10},//54
//для шахтёров
{0, "The State", 0,	"Salt Mine",	Restaurant,	585.5980,874.7810,-42.4970,			741345,1,		0,10, 100,10,15,1000,1,10000,	0,0,0,1,30},//55
//для дровосеков
{0, "The State", 0,	"Sawmill",		Service,	-1969.2313,-2433.8501,31.2501,		12705,1,		0,10, 100,10,15,1000,1,10000,	0,0,0,1,10},//56
//свалка для автомехаников
{0, "The State", 0,	"Scramble",		Amusements,	-1864.6102,-1559.2463,22.2109,		516160,1,		0,10, 100,10,15,1000,1,10000,	0,0,0,1,1300},//57 //Quarry //1300
//база механов
{0, "The State", 0,	"AutoRepair",	Amusements,	-110.1912,-1254.4943,3.3737,		18524,1,		0,10, 100,10,15,1000,1,10000,	0,0,0,1,1320}//58
//склады
//{0, "The State", 0,	"Store House",	Service,	-18.9624,-270.4885,5.4297,			6300,3,		0,10, 100,10,15,1000,1,10000}//59 //-86.2483,-299.4684,2.7646
};
/*
//Сырьё
//Металл - основа для производства товаров индустрии развлечений
#define Amusements 	1//Металл:220/день;
//Текстиль - основа для производства товаров розничной торговли
#define Trade 		2//текстиль:220/день;
//Продовольствие - основа для производства товаров ресторанного бизнеса
#define Restaurant 	3//продовольствие:220/день;
//Древесины - основа для производства товаров сферы услуг
#define Service 	4//древесина:220/день
//Нефть - основа для производства товара промышленной сферы
*/


stock SBizInfo_Load()//вызывается из функции GameModeInit
{ 
	new time = GetTickCount();
	if( !fexist("Property/sbiz.info") )
	{
		SBizInfo_Save();//если файла нет, то создать
		return 1;
	}
	new idx;
	new File: pFile = fopen("Property/sbiz.info", io_read);//io_readwrite
	if(!pFile) { return 1; }

	new arrCoords[23][MAX_PLAYER_NAME];
	new strFromFile[256];//180*34
	for(idx=0; idx<MAX_SBIZ; idx++)
	{
		fread(pFile, strFromFile);
		split(strFromFile, arrCoords, ',');

		SBizInfo[idx][sbOwned] = strval(arrCoords[0]);
		strmid(SBizInfo[idx][sbOwner], arrCoords[1], 0, strlen(arrCoords[1]), MAX_PLAYER_NAME);
		SBizInfo[idx][sbExtortion] = strval(arrCoords[2]);
		SBizInfo[idx][sbBranch] =  strval(arrCoords[3]);
		strmid(SBizInfo[idx][sbDiscription], arrCoords[4], 0, strlen(arrCoords[4]), 20);
		
		SBizInfo[idx][sbEntranceX] = floatstr(arrCoords[5]);
		SBizInfo[idx][sbEntranceY] = floatstr(arrCoords[6]);
		SBizInfo[idx][sbEntranceZ] = floatstr(arrCoords[7]);
		
		SBizInfo[idx][sbBuyPrice] = strval(arrCoords[8]);
		SBizInfo[idx][sbLevel] = strval(arrCoords[9]);
		
		SBizInfo[idx][sbLock] = strval(arrCoords[10]);
		SBizInfo[idx][sbEntranceCost] = strval(arrCoords[11]);//стоимость 1 литра бензина из sbizz.cfg = 1$
		
		SBizInfo[idx][sbProducts] = strval(arrCoords[12]);
		SBizInfo[idx][sbBuyProd] = strval(arrCoords[13]);
		SBizInfo[idx][sbSellProd] = strval(arrCoords[14]);
		SBizInfo[idx][sbTill] = strval(arrCoords[15]);
		SBizInfo[idx][sbDate] = strval(arrCoords[16]);
		SBizInfo[idx][sbInkas] = strval(arrCoords[17]);
		
		SBizInfo[idx][sbWorker] = strval(arrCoords[18]);
		SBizInfo[idx][sbImport] = strval(arrCoords[19]);
		SBizInfo[idx][sbExport] = strval(arrCoords[20]);
		SBizInfo[idx][sbSalary] = strval(arrCoords[21]);
		SBizInfo[idx][sbExpenses] = strval(arrCoords[22]);
		//printf("SBizInfo:%d Owner:%s Message:%s Entfee:%d Till:%d Products:%d/%d Interior:%d.\n",
		//		idx,SBizInfo[idx][sbOwner],SBizInfo[idx][sbDiscription],SBizInfo[idx][sbEntranceCost],
		//		SBizInfo[idx][sbTill],SBizInfo[idx][sbProducts],SBizInfo[idx][sbMaxProducts],SBizInfo[idx][sbInterior]);
	}
	fclose(pFile);
//ИНФОРМИРОВАНИЕ
	printf("5/19. [Загрузка компаний]: Было загружено - %d, потрачено - %d (ms)", MAX_SBIZ, (GetTickCount()-time));
	return 1;
}
stock SBizInfo_Save()
{   //для сохранения параметров домов, бизов, машин
	new time = GetTickCount();
	new File: pFile = fopen("Property/sbiz.info", io_write);
	new idx;
	if( !fexist("Property/sbiz.info") ) pFile = fopen("Property/sbiz.info", io_write);
	else pFile = fopen("Property/sbiz.info", io_append);
	if(!pFile) { return 1; }

	while(idx < sizeof(SBizInfo))
	{
		new coordsstring[256];
		format(coordsstring, sizeof(coordsstring),
"%d,%s,%d,%d,%s,	%.4f,%.4f,%.4f,	%d,%d,	%d,%d,	%d,%d,%d,%d,%d,%d,	%d,%d,%d,%d,%d\n",
SBizInfo[idx][sbOwned],
SBizInfo[idx][sbOwner],
SBizInfo[idx][sbExtortion],
SBizInfo[idx][sbBranch],
SBizInfo[idx][sbDiscription],

SBizInfo[idx][sbEntranceX],
SBizInfo[idx][sbEntranceY],
SBizInfo[idx][sbEntranceZ],

SBizInfo[idx][sbBuyPrice],
SBizInfo[idx][sbLevel],

SBizInfo[idx][sbLock],
SBizInfo[idx][sbEntranceCost],

SBizInfo[idx][sbProducts],
SBizInfo[idx][sbBuyProd],
SBizInfo[idx][sbSellProd],
SBizInfo[idx][sbTill],
SBizInfo[idx][sbDate],
SBizInfo[idx][sbInkas],

SBizInfo[idx][sbWorker],
SBizInfo[idx][sbImport],
SBizInfo[idx][sbExport],
SBizInfo[idx][sbSalary],
SBizInfo[idx][sbExpenses]);
		//fwrite(hFile, coordsstring);
	    for(new c=0; c<strlen(coordsstring); c++)
		{
	        fputchar(pFile, coordsstring[c], false);
	    }
		idx ++;
	}
	fclose(pFile);//закрываем файл по указателю file2
//ИНФОРМИРОВАНИЕ
	new strtmp[74+3+6];
	format(strtmp, sizeof(strtmp), "5/19. [Сохранение биз-компаний]: Было сохранено - %d, потрачено - %d (ms)", MAX_SBIZ, (GetTickCount()-time));
	SendAllAdminMessage(COLOR_RESTARTING, strtmp, 1);
	print(strtmp);
	return 1;
}


new CarModel[MAX_PLAYERS];
new CarColor1[MAX_PLAYERS];
new CarColor2[MAX_PLAYERS];

new Text3D: LabelOnHead[MAX_PLAYERS];// = {-1,...};



//для рыбаловов
new FishCount[MAX_PLAYERS];//таймер

//для инкассаторов
new PaydeskAccepted[MAX_PLAYERS];//хранит ID клиента по индексу инкассатора
new PaydeskAmount[MAX_PLAYERS];//хранит сумму перевозки

//для наркодилеров
new DrugPrice[MAX_PLAYERS];
new DrugGram[MAX_PLAYERS];

//для оружейников
new OfferWeapon[MAX_PLAYERS];
new OfferAmmo[MAX_PLAYERS];
new GunPrice[MAX_PLAYERS];
new GunMat[MAX_PLAYERS];//сколько материалов уйдёт на создания этой пушки
new MatsHolding[MAX_PLAYERS];//кол-во пакетов для оружейника //перевести на PVar

//для антифлуда //для сервиса
new iOfferTime[MAX_PLAYERS];//для запрета нескольких вызовов подряд //хранит время закрытие диалога


//new pricepackage = 7;//цена пакета
new amountmaterials = 30;//кол-во матеров в одном пакете
//цена грамма - pricepackage/amountmaterials = 2


//для грузчиков
new JobAmmount[MAX_PLAYERS];//кол-во перетащеных мешков//кол-во добытой соли
//new myobject = CreateObjectEx(1271,0,0,-1000,0,0,0,100);
//AttachObjectToVehicleEx(myobject, GetPlayerVehicleID(playerid), 0.000000,0.674999,0.300000,0.000000,0.000000,0.000000);

//для скупщиков
new AutoBuyerCounter = 0;

//для фермера
new FermaStatus = 0;

//для автомехаников
new MechanicsCounter = 0;
new playeridMechanicCall = MAX_PLAYERS-1;//ид игрока котторый вызвал механиков



//для таксистов
new CostRoute[MAX_PLAYERS];//стоимость маршрута
new TransportValue[MAX_PLAYERS];//цена за проезд на такси/автобусе
new TransportDriver[MAX_PLAYERS];//id таксиста/водилы автобуса
new TransportEarning[MAX_PLAYERS];//полная выручка только для автобуса/такси
new playeridTaxiAccepted[MAX_PLAYERS];//= ID игрока вызвавшего такси по индексу ID таксиста
new TaxiDriversCounter = 0;//счётчик таксистов на дежурстве
new playeridTaxiCall = MAX_PLAYERS-1;//ID игрока вызвавшего такси
new TaxiDriver[3] = {MAX_PLAYERS-1, ...};
new CarPrice[MAX_PLAYERS];
new gTransportTime[MAX_PLAYERS];//интервал увеличения стоимости проезда//отметка пробега на момент посадки

//для дровосеков
new bool:WoodsmanLoading[MAX_PLAYERS];//признак что у игрока бревно на руках
new FireCounter = 0;//кол-во пожарников на сервере

//для ремонтников
new BeepCounter[MAX_PLAYERS];//перевести на PVar



//для устройства на работу
new GettingJob[MAX_PLAYERS];

//для детективов
new gUsedFindCount[MAX_PLAYERS];



//для школьного инструктора
new LicensePrice[MAX_PLAYERS];
new PlayerQueue[MAX_QUEUE_LINES] = {MAX_PLAYERS-1, ...};//Для школы вождения
//------------------------------------------------------------------------------


stock jobs_OnPlayerConnect(playerid)
{
	LabelPlayerCounter[playerid] = 0;//для 3DText

	iOfferTime[playerid] = 0;//для сервисных вызовов

	GettingJob[playerid] = 0; gJobDuty[playerid] = 0; gOnDuty[playerid] = 0;//для устройства на работу
	gUsedFindCount[playerid] = 0;

	LicensePrice[playerid] = 0;

	gMedicBill[playerid] = 0;//для медиков

//для грузчиков //для шахтёров
	JobAmmount[playerid] = 0;
	//PlayerInfo[playerid][pJob] = 0;//временно

//для автомехаников
	gTrailerAttached[playerid] = 0;
	CarModel[playerid] = 0; CarColor1[playerid] = -1; CarColor2[playerid] = -1; //Offer[playerid] = MAX_PLAYERS-1;

	CarPrice[playerid] = 0;//для автодилеров

	MatsHolding[playerid] = 0; GunPrice[playerid] = 0; //Offer[playerid] = MAX_PLAYERS-1;
	OfferWeapon[playerid] = 0; OfferAmmo[playerid] = 0; GunMat[playerid] = 0;//для оружейников


	FishCount[playerid] = 0;//для рыбаловов

	PaydeskAccepted[playerid] = MAX_PLAYERS-1; PaydeskAmount[playerid] = 0;//Offer[playerid] = MAX_PLAYERS-1; //для инкассаторов
	//Offer[playerid] = MAX_PLAYERS-1;

	PlayerStoned[playerid] = 0; DrugPrice[playerid] = 0; DrugGram[playerid] = 0;//Offer[playerid] = MAX_PLAYERS-1; //для наркодилеров

	BeepCounter[playerid] = 0;//для ремонтника дорог
	
	
	
}


stock jobs_OnPlayerDisconnect(playerid)
{
	#pragma unused playerid
	
}
/*
#define MINER 		1
#define LAWYER 		2
#define ROADWORKER  3
#define DRUGDEALER  4
#define CARJACKER   5
#define AUTOBUYER   6
#define CARMECHANIC 7
#define FARMER 		8
#define ARMSDEALER	9
#define CARDEALER	10
#define INKASSATOR  11
#define BOOKMAKER 	12
#define TAXIDRIVER 	13
#define BUSDRIVER 	14
#define PAPERBOY 	15
#define TRUCKER     16
#define TRASHMAN  	17
#define LOADER 		18
#define WOODSMAN  	19
#define FISHER  	20
#define FIREMAN		21
#define COOKER  	22



#define DRUGDEALER  4
#define CARJACKER   5
#define ARMSDEALER	9
*/
stock JobMenu(playerid)
{//вызывается из biz_OnEnterCheckpoint(playerid), сработает в Мэрии
	new listitems[1235];
	strcat(listitems, "\nМеню вакансий\
\n1.\t Шахтёр({00FF00}без регистрации{A9C4E4})\
\n2.\t Адвокат({00FF00}без регистрации{A9C4E4})\
\n3.\t Ремонтник дорог\
\n4.\t Наркоторговец({00FF00}нелегальная{A9C4E4})\
\n5.\t Автоугонщик({00FF00}нелегальная{A9C4E4})\
\n6.\t Автоскупщик\
\n7.\t Автомеханик\
\n8.\t Фермер({00FF00}без регистрации{A9C4E4})\
\n9.\t Оружейный диллер({00FF00}нелегальная{A9C4E4})");
	strcat(listitems, "\n10.\t Автодилер\
\n11.\t Инкассатор\
\n12.\t Букмекер({00FF00}без регистрации{A9C4E4})\
\n13.\t Таксист\
\n14.\t Водитель автобуса\
\n15.\t Курьер\
\n16.\t Дальнобойщик\
\n17.\t Водитель мусоровоза\
\n18.\t Грузчик({00FF00}без регистрации{A9C4E4})\
\n19.\t Плотник({00FF00}без регистрации{A9C4E4})");
	strcat(listitems, "\n20.\t Рыбалов({00FF00}без регистрации{A9C4E4})\
\n21.\t Пожарник({00FF00}без регистрации{A9C4E4})\
\n22.\t Повар({00FF00}без регистрации{A9C4E4})");
	ShowPlayerDialogEx(playerid, JOBMENU_DIALOG, DIALOG_STYLE_LIST, "Список доступных работ", listitems, "Ок", "Отмена");
}

stock jobs_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext

	Job2Menu_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	MenuVacancies_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	jobmanual_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	GangsVacancies_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);

	if(dialogid != JOBMENU_DIALOG) return 1;

	if(!response) return 1;

	switch(listitem)
	{
		case 0:
		{
			MenuVacancies(playerid);
			return 1;
		}
		case 3://3 RoadWorker Registration
		{
			//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~RoadWorker~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
		    if(PlayerInfo[playerid][pJob] > 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
				JobMenu(playerid);
				return 1;
			}
			else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
				JobMenu(playerid);
				return 1;
			}
		    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
				JobMenu(playerid);
				return 1;
			}
			else if(IsAGangs(playerid) || PlayerInfo[playerid][pMember] >= DoT)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на эту работу, находясь во фракции или в банде.");
				JobMenu(playerid);
				return 1;
			}
    		/*else if(VehInfo[MyCar[playerid][0]][cModel] != 552 && VehInfo[MyCar[playerid][1]][cModel] != 552 && VehInfo[MyCar[playerid][2]][cModel] != 552 &&
					GetPlayerMoneyH(playerid) < VehicleArray[552-400][Virtual_Price] && PlayerInfo[playerid][pBank] < VehicleArray[552-400][Virtual_Price])
			{
				format(strings, sizeof(strings), "   У вас нет $%d для покупки служебного авто !",VehicleArray[552-400][Virtual_Price]);
				SendClientMessage(playerid, COLOR_GREY, strings);
				JobMenu(playerid);
				return 1;
			}*/
			else
			{
				if(StatusJob[3] == 0)
				{
					GettingJob[playerid] = 3;
					SetPlayerSkinEx(playerid, 260);
					if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 260);
					else SetPlayerSkinEx(playerid, 64);
		   			//TogglePlayerControllableEx(playerid, 1);
   				}
   				else if(StatusJob[3] == 1)
   				{
					SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
					JobMenu(playerid);
					return 1;
				}
	   		}
		}
		case 6://6 AutoBuyer
		{
		    if(PlayerInfo[playerid][pJob] > 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
				JobMenu(playerid);
				return 1;
			}
			else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
				JobMenu(playerid);
				return 1;
			}
		    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
				JobMenu(playerid);
				return 1;
			}
			else if(IsAGangs(playerid))// || PlayerInfo[playerid][pMember] >= DoT
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на эту работу, находясь в банде.");// или во фракции
				JobMenu(playerid);
				return 1;
			}
		    else if(GetPlayerMoneyH(playerid) < 120000)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас нет начального капитала в $120000 для покупки паркинга и лицензии на него.");
				JobMenu(playerid);
				return 1;
			}
			else
			{
				if(StatusJob[6] == 0)
				{
					GettingJob[playerid] = 6;
					if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 72);
					else SetPlayerSkinEx(playerid, 69);
		   			//TogglePlayerControllableEx(playerid, 1);
   				}
   				else if(StatusJob[6] == 1)
   				{
					SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
					JobMenu(playerid);
					return 1;
				}
			}
		}
		case 7://7 CarMechanic Registration
		{
			//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Car Mechanic~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
		    if(PlayerInfo[playerid][pJob] > 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
				JobMenu(playerid);
				return 1;
			}
			else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
				JobMenu(playerid);
				return 1;
			}
		    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
				JobMenu(playerid);
				return 1;
			}
			else if(IsAGangs(playerid) || PlayerInfo[playerid][pMember] >= DoT)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на эту работу, находясь во фракции или в банде.");
				JobMenu(playerid);
				return 1;
			}
   			/*else if(VehInfo[MyCar[playerid][0]][cModel] != 525 && VehInfo[MyCar[playerid][1]][cModel] != 525 && VehInfo[MyCar[playerid][2]][cModel] != 525 &&
				GetPlayerMoneyH(playerid) < VehicleArray[525-400][Virtual_Price] &&
				PlayerInfo[playerid][pBank] < VehicleArray[525-400][Virtual_Price])
			{
				format(strings, sizeof(strings), "   У вас нет $%d для покупки служебного авто !",VehicleArray[525-400][Virtual_Price]);
				SendClientMessage(playerid, COLOR_GREY, strings);
				JobMenu(playerid);
				return 1;
			}*/
			else
			{
				if(StatusJob[7] == 0)
				{
					GettingJob[playerid] = 7;
					if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 50);
					else SetPlayerSkinEx(playerid, 157);
		   			//TogglePlayerControllableEx(playerid, 1);
   				}
   				else if(StatusJob[7] == 1)
   				{
					SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
					JobMenu(playerid);
					return 1;
				}
			}
		}
		case 10://10 CarDealer Registration
		{
			//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Car Dealer~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
		    if(PlayerInfo[playerid][pJob] > 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
				JobMenu(playerid);
				return 1;
			}
			else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
				JobMenu(playerid);
				return 1;
			}
		    else if(PlayerInfo[playerid][pLevel] < 4)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Ваш уровень ниже 4!");
				JobMenu(playerid);
			}
		    else if(PlayerInfo[playerid][pBank]+GetPlayerMoneyH(playerid) < 60000)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас нету $60000!");
				JobMenu(playerid);
			}
		    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
				JobMenu(playerid);
				return 1;
			}
			else if(IsAGangs(playerid) || PlayerInfo[playerid][pMember] >= DoT)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на эту работу, находясь во фракции или в банде.");
				JobMenu(playerid);
				return 1;
			}
    		else if(GetPlayerMoneyH(playerid) < VehicleArray[604-400][Virtual_Price] && PlayerInfo[playerid][pBank] < VehicleArray[604-400][Virtual_Price])
			{
				format(strings, sizeof(strings), "   У вас нет даже $%d для продажи самой дешёвой авто !", VehicleArray[604-400][Virtual_Price]);
				SendClientMessage(playerid, COLOR_GREY, strings);
				JobMenu(playerid);
				return 1;
			}
			else
			{
				if(StatusJob[10] == 0)
				{
					GettingJob[playerid] = 10;
					if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 15);
					else SetPlayerSkinEx(playerid, 148);
		   			//TogglePlayerControllableEx(playerid, 1);
   				}
   				else if(StatusJob[10] == 1)
   				{
					SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
					JobMenu(playerid);
					return 1;
				}
			}
		}
		case 11://11 Inkassator Registration
		{
			//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Inkassator~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
		    if(PlayerInfo[playerid][pJob] > 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
				JobMenu(playerid);
				return 1;
			}
			else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
				JobMenu(playerid);
				return 1;
			}
			else if(PlayerInfo[playerid][pCarLic] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без водительского удостоверения.");
				JobMenu(playerid);
				return 1;
			}
		    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
				JobMenu(playerid);
				return 1;
			}
    		/*else if(VehInfo[MyCar[playerid][0]][cModel] != 428 && VehInfo[MyCar[playerid][1]][cModel] != 428 && VehInfo[MyCar[playerid][2]][cModel] != 428 &&
				GetPlayerMoneyH(playerid) < VehicleArray[428-400][Virtual_Price] && PlayerInfo[playerid][pBank] < VehicleArray[428-400][Virtual_Price])
			{
				format(strings, sizeof(strings), "   У вас нет $%d для покупки служебного авто !",VehicleArray[428-400][Virtual_Price]);
				SendClientMessage(playerid, COLOR_GREY, strings);
				JobMenu(playerid);
				return 1;
			}*/
			else if(IsAGangs(playerid) || PlayerInfo[playerid][pMember] >= DoT)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на эту работу, находясь во фракции или в банде.");
				JobMenu(playerid);
				return 1;
			}
			else
			{
				if(StatusJob[11] == 0)
				{
					GettingJob[playerid] = 11;
					if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 71);
					else SetPlayerSkinEx(playerid, 194);
		   			//TogglePlayerControllableEx(playerid, 1);
   				}
   				else if(StatusJob[11] == 1)
   				{
					SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
					JobMenu(playerid);
					return 1;
				}
	   		}
		}
		case 13://для таксистов 13 TaxiDriver
		{
			//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~TaxiDriver~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
		    if(PlayerInfo[playerid][pJob] > 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
				JobMenu(playerid);
				return 1;
			}
			else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
				JobMenu(playerid);
				return 1;
			}
			else if(PlayerInfo[playerid][pCarLic] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без водительского удостоверения.");
				JobMenu(playerid);
				return 1;
			}
		    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
				JobMenu(playerid);
				return 1;
			}
			/*else if(IsAGangs(playerid) || PlayerInfo[playerid][pMember] >= DoT)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на эту работу, находясь во фракции или в банде.");
				JobMenu(playerid);
				return 1;
			}*/
    		/*else if(VehInfo[MyCar[playerid][0]][cModel] != 438 && VehInfo[MyCar[playerid][1]][cModel] != 438 && VehInfo[MyCar[playerid][2]][cModel] != 438 &&
				GetPlayerMoneyH(playerid) < VehicleArray[438-400][Virtual_Price] && PlayerInfo[playerid][pBank] < VehicleArray[438-400][Virtual_Price])
			{
				format(strings, sizeof(strings), "   У вас нет $%d для покупки служебного авто !",VehicleArray[438-400][Virtual_Price]);
				SendClientMessage(playerid, COLOR_GREY, strings);
				JobMenu(playerid);
				return 1;
			}*/
			else
			{
				if(StatusJob[13] == 0)
				{
					GettingJob[playerid] = 13;
					if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 61);
					else SetPlayerSkinEx(playerid, 172);
		   			//TogglePlayerControllableEx(playerid, 1);
   				}
   				else if(StatusJob[13] == 1)
   				{
					SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
					JobMenu(playerid);
					return 1;
				}
	   		}
		}
		case 14://14 BusDriver Registration
		{
			//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Bus Driver~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
		    if(PlayerInfo[playerid][pJob] > 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
				JobMenu(playerid);
				return 1;
			}
			else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
				JobMenu(playerid);
				return 1;
			}
			else if(PlayerInfo[playerid][pCarLic] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без водительского удостоверения.");
				JobMenu(playerid);
				return 1;
			}
		    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
				JobMenu(playerid);
				return 1;
			}
			/*else if(IsAGangs(playerid) || (PlayerInfo[playerid][pMember] >= DoT && PlayerInfo[playerid][pMember] != DoE) )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на эту работу, находясь во фракции (кроме МоЕ) или в банде.");
				JobMenu(playerid);
				return 1;
			}*/
    		/*else if(VehInfo[MyCar[playerid][0]][cModel] != 431 && VehInfo[MyCar[playerid][1]][cModel] != 431 && VehInfo[MyCar[playerid][2]][cModel] != 431 &&
				GetPlayerMoneyH(playerid) < VehicleArray[431-400][Virtual_Price] && PlayerInfo[playerid][pBank] < VehicleArray[431-400][Virtual_Price])
			{
				format(strings, sizeof(strings), "   У вас нет $%d для покупки служебного авто !",VehicleArray[431-400][Virtual_Price]);
				SendClientMessage(playerid, COLOR_GREY, strings);
				JobMenu(playerid);
				return 1;
			}*/
			else
			{
				if(StatusJob[14] == 0)
				{
					GettingJob[playerid] = 14;
					if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 255);
					else SetPlayerSkinEx(playerid, 93);
		   			//TogglePlayerControllableEx(playerid, 1);
   				}
   				else if(StatusJob[14] == 1)
   				{
					SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
					JobMenu(playerid);
					return 1;
				}
	   		}
		}
		case 15://15 PaperBoy Registration
		{	//для курьеров
			//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Paperboy~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
		    if(PlayerInfo[playerid][pJob] > 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
				JobMenu(playerid);
				return 1;
			}
			else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
				JobMenu(playerid);
				return 1;
			}
		    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
				JobMenu(playerid);
				return 1;
			}
			else if( IsAGangs(playerid)	|| (PlayerInfo[playerid][pMember] >= DoT &&
					PlayerInfo[playerid][pMember] != SAN) )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Стать курьером могут только репортёры или гражданские.");
				JobMenu(playerid);
				return 1;
			}
			else
			{
				if(StatusJob[15] == 0)
				{
					GettingJob[playerid] = 15;
					if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 188);
					else SetPlayerSkinEx(playerid, 193);
		   			//TogglePlayerControllableEx(playerid, 1);
   				}
   				else if(StatusJob[15] == 1)
   				{
					SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
					JobMenu(playerid);
					return 1;
				}
			}
		}
		case 16://16 Trucker Registration
		{
			//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Trucker~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
		    if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pLevel] > 3)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
				JobMenu(playerid);
				return 1;
			}
			else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
				JobMenu(playerid);
				return 1;
			}
			else if(PlayerInfo[playerid][pCarLic] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без водительского удостоверения.");
				JobMenu(playerid);
				return 1;
			}
			else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 3 && !gTutorial[playerid])
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
				JobMenu(playerid);
				return 1;
			}
			else
			{
				if(StatusJob[16] == 0 || PlayerInfo[playerid][pLevel] == 1 || PlayerInfo[playerid][pLevel] == 2)
				{
					GettingJob[playerid] = 16;
					if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 133);
					else SetPlayerSkinEx(playerid, 204);
		   			//TogglePlayerControllableEx(playerid, 1);
   				}
   				else if(StatusJob[16] == 1)
   				{
					SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
					JobMenu(playerid);
					return 1;
				}
	   		}
		}
		//для мусорщиков
		case 17://17 Trashman Registration
		{
		    if(PlayerInfo[playerid][pJob] > 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
				JobMenu(playerid);
				return 1;
			}
			else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
				JobMenu(playerid);
				return 1;
			}
		    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
				JobMenu(playerid);
				return 1;
			}
			else if(IsAGangs(playerid) || PlayerInfo[playerid][pMember] >= DoT)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Стать Водителем Мусоровоза могут только гражданские.");
				JobMenu(playerid);
				return 1;
			}
	    	/*else if(VehInfo[MyCar[playerid][0]][cModel] != 408 && VehInfo[MyCar[playerid][1]][cModel] != 408 && VehInfo[MyCar[playerid][2]][cModel] != 408 &&
				GetPlayerMoneyH(playerid) < VehicleArray[408-400][Virtual_Price] && PlayerInfo[playerid][pBank] < VehicleArray[408-400][Virtual_Price])
			{
				format(strings, sizeof(strings), "   У вас нет $%d для покупки служебного авто !",VehicleArray[408-400][Virtual_Price]);
				SendClientMessage(playerid, COLOR_GREY, strings);
				JobMenu(playerid);
				return 1;
			}*/
			else
			{
				if(StatusJob[17] == 0)
				{
					GettingJob[playerid] = 17;
					if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 128);
					else SetPlayerSkinEx(playerid, 64);
   				}
   				else if(StatusJob[17] == 1)
   				{
					SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
					JobMenu(playerid);
					return 1;
				}
			}
		}
		case DRUGDEALER, CARJACKER, ARMSDEALER:
		{
			new msgitem[62+135+69];
			strcat(msgitem, "К сожалению в мерии не занимаются нелегальными профессиями.\n");
			strcat(msgitem, "Если Вы хотите влиться в криминальную жизнь, \nто необходимо обратиться к одной из семей штата: La Cosa Nostra (LS) или Yakuza (SF).\n");
			strcat(msgitem, "Увы, но нам запрещено говорить на эту тему. Ищите информацию сами.\n");
			ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, "МЭРИЯ", msgitem, "OK", "");
			return 1;
		}
		default:
		{
			new msgitem[13*77];
			strcat(msgitem, "В штате San Andreas вы так же можете подработать.\n");
			strcat(msgitem, "Для этого вам НЕ требуется трудоустройство в Мэрии.\n");
			strcat(msgitem, "Вы просто должны приехать на место работы\n");
			strcat(msgitem, "и стать на синюю маячку(таким образом вы берёте дежурство).\n");
			strcat(msgitem, "Доступные подработки: Шахтёр(/gps 1049), Фермер(/gps 1032),\n");
			strcat(msgitem, "Букмекер(Следует зайти в спорт. зал LS или LV), Грузчик(/gps 1046),\n");
			strcat(msgitem, "Дровосек(/gps 1050), Пожарник(/gps 1051).\n");
			strcat(msgitem, "Но если вы захотите отвлечься от насущных проблем,\n");
			strcat(msgitem, "то смело можете поехать ловить рыбу на Пирс LS или купив себе лодку\n");
			strcat(msgitem, "и выйдя на ней в открытое море(USE: /fishhelp).\n");
			strcat(msgitem, "Ну а если вы любите пассивную охоту, т.е. вы заядлый грибник,\n");
			strcat(msgitem, "то рекомендуем вам прокатиться по штату и насобирать грибы в своё лукошко.\n");
			strcat(msgitem, "Потом грибы можно продать в Пункт Приёма(/gps 1033).\n");
			ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, "МЭРИЯ", msgitem, "OK", "");
			return 1;
		}
	}//end switch
	JobManual(playerid, JOB_DIALOG, DIALOG_STYLE_MSGBOX, "Accept", "Cancel", GettingJob[playerid]);
	return 1;
}


stock JobManual(playerid, dialogid, style, button1[], button2[], job)//caption[], info[],
{   //для запрета показа диалого при открытом диалоге //вызывает из JobMenu(playerid)
	if(GetPVarInt(playerid, "gShowDialog") != -1) return 1;
	//если флаг поднят, то выйти, т.е. не загружать.

	if(	GetPlayerState(playerid) == PLAYER_STATE_DRIVER &&
		GetVehicleSpeed(nCarID[playerid]) > 10)
	{ 	//для запрета показа диалого при скорости машины больше 10
		format(strings, sizeof(strings), "  dialogid[%d] заблокировано. Скорость машины больше 10 !", dialogid);
		SendClientMessage(playerid, COLOR_GREY, strings);
 		return 1;
    }
	SetPVarInt(playerid, "gShowDialog", dialogid);

    new bigmsgitem[2093];
    new caption[65];
	if(job == MINER)
	{
		caption = "Профессия шахтёра";
		strcat(bigmsgitem, "Ваша задача - добывать соль в шахте.\n");
		strcat(bigmsgitem, "Чтобы начать работу шахтера необходимо приехать в карьер и пройти в раздевалку (/gps 1049), где вы переоденетесь и возьмёте инструмент.\n");
		strcat(bigmsgitem, "Затем отправляйтесь в шахту для добычи соли. Войдя в шахту, проследуйте к одному из мест добычи. Для добычи соли используйте ЛКМ(Левую Кнопку Мыши).\n");
		strcat(bigmsgitem, "После того, как вы совершите необходимое кол-во ударов вам будет выдана телега. Её необходимо доставить на склад обозначенный маркером.\n");
		strcat(bigmsgitem, "Для окончания работы проследуйте в раздевалку.\n");
		strcat(bigmsgitem, "Чем выше ваш скилл, тем больше соли за раз вы сможете добыть.\n\n");
		strcat(bigmsgitem, "Средний заработок за час: ~8676$\n");
	}
	else if(job == LAWYER)
	{
		caption = "Профессия адвоката";
		strcat(bigmsgitem, "Эта работа позволяет вам освобождать заключённых, отбывающих наказание в Зоне 51.\n");
		strcat(bigmsgitem, "Чтобы увидеть список заключённых и размер их залога - введите /jailstats. Иногда заключённые через объявления сами просят помощи у адвокатов.\n");
		strcat(bigmsgitem, "Чтобы освободить заключённого, нужно убедиться, что он сам желает выйти на свободу и у него есть деньги, чтобы выплатить залог.\n");
		strcat(bigmsgitem, "После чего нужно двигаться к Зоне 51 (/gps 1028). На КПП Зоны 51 сообщите, что вы адвокат и имя заключённого.\n");
		strcat(bigmsgitem, "Если вам не откажут, то проведут к камерам, где вам нужно будет ввести (free [id заключённого].\n");
		strcat(bigmsgitem, "Отказать вам могут, если на Зоне51 идёт бой или мало военных онлайн.\n");
		strcat(bigmsgitem, "Сумма заработка составляет половину залога. Вторая половина пополняет 'общак' семьи.\n");
		strcat(bigmsgitem, "На пятом уровне навыка (/skill) вам не требуется ордер на освобождение.\n");
		strcat(bigmsgitem, "Найти клиентов можно, подав объявление (/service -> Объявление) примерно такого содержания: 'Работает квалифицированный адвокат'.\n\n");
	}
	else if(job == ROADWORKER)
	{
		caption = "Профессия дорожного рабочего";
		strcat(bigmsgitem, "Ваша задача - устанавливать на мостах заграждения и возить к этому месту стройматериалы.\n");
		format(bigmsgitem, sizeof(bigmsgitem), "%sПосле получения профессии нужно купить рабочий транспорт Utility_Van (id 552) в автосалоне (/gps 1015) за $%d.\n",bigmsgitem, VehicleArray[552-400][Virtual_Price]);
		strcat(bigmsgitem, "Затем, выйдя на дежурство, на машине подъехать к мосту, на котором установлен полицейский радар.\n");
		strcat(bigmsgitem, "Приближение к таким мостам можно отследить при наличии Антирадара(купить можно в магазинах 24/7).\n");
		strcat(bigmsgitem, "Подъехав к мосту, установите ремонтное заграждение, нажав на "#VEHICLE_TURRETUP". \nТеперь вам нужно возить к этому месту стройматериалы и чинить мост, нажимая на "#VEHICLE_TURRETUP".\n");
		strcat(bigmsgitem, "Существует место, где их можно взять: используйте /gps 1038 и ищите коричневую коробку.\n");
		strcat(bigmsgitem, "Заграждение перекрывает мост полностью, поэтому водители, не желающие ехать в объезд, 'ремонтируют' его, нажимая на сигнал.\n");
		strcat(bigmsgitem, "При этом вам перечисляются деньги. Мост исчезнет, когда будет отремонтирован или если вы покинете сервер.\n");
		strcat(bigmsgitem, "Бывалые ремонтники рекомендуют чинить мост Foothill.\n\n");
		strcat(bigmsgitem, "Средний заработок в час: ~10224$\n");
	}
	else if(job == DRUGDEALER)
	{
		caption = "Профессия наркодилера";
		strcat(bigmsgitem, "Вам предстоит заняться продажей наркотиков.\n");
		strcat(bigmsgitem, "Наркотики используются для пополнения здоровья и пользуются спросом, в основном, у преступников.\n");
		strcat(bigmsgitem, "Одна доза (2 г.) восстанавливает 23 хитпоинта. Стоит помнить, что после принятия 8 г. у вас будет передозировака.\n");
		strcat(bigmsgitem, "Для начала нужно добраться до притона в Лос-Сантосе (/gps 1006),\n");
		strcat(bigmsgitem, "подойти к пакету с наркотиками и выбрать количество грамм для покупки.");
		strcat(bigmsgitem, "На первом скилле (/skill) можно взять максимум 6 г., на пятом - 100 г.\n");
		strcat(bigmsgitem, "Чтобы увидеть количество порошка у вас в наличии - введите /items.\n");
		strcat(bigmsgitem, "Цена закупки зависит от скилла. Один грамм стоит 30$ на 1 скилле и 10$ - на пятом.\n");
		strcat(bigmsgitem, "Будьте осторожны, т.к. иметь при себе наркотики - противозаконно. Агенты ФБР могут найти их, если вас обыщут.\n");
		strcat(bigmsgitem, "Чтобы найти покупателей, можно подать объявление (/service -> Объявление) с примерно таким содержанием: 'Продаю зубной порошок'.\n");
		strcat(bigmsgitem, "Для продажи исользуйте команду /selldrugs [id игрока][Кол-во грамм][Цена].\n");
		strcat(bigmsgitem, "Половина выручки с продажи пойдёт в 'общак' банды или семьи.\n");
		strcat(bigmsgitem, "Сделки стоит проводить в тихих местах, убедившись, что рядом нету полицейских.\n");
		strcat(bigmsgitem, "Если клиентов нет, можно перевозить пакеты с коноплёй.\n");
		strcat(bigmsgitem, "Взять их можно на Ферме (/gps 1032) на значке '$' и везти в Притон (/gps 1006) для сдачи на пакете с наркотиками.\n");
		strcat(bigmsgitem, "Если вы привезёте пакеты менее, чем за 60 секунд, ваш скилл обнулится.\n\n");
		strcat(bigmsgitem, "Средний заработок в час: ~5940$\n");
	}
	else if(job == CARJACKER)
	{
		caption = "Профессия автоугонщика";
		strcat(bigmsgitem, "Вы будете зарабатывать на краже и сдаче автомобилей игроков на Паркинг (/gps 1024).\n");
		strcat(bigmsgitem, "На 1 скилле вы можете угонять только не запаркованные машины без противоугонного замка\n");
		strcat(bigmsgitem, "(который игроки покупают в 24/7 за 1.000$). Такие замки можно открыть только после получения 5 скилла (/skill).\n");
		strcat(bigmsgitem, "Для угона машины нужно купить отмычки в любом магазине 24/7 (Skeleton Key, стоит 100$).\n");
		strcat(bigmsgitem, "После надо найти незапаркованный авто и ввести команду /steal. Появится полоса взлома, как только она заполнится - машина будет открыта.\n");
		strcat(bigmsgitem, "Далее садимся в автомобиль и едем на паркинг (/gps 1024) и командой /dropcar сдаём на этаже с самым выгодным процентом.\n");
		strcat(bigmsgitem, "Стоит помнить: как только вы начали взлом, все патрули в штате получат сообщение об этом.\n");
		strcat(bigmsgitem, "Если вам не везёт и не удаётся найти подходящий транспорт - вы можете перевозить материалы и перепродавать их в 24/7.\n");
		strcat(bigmsgitem, "Для этого следует подъехать к месту получения материалов (/gps 1039) и взять серый ящик.\n");
		strcat(bigmsgitem, "Потом едьте в город Лос-Сантос к месту сдачи материалов (/gps 1040), чтобы сдать их, придётся спуститься в туннель.\n");
		strcat(bigmsgitem, "Когда вы перевезёте достаточное кол-во материалов, вы можете продать их в магазинах 24/7 командой /sell SkeletonKey.\n\n");
		strcat(bigmsgitem, "Средний заработок в час на продаже материалов: ~1890$\n");
	}
	else if(job == AUTOBUYER)
	{
		caption = "Профессия автоскупщика";
		strcat(bigmsgitem, "Для того, чтобы работать, вам обязательно нужно приобрести один из этажей паркинга (/gps 1024).\n");
		strcat(bigmsgitem, "Ваш заработок будет разницей между суммой, получаемой за продажу автомобилей и суммой, \nкоторую вы будете отдавать автоугонщикам, пригоняющим вам эти машины.\n");
		strcat(bigmsgitem, "Чтобы получить возможность купить паркинг, обязательно приобретите лицензию на покупку у солиситора в Мэрии. \nЗатем едьте к паркингу, поднимайтесь на нужный этаж\n");
		strcat(bigmsgitem, "и покупайте его. Процент скупки машин у автоугонщиков устанавливается командой /bizfee, \nпроцент продажи жителям штата - /prodprice. \n");
		strcat(bigmsgitem, "При выставлении цен ориентируйтесь на остальные этажи и ставьте проценты так, \nчтобы везти и покупать машины к вам было выгодно.\n");
		strcat(bigmsgitem, "У вас есть возможность купить у игрока машину, сев на пассажирское сиденье и введя команду /buycar.\n");
		strcat(bigmsgitem, "Для расстановки всех машин по местам и открытия - /showparking.\n\n");
	}
	else if(job == CARMECHANIC)
	{
		caption = "Профессия механика";
		strcat(bigmsgitem, "Ваша работа заключается в том, чтобы ремонтировать, заправлять и тюнинговать транспорт других игроков.\n");
		format(bigmsgitem, sizeof(bigmsgitem), "%sПосле получения профессии нужно купить рабочий транспорт Towtruck (id 525) в автосалоне (/gps 1015) за $%d.\n",bigmsgitem, VehicleArray[525-400][Virtual_Price]);
		strcat(bigmsgitem, "Затем доберитесь до базы механиков (/gps 1030) и в здании выйдите на дежурство (зайдя на синий маркер в виде майки).\n");
		strcat(bigmsgitem, "Для того, чтобы починить чью-нибудь машину, введите /repair [id][сумма]. Чтобы заправить - /refill [id][сумма].\n");
		strcat(bigmsgitem, "Для выполнения всех этих действий вы Не должны находиться в транспортном средстве. Для тюнинга своего автомобиля введите команду /tuning.\n");
		strcat(bigmsgitem, "Для тюнинга чужого автомобиля сядьте в автомобиль на пассажирское сидение и введите /moding.\n");
		strcat(bigmsgitem, "Во время тюнинга автомобиля расходуются материалы, которые можно получить, цепляя и отвозя оставленные не на парковках автомобили на свалку.\n");
		strcat(bigmsgitem, "Местонахождение свалки - /gps 1031. За одну привезённую машину вам дают около от 3 материалов на 1 скилле (/skill). Посмотреть количество материалов можно, введя /stats.\n");
		strcat(bigmsgitem, "Основные парковки - возле автошколы, Мэрии, автосалона, больницы.\n");
		strcat(bigmsgitem, "Во время заправки и починки смотрите на уровень заказчика. Новичкам выставляйте ценник поменьше, игрокам побогаче - побольше. Время от времени игроки вызывают механика через /service.\n");
		strcat(bigmsgitem, "Получив вызов, стоит созвониться по телефону и помочь человеку. Нередко так и завязывается дружба.\n");
		strcat(bigmsgitem, "При сдаче авто на Базу Mexaников(/gps 1030) вам начисляются деньги. При сдаче авто на Свалку(/gps 1031) - материалы. Так что сами выбирайте свои приоритеты.\n\n");
	    strcat(bigmsgitem, "Средний заработок в час: ~10092$\n");
	}
	else if(job == FARMER)
	{
		caption = "Профессия фермера";
		strcat(bigmsgitem, "Чтобы начать работу подойдите к зданию Фермы (/gps 1032) и переоденьтесь в рабочую одежду.\n");
		strcat(bigmsgitem, "Получив саженец, на вашей карте появится чекпоинт, идите на него. Посадив кустик и идите за новым саженцем.\n");
		strcat(bigmsgitem, "Когда засеете всё поле и урожай ("#MAX_POLE" кустов) созреет, снимите рубашку на всё том же маркере\n");
		strcat(bigmsgitem, "и начинайте косить. Т.е. вам надо просто пройти последовательно все кусты от первого до последнего.\n");
		strcat(bigmsgitem, "и останавливаться в центре каждого кустика.\n");
		strcat(bigmsgitem, "После того, как всё поле будет скошено, собирайте снопы и относите их в ангар\n\n");
	    strcat(bigmsgitem, "Средний заработок в час: ~905$\n");
	}
	else if(job == ARMSDEALER)
	{
		caption = "Профессия оружейника";
		strcat(bigmsgitem, "Вы будете зарабатывать изготавливая и продавая холодное и огнестрельное оружие.\n");
		strcat(bigmsgitem, "На изготовление оружия расходуются материалы. Они появляются, когда вы подберёте коробку на зоне 51 (/gps 1028)\n");
		strcat(bigmsgitem, "и перевезёте её на завод в Сан-Фиерро - промзону, граничащую с автошколой (/gps 1037).");
		strcat(bigmsgitem, "На первом скилле (/skill) за один рейсвы получаете 1800 материалов.");
		strcat(bigmsgitem, "Чтобы затрачивать на 30% меньше материалов при изготовлении, при повышении своего уровня прокачайте перк Miser.\n");
		strcat(bigmsgitem, "На первом скилле вы можете продавать холодное оружие и некоторые виды огнестрельного: кольт, дробовик.\n");
		strcat(bigmsgitem, "С повышением уровня вам станет доступно оружие, не встречающееся в оружейных магазинах, например, снайперская винтовка.\n");
		strcat(bigmsgitem, "Изготовить и продать клиенту оружие можно командой /sellgun [id][название оружия][сумма].\n");
		strcat(bigmsgitem, "Работать удобнее всего на вертолёте, ведь ваша работа является незаконной. При продаже оружия в чате появляется текст об этом, видимый другими в определённом радиусе.\n");
		strcat(bigmsgitem, "Поэтому сделки лучше всего осуществлять в малопосещаемых и уединённых местах и с надёжными людьми..\n");
		strcat(bigmsgitem, "Найти покупателей можно, подав объявление (/service -> Объявление) примерно такого содержания: 'Продаю опасные игрушки. Гарантия'.\n");
		strcat(bigmsgitem, "Всегда будьте начеку - это важнейший закон выживания. Помните, что половина вырученных вами денег пополняет 'общак'.\n");
        strcat(bigmsgitem, "Также можно продавать материалы в Аммо командой /sellgun.\n");
        strcat(bigmsgitem, "Дополнительный заработок в час: ~5880$ или 16800 материалов.\n");
	}
	else if(job == CARDEALER)
	{
		caption = "Профессия автодилера";
		strcat(bigmsgitem, "Вы будете зарабатывать, продавая игрокам новые автомобили, мотоциклы, лодки, самолёты и вертолёты.\n");
		strcat(bigmsgitem, "Устроившись на работу, отправляйтесь в автосалон (/gps 1015), становитесь за стойку и ждите клиентов.\n");
		strcat(bigmsgitem, "Клиенты будут сами приходить в салон и называть ID машины или её название (иногда ещё и цвет, основной и дополнительный).\n");
		strcat(bigmsgitem, "Вы смотрите, сколько машина стоит через /carinfo, устанавливаете наценку,\n");
		strcat(bigmsgitem, "сообщаете получившуюся цену покупателю и, если он согласен, вводите команду /sellcar [id игрока] [id машины] [основной цвет] [дополнительный цвет].\n");
		strcat(bigmsgitem, "При этом пространство внутри салона должно быть свободным от машин. Кроме того, чтобы продать машину, нужно самому иметь необходимую сумму,\n");
		strcat(bigmsgitem, "т.к. вы заказываете машину за свои деньги, и только потом вам перечисляется сумма, которую платит покупатель.\n");
		strcat(bigmsgitem, "От вашего скилла (/skill) зависит количество страховок, т.е. сколько раз владелец машины сможет телепортировать её к себе командой /callcar (1 скилл - 1 раз, 5 скилл - 5 раз).\n");
		strcat(bigmsgitem, "При этом из машины будут высажены все, кто там сидел.\n");
		strcat(bigmsgitem, "При выходе из игры страховки сохраняются. Вы можете застраховать любую машину на сервере, сев на пассажирское сиденье и введя команду /insurance [id] [сумма].\n");
		strcat(bigmsgitem, "Среди автодилеров есть конкуренция - не обманывайте покупателей, иначе к вам перестанут обращаться. Наценку устанавливайте в зависимости от уровня клиента и вида машины.");
		strcat(bigmsgitem, "Страховки защищают машины от несчастных случаев.\n");
		strcat(bigmsgitem, "Со временем у вас сложится база клиентов, которые будут стараться найти именно вас, чтобы купить транспорт. Поэтому нужно создать себе репутацию с самого начала.\n\n");
		strcat(bigmsgitem, "Дополнительный заработок в час: ~1918$\n");
	}
	else if(job == INKASSATOR)
	{
		caption = "Профессия инкассатора";
		strcat(bigmsgitem, "Вы будете зарабатывать деньги, перевозя наличность из бизнесов и компаний в банк (/gps 1026).\n");
		format(bigmsgitem, sizeof(bigmsgitem), "%sПосле получения профессии нужно купить рабочий транспорт Securicar (id 428) в автосалоне (/gps 1015) за $%d.\n",bigmsgitem, VehicleArray[428-400][Virtual_Price]);
		strcat(bigmsgitem, "Вводите команду /paydesk возле бизнеса(компании). Размер суммы зависит от навыка (/skill) инкассатора, на 1 скилле - 100.000, на 5 - 1.000.000.\n");
		strcat(bigmsgitem, "После вы можете двигаться к банку (/gps 1026). Заехав на маркер, вы получите 3% от перевозимой суммы.\n");
		strcat(bigmsgitem, "Если владелец вошел или вышел с сервера во время перевозки, задание не сбивается. Стоит нанимать охрану при перевозке крупных сумм денег.\n\n");
		strcat(bigmsgitem, "Средний заработок за рейс: ~2000$.\n");
	}
	else if(job == BOOKMAKER)
	{
		caption = "Профессия букмекера";
		strcat(bigmsgitem, "Вы будете зарабатывать деньги, устраивая бои. Бой может пройти только в одном из двух спортзалов штата.\n");
		strcat(bigmsgitem, "Первый находится возле притона (/gps 1006). Второй - в Лас-Вентурасе к юго-западу от паркинга (/gps 1024). При входе в залы\n");
		strcat(bigmsgitem, "у вас отбирается всё оружие и наркотики. Чтобы начать бой, букмекер, находясь в зале, должен предложить двум присутствующим подняться\n");
		strcat(bigmsgitem, "на ринг командой /secundans [id первого] [id второго]. После того, как оба игрока подтвердят желание драться, они\n");
		strcat(bigmsgitem, "окажутся на ринге. Оба бойца должны быть здоровыми и без розыска. Первый принявший бой окажется на ринге в синих трусах, второй - в красных.\n");
		strcat(bigmsgitem, "Затем букмекер командой /dorate приглашает каждого зрителя (и себя самого) сделать ставки на синего или на красного бойца.\n");
		strcat(bigmsgitem, "После ставок командой /fight бой начинается и длится до трёх побед. После боя проигравший, умерев, спавнится по месту работы либо\n");
		strcat(bigmsgitem, "дома, а победивший телепортируется к букмекеру, начавшему бой. Зрителям, в зависимости от результата боя, выдаётся выигрыш.\n");
		strcat(bigmsgitem, "Для того, чтобы увидеть историю побед и поражений бойца, а также увидеть действующего чемпиона - введите /boxstats [id бойца].\n");
		strcat(bigmsgitem, "Эта профессия не рекомендуется новичкам, т.к. организовать и провести бой, да ещё привлечь туда людей довольно сложно. Можно посоветовать\n");
		strcat(bigmsgitem, "пользоваться объявлениями (/service -> Объявление), чтобы собрать в зале людей.\n\n");
	}
	else if(job == TAXIDRIVER)
	{
		caption = "Профессия таксиста";
		strcat(bigmsgitem, "Ваша работа будет заключаться в том, чтобы перевозить клиентов в место назначения за вознаграждение.\n");
		format(bigmsgitem, sizeof(bigmsgitem), "%sПосле получения профессии нужно купить рабочий транспорт Cabbie или Taxi(id 438 за $%d | id 420 за $%d)\n",
		    bigmsgitem, VehicleArray[438-400][Virtual_Price], VehicleArray[420-400][Virtual_Price]);
		strcat(bigmsgitem, "(USE: /gps 1015). Вы выходите на дежурство автоматически, сев в машину и в появившемся окошке выбрав город, по которому вы будете ездить.\n");
		strcat(bigmsgitem, "Теперь вы отображены в /dutylist. Вас будут вызывать, используя меню /service. \nВ сообщении будет указано, в какой местности находится заказчик.\n");
		strcat(bigmsgitem, "Если клиент далеко, можно созвониться с ним, убедившись, что он не обманет и дождётся машину. Когда пассажир покинет такси - вам\n");
		strcat(bigmsgitem, "перечислятся деньги за проезд. Покинув машину, вы уйдёте с дежурства. \nВы можете выкинуть пассажира из машины командой /eject.\n");
		strcat(bigmsgitem, "Работа таксиста - довольно опасна, и всегда есть риск быть обстреляным преступниками. \nСтоит всегда быть вежливым с клиентами, чтобы в следующий");
		strcat(bigmsgitem, "раз они опять выбрали вас. \nПриезжайте вовремя, не злоупотребляйте командой /eject и обслуживайте популярные маршруты, беря сразу несколько пассажиров.\n");
		strcat(bigmsgitem, "Не будет лишним время от времени рекламировать свои услуги в объявлениях \n(/service -> Объявление). Текст: 'Работает таксист-профессионал'.\n\n");
		strcat(bigmsgitem, "Средний заработок в час: ~9732$\n");
	}
	else if(job == BUSDRIVER)
	{
		caption = "Профессия водитель автобуса";
		strcat(bigmsgitem, "Вы будете зарабатывать деньги, ездя по установленным маршрутам и подвозя пассажиров.\n");
		format(bigmsgitem, sizeof(bigmsgitem), "%sПосле получения профессии нужно купить рабочий транспорт Bus (id 431) за $%d.\n", bigmsgitem, VehicleArray[431-400][Virtual_Price]);
		strcat(bigmsgitem, "(USE: /gps 1015). Садитесь в автобус, выбирайте нужный маршрут из восьми и едьте к первому маркеру, появившемуся на миникарте.\n");
		strcat(bigmsgitem, "На одном маршруте может быть несколько водителей. При смерти или выходе из игры маршрут освобождается.\n");
		strcat(bigmsgitem, "водителя замораживает на 10 секунд для посадки и высадки пассажиров. \nПосле окончания маршрута вам перечисляются деньги в зависимости от самого маршрута,\n");
		strcat(bigmsgitem, "количества перевезённых пассажиров и навыка (/skill). Чем выше навык - тем больше денег вы получите. \nНа конечной остановке всех пассажиров");
		strcat(bigmsgitem, "высаживает.\nЕздите аккуратно и ни в кого не врезайтесь, чтобы не вызвать агрессию.\n\n");
		strcat(bigmsgitem, "Средний заработок в час: ~13375$.\n");
	}
	else if(job == PAPERBOY)
	{
		caption = "Профессия курьера";
		strcat(bigmsgitem, "Вы будете зарабатывать деньги, развозя газеты от редакции к домам, а также продавая их игрокам.");
		strcat(bigmsgitem, "Сложно быть курьером, не имея транспорта. \nПосле получения работы стоит добраться до автосалона (/gps 1015) и купить себе самую дешёвую\n");
		format(bigmsgitem, sizeof(bigmsgitem), "%sмашину - Glendale_Shit(id 604) за $%d или Sadler_Shit(id 605) за $%d. \nЗатем едьте к зданию редакции новостей (/gps 1008).\n",
			bigmsgitem, VehicleArray[604-400][Virtual_Price], VehicleArray[605-400][Virtual_Price]);
		strcat(bigmsgitem, "Подъехав к редакции, просмотрите список готовых к продаже газет командой /papers, \nвыберите одну из них командой /bring [номер газеты].\n");
		strcat(bigmsgitem, "На карте появился маркер и время. Ваша задача - за указанное время (20 минут) доставить газету к маркеру. \nЕсли успели, то ваш навык (/skill) увеличится на 5");
		strcat(bigmsgitem, "и вы получите деньги. \nПолучаемая сумма зависит от навыка. \nОднако, если ваш путь лежит");
		strcat(bigmsgitem, "через посещаемое игроками место (больница, магазин), \nто у вас есть возможность увеличить навык и заработать денег, продавая газеты, которые вы везёте\n");
		strcat(bigmsgitem, "к маркеру, игрокам. Количество экземпляров для продажи не ограничено. \nЧтобы продать газету, введите команду /sellpaper [id игрока] [Цена].\n");
		strcat(bigmsgitem, "Если игроку понравилась проданная газета и он нажал 'Yes' внизу, \nто ваш навык увеличится на единицу. \nПоэтому очень важно продать по пути газету как можно");
		strcat(bigmsgitem, "большему количеству игроков. \nВежливо обращайтесь к каждому встречному с предложением купить газету. \nНо если вы не успеете на маркер - навык уменьшится на -1.\n\n");
		strcat(bigmsgitem, "Средний заработок в час: ~7585$.\n");
	}
	else if(job == TRUCKER)
	{
		caption = "Профессия дальнобойщика";
		strcat(bigmsgitem, "Вы будете зарабатывать деньги на перевозках различных грузов.\n");
		format(bigmsgitem, sizeof(bigmsgitem), "%sПосле получения профессии нужно купить рабочий транспорт Linerunner (id 403) за $%d.\n",bigmsgitem, VehicleArray[403-400][Virtual_Price]);
		strcat(bigmsgitem, "На сервере все бизнессы распределены по сферам деятельности. Существует 5 сфер:\n");
		strcat(bigmsgitem, "Металл - основа для производства товаров индустрии развлечений.\n");
		strcat(bigmsgitem, "Для перевозки необходим грузовик 455 или прицеп 591.\n");
		strcat(bigmsgitem, "Текстиль - основа для производства товаров розничной торговли\n");
		strcat(bigmsgitem, "Для перевозки необходим грузовик 456 или прицеп 435.\n");
		strcat(bigmsgitem, "Продовольствие - основа для производства товаров ресторанного бизнеса.\n");
		strcat(bigmsgitem, "Для перевозки необходим грузовик 423,588 или прицепы 606,607 c тягачом 485.\n");
		strcat(bigmsgitem, "Древесина - основа для производства товаров сферы услуг.\n");
		strcat(bigmsgitem, "Для перевозки необходим грузовик 478 или прицеп 450 для перевозки сырья сферы услуг.\n");
		strcat(bigmsgitem, "Нефть - основа для производства товара промышленной сферы.\n");
		strcat(bigmsgitem, "Для перевозки необходим грузовик 524 или прицеп 584 для перевозки сырья промышленной сферы.\n");
		strcat(bigmsgitem, "Товар - основа для экспорта любой сферы.\n");
		strcat(bigmsgitem, "Для перевозки необходим грузовик категории Фургоны.\n");

		strcat(bigmsgitem, "Подцепив прицеп нажмите "#VEHICLE_TURRETUP", чтобы взять груз, появится меню для ввода кол-ва груза. Чем больше цифра, тем дольше загрузка\n");
		strcat(bigmsgitem, "Имейте ввиду, что загрузка равносильна покупки продуктов, поэтому у вас отнимется сумма равная стоимости груза.\n");
		strcat(bigmsgitem, "После окончании загрузки на карте появится красный маркер и панель со всеми данным по доставки груза.\n");
		strcat(bigmsgitem, "Если у вас куплен GPS-навигатор в магазине 24/7, то вам будет указано направление и расстояние до цели.\n");
		strcat(bigmsgitem, "Задача - за указанное время доставить груз в указанное место.Нужно стараться везти груз аккуратно. Чем меньше он\n");
		strcat(bigmsgitem, "будет повреждён - тем больше гонорар. По прибытию у вас также появится полоса прогресса разгрузки.\n");
		strcat(bigmsgitem, "По окончанию разгрузки вы получите гонорар за кол-во проданных продуктов.\n");
		strcat(bigmsgitem, "Средний заработок в час: +$10000. Средний заработок за рейс: +$5000.\n");
	}
	else if(job == TRASHMAN)
	{
		caption = "Профессия водителя мусоровоза";
        format(bigmsgitem, sizeof(bigmsgitem), "%sЧтобы начать работу необходимо купить TrashMaster (id 408) стоимостью $%d Автосалоне.\n",bigmsgitem, VehicleArray[408-400][Virtual_Price]);
		strcat(bigmsgitem, "Затем отправляйтесь в бытовку (USE: /gps 1047) и переоденьтесь в рабочую одежду\n");
		strcat(bigmsgitem, "Для начала вам надо будет установить контейнер на первом красном маркере\n");
		strcat(bigmsgitem, "Затем на вашей карте появится чекпоинт, едте к нему, чтобы взять мешок с мусором.\n");
		strcat(bigmsgitem, "Отнесите мешок в контейнер и едте за новым мешком. Когда отвезёте нужное вам количество мешков на свалку,\n");
		strcat(bigmsgitem, "то Вы получаете зарплату и увеличиваете навык.\n\n");
		strcat(bigmsgitem, "Средний заработок в час: ~9345$\n");
	}
	else if(job == LOADER)
	{
		caption = "Профессия грузчика";
		strcat(bigmsgitem, "Ваша задача - носить ящики с корабля на Склад и со Склада на корабль.\n");
		strcat(bigmsgitem, "Чтобы начать работу грузчика вам следует приехать в порт (/gps 1046) и переодеться в рабочую одежду.\n");
		strcat(bigmsgitem, "Затем отправиться на грузовое судно за коробкой. Отнесите коробку на склад и идите за новой.\n");
		strcat(bigmsgitem, "Когда отнесёте достаточное вам кол-во коробок приходите в кассу за зарплатой, она находится рядом с раздевалкой.\n\n");
		strcat(bigmsgitem, "Средний заработок в час: ~8480$\n");

	}
	else if(job == WOODSMAN)
	{
		caption = "Профессия лесоруба";
		strcat(bigmsgitem, "Работа доступна только гражданским.\n");
		strcat(bigmsgitem, "Не имеется спаун по работе. Не зависит от онлайна.\n");
		strcat(bigmsgitem, "Ваша задача пилить и перевозить древесину с лесорубки на Склад.\n");
		strcat(bigmsgitem, "Для этого вам стоит приехать на лесорубку (/gps 1050) и стать на майку.\n");
		strcat(bigmsgitem, "Потом садитесь в служебное авто (DFT-500)\n");
		strcat(bigmsgitem, "и направиться пилить близлежащую древесину (На ЛКМ),\n");
		strcat(bigmsgitem, "после того, как вы её распилите,\n");
		strcat(bigmsgitem, "вам следует положить её в авто(На ПКМ) и отвезти на склад.\n");
		strcat(bigmsgitem, "По приезду вам перечислятся деньги.\n\n");
	    strcat(bigmsgitem, "Средний заработок в час: ~15140$\n");
	}
	else if(job == FISHER)
	{
		caption = "Профессия рыбалова";
		strcat(bigmsgitem, "Вам нужно ловить рыбу на Колесе обозрения (/gps 1005) и сдавать её в рыболовный ларёк (/gps 1005).\n");
		strcat(bigmsgitem, "Для начала ловли нужно подойти к удочке и ввести /fish.\n");
		strcat(bigmsgitem, "Пойманная рыба поместится в ваш рюкзак (/items) - её можно будет либо съесть, либо продать.\n");
		strcat(bigmsgitem, "Максимум в ваш рюкзак может поместится 5 рыб.\n");
		strcat(bigmsgitem, "Для продажи в ларьке станьте на значок '$' и выберете, какую рыбу хотите продать.\n");
		strcat(bigmsgitem, "Чем больше будет ваш скилл, тем крупней рыбу вы сможете споймать.\n\n");
	    strcat(bigmsgitem, "Средний заработок в час: ~12896$\n");
	}
	else if(job == FIREMAN)
	{
		caption = "Профессия пожарного";
		strcat(bigmsgitem, "Вам необходимо приехать на пожарную станцию (/gps 1051) и выйти на дежурство. После этого нам начнут поступать вызовы о пожарах,\n");
		strcat(bigmsgitem, "для тушения одного пожара вам даётся 10 минут, если вы не успеваете - недвижимость сгорает.\n");
		strcat(bigmsgitem, "Сподручнее всего тушить пожары на пожарной машине (407id) - находится у пожарной части.\n");
		strcat(bigmsgitem, "Костюм пожарника не восприимчив к пожарам, так что можно смело вступать в борьбу с огнём - не загоритесь.\n\n");
	    strcat(bigmsgitem, "Средний заработок в час: ~4064$\n");
	}
	else if(job == COOKER)
	{
		caption = "Профессия повара";
		strcat(bigmsgitem, "Ваша - покупать в бизнесах замороженную продукцию и готовить её. После этого еду можно будет продать игроку - /sell cooked [cooknumber][id игрока].\n");
	}
	else caption = "Профессия Неизвестна";
	strcat(bigmsgitem, "* Чтобы увидеть команды наберите /jobhelp. Наберите /question если есть вопросы. Хорошей игры.\n");
	strcat(bigmsgitem, "* Вы должны будете отработать эти 2 часа, чтобы получить возможность уволиться и сменить работу.\n");
	strcat(bigmsgitem, "* Нажмите Accept, чтобы принять и проложить маршрут.\n");
	//ShowPlayerDialogEx(playerid, BACKHELP_DIALOG, DIALOG_STYLE_MSGBOX, "*** JOB HELP *** наберите команду для информации", bigmsgitem, "OK", "Назад");

	return ShowPlayerDialogEx(playerid, dialogid, style, caption, bigmsgitem, button1, button2);
}
stock jobmanual_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != JOB_DIALOG) return 1;
//JobManual(playerid, 22, DIALOG_STYLE_MSGBOX, "Accept", "Cancel", GettingJob[playerid]);
	if(response)
	{

	    //else if(!strcmp(x_job, "job", true))//для устройства на работу
	    if(GettingJob[playerid] > 0)
	    {
		    if(PlayerInfo[playerid][pLocal] != 241 && PlayerInfo[playerid][pLocal] != 243 && PlayerInfo[playerid][pLocal] != 244)
		    {
	        	SendClientMessage(playerid, COLOR_GREY, "  Вы Не находитесь в месте трудоустройства !");
	        	return 1;
			}
	        SendClientMessage(playerid, COLOR_GREEN, "* Теперь, когда Вы подтвердили Ваше желание Работать, Вы получили 2-х часовой Контракт.");
	        SendClientMessage(playerid, COLOR_GREEN, "* Поздравляем с вашей новой Работой, наберите /jobhelp, чтобы увидеть ваши новые команды.");
	        SendClientMessage(playerid, COLOR_GREEN, "* Вы всегда сможете посмотреть описание работы набрав команду /jobmanual.");
	        PlayerInfo[playerid][pJob] = GettingJob[playerid];
	        PlayerInfo[playerid][pModel] = GetPlayerSkin(playerid);
	        if(!IsValidSkin(PlayerInfo[playerid][pModel])) PlayerInfo[playerid][pModel] = 78;//264;
	        GettingJob[playerid] = 0;
	        PlayerInfo[playerid][pMats] = 0;//обнуляем кол-во материалов при смене работы
			TogglePlayerControllableEx(playerid, 1);
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				if(i == playerid) continue;
				if(PlayerInfo[i][pMember] != DoJ) continue;
				if(PlayerInfo[i][pRank] != 2) continue;
				GivePlayerMoneyB(ffamily+PlayerInfo[i][pMember], i, DutyFiveMinuts*PlayerInfo[i][pRank]);//перечислить игроку зарплату
				IncreaseRank(i, 1);
				//format(strtmp, sizeof(strtmp), "Bам перечислено {33AA33}$%d{339966} за трудоустройство !", DutyFiveMinuts*PlayerInfo[i][pRank]);
				//SendClientMessage(i, COLOR_EMERALD, strtmp);
	        }
	    }
	    else
	    {
	        SendClientMessage(playerid, COLOR_GREY, "   Вы Не получили предложения на эту Работу ! Возможно, принятие документов закончено!");
			TogglePlayerControllableEx(playerid, 1);
	    }
	}
	else
	{
		GettingJob[playerid] = 0;
		if(PlayerInfo[playerid][pLocal] == 241) JobMenu(playerid);
		else Job2Menu(playerid);
	}
	return 1;
}


stock Job2Menu(playerid)
{
	new listitems[337];
	strcat(listitems, "\nМеню вакансий\
\n*\t Адвокат\
\n*\t Наркодилер\
\n*\t Автоугонщик\
\n*\t Оружейник\
\nОружейная");
	ShowPlayerDialogEx(playerid, JOB2MENU_DIALOG, DIALOG_STYLE_LIST, "Список криминальных работ", listitems, "Ок", "Отмена");
}

stock Job2Menu_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if(dialogid != JOB2MENU_DIALOG) return 1;
	
	if(!response) return 1;

	switch(listitem)
	{
		case 0:
		{
			GangsVacancies(playerid);
			return 1;
		}
		case 1://2 Lawyer Registration
		{
			//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Lawyer~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
		    if(PlayerInfo[playerid][pJob] > 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
				JobMenu(playerid);
				return 1;
			}
			else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
				JobMenu(playerid);
				return 1;
			}
		    /*else if(PlayerInfo[playerid][pContractTime] == getdate())
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы сегодня не можете устроиться на работу! Приходите завтра!");
				JobMenu(playerid);
			}*/
			else if(PlayerInfo[playerid][pLevel] < 5)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Устроиться на эту работу могут игроки не ниже 5 уровня.");
				JobMenu(playerid);
				return 1;
			}
		    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
				JobMenu(playerid);
				return 1;
			}
			else if(PlayerInfo[playerid][pMember] >= DoT && PlayerInfo[playerid][pMember] != LCN && PlayerInfo[playerid][pMember] != Yakuza)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Стать адвокатом может только член Семьи 'La Cosa Nostra' или 'Yakuza'.");
				JobMenu(playerid);
				return 1;
			}
			else if(IsAGangs(playerid)	|| (PlayerInfo[playerid][pMember] >= DoT &&
				PlayerInfo[playerid][pMember] != LCN &&
				PlayerInfo[playerid][pMember] != Yakuza))
			{
				SendClientMessage(playerid, COLOR_GREY, "   Устроиться на эту работу может только член семьи или гражданский.");
				JobMenu(playerid);
				return 1;
			}
			else
			{
				if(StatusJob[2] == 0)
				{
					GettingJob[playerid] = 2;
					if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 17);
					else SetPlayerSkinEx(playerid, 150);
		   			//TogglePlayerControllableEx(playerid, 1);
   				}
   				else if(StatusJob[2] == 1)
   				{
					SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
					JobMenu(playerid);
					return 1;
				}
			}
		}
		case 2://4 DrugDealer Registration
		{
			//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Drugs Dealer~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
		    if(PlayerInfo[playerid][pJob] > 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
				Job2Menu(playerid);
				return 1;
			}
			else if((PlayerInfo[playerid][pMember] >= DoT &&
				PlayerInfo[playerid][pMember] != LCN && PlayerInfo[playerid][pMember] != Yakuza) )
			{//PlayerInfo[playerid][pMember] == CIVILIAN ||
				SendClientMessage(playerid, COLOR_GREY, "   Стать наркодилером может гражданский, член банды или Семьи.");
				Job2Menu(playerid);
				return 1;
			}
			else
			{
				if(StatusJob[4] == 0)
				{
					GettingJob[playerid] = 4;
					if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 29);
					else SetPlayerSkinEx(playerid, 85);
		   			//TogglePlayerControllableEx(playerid, 1);
   				}
   				else if(StatusJob[4] == 1)
   				{
					SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
					Job2Menu(playerid);
					return 1;
				}
   			}
		}
		case 3://5 CarJacker Registration
		{
			//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Car Jacker~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
		    if(PlayerInfo[playerid][pJob] > 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
				Job2Menu(playerid);
				return 1;
			}
			else if(PlayerInfo[playerid][pLevel] < 3)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Для устроиться на эту работу необходим уровень 3.");
				Job2Menu(playerid);
				return 1;
			}
			else if((PlayerInfo[playerid][pMember] >= DoT &&
				PlayerInfo[playerid][pMember] != LCN && PlayerInfo[playerid][pMember] != Yakuza) )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Стать автоугонщиком может гражданский, член банды или Семьи.");
				Job2Menu(playerid);
				return 1;
			}
			else
			{
				if(StatusJob[5] == 0)
				{
					GettingJob[playerid] = 5;
					if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 28);
					else SetPlayerSkinEx(playerid, 40);
		   			//TogglePlayerControllableEx(playerid, 1);
   				}
   				else if(StatusJob[5] == 1)
   				{
					SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
					Job2Menu(playerid);
					return 1;
				}
			}
		}
		case 4://9 ArmsDealer Registration
		{
			//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Arms Dealer~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
		    if(PlayerInfo[playerid][pJob] > 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
				Job2Menu(playerid);
				return 1;
			}
			else if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без лицензии на оружие !");
				Job2Menu(playerid);
				return 1;
			}
			else if((PlayerInfo[playerid][pMember] >= DoT &&
				PlayerInfo[playerid][pMember] != LCN && PlayerInfo[playerid][pMember] != Yakuza) )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Стать оружейником может гражданский, член банды или Семьи.");
				Job2Menu(playerid);
				return 1;
			}
			else
			{
				if(StatusJob[9] == 0)
				{
					GettingJob[playerid] = 9;
					if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 249);
					else SetPlayerSkinEx(playerid, 192);
		   			//TogglePlayerControllableEx(playerid, 1);
   				}
   				else if(StatusJob[9] == 1)
   				{
					SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
					Job2Menu(playerid);
					return 1;
				}
	   		}
		}
		case 5://ОРУЖЕЙНАЯ
		{
			if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на оружие!");
				return 1;
			}
			if(GetPlayerMoneyH(playerid) <= 500) return SendClientMessage(playerid, COLOR_GREY, "   У Вас не достаточно денег !!!");
			TogglePlayerControllableEx(playerid, 0);//обездвиживает
			ShowMenuForPlayerEx(mAmmuNation, playerid);
			return 1;
		}
		/*case 5://БАР
		{
			//if(PlayerDrunk[playerid] < 50)
			if(GetPlayerDrunkLevel(playerid) < 50000)
			{   //если ты ещё не достаточно пьян
				new location = GetBizLocation(playerid);
			    if(BizInfo[location-100][bProducts] <= 0 && !gTutorial[playerid] && !gRealWar) {
			    	PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Bar", 5000, 1);
				}
		   		if(GetPlayerMoneyH(playerid) < 10) return SendClientMessage(playerid, COLOR_GREY, "   У Вас не достаточно денег !!!");
		 		TogglePlayerControllableEx(playerid, 0);//обездвиживает
				ShowMenuForPlayerEx(mBar, playerid);
			}
			else return SendClientMessage(playerid, COLOR_GREY, "   Вы не можете выпить больше !");
			return 1;
		}*/
	}//end switch
	JobManual(playerid, JOB_DIALOG, DIALOG_STYLE_MSGBOX, "Accept", "Cancel", GettingJob[playerid]);
	return 1;
}



stock jobs_OnPlayerExitedMenu(playerid, Menu:Current)
{
	if(Current == mJobMenu10_19)//для устройства на работу
	{
		HideMenuForPlayerEx(Current,playerid);
		ShowMenuForPlayerEx(mJobMenu1_9,playerid);//то установить основное меню
	}
	else if(Current == mJobMenu1_9)
	{
		HideMenuForPlayerEx(Current, playerid);
		if(!IsAGangs(playerid) && !IsAFamilyMember(playerid))
		{//if(PlayerInfo[playerid][pMember] == 0)
			if(	PlayerInfo[playerid][pChar] > 0 && PlayerInfo[playerid][pChar] != SKIN_DEFAULT
				&& gOnDuty[playerid] == 1)
			{
				SetPlayerSkinEx(playerid, PlayerInfo[playerid][pChar]);
			}
			else
			{//если вступили в ряды ФБР, то скин вернуть граждаский, чтобы форму получил как положено на майке
				SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
			}
		}
		TogglePlayerControllableEx(playerid, 1);
	}
}


stock jobs_OnPlayerSelectedMenuRow(playerid, row, Menu:Current)
{
	//new Menu:Current = GetPlayerMenu(playerid);//получить ID меню
	//--------------------------------------------------------------------------
	//для устройства на работу начало
	if(Current == mJobMenu1_9)
	{
		//new bigmsgitem[1878+151+95];
		switch(row)
		{
			/*case 0://1 Detective Registration
			{
   				if(StatusJob[1] == 0)
   				{
					SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу не производится в Мэрии.");
					//SendClientMessage(playerid, COLOR_GREY, "   Поиск игроков доступен ФБР, Мин.Юстиции и Киллерам.");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Detective~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
			    if(PlayerInfo[playerid][pJob] > 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
			    else if(PlayerInfo[playerid][pLevel] < 3)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы недостаточно опытны, чтобы устроиться на эту Работу.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
			    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else if(IsAGangs(playerid)	||	(PlayerInfo[playerid][pMember] >= DoT &&
						PlayerInfo[playerid][pMember] != FBI && PlayerInfo[playerid][pMember] != DoD &&
						PlayerInfo[playerid][pMember] != Hitman) )
				{
					//SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на эту работу, находясь во фракции или в банде.");
					SendClientMessage(playerid, COLOR_GREY, "   Устроиться на эту работу может только агент ФБР / НГ / Киллер или гражданский.");
					//SendClientMessage(playerid, COLOR_GREY, "   Устроиться на эту работу может только агент ФБР / Киллер или гражданский.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else
				{
					if(StatusJob[1] == 0)
					{
						SetPVarInt(playerid, "gJob", 1);
						if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 156);
						else SetPlayerSkinEx(playerid, 211);
		   				//TogglePlayerControllableEx(playerid, 1);
	   				}
	   				else if(StatusJob[1] == 1)
	   				{
						SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
						ShowMenuForPlayerEx(mJobMenu1_9, playerid);
						return 1;
					}
	   			}
			}*/
			case 0://2 Lawyer Registration
			{
				//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Lawyer~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
			    if(PlayerInfo[playerid][pJob] > 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
			    /*else if(PlayerInfo[playerid][pContractTime] == getdate())
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы сегодня не можете устроиться на работу! Приходите завтра!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
				}*/
				else if(PlayerInfo[playerid][pLevel] < 5)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Устроиться на эту работу могут игроки не ниже 5 уровня.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
			    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else if(PlayerInfo[playerid][pMember] >= DoT && PlayerInfo[playerid][pMember] != LCN && PlayerInfo[playerid][pMember] != Yakuza)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Стать адвокатом может только член Семьи 'La Cosa Nostra' или 'Yakuza'.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else if(IsAGangs(playerid)	|| (PlayerInfo[playerid][pMember] >= DoT &&
					PlayerInfo[playerid][pMember] != LCN &&
					PlayerInfo[playerid][pMember] != Yakuza))
				{
					SendClientMessage(playerid, COLOR_GREY, "   Устроиться на эту работу может только член семьи или гражданский.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else
				{
					if(StatusJob[2] == 0)
					{
						GettingJob[playerid] = 2;
						if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 17);
						else SetPlayerSkinEx(playerid, 150);
			   			//TogglePlayerControllableEx(playerid, 1);
	   				}
	   				else if(StatusJob[2] == 1)
	   				{
						SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
						ShowMenuForPlayerEx(mJobMenu1_9, playerid);
						return 1;
					}
				}
			}
			case 1://3 RoadWorker Registration
			{
				//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~RoadWorker~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
			    if(PlayerInfo[playerid][pJob] > 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У Вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
			    /*else if(PlayerInfo[playerid][pContractTime] == getdate())
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы сегодня не можете устроиться на работу! Приходите завтра!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
				}*/
			    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else if(IsAGangs(playerid) || PlayerInfo[playerid][pMember] >= DoT)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на эту работу, находясь во фракции или в банде.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
	    		else if(VehInfo[MyCar[playerid][0]][cModel] != 552 && VehInfo[MyCar[playerid][1]][cModel] != 552 && VehInfo[MyCar[playerid][2]][cModel] != 552 &&
						GetPlayerMoneyH(playerid) < VehicleArray[552-400][Virtual_Price] && PlayerInfo[playerid][pBank] < VehicleArray[552-400][Virtual_Price])
				{
					format(strings, sizeof(strings), "   У вас нет $%d для покупки служебного авто !",VehicleArray[552-400][Virtual_Price]);
					SendClientMessage(playerid, COLOR_GREY, strings);
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else
				{
					if(StatusJob[3] == 0)
					{
						GettingJob[playerid] = 3;
						SetPlayerSkinEx(playerid, 260);
						if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 260);
						else SetPlayerSkinEx(playerid, 64);
			   			//TogglePlayerControllableEx(playerid, 1);
	   				}
	   				else if(StatusJob[3] == 1)
	   				{
						SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
						ShowMenuForPlayerEx(mJobMenu1_9, playerid);
						return 1;
					}
		   		}
			}
			case 2://4 DrugDealer Registration
			{
				//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Drugs Dealer~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
			    if(PlayerInfo[playerid][pJob] > 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
			    /*else if(PlayerInfo[playerid][pContractTime] == getdate())
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы сегодня не можете устроиться на работу! Приходите завтра!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
				}*/
			    /*else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
				}*/
				else if((PlayerInfo[playerid][pMember] >= DoT &&
					PlayerInfo[playerid][pMember] != LCN && PlayerInfo[playerid][pMember] != Yakuza) )
				{//PlayerInfo[playerid][pMember] == CIVILIAN ||
					SendClientMessage(playerid, COLOR_GREY, "   Стать наркодилером может гражданский, член банды или Семьи.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else
				{
					if(StatusJob[4] == 0)
					{
						GettingJob[playerid] = 4;
						if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 29);
						else SetPlayerSkinEx(playerid, 85);
			   			//TogglePlayerControllableEx(playerid, 1);
	   				}
	   				else if(StatusJob[4] == 1)
	   				{
						SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
						ShowMenuForPlayerEx(mJobMenu1_9, playerid);
						return 1;
					}
	   			}
			}
			case 3://5 CarJacker Registration
			{
				//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Car Jacker~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
			    if(PlayerInfo[playerid][pJob] > 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else if(PlayerInfo[playerid][pLevel] < 3)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Для устроиться на эту работу необходим уровень 3.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
			    /*else if(PlayerInfo[playerid][pContractTime] == getdate())
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы сегодня не можете устроиться на работу! Приходите завтра!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
				}*/
			    /*else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
				}*/
				else if(PlayerInfo[playerid][pMember] > 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на эту работу, находясь во фракции или в банде.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else
				{
					if(StatusJob[5] == 0)
					{
						GettingJob[playerid] = 5;
						if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 28);
						else SetPlayerSkinEx(playerid, 40);
			   			//TogglePlayerControllableEx(playerid, 1);
	   				}
	   				else if(StatusJob[5] == 1)
	   				{
						SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
						ShowMenuForPlayerEx(mJobMenu1_9, playerid);
						return 1;
					}
				}
			}
			case 4://6 AutoBuyer
			{//для скупщиков
			    if(PlayerInfo[playerid][pJob] > 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
			    /*else if(PlayerInfo[playerid][pContractTime] == getdate())
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы сегодня не можете устроиться на работу! Приходите завтра!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
				}*/
			    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else if(IsAGangs(playerid) || PlayerInfo[playerid][pMember] >= DoT)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на эту работу, находясь во фракции или в банде.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
			    else if(GetPlayerMoneyH(playerid) < 120000)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас нет начального капитала в $120000 для покупки паркинга и лицензии на него.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else
				{
					if(StatusJob[6] == 0)
					{
						GettingJob[playerid] = 6;
						if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 72);
						else SetPlayerSkinEx(playerid, 69);
			   			//TogglePlayerControllableEx(playerid, 1);
	   				}
	   				else if(StatusJob[6] == 1)
	   				{
						SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
						ShowMenuForPlayerEx(mJobMenu1_9, playerid);
						return 1;
					}
				}
			}
			case 5://7 CarMechanic Registration
			{
				//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Car Mechanic~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
			    if(PlayerInfo[playerid][pJob] > 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
			    /*else if(PlayerInfo[playerid][pContractTime] == getdate())
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы сегодня не можете устроиться на работу! Приходите завтра!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
				}*/
			    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else if(IsAGangs(playerid) || PlayerInfo[playerid][pMember] >= DoT)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на эту работу, находясь во фракции или в банде.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
    			else if(VehInfo[MyCar[playerid][0]][cModel] != 525 && VehInfo[MyCar[playerid][1]][cModel] != 525 && VehInfo[MyCar[playerid][2]][cModel] != 525 &&
					GetPlayerMoneyH(playerid) < VehicleArray[525-400][Virtual_Price] &&
					PlayerInfo[playerid][pBank] < VehicleArray[525-400][Virtual_Price])
				{
					format(strings, sizeof(strings), "   У вас нет $%d для покупки служебного авто !",VehicleArray[525-400][Virtual_Price]);
					SendClientMessage(playerid, COLOR_GREY, strings);
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else
				{
					if(StatusJob[7] == 0)
					{
						GettingJob[playerid] = 7;
						if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 50);
						else SetPlayerSkinEx(playerid, 157);
			   			//TogglePlayerControllableEx(playerid, 1);
	   				}
	   				else if(StatusJob[7] == 1)
	   				{
						SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
						ShowMenuForPlayerEx(mJobMenu1_9, playerid);
						return 1;
					}
				}
			}
			/*case 6://8 Farmer Registration
			{
   				if(StatusJob[8] == 0)
   				{
					SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу больше не производится.");
					SendClientMessage(playerid, COLOR_GREY, "   Вы можете взять эту работу на ферме.");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
			    if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pLevel] > 3)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
			    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 3)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else if(IsAGangs(playerid) || PlayerInfo[playerid][pMember] >= DoT)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Стать фермером могут только гражданские.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else
				{
					if(StatusJob[8] == 0 || PlayerInfo[playerid][pLevel] == 1 || PlayerInfo[playerid][pLevel] == 2)
					{
						GettingJob[playerid] = 8;
						//if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 16);
						//else SetPlayerSkinEx(playerid, 64);
	   				}
	   				else if(StatusJob[8] == 1)
	   				{
						SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
						ShowMenuForPlayerEx(mJobMenu1_9, playerid);
						return 1;
					}
				}
			}*/
			case 6://9 ArmsDealer Registration
			{
				//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Arms Dealer~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
			    if(PlayerInfo[playerid][pJob] > 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без лицензии на оружие !");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
			    /*else if(PlayerInfo[playerid][pContractTime] == getdate())
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы сегодня не можете устроиться на работу! Приходите завтра!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
				}*/
			    /*else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
				}*/
				else if(PlayerInfo[playerid][pMember] >= DoT && PlayerInfo[playerid][pMember] != LCN && PlayerInfo[playerid][pMember] != Yakuza)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Стать оружейником может гражданский, член банды или Семьи.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
				else
				{
					if(StatusJob[9] == 0)
					{
						GettingJob[playerid] = 9;
						if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 249);
						else SetPlayerSkinEx(playerid, 192);
			   			//TogglePlayerControllableEx(playerid, 1);
	   				}
	   				else if(StatusJob[9] == 1)
	   				{
						SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
						ShowMenuForPlayerEx(mJobMenu1_9, playerid);
						return 1;
					}
		   		}
			}
			case 7://10 Others
			{
				HideMenuForPlayerEx(mJobMenu1_9, playerid);
				ShowMenuForPlayerEx(mJobMenu10_19, playerid);
				return 1;
			}
			case 8://11 mGangsVacancies
			{
				HideMenuForPlayerEx(mJobMenu1_9, playerid);
				ShowMenuForPlayerEx(mGangsVacancies, playerid);
				return 1;
			}
			case 9://12 mVacancies
			{
				if(PlayerInfo[playerid][pRespect] < 14)
				{//т.е. надо пройти обучение там даётся 14 очков
					SendClientMessage(playerid, COLOR_GREY, "   У вас недостаточно очков уважения! Пройдите обучение (USE: /tut)");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
				}
				else
				{
					HideMenuForPlayerEx(mJobMenu1_9, playerid);
					ShowMenuForPlayerEx(mVacancies, playerid);
				}
				return 1;
			}

		}//end switch
		JobManual(playerid, JOB_DIALOG, DIALOG_STYLE_MSGBOX, "Accept", "Cancel", GettingJob[playerid]);
	}
	//для устройства на работу
	else if(Current == mJobMenu10_19)
	{
		//new bigmsgitem[2366];
		switch(row)
		{
			case 0://10 CarDealer Registration
			{
				//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Car Dealer~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
			    if(PlayerInfo[playerid][pJob] > 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
			    else if(PlayerInfo[playerid][pLevel] < 4)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Ваш уровень ниже 4!");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
				}
			    else if(PlayerInfo[playerid][pBank] < 60000 && GetPlayerMoneyH(playerid) < 60000)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас нету $60000 на счету!");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
				}
			    /*else if(PlayerInfo[playerid][pContractTime] == getdate())
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы сегодня не можете устроиться на работу! Приходите завтра!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
				}*/
			    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				else if(IsAGangs(playerid) || PlayerInfo[playerid][pMember] >= DoT)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на эту работу, находясь во фракции или в банде.");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
	    		else if(GetPlayerMoneyH(playerid) < VehicleArray[604-400][Virtual_Price] && PlayerInfo[playerid][pBank] < VehicleArray[604-400][Virtual_Price])
				{
					format(strings, sizeof(strings), "   У вас нет даже $%d для продажи самой дешёвой авто !", VehicleArray[604-400][Virtual_Price]);
					SendClientMessage(playerid, COLOR_GREY, strings);
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				else
				{
					if(StatusJob[10] == 0)
					{
						GettingJob[playerid] = 10;
						if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 15);
						else SetPlayerSkinEx(playerid, 148);
			   			//TogglePlayerControllableEx(playerid, 1);
	   				}
	   				else if(StatusJob[10] == 1)
	   				{
						SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
						ShowMenuForPlayerEx(mJobMenu10_19, playerid);
						return 1;
					}
				}
			}
			case 1://11 Inkassator Registration
			{
				//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Inkassator~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
			    if(PlayerInfo[playerid][pJob] > 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
			    /*else if(PlayerInfo[playerid][pContractTime] == getdate())
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы сегодня не можете устроиться на работу! Приходите завтра!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
				}*/
			    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				/*else if(PlayerInfo[playerid][pLevel] < 2)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть как минимум второго уровня, чтобы устроиться инкассатором.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
				}*/
	    		else if(VehInfo[MyCar[playerid][0]][cModel] != 428 && VehInfo[MyCar[playerid][1]][cModel] != 428 && VehInfo[MyCar[playerid][2]][cModel] != 428 &&
					GetPlayerMoneyH(playerid) < VehicleArray[428-400][Virtual_Price] && PlayerInfo[playerid][pBank] < VehicleArray[428-400][Virtual_Price])
				{
					format(strings, sizeof(strings), "   У вас нет $%d для покупки служебного авто !",VehicleArray[428-400][Virtual_Price]);
					SendClientMessage(playerid, COLOR_GREY, strings);
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				else if(IsAGangs(playerid) || PlayerInfo[playerid][pMember] >= DoT)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на эту работу, находясь во фракции или в банде.");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				else
				{
					if(StatusJob[11] == 0)
					{
						GettingJob[playerid] = 11;
						if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 71);
						else SetPlayerSkinEx(playerid, 194);
			   			//TogglePlayerControllableEx(playerid, 1);
	   				}
	   				else if(StatusJob[11] == 1)
	   				{
						SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
						ShowMenuForPlayerEx(mJobMenu10_19, playerid);
						return 1;
					}
		   		}
			}
			/*case 2://12 Bookmaker Registration
			{
   				if(StatusJob[12] == 0)
   				{
					SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу больше не производится.");
					SendClientMessage(playerid, COLOR_GREY, "   Вы можете взять эту работу в любом тренажёрном зале.");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Bookmaker~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
			    if(PlayerInfo[playerid][pJob] > 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
			    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				else
				{
					if(StatusJob[12] == 0)
					{
						GettingJob[playerid] = 12;
	   				}
	   				else if(StatusJob[12] == 1)
	   				{
						SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
						ShowMenuForPlayerEx(mJobMenu10_19, playerid);
						return 1;
					}
		   		}
			}*/
			case 2://для таксистов 13 TaxiDriver
			{
				//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~TaxiDriver~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
			    if(PlayerInfo[playerid][pJob] > 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
			    /*else if(PlayerInfo[playerid][pContractTime] == getdate())
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы сегодня не можете устроиться на работу! Приходите завтра!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
				}*/
			    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				else if(IsAGangs(playerid) || PlayerInfo[playerid][pMember] >= DoT)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на эту работу, находясь во фракции или в банде.");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
	    		else if(VehInfo[MyCar[playerid][0]][cModel] != 438 && VehInfo[MyCar[playerid][1]][cModel] != 438 && VehInfo[MyCar[playerid][2]][cModel] != 438 &&
					GetPlayerMoneyH(playerid) < VehicleArray[438-400][Virtual_Price] && PlayerInfo[playerid][pBank] < VehicleArray[438-400][Virtual_Price])
				{
					format(strings, sizeof(strings), "   У вас нет $%d для покупки служебного авто !",VehicleArray[438-400][Virtual_Price]);
					SendClientMessage(playerid, COLOR_GREY, strings);
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				else
				{
					if(StatusJob[13] == 0)
					{
						GettingJob[playerid] = 13;
						if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 61);
						else SetPlayerSkinEx(playerid, 172);
			   			//TogglePlayerControllableEx(playerid, 1);
	   				}
	   				else if(StatusJob[13] == 1)
	   				{
						SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
						ShowMenuForPlayerEx(mJobMenu10_19, playerid);
						return 1;
					}
		   		}
			}
			case 3://14 BusDriver Registration
			{
				//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Bus Driver~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
			    if(PlayerInfo[playerid][pJob] > 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
					return 1;
				}
			    /*else if(PlayerInfo[playerid][pContractTime] == getdate())
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы сегодня не можете устроиться на работу! Приходите завтра!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
				}*/
			    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				else if(IsAGangs(playerid) || (PlayerInfo[playerid][pMember] >= DoT && PlayerInfo[playerid][pMember] != DoE) )
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на эту работу, находясь во фракции (кроме МоЕ) или в банде.");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
	    		else if(VehInfo[MyCar[playerid][0]][cModel] != 431 && VehInfo[MyCar[playerid][1]][cModel] != 431 && VehInfo[MyCar[playerid][2]][cModel] != 431 &&
					GetPlayerMoneyH(playerid) < VehicleArray[431-400][Virtual_Price] && PlayerInfo[playerid][pBank] < VehicleArray[431-400][Virtual_Price])
				{
					format(strings, sizeof(strings), "   У вас нет $%d для покупки служебного авто !",VehicleArray[431-400][Virtual_Price]);
					SendClientMessage(playerid, COLOR_GREY, strings);
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				else
				{
					if(StatusJob[14] == 0)
					{
						GettingJob[playerid] = 14;
						if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 255);
						else SetPlayerSkinEx(playerid, 93);
			   			//TogglePlayerControllableEx(playerid, 1);
	   				}
	   				else if(StatusJob[14] == 1)
	   				{
						SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
						ShowMenuForPlayerEx(mJobMenu10_19, playerid);
						return 1;
					}
		   		}
			}
			case 4://15 PaperBoy Registration
			{	//для курьеров
				//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Paperboy~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
			    if(PlayerInfo[playerid][pJob] > 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
			    /*else if(PlayerInfo[playerid][pContractTime] == getdate())
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы сегодня не можете устроиться на работу! Приходите завтра!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
				}*/
			    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				else if( IsAGangs(playerid)	|| (PlayerInfo[playerid][pMember] >= DoT &&
						PlayerInfo[playerid][pMember] != SAN) )
				{
					SendClientMessage(playerid, COLOR_GREY, "   Стать курьером могут только репортёры или гражданские.");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				/*else if(PlayerInfo[playerid][pLevel] > 3 && PlayerInfo[playerid][pMember] != SAN)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете стать курьером, т.к. ваш уровень выше третьего.");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
				}*/
				else
				{
					if(StatusJob[15] == 0)
					{
						GettingJob[playerid] = 15;
						if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 188);
						else SetPlayerSkinEx(playerid, 193);
			   			//TogglePlayerControllableEx(playerid, 1);
	   				}
	   				else if(StatusJob[15] == 1)
	   				{
						SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
						ShowMenuForPlayerEx(mJobMenu10_19, playerid);
						return 1;
					}
				}
			}
			case 5://16 Trucker Registration
			{
				//GameTextForPlayerEx(playerid, "~g~Welcome,~n~~y~you can become a ~r~Trucker~y~ here ~n~~w~Type /accept job if you wish to become one", 5000, 3);
			    if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pLevel] > 3)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
			    /*else if(PlayerInfo[playerid][pContractTime] == getdate())
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы сегодня не можете устроиться на работу! Приходите завтра!");
					ShowMenuForPlayerEx(mJobMenu1_9, playerid);
				}*/
			    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 3 && !gTutorial[playerid])
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				/*else if(IsAGangs(playerid) || PlayerInfo[playerid][pMember] >= DoT)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на эту работу, находясь во фракции или в банде.");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}*/
		    	/*else if(PlayerInfo[playerid][pLevel] > 2 &&
		    		!IsInHardTruck(MyCar[playerid][0]) &&
		    		!IsInHardTruck(MyCar[playerid][1]) &&
		    		!IsInHardTruck(MyCar[playerid][2]) &&
					GetPlayerMoneyH(playerid) < VehicleArray[403-400][Virtual_Price] &&
					PlayerInfo[playerid][pBank] < VehicleArray[403-400][Virtual_Price])
				{
					format(strings, sizeof(strings), "   У вас нет $%d для покупки самого дешёвого тягача %s!", VehicleArray[403-400][Virtual_Price], VehicleArray[403-400][Vehicle_Name]);
					SendClientMessage(playerid, COLOR_GREY, strings);
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}*/
				else
				{
					if(StatusJob[16] == 0 || PlayerInfo[playerid][pLevel] == 1 || PlayerInfo[playerid][pLevel] == 2)
					{
						GettingJob[playerid] = 16;
						if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 133);
						else SetPlayerSkinEx(playerid, 204);
			   			//TogglePlayerControllableEx(playerid, 1);
	   				}
	   				else if(StatusJob[16] == 1)
	   				{
						SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
						ShowMenuForPlayerEx(mJobMenu10_19, playerid);
						return 1;
					}
		   		}
			}
			//для мусорщиков
			case 6://17 Trashman Registration
			{
			    if(PlayerInfo[playerid][pJob] > 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   У вас уже есть Работа (USE: /quitjob, чтобы уйти с работы)!");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				else if(WantedLevel[playerid] > 0 && PlayerInfo[playerid][pLevel] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть Не в Розыске, чтобы получить Работу !");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
			    /*else if(PlayerInfo[playerid][pContractTime] == getdate())
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы сегодня не можете устроиться на работу! Приходите завтра!");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
				}*/
			    else if(PlayerInfo[playerid][pSTD] != IsNotBeenIll && PlayerInfo[playerid][pLevel] > 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете устроиться на работу без мед. осмотра в больнице.");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				else if(IsAGangs(playerid) || PlayerInfo[playerid][pMember] >= DoT)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Стать Водителем Мусоровоза могут только гражданские.");
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
		    	else if(VehInfo[MyCar[playerid][0]][cModel] != 408 && VehInfo[MyCar[playerid][1]][cModel] != 408 && VehInfo[MyCar[playerid][2]][cModel] != 408 &&
					GetPlayerMoneyH(playerid) < VehicleArray[408-400][Virtual_Price] && PlayerInfo[playerid][pBank] < VehicleArray[408-400][Virtual_Price])
				{
					format(strings, sizeof(strings), "   У вас нет $%d для покупки служебного авто !",VehicleArray[408-400][Virtual_Price]);
					SendClientMessage(playerid, COLOR_GREY, strings);
					ShowMenuForPlayerEx(mJobMenu10_19, playerid);
					return 1;
				}
				else
				{
					if(StatusJob[17] == 0)
					{
						GettingJob[playerid] = 17;
						if(PlayerInfo[playerid][pSex] == 1) SetPlayerSkinEx(playerid, 128);
						else SetPlayerSkinEx(playerid, 64);
	   				}
	   				else if(StatusJob[17] == 1)
	   				{
						SendClientMessage(playerid, COLOR_GREY, "   Трудоустройство на эту работу временно не производится.");
						ShowMenuForPlayerEx(mJobMenu10_19, playerid);
						return 1;
					}
				}
			}
		}//end switch
/*
		strcat(bigmsgitem, "* Чтобы увидеть команды наберите /jobhelp. Наберите /question если есть вопросы. Хорошей игры.\n\n");
		strcat(bigmsgitem, "* Вы собираетесь устроиться на эту работу и получить 2-часовой Контракт.\n");
		strcat(bigmsgitem, "* Вы должны будете отработать эти 2 часа, чтобы получить возможность уволиться и сменить работу.\n");
		strcat(bigmsgitem, "* Если вы уверены в своём решении, нажмите Accept.\n");
*/
		//ShowPlayerDialogGap(playerid, 22, DIALOG_STYLE_MSGBOX, "Работодатель", bigmsgitem, "Accept", "Cancel");
		JobManual(playerid, JOB_DIALOG, DIALOG_STYLE_MSGBOX, "Accept", "Cancel", GettingJob[playerid]);
	}//для устройства на работу конец
	return 1;
}



stock GetPlayerJob(playerid)
{
	new jtext[20];
	if(PlayerInfo[playerid][pJob] == MINER)  { jtext = "Шахтёр"; }
	else if(PlayerInfo[playerid][pJob] == LAWYER) { jtext = "Адвокат"; }//Lawyer
	else if(PlayerInfo[playerid][pJob] == ROADWORKER) { jtext = "Ремонтник Дорог"; }//RoadWorker
	else if(PlayerInfo[playerid][pJob] == DRUGDEALER) { jtext = "Наркодилер"; }//DrugDealer
	else if(PlayerInfo[playerid][pJob] == CARJACKER) { jtext = "Автоугонщик"; }//CarJacker
	else if(PlayerInfo[playerid][pJob] == AUTOBUYER) { jtext = "Скупщик Авто"; }
	else if(PlayerInfo[playerid][pJob] == CARMECHANIC) { jtext = "АвтоМеханик"; }//CarMechanic
	else if(PlayerInfo[playerid][pJob] == FARMER) { jtext = "Фермер"; }
	else if(PlayerInfo[playerid][pJob] == ARMSDEALER) { jtext = "Оружейник"; }//ArmsDealer
	else if(PlayerInfo[playerid][pJob] == CARDEALER) { jtext = "Автодилер"; }//CarDealer
	else if(PlayerInfo[playerid][pJob] == INKASSATOR) { jtext = "Инкассатор"; }//Inkassator
	else if(PlayerInfo[playerid][pJob] == BOOKMAKER) { jtext = "Букмекер"; }//Bookmaker
	else if(PlayerInfo[playerid][pJob] == TAXIDRIVER) { jtext = "Таксист"; }//Taxi
	else if(PlayerInfo[playerid][pJob] == BUSDRIVER) { jtext = "Водитель автобуса"; }//BusDriver
	else if(PlayerInfo[playerid][pJob] == PAPERBOY) { jtext = "Курьер"; }//для курьеров PaperBoy
	else if(PlayerInfo[playerid][pJob] == TRUCKER) { jtext = "Дальнобойщик"; }//Trucker
	else if(PlayerInfo[playerid][pJob] == TRASHMAN) { jtext = "Мусоровоз"; }
	else if(PlayerInfo[playerid][pJob] == LOADER)  { jtext = "Грузчик"; }//Loader
	else if(PlayerInfo[playerid][pJob] == WOODSMAN)  { jtext = "Дровосек"; }
	else if(PlayerInfo[playerid][pJob] == FISHER)  { jtext = "Рыбалов"; }
	else if(PlayerInfo[playerid][pJob] == FIREMAN)  { jtext = "Пожарный"; }
	else if(PlayerInfo[playerid][pJob] == COOKER)  { jtext = "Повар"; }
	else { jtext = "Отсутствует"; }
	return jtext;
}

stock QuitJob(playerid)
{
	FixJobCounter(playerid);
	PlayerInfo[playerid][pCarTime] = 0;
    PlayerInfo[playerid][pJob] = 0;  gJobDuty[playerid] = 0;
    PlayerInfo[playerid][pContractTime] = 0;//getdate();
	PlayerInfo[playerid][pMats] = 0;//обнуляем кол-во материалов при смене работы
	DisablePlayerCheckpointEx(playerid);
	JobAmmount[playerid] = 0;
	SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
}

stock FixJobCounter(playerid)
{   //вызывается в if(newstate == PLAYER_STATE_WASTED) --> OnPlayerStateChange для всех кто на дежурстве
//FermaEnd(playerid)
//OnPlayerDisconnect
	if(gJobDuty[playerid] != 1) return 1;

	if(PlayerInfo[playerid][pJob] == MINER)
	{
	    if(IsPlayerAttachedObjectSlotUsed(playerid, DUTY_SLOT)) RemovePlayerAttachedObject(playerid, DUTY_SLOT);
	    if(IsPlayerAttachedObjectSlotUsed(playerid, BAG_SLOT)) RemovePlayerAttachedObject(playerid, BAG_SLOT);

		if(gJobDuty[playerid]) SBizInfo[55][sbWorker] --;
        SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы окончили работу шахтёра.");
	}
	else if(PlayerInfo[playerid][pJob] == ROADWORKER)//для ремонтников
	{
		for(new ir=0; ir<MAX_RADARS; ir++)
		{
			if(RepairRoadPlayerID[ir] == playerid)
			{
				new bridge[20];
				//new strtmp[MAX_STRING];
				DestroyObjectEx(pRoadblock[ir], 20);
				RepairRoadPlayerID[ir] = MAX_PLAYERS-1;
				strmid(bridge, aRadar[ir][radName], 0, strlen(aRadar[ir][radName]), sizeof(bridge));
				//new strtmp[21+20];
				//format(strtmp, sizeof(strtmp), "Мост {FFFFFF}%s{33AA33} свободен !!!", bridge);
				format(PagerMessage, sizeof(PagerMessage), "Мост %s свободен !!!", bridge);
				for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
					RemovePlayerMapIcon(i, MAX_PLAYER_ICONS-ir);
					//SendClientMessage(i, COLOR_GREEN, strtmp);
					//PlayerTextDrawSetStringEx(i, txdPager[i], RusToGame(strtmp));
					//PlayAudioStreamForPlayerEx(i, "pager.wav");
					SendPagerMessage(playerid);
				}
				//JobNews(COLOR_GREEN,strings);
				break;
			}
		}
	}
	else if(PlayerInfo[playerid][pJob] == AUTOBUYER)//для скупщиков
	{
		if(gJobDuty[playerid]) AutoBuyerCounter --;
#if defined vw_sql//#endif
		//для владения несколькими бизами
		new sbouse = -1;
		new ToBase[44+24];
		format(ToBase, sizeof(ToBase), "SELECT `ID` FROM `sbizz` WHERE `Owned`=%d AND `ID`>%d AND `ID`<%d",
			PlayerInfo[playerid][pSQLID], PARKING, PARKING+sizeof(Parking));
		/*mysql_query(ToBase); mysql_store_result();
		if(mysql_num_rows() > 0 && mysql_retrieve_row())
	 	{
	 		new Field[20];
			mysql_fetch_field_row(Field, "ID");	sbouse = strval(Field)-1;
		}
		mysql_free_result();*/
		
		new DBResult:db_result = db_query(db_VW, ToBase);
		if(db_num_rows(db_result))
	 	{
	 		new Field[20];
			db_get_field_assoc(db_result, "ID", Field, sizeof(Field) );   sbouse = strval(Field)-1;
		}
		db_free_result(db_result);
		
#endif
		if(sbouse != -1)
		{
			OnSBizInit(sbouse);

			PlayerInfo[playerid][pBizz] = NOT_KEY;
			//OnPlayerStatsUpdate(playerid);
			format(strings, sizeof(strings), "%s has sell sbiz %d. reason: quitjob", PlayerName(playerid), sbouse);
			Log(BUY,strings);

			new text_info[19+20+24];
	    	format(text_info, sizeof(text_info), "[ %s ]", SBizInfo[sbouse][sbDiscription]);
			Update3DTextLabelEx(sbEntranceText3D[sbouse], 0xEEEE88FF, text_info);
			GameTextForPlayerEx(playerid, "~y~Congratulations~n~~w~You have sold your Parking", 10000, 3);
		}
	}
	else if(PlayerInfo[playerid][pJob] == FARMER)
	{
		if(gJobDuty[playerid]) SBizInfo[52][sbWorker] --;
		if(SBizInfo[52][sbWorker] <= 0) SBizInfo[52][sbWorker] = 0;
		if(FermaStatus == 1 || FermaStatus == 2) FarmerExitAndDeath(playerid);
		if(IsPlayerAttachedObjectSlotUsed(playerid, DUTY_SLOT)) RemovePlayerAttachedObject(playerid, DUTY_SLOT);
	}
	else if(PlayerInfo[playerid][pJob] == CARMECHANIC) MechanicsCounter --;
	else if(PlayerInfo[playerid][pJob] == BOOKMAKER)
	{
	    SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы окончили работу Букмекера.");
	}
	else if(PlayerInfo[playerid][pJob] == TAXIDRIVER)
	{
		TransportValue[playerid] = 0;//цена за проезд на такси
		TransportEarning[playerid] = 0;//полная выручка таксиста и автобуса
        if(gJobDuty[playerid]) TaxiDriversCounter -= 1;

		if(TaxiDriver[0] == playerid) TaxiDriver[0] = MAX_PLAYERS-1;
		else if(TaxiDriver[1] == playerid) TaxiDriver[1] = MAX_PLAYERS-1;
		else if(TaxiDriver[2] == playerid) TaxiDriver[2] = MAX_PLAYERS-1;
		Delete3DTextLabel(LabelOnHead[playerid]);	Counter3DText --;
	}
	else if(PlayerInfo[playerid][pJob] == WOODSMAN)
	{
       	WoodsmanLoading[playerid] = false;
       	SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
   		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы окончили работу Лесоруба!");
   		if(IsPlayerAttachedObjectSlotUsed(playerid, OBJECT_SLOT)) RemovePlayerAttachedObject(playerid, OBJECT_SLOT);
	}
	else if(PlayerInfo[playerid][pJob] == FIREMAN)//для пожарников
	{
		if(gJobDuty[playerid]) { FireCounter --; }
		if(FireCounter <= 0) { FireCounter = 0; }
       	SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
   		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы окончили работу Пожарного!");
 	}
 	BusDriverInit(playerid);
	gJobDuty[playerid] = 0;
	//DeletePVar(playerid, "dutylist");
	//strdel(dutylist[playerid], 0, sizeof(dutylist));
	return 1;
}



//==============================================================================

stock MenuVacancies(playerid)
{
	new listitems[585];
	strcat(listitems, "\n10.\t[DoT] Министерство Транспорта\
\n11.\t[FBI] Федеральное Бюро Раследований\
\n12.\t[DoD] Министерство Обороны\
\n13.\t[DoH] Министерство Здравохранения\
\n14.\t[LCN] La Cosa Nostra\
\n15.\t[Yakuza] Yakuza\
\n16.\t[DoJ] Министерство Юстиции\
\n17.\t[Hitman] Заказное Агентство\
\n18.\t[SAN] Служба Новостей\
\n19.\t[DoE] Министерство Образования\
\nУволиться из фракции");
	ShowPlayerDialogEx(playerid, VACANCIES_DIALOG, DIALOG_STYLE_LIST, "Меню вакансий", listitems, "Ок", "Отмена");
}
stock MenuVacancies_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if(dialogid != VACANCIES_DIALOG) return 1;
	
	if(!response) {  return 1; }
	switch(listitem)
	{
		case 0://1 DoT
		{
			if(PlayerInfo[playerid][pLeader] == DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
			}
			else if(//PlayerInfo[playerid][pTrashSkill] < 400 &&
					PlayerInfo[playerid][pMember] != DoT+listitem &&
					PlayerInfo[playerid][pRespect] < (OnlineRecord*200/100))
			{
				//SendClientMessage(playerid, COLOR_GREY, "   Ваш навык водителя мусоровоза меньше 400 !");
				format(strings, sizeof(strings), "   Ваше уважение %d меньше %d !", PlayerInfo[playerid][pRespect], (OnlineRecord*200/100));
				SendClientMessage(playerid, COLOR_GREY, strings);
			}
			else if(PlayerInfo[playerid][pCarLic] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует водительская лицензия !");
			}
			else if(PlayerInfo[playerid][pFlyLic] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на полёты !");
			}
			else if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на оружие !");
			}
		    else if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pMember] != DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже состоите в какой-то фракции. Для начала увольтесь (USE: /uninvite)!");
			}
		    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob)!");
			}
		    else if(PlayerInfo[playerid][pMember] == DoT+listitem && PlayerInfo[playerid][pProfSkill] < 400
				&& FamilyInfo[DoT+listitem][fMembers] > 1 )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
			}
			else
			{
				if(!strcmp(FamilyInfo[DoT+listitem][fLeader], "No-One", true))
				{//если лидер нет, т.е. имя лидера фракции равно "No-One"
					if(PlayerInfo[playerid][pMember] == DoT+listitem && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+listitem);
					else if(FamilyInfo[DoT+listitem][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+listitem); //если место лидера пусто
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
				}
			}
			MenuVacancies(playerid);
		}
		case 1://2 FBI
		{
			if(PlayerInfo[playerid][pLeader] == DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
			}
			else if(//PlayerInfo[playerid][pMinerSkill] < 400 &&
					PlayerInfo[playerid][pMember] != DoT+listitem &&
					PlayerInfo[playerid][pRespect] < (OnlineRecord*200/100))
			{
				//SendClientMessage(playerid, COLOR_GREY, "   Ваш навык шахтёра меньше 400 !");
    			format(strings, sizeof(strings), "   Ваше уважение %d меньше %d !", PlayerInfo[playerid][pRespect], (OnlineRecord*200/100));
				SendClientMessage(playerid, COLOR_GREY, strings);
			}
			else if(PlayerInfo[playerid][pCarLic] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует водительская лицензия !");
			}
			else if(PlayerInfo[playerid][pFlyLic] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на полёты !");
			}
			else if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на оружие !");
			}
		    else if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pMember] != DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже состоите в какой-то фракции. Для начала увольтесь (USE: /uninvite)!");
			}
		    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob)!");
			}
		    else if(PlayerInfo[playerid][pMember] == DoT+listitem && PlayerInfo[playerid][pProfSkill] < 400
				&& FamilyInfo[DoT+listitem][fMembers] > 1 )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
			}
			else
			{
				if(!strcmp(FamilyInfo[DoT+listitem][fLeader], "No-One", true))
				{//если лидер нет, т.е. имя лидера фракции равно "No-One"
					if(PlayerInfo[playerid][pMember] == DoT+listitem && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+listitem);
					else if(FamilyInfo[DoT+listitem][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+listitem); //если место лидера пусто
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
				}
			}
			MenuVacancies(playerid);
		}
		case 2://3 DoD
		{
			if(PlayerInfo[playerid][pLeader] == DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
			}
			else if(//PlayerInfo[playerid][pLoadSkill] < 400 &&
					PlayerInfo[playerid][pMember] != DoT+listitem &&
					PlayerInfo[playerid][pRespect] < (OnlineRecord*200/100))
			{
				//SendClientMessage(playerid, COLOR_GREY, "   Ваш навык грузчика меньше 400 !");
				format(strings, sizeof(strings), "   Ваше уважение %d меньше %d !", PlayerInfo[playerid][pRespect], (OnlineRecord*200/100));
				SendClientMessage(playerid, COLOR_GREY, strings);
			}
			else if(PlayerInfo[playerid][pCarLic] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует водительская лицензия !");
			}
			else if(PlayerInfo[playerid][pFlyLic] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на полёты !");
			}
			else if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на оружие !");
			}
		    else if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pMember] != DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже состоите в какой-то фракции. Для начала увольтесь (USE: /uninvite)!");
			}
		    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob)!");
			}
		    else if(PlayerInfo[playerid][pMember] == DoT+listitem && PlayerInfo[playerid][pProfSkill] < 400
				&& FamilyInfo[DoT+listitem][fMembers] > 1 )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
			}
			else
			{
				if(!strcmp(FamilyInfo[DoT+listitem][fLeader], "No-One", true))
				{//если лидер нет, т.е. имя лидера фракции равно "No-One"
					if(PlayerInfo[playerid][pMember] == DoT+listitem && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+listitem);
					else if(FamilyInfo[DoT+listitem][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+listitem); //если место лидера пусто
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
				}
			}
			MenuVacancies(playerid);
		}
		case 3://4 DoH
		{
			if(PlayerInfo[playerid][pLeader] == DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
			}
			else if(//PlayerInfo[playerid][pRoadSkill] < 400 &&
					PlayerInfo[playerid][pMember] != DoT+listitem &&
					PlayerInfo[playerid][pRespect] < (OnlineRecord*200/100))
			{
				//SendClientMessage(playerid, COLOR_GREY, "   Ваш навык ремонтника дорог меньше 400 !");
				format(strings, sizeof(strings), "   Ваше уважение %d меньше %d !", PlayerInfo[playerid][pRespect], (OnlineRecord*200/100));
				SendClientMessage(playerid, COLOR_GREY, strings);
			}
			else if(PlayerInfo[playerid][pCarLic] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует водительская лицензия !");
			}
			else if(PlayerInfo[playerid][pFlyLic] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на полёты !");
			}
		    else if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pMember] != DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже состоите в какой-то фракции. Для начала увольтесь (USE: /uninvite)!");
			}
		    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob)!");
			}
		    else if(PlayerInfo[playerid][pMember] == DoT+listitem && PlayerInfo[playerid][pProfSkill] < 400
				&& FamilyInfo[DoT+listitem][fMembers] > 1 )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
			}
			else
			{
				if(!strcmp(FamilyInfo[DoT+listitem][fLeader], "No-One", true))
				{//если лидер нет, т.е. имя лидера фракции равно "No-One"
					if(PlayerInfo[playerid][pMember] == DoT+listitem && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+listitem);
					else if(FamilyInfo[DoT+listitem][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+listitem); //если место лидера пусто
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
				}
			}
			MenuVacancies(playerid);
		}
		case 4://5 LCN
		{
			if(PlayerInfo[playerid][pLeader] == DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
			}
			else if(//PlayerInfo[playerid][pDrugsSkill] < 2000 &&
					PlayerInfo[playerid][pMember] != DoT+listitem &&
					PlayerInfo[playerid][pRespect] < (OnlineRecord*150/100))
			{
				//SendClientMessage(playerid, COLOR_GREY, "   Ваш навык наркодилера меньше 2000 !");
				format(strings, sizeof(strings), "   Ваше уважение %d меньше %d !", PlayerInfo[playerid][pRespect], (OnlineRecord*150/100));
				SendClientMessage(playerid, COLOR_GREY, strings);
			}
			else if(PlayerInfo[playerid][pCarLic] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует водительская лицензия !");
			}
			else if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на оружие !");
			}
		    else if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pMember] != DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже состоите в какой-то фракции. Для начала увольтесь (USE: /uninvite)!");
			}
		    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob)!");
			}
		    else if(PlayerInfo[playerid][pMember] == DoT+listitem && PlayerInfo[playerid][pProfSkill] < 400
				&& FamilyInfo[DoT+listitem][fMembers] > 1 )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
			}
			else
			{
				if(!strcmp(FamilyInfo[DoT+listitem][fLeader], "No-One", true))
				{//если лидер нет, т.е. имя лидера фракции равно "No-One"
					if(PlayerInfo[playerid][pMember] == DoT+listitem && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+listitem);
					else if(FamilyInfo[DoT+listitem][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+listitem); //если место лидера пусто
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
				}
			}
			MenuVacancies(playerid);
		}
		case 5://6 Yakuza
		{
			if(PlayerInfo[playerid][pLeader] == DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
			}
			else if(//PlayerInfo[playerid][pGunSkill] < 400 &&
					PlayerInfo[playerid][pMember] != DoT+listitem &&
			    	PlayerInfo[playerid][pRespect] < (OnlineRecord*150/100))
			{
				//SendClientMessage(playerid, COLOR_GREY, "   Ваш навык оружейника меньше 400 !");
				format(strings, sizeof(strings), "   Ваше уважение %d меньше %d !", PlayerInfo[playerid][pRespect], (OnlineRecord*150/100));
				SendClientMessage(playerid, COLOR_GREY, strings);
			}
			else if(PlayerInfo[playerid][pCarLic] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует водительская лицензия !");
			}
			else if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на оружие !");
			}
		    else if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pMember] != DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже состоите в какой-то фракции. Для начала увольтесь (USE: /uninvite)!");
			}
		    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob)!");
			}
		    else if(PlayerInfo[playerid][pMember] == DoT+listitem && PlayerInfo[playerid][pProfSkill] < 400
				&& FamilyInfo[DoT+listitem][fMembers] > 1 )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
			}
			else
			{
				if(!strcmp(FamilyInfo[DoT+listitem][fLeader], "No-One", true))
				{//если лидер нет, т.е. имя лидера фракции равно "No-One"
					if(PlayerInfo[playerid][pMember] == DoT+listitem && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+listitem);
					else if(FamilyInfo[DoT+listitem][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+listitem); //если место лидера пусто
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
				}
			}
			MenuVacancies(playerid);
		}
		case 6://7 DoJ
		{
			if(PlayerInfo[playerid][pLeader] == DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
			}
			else if(//PlayerInfo[playerid][pBookmakerSkill] < 100 &&
					PlayerInfo[playerid][pMember] != DoT+listitem &&
					PlayerInfo[playerid][pRespect] < (OnlineRecord*200/100))
			{
				//SendClientMessage(playerid, COLOR_GREY, "   Ваш навык букмекера меньше 100 !");
				format(strings, sizeof(strings), "   Ваше уважение меньше %d !", (OnlineRecord*400/10));
				SendClientMessage(playerid, COLOR_GREY, strings);
			}
			else if(PlayerInfo[playerid][pCarLic] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует водительская лицензия !");
			}
		    else if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pMember] != DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже состоите в какой-то фракции. Для начала увольтесь (USE: /uninvite)!");
			}
		    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob)!");
			}
			else if(PlayerInfo[playerid][pRespect] < 32)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Для поста губернатора необходимо 32 очка уважения!");
			}
		    else if(PlayerInfo[playerid][pMember] == DoT+listitem && PlayerInfo[playerid][pProfSkill] < 400
				&& FamilyInfo[DoT+listitem][fMembers] > 1 )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
			}
			else
			{
				if(!strcmp(FamilyInfo[DoT+listitem][fLeader], "No-One", true))
				{//если лидер нет, т.е. имя лидера фракции равно "No-One"
					if(PlayerInfo[playerid][pMember] == DoT+listitem && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+listitem);
					else if(FamilyInfo[DoT+listitem][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+listitem); //если место лидера пусто
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
				}
			}
			MenuVacancies(playerid);
		}
		case 7://8 Hitman
		{
			if(PlayerInfo[playerid][pLeader] == DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
			}
			else if(//PlayerInfo[playerid][pJackSkill] < 400 &&
					PlayerInfo[playerid][pMember] != DoT+listitem &&
    					PlayerInfo[playerid][pRespect] < (OnlineRecord*200/100))
			{
				//SendClientMessage(playerid, COLOR_GREY, "   Ваш навык автоугонщика меньше 400 !");
				format(strings, sizeof(strings), "   Ваше уважение %d меньше %d !", PlayerInfo[playerid][pRespect], (OnlineRecord*200/100));
				SendClientMessage(playerid, COLOR_GREY, strings);
			}
			else if(PlayerInfo[playerid][pCarLic] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует водительская лицензия !");
			}
			else if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на оружие !");
			}
		    else if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pMember] != DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже состоите в какой-то фракции. Для начала увольтесь (USE: /uninvite)!");
			}
		    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob)!");
			}
		    else if(PlayerInfo[playerid][pMember] == DoT+listitem && PlayerInfo[playerid][pProfSkill] < 400
				&& FamilyInfo[DoT+listitem][fMembers] > 1 )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
			}
			else
			{
				if(!strcmp(FamilyInfo[DoT+listitem][fLeader], "No-One", true))
				{//если лидер нет, т.е. имя лидера фракции равно "No-One"
					if(PlayerInfo[playerid][pMember] == DoT+listitem && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+listitem);
					else if(FamilyInfo[DoT+listitem][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+listitem); //если место лидера пусто
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
				}
			}
			MenuVacancies(playerid);
		}
		case 8://9 SAN
		{
			if(PlayerInfo[playerid][pLeader] == DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
			}
			else if(PlayerInfo[playerid][pCourierSkill] < 400 && PlayerInfo[playerid][pMember] != DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Ваш навык курьера меньше 400 !");
			}
			else if(PlayerInfo[playerid][pCarLic] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует водительская лицензия !");
			}
			else if(PlayerInfo[playerid][pFlyLic] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на полёты !");
			}
		    else if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pMember] != DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже состоите в какой-то фракции. Для начала увольтесь (USE: /uninvite)!");
			}
		    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob)!");
			}
		    else if(PlayerInfo[playerid][pMember] == DoT+listitem && PlayerInfo[playerid][pProfSkill] < 400
				&& FamilyInfo[DoT+listitem][fMembers] > 1 )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
			}
			else
			{
				if(!strcmp(FamilyInfo[DoT+listitem][fLeader], "No-One", true))
				{//если лидер нет, т.е. имя лидера фракции равно "No-One"
					if(PlayerInfo[playerid][pMember] == DoT+listitem && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+listitem);
					else if(FamilyInfo[DoT+listitem][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+listitem); //если место лидера пусто
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
				}
			}
			MenuVacancies(playerid);
		}
		case 9://10 DoE
		{
			if(PlayerInfo[playerid][pLeader] == DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
			}
			else if(PlayerInfo[playerid][pBusSkill] < 400 &&
					PlayerInfo[playerid][pMember] != DoT+listitem &&
					PlayerInfo[playerid][pRespect] < (OnlineRecord*200/100))
			{
				SendClientMessage(playerid, COLOR_GREY, "   Ваш навык водителя автобуса меньше 400 !");
				format(strings, sizeof(strings), "   Ваше уважение %d меньше %d !", PlayerInfo[playerid][pRespect], (OnlineRecord*200/100));
				SendClientMessage(playerid, COLOR_GREY, strings);
			}
			else if(PlayerInfo[playerid][pCarLic] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует водительская лицензия !");
			}
		    else if(PlayerInfo[playerid][pMember] > 0 && PlayerInfo[playerid][pMember] != DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже состоите в какой-то фракции. Для начала увольтесь (USE: /uninvite)!");
			}
		    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != DoT+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob)!");
			}
		    else if(PlayerInfo[playerid][pMember] == DoT+listitem && PlayerInfo[playerid][pProfSkill] < 400
				&& FamilyInfo[DoT+listitem][fMembers] > 1 )
			{
				SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
			}
			else
			{
				if(!strcmp(FamilyInfo[DoT+listitem][fLeader], "No-One", true))
				{//если лидер нет, т.е. имя лидера фракции равно "No-One"
					if(PlayerInfo[playerid][pMember] == DoT+listitem && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+listitem);
					else if(FamilyInfo[DoT+listitem][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), DoT+listitem); //если место лидера пусто
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
				}
			}
			MenuVacancies(playerid);
		}
		case 10://UnInvite
		{//178.124.35.222
		    if(PlayerInfo[playerid][pMember] == 0)
		    {
       			SendClientMessage(playerid, COLOR_GREY, "   Вы не являетесь членом организации !");
			}
			else if(GetPVarInt(playerid, "gShowDialog") != -1)
		    {
       			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете в данный момент уволиться! Закройте диалоговое окно!");
			}
			else
			{
				//new member = PlayerInfo[playerid][pMember];
				format(strings, sizeof(strings), "* Вы подали в отставку. Вы теперь снова Гражданский.", PlayerName(playerid));
				SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
				UninvitePlayerid(MAX_PLAYERS-1, playerid, PlayerName(playerid));
				//format(strings, sizeof(strings), "AdmCmd: %s has uninvited from Faction %d.", PlayerName(playerid), member);
				//Log(INVITE,strings);
			}
			MenuVacancies(playerid);
		}
	}
	return 1;
}





stock GangsVacancies(playerid)
{
	new listitems[585];
	strcat(listitems, "\n1.\tGrove Street\
\n2.\tThe Ballas\
\n3.\tVarios Los Aztecas\
\n4.\tLos Santos Vagos\
\n5.\tDa Nang Boys\
\n6.\tSan Fierro Rifa\
\n7.\tThe Traids\
\n8.\tBikers\
\n9.\tThe Mafia\
\nУйти из банды");
	ShowPlayerDialogEx(playerid, GANGVACANCIES_DIALOG, DIALOG_STYLE_LIST, "Меню вакансий", listitems, "Ок", "Отмена");
}

stock GangsVacancies_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if(dialogid != GANGVACANCIES_DIALOG) return 1;
	
	if(!response) return 1;

	switch(listitem)
	{
		case 0..8://1-9
		{
      		/*if(PlayerInfo[playerid][pMember] != 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы находитесь уже в группе! (USE: /uninvite, чтобы уволиться)");
			}*/
			//else
			if(PlayerInfo[playerid][pLeader] == TEAM_GROVE+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы уже лидер данной фракции (USE: /uninvite)!");
			}
			else if(
					//(PlayerInfo[playerid][pDrugsSkill] < 500 && PlayerInfo[playerid][pMember] != TEAM_GROVE+listitem) &&
					//(PlayerInfo[playerid][pGunSkill] < 100 && PlayerInfo[playerid][pMember] != TEAM_GROVE+listitem) &&
					PlayerInfo[playerid][pRespect] < (OnlineRecord*100/100)
				   )
			{
				//SendClientMessage(playerid, COLOR_GREY, "   Ваш навык наркодилера меньше 500 !");
				//SendClientMessage(playerid, COLOR_GREY, "   Ваш навык оружейника меньше 100 !");
				format(strings, sizeof(strings), "   Ваше уважение %d меньше %d !", PlayerInfo[playerid][pRespect], (OnlineRecord*100/100));
				SendClientMessage(playerid, COLOR_GREY, strings);
			}
			else if(PlayerInfo[playerid][pGunLic] != 1 && !gRealWar)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У Вас отсутствует лицензия на оружие !");
			}
		    else if(PlayerInfo[playerid][pJob] > 0 && PlayerInfo[playerid][pMember] != TEAM_GROVE+listitem)
			{
				SendClientMessage(playerid, COLOR_GREY, "   У вас есть Работа (USE: /quitjob, чтобы уйти с работы)!");
			}
		    else if(PlayerInfo[playerid][pMember] == TEAM_GROVE+listitem && PlayerInfo[playerid][pProfSkill] < 400
				&& FamilyInfo[TEAM_GROVE+listitem][fMembers] > 1 )
			{//если во фракции 2 и более человек, то проверить у кого скил достиг 400, а если игрок 1 во фракции то просто дать возможностьстать лидером
				SendClientMessage(playerid, COLOR_GREY, "   Ваш професcиональный навык меньше 400 !");
			}
			else
			{
#if defined vw_sql//#endif
			    new ToBase[49+2];
				format(ToBase, sizeof(ToBase), "SELECT `Leader` FROM `players` WHERE `Leader`=%d", TEAM_GROVE+listitem);// LIMIT 1
				/*mysql_query(ToBase); mysql_store_result();
				if(mysql_num_rows() == 0)
				{
					if(FamilyInfo[TEAM_GROVE+listitem][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), TEAM_GROVE+listitem);
					else if(PlayerInfo[playerid][pMember] == TEAM_GROVE+listitem && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), TEAM_GROVE+listitem);
				}
				mysql_free_result();*/
				new DBResult:db_result = db_query(db_VW, ToBase);
				if(db_num_rows(db_result) == 0)
			 	{
					if(FamilyInfo[TEAM_GROVE+listitem][fMembers] <= 0) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), TEAM_GROVE+listitem);
					else if(PlayerInfo[playerid][pMember] == TEAM_GROVE+listitem && PlayerInfo[playerid][pRank] >= 2) MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), TEAM_GROVE+listitem);
				}
				db_free_result(db_result);
				
#endif
				if(!strcmp(FamilyInfo[TEAM_GROVE+listitem][fLeader], "No-One", true))
				{
					MakeLeader(MAX_PLAYERS-1, playerid, PlayerName(playerid), TEAM_GROVE+listitem);
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   В данной фракции есть лидер !");
				}
			}
			GangsVacancies(playerid);
		}
		case 9://10 UnInvite
		{//178.124.35.222
		    if(PlayerInfo[playerid][pMember] == 0)
		    {
       			SendClientMessage(playerid, COLOR_GREY, "   Вы не являетесь членом организации !");
			}
			else if(GetPVarInt(playerid, "gShowDialog") != -1)
		    {
       			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете в данный момент уволиться! Закройте диалоговое окно!");
			}
			else if(PlayerInfo[playerid][pAccount] == 0)
			{
       			SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
			}
			else
			{
				//new family = PlayerInfo[playerid][pMember];
				format(strings, sizeof(strings), "* Вы подали в отставку. Вы теперь снова Гражданский.", PlayerName(playerid));
				SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
				UninvitePlayerid(MAX_PLAYERS-1, playerid, PlayerName(playerid));
				//format(strings, sizeof(strings), "AdmCmd: %s has uninvited from Faction %d.", PlayerName(playerid), family);
				//Log(INVITE,strings);
			}
			GangsVacancies(playerid);
		}
	}
	return 1;
}

//==============================================================================
stock job_command(playerid)//JobHelp(playerid)
{
	new bigmsgitem[1673];//определяется опытным путём по ошибкам в чате
	if(PlayerInfo[playerid][pJob] == 1) {
		strins(bigmsgitem, "\t*** ШАХТЁР ***", strlen(bigmsgitem));
	}
    else if(PlayerInfo[playerid][pJob] == LAWYER) {
   		strins(bigmsgitem, "\n\t*** АДВОКАТ ***  \n/free - освободить заключенного \n/jailstats - статистика заключенных", strlen(bigmsgitem));
	}
    else if(PlayerInfo[playerid][pJob] == ROADWORKER) {//~k~~VEHICLE_TURRETDOWN~
    	strins(bigmsgitem, "\n\t*** РЕМОНТНИК ДОРОГ *** \nnum8 - поставить/снять блок \n/gps 1048 - выход на дежурство \n/gps 1038 - получение материалов", strlen(bigmsgitem));///gps 1036-1039 - получение материалов
    	strins(bigmsgitem, "\n/roadstatus - посмотреть статус всех мостов", strlen(bigmsgitem));//\n(/rr)repairroad(0=OFF - для 5 скила)
	}
    else if(PlayerInfo[playerid][pJob] == DRUGDEALER) {
    	strins(bigmsgitem, "\n\t*** НАРКОДИЛЕР ***  \n/selldrugs - продать наркотики \n/gps 1032 - получение материалов \n/gps 1006 - сдача материалов", strlen(bigmsgitem));
	}///getdrugs
    else if(PlayerInfo[playerid][pJob] == CARJACKER) {
    	strins(bigmsgitem, "\n\t*** АВТОУГОНЩИК ***  \n/steal - взломать замок машины отмычкой \n/dropcar - сдать авто", strlen(bigmsgitem));
    	strins(bigmsgitem, "\n/gps 1039 - получение материалов \n/gps 1040 - сдача материалов \n/sell SkeletonKey - продать отмычки в 24/7", strlen(bigmsgitem));
	}
    else if(PlayerInfo[playerid][pJob] == AUTOBUYER) {
    	strins(bigmsgitem, "\n*** СКУПЩИК АВТО ***  \n/buycar - предложить купить авто \n/parking - запарковать купленный авто \n/showparking - вернуть все машины в парк и открыть", strlen(bigmsgitem));
    	strins(bigmsgitem, "\n/saveparking - пересохранить на паркинге тачку", strlen(bigmsgitem));//\n/buyprods - установить процент оплаты с покупки \n/sellprods - установить процент оплаты с продажи
	}// //\n/redraft - предложить продать авто
    else if(PlayerInfo[playerid][pJob] == CARMECHANIC) {
    	strins(bigmsgitem, "\n\t*** МЕХАНИК ***  \n/tuning - тюнить свою тачку \n/moding - предложить тюн \n/repair - починить \n/refill - заправить", strlen(bigmsgitem));
    	strins(bigmsgitem, "\n\t*** МЕХАНИК ***  \n"#VEHICLE_TURRETDOWN" - поднять тачку на буксир\n"#VEHICLE_TURRETUP" - опустить тачку", strlen(bigmsgitem));
	}
    else if(PlayerInfo[playerid][pJob] == FARMER) {
    	strins(bigmsgitem, "\n\t*** ФЕРМЕР ***  \n/finfo - статистика фермы ", strlen(bigmsgitem));//\n/finvite - взять на работу \n/funinvite - уволить с работы
	}
    else if(PlayerInfo[playerid][pJob] == ARMSDEALER) {
    	strins(bigmsgitem, "\n\t*** ОРУЖЕЙНИК ***  \n/sellgun - продать оружие \n/gps 1036 - получение материалов \n/gps 1037 - сдача материалов", strlen(bigmsgitem));
	}// /materials get  /materials deliver
    else if(PlayerInfo[playerid][pJob] == CARDEALER) {
    	strins(bigmsgitem, "\n\t*** АВТОДИЛЕР ***  \n/sellcar - продать транспорт \n/insurance - предложить страховой полюс \n/carinfo - посмотреть информацию о автомобилях на сервере", strlen(bigmsgitem));
	}
    else if(PlayerInfo[playerid][pJob] == INKASSATOR) {
    	strins(bigmsgitem, "\n\t*** ИНКАССАТОР ***  \n/paydesk - предложить бизнессмену услуги/взять деньги из кассы биза", strlen(bigmsgitem));
	}
    else if(PlayerInfo[playerid][pJob] == BOOKMAKER) {
    	strins(bigmsgitem, "\n\t*** БУКМЕКЕР ***  \n/secundans - предложить быть секундантом \n/dorate - предложить сделать ставки \n/fight - начать бой \n/boxstats - статистика боксера", strlen(bigmsgitem));
	}//
    else if(PlayerInfo[playerid][pJob] == TAXIDRIVER) {
    	strins(bigmsgitem, "\n\t*** ТАКСИСТ ***  \n/eject - выкинуть из машины пассажира", strlen(bigmsgitem));
	}///duty(установить плату и выйти на дежурство)
	else if(PlayerInfo[playerid][pJob] == BUSDRIVER) {	// если вы таксист или водитель автобуса
    	strins(bigmsgitem, "\n\t*** ВОДИТЕЛЬ ***  \n/seebus - посмотреть список занятых маршрутов", strlen(bigmsgitem));
	}
    else if(PlayerInfo[playerid][pJob] == PAPERBOY) {
    	strins(bigmsgitem, "\n\t*** КУРЬЕР ***  \n/papers - просмотреть список написанных газет \n/bring - взять газету", strlen(bigmsgitem));
    	strins(bigmsgitem, "\n/read paper - читать газету \n/sellpaper - продать газету\n/gps 1008 - здание новостей", strlen(bigmsgitem));
	}
	else if(PlayerInfo[playerid][pJob] == TRUCKER) {//\n/load - загруженность
		strins(bigmsgitem, "\n\t*** ДАЛЬНОБОЙЩИК *** \n"#VEHICLE_TURRETUP" - взять груз \n"#VEHICLE_TURRETDOWN" - подцепить/отцепить прицеп", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/cancel task - отказаться от задания \n(/wt)walkietalkie - рация \n/trafic - диспетчерская грузов", strlen(bigmsgitem));
		strins(bigmsgitem, "\nПолуприцеп 591(/gps 1044) - для металла\nПолуприцеп 435(/gps 1045) - для текстиля\nПолуприцепы 606,607 - для продовольствия", strlen(bigmsgitem));
		strins(bigmsgitem, "\nПолуприцеп 450(/gps 1041) - для древесины\nПолуприцеп 584(/gps 1042)(/gps 1043) - для нефти", strlen(bigmsgitem));
		strins(bigmsgitem, "\nгрузовик категории Station_Wagons(Фургон) - для перевозки всех видов товаров", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/load - кол-во товара в прицепе\n/unload - сбросить часть груза", strlen(bigmsgitem));
	}//для дальнобойщиков
	else if(PlayerInfo[playerid][pJob] == TRASHMAN) {
		strins(bigmsgitem, "\n\t*** ВОДИТЕЛЬ МУСОРОВОЗА ***  \n/gps 1047 - раздевалка", strlen(bigmsgitem));
	}//для дальнобойщиков
	//--------------------------------------------------------------------------
	if(strlen(bigmsgitem) > sizeof(bigmsgitem))
	{
		//ИНФОРМИРОВАНИЕ
		new strtmp[MAX_STRING];
		format(strtmp, sizeof(strtmp), "Error: JOB HELP - %s[%d], strlen(bigmsgitem): %d, sizeof(bigmsgitem): %d", PlayerName(playerid), playerid, strlen(bigmsgitem), sizeof(bigmsgitem));
		Log(ERROR, strtmp);
		return 1;
	}
	if(strlen(bigmsgitem) <= 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   JobHelp пуст");
		help_OnPlayerKeyStateChange(playerid);
		return 1;
	}
	ShowPlayerDialogEx(playerid, BACKCMD_DIALOG, DIALOG_STYLE_MSGBOX, "JOB HELP - наберите команду для информации", bigmsgitem, "OK", "Назад");
	return 1;
}


stock job_OnFiveMinutsTimer(playerid)
{
	new strtmp[MAX_STRING];
	if(PlayerInfo[playerid][pJob] == CARDEALER && AFK_IdleTime[playerid] < 3)//каждые 5 минут начисляем деньги
	{   //для автодилеров
      	if(BizInfo[0][bTill] <= 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Bам НЕ перечислено за дежурство в АвтоСалоне, т.к. Казна пуста !");
			return 1;
		}
      	if( IsPlayerInRangeOfPoint(playerid, 5.0, -1658.0516,1206.8474,7.2500))
  		{
		    new level = PlayerInfo[playerid][pCarSkill];
		    new money;
			if(level < 50) { money = 100 + random(100); }
			else if(level >= 50 && level < 100) { money = 200 + random(200); }
			else if(level >= 100 && level < 200) { money = 300 + random(300); }
			else if(level >= 200 && level < 400) { money = 400 + random(400); }
			else if(level >= 400) { money = 500 + random(500); }
	    	//GivePlayerMoneyB(1, playerid, 2*DutyFiveMinuts*skill);//перечислить игроку зарплату
	    	money = (1+PlayerInfo[playerid][pContractTime]/100)*money;//100 часов работы по контракту увеличивает ЗП в 2 раза
	    	GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, money);//перечислить игроку зарплату
	    	BizInfo[0][bTill] -= money; BizInfo[0][bImport] += money;
	    	PlayerInfo[playerid][pCarSkill] ++;
			format(strtmp, sizeof(strtmp), "Bам перечислено {33AA33}$%d{0080FF} за дежурство в АвтоСалоне !", money);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, strtmp);
//TestLog(OPTIM, "FiveMinutsTimer_5", GetTickCount(), timers);
		}
	}
	else if(PlayerInfo[playerid][pJob] == TAXIDRIVER && gJobDuty[playerid] == 1 && AFK_IdleTime[playerid] < 3)//каждые 5 минут начисляем деньги
	{   //для таксистов
      	if(BizInfo[0][bTill] <= 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Bам НЕ перечислено за дежурство в вашем округе, т.к. Казна пуста !");
			return 1;
		}
       	if(
		   	(playerid == TaxiDriver[0] && IsPlayerInZone(playerid, MI_LOS_SANTOS)) || //LS
			(playerid == TaxiDriver[1] && IsPlayerInZone(playerid, MI_SAN_FIERRO)) ||  //SF
			(playerid == TaxiDriver[2] && IsPlayerInZone(playerid, MI_LAS_VENTURAS)) //LV
		   )
  		{
		    new level = PlayerInfo[playerid][pTaxiSkill];
		    new money;
			if(level < 50) { money = 500 + random(500); }
			else if(level >= 50 && level < 100) { money = 1000 + random(400); }
			else if(level >= 100 && level < 200) { money = 1400 + random(300); }
			else if(level >= 200 && level < 400) { money = 1700 + random(200); }
			else if(level >= 400) { money = 1900 + random(100); }
			money = floatround((1+PlayerInfo[playerid][pContractTime]/10.0)*money);//10 часов работы по контракту увеличивает ЗП в 2 раза
	    	GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, money);//перечислить игроку зарплату
	    	BizInfo[0][bTill] -= money; BizInfo[0][bImport] += money;
	    	if(PlayerInfo[playerid][pTaxiSkill] < (1000-1)) PlayerInfo[playerid][pTaxiSkill] ++;
			format(strtmp, sizeof(strtmp), "Bам перечислено {33AA33}$%d{FF6600} за дежурство в вашем округе !", money);
			SendClientMessage(playerid, COLOR_ORANGE, strtmp);
//TestLog(OPTIM, "FiveMinutsTimer_6", GetTickCount(), timers);
		}
	}
	return 1;
}

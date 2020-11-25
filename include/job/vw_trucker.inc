/*
 *            vw_trucker.inc
 *       (c) Copyright 2009-2019 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (https://vk.com/id174413521)
 * @date      : 07.04.2020
 * @update    : 07.04.2020
 *
 * This file is provided as is (no warranties).
 */


//#include <a_samp>
//#include "../vw_defines"//константы

//new Float: distance_to_point;//расстояние от текущего пробега до точки

new LimitMetal = 5000;
new LimitTextiles = 5000;
new LimitProvisions = 10000;
new LimitTree = 5000;
new LimitFuel = 10000;

new RANDMONEY5 = 600;//для экономики

//для дальнобойщиков
new gLoading[MAX_PLAYERS];//флаг - начало загрузки
new gUnLoading[MAX_PLAYERS];//флаг - начало разгрузки
new ProdCounter[MAX_PLAYERS];//кол-во продов которое будет загружаться, или при разгрузке выгружаться
//new LastRandCargo;


new checktimedeliver[MAX_PLAYERS];//счётчик для проверки доставки

//для дальнобойщиков
new tmpCounter[MAX_PLAYERS];

enum TelePosEnum// текущая позиции для //SetPlayerRouting
{
	Float:tX,
	Float:tY,
	Float:tZ
};
new Float:PurposePoint[MAX_PLAYERS][TelePosEnum];


//new SelectRout[MAX_PLAYERS];
//массив хранит Ид бизов куда надо довезти груз по индексу биза откуда и хрупкость
enum list_cargo_info
{
	cWhere,//куда
	cFrailty,//хрупкость
}
new BizList[MAX_BIZ][list_cargo_info];//хранит направление для каждого биза
new SBizList[MAX_SBIZ][list_cargo_info];

new ImportanceFrailty[] = {15,20,25,30,35,40,45,50};//,55,60,65,70,75};//,80,75,90,95};//случайные значения хрупкости
new Float:CurrentTruckHealth[MAX_VEHICLES+1];//состояние машины в процентах


//переделать на textdraw т.к. убого
stock trucker_SendBuySale(playerid)//для дальнобойщиков STEP0
{   //выводит каждую секунду инфу при заезде на пикап бизов
//вызывается из OnPlayerPickupTimer который вызывается из OneSecondTimers2
	//if(!IsPlayerInAnyVehicle(playerid)) { return 1; }
	//if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) { return 1; }
	if(nCarID[playerid] == 0) { return 1; }
	if( //!IsInHardTruck(nCarID[playerid]) && !IsInTruck(nCarID[playerid]))
		VehicleArray[nCarModel[playerid]-400][Category] != Station_Wagons &&
		VehicleArray[nCarModel[playerid]-400][Category] != Industrial &&
		VehicleArray[nCarModel[playerid]-400][Category] != Lorries)
	{ return 1; }
	if(gLoading[playerid]) { return 1; }//не выводить если загружается
	if(gUnLoading[playerid]) { return 1; }//не выводить если разгружается

	//new strings[MAX_STRING];
	//if(nTrailerModel[playerid] == 435)
	//{
	for(new b=0; b<MAX_BIZ; b++)
	{
		if( !IsPlayerInRangeOfPoint(playerid, 10.0,	BizInfo[b][bEntranceX],BizInfo[b][bEntranceY],BizInfo[b][bEntranceZ]) ) continue;
		//~w~%s~n~~n~~r~Products Required~w~: %d
		format(strings, sizeof(strings), "~p~Buying: ~g~$%.2f ~w~%d %%\
			~n~~p~Sale: ~g~$%.2f ~w~%d %%\
			~n~~p~Funds: ~g~%d",
			//BizInfo[b][bDiscription], //(BizInfo[b][bBuyProd]-BizInfo[b][bProducts]),
		 	compcost*(100+BizInfo[b][bBuyProd])/100.0, 100+BizInfo[b][bBuyProd],
		 	compcost*(100+BizInfo[b][bSellProd])/100.0, 100+BizInfo[b][bSellProd],
			BizInfo[b][bProducts]);
		GameTextForPlayerEx(playerid, strings, 1500, 3);
		return 1;//break;
	}
	//}
	//else if(nTrailerModel[playerid] == 450 || nTrailerModel[playerid] == 584 || nTrailerModel[playerid] == 591)
	//{
	for(new sb=0; sb<MAX_SBIZ; sb++)//36 %%\%%
	{
		if( !IsPlayerInRangeOfPoint(playerid, 10.0,	SBizInfo[sb][sbEntranceX],SBizInfo[sb][sbEntranceY],SBizInfo[sb][sbEntranceZ]) ) continue;
		//~w~%s~n~~n~~r~Products Required~w~: %d~n~~y~Price per Product: ~w~$%d[%d %%]~n~~g~Funds: ~w~$%d
		format(strings, sizeof(strings), "~p~Buying: ~g~$%.2f ~w~%d %%\
			~n~~p~Sale: ~g~$%.2f ~w~%d %%\
			~n~~p~Products: ~g~%d",
			//SBizInfo[sb][sbDiscription], //(SBizInfo[sb][sbBuyProd]-SBizInfo[sb][sbProducts]),
			compcost*(100+SBizInfo[sb][sbBuyProd])/100.0, 100+SBizInfo[sb][sbBuyProd],
			compcost*(100+SBizInfo[sb][sbSellProd])/100.0, 100+SBizInfo[sb][sbSellProd],
			SBizInfo[sb][sbProducts]);
		GameTextForPlayerEx(playerid, strings, 1500, 3);
		break;
	}
	//}
	//custompickups end
//new strtmp[MAX_STRING];
//format(strtmp, sizeof(strtmp), "End SendBuySale(playerid:%d[CarID:%d]) nTrailerModel:%d, gUnLoading:%d", playerid, nCarID[playerid], nTrailerModel[playerid], gUnLoading[playerid]);
//SendClientMessage(playerid, COLOR_GREEN, strtmp);
	return 1;
}

//##############################################################################//
//                                                                              //
//                             ФОРМИРУЕМ ТОВАРООБОРОТ                           //
//                                                                              //
//##############################################################################//
//1. ПОСТАВКА СЫРЬЯ ИЗ ПОРТА НА СКЛАД
//2. ПОСТАВКА ТОВАРОВ СО СКЛАДА В ПОРТ. Цена продажи Складом увеличивается в 3 раза. Цена покупки Портом увеличивается в 4 раза
//3. ПОСТАВКА СЫРЬЯ СО СКЛАДА ПО БИЗАМ
//4. ПОСТАВКА ТОВАРОВ ИЗ БИЗОВ НА СКЛАД
//5. ПОСТАВКА СЫРЬЯ ИЗ КОМПАНИЙ НА СКЛАД
//6. ПОСТАВКА НЕФТИ СО СКЛАДА НА АЗС
//7. ПОСТАВКА НЕФТИ С Oil Company(нефтедобывающая компания) в Gas Company(нефтеперерабатывающая компания)

//для дальнобойщиков STEP0
stock trucker_OnGameModeInit()//stock CargoInit()//формирование массива куда отвезти груз
{   //вызывается из OnFiveMinutsTimer
	//--------------------------------------------------------------------------
//1. ПОСТАВКА СЫРЬЯ ИЗ ПОРТА НА СКЛАД
//4. ПОСТАВКА ТОВАРОВ ИЗ БИЗОВ НА СКЛАД
//все грузы с бизов посылаем на склад
	for(new b=1; b<MAX_BIZ; b++)//пропускаем банк
	{   //пока не заполнятся все ячейки
	    BizList[b][cWhere] = 80;//все грузы с бизов посылаем на склад
		BizList[b][cFrailty] = ImportanceFrailty[ random(sizeof(ImportanceFrailty)) ];//хрупкость в процентах;
	}
//2. ПОСТАВКА ТОВАРОВ СО СКЛАДА В ПОРТ.
	BizList[80][cWhere] = 81;//груз со склада посылаем на порт
	BizList[80][cFrailty] = ImportanceFrailty[ random(sizeof(ImportanceFrailty)) ];//хрупкость товаров случайная, т.к. товары разные
	//--------------------------------------------------------------------------
//5. ПОСТАВКА СЫРЬЯ ИЗ КОМПАНИЙ НА СКЛАД
//все грузы с компаний посылаем на склад
	for(new sb=0; sb<MAX_SBIZ; sb++)
	{   //пока не заполнятся все ячейки по бизам компаний
	    if(sb >= GAS_STATION && sb < PARKING+sizeof(Parking)) continue;//пропускаем паркинг
	    SBizList[sb][cWhere] = 80;
		SBizList[sb][cFrailty] = ImportanceFrailty[ random(sizeof(ImportanceFrailty)) ];//хрупкость в процентах;
		if(sb == 3 || sb == 4 || sb == 17)
		{//для Gas Company Coal Company Oil Company
			SBizList[sb][cFrailty] = 10;//хрупкость в процентах;
		}
	}
	//--------------------------------------------------------------------------
//7. ПОСТАВКА НЕФТИ С Oil Company(нефтедобывающая компания) в Gas Company(нефтеперерабатывающая компания)
    SBizList[GAS_STATION-1][cWhere] = 3;//сырьё нефть с Oil Company посылаем в Gas Company
	SBizList[GAS_STATION-1][cFrailty] = 1;//хрупкость в процентах для нефти
	//--------------------------------------------------------------------------
//6. ПОСТАВКА НЕФТИ СО СКЛАДА НА АЗС
	//составляем список случайных заправок для Gas Company(3)
	//static LastRandCargo;//глючит
	new rout = GAS_STATION+random(PARKING-GAS_STATION);//18 + rand(40-18)
   	/*while(rout == LastRandCargo)
	{//делать  покуда направление равно последнему записанному
		rout = GAS_STATION+random(PARKING-GAS_STATION);
	}
	LastRandCargo = rout;*/
    SBizList[3][cWhere] = rout;//бензин с Gas Company посылаем на АЗС //MAX_SBIZ
	SBizList[3][cFrailty] = 1;//хрупкость в процентах для бензина
	//--------------------------------------------------------------------------
//3. ПОСТАВКА СЫРЬЯ СО СКЛАДА ПО БИЗАМ
//ВАРИАНТ 2, перезапишет верхние направления
	//составляем список последовательности движения грузов для организации гонок
	//
	/*new index;
	while(index < MAX_BIZ)
	{   //пока не заполнятся все ячейки
	    BizList[index][cWhere] = random(MAX_BIZ);
		BizList[index][cFrailty] = ImportanceFrailty[ random(sizeof(ImportanceFrailty)) ];//хрупкость в процентах;
	    new Found;
	    //проверяемя не совпало ли это значение с присутсвующими
		for(new i=0; i<index; i++)
		{   //пробегаем по всем ячейкам КРОМЕ той же
			if( BizList[index][cWhere] == BizList[i][cWhere] && i != index)
			{	//проверяем на совпадение, если такой уже есть, то повторить
				Found = 1; break;
				//если есть такое же, то выйти из цыкла и повторить с тем же
			}
		}
		if(!Found) index ++;//если совпадения не нашли, то переходим к подбору направления для следующего биза
	}*/
	//--------------------------------------------------------------------------
	print("  vw_trucker 1.0 By: DANGER1979");
	print("_____________________________________________");
	print(" ");
}
stock trucker_OnPlayerConnect(playerid)
{
	gLoading[playerid] = 0;
	gUnLoading[playerid] = 0;
	ProdCounter[playerid] = 0;
	tmpCounter[playerid] = 0;//для дальнобойщиков
}

stock trucker_OnPlayerPickUp(playerid, pickupid)
{
	//--------------------------------------------------------------------------
	if(pickupid == PickupID[7] && IsPlayerInRangeOfPoint(playerid, 2.1, Pickups[pickupid][p_x],Pickups[pickupid][p_y],Pickups[pickupid][p_z]) )
	{
		new caption[65];
		strmid(caption, "[ Дальнобойщик ] {CFD9FF}Помощь по работе", 0, 65, 65);
		new bigmsgitem[1487];
		strins(bigmsgitem, "\nЗдравствуй дорогой Водитель Седельного Тягача! Сейчас я кратко объясню тебе, как подзаработать!", strlen(bigmsgitem));
		strins(bigmsgitem, "\nОзнакомившись с [/jobmanual] едь на Store House [/gps 1034]. Подцепи полуприцеп и подъедь к маркеру!", strlen(bigmsgitem));
		strins(bigmsgitem, "\nНажми NUM8 и ты увидишь Бизнес, куда нам надо завести продукцию. Внизу ты видишь возможную загрузку.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nПример: 431[5000]! Однако не спеши загружать на всю свою фуру!  В бизнесе может и не оказаться денег.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nТак вот, первое значение - это сколько продуктов на складе или на сколько продуктов вам хватает денег,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nвторое - это сколько мы можем завести в бизнес. Надёжно вывозить товары из Store House в Порт [/gps 1035], если вы хотите не прогадать.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nНо более выгоднее, но и рискованнее, вывозить Товары из бизнесов, где стоит высокая зарплата за вывоз, на Склад", strlen(bigmsgitem));
		//strins(bigmsgitem, "\nЕё можно узнать, просмотрев на очень продвинутой статистике сервера ", strlen(bigmsgitem));
		//strins(bigmsgitem, HostName, strlen(bigmsgitem));
		//strins(bigmsgitem, "\nвыбрав раздел ПОИСК и подразделы Бизнеса или Компании. Там ищем пункт Зарплата.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЧем выше зарплата стоит в бизнесе, тем больше вы получите. Всего доброго в пути! Будь аккуратен на дорогах!", strlen(bigmsgitem));
		//strins(bigmsgitem, "\nТак же полный мануал по работе Дальнобойщик вы можете просмотреть на Википедии сервера.", strlen(bigmsgitem));
		//strins(bigmsgitem, "\nЗайдите на Статистику сервера и нажмите пункт WIKI. После перехода на Википедию перейдите к пункту Важно знать!", strlen(bigmsgitem));
		//strins(bigmsgitem, "\nи выберите подпункт Мануал для Дальнобойщиков.", strlen(bigmsgitem));

		if(strlen(bigmsgitem) > sizeof(bigmsgitem))
		{
			//ИНФОРМИРОВАНИЕ
			format(strings, sizeof(strings), "Error39: Дальнобойщик %s[%d], strlen(bigmsgitem): %d, sizeof(bigmsgitem): %d",
				PlayerName(playerid), playerid, strlen(bigmsgitem), sizeof(bigmsgitem));
			Log(ERROR, strings);
			return 1;
		}
		if(strlen(bigmsgitem) <= 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Дальнобойщик");//COLOR_BLUEGREY
			return 1;
		}
		ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, caption, bigmsgitem, "ОК", "");
	}
	return 1;
}

stock trucker_OnPlayerInterior(playerid)
{
	if(PlayerInfo[playerid][pJob] != TRUCKER) return 1;
	if(CP[playerid] == CP_TRUCKER)
	{   //если дальнобойщик подобрал пикап //вошёл в интерьер
	   	SendClientMessage(playerid, COLOR_GREY, "   Вы ушли с маршрута ! Поторопитесь !");
	}
	return 1;
}

stock trucker_OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(PlayerInfo[playerid][pJob] != TRUCKER) return 1;

	if((oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER) &&
		newstate != PLAYER_STATE_DRIVER && newstate != PLAYER_STATE_PASSENGER)//если ID нового состояния равно состоянию 1( на ногах)
	{   //выполняется после выхода из машины И ВО ВСЕХ СЛУЧАЯХ
		//для дальнобойщиков STEP0
		if(CP[playerid] == CP_TRUCKER)
		{   //если дальнобойщик подобрал пикап //вошёл в интерьер //вышел из тачки
			DisablePlayerCheckpointEx(playerid);
			gTextDrawHideCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
		   	SendClientMessage(playerid, COLOR_GREY, "   Вы оставили груз и не выполнили задание ! Поторопитесь !");
		}
	}
	TakeTask(playerid, newstate);
	return 1;
}

stock trucker_DamageStatusUpdate(vehicleid, playerid)
{
	if(PlayerInfo[playerid][pJob] != TRUCKER) return 1;
	//для дальнобойщиков STEP0
	//if(	PlayerInfo[playerid][pLevel] < 5) return 1;

	if(	!(IsInHardTruck(vehicleid) && IsTrailerAttachedToVehicle(vehicleid)) &&
		VehicleArray[nCarModel[playerid]-400][Category] != Station_Wagons) return 1;

	new trailerid;//, trailermodel;
	if(IsTrailerAttachedToVehicle(nCarID[playerid])) { trailerid = nTrailerID[playerid]; /*trailermodel = nTrailerModel[playerid];*/ }
	else { trailerid = nCarID[playerid]; /*trailermodel = nCarModel[playerid];*/ }

	if(VehInfo[trailerid][cLoad] <= 0)
	{
		return 1;
	}

	GetVehicleHealth(vehicleid, VehHealth[vehicleid]);
    if(VehHealth[vehicleid] >= CurrentTruckHealth[vehicleid]) return 1;

//если здоровье тачки меньше предыдущего, то записать текущий ущерб
	CurrentTruckHealth[vehicleid] = VehHealth[vehicleid];//состояние машины в процентах
    new Frailty = Cargo[trailerid][tFrailty];//хрупкость в процентах
	//new Float:Damage = ( (StartTruckHealth[nCarID[playerid]]-CurrentTruckHealth[nCarID[playerid]])/10 )
	//* ( 2.0 - (100.0-Frailty)/100.0 );//ущерб в % тягачу с учётом хрупкости груза
	new Float:Damage = ( (StartTruckHealth[nCarID[playerid]]-CurrentTruckHealth[nCarID[playerid]])/10 )*Frailty;//ущерб в % тягачу с учётом хрупкости груза
	//нормальная хрупкость 50 % гонорар снижается в 2 раза
	//т.е. если мы повредили тягач на 1%, то груз повреждается на 1% при хрупкости 1%
	//т.е. если мы повредили тягач на 80%, то груз повреждается на 80% при хрупкости 1%
	//80*1=80
	//если мы повредили тягач на 1%, то груз повреждается на 80% при хрупкости 80%
	//если мы повредили тягач на 80%, то груз повреждается на 6400% при хрупкости 80%
	//80*80=6400
	//при нулевой хрупкости груз не повреждается
	if(Damage >= 100.0) Damage = 100.0;
	VehInfo[trailerid][cLoad] = floatround(VehInfo[trailerid][cLoad]*(100-Damage)/100.0);
	//new strings[MAX_STRING];
   	format(strings, sizeof(strings), "Повреждение груза: %.1f %%\%%. Остаток груза: %d кг", Damage, VehInfo[trailerid][cLoad]);//'/.
	SendClientMessage(playerid, COLOR_DARKRED, strings);
	//PlaySoundForPlayer(playerid, SOUND_MAGNET_VEHICLE_COLLISION);
	PlaySoundForPlayer(playerid, SOUND_CARGO_PLANE_DOOR_STOP);
	return 1;
}



//##############################################################################//
//                                                                              //
//                            НАЧАЛО ПОЛУЧЕНИЯ ЗАДАНИЯ                          //
//                                                                              //
//##############################################################################//

stock TakeTask(playerid, newstate)
{//вызывается из trucker_OnPlayerStateChange после проверки усталости
	if(newstate != PLAYER_STATE_DRIVER) return 1;
	//new vehicleid = nCarID[playerid];//nCarID[playerid] = GetPlayerVehicleID(playerid);//считывается в player_OnPlayerStateChange(playerid, newstate, oldstate)
	new modelid = nCarModel[playerid];//считывается в player_OnPlayerStateChange(playerid, newstate, oldstate)

	//if(!IsInHardTruck(vehicleid)) return 1;//если Вы сели в грузовик
	if(	VehicleArray[modelid-400][Category] != Station_Wagons &&
		VehicleArray[modelid-400][Category] != Industrial &&//все грузовики
		VehicleArray[modelid-400][Category] != Lorries) return 1;

	/*if(PlayerInfo[playerid][pJob] != TRUCKER && !IsPermitToRider(playerid))
	{
		RemovePlayerFromVehicleEx(playerid);
		SendClientMessage(playerid, COLOR_GREY, "   Вы - не Водитель Седельного Тягача !");
		return 1;
	}*/

	new trailerid;//, trailermodel;
	if(IsTrailerAttachedToVehicle(nCarID[playerid])) { trailerid = nTrailerID[playerid]; }
	else { trailerid = nCarID[playerid]; }

	//if(modelid == 455)
	if(GetCargoType(nCarID[playerid], trailerid) == Amusements)
	{
		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы можете поставлять Метал или товары индустрии развлечений.");
		if(!IsPermitToRider(playerid) && PlayerInfo[playerid][pJob] != TRUCKER ) {
			//RemovePlayerFromVehicleEx(playerid);
			SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Для этого вам необходимо устроиться дальнобойщиком в Мэрии (USE: /gps 1014).");
			return 1;
		}
	}
	//else if(modelid == 456)
	else if(GetCargoType(nCarID[playerid], trailerid) == Trade)
	{
		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы можете поставлять Текстиль или товары розничной торговли.");
		if(!IsPermitToRider(playerid) && PlayerInfo[playerid][pJob] != TRUCKER) {
			//RemovePlayerFromVehicleEx(playerid);
			SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Для этого вам необходимо устроиться дальнобойщиком в Мэрии (USE: /gps 1014).");
			return 1;
		}
	}
	//else if(modelid == 423 || modelid == 588)
	else if(GetCargoType(nCarID[playerid], trailerid) == Restaurant)
	{
		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы можете поставлять Продовольствие или товары ресторанного бизнеса.");
		if(!IsPermitToRider(playerid) && PlayerInfo[playerid][pJob] != TRUCKER) {
			//RemovePlayerFromVehicleEx(playerid);
			SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Для этого вам необходимо устроиться дальнобойщиком в Мэрии (USE: /gps 1014).");
			return 1;
		}
	}
	//else if(modelid == 478)
	else if(GetCargoType(nCarID[playerid], trailerid) == Service)
	{
		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы можете поставлять Древесину или товары сферы услуг.");
  		if(!IsPermitToRider(playerid) && PlayerInfo[playerid][pJob] != TRUCKER) {
		  //RemovePlayerFromVehicleEx(playerid);
		  SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Для этого вам необходимо устроиться дальнобойщиком в Мэрии (USE: /gps 1014).");
		  return 1;
  		}
	}
	//else if(modelid == 524)
	else if(GetCargoType(nCarID[playerid], trailerid) == Industry)
	{
		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы можете поставлять Нефть или товары промышленной сферы.");
		if(!IsPermitToRider(playerid) && PlayerInfo[playerid][pJob] != TRUCKER)	{
			//RemovePlayerFromVehicleEx(playerid);
			SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Для этого вам необходимо устроиться дальнобойщиком в Мэрии (USE: /gps 1014).");
			return 1; }
	}
	//else if(VehicleArray[nCarModel[playerid]-400][Category] == Station_Wagons)
	else if(GetCargoType(nCarID[playerid], trailerid) == Station_Wagons)
	{
		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы можете поставлять Товар из Бизнесов на Склад и со Склада в Порт.");
		if(!IsPermitToRider(playerid) && PlayerInfo[playerid][pJob] != TRUCKER)	{
			//RemovePlayerFromVehicleEx(playerid);
			SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Для этого вам необходимо устроиться дальнобойщиком в Мэрии (USE: /gps 1014).");
			return 1; }
	}

	//----------------------------------------------------------------------
	//ФУНКЦИЯ ПОЛУЧЕНИЯ ЗАДАНИЯ ДАЛЬНОБОЙЩИКА
//для дальнобойщиков STEP1
	/*if(PlayerInfo[playerid][pTruckSkill] < 50 && modelid == 514)//если Petrol Tanker - 514
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вам нужен Навык Дальнобойщика 2, чтобы управлять тягачом Petrol Tanker !");
		RemovePlayerFromVehicleEx(playerid);
		return 1;//выйти из функции (LastCar[playerid] = newcar; не запишится)
	}
	if(PlayerInfo[playerid][pTruckSkill] < 400 && modelid == 515)//если Roadtrain - 515
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вам нужен Навык Дальнобойщика 5, чтобы управлять тягачом Roadtrain!");
		RemovePlayerFromVehicleEx(playerid);
		return 1;//выйти из функции
	}*/
	if(CP[playerid] != 0)//если предыдущее задание выполнено
	{ // чтобы нельзя было несколько раз взять задание
		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы не выполнили доставку груза ! Поторопитесь !");
		PlaySoundForPlayer(playerid, SOUND_RACE_GO);
		return 1;
	}
    //PlayerInfo[playerid][pCarTime] = 0;//обнуляется при получении задания, т.к. не всегда обнуляется
	new level = PlayerInfo[playerid][pTruckSkill];
	if(level < 50)//если у вас уровень Навыка 1 - уголь
	{
		SendClientMessage(playerid, COLOR_YELLOW, "Pаботодатель: для ознакомления с условиями работы (USE: /jobmanual)");
		GameTextForPlayerEx(playerid, " Press ~b~~k~~VEHICLE_TURRETDOWN~ ~n~~g~|~w~Get cargo~g~|", 1000, 1);
	}
//ВОЗВРАЩЕНИЕ К ЗАДАНИЮ
//stock trucker_STATE_DRIVER(playerid)//ReturnToTask(playerid)
	//if(PlayerInfo[playerid][pCarTime] <= 0) return 1;// && CP[playerid] == CP_TRUCKER
	if(Cargo[trailerid][tPeriod] <= 0) return 1;
	if(Cargo[trailerid][tWhere] == -1) return 1;
	if(Cargo[trailerid][tWhence] == -1) return 1;
	if(Cargo[trailerid][tWhere] == -1) return 1;
	if(Cargo[trailerid][CargoType] == 0) return 1;
	//if(VehInfo[trailerid][cLoad] == 0) return 1;// if(Cargo[trailerid][tWeight] == 0) return 1;

	//SetPlayerCheckpointEx(playerid, PurposePoint[playerid][tX],PurposePoint[playerid][tY],PurposePoint[playerid][tZ], CHECKPOINT_SIZE*2);
	CP[playerid] = CP_TRUCKER;
	if(Cargo[trailerid][tWhere] >= 100)
	{
		new rout = Cargo[trailerid][tWhere] - 100;
		SetPlayerCheckpointEx(playerid,
			SBizInfo[rout][sbEntranceX],
			SBizInfo[rout][sbEntranceY],
			SBizInfo[rout][sbEntranceZ],
			CHECKPOINT_SIZE*2);
		/*if(PlayerInfo[playerid][pGPS] == 1)
		{
			SetPlayerRouting(playerid,
				SBizInfo[rout][sbEntranceX],
				SBizInfo[rout][sbEntranceY],
				SBizInfo[rout][sbEntranceZ]);
		}*/
	}
	else
	{
		new rout = Cargo[trailerid][tWhere];
		SetPlayerCheckpointEx(playerid,
			BizInfo[rout][bEntranceX],
			BizInfo[rout][bEntranceY],
			BizInfo[rout][bEntranceZ],
			CHECKPOINT_SIZE*2);
		/*if(PlayerInfo[playerid][pGPS] == 1)
		{
			SetPlayerRouting(playerid,
				BizInfo[rout][bEntranceX],
				BizInfo[rout][bEntranceY],
				BizInfo[rout][bEntranceZ]);
		}*/
	}
   	SendClientMessage(playerid, COLOR_GREY, "   Вы вернулись к заданию ! Маркер установлен !");
	return 1;
}


//stock OnPlayerKeyCargoDeliver(playerid, newkeys,oldkeys)//для дальнобойщиков начало
stock trucker_OnPlayerKeyState_UP(playerid)
{//запускается как при нажатии клавиши num8, так и при нажатии в диалоге кнопки NEXT
	//ОСНОВНАЯ ФУНКЦИЯ ПОЛУЧЕНИЯ ЗАДАНИЯ ДАЛЬНОБОЙЩИКАМ //для дальнобойщиков STEP2
		if(PlayerInfo[playerid][pJob] != TRUCKER) return 1;
		if(nCarID[playerid] == 0)  return 1;
		//nCarID[playerid] = GetPlayerVehicleID(playerid);//получить ID машины игрока из списка установленных моделей
		//nCarModel[playerid] = GetVehicleModel(nCarID[playerid]);//Узнает ID модели данного транспортного средства.
		if(	//!IsInHardTruck(nCarID[playerid]) && !IsInTruck(nCarID[playerid]) &&
			VehicleArray[nCarModel[playerid]-400][Category] != Station_Wagons &&
			VehicleArray[nCarModel[playerid]-400][Category] != Industrial &&
			VehicleArray[nCarModel[playerid]-400][Category] != Lorries//все грузовики
		  )	return 1;
	  
		if(CP[playerid] != 0 )//если предыдущее задание выполнено
		{   // чтобы нельзя было несколько раз взять задание
		   	SendClientMessage(playerid, COLOR_GREY, "   Вы уже взяли груз ! Поторопитесь !");
			return 1;
		}
//ВРЕМЕННО
		if(	IsInHardTruck(nCarID[playerid]) &&
			(!IsTrailerAttachedToVehicle(nCarID[playerid]) || nTrailerID[playerid] == 0))
		{   //если Вы сели в грузовик
			SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы - не прикрепили полуприцеп к тягачу !");
//1. ПОСТАВКА СЫРЬЯ ИЗ ПОРТА НА СКЛАД
//2. ПОСТАВКА ТОВАРОВ СО СКЛАДА В ПОРТ. Цена продажи Складом увеличивается в 3 раза. Цена покупки Портом увеличивается в 4 раза
//3. ПОСТАВКА СЫРЬЯ СО СКЛАДА ПО БИЗАМ
//4. ПОСТАВКА ТОВАРОВ ИЗ БИЗОВ НА СКЛАД
//5. ПОСТАВКА СЫРЬЯ ИЗ КОМПАНИЙ НА СКЛАД
//6. ПОСТАВКА НЕФТИ СО СКЛАДА НА АЗС
//7. ПОСТАВКА НЕФТИ С Oil Company(нефтедобывающая компания) в Gas Company(нефтеперерабатывающая компания)

			SendClientMessage(playerid, COLOR_BLUEGREEN, "   Металл - основа для производства товаров {FFFFFF}индустрии развлечений!");
			SendClientMessage(playerid, COLOR_BLUEGREEN, "   Необходим грузовик 455 или прицеп 591 для перевозки сырья {FFFFFF}индустрии развлечений!");
			SendClientMessage(playerid, COLOR_BLUEGREEN, "   Поставка сырья осуществляется со склада по бизам(компаниям) и товаров из бизов(компаний) на склад!");

			SendClientMessage(playerid, COLOR_BLUEGREEN, "   Текстиль - основа для производства товаров {FFFFFF}розничной торговли!");
			SendClientMessage(playerid, COLOR_BLUEGREEN, "   Необходим грузовик 456 или прицеп 435 для перевозки сырья {FFFFFF}розничной торговли!");
			SendClientMessage(playerid, COLOR_BLUEGREEN, "   Поставка сырья осуществляется со склада по бизам(компаниям) и товаров из бизов(компаний) на склад!");

			SendClientMessage(playerid, COLOR_BLUEGREEN, "   Продовольствие - основа для производства товаров {FFFFFF}ресторанного бизнеса!");
			SendClientMessage(playerid, COLOR_BLUEGREEN, "   Необходим грузовик 423,588 или прицепы 606,607 c тягачом 485 для перевозки сырья {FFFFFF}ресторанного бизнеса!");
			SendClientMessage(playerid, COLOR_BLUEGREEN, "   Поставка сырья осуществляется со склада по бизам(компаниям) и товаров из бизов(компаний) на склад!");

			SendClientMessage(playerid, COLOR_BLUEGREEN, "   Древесины - основа для производства товаров {FFFFFF}сферы услуг!");
			SendClientMessage(playerid, COLOR_BLUEGREEN, "   Необходим грузовик 478 или прицеп 450 для перевозки сырья {FFFFFF}сферы услуг!");
			SendClientMessage(playerid, COLOR_BLUEGREEN, "   Поставка сырья осуществляется со склада по бизам(компаниям) и товаров из бизов(компаний) на склад!");
			
			SendClientMessage(playerid, COLOR_BLUEGREEN, "   Нефть - основа для производства товара {FFFFFF}промышленной сферы!");
			SendClientMessage(playerid, COLOR_BLUEGREEN, "   Необходим грузовик 524 или прицеп 584 для перевозки сырья {FFFFFF}промышленной сферы!");
			SendClientMessage(playerid, COLOR_BLUEGREEN, "   Вы можете поставлять Нефть из НефтеДобывающей Компании в НефтеПерерабатывающую Компанию!");
			SendClientMessage(playerid, COLOR_BLUEGREEN, "   Вы можете поставлять бензин из НефтеПерерабатывающей Компании на АЗС!");

			SendClientMessage(playerid, COLOR_BLUEGREEN, "   Товар - основа для экспорта любой сферы!");
			SendClientMessage(playerid, COLOR_BLUEGREEN, "   Необходим грузовик категории Station_Wagons(Фургон) для перевозки товаров!");
			SendClientMessage(playerid, COLOR_BLUEGREEN, "   Поставка осуществляется со склада в порт!");
		    return 1;
		}
		new trailerid;//, trailermodel;
		if(IsTrailerAttachedToVehicle(nCarID[playerid]))
		{//если тягач с прицепом
			gTrailerAttached[playerid] = 1;
			trailerid = nTrailerID[playerid]; //trailermodel = nTrailerModel[playerid];
			nTrailerID[playerid] = GetVehicleTrailer(nCarID[playerid]);//Получить ID трейлера прикреплённого к машине.
			nTrailerModel[playerid] = VehInfo[trailerid][cModel];//GetVehicleModel(nTrailerID[playerid]);//Узнает ID модели данного трейлера прикреплённого к машине.
		}
		else
		{//за трейлер выступает самая тачка
			nTrailerID[playerid] = 0;//Получить ID трейлера прикреплённого к машине.
			nTrailerModel[playerid] = 0;//Узнает ID модели данного трейлера прикреплённого к машине.
			trailerid = nCarID[playerid]; //trailermodel = nCarModel[playerid];
		}
	    PlayerInfo[playerid][pCarTime] = 0;//обнуляем при получении задания, т.к. не всегда обнуляется
		Cargo[trailerid][tPeriod] = 0;
 //НАЧАЛО ПОЛУЧЕНИЯ СОСТОЯНИЯ
		GetVehicleHealth(nCarID[playerid], VehHealth[nCarID[playerid]]);
		CurrentTruckHealth[nCarID[playerid]] = VehHealth[nCarID[playerid]];//состояние машины
		StartTruckHealth[nCarID[playerid]] = VehHealth[nCarID[playerid]];//состояние машины на начало доставки груза
		
//format(strings, sizeof(strings), "nCarID:%d nCarModel:%d VehHealth:%.1f nTrailerID:%d nTrailerModel:%d",nCarID[playerid], nCarModel[playerid], VehHealth[nCarID[playerid]], nTrailerID[playerid], nTrailerModel[playerid]);
//SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strings, 6);
		//------------------------------------------------------------------
		//new strings[MAX_STRING];
		//находим сколько влезет в грузовик
		//new amount = 500 - VehInfo[nCarID[playerid]][cLoad];
		new rout = -1; new biz = -1; new sbiz = -1;
		DisablePlayerCheckpointEx(playerid);//CP[playerid] = 0;
//SendAllAdminMessage(ADMINS_MESSAGE_COLOR, "DisablePlayerCheckpointEx", 6);
//==============================================================================
		if( IsPlayerInRangeOfPoint(playerid, 16.0,	BizInfo[81][bEntranceX],BizInfo[81][bEntranceY],BizInfo[81][bEntranceZ]) )
		{//если ты у доков
//1. ПОСТАВКА СЫРЬЯ ИЗ ПОРТА НА СКЛАД
			biz = 81; //break;
			//if(nCarModel[playerid] == 455 || nTrailerModel[playerid] == 591)
			if(GetCargoType(nCarID[playerid], trailerid) == Amusements)
			{
				if(BizInfo[biz][bMetal] <= 0)
				{
	    			format(strings, sizeof(strings), "~r~Metal Out Of Stock in ~p~%s", BizInfo[biz][bDiscription]);
					GameTextForPlayerEx(playerid, strings, 5000, 1);
					PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return 1;
				}
				if(BizInfo[80][bMetal] > LimitMetal)
				{
	    			format(strings, sizeof(strings), "~r~Metal %d>%d ~n~Full Stock in ~p~%s", BizInfo[80][bMetal], LimitMetal, BizInfo[80][bDiscription]);
					GameTextForPlayerEx(playerid, strings, 5000, 1);
					PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return 1;
				}
				Cargo[trailerid][CargoType] = Amusements;//Металл - основа для производства товаров индустрии развлечений
			}
			//else if(nCarModel[playerid] == 456 || nTrailerModel[playerid] == 435)
			else if(GetCargoType(nCarID[playerid], trailerid) == Trade)
			{
				if(BizInfo[biz][bTextiles] <= 0)
				{
	    			format(strings, sizeof(strings), "~r~Textiles Out Of Stock in ~p~%s", BizInfo[biz][bDiscription]);
					GameTextForPlayerEx(playerid, strings, 5000, 1);
					PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return 1;
				}
				if(BizInfo[80][bTextiles] > LimitTextiles)
				{
	    			format(strings, sizeof(strings), "~r~Textiles %d>%d ~n~Full Stock in ~p~%s", BizInfo[80][bTextiles], LimitTextiles, BizInfo[80][bDiscription]);
					GameTextForPlayerEx(playerid, strings, 5000, 1);
					PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return 1;
				}
				Cargo[trailerid][CargoType] = Trade;//Текстиль - основа для производства товаров розничной торговли
			}
			//else if(nCarModel[playerid] == 423 || nCarModel[playerid] == 588 || nTrailerModel[playerid] == 606 || nTrailerModel[playerid] == 607)
			else if(GetCargoType(nCarID[playerid], trailerid) == Restaurant)
			{
				if(BizInfo[biz][bProvisions] <= 0)
				{
	    			format(strings, sizeof(strings), "~r~Provisions Out Of Stock in ~p~%s", BizInfo[biz][bDiscription]);
					GameTextForPlayerEx(playerid, strings, 5000, 1);
					PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return 1;
				}
				if(BizInfo[80][bProvisions] > LimitProvisions)
				{
	    			format(strings, sizeof(strings), "~r~Provisions %d>%d ~n~Full Stock in ~p~%s", BizInfo[80][bProvisions], LimitProvisions, BizInfo[80][bDiscription]);
					GameTextForPlayerEx(playerid, strings, 5000, 1);
					PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return 1;
				}
				Cargo[trailerid][CargoType] = Restaurant;//Продовольствие - основа для производства товаров ресторанного бизнеса
			}
			//else if(nCarModel[playerid] == 478 || nTrailerModel[playerid] == 450)
			else if(GetCargoType(nCarID[playerid], trailerid) == Service)
			{
				if(BizInfo[biz][bTree] <= 0)
				{
	    			format(strings, sizeof(strings), "~r~Tree Out Of Stock in ~p~%s", BizInfo[biz][bDiscription]);
					GameTextForPlayerEx(playerid, strings, 5000, 1);
					PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return 1;
				}
				if(BizInfo[80][bTree] > LimitTree)
				{
	    			format(strings, sizeof(strings), "~r~Tree %d>%d ~n~Full Stock in ~p~%s", BizInfo[80][bTree], LimitTree, BizInfo[80][bDiscription]);
					GameTextForPlayerEx(playerid, strings, 5000, 1);
					PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return 1;
				}
				Cargo[trailerid][CargoType] = Service;//Древесины - основа для производства товаров сферы услуг
			}
			//else if(nCarModel[playerid] == 524 || nTrailerModel[playerid] == 584)
			else if(GetCargoType(nCarID[playerid], trailerid) == Industry)
			{
				if(BizInfo[biz][bFuel] <= 0)
				{
	    			format(strings, sizeof(strings), "~r~Fuel Out Of Stock in ~p~%s", BizInfo[biz][bDiscription]);
					GameTextForPlayerEx(playerid, strings, 5000, 1);
					PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return 1;
				}
				if(BizInfo[80][bFuel] > LimitFuel)
				{
	    			format(strings, sizeof(strings), "~r~Fuel %d>%d ~n~Full Stock in ~p~%s", BizInfo[80][bFuel], LimitFuel, BizInfo[80][bDiscription]);
					GameTextForPlayerEx(playerid, strings, 5000, 1);
					PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return 1;
				}
				Cargo[trailerid][CargoType] = Industry;//Нефть - основа для производства товара промышленной сферы
			}
			else
			{
				SendClientMessage(playerid, COLOR_BLUEGREEN, "   Порт не может продовать обратно складу товар. Товар хранящийся в Порту подлежит экспорту.");
				SendClientMessage(playerid, COLOR_BLUEGREEN, "   Загрузку товаров на грузовое судно осуществляют грузчики.");
				SendClientMessage(playerid, COLOR_BLUEGREEN, "   Допускается вывоз товаров из бизнесов и со склада.");
			    return 1;
			}
			Cargo[trailerid][tWhence] = biz;//откуда
			Cargo[trailerid][tWhere] = 80;//куда
		}
		else if( IsPlayerInRangeOfPoint(playerid, 16.0,	BizInfo[80][bEntranceX],BizInfo[80][bEntranceY],BizInfo[80][bEntranceZ]) )
		{   //если ты у склада
//==============================================================================
//2. ПОСТАВКА ТОВАРОВ СО СКЛАДА В ПОРТ. Цена продажи Складом увеличивается в 3 раза. Цена покупки Портом увеличивается в 4 раза
//3. ПОСТАВКА СЫРЬЯ СО СКЛАДА ПО БИЗАМ
//6. ПОСТАВКА НЕФТИ СО СКЛАДА НА АЗС
			biz = 80; //break;
//SendAllAdminMessage(ADMINS_MESSAGE_COLOR, "3. ПОСТАВКА СЫРЬЯ СО СКЛАДА ПО БИЗАМ", 6);
			//if(nCarModel[playerid] == 455 || nTrailerModel[playerid] == 591)
			if(GetCargoType(nCarID[playerid], trailerid) == Amusements)
			{//согласно типа прицепа будем выбирать какой грузить товар
				if(BizInfo[biz][bMetal] <= 0)
				{
	    			format(strings, sizeof(strings), "~r~Metal Out Of Stock in ~p~%s", BizInfo[biz][bDiscription]);
					GameTextForPlayerEx(playerid, strings, 5000, 1);
					PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return 1;
				}
//Формируем направление куда отвезти металл
				//выбираем из всех бизов что принимают металл с лучшей ценой покупки
				new best_price;
				for(new b = 1; b < MAX_BIZ; b++)//MAX_BIZ
				{
				    if(b == biz) continue;//пропускаем самого себя
					//if(BizInfo[b][bOwned] == 0) continue;//пропускаем не купленные
					if(BizInfo[b][bLock] == 1) continue;//пропускаем закрытые
					if(BizInfo[b][bBranch] != Amusements) continue;//пропускаем которые не относятся к сфере индустрии развлечений
					if(BizInfo[b][bMetal] >= 30000) continue;//пропускам с кол-вом сырья больше 30к
					if(BizInfo[b][bBuyProd] <= BizInfo[biz][bSellProd]) continue;//пропускаем бизы с ценой покупки меньше цены продажи склада
					new SellPrice = floatround( (100 * compcost*(100+BizInfo[b][bBuyProd])/100.0), floatround_floor );
//находим цену покупки бизом
					if(BizInfo[b][bTill] <= SellPrice || BizInfo[b][bTill] < 2250) continue;//пропускам с кассой меньшей цены покупки

					if(b <= Cargo[trailerid][tWhere]) continue;//для кнопки NEXT пропускаем предыдущий
					if(BizInfo[b][bBuyProd] > best_price)
					{//находим лучшее предложение покупки
						best_price = BizInfo[b][bBuyProd];
						rout = b;//КУДА
					}
				}
				if(rout == -1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Нет бизнесов индустрии развлечений способных купить хотя бы 100 ед. металла !");
					SendClientMessage(playerid, COLOR_GREY, "   Пожалуйста смените тип прицепа !");
					TruckerCargoInit(playerid);
					return 1;
				}
				Cargo[trailerid][CargoType] = Amusements;//Металл - основа для производства товаров индустрии развлечений
				Cargo[trailerid][tFrailty] = BizList[rout][cFrailty];
			}
			//else if(nCarModel[playerid] == 456 || nTrailerModel[playerid] == 435)
			else if(GetCargoType(nCarID[playerid], trailerid) == Trade)
			{
				if(BizInfo[biz][bTextiles] <= 0)
				{
	    			format(strings, sizeof(strings), "~r~Textiles Out Of Stock in ~p~%s", BizInfo[biz][bDiscription]);
					GameTextForPlayerEx(playerid, strings, 5000, 1);
					PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return 1;
				}
				new best_price;
				for(new b = 1; b < MAX_BIZ; b++)
				{
					if(b == biz) continue;
					//if(BizInfo[b][bOwned] == 0) continue;
					if(BizInfo[b][bLock] == 1) continue;
					if(BizInfo[b][bBranch] != Trade) continue;
					if(BizInfo[b][bTextiles] >= 30000) continue;//пропускам с кол-вом сырья на больше 30к
					if(BizInfo[b][bBuyProd] <= BizInfo[biz][bSellProd]) continue;
					new SellPrice = floatround( 100 * compcost*(100+BizInfo[b][bBuyProd])/100.0, floatround_floor );
					if(BizInfo[b][bTill] <= SellPrice) continue;//пропускам с кассой которая не может оплатить 100 продов
					if(b <= Cargo[trailerid][tWhere]) continue;//пропускаем предыдущий
					if(BizInfo[b][bBuyProd] > best_price)
					{
						best_price = BizInfo[b][bBuyProd];
						rout = b;
					}
				}
				if(rout == -1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Нет бизнесов розничной торговли способных купить хотя бы 100 ед. текстиля !");
					SendClientMessage(playerid, COLOR_GREY, "   Пожалуйста смените тип прицепа !");
					TruckerCargoInit(playerid);
					return 1;
				}
				Cargo[trailerid][CargoType] = Trade;//Текстиль - основа для производства товаров розничной торговли
				Cargo[trailerid][tFrailty] = BizList[rout][cFrailty];
			}
			//else if(nCarModel[playerid] == 423 || nCarModel[playerid] == 588 || nTrailerModel[playerid] == 606 || nTrailerModel[playerid] == 607)
			else if(GetCargoType(nCarID[playerid], trailerid) == Restaurant)
			{
				if(BizInfo[biz][bProvisions] <= 0)
				{
	    			format(strings, sizeof(strings), "~r~Provisions Out Of Stock in ~p~%s", BizInfo[biz][bDiscription]);
					GameTextForPlayerEx(playerid, strings, 5000, 1);
					PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return 1;
				}
				new best_price;
				for(new b = 1; b < MAX_BIZ; b++)
				{
					if(b == biz) continue;
					//if(BizInfo[b][bOwned] == 0) continue;
					if(BizInfo[b][bLock] == 1) continue;
					if(BizInfo[b][bBranch] != Restaurant) continue;
					if(BizInfo[b][bProvisions] >= 30000) continue;//пропускам с кол-вом сырья на больше 30к
					if(BizInfo[b][bBuyProd] <= BizInfo[biz][bSellProd]) continue;
					new SellPrice = floatround( 100 * compcost*(100+BizInfo[b][bBuyProd])/100.0, floatround_floor );
					if(BizInfo[b][bTill] <= SellPrice) continue;//пропускам с кассой которая не может оплатить 100 продов
					if(b <= Cargo[trailerid][tWhere]) continue;//пропускаем предыдущий
					if(BizInfo[b][bBuyProd] > best_price)
					{
						best_price = BizInfo[b][bBuyProd];
						rout = b;
					}
				}
				if(rout == -1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Нет бизнесов ресторанной сферы способных купить хотя бы 100 ед. продовольствия !");
					SendClientMessage(playerid, COLOR_GREY, "   Пожалуйста смените тип прицепа !");
					TruckerCargoInit(playerid);
					return 1;
				}
				Cargo[trailerid][CargoType] = Restaurant;//Продовольствие - основа для производства товаров ресторанного бизнеса
				Cargo[trailerid][tFrailty] = BizList[rout][cFrailty];
			}
			//else if(nCarModel[playerid] == 478 || nTrailerModel[playerid] == 450)
			else if(GetCargoType(nCarID[playerid], trailerid) == Service)
			{
				if(BizInfo[biz][bTree] <= 0)
				{
	    			format(strings, sizeof(strings), "~r~Tree Out Of Stock in ~p~%s", BizInfo[biz][bDiscription]);
					GameTextForPlayerEx(playerid, strings, 5000, 1);
					PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return 1;
				}
				new best_price;
				for(new b = 1; b < MAX_BIZ; b++)
				{
					if(b == biz) continue;
					//if(BizInfo[b][bOwned] == 0) continue;
					if(BizInfo[b][bLock] == 1) continue;
					if(BizInfo[b][bBranch] != Service) continue;
					if(BizInfo[b][bTree] >= 30000) continue;//пропускам с кол-вом сырья на больше 30к
					if(BizInfo[b][bBuyProd] <= BizInfo[biz][bSellProd]) continue;
					new SellPrice = floatround( 100 * compcost*(100+BizInfo[b][bBuyProd])/100.0, floatround_floor );
					if(BizInfo[b][bTill] <= SellPrice) continue;//пропускам с кассой которая не может оплатить 100 продов
					if(b <= Cargo[trailerid][tWhere]) continue;//пропускаем предыдущий
					if(BizInfo[b][bBuyProd] > best_price)
					{//даже если бизнесы все в минусах то мы попытаемся найти лучшего их них
						best_price = BizInfo[b][bBuyProd];
						rout = b;
					}
				}
				if(rout == -1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Нет бизнесов сферы услуг способных купить хотя бы 100 ед. древесины !");
					SendClientMessage(playerid, COLOR_GREY, "   Пожалуйста смените тип прицепа !");
					TruckerCargoInit(playerid);
					return 1;
				}
				Cargo[trailerid][CargoType] = Service;//Древесины - основа для производства товаров сферы услуг
				Cargo[trailerid][tFrailty] = BizList[rout][cFrailty];
			}
			//else if(nCarModel[playerid] == 524 || nTrailerModel[playerid] == 584)
			else if(GetCargoType(nCarID[playerid], trailerid) == Industry)
			{
//SendAllAdminMessage(ADMINS_MESSAGE_COLOR, "6. ПОСТАВКА НЕФТИ СО СКЛАДА НА АЗС", 6);
//6. ПОСТАВКА НЕФТИ СО СКЛАДА НА АЗС
				if(BizInfo[biz][bFuel] <= 0)
				{
	    			format(strings, sizeof(strings), "~r~Fuel Out Of Stock in ~p~%s", BizInfo[biz][bDiscription]);
					GameTextForPlayerEx(playerid, strings, 5000, 1);
					PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return 1;
				}
				new best_price;
				for(new sb = GAS_STATION; sb < PARKING; sb++)//для информации по компаниям
				{//сканируем все заправки у которых лучшая цена покупки
					if(sb == biz) continue;
					//if(SBizInfo[sb][sbOwned] == 0) continue;
					if(SBizInfo[sb][sbLock] == 1) continue;
					if(SBizInfo[sb][sbBranch] != Industry) continue;
					//if(SBizInfo[sb][sbProducts] >= 30000) continue;//пропускам с кол-вом сырья на больше 30к
					if(SBizInfo[sb][sbBuyProd] <= BizInfo[biz][bSellProd]) continue;//пропускаем АЗС с покупкой меньше цены продажи склада
					new SellPrice = floatround( 100 * compcost*(100+SBizInfo[sb][sbBuyProd])/100.0, floatround_floor);
					if(SBizInfo[sb][sbTill] <= SellPrice) continue;//пропускам с кассой менее 100 продов
					if(sb <= (Cargo[trailerid][tWhere]-100)) continue;//пропускаем предыдущий
					if(SBizInfo[sb][sbBuyProd] > best_price)
					{
						best_price = SBizInfo[sb][sbBuyProd];
						rout = sb+100;
					}
					//rout = sb+100;
//printf("rout: %d", rout);
				}
				if(rout == -1)
				{//если напраление не изменилось
					SendClientMessage(playerid, COLOR_GREY, "   Нет бизнесов промышленной сферы способных купить хотя бы 100 ед. нефти !");
					SendClientMessage(playerid, COLOR_GREY, "   Пожалуйста смените тип прицепа !");
					TruckerCargoInit(playerid);
					return 1;
				}
				Cargo[trailerid][CargoType] = Industry;//Нефть - основа для производства товара промышленной сферы
				Cargo[trailerid][tFrailty] = 10;//BizList[biz][cFrailty];//SBizList[rout-100][cFrailty] = 10;//хрупкость в процентах;
			}
			else
			{
//SendAllAdminMessage(ADMINS_MESSAGE_COLOR, "2. ПОСТАВКА ТОВАРОВ СО СКЛАДА В ПОРТ.", 6);
//2. ПОСТАВКА ТОВАРОВ СО СКЛАДА В ПОРТ. Цена продажи Складом увеличивается в 3 раза. Цена покупки Портом увеличивается в 4 раза
				if(BizInfo[biz][bProducts] <= 0)
				{
	    			format(strings, sizeof(strings), "~r~Out Of Stock in ~p~%s", BizInfo[biz][bDiscription]);
					GameTextForPlayerEx(playerid, strings, 5000, 1);
					PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return 1;
				}
				//if(VehicleArray[nCarModel[playerid]-400][Category] != Station_Wagons)
				if(GetCargoType(nCarID[playerid], trailerid) != Station_Wagons)
				{   //если Вы сели в грузовик
					SendClientMessage(playerid, COLOR_BLUEGREEN, "   Товар - основа для экспорта любой сферы!");
					SendClientMessage(playerid, COLOR_BLUEGREEN, "   Необходим грузовик категории Station_Wagons(Фургон) для перевозки товаров (USE: /carinfo)!");
				    return 1;
				}
				rout = 81;
				Cargo[trailerid][CargoType] = Station_Wagons;//товары на экспорт
				Cargo[trailerid][tFrailty] = BizList[rout][cFrailty];
			}
			//------------------------------------------------------------------
			Cargo[trailerid][tWhence] = 80;//откуда
			//SelectRout[playerid] = rout;
			Cargo[trailerid][tWhere] = rout;//куда

//ИНФОРМИРОВАНИЕ
//format(strings, sizeof(strings), "4. Откуда: %d, Куда: %d Груз: %d", Cargo[trailerid][tWhence], Cargo[trailerid][tWhere], Cargo[trailerid][CargoType]);
//print(strings);
//SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strings, 6);
		}
		else
		{
	//4. ПОСТАВКА ТОВАРОВ ИЗ БИЗОВ НА СКЛАД
			for(new b = 1; b < (MAX_BIZ-2); b++)//пропускаем банк доки и склад
			{   //находим у какого биза стоит сейчас игрок
				//сначало обязательно сканируем по мирам т.к. может быть одна и таже точка в одном месте
				if(BizInfo[b][bOwned] == 0) continue;
				//if(BizInfo[b][bLock] == 1) continue;//пропускаем закрытые
				if(PlayerInfo[playerid][pVirtual] != 0) continue;
				if(PlayerInfo[playerid][pLocal] != FREEROAM) continue;
				if( !IsPlayerInRangeOfPoint(playerid, 16.0, BizInfo[b][bEntranceX],BizInfo[b][bEntranceY],BizInfo[b][bEntranceZ]) ) continue;

				biz = b;
				if(BizInfo[biz][bProducts] <= 0)
				{
	    			format(strings, sizeof(strings), "~r~Out Of Stock in ~p~%s", BizInfo[biz][bDiscription]);
					GameTextForPlayerEx(playerid, strings, 5000, 1);
					PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return 1;
				}

				if(BizInfo[biz][bBranch] == Amusements)
				{//Металл - основа для производства товаров индустрии развлечений
					if(nCarModel[playerid] != 455 && nTrailerModel[playerid] != 591)
					{
						SendClientMessage(playerid, COLOR_GREY, "   Ваш прицеп отсутствует или не соответствует перевозимому грузу!");
						SendClientMessage(playerid, COLOR_GREY, "   Необходим грузовик 455 или прицеп 591 для перевозки товаров индустрии развлечений!");
					    return 1;
					}
					Cargo[trailerid][CargoType] = 6;
				}
				else if(BizInfo[biz][bBranch] == Trade)
				{//Текстиль - основа для производства товаров розничной торговли
					if(nCarModel[playerid] != 456 && nTrailerModel[playerid] != 435)
					{
						SendClientMessage(playerid, COLOR_GREY, "   Ваш прицеп отсутствует или не соответствует перевозимому грузу!");
						SendClientMessage(playerid, COLOR_GREY, "   Необходим грузовик 456 или прицеп 435 для перевозки товаров розничной торговли!");
					    return 1;
					}
					Cargo[trailerid][CargoType] = 6;
				}
				else if(BizInfo[biz][bBranch] == Restaurant)
				{//Продовольствие - основа для производства товаров ресторанного бизнеса
					if(nCarModel[playerid] != 423 && nCarModel[playerid] != 588 && nTrailerModel[playerid] != 606 && nTrailerModel[playerid] != 607)
					{
						SendClientMessage(playerid, COLOR_GREY, "   Ваш прицеп отсутствует или не соответствует перевозимому грузу!");
						SendClientMessage(playerid, COLOR_GREY, "   Необходим грузовик 423,588 или прицепы 606,607 c тягачом 485 для перевозки товаров ресторанного бизнеса!");
					    return 1;
					}
					Cargo[trailerid][CargoType] = 6;
				}
				else if(BizInfo[biz][bBranch] == Service)
				{//Древесины - основа для производства товаров сферы услуг
					if(nCarModel[playerid] != 478 && nTrailerModel[playerid] != 450)
					{
						SendClientMessage(playerid, COLOR_GREY, "   Ваш прицеп отсутствует или не соответствует перевозимому грузу!");
						SendClientMessage(playerid, COLOR_GREY, "   Необходим грузовик 478 или прицеп 450 для перевозки товаров сферы услуг!");
					    return 1;
					}
					Cargo[trailerid][CargoType] = 6;
				}
				else if(BizInfo[biz][bBranch] == Industry)
				{//Нефть - основа для производства товара промышленной сферы
					if(nCarModel[playerid] != 524 && nTrailerModel[playerid] != 584)
					{
						SendClientMessage(playerid, COLOR_GREY, "   Ваш прицеп отсутствует или не соответствует перевозимому грузу!");
						SendClientMessage(playerid, COLOR_GREY, "   Необходим грузовик 524 или прицеп 584 для перевозки товаров промышленной сферы!");
					    return 1;
					}
					Cargo[trailerid][CargoType] = 6;
				}
				else
				{
					if(VehicleArray[nCarModel[playerid]-400][Category] != Station_Wagons)
					{   //если Вы сели в грузовик
						SendClientMessage(playerid, COLOR_BLUEGREEN, "   Товар - основа для экспорта любой сферы!");
						SendClientMessage(playerid, COLOR_BLUEGREEN, "   Необходимо авто категории Station_Wagons(Фургон) для перевозки товаров (USE: /carinfo)!");
					    return 1;
					}
	    			Cargo[trailerid][CargoType] = 6;
				}
				Cargo[trailerid][tWhence] = biz;//откуда
				Cargo[trailerid][tWhere] = 80;//куда
				Cargo[trailerid][tFrailty] = BizList[biz][cFrailty];//хрупкость биза откуда берём груз
				break;
			}
	//==============================================================================
	//5. ПОСТАВКА СЫРЬЯ ИЗ КОМПАНИЙ НА СКЛАД
			for(new sb=0; sb<MAX_SBIZ; sb++)
			{   //находим у какой компании стоит сейчас игрок
				//сначало обязательно сканируем по мирам т.к. может быть одна и таже точка в одном месте
				if(SBizInfo[sb][sbLock] == 1) continue;//пропускаем закрытые
				if(sb >= GAS_STATION && sb < PARKING+sizeof(Parking)) continue;//пропускам заправки и паркинги
				//if(SBizInfo[sb][sbOwned] == 0 && !gTutorial[playerid]) continue;//после вайпа в обучении не будет работать
				if(PlayerInfo[playerid][pVirtual] != 0) continue;
				if(PlayerInfo[playerid][pLocal] != FREEROAM) continue;
				if( !IsPlayerInRangeOfPoint(playerid, 16.0,	SBizInfo[sb][sbEntranceX],SBizInfo[sb][sbEntranceY],SBizInfo[sb][sbEntranceZ]) ) continue;

				sbiz = sb;
				if(SBizInfo[sbiz][sbProducts] <= 0)
				{
	    			format(strings, sizeof(strings), "~r~Out Of Stock in ~p~%s", SBizInfo[sbiz][sbDiscription]);
					GameTextForPlayerEx(playerid, strings, 5000, 1);
					PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return 1;
				}
				if(SBizInfo[sbiz][sbBranch] == Amusements)
				{//Металл - основа для производства товаров индустрии развлечений
					if(nCarModel[playerid] != 455 && nTrailerModel[playerid] != 591)
					{
						SendClientMessage(playerid, COLOR_GREY, "   Ваш прицеп отсутствует или не соответствует перевозимому грузу!");
						SendClientMessage(playerid, COLOR_GREY, "   Необходим грузовик 455 или прицеп 591 для перевозки товаров индустрии развлечений!");
					    return 1;
					}
					if(BizInfo[80][bMetal] > LimitMetal)
					{
		    			format(strings, sizeof(strings), "~r~Metal %d>%d ~n~Full Stock in ~p~%s", BizInfo[80][bMetal], LimitMetal, BizInfo[80][bDiscription]);
						GameTextForPlayerEx(playerid, strings, 5000, 1);
						PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
						return 1;
					}
					Cargo[trailerid][CargoType] = Amusements;
				}
				else if(SBizInfo[sbiz][sbBranch] == Trade)
				{//Текстиль - основа для производства товаров розничной торговли
					if(nCarModel[playerid] != 456 && nTrailerModel[playerid] != 435)
					{
						SendClientMessage(playerid, COLOR_GREY, "   Ваш прицеп отсутствует или не соответствует перевозимому грузу!");
						SendClientMessage(playerid, COLOR_GREY, "   Необходим грузовик 456 или прицеп 435 для перевозки товаров розничной торговли!");
					    return 1;
					}
					if(BizInfo[80][bTextiles] > LimitTextiles)
					{
		    			format(strings, sizeof(strings), "~r~Textiles Full Stock in ~p~%s", BizInfo[80][bDiscription]);
						GameTextForPlayerEx(playerid, strings, 5000, 1);
						PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
						return 1;
					}
					Cargo[trailerid][CargoType] = Trade;
				}
				else if(SBizInfo[sbiz][sbBranch] == Restaurant)
				{//Продовольствие - основа для производства товаров ресторанного бизнеса
					if(nCarModel[playerid] != 423 && nCarModel[playerid] != 588 && nTrailerModel[playerid] != 606 && nTrailerModel[playerid] != 607)
					{
						SendClientMessage(playerid, COLOR_GREY, "   Ваш прицеп отсутствует или не соответствует перевозимому грузу!");
						SendClientMessage(playerid, COLOR_GREY, "   Необходим грузовик 423,588 или прицепы 606,607 c тягачом 485 для перевозки товаров ресторанного бизнеса!");
					    return 1;
					}
					if(BizInfo[80][bProvisions] > LimitProvisions)
					{
		    			format(strings, sizeof(strings), "~r~Provisions %d>%d ~n~Full Stock in ~p~%s", BizInfo[80][bProvisions], LimitProvisions, BizInfo[80][bDiscription]);
						GameTextForPlayerEx(playerid, strings, 5000, 1);
						PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
						return 1;
					}
					Cargo[trailerid][CargoType] = Restaurant;
				}
				else if(SBizInfo[sbiz][sbBranch] == Service)
				{//Древесины - основа для производства товаров сферы услуг
					if(nCarModel[playerid] != 478 && nTrailerModel[playerid] != 450)
					{
						SendClientMessage(playerid, COLOR_GREY, "   Ваш прицеп отсутствует или не соответствует перевозимому грузу!");
						SendClientMessage(playerid, COLOR_GREY, "   Необходим грузовик 478 или прицеп 450 для перевозки товаров сферы услуг!");
					    return 1;
					}
					if(BizInfo[80][bTree] > LimitTree)
					{
		    			format(strings, sizeof(strings), "~r~Tree Full Stock in ~p~%s", BizInfo[80][bDiscription]);
						GameTextForPlayerEx(playerid, strings, 5000, 1);
						PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
						return 1;
					}
					Cargo[trailerid][CargoType] = Service;
				}
				else if(SBizInfo[sbiz][sbBranch] == Industry)
				{//Нефть - основа для производства товара промышленной сферы
					if(nCarModel[playerid] != 524 && nTrailerModel[playerid] != 584)
					{
						SendClientMessage(playerid, COLOR_GREY, "   Ваш прицеп отсутствует или не соответствует перевозимому грузу!");
						SendClientMessage(playerid, COLOR_GREY, "   Необходим грузовик 524 или прицеп 584 для перевозки товаров промышленной сферы!");
					    return 1;
					}
					if(BizInfo[80][bFuel] > LimitFuel)
					{
		    			format(strings, sizeof(strings), "~r~Fuel %d>%d ~n~Full Stock in ~p~%s", BizInfo[80][bFuel], LimitFuel, BizInfo[80][bDiscription]);
						GameTextForPlayerEx(playerid, strings, 5000, 1);
						PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
						return 1;
					}
					Cargo[trailerid][CargoType] = Industry;
				}
				else
				{
					if(VehicleArray[nCarModel[playerid]-400][Category] != Station_Wagons)
					{   //если Вы сели в грузовик
						SendClientMessage(playerid, COLOR_BLUEGREEN, "   Товар - основа для экспорта любой сферы!");
						SendClientMessage(playerid, COLOR_BLUEGREEN, "   Необходимо авто категории Station_Wagons(Фургон) для перевозки товаров (USE: /carinfo)!");
					    return 1;
					}
	    			Cargo[trailerid][CargoType] = SBizInfo[sbiz][sbBranch];
				}
				Cargo[trailerid][tWhence] = sbiz+100;//откуда
				Cargo[trailerid][tWhere] = 80;//куда
				Cargo[trailerid][tFrailty] = SBizList[sbiz][cFrailty];//хрупкость биза откуда берём груз
				break;
			}
		}
//==============================================================================
		if(biz <= 0 && sbiz < 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы далеко от места загрузки !");
			TruckerCargoInit(playerid);
		    return 1;
		}
		if(VehInfo[trailerid][cLoad] > 0 && VehInfo[trailerid][cLoadType] != Cargo[trailerid][CargoType])
		{
			SendClientMessage(playerid, COLOR_RED, "Тип груза не соответствует загруженному типу !");
			SendClientMessage(playerid, COLOR_GREY, "   Введи /load, чтобы проверить кол-во и тип груза !");
			SendClientMessage(playerid, COLOR_GREY, "   Вы можете грузить только тот тип груза, что у вас загружен до тех пор, пока полностью не разгрузитесь !");
			TruckerCargoInit(playerid);
		    return 1;
		}
//==============================================================================
		CreateCargoLoadingDialog(playerid);//для дальнобойщиков STEP3
//==============================================================================
		gTextDrawShowCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);//txdCarTime

        //distance_to_point = VehInfo[nCarID[playerid]][cDist] + Cargo[trailerid][tDistance];
		CargoInfoTime(playerid, trailerid);
//==============================================================================
		return 1;
}

//Формируем диалог создания груза
stock CreateCargoLoadingDialog(playerid)//для дальнобойщиков STEP3
{   //вызывается  из trucker_OnPlayerKeyState_UP //biz - ОТКУДА
//==============================================================================
	//new Float: distance;
	//new Float: K_mediumspeed = 1.3;//1.15 коэф средней скорости
	new Float: K_mediumspeed = 3.0;//коэф. криволинейности пути
	new speed = VehicleArray[nCarModel[playerid]-400][LineSpeed];//средняя скорость /2  км/ч
	
	new trailerid, trailermodel;
	if(IsTrailerAttachedToVehicle(nCarID[playerid])) { trailerid = nTrailerID[playerid]; trailermodel = nTrailerModel[playerid]; }
	else { trailerid = nCarID[playerid]; trailermodel = nCarModel[playerid]; }
	
	//new rout = Cargo[trailerid][tWhere];
	new amount, amount2, products, maxload, salary;
	new discription[10+20];//откуда
	new WhereDiscription[10+20];//куда
	//strcat(discription, "Откуда: ");//начало формирования заголовка диалога
	//--------------------------------------------------------------------------
//РАСЧЁТ ЦЕНЫ ПО КОТОРОЙ ДАЛЬНОБОЙЩИК КУПИТ
	new biz, sbiz;
	if(Cargo[trailerid][tWhence] >= 100)//откуда
	{
//5. ПОСТАВКА СЫРЬЯ ИЗ КОМПАНИЙ
		strcat(discription, "5. ПОСТАВКА СЫРЬЯ ИЗ: ");
		sbiz = Cargo[trailerid][tWhence]-100;//откуда

		if(Cargo[trailerid][CargoType] == Industry) { Cargo[trailerid][tBuyPrice] = FuelCost*SBizInfo[sbiz][sbSellProd]/100.0; Cargo[trailerid][tFrailty] = 10; }
		else { Cargo[trailerid][tBuyPrice] = compcost*(100+SBizInfo[sbiz][sbSellProd])/100.0; Cargo[trailerid][tFrailty] = SBizList[sbiz][cFrailty]; }

		strcat(discription, SBizInfo[sbiz][sbDiscription]);
		products = SBizInfo[sbiz][sbProducts];
		//price = compcost*(100+SBizInfo[sbiz][sbSellProd])/100.0;
		amount = floatround( GetPlayerMoneyH(playerid)/Cargo[trailerid][tBuyPrice], floatround_floor);
/*Description:
The rounding method used with floatround.
floatround_round	Round to the nearest integer. A fractional part of exactly 0.5 rounds upwards (this is the default).
floatround_floor	Round downwards.
floatround_ceil	Round upwards.
floatround_tozero	Round downwards for positive values and upwards for negative values (“truncate”).*/
		if(products < amount) amount = products;
		//cost = floatround( amount * compcost*price/100.0 );

		salary = SBizInfo[sbiz][sbSalary];//Гонорар оплачивает продавец
	}
	else {
		biz = Cargo[trailerid][tWhence];//откуда
		if(biz == 80 && Cargo[trailerid][tWhere] == 81)
		{//если со склада в порт
//2. ПОСТАВКА НЕФТИ СО СКЛАДА В ПОРТ
			if(Cargo[trailerid][CargoType] == Industry)
			{//тип - нефть
				strcat(discription, "2. ПОСТАВКА НЕФТИ СО СКЛАДА В ПОРТ: ");
				Cargo[trailerid][tBuyPrice] = FuelCost*BizInfo[biz][bSellProd]*3/100.0; Cargo[trailerid][tFrailty] = 10; }
			else
			{//тип топливо
				strcat(discription, "2. ПОСТАВКА ТОПЛИВА СО СКЛАДА В ПОРТ: ");
//2. ПОСТАВКА ТОВАРОВ СО СКЛАДА В ПОРТ. Цена продажи Складом увеличивается в 2 раза. Цена покупки Портом сразу выставляется 100%
				Cargo[trailerid][tBuyPrice] = compcost*(100+BizInfo[biz][bSellProd]*2+10)/100.0;//CompCost:$15
//15*(100+30*2+10)/100 = 25,5
				if((BizInfo[biz][bSellProd]*2+10) > 80) Cargo[trailerid][tBuyPrice] = compcost*(100+80)/100.0;
//if( 40*2+10 > 80) Cargo[trailerid][tBuyPrice] = 15*(100+80)/100 = 27
				Cargo[trailerid][tFrailty] = BizList[biz][cFrailty];
			}
		}
		else
		{//если с
//6. ПОСТАВКА НЕФТИ СО СКЛАДА НА АЗС
			if(Cargo[trailerid][CargoType] == Industry)
			{
				strcat(discription, "6. ПОСТАВКА ТОПЛИВА НА АЗС: ");
				Cargo[trailerid][tBuyPrice] = FuelCost*BizInfo[biz][bSellProd]/100.0;
			}
//1. ПОСТАВКА СЫРЬЯ ИЗ ПОРТА НА СКЛАД
//3. ПОСТАВКА СЫРЬЯ СО СКЛАДА ПО БИЗАМ
//4. ПОСТАВКА ТОВАРОВ ИЗ БИЗОВ НА СКЛАД
			else
			{
				strcat(discription, "1.3.4. ПОСТАВКА ИЗ: ");
				Cargo[trailerid][tBuyPrice] = compcost*(100+BizInfo[biz][bSellProd])/100.0;
			}
		}

//если поставка с биза на склад или с порта на склад или со склада на биз или со склада на порт или со склада на компанию
		strcat(discription, BizInfo[biz][bDiscription]);

		/*if(Cargo[trailerid][CargoType] == Amusements) products = BizInfo[biz][bMetal];
		else if(Cargo[trailerid][CargoType] == Trade) products = BizInfo[biz][bTextiles];
		else if(Cargo[trailerid][CargoType] == Restaurant) products = BizInfo[biz][bProvisions];
		else if(Cargo[trailerid][CargoType] == Service) products = BizInfo[biz][bTree];
		else if(Cargo[trailerid][CargoType] == Industry) products = BizInfo[biz][bFuel];
		else products = BizInfo[biz][bProducts];*/
		products = GetProducts(biz);
		
		//находим сколько сможет оплатить
//находим сколько может оплатить дальнобойщик
		amount = floatround( GetPlayerMoneyH(playerid)/Cargo[trailerid][tBuyPrice], floatround_floor);
		if(products < amount) amount = products;
		//если продуктов меньше чем может купить то

		salary = BizInfo[biz][bSalary];//Гонорар оплачивает продавец
	}

//==============================================================================
//РАСЧЁТ ЦЕНЫ ПО КОТОРОЙ ДАЛЬНОБОЙЩИК ПРОДАСТ
	if(Cargo[trailerid][tWhere] >= 100)//куда
	{
		sbiz = Cargo[trailerid][tWhere]-100;//куда
//6. ПОСТАВКА НЕФТИ СО СКЛАДА НА АЗС
		if(Cargo[trailerid][CargoType] == Industry) Cargo[trailerid][tSellPrice] = FuelCost*SBizInfo[sbiz][sbBuyProd]/100.0;
//6. ПОСТАВКА ... СО СКЛАДА НА ...
		else Cargo[trailerid][tSellPrice] = compcost*(100+SBizInfo[sbiz][sbBuyProd])/100.0;

//3.0 - коэф на криволинейность пути
		Cargo[trailerid][tDistance] =
		//distance =
			GetPlayerDistanceFromPoint(playerid,
			SBizInfo[sbiz][sbEntranceX],
			SBizInfo[sbiz][sbEntranceY],
			SBizInfo[sbiz][sbEntranceZ]);//км

//находим сколько может оплатить биз что покупает груз
		amount2 = floatround(SBizInfo[sbiz][sbTill]/Cargo[trailerid][tSellPrice], floatround_floor);
		if(amount2 < amount) amount = amount2;//если кол-во меньше чем может купить дальнобойщик, то установить меньшее кол-во для возможной загрузки
		strcat(WhereDiscription, SBizInfo[sbiz][sbDiscription]);
	}
	else
	{
		biz = Cargo[trailerid][tWhere];//куда
		if(biz == 80 && (Cargo[trailerid][tWhence] < 100 || Cargo[trailerid][tWhence] == 154) && Cargo[trailerid][tWhence] != 81)
		{//если на склад c бизов или с MushroomVault, но не с порта
//4. ПОСТАВКА ТОВАРОВ ИЗ БИЗОВ НА СКЛАД. Цена покупки Складом увеличивается в 3 раза
//4. ПОСТАВКА ГРИБОВ НА СКЛАД. Цена покупки Складом увеличивается в 3 раза
			Cargo[trailerid][tSellPrice] = compcost*(100+BizInfo[biz][bBuyProd]*3)/100.0;
			if(BizInfo[biz][bBuyProd]*3 > 70) Cargo[trailerid][tSellPrice] = compcost*(100+70)/100.0;
		}
		else
		{
//6. ПОСТАВКА НЕФТИ ИЗ КОМПАНИЙ НА СКЛАД
			if(Cargo[trailerid][CargoType] == Industry) Cargo[trailerid][tSellPrice] = FuelCost*BizInfo[biz][bBuyProd]/100.0;//по чём я продам

//1. ПОСТАВКА СЫРЬЯ ИЗ ПОРТА НА СКЛАД
//2. ПОСТАВКА ТОВАРОВ СО СКЛАДА В ПОРТ. Цена продажи Складом увеличивается в 3 раза. Цена покупки Портом сразу выставляется 100%
//3. ПОСТАВКА СЫРЬЯ СО СКЛАДА ПО БИЗАМ
//5. ПОСТАВКА СЫРЬЯ ИЗ КОМПАНИЙ НА СКЛАД
			else Cargo[trailerid][tSellPrice] = compcost*(100+BizInfo[biz][bBuyProd])/100.0;//по чём я продам
//Cargo[trailerid][tSellPrice] = 15*(100+80)/100 = 27
		}

		Cargo[trailerid][tDistance] =
		//distance =
			GetPlayerDistanceFromPoint(playerid,
			BizInfo[biz][bEntranceX],
			BizInfo[biz][bEntranceY],
			BizInfo[biz][bEntranceZ]);//км

//находим сколько может оплатить биз что покупает груз
		amount2 = floatround(BizInfo[biz][bTill]/Cargo[trailerid][tSellPrice], floatround_floor);
		if(amount2 < amount) amount = amount2;
		strcat(WhereDiscription, BizInfo[biz][bDiscription]);
	}
//==============================================================================
//определяем время доставки
	Cargo[trailerid][tPeriod] = floatround(K_mediumspeed*Cargo[trailerid][tDistance]/(speed*1000)*3600);//м / (K * S км/ч * 1000) = часы * 3600 = секундах
	if(Cargo[trailerid][tPeriod] < 120) Cargo[trailerid][tPeriod] = 120 + Cargo[trailerid][tPeriod];//если меньше 2 минут
	Cargo[trailerid][tBonus] = Cargo[trailerid][tSellPrice] - Cargo[trailerid][tBuyPrice];
//==============================================================================
	//if(Cargo[trailerid][tWhence] == 80)
	//{//если поставка со склада, то увеличиваем предел в 10 раз
	//	maxload = VehicleArray[trailermodel-400][Weight];//*10;
	//}
	//else
	//{//иначе максимальная загрузка не больше половины веса грузовика
	maxload = VehicleArray[trailermodel-400][Weight]/2;
	//}

	new dlgitem[755];//320+279 + 1+20 + 20+2 + 5+5+5 + 10 + 2 + 6+5+10  + 10+10 + 10+5 + 10+10 + 10 = 755
	format(dlgitem, sizeof(dlgitem), "{FFFF00}Тип: {FFFFFF}%d(%s)\
\n{FFFF00}Куда: {FFFFFF}%s[%d]\
\n{FFFF00}Покупка: {33AA33}$%.2f\
\n{FFFF00}Продажа: {33AA33}$%.2f\
\n{FFFF00}Прибыль: {33AA33}$%.2f\
\n{FFFF00}Премия от продавца: {33AA33}$%d\
\n{FFFF00}Хрупкость: {FFFFFF}%d %%\
\n{FFFF00}Растояние: {FFFFFF}%.1f м\
\n{FFFF00}Время: {FFFFFF}%s[%d]",
		Cargo[trailerid][CargoType], TypeCargo(Cargo[trailerid][CargoType]),
		WhereDiscription, Cargo[trailerid][tWhere],
		Cargo[trailerid][tBuyPrice], Cargo[trailerid][tSellPrice], Cargo[trailerid][tBonus],//\n{FFFF00}Прибыль с кг: {FFFFFF}$%.2f
		salary,
		Cargo[trailerid][tFrailty],
		Cargo[trailerid][tDistance], //Cargo[trailerid][tBonus]/Cargo[trailerid][tDistance],//float/float
		TimeConverter(Cargo[trailerid][tPeriod]), Cargo[trailerid][tPeriod]);

	format(dlgitem, sizeof(dlgitem), "%s\n{FFFF00}Загружен: {FFFFFF}%d/%d кг\
\n{FFFF00}На складе: {FFFFFF}%d кг {FFFF00}по Цене: {33AA33}$%.2f\
\n{FFFF00}Можете купить: {FFFFFF}%d кг\
\n{FFFF00}Сможете продать: {FFFFFF}%d кг\
\n\n{A8C3E3}Введите кол-во кг загрузки,\nИли нажмите NEXT, чтобы выбрать другой груз",
		dlgitem,
		VehInfo[trailerid][cLoad], maxload,
		products, Cargo[trailerid][tBuyPrice],
		amount, amount2);
		
	if(strlen(dlgitem) > sizeof(dlgitem))
	{
		//ИНФОРМИРОВАНИЕ
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "Error17: CreateCargoLoadingDialog %s[%d], strlen(dlgitem): %d, sizeof(dlgitem): %d",
			PlayerName(playerid), playerid, strlen(dlgitem), sizeof(dlgitem));
		Log(ERROR, strings);
		return 1;
	}
	if(strlen(dlgitem) <= 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   CreateCargoLoadingDialog пуст");//COLOR_BLUEGREY
		return 1;
	}
//==============================================================================
//создаём маршрут на карте с расчётом дистанции Cargo[trailerid][tDistance]
#if defined vw_gps
	gps_trucker(playerid, trailerid);//до РАСЧЁТа ЦЕНЫ ПО КОТОРОЙ ДАЛЬНОБОЙЩИК ПРОДАСТ
#endif

	format(discription, sizeof(discription), "%s[%d]", discription, Cargo[trailerid][tWhence]);
	ShowPlayerDialogEx(playerid, TRUCK_DIALOG, DIALOG_STYLE_INPUT, discription, dlgitem, "OK", "Next");//для дальнобойщиков STEP4
	return 1;
}

stock trucker_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	//RobberyDialogResponse(playerid, dialogid, response, listitem, inputtext);
	
	if(dialogid != TRUCK_DIALOG) return 1;//для дальнобойщиков STEP4

	new trailerid, trailermodel;
	if(IsTrailerAttachedToVehicle(nCarID[playerid])) { trailerid = nTrailerID[playerid]; trailermodel = nTrailerModel[playerid]; }
	else { trailerid = nCarID[playerid]; trailermodel = nCarModel[playerid]; }

	if(!response)//NEXT
	{
		//new msgitem[256+1];
		//format(msgitem, sizeof(msgitem),"trailerid: %d, откуда: %d, куда: %d", trailerid, Cargo[trailerid][tWhence], Cargo[trailerid][tWhere]);
		//SendClientMessage(playerid, COLOR_GREEN, msgitem);
		if(Cargo[trailerid][tWhence] == 80 && Cargo[trailerid][tWhere] != 81)
		{//если поставка со склада и не в порт
			trucker_OnPlayerKeyState_UP(playerid);
		}
		else
		{
			//gTextDrawHideCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
		    //GPS_OnOff[playerid] = 0; DisablePlayerCheckpointEx(playerid);//CP[playerid] = 0;
			//SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Маркер Задания убран !");

			TruckerCargoInit(playerid);//обнуляем при выходе из диалога
		}
		return 1;
	}
	new msgitem[256+1];
 //ShowPlayerDialogEx(playerid, 71, DIALOG_STYLE_INPUT, discription, dlgitem, "OK", "Cancel");
//вызывается  из CreateCargoLoadingDialog->trucker_OnPlayerKeyState_UP
	if((!IsTrailerAttachedToVehicle(nCarID[playerid]) || nTrailerID[playerid] == 0) && IsInHardTruck(nCarID[playerid]))
	{   //если Вы сели в грузовик
		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы - не прикрепили полуприцеп к тягачу !");
	    return 1;
	}

	if(!strlen(inputtext))
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не ввели кол-во кг загрузки!");
		CreateCargoLoadingDialog(playerid);//, Cargo[trailerid][tWhence]
		return 1;
	}
	//SelectRout[playerid] = 0;
	new amount = strval(inputtext);
	if(Cargo[trailerid][tWhence] == 80)
	{//если поставка со склада, то предел увеличен в 10 раз
		if(	amount < 1 || amount > VehicleArray[trailermodel-400][Weight]*10 ||
			(amount+VehInfo[trailerid][cLoad]) >= VehicleArray[trailermodel-400][Weight]*10)
		{   //если продуктов на складе больше 100, и игрок способен их оплатить, но ввёл кол-во менее 100, то повтор
			format(msgitem, sizeof(msgitem),"   Bы не можете купить менее %d или более %d продуктов!", 1, VehicleArray[trailermodel-400][Weight]*10);
			SendClientMessage(playerid, COLOR_GREEN, msgitem);
			CreateCargoLoadingDialog(playerid);//, Cargo[trailerid][tWhence]
			return 1;
		}
	}
	else
	{
		if(	amount < 1 || amount > VehicleArray[trailermodel-400][Weight]/2 ||
			(amount+VehInfo[trailerid][cLoad]) >= VehicleArray[trailermodel-400][Weight]/2)
		{   //если продуктов на складе больше 100, и игрок способен их оплатить, но ввёл кол-во менее 100, то повтор
			format(msgitem, sizeof(msgitem),"   Bы не можете купить менее %d или более %d продуктов!", 1, (VehicleArray[trailermodel-400][Weight]/2));
			SendClientMessage(playerid, COLOR_GREEN, msgitem);
			CreateCargoLoadingDialog(playerid);//, Cargo[trailerid][tWhence]
			return 1;
		}
	}
	new cost, products;
	//new price;
	if(Cargo[trailerid][tWhence] >= 100)
	{
		new sbiz = Cargo[trailerid][tWhence]-100;
		products = SBizInfo[sbiz][sbProducts];
		if(amount > products)
		{
			SendClientMessage(playerid, COLOR_GREEN, "   Недостаточно продуктов на складе!");
			CreateCargoLoadingDialog(playerid);//, Cargo[trailerid][tWhence]
			return 1;
		}
		//cost = amount*floatround(Cargo[trailerid][tBuyPrice], floatround_ceil);//потеря точности при больших суммах
		cost = floatround(amount*Cargo[trailerid][tBuyPrice], floatround_floor);
	}
	else
	{
		new biz = Cargo[trailerid][tWhence];//откуда
		products =  GetProducts(biz);//, Cargo[trailerid][CargoType]
		/*if(Cargo[trailerid][CargoType] == Amusements)
		{//Металл - основа для производства товаров индустрии развлечений
			products = BizInfo[biz][bMetal];
		}
		else if(Cargo[trailerid][CargoType] == Trade)
		{//Текстиль - основа для производства товаров розничной торговли
			products = BizInfo[biz][bTextiles];
		}
		else if(Cargo[trailerid][CargoType] == Restaurant)
		{//Продовольствие - основа для производства товаров ресторанного бизнеса
			products = BizInfo[biz][bProvisions];
		}
		else if(Cargo[trailerid][CargoType] == Service)
		{//Древесины - основа для производства товаров сферы услуг
			products = BizInfo[biz][bTree];
		}
		else if(Cargo[trailerid][CargoType] == Industry)
		{//Нефть - основа для производства товара промышленной сферы
			products = BizInfo[biz][bFuel];
		}
		else
		{//товар на экспорт
			products = BizInfo[biz][bProducts];
		}*/
		if(amount > products)
		{
			SendClientMessage(playerid, COLOR_GREEN, "   Недостаточно продуктов на складе!");
			CreateCargoLoadingDialog(playerid);//, Cargo[trailerid][tWhence]
			return 1;
		}
		//cost = amount*floatround(Cargo[trailerid][tBuyPrice], floatround_ceil);//потеря точности при больших суммах
		cost = floatround(amount*Cargo[trailerid][tBuyPrice], floatround_floor);
	}
	if(GetPlayerMoneyH(playerid) < cost)
	{
		format(msgitem, sizeof(msgitem), "   Bы не можете купить %d продуктов на сумму $%d! Недостаточно средств на руках!", amount, cost);
		SendClientMessage(playerid, COLOR_GREEN, msgitem);
		CreateCargoLoadingDialog(playerid);//, Cargo[trailerid][tWhence]
		return 1;
	}
	//if(	Cargo[trailerid][tWhence] != 80 &&
	//	Cargo[trailerid][tWhence] != 81)
	//{
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
		if(	i == playerid ) continue;
		if( PlayerInfo[i][pJob] != TRUCKER )  continue;
		if( !IsInHardTruck(nCarID[playerid]) ) continue;//пропускаем все кроме тягачей
		if( gLoading[i] <= 0 ) continue;
		if( gLoading[i] == Cargo[trailerid][tWhence] )//GetPVarInt(playerid, "gShowDialog") == TRUCK_DIALOG
		{ //сканируем тех кто тоже грузится сдесь
			format(msgitem, sizeof(msgitem), "   Bы не можете загружаться пока не окончена загрузка у %s[%d]", PlayerName(i),i);
			SendClientMessage(playerid, COLOR_GREY, msgitem);
			return 1;
		}
	}
	//}
	ProdCounter[playerid] = amount;
	TogglePlayerControllableEx(playerid, 0);//игрок НЕ сможет двигаться
	gLoading[playerid] = Cargo[trailerid][tWhence];//Cargo[nTrailerID[playerid]][tWhence];
	OnVehicleLoading(playerid, Cargo[trailerid][tWhence]);//для дальнобойщиков STEP5

	//PlayAudioStreamForPlayerEx(playerid, "RepairActive.wav");
	//if(RepeatAudio[playerid]) {	KillTimer(RepeatAudio[playerid]); RepeatAudio[playerid] = -1; }
	//RepeatAudio[playerid] = SetTimerEx("RepeatAudioStreamForPlayerEx", 16000, 1, "is", playerid, "RepairActive.wav");

    GameTextForPlayerEx(playerid, "~w~Cargo Delivery~n~~r~Deliver the shipment at the Spot", 5000, 1);
	return 1;
}
//для дальнобойщиков STEP5
stock OnVehicleLoading(playerid, biz)//вызывается из секундного таймера
{   //biz - Cargo[trailerid][tWhence]//Откуда
	//new strings[MAX_STRING];
	//format(strings, sizeof(strings), "Begin OnVehicleLoading(playerid:%d, biz:%d) ProdCounter:%d, gLoading:%d, gUnLoading:%d", playerid, biz, ProdCounter[playerid], gLoading[playerid], gUnLoading[playerid]);
	//SendClientMessage(playerid, COLOR_RED, strings);
	
	new timers = GetTickCount();
	if(gLoading[playerid] == 0) return 1;
	if(gUnLoading[playerid] != 0) return 1;

	if(PlayerInfo[playerid][pJob] != TRUCKER) return 1;
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) { return 1; }
	if(	VehicleArray[nCarModel[playerid]-400][Category] != Station_Wagons &&
		VehicleArray[nCarModel[playerid]-400][Category] != Industrial &&
		VehicleArray[nCarModel[playerid]-400][Category] != Lorries//все грузовики
	  )	return 1;
	  
	new trailerid, trailermodel;
	if(IsTrailerAttachedToVehicle(nCarID[playerid])) { trailerid = nTrailerID[playerid]; trailermodel = nTrailerModel[playerid]; }
	else { trailerid = nCarID[playerid]; trailermodel = nCarModel[playerid]; }
	if(trailerid == 0)  return 1;

	gGameText[playerid] = 1;
	SetPlayerGameTextScale(playerid, "Loading Vehicle", tmpCounter[playerid], ProdCounter[playerid]);
	
//ИНФОРМИРОВАНИЕ
	new strtmp[MAX_STRING];
	//format(strings, sizeof(strings), "biz:%d gLoading:%d tmpCounter:%d ProdCounter:%d",
	//	biz, gLoading[playerid], tmpCounter[playerid], ProdCounter[playerid]);
	//SendClientMessage(playerid, COLOR_YELLOW, strings);
	new level = PlayerInfo[playerid][pTruckSkill];
	new skill;
	if(	level < 50 )
	{   //если вы уже доставили 49 машин то 20 минут
		skill = 1;
	}
	else if(level >= 50  && level < 100)
	{   //если вы уже доставили 49 машин то 20 минут
		skill = 2;
	}
	else if(level >= 100  && level < 200)
	{   //если вы уже доставили 49 машин то 20 минут
		skill = 3;
	}
	else if(level >= 200  && level < 400)
	{   //если вы уже доставили 49 машин то 20 минут
		skill = 4;
	}
	else if(level >= 400)
	{   //если вы уже доставили 49 машин то 20 минут
		skill = 5;
	}
	if(Cargo[trailerid][CargoType] == 5) tmpCounter[playerid] += 40;
	else if(Cargo[trailerid][CargoType] == 6 && Cargo[trailerid][tWhence] == 80) tmpCounter[playerid] += 1000;
	else if(skill == 1) tmpCounter[playerid] += 20;//скорость разгрузки по 30 в секунду
	else if(skill == 2) tmpCounter[playerid] += 24;
	else if(skill == 3) tmpCounter[playerid] += 27;
	else if(skill == 4) tmpCounter[playerid] += 29;
	else if(skill == 5) tmpCounter[playerid] += 30;//скорость разгрузки по 75 в секунду

//TestLog(OPTIM, "OnVehicleLoading1.2 ", GetTickCount(), timers);
 	if(tmpCounter[playerid] >= ProdCounter[playerid] && ProdCounter[playerid] > 0)
	{//считаем пока не до считаем до значения нашего груза
	
		StopAudioStreamForPlayerEx(playerid);
		gGameText[playerid] = 0;
		tmpCounter[playerid] = 0;
		gLoading[playerid] = 0;//опустили флаг - окончили загрузку
		TogglePlayerControllableEx(playerid, 1);//игрок сможет двигаться
//TestLog(OPTIM, "OnVehicleLoading1.3 ", GetTickCount(), timers);
//==============================================================================
//ОТКУДА
		new cost;
		//new Float: price;
		if(biz >= 100)
		{//откуда
			new sbiz = biz-100;
			//price = compcost*(100+SBizInfo[sbiz][sbSellProd])/100.0;
			cost = floatround(ProdCounter[playerid]*Cargo[trailerid][tBuyPrice], floatround_ceil);
//ИНФОРМИРОВАНИЕ
			/*new strtmp[MAX_STRING];
			format(strtmp, sizeof(strtmp), "Loading %s Откуда:%d Куда:%d Касса:%d[%d] Prod:%d[%d] Load:%d[%d] Cost:%d",
				PlayerName(playerid),
				sbiz, Cargo[trailerid][tWhere],
				(SBizInfo[sbiz][sbTill]+cost), SBizInfo[sbiz][sbTill],
				(SBizInfo[sbiz][sbProducts]-ProdCounter[playerid]), SBizInfo[sbiz][sbProducts],
				VehInfo[nCarID[playerid]][cLoad], ProdCounter[playerid],
				cost);
			Log(PACKET, strtmp);*/
//[30/04/2014 | 16:20:14] Loading Danger_Hidden Откуда:12 Куда:80 Касса:108770[107120] Prod:5189[5289] Load:0[100] Cost:1650
			//OnGangsExtortionBiz(sbizz, cost);
			SBizInfo[sbiz][sbProducts] -= ProdCounter[playerid];
			SBizInfo[sbiz][sbTill] += cost;
			SBizInfo[sbiz][sbExport] += cost;

			format(strtmp, sizeof(strtmp), "%s[%d] продажа: {FFFFFF}%s в кол-ве %d кг на сумму {33AA33}$%d{FFFFFF} увёз: %s[%d]",
				SBizInfo[sbiz][sbDiscription], sbiz, TypeCargo(Cargo[trailerid][CargoType]), ProdCounter[playerid], cost, PlayerName(playerid), playerid);
			GetTaskOnCargo(playerid, trailerid, Cargo[trailerid][tWhence], Cargo[trailerid][tWhere], Cargo[trailerid][CargoType], cost, Cargo[trailerid][tPeriod]);
			new giveplayerid = ReturnUser(SBizInfo[sbiz][sbOwner]);
		    if( IsPlayerConnectedEx(giveplayerid) ) SendClientMessageEx(giveplayerid, COLOR_LIGHTBLUE, strtmp);
		    //SendClientMessageToAll(-1, strtmp);
			//SaveSBiz(sbiz);
//TestLog(OPTIM, "OnVehicleLoading1.4 ", GetTickCount(), timers);
		}
		else
		{
//ИНФОРМИРОВАНИЕ
			/*new strtmp[MAX_STRING];
			format(strtmp, sizeof(strtmp), "Loading %s Тип:%d Откуда:%d Куда:%d Касса:%d[%d] Prod:%d[%d] Load:%d[%d] Cost:%d",
				PlayerName(playerid),
				Cargo[trailerid][CargoType],
				biz, Cargo[trailerid][tWhere],
				(BizInfo[biz][bTill]+cost), BizInfo[biz][bTill],
				(BizInfo[biz][bProducts]-ProdCounter[playerid]), BizInfo[biz][bProducts],
				VehInfo[nCarID[playerid]][cLoad], ProdCounter[playerid],
				cost);
			Log(PACKET, strtmp);*/

			if(Cargo[trailerid][CargoType] == 1)
			{//Металл - основа для производства товаров индустрии развлечений
				BizInfo[biz][bMetal] -= ProdCounter[playerid];
			}
			else if(Cargo[trailerid][CargoType] == 2)
			{//Текстиль - основа для производства товаров розничной торговли
				BizInfo[biz][bTextiles] -= ProdCounter[playerid];
			}
			else if(Cargo[trailerid][CargoType] == 3)
			{//Продовольствие - основа для производства товаров ресторанного бизнеса
				BizInfo[biz][bProvisions] -= ProdCounter[playerid];
			}
			else if(Cargo[trailerid][CargoType] == 4)
			{//Древесины - основа для производства товаров сферы услуг
				BizInfo[biz][bTree] -= ProdCounter[playerid];
			}
			else if(Cargo[trailerid][CargoType] == 5)
			{//Нефть - основа для производства товара промышленной сферы
				BizInfo[biz][bFuel] -= ProdCounter[playerid];
			}
			else
			{//товар на экспорт
				BizInfo[biz][bProducts] -= ProdCounter[playerid];//отняли проды из того биза где стоим
			}
			//OnGangsExtortionBiz(bizz, cost);
			//price = compcost*(100+BizInfo[biz][bSellProd])/100.0;
			cost = floatround(ProdCounter[playerid]*Cargo[trailerid][tBuyPrice], floatround_ceil);

			BizInfo[biz][bTill] += cost;//заплатили тому бизу
			BizInfo[biz][bExport] += cost;

			format(strtmp, sizeof(strtmp), "%s[%d] продажа: {FFFFFF}%s в кол-ве %d кг на сумму {33AA33}$%d{FFFFFF} увёз: %s[%d]",
				BizInfo[biz][bDiscription], biz, TypeCargo(Cargo[trailerid][CargoType]), ProdCounter[playerid], cost, PlayerName(playerid), playerid);
			GetTaskOnCargo(playerid, trailerid, Cargo[trailerid][tWhence], Cargo[trailerid][tWhere], Cargo[trailerid][CargoType], cost, Cargo[trailerid][tPeriod]);
			new giveplayerid = ReturnUser(BizInfo[biz][bOwner]);
		    if( IsPlayerConnectedEx(giveplayerid) ) SendClientMessageEx(giveplayerid, COLOR_LIGHTBLUE, strtmp);
			//SendClientMessageToAll(-1, strtmp);
			
			if(biz == 80) UpdateStoreHouse();
			else if(biz == 81) UpdateOceanDock();
			//SaveBiz(biz);
//TestLog(OPTIM, "OnVehicleLoading1.5 ", GetTickCount(), timers);
		}
//==============================================================================
//КУДА
		new rout = -1; new discription[20];
		if(Cargo[trailerid][tWhere] >= 100)
		{
			rout = Cargo[trailerid][tWhere] - 100;
			strmid(discription, SBizInfo[biz][sbDiscription], 0, 20, 20);
			CP[playerid] = CP_TRUCKER;//получено задание 160: Миссия дальнобоев
			SetPlayerCheckpointEx(playerid,
				SBizInfo[rout][sbEntranceX],
				SBizInfo[rout][sbEntranceY],
				SBizInfo[rout][sbEntranceZ],
				CHECKPOINT_SIZE*2);

			checktimedeliver[playerid] = GetTickCount();
		    format(strings, sizeof(strings), "При доставке быстрее чем за %d секунд у вас обнулится скилл.", MinTimeCheckpoint[playerid]/1000);
		    SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);

			/*if(PlayerInfo[playerid][pGPS] == 1)
			{//чтобы записались координаты чекпоинта
				SetPlayerRouting(playerid,
					SBizInfo[rout][sbEntranceX],
					SBizInfo[rout][sbEntranceY],
					SBizInfo[rout][sbEntranceZ]);
			}*/
//TestLog(OPTIM, "OnVehicleLoading1.6 ", GetTickCount(), timers);
		}
		else
		{
			rout = Cargo[trailerid][tWhere];
			strmid(discription, BizInfo[rout][bDiscription], 0, 20, 20);
			CP[playerid] = CP_TRUCKER;//получено задание 160: Миссия дальнобоев
			SetPlayerCheckpointEx(playerid,
					BizInfo[rout][bEntranceX],
					BizInfo[rout][bEntranceY],
					BizInfo[rout][bEntranceZ],
					CHECKPOINT_SIZE*2);

			checktimedeliver[playerid] = GetTickCount();
		    format(strings, sizeof(strings), "При доставке быстрее чем за %d секунд у вас обнулится скилл.", MinTimeCheckpoint[playerid]/1000);
		    SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);

			/*if(PlayerInfo[playerid][pGPS] == 1)
			{
				SetPlayerRouting(playerid,
					BizInfo[rout][bEntranceX],
					BizInfo[rout][bEntranceY],
					BizInfo[rout][bEntranceZ]);
			}*/
//TestLog(OPTIM, "OnVehicleLoading1.7 ", GetTickCount(), timers);
		}
//==============================================================================
		VehInfo[trailerid][cLoad] += ProdCounter[playerid];//добавили к загрузке
		VehInfo[trailerid][cLoadType] = Cargo[trailerid][CargoType];
		VehInfo[trailerid][cWhere] = Cargo[trailerid][tWhere];
		
		Cargo[trailerid][tWeight] = VehInfo[trailerid][cLoad];//записали сколько взяли кг
		//Cargo[trailerid][tBonus] = floatround( (float(VehInfo[nCarID[playerid]][cLoad])/3000.0)*Cargo[trailerid][tBonus] );

		new amount;
		if(Cargo[trailerid][tWhence] == 80)
		{
			amount = VehicleArray[trailermodel-400][Weight];//*10;
		}
		else
		{
			amount = VehicleArray[trailermodel-400][Weight]/2;
		}

//TestLog(OPTIM, "OnVehicleLoading1.8 ", GetTickCount(), timers);

		format(strtmp, sizeof(strtmp), "Загружен: {33AA33}%d/%d. Тип груза: %s[%d]",
			VehInfo[trailerid][cLoad], amount, TypeCargo(Cargo[trailerid][CargoType]), VehInfo[trailerid][cLoadType]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strtmp);
		format(strtmp, sizeof(strtmp), "%d {0080FF}продуктов куплено за {33AA33}$%d {0080FF}по цене {33AA33}$%.1f за шт.",
			ProdCounter[playerid], cost, Cargo[trailerid][tBuyPrice]);
		SendClientMessage(playerid, COLOR_GREEN, strtmp);
		format(strtmp, sizeof(strtmp), "Чистая прибыль при данной загрузке составляет {33AA33}$%d",
			floatround(ProdCounter[playerid]*Cargo[trailerid][tBonus]));
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strtmp);

		GivePlayerMoneyH(fjob+PlayerInfo[playerid][pJob], playerid, -cost);

		GPS_OnOff[playerid] = 1;
		
		//PlaySoundForPlayer(playerid, SOUND_CARGO_PLANE_DOOR_STOP);//SOUND_CARGO_PLANE_DOOR_LOOP
		PlayerInfo[playerid][pCarTime] = Cargo[trailerid][tPeriod];//записали время
		PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][10], TimeConverter(PlayerInfo[playerid][pCarTime]));
//------------------------------------------------------------------------------
//ИНФОРМИРОВАНИЕ
		//new strings[MAX_STRING];
		/*format(strings, sizeof(strings), "OnVehicleLoading(player:%s, Whence:%d Where:%d) Load:%d Prod:%d Cost:%d",
			PlayerName(playerid), biz, Cargo[trailerid][tWhere], VehInfo[nCarID[playerid]][cLoad], ProdCounter[playerid], cost);
		Log(TRUCK, strings);
		SendClientMessageToAll(COLOR_YELLOW, strings);*/
		//SendClientMessage(playerid, COLOR_GREEN, strings);
//------------------------------------------------------------------------------
		ProdCounter[playerid] = 0;
//TestLog(OPTIM, "OnVehicleLoading1.9 ", GetTickCount(), timers);
	}
	new str[82];//45+24+3+10 = 82
	format(str, sizeof(str), "OnVehicleLoading(player:%s, biz:%d) cLoad:%d", PlayerName(playerid), biz, VehInfo[trailerid][cLoad]);
	TestLog(OPTIM, str, GetTickCount(), timers);
	return 1;
}


stock trucker_OneSecondTimers(playerid)
{
	//if(	gTutorial[playerid] != 1) return 1;
	if(PlayerInfo[playerid][pJob] != TRUCKER) return 1;
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;
	//для полицейcких вертолётов
	if(	GPS_OnOff[playerid] == 1 && PlayerInfo[playerid][pGPS] == 1)
	{
    	if(	//PlayerInfo[playerid][pJob] == TRUCKER &&
				//(IsInHardTruck(nCarID[i]) || IsInTruck(nCarID[i]))
				//VehicleArray[nCarModel[i]-400][Category] != Station_Wagons &&
				//VehicleArray[nCarModel[i]-400][Category] != Industrial &&
				//VehicleArray[nCarModel[i]-400][Category] != Lorries &&
				CP[playerid] == CP_TRUCKER )
		{
			//SetPlayerRouting(playerid,PurposePoint[playerid][tX],PurposePoint[playerid][tY],PurposePoint[playerid][tZ]);
		}
	}
	OnCargoTime(playerid);
	new trailerid;//, trailermodel;
	if(IsTrailerAttachedToVehicle(nCarID[playerid])) { trailerid = nTrailerID[playerid]; /*trailermodel = nTrailerModel[playerid];*/ }
	else { trailerid = nCarID[playerid]; /*trailermodel = nCarModel[playerid];*/ }
	if(gLoading[playerid])// && AFK_IdleTime[i] < 3
    {
    	OnVehicleLoading(playerid, Cargo[trailerid][tWhence]);
    }
	else if(gUnLoading[playerid] == 1)// && AFK_IdleTime[i] < 3
    {//поднимается флаг при заезде в чекпоинт
    	OnVehicleUnLoading(playerid, Cargo[trailerid][tWhere]);//для дальнобойщиков STEP8
    }
	return 1;
}

stock OnCargoTime(playerid)//запускается каждую секунду из OneSecondTimers
{
	if(gLoading[playerid]) return 1;
	if(gUnLoading[playerid]) return 1;
	if(gInRacing[playerid]) return 1;
	//if(gInDerbyBloodBowl[playerid]) return 1;
	//if(gInDerby8ball[playerid]) return 1;
	//if(gInTerrorsCount[playerid]) return 1;
	//if(gInCTerrorsCount[playerid]) return 1;

	if(PlayerInfo[playerid][pJob] != TRUCKER) return 1;
	if(CP[playerid] != CP_TRUCKER) return 1;
//SendClientMessageToAll(COLOR_YELLOW, "OnCargoTime");

	new trailerid;
	if(nTrailerModel[playerid]) { trailerid = nTrailerID[playerid]; }
	else { trailerid = nCarID[playerid]; }

	//if(Cargo[trailerid][tPeriod] > 0)
	if(PlayerInfo[playerid][pCarTime] > 0)
	{
		//Cargo[trailerid][tPeriod] --;//счётчик секунд работает
		PlayerInfo[playerid][pCarTime] --;//счётчик секунд работает
		CargoInfoTime(playerid, trailerid);
	}
	return 1;
}

stock CargoInfoTime(playerid, trailerid)
{
	if(gRefueling[playerid] != 0) return 1;
	if(IsAtGasStation(playerid)) return 1;
	new strtmp[227+32];//127 + 3+1+20 + 4+3 + 4+20 + 3+5 + 6+10 + 9+2 + 5+5 = 227
	//if(Cargo[trailerid][tPeriod] <= 0)
	if(PlayerInfo[playerid][pCarTime] <= 0)
    {
		//Cargo[trailerid][tPeriod] = 0;//остановить счётчик
		PlayerInfo[playerid][pCarTime] = 0;//остановить счётчик
		gTextDrawHideCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
		TrailerEnterCheckpoint(playerid);			//для дальнобойщиков STEP9
		//если время вышло и ты не разгружаешься
	}
	else
	{   //для дальнобойщиков STEP6
		CrashDetected[playerid] = 238;
		new discription[20];
		new biz = Cargo[trailerid][tWhere];//куда
		if(biz < 100)
		{
			strmid(discription, BizInfo[biz][bDiscription], 0, 20, 20);
		}
		else if(biz >= 100 && biz < 255)
		{
			biz = biz - 100;
			strmid(discription, SBizInfo[biz][sbDiscription], 0, 20, 20);
		}//~n~~b~%s ~w~%d
		new cargo[20];// = RusToGame(TypeCargo(Cargo[trailerid][CargoType];
		
		strmid(cargo, TypeCargo(Cargo[trailerid][CargoType]), 0, 20, 255);
		format(strtmp, sizeof(strtmp), "~b~%s ~w~%s(%d)\
~n~~b~%s ~w~%s\
~n~~b~%s ~w~%d kg\
~n~~b~%s ~g~$%.2f\
~n~~b~%s ~y~%d %%\
~n~~b~%s ~w~%s",
			RusToGame("ТИП"), RusToGame(cargo), Cargo[trailerid][CargoType],
			RusToGame("КУДА"), discription,
			RusToGame("ВЕС"), VehInfo[trailerid][cLoad],
			RusToGame("ПРИБЫЛЬ"), VehInfo[trailerid][cLoad]*Cargo[trailerid][tBonus],
			RusToGame("ХРУПКОСТЬ"), Cargo[trailerid][tFrailty],
			//RusToGame("ВРЕМЯ"),	TimeConverter(Cargo[trailerid][tPeriod]) );
			RusToGame("ВРЕМЯ"),	TimeConverter(PlayerInfo[playerid][pCarTime]) );
		PlayerTextDrawSetStringEx(playerid, txdCarTime[playerid], strtmp);

		format(strtmp, sizeof(strtmp), "%s(%d) %d кг", cargo, Cargo[trailerid][CargoType], VehInfo[trailerid][cLoad]);//"ТИП" "ВЕС"
		PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][8], RusToGame(strtmp));
		
		PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][9], discription);//"КУДА"
		
		//PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][10], TimeConverter(Cargo[trailerid][tPeriod]));//"ВРЕМЯ"
		PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][10], TimeConverter(PlayerInfo[playerid][pCarTime]));//"ВРЕМЯ"
		
		
		format(strtmp, sizeof(strtmp), "$%.2f", VehInfo[trailerid][cLoad]*Cargo[trailerid][tBonus]);//"ПРИБЫЛЬ"
		PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][11], strtmp);

		//new Float: remaining_distance = distance_to_point - VehInfo[nCarID[playerid]][cDist];
		
		format(strtmp, sizeof(strtmp), "ETA: %s %s, %.0f м, %s",
			GetWeekDay(), GetNextTime(Cargo[trailerid][tPeriod]), Cargo[trailerid][tDistance], TimeConverter(Cargo[trailerid][tPeriod]) );
	   	PlayerTextDrawSetStringEx(playerid, pltxdAdvisor[playerid][12], RusToGame(strtmp));
	}
	return 1;
}



//##############################################################################//
//                                                                              //
//                               ЗАВЕРШЕНИЕ ЗАДАНИЯ                             //
//                                                                              //
//##############################################################################//

stock trucker_OnEnterCheckpoint(playerid)//для дальнобойщиков STEP7
{
	if(PlayerInfo[playerid][pJob] != TRUCKER) return 1;
	if(CurState[playerid] != PLAYER_STATE_DRIVER) { return 1; }
	if(CP[playerid] != CP_TRUCKER) return 1;//если ты получил миссию Дальнобойщиков, чтобы нельзя было несколько раз взять задание
 //приехал на финиш
	if((!IsTrailerAttachedToVehicle(nCarID[playerid]) || nTrailerID[playerid] == 0) && IsInHardTruck(nCarID[playerid]))
	{   //если Вы сели в грузовик
		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы - не прикрепили полуприцеп к тягачу !");
	    return 1;
	}
	if(GetTickCount() < (checktimedeliver[playerid]+MinTimeCheckpoint[playerid]))// && !gAnticheat[playerid]
	{
		format(strings, sizeof(strings), "%s[%d] Reset TruckSkill:%d checktimedeliver:%d[%d] sec",
			PlayerName(playerid),playerid, PlayerInfo[playerid][pTruckSkill],
			(GetTickCount()-checktimedeliver[playerid])/1000, MinTimeCheckpoint[playerid]/1000);
		Log(JOB, strings);
		PlayerInfo[playerid][pTruckSkill] = 0;
		SendClientMessage(playerid, COLOR_GREY, strings);
		return 1;
	}
	/*format(strings, sizeof(strings), "%s[%d] TruckSkill:%d checktimedeliver:%d[%d] sec",
		PlayerName(playerid),playerid, PlayerInfo[playerid][pTruckSkill], (GetTickCount()-checktimedeliver[playerid])/1000, 60);
	Log(JOB, strings);*/

	SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы доставили груз! Ожидайте проверки сохранности груза и разгрузки!");

	new trailerid;//, trailermodel;
	if(IsTrailerAttachedToVehicle(nCarID[playerid])) { trailerid = nTrailerID[playerid]; }
	else { trailerid = nCarID[playerid]; }
	
	new biz = Cargo[trailerid][tWhere];
	if(biz > 100)
	{
		new sbiz = biz - 100;
	    //if(sb >= PARKING && sb < PARKING+sizeof(Parking)) continue;//пропускаем паркинги
		if(VehInfo[trailerid][cLoad] <= 0)
		{
			SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}У вас пустой прицеп !");
			TrailerEnterCheckpoint(playerid);//для дальнобойщиков STEP9
			return 1;//break;
		}
		if(floatcmp(SBizInfo[sbiz][sbTill], Cargo[trailerid][tSellPrice]) > 0)
		{//если в кассе денег есть хоть на один прод
			ProdCounter[playerid] = floatround(SBizInfo[sbiz][sbTill]/Cargo[trailerid][tSellPrice], floatround_floor);
			//кол-во продов которое может купить биз
//ИНФОРМИРОВАНИЕ
		//new strings[MAX_STRING];
		//format(strings, sizeof(strings), "1.CP_TRUCKER(player:%s, biz:%d) Prod:%d Load:%d",
		//	PlayerName(playerid), biz, ProdCounter[playerid], VehInfo[nCarID[playerid]][cLoad]);
		//Log(PACKET, strings);
		}
		else ProdCounter[playerid] = 0;
		if(VehInfo[trailerid][cLoad] < ProdCounter[playerid] && VehInfo[trailerid][cLoad] != 0) ProdCounter[playerid] = VehInfo[trailerid][cLoad];
		//если в грузовике меньше чем может биз , то выгрузить весь грузовик

		if(ProdCounter[playerid] < 1)
		{
			format(strings, sizeof(strings), "%s не может оплатить даже еденицу груза.", SBizInfo[biz][sbDiscription]);
			SendClientMessage(playerid, COLOR_DARKRED, strings);
			//SendClientMessage(playerid, COLOR_DARKRED, "Но не отчаивайтесь, ведь кол-во загруженного сырья находится у вас в авто(USE: /load)");
			TrailerEnterCheckpoint(playerid);//для дальнобойщиков STEP9
			return 1;
		}
	}
	else
	{
		if(VehInfo[trailerid][cLoad] <= 0)
		{
			SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}У вас пустой прицеп !!");
			TrailerEnterCheckpoint(playerid);//для дальнобойщиков STEP9
			return 1;//break;
		}

//РАЗГРУЗКА
		//сколько может оплатить
		//if(BizInfo[biz][bTill] > Cargo[trailerid][tSellPrice])
		if(floatcmp(BizInfo[biz][bTill], Cargo[trailerid][tSellPrice]) > 0)
		{//если в кассе есть деньги хоть на один прод
			ProdCounter[playerid] = floatround(BizInfo[biz][bTill]/Cargo[trailerid][tSellPrice], floatround_floor);
			//кол-во продов которые может оплатить биз
//ИНФОРМИРОВАНИЕ
		//new strings[MAX_STRING];
		//format(strings, sizeof(strings), "1.CP_TRUCKER(player:%s, biz:%d) Prod:%d Load:%d",
		//	PlayerName(playerid), biz, ProdCounter[playerid], VehInfo[nCarID[playerid]][cLoad]);
		//Log(PACKET, strings);
		}
		else ProdCounter[playerid] = 0;
		//сколько есть в грузовике
		if(VehInfo[trailerid][cLoad] < ProdCounter[playerid] && VehInfo[trailerid][cLoad] != 0) ProdCounter[playerid] = VehInfo[trailerid][cLoad];
		//если в грузовике меньше, чем может купить биз, то тогда разгружаться на всё что есть в грузовике

		if(ProdCounter[playerid] < 1)
		{
			format(strings, sizeof(strings), "%s не может оплатить даже еденицу груза.", BizInfo[biz][bDiscription]);
			SendClientMessage(playerid, COLOR_DARKRED, strings);
			//SendClientMessage(playerid, COLOR_DARKRED, "Но не отчаивайтесь, ведь кол-во загруженного сырья находится у вас в авто(USE: /load)");
			TrailerEnterCheckpoint(playerid);//для дальнобойщиков STEP9
			return 1;
		}
	}
//ИНФОРМИРОВАНИЕ
	//new strings[MAX_STRING];
	//format(strings, sizeof(strings), "2.CP_TRUCKER(player:%s, biz:%d) Prod:%d Load:%d",
	//	PlayerName(playerid), biz, ProdCounter[playerid], VehInfo[nCarID[playerid]][cLoad]);
	//Log(PACKET, strings);
	//Cargo[trailerid][tWeight] = VehInfo[nCarID[playerid]][cLoad];//временно записали,чтобы знать сколько осталось груза на момент выполнения заказа
	TogglePlayerControllableEx(playerid, 0);//игрок НЕ сможет двигаться
	gUnLoading[playerid] = 1;
	OnVehicleUnLoading(playerid, biz);//для дальнобойщиков STEP8
	//PlayAudioStreamForPlayerEx(playerid, "RepairActive.wav");
//TestLog(OPTIM, "OnPlayerEnterCheckpoint1.10 ", GetTickCount(), timers);
	return 1;
}

//для дальнобойщиков STEP9
stock TrailerEnterCheckpoint(playerid, money=0, salary=0)
{   //вызывается  из OnCargoTime по окончанию времени доставки, OnPlayerEnterCheckpoint при заезде с пустым прицепом или когда не может оплатить даже еденицу груза
///вызывается  из  OnVehicleUnLoading если Вы - не прикрепили полуприцеп к тягачу, У Вас Отсутствует Груз!
//надо учесть, что игрок может быть не в машине и у него закончится время
	new timers = GetTickCount();
	gTextDrawHideCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
    GPS_OnOff[playerid] = 0; DisablePlayerCheckpointEx(playerid);//CP[playerid] = 0;
	SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Маркер Задания убран !");

//ИНФОРМИРОВАНИЕ
	//new strtmp[112+24+3+3+3+5+5+10];
	//format(strtmp, sizeof(strtmp), "TrailerEnterCheckpoint1(player:%s Frailty:%d StartHealth:%.1f CurrentHealth:%.1f Load:%d Weight:%d Bonus:$%.2f)",
	//	PlayerName(playerid),
	//	Cargo[nCarID[playerid]][tFrailty],
	//	StartTruckHealth[nCarID[playerid]],
	//	CurrentTruckHealth[nCarID[playerid]],
	//	VehInfo[nCarID[playerid]][cLoad],
	//	Cargo[nCarID[playerid]][tWeight],
	//	Cargo[nCarID[playerid]][tBonus]);
	//Log(PACKET, strtmp);
	nCarID[playerid] = GetPlayerVehicleID(playerid);//получаем заново ИД тачки, т.к. игрок после того как сел за руль мог тп в другую тачку

	new trailerid;//, trailermodel;
	if(IsTrailerAttachedToVehicle(nCarID[playerid])) { nTrailerID[playerid] = GetVehicleTrailer(nCarID[playerid]); trailerid = nTrailerID[playerid];  }
	//nTrailerID[playerid] = GetVehicleTrailer(nCarID[playerid]);//Получить ID трейлера прикреплённого к машине.
	//nTrailerModel[playerid] = GetVehicleModel(nTrailerID[playerid]);//Узнает ID модели данного трейлера прикреплённого к машине.
	else { trailerid = nCarID[playerid];  }

    if((!IsTrailerAttachedToVehicle(nCarID[playerid]) || nTrailerID[playerid] == 0) && IsInHardTruck(nCarID[playerid]))
    {
		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}У вас Отсутствует Полуприцеп с грузом !");
		return 1;
	}

//ИНФОРМИРОВАНИЕ
	//format(strtmp, sizeof(strtmp), "TrailerEnterCheckpoint2(player:%s Frailty:%d StartHealth:%.1f CurrentHealth:%.1f Load:%d Weight:%d Bonus:$%.2f)",
	//	PlayerName(playerid), Cargo[trailerid][tFrailty], StartTruckHealth[nCarID[playerid]], CurrentTruckHealth[nCarID[playerid]], VehInfo[nCarID[playerid]][cLoad], Cargo[trailerid][tWeight], Cargo[trailerid][tBonus]);
	//Log(PACKET, strtmp);

	if(PlayerInfo[playerid][pCarTime] > 0 && ProdCounter[playerid] > 0 && nCarID[playerid] != 0)
	//if(Cargo[trailerid][tPeriod] > 0 && ProdCounter[playerid] > 0 && nCarID[playerid] != 0)
	{
		new trailer = GetVehicleTrailer(nCarID[playerid]);
		if(nTrailerID[playerid] != trailer && trailer != 0 && IsInHardTruck(nCarID[playerid]))
		{   //если игрок во время поездки подменил трейлер
			PlayerInfo[playerid][pTruckSkill] --;//уменьшить счётчик проф. уровня доставленных грузов
	    	format(strings, sizeof(strings), "Pаботодатель: {0080FF}Это [%d] не тот [%d] Полуприцеп с Грузом ! Доставка Аннулирована !",
				trailer, nTrailerID[playerid]);
			SendClientMessage(playerid, COLOR_GREEN, strings);
			goto Mark5;
			//return 1;
		}
		//----------------------------------------------------------------------
		if(VehInfo[trailerid][cLoad] <= 0)
		{
			GameTextForPlayerEx(playerid, "~r~Truck is empty, return to the stock house", 5000, 1);
			goto Mark5;
			//return 1;
		}
//ИНФОРМИРОВАНИЕ
	//format(strtmp, sizeof(strtmp), "TrailerEnterCheckpoint3(player:%s Frailty:%d StartHealth:%.1f CurrentHealth:%.1f Load:%d Weight:%d Bonus:$%.2f)",
	//	PlayerName(playerid), Cargo[trailerid][tFrailty], StartTruckHealth[nCarID[playerid]], CurrentTruckHealth[nCarID[playerid]], VehInfo[nCarID[playerid]][cLoad], Cargo[trailerid][tWeight], Cargo[trailerid][tBonus]);
	//Log(PACKET, strtmp);
		//----------------------------------------------------------------------
		//если время ещё не закончилось, т.е. вы пришли во время
		new skillbonus, skill;
	   	PlayerInfo[playerid][pTruckSkill] ++;//увеличить счётчик проф. уровня доставленных грузов
		new level = PlayerInfo[playerid][pTruckSkill];
		if(level == 50)//если игрок доставил 50 грузов то поднимается на следующий уровень 2
		{
			skill = 2; skillbonus = (200 + random(100))*10;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Вам доступен новый тягач Petrol Tanker.");
			GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, skillbonus);
	    	format(strings, sizeof(strings), "Bаш Навык Дальнобойщика теперь %d ! Гонорар %d$.", skill, skillbonus);
			SendClientMessage(playerid, COLOR_GREEN, strings);
		}
		else if(level == 100)
		{
			skill = 3; skillbonus = (300 + random(100))*10;
			GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, skillbonus);
	    	format(strings, sizeof(strings), "Bаш Навык Дальнобойщика теперь %d ! Гонорар %d$.", skill, skillbonus);
			SendClientMessage(playerid, COLOR_GREEN, strings);
		}
		else if(level == 200)
		{
			skill = 4; skillbonus = (400 + random(100))*10;
			GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, skillbonus);
	    	format(strings, sizeof(strings), "Bаш Навык Дальнобойщика теперь %d ! Гонорар %d$.", skill, skillbonus);
			SendClientMessage(playerid, COLOR_GREEN, strings);
		}
		else if(level == 400)
		{
			skill = 5; skillbonus = RANDMONEY5*10;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Вам доступен новый тягач Roadtrain.");
			GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, skillbonus);
	    	format(strings, sizeof(strings), "Bаш Навык Дальнобойщика теперь %d ! Гонорар %d$.", skill, skillbonus);
			SendClientMessage(playerid, COLOR_GREEN, strings);
		}
		//----------------------------------------------------------------------
//НАЧАЛО ПОЛУЧЕНИЯ СОСТОЯНИЯ
	    new Frailty = Cargo[trailerid][tFrailty];//хрупкость в процентах
		//GetVehicleHealth(nCarID[playerid], VehHealth[nCarID[playerid]]);
		//CurrentTruckHealth[nCarID[playerid]])/10 - текущее состояние машины в процентах
		//( 1.0 - (100.0-Frailty)/100.0 ) - коэф. ущерба с учетом хрупкости
		//new Float:Damage = ( (StartTruckHealth[nCarID[playerid]]-CurrentTruckHealth[nCarID[playerid]])/10 ) * ( 1.0 - (100.0-Frailty)/100.0 );//ущерб тягачу с учётом хрупкости груза
		new Float: Damage;
		if(StartTruckHealth[nCarID[playerid]] >= CurrentTruckHealth[nCarID[playerid]])
		{
			Damage = ( (StartTruckHealth[nCarID[playerid]]-CurrentTruckHealth[nCarID[playerid]])/10.0 ) * Frailty;//ущерб тягачу с учётом хрупкости груза
		}
		else Damage = 100.0;
		if(Damage >= 100.0 || Damage < 0.0) Damage = 100.0;
//КОНЕЦ ПОЛУЧЕНИЯ СОСТОЯНИЯ

		//money = floatround(VehInfo[nCarID[playerid]][cLoad]*Cargo[trailerid][tBonus]);//остаток кг умножили на цену за 1 кг
		//new salary;
		//new biz = Cargo[trailerid][tWhence];
		//if(biz >= 100) salary = SBizInfo[biz-100][sbSalary];
		//else salary = BizInfo[biz][bSalary];

//ИНФОРМИРОВАНИЕ
		//new strtmp[97+24+3+3+5+5+10+10];
		//format(strtmp, sizeof(strtmp), "TrailerEnterCheckpoint5(player:%s biz:%d Frailty:%d Damage:%.1f Load:%d Weight:%d Bonus:$%.2f salary:%d)",
		//	PlayerName(playerid), biz, Frailty, Damage, VehInfo[nCarID[playerid]][cLoad], Cargo[trailerid][tWeight], Cargo[trailerid][tBonus], salary);
		//Log(PACKET, strtmp);

		new msgitem[502];//46 + 42+47+59+43+47+39+37 + 48+35 + 3+3+(5+3)+10+10+10+5+10 = 502
		strcat(msgitem, "{AFAFAF}___________________________________\n");
		format(msgitem, sizeof(msgitem), "%s{0080FF}Хрупкость: \t\t{FFFFFF}%d %% \n", msgitem, Frailty);
		format(msgitem, sizeof(msgitem), "%s{0080FF}Груз повреждён: \t{FFFFFF}%.1f %% \n", msgitem, Damage);//Целостность груза:
		format(msgitem, sizeof(msgitem), "%s{0080FF}Целостность груза: \t{FFFFFF}%d кг[ %.1f %% ] \n", msgitem, VehInfo[trailerid][cLoad], (100.0-Damage) );
		format(msgitem, sizeof(msgitem), "%s{0080FF}Неустойка: \t\t{33AA33}$%d\n", msgitem,
			floatround((Cargo[trailerid][tWeight]-VehInfo[trailerid][cLoad])*Cargo[trailerid][tBonus]) );
		format(msgitem, sizeof(msgitem), "%s{0080FF}Стоимость груза: \t{33AA33}$%d\n", msgitem, money);
		format(msgitem, sizeof(msgitem), "%s{0080FF}Полученная прибыль: \t{33AA33}$%.2f\n", msgitem, Cargo[trailerid][tWeight]*Cargo[trailerid][tBonus]);
		format(msgitem, sizeof(msgitem), "%s{0080FF}Гонорар: \t\t{33AA33}$%d\n", msgitem, salary );
		format(msgitem, sizeof(msgitem), "%s{AFAFAF}___________________________________\n", msgitem);
		format(msgitem, sizeof(msgitem), "%s{0080FF}ИТОГО: \t\t{33AA33}$%d\n", msgitem, (money+salary));
		//TogglePlayerControllableEx(playerid, 0);//обездвиживает
		new caption[44+4];
		format(caption, sizeof(caption), "{0080FF}ЗАКАЗ ВЫПОЛНЕН за {FFFFFF}%d секунд", Cargo[ trailerid ][tPeriod] - PlayerInfo[playerid][pCarTime]);
		ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, caption, msgitem, "OK", "");
	}
	//else if(Cargo[ trailerid ][tPeriod] <= 0)
	else if(PlayerInfo[playerid][pCarTime] <= 0)//если время вышло
	{
		new biz = Cargo[trailerid][tWhence];
		if(biz >= 100)
		{
			new sbiz = biz-100;
			if(VehInfo[trailerid][cLoad] > Cargo[trailerid][tWeight])
			{
				SBizInfo[sbiz][sbProducts] += Cargo[trailerid][tWeight];
				format(strings, sizeof(strings), "* Вы не справились с заданием! {FFFFFF}%d{FF0000} продуктов возвращено в {FFFFFF}%s{FF0000}. Неустойка {FFFFFF}50 %%\%%: $%d.",
					Cargo[trailerid][tWeight], SBizInfo[sbiz][sbDiscription], floatround(Cargo[trailerid][tWeight]*Cargo[trailerid][tBuyPrice]/2, floatround_ceil));
		        SendClientMessage(playerid, COLOR_RED, strings);
			}
			else
			{
				SBizInfo[sbiz][sbProducts] += VehInfo[trailerid][cLoad];
				format(strings, sizeof(strings), "* Вы не справились с заданием!! {FFFFFF}%d{FF0000} продуктов возвращено в {FFFFFF}%s{FF0000}. Неустойка {FFFFFF}50 %%\%%: $%d.",
					VehInfo[trailerid][cLoad], SBizInfo[sbiz][sbDiscription], floatround(Cargo[trailerid][tWeight]*Cargo[trailerid][tBuyPrice]/2, floatround_ceil));
		        SendClientMessage(playerid, COLOR_RED, strings);
			}
		}
		else
		{
			if(Cargo[trailerid][CargoType] == 1)
			{//Металл - основа для производства товаров индустрии развлечений
				if(VehInfo[trailerid][cLoad] > Cargo[trailerid][tWeight])
				{
					BizInfo[biz][bMetal] += Cargo[trailerid][tWeight];
				}
				else BizInfo[biz][bMetal] += VehInfo[trailerid][cLoad];
			}
			else if(Cargo[trailerid][CargoType] == 2)
			{//Текстиль - основа для производства товаров розничной торговли
				if(VehInfo[trailerid][cLoad] > Cargo[trailerid][tWeight])
				{
					BizInfo[biz][bTextiles] += Cargo[trailerid][tWeight];
				}
				else BizInfo[biz][bTextiles] += VehInfo[trailerid][cLoad];
			}
			else if(Cargo[trailerid][CargoType] == 3)
			{//Продовольствие - основа для производства товаров ресторанного бизнеса
				if(VehInfo[trailerid][cLoad] > Cargo[trailerid][tWeight])
				{
					BizInfo[biz][bProvisions] += Cargo[trailerid][tWeight];
				}
				else BizInfo[biz][bProvisions] += VehInfo[trailerid][cLoad];
			}
			else if(Cargo[trailerid][CargoType] == 4)
			{//Древесины - основа для производства товаров сферы услуг
				if(VehInfo[trailerid][cLoad] > Cargo[trailerid][tWeight])
				{
					BizInfo[biz][bTree] += Cargo[trailerid][tWeight];
				}
				else BizInfo[biz][bTree] += VehInfo[trailerid][cLoad];
			}
			else if(Cargo[trailerid][CargoType] == 5)
			{//Нефть - основа для производства товара промышленной сферы
				if(VehInfo[trailerid][cLoad] > Cargo[trailerid][tWeight])
				{
					BizInfo[biz][bFuel] += Cargo[trailerid][tWeight];
				}
				else BizInfo[biz][bFuel] += VehInfo[trailerid][cLoad];
			}
			else
			{//товар на импорт
				if(VehInfo[trailerid][cLoad] > Cargo[trailerid][tWeight])
				{
					BizInfo[biz][bProducts] += Cargo[trailerid][tWeight];
				}
				else BizInfo[biz][bProducts] += VehInfo[trailerid][cLoad];
			}
			//BizInfo[biz][bTill] -= money;
			//BizInfo[biz][bImport] += money;
			if(biz == 80) UpdateStoreHouse();
			else if(biz == 81) UpdateOceanDock();

			format(strings, sizeof(strings), "* Вы не справились с заданием!!! Продукты возвращены в %s. Неустойка 50 %%\%%: $%d.",
				BizInfo[biz][bDiscription], floatround(Cargo[trailerid][tWeight]*Cargo[trailerid][tBuyPrice]/2, floatround_ceil));
	        SendClientMessage(playerid, COLOR_RED, strings);
		}
		VehInfo[trailerid][cLoad] -= Cargo[trailerid][tWeight];
		if(VehInfo[trailerid][cLoad] <= 0)
		{
			VehInfo[trailerid][cLoad] = 0;
			VehInfo[trailerid][cLoadType] = 0;
			VehInfo[trailerid][cWhere] = 0;
		}
		GivePlayerMoneyH(fjob+PlayerInfo[playerid][pJob], playerid, -floatround(Cargo[trailerid][tWeight]*Cargo[trailerid][tBuyPrice]/2.0, floatround_ceil));//1000 для экономики

		//GivePlayerMoneyH(fjob+PlayerInfo[playerid][pJob], playerid, -1000);
		//format(strings, sizeof(strings), "Pаботодатель: Время доставки истекло ! НЕУСТОЙКА $%d!", 1000);
		//SendClientMessage(playerid, COLOR_RED, strings);
		GameTextForPlayerEx(playerid, "~w~Cargo Delivery~n~~r~Shipment is Not Delivered", 2500, 1);
	}
Mark5:

	TruckerCargoInit(playerid);
	//ProdCounter[playerid]  = 0;обнуляется в OnVehicleUnLoading, иначе будет равна нулю и не будет отниматься груз

	/*if( nTrailerID[playerid] != 0 &&
		VehInfo[trailerid][cOwned] != PlayerInfo[playerid][pSQLID] )
	{   //если прицеп не личный
		SetVehicleToRespawnEx(playerid, nTrailerID[playerid]);//забрать трейлер у игрока
	}*/
	
	new strtmp[26+24];
	strcat(strtmp, "TrailerEnterCheckpoint ");
	strcat(strtmp, PlayerName(playerid));
	TestLog(OPTIM, strtmp, GetTickCount(), timers);//new timers = GetTickCount();
	return 1;
}

//для дальнобойщиков STEP8
stock OnVehicleUnLoading(playerid, biz)//вызывается из секундного таймера и OnPlayerEnterCheckpoint
{//biz - КУДА
	new timers = GetTickCount();
	if(gLoading[playerid] != 0) return 1;
	if(gUnLoading[playerid] == 0) return 1;

	if(PlayerInfo[playerid][pJob] != TRUCKER) return 1;
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) { return 1; }
	if(	VehicleArray[nCarModel[playerid]-400][Category] != Station_Wagons &&
		VehicleArray[nCarModel[playerid]-400][Category] != Industrial &&
		VehicleArray[nCarModel[playerid]-400][Category] != Lorries//все грузовики
	  )	return 1;
	new trailerid, trailermodel;
	if(IsTrailerAttachedToVehicle(nCarID[playerid])) { trailerid = nTrailerID[playerid]; trailermodel = nTrailerModel[playerid]; }
	else { trailerid = nCarID[playerid]; trailermodel = nCarModel[playerid]; }
	if(trailerid == 0)  return 1;

//ИНФОРМИРОВАНИЕ
	new strtmp[MAX_STRING];
	//format(strings, sizeof(strings), "biz:%d gUnLoading:%d tmpCounter:%d ProdCounter:%d",
//		biz, gUnLoading[playerid], tmpCounter[playerid], ProdCounter[playerid]);
	//SendClientMessage(playerid, COLOR_YELLOW, strings);
	
	if((!IsTrailerAttachedToVehicle(nCarID[playerid]) || nTrailerID[playerid] == 0) && IsInHardTruck(nCarID[playerid]))
	{   //если Вы сели в грузовик
		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы - не прикрепили полуприцеп к тягачу !");

		gGameText[playerid] = 0;
		tmpCounter[playerid] = 0;
		gUnLoading[playerid] = 0;
		TogglePlayerControllableEx(playerid, 1);//игрок сможет двигаться

		TrailerEnterCheckpoint(playerid);
		return 1;
	}
//TestLog(OPTIM, "OnVehicleUnLoading1.1 ", GetTickCount(), timers);
	if(	ProdCounter[playerid] <= 0)
	{
		gGameText[playerid] = 0;
		tmpCounter[playerid] = 0;
		gUnLoading[playerid] = 0;
		TogglePlayerControllableEx(playerid, 1);//игрок сможет двигаться
		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}У Вас Отсутствует Груз!");

		TrailerEnterCheckpoint(playerid);
		return 1;
	}
	gGameText[playerid] = 1;
	SetPlayerGameTextScale(playerid, "UnLoading Vehicle", tmpCounter[playerid], ProdCounter[playerid]);

	new skill, level = PlayerInfo[playerid][pTruckSkill];
	if(	level < 50 ) skill = 1;
	else if(level >= 50  && level < 100) skill = 2;
	else if(level >= 100  && level < 200) skill = 3;
	else if(level >= 200  && level < 400) skill = 4;
	else if(level >= 400) skill = 5;

	if(Cargo[trailerid][CargoType] == 5) tmpCounter[playerid] += 40;
	else if(Cargo[trailerid][CargoType] == 6 && Cargo[trailerid][tWhence] == 80) tmpCounter[playerid] += 1000;
	else if(skill == 1) tmpCounter[playerid] += 20;//скорость разгрузки по 30 в секунду
	else if(skill == 2) tmpCounter[playerid] += 24;
	else if(skill == 3) tmpCounter[playerid] += 27;
	else if(skill == 4) tmpCounter[playerid] += 29;
	else if(skill == 5) tmpCounter[playerid] += 30;//скорость разгрузки по 75 в секунду

	new amount3;
	if(Cargo[trailerid][tWhence] == 80)
	{//если поставка со склада, то увеличиваем предел загрузки в 10 раз
		amount3 = VehicleArray[trailermodel-400][Weight];//*10;
	}
	else
	{//иначе максимальная загрузка не больше половины веса грузовика
		amount3 = VehicleArray[trailermodel-400][Weight]/2;
	}

	new salary;
 	if(tmpCounter[playerid] >= ProdCounter[playerid] && ProdCounter[playerid] != 0)
	{
		StopAudioStreamForPlayerEx(playerid);
		gGameText[playerid] = 0;
		tmpCounter[playerid] = 0;
		gUnLoading[playerid] = 0;//опустили флаг - окончили заправку
		TogglePlayerControllableEx(playerid, 1);//игрок сможет двигаться
		new cost;
		if(biz >= 100)//куда
		{
			new sbiz = biz-100;//куда
			if(sbiz >= GAS_STATION && sbiz < PARKING)
			{
				salary += floatround(SBizInfo[sbiz][sbSalary]*(ProdCounter[playerid]*100/amount3)/100);
//где (ProdCounter[playerid]*100/amount3) - процент загруженности
				SBizInfo[sbiz][sbTill] -= salary;
			}
			if(Cargo[trailerid][tWhence] >= 100)
			{
				new sb = Cargo[trailerid][tWhence]-100;//откуда
				salary += floatround(SBizInfo[sb][sbSalary]*(ProdCounter[playerid]*100/amount3)/100);
				SBizInfo[sb][sbTill] -= salary;
			}
			else
			{
				new b = Cargo[trailerid][tWhence];//откуда
				salary += floatround(BizInfo[b][bSalary]*(ProdCounter[playerid]*100/amount3)/100);
				BizInfo[b][bTill] -= salary;
			}
			//сколько сможет оплатить
			//price = compcost*(100+SBizInfo[sbiz][sbBuyProd])/100.0;
			cost = floatround(ProdCounter[playerid]*Cargo[trailerid][tSellPrice], floatround_floor);
			SBizInfo[sbiz][sbProducts] += ProdCounter[playerid];
			//if(sbiz != GAS_STATION-1)
			SBizInfo[sbiz][sbTill] -= cost;
			SBizInfo[sbiz][sbImport] += cost;

   			if(	!(sbiz >= GAS_STATION && sbiz < PARKING+sizeof(Parking)) &&
			   	SBizInfo[sbiz][sbTill] < 2250) SBizInfo[sbiz][sbBuyProd] = 10;
   			else if(sbiz >= GAS_STATION && sbiz < PARKING &&
			   	SBizInfo[sbiz][sbTill] < 2250) SBizInfo[sbiz][sbBuyProd] = 40;
			//SaveSBiz(sbiz);

			new giveplayerid = ReturnUser(SBizInfo[sbiz][sbOwner]);
		    if( IsPlayerConnectedEx(giveplayerid) )
			{
				format(strings, sizeof(strings), "%s покупка: {FFFFFF}%s в кол-ве %d кг на сумму {33AA33}$%d привёз: %s[%d]",
					SBizInfo[sbiz][sbDiscription], TypeCargo(Cargo[trailerid][CargoType]), ProdCounter[playerid], cost, PlayerName(playerid), playerid);
				SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, strings);//#define COLOR_LIGHTBLUE 	0x0080FFFF
			}
		}
		else
		{
			if(Cargo[trailerid][tWhence] >= 100) {
				new sb = Cargo[trailerid][tWhence]-100;
				salary = floatround(SBizInfo[sb][sbSalary]*(ProdCounter[playerid]*100/amount3)/100);
//где (ProdCounter[playerid]*100/amount3) - процент загруженности
				SBizInfo[sb][sbTill] -= salary;
			}
			else {
				new b = Cargo[trailerid][tWhence];
				salary = floatround(BizInfo[b][bSalary]*(ProdCounter[playerid]*100/amount3)/100);
				BizInfo[b][bTill] -= salary;
			}
			//сколько сможет оплатить
			cost = floatround(ProdCounter[playerid]*Cargo[trailerid][tSellPrice], floatround_floor);

			if(Cargo[trailerid][CargoType] == 1)
			{//Металл - основа для производства товаров индустрии развлечений
				BizInfo[biz][bMetal] += ProdCounter[playerid];
			}
			else if(Cargo[trailerid][CargoType] == 2)
			{//Текстиль - основа для производства товаров розничной торговли
				BizInfo[biz][bTextiles] += ProdCounter[playerid];
			}
			else if(Cargo[trailerid][CargoType] == 3)
			{//Продовольствие - основа для производства товаров ресторанного бизнеса
				BizInfo[biz][bProvisions] += ProdCounter[playerid];
			}
			else if(Cargo[trailerid][CargoType] == 4)
			{//Древесины - основа для производства товаров сферы услуг
				BizInfo[biz][bTree] += ProdCounter[playerid];
			}
			else if(Cargo[trailerid][CargoType] == 5)
			{//Нефть - основа для производства товара промышленной сферы
				BizInfo[biz][bFuel] += ProdCounter[playerid];
			}
			else
			{//товар на импорт
				BizInfo[biz][bProducts] += ProdCounter[playerid];
			}
			BizInfo[biz][bTill] -= cost;
			BizInfo[biz][bImport] += cost;
			if(BizInfo[biz][bTill] < 2250 && biz > 0 && biz < 80) BizInfo[biz][bBuyProd] = 40;

			new giveplayerid = ReturnUser(BizInfo[biz][bOwner]);
		    if( IsPlayerConnectedEx(giveplayerid) )
			{
				format(strings, sizeof(strings), "%s покупка: {FFFFFF}%s в кол-ве %d кг на сумму {33AA33}$%d привёз: %s[%d]",
					BizInfo[biz][bDiscription], TypeCargo(Cargo[trailerid][CargoType]), ProdCounter[playerid], cost, PlayerName(playerid), playerid);
				SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, strings);//#define COLOR_LIGHTBLUE 	0x0080FFFF
			}

			if(biz == 80) UpdateStoreHouse();
			else if(biz == 81) UpdateOceanDock();
			//SaveBiz(biz);
		}
		GivePlayerMoneyH(fjob+PlayerInfo[playerid][pJob], playerid, (cost + salary));
		//new strtmp[95];//81+5+6+3 = 95
		format(strtmp, sizeof(strtmp), "%d {0080FF}продуктов продано на сумму {33AA33}$%d {0080FF}по цене {33AA33}$%.1f за шт.",
			ProdCounter[playerid], cost, Cargo[trailerid][tSellPrice]);
		SendClientMessage(playerid, COLOR_GREEN, strtmp);

//ИНФОРМИРОВАНИЕ
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "OnVehicleUnLoading(player:%s, Whence:%d Where:%d) Load:%d Prod:%d Money:%d",
			PlayerName(playerid), Cargo[trailerid][tWhence], biz, VehInfo[trailerid][cLoad], ProdCounter[playerid], cost);
		Log(TRUCK, strings);
		//SendClientMessageToAll(COLOR_YELLOW, strings);

		TrailerEnterCheckpoint(playerid, cost, salary);//для дальнобойщиков STEP9

		VehInfo[trailerid][cLoad] -= ProdCounter[playerid];
		if(VehInfo[trailerid][cLoad] <= 0)
		{//если разгрузили весь груз, то только тогда обнулять
			VehInfo[trailerid][cLoad] = 0;
			VehInfo[trailerid][cLoadType] = 0;
			VehInfo[trailerid][cWhere] = 0;
		}
		ProdCounter[playerid] = 0;
	}
	new str[50];//26+24 = 50
	strcat(str, "OnVehicleUnLoading ");
	strcat(str, PlayerName(playerid));
	TestLog(OPTIM, str, GetTickCount(), timers);
	return 1;
}//для дальнобойщиков конец

stock AbandonToTasks(playerid)
{//отказ от задания
	if(PlayerInfo[playerid][pJob] != TRUCKER) return 1;
	if(nCarID[playerid] == 0)  return 1;
	//nCarID[playerid] = GetPlayerVehicleID(playerid);//получить ID машины игрока из списка установленных моделей
	//nCarModel[playerid] = GetVehicleModel(nCarID[playerid]);//Узнает ID модели данного транспортного средства.
	if(	//!IsInHardTruck(nCarID[playerid]) && !IsInTruck(nCarID[playerid]) &&
		VehicleArray[nCarModel[playerid]-400][Category] != Station_Wagons &&
		VehicleArray[nCarModel[playerid]-400][Category] != Industrial &&
		VehicleArray[nCarModel[playerid]-400][Category] != Lorries//все грузовики
	  )	return 1;
	  
	if(CurState[playerid] != PLAYER_STATE_DRIVER)
	{   //чтобы не мог пассажир отсоеденить прицеп
		//SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться за рулём транспортного средства!");
		return 1;
	}
    if(CP[playerid] != CP_TRUCKER)//если прицеп загружен
    {
    	SendClientMessage(playerid, COLOR_GREY, "   У вас нет задания, чтобы от него отказаться.");
    	return 1;
    }
	gTextDrawHideCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
	
	new trailerid;
	if(IsTrailerAttachedToVehicle(nCarID[playerid])) trailerid = nTrailerID[playerid];
	else trailerid = nCarID[playerid];
	
	//new money;	//new Float: price;
	new biz = Cargo[trailerid][tWhence];
	if(biz >= 100)
	{
		new sbiz = biz-100;
		if(VehInfo[trailerid][cLoad] > Cargo[trailerid][tWeight])
		{
			SBizInfo[sbiz][sbProducts] += Cargo[trailerid][tWeight];
			format(strings, sizeof(strings), "* Вы Отказались от задания. {FFFFFF}%d{0080FF} продуктов возвращено в %s. Неустойка 50 %%\%%: $%d.",
				Cargo[trailerid][tWeight], SBizInfo[sbiz][sbDiscription], floatround(Cargo[trailerid][tWeight]*Cargo[trailerid][tBuyPrice]/2.0, floatround_ceil));
	        SendClientMessage(playerid, COLOR_RED, strings);
		}
		else
		{
			SBizInfo[sbiz][sbProducts] += VehInfo[trailerid][cLoad];
			format(strings, sizeof(strings), "* Вы Отказались от задания. {FFFFFF}%d{0080FF} продуктов возвращено в %s. Неустойка 50 %%\%%: $%d.",
				VehInfo[trailerid][cLoad], SBizInfo[sbiz][sbDiscription], floatround(Cargo[trailerid][tWeight]*Cargo[trailerid][tBuyPrice]/2.0, floatround_ceil));
	        SendClientMessage(playerid, COLOR_RED, strings);
		}
	}
	else
	{
		if(Cargo[trailerid][CargoType] == 1)
		{//Металл - основа для производства товаров индустрии развлечений
			if(VehInfo[trailerid][cLoad] > Cargo[trailerid][tWeight])
			{
				BizInfo[biz][bMetal] += Cargo[trailerid][tWeight];
			}
			else BizInfo[biz][bMetal] += VehInfo[trailerid][cLoad];
		}
		else if(Cargo[trailerid][CargoType] == 2)
		{//Текстиль - основа для производства товаров розничной торговли
			if(VehInfo[trailerid][cLoad] > Cargo[trailerid][tWeight])
			{
				BizInfo[biz][bTextiles] += Cargo[trailerid][tWeight];
			}
			else BizInfo[biz][bTextiles] += VehInfo[trailerid][cLoad];
		}
		else if(Cargo[trailerid][CargoType] == 3)
		{//Продовольствие - основа для производства товаров ресторанного бизнеса
			if(VehInfo[trailerid][cLoad] > Cargo[trailerid][tWeight])
			{
				BizInfo[biz][bProvisions] += Cargo[trailerid][tWeight];
			}
			else BizInfo[biz][bProvisions] += VehInfo[trailerid][cLoad];
		}
		else if(Cargo[trailerid][CargoType] == 4)
		{//Древесины - основа для производства товаров сферы услуг
			if(VehInfo[trailerid][cLoad] > Cargo[trailerid][tWeight])
			{
				BizInfo[biz][bTree] += Cargo[trailerid][tWeight];
			}
			else BizInfo[biz][bTree] += VehInfo[trailerid][cLoad];
		}
		else if(Cargo[trailerid][CargoType] == 5)
		{//Нефть - основа для производства товара промышленной сферы
			if(VehInfo[trailerid][cLoad] > Cargo[trailerid][tWeight])
			{
				BizInfo[biz][bFuel] += Cargo[trailerid][tWeight];
			}
			else BizInfo[biz][bFuel] += VehInfo[trailerid][cLoad];
		}
		else
		{//товар на импорт
			if(VehInfo[trailerid][cLoad] > Cargo[trailerid][tWeight])
			{
				BizInfo[biz][bProducts] += Cargo[trailerid][tWeight];
			}
			else BizInfo[biz][bProducts] += VehInfo[trailerid][cLoad];
		}
		if(biz == 80) UpdateStoreHouse();
		else if(biz == 81) UpdateOceanDock();
		format(strings, sizeof(strings), "* Вы Отказались от задания. Продукты возвращены в %s. Неустойка 50 %%\%%: $%d.",
		BizInfo[biz][bDiscription], floatround(Cargo[trailerid][tWeight]*Cargo[trailerid][tBuyPrice]/2.0, floatround_ceil));
        SendClientMessage(playerid, COLOR_RED, strings);
	}
	VehInfo[trailerid][cLoad] -= Cargo[trailerid][tWeight];
	if(VehInfo[trailerid][cLoad] <= 0)
	{
		VehInfo[trailerid][cLoad] = 0;
		VehInfo[trailerid][cLoadType] = 0;
		VehInfo[trailerid][cWhere] = 0;
	}

	GivePlayerMoneyH(fjob+PlayerInfo[playerid][pJob], playerid, -floatround(Cargo[trailerid][tWeight]*Cargo[trailerid][tBuyPrice]/2.0, floatround_ceil));//1000 для экономики

	ProdCounter[playerid] = 0;

	TruckerCargoInit(playerid);//обнуляем при нажатии нум2

    //DisablePlayerCheckpointEx(playerid);//CP[playerid] = 0;
	//GPS_OnOff[playerid] = 0;//отключилил GPS
	
	/*if(	IsTrailerAttachedToVehicle(nCarID[playerid]) &&
		PlayerInfo[playerid][pTruckSkill] < 200)
	{	//проверяет была ли машины прикреплена к трейлеру.
	    SetVehicleToRespawnEx(playerid, nTrailerID[playerid]);//вернуть прицеп на респ
	    GameTextForPlayerEx(playerid, "~r~Detach ~w~Trailer ~y~From Vehicle!",3000,1);
	}*/
	return 1;
}


//##############################################################################//
//                                                                              //
//                            ФУНКЦИИ РАБОТЫ С ПРИЦЕПАМИ                        //
//                                                                              //
//##############################################################################//


//##############################################################################//
//                                                                              //
//                                 СИСТЕМА ГОНОК                                //
//                                                                              //
//##############################################################################//


stock StartTruckRace()
{//не используется
	if(gRaceStarted == 0 && RacingMenu != 1)
	{   //если гонка не запущено и в меню гонки ни кого нет
		if(RacingMenu == 2)	//для дальнобойщиков STEP11
		{
		    //определяем состав дальнобойщиков по нахождению в радиусе
		    new found;
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i)) continue;
				if( !gPlayerSpawned[i] ) continue;
				//if( AFK_IdleTime[i] >= 3) continue;
				if(PlayerInfo[i][pJob] != TRUCKER) continue;
			 	RemovePlayerMapIcon(i, MAX_PLAYER_ICONS);
	    		//format(strings, sizeof(strings), "На мосту Гант через 5 минут будут гонки на тягачах за право найма водителей. Приз: $5000", TotalRate);
				SendClientMessage(i, COLOR_BLUEGREY, "Приготовтесь !!!");
		   		if( IsPlayerInRangeOfPoint(i, 30.0, GridPos[0],GridPos[1],GridPos[2]) ||
				   	IsPlayerInRangeOfPoint(i, 30.0, GridPos[4],GridPos[5],GridPos[6]))
			 	{

					//подключаем гонщиков с проверкой всех условий
					found ++;
					StartRingRace(i);//для дальнобойщиков STEP12
				}
			}
			if(found >= 2)
			{
			    //запускаем отсчёт
				KillTimer(gCountdowntimer); gCountdowntimer = -1;//убить предыдущий (навсякий  случай), чтобы можно было установить новый
				gCountdowntimer = SetTimer("RaceCountdown", 1000, 1);//для гонок STEP4
				//запускаем таймер отсчёта
			}
			else
			{
				//gRaceStarted = 0;//опускаем флаг - гонка закончилась
				//TotalRacers = 0;//обнуляем общее кол-во гонщиков 0
				//KillTimer(endracetimer); endracetimer = -1;
	 			RacingMenu = 0;//опустили флаг - вышел из меню
	   			SendClientMessageToAll(COLOR_GREEN, "Гонка не состоялась. На старте не было 2-х гонщиков.");
   			}
		}
		else //для дальнобойщиков STEP10
		{
			new found;
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i)) continue;
				if( !gPlayerSpawned[i] ) continue;
				if(PlayerInfo[i][pJob] != TRUCKER) continue;
				if( !IsInHardTruck(nCarID[i]) ) continue;
				//if(PlayerInfo[i][pJob] == TRUCKER)	//для дальнобойщиков
				//{
				RemovePlayerMapIcon(i, MAX_PLAYER_ICONS);
				SetPlayerMapIcon(i, MAX_PLAYER_ICONS, -2682.0315,1273.8556,61.2178, 53, 0, MAPICON_GLOBAL);
				//}

				found ++;
	    		format(strings, sizeof(strings), "На мосту Гант через 5 минут будут гонки на тягачах за право найма водителей. Приз: $%d", TotalRate);
				SendClientMessage(i, COLOR_BLUEGREY, strings);
				SendClientMessage(i, COLOR_BLUEGREY, "Гонка начнётся только при наличии 2-х и более дальнобойщиков.");
			}
			if(found >= 2)
			{
				TotalRate = 5000;//перезаписали общую ставку
				RacingMenu = 2;
				LoadRace("RING");
				strmid(SelectRace, "RING", 0, strlen("RING"), 20);
			}
			//SendClientMessageToAll(COLOR_YELLOW, "На кольце через 5 минут будут гонки на тягачах за право найма водителей.");
		}
//format(strings, sizeof(strings), "RacingMenu %d", RacingMenu);
//ABroadCast(COLOR_MAROON,strings, 3);
	}
	//для дальнобойщиков конец
}



//для дальнобойщиков STEP12
stock StartRingRace(playerid)
{
   	if(!IsPlayerInAnyVehicle(playerid))
	{
		SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться за рулём транспортного средства !");
		return 1;
	}
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	{
		SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться за рулём транспортного средства !");
		return 1;
	}
	if(PlayerInfo[playerid][pInt] != 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться НЕ в интерьере !");
		return 1;
	}
	if(gRaceStarted)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Гонка уже началась. Подождите окончания гонки.");
		return 1;
	}
	if(gInRacing[playerid])
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы уже участвуете в гонке.");
		return 1;
	}
	if(gOnDuty[playerid])
	{   //если коп и не на дежурстве и не в розыске
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете участвовать в гонке на службе.");
		return 1;
	}
	if(gJobDuty[playerid])
	{   //если коп и не на дежурстве и не в розыске
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете участвовать в гонке на дежурстве.");
		return 1;
	}
	if( IsInIntCar(nCarID[playerid]) )
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете участвовать в гонке на дерби-тачках.");
		return 1;//SLAdd // && HireCarID[playerid] == MAX_VEHICLES-1
	}
	if( IsInRentCar(nCarID[playerid]) && HireCarID[playerid] == MAX_VEHICLES-1)
	{
		SendClientMessage(playerid, COLOR_GREY, "  Вы не можете участвовать в гонке на арендованых тачках, пока не оплатите аренду!");
		return 1;
	}
	if(PlayerInfo[playerid][pLevel] < 2)
	{
		SendClientMessage(playerid,  COLOR_GREY, "   Вы не можете участвовать в гонке на первом уровне !");
		return 1;
	}
	if(WantedPoints[playerid] > 0)
	{
		SendClientMessage(playerid,  COLOR_GREY, "   Вы не можете участвовать в гонке находясь в розыске !");
		return 1;
	}
    if(PlayerCuffed[playerid] < MAX_PLAYERS-1)
    {
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете участвовать в гонке находясь в наручниках !");
        return 1;
    }
	if(PlayerTied[playerid] > 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не можете участвовать в гонке связанным !");
		return 1;
	}
	if(PlayerInfo[playerid][pJailed] > 0)
	{
		SendClientMessage(playerid,  COLOR_GREY, "   Вы не можете участвовать в гонке под арестом !");
		return 1;
	}
	if( IsPlayerInArea(playerid, specialzone[10]) )
	{
		SendClientMessage(playerid,  COLOR_GREY, "   Вы не можете участвовать в гонке пока находитесь в паркинге !");
		return 1;
	}
	if( gInAdventure[playerid] != 0 )
	{
		SendClientMessage(playerid,  COLOR_GREY, "   Вы не можете участвовать в гонке во время квеста !");
		return 1;
	}
	//----------------------------------------------------------
	if(!strcmp(gRaceMaker, "AVANGARD", true))
	{   //если в файле гонки установлено слово AVANGARD
		if(	nCarModel[playerid] != gCars[0] &&
			nCarModel[playerid] != gCars[1] &&
			nCarModel[playerid] != gCars[2] &&
			nCarModel[playerid] != gCars[3] &&
			nCarModel[playerid] != gCars[4] &&
			nCarModel[playerid] != gCars[5])
		{   //то проводим проверку на модель машины игрока
			SendClientMessage(playerid, COLOR_GREY, "   Ваше транспортное средство не соответствует данному типу гонки !");
			return 1;
		}
	}

	PlaySoundForPlayer(playerid, 3200);
	TogglePlayerControllableEx(playerid, 0);//обездвиживает игрока
	gInRacing[playerid] = 1;//вошёл в гонку
	TotalRacers ++;//увеличить кол-во гонщиков
	racecountdown = 15;//начать заново отсчёт

	//new strings[MAX_STRING];

   	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if( !gInRacing[i] ) continue;
		if(gRace[i] != 0) continue;//если чат активирован
		format(strings, sizeof(strings), "%s присоединился к гонке %s",
			PlayerName(playerid),SelectRace);
		SendClientMessage(i, COLOR_BLUEGREEN, strings);
	}
	SendClientMessage(playerid, COLOR_GREY, "   Дождитесь запуска гонки.");

	SetRaceText(playerid, TotalRacers);//для гонок STEP4
	//для показа позиции и приставки append в TextDraw

	SetPVarInt(playerid, "PlayerProgressCount", 0);//обнуляем кол-во пройденых игроком CP
	SetCheckpoint(playerid, GetPVarInt(playerid, "PlayerProgressCount"), gMaxCheckpoints);

    if(TextDrawShowMessage[playerid] == true)
	{
		TextDrawHideForPlayer(playerid, txdSystemMessage);
	}
	//gTextDrawShowRace[playerid] = true;  OnPlayerTextDrawStateChange(playerid);

	new tmp[8+2+2];
	//new temp[5]; format(temp,5, "/%d", TotalRacers);//sizeof(temp)
	//TextDrawSetStringEx(txdTotalRacers, temp);
	format(tmp, sizeof(tmp), "%d / %d", pos, TotalRacers);//sizeof(tmp)
	PlayerTextDrawSetStringEx(playerid, txdPositionOfTotal[playerid], tmp);//позиция игрока
	//TextDrawSetStringEx(txdRaceTime, "0:00");
	PlayerTextDrawSetStringEx(playerid, txdRaceTime[playerid], "00:00");
	return 1;
}


//##############################################################################//
//                                                                              //
//                           СИСТЕМА КРАЖИ ПОЛУПРИЦЕПОВ                         //
//                                                                              //
//##############################################################################//


stock GetTaskOnCargo(playerid, trailerid, whence, where, cargo, cost, time)
{
	if(!IsInHardTruck(nCarID[playerid])) return 1;

	new dlgitem[683];//212+207 + 24+3+ 20+2+20+2+1+20 + 10+6+5+10 = 542
	format(dlgitem, sizeof(dlgitem), "{FFFF00}Дальнобойщик: {FFFFFF}%s[%d]\
\n{FFFF00}Откуда: {FFFFFF}%s[%d]\
\n{FFFF00}Куда: {FFFFFF}%s[%d]\
\n{FFFF00}Тип груза: {FFFFFF}%d(%s)\
\n{FFFF00}Стоимость груза: {33AA33}$%d\
\n{FFFF00}Время: {FFFFFF}%s[%d]",
		PlayerName(playerid), playerid,
		GetDiscription(whence), whence, GetDiscription(where), where,
		cargo, TypeCargo(cargo),
		cost,
		TimeConverter(time), time);

	strcat(dlgitem, "\n{8CAA63}Примечание:\n");
	strcat(dlgitem, "\t- вам нужен напарник на тягаче.\n");
	strcat(dlgitem, "\t- Num6 - запрыгнуть на прицеп\n");
	strcat(dlgitem, "\t- Num4 - отцепить прицеп находясь на крыше тягача");

	if(strlen(dlgitem) > sizeof(dlgitem))
	{
		//ИНФОРМИРОВАНИЕ
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "Error: GetTaskOnCargo %s[%d], strlen(dlgitem): %d, sizeof(dlgitem): %d",
			PlayerName(playerid), playerid, strlen(dlgitem), sizeof(dlgitem));
		Log(ERROR, strings);
		return 1;
	}
	if(strlen(dlgitem) <= 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   GetTaskOnCargo пуст");//COLOR_BLUEGREY
		return 1;
	}
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(PlayerInfo[i][pMember] != LCN && PlayerInfo[i][pMember] != Yakuza) continue;
		SetPVarInt(i, "Trucker", playerid);
		SetPVarInt(i, "Trailer", trailerid);
		ShowPlayerDialogEx(i, FTASK_DIALOG, DIALOG_STYLE_MSGBOX, "Задание по захвату груза", dlgitem, "Accept", "Cancel");//для дальнобойщиков STEP4
	}
	return 1;
}
stock RobberyDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != FTASK_DIALOG) return 1;//для дальнобойщиков STEP4
	if(!response) return 1;

	new msgitem[256+1];
	new giveplayerid = GetPVarInt(playerid, "Trucker");
	new trailerid = GetPVarInt(playerid, "Trailer");
	if(IsPlayerConnected(giveplayerid))
	{
	    if(MarkerToPlayer[playerid] == MAX_PLAYERS-1)
		{//playerid - ID игрока, которому нужно показать маркер, giveplayerid - тот кто будет обозначен
			SetPlayerMarkerForPlayerEx(playerid, giveplayerid, COLOR_MAROON);
			format(msgitem, sizeof(msgitem), "* Маркер на игроке %s[%d] установлен.", PlayerName(giveplayerid), giveplayerid);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
			SendClientMessage(playerid, COLOR_GREY, "   При возникновении его в пределах видимости, он будет показан на радаре бордовым цветом.");
			//gMarkerFor[playerid] = 1;

		}

		new dlgitem[683];//212+207 + 24+3+ 20+2+20+2+1+20 + 10+6+5+10 = 542
		format(dlgitem, sizeof(dlgitem), "{FFFF00}Дальнобойщик: {FFFFFF}%s[%d]\
\n{FFFF00}Откуда: {FFFFFF}%s[%d]\
\n{FFFF00}Куда: {FFFFFF}%s[%d]\
\n{FFFF00}Тип груза: {FFFFFF}%d(%s)\
\n{FFFF00}Вес груза: {FFFFFF}%d кг\
\n{FFFF00}Время: {FFFFFF}%s[%d]",
			PlayerName(giveplayerid), giveplayerid,
			GetDiscription(Cargo[trailerid][tWhence]), Cargo[trailerid][tWhence],
			GetDiscription(Cargo[trailerid][tWhere]), Cargo[trailerid][tWhere],
			Cargo[trailerid][CargoType], TypeCargo(Cargo[trailerid][CargoType]),
			Cargo[trailerid][tWeight],
			TimeConverter(Cargo[trailerid][tPeriod]), Cargo[trailerid][tPeriod]);

		strcat(dlgitem, "\n{8CAA63}Примечание:\n");
		strcat(dlgitem, "\t- Вам нужен напарник.\n");
		strcat(dlgitem, "\t- Если груз будет доставлен, вы получите профскил\n");
		strcat(dlgitem, "\t- В случае неудачи профскил будет понижен");

		if(strlen(dlgitem) > sizeof(dlgitem))
		{
			//ИНФОРМИРОВАНИЕ
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "Error: GetTaskOnCargo %s[%d], strlen(dlgitem): %d, sizeof(dlgitem): %d",
				PlayerName(playerid), playerid, strlen(dlgitem), sizeof(dlgitem));
			Log(ERROR, strings);
			return 1;
		}
		if(strlen(dlgitem) <= 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   GetTaskOnCargo пуст");//COLOR_BLUEGREY
			return 1;
		}
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if( !IsPlayerConnectedEx(i) ) continue;
			if(PlayerInfo[i][pMember] != DoT) continue;
			if(!gOnDuty[i]) continue;
			SetPVarInt(i, "Trucker", playerid);
			SetPVarInt(i, "Trailer", trailerid);
			ShowPlayerDialogEx(i, DIALOG100, DIALOG_STYLE_MSGBOX, "Задание по защите груза", dlgitem, "Accept", "Cancel");//для дальнобойщиков STEP4
		}
	}
	//SetVehicleParamsForPlayerEx(trailerid, playerid, 1, 0);
	return 1;
}



stock trucker_OnPlayerKeyState_RIGHT(playerid)
{
//if(PRESSED(KEY_ANALOG_RIGHT))
//для угона прицепов на ходу
	if(IsPlayerInAnyVehicle(playerid)) return 1;
 //если вы НА тачке
 	new SurfingVehicleID = GetPlayerSurfingVehicleID(playerid);//возвращает INVALID_VEHICLE_ID если в тачке нету водителя
	if(SurfingVehicleID == INVALID_VEHICLE_ID) return 1;
	//PLAYER_STATE_SURFING
	//GetPlayerSurfingVehicleID

//format(strings, sizeof(strings), "SurfingVehicleID: %d", SurfingVehicleID);//, PlayerName(playerid)
//SendClientMessage(playerid, -1, strings);
	new trailerid = 0;
	new Float:vX,Float:vY,Float:vZ;
	new Float:trX,Float:trY,Float:trZ,Float:trA;

	new vid = 1;
	for(new v=0; v!=-1; v=StreamedVehicle[playerid][v])
	{
		if(StreamedVehicle[playerid][v] == -1) continue;
		vid = StreamedVehicle[playerid][v];

		if(vid <= 0) continue;
		if(!IsValidVehicle(vid)) continue;//if(nCarModel[playerid] < 400) continue;
		if(VehInfo[vid][cVirt] != 0) continue;
		//if(!IsInHardTruck(vid)) continue;
		new modelid = VehInfo[vid][cModel];//GetVehicleModel(carid)
		if(VehicleArray[modelid-400][Category] != Trailers) continue;
		//if(!IsTrailerAttachedToVehicle(vid)) continue;//пропускаем без прицепов
		//if(IsTrailerAttach[vid]) continue;//пропускаем уже прицепленные
		GetVehicleModelInfo(modelid, VEHICLE_MODEL_INFO_SIZE, vX, vY, vZ);
		if(GetDistanceToCar(playerid, vid) < (10.0+vY/2.0))
		{
			trailerid = vid;
			GetVehiclePos(vid, trX,trY,trZ);
			GetVehicleZAngle(vid, trA);
			SetPlayerPosEx(playerid, trX,trY,(trZ+vZ/2.0), trA);
//format(strings, sizeof(strings), "trailerid: %d", trailerid);//, PlayerName(playerid)
//SendClientMessage(playerid, -1, strings);
           	//SetPVarInt(playerid, "VehicleID", trailerid);
			break;
		}
	}
	if(!trailerid)
	{   //чтобы не мог пассажир отсоеденить прицеп
		format(strings, sizeof(strings), "  Нет прицепов в радиусе %.2f[%.2f] м!!", (vY), vZ);
		SendClientMessage(playerid, COLOR_GREY, strings);
	}
	return 1;
}



stock trucker_OnPlayerKeyState_LEFT(playerid)
{
//if(PRESSED(KEY_ANALOG_LEFT))//нажал
//~k~~VEHICLE_TURRETDOWN~ //num2 	//прицепить/отцепить
//для угона прицепов на ходу
	if(IsPlayerInAnyVehicle(playerid)) return 1;
 //если вы НА тачке
 	new SurfingVehicleID = GetPlayerSurfingVehicleID(playerid);//возвращает INVALID_VEHICLE_ID если в тачке нету водителя
	if(SurfingVehicleID == INVALID_VEHICLE_ID) return 1;
	//PLAYER_STATE_SURFING
	//GetPlayerSurfingVehicleID

//format(strings, sizeof(strings), "SurfingVehicleID: %d", SurfingVehicleID);//, PlayerName(playerid)
//SendClientMessage(playerid, -1, strings);
	
	if(gRobCountdown[playerid] != -1 && gRobCountdown[playerid] != 0)
	{
	    SendClientMessage(playerid, COLOR_GREY, "   Дождитесь окончания !");
	    return 1;
	}
	//if(!IsInHardTruck(nCarID[playerid]))
	//new SurfingVehicleID = GetPVarInt(playerid, "VehicleID");
	//new modelid = VehInfo[SurfingVehicleID][cModel];
	//if(VehicleArray[modelid-400][Category] != Trailers)
	if(!IsInHardTruck(SurfingVehicleID))
	{
		SendClientMessage(playerid, COLOR_GREY, "   Данное транспортное средство не оборудовано прицепным устройством !");
		//DeletePVar(playerid, "VehicleID");
		return 1;
	}
	/*if(GetDistanceToCar(playerid, SurfingVehicleID) >= (16.0))
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы слишком далеко от прицепного устройства !");
		//DeletePVar(playerid, "VehicleID");
		return 1;
	}*/
	if(!IsTrailerAttachedToVehicle(SurfingVehicleID)) { return 1; }
	if(gLoading[LastDriver[SurfingVehicleID]]) { return 1; }//не выводить если загружается
	if(gUnLoading[LastDriver[SurfingVehicleID]]) { return 1; }//не выводить если разгружается
	KillTimer(gRobCountdown[playerid]); gRobCountdown[playerid] = -1;
	gRobCountdown[playerid] = SetTimerEx("RobCountdown", 1000, 1, "id", playerid, SurfingVehicleID);
	//SetPlayerAttachedObject(playerid, BAG_SLOT, 18644, Right_hand, 0.085414,0.031325,0.012795, 0.000000,170.505798,0.182891, 1.001180,1.003389,1.062038 );
	//ApplyAnimation(playerid, "SILENCED", "Silence_reload", 6.0, 1, 0, 0, 0, 0, 1);
	//ApplyAnimation(playerid, "SILENCED", "Silence_reload", 6.0,1,0,0,1,60000);//фризим на 60 секунд
	//ApplyAnimation(playerid, "SILENCED", "CrouchReload", 4.1, 0, 1, 1, 1, 1, 1);
	//ApplyAnimation(playerid, "SILENCED", "CrouchReload", 4.0, 1, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BOMBER", "BOM_Plant_Loop", 4.0, 1, 0, 0, 0, 0);
	//ClearAnimations(playerid, 1);

	WantedPoints[playerid] += 3;
	new strtmp[64];
	format(strtmp, sizeof(strtmp), " Угон транспортного средства [%d]", GetVehicleTrailer(SurfingVehicleID));//nCarID[playerid]
	SetPlayerCriminal(DoT, playerid, LastDriver[SurfingVehicleID], strtmp);
	SendTeamMessage(DoT, COLOR_DARKTURQUOISE, "   USE: /pdd [19] [1-2] [playerid/PartOfName]");
	SendTeamMessage(DoT, COLOR_DARKTURQUOISE, "   У вас есть 60 секунд, чтобы остановить нарушителя!");
	return 1;
}

stock trucker_OnTrailerAttachedToVeh(playerid, trailerid)
{
	if( VehInfo[trailerid][cOwned] > 0 &&
		VehInfo[trailerid][cOwned] != PlayerInfo[playerid][pSQLID] &&
		PlayerInfo[playerid][pJob] == TRUCKER)
 	{
		DetachTrailerFromVehicleEx(nCarID[playerid]);//отсоединили прицеп
	    SendClientMessageEx(playerid, COLOR_GREY, "   Вы не владелец данного Прицепа !");
		nTrailerID[playerid] = 0;
		nTrailerModel[playerid] = 0;
		DisablePlayerCheckpointEx(playerid);//CP[playerid] = 0;
		return 1;
	}
	//if(Cargo[trailerid][tPeriod] > 0 && VehInfo[trailerid][cLoad] > 0 )
	if(PlayerInfo[playerid][pCarTime] > 0 && VehInfo[trailerid][cLoad] > 0 )
	{
		gTextDrawShowCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
		CP[playerid] = CP_TRUCKER;
		new rout;
		if(Cargo[trailerid][tWhere] < 100)
		{
			rout = Cargo[trailerid][tWhere];
			SetPlayerCheckpointEx(playerid,
				BizInfo[rout][bEntranceX],
				BizInfo[rout][bEntranceY],
				BizInfo[rout][bEntranceZ],
				CHECKPOINT_SIZE*2);
			/*SetPlayerRouting(playerid,
				BizInfo[rout][bEntranceX],
				BizInfo[rout][bEntranceY],
				BizInfo[rout][bEntranceZ]);*/
		}
		else {
			rout = Cargo[trailerid][tWhere]-100;
			SetPlayerCheckpointEx(playerid,
				SBizInfo[rout][sbEntranceX],
				SBizInfo[rout][sbEntranceY],
				SBizInfo[rout][sbEntranceZ],
				CHECKPOINT_SIZE*2);
			/*SetPlayerRouting(playerid,
				SBizInfo[rout][sbEntranceX],
				SBizInfo[rout][sbEntranceY],
				SBizInfo[rout][sbEntranceZ]);*/
		}
		checktimedeliver[playerid] = GetTickCount();
	    format(strings, sizeof(strings), "При доставке быстрее чем за %d секунд у вас обнулится скилл.", MinTimeCheckpoint[playerid]/1000);
	    SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	}
	return 1;
}



//stock TraficList(playerid) // /trafic
stock trucker_OnPlayerCommandText(playerid)
{//создаёт список биржу грузов согласно вашего грузовика
	new strcmd[MAX_STRING];
	if(	PlayerInfo[playerid][pJob] != TRUCKER)
	{
           SendClientMessage(playerid, COLOR_GREY, "   Вы не Дальнобойщик !");
           return 1;
	}
	SendClientMessage(playerid, COLOR_BLUEGREEN, "   Металл - основа для производства товаров {FFFFFF}индустрии развлечений!");
	SendClientMessage(playerid, COLOR_BLUEGREEN, "   Необходим грузовик 455 или прицеп 591 для перевозки сырья {FFFFFF}индустрии развлечений!");
	SendClientMessage(playerid, COLOR_BLUEGREEN, "   Поставка Металла осуществляется со склада по бизам(компаниям) и товаров из бизов(компаний) на склад!");

	SendClientMessage(playerid, COLOR_BLUEGREEN, "   Текстиль - основа для производства товаров {FFFFFF}розничной торговли!");
	SendClientMessage(playerid, COLOR_BLUEGREEN, "   Необходим грузовик 456 или прицеп 435 для перевозки сырья {FFFFFF}розничной торговли!");
	SendClientMessage(playerid, COLOR_BLUEGREEN, "   Поставка Текстиля осуществляется со склада по бизам(компаниям) и товаров из бизов(компаний) на склад!");

	SendClientMessage(playerid, COLOR_BLUEGREEN, "   Продовольствие - основа для производства товаров {FFFFFF}ресторанного бизнеса!");
	SendClientMessage(playerid, COLOR_BLUEGREEN, "   Необходим грузовик 423,588 или прицепы 606,607 c тягачом 485 для перевозки сырья {FFFFFF}ресторанного бизнеса!");
	SendClientMessage(playerid, COLOR_BLUEGREEN, "   Поставка Продовольствия осуществляется со склада по бизам(компаниям) и товаров из бизов(компаний) на склад!");

	SendClientMessage(playerid, COLOR_BLUEGREEN, "   Древесины - основа для производства товаров {FFFFFF}сферы услуг!");
	SendClientMessage(playerid, COLOR_BLUEGREEN, "   Необходим грузовик 478 или прицеп 450 для перевозки сырья {FFFFFF}сферы услуг!");
	SendClientMessage(playerid, COLOR_BLUEGREEN, "   Поставка Древесины осуществляется со склада по бизам(компаниям) и товаров из бизов(компаний) на склад!");

	SendClientMessage(playerid, COLOR_BLUEGREEN, "   Нефть - основа для производства товара {FFFFFF}промышленной сферы!");
	SendClientMessage(playerid, COLOR_BLUEGREEN, "   Необходим грузовик 524 или прицеп 584 для перевозки сырья {FFFFFF}промышленной сферы!");
	SendClientMessage(playerid, COLOR_BLUEGREEN, "   Поставка Нефти осуществляется из НефтеДобывающей Компании в НефтеПерерабатывающую Компанию!");
	SendClientMessage(playerid, COLOR_BLUEGREEN, "   Вы можете поставлять бензин из НефтеПерерабатывающей Компании на АЗС!");

	SendClientMessage(playerid, COLOR_BLUEGREEN, "   Товар - основа для экспорта любой сферы!");
	SendClientMessage(playerid, COLOR_BLUEGREEN, "   Необходим грузовик категории Station_Wagons(Фургон) для перевозки товаров!");
	SendClientMessage(playerid, COLOR_BLUEGREEN, "   Поставка на экспорт осуществляется со склада в порт!");

   	if(!IsPlayerInAnyVehicle(playerid))
	{
		SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться в транспортном средстве!");
		return 1;
	}
	if(CurState[playerid] != PLAYER_STATE_DRIVER)
	{
		SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться за рулём транспортного средства!");
		return 1;
	}
	if(//!IsInHardTruck(nCarID[playerid]) && !IsInTruck(nCarID[playerid])
		VehicleArray[nCarModel[playerid]-400][Category] != Station_Wagons &&
		VehicleArray[nCarModel[playerid]-400][Category] != Industrial &&
		VehicleArray[nCarModel[playerid]-400][Category] != Lorries)
	{
           SendClientMessage(playerid, COLOR_GREY, "   Вы не в грузовике !");
           return 1;
	}
	if( IsInHardTruck(nCarID[playerid]) &&
		(!IsTrailerAttachedToVehicle(nCarID[playerid]) || nTrailerID[playerid] == 0)
	  )
	{   //если Вы сели в грузовик
		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы - не прикрепили полуприцеп к тягачу !");
	    return 1;
	}
	new trailerid, trailermodel;
	if(IsTrailerAttachedToVehicle(nCarID[playerid])) { trailerid = nTrailerID[playerid]; trailermodel = nTrailerModel[playerid]; }
	else { trailerid = nCarID[playerid]; trailermodel = nCarModel[playerid]; }
	
	new bigmsgitem[2400];//2400
//ИНФОРМИРОВАНИЕ
//new strtmp[MAX_STRING];
//format(strtmp, sizeof(strtmp), "nCarModel: %d, trailerid: %d, TrailerModel: %d", nCarModel[playerid], nTrailerID[playerid], nTrailerModel[playerid]);
//ABroadCast(COLOR_MAROON, strcmd, 10);
//SendClientMessageToAll(COLOR_YELLOW, strtmp);


//1. ПОСТАВКА СЫРЬЯ ИЗ ПОРТА НА СКЛАД
//2. ПОСТАВКА ТОВАРОВ СО СКЛАДА В ПОРТ. Цена продажи Складом увеличивается в 3 раза. Цена покупки Портом сразу выставляется 100%
//3. ПОСТАВКА СЫРЬЯ СО СКЛАДА ПО БИЗАМ
//5. ПОСТАВКА СЫРЬЯ ИЗ КОМПАНИЙ НА СКЛАД
//4. ПОСТАВКА ТОВАРОВ ИЗ БИЗОВ НА СКЛАД
//6. ПОСТАВКА НЕФТИ ИЗ КОМПАНИЙ НА СКЛАД

//первая строка заголовок
	//strins(bigmsgitem, "{0080FF}Груз \tПремия \tВ кассе \tПокупаем \tПродадим \tНа складе \tОткуда \tКуда{A8C3E3}\n", strlen(bigmsgitem));
	strins(bigmsgitem, "Груз(На складе)\tОткуда->Куда{FFFFFF}\tРасстояние-Время\t{33AA33}Доход($/м)\n", strlen(bigmsgitem));
	new Branch = GetCargoType(nCarID[playerid], nTrailerID[playerid]);//определяем с какой отраслью работает наш грузовик или прицеп
	//----------------------------------------------------------------------
	//расчёт ведём исходя из полной загрузки
//ПОРТ --> СКЛАД
    new b = 81;
	new Float: distance = GetDistanceBizToPoint(b,
		BizInfo[BizList[b][cWhere]][bEntranceX],
		BizInfo[BizList[b][cWhere]][bEntranceY],
		BizInfo[BizList[b][cWhere]][bEntranceZ]);//км
	new speed = VehicleArray[nCarModel[playerid]-400][LineSpeed];//средняя скорость /2  км/ч
	//3.0 - коэф на криволинейность пути
	new Float: K_mediumspeed = 3.0;//коэф.  криволинейности пути
	new period = floatround(K_mediumspeed*Cargo[trailerid][tDistance]/(speed*1000)*3600);//м / (K * S км/ч * 1000) = часы * 3600 = секундах
	//new period = floatround( 3*3600*distance/(speed*1000) );//км / км/ч * секунды
	
	//new bonus = floatround(10*period*BizList[b][cFrailty]/100.0);
	new biz = BizList[b][cWhere];//куда
	new Float: bPrice = compcost*(100+BizInfo[b][bSellProd])/100.0;//цена покупки сырья у порта //15*(100+10)/100=16,5
	new Float: sPrice = compcost*(100+BizInfo[biz][bBuyProd])/100.0;//цена продажи сырья складу //15*(100+15)/100=17,25
	//new bonus = floatround((sPrice-bPrice)*BizInfo[b][bProducts]);
	
	new maxload = VehicleArray[trailermodel-400][Weight]/2; //{413,	"Pony",	Station_Wagons,	 = 2600/2=1300
	new Float: bonus = (sPrice-bPrice)*maxload;//полученная прибыль с продажи полной загрузки = (17,25-16,5)*1300=975$
	new Float: bonus_per_dist = bonus/distance;//прибыль на 1 м пути 975$/3000м=0,32 $/м
	
	format(strcmd, sizeof(strcmd), "%s(%d кг) \t%s[%d]->%s[%d]{FFFFFF}\t%.fм-%dsec{33AA33}\t%.1f $(%.2f $/м)\n",
									TypeCargo(Branch),//Груз
									GetProducts(b),// \tНа складе //, Branch
									BizInfo[b][bDiscription], b,//\tОткуда
									BizInfo[biz][bDiscription], biz,//\t\t\tКуда
									distance, period,
									bonus,  //\tПремия
									bonus_per_dist);//BizInfo[biz][bTill],//\tВ кассе
									//BizInfo[b][bSellProd],//\tПокупаем
									//BizInfo[biz][bBuyProd]);// \tПродадим
	strins(bigmsgitem, strcmd, strlen(bigmsgitem));
	//------------------------------------------------------------------
//ГРУЗЫ СКЛАД --> БИЗ //СКЛАД --> ПОРТ
	//new best_price,
	new rand = -1;
	biz = 80;
	for(b = 1; b < MAX_BIZ; b++)
	{//пропускаем банк
		//if(BizInfo[b][bOwned] == 0) continue;
		if(b == biz) continue;//пропускаем самого себя
		if(BizInfo[b][bBranch] != Branch) continue;//если ваша тачка относится к сфере бизнеса  && Branch != None
		//if(BizInfo[b][bLock] == 1) continue;//пропускаем закрытые
		if(BizInfo[b][bProducts] < 100) continue;//пропускаем с кол-вом товаров менее 500
		if(BizInfo[biz][bSellProd] <= BizInfo[b][bBuyProd]) continue;//пропускаем невыгодные
		new SellPrice = floatround( 100 * compcost*(100+BizInfo[b][bBuyProd])/100.0 );
		if(BizInfo[b][bTill] <= SellPrice) continue;//пропускаем с кассой которая не может оплатить 100 продов
		rand = b;
	}
	if(rand == -1)
	{
		SendClientMessage(playerid, COLOR_GREEN, "СКЛАД: {0080FF}Нет бизнесов этой сферы способных купить хотя бы 100 ед. сырья !");
		SendClientMessage(playerid, COLOR_GREY, "   Пожалуйста смените транспорт или прицеп !");
	}
	else
	{
		//strmid(caption, "ГРУЗЫ СО СКЛАДА", 0, strlen("ГРУЗЫ СО СКЛАДА"), 16);
//printf("rand: %d", rand);
	    b = rand;
		distance = GetDistanceBizToPoint(b,
			BizInfo[biz][bEntranceX],
			BizInfo[biz][bEntranceY],
			BizInfo[biz][bEntranceZ]);//км
		speed = VehicleArray[nCarModel[playerid]-400][LineSpeed];//средняя скорость /2  км/ч
		period = floatround(K_mediumspeed*Cargo[trailerid][tDistance]/(speed*1000)*3600);//м / (K * S км/ч * 1000) = часы * 3600 = секундах
		//bonus = floatround(10*period*BizList[biz][cFrailty]/100.0);
		bPrice = compcost*(100+BizInfo[b][bSellProd])/100.0;//15*(100+20*3)/100 = 2400
		sPrice = compcost*(100+BizInfo[biz][bBuyProd])/100.0;//15*(100+50)/100 = 2250
		bonus = (sPrice-bPrice)*maxload;
		bonus_per_dist = bonus/distance;

		format(strcmd, sizeof(strcmd), "%s(%d кг) \t%s[%d]->%s[%d]{FFFFFF}\t%.fм-%dsec{33AA33}\t%.1f $(%.2f $/м)\n",
									TypeCargo(Branch),//Груз
									GetProducts(b),// \tНа складе //, Branch
									BizInfo[b][bDiscription], b,//\tОткуда
									BizInfo[biz][bDiscription], biz,//\t\t\tКуда
									distance, period,
									bonus,  //\tПремия
									bonus_per_dist);//BizInfo[biz][bTill],//\tВ кассе
									//BizInfo[b][bSellProd],//\tПокупаем
									//BizInfo[biz][bBuyProd]);// \tПродадим
		strins(bigmsgitem, strcmd, strlen(bigmsgitem));
//printf("strcmd: %s", strcmd);
	}
	//------------------------------------------------------------------
//ГРУЗЫ ИЗ БИЗОВ --> СКЛАД
	for(b = 1; b < MAX_BIZ-2; b++)
	{
		//if(BizInfo[b][bOwned] == 0) continue;//пропускаем не купленные
		if(BizInfo[b][bBranch] != Branch) continue;//пропускаем которые не относятся к нашем прицепу
		//if(BizInfo[b][bLock] == 1) continue;//с закрытых можно вывозить и НУЖНО!
		if(BizInfo[b][bProducts] < 100) continue;//пропускаем с кол-вом товаров менее 500

		distance = GetDistanceBizToPoint(b,
			BizInfo[BizList[b][cWhere]][bEntranceX],
			BizInfo[BizList[b][cWhere]][bEntranceY],
			BizInfo[BizList[b][cWhere]][bEntranceZ]);//км
		speed = VehicleArray[nCarModel[playerid]-400][LineSpeed];//средняя скорость /2  км/ч
		//3.0 - коэф на криволинейность пути
		//period = floatround( 3*3600*distance/(speed*1000) );//км / км/ч * секунды
		period = floatround(K_mediumspeed*Cargo[trailerid][tDistance]/(speed*1000)*3600);
		//bonus = floatround(10*period*BizList[b][cFrailty]/100.0);
		biz = BizList[b][cWhere];
		//new Float: BuyPrice = compcost*(100+BizInfo[b][bSellProd])/100.0;//15*(100+50)/100 = 2250
		//new Float: SellPrice = compcost*(100+BizInfo[biz][bBuyProd]*3)/100.0;//15*(100+20*3)/100 = 2400
		bPrice = compcost*(100+BizInfo[b][bSellProd])/100.0;//15*(100+20*3)/100 = 2400
		sPrice = compcost*(100+BizInfo[biz][bBuyProd])/100.0;//15*(100+50)/100 = 2250
		//bonus = floatround((SellPrice-BuyPrice)*BizInfo[b][bProducts]);
		bonus = (sPrice-bPrice)*maxload;
		bonus_per_dist = bonus/distance;
		format(strcmd, sizeof(strcmd), "%s(%d кг) \t%s[%d]->%s[%d]{FFFFFF}\t%.fм-%dsec{33AA33}\t%.1f $(%.2f $/м)\n",
									TypeCargo(Branch),//Груз
									GetProducts(b),// \tНа складе //, Branch

									BizInfo[b][bDiscription], b,//\tОткуда
									BizInfo[biz][bDiscription], biz,//\t\t\tКуда
									distance, period,
									bonus,  //\tПремия
									bonus_per_dist);//BizInfo[biz][bTill],//\tВ кассе
									//BizInfo[b][bSellProd],//\tПокупаем
									//BizInfo[biz][bBuyProd]);// \tПродадим
		strins(bigmsgitem, strcmd, strlen(bigmsgitem));
	}
	if(strlen(bigmsgitem) >= sizeof(bigmsgitem))
	{
		//ИНФОРМИРОВАНИЕ
		format(strcmd, sizeof(strcmd), "Error34: TRAFIC 3 STATS - %s[%d], strlen(bigmsgitem): %d, sizeof(bigmsgitem): %d", PlayerName(playerid), playerid, strlen(bigmsgitem), sizeof(bigmsgitem));
		Log(ERROR, strcmd);
		return 1;
	}
	if(strlen(bigmsgitem) <= 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   TRAFIC STATS пуст");
		return 1;
	}
	new caption[54 +24+3 +20+24 + 5+5];
	format(caption, sizeof(caption), "Грузовик: %s[%d] Тип груза: %s[%s] Загружен: %d/%d",
			VehicleArray[nCarModel[playerid]-400][Vehicle_Name], nCarModel[playerid],
			TypeCargo( GetCargoType(nCarID[playerid], nTrailerID[playerid]) ),
			TypeBranch( GetCargoType(nCarID[playerid], nTrailerID[playerid]) ),
			VehInfo[trailerid][cLoad], maxload);
	//new caption[] = "Список доступных заданий";

	//ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, caption, bigmsgitem, "OK", "");
	ShowPlayerDialogEx(playerid, TRAFIC_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, caption, bigmsgitem, "OK", "Cancel");
	return 1;
}


//------------------------------------------------------------------------------

stock SetPlayerRouting(playerid, Float:x1, Float:y1, Float:z1)//получить угол направления на точку
{   //вызывается из OnPlayerCallTime(playerid)//запускается каждую секунду из OneSecondTimers
	if(GPS_OnOff[playerid] == 0) return 1;
	if(PlayerInfo[playerid][pInt] != 0) return 1;
	if(PlayerInfo[playerid][pVirtual] != 0) return 1;
	new Float:x2, Float:y2, Float:z2;
    new Float:angle2;//угол под которым мы смотрим
	if(IsPlayerInAnyVehicle(playerid))
	{
		GetVehiclePos(nCarID[playerid], x2, y2, z2);
	   	GetVehicleZAngle(nCarID[playerid], angle2);
	}
	else
	{
		GetPlayerPos(playerid, x2, y2, z2);
		GetPlayerFacingAngle(playerid, angle2);
	}
 	new Float:dist;
	dist = floatsqroot(
						floatpower(floatsub(x1,x2),2)+
						floatpower(floatsub(y1,y2),2)+
						floatpower(floatsub(z1,z2),2)
					  );
	new Float: angle1;//вектор направления на точку
	if( (y1-y2) >= 0.0) angle1 = acos((x1-x2)/dist) - 90.0;
	else angle1 = 270.0 - acos((x1-x2)/dist);

//разница между углами куда мы смотрим и вектором направления на точку
	new Float: offset = 360.0 - angle2 + angle1;//fi
	if(offset > 360.0) offset = offset - 360.0;
	else if(offset < 0.0) offset = offset + 360.0;

	new strtmp[32];//20+4
	if(IsPlayerInAnyVehicle(playerid))
	{
		if(offset >= 30.0 && offset < 60.0) 	{ format(strtmp, sizeof(strtmp), "~<~ ~y~%d", floatround(dist)); }
		else if(offset >= 60.0 && offset < 100.0) 	{ format(strtmp, sizeof(strtmp), "~<~~<~ ~y~%d", floatround(dist)); }
		else if(offset >= 100.0 && offset < 150.0) 	{ format(strtmp, sizeof(strtmp), "~<~ ~y~%d~n~    ~d~", floatround(dist)); }
		else if(offset >= 150.0 && offset < 210.0) 	{ format(strtmp, sizeof(strtmp), "   ~y~%d~n~~d~", floatround(dist)); }
		else if(offset >= 210.0 && offset < 260.0) 	{ format(strtmp, sizeof(strtmp), "    ~y~%d ~>~~n~~d~", floatround(dist)); }
		else if(offset >= 260.0 && offset < 300.0) 	{ format(strtmp, sizeof(strtmp), "~y~%d ~>~~>~", floatround(dist)); }
		else if(offset >= 300.0 && offset < 330.0) 	{ format(strtmp, sizeof(strtmp), "~y~%d ~>~", floatround(dist)); }
		else //if(offset >= 330.0 || offset < 30.0)
		{
			format(strtmp, sizeof(strtmp), "~u~~n~   ~y~%d", floatround(dist));
		}
	}
	else
	{
		if(offset >= 10.0 && offset < 30.0) 	{ format(strtmp, sizeof(strtmp), 	"    ~u~~n~~<~ ~y~%d", floatround(dist)); }
		else if(offset >= 30.0 && offset < 75.0) 	{ format(strtmp, sizeof(strtmp), "~<~ ~y~%d", floatround(dist)); }
		else if(offset >= 75.0 && offset < 105.0) 	{ format(strtmp, sizeof(strtmp), "~<~~<~ ~y~%d", floatround(dist)); }
		else if(offset >= 105.0 && offset < 165.0) 	{ format(strtmp, sizeof(strtmp), "~<~ ~y~%d~n~    ~d~", floatround(dist)); }
		else if(offset >= 165.0 && offset < 195.0) 	{ format(strtmp, sizeof(strtmp), "   ~y~%d~n~~d~", floatround(dist)); }
		else if(offset >= 195.0 && offset < 255.0) 	{ format(strtmp, sizeof(strtmp), "    ~y~%d ~>~~n~~d~", floatround(dist)); }
		else if(offset >= 255.0 && offset < 285.0) 	{ format(strtmp, sizeof(strtmp), "~y~%d ~>~~>~", floatround(dist)); }
		else if(offset >= 285.0 && offset < 330.0) 	{ format(strtmp, sizeof(strtmp), "~y~%d ~>~", floatround(dist)); }
		else if(offset >= 330.0 && offset < 350.0) 	{ format(strtmp, sizeof(strtmp), "~u~~n~    ~y~%d ~>~", floatround(dist)); }
		else //if(offset >= 350.0 || offset < 10.0)
		{
			format(strtmp, sizeof(strtmp), "~u~~n~   ~y~%d", floatround(dist));
		}
	}
//для метки на радаре
	/*new Float: v[3];
	new Float: angle3;// = 180.0 - offset;
	if(offset > 180.0) angle3 = 360.0 - offset + 180.0;
	else if(offset <= 180.0) angle3 = 180.0 - offset;

  	GetXYInring(83.5,403.0, 40, v[0], v[1], angle3);//alpha);//83.5,403.0 координаты центра окружности
	PlayerTextDrawHide(playerid, txdSpeedMark[playerid]);
	PlayerTextDrawDestroy(playerid, txdSpeedMark[playerid]);
	PLAYER_TEXT_DRAWS_COUNTER[playerid] --;

	txdSpeedMark[playerid] = CreatePlayerTextDraw(playerid, v[0], v[1], "~r~.");
	PlayerTextDrawLetterSize(playerid, txdSpeedMark[playerid], 1.0, -3.0);//0.73, -2.60
	PlayerTextDrawSetOutline(playerid, txdSpeedMark[playerid], 1);
	PlayerTextDrawShow(playerid, txdSpeedMark[playerid]);
	PLAYER_TEXT_DRAWS_COUNTER[playerid] ++;*/

	GameTextForPlayerEx(playerid, strtmp, 3500, 4);//3500
	PurposePoint[playerid][tX] = x1;
	PurposePoint[playerid][tY] = y1;
	PurposePoint[playerid][tZ] = z1;
	//return floatround(offset);
	return 1;
}



/*stock OnPlayerKeyChangeInterior(playerid, newkeys, oldkeys)
{   //ни где не вызывается
	if(	IsPlayerInRangeOfPoint(playerid, 10.0, -14.5400,-270.5720,5.4297) &&
		GetPlayerInterior(playerid) == 0 && GetPlayerVirtualWorld(playerid) == 0)
	{
		new carid = GetPlayerVehicleID(playerid);
		new modelveh = GetVehicleModel(carid);
		if(modelveh == 403 || modelveh == 514 || modelveh == 515)
		{
			SetPlayerInteriorEx(playerid, 1);
			SetPlayerVirtualWorldEx(playerid, 80);
			LinkVehicleToInteriorEx(carid, 1);
			SetVehicleVirtualWorldEx(carid, 80);
			SetVehiclePosEx(carid, 1406.3802,-35.5015,1001.5160);
			SetVehicleZAngleEx(carid, 90.4622);

			new trailer = GetVehicleTrailer(carid);
			new modeltrailer = GetVehicleModel(trailer);
			DestroyVehicle(trailer);
			new tveh = CreateVehicle(modeltrailer, 1415.941,-35.423,1001.495, 90.4622, 1, 1, -1);
		   	gVehicleSpawn[tveh] = 1;
			SetVehicleVirtualWorld(trailer, 80);
			LinkVehicleToInteriorEx(trailer, 1);
			AttachTrailerToVehicleEx(trailer,carid);
		}
	}
	if(	IsPlayerInRangeOfPoint(playerid, 10.0, 1418.5487,-45.7592,1000.9281) &&
		GetPlayerInterior(playerid) == 1 && GetPlayerVirtualWorld(playerid) == 80)
	{
		new carid = GetPlayerVehicleID(playerid);
		new modelveh = GetVehicleModel(carid);
		if(modelveh == 403 || modelveh == 514 || modelveh == 515)
		{
			SetPlayerInteriorEx(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			LinkVehicleToInterior(carid, 0);
			SetVehicleVirtualWorld(carid, 0);
			SetVehiclePos(carid, -23.1215,-283.4583,6.0058);
			SetVehicleZAngle(carid, 180.2265);
			new trailer = GetVehicleTrailer(carid);
			new modeltrailer = GetVehicleModel(trailer);
			DestroyVehicle(trailer);
			new tveh = CreateVehicle(modeltrailer, -23.207,-273.771,5.997, 180.2265, 1, 1, -1);
			gVehicleSpawn[tveh] = 1;
			SetVehicleVirtualWorld(trailer, 0);
			LinkVehicleToInterior(trailer, 0);
			AttachTrailerToVehicle(trailer,carid);
		}
	}
}*/

//для дальнобойщиков конец

stock GetDiscription(bizid)
{
	new discription[10+20];
	if(bizid >= 100) strcat(discription, SBizInfo[bizid-100][sbDiscription]);
	else strcat(discription, BizInfo[bizid][bDiscription]);
	return discription;
}

stock TruckerCargoInit(playerid)
{
	PlayerInfo[playerid][pCarTime] = 0;//обнуляем время
	CurrentTruckHealth[LastCar[playerid]] = 0.0;//состояние машины
	StartTruckHealth[LastCar[playerid]] = 1000.0;//состояние машины

	gTextDrawHideCarTime[playerid] = true; OnPlayerTextDrawStateChange(playerid);
	GPS_OnOff[playerid] = 0; DisablePlayerCheckpointEx(playerid);//CP[playerid] = 0;
	//SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Маркер Задания убран !");

	//if(!IsPlayerInAnyVehicle(playerid)) { return 1; }
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) { return 1; }
	//if(IsInHardTruck(nCarID[playerid]))
	if( VehicleArray[nCarModel[playerid]-400][Category] != Station_Wagons &&
		VehicleArray[nCarModel[playerid]-400][Category] != Industrial &&
		VehicleArray[nCarModel[playerid]-400][Category] != Lorries) { return 1; }

	new trailerid;//, trailermodel;
	if(IsTrailerAttachedToVehicle(nCarID[playerid])) { trailerid = nTrailerID[playerid]; /*trailermodel = nTrailerModel[playerid];*/ }
	else { trailerid = nCarID[playerid]; /*trailermodel = nCarModel[playerid];*/ }
	ClearCargo(trailerid);
	return 1;
}

stock ClearCargo(trailerid)
{
	if(VehInfo[trailerid][cLoad] <= 0)
	{
		VehInfo[trailerid][cLoad] = 0;
		VehInfo[trailerid][cLoadType] = 0;
		VehInfo[trailerid][cWhere] = 0;
	}

	Cargo[trailerid][CargoType] = 0;
	Cargo[trailerid][tWhence] = -1;
	Cargo[trailerid][tWhere] = -1;
	Cargo[trailerid][tWeight] = 0;
	Cargo[trailerid][tFrailty] = 0;
	Cargo[trailerid][tPeriod] = 0;
	Cargo[trailerid][tBuyPrice] = 0.0;
	Cargo[trailerid][tSellPrice] = 0.0;
	Cargo[trailerid][tBonus] = 0.0;
	Cargo[trailerid][tDistance] = 0.0;
}


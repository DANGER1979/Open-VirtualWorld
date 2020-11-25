/*
 *            vw_vehmenu v1.0
 *       (c) Copyright 2008-2024 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (danger1979@mail.ru)
 * @date      : 1.01.2009
 * @update    : 13.11.2018
 *
 * This file is provided as is (no warranties).
 * панель управления капотом, багажником, светом, мигалкой, дверями
 * вызывается через нажатие в тачке 2
 */

//This will work on vehicles that have a siren like vehicles that are created with sirens.(0.3.7 RC4)
//Это будет работать на транспортных средствах, которые имеют сирену, как транспортные средства, которые создаются с сиренами.(0.3.7 RC4)
//native SetVehicleParamsSirenState(vehicleid, state);

//#include <a_samp>

//#include "../include/car/fix_doors.inc"
//=============================================================================

stock vehmenu_OnPlayerKeyStateChange(playerid)//CarHelp(playerid);
//stock VehicleMenu(playerid)
{
	new listitems[1053+1+28+29], engine, lights, alarm, doors, bonnet, boot, objective;
	new carid = GetPlayerVehicleID(playerid);
	//new carid = nCarID[playerid];
	//new modelid = nCarModel[playerid];

	GetVehicleParams(carid, engine, lights, alarm, doors, bonnet, boot, objective);
	engine = CarStatus[carid][st_engine];
	lights = CarStatus[carid][st_lights];
	alarm = CarStatus[carid][st_alarm];
	doors = CarStatus[carid][st_doors];
	bonnet = CarStatus[carid][st_bonnet];
	boot = CarStatus[carid][st_boot];
	objective = CarStatus[carid][st_objective];
	//if (engine == VEHICLE_PARAMS_ON && VehicleArray[modelid-400][Category] == Airplane) return 1;

//format(strings, sizeof(strings), "carid: %d. engine: %d lights: %d alarm: %d doors: %d bonnet: %d boot: %d objective: %d", carid, engine, lights, alarm, doors, bonnet, boot, objective);
//SendClientMessage(playerid, COLOR_GREY, strings);
	strcat(listitems, " \tСостояние\tКлавиша\n");

	strcat(listitems, "{00FF00}Поставить на колёса\n");
	//strcat(listitems, "{00FF00}Админка по тачке\n");
	
	//if(engine == VEHICLE_PARAMS_ON) strcat(listitems, "{FF0000}Заглушить двигатель\n");
	//else strcat(listitems, "{00FF00}Завести двигатель\n");
	if(engine == VEHICLE_PARAMS_ON) strcat(listitems, " - Двигатель \t{FF0000}Заведен\tCtrl+Space\n");
	else strcat(listitems, " - Двигатель \t{00FF00}Заглушен\tCtrl+Space\n");

	if(lights == VEHICLE_PARAMS_ON) strcat(listitems, " - Фары \t{FF0000}Включены\n");
	else strcat(listitems, " - Фары \t{00FF00}Выключены\n");
	
	if(alarm == VEHICLE_PARAMS_ON) strcat(listitems, " - Сигнализация \t{FF0000}Включена\n");
	else strcat(listitems, " - Сигнализация \t{00FF00}Выключена\n");
	
	new siren = GetVehicleParamsSirenState(nCarID[playerid]);
	if(siren == 1) strcat(listitems, " - Сирена \t{FF0000}Установлена\n");
	else strcat(listitems, " - Сирена \t{00FF00}Отсутствует\n");

	//if(VehInfo[carid][cLock] == 1 || VehInfo[carid][cLock] == 11) strcat(listitems, "{FF0000}Открыть автомобиль\n");
	//else if(VehInfo[carid][cLock] == 0 || VehInfo[carid][cLock] == 10) strcat(listitems, "{00FF00}Закрыть автомобиль\n");
	if(doors == VEHICLE_PARAMS_ON) strcat(listitems, " - Двери \t{FF0000}Закрыты\tAlt+Space\n");
	else strcat(listitems, " - Двери \t{00FF00}Открыты\tAlt+Space\n");
	
	if(bonnet == VEHICLE_PARAMS_ON) strcat(listitems, " - Капот \t{FF0000}Открыт\n");
	else strcat(listitems, " - Капот \t{00FF00}Закрыт\n");
	
	if(boot == VEHICLE_PARAMS_ON) strcat(listitems, " - Багажник \t{FF0000}Открыт\n");
	else strcat(listitems, " - Багажник \t{00FF00}Закрыт\n"); 

	/*if(objective == VEHICLE_PARAMS_ON) strcat(listitems, "{FF0000}Убрать маркер\n");
	else strcat(listitems, "{00FF00}Установить маркер\n");*/
	if(objective == VEHICLE_PARAMS_ON) strcat(listitems, " - Маркер \t{FF0000}Установлен\n");
	else strcat(listitems, " - Маркер \t{00FF00}Убран\n");

	/*if(VehInfo[carid][cPark] == 1) strcat(listitems, "{FF0000}Распарковать автомобиль\n");
	else strcat(listitems, "{00FF00}Запарковать автомобиль\n");*/
	if(VehInfo[carid][cPark] == 1) strcat(listitems, " - Транспорт \t{FF0000}Запаркован\tShift+Space\n");
	else strcat(listitems, " - Транспорт \t{00FF00}НЕ запаркован\tShift+Space\n");
	
	if(CameraOnePerson[playerid] == true) strcat(listitems, " - Вид от первого лица \t{FF0000}Выключить\n");
	else strcat(listitems, " - Вид от первого лица \t{00FF00}Включить\n");

	strcat(listitems, "{B05EFF}~ {E6CCFF}Управление окнами\n");
	strcat(listitems, "{B05EFF}~ {E6CCFF}Управление дверьми\n");
	strcat(listitems, "{B05EFF}~ {E6CCFF}Радио\n");
	strcat(listitems, "{B05EFF}~ {E6CCFF}Заправить\n");
	strcat(listitems, "{B05EFF}~ {E6CCFF}Выбросить пассажиров\n");
	strcat(listitems, "{B05EFF}~ {E6CCFF}Посмотреть информацию о автомобиле\n");
	strcat(listitems, "{B05EFF}~ {E6CCFF}Сдать в аренду\n");
	strcat(listitems, "{B05EFF}~ {E6CCFF}Выставить на продажу\n");
	//strcat(listitems, "{00FF00}Переоформить авто на другого\n");

	strcat(listitems, "{B05EFF}~ {E6CCFF}Удалить тачку\n");
	strcat(listitems, "{B05EFF}~ {E6CCFF}Установить на спаун\n");
	strcat(listitems, "{B05EFF}~ {E6CCFF}Установить здоровье тачки\n");
	strcat(listitems, "{B05EFF}~ {E6CCFF}Установить тюнинг\n");
	strcat(listitems, "{B05EFF}~ {E6CCFF}Починить тачку\n");
	strcat(listitems, "{B05EFF}~ {E6CCFF}Телепорт тачки\n");
	strcat(listitems, "{B05EFF}~ {E6CCFF}Телепорт к тачке\n");
	ShowPlayerDialogGap(playerid, VEHICLE_DIALOG, DIALOG_STYLE_TABLIST_HEADERS,"{B5CCFF}AUTO MENU",listitems,"OK", "Exit");
}
stock WindowsControl(playerid)
{
	new listitems[44*4];
	new driver, passenger, backleft, backright;
	GetVehicleParamsCarWindows(nCarID[playerid], driver, passenger, backleft, backright);

	new driver_status[16];
	if(driver) driver_status = "\t| Закрыто\n";
	else driver_status = "\t| Открыто\n";

	new passenger_status[16];
	if(passenger) passenger_status = "\t| Закрыто\n";
	else passenger_status = "\t| Открыто\n";

	new modelid_line = nCarModel[playerid]-400;
	new seatnum = VehicleArray[modelid_line][SeatID];

	if(seatnum == 2)
	{
		strcat(listitems, "- Водительское:");
		strcat(listitems, driver_status);
		strcat(listitems, "- Переднее пассажирское:");
		strcat(listitems, passenger_status);
	}
	else if(seatnum == 4)
	{
		new backleft_status[16];
		if(backleft) backleft_status = "\t| Закрыто\n";
		else backleft_status = "\t| Открыто\n";

		new backright_status[16];
		if(backright) backright_status = "\t| Закрыто\n";
		else backright_status = "\t| Открыто\n";
	
		strcat(listitems, "- Водительское:");	strcat(listitems, driver_status);
		strcat(listitems, "- Переднее пассажирское:");	strcat(listitems, passenger_status);
		strcat(listitems, "- Заднее левое:");	strcat(listitems, backleft_status);
		strcat(listitems, "- Заднее правое:");	strcat(listitems, backright_status);
	}
	else
	{
		strcat(listitems, "- Водительское:");
		strcat(listitems, driver_status);
		strcat(listitems, "- Переднее пассажирское:");
		strcat(listitems, passenger_status);
	}
	ShowPlayerDialogGap(playerid, WINDOWS_DIALOG, DIALOG_STYLE_TABLIST, "Управление окнами", listitems, "OK", "Назад");
}

stock WINDOWS_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
//stock vehmenu_OnDialog(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if(dialogid != WINDOWS_DIALOG) return 1;
	if(!response)
	{
		PlaySoundForPlayer(playerid, 5202);
		return 1;
	}
	//new vehicleid = GetPlayerVehicleID(playerid);
	//if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, COLOR_RED, "Нельзя регулировать водительское окно, если вы не водитель!");

	new driver, passenger, backleft, backright;
	new vehicleid = nCarID[playerid];
	GetVehicleParamsCarWindows(vehicleid, driver, passenger, backleft, backright);
	new iSeat = GetPlayerVehicleSeat(playerid);
//new szString[14]; format(szString, sizeof(szString), "Ваше место: %i", iSeat); SendClientMessage(playerid, 0xFFFFFFFF, szString);
	if(iSeat == 0)
	{//если вы водитель
		if(listitem == 0)
		{//если вы выбрали водительскую дверь
			//if(iSeat != 0 && ) return SendClientMessage(playerid, COLOR_RED, "Нельзя регулировать водительское окно, если вы не водитель!");
			if(!driver) return SetVehicleParamsCarWindows(vehicleid, 1, passenger, backleft, backright) && SendClientMessage(playerid, -1, "Вы закрыли переднее левое окно");
			else if(driver) return SetVehicleParamsCarWindows(vehicleid, 0, passenger, backleft, backright) && SendClientMessage(playerid, -1, "Вы открыли переднее левое окно");
		}
		else if(listitem == 1)
		{
			if(!passenger) return SetVehicleParamsCarWindows(vehicleid, driver, 1, backleft, backright) && SendClientMessage(playerid, -1, "Вы закрыли переднее правое окно");
			else if(passenger) return SetVehicleParamsCarWindows(vehicleid, driver, 0, backleft, backright) && SendClientMessage(playerid, -1, "Вы открыли переднее правое окно");
		}
		else if(listitem == 2)
		{
			if(!backleft) return SetVehicleParamsCarWindows(vehicleid, driver, passenger, 1, backright) && SendClientMessage(playerid, -1, "Вы закрыли заднее левое окно");
			else if(backleft) return SetVehicleParamsCarWindows(vehicleid, driver, passenger, 0, backright) && SendClientMessage(playerid, -1, "Вы открыли заднее левое окно");
		}
		else if(listitem == 3)
		{
			if(!backright) return SetVehicleParamsCarWindows(vehicleid, driver, passenger, backleft, 1) && SendClientMessage(playerid, -1, "Вы закрыли заднее правое окно");
			else if(backright) return SetVehicleParamsCarWindows(vehicleid, driver, passenger, backleft, 0) && SendClientMessage(playerid, -1, "Вы открыли заднее правое окно");
		}
	}
	else if(iSeat == 1)
	{
		if(!passenger) return SetVehicleParamsCarWindows(vehicleid, driver, 1, backleft, backright) && SendClientMessage(playerid, -1, "Вы закрыли переднее правое окно");
		else if(passenger) return SetVehicleParamsCarWindows(vehicleid, driver, 0, backleft, backright) && SendClientMessage(playerid, -1, "Вы открыли переднее правоеокно");
	}
	else if(iSeat == 2)
	{
		if(!backleft) return SetVehicleParamsCarWindows(vehicleid, driver, passenger, 1, backright) && SendClientMessage(playerid, -1, "Вы закрыли заднее левое окно");
		else if(backleft) return SetVehicleParamsCarWindows(vehicleid, driver, passenger, 0, backright) && SendClientMessage(playerid, -1, "Вы открыли заднее левое окно");
	}
	else if(iSeat == 3)
	{
		if(!backright) return SetVehicleParamsCarWindows(vehicleid, driver, passenger, backleft, 1) && SendClientMessage(playerid, -1, "Вы закрыли заднее правое окно");
		else if(backright) return SetVehicleParamsCarWindows(vehicleid, driver, passenger, backleft, 0) && SendClientMessage(playerid, -1, "Вы открыли заднее правое окно");
	}
	new panels, doors, lights, tires;
	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, 15);
	return 1;
}


stock DoorsControl(playerid)
{
	new listitems[44*4];
	new driver, passenger, backleft, backright;
	new carid = GetPlayerVehicleID(playerid);
	GetVehicleParamsCarDoors(carid, driver, passenger, backleft, backright);

	new driver_status[16];
	if(driver == 0) driver_status = "\t| Закрыто\n";
	else driver_status = "\t| Открыто\n";

	new passenger_status[16];
	if(passenger == 0) passenger_status = "\t| Закрыто\n";
	else passenger_status = "\t| Открыто\n";

	new modelid_line = nCarModel[playerid]-400;
	new seatnum = VehicleArray[modelid_line][SeatID];

	if(seatnum == 2)
	{
		strcat(listitems, "- Передняя левая:");
		strcat(listitems, driver_status);
		strcat(listitems, "- Передняя правая:");
		strcat(listitems, passenger_status);
	}
	else if(seatnum == 4)
	{
		new backleft_status[16];
		if(backleft == 0) backleft_status = "\t| Закрыта\n";
		else backleft_status = "\t| Открыта\n";

		new backright_status[16];
		if(backright == 0) backright_status = "\t| Закрыта\n";
		else backright_status = "\t| Открыта\n";

		strcat(listitems, "- Передняя левая:");	strcat(listitems, driver_status);
		strcat(listitems, "- Передняя правая:");strcat(listitems, passenger_status);
		strcat(listitems, "- Задняя левая:");	strcat(listitems, backleft_status);
		strcat(listitems, "- Задняя правая:");	strcat(listitems, backright_status);
	}
	else
	{
		strcat(listitems, "- Передняя левая:");
		strcat(listitems, driver_status);
		strcat(listitems, "- Передняя правая:");
		strcat(listitems, passenger_status);
	}
	ShowPlayerDialogGap(playerid, DOORS_DIALOG, DIALOG_STYLE_TABLIST, "Управление дверьми", listitems, "OK", "Назад");
}
stock DOORS_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
//stock vehmenu_OnDialog(playerid, dialogid, response, listitem, inputtext[])
{
/*
Список ошибок дверей GetVehicleParamsCarDoors:
 Состояние дверей не будет обновляться, если я остановлюсь войти или выйти из автомобиля при открытии двери.
 Состояние дверей не будет обновляться, если двери автомобиля будут повреждены (игровым процессом или функцией UpdateVehicleDamageStatus).
 Состояние дверей будет установлено на -1 после входа или выхода из автомобиля.
 Состояние дверей не сохраняется после повторного подключения и для новых подключенных игроков (для состояния -1, но это логично).
 Данные GetVehicleParamsCarDoors не обновляются после SetVehicleParamsCarDoors, если кто-то находится в автомобиле.
 Функция UpdateVehicleDamageStatus визуально закрывает двери, если их состояние равно -1.
*/
	#pragma unused inputtext
	if(dialogid != DOORS_DIALOG) return 1;
	if(!response)
	{
		PlaySoundForPlayer(playerid, 5202);
		return 1;
	}
	new carid = GetPlayerVehicleID(playerid);// nCarID[playerid];

//new szString[14]; format(szString, sizeof(szString), "Ваше место: %i", iSeat); SendClientMessage(playerid, 0xFFFFFFFF, szString);
	new driver, passenger, backleft, backright;
	GetVehicleParamsCarDoors(carid, driver, passenger, backleft, backright);
	//new iSeat = GetPlayerVehicleSeat(playerid);
//new szString[65+3+3+4*1];
//format(szString, sizeof(szString), "carid:%d[%i], driver:%d, passenger:%d, backleft:%d, backright:%d", carid, iSeat,
//	driver, passenger, backleft, backright);
//SendClientMessage(playerid, 0xFFFFFFFF, szString);
	//if(iSeat == 0)
	//{//если вы водитель
	if(listitem == 0)
	{//если вы выбрали водительскую дверь
		//if(iSeat != 0 && ) return SendClientMessage(playerid, COLOR_RED, "Нельзя регулировать водительское окно, если вы не водитель!");
		if(driver == 1) return SetVehicleParamsCarDoors(carid, 0, passenger, backleft, backright) && SendClientMessage(playerid, -1, "Вы закрыли переднюю левую дверь");
		else return SetVehicleParamsCarDoors(carid, 1, passenger, backleft, backright) && SendClientMessage(playerid, -1, "Вы открыли переднюю левую дверь");
	}
	else if(listitem == 1)
	{
		if(passenger == 1) return SetVehicleParamsCarDoors(carid, driver, 1, backleft, backright) && SendClientMessage(playerid, -1, "Вы закрыли переднюю правую дверь");
		else return SetVehicleParamsCarDoors(carid, driver, 0, backleft, backright) && SendClientMessage(playerid, -1, "Вы открыли переднюю правую дверь");
	}
	else if(listitem == 2)
	{
		if(backleft == 1) return SetVehicleParamsCarDoors(carid, driver, passenger, 1, backright) && SendClientMessage(playerid, -1, "Вы закрыли заднюю левую дверь");
		else return SetVehicleParamsCarDoors(carid, driver, passenger, 0, backright) && SendClientMessage(playerid, -1, "Вы открыли заднюю левую дверь");
	}
	else if(listitem == 3)
	{
		if(backright == 1) return SetVehicleParamsCarDoors(carid, driver, passenger, backleft, 1) && SendClientMessage(playerid, -1, "Вы закрыли заднюю правую дверь");
		else return SetVehicleParamsCarDoors(carid, driver, passenger, backleft, 0) && SendClientMessage(playerid, -1, "Вы открыли заднюю правую дверь");
	}
	//}
	/*else if(iSeat == 1)
	{
		if(passenger == 1) return SetVehicleParamsCarDoors(carid, driver, 0, backleft, backright) && SendClientMessage(playerid, -1, "Вы закрыли переднюю правую дверь");
		else return SetVehicleParamsCarDoors(carid, driver, 1, backleft, backright) && SendClientMessage(playerid, -1, "Вы открыли переднюю правую дверь");
	}
	else if(iSeat == 2)
	{
		if(backleft == 1) return SetVehicleParamsCarDoors(carid, driver, passenger, 0, backright) && SendClientMessage(playerid, -1, "Вы закрыли заднюю левую дверь");
		else return SetVehicleParamsCarDoors(carid, driver, passenger, 1, backright) && SendClientMessage(playerid, -1, "Вы открыли заднюю левую дверь");
	}
	else if(iSeat == 3)
	{
		if(backright == 1) return SetVehicleParamsCarDoors(carid, driver, passenger, backleft, 0) && SendClientMessage(playerid, -1, "Вы закрыли заднюю правую дверь");
		else return SetVehicleParamsCarDoors(carid, driver, passenger, backleft, 1) && SendClientMessage(playerid, -1, "Вы открыли заднюю правую дверь");
	}*/
	return 1;
}


stock vehmenu_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
//stock vehmenu_OnDialog(playerid, dialogid, response, listitem, inputtext[])
{
	//#pragma unused inputtext
	FillCarDialogResponse(playerid, dialogid, response, listitem, inputtext);
	WINDOWS_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	DOORS_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	
	if(dialogid != VEHICLE_DIALOG) return 1;
	if(!response)
	{
		//DeletePVar(playerid, "Action");
		PlaySoundForPlayer(playerid, 5202);
		return 1;
	}
	new carid = nCarID[playerid];
	//new carid = GetPlayerVehicleID(playerid);
	new msgitem[256+1];
	new Float:pX, Float:pY, Float:pZ, Float:pA; //new Float:ang;
	new Float:vX, Float:vY, Float:vZ;//, Float:vA;
	new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
	
	//new engine,
	new lights, alarm, doors, bonnet, boot, objective;
	//GetVehicleParams(carid, engine, lights, alarm, doors, bonnet, boot, objective);//инициализируем массив CarStatus
	//engine = CarStatus[carid][st_engine];
	lights = CarStatus[carid][st_lights];
	alarm = CarStatus[carid][st_alarm];
	doors = CarStatus[carid][st_doors];
	bonnet = CarStatus[carid][st_bonnet];
	boot = CarStatus[carid][st_boot];
	objective = CarStatus[carid][st_objective];

//==============================================================================
	if(GetPVarInt(playerid, "Action") == 0)
	{//если операция ещё не выбрана, т.е. это ввод первого параметра
	    //не забыть обнулить при окончанию ввода параметров
		SetPVarInt(playerid, "Action", listitem);//записали выбранную операцию
		DeletePVar(playerid, "InputCounter");//очистили от предыдущих операций
	}
	new operation = GetPVarInt(playerid, "Action");
//------------------------------------------------------------------------------
//GetVehicleParamsEx(carid, engine, lights, alarm, doors, bonnet, boot, objective);
//format(strings, sizeof(strings), "carid: %d", carid);
//SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	if(operation == 0)// перевернуть
	{
	    DeletePVar(playerid, "Action");
		new Float:float_tmp;
		GetVehicleZAngle(carid, float_tmp);
		SetVehicleZAngle(carid, float_tmp);
		PlaySoundForPlayer(playerid, SOUND_TRAILER_HOOKUP);
	}
	else if(operation == 1)//Завести двигатель/Заглушить двигатель
	{
	    DeletePVar(playerid, "Action");
		OnPlayerKeySwitchEngine(playerid, carid);
	}
	else if(operation == 2)//включить/выключить свет
	{
	    DeletePVar(playerid, "Action");
		PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
		if(lights == VEHICLE_PARAMS_ON) SetVehicleParams(carid,
			CarStatus[carid][st_engine],VEHICLE_PARAMS_OFF,CarStatus[carid][st_alarm],CarStatus[carid][st_doors],
			CarStatus[carid][st_bonnet],CarStatus[carid][st_boot],CarStatus[carid][st_objective]);
		else SetVehicleParams(carid,
			CarStatus[carid][st_engine],VEHICLE_PARAMS_ON,
			CarStatus[carid][st_alarm],CarStatus[carid][st_doors],
			CarStatus[carid][st_bonnet],CarStatus[carid][st_boot],CarStatus[carid][st_objective]);
	}
	else if(operation == 3)//включить/выключить сигнализаци
	{
	    DeletePVar(playerid, "Action");
		if(alarm == VEHICLE_PARAMS_ON)//всегда сначало  VEHICLE_PARAMS_ON, т.е. else можете быть как VEHICLE_PARAMS_UNSET || VEHICLE_PARAMS_OFF
		{
			SetVehicleParams(carid,//playerid,
				CarStatus[carid][st_engine],
				CarStatus[carid][st_lights],
				VEHICLE_PARAMS_OFF,
				CarStatus[carid][st_doors],
				CarStatus[carid][st_bonnet],
				CarStatus[carid][st_boot],
				CarStatus[carid][st_objective]);
		}
		else SetVehicleParams(carid,//playerid,
				CarStatus[carid][st_engine],
				CarStatus[carid][st_lights],
				VEHICLE_PARAMS_ON,
				CarStatus[carid][st_doors],
				CarStatus[carid][st_bonnet],
				CarStatus[carid][st_boot],
				CarStatus[carid][st_objective]);
	}
	else if(operation == 4)//включить/выключить сирину
	{
	    DeletePVar(playerid, "Action");
	    
	    new siren = GetVehicleParamsSirenState(nCarID[playerid]);
	    if(siren == 1)
	    {
			if(alarm == VEHICLE_PARAMS_ON)//всегда сначало  VEHICLE_PARAMS_ON, т.е. else можете быть как VEHICLE_PARAMS_UNSET || VEHICLE_PARAMS_OFF
			{
				SetVehicleParams(carid,//playerid,
					CarStatus[carid][st_engine],
					CarStatus[carid][st_lights],
					VEHICLE_PARAMS_OFF,
					CarStatus[carid][st_doors],
					CarStatus[carid][st_bonnet],
					CarStatus[carid][st_boot],
					CarStatus[carid][st_objective]);
			}
			else SetVehicleParams(carid,//playerid,
					CarStatus[carid][st_engine],
					CarStatus[carid][st_lights],
					VEHICLE_PARAMS_ON,
					CarStatus[carid][st_doors],
					CarStatus[carid][st_bonnet],
					CarStatus[carid][st_boot],
					CarStatus[carid][st_objective]);
		}
	}
	else if(operation == 5)//открыть автомобиль/закрыть автомобиль
	{
	    DeletePVar(playerid, "Action");
		PlaySoundForPlayerInRange(playerid, SOUND_LOCK_CAR_DOORS, 30.0);
		if(doors == VEHICLE_PARAMS_ON)
		{
			SetVehicleParams(carid,//playerid,
				CarStatus[carid][st_engine],
				CarStatus[carid][st_lights],
				CarStatus[carid][st_alarm],
				VEHICLE_PARAMS_OFF,
				CarStatus[carid][st_bonnet],
				CarStatus[carid][st_boot],
				CarStatus[carid][st_objective]);
			PlaySoundForPlayerInRange(playerid, SOUND_LOCK_CAR_DOORS, 30.0);
			new strtmp[35+3];
			format(strtmp, sizeof(strtmp), "~w~Vehicle ~n~~p~%d ~n~~g~Unlocked", carid);
			GameTextForPlayerEx(playerid, strtmp, 5000, 6);

		}
		else
		{
			SetVehicleParams(carid,//playerid,
				CarStatus[carid][st_engine],
				CarStatus[carid][st_lights],
				CarStatus[carid][st_alarm],
				VEHICLE_PARAMS_ON,
				CarStatus[carid][st_bonnet],
				CarStatus[carid][st_boot],
				CarStatus[carid][st_objective]);
			PlaySoundForPlayerInRange(playerid, SOUND_LOCK_CAR_DOORS, 30.0);
		    new strtmp[33+3];
			format(strtmp, sizeof(strtmp), "~w~Vehicle ~n~~p~%d ~n~~r~Locked", carid);
			GameTextForPlayerEx(playerid, strtmp, 5000, 6);
		}
		//OnPlayerLockCar(playerid);
		/*if(CarStatus[carid][st_doors] == VEHICLE_PARAMS_ON)
		{
			UnLockCar(carid);
		}
		else LockCar(carid);*/
	}
	else if(operation == 6)//открыть/закрыть капот
	{
	    DeletePVar(playerid, "Action");
		PlaySoundForPlayerInRange(playerid, SOUND_LOCK_CAR_DOORS, 30.0);
		if(bonnet == VEHICLE_PARAMS_ON)
		{
			SetVehicleParams(carid,//playerid,
				CarStatus[carid][st_engine],
				CarStatus[carid][st_lights],
				CarStatus[carid][st_alarm],
				CarStatus[carid][st_doors],
				VEHICLE_PARAMS_OFF,
				CarStatus[carid][st_boot],
				CarStatus[carid][st_objective]);

		}
		else SetVehicleParams(carid,//playerid,
				CarStatus[carid][st_engine],
				CarStatus[carid][st_lights],
				CarStatus[carid][st_alarm],
				CarStatus[carid][st_doors],
				VEHICLE_PARAMS_ON,
				CarStatus[carid][st_boot],
				CarStatus[carid][st_objective]);
	}
	else if(operation == 7)//открыть/закрыть багажник
	{
	    DeletePVar(playerid, "Action");
		PlaySoundForPlayerInRange(playerid, SOUND_LOCK_CAR_DOORS, 30.0);
		if(boot == VEHICLE_PARAMS_ON)
		{
			SetVehicleParams(carid,//playerid,
				CarStatus[carid][st_engine],
				CarStatus[carid][st_lights],
				CarStatus[carid][st_alarm],
				CarStatus[carid][st_doors],
				CarStatus[carid][st_bonnet],
				VEHICLE_PARAMS_OFF,
				CarStatus[carid][st_objective]);

		}
		else SetVehicleParams(carid,//playerid,
				CarStatus[carid][st_engine],
				CarStatus[carid][st_lights],
				CarStatus[carid][st_alarm],
				CarStatus[carid][st_doors],
				CarStatus[carid][st_bonnet],
				VEHICLE_PARAMS_ON,
				CarStatus[carid][st_objective]);
	}
	else if(operation == 8)//установить маркер
	{
	    DeletePVar(playerid, "Action");
		if(objective == VEHICLE_PARAMS_ON)
		{
			SetVehicleParams(carid,//playerid,
				CarStatus[carid][st_engine],
				CarStatus[carid][st_lights],
				CarStatus[carid][st_alarm],
				CarStatus[carid][st_doors],
				CarStatus[carid][st_bonnet],
				CarStatus[carid][st_boot],
				VEHICLE_PARAMS_OFF);

		}
		else SetVehicleParams(carid,//playerid,
				CarStatus[carid][st_engine],
				CarStatus[carid][st_lights],
				CarStatus[carid][st_alarm],
				CarStatus[carid][st_doors],
				CarStatus[carid][st_bonnet],
				CarStatus[carid][st_boot],
				VEHICLE_PARAMS_ON);
	}
	else if(operation == 9)//запарковать/распарковать автомобиль
	{
	    DeletePVar(playerid, "Action");
//SendClientMessage(playerid, COLOR_LIGHTBLUE, "запарковать/распарковать автомобиль");
		if(VehInfo[carid][cPark] == 1) OnPlayerKeyUnParking(playerid);
		else OnPlayerKeyParking(playerid);
	}
	else if(operation == 10)//переключить на вид от первого лица
	{
//SendClientMessage(playerid, COLOR_LIGHTBLUE, "переключить на вид от первого лица");
		PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
		if(CameraOnePerson[playerid] == true)
		{
			CameraOnePerson[playerid] = false;

			if(PlayerCam[playerid][camobj] != 0 && IsValidObjectEx(PlayerCam[playerid][camobj]))
			{
				SetCameraBehindPlayer(playerid);
				DestroyObjectEx(PlayerCam[playerid][camobj]);
				PlayerCam[playerid][camobj] = 0;
			}
			SendClientMessage(playerid, COLOR_GREEN, "Вы выключили вид от 1 лица");
		}
		else
		{
			CameraOnePerson[playerid] = true;
			SetCameraOnePerson(playerid);
			SendClientMessage(playerid, COLOR_GREEN, "Вы включили вид от 1 лица");
		}
	}
	
	else if(operation == 11)//Управление окнами
	{
	    DeletePVar(playerid, "Action");
	    WindowsControl(playerid);
	}
	else if(operation == 12)//Управление дверьми
	{
	    DeletePVar(playerid, "Action");
	    DoorsControl(playerid);
	}
	else if(operation == 13)//радио
	{
	    DeletePVar(playerid, "Action");
		Radio(playerid);
	}
	else if(operation == 14)//Заправить
	{
	    DeletePVar(playerid, "Action");
		//FillCar(playerid);
		//MenuOperation[playerid] = 1;
		ShowPlayerDialogGap(playerid, FILLCAR_DIALOG, DIALOG_STYLE_INPUT, "Заправить авто",
"Введите уровень заполнения бака топлива в  процентах.\n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
	}
	else if(operation == 15)//выбросить пассажиров
	{
	    DeletePVar(playerid, "Action");
		//EjectPassenger(playerid, giveplayerid);
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if(i == playerid) continue;
			if( !IsPlayerConnected(i) || !gPlayerSpawned[i] ) continue;
			//if(!IsPlayerInAnyVehicle(i)) continue;
			//if(GetPlayerState(i) != PLAYER_STATE_PASSENGER) continue;
			if( !IsPlayerInVehicle(i, carid) ) continue;
			RemovePlayerFromVehicleEx(i);
			SendClientMessage(i, COLOR_GREY, "   Вы выкинуты из автомобиля !");
		}
		SendClientMessage(playerid, COLOR_GREY, "   Все пассажиры покинули ваш транспорт !");
	}
	else if(operation == 16)//посмотреть информацию о автомобиле
	{
	    DeletePVar(playerid, "Action");
		VehicleInfo(playerid, nCarID[playerid]);
	}
	else if(operation == 17)//Сдать в аренду
	{
	    DeletePVar(playerid, "Action");
		MenuOperation[playerid] = 1;
		ShowPlayerDialogGap(playerid, SELLCAR_DIALOG, DIALOG_STYLE_INPUT, "Прокат транспортных средств",
"Введите стоимость аренды.\nЦена не ниже $100 и не выше $1000\n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
	}
	else if(operation == 18)//Выставить на продажу
	{
	    DeletePVar(playerid, "Action");
		MenuOperation[playerid] = 2;
		ShowPlayerDialogGap(playerid, SELLCAR_DIALOG, DIALOG_STYLE_INPUT, "Продажа транспортного средства",
"Введите стоимость продажи.\nЦена не ниже $1000 и не выше $100000\n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
	}

	else if(operation == 19)//Удалить тачку
	{
	    DeletePVar(playerid, "Action");
	    if( IsPlayerInAnyVehicle(playerid)) {
			new vehicle;
			vehicle = GetPlayerVehicleID(giveplayerid);
			DestroyVehicleEx(vehicle, 40);//DialogResponse=40
		}
	}
	else if(operation == 20)//Установить на спаун
	{
	    DeletePVar(playerid, "Action");
	    if( IsPlayerInAnyVehicle(playerid)) {
			new vehicle;
			vehicle = GetPlayerVehicleID(giveplayerid);
			SetVehicleToRespawn(vehicle);
		}
	}
	else if(operation == 21)//Установить здоровье тачки
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, VEHICLE_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 1000. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(!strlen(inputtext) || strval(inputtext) < 0 || strval(inputtext) > 1000)
			{
				ShowPlayerDialogEx(playerid, VEHICLE_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите здоровье тачки от 0 до 1000.. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			DeletePVar(playerid, "Action");

			new Float: health = strval(inputtext);
			new vehicleid = GetPlayerVehicleID(giveplayerid);
    		SetVehicleHealth(vehicleid, health);
    		if(health > 900.0) RepairVehicleEx(playerid, vehicleid);
			format(msgitem, sizeof(msgitem), "AdmCmd: %s set %s's SetVehicleHealth: %.0f", PlayerName(playerid), PlayerName(giveplayerid), health);
			//Log(ADMINLOG, msgitem);
			//ABroadCast(COLOR_RED, msgitem, 9);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);
			//SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
		}
	}
	else if(operation == 22)//Установить тюнинг
	{
		DeletePVar(playerid, "Action");
#if defined vw_tuning
		tuning_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
#endif
	}
	else if(operation == 23)//Починить тачку
	{
	    DeletePVar(playerid, "Action");
	    if( IsPlayerInAnyVehicle(playerid))
		{
			RepairVehicleEx(playerid, GetPlayerVehicleID(giveplayerid));
		}
	}
	else if(operation == 24)//Телепорт тачки
	{
		//new carid;//, seatid;
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, VEHICLE_DIALOG, DIALOG_STYLE_INPUT, inputtext,	"Введите значение vehicleid. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			DeletePVar(playerid, "Action");
			carid = GetPVarInt(playerid, "InputValue");//strval(inputtext);//GetPVarInt(playerid, "InputValue");
			GetXYZInFrontOfPlayer(playerid, 2.0, pX,pY,pZ, pA);

			SetVehicleVirtualWorldEx(carid, PlayerInfo[playerid][pVirtual]);
			LinkVehicleToInteriorEx(carid, PlayerInfo[playerid][pInt]);
			SetVehiclePosEx(carid, pX,pY,pZ+1.2196);//работает если кто то сидит в машине? без разницы
			SetVehicleZAngleEx(carid, pA+90.0);

			format(msgitem, sizeof(msgitem), "AdmCmd: %s teleported the car:%d", PlayerName(playerid),carid);
			Log(ADMINLOG, msgitem);
			SendClientMessage(giveplayerid, COLOR_GREY, "   Вы телепортировали тачку!");
		}
	}
	else if(operation == 25)//Телепорт к тачке
	{
		//new carid;
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, VEHICLE_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение vehicleid. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			DeletePVar(playerid, "Action");
			carid = GetPVarInt(playerid, "InputValue");//strval(inputtext);//GetPVarInt(playerid, "InputValue");
			//vX = VehPos[carid][0];
			//vY = VehPos[carid][1];
			//vZ = VehPos[carid][2];
			GetVehiclePos(carid, vX, vY, vZ);

			SetPlayerInteriorEx(playerid, VehInfo[carid][cInt]);
			SetPlayerVirtualWorldEx(playerid, VehInfo[carid][cVirt]);
			PlayerInfo[playerid][pLocal] = FREEROAM;
			SetPlayerPosEx(playerid, vX, vY, vZ+1.0, 0);

			format(msgitem, sizeof(msgitem), "AdmCmd: %s goto teleported to vehicleid:%d", PlayerName(playerid),carid);
			Log(ADMINLOG, msgitem);
			SendClientMessage(giveplayerid, COLOR_GREY, msgitem);//"   Вы телепортировались к тачке!");
		}
	}
	else DeletePVar(playerid, "Action");
	GivePVarInt(playerid, "InputCounter", +1);//счётчик кол-ва входов в данную обработку
//format(strings, sizeof(strings), "carid: %d. engine: %d lights: %d alarm: %d doors: %d bonnet: %d boot: %d objective: %d", carid, engine, lights, alarm, doors, bonnet, boot, objective);
//SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	return 1;
}


stock FillCarDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	if(dialogid != FILLCAR_DIALOG) return 1;
	if(!response)
	{
	
		return 1;
	}
	new percent = strval(inputtext);
	if(	percent <  0 || percent > 100 )
	{
		SendClientMessage(playerid, COLOR_GREY, "   Процент не ниже 0 и не выше 100!");
		ShowPlayerDialogGap(playerid, FILLCAR_DIALOG, DIALOG_STYLE_INPUT, "Заправить авто",
"Введите кол-во литров топлива.\n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		return 1;
	}

	VehInfo[nCarID[playerid]][cFuel] = percent*VehicleArray[nCarModel[playerid]-400][GasMax]/100.0;
	gNoFuel[playerid] = 0;
	new strtmp[51+24+3+3];
	format(strtmp, sizeof(strtmp), "AdmCmd: %s cars %d filled with Fuel on the %d%%\%%", PlayerName(playerid), nCarID[playerid], percent);
	//PlayerTextDrawSetStringEx(playerid, txdPager[playerid], strcmd);
	Log(ADMINLOG, strtmp);
	SendClientMessage(playerid, COLOR_GREY, strtmp);
	//OnPlayerKeyParking(playerid, price);
	return 1;
}

//stock sellcar_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
stock sellcar_OnDialog(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	if(dialogid != SELLCAR_DIALOG) return 1;
	if(!response) return 1;
	new price = strval(inputtext);
	if(	MenuOperation[playerid] == 1 &&
		(price < 100 || price > 1000))
	{
		SendClientMessage(playerid, COLOR_GREY, "   Cуммма не ниже $100 и не выше $1000!");
		MenuOperation[playerid] = 1;
		ShowPlayerDialogGap(playerid, SELLCAR_DIALOG, DIALOG_STYLE_INPUT, "Прокат транспортных средств",
"Введите стоимость аренды.\nЦена не ниже $100 и не выше $1000\n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		return 1;
	}

	//OnPlayerKeyParking(playerid, price);
	return 1;
}

stock OnPlayerKeySwitchEngine(playerid, vehicleid)
{//вызывается из vehmenu_OnDialogResponse
   	/*if( !IsPlayerInAnyVehicle(playerid) )
	{
		//SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться в транспортном средстве!");
		return 1;
	}
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	{
		//SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться за рулём транспортного средства!");
		return 1;
	}*/
	//new engine, lights, alarm, doors, bonnet, boot, objective;
	//GetVehicleParams(carid, engine, lights, alarm, doors, bonnet, boot, objective);
	//GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	
	new carid = vehicleid; //nCarID[playerid];
	if( IsInBike(carid) ) return 1;
	//if( VehicleArray[nCarModel[playerid]-400][Category] == Airplane ) return 1;
	//т.к. у самалётов на 2 шасси

	//if(VehInfo[carid][cFuel] <= 0.1)//если топлива нет
	/*if(floatcmp(VehInfo[carid][cFuel], 0.1) <= 0 && nCarModel[playerid] != 485)
   	{//если VehInfo[carid][cFuel] меньше 0.1
		SendClientMessage(playerid, COLOR_GREY, "   Топливный Бак пуст (USE: /service mechanic).");
		return 1;
	}*/
	
	/*GetVehicleHealth(carid, VehInfo[carid][cHealth]);
	if(VehInfo[carid][cHealth] <= 350.0)
   	{
		SendClientMessage(playerid, COLOR_GREY, "   Двигатель неисправен (USE: /service mechanic).");
		return 1;
	}*/

    if(CarStatus[carid][st_engine] == VEHICLE_PARAMS_ON)
    {
    	if( VehicleArray[nCarModel[playerid]-400][Category] == Airplane &&
			GetVehicleSpeed(nCarID[playerid]) > 3) return 1;

		//PlaySoundForPlayerInRange(playerid, SOUND_LIGHTS_POWER_DOWN, 30.0);//заглушить
		SetVehicleParams(carid,//playerid,
  			VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,CarStatus[carid][st_alarm],CarStatus[carid][st_doors],CarStatus[carid][st_bonnet],
  			CarStatus[carid][st_boot],CarStatus[carid][st_objective]);
#if defined vw_speedometer
		gTextDrawHideSpeed[playerid] = true;
#endif
	}
    else
    {//если двигатель выключен
    	if( VehicleArray[nCarModel[playerid]-400][Category] == Airplane &&
			GetVehicleSpeed(nCarID[playerid]) > 3) return 1;
		//PlaySoundForPlayerInRange(playerid, SOUND_MECHANIC_SLIDE_OUT, 30.0);//завести
		SetVehicleParams(carid,//playerid,
			VEHICLE_PARAMS_ON,VEHICLE_PARAMS_ON,CarStatus[carid][st_alarm],CarStatus[carid][st_doors],CarStatus[carid][st_bonnet],
			CarStatus[carid][st_boot],CarStatus[carid][st_objective]);

		/*new strtmp[10];
		format(strtmp,sizeof(strtmp),"%d", VehInfo[nCarID[playerid]][cInsur]);
		PlayerTextDrawSetStringEx(playerid, txdInsurances[playerid], strtmp);*/

#if defined vw_speedometer
  		gTextDrawShowSpeed[playerid] = true;
#endif
	}
#if defined vw_speedometer
	//speedometer_StateChange(playerid);
	AdvisorOnOff(playerid);
#endif
	return 1;
}


stock LockCar(vehicleid)//вызывается по команде /lock
{   //надо закрывать дверь перед тем как игрок хочет там сесть
	//if(vehicleid != INVALID_VEHICLE_ID) return 1;

	if(vehicleid <= 0) return 1;
	if(VehInfo[vehicleid][cPark] >= 100) return 1;
	//if(IsInBike(vehicleid)) return 1;
	if(VehInfo[vehicleid][cLock] == 10)
	{
		VehInfo[vehicleid][cLock] = 11;
	}
 	else if(VehInfo[vehicleid][cLock] == 0)
	{
		VehInfo[vehicleid][cLock] = 1;
	}
	iVehicleObjective[vehicleid][MAX_PLAYERS-1] = 1;
	SetVehicleParams(vehicleid,//-1,
		CarStatus[vehicleid][st_engine],
		CarStatus[vehicleid][st_lights],
		CarStatus[vehicleid][st_alarm],
		VEHICLE_PARAMS_ON,
		CarStatus[vehicleid][st_bonnet],
		CarStatus[vehicleid][st_boot],
		CarStatus[vehicleid][st_objective]);
	return 1;
}
stock UnLockCar(vehicleid)//вызывается по команде /lock и в др. случаях
{
	if(vehicleid <= 0) return 1;
	//if(IsInBike(vehicleid)) return 1;
	if(VehInfo[vehicleid][cLock] == 11)
	{
		VehInfo[vehicleid][cLock] = 10;
	}
	else if(VehInfo[vehicleid][cLock] == 1)
	{
		VehInfo[vehicleid][cLock] = 0;
	}
	iVehicleObjective[vehicleid][MAX_PLAYERS-1] = 0;
	SetVehicleParams(vehicleid,//-1,
		CarStatus[vehicleid][st_engine],
		CarStatus[vehicleid][st_lights],
		CarStatus[vehicleid][st_alarm],
		VEHICLE_PARAMS_OFF,
		CarStatus[vehicleid][st_bonnet],
		CarStatus[vehicleid][st_boot],
		CarStatus[vehicleid][st_objective]);
	return 1;
}

stock OnPlayerLockCar(playerid)
{   //выполняется по команде или при нажатии клавиш
	new carid;
	if( //HireCarID[playerid] < MAX_VEHICLES-1 &&
		GetPVarInt(playerid, "gSwitchKey") == 2)
	{   //если есть ренткар и ключи переключены на рент кар
		//carid = HireCarID[playerid];
	}
	else
	{
		if(!IsPlayerInAnyVehicle(playerid))
		{
			//for(new vid = 1; vid<=GetMaxVehicles; vid++)
			new vid = 1;
			for(new v=0; v!=-1; v=StreamedVehicle[playerid][v])	{
				if(StreamedVehicle[playerid][v] == -1) continue;
				vid = StreamedVehicle[playerid][v];

				if(GetDistanceToCar(playerid, vid) >= 6.0) continue;
			 	if(PlayerInfo[playerid][pJob] == AUTOBUYER &&
				 	VehInfo[vid][cPark] == PlayerInfo[playerid][pBizz]-100)
				{
					carid = vid;
					break;
				}
			 	else if(VehInfo[vid][cOwned] > 0 &&
				 		VehInfo[vid][cOwned] == PlayerInfo[playerid][pSQLID]
						//!strcmp(VehInfo[vid][cOwner], PlayerName(playerid), true)
					   )
				{ //&& VehInfo[vid][cPark] <= 1
					carid = vid;
					break;
				}
			}
		}
		else
		{
			if(CurState[playerid] != PLAYER_STATE_DRIVER) { return 1; }
			if( VehInfo[nCarID[playerid]][cOwned] > 0 &&
				VehInfo[nCarID[playerid]][cOwned] == PlayerInfo[playerid][pSQLID]
				//!strcmp(VehInfo[nCarID[playerid]][cOwner], PlayerName(playerid), true)
			  )
	  		{
				carid = nCarID[playerid];//LastCar[playerid];
			}
		}
	}
	if(carid == 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   У вас нет Авто или Вы далеко от него или Авто запаркован.");// или он Запаркован
		return 1;
	}
	if(IsInBike(carid))
	{
		SendClientMessage(playerid, COLOR_GREY, "   Это транспортное средство не закрывается.");
		return 1;
	}
	if(VehInfo[carid][cLock] == 0 || VehInfo[carid][cLock] == 10)//если двери открыты
	{
		LockCar(carid);//блокируем двери carid
		if(	//HireCarID[playerid] == carid &&
			GetPVarInt(playerid, "gSwitchKey") == 2)
		{   //если есть ренткар и ключи переключены на рент кар
			GameTextForPlayerEx(playerid, "~w~Hire Vehicle ~r~Locked", 5000, 6);
		}
		else
		{
		    new strtmp[33+3];
			format(strtmp, sizeof(strtmp), "~w~Vehicle ~n~~p~%d ~n~~r~Locked", carid);
			GameTextForPlayerEx(playerid, strtmp, 5000, 6);
		}
		//if(CurState[playerid] == PLAYER_STATE_DRIVER) CheckInCar[playerid] = 2;
	}
	else if(VehInfo[carid][cLock] == 1 || VehInfo[carid][cLock] == 11)//если флаг gCarLock поднят - двери заблокированы
	{
		UnLockCar(carid);
		if(	//HireCarID[playerid] == carid &&
			GetPVarInt(playerid, "gSwitchKey") == 2)
		{
			GameTextForPlayerEx(playerid, "~w~Hire Vehicle ~g~Unlocked", 5000, 6);
		}
		else
		{
			new strtmp[35+3];
			format(strtmp, sizeof(strtmp), "~w~Vehicle ~n~~p~%d ~n~~g~Unlocked", carid);
			GameTextForPlayerEx(playerid, strtmp, 5000, 6);
		}
	}
	PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
	return 1;
}


stock radio_OnPlayerExitVehicle(playerid, vehicleid)
{
	#pragma unused vehicleid
	if(GetPVarInt(playerid, "Radio") != 0)
	{
		SetPVarInt(playerid, "Radio", 0);
		StopAudioStreamForPlayer(playerid);
	}
}

stock Radio(playerid)
{
	new listitems[] = "{FFFFFF}1\t{00FF00}Love радио\
\n{FFFFFF}2\t{00FF00}Aplus радио\
\n{FFFFFF}3\t{00FF00}Дача радио\
\n{FFFFFF}4\t{00FF00}ЕвропаПлюс\
\n{FFFFFF}5\t{00FF00}Авторадио\
\n{FFFFFF}6\t{00FF00}Наше радио\
\n{FFFFFF}7\t{00FF00}Русское радио\
\n{FFFFFF}8\t{00FF00}Рекорд (192 kbps)\
\n{FFFFFF}9\t{00FF00}Дорожное радио\
\n{FFFFFF}10\t{00FF00}Пилот FM\
\n{FFFFFF}11\t{00FF00}POWER FM В SA:MP\
\n{FFFFFF}12\t{00FF00}Своё радио";
	ShowPlayerDialogEx(playerid, RADIO_DIALOG, DIALOG_STYLE_LIST, "Выбирите Радио Станцию (USE: /music 0 - OFF)", listitems, "OK", "Cancel");
}


//stock radio_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
stock radio_OnDialog(playerid, dialogid, response, listitem, inputtext[])
{
	//#pragma unused inputtext
	if(dialogid != RADIO_DIALOG) { SetPVarInt(playerid, "Radio", 0); return 1; }
	if(!response) { SetPVarInt(playerid, "Radio", 0); return 1; }

//ShowPlayerDialogEx(playerid, 75, DIALOG_STYLE_LIST, "Выбирите Радио Станцию:", listitems, "OK", "Cancel");
	StopAudioStreamForPlayer(playerid);
	new url[128];
	if(GetPVarInt(playerid, "Radio") == 12) 
	{
		if(!strlen(inputtext) || strlen(inputtext) > 128)
		{
			SetPVarInt(playerid, "Radio", 12);
			ShowPlayerDialogEx(playerid, RADIO_DIALOG, DIALOG_STYLE_INPUT, "Своё Радио", "Введите url радиостанции \n(Пример: http://shoutcast.byfly.by:88/aplus)", "OK", "Cancel");
			return 1;
		}
		PlayAudioStreamForPlayer(playerid, inputtext);
		strmid(url, inputtext, 0, 128, 128);
		SetPVarInt(playerid, "Radio", 0);
		return 1;
	}
	if(listitem == 0)//Выключить радио
	{
		SetPVarInt(playerid, "Radio", 0);
		StopAudioStreamForPlayer(playerid);
		return 1;
	}
	else if(listitem == 1)//Love радио
	{
    	if(GetPVarInt(playerid, "Radio") != 1)
		{
    	    SetPVarInt(playerid, "Radio", 1);
			if(PlayerInfo[playerid][pOrigin] >= 0 && PlayerInfo[playerid][pOrigin] <= 5) {
				PlayAudioStreamForPlayer(playerid, "http://shoutcast.byfly.by:88/loveradio");
				strmid(url, "http://shoutcast.byfly.by:88/loveradio", 0, 128, 128);
			}
			else {
				PlayAudioStreamForPlayer(playerid, "http://stream.loveradio.ru:8000/loveradio_64");
				strmid(url, "http://stream.loveradio.ru:8000/loveradio_64", 0, 128, 128);
			}
		}
	}
	else if(listitem == 2)//Aplus радио
	{
    	if(GetPVarInt(playerid, "Radio") != 2)
		{
    	    SetPVarInt(playerid, "Radio",2);
			if(PlayerInfo[playerid][pOrigin] >= 0 && PlayerInfo[playerid][pOrigin] <= 5) {
				PlayAudioStreamForPlayer(playerid, "http://shoutcast.byfly.by:88/aplus");
				strmid(url, "http://shoutcast.byfly.by:88/aplus", 0, 128, 128);
			}
			else {
				PlayAudioStreamForPlayer(playerid, "http://webcast.emg.fm:55655/europaplus128.mp3");
				strmid(url, "http://webcast.emg.fm:55655/europaplus128.mp3", 0, 128, 128);
			}
		}
	}
	else if(listitem == 3)//Дача радио
	{
	   	if(GetPVarInt(playerid, "Radio") != 3)
		{
    	    SetPVarInt(playerid, "Radio",3);
			if(PlayerInfo[playerid][pOrigin] >= 0 && PlayerInfo[playerid][pOrigin] <= 5) {
				PlayAudioStreamForPlayer(playerid, "http://shoutcast.byfly.by:88/radiodacha");
				strmid(url, "http://shoutcast.byfly.by:88/radiodacha", 0, 128, 128);
			}
			else {
				PlayAudioStreamForPlayer(playerid, "http://shoutcast.byfly.by:88/radiodacha");
				strmid(url, "http://shoutcast.byfly.by:88/radiodacha", 0, 128, 128);
			}
		}
	}
	else if(listitem == 4)//ЕвропаПлюс
	{
    	if(GetPVarInt(playerid, "Radio") != 4)
		{
    	    SetPVarInt(playerid, "Radio",4);
			if(PlayerInfo[playerid][pOrigin] >= 0 && PlayerInfo[playerid][pOrigin] <= 5) {
				PlayAudioStreamForPlayer(playerid, "http://shoutcast.byfly.by:88/europaplus");
				strmid(url, "http://shoutcast.byfly.by:88/europaplus", 0, 128, 128);
			}
			else {
				PlayAudioStreamForPlayer(playerid, "http://shoutcast.byfly.by:88/europaplus");
				strmid(url, "http://shoutcast.byfly.by:88/europaplus", 0, 128, 128);
			}
		}
	}
	else if(listitem == 5)//Авторадио
	{
    	if(GetPVarInt(playerid, "Radio") != 5)
		{
    	    SetPVarInt(playerid, "Radio",5);
			if(PlayerInfo[playerid][pOrigin] >= 0 && PlayerInfo[playerid][pOrigin] <= 5) {
				PlayAudioStreamForPlayer(playerid, "http://shoutcast.byfly.by:88/avtoradio192");
				strmid(url, "http://shoutcast.byfly.by:88/avtoradio19", 0, 128, 128);
			}
			else {
				PlayAudioStreamForPlayer(playerid, "http://217.199.213.168:8000/v3_1");
				strmid(url, "http://217.199.213.168:8000/v3_1", 0, 128, 128);
			}
		}
	}
	else if(listitem == 6)//Наше радио
	{   //не пашет
    	if(GetPVarInt(playerid, "Radio") != 6)
		{
    	    SetPVarInt(playerid, "Radio",6);
			if(PlayerInfo[playerid][pOrigin] >= 0 && PlayerInfo[playerid][pOrigin] <= 5) {
				PlayAudioStreamForPlayer(playerid, "http://shoutcast.byfly.by:88/nashe128");
				strmid(url, "http://shoutcast.byfly.by:88/nashe128", 0, 128, 128);
			}
			else {
				PlayAudioStreamForPlayer(playerid, "http://94.25.53.133:80/nashe-96");
				strmid(url, "http://94.25.53.133:80/nashe-96", 0, 128, 128);
			}
		}
	}
	else if(listitem == 7)//Русское радио
	{
    	if(GetPVarInt(playerid, "Radio") != 7)
		{
    	    SetPVarInt(playerid, "Radio",7);
			if(PlayerInfo[playerid][pOrigin] >= 0 && PlayerInfo[playerid][pOrigin] <= 5) {
				PlayAudioStreamForPlayer(playerid, "http://shoutcast.byfly.by:88/russianradio");
				strmid(url, "http://shoutcast.byfly.by:88/russianradio", 0, 128, 128);
			}
			else {
				PlayAudioStreamForPlayer(playerid, "http://w01-cn01.akadostream.ru:8000/russianradio128.mp3");
				strmid(url, "http://w01-cn01.akadostream.ru:8000/russianradio128.mp3", 0, 128, 128);
			}
		}
	}
	else if(listitem == 8)//Рекорд (192 kbps)
	{
    	if(GetPVarInt(playerid, "Radio") != 8)
		{
    	    SetPVarInt(playerid, "Radio",8);
			if(PlayerInfo[playerid][pOrigin] >= 0 && PlayerInfo[playerid][pOrigin] <= 5) {
				PlayAudioStreamForPlayer(playerid, "http://shoutcast.byfly.by:88/radiorecord192");
				strmid(url, "http://shoutcast.byfly.by:88/radiorecord192", 0, 128, 128);
			}
			else {
				PlayAudioStreamForPlayer(playerid, "http://92.53.112.250:8101/rr_128");
				strmid(url, "http://92.53.112.250:8101/rr_128", 0, 128, 128);
			}
		}
	}
	else if(listitem == 9)//Дорожное радио
	{
    	if(GetPVarInt(playerid, "Radio") != 9)
		{
    	    SetPVarInt(playerid, "Radio",9);
			if(PlayerInfo[playerid][pOrigin] >= 0 && PlayerInfo[playerid][pOrigin] <= 5) {
				PlayAudioStreamForPlayer(playerid, "http://shoutcast.byfly.by:88/doroznoe");
				strmid(url, "http://shoutcast.byfly.by:88/doroznoe", 0, 128, 128);
			}
			else {
				PlayAudioStreamForPlayer(playerid, "http://dorognoe.hostingradio.ru:8000/dorognoe");
				strmid(url, "http://dorognoe.hostingradio.ru:8000/dorognoe", 0, 128, 128);
			}
		}
	}
	else if(listitem == 10)//Пилот FM
	{
    	if(GetPVarInt(playerid, "Radio") != 10)
		{
    	    SetPVarInt(playerid, "Radio",10);
			if(PlayerInfo[playerid][pOrigin] >= 0 && PlayerInfo[playerid][pOrigin] <= 5) {
				PlayAudioStreamForPlayer(playerid, "http://shoutcast.byfly.by:88/pilotfm");
				strmid(url, "http://shoutcast.byfly.by:88/pilotfm", 0, 128, 128);
			}
			else {
				PlayAudioStreamForPlayer(playerid, "http://shoutcast.byfly.by:88/pilotfm");
				strmid(url, "http://shoutcast.byfly.by:88/pilotfm", 0, 128, 128);
			}
		}
	}
	else if(listitem == 11)//POWER FM В SA:MP
	{
    	if(GetPVarInt(playerid, "Radio") != 11)
		{
    	    SetPVarInt(playerid, "Radio",11);
			PlayAudioStreamForPlayer(playerid, "http://radio.powerdance.ru:8018/power");
			strmid(url, "http://radio.powerdance.ru:8018/power", 0, 128, 128);
		}
	}
	else if(listitem == 12)//Своё Радио
	{
		SetPVarInt(playerid, "Radio", 12);
		ShowPlayerDialogEx(playerid, RADIO_DIALOG, DIALOG_STYLE_INPUT, "Своё Радио", "Введите url радиостанции \n(Пример: http://shoutcast.byfly.by:88/aplus)", "OK", "Cancel");
   	    //PlayAudioStreamForPlayer(playerid, "http://93.84.118.86:8000/wgb");
	}
	
	if(IsPlayerInAnyVehicle(playerid))
	{
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
			if(i == playerid) continue;
			if( !IsPlayerConnected(i) || !gPlayerSpawned[i] ) continue;
			//if(!IsPlayerInAnyVehicle(i)) continue;
			//if(GetPlayerState(i) != PLAYER_STATE_PASSENGER) continue;
			if( !IsPlayerInVehicle(i, nCarID[playerid]) ) continue;
			SetPVarInt(i, "Radio", listitem);
			StopAudioStreamForPlayer(i);
			PlayAudioStreamForPlayer(i, url);
			GameTextForPlayerEx(i, "~g~MP3-Player ON~n~~b~(USE: /music 0 - OFF)", 5000, 5);
		}
	}
	else
	{
		if(!GetPVarInt(playerid, "Radio"))	GameTextForPlayerEx(playerid, "~b~MP3-Player ~r~OFF", 5000, 5);
		else GameTextForPlayerEx(playerid, "~b~MP3-Player ~g~ON~n~~b~(USE: /music 0 - OFF)", 5000, 5);
	}
	return 1;
}


stock VehicleInfo(playerid, vehicleid)
{
	/*if(gLoading[playerid] || gUnLoading[playerid])
	{
		SendClientMessage(playerid, COLOR_GREY, "   Подождите окончания загрузки/выгрузки !");
		return 1;
	}*/
	/*if(CP[playerid] != 0)
	{
	   	SendClientMessage(playerid, COLOR_GREY, "   Вы не можете посмотреть информацию при выполнении задания !");
	   	return 1;
	}*/

	new strtmp[MAX_STRING];

//format(strtmp, sizeof(strtmp), "  vehicleid: %d", nCarID[playerid]);
//SendClientMessage(playerid, COLOR_RED, strtmp);
	
	if(!IsValidVehicle(vehicleid))
	{
		format(strtmp, sizeof(strtmp), "  vehicleid: %d не существует!", vehicleid);
		SendClientMessage(playerid, COLOR_RED, strtmp);
		return 1;
	}
	
	new modelid = nCarModel[playerid];//VehInfo[vehicleid][cModel];//VehInfo[vehicleid][cModel];//GetVehicleModel(vehicleid);
	if(modelid < 400)
	{
		format(strtmp, sizeof(strtmp), "  modelid: %d[%d] не существует!", modelid, VehInfo[vehicleid][cModel]);
		SendClientMessage(playerid, COLOR_RED, strtmp);
		return 1;
	}

	new Float:cwx2,Float:cwy2,Float:cwz2;
	GetVehiclePos(vehicleid, cwx2, cwy2, cwz2);
	new tcity[20], tregion[20];
	for(new j=0; j<MAX_ZONES; j++)
	{
		if(IsPointInZone(cwx2,cwy2,cwz2, j))
		{
			strmid(tcity, zones[j][zone_name], 0, strlen(zones[j][zone_name]), 20);
			break;
		}
	}
	for(new j=0; j<MAX_TURFS; j++)
	{
		if( IsPointInRegion(cwx2,cwy2,cwz2, j) )
		{
			strmid(tregion, regions[j][region_name], 0, strlen(regions[j][region_name]), 20);
			break;
		}
	}

	new carOwner[24];
	if(VehInfo[vehicleid][cOwned] != 0) strmid(carOwner, VehInfo[vehicleid][cOwner], 0, strlen(VehInfo[vehicleid][cOwner]), 24);
	else strmid(carOwner, "Отсутствует", 0, strlen("Отсутствует"), 24);
	
	new carPark[24];
	if(VehInfo[vehicleid][cPark] == 1) carPark = "Запаркован";
	else if(VehInfo[vehicleid][cPark] == 2) carPark = "На свалке";
	else if(VehInfo[vehicleid][cPark] >= 10 && VehInfo[vehicleid][cPark] < 100) carPark = "Продаётся";
	else if(VehInfo[vehicleid][cPark] >= 100 && VehInfo[vehicleid][cPark] < 1000 ) carPark = "Сдаётся";
	else if(VehInfo[vehicleid][cPark] >= 1000) carPark = "Выставлен на продажу";
	else carPark = "Не Запаркован";

	new carLock[20];
	if(VehInfo[vehicleid][cLock] == 1) carLock = "Закрыт";
	else if(VehInfo[vehicleid][cLock] == 11) carLock = "На сигнализации";
	else carLock = "Открыт";

//format(strtmp, sizeof(strtmp), "  vehicleid: %d", nCarID[playerid]);
//SendClientMessage(playerid, COLOR_RED, strtmp);

	//SetPlayerCheckpointEx(playerid, cwx2, cwy2, cwz2, CHECKPOINT_SIZE);
	//GameTextForPlayerEx(playerid, "~w~Waypoint set ~r~Car", 5000, 1);
	//SetPVarInt(playerid, "gCheckpointStatus", CHECKPOINT_CAR);

//#define DIALOG_WIDTH    	165.0
//#define DIALOG_HEIGHT   	150.0

	//new Float:BaseX = 320.0 - DIALOG_WIDTH/2.0;
	//new Float:BaseY = 240.0 - (DIALOG_HEIGHT + DIALOG_HEIGHT/2.0) + 7.0;
//	gSelectionItems[playerid] = CreateModelPreviewTextDraw(playerid, modelid,
//		VehInfo[vehicleid][cColor1], VehInfo[vehicleid][cColor2],
//		BaseX, BaseY, DIALOG_WIDTH, DIALOG_HEIGHT);

//\n{%06x}Основной цвет - {FFFFFF}%d {%06x}Дополнительный цвет - {FFFFFF}%d

	new msgitem[874];//575 + 24+10 + 20+20 + 20+20 +6+3+6+3 + 32 + 20+20+10+3+6 +3+2+10+10 + 51 = 874
    format(msgitem, sizeof(msgitem), "{0080FF}Владелец:{FFFFFF}%s {0080FF}Страховок:{FFFFFF}%d\
\n{0080FF}Состояние:{FFFFFF}%s %s\
\n{0080FF}Район:{FFFFFF}%s[%s]\
\n{0080FF}Основной цвет{FFFFFF}(%d){0080FF}Дополнительный цвет{FFFFFF}(%d)\
\n{0080FF}Прототип:{FFFFFF}%s\
\n{0080FF}Категория:{FFFFFF}%s {0080FF}Тюн:{FFFFFF}%s\
\n{0080FF}Цена:{33AA33}$%d {0080FF}Мест:{FFFFFF}%d {0080FF}Бак:{FFFFFF}%.0f[%d]\
\n{0080FF}Скорость:{FFFFFF}%d {0080FF}Расход:{FFFFFF}%d {0080FF}Загружен:{FFFFFF}%d[%d]",
		carOwner, VehInfo[vehicleid][cInsur],
		carPark, carLock,
		tcity,tregion,
		VehInfo[vehicleid][cColor1],VehInfo[vehicleid][cColor2],
		VehicleArray[modelid-400][Prototype],
		GetCarCategory(modelid-400),
		GetCarModifications(modelid-400),
		VehicleArray[modelid-400][Virtual_Price],
		VehicleArray[modelid-400][SeatID],
		VehInfo[vehicleid][cFuel], VehicleArray[modelid-400][GasMax],
		VehicleArray[modelid-400][LineSpeed],
		VehicleArray[modelid-400][fuelConsumption],
		VehInfo[vehicleid][cLoad],VehicleArray[modelid-400][Weight]/2);
	strcat(msgitem, "\n{AFAFAF}_________________________________________________");
	


	format(strings, sizeof(strings), "VehicleInfo strlen(msgitem): %d, sizeof(msgitem): %d",
			strlen(msgitem), sizeof(msgitem));
	SendClientMessage(playerid, COLOR_RED, strings);
		
	if(strlen(msgitem) >= sizeof(msgitem))
	{
		//ИНФОРМИРОВАНИЕ
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "Error28: %s[%d], VehicleInfo strlen(msgitem): %d > sizeof(msgitem): %d",
			PlayerName(playerid), playerid, strlen(msgitem), sizeof(msgitem));
		Log(ERROR, strings);
		
		format(strings, sizeof(strings), "VehicleInfo strlen(msgitem): %d, sizeof(msgitem): %d",
			strlen(msgitem), sizeof(msgitem));
		SendClientMessage(playerid, COLOR_RED, strings);
		return 1;
	}
	new caption[32+10];
    format(caption, sizeof(caption), "%s[%d]", VehicleArray[modelid-400][Vehicle_Name], VehicleArray[modelid-400][ModelID]);
	ShowPlayerDialogGap(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, caption, msgitem, "OK", "");
	return 1;
}

//Преобразователи
stock GetCarCategory(modelid)//для преобразования цифр в названия carinfo
{
	new category[20];
    switch(VehicleArray[modelid][Category])
	{
 		case 1: category = "Самолет";
		case 2: category = "Классический";
		case 3: category = "Вертолет";
		case 4: category = "Лоурайдер";
		case 5: category = "Роскошный";
		case 6: category = "Мотоцикл";
		case 7: category = "Внедорожник";
		case 8: category = "Гоночный";
		case 9: category = "Фургон";
		case 10: category = "Спортивный";

		case 11: category = "Велосипед";
		case 12: category = "Лодка";
		case 13: category = "Промышленный";
		case 14: category = "Грузовик";
		case 15: category = "Рабочий";
		case 16: category = "Рельсовый";
		case 17: category = "Игрушечный";
		case 18: category = "Скутер";
		case 19: category = "Служебный";
		case 20: category = "Прицеп";
		case 21: category = "Уникальный";
		default: category = "Не используется";
	}
	return category;
}
stock GetCarModifications(modelid)//для преобразования цифр в названия carinfo
{
	new modifications[20];
    switch(VehicleArray[modelid][Modifications])
	{
        case 0: modifications = "None";
		case 1: modifications = "Trans_Fender";
		case 2: modifications = "Loco_Low_Co";
		case 3: modifications = "Wheel_Arch_Angels";
		case 4: modifications = "Standard";
	}
	return modifications;
}


stock EjectPassenger(playerid, giveplayerid)
{
	new strcmd[MAX_STRING];
    if( !IsPlayerConnected(giveplayerid) )
	{
		format(strcmd, sizeof(strcmd), "   ID:%d отсутствует на сервере.", giveplayerid); SendClientMessage(playerid, COLOR_GREY, strcmd);
		return 1;
	}
	if( IsInNPCVehicle(nCarID[playerid]) ) return 1;
	if( IsInRentCar(nCarID[playerid]) ) return 1;
	if(IsPlayerInVehicle(giveplayerid, nCarID[playerid]))
	{
		if( IsInBike(nCarID[playerid]) ) removePlayerFromVehicle(giveplayerid);
		else RemovePlayerFromVehicleEx(giveplayerid);
		format(strcmd, sizeof(strcmd), "* Вы выбросили %s из автомобиля!", PlayerName(giveplayerid));
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);
		format(strcmd, sizeof(strcmd), "* Вас выбросил из автомобиля %s !", PlayerName(playerid));
		SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, strcmd);
	}
	else SendClientMessage(playerid, COLOR_GREY, "   Этот игрок - не в вашем Автомобиле !");
	return 1;
}



   

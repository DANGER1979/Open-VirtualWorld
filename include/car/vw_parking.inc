
stock parkinglift_OnPlayerPickUp(playerid, pickupid)
{
 	#pragma unused pickupid

	if(IsPlayerInRangeOfPoint(playerid, 2.1, 2118.6191,2416.6548,10.8203) ||
		IsPlayerInRangeOfPoint(playerid, 2.1, 2118.6228,2416.6250,15.1172) ||
		IsPlayerInRangeOfPoint(playerid, 2.1, 2118.6272,2416.6191,19.4219) ||
		IsPlayerInRangeOfPoint(playerid, 2.1, 2118.6274,2416.7107,23.7188) ||
		IsPlayerInRangeOfPoint(playerid, 2.1, 2118.6260,2416.6655,28.0234) ||
		IsPlayerInRangeOfPoint(playerid, 2.1, 2118.5996,2416.6738,32.3203) ||
		IsPlayerInRangeOfPoint(playerid, 2.1, 2118.6252,2416.6750,36.6172) ||
		IsPlayerInRangeOfPoint(playerid, 2.1, 2118.6274,2416.6843,40.9219) ||
		IsPlayerInRangeOfPoint(playerid, 2.1, 2118.6245,2416.7009,45.2188) ||
		IsPlayerInRangeOfPoint(playerid, 2.1, 2118.6169,2416.6995,49.5234)
	  )
	{
		new msgitem[] = "Level 1\nLevel 2\nLevel 3\nLevel 4\nLevel 5\nLevel 6\nLevel 7\nLevel 8\nLevel 9\nLevel 10";//\n\nНажмите Accept, чтобы принять.
		ShowPlayerDialogEx(playerid, PARKINGLIFT_DIALOG, DIALOG_STYLE_LIST, "Elevator for Parking", msgitem, "Перейти", "Отмена");
		//return 1;
	}
}


stock parkinglift_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if(dialogid != PARKINGLIFT_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	if(!response) return 1;

	new Float:plocx = 2116.2334,
		Float:plocy = 2416.6816,
		Float:plocz,
		Float:ploca = 88.0434;
	if(listitem == 0)//Level 1
	{
		plocz = 10.8203;
	}
	else if(listitem == 1)//Level 2
	{
		plocz = 15.1172;
	}
	else if(listitem == 2)//Level 3
	{
		plocz = 19.4219;
	}
	else if(listitem == 3)//Level 4
	{
		plocz = 23.7188;
	}
	else if(listitem == 4)//Level 5
	{
		plocz = 28.0234;
	}
	else if(listitem == 5)//Level 6
	{
		plocz = 32.3203;
	}
	else if(listitem == 6)//Level 7
	{
		plocz = 36.3250;
	}
	else if(listitem == 7)//Level 8
	{
		plocz = 40.9219;
	}
	else if(listitem == 8)//Level 9
	{
		plocz = 45.2188;
	}
	else if(listitem == 9)//Level 10
	{
		plocz = 49.5234;
	}
	else
	{
		return 1;
	}
	//PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);//выбор этажа
	PlaySoundForPlayer(playerid, SOUND_LIFT_START);//выбор этажа
	SetPlayerPosEx(playerid, plocx,plocy,plocz, ploca);
	return 1;
}





//##############################################################################//
//                                                                              //
//                             СИСТЕМА ПАРКОВКИ АВТО                            //
//                                                                              //
//##############################################################################//

stock OnPlayerKeyParking(playerid, sell=0)//, newkeys, oldkeys
{
	new timers = GetTickCount();
	if(GetPlayerSurfingVehicleID(playerid) != INVALID_VEHICLE_ID) return 1;
	if(SBizInfo[5][sbProducts] <= 0 && !gTutorial[playerid] && !gRealWar)
	{
		GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Car Delivery", 5000, 1);
    	PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
		return 1;
	}
	if(	PlayerInfo[playerid][pAccount] == 0 &&
		(IsPlayerInRangeOfPoint(playerid, 100.0, 368.3396,2498.1306,16.4006) || //Заброшенное Аэро
		IsPlayerInRangeOfPoint(playerid, 100.0, 365.3851,2537.2632,16.6646) ||   //Вертолётная площадка
		IsPlayerInRangeOfPoint(playerid, 100.0, -2202.8044,2418.8037,0.1991)) //Лодочная станция
	  )
	{
		SendClientMessage(playerid, COLOR_GREY, "   В этом месте нельзя парковать машину !");
		return 1;
	}
	/*if(	IsPlayerInArea(playerid, specialzone[8]) ) //автосалон
	{
		SendClientMessage(playerid, COLOR_GREY, "   На территории АвтоСалона запрещена парковка!");
		return 1;
	}
	if(	IsPlayerInArea(playerid, specialzone[10]) && //автошкола
		PlayerInfo[playerid][pMember] != DoE )
	{
		SendClientMessage(playerid, COLOR_GREY, "   На территории АвтоШколы запрещена парковка!");
		return 1;
	}*/
	/*for(new b=0; b<MAX_BIZ; b++)
	{
		if(!IsPlayerInRangeOfPoint(playerid, 30.0, BizInfo[b][bEntranceX],BizInfo[b][bEntranceY],BizInfo[b][bEntranceZ])) continue;
		SendClientMessage(playerid, COLOR_GREY, "   В этом месте нельзя парковать машину !");
		return 1;
	}
	for(new sb=0; sb<MAX_SBIZ; sb++)
	{
		if(!IsPlayerInRangeOfPoint(playerid, 30.0, SBizInfo[sb][sbEntranceX],SBizInfo[sb][sbEntranceY],SBizInfo[sb][sbEntranceZ])) continue;
		SendClientMessage(playerid, COLOR_GREY, "   В этом месте нельзя парковать машину !");
		return 1;
	}*/
	new carid = nCarID[playerid];
	if(carid < 1)
	{
	    SendClientMessage(playerid, COLOR_GREY, "   У Вас нет Транспортного Средства или Вы далеко от него!");
	    return 1;
	}
	if(VehInfo[carid][cPark] == 1)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Этот транспорт уже Запаркован !");
		return 1;
	}
	//new strings[MAX_STRING];
	if(GetVehicleSpeed(carid) > 1 && GetSeatVehiclePlayer(carid, 0) != INVALID_PLAYER_ID)
	{
		format(strings, sizeof(strings), "   Этот транспорт находится в движении (%d км/ч) !", GetVehicleSpeed(carid));
		SendClientMessage(playerid, COLOR_GREY, strings);
		return 1;
	}
    if(VehInfo[carid][cType] < 950)
	{
	    SendClientMessage(playerid, COLOR_GREY, "   Государственное Транспортное Средство нельзя парковать !");
	    return 1;
	}

    GetVehicleHealth(carid, VehHealth[carid]);
    if(VehHealth[carid] < 300.0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Целостность данного транспорта меньше 30 %% !");
		return 1;
	}
	new sb;
	if(	PlayerInfo[playerid][pJob] == AUTOBUYER && //для скупщиков
		VehInfo[carid][cOwned] > 0 &&// и тачку что ты паркуешь чья то
		PlayerInfo[playerid][pSQLID] != VehInfo[carid][cOwned]//и она не твоя
		//strcmp(VehInfo[carid][cOwner], PlayerName(playerid), true)
	  )
	{//то разрешить перепарковывать тачку в паркинге
#if defined vw_sql//#endif
		new ToBase[69+24+2+2];
		format(ToBase, sizeof(ToBase), "SELECT `ID` FROM `sbizz` WHERE `Owned`=%d AND `ID`>%d AND `ID`<=%d",
			PlayerInfo[playerid][pSQLID], PARKING, PARKING+sizeof(Parking));
		/*mysql_query(ToBase); mysql_store_result();
		if(mysql_num_rows() > 0 && mysql_retrieve_row())
	 	{
	 		new Field[20];
			mysql_fetch_field_row(Field, "ID");	PlayerInfo[playerid][pBizz] = strval(Field)-1+100;
		}
		mysql_free_result();*/
		
		new DBResult:db_result = db_query(db_VW, ToBase);
		if(db_num_rows(db_result))
	 	{
	 		new Field[20];
			db_get_field_assoc(db_result, "ID", Field, sizeof(Field) ); PlayerInfo[playerid][pBizz] = strval(Field)-1+100;
		}
		db_free_result(db_result);
#endif
		new sbouse = NOT_KEY, found;
		for(new limit = 0; limit < 20; limit++)
		{
			if(MyCompany[playerid][limit] == NOT_KEY) continue;
			sbouse = MyCompany[playerid][limit];
			if(sbouse >= PARKING && sbouse < PARKING+sizeof(Parking)) { found = 1; break; }
		}
		if(!found)
		{
  		    SendClientMessage(playerid, COLOR_GREY, "   У вас нет автостоянки в паркинге Emerald Isle в Las Venturas !");
			return 1;
		}

		for(new j = 0; j < sizeof(Parking); j++)
		{
			if(IsPlayerInArea(playerid, Parking[j]))
			{//находим номер биза где стоит игрок
				sb = PARKING+j;
				break;
			}
		}
		if(sb == 0)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Вы должны находиться в паркинге Emerald Isle в Las Venturas !");
			return 1;
		}
		if(PlayerInfo[playerid][pSQLID] != SBizInfo[sb][sbOwned] )
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Вы должны находиться на своей автостоянке !");
			return 1;
		}
	 	if(VehInfo[carid][cPark] != sb)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Этот транспорт не принадлежит вашей автостоянке !");
			return 1;
		}
	}
	else if(PlayerInfo[playerid][pSQLID] != VehInfo[carid][cOwned])
	{
		SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться за рулём СВОЕГО транспортного средства!");
		return 1;
	}
	if(VehInfo[carid][cPark] >= PARKING && VehInfo[carid][cPark] < PARKING+sizeof(Parking) && PlayerInfo[playerid][pJob] != AUTOBUYER)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вам надо выкупить этот транспорт, перед тем как припарковывать !");
		return 1;
	}
	if(GetAdminCar(carid) != -1)
	{
	    SendClientMessage(playerid, COLOR_GREY, "   Админские тачки нельзя парковать !!");
	    return 1;
	}
	//----------------------------------------------------------------------
	new found = -1;
	for(new j = 0; j < sizeof(AvailableParkings); j++)
	{
	    if(j == 24) continue;//пропускаем парковку мотеля
		if(IsPlayerInArea(playerid, AvailableParkings[j]))
		{
			found = j;	break;
		}
	}
	new h = PlayerInfo[playerid][pHouse];
	if(found == -1 && PlayerInfo[playerid][pAccount] == 0)
	{
		if( ( IsPlayerInArea(playerid, specialzone[16]) && PlayerInfo[playerid][pMember] == DoE ) ||
			( IsPlayerInArea(playerid, specialzone[8]) && PlayerInfo[playerid][pJob] == CARDEALER ) ||
			( IsPlayerInRangeOfPoint(playerid, 100.0, -1210.1460,-1043.3667,128.3897) ) ||
			( h != NOT_KEY && IsPlayerInRangeOfPoint(playerid, 30.0, HouseInfo[h][hEntranceX],HouseInfo[h][hEntranceY],HouseInfo[h][hEntranceZ]) )
		  )
		{	}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   В этом месте запрещена парковка. Найдите стоянку, обозначенную разметкой!");
			return 1;
		}
	}
    if(	PlayerInfo[playerid][pBank] < SBizInfo[5][sbEntranceCost] &&
		GetPlayerMoneyH(playerid) < SBizInfo[5][sbEntranceCost])
	{
		format(strings, sizeof(strings), "   Вы не можете оплатить парковку стоимостью $%d.", SBizInfo[5][sbEntranceCost]);
		SendClientMessage(playerid, COLOR_GREY, strings);
		return 1;
	}
	//----------------------------------------------------------------------
	if(PlayerInfo[playerid][pJob] == AUTOBUYER &&//для скупщиков
		PlayerInfo[playerid][pSQLID] != VehInfo[carid][cOwned]
		//strcmp(VehInfo[carid][cOwner], PlayerName(playerid), true)
	 )
	{
		VehInfo[carid][cPark] = sb;
	}
	else if(sell >= 100 && sell < 1000 && PlayerInfo[playerid][pSQLID] == VehInfo[carid][cOwned] )
	{
		new text[39+10];
		if(VehInfo[carid][cPark] < 100)
		{//если текст ещё не прикреплён
	   		format(text, sizeof(text), "Сдаётся.\n{FFFFFF}Цена: {33AA33}$%d", sell);
		    //sale3D[carid] = Create3DTextLabel(text, COLOR_LIGHTBLUE, 0.0,0.0,0.0, 50.0,0,1);
		    //Attach3DTextLabelToVehicle(sale3D[carid], carid, 0.0, 0.0, 1.0);
		    sale3D[carid] = Create3DTextLabelEx(text, COLOR_LIGHTBLUE,	0.0, 0.0, 1.0, 50.0, INVALID_PLAYER_ID, carid, 1, 0);
	    }
	    else
	    {
	   		format(text, sizeof(text), "Сдаётся.\n{FFFFFF}Цена: {33AA33}$%d", sell);
			//Update3DTextLabelText(sale3D[carid], COLOR_LIGHTBLUE, text);
			UpdateDynamic3DTextLabelText(sale3D[carid], COLOR_LIGHTBLUE, text);
	    }
		VehInfo[carid][cPark] = sell;
	}
	else if(sell >= 1000 && PlayerInfo[playerid][pSQLID] == VehInfo[carid][cOwned] )
	{
		new text[39+10];
		if(VehInfo[carid][cPark] < 100)
		{//если текст ещё не прикреплён
	   		format(text, sizeof(text), "Продаётся.\n{FFFFFF}Цена: {33AA33}$%d", sell);
		    //sale3D[carid] = Create3DTextLabel(text, COLOR_LIGHTBLUE, 0.0,0.0,0.0, 50.0,0,1);
		    //Attach3DTextLabelToVehicle(sale3D[carid], carid, 0.0, 0.0, 1.0);
		    sale3D[carid] = Create3DTextLabelEx(text, COLOR_LIGHTBLUE,	0.0, 0.0, 1.0, 50.0, INVALID_PLAYER_ID, carid, 1, 0);
	    }
	    else
	    {
	   		format(text, sizeof(text), "Продаётся.\n{FFFFFF}Цена: {33AA33}$%d", sell);
			UpdateDynamic3DTextLabelText(sale3D[carid], COLOR_LIGHTBLUE, text);
	    }
		VehInfo[carid][cPark] = sell;
	}
	else
	{
		DestroyDynamic3DTextLabel(sale3D[carid]); Counter3DText --;
		VehInfo[carid][cPark] = 1;
	}
	//----------------------------------------------------------------------
	/*if( IsVehicleInArea(carid, specialzone[10]) || //паркинг
		IsVehicleInArea(carid, specialzone[12]) )   //свалка
	{
		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}транспорт запаркован на стоянке, необходимо привозить брошеные авто!");
		return 1;
	}*/
	//----------------------------------------------------------------------
	if(	IsTrailerAttachedToVehicle(carid) &&
		//VehInfo[nTrailerID[playerid]][cOwned] == PlayerInfo[playerid][pSQLID]
		!strcmp(VehInfo[nTrailerID[playerid]][cOwner], PlayerName(playerid), true)
		)
	{
		new trailerid = nTrailerID[playerid];
		VehInfo[carid][cAttach] = trailerid;
	    SetVehicleParams(trailerid,//playerid,
			VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF);
		//LockCar(trailerid);
		//SaveTrailerParameters(trailerid);
	}

    SetVehicleParams(carid,//playerid,
		VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF);
	if(VehInfo[carid][cPark] == 1) LockCar(carid);
	else if(VehInfo[carid][cPark] == 2) UnLockCar(carid);
	else if(VehInfo[carid][cPark] >= 10 && VehInfo[carid][cPark] < 100 ) UnLockCar(carid);
	else if(VehInfo[carid][cPark] >= 100 && VehInfo[carid][cPark] < 1000 ) UnLockCar(carid);
	else if(VehInfo[carid][cPark] >= 1000) UnLockCar(carid);

#if defined vw_sql//#endif
	SaveCarParameters(carid);
#endif
	//gTextDrawHideSpeed[playerid] = true;
	OnPlayerTextDrawStateChange(playerid);

   	if(IsPlayerInAnyVehicle(playerid))
	{
		RemovePlayerFromVehicleEx(playerid);
	}
	//PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
	//PlayAudioStreamForPlayerEx(playerid, "repair.wav");

	new money = floatround(10*PlayerInfo[playerid][pLevel]*SBizInfo[5][sbEntranceCost]/100.0);

	if(PlayerInfo[playerid][pBank] >= money)
	{
	  	PlayerInfo[playerid][pBank] -= money;
		format(strings, sizeof(strings), "$%08d", PlayerInfo[playerid][pBank]);
		PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);
	}
	else
	{
		GivePlayerMoneyH(fsbiz+5, playerid, -money);
	}

	//OnGangsExtortionSBiz(5, money);
	SBizInfo[5][sbProducts] --;

	format(strings, sizeof(strings), "~w~Vehicle ~r~Parking %d~n~~r~-$%d", found, money);
	GameTextForPlayerEx(playerid, strings, 1000, 1);

	TestLog(OPTIM, "OnPlayerKeyParking", GetTickCount(), timers);//new timers = GetTickCount();
	return 1;
}

stock OnPlayerKeyUnParking(playerid)
{
 	if(GetPlayerSurfingVehicleID(playerid) != INVALID_VEHICLE_ID) return 1;
	new vid = 1, carid = 0;
	for(new v=0; v!=-1; v=StreamedVehicle[playerid][v])	{
		if(StreamedVehicle[playerid][v] == -1) continue;
		vid = StreamedVehicle[playerid][v];
		//находим свою запаркованную тачку в 30 м от себя
		if(	GetDistanceToCar(playerid, vid) < 30.0 &&
			VehInfo[vid][cPark] != 0 &&
			VehInfo[vid][cOwned] > 0 &&
			VehInfo[vid][cOwned] == PlayerInfo[playerid][pSQLID]
			//!strcmp(VehInfo[vid][cOwner], PlayerName(playerid), true)
			/* &&	VehInfo[vid][cVirt] == 0*/)
		{
			carid = vid;
			break;
		}
	}
	if(carid == 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Ваш транспорт Далеко от вас или НЕ запаркован или Это Транспортное Средство не принадлежит Вам!");
		return 1;
	}
	/*if(VehInfo[carid][cPark] == 2 && !IsPlayerInArea(playerid, specialzone[12]))//свалка scramble)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Ваш транспорт находится на Свалке (USE: /gps 1034)!");
		return 1;
	}*/
	if(PlayerInfo[playerid][pJob] == AUTOBUYER)//для скупщиков
	{   //скупщик не должен распарковывать тачки не принадлежащие его парковке
		new found;
		for(new limit = 0; limit < 20; limit++)
		{
			if(MyCompany[playerid][limit] == NOT_KEY) continue;
			new sbouse = MyCompany[playerid][limit];
			if(sbouse == VehInfo[carid][cPark])
			{
				found = 1; break;
			}
		}
		if(	!found &&
			carid != MyCar[playerid][0] && carid != MyCar[playerid][1] && carid != MyCar[playerid][2])
		{
	    	SendClientMessage(playerid, COLOR_GREY, "   Этот транспорт НЕ запаркован на вашей стоянке!");
			return 1;
		}
	}
	else
	{
		if(VehInfo[carid][cPark] >= PARKING && VehInfo[carid][cPark] < PARKING+sizeof(Parking))
		{   //и это не личная машина
			format(strings, sizeof(strings), "   Этот транспорт запаркован по автостоянке: %s[%d]", SBizInfo[ VehInfo[carid][cPark] ][sbDiscription], VehInfo[carid][cPark]);
	    	SendClientMessage(playerid, COLOR_GREY, strings);
			return 1;
		}
	}
	/*if(	VehInfo[carid][cPark] != 2 && //если тачка не на свалке
		SBizInfo[5][sbProducts] <= 0 && !gTutorial[playerid] && !gRealWar)
	{
		GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Car Delivery", 5000, 1);
    	PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
		return 1;
	}*/
	if(VehInfo[carid][cAttach] != 0)
	{//если что то прицеплено было
		new trailerid = VehInfo[carid][cAttach];
		SetVehiclePosEx(trailerid, VehInfo[trailerid][cLocX], VehInfo[trailerid][cLocY], VehInfo[trailerid][cLocZ]);
	   	SetVehicleZAngleEx(trailerid, VehInfo[trailerid][cAng]);
		SetVehicleHealthEx(playerid, trailerid, VehInfo[trailerid][cHealth]);
		AttachTrailerToVehicle(trailerid, nCarID[playerid]);
		//VehInfo[carid][cAttach] = 0;
	}
	if(VehInfo[carid][cPark] == 2 && !IsPlayerInArea(playerid, specialzone[12]))//свалка scramble)
	{
		//new Float: price = compcost*(100+SBizInfo[57][sbSellProd])/100.0;//15*(100+10)/100 = 16,5
		new cost = VehicleArray[nTrailerModel[playerid]-400][Virtual_Price]*(SBizInfo[57][sbSellProd])/100;//37282*10/100 = 3728,2
		//new iMaterials = floatround(cost/price);//3728,2/16,5 = 225,9515151515
		//SBizInfo[57][sbProducts] -= iMaterials;
		//SBizInfo[57][sbTill] += cost;
		//SBizInfo[57][sbExport] += cost;

		//new money = floatround(10*PlayerInfo[playerid][pLevel]*SBizInfo[5][sbEntranceCost]/100.0);

		if(PlayerInfo[playerid][pBank] >= cost)
		{
		  	PlayerInfo[playerid][pBank] -= cost;
			format(strings, sizeof(strings), "$%08d", PlayerInfo[playerid][pBank]);
			PlayerTextDrawSetStringEx(playerid, txdBankDisp[playerid], strings);
		}
		else
		{
			GivePlayerMoneyH(fsbiz+57, playerid, -cost);
		}
		//OnGangsExtortionSBiz(57, cost);
		SBizInfo[57][sbProducts] --;
		format(strings, sizeof(strings), "~w~Vehicle ~g~UnParking ~n~~r~-$%d", cost);
		GameTextForPlayerEx(playerid, strings, 1000, 1);
	}
	if(VehInfo[carid][cPark] >= 1000)//снятие продажи
	{
		DestroyDynamic3DTextLabel(sale3D[carid]);	Counter3DText --;
	}
	else GameTextForPlayerEx(playerid, "~w~Vehicle ~g~UnParking", 1000, 1);
    VehInfo[carid][cPark] = 0;
	SetVehiclePosEx(carid, VehInfo[carid][cLocX], VehInfo[carid][cLocY], VehInfo[carid][cLocZ]);
   	SetVehicleZAngleEx(carid, VehInfo[carid][cAng]);
	SetVehicleHealthEx(playerid, carid, VehInfo[carid][cHealth]);
	return 1;
}

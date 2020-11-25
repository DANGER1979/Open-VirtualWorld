//для телохранителей
new GuardPrice[MAX_PLAYERS];
//new index1,index2,index3,index4,index5,index6,index7,index8,index9;
new index12;
new PublicCar[350];

stock ServiceHelp(playerid)
{
	if(PlayerInfo[playerid][pInt] != 0 || PlayerInfo[playerid][pVirtual] != 0)
	{
		help_OnPlayerKeyStateChange(playerid); SendClientMessage(playerid, COLOR_GREY, "   Вы не можете воспользоваться этой командой в интерьере !");
		return 1;
	}
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && VehInfo[nCarID[playerid]][cPark] > 1)
	{
		help_OnPlayerKeyStateChange(playerid); SendClientMessage(playerid, COLOR_GREY, "   Вы не можете воспользоваться этой командой за рулём этого транспорта!");
		return 1;
	}
   	new listitems[] = "{FFFFFF}1\t{00FF00}Вызвать Медика\n{FFFFFF}2\t{00FF00}Вызвать Механика\n{FFFFFF}3\t{00FF00}Вызвать Такси\
\n{FFFFFF}4\t{00FF00}Позвонить в Мин.Транспорта\n{FFFFFF}5\t{00FF00}Позвонить в ФБР\n{FFFFFF}6\t{00FF00}Позвонить в Мин.Здравохранения\
\n{FFFFFF}7\t{00FF00}Подать Объявление\n{FFFFFF}8\t{00FF00}Буксировка авто к дому\n{FFFFFF}9\t{00FF00}Буксировка авто к дому с Ремонтом\n{FFFFFF}10\t{00FF00}Аренда Авто";

	MenuOperation[playerid] = 37;
	ShowPlayerDialogGap(playerid, SERVICE_DIALOG, DIALOG_STYLE_LIST, "Список Услуг", listitems, "OK", "Назад");
	return 1;
}
stock service_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
		if(dialogid != SERVICE_DIALOG) return 1;//service
		if(!response)
		{
			iOfferTime[playerid] = GetTickCount();
			help_OnPlayerKeyStateChange(playerid);
			return 1;
		}
	
		//#pragma unused inputtext
		new msgitem[256+1];
		new giveplayerid;
//ShowPlayerDialogGap(playerid, SERVICE_DIALOG, DIALOG_STYLE_LIST, "Список Услуг", listitems, "OK", "Cancel");
		if(MenuOperation[playerid] == 37)
		{
			if(listitem == 0)//Medic
			//if(!strcmp(tmp, "medic", true))//для медиков
			{
			    if(PlayerInfo[playerid][pMember] == DoH && gOnDuty[playerid] == 1)
			    {
					ServiceHelp(playerid);
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете сделать вызов на дежурстве !");
					return 1;
			    }
			    if(MedicCounter < 1)
		        {
		            ServiceHelp(playerid);
					SendClientMessage(playerid, COLOR_GREY, "   Нет Спасателей в настоящее время, (USE: /service/Аренда Авто) !");//на дежурстве
		            return 1;
		        }
				for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				    if(PlayerInfo[i][pMember] == DoH && gOnDuty[i] == 1 && CallTimeCounter[i] > 0 && MarkerToPlayer[i] == playerid)
				    {
			            ServiceHelp(playerid);
						SendClientMessage(playerid, COLOR_GREY, "   Вы уже сделали вызов !");
			            return 1;
					}
				}
			    format(msgitem, sizeof(msgitem), "Требуется Медик в %s.\nЗаказчик: %s\n\nНажмите Accept, чтобы принять.", GetPlayerInZoneName(playerid), PlayerName(playerid));
				for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
					if(AFK_IdleTime[i] >= 10) continue;
					if(PlayerInfo[i][pMember] != DoH) continue;
				    if(gOnDuty[i] != 1) continue;
				    if(GetPlayerState(i) != PLAYER_STATE_DRIVER) continue;
				    if(	!(IsInAmbulanceCar(nCarID[i]) && nCarModel[i] != 407) &&
						!IsAtHospital(playerid) ) continue;
					if(CallTimeCounter[i] != 0) continue;
					if(MarkerToPlayer[i] != MAX_PLAYERS-1) continue;
					if((GetTickCount()-iOfferTime[i]) < 60000) continue;
					//SendClientMessage(i, COLOR_ORANGE, msgitem);
					HideDialog(i);
					SetVehicleVelocity(nCarID[i], 0.0, 0.0, 0.0);
					MenuOperation[i] = 22;
					//TogglePlayerControllableEx(i, 0);//обездвиживает
					new TrafficManager[65];
					new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
					format(TrafficManager, sizeof(TrafficManager), "[%02d:%02d:%02d] Диспетчер", lH,lM,lS);
					ShowPlayerDialogEx(i, CALL_DIALOG, DIALOG_STYLE_MSGBOX, TrafficManager, msgitem, "Accept", "Cancel");
				}
		    	SendClientMessage(playerid, COLOR_GREY, "   Вы вызвали Спасателей, подождите ответ. Оставайтесь на месте.");
		    	playeridMedicCall = playerid;
			}
			else if(listitem == 1)//Mechanic
			//else if(!strcmp(tmp, "mechanic", true))
			{
			    if(PlayerInfo[playerid][pJob] == CARMECHANIC && gJobDuty[playerid] == 1)
			    {
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   Вы не можете сделать вызов на дежурстве !");
					return 1;
			    }
			    if(MechanicsCounter < 1)
		        {
		            ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   Нет Механиков на дежурстве в настоящее время (USE: /service/Аренда Авто) !");
		            return 1;
		        }
            	if(!IsPlayerInAnyVehicle(playerid))
				{
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться в транспортном средстве!");
					return 1;
				}
				if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
				{
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться за рулём транспортного средства!");
					return 1;
				}
				for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				    if(PlayerInfo[i][pJob] == CARMECHANIC && gJobDuty[i] == 1 &&
						CallTimeCounter[i] > 0 && MarkerToPlayer[i] == playerid)
				    {
			            ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   Вы уже сделали вызов !");
			            return 1;
					}
				}
				new found;
			    format(msgitem, sizeof(msgitem), "Требуется Механик в %s.\nЗаказчик: %s\n\nНажмите Accept, чтобы принять", GetPlayerInZoneName(playerid), PlayerName(playerid));
				for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
					if(AFK_IdleTime[i] >= 10) continue;
					if(PlayerInfo[i][pJob] != CARMECHANIC) continue;
				    if(gJobDuty[i] == 0) continue;
				    if(GetPlayerState(i) != PLAYER_STATE_DRIVER) continue;
				    if(nCarModel[i] != 525) continue;
					if(CallTimeCounter[i] != 0) continue;//если у этого механика установлено время ожидания кого-то, то пропустить
					if(MarkerToPlayer[i] != MAX_PLAYERS-1) continue;//если у этого механика установлен уже маркер на кого-то, то пропустить
					//if((GetTickCount()-iOfferTime[i]) < 60000) continue;//если время с момента последнего вызова прошло меньше минуты, то пропустить

					//SendClientMessage(i, COLOR_ORANGE, msgitem);
					HideDialog(i);
					SetVehicleVelocity(nCarID[i], 0.0, 0.0, 0.0);
					//TogglePlayerControllableEx(i, 0);//обездвиживает
					new TrafficManager[65];
					new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
					format(TrafficManager, sizeof(TrafficManager), "[%02d:%02d:%02d] Диспетчер", lH,lM,lS);
					MenuOperation[i] = 23;
					ShowPlayerDialogEx(i, CALL_DIALOG, DIALOG_STYLE_MSGBOX, TrafficManager, msgitem, "Accept", "Cancel");
					found ++;
				}
		    	if(found)
		    	{
					SendClientMessage(playerid, COLOR_GREY, "   Вы вызвали Механика, подождите ответ. Оставайтесь на месте.");
					playeridMechanicCall = playerid;
				}
		    	else { ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   В настоящее время нету доступных механиков (USE: /service/Аренда Авто) !"); }
			}
			else if(listitem == 2)//Taxi 13
		    //else if(!strcmp(tmp, "taxi", true))//для таксистов STEP3
			{
			    if(PlayerInfo[playerid][pJob] == TAXIDRIVER && gJobDuty[playerid] == 1)
			    {
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   Вы не можете сделать вызов на дежурстве !");
					return 1;
			    }
			    if(TaxiDriversCounter < 1)
		        {
		            ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   Нет Таксистов на дежурстве в настоящее время, (USE: /service/Аренда Авто) !");
		            return 1;
		        }
	           	if(IsPlayerInAnyVehicle(playerid))
				{
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "  Вы Не должны находиться в транспортном средстве!");
					return 1;
				}
				for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
				    if(PlayerInfo[i][pJob] == TAXIDRIVER && gJobDuty[i] == 1 && CallTimeCounter[i] > 0 && MarkerToPlayer[i] == playerid)
				    {
			            ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   Вы уже сделали вызов !");
			            return 1;
					}
				}
			    format(msgitem, sizeof(msgitem), "Требуется Такси в %s.\nЗаказчик: %s\n\n Нажмите Accept, чтобы принять.", GetPlayerInZoneName(playerid), PlayerName(playerid));
				for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
					if(AFK_IdleTime[i] >= 10) continue;
					if(PlayerInfo[i][pJob] != TAXIDRIVER) continue;
				    if(gJobDuty[i] != 1) continue;
				    if(GetPlayerState(i) != PLAYER_STATE_DRIVER) continue;
				    if(nCarModel[i] != 420 && nCarModel[i] != 438) continue;
					if(CallTimeCounter[i] != 0) continue;
					if(MarkerToPlayer[i] != MAX_PLAYERS-1) continue;
					if(TransportCostCounter[i] > 0) continue;
					if((GetTickCount()-iOfferTime[i]) < 60000) continue;
					//if(gTransportTime[i] > 0) continue;
					//SendClientMessage(i, COLOR_ORANGE, msgitem);
					HideDialog(i);
					SetVehicleVelocity(nCarID[i], 0.0, 0.0, 0.0);
					MenuOperation[i] = 24;
					//TogglePlayerControllableEx(i, 0);//обездвиживает
					new TrafficManager[65];
					new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
					format(TrafficManager, sizeof(TrafficManager), "[%02d:%02d:%02d] Диспетчер", lH,lM,lS);
					ShowPlayerDialogEx(i, CALL_DIALOG, DIALOG_STYLE_MSGBOX, TrafficManager, msgitem, "Accept", "Cancel");//для таксистов STEP4
				}
		    	SendClientMessage(playerid, COLOR_GREY, "   Вы вызвали Такси, подождите ответ. Оставайтесь на месте.");
		    	playeridTaxiCall = playerid;
			}
			else if(listitem == 3)//Rescue 911 Police
			{
				if(playeridMobileCall[playerid] != MAX_PLAYERS-1)
				{
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   Вы уже приняли вызов...");
					return 1;
				}
				//==================================================================
				if(PlayerInfo[playerid][pPnumber] == 0)
				{
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   У вас нет телефона !");
					return 1;
				}
				if(gPhoneOnline[playerid] == 1)// && PlayerInfo[playerid][pAdmin] < 1
				{
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}У Вас выключен Телефон (USE: /togphone, чтобы включить)");
					return 1;
				}
				SendClientMessage(playerid, COLOR_LIGHTORANGE, "ДИСПЕТЧЕР: Я переключаю Вас на ГЛ.УПР.ДПС, пожалуйста не вешайте трубку.");
				playeridMobileCall[playerid] = 912;//если police то переход на 912
		        format(msgitem, sizeof(msgitem), "Пожалуйста дайте мне короткое описание преступления \n(не более 128 символа).\
							\n\n\t{8CAA63}По окончанию ввода нажмите OK.", txtcost);
			    MenuOperation[playerid] = 38;
				ShowPlayerDialogGap(playerid, SERVICE_DIALOG, DIALOG_STYLE_INPUT, "ДЕЖУРНАЯ", msgitem, "OK", "Cancel");
			}
			else if(listitem == 4)//Rescue 911 FBI
		    //сall 911
			{
				if(playeridMobileCall[playerid] != MAX_PLAYERS-1)
				{
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   Вы уже приняли вызов...");
					return 1;
				}
				//==================================================================
				if(PlayerInfo[playerid][pPnumber] == 0)
				{
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   У вас нет телефона !");
					return 1;
				}
				if(gPhoneOnline[playerid] == 1)// && PlayerInfo[playerid][pAdmin] < 1
				{
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}У Вас выключен Телефон (USE: /togphone, чтобы включить)");
					return 1;
				}
				SendClientMessage(playerid, COLOR_LIGHTORANGE, "ДИСПЕТЧЕР: Я переключаю Вас на ГЛ.УПР.ФБР, пожалуйста не вешайте трубку.");
				playeridMobileCall[playerid] = 913;//если police то переход на 912
		        format(msgitem, sizeof(msgitem), "Пожалуйста дайте мне короткое описание преступления \n(не более 128 символа).\
							\n\n\t{8CAA63}По окончанию ввода нажмите OK.", txtcost);
			    MenuOperation[playerid] = 38;
				ShowPlayerDialogGap(playerid, SERVICE_DIALOG, DIALOG_STYLE_INPUT, "ДЕЖУРНАЯ", msgitem, "OK", "Cancel");
			}
			else if(listitem == 5)//Rescue 911 Paramedic
		    //сall 911
			{
				if(playeridMobileCall[playerid] != MAX_PLAYERS-1)
				{
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   Вы уже приняли вызов...");
					return 1;
				}
				//==================================================================
				if(PlayerInfo[playerid][pPnumber] == 0)
				{
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   У вас нет телефона !");
					return 1;
				}
				if(gPhoneOnline[playerid] == 1)// && PlayerInfo[playerid][pAdmin] < 1
				{
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}У Вас выключен Телефон (USE: /togphone, чтобы включить)");
					return 1;
				}
				SendClientMessage(playerid, COLOR_LIGHTORANGE, "ДИСПЕТЧЕР: Я переключаю Вас на Приемную Скорой Помощи, пожалуйста не вешайте трубку.");
				playeridMobileCall[playerid] = 914;//если paramedic то переход на 914
		        format(msgitem, sizeof(msgitem), "Пожалуйста дайте мне короткое описание Инцидента\n(не более 128 символа).\
							\n\n\t{8CAA63}По окончанию ввода нажмите OK.", txtcost);
			    MenuOperation[playerid] = 38;
				ShowPlayerDialogGap(playerid, SERVICE_DIALOG, DIALOG_STYLE_INPUT, "ДЕЖУРНАЯ", msgitem, "OK", "Cancel");
			}
			else if(listitem == 6)//Advertise /ad"
		    //if(!strcmp(cmd, "/advertise", true) == 0 || strcmp(cmd, "/ad", true))
			{
#if defined vw_sql//#endif
				new ToBase[74+24+2];
				format(ToBase, sizeof(ToBase), "SELECT `IND` FROM `blacklist` WHERE `Player`='%s' AND Family=%d", PlayerName(playerid), SAN);
				/*mysql_query(ToBase); mysql_store_result();
				if(mysql_num_rows() > 0)
			 	{
					mysql_free_result();
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете подавать объявления находясь в Чёрном Списке!");
		       		ServiceHelp(playerid);
					return 1;
				}
				mysql_free_result();*/
				new DBResult:db_result = db_query(db_VW, ToBase);
				if(db_num_rows(db_result))
			 	{
					db_free_result(db_result);
					SendClientMessage(playerid, COLOR_GREY, "   Вы не можете подавать объявления находясь в Чёрном Списке!");
		       		ServiceHelp(playerid);
					return 1;
				}
				db_free_result(db_result);
#endif
				new found;
				for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) ) continue;
					if( PlayerInfo[i][pMember] != SAN ) continue;
					found++;
				}
				if(!found)
			 	{
		       		SendClientMessage(playerid, COLOR_GREY, "   Нет сотрудников SAN онлайн !");
		       		ServiceHelp(playerid);
					return 1;
				}

		        format(msgitem, sizeof(msgitem), "Введите текст сообщения для рекламы.\
				\nСтоимость одного символа сообщения рекламы составляет $%d.\
					\n\n\t{8CAA63}По окончанию ввода нажмите OK.", txtcost);
			    MenuOperation[playerid] = 39;
				ShowPlayerDialogGap(playerid, SERVICE_DIALOG, DIALOG_STYLE_INPUT, "Advertise", msgitem, "OK", "Назад");
			}
			else if(listitem == 7)//towcar Буксировка авто к дому
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER )
				{//&& VehInfo[nCarID[playerid]][cPark] > 1
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   Вы не можете за рулём воспользоваться данной услугой !");
					return 1;
				}
			    if(GetPlayerMoneyH(playerid) < 50)
			    {
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   У вас нет $50 наличных !");
					return 1;
			    }
				if(PlayerInfo[playerid][pHouse] == NOT_KEY)
				{
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   У вас нет дома !");
					//GameTextForPlayerEx(playerid, "~w~You are not a home owner", 5000, 1);
					return 1;
				}
				if(SBizInfo[8][sbProducts] <= 0)
				{
					ServiceHelp(playerid);  SendClientMessage(playerid, COLOR_GREY, "   Нету товаров на складе службы буксировки !");
					//GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Tow Car Service", 5000, 1);
					//PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return 1;
				}
				MenuOperation[playerid] = 101;
				ShowPlayerDialogGap(playerid, SERVICEHELP_DIALOG, DIALOG_STYLE_INPUT, "TowCar Service",
					"Введите ID вашей тачки. (USE: /stats) \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "Ok", "Cancel");
			}
			else if(listitem == 8)//fixcar
			{
			    if(GetPlayerMoneyH(playerid) < 500)
			    {
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   У вас нет $500 наличных !");
					return 1;
			    }
				if(PlayerInfo[playerid][pHouse] == NOT_KEY)
				{
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   У вас нет дома !");
					//GameTextForPlayerEx(playerid, "~w~You are not a home owner", 5000, 1);
					return 1;
				}
				if(SBizInfo[8][sbProducts] <= 0)
				{
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   Нету товаров на складе Службы Буксировки !");
					//GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Tow Car Service", 5000, 1);
					//PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
					return 1;
				}
				MenuOperation[playerid] = 102;
				ShowPlayerDialogGap(playerid, SERVICEHELP_DIALOG, DIALOG_STYLE_INPUT, "FixCar Service",
					"Введите ID вашей тачки. (USE: /stats) \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "Ok", "Cancel");
 			}
			else if(listitem == 9)//	/rentcar	//Аренда Авто
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER )
				{//&& VehInfo[nCarID[playerid]][cPark] > 1
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   Вы не можете за рулём воспользоваться данной услугой !");
					return 1;
				}
			    if(GetPlayerMoneyH(playerid) < 500)
			    {
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   У вас нет $500 наличных !");
					return 1;
			    }
			   	if(PlayerInfo[playerid][pJailed] > 0)
				{
					ServiceHelp(playerid); SendClientMessage(playerid, COLOR_GREY, "   Вы не можете в данный момент воспользоваться данной услугой !");
					return 1;
				}
				if(IsPlayerInArea(playerid, specialzone[0]) && PlayerInfo[playerid][pMember] != DoD)
				{
					SendClientMessage(playerid, COLOR_GREY, "   На данной территории запрещено использовать эту команду !");
					return 1;
				}
				//if(SBizInfo[8][sbProducts] <= 0)
				//{
				//	GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Tow Car Service", 5000, 1);
				//	PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				//	return 1;
				//}
				new listitems[582];//50*6 + (32+3+6+6)*6 = 582
				new hirefee;
				new tow = SBizInfo[8][sbEntranceCost];
				if(SBizInfo[0][sbOwned] == 0) hirefee = HireCost(RentCar[0]);//получаем цену арендованной тачки
				else hirefee = SBizInfo[0][sbEntranceCost];
				new modelid = VehInfo[RentCar[0]][cModel];//GetVehicleModel(RentCar[0]);

				giveplayerid = GetSeatVehiclePlayer(RentCar[0], 0);
				if(giveplayerid != INVALID_PLAYER_ID) format(listitems, sizeof(listitems), "Car Renting: %s[%d]. Use: %s[%d]\n",
					VehicleArray[modelid-400][Vehicle_Name], RentCar[0], PlayerName(giveplayerid), giveplayerid);
				else format(listitems, sizeof(listitems), "Car Renting: %s[%d]. Аренда: $%d. Доставка: $%d\n",
					VehicleArray[modelid-400][Vehicle_Name], RentCar[0], hirefee, tow);

				modelid = VehInfo[RentCar[1]][cModel];//GetVehicleModel(RentCar[1]);
				giveplayerid = GetSeatVehiclePlayer(RentCar[1], 0);
				if(giveplayerid != INVALID_PLAYER_ID) format(listitems, sizeof(listitems), "%sCar Renting: %s[%d]. Use: %s[%d]\n",
					listitems, VehicleArray[modelid-400][Vehicle_Name], RentCar[1], PlayerName(giveplayerid), giveplayerid);
				else format(listitems, sizeof(listitems), "%sCar Renting: %s[%d]. Аренда: $%d. Доставка: $%d\n",
					listitems, VehicleArray[modelid-400][Vehicle_Name], RentCar[1], hirefee, tow);

				modelid = VehInfo[RentCar[2]][cModel];//GetVehicleModel(RentCar[2]);
				giveplayerid = GetSeatVehiclePlayer(RentCar[2], 0);
				if(giveplayerid != INVALID_PLAYER_ID) format(listitems, sizeof(listitems), "%sCar Renting: %s[%d]. Use: %s[%d]\n",
					listitems, VehicleArray[modelid-400][Vehicle_Name], RentCar[2], PlayerName(giveplayerid), giveplayerid);
				else format(listitems, sizeof(listitems), "%sCar Renting: %s[%d]. Аренда: $%d. Доставка: $%d\n",
					listitems, VehicleArray[modelid-400][Vehicle_Name], RentCar[2], hirefee, tow);
				//----------------------------------------------------------
				if(SBizInfo[1][sbOwned] == 0) hirefee = HireCost(nCarID[playerid]);//получаем цену арендованной тачки
				else hirefee = SBizInfo[1][sbEntranceCost];

				modelid = VehInfo[RentCar[3]][cModel];//GetVehicleModel(RentCar[3]);
				giveplayerid = GetSeatVehiclePlayer(RentCar[3], 0);
				if(giveplayerid != INVALID_PLAYER_ID) format(listitems, sizeof(listitems), "%sWang Cars: %s[%d]. Use: %s[%d]\n",
					listitems, VehicleArray[modelid-400][Vehicle_Name], RentCar[3], PlayerName(giveplayerid), giveplayerid);
				else format(listitems, sizeof(listitems), "%sWang Cars: %s[%d]. Аренда: $%d. Доставка: $%d\n",
					listitems, VehicleArray[modelid-400][Vehicle_Name], RentCar[3], hirefee, tow);

				modelid = VehInfo[RentCar[4]][cModel];//GetVehicleModel(RentCar[4]);
				giveplayerid = GetSeatVehiclePlayer(RentCar[4], 0);
				if(giveplayerid != INVALID_PLAYER_ID) format(listitems, sizeof(listitems), "%sWang Cars: %s[%d]. Use: %s[%d]\n",
					listitems, VehicleArray[modelid-400][Vehicle_Name], RentCar[4], PlayerName(giveplayerid), giveplayerid);
				else format(listitems, sizeof(listitems), "%sWang Cars: %s[%d]. Аренда: $%d. Доставка: $%d\n",
					listitems, VehicleArray[modelid-400][Vehicle_Name], RentCar[4], hirefee, tow);

				modelid = VehInfo[RentCar[5]][cModel];//GetVehicleModel(RentCar[5]);
				giveplayerid = GetSeatVehiclePlayer(RentCar[5], 0);
				if(giveplayerid != INVALID_PLAYER_ID) format(listitems, sizeof(listitems), "%sWang Cars: %s[%d]. Use: %s[%d]\n",
					listitems, VehicleArray[modelid-400][Vehicle_Name], RentCar[5], PlayerName(giveplayerid), giveplayerid);
				else format(listitems, sizeof(listitems), "%sWang Cars: %s[%d]. Аренда: $%d. Доставка: $%d\n",
					listitems, VehicleArray[modelid-400][Vehicle_Name], RentCar[5], hirefee, tow);

				MenuOperation[playerid] = 103;
				ShowPlayerDialogGap(playerid, SERVICEHELP_DIALOG, DIALOG_STYLE_LIST, "RentCar Service", listitems, "Ok", "Назад");
			}
		}
		else if(MenuOperation[playerid] == 38)
		{
			if(!strlen(inputtext) || strlen(inputtext) > 128)
			{
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
				RemovePlayerAttachedObject(playerid, MOBILE_SLOT);
				playeridMobileCall[playerid] = MAX_PLAYERS-1;
				SendClientMessage(playerid, COLOR_LIGHTORANGE, "ДИСПЕТЧЕР: Извините, я не понимаю.");
				return 1;
			}
		    new strtmp[65 + 128+24+3];//65 - максимальная для всех сообщений 911
			//для экстренных вызовов
			if(playeridMobileCall[playerid] == 915)
			{//ГЛ.УПР.Полиции
				if(!strcmp("no", inputtext, true))
				{   //если ID обвиняемого не указано
					new turner[MAX_PLAYER_NAME];
					GetPlayerName(playerid, turner, sizeof(turner));
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "ДЕЖУРНАЯ: Мы предупредили всех в штате. Благодарю вас за содействие!");
					format(strtmp, sizeof(strtmp), "DЕЖУРНАЯ: {FFFFFF}Всем патрулям ДПС. {33CCCC}Сообщение от: {FFFFFF}%s", turner);
					SendFamilyMessage(DoT, strtmp);
					//format(strtmp, sizeof(strtmp), "Обвинение: {FFFFFF}%s. {33CCCC}Подозреваемый: {FFFFFF}Неизвестен", PlayerCrime[playerid][pAccusing]);//badguy Неизвестен
					new tst_StrRet[128]; GetPVarString(playerid, "Accusing",tst_StrRet,128);
					format(strtmp, sizeof(strtmp), "Обвинение: {FFFFFF}%s. {99CCFF}Подозреваемый: {FFFFFF}Неизвестен", tst_StrRet);//badguy Неизвестен
					SendFamilyMessage(DoT, strtmp);
					SendClientMessage(playerid, COLOR_LILAC, "   линия отключена...");
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
					RemovePlayerAttachedObject(playerid, MOBILE_SLOT);
					playeridMobileCall[playerid] = MAX_PLAYERS-1;
					return 1;
				}
				new badguy = ReturnUser(inputtext);//плохой парень
				if(IsPlayerConnected(badguy) && badguy != INVALID_PLAYER_ID)
				{
					if(badguy == playerid || IsPlayerNPC(badguy))
					{
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "ДЕЖУРНАЯ: Хватить дурачиться, это экстренная линия.");
						SendClientMessage(playerid, COLOR_GRAD2, "   линия отключилась...");
						SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
						RemovePlayerAttachedObject(playerid, MOBILE_SLOT);
						playeridMobileCall[playerid] = MAX_PLAYERS-1;
						return 1;
					}
					else if(PlayerInfo[badguy][pMember] == DoT || PlayerInfo[badguy][pMember] == FBI || PlayerInfo[badguy][pMember] == DoD)
					{
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "ДЕЖУРНАЯ: Этот человек является представителем власти! Вы не можете обвинять его!");
						SendClientMessage(playerid, COLOR_GRAD2, "   линия отключилась...");
						SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
						RemovePlayerAttachedObject(playerid, MOBILE_SLOT);
						playeridMobileCall[playerid] = MAX_PLAYERS-1;
						return 1;
					}
					else if(WantedPoints[badguy] > 0)
					{   //если у подозреваемого уровень розыска больше 0
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "ДЕЖУРНАЯ: Этот человек уже в розыске ! Благодарю Вас за содействие !");
						SendClientMessage(playerid, COLOR_GRAD2, "   линия отключилась...");
						SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
						RemovePlayerAttachedObject(playerid, MOBILE_SLOT);
						playeridMobileCall[playerid] = MAX_PLAYERS-1;
						return 1;
					}
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "ДЕЖУРНАЯ: Мы предупредили всех в штате. Благодарю вас за содействие!!");
					format(strtmp, sizeof(strtmp), "DЕЖУРНАЯ: {FFFFFF}Всем патрулям ДПС. {33CCCC}Сообщение от: {FFFFFF}%s[%d]", PlayerName(playerid), playerid);
					SendFamilyMessage(DoT, strtmp);
					//format(strtmp, sizeof(strtmp), "Обвинение: {FFFFFF}%s. {33CCCC}Подозреваемый: {FFFFFF}%s[%d]", PlayerCrime[playerid][pAccusing], PlayerName(badguy), badguy);//badguy Неизвестен
					new tst_StrRet[128]; GetPVarString(playerid, "Accusing",tst_StrRet,128);
					format(strtmp, sizeof(strtmp), "Обвинение: {FFFFFF}%s. {99CCFF}Подозреваемый: {FFFFFF}%s[%d]", tst_StrRet, PlayerName(badguy), badguy);//badguy Неизвестен
					SendFamilyMessage(DoT, strtmp);

					SendClientMessage(playerid, COLOR_GREY, "   линия отключилась...");
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
					RemovePlayerAttachedObject(playerid, MOBILE_SLOT);
					playeridMobileCall[playerid] = MAX_PLAYERS-1;
					return 1;
				}//not connected
				else
				{
			        format(msgitem, sizeof(msgitem), "У меня нет Информации на %s, \nВы уверены, что имя правильное?", inputtext);
				    MenuOperation[playerid] = 38;
					ShowPlayerDialogGap(playerid, SERVICE_DIALOG, DIALOG_STYLE_INPUT, "ДЕЖУРНАЯ", msgitem, "OK", "Cancel");
				}
			}//End 913 Police
			else if(playeridMobileCall[playerid] == 916)
			{
				if(!strcmp("no", inputtext, true) )
				{   //если ID обвиняемого не указано
					new turner[MAX_PLAYER_NAME];
					GetPlayerName(playerid, turner, sizeof(turner));
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "ДЕЖУРНАЯ: Мы предупредили всех в штате. Благодарю вас за содействие");
					format(strtmp, sizeof(strtmp), "DЕЖУРНАЯ: {FFFFFF}Всем агентам FBI. {99CCFF}Сообщение от: {FFFFFF}%s",turner);
					SendFamilyMessage(FBI, strtmp);
					//format(strtmp, sizeof(strtmp), "Обвинение: {FFFFFF}%s. {99CCFF}Подозреваемый: {FFFFFF}Неизвестен", PlayerCrime[playerid][pAccusing]);//badguy Неизвестен
					new tst_StrRet[128]; GetPVarString(playerid, "Accusing",tst_StrRet,128);
					format(strtmp, sizeof(strtmp), "Обвинение: {FFFFFF}%s. {99CCFF}Подозреваемый: {FFFFFF}Неизвестен", tst_StrRet);//badguy Неизвестен
					SendFamilyMessage(FBI, strtmp);
					SendClientMessage(playerid, COLOR_LILAC, "   линия отключена...");
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
					RemovePlayerAttachedObject(playerid, MOBILE_SLOT);
					playeridMobileCall[playerid] = MAX_PLAYERS-1;
					return 1;
				}
				new badguy = ReturnUser(inputtext);//плохой парень
				if(IsPlayerConnected(badguy) && badguy != INVALID_PLAYER_ID)
				{
					if(badguy == playerid || IsPlayerNPC(badguy))
					{
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "ДЕЖУРНАЯ: Хватить дурачиться, это экстренная линия.");
						SendClientMessage(playerid, COLOR_GRAD2, "   линия отключилась...");
						SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
						RemovePlayerAttachedObject(playerid, MOBILE_SLOT);
						playeridMobileCall[playerid] = MAX_PLAYERS-1;
						return 1;
					}
					if(WantedPoints[badguy] > 0)
					{   //если у подозреваемого уровень розыска больше 0
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "ДЕЖУРНАЯ: Этот человек уже в розыске ! Благодарю Вас за содействие !");
						SendClientMessage(playerid, COLOR_GRAD2, "   линия отключилась...");
						SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
						RemovePlayerAttachedObject(playerid, MOBILE_SLOT);
						playeridMobileCall[playerid] = MAX_PLAYERS-1;
						return 1;
					}
					if(PlayerInfo[badguy][pMember] == DoT || PlayerInfo[badguy][pMember] == FBI || PlayerInfo[badguy][pMember] == DoD)
					{
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "ДЕЖУРНАЯ: Этот человек является представителем власти! Вы не можете обвинять его!");
						SendClientMessage(playerid, COLOR_GRAD2, "   линия отключилась...");
						SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
						RemovePlayerAttachedObject(playerid, MOBILE_SLOT);
						playeridMobileCall[playerid] = MAX_PLAYERS-1;
						return 1;
					}
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "ДЕЖУРНАЯ: Мы предупредили всех в штате. Благодарю вас за содействие");
					format(strtmp, sizeof(strtmp), "DЕЖУРНАЯ: {FFFFFF}Всем агентам FBI. {99CCFF}Сообщение от: {FFFFFF}%s[%d]", PlayerName(playerid), playerid);
					SendFamilyMessage(FBI, strtmp);

					//format(strtmp, sizeof(strtmp), "Обвинение: {FFFFFF}%s. {99CCFF}Подозреваемый: {FFFFFF}%s[%d]", PlayerCrime[playerid][pAccusing], PlayerName(badguy), badguy);//badguy Неизвестен
					new tst_StrRet[128]; GetPVarString(playerid, "Accusing",tst_StrRet,128);
					format(strtmp, sizeof(strtmp), "Обвинение: {FFFFFF}%s. {99CCFF}Подозреваемый: {FFFFFF}%s[%d]", tst_StrRet, PlayerName(badguy), badguy);//badguy Неизвестен
					SendFamilyMessage(FBI, strtmp);

					SendClientMessage(playerid, COLOR_GREY, "   линия отключилась...");
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
					RemovePlayerAttachedObject(playerid, MOBILE_SLOT);
					playeridMobileCall[playerid] = MAX_PLAYERS-1;
					return 1;
				}//not connected
				else
				{
			        format(msgitem, sizeof(msgitem), "У меня нет Информации на %s, \nВы уверены, что имя правильное?", inputtext);
				    MenuOperation[playerid] = 38;
					ShowPlayerDialogGap(playerid, SERVICE_DIALOG, DIALOG_STYLE_INPUT, "ДЕЖУРНАЯ", msgitem, "OK", "Cancel");
				}
			}//End 913 FBI
	        //--------------------------------------------------------------
			else if(playeridMobileCall[playerid] == 912)
			{
				SetPVarString(playerid, "Accusing", inputtext);
			    MenuOperation[playerid] = 38;
				ShowPlayerDialogGap(playerid, SERVICE_DIALOG, DIALOG_STYLE_INPUT, "ДЕЖУРНАЯ", "Введите имя нарушителя или его ID\nили просто введите NO.\
							\n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				playeridMobileCall[playerid] = 915;
			}
			else if(playeridMobileCall[playerid] == 913)
			{
				SetPVarString(playerid, "Accusing", inputtext);
			    MenuOperation[playerid] = 38;
				ShowPlayerDialogGap(playerid, SERVICE_DIALOG, DIALOG_STYLE_INPUT, "ДЕЖУРНАЯ","Введите имя нарушителя или его ID\nили просто введите NO.\
							\n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				playeridMobileCall[playerid] = 916;
			}
			else if(playeridMobileCall[playerid] == 914)
			{
				SetPVarString(playerid, "Accusing", inputtext);
				format(strtmp, sizeof(strtmp), "IIРИЕМНАЯ: Всем машинам SAMD: Сообщение от: %s", PlayerName(playerid));
				SendFamilyMessage(DoH, strtmp);
				format(strtmp, sizeof(strtmp), "IIРИЕМНАЯ: Инцидент: %s", inputtext);
				SendFamilyMessage(DoH, strtmp);
				SendClientMessage(playerid, COLOR_PINK, "ПРИЕМНАЯ: Мы предупредили всех в округе. Спасибо за сообщение.");
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
				RemovePlayerAttachedObject(playerid, MOBILE_SLOT);
				playeridMobileCall[playerid] = MAX_PLAYERS-1;
				SendClientMessage(playerid, COLOR_LILAC, "   линия отключена...");
			}//End 913 Paramedic
		}
		else if(MenuOperation[playerid] == 39)//ad
		{
			OnPlayerAdvertise(playerid, inputtext);
		}
		return 1;
}

stock servicehelp_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
			//#pragma unused listitem
			//#pragma unused inputtext
			if(dialogid != SERVICEHELP_DIALOG) return 1;
			if(!response) { ServiceHelp(playerid); return 1; }
			new msgitem[256+1];
			//new giveplayerid;
//ShowPlayerDialogGap(playerid, SERVICEHELP_DIALOG, DIALOG_STYLE_INPUT, "TowCar Service",
			if(MenuOperation[playerid] == 101)
			{
   				if(!strlen(inputtext))
				{
					MenuOperation[playerid] = 101;
					ShowPlayerDialogGap(playerid, SERVICEHELP_DIALOG, DIALOG_STYLE_INPUT, "TowCar Service",
						"Введите ID вашей тачки. (USE: /stats) \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "Ok", "Cancel");
					return 1;
				}
				new carid = strval(inputtext);
				if(carid != MyCar[playerid][0] && carid != MyCar[playerid][1] && carid != MyCar[playerid][2])
				{
					MenuOperation[playerid] = 101;
					ShowPlayerDialogGap(playerid, SERVICEHELP_DIALOG, DIALOG_STYLE_INPUT, "TowCar Service",
						"Введите ID вашей тачки. (USE: /stats) \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "Ok", "Cancel");
					return 1;
				}
				if(carid <= 0)
				{
				    SendClientMessage(playerid, COLOR_GREY, "   У Вас нет собственного Транспортного Средства!");
				    return 1;
				}
				if(VehInfo[carid][cPark] >= PARKING)
				{
				    SendClientMessage(playerid, COLOR_GREY, "   Ваше Транспортное Средство находится у скупщика авто!");
				    return 1;
				}
				if(GetVehicleSpeed(carid) > 1 &&
					GetSeatVehiclePlayer(carid, 0) != INVALID_PLAYER_ID)
				{
					format(msgitem, sizeof(msgitem), "   Этот транспорт находится в движении (%d км/ч) !", GetVehicleSpeed(carid));
					SendClientMessage(playerid, COLOR_GREY, msgitem);
					return 1;
				}
			    GetVehicleHealth(carid, VehHealth[carid]);
			    if(VehHealth[carid] < 300.0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Целостность даного транспорта меньше 30 %% !");
					return 1;
				}
				if(PlayerInfo[playerid][pHouse] == NOT_KEY)
				{
					GameTextForPlayerEx(playerid, "~w~You are not a home owner", 5000, 1);
					return 1;
				}
				new housekey = PlayerInfo[playerid][pHouse];
				if(	!IsPlayerInRangeOfPoint(playerid, 8.0, HouseInfo[housekey][hEntranceX],HouseInfo[housekey][hEntranceY],HouseInfo[housekey][hEntranceZ]) )
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы НЕ рядом с домом!");
					return 1;
				}
				if(OnCarTow(carid, PlayerInfo[playerid][pHouse]))//если ф-ия OnCarTow сработала
				{   //если машина свободная
					//GameTextForPlayerEx(playerid, "~w~Car~n~~g~Towed Home~n~~r~$-500", 5000, 1);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "Ваш автомобиль успешно доставлен к дому в полной сохранности !");
					GivePlayerMoneyH(fcar, playerid, -SBizInfo[8][sbEntranceCost]);//500 для экономики
					SBizInfo[8][sbTill] += SBizInfo[8][sbEntranceCost];
					SBizInfo[8][sbExport] += SBizInfo[8][sbEntranceCost];
				}
				else GameTextForPlayerEx(playerid, "~w~Car is~n~in ~r~use", 5000, 1);
			}
			else if(MenuOperation[playerid] == 102)//	/fixcar
			{
   				if(!strlen(inputtext))
				{
					MenuOperation[playerid] = 102;
					ShowPlayerDialogGap(playerid, SERVICEHELP_DIALOG, DIALOG_STYLE_INPUT, "FixCar Service",
						"Введите ID вашей тачки. (USE: /stats) \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "Ok", "Cancel");
					return 1;
				}
				new carid = strval(inputtext);
				if(carid != MyCar[playerid][0] && carid != MyCar[playerid][1] && carid != MyCar[playerid][2])
				{
					MenuOperation[playerid] = 102;
					ShowPlayerDialogGap(playerid, SERVICEHELP_DIALOG, DIALOG_STYLE_INPUT, "FixCar Service",
						"Введите ID вашей тачки. (USE: /stats) \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "Ok", "Cancel");
					return 1;
				}
				if(carid <= 0)
				{
				    SendClientMessage(playerid, COLOR_GREY, "   У Вас нет собственного Транспортного Средства!");
				    return 1;
				}
				if(VehInfo[carid][cPark] >= PARKING)
				{
				    SendClientMessage(playerid, COLOR_GREY, "   Ваше Транспортное Средство находится у скупщика авто!");
				    return 1;
				}
			    GetVehicleHealth(carid, VehHealth[carid]);
			    if(VehHealth[carid] < 300.0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Целостность даного транспорта меньше 30 %% !");
					return 1;
				}
				if(PlayerInfo[playerid][pHouse] == NOT_KEY)
				{
					GameTextForPlayerEx(playerid, "~w~You are not a home owner", 5000, 1);
					return 1;
				}
				new housekey = PlayerInfo[playerid][pHouse];
				if(	!IsPlayerInRangeOfPoint(playerid, 8.0, HouseInfo[housekey][hEntranceX],HouseInfo[housekey][hEntranceY],HouseInfo[housekey][hEntranceZ]) )
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы НЕ рядом с домом!");
					return 1;
				}
				if(OnCarRespawn(carid, PlayerInfo[playerid][pHouse]))
				{
					gNoFuel[playerid] = 0;
					//GameTextForPlayerEx(playerid, "~w~Car~n~~g~Repaired~n~~r~$-1000", 5000, 1);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "Ваш автомобиль успешно доставлен домой с полным тюнингом!");// и заправкой
					GivePlayerMoneyH(fcar, playerid, (-10*SBizInfo[8][sbEntranceCost]));//5000 для экономики
					SBizInfo[8][sbTill] += 10*SBizInfo[8][sbEntranceCost];
					SBizInfo[8][sbExport] += 10*SBizInfo[8][sbEntranceCost];
				}
				else GameTextForPlayerEx(playerid, "~w~Car is~n~in ~r~use", 5000, 1);
			}
			else if(MenuOperation[playerid] == 103)//	/rentcar
			{
				for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) ) continue;
					if( IsPlayerInVehicle(i, RentCar[listitem]))
					{	//сканируем всех кто находится в данной тачке
						SendClientMessage(playerid, COLOR_GREY, "   Автомобиль занят ! Пожалуйста, выберите другой!");
						return 1;
				    }
				}
				for(new j=0, i; j<MaxPlayers; j++)	{
					i = PLIDs[j];
					if( !IsPlayerConnectedEx(i) ) continue;
					if(HireCarID[i] == RentCar[listitem])
					{	//сканируем всех кто арендовал эту тачку
						SendClientMessage(playerid, COLOR_GREY, "   Автомобиль уже арендован ! Пожалуйста, выберите другой!");
						return 1;
				    }
				}

				new Float:X,Float:Y,Float:Z;
				new Float: Ang2;
				GetXYZInFrontOfPlayer(playerid, 2.0, X,Y,Z, Ang2);
				SetVehiclePosEx(RentCar[listitem], X,Y,Z+1.2196);//работает если кто то сидит в машине? без разницы
		    	SetVehicleZAngleEx(RentCar[listitem], Ang2+90.0);

				GivePlayerMoneyH(fcar, playerid, (-SBizInfo[8][sbEntranceCost]));//5000 для экономики
				//SBizInfo[8][sbTill] += SBizInfo[8][sbEntranceCost];
				//SBizInfo[8][sbExport] += SBizInfo[8][sbEntranceCost];
				OnGangsExtortionSBiz(8, SBizInfo[8][sbEntranceCost]);
				SBizInfo[8][sbProducts] --;
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "Автомобиль для аренды успешно доставлен!");// и заправкой
			}
			return 1;
}


stock call_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != CALL_DIALOG) return 1;
	new msgitem[256+1];
	if(!response)
	{
		iOfferTime[Offer[playerid]] = GetTickCount();
		iOfferTime[playerid] = GetTickCount();
		if(	MenuOperation[playerid] == 22 || MenuOperation[playerid] == 23 ||
			MenuOperation[playerid] == 24)
		{
			if(!gLoading[playerid] && !gUnLoading[playerid])
			{
				TogglePlayerControllableEx(playerid, 1);//размораживает
			}
		}
		Offer[playerid] = MAX_PLAYERS-1;
		SetPVarInt(playerid, "RefillPrice", 0);
		gNoFuel[playerid] = 0;
		SetPVarInt(playerid, "RepairPrice", 0);
		SetPVarInt(playerid, "TuningPrice", 0);//цену на услугу обнуляем

		format(msgitem, sizeof(msgitem), "%s отказался от предложенной услуги !!", PlayerName(playerid));
		ProxDetector(playerid, 30.0, msgitem, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		MenuOperation[playerid] = 0;
	 	return 1;
	}
	return 1;
}

stock accept_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != ACCEPT_DIALOG) return 1;
	new msgitem[256+1];
	if(!response)
	{
		iOfferTime[Offer[playerid]] = GetTickCount();
		iOfferTime[playerid] = GetTickCount();
		Offer[playerid] = MAX_PLAYERS-1;

		DrugPrice[playerid] = 0;
		DrugGram[playerid] = 0;

		GunPrice[playerid] = 0;
		OfferWeapon[playerid] = 0;
		OfferAmmo[playerid] = 0;
		GunMat[playerid] = 0;

		CarPrice[playerid] = 0;
		MarryWitnessOffer[playerid] = MAX_PLAYERS-1;
		if(ProposeOffer[playerid] < MAX_PLAYERS-1) MarryWitness[ProposeOffer[playerid]] = MAX_PLAYERS-1;
		ProposeOffer[playerid] = MAX_PLAYERS-1;
		if(Offer[playerid] < MAX_PLAYERS-1) gGotOrder[Offer[playerid]] = MAX_PLAYERS-1;
		TicketMoney[playerid] = 0;
		PaperPrice[playerid] = 0;

		format(msgitem, sizeof(msgitem), "%s отказался от предложенной услуги !!", PlayerName(playerid));
		ProxDetector(playerid, 30.0, msgitem, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		MenuOperation[playerid] = 0;
	 	return 1;
	}
	new giveplayerid;
	//else if(!strcmp(x_job, "drugs", true))
	if(MenuOperation[playerid] == 6)//для наркодилеров
	{   //&& IsPlayerInRangeOfPoint(playerid, 2.0, -2026.7584,-114.3740,1035.1719)
	    if(Offer[playerid] >= MAX_PLAYERS-1 || !IsPlayerConnected(Offer[playerid]))
	    {
	        SendClientMessage(playerid, COLOR_GREY, "   Нет предложившего Вам Наркотики !");
	        return 1;
	    }
        if(GetPlayerMoneyH(playerid) < DrugPrice[playerid])
		{
			format(msgitem, sizeof(msgitem), "   Вы не можете оплатить столько Наркотиков на сумму $%d!", DrugPrice[playerid]);
			SendClientMessage(playerid, COLOR_GREY, msgitem);
		    return 1;
		}
        if(PlayerInfo[playerid][pDrugs] > 6)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Вы полностью загружены Наркотиками, используйте их для начала (USE: /items)!");
		    return 1;
		}
		if(!IsPlayerInRangeOfPlayer(8.0, playerid, Offer[playerid])
			|| spectateid[playerid] != MAX_PLAYERS-1 || spectateid[Offer[playerid]] != MAX_PLAYERS-1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не рядом с Вами !");
			return 1;
		}
		if(	PlayerInfo[Offer[playerid]][pMember] >= TEAM_GROVE &&
			PlayerInfo[Offer[playerid]][pMember] <= TEAM_MAFIA)
		{
			//PlaySoundForPlayer(Offer[playerid], SOUND_PART_MISSION_COMPLETE);//Успех в миссии (один пункт завершён)
			format(msgitem, sizeof(msgitem), "~r~%d$", DrugPrice[playerid]);
			GameTextForPlayerEx(Offer[playerid], msgitem, 1000, 1);
			FamilyInfo[ PlayerInfo[Offer[playerid]][pMember] ][fBank] += DrugPrice[playerid]/2;
			GivePlayerMoneyB(fjob+PlayerInfo[Offer[playerid]][pJob], Offer[playerid], DrugPrice[playerid]/2);
			//SaveFamiliesSQL(PlayerName(playerid));//слишко часто вызывается
		}
		else if(PlayerInfo[Offer[playerid]][pMember] == LCN)
		{
			//PlaySoundForPlayer(Offer[playerid], SOUND_PART_MISSION_COMPLETE);
			format(msgitem, sizeof(msgitem), "~r~%d$", DrugPrice[playerid]);
			GameTextForPlayerEx(Offer[playerid], msgitem, 1000, 1);
			FamilyInfo[ PlayerInfo[Offer[playerid]][pMember] ][fBank] += DrugPrice[playerid]/2;
			GivePlayerMoneyB(fjob+PlayerInfo[Offer[playerid]][pJob], Offer[playerid], DrugPrice[playerid]/2);
			//SaveFamiliesSQL(PlayerName(playerid));//слишко часто вызывается
		}
		else if(PlayerInfo[Offer[playerid]][pMember] == Yakuza)
		{
			//PlaySoundForPlayer(Offer[playerid], SOUND_PART_MISSION_COMPLETE);
			format(msgitem, sizeof(msgitem), "~r~%d$", DrugPrice[playerid]);
			GameTextForPlayerEx(Offer[playerid], msgitem, 1000, 1);
			FamilyInfo[ 0+PlayerInfo[Offer[playerid]][pMember] ][fBank] += DrugPrice[playerid]/2;
			GivePlayerMoneyB(fjob+PlayerInfo[Offer[playerid]][pJob], Offer[playerid], DrugPrice[playerid]/2);
			//SaveFamiliesSQL(PlayerName(playerid));//слишко часто вызывается
		}
		else
		{
			GivePlayerMoneyB(fjob+PlayerInfo[Offer[playerid]][pJob], Offer[playerid], DrugPrice[playerid]);
		}
		PlayerInfo[Offer[playerid]][pDrugsSkill] ++;
		GivePlayerMoneyH(fjob+PlayerInfo[Offer[playerid]][pJob], playerid, -DrugPrice[playerid] );
		PlayerInfo[playerid][pDrugs] += DrugGram[playerid];
		PlayerInfo[Offer[playerid]][pDrugs] -= DrugGram[playerid];

		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
       		if(WantedPoints[playerid] > 6) break;
			if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
			if(i == playerid) continue;
			if(spectateid[i] != MAX_PLAYERS-1) continue;
		    if(!IsACop(i)) continue;
		    if(!gOnDuty[i]) continue;
		    //if( !IsPlayerInAnyVehicle(i) ) continue;
			//if( !IsInCopCar(nCarID[i]) ) continue;
			//if(nCarID[playerid] == nCarID[i]) continue;//если игрок не сидит в машине полицмена
			if(	!IsPlayerInRangeOfPlayer(60.0, playerid, i) ) continue;
       	    WantedPoints[playerid] += 6;
			SetPlayerCriminal(FBI, playerid, i, " Незаконный оборот наркотических средств");
			SendTeamMessage(FBI, COLOR_DARKTURQUOISE, "   USE: /pun [328] [1-3] [playerid/PartOfName]");
       	    break;
   		}
		format(msgitem, sizeof(msgitem), "* Вы купили %d грамм на сумму $%d у НаркоДилера %s (USE: /items).",DrugGram[playerid],DrugPrice[playerid],PlayerName(Offer[playerid]));
		SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
		format(msgitem, sizeof(msgitem), "* %s купил у вас %d грамм. Вам перечислено на счёт в банке $%d. Остальная сумма переведена в общак. ",
			PlayerName(playerid), DrugGram[playerid], DrugPrice[playerid]/2);
		SendClientMessage(Offer[playerid], COLOR_LIGHTBLUE, msgitem);
		if(PlayerInfo[Offer[playerid]][pDrugsSkill] == 250)
		{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваш Навык НаркоДилера теперь Уровня 2, Вы можете купить больше Граммов и Дешевле."); }
		else if(PlayerInfo[Offer[playerid]][pDrugsSkill] == 500)
		{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваш Навык НаркоДилера теперь Уровня 3, Вы можете купить больше Граммов и Дешевле."); }
		else if(PlayerInfo[Offer[playerid]][pDrugsSkill] == 1000)
		{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваш Навык НаркоДилера теперь Уровня 4, Вы можете купить больше Граммов и Дешевле."); }
		else if(PlayerInfo[Offer[playerid]][pDrugsSkill] == 2000)
		{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваш Навык НаркоДилера теперь Уровня 5, Вы можете купить больше Граммов и Дешевле."); }
		Offer[playerid] = MAX_PLAYERS-1;
		DrugPrice[playerid] = 0;
		DrugGram[playerid] = 0;
		MenuOperation[playerid] = 0;
	}
	else if(MenuOperation[playerid] == 7)
	{
	    if(Offer[playerid] >= MAX_PLAYERS-1)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Нет предложившего Вам Разговор в Прямой Эфире!");
		    return 1;
		}
        if(!IsPlayerConnected(Offer[playerid])) return 1;
		if(!IsPlayerInRangeOfPlayer(8.0, playerid, Offer[playerid])
			|| spectateid[playerid] != MAX_PLAYERS-1 || spectateid[Offer[playerid]] != MAX_PLAYERS-1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не рядом с Вами !");
			return 1;
		}
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "Используйте F6, чтобы разговаривать в эфире. Не Забудьте выключить предыдущий чат (USE: /0).");
	    //SendClientMessage(playerid, COLOR_GREY, "   Вы обездвижены пока находитесь в Прямом Эфире.");
	    SendClientMessage(Offer[playerid], COLOR_LIGHTBLUE, "Игрок принял ваше предложение!");
		SendClientMessage(Offer[playerid], COLOR_LIGHTBLUE, "Используйте F6, чтобы разговаривать в эфире. Не Забудьте выключить предыдущий чат (USE: /0).");
		//SendClientMessage(Offer[playerid], COLOR_GREY, "   Вы обездвижены пока ведёте Разговор в Прямом Эфире (используйте /live снова).");
		//TogglePlayerControllableEx(playerid, 0);//обездвиживает
		TalkingLive[playerid] = Offer[playerid];
		TalkingLive[Offer[playerid]] = playerid;
		Offer[playerid] = MAX_PLAYERS-1;
		MenuOperation[playerid] = 0;
	}
	else if(MenuOperation[playerid] == 11)//для оружейников STEP4
	//else if(!strcmp(x_job, "sellgun", true))//для оружейников
	{
	    if(Offer[playerid] >= MAX_PLAYERS-1 || !IsPlayerConnected(Offer[playerid]))
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Нет предложившего Вам Оружие!");
			return 1;
		}
		if(GetPlayerMoneyH(playerid) < GunPrice[playerid])
		{
			format(msgitem, sizeof(msgitem), "   Вы не можете позволить себе оплатить это Оружие на сумму $%d!", GunPrice[playerid]);
			SendClientMessage(playerid, COLOR_GREY, msgitem);
			return 1;
		}
		new payout = GunMat[playerid];
		new price = GunPrice[playerid];
		if(!IsPlayerInRangeOfPlayer(8.0, playerid, Offer[playerid])
			|| spectateid[playerid] != MAX_PLAYERS-1 || spectateid[Offer[playerid]] != MAX_PLAYERS-1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не рядом с Вами !");
			return 1;
		}
		GivePlayerWeaponEx(playerid, OfferWeapon[playerid], OfferAmmo[playerid]);
		if(OfferWeapon[playerid] == 39) GivePlayerWeaponEx(playerid, 40, 1);
		GivePlayerMoneyH(fjob+PlayerInfo[Offer[playerid]][pJob], playerid, -price);
		format(msgitem, sizeof(msgitem), "   Bы получили %s[%d] с %d патронам(и) от %s'а за {33AA33}$%d",
			WeaponName(OfferWeapon[playerid]), OfferWeapon[playerid], OfferAmmo[playerid],
			PlayerName(Offer[playerid]), price);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
	    if(PlayerInfo[playerid][pMiserPerk] > 0)
    	{
			payout -= 5*GunMat[playerid]*(PlayerInfo[playerid][pMiserPerk]+1)/100;
			price -= 5*GunPrice[playerid]*(PlayerInfo[playerid][pMiserPerk]+1)/100;
		}
		if(	PlayerInfo[Offer[playerid]][pMember] >= TEAM_GROVE &&
			PlayerInfo[Offer[playerid]][pMember] <= TEAM_MAFIA)
		{
			//PlaySoundForPlayer(Offer[playerid], SOUND_PART_MISSION_COMPLETE);
			format(msgitem, sizeof(msgitem), "~r~%d$", price);
			GameTextForPlayerEx(Offer[playerid], msgitem, 1000, 1);
			FamilyInfo[ PlayerInfo[ Offer[playerid] ][pMember] ][fBank] += price/2;
			GivePlayerMoneyB(fjob+PlayerInfo[Offer[playerid]][pJob], Offer[playerid], price/2);
			PlayerInfo[Offer[playerid]][pMats] -= payout/2;
			format(msgitem, sizeof(msgitem), "   Bы передали %s'у %s с %d патронам(и), потратив %d Материалов.",
				PlayerName(playerid), WeaponName(OfferWeapon[playerid]), OfferAmmo[playerid], payout/2);
			SendClientMessage(Offer[playerid], COLOR_LIGHTBLUE, msgitem);
			//SaveFamiliesSQL(PlayerName(playerid));//слишком часто вызывается
		}
		else if(PlayerInfo[Offer[playerid]][pMember] == LCN)
		{
			//PlaySoundForPlayer(Offer[playerid], SOUND_PART_MISSION_COMPLETE);
			format(msgitem, sizeof(msgitem), "~r~%d$", price);
			GameTextForPlayerEx(Offer[playerid], msgitem, 1000, 1);
			FamilyInfo[LCN][fBank] += price/2;
			if(Offer[playerid] != playerid)  GivePlayerMoneyB(fjob+PlayerInfo[Offer[playerid]][pJob], Offer[playerid], price/2);
			PlayerInfo[Offer[playerid]][pMats] -= payout/2;
			format(msgitem, sizeof(msgitem), "   Bы передали %s'у %s с %d патронам(и), потратив %d Материалов.",
				PlayerName(playerid), WeaponName(OfferWeapon[playerid]), OfferAmmo[playerid], payout/2);
			SendClientMessage(Offer[playerid], COLOR_LIGHTBLUE, msgitem);
			//IncreaseRank(Offer[playerid], 1);//будут сами себе бпродовать оружие
			//SaveFamiliesSQL(PlayerName(playerid));//слишком часто вызывается
		}
		else if(PlayerInfo[Offer[playerid]][pMember] == Yakuza)
		{
			//PlaySoundForPlayer(Offer[playerid], SOUND_PART_MISSION_COMPLETE);
			format(msgitem, sizeof(msgitem), "~r~%d$", GunPrice[playerid]);
			GameTextForPlayerEx(Offer[playerid], msgitem, 1000, 1);
			FamilyInfo[Yakuza][fBank] += GunPrice[playerid]/2;
			if(Offer[playerid] != playerid) GivePlayerMoneyB(fjob+PlayerInfo[Offer[playerid]][pJob], Offer[playerid], GunPrice[playerid]/2);
			PlayerInfo[Offer[playerid]][pMats] -= payout/2;
			format(msgitem, sizeof(msgitem), "   Bы передали %s'у %s[%d] с %d патронам(и), потратив %d Материалов.",
				PlayerName(playerid), WeaponName(OfferWeapon[playerid]), OfferWeapon[playerid], OfferAmmo[playerid], payout/2);
			SendClientMessage(Offer[playerid], COLOR_LIGHTBLUE, msgitem);
			//SaveFamiliesSQL(PlayerName(playerid));//слишком часто вызывается
		}
		else
		{
			if(Offer[playerid] != playerid) GivePlayerMoneyB(fjob+PlayerInfo[Offer[playerid]][pJob], Offer[playerid], price);
			PlayerInfo[Offer[playerid]][pMats] -= payout;
			format(msgitem, sizeof(msgitem), "   Bы передали %s'у %s[%d] с %d патронам(и), потратив %d Материалов.",
				PlayerName(playerid), WeaponName(OfferWeapon[playerid]), OfferWeapon[playerid], OfferAmmo[playerid], payout);
			SendClientMessage(Offer[playerid], COLOR_LIGHTBLUE, msgitem);
		}
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
       		if(WantedPoints[playerid] > 6) break;
			if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
			if(i == playerid) continue;
			if(spectateid[i] != MAX_PLAYERS-1) continue;
		    if(!IsACop(i)) continue;
		    if(!gOnDuty[i]) continue;
		    //if( !IsPlayerInAnyVehicle(i) ) continue;
			//if( !IsInCopCar(nCarID[i]) ) continue;
			//if(nCarID[playerid] == nCarID[i]) continue;//если игрок не сидит в машине полицмена
			if(	!IsPlayerInRangeOfPlayer(60.0, playerid, i) ) continue;
       	    WantedPoints[playerid] += 6;
			SetPlayerCriminal(FBI, playerid, i, " Незаконные действия в отношении огнестрельного оружия");
			SendTeamMessage(FBI, COLOR_DARKTURQUOISE, "   USE: /pun [295] [1-3] [playerid/PartOfName]");
       	    break;
   		}
		format(msgitem, sizeof(msgitem), "* %s изготовил %s[%d] из %d Материалов, и передал его %s'у.",
			PlayerName(Offer[playerid]), WeaponName(OfferWeapon[playerid]), OfferWeapon[playerid], payout, PlayerName(playerid));
		ProxDetector(Offer[playerid], 30.0,  msgitem, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		if(Offer[playerid] != playerid)
		{
			PlayerInfo[Offer[playerid]][pGunSkill] ++;
			if(PlayerInfo[Offer[playerid]][pGunSkill] == 50)
			{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваш Навык Оружейника теперь Уровня 2, Вы можете купить больше Пакетов и Дешевле."); }
			else if(PlayerInfo[Offer[playerid]][pGunSkill] == 100)
			{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваш Навык Оружейника теперь Уровня 3, Вы можете купить больше Пакетов и Дешевле."); }
			else if(PlayerInfo[Offer[playerid]][pGunSkill] == 200)
			{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваш Навык Оружейника теперь Уровня 4, Вы можете купить больше Пакетов и Дешевле."); }
			else if(PlayerInfo[Offer[playerid]][pGunSkill] == 400)
			{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваш Навык Оружейника теперь Уровня 5, Вы можете купить больше Пакетов и Дешевле."); }
		}
		Offer[playerid] = MAX_PLAYERS-1;
		GunPrice[playerid] = 0;
		OfferWeapon[playerid] = 0;
		OfferAmmo[playerid] = 0;
		GunMat[playerid] = 0;
		MenuOperation[playerid] = 0;
	}
	else if(MenuOperation[playerid] == 12)//покупка авто
       //else if(!strcmp(x_job, "car", true))//для автодилеров
	{
	    if(Offer[playerid] >= MAX_PLAYERS-1 || !IsPlayerConnected(Offer[playerid]))
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Нет предложившего Вам Авто!");
			return 1;
		}
		if(CarModel[playerid] < 400)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Не правильно указана модель!");
			return 1;
		}
		if(CarPrice[playerid] <= 0)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Не правильно указана стоимость!");
			return 1;
		}
		if(SBizInfo[5][sbProducts] <= 0 && !gTutorial[playerid] && !gRealWar)
		{
			GameTextForPlayerEx(playerid, "~r~Out Of Stock in ~p~Car Delivery", 5000, 1);
	    	PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
			return 1;
		}
		if(GetPlayerMoneyH(playerid) < CarPrice[playerid])
		{
			format(msgitem, sizeof(msgitem), "   Вы не можете позволить себе оплатить этот транспорт ценой $%d!", CarPrice[playerid]);
			SendClientMessage(playerid, COLOR_GREY, msgitem);
			CarPrice[playerid] = 0;
			return 1;
		}
		new car;
		for(new limit = 0; limit < 3; limit++)
		{
			if(MyCar[playerid][limit] != 0) car++;
		}
 		new bouse;
		for(new limit = 0; limit < 10; limit++)
		{
			if(MyBizz[playerid][limit] != NOT_KEY) bouse ++;
		}
 		new sbouse;
		for(new limit = 0; limit < 20; limit++)
		{
			if(MyCompany[playerid][limit] != NOT_KEY) sbouse ++;
		}
		if(PlayerInfo[playerid][pHouse] == NOT_KEY && !bouse && !sbouse && car >= 1)
	    {
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете позволить себе покупку более одного транспорта, при отсутствии дома или бизнеса!");
			CarPrice[playerid] = 0;
			return 1;
		}
		if(PlayerInfo[playerid][pHouse] == NOT_KEY && car >= 2)
	    {
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете позволить себе покупку более двух транспортных средств, при отсутствии дома!");
			CarPrice[playerid] = 0;
			return 1;
		}
		new MyCarID;
   		if(VehicleArray[CarModel[playerid]-400][Category] == Airplane )
		{
			//new vid;
			//foreachex(StreamedVehicle[playerid], vid)
			//for(new vid = 1; vid<=GetMaxVehicles; vid++)
			new vid = 1;
			//каждая ячейка массива должна быть ссылкой на индекс следующей ячейки
			for(new v=0; v!=-1; v=StreamedVehicle[playerid][v]) {
				if(StreamedVehicle[playerid][v] == -1) continue;
				vid = StreamedVehicle[playerid][v];
				if( IsVehicleInRangeOfPoint(vid, 10.0, 368.3396,2498.1306,16.4006)
					&& VehInfo[vid][cVirt] == 0)
				{
					CarModel[playerid] = 0;
					CarColor1[playerid] = -1;
					CarColor2[playerid] = -1;
			        Offer[playerid] = MAX_PLAYERS-1;
					CarPrice[playerid] = 0;
					MenuOperation[playerid] = 0;
					SendClientMessage(playerid, COLOR_GREY, "   Нет места для установки самолёта !");
					return 1;
				}
			}
			MyCarID = CreateStaticVehicleEx(playerid, CarModel[playerid], 368.3396,2498.1306,16.4006,88.6698, CarColor1[playerid], CarColor2[playerid], -1);
		}
     	else if(VehicleArray[CarModel[playerid]-400][Category] == Helicopters )
		{
			//new vid;
			//foreachex(StreamedVehicle[playerid], vid)
			//for(new vid = 1; vid<=GetMaxVehicles; vid++)
			new vid = 1;
			for(new v=0; v!=-1; v=StreamedVehicle[playerid][v])	{
				if(StreamedVehicle[playerid][v] == -1) continue;
				vid = StreamedVehicle[playerid][v];
				if( IsVehicleInRangeOfPoint(vid, 10.0, 365.3851,2537.2632,18.2890)
					&& VehInfo[vid][cVirt] == 0)
				{
					CarModel[playerid] = 0;
					CarColor1[playerid] = -1;
					CarColor2[playerid] = -1;
			        Offer[playerid] = MAX_PLAYERS-1;
					CarPrice[playerid] = 0;
					MenuOperation[playerid] = 0;
					SendClientMessage(playerid, COLOR_GREY, "   Нет места для установки вертолёта !");
					return 1;
				}
			}
			MyCarID = CreateStaticVehicleEx(playerid, CarModel[playerid], 365.3851,2537.2632,18.2890,357.5208, CarColor1[playerid], CarColor2[playerid], -1);
		}
     	else if(VehicleArray[CarModel[playerid]-400][Category] == Boats)
		{
			//new vid;
			//foreachex(StreamedVehicle[playerid], vid)
			//for(new vid = 1; vid<=GetMaxVehicles; vid++)
			/*new vid = 1;
			for(new v=0; v!=-1; v=StreamedVehicle[playerid][v])	{
				if(StreamedVehicle[playerid][v] == -1) continue;
				vid = StreamedVehicle[playerid][v];
				if( IsVehicleInRangeOfPoint(vid, 2.5, -2202.8044,2418.8037,0.1991)
					&& VehInfo[vid][cVirt] == 0)
				{
					CarModel[playerid] = 0;
					CarColor1[playerid] = -1;
					CarColor2[playerid] = -1;
			        Offer[playerid] = MAX_PLAYERS-1;
					CarPrice[playerid] = 0;
					MenuOperation[playerid] = 0;
					SendClientMessage(playerid, COLOR_GREY, "   Нет места для установки лодки !");
					return 1;
				}
			}*/
			MyCarID = CreateStaticVehicleEx(playerid, CarModel[playerid], -2202.8044,2418.8037,0.1991,43.8098, CarColor1[playerid], CarColor2[playerid], -1);
		}
    	//else if( IsPlayerInRangeOfPoint(Offer[playerid],30.0,-1658.0516,1206.8474,7.2500) )
     	else //if( IsPlayerInArea(Offer[playerid], specialzone[8]) )
		{
			//new vid;
			//foreachex(StreamedVehicle[playerid], vid)
			//for(new vid = 1; vid<=GetMaxVehicles; vid++)
			/*new vid = 1;
			for(new v=0; v!=-1; v=StreamedVehicle[playerid][v])	{
				if(StreamedVehicle[playerid][v] == -1) continue;
				vid = StreamedVehicle[playerid][v];
				new Float:vX,Float:vY,Float:vZ;
				GetVehicleModelInfo(CarModel[playerid], VEHICLE_MODEL_INFO_SIZE, vX, vY, vZ);
				//format(strcmd, sizeof(strcmd), "GetVehInfo(%d, %.4f, %.4f, %.4f)", vehicleid, vX, vY, vZ);
				//SendClientMessage(playerid, COLOR_GRAD9, strcmd);
				if( IsVehicleInRangeOfPoint(vid, vY, -1634.3323,1203.5831,6.9067)//IsVehicleInRangeOfPoint(vid, vY/2, -1663.3733,1215.6606,8.3688)
					&& VehInfo[vid][cVirt] == 0)
				{
					CarModel[playerid] = 0;
					CarColor1[playerid] = -1;
					CarColor2[playerid] = -1;
			        Offer[playerid] = MAX_PLAYERS-1;
					CarPrice[playerid] = 0;
					MenuOperation[playerid] = 0;
					SendClientMessage(playerid, COLOR_GREY, "   Нет места для установки транспорта !");
					return 1;
				}
			}*/
			//MyCarID = CreateStaticVehicleEx(playerid, CarModel[playerid], -1634.3323,1203.5831,6.9067,224.4404, CarColor1[playerid], CarColor2[playerid], -1);
			MyCarID = CreateStaticVehicleEx(playerid, CarModel[playerid], 723.8723,-1502.8466,-0.4625,188.3220, CarColor1[playerid], CarColor2[playerid], -1);
		}
		if(!IsPlayerInRangeOfPlayer(8.0, playerid, Offer[playerid])
			|| spectateid[playerid] != MAX_PLAYERS-1 || spectateid[Offer[playerid]] != MAX_PLAYERS-1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Автодилер не рядом с Вами !");
			return 1;
		}
		new points = 5;
        if(playerid != Offer[playerid])
        {
			PlayerInfo[Offer[playerid]][pCarSkill] ++;
			if(PlayerInfo[Offer[playerid]][pCarSkill] == 50)
			{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваш Навык АвтоДилера теперь Уровня 2, Игроки, которые покупают Автомобили у Вас могут вызывать их 2 раза."); }
			else if(PlayerInfo[Offer[playerid]][pCarSkill] == 100)
			{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваш Навык АвтоДилера теперь Уровня 3, Игроки, которые покупают Автомобили у Вас могут вызывать их 3 раза."); }
			else if(PlayerInfo[Offer[playerid]][pCarSkill] == 200)
			{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваш Навык АвтоДилера теперь Уровня 4, Игроки, которые покупают Автомобили у Вас могут вызывать их 4 раза."); }
			else if(PlayerInfo[Offer[playerid]][pCarSkill] == 400)
			{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваш Навык АвтоДилера теперь Уровня 5, Игроки, которые покупают Автомобили у Вас могут вызывать их 5 раз."); }
			new level = PlayerInfo[Offer[playerid]][pCarSkill];
			if(level < 50) { points = 5; }
			else if(level >= 50 && level < 100) { points = 6; }
			else if(level >= 100 && level < 200) { points = 7; }
			else if(level >= 200 && level < 400) { points = 8; }
			else if(level >= 400) { points = 9; }
			new money = CarPrice[playerid] - VehicleArray[CarModel[playerid]-400][Virtual_Price];
			GivePlayerMoneyH(fjob+PlayerInfo[Offer[playerid]][pJob], Offer[playerid], money);
			format(msgitem, sizeof(msgitem), "* Вам %s оплатил  Автомобиль и Страховку стоимостью $%d, игрок может использовать /callcar %d раз.",
				PlayerName(playerid),CarPrice[playerid],points);
			SendClientMessage(Offer[playerid], COLOR_LIGHTBLUE, msgitem);
		}

		if(BizInfo[0][bTill]+CarPrice[playerid] < 2147480000) { BizInfo[0][bTill] += CarPrice[playerid]; BizInfo[0][bExport] += CarPrice[playerid]; }
		VehInfo[MyCarID][cInsur] = points;
		//GivePlayerMoneyH(1, playerid, -CarPrice[playerid]);//деньги снимаются в CreateStaticVehicleEx
		format(msgitem, sizeof(msgitem), "* Вы купили Автомобиль на сумму {33AA33}$%d{0080FF}, у Автомобильного Дилера {FFFFFF}%s. {C0C0C0}(Вы можете использовать /callcar %d раз).",
			CarPrice[playerid],PlayerName(Offer[playerid]),points);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
		SendClientMessage(playerid, COLOR_MAROON, "Откройте автомобиль командой /lock или клавишами "#SNEAK_ABOUT"+"#PED_SPRINT"!");
		SendClientMessage(playerid, COLOR_MAROON, "Отправляйтесь в магазине 24/7 и купите 'Vehicle Lock'");
		SendClientMessage(playerid, COLOR_MAROON, "Запаркуйте ваш транспорт на стоянке командой /parking или клавишей "#VEHICLE_TURRETLEFT")!");
		SendClientMessage(playerid, COLOR_GREY, "/carhelp - список команд по тачкам");
		SendClientMessage(playerid, COLOR_GREY, "/lock("#SNEAK_ABOUT"+"#PED_SPRINT") - открыть/закрыть автомобиль");
		SendClientMessage(playerid, COLOR_GREY, "/engine(~k~~TOGGLE_SUBMISSIONS~) - завести/заглушить двигатель");
		SendClientMessage(playerid, COLOR_GREY, "/parking("#VEHICLE_TURRETLEFT") - запарковать.");
		SendClientMessage(playerid, COLOR_GREY, "/unparking("#VEHICLE_TURRETRIGHT") - распарковать.");
		CarModel[playerid] = 0;
		CarColor1[playerid] = -1;
		CarColor2[playerid] = -1;
        Offer[playerid] = MAX_PLAYERS-1;
		CarPrice[playerid] = 0;
		MenuOperation[playerid] = 0;
	}
	else if(MenuOperation[playerid] == 13)// accept
	//else if(!strcmp(x_job, "secundans", true))
	{	//для боксёров начало STEP2
	    if(Offer[playerid] >= MAX_PLAYERS-1)
	    {
		    SendClientMessage(playerid, COLOR_GREY, "   Вам не поступило предложение на Бой !");
		    return 1;
		}
        if(!IsPlayerConnected(Offer[playerid]))
        {
		    SendClientMessage(playerid, COLOR_GREY, "   Нет секунданта !");
			return 1;//или бросившего Вам Вызов на Бой
		}
        if(	!IsPlayerInRangeOfPoint(playerid, 15.0, 764.9067,6.4177,1000.7171) &&
			!IsPlayerInRangeOfPoint(playerid, 15.0, 766.7358,-68.5967,1001.5692))
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не в Спортивном Зале!");
            return 1;
        }
		if(gPlayerBoxing[playerid])
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы уже Дерётесь !");
            return 1;
        }
		new points;
		if(BoxerBlue == MAX_PLAYERS-1 && !gPlayerBoxing[playerid])
		{
			BoxerBlue = playerid;
			gPlayerBoxing[playerid] = 1;//игрок на ринге
			SetPlayerSkinEx(playerid, 81);
	        if(IsPlayerInRangeOfPoint(Offer[playerid],15.0,764.9067,6.4177,1000.7171))
	        {
				SetPlayerPosEx(playerid, 762.9852,2.4439,1001.6942, 131.8632);
			}
			else if(IsPlayerInRangeOfPoint(Offer[playerid],15.0,766.7358,-68.5967,1001.5692))
			{
				SetPlayerPosEx(playerid, 764.4096,-66.4512,1001.6692, 225.7098);
			}
			strmid(titleblue, GetBoxerRanks(BoxerBlue, points), 0, 20, 20);
		    format(msgitem, sizeof(msgitem), "Bookmaker %s: В синем углу и в синих трусах %s %s. \
											Провёл %d Боев из них %d Побед и %d Поражений.",
											PlayerName(Offer[playerid]),
											titleblue,
											PlayerName(playerid),
											PlayerInfo[playerid][pWins]+PlayerInfo[playerid][pLoses],
											PlayerInfo[playerid][pWins],
											PlayerInfo[playerid][pLoses]);
			OOCNews(COLOR_LIGHTORANGE,msgitem);//OOC(COLOR_WHITE,msgitem);
		}
		else if(BoxerRed == MAX_PLAYERS-1 && !gPlayerBoxing[playerid])
		{//для боксёров начало STEP2
			BoxerRed = playerid;
			gPlayerBoxing[playerid] = 1;//игрок на ринге
			SetPlayerSkinEx(playerid, 80);
	        if(IsPlayerInRangeOfPoint(Offer[playerid],15.0,764.9067,6.4177,1000.7171))
	        {
				SetPlayerPosEx(playerid, 758.7064,-1.8038,1001.5942, 313.1165);
			}
			else if(IsPlayerInRangeOfPoint(Offer[playerid],15.0,766.7358,-68.5967,1001.5692))
			{
				SetPlayerPosEx(playerid, 768.9097,-70.9200,1001.5692, 45.3064);
			}
			strmid(titlered, GetBoxerRanks(BoxerRed, points), 0, 20, 20);
		    format(msgitem, sizeof(msgitem), "Bookmaker %s: В красном углу и в красных трусах %s %s.\
											Провёл %d Боев из них %d Побед и %d Поражений.",
											PlayerName(Offer[playerid]),
											titlered, PlayerName(playerid),
											PlayerInfo[playerid][pWins]+PlayerInfo[playerid][pLoses],
											PlayerInfo[playerid][pWins], PlayerInfo[playerid][pLoses]);
			OOCNews(COLOR_LIGHTORANGE,msgitem);//OOC(COLOR_WHITE,msgitem);
		}
		//SetPlayerHealthEx(playerid, points);
		ResetPlayerWeaponsEx(playerid);
		PlayerInfo[playerid][pDrugs] = 0;
		TogglePlayerControllableEx(playerid, 0);//обездвиживает
		GameTextForPlayerEx(playerid, "~r~Waiting", 3000, 1);
		format(msgitem, sizeof(msgitem), "* Вы приняли предложение Секунданта %s, и будете бороться со %d очками Здоровья. Оружие и наркотики конфискованы.",
			PlayerName(Offer[playerid]), points);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
		format(msgitem, sizeof(msgitem), "* %s принял ваше Предложение на Бой.", PlayerName(playerid));
		SendClientMessage(Offer[playerid], COLOR_LIGHTBLUE, msgitem);
		MenuOperation[playerid] = 0;
	}
	else if(MenuOperation[playerid] == 14)//MenuOperation[adminid] = 14;
	{
		giveplayerid = Offer[playerid];
   	 	MakeLeader(playerid, giveplayerid, PlayerName(giveplayerid), GetPVarInt(playerid, "ProposedFamily"));
	}

	else if(MenuOperation[playerid] == 18)
	//else if(!strcmp(x_job, "washmoney", true))
	{   //если глава семьи подтвердил отмытие
	    if(Offer[playerid] >= MAX_PLAYERS-1)
	    {
	        SendClientMessage(playerid, COLOR_GREY, "   Вам не пришло предложения на Перевод денег !");
	        return 1;
	    }
        if(!IsPlayerConnected(Offer[playerid]))
	    {
	        SendClientMessage(playerid, COLOR_GREY, "   Нет предложившего Вам Перевод денег !");
			return 1;
	    }
		if(!IsPlayerInRangeOfPlayer(8.0, playerid, Offer[playerid])
			|| spectateid[playerid] != MAX_PLAYERS-1 || spectateid[Offer[playerid]] != MAX_PLAYERS-1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не рядом с Вами !");
			return 1;
		}
		new amount = FamilyInfo[ PlayerInfo[Offer[playerid]][pMember] ][fBank]*10/100;//10 процентов от суммы
		GivePlayerMoneyB(ffamily+PlayerInfo[Offer[playerid]][pMember], Offer[playerid], FamilyInfo[ PlayerInfo[Offer[playerid]][pMember] ][fBank]-amount );
		if(PlayerInfo[playerid][pLeader] == LCN)
		{   // && PlayerInfo[playerid][pRank] >= 11
			PlaySoundForPlayer(playerid, SOUND_PART_MISSION_COMPLETE);
			format(msgitem, sizeof(msgitem), "~r~%d$", amount);
			GameTextForPlayerEx(playerid, msgitem, 1000, 1);
			FamilyInfo[LCN][fBank] += amount;
		}
		else if(PlayerInfo[playerid][pLeader] == Yakuza)
		{   // && PlayerInfo[playerid][pRank] >= 11
			PlaySoundForPlayer(playerid, SOUND_PART_MISSION_COMPLETE);
			format(msgitem, sizeof(msgitem), "~r~%d$", amount);
			GameTextForPlayerEx(playerid, msgitem, 1000, 1);
			FamilyInfo[Yakuza][fBank] += amount;
		}
		FamilyInfo[ PlayerInfo[Offer[playerid]][pMember] ][fBank] = 0;
		SaveFamiliesSQL(PlayerName(playerid));//для отката
		format(msgitem, sizeof(msgitem), "   Bы приняли предложение %s'а по отмытию денежной суммы {33AA33}$%d.", PlayerName(Offer[playerid]), amount);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
		format(msgitem, sizeof(msgitem), "   Bаше предложение одобрено %s'ом. Сумма $%d переведена на ваш счёт.", PlayerName(playerid), amount);
		SendClientMessage(Offer[playerid], COLOR_LIGHTBLUE, msgitem);
		Offer[playerid] = MAX_PLAYERS-1;
	}
	else if(MenuOperation[playerid] == 19)
	//else if(!strcmp(x_job, "ticket", true))
	{   //  /accept
	    if(Offer[playerid] >= MAX_PLAYERS-1 || !IsPlayerConnected(Offer[playerid]))
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Нет предложившего Вам Штраф !");
		    return 1;
		}
		if(!IsPlayerInRangeOfPlayer(8.0, playerid, Offer[playerid])
			|| spectateid[playerid] != MAX_PLAYERS-1 || spectateid[Offer[playerid]] != MAX_PLAYERS-1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не рядом с Вами !");
			return 1;
		}
        if(GetPlayerMoneyH(playerid) > TicketMoney[playerid])
        {
			GivePlayerMoneyH(ffamily+PlayerInfo[Offer[playerid]][pMember], playerid, -TicketMoney[playerid]);
		}
        else if(PlayerInfo[playerid][pBank] > TicketMoney[playerid])
        {
			GivePlayerMoneyB(ffamily+PlayerInfo[Offer[playerid]][pMember], playerid, -TicketMoney[playerid]);
		}
        else
        {
            SendClientMessage(Offer[playerid], COLOR_GREY, "   Игрок не может позволить себе оплатить штраф !");
			return 1;
        }
		if(TicketMoney[playerid] > 1000)//для экономики
		{
			IncreaseRank(Offer[playerid], 5);
		}
		PlayerInfo[playerid][pTicket] ++;
		new family = PlayerInfo[Offer[playerid]][pMember];
		FamilyInfo[family][fBank] += TicketMoney[playerid];
		format(msgitem, sizeof(msgitem), "* %s оплатил Штраф %s'у, в размере $%d. Уровень Преступности был %d.",
		PlayerName(playerid), PlayerName(Offer[playerid]), TicketMoney[playerid], LevelToCriminality);//3600
		ProxDetector(playerid, 30.0,  msgitem, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		PlayerInfo[playerid][pArticle] = 0;//убрали статью
		PlayerInfo[playerid][pPart] = 0;//убрали часть
		ClearCrime(playerid, Offer[playerid], TicketMoney[playerid]);
		gGotOrder[Offer[playerid]] = MAX_PLAYERS-1;
		Offer[playerid] = MAX_PLAYERS-1;
		TicketMoney[playerid] = 0;
	}
	else if(MenuOperation[playerid] == 20)
	//else if(!strcmp(x_job, "paper", true))//для газет
	{   // accept
	    if(Offer[playerid] >= MAX_PLAYERS-1 || !IsPlayerConnected(Offer[playerid]))
		{
			SendClientMessage(playerid, COLOR_GREY, "   Нет предложившего Вам Газету !");
		    return 1;
		}
		if(GotPaper[Offer[playerid]])//BringingPaper[Offer[playerid]] > 0
		{
			if(!IsPlayerInRangeOfPlayer(8.0, playerid, Offer[playerid])
				|| spectateid[playerid] != MAX_PLAYERS-1 || spectateid[Offer[playerid]] != MAX_PLAYERS-1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не рядом с Вами !");
				return 1;
			}
		    GivePlayerMoneyH(fjob+PlayerInfo[Offer[playerid]][pJob], playerid, -PaperPrice[playerid]);
		    GivePlayerMoneyB(fjob+PlayerInfo[Offer[playerid]][pJob], Offer[playerid], PaperPrice[playerid]);
			format(msgitem, sizeof(msgitem), "* %s купил вашу Газету.", PlayerName(playerid));
			SendClientMessage(Offer[playerid], COLOR_LIGHTBLUE, msgitem);
			format(msgitem, sizeof(msgitem), "* Вы взяли Газету у Курьера %s (USE: /read paper, чтобы прочитать).", PlayerName(Offer[playerid]));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);//!!! доработать
			strmid(Paper[playerid][pMaker], Paper[Offer[playerid]][pMaker], 0, strlen(Paper[Offer[playerid]][pMaker]), MAX_PLAYER_NAME);
			strmid(Paper[playerid][pTitle], Paper[Offer[playerid]][pTitle], 0, strlen(Paper[Offer[playerid]][pTitle]), 32);
			strmid(Paper[playerid][pLine1], Paper[Offer[playerid]][pLine1], 0, strlen(Paper[Offer[playerid]][pLine1]), 70);
			strmid(Paper[playerid][pLine2], Paper[Offer[playerid]][pLine2], 0, strlen(Paper[Offer[playerid]][pLine2]), 70);
			strmid(Paper[playerid][pLine3], Paper[Offer[playerid]][pLine3], 0, strlen(Paper[Offer[playerid]][pLine3]), 70);
			strmid(Paper[playerid][pLine4], Paper[Offer[playerid]][pLine4], 0, strlen(Paper[Offer[playerid]][pLine4]), 70);
			strmid(Paper[playerid][pLine5], Paper[Offer[playerid]][pLine5], 0, strlen(Paper[Offer[playerid]][pLine5]), 70);
			strmid(Paper[playerid][pLine6], Paper[Offer[playerid]][pLine6], 0, strlen(Paper[Offer[playerid]][pLine6]), 70);
			strmid(Paper[playerid][pLine7], Paper[Offer[playerid]][pLine7], 0, strlen(Paper[Offer[playerid]][pLine7]), 70);
			strmid(Paper[playerid][pLine8], Paper[Offer[playerid]][pLine8], 0, strlen(Paper[Offer[playerid]][pLine8]), 70);
			strmid(Paper[playerid][pLine9], Paper[Offer[playerid]][pLine9], 0, strlen(Paper[Offer[playerid]][pLine9]), 70);
			strmid(Paper[playerid][pLine10], Paper[Offer[playerid]][pLine10], 0, strlen(Paper[Offer[playerid]][pLine10]), 70);
			strmid(Paper[playerid][pLine11], Paper[Offer[playerid]][pLine11], 0, strlen(Paper[Offer[playerid]][pLine11]), 70);
			//Paper[playerid][pDate] = ;
			GotPaper[playerid] = 1;//получил газету
			//Offer[playerid] = MAX_PLAYERS-1;
			PaperPrice[playerid] = 0;
        }
	}
	else if(MenuOperation[playerid] == 21)//if(!strcmp(cmd, "/free", true))
	//else if(!strcmp(x_job, "lawyer", true))
	//ShowPlayerDialogGap(giveplayerid,18, DIALOG_STYLE_MSGBOX, "Want Lawyer", msgitem, "YES", "NO");
	{   // accept
	    if(Offer[playerid] >= MAX_PLAYERS-1 || !IsPlayerConnected(Offer[playerid]))
		{
			SendClientMessage(playerid, COLOR_GREY, "   Нет предложившего Вам Адвоката !");
		    return 1;
		}
		new money;
		if(playerid == Offer[playerid])
		{
			money = PlayerInfo[playerid][pJailPrice] + DutyFiveMinuts*(PlayerInfo[playerid][pLevel]+PlayerInfo[playerid][pRank])*8;
		}
		else
		{
			money = PlayerInfo[playerid][pJailPrice];
		}
		if(money <= 0) return 1;
        if(GetPlayerMoneyH(playerid) > money)
        {
			GivePlayerMoneyH(fjob+PlayerInfo[Offer[playerid]][pJob], playerid, -money);
		}
        else if(PlayerInfo[playerid][pBank] > money)
        {
			GivePlayerMoneyB(fjob+PlayerInfo[Offer[playerid]][pJob], playerid, -money);
		}
		else
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы не можете позволить себе оплатить залог !");
			return 1;
        }
		PlayerInfo[playerid][pJailTime] = 1;//устанавливаем время на 1 чтобы запустилась SetPlayerUnjail
		if(playerid != Offer[playerid])
		{//если игрок не сам себя освобождает
			GivePlayerMoneyB(fjob+PlayerInfo[Offer[playerid]][pJob], Offer[playerid], money/2);
			FamilyInfo[DoD][fBank] += money/2;
			PlayerInfo[Offer[playerid]][pLawSkill] += 10;
			if(PlayerInfo[Offer[playerid]][pLawSkill] == 50)
			{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваше Навык Юриста теперь Уровня 2, Вы зарабатываете больше Денег и за меньше Время."); }
			else if(PlayerInfo[Offer[playerid]][pLawSkill] == 100)
			{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваше Навык Юриста теперь Уровня 3, Вы зарабатываете больше Денег и за меньше Время."); }
			else if(PlayerInfo[Offer[playerid]][pLawSkill] == 200)
			{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваше Навык Юриста теперь Уровня 4, Вы зарабатываете больше Денег и за меньше Время."); }
			else if(PlayerInfo[Offer[playerid]][pLawSkill] == 400)
			{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваше Навык Юриста теперь Уровня 5, Вы зарабатываете больше Денег и за меньше Время."); }
	    	format(msgitem, sizeof(msgitem), "* Адвокат %s освободил %s's под залог {33AA33}$%d. Теперь он свободен!",
				PlayerName(Offer[playerid]), PlayerName(playerid), money);
		}
		else
		{
	    	format(msgitem, sizeof(msgitem), "* %s вышел на свободу под залог {33AA33}$%d.", PlayerName(playerid), money);
	    	FamilyInfo[DoT][fBank] += money/3;
	    	FamilyInfo[FBI][fBank] += money/3;
			FamilyInfo[DoD][fBank] += money/3;
		}
    	JobNews(COLOR_LIGHTPURPLE, msgitem);
		PlayerInfo[playerid][pJailPrice] = 0;
		gGotOrder[Offer[playerid]] = MAX_PLAYERS-1;//отняли разрешение
		Offer[playerid] = MAX_PLAYERS-1;
	}
	else if(MenuOperation[playerid] == 25)
       //else if(!strcmp(x_job, "car", true))//для автодилеров
	{
	    if(Offer[playerid] >= MAX_PLAYERS-1 || !IsPlayerConnected(Offer[playerid]))
		{
	        Offer[playerid] = MAX_PLAYERS-1;
			CarPrice[playerid] = 0;
			MenuOperation[playerid] = 0;
		    SendClientMessage(playerid, COLOR_GREY, "   Нет предложившего Вам страховку Авто!");
		    return 1;
		}
		if(!IsPlayerInAnyVehicle(playerid) || CurState[playerid] != PLAYER_STATE_DRIVER)
		{
	        Offer[playerid] = MAX_PLAYERS-1;
			CarPrice[playerid] = 0;
			MenuOperation[playerid] = 0;
			SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться за рулём транспортного средства!");
			return 1;
		}
		if(VehInfo[nCarID[playerid]][cType] < 1000)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете страховать государственный транспорт!");
			SendClientMessage(Offer[playerid], COLOR_GREY, "   Вы не можете страховать государственный транспорт!");
			return 1;
		}
		new points;
		PlayerInfo[Offer[playerid]][pCarSkill] ++;
		if(PlayerInfo[Offer[playerid]][pCarSkill] == 50)
		{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваш Навык АвтоДилера теперь Уровня 2, Игроки, которые покупают Автомобили у Вас могут вызывать их 2 раза."); }
		else if(PlayerInfo[Offer[playerid]][pCarSkill] == 100)
		{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваш Навык АвтоДилера теперь Уровня 3, Игроки, которые покупают Автомобили у Вас могут вызывать их 3 раза."); }
		else if(PlayerInfo[Offer[playerid]][pCarSkill] == 200)
		{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваш Навык АвтоДилера теперь Уровня 4, Игроки, которые покупают Автомобили у Вас могут вызывать их 4 раза."); }
		else if(PlayerInfo[Offer[playerid]][pCarSkill] == 400)
		{ SendClientMessage(Offer[playerid], COLOR_YELLOW, "* Ваш Навык АвтоДилера теперь Уровня 5, Игроки, которые покупают Автомобили у Вас могут вызывать их 5 раз."); }
		new level = PlayerInfo[Offer[playerid]][pCarSkill];
		if(level < 50) { points = 1; }
		else if(level >= 50 && level < 100) { points = 2; }
		else if(level >= 100 && level < 200) { points = 3; }
		else if(level >= 200 && level < 400) { points = 4; }
		else if(level >= 400) { points = 5; }
		VehInfo[nCarID[playerid]][cInsur] += points;
		new strtmp[10];
		format(strtmp, sizeof(strtmp), "%d", VehInfo[nCarID[playerid]][cInsur]);
		PlayerTextDrawSetStringEx(playerid, txdInsurances[playerid], strtmp);
		format(msgitem, sizeof(msgitem), "* Вы застраховали %s на сумму $%d, у Автомобильного Дилера %s. (Вы можете использовать /callcar +%d раз из %d).",
			 VehicleArray[nCarModel[playerid]-400][Vehicle_Name], CarPrice[playerid], PlayerName(Offer[playerid]), points, VehInfo[nCarID[playerid]][cInsur]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
		format(msgitem, sizeof(msgitem), "* %s оплатил Вам Страховку %s стоимостью $%d, игрок может использовать /callcar +%d раз.",
			PlayerName(playerid), VehicleArray[nCarModel[playerid]-400][Vehicle_Name], CarPrice[playerid],points);
		SendClientMessage(Offer[playerid], COLOR_LIGHTBLUE, msgitem);
		GivePlayerMoneyB(fjob+PlayerInfo[Offer[playerid]][pJob], Offer[playerid], CarPrice[playerid]);
		GivePlayerMoneyH(fjob+PlayerInfo[Offer[playerid]][pJob], playerid, -CarPrice[playerid]);
		RemovePlayerFromVehicleEx(Offer[playerid]);
        Offer[playerid] = MAX_PLAYERS-1;
		CarPrice[playerid] = 0;
        //SendClientMessage(playerid, COLOR_GREY, "   Вы не можете застраховать Автомобиль !"); return 1; }
		MenuOperation[playerid] = 0;
	}
	else if(MenuOperation[playerid] == 26)//	/buycar //	/sellgun"
	{
	    if(Offer[playerid] >= MAX_PLAYERS-1 || !IsPlayerConnected(Offer[playerid]))
		{
		    RemovePlayerFromVehicleEx(playerid);
	        Offer[playerid] = MAX_PLAYERS-1;
			CarPrice[playerid] = 0;
			MenuOperation[playerid] = 0;
		    SendClientMessage(playerid, COLOR_GREY, "   Нет предложившего Вам Авто!");
		    return 1;
		}
		nCarID[playerid] = GetPlayerVehicleID(playerid);
		if(VehInfo[nCarID[playerid]][cType] < 1000)
		{
		    RemovePlayerFromVehicleEx(playerid);
			RemovePlayerFromVehicleEx(Offer[playerid]);
	        Offer[playerid] = MAX_PLAYERS-1;
			CarPrice[playerid] = 0;
			MenuOperation[playerid] = 0;
		    SendClientMessage(playerid, COLOR_GREY, "   Это транспортное средство не подлежит продаже !");
		    return 1;
		}
		if(VehInfo[nCarID[playerid]][cPark] == 1 || VehInfo[nCarID[playerid]][cPark] == 2)
		{
		    RemovePlayerFromVehicleEx(playerid);
			RemovePlayerFromVehicleEx(Offer[playerid]);
	        Offer[playerid] = MAX_PLAYERS-1;
			CarPrice[playerid] = 0;
			MenuOperation[playerid] = 0;
		    SendClientMessage(playerid, COLOR_GREY, "   Запаркованное транспортное средство не подлежит продаже !");
		    return 1;
		}
	    if(VehInfo[nCarID[playerid]][cPark] >= PARKING)
		{
		    RemovePlayerFromVehicleEx(playerid);
			RemovePlayerFromVehicleEx(Offer[playerid]);
	        Offer[playerid] = MAX_PLAYERS-1;
			CarPrice[playerid] = 0;
			MenuOperation[playerid] = 0;
		    SendClientMessage(playerid, COLOR_GREY, "   Это транспортное средство уже продано скупщику !");
		    return 1;
		}
		GivePlayerMoneyB(fjob+PlayerInfo[Offer[playerid]][pJob], playerid, CarPrice[playerid]);
		GivePlayerMoneyH(fjob+PlayerInfo[Offer[playerid]][pJob], Offer[playerid], -CarPrice[playerid]);
		new carid = nCarID[playerid];
	 	//GetVehiclePos(carid, VehInfo[carid][cLocX], VehInfo[carid][cLocY], VehInfo[carid][cLocZ]);
		//GetVehicleZAngle(carid, VehInfo[carid][cAng]);
		LockCar(carid);
		VehInfo[carid][cPark] = GetPVarInt(playerid, "BizID");//PlayerInfo[Offer[playerid]][pBizz]-100;//записываем номер биза
		SaveCarParameters(carid);
		format(msgitem, sizeof(msgitem), "* Вы продали Автомобиль %s's по цене {33AA33}$%d", PlayerName(Offer[playerid]),CarPrice[playerid]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
		format(msgitem, sizeof(msgitem), "* %s продал Вам Автомобиль по цене {33AA33}$%d.", PlayerName(playerid),CarPrice[playerid]);
		SendClientMessage(Offer[playerid], COLOR_LIGHTBLUE, msgitem);
	    RemovePlayerFromVehicleEx(playerid);
		RemovePlayerFromVehicleEx(Offer[playerid]);
        Offer[playerid] = MAX_PLAYERS-1;
		CarPrice[playerid] = 0;
		MenuOperation[playerid] = 0;
	}
	else if(MenuOperation[playerid] == 28)//	/accept guard
	{
	    if(Offer[playerid] >= MAX_PLAYERS-1)
	    {
	        SendClientMessage(playerid, COLOR_GREY, "   Нет предложившего Вам Защиту !");
	        return 1;
	    }
	    if( IsPlayerConnectedEx(Offer[playerid]) )
	    {
			//format(msgitem, sizeof(msgitem), "* Вы приняли услуги на сумму $%d от Телохранителя %s.",GuardPrice[playerid],PlayerName(Offer[playerid]));
			format(msgitem, sizeof(msgitem), "* Вы приняли услуги от Телохранителя %s.", PlayerName(Offer[playerid]));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
			//format(msgitem, sizeof(msgitem), "* %s принял ваши услуги по Защите. Вам перечислено на счёт в банке $%d.", PlayerName(playerid),GuardPrice[playerid]);
			format(msgitem, sizeof(msgitem), "* %s принял ваши услуги по Защите.", PlayerName(playerid));
			SendClientMessage(Offer[playerid], COLOR_LIGHTBLUE, msgitem);
			//GivePlayerMoneyB(1, Offer[playerid], GuardPrice[playerid]);
			//GivePlayerMoneyH(1, playerid, -GuardPrice[playerid]);
	        Offer[playerid] = MAX_PLAYERS-1;
			GuardPrice[playerid] = 0;
		}
	}
	return 1;
}


stock CreateStaticVehicleEx(playerid, modelid, Float:spawn_x,Float:spawn_y,Float:spawn_z,Float:angle_z,color1,color2,carspawntime)
{	// вызывается при покупке тачки у автодилера по команде /sellcar
	#pragma unused carspawntime
	//carspawntime = 0;

	new vehicleid;
	if(	modelid == 449 ||
		modelid == 537 || modelid == 569 || modelid == 590 ||
		modelid == 538 || modelid == 570)
	{   //если это поезд или вагон
		if(modelid == 569 || modelid == 590 || modelid == 570)
		{   //если это вагон
			vehicleid = VehInfo[VehiclesCounter][cID] + 1;//то не создавать тачку
		}
	 	else if(modelid == 449 || modelid == 538)
	 	{   //если это поезд
			vehicleid = AddStaticVehicle(modelid,spawn_x,spawn_y,spawn_z,angle_z,color1,color2);
			gVehicleSpawn[vehicleid] = 1;
		}
	}
	else
	{
		vehicleid = CreateVehicle(modelid,spawn_x,spawn_y,spawn_z,angle_z,color1,color2,-1);
		gVehicleSpawn[vehicleid] = 1;
	}
	CarStatus[vehicleid][st_engine] = VEHICLE_PARAMS_OFF;
	CarStatus[vehicleid][st_lights] = VEHICLE_PARAMS_OFF;
	CarStatus[vehicleid][st_alarm] = VEHICLE_PARAMS_OFF;
	CarStatus[vehicleid][st_doors] = VEHICLE_PARAMS_OFF;
	CarStatus[vehicleid][st_bonnet] = VEHICLE_PARAMS_OFF;
	CarStatus[vehicleid][st_boot] = VEHICLE_PARAMS_OFF;
	CarStatus[vehicleid][st_objective] = VEHICLE_PARAMS_OFF;

	VehPos[vehicleid][0] = spawn_x;
	VehPos[vehicleid][1] = spawn_y;
	VehPos[vehicleid][2] = spawn_z;
	VehPos[vehicleid][3] = angle_z;

	SetVehicleParams(vehicleid,//-1,
		VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF);
	LoadCarCounter ++;
//для вайпа начало
	if(playerid != INVALID_PLAYER_ID)
	{
		//ТУТ т.к. мы не знаем какой будет ид у тачки при покупке
		VehInfo[vehicleid][cOwned] = PlayerInfo[playerid][pSQLID];
		strmid(VehInfo[vehicleid][cOwner], PlayerName(playerid), 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);

		GivePlayerMoneyH(fcar, playerid, -CarPrice[playerid]);

		if(MyCar[playerid][0] == 0) MyCar[playerid][0] = vehicleid;
		else if(MyCar[playerid][1] == 0) MyCar[playerid][1] = vehicleid;
		else if(MyCar[playerid][2] == 0) MyCar[playerid][2] = vehicleid;

		VehInfo[vehicleid][cType] = 1000 + LoadCarCounter;
		LockCar(vehicleid);//блокируем двери carid
		new numberplate[MAX_PLAYER_NAME+10];
		format(numberplate, sizeof(numberplate), "%s [ %d ]",VehInfo[vehicleid][cOwner], vehicleid);
	    //number3D[vehicleid] = Create3DTextLabel(numberplate,0x009DFFFF,0.0,0.0,0.0,30.0,0,1);
	    //Counter3DText ++;
	    //Attach3DTextLabelToVehicle(number3D[vehicleid], vehicleid, 0.0, 0.0, 0.3);
		number3D[vehicleid] = Create3DTextLabelEx(numberplate,0x009DFFFF,0.0,0.0,0.3,30.0, INVALID_PLAYER_ID, vehicleid, 1, 0);

	}
	else
	{
		VehInfo[vehicleid][cOwned] = 0;
		strmid(VehInfo[vehicleid][cOwner], "The State", 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);

		//ИНИЦИАЛИЗАЦИЯ
  		VehInfo[vehicleid][cType] = 600 + index12;
		PublicCar[index12] = vehicleid;
		index12 ++;
	}
//для вайпа конец
	VehiclesCounter ++;//чтобы начиналось с 1
	//--------------------------------------------------------------------------
	new Found = 0;
	for(new i=1; i<=GetMaxVehicles; i++)//MAX_VEHICLES //VehiclesCounter
	{   //сканируем все тачки, добавленные в мод
		if(modelid == aExistModel[i]) { Found = 1; break; }
	}
   	if(Found == 0)
   	{   //если не нашли и дошли до конца массива, создаем массив различных моделей
		VehiclesModelsCounter ++;
		aExistModel[VehiclesModelsCounter] = modelid;
		//printf("aExistModel[%d] = %d", VehiclesModelsCounter, aExistModel[VehiclesModelsCounter]);//для проверки ограничения
	}
	//--------------------------------------------------------------------------
	VehInfo[vehicleid][cID] = vehicleid;
	//strmid(VehInfo[vehicleid][cKey], "", 0, strlen(""), 12);
	VehInfo[vehicleid][cModel] = modelid;
	//VehInfo[vehicleid][cType] = VehInfo[vehicleid][cType];

	if(VehInfo[vehicleid][cType] >= 1000)
	{//сразу меняем парковку, чтобы не спаунились в автосалоне
		new rand = random(sizeof(VehicleSpawns));
		VehInfo[vehicleid][cLocX] = VehicleSpawns[rand][0];
		VehInfo[vehicleid][cLocY] = VehicleSpawns[rand][1];
		VehInfo[vehicleid][cLocZ] = VehicleSpawns[rand][2];
		VehInfo[vehicleid][cAng] = VehicleSpawns[rand][3];
	}
	else
	{
		VehInfo[vehicleid][cLocX] = spawn_x;
		VehInfo[vehicleid][cLocY] = spawn_y;
		VehInfo[vehicleid][cLocZ] = spawn_z;
		VehInfo[vehicleid][cAng] = angle_z;
	}

	VehInfo[vehicleid][cInt] = 0;
	VehInfo[vehicleid][cVirt] = GetVehicleVirtualWorld(vehicleid);
	VehInfo[vehicleid][cPark] = 0;
	VehInfo[vehicleid][cAttach] = 0;
	VehInfo[vehicleid][cInsur] = 0;
	VehInfo[vehicleid][cDist] = 0;
	VehInfo[vehicleid][cFuel] = float(VehicleArray[modelid-400][GasMax]);//100.0;
	VehInfo[vehicleid][cLoad] = 0;
	VehInfo[vehicleid][cLoadType] = 0;
	VehInfo[vehicleid][cDate] = getdate();
	VehInfo[vehicleid][cColor1] = color1;
	VehInfo[vehicleid][cColor2] = color2;
	VehInfo[vehicleid][cPaintjob] = 255;
	VehInfo[vehicleid][cSpoiler] = 0;
	VehInfo[vehicleid][cHood] = 0;
	VehInfo[vehicleid][cRoof] = 0;
	VehInfo[vehicleid][cSideskirt] = 0;
	VehInfo[vehicleid][cLamps] = 0;
	VehInfo[vehicleid][cNitro] = 0;
	VehInfo[vehicleid][cExhaust] = 0;
	VehInfo[vehicleid][cWheels] = 0;
	VehInfo[vehicleid][cStereos] = 0;
	VehInfo[vehicleid][cHydraulics] = 0;
	VehInfo[vehicleid][cFrontBumper] = 0;
	VehInfo[vehicleid][cRearBumper] = 0;
	VehInfo[vehicleid][cVentRight] = 0;
	VehInfo[vehicleid][cVentLeft] = 0;
	VehInfo[vehicleid][cHealth] = 1000.0; VehHealth[vehicleid] = VehInfo[vehicleid][cHealth];
	VehInfo[vehicleid][DamagePanels] = 0;
	VehInfo[vehicleid][DamageDoors] = 0;
	VehInfo[vehicleid][DamageLights] = 0;
	VehInfo[vehicleid][DamageTires] = 0;
	//--------------------------------------------------------------------------
/*	new ToBase[377+145+13 + 4 + 3+4+10+24+6*4+2+10+1+3+4+10 +3+5+3+3+3+3+4*15+6+10+10+4+4 + 12];
	strcat(ToBase, "INSERT INTO `vehicles` (`ID`,\
Model,\
Type,\
Owned,\
Owner,\
LocX,\
LocY,\
LocZ,\
Ang,\
`Int`,\
Virt,\
`Lock`,\
Park,\
Attach,\
Insur,\
Fuel,\
`Load`,\
`LoadType`,\
`Date`,\
Color1,\
Color2,\
Paintjob,\
Spoiler,\
Hood,\
Roof,\
Sideskirt,\
Lamps,\
Nitro,\
Exhaust,\
Wheels,\
Stereos,\
Hydraulics,\
FrontBumper,\
RearBumper,\
VentRight,\
VentLeft,\
Health,\
Panels,\
Doors,\
Lights,\
Tires) ");

	format(ToBase, sizeof(ToBase), "%sVALUES (%d,%d,%d,%d,'%s',%.1f,%.1f,%.1f,%.1f,%d,%d,%d, %d,%d,%d, %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%.1f,%d,%d,%d,%d)",
	ToBase,
	VehInfo[vehicleid][cID],
	VehInfo[vehicleid][cModel],
	VehInfo[vehicleid][cType],
	VehInfo[vehicleid][cOwned],
	VehInfo[vehicleid][cOwner],
	VehInfo[vehicleid][cLocX],
	VehInfo[vehicleid][cLocY],
	VehInfo[vehicleid][cLocZ],
	VehInfo[vehicleid][cAng],
	VehInfo[vehicleid][cInt],
	VehInfo[vehicleid][cVirt],
	VehInfo[vehicleid][cLock],

	VehInfo[vehicleid][cPark],
	VehInfo[vehicleid][cAttach],
	VehInfo[vehicleid][cInsur],

	floatround(VehInfo[vehicleid][cFuel]),
	VehInfo[vehicleid][cLoad],
	VehInfo[vehicleid][cLoadType],
	VehInfo[vehicleid][cDate],
	VehInfo[vehicleid][cColor1],
	VehInfo[vehicleid][cColor2],
	VehInfo[vehicleid][cPaintjob],
	VehInfo[vehicleid][cSpoiler],
	VehInfo[vehicleid][cHood],
	VehInfo[vehicleid][cRoof],
	VehInfo[vehicleid][cSideskirt],
	VehInfo[vehicleid][cLamps],
	VehInfo[vehicleid][cNitro],
	VehInfo[vehicleid][cExhaust],
	VehInfo[vehicleid][cWheels],
	VehInfo[vehicleid][cStereos],
	VehInfo[vehicleid][cHydraulics],
	VehInfo[vehicleid][cFrontBumper],
	VehInfo[vehicleid][cRearBumper],
	VehInfo[vehicleid][cVentRight],
	VehInfo[vehicleid][cVentLeft],
	VehInfo[vehicleid][cHealth],
	VehInfo[vehicleid][DamagePanels],
	VehInfo[vehicleid][DamageDoors],
	VehInfo[vehicleid][DamageLights],
	VehInfo[vehicleid][DamageTires]);
	mysql_query(ToBase);
	VehInfo[vehicleid][cIND] = mysql_insert_id();
*/
	if(vehicleid > GetMaxVehicles) GetMaxVehicles = vehicleid;
	//GetMaxVehicles = GetHighestVehicleID()+1;
	return vehicleid;
}

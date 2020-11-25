//------------------------------------------------------------------------------
#define MAX_MUSOR 5       // Макс. кол-во мусора в баке

new Musor[MAX_PLAYERS]; //МУСОР
new AreMusor[MAX_PLAYERS]; //НАЛИЧИЕ ПАКЕТА С МУСОРОМ НА ДОРОГЕ
new LastRandom[MAX_PLAYERS];
new Trashpacket[MAX_PLAYERS]; //ПАКЕТ С МУСОРОМ

new gAreTank[MAX_VEHICLES+1] = {0, ...}; //флаг НАЛИЧИЕ МУСОРНОГО БАКА НА МАШИНЕ

//для мусорщиков
new Box1[MAX_VEHICLES+1]; //ящик открытый
new Box2[MAX_VEHICLES+1]; //ящик закрытый
new Trash1[MAX_VEHICLES+1]; //мешок 1
new Trash2[MAX_VEHICLES+1]; //мешок 2

//************************************//
//         Места сбора мусора         //
//************************************//
new Float:trash[][3] = {
 {-2037.4995,-2528.0588,30.6250},  //House 1
 {2102.5576,-1274.6263,25.4907},   //House 2
 {193.6281,-106.8917,1.5482},      //House 3
 {-1443.3176,-1537.6855,101.7578}, //House 4
 {860.5648,-17.4365,63.2688},      //House 5
 {912.5654,2003.6926,10.8203},     //House 6
 {-2078.7263,-2302.6523,30.6250},  //House 26
 {-1540.7213,2653.7715,55.8359},   //House 8
 {-1046.6071,1545.5680,33.0651},   //House 9
 {-375.1018,1155.1229,19.7422},    //House 10
 {-2703.3445,817.2593,49.8281},    //House 11
 {1392.3685,1898.8763,10.6719},    //House 12
 {2208.8003,1839.3129,10.8203},    //House 13
 {1304.8383,379.1521,19.5547},     //House 14
 {319.6951,-1775.5868,4.8236},     //House 15
 {2006.5212,-1633.7631,13.3828},   //House 16
 {2810.8284,2152.1282,10.8203},    //House 17
 {2432.9727,694.9072,10.8203},     //House 18
 {-2107.9685,907.1699,76.8162},    //House 19
 {-2224.8674,103.7970,35.3203},    //House 21
 {-2031.3865,-52.1265,35.3696},    //House 39
 {2805.2693,-1970.5173,13.5469},   //House 7
 {2526.0906,-1108.3550,56.8685},   //House 22
 {1485.9623,-694.6193,94.7500},    //House 24
 {-2717.9958,-33.4617,4.3359},     //House 23
 {-2695.1028,112.7652,4.3359},     //House 38
 {884.9249,-1648.8776,13.5469},    //House 27
 {-2379.3318,848.5102,40.1994},    //House 25
 {1106.9745,-732.1215,100.7238},   //House 29
 {-2384.7131,2432.4321,9.4251},    //House 12
 {-2547.9431,2279.3955,4.9844},    //House 31
 {-2479.1614,1132.5444,55.7266},   //House 32
 {2231.5454,161.0766,27.2115},     //House 33
 {293.6717,-1153.3765,80.9099},    //House 34
 {1330.4863,-627.3713,109.1349},   //House 35
 {632.5396,-1118.5054,46.0053},    //House 36
 {833.8336,-866.2376,68.9339},     //House 37
 {-2458.2263,-140.2907,25.9809},   //House 38
 {2483.5972,-2004.3735,13.5469},   //House 39
 {2489.2378,-1682.7185,13.3359},   //House 40
 {-208.1181,2765.2061,62.5372},    //House 41
 {1284.4001,2528.5544,10.8125},    //House 42
 {1525.4197,-805.3763,72.4802},    //House 43
 {-2447.6072,813.2158,35.0313},    //House 44
 {1698.5985,-2098.9092,13.5469},   //House 45
 {786.9681,-513.9152,16.6375},     //House 46
 {2037.1344,1623.3638,10.8281},    //House 47
 {2232.6777,1286.3583,10.8203},    //House 42
 {-2610.9712,2344.1345,8.4345},    //House 28
 {2327.0706,-117.3205,27.1818},    //House 29
 {2207.6284,-45.4652,26.7817}      //House 30
};


stock trashman_OnGameModeInit()
{
	print("  vw_trashman 1.0 By: DANGER1979");
	print("_____________________________________________");
	print(" ");
}

//для мусорщиков начало STEP2
stock trashman_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
		#pragma unused listitem
		#pragma unused inputtext
		if(dialogid != TRASHMAN_DIALOG) return 1;
   //ShowPlayerDialogGap(playerid, TRASHMAN_DIALOG, DIALOG_STYLE_MSGBOX, "РАБОТОДАТЕЛЬ", "Вы хотите начать или закончить работу?", "Начать", "Закончить");
		if(response)
		{
			if(PlayerInfo[playerid][pJob] != TRASHMAN) return SendClientMessage(playerid, COLOR_GREY, "   Вы не Водитель Мусоровоза !");
            if(gJobDuty[playerid] == 1)
			{
                SendClientMessage(playerid, COLOR_RED, "Работодатель: Вы уже на работе.");
    	        return 1;
        	}
            gJobDuty[playerid] = 1;
        	SetPlayerSkinEx(playerid, 128);
	        SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы вышли на дежурство. Сядьте в TrashMaster (model:408).");
	        
			format(strings, sizeof(strings), "   Если у вас нет мусоровоза, то отправляйтесь в Автосалон(/gps 1015) и не забудьте прихватить не менее $%d.",
				VehicleArray[408-400][Virtual_Price]);
	        SendClientMessage(playerid, COLOR_GREY, strings);
		}
		else
		{
			if(PlayerInfo[playerid][pJob] != TRASHMAN) return SendClientMessage(playerid, COLOR_GREY, "   Вы не Водитель Мусоровоза !");
            if(gJobDuty[playerid] == 0)
			{
                SendClientMessage(playerid, COLOR_RED, "Работодатель: Вы не на работе.");
    	        return 1;
        	}
			Musor[playerid] = 0;
			if( IsValidObjectEx(Box2[LastCar[playerid]]) ) DestroyObjectEx(Box2[LastCar[playerid]], 2);
			gAreTank[nCarID[playerid]] = 0;
			DisablePlayerCheckpointEx(playerid);

        	gJobDuty[playerid] = 0;
    		SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
        	//DeletePVar(playerid, "dutylist");
        	SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы закончили рабочий день");
		}
		return 1;
}//для мусорщиков конец


stock trashman_OnEnterCheckpoint(playerid)//для мусорщиков
{
	//else if(IsPlayerInRangeOfPoint(playerid, 5.0, 2249.4053,-2015.4734,13.5469))  // установка мусорного бака
	if(CP[playerid] == CP_TRASHMAN_1 && PlayerInfo[playerid][pJob] == TRASHMAN)  //для мусорщиков начало STEP5
	{
		//if(PlayerInfo[playerid][pJob] != TRASHMAN) return SendClientMessage(playerid, COLOR_GREY, "   Вы не Водитель Мусоровоза !");
		if(gJobDuty[playerid] == 0) return SendClientMessage(playerid, COLOR_GREY, "   Вы не на дежурстве !");
		if(nCarModel[playerid] != 408) return SendClientMessage(playerid, COLOR_GREY, "   Вы не в мусоровозе !");
	    if(gAreTank[nCarID[playerid]] == 0)
		{
		
			/*if(GetTickCount() < (checktimedeliver[playerid]+MinTimeCheckpoint[playerid]) && !gAnticheat[playerid])
			{
				format(strings, sizeof(strings), "%s[%d] Reset TrashSkill1:%d checktimedeliver:%d[min %d] sec",
					PlayerName(playerid),playerid, PlayerInfo[playerid][pTrashSkill], (GetTickCount()-checktimedeliver[playerid])/1000, MinTimeCheckpoint[playerid]/1000);
				Log(JOB, strings);
				PlayerInfo[playerid][pTrashSkill] = 0;
				//JobAmmount[playerid] = 0;
				SendClientMessage(playerid, COLOR_GREY, strings);
			    return 1;
			}*/
			//format(strings, sizeof(strings), "%s[%d] TrashSkill1:%d checktimedeliver:%d sec",
			//	PlayerName(playerid),playerid, PlayerInfo[playerid][pTrashSkill], (GetTickCount()-checktimedeliver[playerid])/1000);
			//Log(JOB, strings);

		    SetVehicleVelocity(nCarID[playerid], 0.0, 0.0, 0.0);

	    	gAreTank[nCarID[playerid]] = 1;
			Box1[nCarID[playerid]] = CreateObjectEx(1439,0,0,0,0,0,0);
			AttachObjectToVehicleEx(Box1[nCarID[playerid]], nCarID[playerid], -0.1, -4.0, -0.90, 0.0, 0.0, 0.0);

			new money;
		   	PlayerInfo[playerid][pTrashSkill] += 1;
			new level = PlayerInfo[playerid][pTrashSkill];
			if(level <= 50)//если игрок доставил 1 мусор
			{
			    money = 2*(50 + random(10));//*10;//2000
				if(level == 50)//если игрок доставил 50 грузов то поднимается на следующий уровень 2
				{
					new Fee = (200 + random(100))*10;
					GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, Fee); SBizInfo[57][sbTill] -= Fee;
			    	format(strings, sizeof(strings), "Bаш Навык Водителя Мусоровоза теперь 2 ! Гонорар %d$.", Fee);
					SendClientMessage(playerid, COLOR_GREEN, strings);
					SendClientMessage(playerid, COLOR_GREEN, "Вы теперь получаете $1500-1800 за доставку контейнера.");
				}
			}
			else if(level > 50 && level <= 100)//2 Уровень
			{
			    money = 3*(50 + random(10));//*10;
				if(level == 100)
				{
					new Fee = (300 + random(100))*10;
					GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, Fee); SBizInfo[57][sbTill] -= Fee;
			    	format(strings, sizeof(strings), "Bаш Навык Водителя Мусоровоза теперь 3 ! Гонорар %d$.", Fee);
					SendClientMessage(playerid, COLOR_GREEN, strings);
					SendClientMessage(playerid, COLOR_GREEN, "Вы получаете $2000-2400 за доставку контейнера.");
				}
			}
			else if(level > 100 && level <= 200)//3 Уровень
			{
			    money = 4*(50 + random(10));//*10;
				if(level == 200)
				{
					new Fee = (400 + random(100))*10;
					GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, Fee); SBizInfo[57][sbTill] -= Fee;
			    	format(strings, sizeof(strings), "Bаш Навык Водителя Мусоровоза теперь 4 ! Гонорар %d$.", Fee);
					SendClientMessage(playerid, COLOR_GREEN, strings);
					SendClientMessage(playerid, COLOR_GREEN, "Вы получаете $2500-3000 за доставку контейнера.");
				}
			}
			else if(level > 200 && level <= 400)//4 Уровень
			{
			    money = 5*(50 + random(10));//*10;
				if(level == 400)
				{
					GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, RANDMONEY5*10); SBizInfo[57][sbTill] -= RANDMONEY5*10;
			    	format(strings, sizeof(strings), "Bаш Навык Водителя Мусоровоза теперь 5 ! Гонорар %d$.", RANDMONEY5*10);
					SendClientMessage(playerid, COLOR_GREEN, strings);
					SendClientMessage(playerid, COLOR_GREEN, "Вы получаете $3600 за доставку контейнера.");
				}
			}
			else if(level > 400)//5 Уровень
			{
			    money = 6*(50 + random(10));//*10;
			}
			GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, money);
			SBizInfo[57][sbTill] -= money;

			SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Бак установлен. Проверьте, надежно ли он закреплен.");
			DisablePlayerCheckpointEx(playerid);
			RemovePlayerFromVehicleEx(playerid);
		}
		else if(gAreTank[nCarID[playerid]] == 1)
		{
		    DisablePlayerCheckpointEx(playerid);
		    SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}На этой машине уже есть бак для сбора мусора.");
		}
//TestLog(OPTIM, "OnPlayerEnterCheckpoint1.11 ", GetTickCount(), timers);
	}
//для мусорщиков начало STEP7
	else if(CP[playerid] == CP_TRASHMAN_2 && PlayerInfo[playerid][pJob] == TRASHMAN)
	{
	   	//if(PlayerInfo[playerid][pJob] != TRASHMAN) return SendClientMessage(playerid, COLOR_GREY, "   Вы не Водитель Мусоровоза !");
		if(gJobDuty[playerid] == 0) return SendClientMessage(playerid, COLOR_GREY, "   Вы не на дежурстве !");
		if(nCarModel[playerid] != 408) return SendClientMessage(playerid, COLOR_GREY, "   Вы не в мусоровозе !");

		/*if(GetTickCount() < (checktimedeliver[playerid]+MinTimeCheckpoint[playerid]) && !gAnticheat[playerid])
		{
			format(strings, sizeof(strings), "%s[%d] Reset TrashSkill2:%d checktimedeliver:%d[min %d] sec",
				PlayerName(playerid),playerid, PlayerInfo[playerid][pTrashSkill], (GetTickCount()-checktimedeliver[playerid])/1000, MinTimeCheckpoint[playerid]/1000);
			Log(JOB, strings);
			PlayerInfo[playerid][pTrashSkill] = 0;
			//JobAmmount[playerid] = 0;
			SendClientMessage(playerid, COLOR_GREY, strings);
		    return 1;
		}*/
		/*format(strings, sizeof(strings), "%s[%d] TrashSkill2:%d checktimedeliver:%d sec",
			PlayerName(playerid),playerid, PlayerInfo[playerid][pTrashSkill], (GetTickCount()-checktimedeliver[playerid])/1000);
		Log(JOB, strings);*/

	    //for(new i=0; i<3; i++)
	    //{
			//if(!IsPlayerInRangeOfPoint(playerid, 4.0, trash[i][0],trash[i][1],trash[i][2])) continue; //место сбора, фаза 1
		Musor[playerid] ++;
		SetVehicleVelocity(nCarID[playerid], 0.0, 0.0, 0.0);
		DisablePlayerCheckpointEx(playerid);

		new Float:x,Float:y,Float:z;
    	GetVehiclePos(nCarID[playerid],x,y,z);

		new money;
	   	PlayerInfo[playerid][pTrashSkill] += 1;
		new level = PlayerInfo[playerid][pTrashSkill];
		if(level <= 50)//если игрок доставил 1 мусор
		{
		    money = 2*(50 + random(10));//*10;//2000
			if(level == 50)//если игрок доставил 50 грузов то поднимается на следующий уровень 2
			{
				new Fee = (200 + random(100))*10;
				GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, Fee);
		    	format(strings, sizeof(strings), "Bаш Навык Водителя Мусоровоза теперь 2 ! Гонорар %d$.", Fee);
				SendClientMessage(playerid, COLOR_GREEN, strings);
				SendClientMessage(playerid, COLOR_GREEN, "Вы теперь получаете $1500-1800 за доставку контейнера.");
			}
		}
		else if(level > 50 && level <= 100)//2 Уровень
		{
		    money = 3*(50 + random(10));//*10;
			if(level == 100)
			{
				new Fee = (300 + random(100))*10;
				GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, Fee);
		    	format(strings, sizeof(strings), "Bаш Навык Водителя Мусоровоза теперь 3 ! Гонорар %d$.", Fee);
				SendClientMessage(playerid, COLOR_GREEN, strings);
				SendClientMessage(playerid, COLOR_GREEN, "Вы получаете $2000-2400 за доставку контейнера.");
			}
		}
		else if(level > 100 && level <= 200)//3 Уровень
		{
		    money = 4*(50 + random(10));//*10;
			if(level == 200)
			{
				new Fee = (400 + random(100))*10;
				GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, Fee);
		    	format(strings, sizeof(strings), "Bаш Навык Водителя Мусоровоза теперь 4 ! Гонорар %d$.", Fee);
				SendClientMessage(playerid, COLOR_GREEN, strings);
				SendClientMessage(playerid, COLOR_GREEN, "Вы получаете $2500-3000 за доставку контейнера.");
			}
		}
		else if(level > 200 && level <= 400)//4 Уровень
		{
		    money = 5*(50 + random(10));//*10;
			if(level == 400)
			{
				GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, RANDMONEY5*10);
		    	format(strings, sizeof(strings), "Bаш Навык Водителя Мусоровоза теперь 5 ! Гонорар %d$.", RANDMONEY5*10);
				SendClientMessage(playerid, COLOR_GREEN, strings);
				SendClientMessage(playerid, COLOR_GREEN, "Вы получаете $3600 за доставку контейнера.");
			}
		}
		else if(level > 400)//5 Уровень
		{
		    money = 6*(50 + random(10));//*10;
		}
		GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, money);

		Trashpacket[playerid] = SetPickupEx(1265, 1, x+2.0,y+2.0,z-0.6);

		CP[playerid] = 0;
		RemovePlayerFromVehicleEx(playerid);
		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Выйдите из машины и заберите мешок с мусором.");
		//}
//TestLog(OPTIM, "OnPlayerEnterCheckpoint1.12 ", GetTickCount(), timers);
	}
	//if(IsPlayerInRangeOfPoint(playerid, 4.0, 2197.6030,-1976.1382,13.5585))  // сдача мусора
//для мусорщиков начало STEP11
	else if(CP[playerid] == CP_TRASHMAN_3 && PlayerInfo[playerid][pJob] == TRASHMAN)
	{
		//if(PlayerInfo[playerid][pJob] != TRASHMAN) return SendClientMessage(playerid, COLOR_GREY, "   Вы не Водитель Мусоровоза !");
		if(gJobDuty[playerid] == 0) return SendClientMessage(playerid, COLOR_GREY, "   Вы не на дежурстве !");
		if(nCarModel[playerid] != 408) return SendClientMessage(playerid, COLOR_GREY, "   Вы не в мусоровозе !");

		/*if(GetTickCount() < (checktimedeliver[playerid]+MinTimeCheckpoint[playerid]) && !gAnticheat[playerid])
		{
			format(strings, sizeof(strings), "%s[%d] Reset TrashSkill3:%d Mats:%d checktimedeliver:%d[min %d] sec",
				PlayerName(playerid),playerid, PlayerInfo[playerid][pTrashSkill], JobAmmount[playerid], (GetTickCount()-checktimedeliver[playerid])/1000, MinTimeCheckpoint[playerid]/1000);
			Log(JOB, strings);
			PlayerInfo[playerid][pTrashSkill] = 0;
			JobAmmount[playerid] = 0;
			SendClientMessage(playerid, COLOR_GREY, strings);
		    return 1;
		}*/
		/*format(strings, sizeof(strings), "%s[%d] TrashSkill3:%d checktimedeliver:%d sec",
			PlayerName(playerid),playerid, PlayerInfo[playerid][pTrashSkill], (GetTickCount()-checktimedeliver[playerid])/1000);
		Log(JOB, strings);*/

		new level;
		if(PlayerInfo[playerid][pTrashSkill] <= 50) level = 1;
		else if(PlayerInfo[playerid][pTrashSkill] > 50 && PlayerInfo[playerid][pTrashSkill] <= 100) level = 2;
		else if(PlayerInfo[playerid][pTrashSkill] > 100 && PlayerInfo[playerid][pTrashSkill] <= 200) level = 3;
		else if(PlayerInfo[playerid][pTrashSkill] > 200 && PlayerInfo[playerid][pTrashSkill] <= 400) level = 4;
		else if(PlayerInfo[playerid][pTrashSkill] > 400) level = 5;
		if(Musor[playerid] >= level)
		{
			new money;
		   	PlayerInfo[playerid][pTrashSkill] += 10;//увеличить счётчик проф. уровня доставленных грузов
			level = PlayerInfo[playerid][pTrashSkill];
			if(level <= 50)//если игрок доставил 1 мусор
			{
			    money = 2*(50 + random(10))*10;//2000
				if(level == 50)//если игрок доставил 50 грузов то поднимается на следующий уровень 2
				{
					new Fee = (200 + random(100))*10;
					GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, Fee);
			    	format(strings, sizeof(strings), "Bаш Навык Водителя Мусоровоза теперь 2 ! Гонорар %d$.", Fee);
					SendClientMessage(playerid, COLOR_GREEN, strings);
					SendClientMessage(playerid, COLOR_GREEN, "Вы теперь получаете $1500-1800 за доставку контейнера.");
				}
			}
			else if(level > 50 && level <= 100)//2 Уровень
			{
			    money = 3*(50 + random(10))*10;
				if(level == 100)
				{
					new Fee = (300 + random(100))*10;
					GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, Fee);
			    	format(strings, sizeof(strings), "Bаш Навык Водителя Мусоровоза теперь 3 ! Гонорар %d$.", Fee);
					SendClientMessage(playerid, COLOR_GREEN, strings);
					SendClientMessage(playerid, COLOR_GREEN, "Вы получаете $2000-2400 за доставку контейнера.");
				}
			}
			else if(level > 100 && level <= 200)//3 Уровень
			{
			    money = 4*(50 + random(10))*10;
				if(level == 200)
				{
					new Fee = (400 + random(100))*10;
					GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, Fee);
			    	format(strings, sizeof(strings), "Bаш Навык Водителя Мусоровоза теперь 4 ! Гонорар %d$.", Fee);
					SendClientMessage(playerid, COLOR_GREEN, strings);
					SendClientMessage(playerid, COLOR_GREEN, "Вы получаете $2500-3000 за доставку контейнера.");
				}
			}
			else if(level > 200 && level <= 400)//4 Уровень
			{
			    money = 5*(50 + random(10))*10;
				if(level == 400)
				{
					GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, RANDMONEY5*10);
			    	format(strings, sizeof(strings), "Bаш Навык Водителя Мусоровоза теперь 5 ! Гонорар %d$.", RANDMONEY5*10);
					SendClientMessage(playerid, COLOR_GREEN, strings);
					SendClientMessage(playerid, COLOR_GREEN, "Вы получаете $3600 за доставку контейнера.");
				}
			}
			else if(level > 400)//5 Уровень
			{
			    money = 6*RANDMONEY5;//5*600
			}
			GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, money);

			SetVehicleVelocity(nCarID[playerid], 0.0, 0.0, 0.0);

			Musor[playerid] = 0;
           	if( IsValidObjectEx(Box2[nCarID[playerid]]) ) DestroyObjectEx(Box2[nCarID[playerid]], 9);
           	gAreTank[nCarID[playerid]] = 0;
           	DisablePlayerCheckpointEx(playerid);
		}
//TestLog(OPTIM, "OnPlayerEnterCheckpoint1.13 ", GetTickCount(), timers);
	}
	//для мусорщиков конец
	return 1;
}

stock trashman_OnPlayerPickUpPickup(playerid, pickupid)
{
	//--------------------------------------------------------------------------
//для мусорщиков начало STEP1
 	if(pickupid == PickupID[8] && IsPlayerInRangeOfPoint(playerid, 2.1, Pickups[pickupid][p_x],Pickups[pickupid][p_y],Pickups[pickupid][p_z]) )
    {
    	if(PlayerInfo[playerid][pJob] != TRASHMAN) return SendClientMessage(playerid, COLOR_GREY, "   Вы не Водитель Мусоровоза !!");
        ShowPlayerDialogGap(playerid, TRASHMAN_DIALOG, DIALOG_STYLE_MSGBOX, "РАБОТОДАТЕЛЬ", "Вы хотите начать или закончить работу?", "Начать", "Закончить");
        return 1;
	}
//для мусорщиков начало STEP8
 	if(pickupid == Trashpacket[playerid] //&& Trashpacket[playerid] != 0
	  && IsPlayerInRangeOfPoint(playerid, 2.1, Pickups[pickupid][p_x],Pickups[pickupid][p_y],Pickups[pickupid][p_z]) )  //место сбора, фаза 2 "Поднятие мешка"
    {
    	if(PlayerInfo[playerid][pJob] != TRASHMAN) return SendClientMessage(playerid, COLOR_GREY, "   Вы не Водитель Мусоровоза !!!");
     	if( IsPlayerInAnyVehicle(playerid) ) return 1;
        if(gJobDuty[playerid] == 1)
	    {
        	SetPlayerAttachedObjectEx( playerid, DUTY_SLOT, 1265, Right_hand, 0.003353,-0.023383,-0.076903, 0.0,0.0,0.0, 0.500000,0.500000,0.500000 );
        	SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Положите мешок в бак. (USE: "#KEY_FOOT_AIM_WEAPON")");
			GameTextForPlayerEx(playerid, " Press ~b~~k~~PED_LOCK_TARGET~ ~n~~g~|~w~Place Bag~g~|", 1000, 1);
        	AreMusor[playerid] = 1;
        	DestroyPickupEx(Trashpacket[playerid]);
		}

	}//для мусорщиков конец
	return 1;
}



//stock OnPlayerKeyCheckMusor(playerid)//для мусорщиков начало STEP9
stock trashman_OnPlayerKeyStateChange(playerid)
{//если игрок нажал правую клавишу мышки или пробел на ногах
	if(PlayerInfo[playerid][pJob] != TRASHMAN) return 1;
	if(gJobDuty[playerid] == 0) return 1;

	/*if(IsPlayerInAnyVehicle(playerid))
	{
		//SendClientMessage(playerid, COLOR_GREY, "  Вы должны находиться ВНЕ транспортного средстве!");
		return 1;
	}*/
	new model = GetVehicleModel(LastCar[playerid]);
	if(model != 408)
	{
		//SendClientMessage(playerid, COLOR_GREY, "   Последнее управляемое авто не мусоровоз !");
		return 1;
	}
    if(AreMusor[playerid] != 1) return 1;//НАЛИЧИЕ ПАКЕТА С МУСОРОМ НА ДОРОГЕ

	new Float:X,Float:Y,Float:Z,Float:A;
	GetXYInFrontOfVehicle(LastCar[playerid], -4.3, X,Y,Z,A);
	if(!IsPlayerInRangeOfPoint(playerid, 2.0, X, Y, Z))	return 1;// место сбора, фаза 3 "Ложим мешок в бак"

	GetVehiclePos(LastCar[playerid], X, Y, Z);
	//if(!IsPlayerLookingAtPoint(playerid, X, Y, Z, 10, 10))
	if(!IsPlayerFacingToPoint(playerid, X, Y, 10)) //10 градусов - допустимый угол
	{
		return 1;
	}

	AreMusor[playerid] = 0;
	if(IsPlayerAttachedObjectSlotUsed(playerid, DUTY_SLOT)) RemovePlayerAttachedObject(playerid, DUTY_SLOT);
	ApplyAnimation(playerid, "INT_SHOP", "shop_shelf",4.1,0,1,1,0,0);

	new level;
	if(PlayerInfo[playerid][pTrashSkill] <= 50) level = 1;
	else if(PlayerInfo[playerid][pTrashSkill] > 50 && PlayerInfo[playerid][pTrashSkill] <= 100) level = 2;
	else if(PlayerInfo[playerid][pTrashSkill] > 100 && PlayerInfo[playerid][pTrashSkill] <= 200) level = 3;
	else if(PlayerInfo[playerid][pTrashSkill] > 200 && PlayerInfo[playerid][pTrashSkill] <= 400) level = 4;
	else if(PlayerInfo[playerid][pTrashSkill] > 400) level = 5;

	new strtmp[22+1+1];
 	format(strtmp, sizeof(strtmp), "~w~%d ~y~/~r~%d", Musor[playerid], level);
	GameTextForPlayerEx(playerid, strtmp, 1000, 4);

	if(Musor[playerid] >= level)//для мусорщиков начало STEP10
	{
		CP[playerid] = CP_TRASHMAN_3;
		SetPlayerCheckpointEx(playerid, 2197.6030,-1976.1382,13.5585, CHECKPOINT_SIZE);

		checktimedeliver[playerid] = GetTickCount();
		format(strings, sizeof(strings), "При доставке быстрее чем за %d секунд у вас обнулится скилл.", MinTimeCheckpoint[playerid]/1000);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);		

		if( IsValidObjectEx(Trash1[LastCar[playerid]]) ) DestroyObjectEx(Trash1[LastCar[playerid]], 6);
		if( IsValidObjectEx(Trash2[LastCar[playerid]]) ) DestroyObjectEx(Trash2[LastCar[playerid]], 6);
		if( IsValidObjectEx(Box1[LastCar[playerid]]) ) DestroyObjectEx(Box1[LastCar[playerid]], 6);
		//if( IsValidObjectEx(Box2[LastCar[playerid]]) ) DestroyObjectEx(Box2[LastCar[playerid]], 6);

		Box2[LastCar[playerid]] = CreateObjectEx(1372, 0.0,0.0,0.0, 0.0,0.0,0.0);
	    AttachObjectToVehicleEx(Box2[LastCar[playerid]], LastCar[playerid], 0.0,-4.0,-0.70, 0.0,0.0,0.0);
		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы собрали достаточно мусора. Отвезите его на свалку.");
	}
	else
	{
		new rand = random(sizeof(trash));
		while(rand == LastRandom[playerid])
		{
			rand = random(sizeof(trash));
		}
		LastRandom[playerid] = rand;
		//установили новый чекпоинт и мешок
		CP[playerid] = CP_TRASHMAN_2;
		SetPlayerCheckpointEx(playerid, trash[rand][0],trash[rand][1],trash[rand][2], CHECKPOINT_SIZE);
		
		checktimedeliver[playerid] = GetTickCount();
		format(strings, sizeof(strings), "При доставке быстрее чем за %d секунд у вас обнулится скилл.", MinTimeCheckpoint[playerid]/1000);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);		
		
		//Trashpacket[playerid] = SetPickupEx(1265,1,trash[rand][0]+1.2,trash[rand][1]+1.2,trash[rand][2]-0.6);
		if(Musor[playerid] == 1)
		{   //если это первый мешок мусор
			Trash1[LastCar[playerid]] = CreateObjectEx(1265, 0.0,0.0,0.0, 0.0,0.0,0.0);
			AttachObjectToVehicleEx(Trash1[LastCar[playerid]], LastCar[playerid], -0.3,-4.0,0.10, 0.0,0.0,90.0);
		}
		else if(Musor[playerid] == 3)
		{
			Trash2[LastCar[playerid]] = CreateObjectEx(1265, 0.0,0.0,0.0, 0.0,0.0,0.0);
			AttachObjectToVehicleEx(Trash2[LastCar[playerid]], LastCar[playerid], 0.3,-4.0,0.10, 0.0,0.0,0.0);
		}
	}

	new money;
   	PlayerInfo[playerid][pTrashSkill] += 1;
	level = PlayerInfo[playerid][pTrashSkill];
	if(level <= 50)//если игрок доставил 1 мусор
	{
	    money = 2*(50 + random(10));//*10;//2000
		if(level == 50)//если игрок доставил 50 грузов то поднимается на следующий уровень 2
		{
			new Fee = (200 + random(100))*10;
			GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, Fee);
	    	format(strings, sizeof(strings), "Bаш Навык Водителя Мусоровоза теперь 2 ! Гонорар %d$.", Fee);
			SendClientMessage(playerid, COLOR_GREEN, strings);
			SendClientMessage(playerid, COLOR_GREEN, "Вы теперь получаете $1500-1800 за доставку контейнера.");
		}
	}
	else if(level > 50 && level <= 100)//2 Уровень
	{
	    money = 3*(50 + random(10));//*10;
		if(level == 100)
		{
			new Fee = (300 + random(100))*10;
			GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, Fee);
	    	format(strings, sizeof(strings), "Bаш Навык Водителя Мусоровоза теперь 3 ! Гонорар %d$.", Fee);
			SendClientMessage(playerid, COLOR_GREEN, strings);
			SendClientMessage(playerid, COLOR_GREEN, "Вы получаете $2000-2400 за доставку контейнера.");
		}
	}
	else if(level > 100 && level <= 200)//3 Уровень
	{
	    money = 4*(50 + random(10));//*10;
		if(level == 200)
		{
			new Fee = (400 + random(100))*10;
			GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, Fee);
	    	format(strings, sizeof(strings), "Bаш Навык Водителя Мусоровоза теперь 4 ! Гонорар %d$.", Fee);
			SendClientMessage(playerid, COLOR_GREEN, strings);
			SendClientMessage(playerid, COLOR_GREEN, "Вы получаете $2500-3000 за доставку контейнера.");
		}
	}
	else if(level > 200 && level <= 400)//4 Уровень
	{
	    money = 5*(50 + random(10));//*10;
		if(level == 400)
		{
			GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, RANDMONEY5*10);
	    	format(strings, sizeof(strings), "Bаш Навык Водителя Мусоровоза теперь 5 ! Гонорар %d$.", RANDMONEY5*10);
			SendClientMessage(playerid, COLOR_GREEN, strings);
			SendClientMessage(playerid, COLOR_GREEN, "Вы получаете $3000-3600 за доставку контейнера.");
		}
	}
	else if(level > 400)//5 Уровень
	{
	    money = 6*(50 + random(10));//*10;
	}
	GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, money);
	return 1;
}

stock trashman_OnPlayerStateChange(playerid, newstate, oldstate)
{
	#pragma unused oldstate
	if(newstate != PLAYER_STATE_DRIVER) return 1;
	//new vehicleid = nCarID[playerid];//nCarID[playerid] = GetPlayerVehicleID(playerid);//считывается в player_OnPlayerStateChange(playerid, newstate, oldstate)
	new modelid = nCarModel[playerid];//считывается в player_OnPlayerStateChange(playerid, newstate, oldstate)
	//----------------------------------------------------------------------
	//ФУНКЦИЯ ПОЛУЧЕНИЯ ЗАДАНИЯ Мусорщика
	if(modelid == 408)//для мусорщиков начало
	{//при посадке в машину
		if(IsPermitToRider(playerid) || PlayerInfo[playerid][pJob] == TRASHMAN)
		{
		    if(gJobDuty[playerid] == 1)
		    {
			    if(AreMusor[playerid] == 1) //проверка на наличие мешка в руках
			    {
				    RemovePlayerFromVehicleEx(playerid);
				    return SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}У вас в руках есть мешок, отнесите его в бак");
			    }
			    if(CP[playerid] == CP_TRASHMAN_2)
			    {
				    return SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}На вашей карте уже отмечен {FF0000}маркер{0080FF}. Поторопитесь!");
			    }
			    //для мусорщиков начало STEP6
		        if(gAreTank[nCarID[playerid]] == 1)
	   			{ 	//едем собирать мусор
	   			    if(Musor[playerid] == 0 && AreMusor[playerid] != 1)
	   			    {
						new rand = random(sizeof(trash));
			   			while(rand == LastRandom[playerid])
						{
							rand = random(sizeof(trash));
						}
						LastRandom[playerid] = rand;
			    		CP[playerid] = CP_TRASHMAN_2;
			    		SetPlayerCheckpointEx(playerid, trash[rand][0],trash[rand][1],trash[rand][2],CHECKPOINT_SIZE);
			    		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}На вашей карте отмечен {FF0000}маркер{0080FF}, едьте к нему, чтобы забрать мусор.");
					}
				}
				//для мусорщиков начало STEP3
				else //if(gAreTank[nCarID[playerid]] != 1)
				{ 	//едем ставить бак
				    SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}У этой машине нет бака для сбора мусора! ");
				    SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}На вашей карте отмечен {FF0000}маркер{0080FF}, едьте к нему, чтобы установить бак.");
				    CP[playerid] = CP_TRASHMAN_1;
				    SetPlayerCheckpointEx(playerid, 2249.4053,-2015.4734,13.5469,CHECKPOINT_SIZE);

				 	/*checktimedeliver[playerid] = GetTickCount();
					format(strings, sizeof(strings), "При доставке быстрее чем за %d секунд у вас обнулится скилл.", 10);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);*/
				}
			}
   		}
   		//else if(PlayerInfo[playerid][pJob] == CARJACKER
		//   		|| PlayerInfo[playerid][pMember] == DoT) {	}
		else
		{
			//RemovePlayerFromVehicleEx(playerid);
			SendClientMessage(playerid, COLOR_GREY, "   Вы не Водитель Мусоровоза !");
			//return 1;
		}
	} //для мусорщиков конец
	return 1;
}

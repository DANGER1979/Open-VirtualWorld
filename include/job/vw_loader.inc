//для грузчиков
/*#define LOADER_DIALOG 52
#define LOADER6_DIALOG 	53

#define LOADER 			18
#define BAG_SLOT 		8//для грузчиков //для шахтёров //может быть у всех кто решил подработать
new JobAmmount[MAX_PLAYERS];//кол-во перетащеных мешков//кол-во добытой соли


enum
{
	CP_LOADER_1,//12
	CP_LOADER_2//13
}
//для грузчиков

//для грузчиков мешки 16
{true, 2060, 2172.8952,-2256.8610,12.4614,0.0,0.0,44.0},
{true, 2060, 2172.8945,-2256.8603,12.4614,0.0,0.0,43.9947},
{true, 2060, 2172.4230,-2256.4282,12.4609,0.0,0.0,47.2500},
{true, 2060, 2173.3183,-2257.3669,12.4614,0.0,0.0,43.75},
{true, 2060, 2172.7585,-2256.4985,12.7768,0.0,0.0,315.2498},
{true, 2060, 2172.4138,-2256.8581,12.7769,0.0,0.0,316.25},
{true, 2060, 2173.6186,-2257.3120,12.7769,0.0,0.0,136.0},
{true, 2060, 2173.2932,-2257.7080,12.7769,0.0,0.0,134.0},
{true, 2060, 2173.7319,-2257.7785,12.4650,0.0,0.0,42.0},
{true, 2060, 2172.6196,-2256.6328,13.0923,0.0,0.0,0.0},
{true, 2060, 2229.2980,-2286.0588,13.5317,0.0,0.0,226.0},
{true, 2060, 2229.6198,-2286.4582,13.5317,0.0,0.0,45.0},
{true, 2060, 2230.0061,-2286.8173,13.5317,0.0,0.0,44.0},
{true, 2060, 2230.3974,-2287.2316,13.5317,0.0,0.0,44.0},
{true, 2060, 2229.3540,-2286.5485,13.8072,0.0,0.0,134.0},
{true, 2060, 2230.2089,-2286.9531,13.8272,0.0,0.0,102.0},
//для грузчиков доски 3
{true, 2315, 2232.6596,-2285.5275,12.8755, 0.0,0.0,315.5},
{true, 2315, 2250.3325,-2260.8190,13.1822, 0.0,8.0,314.0},
{true, 2315, 2243.9631,-2267.1560,13.1603, 0.0,8.0,314.0},
*/




new Float:LoaderPoints[4][3] = {
//координаты места где брать мешок
//{2794.6780,-2448.7661,13.6320},// Точка 1
//{2788.1030,-2449.5293,13.6336},// точка 2
//{2787.9954,-2462.7532,13.6336},// точка 3
//{2779.1006,-2462.6292,13.6358}// точка 4

//координаты места куда нести коробку
{2794.2590,-2425.2559,13.6321},// Точка 1
{2786.0210,-2425.2439,13.6341},// точка 2
{2785.9568,-2410.0410,13.6341},// точка 3
{2793.8035,-2410.0559,13.6322}// точка 4
};


stock loader_OnGameModeInit()
{

	CreateDynamicObject(2029, 2128.29883, -2276.44678, 19.67409,   0.00000, 0.00000, 44.81977);// столики у грузчиков в инте
	CreateDynamicObject(1714, 2129.99976, -2276.76074, 19.53300,   0.00000, 0.00000, 285.19940);// столики у грузчиков в инте

	print("  vw_loader 1.0 By: DANGER1979");
	print("_____________________________________________");
	print(" ");
}

stock loader_OnPlayerConnect(playerid)
{
    RemoveBuildingForPlayer(playerid, 5171, 2124.9453, -2275.4531, 20.1406, 0.25); // у грузчиков в инте столики
}

stock loader_OnPlayerStateChange(playerid, newstate)
{
	if(newstate == PLAYER_STATE_WASTED)//выполняется сразу после смерти игрока
	{   //если ID нового состояния равно состоянию 7
		//для грузчиков STEP0
		if(PlayerInfo[playerid][pJob] == LOADER)
		{
			BizInfo[81][bWorker] --;
			PlayerInfo[playerid][pJob] = 0; gJobDuty[playerid] = 0;
			JobAmmount[playerid] = 0;
			if(IsPlayerAttachedObjectSlotUsed(playerid, BAG_SLOT)) RemovePlayerAttachedObject(playerid, BAG_SLOT);
			//ClearAnimations(playerid, 1);
			ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,0,0,0,0,1);
			//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			DisablePlayerCheckpointEx(playerid);
		}
	}
}

stock loader_OnPlayerInterior(playerid)
{
 	if(PlayerInfo[playerid][pJob] == LOADER)
 	{
 		BizInfo[81][bWorker] --;
	    PlayerInfo[playerid][pJob] = 0;	gJobDuty[playerid] = 0;
		JobAmmount[playerid] = 0;

		if(IsPlayerAttachedObjectSlotUsed(playerid, BAG_SLOT)) RemovePlayerAttachedObject(playerid, BAG_SLOT);
		//ClearAnimations(playerid, 1);
		ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,0,0,0,0,1);
		//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	    SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
	    DisablePlayerCheckpointEx(playerid);
	    SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Ты завершил работу грузчиком.");
	}
}

stock loader_OnEnterCheckpoint(playerid)
{
	if(CP[playerid] == CP_LOADER_1 && PlayerInfo[playerid][pJob] == LOADER)//для грузчиков STEP4 начало
	{//с кораблья на склад
 	 	if(IsPlayerInAnyVehicle(playerid))
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы НЕ должны находиться за рулём транспортного средства !");
		    return 1;
		}

		if(GetTickCount() < (checktimedeliver[playerid]+6000) && !gAnticheat[playerid])
		{
			format(strings, sizeof(strings), "%s[%d] Reset LoadSkill1:%d Mats:%d checktimedeliver:%d[%d] sec",
				PlayerName(playerid),playerid, PlayerInfo[playerid][pLoadSkill], JobAmmount[playerid], (GetTickCount()-checktimedeliver[playerid])/1000, 6);
			Log(JOB, strings);
			PlayerInfo[playerid][pLoadSkill] = 0;
			JobAmmount[playerid] = 0;
			SendClientMessage(playerid, COLOR_GREY, strings);
		    return 1;
		}
		/*format(strings, sizeof(strings), "%s[%d] LoadSkill:%d checktimedeliver:%d sec",
			PlayerName(playerid),playerid, PlayerInfo[playerid][pLoadSkill], (GetTickCount()-checktimedeliver[playerid])/1000);
		Log(JOB, strings);*/

        if(IsPlayerAttachedObjectSlotUsed(playerid, BAG_SLOT)) RemovePlayerAttachedObject(playerid, BAG_SLOT);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        DisablePlayerCheckpointEx(playerid);

		new skill = PlayerInfo[playerid][pLoadSkill];
		new level;
	    if(skill < 50) level = 1;//(1+1)*4=8
	    else if(skill >= 50 && skill < 100) level = 2;//(2+1)*4=12
	    else if(skill >= 100 && skill < 200) level = 3;//(3+1)*4=16
	    else if(skill >= 200 && skill < 400) level = 4;//(4+1)*4=20
	    else if(skill >= 400) level = 5;//(5+1)*4=24

		new package = level;//(level+1);//(level+1)*4;

		new rand;
		do
		{
			if(	(BizInfo[81][bMetal]+package) > LimitMetal &&
				(BizInfo[81][bTextiles]+package) > LimitTextiles &&
				(BizInfo[81][bProvisions]+package) > LimitProvisions &&
				(BizInfo[81][bTree]+package) > LimitTree &&
				(BizInfo[81][bFuel]+package) > LimitFuel)
			{
	  			format(strings, sizeof(strings), "~n~Full Stock in ~p~%s", BizInfo[81][bDiscription]);
				GameTextForPlayerEx(playerid, strings, 5000, 1);
				PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
				return 1;
			}
			rand = random(5);//0-4
			if(rand == 0 && (BizInfo[81][bMetal]+package) > LimitMetal)
			{
				rand = -1;
			}
			else if(rand == 1 && (BizInfo[81][bTextiles]+package) > LimitTextiles)
			{
				rand = -1;
			}
			else if(rand == 2 && (BizInfo[81][bProvisions]+package) > LimitProvisions)
			{
				rand = -1;
			}
			else if(rand == 3 && (BizInfo[81][bTree]+package) > LimitTree)
			{
				rand = -1;
			}
			else if(rand == 4 && (BizInfo[81][bFuel]+package) > LimitFuel)
			{
				rand = -1;
			}
		}
		while(rand == -1);//выйти из цикла как только rand != -1 станет, т.е. пройдёт проверку

        if(rand == 0) BizInfo[81][bMetal] += package;
        else if(rand == 1) BizInfo[81][bTextiles] += package;
        else if(rand == 2) BizInfo[81][bProvisions] += package;
        else if(rand == 3) BizInfo[81][bTree] += package;
		else if(rand == 4) BizInfo[81][bFuel] += package;

        JobAmmount[playerid] += package;

		//цена еденица сырья
		new Float: price = compcost*(100+1)/100.0;//15*(100.0+1)/100.0 = 15.15
		//ЗП за одну коробку
		new money = floatround(JobAmmount[playerid]*price, floatround_floor);//5*15.15 = 75.75

        format(strings, sizeof(strings), "Перенесено: {33AA33}%d кг{0080FF}. К Получке: {33AA33}~$%d", JobAmmount[playerid], money);
        SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
        SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы можете получить деньги в здании склада!");

		UpdateOceanDock();

		PlayerInfo[playerid][pLoadSkill] ++;
    	level = PlayerInfo[playerid][pLoadSkill];
		if(level == 50)
		{ SendClientMessage(playerid, COLOR_YELLOW, "* Ваш профессиональный уровень Грузчика теперь 2."); }
		else if(level == 100)
		{ SendClientMessage(playerid, COLOR_YELLOW, "* Ваш профессиональный уровень Грузчика теперь 3."); }
		else if(level == 200)
		{ SendClientMessage(playerid, COLOR_YELLOW, "* Ваш профессиональный уровень Грузчика теперь 4."); }
		else if(level == 400)
		{ SendClientMessage(playerid, COLOR_YELLOW, "* Ваш профессиональный уровень Грузчика теперь 5."); }
  	}
	else if(CP[playerid] == CP_LOADER_2 && PlayerInfo[playerid][pJob] == LOADER)//для грузчиков STEP4 начало
	{//со склада на корабль
 	 	if(IsPlayerInAnyVehicle(playerid))
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы НЕ должны находиться за рулём транспортного средства !");
		    return 1;
		}
		if(GetTickCount() < (checktimedeliver[playerid]+6000) && !gAnticheat[playerid])
		{
			format(strings, sizeof(strings), "%s[%d] Reset LoadSkill2:%d Mats:%d checktimedeliver:%d[%d] sec",
				PlayerName(playerid),playerid, PlayerInfo[playerid][pLoadSkill], JobAmmount[playerid], (GetTickCount()-checktimedeliver[playerid])/1000, 6);
			Log(JOB, strings);
			PlayerInfo[playerid][pLoadSkill] = 0;
			JobAmmount[playerid] = 0;
			SendClientMessage(playerid, COLOR_GREY, strings);
		    return 1;
		}
		/*format(strings, sizeof(strings), "%s[%d] LoadSkill:%d checktimedeliver:%d sec",
			PlayerName(playerid),playerid, PlayerInfo[playerid][pLoadSkill], (GetTickCount()-checktimedeliver[playerid])/1000);
		Log(JOB, strings);*/
        if(IsPlayerAttachedObjectSlotUsed(playerid, BAG_SLOT)) RemovePlayerAttachedObject(playerid, BAG_SLOT);
		//ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,0,0,0,0,1);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        DisablePlayerCheckpointEx(playerid);
		if(BizInfo[81][bProducts] <= 0)
		{
   			format(strings, sizeof(strings), "~r~Out Of Stock in ~p~%s", BizInfo[81][bDiscription]);
			GameTextForPlayerEx(playerid, strings, 5000, 1);
			PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
			return 1;
		}
		new package;
		new level = PlayerInfo[playerid][pLoadSkill];
		if(level < 50) { package = 3+random(20); } //3+random(20); }
		else if(level >= 50 && level < 100) { package = 3+random(30); }//3+random(30); }
		else if(level >= 100 && level < 200) { package = 3+random(40); }//3+random(40); }
		else if(level >= 200 && level < 400) { package = 3+random(50); }//3+random(50); }
		else if(level >= 400) { package = 100; }//100; }

		BizInfo[81][bProducts] -= numplayers/2*package;//иначе склад в 100 к продов будут всю жизнь разгружать
        JobAmmount[playerid] += package;//кол-во кг что перенёс грузчик
//цена еденица сырья
		new Float: price = compcost*(100+1)/100.0;//15*(100.0+1)/100.0 = 15.15 - цена одно кг
//за стоянку корабля грузчик делает 16 ходок 3*15.15*16 = 727.2
//за стоянку корабля грузчик делает 16 ходок 10*15.15*16  = 2424
		//ЗП за одну коробку
		new money = floatround(JobAmmount[playerid]*price, floatround_floor);
//за час корабль приезжает 24 раза 727.2*24  = 17452.8
//за час корабль приезжает 24 раза 2424*24 = 58176

 		new cost = floatround( numplayers/2*package * compcost*(100+100)/100.0 + package*price, floatround_ceil);//BizInfo[81][bBuyProd] - т.к. она равна 100% продажи на экспорт за море
//Выручка биза
//15 * 15*(100.0+100)/100.0 = 450 - с одной коробки
//450*16 = 7200 - с одной стоянки кораблья
//7200*24 = 172800 - за час
//172800-87264 = 85536 - чистая прибыль биза

//Выручка биза
//50 * 15*(100.0+100)/100.0 = 1500 - с одной коробки
//1500*16 = 24000 - с одной стоянки кораблья
//24000*24 = 576000 - за час
//576000-290880 = 285120 - чистая прибыль биза
		BizInfo[81][bTill] += cost;
		BizInfo[81][bExport] += cost;

        format(strings, sizeof(strings), "Перенесено: {33AA33}%d кг{0080FF} товаров. К Получке: {33AA33}~$%d", JobAmmount[playerid], money);
        SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
        SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы можете получить деньги в здании склада!");

		UpdateOceanDock();

		PlayerInfo[playerid][pLoadSkill] ++;
    	level = PlayerInfo[playerid][pLoadSkill];
		if(level == 50)
		{ SendClientMessage(playerid, COLOR_YELLOW, "* Ваш профессиональный уровень Грузчика теперь 2."); }
		else if(level == 100)
		{ SendClientMessage(playerid, COLOR_YELLOW, "* Ваш профессиональный уровень Грузчика теперь 3."); }
		else if(level == 200)
		{ SendClientMessage(playerid, COLOR_YELLOW, "* Ваш профессиональный уровень Грузчика теперь 4."); }
		else if(level == 400)
		{ SendClientMessage(playerid, COLOR_YELLOW, "* Ваш профессиональный уровень Грузчика теперь 5."); }
  	}
  	return 1;
}

stock loader_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(!response)
	{
		return 1;
	}
	if(dialogid == LOADER_DIALOG)	//для грузчиков STEP2 начало
	{   //ShowPlayerDialogEx(playerid, LOADER_DIALOG, DIALOG_STYLE_MSGBOX, "Раздевалка", dlgitem, "Да", "Нет");
		if(PlayerInfo[playerid][pJob] == LOADER)
		{
		    if(JobAmmount[playerid] != 0) return SendClientMessage(playerid, COLOR_GREY, "   Сначала ты должен получить зарплату в кассе офиса.");
			BizInfo[81][bWorker] --;
		    PlayerInfo[playerid][pJob] = 0;	gJobDuty[playerid] = 0;
		    DisablePlayerCheckpointEx(playerid);

			if(IsPlayerAttachedObjectSlotUsed(playerid, BAG_SLOT)) RemovePlayerAttachedObject(playerid, BAG_SLOT);
			ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,0,0,0,0,1);
		    SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);

			JobAmmount[playerid] = 0;
			UpdateOceanDock();
   		    SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Ты завершил работу грузчиком.");
		}
		else
		{
			BizInfo[81][bWorker] ++;
			PlayerInfo[playerid][pJob] = LOADER; gJobDuty[playerid] = 1;
			JobAmmount[playerid] = 0;
		    DisablePlayerCheckpointEx(playerid);

		    new skin = random(3);
		    if(skin == 1) SetPlayerSkinEx(playerid, 260);
		    else if(skin == 2) SetPlayerSkinEx(playerid, 27);
			else SetPlayerSkinEx(playerid, 16);
			SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Идите на грузовое судно, чтобы взять коробку.");
			SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Когда устанете, можете идти в здание, чтобы закончить работу");
		}
	}
	else if(dialogid == LOADER6_DIALOG)//для грузчиков STEP6
	{   //ShowPlayerDialogEx(playerid, LOADER6_DIALOG, DIALOG_STYLE_MSGBOX, "Касса", "Вы хотите получить зарплату и закончить работу?", "Да", "Нет");
		if(PlayerInfo[playerid][pJob] != LOADER)
		{
		    SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Переоденьтесь в раздевалке, чтобы начать работу.");
			return 1;
		}
		if(JobAmmount[playerid] <= 0)
		{
		 	SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Ты не занёс ни одной коробки.");
			return 1;
		}
		new Float: price = compcost*(100+1)/100.0;//15*(100+1)/100.0 = 15.15
		new money = floatround(JobAmmount[playerid]*price) + BizInfo[81][bSalary];//ЗП за одну коробку

		BizInfo[81][bTill] -= money;//порт оплачивается работу грузчиков
		BizInfo[81][bImport] += money;
	    //GivePlayerMoneyB(fbiz+81, playerid, money);//должно быть после PlayerInfo[playerid][pJob] = 0;
	    GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, money);

	    format(strings, sizeof(strings), "Работодатель: {0080FF}Ты получил {33AA33}$%d {0080FF}. Приходи еще.", money);
        SendClientMessage(playerid, COLOR_GREEN, strings);

		BizInfo[81][bWorker] --;
	    PlayerInfo[playerid][pJob] = 0;
		gJobDuty[playerid] = 0;
	    DisablePlayerCheckpointEx(playerid);

		if(IsPlayerAttachedObjectSlotUsed(playerid, BAG_SLOT)) RemovePlayerAttachedObject(playerid, BAG_SLOT);
		ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,0,0,0,0,1);
	    SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);

		JobAmmount[playerid] = 0;
		UpdateOceanDock();
	    SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Ты завершил работу грузчиком.");
    }//для грузчиков конец
	return 1;
}


stock loader_OnPlayerKeyStateChange(playerid)
{
	if(PlayerInfo[playerid][pJob] != LOADER) return 1;
	//if(CP[playerid] != 82) return 1;
    if( IsPlayerInRangeOfPoint(playerid, 2.0, 2813.5637,-2464.8813,13.8558)) return 1;
	if(IsPlayerAttachedObjectSlotUsed(playerid, BAG_SLOT))
	{
		RemovePlayerAttachedObject(playerid, BAG_SLOT);
		//ClearAnimations(playerid, 1);
		ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,0,0,0,0,1);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		DisablePlayerCheckpointEx(playerid);
       	SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Ты бросил коробку!");
	}
	return 1;
}

stock loader_PlayerEnterPickUp(playerid, pickupid)
{
	//--------------------------------------------------------------------------
//для грузчиков STEP1 начало
	if(	pickupid == PickupID[9] &&
		IsPlayerInRangeOfPoint(playerid, 2.1, Pickups[pickupid][p_x],Pickups[pickupid][p_y],Pickups[pickupid][p_z]) )
	{
		if(PlayerInfo[playerid][pInt] != 0) return 1;
		if(PlayerInfo[playerid][pVirtual] != 0) return 1;
		if(PlayerInfo[playerid][pLocal] != FREEROAM) return 1;
		if(gOnDuty[playerid])
		{   //если коп и не на дежурстве и не в розыске
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете взять эту работу, когда вышли на службу (USE: /duty)!!!");
			return 1;
		}
		if(PlayerInfo[playerid][pJob] != 0 && PlayerInfo[playerid][pJob] != LOADER)
		{
			format(strings, sizeof(strings), "Работодатель: {0080FF}Вы на работе {FFFFFF}%s{0080FF}. Чтобы уволиться (USE: /quitjob).", GetPlayerJob(playerid) ); //сообщение
			SendClientMessage(playerid, COLOR_GREEN, strings);
			return 1;
		}
		if(gJobDuty[playerid])
		{   //если коп и не на дежурстве и не в розыске
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете взять эту работу, когда вышли на дежурство!!!");
			return 1;
		}
        /*if(BizInfo[81][bTill] <= 0)
        {
      		SendClientMessage(playerid, COLOR_GREY, "   Извените, Порт закрыт. В кассе нет денег.");
      		return 1;
        }*/
		if(PlayerInfo[playerid][pJob] == LOADER)
		{
			ShowPlayerDialogEx(playerid, LOADER_DIALOG, DIALOG_STYLE_MSGBOX, "Раздевалка грузчиков", "Вы уже приступили к работе грузчика!\nВы хотите закончить работу?","Да","Нет");
		}
		else
		{
			new dlgitem[] = "1. Чтобы начать работу грузчика переоденьтесь в рабочую одежду\
\n2. Затем отправляйтесь на грузовое судно за коробкой\
\n3. Отнесите коробку на склад и идите за новой\
\n4. Когда отнесёте достаточное вам кол-во коробок\
\nприходите в кассу за зарплатой, она находится рядом с раздевалкой\
\n\nВы хотите переодеться, чтобы начать работу?";
			ShowPlayerDialogEx(playerid, LOADER_DIALOG, DIALOG_STYLE_MSGBOX, "Раздевалка грузчиков", dlgitem, "Да", "Нет");
		}
		//gDialogStatus[playerid][3] = 3;//даём 3 секунд таймера для выхода из пикапа
		//return 1;
	}
	//для грузчиков STEP5
	else if(pickupid == PickupID[10] &&
			IsPlayerInRangeOfPoint(playerid, 2.1, Pickups[pickupid][p_x],Pickups[pickupid][p_y],Pickups[pickupid][p_z]) )
	{
		if(PlayerInfo[playerid][pJob] == LOADER)//if(PlayerInfo[playerid][pJob] != 19)
		{
			return SendClientMessage(playerid, COLOR_GREY, "   Вы не Грузчик !");
		}
		if(PlayerInfo[playerid][pJob] == 0)//if(!gJobDuty[playerid])
		{
			//SendClientMessage(playerid, COLOR_GREY, "   Вы ещё не приступили к работе !");
			return 1;
		}
		ShowPlayerDialogEx(playerid, LOADER6_DIALOG, DIALOG_STYLE_MSGBOX, "Касса грузчиков", "Вы хотите получить зарплату и закончить работу?", "Да", "Нет");
		//return 1;
	}
	//для грузчиков STEP0
	else if(pickupid == PickupID[11] && IsPlayerInRangeOfPoint(playerid, 2.1, Pickups[pickupid][p_x],Pickups[pickupid][p_y],Pickups[pickupid][p_z]) )
	{
		//if(PlayerInfo[playerid][pJob] != 19) return SendClientMessage(playerid, COLOR_GREY, "   Вы не Грузчик !");
		new dlgitem[590];
		strcat(dlgitem, "1. Чтобы начать работу грузчика зайдите в бытовку и переоденьтесь в рабочую одежду.");
		strcat(dlgitem, "\n2. Затем отправляйтесь на грузовое судно за коробкой.");
		strcat(dlgitem, "\n3. Отнесите коробку на склад и идите за новой.");
		strcat(dlgitem, "\n4. Когда отнесёте достаточное вам кол-во коробок,");
		strcat(dlgitem, "\nприходите в кассу за зарплатой, она находится в здании Склада.");
		strcat(dlgitem, "\nС прокачкой навыка ваш заработок будет расти");
		strcat(dlgitem, "\nПосмотреть навык можно командой /skill выбрав в меню пункт 18: Грузчик.");
		strcat(dlgitem, "\n\nВы всегда сможете здесь подзаработать денег");
		ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, "Грузчик. Помощь по работе", dlgitem, "ОК", "");
		//return 1;
	}
//для грузчиков STEP3
	else if(pickupid == PickupID[12] && IsPlayerInRangeOfPoint(playerid, 2.1, Pickups[pickupid][p_x],Pickups[pickupid][p_y],Pickups[pickupid][p_z]))
 	{
		if(PlayerInfo[playerid][pJob] != LOADER)
		{
			//SendClientMessage(playerid, COLOR_GREY, "   Вы не Грузчик !");
			return 1;
		}
		if(CP[playerid] != 0)
  	    {
  	        SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Ты уже взял коробку.");
  	        return 1;
		}
		if(BizInfo[81][bTill] <= (500000+BizInfo[81][bSalary]))
        {
      		SendClientMessage(playerid, COLOR_GREY, "   Извените, в кассе меньше $500000 для поддержания полной работоспобности.");
      		SendClientMessage(playerid, COLOR_GREY, "   Попробуйте заработать на доставке коробок со склада на корабль.");
      		return 1;
        }
  	    if( IsObjectMoving(gMainShipObjectId) )
  	    {
  	        //SendClientMessage(playerid, COLOR_YELLOW, "Судно в пути (USE: /stopship)");
  	        SendClientMessage(playerid, COLOR_YELLOW, "Судно в пути, подождите его у причала.");
  	        return 1;
		}
        new rand = random(sizeof(LoaderPoints));
        CP[playerid] = CP_LOADER_1;
        SetPlayerCheckpointEx(playerid, LoaderPoints[rand][0],LoaderPoints[rand][1],LoaderPoints[rand][2], 2.0);
        //ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,1,0,0,1,1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
        //SetPlayerAttachedObjectEx(playerid, BAG_SLOT, 2060, Spine, 0.11,0.36,0.0, 0.0,90.0);//мешок
        SetPlayerAttachedObjectEx(playerid, BAG_SLOT, 1220, Spine, 0.3720,0.6190,-0.0269, 0.00,9.10,4.99, 1.00,1.00,1.00);//коробка
/*
playerid	ID of the player you want to attach the object to.
index	the index of the object
modelid	The model you want to use.
bone	The bone you want to attach the object to.
fOffsetX	(optional) X axis offset for the object position.
fOffsetY	(optional) Y axis offset for the object position.
fOffsetZ	(optional) Z axis offset for the object position.
fRotX	(optional) X axis rotation of the object.
fRotY	(optional) Y axis rotation of the object.
fRotZ	(optional) Z axis rotation of the object.
fScaleX	(optional) X axis scaling of the object.
fScaley	(optional) Y axis scaling of the object.
fScaleZ	(optional) Z axis scaling of the object.
*/
		checktimedeliver[playerid] = GetTickCount();
		format(strings, sizeof(strings), "При доставке быстрее чем за %d секунд у вас обнулится скилл.", 8);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);

        SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Ты взял коробку. Неси её на склад.");
		//return 1;
	}
//для грузчиков STEP3
	else if(pickupid == PickupID[13] && IsPlayerInRangeOfPoint(playerid, 2.1, Pickups[pickupid][p_x],Pickups[pickupid][p_y],Pickups[pickupid][p_z])
		&& PlayerInfo[playerid][pJob] == LOADER)
 	{
		if(BizInfo[81][bProducts] <= 0)
		{
   			format(strings, sizeof(strings), "~r~Out Of Stock in ~p~%s", BizInfo[81][bDiscription]);
			GameTextForPlayerEx(playerid, strings, 5000, 1);
			PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
			return 1;
		}
  	    if( IsObjectMoving(gMainShipObjectId) )
  	    {
  	        //SendClientMessage(playerid, COLOR_YELLOW, "Судно в пути (USE: /stopship)");
  	        SendClientMessage(playerid, COLOR_YELLOW, "Судно в пути, подождите пока оно не прибудет в порт.");
  	        return 1;
		}
		if(CP[playerid] != 0)
  	    {
  	        SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Ты уже взял коробку.");
  	        return 1;
		}
        CP[playerid] = CP_LOADER_2;
        SetPlayerCheckpointEx(playerid, 2813.5637,-2464.8813,13.8558, 2.0);
        //ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,1,0,0,1,1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
        SetPlayerAttachedObjectEx(playerid, BAG_SLOT, 1220, Spine, 0.3720,0.6190,-0.0269, 0.00,9.10,4.99, 1.00,1.00,1.00);//коробка

 		checktimedeliver[playerid] = GetTickCount();
		format(strings, sizeof(strings), "При доставке быстрее чем за %d секунд у вас обнулится скилл.", 8);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);

        SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Ты взял коробку. Неси её на грузовое судно.");
		//return 1;
	}//для грузчиков конец
	return 1;
}

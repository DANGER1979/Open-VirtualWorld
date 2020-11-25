//для шахтёров
new bool:gMinerGetSalt[MAX_PLAYERS];//наличие телеги //перевести на PVar
//new MinerSkill[MAX_PLAYERS];//скилл //перевести на PVar

stock miner_OnGameModeInit()
{
	print("  vw_miner 1.0 By: DANGER1979");
	print("_____________________________________________");
	print(" ");
}

stock UpdateMine()//для шахтёров
{
    new strtmp[68 + 10+10];
 	format(strtmp, sizeof(strtmp), "[ Шахта ]\n\n{FF6600}Соли: {FFFFFF}%d{FF6600}\nВ Кассе: {33AA33}$%d", SBizInfo[55][sbProducts], SBizInfo[55][sbTill]);
	Update3DTextLabelText(MineInfo, 0xEEEE88FF, strtmp);
}

//для шахтёров STEP6
stock GivePlayerSalt(playerid)
{//ф-ии убирания кирки
	if(IsPlayerAttachedObjectSlotUsed(playerid, DUTY_SLOT)) RemovePlayerAttachedObject(playerid, DUTY_SLOT);//удаляем кирку

	TogglePlayerControllableEx(playerid, 1);//освободили
	//ClearAnimations(playerid, 1);
	//ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,0,0,0,0,1);
	ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,0,0,0,1,1000);
	//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

	gGameText[playerid] = 0;
    gMinerGetSalt[playerid] = true;//получили соль

    SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы добыли соль. Теперь отвезите её на склад.");

    if(!IsPlayerAttachedObjectSlotUsed(playerid, DUTY_SLOT)) SetPlayerAttachedObjectEx(playerid, DUTY_SLOT, 1458, Spine, -1.0348,1.1165,-0.0651, 76.4801,75.7815,280.9525, 0.5755,0.6045,0.6241);
    if(!IsPlayerAttachedObjectSlotUsed(playerid, BAG_SLOT)) SetPlayerAttachedObjectEx(playerid, BAG_SLOT, 3930, Spine, -0.275758,1.505280,-0.1000, 0.0,0.0,0.0, 1.0,1.0,1.0);

	checktimedeliver[playerid] = GetTickCount();
    format(strings, sizeof(strings), "При доставке быстрее чем за %d секунд у вас обнулится скилл.", 10);
    SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);

    CP[playerid] = CP_MINER;//для шахтёров STEP7
    SetPlayerCheckpointEx(playerid, 585.5980,874.7810,-42.4970, 2.0);
	ApplyAnimation(playerid, "PED","IDLE_chat",4.1,0,0,0,1,1000);//чтобы во время бега не махал руками
}

stock miner_OnPlayerConnect(playerid)
{
//для шахтёров
	gMinerGetSalt[playerid] = false;
}


stock miner_OnEnterCheckpoint(playerid)
{
//для шахтёров начало
	if(CP[playerid] == CP_MINER && PlayerInfo[playerid][pJob] == MINER)//для шахтёров STEP7
	{
 	 	if(IsPlayerInAnyVehicle(playerid))
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вы НЕ должны находиться за рулём транспортного средства !");
		    return 1;
		}
		if(GetTickCount() < (checktimedeliver[playerid]+10000) && !gAnticheat[playerid])
		{
			format(strings, sizeof(strings), "%s[%d] Reset MinerSkill:%d Mats:%d checktimedeliver:%d[%d] sec",
				PlayerName(playerid),playerid, PlayerInfo[playerid][pMinerSkill], JobAmmount[playerid], (GetTickCount()-checktimedeliver[playerid])/1000, 12);
			Log(JOB, strings);
			PlayerInfo[playerid][pMinerSkill] = 0;
			JobAmmount[playerid] = 0;
			SendClientMessage(playerid, COLOR_GREY, strings);
		    return 1;
		}
		//format(strings, sizeof(strings), "%s[%d] MinerSkill:%d checktimedeliver:%d sec",
		//	PlayerName(playerid),playerid, PlayerInfo[playerid][pMinerSkill], (GetTickCount()-checktimedeliver[playerid])/1000);
		//Log(JOB, strings);

		//ApplyAnimation(playerid, "CLOTHES","CLO_Buy",4.1,0,0,0,0,0);
	    if(IsPlayerAttachedObjectSlotUsed(playerid, DUTY_SLOT)) RemovePlayerAttachedObject(playerid, DUTY_SLOT);
	    if(IsPlayerAttachedObjectSlotUsed(playerid, BAG_SLOT)) RemovePlayerAttachedObject(playerid, BAG_SLOT);
		//ClearAnimations(playerid, 1);
		ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,0,0,0,0,1);
		//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

	    DisablePlayerCheckpointEx(playerid);

		gMinerGetSalt[playerid] = false;
	    SetPlayerAttachedObjectEx(playerid, DUTY_SLOT, 18634, Right_hand, 0.0782,0.0,0.1108, 298.8973,264.1268,193.3505, 1.0,1.0,1.0);

 		//new price = SBizInfo[55][sbSalary];
 		new Float: price = compcost*(100+SBizInfo[55][sbBuyProd])/100.0;
 		new weight = JobAmmount[playerid]/2;//JobAmmount = (80 - 240)/10 = 8-10 кг
		new money = floatround(weight*price) + SBizInfo[55][sbSalary];
		if(SBizInfo[55][sbTill] > money)
		{
		   	PlayerInfo[playerid][pMinerSkill] ++;//MinerSkill[playerid] ++;
			if(PlayerInfo[playerid][pMinerSkill] == 50)
			{ SendClientMessage(playerid, COLOR_YELLOW, "* Ваш Навык Шахтёра теперь Уровня 2, Вы можете добывать больше соли."); }
			else if(PlayerInfo[playerid][pMinerSkill] == 100)
			{ SendClientMessage(playerid, COLOR_YELLOW, "* Ваш Навык Шахтёра теперь Уровня 3, Вы можете добывать больше соли."); }
			else if(PlayerInfo[playerid][pMinerSkill] == 200)
			{ SendClientMessage(playerid, COLOR_YELLOW, "* Ваш Навык Шахтёра теперь Уровня 4, Вы можете добывать больше соли."); }
			else if(PlayerInfo[playerid][pMinerSkill] == 400)
			{ SendClientMessage(playerid, COLOR_YELLOW, "* Ваш Навык Шахтёра теперь Уровня 5, Вы можете добывать больше соли."); }

	 		//new Float: price = compcost*(100+SBizInfo[55][sbBuyProd])/100.0;

			SBizInfo[55][sbProducts] += weight;
			SBizInfo[55][sbTill] -= money;
			SBizInfo[55][sbImport] += money;
			//GivePlayerMoneyB(fsbiz+55, playerid, money); ///замените на свою выдачу денег
			GivePlayerMoneyB(fjob+PlayerInfo[playerid][pJob], playerid, money);
			UpdateMine();

	  		//new strings[123+10+10];
	    	format(strings, sizeof(strings), "Работодатель: {0080FF}Вы привезли {FFFFFF}%d {0080FF}кг соли и заработали {33AA33}$%d", weight, money);
	        SendClientMessage(playerid, COLOR_GREEN, strings);
        }
        else
        {
      		SendClientMessage(playerid, COLOR_GREY, "   Извените, в кассе нет больше денег.");
        }
        JobAmmount[playerid] = 0;
		SendClientMessage(playerid, COLOR_GREEN,  "Работодатель: {0080FF}Вы можете закончить работу в раздевалке!");
//TestLog(OPTIM, "OnPlayerEnterCheckpoint1.6 ", GetTickCount(), timers);
  	}
//для шахтёров конец
	return 1;
}

stock miner_OnPlayerKeyStateChange(playerid)
{
	//для шахтёров STEP4
	if(PlayerInfo[playerid][pJob] == MINER)
	{//добыча соли //JobAmmount[playerid] == 0 && второй раз не сработает
		if(PlayerInfo[playerid][pLocal] != 239) return 1;
		if(gMinerGetSalt[playerid] == true) return 1;
		if(!IsPlayerInRangeOfPoint(playerid, 2, 636.1420,863.7570,-85.6729)
		&& !IsPlayerInRangeOfPoint(playerid, 2, 637.7719,866.2349,-85.2590)
		&& !IsPlayerInRangeOfPoint(playerid, 2, 638.2020,868.3159,-85.6510)) return 1;

		new skill = PlayerInfo[playerid][pMinerSkill];//MinerSkill[playerid];
		new level;
	    if(skill < 50) level = 1;//(1+1)*4=8
	    else if(skill >= 50 && skill < 100) level = 2;//(2+1)*4=12
	    else if(skill >= 100 && skill < 200) level = 3;//(3+1)*4=16
	    else if(skill >= 200 && skill < 400) level = 4;//(4+1)*4=20
	    else if(skill >= 400) level = 5;//(5+1)*4=24

		new limit = 1*(level+1)*4;
		gGameText[playerid] = 1; SetPlayerGameTextScale(playerid, "Miner Strike", JobAmmount[playerid], limit);
		JobAmmount[playerid] ++;
		if(JobAmmount[playerid] >= limit)
		{   //JobAmmount = 80 - 240
			GivePlayerSalt(playerid);//для шахтёров STEP6
		}
		else
		{
			ApplyAnimation(playerid, "BASEBALL", "Bat_4", 4.1, 0, 0, 0, 1, 0);//чтобы не махал кулаком при движении
  			PlaySoundForPlayer(playerid, SOUND_BASEBALL_BAT_HIT_PED);
		}
	}
	return 1;
}

stock miner_PlayerEnterPickUp(playerid, pickupid)
{
	//--------------------------------------------------------------------------
//для шахтёров STEP1
	if(pickupid == PickupID[0] && IsPlayerInRangeOfPoint(playerid, 2.1, Pickups[pickupid][p_x],Pickups[pickupid][p_y],Pickups[pickupid][p_z]) )
	{
		if(PlayerInfo[playerid][pInt] != 0) return 1;
		if(PlayerInfo[playerid][pVirtual] != 0) return 1;
		if(PlayerInfo[playerid][pLocal] != FREEROAM) return 1;
		if(gOnDuty[playerid])
		{   //если коп и не на дежурстве и не в розыске
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете взять эту работу, когда вышли на службу!!!!!");
			return 1;
		}
		/*if(gJobDuty[playerid])
		{   //если коп и не на дежурстве и не в розыске
			SendClientMessage(playerid, COLOR_GREY, "   Вы не можете взять эту работу, когда вышли на дежурство!!!");
			return 1;
		}*/
		if(PlayerInfo[playerid][pJob] != 0 && PlayerInfo[playerid][pJob] != MINER)
		{
			format(strings, sizeof(strings), "Работодатель: {0080FF}Вы на работе {FFFFFF}%s{0080FF}. Чтобы уволиться (USE: /quitjob).", GetPlayerJob(playerid) ); //сообщение
			SendClientMessage(playerid, COLOR_GREEN, strings);
			return 1;
		}
        if(SBizInfo[55][sbTill] <= 0)
        {
      		SendClientMessage(playerid, COLOR_GREY, "   Извените, шахта не работает. В кассе нет денег.");
      		return 1;
        }
		if(gJobDuty[playerid]) //if(PlayerInfo[playerid][pJob] == MINER && gJobDuty[playerid])
		{
			ShowPlayerDialogEx(playerid, MINER_DIALOG, DIALOG_STYLE_MSGBOX, "Раздевалка шахтёров", "Вы уже приступили к работе шахтёра!\nВы хотите закончить работу?","Да","Нет");
		}
  		else //if(PlayerInfo[playerid][pJob] == 0)
        {
	        new dlgitem[12*60];
	        strcat(dlgitem, "1. Чтобы начать работу шахтера необходимо пройти в ");
	        strcat(dlgitem, "раздевалку, \nгде вы переоденетесь и возмёте инструмент.");
	        strcat(dlgitem, "\n2. Затем отправляйтесь в шахту для добычи соли");
	        strcat(dlgitem, "\n3. Войдя в шахту, проследуйте к одному из мест добычи.");
	        strcat(dlgitem, "\n4. Для добычи соли используйте ЛКМ(Левую Кнопку Мыши)");
	        strcat(dlgitem, "\n5. После того, как вы совершите необходимое кол-во ударов, ");
	        strcat(dlgitem, "\nвам будет выдана телега.");
	        strcat(dlgitem, "\n6. Её необходимо доставить на склад обозначенный маркером.");
	        strcat(dlgitem, "\n7. Для окончания работы проследуйте в раздевалку.");
	        strcat(dlgitem, "\n\nВы хотите переодеться, чтобы начать работу?");
	        ShowPlayerDialogEx(playerid, MINER_DIALOG, DIALOG_STYLE_MSGBOX, "Раздевалка шахтёров", dlgitem, "Да", "Нет");//для шахтёров STEP2
		}
		//return 1;
    }//для шахтёров конец
    return 1;
}

stock miner_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != MINER_DIALOG) return 1;//для шахтёров STEP2
    if(!response) return 1;
	if(PlayerInfo[playerid][pJob] == MINER)
	{
		gMinerGetSalt[playerid] = false;
		SetPlayerSkinEx(playerid, PlayerInfo[playerid][pModel]);
	    if(IsPlayerAttachedObjectSlotUsed(playerid, DUTY_SLOT)) RemovePlayerAttachedObject(playerid, DUTY_SLOT);
	    if(IsPlayerAttachedObjectSlotUsed(playerid, BAG_SLOT)) RemovePlayerAttachedObject(playerid, BAG_SLOT);
		DisablePlayerCheckpointEx(playerid);
		if(gJobDuty[playerid]) SBizInfo[55][sbWorker] --;
		PlayerInfo[playerid][pJob] = 0;	gJobDuty[playerid] = 0;
        SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Вы окончили работу.");
	}
	else
	{
		gMinerGetSalt[playerid] = false;
    	SBizInfo[55][sbWorker] ++;
		PlayerInfo[playerid][pJob] = MINER; gJobDuty[playerid] = 1;
		//PlayerSavedSkin[playerid] = GetPlayerSkin(playerid);
		SetPlayerSkinEx(playerid, 27);
	    SetPlayerAttachedObjectEx(playerid, DUTY_SLOT, 18634, Right_hand, 0.0782,0.0,0.1108, 298.8973,264.1268,193.3505, 1.0,1.0,1.0);//кирка
		SetPlayerCheckpointEx(playerid, 546.3120,880.2810,-41.1199, 2.0);//чекпоинт на вход в шахту
        //ApplyAnimation(playerid, "BASEBALL","Bat_4",4.1,0,0,0,0,1);
        //ApplyAnimation(playerid, "FIGHT_B","FightB_G",4.1,0,0,0,0,1);
        ApplyAnimation(playerid, "CLOTHES", "CLO_Buy",4.1,0,1,1,0,0);
		SendClientMessage(playerid, COLOR_GREEN, "Работодатель: {0080FF}Отправляйтесь в шахту за солью.");
	}
	return 1;
}

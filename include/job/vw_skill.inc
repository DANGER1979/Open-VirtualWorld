stock GetPlayerSkill(playerid, job, &jobskill, &joblevel)//вызывается по команде /stats
{
	new jobname[20];
    if(job == MINER) { jobname = "Шахтёр"; joblevel = PlayerInfo[playerid][pMinerSkill]; }//Miner//Detective
	else if(job == LAWYER) { jobname = "Адвокат";  joblevel = PlayerInfo[playerid][pLawSkill]; }//Lawyer
	else if(job == ROADWORKER) { jobname = "Ремонтник Дорог"; joblevel = PlayerInfo[playerid][pRoadSkill]; }//RoadWorker
	//else if(job == DRUGDEALER) { jobname = "Наркодилер";  joblevel = PlayerInfo[playerid][pDrugsSkill]; }//Drugs Dealer
	else if(job == CARJACKER) { jobname = "Автоугонщик"; joblevel = PlayerInfo[playerid][pJackSkill]; }//Car Jacker
	else if(job == 6) { jobname = "ProfSkill"; joblevel = PlayerInfo[playerid][pProfSkill]; }//News Reporter
	else if(job == CARMECHANIC) { jobname = "АвтоМеханик"; joblevel = PlayerInfo[playerid][pMechSkill]; }//Car Mechanic для автомехаников исправлено
	else if(job == FARMER) { jobname = "Фермер"; joblevel = PlayerInfo[playerid][pFarmSkill]; }//Body Guard
	else if(job == ARMSDEALER) { jobname = "Оружейник"; joblevel = PlayerInfo[playerid][pGunSkill]; }//Gun Dealer
	else if(job == CARDEALER) { jobname = "Автодилер"; joblevel = PlayerInfo[playerid][pCarSkill]; }//Car Dealer
	else if(job == INKASSATOR) { jobname = "Инкассатор";joblevel = PlayerInfo[playerid][pInkasSkill]; }//Inkassator
	else if(job == BOOKMAKER) { jobname = "Букмекер";joblevel = PlayerInfo[playerid][pBookmakerSkill]; }//Boxer
	else if(job == TAXIDRIVER) { jobname = "Таксист"; joblevel = PlayerInfo[playerid][pTaxiSkill]; }//Taxi
	else if(job == BUSDRIVER) { jobname = "Водитель автобуса"; joblevel = PlayerInfo[playerid][pBusSkill]; }//для автобусников
	else if(job == PAPERBOY) { jobname = "Курьер"; joblevel = PlayerInfo[playerid][pCourierSkill]; }//для курьера
	else if(job == TRUCKER) { jobname = "Дальнобойщик"; joblevel = PlayerInfo[playerid][pTruckSkill]; }//Trucker
	else if(job == TRASHMAN) { jobname = "Мусорщик"; joblevel = PlayerInfo[playerid][pTrashSkill]; }//TrashMaster
	else if(job == LOADER) { jobname = "Грузчик";joblevel = PlayerInfo[playerid][pLoadSkill]; }//Loader
	else if(job == WOODSMAN) { jobname = "Дровосек"; joblevel = PlayerInfo[playerid][pWoodSkill]; }//Woodsman
	//else if(job == FISHER) { jobname = "Рыбалов"; joblevel = PlayerInfo[playerid][pFishSkill]; }//Fisher
	else if(job == FIREMAN) { jobname = "Пожарный"; joblevel = PlayerInfo[playerid][pFireSkill]; }//FireFighter
	//else if(job == COOKER) { jobname = "Повар"; joblevel = PlayerInfo[playerid][pCookSkill]; }//Cooker
	else joblevel = 0;

	if(joblevel < 50) jobskill = 1;
	else if(joblevel >= 50 && joblevel < 100) jobskill = 2;
	else if(joblevel >= 100 && joblevel < 200) jobskill = 3;
	else if(joblevel >= 200 && joblevel < 400) jobskill = 4;
	else if(joblevel >= 400) jobskill = 5;

	//----------------------------------------------------------------------
	if(job == DRUGDEALER)//для наркодилеров
	{   //Drugs Dealer
		jobname = "Наркодилер";
	    joblevel = PlayerInfo[playerid][pDrugsSkill];
		if(joblevel < 250) jobskill = 1;
		else if(joblevel >= 250 && joblevel <= 500) jobskill = 2;
		else if(joblevel >= 500 && joblevel <= 1000) jobskill = 3;
		else if(joblevel >= 1000 && joblevel <= 2000) jobskill = 4;
		else if(joblevel >= 2000) jobskill = 5;
	}
	else if(job == FISHER)//Fishing для рыбалки исправлено
	{
	 	jobname = "Рыбалов";
	    joblevel = PlayerInfo[playerid][pFishSkill];
		if(joblevel < 50) jobskill = 1;
		else if(joblevel >= 50 && joblevel < 250) jobskill = 2;
		else if(joblevel >= 250 && joblevel < 500) jobskill = 3;
		else if(joblevel >= 500 && joblevel < 1000) jobskill = 4;
		else if(joblevel >= 1000) jobskill = 5;
	}
	else if(job == COOKER)//Cooking для готовки
	{
		jobname = "Повар";
	    joblevel = PlayerInfo[playerid][pCookSkill];
		if(joblevel < 50) jobskill = 1;
		else if(joblevel >= 50 && joblevel < 100) jobskill = 2;
		else if(joblevel >= 100 && joblevel < 200) jobskill = 3;
		else if(joblevel >= 200 && joblevel < 400) jobskill = 4;
		else if(joblevel >= 400) jobskill = 5;
	}
	return jobname;
}

stock SkillInfo(playerid)
{
	new listitems[(82 + 1+20+1+4)*COOKER];
	new JobSkill, JobLevel;
	new JobName[20];
	new giveplayerid = GetPVarInt(playerid, "ForPlayerID");

    strcat(listitems, "#\t{00FF00}Работа \t{0080FF}Rank \t{0080FF}Skill\n");
	for(new j=1; j<=COOKER; j++)	{
		JobName = GetPlayerSkill(giveplayerid, j, JobLevel, JobSkill);
		format(listitems, sizeof(listitems), "%s{FFFFFF}%d:\t{00FF00}%s \t{0080FF}%d \t{0080FF}%d\n",
			listitems, j, JobName, JobLevel, JobSkill);
	}
	//format(listitems, sizeof(listitems), "%s{FFFFFF}%d:\t{00FF00}%s \t\t{0080FF}Rank:{FFFFFF}%d \t{0080FF}Skill: {FFFFFF}%d\n",
	//		listitems, COOKER, "ProfSkill", JobLevel, PlayerInfo[playerid][pProfSkill]);
	/*strcat(listitems, "{FFFFFF}1:\t{00FF00}Шахтёр\n{FFFFFF}2: \t{00FF00}Адвокат\n{FFFFFF}3: \t{00FF00}Ремонтник\n{FFFFFF}4: \t{00FF00}НаркоДилер\n{FFFFFF}5: \t{00FF00}АвтоУгонщик");
	strcat(listitems, "\n{FFFFFF}6: \t{00FF00}ProfSkill\n{FFFFFF}7: \t{00FF00}АвтоМеханик\n{FFFFFF}8: \t{00FF00}Фермер\n{FFFFFF}9: \t{00FF00}Оружейник\n{FFFFFF}10: \t{00FF00}АвтоДилер");
	strcat(listitems, "\n{FFFFFF}11: \t{00FF00}Инкассатор\n{FFFFFF}12: \t{00FF00}Букмекер\n{FFFFFF}13: \t{00FF00}Таксист\n{FFFFFF}14: \t{00FF00}Водитель Автобуса\n{FFFFFF}15: \t{00FF00}Курьер");
	strcat(listitems, "\n{FFFFFF}16: \t{00FF00}Дальнобойщик\n{FFFFFF}17: \t{00FF00}Водитель мусоровоза\n{FFFFFF}18: \t{00FF00}Грузчик\n{FFFFFF}19: \t{00FF00}Дровосек\n{FFFFFF}20: \t{00FF00}Рыболов");
	strcat(listitems, "\n{FFFFFF}21: \t{00FF00}Пожарный\n{FFFFFF}22: \t{00FF00}Повар");*/
	
	new caption[25+MAX_PLAYER_NAME+3];
    format(caption, sizeof(caption), "Skill Info игрока %s[%d]", PlayerName(giveplayerid), giveplayerid);
	//ShowPlayerDialogEx(playerid, BACKPLMENU_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, caption, listitems, "OK", "Назад");
	//ShowPlayerDialogGap(playerid, SKILL_DIALOG, DIALOG_STYLE_LIST, "Skill Info", listitems, "OK", "Cancel");
	ShowPlayerDialogEx(playerid, SKILL_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, caption, listitems, "OK", "Назад");
}


stock skill_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
		if(dialogid != SKILL_DIALOG) return 1;
		//#pragma unused inputtext
		SetPVarInt(playerid, "gShowDialog", -1);
		if(!response)
		{
			DeletePVar(playerid, "Action");
			/*DeletePVar(playerid, "InputValue");
			DeletePVar(playerid, "InputCounter");
			DeletePVar(playerid, "ForPlayerID");*/
			//new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
			PlayerMenu(playerid);
			return 1;
		}
		new msgitem[256+1];
		//new Float:pX, Float:pY, Float:pZ, Float:pA; //new Float:ang;
		//new Float:vX, Float:vY, Float:vZ;//, Float:vA;
		new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
//==============================================================================
		if(GetPVarInt(playerid, "Action") == 0)
		{//если операция ещё не выбрана, т.е. это ввод первого параметра
		    //не забыть обнулить при окончанию ввода параметров
			//if(dialogid == DEVELOPER_DIALOG)
			SetPVarInt(playerid, "Action", listitem+1);//записали выбранную операцию
			//else  SetPVarInt(playerid, "Action", listitem+100);//записали выбранную операцию

			DeletePVar(playerid, "InputCounter");//очистили от предыдущих операций
		}
		new operation = GetPVarInt(playerid, "Action");
//------------------------------------------------------------------------------
	    if(operation == MINER)
		{
		    new level = PlayerInfo[playerid][pMinerSkill];//"Шахтер Rank:5 Skill: 1356" и т.д.
			if(level < 50) { 	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Шахтёра = 1.");
								format(msgitem, sizeof(msgitem), "Bы должны перевести %d тачек с солью для поднятия уровня.", 50 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 50 && level < 100) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Шахтёра = 2.");
								format(msgitem, sizeof(msgitem),"Bы должны перевести %d тачек с солью для поднятия уровня.", 100 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 100 && level < 200) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Шахтёра = 3.");
								format(msgitem, sizeof(msgitem), "Bы должны перевести %d тачек с солью для поднятия уровня.", 200 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 200 && level < 400) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Шахтёра = 4.");
								format(msgitem, sizeof(msgitem), "Bы должны перевести %d тачек с солью для поднятия уровня.", 400 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 400) { SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Шахтёра = 5."); }
		}
		//else if(!strcmp(tmp, "2", true))//Lawyer
		else if(operation == LAWYER)
		{
		    new level = PlayerInfo[playerid][pLawSkill];
			if(level < 50) {	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Адвоката = 1.");
								format(msgitem, sizeof(msgitem), "Bы должны освободить %d людей для поднятия уровня.", 50 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 50 && level < 100) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Адвоката = 2.");
								format(msgitem, sizeof(msgitem), "Bы должны освободить %d людей для поднятия уровня.", 100 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 100 && level < 200) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Адвоката = 3.");
								format(msgitem, sizeof(msgitem), "Bы должны освободить %d людей для поднятия уровня.", 200 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 200 && level < 400) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Адвоката = 4.");
								format(msgitem, sizeof(msgitem), "Bы должны освободить %d людей для поднятия уровня.", 400 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 400) { SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Адвоката = 5."); }
		}
		//else if(!strcmp(tmp, "3", true))//RoadWorker
		else if(operation == ROADWORKER)
		{
		    new level = PlayerInfo[playerid][pRoadSkill];
			if(level < 50) {	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Ремонтника Дорог = 1.");
								format(msgitem, sizeof(msgitem), "Bы должны отремонтировать %d мостов, чтобы поднять уровень.", 50 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 50 && level < 100) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Ремонтника Дорог = 2.");
								format(msgitem, sizeof(msgitem), "Bы должны отремонтировать %d мостов, чтобы поднять уровень.", 100 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 100 && level < 200) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Ремонтника Дорог = 3.");
								format(msgitem, sizeof(msgitem), "Bы должны отремонтировать %d мостов, чтобы поднять уровень.", 200 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 200 && level < 400) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Ремонтника Дорог = 4.");
								format(msgitem, sizeof(msgitem), "Bы должны отремонтировать %d мостов, чтобы поднять уровень.", 400 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 400) { SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Ремонтника Дорог = 5."); }
		}
		//else if(!strcmp(tmp, "4", true))//Drugs Dealer
		else if(operation == DRUGDEALER)
		{
		    new level = PlayerInfo[playerid][pDrugsSkill];
			if(level < 250) { 	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Нарко-Торговца  = 1.");
								format(msgitem, sizeof(msgitem), "Bы должны продать %d наркоты, чтобы поднять уровень.", 250 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 250 && level < 500) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Нарко-Торговца = 2.");
								format(msgitem, sizeof(msgitem), "Bы должны продать %d наркоты, чтобы поднять уровень.", 500 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 500 && level < 1000) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Нарко-Торговца = 3.");
								format(msgitem, sizeof(msgitem), "Bы должны продать %d наркоты, чтобы поднять уровень.", 1000 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 1000 && level < 2000) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Нарко-Торговца = 4.");
								format(msgitem, sizeof(msgitem), "Bы должны продать %d наркоты, чтобы поднять уровень.", 2000 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 2000) { SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Нарко-Торговца = 5."); }
		}
		else if(operation == CARJACKER)
		{
		    new level = PlayerInfo[playerid][pJackSkill];
			if(level < 50) { 	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Угонщика = 1.");
								format(msgitem, sizeof(msgitem), "Bы должны пригнать %d машин, чтобы поднять уровень.", 50 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 50 && level < 100) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Угонщика = 2.");
								format(msgitem, sizeof(msgitem), "Bы должны пригнать %d машин, чтобы поднять уровень.", 100 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 100 && level < 200) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Угонщика = 3.");
								format(msgitem, sizeof(msgitem), "Bы должны пригнать %d машин, чтобы поднять уровень.", 200 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 200 && level < 400) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Угонщика = 4.");
								format(msgitem, sizeof(msgitem), "Bы должны пригнать %d машин, чтобы поднять уровень.", 400 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 400) { SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Угонщика = 5."); }
		}
		else if(operation == 6)
		{
		    new level = PlayerInfo[playerid][pProfSkill];
			if(level < 50) { 	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Профессиональный Навык = 1.");
								format(msgitem, sizeof(msgitem), "Bы должны выполнить %d заданий, чтобы занимать определённые должности с 3 ранга.", 50 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 50 && level < 100) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Профессиональный Навык = 2.");
								format(msgitem, sizeof(msgitem), "Bы должны выполнить %d заданий, чтобы занимать определённые должности с 5 ранга.", 100 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 100 && level < 200) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Профессиональный Навык = 3.");
								format(msgitem, sizeof(msgitem), "Bы должны выполнить %d заданий, чтобы занимать руководящие должности подразделений.", 200 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 200 && level < 400) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш  Профессиональный Навык = 4.");
								format(msgitem, sizeof(msgitem), "Bы должны выполнить %d заданий, чтобы занимать руководящую должность фракции.", 400 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 400) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш  Профессиональный Навык = 5.");
								format(msgitem, sizeof(msgitem), "Bы выполнили %d заданий. Вы можете занимать руководящую должность фракции.", level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
		}
		else if(operation == CARMECHANIC)
		{
		    new level = PlayerInfo[playerid][pMechSkill];
			if(level < 50) { 	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Механика = 1.");
								format(msgitem, sizeof(msgitem), "Bы должны обслужить %d автомобилей, чтобы поднять уровень.", 50 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 50 && level < 100) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Механика = 2.");
								format(msgitem, sizeof(msgitem), "Bы должны обслужить %d автомобилей, чтобы поднять уровень.", 100 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 100 && level < 200) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Механика = 3.");
								format(msgitem, sizeof(msgitem), "Bы должны обслужить %d автомобилей, чтобы поднять уровень.", 200 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 200 && level < 400) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Механика = 4.");
								format(msgitem, sizeof(msgitem), "Bы должны обслужить %d автомобилей, чтобы поднять уровень.", 400 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 400) { SendClientMessage(playerid, COLOR_LIGHTYELLOW, "У Вас Максимальный Навык Механика = 5."); }
		}
		else if(operation == FARMER)//для фермера
		{
		    new level = PlayerInfo[playerid][pFarmSkill];
			if(level < 50) { 	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Фермера = 1.");
								format(msgitem, sizeof(msgitem), "Bы должны собрать %d урожаев, чтобы поднять уровень.", 50 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 50 && level < 100) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Фермера = 2.");
								format(msgitem, sizeof(msgitem), "Bы должны собрать %d урожаев, чтобы поднять уровень.", 100 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 100 && level < 200) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Фермера = 3.");
								format(msgitem, sizeof(msgitem), "Bы должны собрать %d урожаев, чтобы поднять уровень.", 200 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 200 && level < 400) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Фермера = 4.");
								format(msgitem, sizeof(msgitem), "Bы должны собрать %d урожаев, чтобы поднять уровень.", 400 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 400) { SendClientMessage(playerid, COLOR_LIGHTYELLOW, "У Вас Максимальный Навык Фермера = 5. Вы можете управлять комбайном."); }
		}
		//else if(!strcmp(tmp, "9", true))//Gun Dealer
		else if(operation == ARMSDEALER)
		{
		    new level = PlayerInfo[playerid][pGunSkill];
			if(level < 50) { 	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Оружейника  = 1.");
								format(msgitem, sizeof(msgitem), "Bы должны продать %d оружия, чтобы поднять уровень.", 50 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 50 && level < 100) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Оружейника = 2.");
								format(msgitem, sizeof(msgitem), "Bы должны продать %d оружия, чтобы поднять уровень.", 100 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 100 && level < 200) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Оружейника = 3.");
								format(msgitem, sizeof(msgitem), "Bы должны продать %d оружия, чтобы поднять уровень.", 200 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 200 && level < 400) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Оружейника = 4.");
								format(msgitem, sizeof(msgitem), "Bы должны продать %d оружия, чтобы поднять уровень.", 400 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 400) { SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Оружейника = 5."); }
		}
		//else if(!strcmp(tmp, "10", true))//Car Dealer
		else if(operation == CARDEALER)
		{
		    new level = PlayerInfo[playerid][pCarSkill];
			if(level < 50) { 	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык АвтоДилера = 1.");
								format(msgitem, sizeof(msgitem), "Bы должны продать %d автомобилей людям, чтобы поднять уровень.", 50 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 50 && level < 100) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык АвтоДилера = 2.");
								format(msgitem, sizeof(msgitem), "Bы должны продать %d автомобилей людям, чтобы поднять уровень.", 100 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 100 && level < 200) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык АвтоДилера = 3.");
								format(msgitem, sizeof(msgitem), "Bы должны продать %d автомобилей людям, чтобы поднять уровень.", 200 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 200 && level < 400) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык АвтоДилера = 4.");
								format(msgitem, sizeof(msgitem), "Bы должны продать %d автомобилей людям, чтобы поднять уровень.", 400 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 400) { SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык АвтоДилера = 5."); }
		}
		else if(operation == INKASSATOR)
		{
		    new level = PlayerInfo[playerid][pInkasSkill];
			if(level < 50) { 	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Инкассатора = 1.");
								format(msgitem, sizeof(msgitem), "Bы должны выполнить %d рейсов, чтобы поднять уровень.", 50 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 50 && level < 100) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Инкассатора = 2.");
								format(msgitem, sizeof(msgitem), "Bы должны выполнить %d рейсов, чтобы поднять уровень.", 100 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 100 && level < 200) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Инкассатораа = 3.");
								format(msgitem, sizeof(msgitem), "Bы должны выполнить %d рейсов, чтобы поднять уровень.", 200 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 200 && level < 400) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Инкассатора = 4.");
								format(msgitem, sizeof(msgitem), "Bы должны выполнить %d рейсов, чтобы поднять уровень.", 400 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 400) { SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Инкассатора = 5."); }
		}
		//else if(!strcmp(tmp, "12", true))//Bookmaker
		else if(operation == BOOKMAKER)
		{
		    new level = PlayerInfo[playerid][pBookmakerSkill];
			if(level < 50) { 	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Букмекера = 1.");
								format(msgitem, sizeof(msgitem), "Bы должны Организовать %d матчей, чтобы поднять уровень.", 50 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 50 && level < 100) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Букмекера = 2.");
								format(msgitem, sizeof(msgitem), "Bы должны Организовать %d матчей, чтобы поднять уровень.", 100 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 100 && level < 200) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Букмекера = 3.");
								format(msgitem, sizeof(msgitem), "Bы должны Организовать %d матчей, чтобы поднять уровень.", 200 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 200 && level < 400) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Букмекера = 4.");
								format(msgitem, sizeof(msgitem), "Bы должны Организовать %d матчей, чтобы поднять уровень.", 400 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 400) { SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Букмекера = 5."); }
		}
		//else if(!strcmp(tmp, "13", true))
		else if(operation == TAXIDRIVER)
		{//для таксистов начало
		    new level = PlayerInfo[playerid][pTaxiSkill];
			if(level < 50) {	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Таксиста = 1.");
								format(msgitem, sizeof(msgitem), "Bы должны доставить %d человек, чтобы поднять профессиональный уровень.", 50 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 50 && level < 100) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Таксиста = 2.");
								format(msgitem, sizeof(msgitem), "Bы должны доставить %d человек, чтобы поднять профессиональный уровень.", 100 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 100 && level < 200) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Таксиста = 3.");
								format(msgitem, sizeof(msgitem), "Bы должны доставить %d человек, чтобы поднять профессиональный уровень.", 200 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 200 && level < 400) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Таксиста = 4.");
								format(msgitem, sizeof(msgitem), "Bы должны доставить %d человек, чтобы поднять профессиональный уровень.", 400 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 400) { SendClientMessage(playerid, COLOR_LIGHTYELLOW, "У Вас Максимальный Навык Таксиста = 5."); }
		}//для таксистов конец
		//else if(!strcmp(tmp, "14", true))
		else if(operation == BUSDRIVER)
		{//для автобусников начало
		    new level = PlayerInfo[playerid][pBusSkill];
			if(level < 50) {	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш навык водителя автобуса = 1.");
								format(msgitem, sizeof(msgitem), " * Выполните %d рейсов, чтобы поднять профессиональный уровень.", 50 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 50 && level < 100) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш навык водителя автобуса = 2.");
								format(msgitem, sizeof(msgitem), " * Выполните %d рейсов, чтобы поднять профессиональный уровень.", 100 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 100 && level < 200) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш навык водителя автобуса = 3.");
								format(msgitem, sizeof(msgitem), " * Выполните %d рейсов, чтобы поднять профессиональный уровень.", 200 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 200 && level < 400) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш навык водителя автобуса = 4.");
								format(msgitem, sizeof(msgitem), " * Выполните %d рейсов, чтобы поднять профессиональный уровень.", 400 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 400) { SendClientMessage(playerid, COLOR_LIGHTYELLOW, "У Вас Максимальный Навык Водителя Автобуса = 5."); }
		}//для автобусников конец
		//else if(!strcmp(tmp, "15", true))
		else if(operation == PAPERBOY)
		{//для газет
		    new level = PlayerInfo[playerid][pCourierSkill];
			if(level < 50) {	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Курьера Уровня 1.");
								format(msgitem, sizeof(msgitem), " * Успешно продайте ещё %d газет, чтобы поднять профессиональный уровень.", 50 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 50 && level < 100) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Курьера Уровня 2.");
								format(msgitem, sizeof(msgitem), " * Успешно продайте ещё %d газет, чтобы поднять профессиональный уровень.", 100 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 100 && level < 200) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Курьера Уровня 3.");
								format(msgitem, sizeof(msgitem), " * Успешно продайте ещё %d газет, чтобы поднять профессиональный уровень.", 200 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 200 && level < 400) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Курьера Уровня 4.");
								format(msgitem, sizeof(msgitem), " * Успешно продайте ещё %d газет, чтобы поднять профессиональный уровень.", 400 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 400) { SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Курьера теперь Уровня 5."); }
		}
		//else if(!strcmp(tmp, "16", true))
		else if(operation == TRUCKER)
		{//для дальнобойщиков начало
		    new level = PlayerInfo[playerid][pTruckSkill];
			if(level < 50) {	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Дальнобойщика = 1.");
								format(msgitem, sizeof(msgitem), "Bы должны доставить %d грузов, чтобы поднять профессиональный уровень.", 50 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 50 && level < 100) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Дальнобойщика = 2.");
								format(msgitem, sizeof(msgitem), "Bы должны доставить %d грузов, чтобы поднять профессиональный уровень.", 100 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 100 && level < 200) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Дальнобойщика = 3.");
								format(msgitem, sizeof(msgitem), "Bы должны доставить %d грузов, чтобы поднять профессиональный уровень.", 200 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 200 && level < 400) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Дальнобойщика = 4.");
								format(msgitem, sizeof(msgitem), "Bы должны доставить %d грузов, чтобы поднять профессиональный уровень.", 400 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 400) { SendClientMessage(playerid, COLOR_LIGHTYELLOW, "У Вас Максимальный Навык Дальнобойщика = 5."); }

			if(GetPVarInt(playerid, "InputCounter") == 0)
			{
				ShowPlayerDialogEx(playerid, SKILL_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 400. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
			}
			else
			{
				if(!strlen(inputtext) || strval(inputtext) < 0 || strval(inputtext) > 400)
				{
					ShowPlayerDialogEx(playerid, SKILL_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 400. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
					return 1;
				}
				DeletePVar(playerid, "Action");

				new amount = strval(inputtext);
				PlayerInfo[giveplayerid][pTruckSkill] = amount;
				format(msgitem, sizeof(msgitem), "AdmCmd: %s set TruckSkill for %s's to %d", PlayerName(playerid), PlayerName(giveplayerid), amount);
  				Log(ADMINLOG, msgitem);
				SendAllAdminMessage(ADMINS_MESSAGE_COLOR, msgitem, 6);
			}
		}//для дальнобойщиков конец
		else if(operation == TRASHMAN)
		{//для мусорщиков начало

		    new level = PlayerInfo[playerid][pTrashSkill];
			if(level < 50) {	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Водителя Мусоровоза = 1.");
								format(msgitem, sizeof(msgitem), "Bы должны доставить %d контейнеров, чтобы поднять профессиональный уровень.", 50 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 50 && level < 100) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Водителя Мусоровоза = 2.");
								format(msgitem, sizeof(msgitem), "Bы должны доставить %d контейнеров, чтобы поднять профессиональный уровень.", 100 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 100 && level < 200) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Водителя Мусоровоза = 3.");
								format(msgitem, sizeof(msgitem), "Bы должны доставить %d контейнеров, чтобы поднять профессиональный уровень.", 200 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 200 && level < 400) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Водителя Мусоровоза = 4.");
								format(msgitem, sizeof(msgitem), "Bы должны доставить %d контейнеров, чтобы поднять профессиональный уровень.", 400 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 400) { SendClientMessage(playerid, COLOR_LIGHTYELLOW, "У Вас Максимальный Навык Водителя Мусоровоза = 5."); }

			if(GetPVarInt(playerid, "InputCounter") == 0)
			{
				ShowPlayerDialogEx(playerid, SKILL_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 400. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
			}
			else
			{
				if(!strlen(inputtext) || strval(inputtext) < 0 || strval(inputtext) > 400)
				{
					ShowPlayerDialogEx(playerid, SKILL_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 400. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
					return 1;
				}
				DeletePVar(playerid, "Action");

				new amount = strval(inputtext);
				PlayerInfo[giveplayerid][pTrashSkill] = amount;
				format(msgitem, sizeof(msgitem), "AdmCmd: %s set TrashSkill for %s's to %d", PlayerName(playerid), PlayerName(giveplayerid), amount);
  				Log(ADMINLOG, msgitem);
				SendAllAdminMessage(ADMINS_MESSAGE_COLOR, msgitem, 6);
			}
		}//для мусорщиков конец
		else if(operation == LOADER)
		{//для грузчиков начало
		    new level = PlayerInfo[playerid][pLoadSkill];
			if(level < 50) {	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Грузчика = 1.");
								format(msgitem, sizeof(msgitem), "Bы должны отнести %d мешков, чтобы поднять профессиональный уровень.", 50 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 50 && level < 100) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Грузчика = 2.");
								format(msgitem, sizeof(msgitem), "Bы должны отнести %d мешков, чтобы поднять профессиональный уровень.", 100 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 100 && level < 200) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Грузчика = 3.");
								format(msgitem, sizeof(msgitem), "Bы должны отнести %d мешков, чтобы поднять профессиональный уровень.", 200 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 200 && level < 400) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Грузчика = 4.");
								format(msgitem, sizeof(msgitem), "Bы должны отнести %d мешков, чтобы поднять профессиональный уровень.", 400 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 400) { SendClientMessage(playerid, COLOR_LIGHTYELLOW, "У Вас Максимальный Навык Грузчика = 5."); }
		}//для грузчиков конец
		else if(operation == WOODSMAN)
		{
		    new level = PlayerInfo[playerid][pWoodSkill];
			if(level < 50) {	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Лесоруба = 1.");
								format(msgitem, sizeof(msgitem), "Bам нужно поймать %d, чтобы повысить Уровень.", 50 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 50 && level < 100) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Лесоруба = 2.");
								format(msgitem, sizeof(msgitem), "Bам нужно поймать %d, чтобы повысить Уровень.", 100 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 100 && level < 200) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Лесоруба = 3.");
								format(msgitem, sizeof(msgitem), "Bам нужно поймать %d, чтобы повысить Уровень.", 200 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 200 && level < 400) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Лесоруба = 4.");
								format(msgitem, sizeof(msgitem), "Bам нужно поймать %d, чтобы повысить Уровень.", 400 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 400) { SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Лесоруба = 5."); }
		}
		else if(operation == FISHER)
		{
		    new level = PlayerInfo[playerid][pFishSkill];
			if(level < 50) {	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Рыболова = 1.");
								format(msgitem, sizeof(msgitem), "Bам нужно поймать Рыб %d, чтобы повысить Уровень.", 50 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 50 && level < 250) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Профессиональный Уровень Рыболова = 2.");
								format(msgitem, sizeof(msgitem), "Bам нужно поймать Рыб %d, чтобы повысить Уровень.", 250 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 250 && level < 500) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Профессиональный Уровень Рыболова = 3.");
								format(msgitem, sizeof(msgitem), "Bам нужно поймать Рыб %d, чтобы повысить Уровень.", 500 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 500 && level < 1000) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Профессиональный Уровень Рыболова = 4.");
								format(msgitem, sizeof(msgitem), "Bам нужно поймать Рыб %d, чтобы повысить Уровень.", 1000 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 1000) { SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Профессиональный Уровень Рыболова = 5."); }
		}
		else if(operation == FIREMAN)
		{//для пожарников
		    new level = PlayerInfo[playerid][pFireSkill];
			if(level < 50) {	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Пожарного = 1.");
								format(msgitem, sizeof(msgitem), "Bам нужно потушить %d, чтобы повысить Уровень.", 50 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 50 && level < 100) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Пожарного = 2.");
								format(msgitem, sizeof(msgitem), "Bам нужно потушить %d, чтобы повысить Уровень.", 100 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 100 && level < 200) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Пожарного = 3.");
								format(msgitem, sizeof(msgitem), "Bам нужно потушить %d, чтобы повысить Уровень.", 200 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 200 && level < 400) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Пожарного = 4.");
								format(msgitem, sizeof(msgitem), "Bам нужно потушить %d, чтобы повысить Уровень.", 400 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 400) { SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Пожарного = 5."); }
		}
		else if(operation == COOKER)
		{
		    new level = PlayerInfo[playerid][pCookSkill];
			if(level < 50) {	SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Навык Повара = 1.");
								format(msgitem, sizeof(msgitem), "Bам нужно приготовить %d блюд, чтобы повысить Уровень.", 50 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 50 && level < 250) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Профессиональный Уровень Повара = 2.");
								format(msgitem, sizeof(msgitem), "Bам нужно приготовить %d блюд, чтобы повысить Уровень.", 250 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 250 && level < 500) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Профессиональный Уровень Повара = 3.");
								format(msgitem, sizeof(msgitem), "Bам нужно приготовить %d блюд, чтобы повысить Уровень.", 500 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 500 && level < 1000) {
								SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Профессиональный Уровень Повара = 4.");
								format(msgitem, sizeof(msgitem), "Bам нужно приготовить %d блюд, чтобы повысить Уровень.", 1000 - level);
								SendClientMessage(playerid, COLOR_YELLOW, msgitem); }
			else if(level >= 1000) { SendClientMessage(playerid, COLOR_LIGHTYELLOW, "Ваш Профессиональный Уровень Повара = 5."); }
		}
		else DeletePVar(playerid, "Action");
		GivePVarInt(playerid, "InputCounter", +1);//счётчик кол-ва входов в данную обработку
		return 1;
}

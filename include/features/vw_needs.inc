//для анимаций
#if !defined SPECIAL_ACTION_PISSING
	#define SPECIAL_ACTION_PISSING 68
#endif


//##############################################################################//
//                                                                              //
//                             СИСТЕМА ПОТРЕБНОСТЕЙ                             //
//                                                                              //
//##############################################################################//
//Голод: время заполнения шкалы 3 часа
//Досуг: время заполнения шкалы 4 часа
//Общение: время заполнения шкалы  5 часов
//Туалет: время заполнения шкалы 6 часов
//Бодрость: время заполнения шкалы 7 часов

//предел шкалы
new operator1 = 100;
new operator2 = 50;
new operator3 = 30;
new operator4 = 20;
new operator5 = 15;

//для потребностей флаги
new gParameter1[MAX_PLAYERS];//Голод
new gParameter2[MAX_PLAYERS];//Досуга
new gParameter3[MAX_PLAYERS];//Общение
new gParameter4[MAX_PLAYERS];//Туалет
new gParameter5[MAX_PLAYERS];//Бодрость
//если 1 значит сработала потребность



new gTogNeed = 1;//0

//##############################################################################//
//                                                                              //
//                                 СЧЁТЧИКИ                                     //
//                                                                              //
//##############################################################################//


new TickCount1[MAX_PLAYERS];//счётчик для 1-х секундного пакетника
new TickCount2[MAX_PLAYERS];
new TickCount3[MAX_PLAYERS];
new TickCount4[MAX_PLAYERS];
new TickCount5[MAX_PLAYERS];

//##############################################################################//
stock IsNeeds(playerid)
{
	if(gParameter2[playerid] == 1)
	{
		 return 1;
	}
	return 0;
}

stock needs_OnPlayerConnect(playerid)
{

//для потребностей
	gParameter1[playerid] = 0;
	gParameter2[playerid] = 0;
	gParameter3[playerid] = 0;
	gParameter4[playerid] = 0;
	gParameter5[playerid] = 0;
	PlayerInfo[playerid][pParam1] = 0;
	PlayerInfo[playerid][pParam2] = 0;
	PlayerInfo[playerid][pParam3] = 0;
	PlayerInfo[playerid][pParam4] = 0;
	PlayerInfo[playerid][pParam5] = 0;
	TickCount1[playerid] = 0;
	TickCount2[playerid] = 0;
	TickCount3[playerid] = 0;
	TickCount4[playerid] = 0;
	TickCount5[playerid] = 0;
}



/*1)  Мигрень (неврологическое заболевание [1], наиболее частым и характерным симптомом
которого являются эпизодические или регулярные сильные и мучительные приступы головной боли в одной
(редко в обеих) половине головы. Приступы мигрени часто сопровождаются фотофобией
(светобоязнью, гиперчувствительностью к яркому свету), фонофобией и гиперакузией
(звукобоязнью, гиперчувствительностью к громким звукам), гиперосмией
(гиперчувствительностью и отвращением к запахам), тошнотой, иногда рвотой,
потерей пространственной ориентации и головокружением. Часто наблюдаются резкая
раздражительность (дисфория) или угнетённое, подавленное настроение, возбуждение
или сонливость, вялость. Провоцирующие факторы - Возникновению приступа мигрени
способствуют следующие факторы: стресс, нервное и физическое перенапряжение,
пищевые факторы (сыр, шоколад, орехи, рыба), алкоголь (чаще всего пиво и красное
вино, шампанское), гормональные причины (менструальный цикл, прием контрацептивов),
сон (недостаток или избыток), погодные факторы (смена погоды, смена климатических условий) )
1хп + лёгкое головокружение

2)  ОРВИ (распространённая группа вирусных заболеваний верхних дыхательных путей,
в ходе развития заболевания может присоединяться бактериальная инфекция.
Основные симптомы ОРВИ — насморк, кашель, чихание, головная боль, боль в горле, усталость.)
2хп + лёгкое головокружение + анимация кашель каждые 5 минут (/heist)

3)  Гастрит (собирательное понятие, используемое для обозначения различных по происхождению
и течению воспалительных и дистрофических изменений слизистой оболочки желудка)
3хп + анимация рвоты каждые 5 минут (/vomit)

4)  Недержание мочи
снимает 4 хп + анимация каждые 5 минут (/piss)

5)  Психическое расстройство (состояние психики, отличное от нормального/здорового. )
снимает 5хп  + анимация как будто эпилепсия каждые 5 минут(/nut)

6)  Эпилепсия (Представляет собой хроническое психоневрологическое заболевание,
характеризующееся склонностью к повторяющимся внезапным припадкам. )
6хп + анимация корчится от боли каждые 5 минут (/crack)

7)  Артрит (собирательное обозначение любых болезней (поражений) суставов.
Клиническая картина - Все типы артрита сопровождает боль, характер которой зависит от типа артрита.
Также для артритов характерны покраснение кожи, ограничение подвижности в суставе, изменение его формы.
Часто подверженные болезни суставы неестественно хрустят при нагрузке.
Человек, болеющий артритом, может испытывать трудности в случаях, если нужно применить физическую силу.)
снимает 7 хп + обездвиживание каждые 5 минут (/heist)

8)  Астма (хроническое воспалительное заболевание дыхательных путей, в котором
принимают участие многие клетки и клеточные элементы. Хроническое воспаление
обусловливает развитие бронхиальной гиперреактивности, которая приводит к повторяющимся
эпизодам свистящих хрипов, одышки, чувства заложенности в груди и кашля, особенно
по ночам и ранним утром. Эти эпизоды обычно связаны с распространённой, но изменяющейся
по своей выраженности обструкции дыхательных путей в лёгких, которая часто бывает
обратима либо спонтанно, либо под действием лечения. Экологические факторы.
- выхлопные газы, дым, повышенная влажность, вредные испарения и др.
Клиническая картина - Основными симптомами бронхиальной астмы являются эпизоды одышки,
свистящие хрипы, кашель и заложенность в грудной клетке. )
8 хп + головокружение + анимация отдышки каждые 5 минут.

9)  Рак (вид злокачественной опухоли, развивающейся из клеток эпителиальной ткани
различных органов (кожи, слизистых оболочек и многих внутренних органов).
Клинические проявления - Симптоматика рака зависит главным образом от месторасположения опухоли,
от темпов её роста, наличия метастазов. Наиболее частыми признаками являются:
Изменение кожных покровов на ограниченном участке в виде растущей припухлости, окружённой каймой гиперемии.
Припухлости могут изъязвляться, обнажая глубокие язвы, нечувствительные к лечению.
Изменение тембра голоса, затруднение глотания или прохождения пищи через пищевод,
упорный кашель, боль в области грудной клетки или живота. Потеря веса, снижение аппетита,
немотивированная слабость, стойкое повышение температуры тела, анемия,
уплотнение молочной железы и кровянистые выделения из соска, кровянистые выделения из мочевого пузыря,
затруднение мочеиспускания и т. д.)
снимает 9хп + сильное головокружение + потеря сознания каждые 5 минут (tazer)

10)  Пневмония (воспаление лёгочной ткани инфекционного происхождения
с преимущественным поражением альвеол и интерстициальной ткани легкого.
«Типичная» пневмония характеризуется резким подъёмом температуры, кашлем с обильным выделением гнойной мокроты
и в некоторых случаях плевральной боли. При исследовании: укорочение перкуторного звука,
жесткое дыхание, бронхофония, усиленное голосовое дрожание, сначала сухие, а затем влажные,
крепитирующие хрипы, затемнение на рентгенограмме)
10 хп + анимация кашель каждые 5 минут (/heist) + затемнение экрана

<19:02:02> "Нач.отд. CID Nikalas_Ferpoint":
/animdozer 1, 2  - лестница
ApplyAnimation(playerid, "DOZER", "DOZER_Align_LHS",4.1,0,1,1,1,1);
ApplyAnimation(playerid, "DOZER", "DOZER_Align_RHS",4.1,0,1,1,1,1);

/animghetto 5
/animgraveyard 1 - Кашель
/animmedic - реанимация для медика
/animmisc 35 - чесаться
/animpaulnmac - шатается
/scratching - перелом
/animwuzi - лежит

	ApplyAnimation(playerid, animlib, animname, animspeed, looping, lockx, locky, lockz, lp);//Установить анимацию для игрока
	//animlib - название библиотеке анимации
	//animname - название анимации
	//animspeed - скорость анимации.
	//looping - повторяется (1) или нет (0)
	//lockx - (0) - возвращаться в исх. позицию
	//locky - LockY - в основном хранит позицию игрока когда он выполняют оживление,
	//которое требует перемещения. Когда оживление сделано,
	//оно устанавливает в исходную позицию до оживления, если установлено на 0.
	//Противоположный эффект если установленно на 1.
	//lockz - Заморозит игрока (1) в позиции, оживления (0)
	//lp - через сколько время выйти из цыкла или закончить анимацию. Таймер в миллисекундах. Для бесконечного цикла должно быть 0.
*/

stock needs_OneMinutsTimer(playerid, animationid)//OnPlayerDisease1Timer(playerid)//запускается каждую минуту
{   //для болезней и голода
	if(spectateid[playerid] != MAX_PLAYERS-1) return 1;
	//new strings[MAX_STRING];
    new Float: health = LastHealth[playerid];
    //GetPlayerHealth(playerid, health);
	if(	gTogNeed && PlayerInfo[playerid][pJailed] == 0
		&& IsPlayerControllable[playerid] == 0
		&& FollowBy[playerid] == MAX_PLAYERS-1)
	{
//для потребностей
//голод должен достигать максимума за 97 минут(58000)
//Досуг должен достигать максимума за 143 минут(178000)
//Общение должен достигать максимума за 149 минут(298000)
//Туалет должен достигать максимума за 199 минут(598000)
//Бодрость должен достигать максимума за 240 минут(958000)
/*	new operator1 = 100;
	new operator2 = 50;
	new operator3 = 30;
	new operator4 = 20;
	new operator5 = 15;*/
		/*if(gParameter1[playerid] == 1)
		{
			if(PlayerInfo[playerid][pParam1] <= 0)
			{
				PlayerInfo[playerid][pParam1] = 0;
				gParameter1[playerid] = 0;
				SetPlayerShowScale(playerid, 1, PlayerInfo[playerid][pParam1], 100);
			}
		}*/
		if(	gParameter1[playerid] == 1 &&
			HUNGER == 1 && PlayerInfo[playerid][pLevel] > 2)
		{
			SetPlayerHealthEx(playerid, (health-10.0));//каждые минуту уменьшаем здоровье, типа голод
			format(strings, sizeof(strings), "%s потерял %d здоровья из-за голода", PlayerName(playerid), 10);
			ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);//COLOR_LILAC
		}
		//----------------------------------------------------------------------
		//досуг
		if(	(GetCheckpointType(playerid) == CP_BAR || GetCheckpointType(playerid) == CP_PUMP || GetCheckpointType(playerid) == CP_INN ||
			GetCheckpointType(playerid) == CP_PIGPEN || GetCheckpointType(playerid) == CP_STRIP ||
			GetCheckpointType(playerid) == CP_ALHAMBRA || GetCheckpointType(playerid) == CP_JIZZY) &&
			(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DANCE1 ||
			GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DANCE2 ||
   			GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DANCE3 ||
      		GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DANCE4) &&
      		PlayerInfo[playerid][pParam2] > 0 )
		{
			PlayerInfo[playerid][pParam2] -= 25;//30 минут танцует
			if(PlayerInfo[playerid][pParam2] < operator2) gParameter2[playerid] = 0;//опускаме - нет больше потребности
			if(PlayerInfo[playerid][pParam2] <= 0) PlayerInfo[playerid][pParam2] = 0;//обнуляем
			SetPlayerShowScale(playerid, 2, PlayerInfo[playerid][pParam2], operator2);
		}
		/*else if(PlayerInfo[playerid][pParam2] >= 50)
		{
			if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "PAULNMAC","wank_loop",4.1,1,0,0,1,0,1);//дрочит
			PlayerInfo[playerid][pParam2] -= 1;
		}*/
		//----------------------------------------------------------------------
		/*if(PlayerInfo[playerid][pParam3] >= 30)//общение
		{
			//if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "benchpress","gym_bp_celebrate",4.1,1,0,0,1,0,1);
			PlayerInfo[playerid][pParam3] -= 3;
			if(PlayerInfo[playerid][pParam3] <= 0)
			{
				gParameter3[playerid] = 0;
				ClearAnimations(playerid, 1);
				ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,0,0,0,0,1);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			}
		}*/
		//----------------------------------------------------------------------
		if(	GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_PISSING
			 && PlayerInfo[playerid][pParam4] > 0)//туалет
		{//если человек просто решил понизить потребность
			PlayerInfo[playerid][pParam4] -= 20;//1 минуту сцыться
			if(PlayerInfo[playerid][pParam4] <= 0)
			{
				PlayerInfo[playerid][pParam4] = 0;
				gParameter4[playerid] = 0;
				ClearAnimations(playerid, 1);
				ApplyAnimation(playerid, "CARRY","CRRY_PRTIAL",4.1,0,0,0,0,1);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			}
			SetPlayerShowScale(playerid, 4, PlayerInfo[playerid][pParam4], operator4);
		}
		if(gParameter4[playerid] == 1)
		{
			if(!IsPlayerInAnyVehicle(playerid))
			{
		         SetPlayerSpecialAction(playerid, SPECIAL_ACTION_PISSING);
		         PlaySoundForPlayerInRange(playerid, SOUND_PISSING, 30.0);
		   	     ApplyAnimation(playerid, "PAULNMAC","Piss_in",4.1,1,0,0,1,60000,1); //писать
			}
		}
		//-----------------------------------------------------------------------
		//бодрость
		if(	(PlayerInfo[playerid][pLocal] >= 0 && PlayerInfo[playerid][pLocal] < 100) ||
			PlayerInfo[playerid][pLocal] == 243 ||//Особняк LCN
			PlayerInfo[playerid][pLocal] == 244 ||//Особняк Yakudza
			PlayerInfo[playerid][pLocal] == 254 ||//Мотель
			PlayerInfo[playerid][pLocal] == 240 //Barracks Officers
			)// && PlayerInfo[playerid][pParam5] > 0

		{   //если человек спит в доме или мотеле или в казарме
			//new anim_id = PlayerLastAnimation[playerid];//GetPlayerAnimationIndex(playerid);
			if(animationid)
			{//если введена какая то анимация
				new animNew[32]; new animlib[32];//"PED", "FLOOR_hit"
				GetAnimationName(animationid, animlib, 32, animNew, 32);
				if(	strlen(animNew) &&
					(!strcmp(animNew, "FLOOR_hit", true) ||//Эта функция также возвращает 0 если любая строка пустая.
					!strcmp(animNew, "BED_LOOP_L", true) ||
					!strcmp(animNew, "BED_LOOP_R", true)) )
				{
					PlayerInfo[playerid][pParam5] = 0;
					gParameter5[playerid] = 0;
					SetPlayerShowScale(playerid, 5, PlayerInfo[playerid][pParam5], operator5);
				}
				strmid(animOld[playerid], animNew, 0, strlen(animNew), 32);
			}
		}
		if(gParameter5[playerid] == 1)//бодрость
		{   //если потребность достигла максимума
			gTextDrawShowBlind[playerid] = true; OnPlayerTextDrawStateChange(playerid);
			SetTimerEx("tHidePlayerBlind", 5000, 0, "d", playerid);
			format(strings, sizeof(strings), "%s так сильно хочет спать, что примкнул голову и закрыл глаза на 5 секунд", PlayerName(playerid));
			ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);//COLOR_LILAC
		}
	}
	//==========================================================================
	if(PlayerInfo[playerid][pSTD] <= 0 || PlayerInfo[playerid][pSTD] == IsNotBeenIll) return 1;
	PlayerNowAnimCount[playerid] = CHEATLIM;//задержка 2 секунды
	if(PlayerInfo[playerid][pSTD] == 1)
	{
	    SetPlayerHealthEx(playerid, (health-1.0));
		format(strings, sizeof(strings), " %s потерял 1 здоровья в результате Мигрени.", PlayerName(playerid));
		SetPlayerDrunkLevel(playerid, 3*1000);
		if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "WUZI","CS_Plyr_pt2",4.1,0,0,0,0,0,1);
	}
	else if(PlayerInfo[playerid][pSTD] == 2)
	{
	    SetPlayerHealthEx(playerid, (health-2.0));
		format(strings, sizeof(strings), " %s потерял 2 здоровья в результате ОРВИ.", PlayerName(playerid));
		if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "GRAVEYARD","mrnF_loop",4.1,0,0,0,0,0,1);
		SetPlayerDrunkLevel(playerid, 5*1000);
	}
	else if(PlayerInfo[playerid][pSTD] == 3)
	{
	    SetPlayerHealthEx(playerid, (health-3.0));
		format(strings, sizeof(strings), " %s потерял 3 здоровья в результате Гастрита.", PlayerName(playerid));
		if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "FOOD","EAT_Vomit_P",4.1,0,0,0,0,5000,1); // Vomit BAH!
		PlaySoundForPlayer(playerid, 32201);//рвота
	}
	else if(PlayerInfo[playerid][pSTD] == 4)
	{
	    SetPlayerHealthEx(playerid, (health-4.0));
		format(strings, sizeof(strings), " %s потерял 4 здоровья в результате Простатита.", PlayerName(playerid));//Недержания мочи
		if(!IsPlayerInAnyVehicle(playerid))
		{
			//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_PISSING);
			PlaySoundForPlayerInRange(playerid, SOUND_PISSING, 30.0);
			ApplyAnimation(playerid, "PAULNMAC","Piss_in",4.1,1,0,0,0,5000,1); //писать
		}
	}
	else if(PlayerInfo[playerid][pSTD] == 5)
	{
	    SetPlayerHealthEx(playerid, (health-5.0));
		format(strings, sizeof(strings), " %s потерял 5 здоровья в результате Психического расстройства.", PlayerName(playerid));
		if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "PED","HIT_back",0.1,1,0,0,0,10000,1);
		//if(!IsPlayerInAnyVehicle(playerid)) LoopingAnim(playerid, "PED", "HIT_back", 0.1, 1, 0, 0, 0, 0);
	}
	else if(PlayerInfo[playerid][pSTD] == 6)
	{
	    SetPlayerHealthEx(playerid, (health-6.0));
		format(strings, sizeof(strings), " %s потерял 6 здоровья в результате Эпилепсии.", PlayerName(playerid));
		if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "CRACK","crckdeth2",4.1,1,0,0,0,15000,1); // Dieing of Crack
	}
	else if(PlayerInfo[playerid][pSTD] == 7)
	{
	    SetPlayerHealthEx(playerid, (health-7.0));
		format(strings, sizeof(strings), " %s потерял 7 здоровья в результате Артрита.", PlayerName(playerid));
		//if(!IsPlayerInAnyVehicle(playerid)) OnePlayAnim(playerid, "SCRATCHING", "scdrdlp", 4.0, 0, 0, 0, 0, 0);
		if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "SWEET","Sweet_injuredloop",4.1,1,0,0,0,15000,1);
	}
	else if(PlayerInfo[playerid][pSTD] == 8)
	{
	    SetPlayerHealthEx(playerid, (health-8.0));
		format(strings, sizeof(strings), " %s потерял 8 здоровья в результате Астмы.", PlayerName(playerid));
		SetPlayerDrunkLevel(playerid, 7*1000);
		if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "PAULNMAC","PnM_Argue2_A",4.1,0,0,0,0,15000,1);
	}
	else if(PlayerInfo[playerid][pSTD] == 9)
	{
	    SetPlayerHealthEx(playerid, (health-9.0));
		format(strings, sizeof(strings), " %s потерял 9 здоровья в результате Рака.", PlayerName(playerid));
		if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "CRACK","crckdeth3",4.1,0,1,1,0,15000,1);
		SetPlayerDrunkLevel(playerid, 9*1000);
	}
	else if(PlayerInfo[playerid][pSTD] == 10)
	{
	    SetPlayerHealthEx(playerid, (health-10.0));
		format(strings, sizeof(strings), " %s потерял 10 здоровья в результате Пневмонии.", PlayerName(playerid));
		//if(!IsPlayerInAnyVehicle(playerid)) OnePlayAnim(playerid, "HEIST9", "CAS_G2_GasKO", 4.0, 0, 1, 1, 0, 0);
		//if(!IsPlayerInAnyVehicle(playerid)) OnePlayAnim(playerid, "HEIST9", "CAS_G2_GasKO", 4.0, 0, 0, 0, 0, 0);
		if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid, "SWEET","Sweet_injuredloop",4.1,1,0,0,0,20000,1);//падает на колени
		PlaySoundForPlayer(playerid, 32201);//типа срыгивает
		gTextDrawShowBlind[playerid] = true; OnPlayerTextDrawStateChange(playerid);
		SetTimerEx("tHidePlayerBlind", 5000, 0, "d", playerid);
	}
	if(PlayerInfo[playerid][pSTD] >= 1 && PlayerInfo[playerid][pSTD] <= 10) ProxDetector(playerid, 30.0, strings, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);//COLOR_LILAC
	return 1;
}


//для потребностей начало
stock OnPlayerIncreaseParameter(playerid)//запускается каждую минуту
{
	if(!gTogNeed) return 1;
	//==========================================================================
	//голод должен достигать максимума за 100 срабатываний или 108000 милисекунд или (108000/1000*100)/60=180 минут или 3 часа
	//Досуг должен достигать максимума за 50 срабатываний или 288000 милисекунд или (288000/1000*50)/60=240 минут или 4 часа
	//Общение должен достигать максимума за 30 срабатываний или 600000 срабатываний или (600000/1000*30)/60=300 минут или 5 часа
	//Туалет должен достигать максимума за 20 срабатываний или 1080000 срабатываний или (1080000/1000*20)/60=360 минут или 6 часа
	//Бодрость должен достигать максимума за 15 срабытываний или 108000 срабатываний или (1680000/1000*15)/60=420 минут или 7 часа

	/*new operator1 = 100;
	new operator2 = 50;
	new operator3 = 30;
	new operator4 = 20;
	new operator5 = 15;*/

	new ParameterSpeed1 = (3+PlayerInfo[playerid][pHunger])*60 *60/operator1 *1000;//3*60 *60/100 *1000 = 108000;
	new ParameterSpeed2 = (4+PlayerInfo[playerid][pLeisure])*60 *60/operator2 *1000;//288000
	new ParameterSpeed3 = (5+PlayerInfo[playerid][pContact])*60 *60/operator3 *1000;//600000
	new ParameterSpeed4 = (6+PlayerInfo[playerid][pToilet])*60 *60/operator4 *1000;//1080000
	new ParameterSpeed5 = (7+PlayerInfo[playerid][pVigour])*60 *60/operator5 *1000;//1680000

//голод
	if(GetTickCount() >= (TickCount1[playerid] + ParameterSpeed1))//ParameterSpeed1[playerid] должно быть кратно 60 секундам
	{ 	//срабатывает каждые 108 секунд	//сработает 100 раз за 10800 секунд(~180 минут)
		if(PlayerInfo[playerid][pParam1] < operator1)
		{
			PlayerInfo[playerid][pParam1] += 1;
			SetPlayerShowScale(playerid, 1, PlayerInfo[playerid][pParam1], operator1+PlayerInfo[playerid][pHunger]);
		}
		else gParameter1[playerid] = 1;
		TickCount1[playerid] = GetTickCount();
	}
//Досуг
	if(GetTickCount() >= (TickCount2[playerid] + ParameterSpeed2))
	{ 										//	+ 178000 //сработает 50 раз за 8900 секунд (148 минут)
		if(PlayerInfo[playerid][pParam2] < operator2)
		{
			PlayerInfo[playerid][pParam2] += 1;
			SetPlayerShowScale(playerid, 2, PlayerInfo[playerid][pParam2], operator2);
			//if(PlayerInfo[playerid][pParam2] >= 48) SendClientMessage(playerid, COLOR_MAROON, "РАЗУМ: Ещё немного и ты впадёшь в отчаяние! Вам надо срочно развлечься в клубе!");
			//if(PlayerInfo[playerid][pParam2] >= 48) SendClientMessage(playerid, COLOR_MAROON, "Прохожий: сегодня в клубах города лучшие DJ штата. Хочешь поднять себе настроение? Дуй туда!");
			if(PlayerInfo[playerid][pParam2] >= 47)
			{
				SendClientMessage(playerid, COLOR_GREY, "РАЗУМ: Ууу! Ну и видок у тебя. С таким настроением ко мне на работу лучше не приходи!");
			 	SendClientMessage(playerid, COLOR_GREY, "Подсказка: перед тем, как выйти на работу, посетите клуб или бар. Потанцуйте (USE: /dance) или пропустите баночку пивка!");
			 	PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
			}
		}
		else gParameter2[playerid] = 1;
		TickCount2[playerid] = GetTickCount();
	}
//Общение
	if(GetTickCount() >= (TickCount3[playerid] + ParameterSpeed3))
	{ 										//	+ 298000 //сработает 30 раз за 8940 секунд(149 минут)
		if(PlayerInfo[playerid][pParam3] < operator3)
		{
			PlayerInfo[playerid][pParam3] += 1;
			SetPlayerShowScale(playerid, 3, PlayerInfo[playerid][pParam3], operator3);
			if(PlayerInfo[playerid][pParam3] >= 27)	{
				SendClientMessage(playerid, COLOR_GREY, "РАЗУМ: Ты выглядишь таким потерянным! Видимо с тобой никто не общается. Не унывай, у тебя же есть телефон!");
				PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
			}
			//if(PlayerInfo[playerid][pParam3] >= 27) SendClientMessage(playerid, COLOR_MAROON, "Прохожий: Эй, ну и видок у тебя! Да ты даже пару слов связать не можешь! Быстрей бери телефон и тренируся!");
		}
		else gParameter3[playerid] = 1;
		TickCount3[playerid] = GetTickCount();
	}
//Туалет
	if(GetTickCount() >= (TickCount4[playerid] + ParameterSpeed4))
	{ 										//	+ 598000 //сработает 20 раз за 11960 секунд(199 минут)
		if(PlayerInfo[playerid][pParam4] < operator4)
		{
			PlayerInfo[playerid][pParam4] += 1;
			SetPlayerShowScale(playerid, 4, PlayerInfo[playerid][pParam4], operator4);
			if(PlayerInfo[playerid][pParam4] >= 17) {
				SendClientMessage(playerid, COLOR_GREY, "РАЗУМ: Вам срочно надо справить нужду. Смотрите, чтобы вас ни кто не видел (USE: /piss)!");
				PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
			}
		}
		else gParameter4[playerid] = 1;
		TickCount4[playerid] = GetTickCount();
	}
//Бодрость
	if(GetTickCount() >= (TickCount5[playerid] + ParameterSpeed5))
	{ 	//срабатывает каждые 1680 секунд	//сработает 15 раз за 25200 секунд(~420 минут)
		if(PlayerInfo[playerid][pParam5] < operator5 && gParameter5[playerid] == 0)
		{   //если параметр ниже предельного, и игрок не находится в потребности, то подымаем
			PlayerInfo[playerid][pParam5] += 1;
			SetPlayerShowScale(playerid, 5, PlayerInfo[playerid][pParam5], operator5);
			if(PlayerInfo[playerid][pParam5] >= 12) {
				SendClientMessage(playerid, COLOR_GREY, "РАЗУМ: Ещё немного и ты уснешь! Скорее доберись до кровати и поспи (USE: /bedl /bedr)!");
				PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
			}
		}
		else gParameter5[playerid] = 1;
		TickCount5[playerid] = GetTickCount();
	}
	return 1;
}



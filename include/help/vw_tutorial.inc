
//для обучения начало
//new TutTimeCounter[MAX_PLAYERS];//признак и счётчик переходов в обычном обучении
//==============================================================================
//RegistrationSTEP4
stock Tutorial(playerid)//для обучения
{
	if( TutTimeCounter[playerid] == 0 || TutTimeCounter[playerid] > 14 ) return 1;
	new bigmsgitem[1342];
	new caption[65];
    if(TutTimeCounter[playerid] == 1)
    {
    	SetPlayerTime(playerid, 5, 0);

		PlayAudioStreamForPlayerEx(playerid, "GTAtitles.mp3");
		SetTimerEx("StopAudioStreamForPlayerEx", 89000, 0, "i", playerid);

		strmid(caption, "1/14. Обучающая программа.", 0, 65, 65);
        //SetPlayerCameraPos(playerid, 1528.2993,-984.7744,100.2264);
		//SetPlayerCameraLookAt(playerid, 1313.8358,-779.9300,89.8182, CAMERA_CUT);

		TogglePlayerSpectatingEx(playerid, 1);//Переключает игрока в режим зрителя
		GetPlayerPos(playerid, Unspec[playerid][sPx], Unspec[playerid][sPy], Unspec[playerid][sPz]);
/*
	    SetPlayerPos(playerid, 155.3337, -1776.4384, 14.8978);//телепортируем чтобы загрузить текстуры
	    //TogglePlayerControllableEx(playerid, 0);//обездвиживаем чтобы не падал

	    SetPlayerCameraPos(playerid, 155.3337, -1776.4384, 14.8978);
		InterpolateCameraLookAt(playerid, 156.2734, -1776.0850, 14.2128,
			156.2713, -1776.0797, 14.7078, 5000, CAMERA_MOVE);
*/
	    SetPlayerPosEx(playerid, 155.3337, -1776.4384, 14.8978+5.0, 0);
	    SetPlayerCameraPos(playerid, 155.3337, -1776.4384, 14.8978);

		SetPlayerCameraLookAt(playerid, 156.2734, -1776.0850, 14.2128);
		InterpolateCameraLookAt(playerid, 156.2734, -1776.0850, 14.2128, 156.2713, -1776.0797, 14.7078, 5000, CAMERA_MOVE);


		//for(new i = 0; i != 32; i++) SendClientMessage(playerid, -1, " ");

		strins(bigmsgitem, "Здравствуйте, уважаемый игрок. Мы рады приветствовать вас на сервере ", strlen(bigmsgitem));
		strins(bigmsgitem, SERVERNAME, strlen(bigmsgitem));
        strins(bigmsgitem, "\nРегистрация осуществляется посредством почтового ящика. Если такого", strlen(bigmsgitem));
        strins(bigmsgitem, "\nящика у вас нет - выйдите из обучения и зарегистрируйте ящик. Ваш e-mail не должен превышать 34 символа. Кроме того, ", strlen(bigmsgitem));
        strins(bigmsgitem, "\nво время обучения не нажимайте никаких клавиш. Исключение - клавиша F8. Нажав на неё, вы сделаете скриншот, который", strlen(bigmsgitem));
        strins(bigmsgitem, "\nсохранится в папке 'GTA San Andreas User Files' в 'Моих документах'. Стоит делать снимки экрана, т.к. в тексте", strlen(bigmsgitem));
		strins(bigmsgitem, "\nобучения будет много ссылок, которые трудно запомнить. Читайте обучение очень внимательно - оно призвано облегчить", strlen(bigmsgitem));
		strins(bigmsgitem, "\nвам игру. Из текста вы узнаете о статусе сервера, о его особенностях, о том, чем он выделяется. Мы расскажем вам", strlen(bigmsgitem));
		strins(bigmsgitem, "\nо владении транспортом, о финансовой системе штата, о системе уровней и 'прокачке'. Вы узнаете про общественный", strlen(bigmsgitem));
		strins(bigmsgitem, "\nтранспорт, навигацию; про систему чатов и их закрепление. Словом, немного терпения - и вам будет проще начать играть.", strlen(bigmsgitem));
		SetPlayerWeather(playerid, 13);
    }
	else if(TutTimeCounter[playerid] == 2)
	{
		SetPlayerTime(playerid, 7, 0);
		strmid(caption, "2/14. Режим сервера.", 0, 65, 65);
		//SetPlayerCameraPos(playerid, 810.7180,-1574.1024,64.0412);//ЛС
		//SetPlayerCameraLookAt(playerid, 1092.4534,-1425.0264,30.4647, CAMERA_CUT);

	    InterpolateCameraPos(playerid, 187.600982,-1791.727050,119.087432, 193.731567,-1789.235473,118.845245, 5000);
		InterpolateCameraLookAt(playerid, 189.006942, -1790.279785, 114.512641, 195.057144, -1788.512817, 114.078620, 5000);

		strins(bigmsgitem, "Жанр сервера можно обозначить как 'социально-экономический симулятор жизни'. Мы живём в одном из американских штатов -", strlen(bigmsgitem));
		strins(bigmsgitem, "\nСан Андреасе. Наше Правительство заботится о нас, выдавая помощь малоимущим и принимая законы. Губернатор выбирается", strlen(bigmsgitem));
		strins(bigmsgitem, "\nна определённый срок всенародным голосованием. Наш покой охраняют Армия, ДПС и ФБР. Медики из Минздрава лечат нас, ", strlen(bigmsgitem));
		strins(bigmsgitem, "\nесли мы болеем, инструкторы выдают лицензии. Студия САН проводит новостные выпуски и викторины с конкурсами. Однако", strlen(bigmsgitem));
		strins(bigmsgitem, "\nу штата есть ещё одна теневая сторона - это преступные Семьи и уличные банды, зарабатывающие рэкетом, продажей", strlen(bigmsgitem));
		strins(bigmsgitem, "\nоружия, наркотиков. Департамент и криминалитет ведут бесконечную войну. Мы же - механики, автоугонщики, дорожные", strlen(bigmsgitem));
		strins(bigmsgitem, "\nрабочие, автодилеры, владельцы магазинчиков и ресторанов - ежедневно трудимся, чтобы заработать и принести домой", strlen(bigmsgitem));
		strins(bigmsgitem, "\nденьги. Мы женимся и разводимся, участвуем в выборах или сидим в КПЗ. По вечерам мы отдыхаем в клубах, устраиваем", strlen(bigmsgitem));
		strins(bigmsgitem, "\nнелегальные гонки, дерёмся на ринге, ходим с друзьями в пейнтбол, посещаем дерби. Словом, живём своей жизнью.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 3)
	{
		SetPlayerTime(playerid, 9, 0);
		strmid(caption, "3/14. Отличительные черты.", 0, 65, 65);
		//SetPlayerCameraPos(playerid, -1078.7716,1340.1995,52.3930);//СФ
		//SetPlayerCameraLookAt(playerid, -1617.2352,945.8327,29.4766, CAMERA_CUT);
	    InterpolateCameraPos(playerid, 300.803771, -1753.841796, 59.482250, 332.887237, -1753.466674, 60.534908, 4000);
		InterpolateCameraLookAt(playerid, 302.467315, -1749.504394, 57.633026, 334.005126, -1748.907470, 58.813385, 4000);

		strins(bigmsgitem, "Существует очень много серверов SA-MP, но очень много людей выбрали для игры именно ", strlen(bigmsgitem));
		strins(bigmsgitem, SERVERNAME, strlen(bigmsgitem));
		strins(bigmsgitem, ". Сейчас мы", strlen(bigmsgitem));
		strins(bigmsgitem, "\nрасскажем, чем наш сервер выделяется на фоне остальных. У нас есть собственный сайт, на котором можно найти всю", strlen(bigmsgitem));
		strins(bigmsgitem, "\nнужную информацию. Наша статистика даёт возможность видеть все характеристики любого игрока. Фракции и работы", strlen(bigmsgitem));
		strins(bigmsgitem, "\nотлично сбалансированы.  Мод постоянно дорабатывается, причём разработчик прислушивается к предложениям игроков", strlen(bigmsgitem));
		strins(bigmsgitem, "\n и воплощает их в жизнь. Античиты сервера тонко настроены и постоянно модернизируются, что даёт возможность", strlen(bigmsgitem));
		strins(bigmsgitem, "\nсвоевременно выявлять и отключать от игры читеров. Для любителей погонять у нас есть система гонок и дерби. Если вы любите", strlen(bigmsgitem));
		strins(bigmsgitem, "\nпострелять,то Paintball Arena ждёт Вас. Новичков ждёт интерактивное обучение, которое в игровой форме познакомит с основами", strlen(bigmsgitem));
		strins(bigmsgitem, "\nигры на сервере. Пройдя его, они получат награду в виде суммы денег и начального уважения.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 4)
	{
		SetPlayerTime(playerid, 13, 0);
		//SetPlayerCameraPos(playerid, -1947.2998,-33.9289,77.7945);//АШ
		//SetPlayerCameraLookAt(playerid, -2053.7312,-103.1463,40.7889, CAMERA_CUT);
	    InterpolateCameraPos(playerid, 169.602859, -1775.647705, 6.933395, 169.617141, -1776.156250, 12.790164, 5000);
		InterpolateCameraLookAt(playerid, 169.547332, -1770.651367, 7.117267, 169.588928, -1771.159301, 12.618641, 5000);

		strmid(caption, "4/14. Система владения транспортом.", 0, 65, 65);

		strins(bigmsgitem, "Иметь транспорт жизненно необходимо для комфортной игры. Один игрок может владеть тремя единицами транспорта при наличии дома или бизнеса.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nПриобрести новую машину можно у автодилеров в автосалоне Сан-Фиерро или подержанную в паркинге Лас-Вентураса.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nКоманда /carinfo содержит данные о всём серверном транспорте и его цене. Перед тем, как покупать машину - узнайте", strlen(bigmsgitem));
		strins(bigmsgitem, "\nеё цену в /carinfo, чтобы не быть обманутым автодилером. Для того, чтобы управлять техникой, НЕ нужны лицензии.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nНо если вы не хотите лишний раз платить штраф, то Вам необходимо посетить АвтоШколу в Сан-Фиерро", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЛицензия на автомобили доступна с 1 уровня, лицензия на лодки и пилотирование самолётов и", strlen(bigmsgitem));
		strins(bigmsgitem, "\nвертолётов - со 2 уровня, лицензия на мотоцикл - с 10 уровня. Приобретя машину, купите замок для неё в магазине 24/7.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nМашина при работе двигателя расходует бензин. Не забывайте заправляться на многочисленных заправках по всему штату.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nМашину можно запарковать командой /parking или клавишей num4. ", strlen(bigmsgitem));
		strins(bigmsgitem, "\nПока вы её не распаркуете (/unparking или клавишей num6), с ней ничего не случится.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nКомандой /lock(Alt+Space) можно открыть/закрыть двери.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nКомандой (/engine) завести двигатель. Или используйте автоменю клавишей (2)", strlen(bigmsgitem));
		strins(bigmsgitem, "\nОпасайтесь автоугонщиков. Не распарковывайте машину, если рядом стоит посторонний.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 5)
	{
		SetPlayerTime(playerid, 15, 0);
		strmid(caption, "5/14. Финансовая система.", 0, 65, 65);
		//SetPlayerCameraPos(playerid, -866.9181,1477.3292,36.4689);//Банк
		//SetPlayerCameraLookAt(playerid, -824.9084,1504.1040,19.8339, CAMERA_CUT);
	    InterpolateCameraPos(playerid, 386.273284, -2030.129516, 59.993469, 395.822113, -2044.595703, 59.993469, 5000);
		InterpolateCameraLookAt(playerid, 386.591949, -2029.832275, 55.012496, 396.252319, -2044.526245, 55.012496, 5000);

		strins(bigmsgitem, "Официальной валютой считается доллар. Деньги - основной ресурс этого мира. Деньгами вы будете расплачиваться за еду", strlen(bigmsgitem));
		strins(bigmsgitem, "\nи услуги медиков и механиков; за деньги можно приобрести автомобиль, дом, бизнес или воспользоваться услугами.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЗаработать деньги можно, устроившись на одну из работ в Мэрии либо попав во фракцию или банду. Кроме того, время", strlen(bigmsgitem));
		strins(bigmsgitem, "\nот времени Правительство выдаёт социальные пакеты нуждающимся гражданам в Мэрии. Следите за объявлениями.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nВ штате действует государственный банк. Поэтому вверху справа будут отображаться два счётчика денег: нижний - сумма", strlen(bigmsgitem));
		strins(bigmsgitem, "\nу вас в кармане, верхний - сумма, лежащая на счету в банке. Наличность можно передать другому игроку командой", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/pay id сумма. Максимальный размер передаваемой суммы - 1.000.000 долларов на 3 уровне. Добравшись до банка и зайдя", strlen(bigmsgitem));
		strins(bigmsgitem, "\nна красный маркер, вы получите возможность полностью распоряжаться своими деньгами: передавать их на счёт другому", strlen(bigmsgitem));
		strins(bigmsgitem, "\nигроку, класть их на депозит и получать проценты. Словом, грамотный подход даст возможность отлично заработать.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 6)
	{
		SetPlayerTime(playerid, 17, 0);
		strmid(caption, "6/14. Общественный транспорт и навигация.", 0, 65, 65);
		//SetPlayerCameraPos(playerid, -2410.1316,152.6538,101.9643);//Мэрия
		//SetPlayerCameraLookAt(playerid, -2420.5745,334.9571,46.6400, CAMERA_CUT);
	    InterpolateCameraPos(playerid, 341.018402, -2095.904052, 6.937077, 342.805603, -2096.498535, 6.648118, 5000);
		InterpolateCameraLookAt(playerid, 345.258972, -2093.501220, 5.821543, 347.304443, -2094.563964, 5.639461, 5000);

		strins(bigmsgitem, "В штате работает бесплатный государственный общественный транспорт: самолёты, поезда, автобусы и такси.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nИх маршруты взаимосвязаны: самолёты летают между городами против часовой стрелки, а поезда ездят наоборот по часовой.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nВ каждом городе между вокзалом и основной точкой работает 2 такси и 1 автобус", strlen(bigmsgitem));
		strins(bigmsgitem, "\nНа вокзале можно сесть в такси, который доставит вас в следующий пункт, согласно надписи сверху, или на автобус", strlen(bigmsgitem));
		strins(bigmsgitem, "\nкоторый вас доставит в аэропорт. Общественный транспорт(кроме поездов и самолётов) может останавливаться по дороге", strlen(bigmsgitem));
		strins(bigmsgitem, "\nдля подбора попутчиков. Всегда стойте на правом тратуаре по ходу движения, чтобы такси или автобус ваз заметил.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nДля навигации используйте /gps. После ввода этой команды вы увидите таблицу, которая содержит координаты всех", strlen(bigmsgitem));
		strins(bigmsgitem, "\nзначимых точек штата, отсортированных по городам. Например, чтобы пометить Мэрию, введите /gps 1014.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 7)
	{
		SetPlayerTime(playerid, 19, 0);
		strmid(caption, "7/14. Система уровней и перков.", 0, 65, 65);
		//SetPlayerCameraPos(playerid, -2027.1156,112.4540,49.6482);//Вокзал СФ
		//SetPlayerCameraLookAt(playerid, -1978.6957,138.3720,27.6875, CAMERA_CUT);
	    InterpolateCameraPos(playerid, 481.641052, -1804.006835, 6.803627, 484.250549, -1802.375244, 6.660738, 5000);
		InterpolateCameraLookAt(playerid, 485.734344, -1801.318481, 5.794973, 488.679290, -1800.236572, 5.759444, 5000);
/*
		strins(bigmsgitem, "Зайдя на сервер и введя /stats, вы увидите, что у вас 0 уровень. Проведя в игре час, вы получите 10 очков опыта.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nУровень даётся при достижении определённого кол-ва очков. Очки даются за деньги, навыки, время игры и т.п. Очки можно посмотреть в", strlen(bigmsgitem));
		strins(bigmsgitem, "\nсвоём профиле в статистике. Уровень повышается автоматически. Уровни дают преимущества: со 2-го можно купить лицензии на", strlen(bigmsgitem));
		strins(bigmsgitem, "\nлодки, пилотирование и рыбалку. На 3-ем возможность купить лицензию", strlen(bigmsgitem));
		strins(bigmsgitem, "\nна оружие. С 10-го уровня доступна лицензия на мототранспорт. Следует помнить, что очень высокие уровни порой", strlen(bigmsgitem));
		strins(bigmsgitem, "\nвредны: чем выше уровень, тем больше вам нужно платить за лечение, тем выше штрафы за нарушения ПДД, тем выше налог.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nКроме того, дома на сервере рассчитаны на определённый уровень. Чем выше ваш уровень - тем выше уровень дома, и, следовательно, ", strlen(bigmsgitem));
		strins(bigmsgitem, "\nцена за электричество.Но при достижении 24 уровня вы сможете купить дом любого уровня.
*/
/*
		strins(bigmsgitem, "Зайдя на сервер и введя /stats, вы увидите, что у вас 1 уровень. Проведя в игре час, вы получите одно очко опыта.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nНабрав 8 таких очков и имея 5.000, вы сможете повысить свой уровень до второго. До третьего уровня - 12 часов и", strlen(bigmsgitem));
		strins(bigmsgitem, "\n7.500, для четвёртого - 16 часов и 10.000 и так далее. Уровни дают преимущества: со 2-го можно купить лицензии на", strlen(bigmsgitem));
		strins(bigmsgitem, "\nлодки, пилотирование и рыбалку. На 3-ем вы получаете право голосовать на выборах и возможность купить лицензию", strlen(bigmsgitem));
		strins(bigmsgitem, "\nна оружие. С 10-го уровня доступна лицензия на мототранспорт. Следует помнить, что очень высокие уровни порой", strlen(bigmsgitem));
		strins(bigmsgitem, "\nвредны: чем выше уровень, тем больше вам нужно платить за лечение, тем выше штрафы за нарушения ПДД, тем выше налог.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nКроме того, дома на сервере рассчитаны на определённый уровень. Чем выше ваш уровень - тем выше уровень дома, и, следовательно, ", strlen(bigmsgitem));
		strins(bigmsgitem, "\nцена за электричество будет очень высокой, но при этом можно будет прямо в доме переодеваться. Перки даются с каждым уровнем", strlen(bigmsgitem));
		strins(bigmsgitem, "\nи позволяют специализировать вашего персонажа. Взяв, например, перк, связанный с работой, вы будете трудиться успешнее и т.д.", strlen(bigmsgitem));
*/

		strins(bigmsgitem, "Зайдя на сервер и введя /stats, вы увидите, что у вас 1 уровень. Проведя в игре 55 минут ", strlen(bigmsgitem));
		strins(bigmsgitem, "\nВам засчитается час и начислятся очки с учётом ваших достижений. Уровень даётся при достижении определённого кол-ва очков.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nОчки даются за часы, скиллы, убийства, навыки, деньги, но за смерти они снимаются.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nОчки можно посмотреть при помощи команды /score или в Статистике. Уровни дают преимущества: со 2-го можно купить", strlen(bigmsgitem));
		strins(bigmsgitem, "\nлицензии на лодки, пилотирование и рыбалку. На 3-ем вы получаете право голосовать на выборах и возможность купить лицензию", strlen(bigmsgitem));
		strins(bigmsgitem, "\nна оружие. С 10-го уровня доступна лицензия на мототранспорт. Следует помнить, что очень высокие уровни порой", strlen(bigmsgitem));
		strins(bigmsgitem, "\nвредны: чем выше уровень, тем больше вам нужно платить за лечение, тем выше штрафы за нарушения ПДД, тем выше налог.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nКроме того, дома на сервере рассчитаны на определённый уровень. Чем выше ваш уровень - тем выше уровень дома", strlen(bigmsgitem));
		strins(bigmsgitem, "\nвы можете себе позволить и при этом можно будет прямо в доме переодеваться. Перки даются с каждым уровнем", strlen(bigmsgitem));
		strins(bigmsgitem, "\nи позволяют специализировать вашего персонажа. Взяв, например, перк, связанный с работой, вы будете трудиться успешнее и т.д.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 8)
	{
		SetPlayerTime(playerid, 21, 0);
		strmid(caption, "8/14. Рекомендации по общению.", 0, 65, 65);
		//SetPlayerCameraPos(playerid, 1488.6250,-1612.5281,29.8676);//Участок ЛС
		//SetPlayerCameraLookAt(playerid, 1553.9508,-1672.4800,16.6719, CAMERA_CUT);
	    InterpolateCameraPos(playerid, 662.689147, -1868.981201, 6.513285, 665.048583, -1870.174438, 6.864079, 5000);
		InterpolateCameraLookAt(playerid, 658.142028, -1867.027709, 5.800874, 661.006286, -1867.294311, 6.260089, 5000);

		strins(bigmsgitem, "Телефон - самый первый предмет, который вы купите. Чтобы позвонить или отправить SMS, нажмите TAB и выберите", strlen(bigmsgitem));
		strins(bigmsgitem, "\nабонента. Если вам звонят, поднимите трубку, введя /h (чтобы положить - /p). На сервере работает целая система чатов.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЧтобы сказать что-нибудь в радиусе 30 метров, вызовите консоль (F6), напишите нужный текст и нажмите на Enter.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nДля того чтобы 'крикнуть' в радиусе 60 метров - в консоли введите /s нужный текст. Если вы хотите сообщить что-нибудь, ", strlen(bigmsgitem));
		strins(bigmsgitem, "\nприватное - вам нужен 'шёпот': /w id нужный текст. Радиус этого сообщения - 8 метров, и другие игроки не могут увидеть", strlen(bigmsgitem));
		strins(bigmsgitem, "\nего. Существует ещё чат, символы которого отображаются над головой персонажа - /me нужный текст. Если вам нужно ", strlen(bigmsgitem));
		strins(bigmsgitem, "\n'прокричать' несколько раз подряд, не нужно каждый раз вводить /s перед текстом, т.к. активный чат закрепляется.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nСимвол текущего активного чата отображён вверху справа возле денег. Для того, чтобы вернуть обычный чат - введите /0.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЭто сделано для удобства, если вы часто общаетесь через несколько чатов. Закрепление чатов можно отключить.", strlen(bigmsgitem));

		strins(bigmsgitem, "\nТак же вы можете произвести анонимный звонок. Подойдя к таксофону(белый телефон на стене в Мэрии)", strlen(bigmsgitem));
		strins(bigmsgitem, "\nили зайдя в телефонную будку около дороги вы можете позвонить любому игроку, выбрав его ник в TAB,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nно этот звонок будет анонимным, игрок не узнает вашего имени.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 9)
	{
		SetPlayerTime(playerid, 23, 0);
		strmid(caption, "9/14. Основные термины и сокращения, используемые в игре.", 0, 65, 65);
		//SetPlayerCameraPos(playerid, 233.0978,1934.6124,39.0344);//Зона 51
		//SetPlayerCameraLookAt(playerid, 203.6889,1866.8608,18.5625, CAMERA_CUT);
	    InterpolateCameraPos(playerid, 542.343933, -1901.457519, 2.008791, 544.523376, -1901.883666, 2.085470, 5000);
		InterpolateCameraLookAt(playerid, 544.995666, -1897.256958, 2.577868, 546.892395, -1897.521118, 2.681705, 5000);

		strins(bigmsgitem, "Лос-Сантос (ЛС, 1-ый город) - город, в котором вы появитесь, зайдя на сервер. Ключевые здания: мотель Джефферсона, ", strlen(bigmsgitem));
		strins(bigmsgitem, "\nздание CNN для курьеров, наркопритон, дерби 8ball. Сан-Фиерро (СФ, 2-ой город) - город, в котором расположена Мэрия, ", strlen(bigmsgitem));
		strins(bigmsgitem, "\nавтошкола, автосалон. Лас-Вентурас (ЛВ, 3-ий город) - город, в котором находится паркинг, студия САН. Автошкола - АШ.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЦентральная больница (ЦБ) есть в каждом городе. Часто пишут - 'Медики в ЦБ ЛС'. Респаун - место появления на сервере.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nID - идентификационный номер, присваиваемый каждому игроку, входящему на сервер. ИДы людей можно увидеть, нажав на", strlen(bigmsgitem));
		strins(bigmsgitem, "\n'TAB'. Скилл - навык, умение игрока. Повышается в процессе работы и даёт преимущества. Респект - очко опыта, которое", strlen(bigmsgitem));
		strins(bigmsgitem, "\nвы получите за отыгранный час. Левел - текущий уровень персонажа. ХП - показатель здоровья. Админ - представитель", strlen(bigmsgitem));
		strins(bigmsgitem, "\nадминистрации сервера. НГ (национальная Гвардия) - армия штата. ГМ - годмод, чит-программа, дающая бессмертие. СХ -", strlen(bigmsgitem));
		strins(bigmsgitem, "\nспидхак, чит-программа, увеличивающая скорость. ТП - телепортирование персонажа.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 10)
	{
		SetPlayerTime(playerid, 3, 0);
		strmid(caption, "10/14. Система Потребностей.", 0, 65, 65);
		//SetPlayerCameraPos(playerid, 1243.6803,-1273.6001,40.6886);
		//SetPlayerCameraLookAt(playerid, 1176.9855,-1322.7911,14.0483, CAMERA_CUT);
		InterpolateCameraPos(playerid, 329.131469, -1791.461791, 15.695193, 326.005981, -1793.169311, 15.695193, 3000);
		InterpolateCameraLookAt(playerid, 326.451660, -1787.321044, 14.874702, 323.228546, -1789.171630, 14.553024, 3000);

		strins(bigmsgitem, "Каждый игрок - социальное существо, которое имеет список потребностей: голод, досуг, общение, туалет, бодрость.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЕсли персонаж достигнет уровня потребности, то начнут срабатывать различного рода неудобства.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЧтобы открыть таблицу потребностей нажмите клавишу Alt, находясь вне транспорта. Описание потребностей:", strlen(bigmsgitem));
		strins(bigmsgitem, "\n1) Голод. При достижении полной полосы начинает отниматься здоровье: по 10 единиц в минуту.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nПогасить данную потребность можно, в закусочных и ресторанах.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nБары, автоматы не относятся к этому списку. Время заполнения шкалы 3 часа", strlen(bigmsgitem));
		strins(bigmsgitem, "\n2) Досуг. При заполнении полосы игрок не может выйти на дежурство, cесть в авто. Время заполнения шкалы 4 ч. ", strlen(bigmsgitem));
		strins(bigmsgitem, "\nПогашение: танцуете в клубе (/dance 1-4) 2 мин. Или выпить спиртное: пиво гасит 10 единиц досуга из 50.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n3) Общение. При заполнении шкалы невозможно пользоваться чатами (/me, /s и т.д.). Время заполнения шкалы 5 ч.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nОдно сообщение чата уменьшает на еденицу параметр. Погасить потребность можно поговорив по телефону.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n4) Туалет.При заполнении шкалы выводится сообщение в чат.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nПогашение: командой /piss в течении 1 мин. Время заполнения шкалы 6 ч.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n5) Бодрость.Признаки заполнения шкалы: сообщение в чат и потемнение изображения на мониторе в течение 5 сек.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nГашение: заходите в дом(мотель), забираетесь на кровать, спите 1 минуту(/bedl, /bedr). Время заполнения шкалы 7 ч.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 11)
	{
		SetPlayerTime(playerid, 5, 0);
		//SetPlayerCameraPos(playerid, 2213.1982,-1103.3405,54.7576);//Мотель ЛС
		//SetPlayerCameraLookAt(playerid, 2201.2935,-1137.9199,38.1016, CAMERA_CUT);
		InterpolateCameraPos(playerid, 514.983886, -1760.605102, 17.303379, 514.898010, -1760.553955, 18.443613, 3000);
		InterpolateCameraLookAt(playerid, 519.002807, -1762.556640, 15.058471, 519.071899, -1762.496826, 16.493217, 3000);

        strmid(caption, "11/14. Система знакомств", 0, 65, 65);

		strins(bigmsgitem, "На нашем сервере реализована система знакомств, т.е. при входе вы не знаете никого,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nник-неймы игроков для вас скрыты. Но со временем, осваиваясь в штате, вы знакомитесь с большим кол-вом", strlen(bigmsgitem));
		strins(bigmsgitem, "\nигроков, заводите дружеские связи. Чтобы познакомиться с игроком, выберите его ник в TAB,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nщёлкните 2 раза по нему, в появившемся окошке выберите пункт 'Поздороваться'.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nТакже есть и другой способ. Подойдите к игроку, нацельтесь на него Правой Кнопкой Мыши(прицел)", strlen(bigmsgitem));
		strins(bigmsgitem, "\nи потом нажмите Левую Кнопку Мыши(клавиша удара). Перед вами всё то же окошко.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n Выберите пункт 'Поздороваться'. Теперь игрок увидел ваш ник-нейм. Чтобы вы увидели ник игрока,", strlen(bigmsgitem));
		strins(bigmsgitem, "\n он должен с вами познакомиться.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nТак же через появляющееся окошко можно передать деньги игроку, выразить уважение/презрение", strlen(bigmsgitem));
		strins(bigmsgitem, "\nотносительно его действий, показать паспорт.", strlen(bigmsgitem));
    }
	else if(TutTimeCounter[playerid] == 12)
	{
		SetPlayerTime(playerid, 11, 0);
		//SetPlayerCameraPos(playerid, 2100.5708,1830.5414,60.7640);//ЛВ
		//SetPlayerCameraLookAt(playerid, 2250.2195,1899.3684,10.8203, CAMERA_CUT);
	    InterpolateCameraPos(playerid, 350.840972, -1794.716308, 13.146982, 346.193756, -1800.415649, 10.697548, 8000);
		InterpolateCameraLookAt(playerid, 348.053558, -1790.653564, 12.295993, 342.141357, -1797.657592, 9.712170, 8000);

		strmid(caption, "12/14. Сайт, Cтатистика, Форум и TeamSpeak.", 0, 65, 65);

		strins(bigmsgitem, "Статистика игроков: http://", strlen(bigmsgitem));
		strins(bigmsgitem, HostName, strlen(bigmsgitem));

		strins(bigmsgitem, "\nWiki: http://sa-mp.iam.by/wiki/index.php/VirtualWorld", strlen(bigmsgitem));

		strins(bigmsgitem, "\nForum: ", strlen(bigmsgitem));
		strins(bigmsgitem, FORUM, strlen(bigmsgitem));

	    //strins(bigmsgitem, "\nTeamSpeak3 BY Server Address: vpn.by:9990. Channel: GTA:SA Virtual World", strlen(bigmsgitem));
	    //strins(bigmsgitem, "\nTeamSpeak3 RU Server Address: ts.strikearena.ru. Channel: SAMP Virtual Word", strlen(bigmsgitem));

		strins(bigmsgitem, "\nСтатистика нашего сервера даёт всю информацию о каждом игроке: уровень, количество денег, наличие", strlen(bigmsgitem));
		strins(bigmsgitem, "\nдома, бизнеса, транспорта, количество арестов, смертей и убийств. Словом, всё, что можно представить. Кроме того, ", strlen(bigmsgitem));
		strins(bigmsgitem, "\nтам можно посмотреть состав фракций, список забаненных, а также 'Зал славы' - лучших в своём деле профессионалов.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nУ нашего сервера есть Wiki(энциклопедия посвящённая нашему моду).", strlen(bigmsgitem));
		strins(bigmsgitem, "\nОн содержит всю необходимую информацию для комфортной игры: особенности, FAQ, руководства, советы, ", strlen(bigmsgitem));
		strins(bigmsgitem, "\nисторию разработки сервера, Уголовный и Административный кодексы, обучающее видео и многое другое.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 13)
	{
		SetPlayerTime(playerid, 1, 0);
		strmid(caption, "13/14. Советы новичку.", 0, 65, 65);
		//SetPlayerCameraPos(playerid, 1528.2993,-984.7744,100.2264);//ЛС
		//SetPlayerCameraLookAt(playerid, 1313.8358,-779.9300,89.8182, CAMERA_CUT);
	    InterpolateCameraPos(playerid, 542.945800, -1863.699707, 4.435829, 539.996215, -1863.695556, 4.304386, 5000);
		InterpolateCameraLookAt(playerid, 537.950744, -1863.694213, 4.213245, 535.009887, -1863.990478, 4.081802, 5000);

		strins(bigmsgitem, "Ещё немного, и вы станете игроком нашего сервера. Советуем вам сразу определиться, кем вы планируете здесь стать. Если", strlen(bigmsgitem));
		strins(bigmsgitem, "\nслужителем закона, то не стоит нарушать этот самый закон. Большое кол-во преступлений ограничит для вас вступление во", strlen(bigmsgitem));
		strins(bigmsgitem, "\nфракцию. Если вам по душе быть наёмным убийцей - следите, чтобы количество ваших смертей не было слишком высоким, иначе путь", strlen(bigmsgitem));
		strins(bigmsgitem, "\nтуда будет закрыт. Хотите стать опытным механиком или дорожным рабочим - стоит отказаться от лицензии на оружие и", strlen(bigmsgitem));
		strins(bigmsgitem, "\nдоверить свою защиту полицейским. Словом, выберите себе роль и стремитесь соответствовать ей. С игроками и администрацией", strlen(bigmsgitem));
		strins(bigmsgitem, "\nобщайтесь вежливо, не отказывайте людям в помощи - и со временем о вас сложится хорошее мнение. Ни в коем случае не стоит", strlen(bigmsgitem));
		strins(bigmsgitem, "\nиспользовать чит-программы, т.к. вас рано или поздно выявят, и это станет концом репутации и карьеры. Помните, что целью", strlen(bigmsgitem));
		strins(bigmsgitem, "\nигры является получение удовольствия, общение с друзьями и подругами, приятное проведение времени в хорошей компании.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЖелаем вам удачи в достижении этой цели. Благодарим за внимание. Хорошей игры.", strlen(bigmsgitem));
	}
	else if(TutTimeCounter[playerid] == 14)
	{
		SetPlayerTime(playerid, 5, 0);
		//SetPlayerCameraPos(playerid, 2213.1982,-1103.3405,54.7576);//Мотель ЛС
		//SetPlayerCameraLookAt(playerid, 2201.2935,-1137.9199,38.1016, CAMERA_CUT);
	    InterpolateCameraPos(playerid, 514.983886, -1760.605102, 17.303379, 514.898010, -1760.553955, 18.443613, 3000);
		InterpolateCameraLookAt(playerid, 519.002807, -1762.556640, 15.058471, 519.071899, -1762.496826, 16.493217, 3000);

        strmid(caption, "14/14. В заключение.", 0, 65, 65);

		strins(bigmsgitem, "Обучение подходит к концу. Вы в шаге от того, чтобы начать регистрацию. Даже если текст выше был прочитан", strlen(bigmsgitem));
		strins(bigmsgitem, "\nвнимательно, часто возникает множество вопросов по ходу игры. Задать их можно Helper`aм, введя /question.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nБудьте вежливы - и вам помогут. А ещё можно попросить одного из игроков стать вашим наставником, ", strlen(bigmsgitem));
		strins(bigmsgitem, "\nдля этого есть команда /accept referal. Вы сможете задавать ему вопросы, вводя /re текст.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nСписок игровых команд доступен после введения /help. Не нарушайте игровые правила /rules, играйте честно, не используя", strlen(bigmsgitem));
		strins(bigmsgitem, "\nсторонних чит-программ. Перед вами открыты все дороги: станьте неподкупным защитником закона или матёрым преступником, ", strlen(bigmsgitem));
		strins(bigmsgitem, "\nсамым опытным оружейником или наркодилером. Возможно, вам понравится крутить баранку своего тягача или построить", strlen(bigmsgitem));
		strins(bigmsgitem, "\nфинансовую империю. Помните, главная цель - получить удовольствие от игры, найти друзей и подруг, приятно провести", strlen(bigmsgitem));
		strins(bigmsgitem, "\nвремя в хорошей компании. Желаем вам удачи в достижении этой цели. Спасибо за внимание. Хорошей игры.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n\nЕсли вы в чате увидели такую надпись:", strlen(bigmsgitem));
		strins(bigmsgitem, "\n{FF0000}CEPBEP: [ваш ник] был забанен, причина: ...", strlen(bigmsgitem));
		strins(bigmsgitem, "\n{A9C4E4}то обязательно сделайте скриншот клавишей F8, перед тем как выходить из игры.", strlen(bigmsgitem));
    }
	if(strlen(bigmsgitem) > sizeof(bigmsgitem))
	{
		//ИНФОРМИРОВАНИЕ
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "Error8: Tutorial %s[%d], strlen(bigmsgitem): %d, sizeof(bigmsgitem): %d",
			PlayerName(playerid), playerid, strlen(bigmsgitem), sizeof(bigmsgitem));
		Log(ERROR, strings);
		return 1;
	}
	ShowPlayerDialogEx(playerid, TUTORIAL_DIALOG, DIALOG_STYLE_MSGBOX, caption, bigmsgitem, "Назад", "Далее");//RegistrationSTEP5
	return 1;
}

stock tutorial_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != TUTORIAL_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
//ShowPlayerDialogEx(playerid, TUTORIAL_DIALOG, DIALOG_STYLE_MSGBOX, caption, bigmsgitem, "Назад", "Далее");
	if(response)
	{//если нажали НАЗАД
	    TutTimeCounter[playerid] --;//счётчик
	    if(TutTimeCounter[playerid] < 1) TutTimeCounter[playerid] = 1;
		Tutorial(playerid);
		return 1;
	}
//если нажали ДАЛЕЕ
    TutTimeCounter[playerid] ++;//счётчик
	if(TutTimeCounter[playerid] > 14)
	{
	    //InterpolateCameraPos(playerid, 524.473022, -1763.555786, 14.948656, 524.520751, -1763.556152, 15.495350, 5000);
		//InterpolateCameraLookAt(playerid, 519.486999, -1763.304687, 14.671454, 519.540893, -1763.958007, 15.296504, 5000);
		//StopAudioStreamForPlayer(playerid);
//TutTimeCounter[playerid] = 0;
	 	//if(GetPVarInt(playerid, "gStatusRegistration"))
	 	/*if(PlayerInfo[playerid][pConnectTime] == 0 && !GetPVarInt(playerid, "gPlayerAccount"))
	 	{
	    	SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ok, итак, просмотрев обучение, Вы можете начать регистрацию. ");
			SetPVarInt(playerid, "gOoc", 0); SetPVarInt(playerid, "gNews", 0);
			SetPVarInt(playerid, "gFam", 0); SetPVarInt(playerid, "gHidePM", 0);
			SetPVarInt(playerid, "gSport", 0); SetPVarInt(playerid, "gJob", 0);//для чата
			//gMedicBill[playerid] = 0;
			//SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Пожалуйста, введите свой рабочий email (не более 34 символов) и нажмите REGISTER !!!!");
			//AudioMessage(playerid, "Пожалуйста, введите свой рабочий email и нажмите REGISTER.");
			RegistrationSTEP6(playerid);
		}
		else
		{*/
			TogglePlayerSpectatingEx(playerid, 0);//Переключает игрока из режима зрителя
   			SetPlayerPos(playerid, Unspec[playerid][sPx], Unspec[playerid][sPy], Unspec[playerid][sPz]);
   			TogglePlayerControllableEx(playerid, 1);//освобождаем
			SetCameraBehindPlayer(playerid);
		//}
	}
	else
	{
		Tutorial(playerid);
	}
	return 1;
}




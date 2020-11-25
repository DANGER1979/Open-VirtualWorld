
new AboutTimeCounter[MAX_PLAYERS];
stock AboutServer(playerid)
{
	new listitems[520];
    strcat(listitems, "{FFFFFF}1. {00FF00}О сервере:");
	strcat(listitems, "{FFFFFF}\n2. {00FF00}Безопасность:");
	strcat(listitems, "{FFFFFF}\n3. {00FF00}Основы игры:");
	strcat(listitems, "{FFFFFF}\n4. {00FF00}Пару советов:");
	strcat(listitems, "{FFFFFF}\n5. {00FF00}Первые шаги:");
	strcat(listitems, "{FFFFFF}\n6. {00FF00}Общение:");
	strcat(listitems, "{FFFFFF}\n7. {00FF00}Транспорт:");
	strcat(listitems, "{FFFFFF}\n8. {00FF00}Государственная система:");
	strcat(listitems, "{FFFFFF}\n9. {00FF00}Жильё:");
	strcat(listitems, "{FFFFFF}\n10.{00FF00}Бизнес и АЗС:");
	strcat(listitems, "{FFFFFF}\n11.{00FF00}Банки, хранение средств:");
	AboutTimeCounter[playerid] = 0;
	ShowPlayerDialogEx(playerid, ABOUT_DIALOG, DIALOG_STYLE_LIST, "О сервере", listitems, "OK", "Назад");
}

stock about_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if(dialogid != ABOUT_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	if(response && AboutTimeCounter[playerid] == 0)
	{//если выбрали пункт
	    AboutServerList(playerid, listitem+1);
	    //help_OnPlayerKeyStateChange(playerid);
	    return 1;
	}
	else if(response && AboutTimeCounter[playerid] > 0)
	{//если нажали НАЗАД
	    AboutTimeCounter[playerid] --;//счётчик
	    if(AboutTimeCounter[playerid] < 1)
		{
			AboutTimeCounter[playerid] = 0;
			AboutServer(playerid);
			return 1;
		}
	}
	else if(!response && AboutTimeCounter[playerid] == 0)
	{
		help_OnPlayerKeyStateChange(playerid);
		//PlaySoundForPlayer(playerid, 5202);
		return 1;
	}//если нажали Exit
	else if(!response && AboutTimeCounter[playerid] > 0)
	{//если нажали ДАЛЕЕ
	    AboutTimeCounter[playerid] ++;//счётчик
		if(AboutTimeCounter[playerid] > 11)
		{
			//TogglePlayerSpectatingEx(playerid, 0);//Переключает игрока из режима зрителя
	 		//SetPlayerPos(playerid, Unspec[playerid][sPx], Unspec[playerid][sPy], Unspec[playerid][sPz]);
	  		//TogglePlayerControllableEx(playerid, 1);//освобождаем
			//SetCameraBehindPlayer(playerid);
			PlaySoundForPlayer(playerid, 5202);
			return 1;
		}
	}
	AboutServerList(playerid, AboutTimeCounter[playerid]);
	return 1;
}
stock AboutServerList(playerid, listitem)
{
    AboutTimeCounter[playerid] = listitem;
	//if( AboutTimeCounter[playerid] == 0 || AboutTimeCounter[playerid] > 11 ) PlaySoundForPlayer(playerid, 5202); return 1;
	new bigmsgitem[2681];
	new caption[65];
    if(AboutTimeCounter[playerid] == 1)
    {
        strmid(caption, "1/11. О сервере:", 0, 65, 65);
		strins(bigmsgitem, "\nVirtual World – это не только RPG-сервер, это целый симулятор жизни", strlen(bigmsgitem));
		strins(bigmsgitem, "\nкоторый включает в себя собственную продуманную и настроенную систему экономики", strlen(bigmsgitem));
		strins(bigmsgitem, "\nи бизнеса, множество концептуально измененных профессий и фракций.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nВы можете отыгрывать роль Медика,спасая жизни, Преступника, убегая от погони,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nРепортёра, развлекая штат, Вояки, охраняя особо опасных заключённых", strlen(bigmsgitem));
		strins(bigmsgitem, "\nили простого Дальнобойщика, зарабатывая перевозкой грузов и обеспечивая процветание штата.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nVirtual World берёт для себя всё самое лучшее с различных online и single игр.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nНапример, экономическая система сервера построена на аналоге из игры Тропико,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nработа дальнобойщика и система грузоперевозок похожа на игру Дальнобойщики 2,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nсистема квестов основывалась на подобной системе из игры Космические Рейнджеры,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nThe Sims подарила серверу систему потребностей,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nа на популярном шутере Counter-Strike основываются командные перестрелки на Paintball арене.", strlen(bigmsgitem));
	}
    else if(AboutTimeCounter[playerid] == 2)
    {
		strmid(caption, "2/11. Безопасность:", 0, 65, 65);
		strins(bigmsgitem, "\nНИКОГДА и ни при каких условиях НЕ передавайте пароль от своего аккаунта другим людям", strlen(bigmsgitem));
		strins(bigmsgitem, "\n(Родителям, друзьям, знакомым, дом.животным). Администрация НЕ НЕСЁТ ответственности за ваш аккаунт.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nВремя от времени меняйте пароль на аккаунте(USE:/changepass).", strlen(bigmsgitem));
		strins(bigmsgitem, "\nПароль должен состоять из заглавных и строчных символов и цифр.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nНе используйте в пароле личную информацию(Номер телефона, дата рождения и т.п.)", strlen(bigmsgitem));
		strins(bigmsgitem, "\nПример хорошего пароля: Qfg25L4Nt Пример плохого: 123qwe", strlen(bigmsgitem));
	}
    else if(AboutTimeCounter[playerid] == 3)
    {
		strmid(caption, "3/11. Основы игры:", 0, 65, 65);
		strcat(bigmsgitem, "Играя на сервере, Вы получаете очки опыта. При накоплении их", strlen(bigmsgitem));
		strcat(bigmsgitem, "\nопределённого количества происходит переход на следующий уровень.", strlen(bigmsgitem));
		strcat(bigmsgitem, "\nС каждым новым уровнем открываются новые возможности и", strlen(bigmsgitem));
		strcat(bigmsgitem, "\nстановится доступные более интересные функции.", strlen(bigmsgitem));
		strcat(bigmsgitem, "\nДля просмотра статистики воспользуйтесь командой /menu. В игровом", strlen(bigmsgitem));
		strcat(bigmsgitem, "\nпроцессе постоянно нужно будет пользоваться подобными командами.", strlen(bigmsgitem));
		strcat(bigmsgitem, "\nОни вводятся в игровой чат (F6) через косую черту, например /help и т.п.", strlen(bigmsgitem));
		strcat(bigmsgitem, "\nВведите /menu, далее выберите пункт 'Список команд'. Там", strlen(bigmsgitem));
		strcat(bigmsgitem, "\nрасположен полный перечень команд, а также кнопка 'Описание команд'", strlen(bigmsgitem));
		strcat(bigmsgitem, "\nдля пояснения каждой их них", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЗайдя на сервер вы очутитесь с тяжёлым портфелем на плечах.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nНа данный момент цель у вас одна: подзаработать немного деньжат.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nНо, как говорят, бесплатный сыр бывает только в мышеловке,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nтак что вы должны будете немного попотеть, чтобы реализоваться в штате.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЕсли у вас возик вопрос 'Как?', то прочтите пункт 'Первые шаги' в данном обучении.", strlen(bigmsgitem));
	}
    else if(AboutTimeCounter[playerid] == 4)
    {
		strmid(caption, "4/11. Пару советов:", 0, 65, 65);
 		strins(bigmsgitem, "\n1) Команды вводятся в окне чата (F6) при помощи слэша (наклонной черты /) и самой команды.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nПример : /help Потом нажимается Enter.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n2) Для написания сообщения достаточно открыть окно чата (F6) ввести команду на активацию чата", strlen(bigmsgitem));
		strins(bigmsgitem, "\n(/s к примеру), сделать пробел и написать само сообщение.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЕсли вы захочете ещё раз написать в чат, то можете не пользоваться командой,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nа просто писать в чат. Это называется закрепление чата.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЧто бы продолжить писать в простой чат наберите /0 (ноль)", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЧтобы узнать список чатов введите /menu, выберите пункт Список команд, а потом пункт Чат.", strlen(bigmsgitem));
		strins(bigmsgitem, "\n3) Чтобы узнать список доступных команд введите [/help] или нажмите клавишу H", strlen(bigmsgitem));
		strins(bigmsgitem, "\n4) Если у вас будут возникать вопросы, то задайте их в [/question]", strlen(bigmsgitem));
		strins(bigmsgitem, "\n5) Узнать все важные места в штате можнo, введя [/gps]", strlen(bigmsgitem));
		strins(bigmsgitem, "\n6) Обязательно купите себе телефон в сети магазинов 24/7(Розовый стаканчик на радаре).", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЗайдя внутрь вы увидите красный маркер. Станьте на него и выбeрите 1 пункт - 'CellPhone'", strlen(bigmsgitem));
		strins(bigmsgitem, "\n7) С 3 уровня на вас насчнут действовать потребности.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЧтобы посмотреть их заполненность нажмите Левый Alt ВНЕ авто.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЧтобы подробнее узнать про систему потребностей введите [/help],", strlen(bigmsgitem));
		strins(bigmsgitem, "\nтам выберите самый последний пункт(Обучение) и просмотрите пункт номер 10", strlen(bigmsgitem));
		strins(bigmsgitem, "\n8) Зайдя в игру вы не увидите Ников персонажей.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЧтобы он появился игрок должен с вами поздороваться(Выбрать ник в TAB,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nнажать 2 раза на нём, выбрать пункт Поздороваться).", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЧтобы подробнее узнать про систему знакомств введите [/help],", strlen(bigmsgitem));
		strins(bigmsgitem, "\nтам выберите самый последний пункт(Обучение) и просмотрите пункт номер 11", strlen(bigmsgitem));
	}
    else if(AboutTimeCounter[playerid] == 5)
    {
		strmid(caption, "5/11. Первые шаги:", 0, 65, 65);
		strins(bigmsgitem, "\nНа сервере имеется обучающая программа, которая поможет вам на начальных этапах игры.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nВ процессе её прохождения вам будет выдано около $25000, 3 lvl,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nПрава категории B(На авто транспорт), 14 чков уважения. Для активации нажмите F6,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nвведите '/' (косой слэш) и команду tut. Должно получиться : [/tut] И нажмите Enter", strlen(bigmsgitem));
		strins(bigmsgitem, "\nОднако,если вы не хотите проходить обучение, то съездите и сдайте на права в АвтоШколе(/gps 1013).", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЗайдя в здание вы увидите красный маркер. Станьте на него.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nНА НАШЕМ СЕРВЕРЕ МОЖНО ЕЗДИТЬ НА АВТО БЕЗ ЛИЦЕНЗИИ НА АВТОТРАНСПОРТ!", strlen(bigmsgitem));
		strins(bigmsgitem, "\nОднако, если вас остановят сотрудники ДПС, то они могут выдать штраф или посадить в КПЗ.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nПосле сдачи экзамена на получение прав съездите в Мэрию(/gps 1014)", strlen(bigmsgitem));
		strins(bigmsgitem, "\nи устройтесь на работу(станьте на красный маркер у стойки). Там выберите любую работу,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nкоторая вам по душе. После трудоустройства введите [/jobmanual] и внимательно прочтите его.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nТам расскажется об основах профессии. Потом съездите в АвтоСалон(/gps 1015)", strlen(bigmsgitem));
		strins(bigmsgitem, "\nи купите служебную машину(ID машины узнаете в /jobmanual).", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЕсли же вам не хватило денег на трудоустройство, то не отчаивайтесь.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nНа сервере есть масса подработок, на которые НЕ НУЖНО устраиваться в Мэрии:", strlen(bigmsgitem));
		strins(bigmsgitem, "\nГрузчиком(/gps 1046), Шахтёром(/gps 1049), Лесорубом(/gps 1050), Пожарником(/gps 1051).", strlen(bigmsgitem));
		strins(bigmsgitem, "\nНа них вы сможете подзаработать немного денег для покупки служебного авто.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЕсли возникнут вопросы, то задавайте их в [/question]", strlen(bigmsgitem));
	}
    else if(AboutTimeCounter[playerid] == 6)
    {
		strmid(caption, "6/11. Общение:", 0, 65, 65);
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
    else if(AboutTimeCounter[playerid] == 7)
    {
		strmid(caption, "7/11. Транспорт:", 0, 65, 65);
		strins(bigmsgitem, "Иметь транспорт жизненно необходимо для комфортной игры.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nОдин игрок может владеть тремя единицами транспорта при наличии дома или бизнеса.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nПриобрести новую машину можно у автодилеров в автосалоне Сан-Фиерро или подержанную в паркинге Лас-Вентураса.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЦена продажи авто у автодилера установлена в размере 100-150% от стоимости авто.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nКоманда /carinfo содержит данные о всём серверном транспорте и его цене.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nПеред тем, как покупать машину - узнайте её цену в /carinfo, чтобы не быть обманутым автодилером.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nДля того, чтобы управлять техникой, НЕ нужны лицензии.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nНо если вы не хотите лишний раз платить штраф, то Вам необходимо посетить АвтоШколу в Сан-Фиерро", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЛицензия на автомобили доступна с 1 уровня, лицензия на лодки и пилотирование самолётов и", strlen(bigmsgitem));
		strins(bigmsgitem, "\nвертолётов - со 2 уровня, лицензия на мотоцикл - с 10 уровня. Приобретя машину, купите замок для неё в магазине 24/7.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nМашина при работе двигателя расходует бензин. Не забывайте заправляться на многочисленных заправках по всему штату.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nМашину можно запарковать командой /parking или клавишей num4.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nПока вы её не распаркуете (/unparking или клавишей num6), с ней ничего не случится.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nСтоимость за парковку теперь зависит от лвла,т.е. на 1 лвле цена 100$ на 45 - 4500$(+100$ за каждый лвл).", strlen(bigmsgitem));
		strins(bigmsgitem, "\nКомандой /lock(Alt+Space) можно открыть/закрыть двери.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nКомандой (/engine) завести двигатель. Или используйте автоменю клавишей (2)", strlen(bigmsgitem));
		strins(bigmsgitem, "\nОпасайтесь автоугонщиков. Не распарковывайте машину, если рядом стоит посторонний.", strlen(bigmsgitem));
	}
    else if(AboutTimeCounter[playerid] == 8)
    {
		strmid(caption, "8/11. Государственная система:", 0, 65, 65);
		strins(bigmsgitem, "\nГлавным человеком в штате является Губернатор. Он формирует своё правительство,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nкоторое следит за соблюдением гос.структур правил, выдают Зарплату, Соц.помощь.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЕсли вы совершили ДТП, то вас будут искать сотрудники ДПС, если преступление,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nповлекшее приченение вреда - агенты FBI.  День и ночь штат охраняет Армия.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЕсли вы заболеете, то сотрудники МЧС придут к вам на помощь.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nСотрудники Мин.Образования помогут вам в получении различного рода лицензий.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nНу а репортёры SAN проводят различные развлекательные программы.", strlen(bigmsgitem));
	}
    else if(AboutTimeCounter[playerid] == 9)
    {
		strmid(caption, "9/11. Жильё:", 0, 65, 65);
		strins(bigmsgitem, "\nЖилье - самый необходимый атрибут игры на сервере!", strlen(bigmsgitem));
		strins(bigmsgitem, "\nВ нем ты можете спрятаться от бандитов/копов либо от плохой погоды, чтобы не заболеть.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nBот что ты можешь в нем делать: ты можешь пополнить свое здоровье [/heal]", strlen(bigmsgitem));
		strins(bigmsgitem, "\nили забрать оружие из шкафчика [/givegun], смотреть TV [/tv] или просто переодеться в раздевалке.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nТак же если ты имеешь личный автомобиль то выйдя из дома", strlen(bigmsgitem));
		strins(bigmsgitem, "\nи использовав [/service]>>буксировка авто телепортировать его к дому.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nНа начальных стадиях игры будет очень трудно да и дорого купить дом,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nтак что будет проще найти где подешевле стоит аренда за комнату и заселиться туда [/rentroom].", strlen(bigmsgitem));
		strins(bigmsgitem, "\nНо через несколько игровых лет ты под собирав денжат  решишься купить свой собственный дом.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nДля этого тебе нужно будет найти свободный дом или дом своей мечты и купить его [/buy].", strlen(bigmsgitem));
		strins(bigmsgitem, "\nБез дома ты всегда будете появляться в мотеле Los Santos. Если ты имеешь дом,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nто ты сможешь выбирать, где тебе появиться при входе в игру(По месту выхода,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nВ доме, По месту работы).", strlen(bigmsgitem));
	}
    else if(AboutTimeCounter[playerid] == 10)
    {
		strmid(caption, "10/11. Бизнес и АЗС:", 0, 65, 65);
		strins(bigmsgitem, "\nБизнес и АЗС - это предприятия в центрах городов либо на оживленных дорогах.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nСвободный бизнес/АЗС можно увидеть в статистике, выбрав пункт Поиск --> Бизнеса или Компании.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nПодробности о своем бизнесе или АЗС вы можете посмотреть, введя [/prop]", strlen(bigmsgitem));
		strins(bigmsgitem, "\nи выбрав интересующий вас бизнес. [/bizinfo] дает возможность просмотреть  Кассу,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nПродукты, Товары и что нужно для поднятия следующего уровня бизнеса, чтобы они не обанкротились.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nДля этого нужно пополнять кассу и завозить продукты, необходимые для него.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nДля завоза сырья в бизнес нужно выставить процент закупки, он может колебаться от 40% до 49%.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЧем выше процент закупки, тем больше вероятность, что сырьё завезут именно в ваш бизнес.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nПосле того, как сырьё переработается в товар, его необходимо вывести на Склад,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nчтобы получить прибыль. Чтобы привлечь дальнобойщиков к вашему бизнесу,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nдостаточно поставить высокую премию за вывоз товара. Премию нужно выставлять так,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nчтобы не быть в убытке самому. Но если вы боитесь покупать бизнес из-за незнания как управлять им,", strlen(bigmsgitem));
		strins(bigmsgitem, "\nто ты можете спросить у более опытного бизнесмена либо у хелперов [/question], ибо в Википедии сервера", strlen(bigmsgitem));
		strins(bigmsgitem, "\nНо помните: на каждый хороший бизнес есть и конкурент, который будет пытаться насолить и обанкротить его.", strlen(bigmsgitem));

	}
    else if(AboutTimeCounter[playerid] == 11)
    {
		strmid(caption, "11/11. Банки, хранение средств:", 0, 65, 65);
		strins(bigmsgitem, "Официальной валютой считается доллар. Деньги - основной ресурс этого мира. Деньгами вы будете расплачиваться за еду", strlen(bigmsgitem));
		strins(bigmsgitem, "\nи услуги медиков и механиков; за деньги можно приобрести автомобиль, дом, бизнес или воспользоваться услугами.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nЗаработать деньги можно, устроившись на одну из работ в Мэрии либо попав во фракцию или банду. Кроме того, время", strlen(bigmsgitem));
		strins(bigmsgitem, "\nот времени Правительство выдаёт социальные пакеты нуждающимся гражданам в Мэрии. Следите за объявлениями.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nВ штате действует государственный банк. Поэтому вверху справа будут отображаться два счётчика денег: нижний - сумма", strlen(bigmsgitem));
		strins(bigmsgitem, "\nу вас в кармане, верхний - сумма, лежащая на счету в банке. Наличность можно передать другому игроку командой", strlen(bigmsgitem));
		strins(bigmsgitem, "\n/pay id сумма. Максимальный размер передаваемой суммы - 1.000.000 долларов на 3 уровне. Добравшись до банка и зайдя", strlen(bigmsgitem));
		strins(bigmsgitem, "\nна красный маркер, вы получите возможность полностью распоряжаться своими деньгами: передавать их на счёт другому", strlen(bigmsgitem));
		strins(bigmsgitem, "\nигроку, класть их на депозит и получать проценты. Словом, грамотный подход даст возможность отлично заработать.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nВ штате находится много банкоматов в самых людных местах. В них вы сможете снять деньги с карточки на руки.", strlen(bigmsgitem));
		strins(bigmsgitem, "\nПодойдите к банкомату и нажмите Левый Alt.", strlen(bigmsgitem));
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
	ShowPlayerDialogEx(playerid, ABOUT_DIALOG, DIALOG_STYLE_MSGBOX, caption, bigmsgitem, "Назад", "Далее");//RegistrationSTEP5
	return 1;
}

/*
Координаты где поставить маркеры. И на каждом маркере должно быть написано Помощь по игре

1181.1794,-1332.7791,13.5804,267.5658 ; ЦБ ЛС
1470.6993,-1750.2477,15.4453,2.1933 ; Мэрия ЛС
2227.7502,-1143.9991,25.7969,339.3198 ; Мотель
-2039.2751,-79.0532,35.3203,353.4199 ; АШ
-2428.3660,332.3707,36.9969,243.7523 ; Мэрия СФ
-2661.6218,639.6078,14.4531,179.2284 ; ЦБ СФ
1611.5840,1817.9027,10.8203,3.7600 ; ЦБ ЛВ
-1641.4799,1207.9347,7.1797,305.8162 ; АвтоСалон
2742.8965,-2415.3386,13.6363,73.3673 ; Доки
*/


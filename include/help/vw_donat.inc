stock donat_OnPlayerPickUp(playerid, pickupid)
{
	if(pickupid == PickupID[16] &&
		IsPlayerInRangeOfPoint(playerid, 2.1, Pickups[pickupid][p_x],Pickups[pickupid][p_y],Pickups[pickupid][p_z]) )
	{
		//if( !strcmp(php_host, "vw-rp.net", true) )
		Donat(playerid);
		//return 1;
	}
}

stock Donat(playerid)
{
	DeletePVar(playerid, "GOLD"); PlayerInfo[playerid][pGold] = 0;
#if defined vw_sql//#endif
	new ToBase[57+24]; new Field[34];
	format(ToBase, sizeof(ToBase), "SELECT `Gold` FROM `players` WHERE `Name`='%s' AND `Gold`>0", PlayerName(playerid));

/*
	mysql_query(ToBase); mysql_store_result();
	if(mysql_num_rows() > 0 && mysql_retrieve_row())
	{
		mysql_fetch_field_row(Field, "Gold"); PlayerInfo[playerid][pGold] = floatstr(Field);//strval(Field);
	}
	else { PlayerInfo[playerid][pGold] = 0; SendClientMessage(playerid, COLOR_GREY, "   У вас нету золота на счету !"); }
	mysql_free_result();
*/
	new DBResult:db_result = db_query(db_VW, ToBase);
	if(db_num_rows(db_result))
	{
		db_get_field_assoc(db_result, "Gold", Field, sizeof(Field) ); PlayerInfo[playerid][pGold] = floatstr(Field);//strval(Field);
	}
	else { PlayerInfo[playerid][pGold] = 0; SendClientMessage(playerid, COLOR_GREY, "   У вас нету золота на счету !"); }
	db_free_result(db_result);

#endif
	new listitems[1035];
	strcat(listitems, "{FFFFFF}1\t{00FF00}Как пополнить.\n");//0
	strcat(listitems, "{FFFFFF}2\t{00FF00}Покупка игровой валюты. Курс: 1 золотой = 1200$\n");//1
	strcat(listitems, "{FFFFFF}3\t{00FF00}Снятие варна (предупреждения). Стоимость: 50 золотых\n");
	strcat(listitems, "{FFFFFF}4\t{00FF00}Очистить розыск. Стоимость: 50 золотых\n");
	strcat(listitems, "{FFFFFF}5\t{00FF00}Очистить список преступлений. Стоимость: 50 золотых\n");
	strcat(listitems, "{FFFFFF}6\t{00FF00}Покупка VIP статуса. Стоимость услуги на 30 дней: 300 золотых\n");
	//strcat(listitems, "{FFFFFF}\n7\t{00FF00}Дополнительная машина = 80 рублей");
	/*strcat(listitems, "{FFFFFF}\n8\t{00FF00}Покупка скили оружия");
	strcat(listitems, "{FFFFFF}\n9\t{00FF00}помощь по кланам");
	strcat(listitems, "{FFFFFF}\n10\t{00FF00}помощь по рыбалке");
	strcat(listitems, "{FFFFFF}\n11\t{00FF00}помощь по кухне");
	strcat(listitems, "{FFFFFF}\n12\t{00FF00}помощь по вступлению в брак");
	strcat(listitems, "{FFFFFF}\n13\t{00FF00}помощь по IRC-чату");
	strcat(listitems, "{FFFFFF}\n14\t{00FF00}преимущества премиум аккаунта");
	strcat(listitems, "{FFFFFF}\n15\t{00FF00}общее обучение");//13*/
	//strcat(listitems, "{FFFFFF}4\t{00FF00}Разбан на сервере. Стоимость разбана: 100 рублей\n");
	new caption[70];
	format(caption, sizeof(caption), "*** ДОНАТ *** Доступно %.1f золотых", PlayerInfo[playerid][pGold]);

	if(strlen(listitems) > sizeof(listitems))
	{
		PlayerInfo[playerid][pGold] = 0;
		//ИНФОРМИРОВАНИЕ
		format(strings, sizeof(strings), "Error: *** ДОНАТ *** %s[%d], strlen(listitems): %d, sizeof(listitems): %d",
			PlayerName(playerid), playerid, strlen(listitems), sizeof(listitems));
		Log(ERROR, strings);
		return 1;
	}
	if(strlen(listitems) <= 0)
	{
		PlayerInfo[playerid][pGold] = 0;
		SendClientMessage(playerid, COLOR_GREY, "   ДОНАТ пуст");//COLOR_BLUEGREY
		return 1;
	}
	MenuOperation[playerid] = 0;
	ShowPlayerDialogEx(playerid, GOLD_DIALOG, DIALOG_STYLE_LIST, caption, listitems, "OK", "Cancel");
	return 1;
}

stock VIPHelp(playerid)
{
	DeletePVar(playerid, "GOLD"); PlayerInfo[playerid][pGold] = 0;
	
#if defined vw_sql//#endif
	new ToBase[57+24]; new Field[34];
	format(ToBase, sizeof(ToBase), "SELECT `Gold` FROM `players` WHERE `Name`='%s' AND `Gold`>0 LIMIT 1", PlayerName(playerid));
	/*mysql_query(ToBase); mysql_store_result();
	if(mysql_num_rows() > 0 && mysql_retrieve_row())
	{
		//mysql_fetch_field_row(Field, "Gold"); PlayerInfo[playerid][pGold] = strval(Field);
		mysql_fetch_field_row(Field, "Gold"); PlayerInfo[playerid][pGold] = floatstr(Field);
	}
	else { PlayerInfo[playerid][pGold] = 0; SendClientMessage(playerid, COLOR_GREY, "   У вас нету золота на счету !"); }
	mysql_free_result();*/
	
	new DBResult:db_result = db_query(db_VW, ToBase);
	if(db_num_rows(db_result))
	{
		db_get_field_assoc(db_result, "Gold", Field, sizeof(Field) ); PlayerInfo[playerid][pGold] = floatstr(Field);//strval(Field);
	}
	else { PlayerInfo[playerid][pGold] = 0; SendClientMessage(playerid, COLOR_GREY, "   У вас нету золота на счету !"); }
	db_free_result(db_result);
#endif

	new dlgitem[1484+113+10];
	strcat(dlgitem, "\n1. ни где информация о вашем аккаунте не отображается, кроме приветствия для Вас");
	strcat(dlgitem, "\n2. не болеет и соответственно не проходит мед. осмотр");
	strcat(dlgitem, "\n3. спаунится всегда с 100% здоровья");
	strcat(dlgitem, "\n4. может сразу уволиться с работы без отработки");
	strcat(dlgitem, "\n5. ни кто не может заказать ВИПа, а также он не виден в списке заказов");
	strcat(dlgitem, "\n6. бонус к зарплате в размере половины зарплаты");
	strcat(dlgitem, "\n7. +0.2% по вкладу, если владелец дома +0.4% по вкладу, если вы владелец биза +0.2% по вкладу, \nесли вы в браке +0.3% по вкладу");
	strcat(dlgitem, "\n8. не проходит проверку собственности, \nт.е. бизнес не может обанкротится и дом не может выставиться на аукцион");
	strcat(dlgitem, "\n9. сразу имеет стиль боя FIGHT_STYLE_KNEEHEAD (Колено)");
	strcat(dlgitem, "\n10. сразу имеет прокаченные все скилы оружия на максимум, \nно при этом скилы продолжают качаться");
	strcat(dlgitem, "\n11. дает возможности выключать/включать телефон (/togphone)");
	strcat(dlgitem, "\n12. дает возможность смотреть список администраторов(онлайн) (/admins).");
	strcat(dlgitem, "\n13. дает возможности увольняться из организации");
	//strcat(dlgitem, "\n14. Снятие ban'a/warn'a производится автоматически после получения VIP");
	strcat(dlgitem, "\n15. Ваш телефонный разговор и СМС больше не возможно прослушать");
	//strcat(dlgitem, "\n16. доступна команда /changeorigin");
	strcat(dlgitem, "\n16. доступна команда /showtag");
	strcat(dlgitem, "\n17. из-за большого кол-ва нарушений и судимостей не выкидывает из фракции");
	strcat(dlgitem, "\n18. из-за низкого онлайна не выкидывает из фракции");
	strcat(dlgitem, "\n19. в некоторых проверках не кикает");
	strcat(dlgitem, "\n20. ни в чём не нуждается, т.е. параметры потребностей не идут");
	//strcat(dlgitem, "\n21. не требуется разрешение на покупку недвижимости");
	strcat(dlgitem, "\n21. не сдувает с крыши авто");
	strcat(dlgitem, "\n22. можно парковать тачку в любом месте");

	format(dlgitem, sizeof(dlgitem), "%s\n\nСтоимость услуги на 30 дней: 300 золотых.\
\nДоступно %.1f золотых.\
\nВы согласны купить VIP статус на 30 дней?", dlgitem, PlayerInfo[playerid][pGold]);
	MenuOperation[playerid] = 5;
	new caption[] = "Покупка VIP статуса";
	ShowPlayerDialogEx(playerid, GOLD_DIALOG, DIALOG_STYLE_MSGBOX, caption, dlgitem, "Да", "Нет");
}

stock donat_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if(dialogid != GOLD_DIALOG) return 1;
	if(!response) { DeletePVar(playerid, "GOLD"); PlayerInfo[playerid][pGold] = 0; MenuOperation[playerid] = 0; return 1; }
	if(MenuOperation[playerid] == 0)
	{
		new dlgitem[969];//64+58+36+45+56+44+37+44+42+37+66+37+47+86+51+91 + 64+64 = 969
		if(listitem == 0)
		{
			strcat(dlgitem, "Чтобы пополнить количество золотых у вас на счету необходимо:.\n");
			new weburl[64];
			GetServerVarAsString("weburl", weburl, sizeof(weburl));
			format(dlgitem, sizeof(dlgitem), "%s{FFFFFF}1\t{00FF00}Зайти по адресу http://%s/index.php?page=21\n", dlgitem, weburl);
			strcat(dlgitem, "{FFFFFF}2\t{00FF00}Выбрать сервер\n");
			strcat(dlgitem, "{FFFFFF}3\t{00FF00}Ввести Ваше игровое имя\n");
			strcat(dlgitem, "{FFFFFF}4\t{00FF00}Указать Сколько денег хотите положить на счёт\n");
			strcat(dlgitem, "{FFFFFF}5\t{00FF00}Нажать кнопку ОПЛАТИТЬ\nВас перекинет на сайт robokassa.ru\n");
			strcat(dlgitem, "{FFFFFF}6\t{00FF00}Выбрать способ оплаты\nВас перекинет на страницу Оплаты заказа\n");
			format(dlgitem, sizeof(dlgitem), "%sв магазине %s где будет указано \n", dlgitem, SERVERNAME);
			strcat(dlgitem, "Стоимость заказа, Заплатить до, Описание заказа, Итого к оплате\n");
			strcat(dlgitem, "{FFFFFF}7\t{00FF00}Ввести ваш Email(почтовый ящик)\n");
			strcat(dlgitem, "{FFFFFF}8\t{00FF00}Нажать 'Перейти к оплате'\nВас перекинет на страницу вашей системы оплаты, где надо просто подтвердить платёж.\n");
			strcat(dlgitem, "{FFFFFF}9\t{00FF00}В игре набрать команду /donat\n");
			strcat(dlgitem, "{FFFFFF}10\t{00FF00}и выбрать, согласно списка, на что вы хотитет потратить ваше золото.\n");
			new caption[70];
			format(caption, sizeof(caption), "*** ДОНАТ *** Доступно %.1f золотых", PlayerInfo[playerid][pGold]);
			MenuOperation[playerid] = 0;
			ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, caption, dlgitem, "OK", "");
		}
		else if(listitem == 1)
		{
			MenuOperation[playerid] = 1;
			new caption[] = "Покупка игровой валюты ($)";
			format(dlgitem, sizeof(dlgitem), "Курс: 1 золото = 1200$.\
\nДоступно %.1f золотых.\
\nВы можете купить $%d.\
\nСколько $ вы хотите купить?\
\n\n\t{8CAA63}По окончанию ввода нажмите OK.", PlayerInfo[playerid][pGold], floatround(PlayerInfo[playerid][pGold]*1200.0));
			ShowPlayerDialogEx(playerid, GOLD_DIALOG, DIALOG_STYLE_INPUT, caption, dlgitem, "OK", "Cancel");
		}
		else if(listitem == 2)
		{
			MenuOperation[playerid] = 2;
			new caption[] = "Снятие варна (предупреждения)";
			format(dlgitem, sizeof(dlgitem), "Стоимость снятия: 50 золотых \nДоступно %.1f золотых. \nВы согласны снять с вас варн?", PlayerInfo[playerid][pGold]);
			ShowPlayerDialogEx(playerid, GOLD_DIALOG, DIALOG_STYLE_MSGBOX, caption, dlgitem, "Да", "Нет");
		}
		else if(listitem == 3)
		{
			MenuOperation[playerid] = 3;
			new caption[] = "Очистить розыск. ";
			format(dlgitem, sizeof(dlgitem), "Стоимость: 50 золотых. \nДоступно %.1f золотых. \nВы согласны очистить розыск?", PlayerInfo[playerid][pGold]);
			ShowPlayerDialogEx(playerid, GOLD_DIALOG, DIALOG_STYLE_MSGBOX, caption, dlgitem, "Да", "Нет");
		}
		else if(listitem == 4)
		{
			MenuOperation[playerid] = 4;
			new caption[] = "Очистить список преступлений";
			format(dlgitem, sizeof(dlgitem), "Стоимость: 50 золотых. \nДоступно %.1f золотых. \nВы согласны очистить список преступлений?", PlayerInfo[playerid][pGold]);
			ShowPlayerDialogEx(playerid, GOLD_DIALOG, DIALOG_STYLE_MSGBOX, caption, dlgitem, "Да", "Нет");
		}
		else if(listitem == 5)
		{
			VIPHelp(playerid);
		}
	}
//==============================================================================
	else if(MenuOperation[playerid] == 1)
	{
	    if(!strlen(inputtext) || strlen(inputtext) > 10)
	    {
	    	DeletePVar(playerid, "GOLD"); PlayerInfo[playerid][pGold] = 0;
			SendClientMessage(playerid, COLOR_GREY, "   Вы не указали кол-во игровой валюты необходимой для покупки !");
			return 1;
	    }
	    if(strval(inputtext) < 0 || strval(inputtext) >= 2147483647)
	    {
	    	PlayerInfo[playerid][pGold] = 0;
			SendClientMessage(playerid, COLOR_GREY, "   Не допустимое значение !");
			return 1;
	    }
	    if(strval(inputtext) < 1200)
	    {
	    	DeletePVar(playerid, "GOLD"); PlayerInfo[playerid][pGold] = 0;
			SendClientMessage(playerid, COLOR_GREY, "   Минимальный заказ $1200 !");
			return 1;
	    }
	  	new Float: gold = strval(inputtext)/1200.0;
	    //if(PlayerInfo[playerid][pGold] > gold)
	    if(floatcmp(PlayerInfo[playerid][pGold], gold) < 0)
	    {
	    	DeletePVar(playerid, "GOLD"); PlayerInfo[playerid][pGold] = 0;
			SendClientMessage(playerid, COLOR_GREY, "   У вас нет столько золотых !");
			return 1;
	    }
		SetPVarFloat(playerid, "GOLD", gold);

		new dlgitem[135+35 + 24+3+10+64+10];
		format(dlgitem, sizeof(dlgitem), "%s[%d] оплачивает:\n\
Товар или услугу:\tПокупка игровой валюты.\n\
На сумму:\t\t$%d\n\
Продавцу:\t\t%s\n\
Оплата заказа:\t\t%.1f золотых\n\
\n\nНажмите Accept, чтобы принять.", PlayerName(playerid), playerid, strval(inputtext), HostName, gold);
		new caption[70];
		format(caption, sizeof(caption), "*** ДОНАТ *** Доступно %.1f золотых", PlayerInfo[playerid][pGold]);
		MenuOperation[playerid] = 11;
	 	ShowPlayerDialogEx(playerid, GOLD_DIALOG, DIALOG_STYLE_MSGBOX, caption, dlgitem, "Accept", "Cancel");
	}
	else if(MenuOperation[playerid] == 2)
	{
	    if(PlayerInfo[playerid][pWarns] <= 0)
	    {
	    	DeletePVar(playerid, "GOLD"); PlayerInfo[playerid][pGold] = 0;
			SendClientMessage(playerid, COLOR_GREY, "   У вас нет предупреждений !");
			return 1;
	    }
	    //if(PlayerInfo[playerid][pGold] < 50)
	    if(floatcmp(PlayerInfo[playerid][pGold], 50) <= 0)
	    {
	    	DeletePVar(playerid, "GOLD"); PlayerInfo[playerid][pGold] = 0;
			SendClientMessage(playerid, COLOR_GREY, "   У вас нет столько золотых !");
			return 1;
	    }
#if defined vw_sql//#endif
		new ToBase[79+24+10];
		format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Gold`=`Gold`-%d WHERE `Name`='%s'", 50, PlayerName(playerid));// AND `Gold`>=%d
  		//mysql_query(ToBase);
		db_free_result(db_query(db_VW, ToBase));
#endif

		PlayerInfo[playerid][pGold] = floatsub(PlayerInfo[playerid][pGold],50.0);//PlayerInfo[playerid][pGold] -= 50;
		PlayerInfo[playerid][pWarns] --;
		
		format(strings, sizeof(strings), "DONAT %s[%d]: Warns: %d. %d золотых списано" ,
			PlayerName(playerid), playerid, PlayerInfo[playerid][pWarns], 50);
		Log(DONAT, strings);
		
		new dlgitem[135+24+3+10+64+10];
		format(dlgitem, sizeof(dlgitem), "%s[%d]\n\
Спасибо, что воспользовались нашим магазином.\n\
Варн снят. Оставшееся количество варнов: %d\n\
С вашего золотого счёта списано: %d золотых\n", PlayerName(playerid), playerid, PlayerInfo[playerid][pWarns], 50);
		new caption[70];
		format(caption, sizeof(caption), "*** ДОНАТ *** Доступно %.1f золотых", PlayerInfo[playerid][pGold]);
		DeletePVar(playerid, "GOLD"); PlayerInfo[playerid][pGold] = 0; MenuOperation[playerid] = 0;
	 	ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, caption, dlgitem, "OK", "");

	}
	else if(MenuOperation[playerid] == 3)
	{
	    if(WantedPoints[playerid] <= 0)
	    {
	    	DeletePVar(playerid, "GOLD"); PlayerInfo[playerid][pGold] = 0;
			SendClientMessage(playerid, COLOR_GREY, "   У вас нет розыска !");
			return 1;
	    }
	    //if(PlayerInfo[playerid][pGold] < 50)
	    if(floatcmp(PlayerInfo[playerid][pGold], 50) <= 0)
	    {
	    	DeletePVar(playerid, "GOLD"); PlayerInfo[playerid][pGold] = 0;
			SendClientMessage(playerid, COLOR_GREY, "   У вас нет столько золотых !");
			return 1;
	    }
#if defined vw_sql//#endif
		new ToBase[79+24+10];
		format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Gold`=`Gold`-%d WHERE `Name`='%s'", 50, PlayerName(playerid));// AND `Gold`>=%d
		//mysql_query(ToBase);
		db_free_result(db_query(db_VW, ToBase));
#endif


		PlayerInfo[playerid][pGold] = floatsub(PlayerInfo[playerid][pGold],50.0);//PlayerInfo[playerid][pGold] -= 50;
		ClearCrime(playerid, playerid, 0);
		
		format(strings, sizeof(strings), "DONAT %s[%d]: ClearCrime. %d золотых списано" ,
			PlayerName(playerid), playerid, 50);
		Log(DONAT, strings);

		new dlgitem[135+24+3+10+64+10];
		format(dlgitem, sizeof(dlgitem), "%s[%d]\n\
Спасибо, что воспользовались нашим магазином.\n\
Розыск очищен. Звёзды убраны.\n\
С вашего золотого счёта списано: %d золотых\n", PlayerName(playerid), playerid, 50);
		new caption[70];
		format(caption, sizeof(caption), "*** ДОНАТ *** Доступно %.1f золотых", PlayerInfo[playerid][pGold]);
		DeletePVar(playerid, "GOLD"); PlayerInfo[playerid][pGold] = 0; MenuOperation[playerid] = 0;
	 	ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, caption, dlgitem, "OK", "");
	}
	else if(MenuOperation[playerid] == 4)
	{
	    if(PlayerInfo[playerid][pCrimes] <= 0)
	    {
	    	DeletePVar(playerid, "GOLD"); PlayerInfo[playerid][pGold] = 0;
			SendClientMessage(playerid, COLOR_GREY, "   У вас нет преступлений !");
			return 1;
	    }
	    //if(PlayerInfo[playerid][pGold] < 50)
	    if(floatcmp(PlayerInfo[playerid][pGold], 50) <= 0)
	    {
	    	DeletePVar(playerid, "GOLD"); PlayerInfo[playerid][pGold] = 0;
			SendClientMessage(playerid, COLOR_GREY, "   У вас нет столько золотых !");
			return 1;
	    }
#if defined vw_sql//#endif
		new ToBase[79+24+10];
		format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Gold`=`Gold`-%d WHERE `Name`='%s'", 50, PlayerName(playerid));// AND `Gold`>=%d
		//mysql_query(ToBase);
		db_free_result(db_query(db_VW, ToBase));
		
		format(ToBase, sizeof(ToBase), "DELETE FROM `criminallist` WHERE `Player` = '%s'", PlayerName(playerid));
		//mysql_query(ToBase);
		db_free_result(db_query(db_VW, ToBase));
#endif
		//PlayerInfo[playerid][pGold] -= 50;
		PlayerInfo[playerid][pGold] = floatsub(PlayerInfo[playerid][pGold],50.0);
		PlayerInfo[playerid][pCrimes] = 0;

		format(strings, sizeof(strings), "DONAT %s[%d]: DELETE FROM `criminallist. %d золотых списано" ,
			PlayerName(playerid), playerid, 50);
		Log(DONAT, strings);

		new dlgitem[135+24+3+10+64+10];
		format(dlgitem, sizeof(dlgitem), "%s[%d]\n\
Спасибо, что воспользовались нашим магазином.\n\
Список преступлений очищен.\n\
С вашего золотого счёта списано: %d золотых\n", PlayerName(playerid), playerid, 50);
		new caption[70];
		format(caption, sizeof(caption), "*** ДОНАТ *** Доступно %.1f золотых", PlayerInfo[playerid][pGold]);
		DeletePVar(playerid, "GOLD"); PlayerInfo[playerid][pGold] = 0; MenuOperation[playerid] = 0;
	 	ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, caption, dlgitem, "OK", "");
	}
	else if(MenuOperation[playerid] == 5)
	{
/*Examples:
floatcmp(2.0, 2.0) ->  0
floatcmp(1.0, 2.0) -> -1
floatcmp(2.0, 1.0) ->  1*/
	    //if(PlayerInfo[playerid][pGold] < 300)
	   	if(floatcmp(PlayerInfo[playerid][pGold], 300) <= 0)
	    {//если золотых <= 300
	    	DeletePVar(playerid, "GOLD"); PlayerInfo[playerid][pGold] = 0;
			SendClientMessage(playerid, COLOR_GREY, "   У вас нет столько золотых !");
			return 1;
	    }
#if defined vw_sql//#endif
		new ToBase[79+24+10];
		format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Gold`=`Gold`-%d WHERE `Name`='%s'", 300, PlayerName(playerid));// AND `Gold`>=%d
		//mysql_query(ToBase);
		db_free_result(db_query(db_VW, ToBase));
#endif
		//PlayerInfo[playerid][pGold] -= 300.0;
		PlayerInfo[playerid][pGold] = floatsub(PlayerInfo[playerid][pGold],300.0);
		if(PlayerInfo[playerid][pAccount] < getdate())
		{
			PlayerInfo[playerid][pAccount] = (getdate() + 30);
		}
		else PlayerInfo[playerid][pAccount] += 30;

		PlayerInfo[playerid][pSTD] = IsNotBeenIll;

		format(strings, sizeof(strings), "DONAT %s[%d]: Премиум Аккаунт до %s. %d золотых списано" ,
			PlayerName(playerid), playerid, getDate(PlayerInfo[playerid][pAccount]), 300);
		Log(DONAT, strings);
		
		new dlgitem[164 + 24+3 +32+10];
		format(dlgitem, sizeof(dlgitem), "%s[%d]\n\
Спасибо, что воспользовались нашим магазином.\n\
Вы имеете Премиум Аккаунт до %s, с чем Вас и Поздравляю.\n\
С вашего золотого счёта списано: %d золотых\n", PlayerName(playerid), playerid, getDate(PlayerInfo[playerid][pAccount]), 300);
		new caption[70];
		format(caption, sizeof(caption), "*** ДОНАТ *** Доступно %.1f золотых", PlayerInfo[playerid][pGold]);
		DeletePVar(playerid, "GOLD"); PlayerInfo[playerid][pGold] = 0; MenuOperation[playerid] = 0;
	 	ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, caption, dlgitem, "OK", "");
	}
//==============================================================================
//UPDATE `players` SET `Gold`=`Gold`+%d WHERE `Name`='%s' LIMIT 1
	else if(MenuOperation[playerid] == 11)
	{
	    if(PlayerInfo[playerid][pGold] < GetPVarFloat(playerid, "GOLD"))
	    {
	    	DeletePVar(playerid, "GOLD"); PlayerInfo[playerid][pGold] = 0;
			SendClientMessage(playerid, COLOR_GREY, "   У вас нет столько золотых !");
			return 1;
	    }
	    

#if defined vw_sql//#endif
		new ToBase[83+24+10];
		//format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Gold`=`Gold`-%.1f WHERE `Name`='%s' AND `Gold`>=%.1f LIMIT 1",
		//	GetPVarFloat(playerid, "GOLD"), PlayerName(playerid), GetPVarFloat(playerid, "GOLD") );
		format(ToBase, sizeof(ToBase), "UPDATE `players` SET `Gold`=`Gold`-%.1f WHERE `Name`='%s'",
			GetPVarFloat(playerid, "GOLD"), PlayerName(playerid) );
		//mysql_query(ToBase);
		db_free_result(db_query(db_VW, ToBase));
#endif

		PlayerInfo[playerid][pGold] = floatsub(PlayerInfo[playerid][pGold], GetPVarFloat(playerid, "GOLD"));
		//PlayerInfo[playerid][pBank] = PlayerInfo[playerid][pBank] + floatround( GetPVarFloat(playerid, "GOLD")*1200.0 );
		GivePlayerMoneyB(fdonat, playerid, floatround( GetPVarFloat(playerid, "GOLD")*1200.0 ));

		new dlgitem[135+24+3+10+64+10];
		format(dlgitem, sizeof(dlgitem), "%s[%d]\n\
Спасибо, что воспользовались нашим магазином.\n\
$%d поступило к вам на банковский счёт.\n\
С вашего золотого счёта списано: %.1f золотых\n",
			PlayerName(playerid), playerid, floatround( GetPVarFloat(playerid, "GOLD")*1200.0 ), GetPVarFloat(playerid, "GOLD") );

		format(strings, sizeof(strings), "DONAT %s[%d]: $%d поступило. %.1f золотых списано" ,
			PlayerName(playerid), playerid, floatround( GetPVarFloat(playerid, "GOLD")*1200.0 ), GetPVarFloat(playerid, "GOLD"));
		Log(DONAT, strings);

		new caption[70];
		format(caption, sizeof(caption), "*** ДОНАТ *** Доступно %.1f золотых", PlayerInfo[playerid][pGold]);
		DeletePVar(playerid, "GOLD"); PlayerInfo[playerid][pGold] = 0; MenuOperation[playerid] = 0;
	 	ShowPlayerDialogEx(playerid, DIALOG100, DIALOG_STYLE_MSGBOX, caption, dlgitem, "OK", "");

	}
	return 1;
}

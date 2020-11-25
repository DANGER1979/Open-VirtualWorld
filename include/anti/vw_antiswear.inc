//дл€ антимата
#define MAX_SWEARS 200 //максимальное кол-во матных слов, при увеличении - увеличить
#define length_swear_word 16 //длина матного слова
new Swears[MAX_SWEARS][length_swear_word];//массив дл€ хранени€ матных слов в игре
new WordsCounter = 0;//счЄтчик кол-ва матных слов в базе
new BreachCounter[MAX_PLAYERS];//счЄтчик нарушений

stock antiswear_OnGameModeInit()
{
	//дл€ антимата
	new	LSW[length_swear_word], File:file;
	if((file = fopen("Logs/antiswear.cfg",io_read)))
	{
		while(fread(file,LSW))
		{//„тение фала до тех пор пока в нем есть строки:
			for(new i=0, j=strlen(LSW); i<j; i++)
			{
				if(LSW[i] == '\n' || LSW[i] == '\r') LSW[i] = '\0';//\0 - заканчивает строку
			}
			Swears[WordsCounter] = LSW;//записываем в массив все матные слова из файла
			WordsCounter ++;
		}
		fclose(file);
	}
}

stock antiswear_OnPlayerConnect(playerid)
{
	BreachCounter[playerid] = 0;//дл€ антимата счЄтчик нарушений
}

stock AntiSweer(playerid, const message[])
{
/*
	new index;
	new length = strlen(strings);//Ёта функци€ может быть использована дл€ проверки длины указанной строки после пробела.
	while ((index < length) && (strings[index] <= ' '))
	{
		index ++;//Ќомер позиции пробела
	}
	new offset = index;//записываем позицию пробела в полученной строке
	new result[MAX_STRING];
	while ((index < length) && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = strings[index];//в переменную result записать символы с позиции после пробела
		index ++;
	}
	result[index - offset] = EOS;//обнулили данные в строке result начина€ с позиции последнего записанного символа
*/
	//------------------------------------------------------------------
	new result[MAX_STRING];
	strmid(result, message, 0, strlen(message), MAX_STRING);//лидер банды
	if(ANTISWEER == 1)//дл€ антимата начало
	{   //если антимат активирован
		new SweerFound = 0;
		for(new s=0; s<WordsCounter; s++)
    	{   //сканируем все матные слова в базе
			new pos;
			if( ( pos = strfind(result, Swears[s], true) ) != -1)//если матное слово найдено
			//поиска подстроки в строке. -1 - если не найдено
			//cmdtext - —трока, в которой будет производитьс€ поиск
			//Swears[s] - »скома€ строка
	    	{   //если слова набранное и слово в базе совпали
				for(new i=pos, j=pos+strlen(Swears[s]); i<j; i++)
				{   //все символы начина€ с первого символа матного слова до длины этого слова
		 	 		result[i] = '*';//замениваем на символ *
				}
				SweerFound = 1;
				BreachCounter[playerid] ++;//счЄтчик кол-ва раз написавших матных слов в общий чат
			}
		}
		if(BreachCounter[playerid] > 0 && SweerFound == 1)//наказание
		{
	 	 	SendClientMessage(playerid, COLOR_RED, "CEPBEP: {800000}«а мат ты несешь наказание (уменьшаетс€ счет в банке)!!!");
	        new tmpSwear = FLOODLIM - BreachCounter[playerid];
	       	//new strings[MAX_STRING];
	        format(strings, sizeof(strings), "CEPBEP: {800000}≈ще %d предупреждений и ¬ы не cможете говорить!", tmpSwear);
	 	 	SendClientMessage(playerid, COLOR_RED, strings);
	  		if(PlayerInfo[playerid][pBank] > 100*BreachCounter[playerid])
	  		{
			  	GivePlayerMoneyB(fadmin, playerid, -100*BreachCounter[playerid]);
			}
	  		else
	  		{
				GivePlayerMoneyH(fadmin, playerid, -100*BreachCounter[playerid]);
			}
			if(BizInfo[0][bTill]+100*BreachCounter[playerid] < 2147480000) { BizInfo[0][bTill] += 100*BreachCounter[playerid]; BizInfo[0][bExport] += 100*BreachCounter[playerid]; }
	        if(BreachCounter[playerid] >= FLOODLIM)
	        {

				PlayerInfo[playerid][pMuted] = getdate() + 3;
	        	SendClientMessage(playerid, COLOR_RED, "CEPBEP: {800000}¬ы не можете говорить! ¬ы заглушены на 3 дн€!");
				format(strings, sizeof(strings), "CEPBEP: %s был заглушен на 3 дн€. reason: ignore %d warnings in local chat", PlayerName(playerid), BreachCounter[playerid]);
		 		Log(CHAT,strings);
  				BreachCounter[playerid] = 0;
	        }
		}
	}//дл€ антимата конец'
	return result;
	//------------------------------------------------------------------
}

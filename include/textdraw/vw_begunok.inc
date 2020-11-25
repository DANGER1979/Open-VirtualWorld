//new offsettimer = -1;
new WriteIndex;// это номер символа с которого мы начинаем записывать в темп строчку
new RunString[128] = "Zdes mogla byt vasha reklama";//0xFF // это текст бегунка
//new PagerString[256+1] = "Движение по трассе открыто";

/*stock PagerOffset(playerid, txdX, txdYOffset, txdSize, movetime) // Создает бегунок, параметры описаны в примечаниях
{
	new pattern[256+1]; //0xFF эта строка заполняется пробелами, чтобы создать текстдрав определенной длины (в символах)
	WriteIndex = (-1)*txdSize; //устанавливаем индекс так, чтобы строка уехала влево полностью, т.е. на 'c' символов назад
	for(new i=0; i<txdSize; i++) { pattern[i] = ' '; }// заполняем так называемый шаблон для текстдрава (он по идее не обязателен)
	pattern[txdSize] = 0; // завершаем строку

	if(TextDrawShowBegunok == false)
	{
		//for(new l; l < sizeof(RunString)-1; l++) RunString[l] = " ";//очистить от предыдущего
		txdPager[playerid] = TextDrawCreateEx(445.0, 433.0, pattern);//150.0, 2.1, //Создать новый Text Draw в памяти сервера  с нашим шаблоном.
		PlayerTextDrawUseBox(playerid, txdPager[playerid], 0);//Определяет использование рамки. 1 - использовать, 0 - не использовать
		PlayerTextDrawFont(playerid, txdPager[playerid], 1);//Изменяет шрифт текста. (0-3)
		PlayerTextDrawLetterSize(playerid, txdPager[playerid], 0.30, 1.0);//Устанавливает ширину и высоту букв(рамки) в пикселях.
		PlayerTextDrawSetOutline(playerid, txdPager[playerid], 1);//Устанавливает размер обводки текста. 1 - Толщина обводки
		PlayerTextDrawBackgroundColor(playerid, txdPager[playerid], 0x000000FF);//Устанавливает цвет фона текста
		PlayerTextDrawBoxColor(playerid, txdPager[playerid], 0x0000ff11);//0x00FFFF66 Устанавливает цвет рамки
		PlayerTextDrawColor(playerid, txdPager[playerid], COLOR_BRIGHTLYGREEN);//COLOR_DARKTURQUOISE 0x000000FF COLOR_LIGHTTURQUOISE
		PlayerTextDrawTextSize(playerid, txdPager[playerid], 540.0, 0.0);//Устанавливает ширину и высоту рамки (при использовании рамки).

		TextDrawShowForAll(txdPager[playerid]);
		TextDrawShowBegunok = true;
	}
	KillTimer(gOffsettimer); gOffsettimer = -1;
	gOffsettimer = SetTimerEx("PagerTimer", movetime, 1, "ii", playerid, txdSize); //запускаем бесконечный таймер
	return gOffsettimer;
}
public PagerTimer(playerid, size)
{ // функция служит для определения направления
	BegunokOffsetLine(RunString, strlen(RunString), size, playerid); // запускаем функцию перемещающую символы
}*/

//для бегущей строки начало
stock BegunokOffset(txdX, txdYOffset, txdSize, movetime) // Создает бегунок, параметры описаны в примечаниях
{
	new pattern[255]; //0xFF эта строка заполняется пробелами, чтобы создать текстдрав определенной длины (в символах)
	WriteIndex = (-1)*txdSize; //устанавливаем индекс так, чтобы строка уехала влево полностью, т.е. на txdSize символов назад
	for(new i=0; i<txdSize; i++) { pattern[i] = ' '; }// заполняем так называемый шаблон для текстдрава (он по идее не обязателен)
//чтобы создать фон
	pattern[txdSize] = '\0';//0; // завершаем строку

	if(TextDrawShowBegunok == false)
	{
		//for(new l; l < sizeof(RunString)-1; l++) RunString[l] = " ";//очистить от предыдущего
		txdBegunok = TextDrawCreateEx(txdX*1.0, txdYOffset*1.0, pattern);//150.0, 2.1, //Создать новый Text Draw в памяти сервера  с нашим шаблоном.
		TextDrawUseBox(txdBegunok, 1);//Определяет использование рамки. 1 - использовать, 0 - не использовать
		TextDrawFont(txdBegunok, 1);//Изменяет шрифт текста. (0-3)
		TextDrawLetterSize(txdBegunok, 0.30, 1.0);//Устанавливает ширину и высоту букв(рамки) в пикселях.
		TextDrawSetOutline(txdBegunok, 1);//Устанавливает размер обводки текста. 1 - Толщина обводки
		TextDrawBackgroundColor(txdBegunok, 0x000000FF);//Устанавливает цвет фона текста
		TextDrawBoxColor(txdBegunok, 0x0000ff11);//0x00FFFF66 Устанавливает цвет рамки
		TextDrawColor(txdBegunok, COLOR_BRIGHTLYGREEN);//COLOR_DARKTURQUOISE 0x000000FF COLOR_LIGHTTURQUOISE
		TextDrawTextSize(txdBegunok, 540.0, 0.0);//Устанавливает ширину и высоту рамки (при использовании рамки).

		TextDrawShowForAll(txdBegunok);
		TextDrawShowBegunok = true;
	}
	KillTimer(gOffsettimer); gOffsettimer = -1;
	gOffsettimer = SetTimerEx("BegunokTimer", movetime, 1, "i", txdSize); //запускаем бесконечный таймер
	return gOffsettimer;
}
forward BegunokTimer(size);//для бегущей строки
public BegunokTimer(size)
{ // функция служит для определения направления
	BegunokOffsetLine(RunString, strlen(RunString), size); // запускаем функцию перемещающую символы
}
stock BegunokOffsetLine(const message[], length, size, mode=0)
{ // функция переставляет символы в RunString
	new buffer[0xFF];//256//0xFF сюда собираем строку, чтобы потом ее отобразить
	new i; // счетчик для for
	new pos = 0; // переменная для определения конца строки буфера относительно строки нашего бегунка 
//(концом будет index+size-1)
	for(i=0; i<size; i++)
	{
		pos = WriteIndex + i; // определяем текущий символ относительно index
		if( (pos > -1) && (pos < length) ) buffer[i] = message[pos]; 
// если мы находимся в пределах строки бегунка, тогда пишем i-ый символ в pos-ый
		else
		{//в противном случаи мы ставим пробелы, если до строки, и прекращаем цикл, если после
			if(pos >= length) break;
			else buffer[i] = ' ';//32
		}
	}
	if(buffer[size-1] == ' ') buffer[size-1] = '\0';//0; // если наш буфер оканчивается на пробел, то заменяем его 0,
	//если это не зделать, то текстдрав в этот момент будет исчезать с экрана
	else buffer[i] = '\0';//0; // если пробел не встречен, то просто делаем символ номер index+size нулевым, чтобы корректно закончить строку

//SendClientMessageToAll(-1, buffer);
	if(mode == 1)
	{
		//PlayerTextDrawSetStringEx(txdPager[i], buffer); // функция изменения содержимого текстдрава
	}
    else TextDrawSetStringEx(txdBegunok, RusToGame(buffer)); // функция изменения содержимого текстдрава
//printf("%s", buffer);

	if(WriteIndex >= strlen(RunString)-1) WriteIndex = (-1)*size;
	else WriteIndex ++;
	

}//для бегущей строки конец

stock begunok_OnPlayerSpawn(playerid)
{
	if(TextDrawShowBegunok == true)//для бегущей строки
	{
		TextDrawShowForPlayer(playerid, txdBegunok);
	}
}

stock begunok_STATE_WASTED(playerid)
{
	if(TextDrawShowBegunok == true)//для бегущей строки
	{
		TextDrawHideForPlayer(playerid, txdBegunok);
	}
}
/*
stock begunok_OnPlayerCommandText(playerid, cmdtext[])
{
	new strcmd[MAX_STRING];
	new cmd[20], idx, tmp[MAX_STRING], gMessage[MAX_STRING];
	//new giveplayerid;
	cmd = strtok(cmdtext, idx);
	if(!strcmp(cmd, "/stopline", true))
	{
		if(PlayerInfo[playerid][pMember] != SAN && PlayerInfo[playerid][pAdmin] != 9)
		{
		    return SendClientMessage(playerid, COLOR_GREY, "   Вы не репортёр новостей! !");
		}
		if(PlayerInfo[playerid][pRank] < 6 && PlayerInfo[playerid][pAdmin] != 9)
		{
		    return SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть 6 Ранга !");
		}
		if(gOffsettimer < 0)
		{
			return SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /startline [Size ~120] [Speed(ms) ~200] [Text]");
		}
		KillTimer(gOffsettimer); gOffsettimer = -1;
		if(TextDrawShowBegunok == true)
		{
			TextDrawShowBegunok = false;
			TextDrawHideForAll(txdBegunok);
			TextDrawDestroyEx(txdBegunok);
		}
		else SendClientMessage(playerid, COLOR_GREY, "   Бегущая строка не показана (USE: /startline)");
		return 1;
	}
	if(!strcmp(cmd, "/startline", true))
	{
		if(PlayerInfo[playerid][pMember] != SAN && PlayerInfo[playerid][pAdmin] != 9)
		{
		    return SendClientMessage(playerid, COLOR_GREY, "   Вы не ЛИДЕР Агенства Новостей !");
		}
		if(PlayerInfo[playerid][pMember] == SAN && PlayerInfo[playerid][pRank] < 6)
		{
		    return SendClientMessage(playerid, COLOR_GREY, "   Вы должны быть 6 Ранга !");
		}
		if(gOffsettimer >= 0)
		{
			return SendClientMessage(playerid, COLOR_GREY, "USE: /stopline, чтобы остановить бегущую строку");
		}
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /startline [Size ~120] [Speed(ms) ~200] [Text]");
			SendClientMessage(playerid, COLOR_GREY, "USE: /stopline, чтобы остановить");
			return 1;
		}
		if(strval(tmp) < 10 && strval(tmp) > 300)
		{
			return SendClientMessage(playerid, COLOR_GRAYWHITE,  "USE: /startline [Size ~120] [Speed(ms) ~200] [Text]");
		}
		new txdSize = strval(tmp);

   		format(strcmd, sizeof(strcmd), "txdSize: %d", txdSize);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);

		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			return SendClientMessage(playerid, COLOR_GRAYWHITE,  "USE: /startline [Size ~120] [Speed(ms) ~200] [Text]");
		}
		if(strval(tmp) < 100 && strval(tmp) > 1000)
		{
			return SendClientMessage(playerid, COLOR_GRAYWHITE,  "USE: /startline [Size ~120] [Speed(ms) ~200] [Text]");
		}
		new movetime = strval(tmp);
   		format(strcmd, sizeof(strcmd), "movetime: %d miliseconds", movetime);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);

		gMessage = strrest(cmdtext, idx);
		if(strlen(gMessage) > sizeof(RunString))
		{
			return SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /startline [Size ~120] [Speed(ms) ~200] [Text(256 char)]");
		}
		if(!strlen(gMessage))
		{
			strmid(gMessage, "Zdes mogla byt vasha reklama", 0, strlen(gMessage), 255);
			//return 1;
		}
		strmid(RunString, gMessage, 0, strlen(gMessage), 255);
		BegunokOffset(150, 410, txdSize, movetime);//BegunokOffset(150, 438, txdSize, movetime);

   		format(strcmd, sizeof(strcmd), "gMessage: %s", gMessage);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);	
		return 1;
	}
//для бегущей строки конец
	return 1;
}*/

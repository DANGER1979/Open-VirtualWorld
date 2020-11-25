//------------------------------------------------------------------------------
//для потребностей
new bool:gTextDrawShowScale[MAX_PLAYERS];
new bool:gTextDrawHideScale[MAX_PLAYERS];
new bool:TextDrawShowScale[MAX_PLAYERS];
//new textdrawtimer;
//forward TextDrawTimer();
new indicator1[MAX_PLAYERS];//Голод
new indicator2[MAX_PLAYERS];//Досуга
new indicator3[MAX_PLAYERS];//Общение
new indicator4[MAX_PLAYERS];//Туалет
new indicator5[MAX_PLAYERS];//Бодрость
new indicator6[MAX_PLAYERS];//для уважения
new indicator7[MAX_PLAYERS];//для оружия

new Text:txdStatistics;

new Text:txdProgressObv1,
	Text:txdProgressObv2,
	Text:txdProgressObv3,
	Text:txdProgressObv4,
	Text:txdProgressObv5;

new Text:txdProgress1,
	Text:txdProgress2,
	Text:txdProgress3,
	Text:txdProgress4,
	Text:txdProgress5;

new Text:txdRamka,
	Text:txdRespect,
	Text:txdSunday;

new PlayerText:txdProgressZap1[MAX_PLAYERS],
	PlayerText:txdProgressZap2[MAX_PLAYERS],
	PlayerText:txdProgressZap3[MAX_PLAYERS],
	PlayerText:txdProgressZap4[MAX_PLAYERS],
	PlayerText:txdProgressZap5[MAX_PLAYERS];

//new PlayerText:txdCHAT[MAX_PLAYERS];

//для потребностей
stock Progress_OnGameModeInit()
{

//основная рамка
   	txdRamka = TextDrawCreateEx(16.5, 225.0, "_");
	TextDrawUseBox(txdRamka, 1);//Определяет использование рамки. 1 - использовать, 0 - не использовать
	TextDrawBoxColor(txdRamka,0x00000088);//Устанавливает цвет рамки
	TextDrawTextSize(txdRamka,184.0,0.0);//Устанавливает ширину и высоту рамки (при использовании рамки).
	TextDrawAlignment(txdRamka,1);//Устанавливает смещение текста в Text Draw. ID смещения: 0 или 1 - влево, 2 - центр, 3 - вправо.
	TextDrawBackgroundColor(txdRamka,0x000000ff);//Устанавливает цвет фона теста
	TextDrawFont(txdRamka, 1);//Изменяет шрифт текста. (0-3) 0(Style 2)-закавырестый, 1- компактный 2-все большие 3-все маленькие
	TextDrawLetterSize(txdRamka, 0.0, 11.98);//Устанавливает ширину и высоту букв(рамки) в пикселях.
	TextDrawColor(txdRamka, 0xFFFFFFFF);//Устанавливает цвет текста
	TextDrawSetShadow(txdRamka, 1);//Устанавливает размер тени текста. 2 - Размер тени по умолчанию
	//--------------------------------------------------------------------------
	//обводка1
	txdProgressObv1 = TextDrawCreateEx(177.0, 244.0, "_");
	TextDrawUseBox(txdProgressObv1, 1);
	TextDrawBoxColor(txdProgressObv1, 0x00000077);
	TextDrawTextSize(txdProgressObv1, 103.0,0.0);
	TextDrawLetterSize(txdProgressObv1, 0.0, 0.8);
	//прогресбар1
	txdProgress1 = TextDrawCreateEx(175.0, 246.0, "_");
	TextDrawUseBox(txdProgress1, 1);
	TextDrawBoxColor(txdProgress1,0x60646033);
	TextDrawTextSize(txdProgress1,105.0,0.0);
	TextDrawLetterSize(txdProgress1, 0.0, 0.3);
	//--------------------------------------------------------------------------
	//обводка8
	txdProgressObv2 = TextDrawCreateEx(177.0, 260.0, "_");
	TextDrawUseBox(txdProgressObv2, 1);
	TextDrawBoxColor(txdProgressObv2, 0x00000077);
	TextDrawTextSize(txdProgressObv2, 103.0,0.0);
	TextDrawLetterSize(txdProgressObv2, 0.0, 0.8);
	//прогресбар2
	txdProgress2 = TextDrawCreateEx(175.0, 262.0, "_");
	TextDrawUseBox(txdProgress2, 1);
	TextDrawBoxColor(txdProgress2,0x60646033);
	TextDrawTextSize(txdProgress2,105.0,0.0);
	TextDrawLetterSize(txdProgress2, 0.0, 0.3);
	//--------------------------------------------------------------------------
	//обводка3
	txdProgressObv3 = TextDrawCreateEx(177.0, 276.0, "_");
	TextDrawUseBox(txdProgressObv3, 1);
	TextDrawBoxColor(txdProgressObv3, 0x00000077);
	TextDrawTextSize(txdProgressObv3, 103.0,0.0);
	TextDrawLetterSize(txdProgressObv3, 0.0, 0.8);
	//прогресбар3
	txdProgress3 = TextDrawCreateEx(175.0, 278.0, "_");
	TextDrawUseBox(txdProgress3, 1);
	TextDrawBoxColor(txdProgress3,0x60646033);
	TextDrawTextSize(txdProgress3,105.0,0.0);
	TextDrawLetterSize(txdProgress3, 0.0, 0.3);
	//--------------------------------------------------------------------------
	//обводка4
	txdProgressObv4 = TextDrawCreateEx(177.0, 292.0, "_");
	TextDrawUseBox(txdProgressObv4, 1);
	TextDrawBoxColor(txdProgressObv4, 0x00000077);
	TextDrawTextSize(txdProgressObv4, 103.0,0.0);
	TextDrawLetterSize(txdProgressObv4, 0.0, 0.8);

	//прогресбар4
	txdProgress4 = TextDrawCreateEx(175.0, 294.0, "_");
	TextDrawUseBox(txdProgress4, 1);
	TextDrawBoxColor(txdProgress4, 0x60646033);
	TextDrawTextSize(txdProgress4, 105.0,0.0);
	TextDrawLetterSize(txdProgress4, 0.0, 0.3);
	//--------------------------------------------------------------------------
	//обводка5
	txdProgressObv5 = TextDrawCreateEx(177.0, 307.0, "_");
	TextDrawUseBox(txdProgressObv5, 1);
	TextDrawBoxColor(txdProgressObv5, 0x00000077);
	TextDrawTextSize(txdProgressObv5, 103.0,0.0);
	TextDrawLetterSize(txdProgressObv5, 0.0, 0.8);
	//прогресбар5
	txdProgress5 = TextDrawCreateEx(175.0, 309.0, "_");
	TextDrawUseBox(txdProgress5, 1);
	TextDrawBoxColor(txdProgress5, 0x60646033);
	TextDrawTextSize(txdProgress5, 105.0,0.0);
	TextDrawLetterSize(txdProgress5, 0.0, 0.3);
	//--------------------------------------------------------------------------
	//заголовок самапальной менюшки
	txdStatistics = TextDrawCreate(25.000000, 207.000000, RusToGame("Сведения"));
	TextDrawLetterSize(txdStatistics, 1.000000, 2.799999);
	TextDrawAlignment(txdStatistics, 0);
	TextDrawColor(txdStatistics, 0xE0DCE0FF);
	TextDrawSetShadow(txdStatistics, 0);
	TextDrawSetOutline(txdStatistics, 2);
	TextDrawFont(txdStatistics, 0);
	TextDrawSetProportional(txdStatistics, 1);
	//--------------------------------------------------------------------------
	//название параметров самапальной менюшки

	txdRespect = TextDrawCreateEx(25.0, 238.0, RusToGame("Голод~n~Досуг~n~Общение~n~Туалет~n~Бодрость"));
	TextDrawLetterSize(txdRespect, 0.349999, 1.759999);
	TextDrawTextSize(txdRespect, 105.000000, 100.000000);
	TextDrawAlignment(txdRespect, 0);
	TextDrawColor(txdRespect, 0xE0DCE0FF);
	TextDrawSetShadow(txdRespect, 1);
	TextDrawSetOutline(txdRespect, 0);
	TextDrawFont(txdRespect, 1);
	TextDrawSetProportional(txdRespect, 1);
	//--------------------------------------------------------------------------
	//дополнительный сведения в самапальной менюшке
	txdSunday = TextDrawCreateEx(175.5, 317.0, RusToGame("по потребностям"));
	TextDrawAlignment(txdSunday,3);
	TextDrawFont(txdSunday,3);
	TextDrawLetterSize(txdSunday,0.47,1.35);
	TextDrawColor(txdSunday,0xC8C4C8FF);
	TextDrawSetOutline(txdSunday,1);
	TextDrawSetShadow(txdSunday,0);

}
//голод должен достигать максимума за 10 минут
//Досуг должен достигать максимума за 15 минут
//Общение должен достигать максимума за 20 минут
//Туалет должен достигать максимума за 30 минут
//Бодрость должен достигать максимума за 60 минут
//"Respect Stamina Bodybuilding Kilogramm Glamour"

stock Progress_OnGameModeExit()
{
	//основная рамка
   	TextDrawDestroyEx(txdRamka);
	//--------------------------------------------------------------------------
	//обводка1
	TextDrawDestroyEx(txdProgressObv1);
	//прогресбар1
	TextDrawDestroyEx(txdProgress1);
	//--------------------------------------------------------------------------
	//обводка8
	TextDrawDestroyEx(txdProgressObv2);
	//прогресбар2
	TextDrawDestroyEx(txdProgress2);
	//--------------------------------------------------------------------------
	//обводка3
	TextDrawDestroyEx(txdProgressObv3);
	//прогресбар3
	TextDrawDestroyEx(txdProgress3);
	//--------------------------------------------------------------------------
	//обводка4
	TextDrawDestroyEx(txdProgressObv4);
	//прогресбар4
	TextDrawDestroyEx(txdProgress4);
	//--------------------------------------------------------------------------
	//обводка5
	TextDrawDestroyEx(txdProgressObv5);
	//прогресбар5
	TextDrawDestroyEx(txdProgress5);
	//--------------------------------------------------------------------------
	TextDrawDestroyEx(txdStatistics);
	TextDrawDestroyEx(txdRespect);
	TextDrawDestroyEx(txdSunday);
}
	
stock Progress_OnPlayerConnect(playerid)
{

	txdProgressZap1[playerid] = CreatePlayerTextDrawEx(playerid, 106.000000, 242.100006, "llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll");
	PlayerTextDrawLetterSize(playerid, txdProgressZap1[playerid], 0.075000, 1.080000);
	PlayerTextDrawAlignment(playerid, txdProgressZap1[playerid], 1);
	PlayerTextDrawColor(playerid, txdProgressZap1[playerid], -1);
	PlayerTextDrawSetShadow(playerid, txdProgressZap1[playerid], 0);
	PlayerTextDrawSetOutline(playerid, txdProgressZap1[playerid], 0);
	PlayerTextDrawFont(playerid, txdProgressZap1[playerid], 1);
	PlayerTextDrawSetProportional(playerid, txdProgressZap1[playerid], 1);

	txdProgressZap2[playerid] = CreatePlayerTextDrawEx(playerid, 106.000000, 258.100006, "llllllllllllllllllllllllllllllllllllllllllllllllll");
	PlayerTextDrawLetterSize(playerid, txdProgressZap2[playerid], 0.150000, 1.080000);
	PlayerTextDrawAlignment(playerid, txdProgressZap2[playerid], 1);
	PlayerTextDrawColor(playerid, txdProgressZap2[playerid], -1);
	PlayerTextDrawSetShadow(playerid, txdProgressZap2[playerid], 0);
	PlayerTextDrawSetOutline(playerid, txdProgressZap2[playerid], 0);
	PlayerTextDrawFont(playerid, txdProgressZap2[playerid], 1);
	PlayerTextDrawSetProportional(playerid, txdProgressZap2[playerid], 1);

	txdProgressZap3[playerid] = CreatePlayerTextDrawEx(playerid, 106.000000, 274.100006, "llllllllllllllllllllllllllllll");
	PlayerTextDrawLetterSize(playerid, txdProgressZap3[playerid], 0.252000, 1.080000);
	PlayerTextDrawAlignment(playerid, txdProgressZap3[playerid], 1);
	PlayerTextDrawColor(playerid, txdProgressZap3[playerid], -1);
	PlayerTextDrawSetShadow(playerid, txdProgressZap3[playerid], 0);
	PlayerTextDrawSetOutline(playerid, txdProgressZap3[playerid], 0);
	PlayerTextDrawFont(playerid, txdProgressZap3[playerid], 1);
	PlayerTextDrawSetProportional(playerid, txdProgressZap3[playerid], 1);

	txdProgressZap4[playerid] = CreatePlayerTextDrawEx(playerid, 106.000000, 290.000000, "llllllllllllllllllll");
	PlayerTextDrawLetterSize(playerid, txdProgressZap4[playerid], 0.379999, 1.080000);
	PlayerTextDrawAlignment(playerid, txdProgressZap4[playerid], 1);
	PlayerTextDrawColor(playerid, txdProgressZap4[playerid], -1);
	PlayerTextDrawSetShadow(playerid, txdProgressZap4[playerid], 0);
	PlayerTextDrawSetOutline(playerid, txdProgressZap4[playerid], 0);
	PlayerTextDrawFont(playerid, txdProgressZap4[playerid], 1);
	PlayerTextDrawSetProportional(playerid, txdProgressZap4[playerid], 1);

	txdProgressZap5[playerid] = CreatePlayerTextDrawEx(playerid, 106.000000, 305.000000, "lllllllllllllll");
	PlayerTextDrawLetterSize(playerid, txdProgressZap5[playerid], 0.509999, 1.080000);
	PlayerTextDrawAlignment(playerid, txdProgressZap5[playerid], 1);
	PlayerTextDrawColor(playerid, txdProgressZap5[playerid], -1);
	PlayerTextDrawSetShadow(playerid, txdProgressZap5[playerid], 0);
	PlayerTextDrawSetOutline(playerid, txdProgressZap5[playerid], 0);
	PlayerTextDrawFont(playerid, txdProgressZap5[playerid], 1);
	PlayerTextDrawSetProportional(playerid, txdProgressZap5[playerid], 1);


/*
	txdCHAT[playerid] = CreatePlayerTextDrawEx(playerid, 590.000000, 110.000000, "LD_CHAT:badchat");
	PlayerTextDrawLetterSize(playerid, txdCHAT[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, txdCHAT[playerid], 24.000000, 24.000000);
	PlayerTextDrawAlignment(playerid, txdCHAT[playerid], 0);
	PlayerTextDrawColor(playerid, txdCHAT[playerid], -1);
	PlayerTextDrawSetShadow(playerid, txdCHAT[playerid], 0);
	PlayerTextDrawSetOutline(playerid, txdCHAT[playerid], 0);
	PlayerTextDrawFont(playerid, txdCHAT[playerid], 4);
	PlayerTextDrawSetProportional(playerid, txdCHAT[playerid], 1);
*/
}


stock Progress_OnPlayerDisconnect(playerid)
{

	if(TextDrawShowScale[playerid] == true)
	{
		TextDrawHideForPlayer(playerid, txdStatistics);

		TextDrawHideForPlayer(playerid, txdProgressObv1);
		TextDrawHideForPlayer(playerid, txdProgressObv2);
		TextDrawHideForPlayer(playerid, txdProgressObv3);
		TextDrawHideForPlayer(playerid, txdProgressObv4);
		TextDrawHideForPlayer(playerid, txdProgressObv5);

		TextDrawHideForPlayer(playerid, txdProgress1);
		TextDrawHideForPlayer(playerid, txdProgress2);
		TextDrawHideForPlayer(playerid, txdProgress3);
		TextDrawHideForPlayer(playerid, txdProgress4);
		TextDrawHideForPlayer(playerid, txdProgress5);

		TextDrawHideForPlayer(playerid, txdRamka);
		TextDrawHideForPlayer(playerid, txdRespect);
		TextDrawHideForPlayer(playerid, txdSunday);

		PlayerTextDrawHide(playerid, txdProgressZap1[playerid]);
		PlayerTextDrawHide(playerid, txdProgressZap2[playerid]);
		PlayerTextDrawHide(playerid, txdProgressZap3[playerid]);
		PlayerTextDrawHide(playerid, txdProgressZap4[playerid]);
		PlayerTextDrawHide(playerid, txdProgressZap5[playerid]);
		TextDrawShowScale[playerid] = false;
	}

//для потребностей
	PlayerTextDrawDestroyEx(playerid, txdProgressZap1[playerid]);
	PlayerTextDrawDestroyEx(playerid, txdProgressZap2[playerid]);
	PlayerTextDrawDestroyEx(playerid, txdProgressZap3[playerid]);
	PlayerTextDrawDestroyEx(playerid, txdProgressZap4[playerid]);
	PlayerTextDrawDestroyEx(playerid, txdProgressZap5[playerid]);

	//PlayerTextDrawDestroyEx(playerid, txdCHAT[playerid]);
}


stock SetPlayerShowScale(playerid, indicator_num, indicator_value, limit)//SetPlayerShowScale(playerid, 1, PlayerInfo[playerid][pParam1], operator1);//Голод new operator1 = 100;
{//заполнение таблички потребностей, indicator_num - номер бара заполнение которого хотим поменять, indicator_value - новое значение, limit - максимальное значение
    if(indicator_value-1 <= limit)//если 1000-1 <= 999
    {   //если не показан, то показать
		if(!IsPlayerConnected(playerid)) return 1;
//ВНИМАНИЕ
//static массив создается только 1 раз и существует до отключения сервера, область видимости при этом не меняется.
//Т.е. например селекторы которые делают все на глобальных переменных можно сделать локально:
//и это локальные переменные, которая создана один раз и в которой значение храниться постоянно.
//PS будьте осторожней, потому что при перезаходе игока, значение останется от предыдущего.
		//static indicator1[MAX_PLAYERS];
		//static indicator2[MAX_PLAYERS];
		//static indicator3[MAX_PLAYERS];
		//static indicator4[MAX_PLAYERS];
		//static indicator5[MAX_PLAYERS];
		new strtmp[101];
		new percent;
		switch(indicator_num)
		{
		    case 1:
		    {
				//--------------------------------------------------------------
			    if(indicator_value > limit) percent = 100;//limit;
			    else if(indicator_value < 0) percent = 0;
			    else percent = indicator_value*100/limit;
		   		for(new p=0; p<percent; p++)
		   		{//отнимаем 1, чтобы добавить в другом цвете
					strins(strtmp, "l", strlen(strtmp));
				}
				//--------------------------------------------------------------
				indicator1[playerid] = indicator_value;
				PlayerTextDrawSetStringEx(playerid, txdProgressZap1[playerid], strtmp);
				//PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
		    }
		    case 2:
		    {
				//--------------------------------------------------------------
			    if(indicator_value > limit) percent = 50;//limit;
			    else if(indicator_value < 0) percent = 0;
			    else percent = indicator_value*50/limit;

				if(	indicator_value > indicator2[playerid])
				{
			   		for(new p=0; p<percent-1; p++)
			   		{
						strins(strtmp, "l", strlen(strtmp));
					}
					strins(strtmp, "~r~l", strlen(strtmp));
				}
				else if(indicator_value < indicator2[playerid])
				{
			   		for(new p=0; p<percent-1; p++)
			   		{
						strins(strtmp, "l", strlen(strtmp));
					}
					strins(strtmp, "~g~l", strlen(strtmp));
				}
				else
				{
			   		for(new p=0; p<percent; p++)
			   		{
						strins(strtmp, "l", strlen(strtmp));
					}
				}
				//--------------------------------------------------------------
				indicator2[playerid] = indicator_value;
				PlayerTextDrawSetStringEx(playerid, txdProgressZap2[playerid], strtmp);
				//PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
		    }
		    case 3:
		    {
				//--------------------------------------------------------------
			    if(indicator_value > limit) percent = 30;//limit;
			    else if(indicator_value < 0) percent = 0;
			    else percent = indicator_value*30/limit;
				if(	indicator_value > indicator3[playerid])
				{
			   		for(new p=0; p<percent-1; p++)
			   		{
						strins(strtmp, "l", strlen(strtmp));
					}
					strins(strtmp, "~r~l", strlen(strtmp));
				}
				else if(indicator_value < indicator3[playerid])
				{
			   		for(new p=0; p<percent-1; p++)
			   		{
						strins(strtmp, "l", strlen(strtmp));
					}
					strins(strtmp, "~g~l", strlen(strtmp));
				}
				else
				{
			   		for(new p=0; p<percent; p++)
			   		{
						strins(strtmp, "l", strlen(strtmp));
					}
				}
				//--------------------------------------------------------------
				indicator3[playerid] = indicator_value;
				PlayerTextDrawSetStringEx(playerid, txdProgressZap3[playerid], strtmp);
				//PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
		    }
		    case 4:
		    {
				//--------------------------------------------------------------
			    if(indicator_value > limit) percent = 20;//limit;
			    else if(indicator_value < 0) percent = 0;
			    else percent = indicator_value*20/limit;
				if(	indicator_value > indicator4[playerid])
				{
			   		for(new p=0; p<percent-1; p++)
			   		{
						strins(strtmp, "l", strlen(strtmp));
					}
					strins(strtmp, "~r~l", strlen(strtmp));
				}
				else if(indicator_value < indicator4[playerid])
				{
			   		for(new p=0; p<percent-1; p++)
			   		{
						strins(strtmp, "l", strlen(strtmp));
					}
					strins(strtmp, "~g~l", strlen(strtmp));
				}
				else
				{
			   		for(new p=0; p<percent; p++)
			   		{
						strins(strtmp, "l", strlen(strtmp));
					}
				}
				//--------------------------------------------------------------
				indicator4[playerid] = indicator_value;
				PlayerTextDrawSetStringEx(playerid, txdProgressZap4[playerid], strtmp);
				//PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
		    }
		    case 5:
		    {
				//--------------------------------------------------------------
			    if(indicator_value > limit) percent = 15;//limit;
			    else if(indicator_value < 0) percent = 0;
			    else percent = indicator_value*15/limit;
				if(	indicator_value > indicator5[playerid])
				{
			   		for(new p=0; p<percent-1; p++)
			   		{
						strins(strtmp, "l", strlen(strtmp));
					}
					strins(strtmp, "~r~l", strlen(strtmp));
				}
				else if(indicator_value < indicator5[playerid])
				{
			   		for(new p=0; p<percent-1; p++)
			   		{
						strins(strtmp, "l", strlen(strtmp));
					}
					strins(strtmp, "~g~l", strlen(strtmp));
				}
				else
				{
			   		for(new p=0; p<percent; p++)
			   		{
						strins(strtmp, "l", strlen(strtmp));
					}
				}
				//--------------------------------------------------------------
				indicator5[playerid] = indicator_value;
				PlayerTextDrawSetStringEx(playerid, txdProgressZap5[playerid], strtmp);
				//PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
		    }
		}
		//------------------------------------------------------------------
	}
	return 1;
}
//для потребностей конец



stock needs_OnPlayerKeyState_PRESSED(playerid)
{
	if(gLadderNumber[playerid] != 0) return 1;
//для потребностей
	gTextDrawShowScale[playerid] = true;
	if(gTextDrawShowScale[playerid] == true && TextDrawShowScale[playerid] == false)
	{
			TextDrawShowForPlayer(playerid, txdStatistics);

			TextDrawShowForPlayer(playerid, txdProgressObv1);
			TextDrawShowForPlayer(playerid, txdProgressObv2);
			TextDrawShowForPlayer(playerid, txdProgressObv3);
			TextDrawShowForPlayer(playerid, txdProgressObv4);
			TextDrawShowForPlayer(playerid, txdProgressObv5);

			TextDrawShowForPlayer(playerid, txdProgress1);
			TextDrawShowForPlayer(playerid, txdProgress2);
			TextDrawShowForPlayer(playerid, txdProgress3);
			TextDrawShowForPlayer(playerid, txdProgress4);
			TextDrawShowForPlayer(playerid, txdProgress5);

			TextDrawShowForPlayer(playerid, txdRamka);
			TextDrawShowForPlayer(playerid, txdRespect);
			TextDrawShowForPlayer(playerid, txdSunday);

			PlayerTextDrawShow(playerid, txdProgressZap1[playerid]);
			PlayerTextDrawShow(playerid, txdProgressZap2[playerid]);
			PlayerTextDrawShow(playerid, txdProgressZap3[playerid]);
			PlayerTextDrawShow(playerid, txdProgressZap4[playerid]);
			PlayerTextDrawShow(playerid, txdProgressZap5[playerid]);
			TextDrawShowScale[playerid] = true;
			gTextDrawShowScale[playerid] = false;

			//SelectTextDraw(playerid, 0xFF4040AA);//будет моргать
	}
	return 1;
}

stock needs_OnPlayerKeyState_RELEASED(playerid)
{
	if(gLadderNumber[playerid] != 0) return 1;

 	gTextDrawHideScale[playerid] = true;
	if(gTextDrawHideScale[playerid] == true && TextDrawShowScale[playerid] == true)
	{
			TextDrawHideForPlayer(playerid, txdStatistics);

			TextDrawHideForPlayer(playerid, txdProgressObv1);
			TextDrawHideForPlayer(playerid, txdProgressObv2);
			TextDrawHideForPlayer(playerid, txdProgressObv3);
			TextDrawHideForPlayer(playerid, txdProgressObv4);
			TextDrawHideForPlayer(playerid, txdProgressObv5);

			TextDrawHideForPlayer(playerid, txdProgress1);
			TextDrawHideForPlayer(playerid, txdProgress2);
			TextDrawHideForPlayer(playerid, txdProgress3);
			TextDrawHideForPlayer(playerid, txdProgress4);
			TextDrawHideForPlayer(playerid, txdProgress5);

			TextDrawHideForPlayer(playerid, txdRamka);
			TextDrawHideForPlayer(playerid, txdRespect);
			TextDrawHideForPlayer(playerid, txdSunday);

			PlayerTextDrawHide(playerid, txdProgressZap1[playerid]);
			PlayerTextDrawHide(playerid, txdProgressZap2[playerid]);
			PlayerTextDrawHide(playerid, txdProgressZap3[playerid]);
			PlayerTextDrawHide(playerid, txdProgressZap4[playerid]);
			PlayerTextDrawHide(playerid, txdProgressZap5[playerid]);
			TextDrawShowScale[playerid] = false;//1
			gTextDrawHideScale[playerid] = false;//2

			//CancelSelectTextDraw(playerid);
	}
	return 1;
}

/*
stock HideTextDrawShowScale(playerid)
{
	if(TextDrawShowScale[playerid] == true)
	{
		TextDrawHideForPlayer(playerid, txdStatistics);

		TextDrawHideForPlayer(playerid, txdProgressObv1);
		TextDrawHideForPlayer(playerid, txdProgressObv2);
		TextDrawHideForPlayer(playerid, txdProgressObv3);
		TextDrawHideForPlayer(playerid, txdProgressObv4);
		TextDrawHideForPlayer(playerid, txdProgressObv5);

		TextDrawHideForPlayer(playerid, txdProgress1);
		TextDrawHideForPlayer(playerid, txdProgress2);
		TextDrawHideForPlayer(playerid, txdProgress3);
		TextDrawHideForPlayer(playerid, txdProgress4);
		TextDrawHideForPlayer(playerid, txdProgress5);

		TextDrawHideForPlayer(playerid, txdRamka);
		TextDrawHideForPlayer(playerid, txdRespect);
		TextDrawHideForPlayer(playerid, txdSunday);

		PlayerTextDrawHide(playerid, txdProgressZap1[playerid]);
		PlayerTextDrawHide(playerid, txdProgressZap2[playerid]);
		PlayerTextDrawHide(playerid, txdProgressZap3[playerid]);
		PlayerTextDrawHide(playerid, txdProgressZap4[playerid]);
		PlayerTextDrawHide(playerid, txdProgressZap5[playerid]);
		//TextDrawShowScale[playerid] = false;
	}
}*/

/*===================[FS] Система актёров v10.0=================================
_____________ При публикации просьба указывать автора Oleg_Petrow ______________

  +==========+ +==========+ +==========+ +==========+    +======+  +==+      +==+     +==+
  ||        || ||                ||      ||        ||  //       \\  \  \     |  |    /  /
  ||        || ||                ||      ||        || ||         ||  \  \    |  |   /  /
  ||=========+ |+========+       ||      ||=\\======+ ||         ||   \  \   |  |  /  /
  ||           ||                ||      ||   \\      ||         ||    \  \  |  | /  /
  ||           ||                ||      ||     \\     \\       //      \  \/   \/  /
  ||           |+=========+      ||      ||       \\    +======+         \_________/

	Обновления в версии 1.1:
	- Не нужны инклуды dc_cmd и mxINI.

	Обновления в версии 2.0:
	- Добавлена система поворота актёра.
	- Исправлен большой баг с удалением актёров.
	- Теперь при удалении обновляются все актёры.
	- Поставленно ограничение на создание актёров (максимальное число: 50).
	- Добавлена функция сохранения актёров. Они сохраняются в папку scriptfiles. Файл: op_actors.pwn
	- Показывается номер скина в "Изменении скина"
	
	Обновления в версии 3.0:
	- Добавлена функция изменения виртуального мира актёра.
	- При создании актёра ему даётся вирт.мир такой же, как и у игрока.
	- Теперь команда /actor доступна только Rcon-администратору.
	- Максимальное количество актёров теперь 100.
	- Теперь использование скрипта более удобно (я про диалог)
	- Из-за пункта выше количество строк и количество диалогов уменьшилось.
	
	Обновление в версии 3.1:
	- Исправлен маленький баг с вирт.миром
	
	Обновление в версии 4.0:
	- Теперь при сохранении сохраняется ещё и вирт.мир актёра.
	- Добавлена функция "передвигать актёра".
	- В меню управления актёром можно задать актёру анимацию. Пока что это пробная версия, поэтому пока что только анимации из библиотеки DANCING.
	- При сохранении актёров их анимации тоже сохраняются.
	
	Обновление в версии 4.1:
	- Добавлены 3 библиотеки анимаций.

	Обновление в версии 4.2:
	- Добавлены ещё 3 библиотеки анимаций.
	
	Обновление в версии 5.0:
	- Теперь максимальное количество актёров равно его лимиту в клиенте SA-MP (1000 актёров).
	- Исправлен небольшой баг при создании актёра на одном месте.
	- Теперь вместо клавиши 'Пробел' нужно нажать 'с' (по умолчанию - присесть). Причиной тому стало то, что на Пробел игроки бегают, и не удобно использовать.
	- Нельзя создать актёра, сидя в машине.
	- Теперь актёр создаётся не в метре от Вас, а на вашем месте. После создания актёра - Вас ТПшит на расстояние метра от актёра.
	- Сидя в машине нельзя переместить/повернуть актёра.
	- Теперь снова нужен инклуд mxINI (как в версии 1.0, но там он был бесполезен).
	- Теперь функция "Сохранение актёров" - не для вставки в мод.
	- Добавлена функция загрузки актёров - загружаются они после сохранения (пункт выше).
	- Исправлены текстовые ошибки.
	- Добавлена функция удаления всех актёров.
	
	Обновление в версии 5.1:
	- Исправлен крупный баг с командами (у многих команды сервера не работали).
	- Исправлен баг с удалением всех актёров (раньше не удаляло).
	
	Обновление в версии 6.0:
	- Добавлены имена актёрам. Имена отображаются над головой актёра (так же как и ник у игрока).
	- Добавлена смена имён.
	- Стандартные имена (даётся при создании актёра): мужское - Олежка; женское - Олечка.
	- Добавлена функция изменение цвета имени.
	- Стандартный цвет (при создании) - белый.
	- Добавлено сохранение/загрузка цвета.
	
	Обновление в версии 6.1:
	- Теперь в просмотре актёров, если актёры не созданы - будет писаться, типа "Актёры ещё не созданы".
	- То же самое, но с удалением и с сохранением.
	
	Обновление в версии 6.2:
	- Исправлен баг с удалением актёра (оставалось его имя над головой).
	
	Обновление в версии 7.0:
	- Добавлен рандомный выбор цвета, при создании актёра (раньше первый цвет давался только белый).
	- Имена актёрам теперь даются из файлов, которые находятся в scriptfiles.
	- Мужским скинам даются мужские имена (из файла "OP_Actors_Names_M.cfg")
	- Женским скинам даются женские имена (из файла "OP_Actors_Names_W.cfg")
	- Теперь, если в scriptfiles нет файлов: "OP_Actors.cfg", "OP_Actors_Names_M.cfg" и "OP_Actors_Names_W.cfg", то автоматически будут создаваться эти файлы.
	
	Обновление в версии 8.0:
	- Если в файлах с именами отсутствуют некоторые числа (между самым меньшим и самым большим), то эти числа будут создаваться автоматически при запуске мода.
	- Исправлена небольшая недоработка версии 7.0 (когда файлы не закрывались системой, после создания)
	- При отключении скрипта от сервера (через RCON или выключение сервера) теперь автоматически удаляются актёры и их имена (которые 3D текстом над ними)
	
	Обновление в версии 8.1:
	- Теперь при просмотре всех актёров будут показываться их имена.
	
	Обновление в версии 9.0:
	- Добавлено изменение количества имён.
	- В пункт 'Меню' добавлены 'Настройки'.
	- В меню настроек добавлена функция показа/скрытия имени актёра.
	- Добавлена функция вывода ID актёра вместе с именем (в квадратных скобках, как ID игрока) - включить и отключить её можно в настройках.
	- Пункты "Переместить актёра" и "Повернуть актёра" объединены в один раздел.
	- В новом разделе "Переместить/Повернуть актёра" добавлена функция Перемещения и Поворота актёра одновременно.

	Обновление в версии 9.1:
	- Теперь настраивать систему актёров под сервер намного проще. В Вашем моде должно быть около 30 подряд пустых диалогов. То есть номера диалогов не должны использоваться.
	- Немного прокомментировал свой код.
	
	Обновление в версии 9.2:
	- Исправлены все ошибки с цветами.
	- Небольшие улучшении в меню создании имён.
	
	Обновление в версии 10.0:
	- Обновлён дизайн раздела 'Настройки'.
	- Сделал возврат к диалогу настроек.
	- Добавлено оповещение после изменения количества имён.
	- Исправлен баг с женскими именами.
	- В функцию изменения количества имён добавлено разделение на тип имён (мужские, женские, мужские и женские).
	- Исправлен баг с удалением 3D текста актёра.
	- Исправлен баг, когда при изменении имени или цвета актёра, убирался ID актёра (если показ ID был включен).
	- Теперь не требуется искать подряд 25 свободных ID диалогов для корректной работы скрипта. Все окна показываются теперь в одном диалоге.
	- Добавлено пару новых цветов.
	Что касается кода:
	- Изменены названия некоторых переменных.
	- Прокомментированы некоторые части кода.

																																																												*/
#include <a_samp>                   // Стандартный инклуд SA:MP
#include <a_actor>                  // Инклуд для работы с актёрами
#include <mxINI>                    // Инклуд для работы с файлами

//#define COLOR_WHITE 	0xFFFFFFAA  // Не трогать!
#define DACT            15194       // Изменить под свой сервер. Данное значение - диалог, который должен быть свободным (не должно быть у Вас в моде или сторонних FS).

new Max_ActorID = -1;  				// Не трогать!
new Number_Names_Male = 10;    		// Не трогать!
new Number_Names_Female = 10;      	// Не трогать!
new bool:show_name = true; 			// Показ ника актёра при загрузке скрипта (true - включить | false - выключить)
new bool:show_id = false;   		// Показ номера актёра при загрузке скрипта (true - включить | false - выключить)

enum OP_aInfo                          // Массив актёра
{
	aID,                            // ID актёра
	aSkin,                          // ID скина актёра
	Float:aPosX,                    // Координата X актёра
	Float:aPosY,                    // Координата Y актёра
	Float:aPosZ,                    // Координата Z актёра
	Float:aPosA,                    // Координата угла поворота актёра (Angle)
	aVirt,                          // Виртуальный мир актёра
	bool:aSex,                      // Пол актёра
	aColor,                         // Цвет ника актёра
	aName[MAX_PLAYER_NAME],         // Имя актёра
	Text3D:Text3D                   // ID 3D текста актёра
};
new OP_ActorInfo[MAX_ACTORS][OP_aInfo];   // Переменная для работы с массивами актёров

//forward ShowPlayerDialog_CheckForAC(playerid, dialogid, style, caption[], info[], button1[], button2[]);
//public ShowPlayerDialog_CheckForAC(playerid, dialogid, style, caption[], info[], button1[], button2[])
stock ShowPlayerDialog_CheckForAC(playerid, dialogid, style, caption[], info[], button1[], button2[])
{
	ShowPlayerDialog(playerid, DACT, style, caption, info, button1, button2);
	SetPVarInt(playerid, "DACT", dialogid - DACT);
	return 1;
}

stock CloseDialog(playerid)
{
	DeletePVar(playerid, "DACT");
	return 0;
}

//#define ShowPlayerDialog ShowPlayerDialog_CheckForAC

stock GetActorPol(actor)
{
	switch(OP_ActorInfo[actor][aSkin])
	{
		case 1..8,14..30,32..38,42..52,57..62,66..68,70..74,78..84,86,94..128,132..137,142..147,149,153..156,158..168,170,171,173..177,179..189,200,202..204,206,208..213,217,220..223,227..230,234..236,239..242,247..250,252..255,258..262,264..297,299..305,310,311:
		{
			return OP_ActorInfo[actor][aSex] = false;
		}
		case 9..13,31,39..41,53..56,63..65,69,75.77,85,87..93,129..131,138..141,148,150..152,157,169,172,178,190..199,201,205,207,214..216,218,219,224..226,231..233,237,238,243..246,251,256,257,263,298,306..309:
		{
			return OP_ActorInfo[actor][aSex] = true;
		}
	}
	return false;
}
//public OnFilterScriptInit()         // Загрузка скрипта
stock OP_actor_OnGameModeInit()
{
/*	print("+----------------------------------------------------+");
	print("|        Скрипт от Oleg_Petrow успешно загружен      |");
	print("|    Скриптинг от Oleg_Petrow: vk.com/op_scripts     |");
	print("|          Oleg_Petrow в ВК: vk.com/flomkas          |");
	print("| Oleg_Petrow в ВК (вторая страница): vk.com/flomkas |");
	print("|            Система актёров | Версия: 10.0          |");
	print("|____________________________________________________|");
*/
	print("_____________________________________________");
	print(" ");
	print("   Система актёров | Версия: 10.0 by Oleg_Petrow");

	
	new opf = ini_openFile("Actors/OP_Actors_Names_M.cfg");
	if(opf < 0)
	{
	    new opfc = ini_createFile("Actors/OP_Actors_Names_M.cfg");
	    ini_setInteger(opfc, "MAXMN", 10);
		for(new i; i<Number_Names_Male; i++)
		{
		    new string[3];
		    format(string, sizeof(string), "%d", i);
		    ini_setString(opfc, string, "");
		}
		ini_closeFile(opfc);
		print("[OP_Actors] Файла \"OP_Actors_Names_M.cfg\" не было обнаружено.");
		print("[OP_Actors] Файл \"OP_Actors_Names_M.cfg\" был создан системой.");
	}
	else
	{
		ini_getInteger(opf, "MAXMN", Number_Names_Male);
		if(Number_Names_Male < 10) Number_Names_Male = 10, ini_setInteger(opf, "MAXMN", 10);
		for(new i; i<Number_Names_Male; i++)
		{
		    new string[4], p[MAX_PLAYER_NAME];
		    format(string, sizeof(string), "%d", i);
		    ini_getString(opf, string, p);
	    	if(!strlen(p)) ini_setString(opf, string, "");
		}
		print("[OP_Actors] Файл \"OP_Actors_Names_M.cfg\" успешно загружен.");
	}
	ini_closeFile(opf);
	opf = ini_openFile("Actors/OP_Actors_Names_W.cfg");
	if(opf < 0)
	{
	    new opfc = ini_createFile("Actors/OP_Actors_Names_W.cfg");
	    ini_setInteger(opfc, "MAXWN", 10);
		for(new i; i<Number_Names_Female; i++)
		{
		    new string[3];
		    format(string, sizeof(string), "%d", i);
		    ini_setString(opfc, string, "");
		}
		ini_closeFile(opfc);
		print("[OP_Actors] Файла \"OP_Actors_Names_W.cfg\" не было обнаружено.");
		print("[OP_Actors] Файл \"OP_Actors_Names_W.cfg\" был создан системой.");
	}
	else
	{
		ini_getInteger(opf, "MAXWN", Number_Names_Female);
		if(Number_Names_Female < 10) Number_Names_Female = 10, ini_setInteger(opf, "MAXWN", 10);
		for(new i; i<Number_Names_Female; i++)
		{
		    new string[4], p[MAX_PLAYER_NAME];
		    format(string, sizeof(string), "%d", i);
		    ini_getString(opf, string, p);
	    	if(!strlen(p)) ini_setString(opf, string, "");
		}
		print("[OP_Actors] Файл \"OP_Actors_Names_W.cfg\" успешно загружен.");
	}
	ini_closeFile(opf);
	LoadActors();
	return 1;
}
//public OnFilterScriptExit()         // Завершение работы скрипта
stock OP_actor_OnGameModeExit()
{
	for(new i; i <= Max_ActorID; i++)
	{
		DestroyActor(i);
		if(show_name == true) Delete3DTextLabel(OP_ActorInfo[i][Text3D]);
	}
	for(new i; i < GetMaxPlayers(); i++)
	{
		DeletePVar(i, "DACT");
		DeletePVar(i, "DACT+21");
	}
	return 1;
}
stock LoadActors()                  // Загрузка актёров
{
	new time = GetTickCount();
	new iniFile = ini_openFile("Actors/OP_Actors.cfg");
	if(iniFile < 0)
	{
		new timeFile = ini_createFile("Actors/OP_Actors.cfg");
		new string[7];
		format(string, sizeof(string), "MAXACT");
		ini_setInteger(timeFile, string, Max_ActorID);
		ini_closeFile(timeFile);
		print("[OP_Actors] Файла \"OP_Actors.cfg\" не было обнаружено.");
		print("[OP_Actors] Файл \"OP_Actors.cfg\" был создан системой.");
		return 1;
	}
	ini_getInteger(iniFile, "MAXACT",Max_ActorID);
	for(new i = 0; i <= Max_ActorID; i++)
	{
	    new string[50];
	    format(string, sizeof(string), "[%d] aID", i);
		ini_getInteger(iniFile, string, OP_ActorInfo[i][aID]);
	    format(string, sizeof(string), "[%d] aSkin", i);
		ini_getInteger(iniFile, string, OP_ActorInfo[i][aSkin]);
	    format(string, sizeof(string), "[%d] aVirt", i);
		ini_getInteger(iniFile, string, OP_ActorInfo[i][aVirt]);
	    format(string, sizeof(string), "[%d] aPosX", i);
		ini_getFloat(iniFile, string, OP_ActorInfo[i][aPosX]);
	    format(string, sizeof(string), "[%d] aPosY", i);
		ini_getFloat(iniFile, string, OP_ActorInfo[i][aPosY]);
	    format(string, sizeof(string), "[%d] aPosZ", i);
		ini_getFloat(iniFile, string, OP_ActorInfo[i][aPosZ]);
	    format(string, sizeof(string), "[%d] aPosA", i);
		ini_getFloat(iniFile, string, OP_ActorInfo[i][aPosA]);
	    format(string, sizeof(string), "[%d] aColor", i);
		ini_getInteger(iniFile, string, OP_ActorInfo[i][aColor]);
		format(string, sizeof(string), "[%d] aName", i);
		new nameact[MAX_PLAYER_NAME];
		ini_getString(iniFile, string,nameact);
		format(OP_ActorInfo[i][aName], MAX_PLAYER_NAME, "%s", nameact);
		CreateActor(OP_ActorInfo[i][aSkin], OP_ActorInfo[i][aPosX], OP_ActorInfo[i][aPosY], OP_ActorInfo[i][aPosZ], OP_ActorInfo[i][aPosA]);
		SetActorVirtualWorld(i, OP_ActorInfo[i][aVirt]);
		LoadActorAnim(i);
		if(show_name == true)
		{
			if(show_id == false) OP_ActorInfo[i][Text3D] = Create3DTextLabel(OP_ActorInfo[i][aName], SetActorColor(i,true), OP_ActorInfo[i][aPosX], OP_ActorInfo[i][aPosY], OP_ActorInfo[i][aPosZ]+1.1, 15.0, OP_ActorInfo[i][aVirt], 1);
			else
			{
				new str[MAX_PLAYER_NAME+8];
				format(str, sizeof(str), "%s [%d]", OP_ActorInfo[i][aName], i);
				OP_ActorInfo[i][Text3D] = Create3DTextLabel(str, SetActorColor(i,true), OP_ActorInfo[i][aPosX], OP_ActorInfo[i][aPosY], OP_ActorInfo[i][aPosZ]+1.1, 15.0, OP_ActorInfo[i][aVirt], 1);
			}
		}
	}
	ini_closeFile(iniFile);

	printf("8/19. [Загрузка OP актёров]: Было загружено - %d, потрачено - %d (ms)", Max_ActorID+1, GetTickCount() - time);//new time = GetTickCount();
	return 1;
}
stock SaveActors()          // Сохранение актёров
{
	new iniFile = ini_openFile("Actors/OP_Actors.cfg");
	ini_setInteger(iniFile, "MAXACT", Max_ActorID);
	for(new i = 0; i <= Max_ActorID; i++)
	{
	    new string[50];
	    format(string, sizeof(string), "[%d] aID", i);
		ini_setInteger(iniFile, string, OP_ActorInfo[i][aID]);
	    format(string, sizeof(string), "[%d] aSkin", i);
		ini_setInteger(iniFile, string, OP_ActorInfo[i][aSkin]);
	    format(string, sizeof(string), "[%d] aVirt", i);
		ini_setInteger(iniFile, string, OP_ActorInfo[i][aVirt]);
	    format(string, sizeof(string), "[%d] aPosX", i);
		ini_setFloat(iniFile, string, OP_ActorInfo[i][aPosX]);
	    format(string, sizeof(string), "[%d] aPosY", i);
		ini_setFloat(iniFile, string, OP_ActorInfo[i][aPosY]);
	    format(string, sizeof(string), "[%d] aPosZ", i);
		ini_setFloat(iniFile, string, OP_ActorInfo[i][aPosZ]);
	    format(string, sizeof(string), "[%d] aPosA", i);
		ini_setFloat(iniFile, string, OP_ActorInfo[i][aPosA]);
	    format(string, sizeof(string), "[%d] aName", i);
		ini_setString(iniFile, string, OP_ActorInfo[i][aName]);
	    format(string, sizeof(string), "[%d] aColor", i);
		ini_setInteger(iniFile, string, OP_ActorInfo[i][aColor]);
	}
	print("Все актёры были успешно сохранены!");
	ini_closeFile(iniFile);
	return 1;
}
stock SetActorColor(actor, bool:type)
{
	new color;
	switch(type)
	{
	    case true:
	    {
			switch(OP_ActorInfo[actor][aColor])
			{
			    case 0: color = 0xFFFFFFFF;
				case 1: color = 0x0000FFFF;
				case 2: color = 0x000000FF;
				case 3: color = 0xFF0000FF;
				case 4: color = 0xFFFF00FF;
				case 5: color = 0x00FF00FF;
				case 6: color = 0x000066FF;
				case 7: color = 0xFF66FFFF;
				case 8: color = 0x009900FF;
				case 9: color = 0x00FFFFFF;
				case 10: color = 0xFF8C00FF;
				case 11: color = 0x006400FF;
				default: color = 0xFFFFFFFF;
			}
			return color;
		}
		case false:
		{
		    new rand = random(10);
			OP_ActorInfo[actor][aColor] = rand;
		    switch(rand)
		    {
			    case 0: color = 0xFFFFFFFF;
				case 1: color = 0x0000FFFF;
				case 2: color = 0x000000FF;
				case 3: color = 0xFF0000FF;
				case 4: color = 0xFFFF00FF;
				case 5: color = 0x00FF00FF;
				case 6: color = 0x000066FF;
				case 7: color = 0xFF66FFFF;
				case 8: color = 0x009900FF;
				case 9: color = 0x00FFFFFF;
				case 10: color = 0xFF8C00FF;
				case 11: color = 0x006400FF;
				default: color = 0xFFFFFFFF;
		    }
			return color;
		}
	}
	return false;
}
stock GetName(actor)
{
	new string[64], rname = random(10);
	switch(OP_ActorInfo[actor][aSex])
	{
	    case false:
	    {
			new OPAct = ini_openFile("Actors/OP_Actors_Names_M.cfg"), nameact[MAX_PLAYER_NAME];
			format(string, sizeof(string), "%d", rname);
			ini_getString(OPAct, string, nameact);
			format(OP_ActorInfo[actor][aName], MAX_PLAYER_NAME, "%s", nameact);
			ini_closeFile(OPAct);
			if(!strlen(OP_ActorInfo[actor][aName])) format(OP_ActorInfo[actor][aName], 7, "Олежка");
	    }
	    case true:
		{
			new OPAct = ini_openFile("Actors/OP_Actors_Names_W.cfg"), nameact[MAX_PLAYER_NAME];
			format(string, sizeof(string), "%d", rname);
			ini_getString(OPAct, string, nameact);
			format(OP_ActorInfo[actor][aName], MAX_PLAYER_NAME, "%s", nameact);
			ini_closeFile(OPAct);
			if(!strlen(OP_ActorInfo[actor][aName])) format(OP_ActorInfo[actor][aName], 7, "Олечка");
		}
	}
	if(show_name == true)
	{
		if(show_id == false) OP_ActorInfo[actor][Text3D] = Create3DTextLabel(OP_ActorInfo[actor][aName], SetActorColor(actor,false), OP_ActorInfo[actor][aPosX], OP_ActorInfo[actor][aPosY], OP_ActorInfo[actor][aPosZ]+1.1, 15.0, OP_ActorInfo[actor][aVirt], 1);
		else
		{
			new str[MAX_PLAYER_NAME+8];
			format(str, sizeof(str), "%s [%d]", OP_ActorInfo[actor][aName], actor);
			OP_ActorInfo[actor][Text3D] = Create3DTextLabel(str, SetActorColor(actor,false), OP_ActorInfo[actor][aPosX], OP_ActorInfo[actor][aPosY], OP_ActorInfo[actor][aPosZ]+1.1, 15.0, OP_ActorInfo[actor][aVirt], 1);
		}
	}
	return 1;
}

stock Settings(playerid)
{
	new string[250];
	format(string, sizeof string, "Список рандомных имён\t\nИзменение количества имён\t{81DAF5}М{FFFFFF} = %d | {81DAF5}Ж{FFFFFF} = %d\nИмена актёров\t%s\nНомера(ID) актёров\t%s", Number_Names_Male, Number_Names_Female, (show_name == true) ? ("{01DF01}Включены{FFFFFF}") : ("{FE2E2E}Отключены{FFFFFF}"), (show_id == true) ? ("{01DF01}Включены{FFFFFF}") : ("{FE2E2E}Отключены{FFFFFF}"));
    ShowPlayerDialog_CheckForAC(playerid, DACT+22, DIALOG_STYLE_TABLIST, "Настройки",string,"Далее","Назад");
	return 1;
}

//public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
stock OP_actor_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid != DACT) return 0;
    switch(GetPVarInt(playerid, "DACT"))
    {
        case 0:
        {
	        if(!response) return CloseDialog(playerid);
			switch(listitem)
			{
				case 0:
				{
				    if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Нельзя создать актёра, сидя в машине!");
					ShowPlayerDialog_CheckForAC(playerid, DACT+1, DIALOG_STYLE_INPUT, "Создание актёра","Введите номер скина, который будет у актёра!", "Далее","Назад");
				}
				case 1:
				{
        			if(Max_ActorID < 0) return SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Актёры ещё не созданы!");
					new string[32], stringer[2000];
				    for(new i = 0; i <= Max_ActorID; i++)
				    {
					    format(string, sizeof(string), "%s[%d]\n", OP_ActorInfo[i][aName], i);
					    strcat(stringer, string);
				    }
					ShowPlayerDialog_CheckForAC(playerid, DACT+26, DIALOG_STYLE_LIST, "Выберите актёра",stringer, "Далее","Назад");
				}
				case 2:
				{
				    if(Max_ActorID < 0) return SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Актёры не были созданы!");
				    for(new i = 0; i <= Max_ActorID; i++)
				    {
				        DestroyActor(i);
						if(show_name == true) Delete3DTextLabel(OP_ActorInfo[i][Text3D]);
				    }
				    Max_ActorID = -1;
					SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Все актёры удалены!");
				}
				case 3:
				{
				    if(Max_ActorID < 0) return SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Актёры ещё не созданы!");
				    SaveActors();
					SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Все актёры сохранены. При следующем запуске мода вместе со скриптом - актёры будут загружены.");
				}
				case 4: Settings(playerid);
			}
		}
	    case 1:
		{
	        if(!response) return CloseDialog(playerid), OnPlayerCommandText(playerid, "/actor");
	        if(Max_ActorID >= 999) return SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] У вас уже максимальное количество актёров!");
			if(!strlen(inputtext)) return SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Неверный номер скина!");
			if(strval(inputtext) < 1 || strval(inputtext) > 311) return SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Неверный номер скина!");
			new Float: pX, Float: pY, Float: pZ, Float: pA, Float: pXx, Float: pYy, Float: pZz;
			GetPlayerPos(playerid, pX, pY, pZ);
			for(new i = 0; i <= Max_ActorID; i++)
			{
				GetActorPos(i, pXx, pYy, pZz);
				if(pX == pXx && pY == pYy) return SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Актёр уже существует на этом месте!");
			}
			GetPlayerFacingAngle(playerid, pA);
			new string[160];
			Max_ActorID = CreateActor(strval(inputtext), pX, pY, pZ, pA);
			OP_ActorInfo[Max_ActorID][aID] = Max_ActorID;
			OP_ActorInfo[Max_ActorID][aSkin] = strval(inputtext);
			OP_ActorInfo[Max_ActorID][aVirt] = GetPlayerVirtualWorld(playerid);
			OP_ActorInfo[Max_ActorID][aPosX] = pX;
			OP_ActorInfo[Max_ActorID][aPosY] = pY;
			OP_ActorInfo[Max_ActorID][aPosZ] = pZ;
			OP_ActorInfo[Max_ActorID][aPosA] = pA;
			SetActorVirtualWorld(Max_ActorID, OP_ActorInfo[Max_ActorID][aVirt]);
			LoadActorAnim(Max_ActorID);
			SetPlayerPos(playerid, pX, pY+1, pZ);
			GetActorPol(Max_ActorID);
			GetName(Max_ActorID);
			SendClientMessage(playerid, 0x00FFFFFF, "Вы создали актёра.");
			format(string, 160, "{00FFFF}Номер: {FFFFFF}%d{FF0000} | {00FFFF}Имя: {FFFFFF}%s{FF0000} | {00FFFF}Вирт.мир: {FFFFFF}%d", Max_ActorID, OP_ActorInfo[Max_ActorID][aName], OP_ActorInfo[Max_ActorID][aVirt]);
			SendClientMessage(playerid, COLOR_WHITE, string);
	    }
		case 2:
		{
		    if(!response) return CloseDialog(playerid);
			new i = GetPVarInt(playerid, "actor");
		    switch(listitem)
		    {
		        case 0:
				{
				    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SetPlayerPos(playerid, OP_ActorInfo[i][aPosX], OP_ActorInfo[i][aPosY]+2, OP_ActorInfo[i][aPosZ]);
					SetVehiclePos(GetPlayerVehicleID(playerid), OP_ActorInfo[i][aPosX], OP_ActorInfo[i][aPosY]+3, OP_ActorInfo[i][aPosZ]);
				}
				case 1: ShowPlayerDialog_CheckForAC(playerid, DACT+3, DIALOG_STYLE_INPUT, "Изменить скин актёру","Введите номер скина", "Сменить","Назад");
				case 2:
				{
	                DestroyActor(i);
					if(show_name == true) Delete3DTextLabel(OP_ActorInfo[i][Text3D]);
				    for(new o = 0; o <= Max_ActorID; o++)
				    {
				        if(o <= i) continue;
						DestroyActor(o);
						OP_ActorInfo[o-1][aID] = CreateActor(OP_ActorInfo[o][aSkin], OP_ActorInfo[o][aPosX], OP_ActorInfo[o][aPosY], OP_ActorInfo[o][aPosZ], OP_ActorInfo[o][aPosA]);
						OP_ActorInfo[o-1][aSkin] = OP_ActorInfo[o][aSkin];
						OP_ActorInfo[o-1][aVirt] = OP_ActorInfo[o][aVirt];
						OP_ActorInfo[o-1][aPosX] = OP_ActorInfo[o][aPosX];
						OP_ActorInfo[o-1][aPosY] = OP_ActorInfo[o][aPosY];
						OP_ActorInfo[o-1][aPosZ] = OP_ActorInfo[o][aPosZ];
						OP_ActorInfo[o-1][aPosA] = OP_ActorInfo[o][aPosA];
						OP_ActorInfo[o-1][aColor] = OP_ActorInfo[o][aColor];
						format(OP_ActorInfo[o-1][aName], MAX_PLAYER_NAME, OP_ActorInfo[o][aName]);
						SetActorVirtualWorld(OP_ActorInfo[o-1][aID], OP_ActorInfo[o-1][aVirt]);
						if(show_name == true)
						{
							Delete3DTextLabel(OP_ActorInfo[o][Text3D]);
							if(show_id == false) OP_ActorInfo[o-1][Text3D] = Create3DTextLabel(OP_ActorInfo[o-1][aName], SetActorColor(o-1,true), OP_ActorInfo[o-1][aPosX], OP_ActorInfo[o-1][aPosY], OP_ActorInfo[o-1][aPosZ]+1.1, 15.0, OP_ActorInfo[o-1][aVirt], 1);
							else
							{
								new str[MAX_PLAYER_NAME+8];
								format(str, sizeof(str), "%s [%d]", OP_ActorInfo[o-1][aName], o-1);
								OP_ActorInfo[o-1][Text3D] = Create3DTextLabel(str, SetActorColor(o-1,true), OP_ActorInfo[o-1][aPosX], OP_ActorInfo[o-1][aPosY], OP_ActorInfo[o-1][aPosZ]+1.1, 15.0, OP_ActorInfo[o-1][aVirt], 1);
							}
						}
						LoadActorAnim(o-1);
				    }
				    Max_ActorID --;
	        		SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Вы успешно удалили актёра. Все актёры обновлены!");
				}
				case 3: ShowPlayerDialog_CheckForAC(playerid, DACT+25, DIALOG_STYLE_LIST, "Повернуть/Переместить актёра","Повернуть актёра\nПеревестить актёра\nПовернуть и переместить актёра","Выбрать","Назад");
				case 4: ShowPlayerDialog_CheckForAC(playerid, DACT+4, DIALOG_STYLE_INPUT, "Изменение вирт.мира актёра","Введите вирт.мир актёра \n\nвирт.мир не может быть меньше 0 и больше 1000.", "Далее","Назад");
				case 5: ShowPlayerDialog_CheckForAC(playerid, DACT+5, DIALOG_STYLE_LIST, "Анимации","Очистить анимацию\nDANCING\nBAR\nBEACH\nBOMBER\nBUDDY\nCAMERA\nped","Далее","Назад");
				case 6:
				{
				    if(show_name == false) return SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] У Вас отключён показ имён!");
					ShowPlayerDialog_CheckForAC(playerid, DACT+13, DIALOG_STYLE_INPUT, "Изменить имя актёру","Введите новое имя","Далее","Отмена");
				}
				case 7:
				{
				    if(show_name == false) return SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] У Вас отключён показ имён!");
					ShowPlayerDialog_CheckForAC(playerid, DACT+14, DIALOG_STYLE_LIST, "Цвет имени актёра","{FFFFFF}Белый\n{0000FF}Синий\n{000000}Чёрный\n{FF0000}Красный\n{FFFF00}Жёлтый\n{00FF00}Ярко-зелёный\n{000066}Тёмно-синий\n{FF66FF}Розовый\n{008000}Зелёный\n{00FFFF}Голубой\n{FF8C00}Оранжевый\n{006400}Тёмно-зелёный","Далее","Отмена");
				}
		 	}
		}
	    case 3:
	    {
	        if(!response) return CloseDialog(playerid), OnPlayerCommandText(playerid, "/actor");
			if(!strlen(inputtext) || strval(inputtext) < 1 || strval(inputtext) > 311) return SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Неверный номер скина!");
			new i = GetPVarInt(playerid, "actor"), string[100];
			DestroyActor(i);
			CreateActor(strval(inputtext), OP_ActorInfo[i][aPosX], OP_ActorInfo[i][aPosY], OP_ActorInfo[i][aPosZ], OP_ActorInfo[i][aPosA]);
			SetActorVirtualWorld(i, OP_ActorInfo[i][aVirt]);
			OP_ActorInfo[i][aSkin] = strval(inputtext);
			LoadActorAnim(i);
			format(string, sizeof(string), "[{0000FF}OP_Actor{FFFFFF}] Новый скин актёра номер {00FF00}%d{FFFFFF}: {FF0000}%d",i, OP_ActorInfo[i][aSkin]);
			SendClientMessage(playerid, COLOR_WHITE, string);
	    }
		case 4:
		{
			if(!response) return CloseDialog(playerid), OnPlayerCommandText(playerid, "/actor");
			if(!strlen(inputtext) || strval(inputtext) < 0 || strval(inputtext) > 1000) return SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Неверный номер вирт.мира!");
			new i = GetPVarInt(playerid, "actor"), string[100];
			SetActorVirtualWorld(i, strval(inputtext));
			OP_ActorInfo[i][aVirt] = strval(inputtext);
			if(show_name == true)
			{
				Delete3DTextLabel(OP_ActorInfo[i][Text3D]);
				if(show_id == false) OP_ActorInfo[i][Text3D] = Create3DTextLabel(OP_ActorInfo[i][aName], SetActorColor(i,true), OP_ActorInfo[i][aPosX], OP_ActorInfo[i][aPosY], OP_ActorInfo[i][aPosZ]+1.1, 15.0, OP_ActorInfo[i][aVirt], 1);
				else
				{
					new str[MAX_PLAYER_NAME+8];
					format(str, sizeof(str), "%s [%d]", OP_ActorInfo[i][aName], i);
					OP_ActorInfo[i][Text3D] = Create3DTextLabel(str, SetActorColor(i,true), OP_ActorInfo[i][aPosX], OP_ActorInfo[i][aPosY], OP_ActorInfo[i][aPosZ]+1.1, 15.0, OP_ActorInfo[i][aVirt], 1);
				}
			}
			format(string, sizeof(string), "[{0000FF}OP_Actor{FFFFFF}] Новый вирт.мир актёра номер {00FF00}%d{FFFFFF}: {FF0000}%d",i, OP_ActorInfo[i][aVirt]);
			SendClientMessage(playerid, COLOR_WHITE, string);
			LoadActorAnim(i);
		}
		case 5:
		{
			if(!response) return CloseDialog(playerid), OnPlayerCommandText(playerid, "/actor");
			new i = GetPVarInt(playerid, "actor");
			switch(listitem)
			{
			    case 0: ClearActorAnimations(i);
			    case 1: ShowPlayerDialog_CheckForAC(playerid, DACT+6, DIALOG_STYLE_LIST, "Выберите анимацию | {FF0000}DANCING","bd_clap\nbd_clap1\ndance_loops\nDAN_Down_A\nDAN_Left_A\nDAN_Loop_A\nDAN_Right_A\nDAN_Up_A\ndnce_M_a\ndnce_M_b\ndnce_M_c\ndnce_M_d\ndnce_M_e","Далее","Назад");
				case 2: ShowPlayerDialog_CheckForAC(playerid, DACT+7, DIALOG_STYLE_LIST, "Выберите анимацию | {FF0000}BAR","Barcustom_loop\nBARman_idle\nBarserve_bottle\nBarserve_give\nBarserve_glass\nBarserve_loop\ndnk_stndF_loop\ndnk_stndM_loop","Далее","Назад");
				case 3: ShowPlayerDialog_CheckForAC(playerid, DACT+8, DIALOG_STYLE_LIST, "Выберите анимацию | {FF0000}BEACH","bather\nLay_Bac_Loop\nParkSit_M_loop\nParkSit_W_loop\nSitnWait_loop_W","Далее","Назад");
				case 4: ShowPlayerDialog_CheckForAC(playerid, DACT+9, DIALOG_STYLE_LIST, "Выберите анимацию | {FF0000}BOMBER","BOM_Plant\nBOM_Plant_Loop","Далее","Назад");
				case 5: ShowPlayerDialog_CheckForAC(playerid, DACT+10, DIALOG_STYLE_LIST, "Выберите анимацию | {FF0000}BUDDY", "buddy_crouchfire\nbuddy_crouchreload\nbuddy_fire","Далее","Назад");
				case 6: ShowPlayerDialog_CheckForAC(playerid, DACT+11, DIALOG_STYLE_LIST, "Выберите анимацию | {FF0000}CAMERA", "camcrch_cmon\ncamcrch_idleloop\ncamcrch_stay\ncamcrch_to_camstnd\ncamstnd_cmon\ncamstnd_idleloop\ncamstnd_lkabt","Далее","Назад");
				case 7: ShowPlayerDialog_CheckForAC(playerid, DACT+12, DIALOG_STYLE_LIST, "Выберите анимацию | {FF0000}ped", "WALK_armed\nWALK_civi\nWALK_csaw\nWalk_DoorPartial\nWALK_drunk\nWALK_fat\nWALK_fatold\nWALK_gang1\nWALK_gang2\nWALK_old\nWALK_player\nWALK_rocket\nWALK_shuffle\nWALK_start\nWALK_start_armed\nWALK_start_csaw\nWALK_start_rocket\nWalk_Wuzi\nWEAPON_crouch\nXPRESSscratch\nsprint_civi\nsprint_panic\nSprint_Wuzi","Далее","Назад");
			}
		}
		case 6:
		{
		    if(!response) return CloseDialog(playerid), OnPlayerCommandText(playerid, "/actor");
			new i = GetPVarInt(playerid, "actor");
		    switch(listitem)
		    {
		        case 0: ApplyActorAnimation(i, "DANCING", "bd_clap", 4.1, 1, 0, 0, 0, 0);
		        case 1: ApplyActorAnimation(i, "DANCING", "bd_clap1", 4.1, 1, 0, 0, 0, 0); 
		        case 2: ApplyActorAnimation(i, "DANCING", "dance_loop", 4.1, 1, 0, 0, 0, 0); 
		        case 3: ApplyActorAnimation(i, "DANCING", "DAN_Down_A", 4.1, 1, 0, 0, 0, 0);
		        case 4: ApplyActorAnimation(i, "DANCING", "DAN_Left_A", 4.1, 1, 0, 0, 0, 0);
		        case 5: ApplyActorAnimation(i, "DANCING", "DAN_Loop_A", 4.1, 1, 0, 0, 0, 0);
		        case 6: ApplyActorAnimation(i, "DANCING", "DAN_Right_A", 4.1, 1, 0, 0, 0, 0); 
		        case 7: ApplyActorAnimation(i, "DANCING", "DAN_Up_A", 4.1, 1, 0, 0, 0, 0);
		        case 8: ApplyActorAnimation(i, "DANCING", "dnce_M_a", 4.1, 1, 0, 0, 0, 0); 
		        case 9: ApplyActorAnimation(i, "DANCING", "dnce_M_b", 4.1, 1, 0, 0, 0, 0);
		        case 10: ApplyActorAnimation(i, "DANCING", "dnce_M_c", 4.1, 1, 0, 0, 0, 0);
		        case 11: ApplyActorAnimation(i, "DANCING", "dnce_M_d", 4.1, 1, 0, 0, 0, 0); 
		        case 12: ApplyActorAnimation(i, "DANCING", "dnce_M_e", 4.1, 1, 0, 0, 0, 0);
		    }
		}
		case 7:
		{
		    if(!response) return CloseDialog(playerid), OnPlayerCommandText(playerid, "/actor");
			new i = GetPVarInt(playerid, "actor");
			switch(listitem)
			{
			    case 0: ApplyActorAnimation(i, "BAR", "Barcustom_loop", 4.1, 1, 0, 0, 0, 0); 
			    case 1: ApplyActorAnimation(i, "BAR", "BARman_idle", 4.1, 1, 0, 0, 0, 0); 
			    case 2: ApplyActorAnimation(i, "BAR", "Barserve_bottle", 4.1, 1, 0, 0, 0, 0); 
			    case 3: ApplyActorAnimation(i, "BAR", "Barserve_give", 4.1, 1, 0, 0, 0, 0); 
			    case 4: ApplyActorAnimation(i, "BAR", "Barserve_glass", 4.1, 1, 0, 0, 0, 0); 
			    case 5: ApplyActorAnimation(i, "BAR", "Barserve_loop", 4.1, 1, 0, 0, 0, 0);
			    case 6: ApplyActorAnimation(i, "BAR", "dnk_stndF_loop", 4.1, 1, 0, 0, 0, 0); 
			    case 7: ApplyActorAnimation(i, "BAR", "dnk_stndM_loop", 4.1, 1, 0, 0, 0, 0);
			}
		}
		case 8:
		{
		    if(!response) return CloseDialog(playerid), OnPlayerCommandText(playerid, "/actor");
			new i = GetPVarInt(playerid, "actor");
		    switch(listitem)
		    {
		        case 0: ApplyActorAnimation(i, "BEACH", "bather", 4.1, 1, 0, 0, 0, 0); 
		        case 1: ApplyActorAnimation(i, "BEACH", "Lay_Bac_Loop", 4.1, 1, 0, 0, 0, 0);
		        case 2: ApplyActorAnimation(i, "BEACH", "ParkSit_M_loop", 4.1, 1, 0, 0, 0, 0); 
		        case 3: ApplyActorAnimation(i, "BEACH", "ParkSit_W_loop", 4.1, 1, 0, 0, 0, 0);
		        case 4: ApplyActorAnimation(i, "BEACH", "SitnWait_loop_W", 4.1, 1, 0, 0, 0, 0);
			}
		}
		case 9:
		{
		    if(!response) return CloseDialog(playerid), OnPlayerCommandText(playerid, "/actor");
		    new i = GetPVarInt(playerid, "actor");
		    switch(listitem)
		    {
		        case 0: ApplyActorAnimation(i, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0);
		        case 1: ApplyActorAnimation(i, "BOMBER", "BOM_Plant_Loop", 4.1, 1, 0, 0, 0, 0); 
		    }
		}
		case 10:
		{
			if(!response) return CloseDialog(playerid), OnPlayerCommandText(playerid, "/actor");
			new i = GetPVarInt(playerid, "actor");
			switch(listitem)
			{
			    case 0: ApplyActorAnimation(i, "BUDDY", "buddy_crouchfire", 4.1, 1, 0, 0, 0, 0);
			    case 1: ApplyActorAnimation(i, "BUDDY", "buddy_crouchreload", 4.1, 1, 0, 0, 0, 0); 
			    case 2: ApplyActorAnimation(i, "BUDDY", "buddy_fire", 4.1, 1, 0, 0, 0, 0);
			}
		}
		case 11:
		{
		    if(!response) return CloseDialog(playerid), OnPlayerCommandText(playerid, "/actor");
			new i = GetPVarInt(playerid, "actor");
		    switch(listitem)
		    {
		        case 0: ApplyActorAnimation(i, "CAMERA", "camcrch_cmon", 4.1, 1, 0, 0, 0, 0); 
		        case 1: ApplyActorAnimation(i, "CAMERA", "camcrch_idleloop", 4.1, 1, 0, 0, 0, 0); 
		        case 2: ApplyActorAnimation(i, "CAMERA", "camcrch_stay", 4.1, 1, 0, 0, 0, 0);
		        case 3: ApplyActorAnimation(i, "CAMERA", "camcrch_to_camstnd", 4.1, 1, 0, 0, 0, 0);
		        case 4: ApplyActorAnimation(i, "CAMERA", "camstnd_cmon", 4.1, 1, 0, 0, 0, 0);
		        case 5: ApplyActorAnimation(i, "CAMERA", "camstnd_idleloop", 4.1, 1, 0, 0, 0, 0);
		        case 6: ApplyActorAnimation(i, "CAMERA", "camstnd_lkabt", 4.1, 1, 0, 0, 0, 0); 
		        case 7: ApplyActorAnimation(i, "CAMERA", "camstnd_to_camcrch", 4.1, 1, 0, 0, 0, 0);
	     	}
		}
		case 12:
		{
		    if(!response) return CloseDialog(playerid), OnPlayerCommandText(playerid, "/actor");
			new i = GetPVarInt(playerid, "actor");
		    switch(listitem)
		    {
		        case 0: ApplyActorAnimation(i, "ped", "WALK_armed", 4.1, 0, 0, 0, 0, 0);
		        case 1: ApplyActorAnimation(i, "ped", "WALK_civi", 4.1, 0, 0, 0, 0, 0); 
		        case 2: ApplyActorAnimation(i, "ped", "WALK_csaw", 4.1, 0, 0, 0, 0, 0);
		        case 3: ApplyActorAnimation(i, "ped", "Walk_DoorPartial", 4.1, 0, 0, 0, 0, 0); 
		        case 4: ApplyActorAnimation(i, "ped", "WALK_drunk", 4.1, 0, 0, 0, 0, 0); 
		        case 5: ApplyActorAnimation(i, "ped", "WALK_fat", 4.1, 0, 0, 0, 0, 0);
		        case 6: ApplyActorAnimation(i, "ped", "WALK_fatold", 4.1, 0, 0, 0, 0, 0);
		        case 7: ApplyActorAnimation(i, "ped", "WALK_gang1", 4.1, 0, 0, 0, 0, 0);
		        case 8: ApplyActorAnimation(i, "ped", "WALK_gang2", 4.1, 0, 0, 0, 0, 0); 
		        case 9: ApplyActorAnimation(i, "ped", "WALK_old", 4.1, 0, 0, 0, 0, 0);
		        case 10: ApplyActorAnimation(i, "ped", "WALK_player", 4.1, 0, 0, 0, 0, 0);
		        case 11: ApplyActorAnimation(i, "ped", "WALK_rocket", 4.1, 0, 0, 0, 0, 0);
		        case 12: ApplyActorAnimation(i, "ped", "WALK_shuffle", 4.1, 0, 0, 0, 0, 0); 
		        case 13: ApplyActorAnimation(i, "ped", "WALK_start", 4.1, 0, 0, 0, 0, 0); 
		        case 14: ApplyActorAnimation(i, "ped", "WALK_start_armed", 4.1, 0, 0, 0, 0, 0);
		        case 15: ApplyActorAnimation(i, "ped", "WALK_start_csaw", 4.1, 0, 0, 0, 0, 0); 
		        case 16: ApplyActorAnimation(i, "ped", "WALK_start_rocket", 4.1, 0, 0, 0, 0, 0); 
		        case 17: ApplyActorAnimation(i, "ped", "Walk_Wuzi", 4.1, 0, 0, 0, 0, 0); 
		        case 18: ApplyActorAnimation(i, "ped", "WEAPON_crouch", 4.1, 0, 0, 0, 0, 0);
		        case 19: ApplyActorAnimation(i, "ped", "XPRESSscratch", 4.1, 0, 0, 0, 0, 0); 
		        case 20: ApplyActorAnimation(i, "ped", "sprint_civi", 4.1, 0, 0, 0, 0, 0);
		        case 21: ApplyActorAnimation(i, "ped", "sprint_panic", 4.1, 0, 0, 0, 0, 0); 
		        case 22: ApplyActorAnimation(i, "ped", "Sprint_Wuzi", 4.1, 0, 0, 0, 0, 0);
	     	}
		}
		case 13:
		{
			if(!response) return CloseDialog(playerid);
		    if(!strlen(inputtext)) return SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Вы ничего не ввели!");
		    new actor = GetPVarInt(playerid, "actor"), Float:axX, Float:ayY, Float:azZ, string[100];
		    GetActorPos(actor, axX, ayY, azZ);
			if(show_name == true)
			{
				if(show_id == false) Update3DTextLabelText(OP_ActorInfo[actor][Text3D], SetActorColor(actor,true), inputtext);
				else
				{
					new str[MAX_PLAYER_NAME+8];
					format(str, sizeof(str), "%s [%d]", inputtext, actor);
					Update3DTextLabelText(OP_ActorInfo[actor][Text3D], SetActorColor(actor,true), str);
				}
			}
			format(string, sizeof(string), "[{0000FF}OP_Actor{FFFFFF}] Вы сменили имя актёру. Новое имя: %s.", inputtext);
			SendClientMessage(playerid, COLOR_WHITE, string);
			format(OP_ActorInfo[actor][aName], MAX_PLAYER_NAME, inputtext);
		}
		case 14:
		{
			if(!response) return CloseDialog(playerid);
			new actor = GetPVarInt(playerid, "actor"), string[100];
			switch(listitem)
			{
			    case 0: OP_ActorInfo[actor][aColor] = 0, format(string, sizeof(string), "Вы выбрали белый цвет имени для актёра {FF0000}%d", actor), SendClientMessage(playerid, COLOR_WHITE, string);
			    case 1: OP_ActorInfo[actor][aColor] = 1, format(string, sizeof(string), "Вы выбрали {0000FF}синий цвет{FFFFFF} имени для актёра {FF0000}%d", actor), SendClientMessage(playerid, COLOR_WHITE, string);
			    case 2: OP_ActorInfo[actor][aColor] = 2, format(string, sizeof(string), "Вы выбрали {000000}чёрный цвет{FFFFFF} имени для актёра {FF0000}%d", actor), SendClientMessage(playerid, COLOR_WHITE, string);
			    case 3: OP_ActorInfo[actor][aColor] = 3, format(string, sizeof(string), "Вы выбрали {FF0000}красный цвет{FFFFFF} имени для актёра {FF0000}%d", actor), SendClientMessage(playerid, COLOR_WHITE, string);
			    case 4: OP_ActorInfo[actor][aColor] = 4, format(string, sizeof(string), "Вы выбрали {FFFF00}жёлтый цвет{FFFFFF} имени для актёра {FF0000}%d", actor), SendClientMessage(playerid, COLOR_WHITE, string);
			    case 5: OP_ActorInfo[actor][aColor] = 5, format(string, sizeof(string), "Вы выбрали {00FF00}ярко-зелёный цвет{FFFFFF} имени для актёра {FF0000}%d", actor), SendClientMessage(playerid, COLOR_WHITE, string);
			    case 6: OP_ActorInfo[actor][aColor] = 6, format(string, sizeof(string), "Вы выбрали {000066}тёмно-синий цвет{FFFFFF} имени для актёра {FF0000}%d", actor), SendClientMessage(playerid, COLOR_WHITE, string);
			    case 7: OP_ActorInfo[actor][aColor] = 7, format(string, sizeof(string), "Вы выбрали {FF66FF}розовый цвет{FFFFFF} имени для актёра {FF0000}%d", actor), SendClientMessage(playerid, COLOR_WHITE, string);
			    case 8: OP_ActorInfo[actor][aColor] = 8, format(string, sizeof(string), "Вы выбрали {009900}зелёный цвет{FFFFFF} имени для актёра {FF0000}%d", actor), SendClientMessage(playerid, COLOR_WHITE, string);
			    case 9: OP_ActorInfo[actor][aColor] = 9, format(string, sizeof(string), "Вы выбрали {00FFFF}голубой цвет{FFFFFF} имени для актёра {FF0000}%d", actor), SendClientMessage(playerid, COLOR_WHITE, string);
				case 10: OP_ActorInfo[actor][aColor] = 10, format(string, sizeof(string), "Вы выбрали {FF8C00}оранжевый цвет{FFFFFF} имени для актёра {FF0000}%d", actor), SendClientMessage(playerid, COLOR_WHITE, string);
				case 11: OP_ActorInfo[actor][aColor] = 11, format(string, sizeof(string), "Вы выбрали {006400}тёмно-зелёный цвет{FFFFFF} имени для актёра {FF0000}%d", actor), SendClientMessage(playerid, COLOR_WHITE, string);
			}
			if(show_name == true)
			{
				if(show_id == false) Update3DTextLabelText(OP_ActorInfo[actor][Text3D], SetActorColor(actor,true), inputtext);
				else
				{
					new str[MAX_PLAYER_NAME+8];
					format(str, sizeof(str), "%s [%d]", inputtext, actor);
					Update3DTextLabelText(OP_ActorInfo[actor][Text3D], SetActorColor(actor,true), str);
				}
			}
		}
		case 15:
		{
		    if(!response) return CloseDialog(playerid), Settings(playerid);
		    switch(listitem)
		    {
		        case 0:
		        {
					new opf = ini_openFile("Actors/OP_Actors_Names_M.cfg");
					if(opf < 0)
					{
					    new opfc = ini_createFile("Actors/OP_Actors_Names_M.cfg");
					    ini_setInteger(opfc, "MAXMN", 10);
						for(new i; i<Number_Names_Male; i++)
						{
						    new string[3];
						    format(string, sizeof(string), "%d", i);
						    ini_setString(opfc, string, "");
						}
						ini_closeFile(opfc);
						SetPVarInt(playerid, "polname", 0);
						ShowPlayerDialog_CheckForAC(playerid, DACT+16, DIALOG_STYLE_LIST, "Список мужских имён | Нажмите для настроек","-\n-\n-\n-\n-\n-\n-\n-\n-\n-","Далее","Назад");
					}
					else
					{
						ini_getInteger(opf, "MAXMN", Number_Names_Male);
						if(Number_Names_Male < 10) Number_Names_Male = 10, ini_setInteger(opf, "MAXMN", 10);
						new p[4], name[MAX_PLAYER_NAME], stringer[800];
						for(new i; i<Number_Names_Male; i++)
						{
							new string[50];
						    format(p, sizeof(p), "%d", i);
						    ini_getString(opf, p, name);
					    	if(!strlen(name)) format(string, 4, "-\n");
					    	else format(string, sizeof(string), "%s\n", name);
					    	strcat(stringer, string);
						}
						SetPVarInt(playerid, "polname", 0);
						ShowPlayerDialog_CheckForAC(playerid, DACT+18, DIALOG_STYLE_LIST, "Список мужских имён | Нажмите для настроек",stringer,"Далее","Назад");
					}
					ini_closeFile(opf);
		        }
		        default:
		        {
					new opf = ini_openFile("Actors/OP_Actors_Names_W.cfg");
					if(opf < 0)
					{
					    new opfc = ini_createFile("Actors/OP_Actors_Names_W.cfg");
					    ini_setInteger(opfc, "MAXWN", 10);
						for(new i; i<Number_Names_Female; i++)
						{
						    new string[3];
						    format(string, sizeof(string), "%d", i);
						    ini_setString(opfc, string, "");
						}
						ini_closeFile(opfc);
						SetPVarInt(playerid, "polname", 1);
						ShowPlayerDialog_CheckForAC(playerid, DACT+16, DIALOG_STYLE_LIST, "Список женских имён | Нажмите для настроек","-\n-\n-\n-\n-\n-\n-\n-\n-\n-", "Далее","Назад");
					}
					else
					{
						ini_getInteger(opf, "MAXWN", Number_Names_Female);
						if(Number_Names_Female < 10) Number_Names_Female = 10, ini_setInteger(opf, "MAXWN", 10);
						new p[4], name[MAX_PLAYER_NAME], stringer[800];
						for(new i; i<Number_Names_Female; i++)
						{
							new string[50];
						    format(p, sizeof(p), "%d", i);
						    ini_getString(opf, p, name);
					    	if(!strlen(name)) format(string, 4, "-\n");
					    	else format(string, sizeof(string), "%s\n", name);
					    	strcat(stringer, string);
						}
						SetPVarInt(playerid, "polname", 1);
						ShowPlayerDialog_CheckForAC(playerid, DACT+18, DIALOG_STYLE_LIST, "Список женских имён | Нажмите для настроек",stringer,"Далее","Назад");
					}
					ini_closeFile(opf);
		        }
		    }
		}
		case 16:
		{
		    if(!response) return CloseDialog(playerid), Settings(playerid);
		    switch(GetPVarInt(playerid, "polname"))
		    {
		        case 0:
				{
					for(new i; i<Number_Names_Male; i++)
					{
					    new zagol[50];
					    format(zagol, sizeof(zagol), "Номер: %d | Имя: -", i);
					    if(listitem == i) SetPVarInt(playerid, "NameStr",i), ShowPlayerDialog_CheckForAC(playerid, DACT+17, DIALOG_STYLE_INPUT, zagol, "Введите новое мужское имя","Ввести","Назад");
					}
					ShowPlayerDialog_CheckForAC(playerid, DACT+15, DIALOG_STYLE_LIST, "Список рандомных имён","Мужские имена\nЖенские имена","Далее","Назад");
				}
				default:
				{
					for(new i; i<Number_Names_Female; i++)
					{
					    new zagol[50];
					    format(zagol, sizeof(zagol), "Номер: %d | Имя: -", i);
					    if(listitem == i) SetPVarInt(playerid, "NameStr",i), ShowPlayerDialog_CheckForAC(playerid, DACT+17, DIALOG_STYLE_INPUT, zagol, "Введите новое женское имя","Ввести","Назад");
					}
					ShowPlayerDialog_CheckForAC(playerid, DACT+15, DIALOG_STYLE_LIST, "Список рандомных имён","Мужские имена\nЖенские имена","Далее","Назад");
				}
		    }
		}
		case 17:
		{
		    if(!response) return CloseDialog(playerid), Settings(playerid);
		    if(!strlen(inputtext)) return SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Вы ничего не ввели!");
		    if(strlen(inputtext) < 2 || strlen(inputtext) > 24) return SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Длина имени не может быть меньше 2-х и больше 24-х символов.");
			switch(GetPVarInt(playerid, "polname"))
			{
				case 0:
				{
					new OPFile = ini_openFile("Actors/OP_Actors_Names_M.cfg");
					if(OPFile < 0)
					{
					    new OPFileM = ini_createFile("Actors/OP_Actors_Names_M.cfg");
						ini_setInteger(OPFileM, "MAXMN", 10);
						for(new i; i<Number_Names_Male; i++)
						{
						    new string[4];
						    format(string, sizeof(string), "%d", i);
							if(i == GetPVarInt(playerid, "NameStr")) ini_setString(OPFileM, string, inputtext);
							else ini_setString(OPFileM, string, "");
							ini_closeFile(OPFileM);
						}
						ini_closeFile(OPFile);
						new string[100];
						format(string, sizeof(string), "[{0000FF}OP_Actor{FFFFFF}] Вы добавили мужское имя: %s | Строка: %d", inputtext, GetPVarInt(playerid, "NameStr"));
						SendClientMessage(playerid, COLOR_WHITE, string);
						return 0;
					}
					else
					{
					    new string[100];
						format(string, 5, "%d", GetPVarInt(playerid, "NameStr"));
						ini_setString(OPFile, string, inputtext);
						format(string, sizeof(string), "[{0000FF}OP_Actor{FFFFFF}] Вы добавили мужское имя: %s | Строка: %d", inputtext, GetPVarInt(playerid, "NameStr"));
						SendClientMessage(playerid, COLOR_WHITE, string);
						return 0;
					}
				}
				default:
				{
					new OPFile = ini_openFile("Actors/OP_Actors_Names_W.cfg");
					if(OPFile < 0)
					{
					    new OPFileM = ini_createFile("Actors/OP_Actors_Names_W.cfg");
						ini_setInteger(OPFileM, "MAXWN", 10);
						for(new i; i<Number_Names_Female; i++)
						{
						    new string[4];
						    format(string, sizeof(string), "%d", i);
							if(i == GetPVarInt(playerid, "NameStr")) ini_setString(OPFileM, string, inputtext);
							else ini_setString(OPFileM, string, "");
							ini_closeFile(OPFileM);
						}
						ini_closeFile(OPFile);
						new string[100];
						format(string, sizeof(string), "[{0000FF}OP_Actor{FFFFFF}] Вы добавили женское имя: %s | Строка: %d", inputtext, GetPVarInt(playerid, "NameStr"));
						SendClientMessage(playerid, COLOR_WHITE, string);
						return 0;
					}
					else
					{
					    new string[100];
						format(string, 5, "%d", GetPVarInt(playerid, "NameStr"));
						ini_setString(OPFile, string, inputtext);
						format(string, sizeof(string), "[{0000FF}OP_Actor{FFFFFF}] Вы добавили женское имя: %s | Строка: %d", inputtext, GetPVarInt(playerid, "NameStr"));
						SendClientMessage(playerid, COLOR_WHITE, string);
						return 0;
					}
				}
			}
      	}
		case 18:
		{
		    if(!response) return CloseDialog(playerid), Settings(playerid);
			switch(GetPVarInt(playerid, "polname"))
			{
			    case 0:
			    {
			        for(new i; i<Number_Names_Male; i++) if(listitem == i) SetPVarInt(playerid, "NameStr", i);
			    }
			    default:
			    {
			        for(new i; i<Number_Names_Female; i++) if(listitem == i) SetPVarInt(playerid, "NameStr", i);
			    }
			}
			ShowPlayerDialog_CheckForAC(playerid, DACT+19, DIALOG_STYLE_LIST, "Выберите действие","Изменить имя\nУдалить имя","Далее","Назад");
      	}
		case 19:
		{
		    if(!response) return CloseDialog(playerid), Settings(playerid);
		    switch(listitem)
		    {
				case 0: ShowPlayerDialog_CheckForAC(playerid, DACT+20, DIALOG_STYLE_INPUT, "Изменить имя","Введите новое имя","Далее","Назад");
				case 1:
				{
					switch(GetPVarInt(playerid, "polname"))
					{
					    case 0:
				    	{
							new OPFile = ini_openFile("Actors/OP_Actors_Names_M.cfg");
							if(OPFile < 0)
							{
								new OPFileM = ini_createFile("Actors/OP_Actors_Names_M.cfg");
								ini_setInteger(OPFileM, "MAXMN", 10); Number_Names_Male = 10;
								for(new i; i<Number_Names_Male;i++)
								{
								    new str[4];
								    format(str, sizeof(str), "%d", i);
								    ini_setString(OPFileM, str, "");
								}
								ini_closeFile(OPFileM);
							}
							else
							{
								new str[4];
								format(str, sizeof(str), "%d", GetPVarInt(playerid, "NameStr"));
								SendClientMessage(playerid, -1, str);
								ini_setString(OPFile, str, "");
							}
							ini_closeFile(OPFile);
					    }
						default:
						{
							new OPFile = ini_openFile("Actors/OP_Actors_Names_W.cfg");
							if(OPFile < 0)
							{
								new OPFileW = ini_createFile("Actors/OP_Actors_Names_W.cfg");
								ini_setInteger(OPFileW, "MAXWN", 10); Number_Names_Female = 10;
								for(new i; i<Number_Names_Female;i++)
								{
								    new str[4];
								    format(str, sizeof(str), "%d", i);
								    ini_setString(OPFileW, str, "");
								}
								ini_closeFile(OPFileW);
							}
							else
							{
								new str[4];
								format(str, sizeof(str), "%d", GetPVarInt(playerid, "NameStr"));
								SendClientMessage(playerid, -1, str);
								ini_setString(OPFile, str, "");
							}
							ini_closeFile(OPFile);
						}
					}
				}
			}
			Settings(playerid);
      	}
		case 20:
		{
		    if(!response) return CloseDialog(playerid), OnPlayerCommandText(playerid, "/actor");
		    if(!strlen(inputtext)) return SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Вы ничего не ввели!");
		    if(strlen(inputtext) < 2 || strlen(inputtext) > 24) return SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Имя не может быть меньше 2-х и больше 24-х символов!");
			switch(GetPVarInt(playerid, "polname"))
			{
			    case 0:
			    {
					new OPFile = ini_openFile("Actors/OP_Actors_Names_M.cfg");
					if(OPFile < 0)
					{
						new OPFileM = ini_createFile("Actors/OP_Actors_Names_M.cfg");
						ini_setInteger(OPFileM, "MAXMN", 10); Number_Names_Male = 10;
						for(new i; i<Number_Names_Male;i++)
						{
						    new str[4];
						    format(str, sizeof(str), "%d", i);
						    if(GetPVarInt(playerid, "NameStr") == i) ini_setString(OPFileM, str, inputtext);
						    else ini_setString(OPFileM, str, "");
						}
						ini_closeFile(OPFileM);
					}
					else
					{
						new str[4];
						format(str, sizeof(str), "%d", GetPVarInt(playerid, "NameStr"));
						ini_setString(OPFile, str, inputtext);
					}
					ini_closeFile(OPFile);
					new stringer[150];
					format(stringer, sizeof(stringer), "[{0000FF}OP_Actor{FFFFFF}] Вы успешно изменили мужское имя номер %d. Новое имя: %s", GetPVarInt(playerid, "NameStr"), inputtext);
					SendClientMessage(playerid, COLOR_WHITE, stringer);
					return 0;
			    }
			    default:
			    {
					new OPFile = ini_openFile("Actors/OP_Actors_Names_W.cfg");
					if(OPFile < 0)
					{
						new OPFileW = ini_createFile("Actors/OP_Actors_Names_W.cfg");
						ini_setInteger(OPFileW, "MAXWN", 10); Number_Names_Female = 10;
						for(new i; i<Number_Names_Female;i++)
						{
						    new str[4];
						    format(str, sizeof(str), "%d", i);
						    if(GetPVarInt(playerid, "NameStr") == i) ini_setString(OPFileW, str, inputtext);
						    else ini_setString(OPFileW, str, "");
						}
						ini_closeFile(OPFileW);
					}
					else
					{
						new str[4];
						format(str, sizeof(str), "%d", GetPVarInt(playerid, "NameStr"));
						ini_setString(OPFile, str, inputtext);
					}
					ini_closeFile(OPFile);
					new stringer[150];
					format(stringer, sizeof(stringer), "[{0000FF}OP_Actor{FFFFFF}] Вы успешно изменили женское имя номер %d. Новое имя: %s", GetPVarInt(playerid, "NameStr"), inputtext);
					SendClientMessage(playerid, COLOR_WHITE, stringer);
					return 0;
			    }
			}
   		}
		case 21:
		{
		    if(!response) return CloseDialog(playerid), Settings(playerid);
			if(!strlen(inputtext)) return ShowPlayerDialog_CheckForAC(playerid, DACT+21, DIALOG_STYLE_INPUT, "Изменение количества имён","{FFFFFF}Вы хотите изменить количество имён.\nКоличество может быть ТОЛЬКО больше 10.\n\nВведите максимальное количество имён!", "Далее","Назад");
			if(strval(inputtext) < 10) return ShowPlayerDialog_CheckForAC(playerid, DACT+21, DIALOG_STYLE_INPUT, "Изменение количества имён","{FFFFFF}Вы хотите изменить количество имён.\n{FF0000}Количество может быть ТОЛЬКО больше 10.\n\n{FFFFFF}Введите максимальное количество имён!", "Далее","Назад");
			if(GetPVarInt(playerid, "DACT+21") == 1 || GetPVarInt(playerid, "DACT+21") == 3) Number_Names_Male = strval(inputtext);
			if(GetPVarInt(playerid, "DACT+21") == 2 || GetPVarInt(playerid, "DACT+21") == 3) Number_Names_Female = strval(inputtext);
			if(GetPVarInt(playerid, "DACT+21") == 1 || GetPVarInt(playerid, "DACT+21") == 3)
			{
				new OPFile = ini_openFile("Actors/OP_Actors_Names_M.cfg");
				if(OPFile < 0)
				{
					new OPFileW = ini_createFile("Actors/OP_Actors_Names_M.cfg");
					ini_setInteger(OPFileW, "MAXMN", strval(inputtext));
					for(new i; i<Number_Names_Male;i++)
					{
					    new str[4];
					    format(str, sizeof(str), "%d", i);
					    if(GetPVarInt(playerid, "NameStr") == i) ini_setString(OPFileW, str, inputtext);
					    else ini_setString(OPFileW, str, "");
					}
					ini_closeFile(OPFileW);
				}
				else ini_setInteger(OPFile, "MAXMN", strval(inputtext)), ini_closeFile(OPFile);
			}
			if(GetPVarInt(playerid, "DACT+21") == 2 || GetPVarInt(playerid, "DACT+21") == 3)
			{
				new OPFile = ini_openFile("Actors/OP_Actors_Names_W.cfg");
				if(OPFile < 0)
				{
					new OPFileW = ini_createFile("Actors/OP_Actors_Names_W.cfg");
					ini_setInteger(OPFileW, "MAXWN", strval(inputtext));
					for(new i; i<Number_Names_Female;i++)
					{
					    new str[4];
					    format(str, sizeof(str), "%d", i);
					    if(GetPVarInt(playerid, "NameStr") == i) ini_setString(OPFileW, str, inputtext);
					    else ini_setString(OPFileW, str, "");
					}
					ini_closeFile(OPFileW);
				}
				else ini_setInteger(OPFile, "MAXWN", strval(inputtext)), ini_closeFile(OPFile);
			}
			
			new string[150];
			format(string, sizeof string, "[{0000FF}OP_Actor{FFFFFF}] Вы изменили количество %s имён на {0000FF}%d", (GetPVarInt(playerid, "DACT+21") == 1) ? ("мужских") : ((GetPVarInt(playerid, "DACT+21") == 2) ? ("женских") : ("мужских и женских")), strval(inputtext));
			SendClientMessage(playerid, COLOR_WHITE, string);
			DeletePVar(playerid, "DACT+21");
			Settings(playerid);
   		}
		case 22:
		{
		    if(!response) return CloseDialog(playerid), OnPlayerCommandText(playerid, "/actor");
			switch(listitem)
			{
				case 0: ShowPlayerDialog_CheckForAC(playerid, DACT+15, DIALOG_STYLE_LIST, "Список рандомных имён","Мужские имена\nЖенские имена","Далее","Назад");
				case 1: ShowPlayerDialog_CheckForAC(playerid, DACT+23, DIALOG_STYLE_LIST, "Изменение количества имён","Изменить количество мужских имён\nИзменить количество женских имён\nИзменить количество мужских и женских имён", "Далее","Назад");
				case 2:
				{
					if(show_name == true) show_name = false;
					else show_name = true;
					Settings(playerid);
				}
				case 3:
				{
					if(show_id == true) show_id = false;
					else show_id = true;
					Settings(playerid);
				}
			}
   		}
   		case 23:
   		{
   		    if(!response) return CloseDialog(playerid), Settings(playerid);
   		    switch(listitem)
   		    {
   		        case 0: SetPVarInt(playerid, "DACT+21", 1), ShowPlayerDialog_CheckForAC(playerid, DACT+21, DIALOG_STYLE_INPUT, "Изменение количества имён","Вы хотите изменить количество мужских имён.\nКоличество может быть ТОЛЬКО больше 10.\n\nВведите максимальное количество имён!", "Далее","Назад");
   		        case 1: SetPVarInt(playerid, "DACT+21", 2), ShowPlayerDialog_CheckForAC(playerid, DACT+21, DIALOG_STYLE_INPUT, "Изменение количества имён","Вы хотите изменить количество женских имён.\nКоличество может быть ТОЛЬКО больше 10.\n\nВведите максимальное количество имён!", "Далее","Назад");
   		        case 2: SetPVarInt(playerid, "DACT+21", 3), ShowPlayerDialog_CheckForAC(playerid, DACT+21, DIALOG_STYLE_INPUT, "Изменение количества имён","Вы хотите изменить количество имён.\nКоличество может быть ТОЛЬКО больше 10.\n\nВведите максимальное количество имён!", "Далее","Назад");
   		    }
   		}
		case 25:
		{
		    if(!response) return CloseDialog(playerid), OnPlayerCommandText(playerid, "/actor");
		    if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Нельзя использовать в машине!");
		    switch(listitem)
		    {
		    	case 0:
				{
					SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Встаньте с таким углом поворота, с каким вы хотите видеть актёра!");
					SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] После того как Вы встали под таким углом - нажмите 'c' (по умолчанию - присесть)!");
				}
				case 1:
				{
					SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Встаньте на то место, куда нужно переместить актёра!");
					SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] После того как Вы встали на то место - нажмите 'c' (по умолчанию - присесть)!");
				}
				case 2:
				{
					SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Встаньте на то место, куда нужно переместить актёра!");
					SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Выберите новый угол поворота актёра!");
					SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Для сохранения положения актёра - нажмите 'c' (по умолчанию - присесть)!");
				}
			}
			SetPVarInt(playerid, "vbor", listitem+1);
   		}
		case 26:
		{
	        if(!response) return CloseDialog(playerid);
		  	new string[100];
	        for(new i = 0; i <= Max_ActorID; i++)
	        {
	            if(listitem == i)
	            {
					SetPVarInt(playerid, "actor", i);
	                format(string, sizeof(string), "Актёр номер {FF0000}%d{FFFFFF} | Имя: {FF0000}%s", i, OP_ActorInfo[i][aName]);
	            }
	        }
			ShowPlayerDialog_CheckForAC(playerid, DACT+2, DIALOG_STYLE_LIST, string, "Телепорт к актёру\nИзменить скин актёру\nУдалить актёра\nПереместить/Повернуть актёра\nИзменить вирт.мир актёра\nДобавить анимацию актёру\nИзменить имя актёру\nИзменить цвет имени", "Далее", "Назад");
   		}
	}
	return 0;
}
//forward LoadActorAnim(actor);
//public LoadActorAnim(actor)
stock LoadActorAnim(actor)
{
	ApplyActorAnimation(actor, "DANCING", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyActorAnimation(actor, "BAR", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyActorAnimation(actor, "BEACH", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyActorAnimation(actor, "CAMERA", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyActorAnimation(actor, "DANCING", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyActorAnimation(actor, "CAMERA", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyActorAnimation(actor, "ped", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyActorAnimation(actor, "BOMBER", "null", 0.0, 0, 0, 0, 0, 0);
	ApplyActorAnimation(actor, "BUDDY", "null", 0.0, 0, 0, 0, 0, 0);
	return 1;
}
//public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
//stock OP_actor_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
stock OP_actor_OnPlayerKeyStateChange(playerid)
{//newkeys == KEY_CROUCH &&
    if(GetPVarInt(playerid, "vbor") > 0)
    {
        if(IsPlayerInAnyVehicle(playerid)) return DeletePVar(playerid, "vbor") && DeletePVar(playerid, "actor") && SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Нельзя использовать в машине!");
        new actor = GetPVarInt(playerid, "actor");
        new Float:fx, Float:fy, Float:fz, Float:fa;
		GetPlayerPos(playerid, fx, fy, fz);
		GetPlayerFacingAngle(playerid, fa);
		DestroyActor(actor);
		switch(GetPVarInt(playerid, "vbor"))
		{
			case 1:
			{
				CreateActor(OP_ActorInfo[actor][aSkin], OP_ActorInfo[actor][aPosX], OP_ActorInfo[actor][aPosY], OP_ActorInfo[actor][aPosZ], fa);
				OP_ActorInfo[actor][aPosA] = fa;
		        SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Вы успешно повернули актёра!");
			}
			case 2:
			{
				SetPlayerPos(playerid, fx, fy+1, fz);
				CreateActor(OP_ActorInfo[actor][aSkin], fx, fy, fz, OP_ActorInfo[actor][aPosA]);
				OP_ActorInfo[actor][aPosX] = fx;
				OP_ActorInfo[actor][aPosY] = fy;
				OP_ActorInfo[actor][aPosZ] = fz;
				if(show_name == true)
				{
					Delete3DTextLabel(OP_ActorInfo[actor][Text3D]);
					if(show_id == false) OP_ActorInfo[actor][Text3D] = Create3DTextLabel(OP_ActorInfo[actor][aName], SetActorColor(actor,true), OP_ActorInfo[actor][aPosX], OP_ActorInfo[actor][aPosY], OP_ActorInfo[actor][aPosZ]+1.1, 15.0, OP_ActorInfo[actor][aVirt], 1);
					else
					{
						new str[MAX_PLAYER_NAME+8];
						format(str, sizeof(str), "%s [%d]", OP_ActorInfo[actor][aName], actor);
						OP_ActorInfo[actor][Text3D] = Create3DTextLabel(str, SetActorColor(actor,true), OP_ActorInfo[actor][aPosX], OP_ActorInfo[actor][aPosY], OP_ActorInfo[actor][aPosZ]+1.1, 15.0, OP_ActorInfo[actor][aVirt], 1);
					}
				}
		        SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Вы успешно переместили актёра!");
			}
			case 3:
			{
				SetPlayerPos(playerid, fx, fy+1, fz);
				CreateActor(OP_ActorInfo[actor][aSkin], fx, fy, fz, fa);
				OP_ActorInfo[actor][aPosX] = fx;
				OP_ActorInfo[actor][aPosY] = fy;
				OP_ActorInfo[actor][aPosZ] = fz;
				OP_ActorInfo[actor][aPosA] = fa;
				if(show_name == true)
				{
					Delete3DTextLabel(OP_ActorInfo[actor][Text3D]);
					if(show_id == false) OP_ActorInfo[actor][Text3D] = Create3DTextLabel(OP_ActorInfo[actor][aName], SetActorColor(actor,true), OP_ActorInfo[actor][aPosX], OP_ActorInfo[actor][aPosY], OP_ActorInfo[actor][aPosZ]+1.1, 15.0, OP_ActorInfo[actor][aVirt], 1);
					else
					{
						new str[MAX_PLAYER_NAME+8];
						format(str, sizeof(str), "%s [%d]", OP_ActorInfo[actor][aName], actor);
						OP_ActorInfo[actor][Text3D] = Create3DTextLabel(str, SetActorColor(actor,true), OP_ActorInfo[actor][aPosX], OP_ActorInfo[actor][aPosY], OP_ActorInfo[actor][aPosZ]+1.1, 15.0, OP_ActorInfo[actor][aVirt], 1);
					}
				}
		        SendClientMessage(playerid, COLOR_WHITE, "[{0000FF}OP_Actor{FFFFFF}] Вы успешно переместили и повернули актёра!");
			}
		}
		LoadActorAnim(actor);
		SetActorVirtualWorld(actor, OP_ActorInfo[actor][aVirt]);
		DeletePVar(playerid, "actor");
		DeletePVar(playerid, "vbor");
	}
	return 1;
}
//public OnRconLoginAttempt(ip[], password[], success)
stock OP_actor_OnRconLoginAttempt(ip[], password[], success)
{
	#pragma unused password
    if(success)
    {
		for(new i; i<MAX_PLAYERS; i++)
		{
			new gip[16];
			GetPlayerIp(i, gip, 16);
			if(!strcmp(ip, gip, true))
			{
				SendClientMessage(i, COLOR_WHITE, "Система актёров v10.0 успешно загружена и работает. Для вызова меню введите {FF0000}/actor");
				if(Max_ActorID >= 0)
				{
					new string[30];
					format(string, sizeof(string), "Загружено актёров: {0000FF}%d", Max_ActorID+1);
					SendClientMessage(i, COLOR_WHITE, string);
				}
			}
		}
    }
	return 0;
}
//public OnPlayerCommandText(playerid, cmdtext[])
stock OP_actor_OnPlayerCommandText(playerid, cmdtext[])
{
	if(!strcmp(cmdtext, "/actor", true))
	{
		if(!IsPlayerAdmin(playerid)) return 1;
		ShowPlayerDialog_CheckForAC(playerid, DACT, DIALOG_STYLE_LIST, "Актёры от Oleg_Petrow","Создать нового актёра\nПросмотр списка актёров\nУдалить всех актёров\nСохранить всех актёров\nНастройки","Далее","Выход");
		return 1;
	}
	return 0;
}

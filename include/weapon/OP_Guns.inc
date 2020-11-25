/*===================[FS] Система выброса оружия v2.0===========================
_____________ При публикации просьба указывать автора Oleg_Petrow ______________

  +==========+ +==========+ +==========+ +==========+    +======+  +==+      +==+     +==+
  ||        || ||                ||      ||        ||  //       \\  \  \     |  |    /  /
  ||        || ||                ||      ||        || ||         ||  \  \    |  |   /  /
  ||=========+ |+========+       ||      ||=\\======+ ||         ||   \  \   |  |  /  /
  ||           ||                ||      ||   \\      ||         ||    \  \  |  | /  /
  ||           ||                ||      ||     \\     \\       //      \  \/   \/  /
  ||           |+=========+      ||      ||       \\    +======+         \_________/


	Обновление в версии 1.1:
	- Подправлены мелкие недочёты
	
	Обновления в версии 2.0:
	- Исправлен баг, что если на сервере лежит более 150 оружий - больше нельзя класть.
	- Увеличен лимит оружий до 200 (страшно за лимит объектов и лимит 3DText'ов)
	- Теперь, если Вы выбросили оружие, а на сервере уже лежит максимальное кол-во оружий,
		то самое старое оружие удаляется. На его месте появляется новое.
	- Удалена команда /gun (выдавались M4 и Deagle, делал для теста скрипта, забыл убрать).
	- Для RCON администрации добавлена команда /op_guns (настройки скрипта)
	- Для удобства в совместимости с модом - создан макрос DIALOG_GUNS, отвечающий за ID диалога.
	- Теперь над головой персонажа и самому ему пишется текст, что он поднял оружие.

	
																																		*/
main() {}
#include a_samp

#define MAX_GUN_DROP 200
#define DIALOG_GUNS  9000

new bool:op_scr=true;
new const GunObjects[47] = {0,331,333,334,335,336,337,338,339,341,321,322,323,324,325,326,342,343,344,0,0,0,346,347,348,349,350,351,352,353,355,356,372,357,358,359,360,361,362,363,364,365,366,367,368,368,371};
enum gun_drop
{
	bool:ob_Yes,
	Float:Ob_Pos[3],
	obI_jD,
	Ob_Dta[2],
	Text3D:LabelGun,
	ob_time
};
new g_info[MAX_GUN_DROP][gun_drop];

public OnFilterScriptInit()
{
	print("+----------------------------------------------------+");
	print("|        Скрипт от Oleg_Petrow успешно загружен      |");
	print("|    Скриптинг от Oleg_Petrow: vk.com/op_scripts     |");
	print("|          Oleg_Petrow в ВК: vk.com/flomkas          |");
	print("| Oleg_Petrow в ВК (вторая страница): vk.com/flomkas |");
	print("|          Система выброса оружий | Версия: 2.0      |");
	print("|____________________________________________________|");
	op_scr = true;
	for(new a = 0; a < MAX_GUN_DROP; a++)
	{
		DestroyObject(g_info[a][obI_jD]);
		g_info[a][Ob_Dta][1] = 0;
		g_info[a][Ob_Pos][0] = 0.0;
		g_info[a][Ob_Pos][1] = 0.0;
		g_info[a][Ob_Pos][2] = 0.0;
		g_info[a][ob_Yes] = false;
		g_info[a][ob_time] = 0;
		g_info[a][obI_jD] = -1;
		Delete3DTextLabel(g_info[a][LabelGun]);
		g_info[a][Ob_Dta][0] = 0;
	}
	return 1;
}

public OnFilterScriptExit()
{
	for(new a = 0; a < MAX_GUN_DROP; a++)
	{
		DestroyObject(g_info[a][obI_jD]);
		g_info[a][Ob_Dta][1] = 0;
		g_info[a][Ob_Pos][0] = 0.0;
		g_info[a][Ob_Pos][1] = 0.0;
		g_info[a][Ob_Pos][2] = 0.0;
		g_info[a][ob_Yes] = false;
		g_info[a][ob_time] = 0;
		g_info[a][obI_jD] = -1;
		Delete3DTextLabel(g_info[a][LabelGun]);
		g_info[a][Ob_Dta][0] = 0;
	}
	return 1;
}

new const nameGun[47][] =
{
	"Кастет", "Гольф клюшка", "Дубинка", "Нож", "Бита", "Лопата",	"Кий", "Катана", "Katana", "Бензо пила", "Фалоэмитатор", "Фалоэмитатор",	"Фалоэмитатор", "Вибратор", "Цветы", "Трость", "Взрывная граната", "Дымовая граната", "Коктель молотова","Error","Error","Error",
	"9mm", "Пистолет с глушителем", "Дигл", "Дробовик", "Обрез", "Дробовик", "Микро узи", "MP5", "AK-47", "M4", "Узи",	"Рифл", "Снайперская винтовка", "Гранатомёт", "Гранатом", "Огнемёт", "Восьмистволка",	"Липкая бомба", "Детонатор", "Спрей", "Огнетушитель", "Фотоаппарат", "Очки ночного виденья",
	"Очки ночного виденья", "Парашют"
};
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys == KEY_YES)
	{
		if(GetPlayerWeapon(playerid) != 0 && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && op_scr == true)
		{
			if(!IsPlayerConnected(playerid)) return 1;
			new GunIDEx = GetPlayerWeapon(playerid);
			new GunAmmoEx = GetPlayerAmmo(playerid);
			new msgs[200],Name[MAX_PLAYER_NAME]; GetPlayerName(playerid, Name, sizeof(Name));
			if(GunIDEx > 0 && GunAmmoEx != 0)
			{
				new f = MAX_GUN_DROP+1;
				for(new a; a < MAX_GUN_DROP; a++)
				{
					if(g_info[a][ob_Yes] == false)
					{
						f = a;
						break;
					}
				}
				if(f == MAX_GUN_DROP+1)
				{
				    f = 0;
				    new timeCr = g_info[0][ob_time];
				    for(new a=1; a < MAX_GUN_DROP; a++)
				    {
				        if(timeCr > g_info[a][ob_time])
				        {
				            timeCr = g_info[a][ob_time];
							f = a;
				        }
				    }
					DestroyObject(g_info[f][obI_jD]);
					g_info[f][Ob_Dta][1] = 0;
					g_info[f][Ob_Pos][0] = 0.0;
					g_info[f][Ob_Pos][1] = 0.0;
					g_info[f][Ob_Pos][2] = 0.0;
					g_info[f][ob_Yes] = false;
					g_info[f][ob_time] = 0;
					g_info[f][obI_jD] = -1;
					Delete3DTextLabel(g_info[f][LabelGun]);
					g_info[f][Ob_Dta][0] = 0;
				}
				g_info[f][ob_Yes] = true;
				RemovePlayerWeapon(playerid, GunIDEx);
				g_info[f][Ob_Dta][0] = GunIDEx;
				g_info[f][Ob_Dta][1] = GunAmmoEx;
				g_info[f][ob_time] = GetTickCount();
				GetPlayerPos(playerid, g_info[f][Ob_Pos][0], g_info[f][Ob_Pos][1], g_info[f][Ob_Pos][2]);
				g_info[f][obI_jD] = CreateObject(GunObjects[GunIDEx], g_info[f][Ob_Pos][0], g_info[f][Ob_Pos][1], g_info[f][Ob_Pos][2]-1, 93.7, 120.0, 120.0);
				format(msgs, 200, "{FFFFFF}Оружие: {FF6F00}%s\n{FFFFFF}Выбросил: {FF6F00}%s\nПоднять: {FF6F00}N",nameGun[g_info[f][Ob_Dta][0]], Name);
				g_info[f][LabelGun] = Create3DTextLabel(msgs, 0x317CDFFF, g_info[f][Ob_Pos][0], g_info[f][Ob_Pos][1], g_info[f][Ob_Pos][2], 10.0,GetPlayerVirtualWorld(playerid));
				format(msgs, 60, "Вы выбросили {FF6F00}%s", nameGun[g_info[f][Ob_Dta][0]]);
				SendClientMessage(playerid, -1, msgs);
				GetPlayerName(playerid, Name, MAX_PLAYER_NAME);
				format(msgs,100,"%s положил оружие на землю",Name);
				ProxDetector(13.0, playerid, msgs, 0xDD90FFFF,0xDD90FFFF,0xDD90FFFF,0xDD90FFFF,0xDD90FFFF);
			}
		}
	}
	else if(newkeys == KEY_NO)
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && op_scr == true)
		{
			for(new a = 0; a < MAX_GUN_DROP; a++)
			{
				if(IsPlayerInRangeOfPoint(playerid, 1.5, g_info[a][Ob_Pos][0], g_info[a][Ob_Pos][1], g_info[a][Ob_Pos][2]))
				{
					DestroyObject(g_info[a][obI_jD]);
					GivePlayerWeapon(playerid, g_info[a][Ob_Dta][0], g_info[a][Ob_Dta][1]);
					g_info[a][Ob_Dta][1] = 0;
					g_info[a][Ob_Pos][0] = 0.0;
					g_info[a][Ob_Pos][1] = 0.0;
					g_info[a][Ob_Pos][2] = 0.0;
					g_info[a][ob_Yes] = false;
					g_info[a][ob_time] = 0;
					g_info[a][obI_jD] = -1;
					Delete3DTextLabel(g_info[a][LabelGun]);
					new msgs[100],Name[MAX_PLAYER_NAME];
					format(msgs, 60, "Вы подобрали {FF6F00}%s", nameGun[g_info[a][Ob_Dta][0]]);
					SendClientMessage(playerid, -1, msgs);
					g_info[a][Ob_Dta][0] = 0;
					GetPlayerName(playerid, Name, MAX_PLAYER_NAME);
					format(msgs,sizeof(msgs),"%s подобрал оружие с земли",Name);
					ProxDetector(13.0, playerid, msgs, 0xDD90FFFF,0xDD90FFFF,0xDD90FFFF,0xDD90FFFF,0xDD90FFFF);
				}
			}
		}
	}
	return 1;
}
stock ProxDetector(Float:radius = 30.0, playerid, text[], col1 = 0xFFFFFFFF, col2 = 0xCCCCCCFF, col3 = 0x999999FF, col4 = 0x666666FF, col5 = 0x333333FF)
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	new Float:dist, virtualworld = GetPlayerVirtualWorld(playerid), interior = GetPlayerInterior(playerid);
	for(new i; i < MAX_PLAYERS; i++)
	{
		if(virtualworld != GetPlayerVirtualWorld(i) || interior != GetPlayerInterior(i)) continue;
		dist = GetPlayerDistanceFromPoint(i, x, y, z);
		if(dist < radius / 16) SendClientMessage(i, col1, text);
		else if(dist < radius / 8) SendClientMessage(i, col2, text);
		else if(dist < radius / 4) SendClientMessage(i, col3, text);
		else if(dist < radius / 2) SendClientMessage(i, col4, text);
		else if(dist < radius) SendClientMessage(i, col5, text);
	}
	return 1;
}
stock RemovePlayerWeapon(playerid, weaponid)
{
	if(!IsPlayerConnected(playerid) || weaponid < 0 || weaponid > 50) return;
	new saveweapon[13], saveammo[13];
	for(new slot = 0; slot < 13; slot++) GetPlayerWeaponData(playerid, slot, saveweapon[slot], saveammo[slot]);
	ResetPlayerWeapons(playerid);
	for(new slot; slot < 13; slot++)
	{
		if(saveweapon[slot] == weaponid || saveammo[slot] == 0) continue;
		GivePlayerWeapon(playerid, saveweapon[slot], saveammo[slot]);
	}
	GivePlayerWeapon(playerid, 0, 1);
}
public OnPlayerCommandText(playerid, cmdtext[])
{
	if(!strcmp(cmdtext, "/op_guns", true))
	{
	   	if(!IsPlayerAdmin(playerid)) return 1;
		new string[150];
		format(string, sizeof(string), "Удаление всех оружий\n{FF0000}%s скрипта", (op_scr)?("Отключение"):("Включение"));
	    ShowPlayerDialog(playerid, DIALOG_GUNS, DIALOG_STYLE_LIST, "Настройки {0000FF}OP_Guns", string, "Далее", "Отмена");
		return 1;
	}
	return 0;
}
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
	    case DIALOG_GUNS:
	    {
	        if(!IsPlayerAdmin(playerid)) return 1;
	        if(!response) return 1;
			switch(listitem)
			{
				case 0:
				{
					for(new a = 0; a < MAX_GUN_DROP; a++)
					{
						DestroyObject(g_info[a][obI_jD]);
						g_info[a][Ob_Dta][1] = 0;
						g_info[a][Ob_Pos][0] = 0.0;
						g_info[a][Ob_Pos][1] = 0.0;
						g_info[a][Ob_Pos][2] = 0.0;
						g_info[a][ob_Yes] = false;
						g_info[a][ob_time] = 0;
						g_info[a][obI_jD] = -1;
						Delete3DTextLabel(g_info[a][LabelGun]);
						g_info[a][Ob_Dta][0] = 0;
					}
					SendClientMessage(playerid, 0xFF6F00FF, "Вы удалили все оружия, лежащие на земле!");
					OnPlayerCommandText(playerid, "/op_guns");
					return 1;
				}
				case 1:
				{
				    new str[100],str1[150];
				    format(str, sizeof(str), "Временное %s скрипта", (op_scr)?("Отключение"):("Включение"));
				    format(str1, sizeof(str1), "Вы действительно хотите временно %s скрипт?\n\nСкрипт можно будет включить, введя команду /op_guns и выбрав соответствующий пункт!", (op_scr)?("отключить"):("включить"));
				    ShowPlayerDialog(playerid, DIALOG_GUNS+1, DIALOG_STYLE_MSGBOX, str, str1, "Да", "Назад");
					return 1;
				}
			}
	    }
	    case DIALOG_GUNS+1:
	    {
	        if(!IsPlayerAdmin(playerid)) return 1;
	        if(!response) return OnPlayerCommandText(playerid, "/op_guns");
			if(op_scr == true)
			{
				for(new a = 0; a < MAX_GUN_DROP; a++)
				{
					DestroyObject(g_info[a][obI_jD]);
					g_info[a][Ob_Dta][1] = 0;
					g_info[a][Ob_Pos][0] = 0.0;
					g_info[a][Ob_Pos][1] = 0.0;
					g_info[a][Ob_Pos][2] = 0.0;
					g_info[a][ob_Yes] = false;
					g_info[a][ob_time] = 0;
					g_info[a][obI_jD] = -1;
					Delete3DTextLabel(g_info[a][LabelGun]);
					g_info[a][Ob_Dta][0] = 0;
				}
				op_scr = false;
				SendClientMessage(playerid, -1, "Вы временно отключили скрипт. Включение - /op_guns");
				return 1;
			}
			else op_scr = true, SendClientMessage(playerid, -1, "Вы включили скрипт. Включение - /op_guns");
	        return 1;
	    }
	}
	return 1;
}

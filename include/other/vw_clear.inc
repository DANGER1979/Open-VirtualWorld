
stock UnloadContent() // by O.K.StyleЩ
{
// Objects
// * Global
    new testobj = CreateObject(971, 0.0,0.0,0.0, 0.0,0.0,0.0); // создаЄм тестовый объект, получаем пор€дковый id последнего объекта(а вдруг не последнего?)
    DestroyObject(testobj); // удал€ем тестовый объект
    for(new i; i < testobj; i++) // и тут уже вместо MAX_OBJECTS используем этот ID
    {
        if(!IsValidObjectEx(i)) continue; // мы ускорили перебор циклом за счЄт проверки на наличие объекта на сервере
        DestroyObject(i);
    }
    /*for(new i; i < MAX_OBJECTS; i++) // и тут уже вместо MAX_OBJECTS используем этот ID
    {
        if(!IsValidObjectEx(i)) continue; // мы ускорили перебор циклом за счЄт проверки на наличие объекта на сервере
        DestroyObject(i);
    }*/
// * Personal
    for(new i, j = GetMaxPlayers(); i != j; i++)
    {
        if(!IsPlayerConnected(i)) continue;
        new pobj = CreatePlayerObject(i, 971, 0.0,0.0,0.0, 0.0,0.0,0.0); // внесЄм в цикл, т.к. дл€ разных игроков может быть разное кол-во объектов
        DestroyPlayerObject(i, pobj);
        for(new k; k < pobj; k++)
        {
            if(!IsValidPlayerObject(i, k)) continue;
            DestroyPlayerObject(i, k);
        }
    }
// * Attach
	for(new i; i < GetMaxPlayers(); i++)
    {
    	if(!IsPlayerConnected(i)) continue;
    	for(new j; j < MAX_PLAYER_ATTACHED_OBJECTS; j++)
    	{
	    	if(!IsPlayerAttachedObjectSlotUsed(i, j)) continue;
			RemovePlayerAttachedObject(i, j);
		}
    }
    
// Pickups
    new tpickup = CreatePickup(1242, 23, 0.0, 0.0, 0.0, -1);
    DestroyPickup(tpickup);
    for(new i; i < tpickup; i++)
    {
        DestroyPickup(i);
    }

// 3D Labels
// * Dynamic
    /*new Text3D: tthreed = CreateDynamic3DTextLabel("UNLOAD", 0x00000000, 0.0,0.0,0.0, 0.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, testlos = 0);
    DestroyDynamic3DTextLabel(tthreed);
    for(new Text3D: i; i < tthreed; i++)
    {
        DestroyDynamic3DTextLabel(i);
    }*/

// 3D Labels
// * Global
    new Text3D: tthreed = Create3DTextLabel("UNLOAD", 0x00000000, 0.0, 0.0, 0.0, 0.0, 0, 0);
    Delete3DTextLabel(tthreed);
    for(new Text3D: i; i < tthreed; i++)
    {
        Delete3DTextLabel(i);
        DestroyDynamic3DTextLabel(i);
    }
// * Personal
    /*for(new i, j = GetMaxPlayers(); i != j; i++)
    {
        if(!IsPlayerConnected(i)) continue;
        new PlayerText3D: ptthreed = CreatePlayer3DTextLabel(i, "UNLOAD", 0x00000000, 0.0, 0.0, 0.0, 0.0, 0, 0);
        DeletePlayer3DTextLabel(i, ptthreed);
        for(new PlayerText3D: k; k < ptthreed; k++)
        {
            DeletePlayer3DTextLabel(i, k);
        }
    }*/
    
// Gangzones
    new gangzone = GangZoneCreate(0.0, 0.0, 0.0, 0.0);
    GangZoneDestroy(gangzone);
    for(new i; i < gangzone; i++)
    {
        GangZoneHideForAll(i);
        GangZoneDestroy(i);
    }

// * Personal
    /*for(new i; i < GetMaxPlayers(); i++)
    {
        if(!IsPlayerConnected(i)) continue;
        PTD[i] = CreatePlayerTextDraw(i, -10.0, -10.0, " ");
        PlayerTextDrawDestroy(i, PTD[i]);
        for(new PlayerText: k; k < PTD[i]; k++)
        {
			PlayerTextDrawHide(i, k);
			PlayerTextDrawDestroy(i, k); TEXT_DRAWS_COUNTER --;
        }
    }
// Textdraws
    new Text: TD = TextDrawCreateEx(-10.0, -10.0, " ");
    TextDrawDestroyEx(TD);
    for(new Text: k; k < TD; k++)
    {
        TextDrawHideForAll(k);
        TextDrawDestroyEx(k);
    }*/

// Menus
    new Menu:examplemenu = CreateMenu("UNLOAD", 2, 0.0, 0.0, 0.0, 0.0);
    DestroyMenu(examplemenu);
    for(new Menu: k; k < examplemenu; k++)
    {
        if(!IsValidMenu(k)) continue;
        for(new i, j = GetMaxPlayers(); i != j; i++)
        {
            if(!IsPlayerConnected(i)) continue;
            if(!GetPlayerMenu(i)) continue;
            HideMenuForPlayer(k, i);
        }
        DestroyMenu(k);
    }
// Vehicles
    new tveh = CreateVehicle(400, 0.0, 0.0, 0.0, 0.0, -1, -1, -1);
   	gVehicleSpawn[tveh] = 1;
    DestroyVehicle(tveh);
    for(new i; i < tveh; i++)
    {
        //if(GetVehicleModel(i) == 0) continue; // модель неопределена, значит машины нет
        if(IsValidVehicle(i) == 0) continue;
        DestroyVehicle(i);
    }

 	//SendClientMessageToAll(COLOR_RESTARTING, "UnloadContent");
	print("UnloadContent завершено");
    //return 1;
}



stock ClearMarriage(playerid)
{
    new strtmp[16];//MAX_PLAYER_NAME
	format(strtmp, sizeof(strtmp), "BeSingle");
	strmid(PlayerInfo[playerid][pMarriedTo], strtmp, 0, strlen(strtmp), 24);
	PlayerInfo[playerid][pMarried] = 0;
}





//----------------------------------------------------------
//
// GRAND LARCENY common functions include.
//
//----------------------------------------------------------
new NPCCar[16];
stock IsInNPCVehicle(vehicleid)
{
	if(	vehicleid>=NPCCar[0] && vehicleid<=sizeof(NPCCar)) return 1;
	return 0;
}

new npc_veh;
stock LoadStaticVehiclesFromFile(const filename[])
{
	new File:file_ptr;
	new line[256];
	new var_from_line[64];
	new vehicletype;
	new Float:SpawnX;
	new Float:SpawnY;
	new Float:SpawnZ;
	new Float:SpawnRot;
    new Color1, Color2;
	new index;
	new vehicles_loaded;

	file_ptr = fopen(filename,filemode:io_read);
	if(!file_ptr) return 0;

	vehicles_loaded = 0;

	while(fread(file_ptr,line,256) > 0)
	{
	    index = 0;

	    // Read type
  		index = token_by_delim(line,var_from_line,',',index);
  		if(index == (-1)) continue;
  		vehicletype = strval(var_from_line);
   		if(vehicletype < 400 || vehicletype > 611) continue;

  		// Read X, Y, Z, Rotation
  		index = token_by_delim(line,var_from_line,',',index+1);
  		if(index == (-1)) continue;
  		SpawnX = floatstr(var_from_line);

  		index = token_by_delim(line,var_from_line,',',index+1);
  		if(index == (-1)) continue;
  		SpawnY = floatstr(var_from_line);

  		index = token_by_delim(line,var_from_line,',',index+1);
  		if(index == (-1)) continue;
  		SpawnZ = floatstr(var_from_line);

  		index = token_by_delim(line,var_from_line,',',index+1);
  		if(index == (-1)) continue;
  		SpawnRot = floatstr(var_from_line);

  		// Read Color1, Color2
  		index = token_by_delim(line,var_from_line,',',index+1);
  		if(index == (-1)) continue;
  		Color1 = strval(var_from_line);

  		index = token_by_delim(line,var_from_line,';',index+1);
  		Color2 = strval(var_from_line);

  		//printf("%d,%.2f,%.2f,%.2f,%.4f,%d,%d",vehicletype,SpawnX,SpawnY,SpawnZ,SpawnRot,Color1,Color2);
		if(vehicletype == 538)
		{//локомотив
			NPCCar[npc_veh] = AddStaticVehicle(vehicletype,SpawnX,SpawnY,SpawnZ,SpawnRot,Color1,Color2);
//printf("538.NPCCar[%d] = %d", npc_veh, NPCCar[npc_veh]);
			//gVehicleSpawn[NPCCar[npc_veh]] = 1;
			npc_veh ++;
		}
		else if(vehicletype == 449)
		{//трамвай
			NPCCar[npc_veh] = AddStaticVehicle(vehicletype,SpawnX,SpawnY,SpawnZ,SpawnRot,Color1,Color2);
//printf("449.NPCCar[%d] = %d", npc_veh, NPCCar[npc_veh]);
			//gVehicleSpawn[NPCCar[npc_veh]] = 1;
			npc_veh ++;
		}
		else if(vehicletype == 577)
		{//самалёт
			NPCCar[npc_veh] = AddStaticVehicle(vehicletype,SpawnX,SpawnY,SpawnZ,SpawnRot,Color1,Color2);
//printf("577.NPCCar[%d] = %d", npc_veh, NPCCar[npc_veh]);
			//gVehicleSpawn[NPCCar[npc_veh]] = 1;
			npc_veh ++;
		}
		else if(vehicletype == 420 && npc_veh < sizeof(NPCCar)
					/*(IsPointInRangeOfPoint(SpawnX,SpawnY,SpawnZ, 1.0, 1802.9108,-1862.4247,13.4583) ||
					IsPointInRangeOfPoint(SpawnX,SpawnY,SpawnZ, 1.0, 1802.9108,-1862.4247,13.4583) ||
					IsPointInRangeOfPoint(SpawnX,SpawnY,SpawnZ, 1.0, 1802.9108,-1862.4247,13.4583) ||
					IsPointInRangeOfPoint(SpawnX,SpawnY,SpawnZ, 1.0, 1802.9108,-1862.4247,13.4583) ||
					IsPointInRangeOfPoint(SpawnX,SpawnY,SpawnZ, 1.0, 1802.9108,-1862.4247,13.4583) ||
					IsPointInRangeOfPoint(SpawnX,SpawnY,SpawnZ, 1.0, 1802.9108,-1862.4247,13.4583))*/
				)
		{//такси
			NPCCar[npc_veh] = AddStaticVehicle(vehicletype,SpawnX,SpawnY,SpawnZ,SpawnRot,Color1,Color2);
//printf("420.NPCCar[%d] = %d", npc_veh, NPCCar[npc_veh]);
			//gVehicleSpawn[NPCCar[npc_veh]] = 1;
			npc_veh ++;
		}
		else
		{
  			AddStaticVehicleEx(vehicletype,SpawnX,SpawnY,SpawnZ,SpawnRot,Color1,Color2,-1);//(CARSPAWN*60));//(30*60)); // respawn 30 minutes -1);//отключаем респаун
  		}
		/*new numplate_test[32+1];
		format(numplate_test,32,"GRLC{44AA33}%d",vid);
		SetVehicleNumberPlate(vid, numplate_test);*/
		
		vehicles_loaded++;
	}
//Подвижные глобальные 3DText для ботов
/*
	CreateDynamic3DTextLabel("Мотель - Грузчик - Вокзал LS", COLOR_YELLOW,	0.0, -0.5, 1.2, 80.0, INVALID_PLAYER_ID, 548, 1);//NPCCar[7]
    CreateDynamic3DTextLabel("Вокзал LS - Стадион - Мотель", COLOR_YELLOW,	0.0, -0.5, 1.2, 80.0, INVALID_PLAYER_ID, 549, 1);
    CreateDynamic3DTextLabel("Мэрия - Вокзал SF - Больница", COLOR_YELLOW,	0.0, -0.5, 1.2, 80.0, INVALID_PLAYER_ID, 550, 1);

    CreateDynamic3DTextLabel("Вокзал SF - Ферма", COLOR_YELLOW,	0.0, -0.5, 1.2, 80.0, INVALID_PLAYER_ID, 551, 1);
    CreateDynamic3DTextLabel("Паркинг LV - Вокзал LV", COLOR_YELLOW,	0.0, -0.5, 1.2, 80.0, INVALID_PLAYER_ID, 622, 1);
    CreateDynamic3DTextLabel("LasVenturas\nLosSantos\nSanFierro", COLOR_YELLOW,	0.0, -0.5, 1.2, 80.0, INVALID_PLAYER_ID, 623, 1);

    CreateDynamic3DTextLabel("Аэропорт LS - Вокзал LS", COLOR_YELLOW,	0.0, -0.5, 1.2, 80.0, INVALID_PLAYER_ID, 624, 1);
    CreateDynamic3DTextLabel("Аэропорт LV - Вокзал LV", COLOR_YELLOW,	0.0, -0.5, 1.2, 80.0, INVALID_PLAYER_ID, 625, 1);
    CreateDynamic3DTextLabel("Аэропорт SF - Автошкола", COLOR_YELLOW,	0.0, -0.5, 1.2, 80.0, INVALID_PLAYER_ID, 733, 1);//NPCCar[15]
*/
	fclose(file_ptr);
	printf("Loaded %d vehicles from: %s",vehicles_loaded,filename);
	return vehicles_loaded;
}

//----------------------------------------------------------

stock strtok(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}

	new offset = index;
	new result[20];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}

//------------------------------------------------

stock strrest(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}
	new offset = index;
	new result[128];
	while ((index < length) && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}

//----------------------------------------------------------
// Tokenise by a delimiter
// Return string and index of the end determined by the
// provided delimiter in delim

stock token_by_delim(const string[], return_str[], delim, start_index)
{
	new x=0;
	while(string[start_index] != EOS && string[start_index] != delim) {
	    return_str[x] = string[start_index];
	    x++;
	    start_index++;
	}
	return_str[x] = EOS;
	if(string[start_index] == EOS) start_index = (-1);
	return start_index;
}

//----------------------------------------------------------

stock isNumeric(const string[])
{
  new length=strlen(string);
  if (length==0) return false;
  for (new i = 0; i < length; i++)
    {
      if (
            (string[i] > '9' || string[i] < '0' && string[i]!='-' && string[i]!='+') // Not a number,'+' or '-'
             || (string[i]=='-' && i!=0)                                             // A '-' but not at first.
             || (string[i]=='+' && i!=0)                                             // A '+' but not at first.
         ) return false;
    }
  if (length==1 && (string[0]=='-' || string[0]=='+')) return false;
  return true;
}

//----------------------------------------------------------

stock IsKeyJustDown(key, newkeys, oldkeys)
{
	if((newkeys & key) && !(oldkeys & key)) return 1;
	return 0;
}

//----------------------------------------------------------

stock PlaySoundForAll(soundid, Float:x, Float:y, Float:z)
{
	for(new i=0; i<MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i))
	    {
		    PlayerPlaySound(i, soundid, x, y, z);
	    }
	}
}

//----------------------------------------------------------

stock PlaySoundForPlayersInRange(soundid, Float:range, Float:x, Float:y, Float:z)
{
	for(new i=0; i<MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i) && IsPlayerInRangeOfPoint(i,range,x,y,z))
	    {
		    PlayerPlaySound(i, soundid, x, y, z);
	    }
	}
}

//----------------------------------------------------------

#define RETURN_USER_FAILURE -1
#define RETURN_USER_MULTIPLE -2

stock ReturnUser(text[])
{
	new pos = 0;
	new userid = RETURN_USER_FAILURE;
		
	while(text[pos] < 0x21) { // Strip out leading spaces
		if(text[pos] == 0) return RETURN_USER_FAILURE; // No passed text
		pos++;
	}
		
	if(isNumeric(text[pos])) { // Check whole passed string
		userid = strval(text[pos]);
		if(userid >=0 && userid < MAX_PLAYERS)
		{
			if(IsPlayerConnected(userid)) return userid;
			return RETURN_USER_FAILURE;
		}
	}
	
	// They entered [part of] a name or the id search failed (check names just incase)
	new len = strlen(text[pos]);
	new count = 0;
	new name[MAX_PLAYER_NAME+1];
	
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			GetPlayerName(i, name, sizeof(name));
			if(strcmp(name, text[pos], true, len) == 0) // Check segment of name
			{
				if(len == strlen(name)) { // Exact match
					return i;
				}
				else { // Partial match
					count++;
					userid = i;
				}
			}
		}
	}
	
	if(!count) return RETURN_USER_FAILURE;
	if(count > 1) return RETURN_USER_MULTIPLE;
	
	return userid;
}

//----------------------------------------------------------

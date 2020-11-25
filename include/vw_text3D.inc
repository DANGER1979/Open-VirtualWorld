//#include "../include/vw_farmer"

/*
#define MAX_STREAM_LABELS 221//MAX_HOUSE+MAX_BIZ+MAX_SBIZ = 52+82+59 + 24=217
enum label_info
{
	lText[128],//19+20+24+1
	lColor,
	Float:lX,
	Float:lY,
	Float:lZ,
	Float:lDist,
	lLos
}
new PlayerLabels[MAX_STREAM_LABELS][label_info];//массив 3D текстов для стримера OnPlayer3DTextLabelTimer(playerid)
*/
//##############################################################################//
//                                                                              //
//                           ИДЕНТИФИКАТОРЫ Text3D                              //
//                                                                              //
//##############################################################################//
//new Text3D: text3D[MAX_HOUSE+MAX_BIZ+MAX_SBIZ];
//new Text3D: Label;

new Text3D: MineInfo;      // 3д текст для склада шахтёров
new Text3D: OceanDockInfo;      // 3д текст для склада порта
new Text3D: StoreHouseInfo;      // 3д текст для общего склада биржи
//new Text3D: ElectionInfo; // 3д текст для выборов

new Text3D: number3D[MAX_VEHICLES+1];//номер авто
new Text3D: sale3D[MAX_VEHICLES+1];

//##############################################################################//
/*enum lab_info
{
	PlayerText3D: labelid[MAX_STREAM_LABELS],
	bool: lView[MAX_STREAM_LABELS],//состояние отображения - переключатель стримера
	bool: lShow[MAX_STREAM_LABELS]//состояние отображения - переключатель стримера
}
new labelPlayer[MAX_PLAYERS][lab_info];//для ф-ии OnPlayerLabelTimer


stock text3D_OneSecondTimers2(playerid)
//stock OnPlayer3DTextLabelTimer(playerid)//вызывается из OneSecondTimers2 //OnPlayerSpawn
{//для УСТАНОВКИ СТРИМ-ОБЪЕКТОВ
   	//new strings[MAX_STRING];
	for(new l=0; l<MAX_STREAM_LABELS; l++)
	{
   		if(IsPlayerInRangeOfPoint(playerid, stream_distance, PlayerLabels[l][lX],PlayerLabels[l][lY],PlayerLabels[l][lZ]) )
		{   //если игрок в зоне установки 3Dтекста
			if(labelPlayer[playerid][lView][l] == false)
			{   //если игроку не показан 3Dтекст
				if(LabelPlayerCounter[playerid]+1 < MAX_3DTEXT_PLAYER)
				{   //ЗАЩИТА: если ID 3Dтекста не достиг максимуа
					labelPlayer[playerid][labelid][l] = CreatePlayer3DTextLabelEx(playerid,
						PlayerLabels[l][lText], PlayerLabels[l][lColor],
						PlayerLabels[l][lX],PlayerLabels[l][lY],PlayerLabels[l][lZ],
						PlayerLabels[l][lDist], INVALID_PLAYER_ID, INVALID_VEHICLE_ID, PlayerLabels[l][lLos]);
					labelPlayer[playerid][lView][l] = true;


					//ИНФОРМИРОВАНИЕ
					//format(strings, sizeof(strings), "CreatePlayer3DTextLabel(playerid:%d, idx:%d, text:%s)", playerid, l, PlayerLabels[l][lText]);
					//SendClientMessage(playerid, COLOR_GREY, strings);
					//ABroadCast(COLOR_MAROON, strings, 11);
					//SendClientMessageToAll(COLOR_YELLOW, strings);
				}
				else
				{
					format(strings, sizeof(strings), "Error: labelPlayer %d >= MAX_3DTEXT_PLAYER", l);
					Log(ERROR, strings);
				}
			}
			else
			{
				if(labelPlayer[playerid][lShow][l] == true)
				{   //если показан, то обновить
					UpdatePlayer3DTextLabelText(playerid, labelPlayer[playerid][labelid][l], PlayerLabels[l][lColor], PlayerLabels[l][lText]);
					labelPlayer[playerid][lShow][l] = false;

					//ИНФОРМИРОВАНИЕ
					//format(strings, sizeof(strings), "UpdatePlayer3DTextLabelText(playerid:%d, idx:%d, text:%s)", playerid, l, PlayerLabels[l][lText]);
					//SendClientMessage(playerid, COLOR_GREY, strings);
					//ABroadCast(COLOR_MAROON, strings, 11);
					//SendClientMessageToAll(COLOR_YELLOW, strings);
				}
			}
		}
		else//если игрок далеко, то убрать если были показаны
		{
			if(labelPlayer[playerid][lView][l] == true)
			{	//если игроку показан объект
				DeletePlayer3DTextLabelEx(playerid, labelPlayer[playerid][labelid][l]);
				labelPlayer[playerid][lView][l] = false;
				labelPlayer[playerid][lShow][l] = false;


				//ИНФОРМИРОВАНИЕ
				//format(strings, sizeof(strings), "DeletePlayer3DTextLabel(playerid:%d, idx:%d)", playerid, l);
				//SendClientMessage(playerid, COLOR_GREY, strings);
				//ABroadCast(COLOR_MAROON, strings, 11);
				//SendClientMessageToAll(COLOR_YELLOW, strings);
			}
		}
	}
}
*/

stock text3D_OnGameModeInit()
{
//##############################################################################//
//                                                                              //
//                              ГЛОБАЛЬНЫЕ 3DText                               //
//                                                                              //
//##############################################################################//

/*
//{179,296.3036,-40.2164,1001.5156,1.4359,4}, // ammo, vw 4, int 1
	Create3DTextLabelEx("{EE66EE}Ammunation'1{FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, 296.2800,-37.3602,1001.5156, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Ammunation'1 int1
//	{179,295.7170,-82.5275,1001.5156,359.9262,5}, // ammo, vw 5, int 4
	Create3DTextLabelEx("{EE66EE}Ammunation'2{FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, 295.6000,-80.0605,1001.5156, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Ammunation'2 int4
	Create3DTextLabelEx("{EE66EE}Ammunation'3{FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, 290.2196,-109.6215,1001.5156, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Ammunation'3 int6
	Create3DTextLabelEx("{EE66EE}Ammunation'4{FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, 308.0652,-140.5119,999.6016, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Ammunation'4 int7
	Create3DTextLabelEx("{EE66EE}Ammunation'5{FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, 312.7611,-165.6264,999.6010, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Ammunation'5 int6
	Create3DTextLabelEx("{EE66EE}Burger Shot{FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, 376.6057,-68.3676,1001.5151, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Burger Shot int10
	Create3DTextLabelEx("{EE66EE}Stacked Pizza{FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, 376.7138,-120.1047,1001.4995, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Stacked Pizza int5
	Create3DTextLabelEx("{EE66EE}Cluckin Bell{FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, 370.8717,-7.2981,1001.8589, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Cluckin Bell int9
	Create3DTextLabelEx("{EE66EE}Shop 24/7 (V1){FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, -28.5542,-184.4023,1003.5469, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Shop 24/7 (V1) int17
	Create3DTextLabelEx("{EE66EE}Shop 24/7 (V2){FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, 2.0517,-29.0135,1003.5494, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Shop 24/7 (V2) int10
	Create3DTextLabelEx("{EE66EE}Shop 24/7 (V3){FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, -26.9264,-89.3450,1003.5469, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Shop 24/7 (V3) int18
	Create3DTextLabelEx("{EE66EE}Shop 24/7 (V4){FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, -21.1814,-138.0265,1003.5469, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Shop 24/7 (V4) int16
	Create3DTextLabelEx("{EE66EE}Shop 24/7 (V5){FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, -30.1156,-28.2309,1003.5573, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Shop 24/7 (V5) int4
	Create3DTextLabelEx("{EE66EE}Shop 24/7 (V6){FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, -22.2079,-54.9859,1003.5469, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Shop 24/7 (V6) int6
	Create3DTextLabelEx("{EE66EE}Mistys Bar{FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, 495.7801,-76.0305,998.7578, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Mistys Bar int11
	Create3DTextLabelEx("{EE66EE}Restaurant{FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, -782.3854,500.0729,1371.7490, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Restaurant int1
	Create3DTextLabelEx("{EE66EE}Lil' Probe{FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, -224.7967,1403.9092,27.7734, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Lil' Probe'Inn int18
	Create3DTextLabelEx("{EE66EE}igPen{FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, 1215.8767,-12.5477,1000.9219, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Club PigPen int2
	Create3DTextLabelEx("{EE66EE}Nude Strippers{FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, 1207.2367,-31.5843,1000.9531, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Nude Strippers Daily int3
	Create3DTextLabelEx("{EE66EE}Alhamdra{FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, 499.9627,-18.7895,1000.6719, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Club Alhamdra int17
	Create3DTextLabelEx("{EE66EE}Jizzy{FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, -2665.2327,1410.2078,906.2734, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);	//Jizzy's Pleasure Domes int3
	Create3DTextLabelEx("{EE66EE}Restaurant{FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, 449.4581,-83.6614,999.5547, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Restaurant int4
	Create3DTextLabelEx("{EE66EE}Restaurant{FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, 449.2562,-17.5881,1001.1328, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Restaurant int1
	Create3DTextLabelEx("{EE66EE}Pump Bar{FFFFFF}Нажмите {1EFF00}'Y' {FFFFFF}для взаимодействия",0xFFFFFFFF, 681.5111,-454.3947,-25.6172, 20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1);		//Pump Bar int1
*/
	//--------------------------------------------------------------------------
//Подвижные глобальные 3DText для ботов
/*
	//Label = Create3DTextLabel("Мотель - Грузчик - Вокзал LS", COLOR_YELLOW, 0.0,0.0,0.0, 80.0,0,1); Counter3DText ++;
    //Attach3DTextLabelToVehicle(Label, 101, 0.0, -0.5, 1.2);
	CreateDynamic3DTextLabel("Мотель - Грузчик - Вокзал LS", COLOR_YELLOW,	0.0, -0.5, 1.2, 80.0, INVALID_PLAYER_ID, 101, 1);

    //Label = Create3DTextLabel("Вокзал LS - Стадион - Мотель", COLOR_YELLOW, 0.0,0.0,0.0, 80.0,0,1); Counter3DText ++;
    //Attach3DTextLabelToVehicle(Label, 102, 0.0, -0.5, 1.2);
    CreateDynamic3DTextLabel("Вокзал LS - Стадион - Мотель", COLOR_YELLOW,	0.0, -0.5, 1.2, 80.0, INVALID_PLAYER_ID, 102, 1);

    //Label = Create3DTextLabel("Мэрия - Вокзал SF - Больница", COLOR_YELLOW, 0.0,0.0,0.0, 80.0,0,1); Counter3DText ++;
    //Attach3DTextLabelToVehicle(Label, 103, 0.0, -0.5, 1.2);
    CreateDynamic3DTextLabel("Мэрия - Вокзал SF - Больница", COLOR_YELLOW,	0.0, -0.5, 1.2, 80.0, INVALID_PLAYER_ID, 102, 1);

    Label = Create3DTextLabel("Вокзал SF - Ферма", COLOR_YELLOW, 0.0,0.0,0.5, 80.0,0,1); Counter3DText ++;
    Attach3DTextLabelToVehicle(Label, 104, 0.0, -0.5, 1.2);

    Label = Create3DTextLabel("Паркинг LV - Вокзал LV", COLOR_YELLOW, 0.0,0.0,0.0, 80.0,0,1); Counter3DText ++;
    Attach3DTextLabelToVehicle(Label, 105, 0.0, -0.5, 1.2);

    Label = Create3DTextLabel("LasVenturas\nLosSantos\nSanFierro", COLOR_YELLOW, 0.0,0.0,0.75, 80.0,0,1); Counter3DText ++;
    Attach3DTextLabelToVehicle(Label, 106, 0.0, -0.5, 1.2);
	//--------------------------------------------------------------------------
    Label = Create3DTextLabel("Аэропорт LS - Вокзал LS", COLOR_ORANGE, 0.0,0.0,0.0, 80.0,0,1); Counter3DText ++;
    Attach3DTextLabelToVehicle(Label, 107, 0.0, 0.0, 2.4);

    Label = Create3DTextLabel("Аэропорт LV - Вокзал LV", COLOR_ORANGE, 0.0,0.0,0.0, 80.0,0,1); Counter3DText ++;
    Attach3DTextLabelToVehicle(Label, 108, 0.0, 0.0, 2.4);

    Label = Create3DTextLabel("Аэропорт SF - Автошкола", COLOR_ORANGE, 0.0,0.0,0.0, 80.0,0,1); Counter3DText ++;
    Attach3DTextLabelToVehicle(Label, 109, 0.0, 0.0, 2.4);
*/
}



//forward Text3D: Create3DTextLabelEx(text[], color, Float:x, Float:y, Float:z, Float:drawdistance, attachedplayer, attachedvehicle, testlos,	worldid,
//	interiorid, playerid, Float:streamdistance);
//public

forward Text3D: Create3DTextLabelEx(text[], color, Float:x, Float:y, Float:z, Float:drawdistance, attachedplayer, attachedvehicle, testlos, worldid);
public Text3D: Create3DTextLabelEx(text[], color, Float:x, Float:y, Float:z, Float:drawdistance, attachedplayer, attachedvehicle, testlos, worldid)
//attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1)
//interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD
{
	if(!strlen(text)) return Text3D: INVALID_3DTEXT_ID;
 	//LabelPlayerCounter[playerid] ++;
	//if( !strlen(text) ) return CreatePlayer3DTextLabel(playerid, "none", color, x,y,z, drawdistance, attachedplayer, attachedvehicle, testlos);
/*	PlayerLabels[h][lText] = text;
	PlayerLabels[h][lColor] = color;
	PlayerLabels[h][lX] = X;
	PlayerLabels[h][lY] = Y;
	PlayerLabels[h][lZ] = Z+0.75;
	PlayerLabels[h][lDist] = DrawDistance;
	PlayerLabels[h][lLos] = testLOS;
*/
	//labelPlayer[playerid][view][indexText3D] = true;
	//return CreatePlayer3DTextLabel(playerid, text, color, x,y,z, drawdistance, attachedplayer, attachedvehicle, testlos);

	Counter3DText ++;
	return CreateDynamic3DTextLabel(text, color, x,y,z, drawdistance, attachedplayer, attachedvehicle, testlos, worldid);//, interiorid, playerid, streamdistance);
}

forward Delete3DTextLabelEx(Text3D: TextID);
public Delete3DTextLabelEx(Text3D: TextID)
{
 	//LabelPlayerCounter[playerid] --;
 	Counter3DText --;
	DestroyDynamic3DTextLabel(TextID);
	TextID = Text3D:-1;
	//return DeletePlayer3DTextLabel(playerid, PlayerTextID);
}

forward Update3DTextLabelEx(Text3D: TextID, color, text[]);
public Update3DTextLabelEx(Text3D: TextID, color, text[])
{//PlayerText3D:id
	//#pragma unused playerid
	if(!strlen(text)) return INVALID_3DTEXT_ID;
	//strmid(PlayerLabels[indexText3D][lText], text, 0, strlen(text), 128);//19+20+24+1
	//PlayerLabels[TextID][lColor] = color;
	/*if(playerid != MAX_PLAYERS-1)
	{
		labelPlayer[playerid][lShow][indexText3D] = true;//чтобы обновить всем у кого показан данный 3Д текст, но не они инициаторы изменения
		//return UpdatePlayer3DTextLabelText(playerid, labelPlayer[playerid][labelid][indexText3D], color, text);
		//return UpdateDynamic3DTextLabelText(labelPlayer[playerid][labelid][indexText3D], color, text);
	}*/
	//return 1;
	return UpdateDynamic3DTextLabelText(TextID, color, text);
}

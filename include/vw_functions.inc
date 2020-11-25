/*
 *            VW_UsefulFunctions 1.8
 *       (c) Copyright 2009-2010 by Hidden -=DANGER=-
 *
 * @author    : DANGER1979 (gameplanet.by)
 * @date      : 18.10.2009
 * @update    : 23.09.2013
 *
 * This file is provided as is (no warranties).
 *
 */
/*#if defined _VW_UsefulFunctions_included
	#endinput
#endif
#define _VW_UsefulFunctions_included
#pragma library VW_UsefulFunctions*/

//#include <a_samp>

//#define DisableBadword(%1) for(new i=0; i<strlen(text); i++) if(strfind(text[i], %1, true) == 0) for(new a=0; a<256; a++) if(a >= i && a < i+strlen(%1)) text[a]='*'


//ф-ии не использующие внешние массивы PlayerInfo и т.п.

//##############################################################################//
//                                                                              //
//                             ПЕРЕГРУЖЕННЫЕ ФУНКЦИИ                            //
//                                                                              //
//##############################################################################//
stock strvalEx(const tmp[])
{
	if(strlen(tmp) > 10) return 0;
	if(strval(tmp) >= 2147483647 || strval(tmp) <= -2147483647) return 0;
	return strval(tmp);
}

//##############################################################################//
//                                                                              //
//                               БЛОКИ АВТОЗАМЕНЫ                               //
//                                                                              //
//##############################################################################//

#define GivePVarInt(%0,%1,%2) SetPVarInt(%0,%1,GetPVarInt(%0,%1) %2)
//GetPVarInt обнуляется при дисконнекте
//#define SQUARE(%0) ((%0)*(%0))

//#define PlayerName(%0) PlayerInfo[%0][pName]
stock PlayerName(playerid)
{
	new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));
	return name;
}

stock HideDialog(playerid)
{
	ShowPlayerDialog(playerid, -1, 0, " ", " ", " ", "");
}
stock Pressing(playerid)
{
	new keys, updown, leftright;
	GetPlayerKeys(playerid, keys, updown, leftright);
	return keys;
}

stock WeaponName(weaponid)
//weaponid,const weapon[],len)
{  //для получения имя оружия
	new gunname[32];
	if(weaponid == 0)
	{
		gunname = "Unarmed (Fist)";
	}
	else if(weaponid == 18)
	{
		gunname = "Molotov Cocktail";
	}
	else if(weaponid == 44)
	{
		gunname = "Thermal Goggles";
	}
	else if(weaponid == 45)
	{
		gunname = "Night Vision Goggles";
	}
	else if(weaponid == 50)
	{
		gunname = "DriveByVehicle";
	}
	else if(weaponid == 51)
	{
		gunname = "Взорван";
	}
	else if(weaponid == 53)
	{
		gunname = "Утонул";
	}
	else if(weaponid == 54)
	{
		gunname = "Упал";
	}
	else
	{
		GetWeaponName(weaponid, gunname, sizeof(gunname));
	}
	return gunname;
}
/*new aWeaponNames[][32] = {
	{"Unarmed (Fist)"}, // 0
	{"Brass Knuckles"}, // 1
	{"Golf Club"}, // 2
	{"Night Stick"}, // 3
	{"Knife"}, // 4
	{"Baseball Bat"}, // 5
	{"Shovel"}, // 6
	{"Pool Cue"}, // 7
	{"Katana"}, // 8
	{"Chainsaw"}, // 9
	{"Purple Dildo"}, // 10
	{"Big White Vibrator"}, // 11
	{"Medium White Vibrator"}, // 12
	{"Small White Vibrator"}, // 13
	{"Flowers"}, // 14
	{"Cane"}, // 15
	{"Grenade"}, // 16
	{"Teargas"}, // 17
	{"Molotov"}, // 18
	{" "}, // 19
	{" "}, // 20
	{" "}, // 21
	{"Colt 45"}, // 22
	{"Colt 45 (Silenced)"}, // 23
	{"Desert Eagle"}, // 24
	{"Normal Shotgun"}, // 25
	{"Sawnoff Shotgun"}, // 26
	{"Combat Shotgun"}, // 27
	{"Micro Uzi (Mac 10)"}, // 28
	{"MP5"}, // 29
	{"AK47"}, // 30
	{"M4"}, // 31
	{"Tec9"}, // 32
	{"Country Rifle"}, // 33
	{"Sniper Rifle"}, // 34
	{"Rocket Launcher"}, // 35
	{"Heat-Seeking Rocket Launcher"}, // 36
	{"Flamethrower"}, // 37
	{"Minigun"}, // 38
	{"Satchel Charge"}, // 39
	{"Detonator"}, // 40
	{"Spray Can"}, // 41
	{"Fire Extinguisher"}, // 42
	{"Camera"}, // 43
	{"Night Vision Goggles"}, // 44
	{"Infrared Vision Goggles"}, // 45
	{"Parachute"}, // 46
	{"Fake Pistol"} // 47
};*/

stock TimeConverter(seconds)//Конвертер секунд - в минуты и секунды
{
	new strtmp[10+3+3 + 1];//объявляем символьную переменную
 	//new minutes = floatround(seconds/60.0, floatround_floor);//кол. целых минут
  	new minutes = seconds/60;//кол. целых минут
//ВНИМАНИЕ: округлять только вещественную, целую не надо округлять, но при этом может быть потеря точности
//ВНИМАНИЕ: лучше округлять каждый отдельно,чем все вместе
//ВНИМАНИЕ: для получения вещественной лучше делить на вещественную, но чем меньше вещественных тем быстрее
//floatround_round	Округлите до ближайшего целое. Дробная часть 0.5 Округлить вверх.
//floatround_floor	Округлить вниз. Лучше вообще ни чего не ставить, т.к. подпедаливает
//floatround_ceil	Округлить вверх
//floatround_tozero	Округлить вниз для положительных величин и вверх для отрицательных величин
	//seconds = seconds - minutes*60; 	//остаток
	format(strtmp, sizeof(strtmp), "%02d:%02d", minutes, (seconds - minutes*60));//преобразовываем
	return strtmp;//возвращаем строку символов
}

stock HoursTimeConverter(seconds)//Конвертер секунд - в часы и минуты
{//20:39   74340/3600 = 20,65  (74340 - 20*3600)/60 = 39
	new strtmp[10+3+3 + 1];//объявляем символьную переменную
 	//new minutes = floatround(seconds/60.0, floatround_floor);//кол. целых минут
  	new hours = seconds/3600;//кол. целых часов
	//minutes = (seconds - hours*3600)/60; 	//остаток
	format(strtmp, sizeof(strtmp), "%02d:%02d", hours, (seconds - hours*3600)/60);//преобразовываем
	return strtmp;//возвращаем строку символов
}

stock GetNextTime(add_seconds)//21*3600+50*60 = 78600
{//возвращает время увеличенное на указанное кол-во секунд 74340+ 16*60 = 75300
	new a_hour, a_minute, a_seconds;
	gettime(a_hour, a_minute, a_seconds);
	new cur_time = a_hour*60*60 + a_minute*60 + a_seconds + add_seconds; //в секундах

  	new hours = cur_time/3600;//кол. целых часов
	new strtmp[10+3+3 + 1];//объявляем символьную переменную
	format(strtmp, sizeof(strtmp), "%02d:%02d", hours, (cur_time - hours*3600)/60);//преобразовываем
	return strtmp;
}

//конвертор мс - в мин:сек.мсек
stock timeconvert(Time, &Minutes, &Seconds, &rMSeconds)//для гонок конвертор мс - в мин:сек.мсек
{   //Time - кол-во процесорных тиков с момента старта, в мс
	new Float:fTime = floatdiv(Time, 60000.0);//Делит вещественное число на значение, указанное вещественным числом, делителем.
    Minutes = floatround(fTime, floatround_tozero);//Округляет вещественное число указанным методом.
    //Round downwards for positive values and upwards for negative values (“truncate”).
    //Округлить вниз для положительных величин и вверх для отрицательных величин
    Seconds = floatround(floatmul(fTime - Minutes, 60.0), floatround_tozero);
						//Перемножает два вещественных числа и возвращает произведение.
    rMSeconds = floatround(floatmul(floatmul(fTime - Minutes, 60.0) - Seconds, 1000.0), floatround_tozero);
}

stock GetMonth(month=1)
{
	new month_str[14];
	switch(month)
	{
		/*case 1: month_str = 	"Янв";
		case 2: month_str = 	"Фев";
		case 3: month_str = 	"Мар";
		case 4: month_str = 	"Апр";
		case 5: month_str = 	"Мая";
		case 6: month_str = 	"Июня";
		case 7: month_str = 	"Июля";
		case 8: month_str = 	"Авг";
		case 9: month_str = 	"Сен";
		case 10: month_str = 	"Окт";
		case 11: month_str = 	"Нояб";
		case 12: month_str = 	"Дек";
		default: month_str = 	"Янв";*/
		
		case 1: month_str = 	"•®ў";
		case 2: month_str = 	"Ѓeў";
		case 3: month_str = 	"Map";
		case 4: month_str = 	"AЈp";
		case 5: month_str = 	"Ma¬";
		case 6: month_str = 	"…«®¬";
		case 7: month_str = 	"…«ћ¬";
		case 8: month_str = 	"Aў™";
		case 9: month_str = 	"Ce®";
		case 10: month_str = 	"Ok¦";
		case 11: month_str = 	"Ho¬—";
		case 12: month_str = 	"ѓek";
		default: month_str = 	"•®ў";
	}
	return month_str;
}

//https://pawnokit.ru/text_conv
stock GetFullWeekDay(day=1, month=1, year=2020)
{
//GetWeekDay(); //return the weekday of today
//GetWeekDay(13, 3, 2009); //return "Friday"
	if(!day) getdate(year, month, day);
	new  weekday_str[14],//[10]
		j, e;
	if (month <= 2)
	{
		month += 12;
		--year;
	}

	j = year % 100;
	e = year / 100;

	switch ((day + (month+1)*26/10 + j + j/4 + e/4 - 2*e) % 7)
	{
		/*case 0: weekday_str = "Суббота";
		case 1: weekday_str = "Воскресенье";
		case 2: weekday_str = "Понедельник";
		case 3: weekday_str = "Вторник";
		case 4: weekday_str = "Среда";
		case 5: weekday_str = "Четверг";
		case 6: weekday_str = "Пятница";
        default: weekday_str = "Воскресенье";*/
        
		case 0: weekday_str = "Cy——o¦a";
		case 1: weekday_str = "‹ockpece®©e";
		case 2: weekday_str = "Њo®eљeћ©®њk";
		case 3: weekday_str = "‹¦op®њk";
		case 4: weekday_str = "Cpeљa";
		case 5: weekday_str = "Ќe¦ўep™";
		case 6: weekday_str = "Њ¬¦®њ‰a";
        default: weekday_str = "‹ockpece®©e";
        
		/*case 0: weekday_str = "Saturday";
		case 1: weekday_str = "Sunday";
		case 2: weekday_str = "Monday";
		case 3: weekday_str = "Tuesday";
		case 4: weekday_str = "Wednesday";
		case 5: weekday_str = "Thursday";
		case 6: weekday_str = "Friday";*/
	}
	return weekday_str;
}

stock GetWeekDay(day=1, month=1, year=2020)
{
//GetWeekDay(); //return the weekday of today
//GetWeekDay(13, 3, 2009); //return "Friday"
	if(!day) getdate(year, month, day);
	new  weekday_str[3],//[10]
		j, e;
	if (month <= 2)
	{
		month += 12;
		--year;
	}

	j = year % 100;
	e = year / 100;

	switch ((day + (month+1)*26/10 + j + j/4 + e/4 - 2*e) % 7)
	{
		case 0: weekday_str = "C6";
		case 1: weekday_str = "Bc";
		case 2: weekday_str = "Њ®";
		case 3: weekday_str = "Bm";
		case 4: weekday_str = "Cp";
		case 5: weekday_str = "4m";
		case 6: weekday_str = "Њm";
		default: weekday_str = "Bc";
		/*case 0: weekday_str = "Saturday";
		case 1: weekday_str = "Sunday";
		case 2: weekday_str = "Monday";
		case 3: weekday_str = "Tuesday";
		case 4: weekday_str = "Wednesday";
		case 5: weekday_str = "Thursday";
		case 6: weekday_str = "Friday";*/
	}
	return weekday_str;
}

forward Float: CalculateArea(Float:x1,Float:y1,Float:x2,Float:y2,Float:x3,Float:y3);
public Float: CalculateArea(Float:x1,Float:y1,
					Float:x2,Float:y2,
					Float:x3,Float:y3)
{   //возвращает площадь треугольника
    new Float: ab = x1*y2 - y1*x2;
    new Float: bc = x2*y3 - y2*x3;
	new Float: ca = x3*y1 - y3*x1;
	//new Float: S = floatabs((ab + bc + ca)/2);
	//printf("ab:%.1f, bc:%.1f, ca:%.1f, S=%.1f",ab, bc, ca, S);
	return floatabs((ab + bc + ca)/2);
}//Проверка: //S = 1/2 * a * h = 1921
//S = 1/2 * a * b * sin(gamma) = 1820;



//===================== stocks ====================

stock SetPlayerToFacePlayer(playerid, targetid)
{
	if(!IsPlayerConnected(playerid) || !IsPlayerConnected(targetid)) return 0;
	new	Float:pX, Float:pY, Float:pZ, Float:X, Float:Y,	Float:Z, Float:ang;
	GetPlayerPos(targetid, X, Y, Z);
	GetPlayerPos(playerid, pX, pY, pZ);
	if( Y > pY ) ang = (-acos((X - pX) / floatsqroot((X - pX)*(X - pX) + (Y - pY)*(Y - pY))) - 90.0);
	else if( Y < pY && X < pX ) ang = (acos((X - pX) / floatsqroot((X - pX)*(X - pX) + (Y - pY)*(Y - pY))) - 450.0);
	else if( Y < pY ) ang = (acos((X - pX) / floatsqroot((X - pX)*(X - pX) + (Y - pY)*(Y - pY))) - 90.0);

	if(X > pX) ang = (floatabs(floatabs(ang) + 180.0));
	else ang = (floatabs(ang) - 180.0);

	SetPlayerFacingAngle(playerid, ang);
	return 0;
}

stock AngleInRangeOfAngle(Float:a1, Float:a2, Float:range)
{   //range - диапазон угла
	a1 = a1 - a2;
	if((a1 < range) && (a1 > -range)) return 1;
	return 0;
}


stock SetObjectFaceCoords3D(iObject, Float: fX, Float: fY, Float: fZ, Float: fRollOffset = 0.0, Float: fPitchOffset = 0.0, Float: fYawOffset = 0.0) {
    new
        Float: fOX,
        Float: fOY,
        Float: fOZ,
        Float: fPitch
    ;
    GetObjectPos(iObject, fOX, fOY, fOZ);

    fPitch = floatsqroot(floatpower(fX - fOX, 2.0) + floatpower(fY - fOY, 2.0));
    fPitch = floatabs(atan2(fPitch, fZ - fOZ));

    fZ = atan2(fY - fOY, fX - fOX) - 90.0; // Yaw

    SetObjectRot(iObject, fRollOffset, fPitch + fPitchOffset, fZ + fYawOffset);
}


stock odd_number(numeric)
{//возвращает верно если numeric чётное
	new val = (numeric+2)/2 - (numeric+1)/2;//результат целочисленного деления
	//Равно 1 если "c" четное, 0 - нечетное.
	//printf( "value: %d, c: %d", value, c);
	if(val == 1) return 0;//если чётное - точка не принадлежит треугольнику
	else return 1;//если нечётное - точка принадлежит треугольнику
}
stock check_number(number, check)
{//возвращает верно если  number кратно check
	new val = number%check;//остаток от деления
	if(val == 0) return 1;
	else return 0;
}
stock generate_password(const number)
{	//number - длина пароля
	/*salt = "abchefghjkmnpqrstuvwxyz0123456789";
	srand( ( double ) microtime() * 1000000 );
	for($i = 0; $i < 9; $i ++) {
		$new_pass .= $salt{rand( 0, 33 )};
	}*/
	//static const cells[] = "abcdefghijklmnoprstuvxyz123456789";
	static const cells[] = "abcdefghjkmnoprstuvxyz123456789";
	new pass[7];
	new i=0;
	do
	//for(new i = 0; i < number; i++)
	{
		pass[i] = cells[random(sizeof(cells))];
		i++;
	}
	while(strlen(pass) < number);
	return pass;
}


stock ConvertNonNormaQuatToEuler(Float: qw, Float: qx, Float:qy, Float:qz,
								&Float:heading, &Float:attitude, &Float:bank)
{	// Yaw(Heading) - рысканье(курс), Pitch(Attitude) - тангаж (килевая качка), Roll(Bank) - крен (бортовая качка),
    new Float: sqw = qw*qw;
    new Float: sqx = qx*qx;
    new Float: sqy = qy*qy;
    new Float: sqz = qz*qz;
	new Float: unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
	//если normalised, - один, в противном случае - показатель коррекции
	new Float: test = qx*qy + qz*qw;
	if(test > 0.499*unit)
	{ // singularity at north pole - особенность на северном полюсе
		heading = 2*atan2(qx,qw);
		attitude = 3.141592653/2;
		bank = 0;
		return 1;
	}
	if(test < -0.499*unit)
	{ // singularity at south pole - особенность на южном полюсе
		heading = -2*atan2(qx,qw);
		attitude = -3.141592653/2;
		bank = 0;
		return 1;
	}
    heading = atan2(2*qy*qw - 2*qx*qz, sqx - sqy - sqz + sqw);
	attitude = asin(2*test/unit);
	bank = atan2(2*qx*qw - 2*qy*qz, -sqx + sqy - sqz + sqw);
	return 1;
}


//##############################################################################//
//                                                                              //
//                         ФУНКЦИИ ДЛЯ РАБОТЫ С ТЕКСТОМ                         //
//                                                                              //
//##############################################################################//

stock GameTextFormatForPlayer(playerid, const msg[], timeg, style, {Float,_}:...)
{
	new len = strlen(msg),d=0,posArg = 4;
 	new dest[512];
	for(new i=0;i<len;i++)
	{
	    if(msg[i] == '%')
	    {
	        switch (msg[i+1])
	        {
	            case 's':
				{
	   				new pos,arg,tmppos;
	   				new str[128];
	       			while(getarg(posArg,pos)!='\0')
	   				{
        				arg=getarg(posArg,pos++);
						str[tmppos]=arg;
      					tmppos++;
	       			}
				    strins(dest,str,d,strlen(str));
				    d+=strlen(str);
					posArg++;
					i++;
				}
	            case 'i', 'd':
				{
				    new str[128];
				    format(str,sizeof(str),"%d",getarg(posArg));
				    strins(dest,str,d,strlen(str));
				    d+=strlen(str);
					posArg++;
					i++;
				}
	            case 'f':
				{
				    new str[128];
				    format(str,sizeof(str),"%f",getarg(posArg));
				    strins(dest,str,d,strlen(str));
				    d+=strlen(str);
					posArg++;
					i++;
				}
				case '.':
				{
				    new len2 = msg[i+2];
				    if(len2 == 0)
					{
						dest[d] = msg[i];
						d++;
					}
					else
					{
					    new str[32],formatting[5];
					    formatting[0] = '%';
					    formatting[1] = '.';
					    formatting[2] = len2;
					    formatting[3] = 'f';
					    format(str,sizeof(str),formatting,getarg(posArg));
					    strins(dest,str,d,len2);
					    d+=len;
						posArg++;
						i+= 2;
					}
				}
				default:
				{
					dest[d] = msg[i];
					d++;
				}
			}
		}
		else
		{
			dest[d] = msg[i];
			d++;
		}
	}
	return GameTextForPlayer(playerid,dest,timeg,style);
}
stock SendClientFormatMessage(playerid,color,const msg[],{Float,_}:...)
{
	new len = strlen(msg),d=0,posArg = 3;
 	new dest[512];
	for(new i=0;i<len;i++)
	{
	    if(msg[i] == '%')
	    {
	        switch (msg[i+1])
	        {
	            case 's':
				{
	   				new pos,arg,tmppos;
	   				new str[128];
	       			while(getarg(posArg,pos)!='\0')
	   				{
        				arg=getarg(posArg,pos++);
						str[tmppos]=arg;
      					tmppos++;
	       			}
				    strins(dest,str,d,strlen(str));
				    d+=strlen(str);
					posArg++;
					i++;
				}
	            case 'i', 'd':
				{
				    new str[128];
				    format(str,sizeof(str),"%d",getarg(posArg));
				    strins(dest,str,d,strlen(str));
				    d+=strlen(str);
					posArg++;
					i++;
				}
	            case 'f':
				{
				    new str[128];
				    format(str,sizeof(str),"%f",getarg(posArg));
				    strins(dest,str,d,strlen(str));
				    d+=strlen(str);
					posArg++;
					i++;
				}
				case '.':
				{
				    new len2 = msg[i+2];
				    if(len2 == 0)
					{
						dest[d] = msg[i];
						d++;
					}
					else
					{
					    new str[32],formatting[5];
					    formatting[0] = '%';
					    formatting[1] = '.';
					    formatting[2] = len2;
					    formatting[3] = 'f';
					    format(str,sizeof(str),formatting,getarg(posArg));
					    strins(dest,str,d,len2);
					    d+=len;
						posArg++;
						i+= 2;
					}
				}
				default:
				{
					dest[d] = msg[i];
					d++;
				}
			}
		}
		else
		{
			dest[d] = msg[i];
			d++;
		}
	}
	return SendClientMessage(playerid,color,dest);
}


stock strtolower(source[])
{//ф-ия делает все буквы в нижнем регистре
    for(new i; i < strlen(source); i++) switch(source[i]) {
        case 168: source[i] = 184;
        case 192..223: source[i] = (source[i] + 32);
        default: source[i] = tolower(source[i]);
    }
}
/*
stock ucfirst(string[])
{//ф-ия делает все буквы в нижнем регистре кроме первой
	string[0] = toupper(string[0]);
	const dist = 'A' - 'a';
	for(new i = 1, len = strlen(string), c; i < len; ++i)
	{
		if ('A' <= (c = string[i]) <= 'Z')
			c -= dist;
		string[i] = c;
	}
}*/

stock ucfirst(string[])
{//ф-ия делает все буквы в нижнем регистре кроме первой
    string[0] = toupper(string[0]);
    const dist = 'A' - 'a';
    for (new i = 1, len = strlen(string), c; i < len; ++i)
    {
        if ('A' <= string[i] <= 'Z') string[i] -= dist;
    }
}


stock ini_GetKey( line[] )//вызывается из ф-ии PlayerLogin
{   //возвращает значение до разделителя "=" во входной строке line
	new keyRes[256+1];
	keyRes[0] = 0;
    if( strfind(line, "=", true) == -1 ) return keyRes;
    strmid(keyRes, line, 0, strfind(line, "=", true), sizeof(keyRes) );
    return keyRes;
}
stock ini_GetValue( line[] )//вызывается из ф-ии PlayerLogin
{	//возвращает значение после разделителя "=" во входной строке line
	new valRes[256+1];
	valRes[0] = 0;
	if( strfind(line , "=" , true) == -1 ) return valRes;
	//strmid(valRes, line, strfind(line, "=", true)+1, strfind(line,"\n",true)-1, sizeof(valRes) );
	strmid(valRes, line, strfind(line, "=", true)+1, strfind(line,"\n",true), sizeof(valRes) );
	return valRes;
}
/*
stock strtok(const str[], &index)//Сканирует строку на наличие символа 'пробел'
//и возвращает аргумент номер которого указан в переменной (&index).
//Применяется в основном для команд, чтобы чтобы получать параметры после пробела.
//str[] - Строка, которую нужно разделить.
//&index - Номер аргумента который вы хотите вернуть.
//Возвращает  аргумент номер которого указан в в переменной &index
//stock - блоком автозамен, жрет меньше памяти
//stock - выполняется только в пределах массива
//stock - это функция компилятора, т.е. при компиляции все функции stock, а точнее в места где вы их прописали вписывается код который в них объявлен.
//public - аппаратная функция, т.е. она компилируеться как отдельный скрипт, а в места где вы её вызываете вписываеться адрес где находиться public в памяти,
//forward - это так сказать адресная книга которая при начале обработки срипта указывает адреса на ваш public
{
   new length = strlen(str);//записали длину полученной входной строки
   while ((index < length) && (str[index] <= ' ')) index++;//подсчитали сколько символов до пробела
   //если позиция символа < длины строки и позиции символа находится до пробела, то перейти на следующий
   new offset = index;//записать позицию пробела
   new result[20];//20 объявляем новую символьную переменную с размерностью 20
   while ((index < length) && (str[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
   {	//пока позиция символа меньше длины строки и символы находится за пробелом
		// и разница между позицие символа и позицией пробела < меньше пока размера строки result, т.е. меньше 20 в данном случаи
		result[index - offset] = str[index];//записали символ в ячейку со смещением на величину позиции пробела, тем самым сформировав строку после пробела
		index++;//перешли на следующий символ
   }
   result[index - offset] = EOS;//обнулили данные в строке result начиная с позиции последнего записанного символа
   return result;//возвращаем строку из символов начиная от указаной позиции до пробела
}
*/
stock strtoko(const str[], &index, seperator=' ')
{//разделяет строку str на подстроку result разделённую seperator
//print(" ");
//printf("str: '%s' index: %d seperator: '%c'", str, index, seperator);
	new length = strlen(str);//записали длину полученной входной строки
//printf("length: %d", length);
//НАХОДИМ ПОЗИЦИЮ РАЗДЕЛИТЕЛЯ
	while((index < length) && (str[index] <= seperator))
	{   //делаем пока позиция символ < длины строки и символ данной позиции <= разделителю
		index++;//подсчитали сколько символов по разделитель, включаю его позицию
//printf("str[index]: '%c'[%d]", str[index], index);
	}
	new offset = index;//записали в offset позицию разделителя,чтобы каждый раз начинать со смещением формировать подстроку
//printf("offset: %d", offset);
	//--------------------------------------------------------------------------
	new result[MAX_STRING];//объявляем новую символьную переменную с размерностью 168
//ФОРМИРУЕМ ПОДСТРОКУ, пока не достигнем конца строки
	while ((index < length) && (str[index] > seperator) && ((index - offset) < (sizeof(result)-1)))
	{   //делаем пока позиция символа меньше длины строки и символ != последнему разделителю и
// и разница между позицие символа и позицией последнего разделителя < меньше размера строки result, т.е. меньше 256 в данном случаи
		result[index - offset] = str[index];//записали символ в ячейку со смещением на величину позиции разделителя,
		//тем самым сформировав строку после разделителя
//printf("result[index - offset]: %s[%d-%d] str[index]: '%c' sizeof(result): %d", result, index, offset, str[index], sizeof(result));
		//в 1-ую ячейку пишем первый символ и т.д.
		index++;//перешли на следующий символ
	}
//ОБРЕЗАЕМ ПОДСТРОКУ от лишних пробелов
	result[index - offset] = EOS;//обнулили данные в строке result начиная с позиции последнего записанного символа
//printf("result: '%s'", result);
	return result;//возвращаем строку из символов начиная от указаной позиции до пробела
}

stock strcharsplit(const str[], &index, seperator=' ')
{
	new result[20], i = 0;
	if (index != 0 && str[index] != '\0') index++;
	while (str[index] && str[index] != seperator && str[index] != '\r' && str[index] != '\n')
	{
		result[i++] = str[index++];
	}
	return result;
}

stock split(const strsrc[], strdest[][], delimiter)
{   //разделяет первый параметр strsrc на части и заносит их во второй параметр массив
	new i, li, aNum, len;
	while(i <= strlen(strsrc))
	{   //пока i <= длины строки strsrc
	    if(strsrc[i]==delimiter || i==strlen(strsrc))
		{   //если значение strsrc[i] == '/' или  i == длине строки strsrc
	        len = strmid(strdest[aNum], strsrc, li, i, 128);//Извлекает диапазон символов из строки.
			//li - Позиция первого символа, i - Позиция последнего символа, 128 - Максимальная длина строки-назначения для копирования.
	        //записать в strdest[aNum] значение strsrc
	        strdest[aNum][len] = 0;
	        li = i+1;//
	        aNum++;//обычный счётчик
		}
		i++;
	}
	return 1;
}/*
stock token_by_delim(const str[], return_str[], delim, start_index)
{   //str[] - откуда считываем //return_str[] - куда заносим
	new x = 0;
	while(str[start_index] != EOS && str[start_index] != delim)
	{
	    return_str[x] = str[start_index];
	    x++;
	    start_index++;
	}
	return_str[x] = EOS;
	if(str[start_index] == EOS) start_index = (-1);
	return start_index;
}*/
//------------------------------------------------------------------------------
/*
stock strrest(const str[], &index)
{   //str[] - Строка, длину которой вы хотите знать в виде целого числа.
	new length = strlen(str);//Эта функция может быть использована для проверки длины указанной строки.
	while ((index < length) && (str[index] <= ' '))
	{
		index++;//Номер позиции пробела
	}
	new offset = index;//записываем позицию пробела в полученной строке
	new result[MAX_STRING];
	while ((index < length) && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = str[index];//в переменную result записать символы с позиции после пробела
		index++;
	}
	result[index - offset] = EOS;//обнулили данные в строке result начиная с позиции последнего записанного символа
	return result;
}
*/

stock replaceString(const str[], const findstr[], const replacestr[])//, size = sizeof getStr
{
	new getStr[128];//max 640
    strmid(getStr, str, 0, strlen(str));
	new start = strfind(getStr, findstr, true);
	while(start != -1)
	{
		new end = start + strlen(findstr);
		strdel(getStr, start, end);
		strins(getStr, replacestr, start);
		start = strfind(getStr, findstr, true);//, start+strlen(replacestr)
	}
	//print(getStr);
	return getStr;
}
stock findParam(const str[], const findstr[])
{
	new getStr[400+1];
	new start = strfind(str, findstr, true);
	for(new i=start; i<sizeof(getStr); i++)
	{
		if(str[i] == '\n')
		{
			strmid(getStr, str, start+strlen(findstr), i, sizeof(getStr));
			break;
		}
	}
	return getStr;
}

#define SPACE_CHARS ' ', '%', '\t', '\r', '\n'
/*
    Обрежет по обоим краям строки все пробельные символы.
-----------
    Ничего не возвращает.
*/
stock trimSideSpaces( str[] )
{
    new c, len = strlen(str);
    for( ; c < len; c++ ) // вырежем пробелы в начале
    {
        switch ( str[c] )
        {
            case SPACE_CHARS: continue;
            default:
            {
                if( c != 0 ) strmid( str, str, c, len, len );
                break;
            }
        }
    }
    for( c = len - c - 1; c >= 0; c-- ) // вырежем пробелы в конце
    {
        switch ( str[c] )
        {
            case SPACE_CHARS: continue;
            default:
            {
                str[c + 1] = 0;
                break;
            }
        }
    }
}
#define cells *4
/*
    Заменяет группы пробельных символов на единичные пробелы
-----------
    Ничего не возвращает
*/
stock spaceGroupsToSpaces( str[] )
{
    new len = strlen(str), c = len - 1, spaces;
    for( ; c >= 0; c-- )
    {
        switch ( str[c] )
        {
            case SPACE_CHARS : spaces++;
            default :
            {
                if( spaces > 1 )
                {
                    memcpy( str, str[c + spaces + 1], (c + 2) cells, (len - c - spaces - 1) cells, len );
                    len -= spaces - 1;
                }
                if( spaces > 0 )
                {
                    str[c + 1] = ' ';
                    spaces        =  0;
                }
            }
        }
    }
    if( spaces > 1 )
    {
        memcpy( str, str[c + spaces + 1], (c + 2) cells, (len - c - spaces - 1) cells, len );
        len -= spaces - 1;
    }
    if( spaces > 0 ) str[c + 1] = ' ';
    str[len] = 0;
}
#undef SPACE_CHARS


stock RusToGame(const strrus[])
{
	new result[256+1];
	for(new i=0; i < 256; i++)
	{
		switch(strrus[i])
		{
			case 'а':result[i] = 'a';
			case 'А':result[i] = 'A';
			case 'б':result[i] = '—';
			case 'Б':result[i] = 'Ђ';
			case 'в':result[i] = 'ў';
			case 'В':result[i] = '‹';
			case 'г':result[i] = '™';
			case 'Г':result[i] = '‚';
			case 'д':result[i] = 'љ';
			case 'Д':result[i] = 'ѓ';
			case 'е':result[i] = 'e';
			case 'Е':result[i] = 'E';
			case 'ё':result[i] = 'e';
			case 'Ё':result[i] = 'E';
			case 'ж':result[i] = '›';
			case 'Ж':result[i] = '„';
			case 'з':result[i] = 'џ';
			case 'З':result[i] = '€';
			case 'и':result[i] = 'њ';
			case 'И':result[i] = '…';
			case 'й':result[i] = 'ќ';
			case 'Й':result[i] = '…';
			case 'к':result[i] = 'k';
			case 'К':result[i] = 'K';
			case 'л':result[i] = 'ћ';
			case 'Л':result[i] = '‡';
			case 'м':result[i] = 'Ї';
			case 'М':result[i] = 'M';
			case 'н':result[i] = '®';
			case 'Н':result[i] = '­';
			case 'о':result[i] = 'o';
			case 'О':result[i] = 'O';
			case 'п':result[i] = 'Ј';
			case 'П':result[i] = 'Њ';
			case 'р':result[i] = 'p';
			case 'Р':result[i] = 'P';
			case 'с':result[i] = 'c';
			case 'С':result[i] = 'C';
			case 'т':result[i] = '¦';
			case 'Т':result[i] = 'Џ';
			case 'у':result[i] = 'y';
			case 'У':result[i] = 'Y';
			case 'ф':result[i] = '';
			case 'Ф':result[i] = 'Ѓ';
			case 'х':result[i] = 'x';
			case 'Х':result[i] = 'X';
			case 'ц':result[i] = ' ';
			case 'Ц':result[i] = '‰';
			case 'ч':result[i] = '¤';
			case 'Ч':result[i] = 'Ќ';
			case 'ш':result[i] = 'Ґ';
			case 'Ш':result[i] = 'Ћ';
			case 'щ':result[i] = 'Ў';
			case 'Щ':result[i] = 'Љ';
			case 'ь':result[i] = '©';
			case 'Ь':result[i] = '’';
			case 'ъ':result[i] = 'ђ';
			case 'Ъ':result[i] = '§';
			case 'ы':result[i] = 'Ё';
			case 'Ы':result[i] = '‘';
			case 'э':result[i] = 'Є';
			case 'Э':result[i] = '“';
			case 'ю':result[i] = '«';
			case 'Ю':result[i] = '”';
			case 'я':result[i] = '¬';
			case 'Я':result[i] = '•';
			default:result[i] = strrus[i];
		}
	}
	return result;
}

//[16:14:38] Подсказка: нажми {FFFF00}ЊPOЂE‡{FFFFFF}, чтобы спрятать телефон.
stock GameToRus(const strrus[])
{
	new result[256+1];
	for(new i=0; i < 256; i++)
	{
		switch(strrus[i])
		{
			case 'a':result[i] = 'а';
			case 'A':result[i] = 'А';
			case '—':result[i] = 'б';
			case 'Ђ':result[i] = 'Б';
			case 'ў':result[i] = 'в';
			case '‹':result[i] = 'В';
			case '™':result[i] = 'г';
			case '‚':result[i] = 'Г';
			case 'љ':result[i] = 'д';
			case 'ѓ':result[i] = 'Д';
			case 'e':result[i] = 'е';
			case 'E':result[i] = 'Е';
case 'ё':result[i] = 'ё';
case 'Ё':result[i] = 'Ё';
			case '›':result[i] = 'ж';
			case '„':result[i] = 'Ж';
			case 'џ':result[i] = 'з';
			case '€':result[i] = 'З';
			case 'њ':result[i] = 'и';
			case '…':result[i] = 'И';
			case 'ќ':result[i] = 'й';
			case '†':result[i] = 'Й';
			case 'k':result[i] = 'к';
			case 'K':result[i] = 'К';
			case 'ћ':result[i] = 'л';
			case '‡':result[i] = 'Л';
			case 'Ї':result[i] = 'м';
			case '–':result[i] = 'М';
			case '®':result[i] = 'н';
			case '­':result[i] = 'Н';
			case 'o':result[i] = 'о';
			case 'O':result[i] = 'О';
			case 'Ј':result[i] = 'п';
			case 'Њ':result[i] = 'П';
			case 'p':result[i] = 'р';
			case 'P':result[i] = 'Р';
			case 'c':result[i] = 'с';
			case 'C':result[i] = 'С';
			case '¦':result[i] = 'т';
			case 'Џ':result[i] = 'Т';
			case 'y':result[i] = 'у';
			case 'Y':result[i] = 'У';
			case '':result[i] = 'ф';
			case 'Ѓ':result[i] = 'Ф';
			case 'x':result[i] = 'х';
			case 'X':result[i] = 'Х';
			case ' ':result[i] = 'ц';
			case '‰':result[i] = 'Ц';
			case '¤':result[i] = 'ч';
			case 'Ќ':result[i] = 'Ч';
			case 'Ґ':result[i] = 'ш';
			case 'Ћ':result[i] = 'Ш';
			case 'Ў':result[i] = 'щ';
			case 'Љ':result[i] = 'Щ';
			case '©':result[i] = 'ь';
			case '’':result[i] = 'Ь';
			case 'ђ':result[i] = 'ъ';
			case '§':result[i] = 'Ъ';
			case '‘':result[i] = 'Ы';
			case 'Є':result[i] = 'э';
			case '“':result[i] = 'Э';
			case '«':result[i] = 'ю';
			case '”':result[i] = 'Ю';
			case '¬':result[i] = 'я';
			case '•':result[i] = 'Я';
			default: result[i] = strrus[i];
		}
	}
	return result;
}

stock Translate(str[])
{
    new retstr[512];
    for(new i=0;i<strlen(str);i++)
    {
        switch(str[i])
        {
            case 'А':strcat(retstr,"A");
            case 'Б':strcat(retstr,"B");
            case 'В':strcat(retstr,"V");
            case 'Г':strcat(retstr,"G");
            case 'Д':strcat(retstr,"D");
            case 'Е':strcat(retstr,"E");
            case 'Ё':strcat(retstr,"Jo");
            case 'Ж':strcat(retstr,"Zh");
            case 'З':strcat(retstr,"Z");
            case 'И':strcat(retstr,"I");
            case 'Й':strcat(retstr,"J");
            case 'К':strcat(retstr,"K");
            case 'Л':strcat(retstr,"L");
            case 'М':strcat(retstr,"M");
            case 'Н':strcat(retstr,"N");
            case 'О':strcat(retstr,"O");
            case 'П':strcat(retstr,"P");
            case 'Р':strcat(retstr,"R");
            case 'С':strcat(retstr,"S");
            case 'Т':strcat(retstr,"T");
            case 'У':strcat(retstr,"U");
            case 'Ф':strcat(retstr,"F");
            case 'Х':strcat(retstr,"H");
            case 'Ц':strcat(retstr,"C");
            case 'Ч':strcat(retstr,"Ch");
            case 'Ш':strcat(retstr,"Sh");
            case 'Щ':strcat(retstr,"Shh");
            case 'Ь':strcat(retstr,"#");
            case 'Ы':strcat(retstr,"Y");
            case 'Ъ':strcat(retstr,"'");
            case 'Э':strcat(retstr,"Je");
            case 'Ю':strcat(retstr,"Ju");
            case 'Я':strcat(retstr,"Ja");
            case 'а':strcat(retstr,"a");
            case 'б':strcat(retstr,"b");
            case 'в':strcat(retstr,"v");
            case 'г':strcat(retstr,"g");
            case 'д':strcat(retstr,"d");
            case 'е':strcat(retstr,"e");
            case 'ё':strcat(retstr,"jo");
            case 'ж':strcat(retstr,"zh");
            case 'з':strcat(retstr,"z");
            case 'и':strcat(retstr,"i");
            case 'й':strcat(retstr,"j");
            case 'к':strcat(retstr,"k");
            case 'л':strcat(retstr,"l");
            case 'м':strcat(retstr,"m");
            case 'н':strcat(retstr,"n");
            case 'о':strcat(retstr,"o");
            case 'п':strcat(retstr,"p");
            case 'р':strcat(retstr,"r");
            case 'с':strcat(retstr,"s");
            case 'т':strcat(retstr,"t");
            case 'у':strcat(retstr,"u");
            case 'ф':strcat(retstr,"f");
            case 'х':strcat(retstr,"h");
            case 'ц':strcat(retstr,"c");
            case 'ч':strcat(retstr,"ch");
            case 'ш':strcat(retstr,"sh");
            case 'щ':strcat(retstr,"shh");
            case 'ъ':strcat(retstr,"#");
            case 'ы':strcat(retstr,"y");
            case 'ь':strcat(retstr,"'");
            case 'э':strcat(retstr,"je");
            case 'ю':strcat(retstr,"ju");
            case 'я':strcat(retstr,"ja");
            case ' ':strcat(retstr," ");
            case '0':strcat(retstr,"0");
            case '1':strcat(retstr,"1");
            case '2':strcat(retstr,"2");
            case '3':strcat(retstr,"3");
            case '4':strcat(retstr,"4");
            case '5':strcat(retstr,"5");
            case '6':strcat(retstr,"6");
            case '7':strcat(retstr,"7");
            case '8':strcat(retstr,"8");
            case '9':strcat(retstr,"9");
            case 'a':strcat(retstr,"a");
            case 'b':strcat(retstr,"b");
            case 'c':strcat(retstr,"c");
            case 'd':strcat(retstr,"d");
            case 'e':strcat(retstr,"e");
            case 'f':strcat(retstr,"f");
            case 'g':strcat(retstr,"g");
            case 'h':strcat(retstr,"h");
            case 'i':strcat(retstr,"i");
            case 'j':strcat(retstr,"j");
            case 'k':strcat(retstr,"k");
            case 'l':strcat(retstr,"l");
            case 'm':strcat(retstr,"m");
            case 'n':strcat(retstr,"n");
            case 'o':strcat(retstr,"o");
            case 'p':strcat(retstr,"p");
            case 'q':strcat(retstr,"q");
            case 'r':strcat(retstr,"r");
            case 's':strcat(retstr,"s");
            case 't':strcat(retstr,"t");
            case 'u':strcat(retstr,"u");
            case 'v':strcat(retstr,"v");
            case 'w':strcat(retstr,"w");
            case 'x':strcat(retstr,"x");
            case 'y':strcat(retstr,"y");
            case 'z':strcat(retstr,"z");
            case 'A':strcat(retstr,"A");
            case 'B':strcat(retstr,"B");
            case 'C':strcat(retstr,"C");
            case 'D':strcat(retstr,"D");
            case 'E':strcat(retstr,"E");
            case 'F':strcat(retstr,"F");
            case 'G':strcat(retstr,"G");
            case 'H':strcat(retstr,"H");
            case 'I':strcat(retstr,"I");
            case 'J':strcat(retstr,"J");
            case 'K':strcat(retstr,"K");
            case 'L':strcat(retstr,"L");
            case 'M':strcat(retstr,"M");
            case 'N':strcat(retstr,"N");
            case 'O':strcat(retstr,"O");
            case 'P':strcat(retstr,"P");
            case 'Q':strcat(retstr,"Q");
            case 'R':strcat(retstr,"R");
            case 'S':strcat(retstr,"S");
            case 'T':strcat(retstr,"T");
            case 'U':strcat(retstr,"U");
            case 'V':strcat(retstr,"V");
            case 'W':strcat(retstr,"W");
            case 'X':strcat(retstr,"X");
            case 'Y':strcat(retstr,"Y");
            case 'Z':strcat(retstr,"Z");
            case '!':strcat(retstr,"!");
            case '@':strcat(retstr,"@");
            case '#':strcat(retstr,"#");
            case '$':strcat(retstr,"$");
            case '%':strcat(retstr,"%");
            case '^':strcat(retstr,"^");
            case '&':strcat(retstr,"&");
            case '*':strcat(retstr,"*");
            case '(':strcat(retstr,"(");
            case ')':strcat(retstr,")");
            case '-':strcat(retstr,"-");
            case '_':strcat(retstr,"_");
            case '=':strcat(retstr,"=");
            case '+':strcat(retstr,"+");
            case ';':strcat(retstr,";");
            case ':':strcat(retstr,":");
            case '|':strcat(retstr,"|");
            case '[':strcat(retstr,"[");
            case ']':strcat(retstr,"]");
            case '{':strcat(retstr,"{");
            case '}':strcat(retstr,"}");
            case '.':strcat(retstr,".");
            case ',':strcat(retstr,",");
            case '?':strcat(retstr,"?");
            case '/':strcat(retstr,"/");
            default: strcat(retstr,str[i]);
        }
    }
    return retstr;
}

stock RemoveCapsLock(str[])
{
    new i, ch;
    while ((ch = str[i++]))
    {
        if (ch >= 'A' && ch <= 'Z') str[i] = tolower(ch);
    }
    return 1;
}

/*
Tested:
printf("%s", NiceMoney(1));
printf("%s", NiceMoney(12));
printf("%s", NiceMoney(123));
printf("%s", NiceMoney(1234));
printf("%s", NiceMoney(12345));
printf("%s", NiceMoney(123456));
printf("%s", NiceMoney(1234567));
printf("%s", NiceMoney(12345678));
printf("%s", NiceMoney(123456789));
printf("%s", NiceMoney(1234567890));
printf("%s", NiceMoney(-1));
printf("%s", NiceMoney(-12));
printf("%s", NiceMoney(-123));
printf("%s", NiceMoney(-1234));
printf("%s", NiceMoney(-12345));
printf("%s", NiceMoney(-123456));
printf("%s", NiceMoney(-1234567));
printf("%s", NiceMoney(-12345678));
printf("%s", NiceMoney(-123456789));
printf("%s", NiceMoney(-1234567890));

Example:
[01:27:05] 1
[01:27:05] 12
[01:27:05] 123
[01:27:05] 1,234
[01:27:05] 12,345
[01:27:05] 123,456
[01:27:05] 1,234,567
[01:27:05] 12,345,678
[01:27:05] 123,456,789
[01:27:05] 1,234,567,890
[01:27:05] -1
[01:27:05] -12
[01:27:05] -123
[01:27:05] -1,234
[01:27:05] -12,345
[01:27:05] -123,456
[01:27:05] -1,234,567
[01:27:05] -12,345,678
[01:27:05] -123,456,789
[01:27:05] -1,234,567,890
*/
stock NiceMoney(amount, sep[] = ".")
//stock NiceMoney(amount, sep[] = " ")
{
    new strtmp[16],
        negativ = 0;
    if(amount < 0) negativ = 1;
    format(strtmp, sizeof(strtmp), "%d", amount);
    new
        lenght = strlen(strtmp);
    while((lenght -= 3) > negativ) strins(strtmp, sep, lenght);
    return strtmp;
}

stock ReturnColor(const color) // from Y_Less
{
    new strtmp[32];
    format(strtmp, sizeof(strtmp), "{%06x}", color);
    //print(strtmp);
    return strtmp;
}

stock ReturnServerStringVar(const varname[])
{
    new strtmp[64];
    GetServerVarAsString(varname, strtmp, sizeof(strtmp));
    return strtmp;
}

//-------------------------------------------
// Sends a list of all PVars to the player as
// client messages.

stock SendPVarListToPlayer(playerid)
{
    new ubound = GetPVarsUpperIndex(playerid);
	new x=0;
	new name[40+1];
	new line[128+1];

    SendClientMessage(playerid, 0xF000F0F0, "---Player Vars List---");
	while(x != ubound) {
		if(GetPVarNameAtIndex(playerid, x,name,40)) {
			if(Util_GetPVarEntryAsString(playerid, name,line,128)) {
                 SendClientMessage(playerid, 0xFFFFFFFF,line);
			}
		}
		x++;
	}
}

//-------------------------------------------
// return PVar entry as 'name'='value' str
stock Util_GetPVarEntryAsString(playerid, name[], ret[], len)
{
	new Float:fValue;
	new iValue;
	new szStrValue[1024+1]; // this might require greater size if you store large str in PVars
	new type;
    ret[0] = EOS;

  	type = GetPVarType(playerid, name);
	if(type != PLAYER_VARTYPE_NONE) {
		switch(type)
		{
			case PLAYER_VARTYPE_STRING:
			{
				GetPVarString(playerid, name,szStrValue,1024);
				format(ret,len,"%s=%s",name,szStrValue);
			}
			case PLAYER_VARTYPE_INT:
			{
				iValue = GetPVarInt(playerid, name);
				format(ret,len,"%s=%d",name,iValue);
			}
			case PLAYER_VARTYPE_FLOAT:
			{
			    fValue = GetPVarFloat(playerid, name);
				format(ret,len,"%s=%f",name,fValue);
			}
		}
		return 1;
	}
	return 0;
}


/*
stock ReturnUser(text[], playerid = INVALID_PLAYER_ID)
{
	new pos = 0;
	while(text[pos] < 0x21) // Strip out leading spaces //Удаляет свободное место
	{
		if(text[pos] == 0) return INVALID_PLAYER_ID; // No passed text //Нет текста на входе
		pos++;
	}
	new userid = INVALID_PLAYER_ID;
	if(IsNumeric(text[pos])) // Check whole passed str - Проверьте целую прошедшую строку
	{   //если строка представлена в виде числа
		// If they have a numeric name you have a problem (although names are checked on id failure)
		// Если у них есть числовое имя у вас есть проблема (хотя имена проверены в неудаче)
		userid = strval(text[pos]);
		if(userid >= 0 && userid < MAX_PLAYERS)// && !IsPlayerNPC(userid)
		{
			if(!IsPlayerConnected(userid))	userid = INVALID_PLAYER_ID;
			else return userid; // A player was found
		}
	}
	// They entered [part of] a name or the id search failed (check names just incase)
	new len = strlen(text[pos]);
	new count = 0;
	new name[MAX_PLAYER_NAME+1];
	//foreach(Player, i)
	//for(new i=0; i<GetMaxPlayers(); i++)	{
	for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnected(i) || IsPlayerNPC(i)) continue;
		GetPlayerName(i, name, sizeof(name));
		if(strcmp(name, text[pos], true, len) == 0) // Check segment of name
		{   //проверяем совпадает ли введенное имя с одним из онлайн игроков
			if(len == strlen(name)) // Exact match //более Точная проверка
			{   //если длина также совпадает
				return i; // Return the exact player on an exact match
				//Возвращает точного указанного игрока ID и выходит из ф-ии
			}
			else // Partial match //Частичная проверка
			//В противном случае если есть два игрока:
			//Me и MeYou всякий раз, когда Вы ввели Me это должно найти оба
			//И никогда не быть способным возвращать просто Me id
			{   //если введена не полная часть имени, то совпадение частичное
				count++;
				userid = i;//записываем userid =
			}
		}
	}
	if(count != 1)
	{
		if(playerid != INVALID_PLAYER_ID)// && !IsPlayerNPC(playerid)
		{
			//if(count) ABroadCast(COLOR_RED, "Error: Multiple users found, please narrow earch", 1);
			//else ABroadCast(COLOR_RED, "Error: No matching user found", 1);
			if(count) SendClientMessageToAll(0xFF0000FF, "Error: Multiple users found, please narrow earch");
			else SendClientMessageToAll(0xFF0000FF, "Error: No matching user found");
		}
		userid = INVALID_PLAYER_ID;
	}
	return userid; // INVALID_USER_ID for bad return
}
*/

stock SetPlayerGameTextScale(playerid, const gametext[], indicator, limit)
{   // 0 // 2000
	if(!IsPlayerConnectedEx(playerid)) return 1;
	//new timers = GetTickCount();
//printf("1. indicator:%d limit:%d", indicator, limit);
	new str1[16], str2[16], str3[16], str4[16], str5[16], str6[16];
	new strtmp[70+24+16*6];

	new percent;
	new maximum = 55;//максимальное кол-во вмещаемых символов
    if(indicator > limit) percent = maximum;//limit;
    else if(indicator < 0) percent = 0;
    else percent = indicator*maximum/limit;

	for(new p=0; p<percent; p++)
	{
	    if(p <= 1*maximum/6) { strins(str1, "I", strlen(str1)); }
	    else if(p > (1*maximum/6) && p < (2*maximum/6) ) { strins(str2, "I", strlen(str2)); }
	    else if(p > (2*maximum/6) && p < (3*maximum/6) ) { strins(str3, "I", strlen(str3)); }
	    else if(p > (3*maximum/6) && p < (4*maximum/6) ) { strins(str4, "I", strlen(str4)); }
	    else if(p > (4*maximum/6) && p < (5*maximum/6) ) { strins(str5, "I", strlen(str5)); }
	    else if(p >= 5*maximum/6) { strins(str6, "I", strlen(str6)); }
	}
//printf("2. indicator:%d limit:%d", indicator, limit);
	//format(strtmp, sizeof(strtmp), "~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~r~%s~y~%s~g~%s", gametext, str1, str2, str3);
	format(strtmp, sizeof(strtmp), "~n~~n~~n~~n~~n~~n~~n~~n~~n~ ~w~%s~n~~r~%s~y~%s~g~%s~p~%s~b~%s~w~%s", gametext, str1, str2, str3, str4, str5, str6);
//красный-оранжевый-жёлтый-салатовый-зелёный-синий-белый
//r-y-g-p-b-w
	//GameTextForPlayer(playerid, strtmp, 10000, 3);
	GameTextForPlayer(playerid, strtmp, 3000, 3);
	//PlaySoundForPlayer(playerid, SOUND_AMMUNATION_BUY_WEAPON);
//printf("3. indicator:%d limit:%d", indicator, limit);
	//TestLog(OPTIM, "SetPlayerGameTextScale", GetTickCount(), timers);//new timers = GetTickCount();
	return 1;
}

stock FixHour(&hour)//получает текущий час
{   //для 24-часового формата времени
	hour = hour + timeshift;//к текущему часу добавить час корректировки на часовой пояс
	//22+3 = 25
	if(hour < 0) hour = hour+24;
	else if(hour > 23)	hour = hour-24;
	//25 > 12 hour = 25-24 = 1
	//shifthour = hour;//записали в shifthour скоректированный час
}


stock IsPlayerInZone(playerid, zoneid)//для УСТАНОВКИ ИКОНОК НА КАРТЕ
{    //если игрок находится в кубе ограниченном координатами из массива zones
	if( !IsPlayerConnectedEx(playerid) ) return 0;
	if(zoneid < 0 || zoneid >= MAX_ZONES) return 0;
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	if(x >= zones[zoneid][zone_minx] && x < zones[zoneid][zone_maxx]
	&& y >= zones[zoneid][zone_miny] && y < zones[zoneid][zone_maxy]
	&& z >= zones[zoneid][zone_minz] && z < zones[zoneid][zone_maxz]
	&& z < 900.0) {
//ИНФОРМИРОВАНИЕ
//////new strings[MAX_STRING];
//format(strings, sizeof(strings), "3. playerid: %d, zoneid: %d, X:%.4f, Y:%.4f, Z:%.4f", playerid, zoneid, x,y,z);
//SendClientMessageEx(playerid, COLOR_PINK, strings);
//SendClientMessageToAll(COLOR_PINK, strings);
		return 1;
	}
	return 0;
}
stock IsPlayerInRegion(playerid, regionid)//вызывается по команде giveturf
{   //если игрок находится в координатах по строке turfid из массива regions
	if( !IsPlayerConnectedEx(playerid) )return 0;
	if(regionid < 0 || regionid >= MAX_TURFS) return 0;
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x,y,z);
	if(x >= regions[regionid][region_minx] && x < regions[regionid][region_maxx]
	&& y >= regions[regionid][region_miny] && y < regions[regionid][region_maxy]
	&& z >= regions[regionid][region_minz] && z < regions[regionid][region_maxz]
	&& z < 900.0) { return 1; }
	return 0;
}
stock IsVehicleInZone(vehicleid, regionid)//для УСТАНОВКИ ИКОНОК НА КАРТЕ
{    //если игрок находится в кубе ограниченном координатами из массива zones
	if(vehicleid <= 0) return 0;
	if(regionid < 0 || regionid >= MAX_TURFS) return 0;
	new Float:x, Float:y, Float:z;
	GetVehiclePos(vehicleid, x, y, z);
	if(x >= regions[regionid][region_minx] && x < regions[regionid][region_maxx]
	&& y >= regions[regionid][region_miny] && y < regions[regionid][region_maxy]
	&& z >= regions[regionid][region_minz] && z < regions[regionid][region_maxz]
	&& z < 900.0) { return 1; }
	return 0;
}
stock IsPointInZone(Float:x, Float:y, Float:z, zoneid)//для gDocuments
{    //если точка(дом) находится в координатах по строке zoneid из массива zones
	if(zoneid < 0 || zoneid >= MAX_ZONES) return 0;
	if(x >= zones[zoneid][zone_minx] && x < zones[zoneid][zone_maxx]
	&& y >= zones[zoneid][zone_miny] && y < zones[zoneid][zone_maxy]
	&& z >= zones[zoneid][zone_minz] && z < zones[zoneid][zone_maxz]
	&& z < 900.0) { return 1; }
	return 0;
}
stock IsPointInRegion(Float:x, Float:y, Float:z, regionid)//возвращает верно каждую секунду
{    //если очка(дом) находится в координатах по строке regionid из массива regions
	if(regionid < 0 || regionid >= MAX_TURFS) return 0;
	if(x >= regions[regionid][region_minx] && x < regions[regionid][region_maxx]
	&& y >= regions[regionid][region_miny] && y < regions[regionid][region_maxy]
	&& z >= regions[regionid][region_minz] && z < regions[regionid][region_maxz]
	&& z < 900.0) { return 1; }
	return 0;
}
stock GetPlayerInZoneName(playerid)
{
	new tcity[20];
	for(new j=0; j<MAX_ZONES; j++)
	{
		if( IsPlayerInZone(playerid, j) )
		{
			strmid(tcity, zones[j][zone_name], 0, strlen(zones[j][zone_name]), 20);
			break;
		}
	}
	return tcity;
}
stock GetPointInZoneName(Float:x, Float:y, Float:z)
{
	new tcity[20];
	for(new j=0; j<MAX_ZONES; j++)
	{
		if( IsPointInZone(x, y, z, j) )
		{
			strmid(tcity, zones[j][zone_name], 0, strlen(zones[j][zone_name]), 20);
			break;
		}
	}
	return tcity;
}



stock SendPlayerStateMessage(playerid)
{
	new strstate[64];
    switch(GetPlayerState(playerid))
	{
	        case PLAYER_STATE_ONFOOT: strstate = "\n{0080FF}Игрок находится на земле";
	        case PLAYER_STATE_DRIVER: strstate = "\n{0080FF}Игрок находится за рулём транспортного средства";//58
	        case PLAYER_STATE_PASSENGER: strstate = "\n{0080FF}Игрок находится на пассажирском сидении";
	        case PLAYER_STATE_EXIT_VEHICLE: strstate = "\n{0080FF}Игрок выходит из машины";
	        case PLAYER_STATE_ENTER_VEHICLE_DRIVER: strstate = "\n{0080FF}Игрок садится в машину на водительское сиденье";
	        case PLAYER_STATE_ENTER_VEHICLE_PASSENGER: strstate = "\n{0080FF}Игрок садится в машину на пассажирское сиденье";
	        case PLAYER_STATE_WASTED: strstate = "\n{0080FF}Игрок находится в розыске";
	        case PLAYER_STATE_SPAWNED: strstate = "\n{0080FF}Игрок спаунится";
	        case PLAYER_STATE_SPECTATING: strstate = "\n{0080FF}Игрок находится в режиме наблюдателя";
	        case PLAYER_STATE_KILLED: strstate = "\n{0080FF}Игрок был убит";
			default: strstate = "\n{0080FF}Unknown";
	}
	return strstate;
}

stock SendDeathReasonMessage(playerid, killerid, reason)
{
	new strtmp[44+40], deathreason[40];
    switch(reason)
	{
        case 0: deathreason = "Кулак";
        case 1: deathreason = "Кастет";
        case 2: deathreason = "Клюшка для гольфа";
		case 3: deathreason = "Резиновая дубинка  ";
		case 4: deathreason = "Нож";
		case 5: deathreason = "Бита";
		case 6: deathreason = "Лопата";
		case 7: deathreason = "Кий";
		case 8: deathreason = "Катана";
		case 9: deathreason = "Пила";
		case 10: deathreason = "Большой синий фалоиммитатор";
		case 11: deathreason = "Маленький светло-зелёный фалоиммитатор";
		case 12: deathreason = "Большой серый фалоиммитатор";
		case 13: deathreason = "Маленький деревянный фалоиммитатор";
		case 14: deathreason = "Цветы";
		case 15: deathreason = "Трость";
		case 16: deathreason = "Граната";
		case 17: deathreason = "Дымовая шашка";
		case 18: deathreason = "Коктейль Молотова";
		case 19: deathreason = "Ракета";
		case 20: deathreason = "Ракета";
		case 21: deathreason = "Ракета";
		case 22: deathreason = "Пистолет";
		case 23: deathreason = "Пистолет с глушителем";
		case 24: deathreason = "Пустынный орёл";
		case 25: deathreason = "Дробовик";
		case 26: deathreason = "Обрез";
		case 27: deathreason = "Военный дробовик";
		case 28: deathreason = "Uzi";
		case 29: deathreason = "MP5";
		case 30: deathreason = "AK-47";
		case 31: deathreason = "M4/Seasparrow/Rustler";
		case 32: deathreason = "TEC-9";
		case 33: deathreason = "Винтовка";
		case 34: deathreason = "Снайперская винтовка";
		case 35: deathreason = "Ракетница";
		case 36: deathreason = "Ракетница с тепловым наведением";
		case 37: deathreason = "Сгорел";
		case 38: deathreason = "Миниган/Hunter";
		case 39: deathreason = "Взрывпакет";
		case 40: deathreason = "Детонатор для взрывпакетов";
		case 41: deathreason = "Баллончик";
		case 42: deathreason = "Огнетушитель";
		case 43: deathreason = "Фотоаппарат";
		case 44: deathreason = "Очки ночного видения";
		case 45: deathreason = "Инфракрасные очки";
		case 46: deathreason = "Парашют";
		case 47: deathreason = "Fake Pistol";
		case 49: deathreason = "Сбила машина/Задавил Вертолёт";
		case 50: deathreason = "Задавлен машиной/Зарезан Лопастями";
		case 51: deathreason = "Взорвался/Rhino";
		case 52: deathreason = "Пулемёт(вертолёта)";//с полицейского вертолёта
		case 53: deathreason = "Утонул";
		case 54: deathreason = "Упал";
		case 57: deathreason = "любой";
		case 200: deathreason = "Присоединился к игре";
		case 201: deathreason = "Вышел из игры";
		case 255: deathreason = "Умер собственной смертью";
		default: deathreason = "Unknown";
	}
	format(strtmp, sizeof(strtmp), "player:%s[%d], killer:%s[%d], reason:%s[%d]",
		PlayerName(playerid), playerid, PlayerName(killerid), killerid, deathreason, reason);
   	return strtmp;
}

//==============================================================================
//Данные нужно кодировать.
//Фукнции шифрации:
stock encode_panels(flp, frp, rlp, rrp, windshield, front_bumper, rear_bumper)
{
	return flp | (frp << 4) | (rlp << 8) | (rrp << 12) | (windshield << 16) | (front_bumper << 20) | (rear_bumper << 24);
}
stock encode_doors(bonnet, boot, driver_door, passenger_door)
{
	//#pragma unused behind_driver_door
	//#pragma unused behind_passenger_door
	// will be modified once again, when rear doors are synced.
	return bonnet | (boot << 8) | (driver_door << 16) | (passenger_door << 24);
}
stock encode_lights(light1, light2, light3, light4)
{
	return light1 | (light2 << 1) | (light3 << 2) | (light4 << 3);
}
stock encode_tires(tire1, tire2, tire3, tire4)
{
	return tire1 | (tire2 << 1) | (tire3 << 2) | (tire4 << 3);
}
// специально для байков
stock encode_tires_bike(rear, front)
{
	return rear | (front << 1);
}
//#pragma unused encode_tires_bike
//------------------------------------------------------------------------------
//Данные будут кодированы, это сделано для экономии трафика.
//Функции дешифрации:
stock decode_panels(panels,&flp,&frp,&rlp,&rrp,&windshield,&front_bumper,&rear_bumper)
{
	flp = panels >> 0 & 0xF; // передняя левая панель
	frp = panels >> 4 & 0xF; // передняя правая панель
	rlp = panels >> 8 & 0xF; // задняя левая панель
	rrp = panels >> 12 & 0xF; // задняя правая панель
	windshield = panels >> 16 & 0xF; // ветровое стекло(переднее если кто не понял)
	front_bumper = panels >> 20 & 0xF; // передний бампер
	rear_bumper = panels >> 24 & 0xF; // задний бампер
}
stock decode_doors(doors,&driver_door,&passenger_door,&bonnet,&boot)
{
	bonnet = doors & 0x7; // капот
	boot = doors >> 8 & 0x7; // багажник
	driver_door = doors >> 16 & 0x7; // водительская дверь
	passenger_door = doors >> 24 & 0x7; // пассажирская дверь
}
stock decode_lights(lights,&light1,&light2,&light3,&light4)
{
	light1 = lights >> 0 & 0x1; // передняя левая фара
	light2 = lights >> 1 & 0x1; // не может повредиться
	light3 = lights >> 2 & 0x1; // передняя правая фара
	light4 = lights >> 3 & 0x1; // не может повредиться
}
stock decode_tires(tires,&tyre1,&tyre2,&tyre3,&tyre4)
{
	tyre1 = tires >> 0 & 0x1; // задняя правая(на байке задняя)
	tyre2 = tires >> 1 & 0x1; // передняя правая(на байке передняя)
	tyre3 = tires >> 2 & 0x1; // задняя левая
	tyre4 = tires >> 3 & 0x1; // передняя левая
}
//==============================================================================

stock HexToInt(string[])
{
    if(!string[0]) return 0;
    new cur = 1, res = 0;
    for(new i = strlen(string); i > 0; i--)
    {
        res += cur * (string[i - 1] - ((string[i - 1] < 58) ? (48) : (55)));
        cur = cur * 16;
    }
    return res;
}

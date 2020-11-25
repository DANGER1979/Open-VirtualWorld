
//ВНИМАНИЕ: обязательно наличие папки Logs со всеми логами в ней
//##############################################################################//
//                                                                              //
//                            ИДЕНТИФИКАТОРЫ ЛОГОВ                              //
//                                                                              //
//##############################################################################//
enum
{
	CONTRACT,
	ADMINLOG,
	WARN,
	CHEAT,
	TIMEOUT,
	PMS,
	CHAT,
	PAY,
	BUY,
	INKASS,
	RATE,
	KILL,
	LOGIN,
	KICK,
	BAN,
	OFFLINE,
	DEATH,
	SPAWN,
	INVITE,
	ERROR,
	PACKET,
	OPTIM,
	CRASH,
	CRIMINAL,
	FAMILY,
	JOB,
	TRUCK,
	DONAT,
	VEHLOG
}

//##############################################################################//
//                                                                              //
//                                 ЛОГИРОВАНИЕ                                  //
//                                                                              //
//##############################################################################//




//для настроек лог
stock Log(nam, const strLogs[])
{   //для ведения лога //strLogs не более 200
	if(!LOGS) return 1;
	new File:lFile;
	new strL[256+1];//42 + 2+2+4+2+2+2 //MAX_STRING
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld; getdate(ly,lmm,ld);
	if(nam == ADMINLOG)
	{
  		format(strL, sizeof(strL), " [%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly, lH,lM,lS, strLogs);
		if( !fexist("Logs/adminka.log") ) lFile = fopen("Logs/adminka.log", io_write);
		else lFile = fopen("Logs/adminka.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == WARN)
	{
  		format(strL, sizeof(strL), " [%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly, lH,lM,lS, strLogs);
		if( !fexist("Logs/warn.log") ) lFile = fopen("Logs/warn.log", io_write);
		else lFile = fopen("Logs/warn.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == CHEAT)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/cheats.log") ) lFile = fopen("Logs/cheats.log", io_write);
		else lFile = fopen("Logs/cheats.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == TIMEOUT)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/timeout.log") ) lFile = fopen("Logs/timeout.log", io_write);
		else lFile = fopen("Logs/timeout.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == PMS)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/pms.log") ) lFile = fopen("Logs/pms.log", io_write);
		else lFile = fopen("Logs/pms.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == CHAT)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/chat.log") ) lFile = fopen("Logs/chat.log", io_write);
		else lFile = fopen("Logs/chat.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == KILL)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/kills.log") ) lFile = fopen("Logs/kills.log", io_write);
		else lFile = fopen("Logs/kills.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == PAY)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/pay.log") ) lFile = fopen("Logs/pay.log", io_write);
		else lFile = fopen("Logs/pay.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == BUY)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/buy.log") ) lFile = fopen("Logs/buy.log", io_write);
		else lFile = fopen("Logs/buy.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == INKASS)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/inkassator.log") ) lFile = fopen("Logs/inkassator.log", io_write);
		else lFile = fopen("Logs/inkassator.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == KICK)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/kick.log") ) lFile = fopen("Logs/kick.log", io_write);
		else lFile = fopen("Logs/kick.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == BAN)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/ban.log") ) lFile = fopen("Logs/ban.log", io_write);
		else lFile = fopen("Logs/ban.log", io_append);
		//fwrite(lFile,strL);
	    for(new c=0; c<strlen(strL); c++)
		{
	        //fputchar(lFile, strL[c], true);//будет кривая кодировка
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == CONTRACT)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/contract.log") ) lFile = fopen("Logs/contract.log", io_write);
		else lFile = fopen("Logs/contract.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == RATE)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/rate.log") ) lFile = fopen("Logs/rate.log", io_write);
		else lFile = fopen("Logs/rate.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == LOGIN)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/login.log") ) lFile = fopen("Logs/login.log", io_write);
		else lFile = fopen("Logs/login.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == OFFLINE)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/offline.log") ) lFile = fopen("Logs/offline.log", io_write);
		else lFile = fopen("Logs/offline.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == INVITE)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/invite.log") ) lFile = fopen("Logs/invite.log", io_write);
		else lFile = fopen("Logs/invite.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == ERROR)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/error.log") ) lFile = fopen("Logs/error.log", io_write);
		else lFile = fopen("Logs/error.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == PACKET)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/packet.log") ) lFile = fopen("Logs/packet.log", io_write);
		else lFile = fopen("Logs/packet.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == DEATH)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/vehicledeath.log") ) lFile = fopen("Logs/vehicledeath.log", io_write);
		else lFile = fopen("Logs/vehicledeath.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == SPAWN)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/spawn.log") ) lFile = fopen("Logs/spawn.log", io_write);
		else lFile = fopen("Logs/spawn.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == CRIMINAL)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/criminal.log") ) lFile = fopen("Logs/criminal.log", io_write);
		else lFile = fopen("Logs/criminal.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == CRASH)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/crash.log") ) lFile = fopen("Logs/crash.log", io_write);
		else lFile = fopen("Logs/crash.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == FAMILY)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/family.log") ) lFile = fopen("Logs/family.log", io_write);
		else lFile = fopen("Logs/family.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == JOB)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/job.log") ) lFile = fopen("Logs/job.log", io_write);
		else lFile = fopen("Logs/job.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == TRUCK)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/truck.log") ) lFile = fopen("Logs/truck.log", io_write);
		else lFile = fopen("Logs/truck.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == DONAT)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/donat.log") ) lFile = fopen("Logs/donat.log", io_write);
		else lFile = fopen("Logs/donat.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	else if(nam == VEHLOG)
	{
  		format(strL, sizeof(strL), "[%02d/%02d/%04d | %02d:%02d:%02d] %s\r\n",ld,lmm,ly,lH,lM,lS,strLogs);
		if( !fexist("Logs/vehicle.log") ) lFile = fopen("Logs/vehicle.log", io_write);
		else lFile = fopen("Logs/vehicle.log", io_append);
	    for(new c=0; c<strlen(strL); c++)
		{
	        fputchar(lFile, strL[c], false);
	    }
		fclose(lFile);
	}
	return 1;
}

new Min_LAGS = 30;//300
stock TestLog(nam, const function_name[], newtime=0, oldtime=0, obligatory=0)
{   //для ведения лога с проверкой на задержку не более 300 мс
	if(Min_LAGS == 0) return 1;
	if(newtime-oldtime < Min_LAGS && obligatory == 0) return 1;
	new File:lFile;
	new strtmp[256+1];
	new lH, lM, lS;	gettime(lH,lM,lS); //FixHour(lH);
	new ly, lmm, ld; getdate(ly,lmm,ld);
	if(nam == OPTIM)
	{
  		format(strtmp, sizeof(strtmp), "[%02d/%02d/%04d | %02d:%02d:%02d] Online: %d %s: %d ms\r\n",ld,lmm,ly, lH,lM,lS,
			numplayers, function_name, newtime-oldtime);
		if( !fexist("Logs/optimize.log") ) lFile = fopen("Logs/optimize.log", io_write);
		else lFile = fopen("Logs/optimize.log", io_append);
	    for(new c=0; c<strlen(strtmp); c++)
		{
	        fputchar(lFile, strtmp[c], false);
	    }
		fclose(lFile);
	}
	return 1;
}

//RegistrationSTEP7
forward HTTP_CheckOnMail(playerid, response_code, data[]);
public HTTP_CheckOnMail(playerid, response_code, data[])
{   //вызывается из OnDialogResponse
//response_code - код ошибки при получении ответа
//data - текстовая переменная, которая содержит полученную страницу в результате запроса
	new timers = GetTickCount();
    if(response_code == 200)
    {
		new GotResult = strval(data);
		if(!GotResult)
		{
		    //format(dlgitem, sizeof(dlgitem), "data: %s", data);
			//SendClientMessage(playerid, COLOR_RED, dlgitem);
	        new strtmp[256+1];
	        format(strtmp, sizeof(strtmp), "HTTP_CheckOnMail: %s[%d] отправляет запрос на несуществующий email %d", PlayerName(playerid), playerid, response_code);
	        SendAllAdminMessage(COLOR_MAROON, strtmp, 1);
	        //Log(ERROR, strtmp);

			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Пожалуйста, введите существующий email (желательно на mail.ru)!!!");
			RegistrationSTEP6(playerid);
			return 1;
		}
		SetPVarInt(playerid, "gOoc", 1);//Общий чат отключен
		SetPVarInt(playerid, "gNews", 1);//Канал Новостей отключен
		SetPVarInt(playerid, "gFam", 1);//Семейный чат отключен
		SetPVarInt(playerid, "gSport", 1);//чат гонок отключен
		SetPVarInt(playerid, "gJob", 1);//чат выходов на дежурство

		RegistrationSTEP8(playerid);
    }
    else
    {
    	//SendClientMessage(playerid, COLOR_LIGHTBLUE, "Ошибка запроса отправки проверки почтового ящика. Свяжитесь с администрацией.");

		RegistrationSTEP8(playerid);

		new response[30];
		if(response_code == HTTP_ERROR_BAD_HOST)//1
		{
			strmid(response, "HTTP_ERROR_BAD_HOST", 0, strlen("HTTP_ERROR_BAD_HOST"), 30);
        }
        else if(response_code == HTTP_ERROR_NO_SOCKET)//2
		{
			strmid(response, "HTTP_ERROR_NO_SOCKET", 0, strlen("HTTP_ERROR_NO_SOCKET"), 30);
        }
        else if(response_code == HTTP_ERROR_CANT_CONNECT)//3
		{
			strmid(response, "HTTP_ERROR_CANT_CONNECT", 0, strlen("HTTP_ERROR_CANT_CONNECT"), 30);
        }
        else if(response_code == HTTP_ERROR_CANT_WRITE)//4
		{
			strmid(response, "HTTP_ERROR_CANT_WRITE", 0, strlen("HTTP_ERROR_CANT_WRITE"), 30);
        }
        else if(response_code == HTTP_ERROR_CONTENT_TOO_BIG)//5
		{
			strmid(response, "HTTP_ERROR_CONTENT_TOO_BIG", 0, strlen("HTTP_ERROR_CONTENT_TOO_BIG"), 30);
        }
        else if(response_code == HTTP_ERROR_MALFORMED_RESPONSE)//6
		{
			strmid(response, "HTTP_ERROR_MALFORMED_RESPONSE", 0, strlen("HTTP_ERROR_MALFORMED_RESPONSE"), 30);
        }
        //new strings[MAX_STRING];
        //format(strings, sizeof(strings), "%s[%d] отсылает неверный запрос HTTP_CheckOnMail: %s", PlayerName(playerid), playerid, response);
        //SendAllAdminMessage(COLOR_MAROON, strings, 1);
        //Log(ERROR, strings);
    }
	TestLog(OPTIM, "HTTP_CheckOnMail", GetTickCount(), timers);//new timers = GetTickCount();
    return 1;
}
//404 (Page not found),
//500 (Server error) or 403 (forbidden)


forward HTTP_SendMail(playerid, response_code, data[]);
public HTTP_SendMail(playerid, response_code, data[])//RegistrationSTEP13
{   //вызывается из OnPlayerRegister
	//print(data);
	new timers = GetTickCount();
    if(response_code == 200)
    {
        new GotResult = strval(data);
		if(GotResult)
		{
			//new strings[MAX_STRING];
			format(strings, sizeof(strings), "CEPBEP: {33AA33}Пароль '{0080FF}%s'", PlayerInfo[playerid][pKey]);//из символов (a..z1..2)
			SendClientMessage(playerid, COLOR_RED, strings);
			format(strings, sizeof(strings), "успешно отправлен на '%s'. {FF0000}Проверьте почту.", PlayerInfo[playerid][pMail]);
			SendClientMessage(playerid, COLOR_GREEN, strings);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Сменить пароль (USE: /changepass) вы можете после входа в игру и выбора спауна.");
			//format(strings, sizeof(strings), "Пароль '%s' успешно отправлен на '%s'. Проверьте почту.", PlayerInfo[playerid][pKey], PlayerInfo[playerid][pMail]);
			//AudioMessage(playerid, strings);

//OnPlayerCreateAccount(playerid);
		}
		/*else
		{
		    // ........... ЗДЕСЬ СНОВА ВЫЛАЗИТ ДИАЛОГ РЕГИСТРАЦИИ ИГРОКА ......................
		    RegistrationSTEP6(playerid);
		}*/
    }
    else
    {
     	//SendClientMessage(playerid, COLOR_LIGHTBLUE, "Ошибка запроса отправки регистрационных данных на почтовый ящик. Свяжитесь с администрацией.");

/*
http://ru.wikipedia.org/wiki/%D0%A1%D0%BF%D0%B8%D1%81%D0%BE%D0%BA_%D0%BA%D0%BE%D0%B4%D0%BE%D0%B2_%D1%81%D0%BE%D1%81%D1%82%D0%BE%D1%8F%D0%BD%D0%B8%D1%8F_HTTP#500
#define HTTP_ERROR_BAD_HOST				1
#define HTTP_ERROR_NO_SOCKET			2
#define HTTP_ERROR_CANT_CONNECT			3
#define HTTP_ERROR_CANT_WRITE			4
#define HTTP_ERROR_CONTENT_TOO_BIG		5
#define HTTP_ERROR_MALFORMED_RESPONSE	6

    500 Internal Server Error — любая внутренняя ошибка сервера, которая не входит в рамки остальных ошибок класса. Появился в HTTP/1.0.
Сервер временно не может отобразить запрошенную страницу.

	501 Not Implemented — сервер не поддерживает возможностей, необходимых для обработки запроса. Типичный ответ для случаев, когда сервер не понимает указанный в запросе метод. Если же метод серверу известен, но он не применим к данному ресурсу, то нужно вернуть ответ 405. Появился в HTTP/1.0.
    502 Bad Gateway — сервер в роли шлюза или прокси-сервера получил сообщение о неудачном выполнении промежуточной операции. Появился в HTTP/1.0.
    503 Service Unavailable — сервер временно не имеет возможности обрабатывать запросы по техническим причинам (обслуживание, перегрузка и прочее). В поле Retry-After заголовка сервер может указать время, через которое клиенту рекомендуется повторить запрос. Хотя во время перегрузки очевидным кажется сразу разрывать соединение, эффективней может оказаться установка большого значения поля Retry-After для уменьшения частоты избыточных запросов. Появился в HTTP/1.0.
    504 Gateway Timeout — сервер в роли шлюза или прокси-сервера не дождался ответа от вышестоящего сервера для завершения текущего запроса. Появился в HTTP/1.1.
    505 HTTP Version Not Supported — сервер не поддерживает или отказывается поддерживать указанную в запросе версию протокола HTTP. Появился в HTTP/1.1.
    506 Variant Also Negotiates — в результате ошибочной конфигурации выбранный вариант указывает сам на себя, из-за чего процесс связывания прерывается. Экспериментальное. Введено в RFC 2295 для дополнения протокола HTTP технологией Transparent Content Negotiation.
    507 Insufficient Storage — не хватает места для выполнения текущего запроса. Проблема может быть временной. Введено в WebDAV.
    509 Bandwidth Limit Exceeded — используется при превышении веб-площадкой отведённого ей ограничения на потребление трафика. В данном случае владельцу площадки следует обратиться к своему хостинг-провайдеру. В настоящий момент данный код не описан ни в одном RFC и используется только модулем «bw/limited», входящим в панель управления хостингом cPanel, где и был введён.
    510 Not Extended — на сервере отсутствует расширение, которое желает использовать клиент. Сервер может дополнительно передать информацию о доступных ему расширениях. Введено в RFC 2774 для дополнения протокола HTTP поддержкой расширений.


*/
		/*new response[30];
		if(response_code == HTTP_ERROR_BAD_HOST)
		{
			strmid(response, "HTTP_ERROR_BAD_HOST", 0, strlen("HTTP_ERROR_BAD_HOST"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_NO_SOCKET)
		{
			strmid(response, "HTTP_ERROR_NO_SOCKET", 0, strlen("HTTP_ERROR_NO_SOCKET"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_CANT_CONNECT)
		{
			strmid(response, "HTTP_ERROR_CANT_CONNECT", 0, strlen("HTTP_ERROR_CANT_CONNECT"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_CANT_WRITE)
		{
			strmid(response, "HTTP_ERROR_CANT_WRITE", 0, strlen("HTTP_ERROR_CANT_WRITE"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_CONTENT_TOO_BIG)
		{
			strmid(response, "HTTP_ERROR_CONTENT_TOO_BIG", 0, strlen("HTTP_ERROR_CONTENT_TOO_BIG"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_MALFORMED_RESPONSE)
		{
			strmid(response, "HTTP_ERROR_MALFORMED_RESPONSE", 0, strlen("HTTP_ERROR_MALFORMED_RESPONSE"), sizeof(response));
        }
        else if(response_code == 500)
		{
			strmid(response, "внутренняя ошибка сервера", 0, strlen("HTTP_ERROR_MALFORMED_RESPONSE"), sizeof(response));
        }
		//new strings[MAX_STRING];
        format(strings, sizeof(strings), "%s[%d] отсылает на HTTP неверный запрос SendMail: %s[%d]", PlayerName(playerid), playerid, response, response_code);
        //SendAllAdminMessage(COLOR_MAROON, strings, 1);
        Log(ERROR, strings);*/
    }
	TestLog(OPTIM, "HTTP_SendMail", GetTickCount(), timers);//new timers = GetTickCount();
    return 1;
}


/*
stock SendMessageToICQ(playerid, const message[])//запрос
{
	new strings[55+128+12+24+4+3 + 12];
	format(strings, sizeof(strings), "gta.strikearena.ru/SendMailVW/SendMessageFromICO.php?Message=%s&PlayerName=%s&ID=%d",
		message, PlayerName(playerid), playerid);
	//print(strings);
	HTTP(playerid, HTTP_GET, strings, "", "");
	//HTTP(playerid, HTTP_HEAD, strings, "", "");
	return 1;
}*/
forward HTTP_PasswordSendToMail(playerid, response_code, data[]);
public HTTP_PasswordSendToMail(playerid, response_code, data[])
{
	new timers = GetTickCount();
    if(response_code == 200)
    {
    	new GotResult = strval(data);
		if(GotResult)
		{
			SetPVarInt(playerid, "PasswordHasEdited", getdate());
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Копия с новым паролем была успешна отправлена на ваш почтовый адрес!");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Проверьте почтовый ящик (ВХОДЯЩИЕ или СПАМ)!");
		}
		else return SendClientMessage(playerid, COLOR_LIGHTBLUE, "Невозможно выслать копию с новым паролем на ваш почтовый адрес.");
    }
    else
    {
		//SendClientMessage(playerid, COLOR_LIGHTBLUE, "Ошибка запроса отправки нового пароля на почтовый ящик. Свяжитесь с администрацией.");

		new response[30];
		if(response_code == HTTP_ERROR_BAD_HOST)
		{
			strmid(response, "HTTP_ERROR_BAD_HOST", 0, strlen("HTTP_ERROR_BAD_HOST"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_NO_SOCKET)
		{
			strmid(response, "HTTP_ERROR_NO_SOCKET", 0, strlen("HTTP_ERROR_NO_SOCKET"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_CANT_CONNECT)
		{
			strmid(response, "HTTP_ERROR_CANT_CONNECT", 0, strlen("HTTP_ERROR_CANT_CONNECT"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_CANT_WRITE)
		{
			strmid(response, "HTTP_ERROR_CANT_WRITE", 0, strlen("HTTP_ERROR_CANT_WRITE"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_CONTENT_TOO_BIG)
		{
			strmid(response, "HTTP_ERROR_CONTENT_TOO_BIG", 0, strlen("HTTP_ERROR_CONTENT_TOO_BIG"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_MALFORMED_RESPONSE)
		{
			strmid(response, "HTTP_ERROR_MALFORMED_RESPONSE", 0, strlen("HTTP_ERROR_MALFORMED_RESPONSE"), sizeof(response));
        }
        else if(response_code == 500)
		{
			strmid(response, "внутренняя ошибка сервера", 0, strlen("HTTP_ERROR_MALFORMED_RESPONSE"), sizeof(response));
        }
        
		//new strings[MAX_STRING];
		format(strings, sizeof(strings), "%s[%d] отсылает на HTTP неверный запрос PasswordSendToMail: %s[%d]", PlayerName(playerid), playerid, response, response_code);
		Log(ERROR, strings);
    }
	TestLog(OPTIM, "HTTP_PasswordSendToMail", GetTickCount(), timers);//new timers = GetTickCount();
    return 1;
}

forward HTTP_RememberPassword(playerid, response_code, data[]);
public HTTP_RememberPassword(playerid, response_code, data[])
{   //вызывается при нажатии кнопку REMINDER
	new timers = GetTickCount();
    if(response_code == 200)
    {
    	new GotResult = strval(data);
		if(GotResult)
		{
			SetPVarInt(playerid, "PasswordHasEdited", getdate());
			//return SendClientMessage(playerid, COLOR_LIGHTBLUE, "Копия с паролем была успешна отправлена на ваш почтовый адрес!");
			SendClientMessage(playerid, COLOR_RED, "CEPBEP: {33AA33}Ваши данные были отправлены на ваш почтовый ящик указанный при регистрации.");
			SendClientMessage(playerid, COLOR_RED, "Проверьте почтовый ящик (в разделе СПАМ)!");
		}
		else return SendClientMessage(playerid, COLOR_LIGHTBLUE, "Невозможно выслать копию с паролем на ваш почтовый адрес.");
    }
    else
    {
  		new response[40];
 		if(response_code == 404)
		{
//404 Not Found — самая распространенная ошибка при пользовании Интернетом,
//основная причина — ошибка в написании адреса Web-страницы.
//Сервер понял запрос, но не нашёл соответствующего ресурса по указанному URI.
//Если серверу известно, что по этому адресу был документ, то ему желательно использовать код 410.
//Ответ 404 может использоваться вместо 403, если требуется тщательно скрыть от посторонних глаз определённые ресурсы. Появился в HTTP/1.0.
			strmid(response, "ошибка в написании адреса Web-страницы", 0, strlen("ошибка в написании адреса Web-страницы"), sizeof(response));
        }
		//SendClientMessage(playerid, COLOR_LIGHTBLUE, "Ошибка запроса отправки пароля на почтовый ящик. Свяжитесь с администрацией.");

/*
http://ru.wikipedia.org/wiki/%D0%A1%D0%BF%D0%B8%D1%81%D0%BE%D0%BA_%D0%BA%D0%BE%D0%B4%D0%BE%D0%B2_%D1%81%D0%BE%D1%81%D1%82%D0%BE%D1%8F%D0%BD%D0%B8%D1%8F_HTTP#500
#define HTTP_ERROR_BAD_HOST				1
#define HTTP_ERROR_NO_SOCKET			2
#define HTTP_ERROR_CANT_CONNECT			3
#define HTTP_ERROR_CANT_WRITE			4
#define HTTP_ERROR_CONTENT_TOO_BIG		5
#define HTTP_ERROR_MALFORMED_RESPONSE	6

    500 Internal Server Error — любая внутренняя ошибка сервера, которая не входит в рамки остальных ошибок класса. Появился в HTTP/1.0.
    501 Not Implemented — сервер не поддерживает возможностей, необходимых для обработки запроса. Типичный ответ для случаев, когда сервер не понимает указанный в запросе метод. Если же метод серверу известен, но он не применим к данному ресурсу, то нужно вернуть ответ 405. Появился в HTTP/1.0.
    502 Bad Gateway — сервер в роли шлюза или прокси-сервера получил сообщение о неудачном выполнении промежуточной операции. Появился в HTTP/1.0.
    503 Service Unavailable — сервер временно не имеет возможности обрабатывать запросы по техническим причинам (обслуживание, перегрузка и прочее). В поле Retry-After заголовка сервер может указать время, через которое клиенту рекомендуется повторить запрос. Хотя во время перегрузки очевидным кажется сразу разрывать соединение, эффективней может оказаться установка большого значения поля Retry-After для уменьшения частоты избыточных запросов. Появился в HTTP/1.0.
    504 Gateway Timeout — сервер в роли шлюза или прокси-сервера не дождался ответа от вышестоящего сервера для завершения текущего запроса. Появился в HTTP/1.1.
    505 HTTP Version Not Supported — сервер не поддерживает или отказывается поддерживать указанную в запросе версию протокола HTTP. Появился в HTTP/1.1.
    506 Variant Also Negotiates — в результате ошибочной конфигурации выбранный вариант указывает сам на себя, из-за чего процесс связывания прерывается. Экспериментальное. Введено в RFC 2295 для дополнения протокола HTTP технологией Transparent Content Negotiation.
    507 Insufficient Storage — не хватает места для выполнения текущего запроса. Проблема может быть временной. Введено в WebDAV.
    509 Bandwidth Limit Exceeded — используется при превышении веб-площадкой отведённого ей ограничения на потребление трафика. В данном случае владельцу площадки следует обратиться к своему хостинг-провайдеру. В настоящий момент данный код не описан ни в одном RFC и используется только модулем «bw/limited», входящим в панель управления хостингом cPanel, где и был введён.
    510 Not Extended — на сервере отсутствует расширение, которое желает использовать клиент. Сервер может дополнительно передать информацию о доступных ему расширениях. Введено в RFC 2774 для дополнения протокола HTTP поддержкой расширений.


*/
		if(response_code == HTTP_ERROR_BAD_HOST)
		{
			strmid(response, "HTTP_ERROR_BAD_HOST", 0, strlen("HTTP_ERROR_BAD_HOST"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_NO_SOCKET)
		{
			strmid(response, "HTTP_ERROR_NO_SOCKET", 0, strlen("HTTP_ERROR_NO_SOCKET"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_CANT_CONNECT)
		{
			strmid(response, "HTTP_ERROR_CANT_CONNECT", 0, strlen("HTTP_ERROR_CANT_CONNECT"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_CANT_WRITE)
		{
			strmid(response, "HTTP_ERROR_CANT_WRITE", 0, strlen("HTTP_ERROR_CANT_WRITE"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_CONTENT_TOO_BIG)
		{
			strmid(response, "HTTP_ERROR_CONTENT_TOO_BIG", 0, strlen("HTTP_ERROR_CONTENT_TOO_BIG"), sizeof(response));
        }
        else if(response_code == HTTP_ERROR_MALFORMED_RESPONSE)
		{
			strmid(response, "HTTP_ERROR_MALFORMED_RESPONSE", 0, strlen("HTTP_ERROR_MALFORMED_RESPONSE"), sizeof(response));
        }
        else if(response_code == 500)
		{
			strmid(response, "внутренняя ошибка сервера", 0, strlen("HTTP_ERROR_MALFORMED_RESPONSE"), sizeof(response));
        }
        
		//new strings[MAX_STRING];
        format(strings, sizeof(strings), "RememberPassword %s[%d]: %s[%d]", PlayerName(playerid), playerid, response, response_code);
        //SendAllAdminMessage(COLOR_MAROON, strings, 1);
        Log(ERROR, strings);
    }
	TestLog(OPTIM, "HTTP_RememberPassword", GetTickCount(), timers);//new timers = GetTickCount();
    return 1;
}

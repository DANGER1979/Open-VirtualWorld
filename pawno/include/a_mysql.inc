/*
	SA-MP MySQL plugin R5
	Copyright (c) 2008-2010, G-sTyLeZzZ 
*/

#if defined mysql_included
	#endinput
#endif
#define mysql_included

//Common error codes (http://dev.mysql.com/doc/refman/5.0/en/error-messages-(client|server).html)

#define ER_DBACCESS_DENIED_ERROR 1044
#define ER_ACCESS_DENIED_ERROR 1045
#define ER_UNKNOWN_TABLE 1109
#define ER_SYNTAX_ERROR 1149
#define CR_SERVER_GONE_ERROR 2006
#define CR_SERVER_LOST 2013
#define CR_COMMAND_OUT_OF_SYNC 2014
#define CR_SERVER_LOST_EXTENDED 2055

//Native functions

#define mysql_fetch_row(%1) mysql_fetch_row_format(%1,"|")
#define mysql_next_row() mysql_retrieve_row()
#define mysql_get_field(%1,%2) mysql_fetch_field_row(%2,%1)

native mysql_connect(const host[],const user[],const database[],const password[]);//DB:db_open(name[]);
native mysql_close(connectionHandle = 1);//db_close(DB:db);
native mysql_query(query[],resultid = (-1),extraid = (-1),connectionHandle = 1);//DBResult:db_query(DB:db, query[]);//делаем запрос
native mysql_num_rows(connectionHandle = 1);//db_num_rows(DBResult:dbresult);

//не используется
native mysql_num_fields(connectionHandle = 1);//Возвращает количество столбцов в результирующем наборе.
//db_num_fields(DBResult:dbresult); //Позволяет узнать количество полей результата запроса.


native mysql_fetch_row_format(string[],const delimiter[] = "|",connectionHandle = 1);//ф-ия полученную строку разделяет по разделителю "|"//Функция служит для обработки полной строки из результата запроса
native mysql_retrieve_row(connectionHandle = 1);//получает строку, а если строки нет - даёт ноль, служит для перехода на следующую строк //Используйте эту функцию для перемещения внутреннего указателя строки на следующую строку.
//Мы могли бы в принципе назвать эту функцию mysql_next_row (). Эта функция очень полезна, когда мы планируем использовать mysql_fetch_field() или mysql_fetch_field_row() позже, поэтому нам не нужно извлекать весь результат в Pawno.
//db_next_row(DBResult:dbresult);//Переходит к следующей строке результата, выделенного из db_query. Пример: while(db_next_row(db_result));


native mysql_fetch_field_row(string[],const fieldname[],connectionHandle = 1);//Используйте эту функцию для получения данных в поле string, адресованном по его имени fieldname. //получает данные из указанного столбца fieldname и записывает в string
//db_get_field_assoc(DBResult:dbresult, const field[], result[], maxlength);//Позволяет узнать содержимое поля в виде строки текста с указанным именем field и записывает в строковую переменную result
//db_get_field_assoc_int(DBResult:result, const field[]);//Получите содержимое поля в виде целого числа с указанным именем field
//db_get_field_assoc_float(DBResult:result, const field[]);//Получите содержимое поля в виде вещественного числа с указанным именем field


native mysql_free_result(connectionHandle = 1);//db_free_result(DBResult:dbresult);//Функция используется для очистки результата после использования mysql_store_result или после запроса SELECT
native mysql_insert_id(connectionHandle = 1);//возвращает индекс строки созданной в базе после команда INSERT


//------------------------------------------------------------------------------
//не используются в SQLite
native mysql_store_result(connectionHandle = 1);////получаем результат //сохраняет результат в буфер. всегда возвращает единицу //всегда следует за mysql_query если запрос SELECT
native mysql_affected_rows(connectionHandle = 1);
native mysql_debug(enable = 1);
native mysql_errno(connectionHandle = 1);

//db_field_name(DBResult:dbresult, field, result[], maxlength);//Получает название поля по его индексу, т.е. номеру столбца
native mysql_fetch_field(number,dest[],connectionHandle = 1);//Используйте эту функцию, чтобы получить имя конкретного поля по номеру number, которое запишется в dest

native mysql_fetch_int(connectionHandle = 1);//Используйте эту функцию для извлечения одного!!! целого числа (положительного числа) из результирующего набора.
native mysql_fetch_float(&Float:result,connectionHandle = 1);//Используйте эту функцию для извлечения одного!!! значения с плавающей точкой из результирующего набора.
/*mysql_query("SELECT health FROM players LIMIT 1");mysql_store_result();
new Float:health;
mysql_fetch_float(health);
mysql_free_result();*/

native mysql_field_count(connectionHandle = 1);//Используйте эту функцию, чтобы получить количество столбцов для самого последнего запроса на соединение.

native mysql_set_charset(charset[],connectionHandle = 1);
native mysql_get_charset(destination[],connectionHandle = 1);
native mysql_ping(connectionHandle = 1);
native mysql_real_escape_string(const source[],destination[],connectionHandle = 1);
native mysql_query_callback(index,query[],callback[],extraid = (-1),connectionHandle = 1);
native mysql_reconnect(connectionHandle = 1);
native mysql_reload(connectionHandle = 1);
native mysql_stat(const destination[],connectionHandle = 1);
native mysql_warning_count(connectionHandle = 1);

//forward declarations

forward OnQueryFinish(query[], resultid, extraid, connectionHandle);
forward OnQueryError(errorid, error[], resultid, extraid, callback[], query[], connectionHandle);
/*------------------------------------------------------------------------------
//не используются в mysql
//db_get_field(DBResult:dbresult, field, result[], maxlength);//Позволяет узнать содержимое поля в виде строки текста по его порядковому номеру field.
//db_get_field_int(DBResult:result, field = 0);//Позволяет узнать содержимое поля в виде целого числа по его порядковому номеру field.
//Float:db_get_field_float(DBResult:result, field = 0);//Позволяет узнать содержимое поля в виде вещественного числа по его порядковому номеру field.

native db_get_mem_handle(DB:db);
native db_get_result_mem_handle(DBResult:result);

native db_debug_openfiles();
native db_debug_openresults();

#define MAX_INI_ENTRY_TEXT 80
stock DB_Escape(text[])
{
	new	ret[MAX_INI_ENTRY_TEXT * 2], ch, i,	j;
	while ((ch = text[i++]) && j < sizeof (ret))
	{
		if (ch == '\'')
		{
			if (j < sizeof (ret) - 2)
			{
				ret[j++] = '\'';
				ret[j++] = '\'';
			}
		}
		else if (j < sizeof (ret)) ret[j++] = ch;
		else j++;
	}
	ret[sizeof (ret) - 1] = '\0';
	return ret;
}*/

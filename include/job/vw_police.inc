new rbCounter = 0;//счётчик добавленных блоков

enum pddinfo
{
	Article,//статья
	Part,//часть
	Title[64],//Название
	Commentary[128],//Нарушения, за которые налагаются административные взыскания
	Jailed,//Виды и меры взысканий: 1 - предупреждение или штраф, 2 - штраф, 3 - штраф либо лишение 4 - арест с лишением
	Bail,//штраф - кол-во базовых величин /сколько начислить очков розыска //ticket = PDD[i][Bail]*1*360;//3600
	Period//время отбора прав
};
//ГЛАВА 18. АДМИНИСТРАТИВНЫЕ ПРАВОНАРУШЕНИЯ ПРОТИВ БЕЗОПАСНОСТИ ДВИЖЕНИЯ И ЭКСПЛУАТАЦИИ ТРАНСПОРТА
new PDD[47][pddinfo] = {
{1,1, "Умышленное блокирование транспортных коммуникаций", "путем создания препятствий, установки постов или иным способом",2,6,0},
{2,2, "Нарушение правил безопасности", "движения или эксплуатации транспортного средства",2,5,0},//2,15,0},
{3,5, "Нарушение правил, обеспечивающих безопасность движения", "Проход по железнодорожным путям в неустановленном месте ",2,2,0},
{4,1, "Нарушение правил пользования железнодорожного ТС", "проезд на крыше вагона",2,3,0},
{5,4, "Нарушение правил безопасности полетов", "Самовольный проход или проезд по территории аэропорта",1,2,0},
{10,21, "Нарушение правил перевозки грузов", "с превышением более чем на 15 %%",2,1,0},//1-3
{11,77, "Нарушение авиационной безопасности", "Вторжение в Контролируемую Зону",4,1,3},
{12,1, "Hарушение правил эксплуатации ТС", "Управление ТС, имеющим неисправности или несоблюдение тех. характеристик",1,1,0},//1-3
{12,79, "Нарушение безопасности полетов воздушных судов", "Неправильное использование аэродромов совместного использования",3,1,3},
{12,80, "Нарушение правил безопасности движения на воздушном ТС", "Неправильное использование воздушного ТС и пространства",3,1,3},
{13,1, "Превышение установленной скорости движения", "от 10-20 км/ч.",1,1,0},
{13,2, "Превышение установленной скорости движения", "от 20-30 км/ч.",2,1,0},//1-2
{13,3, "Превышение установленной скорости движения", "от 30 км/ч.",2,2,0},//2-10
{13,4, "Превышение установленной скорости движения", "совершенные повторно в течение 1 года после наложения взыскания",3,4,1},//4-15
{14,1, "Невыполнение лицом, управляющим ТС требований", "сигналов регулирования, нарушение правил перевозки людей или грузов",1,1,0},//1-5
{14,3, "Невыполнение лицом, управляющим ТС требований", "правил расположения ТС, обгона, выезда на полосу встречного движения",2,5,0},//5-10
{14,4, "Невыполнение требований", "знаков, разметки, перекрестков, буксировки, маневрирования, непредоставление преимущества",1,1,0},//1-5
{14,5, "Невыполнение лицом, управляющим ТС требований", "правил по обеспечению беспрепятственного проезда ТС оперативного назначения",2,2,1},//2-10
{14,6, "Невыполнение лицом, управляющим ТС требований", "правил движения по автомагистрали",1,3,0},//1-4
{14,7, "Невыполнение требований правил", "в жилых зонах либо движение по пешеходным дорожкам, обочинам, тротуарам или газонам",1,1,0},//1-3
{14,8, "Невыполнение лицом, управляющим ТС требований", "правил участия в групповом передвижении ТС, создающем угрозу безопасности движения",3,5,1},//5-10
{14,9, "Невыполнение лицом, управляющим ТС требований", "повлекшие создание аварийной обстановки",3,10,2},//10-20
{14,10, "Невыполнение лицом, управляющим ТС требований", "пользования радио- и телефонной связью во время движения",1,1,0},//1-2
{15,1, "Hарушение лицом, управляющим ТС, правил", "проезда железнодорожного переезда",2,2,0},//2-4
{15,2, "Hарушение лицом, управляющим ТС, правил", "проезда железнодорожного переезда совершенное повторно",2,4,0},//4-20
{16,1, "Управление ТС", "лицом находящимся в состоянии опьянения или под воздействием наркотических веществ",4,15,3},//15-35
{16,2, "Управление ТС", "в состоянии опьянения не имеющим права управления ТС",4,25,3},//25-45
{17,1, "Нарушения ПДД", "повлекшие причинение легкого телесного повреждения либо повреждение ТС, груза, дорожных и др. сооружений",3,10,2},//10-30
{17,2, "Нарушения ПДД лицом, управляющим ТС", "совершенные лицом, не имеющим права управления этим ТС",4,20,2},//20-50
{17,3, "Нарушения ПДД", "повлекшие причинение тяжкого телесного повреждения либо смерть",4,10,5},//10-30
{17,4, "Нарушения ПДД лицом, управляющим ТС", "Оставление водителем места ДТП",3,20,3},//20-50
{18,1, "Управление ТС", "лицом не имеющим документов, либо отказ от предъявления",3,10,0},//подтверждающего право на управление ТС данной категории
{19,1, "Угон ТС", "совершенном без насилия над личностью или с насилием, которое не опасно для жизни и здоровья.",3,20,2},
{19,2, "Угон ТС", "совершенное группой лиц, повлекшее причинение ущерба в особо крупном размере",4,20,3},
{20,1, "Управление ТС", "без заключения договора обязательного страхования",2,2,0},//2-5
{20,2, "Управление ТС", "без заключения договора страхования в случае совершения ДТП",2,5,0},//5-10
{21,1, "Невыполнение лицом, управляющим ТС", "требования работника милиции об остановке ТС",2,1,0},//1,1,0
{21,2, "Невыполнение лицом, управляющим ТС", "неоднократных требований работника милиции об остановке ТС",3,1,1},//1,1,0
{22,1, "Нарушение лицом, управляющим ТС", "правил остановки или стоянки транспортного средства",1,1,0},
{23,1, "Hарушение ПДД участником дорожного движения", "управляющим велосипедом или лицом, участвующим в движении и не управляющим ТС",1,1,0},
//{24,1, "Выпуск в эксплуатацию ТС, имеющего неисправности", "при наличии которой его эксплуатация запрещена, или переоборудованного без соответствующего разрешения, или не зарегистрированного в установленном порядке, или не прошедшего государственного технического осмотра",2,4-6,0},
{26,1, "Нарушение режима труда и отдыха", "Нарушение установленного режима труда и отдыха",2,4,0},
{27,1, "Hарушение лицом, управляющим ТС, правил", "учебной езды водителем, обучающим вождению ТС",1,1,0},
{29,1, "Hарушение лицом, управляющим ТС, правил", "безопасности при перевозке опасных грузов",2,2,0},//2-10
{35,1, "Повреждение, загромождение, загрязнение", "автодороги, ж.д. переезда, др. сооружения или средств регулирования",2,2,0},//2-5
{36,1, "Hарушение ТС-ом порядка пользования дорогами", "Размещение под мостами, путепроводами и эстакадами",2,2,0},//2-10
{36,2, "Hарушение ТС-ом порядка пользования дорогами", "Проведение на дорогах общего пользования испытаний",2,2,0},//2-5
{36,4, "Hарушение ТС-ом порядка пользования дорогами", "Въезд, съезд в неустановленных или необустроенных местах",2,1,0}
};

new DOTL[23][18] = {//для PenalCode - УК СА
{1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2},//0. до 2 часов
{1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3},//1. до 3 часов
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5},//2. до 5 часов
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6},//3. до 6 часов
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7},//4. до 7 часов
{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10},//5. 2-10 часов
{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 5, 6, 7, 8, 9, 10},//6. 3-10 часов
{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 7, 8, 9, 10},//7. 5-10 часов
{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 8, 9, 10},//8. 6-10 часов
{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 4, 5},//9. 2-5 часов
{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 4, 5, 6},//10. 2-6 часов
{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 4, 5, 6, 7},//11. 2-7 часов
{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 5, 6, 7},//12. 3-7 часов
{5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7},//13. 5–7 часов
{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 5, 6, 7, 8},//14. 3-8 часо
{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 6, 7, 8, 9, 10, 11, 12},//15. 4-12 часов
{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 7, 8, 9, 10, 11, 12},//16. 5-12 часов
{5, 5, 5, 5, 5, 5, 5, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},//17. 5-15 часов
{6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},//18. 6-15 часов
{7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 10, 11, 12, 13},//19. 8-13 часов
{7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 10, 11, 12, 13, 14, 15},//20. 8-15 часов
{7, 8, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 12, 13, 14, 15},//21. 10-15 часов
{8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25}//22. 8-25 часов
};
enum punishmentinfo
{
	Article,//Номер Статьи
	Part,//Номер Части
	Title[64],//Название Статьи/Части
	Commentary[128],//Коментарий/пояснения
	Bail,//залог или штраф - кол-во базовых величин
	Jailed,//3 - камере предварительного заключения, 10 - исправительной колонии
	Period,//номер строки из массива - время заключения из массива DOTL строка
	Wanted//сколько начислить очков розыска //1-6 - малое, 7-14 - среднее, 15-25 - тяжкое
};
//1. Установить:
//1.1. административную ответственность физических лиц за следующие правонарушения:
new PenalCode[81][punishmentinfo] = {
{83,1, "Лицо освобождается от ответственности, если истек", "1 ч. при преступлении не представляющего большой опасности (2 ч. вне игры)",0,0,0,0},
{83,2, "Лицо освобождается от уголовной ответственности, если истекло", "от 1 до 3 ч. при совершении менее тяжкого преступления (5 ч. вне игры)",0,0,0,0},
{83,3, "Лицо освобождается от уголовной ответственности, если истекло", "от 3 до 5 ч. при совершении тяжкого преступления (10 ч. вне игры)",0,0,0,0},
{86,1, "Лицо, впервые совершившее преступление привлекается", "к административной ответственности: арест 15 минут",1,3,0,0},
{90,1, "Условно-досрочное освобождение от наказания", "при его примерном поведении, доказывающем исправление лица.",0,0,0,0},
{90,2, "Условно-досрочное освобождение от наказания", "после отбытия 1/2 срока, за преступление, не представляющее большой опасности",0,0,0,0},
{90,3, "Условно-досрочное освобождение от наказания", "после отбытия 2/3 срока, за тяжкое преступление",0,0,0,0},
{90,4, "Условно-досрочное освобождение от наказания", "после отбытия 3/4 срока, за особо тяжкое преступление",0,0,0,0},
{118,1, "Освобождение от уголовной ответственности", "Лицо, впервые совершившее преступление до 18 лет, не представляющее большой опасности",0,0,0,0},
//------------------------------------------------------------------------------
{139,1, "Убийство", "Умышленное противоправное лишение жизни другого человека",15,10,18,25},
{139,2, "Убийство", "Убийство 2-х или более лиц, либо совершенное группой лиц",20,10,20,30},
{139,3, "Убийство", "Убийство при превышении мер, необходимых для задержания лица, совершившего преступление",3,10,1,7},
{139,4, "Убийство", "Убийство при превышении пределов необходимой обороны",4,3,0,14},//",4,3,0,14
{139,5, "Убийство", "Убийство сотрудника органов внутренних дел",25,10,19,35},
{144,1, "Причинение смерти по неосторожности", "Причинение тяжкого вреда, повлекшее смерть",3,10,1,15},
{144,2, "Причинение смерти по неосторожности", "двум или более лицам",5,10,2,20},
{149,1, "Умышленное причинение менее тяжкого телесного повреждения", "вызвавшего расстройство здоровья либо утрату трудоспособности",3,3,1,5},
{149,2, "Умышленное причинение менее тяжкого телесного повреждения", "совершенное группой лиц либо способом, носящим характер мучения или истязания",5,10,2,6},
{150,1, "Умышленное причинение тяжкого телесного повреждения", "при превышении пределов необходимой обороны",5,3,1,10},
{150,2, "Умышленное причинение тяжкого телесного повреждения", "возникшее в связи с систематическим противоправным поведением",7,10,2,14},
{161,1, "Неоказание помощи больному", "Ненадлежащее исполнение профессиональных обязанностей медицинским работником",3,3,0,2},//",3,3,0,2
{182,1, "Похищение человека", "Захват заложника",5,10,13,7},
{182,2, "Похищение человека", "совершенное группой лиц c применением оружия в отношении двух или более лиц",7,10,17,15},
{182,3, "Похищение человека", "повлеклекшее смерть потерпевшего или иные тяжкие последствия",8,10,21,20},
{188,1, "Клевета. Оскорбление. Заведомо ложный донос", "Распространение заведомо ложных, позорящих другое лицо измышлений, умышленное унижение чести и достоинства",2,3,0,2},//",2,3,0,2
{188,2, "Клевета. Оскорбление. Заведомо ложный донос", "совершенное в публичном выступлении",3,3,0,7},//",3,3,0,7
{188,3, "Клевета. Оскорбление. Заведомо ложный донос", "cоединенные с обвинением в тяжком или особо тяжком преступлении",3,10,1,15},
{202,1, "Нарушение законных владений граждан", "Незаконное вторжение в жилище вопреки воле проживающих",1,3,0,2},//",1,3,0,2
{202,2, "Нарушение законных владений граждан", "совершенное должностным лицом с использованием своих служебных полномочий",1,3,0,2},//",1,3,0,2
{205,1, "Кража. Грабеж. Угон", "совершенном без насилия над личностью или с насилием, которое не опасно для жизни и здоровья.",2,10,1,3},
{205,2, "Кража. Грабеж. Угон", "совершенное группой лиц, повлекшее причинение ущерба в особо крупном размере",3,10,11,7},
{205,3, "Кража. Грабеж. Угон", "повлекшее смерть человека",6,10,7,15},//Разбой.
{209,1, "Мошенничество", "Завладение имуществом путем обмана или злоупотребления доверием",5,10,1,3},
{209,2, "Мошенничество", "совершенное повторно либо группой лиц, в крупном размере",10,10,20,7},
{209,3, "Мошенничество", "совершенное организованной группой лиц, либо в особо крупном размере",12,10,6,15},
{285,1, "Бандитизм", "Создание незаконного вооруженного формирования",5,3,0,2},//",5,3,0,2
{285,2, "Бандитизм", "Участие в преступной организации в любой иной форме",4,3,0,2},//",4,3,0,2
{293,1, "Массовые беспорядки", "погромы, поджоги, уничтожение имущества, вооруженное сопротивление представителям власти",6,10,17,15},
{293,2, "Массовые беспорядки", "совершенные повторно либо группой лиц",4,10,14,8},
{295,1, "Незаконные действия в отношении огнестрельного оружия", "Незаконные изготовление, приобретение, передача во владение, сбыт, хранение или ношение",3,10,4,6},
{295,2, "Незаконные действия в отношении огнестрельного оружия", "совершенные повторно либо группой лиц по предварительному сговору",3,10,5,14},
{295,3, "Незаконные действия в отношении огнестрельного оружия", "совершенные организованной группой",4,10,15,20},
{317,1, "Нарушение ПДД(полетов) или эксплуатации ТС", "Повлекшее причинение ущерба либо менее тяжкого телесного повреждения",1,3,0,2},//",1,3,0,2
{317,2, "Нарушение ПДД(полетов) или эксплуатации ТС", "повлекшее смерть человека либо причинение тяжкого телесного повреждения",5,10,5,7},
{317,3, "Нарушение ПДД(полетов) или эксплуатации ТС", "Повлекшее смерть двух или более лиц, ",8,10,15,20},
{317,4, "Нарушение ПДД(полетов) или эксплуатации ТС", "Управление транспортным в состоянии опьянения",1,3,0,15},//",1,3,0,15
{328,1, "Незаконный оборот наркотических средств", "хранение наркотических средств",2,3,0,2},//",2,3,0,2
{328,2, "Незаконный оборот наркотических средств", "изготовление с целью сбыта, либо сбыт наркотических средств",3,10,0,14},
{328,3, "Незаконный оборот наркотических средств", "совершенные группой лиц, в крупном размере, в месте проведения мероприятий",4,10,19,20},
{339,1, "Хулиганство", "действия нарушающие общественный порядок или выражающие неуважение к обществу",2,10,1,3},
{339,2, "Хулиганство", "совершенное группой лиц или Стрельба из огнестрельного оружия в непредназначенном месте",4,10,3,5},
{339,3, "Хулиганство", "совершенные с применением оружия для причинения телесных повреждений",6,10,6,10},
{363,1, "Сопротивление лицу, охраняющим общественный порядок", "при выполнении им обязанностей по охране общественного порядка",2,10,1,3},
{363,2, "Сопротивление лицу, охраняющим общественный порядок", "сопряженное с применением насилия или с угрозой его применения",4,10,2,5},// к выполнению явно незаконных действий
{369,1, "Оскорбление представителя власти", "Публичное оскорбление в связи с выполнением им служебных обязанностей",2,10,1,3},
{383,1, "Самоуправство", "Самовольное осуществление своего действительного или предполагаемого права",3,3,0,2},//",3,3,0,2
{397,1, "Заведомо незаконные задержание", "заключение под стражу, либо содержание под стражей",2,10,1,3},
{397,2, "Заведомо незаконные задержание", "повлекшие тяжкие последствия (смерть человека)",3,10,11,7},
{402,1, "Отказ либо уклонение от дачи показаний", "Отказ либо уклонение свидетеля или потерпевшего от дачи показаний",2,3,0,2},
{413,1, "Побег", "Побег из исправительного учреждения, или из-под стражи",12,10,1,3},//30000,10,1,3
{413,2, "Побег", "совершенное группой лиц, либо с применением насилия, опасного для жизни и здоровья",17,10,11,7},//70000,10,11,7
{414,1, "Уклонение от ареста", "Уклонение от отбывания наказания в виде лишения свободы или ареста",2,10,1,2},
{418,1, "Уклонение от уплаты штрафа", "Уклонение от уплаты штрафа",2,10,1,6},//20000,3,0,2
{424,1, "Злоупотребление властью. Превышение власти", "повлекшее причинение ущерба в крупном размере или существенного вреда общественным интересам",2,10,1,3},
{424,2, "Злоупотребление властью. Превышение власти", "совершенное из корыстной или иной личной заинтересованности с применением оружия ",3,10,3,6},
{424,3, "Злоупотребление властью. Превышение власти", "занимающего ответственное положение, повлекшие тяжкие последствия, совершенные в сложной обстановке",4,10,6,10},
{425,1, "Бездействие должностного лица. Служебная халатность", "Умышленное неисполнение должностным лицом действий, попустительство",3,10,1,3},//вопреки интересам службы
{425,2, "Бездействие должностного лица. Служебная халатность", "Бездействие должностного лица из корыстной или иной личной заинтересованности",4,10,3,6},
{425,3, "Бездействие должностного лица. Служебная халатность", "занимающего ответственное положение, повлекшие тяжкие последствия",5,10,6,10},
{430,1, "Получение взятки", "приобретение выгод имущественного характера",3,10,4,7},
{430,2, "Получение взятки", "совершенное группой лиц по предварительному сговору, либо в крупном размере",4,10,8,10},
{430,3, "Получение взятки", "совершенное лицом занимающим ответственное положение в особо крупном размере, организованной группой",4,10,20,15},
{431,1, "Дача взятки", "Дача взятки",2,10,2,5},
{431,2, "Дача взятки", "повторно за заведомо незаконное действие в крупном размере",4,10,11,7},
{438,1, "Неповиновение. Неисполнение приказа", "Открытый отказ либо иное умышленное неисполнене приказа",2,10,1,2},
{438,2, "Неповиновение. Неисполнение приказа", "совершенное группой лиц в боевой обстановке повлекшее тяжкие последствия",4,10,4,7},
{445,1, "Дезертирство", "неявка в срок без уважительных причин (2-10 минут)",2,3,0,2},
{445,2, "Дезертирство", "Самовольное оставление места службы, неявка в срок без уважительных причин (10-60 минут)",3,10,1,3},
{445,3, "Дезертирство", "самовольное отсутствие свыше часа",4,10,2,5},
{445,4, "Дезертирство", "совершенные в боевой обстановке",6,10,7,10},
{581,1, "Браконьерство", "добыча рыбы или др. водных животных Без надлежащего на то Разрешения",50,10,15,14}//50,10,15,14
};

stock police_OnGameModeInit()
{

	print("  vw_police 1.0 By: DANGER1979");
	print("_____________________________________________");
	print(" ");

}

stock police_OnPlayerConnect(playerid)
{
    //удаленные шлакбаумы фбр
	RemoveBuildingForPlayer(playerid, 968, -2436.810, 495.468, 29.679, 0.250);
	RemoveBuildingForPlayer(playerid, 966, -2436.850, 495.453, 28.953, 0.250);
	RemoveBuildingForPlayer(playerid, 967, -2438.729, 495.007, 29.101, 0.250);
	RemoveBuildingForPlayer(playerid, 1622, -2447.010, 516.046, 32.648, 0.250);
}


stock police_OnPlayerExitedMenu(playerid, Menu:Current)
{
	if(Current == mPoliceDepartment)//для участков полиции
	{
		HideMenuForPlayerEx(Current,playerid);
		TogglePlayerControllableEx(playerid, 1);
	}
}

stock police_OnPlayerSelectedMenuRow(playerid, row, Menu:Current)
{
	//new Menu:Current = GetPlayerMenu(playerid);//получить ID меню
	if(Current != mPoliceDepartment) return 1;
	switch(row)
	{
		case 0://Wanted list
		{
			if(PlayerInfo[playerid][pMember] == DoD || IsACop(playerid))
			{   //если игрок военный или коп
				WantedList(playerid);
				TogglePlayerControllableEx(playerid, 1);
			}
			else
			{
				ShowMenuForPlayerEx(mPoliceDepartment, playerid);
				SendClientMessage(playerid, COLOR_GREY, "   Вы не Коп / FBI / National Guard !");
			}
		}
		case 1://Clear Wanted
		{
			//new member = PlayerInfo[playerid][pMember];
			new leader = PlayerInfo[playerid][pLeader];
			//new rank = PlayerInfo[playerid][pRank];
	 		if(IsACop(playerid) || leader == 5 || leader == 6)
			{
				TogglePlayerControllableEx(playerid, 1);
				ShowPlayerDialogEx(playerid, CLEARWANTED_DIALOG, DIALOG_STYLE_INPUT, "Clear Wanted", "Введите ID игрока [playerid] \nили часть имени [PartOfName]", "OK", "Cancel");
			}
			else
			{
				/*if(WantedLevel[playerid] >= 2)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Вы розыскиваетесь как особо опасный преступник и Вы не можете снять с себя розыск !");
				}
				else if(WantedLevel[playerid] == 1)
				{*/   //для экономики
				new ticket;
				if(PlayerInfo[playerid][pArticle] >= 1 && PlayerInfo[playerid][pArticle] <= 36)
				{
					for(new i=0; i<sizeof(PDD); i++)
					{
						if(PlayerInfo[playerid][pArticle] != PDD[i][Article]) continue;
						if(PlayerInfo[playerid][pPart] != PDD[i][Part]) continue;
		 				ticket = PDD[i][Bail]*WantedLevel[playerid]*ticket_rate;//3600
						break;
					}
				}
				else if(PlayerInfo[playerid][pArticle] >= 83)
				{
					for(new i=0; i<sizeof(PenalCode); i++)
					{
						if(PlayerInfo[playerid][pArticle] != PenalCode[i][Article]) continue;
						if(PlayerInfo[playerid][pPart] != PenalCode[i][Part]) continue;
						ticket = PenalCode[i][Bail]*WantedLevel[playerid]*ticket_rate;//3600
						break;
					}
				}
				else
				{
					if(WantedPoints[playerid] <= 0 && GaiWant[playerid] == 1) { ticket = 500; }//штраф за нарушение ПДД
					else if(WantedPoints[playerid] > 0) { ticket = WantedPoints[playerid]*500; }//5000 в зависимости от очков розыска начислить бабки
				}
				TicketMoney[playerid] = ticket;
		        if(GetPlayerMoneyH(playerid) > TicketMoney[playerid])
		        {
					GivePlayerMoneyH(ffamily+FBI, playerid, -TicketMoney[playerid]);
				}
		        else if(PlayerInfo[playerid][pBank] > TicketMoney[playerid])
		        {
					GivePlayerMoneyB(ffamily+FBI, playerid, -TicketMoney[playerid]);
				}
		        else
		        {
		            SendClientMessage(playerid, COLOR_GREY, "   Вы не можете позволить себе оплатить штраф !");
					return 1;
		        }
				PlayerInfo[playerid][pTicket] ++;

				if(ticket == 500) FamilyInfo[DoT][fBank] += TicketMoney[playerid];
				else FamilyInfo[FBI][fBank] += TicketMoney[playerid];

				format(strings, sizeof(strings), "Bы оплатили штраф в размере $%d. Уровень Преступности был %d.", TicketMoney[playerid], LevelToCriminality);
				SendClientMessage(playerid, COLOR_BLUEGREY,strings);// Права и антирадар конфискованы!

				PlayerInfo[playerid][pArticle] = 0;//убрали статью
				PlayerInfo[playerid][pPart] = 0;//убрали часть
				ClearCrime(playerid, playerid, TicketMoney[playerid]);
				TicketMoney[playerid] = 0;
				ShowMenuForPlayerEx(mPoliceDepartment, playerid);
			}
		}
		case 2://MobileDataComputer
		{
			/*new Menu:Current = GetPlayerMenu(playerid);//получить ID меню
			if(Current == mPoliceDepartment)
			{*/
			HideMenuForPlayerEx(mPoliceDepartment,playerid);
			//}
			MobileDataComputer(playerid);
			//TogglePlayerControllableEx(playerid, 0);//обездвиживает
		}
		case 3://Lock Door
		{
	        if(IsACop(playerid))
	        {
				if(gPDLockDoor == 1)
				{
					gPDLockDoor = 0;
					GameTextForPlayerEx(playerid, "~w~Door ~g~Unlocked", 5000, 6);
					PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
					ShowMenuForPlayerEx(mPoliceDepartment, playerid);
				}
				else// if(gPDLockDoor == 0)
				{
					gPDLockDoor = 1;
					GameTextForPlayerEx(playerid, "~w~Door ~r~Locked", 5000, 6);
					PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
					ShowMenuForPlayerEx(mPoliceDepartment, playerid);
				}
	        }
			else
			{
			    SendClientMessage(playerid, COLOR_GREY, "   Вы не Коп / FBI!");// / National Guard
				ShowMenuForPlayerEx(mPoliceDepartment, playerid);
			}
		}
	}
	return 1;
}


stock WantedList(playerid)
{   //вызывается из police_OnPlayerSelectedMenuRow(playerid, row)
	//new strings[MAX_STRING];
	//format(strings, sizeof(strings), "Список Розыскиваемых:", LevelToCriminality);
	SendClientMessage(playerid, COLOR_BROWNGREEN, "Список Розыскиваемых:");

	new wanted_counter, ind, strtmp[128];
    for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(WantedLevel[i] > 0 && PlayerInfo[i][pJailed] == 0)
		{
			if(PlayerInfo[i][pArticle] >= 139) format(strtmp, sizeof(strtmp), "%s{99CCFF}%s[%d]: %d", strtmp, PlayerName(i), i, WantedLevel[i]);
			else if(PlayerInfo[i][pArticle] >= 1 && PlayerInfo[i][pArticle] <= 36) format(strtmp, sizeof(strtmp), "%s{33CCCC}%s[%d]: %d", strtmp, PlayerName(i), i, WantedLevel[i]);
			else format(strtmp, sizeof(strtmp), "%s{666699}%s[%d]: %d", strtmp, PlayerName(i), i, WantedLevel[i]);
			ind ++;
			if(ind > 3)
			{//если счётчик кол-ва людей не одной строке больше 3, то
			    SendClientMessage(playerid, COLOR_BLUEGREY, strtmp);
			    ind = 0;
				strdel(strtmp, 0, sizeof(strtmp));
			}
			else
			{
				format(strtmp, sizeof(strtmp), "%s, ", strtmp);//ставим запятую между каждым
			}
			wanted_counter ++;
		}
	}
	if(ind > 0 && ind <= 3)
	{//ставим точку в конце строки
		strtmp[strlen(strtmp)-2] = '.';
	    SendClientMessage(playerid, COLOR_BLUEGREY, strtmp);
	}
	format(strings, sizeof(strings), "Цвет РОЗЫСКА, {%06x}Цвет ДПС, {%06x}Цвет ФБР", COLOR_DARKTURQUOISE >>> 72, COLOR_PALEPURPLE >>> 72);
	SendClientMessage(playerid, COLOR_BLUEGREY, strings);

	format(strings, sizeof(strings), "Tекущий Уровень Преступности в Штате Сан-Андреас: %d.", LevelToCriminality);
	SendClientMessage(playerid, COLOR_BROWNGREEN, strings);
}


stock police_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	//#pragma unused inputtext
	if(dialogid != CLEARWANTED_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	new msgitem[256+1];
	new giveplayerid;
//mPoliceDepartment
	if(!response)
	{
		TogglePlayerControllableEx(playerid, 0);//обездвиживает
		if(PlayerInfo[playerid][pLocal] >= 246 && PlayerInfo[playerid][pLocal] <= 248) ShowMenuForPlayerEx(mPoliceDepartment, playerid);
		else if(PlayerInfo[playerid][pLocal] == 100) ShowMenuForPlayerEx(mBank, playerid);
		return 1;
	}
//ShowPlayerDialogEx(playerid, 16, DIALOG_STYLE_INPUT, "Clear Wanted", "Введите ID игрока [playerid] \nили часть имени [PartOfName]", "OK", "Cancel");
//ShowPlayerDialogEx(playerid, 16, DIALOG_STYLE_INPUT, "Transfer", "Введите ID игрока [playerid] \nили часть имени [PartOfName]", "OK", "Cancel");
//Clear Wanted
	if(PlayerInfo[playerid][pLocal] >= 246 && PlayerInfo[playerid][pLocal] <= 248)
	{
		giveplayerid = ReturnUser(inputtext);
		if( !IsPlayerConnected(giveplayerid) )
		{
			format(msgitem, sizeof(msgitem), "   ID:%d отсутствует на сервере.", giveplayerid);
			SendClientMessage(playerid, COLOR_GREY, msgitem);
			return 1;
		}
	    if(WantedLevel[giveplayerid] <= 0)
		{
		  	SendClientMessage(playerid, COLOR_GREY, "   Данный игрок не в Розыске!");
		  	return 1;
		}
		if(IsACop(playerid) && PlayerInfo[playerid][pRank] >= 4)
		{
			if(!IsAtPolice(playerid))
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не в полицейском участке!");
				return 1;
			}
			if(gGotOrder[playerid] != giveplayerid && PlayerInfo[giveplayerid][pAdmin] != 9)
			{
			    SendClientMessage(playerid, COLOR_GREY, "   У Вас нет Разрешения на снятие уровня преступности этого человека !");
			    return 1;
			}
			if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "   Вы не можете снять Уровень Преступности с самого себя!"); return 1; }
		   	if(PlayerInfo[giveplayerid][pJailed] > 0) { SendClientMessage(playerid, COLOR_GREY, "   Вы не можете снять Уровень Розыска с заключенного!"); return 1; }
			format(msgitem, sizeof(msgitem), "* Вы сняли Уровень Преступности с %s.", PlayerName(giveplayerid));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
			format(msgitem, sizeof(msgitem), "* Офицер %s снял Уровень Преступности.", PlayerName(playerid));
			SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
			PlayerInfo[giveplayerid][pArticle] = 0;//убрали статью
			PlayerInfo[giveplayerid][pPart] = 0;//убрали часть
			gGotOrder[playerid] = MAX_PLAYERS-1;
			//PlayerInfo[giveplayeri][pJailTime] = 0;//убрали срок
			//PlayerInfo[giveplayerid][pJailed] = 0;//игрок не в тюрьме
			ClearCrime(giveplayerid, playerid, 1);
		}
		else if(PlayerInfo[playerid][pLeader] == LCN || PlayerInfo[playerid][pLeader] == Yakuza)//если вы лидер семьи
		{
			//if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "   Вы не можете снять Уровень Преступности с самого себя!"); return 1; }
			if(PlayerInfo[giveplayerid][pJailed] > 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете снять Уровень Розыска с заключенного!");
				return 1;
			}
		    if(GetPlayerMoneyH(playerid) < 500)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вам нужно $500, чтобы снимать Уровень Преступности!");
				return 1;
			}
		   	if(WantedLevel[giveplayerid] > 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы пока не можете снять Уровень Розыска с подозреваемого!");
				return 1;
			}
			PlayerInfo[giveplayerid][pArticle] = 0;//убрали статью
			PlayerInfo[giveplayerid][pPart] = 0;//убрали часть
			ClearCrime(giveplayerid, playerid, 500);

			GivePlayerMoneyH(ftax, playerid, -500);//для экономики
			if(BizInfo[0][bTill] < 2147480000) { BizInfo[0][bTill] += 500; BizInfo[0][bExport] += 500; }

		    format(msgitem, sizeof(msgitem), "* Вы очистили Записи и Уровень Разыска с {FFFFFF}%s{0080FF} за {33AA33}$500.", PlayerName(giveplayerid));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
			format(msgitem, sizeof(msgitem), "* Лидер Семьи %s, очистил ваши Записи и Уровень Разыска.", PlayerName(playerid));
			SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
		}
		else SendClientMessage(playerid, COLOR_GREY, "   Вы не Полицейский >4 ранга / Family Leader !");// National Guard
	}
	return 1;
}

stock police_OneSecondTimers(playerid)
{
	if(	gTutorial[playerid] == 1) return 1;
	//для полицейcких вертолётов
	if(	GPS_OnOff[playerid] == 1 && PlayerInfo[playerid][pGPS] == 1 &&
		GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
    	if((PlayerInfo[playerid][pMember] == DoT || PlayerInfo[playerid][pMember] == DoH) &&
			(nCarModel[playerid] == 497 ||	nCarModel[playerid] == 447) )
		{
		    if(MarkerToPlayer[playerid] != MAX_PLAYERS-1 && GetPVarInt(playerid, "gCheckpointStatus") < MAX_PLAYERS)
			{
				new Float:X,Float:Y,Float:Z;
				GetPlayerPos(MarkerToPlayer[playerid], X, Y, Z);
				SetPlayerRouting(playerid, X, Y, Z);
			}
		}
	}
	return 1;
}

#define MAX_ROADBLOCK 60
enum rbInfo
{
	rbCreated,
    Float:rbX,
    Float:rbY,
    Float:rbZ,
    rbObject
};
new RoadBlock[MAX_ROADBLOCK][rbInfo];//массив добавленных блоков


stock police_OnPlayerKeyState_LEFT(playerid)
{
		new strcmd[MAX_STRING];//, tmp[MAX_STRING], gMessage[MAX_STRING];
		if(PlayerInfo[playerid][pMember] != DoT && PlayerInfo[playerid][pAdmin] != 4)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not a Road Policemen San-Andreas !");
			return 1;
		}
		if(PlayerInfo[playerid][pRank] < 4 && PlayerInfo[playerid][pAdmin] != 4)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Вам нужен ранг 4, чтобы устанавливать дорожные блоки !");
			return 1;
		}
        if(gOnDuty[playerid] != 1 && PlayerInfo[playerid][pAdmin] != 4)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Вы не при исполнении служебных обязанностей !");
		    return 1;
		}

		if(PlayerInfo[playerid][pInt] != 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   В интерьере не допускается устанавливать дорожные блоки !");
			return 1;
		}
		if(IsPlayerInArea(playerid, specialzone[0]))
		{
			SendClientMessage(playerid, COLOR_GREY, "   В этом месте запрещена установка дорожных блоков !");
			return 1;
		}
		new Float:rX, Float:rY, Float:rZ, Float:rA;
		GetXYZInFrontOfPlayer(playerid, 2.0, rX,rY,rZ, rA);
		if(rbCounter < MAX_ROADBLOCK/2)
		{
	  	    if(RoadBlock[rbCounter][rbCreated] == 0)
	  	    {
	            RoadBlock[rbCounter][rbCreated] = 1;
	            RoadBlock[rbCounter][rbX] = rX;
	            RoadBlock[rbCounter][rbY] = rY;
	            RoadBlock[rbCounter][rbZ] = rZ;
				RoadBlock[rbCounter][rbObject] = CreateObjectEx(981, rX, rY, rZ, 0.0, 0.0, rA);
				format(strcmd, sizeof(strcmd), "%s has installed roadblock %d[%d]", PlayerName(playerid), RoadBlock[rbCounter][rbObject], rbCounter);
				SendTeamMessage(DoT, COLOR_DARKTURQUOISE, strcmd);
				rbCounter ++;
			}
	  	    if(RoadBlock[rbCounter][rbCreated] == 0)
	  	    {
	            RoadBlock[rbCounter][rbCreated] = 1;
	            RoadBlock[rbCounter][rbX] = rX;
	            RoadBlock[rbCounter][rbY] = rY;
	            RoadBlock[rbCounter][rbZ] = rZ-0.3;
				RoadBlock[rbCounter][rbObject] = CreateObjectEx(982, rX, rY, rZ-0.3, 0.0, 0.0, rA+90.0);
				format(strcmd, sizeof(strcmd), "%s has installed roadblock %d[%d]", PlayerName(playerid), RoadBlock[rbCounter][rbObject], rbCounter);
				SendTeamMessage(DoT, COLOR_DARKTURQUOISE, strcmd);
				rbCounter ++;
			}
		}
		else SendClientMessage(playerid, COLOR_GREY, "   Достигнут предел установки дорожных блоков !");
		//SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /roadblock [number radar 1-32] (0 = OFF)");
		return 1;
}

stock police_OnPlayerKeyState_RIGHT(playerid)
{
		new strcmd[MAX_STRING];//, tmp[MAX_STRING], gMessage[MAX_STRING];
	    if((PlayerInfo[playerid][pMember] != DoT && PlayerInfo[playerid][pAdmin] < 4) ||
			(PlayerInfo[playerid][pMember] == DoT && PlayerInfo[playerid][pRank] < 4))
	    {
		    SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду: destroyed roadblock !");
	        return 1;
	    }
        if(gOnDuty[playerid] != 1)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Вы не при исполнении служебных обязанностей !");
		    return 1;
		}
        //tmp = strtok(cmdtext, idx);
		//if(!strlen(tmp))
		//{
	    for(new rb = sizeof(RoadBlock)-1; rb >= 0; rb--)
	  	{
	  	    if(RoadBlock[rb][rbCreated] == 1)
	  	    {
		  	    if(IsPlayerInRangeOfPoint(playerid, 30.0, RoadBlock[rb][rbX], RoadBlock[rb][rbY], RoadBlock[rb][rbZ]))
		        {
		            RoadBlock[rb][rbCreated] = 0;
		            RoadBlock[rb][rbX] = 0.0;
		            RoadBlock[rb][rbY] = 0.0;
		            RoadBlock[rb][rbZ] = 0.0;
		            DestroyObjectEx(RoadBlock[rb][rbObject], 15);
					format(strcmd, sizeof(strcmd), "%s has destroyed roadblock %d[%d]", PlayerName(playerid), RoadBlock[rb], rb);
					SendTeamMessage(DoT, COLOR_DARKTURQUOISE, strcmd);
					rbCounter --;
			        return 1;//break;
		  	    }
			}
	  	}
		SendClientMessage(playerid, COLOR_GREY, "   Вы далеко от объекта !");
			//return 1;
		//}
		
		/*new oRoadBlock = strval(tmp);
		if(oRoadBlock == 0)// && PlayerInfo[playerid][pRank] >= 5
		{
			if(PlayerInfo[playerid][pAdmin] >= 4 || PlayerInfo[playerid][pRank] >= 11)
			{
		    	for(new rb = 0; rb < sizeof(RoadBlock); rb++)
		  		{
		  	    	if(RoadBlock[rb][rbCreated] == 1)
		  	    	{
			            RoadBlock[rb][rbCreated] = 0;
			            RoadBlock[rb][rbX] = 0.0;
			            RoadBlock[rb][rbY] = 0.0;
			            RoadBlock[rb][rbZ] = 0.0;
			            DestroyObjectEx(RoadBlock[rb][rbObject], 16);
			            rbCounter --;
			  	    }
				}
			  	SendClientMessage(playerid, COLOR_GREY, "   Все Созданные ПОЛИЦЕЙСКИЕ БЛОКИ Уничтожены !");
				//GameTextForPlayerEx(playerid, "~g~All PoliceBlock deployed successfully", 5000, 5);
				return 1;
			}
		}*/
		return 1;
}

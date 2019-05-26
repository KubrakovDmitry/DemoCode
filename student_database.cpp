#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>


using namespace std;
// данные
FILE *DBFile;
FILE *TextFile1;
FILE *TextFile2;
string DBFName[10] = "DBfile.txt";
char Delimetr = 59; //9 - табуляция, а 59 - ";" 


	//список для списка студентов	
	//узлы списка 
struct NodeList {
	struct 	NodeList *prv;		// слева
    struct 	NodeList *nxt; 	// справа
    int		IDS;			// id студента
    string	FNS;			// фамилия студента
    string	SNS;			// имя студента
    string	DBS;			// ДР студента
    int	    NZB;			// номер зачётки
    string	NFL;			// иностранный язык
    float	MBS;			// средний балл студента
    int	    PDR;			// признак удаления записи о студенте
};
	//вспомогательная структура о списке
struct ListStud{
    size_t 		size;		//размер 
    NodeList   	*head;		//указатель голова
    NodeList   	*tail;		//указатель хвост
};

// функции
int 		showMainMenu(); //Отображение главного меню программы, возврат номера пункта меню	
ListStud* 	DBLoadList();   //загрузка данных из файла в оперативную память
void 		DBshow();		//Отображение содержимого БД
void 		DBGener();		//Генерация файла данных
void 		DBSaveList( ListStud * proList ); //Сохранение списка в файл данных
void 		DBSortDB();		//Сортировка по возрастанию даты рождения	 
void 		DBSortMBI();	//Сортировка по возрастанию среднегно балла	 
void 		DBSortMBD();	//Сортировка по убыванию среднегно балла	 
void 		DBList45();		//Отображение хорошистов
//-----------------------------------------------
string 		loc_itoa(int value);	//локальное отображение числа в строку
void 		EmptyFile();	//Удаление файла
int			GenBall();		// Генерация среднего балла
//-----------------------------------------------
ListStud* 	createList();
NodeList* 	addNode( ListStud * proList , string Str );
void 		showList( ListStud * proList );			
void 		sortList( ListStud * proList  , int varSort );
int 	    getPosCharInStr(string LocStr , char LocCh , int startPos );
void 	    getSubString(string Str, char Delimiter, int startPos , int* endPos , char Arr[80] );
//-----------------------------------------------

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");
    cout << "Программа методов работы с базой данных" << endl;
    int NA = 0; // код действия программы
    int sw1; 	// для управления выходом из программы
	do{
		NA = showMainMenu(); 
		sw1 = 0;
		switch  ( NA )
		{
		case 1:
			{
				DBshow();break;
			}
		case 2:
			{	
				DBGener();break;
			}
		case 3:
			{
				DBSortMBI();break;
			}
		case 4:
			{	
				DBSortMBD();break;
			}
		case 5:
			{
				DBList45();break;
			}
		case 6:
			{
				sw1 = 1; break; // выход 	
			}		
		}
		if (sw1>0) break;
	}while(1);	
	return 0;
}

int showMainMenu() 
{ //отображение главного меню программы, возврат номера пункта меню
	int numberPunkt = -1;	
	cout << "Главное меню программы:" << endl;
	cout << "1 - Отобразить содержимое файла БД" << endl;
	cout << "2 - Сгенерировать наполнение файла БД" << endl;
	cout << "3 - Сортировать по возрастанию среднего балла" << endl;
	cout << "4 - Сортировать по убыванию среднего балла" << endl;
	cout << "5 - Вывод списка студентов со средним баллом выше 4,0" << endl;
	cout << "6 - Выход из программы" << endl;
    do{		
		cin >> numberPunkt;
		//cout << endl;
		if ( 0 < numberPunkt && numberPunkt < 8 ) break;
	}while(1);
	return numberPunkt;
}
ListStud* DBLoadList() //загрузка данных из файла в оперативную память
{
	DBFile = fopen( "DBfile.txt" , "r");
	if(DBFile == NULL){
		cout << "Файл БД отсутствует! Сгенерируйте его!!!\n";
		return NULL;
	};
	char str [80];
	ListStud* loc_ListStud = createList();	
	do{
		if (fscanf( DBFile , "%s", str )==EOF) break;
		NodeList* tmp =	addNode( loc_ListStud , str ); //здесь разбор строки файла и помещение в список
	}while(1);	
	fclose( DBFile );
	return loc_ListStud;	
}
void DBshow()		//отображение содержимого БД
{
	ListStud* loc_ListStud = DBLoadList();
	showList( loc_ListStud ); 
	return;	
}
void DBGener()		//Генерация файла данных
{
	TextFile1 = fopen("Names.txt", "r");
	TextFile2 = fopen("Names2.txt", "r");
	char Names1[20];
	char Names2[20];
	int countRecords2Work=10;
	DBFile = fopen( "DBfile.txt" , "r");
	if(DBFile == NULL){
		DBFile = fopen("DBfile.txt", "w");
		if(DBFile == NULL){
			cout << " Ошибка открытия файла результатов (место 1). Программа завершена! " << endl;
			exit(0);
		}	
	}
	else{
		fclose( DBFile );
		EmptyFile();
		DBFile = fopen("DBfile.txt", "w");
		if(DBFile == NULL){
			cout << " Ошибка открытия файла результатов (место 2). Программа завершена! " << endl;
			exit(0);
		}			
	};

	unsigned rand_value = 11;
	srand(rand_value);
	for ( int i=1 ; i<=countRecords2Work ; i++)
	{
		fgets(Names1, 20, TextFile1);
		fgets(Names2, 20, TextFile2);
		fprintf( DBFile, "%d" , i ); 			// ун.# объекта
		fprintf( DBFile, "%c" , Delimetr );
		fprintf( DBFile, "%s" , Names1 ); 	//"Фамилия"loc_itoa(i)
		fprintf( DBFile, "%c" , Delimetr );
		fprintf( DBFile, "%s" , Names2 ); 	//"Имя"loc_itoa(i)
		fprintf( DBFile, "%c" , Delimetr );
		fprintf( DBFile, "%s" , "2000/01/01" ); //"Дата рождения" 
		fprintf( DBFile, "%c" , Delimetr );
		fprintf( DBFile, "%d" , 100000+i ); 	//"номер зачетной книжки" 
		fprintf( DBFile, "%c" , Delimetr );
		fprintf( DBFile, "%s" , "English" ); 	//"изучаемый иностранный язык" 
		fprintf( DBFile, "%c" , Delimetr );		
		fprintf( DBFile, "%d" , GenBall() );	//"Средний балл"
		fprintf( DBFile, "%c" , Delimetr );
		fprintf( DBFile, "%d" , 0 );			//"Признак удалённости записи из БД"	0 - есть; 1 - удалена 	
		fprintf( DBFile, "\n");		
	}
	if (not (DBFile==NULL) ) {
		fclose( DBFile );
	};
	return;	
}
void 		DBSaveList( ListStud * proList ) //Сохранение списка в файл данных
{
	// проверка наличия данных в списке
	if ( proList == NULL ) {
		puts("Списка студентов для отображения не указано\n");
		return;
	}
	if ( proList->size == 0 ) {
		puts("Список студентов для отображения пуст\n");
		return;
	}
	if ( proList->head == NULL ) {
		puts("Список студентов поврежден\n");
		return;
	}
	DBFile = fopen( "DBfile2.txt" , "r");
	if(DBFile == NULL){
		DBFile = fopen("DBfile2.txt", "w");
		if(DBFile == NULL){
			cout << " Ошибка открытия файла результатов (место 1). Программа завершена! " << endl;
			exit(0);
		}	
	}
	else{
		fclose( DBFile );
		system("del DBfile2.txt");
		DBFile = fopen("DBfile2.txt", "w");
		if(DBFile == NULL){
			cout << " Ошибка открытия файла результатов (место 2). Программа завершена! " << endl;
			exit(0);
		}			
	};
	NodeList *tmp;	
	tmp = new NodeList;
	tmp = proList->head;
	char tmpstr[3];	
	do{
		fprintf( DBFile, "%d" , tmp->IDS ); 			// ун.# объекта
		fprintf( DBFile, "%c" , Delimetr );
		fprintf( DBFile, "fisrtName_%d" , tmp->IDS ); 	//"Фамилия"loc_itoa(i)
		fprintf( DBFile, "%c" , Delimetr );
		fprintf( DBFile, "sekondName%d" , tmp->IDS );	//"Имя"loc_itoa(i)  
		fprintf( DBFile, "%c" , Delimetr );
		fprintf( DBFile, "%s" , "2000/01/01" ); //"Дата рождения" 
		fprintf( DBFile, "%c" , Delimetr );
		fprintf( DBFile, "%d" , tmp->NZB ); 	//"номер зачетной книжки" 
		fprintf( DBFile, "%c" , Delimetr );
		fprintf( DBFile, "%s" , "English" ); 	//"изучаемый иностранный язык" 
		fprintf( DBFile, "%c" , Delimetr );	
		itoa( int( tmp->MBS*10 ), tmpstr, 10 );	
		fprintf( DBFile, "%s" , tmpstr );	    //"Средний балл"
		fprintf( DBFile, "%c" , Delimetr );
		itoa(int( tmp->PDR ), tmpstr, 10 );
		fprintf( DBFile, "%s" , tmpstr );		//"Признак удалённости записи из БД"	0 - есть; 1 - удалена 	
		fprintf( DBFile, "\n");		
		if (tmp->nxt == NULL) break;
		tmp = tmp->nxt; 
	}while(1);
	if (not (DBFile==NULL) ) {
		fclose( DBFile );
	};
	system("del DBfile.txt");
	system("copy DBfile2.txt DBfile.txt");
	return;	
}

void DBSortDB()		//Сортировка по возрастанию даты рождения	 
{
	cout << "процедура не готова! и не нужно!!!\n";
	return;
}
void DBSortMBI()	//Сортировка по возрастанию среднего балла	 
{
	DBFile = fopen( "DBfile.txt" , "r");
	if(DBFile == NULL){
		cout << "Файл БД отсутствует! Сгенерируйте его!!!\n";
		return;
	};
	char str [80];
	ListStud* loc_ListStud = createList();	
	do{
		if (fscanf( DBFile , "%s", str )==EOF) break;
		NodeList* tmp =	addNode( loc_ListStud , str ); //здесь разбор строки файла и помещение в список
	}while(1);	
	fclose( DBFile );
	cout << "Исходный список" << endl; 
	showList( loc_ListStud );
	sortList( loc_ListStud , 1 );
	cout << "Отсортированный список" << endl;	
	showList( loc_ListStud );
	DBSaveList( loc_ListStud ); 
	return;
}
void DBSortMBD()	//Сортировка по убыванию среднегно балла	 
{
	DBFile = fopen( "DBfile.txt" , "r");
	if(DBFile == NULL){
		cout << "Файл БД отсутствует! Сгенерируйте его!!!\n";
		return;
	};
	char str [80];
	ListStud* loc_ListStud = createList();	
	do{
		if (fscanf( DBFile , "%s", str )==EOF) break;
		NodeList* tmp =	addNode( loc_ListStud , str ); //здесь разбор строки файла и помещение в список
	}while(1);	
	fclose( DBFile );	
	cout << "Исходный список" << endl;
	showList( loc_ListStud ); 
	sortList( loc_ListStud , 2 );
	cout << "Отсортированный список" << endl; 
	showList( loc_ListStud ); 
	DBSaveList( loc_ListStud ); 	
	return;
}
void DBList45()		//Отображение хорошистов
{
	cout << "Вывод списка хорошистов\n";
	cout << "Ждите. Процесс чтение данных о студентах \n";
	ListStud* proList = DBLoadList(); //загрузка данные формирование списка
	// проверка наличия данных в списке
	if ( proList == NULL ) {
		puts("Списка студентов для отображения не указано\n");
		return;
	}
	if ( proList->size == 0 ) {
		puts("Список студентов для отображения пуст\n");
		return;
	}
	if ( proList->head == NULL ) {
		puts("Список студентов поврежден\n");
		return;
	}
	cout << "Данных о студентах считаны \n";
	cout << "Ждите. Подготовка файла DBfile45.txt о хорошистах \n";
	DBFile = fopen( "DBfile45.txt" , "r");
	if(DBFile == NULL){
		DBFile = fopen("DBfile45.txt", "w");
		if(DBFile == NULL){
			cout << " Ошибка открытия файла результатов (место 1). Программа завершена! " << endl;
			exit(0);
		}	
	}
	else{
		fclose( DBFile );
		system("del DBfile45.txt");
		DBFile = fopen("DBfile45.txt", "w");
		if(DBFile == NULL){
			cout << " Ошибка открытия файла результатов (место 2). Программа завершена! " << endl;
			exit(0);
		}			
	};
	cout << "Ждите. Выгрузка данных о хорошистах в файл DBfile45.txt \n";
	NodeList *tmp;	
	tmp = new NodeList;
	tmp = proList->head;
	char tmpstr[3];	
	do{
		if (tmp->MBS > 4.0) 
		{
			fprintf( DBFile, "%d" , tmp->IDS ); 			// ун.# объекта
			fprintf( DBFile, "%c" , Delimetr );
			fprintf( DBFile, "fisrtName_%d" , tmp->IDS ); 	//"Фамилия"loc_itoa(i)
			fprintf( DBFile, "%c" , Delimetr );
			fprintf( DBFile, "sekondName%d" , tmp->IDS );	//"Имя"loc_itoa(i)  
			fprintf( DBFile, "%c" , Delimetr );
			fprintf( DBFile, "%s" , "2000/01/01" ); //"Дата рождения" 
			fprintf( DBFile, "%c" , Delimetr );
			fprintf( DBFile, "%d" , tmp->NZB ); 	//"номер зачетной книжки" 
			fprintf( DBFile, "%c" , Delimetr ); 
			fprintf( DBFile, "%s" , "English" ); 	//"изучаемый иностранный язык" 
			fprintf( DBFile, "%c" , Delimetr );	
			itoa( int( tmp->MBS*10 ), tmpstr, 10 );	
			fprintf( DBFile, "%s" , tmpstr );	    //"Средний балл"
			fprintf( DBFile, "%c" , Delimetr );
			itoa(int( tmp->PDR ), tmpstr, 10 );
			fprintf( DBFile, "%s" , tmpstr );		//"Признак удалённости записи из БД"	0 - есть; 1 - удалена 	
			fprintf( DBFile, "\n");		
		}
		if (tmp->nxt == NULL) break;
		tmp = tmp->nxt; 
	}while(1);
	if (not (DBFile==NULL) ) {
		fclose( DBFile );
	};
	cout << "Выгрузка данных о хорошистах в файл DBfile45.txt завершена \n";
	return;	
}
string loc_itoa(int value)	//локальное отображение числа в строку
{
    char string[10] = "";
	itoa(value, string, 10);
	return( string );
}
void EmptyFile()	// удаление файла БД полностью
{
	system("del DBfile.txt");	
}
int	GenBall()	    // Генерация среднего балла
{
	int val;
	do{
		val = 1 + rand();	
		if (val < 51 ) break; 
	}while(1);
	return( val );
}
ListStud* createList()
{
    ListStud *tmp = ( ListStud* ) malloc( sizeof( ListStud ) );
    tmp->size = 0;
    tmp->head = NULL; 
    tmp->tail = NULL; 
    cout << "Список создан. ";
	cout << "Вспомогательная структура находиться по адресу: " << tmp << endl;  
    return tmp;			
}
NodeList* 	addNode( ListStud * proList , string Str )
{
	if ( proList == NULL ) proList = createList();
	NodeList *tmp;	
	tmp = new NodeList;
    // str обработать!!! 
    if ( proList->size == 0 ) 	
		{ 
			tmp->prv		= NULL;
			tmp->nxt		= NULL;
			proList->head   = tmp;
			proList->tail   = tmp;
			proList->size   = 1;
		}
	else 
		{ 
			tmp->prv	    = proList->tail;
			tmp->nxt	    = NULL;	
			proList->tail->nxt = tmp;
			proList->size   ++;
			proList->tail   = tmp;		    	
		}
		
	int pp = 0;
	int pp1 = 0;
	char tempstr[80];
	getSubString( Str , Delimetr , pp , &pp1 , tempstr );
	tmp->IDS = atoi( tempstr );
	pp=pp1+1;
	getSubString( Str , Delimetr , pp , &pp1 , tempstr);
	tmp->FNS = string(tempstr);
	pp=pp1+1;	
	getSubString( Str , Delimetr , pp , &pp1 , tempstr);
	tmp->SNS = string(tempstr);
	pp=pp1+1;
	getSubString( Str , Delimetr , pp , &pp1 , tempstr);
	tmp->DBS = string(tempstr);
	pp=pp1+1;	
	getSubString( Str , Delimetr , pp , &pp1 , tempstr);
	tmp->NZB = atoi(tempstr);
	pp=pp1+1;	
	getSubString( Str , Delimetr , pp , &pp1 , tempstr);
	tmp->NFL = string(tempstr);
	pp=pp1+1;	
	getSubString( Str , Delimetr , pp , &pp1 , tempstr);
	tmp->MBS = float ( atoi(tempstr) )/10;
	pp=pp1+1;
	getSubString( Str , Delimetr , pp , &pp1 , tempstr);
	tmp->PDR = atoi(tempstr);
	return tmp;
}
void        showList( ListStud * proList )
{
	if ( proList == NULL ) {
		puts("Списка студентов для отображения не указано\n");
		return;
	}
	if ( proList->size == 0 ) {
		puts("Список студентов для отображения пуст\n");
		return;
	}
	if ( proList->head == NULL ) {
		puts("Список студентов поврежден\n");
		return;
	}
	cout << "Список   начинается  по адресу: " << proList->head << endl;
	cout << "Список заканчивается по адресу: " << proList->tail << endl;
	printf("Список студентов.\nКоличество студентов в списке %d\n" , proList->size );	
	printf( "------------------------------------------------------------------------------------------------\n" );
	cout << "|";
	cout.width(5);
	cout.setf(ios::left);	
	cout << " №пп " << "|";
	cout.width(20);
	cout.setf(ios::left);	
	cout << "Фамилия" << "|";	
	cout.width(20);
	cout.setf(ios::left);
	cout << "Имя" << "|";
	cout.width(10);	
	cout << "Дата рожд." << "|";
	cout.width(10);	
	cout << "№ зач. кн." << "|";
	cout.width(10);	
	cout.setf(ios::left);
	cout << "Ин.яз.ст." << "|";
	cout.width(7);
	cout.precision(3);
	cout << "Ср.Балл" << "|";
	cout.width(3);
	cout.precision(0);	
	cout  << "ПУС" << endl;
	printf( "------------------------------------------------------------------------------------------------\n" );
	NodeList *tmp;	
	tmp = new NodeList;
	tmp = proList->head;	
	int i = 0;
	do{	
		cout << "|";
		cout.width(5);	
		cout.setf(ios::left);	
		cout << tmp->IDS << "|";
		cout.width(20);
		cout.setf(ios::left);	
		cout << tmp->FNS << "|";	
		cout.width(20);
		cout.setf(ios::left);
		cout << tmp->SNS << "|";
		cout.width(10);	
		cout << tmp->DBS << "|";
		cout.width(10);	
		cout << tmp->NZB << "|";
		cout.width(10);	
		cout.setf(ios::left);
		cout << tmp->NFL << "|";
		cout.width(7);
		cout.precision(4);
		cout << tmp->MBS << "|";
		cout.width(3);
		cout.precision(0);	
		cout << tmp->PDR << endl;	
		if (tmp->nxt == NULL) break;
		tmp = tmp->nxt; 
		i++;
	}while(1);
	printf( "------------------------------------------------------------------------------------------------\n" );	
	return;
}
void 		sortList( ListStud * proList  , int varSort )
{
	if ( proList == NULL ) {
		puts("Списка студентов для отображения не указано\n");
		return;
	}
	if ( proList->head == NULL ) {
		puts("Список студентов поврежден\n");
		return;
	}
	if ( proList->size == 0 ) {
		puts("Список студентов для отображения пуст\n");
		return;
	}	
	if ( proList->size == 1 ) {
		puts("Список студентов сортировать не надо\n");
		return;
	}	
	int CA; // счётчик перестановок
    NodeList *tmp;	
	tmp = new NodeList;
	NodeList *buf;
	buf = new NodeList;		
	do{
		CA = 0;
		tmp = proList->head;
		do{
			switch ( varSort ){
				case 1:
				{
					if (tmp->MBS>tmp->nxt->MBS) 
					{
						CA++;
						buf->IDS = tmp->IDS;	
						buf->FNS = tmp->FNS;	
						buf->SNS = tmp->SNS;	
						buf->DBS = tmp->DBS;	
						buf->NZB = tmp->NZB;	
						buf->NFL = tmp->NFL;						
						buf->MBS = tmp->MBS;						
						buf->PDR = tmp->PDR;
						
						tmp->IDS = tmp->nxt->IDS;	
						tmp->FNS = tmp->nxt->FNS;	
						tmp->SNS = tmp->nxt->SNS;	
						tmp->DBS = tmp->nxt->DBS;	
						tmp->NZB = tmp->nxt->NZB;	
						tmp->NFL = tmp->nxt->NFL;						
						tmp->MBS = tmp->nxt->MBS;						
						tmp->PDR = tmp->nxt->PDR;
						
						tmp->nxt->IDS = buf->IDS;	
						tmp->nxt->FNS = buf->FNS;	
						tmp->nxt->SNS = buf->SNS;	
						tmp->nxt->DBS = buf->DBS;	
						tmp->nxt->NZB = buf->NZB;	
						tmp->nxt->NFL = buf->NFL;						
						tmp->nxt->MBS = buf->MBS;						
						tmp->nxt->PDR = buf->PDR;						
					};
					break;
				}
				case 2:
				{
					if (tmp->MBS<tmp->nxt->MBS) 
					{
						CA++;
						buf->IDS = tmp->IDS;	
						buf->FNS = tmp->FNS;	
						buf->SNS = tmp->SNS;	
						buf->DBS = tmp->DBS;	
						buf->NZB = tmp->NZB;	
						buf->NFL = tmp->NFL;						
						buf->MBS = tmp->MBS;						
						buf->PDR = tmp->PDR;
						
						tmp->IDS = tmp->nxt->IDS;	
						tmp->FNS = tmp->nxt->FNS;	
						tmp->SNS = tmp->nxt->SNS;	
						tmp->DBS = tmp->nxt->DBS;	
						tmp->NZB = tmp->nxt->NZB;	
						tmp->NFL = tmp->nxt->NFL;						
						tmp->MBS = tmp->nxt->MBS;						
						tmp->PDR = tmp->nxt->PDR;
						
						tmp->nxt->IDS = buf->IDS;	
						tmp->nxt->FNS = buf->FNS;	
						tmp->nxt->SNS = buf->SNS;	
						tmp->nxt->DBS = buf->DBS;	
						tmp->nxt->NZB = buf->NZB;	
						tmp->nxt->NFL = buf->NFL;						
						tmp->nxt->MBS = buf->MBS;						
						tmp->nxt->PDR = buf->PDR;	
					};
					break;
				}
			};
			if (tmp->nxt->nxt == NULL) break;
			tmp = tmp->nxt;
		}while(1);
		if (CA==0) break;
	}while(1);
	return;
}

int getPosCharInStr(string LocStr , char LocCh , int startPos )
{	
	for (int i = startPos ; i < 80 ; i++ ){
		if (LocStr[i]==LocCh){return i;}	
	}
	return 0;
}
void getSubString(string Str, char Delimiter, int startPos , int* endPos , char Arr[80] )
{
	int p = getPosCharInStr( Str , Delimetr , startPos );
	int j = 0;
	for(int i=startPos; i < p; i++)
	{
		Arr[j] = Str[i];
		j++;
	}
	Arr[j]='\0';
	*endPos = p;
	return;
}

//конец


#include <iostream>
#include <clocale>
#include <string.h>
#include <stdlib.h>

using namespace std;

#define maxLenNameFile 256 
#define maxLenStr 1024 

//структура двусвязный список
//=часть списка - один элемент
struct Node {
    struct Node *next;
    struct Node *prev; 		//Указатель prev хранит адрес предыдущего узла, если его нет (значит, это первый узел) то переменная равна NULL.
    int lenWord;			//длина слов
    int countLenWord;		//количество случаев	
    float share;   			//relative share(относительная доля)
};
//=вспомогательная структура о  списке
struct DblLinkedList {
    size_t size;			//размер 
    Node *head;				//указатель head, ссылающийся на первый элемент
    Node *tail;				//указатель tail, ссылающийся на последний элемент
};
//структура двусвязный список::конец
DblLinkedList *ListStat;	//список статистики
//=====================================================================================================================
int getDataCL();									//ввод данных с консоли
int getDataTF();									//ввод данных из текстового файла
int output2screen( DblLinkedList *list );			//вывод на экран
int	output2tf( DblLinkedList *list );				//вывод в файл
//=====================================================================================================================
DblLinkedList* createDblLinkedList(); 				// создание пустого списка для статистики длин слов
void deleteDblLinkedList(DblLinkedList **list); 	// удаление списка (внутри очистка - утечек памяти не будет!!!) 
int workAboutWord( char curWord[maxLenStr] , DblLinkedList *list );
int getCountWord( DblLinkedList *list ); 			//подсчёт количества введённых слов
void showList( DblLinkedList *list ); 				//отображение списка
void sortList( DblLinkedList *list ); 				//сортировка ListStat 
int calcShare( DblLinkedList *list ); 				//расчёт доль ListStat	

void copySubString( char BigString[maxLenStr] , int fPos , int lastPos , char SubString[maxLenStr] ); //копирование подстроки	

int main(int argc, char** argv) {
	setlocale(LC_CTYPE, "rus"); 
	puts("Program \"Kursach\". Writed by KD\n");
	int prgMastWork=1;
	int numberVarAction=0;	
	ListStat = NULL;			//зачистка	
	while(prgMastWork==1){
		puts("Program menu.Select action:");	
		puts("1 - Input data from command line");	
		puts("2 - Input data from text file");
		puts("3 - Output rezults to screen");
		puts("4 - Output rezults to text file");
		puts("5 - Quit from program\n");
		puts("6 - Отображение статистики длины слов");
		puts("7 - Сортировка статистики длины слов");
		cin >> numberVarAction;
		switch (numberVarAction){
			case 1:{
				if ( getDataCL() > 0 ) puts("Ошибка обработки строки с экрана");
				break;
			} 
			case 2:{
				if ( getDataTF() > 0 ) puts("произошла ошибка при чтении/обработке данных из файла! Конец работы");
				break;
			} 
			case 3:{
				output2screen( ListStat );
				break;
			}
			case 4:{
				output2tf( ListStat );
				break;
			}
			case 5:{
				prgMastWork=0;
				puts("End of program. By!\n");
				break;
			}
			case 6:{
				showList( ListStat );
				break;
			}
			case 7:{
				sortList( ListStat );
				showList( ListStat );
				break;
			}
		}		
	}
	if ( ListStat != NULL ) deleteDblLinkedList( &ListStat );
	system("pause");
	return 0;
}

int getDataCL(){ //Ввод данных из консоли...			
	if (ListStat==NULL) {
		ListStat = createDblLinkedList();			//создание списка статистики
	}	
	char veryLongString[ maxLenStr ];
	char locWord[ maxLenStr ];
	int err=0; // флаг ошибки в процедуре повод выйти с ошибкой
	while( 1==1 ){
		printf( "Количество введённых слов:%d. Введите слово для обработки (слово \"-1\" прекращает ввод).\n", getCountWord( ListStat ) );
		scanf( "%s" , veryLongString );
		if ( veryLongString[0] == '-' && veryLongString[1] == '1' && veryLongString[2] == '\0' ) break;
		if ( workAboutWord( veryLongString , ListStat ) > 0 ) { err = 1; break; };
	}
	calcShare( ListStat );
	return 0;
}

int getDataTF(){ //Ввод данных из текстового файла...
	int getNameFile=0;
	char namefile[maxLenNameFile];
	FILE * f_txt;
	char locWord[maxLenStr];
	int err=0; // флаг ошибки в процедуре повод выйти с ошибкой
	if (ListStat==NULL) {
		ListStat = createDblLinkedList();			//создание списка статистики
	}		
	puts( "Введите имя файла для обработки" );
	while( getNameFile==0 ){
		cin >> namefile;
		if ( strlen(namefile)==0){
			puts( "Имя файла не введено.\nВведите имя файла для обработки" );
			continue;
		}  
		f_txt = fopen( namefile , "r" );
		if ( f_txt == NULL ){
			puts("Файл с указанным названием не существует.\nВведите имя файла для обработки");
			continue;					
		} 
		getNameFile = 1;
	}
	//обработка файла данных
	while( fscanf( f_txt , "%s" , locWord )!=EOF ){
		if ( workAboutWord( locWord , ListStat ) > 0 ) {
			err = 1;
			break;		
		}
	}
	if ( f_txt != NULL ){
		fclose( f_txt );
	}	
	if ( err== 1 ) return 1;
	calcShare( ListStat );
	return 0;
}

int output2screen( DblLinkedList *list ){
	puts("Результат работы программы!");
	if (list==NULL) {
		cout << "Списка нет. Отображать нечего. Возрат" << endl << endl;
		return 0;
	}		
	char namefile[maxLenNameFile]="rezults.txt";
	FILE * f_txt;
	f_txt = fopen( namefile , "w" );
	if ( f_txt == NULL ){
		puts("Файл с указанным названием не существует.\nВведите имя файла для обработки");
		return 0;					
	} 
	int porog		 = 10;
	int countEl		 = 0;
	int countElporog = 0;
	puts("Файл для результатов открыт...");
	printf("Отображение списка статистики\n" );	
	Node *tmp = list->head; 
	int i = 0; 
	float maxShare = 0;
	while ( tmp ) { 
		++i;
		printf( "Эл-нт № %3d и его длина=%3d кол-во= %5d доля=%f\n", i , tmp->lenWord , tmp->countLenWord, tmp->share );
		countEl++;
		if ( float( tmp->share*100 ) >= float( porog ) ) countElporog++;
		if ( maxShare < tmp->share ) { maxShare = tmp->share ; };
		tmp = tmp->next ;	
		if ( tmp->next == NULL ) break ;	
		if ( i>100 ) break ;	
	}
	printf("Всего длин слов: %d; длин слов с долей более %d %% : %d \n", countEl , porog , countElporog );
	printf("Всего слов: %d\n", getCountWord( list ) );
	if ( countElporog < 10 ) {
		printf("Количество длин слов с долями более %2d %% слишком мало\nПорог принудительно заменён на 2%.\n", porog );
		porog = 2;	
	}
	printf( "Гистограмма\n" );
	printf( "Доля    /\\ \n" );
	printf( "слов в %%| \n" );
	int index2 = int (maxShare * 100 + 1);
	while(index2>-1){
		printf(  "%8d|" , index2 );			
		tmp = list->head; 
		while ( tmp ) { 
			if(int( tmp->share*100 ) > porog ) {
				if ( int( tmp->share*100 ) > index2 ) {
					printf( "*" );	
				}
				else{
					printf( " " );	
				}
			}
			tmp = tmp->next ;	
			if ( tmp->next == NULL ) break ;	
			if ( i>100 ) break ;	
		}		
		index2--;
		printf(  "\n" );	
	}
	printf(  "-----------------------------------------------------------------------------------------\n" );
	//fprintf( f_txt , "         |--------------------------------------------------------------------------------\n" );
	printf("        |---------11111111112222222222333333333344444444445555555555666666666677777777778\n" );
	printf(  "        |12345678901234567890123456789012345678901234567890123456789012345678901234567890\n" );
	fclose( f_txt );
	puts("Файл выходных данных сформирован и закрыт\n");	
	return 0;
	return 0;
}

int	output2tf( DblLinkedList *list ){
	if (list==NULL) {
		cout << "Списка нет. Отображать нечего. Возрат" << endl << endl;
		return 0;
	}		
	char namefile[maxLenNameFile]="rezults.txt";
	FILE * f_txt;
	f_txt = fopen( namefile , "w" );
	if ( f_txt == NULL ){
		puts("Файл с указанным названием не существует.\nВведите имя файла для обработки\n");
		return 0;					
	} 
	int porog		 = 10;
	int countEl		 = 0;
	int countElporog = 0;
	puts("Файл для результатов открыт...");
	fprintf( f_txt , "Отображение списка статистики\n" );	
	Node *tmp = list->head; 
	int i = 0; 
	float maxShare = 0;
	while ( tmp ) { 
		++i;
		fprintf( f_txt , "Эл-нт № %3d и его длина=%3d кол-во= %5d доля=%f\n", i , tmp->lenWord , tmp->countLenWord, tmp->share );
		countEl++;
		if ( float( tmp->share*100 ) >= float( porog ) ) countElporog++;
		if ( maxShare < tmp->share ) { maxShare = tmp->share ; };
		tmp = tmp->next ;	
		if ( tmp->next == NULL ) break ;	
		if ( i>100 ) break ;	
	}
	fprintf( f_txt , "Всего длин слов: %d; длин слов с долей более %d %% : %d \n", countEl , porog , countElporog );
	fprintf( f_txt , "Всего слов: %d\n", getCountWord( list ) );
	if ( countElporog < 10 ) {
		fprintf( f_txt , "Количество длин слов с долями более %2d %% слишком мало\nПорог принудительно заменён на 2%.\n", porog );
		porog = 2;	
	}
	fprintf( f_txt , "Гистограмма\n" );
	fprintf( f_txt , "Доля    /\\ \n" );
	fprintf( f_txt , "слов в %%| \n" );
	int index2 = int (maxShare * 100 + 1);
	while(index2>-1){
		fprintf( f_txt , "%8d|" , index2 );			
		tmp = list->head; 
		while ( tmp ) { 
			if(int( tmp->share*100 ) > porog ) {
				if ( int( tmp->share*100 ) > index2 ) {
					fprintf( f_txt , "*" );	
				}
				else{
					fprintf( f_txt , " " );	
				}
			}
				
			tmp = tmp->next ;	
			if ( tmp->next == NULL ) break ;	
			if ( i>100 ) break ;	
		}		
		index2--;
		fprintf( f_txt , "\n" );	
	}
	fprintf( f_txt , "-----------------------------------------------------------------------------------------\n" );
	fprintf( f_txt , "        |---------11111111112222222222333333333344444444445555555555666666666677777777778\n" );
	fprintf( f_txt , "        |12345678901234567890123456789012345678901234567890123456789012345678901234567890\n" );
	fclose( f_txt );
	puts("Файл выходных данных сформирован и закрыт\n");	
	return 0;
}

//=====================================================================================================================
DblLinkedList* createDblLinkedList() { 			//создание списка
    DblLinkedList *tmp = (DblLinkedList*) malloc(sizeof(DblLinkedList));
    tmp->size = 0;
    tmp->head = NULL;
    tmp->tail = NULL; 
    cout << "Список создан. Вспомогательная структура находиться по адресу = " << tmp << endl;
    return tmp;
}

void deleteDblLinkedList( DblLinkedList **list ) { //удаление списка
    Node *tmpNode = (*list)->head;
    Node *next = NULL;
    while (tmpNode) {                           //очистка списка
        next = tmpNode->next;
        free(tmpNode);
        tmpNode = next;
    }  
    (*list)->size = 0;
    (*list)->head = NULL;
    (*list)->tail = NULL;
    delete *list;								// и наконец удаление списка
    *list = NULL;
    return;
}

int getCountWord( DblLinkedList *list ){ // подсчёт количества введённых слов
	if (list==NULL) {
		return 0;
	}	
	if (list->size==0) { // проверка на то что список не пуст...
		return 0;
	}
	Node *tmpNode = new Node; 	//запрос дополнительной памяти для просматриваемого элемента списка 
    if (tmpNode == NULL) { 
		return -1; 
	};
    int countWords = 0; 
    tmpNode = list->head; 		//взять элемент голову
    Node *buffUkaz; 			//буфер
    do {	
    	countWords += tmpNode->countLenWord; 
		if (tmpNode->next==NULL || tmpNode->next==list->head){ break; } // null - если двусвязный список head - если циклический список
		buffUkaz = tmpNode->next;
		tmpNode = buffUkaz;
	}while(1==1);
	return countWords;	
}

void showList( DblLinkedList *list ){ //отображение списка
	if (list==NULL) {
		cout << "Списка нет. Отображать нечего. Возрат" << endl << endl;
		return;
	}
	cout << "Отображение списка" << endl ;
	cout << "list = " <<  (list) << " size= " << list->size << " адр.голова " << list->head << " адр.хвост " << list->tail << endl;
	cout << "в списке содержиться " << list->size << " записей" << endl;		
	Node *tmp = list->head; 
	int i = 0; 
	while (tmp) { 
		++i;
		printf("Эл-нт № %3d и его длина=%3d кол-во= %5d доля=%f адр.эл-та= %10x адр.пред. %10x адр.след. %10x\n", i, tmp->lenWord, tmp->countLenWord, tmp->share, (tmp), tmp->prev,tmp->next);
		tmp = tmp->next;
	}
	printf("Всего слов: %d\n", getCountWord( list ) );
	return;
}

void sortList( DblLinkedList *list){ //сортировка ListStat 
	int bufLenWord;
	int bufCountLenWord;
	float bufShare;
	puts("Сортировка списка статистики начата.");
	if (list==NULL) {	 // проверка на то что список существует...
		cout << "Сортировка статистики. Списка нет." << endl << "Возврат" << endl;
		return;
	}	
	if (list->size==0) { // проверка на то что список пуст...
		cout << "Сортировка статистики. Список пуст." << endl << "Возврат" << endl;
		return;
	}
	if (list->size==1) { // проверка на то что список состоит из одного элемента => нечего сортировать!!!
		cout << "Сортировка статистики. Список из одного элемента." << endl << "Возврат" << endl;
		return;
	}
	Node *currentNode = new Node; // запрос дополнительной памяти для просматриваемого элемента списка 
    if (currentNode == NULL) { cout << "Ошибка выделения памяти. Возврат" << endl; return; };    
    Node *nextNode; 			// следующий узел
	int countPerestav; 			// счётчик перестановок
	do{
	    countPerestav = 0;
	    currentNode = list->head; 	// взять голову
	    do {

			nextNode = currentNode->next;
			if ( currentNode->lenWord > nextNode->lenWord ){
				// нужна перестановка
				bufLenWord = currentNode->lenWord;
				bufCountLenWord = currentNode->countLenWord;
				bufShare = currentNode->share;
				currentNode->lenWord = nextNode->lenWord;
				currentNode->countLenWord = nextNode->countLenWord;
				currentNode->share = nextNode->share;
				nextNode->lenWord = bufLenWord;
				nextNode->countLenWord = bufCountLenWord;
				nextNode->share = bufShare;	
				// перестановка сделана		
				countPerestav++; // подправим счётчик перестановок
			}
			currentNode = nextNode;
		}while( nextNode->next!=NULL );
	}while(countPerestav>0);
	puts("Сортировка списка статистики завершена.");
	return;
}

int calcShare( DblLinkedList *list ){				//расчёт доль ListStat	
	if (list==NULL) {
		return 0;
	}	
	if (list->size==0) { // проверка на то что список не пуст...
		return 0;
	}
	Node *tmpNode = new Node; 	//запрос дополнительной памяти для просматриваемого элемента списка 
    if (tmpNode == NULL) { 
		return -1; 
	};
    int countWords = getCountWord( list );
    tmpNode = list->head; 		//взять элемент голову
    Node *buffUkaz; 			//буфер
    do {	
    	tmpNode->share = float(tmpNode->countLenWord) / float( countWords );
		//printf("доля=%f\n", tmpNode->share ); 
		if (tmpNode->next==NULL || tmpNode->next==list->head){ break; } // null - если двусвязный список head - если циклический список
		buffUkaz = tmpNode->next;
		tmpNode = buffUkaz;
	}while(1==1);
	return countWords;
}

int workAboutWord( char curWord[maxLenStr] , DblLinkedList *list ){
	if ( strlen( curWord ) == 1 ){ // отбросить не буквы
		if ( curWord[1] < 65 ) { return 0 ;};
		if ( 90 < curWord[1] && curWord[1] < 97 ) { return 0 ;};
		if ( 122 < curWord[1] && curWord[1] < 128 ) { return 0 ;};
	}
	int addOrEditStat( DblLinkedList *list , int val2work );
	if ( list == NULL ) {
		puts("Ошибка реализации алгоритма! Возврат с ошибкой");
		return 1;		
	}
	if ( addOrEditStat( list , strlen( curWord ) ) > 0 ){ //внесение новых данных в статистику
		puts("Ошибка реализации алгоритма2! Возврат с ошибкой");
		return 2;	
	} 	
	return 0;		
}

int addOrEditStat( DblLinkedList *list , int val2work ){ //добавлнение или редактирование статистики
	int add2Stat( DblLinkedList *list , int val2work );
	if ( list==NULL ) { cout << "добавление или редактирование статистики. Списка нет." << "Возврат" << endl; return 1;}	
	if ( val2work == 0 ){ cout << "добавление или редактирование статистики. Длина слова = 0." << "Возврат" << endl; return 2;}	
	if ( list->size == 0 ) {   // проверка на то что список не пуст...
		if ( add2Stat( list , val2work ) > 0 ){ 
			cout << "добавление или редактирование статистики. Добавление в ПУСТОЙ список статистики." << " Возврат" << endl;
			return 3; 
		}
		return 0;		
	}	
	Node *tmpNode = new Node; 	// запрос дополнительной памяти для просматриваемого элемента списка 
    if ( tmpNode == NULL ) { cout << "Ошибка выделения памяти. Возврат" << endl; return 4; };
    int countElem = 0;
    int numberPos = 1; 
    tmpNode = list->head; 		// взять элемент голову
    Node *buffUkaz; 			// для создания буфера
    do {	
	    if ( tmpNode->lenWord==val2work ){
	    	countElem++;
	    	//cout << "Значение найдено в позиции:" << numberPos << endl; 
	    	tmpNode->countLenWord++; // нарастим статистику
	    	return 0;
		}		
		if ( tmpNode->next==NULL || tmpNode->next==list->head ){ break; } // null - если двусвязный список, head - если циклический список
		buffUkaz = tmpNode->next;
		tmpNode = buffUkaz;
		numberPos++; 
	}while(1==1);	
	if (countElem==0){
		if ( add2Stat( list , val2work ) > 0 ){ 
			cout << "добавление или редактирование статистики. Добавление в ПУСТОЙ список статистики." << " Возврат" << endl;
			return 4; 
		}		
	}
	return 0;
}

int add2Stat( DblLinkedList *list , int val2work ){ //добавление в конец списка
	if ( list==NULL ){
		cout << "создайте список!!! Возврат" << endl;
		return 1;
	}
	Node *tmpNode = new Node; // запрос дополнительной памяти для нового элемента списка 
    if (tmpNode == NULL) { cout << "Ошибка выделения памяти. Возврат" << endl; return 2; }    
    tmpNode->lenWord = val2work; // запись значения  нового элемента
    tmpNode->countLenWord = 1; 
    tmpNode->next = NULL; // пустой указатель на несуществующий хвост
    tmpNode->prev = list->tail; // указатель на бывший хвост
    if (list->tail) { // если список не был пуст, то 
        list->tail->next = tmpNode; // редактирование старого хвоста указанием нового хвоста
    }
    list->tail = tmpNode; // редактирование заголовка списка по указателю на новый хвост
    if (list->head == NULL) { // если в заголовке не было указания на элемент, то
        list->head = tmpNode; // запомнить указатель на голову списка
    }
    list->size++; // увеличение счёчика элементов списка
    return 0;
}

void copySubString( char BigString[maxLenStr] , int firstPos , int lastPos , char SubString[maxLenStr] ){ //копирование подстроки
	int i = 0;
	for (int j=firstPos ; j<=lastPos ; j++ ){
		SubString[i] = BigString[j];
		i++;	
	}	
	return;
}
//=====================================================================================================================

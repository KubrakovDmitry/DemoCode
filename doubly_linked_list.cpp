#include <iostream>

using namespace std;

const int N=20; //размер дека
struct Deque
{
	int data[N]; //массив данных
	int last; //указатель на конец
};

struct Node
{
	int d;
	Node *next;
	Node *prev;
};

//Векторная организация дека
void Vector();

//Процедуры и функции  для вектора
//-------------------------------------------------------------------
void Creation(Deque *D); 			//создание дека
bool Full(Deque *D); 				//проверка дека на пустоту
void AddL(Deque *D); 				//добавление элемента в начало
void AddR(Deque *D); 				//добавление элемента в конец
void DeleteL(Deque *D);				//удаление первого элемента
void DeleteR(Deque *D); 			//удаление последнего элемента
void DeletP(Deque *D); 				//удаление элемента по ключу
void InputP(Deque *D);				//вставка элемента
void FindE(Deque *D);				//Поиск элемента по ключу
void DeleteDL(Deque *D);			//Очистка с начала
void DeleteDR(Deque *D);            //Очистка с конца

//int OutputL(Deque *D); 				//вывод первого элемента
//int OutputR(Deque *D); 				//вывод последнего элемента
int Size(Deque *D); 				//размер дека
//-------------------------------------------------------------------

//Списковая организация дека
void List();

//Процедуры и функции  для списка
//-------------------------------------------------------------------

//формирование первого элемента
Node* first(int d);
//Добавление в конец списка
void addE(Node **pend, int d);
//Добавление в начало списка
void addB(Node **pbeg, int d);
//Создание дека из 20 элементов
void creatD(Node *pend);
//Поиск элемента по ключу(значению)
Node* find(Node *const pbeg, int i);
//Удаление
bool remove(Node **pbeg, Node **pend, int key);
//Вставка элемента
Node* insert(Node *const pbeg, Node **pend, int key, int d); 
//-------------------------------------------------------------------

int main() //главная функция
{
	setlocale(LC_ALL,"Rus");
	int button;
	int sw = 0;
	do{
		cout << "1. Векторная реализация " << endl;
		cout << "2. Списковая реализация " << endl;
		cout << "3. Выход из программы " << endl;
		cout << "Выберите способ реализации >" << endl;
		cin >> button;
		switch(button){
			case 1:Vector();
				break;
			case 2:List();
				break;
			case 3:
				sw=1;
				break;	
			default: cout<<endl<<"Команда не определена\n\n";
			break;						
		}
		if(sw>0) break;
	}while(1);
	cout<<" Работа программы успешно завершена. Увидимся! " << endl;
	return 0;
}

//Процедуры и функции  для вектора
//-------------------------------------------------------------------

//создание дека
void Creation(Deque *D) { D->last=0; }

//проверка дека на пустоту
bool Full(Deque *D) 
{
	if (D->last==0) return true;
	else return false;
}

//добавление элемента в начало
void AddL(Deque *D) 
{
	if (D->last==N){ cout<<"\nДек уже заполнен!!! Возврат\n\n"; return; }
	int value;
	cout<<"\nЗначение > "; cin>>value;
	//for(int h = 0; h < N; h++ ) cout << " AddL before:" << h  << "D->data = " << D->data[h] << endl;
	for (int i=D->last; i>0; i--) D->data[i]=D->data[i-1];
	//for(int h = 0; h < N; h++ ) cout << " AddL after:" << h  << "D->data = " << D->data[h] << endl;
	D->data[0]=value;
	D->last++;
	//for(int h = 0; h < N; h++ ) cout << " AddL after:" << h  << "D->data = " << D->data[h] << endl;	
	cout<<endl<<"Элемент добавлен\n\n";
}

//добавление элемента в конец
void AddR(Deque *D) 
{
	if (D->last==N){ cout<<"\nДек заполнен\n\n"; return; }
	int value;
	cout<<"\nЗначение > "; cin>>value;
	D->data[D->last++]=value;
	cout<<endl<<"Элемент добавлен\n\n";
}

//удаление первого элемента
void DeleteL(Deque *D) 
{
	for (int i=0; i<D->last-1; i++){ //смещение элементов
		D->data[i]=D->data[i+1];
	}
	D->data[D->last-1] = 0;
	D->last=D->last-1;
}

//удаление последнего элемента
void DeleteR(Deque *D) { D->last--; }

//удаление элемента по ключу
void DeletP(Deque *D){
	int key;
	int w=0;
	cout << " Введиде ключ >" << endl;
	cin >> key;
	int countDel=0;//счётчик удалений  
	for(int i=0; i<D->last-1; i++){
		if( D->data[i]==key){
			countDel++;
			for(int j=i; j<D->last-1; j++ )D->data[j]=D->data[j+1];
		}
	}
	D->last--;
	cout << " Количество удалений по ключу ("<< key <<") = " << countDel << endl;
	if(countDel==0)
	cout << " Указанный ключ ("<< key <<") не найден!"<< endl;
}

//вставка элемента
void InputP(Deque *D){
	int p, value;
	cout << " Добавление элемента в заданную позицию " << endl;
	if(D->last == N) {cout << " Ввод невозможен. Список заполнен. Возврат. " << endl; return;};
	do{
		cout << " Введите позицию >" << endl;
		cin>> p;
		if(p<=D->last+1) {break;}
		else{
			cout << " Некорректная позиция для ввода нового элемента! " << endl;
		}
	}while(1);
	cout << " Введите значение >" << endl;
	cin>> value; 
	
	for (int i=D->last-1; i>=p; i--)
	D->data[i+1]=D->data[i];
	
	D->data[p]=value;
	D->last++;
	cout << " Элемент добавлен " << endl;
}

//Поиск элемента по ключу
void FindE(Deque *D){
	int key;
	int countFE; // количество поисков
	cout << " Введите искомый ключ " << endl;
	cin >> key;
	for (int i=D->last; i>0; i--){
		if( D->data[i]==key){
			cout<<" Ключ найден в позиции: " << i << endl;
		}
		if(countFE == 0) cout << " Ключ не найден! " << endl;
	}	
}

//Очистка с начала
void DeleteDL(Deque *D){
	int i = 0;
	do{
		D->data[i]=D->data[i+1];
		D->last--;
		if(D->last==0){
			cout<<" Дек удалён " << endl;
			break;
		}
		i++;
	}while(1);
}

//Очистка с конца
void DeleteDR(Deque *D){
	int i = 0;
	do{
		D->data[i]=D->data[i-1];
		D->last--;
		if(D->last==0){
			cout<<" Дек удалён " << endl;
			break;
		}
	}while(1);
}

//Вывод дека на экран
int OutputScreen(Deque *D) {
	cout << " Вывод содержимого Deque " << endl;
	cout << " Количество элементов (D->last): " << D->last << endl;
	for(int i=0; i<D->last; i++){
		cout << "# = " << i << "\t" <<  D->data[i] <<";  "<<endl;
	}
	cout << " Вывод содержимого Deque: конец " << endl;
}

//-----------------------------------------------------------

// Дек - вектор
void Vector(){
	Deque D;
	for(int i = 0; i < N; i++) D.data[i] = 0;
	Creation(&D);
	for(int i=0; i<N; i++){
		//AddL(&D);
		D.data[i] = (N-i)*100;
		D.last++;
		//if(i==17)AddR(&D);
	}
	int number;
	int sw = 0;
	do
	{
		cout<< endl <<" Векторная реализация... " ;
		cout<<"\n1. Добавить элемент в начало"<<endl;
		cout<<"2. Добавить элемент в конец"<<endl;
		cout<<"3. Удалить первый элемент"<<endl;
		cout<<"4. Удалить последний элемент"<<endl;
		cout<<"5. Удаление элемента по ключу"<<endl;
		cout<<"6. Вставка элемента"<<endl;
		cout<<"7. Поиск элемента по ключу"<<endl;
		cout<<"8. Очистка с начала"<<endl;
		cout<<"9. Очистка с конца"<<endl;
		cout<<"10.Вывод дека на экран"<<endl;
		cout<<"0. Выйти\n\n";
		cout<<"Номер команды > "; cin>>number;
		switch (number)
		{
			case 1: AddL(&D);
				break;
			//-----------------------------------------------
			case 2: AddR(&D);
				break;
			//-----------------------------------------------
			case 3:
				if (Full(&D)) cout<<endl<<"Дек пуст\n\n";
			else
			{
				DeleteL(&D);
				cout<<endl<<"Первый элемент удален из дека\n\n";
			} break;
			//-----------------------------------------------
			case 4:
				if (Full(&D)) cout<<endl<<"Дек пуст\n\n";
			else
			{
				DeleteR(&D);
				cout<<endl<<"Последний элемент удален\n\n";
			} break;
			//-----------------------------------------------
			case 5:
				if (Full(&D)) cout<<endl<<"Дек пуст\n\n";
			else DeletP(&D);
				break;
			//-----------------------------------------------
			case 6:
				if (Full(&D)) cout<<endl<<"Дек пуст\n\n";
			else InputP(&D);
				break;
			//-----------------------------------------------
			case 7:
				if (Full(&D)) cout<<endl<<"Дек пуст\n\n";
			else FindE(&D);
				break;
			//-----------------------------------------------
			case 8:
				if (Full(&D)) cout<<endl<<"Дек пуст\n\n";
			else DeleteDL(&D);
				break;
			//-----------------------------------------------
			case 9:
				if (Full(&D)) cout<<endl<<"Дек пуст\n\n";
			else DeleteDR(&D);
				break;
			//-----------------------------------------------
			case 10:
				if (Full(&D)) cout<<endl<<"Дек пуст\n\n";
			else OutputScreen(&D);
				break;
			//-----------------------------------------------
			case 0:
				sw = 100;
				break;
			default: cout<<endl<<"Команда не определена\n\n";
		break;
		}
	} while(sw==0);
}

//Процедуры и функции  для списка
//-----------------------------------------------------------
// формирование первого элемента
Node * first(int d)
{
	Node *pv = new Node;
	pv->d = d;
	pv->next = 0;
	pv->prev = 0;
	return pv;
}
//-----------------------------------------------------------
//добавление в конец списка
void addE(Node **pend,  int d)
{	
	Node *pv=new Node;
	pv->d=d;
	pv->next=0;
	pv->prev=*pend;
	(*pend)->next=pv;
	*pend=pv;
}
//-----------------------------------------------------------
//Добавление в начало списка
void addB(Node **pbeg, int d)
{
	if(*pbeg==NULL) *pbeg = first(1);
	Node *pv=new Node;
	pv->d=d;
	pv->next=*pbeg;
	pv->prev=0;
	(*pbeg)->prev=pv;
	*pbeg=pv;	
}
//-----------------------------------------------------------
//Создание дека из 20 элементов
void creatD(Node *pend){
	for (int i = 100; i<121; i++){
		//cout<<"Внимание" << endl;
		addE(&pend, i);
	}
}
//-----------------------------------------------------------
//поиск элемента по ключу
Node * find(Node *const pbeg, int d)
{
	Node *pv = pbeg;
	while (pv){
		if(pv->d == d)break;
		pv = pv->next;
	}
	return pv;
}
//-----------------------------------------------------------
//удаление элемента
bool remove(Node **pbeg, Node **pend, int key)
{
	if(Node *pkey = find(*pbeg, key))
	{
		if (pkey == *pbeg)
		{
		*pbeg = (*pbeg)->next;
		(*pbeg)->prev =0;}
		else if (pkey == *pend){
			*pend = (*pend)->prev;
			(*pend)->next =0;}
		else{
			(pkey->prev)->next = pkey->next;
			(pkey->next)->prev = pkey->prev;}
		delete pkey;
		return true;
	}
	return false;
}
//-----------------------------------------------------------


// Дек - список
void List()
{
// формирование первого элемента списка:
	Node *pbeg = first(1);
// список заканчивается, едва начавшись:
	Node *pend = pbeg;
//создание списка из 20 элементов 	 
	for (int i = 1; i<N+1; i++)addE(&pend, i);
	int button;
	int sw = 0;
	do{
		cout<< endl <<" Списковая реализация... \n" ;	
		cout<<"1.  Добавить элемент в начало"<<endl;
		cout<<"2.  Добавить элемент в конец"<<endl;
		cout<<"3.  Удалить первый элемент"<<endl;
		cout<<"4.  Удалить последний элемент"<<endl;
		cout<<"5.  Удаление элемента по ключу"<<endl;
		cout<<"6.  Поиск элемента по ключу"<<endl;
		cout<<"7.  Очистка списка с начала"<<endl;
		cout<<"8.  Очистка списка с конца"<<endl;
		cout<<"9. Вывод списка на экране"<<endl;
		cout<<"0.  Выйти\n\n";
		cout<<"Номер команды > "; 
		cin >> button;
		switch(button){
//---------------------------------------------------------------------
		case 1 :{
			int number;
			cout << " Введите значение добавляемого элемента >" << endl;
			cin >> number;
			// добавление в начало списка:
			addB(&pbeg, number);
			break;
		}
//---------------------------------------------------------------------
		case 2 :{
			if(pend==NULL) {
				pbeg = first(1);
				pend = pbeg;
			}
			int number;
			// добавление в конец списка :
			cout << " Введите значение добавляемого элемента >" << endl;
			cin >> number;
			addE(&pend, number);
			break;
		}
//---------------------------------------------------------------------
		case 3 :{
			// удаление первого элемента :
			if(!remove (&pbeg, &pend, pbeg->d))cout << "не найден";
			break;
		}
//---------------------------------------------------------------------
		case 4 :{
			// удаление последнего элемента :
			if(!remove (&pbeg, &pend, pend->d))cout << "не найден";
			break;
		}
//---------------------------------------------------------------------
		case 5 :{
			// удаление заданного элемента :
			int num;
			cin>>num;
			cout<<"Задано "<< num << endl;
			if(!remove (&pbeg, &pend, num))cout << "не найден";
			break;
		}
//---------------------------------------------------------------------		
		case 6 :{
			int num;
			cout << "Введите значение " << endl;
			cin>>num;
			//Поиск элемента по ключу 
			Node *val = find(pbeg, num);
			if(val){
				cout<<"Значение найденного элемента = "<< val->d <<endl;
			}
			break;
		}
//---------------------------------------------------------------------		
		case 7 :{
			// очистка дека с начала 
			Node *ptr;
			do{
				ptr = pbeg->next;
				delete pbeg;
				pbeg=ptr;
				if(pbeg == NULL){
					cout << "\n Список удалён!" << endl;
					pend = NULL;
					break;
				}			
			}while(pbeg);
		//	cout << "pend=" << pend << endl;	
		//	cout << "pbeg=" << pbeg << endl;
			break;
		}
//---------------------------------------------------------------------
		case 8 :{
			// очистка дека с конца
			Node *ptr; 
			do{
				ptr=pend->prev;
				delete pend;
				pend=ptr;
				if(pend==NULL){
					cout << "\n Список удалён!" << endl;
					pbeg = NULL;
					break;
				}
			}while(1);
		//	cout << "pend=" << pend << endl;
		//	cout << "pbeg=" << pbeg << endl;
			break;
		}
//---------------------------------------------------------------------
		case 9:{
			cout << "Вывод списка " <<endl;
			Node *pv = pbeg;
			// вывод списка на экран:
			while( pv ){
				cout << pv->d << ";  ";
				pv = pv->next;
			}
			cout << "\nВывод списка: Конец\n" <<endl;
			cout << endl;
			break;
		}
//---------------------------------------------------------------------
		case 0 : sw = 1; break;
		default: cout<<endl<<"Команда не определена\n\n";				
		} 		
	}while(sw == 0);	
}

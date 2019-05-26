#include <iostream>
#include <math.h>
#include <cstdio>
#include <cstdlib>
#include <locale.h>
#include <fstream>

using namespace std;
/*Поиск корня уравнения методами хорд, касательных, деления отрезка попалам, простых итераций*/
long double Xb = 0 , Xe = 0;
long double Epsel = 0.01;
int countSteps = 0;
int show2screen = 8;
int array2graf[8][2];						//кол-во итер. 2graf
int lowaccuracy;							//управления точностью поиска первых приближений
void outputGraph();

long double qabs(long double val);
long double functionFX( long double x );												//исходная функия
long double functionDerFX( long double x );												//производная исходной функции
void keyboardInput( long double *Xb, long double *Xe );									//ввод с клавиатуры
void fileInput( long double *Xb, long double *Xe );										//ввод из файла
void outPut2screen(int CodeMethod, long double Epsel, int counterI, long double root);	//вывод на экран
long double 	getX0(long double startPos, int direction, long double Epsel, int *counter);
int MD( long double Xb, long double Xe, long double Epsel);			//Метод хорд
int MN( long double Xb, long double Xe, long double Epsel);			//Метод касательных
int Mm( long double Xb, long double Xe, long double Epsel);			//Метод деления отрезка попалам
int Mi( long double Xb, long double Xe, long double Epsel);			//Метод простых итераций

//Файл результатов вычислений и процедура записи в него
FILE *txtFile;
char Delimetr = 9;

void EmptyFile();
void Write2File( int CodeMethod, long double Epsel, int counterI, long double root, int counter );//вывод в файл

int main() {
	setlocale(LC_ALL, "Rus");
	EmptyFile();
	int act;									//вариант действия
	int aoca[4];                       			//массив счётчиков прибижений
	long double  *ptXb = &Xb;
	long double  *ptXe = &Xe;

	for (int i = 0; i < 4; i++){
		aoca[i] = 0;
	}
	cout << "Практическое задание, часть 2."<< endl;
	cout << "Укажите вариант ввода: " << endl << "1 - с клавиатуры" << endl << "2 - из файла" << endl;
	cin >> act;
	switch(act){
		case 1: {	keyboardInput( ptXb, ptXe ); break;}
		case 2: {fileInput( ptXb, ptXe ); break;}
		default: cout << " Указан непредусмотренный вариант ввода. " << endl << " Выход из программы! " << endl;
	}
	cout << " \n " << endl;
	Epsel=0.01;
	for( int i = 1; i < 9; i++ ){
		cout << " Заход№" << i << endl;
		array2graf[i-1][0] = log10(Epsel);
		array2graf[i-1][1] = MD( Xb, Xe, Epsel );
		cout << " \n " << endl;
		Epsel=Epsel/10;
	}
	outputGraph();
	
	Epsel=0.01;	
	for( int i = 1; i < 9; i++ ){
		cout << " Заход№" << i << endl;
		array2graf[i-1][0] = log10(Epsel);
		array2graf[i-1][1] = MN( Xb, Xe, Epsel );
		cout << " \n " << endl;
		Epsel=Epsel/10;
	}
	outputGraph();
	
	Epsel=0.01;
	for( int i = 1; i < 9; i++ ){
		cout << " Заход№" << i << endl;
		array2graf[i-1][0] = log10(Epsel);
		array2graf[i-1][1] = Mm( Xb, Xe, Epsel );		
		cout << " \n " << endl;
		Epsel=Epsel/10;
	}
	outputGraph();
	
	Epsel=0.01;
	for( int i = 1; i < 9; i++ ){
		cout << " Заход№" << i << endl;
		array2graf[i-1][0] = log10(Epsel);
		array2graf[i-1][1] = Mi( Xb, Xe, Epsel );		
		cout << " \n " << endl;
		Epsel=Epsel/10;
	}	
	outputGraph();	
		
	cout << " Все расчёты завершены. ОК. " << endl;
	return 0;
}

void outPut2screen(int CodeMethod, long double Epsel, int counterI, long double root){
	if(show2screen  != 8 ){return;} 
	switch(CodeMethod){
		case 1: 
		{
			printf( "%s" , " Метод секущих(Хорд) "  );
			break;
		}
		case 2: 
		{
			printf( "%s" , " Метод касательных "  );
			break;
		}
		case 3:
		{
			printf( "%s" , " Метод дихотомии "  );
			break;
		} 
		case 4: 
		{
			printf( "%s" , " Метод итерации "  );
			break;
		}
	}
	printf(  "%c" , Delimetr );
	printf(  "%g" , Epsel    );
	printf(  "%c" , Delimetr );
	printf(  "%d" , counterI );
	cout << "  " << endl;
	return ;
}

void EmptyFile(  ){
	system("del Result.txt");	
}

void Write2File( int CodeMethod, long double Epsel, int counterI, long double root, int counter){
	txtFile = fopen("Result.txt", "r");
	if(txtFile == NULL){
		txtFile = fopen("Result.txt", "w");
		if(txtFile == NULL){
			cout << " Ошибка открытия файла результатов. Программа завершена! " << endl;
			exit(0);
		}
		fprintf( txtFile, "%s" , "Название метода "  );
		fprintf( txtFile, "%c", Delimetr);
		fprintf( txtFile, "%s" , "Точность "  );
		fprintf( txtFile, "%c", Delimetr);
		fprintf( txtFile, "%s" , "Количество итераций "  );
		fprintf( txtFile, "%c\r", Delimetr);
		fprintf( txtFile, "\n");
	}
	else{
		fclose(txtFile);
		txtFile = fopen("Result.txt", "a+");
		if(txtFile == NULL){
			cout << " Ошибка открытия файла результатов. Программа завершена! " << endl;
			exit(0);
		}
	}
	switch(CodeMethod){
		case 1: 
		{
			fprintf( txtFile, "%s" , " Метод хорд "  );
			break;
		}
		case 2: 
		{
			fprintf( txtFile, "%s" , " Метод касательных "  );
			break;
		}
		case 3:
		{
			fprintf( txtFile, "%s" , " Метод дихотомии "  );
			break;
		} 
		case 4: 
		{
			fprintf( txtFile, "%s" , " Метод итерации "  );
			break;
		}
	}
	fprintf( txtFile, "%c", 	Delimetr);
	fprintf( txtFile, "%lg", 	log10(Epsel)  );
	fprintf( txtFile, "%c", 	Delimetr);
	fprintf( txtFile, "%d\n", 	counterI );
	fclose(txtFile);
	return ;
}

long double functionFX( long double x ){
	return ( 5 * pow( x, 3) - x - 1 );
}

long double functionDerFX( long double x ){
	return ( 15 * pow( x, 2 ) - 1 );
}

void keyboardInput( long double *Xb, long double *Xe ){
	long double Wb = 0, We = 0;
	cout << " Введите левую границу. " << endl;
	cin >> Wb; 
	*Xb = Wb;
	cout << " Xb= " << Xb << endl;
	cout << " Введите правую границу. " << endl;
	cin >> We; 
	*Xe = We;
	cout << " Xe= " << Xe << endl;
	cin >> show2screen;
	return ;
}

void fileInput( long double *Xb, long double *Xe ){
	FILE *f;
	char str[80];
	long double num[3];
	for(int i = 0; i < 80; i++){
		str[i] = 0; 
	}
	int i = 0;
	f = fopen("Scopes.txt", "r");
	while(fgets(str, 80, f)!=NULL){
		num[i] = atof(str);
		i++;	
	}
	*Xb = num[0];
	*Xe = num[1];
	lowaccuracy = num[2];
	cout << " Данные считанны. " << endl;
	cout << " Xb= " << *Xb << " Xe= " << *Xe << endl;
	cout << "lowaccuracy= " << lowaccuracy << endl;
	fclose(f);
}

long double qabs(long double val){
	if(val<0) return -1 * val;
	return val;
}

int MD( long double Xb, long double Xe, long double Epsel ){
	int getRoot(long double x0, long double x1, int countSteps);
	long double getX1(long double x0, int direction, long double Epsel, int *counter);
	long double locEpsel;
	int counter=0;
	countSteps = 0;
	cout << "Поиск корня методом секущих" << endl;
	int direction = 1 ;								//1 - корень ищем справа, 2 - слева
	if(lowaccuracy){
		locEpsel= 0.01;
	}
	else{
		locEpsel = Epsel;	
	}
	long double x0 = getX0( Xb, direction, locEpsel, &counter );
	long double x1 = getX1( x0, direction, locEpsel, &counter );
	cout << "x0= " << x0 << "\nx1= " << x1 << endl;
	
	int counterW = getRoot(  x0,  x1, countSteps );
	
	Write2File(1, Epsel, counterW, 0, counter );
	cout << "Конец поиска методом секущих. Количество итераций = " << counterW << endl;	
	return counterW;
}

long double getX0(long double startPos, int direction, long double Epsel, int *counter){
	long double x = startPos;
	cout << " startPos " << x << endl;
	long double val;
	int countSteps = 0;
	long double locEps = 0.01;
	do{
		
		val = functionFX(x)*30*x;
		if(val < 0) {
			if(direction == 1)	{
			x+=locEps;
			countSteps++;
			} 
			else {
				x-=locEps;
			}
			continue;
		}
		break;
	}while(1);
	*counter = countSteps;
	cout << " Первое приближение = " << x << " Количество итераций поиска " <<  countSteps << " Epsel =  " << Epsel << endl;
	return x;
}

long double getX1( long double x0, int direction, long double Epsel, int *counter ){
	*counter = *counter + 1;
	if(direction == 1 ) return x0 + 1.1 * Epsel;
	if(direction == 2 ) return x0 - 1.1 * Epsel;
	exit(0); 
	return 0;
}

int getRoot( long double x0, long double x1, int countSteps ){
	long double xk0 = x0;//первое начальное приближение
	long double xk = x1;//второе начальное приближение
	long double gfX;	//переменная для хранения значения функции
	gfX=functionFX(xk);
	long double xk1;	//претендент на корень
	int r1, r2;
	do{
		countSteps++;
		xk1 = xk - gfX*(xk - xk0)/(gfX-functionFX(xk0));
		cout << " xk1 =  " << xk1 << " xk = " << xk << " Разница = " << qabs(xk1-xk) << endl;
		//проверка условия выхода из цикла
		if(qabs(xk1-xk) < Epsel){
			r1 = 1;
			cout << "Выход по r1"<< endl;
			break;
		}
		else {
			r1 = 0;
		}
		gfX=functionFX(xk1);
		if(qabs(gfX) < Epsel){
			r2 = 1;
			cout << "Выход по r2:"<< "gfX= " << gfX << endl;
			break;
		}
		else {
			r2 = 0;
		}
		xk0 = xk;
		xk = xk1;
		printf(" xk0 (LF)= %20.15LF \n", xk0);
		printf(" xk (LF)= %20.15LF \n", xk);
	}while ((r1 == 0) || (r2 == 0));
	cout << " Найденное Значение КОРНЯ = " << xk1 << endl;
	printf(" Найденное Значение КОРНЯ (LF)= %20.15LF \n", xk1);
	return countSteps;
}

int MN( long double Xb, long double Xe, long double Epsel) //Метод касательных
{//Метод касательных
	cout << "Поиск корня методом касательных " << endl;
	int counterW = 0;
	int counter = 0;
	int direction = 1 ;								//1 - корень ищем справа, 2 - слева
	long double X0 = getX0( Xb, direction, Epsel, &counter);
	long double Xprev = X0;
	long double Xnext;
	do{
		counterW++;
		Xnext = Xprev - functionFX(Xprev)/functionDerFX(Xprev);
        printf("qabs(Xnext-Xprev)(LF)= %20.15LF \n", qabs(Xnext-Xprev));
		printf("Xprev(LF)= %20.15LF \n", Xprev);
		printf("Xnext(LF)= %20.15LF \n", Xnext);
		if( qabs(Xnext-Xprev) < Epsel) { cout << "     выход" << endl; break;}
		Xprev = Xnext;
		
	}while(1);
	Write2File(2, Epsel, counterW, 0, counter);
	cout << " Количество итераций поиска начальных приближений = " << counterW << endl;
	cout << "Конец поиска корня методом касательных " << endl;
	return counterW;
}

int Mm( long double Xb, long double Xe, long double Epsel)			//Метод деления отрезка попалам
{
	cout << " Поиск корня методом деления отрезка попалам " << endl;
	int counterW = 0;
	long double Xl = Xb;
	long double Xr = Xe;
	long double Xm, fl, fr, fm ;
	do{	
		fl = functionFX(Xl);
		fr = functionFX(Xr);
		if(fl * fr > 0){break;}
		counterW++;
		if(Xr - Xl <= 2 * Epsel){
		//	(Xr+Xl)/2; 	это есть корень			
			break;
		}
		Xm = (Xl + Xr)/2;
		fm = functionFX(Xm);
		if(fm == 0){break;}
		if(fl * fm < 0){Xr = Xm;}
		else{Xl = Xm;}
	}while(1);
	int counter = 0;
	Write2File(3, Epsel, counterW, 0, counter);
	cout << " counterW " << counterW << endl;
	cout << " Конец поиска корня методом деления отрезка попалам  " << endl;
	return counterW;
}

int Mi( long double Xb, long double Xe, long double Epsel)			//Метод простых итераций
{
	cout << " Поиск корня методом итераций " << endl;
	int counterW = 0;
	long double Xl = Xb;
	long double Xr = Xe;
	long double X0 = (Xl+Xr)/2;
	long double psi, Ppsi;
	long double q;
	cout << "Epsel=" << Epsel << endl;
	do{
		psi = pow( ( ( X0+1 )/5 ), 1.0/3.0 );
		Ppsi = 1/(15*pow(((X0+1)/5),1.0/3.0));
		
		printf("X0(LF)= %20.15LF \n", X0);
		printf("psi(LF)= %20.15LF \n", psi);
		printf("Ppsi(LF)= %20.15LF \n", Ppsi);
		printf("qabs(psi-X0)(LF)= %20.15LF \n", qabs(psi-X0));
		if(qabs(Ppsi) >= 1){
			cout << " Метод итерации неприменим! " << endl;
			break;
		}
		counterW++;
		q = fabs(Ppsi);
		printf("q(LF)= %20.15LF \n", q);
		long double v2qt = q/(1-q)*qabs(psi - X0);
		if(v2qt <= Epsel){
			cout << "v2qt = " << v2qt << endl;
			break;
		}
		X0 = psi;
	}while(1);
	printf("root(LF)= %20.15LF \n", X0);
	int counter = 0;
	//outPut2screen( 4,  Epsel,  counterW,  0);
	Write2File(4, Epsel, counterW, 0, counter );
	cout << " counterW " << counterW << endl;
	cout << " Конец поиска корня методом итераций  " << endl;
	return counterW;
}
void outputGraph()
{
	txtFile = fopen("Result.txt", "a+");
	fprintf(txtFile,"\n");	
	fprintf(txtFile,"Диаграмма (* - одна итерация поиска корня)\n");	
	fprintf(txtFile,"--------------------------------------- --------------------------------------------\n");
	for(int i=0; i<8; i++){
		fprintf(txtFile,"%ld|(%5d)|", array2graf[i][0], array2graf[i][1]);
		if(array2graf[i][1]>0){
			for(int j=1;j<=array2graf[i][1]; j++){
				fprintf(txtFile,"*");
			};
			fprintf(txtFile,"\n");	
		}
			
	}
	fprintf(txtFile,"---------------------------------------------------------------- -------------------\n");
	fprintf(txtFile,"\n");	
	fprintf(txtFile,"График (* или пробел - одна итерация поиска корня)\n");	
	fprintf(txtFile,"-------------------------------------------------------------------- ---------------\n");
	for(int i=0; i<8; i++){
		fprintf(txtFile,"%ld|(%5d)|", array2graf[i][0], array2graf[i][1]);
		if(array2graf[i][1]>0){
			for(int j=1;j<=array2graf[i][1]-1; j++){
				fprintf(txtFile," ");
			};
			fprintf(txtFile,"*");
			fprintf(txtFile,"\n");	
		}
			
	}
	fprintf(txtFile,"-------------------------------------------------------------------- ---------------\n");
	fclose(txtFile);
	return ;
}

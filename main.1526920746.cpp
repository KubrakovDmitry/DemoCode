#include <iostream>
#include <math.h>
#include <clocale>

using namespace std; 

int main() {
 	setlocale(LC_ALL, "Russian");
	double X;		
	double Xo = 3*M_PI/16;
	double MX[4];
	double eest;//оценка погрешности
	MX[0] = 0;
	MX[1] = M_PI/8;
	MX[2] = M_PI/4;
	MX[3] = 3*M_PI;
	
	cout << " Интерполяционный многочлен Лагранжа " << endl;
	cout << " Начало " << endl;
	double L3; //многочлен Лагранжа
	double MFi[4];//значения функции
	double WSht[4];//амега штрих
	double D[4];//частное функции и амеги штрих
	double RL[4];
	void funFi(double MX[4], double MFi[4]);
	void funWSht(double MX[4], double WSht[4]);
	void funFiDivWSht(double WSht[4], double D[4], double MFi[4]); // частная производная
	double Epselan_of_X(double X, double MX[4]);//вычисление оценки погрешности интерполяции
	
	funFi(MX, MFi);
	funWSht(MX, WSht);
	funFiDivWSht(WSht, D, MFi);
	X=Xo;
	eest = Epselan_of_X( X, MX );
	cout << " eest= " << eest << endl;
	
	for(int i = 0; i<4; i++){
	}
	for(int i = 0; i<4; i++){
		RL[i] = D[i];
		for( int j1 = 0 ; j1 < 4 ; j1++ ){
			if (j1==i) { continue; };	
			RL[i] = RL[i]*( X - MX[j1] );
		}		
	}
	cout << " " << endl;
	cout << "RL[0]=" << RL[0] << endl;
	cout << "RL[1]=" << RL[1] << endl;
	cout << "RL[2]=" << RL[2] << endl;
	cout << "RL[3]=" << RL[3] << endl;
	cout << " " << endl;
	L3 = RL[0] + RL[1] + RL[2] + RL[3];
	double Result = fabs(L3-tan(X));
	cout << "  " << endl;
	cout << " L3= " << L3 << endl;
	cout << " tg(X)= " << tan(X) << endl;
	cout << " Result= " << Result << endl;
	int J = 0;
	if(Result<eest)//сравнение оценки с погрешностью
	{
		J=1;
		cout << " J =" << J << endl;
		cout << " Погрешность допускается точность " <<  endl;
	}
	else{
		cout << " J =" << J << endl;
	}
	cout << " Конец " << endl << endl;
	cout << " Интерполяционный многочлен Ньютона " << endl;
	cout << " Начало " << endl;	
	double Fx0x1(double X0, double X1);//разделённая разность 1-го порядка
	double Fx0x1x2(double X0, double X1, double X2);//разделённая разность 2-го порядка
	double Fx0x1x2X3(double X0, double X1, double X2, double X3);//разделённая разность 3-го порядка
	double p1 = (X-MX[0])*Fx0x1(MX[0],MX[1]);
	cout << " p1 = " << p1 << endl;
	double p2 = (X-MX[0])*(X-MX[1])*(Fx0x1x2(MX[0],MX[1],MX[2]));
	cout << " p2 = " << p2 << endl;
	double p3 = (X-MX[0])*(X-MX[1])*(X-MX[2])*(Fx0x1x2(MX[0],MX[1],MX[2]));
	cout << " p3 = " << p3 << endl;
	double p4 = (X-MX[0])*(X-MX[1])*(X-MX[2])*(X-MX[3])*Fx0x1x2X3(MX[0],MX[1],MX[2],MX[3]);
	cout << " p4 = " << p4 << endl;
	double P3 = tan(MX[0])+p1+p2+p3+p4;
	cout << " P3= " << P3 << endl;
	cout << " Result= " << fabs(P3-tan(X)) << endl;
	if(Result<eest)//сравнение оценки с погрешностью
	{
		J=1;
		cout << " J =" << J << endl;
		cout << " Погрешность допускается точность " <<  endl;
	}
	else{
		cout << " J =" << J << endl;
	}
	cout << " Конец " << endl;	
	return 0;
} 
// Процедуры  
// для Лагранжа
void funFi(double MX[4], double MFi[4])
{
	for(int i =0; i<4; i++){
		MFi[i] = tan(MX[i]);
		cout << "MF#"<< i+1 << "=" << MFi[i] << endl;
	}
	return ;
}

void funWSht(double MX[4], double WSht[4])
{
	for(int i = 0; i<4; i++){
		WSht[i]=1;
		for( int j1 = 0 ; j1 < 4 ; j1++ ){
			if (j1==i) { continue; };	
			WSht[i] = WSht[i]*( MX[i] - MX[j1] );
		}		
	}
	return ;
}

void funFiDivWSht(double WSht[4], double D[4], double MFi[4])
{
	for(int i = 0; i<4; i++){
		D[i] = MFi[i]/WSht[i];
	}
	return ;
}

//для Ньютона
double Fx0x1(double X0, double X1)
{
	return((ctan(X0)-tan(X1))/(X0-X1));
}

double Fx0x1x2(double X0, double X1, double X2)
{
	return((Fx0x1(X0,X1)-Fx0x1(X1,X2))/(X0-X2));
}

double Fx0x1x2X3(double X0, double X1, double X2, double X3)
{
	return((Fx0x1x2(X0,X1,X2)-Fx0x1x2(X1,X2,X3))/(X0-X3));
}

double Epselan_of_X(double X, double MX[4])//вычисление оценки погрешности интерполяции
{
	double dofnl_5 = 0; //производная пятого порядка(для логарима он равне 1/pow(MX[i], 5);)
	double k;
	int res=1;
	double amega;
	for(int i= 0; i<4; i++)//поиск максимального значения модуля производной 
	{
		k = 16/pow(cos(MX[i]), 2)+120*pow(sin(MX[i]),2)/pow((cos(MX[i])),6);
		if(dofnl_5 < fabs(k))//если текущая макс. произв. меньше новой
		{
			dofnl_5 = fabs(k);
		}
//		cout << " k= " << k << endl;
//		cout << " fabs(k)= " << fabs(k) << endl;
//		cout << " dofnl_5= " << dofnl_5 << endl;
	}
	cout << " dofnl_5= " << dofnl_5 << endl;
	for(int i = 1; i <= 5; i++ )//факториал
	{
		res = res * i;
	}
	cout << " res= " << res << endl;
	amega=(X-MX[0])*(X-MX[1])*(X-MX[2])*(X-MX[3]);
	cout << " amega= " << amega << endl;
	return(dofnl_5/res*fabs(amega)) ;
}



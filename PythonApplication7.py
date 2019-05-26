import time
#from datetime import time
import math
#Импортируем один из пакетов Matplotlib
import pylab
#Импортируем пакет со вспомогательными функциями
from matplotlib import mlab
import numpy as np     # installed with matplotlib
import matplotlib.pyplot as plt

def Transformation(DFV, n):
    i = 0
    T = complex(0.0, 0.0)
    for item in DFV:
        c = complex(item*math.cos(2*math.pi*i*n/len(DFV)), item*math.sin(2*math.pi*i*n/len(DFV)))
        i+=1
        T += c.conjugate()
    return T

I = 1
print("Начало a = 0, b = 10, h = 0.1" )
while I <= 30:
    start_time = time.time()
    a = 0.0                         #левая граница отрезка
    b = 10.0                        #правая граница отрезка
    h = 0.1                         #шаг 
    t = a                           #начало отсчета
    #Создадим список координат по оси 
    #X на отрезке [-xmin; xmax], включая концы
    xlist = mlab.frange (a, b, h)

    # Вычислим значение функции в заданных точках
    ylist = [math.fabs(math.sin(x)) for x in xlist]

    pylab.plot (xlist, ylist)
    DFV = list()
    CDFV = list()
    while t <= b:
        DFV.append(math.fabs(math.sin(t)))
        t += h
    counter = 0
    n = 0
    while counter < len(DFV):
        CDFV.append(Transformation(DFV, n))
        counter += 1
        n += 1
    print("--- %s seconds ---" % (time.time() - start_time))
    I+=1
print("Конец a = 0, b = 10, h = 0.1" )

I = 1
print("Начало a = -10, b = 10, h = 0.1" )
while I <= 30:
    start_time = time.time()
    a = -10.0                         #левая граница отрезка
    b = 10.0                        #правая граница отрезка
    h = 0.1                         #шаг 
    t = a                           #начало отсчета
    #Создадим список координат по оси 
    #X на отрезке [-xmin; xmax], включая концы
    xlist = mlab.frange (a, b, h)

    # Вычислим значение функции в заданных точках
    ylist = [math.fabs(math.sin(x)) for x in xlist]

    #Нарисуем одномерный график
    pylab.plot (xlist, ylist)

    DFV = list()
    CDFV = list()
    while t <= b:
        DFV.append(math.fabs(math.sin(t)))
        t += h
    counter = 0
    n = 0
    while counter < len(DFV):
        CDFV.append(Transformation(DFV, n))
        counter += 1
        n += 1
    print("--- %s seconds ---" % (time.time() - start_time))
    I+=1
print("Конец a = -10, b = 10, h = 0.1" )

I = 1

print("Начало a = -10, b = 10, h = 0.01" )
while I <= 30:
    start_time = time.time()
    a = -10.0                         #левая граница отрезка
    b = 10.0                        #правая граница отрезка
    h = 0.01                         #шаг 
    t = a                           #начало отсчета
    #Создадим список координат по оси 
    xlist = mlab.frange (a, b, h)

    # Вычислим значение функции в заданных точках
    ylist = [math.fabs(math.sin(x)) for x in xlist]

    #Нарисуем одномерный график
    pylab.plot (xlist, ylist)

    #Покажем окно с нарисованным графиком
    DFV = list()
    CDFV = list()
    while t <= b:
        DFV.append(math.fabs(math.sin(t)))
        t += h
    counter = 0
    n = 0
    while counter < len(DFV):
        CDFV.append(Transformation(DFV, n))
        counter += 1
        n += 1
    print("--- %s seconds ---" % (time.time() - start_time))
    I+=1
#somefile.close()
print("Конец a = -10, b = 10, h = 0.01" )

# Список действительных частей
RealList = [CtR.real for CtR in CDFV]

#Нарисуем одномерный график
pylab.plot (xlist, RealList)




# Список мнимых частей
ImagList = [CtL.imag for CtL in CDFV]

#Нарисуем одномерный график
pylab.plot (xlist, ImagList)

#Покажем окно с нарисованным графиком
pylab.show()


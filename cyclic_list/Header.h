#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "HeaderLine.h"
using namespace std;

template <class Type>
class CyclicalList : public fstream, public Line
{
protected:
	streampos beg;
	int size;
public:
	CyclicalList() :basic_fstream() { size = 0; }
	CyclicalList(char* filename, ios_base::openmode mode = ios_base::in | ios_base::out | ios_base::binary | ios_base::trunc) :basic_fstream(filename, mode) { size = 0; }
	~CyclicalList();
	void Add(Type);
	void Print();
	void Remove();
	void Update(int Num, Type obj);
	void Sort();
};
template <class Type>
CyclicalList<Type>::~CyclicalList()
{
	close();
}
template <class Type>
void CyclicalList<Type>::Add(Type Object)
{
	if (beg.operator== (0))   //если список пуст
	{
		beg = 0;

		// запись в начало файла, для того, чтобы переместить указатель на начало первого объекта
		seekg(0);
		write((char*)&beg, sizeof(streampos));
		beg = tellg();

		seekg(0);
		write((char*)&beg, sizeof(streampos)); // указатель на первый элемент
		write((char*)&beg, sizeof(streampos)); // указатель на предыдущий для первого - то есть на самого себя
		write((char*)&beg, sizeof(streampos)); // указатель на следующий для первого - то есть на самого себя
		write((char*)&Object, sizeof(Type)); // запись самого объекта

		size++;
	}

	else
	{
		streampos PrevTemp, NextTemp, Last_object;
		seekg(beg);
		read((char*)&PrevTemp, sizeof(streampos));
		seekg(0, end);
		Last_object = tellg(); //указатель на добавленный элемент
		write((char*)&PrevTemp, sizeof(streampos));// указатель на предыдущий
		write((char*)&beg, sizeof(streampos));// указатель на следующий
		write((char*)&Object, sizeof(Type));// объект

		// смена указателей у других объектов                                   
		seekg(PrevTemp.operator+(sizeof(streampos)));
		write((char*)&Last_object, sizeof(streampos));     //заменяем указатель на сделующий элемент в старом последнем узле

		seekg(beg);
		write((char*)&Last_object, sizeof(streampos));    //заменяем указатель на предыдущий элемент для первого

		seekg(0, end);

		size++;
	}
}

void CyclicalList<Line>::Add(Line Object)
{
	if (beg.operator== (0))   //если список пуст
	{
		beg = 0;

		// запись в начало файла, для того, чтобы переместить указатель на начало первого объекта
		seekg(0);
		write((char*)&beg, sizeof(streampos));
		beg = tellg();

		seekg(0);
		write((char*)&beg, sizeof(streampos)); // указатель на первый элемент
		write((char*)&beg, sizeof(streampos)); // указатель на предыдущий для первого - то есть на самого себя
		write((char*)&beg, sizeof(streampos)); // указатель на следующий для первого - то есть на самого себя
		// запись самого объекта
		write((char*)&Object.len, sizeof(int));
		write(Object.String, Object.len * sizeof(char));
		write((char*)Object.time_buf, 8 * sizeof(char));

		size++;
	}

	else
	{
		streampos PrevTemp, NextTemp, Last_object;
		seekg(beg);
		read((char*)&PrevTemp, sizeof(streampos));
		seekg(0, end);
		Last_object = tellg(); //указатель на добавленный элемент
		write((char*)&PrevTemp, sizeof(streampos));// указатель на предыдущий
		write((char*)&beg, sizeof(streampos));// указатель на следующий
		// запись самого объекта
		write((char*)&Object.len, sizeof(int));
		write(Object.String, Object.len * sizeof(char));
		write((char*)Object.time_buf, 8 * sizeof(char));

		// смена указателей у других объектов                                   
		seekg(PrevTemp.operator+(sizeof(streampos)));
		write((char*)&Last_object, sizeof(streampos));     //заменяем указатель на сделующий элемент в старом последнем узле

		seekg(beg);
		write((char*)&Last_object, sizeof(streampos));    //заменяем указатель на предыдущий элемент для первого

		seekg(0, end);

		size++;
	}
}
template <class Type>
void CyclicalList<Type>::Print()
{
	Type object;
	streampos Next = 0;
	// вывод первого элемента. для того, чтобы потом можно было сделать цикл
	seekg(beg.operator+(2 * sizeof(streampos)));
	read((char*)&object, sizeof(Type));
	cout << object << " ";

	seekg(beg.operator+(sizeof(streampos)));
	read((char*)&Next, sizeof(streampos));

	// вывод остальных элементов
	while (Next != beg)
	{
		seekg(Next.operator+(2 * sizeof(streampos)));
		read((char*)&object, sizeof(Type));
		cout << object << " ";
		seekg(Next.operator+(sizeof(streampos)));
		read((char*)&Next, sizeof(streampos));
	}
	cout << endl;
}

void CyclicalList<Line>::Print()
{
	Line object;
	streampos Next = 0;
	// вывод первого элемента. для того, чтобы потом можно было сделать цикл
	seekg(beg.operator+(2 * sizeof(streampos)));

	read((char*)&object.len, sizeof(int));
	object.String = new char[object.len + 1];
	read(object.String, object.len * sizeof(char));
	object.String[object.len] = '\0';
	read((char*)object.time_buf, 8 * sizeof(char));

	cout << object.len << ", " << object.String << ", " << object.time_buf << "   ";

	seekg(beg.operator+(sizeof(streampos)));
	read((char*)&Next, sizeof(streampos));

	// вывод остальных элементов
	while (Next != beg)
	{
		seekg(Next.operator+(2 * sizeof(streampos)));

		read((char*)&object.len, sizeof(int));
		object.String = new char[object.len + 1];
		read(object.String, object.len * sizeof(char));
		object.String[object.len] = '\0';
		read((char*)object.time_buf, 8 * sizeof(char));

		cout << object.len << ", " << object.String << ", " << object.time_buf << "   ";

		seekg(Next.operator+(sizeof(streampos)));
		read((char*)&Next, sizeof(streampos));
	}
	cout << endl;
}
template <class Type>
void CyclicalList<Type>::Remove()// удаление последнего элемента в списке
{
	streampos Prev, Next, Destroy;
	//сохраняем указатели на предыдущий и следующий элементы удаляемого элемента
	seekg(beg);
	read((char*)&Destroy, sizeof(streampos));
	seekg(Destroy);
	read((char*)&Prev, sizeof(streampos));
	seekg(Destroy.operator+(sizeof(streampos)));
	read((char*)&Next, sizeof(streampos));

	//заменяем у предыдущего элемента указатель на следующий элемент
	seekg(Prev.operator+(sizeof(streampos)));
	write((char*)&Next, sizeof(streampos));

	//заменяем у следующего элемента указатель на предыдущий
	seekg(Next);
	write((char*)&Prev, sizeof(streampos));

	size--;
}
template <class Type>
void CyclicalList<Type>::Update(int Num, Type obj)
{
	streampos Temp;

	if (Num == 1)
	{
		seekg(beg.operator+(2 * sizeof(streampos)));
		write((char*)&obj, sizeof(Type));
	}

	else
	{
		seekg(beg.operator+(sizeof(streampos)));//Next для первого
		read((char*)&Temp, sizeof(streampos));

		for (int i = 1; i < Num - 1; i++)
		{
			seekg(Temp.operator+(sizeof(streampos)));//Next для текущего
			read((char*)&Temp, sizeof(streampos));
		}

		seekg(Temp.operator+(2 * sizeof(streampos)));
		write((char*)&obj, sizeof(Type));
	}
}

void CyclicalList<Line>::Update(int Num, Line obj)
{
	streampos Temp;

	if (Num == 1)
	{
		seekg(beg.operator+(2 * sizeof(streampos)));

		write((char*)&obj.len, sizeof(int));
		write(obj.String, obj.len * sizeof(char));
		write((char*)obj.time_buf, 8 * sizeof(char));
	}

	else
	{
		seekg(beg.operator+(sizeof(streampos)));//Next для первого
		read((char*)&Temp, sizeof(streampos));

		for (int i = 1; i < Num - 1; i++)
		{
			seekg(Temp.operator+(sizeof(streampos)));//Next для текущего
			read((char*)&Temp, sizeof(streampos));
		}

		seekg(Temp.operator+(2 * sizeof(streampos)));

		write((char*)&obj.len, sizeof(int));
		write(obj.String, obj.len * sizeof(char));
		write((char*)obj.time_buf, 8 * sizeof(char));
	}
}
template <class Type>
void CyclicalList<Type>::Sort()
{
	streampos P1, P2, Prev1, Prev2, Next1, Next2;
	Type obj1, obj2;
	seekg(beg);
	P1 = tellg();
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i; j < size - 1; j++)
		{
			seekg(P1.operator+(sizeof(streampos)));
			read((char*)&P2, sizeof(streampos));
			seekg(P1.operator+(2 * sizeof(streampos)));
			read((char*)&obj1, sizeof(Type));
			seekg(P2.operator+(2 * sizeof(streampos)));
			read((char*)&obj2, sizeof(Type));
			if (obj1 > obj2)
			{
				//сохраняем старые указатели
				seekg(P1);
				read((char*)&Prev1, sizeof(streampos));
				Prev2 = P1;

				Next1 = P2;
				seekg(P2.operator+(sizeof(streampos)));
				read((char*)&Next2, sizeof(streampos));

				//меняем указатели
				seekg(P2);
				write((char*)&Prev1, sizeof(streampos));
				seekg(P1);
				write((char*)&Next1, sizeof(streampos));
				seekg(Next2);
				write((char*)&Prev2, sizeof(streampos));

				seekg(Prev1.operator+(sizeof(streampos)));
				write((char*)&Next1, sizeof(streampos));
				seekg(P2.operator+(sizeof(streampos)));
				write((char*)&Prev2, sizeof(streampos));
				seekg(P1.operator+(sizeof(streampos)));
				write((char*)&Next2, sizeof(streampos));

				if (j == i)
					beg = P2;
			}
			else
				P1 = P2;
		}
		seekg(beg);
		P1 = tellg();
	}
}

void CyclicalList<Line>::Sort()
{
	streampos P1, P2, Prev1, Prev2, Next1, Next2;
	int obj1, obj2;
	seekg(beg);
	P1 = tellg();
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i; j < size - 1; j++)
		{
			seekg(P1.operator+(sizeof(streampos)));
			read((char*)&P2, sizeof(streampos));
			seekg(P1.operator+(2 * sizeof(streampos)));
			read((char*)&obj1, sizeof(int));
			seekg(P2.operator+(2 * sizeof(streampos)));
			read((char*)&obj2, sizeof(int));
			if (obj1 > obj2)
			{
				//сохраняем старые указатели
				seekg(P1);
				read((char*)&Prev1, sizeof(streampos));
				Prev2 = P1;

				Next1 = P2;
				seekg(P2.operator+(sizeof(streampos)));
				read((char*)&Next2, sizeof(streampos));

				//меняем указатели
				seekg(P2);
				write((char*)&Prev1, sizeof(streampos));
				seekg(P1);
				write((char*)&Next1, sizeof(streampos));
				seekg(Next2);
				write((char*)&Prev2, sizeof(streampos));

				seekg(Prev1.operator+(sizeof(streampos)));
				write((char*)&Next1, sizeof(streampos));
				seekg(P2.operator+(sizeof(streampos)));
				write((char*)&Prev2, sizeof(streampos));
				seekg(P1.operator+(sizeof(streampos)));
				write((char*)&Next2, sizeof(streampos));

				if (j == i)
					beg = P2;
			}
			else
				P1 = P2;
		}
		seekg(beg);
		P1 = tellg();
	}
}

#include "HeaderLine.h"

//конструтор без параметров
Line::Line()
{
	len = -1;
	String = NULL;
	_strtime_s(time_buf);
}

// конструктор с параметрами
Line::Line(int Len_in, char* Str_in)
{
	len = Len_in;
	String = new char[len + 1];
	strcpy(String, Str_in);
	_strtime_s(time_buf);

}

//деструктор
Line:: ~Line()
{
	if (String != NULL)
		delete[] String;
}

//конструктор копирования
Line::Line(const Line& Str_in)
{
	len = Str_in.len;
	String = new char[len + 1];
	strcpy(String, Str_in.String);
	_strtime_s(time_buf);
}

// метод сумма
void Line::Sum(Line String1, Line String2)
{
	String = new char[String1.len + String2.len + 1];
	len = String1.len + String2.len;
	_strtime_s(time_buf);

	strcpy(String, String1.String);
	strcat(String, String2.String);
}

// метод для вывода
void Line::Print()
{
	if (String != NULL)
	{
		cout << String << ", " << "len=" << len << ", time=" << time_buf << endl;
	}
}

//метод для изменения значений
void Line::Change(char *String_in)
{
	if (String != NULL)
		delete[] String;

	len = strlen(String_in);
	String = new char[len + 1];
	strcpy(String, String_in);
	_strtime_s(time_buf);
}

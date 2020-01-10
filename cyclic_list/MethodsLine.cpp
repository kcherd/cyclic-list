#include "HeaderLine.h"

//���������� ��� ����������
Line::Line()
{
	len = -1;
	String = NULL;
	_strtime_s(time_buf);
}

// ����������� � �����������
Line::Line(int Len_in, char* Str_in)
{
	len = Len_in;
	String = new char[len + 1];
	strcpy(String, Str_in);
	_strtime_s(time_buf);

}

//����������
Line:: ~Line()
{
	if (String != NULL)
		delete[] String;
}

//����������� �����������
Line::Line(const Line& Str_in)
{
	len = Str_in.len;
	String = new char[len + 1];
	strcpy(String, Str_in.String);
	_strtime_s(time_buf);
}

// ����� �����
void Line::Sum(Line String1, Line String2)
{
	String = new char[String1.len + String2.len + 1];
	len = String1.len + String2.len;
	_strtime_s(time_buf);

	strcpy(String, String1.String);
	strcat(String, String2.String);
}

// ����� ��� ������
void Line::Print()
{
	if (String != NULL)
	{
		cout << String << ", " << "len=" << len << ", time=" << time_buf << endl;
	}
}

//����� ��� ��������� ��������
void Line::Change(char *String_in)
{
	if (String != NULL)
		delete[] String;

	len = strlen(String_in);
	String = new char[len + 1];
	strcpy(String, String_in);
	_strtime_s(time_buf);
}

#include "Header.h"
#include "HeaderLine.h"
void main()
{
	setlocale(LC_ALL, "Russian");
	int act;
	char nameFile[] = "Test.txt";

	cout << "�������� ��������:" << "\n" << "1: ����������" << "\n" << "2: ��������" << "\n" << "3: ������ ��������" << "\n" << "4: ����������" << endl;
	cin >> act;

	switch (act)
	{
	case 1:
	{
		char Arr1[4] = "cvb", Arr2[5] = "wert", Arr3[3] = "a";
		Line L1(3, Arr1), L2(4, Arr2), L3(1, Arr3);
		CyclicalList<Line> List1(nameFile);
		List1.Add(L1);
		List1.Add(L2);
		List1.Add(L3);
		List1.Print();
		break;
	}
	case 2:
	{
		CyclicalList<char> List1(nameFile);
		List1.Add('d');
		List1.Add('c');
		List1.Add('b');
		List1.Print();
		List1.Remove();
		List1.Print();
		break;
	}
	case 3:
	{
		CyclicalList<char> List1(nameFile);
		List1.Add('d');
		List1.Add('c');
		List1.Add('b');
		List1.Print();
		List1.Update(3, 'a');
		List1.Print();
		break;
	}
	case 4:
	{
		CyclicalList<int> List1(nameFile);
		List1.Add(3);
		List1.Add(2);
		List1.Add(1);
		List1.Print();
		List1.Sort();
		List1.Print();
		break;
	}
	default:
	{
		cout << "������ �������� ���" << endl;
		break;
	}
	}

	system("pause");
}

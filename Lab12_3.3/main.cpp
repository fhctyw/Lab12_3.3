#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <Windows.h>
using namespace std;

enum class ZodiacSigns { Ram, Bull, Twins, Crab, Lion, Virgin, Balance, Scorpion, Archer, Goat, Water_Bearer, Fish };
string strZodiacSigns[] = { "Ram", "Bull", "Twins", "Crab", "Lion", "Virgin", "Balance", "Scorpion", "Archer", "Goat", "Water_Bearer", "Fish" };
struct Zodiac
{
	string name, sur_name;
	ZodiacSigns sign;
	int date[3];
};

string names[] {
	"���",
	"������",
	"�����",
	"�����",
	"������",
	"�������",
	"�������",
	"���������",
	"�\'��",
	"���������",

	"�����",
	"����",
	"����",
	"�����",
	"�������",
	"�������",
	"�����",
	"������",
	"���������",
	"������"
};
string sur_names[]{
	"���������",
	"³������",
	"�����������",
	"�����������",
	"��������",
	"��������",
	"�����",
	"���������",
	"��������",
	"��������",

	"�����",
	"�������",
	"�������",
	"�����������",
	"����������",
	"��������",
	"���������",
	"�����",
	"����������",
	"����������"
};

ZodiacSigns getSign(int day, int month)
{
	if (month == 1 && day >= 21 || month == 2 && day <= 19)
		return ZodiacSigns::Water_Bearer;
	if (month == 2 && day >= 20 || month == 3 && day <= 20)
		return ZodiacSigns::Fish;
	if (month == 3 && day >= 21 || month == 4 && day <= 20)
		return ZodiacSigns::Ram;
	if (month == 4 && day >= 21 || month == 5 && day <= 21)
		return ZodiacSigns::Bull;
	if (month == 5 && day >= 22 || month == 6 && day <= 21)
		return ZodiacSigns::Twins;
	if (month == 6 && day >= 22 || month == 7 && day <= 23)
		return ZodiacSigns::Crab;
	if (month == 7 && day >= 24 || month == 8 && day <= 23)
		return ZodiacSigns::Lion;
	if (month == 8 && day >= 24 || month == 9 && day <= 23)
		return ZodiacSigns::Virgin;
	if (month == 9 && day >= 24 || month == 10 && day <= 23)
		return ZodiacSigns::Balance;
	if (month == 10 && day >= 24 || month == 11 && day <= 22)
		return ZodiacSigns::Scorpion;
	if (month == 11 && day >= 23 || month == 12 && day <= 21)
		return ZodiacSigns::Archer;
	if (month == 12 && day >= 22 || month == 1 && day <= 20)
		return ZodiacSigns::Goat;
}

void Generate(Zodiac*& z, size_t cnt)
{
	for (size_t i = 0; i < cnt; i++)
	{
		z[i].date[0] = 1 + rand() % 28;
		z[i].date[1] = 1 + rand() % 12;
		z[i].date[2] = 1900 + rand() % 123;
		z[i].name = names[rand() % 20];
		z[i].sur_name = sur_names[rand() % 20];
		z[i].sign = getSign(z[i].date[0], z[i].date[1]);
	}
}

bool checkInputs(Zodiac z)
{
	return (int)z.sign >= 0 && (int)z.sign < 13 && z.date[0] > 0 && z.date[0] <= 28 && z.date[1] > 0 && z.date[1] <= 12 && z.date[2] >= 1900 && z.date[2] <= 2022;
}

void Input(Zodiac*& z, size_t cnt)
{
	for (size_t i = 0; i < cnt; i++)
	{
		Zodiac tmp;
		do {
			cin.get();
			cin.sync();
			cout << "������ �������: "; getline(cin, tmp.sur_name);
			cout << "������ ��\'�: "; getline(cin, tmp.name);
			int s;
			cout << "������ ���� ������\n(0 - ����, 1 - ������, 2 - ��������, 3 - ���, 4 - ���, 5 - ĳ��, 6 - ������, 7 - �������, 8 - ������, 9 - ������, 10 - ������, 11 - ����): "; cin >> s;
			tmp.sign = (ZodiacSigns)s;
			cout << "������ ���� ����������: "; cin >> tmp.date[0];
			cout << "������ ����� ����������: "; cin >> tmp.date[1];
			cout << "������ �� ����������: "; cin >> tmp.date[2];
		} while (!checkInputs(tmp));
		z[i] = tmp;
	}
}

void Display(Zodiac* z, size_t cnt)
{
	if (z) {
		cout << "----------------------------------------------------------------" << endl;
		cout << "| � |  �������  |   ��\'�   |���� ������| ���� | ����� | �� |" << endl;
		cout << "----------------------------------------------------------------" << endl;
		cout << left;
		for (size_t i = 0; i < cnt; i++)
		{
			cout << '|' <<
				setw(3) << i + 1 << '|' <<
				setw(12) << z[i].sur_name << '|' <<
				setw(10) << z[i].name << '|' <<
				setw(12) << strZodiacSigns[(int)z[i].sign] << '|' <<
				setw(6) << z[i].date[0] << '|' <<
				setw(8) << z[i].date[1] << '|' <<
				setw(5) << z[i].date[2] << '|' << endl;
		}
		cout << "----------------------------------------------------------------" << endl;
	}
	else
		cout << "������� �����" << endl;
	cout << endl;
}

void Save(Zodiac* z, size_t cnt)
{
	if (z) {
		fstream f;
		f.open("data", ios::binary | ios::out);
		if (f.is_open() && !f.fail())
		{
			f.write((char*)&cnt, sizeof(cnt));
			for (size_t i = 0; i < cnt; i++) {
				f.write((char*)&z[i].date, sizeof(z[i].date));
				size_t l = z[i].sur_name.length() + 1;
				f.write((char*)&l, sizeof(l));
				f.write(z[i].sur_name.c_str(), l);
				l = z[i].name.length() + 1;
				f.write((char*)&l, sizeof(l));
				f.write(z[i].name.c_str(), l);
				f.write((char*)&z[i].sign, sizeof(z[i].sign));
			}
		}
		else
			cout << "������� ��� �������� �����" << endl;
		
		f.close();
	}
	else
		cout << "������� �����" << endl;
	cout << endl;
}

void Load(Zodiac*& z, size_t &cnt)
{
	if (z) {
		delete[] z;
		z = nullptr;
	}

	fstream f;
	f.open("data", ios::binary | ios::in);
	if (f.is_open() && !f.fail())
	{
		f.read((char*)&cnt, sizeof(cnt));
		z = new Zodiac[cnt];
		for (size_t i = 0; i < cnt; i++)
		{
			f.read((char*)&z[i].date, sizeof(z[i].date));
			size_t l;
			f.read((char*)&l, sizeof(l));
			char* tmp = new char[l];
			f.read(tmp, l);
			z[i].sur_name = tmp;
			delete[] tmp;
			f.read((char*)&l, sizeof(l));
			tmp = new char[l];
			f.read(tmp, l);
			z[i].name = tmp;
			delete[] tmp;
			f.read((char*)&z[i].sign, sizeof(z[i].sign));
		}
	}
	else
		cout << "������� ��� ���������� � �����" << endl;
	cout << endl;
}

void Create(Zodiac* &z, size_t &cnt)
{
	cout << "������ ������� ��������: "; cin >> cnt;
	if (z) {
		delete[] z;
		z = nullptr;
	}
	z = new Zodiac[cnt];
	int c;
	do {
		cout << "1 - ����������� �����������" << endl;
		cout << "2 - ������ ���" << endl;
		cout << "0 - �����" << endl;
		cout << "����: "; cin >> c;

		if (c == 1) {
			Generate(z, cnt);
			break;
		}
		else if (c == 2) {
			Input(z, cnt);
			break;
		}
		cout << endl;
	} while (c != 0);
}

void Sort(Zodiac* z, size_t cnt)
{
	if (z) {
		for (size_t i = 0; i < cnt; i++)
			for (size_t j = 0; j < cnt - i - 1; j++)
				if (z[j].sur_name > z[j + 1].sur_name)
					swap(z[j], z[j + 1]);
	}
	else
		cout << "������� �����" << endl;
	cout << endl;
}


void SearchByZodiac(Zodiac* z, size_t cnt)
{
	if (z) {
		int sign;
		cout << "������ ���� ������: "; cin >> sign;
		size_t c = 0;
		for (size_t i = 0; i < cnt; i++)
			if (z[i].sign == (ZodiacSigns)sign)
				c++;
		
		if (c > 0)
		{
			Zodiac* tmp = new Zodiac[c];
			for (size_t i = 0, i1 = 0; i < cnt; i++)
				if (z[i].sign == (ZodiacSigns)sign)
					tmp[i1++] = z[i];

			Display(tmp, c);
			delete[] tmp;
		}
		else
			cout << "���� ����� �� ��� ������ ������" << endl;
	}
	else
		cout << "������� �����" << endl;
}

int main()
{
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	int c;
	Zodiac* z = nullptr;
	size_t cnt = 0;
	do
	{
		cout << "1 - �������� ����� �����" << endl;
		cout << "2 - ��������� � �����" << endl;
		cout << "3 - ��������� � ����" << endl;
		cout << "4 - ³��������� �����" << endl;
		cout << "5 - ������������� �� ��������� (� ���������� �������)" << endl;
		cout << "6 - ���� �� ����� ���������� ��� �����, �� ���������� �� ������" << endl;
		cout << "0 - �����" << endl;
		cout << "����: "; cin >> c;

		switch (c)
		{
		case 1: {
			Create(z, cnt);
			break;
		}
		case 2: {
			Load(z, cnt);
			break;
		}
		case 3: {
			Save(z, cnt);
			break;
		}
		case 4: {
			Display(z, cnt);
			break;
		}
		case 5: {
			Sort(z, cnt);
			break;
		}
		case 6: {
			SearchByZodiac(z, cnt);
			break;
		}
		}

	} while (c != 0);

	return 0;
}
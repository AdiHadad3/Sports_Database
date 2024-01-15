#define _CRT_SECURE_NO_WARNINGS//����� ����� ����� ��������� STR
#include <iostream>//������ ��� ���
#include <cstring>//������ �������� STR
using namespace std;

#define SIZE_PNAME 10//���� ���� ����� �� ���� �� �������
#define SIZE_FNAME 15//���� ���� ����� �� ����� �� �������
#define STATIC_SIZE 100//���� ������ ���� �������

struct event//���� �����
{
	char* title;//�� �����
	char* place;//����� �����
	int year;// ��� ������
	event* next;// ����� ����� ��� ������ ������� ���� ���� �����
};

struct sportsman//���� �������
{
	int id;//���� �����
	char Pname[SIZE_PNAME];//�� ����
	char Fname[SIZE_FNAME];//�� �����
	char* club;//�� ������ ������
	bool gen;//����� 0, ���� 1
	event* list;//����� ������ ������ �� �������� ��� ����� ��������
};

struct nodeCheck//���� ���� ����� ������ ������ �������
{
	char* CheckStr;//����� ����� ����� �� ��� ����
	nodeCheck* next;//����� �� ���� ���� ���� ���
};

nodeCheck* AddNewClubToList(char* club, nodeCheck* HeadClublist)//������� ������ ������ ��� ������ ������� �������
{
	nodeCheck* NewCheckClub = new nodeCheck;//����� ������ ����� ��� 
	NewCheckClub->CheckStr = new char[strlen(club) + 1];//����� ���� ����� ���� ������ ������
	strcpy(NewCheckClub->CheckStr, club);//����� �� ���� ������� ����� ������� ������ ������ 
	NewCheckClub->next = HeadClublist;//�"����" �� ����� ���� ����� �� ����� ������ ��� ������
	HeadClublist = NewCheckClub;//����� ��� ������ �� ����� ����
	return HeadClublist;
}
event* AddNewEventToList(const event* Event, event* HeadEventChecklist)//������� ������ ����� ��� ������ ������� �������
{
	event* NewCheckEvent = new event;//����� ����� ����� ��� 
	NewCheckEvent->title = new char[strlen(Event->title) + 1];//����� ���� ����� ���� �� ����� ������
	strcpy(NewCheckEvent->title, Event->title);//����� �� ����� ������ ���� ��� 
	NewCheckEvent->place = new char[strlen(Event->place) + 1];//����� ���� ����� ���� �� ����� ������
	strcpy(NewCheckEvent->place, Event->place);//����� �� ����� ������ ���� ��� 
	NewCheckEvent->year = Event->year;//����� ����
	NewCheckEvent->next = HeadEventChecklist;//�"����" �� ����� ���� ����� �� ����� ������ ��� ������
	HeadEventChecklist = NewCheckEvent;//����� ��� ������ �� ����� ����
	return HeadEventChecklist;
}
event* CreateNewEvent(event* temp, event* NewEvent)//�������� ������� ���� ��� ���� ����� ������ �� ������ ��� ������ ������
{
	NewEvent = new event;
	NewEvent->title = new char[strlen(temp->title) + 1];//���� ���� ������ ��� ������ ����
	strcpy(NewEvent->title, temp->title);//����� �� �� ������ ������ ������ ��� ������ ����
	NewEvent->place = new char[strlen(temp->place) + 1];//���� ���� ������ ����� ������ ����
	strcpy(NewEvent->place, temp->place);//����� �� ���� ������ ������ ������ ��� ������ ����
	NewEvent->year = temp->year;//����� �� ��� ������ ������ ������ ���� ������ ����
	NewEvent->next = NULL;//
	return NewEvent;//����� �� ������ ����
}
void deleteEventList(event* HeadEventChecklist)//����� ������ �� ����� ������ �� �������
{
	event* tmpCheckEvent = HeadEventChecklist;//����� ������ ���� ���� ������
	while (tmpCheckEvent != NULL)//����� �� ������ ������� �����
	{
		HeadEventChecklist = HeadEventChecklist->next;//���� ������ ��� ������ �� ����� ��� ������ ������ �� ����� ����� ��
		delete[] tmpCheckEvent->title;
		delete[] tmpCheckEvent->place;
		delete tmpCheckEvent;
		tmpCheckEvent = HeadEventChecklist;
	}
}
void deleteNodeCheckList(nodeCheck* HeadChecklist)//����� ������ ����� ������ ������� ������� ������� ����� ���
{
	nodeCheck* tmp = HeadChecklist;
	while (tmp != NULL)//����� ������ ����� ���������
	{
		HeadChecklist = HeadChecklist->next;//���� ������ ��� ������ �� ����� ��� ������ ������ �� ����� ����� ��
		delete[] tmp->CheckStr;
		delete tmp;
		tmp = HeadChecklist;
	}
}

int countLines(const char* fname)//������� ������ �� ���� ������ ����� ��� ����� ������
{
	FILE* myfile = fopen(fname, "r");//����� ����� ������ ������
	if (myfile == NULL)//����� ��� ����� ���� �����
	{
		cout << "Error - file read error !\n";//����� ����� ����� �� ����� �� ����
		return 0;
	}
	int counter = 0;
	char str[STATIC_SIZE];
	while (!feof(myfile))//����� �� ������ �� ���� ���� �����
	{
		if (fgets(str, STATIC_SIZE, myfile) != NULL)//����� �� �� ������ �����
			counter++;//����� �� ���� ������
	}
	fclose(myfile);//����� �����
	return (counter - 1);//����� ���� ������ ��� ���� ������
}

void FromFileToStruct(const char* fname, sportsman* arr, int size)//���� ����� ��������� ����� ������ ������
{
	FILE* myfile = fopen(fname, "r");//����� ����� ������ ������
	if (myfile == NULL)//����� ��� ����� ���� �����
	{
		cout << "Error - file read error !\n";//����� ����� ����� �� ����� �� ����
		return;
	}
	char tempSentence[STATIC_SIZE];
	char* tempWord;
	int counter;
	int intTempWpword;
	bool ManOrWoman = 0;//���� ������ ��� ��� ����� ���� �������
	fgets(tempSentence, STATIC_SIZE, myfile);//����� �� ���� ������ ��� ����� ����� ��������
	for (int i = 0; i < size; i++)//����� ������ �� �� ����� ����� ������ ������ ����� �� ����� ������ �� ���� �"����"- ���� ��������� �����
	{
		if (fgets(tempSentence, STATIC_SIZE, myfile) != NULL)//����� �� �� ����� �����
		{
			tempWord = strtok(tempSentence, "\n;");//�������� ����� ����� ������� ������
			counter = 0;//����� ������� ������ ������
			while (tempWord != NULL)//�� ��� ������� ��� ���� ����� �����
			{
				switch (counter)//������� ������� �� ��� �������
				{
				case(0): arr[i].id = atoi(tempWord);//���� ���� ������� ������ ���� ���� ������ �� ��������
					break;
				case(1):strcpy(arr[i].Pname, tempWord);//������ ������� ���� ������ ����� ���� ��� �����
					break;
				case(2):strcpy(arr[i].Fname, tempWord);//������ ������� ������ ������ ����� ���� �� ������
					break;
				case(3): arr[i].club = new char[strlen(tempWord) + 1];//����� �� ���� ������ ���
					strcpy(arr[i].club, tempWord);//����� ���� ������� ����� �������
					break;
				case(4): intTempWpword = atoi(tempWord);//���� ���� ������� ����� ����� ���
					if (intTempWpword == 1)//�� ������� ��� 1 ����� ��� ���
						arr[i].gen = 0;//����� �� ���� ��� ���, ����� ���� ������ �����
					else arr[i].gen = 1;//������, �� ����� ��� 0 ����� ����� ����, ��� 0 ���� ���
				}
				counter++;//��������� ����� ������� ���
				tempWord = strtok(NULL, "\n;");//����� ������� ���
			}
			arr[i].list = NULL;//����� �� ������ ������ ������� �� ������ �������� ������ ����
		}
	}
	fclose(myfile);
}

void FromFileToList(const char* fname, sportsman* arr, int size)//������ ������ ������� ����� ����� ������ ����� ����� ������
{
	FILE* myfile = fopen(fname, "r");//����� ����� ������ ������
	if (myfile == NULL)//����� ��� ����� ���� �����
	{
		cout << "Error - file read error !\n";//����� ����� ����� �� ����� �� ����
		return;
	}
	char tempSentence[STATIC_SIZE];
	char* tempWord;
	int counter;
	int idSportMan = 0;
	event* newEvent;
	fgets(tempSentence, STATIC_SIZE, myfile);//����� ����� ������
	while (fgets(tempSentence, STATIC_SIZE, myfile) != NULL)//�� ��� �� ����� ���� �����
	{
		newEvent = new event;
		tempWord = strtok(tempSentence, "\n,");//�������� ����� ����� ������� ������
		counter = 0;
		while (tempWord != NULL)//�� ��� ������� ��� ���� ����� ������
		{
			switch (counter)//������� ������� �� ��� ������� �����
			{
			case(0):idSportMan = atoi(tempWord);//���� ���� ������� ������ ���� ���� ������ �� ��������
				break;
			case(1): newEvent->title = new char[strlen(tempWord) + 1];//����� ���� ����� ������� �� �� ������
				strcpy(newEvent->title, tempWord);//����� ���� ������� ���� ����� ������
				break;
			case(2):  newEvent->place = new char[strlen(tempWord) + 1];//����� ���� ����� ������� �� ���� ������
				strcpy(newEvent->place, tempWord);//����� ���� ������� ������ ����� ������
				break;
			case(3): newEvent->year = atoi(tempWord);//���� ���� ������� ������ ������� ���� ��� ������
			}
			counter++;//
			tempWord = strtok(NULL, "\n,");//���� �� �������
		}
		newEvent->next = NULL;//����� ������� ��� ����� ������ ����
		for (int i = 0; i < size; i++)//����� ������ �� �� ���� ���� ���������
		{
			if (arr[i].id == idSportMan)//�� ����� ����� ��� ����� ����� �� �������� ����� ������� �� ����� ���� �� ������ ���� ������ ������� ������ ��������
			{
				newEvent->next = arr[i].list;//���� �� ������ ���� ����� �� ����� ���� "����" �����
				arr[i].list = newEvent;//����� �� "����" ������ �� ����� ����� ���� ���� �����
				break;//��� ������� ���� ����� ������ ����� ������
			}
		}
	}
	fclose(myfile);//����� �����
}

sportsman* addSportsman(sportsman* arr, int& size)//����� ������� ���
{
	char str[STATIC_SIZE];//���� ��� ������ �������
	int IdCheck;//���� ����� ����� �"� ������ ������ �� ���� ���
	cout << "Please enter your family name: ";
	cin.ignore(); cin.getline(str, SIZE_FNAME);
	cout << "Please enter your id: ";
	cin >> IdCheck;
	for (int i = 0; i < size; i++)//����� ������ ��� �� ������ ������� ���� ���� ����� ������ ������� ���
	{
		if (strcmp(str, arr[i].Fname) == 0 && arr[i].id == IdCheck)//����� ����� ����� �������� �� ����� ��� ��� �����-�������� ����� �� ����� ��� �����
		{
			cout << "\nThe new athlete is already exists...\n";
			return arr;//����� �� ����� ����� ��� �����
		}
	}
	sportsman* newSportsManArray = new sportsman[size + 1];//����� ���� �������� ��� ����� �1 ��� ����� ���� �������� ����
	for (int j = 0; j < size; j++)//���� �� ����� ����� ���� ����� ����
	{
		newSportsManArray[j] = arr[j];
	}
	delete[] arr;//����� ���� ��������� �����
	newSportsManArray[size].id = IdCheck;//���� ����� ���� ������ ����� ���� �����
	cout << "Please enter your private name: ";
	cin.ignore(); cin.getline(newSportsManArray[size].Pname, SIZE_PNAME);
	strcpy(newSportsManArray[size].Fname, str);//����� ����� ���� ���� ���� �� ������
	cout << "Please enter your sport club: ";
	cin.getline(str, 100);
	newSportsManArray[size].club = new char[strlen(str) + 1];//����� ���� ����� ��� ���� �������
	strcpy(newSportsManArray[size].club, str);
	cout << "Please enter your gender (for woman-press '1', for man-press '0'): ";
	cin >> newSportsManArray[size].gen;
	newSportsManArray[size].list = NULL;//������ ���� ������ ������ ������ ������ ����
	size++;//����� ���� ����� �1
	cout << "The new athlete added!\n";
	return newSportsManArray;//�������� ����� �� ����� ���� �� ��������
}

bool addEvent(int id, sportsman* arr, int size)
{
	event* newEvent = new event;//����� �� ����� ����� ���
	char str[STATIC_SIZE];//���� ��� ����
	cout << "Please enter event title: ";
	cin.ignore(); cin.getline(str, STATIC_SIZE);//���� �� ������
	newEvent->title = new char[strlen(str) + 1];//����� ���� ����� ������ �� �� ������
	strcpy(newEvent->title, str);//����� �� ������ ����� �������
	cout << "Please enter event place: ";
	cin.getline(str, STATIC_SIZE);//���� ���� ������
	newEvent->place = new char[strlen(str) + 1];//����� ���� ����� ������ �� ���� ������
	strcpy(newEvent->place, str);//����� ���� ������ ����� �������
	cout << "Please enter event year: ";
	cin >> newEvent->year;//���� ���� ������
	newEvent->next = NULL;//����� ������ ������ ����� ������ ����
	event* tmp;//������ ��� ������ �� �����
	for (int i = 0; i < size; i++)//���� �� �� ����� ���� ���� ���������
	{
		if (arr[i].id == id)//����� ���� ����� ����� ���� ����� ����� ��������
		{
			tmp = arr[i].list;//����� ������ ��� ������ ����� ������ ������ �������
			if (tmp == NULL)//�� ��� ������� �������� ����� �� ������ ������ ������� ������ ���
			{
				cout << "\nThe new event is added!\n";
				arr[i].list = newEvent;//���� �� ������ ���� ��������
				cout << arr[i].list->title;
				return true;
			}
			while (true)//���� �� �� ����� ������ ����� ���� �����
			{
				if (strcmp(newEvent->title, tmp->title) == 0 && strcmp(newEvent->place, tmp->place) == 0 && newEvent->year == tmp->year)//����� ���� ���� ��� ���� ������ ����� ����� ������ ����� ������ ������� �� �������� �� ��������
				{
					cout << "\nThe event is already exists...\n";
					return false;//�� ����� ���� ���� ��� �������� ����� ���
					break;
				}
				else//�� �� ����� ��� ��� ���� ��� ��������
				{
					if (tmp->next != NULL)//�� �� ����� ����� ������ ������ �������
						tmp = tmp->next;//����� �� ������ ������ ����� �����
					else break;
				}
			}
			cout << "\nThe new event is added!\n";
			tmp->next = newEvent;//�� ���� �� �� ������ ��� ���� ������� ����� �� ����� ������
			return true;
		}
	}
	cout << "\nThe id number does not apply any athlete...\n";
	return false;
}

void CheckEvent(char* E, sportsman* arr, int size)//������� ������� �� ���� ��������� ������� ������ ������
{
	event* tmp;//����� ������ ��� �� ����� ���
	for (int i = 0; i < size; i++)//����� ������ �� �� ��������� ������ ��� ������ ���� ������ ������� �� ��������
	{
		tmp = arr[i].list;//������ ��� ����� �� ����� ������ ������
		while (tmp != NULL)//�� ��� �� ����� ���� ������
		{
			if (strcmp(tmp->title, E) == 0)//����� ������� ���� ��� ������ ������ ����� ������ ������ ����� �� ��� ���� �� �������� ��"�
			{
				cout << arr[i].Pname << " " << arr[i].Fname << endl;
				break;
			}
			tmp = tmp->next;//����� ������� ������ ��� �� ��������
		}
	}
}

void printNoEvents(sportsman* arr, int size)
{
	nodeCheck* HeadClublist = NULL;//����� ������ ������ �� ����� ������ ������ ����� �������, ������ ����� �� ����� ����
	nodeCheck* tmp;//������ ���
	for (int i = 0; i < size; i++)//����� ������ �� �� ���� ��������� ������ ��� �������� �� ����� ���� �����, ���� ��� ����� �� ������� ��� ��� �������� ����� ����� ������
	{
		tmp = HeadClublist;//������ ���� ����� �� ����� ������ ������ ��������� ������
		if (arr[i].list == NULL)//�� �� ������ ������� ������ �� �������� ����� ��� ������ ������� ����� ��� ���� ������ ������ ������ ��� �� ���� ��� ����� ��� ������� �������
		{
			while (tmp != NULL)//�� ��� �� ����� ���� ������
			{
				if (strcmp(arr[i].club, tmp->CheckStr) == 0)//�� ������� ����� ��� ���� ������ ��� ������� 
					break;
				tmp = tmp->next;//���� �� ������� �� ��� ����� �� �� ������� ������� ���
			}
			if (tmp == NULL)//�� ������� ���� ���� ������ �� ���� ��� �� ���� ������� ��������� ������� ������ ������ �������
			{
				AddNewClubToList(arr[i].club, HeadClublist);
				cout << arr[i].club << endl;//����� �� ������� ��������
			}
		}//���� �������� ��� ������
	}
}

void printEvent(char* C, int Y, sportsman* arr, int size)
{
	event* tmp;//������ ������ �� �������� ����� ����� ����� ���� �������
	event* headEventsListCheck = NULL;//������ ������ �� ����� ������ �� ������ ������-�� ����� ���� ������ ����� ������ ����� ��� ���� �� �����, ��� �� �� �����
	event* tmpCheck;//������ ������ �� ������ ������� �� �������� ����� ������ ����
	for (int i = 0; i < size; i++)//����� ������ �� ����� ���� ���������
	{
		tmp = arr[i].list;//������ ����� �� ����� ������ ������ ������ ��������
		tmpCheck = headEventsListCheck;
		while (tmp != NULL)//�� ��� �� ����� ���� ����� ������ �������� ����� ���� ������� ��� ���� ������� ������� ������ ������� �����
		{
			if (strcmp(arr[i].club, C) == 0 && tmp->year == Y)//�� ����� �������� ���� ������� ����� �� ����� �� ����� �� ���� ������ ������� �� ����� ��������
			{
				while (tmpCheck != NULL)//�� ��� �� ����� ���� ����� ������ ������ ����� �� ������ ������ �������� ��� �����
				{
					if (strcmp(tmpCheck->title, tmp->title) == 0 && strcmp(tmpCheck->place, tmp->place) == 0 && tmpCheck->year == tmp->year)//�� �� ������� ��� ������ ������ ����� ���� �������� ���� ���� ������ ������� ���
						break;//��� �������
					tmpCheck = tmpCheck->next;//����� ������ ���� ������ ������ ��� 
				}
				if (tmpCheck == NULL)//�� ����� ���� ����� ������
				{
					headEventsListCheck = AddNewEventToList(tmp, headEventsListCheck);//����� �� ������ ������ ������� ������ ������ �������
					cout << tmp->title << endl;//����� �� ������ ��������
				}
			}tmp = tmp->next;//����� ������ ��� �� ��������	
		}
	}
	if (headEventsListCheck == NULL)//�� ��� �� ����� ������ ������� ��� ������� ������� ���� ������ ����� ����� ������
		cout << "There are no suitable events";
	else deleteEventList(headEventsListCheck);//�� ����� ������� ����� ����� �� ������� ����


}

void compareSport(int id1, int id2, sportsman* arr, int size)
{
	int i = 0;
	int j = 0;
	for (; i < size; i++)//���� �� ����� �� ���� ���� ������ �� �������� ������
	{
		if (arr[i].id == id1)//���� �� ���� ������ ������
			break;//����
	}
	for (; j < size; j++)//���� �� ����� �� ���� ���� ������ �� �������� ����
	{
		if (arr[j].id == id2)//���� �� ���� ������ ������
			break;//����
	}
	if (i == size) cout << "\nThe first id is not identified\n";//���� ����� ����� �� ����
	if (j == size) cout << "\nThe second id is not identified\n";//���� ����� ��� �� ����
	int counter = 0;//����� ����� ��� �� ������� �������
	event* temp1 = arr[i].list;//����� ����� ��� ������ �� ������ ������ �� �������� ������
	event* temp2;//����� ����� ��� ������ �� ����� ���� �����
	if (i != size && j != size)//�� ��� ����� ����� �������
	{
		while (temp1 != NULL)//�� ��� �� ����� ������ ������ �� �������� ������ ��� ���� ��� ����� ����� ����
		{
			temp2 = arr[j].list;//����� �� ������ ������ �� ������ ����
			while (temp2 != NULL && temp1 != NULL)//���� ����� �� ��� �� ����� ����� ������ �� ������� ����
			{
				if ((strcmp(temp1->title, temp2->title) != 0) || (temp1->year != temp2->year))//�� �� ���� ����� ��� ��� ��������� �����
				{
					temp2 = temp2->next;//���� �� ������ ������ ���� �� �������� ����
				}
				else//�� �� ����� ���� ����� ��� ��� ��������� �����
				{
					cout << "\nBoth athletes participated in '" << temp1->title << "' event at " << temp1->year;//����� �� �� ������ ����� �� ��� ��
					counter++;//����� ������ ��� ��� ���� �������� ��������
					temp1 = temp1->next;//����� ������ ��� �� �������� ������ ��� ����� �� �� ��� ����� �������� ����
				}
			}
			if (temp1 != NULL)
				temp1 = temp1->next;//���� �� ����� ����� ��� ������ �� �������� ������ ��� �������� �� �������� ����, ����� ������ ���� �� �������� ������ ������ ����� ����
		}
		if (counter == 0)//����� ���� ������� ������� ����� ���
			cout << "\nNo matching events\n";
	}
}

void BestClub(sportsman* arr, int size)//������� ������ �� ������� �� ��� ���� ������� �������� ������ ��� ��� �������� �� ������� ���� �������
{
	int countEvents = 0;//����� �������� ������� �������
	int maxEvents = 0;//���� ������� ������� ���� �� ���������
	char* MaxClub = arr[0].club;//�� ������� �� ������� ������� �����, ����� ������ �����
	event* tmpSE;//������ ��� ����� �� ������ ��������
	event* HeadEvent = NULL;//����� ���� ����� ����� ������ �����
	event* tmpCheckEvent;
	nodeCheck* HeadClub = NULL;//����� ���� ����� ����� ������ ������
	nodeCheck* tmpCheckClub;
	for (int i = 0; i < size; i++)//����� ������ �� �� ����� ���� ��������� ���� ������ ����� �� �� ������� ��� ��������
	{
		tmpCheckClub = HeadClub;//����� ��� ��� ��� ���� ������� ������
		while (tmpCheckClub != NULL)//�� ��� �� ����� ���� ����� ������ ������ ����� ����� ��� ����� �� ��� ����
		{
			if (strcmp(arr[i].club, tmpCheckClub->CheckStr) == 0)//�� ���� ������� ��� ������� ������ ���� ������ ����� ������ ������ ��� �������
				break;//��� ���� ������� ������� ��, ������� ��� �����
			tmpCheckClub = tmpCheckClub->next;//����� �� ������� �����
		}
		if (tmpCheckClub == NULL)//�� ��� ����� �� ������� ��� ���� ����
		{
			HeadClub = AddNewClubToList(arr[i].club, HeadClub);//����� �� ����� �� ������ �� �� ������
			countEvents = 0;//����� ����� ������� ���� ��� ������ 
			for (int j = i; j < size; j++)//����� ������ �� �� ��������� ���� �������� ������ 
			{
				if (strcmp(arr[i].club, arr[j].club) == 0)//�� ��� ���� ���� ��� ��������� ����� �� �� �������� ������ ������
				{
					tmpSE = arr[j].list;//������ ���� ����� �� ��� ������
					while (tmpSE != NULL)//�� ��� �� ����� ���� ����� ������ ��������
					{
						tmpCheckEvent = HeadEvent;//������ ���� ����� �� ��� ������
						while (tmpCheckEvent != NULL)//�� ��� �� ����� ���� ����� ������ ������ ��� ������ ������ �����
						{
							if (strcmp(tmpCheckEvent->title, tmpSE->title) == 0 && strcmp(tmpCheckEvent->place, tmpSE->place) == 0 && tmpCheckEvent->year == tmpSE->year)//�� ������ ��� ����
								break;//������ ������� ����� ������ ��� �� ��������-����� �� ��� ����  
							tmpCheckEvent = tmpCheckEvent->next;//����� ������ ����� ��� ��� ����� ��������
						}
						if (tmpCheckEvent == NULL)//�� ����� �� �� ������ ������ ��� ���� ������� ��� ����� ���� ����� ���
						{
							HeadEvent = AddNewEventToList(tmpSE, HeadEvent);
							countEvents++;//����� �������� ������ ������ ������ �������
						}
						tmpSE = tmpSE->next;
					}
				}
			}
			if (countEvents > maxEvents)
			{
				maxEvents = countEvents;
				strcpy(MaxClub, arr[i].club);
			}
		}
		deleteEventList(HeadEvent);//����� ����� �������� ������� ��"�
		HeadEvent = NULL;//����� ����� ������� ����
	}
	deleteNodeCheckList(HeadClub);//����� ����� ���������
	cout << "The best club is: " << MaxClub << " with " << maxEvents << " events";
}

sportsman* deleteSport(int Y, sportsman* arr, int& size)
{
	event* tmp;
	int counter = 0;//����� ������ ���� ������� ������ 
	for (int i = 0; i < size; i++)
	{
		if (arr[i].gen == 1)//�� �� ����� ����� ���� �� ������
		{
			tmp = arr[i].list;//������ ��� ����� �� ����� ������
			while (tmp != NULL)//�� ��� �� ����� ���� ������
			{
				if (tmp->year == Y)//����� �� ���� ����� ����� ����� ���� ���� �������
					break;//�� �� ��� ������� ����� ����� �����
				tmp = tmp->next;//����� ������ ��� ������
			}
			if (tmp != NULL)//�� ������ ������� ������ ��� ������� ���� ���� �������� ����� ����� ����� ������ ����� �� ������ �� ���� ����� ������ �� ��� ����� �� ���� ����� ���� ������
			{
				tmp = arr[i].list;//������ ���� ��� ����� �� ����� ������ ������
				while (tmp != NULL)//�� ��� �� ����� ����� ������ ������ �������� ����� �� �� ������� ������
				{
					arr[i].list = arr[i].list->next;//��� ������ ����� ����� ���
					delete[] tmp->title;//����� ������ ���� �� ������ ����� ������
					delete[] tmp->place;//����� ������ ���� ���� ������ ������
					tmp = arr[i].list;//����� ������ ���� ����� ���
				}
				delete arr[i].club;//����� ������ ���� ������ ���������
				arr[i].club = NULL;//����� ��� �� ����� ������ ���� ���������� ���� �����
				counter++;//����� ����� ������� ���
			}
		}
	}
	int j = 0;
	int NewSize = size - counter;//���� ����� ����
	sportsman* NewArrayNoYear = new sportsman[NewSize];//���� �������� ��� ��� ���� �� ������� ������
	for (int i = 0; i < size; i++)
	{
		if (arr[i].club != NULL && j < NewSize)//�� ����� ����� �� ������� ���� ������ ���� ��� �� ����� ���� ���� ��������� ����
		{
			NewArrayNoYear[j] = arr[i];//����� �� ������ ������� ����� ���� ����� ���� ����� ����
			j++;//����� ����� ��� ����� ����
		}

	}
	size = NewSize;
	return NewArrayNoYear;
}

void PrintByCountry(char* country, sportsman* arr, int size)
{
	int counter = 0;//���� ��� ������ ���� ������ �����
	event* temp;//������ ������ �� �������� ����� ����� ������ ������
	event* head = NULL;//����� �� ��� ������ ����� �� �������� �������� ������
	event* tempCheck;//������� ������ �� ������ �� �������� �������� ������ ��� ��� ���� ��������
	event* arrangYears;//������� ����� �� ������ ������� ��� ����
	event* NewEvent;
	event* newEvent = NULL;
	for (int i = 0; i < size; i++)//����� ������ �� �� ���������
	{
		temp = arr[i].list;//���� �� ������ ������ �� �������� ������
		tempCheck = head;//������ ����� �� ����� ����
		while (temp != NULL)//�� ��� �� ����� �� �� ������ �������� ����� ������
		{
			if (strcmp(temp->place, country) == 0)//�� ����� ������ ������� ������ �������
			{
				while (tempCheck != NULL)//�� ��� �� ����� ���� ������ ������� ����� ������ �� �� �������� ��
				{
					if (strcmp(temp->title, tempCheck->title) == 0 && strcmp(temp->place, tempCheck->place) == 0 && (temp->year == tempCheck->year))//����� ��� ������ ��� ���� ������ ����� ����� ������ ���
						break;
					tempCheck = tempCheck->next;//���� �� ������ ������ ��� ������ �� ����
				}
				if (tempCheck == NULL)//����� ������ ��������� ������ ����� ������-�� ����� ������� �� ���� ����� ������, ����� ���� ����� ������
				{
					counter++;//��������� ����� ������ ��������
					if (counter == 1)//���� �� ���� ���
					{
						NewEvent = CreateNewEvent(temp, newEvent);//���� �� ����� ��������� ���
						head = NewEvent;//����� ����� ������
					}
					if (counter > 1)//�� �� ���� ����� ��� ������
					{
						arrangYears = head;//������� ������ �� ����� ������ ����� �� �������� �������� ������
						NewEvent = CreateNewEvent(temp, newEvent);//���� �� ������ ��������� ���
						if ((arrangYears->year == NewEvent->year) || (arrangYears->year < NewEvent->year))//���� ��� ��� ��������� �� ������, ����� ��� ���� �� ������ ����� ���� �� ��� ���� ����� ������ ����
						{
							NewEvent->next = head;//���� �� ������ ���� ���� ������
							head = NewEvent;//���� �� ����� ������ ����� ����
							break;//���� ������� ������ ����� �� ������ ���
						}
						while (arrangYears->next != NULL)//�� ��� ����� ������ ����� ����� ���� ������ �� ������ ���� �� ����� ������ ����
						{
							while (NewEvent->year < arrangYears->next->year)//�� ���� �� ������ ���� ��� ����� �� ������ ��� ������ �� ������ ������ �����
							{
								arrangYears = arrangYears->next;//���� �� ����� ������ ����� ����� ���
								break;//���� ������ ��� �� ����� �� ������ ��������
							}
							NewEvent->next = arrangYears->next;//��� ����� ���� ����� ���� ����� ���, ���� �� ����� ���� ����� ��
							arrangYears->next = NewEvent;//���� �� ����� ��� ����� ����
							break;//���� ������ ����� ���
						}
						if (arrangYears->next == NULL)//�� ����� ����� ����� �� ������ �� ������ ���� ������ ����, ����� ���� ������
						{
							arrangYears->next = NewEvent;//���� �� ����� ������ ������ ������� ����� ���� ���� ����� ���� ����� ������ ����
							break;//���� ������ ����� ���
						}
					}
				}
			}
			temp = temp->next;//����� ������ ���
		}
	}
	if (head == NULL)//�� �� ����� ������ ������� ����� ������� ��������� ������ ����� ����� ������
	{
		cout << "\nThere are no events that took place in this country\n";
	}
	else
	{
		FILE* myfile = fopen("Country.txt", "w");//����� ���� ��� ������ ������
		if (myfile == NULL)//����� ��� ����� ���� �����
		{
			cout << "Error - the file with sportsman data has error !\n";//����� ����� ����� ������ �� ����
		}
		while (head != NULL)//�� ��� �� ����� ���� ������
		{
			fprintf(myfile, "%s,%i\n", head->title, head->year);//����� �� ���� �������� ����� ������
			head = head->next;//����� ����� �� ����� ���
		}
		cout << endl << counter << " events are added to 'Country.txt' FILE\n";//����� �� ���� �������� ������� ����� �����
		fclose(myfile);//����� �����
	}
}

void printMenu(sportsman* arr, int& size, const char* fname1, const char* fname2)
{
	int choice = 1;
	int numberEzer, numberEzer2;
	char stringEzer[50] = ".";
	int gen;
	do//����� ������� ����� �� ���� �� ��� ������ �� ���
	{
		cout << endl << "THIS IS YOUR MENU:\n";
		cout << "to addSportman press '1'\n";
		cout << "to addEvent press '2'\n";
		cout << "to CheckEvent press '3'\n";
		cout << "to printNoEvents press '4'\n";
		cout << "to printEvent press '5'\n";
		cout << "to compareSport press '6'\n";
		cout << "to BestClub press '7'\n";
		cout << "to deleteSport press '8'\n";
		cout << "to PrintByCountry prees '9'\n";
		cout << "to end the program press '0'\n";
		cin >> choice;//����� ������

		switch (choice)
		{
		case(1):
			arr = addSportsman(arr, size);//������ ��� ������ �������, ����� �� �������� �������
			break;
		case(2):
			cout << "Please enter id: ";//������ ��� ������ �������� �����
			cin >> numberEzer;//���� ����� ����� ����� �"� ���� ����� ��� ���� ��������
			addEvent(numberEzer, arr, size);//����� �� �������� �������
			break;
		case(3):
			cout << "Please enter an event: ";
			cin.ignore(); cin.getline(stringEzer, 50, '\n');
			CheckEvent(stringEzer, arr, size);
			break;
		case(4):
			printNoEvents(arr, size);
			break;
		case(5):
			cout << "Please enter club name:\n";
			cin.ignore(); cin.getline(stringEzer, 50, '\n');
			cout << "Please enter a year:\n";
			cin >> numberEzer;
			printEvent(stringEzer, numberEzer, arr, size);
			break;
		case(6):
			cout << "Please enter 2 ID numbers:\n";
			cin >> numberEzer;
			cin >> numberEzer2;
			compareSport(numberEzer, numberEzer2, arr, size);
			break;
		case(7):
			BestClub(arr, size);
		case(8):
			cout << "Please enter a year:\n";
			cin >> numberEzer;
			arr = deleteSport(numberEzer, arr, size);
			break;
		case(9):
			cout << "Please enter a country:\n";
			cin.ignore(); cin.getline(stringEzer, 50, '\n');
			PrintByCountry(stringEzer, arr, size);
			break;
		case(0):
			FILE* myfile1 = fopen(fname1, "w");//����� ���� ��������� ������ ������
			FILE* myfile2 = fopen(fname2, "w");//����� ���� �������� ������ ������
			if (myfile1 == NULL)//����� ��� ����� ���� �����
			{
				cout << "Error - the file with sportsman data has error !\n";//����� ����� ����� ������ �� ����
			}
			if (myfile2 == NULL)//����� ��� ����� ���� �����
			{
				cout << "Error - the file with sport events is error !\n";//����� ����� ����� ������ �� ����
			}
			event* tmp;
			fprintf(myfile1, "sportsman_id;fname;lname;club;gender(bool)\n");
			fprintf(myfile2, "format:sportsman_id,event,place,year\n");
			for (int i = 0; i < size; i++)//����� ������ �� �� ��������� �������
			{
				gen = (int)arr[i].gen;//���� ���� ������� ���� ���
				if (gen == 1)
					gen = 0;
				else gen = 1;
				fprintf(myfile1, "%d;%s;%s;%s;%d\n", arr[i].id, arr[i].Pname, arr[i].Fname, arr[i].club, gen);//����� �� ���� �������� ����� ������
				tmp = arr[i].list;
				while (tmp != NULL)
				{
					fprintf(myfile2, "%d;", arr[i].id);//����� ���� ����� ����� �� ������ ������
					fprintf(myfile2, "%s,%s%,%i\n", tmp->place, tmp->title, tmp->year);//����� �� ���� �������� ����� ������
					tmp = tmp->next;
				}
			}
			fclose(myfile1);
			fclose(myfile2);
			break;
		}
	} while (choice != 0);
	cout << "\nEND OF PROGRAM!\n";
}

void deleteArray(sportsman* arr, int size)//�������� ����� ������ ������ ����� ������
{
	event* tmp;
	for (int i = 0; i < size; i++)//���� �� �� ����� ���� ��������� ������� �� ������� �������
	{
		delete[] arr[i].club;//����� ���� ����� ������
		tmp = arr[i].list;//����� ������� ��� ������ ������ �������
		while (tmp != NULL)//�� ��� �� ����� ���� ������ �� ����� ����� ���
		{
			arr[i].list = arr[i].list->next;//����� �������� �� ������� ����� �� ������ ��� ������ ���� ������� ���� ����� �� ����� ��
			delete[] tmp->title;//����� ���� �� ������
			delete[] tmp->place;//����� ���� ����� ������
			tmp = arr[i].list;//���� ������ ���� ����� ����� ��� ������ ������
		}
	}
	delete[] arr;//����� ��� ����� �� ���������
}

void main()
{
	int size = countLines("SportsmanData.txt");//���� �� �������� ����� ������- ����� �� ���� ��������� ������� �����
	sportsman* arr = new sportsman[size];//����� ���� ������ ����� �� ���� ���������
	FromFileToStruct("SportsmanData.txt", arr, size);//����� �� ����� ��������� ������ ����� �������
	FromFileToList("EventData.txt", arr, size);//����� �� ����� �������� ������ ������ ������ �� �� �������
	printMenu(arr, size, "SportsmanData.txt", "EventData.txt");//����� ����
	void deleteArray(sportsman * arr, int size);//�������� �����
}
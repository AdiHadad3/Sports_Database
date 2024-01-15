#define _CRT_SECURE_NO_WARNINGS//נוודא כניסה בטוחה לפונקציות STR
#include <iostream>//ספריית קלט פלט
#include <cstring>//ספריית פונקציות STR
using namespace std;

#define SIZE_PNAME 10//גודל קבוע למערך שם פרטי של ספורטאי
#define SIZE_FNAME 15//גודל קבוע למערך שם משפחה של ספורטאי
#define STATIC_SIZE 100//גודל למערכי העזר הסטטיים

struct event//מבנה אירוע
{
	char* title;//שם אירוע
	char* place;//מיקום אירוע
	int year;// שנת האירוע
	event* next;// מצביע לאיבר הבא ברשימה המקושרת מסוג מבנה אירוע
};

struct sportsman//מבנה ספורטאי
{
	int id;//מספר זיהוי
	char Pname[SIZE_PNAME];//שם פרטי
	char Fname[SIZE_FNAME];//שם משפחה
	char* club;//שם מועדון הספורט
	bool gen;//לאישה 0, לגבר 1
	event* list;//מצביע לרשימה מקושרת של האירועים בהם השתתף הספורטאי
};

struct nodeCheck//מבנה מסוג רשימה מקושרת היסייע בתוכנית
{
	char* CheckStr;//התוכן שנדרש לבדוק אם כבר קיים
	nodeCheck* next;//הצבעה על איבר תוכן נבדק הבא
};

nodeCheck* AddNewClubToList(char* club, nodeCheck* HeadClublist)//פונקציה היוצרת מועדון חדש לרשימה המקושרת שהתקבלה
{
	nodeCheck* NewCheckClub = new nodeCheck;//ניצור מועדון בדיקה חדש 
	NewCheckClub->CheckStr = new char[strlen(club) + 1];//יצירת מערך דינמי בשדה מועדון הבדיקה
	strcpy(NewCheckClub->CheckStr, club);//נעתיק את תוכן המועדון הנבדק למועדון ברשימת הבדיקה 
	NewCheckClub->next = HeadClublist;//ה"נקסט" של האיבר החדש יצביע על התוכן שמצביע ראש הרשימה
	HeadClublist = NewCheckClub;//הצבעת ראש הרשימה על האיבר החדש
	return HeadClublist;
}
event* AddNewEventToList(const event* Event, event* HeadEventChecklist)//פונקציה היוצרת אירוע חדש לרשימה המקושרת שהתקבלה
{
	event* NewCheckEvent = new event;//ניצור אירוע בדיקה חדש 
	NewCheckEvent->title = new char[strlen(Event->title) + 1];//יצירת מערך דינמי בשדה שם אירוע הבדיקה
	strcpy(NewCheckEvent->title, Event->title);//נעתיק את התוכן הנוכחי לשדה השם 
	NewCheckEvent->place = new char[strlen(Event->place) + 1];//יצירת מערך דינמי בשדה שם אירוע הבדיקה
	strcpy(NewCheckEvent->place, Event->place);//נעתיק את התוכן הנוכחי לשדה השם 
	NewCheckEvent->year = Event->year;//העתקת השנה
	NewCheckEvent->next = HeadEventChecklist;//ה"נקסט" של האיבר החדש יצביע על התוכן שמצביע ראש הרשימה
	HeadEventChecklist = NewCheckEvent;//הצבעת ראש הרשימה על האיבר החדש
	return HeadEventChecklist;
}
event* CreateNewEvent(event* temp, event* NewEvent)//פונקצייה המייצרת איבר חדש מסוג אירוע וממלאה את שדותיו לפי האירוע שהתקבל
{
	NewEvent = new event;
	NewEvent->title = new char[strlen(temp->title) + 1];//נקצה מקום דינאמי לשם האירוע החדש
	strcpy(NewEvent->title, temp->title);//נעתיק את שם האירוע שהתאים בתנאים לשם האירוע החדש
	NewEvent->place = new char[strlen(temp->place) + 1];//נקצה מקום דינאמי למקום האירוע החדש
	strcpy(NewEvent->place, temp->place);//נעתיק את מקום האירוע שהתאים בתנאים לשם האירוע החדש
	NewEvent->year = temp->year;//נעתיק את שנת האירוע שהתאים בתנאים לשנת האירוע החדש
	NewEvent->next = NULL;//
	return NewEvent;//נחזיר את האירוע החדש
}
void deleteEventList(event* HeadEventChecklist)//שחרור זיכרון של רשימה מקושרת של אירועים
{
	event* tmpCheckEvent = HeadEventChecklist;//החזרת פוינטר העזר לראש הרשימה
	while (tmpCheckEvent != NULL)//מחיקת כל אירועי המועדון הנתון
	{
		HeadEventChecklist = HeadEventChecklist->next;//מעבר פוינטר ראש הרשימה אל האיבר הבא ושחרור הזכרון של האיבר הקודם לו
		delete[] tmpCheckEvent->title;
		delete[] tmpCheckEvent->place;
		delete tmpCheckEvent;
		tmpCheckEvent = HeadEventChecklist;
	}
}
void deleteNodeCheckList(nodeCheck* HeadChecklist)//שחרור זיכרון רשימה מקושרת המורכבת ממחרוזת ופוינטר לאיבר הבא
{
	nodeCheck* tmp = HeadChecklist;
	while (tmp != NULL)//שחרור זיכרון רשימת המועדונים
	{
		HeadChecklist = HeadChecklist->next;//מעבר פוינטר ראש הרשימה אל האיבר הבא ושחרור הזכרון של האיבר הקודם לו
		delete[] tmp->CheckStr;
		delete tmp;
		tmp = HeadChecklist;
	}
}

int countLines(const char* fname)//פונקציה הסופרת את מספר השורות בקובץ פרט לשורת הפורמט
{
	FILE* myfile = fopen(fname, "r");//פתיחת הקובץ המצורף לקריאה
	if (myfile == NULL)//בדיקה האם הקובץ נפתח כראוי
	{
		cout << "Error - file read error !\n";//נדפיס שגיאה במקרה בו הקובץ לא נפתח
		return 0;
	}
	int counter = 0;
	char str[STATIC_SIZE];
	while (!feof(myfile))//נספור את השורות עד הגעה לסוף הקובץ
	{
		if (fgets(str, STATIC_SIZE, myfile) != NULL)//נעבור על כל השורות בקובץ
			counter++;//נסכום את מספר השורות
	}
	fclose(myfile);//סגירת הקובץ
	return (counter - 1);//החזרת מספר השורות ללא שורת הפורמט
}

void FromFileToStruct(const char* fname, sportsman* arr, int size)//הזנת נתוני הספורטאים למערך מהקובץ המתאים
{
	FILE* myfile = fopen(fname, "r");//פתיחת הקובץ המצורף לקריאה
	if (myfile == NULL)//בדיקה האם הקובץ נפתח כראוי
	{
		cout << "Error - file read error !\n";//נדפיס שגיאה במקרה בו הקובץ לא נפתח
		return;
	}
	char tempSentence[STATIC_SIZE];
	char* tempWord;
	int counter;
	int intTempWpword;
	bool ManOrWoman = 0;//מקבל מהקובץ ערך שלם שיומר לערך בוליאני
	fgets(tempSentence, STATIC_SIZE, myfile);//נעבור על שורת הפורמט כדי לעבור לתוכן הרלוונטי
	for (int i = 0; i < size; i++)//לולאה העוברת על כל איברי המערך שהתקבל ומזינה לתוכם את התוכן המתאים עד הגעה ל"סייז"- מספר הספורטאים בקובץ
	{
		if (fgets(tempSentence, STATIC_SIZE, myfile) != NULL)//נעבור על כל שורות הקובץ
		{
			tempWord = strtok(tempSentence, "\n;");//הפונקציה תחזיר מצביע לאסימון הראשון
			counter = 0;//הגדרת האסימון הנוכחי הראשון
			while (tempWord != NULL)//כל עוד האסימון הבא קיים ניכנס ללואה
			{
				switch (counter)//פונקציה המתאימה את ערך האסימון
				{
				case(0): arr[i].id = atoi(tempWord);//המרת תוכן האסימון הראשון לשדה מספר הזיהוי של הספורטאי
					break;
				case(1):strcpy(arr[i].Pname, tempWord);//נוכחות באסימון השני והכנסת תוכנו לשדה השם הפרטי
					break;
				case(2):strcpy(arr[i].Fname, tempWord);//נוכחות באסימון השלישי והכנסת תוכנו לשדה שם המשפחה
					break;
				case(3): arr[i].club = new char[strlen(tempWord) + 1];//הכרזה על מערך דינאמי חדש
					strcpy(arr[i].club, tempWord);//העתקת תוכן האסימון למערך הדינאמי
					break;
				case(4): intTempWpword = atoi(tempWord);//המרת תוכן האסימון לתוכן מספרי שלם
					if (intTempWpword == 1)//אם האסימון הוא 1 בתוכן הוא גבר
						arr[i].gen = 0;//נגדיר כי המין הוא אפס, הפיכת המין מהקובץ למערך
					else arr[i].gen = 1;//ולהיפך, אם התוכן הוא 0 כלומר בקובץ אישה, כעת 0 מסמל גבר
				}
				counter++;//אינדיקציה למעבר לאסימון הבא
				tempWord = strtok(NULL, "\n;");//נתקדם לאסימון הבא
			}
			arr[i].list = NULL;//נאתחל את המצביע לרשימה המקושרת של אירועי הספורטאי בכתובת האפס
		}
	}
	fclose(myfile);
}

void FromFileToList(const char* fname, sportsman* arr, int size)//איתחול הרשימה המקושרת בהתאם לשחקן המתאים בעזרת קריאה מהקובץ
{
	FILE* myfile = fopen(fname, "r");//פתיחת הקובץ המצורף לקריאה
	if (myfile == NULL)//בדיקה האם הקובץ נפתח כראוי
	{
		cout << "Error - file read error !\n";//נדפיס שגיאה במקרה בו הקובץ לא נפתח
		return;
	}
	char tempSentence[STATIC_SIZE];
	char* tempWord;
	int counter;
	int idSportMan = 0;
	event* newEvent;
	fgets(tempSentence, STATIC_SIZE, myfile);//נתעלם משורת הפורמט
	while (fgets(tempSentence, STATIC_SIZE, myfile) != NULL)//כל עוד לא הגענו לסוף הקובץ
	{
		newEvent = new event;
		tempWord = strtok(tempSentence, "\n,");//הפונקציה תחזיר מצביע לאסימון הראשון
		counter = 0;
		while (tempWord != NULL)//כל עוד האסימון הבא קיים ניכנס ללולאה
		{
			switch (counter)//פונקציה המתאימה את ערך האסימון למקרה
			{
			case(0):idSportMan = atoi(tempWord);//המרת תוכן האסימון הראשון לשדה מספר הזיהוי של הספורטאי
				break;
			case(1): newEvent->title = new char[strlen(tempWord) + 1];//הקצאת מקום למערך הדינאמי של שם האירוע
				strcpy(newEvent->title, tempWord);//העתקת תוכן האסימון השני למקום האירוע
				break;
			case(2):  newEvent->place = new char[strlen(tempWord) + 1];//הקצאת מקום למערך הדינאמי של מקום האירוע
				strcpy(newEvent->place, tempWord);//העתקת תוכן האסימון השלישי למקום האירוע
				break;
			case(3): newEvent->year = atoi(tempWord);//המרת תוכן האסימון הרביעי והכנסתו לשדה שנת האירוע
			}
			counter++;//
			tempWord = strtok(NULL, "\n,");//נקדם את האסימון
		}
		newEvent->next = NULL;//נגדיר שהאירוע הבא מצביע לכתובת האפס
		for (int i = 0; i < size; i++)//לולאה העוברת על כל אברי מערך הספורטאים
		{
			if (arr[i].id == idSportMan)//אם נמצאה התאמה בין המספר המזהה של הספורטאי לתוכן הראשוני של הקובץ נצרף את האירוע החדש לרשימה המקושרת שבמבנה הספורטאי
			{
				newEvent->next = arr[i].list;//נקסט של האירוע החדש יצביע על התוכן אליו "ליסט" מצביע
				arr[i].list = newEvent;//נעביר את "ליסט" להצביע על האיבר המבני החדש מסוג אירוע
				break;//נצא מהלולאה כאשר הגענו למשתמש מתאים לאירוע
			}
		}
	}
	fclose(myfile);//סגירת הקובץ
}

sportsman* addSportsman(sportsman* arr, int& size)//הוספת ספורטאי חדש
{
	char str[STATIC_SIZE];//מערך עזר לקליטת הנתונים
	int IdCheck;//מספר זיהוי שיוזן ע"י המשתמש לבדיקה אם קיים כבר
	cout << "Please enter your family name: ";
	cin.ignore(); cin.getline(str, SIZE_FNAME);
	cout << "Please enter your id: ";
	cin >> IdCheck;
	for (int i = 0; i < size; i++)//לולאה הבודקת האם שם המשפחה שקיבלנו תואם לאחד משמות המשפחה שמוזנים כבר
	{
		if (strcmp(str, arr[i].Fname) == 0 && arr[i].id == IdCheck)//במידה וקיים במערך ספורטאים שם משפחה זהה לשם שהוזן-הפונקציה תחזיר את המערך ללא שינוי
		{
			cout << "\nThe new athlete is already exists...\n";
			return arr;//נחזיר את המערך הקודם שלא השתנה
		}
	}
	sportsman* newSportsManArray = new sportsman[size + 1];//יצירת מערך ספורטאים חדש הגדול ב1 לשם הכנסת מבנה הספורטאי החדש
	for (int j = 0; j < size; j++)//הזנת כל נתוני המערך הישן למערך החדש
	{
		newSportsManArray[j] = arr[j];
	}
	delete[] arr;//מחיקת מערך הספורטאים הקודם
	newSportsManArray[size].id = IdCheck;//הזנת התוכן לשדה המתאים באיבר החדש במערך
	cout << "Please enter your private name: ";
	cin.ignore(); cin.getline(newSportsManArray[size].Pname, SIZE_PNAME);
	strcpy(newSportsManArray[size].Fname, str);//העתקת המערך שכבר נקלט לשדה שם המשפחה
	cout << "Please enter your sport club: ";
	cin.getline(str, 100);
	newSportsManArray[size].club = new char[strlen(str) + 1];//יצירת מערך דינמי חדש לשדה המועדון
	strcpy(newSportsManArray[size].club, str);
	cout << "Please enter your gender (for woman-press '1', for man-press '0'): ";
	cin >> newSportsManArray[size].gen;
	newSportsManArray[size].list = NULL;//איתחול השדה המצביע לרשימה מקושרת בכתובת האפס
	size++;//הגדלת גודל המערך ב1
	cout << "The new athlete added!\n";
	return newSportsManArray;//הפונקציה תחזיר את המערך החדש עם השינויים
}

bool addEvent(int id, sportsman* arr, int size)
{
	event* newEvent = new event;//הכרזה על משתנה אירוע חדש
	char str[STATIC_SIZE];//מערך עזר סטטי
	cout << "Please enter event title: ";
	cin.ignore(); cin.getline(str, STATIC_SIZE);//הזנת שם האירוע
	newEvent->title = new char[strlen(str) + 1];//הקצאת מקום למערך דינאמי של שם האירוע
	strcpy(newEvent->title, str);//העתקת שם האירוע למערך הדינאמי
	cout << "Please enter event place: ";
	cin.getline(str, STATIC_SIZE);//הזנת מקום האירוע
	newEvent->place = new char[strlen(str) + 1];//הקצאת מקום למערך דינאמי של מקום האירוע
	strcpy(newEvent->place, str);//העתקת מקום האירוע למערך הדינאמי
	cout << "Please enter event year: ";
	cin >> newEvent->year;//הזנת מקום העירוע
	newEvent->next = NULL;//האיבר האחרון ברשימה יצביע לכתובת האפס
	event* tmp;//פוינטר עזר היצביע על אירוע
	for (int i = 0; i < size; i++)//מעבר על כל איברי מערך מבני הספורטאים
	{
		if (arr[i].id == id)//בדיקת הגעה למספר זיהוי תואם למספר שהוזן לפונקציה
		{
			tmp = arr[i].list;//הגדרת פוינטר עזר היצביע לאיבר הראשון ברשימה המקושרת
			if (tmp == NULL)//אם אין אירועים לספורטאי נוסיף את האירוע לרשימה המקושרת ונחזיר אמת
			{
				cout << "\nThe new event is added!\n";
				arr[i].list = newEvent;//נקשר את האירוע החדש לספורטאי
				cout << arr[i].list->title;
				return true;
			}
			while (true)//מעבר על כל איברי הרשימה והגעה למצב מתאים
			{
				if (strcmp(newEvent->title, tmp->title) == 0 && strcmp(newEvent->place, tmp->place) == 0 && newEvent->year == tmp->year)//בדיקת זהות מלאה בין שדות האירוע שהוזן לשדות האירוע הקיים ברשימה המקושרת של האירועים של הספורטאי
				{
					cout << "\nThe event is already exists...\n";
					return false;//אם נמצאה זהות מלאה בין האירועים נחזיר שקר
					break;
				}
				else//אם יש לפחות שדה אחד שונה בין האירועים
				{
					if (tmp->next != NULL)//אם לא הגענו לאיבר האחרון ברשימה המקושרת
						tmp = tmp->next;//נעביר את המצביע הנוכחי לאיבר אחריו
					else break;
				}
			}
			cout << "\nThe new event is added!\n";
			tmp->next = newEvent;//אם עברת על כל הרשימה ולא נמצא שיוויון תוסיף את האיבר לרשימה
			return true;
		}
	}
	cout << "\nThe id number does not apply any athlete...\n";
	return false;
}

void CheckEvent(char* E, sportsman* arr, int size)//פונקציה המדפיסה את שמות הספורטאים שהשתתפו באירוע שקיבלה
{
	event* tmp;//הכרזת פוינטר עזר על אירוע חדש
	for (int i = 0; i < size; i++)//לולאה העוברת על כל הספורטאים ובודקת האם האירוע נמצא ברשימה המקושרת של הספורטאי
	{
		tmp = arr[i].list;//פוינטר עזר מצביע על האיבר הראשון ברשימה
		while (tmp != NULL)//כל עוד לא הגענו לסוף הרשימה
		{
			if (strcmp(tmp->title, E) == 0)//במידה והאירוע תואם לשם האירוע המופיע באיבר הרשימה הנוכחי נדפיס את שמו המלא של הספורטאי הנ"ל
			{
				cout << arr[i].Pname << " " << arr[i].Fname << endl;
				break;
			}
			tmp = tmp->next;//קידום הפוינטר לאירוע הבא של הספורטאי
		}
	}
}

void printNoEvents(sportsman* arr, int size)
{
	nodeCheck* HeadClublist = NULL;//הכרזת פוינטר המצביע על האיבר הראשון ברשימת בדיקת המועדון, בהתחלה יצביע על כתובת האפס
	nodeCheck* tmp;//פוינטר עזר
	for (int i = 0; i < size; i++)//לולאה התעבור על כל מערך הספורטאים ותבדוק האם הספורטאי לא השתתף בשום אירוע, במצב כזה תדפיס את המועדון שלו בלי כפילויות בעזרת רשימה מקושרת
	{
		tmp = HeadClublist;//פוינטר העזר יצביע על האיבר הראשון ברשימת המועדונים לבדיקה
		if (arr[i].list == NULL)//אם לא קיימים אירועים ברשימה של הספורטאי נבדוק האם ברשימה המקושרת החדשה כבר קיים מועדון שהודפס מהסיבה שיש לו שחקן אחד לפחות בלי אירועים ברשימתו
		{
			while (tmp != NULL)//כל עוד לא הגענו לסוף הרשימה
			{
				if (strcmp(arr[i].club, tmp->CheckStr) == 0)//אם המועדון שנמצא כבר קיים ברשימה נצא מהלולאה 
					break;
				tmp = tmp->next;//נקדם את הפוינטר על מנת לבדוק אם יש שיוויון למועדון הבא
			}
			if (tmp == NULL)//אם הפוינטר הגיע לסוף הרשימה זה מעיד לנו על חוסר שיוויון למועדונים הקיימים בעקבות השלבים הקודמים
			{
				AddNewClubToList(arr[i].club, HeadClublist);
				cout << arr[i].club << endl;//הדפסת שם המועדון הרלוונטי
			}
		}//מעבר לספורטאי הבא לבדיקה
	}
}

void printEvent(char* C, int Y, sportsman* arr, int size)
{
	event* tmp;//פוינטר היעבור על האירועים וימצא אירוע מתאים לשנה שקיבלנו
	event* headEventsListCheck = NULL;//פוינטר המצביע על האיבר הראשון של אירועי הבדיקה-כל אירוע שעמד בתנאים ייכנס לרשימה במידה ולא קיים בה עדיין, ואם כך גם יודפס
	event* tmpCheck;//פוינטר היעבור על הרשימה המקושרת של האירועים שעמדו בתנאים לעיל
	for (int i = 0; i < size; i++)//לולאה העוברת על איברי מערך הספורטאים
	{
		tmp = arr[i].list;//פוינטר מצביע על האיבר הראשון ברשימת אירועי הספורטאי
		tmpCheck = headEventsListCheck;
		while (tmp != NULL)//כל עוד לא הגענו לסוף רשימת אירועי הספורטאי נבדוק בשדה המועדון וגם באחד אירועיו שיוויון לתכנים שהתקבלו בהתאם
		{
			if (strcmp(arr[i].club, C) == 0 && tmp->year == Y)//אם הגענו לשיוויון בשני הנתונים נבדוק אם אירוע זה עדיין לא קיים ברשימה המקושרת של בדיקת האירועים
			{
				while (tmpCheck != NULL)//כל עוד לא הגענו לסוף רשימת אירועי הבדיקה נבדוק אם האירוע שקיבלה הפונקציה כבר הודפס
				{
					if (strcmp(tmpCheck->title, tmp->title) == 0 && strcmp(tmpCheck->place, tmp->place) == 0 && tmpCheck->year == tmp->year)//אם יש שיוויון מלא האירוע הנוכחי שנבדק לאחד האירועים שכבר בתוך הרשימה והודפסו כבר
						break;//נצא מהלולאה
					tmpCheck = tmpCheck->next;//קידום פוינטר העזר לבדיקת האירוע הבא 
				}
				if (tmpCheck == NULL)//אם הגענו לסוף רשימת הבדיקה
				{
					headEventsListCheck = AddNewEventToList(tmp, headEventsListCheck);//נוסיף את האירוע לרשימה המקושרת הבודקת נוכחות אירועים
					cout << tmp->title << endl;//הדפסת שם האירוע הרלוונטי
				}
			}tmp = tmp->next;//נתקדם לאירוע הבא של הספורטאי	
		}
	}
	if (headEventsListCheck == NULL)//אם אין לא נוספו לרשימה המקושרת כלל אירועים העומדים בשני התנאים נחזיר הודעה מתאימה
		cout << "There are no suitable events";
	else deleteEventList(headEventsListCheck);//אם נוצרו אירועים חדשים נשחרר את הזיכרון שלהם


}

void compareSport(int id1, int id2, sportsman* arr, int size)
{
	int i = 0;
	int j = 0;
	for (; i < size; i++)//נחפש את המקום בו הוזן מספר הזיהוי של הספורטאי הראשון
	{
		if (arr[i].id == id1)//נמצא את מספר הזיהוי המתאים
			break;//ניצא
	}
	for (; j < size; j++)//נחפש את המקום בו הוזן מספר הזיהוי של הספורטאי השני
	{
		if (arr[j].id == id2)//נמצא את מספר הזיהוי המתאים
			break;//ניצא
	}
	if (i == size) cout << "\nThe first id is not identified\n";//מספר זיהוי ראשון לא זוהה
	if (j == size) cout << "\nThe second id is not identified\n";//מספר זיהוי שני לא זוהה
	int counter = 0;//משתנה הבודק האם יש אירועים מתאימים
	event* temp1 = arr[i].list;//נגדיר מצביע חדש שיצביע על האירוע הראשון של הספורטאי הראשון
	event* temp2;//נגדיר מצביע חדש שיצביע על משתנה מסוג אירוע
	if (i != size && j != size)//אם שני מספרי הזהוי מתאימים
	{
		while (temp1 != NULL)//כל עוד לא הגענו לאירוע האחרון של הספונטאי הראשון וגם כאשר שני מספרי הזהות זוהו
		{
			temp2 = arr[j].list;//מצביע על האירוע הראשון של המשתנה השני
			while (temp2 != NULL && temp1 != NULL)//נצבע לולאה כל עוד לא הגענו למקום האחרון של הספוטאי השני
			{
				if ((strcmp(temp1->title, temp2->title) != 0) || (temp1->year != temp2->year))//אם שם ושנת אירוע אצל שני הספורטאים שונים
				{
					temp2 = temp2->next;//נקדם את המצביע לאירוע השני של הספורטאי השני
				}
				else//אם שם אירוע ושנת אירוע אצל שני הספורטאים שווים
				{
					cout << "\nBoth athletes participated in '" << temp1->title << "' event at " << temp1->year;//נדפיס את שם האירוע והשנה בה הוא חל
					counter++;//מוסיף למשתנה אחד לפי מספר האירועים המשותפים
					temp1 = temp1->next;//נתקדם לאירוע הבא של הספורטאי הראשון כדי לבדוק אם גם הוא מתאים לספורטאי השני
				}
			}
			if (temp1 != NULL)
				temp1 = temp1->next;//כאשר לא הייתה התאמה בין האירוע של הספורטאי הראשוו לכל האירועים של הספורטאי השני, נתקדם לאירוע השני של הספורטאי הראשון ונמשיך לבדוק אותו
		}
		if (counter == 0)//במידה ואין אירועים מתאימים נדפיס זאת
			cout << "\nNo matching events\n";
	}
}

void BestClub(sportsman* arr, int size)//פונקציה המוצאת את המועדון עם הכי הרבה אירועים שהשחקנים השתתפו בהם בלי כפילויות של אירועים זהים לחלוטין
{
	int countEvents = 0;//סכימת האירועים למועדון הספציפי
	int maxEvents = 0;//מספר אירועים מקסימלי מבין כל המועדונים
	char* MaxClub = arr[0].club;//שם המועדון עם מקסימום אירועים נוכחי, נאתחל בכתובת מוכרת
	event* tmpSE;//פוינטר עזר למעבר על אירועי הספורטאי
	event* HeadEvent = NULL;//מצביע לראש רשימת בדיקת נוכחות אירוע
	event* tmpCheckEvent;
	nodeCheck* HeadClub = NULL;//מצביע לראש רשימת בדיקת נוכחות מועדון
	nodeCheck* tmpCheckClub;
	for (int i = 0; i < size; i++)//לולאה העוברת על כל איברי מערך הספורטאים ולכל מועדון סופרת את סך אירועיו ללא כפילויות
	{
		tmpCheckClub = HeadClub;//בדיקה האם היה יחס קודם למועדון הנוכחי
		while (tmpCheckClub != NULL)//כל עוד לא העגנו לסוף רשימת אירועי הבדיקה נמשיך לבדוק האם אירוע זה כבר קיים
		{
			if (strcmp(arr[i].club, tmpCheckClub->CheckStr) == 0)//אם נמצא שיוויון בין המועדון הנוכחי לבין מועדון שנמצא ברשימת הבדיקה נצא מהלולאה
				break;//אין צורך להתייחס למועדון זה, אירועיו כבר נבדקו
			tmpCheckClub = tmpCheckClub->next;//נבדוק את האיברים הבאים
		}
		if (tmpCheckClub == NULL)//אם כבר נבדקו כל האיברים ולא נמצא תואם
		{
			HeadClub = AddNewClubToList(arr[i].club, HeadClub);//נוסיף את אירוע זה לרשימה עם כל נתוניו
			countEvents = 0;//נתחיל ספירת אירועים מחדש לכל מועדון 
			for (int j = i; j < size; j++)//לולאה העוברת על כל הספורטאים לאחר הספורטאי הנוכחי 
			{
				if (strcmp(arr[i].club, arr[j].club) == 0)//כל עוד ישנה זהות בין המועדונים נכניס את כל האירועים לרשימה מתאימה
				{
					tmpSE = arr[j].list;//פוינטר העזר מצביע על ראש הרשימה
					while (tmpSE != NULL)//כל עוד לא הגענו לסוף רשימת אירועי הספורטאי
					{
						tmpCheckEvent = HeadEvent;//פוינטר העזר מצביע על ראש הרשימה
						while (tmpCheckEvent != NULL)//כל עוד לא הגענו לסוף רשימת אירועי הבדיקה מול האירוע הנוכחי נמשיך
						{
							if (strcmp(tmpCheckEvent->title, tmpSE->title) == 0 && strcmp(tmpCheckEvent->place, tmpSE->place) == 0 && tmpCheckEvent->year == tmpSE->year)//אם האירוע כבר קיים
								break;//ביציאה מהלולאה נמשיך לאירוע הבא של הספורטאי-לבדוק אם הוא קיים  
							tmpCheckEvent = tmpCheckEvent->next;//נמשיך לאירוע בדיקה הבא מול אירוע הספורטאי
						}
						if (tmpCheckEvent == NULL)//אם עברנו על כל אירועי הבדיקה ולא נמצא שיוויון מלא ניצור מבנה אירוע חדש
						{
							HeadEvent = AddNewEventToList(tmpSE, HeadEvent);
							countEvents++;//סכימת האירועים שנוספו לרשימת אירועי המועדון
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
		deleteEventList(HeadEvent);//מחיקת רשימת האירועים למועדון הנ"ל
		HeadEvent = NULL;//אתחול רשימת אירועים חדשה
	}
	deleteNodeCheckList(HeadClub);//מחיקת רשימת המועדונים
	cout << "The best club is: " << MaxClub << " with " << maxEvents << " events";
}

sportsman* deleteSport(int Y, sportsman* arr, int& size)
{
	event* tmp;
	int counter = 0;//יסייע בספירת כמות האיברים שמחקנו 
	for (int i = 0; i < size; i++)
	{
		if (arr[i].gen == 1)//רק אם הגענו לאישה נבצע את המחיקה
		{
			tmp = arr[i].list;//פוינטר עזר יצביע על האיבר הראשון
			while (tmp != NULL)//כל עוד לא הגענו לסוף הרשימה
			{
				if (tmp->year == Y)//בדיקה אם ישנו אירוע כלשהו ששנתו שווה לשנה שהתקבלה
					break;//אם כן נצא מהלולאת בדיקה למטרת מחיקה
				tmp = tmp->next;//קידום לאירוע הבא שייבדק
			}
			if (tmp != NULL)//אם היציאה מהלולאה כתוצאה מכך שפוינטר העזר הגיע לשיוויון בערכי השנים נשחרר זיכרון לאיבר זה ונספור את כמות הפעים שמחקנו על מנת לקבוע את גודל המערך החדש שניצור
			{
				tmp = arr[i].list;//פוינטר העזר שוב יצביע על האיבר הראשון ברשימה
				while (tmp != NULL)//כל עוד לא הגענו לאיבר האחרון ברשימת האירועים נשחרר את כל הזיכרון הדינמי
				{
					arr[i].list = arr[i].list->next;//ראש הרשימה יצביע לאיבר הבא
					delete[] tmp->title;//שחרור זיכרון לשדה שם האירוע באיבר הנוכחי
					delete[] tmp->place;//שחרור זיכרון לשדה מקום האירוע הנוכחי
					tmp = arr[i].list;//העברת פוינטר העזר לאיבר הבא
				}
				delete arr[i].club;//שחרור זיכרון לשדה מועדון הספורטאית
				arr[i].club = NULL;//נגדיר שדה זה מצביע לכתובת האפס כאינדיקציה לשדה שנמחק
				counter++;//נספור מחיקה כשבוצעה כזו
			}
		}
	}
	int j = 0;
	int NewSize = size - counter;//גודל המערך החדש
	sportsman* NewArrayNoYear = new sportsman[NewSize];//מערך ספורטאים חדש שלא יכיל את האיברים שנמחקו
	for (int i = 0; i < size; i++)
	{
		if (arr[i].club != NULL && j < NewSize)//אם הגענו לאיבר בו המועדון שונה מכתובת האפס וגם לא הגענו לסוף מערך הספורטאים החדש
		{
			NewArrayNoYear[j] = arr[i];//נעתיק את הכתובת שמופיעה באיבר הישן לאיבר החדש במערך החדש
			j++;//נעבור לאיבר הבא במערך החדש
		}

	}
	size = NewSize;
	return NewArrayNoYear;
}

void PrintByCountry(char* country, sportsman* arr, int size)
{
	int counter = 0;//בודק כמה איברים צריך להדפיס לקובץ
	event* temp;//פוינטר שיעבור על האירועים וימצא אירוע המתאים למדינה
	event* head = NULL;//יצביע על ראש הרשימה החדשה של האירועים המתאימים לתנאים
	event* tempCheck;//פויינטר שיעבור על הרשימה של האירועים המתאימים לתנאים כדי שלא יהיו כפילויות
	event* arrangYears;//פויינטר שיסדר את הרשימה המקושרת לפי שנים
	event* NewEvent;
	event* newEvent = NULL;
	for (int i = 0; i < size; i++)//לולאה שעובדת על כל הספורטאים
	{
		temp = arr[i].list;//מקבל את האירוע הראשון של הספורטאי הראשון
		tempCheck = head;//בהתחלה מצביע על כתובת האפס
		while (temp != NULL)//כל עוד לא עברנו על כל אירועי הספורטאי נמשיך בלולאה
		{
			if (strcmp(temp->place, country) == 0)//אם הגענו לאירוע שהתקיים במדינה המתאימה
			{
				while (tempCheck != NULL)//כל עוד לא הגענו לסוף הרשימה המקושרת החדשה ובדקנו את כל האירועים בה
				{
					if (strcmp(temp->title, tempCheck->title) == 0 && strcmp(temp->place, tempCheck->place) == 0 && (temp->year == tempCheck->year))//נבדוק האם האירוע כבר קיים ברשימה החדשה באיבר הראשון שלה
						break;
					tempCheck = tempCheck->next;//נקדם את הבדיקה לאירוע הבא ונבדוק גם אותו
				}
				if (tempCheck == NULL)//במידה ויצאנו מהפונקציה והגענו לאיבר האחרון-מה שאומר שהאירוע לא קיים עדיין ברשימה, נוסיף אותו במקום המתאים
				{
					counter++;//אינדיקציה לכמות איברים שהתווספו
					if (counter == 1)//כאשר יש איבר אחד
					{
						NewEvent = CreateNewEvent(temp, newEvent);//נמלא את השדות בפונקציית עזר
						head = NewEvent;//הוספת האיבר הראשון
					}
					if (counter > 1)//אם יש יותר מאיבר אחד ברשימה
					{
						arrangYears = head;//פויינטר המצביע על תחילת הרשימה החדשה של האירועים המתאימים לתנאים
						NewEvent = CreateNewEvent(temp, newEvent);//נמלא את הפרטים בפונקציית עזר
						if ((arrangYears->year == NewEvent->year) || (arrangYears->year < NewEvent->year))//נסדר לפי סדר כרונולוגי את הרשימה, נבדוק האם השנה של האירוע הקיים שווה או קטן לשנה החדשה באירוע החדש
						{
							NewEvent->next = head;//נקשר את האירוע החדש לראש הרשימה
							head = NewEvent;//נקשר את האיבר הראשוו לאיבר החדש
							break;//ניצא מהלולאה ונעבור לבדוק את האירוע הבא
						}
						while (arrangYears->next != NULL)//כל עוד האיבר שאחריו האיבר שבודק היכן להכניס את האירוע החדש לא מצביע לכתובת האפס
						{
							while (NewEvent->year < arrangYears->next->year)//אם השנה של האירוע החדש קטן מהשנה של האירוע הבא מהאיבר בו בודקים ברשימה ניכנס
							{
								arrangYears = arrangYears->next;//נקדם את האיבר ברשימה החדשה לאיבר הבא
								break;//ניצא ונבדוק שוב את התנאי של הלולאה החיצונית
							}
							NewEvent->next = arrangYears->next;//שנת האיבר החדש גדולה משנת האיבר הבא, נקשר את האיבר החדש לאיבר זה
							arrangYears->next = NewEvent;//נקשר את האיבר הבא לאיבר החדש
							break;//ניצא ונבדוק אירוע חדש
						}
						if (arrangYears->next == NULL)//אם האיבר שאחרי האיבר בו בודקים את הרשימה מגיע לכתובת האפס, הגענו לסוף הרשימה
						{
							arrangYears->next = NewEvent;//נקשר את האיבר האחרון הרשימה הנוכחית לאיבר החדש כאשר האיבר החדש מצביע לכתובת האפס
							break;//ניצא ונבדוק אירוע חדש
						}
					}
				}
			}
			temp = temp->next;//נתקדם לאירוע הבא
		}
	}
	if (head == NULL)//אם לא נוספו לרשימה המקושרת החדשה אירועים המתקיימים במדינה נחזיר הודעה מתאימה
	{
		cout << "\nThere are no events that took place in this country\n";
	}
	else
	{
		FILE* myfile = fopen("Country.txt", "w");//פתיחת קובץ חדש המצורף לכתיבה
		if (myfile == NULL)//בדיקה האם הקובץ נפתח כראוי
		{
			cout << "Error - the file with sportsman data has error !\n";//נדפיס שגיאה במקרה שהקובץ לא נפתח
		}
		while (head != NULL)//כל עוד לא הגענו לסוף הרשימה
		{
			fprintf(myfile, "%s,%i\n", head->title, head->year);//נעתיק את תוכן האירועים לקובץ המתאים
			head = head->next;//נתקדם לכתוב את האיבר הבא
		}
		cout << endl << counter << " events are added to 'Country.txt' FILE\n";//נעדכן את מספר האירועים שהוספנו לקובץ הנתון
		fclose(myfile);//סגירת הקובץ
	}
}

void printMenu(sportsman* arr, int& size, const char* fname1, const char* fname2)
{
	int choice = 1;
	int numberEzer, numberEzer2;
	char stringEzer[50] = ".";
	int gen;
	do//תפריט התוכנית שחוזר על עצמו עד שלא לוחצים על אפס
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
		cin >> choice;//בחירת המשתמש

		switch (choice)
		{
		case(1):
			arr = addSportsman(arr, size);//המשתמש בחר להוסיף ספורטאי, נפעיל את הפונקציה המתאימה
			break;
		case(2):
			cout << "Please enter id: ";//המשתמש בחר להוסיף לספורטאי אירוע
			cin >> numberEzer;//נבקש שיזין לאיזה משתמש ע"י מספר זיהוי אשר נשלח לפונקציה
			addEvent(numberEzer, arr, size);//נפעיל את הפונקציה המתאימה
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
			FILE* myfile1 = fopen(fname1, "w");//פתיחת קובץ הספורטאים המצורף לכתיבה
			FILE* myfile2 = fopen(fname2, "w");//פתיחת קובץ האירועים המצורף לכתיבה
			if (myfile1 == NULL)//בדיקה האם הקובץ נפתח כראוי
			{
				cout << "Error - the file with sportsman data has error !\n";//נדפיס שגיאה במקרה שהקובץ לא נפתח
			}
			if (myfile2 == NULL)//בדיקה האם הקובץ נפתח כראוי
			{
				cout << "Error - the file with sport events is error !\n";//נדפיס שגיאה במקרה שהקובץ לא נפתח
			}
			event* tmp;
			fprintf(myfile1, "sportsman_id;fname;lname;club;gender(bool)\n");
			fprintf(myfile2, "format:sportsman_id,event,place,year\n");
			for (int i = 0; i < size; i++)//לולאה שעוברת על כל הספורטאים הקיימים
			{
				gen = (int)arr[i].gen;//המרה מערך בוליאני לערך שלם
				if (gen == 1)
					gen = 0;
				else gen = 1;
				fprintf(myfile1, "%d;%s;%s;%s;%d\n", arr[i].id, arr[i].Pname, arr[i].Fname, arr[i].club, gen);//נעתיק את תוכן המשתמשים לקובץ המתאים
				tmp = arr[i].list;
				while (tmp != NULL)
				{
					fprintf(myfile2, "%d;", arr[i].id);//כתיבת מספר זיהוי בקובץ של אירועי הספורט
					fprintf(myfile2, "%s,%s%,%i\n", tmp->place, tmp->title, tmp->year);//נעתיק את תוכן האירועים לקובץ המתאים
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

void deleteArray(sportsman* arr, int size)//פונקציית שחרור הזכרון הדינמי הנותר בתכנית
{
	event* tmp;
	for (int i = 0; i < size; i++)//מעבר על כל איברי מערך הספורטאים ושיחרור כל הזיכרון הדינאמי
	{
		delete[] arr[i].club;//מחיקת תוכן דינמי מועדון
		tmp = arr[i].list;//שימוש בפוינטר עזר למחיקת הרשימה המקושרת
		while (tmp != NULL)//כל עוד לא הגענו לסוף הרשימה או שאינה רשימה כלל
		{
			arr[i].list = arr[i].list->next;//מצביע הספורטאי על אירועיו יצביע על האירוע הבא ברשימה בעוד שפוינטר העזר מצביע על הקודם לו
			delete[] tmp->title;//מחיקת תוכן שם האירוע
			delete[] tmp->place;//מחיקת תוכן מיקום האירוע
			tmp = arr[i].list;//מעבר פוינטר העזר לאיבר שכרגע הוא הראשון ברשימה
		}
	}
	delete[] arr;//מחיקת כלל המערך של הספורטאים
}

void main()
{
	int size = countLines("SportsmanData.txt");//נבצע את פונקציית ספירת השורות- סופרת את מספר הספורטאים הקיימים בקובץ
	sportsman* arr = new sportsman[size];//נגדיר מערך דינאמי בגודל של מספר הספורטאים
	FromFileToStruct("SportsmanData.txt", arr, size);//נעביר את נתוני הספורטאים מהקובץ למערך הדינאמי
	FromFileToList("EventData.txt", arr, size);//נעביר את נתוני האירועים מהקובץ לרשימה מקושרת של כל ספורטאי
	printMenu(arr, size, "SportsmanData.txt", "EventData.txt");//תפריט ראשי
	void deleteArray(sportsman * arr, int size);//פונקציית מחיקה
}
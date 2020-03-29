#include <iostream>
#include <string.h>

using namespace std;

enum HaabMonth{pop, no, zip, zotz, tzec, xul, yoxkin, mol, chen, yax, zac, ceh, mac, kankin, muan, pax, koyab, cumhu, uayet};

struct Haab{
	int day;
	HaabMonth month;
	int year;
};

enum TzolkinDay{imix, ik, akbal, kan, chicchan, cimi, manik, lamat, muluk, ok, chuen, eb, ben, ix, mem, cib, caban, eznab, canac, ahau};

struct Tzolkin{
	int num;
	TzolkinDay day;
	int year;
};

int getMonthNum(char *month)
{
	if(strcmp(month, "pop")==0)
		return 0;
	else if(strcmp(month, "no")==0)
		return 1;
	else if(strcmp(month, "zip")==0)
		return 2;
	else if(strcmp(month, "zotz")==0)
		return 3;
	else if(strcmp(month, "tzec")==0)
		return 4;
	else if(strcmp(month, "xul")==0)
		return 5;
	else if(strcmp(month, "yoxkin")==0)
		return 6;
	else if(strcmp(month, "mol")==0)
		return 7;
	else if(strcmp(month, "chen")==0)
		return 8;
	else if(strcmp(month, "yax")==0)
		return 9;
	else if(strcmp(month, "zac")==0)
		return 10;
	else if(strcmp(month, "ceh")==0)
		return 11;
	else if(strcmp(month, "mac")==0)
		return 12;
	else if(strcmp(month, "kankin")==0)
		return 13;
	else if(strcmp(month, "muan")==0)
		return 14;
	else if(strcmp(month, "pax")==0)
		return 15;
	else if(strcmp(month, "koyab")==0)
		return 16;
	else if(strcmp(month, "cumhu")==0)
		return 17;
	else
		return 18;
}

void getDayName(int day, char *name)
{
	switch(day)
	{
	case 0:
		strcpy(name, "imix");
		break;
	case 1:
		strcpy(name, "ik");
		break;
	case 2:
		strcpy(name, "akbal");
		break;
	case 3:
		strcpy(name, "kan");
		break;
	case 4:
		strcpy(name, "chicchan");
		break;
	case 5:
		strcpy(name, "cimi");
		break;
	case 6:
		strcpy(name, "manik");
		break;
	case 7:
		strcpy(name, "lamat");
		break;
	case 8:
		strcpy(name, "muluk");
		break;
	case 9:
		strcpy(name, "ok");
		break;
	case 10:
		strcpy(name, "chuen");
		break;
	case 11:
		strcpy(name, "eb");
		break;
	case 12:
		strcpy(name, "ben");
		break;
	case 13:
		strcpy(name, "ix");
		break;
	case 14:
		strcpy(name, "mem");
		break;
	case 15:
		strcpy(name, "cib");
		break;
	case 16:
		strcpy(name, "caban");
		break;
	case 17:
		strcpy(name, "eznab");
		break;
	case 18:
		strcpy(name, "canac");
		break;
	case 19:
		strcpy(name, "ahau");
	}
}

int main()
{
	int i;
	int n;
	cin>>n;
	Haab *haabCal = new Haab[n];
	Tzolkin *tzolkinCal = new Tzolkin[n];
	char c;
	char month[7];
	int totalDays;
	int days;
	for(i=0; i<n; i++)
	{
		cin>>haabCal[i].day>>c>>month>>haabCal[i].year;
		haabCal[i].month = (HaabMonth)getMonthNum(month);
		totalDays = haabCal[i].year*365+haabCal[i].month*20+haabCal[i].day+1;
		tzolkinCal[i].year = (totalDays-1)/260;
		days = totalDays-tzolkinCal[i].year*260;
		tzolkinCal[i].num = (days-1)%13+1;
		tzolkinCal[i].day = (TzolkinDay)((days-1)%20);
	}
	char day[9];
	cout<<n<<endl;
	for(i=0; i<n; i++)
	{
		getDayName(tzolkinCal[i].day, day);
		cout<<tzolkinCal[i].num<<' '<<day<<' '<<tzolkinCal[i].year<<endl;
	}
	return 0;
}
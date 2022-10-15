#ifndef SANAEUTIL_H
#define SANAEUTIL_H


#include <time.h>
#include <stdlib.h>


typedef unsigned int UINT;


/*Define Function*/
/*Random*/
void setseed ();
UINT random  (UINT,UINT);

/*Time*/
UINT get_second (time_t);
UINT get_minutes(time_t);
UINT get_hour   (time_t);
UINT get_day    (time_t);
UINT get_year   (time_t);


/*random*/

bool is_setseed = false;

void setseed() {
	union times{
		time_t time;
		int    show[sizeof time_t / sizeof (int)];
	}
	data = { time(NULL) };
	
	srand((UINT)data.show[0]);

	is_setseed = true;
}

UINT random(UINT min,UINT max) {
	if (!is_setseed)setseed();

	return (UINT)(rand()%(max-min+1))+min;
}


/*TIME*/

enum SanaeUtilTime {
	MIN  = 60, 
	HOUR = MIN  * 60, 
	DAY  = HOUR * 24, 
	YEAR = DAY  * 365,
	GMT  = 9
};

UINT get_second(time_t buf = 0) {
	if (buf == 0)
		buf = time(NULL);
	
	buf %= MIN;

	return (UINT)buf;
}

UINT get_minutes(time_t buf = 0) {
	if (buf == 0)
		buf = time(NULL);
	
	buf %= HOUR;
	buf /= MIN;

	return (UINT)buf;
}

UINT get_hour(time_t buf = 0) {
	if (buf == 0)
		buf = time(NULL);

	buf %= DAY;
	buf /= HOUR;
	buf += GMT;

	if (buf>24)
		buf -= 24;

	return  (UINT)buf;
}

UINT get_day(time_t buf = 0) {
	if (buf == 0)
		buf = time(NULL);
	
	//‰“ú‚ğŠÜ‚Ü‚È‚¢
	buf -= DAY;

	buf %= YEAR;
	buf /= DAY;
	
	return  (UINT)buf-12;
}

UINT get_year(time_t buf = 0) {
	if (buf == 0)
		buf = time(NULL);

	buf /= YEAR;

	/*1970”N‚©‚ç‚ÌŒo‰ßŠÔ*/
	buf += 1970;

	return  (UINT)buf;
}
#endif
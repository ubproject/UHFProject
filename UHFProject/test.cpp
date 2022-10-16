#include "Sanae.h"

int main(void) {
	UINT sec = get_second();

	for (UINT i = 1; i <= 10000;i++) {
		printf("%u^1/2=%lf\n",i,root(i));
	}

	double keika = (double)get_second() - sec;
	keika /= 10000;
	printf("ˆê‚Â“–‚½‚è‚ÌŒo‰ß•b‚Í%lf‚Å‚µ‚½\n",keika);

}
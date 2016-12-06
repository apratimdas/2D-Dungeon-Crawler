
#include "Project_Util.h"

//#include <time.h>
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <math.h>


//Define other attributes like speed when needed
double util_distance(int posx1, int posy1, int posx2, int posy2)
{
	return sqrt(pow(((double)posx1 - (double)posx2), 2.0) + pow(((double)posy1 - (double)posy2), 2.0));
}

/**
*
*/
/* Compile with:

cc hrzones.c -o hrzones -lm -O2 -Wall -ansi -pedantic -static

*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> /* strlen() */
#include <ctype.h>  /* isdigit() */

#define VERSION "0.10b"

double round(double x);

int is_integer (char * s)
/* Determines if passed string is a positive integer */
{
    short c;
    short sc = strlen(s);
    for ( c = 0; c < sc; c ++ )
    {
        if ( isdigit( s[c] ) )
            continue;
        else
			return 0;
    }
    return 1;
}


int main(int argc, char ** argv)
{
	int age, hrmax, hrmin = 0;
	int zones[5] = {50, 60, 70, 80, 90};
	int i, bpm, prev, bpm_standard, bpm_karvonen;

	switch (argc)
	{
		case 0:
			fprintf(stderr, "There are no arguments. Is everything OK?\n");
			return 1;
			break;
		case 1:
			fprintf(stderr, "Please, specify the age value.\n"
							"\nFor example: %s 40\n", argv[0]);
			return 1;
			break;
		case 2:
			if (!is_integer(argv[1]))
			{
				fprintf(stderr, "Age value must be a positive integer.\n");
				return 1;
			}
			age = atoi(argv[1]);
			hrmax = round(208.75 - (age * 0.73));  /* Tanaka hrmax */
			/*printf("Age: %d HRMax: %d (Tanaka) HRMin: Unknown\n", age, hrmax); */
			printf("Age: %d HRMax: %d (Tanaka)\n", age, hrmax);
			break;
		case 3:
			if (!is_integer(argv[2]))
			{
				fprintf(stderr, "HRMax value must be a positive integer.\n");
				return 1;
			}
			hrmax = atoi(argv[2]);
			printf("HRMax: %d\n", hrmax);
			break;
		case 4:  /* Karvonen formula */
			if (!is_integer(argv[2]))
			{
				fprintf(stderr, "HRMax value must be a positive integer.\n");
				return 1;
			}
			if (!is_integer(argv[3]))
			{
				fprintf(stderr, "HRMin value must be a positive integer.\n");
				return 1;
			}
			hrmax = atoi(argv[2]);
			hrmin = atoi(argv[3]);
			printf("HRMax: %d HRMin: %d\n", hrmax, hrmin);
			break;
		default:
			fprintf(stderr, "There are too much arguments: %d\n", argc);
			return 1;
			break;
	}


	prev = hrmax;

	for (i = 4; i>=0; i--)
	{
		if (hrmin)
		{
			bpm_karvonen = round((hrmax - hrmin) * zones[i] / 100 + hrmin);
			bpm = bpm_karvonen;
		}
		else
		{
			bpm_standard = round(zones[i] * hrmax / 100);
			bpm = bpm_standard;
		}


		printf("Z%d: %3d-%d (%d %%)\n", i+1, bpm, prev, zones[i]);
		prev = bpm - 1;
	}

    return 0;
}

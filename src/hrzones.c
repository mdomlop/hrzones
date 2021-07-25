/* Compile with:

cc hrzones.c -o hrzones -lm -O2 -Wall -ansi -pedantic -static

*/

#include <stdio.h>
#include <math.h>   /* round() */
#include <stdlib.h> /* abort() */
#include <string.h> /* strlen() */
#include <ctype.h>  /* isdigit() */
#include <unistd.h>

#define VERSION "0.10a"

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


void help (int error)
{
	if (error)
		fprintf (stderr, "Error. Mostrar ayuda.\n");
	else
		printf ("Sin error. Mostrar ayuda.\n");
}

int tanaka (int n)
{
	int x = round(208.75 - (n * 0.73));  /* Tanaka hrmax */
	return x;
}


int main(int argc, char ** argv)
{

	int age, hrmax, hrmin = 0;
	int zones[5] = {50, 60, 70, 80, 90};
	int i, bpm, prev, bpm_standard, bpm_karvonen;


	int aflag = 0;
	int index;
	int c;

	opterr = 0;

	int non_optc;


	while ((c = getopt (argc, argv, "a")) != -1)
		switch (c)
		{
			case 'a':
				aflag = 1;
				break;
			case '?':
				if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr, "Unknown option character `\\x%x'.\n",
							optopt);
                return 1;
			default:
				abort ();
		}

	non_optc = argc - optind;

	switch (non_optc)
	{
		case 0:
			if (aflag) fprintf (stderr, "Sorry, `-a' flag needs a number.\n");
			else fprintf (stderr, "I need at least one argument.\n");
			return 1;

		case 1:  /* Age or HRMax */

			if (is_integer(argv[optind]))
			{
				age = atoi(argv[optind]);
				if (aflag)
				{
					hrmax = tanaka(age);
					printf("Age: %d HRMax: %d (Tanaka)\n", age, hrmax);
				}
				else
				{
					hrmax = age;
					printf("HRMax: %d\n", hrmax);
				}
				break;
			}
			else {
				fprintf (stderr, "Arguments must be positive integers.\n");
				return 1;
			}

		case 2:  /* Age or HRMax and HRMin*/
			if (is_integer(argv[optind]) && is_integer(argv[optind + 1]))
			{
				age = atoi(argv[optind]);
				hrmin = atoi(argv[optind + 1]);

				if (aflag)
				{
					hrmax = tanaka(age);
					printf("Age: %d HRMax: %d (Tanaka) HRMin: %d\n", age, hrmax, hrmin);
				}
				else
				{
					hrmax = age;
					printf("HRMax: %d HRMin: %d\n", hrmax, hrmin);
				}
				break;
			}
			else
			{
				fprintf (stderr, "Arguments must be positive integers.\n");
				return 1;
			}

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

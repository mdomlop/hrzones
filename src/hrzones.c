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
int getopt(int argc, char *const argv[], const char *optstring);
extern int optind, optopt;

int is_integer (char * s)
/* Determines if passed string is a positive integer */
{
    short c;
    short sc = strlen(s);
    for ( c = 0; c < sc; c ++ )
    {
        if (isdigit (s[c]))
            continue;
        else
			return 0;
    }
    return 1;
}

void version (void)
{
	printf ("Version: %s\n", VERSION);
}

void help (int error)
{
	char text[] = "\nUsage:\n"
	"\thrzones [-a] n1 [n2]\n\n"
	"Options:\n\n"
	"\tn1    An integer positive which is maximun heart rate (or age, if `-a'\n"
	"\t      flag is present).\n"
	"\tn2    An integer positive number which is resting heart rate.\n"
	"\t      If provided, Karvonen's formula will be used.\n\n"
	"\t-a    Indicate that `n1' is an age and not the maximum heart rate.\n"
	"\t      Therebefore `n1' will be used to calculate the maximum heart \n"
	"\t      rate with the Tanaka's formula.\n"
	"\t-h    Show this help.\n"
	"\t-v    Show program version and exit.\n";

	if (error)
		fprintf (stderr, "%s\n", text);
	else
		printf ("%s\n", text);
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
	int c;

	int non_optc;


	while ((c = getopt (argc, argv, "ahv")) != -1)
		switch (c)
		{
			case 'a':
				aflag = 1;
				break;
			case 'h':
				help(1);
				return 0;
			case 'v':
				version();
				return 0;
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
			help(1);
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
			fprintf(stderr, "There are too much arguments: %d\n", non_optc);
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

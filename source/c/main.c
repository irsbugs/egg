/**
* main.c for egg timer program
*
* Program to demonstrate GObject Introspection Repository.
* This C source code compilies to a standalone executable.
*
* Three functions are exposed so they may be accessed by other language bindings
*
* Bindings for different languages:
* https://wiki.gnome.org/Projects/GObjectIntrospection/Users
*
* The comments that start with /** are GTK-Doc comments. Everything that is 
* part of the object's external API should be documented with these. 
*
* Author: Ian Stewart
* Date: 2020-06-01
*/

#include<stdio.h>  
#include<stdlib.h>  
#include<time.h>
#include<string.h>


// declarations
void start_egg_timer(int);
void time_elapsed();
void time_remaining();


void start_egg_timer(int duration)
/**
* start_egg_timer(int duration)
* 
* This function accepts a value of seconds for the duration.
* Retrieves the epoch time stamp and with comma delimiter add the duration
* Stores these two values in /tmp/egg.data file.
*/
{
    //fprintf(stdout, "Start Egg Timer: %lu\n", (unsigned long)time(NULL));
    FILE *fp;  
    //open file, write time stamp now,duration, close file  
    fp = fopen("/tmp/egg.data", "w");
    //writing data into file  
    fprintf(fp, "%lu,%d\n", (unsigned long)time(NULL), duration);
    fclose(fp);
 
    // Time now local. E.g. 1 Jun 2020 17:57:15
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer,80,"\nEgg timer started: %e %b %Y %H:%M:%S",timeinfo);
    puts (buffer);
    // Duration of timer
    printf("Timer set for: %d seconds\n", duration);
}


void time_elapsed()
/**
* time_elapsed()
*
* This function reads the data file and extracts the time stamp.
* A comparison is made with the current time to derive the elapsed time.
*
*/
{
    #define MAXCHAR 100

    FILE *fp;
    char str[MAXCHAR];
    char* filename = "/tmp/egg.data";
 
    if (!(fp = fopen(filename, "r"))) 
    {
        printf("\nCould not open file: %s\n",filename);
        return;
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        //printf("%s", str);
	    char delim[] = ",";
	    char *ptr = strtok(str, delim);
		//printf("'%s'\n", ptr);

        // Convert string to integer
        // Time now - start time
        int time_now = (unsigned long)time(NULL);
        int elapsed = time_now - ((int) strtol(ptr, (char **)NULL, 10));

        printf("\nEggs have been cooking for %d seconds\n", elapsed);
    }
    fclose(fp);
}


void time_remaining()
/**
* time_remaining()
* 
* This functions reads from the data file both the time stamp and the 
* duration. In conjunction with the time now the remaining time is calculated.
*/
{
    #define MAXCHAR 100

    FILE *fp;
    char str[MAXCHAR];
    char* filename = "/tmp/egg.data";

    if (!(fp = fopen(filename, "r"))) 
    {
        printf("\nCould not open file: %s\n",filename);
        return;
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
    {   //printf("%s", str);

	    char delim[] = ",";

        // Start time
	    char *ptr = strtok(str, delim);
        int start_time = ((int) strtol(ptr, (char **)NULL, 10));
		//printf("'%s'\n", ptr);

        // Duration
		ptr = strtok(NULL, delim);
        ptr = strtok(ptr, "\n");
        //char *duration = strtok(ptr, "\n");
        int duration = ((int) strtol(ptr, (char **)NULL, 10));
		//printf("'%s'\n", ptr);

        int time_now = (unsigned long)time(NULL);
        int remain = (start_time + duration) - time_now;

        printf("\nKeep cooking the eggs for %d seconds\n", remain);
    }
    fclose(fp);
}


void main( int argc, char *argv[] )
/**
* main( int argc, char *argv[] )
*
* This functions allows the C program to execute standalone. A menu is 
* displayed on the console and the User selects an egg timer option. Three
* options make calls to the exposed functions.
*
*/
{  
    char c;  
    int choice;
   
    c = 'y';
    while (c == 'y')
    {  
        printf("\n" \
                "Egg Timer Menu:\n" \
                "   1. Start Egg Timer\n" \
                "   2. Time Elapsed\n" \
                "   3. Time Remaining\n" \
                "   4. Stop Egg Timer\n\n" \
                "Selection: ");

        if (scanf("%d",&choice) != 1)
        {
            // If non-numeric characters are entered then error message. 
            printf("Invalid Characters: Enter a value between 1 and 4...\n");
            scanf("%*s");
        }
        else    
        {
            // Process numeric entries from 1 to 4. Ignore all other numerics.
            switch(choice)  
            {      
                case 1 :
                    // If present get the argv[1] for time to cook eggs. Or 60.
                    // Call start_egg_timer.
                    if(argc < 2)
                    {
                        //printf("No argument passed through command line.\n");
                        start_egg_timer(60);
                    }  
                    else
                    {  
                        //printf("First argument is: %s\n", argv[1]);
                        // Convert argv[1] string to integer
                        start_egg_timer((int) strtol(argv[1], (char **)NULL, 10));
                    }
                    break;

                case 2 :    
                    // Call time_elapsed()
                    //printf("Get the elapsed time\n");
                    time_elapsed();  
                    break;  

                case 3 :
                    // Call time_remaining()
                    //printf("Get the remaining time.\n");
                    time_remaining();
                    break;

                case 4 :  
                    // Exit the loop
                    c = 'n';
                    printf("\nEnjoy your eggs.\n\n");
                    break;  

                default :
                    // Numeric data entered but not 1 through 4. Error message.
                    printf("Invalid Numeric: Enter a value between 1 and 4...\n");
            }
        }
    } 
}

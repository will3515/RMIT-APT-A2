/**
 * File: utility.c
 * Author: William Cohen
 * Student no.: s3660470
 * Course: Advanced Programming Techniques
 * Year: 2017
 **/

#include "utility.h"

/**
 * Function required to be used when clearing the buffer. It simply reads
 * each char from the buffer until the buffer is empty again. Please refer
 * to the materials on string and buffer handling in the course for more
 * information.
 **/
void readRestOfLine()
{
    int ch;
    while(ch = getc(stdin), ch != EOF && ch != '\n')
    { } /* Gobble each character. */

    /* Reset the error status of the stream. */
    clearerr(stdin);
}

/* Counts and returns the number of digits in a number*/
unsigned countDigits(unsigned n) {
    size_t count = 0;
    while (n != 0) {
        n /= 10;
        count++;
    }
    return count;
}

/* Gets text input from user 
 * Returns false if nothing was entered 
 * Returns true if a valid input was entered */
Boolean getUserInput(char * string, int max) {
    Boolean valid = FALSE;
    while (!valid) {
        fgets(string, max, stdin);

        /* Check to see if a new-line was entered */
        if (string[0] == '\n' || string[0] == '\0') return FALSE;

        /* Check to see if too many chars were entered */
        if (string[strlen(string)-1] != '\n') {
            /* Clear the buffer */
            readRestOfLine();
            printf("Too many characters were entered.\nPlease try again:");
            continue;
        }

        valid = TRUE;
    }

    if (string[strlen(string)-1] == '\n') string[strlen(string)-1] = '\0'; 

    return TRUE;

}


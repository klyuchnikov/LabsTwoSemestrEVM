#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <stdio.h>
#include <conio.h>
#include <iostream>
#pragma warning(disable : 4996)
using namespace std;
void sleep( clock_t wait );

int main( void )
{
   long    i = 6000000L;
   clock_t start, finish;
   double  duration;

   // Delay for a specified time.
   printf( "Delay for three seconds\n" );
   float t = 0.0;
   while (t < 10)
   {
	   printf("%f\n", t+= 0.1);
	   sleep( (clock_t)100);
   }
   printf( "Done!\n" );

   // Measure the duration of an event.
   printf( "Time to do %ld empty loops is ", i );
   start = clock();
   while( i-- ) 
      ;
   finish = clock();
   duration = (double)(finish - start) / CLOCKS_PER_SEC;
   printf( "%2.1f seconds\n", duration );
}

// Pauses for a specified number of milliseconds.
void sleep( clock_t wait )
{
   clock_t goal;
   goal = wait + clock();
   while( goal > clock() )
      ;
}
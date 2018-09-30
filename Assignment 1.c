#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Luis O'Donnell
//PID: L3406464
//Assignment 1
//Addition between N-digit numbers

void  adding( int random1[2002], int random2[2002], int n, int length);
void  addsub( int random1[2002], int random2[2002], int n, int length, int og1[2002], int og2[2002]);
void  printAll(int result[2002], int random1[2002], int random2[2002], int n, int length, int reslength);

//if we print or not
int printflag; 

int main()
{	
	//Prereqs for input here
    printf("Please Enter in the n-digit inputsize ranging from 1 to 1000\n");
    int n; 
    scanf("%d", &n);
    while( !(n >= 1 && n <= 1000))
    {
    	printf("Out of Bounds enter in N, between 1 and 1000 (inclusive)\n");
    	scanf("%d", &n);
	}
    //printf("Input value read : n = %d", n);
    printf("Do you wish to print to console all the n-digit addition results?\n");
    printf("Example N = 3 Prints: 123 + 456 = 579\n");
    printf("SAYING YES MAY TAKE LONGER FOR RESULTS\n");
    printf("This option mainly used for testing\n");
    printf("Enter in 1 for YES and 0 for NO\n");
    scanf("%d", &printflag);
    
    while( printflag!=0 && printflag!=1 )
    {
    	printf("Do you wish to print to console all the n-digit addition results?\n");
    	printf("Example N = 3 Prints: 123 + 456 = 579\n");
    	printf("SAYING YES MAY TAKE LONGER FOR RESULTS\n"); 
    	printf("This option mainly used for testing\n");
    	printf("Enter in 1 for YES and 0 for NO\n");
    	scanf("%d", &printflag);
	}
	
	srand(time(0));
	
	//we start timer here
    clock_t clocker;
    clocker = clock();
    
    //performs the addition 1000 times
    int timer;
    printf("\nResults:\n");
    for(timer = 0; timer < 1000; timer++)
    {
    	//gens number from 0-9 randomly in all spots
    	int i, random1[2002], random2[2002];
    	for(i = 0; i < n-1; i++)
    	{
    		random1[i] = rand() % 10;
    		random2[i] = rand() % 10;
		}
		//makes the front of the number not 0, so 1-9 to make sure it is N-digit
		random1[i] = rand() % 9+1;
    	random2[i] = rand() % 9+1;
    	
    	//makes them either positibe and negative signed.
    	//0 is positive, and 1 is negative
    	random1[2001] = rand() % 2;
    	random2[2001] = rand() % 2;
    	//random1[2001] = 0;
    	//random2[2001] = 0;
    	
    	adding( random1, random2, n, i); 
	}
	
	clocker = clock() - clocker;
	double time_taken = ((double)clocker)/CLOCKS_PER_SEC; // in seconds
	printf("The 1000 tests took %f seconds for N = %d", time_taken, n);  
    
    return 0;
}


void  adding( int random1[2002], int random2[2002], int n, int length ) 
{
	int result[2002];
	//if same sign do addition
	if (random1[2001] == random2[2001])
	{
		//do add in each digit
		int carry = 0, i, temp;
		for(i = 0; i < n; i++)
		{
			temp = random1[i] + random2[i] + carry;
			carry = temp / 10;
			result[i] = temp % 10;
		}
		//if at end we added a large number move it to rnext spot
		if(carry !=0 )
		{
			result[i] = carry; 
			i++;
		}
		//i contains our current max length of the result array,
		//same as length except with random1 and random 2
		i--;
		//i-- is for helpw ith printing
		
		//keep the sign
		result[2001] = random1[2001];
		
		//print here
		if(printflag)
		{
			printAll(result, random1, random2, n, length, i);
		}
	}
	else
	{
		//we have different signs so we must add a positive and negative
		//which is essentially subtracting the larger number by the smaller number (absolute value)
		//while also keeping the sign of the larger number
		addsub(random1, random2, n, length, random1, random2);
	}
}

void  addsub( int random1[2002], int random2[2002], int n, int length, int og1[2002], int og2[2002])
{
	int result[2002], i;
	i = length;
	int flag = 1;
	int longer = 0;
	int nextlength = 1;
	
	int test1[2002], test2[2002], yy;
	for(yy = 0; yy < 2002; yy++)
	{
		test1[yy] = random1[yy];
		test2[yy] = random2[yy];
	}
	
	//fins which number has bigger aboslute value
	while( flag )
	{
		//we got to end thus same number
		//so result is just 0, which is its default state
		//exit loop
		if(i < 0)
		{
			flag = 0;
		}
		else
		{
			//if same number go to the next number i-1
			//and restart loop
			if(random1[i] == random2[i])
			{
				i--;
			}
			else
			{
				if(random1[i] > random2[i])
				{
					longer = 1;
					flag = 0;
				}
				else
				{
					longer = 2;
					flag = 0;
				}
			}
		}
	}
	
	//if i was more than equal to zero than we can subtract
	if(i >= 0)
	{
		//case for random1 > random2 aboslute value
		if(longer == 1)
		{
			int j,k, temp, carry;
			for(j = 0; j < n; j++)
			{
				if(test1[j] >= test2[j])
				{
					result[j] = test1[j] - test2[j];
				}
				else
				{
					temp = test1[j] + 10;
					k = j+1;
					while(test1[k] == 0 && k < n)
					{
						test1[k] = 9;
						k++;
					}
					test1[k] = test1[k] - 1;
					
					result[j] = temp - test2[j];
				}
			}
			
			//keep same sign of larger number
			result[2001] = random1[2001];
		}
		//thus case for random1 < random2 aboslute value
		else
		{
			int j,k, temp, carry;
			for(j = 0; j < n; j++)
			{
				if(test2[j] >= test1[j])
				{
					result[j] = test2[j] - test1[j];
				}
				else
				{
					temp = test2[j] + 10;
					k = j+1;
					while(test2[k] == 0 && k < n)
					{
						test2[k] = 9;
						k++;
					}
					test2[k] = test2[k] - 1;
					
					result[j] = temp - test1[j];
				}
			}
			
			//keep same sign of larger number
			result[2001] = random2[2001];
		}
	}
	else
	{
		nextlength = 0;
	}
	
	/*
	//calc length of result
	if(nextlength != 1)
	{
		int x = 2000, counter = 0;
		while(result[x] == 0)
		{
			if(x == 0)
			{
				break;
			}
			counter++;
			x--;
		}
		if(x == 0)
		{
			nextlength = 0;
		}
		else
		{
			nextlength = 2002 - 2 - counter;
		}
	
	}
	*/
	
	//We have our results here so we can print them
	//print here
	if(printflag)
	{
		printAll(result, og1, og2, n, length, n-1);
	}
}

printAll(int result[2002], int random1[2002], int random2[2002], int n, int length, int reslength)
{
	int i, j, k;
	//print in reverse order (which is where lenght is)
	//also print out if negative sign first
	if(random1[2001] == 1)
	{
		printf("-");
	}
	for(i = length; i >= 0; i--)
	{
		printf("%d", random1[i]);
	}
	
	printf(" + ");
	
	if(random2[2001] == 1)
	{
		printf("-");
	}
	for(i = length; i >= 0; i--)
	{
		printf("%d", random2[i]);
	}
	
	printf(" = ");
	
	if(result[2001] == 1)
	{
		printf("-");
	}
	for(i = reslength; i >= 0; i--)
	{
		printf("%d", result[i]);
	}
	printf("\n");
}

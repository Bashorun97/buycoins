/*
Wed 30 Sep 2020 04:42:06 AM WAT 
Author: Bashorun, E. (babaibeji)
Written with love using VIM
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


struct Jacobi
{
  int A[100]; // Array of 'a' values
};


_Bool is_power(int num)
{
  return (num && !(num &(num - 1)));
}


_Bool check_proth(int num)
{
  int k = 1;
  num = num - 1;
  
  while (k < (num/k))
  {
    if (num % k == 0)
      if (is_power(num/k))
        return 1;
    k = k + 2;
  }
  return 0;
}


int greatest_common_divisor(int a, int b)
{
  if (a == 0)
    return b;
  else
    greatest_common_divisor(b % a, a);
}


// Using Jacobi symbol to generate appropriate 'a' values to minimize randomization
int jacobi_symbol(struct Jacobi *j, int limit)
{
  // Randomly generate positive integers 'a' and odd integers 'n' where n>a. 
  int i;
  int a, n, r;

  srand(time(0));

  for (i=0; i<limit; i++)
  {
    a = rand()%100;
    n = rand()%2*100;
    if (n%2 == 0)
      n += 1;
      
    int t = 1;
    while (a != 0)
    {
      while (a % 2 == 0)
      {
        a /= 2;
        r = n % 8;
        if (r == 3 || r == 5)
          t = -t;
      }
      a = n;
      n = a;
      if (a % 4 == n % 4 == 3)
        t = -t;
      a %= n;
    }
    if (n == -1)
    {
      j->A[i] = t;  
    }
    else
      return 0;
  }
}

/*
void Display(struct Jacobi j, int limit)
{
  int i;
  for (i=0; i<limit; i++)
  {
    printf("%d, ", j.A[i]);
  }
}
*/


// Using Proths Theorem, check if Proths number is prime
_Bool check_proth_prime(struct Jacobi *j, int proth_number, int limit)
{
  int i, a, b, exponent;

  i = 0;
  while (1)
  {
    a = j->A[i];
    exponent = (proth_number - 1)/2;
    b = (int)pow(a, exponent);
    if (b % proth_number == -1 % proth_number)
    {
      return 1;
    }
    i++;
  }
  return 0;
}


int main()
{
  int proth_value;
  int range = 100;
  _Bool is_proth, proth_prime_result;

  struct Jacobi j;

  printf("Enter a Proth Number: ");
  scanf("%d", &proth_value);

  is_proth = check_proth(proth_value);
  if (is_proth == 1)
  {
    jacobi_symbol(&j, range);
    proth_prime_result = check_proth_prime(&j, proth_value, range);
    if (proth_prime_result == 1)
    {
      printf("%d is a prime number and a proth number. \n", proth_value);
    }
    else if (proth_prime_result == 0)
    {
      printf("%d is a proth number \n", proth_value);
      printf("But it isn\'t a prime number. \n");
    }
  }
  else
    printf("Not a proth number neither is it a proth prime. \n");
  //Display(j, range);
}

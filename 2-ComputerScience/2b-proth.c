/*
Wed 30 Sep 2020 04:42:06 AM WAT
Author: Bashorun, E. (babaibeji)
Written with love on VIM
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MOD(a, b) ((((a) % (b)) + (b)) % (b))

struct Jacobi
{
  int A[500]; // Array of 'a' values
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


_Bool modular (int a, int b, int m)
{
  if ((a % m) == (b % m))
    return 1;
}


// Using Jacobi symbol to generate appropriate 'a' values to minimize randomization
void jacobi_symbol(struct Jacobi j, int limit)
{
  // Randomly generate positive integers 'a' and odd integers 'n' where n>a.
  int i;
  int a, n, r;

  //srand(time(0));

  for (i=0; i<limit; i++)
  {
    a = rand()%1000;
    n = rand()%2*1000;
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
      j.A[i] = t;
  }
}


// Using Proths Theorem, check if Proths number is prime
_Bool check_proth_prime(struct Jacobi *j, int proth_number)
{
  long long i, a, b, exponent;
  long long left_1, right_1, left_2, right_2;

  for (i=0; i<500; i++)
  {
    a = j->A[i];
    exponent = (proth_number - 1)/2;
    b = (long)pow(a, exponent);
    left_1 = MOD(b, proth_number);
    right_1 = MOD(-1, proth_number);
    left_2 = b % proth_number;
    right_2 = 1 % proth_number;

    if (left_1 == right_1)
      return 1;
    if (left_2 == right_2)
      continue;
  }
  return 0;
}


int main()
{
  int proth_value;
  int range = 500;
  _Bool is_proth, proth_prime_result;

  struct Jacobi j;

  printf("Enter a Proth Number: ");
  scanf("%d", &proth_value);

  is_proth = check_proth(proth_value);
  if (is_proth == 1)
  {
    jacobi_symbol(j, range);
    proth_prime_result = check_proth_prime(&j, proth_value);
    if (proth_prime_result == 1)
    {
      printf("%d is a prime number and a proth number. \n", proth_value);
    }
    else if (proth_prime_result == 0)
    {
      printf("%d is a proth number \n", proth_value);
      printf("But it isn\'t a proth prime number. \n");
    }
  }
  else
    printf("Not a proth number neither is it a proth prime. \n");
}

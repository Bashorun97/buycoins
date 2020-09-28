#include <stdio.h>

int fib(int n)
{
  if (n<=1)
    return n;
  return fib(n-2)+fib(n-1);
}

int main()
{
  int number;
  printf("Enter a number: ");
  scanf("%d", &number);
  printf("Fibonacci of %d \n", fib(number));
}


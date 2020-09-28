#include <stdio.h>

_Bool isPower(int num)
{
  return (num && !(num &(num - 1)));
}

int main()
{
  if (isPower(2))
  {
    printf("True");
  }
}

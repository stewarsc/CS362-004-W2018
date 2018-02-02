#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    //defining input to be target parameters
    char* charValues= "[({ ax})]";
    int randChoice = rand() % 9;
    
    //returns random choice between 0 and 8 of charVaules
    return charValues[randChoice];
}

char *inputString()
{
  //array for target values
  char* inputValues = "reset\0";
  char* output;
  int i = 0;
  int randNum;
  
  //making copy array and setting equal to NULL
  output = malloc(sizeof(char) * 6);
  memset(output, '\0', 7); 

  //loop that randomly fills array with target values
  for (i; i < 6; i++){
    randNum = rand() % 6;
    output[i] = inputValues[randNum];
  }

  //returning output array
  return output;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}

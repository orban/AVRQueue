#include <util/delay.h>
#include <stdio.h>

#include "../queue.c"

#include "tests.h"

int testFunction(queue_time_t now)
{
    _delay_ms(100);
    return 1;
}

int test_addTooMany(void)
{
   int rv;
   int testStatus = 0;
   rv = scheduleFunction(testFunction, "Test1", 5000, 1000);
   if(rv != 0)
   {
     printf("test_addTooMany failed.");
     testStatus = -1;
   }
   rv = scheduleFunction(testFunction, "Test2", 5000, 1000);
   if(rv != 0)
   {
     printf("test_addTooMany failed.");
     testStatus = -1;
   }
   rv = scheduleFunction(testFunction, "Test3", 5000, 1000);
   if(rv != 0)
   {
     printf("test_addTooMany failed.");
     testStatus = -1;
   }
   rv = scheduleFunction(testFunction, "Test4", 5000, 1000);
   if(rv != 0)
   {
     printf("test_addTooMany failed.");
     testStatus = -1;
   }
   rv = scheduleFunction(testFunction, "Test5", 5000, 1000);
   if(rv != 0)
   {
     printf("test_addTooMany failed.");
     testStatus = -1;
   }
   rv = scheduleFunction(testFunction, "Test6", 5000, 1000);
   if(rv != 0)
   {
     printf("test_addTooMany failed.");
     testStatus = -1;
   }
   rv = scheduleFunction(testFunction, "Test7", 5000, 1000);
   if(rv != 0)
   {
     printf("test_addTooMany failed.");
     testStatus = -1;
   }
   rv = scheduleFunction(testFunction, "Test8", 5000, 1000);
   if(rv != 0)
   {
     printf("test_addTooMany failed.");
     testStatus = -1;
   }
   rv = scheduleFunction(testFunction, "Test9", 5000, 1000);
   if(rv != 0)
   {
     printf("test_addTooMany failed.");
     testStatus = -1;
   }
   rv = scheduleFunction(testFunction, "Test10", 5000, 1000);
   if(rv != 0)
   {
     printf("test_addTooMany failed.");
     testStatus = -1;
   }
   rv = scheduleFunction(testFunction, "Test11", 5000, 1000);
   if(rv != -1)
   {
     printf("test_addTooMany failed.");
     testStatus = -1;
   }

   return testStatus;
}
int test_removeNonExistent(void)
{
    int rv;
    int testStatus = 0;
    rv = scheduleFunction(testFunction, "Test", 5000, 1000);
    if(rv != 0)
    {
      printf("test_removeNonExistent failed.");
      testStatus = -1;
    }
    rv = scheduleRemoveFunction("Fail");
    if(rv != -1)
    {
      printf("test_removeNonExistent failed.");
      testStatus = -1;
    }
    return testStatus;
}

int test_tooManyCharacters(void)
{
    int rv;
    int testStatus = 0;
    rv = scheduleFunction(testFunction, "ReallyLongName", 5000, 1000);
    if(rv != -1)
    {
      printf("test_tooManyCharacters failed.");
      testStatus = -1;
    }
    return testStatus;
}

int test_changeNonExistent(void)
{
    int rv;
    int testStatus = 0;
    rv = scheduleFunction(testFunction, "Test", 5000, 1000);
    if(rv != 0)
    {
      printf("test_changeNonExistent failed.");
      testStatus = -1;
    }
    rv = scheduleChangeFunction("Fail", 1000, 1000);
    if(rv != -1)
    {
      printf("test_changeNonExistent failed.");
      testStatus = -1;
    }
    return testStatus;
}

int test_runEmpty(void)
{
    int rv = 0;
    int testStatus = 0;
    rv = scheduleRun(10);
    if (rv != -1)
    {
      printf("test_runEmpty failed.");
      testStatus = -1;
    }
    return testStatus;
}

int testAll(void)
{
    queueStart = 0;
    queueEnd = 0;
    int testStatus = 0;
    testStatus |= test_addTooMany();
    queueStart = 0;
    queueEnd = 0;
    testStatus |= test_removeNonExistent();
    queueStart = 0;
    queueEnd = 0;
    testStatus |= test_tooManyCharacters();
    queueStart = 0;
    queueEnd = 0;
    testStatus |= test_changeNonExistent();
    queueStart = 0;
    queueEnd = 0;
    testStatus |= test_runEmpty();

    return testStatus;


}
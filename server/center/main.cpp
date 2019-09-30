#include <stdio.h>
#include "common/servercommon.h"

void test()
{
    printf("sizeof char8 :%d\n", sizeof(char8));
    printf("sizeof char16 :%d\n", sizeof(char16));
    printf("sizeof float32 :%d\n", sizeof(float32));
    printf("sizeof double64 :%d\n", sizeof(double64));
    printf("sizeof byte8 :%d\n", sizeof(byte8));
    printf("sizeof int16 :%d\n", sizeof(int16));
    printf("sizeof uint16 :%d\n", sizeof(uint16));
    printf("sizeof int32 :%d\n", sizeof(int32));
    printf("sizeof uint32 :%d\n", sizeof(uint32));
    printf("sizeof int64 :%d\n", sizeof(int64));
    printf("sizeof uint64 :%d\n", sizeof(uint64));
}
 
int main(int argc, char* argv[])
{
	test();
	return 0;
}

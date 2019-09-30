#include <stdio.h>
#include "common/servercommon.h"

void test()
{
    printf("sizeof char8 :%lu\n", sizeof(char8));
    printf("sizeof char16 :%lu\n", sizeof(char16));
    printf("sizeof float32 :%lu\n", sizeof(float32));
    printf("sizeof double64 :%lu\n", sizeof(double64));
    printf("sizeof byte8 :%lu\n", sizeof(byte8));
    printf("sizeof int16 :%lu\n", sizeof(int16));
    printf("sizeof uint16 :%lu\n", sizeof(uint16));
    printf("sizeof int32 :%lu\n", sizeof(int32));
    printf("sizeof uint32 :%lu\n", sizeof(uint32));
    printf("sizeof int64 :%lu\n", sizeof(int64));
    printf("sizeof uint64 :%lu\n", sizeof(uint64));
}
 
int main(int argc, char* argv[])
{
	test();
	return 0;
}

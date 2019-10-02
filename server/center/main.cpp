#include <stdio.h>
#include "common/servercommon.h"

void test()
{
    printf("sizeof char8 :%d\n", static_cast<int32>(sizeof(char8)));
    printf("sizeof char16 :%d\n", static_cast<int32>(sizeof(char16)));
    printf("sizeof float32 :%d\n", static_cast<int32>(sizeof(float32)));
    printf("sizeof double64 :%d\n", static_cast<int32>(sizeof(double64)));
    printf("sizeof byte8 :%d\n", static_cast<int32>(sizeof(byte8)));
    printf("sizeof int16 :%d\n", static_cast<int32>(sizeof(int16)));
    printf("sizeof uint16 :%d\n", static_cast<int32>(sizeof(uint16)));
    printf("sizeof int32 :%d\n", static_cast<int32>(sizeof(int32)));
    printf("sizeof uint32 :%d\n", static_cast<int32>(sizeof(uint32)));
    printf("sizeof int64 :%d\n", static_cast<int32>(sizeof(int64)));
    printf("sizeof uint64 :%d\n", static_cast<int32>(sizeof(uint64)));
}
 
int main(int argc, char* argv[])
{
	test();
	return 0;
}

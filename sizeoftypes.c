#include <stdio.h>
#include <stdint.h> 
#include <stddef.h>

int main() {
    
    printf("char:        %lu\n", sizeof(char));
    printf("short:       %lu\n", sizeof(short)); 
    printf("int:         %lu\n", sizeof(int)); 
    printf("long:        %lu\n", sizeof(long));
    
    printf("float:       %lu\n", sizeof(float));
    printf("double:      %lu\n", sizeof(double));
        
    printf("size_t:      %lu\n", sizeof(size_t));
    printf("ptrdiff_t:   %lu\n", sizeof(ptrdiff_t));
    
    printf("int8_t:      %lu\n", sizeof(int8_t));   
    printf("int16_t:     %lu\n", sizeof(int16_t));
    printf("int32_t:     %lu\n", sizeof(int32_t));
    printf("int64_t:     %lu\n", sizeof(int64_t));
        
    return 0;
}
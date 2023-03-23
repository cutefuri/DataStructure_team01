#include <unistd.h> //write 사용을 위해
#include <stdarg.h> //가변 인수를 사용하기 위해

int custom_printf(const char* format, ...){
    va_list arg;    //가변 인자 생성
    va_start(arg, format);  //가변 인자 목록 저장

    char buf[1024];
    int len = _vsnprintf_s(buf, sizeof(buf), format, arg); //format의 형식으로 문자열을 생성해 buf 배열에 저장하고, len에 값을 반환. 이때 len의 값이 -1이면 버퍼 오버플로 발생

    va_end(arg); //가변 인자 목록 종료를 위해 쓰임
    return write(STDOUT_FILENO, buf, len);  //buf에 len 길이의 데이터를 터미널에 출력
}
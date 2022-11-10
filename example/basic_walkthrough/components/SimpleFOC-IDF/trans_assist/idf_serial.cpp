
#include "idf_serial.h"



void Stream::println(const __FlashStringHelper* msg){
    SimpleFOCDebug::println(msg);
}
void Stream::println(const char* msg){
    SimpleFOCDebug::println(msg);
}
void Stream::println(const __FlashStringHelper* msg, float val){
    SimpleFOCDebug::println(msg,val);
}
void Stream::println(const char* msg, float val){
    SimpleFOCDebug::println(msg,val);
}
void Stream::println(const __FlashStringHelper* msg, int val){
    SimpleFOCDebug::println(msg,val);
}
void Stream::println(const char* msg, int val){
    SimpleFOCDebug::println(msg,val);
}
void Stream::println(){
    SimpleFOCDebug::println();
}
void Stream::println(int val){
    SimpleFOCDebug::println(val);
}
void Stream::println(float val){
    SimpleFOCDebug::println(val);
}

void Stream::print(const char* msg){
    SimpleFOCDebug::print(msg);
}
void Stream::print(const __FlashStringHelper* msg){
    SimpleFOCDebug::print(msg);
}
void Stream::print(int val){
    SimpleFOCDebug::print(val);
}
void Stream::print(float val){
    SimpleFOCDebug::print(val);
}
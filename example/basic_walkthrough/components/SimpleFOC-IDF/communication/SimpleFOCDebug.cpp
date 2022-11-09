
#include "SimpleFOCDebug.h"

#ifndef SIMPLEFOC_DISABLE_DEBUG

//stop using Print class from Arduino 
/* 
Print* SimpleFOCDebug::_debugPrint = NULL;
 */

void * _debugPrint = NULL;

void SimpleFOCDebug::enable() {
    _debugPrint = (void*)"enable";
}


void SimpleFOCDebug::println(int val) {
    if (_debugPrint != NULL) {
        printf("%d\n",val);
    }
}

void SimpleFOCDebug::println(float val) {
    if (_debugPrint != NULL) {
        printf("%f\n",val);
    }
}



void SimpleFOCDebug::println(const char* str) {
    if (_debugPrint != NULL) {
        printf("%s\n",str);
    }
}

void SimpleFOCDebug::println(const __FlashStringHelper* str) {
    if (_debugPrint != NULL) {
        printf("%s\n",(char *)str);
    }
}

void SimpleFOCDebug::println(const char* str, float val) {
    if (_debugPrint != NULL) {
        printf(str);
        printf("%f\n",val);
    }
}

void SimpleFOCDebug::println(const __FlashStringHelper* str, float val) {
    if (_debugPrint != NULL) {
        printf("%s",(char *)str);
        printf("%f\n",val);
    }
}

void SimpleFOCDebug::println(const char* str, int val) {
    if (_debugPrint != NULL) {
        printf("%s",str);
        printf("%d\n",val);
    }
}

void SimpleFOCDebug::println(const __FlashStringHelper* str, int val) {
    if (_debugPrint != NULL) {
        printf("%s",(char *)str);
        printf("%d\n",val);
    }
}


void SimpleFOCDebug::print(const char* str) {
    if (_debugPrint != NULL) {
        printf(str);
    }
}


void SimpleFOCDebug::print(const __FlashStringHelper* str) {
    if (_debugPrint != NULL) {
        printf((char *)str);
    }
}


void SimpleFOCDebug::print(int val) {
    if (_debugPrint != NULL) {
        printf("%d",val);
    }
}


void SimpleFOCDebug::print(float val) {
    if (_debugPrint != NULL) {
        printf("%f",val);
    }
}


void SimpleFOCDebug::println() {
    if (_debugPrint != NULL) {
        printf("\n");
    }
}

#endif
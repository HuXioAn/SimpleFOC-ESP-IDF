
#ifndef _IDF_SERIAL_H_
#define _IDF_SERIAL_H_

#include "../communication/SimpleFOCDebug.h"

//In order to keep simplefoc as it was, we need to implement classes like STtream\Print partly

class Stream {
public:
    void println(const __FlashStringHelper* msg);
    void println(const char* msg);
    void println(const __FlashStringHelper* msg, float val);
    void println(const char* msg, float val);
    void println(const __FlashStringHelper* msg, int val);
    void println(const char* msg, int val);
    void println();
    void println(int val);
    void println(float val);

    void print(const char* msg);
    void print(const __FlashStringHelper* msg);
    void print(int val);
    void print(float val);
};



#endif
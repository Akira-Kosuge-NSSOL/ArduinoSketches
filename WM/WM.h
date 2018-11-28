#ifndef ___WM_H___
#define ___WM_H___

#include <Arduino.h>

void test();

int generateToken(char * secret, unsigned long count, unsigned int digit);
int _generateToken(byte * key, int keySize, unsigned long count, unsigned int size) ;
int createHmacSha1(byte * key, int keySize, byte * payload, int payloadSize);

#endif

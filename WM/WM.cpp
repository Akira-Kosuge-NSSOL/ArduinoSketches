#include "WM.h"
#include <Arduino.h>
#include "mbedtls/md.h"
#include "Base32.h"

void test() {

}

int generateToken(char * secret, unsigned long count, unsigned int digit) {
  char ret[32];
  Base32 base32;
  //byte* decodedKey = NULL;

  //int keySize = base32.fromBase32((byte *)secret, strlen(secret), (byte*&)decodedKey);
//  Serial.println("--- 1.base32 decode secret. ---");
//  Serial.printf("KeySize: %d\n", keySize);
//  for(int i = 0; i < keySize; i++) {
//    char str[3];
//    sprintf(str, "%02x:", decodedKey[i]);
//    Serial.print(str);
//  }
//  Serial.println("\n-------------------------------");

//  int hash = _generateToken(decodedKey, keySize, count, digit);  
//  free(decodedKey); 
//  sprintf(ret, "%06d", hash);
  
  int decodeLength = Base32::GetDecode32Length(strlen(secret));
  char * decodedKey = (char *)malloc(decodeLength);
  
  Base32::Decode32((unsigned char *)secret, strlen(secret), (unsigned char *)decodedKey);
  Serial.println("--- 1.base32 decode secret. ---");
  Serial.printf("KeySize: %d\n", decodeLength);
  for(int i = 0; i < decodeLength; i++) {
    char str[4];
    sprintf(str, "%02x:", decodedKey[i]);
    Serial.print(str);
  }
  Serial.println("\n-------------------------------");
  free(decodedKey);
  
  return 1;
}

int _generateToken(byte * key, int keySize, unsigned long count, unsigned int size) {
  int ret;
  byte data[8];
  unsigned long value = count;
  byte * p = (byte *)&value;

  Serial.println("--- 2.reverse payload. ---");
  Serial.print("before - ");
  for(int i = 0; i < 8; i++) {
    char str[4];
    sprintf(str, "%02x:", p[i]);
    Serial.print(str);
  }
  Serial.println();

  for(int i = 0; i < 8; i++) {
    data[i] = p[7 - i];
  }

  Serial.print("after - ");
  for(int i = 0; i < 8; i++) {
    char str[4];
    sprintf(str, "%02x:", data[i]);
    Serial.print(str);
  }
  Serial.println();
  Serial.println("-------------------------------"); 

  Serial.println("--- 3.create hash. ---");
  createHmacSha1(key, keySize, data, 8);
//  Serial.print("Hash: ");
// 
//  for(int i= 0; i< 20; i++){
//      char str[3];
// 
//      sprintf(str, "%02x:", (int)hash[i]);
//      Serial.print(str);
//  }
  Serial.println("-------------------------------"); 


  return ret;
}

int createHmacSha1(byte * key, int keySize, byte * payload, int payloadSize) {
//  byte hmacResult[32];
 
//  mbedtls_md_context_t ctx;
//  mbedtls_md_type_t md_type = MBEDTLS_MD_SHA1;
// 
//  mbedtls_md_init(&ctx);
//  mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 1);
//  mbedtls_md_hmac_starts(&ctx, (const unsigned char *) key, keySize);
//  mbedtls_md_hmac_update(&ctx, (const unsigned char *) payload, payloadSize);
//  mbedtls_md_hmac_finish(&ctx, hmacResult);
//  mbedtls_md_free(&ctx);

  char *key1 = "secretKey";
  char *payload1 = "Hello HMAC SHA 256!";
  byte hmacResult[32];
 
  mbedtls_md_context_t ctx;
  mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;
 
  const size_t payloadLength = strlen(payload1);
  const size_t keyLength = strlen(key1);            
 
  mbedtls_md_init(&ctx);
  mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 1);
  mbedtls_md_hmac_starts(&ctx, (const unsigned char *) key1, keyLength);
  mbedtls_md_hmac_update(&ctx, (const unsigned char *) payload1, payloadLength);
  mbedtls_md_hmac_finish(&ctx, hmacResult);
  mbedtls_md_free(&ctx);
 
  Serial.print("Hash: ");
 
  for(int i= 0; i< sizeof(hmacResult); i++){
      char str[4];
 
      sprintf(str, "%02x:", (int)hmacResult[i]);
      Serial.print(str);
  }

  return sizeof(hmacResult);;
}

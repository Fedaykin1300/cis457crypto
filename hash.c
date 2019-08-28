#include "hash.h"

unsigned char* getHash(const char *str){
	
	unsigned char result[MD5_DIGEST_LENGTH];
	MD5(str, strlen(str),result);
	unsigned char *ret = malloc(MD5_DIGEST_LENGTH * sizeof(unsigned char*));
	
	int i;
	for(i = 0;i < MD5_DIGEST_LENGTH;i++)
		ret[i] = (result[i] & 0xff);
	return ret;	
}

void printHash(const unsigned char *str){
	int i;
	for(int i = 0;i < MD5_DIGEST_LENGTH;i++)
		printf("%02x",str[i]);
	printf("\n");
}

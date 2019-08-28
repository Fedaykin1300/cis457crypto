#include "rsa.h"
#include "hash.h"

int main(){

		
	const char* msg = "fedaykin!";

	//HASH	
	char* answer = getHash(msg);
	printHash(answer);
	free(answer);

	//RSA
	struct keyPair keys = generateKeys();

	ULL* cipher = encrypt(msg,keys.public);

	printf("Cipher Text....\n");
	int i;
	int msglen = strlen(msg);
	for(int i = 0;i < msglen;i++)
		printf("%lld\n",cipher[i]);

	char* plain = decrypt(cipher,msglen,keys.private);

	printf("Plain Text.....\n");
	printf("%s\n",plain);

	free(cipher);
	free(plain);

	return 0;
}

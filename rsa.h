#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PRIME 1000
#define MAX_SQRT 40
#define MAX_PQ 10000

typedef unsigned long long ULL;

struct privateKey{
	ULL n;
	ULL d;
};

struct publicKey{
	ULL n;
	ULL e;
};

struct keyPair{
	struct privateKey private;
	struct publicKey public;
};

ULL inverse(ULL,ULL);
ULL gcd(ULL,ULL);
int isPrime(ULL,int*,int);
ULL makeRandomLong(int*,int);
struct keyPair generateKeys();
ULL exponentiate(ULL,ULL,ULL);
ULL* encrypt(const char*,struct publicKey);
char* decrypt(const ULL*,int,struct privateKey);


#include "rsa.h"

/************************************
 * Finds Modular inverse
 * a is the num to find inverse of
 * n is the mod
 * ************************************/
ULL inverse(ULL a,ULL n){
	ULL t = 0;
	ULL r = n;
	ULL newt = 1;
	ULL newr = a;
	
	while(newr != 0){
		ULL quotient = r / newr;
		
		ULL tempt = newt;
		newt = t - (quotient * newt);
		t = tempt;
		
		ULL tempr = newr;
		newr = r - (quotient * newr);
		r = tempr;
	}

	return (t + n);
}

/**********************************
 * Finds greatest common divisor
 * *******************************/
ULL gcd(ULL a,ULL b){
	if(b == 0)
		return a;
	else
		return gcd(b, a % b);
}

/********************************
 * Tells if  anumber is prime
 * 1 is yes and 0 is no
 * (c needs bools)
 * *******************************/
int isPrime(ULL num,int *primes,int numPrimes){
	int i;
	for(i = 0;i < numPrimes;i++)
		if(num % primes[i] == 0)
			return 0;
	return 1;
}

/*****************************************
 * Creates a Random number
 * size base on MAX_PQ
 * ******************************************/
ULL makeRandomLong(int* primes,int numPrimes){

	srand(clock());

	ULL value = 1;

	while(value < MAX_PQ)
		value = (value * 10) + (rand() % 10);

	while(isPrime(value,primes,numPrimes) == 0)
		value++;

	return value;
}

/***************************************
 * Generates a RSA private and public key
 * ***************************************/
struct keyPair generateKeys(){

	//Initialize prime sieve so all are 'p' (prime)
	char sieve[MAX_PRIME] = {};
	int i;
	for(i = 0;i < MAX_PRIME;i++){
		sieve[i] = 'p';
	}

	//Run sieve, put 'n'(not prime) on all multiples
	int base;
	for(base = 2;base < MAX_SQRT;base++){
		int m = 2;
		while(base * m < MAX_PRIME){
			sieve[base*m] = 'n';
			m++;
		}
	}

	//Find the number of primes found
	int numPrimes = 0;
	for(i = 2;i < MAX_PRIME;i++)
		if(sieve[i] == 'p')
			numPrimes++;

	//Put primes into array of their own
	//used for primality(sic?) testing
	int* primes = malloc(numPrimes * sizeof(int));
	int pos = 0;
	for(i = 2;i < MAX_PRIME;i++)
		if(sieve[i] == 'p')
			primes[pos++] = i;

	//Create the values needed for keys
	ULL p = makeRandomLong(primes,numPrimes);
	ULL q = makeRandomLong(primes,numPrimes);
	ULL n = p * q;
	ULL lambda = ((p-1)*(q-1)) / gcd(p-1,(q-1) % (p-1));
	ULL e = 65537;
	ULL d = inverse(e,lambda);

	printf("P: %lld  Q: %lld  N: %lld  Lambda: %lld  E: %lld  D: %lld\n",p,q,n,lambda,e,d);

	//Create keys and keypair
	struct privateKey priv = { n , d };
	struct publicKey pub = { n , e };
	struct keyPair pair = { priv , pub };

	return pair;
}

/******************************
 * Modular exponentiation
 * base^exp mod (mod)
 * *******************************/
ULL exponentiate(ULL base,ULL exp,ULL mod){

	ULL result = 1;

	while(exp > 0){
		if((exp%2) == 1)
			result = (result * base) % mod;
		exp = exp >> 1;
		base = (base*base) % mod;
	}

	return result;
}

/************************************
 * Encrypts plaintext message into 
 * ciphertext numbers
 * **********************************/
ULL* encrypt(const char* msg,struct publicKey key){
	ULL* ret = malloc(strlen(msg) * sizeof(ULL));
	int i;
	for(i = 0;i < strlen(msg);i++){
		ULL base = (ULL) msg[i];
		ret[i] = exponentiate(base,key.e,key.n);
	}
	return ret;
}

/************************************
 * Decrypts cipher text into plaintext
 * *************************************/
char* decrypt(const ULL* cipher,int length,struct privateKey key){
	char* plain = malloc(length * sizeof(char));
	int i;
	for(i = 0;i < length;i++){
		ULL base = cipher[i];
		ULL p = exponentiate(base,key.d,key.n);
		plain[i] = (char) p;
	}
	return plain;
}

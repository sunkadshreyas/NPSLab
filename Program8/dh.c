#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compute(int a, int m, int n)
{
	a = a%n;
	int answer = 1;
	while(m)
	{
		if(m&1)
		{
			answer = answer * a % n;
		}
		a = a*a % n;
		m >>= 1;
	}
	return answer;
}

// C program to demonstrate Diffie-Hellman algorithm
int main()
{
	int p = 23;		// modulus
	int g = 5;		// base

	printf("Enter p(q) value : ");
	scanf("%d",&p);
	printf("Enter g(alpha) value : ");
	scanf("%d",&g);

	int a, b;	// a - Alice's Secret Key, b - Bob's Secret Key.
	int A, B;	// A - Alice's Public Key, B - Bob's Public Key

	// choose secret integer for Alice's Pivate Key (only known to Alice)
	srand(time(0));
	a = rand();		// or use rand()
	printf("\nEnter Alice's private key : ");
	scanf("%d",&a);

	// Calculate Alice's Public Key (Alice will send A to Bob)
	// public key = g^prikey mod p
	A = compute(g, a, p); 

	printf("\nAlice's private key : %d.\n", a);
	printf("Alice's public key : %d.\n", A);

	// choose secret integer for Bob's Pivate Key (only known to Bob)
	// srand(time(0))	;
	b = rand();		// or use rand()
	printf("\nEnter Bob's private key : ");
	scanf("%d",&b);

	// Calculate Bob's Public Key (Bob will send B to Alice)
	B = compute(g, b, p);

	printf("\nBob's private key : %d.\n", b);
	printf("Bob's public key : %d.\n",B);

	// Alice and Bob Exchanges their Public Key A & B with each other

	// To Find Secret key use public key of other person
	// key = publickey ^ privatekey mod p
	int keyA = compute(B, a, p);
	int keyB = compute(A, b, p);

	printf("\nAlice's Secret Key is %d\nBob's Secret Key is %d\n\n", keyA, keyB);

	return 0;
}
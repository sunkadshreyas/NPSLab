#include<stdio.h>
#include<stdlib.h>

unsigned fields[10];

unsigned short computeCheckSum()
{
	int i, sum=0;

	for(i=0; i<9; i++)
	{
		// printf("Enter field %d\n", i+1);
		scanf("%x", &fields[i]);
		sum += (unsigned short)fields[i];
		while(sum>>16)
		{
			sum = (sum & 0xFFFF) + (sum >> 16);
		}
	}
	sum = ~sum;
	return (unsigned short)sum;
}

// 4500 003c 1c46 4000 b1e6 ac10 0a63 ac10 0a0c

int main()
{
	unsigned short result1, result2;
	// sender
	printf("Enter IP address in 16 bit word format at sender side : \n");
	result1 = computeCheckSum();
	printf("CheckSum at sender side : %x\n\n", result1);
	// receiver
	printf("Enter IP address in 16 bit word format at receiver side: \n");
	result2 = computeCheckSum();
	printf("CheckSum at receiver side : %x\n\n",result2);
	if(result1 == result2)
		printf("No error\n");
	else
		printf("Error detected\n");
}

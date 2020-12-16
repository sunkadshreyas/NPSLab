#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void main()
{
    int maxp=6;
    int a[50],temp[70],temp2[70];
    int t,i,j,k,nd,n,nh,sum=0,pos=0;

    printf("Enter Length of Data String: ");
    scanf("%d",&nd);
    printf("Enter Data String: ");
    for(i=0;i<nd;i++)
    {
        scanf("%d",&a[i]);
    }
    //printf("-----------------------------------\n",nd);
    for(i=0,j=0;i<nd;i++)
    {
        for(k=0;k<maxp;k++)
        {
            t=pow(2,k)-1;
            if(j==t)
            {
                temp[j]=0;
                j++;
            }
        }
        temp[j]=a[i];
        j++;
    }
    for(i=0; i<j; i++)
    {
        // printf("%d",temp[i]);
    }
    // printf("\n");
    nh=j;
    printf("\nTotal length of message  : %d\n",nh);
    n=nh-nd;
    printf("Number of redundant Bits: %d \n",n);
    // printf("N : %d.\n",n);
    // printf("nh : %d.\n", nh);
    // printf("nd : %d\n", nd);
    int b[n];
    int m=n-1;
    for(i=0; i<j; i++)
    {
        // printf("%d",temp[i]);
    }
    // printf("\n");
    printf("Redundant bits are : ");
    for(k=0;k<n;k++)
    {
        t=pow(2,k)-1;

        for(i=t;i<nh;)
        {
            for(j=0;j<=t;j++)
            {
                sum=sum+temp[i];
                i++;
                if(i>=nh)
                    break;
            }

            if(i>=nh)
                break;

            for(j=0;j<=t;j++)
            {
                i++;
                if(i>=nh)
                    break;
            }

            if(i>=nh)
                break;
        }
        temp[t]=sum%2;
        sum=0;
        printf("%d ",temp[t]);
        // printf("P%d: %d\n",t+1,temp[t]);
    }


    printf("\nCodeword at sender side:   ");
    for(i=0;i<nh;i++)
    {
        printf("%d ",temp[i]);
    }
    printf("\n");

    printf("\nEnter the Codeword at receiver side: ");
    for(i=0;i<nh;i++)
    {
        scanf("%d",&temp2[i]);
    }
    sum=0;
    printf("Syndrome bits : ");
    for(k=0;k<n;k++)
    {
        t=pow(2,k)-1;

        for(i=t;i<nh;)
        {
            for(j=0;j<=t;j++)
            {
                sum=sum+temp2[i];
                i++;
                if(i>=nh)
                    break;
            }

            if(i>=nh)
                break;

            for(j=0;j<=t;j++)
            {
                i++;
                if(i>=nh)
                    break;
            }

            if(i>=nh)
                break;
        }
        b[m]=sum%2;
        sum=0;
        printf("%d ",b[m]);
        //printf("P%d: %d\n",t+1,b[m]);
        m--;
    }
    printf("\n");
    for(m=0;m<n;m++)
    {
        pos=pos+b[n-m-1]*pow(2,m);
    }
    int error_present = 0;
    for(i=0; i<n; i++)
    {
        if(b[i]!=0)
        {
            error_present = 1;
            break;
        }
    }
    if(error_present == 0)
    {
        printf("No error is present\n");
    }
    else
    {
        printf("Error is present at bit : %d\n",pos-1);
        if(temp2[pos-1]==0)
            temp2[pos-1]=1;
        else
            temp2[pos-1]=0;

       printf("\nCorrect codeword is :  ");
        for(i=0;i<nh;i++)
        {
           printf("%d ",temp2[i]);
        }
        printf("\n");
    }

    //printf("\n-----------------------------------\n",nd);
}

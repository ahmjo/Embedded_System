#include <stdio.h>

void max_ones(int num)
{
	int i,j,count=0,max=0;

	for (i=31;i>=0;i--)
	{
		j=num>>i;
		if (j&1)
		{
			count++;
		}
		else
		{
			if (count>max)
			{
				max=count;
			}
			count=0;
		}
	}
	printf("the count of max ones between two zero in binary of number: %d",max);
}

int main()
	{
		int num;
		printf("Enter a number: ");
		scanf("%d",&num);
		max_ones(num);
}
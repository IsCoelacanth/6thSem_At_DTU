#include<stdio.h>
#include<string.h>
int main()
{
	char frame[50][50], str[50][50];
	char flag[10];
	strcpy(flag, "flag");
	char esc[10];
	strcpy(esc, "esc");
	int i, j, k = 0, n;

	strcpy(frame[k++], "flag");
	printf("Enter no.of String :\t");
	scanf("%d", &n);
	printf("Enter String \n");
	for (i = 0; i <= n; i++)
	{
		gets(str[i]);
	}
	printf("You entered :\n");
	for (i = 0; i <= n; i++)
	{
		puts(str[i]);
	}

	printf("\n");
	for (i = 1; i <= n; i++)
	{
		if (strcmp(str[i], flag) != 0 && strcmp(str[i], esc) != 0)
		{
			strcpy(frame[k++], str[i]);
		}
		else
		{
			strcpy(frame[k++], "esc");
			strcpy(frame[k++], str[i]);
		}
	}

	strcpy(frame[k++], "flag");
	//frame[k++]='\0';
	printf("------------------------------\n");
	printf("Byte stuffing at sender side:\n\n");
	printf("------------------------------\n");
	for (i = 0; i<k; i++)
	{
		printf("%s\t", frame[i]);
	}
}
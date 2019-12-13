#include<stdio.h>
#include<stdlib.h>

struct cliendata
{
	int acctNum;
	char lastname[15];
	char firstname[10];
	double balance;
};

int main(void)
{
	FILE *pread, *pwrite;
	FILE *cfptr;
	int cnt = 0;
	struct cliendata client = { 0,"","",0.0 };
	pread = fopen("c://credit.txt", "r");
	if (NULL == pread)
	{
		return 0;
	}
	pwrite = fopen("c://credit_bin.txt", "wb");
	if (NULL == pwrite)
	{
		fclose(pread);
		return 0;
	}
	while (!feof(pread))
	{
		fscanf(pread, "%d%s%S%lf", &client.acctNum, client.lastname, client.firstname, &client.balance);
		fwrite(&client, sizeof(struct cliendata), 1, pwrite);
		printf("%-6d%-16s%-11s%10.2f\n",client.acctNum,client.lastname,client.firstname,client.balance);
	}
	fclose(pread);
	fclose(pwrite);
	printf("以讀取文字檔ascii,並轉存二進位檔案\n\n");
	system("pause");
	printf("\n讀取二進位資料，並格式化輸出");
	if ((cfptr = fopen("c://credit_bin.txt", "rb")) == NULL)
		printf("file could not be opened.\n");
	else
	{
		printf("%-6s%-16s%-11s%10s\n", "Acct", "LAST NAME", "first name", "balance");
		cnt = fread(&client, sizeof(struct cliendata), 1, cfptr);
		while (cnt>0)
		{
			printf("%-6d%-16s%-11s%10.2f\n", client.acctNum, client.lastname, client.firstname, client.balance);
			cnt = fread(&client, sizeof(struct cliendata), 1, cfptr);

		}
		fclose(cfptr);

	}
	system("pause");
	return 0;
}
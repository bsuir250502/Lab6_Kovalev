#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int num_check()
{
    char buffer[20], *bufferPointer;
    int num;
    bufferPointer = buffer;
    do {
        fgets(buffer, 20, stdin);
        num = strtol(buffer, &bufferPointer, 10);
        if (*bufferPointer != '\n' || num>10000) {
            printf("Incorrect value. Try again: ");
            continue;
        }
        break;
    } while (1);
    return num;
}

void file_create()
{
	FILE *f;
	int i;
	if(!(f = fopen("lab6.bin", "w+b")))
	{
		puts("Can't create a file!");
		return;
	}
	for(i=1; i<100000; i*=10)
	{
		fwrite(&i, sizeof(int), 1, f);
	}
	fclose(f);
}

void file_change()
{
	FILE *f;
	int new_num, file_num, cur_num, n = 0, n1, ident = 0;
	if(!(f = fopen("lab6.bin", "r+b")))
	{
		puts("Can't open a file!");
		return;
	}
	puts("\nPut the number, please (<10000): ");
	new_num = num_check();
	do
	{
		fread(&file_num, sizeof(int), 1, f);
		if(file_num == new_num)
		{
			puts("There's such a number. Repeat input");
			ident = 1;
			break;
		}
		else if(file_num > new_num)
		{

			do
			{
				rewind(f);
				for(n1 = n; n1>0; n1--)
				{
					fread(&cur_num, sizeof(int), 1, f);
				}
				fwrite(&new_num, sizeof(int), 1, f);
				new_num = file_num;
				n++;
			} while(fread(&file_num, sizeof(int), 1, f));
			break;
		}
		else
		{
			n++;
		}
	} while(file_num);
	if(!ident) fwrite(&new_num, sizeof(int), 1, f);
	fclose(f);
}

void file_output()
{
	FILE *f;
	int n;
	if(!(f = fopen("lab6.bin", "r+b")))
	{
		puts("Can't open a file!");
		return;
	}
	printf("Current numbers in file are:");
	while(fread(&n, sizeof(int), 1, f))
	{
		printf(" %d ", n);
	}
	fclose(f);
}

int atoi_change()
{
    int identifier;
    while(1)
    {
	printf("(yes - 1/no - 0) ");
	identifier = num_check();
	if(identifier == 1 || identifier == 0) { break; }
	puts("It's not correct. Please, input data again.");
    }
    return identifier;
}



int main(int argc, char** argv)
{
	int ident;
	file_create();
	do
	{
		file_output();
		file_change();
		file_output();
		puts("\nWant to continue?");
		ident = atoi_change();
	} while(ident);
	return 0;
}

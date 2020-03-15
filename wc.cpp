#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>


int count_char(char* name) {
	FILE* fp;
	int num = 0;
	char find;
	//errno_t err;
	if ((fp = fopen(name, "r")) == NULL) {
		printf("File open failed\n");
		return -1;
	}
	while ((find = getc(fp)) != EOF) {
		num++;
	}
	fclose(fp);
	return num;
}

int count_word(char* name) {
	FILE* fp;
	int num, word, t_word = 0;
	char find;
	//errno_t err;
	num = 0;
	word = 0;
	if ((fp = fopen(name, "r")) == NULL) {
		printf("File open failed\n");
		return -1;
	}
	while ((find = getc(fp)) != EOF) {
		num++;
		if ((find >= 'A' && find <= 'Z') || (find >= 'a' && find <= 'z')) {
			t_word++;
			if (t_word < num) {
				t_word = num;
				word++;
			}
		}
	}
	fclose(fp);
	return word;
}

int count_line(char* name) {
	FILE* fp;
	int line = 0;
	char find;
	//errno_t err;
	if ((fp = fopen(name, "r")) == NULL) {
		printf("File open failed\n");
		return -1;
	}
	while ((find = getc(fp)) != EOF) {
		if (find == '\n') {
			line++;
		}
	}
	fclose(fp);
	return line+1;
}

int count_empty_line(char* name) {
	FILE* fp;
	int e_line = 0;
	int i,sign = 0;
	int common_sign, special_sign;
	char find;
	char word[1000];
	common_sign = 0;
	special_sign = 0;
	//errno_t err;
	if ((fp = fopen(name, "r")) == NULL) {
		printf("File open failed\n");
		return -1;
	}
	while ((find = getc(fp)) != EOF) {
		word[sign] = find;
		++sign;
		if(find == '\n'){
			common_sign = 0;
			special_sign = 0;
			for(i = 0; i < sign; i++){
				if(word[i] == ' '|| word[i] == '	' || word[i] == '\n'){
					++common_sign;
				}
				else{
					++special_sign;
				}
			}
			if(common_sign == sign || special_sign == 1) ++e_line;
			sign = 0;
		}
	}
	common_sign = 0;
    special_sign = 0;
	for(i = 0; i < sign; i++){
		if(word[i] == ' '|| word[i] == '	' || word[i] == '\n'){
			++common_sign;
		}
		else{
			++special_sign;
		}
	}
	if(common_sign == sign || special_sign == 1) ++e_line;
	fclose(fp);
	return e_line;
}

int count_notes_line(char* name) {
	FILE* fp;
	int n_line = 0;
	int i,sign = 0;
	int flag = 0;
	char find;
	char word[1000];
	//errno_t err;
	if ((fp = fopen(name, "r")) == NULL) {
		printf("File open failed\n");
		return -1;
	}
	while ((find = getc(fp)) != EOF) {
		word[sign] = find;
		++sign;
		if(find == '\n'){
			for(i = 0; i < sign; i++){
				if((i == 0 || i == 1) && (word[i] == '/' && word[i+1] == '/')) ++n_line;
			}
			sign = 0;
		}
	}
	for(i = 0; i < sign; i++){
		if((i == 0 || i == 1) && (word[i] == '/' && word[i+1] == '/')) ++n_line;
	}
	fclose(fp);
	return n_line;
}

int main(int argc,char *argv[]) {
	//char name[1000];
	//char order[1000];
	//scanf("%s",order);
	//scanf("%s",name);
	if (strcmp(argv[1], "-c") == 0) {
		printf("character %d", count_char(argv[2]));
		printf("\n");
	}
	else if (strcmp(argv[1], "-w") == 0) {
		printf("word %d", count_word(argv[2]));
		printf("\n");
	}
	else if (strcmp(argv[1], "-l") == 0) {
		printf("line: %d", count_line(argv[2]));
		printf("\n");
	}
	else if (strcmp(argv[1], "-a") == 0) {
		printf("empty_line: %d, Comment lines using single line annotators: %d", count_empty_line(argv[2]),count_notes_line(argv[2]));
		printf("\n");
	}
	else printf("we are working\n");
	return 0;
}

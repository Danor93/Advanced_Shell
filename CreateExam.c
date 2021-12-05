#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define N 256

/**int CreateExam(char *name, char *course, char *test_writer)**/

int main(int argc, char* argv[]) {

	int fd1, numofquest, wbytes, i, j;
	char *str, *str2 = { ".txt" }, num[5], *Question = { "\nQuestion" }, dot[2] =
			{ "." }, *col = { ": " };
	char buffer[N] = { 0 }, temp[N] = { 0 }, ch[2] = { "\n" }, temp2[N];
	char *token, s[2] = " ", final[N] = { "\nSuccessfully\n" };
	char name[N] = { 0 }, course[N] = { 0 }, test_writer[N] = { 0 };

	strcpy(name, argv[1]);
	strcpy(course, argv[2]);
	strcpy(test_writer, argv[3]);

	strcat(final, test_writer);

//=====================================
	// *creating the file
	str = (char*) malloc((sizeof(char) * strlen(name)) + sizeof(char) * 6);

	if (str == NULL) {
		perror("Memory allocation failed!\n");
		return (-1);
	}

	str = name;
	strcat(str, str2);	//make the name "name.txt" that we can accsual open
	if ((fd1 = open(str, O_WRONLY | O_CREAT, 0777)) == -1) {
		perror("Error opening File\n");
		free(str);
		exit(1);
	}

//================================

//================================
	// *start build the buffer to writing the course name and
	// the number of questions to the file.
	strcpy(buffer, course);
	strcat(buffer, ch);

	printf("Enter Number of Questions:\n");
	scanf("%d", &numofquest);
	getchar();

	sprintf(num,"%d",numofquest);
	strcat(buffer, num);
	strcat(buffer, ch);
	if ((wbytes = write(fd1, buffer, strlen(buffer))) == -1) {
		perror("write error\n");
		free(str);
		exit(1);
	}
//=====================================
// *this loop build the file using 2 buffers 1 for the questions
// and one for the answers

	for (i = 1; i <= numofquest; i++) {
		char in_put[N][N], ans[N] = { 0 }, quest[N], buffer2[N] = { 0 },
				buffer3[N] = { 0 };
        int count = 0;
		printf("Insert Question %d:", i);
		fgets(quest, N, stdin);
		strcpy(buffer3, Question);
		sprintf(num,"%d",i);
		strcat(buffer3, num);
		strcat(buffer3, col);
		strcat(buffer3, ch);
		token = strtok(quest, s);
		while ((token != NULL) && count < N) { // in case that the quastion is more than 1 word
			strcpy(in_put[count], token);
			strcat(buffer3, in_put[count]);
			count++;
			strcat(buffer3, s);
			token = strtok(NULL, s);

		}
		if ((wbytes = write(fd1, buffer3, strlen(buffer3))) == -1) { // buffer 3 is the quastion buffer
			perror("write error\n");
			free(str);
			exit(1);
		}
		printf("Insert 4 Answers:\n");
		for (j = 1; j <= 4; j++) { //this loop occured us to enter answers and write it 1 by 1 to the file.
								   // buffer 2 is for the answers

            char buffer2[N] = { 0 };
			printf("%d. ", j);
			scanf("%s", ans);
			getchar();
			if (j == 1) {
				strcpy(buffer2, ch);
			} else {
				strcat(buffer2, ch);
			}
			sprintf(num,"%d",j);

			strcat(buffer2, num);

			strcat(buffer2, dot);

			strcat(buffer2, ans);

			strcat(buffer2, ch);
			if ((wbytes = write(fd1, buffer2, strlen(buffer2) - 1)) == -1) {//wrinting the answers to the file
				perror("write error\n");
				free(str);
				exit(1);
			}

		}
		printf("\n");

	}

	if ((wbytes = write(fd1, final, strlen(final))) == -1) {//wrinting the answers to the file
		perror("write error\n");
		free(str);
		exit(1);
	}

//end of loop
//=======================================================

	close(fd1); // closing the file to save changes
	return 1;
}

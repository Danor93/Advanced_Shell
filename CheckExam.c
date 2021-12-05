#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define N 256

/**int CheckExam(char* test_name, char* name)**/
int main(int argc, char* argv[]) {

	char *str, *str2 = { ".txt" }, buffer[N] = { 0 }, *token, s[2] = "\n",
			s1[2] = "_", out_name1[N] = ("Grade_"), in[N] = { "Sol_" },
			true[N][N] = { 0 }, ans[N][N] = { 0 }, final[N] = { 0 }, out[4] = {
					0 };
	int fd1, fd2, rbytes, wbytes, i, j, numofques = 0, sum = 0, answers = 0,
			count = 0;

	char test_name[N] = { 0 }, name[N] = { 0 };

	strcpy(test_name, argv[1]);
	strcpy(name, argv[2]);

	str = (char*) malloc((sizeof(char) * strlen(test_name)) + sizeof(char) * 6);

	if (str == NULL) {
		perror("Memory allocation failed!\n");
		return (-1);
	}

	strcpy(str, test_name);
	strcat(str, str2); //str=test.txt
	strcat(out_name1, name); //out=Grade_name
	strcat(out_name1, s1); //out=Grade_name_
	strcat(out_name1, str); //out= Grade_name_test,txt
	strcat(in, str); //in = Sol_test.txt

	strcpy(final, name);
	strcat(final, s1);
	strcat(final, str); //final = name_test.txt

	if ((fd1 = open(in, O_RDONLY, 0777)) == -1) {
		perror("Error opening File\n");
		free(str);
		exit(1);
	}

	if ((rbytes = read(fd1, buffer, N)) == -1) {
		perror("Cannot read the file!\n");
		exit(-1);
	}

	token = strtok(buffer, s); //to divide the input until the \n (in case the number of questions is more then 1 digit.
	while ((token != NULL) && (count < N)) {
		strcpy(true[count], token);
		count++;
		token = strtok(NULL, s);
	} ////true contain the right answers

	close(fd1);
	if ((fd1 = open(final, O_RDONLY, 0777)) == -1) {
		perror("Error opening File\n");
		free(str);
		exit(1);
	}

	if ((rbytes = read(fd1, buffer, N)) == -1) {
		perror("Cannot read the file!\n");
		exit(-1);
	}
	count = 0;
	token = strtok(buffer, s); //to divide the input until the \n (in case the number of questions is more then 1 digit.
	while ((token != NULL) && (count < N)) {
		strcpy(ans[count], token);
		count++;
		token = strtok(NULL, s);
	} ////true contain the right answers

	close(fd1);

	//count is the num of quest

	for (i = 0; i < count; i++) {
		if (strcmp(ans[i], true[i]) == 0) {
			answers++;
		}
	}

	out[0] = ('0' + answers);
	out[1] = ('/');
	out[2] = ('0' + count);
	out[3] = ('\0');

	if ((fd1 = open(out_name1, O_WRONLY | O_CREAT, 0777)) == -1) {
		perror("Error opening File\n");
		free(str);
		exit(1);
	}

	if ((wbytes = write(fd1, out, strlen(out))) == -1) { //wrinting the answers to the file
		perror("write error\n");
		free(str);
		exit(1);
	}

	close(fd1);

	return 1;
}




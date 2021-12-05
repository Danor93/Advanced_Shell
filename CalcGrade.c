#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define N 256

/**int CalcGrade(char* test_name, char* name)**/

int main(int argc, char* argv[]) {
	char *str, *str2 = { ".txt" }, buffer[N] = { 0 }, *token, s[2] = "\n",
			s2[2] = " ", s1[2] = "_", out_name1[N] = ("Grade_"), in[N] = {
					"\nFinal Grade:" }, true[N][N] = { 0 }, ans[N] = { 0 },
			final[3] = { 0 }, out[4] = { 0 };
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

	if ((fd1 = open(out_name1, O_RDONLY, 0777)) == -1) {
		printf("%s is not Found!\n",test_name);
		free(str);
		exit(1);
	}

	if ((rbytes = read(fd1, buffer, N)) == -1) {
		perror("Cannot read the file!\n");
		exit(-1);
	}
	close(fd1);

	sum = (buffer[0] - '0');
	answers = (buffer[2] - '0');

	strcat(buffer, in);

	count = (100 / answers) * sum;
	sum = count;
	if (count < 100) {

		final[1] = ((count % 10) + '0');
		final[0] = ((count / 10) + '0');
		final[2] = '\0';
		strcat(buffer, s2);
		strcat(buffer, final);
		strcat(buffer, "/100");

	} else {
		strcat(buffer, "100");
		strcat(buffer, "/100");
	}

	if ((fd1 = open(out_name1, O_WRONLY | O_CREAT, 0777)) == -1) {
		perror("Error opening File\n");
		free(str);
		exit(1);
	}

	if ((wbytes = write(fd1, buffer, strlen(buffer))) == -1) { //wrinting the answers to the file
		perror("write error\n");
		free(str);
		exit(1);
	}

	printf("%s\n", name);
	printf("%s", test_name);
	printf("\nYour final grade is %d", sum);

	close(fd1);

	return 1;

}


#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define N 256

/*int SolExam(char *file_name)*/
int main(int argc, char* argv[]) {
	char *str, *str2 = { ".txt" }, buffer[N] = { 0 }, *token, s[2] = "\n",
			out_name1[N] = ("Sol_"), number[N] = { 0 }, final[N] = { 0 }, *out,
			file_name[N] = { 0 };
	int fd1, fd2, rbytes, wbytes, i, j, numofques = 0, flag = 0, arr[N] = { 0 },
			count = 0;

	strcpy(file_name, argv[1]);

	str = (char*) malloc((sizeof(char) * strlen(file_name)) + sizeof(char) * 6);

	if (str == NULL) {
		perror("Memory allocation failed!\n");
		return (-1);
	}

	strcpy(str, file_name);
	strcat(str, str2);	//make the name "name.txt" that we can accsual open
	//strcat(out, str);	//to make the new file Sol_neme,txt
	if ((fd1 = open(str, O_RDONLY, 0777)) == -1) {
		perror("Error opening File\n");
		free(str);
		exit(1);
	}
	if ((rbytes = read(fd1, buffer, N)) == -1) {
		perror("Cannot read the file!\n");
		exit(-1);
	}
	close(fd1);

	token = strtok(buffer, s); //to divide the input until the \n (in case the number of questions is more then 1 digit.
	while ((token != NULL) && (count < 2)) {
		strcpy(number, token);
		count++;
		token = strtok(NULL, s);
	} // now the variable of number is in number

	numofques = atoi(number);

//================================

	strcat(out_name1, str); //make new file name

	if ((fd2 = open(out_name1, O_WRONLY | O_CREAT, 0777)) == -1) {
		perror("Error opening File\n");
		free(str);
		exit(1);
	}
	j = 0;
	for (i = 0; i < numofques + 1; i = i + 2) {
		printf("Insert True Sol for Question %d:\n", j + 1);
		scanf("%s", (final + i));
		getchar();
		final[i + 1] = '\n';
		j++;
	}

	if ((wbytes = write(fd2, final, strlen(final))) == -1) { //wrinting the answers to the file
		perror("write error\n");
		free(str);
		exit(1);
	}
	close(fd2);

	return 1;

}


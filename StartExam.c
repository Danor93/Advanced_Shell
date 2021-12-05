#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define N 256

/*int StartExam(char *file_name, char*name)*/

int main(int argc, char* argv[]) {
	char *str, *str2 = { ".txt" }, buffer[N] = { 0 }, *token, s[2] = "\n",
			number[N] = { 0 }, temp[N] = { 0 }, out[N] = { 0 }, Q, A, new_f[N] =
					{ 0 }, final[N] = { 0 };
	int fd1, fd2, rbytes, wbytes, i, j, numofques = 0, flag = 0, arr[N] = { 0 },
			count = 0;

	char file_name[N] = { 0 }, name[N] = { 0 };

	strcpy(file_name, argv[1]);
	strcpy(name, argv[2]);

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

	strcpy(new_f, name);
	strcat(new_f, "_");
	strcat(new_f, str);

	if ((fd1 = open(new_f, O_WRONLY | O_CREAT, 0777)) == -1) {
		perror("Error opening File\n");
		free(str);
		exit(1);
	}

	strcpy(number, buffer);
	token = strtok(number, s); //to divide the input until the \n (in case the number of questions is more then 1 digit.
	while ((token != NULL) && (count < 2)) {
		strcpy(temp, token);
		count++;
		token = strtok(NULL, s);
	} // now the variable of number is in number

	numofques = atoi(temp);

	for (i = 0; i < strlen(buffer); i++) {
		printf("%c", buffer[i]);
	}

	printf("\n\nInsert number of Question and sol:\n");
	for (i = 0; i < numofques; i++) {
		scanf("%c", &Q);    //out [0] = A
		getchar();
		scanf("%c", &A);
		getchar();
		out[(Q - '0') - 1] = A;
	}
	j = 0;
	for (i = 0; i < 2 * numofques; i = i + 2) {

		final[i] = out[j];
		final[i + 1] = '\n';
		j++;
	}

	//out[strlen(out) + 1] = '\0';

	if ((wbytes = write(fd1, final, strlen(final))) == -1) { //wrinting the answers to the file
		perror("write error\n");
		free(str);
		exit(1);
	}

	//sleep(2);
	close(fd1);

	return 0;

}


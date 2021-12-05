#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define N 256

int procs(char *path, char args[][N], int n);

int main() {
	int i, flag2 = 1;
	do {
		char s[2] = " ", *token, args[6][N], path[N] = "/bin/", path2[N] =
				"/home/braude/", temp[N] = { 0 };
		char buffer[N] = { 0 };
		int count = 0, flag = 0, i, fd_o, fd_s, outflag = 0, mark, pid;

		printf("\nAdvShell>");
		fgets(buffer, N, stdin);

		token = strtok(buffer, s); //to divide the input until the space.
		while ((token != NULL) && (count < 6)) {
			strcpy(args[count], token);
			count++;
			token = strtok(NULL, s);
		}

		args[count - 1][strlen(args[count - 1]) - 1] = '\0'; //to remove the enter.

		strcat(path, args[0]);
		strcpy(temp, path2);
		strcat(temp, args[0]);

		//check the case when the output is include ">".
		for (i = 0; i < count; i++) {
			if (!(strcmp(args[i], ">"))) {
				if ((fd_o = open(args[i + 1], O_WRONLY | O_CREAT, 0777))
						== -1) {
					perror("open File\n");
					return (-1);
				}
				fd_s = dup(1); //saves the default screen fd
				dup2(fd_o, 1); //replace the default output with the opened file.
				outflag = 1; //indicate that the output has been changed.
				count -= 2; //for ">" and "new stdout"
			}
		}

		if (strcmp("CreateExam", args[0]) == 0) {

			if ((pid = fork()) == 0) {
				execl(temp, args[0], args[1], args[2], args[3], NULL);
				perror("Wrong input!\n");
				exit(1);
			}
			flag = 1;
		}

		if (strcmp("SolExam", args[0]) == 0) {

			if ((pid = fork()) == 0) {
				execl(temp, args[0], args[1], NULL);
				perror("Wrong input!\n");
				exit(1);
			}
			flag = 1;
		}

		if (strcmp("StartExam", args[0]) == 0) {

			if ((pid = fork()) == 0) {
				execl(temp, args[0], args[1], args[2], NULL);
				perror("Wrong input!\n");
				exit(1);
			}
			flag = 1;
		}

		if (strcmp("CheckExam", args[0]) == 0) {

			if ((pid = fork()) == 0) {
				execl(temp, args[0], args[1], args[2], NULL);
				perror("Wrong input!\n");
				exit(1);
			}
			flag = 1;
		}

		if (strcmp("CalcGrade", args[0]) == 0) {

			if ((pid = fork()) == 0) {
				execl(temp, args[0], args[1], args[2], NULL);
				perror("Wrong input!\n");
				exit(1);
			}
			flag = 1;
		}

		if (strcmp("GoodBye", args[0]) == 0) {
			flag = 1;
			flag2 = 0;
		}

		if (!flag) {
			if (procs(path, args, count - 1) == -1) {
				printf("too many/less arguments!\n");
			}
		}

		if (outflag == 1) {
			dup2(fd_s, 1); /*to make sure that stdout default is the screen.*/
			close(fd_o);
		}
		wait();

	} while (flag2);

	return 0;

}

int procs(char *path, char args[][N], int n) {/*this function will check if the commands are from the shell system. */
	int pid;

	if ((pid = fork()) == -1) {
		perror("fork() failed.");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) {

		switch (n) {
		case 0:/*for zero arguments*/

			execlp(args[0], args[1], NULL);
			printf("Not Supported!\n");
			exit(0);
			break;

		case 1: /*for 1 arguments*/

			execl(path, args[0], args[1], NULL);
			printf("Not Supported!\n");
			exit(0);
			break;

		case 2: /*for 2 arguments*/

			execl(path, args[0], args[1], args[2], NULL);
			printf("Not Supported!\n");
			exit(0);
			break;

		case 3:/*for 3 arguments*/

			execl(path, args[0], args[1], args[2], args[3], NULL);
			printf("Not Supported!\n");
			exit(0);
			break;

		default:
			exit(0);
		}
	}

	wait();
	return 0;
}

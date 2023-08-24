#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define status "git status"
#define add "git add ."
#define commit "git commit -m \""
#define push "git push"
int git_status();
int git_add();
int git_commit();
int git_push();

int main() {
	git_status();
	printf("Continue(add, commit)?\n y/n\n");
	if (!git_add())
		return 0;
	printf("Continue(add, commit)?\n y/n\n");
	git_commit();
	printf("Continue(add, commit)?\n y/n\n");
	git_push();
	return 0;
}


int git_status() {
	system(status);
}


int git_add() {
	printf("Continue(add, commit)?\n y/n\n");
	char answer;
	scanf("%c", &answer);
	if (answer != 'y')
		return 1;
	system(add);
}


int git_commit() {
	printf("¬ведите комментарий\n");
	char* comment = malloc(128 * sizeof(char));
	char message[200] = { '\0' };
	char next_letter;
	int i = 0;
	do {
		scanf("%c", &next_letter);
		if (next_letter != '\n') {
			comment[i++] = next_letter;
		}

	} while (next_letter != '\n');
	comment[i] = '\0';
	strcat(message, commit);
	strcat(message, comment);
	strcat(message, "\"");
	system(message);
	free(comment);
	return 0;
}


int git_push() {
	printf("Push?\n y/n\n");
	char answer;
	scanf("%c", &answer);
	if (answer != 'y')
		return 1;
	printf("¬ведите название ветки\n");
	char* branch = malloc(128 * sizeof(char));
	char message[200] = { '\0' }, next_letter;
	int i = 0;
	do {
		scanf("%c", &next_letter);
		if (next_letter != '\n') {
			branch[i++] = next_letter;
		}

	} while (next_letter != '\n');
	strcat(message, push);
	strcat(message, branch);
	system(message);
	free(branch);
	return 0;
}
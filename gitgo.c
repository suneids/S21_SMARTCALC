#include <stdio.h>
#define status "git status"
#define add "git add ."
#define commit "git commit -m"
#define push "git push"

int main() {
	system(status);
	printf("\ny/n\n");
	char answer;
	scanf("%c", &answer);
	if (answer != 'y')
		return 0;
	system(add);
	printf("¬ведите название ветки\n");

	system();

	return 0;
}

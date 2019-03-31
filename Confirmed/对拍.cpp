#include <cstdio>
#include <cstdlib>

int main() {
	for (int i = 1; ; i++) {
		system("maker.exe > data.in");
		system("std.exe < data.in > data.ans");
		system("Doncoi.exe < data.in > data.out");
		if (system("fc data.ans data.out > 1") != 0) {
			printf("Wrong_Answer on #%d\n", i);
			break;
		} else {
			printf("Accepted on #%d\n", i);
		}
	}

	return 0;
}
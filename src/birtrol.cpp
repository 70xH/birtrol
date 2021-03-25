#include <cstdlib>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

void u_choice(void);
void help(void);
void max_brigthness(void);
void current_brightness(void);
void inc(char *val);
void dec(char *val);

string dir_path = "/sys/class/backlight/amdgpu_bl1/";

void u_choice() {
		string file_path = dir_path + "brightness";
		FILE *file = fopen(file_path.c_str(), "w+");

		if (file == NULL) {
				fprintf(stderr, "failed to read the file\n");
				exit(-1);
		}

		char c;
		printf("Current brightness: ");
		while ((c = fgetc(file)) != EOF) {
				printf("%c", c);
		}

		char ch = 'n';

		printf("Change brightness (y/N): ");
		scanf("%c", &ch);

		if (ch == 'y') {
				printf("Change the brightness to: ");
				int num;
				scanf("%d", &num);
				
				fprintf(file, "%d", num);
		}

		fclose(file);
}

void help() {
		printf("help section\n");
}

void dec(char *val) {
		string file_path = dir_path + "brightness";
		FILE *file = fopen(file_path.c_str(), "w+");

		if (file == NULL) {
				fprintf(stderr, "failed to open file\n");
				exit(-1);
		}

		char c;
		string read_num;

		while ( (c = fgetc(file)) != EOF ) {
				read_num += c;
		}

		int num = atoi(read_num.c_str()) - atoi(val);
		fprintf(file, "%d", num);

		fclose(file);
}

void inc(char *val) {
		string file_path = dir_path + "brightness";
		FILE *file = fopen(file_path.c_str(), "w+");

		if (file == NULL) {
				fprintf(stderr, "failed to open file\n");
				exit(-1);
		}

		char c;
		string read_num;

		while ( (c = fgetc(file)) != EOF ) {
				read_num += c;
		}

		int num = atoi(read_num.c_str()) + atoi(val);
		fprintf(file, "%d", num);

		fclose(file);
}

void current_brightness() {
		string file_path = dir_path + "brightness";
		FILE *file = fopen(file_path.c_str(), "r");

		if (file == NULL) {
				fprintf(stderr, "failed to open file\n");
				exit(-1);
		}

		char c;

		while ( (c = fgetc(file)) != EOF ) {
				printf("%c", c);
		}

		fclose(file);
}

void max_brigthness() {
		string file_path = dir_path + "max_brightness";
		FILE *file = fopen(file_path.c_str(), "r");

		if (file == NULL) {
				fprintf(stderr, "failed to open file\n");
				exit(-1);
		}

		char c;

		while ( (c = fgetc(file)) != EOF ) {
				printf("%c", c);
		}

		fclose(file);
}

int main(int argc, char **argv) {
		if (getuid()) {
				cout << "need to be root" << endl;
				return -1;
		}

		if (argc == 1) {
				u_choice();
				return 0;
		}

		int opt;

		while ( (opt = getopt(argc, argv, "hmci:d:")) != -1 ) {
				switch (opt) {
						case 'h':
								help();
								break;
						case 'm':
								max_brigthness();
								break;
						case 'c':
								current_brightness();
								break;
						case 'i':
								inc(optarg);
								break;
						case 'd':
								dec(optarg);
								break;
						default:
								u_choice();
								break;
				}
		}

		return 0;
}

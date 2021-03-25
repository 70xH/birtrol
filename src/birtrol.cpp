#include <cstdlib>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

string dir_path = "/sys/class/backlight/amdgpu_bl1/";

void update_brightness(char *val) {
		string file_path = dir_path + "brightness";
		FILE *file = fopen(file_path.c_str(), "w+");

		if (file == NULL) {
				fprintf(stderr, "failed to open file\n");
				exit(-1);
		}

		fprintf(file, "%d", atoi(val));

		fclose(file);
}

string current_brightness() {
		string file_path = dir_path + "brightness";
		FILE *file = fopen(file_path.c_str(), "r");

		if (file == NULL) {
				fprintf(stderr, "failed to open file\n");
				exit(-1);
		}

		char c;
		string num;

		while ( (c = fgetc(file)) != EOF ) {
				num += c;
		}

		fclose(file);
		return num;
}

void u_choice() {
		printf("Current brightness: ");
		cout << current_brightness();

		char ch = 'n';

		printf("Change brightness (y/N): ");
		scanf("%c", &ch);

		if (ch == 'y') {
				printf("Change the brightness to: ");
				string val;
				cin >> val;

				update_brightness(strdup(val.c_str()));
		}
}

void help() {
		printf("help section\n");
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
		if (argc == 1) {
				u_choice();
				return 0;
		}

		int opt;
		string val;

		while ( (opt = getopt(argc, argv, "hmci:d:u:")) != -1 ) {
				switch (opt) {
						case 'h':
								help();
								break;
						case 'm':
								max_brigthness();
								break;
						case 'c':
								cout << current_brightness();
								break;
						case 'u':
								update_brightness(optarg);
								break;
						case 'i':
								val = to_string(atoi(current_brightness().c_str()) + atoi(optarg));
								update_brightness(strdup(val.c_str()));
								break;
						case 'd':
								val = to_string(atoi(current_brightness().c_str()) - atoi(optarg));
								update_brightness(strdup(val.c_str()));
								break;
						default:
								u_choice();
								break;
				}
		}

		return 0;
}

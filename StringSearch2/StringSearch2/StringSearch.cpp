#include <iostream>
using namespace std;

#define BUFFER 100

int size(char* a){
	int i(0);
	while (a[i++] != '\0');
	return (--i);
}

void copy(char* n, char* o){
	int i(0);
	while (o[i] != '\0'){
		n[i] = o[i];
		++i;
	}
	n[i] = '\0';
}

bool FindNextChar(char* str, char a, int& cntr){
	int res(false);
	int s = size(str);
	for (int i = cntr; i < s; ++i){
		if (str[i] == a) {
			cntr = i;
			res = true;
			break;
		}
	}
	return res;
}

bool SearchSubString(char* str1, char* str2, int &a, int &b){
	int s1 = size(str1);
	int s2 = size(str2);

	int b_temp = b;
	while ((b_temp < s2) && str2[b_temp] == '*') ++b_temp;
	if (b_temp == s2) return true;

	if ((b_temp < s2 - 1) && str2[b_temp] == '\\' && str2[b_temp + 1] == '*'){
		if (!FindNextChar(str1, '*', a)) return false;
	}

	while (a < s1){
		int aa = a;
		b = b_temp;
		
		if (b < s2 - 1 && str2[b] == '\\' && str2[b + 1] == '*') ++b;
		
		while (aa < s1 && str1[aa] == str2[b]){
			++aa; ++b;
			if (b < s2 && str2[b] == '*'){
				if (SearchSubString(str1, str2, aa, b)) return true;
			}
			else if (b < s2 - 1 && str2[b] == '\\' && str2[b + 1] == '*') ++b;
			if (b == s2) return true;
		}
		++a;
	}
	return false;
}


int main(int argc, char* argv[]){

	char str1[BUFFER], str2[BUFFER];

	if (argc != 3){
		cout << "Enter the First word: ";
		cin.getline(str1, BUFFER);
		cout << "Enter the Second word: ";
		cin.getline(str2, BUFFER);
	}
	else {
		copy(str1, argv[1]);
		copy(str2, argv[2]);
	}

	int a = 0, b = 0;
	if (SearchSubString(str1, str2,a,b)){
		cout << "\"" << str2 << "\" is the substring of \"" << str1 << "\"\n";
	}
	else{
		cout << "\"" << str2 << "\" is NOT the substring of \"" << str1 << "\"\n";
	}

	cin.get();
	return(0);
}
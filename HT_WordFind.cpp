#include<iostream>
#include<time.h>
#include<cstdlib>
using namespace std;
//tao hashFunc de tao 1 index qua do tim kiem nhanh hon. khong phai duyet lan luot

#define N 8
#define M 8

// create table where you will find word 
void createArray(char arr[][M]){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			arr[i][j] = 97 + rand()%(122+1-97); 
		}
	}
}
void displayArray(char arr[][M]){
	for(int i = 0; i < N; i ++){
		for(int j = 0; j < M; j++){
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

//algorithm
// 1. phan tich tu thanh cac tien to nho hon 
// 2. nem chung vao mang bam 
// 3. xet chu cai trong bang. voi moi o kiem tra xem co trung voi mang bam khong. neu co kiem tra hang xom cua no 
// 4. de quy neu tim thay tu phu hop thi nem ra 
// 5. lap lai voi cac o 

// tao mang chua dang tu can tim
// chia nho tu can tim thanh cac tien to , vd bird -> b, bi, bir, bird  (tao ham chia nho tien tien tu)
// tao hashTable cua cac tien to tu 
// xet moi o, co trong hashtable khong ( tao hashfunc, tao ham check o )
// neu co xem o xung quanh co o nao ket hop lai thanh tu co trong hashtable ko -> neu khong thi chuyen o ( tao ham check o xung quanh doi vs o hien tai )
// neu co xem tiep o lien ke theo 1 chieu dang xet co tao thanh 1 thanh phan tu trong hashtable khong -> neu khong thi chuyen o -> de quy 
// lap lai cho den khi tim thay 1 trong cac tu thi nem vi tri cua no ra -> vi tri la vi tri o dang xet va chieu cua tu tim thay (tao ham check xem co dung tu can tim khong) 


// create array contains word need to find 
string words[3];
int wordsSize = 3;
void createWords(string arr[]){
	for (int i = 0; i < wordsSize; i++){
		cin >> arr[i]; 
	}
	for(int i = 0; i < wordsSize; i++){
		cout << arr[i] << endl;
	}
}

// divide words to prefixes of word
string prefixesWord[50];
int h = 0;
void createPrefixesWord(string arr[]){
	for(int i = 0; i < wordsSize; i++){
		string temp = "";
		for( int j = 0; j < arr[i].length(); j ++){
			temp += arr[i][j];
			prefixesWord[h] = temp;
			h++;
		}
	}
	for ( int i = 0; i < h; i ++ ){
		cout << prefixesWord[i] << " ";
	}
	cout << endl;
}

// create hashTable of prefixes of word and words
string hashTable[50];
int hashTableSize = 50;

//create hashing func
int hashFunc(string word){
	int sum = 0;
	for(int i = 0 ;i < word.length() ; i++){
		sum += (i+1)*word[i];
	}
	return sum % hashTableSize;
} 

void createHashTable(string arr[]){
	for(int i = 0; i < h; i++){
		int index = hashFunc(arr[i]);
		while (hashTable[index] != ""){
			index = (index + 1) % hashTableSize;
		}
		hashTable[index] = arr[i];
	}
	for (int i = 0; i < hashTableSize; i++){
		cout << hashTable[i] << " "; 
	}
	cout << endl;
}

// create func check words 
bool isValidWord (string word){
	for(int i = 0; i < wordsSize; i++){
		if(word == words[i])
			return true;
	}
	return false;
}

// create func check alphabet is in hashTable or not 
bool isOnHashTable(string s){
	int index = hashFunc(s);
	while(hashTable[index] != s and hashTable[index] != "")
        index = (index + 1) % hashTableSize;
	if(hashTable[index] == s) return true;
	else return false;
}

// tim kiem phan tu xung quanh 
char RightNeighbor(char c){
	return *(&c + 1);
}

// find words
string findwords(string s){
	if(isValidWord(s)) 
		return s;
	return 0;
}

int main(){
	// create words 
	createWords(words);

	//create table 
	char arr[N][M];
	// srand(int(time(0)));
	createArray(arr);
	displayArray(arr);

	//divide word 
	createPrefixesWord(words);

	//create hashTable
	createHashTable(prefixesWord);

	//xet tung o mot 
	cout << arr[6][0] << " " << RightNeighbor(arr[6][0]) << endl;
	return 0;
}


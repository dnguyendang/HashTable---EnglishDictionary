#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;

//feature of dictionary 
// - show all words 
// - add new word
// - search word -> explant meaning
// - update old word -> change mening 

// create Word (word, type, meaning)
// create Dictionary (pointer array of linked list) -> create node(word) of linked list
// create hashFunction and hashTable 
// add word to dictionary (processing linked list of array where contains that word )

int DictSize = 100; // Dictionary size 

struct Word{
    string word; // english
    string type; // adj, N , V or adv
    string meaning; // explant by english 
};

struct DictNode{
    Word word;
    DictNode* next;
};

void init(DictNode* heads[]){
    for(int i = 0; i < DictSize; i++){
        heads[i] = NULL;
    }
}

DictNode* createNode(Word w){
    DictNode* word = new DictNode();
    word->word = w;
    word->next = NULL;
    return word;
}

string toLower(string w){
    for(int i = 0; i < w.length(); i++){
        if(w[i] >= 'A' && w[i] <= 'Z')
            w[i] += ('a'-'A');
    }
    return w;
}

int hashFuncString(string w){
    int sum = 0;
    for(int i = 0; i < w.length(); i++){
        sum += (i+1)*tolower(w[i]);
    }
    return sum % DictSize;   
}

int hashFunc(Word w){
    int sum = 0;
    for(int i = 0; i < w.word.length(); i++){
        sum += (i+1)*tolower(w.word[i]);
    }
    return sum % DictSize;
}

void addWord(DictNode* heads[], Word w){
    int index = hashFunc(w);
    DictNode* r = heads[index];
    DictNode* p = createNode(w);
    bool flag = false;
    if(r == NULL)
        heads[index] = p;
    else{
        do{
            if(hashFunc(r->word) == hashFunc(w)){
                flag = true;
                break;
            }else
                r = r->next;
        }while(r->next != NULL);
        if(!flag){
            r->next = p;
        }
    }
}

void searchWord(DictNode* heads[], string en){
    int index = hashFuncString(en);
    DictNode* r = heads[index];
    while(r != NULL){
        if(hashFunc(r->word) == hashFuncString(en)){
            cout << r->word.word << " [" << r->word.type << "] : " << r->word.meaning << endl;
            break;
        }
        r = r->next;
    }
}

void updateWord(DictNode* heads[], Word w){
    int index = hashFunc(w);
    DictNode* r = heads[index];
    if(r != NULL){
        while(r != NULL){
            if(hashFunc(r->word) == hashFunc(w)){
                r->word.type = w.type;
                r->word.meaning = w.meaning;
                cout << r->word.word << " [" << r->word.type << "] : " << r->word.meaning << endl;
                break;
            }
            r = r->next;
        }
    }
}

void displayDict(DictNode* heads[]){
    for(int i = 0; i < DictSize; i++){
        if(heads[i] != NULL){
            cout << "== BUCKET " << i << " ==" << endl;
            DictNode* p = heads[i];
            while(p != NULL){
                cout << p->word.word << " [" << p->word.type << "] : " << p->word.meaning << endl;
                p = p->next;
            }
        }  
    }
}

void readDict(DictNode* heads[]){
    ifstream f;
    f.open("Dict.txt", ios::in);
    while(!f.eof()) // f.eof() -> at the end of file ? 
    {
        Word w;
        getline(f, w.word);
        getline(f, w.type);
        getline(f, w.meaning);

        addWord(heads, w);
    }
    f.close();
}

void writeDict(DictNode* heads[]){
    ofstream f;
    f.open("Dict.txt", ios::out);
    for(int i = 0; i < DictSize; i++){
        if(heads[i] != NULL){
            DictNode* p = heads[i];
            while(p != NULL){
                f << p->word.word << endl;
                f << p->word.type << endl;
                f << p->word.meaning << endl;
                p = p->next;
            }
        }  
    }
    f.close();
}

int main(){
    cout << "DICTIONARY" << endl;
    Word w1, w2, w3, w4, w5, w6, w7;

    w1.word = "Student";
    w1.type = "N";
    w1.meaning = "a person who is studying at a university or college";

    w2.word = "Teacher";
    w2.type = "N";
    w2.meaning = "a person who is teaching in a school";

    w3.word = "School";
    w3.type = "N";
    w3.meaning = "a place where children go to be educated";

    w4.word = "Go";
    w4.type = "V";
    w4.meaning = "to move or travel from one place to another";

    w5.word = "Teacher";
    w5.type = "N";
    w5.meaning = "a person whose job is teaching, especially in a school"; 

    w6.word = "University";
    w6.type = "N";
    w6.meaning = "an institution at the highest level of education where you can study for a degree or do research";

    w7.word = "Friend";
    w7.type = "N";
    w7.meaning = "a preson you know well and like, and who is not usually a member of your family";

    DictNode* Dict[DictSize];
    init(Dict);

    addWord(Dict, w1);
    addWord(Dict, w2);
    addWord(Dict, w3);
    addWord(Dict, w4);
    addWord(Dict, w6);
    addWord(Dict, w7);
    
    updateWord(Dict, w5);

    readDict(Dict);

    displayDict(Dict);
    // searchWord(Dict,"StudenT");

    writeDict(Dict);

    return 0;
}


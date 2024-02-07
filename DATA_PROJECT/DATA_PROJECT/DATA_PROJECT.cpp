#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;


struct sWord {
    char data[30];
    sWord* next;
};
struct dWord {
    char data[30];
    sWord* synonym, * antonym;
    dWord* next, * previous;
};
struct Dictionary {
    dWord* head, * tail;
};
sWord* createSWord(string& data) {
    sWord* newSWord = new sWord;
    if (data.length() < sizeof(newSWord->data)) {
        strcpy_s(newSWord->data, data.c_str());
    }
    newSWord->next = nullptr;
    return newSWord;
}
dWord* createDWord(string& data) {
    dWord* newDWord = new dWord;
    strcpy_s(newDWord->data, data.c_str());
    newDWord->synonym = nullptr;
    newDWord->antonym = nullptr;
    newDWord->next = nullptr;
    newDWord->previous = nullptr;
    return newDWord;
}
dWord* addWord(Dictionary* dict, string& data) {
    dWord* newWord = createDWord(data);
    if (dict->head == nullptr) {
        dict->head = newWord;
        dict->head->previous = nullptr;
         dict->tail = newWord;
    }
    else {

        dict->tail->next = newWord;
        newWord->previous = dict->tail;
        dict->tail = newWord;
    }
    return newWord;
}

void addSynonym(dWord* word, string& synonymData) {
    if (word->synonym == nullptr) {
        word->synonym = createSWord(synonymData);
    }
    else {
        sWord* temp = word->synonym;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = createSWord(synonymData);
    }
}
void addAntonym(dWord* word, string antonymData) {
    if (word->antonym == nullptr) {
        word->antonym = createSWord(antonymData);
    }
    else {
        sWord* temp = word->antonym;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = createSWord(antonymData);
    }
}
bool checkIfWordIsInDictionary(dWord* head, string word) {
    dWord* currentWord = head;

    while (currentWord != nullptr) {
        if (strcmp(currentWord->data, word.c_str()) == 0) {
            return true; //  found 
        }
        currentWord = currentWord->next;
    }
    return false; //  not found 
}
void outputAllWords(Dictionary* dict) {
    if (dict == nullptr || dict->head == nullptr) {
        cout << "Dictionary is empty." <<  endl;
        return;
    }

    const dWord* current = dict->head;
    while (current != nullptr) {
        cout << "Word: " << current->data <<   endl;

        sWord* synonym = current->synonym;
        if (synonym != nullptr) {
            cout << "Synonyms: ";
            while (synonym != nullptr) {
                  cout << synonym->data << " ";
                synonym = synonym->next;
            }
            cout <<   endl;
        }
        else {
              cout << "No synonyms found." <<   endl;
        }

        sWord* antonym = current->antonym;
        if (antonym != nullptr) {
            cout << "Antonyms: ";
            while (antonym != nullptr) {
               cout << antonym->data << " ";
                antonym = antonym->next;
            }
            cout << endl;
        }
        else {
            cout << "No antonyms found." << endl;
        }

        current = current->next;
    }
}
void outputWordDetails(Dictionary* dict, string targetWord) {
    if (dict == nullptr || dict->head == nullptr) {
        cout << "Dictionary is empty." << endl;
        return;
    }

    dWord* current = dict->head;
    bool found = false;

    while (current != nullptr) {
        if (current->data == targetWord) {
            found = true;
              cout << "Word: " << current->data <<   endl;

            sWord* synonym = current->synonym;
            if (synonym != nullptr) {
                  cout << "Synonyms: ";
                while (synonym != nullptr) {
                      cout << synonym->data << " ";
                    synonym = synonym->next;
                }
                  cout <<   endl;
            }
            else {
                  cout << "No synonyms found." <<   endl;
            }

            sWord* antonym = current->antonym;
            if (antonym != nullptr) {
                  cout << "Antonyms: ";
                while (antonym != nullptr) {
                      cout << antonym->data << " ";
                    antonym = antonym->next;
                }
                  cout <<   endl;
            }
            else {
                  cout << "No antonyms found." <<   endl;
            }

            break; //  exit  loop
        }
        current = current->next;
    }

    if (!found) {
          cout << "Word '" << targetWord << "' not found in the dictionary." <<   endl;
    }
}
void addWordToDictionary(dWord*& head, const char* wordToAdd) {//addtobegin
    dWord* newWord = new dWord;
    strncpy_s(newWord->data, wordToAdd, sizeof(newWord->data) - 1);
    newWord->synonym = nullptr; // Initialize synonym pointer
    newWord->antonym = nullptr; // Initialize antonym pointer
    newWord->next = nullptr;

    if (head == nullptr) {
        head = newWord;
    }
    else {
        newWord->next = head;
        head = newWord;
        head->previous = nullptr;
    }
}
dWord* findWord(dWord* head, const char* wordToFind) {
    dWord* current = head;
    while (current != nullptr) {
        if (strcmp(current->data, wordToFind) == 0) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}
dWord* createNewWord(const char* word) {
    dWord* newWord = new dWord;
    strcpy_s(newWord->data, word);
    newWord->synonym = nullptr;
    newWord->antonym = nullptr;
    newWord->next = nullptr;
    return newWord;
}

void addSynonymsAndAntonyms(dWord* word) {
    char synonyms[200];
    cout << "Enter synonyms separated by commas: ";
    cin.getline(synonyms, sizeof(synonyms));

    char* temp;
    char* nextToken = nullptr;
    temp = strtok_s(synonyms, ",", &nextToken);

    while (temp != nullptr) {
        sWord* newSynonym = new sWord;
        strcpy_s(newSynonym->data, temp);
        newSynonym->next = word->synonym;
        word->synonym = newSynonym;
        temp = strtok_s(nullptr, ",", &nextToken);
    }

    char antonyms[200];
      cout << "Enter antonyms separated by commas: ";
      cin.getline(antonyms, sizeof(antonyms));

    temp = strtok_s(antonyms, ",", &nextToken);
    while (temp != nullptr) {
        sWord* newAntonym = new sWord;
        strcpy_s(newAntonym->data, temp);
        newAntonym->next = word->antonym;
        word->antonym = newAntonym;
        temp = strtok_s(nullptr, ",", &nextToken);
    }
}

void initializeDictionary(Dictionary* dict) {
    dict->head = nullptr;
    dict->tail = nullptr;
}
Dictionary readfrominputfile(Dictionary* dict) {

    ifstream inputFile("data.txt");
    string line;
    string wordsBetweenColon;
    string firstWords;
    string wordsAfterHash;

    if (inputFile.is_open()) {
        //Dictionary dict;
        //initializeDictionary(&dict);

        while (getline(inputFile, line)) {
            stringstream ss(line);
            string firstWord, rest, synonym, antonym;
            getline(ss, firstWord, ':');
            if (checkIfWordIsInDictionary(dict->head, firstWord)) {
                continue;
            }
            firstWords += firstWord + " ";//dword
            //cout << firstWord << " dictionary " <<   endl;

            if (checkIfWordIsInDictionary(dict->head, firstWord) == true) {
                continue;
            }
            dWord* newWord = addWord(dict, firstWord);


            bool isFirst = true;
            bool isFirst1 = true;
            while (getline(ss, synonym, ':')) {

                if (!synonym.empty()) {

                    if (ss.eof()) {
                        rest = synonym;
                        stringstream r(rest);
                        string contents = r.str();
                        //cout << "r is " << contents << endl;;


                        while (getline(r, antonym, '#')) {
                            if (isFirst1) {

                                wordsBetweenColon += antonym + " ";//synonym
                                isFirst1 = false;
                                addSynonym(newWord, antonym);
                            }
                            else {
                                wordsAfterHash += antonym + " ";
                                addAntonym(newWord, antonym);//antonym
                            }
                        }
                    }
                    else if (isFirst) {
                        wordsBetweenColon += synonym + " ";//synonym
                        isFirst = false;
                        addSynonym(newWord, synonym);

                    }
                    else {
                        wordsBetweenColon += synonym + " ";
                        addSynonym(newWord, synonym);

                        //synonym
                    }
                }
            }


        }

         // cout << "Words between colons: " << wordsBetweenColon <<   endl;
          //cout << "Words after hash: " << wordsAfterHash <<   endl;
        outputAllWords(dict);
    }

    else {
          cout << "Unable to open file!" <<   endl;
    }
    return *dict;
}
void writeToInputFile(const Dictionary* dict, const string& filename) {
      ofstream outputFile(filename);

    if (outputFile.is_open()) {
        const dWord* currentWord = dict->head;

        while (currentWord != nullptr) {
            outputFile << currentWord->data;

            sWord* synonym = currentWord->synonym;
            while (synonym != nullptr) {
                outputFile << ":" << synonym->data;
                synonym = synonym->next;
            }

            sWord* antonym = currentWord->antonym;
            while (antonym != nullptr) {
                outputFile << "#" << antonym->data;
                antonym = antonym->next;
            }

            outputFile << "\n";
            currentWord = currentWord->next;
        }

        outputFile.close();
          cout << "Data written to file: " << filename <<   endl;
    }
    else {
          cout << "Unable to open file for writing!" <<   endl;
    }
}
void addSynonymsToDictionary(dWord*& head) {
    dWord* current = head;

    while (current != nullptr) {
        sWord* synonym = current->synonym;

        while (synonym != nullptr) {
            if (!checkIfWordIsInDictionary(head, synonym->data) && strcmp(synonym->data, current->data) != 0) {
                addWordToDictionary(head, synonym->data);
                dWord* addedSynonym = findWord(head, synonym->data);

                addedSynonym->synonym = nullptr;
                addedSynonym->antonym = nullptr;

                addedSynonym->antonym = current->antonym;

                sWord* tempSynonym = current->synonym;
                sWord* previousNewSynonym = nullptr;

                while (tempSynonym != nullptr) {
                    if (strcmp(tempSynonym->data, synonym->data) != 0) {
                        sWord* newSynonym = new sWord;
                        strcpy_s(newSynonym->data, tempSynonym->data);
                        newSynonym->next = nullptr;

                        if (addedSynonym->synonym == nullptr) {
                            addedSynonym->synonym = newSynonym;
                        }
                        else {
                            if (previousNewSynonym != nullptr) {
                                previousNewSynonym->next = newSynonym;
                            }
                        }
                        previousNewSynonym = newSynonym;
                    }
                    tempSynonym = tempSynonym->next;
                }

                sWord* newSynonymForCurrent = new sWord;
                strcpy_s(newSynonymForCurrent->data, current->data);
                newSynonymForCurrent->next = addedSynonym->synonym;
                addedSynonym->synonym = newSynonymForCurrent;
            }
            synonym = synonym->next;
        }
        current = current->next;
    }
}
void addAntonymsToDictionary(dWord*& head) {
    dWord* current = head;

    while (current != nullptr) {
        sWord* antonym = current->antonym;

        while (antonym != nullptr) {
            if (!checkIfWordIsInDictionary(head, antonym->data) && strcmp(antonym->data, current->data) != 0) {
                addWordToDictionary(head, antonym->data);
                dWord* addedAntonym = findWord(head, antonym->data);

                addedAntonym->synonym = nullptr;
                addedAntonym->antonym = nullptr;

                sWord* newAntonymForCurrent = new sWord;
                strcpy_s(newAntonymForCurrent->data, current->data);
                newAntonymForCurrent->next = addedAntonym->antonym;
                addedAntonym->antonym = newAntonymForCurrent;

                sWord* tempSynonym = current->synonym;
                while (tempSynonym != nullptr) {
                    if (strcmp(tempSynonym->data, antonym->data) != 0) {
                        sWord* newSynonym = new sWord;
                        strcpy_s(newSynonym->data, tempSynonym->data);
                        newSynonym->next = addedAntonym->antonym;

                        addedAntonym->antonym = newSynonym;
                    }
                    tempSynonym = tempSynonym->next;
                }

                sWord* tempAntonym = current->antonym;
                while (tempAntonym != nullptr) {
                    if (strcmp(tempAntonym->data, antonym->data) != 0) {
                        sWord* newAntonym = new sWord;
                        strcpy_s(newAntonym->data, tempAntonym->data);
                        newAntonym->next = addedAntonym->synonym;

                        addedAntonym->synonym = newAntonym;
                    }
                    tempAntonym = tempAntonym->next;
                }
            }
            antonym = antonym->next;
        }
        current = current->next;
    }
}
void sortDictionary(dWord*& head) {
    bool swapped;
    dWord* ptr1;
    dWord* lptr = nullptr;

    if (head == nullptr)
        return;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->data, ptr1->next->data) > 0) {
              
                  swap(ptr1->data, ptr1->next->data);
                  swap(ptr1->synonym, ptr1->next->synonym);
                  swap(ptr1->antonym, ptr1->next->antonym);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}


void swapNodes(dWord*& a, dWord*& b) {
    dWord* temp = a;
    a = b;
    b = temp;
}

void sortDictionarynodes(dWord*& head) {
    bool swapped;
    dWord* ptr1, * lptr = nullptr;

    if (head == nullptr)
        return;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->data, ptr1->next->data) > 0) {
                // Swap nodes
                swapNodes(ptr1, ptr1->next);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
void addWordToDictionarySorted(dWord*& head, dWord* wordToAdd) {
    dWord* newWord = wordToAdd;
    newWord->next = nullptr;

    dWord* current = head;
    dWord* prev = nullptr;

    while (current != nullptr && strcmp(current->data, wordToAdd->data) < 0) {
        prev = current;
        current = current->next;
    }

    if (prev == nullptr) {
        newWord->next = head;
        head = newWord;
    }
    else {
        prev->next = newWord;
        newWord->next = current;
    }
}





void addUserInputToDictionary(dWord*& head) {
    char word[50];
    cout << "Enter a word: ";
    cin.getline(word, sizeof(word));

    dWord* newWord = createNewWord(word);

    addSynonymsAndAntonyms(newWord);

    addWordToDictionarySorted(head, newWord);
}
void addSynonymOrAntonym(dWord* head) {
    char targetWord[50];
      cout << "Enter the word you want to add a synonym/antonym to: ";
      cin >> targetWord;

    dWord* current = head;
    while (current != nullptr) {
        if (strcmp(current->data, targetWord) == 0) {
            char choice;
              cout << "Do you want to add a synonym (s) or an antonym (a)? ";
              cin >> choice;

            if (choice == 's') {
                char synonymToAdd[50];
                  cout << "Enter the synonym: ";
                  cin >> synonymToAdd;

                sWord* newSynonym = new sWord;
                strcpy_s(newSynonym->data, synonymToAdd);
                newSynonym->next = current->synonym;
                current->synonym = newSynonym;

                  cout << "Synonym added successfully!\n";
            }
            else if (choice == 'a') {
                char antonymToAdd[50];
                  cout << "Enter the antonym: ";
                  cin >> antonymToAdd;

                sWord* newAntonym = new sWord;
                strcpy_s(newAntonym->data, antonymToAdd);
                newAntonym->next = current->antonym;
                current->antonym = newAntonym;

                  cout << "Antonym added successfully!\n";
            }
            else {
                  cout << "Invalid choice!\n";
            }

            return;
        }
        current = current->next;
    }

      cout << "Word not found in the dictionary!\n";
}
void deleteNodesWithLetters(Dictionary* dict, string letters) {
    if (dict == nullptr || dict->head == nullptr) {
        cout << "Dictionary is empty." << endl;
        return;
    }

    dWord* current = dict->head;
    dWord* prev = nullptr;

    while (current != nullptr) {
        bool containsLetter = false;

        for (char letter : letters) {
            if (strchr(current->data, letter) != nullptr) {
                containsLetter = true;
                break;
            }

            sWord* synonym = current->synonym;
            while (synonym != nullptr) {
                if (strchr(synonym->data, letter) != nullptr) {
                    containsLetter = true;
                    break;
                }
                synonym = synonym->next;
            }

            sWord* antonym = current->antonym;
            while (antonym != nullptr) {
                if (strchr(antonym->data, letter) != nullptr) {
                    containsLetter = true;
                    break;
                }
                antonym = antonym->next;
            }

            if (containsLetter) {
                break;
            }
        }

        
        if (containsLetter) {
            if (prev == nullptr) {
                
                dict->head = current->next;
                if (dict->head != nullptr) {
                    dict->head->previous = nullptr;
                }
                delete current;
                current = dict->head; 
            }
            else {
                dWord* temp = current;
                current = current->next;
                prev->next = current;
                if (current != nullptr) {
                    current->previous = prev;
                }
                delete temp;
            }
        }
        else {
            
            prev = current;
            current = current->next;
        }
    }
}
void deleteWordsStartingWithLetters(Dictionary* dict, const string& letters) {
    if (dict == nullptr || dict->head == nullptr) {
        cout << "Dictionary is empty." << endl;
        return;
    }

    dWord* current = dict->head;
    dWord* nextWord;

    while (current != nullptr) {
        
        nextWord = current->next;

        
        if (letters.find(current->data[0]) != string::npos) {
            
            if (current->previous != nullptr) {
                current->previous->next = current->next;
            }
            if (current->next != nullptr) {
                current->next->previous = current->previous;
            }
            if (current == dict->head) {
                dict->head = current->next;
            }
            if (current == dict->tail) {
                dict->tail = current->previous;
            }
            dWord* toDelete = current;
            current = current->next;
            delete toDelete;
            continue; 
        }

        
        sWord* synonym = current->synonym;
        sWord* prevSynonym = nullptr;
        while (synonym != nullptr) {
            if (letters.find(synonym->data[0]) != string::npos) {
                
                if (synonym == current->synonym) {
                    current->synonym = synonym->next;
                }
                else {
                    prevSynonym->next = synonym->next;
                }
                sWord* toDelete = synonym;
                synonym = synonym->next;
                delete toDelete;
                continue; 
            }
            prevSynonym = synonym;
            synonym = synonym->next;
        }

        
        sWord* antonym = current->antonym;
        sWord* prevAntonym = nullptr;
        while (antonym != nullptr) {
            if (letters.find(antonym->data[0]) != string::npos) {
                
                if (antonym == current->antonym) {
                    current->antonym = antonym->next;
                }
                else {
                    prevAntonym->next = antonym->next;
                }
                sWord* toDelete = antonym;
                antonym = antonym->next;
                delete toDelete;
                continue; 
            }
            prevAntonym = antonym;
            antonym = antonym->next;
        }

        current = nextWord;
    }
}
bool containsAllLetters(const string& word, const string& letters) {
    return all_of(letters.begin(), letters.end(), [&](char letter) {
        return count(word.begin(), word.end(), letter) > 0;
        });
}
void filterWordsByLetters(const Dictionary* dict, const string& letters) {
    if (dict == nullptr || dict->head == nullptr) {
        cout << "Dictionary is empty." << endl;
        return;
    }

    const dWord* current = dict->head;

    cout << "Words containing all letters in '" << letters << "':" << endl;

    while (current != nullptr) {
        if (containsAllLetters(current->data, letters)) {
            cout << current->data << endl;
        }

        sWord* synonym = current->synonym;
        while (synonym != nullptr) {
            if (containsAllLetters(synonym->data, letters)) {
                cout << "Synonym: " << synonym->data << " (for word: " << current->data << ")" << endl;
            }
            synonym = synonym->next;
        }

        sWord* antonym = current->antonym;
        while (antonym != nullptr) {
            if (containsAllLetters(antonym->data, letters)) {
                cout << "Antonym: " << antonym->data << " (for word: " << current->data << ")" << endl;
            }
            antonym = antonym->next;
        }

        current = current->next;
    }
}
void outputSynonymsAndAntonyms(const Dictionary* dict, const string& targetWord) {
    if (dict == nullptr || dict->head == nullptr) {
        cout << "Dictionary is empty." << endl;
        return;
    }

    dWord* current = dict->head;
    bool found = false;

    while (current != nullptr) {
        if (current->data == targetWord) {
            found = true;

            
            sWord* synonym = current->synonym;
            if (synonym != nullptr) {
                cout << "Synonyms for '" << targetWord << "': ";
                while (synonym != nullptr) {
                    cout << synonym->data << " ";
                    synonym = synonym->next;
                }
                cout << endl;
            }
            else {
                cout << "No synonyms found for '" << targetWord << "'." << endl;
            }

            
            sWord* antonym = current->antonym;
            if (antonym != nullptr) {
                cout << "Antonyms for '" << targetWord << "': ";
                while (antonym != nullptr) {
                    cout << antonym->data << " ";
                    antonym = antonym->next;
                }
                cout << endl;
            }
            else {
                cout << "No antonyms found for '" << targetWord << "'." << endl;
            }

            break; 
        }
        current = current->next;
    }

    if (!found) {
        cout << "Word '" << targetWord << "' not found in the dictionary." << endl;
    }
}









int main() {
    Dictionary dict;

    initializeDictionary(&dict);
    readfrominputfile(&dict);
    addSynonymsToDictionary(dict.head);
    addAntonymsToDictionary(dict.head);
    sortDictionary(dict.head);
    dWord* dictionary = nullptr;

    int choice;
    char continueChoice;
    string lettersToDelete;
    string lettersToFilter;
    string wordToSearch;
    string startLetters;

    do {
        cout << "\nDictionary Menu:\n";
        cout << "1. Add a new word\n";
        cout << "2. Add a synonym or antonym\n";
        cout << "3. delete depending on  letters\n";
        cout << "4. search words with a given set of letters\n";
        cout << "5. search for synonyms and antonyms \n";
        cout << "6.delete depending on starting words\n";
        cout << "7. exit\n";

        
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            addUserInputToDictionary(dict.head);
            addSynonymsToDictionary(dict.head);
            addAntonymsToDictionary(dict.head);
            sortDictionary(dict.head);
            outputAllWords(&dict);

            break;
        case 2:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            addSynonymOrAntonym(dict.head);
            addSynonymsToDictionary(dict.head);
            addAntonymsToDictionary(dict.head);
            sortDictionary(dict.head);
            outputAllWords(&dict);

            break;
        case 3:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter letters to delete words: ";
            cin >> lettersToDelete;
            deleteNodesWithLetters(&dict, lettersToDelete);
            outputAllWords(&dict);

            break;
        case 4:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            
            cout << "Enter letters to filter words: ";
            cin >> lettersToFilter;
            filterWordsByLetters(&dict, lettersToFilter);
            break;
        case 5:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            
            cout << "Enter a word to show synonyms and antonyms: ";
            cin >> wordToSearch;
            outputSynonymsAndAntonyms(&dict, wordToSearch);
            break;
        case 6:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter letters to delete words starting with: ";
           
            cin >> startLetters;
            deleteWordsStartingWithLetters(&dict, startLetters);
            outputAllWords(&dict);
            break;


        case 7:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

           cout << "Exiting the dictionary...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

        if (choice != 7) {
            cout << "Do you want to continue (Y/N)? ";
            cin >> continueChoice;
        }
    } while (choice != 7 && (continueChoice == 'Y' || continueChoice == 'y'));
    writeToInputFile(&dict, "data.txt");
    return 0;
}
/* International Dictionary - Project 1
*  CIT-284 Fall 2019
*
*  Author: Marisha Kulseng
*  Date last modified: 9/29/2019
*
*  This project seeks to assemble an international dictionary containing
*  25 words each from French, German, Hebrew, and Latin and their
*  English translations.
*/

#include <iostream>
//using std::cout;
//using std::endl;
using namespace std;

#include <cstdlib>
#include <conio.h>
#include <string> 
#include <fstream>
#include <iomanip>

struct VocabWord {
	string displayWord; // with special char, (def article too?)
	string sortWord; // without special char, without definite article for sorting
	string partOfSpeech; // noun, verb, preposition, cardinal number, adverb, adjective, pronoun, conjunction
	string englishWord; // English translation of the word
	string sourceLanguage; //German, French, Latin, Hebrew
};


void printSpecialCharHelp();
char menu();
char printSubMenu();
string selectLanguage();
char dictionaryImportMenu();
void quit();
void checkDictionary(VocabWord **pDictionary, int DICT_SIZE, string partOfSpeech, bool hasDictionaryImported, bool isEnglish);

string getWord();
void manuallyImportDictionary(VocabWord *, int);
void loadStructArray(VocabWord *dictionary, int DICT_SIZE, ifstream &inFile);
void splitLine(string line, string segmentArr[], int size);
bool createWordList(VocabWord * dictionary, int DICT_SIZE, ifstream &inFile, ofstream &outFile);
void printDictionary(VocabWord*, int, ostream&);

int countPartOfSpeech(VocabWord**, int, string);
void printPartOfSpeech(VocabWord **pDictionary, int pDictSize, int logicalSize, string partOfSpeech, bool isEnglish);
VocabWord **sortWords(VocabWord **, int);
VocabWord** sortWordsInEnglish(VocabWord **pDictionary, int size);
void printStructArray(VocabWord **wordsToPrint, int size, string printLanguage, bool isEnglish);

int wordSearch(VocabWord **pDictionary, int size, string inputWord);


int main() {
	system("title International Dictionary - M. Kulseng - CIT-284");

	char choice;
	string word, printLanguage, inputFileName = "", outputFileName = "",
		noDictionaryErrorMsg = "\nYou must import a dictionary first!\nPress any key to return to the menu.",
		hasDictionaryErrorMsg = "\nThe dictionary already exists; you cannot import another one. \nPress any key to return to the menu.";
	ifstream inFile;
	ofstream outFile;
	const int DICT_SIZE = 100;
	VocabWord dictionary[DICT_SIZE]; // 100 is the given dictionary size -- array of struct
	VocabWord *pDictionary[DICT_SIZE] = { nullptr }; // array of pointers to structs
	int logicalSize;
	bool isEnglish, hasDictionaryImported = false; // we start the program with no dictionary loaded


	for (int i = 0; i < DICT_SIZE; i++) { // load array of pointers to array of struct
		pDictionary[i] = &dictionary[i];
	}


	while (true) {
		choice = menu();
		switch (choice)
		{
		case 'A':  // Create the word list	
			if (hasDictionaryImported) {
				cout << hasDictionaryErrorMsg;
				_getch();   break;
			}
			hasDictionaryImported = createWordList(dictionary, DICT_SIZE, inFile, outFile);
			break;

		case 'B': // German(French,Latin,Hebrew) to English nouns
			isEnglish = false;
			checkDictionary(pDictionary, DICT_SIZE, "noun", hasDictionaryImported, isEnglish);
			break;
		case 'C':  // German(French,Latin,Hebrew) to English verbs
			isEnglish = false;
			checkDictionary(pDictionary, DICT_SIZE, "verb", hasDictionaryImported, isEnglish);
			break;
		case 'D': // German(French,Latin,Hebrew) to English prepositions
			isEnglish = false;
			checkDictionary(pDictionary, DICT_SIZE, "preposition", hasDictionaryImported, isEnglish);
			break;
		case 'E': // German(French,Latin,Hebrew) to English adjectives
			isEnglish = false;
			checkDictionary(pDictionary, DICT_SIZE, "adjective", hasDictionaryImported, isEnglish);
			break;
		case 'F': // German(French,Latin,Hebrew) to English adverbs
			isEnglish = false;
			checkDictionary(pDictionary, DICT_SIZE, "adverb", hasDictionaryImported, isEnglish);
			break;
		case 'G': // German(French,Latin,Hebrew) to English cardinal numbers
			isEnglish = false;
			checkDictionary(pDictionary, DICT_SIZE, "cardinal number", hasDictionaryImported, isEnglish);
			break;
		case 'H': // German(French,Latin,Hebrew) to English conjunctions
			isEnglish = false;
			checkDictionary(pDictionary, DICT_SIZE, "conjunction", hasDictionaryImported, isEnglish);
			break;
		case 'I': // German(French,Latin,Hebrew) to English pronouns
			isEnglish = false;
			checkDictionary(pDictionary, DICT_SIZE, "pronoun", hasDictionaryImported, isEnglish);
			break;
		case 'J': // German(French,Latin,Hebrew) to English all
			if (!hasDictionaryImported) {
				cout << noDictionaryErrorMsg;
				_getch();   break;
			}
			isEnglish = false;
			printLanguage = selectLanguage();
			sortWords(pDictionary, DICT_SIZE);
			printStructArray(pDictionary, DICT_SIZE, printLanguage, isEnglish);
			break;
		case 'K': // English to (German,French,Latin,Hebrew) nouns
			isEnglish = true;
			checkDictionary(pDictionary, DICT_SIZE, "noun", hasDictionaryImported, isEnglish);
			break;
		case 'L': // English to (German,French,Latin,Hebrew) verbs
			isEnglish = true;
			checkDictionary(pDictionary, DICT_SIZE, "verb", hasDictionaryImported, isEnglish);
			break;
		case 'M': // English to (German,French,Latin,Hebrew) prepositions
			isEnglish = true;
			checkDictionary(pDictionary, DICT_SIZE, "preposition", hasDictionaryImported, isEnglish);
			break;
		case 'N': // English to (German,French,Latin,Hebrew) adjectives
			isEnglish = true;
			checkDictionary(pDictionary, DICT_SIZE, "adjective", hasDictionaryImported, isEnglish);
			break;
		case 'O': // English to (German,French,Latin,Hebrew) adverbs
			isEnglish = true;
			checkDictionary(pDictionary, DICT_SIZE, "adverb", hasDictionaryImported, isEnglish);
			break;
		case 'P': // English to (German,French,Latin,Hebrew) cardinal numbers
			isEnglish = true;
			checkDictionary(pDictionary, DICT_SIZE, "cardinal number", hasDictionaryImported, isEnglish);
			break;
		case 'Q': // English to (German,French,Latin,Hebrew) conjunctions
			isEnglish = true;
			checkDictionary(pDictionary, DICT_SIZE, "conjunction", hasDictionaryImported, isEnglish);
			break;
		case 'R': //  English to (German,French,Latin,Hebrew) pronouns
			isEnglish = true;
			checkDictionary(pDictionary, DICT_SIZE, "pronoun", hasDictionaryImported, isEnglish);
			break;
		case 'S': // English to (German,French,Latin,Hebrew) all 
			if (!hasDictionaryImported) {
				cout << noDictionaryErrorMsg;
				_getch();   break;
			}
			isEnglish = true;
			printLanguage = selectLanguage();
			sortWordsInEnglish(pDictionary, DICT_SIZE);
			printStructArray(pDictionary, DICT_SIZE, printLanguage, isEnglish);
			break;
		case 'T': // Search for a word in one language and return all other languages
			if (!hasDictionaryImported) {
				cout << noDictionaryErrorMsg;
				_getch();   break;
			}
			system("cls");
			printSpecialCharHelp();
			word = getWord(); // word search
			logicalSize = wordSearch(pDictionary, DICT_SIZE, word); // returns logical size of a new array
			break;
		case 'U': quit(); break; // Quit
		default: cout << "\n\nInvalid choice; please try again" << endl;
			cout << "\nPress any key to continue...";
			_getch();
			break;
		}
	}
	
	_getch();
	return 0;
}

char menu() {
	char choice;
	system("cls");
	cout << "\t***Main Menu***" << endl
		<< "(A)   Create the word list" << endl
		<< "(B)   German(French,Latin,Hebrew) to English nouns" << endl
		<< "(C)   German(French,Latin,Hebrew) to English verbs" << endl
		<< "(D)   German(French,Latin,Hebrew) to English prepositions" << endl
		<< "(E)   German(French,Latin,Hebrew) to English adjectives" << endl
		<< "(F)   German(French,Latin,Hebrew) to English adverbs" << endl
		<< "(G)   German(French,Latin,Hebrew) to English cardinal numbers" << endl
		<< "(H)   German(French,Latin,Hebrew) to English conjunctions" << endl
		<< "(I)   German(French,Latin,Hebrew) to English pronouns" << endl
		<< "(J)   German(French,Latin,Hebrew) to English all" << endl
		<< "(K)   English to (German,French,Latin,Hebrew) nouns" << endl
		<< "(L)   English to (German,French,Latin,Hebrew) verbs" << endl
		<< "(M)   English to (German,French,Latin,Hebrew) prepositions" << endl
		<< "(N)   English to (German,French,Latin,Hebrew) adjectives" << endl
		<< "(O)   English to (German,French,Latin,Hebrew) adverbs" << endl
		<< "(P)   English to (German,French,Latin,Hebrew) cardinal numbers" << endl
		<< "(Q)   English to (German,French,Latin,Hebrew) conjunctions" << endl
		<< "(R)   English to (German,French,Latin,Hebrew) pronouns" << endl
		<< "(S)   English to (German,French,Latin,Hebrew) all" << endl
		<< "(T)   Search for a word in one language and return all other languages" << endl
		<< "(U)   Quit" << endl;

	cout << endl << "Please enter your choice: ";
	choice = _getch();
	choice = toupper(choice);
	return choice;
}

void quit() {
	char selection;
	cout << "\nAre you sure you want to quit? (Enter y for yes; any other response will return to the main menu)" << endl;
	selection = _getch();


	if (selection == 'y' || selection == 'Y') {
		cout << "\nPress any key to close the program.";
		_getch();
		exit(0);
	}
	else {
		return;
	}
}


char printSubMenu() {
	char choice;
	string language;
	cout << "\n\tPlease select the language to display: \n"
		<< "(1) German  \n"
		<< "(2) French  \n"
		<< "(3) Latin   \n"
		<< "(4) Hebrew  \n"
		<< "(5) All     \n\n";
	choice = _getch();
	return choice;
}

string selectLanguage() {
	string language = "";
	char choice;

	choice = printSubMenu();

	while (language == "") {
		switch (choice)
		{
		case '1': language = "German"; break;
		case '2': language = "French"; break;
		case '3': language = "Latin"; break;
		case '4': language = "Hebrew"; break;
		case '5': language = "All"; break;
		default:
			language == "";
			system("cls");
			cout << "\nInvalid choice. Please select from the menu:\n\n";
			choice = printSubMenu();
			break;
		}
	}
	return language;
}


VocabWord** sortWords(VocabWord **pDictionary, int size) { // names[x]->fnames, names[y]->fnames
	VocabWord *temp = pDictionary[0];
	for (int x = 0; x < (size - 1); x++) {
		for (int y = x + 1; y < size; y++) {
			if (pDictionary[x]->sortWord.compare(pDictionary[y]->sortWord) > 0) {
				temp = pDictionary[x];
				pDictionary[x] = pDictionary[y];
				pDictionary[y] = temp;
			}
		}
	}
	return pDictionary;
}


VocabWord** sortWordsInEnglish(VocabWord **pDictionary, int size) { // names[x]->fnames, names[y]->fnames
	VocabWord *temp = pDictionary[0];
	string verb = "verb", tempString = "", missUpper = "Miss", missLower = "miss",
		tuesdayUpper = "Tuesday", tuesdayLower = "tuesday", frenchUpper = "French", frenchLower = "french";
	int length;

	for (int z = 0; z < size; z++) {
		if (verb.compare(pDictionary[z]->partOfSpeech) == 0) { // determines whether the part of speech of the english word is a verb
			length = (pDictionary[z]->englishWord).length();
			pDictionary[z]->englishWord = (pDictionary[z]->englishWord).substr(3, length); // clips off the "to" in "to go," etc. (infinitive version of English verb)
		}
		if (missUpper.compare(pDictionary[z]->englishWord) == 0) {
			pDictionary[z]->englishWord = missLower;
		}
		if (tuesdayUpper.compare(pDictionary[z]->englishWord) == 0) {
			pDictionary[z]->englishWord = tuesdayLower;
		}
		if (frenchUpper.compare(pDictionary[z]->englishWord) == 0) {
			pDictionary[z]->englishWord = frenchLower;
		}
	}

	for (int x = 0; x < (size - 1); x++) {
		for (int y = x + 1; y < size; y++) {
			if (pDictionary[x]->englishWord.compare(pDictionary[y]->englishWord) > 0) {
				temp = pDictionary[x];
				pDictionary[x] = pDictionary[y];
				pDictionary[y] = temp;
			}
		}
	}

	for (int z = 0; z < size; z++) { // adds the "to" back to infinitive verbs after sorting without
		if (verb.compare(pDictionary[z]->partOfSpeech) == 0) { // determines whether the part of speech of the english word is a verb
			pDictionary[z]->englishWord = "to " + (pDictionary[z]->englishWord); // clips off the "to" in "to go," etc. (infinitive version of English verb)
		}
		if (missLower.compare(pDictionary[z]->englishWord) == 0) { //changes "Miss" back if applicable
			pDictionary[z]->englishWord = missUpper;
		}
		if (tuesdayLower.compare(pDictionary[z]->englishWord) == 0) { // changes "Tuesday" back if applicable
			pDictionary[z]->englishWord = tuesdayUpper;
		}
		if (frenchLower.compare(pDictionary[z]->englishWord) == 0) { // changes "French" back if applicable
			pDictionary[z]->englishWord = frenchUpper;
		}
	}
	return pDictionary;
}

string getWord() {
	unsigned char key, key2;
	string inputWord = "";

	cout << "\nEntry: ";
	while ((key = _getch()) != '\r') {

		if (0 == key) {
			key2 = _getch();
			switch (key2)
			{
			case 59: inputWord += static_cast<char>(153); cout << static_cast<char>(153); break; // f1 -- Ö
			case 60: inputWord += static_cast<char>(132); cout << static_cast<char>(132); break; // f2 -- ä
			case 61: inputWord += static_cast<char>(135); cout << static_cast<char>(135); break; // f3 -- ç
			case 62: inputWord += static_cast<char>(130); cout << static_cast<char>(130); break; // f4 -- é
			case 63: inputWord += static_cast<char>(136); cout << static_cast<char>(136); break; // f5 -- ê
			case 64: inputWord += static_cast<char>(138); cout << static_cast<char>(138); break; // f6 -- è
			case 65: inputWord += static_cast<char>(148); cout << static_cast<char>(148); break; // f7 -- ö
			case 66: inputWord += static_cast<char>(129); cout << static_cast<char>(129); break; // f8 -- ü
			}
		}
		else if (key == ' ' || key == '\'' || key == '/' || (key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')
			|| key == '(' || key == ')') {
			inputWord += key; // just save it in the string
			cout << key;
		}
		else if (key == static_cast<char>(8)) {
			cout << key << ' ' << key;
			inputWord = inputWord.substr(0, inputWord.length() - 1);
		}
	}
	cout << endl;
	return inputWord;
}



void manuallyImportDictionary(VocabWord * dictionarySet, int size) {
	char addNextWord = 'y';
	int i = 0;
	system("cls");
	printSpecialCharHelp();

	for (int i = 0; i < size && addNextWord != 'n' && addNextWord != 'N'; i++) {
		cout << "\nEnter a new word (including special characters, definite articles): ";
		(dictionarySet + i)->displayWord = getWord();

		cout << "\nEnter the word without special characters or definite articles: ";
		(dictionarySet + i)->sortWord = getWord();

		cout << "\nEnter the part of speech: ";
		(dictionarySet + i)->partOfSpeech = getWord();

		cout << "\nEnter the meaning in English: ";
		(dictionarySet + i)->englishWord = getWord();

		cout << "\nEnter the source language for the word: ";
		(dictionarySet + i)->sourceLanguage = getWord();

		system("cls");
		printSpecialCharHelp();
	}
}


void splitLine(string line, string segmentArr[], int size) { // size is numPipes + 1 - 4 pipes per line, so 5 is our size
	int pipeIndex = 0;
	for (int x = 0; x < size; x++) {
		segmentArr[x] = line.substr(pipeIndex, line.find('|', pipeIndex) - pipeIndex); // store each segment in array
		if (x != size - 1)
			pipeIndex = line.find('|', pipeIndex) + 1; // as long as we haven't reached the last pipe, update pipeIndex
	}
}

void loadStructArray(VocabWord *dictionary, int DICT_SIZE, ifstream &inFile) { // dictionary size is 100 words, array name is dictionary
	const int NUM_STRUCT_FIELDS = 5; // 5 string fields in our struct variable
	string segmentArr[NUM_STRUCT_FIELDS];
	string line;

	for (int i = 0; i < DICT_SIZE; i++) {
		getline(inFile >> ws, line);
		splitLine(line, segmentArr, NUM_STRUCT_FIELDS);

		(dictionary + i)->displayWord = segmentArr[0];
		(dictionary + i)->sortWord = segmentArr[1];
		(dictionary + i)->partOfSpeech = segmentArr[2];
		(dictionary + i)->englishWord = segmentArr[3];
		(dictionary + i)->sourceLanguage = segmentArr[4];
	}

}


void printDictionary(VocabWord *dictionary, int size, ostream &os) {
	for (int i = 0; i < size; i++) {
		os << (dictionary + i)->displayWord
			<< "|" << (dictionary + i)->sortWord
			<< "|" << (dictionary + i)->partOfSpeech
			<< "|" << (dictionary + i)->englishWord
			<< "|" << (dictionary + i)->sourceLanguage << endl;
	}
}

char dictionaryImportMenu() {
	char selection;
	cout << "\nWould you like to upload a txt file dictionary, or create the dictionary manually?\n"
		<< "(1) Upload a premade txt dictionary \n"
		<< "(2) Create the dictionary manually \n\n";
	selection = _getch();
	return selection;
}


bool createWordList(VocabWord * dictionary, int DICT_SIZE, ifstream &inFile, ofstream &outFile) {
	string noDictionaryErrorMsg = "\nYou must import a dictionary first!\nPress any key to return to the menu.",
		hasDictionaryErrorMsg = "\nThe dictionary already exists; you cannot import another one. \nPress any key to return to the menu.";
	char importChoice;

	// code/function call to import new dictionary
	importChoice = dictionaryImportMenu();
	if (importChoice == '1') {
		inFile.open("dictionary.txt");
		if (inFile.fail()) {
			cout << "\nERROR: no dictionary found.\n";
			system("pause");
			return false;
		}
		loadStructArray(dictionary, DICT_SIZE, inFile);
		inFile.close();
		cout << "Dictionary loaded.\nPress any key to continue...";
		_getch();
		return true;
	} // premade txt
	else if (importChoice == '2') { // manual entry
		manuallyImportDictionary(dictionary, DICT_SIZE);
		outFile.open("dictionary.txt");
		printDictionary(dictionary, DICT_SIZE, outFile);
		outFile.close();
		cout << "\nSaved new dictionary. \nPress any key to continue...";
		_getch();
		return true;
	}
	else {
		cout << "Invalid selection. Press any key to return to the main menu...\n";
		_getch();
		return false;
	}
}

void printSpecialCharHelp() {
	cout << "************************************"
		<< "\n\t*Special Characters*"
		<< "\n\t  F1: " << static_cast<char>(153) << "\t    F5:  " << static_cast<char>(136)   // f1 -- Ö     // f5 -- ê
		<< "\n\t  F2: " << static_cast<char>(132) << "\t    F6:  " << static_cast<char>(138)   // f2 -- ä     // f6 -- è
		<< "\n\t  F3: " << static_cast<char>(135) << "\t    F7:  " << static_cast<char>(148)   // f3 -- ç     // f7 -- ö
		<< "\n\t  F4: " << static_cast<char>(130) << "\t    F8:  " << static_cast<char>(129)   // f4 -- é     // f8 -- ü 
		<< "\n************************************";
}

int countPartOfSpeech(VocabWord **pDictionary, int size, string partOfSpeech) { // returns logical size of new array of ptrs to struct
	string tempPOS, tempPOS2;
	int length = partOfSpeech.length();
	int total = 0;

	for (int x = 0; x < size; x++) {
		tempPOS = (pDictionary[x]->partOfSpeech).substr(0, length); // extracts substring to make (m), etc, count as noun, etc
		if (partOfSpeech == "adverb" && (pDictionary[x]->partOfSpeech).length() >(7 + length)) {
			tempPOS2 = (pDictionary[x]->partOfSpeech).substr(10, length); // this section exists to deal with words like "gut"
		}
		else tempPOS2 = tempPOS;

		if (pDictionary[x]->partOfSpeech.compare(partOfSpeech) == 0 || tempPOS.compare(partOfSpeech) == 0 || tempPOS2.compare(partOfSpeech) == 0) {
			total++;
		}
	}
	return total;
}

void loadPartOfSpeechArray(VocabWord **pDictionary, int pDictSize, VocabWord ** pDictToPrint, int logicalSize, string partOfSpeech) {
	string tempPOS, tempPOS2;
	int length = partOfSpeech.length();
	int newArrayIndex = 0;

	for (int x = 0; x < pDictSize; x++) {
		tempPOS = (pDictionary[x]->partOfSpeech).substr(0, length); // extracts substring to make (m), etc, count as noun, etc
		if (partOfSpeech == "adverb" && (pDictionary[x]->partOfSpeech).length() >(7 + length)) {
			tempPOS2 = (pDictionary[x]->partOfSpeech).substr(10, length); // this section exists to deal with words like "gut"
		}
		else tempPOS2 = tempPOS;

		if (pDictionary[x]->partOfSpeech.compare(partOfSpeech) == 0 || tempPOS.compare(partOfSpeech) == 0 || tempPOS2.compare(partOfSpeech) == 0) {
			pDictToPrint[newArrayIndex] = pDictionary[x];
			newArrayIndex++;
		}
	}
	for (int y = 0; y < newArrayIndex; y++) {
		cout << pDictToPrint[y]->displayWord << "\t" << pDictToPrint[y]->partOfSpeech << endl;
	}

	system("pause");
}

void printPartOfSpeech(VocabWord **pDictionary, int pDictSize, int logicalSize, string partOfSpeech, bool isEnglish) {
	VocabWord **pDictToPrint = nullptr;
	pDictToPrint = new VocabWord*[logicalSize]; // dynamically allocate array to hold new words
	string tempPOS, tempPOS2;
	int length = partOfSpeech.length();
	int newArrayIndex = 0;
	bool hasElements = false; // bool variable to denote whether there are any elements that correspond
							  // to our given language to print/source language
	string printLanguage = selectLanguage();

	for (int x = 0; x < pDictSize; x++) {
		tempPOS = (pDictionary[x]->partOfSpeech).substr(0, length); // extracts substring to make (m), etc, count as noun, etc
		if (partOfSpeech == "adverb" && (pDictionary[x]->partOfSpeech).length() >(7 + length)) { // adverb is a special case
			tempPOS2 = (pDictionary[x]->partOfSpeech).substr(10, length); // this section exists to deal with words like "gut"
		}
		else tempPOS2 = tempPOS;

		if (pDictionary[x]->partOfSpeech.compare(partOfSpeech) == 0 || tempPOS.compare(partOfSpeech) == 0
			|| tempPOS2.compare(partOfSpeech) == 0) {
			pDictToPrint[newArrayIndex] = pDictionary[x];
			newArrayIndex++;
			if (pDictionary[x]->sourceLanguage == printLanguage || printLanguage == "All")
				hasElements = true;
		}
	}
	if (isEnglish) {
		sortWordsInEnglish(pDictToPrint, logicalSize);
	}
	else {
		sortWords(pDictToPrint, logicalSize);
	}
	if (hasElements)
		printStructArray(pDictToPrint, logicalSize, printLanguage, isEnglish);
	else {
		cout << "\nNo words match your query.\n";
		system("pause");
	}
	delete[] pDictToPrint;
	pDictToPrint = { nullptr };
}


void printStructArray(VocabWord **wordsToPrint, int size, string printLanguage, bool isEnglish) {
	cout << endl;
	if (!isEnglish) {
		cout << " " << left << setw(20) << "Non-English Word" << setw(20) << "Part of Speech"
			<< setw(20) << "English Word" << setw(20) << "Source Language" << endl;
		cout << " ----------------------------------------------------------------------------\n";

		for (int i = 0; i < size; i++) {
			if ((wordsToPrint[i]->sourceLanguage) == printLanguage || printLanguage == "All") {
				cout << " " << left << setw(20) << wordsToPrint[i]->displayWord << setw(20) << wordsToPrint[i]->partOfSpeech
					<< setw(20) << wordsToPrint[i]->englishWord << setw(20) << wordsToPrint[i]->sourceLanguage << endl;
			}
		}
	}
	else {
		cout << " " << left << setw(20) << "English Word" << setw(20) << "Part of Speech"
			<< setw(20) << "Non-English Word" << setw(20) << "Source Language" << endl;
		cout << " ----------------------------------------------------------------------------\n";

		for (int i = 0; i < size; i++) {
			if ((wordsToPrint[i]->sourceLanguage) == printLanguage || printLanguage == "All") {
				cout << " " << left << setw(20) << wordsToPrint[i]->englishWord << setw(20) << wordsToPrint[i]->partOfSpeech
					<< setw(20) << wordsToPrint[i]->displayWord << setw(20) << wordsToPrint[i]->sourceLanguage << endl;
			}
		}
	}
	system("pause");
}

void checkDictionary(VocabWord **pDictionary, int DICT_SIZE, string partOfSpeech, bool hasDictionaryImported, bool isEnglish) {
	string printLanguage,
		noDictionaryErrorMsg = "\nYou must import a dictionary first!\nPress any key to return to the menu.";
	int logicalSize;

	if (!hasDictionaryImported) {
		cout << noDictionaryErrorMsg;
		_getch();
		return;
	}

	logicalSize = countPartOfSpeech(pDictionary, DICT_SIZE, partOfSpeech);
	printPartOfSpeech(pDictionary, DICT_SIZE, logicalSize, partOfSpeech, isEnglish); // false -> not English
	return;
}

int wordSearch(VocabWord **pDictionary, int size, string inputWord) {
	VocabWord *pDictToPrint[10];
	int logicalSize = 0;
	bool isEnglish = false, wordIsFound = false;
	string englishMeaning = inputWord;

	for (int y = 0; y < size; y++) {
		if ((inputWord.compare(pDictionary[y]->englishWord) == 0)) {
			isEnglish = true;
			wordIsFound = true;
		}
		if ((inputWord.compare(pDictionary[y]->sortWord) == 0) || (inputWord.compare(pDictionary[y]->displayWord) == 0)) {
			isEnglish = false;
			wordIsFound = true;
			englishMeaning = pDictionary[y]->englishWord;
		}
	}

	for (int x = 0; x < size; x++) {

		if ((englishMeaning.compare(pDictionary[x]->englishWord) == 0) || (inputWord.compare(pDictionary[x]->englishWord) == 0)) {
			pDictToPrint[logicalSize] = pDictionary[x];
			logicalSize++;
		}
	}

	if (wordIsFound)
		printStructArray(pDictToPrint, logicalSize, "All", isEnglish); // is english = false
	else {
		cout << "\nThat word is not in my dictionary.\n";
		system("pause");
	}

	return logicalSize;
}
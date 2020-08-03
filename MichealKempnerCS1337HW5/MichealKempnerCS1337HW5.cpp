/*This is the Wild Kingdom Psychic Thingy
 A program developed by Micheal Kempner to guess an animal the user is thinking of
 Pseudocode is as follows
 -create a struct which will house strings relating to animal names and questions
 -build a tree which asks a single beginning question with only one guess for each branch
 -if the guess is correct, start the program over from the root of the tree
 -if the guess is incorrect, create a new node
 -get animal name, a yes or no question to differentiate, and the answer to said question from the user
 -set pointers depending on user input
 -restart game with new pointers
 -continue forever
 
 Changelog:
 
    7/14/2020
        -Created animalNode struct
        -Created initThePointers function
        -Created main function
        -Created startTheGame function
        -Created askQuestions function
        -Created validateInput function
    
    7/15/2020
        -Revised method for generating tree, decided to build tree from two preloaded answers to simplify user experience
        -Created buildTheTree function
        -Removed signifcant portions from askQuestions function to create addNewAnimal function
        -First working copy of the game completed
        
    7/17/2020
        -Updated documentation for readability
        -Removed debugging code
        */

#include <iostream>
#include "debug.h"
#include "utilities.h"

struct animalNode { 
    string question;
    string animal;
    animalNode* yesAnswer;
    animalNode* noAnswer;
}; //Nodes which contain information relevant to the guess. Separate question and animal strings will likely not be used simultaneously, but make for easier-to-read code

animalNode* treeHead; //always points to the first node on the tree
animalNode* currentNode; //points to the current node (in this case, the current question)
animalNode* prevNode; //unused, was for tracking previous nodes in prior builds
animalNode* nextNode; //points to upcoming node, also unused due to simplification of code

void initThePointers(); //initializes pointers
void startTheGame(); //starts the game over at the first node
void askQuestions(); //asks user yes or no questions until a guess can be made
bool validateInput(string); //validates user input
void addNewAnimal(); //creates new animal, question and answer when incorrect guess occurs
void buildTheTree(); //creates first nodes on tree



int main()
{
    initThePointers();
    show("Welcome to The Wild Kingdom Psychic Thingy! I know everything! Yes, even that!");
    show("Best me in an animal guessing game and win a fabulous prize: honor!\nLet us begin!");
    buildTheTree();
    startTheGame(); 
    return 0;
}

void initThePointers() {
    treeHead = nullptr;
    currentNode = nullptr;
    prevNode = nullptr;
    nextNode = nullptr;
}

void buildTheTree() {
    treeHead = new animalNode; 
    treeHead->yesAnswer = new animalNode;
    treeHead->noAnswer = new animalNode;    //at this point, three nodes have been made, one for the first question, and one for each initial guess which will likely be incorrect
    treeHead->noAnswer->animal = "human"; 
    treeHead->yesAnswer->animal = "megalodon";
    treeHead->animal = ""; 
    treeHead->question = "Is your animal extinct?"; //makes the first question as generic as possible
    treeHead->yesAnswer->yesAnswer = treeHead->yesAnswer->noAnswer = nullptr;
    treeHead->noAnswer->yesAnswer = treeHead->noAnswer->noAnswer = nullptr; //initializes pointers for first answer nodes
}

void askQuestions() {
    string answer;
    bool goodInput = false;

    while (currentNode != nullptr) {
        if (currentNode->yesAnswer == nullptr && currentNode->noAnswer == nullptr) { //if the current node has no pointers directing it to move forward, the program has progressed as far as it can and must guess
            cout << "Is your animal the majestic " << currentNode->animal << "?\n"; //It all comes down to this. Will man (or woman, or non-binary person) emerge victorious over machine?
            getline(cin, answer);
            goodInput = validateInput(answer);
            while (goodInput != true) {
                cout << "You must answer \"y\" for \"yes\" or \"n\" for \"no\"\nPlease try again\n";
                askQuestions();
                goodInput = validateInput(answer);
            }
            if (goodInput == true) {
                if (answer == "y" || answer == "Y") {
                    show("Haha! I knew it! I win!"); //The program celebrates its well-earned victory. That was for the drilling machine that lost to John Henry.
                    startTheGame();
                }
                else if (answer == "n" || answer == "N") { //The machine loses, humanity wins the battle against artificial intelligence... this time.
                    addNewAnimal();
                }
            }

        }

        //a loop for a situation in which either a yes or no answer will continue the game
        else if (currentNode->yesAnswer != nullptr && currentNode->noAnswer != nullptr) { 
            cout << currentNode->question << endl;
            getline(cin, answer);
            goodInput = validateInput(answer);
            while (goodInput != true) {
                cout << "You must answer \"y\" for \"yes\" or \"n\" for \"no\"\nPlease try again\n";
                askQuestions();
                goodInput = validateInput(answer);
            }
            if (goodInput == true) {
                if (answer == "y" || answer == "Y") {
                    currentNode = currentNode->yesAnswer; //the pointer moves ahead and the game proceeds
                    askQuestions();
                }
                else if (answer == "n" || answer == "N") {
                    currentNode = currentNode->noAnswer; //we just went over this on line 118, but ok. the pointer moves ahead and the game proceeds
                    askQuestions;
                }
            }
        }

        //a loop for a situation in which the game may continue or end depending on the user's answer
        else if ((currentNode->yesAnswer == nullptr && currentNode->noAnswer != nullptr) || (currentNode->yesAnswer != nullptr && currentNode->noAnswer == nullptr)) {
            cout << currentNode->question << endl;
            getline(cin, answer);
            goodInput = validateInput(answer);
            while (goodInput != true) {
                cout << "You must answer \"y\" for \"yes\" or \"n\" for \"no\"\nPlease try again\n";
                askQuestions();
                goodInput = validateInput(answer);
            }
            if (goodInput == true) {
                if ((answer == "y" || answer == "Y") && currentNode->yesAnswer != nullptr) {
                    currentNode = currentNode->yesAnswer;
                    askQuestions();
                }
                else if ((answer == "y" || answer == "Y") && currentNode->yesAnswer == nullptr) {
                    addNewAnimal();
                }
                else if ((answer == "n" || answer == "N") && currentNode->noAnswer != nullptr) {
                    currentNode = currentNode->noAnswer;
                    askQuestions;
                }
                else if ((answer == "n" || answer == "N") && currentNode->noAnswer == nullptr) {
                    addNewAnimal();
                }
            }
        }
    }
   

}

void addNewAnimal() {
    bool goodInput = false;
    string newAnswer;
    string tempAnimal, tempQuestion;
    animalNode* newAnimal = new animalNode; //create a node for the new animal the user was thinking of
    animalNode* oldAnimal = new animalNode; //create a node for the incorrect guess to move to
    newAnimal->yesAnswer = newAnimal->noAnswer = nullptr;
    oldAnimal->yesAnswer = oldAnimal->noAnswer = nullptr;

    oldAnimal->animal = currentNode->animal; //place the incorrect animal in the new node
    
    show("Curses! You have bested me! What is your animal called?");
    getline(cin, tempAnimal); //user reveals the correct answer and it is assigned to the new node
    newAnimal->animal = tempAnimal;

    cout << "How clever of you! And what yes or no question might I ask tell the majestic " << currentNode->animal << " from the fearsome " << tempAnimal << "?\n";
    getline(cin, tempQuestion); //user creates a question to differentiate between the two animals
    newAnimal->question = tempQuestion;

    cout << "And for the fearsome " << tempAnimal << ", is the answer yes or no? (y or n)?\n";
    getline(cin, newAnswer);
    goodInput = validateInput(newAnswer);

    while (goodInput != true) {
        cout << "You must answer \"y\" for \"yes\" or \"n\" for \"no\"\nPlease try again\n";
        cin >> newAnswer;
        goodInput = validateInput(newAnswer);
    }
    if (validateInput(newAnswer)) { //places the answers in the corresponding nodes depending on user input
        if (newAnswer == "y" || newAnswer == "Y") {
            currentNode->question = newAnimal->question;
            currentNode->yesAnswer = newAnimal;
            currentNode->noAnswer = oldAnimal;
            startTheGame();
        }
        else if (newAnswer == "n" || newAnswer == "N") {
            currentNode->question = newAnimal->question;
            currentNode->noAnswer = newAnimal;
            currentNode->yesAnswer = oldAnimal;
            startTheGame();
        }
    }
}

void startTheGame() {
    currentNode = treeHead; //resets node to beginning
    show("Please think of an animal and tell me when you are ready...");
    pause();
    askQuestions(); //calls askQuestions function to begin line of questioning
    return;
}

bool validateInput(string answer) {
    if (answer == "y" || answer == "Y" || answer == "n" || answer == "N")
        return true;
    else
        return false;
}


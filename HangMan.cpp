#include <iostream>
#include <vector>
#include <cstdlib>

const int TURNS = 6;

void ChooseRandomWord(std::string& word, std::vector<std::string> list, int& wordLength, std::vector<char>& blank, int round);

void PrintWordAndGuesses(std::vector<char> word, std::vector<char> incorrectGuesses, int correctGuesses);

bool GameFinished(std::string word, std::vector<char> correctGuesses, int incorrectGuesses);

void PrintBody(int incorrectGuesses);

int main() {

    //Initialize vector with 10 words of different lengths, continue play variable and number of rounds played
    std::vector<std::string> listOfWords{ "hello", "tag", "blue", "bagels", "bananas", "it", "keyboard", "playhouse", "television", "automobiles" };
    char continuePlay = 'y';
    int roundsPlayed = 0;


    //While loop to facilitate multiple rounds
    while (continuePlay == 'y') {


        //declare and initialize variables needed for game
        std::vector<char> hiddenWord;
        std::vector<char> incorrectUserGuesses;
        std::string wordToGuess;
        int lengthOfWord = 0;
        int numCorrectGuesses = 0;
        int numIncorrectGuesses = 0;
        char userGuess;

        //Generates random word from list
        ChooseRandomWord(wordToGuess, listOfWords, lengthOfWord, hiddenWord, roundsPlayed);

        //Greets the user and presents length of word to guess
        std::cout << "----- Welcome to HANG-MAN -----" << std::endl << std::endl;
        std::cout << "Your word is " << lengthOfWord << " characters long." << std::endl;

        //While loop checks if user has guessed word or reached the maximum number of guesses
        while (!GameFinished(wordToGuess, hiddenWord, numIncorrectGuesses)) {
            bool isCorrectGuess = false;
            std::cout << "Guess a letter: ";
            std::cin >> userGuess;

            //For loop compares user guess to random word
            for (int i = 0; i < wordToGuess.size(); i++) {
                if (userGuess == wordToGuess[i]) {
                    hiddenWord.at(i) = userGuess;
                    isCorrectGuess = true;
                    numCorrectGuesses++;
                }
            }

            //If incorrect, user guess is appended to incorrect user guesses and incorrect guesses increments
            if (!isCorrectGuess) {
                incorrectUserGuesses.push_back(userGuess);
                numIncorrectGuesses++;
            }

            //Word and guesses are printed out include total number of guesses
            PrintWordAndGuesses(hiddenWord, incorrectUserGuesses, numCorrectGuesses);

            //Gallows and Hangman body are printed based on number of incorrect guesses
            PrintBody(numIncorrectGuesses);
        }

        //If user guessed word under 6 turns (Number of hangman body parts), they win
        if (numIncorrectGuesses < TURNS) {
            std::cout << "CONGRATULATIONS! You correctly guessed the word!" << std::endl;
            std::cout << "It took you a total of: " << numCorrectGuesses + incorrectUserGuesses.size() << " guesses." << std::endl;
        }

        //Else, they lose.
        else {
            std::cout << "Sorry! You weren't able to guess the word in time." << std::endl;
            std::cout << "Total guesses: " << numIncorrectGuesses + numCorrectGuesses << std::endl;
        }


        //User prompted to play again
        std::cout << "Would you like to play again? (y/n)";
        std::cin >> continuePlay;
        roundsPlayed++;
    }

    std::cout << std::endl << "Thank you for playing! Quitting program...";

    return 0;
}


//Chooses a random word from the vector of strings for the word the user to guess
void ChooseRandomWord(std::string& word, std::vector<std::string> list, int& wordLength, std::vector<char>& blank, int rounds) {
    //Random is seeded based on round
    srand(rounds);
    word = list.at(rand() % 10);
    wordLength = word.size();

    for (int i = 0; i < wordLength; i++) {
        blank.push_back('_');
    }
}

//Prints vector of char
void PrintWordAndGuesses(std::vector<char> word, std::vector<char> incorrectGuesses, int correctGuesses) {
    std::cout << "----------------------" << std::endl;

    std::cout << "Correct guesses: " << correctGuesses << std::endl;
    for (int i = 0; i < word.size(); i++) {
        std::cout << word.at(i);
    }

    std::cout << std::endl << std::endl;
    std::cout << "Incorrect guesses: " << incorrectGuesses.size() << std::endl;

    for (int i = 0; i < incorrectGuesses.size(); i++) {
        std::cout << incorrectGuesses.at(i);
    }
    std::cout << std::endl << std::endl << "Total guesses: " << correctGuesses + incorrectGuesses.size() << std::endl;
    std::cout << "----------------------" << std::endl;
    std::cout << std::endl << std::endl;
}

//Checks to see if user has guessed the word correctly
bool GameFinished(std::string word, std::vector<char> correctGuesses, int incorrectGuesses) {
    if (incorrectGuesses == TURNS) {
        return true;
    }
    for (int i = 0; i < correctGuesses.size(); i++) {
        if (word[i] != correctGuesses.at(i)) {
            return false;
        }
    }
    return true;
}

//Print gallows with the hangman body
void PrintBody(int incorrectGuesses) {

    switch (incorrectGuesses) {
    case 1:
        std::cout << "----|" << std::endl;
        std::cout << "|   0   " << std::endl;
        std::cout << "|" << std::endl;
        std::cout << "|" << std::endl;
        std::cout << "|-------" << std::endl;
        break;
    case 2:
        std::cout << "----|" << std::endl;
        std::cout << "|   0   " << std::endl;
        std::cout << "|   |" << std::endl;
        std::cout << "|" << std::endl;
        std::cout << "|-------" << std::endl;
        break;
    case 3:
        std::cout << "----|" << std::endl;
        std::cout << "|   0   " << std::endl;
        std::cout << "| o-|" << std::endl;
        std::cout << "|" << std::endl;
        std::cout << "|-------" << std::endl;
        break;
    case 4:
        std::cout << "----|" << std::endl;
        std::cout << "|   0   " << std::endl;
        std::cout << "| o-|-o" << std::endl;
        std::cout << "|" << std::endl;
        std::cout << "|-------" << std::endl;
        break;
    case 5:
        std::cout << "----|" << std::endl;
        std::cout << "|   0   " << std::endl;
        std::cout << "| o-|-o" << std::endl;
        std::cout << "|  |" << std::endl;
        std::cout << "|-------" << std::endl;
        break;
    case 6:
        std::cout << "----|" << std::endl;
        std::cout << "|   0   " << std::endl;
        std::cout << "| o-|-o" << std::endl;
        std::cout << "|  | |" << std::endl;
        std::cout << "|-------" << std::endl;
        break;

    }
}
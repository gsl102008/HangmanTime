#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Class for the Hangman game
class HangmanGame {
private:
    string word;             // The word to guess
    string guessedWord;      // The word with guessed letters revealed
    int maxAttempts;         // Maximum number of attempts allowed
    int remainingAttempts;   // Remaining attempts
    vector<char> guessedLetters; // Letters already guessed by the player
public:
    HangmanGame(string w, int maxAtt) : word(w), maxAttempts(maxAtt), remainingAttempts(maxAtt) {
        // Initialize guessedWord with underscores
        guessedWord = string(word.length(), '_');
    }

    // Function to start the game
    void startGame() {
        cout << "Welcome to Hangman!" << endl;
        cout << "Guess the word: ";
        displayGuessedWord();
        cout << endl;
    }

    // Function to display the word with guessed letters revealed
    void displayGuessedWord() {
        for (char c : guessedWord) {
            cout << c << " ";
        }
        cout << endl;
    }

    // Function to make a guess
    void makeGuess(char guess) {
        if (isalpha(guess)) {
            guess = tolower(guess); // Convert to lowercase
            if (find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
                cout << "You already guessed '" << guess << "'. Try another letter." << endl;
            } else {
                guessedLetters.push_back(guess);
                bool found = false;
                for (int i = 0; i < word.length(); ++i) {
                    if (word[i] == guess) {
                        guessedWord[i] = guess;
                        found = true;
                    }
                }
                if (!found) {
                    cout << "Incorrect guess!" << endl;
                    --remainingAttempts;
                }
            }
        } else {
            cout << "Invalid input! Please enter a valid letter." << endl;
        }
    }

    // Function to check if the game is over
    bool isGameOver() {
        return (remainingAttempts == 0) || (guessedWord == word);
    }

    // Function to display game result
    void displayResult() {
        if (guessedWord == word) {
            cout << "Congratulations! You guessed the word '" << word << "'!" << endl;
        } else {
            cout << "Sorry, you ran out of attempts. The word was '" << word << "'." << endl;
        }
    }
};

int main() {
    // Array of words to choose from
    vector<string> words = {"hangman", "programming", "computer", "algorithm", "cryptography"};

    // Seed the random number generator
    srand(time(nullptr));

    // Choose a random word from the array
    string selectedWord = words[rand() % words.size()];

    // Maximum attempts allowed
    int maxAttempts = 6;

    // Create an instance of HangmanGame
    HangmanGame game(selectedWord, maxAttempts);

    // Start the game
    game.startGame();

    // Game loop
    while (!game.isGameOver()) {
        cout << "Enter a letter: ";
        char guess;
        cin >> guess;
        game.makeGuess(guess);
        game.displayGuessedWord();
        cout << "Remaining attempts: " << game.remainingAttempts << endl;
    }

    // Display game result
    game.displayResult();

    return 0;
}

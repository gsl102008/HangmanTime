#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Class for Hangman game
class HangmanGame {
private:
    string word;             // The word to guess
    string guessedWord;      // The word with guessed letters revealed
    int maxAttempts;         // Maximum number of attempts allowed
    int remainingAttempts;   // Remaining attempts
    vector<char> guessedLetters; // Letters already guessed by the player
public:
    HangmanGame(string w, int maxAtt) : word(w), maxAttempts(maxAtt), remainingAttempts(maxAtt) {
        // Initialize guessedWord 
        guessedWord = string(word.length(), '_');
    }

    // Start the game
    void startGame() {
        cout << "Welcome to Hangman!" << endl;
        cout << "Guess the word: ";
        displayGuessedWord();
        cout << endl;
    }

    // Displey the word with guessed letters revealed
    void displayGuessedWord() {
        for (char c : guessedWord) {
            cout << c << " ";
        }
        cout << endl;
    }

    // Make a guess
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

    bool isGameOver() {
        return (remainingAttempts == 0) || (guessedWord == word);
    }

    void displayResult() {
        if (guessedWord == word) {
            cout << "Congratulations! You guessed the word '" << word << "'!" << endl;
        } else {
            cout << "Sorry, you ran out of attempts. The word was '" << word << "'." << endl;
        }
    }
};

int main() {
    // Words to choose from
    vector<string> words = {"goonies", "ghostbusters", "gremlins", "dune", "batman", "godzilla"};

    srand(time(nullptr));

    string selectedWord = words[rand() % words.size()];

    int maxAttempts = 6;

    HangmanGame game(selectedWord, maxAttempts);

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

    game.displayResult();

    return 0;
}

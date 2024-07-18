#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

// Function to display the welcome logo
void displayWelcomeLogo() {
    cout << "**************************************************" << endl;
    cout << "*                                                *" << endl;
    cout << "*       Welcome to the Higher or Lower Game!     *" << endl;
    cout << "*                                                *" << endl;
    cout << "*                 Best of Luck!                  *" << endl;
    cout << "*                                                *" << endl;
    cout << "**************************************************" << endl;
    cout << endl;
}

// Function to display sparkles for winning
void displaySparkles() {
    cout << "*****************************************" << endl;
    cout << "*   *     *     * *     *     *     *   *" << endl;
    cout << "*   Congratulations! You win!    *     *" << endl;
    cout << "*   *     *     * *     *     *     *   *" << endl;
    cout << "*****************************************" << endl;
}

// Function to display a sad face for losing
void displaySadFace() {
    cout << "*****************************************" << endl;
    cout << "*        Better luck next time! :(      *" << endl;
    cout << "*****************************************" << endl;
}

// Function to display the last played rounds
void displayLastRounds(const vector<string>& rounds) {
    if (rounds.empty()) {
        cout << "No rounds have been played yet." << endl;
    } else {
        cout << "Last 3 rounds results:" << endl;
        for (const string& round : rounds) {
            cout << round << endl;
        }
    }
}

// Function to display player statistics
void displayStats(int gamesPlayed, int wins, int losses) {
    cout << "*****************************************" << endl;
    cout << "*            Player Statistics           *" << endl;
    cout << "*****************************************" << endl;
    cout << "* Games Played: " << gamesPlayed << "                       *" << endl;
    cout << "* Wins: " << wins << "                                *" << endl;
    cout << "* Losses: " << losses << "                              *" << endl;
    cout << "*****************************************" << endl;
}

int main() {
    srand(time(0)); // Seed the random number generator

    vector<string> lastRounds; // Vector to store last 3 rounds' results
    int gamesPlayed = 0, wins = 0, losses = 0; // Variables to track game statistics
    char choice; // Variable to store user's choice

    // Main game loop
    while (true) {
        displayWelcomeLogo(); // Display welcome logo and message
        cout << "Choose an option:" << endl;
        cout << "1. Start a new game" << endl;
        cout << "2. Display the last 3 rounds" << endl;
        cout << "3. Display player statistics" << endl;
        cout << "4. Exit" << endl;
        cin >> choice; // Read user's choice

        // Handling user's choice
        if (choice == '1') { // Start a new game
            int maxRange = 100; // Default maximum range for guessing
            int attempts = 5; // Default number of attempts allowed

            // Display difficulty options and read user's choice
            cout << "Select difficulty level: " << endl;
            cout << "1. Easy (1-50, 7 attempts)" << endl;
            cout << "2. Medium (1-100, 5 attempts)" << endl;
            cout << "3. Hard (1-200, 3 attempts)" << endl;
            int difficulty;
            cin >> difficulty;

            // Adjust game parameters based on difficulty chosen
            if (difficulty == 1) {
                maxRange = 50;
                attempts = 7;
            } else if (difficulty == 3) {
                maxRange = 200;
                attempts = 3;
            }

            int ranNum = rand() % maxRange + 1; // Generate a random number
            bool win = false; // Flag to track if the player wins
            int guess; // Variable to store player's guess
            int pTries = 0; // Variable to count player's attempts
            string result; // String to store game result

            // Game loop for current game
            while (!win && pTries < attempts) {
                if (pTries == attempts - 1) { // Last attempt special message
                    cout << "This is your last attempt! Here are 5 numbers to choose from: ";
                    int options[5];
                    bool numberIncluded = false;

                    // Generate 5 random options for the player
                    for (int i = 0; i < 5; ++i) {
                        options[i] = rand() % maxRange + 1;
                    }

                    if (!numberIncluded) {
                        options[rand() % 5] = ranNum; // Ensure correct number is included
                    }

                    // Display the options to the player
                    for (int i = 0; i < 5; ++i) {
                        cout << options[i] << " ";
                    }
                    cout << endl;
                } else {
                    cout << "Guess a number between 1 and " << maxRange << ": ";
                }

                cin >> guess; // Read player's guess
                pTries++; // Increment attempt count

                if (guess == ranNum) { // Player guessed correctly
                    displaySparkles(); // Display winning message
                    cout << "Congratulations! You guessed the number in " << pTries << " tries!" << endl;
                    win = true;
                    wins++; // Increment win count
                    result = "Win: Guessed the number " + to_string(ranNum) + " in " + to_string(pTries) + " tries.";
                } else if (pTries == attempts) { // Player used all attempts without guessing correctly
                    displaySadFace(); // Display losing message
                    cout << "Sorry, the correct number was " << ranNum << ". Better luck next time!" << endl;
                    losses++; // Increment loss count
                    result = "Loss: Did not guess the number " + to_string(ranNum) + " in " + to_string(attempts) + " tries.";
                    break; // Exit the loop as game is over
                } else if (guess < ranNum) { // Player's guess is too low
                    cout << "Too low! ";
                } else { // Player's guess is too high
                    cout << "Too high! ";
                }

                // Provide a hint if not the last attempt
                if (!win && pTries < attempts - 1) {
                    int range = maxRange / 10;
                    if (abs(guess - ranNum) <= range) {
                        cout << "You're very close!" << endl;
                    } else if (abs(guess - ranNum) <= range * 2) {
                        cout << "You're close!" << endl;
                    } else {
                        cout << "Not close." << endl;
                    }
                }
            }

            // Record the result of the game
            gamesPlayed++; // Increment total games played
            if (lastRounds.size() == 3) { // Maintain only last 3 rounds' results
                lastRounds.erase(lastRounds.begin());
            }
            lastRounds.push_back(result); // Add current game's result to the list

        } else if (choice == '2') { // Display last 3 rounds' results
            displayLastRounds(lastRounds);
        } else if (choice == '3') { // Display player statistics
            displayStats(gamesPlayed, wins, losses);
        } else if (choice == '4') { // Exit the game
            break; // Break out of the main loop
        } else { // Handle invalid input
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0; // Exit the program
}
3

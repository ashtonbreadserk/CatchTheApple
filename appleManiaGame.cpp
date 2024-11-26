#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

// Global variables
bool gameOver;
const int width = 40;
const int height = 20;
int x;            // bucket's position (x-axis)
int fruitX, fruitY;   // Position of the fruit
int score;        // Player's score
int fruitCount = 0; // Counter for dropped fruits

enum eDirecton { STOP = 0, LEFT, RIGHT }; // bucket's Directions
eDirecton dir;    // Current direction of the bucket

// Setup game variables
void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2; // Start at the middle of the board
    fruitX = rand() % width; // Randomly position the fruit
    fruitY = 0; // Start fruit at the top of the screen
    score = 0;
    fruitCount = 0;
}

// Draw the game board
void Draw() {
    system("cls"); // Clear console

    // Top border
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    // Board contents
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width + 2; j++) {
            if (j == x && i == height - 1) { // bucket
                cout << "|__|";
            }
            else if (i == fruitY && j == fruitX) // Fruit
                cout << "O";
            else {
                cout << " ";
            }
        }
        cout << endl;
    }

    // Bottom border
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    // Display the score
    cout << "Score: " << score << endl;
}

// Process player input
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a': // Move left
            dir = LEFT;
            break;
        case 'd': // Move right
            dir = RIGHT;
            break;
        case 'q': // Quit the game
            gameOver = true;
            break;
        }
    }
}

// Update game logic
void Logic() {
    // Move the bucket
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    default:
        break;
    }

    // Implement wall wrapping
    if (x >= width) x = 0;
    else if (x < 0) x = width - 1;

    // Update fruit position
    fruitY++;

    // Check if the fruit reaches the bottom
    if (fruitY >= height) {
        fruitY = 0; // Reset the fruit's position to top
        fruitX = rand() % width; // Randomly generate a new fruit position
        fruitCount++;

        if (fruitCount >= 3) { // If three fruits are missed
            gameOver = true; // End the game
        }
    }

    // Check if the bucket catches the fruit
    if (x == fruitX && height - 1 == fruitY) {
        score += 10; // Increase score
        fruitY = 0; // Reset fruit position
        fruitX = rand() % width; // Randomly generate new fruit position
        fruitCount = 0; // Reset missed fruit count
    }
}

// Display the menu
void DisplayMenu() {
    int choice;

    cout << R"(
 ________   ______   ______   __       ______       ___ __ __   ________   ___   __     ________  ________      
/_______/\ /_____/\ /_____/\ /_/\     /_____/\     /__//_//_/\ /_______/\ /__/\ /__/\  /_______/\/_______/\     
\::: _  \ \\:::_ \ \\:::_ \ \\:\ \    \::::_\/_    \::\| \| \ \\::: _  \ \\::\_\\  \ \ \__.::._\/\::: _  \ \    
 \::(_)  \ \\:(_) \ \\:(_) \ \\:\ \    \:\/___/\    \:.      \ \\::(_)  \ \\:. `-\  \ \   \::\ \  \::(_)  \ \   
  \:: __  \ \\: ___\/ \: ___\/ \:\ \____\::___\/_    \:.\-/\  \ \\:: __  \ \\:. _    \ \  _\::\ \__\:: __  \ \  
   \:.\ \  \ \\ \ \    \ \ \    \:\/___/\\:\____/\    \. \  \  \ \\:.\ \  \ \\. \`-\  \ \/__\::\__/\\:.\ \  \ \ 
    \__\/\__\/ \_\/     \_\/     \_____\/ \_____\/     \__\/ \__\/ \__\/\__\/ \__\/ \__\/\________\/ \__\/\__\/     
                                       )        (   (         *       ) (          
                                      ( /(  (     )\ ))\ )    (  `   ( /( )\ )       
                                       )\()) )\   (()/(()/(    )\))(  )\()|()/(  (    
                                      ((_)((((_)(  /(_))(_))  ((_)()\((_)\ /(_)) )\   
                                       _((_)\ _ )\(_))(_))_   (_()((_) ((_|_))_ ((_)  
                                      | || (_)_\(_) _ \|   \  |  \/  |/ _ \|   \| __| 
                                      | __ |/ _ \ |   /| |) | | |\/| | (_) | |) | _|  
                                      |_||_/_/ \_\|_|_\|___/  |_|  |_|\___/|___/|___| 
                                                                                                                                                           
)" << '\n';
    while (true) {
        cout << "+----------------------------------+" << endl;
        cout << "|           Apple Mania            |" << endl;
        cout << "|----------------------------------|" << endl;
        cout << "|                                  |" << endl;
        cout << "| 1 | Start Game                   |" << endl;
        cout << "| 2 | Instructions                 |" << endl;
        cout << "| 3 | Exit                         |" << endl;
        cout << "|                                  |" << endl;
        cout << "+----------------------------------+" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            Setup();
            break;
        }
        else if (choice == 2) {
            cout << "Instructions: Use 'a' to move left and 'd' to move right to catch the fruit." << endl;
            cout << "If you miss 5 fruits, the game ends." << endl;
            system("pause");
        }
        else if (choice == 5) {
            exit(0);
        }
    }
}

// Main game loop
int main() {
    DisplayMenu(); // Show the menu

    while (!gameOver) {
        Draw();   // Render game
        Input();  // Handle input
        Logic();  // Update logic
        Sleep(50); // Control speed
    }

    cout << "Game Over! Final Score: " << score << endl;
    return 0;
}

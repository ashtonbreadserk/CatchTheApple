#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>
#include <algorithm>

using namespace std;

// Global variables
bool gameOver;
const int width = 40;
const int height = 20;
int x;                  // Basket position
int fruitX, fruitY;     // Fruit position
int score;              // Current score
int fruitCount = 0;     // Missed fruits
int basketSpeed = 1;    // Basket speed multiplier
int sensitivity = 1;    // Basket sensitivity
string currentUser = ""; // Logged-in user
vector<pair<string, int>> leaderboard; // Leaderboard

enum eDirecton { STOP = 0, LEFT, RIGHT };
eDirecton dir;

// Setup game variables
void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2; // Start at the middle of the board
    fruitX = rand() % width;
    fruitY = 0;
    score = 0;
    fruitCount = 0;
}

// Save leaderboard to file
void SaveLeaderboard() {
    ofstream file("leaderboard.txt");
    for (const auto& entry : leaderboard) {
        file << entry.first << " " << entry.second << endl;
    }
    file.close();
}

// Load leaderboard from file
void LoadLeaderboard() {
    leaderboard.clear();
    ifstream file("leaderboard.txt");
    string name;
    int score;
    while (file >> name >> score) {
        leaderboard.emplace_back(name, score);
    }
    file.close();
}

// Display leaderboard
void DisplayLeaderboard() {
    cout << "Leaderboard:" << endl;
    cout << "+------------------+---------+" << endl;
    cout << "| Player           | Score   |" << endl;
    cout << "+------------------+---------+" << endl;
    for (const auto& entry : leaderboard) {
        cout << "| " << entry.first << string(17 - entry.first.length(), ' ') << "| " << entry.second << "     |" << endl;
    }
    cout << "+------------------+---------+" << endl;
    system("pause");
}

// Update leaderboard
void UpdateLeaderboard() {
    leaderboard.emplace_back(currentUser, score);
    sort(leaderboard.begin(), leaderboard.end(), [](const auto& a, const auto& b) {
        return b.second < a.second;
        });
    if (leaderboard.size() > 10) leaderboard.pop_back();
    SaveLeaderboard();
}

// Draw the game board
void Draw() {
    system("cls");

    for (int i = 0; i < width + 2; i++) cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width + 2; j++) {
            if (j == x && i == height - 1) cout << "|___|";
            else if (i == fruitY && j == fruitX) cout << "O";
            else cout << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++) cout << "-";
    cout << endl;

    cout << "Player: " << currentUser << " | Score: " << score << " | Missed: " << fruitCount << endl;
}

// Process input
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'q':
            gameOver = true;
            break;
        }
    }
}

// Update game logic
void Logic() {
    switch (dir) {
    case LEFT:
        x -= basketSpeed * sensitivity;
        break;
    case RIGHT:
        x += basketSpeed * sensitivity;
        break;
    default:
        break;
    }

    if (x >= width) x = 0;
    else if (x < 0) x = width - 1;

    fruitY++;

    if (fruitY >= height) {
        fruitY = 0;
        fruitX = rand() % width;
        fruitCount++;
        if (fruitCount == 3) {
            gameOver = true;
        }
    }

    if (x == fruitX && height - 1 == fruitY) {
        score += 10;
        fruitY = 0;
        fruitX = rand() % width;
        fruitCount = 0;
    }
}

// Handle user login
void Login() {
    cout << "Enter your name: ";
    cin >> currentUser;
    cout << "Welcome, " << currentUser << "!" << endl;
}

// Display menu
void DisplayMenu() {
    int choice;

    while (true) {
        cout << "+----------------------------------+" << endl;
        cout << "|           Apple Mania            |" << endl;
        cout << "+----------------------------------+" << endl;
        cout << "| 1 | Start Game                   |" << endl;
        cout << "| 2 | View Leaderboard             |" << endl;
        cout << "| 3 | Set Basket Speed             |" << endl;
        cout << "| 4 | Set Sensitivity              |" << endl;
        cout << "| 5 | Instructions                 |" << endl;
        cout << "| 6 | Exit                         |" << endl;
        cout << "+----------------------------------+" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            Setup();
            break;
        }
        else if (choice == 2) {
            DisplayLeaderboard();
        }
        else if (choice == 3) {
            cout << "Enter basket speed (1-5): ";
            cin >> basketSpeed;
        }
        else if (choice == 4) {
            cout << "Enter sensitivity (1-5): ";
            cin >> sensitivity;
        }
        else if (choice == 5) {
            cout << 
        }
        else if (choice == 6) {
            exit(0);
        }
        else {
            cout << "Invalid choice. Try again." << endl;
        }
    }
}

// Main function
int main() {
    LoadLeaderboard();
    Login();

    while (true) {
        DisplayMenu();
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            Sleep(70);
        }
        UpdateLeaderboard();
        cout << "Game Over! Final Score: " << score << endl;
        char returnToMenu;
        cout << "Do you want to return to the menu? (y/n): ";
        cin >> returnToMenu;
        if (returnToMenu != 'y' && returnToMenu != 'Y') {
            cout << "Thank you for playing!" << endl;
            break;
        }
    }
    return 0;
}

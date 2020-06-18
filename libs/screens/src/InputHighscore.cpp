#pragma warning(disable: 4244)
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include "InputHighscore.h"

using namespace std;


bool CheckScore::checkScore(int score) {
    bool flag = false;
    Score scores[10];

    ifstream inFile("ScoresData.txt");
    if (!inFile) {
        cerr << "Unable to open input file ScoresData.txt" << endl;
        exit(-1);
    }
    string line;
    int numScores = 0;
    while (getline(inFile, line)) {
        if (line == "") {
            break;
        }
        CheckScore::insertScore(scores, line, numScores);
        numScores++;
    }
    CheckScore::sort(scores, numScores);

    if (score > scores[numScores - 1].getScore() || numScores < 10) {
        flag = true;
    }
    inFile.close();
    return flag;
}


void CheckScore::insertScore(Score* scores, string line, int numScores) {
    const char* lineTemp = line.c_str();
    Score temp(lineTemp);
    scores[numScores] = temp;
}


void CheckScore::writeScoresToFile(Score* scores, unsigned numScores) {
    ofstream outFile("ScoresData.txt", ios::trunc);
    if (!outFile) {
        cerr << "Unable to open output file ScoresData.txt" << endl;
        exit(-1);
    }
    for (unsigned int i = 0; i < numScores; i++) {
        outFile << scores[i];
        if (i != numScores - 1) {
            outFile << endl;
        }
    }

    outFile.close();
}


void CheckScore::inputNewScore(int score, std::string name) {
    Score scores[10];
    ifstream inFile("ScoresData.txt");
    if (!inFile) {
        cerr << "Unable to open input file ScoresData.txt" << endl;
        exit(-1);
    }

    string line;
    int numScores = 0;
    while (getline(inFile, line)) {
        if (line == "") {
            break;
        }
        CheckScore::insertScore(scores, line, numScores);
        numScores++;
    }
    inFile.close();
    CheckScore::sort(scores, numScores);

    Score newScore;
    const char* nameCstr = name.c_str();
    newScore.setName(nameCstr);
    newScore.setScore(score);
    newScore.setDate();
    if (numScores == 10) {
        scores[numScores - 1] = newScore;
    }
    else if (numScores < 10) {
        scores[numScores] = newScore;
        numScores++;
    }

    CheckScore::sort(scores, numScores);
    CheckScore::writeScoresToFile(scores, numScores);
}


void CheckScore::sort(Score* scores, unsigned numScores) {
    std::sort(scores, scores + numScores);
    Score* tempScores = new Score[numScores];
    for (unsigned int i = 0; i < numScores; i++) {
        tempScores[numScores - 1 - i] = scores[i];
    }
    for (unsigned int i = 0; i < numScores; i++) {
        scores[i] = tempScores[i];
    }
    delete[] tempScores;
}





//SFML
InputHighscore::InputHighscore(float width, float height) {
    if (!font.loadFromFile("Samson_Bold_Oblique.ttf")) {
        //handle error
    }
    title.setFont(font);
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::Blue);
    title.setString("CONGRATULATIONS");
    title.setPosition(sf::Vector2f(width / 5.00, height / 5.50));

    title2.setFont(font);
    title2.setCharacterSize(40);
    title2.setFillColor(sf::Color::Blue);
    title2.setString("YOU HAVE ACHIEVED A TOP 10 HIGHSCORE");
    title2.setPosition(sf::Vector2f(width / 4.20, height / 3.10));

    back.setFont(font);
    back.setCharacterSize(45);
    back.setFillColor(sf::Color::White);
    back.setString("ENTER YOUR NAME: ");
    back.setPosition(sf::Vector2f(width / 4.80, height / 1.40));

    userInputPrint.setFont(font);
    userInputPrint.setCharacterSize(45);
    userInputPrint.setFillColor(sf::Color::White);
    userInputPrint.setPosition(sf::Vector2f(width / 2.00, height / 1.40));

    scoreWord.setFont(font);
    scoreWord.setCharacterSize(75);
    scoreWord.setFillColor(sf::Color::White);
    scoreWord.setString("SCORE: ");
    scoreWord.setPosition(sf::Vector2f(width / 3.50, height / 2.4));

    scorePrint.setFont(font);
    scorePrint.setCharacterSize(125);
    scorePrint.setFillColor(sf::Color::Yellow);
    scorePrint.setPosition(sf::Vector2f(width / 2.15, height / 2.72));

    instruction.setFont(font);
    instruction.setCharacterSize(35);
    instruction.setFillColor(sf::Color::Red);
    instruction.setString("PRESS ENTER WHEN FINISHED");
    instruction.setPosition(sf::Vector2f(width / 3.25, height / 1.2));
}

InputHighscore::~InputHighscore() {}

// InputHighScore object? why
void InputHighscore::work(sf::RenderWindow& window, InputHighscore& inputHighscore, sf::Sprite& s, sf::Sound& sound, int score) {
    //char* tempScore = new char;
    string tempScore = std::to_string(score);
    bool noName = false;
    scorePrint.setString(tempScore);
    userInput.clear();
    userInputPrint.setString(userInput);
    bool inInputHighscore = true;
    sf::Event event;
    window.clear();
    window.draw(s);
    inputHighscore.draw(window);
    while (inInputHighscore) {
        // prevent drawing to much CPU time  
        sf::sleep(sf::milliseconds(10));
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Enter) { 
                    if (userInput.getSize() == 0) {
                        noName = true;
                    }
                    inInputHighscore = false;
                }
                break;
            case sf::Event::TextEntered:
                if (event.key.code == 13) { // 13  = return/enter
                    break;
                }
                if (event.key.code == 8) { // 8 = backspace
                    if (userInput.getSize() > 0) {
                        userInput.erase(userInput.getSize() - 1);
                        userInputPrint.setString(userInput);
                    }
                }
                else {
                    if (userInput.getSize() < 14) {
                        userInput.insert(userInput.getSize(), event.text.unicode);
                        userInputPrint.setString(userInput);
                    }
                }
                break;
            case sf::Event::Closed:
                userInput = "-NO NAME-";
                CheckScore::inputNewScore(score, userInput);
                window.close();
                exit(0);
            }
            window.draw(s);
            inputHighscore.draw(window);
            break;
        }
    }
    if (noName == true) {
        userInput = "-NO NAME-";
    }
    CheckScore::inputNewScore(score, userInput);
}

void InputHighscore::draw(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(title2);
    window.draw(back);
    window.draw(instruction);
    window.draw(userInputPrint);
    window.draw(scoreWord);
    window.draw(scorePrint);
    window.display();
}
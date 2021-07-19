//C++ Project - dotdm26
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

#include "QuestionAndQuiz.h"

#define FILENAME "questions.txt"

int main() {
    Quiz q;
    int total = 0, user;
    std::vector<Question> questions;
    std::ifstream data(FILENAME);
    std::cout << "====== C++ PROJECT: QUIZ GAME - MINH DO (1911396), ICT19-SI2 ======\n" << std::endl;

    do 
    {
        std::cout << "====================" << std::endl;
        std::cout << "1. Take the quiz\n2. List of questions\n3. Read from file\n4. Save to file\n5. Add new question\n6. Initialize\n7. Exit program" << std::endl;
        std::cout << "\nPlease select an option: ";
        std::cin >> user;
        switch (user) 
        {
        case 1: //take the quiz
            q.Game(questions);
            break;
        case 2: //print list of questions
            q.PrintQuestions(questions);
            break;
        case 3: //read from file
            if (data.is_open()) 
            {
                std::cout << "\nData file found." << std::endl;
                q.Load(data, questions);
                std::cout << "Loaded file. (Note: The file may be empty. In this case, please add questions via option (5).)\n" << std::endl;
            }
            else 
            {
                std::cout << "Error! " << FILENAME << " not found." << std::endl;
            }
            break;
        case 4:
            q.SaveToFile(FILENAME, questions);
            break;
        case 5:
            q.AddQuestion(questions);
            break;
        case 6:
            questions.clear();
            q.Initialize(questions);
            break;
        case 7:
            std::cout << "Exiting program. Thank you for playing!" << std::endl;
            break;
        default:
            //prevent infinite loop if user inputted string or etc. by accident
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nPlease select a valid option!\n" << std::endl;
            break;
        }
    } while (user != 7);
    return 0;
}
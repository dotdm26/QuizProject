#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

#include "QuestionAndQuiz.h"

//Allows the user to type the question but not add the question into the question vector
//Used in AddQuestion()
void Question::WriteQuestion()
{
    std::cin.get();
    std::cout << "Enter the question: " << std::endl;
    std::getline(std::cin, question_text);
    std::cout << "Enter answer 1: " << std::endl;
    std::getline(std::cin, answer_1);
    std::cout << "Enter answer 2: " << std::endl;
    std::getline(std::cin, answer_2);
    std::cout << "Enter answer 3: " << std::endl;
    std::getline(std::cin, answer_3);
    std::cout << "Enter answer 4: " << std::endl;
    std::getline(std::cin, answer_4);
    std::cout << "\nYou have written the following question and its answers:" << std::endl;
    std::cout << question_text << std::endl;
    std::cout << "1- " << answer_1 << std::endl << "2- " << answer_2 << std::endl << "3- " << answer_3 << std::endl << "4- " << answer_4 << std::endl;
    do {
        std::cout << "Enter the number of the correct answer (1 - 4):" << std::endl;
        std::cin >> correct_answer;
        if (correct_answer < 1 || correct_answer > 4) {
            //prevent infinite loop if user inputted string or etc. by accident
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter a valid number!" << std::endl;
        }
    } while (correct_answer < 1 || correct_answer > 4);
}

//Used in Game()
int Question::AskQuestion(int num)
{
    int score = 0, guess;
    std::cout << "\n";
    if (num >= 0) { //Print numbered question (q1, q2, q3, ...)
        std::cout << num + 1 << ") ";
    }
    AnswerPicker();
    std::cout << question_text << "\n";
    std::cout << "1. " << alt_1 << "\n";
    std::cout << "2. " << alt_2 << "\n";
    std::cout << "3. " << alt_3 << "\n";

    do { //Gets user's answer
        std::cout << "What's your answer? ";
        std::cin >> guess;
        if (guess < 1 || guess > 3) {
            //prevent infinite loop if user inputted string or etc. by accident
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid answer! (1 - 3)" << std::endl;
        }
    } while (guess < 1 || guess > 3);

    if (guess == correct_alt) {
        std::cout << "\nCorrect answer! +1 point. " << std::endl;
        score = 1;
        std::cin.get();
    }
    else {
        std::cout << "\nWrong answer. No points awarded. " << std::endl;
        std::cin.get();
    }
    return score;
}

//Used in Game()
//Takes 1 correct answer and 2 wrong answer to the quiz game
void Question::AnswerPicker()
{
    srand(NULL);
    int exclude;
    do {
        exclude = rand() % 4 + 1;
    } while (exclude == correct_answer);

    if (exclude == 1) {
        alt_1.append(answer_2);
        alt_2.append(answer_3);
        alt_3.append(answer_4);
    }
    if (exclude == 2) {
        alt_1.append(answer_1);
        alt_2.append(answer_3);
        alt_3.append(answer_4);
    }
    if (exclude == 3) {
        alt_1.append(answer_1);
        alt_2.append(answer_2);
        alt_3.append(answer_4);
    }
    if (exclude == 4) {
        alt_1.append(answer_1);
        alt_2.append(answer_2);
        alt_3.append(answer_3);
    }
    if (correct_answer == 4) {
        correct_alt = 3;
    }
    else {
        correct_alt = correct_answer;
    }
}

std::istream& operator>> (std::istream& is, Question& question)
{
    std::string line;
    while (std::getline(is, line))
    {
        if (line.size() == 0)
            continue;
        break;
    }
    question.question_text = line;
    std::getline(is, question.answer_1);
    std::getline(is, question.answer_2);
    std::getline(is, question.answer_3);
    std::getline(is, question.answer_4);
    is >> question.correct_answer;
    return is;
}

std::ostream& operator<<(std::ostream& out, Question& question)
{
    out << question.question_text;
    out << std::endl;
    out << question.answer_1;
    out << std::endl;
    out << question.answer_2;
    out << std::endl;
    out << question.answer_3;
    out << std::endl;
    out << question.answer_4;
    out << std::endl;
    out << question.correct_answer;
    out << std::endl;
    return out;
}

/*Below are functions of the Quiz class. 
I have not been able to figure out how to put the Quiz header & functions in a separate file,
because the Quiz functions require a Question object as its parameter.*/

void Quiz::Initialize(std::vector<Question>& questions)
{
    //clear questions from the vector
    questions.clear();
    //clears data file
    std::ofstream ini(FILENAME);
    ini.open(FILENAME, std::ofstream::out | std::ofstream::trunc);
    ini.close();
    std::cout << "\nData has been cleared.\n" << std::endl;
}

//adds the inputted Question object into the container
void Quiz::AddQuestion(std::vector<Question>& questions)
{
    Question q;
    q.WriteQuestion();
    questions.push_back(q);
    std::cout << "\nNew question has been added into the program.\n" << std::endl;
}

void Quiz::SaveToFile(std::string filename, std::vector<Question>& questions)
{
    std::ofstream output;
    output.open(filename, std::ios::out);
    for (int i = 0; i < questions.size(); i++) {
        output << questions[i];
    }
    output.close();
    std::cout << "\nSaved the questions from the console log into the data file.\n" << std::endl;
}

//load file content into object vector
void Quiz::Load(std::istream& is, std::vector<Question>& questions)
{
    Question q;
    while (is >> q) {
        questions.push_back(q);
    }
}

void Quiz::PrintQuestions(std::vector<Question> questions)
{
    int i = 1;
    if (questions.empty()) {
        std::cout << "\nThere are no questions in the program!\n" << std::endl;
    }
    else {
        std::cout << "There are " << questions.size() << " questions." << std::endl;
        std::cout << "\nList of questions: \n" << std::endl;
        for_each(questions.begin(), questions.end(), [&i](Question q) {
            std::cout << i << ") " << q.getQuestion() << std::endl;
            i++;
            });
        std::cout << "\n";
    }
}

//Used in Game()
void Quiz::ShuffleQuestions(std::vector<Question>& questions) //Shuffle the questions. 
{
    std::random_device rd;
    std::mt19937 randomGenerator(rd());
    std::shuffle(questions.begin(), questions.end(), randomGenerator);
}

//Starts the quiz game
void Quiz::Game(std::vector<Question>& questions)
{
    int total = 0;
    if (questions.size() < 5) {
        std::cout << "\nThe quiz cannot be taken because there are not enough questions in order to play the quiz." << std::endl;
        std::cout << "Please load the questions from the data file (3) or add more into the program (5).\n" << std::endl;
    }
    else {
        ShuffleQuestions(questions);
        std::cout << "\nThe quiz is going to start. Good luck! :)" << std::endl;
        for (int i = 0; i < 5; ++i) {
            total += questions[i].AskQuestion(i);
        }
        std::cout << "\nYou scored " << total << " out of 5 for the quiz.\n" << std::endl;
    }
}

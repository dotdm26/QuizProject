#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

#define FILENAME "questions.txt"

/*
NOTE: The functions of the Quiz class require Question objects.
I haven't been able to put the contents of the Quiz class into a separate Quiz.h and Quiz.cpp file.
*/

class Question
{
    friend std::istream& operator>> (std::istream& is, Question& question);
    friend std::ostream& operator<<(std::ostream& out, Question& question);
public:
    Question() { question_text = ""; answer_1 = ""; answer_1 = ""; answer_1 = ""; answer_1 = ""; correct_answer = 0; }
    ~Question() = default;
    void WriteQuestion();
    int AskQuestion(int num = 0); //num is the order of the question (q1, q2, q3, ...)
    void AnswerPicker();
    std::string getQuestion() { return question_text; }
private:
    std::string question_text;
    std::string answer_1;
    std::string answer_2;
    std::string answer_3;
    std::string answer_4;
    int correct_answer;
    //Below are the elements used to display question & 3 answers in the quiz game
    std::string alt_1;
    std::string alt_2;
    std::string alt_3;
    int correct_alt;
};

class Quiz
{
public:
    void Initialize(std::vector<Question>& questions);
    void AddQuestion(std::vector<Question>& questions);
    void SaveToFile(std::string filename, std::vector<Question>& questions);
    void Load(std::istream& is, std::vector<Question>& questions);
    void PrintQuestions(std::vector<Question> questions);
    void ShuffleQuestions(std::vector<Question>& questions);
    void Game(std::vector<Question>& questions);
};
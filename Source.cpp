//C++ Project - dotdm26
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

#define FILENAME "questions.txt"

using namespace std;

/*
References taken from https://codereview.stackexchange.com/questions/148866/c-quiz-game-w-questions-in-random-order
*/

class Question {
    friend istream& operator>> (istream& is, Question& question);
    friend ostream& operator<<(ostream& out, Question& question);
public:
    Question() { question_text = ""; answer_1 = ""; answer_1 = ""; answer_1 = ""; answer_1 = ""; correct_answer = 0; }
    ~Question() = default;
    void WriteQuestion();
    int AskQuestion(int num = 0); //num is the order of the question (q1, q2, q3, ...)
    void AnswerPicker();
    string getQuestion() { return question_text; }
    string alt_1;
    string alt_2;
    string alt_3;
    int correct_alt;
private:
    string question_text;
    string answer_1;
    string answer_2;
    string answer_3;
    string answer_4;
    int correct_answer;
};

void Initialize(vector<Question>& questions);
void AddQuestion(vector<Question>& questions);
void SaveToFile(string filename, vector<Question>& questions);
void Load(istream& is, vector<Question>& questions);
void PrintQuestions(vector<Question> questions);
void ShuffleQuestions(vector<Question>& questions);
void Game(vector<Question>& questions); 

int main() {
    int total = 0, user;
    vector<Question> questions;
    ifstream data(FILENAME);
    cout << "====== C++ PROJECT: QUIZ GAME - MINH DO (1911396), ICT19-SI2 ======\n" << endl;

    do {
        cout << "1. Take the quiz\n2. List of questions\n3. Read from file\n4. Save to file\n5. Add new question\n6. Initialize\n7. Exit program" << endl;
        cout << "\nPlease select an option: ";
        cin >> user;
        switch (user) {
        case 1: //take the quiz
            Game(questions);
            break;
        case 2: //print list of questions
            PrintQuestions(questions);
            break;
        case 3: //read from file
            if (data.is_open()) {
                cout << "\nData file found. Now loading the file..." << endl;
                Load(data, questions);
                cout << "File has been loaded.\n" << endl;
            }
            else {
                cout << "Error: File not found!\n";
            }
            break;
        case 4: //save to file
            SaveToFile(FILENAME, questions);
            break;
        case 5: //add new question
            AddQuestion(questions);
            break;
        case 6: //initialize
            questions.clear();
            Initialize(questions);
            break;
        case 7:
            cout << "Exiting program. Thank you for playing!" << endl;
            break;
        default:
            //prevent infinite loop if user inputted string or etc. by accident
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nPlease select a valid option!\n" << endl;
            break;
        }
    } while (user != 7);
    return 0;
}

void Initialize(vector<Question>& questions) {
    //clear questions from the vector
    questions.clear();
    //clears data file
    ofstream ini(FILENAME);
    ini.open(FILENAME, ofstream::out | ofstream::trunc);
    ini.close();
    cout << "\nData has been cleared.\n" << endl;
}

//adds the inputted Question object into the container
void AddQuestion(vector<Question>& questions) {
    Question q;
    q.WriteQuestion();
    questions.push_back(q);
    cout << "\nNew question has been added into the program.\n" << endl;
}

void SaveToFile(string filename, vector<Question>& questions) {
    ofstream output;
    output.open(filename, ios::out);
    for (int i = 0; i < questions.size(); i++) {
        output << questions[i];
    }
    output.close();
    cout << "\nSaved questions from the program in the data file.\n" << endl;
}

//load file content into object vector
void Load(istream& is, vector<Question>& questions) {
    Question q;
    while (is >> q) {
        questions.push_back(q);
    }
}

void PrintQuestions(vector<Question> questions) {
    int i = 1;
    if (questions.empty()) {
        cout << "\nThere are no questions in the program!\n" << endl;
    }
    else {
        cout << "There are " << questions.size() << " questions." << endl;
        cout << "\nList of questions: \n" << endl;
        for_each(questions.begin(), questions.end(), [&i](Question q) {
            cout << i << ") " << q.getQuestion() << endl;
            i++;
            });
        cout << "\n";
    }
}

//Used in Game()
void ShuffleQuestions(vector<Question>& questions) //Shuffle the questions. 
{
    std::random_device rd;
    std::mt19937 randomGenerator(rd());
    std::shuffle(questions.begin(), questions.end(), randomGenerator);
}

//Starts the quiz game
void Game(vector<Question>& questions) {
    int total = 0;
    if (questions.size() < 5) {
        cout << "\nThe quiz cannot be taken because there are not enough questions in order to play the quiz." << endl;
        cout << "Please load the questions from the data file (3) or add more into the program (5).\n" << endl;
    }
    else {
        ShuffleQuestions(questions);
        cout << "\nThe quiz is going to start. Good luck! :)" << endl;
        for (int i = 0; i < 5; ++i) {
            total += questions[i].AskQuestion(i);
        }
        cout << "\nYou scored " << total << " out of 5 in the quiz.\n" << endl;
    }
}

//Allows the user to type the question but not add the question into the question vector
//Used in AddQuestion()
void Question::WriteQuestion() {
    cin.get();
    cout << "Enter the question: " << endl;
    getline(cin, question_text);
    cout << "Enter answer 1: " << endl;
    getline(cin, answer_1);
    cout << "Enter answer 2: " << endl;
    getline(cin, answer_2);
    cout << "Enter answer 3: " << endl;
    getline(cin, answer_3);
    cout << "Enter answer 4: " << endl;
    getline(cin, answer_4);
    cout << "\nYou have written the following question and its answers:" << endl;
    cout << question_text << endl;
    cout << "1- " << answer_1 << endl << "2- " << answer_2 << endl << "3- " << answer_3 << endl << "4- " << answer_4 << endl;
    do {
        cout << "Enter the number of the correct answer (1 - 4):" << endl;
        cin >> correct_answer;
        if (correct_answer < 1 || correct_answer > 4) {
            //prevent infinite loop if user inputted string or etc. by accident
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter a valid number!" << endl;
        }
    } while (correct_answer < 1 || correct_answer > 4);
}

//Used in Game()
int Question::AskQuestion(int num) {
    int score = 0, guess;
    cout << "\n";
    if (num >= 0) { //Print numbered question (q1, q2, q3, ...)
        cout << num + 1 << ") ";
    }
    AnswerPicker();
    cout << question_text << "\n";
    cout << "1. " << alt_1 << "\n";
    cout << "2. " << alt_2 << "\n";
    cout << "3. " << alt_3 << "\n";

    do { //Gets user's answer
        cout << "What's your answer? ";
        cin >> guess;
        if (guess < 1 || guess > 3) {
            //prevent infinite loop if user inputted string or etc. by accident
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid answer! (1 - 3)" << endl;
        }
    } while (guess < 1 || guess > 3);

    if (guess == correct_alt) {
        cout << "\nCorrect answer! +1 point. " << endl;
        score = 1;
        cin.get();
    }
    else {
        cout << "\nWrong answer. No points awarded. " << endl;
        cin.get();
    }
    return score;
}

//Used in Game()
//Takes 1 correct answer and 2 wrong answer to the quiz game
void Question::AnswerPicker() {
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

istream& operator>> (istream& is, Question& question) {
    string line;
    while (getline(is, line))
    {
        if (line.size() == 0)
            continue;
        break;
    }
    question.question_text = line;
    getline(is, question.answer_1);
    getline(is, question.answer_2);
    getline(is, question.answer_3);
    getline(is, question.answer_4);
    is >> question.correct_answer;
    return is;
}

ostream& operator<<(ostream& out, Question& question) {
    out << question.question_text;
    out << endl;
    out << question.answer_1;
    out << endl;
    out << question.answer_2;
    out << endl;
    out << question.answer_3;
    out << endl;
    out << question.answer_4;
    out << endl;
    out << question.correct_answer;
    out << endl;
    return out;
}
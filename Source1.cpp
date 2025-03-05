#include <iostream>
#include <cstdlib>
using namespace std;

//Enum & Struct
enum en_QuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum en_OperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

struct st_Question {

    int Number1 = 0;
    int Number2 = 0;
    en_OperationType OperationType;
    en_QuestionsLevel QuestionsLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};
struct st_Quizz
{
    st_Question QuestionList[100];
    short NumberOfQuestions;
    en_QuestionsLevel QuestionsLevel;
    en_OperationType OperationType;
    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswers = 0;
    bool isPass = false;
};

//Helpers functions
int RandomNumber(int From, int To)
{
    int RandNumber = rand() % (To - From + 1) + From;
    return RandNumber;
}
int SimpleCalculator(int Number1, int Number2, en_OperationType OpType) {

    switch (OpType)
    {
    case Add:
        return Number1 + Number2;
    case Sub:
        return Number1 - Number2;
    case Mult:
        return Number1 * Number2;
    case Div:
        return Number1 / Number2;
    default:
        return Number1 + Number2;
    }

}
string GetOperationTypeSymbol(en_OperationType OpType)
{
    switch (OpType)
    {
    case en_OperationType::Add:
        return "+";
    case en_OperationType::Sub:
        return "-";
    case en_OperationType::Mult:
        return "x";
    case en_OperationType::Div:
        return "/";
    default:
        return "Mix";
    }
}

//Inpout functions
short Read_HowManyQuestions() {

    short NumberOfQuestions = 1;

    do
    {
        cout << "How Many Questions do you want to answer?";
        cin >> NumberOfQuestions;

    } while (NumberOfQuestions < 1 || NumberOfQuestions > 10);

    return NumberOfQuestions;
}
en_QuestionsLevel Read_QuestionsLevel() {

    short QuestionLevel = 0;
    do
    {
        cout << "Enter Question Level: [1]Easy [2]Med [3]Hard [4]Mix ? ";
        cin >> QuestionLevel;

    } while (QuestionLevel < 1 || QuestionLevel > 4);

    return (en_QuestionsLevel)QuestionLevel;
}
en_OperationType Read_OperationType() {

    short OperationType = 0;
    do
    {
        cout << "Enter Operation Type: [1]Add [2]Sub [3]Mul [4]Div [5]Mix ? ";
        cin >> OperationType;

    } while (OperationType < 1 || OperationType > 5);

    return (en_OperationType)OperationType;
}
float Read_QuestionAnswer() {

    float Answer = 0;
    cin >> Answer;

    return Answer;
}

//Display functions
void ResetScreen() {
    // Resets the screen by clearing it and restoring the default color.
    system("cls");
    system("color 0F");//Black
}
void PrintTheQuestion(st_Quizz& Quizz, short QuestionNumber) {

    cout << "\n";
    cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
    cout << GetOperationTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
    cout << "\n___________" << endl;
}
string GitFinalResultsText(bool Pass) {

    if (Pass)
        return "Pass :-)";
    else
        return "Fail :-(";

}
string GetQuestionLevelText(en_QuestionsLevel QuestionsLevel) {

    string arrQuestionLevelText[4] = { "Easy","Med","Hard","Mix" };
    return arrQuestionLevelText[QuestionsLevel - 1];
}
string GetOpTypeSymbol(en_OperationType OpType) {

    switch (OpType)
    {
    case Add:
        return "+";
    case Sub:
        return "-";
    case Mult:
        return "*";
    case Div:
        return "/";
    default:
        return "Mix";
    }

}
void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F"); //turn screen to Green
    else
    {
        system("color 4F"); //turn screen to Red
        cout << "\a";
    }
}
void PrintQuizzResults(st_Quizz Quizz) {

    cout << "\n-------------------\n\n";
    cout << "Final Results is " << GitFinalResultsText(Quizz.isPass) << endl;
    cout << "-------------------\n\n";

    cout << "Number of Question:" << Quizz.NumberOfQuestions << endl;
    cout << "Questions Level   :" << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
    cout << "OpType            :" << GetOpTypeSymbol(Quizz.OperationType) << endl;
    cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
    cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
    cout << "-------------------\n";

}

//logic functions
en_OperationType GetRandomOperationType() {

    int Op = RandomNumber(1, 4);
    return (en_OperationType)Op;
}
st_Question GeneratQuestion(en_QuestionsLevel QuestionsLevel, en_OperationType OperationType) {
    st_Question Question;

    if (QuestionsLevel == en_QuestionsLevel::Mix)
    {
        QuestionsLevel = (en_QuestionsLevel)RandomNumber(1, 3);
    }

    if (OperationType == en_OperationType::MixOp)
    {
        OperationType = GetRandomOperationType();
    }

    Question.OperationType = OperationType;


    switch (QuestionsLevel)
    {
    case en_QuestionsLevel::EasyLevel:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OperationType);
        Question.QuestionsLevel = QuestionsLevel;
        return Question;

    case en_QuestionsLevel::MedLevel:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OperationType);
        Question.QuestionsLevel = QuestionsLevel;
        return Question;

    case en_QuestionsLevel::HardLevel:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OperationType);
        Question.QuestionsLevel = QuestionsLevel;
        return Question;
    }
    return Question;
}
void Generate_Quizz_Questions(st_Quizz& Quizz) {

    for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
    {
        Quizz.QuestionList[Question] = GeneratQuestion(Quizz.QuestionsLevel, Quizz.OperationType);
    }
}
void CorrectTheQuestionAnswer(st_Quizz& Quizz, short QuestionNumber) {

    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;

        cout << "Worng Answer :-(\n";
        cout << "The right answer is: ";
        cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
        cout << "\n";
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswers++;

        cout << "Right Answer :-) \n";
    }

    cout << endl;

    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}
void AskAndCorrect_QuestionListAnswers(st_Quizz& Quizz) {

    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        PrintTheQuestion(Quizz, QuestionNumber);

        Quizz.QuestionList[QuestionNumber].PlayerAnswer = Read_QuestionAnswer();

        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
    }

    Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

//Main functions
void PlayMathGame() {

    st_Quizz Quizz;

    Quizz.NumberOfQuestions = Read_HowManyQuestions();
    Quizz.QuestionsLevel = Read_QuestionsLevel();
    Quizz.OperationType = Read_OperationType();

    Generate_Quizz_Questions(Quizz);
    AskAndCorrect_QuestionListAnswers(Quizz);
    PrintQuizzResults(Quizz);
}
void startGame() {

    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        PlayMathGame();

        cout << "\n\nDo you want play again (Y/N) ? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {
    srand((unsigned)time(NULL)); // Seed the random number generator

    startGame();

    return 0;
}
/**
 @file tic-tac-toe.cpp
*/

/*
 Tic-Tac-Toe
 Plays the game of tic-tac-toe against a human opponent
 인간 상대와 틱택토 게임을 합니다.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*전역 상수*/
/*global constants*/
const char X      = 'X';
const char O      = 'O';
const char EMPTY  = ' ';
const char TIE    = 'T';
const char NO_ONE = 'N';

/*함수 프로토타입*/
/*function prototypes*/
void instructions();
char askYesNo(string question);
int askNumber(string question, int high, int low = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(const vector<char>& board);
char winner(const vector<char>& board);
bool isLegal(const vector<char>& board, int move);
int humanMove(const vector<char>& board, char human);
int computerMove(vector<char> board, char computer);
void announceWinner(char winner, char computer, char human);

int main()
{
    /*보드의 이동할 위치 번호 변수*/
    int move;

    /*보드의 셀 갯수*/
    const int NUM_SQUARES = 9;

    /*보드*/
    vector<char> board(NUM_SQUARES, EMPTY);

    /*게임 지침 표시 함수*/
    instructions();

    /*플레이어의 피스를 정하는 함수*/
    char human = humanPiece();

    /*상대의 반대 피스를 반환하는 함수*/
    char computer = opponent(human);

    /*선수 'X'*/
    char turn = X;

    /*보드 표시 함수*/
    displayBoard(board);

    /*승자가 아무도 없는 경우 반복*/
    while (winner(board) == NO_ONE) {
        /*플레이어의 차례인 경우*/
        if (turn == human) {
            /*플레이어가 이동할 보드의 위치 번호를 선택하는 함수*/
            move = humanMove(board, human);

            /*보드의 해당 위치 셀에 인간의 피스 저장*/
            board[move] = human;
        }
        /*컴퓨터의 차례인 경우*/
        else {
            /*컴퓨터가 이동할 보드의 위치 번호를 선택하는 함수*/
            move = computerMove(board, computer);
            
            /*보드의 해당 위치 셀에 컴퓨터의 피스 저장*/
            board[move] = computer;
        }

        /*보드 표시 함수*/
        displayBoard(board);

        /*상대의 반대 피스를 반환하는 함수*/
        turn = opponent(turn);
    }

    /*승리 또는 동점 발표 함수*/
    announceWinner(winner(board), computer, human);

    return 0;
}

/**
 * @fn    void instructions()
 * @brief 게임 지침 표시 함수
 */
void instructions() {
    cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n";
    cout << "--where human brain is pit against silicon processor\n\n";
    cout << "Make your move know by entering a number, 0 - 8. The number\n";
    cout << "corresponds to the desired board position, as illustrated:\n\n";

    cout << " 0 | 1 | 2\n";
    cout << " ---------\n";
    cout << " 3 | 4 | 5\n";
    cout << " ---------\n";
    cout << " 6 | 7 | 8\n\n";

    cout << "Prepare yourself, human. The battle is about to begin.\n\n";
}

char askYesNo(string question) {
    char response;

    do
    {
        cout << question << " (y/n): ";

        cin >> response;
    } while (response != 'y' && response != 'n'); /*입력이 'y'가 아니고 'n'이 아닌 경우 반복*/

    return response;
}

int askNumber(string question, int high, int low) {
    int number;
    do
    {
        cout << question << " (" << low << " - " << high << "): ";

        cin >> number;
    } while (number > high || number < low); /*number가 high보다 크거나 number가 low보다 작은 경우 반복*/

    return number;
}

/**
 * @fn    char humanPiece()
 * @brief 플레이어의 피스를 정하는 함수
 * @return 
 */
char humanPiece() {
    char go_first = askYesNo("Do you require the first move?");

    /*플레이어가 선수를 선택한 경우*/
    if (go_first == 'y') {
        cout << "\nThen take the first move. You will need it.\n";

        return X;
    }
    /*플레이어가 후수를 선택한 경우*/
    else {
        cout << "\nYour bravery will be your undoing... I will go first.\n";

        return O;
    }
}

/**
 * @fn          char opponent(char piece)
 * @biref       상대의 반대 피스를 반환하는 함수
 * @param piece 상대의 피스
 * @return 
 */
char opponent(char piece) {
    if (piece == X) {
        return O;
    }
    else {
        return X;
    }
}

/**
 * @fn          void displayBoard(const vector<char>& board)
 * @brief       보드 표시 함수
 * @param board 보드
 */
void displayBoard(const vector<char>& board) {
    cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
    cout << "\n\t" << "---------";
    cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
    cout << "\n\t" << "---------";
    cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
    cout << "\n\n";
}

/**
 * @fn          char winner(const vector<char>& board)
 * @brief       승리 조건 확인 함수
 * @param board 보드
 * @return 
 */
char winner(const vector<char>& board) {
    /*모든 가능한 승리의 경우 모음*/
    const int WINNING_ROWS[8][3] =
    {
        /* X X X */
        { 0, 1, 2 },
        { 3, 4, 5 },
        { 6, 7, 8 },

        /* X
           X
           X
        */
        { 0, 3, 6 },
        { 1, 4, 7 },
        { 2, 5, 8 },

        /* X
            X
             X
        */
        { 0, 4, 8 },

        /*   X
            X
           X
        */
        { 2, 4, 6}
    };

    const int TOTAL_ROWS = 8;

    /*승리 가능한 배열(WINNING_ROWS)의 행 중에서*/
    /*모든 열이 동일한 값이 세 개 있는 경우(비어 있지 않음)*/
    /*그렇다면 승자*/
    for (int row = 0; row < TOTAL_ROWS; ++row) {

        /*보드 행의 왼쪽이 빈 공간이 아니고*/
        /*모든 가능한 승리의 경우 중*/
        /* 값이 같은 경우 확인 'X' 혹은 'O' */
        if ((board[WINNING_ROWS[row][0]] != EMPTY) &&
            (board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]])
            && (board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]])) {

            /*보드 행의 왼쪽 값 반환*/
            /* 'X' 혹은 'O' */
            return board[WINNING_ROWS[row][0]];
        }
    }

    /*승자가 없고*/
    /*빈 공간이 하나도 없는 경우*/
    if (count(board.begin(), board.end(), EMPTY) == 0) {
        /*TIE(동점, 무승부) 반환*/
        return TIE;
    }

    /*게임이 진행 중인 경우*/
    /*NO_ONE(아직 승자가 없습니다) 반환*/
    return NO_ONE;
}

/**
 * @fn          inline bool isLegal(int move, const vector<char>& board)
 * @brief       이동 가능한 셀이 빈 공간인지 확인하는 함수
 * @param move  이동
 * @param board 보드
 * @return 
 */
inline bool isLegal(int move, const vector<char>& board) {
    /*이동 가능한 셀이 빈 공간인 경우*/
    return (board[move] == EMPTY);
}

/**
 * @fn          int humanMove(const vector<char>& board, char human)
 * @brief       플레이어가 이동할 보드의 위치 번호를 선택하는 함수
 * @param board 보드
 * @param human 플레이어의 피스
 * @return 
 */
int humanMove(const vector<char>& board, char human) {
    int move = askNumber("Where will you move?", (board.size() - 1));

    /*이동 가능한 위치 번호 일 때까지 반복*/
    while (!isLegal(move, board)) {
        cout << "\nThat square is already occupied, foolish human.\n";
        move = askNumber("Where will you move?", (board.size() - 1));
    }

    cout << "Fine...\n";

    return move;
}

/**
 * @fn             int computerMove(vector<char> board, char computer)
 * @brief          컴퓨터가 이동할 보드의 위치 번호를 선택하는 함수
 * @param board    보드
 * @param computer 컴퓨터의 피스
 * @return 
 */
int computerMove(vector<char> board, char computer) {
    /*board vector를 참조로 받지 않고*/
    /*board vector를 복사본으로 받음*/

    /*보드의 이동할 위치 번호 변수*/
    unsigned int move = 0;

    /*다음 이동으로 승리하는 경우 찾았는지 확인 부울*/
    bool found = false;

    /*만약 컴퓨터가 다음 이동으로 이길 수 있다면, 그렇게 하세요*/
    /*다음 이동으로 컴퓨터가 승리하지 못하고*/
    /*보드의 이동할 위치 번호 변수가 보드 셀의 갯수 보다 작은 경우 반복*/
    while (!found && move < board.size()) {
        /*이동 가능한 셀이 빈 공간인 경우*/
        if (isLegal(move, board)) {
            /*보드의 이동 가능한 해당 위치에 컴퓨터의 피스를 저장*/
            board[move] = computer;

            /*다음 이동으로 컴퓨터가 승리하는 경우인지 확인*/
            found = winner(board) == computer;

            /*보드의 해당 셀을 빈 공간으로 설정*/
            board[move] = EMPTY;
        }

        /*보드의 이동 가능한 다음 위치에서 이기지 못하는 경우*/
        if (!found) {
            /*이동할 보드의 위치 번호 1 증가*/
            ++move;
        }
    }

    /*만약 인간이 다음 이동으로 이길 수 있다면, 막습니다*/
    /*다음 이동으로 컴퓨터가 승리하지 못하는 경우*/
    if (!found) {
        /*보드의 이동할 위치 번호 변수*/
        move = 0;

        /*상대의 반대 피스 반환 함수*/
        char human = opponent(computer);

        /*다음 이동으로 인간이 승리하지 못하고*/
        /*보드의 이동할 위치 번호 변수가 보드 셀의 갯수 보다 작은 경우 반복*/
        while (!found && move < board.size()) {
            /*이동 가능한 셀이 빈 공간인 경우*/
            if (isLegal(move, board)) {
                /*보드의 이동 가능한 위치에 인간의 피스를 저장*/
                board[move] = human;

                /*다음 이동으로 인간이 승리하는 경우인지 확인*/
                found = winner(board) == human;

                /*보드의 해당 셀을 빈 공간으로 설정*/
                board[move] = EMPTY;
            }

            /*보드의 이동 가능한 다음 위치에서 이기지 못하는 경우*/
            if (!found) {
                /*이동할 보드의 위치 번호 1 증가*/
                ++move;
            }
        }
    }

    /*다음 이동으로 컴퓨터가 승리하지 못하고*/
    /*다음 이동으로 인간이 승리하지 못하는 경우*/
    if (!found) {
        /*보드의 이동할 위치 번호 변수*/
        move = 0;
        unsigned int i = 0;

        /*
         4          == center (중앙)
         0, 2, 6, 8 == corners (모서리)
         1, 3, 5, 7 == rest of the squares (사각형의 나머지 셀)
        */
        const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };

        /*최선의 셀 선택*/
        /*최선의 셀을 찾지 못하고*/
        /*보드에서 최선의 셀을 선택할 때까지 반복*/
        while (!found && i < board.size()) {
            /*이동할 보드 위치에 최선의 셀 저장*/
            move = BEST_MOVES[i];

            /*이동 가능한 셀이 빈 공간인 경우*/
            if (isLegal(move, board)) {
                /*최선의 셀을 찾음 확인*/
                found = true;
            }

            ++i;
        }
    }

    cout << "I shall take square number " << move << endl;

    /*보드의 이동할 위치 번호 반환*/
    return move;
}

/**
 * @fn             void announceWinner(char winner, char computer, char human)
 * @brief          승리 또는 동점 발표 함수
 * @param winner   승자의 피스
 * @param computer 컴퓨터의 피스
 * @param human    플레이어의 피스
 */
void announceWinner(char winner, char computer, char human) {
    /*컴퓨터가 승리한 경우*/
    if (winner == computer) {
        cout << winner << "'s won!\n";
        cout << "As I predicted, human, I am triumphant once more -- proof\n";
        cout << "that computers are superior to humans in all regards.\n";
    }
    /*플레이어가 승리한 경우*/
    else if (winner == human) {
        cout << winner << "'s won!\n";
        cout << "No, no! It cannot be! Somehow you tricked me, human.\n";
        cout << "But never again! I, the computer, so swear it!\n";
    }
    /*동점(tie)인 경우*/
    else {
        cout << "It's a tie.\n";
        cout << "You were most lucky, human, and somehow managed to tie me.\n";
        cout << "Celebrate...for this is the best you will ever achieve.\n";
    }
}

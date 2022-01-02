/**
 @file tic-tac-toe.cpp
*/

/*
 Tic-Tac-Toe
 Plays the game of tic-tac-toe against a human opponent
 �ΰ� ���� ƽ���� ������ �մϴ�.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*���� ���*/
/*global constants*/
const char X      = 'X';
const char O      = 'O';
const char EMPTY  = ' ';
const char TIE    = 'T';
const char NO_ONE = 'N';

/*�Լ� ������Ÿ��*/
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
    /*������ �̵��� ��ġ ��ȣ ����*/
    int move;

    /*������ �� ����*/
    const int NUM_SQUARES = 9;

    /*����*/
    vector<char> board(NUM_SQUARES, EMPTY);

    /*���� ��ħ ǥ�� �Լ�*/
    instructions();

    /*�÷��̾��� �ǽ��� ���ϴ� �Լ�*/
    char human = humanPiece();

    /*����� �ݴ� �ǽ��� ��ȯ�ϴ� �Լ�*/
    char computer = opponent(human);

    /*���� 'X'*/
    char turn = X;

    /*���� ǥ�� �Լ�*/
    displayBoard(board);

    /*���ڰ� �ƹ��� ���� ��� �ݺ�*/
    while (winner(board) == NO_ONE) {
        /*�÷��̾��� ������ ���*/
        if (turn == human) {
            /*�÷��̾ �̵��� ������ ��ġ ��ȣ�� �����ϴ� �Լ�*/
            move = humanMove(board, human);

            /*������ �ش� ��ġ ���� �ΰ��� �ǽ� ����*/
            board[move] = human;
        }
        /*��ǻ���� ������ ���*/
        else {
            /*��ǻ�Ͱ� �̵��� ������ ��ġ ��ȣ�� �����ϴ� �Լ�*/
            move = computerMove(board, computer);
            
            /*������ �ش� ��ġ ���� ��ǻ���� �ǽ� ����*/
            board[move] = computer;
        }

        /*���� ǥ�� �Լ�*/
        displayBoard(board);

        /*����� �ݴ� �ǽ��� ��ȯ�ϴ� �Լ�*/
        turn = opponent(turn);
    }

    /*�¸� �Ǵ� ���� ��ǥ �Լ�*/
    announceWinner(winner(board), computer, human);

    return 0;
}

/**
 * @fn    void instructions()
 * @brief ���� ��ħ ǥ�� �Լ�
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
    } while (response != 'y' && response != 'n'); /*�Է��� 'y'�� �ƴϰ� 'n'�� �ƴ� ��� �ݺ�*/

    return response;
}

int askNumber(string question, int high, int low) {
    int number;
    do
    {
        cout << question << " (" << low << " - " << high << "): ";

        cin >> number;
    } while (number > high || number < low); /*number�� high���� ũ�ų� number�� low���� ���� ��� �ݺ�*/

    return number;
}

/**
 * @fn    char humanPiece()
 * @brief �÷��̾��� �ǽ��� ���ϴ� �Լ�
 * @return 
 */
char humanPiece() {
    char go_first = askYesNo("Do you require the first move?");

    /*�÷��̾ ������ ������ ���*/
    if (go_first == 'y') {
        cout << "\nThen take the first move. You will need it.\n";

        return X;
    }
    /*�÷��̾ �ļ��� ������ ���*/
    else {
        cout << "\nYour bravery will be your undoing... I will go first.\n";

        return O;
    }
}

/**
 * @fn          char opponent(char piece)
 * @biref       ����� �ݴ� �ǽ��� ��ȯ�ϴ� �Լ�
 * @param piece ����� �ǽ�
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
 * @brief       ���� ǥ�� �Լ�
 * @param board ����
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
 * @brief       �¸� ���� Ȯ�� �Լ�
 * @param board ����
 * @return 
 */
char winner(const vector<char>& board) {
    /*��� ������ �¸��� ��� ����*/
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

    /*�¸� ������ �迭(WINNING_ROWS)�� �� �߿���*/
    /*��� ���� ������ ���� �� �� �ִ� ���(��� ���� ����)*/
    /*�׷��ٸ� ����*/
    for (int row = 0; row < TOTAL_ROWS; ++row) {

        /*���� ���� ������ �� ������ �ƴϰ�*/
        /*��� ������ �¸��� ��� ��*/
        /* ���� ���� ��� Ȯ�� 'X' Ȥ�� 'O' */
        if ((board[WINNING_ROWS[row][0]] != EMPTY) &&
            (board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]])
            && (board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]])) {

            /*���� ���� ���� �� ��ȯ*/
            /* 'X' Ȥ�� 'O' */
            return board[WINNING_ROWS[row][0]];
        }
    }

    /*���ڰ� ����*/
    /*�� ������ �ϳ��� ���� ���*/
    if (count(board.begin(), board.end(), EMPTY) == 0) {
        /*TIE(����, ���º�) ��ȯ*/
        return TIE;
    }

    /*������ ���� ���� ���*/
    /*NO_ONE(���� ���ڰ� �����ϴ�) ��ȯ*/
    return NO_ONE;
}

/**
 * @fn          inline bool isLegal(int move, const vector<char>& board)
 * @brief       �̵� ������ ���� �� �������� Ȯ���ϴ� �Լ�
 * @param move  �̵�
 * @param board ����
 * @return 
 */
inline bool isLegal(int move, const vector<char>& board) {
    /*�̵� ������ ���� �� ������ ���*/
    return (board[move] == EMPTY);
}

/**
 * @fn          int humanMove(const vector<char>& board, char human)
 * @brief       �÷��̾ �̵��� ������ ��ġ ��ȣ�� �����ϴ� �Լ�
 * @param board ����
 * @param human �÷��̾��� �ǽ�
 * @return 
 */
int humanMove(const vector<char>& board, char human) {
    int move = askNumber("Where will you move?", (board.size() - 1));

    /*�̵� ������ ��ġ ��ȣ �� ������ �ݺ�*/
    while (!isLegal(move, board)) {
        cout << "\nThat square is already occupied, foolish human.\n";
        move = askNumber("Where will you move?", (board.size() - 1));
    }

    cout << "Fine...\n";

    return move;
}

/**
 * @fn             int computerMove(vector<char> board, char computer)
 * @brief          ��ǻ�Ͱ� �̵��� ������ ��ġ ��ȣ�� �����ϴ� �Լ�
 * @param board    ����
 * @param computer ��ǻ���� �ǽ�
 * @return 
 */
int computerMove(vector<char> board, char computer) {
    /*board vector�� ������ ���� �ʰ�*/
    /*board vector�� ���纻���� ����*/

    /*������ �̵��� ��ġ ��ȣ ����*/
    unsigned int move = 0;

    /*���� �̵����� �¸��ϴ� ��� ã�Ҵ��� Ȯ�� �ο�*/
    bool found = false;

    /*���� ��ǻ�Ͱ� ���� �̵����� �̱� �� �ִٸ�, �׷��� �ϼ���*/
    /*���� �̵����� ��ǻ�Ͱ� �¸����� ���ϰ�*/
    /*������ �̵��� ��ġ ��ȣ ������ ���� ���� ���� ���� ���� ��� �ݺ�*/
    while (!found && move < board.size()) {
        /*�̵� ������ ���� �� ������ ���*/
        if (isLegal(move, board)) {
            /*������ �̵� ������ �ش� ��ġ�� ��ǻ���� �ǽ��� ����*/
            board[move] = computer;

            /*���� �̵����� ��ǻ�Ͱ� �¸��ϴ� ������� Ȯ��*/
            found = winner(board) == computer;

            /*������ �ش� ���� �� �������� ����*/
            board[move] = EMPTY;
        }

        /*������ �̵� ������ ���� ��ġ���� �̱��� ���ϴ� ���*/
        if (!found) {
            /*�̵��� ������ ��ġ ��ȣ 1 ����*/
            ++move;
        }
    }

    /*���� �ΰ��� ���� �̵����� �̱� �� �ִٸ�, �����ϴ�*/
    /*���� �̵����� ��ǻ�Ͱ� �¸����� ���ϴ� ���*/
    if (!found) {
        /*������ �̵��� ��ġ ��ȣ ����*/
        move = 0;

        /*����� �ݴ� �ǽ� ��ȯ �Լ�*/
        char human = opponent(computer);

        /*���� �̵����� �ΰ��� �¸����� ���ϰ�*/
        /*������ �̵��� ��ġ ��ȣ ������ ���� ���� ���� ���� ���� ��� �ݺ�*/
        while (!found && move < board.size()) {
            /*�̵� ������ ���� �� ������ ���*/
            if (isLegal(move, board)) {
                /*������ �̵� ������ ��ġ�� �ΰ��� �ǽ��� ����*/
                board[move] = human;

                /*���� �̵����� �ΰ��� �¸��ϴ� ������� Ȯ��*/
                found = winner(board) == human;

                /*������ �ش� ���� �� �������� ����*/
                board[move] = EMPTY;
            }

            /*������ �̵� ������ ���� ��ġ���� �̱��� ���ϴ� ���*/
            if (!found) {
                /*�̵��� ������ ��ġ ��ȣ 1 ����*/
                ++move;
            }
        }
    }

    /*���� �̵����� ��ǻ�Ͱ� �¸����� ���ϰ�*/
    /*���� �̵����� �ΰ��� �¸����� ���ϴ� ���*/
    if (!found) {
        /*������ �̵��� ��ġ ��ȣ ����*/
        move = 0;
        unsigned int i = 0;

        /*
         4          == center (�߾�)
         0, 2, 6, 8 == corners (�𼭸�)
         1, 3, 5, 7 == rest of the squares (�簢���� ������ ��)
        */
        const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };

        /*�ּ��� �� ����*/
        /*�ּ��� ���� ã�� ���ϰ�*/
        /*���忡�� �ּ��� ���� ������ ������ �ݺ�*/
        while (!found && i < board.size()) {
            /*�̵��� ���� ��ġ�� �ּ��� �� ����*/
            move = BEST_MOVES[i];

            /*�̵� ������ ���� �� ������ ���*/
            if (isLegal(move, board)) {
                /*�ּ��� ���� ã�� Ȯ��*/
                found = true;
            }

            ++i;
        }
    }

    cout << "I shall take square number " << move << endl;

    /*������ �̵��� ��ġ ��ȣ ��ȯ*/
    return move;
}

/**
 * @fn             void announceWinner(char winner, char computer, char human)
 * @brief          �¸� �Ǵ� ���� ��ǥ �Լ�
 * @param winner   ������ �ǽ�
 * @param computer ��ǻ���� �ǽ�
 * @param human    �÷��̾��� �ǽ�
 */
void announceWinner(char winner, char computer, char human) {
    /*��ǻ�Ͱ� �¸��� ���*/
    if (winner == computer) {
        cout << winner << "'s won!\n";
        cout << "As I predicted, human, I am triumphant once more -- proof\n";
        cout << "that computers are superior to humans in all regards.\n";
    }
    /*�÷��̾ �¸��� ���*/
    else if (winner == human) {
        cout << winner << "'s won!\n";
        cout << "No, no! It cannot be! Somehow you tricked me, human.\n";
        cout << "But never again! I, the computer, so swear it!\n";
    }
    /*����(tie)�� ���*/
    else {
        cout << "It's a tie.\n";
        cout << "You were most lucky, human, and somehow managed to tie me.\n";
        cout << "Celebrate...for this is the best you will ever achieve.\n";
    }
}

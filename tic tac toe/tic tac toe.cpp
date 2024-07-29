#include <iostream>
#include <vector>

using namespace std;

//функция для вывода текста
void printtxt(string s) {
    cout << s << endl;
}

//функция для получения ответа на вопрос да/нет
char ask_yes_no(string s) {
    char c = 'i';
    while (c != 'y' && c != 'n') {
        cout << s << " y/n: ";
        cin >> c;
    }
    return c;
}

//функция вывода поля
void prtboard(const vector<char>& board) {
    cout << board[0] << " | " << board[1] << " | " << board[2] << endl;
    cout  << "---------"<<endl;
    cout << board[3] << " | " << board[4] << " | " << board[5] << endl;
    cout << "---------"<<endl;
    cout  << board[6] << " | " << board[7] << " | " << board[8] << endl;
    
}

//функция вывода победителя
char winner(vector<char>& board) {
    //победные совокупности клеток
    const int WINNING_ROWS[8][3] = { {0, 1, 2}, {3, 4, 5},
    {6, 7, 8},
    {0, 3, 6},
    {1, 4, 7},
    {2, 5, 8},
    {0, 4, 8},
    {2, 4, 6} };
    // цикл сравнивает каждую совокупность с тем, что у нас на поле
    for (int i = 0;i < 8;++i) {
        if (board[WINNING_ROWS[i][0]] != '.' && board[WINNING_ROWS[i][0]] == board[WINNING_ROWS[i][1]] && board[WINNING_ROWS[i][1]] == board[WINNING_ROWS[i][2]]) {
            //возвращаем победителя
            return board[WINNING_ROWS[i][0]];
        }
    }
    //возвращаем ничью
    if (count(board.begin(),board.end(),'.') == 0) {
        return 'n';
    }
    //сообщаем, что игра ещё не кончена
    return 'c';
}

//проверка на правильность хода
bool is_legal(int num, vector<char> board) {
    if (board[num] == '.') {
        return true;
    }
    
    return false;
}

//функция спрашивает число в каких-то пределах
int ask_num(int low, int high) {
    cout << "Enter the number " << low << "-" << high << ":";
    int num;
    cin >> num;
    while (num > high || num < low) {
        cout << "Enter the number " << low << "-" << high << ":";
        int num;
        cin >> num;
    }
    return num;
}

//функция описывает ход компьютера
int computer_move(vector<char> board,char c) {
    cout << "Computer's move: "<<endl;
    //самый лчший ход в центре
    if (board[4] == '.') {
        return 4;
    }

    //смотрим может ли компьютер выиграть следующим ходом
    for (int i = 0;i < 9;++i) {
        
        if (is_legal(i,board)) {
            board[i] = c;
            if (winner(board) == c) {
                return i;
            }
            board[i] = '.';
        }
    }

    char h;
    
    //присваиваем значение фигры игрока
    if (c == 'x') {
        h = 'o';
    }
    else {
        h = 'x';
    }

    //смотрим может ли игрок следующим ходом выиграть, если да, то перекрываем этот ход
    for (int i = 0;i < 9;++i) {

        if (is_legal(i, board)) {
            board[i] = h;
            if (winner(board) == h) {
                return i;
            }
            board[i] = '.';
        }
    }

    //ищем свободные клетки в углах
    if (board[0] == '.') { return 0; }
    if (board[2] == '.') { return 2; }
    if (board[6] == '.') { return 6; }
    if (board[8] == '.') { return 8; }

    //ищем свободные клетки в других местах, они самые бесполезные
    if (board[1] == '.') { return 1; }
    if (board[3] == '.') { return 3; }
    if (board[5] == '.') { return 5; }
    if (board[7] == '.') { return 7; }
}

//функция хода игрока
int player_move(vector<char>& board) {
    //для удобства спрашиваем обычную нмерацию, чтобы не спрашивать с нуля
    int h=ask_num(1, 9)-1;
    while (!is_legal(h,board)) {
        cout << "It's illegal!" << endl;
        h = ask_num(1, 9)-1;
    }
    return h;
}

//функция пишет кто победил
void announce_winner(char winner) {
    if (winner == 'p') {
        cout << "Ok... You won. But next time I will win!";
    }
    else if (winner == 'c') {
        cout << "Hahahahaha, I won, looser!";
    }
    else {
        cout << "Just tie...";
    }
}

int main()
{
    vector<char> board(9,'.');
    
    printtxt("Wassap! Welcome to the game. I will win you! Let's go.");
    printtxt("This is our game board:");
    cout << "1" << " | " << "2" << " | " << "3" << endl;
    cout << "---------" << endl;
    cout << "4" << " | " << "5" << " | " <<"6" << endl;
    cout << "---------" << endl;
    cout << "7" << " | " << "8" << " | " <<"9" << endl;
    //символы игрока и компьютера
    char player, computer;
    //спрашиваем хочет ли игрок начать превым и соответственно присваиваем фигуры
    if(ask_yes_no("Do you want to start game first?")=='y') {
        player = 'x';
        computer = 'o';
    }
    else {
        player = 'o';
        computer = 'x';
    }
    //если  игрока х, то он ходит первым
    if (player == 'x') {
        //в эту переменную записываем текущий ход
        int t;
        //пока игра не закончена
        while (winner(board) == 'c') {
            t = player_move(board);
            board[t] = player;
            prtboard(board);
            //важно посмотреть победил ли кто-то уже
            if (winner(board) != 'c') {
                break;
            }
            t = computer_move(board, computer);
            board[t] = computer;
            prtboard(board);
        }

    }//иначе игрок ходит вторым
    else {
        //в эту переменную записываем текущий ход
        int t;
        //пока игра не закончена
        while (winner(board) == 'c') {
            t = computer_move(board, computer);
            board[t] = computer;
            prtboard(board);
            //важно посмотреть победил ли кто-то уже
            if (winner(board) != 'c') {
                break;
            }
            t = player_move(board);
            board[t] = player;
            prtboard(board);
        }
    }
    //записываем кто победил
    char c = winner(board);

    if (c == computer) {
        announce_winner('c');
    }
    else if (c == player) {
        announce_winner('p');
    }
    else {
        announce_winner('n');
    }

}


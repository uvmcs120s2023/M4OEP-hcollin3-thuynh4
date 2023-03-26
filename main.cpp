//Hayden Collins, OEP
#include "Board.h"
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
#include "pieces/pieceClasses.h"
#include <filesystem>
#include <sstream>
using namespace std;

//TODO comments & readme
//TODO menu on program start (color to play, stockfish enabled, show legal moves, etc)
//TODO stockfish api via python
//TODO FEN get/set positions
//TODO print move disambiguating in printLegalMovesList
//TODO add promotion
//TODO save moves of the game in a list (needed for en passant and 50 move rule)
//TODO add en passant
//TODO add three fold repetition, insufficient material, 50 move rule draws
//TODO add test cases for all complex functionality

// square encoding
enum squares {
    a8 = 0,   b8, c8, d8, e8, f8, g8, h8,
    a7 = 16,  b7, c7, d7, e7, f7, g7, h7,
    a6 = 32,  b6, c6, d6, e6, f6, g6, h6,
    a5 = 48,  b5, c5, d5, e5, f5, g5, h5,
    a4 = 64,  b4, c4, d4, e4, f4, g4, h4,
    a3 = 80,  b3, c3, d3, e3, f3, g3, h3,
    a2 = 96,  b2, c2, d2, e2, f2, g2, h2,
    a1 = 112, b1, c1, d1, e1, f1, g1, h1, no_sq
};
string getMove(string FEN, int elo);

void passAndPlay(Board& board);

void stockFish(int elo,Board& board,bool side);

void regularPlay();

void tests();

int squareToInt(string square);

void makeCompMove(bool side,int elo,Board& board);

int main () {
    cout << "Welcome to Chess" << endl;
    Board board(true);
    regularPlay();
}

string getMove(string FEN, int elo){
    //change based on computer type
    const string python = "python";
    string command = python + " ../chess.py" + " "+ FEN +" "+ to_string(elo);
    system(command.c_str());
    string move = "e2e4";

    //gather move from file now
    ifstream stockMove;
    stockMove.open("../cmake-build-debug/stockfishMove.txt");
    if(stockMove.is_open()){
        stockMove >> move;
    }
    cout << move << endl;
    stockMove.close();


    return move;
    //pull from file when getting move from stockfish
}

void passAndPlay(Board& board){
    vector<int> moves;
    bool side = true;
    board.printBoard(true);
    while(!board.game_end){
        if(side){
            cout << "White to move." << endl;
        }else{
            cout << "Black to move." << endl;
        }
        moves = board.getUserMove(side, cout, cin);
        board.makeUserMove(moves);
        board.printBoard(true);
        board.checkGameEnd();
        side = !side;
    }
}

void stockFish(int elo,Board& board,bool side){
    if(!side){
        makeCompMove(!side,elo,board);
    }
    board.printBoard(side);
    while(!board.game_end) {
        //board.printLegalMovesList(board.side_to_move);
        vector<int> moves = board.getUserMove(side, cout, cin);
        board.makeUserMove(moves);
        board.printBoard(side);
        board.checkGameEnd();
        if(!board.game_end) {
            makeCompMove(!side, elo, board);
        }
        board.checkGameEnd();
    }
}

void regularPlay(){
    string line;
    stringstream ss;
    int elo;
    bool side;
    Board board(true);
    cout << "Would you like to do pass and play or play a computer? (p/c) or (debug) to enter custom setups: " << endl;
    getline(cin, line);
    while(line != "p" && line != "c" && line != "debug"){
        cout << "please enter a valid option (p/c): " << endl;
        cin.clear();
        getline(cin,line);
    }
    if(line == "p"){
        passAndPlay(board);
    }
    else if (line == "debug") {
        tests();
    }
    else{
        cin.clear();
        cout << "Jack , elo 400" << endl;
        cout << "Evan, elo 1000" << endl;
        cout << "Hayden, elo 1700" << endl;
        cout << "Huong, elo 1900" << endl;
        cout << "Who would you like to play against? (j,e,ha,hu) " << endl;
        getline(cin, line);
        while(line != "j" && line != "e" && line != "ha" && line != "hu"){
            cout << "please enter a valid option (j,e,ha,hu): " << endl;
            cin.clear();
            getline(cin,line);
        }
        if(line == "j"){
            elo = 400;
        }else if(line == "e"){
            elo = 1000;
        }else if(line == "ha"){
            elo = 1700;
        }else{
            elo = 2000;
        }
        //run stockfish option
        cin.clear();
        cout << "Would you like to play as white or black?(w/b) " << endl;
        getline(cin,line);
        while(line != "w" && line != "b"){
            cout << "please enter a valid option (w/b): " << endl;
            cin.clear();
            getline(cin,line);
        }
        if(line == "w"){
            side = true;
        }else{
            side = false;
        }
        stockFish(elo,board,side);
    }
}

void tests() {
    string setup;
    vector<string> setups = {"pin", "legality", "checkmate", "promotion", "castles", "stalemate", "disambiguate"};
    cout << "Choose a setup: 'pin', 'legality' ,'checkmate', 'promotion', 'castles', 'stalemate', 'disambiguate'" << endl;
    getline(cin,setup);
    while (find(setups.begin(), setups.end(), setup) == setups.end()) {
        cout << setup << " is invalid. Choose from: 'pin', 'legality', 'checkmate', 'promotion', 'castles', 'stalemate', 'disambiguate'" << endl;
        getline(cin,setup);
    }
    Board board(setup);
    board.printBoard(true);
    if (setup == "checkmate") {
        cout << "Enter Rh8 to demonstrate checkmate." << endl;
    }
    else if (setup == "stalemate") {
        cout << "Enter Qb6 to demonstrate stalemate." << endl;
    }
    else if (setup == "promotion") {
        cout << "Enter 'a8=Q', 'a8=R', 'a8=N', or 'a8=B' to demonstrate promotion." << endl;
    }
    else if (setup == "disambiguate") {
        cout << "Enter 'Rbd5' or 'Rgd5' to demonstrate disambiguation." << endl;
    }
    else if (setup == "castles") {
        cout << "Enter '0-0' or '0-0-0' to demonstrate castling." << endl;
    }
    else if (setup == "legality") {
        cout << "The Black rook on f8 prevents White from moving into check on f1 or f2. ";
        board.printLegalMovesList(board.side_to_move);
    }
    else if (setup == "pin") {
        cout << "The Black rook on e8 prevents White from moving the knight, it is pinned to the king. ";
        board.printLegalMovesList(board.side_to_move);
    }
    else {
        cout << "Invalid setup type" << endl;
    }
    while (!board.game_end) {
        vector<int> moves = board.getUserMove(board.side_to_move, cout, cin);
        board.makeUserMove(moves);
        board.printBoard(true);
        board.checkGameEnd();
    }
}

int squareToInt(string square){
    cout << square << endl;
    int rank = square[0]-97;
    int file = square[1]-48;
    return rank * 16 + file;
}

void makeCompMove(bool side, int elo, Board& board){
    string opp_move;
    int init;
    int target;
    opp_move = getMove(board.getFEN(side), elo);
    init = squareToInt(opp_move.substr(0,2));
    target = squareToInt(opp_move.substr(2,2));
    cout << init << endl;
    cout << target << endl;
    board.move(init,target);
}

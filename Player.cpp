#include "Player.h"
#include "GamePiece.h"

Player::Player(const bool isPlaying, const char whichPlayer) : _isPlaying(isPlaying), _isLoser(false), _whichPlayer(whichPlayer)
{
}
bool				   _isPlaying;
bool				   _isLoser;
char				   _whichPlayer;
int					   _numOfPieces;
int					   _sizeBoard;

const Player& Player::operator=(const Player& other)
{
    _isPlaying = other.getIsPlaying();
    _isLoser = other.getIsLoser();
    _whichPlayer = other.getWhichPlayer();
    _numOfPieces = other.getNumOfPieces();
    _sizeBoard = other.getSizeBoard();
    pieces = other.getPieces();

    return *this;
}

Player::Player(const Player& other)
{
    *this = other;
}

void Player::initPieces(vector<vector<GamePiece*>> board, int sizeBoard) {
    _sizeBoard = sizeBoard;
    int i, j;
    position data;
    for (i = 0; i < _sizeBoard; i++)
        for (j = 0; j < _sizeBoard; j++)
        {
            if (board[i][j] != nullptr && board[i][j]->getColor() == _whichPlayer)
            {
                data.x = i + 1;
                data.y = j + 1;
                pieces.push_back(data);
            }
        }
}

void Player::setNumOfPieces(int numOfPieces) {
    _numOfPieces = numOfPieces;
}

const bool Player::getIsPlaying()const
{
    return _isPlaying;
}

const int Player::getSizeBoard() const
{
    return _sizeBoard;
}

const bool Player::getIsLoser() const
{
    return _isLoser;
}

const int  Player::getNumOfPieces() const {
    return _numOfPieces;
}

void Player::setIsPlaying(bool isPlaying)
{
    _isPlaying = isPlaying;
}

void Player::setIsLoser(bool isWinner)
{
    _isLoser = isWinner;
}

const int Player::getWhichPlayer() const {
    return _whichPlayer;
}

void Player::setWhichPlayer(char whichPlayer) {
    _whichPlayer = whichPlayer;
}

list<position>& Player::getPieces() {
    return pieces;
}

const list<position>& Player::getPieces() const {
    return pieces;
}

void Player::save(ostream& out) const
{
    out.write(rcastcc(&_isPlaying), sizeof(bool));
    out.write(rcastcc(&_isLoser), sizeof(bool));
    out.write(rcastcc(&_whichPlayer), sizeof(char));
    out.write(rcastcc(&_numOfPieces), sizeof(int));
    out.write(rcastcc(&_sizeBoard), sizeof(int));

    for (auto itr = pieces.begin(); itr != pieces.end(); ++itr)
        out.write(rcastcc(&(*itr)), sizeof(position));

}

void Player::load(istream& in)
{
    in.read(rcastc(&_isPlaying), sizeof(bool));
    in.read(rcastc(&_isLoser), sizeof(bool));
    in.read(rcastc(&_whichPlayer), sizeof(char));
    in.read(rcastc(&_numOfPieces), sizeof(int));
    in.read(rcastc(&_sizeBoard), sizeof(int));

    pieces.clear();

    for (int i = 0; i < _numOfPieces ; ++i)
    {
        position pos;
        in.read(rcastc(&pos), sizeof(position));
        pieces.push_back(pos);
    }
}

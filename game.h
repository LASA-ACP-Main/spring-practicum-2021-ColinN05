class CheckersBoard
{
public:
	CheckersBoard();

    void Display();

    // tries to move piece at (x0,y0) to (x1,y1) returns true if move could be made and false if not
    bool TryMove(int x0, int y0, int x1, int y1); 
private:
	int Squares[8][8]; // 0 = empty square, 1 = black square, 2 = white square
};

class CheckersGame
{
public:
    void Play();
private:
    CheckersBoard Board; 
};
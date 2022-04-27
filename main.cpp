#include "game.h"
#include <iostream>
int main()
{
  srand(time(NULL));
  
  while (true)
  { 
    CheckersGame game;
    game.Play();
  }
  
	return 0;
}

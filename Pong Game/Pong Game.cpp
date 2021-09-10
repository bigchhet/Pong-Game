

#include <iostream>
#include <time.h>
#include <conio.h>
#include <Windows.h>


using namespace std;
enum eDir {STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

class cBall
{
	private:

		#pragma region private ball variables
			int x, y;
			int originalX, originalY;
			eDir direction;
		#pragma endregion

	public:

		#pragma region Constructors for ball
			//the constructor for class allowing input
			cBall(int posX, int posY)
			{
				//saves position of ball so we can reset the game later
				originalX = posX;
				originalY = posY;
				x = posX;
				y = posY;
				direction = STOP;
			}
		#pragma endregion

		#pragma region Paddle position reset
			void Reset()
			{
				x = originalX;
				y = originalY;
				direction = STOP;
			}
		#pragma endregion

		#pragma region Ball Direction Logic
				void ChangeDirection(eDir d)
				{
					direction = d;

				}

				//calls a random direction to make game mover interesting after play makes contact with ball
				void randomDirection()
				{
					//picks a random # from 1-6
					direction = (eDir)(rand() % 6 + 1);
				}
		#pragma endregion

		#pragma region Ball Moving Logic
				void Move()
				{

					switch (direction)
					{
						//ball not moving

					case STOP:
						break;

						//moving leftwards

					case LEFT:
						x--;
						break;

					case UPLEFT:
						x--;
						y--;
						break;

					case DOWNLEFT:
						x--;
						y++;
						break;

						//moving rightwards

					case RIGHT:
						x++;
						break;

					case UPRIGHT:
						x++;
						y++;
						break;

					case DOWNRIGHT:
						x++;
						y--;
						break;

					default:
						break;
					}
					
				}
		#pragma endregion		

		#pragma region replacing variables
				//compiler replaces the current position with x
				inline int getX()
				{
					return x;
				}

				//compiler replaces the current position with y
				inline int getY()
				{
					return y;
				}

				//compiler replaces the current position with direction
				inline eDir getDirection()
				{
					return direction;
				}
		#pragma endregion

		//prints the coorindates of ball onto console
		friend ostream & operator <<(ostream & o, cBall c)
		{
			o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
			return o;
		}

};

class cPaddle
{
	private:

		#pragma region private variables for paddle
			int x, y;
			int originalX, originalY;
		#pragma endregion

	public:

		#pragma region constructors for paddle
				cPaddle()
				{
					x = y = 0;
				}
				cPaddle(int posX, int posY) : cPaddle()
				{
					//starting position
					originalX = posX;
					originalY = posY;
					//position is provided from constructor
					x = posX;
					y = posY;
				}
		#pragma endregion

		#pragma region paddle reset logic
				inline void Reset()
				{
					x = originalX;
					y = originalY;
				}

		#pragma endregion

		#pragma region values for x and y
				inline int getX()
				{
					return x;
				}

				inline int getY()
				{
					return y;
				}
		#pragma endregion

		#pragma region Paddle moving logic
				inline void moveUp()
				{
					y--;
				}

				inline void moveDown()
				{
					y++;
				}
		#pragma endregion

		//prints the coorindates of paddle onto console
		friend ostream & operator <<(ostream& o, cPaddle c)
		{
			o << "Paddle [" << c.x << "," << c.y << "]";
			return o;
		}

};

class cGameManager
{
	private:

		#pragma region GamManager private variables
			int width, height, score1, score2;
			char up1, down1, up2, down2;
			bool quit;
			//initailzing pointers to ball and players
			cBall* ball;
			cPaddle* player1;
			cPaddle* player2;
		#pragma endregion

	public:

		#pragma region GameManager constructor
			cGameManager(int w, int h)
			{
				//randomize number
				srand(time(NULL));

				//ensures the game will run
				quit = false;

				//defines the controlls for player 1
				up1 = 'w';
				down1 = 's';

				//defines the controlls for player 2
				up2 = 'i';
				down2 = 'k';

				//preset score to zero at the start
				score1 = 0;
				score2 = 0;

				//parameters of the game
				width = w;
				height = h;

				//ensures the ball starts in the center
				ball = new cBall(w / 2, h / 2);

				//initialize the player location
				player1 = new cPaddle(1, h / 2 - 3);
				player2 = new cPaddle(w - 2, h / 2 - 3);

			}
		#pragma endregion

		#pragma region GameManager destructor

			//ensures the program will not create a memory leak for the pointers
			~cGameManager()
			{
				delete ball, player1, player2;
			}

		#pragma endregion

		#pragma region Scoring logic
			void ScoreUp(cPaddle* player)
			{
				//player1 scores a point 
				if (player == player1)
				{
					score1 += 10;
				}

				//player2 scores a poin
				else if (player == player2)
				{
					score2 += 10;
				}

				//ball amd players will reset after each score
				ball->Reset();
				player1->Reset();
				player2->Reset();
			}
		#pragma endregion

		#pragma region Most visual components in program
			void Draw()
			{
				//clear the console screen
				system("cls");
				cout << endl;
				cout << "PRESS 'p' TO QUIT " << endl;
				cout << endl;
				//create the top wall
				for (int i = 0; i < width + 2; i++)
				{
					//hexidecimal for fancy wall
					cout << "\xB2";
				}
				cout << endl;

				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						#pragma region getting coordinates
						//retrieve coordinates of the ball
						int ballx = ball->getX();
						int bally = ball->getY();
						//retrieves coordinates of the player 1
						int player1x = player1->getX();
						int player1y = player1->getY();
						//retrieve coordinates of player 2
						int player2x = player2->getX();
						int player2y = player2->getY();
						#pragma endregion

						#pragma region drawing pretty much everything
						//creates intial wall border
						if (j == 0)
						{
							//hexidecimal for fancy wall
							cout << "\xB2";
						}

						//logic for print ball position
						if (ballx == j && bally == i)
						{
							cout << "o";
						}

						//logic for displaying paddle for player 1
						else if (player1x == j && player1y == i)
						{
							//hexicode for block
							cout << "\xDB";
						}

						//logic for displaying paddle for player 2
						else if (player2x == j && player2y == i)
						{
							//hexicode for block
							cout << "\xDB";
						}



						//prints the 4 segments of paddle for player 1
						else if (player1x == j && player1y + 1 == i)
						{
							//hexicode for block
							cout << "\xDB";
						}
						else if (player1x == j && player1y + 2 == i)
						{
							//hexicode for block
							cout << "\xDB";
						}
						else if (player1x == j && player1y + 3 == i)
						{
							//hexicode for block
							cout << "\xDB";
						}

						//prints the 4 segments of paddle for player 2
						else if (player2x == j && player2y + 1 == i)
						{
							//hexicode for block
							cout << "\xDB";
						}
						else if (player2x == j && player2y + 2 == i)
						{
							//hexicode for block
							cout << "\xDB";
						}
						else if (player2x == j && player2y + 3 == i)
						{
							//hexicode for block
							cout << "\xDB";
						}



						//logic for creating the blank space of the map area
						else
						{
							cout << " ";
						}

						//iterates to create the side walls
						if (j == width - 1)
						{
							//hexidecimal for fancy wall
							cout << "\xB2";
						}
						#pragma endregion

					}

					//adding a line is essential to making a wall
					cout << endl;
				}

				//bottom wall
				for (int i = 0; i < width + 2; i++)
				{
					//hexidecimal for fancy wall
					cout << "\xB2";
				}
				cout << endl;

				//print score to the console
				cout << "Score 1: " << score1 << endl << "Score 2: " << score2 << endl;
			}
		#pragma endregion

		#pragma region Allow input
			void Input()
			{
				//will actually cause the ball to move
				ball->Move();

				#pragma region Stores the coordinates
					//retrieve coordinates of the ball
					int ballx = ball->getX();
					int bally = ball->getY();
					//retrieves coordinates of the player 1
					int player1x = player1->getX();
					int player1y = player1->getY();
					//retrieve coordinates of player 2
					int player2x = player2->getX();
					int player2y = player2->getY();
				#pragma endregion

				#pragma region Logic for ball/player/quiting

				if (_kbhit())
				{
					char current = _getch();

					//player 1 up
					if (current == up1)
					{
						if (player1y > 0)
						{
							player1->moveUp();
						}
					}

					//player 1 down
					if (current == down1)
					{
						if (player1y + 4 < height)
						{
							player1->moveDown();
						}
					}

					//player 2 up
					if (current == up2)
					{
						if (player2y > 0)
						{
							player2->moveUp();
						}
					}

					//player 2 down
					if (current == down2)
					{
						if (player2y + 4 < height)
						{
							player2->moveDown();
						}
					}

					//makes the ball direction randomized if it doesnt move
					if (ball->getDirection() == STOP)
					{
						ball->randomDirection();
					}

					//allow user to break out of game
					if (current == 'p')
					{
						quit = true;
					}
				}

				#pragma endregion

			}
		#pragma endregion

		#pragma region Paddle and Wall Bounce Logic
			void Logic()
			{
				#pragma region Stores the coordinates
				//retrieve coordinates of the ball
				int ballx = ball->getX();
				int bally = ball->getY();
				//retrieves coordinates of the player 1
				int player1x = player1->getX();
				int player1y = player1->getY();
				//retrieve coordinates of player 2
				int player2x = player2->getX();
				int player2y = player2->getY();
				#pragma endregion

				#pragma region Paddle logic
				//left paddle
				for (int i = 0; i < 4; i++)
				{
					if (ballx == player1x + 1) //+1 is so ball does not go into paddle
					{
						if (bally == player1y + i)
						{
							ball->ChangeDirection((eDir)((rand() % 3) + 4));
						}
					}
				}

				//right paddle
				for (int i = 0; i < 4; i++)
				{
					if (ballx == player2x - 1) //-1 is so ball does not go into paddle
					{
						if (bally == player2y + i)
						{
							ball->ChangeDirection((eDir)((rand() % 3) + 1));
						}
					}
				}
				#pragma endregion

				#pragma region Wall bounce logic

				//check if ball hits the bottom wall
				if (bally == height - 1)
				{
					ball->ChangeDirection(ball->getDirection() == DOWNLEFT ? UPRIGHT : UPLEFT); // ? = inline if
				}

				//check if ball hits the top wall
				if (bally == 0)
				{
					ball->ChangeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT); // ? = inline if
				}
				//check if right wall hits the ball
				if (ballx == width - 1)
				{
					//points are scored
					ScoreUp(player1);
				}
				//check if left wall hits the ball
				if (ballx == 0)
				{
					//points are scored
					ScoreUp(player2);
				}

				#pragma endregion

			}
			#pragma endregion

		#pragma region Run Logic
		void Run()
		{
			while (!quit)
			{
				Draw();
				Sleep(60);
				Input();
				Logic();
			}
		}
		#pragma endregion



			
};

int main()
{
	//declaring cGameManager object and giving width and height values
	cGameManager c(40,20);
	c.Run();
	system("cls");
	cout << "THANK YOU FOR PLAYING" << endl;
	return 0;
}

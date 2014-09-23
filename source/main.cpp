#include "AIE.h"
#include <iostream>

using namespace std;

//\Initializing const
const int screenWidth = 780;
const int screenHeight = 672;
const char* gameTitle = "Pong";

//\File Locations
const char* fontLoc = "./fonts/arial.fnt";
const char* player1Loc = "./images/Player1.png";
const char* ballLoc = "./images/Ball.png";
const char* enemy1Loc = "./images/Enemy1.png";

//\ Non magic stings
const char* score1 = "Player1 Score";
const char* score2 = "Player2 Score";


//\GameStates enum
enum GAMESTATES
{
	MAINMENU,
	HOWTOPLAY,
	GAMEPLAY,
	END
};
 
//\ Directions enum
enum DIRECTIONS
{
	UP,
	DOWN
};
//\ creating player
struct PlayerBar
{
	unsigned int spriteID;
	float width;
	float height;
	float x;
	float y;
	float speed = 500.f;
	unsigned int moveUpKey;
	unsigned int moveDownKey;
	int heightExt;
	int heightLow;
	void SetSize(float a_width, float a_height)
	{
		width = a_width;
		height = a_height;
	}
	void SetPosition(float a_x, float a_y)
	{
		x = a_x;
		y = a_y;
	}
	void SetMovementKeys(unsigned int a_moveUp, unsigned int a_moveDown)
	{
		moveUpKey = a_moveUp;
		moveDownKey = a_moveDown;
	}
	void Move(float a_deltaTime) 
	{
		if (IsKeyDown(moveUpKey))
		{
			y += speed * a_deltaTime;
			
			
			if (y + height * .5f >= heightExt)
			{
				y = heightExt - height *.5f;

			}
		}
		 
		if (IsKeyDown(moveDownKey))
		{
			y -= speed * a_deltaTime;
			if (y - height * .5f <= heightLow)
			{
				y = heightLow + height * .5f;
			}
		
		}
		MoveSprite(spriteID, x, y);
	}
	
};
PlayerBar player;
//\ creating the enemy
struct Enemy
{
	unsigned int enemyID;
	float x;
	float y;
	float width = 100;
	float height = 150;
	float speed = 500.f;
	unsigned int moveUpKey;
	unsigned int moveDownKey;
	int heightExt;
	int heightLow;
	void SetSize(float a_width, float a_height)
	{
		width = a_width;
		height = a_height;
	}
	void SetPosition(float a_x, float a_y)
	{
		x = a_x;
		y = a_y;
	}
	void SetMovementKeys(unsigned int a_moveUp, unsigned int a_moveDown)
	{
		moveUpKey = a_moveUp;
		moveDownKey = a_moveDown;
	}
	void Move(float a_deltaTime)
	{
		if (IsKeyDown(moveUpKey))
		{
			y += speed * a_deltaTime;


			if (y + height * .5f >= heightExt)
			{
				y = heightExt - height *.5f;

			}
		}

		if (IsKeyDown(moveDownKey))
		{
			y -= speed * a_deltaTime;
			if (y - height * .5f <= heightLow)
			{
				y = heightLow + height * .5f;
			}

		}
		MoveSprite(enemyID, x, y);
	}
};
Enemy enemy;
//\creating ball
struct Ball
{
	unsigned int ballID; 
	float x;
	float y;
	float width = 150;
	float height = 150;
	
	float speedY = 100.f;
	float speedX = 100.f;
	int widthExt;
	int widthLow;
	int heightExt;
	void SetPosition(float a_x, float a_y)
	{
		x = a_x;
		y = a_y;
	}
	void Move(float deltaTime)
	{
		//\ rate oh how fast the ball moves along the x and y axis
		x += speedX * deltaTime;
		y += speedY * deltaTime;

		y -= speedY * deltaTime;
		if (y - height * .5f <= 0)
		{
			y = 0 + height * .5f;
		}

		y += speedY * deltaTime;
		if (y + height * .5f >= screenHeight)
		{
			y = screenHeight - height *.5f;
			speedY *= -1;

		}
		

		if (x > screenWidth)
		{// todo implement score
			x = screenWidth *.5f;
		}
		if (x < 0 + width * .5)
		{// todo implement score
			x = 0 + width * .5f;

		}


		
	}
	//\ checking collision with player
	bool IsPlayerCollision()
	{
		//\ what we started with- this code work for square ball collision
		/*if (x - width / 2  <= player.x + player.width / 2 &&
			x - width / 2 >= player.x - player.width / 2 &&
			y - height <= player.y + player.height / 2 &&
			y + height >= player.height / 2)*/

		if (x  <= player.x + player.width / 2 &&
			x  >= player.x - player.width / 2 &&
			y <= player.y + player.height / 2 &&
			y >= player.height / 2)
		{
			return true;
		}
		return false;
	}
	//\ checking collision with enemy
	bool IsEnemyCollision()
	{
		if (x   <= enemy.x + enemy.width / 2 &&
			x   >= enemy.x - enemy.width / 2 &&
			y  <= enemy.y + enemy.height / 2 &&
			y  >=  enemy.height / 2)
		{
			return true;
		}
		return false;
	}

};




//\ Sprite Global

Ball ball;








GAMESTATES currentState = MAINMENU;

void UpdateMainMenu();
void UpdateGameStates();
void HowToPlay();
void IsPlayerCollision();
void IsEnemyCollision();






int main( int argc, char* argv[] )
{	
    Initialise(screenWidth, screenHeight, false, gameTitle);
	//AddFont(fontLoc);
	//SetFont(fontLoc);

	player.heightExt = screenHeight;
	ball.heightExt = screenHeight;
	enemy.heightExt = screenHeight;

	player.SetPosition(screenWidth *.5f, 80.f);
	player.SetSize(100.f, 120.f);
	//\ movement keys
	player.SetMovementKeys('W', 'S');
	enemy.SetMovementKeys('O', 'L');

    SetBackgroundColour(SColour(0, 0, 0, 255));
	//\ creating sprites
	player.spriteID = CreateSprite(player1Loc, player.width, player.height, true);
	ball.ballID = CreateSprite(ballLoc, ball.width, ball.height, true);
	enemy.enemyID = CreateSprite(enemy1Loc, enemy.width, enemy.height, true);

	
	ball.SetPosition(screenWidth * .5f, screenHeight * .5f);
	player.SetPosition(50, 390);
	enemy.SetPosition(750, 390);

	MoveSprite(player.spriteID, player.x, player.y);
	MoveSprite(ball.ballID, ball.x, ball.y);
	MoveSprite(enemy.enemyID, enemy.x, enemy.y);


    //\Game Loop
    do
    {


		 ClearScreen();
//		 SetFont(fontLoc);
		 switch (currentState)
		 {
		 case MAINMENU:
			 UpdateMainMenu();
			 break;
		 case GAMEPLAY:
			 UpdateGameStates();
			 break;
		 case HOWTOPLAY:
			 HowToPlay();
			 break;
		 case END:
			 break;
		 default:
			 break;
		 }


    } while(!FrameworkUpdate());

	DestroySprite(player.spriteID);
	DestroySprite(ball.ballID);
	DestroySprite(enemy.enemyID);

    Shutdown();

    return 0;
}
void UpdateGameStates()
{
	float delta = GetDeltaTime();
	//\ player movement

	player.Move(delta);
	ball.Move(delta);
	enemy.Move(delta);
	if(ball.IsEnemyCollision() == true)
	{
		ball.speedX *= -1;//\ this allows the ball to bounce off the enemy bar
	}
	if (ball.IsPlayerCollision() == true)
	{
		ball.speedX *= -1;//\ allowing ball to bounce off player bar

	}

	





	MoveSprite(enemy.enemyID, enemy.x, enemy.y);
	MoveSprite(ball.ballID, ball.x, ball.y);
	MoveSprite(player.spriteID, player.x, player.y);

	//\ drawing the sprites
	DrawSprite(ball.ballID);
	DrawSprite(player.spriteID);
	DrawSprite(enemy.enemyID);

}
void UpdateMainMenu()
{
	DrawString("Welcome to Pong\n", 300, 600);
	DrawString("Take an attempt at winning?\n", 225, 450);
	DrawString("Press P to play", 250, 400);
	DrawString(" How to play", 250, 250);
	DrawString("Press X", 250, 200);
	//\ Will go to game
	if (IsKeyDown('P'))
	{
		currentState = GAMEPLAY;
	}

	//\ Go to how to play
	if (IsKeyDown('X'))
	{
		currentState = HOWTOPLAY;
	}

	//\Will go back to menu
	if (IsKeyDown('D'))
	{
		currentState = MAINMENU;
	}
}
void HowToPlay()
{
	DrawString("Here's how to play:", 250, 600);
	DrawString("1.Use your paddle to block the ball from going past you.", 50, 500);
	DrawString("2. Get the ball past your oppenent to score.", 50, 450);
	DrawString("3.Get more point then your opponent in the end.", 50, 400);
	DrawString(" Controls:", 250, 350);
	DrawString("Press W to move up", 50, 250);
	DrawString("Press S to move Down", 50, 200);
	DrawString(" Press D to go back to the menu", 150, 100);
	//\Will go back to menu
	if (IsKeyDown('D'))
	{
		currentState = MAINMENU;
	}
}
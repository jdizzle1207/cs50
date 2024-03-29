//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
void movement(GEvent mouseEvent);

int main(void)
{
	// seed pseudorandom number generator
	srand48(time(NULL));

	// instantiate window
	GWindow window = newGWindow(WIDTH, HEIGHT);

	// instantiate bricks
	initBricks(window);

	// instantiate ball, centered in middle of window
	GOval ball = initBall(window);

	// instantiate paddle, centered at bottom of window
	GRect paddle = initPaddle(window);

	// instantiate scoreboard, centered in middle of window, just above ball
	GLabel label = initScoreboard(window);

	// number of bricks initially
	int bricks = COLS * ROWS;

	// number of lives initially
	int lives = LIVES;

	// number of points initially
	int points = 0;

	// declare initial velocity outside loop to allow for reverse direction
	double xvel = drand48()/32;
	double yvel = drand48()/16;

	// wait for click to begin
	waitForClick();

	// paddle won't move up/down no need to check every iteration
	int paddleY = getLocation(paddle).y;

	// keep playing until game over
	while (lives > 0 && bricks > 0)
	{
		// start the ball moving
		// (random velocity)
		move(ball, xvel, yvel);

		// start checking for collisions (ball is now moving)
		GObject collision = detectCollision(window, ball);
		if (collision != NULL)
		{
			if (collision == paddle)
			{
				yvel = -yvel;
			}
			// if we hit a brick, reverse direction, remove brick, gain point
			// but ONLY if not hitting paddle
			else if (strcmp(getType(collision), "GRect") == 0 && strcmp(getType(collision), "GLabel") != 0)
			{
				yvel = -yvel;
				removeGWindow(window, collision);
				points++;
				updateScoreboard(window, label, points);
			}
			// randomize x AND y velocity after collision
			double xvel = drand48()/32;
			double yvel = drand48()/16;
		}

		if (getX(ball) + getWidth(ball) >= WIDTH || getX(ball) <= 0)
		{
			xvel = -xvel;
		}

		if (getY(ball) <= 0 || getY(ball) + getHeight(ball) >= HEIGHT)
		{
			yvel = -yvel;
		}

		// lose a life if hit bottom, wait for click to restart
		if (getY(ball) + getWidth(ball) >= HEIGHT)
		{
			lives--;
			setLocation(ball, (WIDTH/2)-10, (HEIGHT/2)-10);
			waitForClick();
		}

		GEvent mouseEvent = getNextEvent(MOUSE_EVENT);
		if (mouseEvent && getEventType(mouseEvent) == MOUSE_MOVED )
		{
			setLocation(paddle, getX(mouseEvent)-(getWidth(paddle)/2), paddleY);
		}
		else if (mouseEvent) freeEvent(mouseEvent);
	}

	// wait for click before exiting
	waitForClick();

	// game over
	closeGWindow(window);
	return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
	// figure the size of a brick
	// add some color (if length change, change modulo below in setColor) 
	char* color[] = {"green", "blue", "red", "yellow", "orange", "magenta", "pink", "dark gray", "gray", "light gray"};
	int width = getWidth(window) / COLS;
	// take up the 10% third of window;
	int height = (getHeight(window) / 10) / ROWS;
	// for each row
	for (int row = 0; row < ROWS; row++)
	{
		// and each column within that row
		for (int col = 0; col < COLS; col++)
		{
			// create brick with spacing
			GRect brick = newGRect(col * width + 2, row * height + 2, width - 5, height - 5);
			setFilled(brick, true);
			setColor(brick, color[row%9]);
			add(window, brick);
		}
	}
}

/**
 * 
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
	GOval ball = newGOval((getWidth(window)/2)-10, (getHeight(window)/2)-10, 20, 20);
	setFilled(ball, true);
	add(window, ball);
	return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
	GRect paddle = newGRect((getWidth(window)/2)-10,getHeight(window)-12,20,3);
	setFilled(paddle, true);
	setColor(paddle, "RED");
	add(window, paddle);
	return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
	GObject score = newGLabel("0");
	int x = (getWidth(window) - getWidth(score)) / 2;
	int y = (getHeight(window) + getFontAscent(score)) / 2;
	setLocation(score, x, y);
	add(window, score);
	return score;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
	// update label
	char s[12];
	sprintf(s, "%i", points);
	setLabel(label, s);

	// center label in window
	double x = (getWidth(window) - getWidth(label)) / 2;
	double y = (getHeight(window) - getHeight(label)) / 2;
	setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
                                                     * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
	 */
GObject detectCollision(GWindow window, GOval ball)
{
	// ball's location
	double x = getX(ball);
	double y = getY(ball);

	// for checking for collisions
	GObject object;

	// check for collision at ball's top-left corner
	object = getGObjectAt(window, x, y);
	if (object != NULL)
	{
		return object;
	}

	// check for collision at ball's top-right corner
	object = getGObjectAt(window, x + 2 * RADIUS, y);
	if (object != NULL)
	{
		return object;
	}

	// check for collision at ball's bottom-left corner
	object = getGObjectAt(window, x, y + 2 * RADIUS);
	if (object != NULL)
	{
		return object;
	}

	// check for collision at ball's bottom-right corner
	object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
	if (object != NULL)
	{
		return object;
	}

	// no collision
	return NULL;
}

//includes
#include <stdio.h>
#include <math.h>
#include <random>
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <tchar.h>
#include <glut.h>

//-----------------

//  Global Variables   
int height = 800;
int width = 800;
bool start = false;
int i = 1;

bool collision = false;
int bar1X = 0;
int startX = 400;
int birdY = 0;
int score = 0;
int finish = false;
int set = -1;
bool powerUp = true;
int lives = 3;
bool fall = false;
int displayedScore = 0;
bool barrierOne = true;
bool barrierTwo = true;
bool barrierThree = true;
bool barrierFour = true;
bool barrierFive = true;
bool barrierSix = true;
bool barrierSeven = true;
bool barrierEight = true;
bool barrierNine = true;
//-----------------

//  Methods Signatures
void drawRect(int x, int y, int w, int h);
void drawCircle(int x, int y, float r);
void Key(unsigned char key, int x, int y);
void drawSetOne(int x);
void drawSetTwo(int x);
void drawSetThree(int x);
void Timer(int value);
void getSets(int value);
void Display();
//-----------------

// draws rectangles using the (x,y) of the bottom left vertex, width (w) and height (h)
void drawRect(int x, int y, int w, int h) {
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	glEnd();
}

// draws a circle using OpenGL's gluDisk, given (x,y) of its center and tis radius
void drawCircle(int x, int y, float r) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	GLUquadric* quadObj = gluNewQuadric();
	gluDisk(quadObj, 0, r, 50, 50);
	glPopMatrix();
}

// determines the actions to be done on pressing space
void Key(unsigned char k, int x, int y)
{
	// start the game
	if (k == ' ' && start == false) {
		start = true;
	}
	else
		if (k == ' ' && !finish)
		{
			// increment the bird's height if not collided
			if (!collision)
			{
				birdY += 50;
				/*PlaySound(TEXT("sfx_wing.WAV"), NULL, SND_ASYNC | SND_FILENAME  );*/
			}
			
		}
	
	glutPostRedisplay();
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int c1, int c2, int c3)
{
	glBegin(GL_TRIANGLES);
	glColor3f(c1, c2, c3);
	glVertex3f(x1, y1, 0.0f);
	glColor3f(c1, c2, c3);
	glVertex3f(x2, y2, 0.0f);
	glColor3f(c1, c2, c3);
	glVertex3f(x3, y3, 0.0f);
	glEnd();
}

// the display method
void Display() {
	glClear(GL_COLOR_BUFFER_BIT);


	// randomizing the sets appearance before the beginning of the game
	if (set == -1)
	{
		srand(time(0));
		set = rand() % 6 + 1;
	}

	// drawing the barriers
	glPushMatrix();
	glTranslatef(bar1X, 0, 0);
	getSets(set);
	glPopMatrix();
	

	// drawing the bird
	glPushMatrix();
	glTranslatef(0, birdY, 0);
	glColor3f(0.5, 0.5, 0.5);
	drawCircle(width / 4, height/2, 15);
	glColor3f(1, 1, 1);
	drawRect(width / 4 + 2, height / 2 + 3, 8, 3);
	drawTriangle(width / 4 + 13, height / 2 + 3, width / 4 + 13, height / 2 - 3, width / 4 + 18, height / 2,1,1,0 );
	drawTriangle(width / 4 - 10, height / 2 + 5, width / 4 - 10, height / 2 - 5, width / 4 - 2, height / 2, 0, 0, 0);
	glPopMatrix();


	// incrementing the score 
	if (!collision && start && !fall)
	{
		displayedScore++;
		/*PlaySound(TEXT("sfx_point.WAV"), NULL, SND_ASYNC | SND_FILENAME);*/
	}


	// displaying Hard luck on colliding three times
	if (collision || fall)
	{
		glColor3f(0.5, 0.5, 0.5);
		glRasterPos2f(400, 400); //define position on the screen
		char* string = "HARD LUCK !!!!!!!!!";

		while (*string) {
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *string++);
		}
		
	}

	// Displaying the score
	glColor3f(0.5, 0.5, 0.5);
	glRasterPos2f(50, 700); //define position on the screen
	char* scoreDisplay = "Score   ";

	while (*scoreDisplay) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *scoreDisplay++);
	}


	glColor3f(1, 1, 1);
	glColor3f(0.5, 0.5, 0.5);
	glRasterPos2f(120, 700); //define position on the screen
	int c = displayedScore;
	int i = 4;
	while (i >= 0)
	{
		
		int a = c / pow(10, i);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, a + 48);
		int z = pow(10, i);
		c = c % z;
		i--;
	}

	
		
	

	// Displaying the lives

	glColor3f(0.5, 0.5, 0.5);
	glRasterPos2f(50, 650); //define position on the screen
	char* string2 = "Lives";

	while (*string2) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *string2++);
	}


	if (lives >= 1)
	{
		glColor3f(0.5, 0.5, 0.5);
		drawCircle(110, 650,7);
	}
	if (lives >= 2)
	{
		glColor3f(0.5, 0.5, 0.5);
		drawCircle(125, 650, 7);
	}
	if (lives == 3)
	{
		glColor3f(0.5, 0.5, 0.5);
		drawCircle(140, 650, 7);
	}

	
	// displaying Congrats on passing through the barriers with 1 or more lives
	if (finish)
	{
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(400, 400); //define position on the screen
		char* string = "Congratulations!!!!";

		while (*string) {
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *string++);
		}
	}


	glFlush();
}

// drawing the first set
void drawSetOne(int x)
{

	//barrier one is drawn
	glColor3f(1, 0, 0);
	drawRect(x, 500, 75, 300);
	drawRect(x, 0, 75, 300);
	drawTriangle(x, 500, x + 75, 500, x + 37, 520,1,1,0 );
	drawTriangle(x, 300, x + 75, 300, x + 37, 280, 1, 1, 0);
	
	// checking for collision
	
	if (x + bar1X  <= width / 4 + 15 && x + bar1X + 75  >= width / 4 - 15)
	{
		if (height / 2 + birdY + 15 >= 500 || height / 2 + birdY - 15 <= 300)
		{
			if (barrierOne)
			{
				lives--;
				if (lives == 0)
					collision = true;
				barrierOne = false;
				if (height / 2 + birdY + 15 >= 500)
					birdY = 50;
				if (height / 2 + birdY - 15 <= 300)
					birdY = -50;
				PlaySound(TEXT("sfx_hit.WAV"), NULL, SND_ASYNC | SND_FILENAME);
			}
		}
	}

	// incrementing on safely passing through the barrier
	if (x + bar1X + 100 == width / 4)
	{
			score++;
		 
	}

	// drawing barrier two

	glColor3f(1, 0, 0);
	drawRect(x + 150, 450, 75, 500);
	drawRect(x + 150, 0, 75, 200);
	drawTriangle(x + 150, 450, x + 150 + 75, 450, x + 150 + 37, 470, 1, 1, 0);
	drawTriangle(x + 150, 200, x + 75 + 150, 200, x + 37 + 150, 180, 1, 1, 0);

	// checking for collision
	
	if (x + bar1X + 150  <= width / 4+15 && x + bar1X + 150 + 75  >= width / 4 -15)
	{
		if (height / 2 + birdY + 15 >= 450 || height / 2 + birdY - 15 <= 200)
		{
			if (barrierTwo)
			{
				lives--;
				if (lives == 0)
					collision = true;
				barrierTwo = false;
				if (height / 2 + birdY + 15 >= 450)
					birdY = 10;
				if (height / 2 + birdY - 15 <= 200)
					birdY = -150;
				PlaySound(TEXT("sfx_hit.WAV"), NULL, SND_ASYNC | SND_FILENAME );
			}
		}
	}

	// incrementing on safely passing through the barrier
	if (x + bar1X + 150 + 100 == width / 4)
	{
			score++;
	}

	//drawing the third barrier

	glColor3f(1, 0, 0);
	drawRect(x + 300, 500, 75, 500);
	drawRect(x + 300, 0, 75, 300);
	drawTriangle(x + 300, 500, x + 300 + 75, 500, x + 300 + 37, 520, 1, 1, 0);
	drawTriangle(x + 300, 300, x + 75 + 300, 300, x + 37 + 300, 280, 1, 1, 0);

	// checking for collision

	if (x + bar1X + 300 -15 <= width / 4 + 15 && x + bar1X + 300 + 75 + 15 >= width / 4 - 15)
	{
		if (height / 2 + birdY + 15 >= 500 || height / 2 + birdY - 15 <= 300)
		{
			if (barrierThree)
			{
				lives--;
				if (lives == 0)
					collision = true;
				barrierThree = false;
				if (height / 2 + birdY + 15 >= 500)
					birdY = 50;
				if (height / 2 + birdY - 15 <= 300)
					birdY = -50;
				PlaySound(TEXT("sfx_hit.WAV"), NULL, SND_ASYNC | SND_FILENAME );
			}
		}
	}

	// incrementing on safely passing through the barrier
	if (x + bar1X + 300 + 100 == width / 4)
	{
			score++;
		if (score == 9)
		{
			finish = true;
			start = false;
		}
	}
}

// drawing the second set
void drawSetTwo(int x)
{
	
	if (powerUp)
	{
		glColor3f(1, 1, 1);
		drawCircle(x + 30, 525, 15);
		drawTriangle(x + 30, 540, x + 45, 525, x + 15, 525, 1,1,0 );

		if (x + bar1X <= width / 4 + 15&& x + bar1X + 75 >= width / 4 - 15)
		{
			if (height / 2 + birdY + 15 >= 510 && height / 2 + birdY + 15 <= 540)
			{
				powerUp = false;
				PlaySound(TEXT("powerup.WAV"), NULL, SND_ASYNC | SND_FILENAME );
			}
		}
	}

	if(powerUp)
	{
		glColor3f(0, 1, 0);
	}
	else
	{
		glColor3f(1, 1, 1);
	}
	//barrier 1
	drawRect(x, 600, 75, 300);
	drawRect(x, 0, 75, 400);
	drawTriangle(x, 600, x + 75, 600, x + 37, 620, 1, 1, 0);
	drawTriangle(x, 400, x + 75, 400, x + 37, 380, 1, 1, 0);
	
	if (x + bar1X  <= width / 4 + 15 && x + bar1X+75 >= width / 4 - 15)
	{
		if (height / 2 + birdY + 15 >= 600 || height / 2 + birdY - 15 <= 400)
		{
			if (powerUp)
			{
				if (barrierFour)
				{
					lives--;
					if (lives == 0)
						collision = true;
					barrierFour = false;
					if (height / 2 + birdY + 15 >= 600)
						birdY = 150;
					if (height / 2 + birdY - 15 <= 400)
						birdY = 50;
					PlaySound(TEXT("sfx_hit.WAV"), NULL, SND_ASYNC | SND_FILENAME );
				}
			}
		}
	}
	if (x + bar1X + 100 == width / 4)
	{
			score++;
	}

	
	if (powerUp)
	{
		glColor3f(0, 1, 0);
	}
	else
	{
		glColor3f(1, 1, 1);
	}
	drawRect(x + 150, 500, 75, 500);
	drawRect(x + 150, 0, 75, 300);
	drawTriangle(x + 150, 500, x + 150 + 75, 500, x + 150 + 37, 520, 1, 1, 0);
	drawTriangle(x + 150, 300, x + 150 + 75, 300, x + 150 + 37, 280, 1, 1, 0);
	
	if (x + bar1X + 150  <= width / 4 + 15 && x + bar1X + 150+75 >= width / 4 -15)
	{
		if (height / 2 + birdY + 15 >= 500 || height / 2 + birdY -15 <= 300)
		{
			if (powerUp)
			{
				if (barrierFive)
				{
					lives--;
					if (lives == 0)
						collision = true;
					barrierFive = false;
					if (height / 2 + birdY + 15>= 500)
						birdY = 50;
					if (height / 2 + birdY -15 <= 300)
						birdY = -50;
					PlaySound(TEXT("sfx_hit.WAV"), NULL, SND_ASYNC | SND_FILENAME );
				}
			}
		}
	}
	if (x + bar1X + 150 + 100 == width / 4)
	{
			score++;
	}

	if (powerUp)
	{
		glColor3f(0, 1, 0);
	}
	else
	{
		glColor3f(1, 1, 1);
	}
	drawRect(x + 300, 400, 75, 500);
	drawRect(x + 300, 0, 75, 200);
	drawTriangle(x + 300, 400, x + 300 + 75, 400, x + 300 + 37, 420, 1, 1, 0);
	drawTriangle(x + 300, 200, x + 300 + 75, 200, x + 300 + 37, 180, 1, 1, 0);

	if (x + bar1X + 300 <= width / 4 + 15 && x + bar1X + 300+75 >= width / 4 - 15)
	{
		if (height / 2 + birdY + 15>= 400 || height / 2 + birdY-15 <= 200)
		{
			if (powerUp)
			{
				if (barrierSix)
				{
					lives--;
					if (lives == 0)
						collision = true;
					barrierSix = false;
					if (height / 2 + birdY +15 >= 400)
						birdY = -50;
					if (height / 2 + birdY -15<= 200)
						birdY = -150;
					PlaySound(TEXT("sfx_hit.WAV"), NULL, SND_ASYNC | SND_FILENAME );
				}
			}
		}
	}
	if (x + bar1X + 300 + 100 == width / 4)
	{
			score++;
		if (score == 9)
		{
			finish = true;
			start = false;
		}
	}
}

//drawing the third set
void drawSetThree(int x)
{

	glColor3f(0, 0, 1);
	drawRect(x, 600, 75, 300);
	drawRect(x, 0, 75, 300);
	drawTriangle(x, 600, x + 75, 600, x + 37, 620, 1, 1, 0);
	drawTriangle(x, 300, x + 75, 300, x + 37, 280, 1, 1, 0);
	
	if (x + bar1X <= width / 4 + 15 && x + bar1X+ 75>= width / 4 - 15)
	{
		if (height / 2 + birdY + 15>= 600 || height / 2 + birdY - 15 <= 300)
		{
			if (barrierSeven)
			{
				lives--;
				if (lives == 0)
					collision = true;
				barrierSeven = false;
				if (height / 2 + birdY + 15 >= 600)
					birdY = 150;
				if (height / 2 + birdY - 15 <= 300)
					birdY = -50;
				PlaySound(TEXT("sfx_hit.WAV"), NULL, SND_ASYNC | SND_FILENAME );
			}
		}
	}
	if (x + bar1X + 100 == width / 4)
	{
			score++;
	}

	glColor3f(0, 0, 1);
	drawRect(x + 150, 700, 75, 500);
	drawRect(x + 150, 0, 75, 450);
	drawTriangle(x + 150, 700, x + 150 + 75, 700, x + 150 + 37, 720, 1, 1, 0);
	drawTriangle(x + 150, 450, x + 150 + 75, 450, x + 150 + 37, 430, 1, 1, 0);
	
	if (x + bar1X + 150  <= width / 4 + 15 && x + bar1X + 150+75>= width / 4 -15)
	{
		if (height / 2 + birdY + 15 >= 700 || height / 2 + birdY-15 <= 450)
		{
			if (barrierEight)
			{
				lives--;
				if (lives == 0)
					collision = true;
				barrierEight = false;
				if (height / 2 + birdY + 15 >= 700)
					birdY = 250;
				if (height / 2 + birdY - 15 <= 450)
					birdY = 80;
				PlaySound(TEXT("sfx_hit.WAV"), NULL, SND_ASYNC | SND_FILENAME );
			}
		}
	}
	if (x + bar1X + 150 + 100 == width / 4)
	{
			score++;
	}

	glColor3f(0, 0, 1);
	drawRect(x + 300, 500, 75, 500);
	drawRect(x + 300, 0, 75, 300);
	drawTriangle(x + 300, 500, x + 300 + 75, 500, x + 300 + 37, 520, 1, 1, 0);
	drawTriangle(x + 300, 300, x + 300 + 75, 300, x + 300 + 37, 280, 1, 1, 0);
	
	if (x + bar1X + 300  <= width / 4 + 15 && x + bar1X + 300+75 >= width / 4 - 15)
	{
		if (height / 2 + birdY+ 15 >= 500 || height / 2 + birdY-15 <= 300)
		{
			if (barrierNine)
			{
				lives--;
				if (lives == 0)
					collision = true;
				barrierNine = false;
				if (height / 2 + birdY + 15 >= 500)
					birdY = 50;
				if (height / 2 + birdY - 15 <= 300)
					birdY = -50;
				PlaySound(TEXT("sfx_hit.WAV"), NULL, SND_ASYNC | SND_FILENAME );
			}
		}
	}
	if (x + bar1X + 300 + 100 == width / 4)
	{
			score++;
		if (score == 9)
		{
			finish = true;
			start = false;
		}
	}
}

// the timer function 
void Timer(int value)
{
	if (start ) 
	{
		if (!collision)
		{
			if (finish)
			{
				
				
				glutPostRedisplay();
				start = false;
				glutTimerFunc(20, NULL, 0);
				
				
			}
			else if (birdY + height / 4 <= -100 || birdY + height / 4 >= 600)
			{
				fall = true;
				glutPostRedisplay();
				glutTimerFunc(20, NULL, 0);
			}
			else if( displayedScore >= 408)
			{
				PlaySound(TEXT("sfx_point.wav"), NULL, SND_FILENAME | SND_ASYNC);
				finish = true;
			}
			else
			{
				bar1X -= 5;
				birdY -= 5;
			}
		}
		else
		{
			glutPostRedisplay();
			glutTimerFunc(20, NULL, bar1X);
		}
	}
	glutPostRedisplay();

	glutTimerFunc(20, Timer, bar1X);

}

// the method with different sets order
void getSets(int value)
{
	switch (value)
	{
	case 1:
		drawSetOne(startX);
		drawSetTwo(startX + 650);
		drawSetThree(startX + 1300);
	    break;
	case 2:
		drawSetOne(startX);
		drawSetThree(startX + 650);
		drawSetTwo(startX + 1300);
		break;
	case 3:
		drawSetThree(startX);
		drawSetOne(startX + 650);
		drawSetTwo(startX + 1300);
		break;
	case 4:
		drawSetThree(startX);
		drawSetTwo(startX + 650);
		drawSetOne(startX + 1300);
		break;
	case 5:
		drawSetTwo(startX );
		drawSetThree(startX + 650);
		drawSetOne(startX + 1300);
		break;
	case 6:
		drawSetTwo(startX );
		drawSetOne(startX + 650);
		drawSetThree(startX + 1300);
		break;
	}
}

// the main method
void main(int argc, char** argr) {

	glutInit(&argc, argr);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(150, 150);

	glutCreateWindow("Assignment-One");		

	glutDisplayFunc(Display);
	glutKeyboardFunc(Key);
	glutTimerFunc(0, Timer, 0);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, width, 0.0, height);

	glutMainLoop();

	
}

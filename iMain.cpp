
# include "iGraphics.h"

/* 
	function iDraw() is called again and again by the system.
*/

#define ScreenLength  960
#define ScreenWidth  540

char movingBackgroungImages[18][100] = {
	"Images\\background images\\meena3_01.bmp",
	"Images\\background images\\meena3_02.bmp",
	"Images\\background images\\meena3_03.bmp",
	"Images\\background images\\meena3_04.bmp",
	"Images\\background images\\meena3_05.bmp",
	"Images\\background images\\meena3_06.bmp",
	"Images\\background images\\meena3_07.bmp",
	"Images\\background images\\meena3_08.bmp",
	"Images\\background images\\meena3_09.bmp",
	"Images\\background images\\meena3_10.bmp",
	"Images\\background images\\meena3_11.bmp",
	"Images\\background images\\meena3_12.bmp",
	"Images\\background images\\meena3_13.bmp",
	"Images\\background images\\meena3_14.bmp",
	"Images\\background images\\meena3_15.bmp",
	"Images\\background images\\meena3_16.bmp",
	"Images\\background images\\meena3_17.bmp",
	"Images\\background images\\meena3_18.bmp",
};
char characterImages[12][100] {
	"Images\\mainCharacter\\1.bmp",
	"Images\\mainCharacter\\2.bmp",
	"Images\\mainCharacter\\3.bmp",
	"Images\\mainCharacter\\4.bmp",
	"Images\\mainCharacter\\5.bmp",
	"Images\\mainCharacter\\6.bmp",
	"Images\\mainCharacter\\7.bmp",
	"Images\\mainCharacter\\8.bmp",
	"Images\\mainCharacter\\9.bmp",
	"Images\\mainCharacter\\10.bmp",
	"Images\\mainCharacter\\11.bmp",
	"Images\\mainCharacter\\12.bmp",
};
char standImage[100] = "Images\\mainCharacter\\12.bmp";
char copter[100] = "Images\\vector_sprite_helicopter_commission_by_pasunna_zacrifa-d6bxqfi.bmp";
char boxImage[100] = "box1.bmp";

int mbSpeed = 4;
int numberOfMb = 18;
int mainx = 120;
int mainy = 100;
int mainGround = mainy;
int jumpLimit = 100 + mainGround;
int mainIndex = 0;
int boxx, boxy;
int boxHeight = 42;
bool stand = true;
bool gotoRight = false;
bool gotoUp = false;
bool copterDropBox = false;

int copterx = ScreenLength;
int coptery = 450;

void resetCopter() {
	copterx = ScreenLength;
	copterDropBox = false;
}
void changeCopterPosition() {
	copterx -= 2;
	if (copterx <= 717 && !copterDropBox) {
		copterDropBox = true;
		boxx = copterx + 140;
		boxy = coptery - boxHeight;
	}
	if (gotoRight || gotoUp) {
		copterx -= mbSpeed;
	}
	if (copterx <= 0) {
		resetCopter();
	}
}
void drawCopter() {
	iShowBMP2(copterx, coptery, copter, 0);
	changeCopterPosition();
}
void changeBoxPosition() {
	boxy -= 2;
	if (boxy <= mainGround) {
		boxy = mainGround;
	}
	if (stand) {

	}
	else if (gotoRight || gotoUp) {
		boxx -= mbSpeed;
	}
}
void printBox() {
	if (!copterDropBox) return;
	iShowBMP2(boxx, boxy, boxImage, 0);
	changeBoxPosition();
}


struct movingBackground {
	int x;
	int y;
	char image[100];
	int number;
	void setPosition() {
		y = 0;
		x = number * 60;
	}
	void showImage() {
		iShowBMP(x, y, image);
		//changeCoordinates();
	}

	void changeCoordinates() {
		x -= mbSpeed;
		if (x <= -60) {
			x = (17) * 60;
		}
	}

}mb[18];

void copyImage() {
	for (int i = 0; i < 18; i++) {
		mb[i].number = i + 1;
		strcpy(mb[i].image, movingBackgroungImages[i]);
		mb[i].setPosition();
		printf("%s\n", mb[i].image);
	}
}

int numberOfCharacters = 12;
int moveUpSign1 = 1;
void displayMainCharacter() {
	if (stand) {
		iShowBMP2(mainx, mainy, standImage, 0);
	}
	if (gotoRight) {
		iShowBMP2(mainx, mainy, characterImages[mainIndex], 0);
		for (int i = 0; i < numberOfMb; i++) {
			mb[i].changeCoordinates();
		}
	}
	if (gotoUp) {
		mainy += (mbSpeed * moveUpSign1);
		if (mainy >= jumpLimit) {
			moveUpSign1 = moveUpSign1 * (-1);
		}
		if (mainy <= mainGround) {
			stand = false;
			gotoRight = true;
			gotoUp = false;
			moveUpSign1 = moveUpSign1 * (-1);
			mainy = mainGround;
			
		}
		
		for (int i = 0; i < numberOfMb; i++) {
			mb[i].changeCoordinates();
		}
		iShowBMP2(mainx, mainy, characterImages[mainIndex], 0);
	}
}




void iDraw()
{
	//place your drawing codes here	
	iClear();
	

	for (int i = 0; i < 18; i++) {
		mb[i].showImage();
	}

	drawCopter();
	displayMainCharacter();
	printBox();
	iFilledRectangle(0, 0, 60, ScreenWidth);

}

/* 
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/* 
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("%d %d\n", mx, my);
		//place your codes here	
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here	
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed. 
*/
void iKeyboard(unsigned char key)
{
	if(key == 'q')
	{
		//do something with 'q'
	}
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use 
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, 
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, 
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT 
*/
void iSpecialKeyboard(unsigned char key)
{
	if (gotoUp) return;
	if (key == GLUT_KEY_RIGHT) {
		stand = false;
		gotoUp = false;
		gotoRight = true;
	}
	if (key == GLUT_KEY_LEFT) {
		stand = true;
		gotoUp = false;
		gotoRight = false;
	}
	if (key == GLUT_KEY_UP) {
		stand = false;
		gotoUp = true;
		gotoRight = false;
	}

	if(key == GLUT_KEY_END)
	{
		exit(0);	
	}
	//place your codes for other keys here
}

void changeMainIndex() {
	mainIndex++;
	if (mainIndex >= numberOfCharacters) {
		mainIndex = 0;
	}
}

void change() {
	changeMainIndex();
}

int main()
{
	//place your own initialization codes here. 
	copyImage();
	iSetTimer(100, change);
	iInitialize(ScreenLength, ScreenWidth, "Jini Survival!!");
	return 0;
}	
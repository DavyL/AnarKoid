#ifndef COMMON_H
#define COMMON_H

struct screenInfo{
	unsigned short int width;
	unsigned short int height;
	unsigned short int posX;
	unsigned short int posY;
	
	unsigned short int fullScreen;

	long int time;
};

struct screenInfo getScreenInfo(struct screenInfo __screen);
void displayScreenInfo(struct screenInfo __screen);



#endif

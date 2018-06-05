#ifndef BMPLOADER_H
#define BMPLOADER_H

#include<windows.h>

class BmpLoader
{
	public:
		unsigned char* textureData;
		int Width,Height;
		BmpLoader(const char* filename);
		~BmpLoader();	
	private:
		BITMAPFILEHEADER bfh;
		BITMAPINFOHEADER bih;
};
#endif

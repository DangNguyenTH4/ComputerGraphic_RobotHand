#include <stdio.h>
#include "BmpLoader.h"
BmpLoader::BmpLoader(const char* filename)
{
	FILE *file =0;
	file = fopen(filename,"rb");
	if(!file)
	{
		//khong thay file
	}
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,file);
	if(bfh.bfType!=0x4D42)
	{
		//khong phai file bitmap
	}
	fread(&bih,sizeof(BITMAPINFOHEADER),1,file);
	if(bih.biSizeImage==0)
	{
		bih.biSizeImage=bih.biHeight*bih.biWidth;
	}
	textureData = new unsigned char[bih.biSizeImage];
	fseek(file,bfh.bfOffBits,SEEK_SET);
	fread(textureData,1,bih.biSizeImage,file);
	unsigned char temp;
	for(int i=0;i<bih.biSizeImage;i+=3)
	{
		temp = textureData[i];
		textureData[i]=textureData[i+2];
		textureData[i+2]=temp;
	}
	Width = bih.biWidth;
	Height =bih.biHeight;
	fclose(file);
}
BmpLoader::~BmpLoader()
{
	delete [] textureData;
	
}

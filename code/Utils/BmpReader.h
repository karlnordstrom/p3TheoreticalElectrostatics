/*
 * BmpReader.h
 *
 *  Created on: 21 Feb 2013
 *      Author: david
 *
 */

#ifndef BMPREADER_H_
#define BMPREADER_H_

#include <string>
#include <stdio.h>
#include <iostream>
#include "../Structures/Grid.h"

#define BMP_MAGIC_NUM 0x4D42		// Magic number for bmp file format
// Compression Types
#define BI_RGB       0             	// No compression - straight BGR data
#define BI_RLE8      1             	// 8-bit run-length compression
#define BI_RLE4      2             	// 4-bit run-length compression
#define BI_BITFIELDS 3             	// RGB bitmap with RGB masks

#pragma pack(2)	// To fix problem with file padding

/**
 * @struct 					BITMAPFILEHEADER
 * @brief 					Container for the BMP file header
 * @var bfType 				Magic number for file, should be 0x4D42 for bmp
 * @var bfSize 				Size of file
 * @var bfReserved1 		Reserved space
 * @var bfReserved2 		Reserved space
 * @var vfOffBits 			Offset to bitmap data
 */
typedef struct {
    unsigned short bfType;
    unsigned int   bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int   bfOffBits;
} BITMAPFILEHEADER;

#pragma pack()

/**
 * @struct 					BITMAPINFOHEADER
 * @brief 					Container for the BMP info header
 * @var biSize 				Size of info header
 * @var biWidth 			Width of image
 * @var biHeight 			Height of image
 * @var biPlanes 			Number of colour planes
 * @var biBitCount 			Number of bits per pixel
 * @var biCompression 		Type of compression to use
 * @var biSizeImage 		Size of image data
 * @var biXPelsPerMeter 	X pixels per metre
 * @var biYPelsPerMeter 	Y pixels per metre
 * @var biClrUsed 			Number of colours used
 * @var biClrImportant 		Number of important colours
 */
typedef struct {
    unsigned int   biSize;
    int            biWidth;
    int            biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int   biCompression;
    unsigned int   biSizeImage;
    int            biXPelsPerMeter;
    int            biYPelsPerMeter;
    unsigned int   biClrUsed;
    unsigned int   biClrImportant;
} BITMAPINFOHEADER;

/**
 * @struct 					RGBQUAD
 * @brief 					Colourmap entry structure
 * @var rgbBlue				unsigned char : Blue value
 * @var rgbGreen			unsigned char : Green value
 * @var rgbRed				unsigned char : Red value
 * @var rgbReserved			unsigned char : Reserved
 */
typedef struct {
    unsigned char  rgbBlue;
    unsigned char  rgbGreen;
    unsigned char  rgbRed;
    unsigned char  rgbReserved;
} RGBQUAD;

/**
 * @class 					Bmp_Reader
 * @brief					Used to read in information from a bmp
 */
class Bmp_Reader {
public:

	/**
	 * @function					Constructor
	 * @brief						Creates a bmp object from a requested bmp file
	 * @param						std::string : filename
	 * @return						None
	 */
	Bmp_Reader(std::string file);

	/**
	 * @function					get_width
	 * @brief						get the horizontal size of the bmp
	 * @return						Horizontal size of bmp
	 */
	unsigned int get_width();

	/**
	 * @function					get_height
	 * @brief 						get the vertical size of the bmp
	 * @return						Vertical Size of bmp
	 */
	unsigned int get_height();

	/**
	 * @function					get_pixels
	 * @brief						gets the array of pixel information
	 * @return						Array of pixel information
	 */
	RGBQUAD *get_pixels();

	/**
	 * @function					get_size
	 * @brief						gets the number of pixels
	 * @return						Number of pixels
	 */
	unsigned int get_size();
	virtual ~Bmp_Reader();
private:
	BITMAPFILEHEADER fh;
	BITMAPINFOHEADER ih;
	RGBQUAD *pixels;
};

#endif /* BMPREADER_H_ */
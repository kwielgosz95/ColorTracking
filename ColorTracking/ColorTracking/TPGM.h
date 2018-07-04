#pragma once
/*
* Created: 2011-11-04
* Author : Tomasz G¹ciarz
*
* Copyright (C) 2011.  All rights reserved.
*/

#if !defined(DEF_TPGM)
#define DEF_TPGM

int readPGMB_header(const char *fname, int *rows, int *cols, int *max_color);
int readPGMB_data(unsigned char *image, const  char *fname, int hlen, int rows, int cols, int max_color);
int writePGMB_image(const char *fname, unsigned char *image, int rows, int cols, int max_color);

int readPPMB_header(const char *fname, int *rows, int *cols, int *max_color);
int readPPMB_data(unsigned char *imageR, unsigned char *imageG, unsigned char *imageB, const  char *fname, int hlen, int rows, int cols, int max_color);
int writePPMB_image(const char *fname, unsigned char *imageR, unsigned char *imageG, unsigned char *imageB, int rows, int cols, int max_color);

#endif

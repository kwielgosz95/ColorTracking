
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>

using namespace std;

void skipcomments(FILE *fp)
{
	int ch;
	char line[256];

	while ((ch = fgetc(fp)) != EOF && isspace(ch))
		;
	if (ch == '#') {
		fgets(line, sizeof(line), fp);
		skipcomments(fp);
	}
	else
		fseek(fp, -1, SEEK_CUR);
}


int readPGMB_header(const char *fname, int *rows, int *cols, int *max_color)
{

	FILE *fp;
	size_t flen, hlen;
	char signature[3];

	if ((fp = fopen(fname, "rb")) == NULL)
		return 0;



	fseek(fp, 0, SEEK_END);
	flen = ftell(fp);	//file lenght
	fseek(fp, 0, SEEK_SET);

	fgets(signature, sizeof(signature), fp);
	if (signature[0] != 'P' || signature[1] != '5')
	{
		fclose(fp); return 0;
	}	//probably not pgm binary file...

	skipcomments(fp);
	fscanf(fp, "%d", cols);
	skipcomments(fp);
	fscanf(fp, "%d", rows);
	skipcomments(fp);
	fscanf(fp, "%d", max_color);
	fgetc(fp);

	hlen = ftell(fp); //header lenght
	fclose(fp);
	if ((*rows) * (*cols) != (flen - hlen))	//we assume only one picture in the file
		return 0;

	return hlen;
}

int readPGMB_data(unsigned char *image, const char *fname, int hlen, int rows, int cols, int max_color)
{

	FILE *fp;
	if ((fp = fopen(fname, "rb")) == NULL)
		return 0;

	fseek(fp, hlen, SEEK_SET);
	int readedrows = fread(image, cols, rows, fp);
	fclose(fp);

	if (rows != readedrows)
		return 0;

	return 1;
}

int writePGMB_image(const char *fname, unsigned char *image, int rows, int cols, int max_color)
{
	FILE *fp;

	if ((fp = fopen(fname, "wb")) == NULL)
		return(0);

	fprintf(fp, "P5\n%d %d\n# eyetom.com\n%d\n", cols, rows, max_color);

	if (rows != fwrite(image, cols, rows, fp)) {
		fclose(fp);
		return(0);
	}

	fclose(fp);
	return(1);
}

int readPPMB_header(const char *fname, int *rows, int *cols, int *max_color)
{

	FILE *fp;
	size_t flen, hlen;
	char signature[3];

	if ((fp = fopen(fname, "rb")) == NULL)
		return 0;

	fseek(fp, 0, SEEK_END);
	flen = ftell(fp);	//file lenght
	fseek(fp, 0, SEEK_SET);

	fgets(signature, sizeof(signature), fp);
	if (signature[0] != 'P' || signature[1] != '6')
	{
		fclose(fp); return 0;
	}	//probably not pgm binary file...

	skipcomments(fp);
	fscanf(fp, "%d", cols);
	skipcomments(fp);
	fscanf(fp, "%d", rows);
	skipcomments(fp);
	fscanf(fp, "%d", max_color);
	fgetc(fp);

	hlen = ftell(fp); //header lenght
	fclose(fp);
	if ((*rows) * 3 * (*cols) != (flen - hlen))	//we assume only one picture in the file
		return 0;

	return hlen;
}

int readPPMB_data(unsigned char *imageR, unsigned char *imageG, unsigned char *imageB, const char *fname, int hlen, int rows, int cols, int max_color)
{
	long i, wxh;
	FILE *fp;

	if (max_color>255) return 0;	//for now only 1 byte color values

	if ((fp = fopen(fname, "rb")) == NULL)
		return 0;

	fseek(fp, hlen, SEEK_SET);

	wxh = rows*cols;
	for (i = 0; i<wxh; i++) {
		imageR[i] = (unsigned char)fgetc(fp);
		imageG[i] = (unsigned char)fgetc(fp);
		imageB[i] = (unsigned char)fgetc(fp);
	}

	return 1;
}

int writePPMB_image(const char *fname, unsigned char *imageR, unsigned char *imageG, unsigned char *imageB, int rows, int cols, int max_color)
{
	long i, wxh;
	FILE *fp;

	if ((fp = fopen(fname, "wb")) == NULL)
		return(0);

	fprintf(fp, "P6\n%d %d\n# eyetom.com\n%d\n", cols, rows, max_color);

	wxh = rows*cols;
	for (i = 0; i<wxh; i++) {      /* Write the image in pixel interleaved format. */
		fputc(imageR[i], fp);
		fputc(imageG[i], fp);
		fputc(imageB[i], fp);
	}

	fclose(fp);
	return(1);
}



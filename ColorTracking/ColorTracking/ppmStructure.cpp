#include "ppmStructure.h"


void ppmStructure::initRGBTable()
{
	R_ppm = new unsigned char *[h_ppm];
	R_ppm[0] = new unsigned char[h_ppm * w_ppm];
	for (int i = 1; i < h_ppm; i++)
		R_ppm[i] = R_ppm[i - 1] + w_ppm;

	G_ppm = new unsigned char *[h_ppm];
	G_ppm[0] = new unsigned char[h_ppm * w_ppm];
	for (int i = 1; i < h_ppm; i++)
		G_ppm[i] = G_ppm[i - 1] + w_ppm;

	B_ppm = new unsigned char *[h_ppm];
	B_ppm[0] = new unsigned char[h_ppm * w_ppm];
	for (int i = 1; i < h_ppm; i++)
		B_ppm[i] = B_ppm[i - 1] + w_ppm;
}

void ppmStructure::readPPMBHead()
{
	if ((hpos_ppm = readPPMB_header(imageName.c_str(), &h_ppm, &w_ppm, &max_color_ppm)) <= 0) exit(1);
}

void ppmStructure::readPPMBData()
{
	if (readPPMB_data(R_ppm[0], G_ppm[0], B_ppm[0], imageName.c_str(), hpos_ppm, h_ppm, w_ppm, max_color_ppm) == 0) exit(1);
}

void ppmStructure::writePPMBImage(string outputFileName)
{
	if (writePPMB_image(outputFileName.c_str(), R_ppm[0], G_ppm[0], B_ppm[0], h_ppm, w_ppm, max_color_ppm) == 0) exit(1);
}

ppmStructure::ppmStructure(string imgName)
{
	imageName = imgName;
}


ppmStructure::~ppmStructure()
{
	delete[] R_ppm[0];
	delete[] R_ppm;

	delete[] G_ppm[0];
	delete[] G_ppm;

	delete[] B_ppm[0];
	delete[] B_ppm;
}

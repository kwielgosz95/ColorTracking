#pragma once
#include <string>
#include <iostream>
#include "TPGM.h"
using namespace std;

class ppmStructure
{
	
public:
	int h_ppm, w_ppm; // height, width rows / cols
	int max_color_ppm;
	int hpos_ppm;
	string imageName;
	unsigned char **R_ppm; 
	unsigned char **G_ppm; 
	unsigned char **B_ppm;

	void initRGBTable();
	void readPPMBHead();
	void readPPMBData();
	void writePPMBImage(string outputFileName);
	ppmStructure(string imageName);
	~ppmStructure();
};


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>
#include "TPGM.h"
#include "ppmStructure.h"

using namespace std;

int frameSize = 7;
int imagesCount = 557;

bool replace(std::string &str, const std::string &from, const std::string &to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}


//moveFrames ma rozmiar obrazka i zawiera siatke o wymiarach kwadracika frameSize x frameSize
void initMovementFrames(int width, int height, unsigned char **moveFrames) {
	int t = 0;

	for (int x = 0; x < width - 1; x++) {
		for (int y = 0; y < height - 1; y++) {
			if (x % frameSize == 0 || y % frameSize == 0) {
				moveFrames[x][y] = 1;
			}
			else {
				moveFrames[x][y] = 0;
			}
		}
	}
}

void drawFrames(int width, int height, unsigned char **R, unsigned char **G, unsigned char **B, unsigned char **frames) {
	for (int x = 0; x < width - frameSize; x++) {
		for (int y = 0; y < height - frameSize; y++) {
			if (frames[x][y] != 0) {
				for (int xx = x; xx < x + frameSize; xx++) {
					for (int yy = y; yy < y + frameSize; yy++) {
						if (xx % frameSize == 0 || yy % frameSize == 0) {
							R[xx][yy] = 0;
							G[xx][yy] = 0;
							B[xx][yy] = 255;
						}
					}
				}
			}
		}
	}
}

//Funkcja do nadania wartoœci kwadratowi framSize x framSize
void measureFramesFactor(int height, int width, unsigned char **R, unsigned char **G, unsigned char **B, unsigned int **frames) {
	unsigned int suma = 0;
	unsigned int suma_next = 0;
	// unsigned int *tab_suma = new unsigned int[(height - 10) * (width - 10) * 100];
	// unsigned int *tab_suma_next = new unsigned int[(height - 10) * (width - 10) * 100];
	int counter = 0;

	for (int x = 0; x < height - frameSize; x++) {
		for (int y = 0; y < width - frameSize; y++) {
			for (int i = x; i < x + frameSize; i++) {
				for (int k = y; k < y + frameSize; k++) {
					/*
					//diffValue = 28000
					//compareValue = 200
					suma += R[i][k];
					suma += G[i][k];
					suma += B[i][k];
					*/
					
					//diffValue = 
					//compareValue = 
					suma += R[i][k] + G[i][k] + B[i][k];
                     	
					//suma += (0.299*R[i][k]) + (0.587*G[i][k]) * (0.114*B[i][k]);
					
				}
			}


			frames[x][y] = suma;
			//	cout << "frames[x][y]: " << frames[x][y] << " || suma: " << suma << "\n";
			suma = 0;
		}
	}

}

//Funkcja do znalezienia podobnych kwadratów 
void compareMeasurements(int height, int width, unsigned int **first, unsigned int **second, unsigned char **moveFrames) {
	for (int x = 0; x < height - 1; x++) {
		for (int y = 0; y < width - 1; y++) {
			moveFrames[x][y] = 0;
		}
	}


	

	unsigned int diffxmin = 0;
	unsigned int diffymin = 0;
	unsigned int diffxmax = height;
	unsigned int diffymax = width;

	unsigned int searchScope = 40;

	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {

			unsigned int firstImageFrameValue = first[x][y];
			unsigned int secondImageFrameValue = second[x][y];
			unsigned int firstSecondDiff = 0;
			if (firstImageFrameValue > secondImageFrameValue) {
				firstSecondDiff = firstImageFrameValue - secondImageFrameValue;
			}
			else {
				firstSecondDiff = secondImageFrameValue - firstImageFrameValue;
			}
			
			
			//cout << firstSecondDiff << endl;
			unsigned int diffValue = 15000;
			
			if (firstSecondDiff > diffValue) { //Sprawdzenie czy ró¿nica kwadratu z pierwszego zdjecia i drugiego zdjecia jest znacz¹co du¿a (parametr diffValue)

				if (x > searchScope) {
					diffxmin = x - searchScope;
				}
				else {
					diffxmin = 0;
				}

				if (y > searchScope) {
					diffymin = y - searchScope;
				}
				else {
					diffymin = 0;
				}

				if ( (x + searchScope) < height) {
					diffxmax = x + searchScope;
				}
				else {
					diffxmax = height;
				}

				if ((y + searchScope) < width) {
					diffymax = x + searchScope;
				}
				else {
					diffymax = width;
				}

				for (int xx = diffxmin; xx < diffxmax; xx++) {
					

					for (int yy = diffymin; yy < diffymax; yy++) {

						if (firstImageFrameValue > second[xx][yy]) {
							firstSecondDiff = firstImageFrameValue - second[xx][yy];
						}
						else {
							firstSecondDiff = second[xx][yy] - firstImageFrameValue;
						}

						unsigned int compareValue = 2;

						if (firstSecondDiff < compareValue) {
							moveFrames[xx][yy] = 1;
							
						}

					}
				}
				


			}
		} //for y
	} //for x
}


int main(int argc, char **argv) {

	
	//Rysowanie przyk³adowej siatki na obrazku

	ppmStructure ppmStruct("001.ppm");
	ppmStruct.readPPMBHead();
	ppmStruct.initRGBTable();

	//init frames
	unsigned char **moveFrames1 = new unsigned char *[ppmStruct.h_ppm];
	moveFrames1[0] = new unsigned char[ppmStruct.h_ppm * ppmStruct.w_ppm];
	for (int i = 1; i < ppmStruct.h_ppm; i++)
		moveFrames1[i] = moveFrames1[i - 1] + ppmStruct.w_ppm;

	initMovementFrames(ppmStruct.h_ppm, ppmStruct.w_ppm, moveFrames1);

	ppmStruct.readPPMBData();

	drawFrames(ppmStruct.h_ppm, ppmStruct.w_ppm, ppmStruct.R_ppm, ppmStruct.G_ppm, ppmStruct.B_ppm, moveFrames1);

	std::string outfname_ppm = ppmStruct.imageName;
	replace(outfname_ppm, ".ppm", "_simple_with_frames.ppm");

	ppmStruct.writePPMBImage(outfname_ppm);

	delete[] moveFrames1[0];
	delete[] moveFrames1;

	//KONIEC rysowania siatki na obrazku

	cout << "END INIT - wcisnij enter" << endl;
	getchar();

	
	for (int currentImage = 1; currentImage < imagesCount; currentImage++) {
		///////////////////////////////PIERWSZY OBRAZEK
		int nextImage = currentImage + 1;
		string infname_ppm = "obr2_r\\" + std::to_string(currentImage) + ".ppm";

		ppmStructure ppmStructFirst(infname_ppm);
		cout << "\nOdczyt: " << infname_ppm;
		ppmStructFirst.readPPMBHead();
		cout << "Wymiary obrazka: height: " << ppmStructFirst.h_ppm << " | width: " << ppmStructFirst.w_ppm;
		ppmStructFirst.initRGBTable();

		//init frames
		unsigned char **moveFrames = new unsigned char *[ppmStructFirst.h_ppm];
		moveFrames[0] = new unsigned char[ppmStructFirst.h_ppm * ppmStructFirst.w_ppm];
		for (int i = 1; i < ppmStructFirst.h_ppm; i++)
			moveFrames[i] = moveFrames[i - 1] + ppmStructFirst.w_ppm;

		//Ustawianie siatki
		initMovementFrames(ppmStructFirst.h_ppm, ppmStructFirst.w_ppm, moveFrames);

		ppmStructFirst.readPPMBData();

		unsigned int **factorFramesFirstImage = new unsigned int *[ppmStructFirst.h_ppm];
		factorFramesFirstImage[0] = new unsigned int[ppmStructFirst.h_ppm * ppmStructFirst.w_ppm];
		for (int i = 1; i < ppmStructFirst.h_ppm; i++)
			factorFramesFirstImage[i] = factorFramesFirstImage[i - 1] + ppmStructFirst.w_ppm;

		//Obliczanie wartoœci dla ka¿ego kwadracika
		measureFramesFactor(ppmStructFirst.h_ppm, ppmStructFirst.w_ppm, ppmStructFirst.R_ppm, ppmStructFirst.G_ppm, ppmStructFirst.B_ppm, factorFramesFirstImage);

		////////////////////////////////DRUGI OBRAZEK ///////////////////////////////////////////////////////////////////////////

		std::string infname_ppm_next = "obr2_r\\" + std::to_string(nextImage) + ".ppm";
		ppmStructure ppmStructSecond(infname_ppm_next);
		cout << "\nOdczyt: " << infname_ppm_next;

		ppmStructSecond.readPPMBHead();
		ppmStructSecond.initRGBTable();

		ppmStructSecond.readPPMBData();

		unsigned int **factorFramesSecondImage = new unsigned int *[ppmStructSecond.h_ppm];
		factorFramesSecondImage[0] = new unsigned int[ppmStructSecond.h_ppm * ppmStructSecond.w_ppm];
		for (int i = 1; i < ppmStructSecond.h_ppm; i++)
			factorFramesSecondImage[i] = factorFramesSecondImage[i - 1] + ppmStructSecond.w_ppm;
		cout << "\nStart measureFramesFactor\n";

		//Obliczanie wartoœci dla ka¿ego kwadracika
		measureFramesFactor(ppmStructSecond.h_ppm, ppmStructSecond.w_ppm, ppmStructSecond.R_ppm, ppmStructSecond.G_ppm, ppmStructSecond.B_ppm, factorFramesSecondImage);

		cout << "Start compareMeasurements \n";
		//Porownywanie kwadracików z pierwszego i drugiego zdjêcia
		compareMeasurements(ppmStructSecond.h_ppm, ppmStructSecond.w_ppm, factorFramesFirstImage, factorFramesSecondImage, moveFrames);
		cout << "Start drawFrames \n";
		
		drawFrames(ppmStructSecond.h_ppm, ppmStructSecond.w_ppm, ppmStructSecond.R_ppm, ppmStructSecond.G_ppm, ppmStructSecond.B_ppm, moveFrames);

		std::string	outfname_ppm = "obr2_r-simplev1\\" + std::to_string(nextImage) + ".ppm";

		replace(outfname_ppm, ".ppm", "_done.ppm");
		cout << "Start writePPMB_image \n";
		ppmStructSecond.writePPMBImage(outfname_ppm);

		delete[] moveFrames[0];
		delete[] moveFrames;

		delete[] factorFramesFirstImage[0];
		delete[] factorFramesFirstImage;

		delete[] factorFramesSecondImage[0];
		delete[] factorFramesSecondImage;

		cout << "Koniec petli \n";
		//getchar();
	}

	cout << "koniec programu";
	getchar();

	return 0;
}
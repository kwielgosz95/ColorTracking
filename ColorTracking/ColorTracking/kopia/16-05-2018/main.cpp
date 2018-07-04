#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>
#include "TPGM.h"

using namespace std;

bool replace(std::string &str, const std::string &from, const std::string &to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}


int main(int argc, char **argv) {


	/*
	long long int suma = 0;
	int licznik = 0;
	for (int x = 0; x < 100 - 10; x++) {
		for (int y = 0; y < 30 - 10; y++) {

			for (int i = x; i < x + 10; i++) {

				for (int k = y; k < y + 10; k++) {
					licznik++;
				}

			}



		}
	}
	cout << licznik;
	getchar();

	*/
	/////PGM/////////////
	
	int h_pgm, w_pgm; // height, width
	int max_color_pgm;
	int hpos_pgm, i_pgm, j_pgm;

	std::string infname_pgm = "maly.pgm";

	if ((hpos_pgm = readPGMB_header(infname_pgm.c_str(), &h_pgm, &w_pgm, &max_color_pgm)) <= 0) exit(1);

	unsigned char **a_pgm = new unsigned char *[h_pgm];
	a_pgm[0] = new unsigned char[h_pgm * w_pgm];
	for (int i = 1; i < h_pgm; i++)
		a_pgm[i] = a_pgm[i - 1] + w_pgm;

	if (readPGMB_data(a_pgm[0], infname_pgm.c_str(), hpos_pgm, h_pgm, w_pgm, max_color_pgm) == 0) exit(1);

	std::string outfname_pgm = infname_pgm;
	replace(outfname_pgm, ".pgm", "_simple.pgm");

	if (writePGMB_image(outfname_pgm.c_str(), a_pgm[0], h_pgm, w_pgm, 255) == 0) exit(1);

	delete[] a_pgm[0];
	delete[] a_pgm;

	//// KONIEC PGM ////////////////////////////////////////

	//////////////PPM/////////////////////////////////////////////
	
	
	///PIERWSZY OBRAZEK

	int h_ppm, w_ppm; // height, width rows / cols
	int max_color_ppm;
	int hpos_ppm, i_ppm, j_ppm;

	std::string infname_ppm = "001.ppm";

	if ((hpos_ppm = readPPMB_header(infname_ppm.c_str(), &h_ppm, &w_ppm, &max_color_ppm)) <= 0) exit(1);

	unsigned char **R_ppm = new unsigned char *[h_ppm];
	R_ppm[0] = new unsigned char[h_ppm * w_ppm];
	for (int i = 1; i < h_ppm; i++)
		R_ppm[i] = R_ppm[i - 1] + w_ppm;

	unsigned char **G_ppm = new unsigned char *[h_ppm];
	G_ppm[0] = new unsigned char[h_ppm * w_ppm];
	for (int i = 1; i < h_ppm; i++)
		G_ppm[i] = G_ppm[i - 1] + w_ppm;

	unsigned char **B_ppm = new unsigned char *[h_ppm];
	B_ppm[0] = new unsigned char[h_ppm * w_ppm];
	for (int i = 1; i < h_ppm; i++)
		B_ppm[i] = B_ppm[i - 1] + w_ppm;

	if (readPPMB_data(R_ppm[0], G_ppm[0], B_ppm[0], infname_ppm.c_str(), hpos_ppm, h_ppm, w_ppm, max_color_ppm) == 0) exit(1);

	////////////////////////////////DRUGI OBRAZEK
	int h_ppm_next, w_ppm_next; // height, width rows / cols
	int max_color_ppm_next;
	int hpos_ppm_next, i_ppm_next, j_ppm_next;

	std::string infname_ppm_next = "002.ppm";

	if ((hpos_ppm_next = readPPMB_header(infname_ppm_next.c_str(), &h_ppm_next, &w_ppm_next, &max_color_ppm_next)) <= 0) exit(1);

	unsigned char **R_ppm_next = new unsigned char *[h_ppm_next];
	R_ppm_next[0] = new unsigned char[h_ppm_next * w_ppm_next];
	for (int i = 1; i < h_ppm_next; i++)
		R_ppm_next[i] = R_ppm_next[i - 1] + w_ppm_next;

	unsigned char **G_ppm_next = new unsigned char *[h_ppm_next];
	G_ppm_next[0] = new unsigned char[h_ppm_next * w_ppm_next];
	for (int i = 1; i < h_ppm_next; i++)
		G_ppm_next[i] = G_ppm_next[i - 1] + w_ppm_next;

	unsigned char **B_ppm_next = new unsigned char *[h_ppm_next];
	B_ppm_next[0] = new unsigned char[h_ppm_next * w_ppm_next];
	for (int i = 1; i < h_ppm_next; i++)
		B_ppm_next[i] = B_ppm_next[i - 1] + w_ppm_next;

	if (readPPMB_data(R_ppm_next[0], G_ppm_next[0], B_ppm_next[0], infname_ppm_next.c_str(), hpos_ppm_next, h_ppm_next, w_ppm_next, max_color_ppm_next) == 0) exit(1);


	//KWADRATY 10x10

	unsigned int suma = 0;
	unsigned int suma_next = 0;
	unsigned int *tab_suma = new unsigned int [(h_ppm - 10)*(w_ppm - 10)*100];
	unsigned int *tab_suma_next = new unsigned int[(h_ppm - 10)*(w_ppm - 10) * 100];



	int counter = 0;
	for (int x = 0; x < h_ppm - 10; x++) {
		for (int y = 0; y < w_ppm - 10; y++) {



			for (int i = x; i < x + 10; i++) {
				for (int k = y; k < y + 10; k++) {
					suma += R_ppm[i][k];
					suma += G_ppm[i][k];
					suma += B_ppm[i][k];

					suma_next += R_ppm_next[i][k];
					suma_next += G_ppm_next[i][k];
					suma_next += B_ppm_next[i][k];
					
				}
			}
		
			tab_suma[counter] = suma;
			tab_suma_next[counter++] = suma_next;

			//if (x == 0 && y < 100) {
			//	cout << "y = " << y<< endl;
				cout << tab_suma[y] << endl;
				cout << suma << endl;
		//	}
			suma = 0;
			suma_next = 0;

			
		}
	}
	


	std::fstream plik;
	plik.open("roznica.txt", std::ios::in | std::ios::out);
	if (plik.good() == true)
	{
		for (int i = 0; i < (h_ppm - 10)*(w_ppm - 10) * 100; i++) {
			plik << tab_suma[i] << " ; " << tab_suma_next[i] << " ; ";
			if (tab_suma[i] > tab_suma_next[i]) {
				plik << tab_suma[i] - tab_suma_next[i] << endl;
			}
			else {
				plik << "-" << tab_suma_next[i] - tab_suma[i] << endl;
			}
		}


		plik.close();
	}





	std::string outfname_ppm = infname_ppm;
	replace(outfname_ppm, ".ppm", "_simple.ppm");

	if (writePPMB_image(outfname_ppm.c_str(), R_ppm[0], G_ppm[0], B_ppm[0], h_ppm, w_ppm, max_color_ppm) == 0) exit(1);

	delete[] R_ppm[0];
	delete[] R_ppm;
	
	delete[] G_ppm[0];
	delete[] G_ppm;

	delete[] B_ppm[0];
	delete[] B_ppm;


	delete[] R_ppm_next[0];
	delete[] R_ppm_next;

	delete[] G_ppm_next[0];
	delete[] G_ppm_next;

	delete[] B_ppm_next[0];
	delete[] B_ppm_next;
	cout << "koniec programu";
	getchar();

	return 0;
}
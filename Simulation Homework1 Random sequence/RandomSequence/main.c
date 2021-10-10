#pragma once
#include "UD.h"
#include "GD.h"
#include "BPSK.h"
#include "FN.h"
#include <stdio.h>



int main()
{
	UDS2txt(10000);
	USGRS2txt(10000);
	BMGRS2txt(10000);
	PMGRS2txt(10000);
	Rayleigh_RS2txt(10000);
	float ber;
	FILE* fp;//ÎÄ¼þÖ¸Õë
	fp = fopen(".\\data\\ber.txt", "w");
	for (int SNB_dB = -3; SNB_dB < 13; SNB_dB++) {
	       ber = BPSK_main(10000,SNB_dB);
		fprintf(fp, "%f\n", ber);
	}
	AutoCorrelation_Y(1000);
}

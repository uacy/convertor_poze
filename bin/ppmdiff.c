#include <stdio.h>
#include <string.h>

int abs(int x) {
	return x > 0 ? x : -x;
}

int main(int argc, char **argv)
{
	if(argc < 3) {
		return -1;
	}
	FILE *f1,*f2;
	f1 = fopen(argv[1],"rt");
	f2 = fopen(argv[2],"rt");
	if(f1 == NULL) {
		printf("File %s does not exists.\n",argv[1]);
		return -2;
	} else if(f2 == NULL) {
		printf("File %s does not exists.\n",argv[2]);
		return -2;
	}
	int channels;
	char header[10];
	int sizeX1, sizeY1, sizeX2, sizeY2;
	int depth1, depth2;
	int pixel1, pixel2, i;

	if(strcmp(argv[1] + strlen(argv[1])-3,"ppm") == 0)
		channels = 3;
	else
		channels = 1;

	//drop header
	fscanf(f1,"%s",header);
	fscanf(f2,"%s",header);

	fscanf(f1,"%d %d %d",&sizeX1,&sizeY1,&depth1);
	fscanf(f2,"%d %d %d",&sizeX2,&sizeY2,&depth2);
	if(depth1 != depth2 || sizeX1 != sizeX2 || sizeY1 != sizeY2) {
		printf("Sizes do not match.\n");
		return -3;
	}
	for(i=0; i<sizeX1*sizeY1*channels; i++) {
		fscanf(f1,"%d",&pixel1);
		fscanf(f2,"%d",&pixel2);
		if(abs(pixel1 - pixel2) > 4) {
			printf("Images differ.\n");
			return -4;
		}
	}
	return 0;
}

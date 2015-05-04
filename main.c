//312CB_Untesu_Albert_Cristian_Tema2
#include "bmp_helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 512


void convert_bmp_to_pgm(char nume1[N], char nume2[N]){
	int i,j, s=0;
	FILEHEADER H1;
	INFOHEADER H2;
	unsigned char **a;
	FILE *f, *sf;

	f = fopen(nume1,"rb");
//se citeste imaginea bmp cu ajutorul structurilor
	fread(&H1,sizeof(FILEHEADER),1,f);
	fread(&H2,sizeof(INFOHEADER),1,f);
//se aloca dinamic matricea a care contine pixelii
	a = malloc(H2.height*sizeof(unsigned char *));
	for (i = 0;i < H2.height;++i)
		a[i]=malloc(3*H2.width);
//se citeste valoarea fiecarui pixel si se stocheaza in matricea a
	for (i = 0;i<H2.height;++i)
		fread(a[i],3*H2.width,1,f);
	fclose(f);
	sf = fopen(nume2,"w");
//se trece peste primele 3 randuri care au date despre poza
	fprintf(sf,"P2\n");
	fprintf(sf,"%d %d\n",H2.width,H2.height);
	fprintf(sf,"255\n");
//se scrie valoarea fiecarui pixel in poza converita
	for (i = H2.height-1;i >= 0;--i)
		for (j = 0;j < H2.width;++j)
		{
//se transforma in int valorile matricei pentru a se putea face media aritmetica
//dintre pixeli si sa pun in noua poza
			s = (int)a[i][3*j]+(int)a[i][3*j+1]+(int)a[i][3*j+2];
			fprintf(sf,"%d ",s/3);
		}
	fclose(sf);
}

void convert_bmp_to_ppm(char nume1[N], char nume2[N]){
	int i,j;
	FILEHEADER H1;
	INFOHEADER H2;
	unsigned char **a;
	FILE *f, *sf;

	f = fopen(nume1,"rb");
//se citeste imaginea bmp cu ajutorul structurilor
	fread(&H1,sizeof(FILEHEADER),1,f);
	fread(&H2,sizeof(INFOHEADER),1,f);
//se aloca dinamic matricea a care contine pixelii
	a = malloc(H2.height*sizeof(unsigned char *));
	for (i = 0;i<H2.height;++i)
		a[i]=malloc(3*H2.width);
//se citeste valoarea fiecarui pixel si se stocheaza in matricea a
	for (i = 0;i<H2.height;++i)
		fread(a[i],3*H2.width,1,f);
	fclose(f);
	sf = fopen(nume2,"w");
//se trece peste primele 3 randuri care au date despre poza
	fprintf(sf,"P3\n");
	fprintf(sf,"%d %d\n",H2.width,H2.height);
	fprintf(sf,"255\n");
//se scrie valoarea fiecarui pixel in poza converita (3 cate 3)
	for (i = H2.height-1;i >= 0;--i)
		for (j = 0;j < H2.width;++j)
			fprintf(sf,"%d %d %d ",a[i][3*j+2],a[i][3*j+1],a[i][3*j]);
	fclose(sf);
}

void convert_ppm_to_pgm(char nume1[N], char nume2[N]){
	int i, j, w, h, nr, s=0;
	FILE *f, *sf;
	char sir[N];
	int **a;

	f = fopen(nume1, "r");
//se citeste in gol pt a ajunge la linia 4 unde incepe scrierea pixelilor
	fgets(sir,N,f);
	fscanf(f,"%d %d", &w, &h);
	fgets(sir,N,f);
	fscanf(f, "%d", &nr);
	fgets(sir, N, f);

//se aloca dinamic matricea a care contine valoarea fiecarui pixel
	a = (int **) malloc(h * sizeof(int *));
	for (i = 0; i < h; ++i) {
		a[i] = (int *) malloc(3 * w * sizeof(int));
	}
//se citeste valoarea fiecarui pixel si se stocheaza in matricea a
	for (i = 0; i < h; ++i) {
		for (j = 0; j < 3 * w; ++j) {
			fscanf(f, "%d", &a[i][j]);
		}
	}
	fclose(f);
	sf = fopen(nume2, "w");
//se trece peste primele 3 randuri care au date despre poza
	fprintf(sf,"P2\n");
	fprintf(sf,"%d %d\n",w,h);
	fprintf(sf,"255\n");
// sa face conversia din ppm in pgm imaprtinduse cate 3 pixeli la 3 rezultand unul
	for (i = 0;i < h;i++){		
		for (j = 0;j < 3*w;j += 3){
			s=(a[i][j]+a[i][j+1]+a[i][j+2])/3;
			fprintf(sf,"%d ", s);
		}
		fprintf(sf,"\n");
	}
	fclose(sf);
}

void blur_ppm(char nume1[N]){
	int i, j, sum=0, nr=0, w, h, gl, z;
	FILE *f, *sf;
	char sir[N];
	int **a, **b;

	f = fopen(nume1, "r");
//se citeste in gol pt a ajunge la linia 4 unde incepe scrierea pixelilor
	fgets(sir,N,f);
	fscanf(f,"%d %d", &w, &h);
	fgets(sir,N,f);
	fscanf(f, "%d", &gl);
	fgets(sir, N, f);
//se aloca dinamic matricile a si b care vor ajuta la blur-area imaginii
	a = (int **) malloc(h * sizeof(int *));
	b = (int **) malloc(h * sizeof(int *));
	for (i = 0; i < h; ++i) {
		a[i] = (int *) malloc(3 * w * sizeof(int));
		b[i] = (int *) malloc(3 * w * sizeof(int));
	}
//mai intai se stocheaza in matricea a valoarea pixelilor initiali
	for (i = 0; i < h; ++i){
		for (j = 0; j < 3 * w; ++j){
			fscanf(f, "%d", &a[i][j]);
		}
	}
	fclose(f);

	sf = fopen("santa_blur.ppm", "w");
//se trece peste primele 3 randuri care au date despre poza
	fprintf(sf,"P3\n");
	fprintf(sf,"%d %d\n", w, h);
	fprintf(sf,"255\n");
//se face de 10 ori blur-area
	for (z = 0; z < 10; ++z){
		for (i = 0;i < h;++i){
//sa facea blur-area + cazurile speciale din margini unde pixelii nu au 4 vecini
//si se salveaza in matricea b
			for (j = 0;j < 3 * w;++j){
				nr = 0; sum = 0;
				if(i-1 >= 0){
					sum += a[i-1][j];
					++nr;
				}
				if(i+1 < h){	
					sum +=a [i+1][j];
					++nr;
				}
				if(j-3 >= 0){
					sum += a[i][j-3];
					++nr;
				}
				if(j+3 < 3 * w){
					sum += a[i][j+3];
					++nr;
				}
				b[i][j]=sum/nr;
			}
		}
//se face schimbarea intre matricile a si b pentru a relua procesul de 
//blur-are de 10 ori 	
		for (i = 0; i < h; ++i)
			for (j = 0; j < 3 * w; ++j)
				a[i][j] = b[i][j];
	}
//se scrie valoarea finala a pozei blur-ate de 10 ori
	for (i = 0; i < h; ++i){
		for(j = 0; j < 3 * w; ++j)
			fprintf(sf,"%d ", a[i][j]);
		fprintf(sf,"\n");
	}

	fclose(sf);
}

void blur_pgm(char nume1[N]){
	int i, j, sum=0, nr=0, w, h, gl, z;
	FILE *f, *sf;
	char sir[N];
	int **a, **b;

	f = fopen(nume1, "r");
//se citeste in gol pt a ajunge la linia 4 unde incepe scrierea pixelilor
	fgets(sir,N,f);
	fscanf(f,"%d %d", &w, &h);
	fgets(sir,N,f);
	fscanf(f, "%d", &gl);
	fgets(sir, N, f);
//se aloca dinamic matricile a si b care vor ajuta la blur-area imaginii
	a = (int **) malloc(h * sizeof(int *));
	b = (int **) malloc(h * sizeof(int *));
	for (i = 0; i < h; ++i) {
		a[i] = (int *) malloc(w * sizeof(int));
		b[i] = (int *) malloc(w * sizeof(int));
	}
//mai intai se stocheaza in matricea a valoarea pixelilor initiali
	for (i = 0; i < h; ++i) {
		for (j = 0; j <  w; ++j) {
			fscanf(f, "%d", &a[i][j]);
		}
	}

	fclose(f);

	sf = fopen("santa_blur.pgm", "w");
//se trece peste primele 3 randuri care au date despre poza
	fprintf(sf,"P2\n");
	fprintf(sf,"%d %d\n",w,h);
	fprintf(sf,"255\n");
//se face de 10 ori blur-area
	for (z = 0; z < 10; ++z){
		for (i = 0;i < h;i++){
//sa facea blur-area + cazurile speciale din margini unde pixelii nu au 4 vecini
//si se salveaza in matricea b
			for (j = 0;j < w;j++){
				nr = 0; sum = 0;
				if(i-1 >= 0){
					sum += a[i-1][j];
					++nr;
				}
				if(i+1 < h){
					sum += a[i+1][j];	
					++nr;
				}
				if(j-1 >= 0){
					sum +=a [i][j-1];
					++nr;
				}
				if(j+1 < w){
					sum += a[i][j+1];
					++nr;
				}
				b[i][j]=sum/nr;
			}
		}
//se face schimbarea intre matricile a si b pentru a relua procesul de 
//blur-are de 10 ori 
		for (i = 0; i < h; ++i)
			for (j = 0; j < w; ++j)
				a[i][j] = b[i][j];
	}
//se scrie valoarea finala a pozei blur-ate de 10 ori
	for (i = 0; i < h; ++i){
		for(j = 0; j <  w; ++j)
			fprintf(sf,"%d ", a[i][j]);
		fprintf(sf,"\n");
	}

	fclose(sf);
}

void crop_ppm(int x1, int x2, int y1, int y2, char nume1[N]){
	int i, j, w, h, nr;
	FILE *f, *sf;
	char sir[N];
	int **a;

	f = fopen(nume1, "r");
//se citeste in gol pt a ajunge la linia 4 unde incepe scrierea pixelilor
	fgets(sir,N,f);
	fscanf(f,"%d %d", &w, &h);
	fgets(sir,N,f);
	fscanf(f, "%d", &nr);
	fgets(sir, N, f);

//se aloca dinamic matricea a care contine valoarea fiecarui pixel
	a = (int **) malloc(h * sizeof(int *));
	for (i = 0; i < h; ++i) {
		a[i] = (int *) malloc(3 * w * sizeof(int));
	}
//se citeste valoarea fiecarui pixel si se stocheaza in matricea a
	for (i = 0; i < h; ++i) {
		for (j = 0; j < 3 * w; ++j) {
			fscanf(f, "%d", &a[i][j]);
		}
	}

	fclose(f);
	sf = fopen("santa_crop.ppm", "w");
//se trece peste primele 3 randuri care au date despre poza
	fprintf(sf,"P3\n");
	fprintf(sf,"%d %d\n", x2-x1+1,y2-y1+1);
	fprintf(sf,"255\n");

//se scrie valoarea fiecarui pixel in poza crop-ata cu coordonatele date
	for(i=h-y2-1;i<h;i++){
		for(j=x1;j<=3*x2;j += 3){
			fprintf(sf,"%d %d %d ", a[i][j], a[i][j+1], a[i][j+2]);
		}
		fprintf(sf,"\n");
	}
	fclose(sf);
}

void crop_pgm(int x1, int x2, int y1, int y2, char nume1[N]){
	int i, j, w, h, nr;
	FILE *f, *sf;
	char sir[N];
	int **a;

	f = fopen(nume1, "r");
//se citeste in gol pt a ajunge la linia 4 unde incepe scrierea pixelilor
	fgets(sir,N,f);
	fscanf(f,"%d %d", &w, &h);
	fgets(sir,N,f);
	fscanf(f, "%d", &nr);
	fgets(sir, N, f);

//se aloca dinamic matricea a care contine valoarea fiecarui pixel
	a = (int **) malloc(h * sizeof(int *));
	for (i = 0; i < h; ++i) {
		a[i] = (int *) malloc( w * sizeof(int));
	}
//se citeste valoarea fiecarui pixel si se stocheaza in matricea a
	for (i = 0; i < h; ++i) {
		for (j = 0; j < w; ++j) {
			fscanf(f, "%d", &a[i][j]);
		}
	}

	fclose(f);
	sf = fopen("santa_crop.pgm", "w");
//se trece peste primele 3 randuri care au date despre poza
	fprintf(sf,"P2\n");
	fprintf(sf,"%d %d\n", x2-x1+1, y2-y1+1);
	fprintf(sf,"255\n");

//se scrie valoarea fiecarui pixel in poza crop-ata cu coordonatele date
	for(i = h-y2-1;i < h;++i){
		for(j = x1;j <= x2;++j){
			fprintf(sf,"%d ", a[i][j]);
		}
		fprintf(sf,"\n");
	}
	fclose(sf);
}

int main(){
	char comanda[N], nume1[N], nume2[N];
	int x1, x2, y1, y2;
//se citeste comanzi de la tastatura pana la comanda exit 
	scanf("%s",comanda);
	while(strcmp(comanda,"exit")){
		
		if(!strcmp(comanda,"convert")){
			scanf("%s%s", nume1, nume2);
			if(!strcmp(nume2,"santa.pgm")){
				convert_bmp_to_pgm(nume1,nume2);
			}else if(!strcmp(nume2,"santa.ppm")){
				convert_bmp_to_ppm(nume1,nume2);
			}else if(!strcmp(nume2,"santa_gray.pgm")){
				convert_ppm_to_pgm(nume1,nume2);
			}
		}
		if(!strcmp(comanda,"blur")){
			scanf("%s",nume1);
			if(!strcmp(nume1,"santa.pgm")){
				blur_pgm(nume1);
			}else if(!strcmp(nume1,"santa.ppm")){
				blur_ppm(nume1);
			}
		}
		if(!strcmp(comanda,"crop")){
			scanf("%s%d%d%d%d",nume1, &x1, &y1, &x2, &y2);
			if(!strcmp(nume1,"santa.pgm")){
				crop_pgm(x1, x2, y1, y2, nume1);
			}else if(!strcmp(nume1,"santa.ppm")){
				crop_ppm(x1, x2, y1, y2, nume1);
			}		
		}
		scanf("%s",comanda);
		
	}

	return 0;
}

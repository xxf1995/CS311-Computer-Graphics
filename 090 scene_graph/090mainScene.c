//Xingfan Xia Jan 14th
//clang 090mainScene.c 000pixel.o -lglfw -framework OpenGL; ./a.out
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include "000pixel.h"
#include "090matrix.c"
#include "070vector.c"
#include "040texture.c"
#include "090renderer.c"


#define renVARYDIMBOUND 16
#define renVERTNUMBOUND 16
#define renATTRX 0
#define renATTRY 1
#define renATTRS 2
#define renATTRT 3
#define renATTRR 4
#define renATTRG 5
#define renATTRB 6

#define renVARYX 0
#define renVARYY 1
#define renVARYS 2
#define renVARYT 3
#define renVARYR 4
#define renVARYG 5
#define renVARYB 6

#define renUNIFR 0
#define renUNIFG 1
#define renUNIFB 2
#define renUNIFTHETA 3
#define renUNIFTRANSX 4
#define renUNIFTRANSY 5
#define renUNIFISOMETRY 6

#define renTEXR 0
#define renTEXG 1
#define renTEXB 2

//first [0, 1, 2] background rgb, [3] angle theta, [4,5] translation vector
double unif[3+3+9] = {1.0, 1.0, 1.0, 45.0, 10.0, 10.0};

/* Sets rgb, based on the other parameters, which are unaltered. attr is an 
interpolated attribute vector. */
void colorPixel(renRenderer *ren, double unif[], texTexture *tex[], 
        double vary[], double rgb[]) {
    texSample(tex[0], vary[renVARYS], vary[renVARYT]);
    rgb[0] = tex[0]->sample[renTEXR] * unif[renUNIFR];
    rgb[1] = tex[0]->sample[renTEXG] * unif[renUNIFG];
    rgb[2] = tex[0]->sample[renTEXB] * unif[renUNIFB];
}

// void rotateMatrix(double angle, double matrix[2][2]) {
// 	double rad = M_PI/180.0 * angle;
// 	matrix[0][0] = cos(rad);
// 	matrix[0][1] = -sin(rad);
// 	matrix[1][0] = sin(rad);
// 	matrix[1][1] = cos(rad);
// }

/* Writes the vary vector, based on the other parameters. */
void transformVertex(renRenderer *ren, double unif[], double attr[], 
        double vary[]) {
    /* For now, just copy attr to varying. Baby steps. */
 //    double angle = 45.0;
 //    double x, y  = 10.0, 10.0;

 //   	double isom[3][3];
	// mat33Isometry(a, x, y, isom);
	mat33Isometry(unif[renUNIFTHETA], unif[renUNIFTRANSX], 
		unif[renUNIFTRANSY], (double(*)[3])(&unif[renUNIFISOMETRY]));
	double original[3] = {attr[renATTRX], attr[renATTRY], 1};

    mat331Multiply((double(*)[3])(&unif[renUNIFISOMETRY]), original, vary);
    // vary[renVARYX] = attr[renATTRX];
    // vary[renVARYY] = attr[renATTRY];
    vary[renVARYS] = attr[renATTRS];
    vary[renVARYT] = attr[renATTRT];
}

/* If unifParent is NULL, then sets the uniform matrix to the 
rotation-translation M described by the other uniforms. If unifParent is not 
NULL, but instead contains a rotation-translation P, then sets the uniform 
matrix to the matrix product P * M. */
void updateUniform(renRenderer *ren, double unif[], double unifParent[]) {
    if (unifParent == NULL)
        /* The nine uniforms for storing the matrix start at index 
        renUNIFISOMETRY. So &unif[renUNIFISOMETRY] is an array containing those 
        nine numbers. We use '(double(*)[3])' to cast it to a 3x3 matrix. */
        mat33Isometry(unif[renUNIFTHETA], unif[renUNIFTRANSX], 
            unif[renUNIFTRANSY], (double(*)[3])(&unif[renUNIFISOMETRY]));
    else {
        double m[3][3];
        mat33Isometry(unif[renUNIFTHETA], unif[renUNIFTRANSX], 
            unif[renUNIFTRANSY], m);
        mat333Multiply((double(*)[3])(&unifParent[renUNIFISOMETRY]), m, 
            (double(*)[3])(&unif[renUNIFISOMETRY]));
    }
}

#include "090triangle.c"
#include "090mesh.c"
texTexture texture;
texTexture *tex_0;
meshMesh mesh_1;
meshMesh *mesh;
renRenderer renderer = {
	.unifDim = 3,
	.texNum = 2,
	.varyDim = 4,
	.transformVertex = transformVertex,
	.colorPixel = colorPixel 
};



int main(void) {
	if (pixInitialize(512, 512, "Pixel Graphics") != 0)
		return 1;
	else {
		renRenderer *ren = &renderer;
		mesh = &mesh_1;
		// meshInitializeRectangle(mesh, 200, 300, 200, 300);
		meshInitializeEllipse(mesh, 300, 300, 100, 100, 30);
		
		tex_0 = &texture;
		if (texInitializeFile(tex_0, "avatar.jpg") != 0) {
			return 1;
		} else {
			pixClearRGB(0.0, 0.0, 0.0);
			texTexture *tex[renVARYDIMBOUND];
			tex_0->filtering = texQUADRATIC;
			tex[0] = tex_0;
			meshRender(mesh, ren, unif, tex);
			pixRun();
			texDestroy(tex[0]);
			meshDestroy(mesh);
			return 0;
		}
	}	
}
//Xingfan Xia, January 12th, With the help from Yanhan Lyu for teaching
//me the classes I have missed for starting this class in the middle of second week


//To Generate Color at vector x by applying formulae learnt in class
void getSTcoordinates(double x[2], double a[2], double b[2], double c[2], double rgb[3],
		double alpha[2], double beta[2], double gamma[2], double coordinates[2]) {

	double m[2][2] = {
		{b[0]-a[0], c[0]-a[0]},
		{b[1]-a[1], c[1]-a[1]}
	};
	double Inv[2][2] = {
		{0.0,0.0},
		{0.0,0.0}
	};	
	double det = mat22Invert(m,Inv);
	double vec[2] = {x[0]-a[0], x[1]-a[1]};
	double pq[2] = {0.0, 0.0};
	mat221Multiply(Inv,vec,pq);
	if (det != 0) {
		coordinates[0] = alpha[0] + pq[0]*(beta[0]-alpha[0])+pq[1]*(gamma[0]-alpha[0]);
		coordinates[1] = alpha[1] + pq[0]*(beta[1]-alpha[1])+pq[1]*(gamma[1]-alpha[1]);
	} else {
		printf("The matrix doesn't have an Inverse, something is wrong here\n");
	}
}

/* triRenderAleft rasterizes a triangle whose vertices are given in 
a counter-clockwise order and with each pixel's color interpolated 
using the formulae we learnt in class.*/
void triRenderALeft(double a[2], double b[2], double c[2], double rgb[3], texTexture *tex, 
		double alpha[2], double beta[2], double gamma[2]) {
	
	double STvalue[2];
	double *sampleRGB;
	double x[2];
	//c[0]<b[0], so it is an Acute Triangle/Right Triangle, Angle(abc)<=90
	if (c[0] <= b[0]){ 

		//A and C on the same y-axis
		if (a[0] == c[0]){ 
			/* Some triangle
			C

						B
			A            
			*/
			/* The left bound is (int)ceil(a[0]) and the right bound is (int)floor(b[0])*/
			for (x[0]=(int)ceil(a[0]); x[0]<=(int)floor(b[0]); x[0]++){
				int x1_low;
				int x1_high;
				/*The lower bound is ac and the higher bound is bc*/
				x1_low = a[1]+(b[1]-a[1])/(b[0]-a[0])*(x[0]-a[0]);
				x1_high = c[1]+(b[1]-c[1])/(b[0]-c[0])*(x[0]-c[0]);
				for (x[1]=(int)ceil(x1_low); x[1]<=(int)floor(x1_high); x[1]++){
					getSTcoordinates(x, a, b, c, rgb, alpha, beta, gamma, STvalue);
					texSample(tex, STvalue[0], STvalue[1]);
					sampleRGB = tex->sample;
					sampleRGB[0] *= rgb[0];
					sampleRGB[1] *= rgb[1];
					sampleRGB[2] *= rgb[2];
					pixSetRGB(x[0], x[1], sampleRGB[0], sampleRGB[1], sampleRGB[2]);
				}
			}
		/*case2: B and C on the same y-axis*/
		} else if (c[0] == b[0]){
			/* Some triangle
						 C

		
						 B
			A            
			*/			
			for (x[0]=(int)ceil(a[0]); x[0]<=(int)floor(b[0]); x[0]++){
				int x1_low;
				int x1_high;
				x1_low = a[1]+(b[1]-a[1])/(b[0]-a[0])*(x[0]-a[0]);
				x1_high = a[1]+(c[1]-a[1])/(c[0]-a[0])*(x[0]-a[0]);
				for (x[1]=(int)ceil(x1_low); x[1]<=(int)floor(x1_high); x[1]++){
					getSTcoordinates(x, a, b, c, rgb, alpha, beta, gamma, STvalue);
					texSample(tex, STvalue[0], STvalue[1]);
					sampleRGB = tex->sample;
					sampleRGB[0] *= rgb[0];
					sampleRGB[1] *= rgb[1];
					sampleRGB[2] *= rgb[2];
					pixSetRGB(x[0], x[1], sampleRGB[0], sampleRGB[1], sampleRGB[2]);
				}
			}
		/*case3: B in the middle of A and B in terms of x-coordinates*/
		} else {
			/* Some triangle
				  C

		
						 B
			A            
			*/	
			for (x[0]=(int)ceil(a[0]); x[0]<=(int)floor(c[0]); x[0]++){
				//Left sub-Triangle of Triangle ABC
				int x1_low;
				int x1_high;
				x1_low = a[1]+(b[1]-a[1])/(b[0]-a[0])*(x[0]-a[0]);
				x1_high = a[1]+(c[1]-a[1])/(c[0]-a[0])*(x[0]-a[0]);
				for (x[1]=(int)ceil(x1_low); x[1]<=(int)floor(x1_high); x[1]++){
					getSTcoordinates(x, a, b, c, rgb, alpha, beta, gamma, STvalue);
					texSample(tex, STvalue[0], STvalue[1]);
					sampleRGB = tex->sample;
					sampleRGB[0] *= rgb[0];
					sampleRGB[1] *= rgb[1];
					sampleRGB[2] *= rgb[2];
					pixSetRGB(x[0], x[1], sampleRGB[0], sampleRGB[1], sampleRGB[2]);
				}
			}
			for (x[0]=(int)floor(c[0])+1; x[0]<=(int)floor(b[0]); x[0]++){
				//Right sub-Triangle of Triangle ABC
				int x1_low;
				int x1_high;
				x1_low = a[1]+(b[1]-a[1])/(b[0]-a[0])*(x[0]-a[0]);
				x1_high = c[1]+(b[1]-c[1])/(b[0]-c[0])*(x[0]-c[0]);
				for (x[1]=(int)ceil(x1_low); x[1]<=(int)floor(x1_high); x[1]++){	
					getSTcoordinates(x, a, b, c, rgb, alpha, beta, gamma, STvalue);
					texSample(tex, STvalue[0], STvalue[1]);
					sampleRGB = tex->sample;
					sampleRGB[0] *= rgb[0];
					sampleRGB[1] *= rgb[1];
					sampleRGB[2] *= rgb[2];
					pixSetRGB(x[0], x[1], sampleRGB[0], sampleRGB[1], sampleRGB[2]);
				}
			}
		}
	/* c[0] > b[0], Obtuse triangles. 90<Angle(abc)*/
	} else {
		for (x[0]=(int)ceil(a[0]); x[0]<=(int)floor(b[0]); x[0]++){
			//Left sub-Triangle of Triangle ABC
			int x1_low;
			int x1_high;
			x1_low = a[1]+(b[1]-a[1])/(b[0]-a[0])*(x[0]-a[0]);
			x1_high = a[1]+(c[1]-a[1])/(c[0]-a[0])*(x[0]-a[0]);
			for (x[1]=(int)ceil(x1_low); x[1]<=(int)floor(x1_high); x[1]++){
				getSTcoordinates(x, a, b, c, rgb, alpha, beta, gamma, STvalue);
				texSample(tex, STvalue[0], STvalue[1]);
				sampleRGB = tex->sample;
				sampleRGB[0] *= rgb[0];
				sampleRGB[1] *= rgb[1];
				sampleRGB[2] *= rgb[2];
				pixSetRGB(x[0], x[1], sampleRGB[0], sampleRGB[1], sampleRGB[2]);
			}
		}
		for (x[0]=(int)floor(b[0])+1; x[0]<=(int)floor(c[0]); x[0]++){
			//Right sub-Triangle of Triangle ABC
			int x1_low;
			int x1_high;
			x1_low  = b[1]+(c[1]-b[1])/(c[0]-b[0])*(x[0]-b[0]);
			x1_high = a[1]+(c[1]-a[1])/(c[0]-a[0])*(x[0]-a[0]);
			for (x[1]=(int)ceil(x1_low); x[1]<=(int)floor(x1_high); x[1]++){	
				getSTcoordinates(x, a, b, c, rgb, alpha, beta, gamma, STvalue);
				texSample(tex, STvalue[0], STvalue[1]);
				sampleRGB = tex->sample;
				sampleRGB[0] *= rgb[0];
				sampleRGB[1] *= rgb[1];
				sampleRGB[2] *= rgb[2];
				pixSetRGB(x[0], x[1], sampleRGB[0], sampleRGB[1], sampleRGB[2]);
			}

		}
		
	}
}	

/*triRender is a dummy functio that calls the triRenderAleft which
is the actual method that does the drawing and pass the vertices in
correct order*/
void triRender(double a[2], double b[2], double c[2], double rgb[3], texTexture *tex,
		double alpha[3], double beta[3], double gamma[3]) { 
	if (a[0] < b[0] && a[0] < c[0]) {
		triRenderALeft(a, b, c, rgb, tex, alpha, beta, gamma);
	} else if (b[0] < a[0] && b[0] < c[0]) {
		triRenderALeft(b, c, a, rgb, tex, alpha, beta, gamma);
	} else if (c[0] < a[0] && c[0] < b[0]) {
		triRenderALeft(c, a, b, rgb, tex, alpha, beta, gamma);
	}
}
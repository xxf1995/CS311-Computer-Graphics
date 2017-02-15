//Xingfan Xia, Feb 2nd
/*** 2 x 2 Matrices ***/

//Build identity matrix
void mat33Identity(GLdouble m[3][3]) {
	for (int i = 0; i < 3; i++) {
  		for (int j = 0; j < 3; j++) {
  			if (i == j) {
  				m[i][j] = 1;
  			} else {
  				m[i][j] = 0;
  			}
  		}
  	}
}

void mat44Identity(GLdouble m[4][4]) {
	for (int i = 0; i < 4; i++) {
  		for (int j = 0; j < 4; j++) {
  			if (i == j) {
  				m[i][j] = 1;
  			} else {
  				m[i][j] = 0;
  			}
  		}
  	}
}

/* We want to pass matrices into OpenGL, but there are two obstacles. First, 
our matrix library uses GLdouble matrices, but OpenGL 2.x expects GLfloat 
matrices. Second, C matrices are implicitly stored one-row-after-another, while 
OpenGL expects matrices to be stored one-column-after-another. This function 
plows through both of those obstacles. */
void mat44OpenGL(GLdouble m[4][4], GLfloat openGL[4][4]) {
	for (int i = 0; i < 4; i += 1)
		for (int j = 0; j < 4; j += 1)
			openGL[i][j] = m[j][i];
}

/* Pretty-prints the given matrix, with one line of text per row of matrix. */

void mat22Print(GLdouble m[2][2]) {
    for (int i = 0; i <2; i++){
        printf("%f  %f\n",m[i][0],m[i][1]);
    } 	
}

void mat33Print(GLdouble m[3][3]) {
    for (int i = 0; i < 3; i++) {
        printf("%f %f %f\n", m[i][0], m[i][1], m[i][2]);
    }
}

void mat44Print(GLdouble m[4][4]) {
    for (int i = 0; i < 4; i+=1) {
        for (int j = 0; j< 4; j+=1) {
            printf("%f,", m[i][j]);
        }
        printf("\n");
    }
}
/* Returns the determinant of the matrix m. If the determinant is 0.0, then the 
matrix is not invertible, and mInv is untouched. If the determinant is not 0.0, 
then the matrix is invertible, and its inverse is placed into mInv. */
GLdouble mat22Invert(GLdouble m[2][2], GLdouble mInv[2][2]) {
    GLdouble det = m[0][0]*m[1][1] - m[0][1]*m[1][0];
    if (det != 0){
        mInv[0][0] = m[1][1]/det;
        mInv[0][1] = m[0][1]/((-1)*det);
        mInv[1][0] = m[1][0]/((-1)*det);
        mInv[1][1] = m[0][0]/det;
    }
    return det;	
}

/* Multiplies a 2x2 matrix m by a 2-column v, storing the result in mTimesV. 
The output should not */
void mat221Multiply(GLdouble m[2][2], GLdouble v[2], GLdouble mTimesV[2]) {
    mTimesV[0] = m[0][0]* v[0] + m[0][1] *v[1];
    mTimesV[1] = m[1][0]* v[0] + m[1][1] *v[1];
}

/* Fills the matrix m from its two columns. */
void mat22Columns(GLdouble col0[2], GLdouble col1[2], GLdouble m[2][2]) {
    m[0][0] = col0[0];
    m[0][1] = col1[0];
    m[1][0] = col0[1];
    m[1][1]	= col1[1];
}

/* Multiplies the 3x3 matrix m by the 3x3 matrix n. */
void mat333Multiply(GLdouble m[3][3], GLdouble n[3][3], GLdouble mTimesN[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            GLdouble sum = 0;
            for (int k = 0; k < 3; k++) {
                sum += m[i][k] * n[k][j];
            }
            mTimesN[i][j] = sum;
        }
    }
}

void mat331Multiply(GLdouble m[3][3], GLdouble v[3], GLdouble mTimesV[3]) {
    for (int i = 0; i < 3; i++) {
        GLdouble sum = 0;
        for (int j = 0; j < 3; j++) {
            sum += m[i][j]*v[j];
        }
        mTimesV[i] = sum;
    }
}
/* Builds a 3x3 matrix representing 2D rotation and translation in homogeneous 
coordinates. More precisely, the transformation first rotates through the angle 
theta (in radians, counterclockwise), and then translates by the vector (x, y). 
*/
void mat33Isometry(GLdouble theta, GLdouble x, GLdouble y, GLdouble isom[3][3]) {
    // GLdouble rad = M_PI/180.0 * theta;
    GLdouble rotMat[3][3] = {
        cos(theta), -sin(theta), 0,
        sin(theta), cos(theta), 0,
        0, 0, 1,
    };

    GLdouble transMat[3][3] = {
        1, 0, x,
        0, 1, y,
        0, 0, 1,
    };
    mat333Multiply(transMat, rotMat, isom);
}

void mat33Add(GLdouble m[3][3], GLdouble v[3][3], GLdouble mAddV[3][3]){
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			mAddV[i][j] = m[i][j] + v[i][j];
		}
	}
}

void matMultScalar(GLdouble k, GLdouble m[3][3], GLdouble mMultK[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			mMultK[i][j] = m[i][j]*k;
		}
	}
}

void mat33Transpose(GLdouble m[3][3], GLdouble mTrans[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			mTrans[j][i] = m[i][j];
		}
	}
}

void mat44Transpose(GLdouble m[4][4], GLdouble mTrans[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mTrans[j][i] = m[i][j];
		}
	}
}
/* Given a length-1 3D vector axis and an angle theta (in radians), builds the 
rotation matrix for the rotation about that axis through that angle. Based on 
Rodrigues' rotation formula R = I + (sin theta) U + (1 - cos theta) U^2. */
void mat33AngleAxisRotation(GLdouble theta, GLdouble axis[3], GLdouble rot[3][3]) {
	GLdouble axis33[3][3] = {
		0, -axis[2], axis[1],
		axis[2], 0, -axis[0],
		-axis[1], axis[0], 0,
	};
	GLdouble axis33Square[3][3];
	GLdouble identity[3][3] = {
	  1,0,0,
	  0,1,0,
	  0,0,1,
	};
	GLdouble rAddPart1[3][3];
	GLdouble rAddPart2[3][3];
	mat333Multiply(axis33, axis33, axis33Square);
	matMultScalar(sin(theta), axis33, rAddPart1);
	matMultScalar(1-cos(theta), axis33Square, rAddPart2);
	mat33Add(rAddPart1, rAddPart2, rot);
	mat33Add(rot, identity, rot);
}

/* Given two length-1 3D vectors u, v that are perpendicular to each other. 
Given two length-1 3D vectors a, b that are perpendicular to each other. Builds 
the rotation matrix that rotates u to a and v to b. */
void mat33BasisRotation(GLdouble u[3], GLdouble v[3], GLdouble a[3], GLdouble b[3], 
        GLdouble rot[3][3]) {
	GLdouble w[3];
	vec3Cross(u, v, w);
	GLdouble R[3][3] = {
		u[0], v[0], w[0],
		u[1], v[1], w[1],
		u[2], v[2], w[2],
	};

	GLdouble ab[3];
	vec3Cross(a, b, ab);
	GLdouble S[3][3] = {
		a[0], b[0], ab[0],
		a[1], b[1], ab[1],
		a[2], b[2], ab[2],
	};
	GLdouble Rtrans[3][3];
	mat33Transpose(R, Rtrans);
	mat333Multiply(S, Rtrans, rot);
}

/* Multiplies m by n, placing the answer in mTimesN. */
void mat444Multiply(GLdouble m[4][4], GLdouble n[4][4], GLdouble mTimesN[4][4]) {
	for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            GLdouble sum = 0;
            for (int k = 0; k < 4; k++) {
                sum += m[i][k] * n[k][j];
            }
            mTimesN[i][j] = sum;
        }
    }
}

/* Multiplies m by v, placing the answer in mTimesV. */
void mat441Multiply(GLdouble m[4][4], GLdouble v[4], GLdouble mTimesV[4]) {
	for (int i = 0; i < 4; i++) {
        GLdouble sum = 0;
        for (int j = 0; j < 4; j++) {
            sum += m[i][j]*v[j];
        }
        mTimesV[i] = sum;
    }
}

/* Given a rotation and a translation, forms the 4x4 homogeneous matrix 
representing the rotation followed in time by the translation. */
void mat44Isometry(GLdouble rot[3][3], GLdouble trans[3], GLdouble isom[4][4]) {
	GLdouble trans44[4][4] = {
		1, 0, 0, trans[0],
		0, 1, 0, trans[1],
		0, 0, 1, trans[2],
		0, 0, 0, 1
	};

	GLdouble rot44[4][4] = {
		rot[0][0], rot[0][1], rot[0][2], 0,
		rot[1][0], rot[1][1], rot[1][2], 0,
		rot[2][0], rot[2][1], rot[2][2], 0,
		0, 0, 0, 1
	};

	mat444Multiply(trans44, rot44, isom);
}

/* Given a rotation and translation, forms the 4x4 homogeneous matrix 
representing the inverse translation followed in time by the inverse rotation. 
That is, the isom produced by this function is the inverse to the isom 
produced by mat44Isometry on the same inputs. */
void mat44InverseIsometry(GLdouble rot[3][3], GLdouble trans[3], 
        GLdouble isom[4][4]) {
	GLdouble trans44Inverse[4][4] = {
		1, 0, 0, -trans[0],
		0, 1, 0, -trans[1],
		0, 0, 1, -trans[2],
		0, 0, 0, 1
	};

	GLdouble rot44[4][4] = {
		rot[0][0], rot[0][1], rot[0][2], 0,
		rot[1][0], rot[1][1], rot[1][2], 0,
		rot[2][0], rot[2][1], rot[2][2], 0,
		0, 0, 0, 1
	};

	GLdouble rot44Transpose[4][4];
	mat44Transpose(rot44, rot44Transpose);
	mat444Multiply(rot44Transpose, trans44Inverse, isom);
}

/* Builds a 4x4 matrix representing orthographic projection with a boxy viewing 
volume [left, right] x [bottom, top] x [far, near]. That is, on the near plane 
the box is the rectangle R = [left, right] x [bottom, top], and on the far 
plane the box is the same rectangle R. Keep in mind that 0 > near > far. Maps 
the viewing volume to [-1, 1] x [-1, 1] x [-1, 1]. */
void mat44Orthographic(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, 
        GLdouble far, GLdouble near, GLdouble proj[4][4]){
  	for (int i = 0; i < 4; i++) {
  		for (int j = 0; j < 4; j++) {
  			proj[i][j] = 0;
  		}
  	}
	proj[0][0] = 2/(right - left);
	proj[1][1] = 2/(top - bottom);
	proj[2][2] = 2/(near - far);
	proj[2][3] = (near + far)/(far - near);
	proj[0][3] = (right + left)/(left - right);
	proj[1][3] = (top + bottom)/(bottom - top);
	proj[3][3] = 1;
}
/* Builds a 4x4 matrix that maps a projected viewing volume 
[-1, 1] x [-1, 1] x [-1, 1] to screen [0, w - 1] x [0, h - 1] x [-1, 1]. */
void mat44Viewport(GLdouble width, GLdouble height, GLdouble view[4][4]){
	for (int i = 0; i < 4; i++) {
  		for (int j = 0; j < 4; j++) {
  			view[i][j] = 0;
  		}
  	}
  	view[0][0] = (width - 1)/ 2;
  	view[0][3] = (width - 1)/ 2;
  	view[1][1] = (height - 1)/ 2;
  	view[1][3] = (height - 1)/ 2;
  	view[2][2] = 1;
  	view[3][3] = 1;
}
/* Builds a 4x4 matrix representing perspective projection. The viewing frustum 
is contained between the near and far planes, with 0 > near > far. On the near 
plane, the frustum is the rectangle R = [left, right] x [bottom, top]. On the 
far plane, the frustum is the rectangle (far / near) * R. Maps the viewing 
volume to [-1, 1] x [-1, 1] x [-1, 1]. */
void mat44Perspective(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, 
        GLdouble far, GLdouble near, GLdouble proj[4][4]){
	for (int i = 0; i < 4; i++) {
  		for (int j = 0; j < 4; j++) {
  			proj[i][j] = 0;
  		}
  	}
	proj[0][0] = -(2 * near) / (right - left);
	proj[1][1] = -(2 * near) / (top - bottom);
	proj[2][2] = (near + far) / (far - near);
	proj[0][2] = (right + left) / (right - left);
	proj[1][2] = (top + bottom) / (top - bottom); 
	proj[3][2] =  -1;
	proj[2][3] =  (2 * near * far) / (near - far);	

}





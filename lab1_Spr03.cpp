/*
 * LAB1 - from Spring 2003
 * CS370
 *  
 * Alfredo Tigolo III
 * 
 * Comments:  Feel free to view code.  Have fun trying to get it to work.
 * 
 * Compute the determinant of a 4x4 matrix using four processes  NOTE:
 * Determinant is computed as a sum of four terms (each term comprises of
 * computing a 3x3 matrix).  Use the parent process to add four terms and
 * print out the determinant.
 */
#include <iostream.h>

int *p = NULL;
int procs, id, shareid;
int deterSum;

extern "C"{
//for external c functions in util.o
int process_fork(int nproc);
void process_join(int nproc, int id);
int *shareint (int size, int& id);
void clean_up_shared(int IdShareMem);
}

//FUNCTION PROTOTYPES
void determinant(int *p, int sum, int m[4][4]);
void DisplayMatrix(int m[4][4]);

/*
 * MAINT METHOD
 **/
int main()
{	
	int m[4][4]={ {1,2,3,4},
		      {5,6,7,8},
		      {9,10,11,12},
		      {13,14,15,16} };
	p = shareint(4, shareid);	      
	determinant ( p, deterSum, m);
	deterSum = *p;
	cout << "Determinant sum is: " << deterSum << endl;
//	DisplayMatrix(m);

	clean_up_shared(shareid);
	
	return 0;
}//end main

/*
 * METHOD THAT DISPLAYS THE MATRIX
 **/
void DisplayMatrix(int m[4][4]) {
	for (int i = 0; i<4; i++)
	{
		for (int j=0; j<4; j++) {
			cout << i << j << "array element at :" << endl;
			cout << m[i][j] << endl;
		}//inner loop
	}//outer loop
}//end DisplayMatrix

/*
 * METHOD THAT CALCULATES DETERMINANT OF A 4x4 MATRIX.  USED ALSO
 * TO BREAK UP INTO 4 PROCESSES.
 **/
void determinant(int *p, int sum,int m[4][4]) {
	procs = 4;
	id = process_fork(procs);
	int term1, term2, term3, subTotal;
	//determinant switch case code
	switch(id) {
		case 0: cout << endl << "case 0" << endl;
			term1=m[1][1]*(m[2][2]*m[3][3]-m[3][2]*m[2][3]);
			term2=m[1][2]*(m[2][1]*m[3][3]-m[2][3]*m[3][1]);
			term3=m[1][3]*(m[2][1]*m[3][2]-m[2][2]*m[3][1]);
			cout << "Term 1 is "<< term1 <<" ";
			cout << "Term 2 is "<< term2 <<" ";
			cout << "Term 3 is "<< term3 <<" ";
			subTotal=m[0][0]*(term1-term2+term3);
			*p += subTotal;
			cout << "P0 SubSum is "<< subTotal << endl;
			break;
		case 1: cout << endl << "case 1" << endl;
			term1=m[1][0]*(m[2][2]*m[3][3]-m[2][3]*m[3][2]);
			term2=m[1][2]*(m[2][0]*m[3][3]-m[2][3]*m[3][0]);
			term3=m[1][3]*(m[2][0]*m[3][2]-m[2][2]*m[3][0]);
			cout << "Term 1 is "<< term1 <<" ";
			cout << "Term 2 is "<< term2 <<" ";
			cout << "Term 3 is "<< term3 <<" ";
			subTotal=m[0][1]*(term1-term2+term3);
			cout << "P1 SubSum is " << subTotal << endl;
			*p -= subTotal;
			break;
		case 2: cout << endl << "case 2" << endl;
			term1=m[1][0]*(m[2][1]*m[3][3]-m[2][3]*m[3][1]);
			term2=m[1][1]*(m[2][0]*m[3][3]-m[2][3]*m[3][0]);
			term3=m[1][3]*(m[2][0]*m[3][1]-m[2][1]*m[3][0]);
			cout << "Term 1 is "<< term1 <<" ";
			cout << "Term 2 is "<< term2 <<" ";
			cout << "Term 3 is "<< term3 <<" ";
			subTotal=m[0][2]*(term1-term2+term3);
			cout << "P2 SubSum is " << subTotal << endl;
			*p += subTotal;
			break;
		case 3: cout << endl << "case 3" << endl;
			term1=m[1][0]*(m[2][1]*m[3][2]-m[2][2]*m[3][1]);
			term2=m[1][1]*(m[2][0]*m[3][2]-m[2][2]*m[3][0]);
			term3=m[1][2]*(m[2][0]*m[3][1]-m[2][1]*m[3][0]);
			cout << "Term 1 is "<< term1 <<" ";
			cout << "Term 2 is "<< term2 <<" ";
			cout << "Term 3 is "<< term3 <<" ";
			subTotal=m[0][3]*(term1-term2+term3);
			cout << "P3 SubSum is " << subTotal << endl;
			*p -= subTotal;
			break;
	}
	process_join(procs, id);
}//end determinant 

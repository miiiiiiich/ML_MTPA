#define N 4
void printmat(double a[N][N])
{
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
		printf("%10g",a[i][j]);
		printf("\n");
	}
}

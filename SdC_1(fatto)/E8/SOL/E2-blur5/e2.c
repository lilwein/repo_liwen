// Scrivere la soluzione qui...
void blur5(unsigned char* in, unsigned char* out, int w, int h){
	int row;
	int col;
	int sum;
	for(int i = 0; i < h*w; i++){
		sum = 0;
		row = (int) (i/w);
		col = i%w;
		if(row-2 < 0 || row+2 >= h || col-2 < 0 || col+2 >= w)
			out[i] = in[i];
		else{
			for(int j=row-2; j<=row+2;j++)
				for(int k = col-2; k<=col+2; k++)
					sum += in[j*w+k];
			out[i] = sum/25;
		}
	}
}

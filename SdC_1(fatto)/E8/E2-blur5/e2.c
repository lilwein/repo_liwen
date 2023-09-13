void blur5(unsigned char* in, unsigned char* out, int w, int h){
    for(int r=0; r<h; r++){
        for(int c=0; c<w; c++){
            if( (r-2)<0 || (r+2)>=h || (c-2)<0 || (c+2)>=w ){
                out[c+w*r] = in[c+w*r];
            }
            else{
                unsigned avg = 0;
                for(int i=r-2; i<=r+2; i++){
                    for(int j=c-2; j<=c+2; j++){
                        avg += in[j+w*i];
                    }
                }
                out[c+w*r] = avg/25;
            }
        }
    }

}
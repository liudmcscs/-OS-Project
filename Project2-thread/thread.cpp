#include "bmpReader.h"
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <pthread.h>
#include <iostream>
#define M_PI 3.14159265358979323846
using namespace std;
const int BILINEAR_RATIO = 7;
float ROTATION_ANGLE = 45;
float ROTATION_ANGLE_60 = 60;
float SHEAR_VERTICAL_DEGREE = 0.3;
float SHEAR_HORIZONTAL_DEGREE = 0.6;
float SHEAR_VERTICAL_DEGREE_45 = 0.45;
float SHEAR_HORIZONTAL_DEGREE_45 = 0.45;

const char* INPUT_IMAGE = "input.bmp";
const char* OUT_IMAGE[5] = {"output1.bmp", "output2.bmp", "output3.bmp", "output4.bmp", "output5.bmp"};
BmpImage bilinear(BmpImage pic, int nw, int nh);
BmpImage rotation(BmpImage pic, int nw,int nh);
BmpImage shear_vertical(BmpImage pic, int nw, int nh);
BmpImage shear_horizontal(BmpImage pic, int nw, int nh);
BmpImage rotation_60(BmpImage pic, int nw,int nh);
BmpImage shear_vertical_45(BmpImage pic, int nw, int nh);
BmpImage shear_horizontal_45(BmpImage pic, int nw, int nh);
// TODO: add your pthread codes to speed up the program
struct timeval tv_begin, tv_end;
void *rotation(void* rotation_pic_p);
void* shvert(void* shearVert_pic_p);
void* shhori(void* shearHori_pic_p);
void *shshrosh(void* shearHori_pic_p);
 BmpReader* bmpReader = new BmpReader();


int main(){
 double t1,t2,speeduprate;
 struct timeval  tv1, tv2;

 // timing function 1
 gettimeofday(&tv1, NULL);



 BmpImage input_pic = bmpReader->ReadBMP(INPUT_IMAGE);

 int newWidth = (int)(input_pic.width * BILINEAR_RATIO);
 int newHeight = (int)(input_pic.height * BILINEAR_RATIO);

 //all image processing
 BmpImage bilinear_pic = bilinear(input_pic, newWidth, newHeight);
 BmpImage rotation_pic = rotation(bilinear_pic, newWidth, newHeight);
 BmpImage shearVert_pic = shear_vertical(bilinear_pic, newWidth, newHeight);
 BmpImage shearHori_pic = shear_horizontal(bilinear_pic, newWidth, newHeight);

 BmpImage tmp1_pic = shear_vertical_45(bilinear_pic, newWidth, newHeight);
 BmpImage tmp2_pic = rotation_60(tmp1_pic, newWidth, newHeight);
 BmpImage mix_pic = shear_horizontal_45(tmp2_pic, newWidth, newHeight);
 //Write bmp files
 bmpReader->WriteBMP(OUT_IMAGE[0], bilinear_pic);
 bmpReader->WriteBMP(OUT_IMAGE[1], rotation_pic);
 bmpReader->WriteBMP(OUT_IMAGE[2], shearVert_pic);
 bmpReader->WriteBMP(OUT_IMAGE[3], shearHori_pic);
 bmpReader->WriteBMP(OUT_IMAGE[4], mix_pic);

 //free memory
 free(input_pic.data);
 free(bilinear_pic.data);
 free(rotation_pic.data);
 free(shearVert_pic.data);
 free(shearHori_pic.data);
 free(tmp1_pic.data);
 free(tmp2_pic.data);
 free(mix_pic.data);

 // timing function 2
 gettimeofday(&tv2, NULL);

 // TODO: modify (ID) to your student ID
 t1=(double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double)(tv2.tv_sec - tv1.tv_sec);
 printf("(0311614)%f seconds\n", (double)t1);
pthread_t tid[5];
pthread_attr_t  attr;


 gettimeofday(&tv1, NULL);

 BmpReader* bmpReader_p = new BmpReader();
 BmpImage input_pic_p = bmpReader->ReadBMP(INPUT_IMAGE);


 BmpImage tmp_pic_p;
 BmpImage mix_pic_p;
pthread_attr_init(&attr);
 int newWidth_p = (int)(input_pic_p.width * BILINEAR_RATIO);
 int newHeight_p = (int)(input_pic_p.height * BILINEAR_RATIO);
 BmpImage bilinear_pic_p = bilinear(input_pic_p, newWidth, newHeight);

 bmpReader->WriteBMP(OUT_IMAGE[0], bilinear_pic_p);

 BmpImage rotation_pic_p = bilinear_pic_p;
 BmpImage shearVert_pic_p = bilinear_pic_p;
 BmpImage shearHori_pic_p = bilinear_pic_p;
 BmpImage shearotsh_pic_p = bilinear_pic_p;

 pthread_create(&tid[0],&attr, &rotation, &rotation_pic_p);
 pthread_create(&tid[1],&attr, &shvert, &shearVert_pic_p);
 pthread_join(tid[0], NULL); //cout<<"444FFFFiiii4444"<<endl;
 pthread_join(tid[1], NULL);

 pthread_create(&tid[2], &attr, &shhori, &shearHori_pic_p);
 pthread_create(&tid[3], &attr, &shshrosh, &shearotsh_pic_p);
 pthread_join(tid[2], NULL);
 pthread_join(tid[3], NULL);

  //Write bmp files

 //free memory
 free(input_pic_p.data);

 gettimeofday(&tv2, NULL);
 t2=(double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double)(tv2.tv_sec - tv1.tv_sec);
 printf("(0311614)%f seconds\n", (double)t2);
 speeduprate=(double)t1/t2;
 printf("speed up rate :%f \n", (double)speeduprate);
 exit(0);

 return 0;
}
void *rotation(void* rotation_pic_p)
{
 BmpImage rotation_p=*(BmpImage*) rotation_pic_p;
 int nw = (int)(rotation_p.width );
 int nh = (int)(rotation_p.height );
  unsigned char* data = (unsigned char*)malloc(3 * nw * nh * sizeof(unsigned char));

 int w_offset = (int)(nw / 2);
 int h_offset = (int)(nh / 2);

 for(int i = 0 ; i < nw; i++){
  for(int j = 0; j < nh; j++){
   for(int k = 0 ; k < 3 ; k++){

    double angle = (double)ROTATION_ANGLE * M_PI / 180.0;
    double cos_theta = cos(angle);
    double sin_theta = sin(angle);
    int relevant_w = i - w_offset;
    int relevant_h = j - h_offset;
    int trans_w = (int)(relevant_w * cos_theta - relevant_h * sin_theta) + w_offset;
    int trans_h = (int)(relevant_h * cos_theta + relevant_w * sin_theta) + h_offset;

    int pixel;

    if (trans_w >= 0 && trans_w < w_offset * 2 && trans_h >= 0 && trans_h < h_offset * 2){
     pixel = rotation_p.data[3 * (trans_h * 2 * w_offset + trans_w) + k];
    }else{
     pixel = 0;
    }

    data[3 * (j * nw + i) + k] = pixel;
   }
  }
 }

 BmpImage newBmpImage;

 newBmpImage.data = data;
 newBmpImage.width = nw;
 newBmpImage.height = nh;
 bmpReader->WriteBMP(OUT_IMAGE[1], newBmpImage);
 pthread_exit(NULL);
}

void *shshrosh(void* shearHori_pic_p)
{
 BmpImage shhori_p=*(BmpImage*) shearHori_pic_p;
 int nw = (int)(shhori_p.width );
 int nh = (int)(shhori_p.height );
 unsigned char* data1 = (unsigned char*)malloc(3 * nw * nh * sizeof(unsigned char));

 for(int i = 0 ; i < nw ; i++){
  for(int j = 0 ; j < nh ; j++){
   //k is RGB color, R = 2, G = 1, B = 0
   for(int k = 0;k < 3;k++){
    int pixel = 0;
    int h_offset = (int)(nw * SHEAR_VERTICAL_DEGREE_45 / 2);
    int trans_w = i;
    int trans_h = (int)(j + i * SHEAR_VERTICAL_DEGREE_45) - h_offset;

    if (trans_h >= 0 && trans_h < nh){
     pixel = shhori_p.data[3 * (trans_h * nw + trans_w) + k];
    }else{
     pixel = 0;
    }

    data1[3 * (j * nw + i) + k] = pixel;
   }
  }
 }
 BmpImage temp1;
 temp1.data=data1;
 int w_offset = (int)(nw / 2);
 int h_offset = (int)(nh / 2);
 unsigned char* data2 = (unsigned char*)malloc(3 * nw * nh * sizeof(unsigned char));
 for(int i = 0 ; i < nw; i++){
  for(int j = 0; j < nh; j++){
   for(int k = 0 ; k < 3 ; k++){

    double angle = (double)ROTATION_ANGLE_60 * M_PI / 180.0;
    double cos_theta = cos(angle);
    double sin_theta = sin(angle);
    int relevant_w = i - w_offset;
    int relevant_h = j - h_offset;
    int trans_w = (int)(relevant_w * cos_theta - relevant_h * sin_theta) + w_offset;
    int trans_h = (int)(relevant_h * cos_theta + relevant_w * sin_theta) + h_offset;

    int pixel;

    if (trans_w >= 0 && trans_w < w_offset * 2 && trans_h >= 0 && trans_h < h_offset * 2){
     pixel = temp1.data[3 * (trans_h * 2 * w_offset + trans_w) + k];
    }else{
     pixel = 0;
    }

    data2[3 * (j * nw + i) + k] = pixel;
   }
  }
 }
 BmpImage temp2;
 temp2.data=data2;
 unsigned char* data3 = (unsigned char*)malloc(3 * nw * nh * sizeof(unsigned char));
 for(int i = 0 ; i < nw ; i++){
  for(int j = 0 ; j < nh ; j++){
   //k is RGB color, R = 2, G = 1, B = 0
   for(int k = 0;k < 3;k++){
    int pixel = 0;

    int w_offset = (int)(nh * SHEAR_HORIZONTAL_DEGREE_45 / 2);
    int trans_h = j;
    int trans_w = (int)(i + j * SHEAR_HORIZONTAL_DEGREE_45) - w_offset;

    if (trans_w >= 0 && trans_w < nw){
     pixel = temp2.data[3 * (trans_h * nw + trans_w) + k];
    }else{
     pixel = 0;
    }

    // TODO: refer to shear_vertical, try to write shear_horizontal on your own

    data3[3 * (j * nw + i) + k] = pixel;
   }
  }
 }
/*
 */



 BmpImage newBmpImage;

 newBmpImage.data = data3;
 newBmpImage.width = nw;
 newBmpImage.height = nh;

 bmpReader->WriteBMP(OUT_IMAGE[4], newBmpImage);
 pthread_exit(NULL);
}


void *shvert(void* shearVert_pic_p)
{
 BmpImage shvert_p=*(BmpImage*) shearVert_pic_p;
 int nw = (int)(shvert_p.width );
 int nh = (int)(shvert_p.height );
 BmpImage shearVert_pic;



 unsigned char* data = (unsigned char*)malloc(3 * nw * nh * sizeof(unsigned char));

int pixel    ;
int h_offset ;
int trans_w  ;
int trans_h  ;

 for(int i = 0 ; i < nw ; i++){
  for(int j = 0 ; j < nh ; j++){
   //k is RGB color, R = 2, G = 1, B = 0
   for(int k = 0;k < 3;k++){
    pixel = 0;
    h_offset = (int)(nw * SHEAR_VERTICAL_DEGREE / 2);
    trans_w = i;
    trans_h = (int)(j + i * SHEAR_VERTICAL_DEGREE) - h_offset;

    if (trans_h >= 0 && trans_h < nh){
     pixel = shvert_p.data[3 * (trans_h * nw + trans_w) + k];
    }
    else{
     pixel = 0;
    }

    data[3 * (j * nw + i) + k] = pixel;
   }
  }
 }

 BmpImage newBmpImage;

 newBmpImage.data = data;
 newBmpImage.width = nw;
 newBmpImage.height = nh;
 bmpReader->WriteBMP(OUT_IMAGE[2], newBmpImage);


pthread_exit(NULL);

}
void *shhori(void* shearHori_pic_p)
{
 BmpImage shhori_p=*(BmpImage*) shearHori_pic_p;
 int nw = (int)(shhori_p.width );
 int nh = (int)(shhori_p.height );

 unsigned char* data = (unsigned char*)malloc(3 * nw * nh * sizeof(unsigned char));
int pixel    ;
int h_offset ;
int trans_w  ;
int trans_h  ;
 for(int i = 0 ; i < nw ; i++){
  for(int j = 0 ; j < nh ; j++){
   //k is RGB color, R = 2, G = 1, B = 0
   for(int k = 0;k < 3;k++){
    int pixel = 0;

    int w_offset = (int)(nh * SHEAR_HORIZONTAL_DEGREE / 2);
    int trans_h = j;
    int trans_w = (int)(i + j * SHEAR_HORIZONTAL_DEGREE) - w_offset;

    if (trans_w >= 0 && trans_w < nw){
     pixel = shhori_p.data[3 * (trans_h * nw + trans_w) + k];
    }else{
     pixel = 0;
    }

    // TODO: refer to shear_vertical, try to write shear_horizontal on your own

    data[3 * (j * nw + i) + k] = pixel;
   }
  }
 }

 BmpImage newBmpImage;

 newBmpImage.data = data;
 newBmpImage.width = nw;
 newBmpImage.height = nh;

 bmpReader->WriteBMP(OUT_IMAGE[3], newBmpImage);
 pthread_exit(NULL);
}

BmpImage bilinear(BmpImage pic, int newWidth, int newHeight)
{
 unsigned char* data = (unsigned char*)malloc(3 * newWidth * newHeight * sizeof(unsigned char));

 for(int i = 0 ; i < newWidth; i++){
  for(int j = 0;j < newHeight; j++){
   //k is RGB color, R = 2, G = 1, B = 0
   for(int k = 0;k < 3;k++){
    int pixel = 0;
    int relevant_w = (int)(i / BILINEAR_RATIO);
    int relevant_h = (int)(j / BILINEAR_RATIO);
    int reference_points[4];

    // the four reference points of this pixel
    reference_points[0] = pic.data[3 * (relevant_h * pic.width + relevant_w) + k];
    reference_points[1] = pic.data[3 * (relevant_h * pic.width + (relevant_w + 1)) + k];
    reference_points[2] = pic.data[3 * ((relevant_h + 1) * pic.width + relevant_w) + k];
    reference_points[3] = pic.data[3 * ((relevant_h + 1) * pic.width + (relevant_w + 1)) + k];

    // TODO: assign a new value to this pixel
    pixel = reference_points[0]*(BILINEAR_RATIO-i%BILINEAR_RATIO)*(BILINEAR_RATIO-j%BILINEAR_RATIO) + reference_points[1]*(i%BILINEAR_RATIO)*(BILINEAR_RATIO-j%BILINEAR_RATIO)+reference_points[2]*(BILINEAR_RATIO-i%BILINEAR_RATIO)*(j%BILINEAR_RATIO)+reference_points[3]*(i%BILINEAR_RATIO)*(j%BILINEAR_RATIO);
    pixel/=(BILINEAR_RATIO*BILINEAR_RATIO);
	if (pixel < 0) pixel = 0;
    if (pixel > 255) pixel = 255;

    data[3 * (j * newWidth + i) + k] = pixel;
   }
  }
 }

 BmpImage newBmpImage;

 newBmpImage.data = data;
 newBmpImage.width = newWidth;
 newBmpImage.height = newHeight;

 return newBmpImage;
}

BmpImage rotation(BmpImage pic,int nw,int nh)
{
 unsigned char* data = (unsigned char*)malloc(3 * nw * nh * sizeof(unsigned char));

 int w_offset = (int)(nw / 2);
 int h_offset = (int)(nh / 2);

 for(int i = 0 ; i < nw; i++){
  for(int j = 0; j < nh; j++){
   for(int k = 0 ; k < 3 ; k++){

    double angle = (double)ROTATION_ANGLE * M_PI / 180.0;
    double cos_theta = cos(angle);
    double sin_theta = sin(angle);
    int relevant_w = i - w_offset;
    int relevant_h = j - h_offset;
    int trans_w = (int)(relevant_w * cos_theta - relevant_h * sin_theta) + w_offset;
    int trans_h = (int)(relevant_h * cos_theta + relevant_w * sin_theta) + h_offset;

    int pixel;

    if (trans_w >= 0 && trans_w < w_offset * 2 && trans_h >= 0 && trans_h < h_offset * 2){
     pixel = pic.data[3 * (trans_h * 2 * w_offset + trans_w) + k];
    }else{
     pixel = 0;
    }

    data[3 * (j * nw + i) + k] = pixel;
   }
  }
 }

 BmpImage newBmpImage;

 newBmpImage.data = data;
 newBmpImage.width = nw;
 newBmpImage.height = nh;

 return newBmpImage;
}


BmpImage rotation_60(BmpImage pic,int nw,int nh)
{
 unsigned char* data = (unsigned char*)malloc(3 * nw * nh * sizeof(unsigned char));

 int w_offset = (int)(nw / 2);
 int h_offset = (int)(nh / 2);

 for(int i = 0 ; i < nw; i++){
  for(int j = 0; j < nh; j++){
   for(int k = 0 ; k < 3 ; k++){

    double angle = (double)ROTATION_ANGLE_60 * M_PI / 180.0;
    double cos_theta = cos(angle);
    double sin_theta = sin(angle);
    int relevant_w = i - w_offset;
    int relevant_h = j - h_offset;
    int trans_w = (int)(relevant_w * cos_theta - relevant_h * sin_theta) + w_offset;
    int trans_h = (int)(relevant_h * cos_theta + relevant_w * sin_theta) + h_offset;

    int pixel;

    if (trans_w >= 0 && trans_w < w_offset * 2 && trans_h >= 0 && trans_h < h_offset * 2){
     pixel = pic.data[3 * (trans_h * 2 * w_offset + trans_w) + k];
    }else{
     pixel = 0;
    }

    data[3 * (j * nw + i) + k] = pixel;
   }
  }
 }

 BmpImage newBmpImage;

 newBmpImage.data = data;
 newBmpImage.width = nw;
 newBmpImage.height = nh;

 return newBmpImage;
}

BmpImage shear_vertical(BmpImage pic, int nw, int nh)
{

 unsigned char* data = (unsigned char*)malloc(3 * nw * nh * sizeof(unsigned char));

 for(int i = 0 ; i < nw ; i++){
  for(int j = 0 ; j < nh ; j++){
   //k is RGB color, R = 2, G = 1, B = 0
   for(int k = 0;k < 3;k++){
    int pixel = 0;
    int h_offset = (int)(nw * SHEAR_VERTICAL_DEGREE / 2);
    int trans_w = i;
    int trans_h = (int)(j + i * SHEAR_VERTICAL_DEGREE) - h_offset;

    if (trans_h >= 0 && trans_h < nh){
     pixel = pic.data[3 * (trans_h * nw + trans_w) + k];
    }else{
     pixel = 0;
    }

    data[3 * (j * nw + i) + k] = pixel;
   }
  }
 }

 BmpImage newBmpImage;

 newBmpImage.data = data;
 newBmpImage.width = nw;
 newBmpImage.height = nh;

 return newBmpImage;
}


BmpImage shear_vertical_45(BmpImage pic, int nw, int nh)
{

 unsigned char* data = (unsigned char*)malloc(3 * nw * nh * sizeof(unsigned char));

 for(int i = 0 ; i < nw ; i++){
  for(int j = 0 ; j < nh ; j++){
   //k is RGB color, R = 2, G = 1, B = 0
   for(int k = 0;k < 3;k++){
    int pixel = 0;
    int h_offset = (int)(nw * SHEAR_VERTICAL_DEGREE_45 / 2);
    int trans_w = i;
    int trans_h = (int)(j + i * SHEAR_VERTICAL_DEGREE_45) - h_offset;

    if (trans_h >= 0 && trans_h < nh){
     pixel = pic.data[3 * (trans_h * nw + trans_w) + k];
    }else{
     pixel = 0;
    }

    data[3 * (j * nw + i) + k] = pixel;
   }
  }
 }

 BmpImage newBmpImage;

 newBmpImage.data = data;
 newBmpImage.width = nw;
 newBmpImage.height = nh;

 return newBmpImage;
}


BmpImage shear_horizontal(BmpImage pic, int nw, int nh)
{

 unsigned char* data = (unsigned char*)malloc(3 * nw * nh * sizeof(unsigned char));

 for(int i = 0 ; i < nw ; i++){
  for(int j = 0 ; j < nh ; j++){
   //k is RGB color, R = 2, G = 1, B = 0
   for(int k = 0;k < 3;k++){
    int pixel = 0;

    int w_offset = (int)(nh * SHEAR_HORIZONTAL_DEGREE / 2);
    int trans_h = j;
    int trans_w = (int)(i + j * SHEAR_HORIZONTAL_DEGREE) - w_offset;

    if (trans_w >= 0 && trans_w < nw){
     pixel = pic.data[3 * (trans_h * nw + trans_w) + k];
    }else{
     pixel = 0;
    }

    // TODO: refer to shear_vertical, try to write shear_horizontal on your own

    data[3 * (j * nw + i) + k] = pixel;
   }
  }
 }

 BmpImage newBmpImage;

 newBmpImage.data = data;
 newBmpImage.width = nw;
 newBmpImage.height = nh;

 return newBmpImage;
}

BmpImage shear_horizontal_45(BmpImage pic, int nw, int nh)
{

 unsigned char* data = (unsigned char*)malloc(3 * nw * nh * sizeof(unsigned char));

 for(int i = 0 ; i < nw ; i++){
  for(int j = 0 ; j < nh ; j++){
   //k is RGB color, R = 2, G = 1, B = 0
   for(int k = 0;k < 3;k++){
    int pixel = 0;

    int w_offset = (int)(nh * SHEAR_HORIZONTAL_DEGREE_45 / 2);
    int trans_h = j;
    int trans_w = (int)(i + j * SHEAR_HORIZONTAL_DEGREE_45) - w_offset;

    if (trans_w >= 0 && trans_w < nw){
     pixel = pic.data[3 * (trans_h * nw + trans_w) + k];
    }else{
     pixel = 0;
    }

    // TODO: refer to shear_vertical, try to write shear_horizontal on your own

    data[3 * (j * nw + i) + k] = pixel;
   }
  }
 }

 BmpImage newBmpImage;

 newBmpImage.data = data;
 newBmpImage.width = nw;
 newBmpImage.height = nh;

 return newBmpImage;
}

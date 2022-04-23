#include <iostream>
#include "bmplib.cpp"
#include "bmplib.h"
using namespace std;
unsigned char image[SIZE][SIZE][RGB];
unsigned char newimage[SIZE][SIZE][RGB];
unsigned char image1[SIZE][SIZE][RGB];
void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readRGBBMP(imageFileName, image);
}
void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeRGBBMP(imageFileName, image);
}
void savenewImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeRGBBMP(imageFileName, newimage);
}

void filter_1() {
    int sum=0,avg=0;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            for (int k = 0; k < RGB; ++k) {
                sum+=image[i][j][k];
            }

        }
    }


    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            for (int k = 0; k < RGB; k++) {
                avg+=image[i][j][k];
            }
            avg/=3;
            if (avg>127)
            {
                image[i][j][0] = 255;
                image[i][j][1] = 255;
                image[i][j][2] = 255;
            }
            else
            {
                image[i][j][0] = 0;
                image[i][j][1] = 0;
                image[i][j][2] = 0;
            }

        }
    }
}




void invertimage() {

    // a nested for loop to loop on each pixel in image
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j< SIZE; j++) {
            for(int k=0;k<RGB;k++){

                // convert dark pixels to ligth
                if(image[i][j][k]==0){
                    image[i][j][k]=255;

               // convert ligth pixels to dark
                }else if(image[i][j][k]==255){
                    image[i][j][k]=0;

               // convert colour scale pixels
                }else{
                    image[i][j][k]=255-image[i][j][k];
                }
            }

    }
  }
}
void filter_3(){

   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the other source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readRGBBMP(imageFileName, image1);

   for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++){
        for(int k=0; k<RGB; ++k){
            image[i][j][k] = (image1[i][j][k] + image[i][j][k])/2;
        }
    }
   }



}
void filter_4() {
    int choose;
    //the user will choose the type of the flip he wants
    cout << "choose the type of the flip : " << endl;
    cout << "1- vertical flip : " << endl;
    cout << "2- Horizontal flip : " << endl;
    cin >> choose;
    //for vertical flip
    if (choose == 1) {
        for (int i = 0; i <= 255; i++) {
            for (int j = 0; j <= 127; j++) {
                for (int k = 0; k < RGB; ++k) {
                    swap(image[i][j][k], image[255 - i][ 255-j][k]);
                }
            }
        }
        //for horizontal flip
    } else if (choose == 2) {

        for (int i = 0; i <= 255; i++) {
            for (int j = 0; j <= 127; j++) {
                for (int k = 0; k < RGB; ++k) {
                    swap(image[i][j][k], image[i][255 - j][k]);
                }

            }
        }
    }


}



void rotateimage(){

    // a nested for loop to loop on each pixel in the 3D array and transpose the 3D array
     for (int i = 0; i <SIZE; i++) {
            for (int j = i+1; j < SIZE; j++) {
                    for(int k=0;k<RGB;k++){

                     //transpose
                     swap(image[i][j][k],image[j][i][k]);
                   }
            }
        }

        // a nested for loop to loop on each row in the 3D array and reverse it
        for (int i = 0; i <=SIZE; i++) {
            for (int j = 0; j <= SIZE/2; j++) {
                    for(int k=0;k<RGB;k++){
                        // reverse
                        swap(image[i][j][k],image[i][SIZE-1-j][k]);
                    }

            }
        }
}
void filter_6(){

    string choice;

    while(true){

        cout<<"Enter (D) if you want to darken the photo"<<endl;
        cout<<"Enter (L) if you want to lighten the photo"<<endl;
        cout<<endl;
        cout<<"Choose whether you want to darken or lighten the photo: ";
        cin>>choice;

        if(choice == "L" || choice == "l"){

            for (int i = 0; i <= SIZE; i++) {
                for (int j = 0; j <= SIZE; j++){
                    for(int k=0; k<RGB; ++k){
                        if(image[i][j][k]*2 <= 300){
                        image[i][j][k] *= 1.5;
                        }
                    }
                 }
             }
            break;
        }

        else if(choice == "D" || choice == "d"){

            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++){
                    for(int k=0; k<RGB; ++k){
                         image[i][j][k] *= 0.5;
                    }
                 }
             }
             break;
        }

        else{
            cout<<"Invalid input!"<<endl;
        }
    }
}
void detect_edges() {


    unsigned char new_image[SIZE][SIZE][RGB];
// first of all inorder to detect edges of the photo
// we have to return the photo into black and white only by using filter 1 of changing image into black and white
    int sum = 0, avg = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                sum += image[i][j][k];
            }

        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                avg += image[i][j][k];
            }
            avg /= 3;
            if (avg > 127) {
                image[i][j][0] = 255;
                image[i][j][1] = 255;
                image[i][j][2] = 255;
            } else {
                image[i][j][0] = 0;
                image[i][j][1] = 0;
                image[i][j][2] = 0;
            }

        }
    }
// after we turned the image into black and white we have to compare each pixel with the whole surrounded pixels
// by using already present pixels to compare with this pixel
    for (int i = 1; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                new_image[i][j][k] =
                        (image[i - 1][j - 1][k]) + (image[i + 1][j - 1][k]) + (image[i - 1][j][k]) +
                        (image[i][j][k] * -8) +
                        (image[i + 1][j][k]) + (image[i - 1][j + 1][k]) + (image[i][j + 1][k]) +
                        (image[i + 1][j + 1][k]) +
                        (image[i][j - 1][k]);
            }
        }

    }
// after we convert the image inti black and white
// and compare the pixels with it's surrounding pixels we have to invert the image by using filter 2 to invert the image colors

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int k = 0; k <RGB ; ++k) {

                if(image[i][j][k]==0){
                    image[i][j][k]=255;
                }else if(image[i][j][k]==255){
                    image[i][j][k]=0;
                }else{
                    image[i][j][k]=255-image[i][j][k];
                }
            }

        }
    }

    for(int i=0;i<255;i++){
        for(int j=0;j<255;j++){
            for(int k=0;k<RGB;k++) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = new_image[i][j][k];
                }
            }
        }
    }

    for (int i = 0; i < 255; i++) {
        for (int j = 0; j < 255; j++) {
            for (int k = 0; k < RGB; ++k) {
                if (image[i][j][k] == 0) {
                    image[i][j][k] = 255;
                } else if (image[i][j][k] == 255) {
                    image[i][j][k] = 0;
                } else {
                    image[i][j][k] = 255 - image[i][j][k];
                }
            }


        }
    }

}







void filter_8(int n){

    // enlarging first quarter
    if(n==1){

        // a nested for loop to copy the value of each pixel and store it in 4 pixels in a new image
        for (int i = 0,k=0; i <=SIZE/2,k<SIZE; i++,k+=2) {
            for (int j = 0,l=0; j <= SIZE/2,l<SIZE; j++,l+=2) {
                 for(int m=0;m<RGB;m++){
                     newimage[k][l][m]=image[i][j][m];
                     newimage[k+1][l][m]=image[i][j][m];
                     newimage[k][l+1][m]=image[i][j][m];
                     newimage[k+1][l+1][m]=image[i][j][m];
                 }
            }
        }

     // enlarging second quarter
    }else if(n==2){

        // a nested for loop to copy the value of each pixel and store it in 4 pixels in a new image
        for (int i = 0,k=0; i <=SIZE/2,k<SIZE; i++,k+=2) {
            for (int j = SIZE/2,l=0; j <= SIZE,l<SIZE; j++,l+=2) {
                 for(int m=0;m<RGB;m++){
                     newimage[k][l][m]=image[i][j][m];
                     newimage[k+1][l][m]=image[i][j][m];
                     newimage[k][l+1][m]=image[i][j][m];
                     newimage[k+1][l+1][m]=image[i][j][m];
                 }
            }
        }

    //enlarging third quarter
    }else if(n==3){

        // a nested for loop to copy the value of each pixel and store it in 4 pixels in a new image
        for (int i = SIZE/2,k=0; i <=SIZE,k<SIZE; i++,k+=2) {
            for (int j = 0,l=0; j <= SIZE/2,l<SIZE; j++,l+=2) {
                 for(int m=0;m<RGB;m++){
                     newimage[k][l][m]=image[i][j][m];
                     newimage[k+1][l][m]=image[i][j][m];
                     newimage[k][l+1][m]=image[i][j][m];
                     newimage[k+1][l+1][m]=image[i][j][m];
                 }
            }
        }

     // enlarging fourth quarter
    }else if(n==4){

        // a nested for loop to copy the value of each pixel and store it in 4 pixels in a new image
        for (int i = SIZE/2,k=0; i <=SIZE,k<SIZE; i++,k+=2) {
            for (int j = SIZE/2,l=0; j <= SIZE,l<SIZE; j++,l+=2) {
                 for(int m=0;m<RGB;m++){
                     newimage[k][l][m]=image[i][j][m];
                     newimage[k+1][l][m]=image[i][j][m];
                     newimage[k][l+1][m]=image[i][j][m];
                     newimage[k+1][l+1][m]=image[i][j][m];
                 }
            }
        }

    }

}

void filter_9(){
    string choice;
    cout<<"Enter 1 if you want to divide the image into half"<<endl;
    cout<<"Enter 2 if you want to divide the image into one third"<<endl;
    cout<<"Enter 3 if you want to divide the image into quarter"<<endl;
    cout<<"Your choice: ";
    cin>>choice;

    if(choice=="1"){

        for (int i = 0; i < SIZE/2; i++){
           for (int j = 0; j < SIZE/2; j++){
                for(int k=0; k<RGB; ++k){
                    image1[i][j][k]=image[i*2][j*2][k];
                }
           }
        }
        for (int i = 0; i < SIZE; i++){
           for (int j = 0; j < SIZE; j++){
                for(int k=0; k<RGB; ++k){
                    image[i][j][k]=image1[i][j][k];
                }
           }
        }

    }
    else if(choice=="2"){

        for (int i = 0; i < SIZE/3; i++){
           for (int j = 0; j < SIZE/3; j++){
                for(int k=0; k<RGB; ++k){
                    image1[i][j][k]=image[i*3][j*3][k];
                }
           }
        }
        for (int i = 0; i < SIZE; i++){
           for (int j = 0; j < SIZE; j++){
                for(int k=0; k<RGB; ++k){
                    image[i][j][k]=image1[i][j][k];
                }
           }
        }
    }

    else if(choice=="3"){

        for (int i = 0; i < SIZE/4; i++){
           for (int j = 0; j < SIZE/4; j++){
                for(int k=0; k<RGB; ++k){
                    image1[i][j][k]=image[i*4][j*4][k];
                }
           }
        }
        for (int i = 0; i < SIZE; i++){
           for (int j = 0; j < SIZE; j++){
                for(int k=0; k<RGB; ++k){
                    image[i][j][k]=image1[i][j][k];
                }
           }
        }
    }
}

void mirror_image(){
    cout<<"choose the filter you want here :\n"
          "1)left mirror\n"
          "2)right mirror\n"
          "3)upper mirror\n"
          "4)lower mirror \n";
    int mirror;
    cin>>mirror;
    //there are for types for image mirroring
    //first left mirror
    if(mirror==1){
        for(int i=0;i<=255;i++){
            for(int j=0;j<=127;j++){
                for (int k = 0; k < RGB; ++k) {
                    image[i][255-j][k]=image[i][j][k];
                }

            }
        }
    }
        //second right mirror
    else if(mirror==2){
        for(int i=0;i<=255;i++){
            for(int j=0;j<=127;j++){
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k]=image[i][255-j][k];
                }

            }
        }
    }
        //third upper mirror
    else if(mirror==3){

        for(int i=0;i<=127;i++){
            for(int j=0;j<=255;j++)
                for (int k = 0; k < RGB; ++k) {
                    image[255-i][j][k]= image[i][j][k];
                }

        }
    }

//forth lower mirror
    else if(mirror==4){

        for(int i=0;i<=127;i++){
            for(int j=0;j<=255;j++){
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k]=image[255-i][j][k];
                }

            }        }
    }}




void filter_b(int a,int b,int c,int d){

    //a nested for loop to insert the the first quarter of the image in the new quarter that the user chose
    if(a==1){
      for (int i = 0,k=0; i <=SIZE/2,k<SIZE/2; i++,k++) {
            for (int j = 0,l=0; j <= SIZE/2,l<SIZE/2; j++,l++) {
                    for(int m=0;m<RGB;m++){
                        newimage[k][l][m]=image[i][j][m];
                    }
            }
        }

    }else if(a==2){
        for (int i = 0,k=0; i <=SIZE/2,k<SIZE/2; i++,k++) {
            for (int j = SIZE/2,l=0; j <= SIZE,l<SIZE/2; j++,l++) {
                 for(int m=0;m<RGB;m++){
                        newimage[k][l][m]=image[i][j][m];
                    }
            }
        }
    }else if(a==3){
        for (int i = SIZE/2,k=0; i <=SIZE,k<SIZE/2; i++,k++) {
            for (int j = 0,l=0; j <= SIZE/2,l<SIZE/2; j++,l++) {
                 for(int m=0;m<RGB;m++){
                        newimage[k][l][m]=image[i][j][m];
                    }
            }
        }
    }else if(a==4){
        for (int i = SIZE/2,k=0; i <=SIZE,k<SIZE/2; i++,k++) {
            for (int j = SIZE/2,l=0; j <= SIZE,l<SIZE/2; j++,l++) {
                 for(int m=0;m<RGB;m++){
                        newimage[k][l][m]=image[i][j][m];
                    }
            }
        }
    }

    //a nested for loop to insert the the second quarter of the image in the new quarter that the user chose
    if(b==1){
       for (int i = 0,k=0; i <=SIZE/2,k<SIZE/2; i++,k++) {
            for (int j = 0,l=SIZE/2; j <= SIZE,l<SIZE; j++,l++) {
                 for(int m=0;m<RGB;m++){
                        newimage[k][l][m]=image[i][j][m];
                    }
            }
        }
    }else if(b==2){
        for (int i = 0,k=0; i <=SIZE/2,k<SIZE/2; i++,k++) {
            for (int j = SIZE/2,l=SIZE/2; j <= SIZE,l<SIZE; j++,l++) {
                 for(int m=0;m<RGB;m++){
                        newimage[k][l][m]=image[i][j][m];
                    }
            }
        }
    }else if(b==3){
        for (int i = SIZE/2,k=0; i <=SIZE,k<SIZE/2; i++,k++) {
            for (int j = 0,l=SIZE/2; j <= SIZE/2,l<SIZE; j++,l++) {
                 for(int m=0;m<RGB;m++){
                        newimage[k][l][m]=image[i][j][m];
                    }
            }
        }
    }else if(b==4){
        for (int i = SIZE/2,k=0; i <=SIZE,k<SIZE/2; i++,k++) {
            for (int j = SIZE/2,l=SIZE/2; j <= SIZE,l<SIZE; j++,l++) {
                 for(int m=0;m<RGB;m++){
                        newimage[k][l][m]=image[i][j][m];
                    }
            }
        }
    }

    //a nested for loop to insert the the third quarter of the image in the new quarter that the user chose
    if(c==1){
        for (int i = 0,k=SIZE/2; i <=SIZE/2,k<SIZE; i++,k++) {
            for (int j = 0,l=0; j <= SIZE/2,l<SIZE/2; j++,l++) {
                 for(int m=0;m<RGB;m++){
                        newimage[k][l][m]=image[i][j][m];
                    }
            }
        }
    }else if(c==2){
        for (int i = 0,k=SIZE/2; i <=SIZE/2,k<SIZE; i++,k++) {
            for (int j = SIZE/2,l=0; j <= SIZE,l<SIZE/2; j++,l++) {
                 for(int m=0;m<RGB;m++){
                        newimage[k][l][m]=image[i][j][m];
                    }
            }
        }
    }else if(c==3){
        for (int i = SIZE/2,k=SIZE/2; i <=SIZE,k<SIZE; i++,k++) {
            for (int j = 0,l=0; j <= SIZE/2,l<SIZE/2; j++,l++) {
                 for(int m=0;m<RGB;m++){
                        newimage[k][l][m]=image[i][j][m];
                    }
            }
        }
    }else if(c==4){
        for (int i = SIZE/2,k=SIZE/2; i <=SIZE,k<SIZE; i++,k++) {
            for (int j = SIZE/2,l=0; j <= SIZE,l<SIZE/2; j++,l++) {
                 for(int m=0;m<RGB;m++){
                        newimage[k][l][m]=image[i][j][m];
                    }
            }
        }
    }

    //a nested for loop to insert the the fourth quarter of the image in the new quarter that the user chose
    if(d==1){
        for (int k = SIZE/2,i=0; i <=SIZE/2,k<SIZE; i++,k++) {
            for (int l = SIZE/2,j=0; j <= SIZE/2,l<SIZE; j++,l++) {
                 for(int m=0;m<RGB;m++){
                        newimage[k][l][m]=image[i][j][m];
                    }
            }
        }
    }else if(d==2){
        for (int k = SIZE/2,i=0; i <=SIZE/2,k<SIZE; i++,k++) {
            for (int l = SIZE/2,j=SIZE/2; j <= SIZE,l<SIZE; j++,l++) {
                 for(int m=0;m<RGB;m++){
                        newimage[k][l][m]=image[i][j][m];
                    }
            }
        }
    }else if(d==3){
        for (int k = SIZE/2,i=SIZE/2; i <=SIZE,k<SIZE; i++,k++) {
            for (int l = SIZE/2,j=0; j <= SIZE/2,l<SIZE; j++,l++) {
                 for(int m=0;m<RGB;m++){
                        newimage[k][l][m]=image[i][j][m];
                    }
            }
        }
    }else if(d==4){
        for (int k = SIZE/2,i=SIZE/2; i <=SIZE,k<SIZE; i++,k++) {
            for (int l = SIZE/2,j=SIZE/2; j <= SIZE,l<SIZE; j++,l++) {
                 for(int m=0;m<RGB;m++){
                        newimage[k][l][m]=image[i][j][m];
                    }
            }
        }
    }
}
int average = 0;
void filter_c(){

        for (int i = 0; i < SIZE; i+=3){
           for (int j = 0; j < SIZE; j+=3){
                for(int k=0;k<RGB;k++){

                    for(int p = i; p < 3 + i; p++){
                       for(int h = j; h < 3 + j; h++){
                               average += image[p][h][k];
                        }
                    }

                   for(int p = i; p < 3 + i; p++){
                       for(int h = j; h < 3 + j; h++){
                               newimage[p][h][k] = average/9;
                        }
                    }
                    average=0;
           }

           }
        }

}
bool check(int a){
    if(a<0 || a>4){
        return false;
    }else{
        return true;
    }
}
int main(){
    int n,a,b,c,d;
    cout<<"Hello user!"<<endl;
    string choice;

  while(true){


    cout<<"1- Black & White Filter"<<endl;
    cout<<"2- Invert Filter"<<endl;
    cout<<"3- Merge Filter"<<endl;
    cout<<"4- Flip Image"<<endl;
    cout<<"5- Rotate Image"<<endl;
    cout<<"6- Darken and Lighten Image"<<endl;
    cout<<"7- Detect Image Edges"<<endl;
    cout<<"8- Enlarge Image"<<endl;
    cout<<"9- Shrink Image"<<endl;
    cout<<"a- Mirror 1/2 Image"<<endl;
    cout<<"b- Shuffle Image"<<endl;
    cout<<"c- Blur Image"<<endl;
    cout<<"s- Save the image to a file"<<endl;


    cout<<"Please select a filter to apply or 0 to exit: ";

    cin>>choice;
    cout<<endl;

    if(choice == "1"){

        loadImage();
        filter_1();

    }

    else if(choice == "2"){
        loadImage();
        invertimage();
    }

    else if(choice == "3"){
        loadImage();
        filter_3();

    }
    else if(choice == "4"){
        loadImage();
        filter_4();

    }

    else if(choice == "5"){
        loadImage();
        cout<<"please choose:"<<'\n'<<" 1- rotate 90 degrees"<<'\n'<<" 2- rotate 180 degrees"<<'\n'<<" 3- rotate 270 degrees"<<'\n';
        cin>>n;
        if(n==1){
            rotateimage(); //rotate 90 degrees
        }else if(n==2){
            rotateimage();
            rotateimage();  //rotate 180 degrees


        }else if(n==3){
           rotateimage();
           rotateimage();
           rotateimage();   // rotate 270 degrees

        }

    }

    else if(choice == "6"){
        loadImage();
        filter_6();

    }
    else if(choice == "7"){
        loadImage();
        detect_edges() ;

    }
    else if(choice =="8"){
        loadImage();
        cout<<"please choose Which quarter to enlarge 1, 2, 3 or 4: "<<'\n';
        cin>>n;
        filter_8(n);

    }else if(choice == "9"){
        loadImage();
        filter_9();

    }
  else if(choice == "a"){
        loadImage();
        mirror_image();

    }
    else if(choice =="b"){
        loadImage();
        cout<<"please choose new order of quarters(separated with spaces): "<<'\n';
        cin>>a>>b>>c>>d;
        while(true){
            if(check(a) && check(b) && check(c) && check(d)){
                break;
            }else{
                cout<<"invalid input, please choose new order of quarters(separated with spaces): "<<'\n';
                cin>>a>>b>>c>>d;
            }
        }
        filter_b(a,b,c,d);

    }
    else if(choice == "c"){
        loadImage();
        filter_c();
    }

    else if(choice == "0"){

        cout<<endl;
        cout<<"Thank you for using this program!"<<endl;
        break;
    }

    else if(choice == "s"){
           savenewImage();
           //saveImage();


    }

    else{

        cout<<"Invalid input!"<<endl;

    }



  }


    return 0;
}

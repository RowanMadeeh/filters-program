#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;


unsigned char image[SIZE][SIZE];


void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image);
}


void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image);
}

void swap(int& a,int& b){
    int t = a;
    a = b;
    b = t;
}

void invertimage() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j< SIZE; j++) {
            if(image[i][j]==0){
                image[i][j]=255;
            }else if(image[i][j]==255){
                image[i][j]=0;
            }else{
                image[i][j]=255-image[i][j];
            }

    }
  }
}

void rotateimage(){
     for (int i = 0; i <=SIZE; i++) {
            for (int j = i+1; j <= SIZE; j++) {

                swap(image[i][j],image[j][i]);

            }
        }
        for (int i = 0; i <=SIZE; i++) {
            for (int j = 0; j <= SIZE/2; j++) {

                swap(image[i][j],image[i][SIZE-1-j]);

            }
        }
}
void filter_1()
{
int sum=0,avg;
for(int i=0;i<size;i++){
    for(int j=0;j<size;j++){
        sum++image[i][j];
    }
}
avg=sum/(size*size);
for(int i=0;i<size;i++){
    for(int j=0;j<size;j++){
        if(image[i][j]>avg)
            image[i][j]=255;
        else
            {
            image[i][j]=0;
            }
    }
}
}

void filter_4(){
    for(int i=0;i<=255;i++){
        for(int j=0;j<=127;j++){
            swap(image[i][j],image[255-i][255-j]);
        }
    }
}


int main()
{

  cout<<"Hello user!"<<endl;

  string choice;
  int n;

  while(true){


    cout<<"1- Black & White Filter"<<endl;
    cout<<"2- Invert Filter"<<endl;
    cout<<"3- Merge Filter"<<endl;
    cout<<"4- Flip Image"<<endl;
    cout<<"5- Darken and Lighten Image"<<endl;
    cout<<"6- Rotate Image"<<endl;
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

    }

    else if(choice == "4"){
        loadImage();
         filter_4();



    }

    else if(choice == "5"){

    }

    else if(choice == "6"){
        loadImage();
        cout<<"please choose:"<<'\n'<<" 1- rotate 90 degrees"<<'\n'<<" 2- rotate 180 degrees"<<'\n'<<" 3- rotate 270 degrees"<<'\n';
        cin>>n;
        if(n==1){
            rotateimage();
        }else if(n==2){
            rotateimage();
            rotateimage();


        }else if(n==3){
           rotateimage();
           rotateimage();
           rotateimage();

        }
    }

    else if(choice == "0"){

        cout<<endl;
        cout<<"Thank you for using this program!"<<endl;
        break;
    }

    else if(choice == "s"){

        saveImage();

    }

    else{

        cout<<"Invalid input!"<<endl;

    }



  }








  return 0;
}


#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;


unsigned char image[SIZE][SIZE];
unsigned char image1[SIZE][SIZE];


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

// a function for inverting image to produce negative of the image

void invertimage() {
    // a for loop to loop on each pixel in image
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j< SIZE; j++) {

              // convert black pixels to white
            if(image[i][j]==0){
                image[i][j]=255;

             // convert white pixels to black
            }else if(image[i][j]==255){
                image[i][j]=0;

             // convert gray scale pixels
            }else{
                image[i][j]=255-image[i][j];
            }

    }
  }
}

// a function for rotating image by 90 degrees

void rotateimage(){
     // a for loop to loop on each pixel in the 2D array and transpose the 2D array
     for (int i = 0; i <=SIZE; i++) {
            for (int j = i+1; j <= SIZE; j++) {

                swap(image[i][j],image[j][i]);   // transpose

            }
        }

        // a for loop to loop on each row in the 2D array and reverse it
        for (int i = 0; i <=SIZE; i++) {
            for (int j = 0; j <= SIZE/2; j++) {

                swap(image[i][j],image[i][SIZE-1-j]);  // reverse

            }
        }
}
void filter_1()
{
int sum=0,avg;
for(int i=0;i<SIZE;i++){
    for(int j=0;j<SIZE;j++){
        sum+=image[i][j];
    }
}
avg=sum/(SIZE*SIZE);
for(int i=0;i<SIZE;i++){
    for(int j=0;j<SIZE;j++){
        if(image[i][j]>avg)
            image[i][j]=255;
        else
            {
            image[i][j]=0;
            }
    }
}
}

// a function for merging two images

void filter_3(){

   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the other source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image1);
   // a nested loop to loop on each pixel in the image
   for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++){

        // Assigning the image with the average between the pixel of the two images
        image[i][j] = (image1[i][j] + image[i][j])/2;

    }
   }



}

//function for filter 2 to flip either horizontally or verticaly
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
                swap(image[i][j], image[127 - i][127 - j]);
            }
        }
        //for horizontal flip
    } else if (choose == 2) {

        for (int i = 0; i <= 255; i++) {
            for (int j = 0; j <= 127; j++) {
                swap(image[i][j], image[i][255 - j]);
            }
        }
    }

// a function to lighten or darken an image

void filter_6(){

    string choice;

    while(true){

        cout<<"Enter (D) if you want to darken the photo"<<endl;
        cout<<"Enter (L) if you want to lighten the photo"<<endl;
        cout<<endl;
        cout<<"Choose whether you want to darken or lighten the photo: ";
        cin>>choice;
        // To lighten the image

        if(choice == "L" || choice == "l"){

            // a nested loop to loop on each pixel in the image
            for (int i = 0; i <= SIZE; i++) {
                for (int j = 0; j <= SIZE; j++){

             // Assigning each pixel with value 1.5*pixel
                    if(image[i][j]*2 <= 255){
                        image[i][j] *= 1.5;
                    }

                 }
             }
            break;
        }
        // To darken the image
        else if(choice == "D" || choice == "d"){

           // a nested loop to loop on each pixel in the image
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++){

            // Assigning each pixel with its half value
                    image[i][j] *= 0.5;

                 }
             }
             break;
        }

        else{
            cout<<"Invalid input!"<<endl;
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


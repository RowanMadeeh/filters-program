#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;


unsigned char image[SIZE][SIZE];
unsigned char image1[SIZE][SIZE];
unsigned char newimage[SIZE][SIZE];


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
                // transpose
                swap(image[i][j],image[j][i]);

            }
        }

        // a for loop to loop on each row in the 2D array and reverse it
        for (int i = 0; i <=SIZE; i++) {
            for (int j = 0; j <= SIZE/2; j++) {
                // reverse
                swap(image[i][j],image[i][SIZE-1-j]);

            }
        }
}
// a function for converting white pixels to black pixels and vice versa

void filter_1()
{
int sum=0,avg;
// a for loop for getting average of pixels
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
}
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
void detect_edges() {

    unsigned char new_image[SIZE][SIZE];

    int sum = 0, avg;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            sum += image[i][j];
        }
    }
//here we got the average of the colors in the photo
    avg = sum / (SIZE * SIZE);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j]>avg)
                image[i][j] = 255;
            else {
                image[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }

    for (int i = 1; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            new_image[i][j] = (image[i - 1][j - 1]) + (image[i + 1][j - 1]) + (image[i - 1][j]) + (image[i][j] * -8) +
                              (image[i + 1][j]) + (image[i - 1][j + 1]) + (image[i][j + 1]) + (image[i + 1][j + 1]) +
                              (image[i][j - 1]);

        }}
    for (auto &i: new_image) {
        for (unsigned char &j: i) {
            j = 255 - j;
        }

    }

    for(int i=0;i<255;i++){
        for(int j=0;j<255;j++){
            image[i][j]=new_image[i][j];
        }
    }



//invert
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] == 0) {
                image[i][j] = 255;
            } else if (image[i][j] == 255) {
                image[i][j] = 0;
            } else {
                image[i][j] = 255 - image[i][j];
            }


        }
    }

}

// a function for enlarging a certain quarter of an image
void filter_8(int n){

    // enlarging first quarter
    if(n==1){

        // a nested for loop to copy the value of each pixel and store it in 4 pixels in a new image
        for (int i = 0,k=0; i <=SIZE/2,k<SIZE; i++,k+=2) {
            for (int j = 0,l=0; j <= SIZE/2,l<SIZE; j++,l+=2) {
                 newimage[k][l]=image[i][j];
                 newimage[k+1][l]=image[i][j];
                 newimage[k][l+1]=image[i][j];
                 newimage[k+1][l+1]=image[i][j];
            }
        }

     // enlarging second quarter
    }else if(n==2){

        // a nested for loop to copy the value of each pixel and store it in 4 pixels in a new image
        for (int i = 0,k=0; i <=SIZE/2,k<SIZE; i++,k+=2) {
            for (int j = SIZE/2,l=0; j <= SIZE,l<SIZE; j++,l+=2) {
                 newimage[k][l]=image[i][j];
                 newimage[k+1][l]=image[i][j];
                 newimage[k][l+1]=image[i][j];
                 newimage[k+1][l+1]=image[i][j];
            }
        }

    //enlarging third quarter
    }else if(n==3){

        // a nested for loop to copy the value of each pixel and store it in 4 pixels in a new image
        for (int i = SIZE/2,k=0; i <=SIZE,k<SIZE; i++,k+=2) {
            for (int j = 0,l=0; j <= SIZE/2,l<SIZE; j++,l+=2) {
                 newimage[k][l]=image[i][j];
                 newimage[k+1][l]=image[i][j];
                 newimage[k][l+1]=image[i][j];
                 newimage[k+1][l+1]=image[i][j];
            }
        }

    // enlarging fourth quarter
    }else if(n==4){

        // a nested for loop to copy the value of each pixel and store it in 4 pixels in a new image
        for (int i = SIZE/2,k=0; i <=SIZE,k<SIZE; i++,k+=2) {
            for (int j = SIZE/2,l=0; j <= SIZE,l<SIZE; j++,l+=2) {
                 newimage[k][l]=image[i][j];
                 newimage[k+1][l]=image[i][j];
                 newimage[k][l+1]=image[i][j];
                 newimage[k+1][l+1]=image[i][j];
            }
        }

    }
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            image[i][j]=newimage[i][j];
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
                image1[i][j]=image[i*2][j*2];
           }
        }
        for (int i = 0; i < SIZE; i++){
           for (int j = 0; j < SIZE; j++){
                image[i][j]=image1[i][j];
           }
        }

    }
    else if(choice=="2"){

        for (int i = 0; i < SIZE/3; i++){
           for (int j = 0; j < SIZE/3; j++){
                image1[i][j]=image[i*3][j*3];
           }
        }
        for (int i = 0; i < SIZE; i++){
           for (int j = 0; j < SIZE; j++){
                image[i][j]=image1[i][j];
           }
        }
    }

    else if(choice=="3"){

        for (int i = 0; i < SIZE/4; i++){
           for (int j = 0; j < SIZE/4; j++){
                image1[i][j]=image[i*4][j*4];
           }
        }
        for (int i = 0; i < SIZE; i++){
           for (int j = 0; j < SIZE; j++){
                image[i][j]=image1[i][j];
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

                image[i][255-j]=image[i][j];


            }
        }
    }
        //second right mirror
    else if(mirror==2){
        for(int i=0;i<=255;i++){
            for(int j=0;j<=127;j++){

                image[i][j]=image[i][255-j];


            }
        }
    }
        //third upper mirror
    else if(mirror==3){

        for(int i=0;i<=127;i++){
            for(int j=0;j<=255;j++)

                image[255-i][j]= image[i][j];


        }
    }

//forth lower mirror
    else if(mirror==4){

        for(int i=0;i<=127;i++){
            for(int j=0;j<=255;j++){

                image[i][j]=image[255-i][j];

            }
        }
    }

}

// a function for shuffling the four quarters of an image
void filter_b(int a,int b,int c,int d){

    //a nested for loop to insert the the first quarter of the image in the new quarter that the user chose
    if(a==1){
      for (int i = 0,k=0; i <=SIZE/2,k<SIZE/2; i++,k++) {
            for (int j = 0,l=0; j <= SIZE/2,l<SIZE/2; j++,l++) {
                 newimage[k][l]=image[i][j];
            }
        }

    }else if(a==2){
        for (int i = 0,k=0; i <=SIZE/2,k<SIZE/2; i++,k++) {
            for (int j = SIZE/2,l=0; j <= SIZE,l<SIZE/2; j++,l++) {
                 newimage[k][l]=image[i][j];
            }
        }
    }else if(a==3){
        for (int i = SIZE/2,k=0; i <=SIZE,k<SIZE/2; i++,k++) {
            for (int j = 0,l=0; j <= SIZE/2,l<SIZE/2; j++,l++) {
                 newimage[k][l]=image[i][j];
            }
        }
    }else if(a==4){
        for (int i = SIZE/2,k=0; i <=SIZE,k<SIZE/2; i++,k++) {
            for (int j = SIZE/2,l=0; j <= SIZE,l<SIZE/2; j++,l++) {
                 newimage[k][l]=image[i][j];
            }
        }
    }

    //a nested for loop to insert the the second quarter of the image in the new quarter that the user chose
    if(b==1){
       for (int i = 0,k=0; i <=SIZE/2,k<SIZE/2; i++,k++) {
            for (int j = 0,l=SIZE/2; j <= SIZE,l<SIZE; j++,l++) {
                 newimage[k][l]=image[i][j];
            }
        }
    }else if(b==2){
        for (int i = 0,k=0; i <=SIZE/2,k<SIZE/2; i++,k++) {
            for (int j = SIZE/2,l=SIZE/2; j <= SIZE,l<SIZE; j++,l++) {
                 newimage[k][l]=image[i][j];
            }
        }
    }else if(b==3){
        for (int i = SIZE/2,k=0; i <=SIZE,k<SIZE/2; i++,k++) {
            for (int j = 0,l=SIZE/2; j <= SIZE/2,l<SIZE; j++,l++) {
                 newimage[k][l]=image[i][j];
            }
        }
    }else if(b==4){
        for (int i = SIZE/2,k=0; i <=SIZE,k<SIZE/2; i++,k++) {
            for (int j = SIZE/2,l=SIZE/2; j <= SIZE,l<SIZE; j++,l++) {
                 newimage[k][l]=image[i][j];
            }
        }
    }
    //a nested for loop to insert the the third quarter of the image in the new quarter that the user chose
    if(c==1){
        for (int i = 0,k=SIZE/2; i <=SIZE/2,k<SIZE; i++,k++) {
            for (int j = 0,l=0; j <= SIZE/2,l<SIZE/2; j++,l++) {
                 newimage[k][l]=image[i][j];
            }
        }
    }else if(c==2){
        for (int i = 0,k=SIZE/2; i <=SIZE/2,k<SIZE; i++,k++) {
            for (int j = SIZE/2,l=0; j <= SIZE,l<SIZE/2; j++,l++) {
                 newimage[k][l]=image[i][j];
            }
        }
    }else if(c==3){
        for (int i = SIZE/2,k=SIZE/2; i <=SIZE,k<SIZE; i++,k++) {
            for (int j = 0,l=0; j <= SIZE/2,l<SIZE/2; j++,l++) {
                 newimage[k][l]=image[i][j];
            }
        }
    }else if(c==4){
        for (int i = SIZE/2,k=SIZE/2; i <=SIZE,k<SIZE; i++,k++) {
            for (int j = SIZE/2,l=0; j <= SIZE,l<SIZE/2; j++,l++) {
                 newimage[k][l]=image[i][j];
            }
        }
    }
    //a nested for loop to insert the the fourth quarter of the image in the new quarter that the user chose
    if(d==1){
        for (int k = SIZE/2,i=0; i <=SIZE/2,k<SIZE; i++,k++) {
            for (int l = SIZE/2,j=0; j <= SIZE/2,l<SIZE; j++,l++) {
                 newimage[k][l]=image[i][j];
            }
        }
    }else if(d==2){
        for (int k = SIZE/2,i=0; i <=SIZE/2,k<SIZE; i++,k++) {
            for (int l = SIZE/2,j=SIZE/2; j <= SIZE,l<SIZE; j++,l++) {
                 newimage[k][l]=image[i][j];
            }
        }
    }else if(d==3){
        for (int k = SIZE/2,i=SIZE/2; i <=SIZE,k<SIZE; i++,k++) {
            for (int l = SIZE/2,j=0; j <= SIZE/2,l<SIZE; j++,l++) {
                 newimage[k][l]=image[i][j];
            }
        }
    }else if(d==4){
        for (int k = SIZE/2,i=SIZE/2; i <=SIZE,k<SIZE; i++,k++) {
            for (int l = SIZE/2,j=SIZE/2; j <= SIZE,l<SIZE; j++,l++) {
                 newimage[k][l]=image[i][j];
            }
        }
    }
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            image[i][j]=newimage[i][j];
        }
    }
}
int average = 0;
// a function to blur an image
void filter_c(){

    for (int i = 1,k=0; i < SIZE; i+=3,k++) {
        for (int j = 1,l=0; j < SIZE; j+=3,l++){

            for(int k = i; k < 3 + i; k++){
                for(int h = j; h < 3 + j; h++){
                    average += image[k][h];

                }
            }

            for(int k = i; k < 3 + i; k++){
                for(int h = j; h < 3 + j; h++){
                    image[k][h] = average/9;

                }
            }
            average = 0;
        }
    }
}
// a function to check if the input is between 1 and 4

bool check(int a){
    if(a<0 || a>4){
        return false;
    }else{
        return true;
    }
}



int main()
{

  cout<<"Hello user!"<<endl;

  string choice;
  int n,a,b,c,d;

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
            //rotate 90 degrees
            rotateimage();
        }else if(n==2){
            //rotate 180 degrees
            rotateimage();
            rotateimage();


        }else if(n==3){
            // rotate 270 degrees
           rotateimage();
           rotateimage();
           rotateimage();

        }

    }

    else if(choice == "6"){
        loadImage();
        filter_6();

    }
    else if(choice == "7"){
        loadImage();
        detect_edges();

    }
    else if(choice == "8"){
        loadImage();
        cout<<"please choose Which quarter to enlarge 1, 2, 3 or 4: "<<'\n';
        cin>>n;
        filter_8(n);

    }
    else if(choice == "9"){
        loadImage();
        filter_9();
    }
    else if(choice == "a"){
        loadImage();
        mirror_image();

    }
    else if(choice == "b"){
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

        saveImage();

    }

    else{

        cout<<"Invalid input!"<<endl;

    }



  }



  return 0;
}


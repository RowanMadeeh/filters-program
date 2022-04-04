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






int main()
{

  cout<<"Hello user!"<<endl;

  string choice;

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


    }

    else if(choice == "2"){

    }

    else if(choice == "3"){

    }

    else if(choice == "4"){


    }

    else if(choice == "5"){

    }

    else if(choice == "6"){

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


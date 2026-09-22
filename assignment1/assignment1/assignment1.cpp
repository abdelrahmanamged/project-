#include <string>
#include <iostream>
#include "Image_Class.h"
using namespace std;
void show_menu()
{
    cout << "======================================================\n";
    cout << "           welcome to our Program          \n";
    cout << "======================================================\n";
    cout << " [1]  Load Image\n";
    cout << " [2]  Apply Filter 1: Grayscale Conversion\n";
    cout << " [3]  Apply Filter 2: Black and White\n";
    cout << " [4]  Apply Filter 3: Invert Image \n";
    cout << " [5]  Apply Filter 4: Adding a Frame to the Picture\n";
    cout << " [6]  Apply Filter 5: Flip Image (Horizontal / Vertical)\n";
    cout << " [7]  Apply Filter 6: Rotate Image (90 / 180 / 270)\n";
    cout << " [8]  Apply Filter 7: Darken and Lighten Image\n";
    cout << " [9]  Apply Filter 8: Resizing Image\n";
    cout << " [10] Save Image\n";
    cout << " [11] Reset Image to Original State\n";
    cout << " [0]  Exit Program\n";
    cout << "======================================================\n";
    cout << "Enter your choice: ";
}
void save_image(Image& current_image,string & original_filename)
{
    cout << "If you want to save  in same file enter 1" << "\n";
    cout << "If you want to save  in new file enter 2\n";
    int choice;
    cout << "enter your choice" << "\n";
    cin >> choice;
    if (choice == 1)
    {
        if (current_image.saveImage(original_filename))
        {
            cout << "Image saved successfully to "<< original_filename<<"\n";
        }
        else
        {
            cout << "image failed to save to " << original_filename << " please try again\n";
        }
    }
    if (choice == 2)
    {
        string new_filename;
        cout << "enter name of new file" << "\n";
        cin >> new_filename;
        if (current_image.saveImage(new_filename))
        {
            cout << "Image saved successfully to " << new_filename << "\n";
        }
        else
        {

            cout << "Image failed to save to " << new_filename << " please try again" << "\n";
        }

            
    }
}

 int main() 
 {
     Image current_image;
     Image original_image;
     int choice;
     string file_name;

     while (true)
     {
       
         show_menu();                    // menu function
         cin >> choice;
         if (choice ==0 ) //exit
         {
             cout << "program is ended"<<"\n";
             break;
         }
         if (choice ==1 ) //load
         {
             cout << "===========\n" << "load option\n" << "===========\n";

             cout << "enter name of image with extension" << "\n";
             cout << "supported format in this program : JPEG / JPG / PNG / BMP "<<"\n";
             cin >> file_name;
             if (current_image.loadNewImage(file_name))
             {
                 cout << "Image loaded successfully\n";
                 original_image = current_image;
             
             }
             else {
                 cout << "failed to load image please try again\n";
           
             }
             
         }
         if (choice == 10) //save
         {
             cout << "===========\n"<<"save option\n"<<"===========\n";
             save_image(current_image, file_name);
         }
         if (choice == 11) // reset
         {
             cout << "===========\n" << "reset option\n" << "===========\n";
             current_image = original_image;
             cout << "original image restored successfull\n";

         }
     }
    
}



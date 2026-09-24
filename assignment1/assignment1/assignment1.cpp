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
void black_white(Image& current_image)
{
    cout << "===========\n" << "filter: black and white\n" << "===========\n";
    for (int i = 0; i < current_image.width; i++)
    {
        for (int j = 0; j < current_image.height; j++)
        {
            int avg = (current_image(i, j, 0) + current_image(i, j, 1) + current_image(i, j, 2)) / 3;
            if (avg >= 128)
            {
                for (int k = 0; k < 3; k++)
                {
                    current_image(i, j, k) = 255;
                }
            }
            else
            {
                for (int k = 0; k < 3; k++)
                {
                    current_image(i, j, k) = 0;
                }
            }

        }

    }
    cout << "Black and White filter applied successfully!\n";
}
void Rotate_Image(Image& current_image)
{
    int choice;
    int w, h;
    w = current_image.width;
    h = current_image.height;
    cout << "===========\n" << "filter: Rotate_Image \n" << "===========\n";
    cout << "Please select the rotation angle :\n";
    cout << "enter [1] for rotate 90\n";
    cout << "enter [2] for rotate 180\n";
    cout << "enter [3] for rotate 270\n";
    cout << "enter your choice\n";
    cin >> choice;
    if (choice == 1)
    {
        Image rotated_image(h,w);
        for (int i = 0; i < current_image.width; i++)
        {
            for (int j = 0; j < current_image.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    rotated_image(h - 1 - j, i, k) = current_image(i, j, k);
                }
            }
        }
        current_image = rotated_image;
        cout << "image roated 90 successfully\n";
    }
    if (choice == 2)
    {
        Image rotated_image(w,h);
        for (int i = 0; i < current_image.width; i++)
        {
            for (int j = 0; j < current_image.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    rotated_image(w-1-i,h-1-j , k) = current_image(i, j, k);
                }
            }
        }
        current_image = rotated_image;
        cout << "image roated 180 successfully\n";
    }
    if (choice == 3)
    {
        Image rotated_image(h, w);
        for (int i = 0; i < current_image.width; i++)
        {
            for (int j = 0; j < current_image.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    rotated_image(j, w-1-i, k) = current_image(i, j, k);
                }
            }
        }
        current_image = rotated_image;
        cout << "image roated 270 successfully\n";
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
         if (choice == 3) // black and white filter
         {
             black_white(current_image);
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
         if (choice == 7) //rotate image 
         {
             Rotate_Image(current_image);
      }
       
     }
    
    
}



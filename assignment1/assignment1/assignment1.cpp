#include <string>
#include <iostream>
#include "Image_Class.h"
#include <cmath>
#include <algorithm>
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
void save_image(Image& current_image, string& original_filename)
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
            cout << "Image saved successfully to " << original_filename << "\n";
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
//*************************************Hesham****************************************************************//
void Darken_or_lighten_image(Image& current_image)
{
    cout << "Do you want to darken or lighten the image?\nEnter 0 to darken or 1 to lighten.\n→ ";
    bool dark_or_light_choice = 0;
    cin >> dark_or_light_choice; // take the input from the user
    if (dark_or_light_choice)
    { // i.e. the user chose lighten
        cout << "On a scale of 0 to 100, what is the level of lightening do you wish for? (in percents)\n(0 means no change and 100 means double the lightening)\n→ ";
        int level = 0;
        while (true)
        {
            cin >> level;
            if (level >= 0 && level <= 100)
                break;
            else
                cout << "Please enter a valid level. No negative numbers. The maximum is 100\n";
        }
        for (int x = 0; x < current_image.width; x++)
        {
            for (int y = 0; y < current_image.height; y++)
            {
                for (int c = 0; c < 3; c++)
                {
                    current_image(x, y, c) *= (1 + level / 100.0); // current_image + (level / 100 * current_image)
                    if (current_image(x, y, c) > 255)
                        current_image(x, y, c) = 255;
                }
            }
        }
        cout << "The image has been lightened by " << level << "% successfully.\n";
    }
    else
    { // i.e. dark_or_light_choice = 0 which means the user chose to darken it.
        cout << "On a scale of 0 to 100, what is the level of darkening do you wish for? (in percents)\n(0 means no change and 100 means double the darkening)\n→ ";
        int level = 0;
        while (true)
        {
            cin >> level;
            if (level >= 0 && level <= 100)
                break;
            else
                cout << "Please enter a valid level. No negative numbers. The maximum is 100\n";
        }
        for (int x = 0; x < current_image.width; x++)
        {
            for (int y = 0; y < current_image.height; y++)
            {
                for (int c = 0; c < 3; c++)
                {
                    current_image(x, y, c) *= (1 - level / 100.0); // current_image - (level / 100 * current_image)
                    if (current_image(x, y, c) < 0)
                        current_image(x, y, c) = 0;
                }
            }
        }
        cout << "The image has been darkened by " << level << "% successfully.\n";
    }
}
void invert_image(Image& current_image)
{
    for (int x = 0; x < current_image.width; x++)
    {
        for (int y = 0; y < current_image.height; y++)
        {
            for (int c = 0; c < 3; c++)
            { // c++ lol
                current_image(x, y, c) = 255 - current_image(x, y, c);
            }
        }
    }
    cout << "Inversion Filter has successfully been applied.\n";
}
//************************************************************************************************************//
//--------------------------------------------------abdelrahaman-----------------------------------------//
void Grayscale_Conversion(Image& image)
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            int avg = 0;
            for (int k = 0; k < image.channels; k++)
            {
                avg += image(i, j, k);
            }
            avg = avg / 3;
            for (int k = 0; k < image.channels; k++)
            {
                image(i, j, k) = avg;
            }
        }
    }
}
void Flip_Image(int x, Image& image)
{
    if (x == 1)
    {
        for (int i = 0; i < image.height; i++)
        {
            for (int j = 0; j < image.width / 2; j++)
            {
                for (int k = 0; k < image.channels; k++)
                {
                    swap(image(j, i, k), image(image.width - 1 - j, i, k));
                }
            }
        }
    }
    if (x == 2)
    {
        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height / 2; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    swap(image(i, j, k), image(i, image.height - 1 - j, k));
                }
            }
        }
    }
}

//--------------------------------------------------------------------------------------------//
//####################################omar####################################################//
void black_white(Image& current_image)
{
    cout << "===========\n"
        << "filter: black and white\n"
        << "===========\n";
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
    cout << "===========\n"
        << "filter: Rotate_Image \n"
        << "===========\n";
    cout << "Please select the rotation angle :\n";
    cout << "enter [1] for rotate 90\n";
    cout << "enter [2] for rotate 180\n";
    cout << "enter [3] for rotate 270\n";
    cout << "enter your choice\n";
    cin >> choice;
    if (choice == 1)
    {
        Image rotated_image(h, w);
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
        Image rotated_image(w, h);
        for (int i = 0; i < current_image.width; i++)
        {
            for (int j = 0; j < current_image.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    rotated_image(w - 1 - i, h - 1 - j, k) = current_image(i, j, k);
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
                    rotated_image(j, w - 1 - i, k) = current_image(i, j, k);
                }
            }
        }
        current_image = rotated_image;
        cout << "image roated 270 successfully\n";
    }
}
//===========================================yasin================================================//
void apply_framefilter(Image& img)
{
    int frametype;
    cout << "*---Choose Frame Type---* \n";
    cout << "1. Simple Frame \n";
    cout << "2. Fancy Frame \n";
    cin >> frametype;
    int frame_size;
    cout << "Enter Frame Size : \n";
    cin >> frame_size;
    if (frametype == 1)
    {
        int r, g, b;
        cout << "Enter Frame Color (R G B values from 0 to 255): \n";
        cin >> r >> g >> b;
        for (int i = 0; i < img.width; i++)
        {
            for (int j = 0; j < img.height; j++)
            {
                if (i < frame_size || i >= img.width - frame_size || j < frame_size || j >= img.height - frame_size)
                {
                    img(i, j, 0) = r;
                    img(i, j, 1) = g;
                    img(i, j, 2) = b;
                }
            }
        }
    }
    else if (frametype == 2)
    {
        int r1, g1, b1, r2, g2, b2;
        cout << "Enter First color (Pattern) (R G B values from 0 to 255): \n";
        cin >> r1 >> g1 >> b1;
        cout << "Enter Second Color(Background of Pattern) (R G B values from 0 to 255): \n";
        cin >> r2 >> g2 >> b2;
        int square_size = 20;
        int pattern_type;
        cout << "*---Choose pattern type:---* \n";
        cout << "1. Checkers / Squares patterns \n";
        cout << "2.Diamond pattern  \n";
        cin >> pattern_type;
        int diamound_size = 20;

        for (int i = 0; i < img.width; i++)
        {
            for (int j = 0; j < img.height; j++)
            {
                if (i < frame_size || i >= img.width - frame_size || j < frame_size || j >= img.height - frame_size)
                {
                    bool apply_first_color = false;
                    if (pattern_type == 1)
                    {
                        if ((i / square_size + j / square_size) % 2 == 0)
                        {
                            apply_first_color = true;
                        }
                    }
                    else if (pattern_type == 2)
                    {
                        if (((i + j) / diamound_size) % 2 == 0)
                        {
                            apply_first_color = true;
                        }
                    }
                    if (apply_first_color)
                    {
                        img(i, j, 0) = r1;
                        img(i, j, 1) = g1;
                        img(i, j, 2) = b1;
                    }
                    else
                    {
                        img(i, j, 0) = r2;
                        img(i, j, 1) = g2;
                        img(i, j, 2) = b2;
                    }
                }
            }
        }
    }
    cout << "Frame filter applied successfully!\n";
}
void apply_resize_image_filter(Image& img)
{
    int new_width, new_height;
    cout << "Enter New Width and Height: \n";
    cin >> new_width >> new_height;
    Image new_img(new_width, new_height);
    double x_ratio = (double)img.width / new_width;
    double y_ratio = (double)img.height / new_height;
    for (int i = 0; i < new_width; i++)
    {
        for (int j = 0; j < new_height; j++)
        {
            int old_i = i * x_ratio;
            int old_j = j * y_ratio;
            new_img(i, j, 0) = img(old_i, old_j, 0);
            new_img(i, j, 1) = img(old_i, old_j, 1);
            new_img(i, j, 2) = img(old_i, old_j, 2);
        }
    }
    img = new_img;
    cout << "Resize filter applied successfully!\n";
}
//================================================================================//
int main()
{
    Image current_image;
    Image original_image;
    int choice;
    string file_name;

    while (true)
    {
        show_menu(); // menu function
        cin >> choice;
        if (choice == 0) // exit
        {
            cout << "program is ended" << "\n";
            break;
        }
        else if (choice == 1) // load
        {
            cout << "===========\n"
                << "load option\n"
                << "===========\n";

            cout << "enter name of image with extension" << "\n";
            cout << "supported format in this program : JPEG / JPG / PNG / BMP " << "\n";
            cin >> file_name;
            if (current_image.loadNewImage(file_name))
            {
                cout << "Image loaded successfully\n";
                original_image = current_image;
            }
            else
            {
                cout << "failed to load image please try again\n";
            }
        }
        else if (choice == 2) // grayscale
        {
            Grayscale_Conversion(current_image);
        }
        else if (choice == 3) // black and white filter
        {
            black_white(current_image);
        }
        else if (choice == 4) // Inversion Filter
        {
            invert_image(current_image);
        }
        else if (choice == 5) // frame filter
        {
            apply_framefilter(current_image);
        }
        else if (choice == 6) // flip image
        {
            int x;
            cout << "==========================================\n";
            cout << "if you want flip it Horizontally put 1\n"
                << "======================================\n"
                << "if you want flip it Vertically put 2\n"
                << "======================================\n";
            cin >> x;
            Flip_Image(x, current_image);
        }
        else if (choice == 7) // rotate image
        {
            Rotate_Image(current_image);
        }
        else if (choice == 8) // Apply the Darken/Lighten Filter
        {
            Darken_or_lighten_image(current_image);
        }
        else if (choice == 9) // resize filter
        {
            apply_resize_image_filter(current_image);
        }
        else if (choice == 10) // save
        {
            cout << "===========\n"
                << "save option\n"
                << "===========\n";
            save_image(current_image, file_name);
        }
        else if (choice == 11) // reset
        {
            cout << "===========\n"
                << "reset option\n"
                << "===========\n";
            current_image = original_image;
            cout << "original image restored successfull\n";
        }
    }
    return 0;
}
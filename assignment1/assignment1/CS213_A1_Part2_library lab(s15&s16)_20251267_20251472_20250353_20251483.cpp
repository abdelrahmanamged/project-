/*
================================================================================================================================

Description:    This program is an image processing application implemented in C++ utilizing the "Image_Class.h" library.
                It operates directly at the pixel level by iterating through each pixel across the image grid and performing
                various operations—such as manipulating RGB color channel values, thresholding, and rearranging pixel spatial
                coordinates to produce 8 distinct filters: Grayscale, Black & White, Inversion, Framing, Flipping,
                Rotation, Brightness Adjustment (Darken/Lighten), and Resizing.


--------------------------------------------------------------------------------------------------------------------------------
Team Details:
        Name                     ID                 Section                     Filters
--------------------------------------------------------------------------------------------------------------------------------
 1. Omar Ayman Mohamed        20251267       Library Lab (S15, S16)            Filter 2 and Filter 6 Filter 10 and Filter 14 and menu

 2. Abdelrahman Amgd Mosad    20250353       Library Lab (S15, S16)            Filter 1 and Filter 5 Filter 9 and Filter 13

 3. Yassine Awadallah Bakry   20251483       Library Lab (S15, S16)            Filter 4 and Filter 8 Filter 12 and Filter 16

 4. Hesham Waleed Fawzi       20251472       Library Lab (S15, S16)            Filter 3 and Filter 7 Filter 11 and Filter 15


--------------------------------------------------------------------------------------------------------------------------------
Drive Link: https://drive.google.com/drive/folders/1P8NzdlLUSTNO3rtDvzyjUo6f3KjLUWlW?usp=sharing


================================================================================================================================
*/
#include <string>
#include <iostream>
#include "Image_Class.h"
#include <cmath>
#include <algorithm>
#include <cstdlib>
using namespace std;

void show_menu()
{
    cout << "======================================================\n";
    cout << "           Welcome to our Program          \n";
    cout << "======================================================\n";
    cout << " [0]  Exit Program\n";
    cout << " [1]  Load Image\n";
    cout << " [2]  Apply Filter: Grayscale Conversion\n";
    cout << " [3]  Apply Filter: Black and White\n";
    cout << " [4]  Apply Filter: Invert Image \n";
    cout << " [5]  Apply Filter: Adding a Frame to the Picture\n";
    cout << " [6]  Apply Filter: Flip Image (Horizontal / Vertical)\n";
    cout << " [7]  Apply Filter: Rotate Image (90 / 180 / 270)\n";
    cout << " [8]  Apply Filter: Darken and Lighten Image\n";
    cout << " [9]  Apply Filter: Resizing Image\n";
    cout << " [10] Apply Filter: Merge Images\n";
    cout << " [11] Apply Filter: Wano-like Sunlight\n";
    cout << " [12] Apply Filter: Detect Image Edges\n";
    cout << " [13] Apply Filter: Den Den Mushi TV Image Filter\n";
    cout << " [14] Apply Filter: Crop Images\n";
    cout << " [15] Apply Filter: Purple Filter\n";
    cout << " [16] Apply Filter: Blur Images\n";
    cout << " [17] Apply Filter: Infrared Photography\n";
    cout << " [18] Save Image\n";
    cout << " [19] Reset Image to Original State\n";
    cout << "======================================================\n";
    cout << "Enter your choice: ";
}

void save_image(Image &current_image, string &original_filename)
{
    cout << "If you want to save the changes in the same image (that will modify your image), enter 1" << "\n";
    cout << "If you want to save the changes in a new image (that will make a copy while preserving your original image), enter 2\n";
    int choice;
    cout << "Enter your choice\n";
    cin >> choice;
    if (choice == 1)
    {
        if (current_image.saveImage(original_filename))
        {
            cout << "The image has been saved successfully to " << original_filename << "\n";
        }
        else
        {
            cout << "Failed to save " << original_filename << ". Please try again.\n";
        }
    }
    if (choice == 2)
    {
        string new_filename;
        cout << "Enter the name you want for the new image including the extension. (Example: imagename.png)" << "\n";
        cout << "Supported formats by this program are: jpeg / jpg / png / bmp" << "\n";

        cin >> new_filename;

        if (current_image.saveImage(new_filename))
        {
            cout << "Image has been saved successfully to " << new_filename << ".\n";
        }
        else
        {
            cout << "Failed to save " << new_filename << ". Please try again." << "\n";
        }
    }
}

//************************************************************************************************************//
// #################################### Hesham Waleed 20251472 ###############################################//
void Darken_or_lighten_image(Image &current_image)
{
    cout << "Do you want to darken or lighten the image?\nEnter 0 to darken or 1 to lighten.\n";
    bool dark_or_light_choice = 0;
    cin >> dark_or_light_choice;
    if (dark_or_light_choice)
    {
        cout << "On a scale of 0 to 100, what is the level of lightening do you wish for? (in percents)\n(0 means no change and 100 means double the lightening)\n";
        int level = 0;
        while (true)
        {
            cin >> level;
            if (level >= 0 && level <= 100)
                break;
            else
                cout << "Please enter a valid level. No negative numbers. The maximum is 100.\n";
        }
        for (int x = 0; x < current_image.width; x++)
        {
            for (int y = 0; y < current_image.height; y++)
            {
                for (int c = 0; c < 3; c++)
                {
                    int temp = current_image(x, y, c) * (1 + level / 100.0); // use a temporary integer variable to avoid the overflow for the unsigned character.
                    if (temp > 255)
                        temp = 255;
                    current_image(x, y, c) = temp;
                }
            }
        }
        cout << "The image has been lightened by " << level << "% successfully.\n";
    }
    else
    {
        cout << "On a scale of 0 to 100, what is the level of darkening do you wish for? (in percents)\n(0 means no change and 100 means double the darkening)\n";
        int level = 0;
        while (true)
        {
            cin >> level;
            if (level >= 0 && level <= 100)
                break;
            else
                cout << "Please enter a valid level. No negative numbers. The maximum is 100.\n";
        }
        for (int x = 0; x < current_image.width; x++)
        {
            for (int y = 0; y < current_image.height; y++)
            {
                for (int c = 0; c < 3; c++)
                {
                    current_image(x, y, c) *= (1 - level / 100.0); // either way, it's never gonna be negative. A check would just be useless.
                }
            }
        }
        cout << "The image has been darkened by " << level << "% successfully.\n";
    }
}

void invert_image(Image &current_image)
{
    for (int x = 0; x < current_image.width; x++)
    {
        for (int y = 0; y < current_image.height; y++)
        {
            for (int c = 0; c < 3; c++)
            {
                current_image(x, y, c) = 255 - current_image(x, y, c);
            }
        }
    }
    cout << "Inversion Filter has successfully been applied.\n";
}

void crop_image(Image &current_image)
{
    int crop_x, crop_y, crop_width, crop_height;
    cout << "Enter the point for the top-left corner of the region you want to crop. (Example: 155 4)\n";
    while (true)
    { // Input loop for extra validation for X and Y.
        cin >> crop_x >> crop_y;
        if (crop_x >= 0 && crop_x <= current_image.width - 1 && crop_y >= 0 && crop_y <= current_image.height - 1)
        {
            break;
        }
        cout << "Please enter a valid point. Both X and Y have to be non-negative numbers that are smaller than the width and the height of the original picture respectively.\n";
    }
    cout << "Enter the width and height (in pixels) for the region you want to crop. (Example: 20 5 will crop a 20x5 rectangle from the top-left corner you specified above)\n";
    while (true)
    { // Input loop for extra validation for width and height
        cin >> crop_width >> crop_height;
        if ((crop_x + crop_width <= current_image.width) && (crop_y + crop_height <= current_image.height) && crop_width > 0 && crop_height > 0)
        { // original condition: (crop_x + crop_width - 1 <= current_image.width - 1) && (crop_y + crop_height - 1 <= current_image.height - 1) but this is just simplified.
            break;
        }
        cout << "The cropped area dimensions can't exceed the original image's dimensions. The width and height can't be zero either. Please enter a valid width and height for the top-left corner you specified above.\n";
    }

    Image new_Image(crop_width, crop_height);

    for (int i = 0; i < crop_width; i++)
    {
        for (int j = 0; j < crop_height; j++)
        {
            for (int c = 0; c < 3; c++)
            {
                new_Image(i, j, c) = current_image(crop_x + i, crop_y + j, c);
            }
        }
    }
    current_image = new_Image;
    cout << "The image has been cropped successfuly.\n";
}

void purple_image(Image &current_image)
{
    for (int x = 0; x < current_image.width; x++)
    {
        for (int y = 0; y < current_image.height; y++)
        {
            int r, g, b;
            r = current_image(x, y, 0) * 1.1; // Scale up the Red channel
            g = current_image(x, y, 1) * 0.8; // Scale down the Green channel
            b = current_image(x, y, 2) * 1.2; // Scale up the Blue channel.
            if (r > 255)
                r = 255;
            if (b > 255)
                b = 255;

            current_image(x, y, 0) = r;
            current_image(x, y, 1) = g;
            current_image(x, y, 2) = b;
        }
    }
    cout << "The purple filter has been applied successfully.\n";
}

//************************************************************************************************************//
// #################################### Abdelrahman Amgd 20250353 #############################################//
void Grayscale_Conversion(Image &image)
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
    cout << "Grayscale Conversion filter has been applied successfully.\n";
}

void Flip_Image(int x, Image &image)
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
        cout << "The image has been flipped horizontally successfully.\n";
    }
    else if (x == 2)
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
        cout << "The image has been flipped vertically successfully.\n";
    }
}
void merge_image(Image &current_image, Image &second)
{
    int x;
    cout << "===========================================================\n";
    cout << "Enter 0 to resize both images to the biggest size and merge\n";
    cout << "===========================================================\n";
    cout << "Enter 1 to merge the common (smaller) area only\n";
    cout << "===========================================================\n";
    cout << "Enter your choice: ";
    cin >> x;
    if (x == 0)
    {
        int w = max(current_image.width, second.width);
        int h = max(current_image.height, second.height);
        Image result(w, h);
        for (int i = 0; i < w; i++)
        {
            for (int j = 0; j < h; j++)
            {
                int x1, x2, y1, y2;
                x1 = (i * current_image.width) / w;
                y1 = (j * current_image.height) / h;
                x2 = (i * second.width) / w;
                y2 = (j * second.height) / h;

                for (int k = 0; k < 3; k++)
                {
                    result(i, j, k) = (current_image(x1, y1, k) + second(x2, y2, k)) / 2;
                }
            }
        }

        current_image = result;
    }

    else if (x == 1)
    {
        int w = min(current_image.width, second.width);
        int h = min(current_image.height, second.height);
        Image result(w, h);
        for (int i = 0; i < w; i++)
        {
            int avg1 = 0, avg2 = 0, avg3 = 0;
            for (int j = 0; j < h; j++)
            {
                int red1, red2, blue1, blue2, green1, green2;
                for (int k = 0; k < 3; k++)
                {
                    red1 = current_image(i, j, 0);
                    green1 = current_image(i, j, 1);
                    blue1 = current_image(i, j, 2);
                }
                for (int k = 0; k < 3; k++)
                {
                    red2 = second(i, j, 0);
                    green2 = second(i, j, 1);
                    blue2 = second(i, j, 2);
                }
                avg1 = (red1 + red2) / 2;
                avg2 = (green1 + green2) / 2;
                avg3 = (blue1 + blue2) / 2;
                for (int k = 0; k < 3; k++)
                {
                    result(i, j, 0) = avg1;
                    result(i, j, 1) = avg2;
                    result(i, j, 2) = avg3;cd cdlb
                }
            }
        }
        current_image = result;
    }
};
void The_LandofWano(Image &current_image)
{
    for (int i = 0; i < current_image.width; i++)
    {
        for (int j = 0; j < current_image.height; j++)
        {
            int red, green, blue;
            for (int k = 0; k < 3; k++)
            {
                red = current_image(i, j, 0);
                green = current_image(i, j, 1);
                blue = current_image(i, j, 2);
            }
            red += 40;
            green += 60;
            if (red >= 255)
                red = 255;
            if (green >= 255)
                green = 255;
            for (int k = 0; k < 3; k++)
            {
                current_image(i, j, 0) = red;
                current_image(i, j, 1) = green;
                current_image(i, j, 2) = blue;
            }
        }
    }
    cout << "The filter has been applied successfully.\n";
}

//--------------------------------------------------------------------------------------------//
// #################################### Omar Ayman 20251267 ###################################//
void black_white(Image &current_image)
{
    cout << "=======================\n"
         << "Filter: Black and White\n"
         << "=======================\n";
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
    cout << "The Black-and-White filter has been applied successfully.\n";
}

void Rotate_Image(Image &current_image)
{
    int choice;
    int w, h;
    w = current_image.width;
    h = current_image.height;
    cout << "=======================\n"
         << "Filter: Rotate Image \n"
         << "=======================\n";
    cout << "Please select the rotation angle:\n";
    cout << "Enter [1] for a 90-degree rotation\n";
    cout << "Enter [2] for a 180-degree rotation \n";
    cout << "Enter [3] for a 270-degree rotation \n";
    cout << "Enter your choice: ";
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
        cout << "=======================================================\n"
             << "The image has been rotated by 90 degrees successfully.\n"
             << "=======================================================\n";
    }
    else if (choice == 2)
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
        cout << "=======================================================\n"
             << "The image has been rotated by 180 degrees successfully.\n"
             << "=======================================================\n";
    }
    else if (choice == 3)
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
        cout << "=======================================================\n"
             << "The image has been rotated by 270 degrees successfully.\n"
             << "=======================================================\n";
    }
}
void Detect_Image_Edges(Image &current_image)
{
    cout << "=======================\n"
         << "Filter: Detect_Image_Edges \n"
         << "=======================\n";
    Image new_image(current_image.width, current_image.height);
    int identifier = 40; // Threshold
    // Convert to grayscale to remove colors and make edges easy to find.

    for (int i = 0; i < current_image.width; i++)
    {
        for (int j = 0; j < current_image.height; j++)
        {
            int avg = (current_image(i, j, 0) + current_image(i, j, 1) + current_image(i, j, 2)) / 3;
            for (int k = 0; k < 3; k++)
            {
                current_image(i, j, k) = avg;
            }
        }
    }

    for (int i = 0; i < current_image.width - 1; i++) // to avoid bpoundries
    {
        for (int j = 0; j < current_image.height - 1; j++) // to avoid bpoundries
        {
            int current_brightness = (current_image(i, j, 0) + current_image(i, j, 1) + current_image(i, j, 2)) / 3;            // level of brightness
            int right_brightness = (current_image(i + 1, j, 0) + current_image(i + 1, j, 1) + current_image(i + 1, j, 2)) / 3;  // level of brightness
            int bottom_brightness = (current_image(i, j + 1, 0) + current_image(i, j + 1, 1) + current_image(i, j + 1, 2)) / 3; // level of brightness
            int difference_x = abs(current_brightness - right_brightness);                                                      // compare brightness of current pixel and right pixel
            int difference_y = abs(current_brightness - bottom_brightness);                                                     // compare brightness of current pixel and bottom pixel
            int identifier1 = difference_x + difference_y;
            int final_color;
            if (identifier1 >= identifier) // identify pixel is edge or not
            {
                final_color = 0; // will execute it if it is edge
            }
            else
            {
                final_color = 255; // will execute it if it is not edge
            }
            for (int c = 0; c < 3; c++)
            {
                new_image(i, j, c) = final_color;
            }
        }
    }
    current_image = new_image;
    cout << "=======================================================\n"
         << "Filter: Detect Image Edges has been applied successfully.\n"
         << "=======================================================\n";
}
void old_tv_image(Image &current_image)

{
    cout << "======================================\n"
         << "Filter: Old Den Den Mushi Televisions\n"
         << "======================================\n";
    for (int i = 0; i < current_image.width; i++)
    {
        for (int j = 0; j < current_image.height; j++)
        {
            // Generate a small random noise inside range [-20, 20]
            // [rand() % 41] gives random value from  0 to 40 then subtracting 20 shifts range to[-20,20]
            int noise = (rand() % 41) - 20;

            for (int c = 0; c < 3; c++)
            {
                int value = current_image(i, j, c);
                if (j % 2 == 0)
                {
                    value *= 0.4; // darken even rows by 60%
                }
                value += noise; // add the random noise to value of pixel to add noise to the pixels
                if (value > 255)
                    value = 255; // check point to protect the value from overflow
                if (value < 0)
                    value = 0; // check point to protect the value from underflow
                current_image(i, j, c) = value;
            }
        }
    }

    cout << "====================================================================\n"
         << "Filter: The Old Den Den Mushi Filter has been applied successfully.\n"
         << "====================================================================\n";
}

//************************************************************************************************************//
// ########################################## Yassine Bakry 20251483 ##########################################//
void apply_framefilter(Image &img)
{
    int frametype;
    cout << "*---Choose Frame Type---* \n";
    cout << "1. Simple Frame. \n";
    cout << "2. Fancy Frame. \n";
    cout << "Enter choice: ";
    cin >> frametype;
    int frame_size;
    cout << "Enter Frame Size: ";
    cin >> frame_size;
    if (frametype == 1)
    {
        int r, g, b;
        cout << "Enter Frame Color (R G B values from 0 to 255) (Example: Enter 0 0 0 for Black): ";
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
        cout << "Enter the first color (Pattern) (R G B values from 0 to 255): ";
        cin >> r1 >> g1 >> b1;
        cout << "Enter the second color (Background of Pattern) (R G B values from 0 to 255): ";
        cin >> r2 >> g2 >> b2;
        int square_size = 20;
        int pattern_type;
        cout << "*---Choose pattern type:---* \n";
        cout << "1. Checkers / Squares patterns. \n";
        cout << "2. Diamond pattern. \n";
        cout << "Enter your choice: ";
        cin >> pattern_type;
        int diamond_size = 20;

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
                        if (((i + j) / diamond_size) % 2 == 0)
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
    cout << "The Frame filter has been applied successfully!\n";
}

void apply_resize_image_filter(Image &img)
{
    int new_width, new_height;
    cout << "Enter the new width and height: ";
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
    cout << "The Resize Filter has been applied successfully!\n";
}
void apply_Blur_image_filter(Image &img)
{
    int kernel_size;
    cout << "Enter the blur intensity level (It must be an odd number like 3,5,7,...):\n";
    cin >> kernel_size;
    Image temporary_img = img;
    if (kernel_size <= 0 || kernel_size % 2 == 0)
    {
        cout << "Kernel Size Error: please enter a positive odd number.\n ";
    }
    else
    {
        for (int i = 0; i < img.width; i++)
        {
            for (int j = 0; j < img.height; j++)
            {
                int red = 0;
                int green = 0;
                int blue = 0;
                int count = 0;
                for (int n = i - (kernel_size / 2); n <= i + (kernel_size / 2); n++)
                {
                    for (int s = j - (kernel_size / 2); s <= j + (kernel_size / 2); s++)
                    {
                        if (n >= 0 && n < img.width && s >= 0 && s < img.height)
                        {
                            count++;
                            red += temporary_img(n, s, 0);
                            green += temporary_img(n, s, 1);
                            blue += temporary_img(n, s, 2);
                        }
                    }
                }
                img(i, j, 0) = red / count;
                img(i, j, 1) = green / count;
                img(i, j, 2) = blue / count;
            }
        }
        cout << "The Blur Image Filter has been applied sucssesfully.\n";
    }
}
void apply_infrared_filter(Image &img)
{
    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            img(i, j, 0) = 255;
            img(i, j, 1) = 255 - img(i, j, 1);
            img(i, j, 2) = 255 - img(i, j, 2);
        }
    }
    cout << "The Infrared Filter has been applied sucessfully.\n";
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
            cout << "Program has ended." << "\n";
            break;
        }
        else if (choice == 1) // load
        {
            cout << "===========\n"
                 << "Load Option\n"
                 << "===========\n";

            cout << "Enter the name of image including its extension (Example: image.jpg)" << "\n";
            cout << "Supported formats by this program are: jpeg / jpg / png / bmp " << "\n";
            cin >> file_name;
            if (current_image.loadNewImage(file_name))
            {
                cout << "Image loaded successfully.\n";
                original_image = current_image;
            }
            else
            {
                cout << "Failed to load image. Please try again.\n";
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
            cout << "======================================\n";
            cout << "If you want flip it horizontally, put 1\n"
                 << "======================================\n"
                 << "If you want flip it vertically, put 2\n"
                 << "======================================\n";
            cout << "Enter your choice: ";
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
        else if (choice == 10) // merge
        {
            cout << "Enter the name of the second image to load including its extension. (Example: image.png): " << "\n";
            Image second;
            string name;
            cin >> name;
            bool x = true;
            if (second.loadNewImage(name) == x)
            {
                cout << "==============================================";
                cout << "The second image has been loaded successfully.";
                cout << "==============================================" << "\n";
                merge_image(current_image, second);
            }
            else
            {
                cout << "Failed to load the second image.";
            }
        }
        else if (choice == 11) // land wano or sunlight
        {
            The_LandofWano(current_image);
        }
        else if (choice == 12) // Apply detect image
        {
            Detect_Image_Edges(current_image);
        }
        else if (choice == 13) // Apply old tv filter
        {
            old_tv_image(current_image);
        }
        else if (choice == 14) // Apply the Crop filter
        {
            crop_image(current_image);
        }
        else if (choice == 15) // Apply the purple filter
        {
            purple_image(current_image);
        }
        else if (choice == 16) // Apply blur filter
        {
            apply_Blur_image_filter(current_image);
        }
        else if (choice == 17)
        {
            apply_infrared_filter(current_image); // Apply infrared filter
        }

        else if (choice == 18) // save
        {
            cout << "===========\n"
                 << "Save Option\n"
                 << "===========\n";
            save_image(current_image, file_name);
        }
        else if (choice == 19) // reset
        {
            cout << "===========\n"
                 << "Reset Option\n"
                 << "===========\n";
            current_image = original_image;
            cout << "The original image has been restored successfully.\n";
        }
    }
    return 0;
}
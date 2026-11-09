/*
This is the image processing project phase two which consists of 15 filters

Team members:-
    1- Name: Ahmed Osama, ID: 20240012, Section: S25
    2- Name: Hassan Abdul-Moneim, ID: 20240163, Section: S25
    3- Name: Mohamed Motaz, ID: 20240529, Section: S28

Work breakdown:-
    1- Ahmed worked on filters 1, 4, 7, 10, and 14
    2- Hassan has worked on filters 2, 5, 8, 11, and 15 and implemented the menu, load, save, and apply_filter functions
    3- Mohamed has worked on filters 3, 6, 9, 12, and 13

Links:-
    GitHub repository link: https://github.com/ahmedosama20240012/image_processing_101
    Project Document link: https://docs.google.com/document/d/1KZosmdwqfEPodZUQJZ90tdNnU80y3pm4k89by-sO694/edit?usp=sharing
    Video link: https://youtu.be/SjXj6ia4mZM
*/

#include <iostream>
#include "Image_Class.h"
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

Image edited_image;
string current_filename;

Image greyscale(Image image)
{

  for (int i = 0; i < image.width; ++i) {

    for (int j = 0; j < image.height; ++j) {

      unsigned int avg = 0;
      int total = 0;

      for (int k = 0; k < image.channels; ++k) {
        total += image(i, j, k);
      }

      avg = total/3;

      image(i, j, 0) = avg;
      image(i, j, 1) = avg;
      image(i, j, 2) = avg;
    }

  }

  return image;
}

Image black_and_white(Image image)
{
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int sum = 0, average = 0;

            for (int k = 0; k < 3; k++) {
                sum += image(i, j, k);
            }

            average = sum / 3;

            if (average >= 100) {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
            else {
                image(i, j, 0) = 0;
                image(i, j, 1) = 0;
                image(i, j, 2) = 0;
            }
        }
    }

    return image;
}

Image Inverted(Image img)
{

    for (int i=0; i<img.width;++i){
        for (int j=0; j<img.height;++j){
            unsigned int red=0,green=0,blue=0;

            red=img(i,j,0);
            green=img(i,j,1);
            blue=img(i,j,2);
            img(i,j,0) = 255-red;
            img(i,j,1) = 255-green;
            img(i,j,2) = 255-blue;
        }
    }

    return img;
}

Image merge(Image img1, Image img2)
{

  Image out_img(min(img1.width, img2.width), min(img1.height, img2.height));

  if (img1.width != img2.width || img1.height != img2.height) {

    for (int i = 0; i < min(img1.width,img2.width); ++i) {
      for (int j = 0; j < min(img1.height, img2.height); ++j) {
        for (int k = 0; k < img1.channels; ++k) {

          out_img(i, j ,k) = (img1(i, j, k) + img2(i, j, k))/2;
        }
      }
    }

    return out_img;
  }
  else {

    for (int i = 0; i < img1.width; ++i) {
      for (int j = 0; j < img1.height; ++j) {
        for (int k = 0; k < img1.channels; ++k) {

          out_img(i, j, k) = (img1(i, j, k) + img2(i, j, k))/2;

        }
      }
    }

    return out_img;

  }

}

Image flip_image_vertically(Image &image)
{
    int width = image.width, height = image.height;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height / 2; j++) {
            for (int k = 0; k < 3; k++) {
                // Swap pixel at (i, j) with pixel at (i, height - j - 1)
                int temp = image(i, j, k);
                image(i, j, k) = image(i, height - j - 1, k);
                image(i, height - j - 1, k) = temp;
            }
        }
    }

    return image;
}

Image flip_image_horizontally(Image &image)
{
    int width = image.width, height = image.height;

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width / 2; i++) {
            for (int k = 0; k < 3; k++) {
                int temp = image(i, j, k);
                image(i, j, k) = image(width - i - 1, j, k);
                image(width - i - 1, j, k) = temp;
            }
        }
    }

    return image;
}

Image flip_image(Image image)
{
    cout << "Choose whether you want to flip it vertically or horizontally:\n"
         << "1) Vertical flip\n"
         << "2) Horizontal flip\n"
         << "Enter your choice: ";

    int choice = -1;
    cin >> choice;

    while (!(1 <= choice && choice <= 2)) {
        cout << "Invalid input. Try again\n";
        cin >> choice;
    }

    if (choice == 1)
        return flip_image_vertically(image);
    else
        return flip_image_horizontally(image);
}

Image Rotate(Image img)
{
    string outfile;
    int degree=0;
    while (degree != 90 && degree != 180 && degree != 270) {
        cout << "How many degrees do you want to rotate? (90, 180, 270): ";
        cin >> degree;
        if (degree != 90 && degree != 180 && degree != 270) {
            cout << "Invalid input. Please enter 90, 180, or 270." << endl;
        }
    }
    int w = img.width;
    int h = img.height;
    switch (degree) {
        case 90: {
            Image ninty(h, w);

            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    for (int c = 0; c < 3; c++) {
                        ninty(h - 1 - j, i,c) = img(i, j,c);
                    }
                }
            }

            return ninty;
        }
        case 180: {
            Image hundred(w,h);
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    for (int k = 0; k < 3; k++) {
                        hundred(w-1-i,h-1-j,k)=img(i,j,k);
                    }
                }
            }

            return hundred;
        }
        case 270:{
            Image twohundred(h,w);
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    for (int k = 0; k < 3; k++) {
                        twohundred(j,w-1-i,k)=img(i,j,k);
                    }
                }
            }

            return twohundred;
        }
        default:
            cout << "Invalid degree input." << endl;
        return img;
    }
}

Image darker(Image image)
{
    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            for (int k = 0; k < 3; k++) {
                image(i, j, k) = image(i, j, k)/2;
            }
        }
    }

    return image;
}

Image lighter(Image image)
{
    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            for (int k = 0; k < 3; k++) {

                if (image(i, j, k)*1.5 <= 255) {

                    image(i, j, k) = image(i, j, k)*1.5;
                }
                else {
                    image(i, j, k) = 255;
                }
            }
        }
    }

    return image;
}

Image brightness(Image image)
{
    cout << "Choose whether you want to make image darker or lighter \n"
        << "1) Darker\n"
        << "2) Lighter\n"
        << "Enter your choice: ";
    int choice = -1;
    cin >> choice;

    while (!(1 <= choice && choice <= 2)) {
        cout << "Invalid input. Try again\n";
        cin >> choice;
    }

    if (choice == 1)
        return darker(image);
    else
        return lighter(image);
}

Image crop(Image image)
{
    int row, col, width, height;

    cout << "Enter the row and column of the upper left corner ";
    cin >> row >> col;
    cout << "Enter the dimensions of the image you want to crop (width X height): ";
    cin >> width >> height;

    Image out_image(width, height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 3; k++) {
                out_image(j, i, k) = image(j + col - 1, i + row - 1, k);
            }
        }
    }

    return out_image;
}

Image Frame(Image &img, int s)
{
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            if (y < s || y >= img.height - s ||
                x < s || x >= img.width - s) {
                for (int c = 0; c < 3; c++) {
                    img(x,y,c)=0;
                }
                }
        }
    }

    return img;
}

Image edge_detection(Image& image)
{
    image = greyscale(image);
    Image edge_map(image.width, image.height);
    int threshold = 120;


    for (int i = 1; i  < image.width - 1; i++) {
        for (int j = 1; j  < image.height - 1; j++) {
            int Gx = -1 * image(i-1, j-1, 0) + 1 * image(i-1, j+1, 0) +
                     -2 * image(i,   j-1, 0) + 2 * image(i,   j+1, 0) +
                     -1 * image(i+1, j-1, 0) + 1 * image(i+1, j+1, 0);

            int Gy = -1 * image(i-1, j-1, 0) - 2 * image(i-1, j, 0) - 1 * image(i-1, j+1, 0) +
                      1 * image(i+1, j-1, 0) + 2 * image(i+1, j, 0) + 1 * image(i+1, j+1, 0);

            int G = abs(Gx) + abs(Gy);
            for (int k = 0; k < 3; k++) {


                edge_map(i, j, k) = (G >= threshold) ? 255 : 0;
            }
        }
    }

    return edge_map;
}

Image resize(Image image)
{
    int choice = -1;

    cout << "(1) Resize by new dimensions\n"
         << "(2) Resize by ratio\n"
         << "Enter your choice: ";

    cin >> choice;

    while (choice > 2 || choice < 1) {
        cout << "Invalid input. Try again\n";
        cin >> choice;
    }

    int old_width = image.width, old_height = image.height;
    int new_width, new_height;

    if (choice == 1) {
    cout << "Enter the new dimensions of the image (width X height): ";
    cin >> new_width >> new_height;
    }

    else {
        int New, Old;
        cout << "Enter the ratio (new / old): ";
        cin >> New >> Old;

        new_width = ((double) New / Old) * old_width;
        new_height = ((double) New / Old) * old_height;
    }

    Image out_image(new_width, new_height);

    for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < new_width; j++) {
            int old_row = ((double) old_height / new_height) * i;
            int old_col = ((double) old_width / new_width) * j;

            for (int k = 0; k < 3; k++) {
                out_image(j, i, k) = image(old_col, old_row, k);
            }
        }
    }

    return out_image;
}

Image Blur(const Image& img, int kernelSize)
{
    Image blurred = img;
    int m = kernelSize / 2;

    for (int x = m; x < img.width - m; ++x) {
        for (int y = m; y < img.height - m; ++y) {
            for (int c = 0; c < 3; ++c) {

                int total = 0;
                int count = 0;

                for (int dx = -m; dx <= m; ++dx) {
                    for (int dy = -m; dy <= m; ++dy) {
                        total += img(x + dx, y + dy, c);
                        count++;
                    }
                }

                blurred(x, y, c) = total / count;
            }
        }
    }

    return blurred;
}

Image Sunlight(Image& img)
{
    Image sunny (img.width, img.height);

    for (int x = 0; x < img.width; x++) {
        for (int y = 0; y < img.height; y++) {
            sunny(x, y, 0) = min(255, int(img(x, y, 0) * 1.35 ));
            sunny(x, y, 1) = min(255, int(img(x, y, 1) * 1.25 ));
            sunny(x, y, 2) = min(255, int(img(x, y, 2) * 0.75 ));
        }
    }

    return sunny;
}

Image oil_painting(Image& img)
{

    int radius = 3;
    int intensityLevels = 32;
    Image result(img.width, img.height);

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {

            vector<int> intensityCount(intensityLevels, 0);
            vector<int> sumR(intensityLevels, 0);
            vector<int> sumG(intensityLevels, 0);
            vector<int> sumB(intensityLevels, 0);

            for (int ny = -radius; ny <= radius; ny++) {
                for (int nx = -radius; nx <= radius; nx++) {

                    int px = clamp(x + nx, 0, img.width - 1);
                    int py = clamp(y + ny, 0, img.height - 1);

                    int r = img.getPixel(px, py, 0);
                    int g = img.getPixel(px, py, 1);
                    int b = img.getPixel(px, py, 2);

                    int intensity = ((r + g + b) * intensityLevels) / (3 * 255);
                    intensity = min(intensity, intensityLevels - 1);

                    intensityCount[intensity]++;
                    sumR[intensity] += r;
                    sumG[intensity] += g;
                    sumB[intensity] += b;
                }
            }

            int maxIndex = max_element(intensityCount.begin(), intensityCount.end()) - intensityCount.begin();
            int count =  intensityCount[maxIndex];

            result.setPixel(x, y, 0, sumR[maxIndex] / count);
            result.setPixel(x, y, 1, sumG[maxIndex] / count);
            result.setPixel(x, y, 2, sumB[maxIndex] / count);
        }
    }

    return result;
}

Image old_tv(Image image)
{
    bool turn = true;

    int class_width = image.height / 250;

    if (image.height < 250) {
        class_width = 1;
    }

    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            for (int k = 0; k < 3; k++) {
                if (i % class_width == 0) {
                    turn = !turn;
                }

                if (turn) {
                    image(j, i, k) = 0.6 * image(j, i, k);
                }

                else {
                      image(j, i, k) = 0.9 * image(j, i, k);
                }
            }
        }
    }

    return image;
}

void load()
{
    string filename;
    cout << "Enter file name with extension: ";
    cin >> filename;

    edited_image = Image(filename);
    current_filename = filename;

    cout << "Image has been loaded successfully\n" << endl;
}

void save (Image &image)
{
    int choice = -1;
    while (choice == -1) {
        cout << "(1) Save in the same image file" << endl;
        cout << "(2) Save as a new image" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        if (!(1 <= choice && choice <= 2)) {
            cout << "Invalid input, Try again\n";
            choice = -1;
        }
    }

    if (choice == 1){
        image.saveImage( current_filename);
    }

    else {
        string outfilename;
        cout << "Enter file name with extension: ";
        cin >> outfilename;

        image.saveImage( outfilename);
    }

    cout << "Image has been saved successfully\n" << endl;
}

void apply_filter()
{
    cout << "\n" << "Select filter:" << endl;
    cout << "(1) Gray scale" << endl;
    cout << "(2) Black-and-White" << endl;
    cout << "(3) Invert " << endl;
    cout << "(4) Merge" << endl;
    cout << "(5) Flip" << endl;
    cout << "(6) Rotate " << endl;
    cout << "(7) Edit brightness " << endl;
    cout << "(8) Crop " << endl;
    cout << "(9) Frame " << endl;
    cout << "(10) Detect edges " << endl;
    cout << "(11) Resize " << endl;
    cout << "(12) Blur " << endl;
    cout << "(13) Sunlight " << endl;
    cout << "(14) Oil Painting" << endl;
    cout << "(15) Old TV " << endl;
    cout << "Enter Your Choice (Number) : ";
    int choice=0;
    cin >> choice;
    while (!(1 <= choice && choice <= 15)) {
        cout << "Invalid input. Try again\n";
        cin >> choice;
    }

    if (choice == 1) {
        edited_image = greyscale(edited_image);
        cout << "Gray scale filter has been applied successfully\n" << endl;
    }

    else if (choice == 2) {
        edited_image = black_and_white(edited_image);
        cout << "Black and White filter has been applied successfully\n" << endl;
    }

    else if (choice == 3) {
        edited_image = Inverted(edited_image);
        cout << "Invert filter has been applied successfully\n" << endl;
    }

    else if (choice == 4) {
        string filename2;
        cout << "Enter the 2nd file name with extension: ";
        cin >> filename2;
        Image image2(filename2);
        edited_image = merge(edited_image, image2);
        cout << "Invert filter has been applied successfully\n" << endl;
    }

    else if (choice == 5) {
        edited_image = flip_image(edited_image);
        cout << "Flip filter has been applied successfully\n" << endl;
    }

    else if (choice == 6) {
        edited_image = Rotate(edited_image);
        cout << "Rotate filter has been applied successfully\n" << endl;
    }

    else if (choice == 7) {
        edited_image = brightness(edited_image);
        cout << "Broghtness has been edited successfully\n" << endl;
    }

    else if (choice == 8) {
        edited_image = crop(edited_image);
        cout << "Crop filter has been applied successfully\n" << endl;
    }

    else if (choice == 9) {
        int s;
        cout << "Please add the size of the frame: ";
        cin >> s;
        edited_image = Frame(edited_image,s);
        cout << "The Frame has been added successfully \n"<< endl;
    }

    else if (choice == 10) {
        edited_image = edge_detection(edited_image);
        cout << "Optimized Edge Detection completed successfully\n" << endl;
    }

    else if (choice == 11) {
        edited_image = resize(edited_image);
        cout << "Image has been resized successfully\n" << endl;
    }

    else if (choice == 12) {
        int size;
        cout << "Please enter the blur size (5,7,9):  ";
        cin >> size;
        edited_image = Blur(edited_image,size);
        cout << "Blur filter has been applied successfully.\n" << endl;
    }

    else if (choice == 13) {
        edited_image = Sunlight(edited_image);
        cout << "The Sunlight filter has been applied successfully\n"<<endl;
    }

    else if (choice == 14) {
        edited_image = oil_painting(edited_image);
        cout << "Oil Painting filter has been applied successfully.\n" << endl;
    }

    else {
        edited_image = old_tv(edited_image);
        cout << "Old TV filter has been applied successfully\n" << endl;
    }
}

int menu()
{
    int choice = -1;

    while (choice == -1) {

        cout << "Select option:" << endl;
        cout << "(1) Load a new image" << endl;
        cout << "(2) Apply a new filter" << endl;
        cout << "(3) Save image" << endl;
        cout << "(4) Quit Program " << endl;
        cout << "Enter Your Choice (Number) : ";

        cin >> choice;

        if (!(1 <= choice && choice <= 4)) {
            cout << "Invalid Choice" << endl;
            choice = -1;
        }
    }

    return choice;
}


int main(){
    bool first_choice = true;

    while (true) {
        int choice = menu();

        if (first_choice && (choice == 2 || choice == 3)) {
            cout << "You must load a new image first\n" << endl;
            continue;
        }

        else if (first_choice && choice == 1){
            first_choice = false;
        }

        if (choice == 1) {
            load();
        }

        else if (choice == 2) {
            apply_filter();
        }

        else if (choice == 3) {
            save(edited_image);
        }

        else {
            cout << "Quitting..." << endl;
            return 0;
        }
    }
}
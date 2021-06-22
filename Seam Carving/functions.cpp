#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

#define INFO(X) cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " = " << X << endl;

using namespace std;


Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // dlete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

int* createSeam(int length) {
  int* seam = new int [length];
  for (int i = 0; i < length; i++){
	  seam[i] = 0;
  }
  return seam;
}

void deleteSeam(int* seam) {
	delete [] seam;
	seam = nullptr;
}

bool loadImage(string filename, Pixel** image, int width, int height) {
  ifstream ifs (filename);
  
  // check if input stream opened successfully
  if (!ifs.is_open()) {
    cout << "Error: failed to open input file - " << filename << endl;
    return false;
  }
 
 char type[3];
 ifs >> type; // should be P3
 if ((toupper(type[0]) != 'P') || (type[1] != '3')) { // check that type is correct
    cout << "Error: type is " << type << " instead of P3" << endl;
    return false;
  }
  
  // get width (w) and height (h) from preamble
  int w = 0, h = 0;
  ifs >> w;
  if(ifs.fail()){
	cout << "Error: read non-integer value" << endl;
	return false;
  }
  ifs >> h;
  if(ifs.fail()){
	cout << "Error: read non-integer value" << endl;
	return false;
  }
  if (w != width) { // check that width matches what was passed into the function
    cout << "Error: input width ("<< width << ") does not match value in file (" << w << ")" << endl;
    return false;
  }
  if (h != height) { // check that height matches what was passed into the function
    cout << "Error: input height ("<< height << ") does not match value in file (" << h << ")" << endl;
    return false;
  }
  
  int colorMax = 0;
  ifs >> colorMax;
  if (ifs.fail()){
  	cout << "Error: read non-integer value" << endl;
	return false;
  }
  if (colorMax != 255) {
    cout << "Error: file is not using RGB color values." << endl;
    return false;
  }
  //int row_count =0;
  //int col_count =0;
  
  Pixel colors;
  int fullWidth = 0;
  int fullHeight = 0;
  
  for (int i = 0; i < height; i++){
	  fullHeight++;
	  fullWidth = 0;
	  for (int j = 0; j < width; j++){
		  fullWidth++;
		  ifs.clear();
		  ifs >> colors.r;
		  if (ifs.fail()){
			  cout << "Error: read non-integer value" << endl;
			  return false;
		  }		  
		  ifs >> colors.g;
		  if (ifs.fail()){
			  cout << "Error: read non-integer value" << endl;
			  return false;
		  }
		  ifs >> colors.b;
		  if (ifs.fail()){
			  cout << "Error: read non-integer value" << endl;
			  return false;
		  }
		  if (colors.b < 0 || colors.b > 255){
			  cout << "Error: invalid color value " << colors.b << endl;
			  return false;
		  }
		  else if (colors.g < 0 || colors.g > 255){
		  	  cout << "Error: invalid color value " << colors.g << endl;
			  return false;
		  }
		  else if (colors.r < 0 || colors.r > 255){
			  cout << "Error: invalid color value " << colors.r << endl;
			  return false;
		  }
		  else if ((fullWidth == width) && (fullHeight == height) && !ifs.eof()){
			  cout << "Error: too many color values" << endl;
		  }
		  else{
		  	  image[j][i] = colors;
		  }
		  if(ifs.eof() && (fullHeight != height) && (fullWidth != width)){
			  cout << "Error: not enough color values" << endl;
			  return false;
		  }
		}
  }
  return true;
}

bool outputImage(string filename, Pixel** image, int width, int height) {  ofstream ofs (filename);
  
  // check if output stream opened successfully
  if (!ofs.is_open()) {
    cout << "Error: failed to open output file - " << filename << endl;
    return false;
  }
  
  // output preamble
  ofs << "P3" << endl;
  ofs << width << " " << height << endl;
  ofs << 255 << endl;
  
  // output pixels
  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      ofs << image[col][row].r << " ";
      ofs << image[col][row].g << " ";
      ofs << image[col][row].b << " ";
    }
    ofs << endl;
  }
  return true;
}

int energy(Pixel** image, int column, int row, int width, int height) { 
//find adj pixels (since other method didnt work maybe try insturctions again)
// restarting due to a seg fault in part two :(
	int xR = 0;
	int xG = 0;
	int xB = 0;
	int yR = 0;
	int yG = 0;
	int yB = 0;
	int xEn = 0;
	int yEn = 0;
	int energy = 0;
//please work I wanna cry
	if (column == 0 && row == 0){
		xR = abs(image[column + 1][row].r - image[width -1][row].r);
		xG = abs(image[column + 1][row].g - image[width -1][row].g);
		xB = abs(image[column + 1][row].b - image[width -1][row].b);
		
		yR = abs(image[column][row + 1].r - image[column][height-1].r);
		yG = abs(image[column][row + 1].g - image[column][height-1].g);
		yB = abs(image[column][row + 1].b - image[column][height-1].b);
		

	}
	else if (column == 0 && row == height -1){
		xR = abs(image[column + 1][row].r - image[width -1][row].r);
		xG = abs(image[column + 1][row].g - image[width -1][row].g);
		xB = abs(image[column + 1][row].b - image[width -1][row].b);
		
		yR = abs(image[column][0].r - image[column][row -1].r);
		yG = abs(image[column][0].g - image[column][row -1].g);
		yB = abs(image[column][0].b - image[column][row -1].b);
		

	}
	else if (column == width -1 && row == 0){
		xR = abs(image[0][row].r - image[column -1][row].r);
		xG = abs(image[0][row].g - image[column -1][row].g);
		xB = abs(image[0][row].b - image[column -1][row].b);
		
		yR = abs(image[column][row + 1].r - image[column][height-1].r);
		yG = abs(image[column][row + 1].g - image[column][height-1].g);
		yB = abs(image[column][row + 1].b - image[column][height-1].b);
		

	}
	else if (column == 0){
		xR = abs(image[column + 1][row].r - image[width -1][row].r);
		xG = abs(image[column + 1][row].g - image[width -1][row].g);
		xB = abs(image[column + 1][row].b - image[width -1][row].b);
		
		yR = abs(image[column][row + 1].r - image[column][row -1].r);
		yG = abs(image[column][row + 1].g - image[column][row -1].g);
		yB = abs(image[column][row + 1].b - image[column][row -1].b);
		
	}
	else if (row == 0){
		xR = abs(image[column + 1][row].r - image[column -1][row].r);
		xG = abs(image[column + 1][row].g - image[column -1][row].g);
		xB = abs(image[column + 1][row].b - image[column -1][row].b);
		
		yR = abs(image[column][row + 1].r - image[column][height-1].r);
		yG = abs(image[column][row + 1].g - image[column][height-1].g);
		yB = abs(image[column][row + 1].b - image[column][height-1].b);
		
	}
	else if (column == width - 1 && row == height -1){
		xR = abs(image[0][row].r - image[column -1][row].r);
		xG = abs(image[0][row].g - image[column -1][row].g);
		xB = abs(image[0][row].b - image[column -1][row].b);
		
		yR = abs(image[column][0].r - image[column][row-1].r);
		yG = abs(image[column][0].g - image[column][row-1].g);
		yB = abs(image[column][0].b - image[column][row-1].b);
		
	}	
	else if (column == width - 1){
		xR = abs(image[0][row].r - image[column -1][row].r);
		xG = abs(image[0][row].g - image[column -1][row].g);
		xB = abs(image[0][row].b - image[column -1][row].b);
		
		yR = abs(image[column][row + 1].r - image[column][row-1].r);
		yG = abs(image[column][row + 1].g - image[column][row-1].g);
		yB = abs(image[column][row + 1].b - image[column][row-1].b);
		
	}
	else if (row == height-1){
		xR = abs(image[column + 1][row].r - image[column -1][row].r);
		xG = abs(image[column + 1][row].g - image[column -1][row].g);
		xB = abs(image[column + 1][row].b - image[column -1][row].b);
		
		yR = abs(image[column][0].r - image[column][row-1].r);
		yG = abs(image[column][0].g - image[column][row-1].g);
		yB = abs(image[column][0].b - image[column][row-1].b);
		
	}
	else 
	{
		xR = abs(image[column + 1][row].r - image[column -1][row].r);
		xG = abs(image[column + 1][row].g - image[column -1][row].g);
		xB = abs(image[column + 1][row].b - image[column -1][row].b);
		
		yR = abs(image[column][row + 1].r - image[column][row-1].r);
		yG = abs(image[column][row + 1].g - image[column][row-1].g);
		yB = abs(image[column][row + 1].b - image[column][row-1].b);

	}
	
	xEn = pow(xR,2) + pow(xB,2) + pow(xG, 2);
	yEn = pow(yR,2) + pow(yB,2) + pow(yG, 2);
		
	energy = xEn + yEn;	
	return energy;
		
	
}

int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
    // TODO(student): load a vertical seam
	int total_energy = energy(image, start_col, 0, width, height);
	seam[0] = start_col;
	int rightpos = 0;
	int leftpos = 0;
	int centerpos = 0;

	
	for (int i = 0; i < height; i++){
		if(start_col == 0){
			centerpos = energy(image, start_col, i , width, height);
			rightpos = energy(image, start_col + 1, i , width, height);
			leftpos = centerpos + rightpos;
		}
		else if (start_col == width -1){
			leftpos = energy(image, start_col - 1, i, width, height);
			centerpos = energy(image, start_col, i , width, height);
			rightpos = leftpos + centerpos;
		}
		else{
			leftpos = energy(image, start_col - 1, i, width, height);
			centerpos = energy(image, start_col, i, width, height);
			rightpos = energy(image, start_col + 1, i, width, height);
		}
		
		if (leftpos < centerpos && leftpos < rightpos){
			start_col -= 1;
			seam[i] = start_col;
			total_energy += leftpos;
		}
		else if (centerpos < leftpos && centerpos < rightpos){
			seam[i] = start_col;
			total_energy += centerpos;
		}		
		else if (rightpos < leftpos && rightpos < centerpos){
			start_col += 1;
			seam[i] = start_col;
			total_energy += rightpos;
		}
		else if (leftpos == centerpos && leftpos < rightpos){
			seam[i] = start_col;
			total_energy += centerpos;
		}
		else if (centerpos == rightpos && centerpos < leftpos){
			seam[i] = start_col;
			total_energy += centerpos;
		}
		else if (leftpos == rightpos && rightpos < centerpos){
			start_col += 1;
			seam[i] = start_col;
			total_energy += rightpos;
		}
		else if (leftpos == centerpos && centerpos == rightpos){
			seam [i] = start_col;
			total_energy += centerpos;
		}

		
		
	}

  return total_energy;
}

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
    // TODO(student): load a horizontal seam
    INFO(image);
    INFO(start_row);
    INFO(width);
    INFO(height);
    INFO(seam);
  return 0;
}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
    // TODO(student): find min vertical seam
	int* minSeam = new int[height];
	int* seam = new int [height];
	int minEnergy = 0;
	int currentEnergy = 0;
	
	minEnergy = loadVerticalSeam(image, 0, width, height, seam);
	
	for(int i = 1; i < width; i ++){
		currentEnergy = loadVerticalSeam(image, i, width, height, seam);
		if(currentEnergy < minEnergy){
			minEnergy = currentEnergy;
			
			for(int j = 0; j < height; j++){
				minSeam[j] = seam[j];
			}
		}
	}
	
	delete[] seam;
	seam = nullptr;
  return minSeam;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) {
    // TODO(student): find min horizontal seam
    INFO(image);
    INFO(width);
    INFO(height);
  return nullptr;
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
	Pixel tempPixel;
	
	for (int i = 0; i < height; i ++){
		tempPixel = image[verticalSeam[i]][i];
		for (int j = verticalSeam[i]; j < width - 1; j++ ){
			image[i][j] = image[i][j+1];
		}
		image[i][height - 1] = tempPixel;
	}
}

void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
    // TODO(student): remove a horizontal seam
    INFO(image);
    INFO(width);
    INFO(height);
    INFO(horizontalSeam);
}


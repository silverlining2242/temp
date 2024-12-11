#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <vector>
#include <iomanip> //for fixed precision

using namespace std;

int w, h, k;
int width, height;

void input(const char *infile, vector<vector<float>> &Dist, vector<vector<float>> &Mask)
{
  FILE *file = fopen(infile, "rb"); // Open file in binary mode
  if (!file)
  {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  // Read dimensions (h, w, k)
  fread(&h, sizeof(int), 1, file);
  fread(&w, sizeof(int), 1, file);
  fread(&k, sizeof(int), 1, file);

  width = w - k + 1;
  height = h - k + 1;

  // Resize 2D vectors
  Dist.resize(h, vector<float>(w));
  Mask.resize(k, vector<float>(k));

  // Allocate a 1D array for binary reading
  vector<float> flatDist(h * w);
  vector<float> flatMask(k * k);

  // Read flattened Dist and Mask
  fread(flatDist.data(), sizeof(float), h * w, file);
  fread(flatMask.data(), sizeof(float), k * k, file);

  // Map 1D array to 2D vector for Dist
  for (int i = 0; i < h; ++i)
  {
    for (int j = 0; j < w; ++j)
    {
      Dist[i][j] = flatDist[i * w + j];
    }
  }

  // Map 1D array to 2D vector for Mask
  for (int i = 0; i < k; ++i)
  {
    for (int j = 0; j < k; ++j)
    {
      Mask[i][j] = flatMask[i * k + j];
    }
  }
  // print check
  for (int i = 0; i < h; ++i)
  {
    for (int j = 0; j < w; ++j)
    {
      cout << Dist[i][j] << ' ';
    }
    cout << endl;
  }
  for (int i = 0; i < k; ++i)
  {
    for (int j = 0; j < k; ++j)
    {
      cout << Mask[i][j] << ' ';
    }
    cout << endl;
  }

  fclose(file);
}
void output(const char *outFileName, const vector<vector<float>> &Result)
{
  // Debugging output to console
  cout << "Result matrix (" << height << "x" << width << "):" << endl;
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      cout << fixed << setprecision(4) << Result[i][j] << ' ';
    }
    cout << endl;
  }

  // Open the binary file for writing
  FILE *outfile = fopen(outFileName, "wb");
  if (!outfile)
  {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  // Write the dimensions (height and width) to the file
  fwrite(&height, sizeof(int), 1, outfile);
  fwrite(&width, sizeof(int), 1, outfile);

  // Write the matrix data row by row
  for (int i = 0; i < height; ++i)
  {
    fwrite(Result[i].data(), sizeof(float), width, outfile);
  }

  fclose(outfile);
  cout << "Output written to file: " << outFileName << endl;
}

void Convolution(const vector<vector<float>> &Dist, const vector<vector<float>> &Mask, vector<vector<float>> &Result)
{
  // Initialize the result matrix
  Result.resize(height, vector<float>(width, 0));

  // Perform the convolution
  for (int i = 0; i < height; ++i)
  {
    for (int j = 0; j < width; ++j)
    {
      float sum = 0.0f;
      for (int ki = 0; ki < k; ++ki)
      {
        for (int kj = 0; kj < k; ++kj)
        {
          sum += Dist[i + ki][j + kj] * Mask[ki][kj];
        }
      }
      Result[i][j] = sum;
    }
  }
}

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    cerr << "Usage: ./conv <input_file> <output_file>" << endl;
    return EXIT_FAILURE;
  }

  vector<vector<float>> Dist, Mask, Result;

  // Input data
  input(argv[1], Dist, Mask);

  // Perform Convolution
  Convolution(Dist, Mask, Result);

  // Output results
  output(argv[2], Result);

  return EXIT_SUCCESS;
}

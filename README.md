# Image Processing Project

This project implements basic image processing operations on images in the TGA format, including reading and writing images, and performing various transformations and blend modes. The program can be run either by predefined tasks in the `main` function or through a command-line interface for additional customization.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Build and Compile](#build-and-compile)
- [Examples](#examples)

---

### Overview

This image processing application performs a series of transformations on images using the TGA file format. The program provides functionality to load, manipulate, and save images, with operations like addition, subtraction, multiplication, and blending techniques (screen, overlay).

### Features

The following features are implemented:

1. **Image Reading and Writing**: Supports reading and writing of TGA images.
2. **Pixel Manipulation**:
    - **Addition and Subtraction**: Adds or subtracts pixel values from two images.
    - **Multiplication**: Multiplies corresponding pixels of two images.
    - **Screen and Overlay Blending**: Applies screen and overlay blending effects between two images.
    - **Color Adjustment**: Modifies color channels with addition and scaling factors.
    - **Image Flip**: Reverses image pixels horizontally.
3. **Image Composition**: Combines color channels from different images to form a composite image.

### Usage

To use the command-line interface:
```bash
./project2.out [output_file] [first_image] [method] [...]
```

#### Commands

- **multiply**: Multiply pixel values between two images.
- **subtract**: Subtract pixel values of the second image from the first.
- **overlay**: Overlay blend mode between two images.
- **screen**: Screen blend mode between two images.
- **flip**: Flip the image horizontally.
- **onlyred, onlygreen, onlyblue**: Isolate a single color channel in an image.
- **addred, addgreen, addblue**: Add value to a specific color channel.
- **scalered, scalegreen, scaleblue**: Scale a specific color channel.

### Project Structure

- `image`: Contains the main class with functions for loading, writing, and transforming images.
- `main`: CLI entry point for performing image manipulations based on user input.

### Build and Compile

1. Clone the repository:
    ```]bash
    git clone <repository_link>
    cd <repository_folder>
    ```
2. Compile the program:
    ```bash
    g++ -o project2.out project2.cpp
    ```
3. Run with command-line arguments or modify tasks in `main` for customized use cases.

### Examples

1. **Multiply Layers**:
   ```cpp
   image layer1("layer1.tga");
   image pattern1("pattern1.tga");
   image *result;
   result = layer1.multiply(pattern1);
   result->writeImage("output.tga");
   ```

2. **Color Addition**:
   ```cpp
   image car("car.tga");
   car.addColor(0, 200, 0); // Adds green channel
   car.writeImage("part6.tga");
   ```

3. **Composite Channels**:
   Load individual red, green, and blue channels and combine them:
   ```cpp
   image red("layer_red.tga"), green("layer_green.tga"), blue("layer_blue.tga");
   // Composite to form RGB image and save
   ```

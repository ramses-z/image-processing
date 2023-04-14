#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;

};

class image {
    public:
    string filename;
    Header header;
    int imageSize;
    unsigned char* data;

    image () {
        header.idLength = 0;
        header.colorMapType = 0;
        header.dataTypeCode = 2;
        header.colorMapOrigin = 0;
        header.colorMapLength = 0;
        header.colorMapDepth = 0;
        header.xOrigin = 0;
        header.yOrigin = 0;
        header.width = 10;
        header.height = 10;
        header.bitsPerPixel = 24;
        header.imageDescriptor = 0;

        imageSize = (header.width * header.height);

        data = new unsigned char[imageSize * 3] {};
    }

    image (string filename_) {
        ifstream file("../input/" + filename_, ios::in | ios::binary);
        if (!file) {
            cout << endl << "Unable to open " << filename << endl;
            return;
        }
        
        filename = filename_;

        file.seekg(0, ios::beg);
        
        file.read((char*) &header.idLength, sizeof(unsigned char));
        file.read((char*) &header.colorMapType, sizeof(unsigned char));
        file.read((char*) &header.dataTypeCode, sizeof(unsigned char));
        file.read((char*) &header.colorMapOrigin, sizeof(unsigned short));
        file.read((char*) &header.colorMapLength, sizeof(unsigned short));
        file.read((char*) &header.colorMapDepth, sizeof(unsigned char));
        file.read((char*) &header.xOrigin, sizeof(unsigned short));
        file.read((char*) &header.yOrigin, sizeof(unsigned short));
        file.read((char*) &header.width, sizeof(unsigned short));
        file.read((char*) &header.height, sizeof(unsigned short));
        file.read((char*) &header.bitsPerPixel, sizeof(unsigned char));
        file.read((char*) &header.imageDescriptor, sizeof(unsigned char));

        imageSize = header.width * header.height;
        data = new unsigned char[imageSize * 3] {};
        file.read((char*) data, imageSize * 3);

        file.close();
    }

    void loadImage (string filename) {
        ifstream file("../input/" + filename, ios::in | ios::binary);
        if (!file) {
            cout << endl << "Unable to open " << filename << endl;
            return;
        }

        file.seekg(0, ios::beg);
        
        file.read((char*) &header.idLength, sizeof(unsigned char));
        file.read((char*) &header.colorMapType, sizeof(unsigned char));
        file.read((char*) &header.dataTypeCode, sizeof(unsigned char));
        file.read((char*) &header.colorMapOrigin, sizeof(unsigned short));
        file.read((char*) &header.colorMapLength, sizeof(unsigned short));
        file.read((char*) &header.colorMapDepth, sizeof(unsigned char));
        file.read((char*) &header.xOrigin, sizeof(unsigned short));
        file.read((char*) &header.yOrigin, sizeof(unsigned short));
        file.read((char*) &header.width, sizeof(unsigned short));
        file.read((char*) &header.height, sizeof(unsigned short));
        file.read((char*) &header.bitsPerPixel, sizeof(unsigned char));
        file.read((char*) &header.imageDescriptor, sizeof(unsigned char));

        int imageSize = header.width * header.height;
        data = new unsigned char[imageSize * 3] {};
        file.read((char*) data, imageSize * 3);

        // PRINT HEADER
        // cout << "id: " << (int) header.idLength << endl;
        // cout << "color map type: " << (int) header.colorMapType << endl;
        // cout << "image type: " << (int) header.dataTypeCode << endl;
        // cout << "color map origin: " << (int) header.colorMapOrigin << endl;
        // cout << "color map length: " << (int) header.colorMapLength << endl;
        // cout << "color map depth: " << (int) header.colorMapDepth << endl;
        // cout << "xorigin: " << (int) header.xOrigin << endl;
        // cout << "yorigin: " << (int) header.yOrigin << endl;
        // cout << "width: " << (int) header.width << endl;
        // cout << "height: " << (int) header.height << endl;
        // cout << "pixel depth: " << (int) header.bitsPerPixel << endl;
        // cout << "image descriptor: " << (int) header.imageDescriptor << endl;

        // PRINT PIXEL DATA
        // cout << "raw pixel data: " << endl;
        // for (int i = 0; i < imageSize * 3; i++)
        //     cout << (int) img.data[i] << ", ";

        file.close();

        return;
    }

    void writeImage (string filename) {
        ofstream file("../output/" + filename, ios::binary | ios::out);

        file.write((char*) &header.idLength, sizeof(header.idLength));
        file.write((char*) &header.colorMapType, sizeof(header.colorMapType));
        file.write((char*) &header.dataTypeCode, sizeof(header.dataTypeCode));
        file.write((char*) &header.colorMapOrigin, sizeof(header.colorMapOrigin));
        file.write((char*) &header.colorMapLength, sizeof(header.colorMapLength));
        file.write((char*) &header.colorMapDepth, sizeof(header.colorMapDepth));
        file.write((char*) &header.xOrigin, sizeof(header.xOrigin));
        file.write((char*) &header.yOrigin, sizeof(header.yOrigin));
        file.write((char*) &header.width, sizeof(header.width));
        file.write((char*) &header.height, sizeof(header.height));
        file.write((char*) &header.bitsPerPixel, sizeof(header.bitsPerPixel));
        file.write((char*) &header.imageDescriptor, sizeof(header.imageDescriptor));

        int imageSize = header.width * header.height;

        file.write((char*) data, imageSize * 3);
        file.close();
    }

    image* addition (image img) {
        image* out = new image;
        out = this;

        for (int i = 0; i < out -> imageSize * 3; i++) {
            if (out -> data[i] + img.data[i] > 255) {out -> data[i] = 255;}
            else {out -> data[i] += img.data[i];}
        }
        return out;
    }

    image* subtract (image img) {
        image* out = new image;
        out = this;

        for (int i = 0; i < out -> imageSize * 3; i++) {
            if (out -> data[i] - img.data[i] < 0) {out -> data[i] = 0;}
            else {out -> data[i] -= img.data[i];}
        }
        return out;
    }

    image* multiply (image img) {
        float N1, N2;
        image* out = new image;
        out = this;

        for (int i = 0; i < imageSize * 3; i++){
            N1 = (data[i] / 255.0);
            N2 = (img.data[i] / 255.0);
            out -> data[i] =  (N1 * N2 * 255.0 + 0.5f);
            if (out -> data[i] > 255) {out -> data[i] = 255;}
            else if (out -> data[i] < 0) {out -> data[i] = 0;}
        }
        return out;
    }

    image* screen (image img) {
        float N1, N2;
        image* out = new image;
        out = this;

        for (int i = 0; i < out -> imageSize * 3; i++) {
            N1 = (out -> data[i] / 255.0);
            N2 = (img.data[i] / 255.0);
            out -> data[i] = ((1 - ((1 - N1) * (1 - N2))) * 255) + 0.5f;
        }
        return out;
    }

    image* overlay (image img) {
        float N1, N2;
        image* out = new image;
        out = this;

        for (int i = 0; i < imageSize * 3; i++){
            N1 = (data[i] / 255.0);
            N2 = (img.data[i] / 255.0);
            if (N2 <= 0.5) {
                out -> data[i] = (2 * N1 * N2 * 255.0 + 0.5f);
            }
            else {
                out -> data[i] = ((1 - (2 * (1 - N1) * (1 - N2))) * 255.0 + 0.5f);
            }
            if (out -> data[i] > 255) {out -> data[i] = 255;}
            else if (out -> data[i] < 0) {out -> data[i] = 0;}
        }
        return out;

    }

    void addColor (int b, int g, int r) {
        for (int i = 0; i < imageSize * 3; i+=3) {
            if (data[i] + b > 255) {data[i] = 255;}
            else if (data[i] + b < 0) {data[i] = 0;}
            else {data[i] += b;}
            if (data[i+1] + g > 255) {data[i+1] = 255;}
            else if (data[i+1] + g < 0) {data[i+1] = 0;}
            else {data[i+1] += g;}
            if (data[i+2] + r > 255) {data[i+2] = 255;}
            else if (data[i+2] + r < 0) {data[i+2] = 0;}
            else {data[i+2] += r;}
        }
    }

    void scaleColor (int b, int g, int r) {
        for (int i = 0; i < imageSize * 3; i+=3) {
            if (data[i] * b > 255) {data[i] = 255;}
            else if (data[i] * b < 0) {data[i] = 0;}
            else {data[i] *= b;}
            if (data[i+1] * g > 255) {data[i+1] = 255;}
            else if (data[i+1] * g < 0) {data[i+1] = 0;}
            else {data[i+1] *= g;}
            if (data[i+2] * r > 255) {data[i+2] = 255;}
            else if (data[i+2] * r < 0) {data[i+2] = 0;}
            else {data[i+2] *= r;}
        }
    }

    void flip () {
        unsigned char* data_ = new unsigned char[imageSize * 3] {};
        for (int i = 0; i < imageSize * 3; i += 3) {
            data_[i] = data[imageSize * 3 - i-3];
            data_[i+1] = data[imageSize * 3 - i-2];
            data_[i+2] = data[imageSize * 3 - i-1];
        }
        data = data_;
        delete data_;
    }
};

bool isFile (string filename) {
    if (filename == "car.tga" ||
        filename == "circles.tga" ||
        filename == "layer_blue.tga" ||
        filename == "layer_green.tga" ||
        filename == "layer_red.tga" ||
        filename == "layer1.tga" ||
        filename == "layer2.tga" ||
        filename == "patter1.tga" ||
        filename == "pattern2.tga" ||
        filename == "text.tga" ||
        filename == "text2.tga") { return true; }
    else 
        return false;
}

bool isMethod (string name) {
    if (name == "multiply" || 
        name == "subtract" ||
        name == "overlay" ||
        name == "screen" ||
        name == "combine" ||
        name == "flip" ||
        name == "onlyred" ||
        name == "onlyblue" ||
        name == "addred" ||
        name == "addgreen" ||
        name == "addblue" ||
        name == "scalered" ||
        name == "scaleblue" ||
        name == "scalegreen") { return true; }
    else
        return false;

}

int main (int argc, char* argv[]) {
    
    // image car("car.tga");
    // image circles ("circles.tga");
    // image layer_blue ("layer_blue.tga");
    // image layer_green ("layer_green.tga");
    // image layer_red ("layer_red.tga");
    // image layer1 ("layer1.tga");
    // image layer2 ("layer2.tga");
    // image pattern1 ("pattern1.tga");
    // image pattern2 ("pattern2.tga");
    // image text ("text.tga");
    // image text2 ("text2.tga");
    
    // // task 1
    // layer1.loadImage("layer1.tga");
    // pattern1.loadImage("pattern1.tga");
    // image *t1;
    // t1 = layer1.multiply(pattern1);
    // t1 -> writeImage("part1.tga");

    // // task 2
    // car.loadImage("car.tga"); 
    // layer2.loadImage("layer2.tga");
    // image* t2;
    // t2 = car.subtract(layer2);
    // t2 -> writeImage("part2.tga");

    // // task 3
    // layer1.loadImage("layer1.tga");
    // pattern2.loadImage("pattern2.tga");
    // text.loadImage("text.tga");
    // image* t3;
    // t3 = text.screen(*(layer1.multiply(pattern2)));
    // t3 -> writeImage("part3.tga");

    // // task 4
    // layer2.loadImage("layer2.tga");
    // circles.loadImage("circles.tga");
    // pattern2.loadImage("pattern2.tga");
    // image* t4;
    // t4 = (layer2.multiply(circles)) -> subtract(pattern2);
    // t4 -> writeImage("part4.tga");

    // // task 5
    // layer1.loadImage("layer1.tga");
    // pattern1.loadImage("pattern1.tga");
    // image* t5;
    // t5 = layer1.overlay(pattern1);
    // t5 -> writeImage("part5.tga");

    // // task 6
    // car.loadImage("car.tga");
    // car.addColor(0, 200, 0);
    // car.writeImage("part6.tga");

    // // task 7
    // car.loadImage("car.tga");
    // car.scaleColor(0, 1, 4);
    // car.writeImage("part7.tga");

    // // task 8
    // image carB, carG, carR;
    // carB.loadImage("car.tga");
    // carG.loadImage("car.tga");
    // carR.loadImage("car.tga");
    
    // for (int i = 0; i < car.imageSize * 3; i += 3) {
    //     carB.data[i+1] = carB.data[i];
    //     carB.data[i+2] = carB.data[i];
    //     carG.data[i] = carG.data[i+1];
    //     carG.data[i+2] = carG.data[i+1];
    //     carR.data[i] = carR.data[i+2];
    //     carR.data[i+1] = carR.data[i+2];
    // }

    // carB.writeImage("part8_b.tga");
    // carG.writeImage("part8_g.tga");
    // carR.writeImage("part8_r.tga");

    // // task 9
    // layer_red.loadImage("layer_red.tga");
    // layer_green.loadImage("layer_green.tga");
    // layer_red.loadImage("layer_red.tga");
    // image t9 ("layer_green.tga");

    // cout << "test" << endl;
    // for (int i = 0; i < layer_red.imageSize * 3; i += 3) {
    //     t9.data[i] = layer_blue.data[i];
    //     t9.data[i+1] = layer_green.data[i];
    //     t9.data[i+2] = layer_red.data[i];
    // }

    // t9.writeImage("part9.tga");

    // // task 10
    // text2.loadImage("text2.tga");
    // text2.flip();
    // text2.writeImage("part10.tga");

    // CLI
    string helpMessage = "Project 2: Image Processing, Spring 2023\n\nUsage:\n    .project2.out [output] [firstImage] [method] [...]\n";

    if (argc < 3 || (argc == 3 && argv[1] == "--help")) {
        cout << helpMessage;
        return 0;
    }

    else if (argc == 3) {
        cout << "Invalid file name.";
        return 0;
    }

    else if (argc > 3) {
        if (isFile(argv[2])) {
            if (isMethod(argv[3])) {
                
            }
            else
                return 0;
        }
        else {
            cout << "Invalid file name.";
            return 0;
        }
    }

    return 0;
}
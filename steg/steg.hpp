#if !defined steg_hpp
#define      steg_hpp

#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <CImg.h>

std::string decode(const char* infile)
{
    using namespace std;
    cimg_library::CImg<unsigned char> img(infile);
    vector<char> msg;
    char current = '\0';
    unsigned char *pi = img.data(),
                  *pend = img.data() + img.size();
    unsigned int offset = 0;
    //copy(img.begin(), img.end(), ostream_iterator<unsigned char>(cout));
    while (pi < pend){
        switch(offset){
            case 0x80:
                if (current == '\0'){
                    return string(msg.begin(), msg.end());
                }
                msg.push_back(current);
                current = '\0';
            case 0:
                offset = 1;
                break;
            default:
                offset<<=1;
        }
        if (*pi & 1){
            current |= offset;
        }else{
            current &= ~offset;
        }
        ++pi;
    }
    return string(msg.begin(), msg.end());
}

void encode(const char* infile, const char* outfile, const char* msg)
{
    using namespace std;
    cimg_library::CImg<unsigned char> img(infile);
    unsigned char *pi = img.data(),
                  *pend = img.data() + img.size();
    unsigned int offset = 0;
    while (pi < pend){
        switch(offset){
            case 0x80:
                if (*msg == '\0'){
                    // copy(img.begin(), img.end(), ostream_iterator<unsigned char>(cout));
                    // All done!
                    img.save(outfile);
                    return;
                }
                ++msg;
            case 0:
                offset = 1;
                break;
            default:
                offset<<=1;
        }
        if (*msg & offset){
            *pi |= 1;
        }else{
            *pi &= 0xfe;
        }
        ++pi;
    }
    // Save what we can, even if it truncates the message.
    img.save(outfile);
}

#endif

# xml_xournal

Program that corrects the odd number of points in .xopp file. Usually that problem happens with files made with the beta App "Xournall++ Mobile". When trying to open those files in the Desktop application, the error "**XML Parser error: Wrong count of points**" appears and can't open the content. This app duplicate the last point of each stroke that has an odd number of point to make it even.

## Notice

first program in C++, use with caution

## Dependencies

* xmlstarlet
* g++
* pugixml

## Usage

```shell
cd xml_xournal
make
./script.sh <FILENAME>.xopp 

```

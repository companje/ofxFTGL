/* This version of ofxFTGL supports multi byte characters 
 * Rick Companje, 19-12-2011
 */

#pragma once
#include "ofMain.h"
#include <FTGL/ftgl.h>

class ofxFTGLFont {
public:
    
    bool 		loadFont(string filename, float fontsize = 10, bool _bAntiAliased = false, bool _bFullCharacterSet = false, bool makeContours = false);
    void 		setSize(int size);
    void 		setLineHeight(float height);
    ofRectangle getStringBoundingBox(string s, float x, float y);

    //functions below take in account multi byte characters
    void 		drawString(string s, float x, float y);
    string      getChar(string s, int pos);
    int         getLength(string s);
    int         getWidth(string s);
    
    FTFont*     font;
};


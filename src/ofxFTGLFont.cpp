#include "ofxFTGLFont.h"

bool ofxFTGLFont::loadFont(string filename, float fontsize, bool _bAntiAliased, bool _bFullCharacterSet, bool makeContours){
    font = new FTTextureFont(ofToDataPath(filename).c_str());
    font->Outset(0.0f, fontsize);
    
    font->CharMap(ft_encoding_unicode);
    
    if(font->Error()){
        ofLog(OF_LOG_ERROR, "error loading font");
        return false;
    }    
    
    if(!font->FaceSize(fontsize)){
        ofLog(OF_LOG_ERROR, "Failed to set size");
        return false;
    }
    return true;
}

void ofxFTGLFont::setSize(int size){
    font->FaceSize(size);
}

ofRectangle ofxFTGLFont::getStringBoundingBox(string s, float x, float y){
    FTBBox bbox = font->BBox(s.c_str());
    return ofRectangle(x + bbox.Lower().Xf(), y + bbox.Lower().Yf(), bbox.Upper().Xf(), bbox.Upper().Yf());
}

int ofxFTGLFont::getWidth(string s) {
    //FIXME: should also count spaces inside a string
    return getStringBoundingBox(s==" " ? "n" : s, 0, 0).width;
}

int ofxFTGLFont::getLength(string s) { //corrected for 3 bytes UTF-8 characters
    //count the number of special chars (3 bytes) in the string
    int total = 0;
    for (int i=0; i<s.length(); i++) {
        if (s.at(i)<0) total++;
    }
    total/=3; //3 bytes per special char
    return s.length()-total*2; //subtract 2 of the length for each special char
}

string ofxFTGLFont::getChar(string s, int pos) {
    string letter;
    int cur=0;
    
    for (int i=0; i<s.length(); i++) {
        letter += ofToString(s.at(i)); //add char to (multibyte) string 
        if (s.at(i)>0 || letter.size()>=3) {
            if (cur==pos) return letter;
            letter = "";
            cur++;
        }
    }
}

void ofxFTGLFont::drawString(string s, float x, float y){
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(1,-1,1);
    
    font->Render(s.c_str(), getLength(s), FTPoint(), FTPoint(), FTGL::RENDER_FRONT | FTGL::RENDER_BACK);
    glPopMatrix();
}

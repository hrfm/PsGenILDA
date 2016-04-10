#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0, 0, 0);
    ofSetFrameRate(60);
    
    receiver.setup(22222);
    
    etherdream.setup();
    etherdream.setPPS(30000);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    while(receiver.hasWaitingMessages()){
        
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        if( m.getAddress() == "/path" ){
            
            frames.empty();
            frames.clear();
            
            float step = 4.0f;
            ofVec2f beforeAnchor;
            
            vector<ofPolyline> * _lines = NULL;
            ofPolyline * _line = NULL;
            
            int i = 0;
            int pointCount = 0;
            
            while( i < m.getNumArgs() ){
                
                if( m.getArgType(i) == OFXOSC_TYPE_STRING ){
                    
                    string argStr = m.getArgAsString(i);
                    
                    if( argStr == "f" ){
                        if( _lines != NULL ){
                            frames.push_back(*_lines);
                        }
                        _lines = new vector<ofPolyline>();
                    }else if( argStr == "l" ){
                        if( _line != NULL ){
                            _lines->push_back(*_line);
                        }
                        _line = new ofPolyline();
                        pointCount = 0;
                    }
                    
                    i++;
                    continue;
                    
                }
                
                float x, y;
                ofVec2f anchor, left, right;
                
                {
                    x = m.getArgAsFloat(i);
                    y = m.getArgAsFloat(i+1);
                    anchor = ofVec2f(x,y);
                }
                
                // 前の点がある場合はベジエ計算をする
                if( 0 < pointCount ){
                    {
                        x = m.getArgAsFloat(i-4);
                        y = m.getArgAsFloat(i-3);
                        left = ofVec2f(x,y);
                    }
                    {
                        x = m.getArgAsFloat(i+4);
                        y = m.getArgAsFloat(i+5);
                        right = ofVec2f(x,y);
                    }
                    
                    for( int i=0; i<step; i++ ){
                        float t = float(i)/step;
                        x = (1-t)*(1-t)*(1-t)*beforeAnchor.x + 3*(1-t)*(1-t)*t*left.x + 3*(1-t)*t*t*right.x + t*t*t*anchor.x;
                        y = (1-t)*(1-t)*(1-t)*beforeAnchor.y + 3*(1-t)*(1-t)*t*left.y + 3*(1-t)*t*t*right.y + t*t*t*anchor.y;
                        _line->addVertex(ofVec2f(x,y));
                    }
                    
                }
                
                _line->addVertex(anchor);
                beforeAnchor = anchor;
                pointCount++;
                
                i+=6;
                
            }
            
            if( _lines != NULL ){
                if( _line != NULL ){
                    _lines->push_back(*_line);
                }
                frames.push_back(*_lines);
            }
            
        }
        
    }
    
    if( 0 < frames.size() ){
        if( 4 <= ++count ){
            if( ++idx ){
                if( frames.size() <= idx ){
                    idx = 0;
                }
            }
            ildaFrame.clear();
            ildaFrame.addPolys( frames.at(idx) );
            count = 0;
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    string buf;
    buf = "Listening message form photoshop-generator on port : 222222";
    ofDrawBitmapString(buf, 10, 20);

    // do your thang
    ildaFrame.update();
    // draw to the screen
    ildaFrame.draw(0, 0, ofGetWidth(), ofGetHeight());
    // send points to the etherdream
    etherdream.setPoints(ildaFrame);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

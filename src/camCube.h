#pragma once

#include "ofMain.h"

#ifdef TARGET_ANDROID
#include "ofxAndroid.h"
#endif

#ifdef TARGET_ANDROID
  class camCube : public ofxAndroidApp {
#else
  class camCube : public ofBaseApp {
#endif
    
    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void windowResized(int w, int h);

        void touchDown(int x, int y, int id);
        void touchMoved(int x, int y, int id);
        void touchUp(int x, int y, int id);
        void touchDoubleTap(int x, int y, int id);
        void touchCancelled(int x, int y, int id);

        void pause();
        void stop();
        void resume();
        void reloadTextures();

        bool backPressed();
        void okPressed();
        void cancelPressed();

#ifdef TARGET_ANDROID
        void swipe(ofxAndroidSwipeDir swipeDir, int id);
#endif
    
        ofVec2f size;
        ofVec2f position;
        ofVec2f velocity;
        ofVec2f acceleration;
        ofVec2f spin;

        ofVideoGrabber video;
        ofImage image1;
        ofBoxPrimitive box;
        ofSpherePrimitive sphere;

    private:
        void applyForce(ofVec2f force);
        ofVec2f calculateFriction();
        void checkEdges();
};

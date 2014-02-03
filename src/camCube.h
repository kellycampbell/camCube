#pragma once

#include "ofMain.h"
#include "ofxAndroid.h"

class camCube : public ofxAndroidApp {

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void windowResized(int w, int h);


        // Some of these are Android specific TODO(kellyc): document which ones
        void touchDown(int x, int y, int id);
        void touchMoved(int x, int y, int id);
        void touchUp(int x, int y, int id);
        void touchDoubleTap(int x, int y, int id);
        void touchCancelled(int x, int y, int id);
        void swipe(ofxAndroidSwipeDir swipeDir, int id);

        void pause();
        void stop();
        void resume();
        void reloadTextures();

        bool backPressed();
        void okPressed();
        void cancelPressed();

        ofVec2f size;
        ofVec2f position;
        ofVec2f velocity;
        ofVec2f acceleration;
        ofVec2f spin;

        ofVideoGrabber video;
        ofImage image1;
        ofBoxPrimitive box;

    private:
        void applyForce(ofVec2f force);
        ofVec2f calculateFriction();
        void checkEdges();
};

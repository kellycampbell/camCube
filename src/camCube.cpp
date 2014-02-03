#include "camCube.h"


/**
 * This sets up the world, the shapes and textures, including initializing the front or back camera.
 *
 */
void camCube::setup() {
    ofEnableSmoothing(); // Smooth edges on our shapes.
    glEnable(GL_DEPTH_TEST); //enable depth comparisons so the cube looks right

    // Fixed framerate
    ofSetFrameRate(30);

    size = ofVec2f(320.0, 240.0);
    box = ofBoxPrimitive(size.x, size.y, size.x);
//    sphere = ofSpherePrimitive(size.x / 2, 24);


#ifdef TARGET_ANDROID
    video.setDeviceID(1); // Front facing camera is typically id #1 when there's 2 cameras.
#endif

    if (video.initGrabber(size.x, size.y)) {
        box.resizeToTexture(video.getTextureReference());
//        sphere.mapTexCoordsFromTexture(video.getTextureReference());
    } else {
        ofLog(OF_LOG_FATAL_ERROR, "Camera initialization failed");

        // Use an image resource if the camera didn't work.
        if (!image1.loadImage("city_hall_instagram.jpg")) {
            ofLog(OF_LOG_FATAL_ERROR, "City hall image loading failed.");
        }
        size = ofVec2f(200.0, 200.0);
        image1.resize(size.x, size.y);
        box.resizeToTexture(image1.getTextureReference());
//        sphere.mapTexCoordsFromTexture(image1.getTextureReference());
    }


    position = ofVec2f(0.0, 0.0);
    velocity = ofVec2f(0.0, 0.0);
    acceleration = ofVec2f(0.0, 0.0);
    spin = ofVec2f(0.0, 0.0);
}

/**
 * Apply a 2-dimensional vector force. Mass is a hard coded amount (1.0) for now.
 */
void camCube::applyForce(ofVec2f force) {
    float mass = 1.0;
    force = force / mass;
    acceleration += force;
}

/**
 * Calculates friction force based on the velocity normal.
 * Hard coded coefficient and normal force values.
 */
ofVec2f camCube::calculateFriction() {
    float cF = 0.1; // coefficient of friction
    float N = 1.0;  // normal force

    return -1 * cF * N * velocity.getNormalized();
}

/**
 * Checks location based on edges of window and reverses travel and spin direction when cube reaches edge.
 */
void camCube::checkEdges() {
    if (position.x > ofGetWindowWidth() - size.x) {
        position.x = ofGetWindowWidth() - size.y;
        velocity.x *= -1;
        spin.x *= -1;
    } else if (position.x < 0) {
        position.x = 0;
        velocity.x *= -1;
        spin.x *= -1;
    }
    if (position.y > ofGetWindowHeight() - size.y) {
        position.y = ofGetWindowHeight() - size.y;
        velocity.y *= -1;
        spin.y *= -1;
    } else if (position.y < 0) {
        position.y = 0;
        velocity.y *= -1;
        spin.y *= -1;
    }
}

/**
 * Applies forces and capture video frame.
 */
void camCube::update() {
    ofVec2f gravity = ofVec2f(0, 1.0);
    ofVec2f wind = ofVec2f(1.0, 1.0) * ofNoise(position.x, position.y);

    applyForce(gravity);
    applyForce(wind);
    applyForce(calculateFriction());

    // We just set the spin to a random value for now. No collision physics yet.
    spin = ofVec2f(1, 1) * ofNoise(ofGetFrameNum());

    velocity += acceleration;
    position += velocity;

    checkEdges();

    box.setPosition(position.x, position.y, 0);
    box.rotate(spin.x, 1.0, 0.0, 0.0);
    box.rotate(spin.y, 0, 1.0, 0.0);

    // Forces shouldn't accumulate.
    acceleration *= 0;

    if (video.isInitialized()) {
        video.update();
        if (video.isFrameNew()) {
            box.resizeToTexture(video.getTextureReference());
        }
    }
}

/**
 * Draw the frame.
 */
void camCube::draw() {
    ofBackgroundGradient(ofColor::gray, ofColor(30, 10, 30), OF_GRADIENT_CIRCULAR);
    ofSetColor(ofColor::white); // Needed in case image has an alpha channel.

    if (video.isInitialized()) {
        video.getTextureReference().bind();
    } else {
        image1.bind();
    }

    box.draw();

    if (video.isInitialized()) {
        video.getTextureReference().unbind();
    } else {
        image1.unbind();
    }

    // Add the fps to the top left corner.
    ofDrawBitmapString(ofToString(ofGetFrameRate()) + "fps", 10, 15);
}


//--------------------------------------------------------------
void camCube::keyPressed  (int key){ 

}

//--------------------------------------------------------------
void camCube::keyReleased(int key){ 

}

//--------------------------------------------------------------
void camCube::windowResized(int w, int h){

}

//--------------------------------------------------------------
void camCube::touchDown(int x, int y, int id){

}

//--------------------------------------------------------------
void camCube::touchMoved(int x, int y, int id){

}

//--------------------------------------------------------------
void camCube::touchUp(int x, int y, int id){

}

//--------------------------------------------------------------
void camCube::touchDoubleTap(int x, int y, int id){

}

//--------------------------------------------------------------
void camCube::touchCancelled(int x, int y, int id){

}

//--------------------------------------------------------------
void camCube::pause(){

}

//--------------------------------------------------------------
void camCube::stop(){

}

//--------------------------------------------------------------
void camCube::resume(){

}

//--------------------------------------------------------------
void camCube::reloadTextures(){

}

//--------------------------------------------------------------
bool camCube::backPressed(){
    return false;
}

//--------------------------------------------------------------
void camCube::okPressed(){

}

//--------------------------------------------------------------
void camCube::cancelPressed(){

}

#ifdef TARGET_ANDROID
//--------------------------------------------------------------
void camCube::swipe(ofxAndroidSwipeDir swipeDir, int id){
  
}
#endif

#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(15); // Limit the speed of our program to 15 frames per second
    
    // We still want to draw on a black background, so we need to draw
    // the background before we do anything with the brush
    ofBackground(255,255,255);
    ofSetLineWidth(4);
    
    draw_flag = 0;
    load_flag = 0;
    dot_diameter = 20.0f;
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(127,23,31);  // Set the drawing color to brown
    
    // Draw shapes for ceiling and floor
    ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
   
 
    
    
    //ofSetLineWidth(5);
    if (draw_flag) {

        //ofSetColor(ofColor::black);
        //ofDrawLine(50,700,80,700);
        int k, i;
        int j = 0;
        if (Rkey) { //오른쪽 방향 키보드가 눌려졌을 경우에 lx 배열에 x좌표가 40만큼 더해져서 저장됨.

            lx[j + 1] = lx[j] + Rkey * 40; 
            ofSetColor(ofColor::black);
            ofDrawLine(lx[j + 1], 700, lx[j + 1] + 40, 700); //길이는 40, 

            j++;
        }
        for (i = 0; i < num_of_dot; i++) {
            if (DS[i].button) {
                ofSetColor(ofColor::red);
                LaserOn(DS[i].x1, DS[i].y1); //선택된곳 레이저 발사
                if (DS[i].x1 == lx[j]) Die(); //막대기의 시작점과 레이저가 겹치면 죽어
            }
            else
                ofSetColor(ofColor::black);
            ofDrawCircle(DS[i].x1, DS[i].y1, 10);
        } //죽고싶으면 왼쪽방향키보드 누르면됨



        
            //ofDrawLine(0 + Rkey * 40, 700, 40 + Rkey * 40, 700); //누른만큼 막대기가 새로 이동


            //ofSetColor(ofColor::black);
            //ofDrawLine(LS[k].x1 - Lkey * 40, 700, LS[k].x1 + 40 - Rkey * 40, 700);
        
            //ofDrawLine(0 + Rkey * 40 - Lkey * 40, 700, 40 + Rkey * 40 - Lkey * 40, 700);


    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'v') {
        // HACK: only needed on windows, when using ofSetAutoBackground(false)
        glReadBuffer(GL_FRONT);
        ofSaveScreen("savedScreenshot_"+ofGetTimestampString()+".png");
    }
    if (key == 'q'){
        // Reset flags
        draw_flag = 0;
        
        // Free the dynamically allocated memory exits.
        
        cout << "Dynamically allocated memory has been freed." << endl;
        
        _Exit(0);
    }
    if (key == 'd'){
        if(!load_flag) return;
        draw_flag = 1;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == 'l' || key == 'L') {
        // Open the Open File Dialog
        ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a only txt for Waterfall");
        
        // Check whether the user opened a file
        if( openFileResult.bSuccess){
            ofLogVerbose("User selected a file");
            
            // We have a file, so let's check it and process it
            processOpenFileSelection(openFileResult);
            load_flag = 1;
        }
    }
 
    if (key == OF_KEY_RIGHT){
        if (Rkey == 24) {
            draw_flag = 0;
            cout << "Congratulations ! Today is a lucky day !" << endl;
            _Exit(0);
        }
        Rkey++;
        prev = curr;
        if (curr == num_of_dot - 1)
            curr = 0;
        else {
            curr = rand() % 12 + 1; // 오른쪽 방향키를 누를때마다 레이저 랜덤하게 발사됨
        }

        DS[curr].button = 1;
        DS[prev].button = 0;

        cout << "Selected Dot Coordinate is (" << DS[curr].x1 << ", " << DS[curr].y1 << ")" << endl;
   
    }
    if (key == OF_KEY_LEFT){
        Die(); //후진하면 죽음
    }
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

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) { 
    //Path to the comma delimited file
    //string fileName = "input.txt";
    
    int d = 0;
    string fileName = openFileResult.getName();
    ofFile file(fileName);
    
    if( !file.exists()) cout << "Target file does not exists." << endl;
    else cout << "We found the target file." << endl;
    ofBuffer buffer(file);
    int input_type = 1;

    // Read file line by line
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        
        // Split line into strings
        vector<string> words = ofSplitString(line, " ");
        
        if (words.size() == 1) {
            // Input for the number of dots.
            if (input_type == 1) {
                num_of_dot = atoi(words[0].c_str());
                cout << "The number of dot is: " << num_of_dot << endl;
                DS = new DotSource[num_of_dot];
            }
        }
        else if (words.size() >= 2) {
            // Input for actual information of dots.
            int x1 = atoi(words[0].c_str());
            int y1 = atoi(words[1].c_str());
            if (x1 >= 1024 || y1 >= 1024) continue;
            DS[d].x1 = x1;
            DS[d].y1 = y1;
            d++;
        }

    } // End of for-loop (Read file line by line).

    DS[0].button = 1;
    //initializeWaterLines();
}

// 아래 사용

void ofApp::LaserOn(int x1, int y1) {
    ofDrawLine(x1, y1, x1, 728);
    ofSetColor(ofColor::red);
    //laserflag.push(x1);
}

int ofApp::Die() {
    cout << "You Died!" << endl;
    _Exit(0);
}

/*
void ofApp::Swap(int arr[], int a, int b) // a,b 스왑 함수 
{
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

int ofApp::Partition(int arr[], int left, int right)
{
    int pivot = arr[left]; // 피벗의 위치는 가장 왼쪽에서 시작
    int low = left + 1;
    int high = right;

    while (low <= high) // 교차되기 전까지 반복한다 
    {
        while (low <= right && pivot >= arr[low]) // 피벗보다 큰 값을 찾는 과정 
        {
            low++; // low를 오른쪽으로 이동 
        }
        while (high >= (left + 1) && pivot <= arr[high]) // 피벗보다 작은 값을 찾는 과정 
        {
            high--; // high를 왼쪽으로 이동
        }
        if (low <= high)// 교차되지 않은 상태이면 스왑 과정 실행 
        {
            Swap(arr, low, high); //low와 high를 스왑 
        }
    }
    Swap(arr, left, high); // 피벗과 high가 가리키는 대상을 교환 
    return high;  // 옮겨진 피벗의 위치정보를 반환 

}


void ofApp::QuickSort(int arr[], int left, int right)
{
    if (left <= right)
    {
        int pivot = Partition(arr, left, right);
        QuickSort(arr, left, pivot - 1);
        QuickSort(arr, pivot + 1, right);
    }
}*/


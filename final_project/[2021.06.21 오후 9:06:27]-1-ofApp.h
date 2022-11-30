#pragma once

#include "ofMain.h"


class DotSource {
	public:
		int x1;
		int y1;
		bool button = 0;
};
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


    // flag variables
    int draw_flag;
    int load_flag;
	int water_flag;
    // Line segment and dot related variables
    int num_of_dot;
    float dot_diameter;

	int Rkey = 0; //오른쪽 방향키 눌린것 flag
	int Lkey = 0; //왼쪽 방향키 눌린것 flag

	stack <int> laserflag; // 레이저 발사한곳 x좌표저장
	int endflag = 0;
	int lx[25]; //밑바닥 직선의 개수 (직선길이 : 40  가로길이 1024 so 최대움직임 = 25
	int Die();
	//void Swap(int arr[], int a, int b);
	//int Partition(int arr[], int left, int right);
	//void QuickSort(int arr[], int left, int right);
	DotSource* DS;
	int curr = 0, prev = 0;
    
    /* WaterFall-related member functions */
    
    void processOpenFileSelection(ofFileDialogResult openFileResult);
	void LaserOn(int x1, int y1);
		
};

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

	int Rkey = 0; //������ ����Ű ������ flag
	int Lkey = 0; //���� ����Ű ������ flag

	stack <int> laserflag; // ������ �߻��Ѱ� x��ǥ����
	int endflag = 0;
	int lx[25]; //�عٴ� ������ ���� (�������� : 40  ���α��� 1024 so �ִ������ = 25
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

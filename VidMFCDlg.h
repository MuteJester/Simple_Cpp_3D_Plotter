
// VidMFCDlg.h : header file
//

#pragma once
#include "Image_Header.h"
#include "Color_Catalog.h"

typedef struct Space_Point {
	string Name;
	Point Coordinate;
}Space_p;

typedef struct Edge {
	int Index_A;
	int Index_B;
	pixel EdgeColor;
	
}Space_Edge;

class Cartesian_Coordinate_System {
protected:
	bool Colored;
public:
	vector<Space_p> Coordinates;
	vector<Space_Edge> Edges;
	Cartesian_Coordinate_System() {
		Colored = false;
	};
	void Add_Point(double const &x, double const &y, double const &z, string name) {
		Space_Point temp;
		temp.Name = name;
		temp.Coordinate.x = x;
		temp.Coordinate.y = y;
		temp.Coordinate.z = z;
		Coordinates.push_back(temp);
	}
	bool Add_Edge(string const &nameA, string const &nameB) {
		Space_Edge temp;
		bool Aauth = false, Bauth = false;
		for (int i = 0; i < Coordinates.size();i++) {
			if (Coordinates[i].Name == nameA) {
				temp.Index_A = i;
				Aauth = true;
				
			}
			else if (Coordinates[i].Name == nameB) {
				temp.Index_B = i;
				Bauth = true;
			
			}
			if (Aauth == true && Bauth == true) {
				Edges.push_back(temp);
				return true;
				
			}

		}
		return false;
	}
	bool Add_Edge(string const &nameA, string const &nameB,pixel const &EdgeColor) {
		Space_Edge temp;
		Colored = true;
		bool Aauth = false, Bauth = false;
		for (int i = 0; i < Coordinates.size(); i++) {
			if (Coordinates[i].Name == nameA) {
				temp.Index_A = i;
				Aauth = true;

			}
			else if (Coordinates[i].Name == nameB) {
				temp.Index_B = i;
				Bauth = true;

			}
			if (Aauth == true && Bauth == true) {
				Edges.push_back(temp);
				Edges.back().EdgeColor = EdgeColor;
				return true;

			}

		}
		return false;
	}
	bool Is_Colored() {
		return Colored == true ? true : false;
	}

};





class DMatrix {
public:
	double **Matrix;
	unsigned int Rows, Cols;
	DMatrix() {

	}
	DMatrix(int const Rows, int const Cols) {
		this->Rows = Rows;
		this->Cols = Cols;
		Matrix = (double**)malloc(sizeof(double*)*Rows);
		for (int i = 0; i < Rows; i++) {
			Matrix[i] = (double*)calloc(Cols, sizeof(double));
		}



	}


	~DMatrix() {
		for (int i = 0; i < Rows; i++) {
			free(Matrix[i]);
		}
		free(Matrix);
	}
	void Mul(DMatrix &A, DMatrix &B) {
		this->Rows = A.Rows;
		this->Cols = B.Cols;
		this->Matrix = (double**)malloc(sizeof(double*)*Rows);
		for (int i = 0; i < Rows; i++) {
			Matrix[i] = (double*)calloc(Cols, sizeof(double));
		}


		for (int i = 0; i < A.Rows; i++)
		{
			for (int j = 0; j < B.Cols; j++)
			{
				for (int k = 0; k < A.Cols; k++)
				{
					Matrix[i][j] += A.Matrix[i][k] * B.Matrix[k][j];
				}
			}
		}
	}


};



// CVidMFCDlg dialog
class CVidMFCDlg : public CDialog
{
// Construction
public:
	CVidMFCDlg(CWnd* pParent = nullptr);	// standard constructor

	Point Camera;
	Point Teta;
	Point E;
	Point RA;
	Point RotationAngle;

	coordinate point_to_coordinate(Point point);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIDMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	Image C;
	Cartesian_Coordinate_System Cord_Sys;
	void EulerCord(Point X, Point Y, Point Z, Point &R);
	void rotateAZ(double theta, Point &Cord);
	void rotateAY(double theta, Point &Cord);
	void rotateAX(double theta, Point &Cord);

	// Generated message map functions
	BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void Refresh_Frame();
	CStatic DisplayFrame;
	CButton InitBTN;
	afx_msg void OnBnDoubleclickedInitbtn();
	CButton BTNSTART;
	afx_msg void OnBnClickedInitbtn();
	afx_msg void OnStnClickedDisplayframe();
	CSpinButtonCtrl X_SPIN;
	CSpinButtonCtrl Y_SPIN;
	CSpinButtonCtrl Z_SPIN;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CTabCtrl Tab_Select;
	CButton SetValues;
	CEdit Input_X;
	CEdit Input_Y;
	CEdit Input_Z;
	afx_msg void OnBnClickedButton1();
	CStatic Cur_X;
	CStatic Cur_Z;
	CStatic Cur_Y;
	afx_msg void OnNMReleasedcaptureXSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposXSpin(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit AddPoint_X_INPUT;
	CEdit AddPoint_Y_INPUT;
	CEdit AddPoint_Z_INPUT;
	CButton NewPointBTN;
	CEdit AddPoint_Name_INPUT;
	afx_msg void OnBnClickedNewpointbtn();
	CEdit AddEdge_A_INPUT;
	CEdit AddEdge_B_INPUT;
	CButton NewEdgeBTN;
	afx_msg void OnBnClickedNewedgebtn();
	CMFCEditBrowseCtrl PlotBrowser;
	CButton RegisterPlotBTN;
	afx_msg void OnBnClickedRegistrplotbtn();
};

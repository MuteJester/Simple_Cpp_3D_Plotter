
// VidMFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VidMFC.h"
#include "VidMFCDlg.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "GlobalVars.h"
#include <sstream>
#include "Color_Catalog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define PI 3.14159265










// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CVidMFCDlg dialog



CVidMFCDlg::CVidMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_VIDMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVidMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DisplayFrame, DisplayFrame);
	DDX_Control(pDX, IDC_InitBTN, InitBTN);
	DDX_Control(pDX, IDC_TAB_Select, Tab_Select);
	DDX_Control(pDX, IDC_BUTTON1, SetValues);
	DDX_Control(pDX, IDC_Input_X, Input_X);
	DDX_Control(pDX, IDC_Input_Y, Input_Y);
	DDX_Control(pDX, IDC_Input_Z, Input_Z);
	DDX_Control(pDX, IDC_Cur_X, Cur_X);
	DDX_Control(pDX, IDC_Cur_Z, Cur_Z);
	DDX_Control(pDX, IDC_Cur_Y, Cur_Y);
	DDX_Control(pDX, IDC_AddPoint_X, AddPoint_X_INPUT);
	DDX_Control(pDX, IDC_AddPoint_Y, AddPoint_Y_INPUT);
	DDX_Control(pDX, IDC_AddPoint_Z, AddPoint_Z_INPUT);
	DDX_Control(pDX, IDC_NewPointBTN, NewPointBTN);
	DDX_Control(pDX, IDC_AddPoint_Name, AddPoint_Name_INPUT);
	DDX_Control(pDX, IDC_AddEdge_A, AddEdge_A_INPUT);
	DDX_Control(pDX, IDC_AddEdge_B, AddEdge_B_INPUT);
	DDX_Control(pDX, IDC_NewEdgeBTN, NewEdgeBTN);
	DDX_Control(pDX, IDC_PlotBrowser, PlotBrowser);
	DDX_Control(pDX, IDC_RegistrPlotBTN, RegisterPlotBTN);
}

BEGIN_MESSAGE_MAP(CVidMFCDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_DOUBLECLICKED(IDC_InitBTN, &CVidMFCDlg::OnBnDoubleclickedInitbtn)
	ON_BN_CLICKED(IDC_InitBTN, &CVidMFCDlg::OnBnClickedInitbtn)
	ON_STN_CLICKED(IDC_DisplayFrame, &CVidMFCDlg::OnStnClickedDisplayframe)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_Select, &CVidMFCDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON1, &CVidMFCDlg::OnBnClickedButton1)

	ON_BN_CLICKED(IDC_NewPointBTN, &CVidMFCDlg::OnBnClickedNewpointbtn)
	ON_BN_CLICKED(IDC_NewEdgeBTN, &CVidMFCDlg::OnBnClickedNewedgebtn)
	ON_BN_CLICKED(IDC_RegistrPlotBTN, &CVidMFCDlg::OnBnClickedRegistrplotbtn)
END_MESSAGE_MAP()


// CVidMFCDlg message handlers

BOOL CVidMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	pLoadedImage = (CStatic*)GetDlgItem(IDC_DisplayFrame);


	this->Tab_Select.InsertItem(0, _T("Camera"));
	this->Tab_Select.InsertItem(1, _T("Teta"));
	this->Tab_Select.InsertItem(2, _T("E"));
	this->Tab_Select.InsertItem(3, _T("R"));



	RA.x = RA.y = RA.z = 0;
	this->E.x = E.y;
	E.z = 1;
	this->Camera.x = Camera.y = Camera.z = 0;
	this->Teta.x = Teta.y = Teta.z = 0;
	pixel w;
	w.r = w.g = w.b = 255;
	C.Load_Blank_Canvas(900, 900, w);
	RotationAngle.x = RotationAngle.y = RotationAngle.z = 0;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVidMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVidMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVidMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVidMFCDlg::OnBnDoubleclickedInitbtn()
{
	CImage ImageView;
	CBitmap BitmapView;
	ImageView.Load(_T("G_EVENT.jpg"));
	BitmapView.Attach(ImageView.Detach());
	pLoadedImage->SetBitmap((HBITMAP)BitmapView);

	//for (int i = 0; i < 90; i++) {
	//	gol_frame.Update_Event();
	//	gol_frame.Save_Event();
	//	ImageView.Load(_T("G_EVENT.jpg"));
	//	BitmapView.Attach(ImageView.Detach());
	//	pLoadedImage->SetBitmap((HBITMAP)BitmapView);
	//}
	
	
}
void   CVidMFCDlg::EulerCord(Point X, Point Y, Point Z, Point &R)
{
	double Z1xy = sqrt(Z.x*Z.x + Z.y * Z.y);
	if (Z1xy > DBL_EPSILON)
	{
		R.x = atan2(Y.x*Z.y - Y.y * Z.x, X.x*Z.y - X.y * Z.x);
		R.y = atan2(Z1xy, Z.z);
		R.z = -atan2(-Z.x, Z.y);
	}
	else
	{
		R.x = 0.;
		R.y = (Z.z > 0.) ? 0. : PI;
		R.z = -atan2(X.y, X.x);
	}
}

// Rotate shape around the z-axis
void CVidMFCDlg::rotateAZ(double theta,Point &Cord) {
	double sinTheta = sin(theta);
	double cosTheta = cos(theta);

	//for (int n = 0; n < Cord_Sys.Coordinates.size(); n++) {
	//	double y =Cord_Sys.Coordinates[n].Coordinate.y;
	//	double x =Cord_Sys.Coordinates[n].Coordinate.x;
	//	Cord_Sys.Coordinates[n].Coordinate.x = x * cosTheta - y * sinTheta;
	//	Cord_Sys.Coordinates[n].Coordinate.y = y * cosTheta + x * sinTheta;
	//}

	double y = Cord.x;
	double x = Cord.y;
	Cord.x = x * cosTheta - y * sinTheta;
	Cord.y = y * cosTheta + x * sinTheta;

};

void CVidMFCDlg::rotateAX(double theta, Point &Cord) {
	double sinTheta = sin(theta);
	double cosTheta = cos(theta);

	/*for (int n = 0; n < Cord_Sys.Coordinates.size(); n++) {
		double y = Cord_Sys.Coordinates[n].Coordinate.y;
		double z = Cord_Sys.Coordinates[n].Coordinate.z;
		Cord_Sys.Coordinates[n].Coordinate.y = y * cosTheta - z * sinTheta;
		Cord_Sys.Coordinates[n].Coordinate.z = z * cosTheta + y * sinTheta;
	}*/

	double y = Cord.y;
	double z = Cord.z;
	double x = Cord.x;
	Cord.y = y * cosTheta - z * sinTheta;
	Cord.z = z * cosTheta + y * sinTheta;
};


void CVidMFCDlg::rotateAY(double theta, Point &Cord){
	double sinTheta = sin(theta);
	double cosTheta = cos(theta);

	//for (int n = 0; n < Cord_Sys.Coordinates.size(); n++) {
	//	double x = Cord_Sys.Coordinates[n].Coordinate.x;
	//	double z = Cord_Sys.Coordinates[n].Coordinate.z;
	//	Cord_Sys.Coordinates[n].Coordinate.x = x * cosTheta + z * sinTheta;
	//	Cord_Sys.Coordinates[n].Coordinate.z = z * cosTheta - x * sinTheta;
	//	
	//}

	double x = Cord.x;
	double z = Cord.z;
	Cord.x = x * cosTheta + z * sinTheta;
	Cord.z = z * cosTheta - x * sinTheta;
};



coordinate  CVidMFCDlg::point_to_coordinate(Point point) {
	coordinate Result;
	double X, Y, Z;
	double dX, dY, dZ;
	X = point.x- Camera.x;
	Y = point.y- Camera.y;
	Z = point.z- Camera.z;
	double TR = PI / 180;
	Point ToW;
	ToW.x = point.x;
	ToW.y = point.y;
	ToW.z = point.z;
	//Point X1={point.x,1,1}, Y1 = { 1,point.y,1 }, Z1 = { 1,1,point.z};
	//Point X1 = { 2,0,0 }, Y1 = { 0,2,0 }, Z1 = { 0,0,2 };
	//EulerCord(X1, Y1, Z1, Teta);
	DMatrix RE, A(3, 3), B(3, 3), C(3, 3),D,F,FINAL(3,1),Ppoint(3,1);
	DMatrix Hproj(3, 1), MProj(3, 3);





	this->rotateAX(this->RotationAngle.x*TR, ToW);
	this->rotateAY(this->RotationAngle.y*TR, ToW);
	this->rotateAZ(this->RotationAngle.z*TR, ToW);



	Ppoint.Matrix[0][0] = ToW.x - Camera.x;
	Ppoint.Matrix[1][0] = ToW.y - Camera.y;
	Ppoint.Matrix[2][0] = ToW.z - Camera.z;

	A.Matrix[0][0] = 1;
	A.Matrix[0][1] = 0;
	A.Matrix[0][2] = 0;
	A.Matrix[1][0] = 0;
	A.Matrix[1][1] = cos(Teta.x * TR);
	A.Matrix[1][2] = sin(Teta.x* TR);
	A.Matrix[2][0] = 0;
	A.Matrix[2][1] = -sin(Teta.x* TR);
	A.Matrix[2][2] = cos(Teta.x* TR);
	
	B.Matrix[0][0] = cos(Teta.y* TR);
	B.Matrix[0][1] = 0;
	B.Matrix[0][2] = -sin(Teta.y* TR);
	B.Matrix[1][0] = 0;
	B.Matrix[1][1] = 1;
	B.Matrix[1][2] = 0;
	B.Matrix[2][0] = sin(Teta.y* TR);
	B.Matrix[2][1] = 0;
	B.Matrix[2][2] = cos(Teta.y* TR);

	C.Matrix[0][0] = cos(Teta.z* TR);
	C.Matrix[0][1] = sin(Teta.z* TR);
	C.Matrix[0][2] = 0;
	C.Matrix[1][0] = -sin(Teta.z* TR);
	C.Matrix[1][1] = cos(Teta.z* TR);
	C.Matrix[1][2] = 0;
	C.Matrix[2][0] = 0;
	C.Matrix[2][1] = 0;
	C.Matrix[2][2] = 1;

	RE.Mul(A, B);
	F.Mul(RE, C);

	FINAL.Mul(F,Ppoint);
	

	MProj.Matrix[0][0] = 1;
	MProj.Matrix[0][1] = 0;
	MProj.Matrix[0][2] = E.x / E.z;
	MProj.Matrix[1][0] = 0;
	MProj.Matrix[1][1] = 1;
	MProj.Matrix[1][2] = E.y / E.z;
	MProj.Matrix[2][0] = 0;
	MProj.Matrix[2][1] = 0;
	MProj.Matrix[2][2] = 1 / E.z;

	Hproj.Mul(MProj, FINAL);








	//dX = cos(Teta.y) * (sin(Teta.z)*Y + cos(Teta.z)*X) - sin(Teta.y)*Z;
	//dY = sin(Teta.x)*(cos(Teta.y)*Z + sin(Teta.y) *(sin(Teta.z)*Y + cos(Teta.z)*X)) + cos(Teta.x)*(cos(Teta.z)*Y - sin(Teta.z)*X);
	//dZ = cos(Teta.x)*(cos(Teta.y)*Z + sin(Teta.y) *(sin(Teta.z)*Y + cos(Teta.z)*X)) + sin(Teta.x)*(cos(Teta.z)*Y - sin(Teta.z)*X);




	//Result.x = (E.z / FINAL.Matrix[2][0])*FINAL.Matrix[0][0] + E.x;
	//Result.y = (E.z / FINAL.Matrix[2][0])*FINAL.Matrix[1][0] + E.y;

	//Result.x = Hproj.Matrix[0][0] / Hproj.Matrix[2][0];
	//Result.y = Hproj.Matrix[1][0] / Hproj.Matrix[2][0];


	Result.x = (FINAL.Matrix[0][0] + E.x)*Camera.z;
	Result.y = (FINAL.Matrix[1][0] + E.y)*Camera.z;

	//Result.x = (( FINAL.Matrix[2][0])*FINAL.Matrix[0][0] + E.x);
	//Result.y = (( FINAL.Matrix[2][0])*FINAL.Matrix[1][0] + E.y);

	return Result;
}

//draw cube

//void CVidMFCDlg::OnBnClickedInitbtn()
//{
//	GOL_ENG gol_frame;
//	CImage ImageView;
//	CBitmap BitmapView;
//	CBitmap BitmapV;
//
//	gol_frame.Random_Seed_Init(1);
//	gol_frame.Save_Event();
//
//	ImageView.Load(_T("G_EVENT.jpg"));
//	BitmapView.Attach(ImageView.Detach());
//	pLoadedImage->SetBitmap((HBITMAP)BitmapView);
//
//
//	this->X_SPIN.SetRange(-800, 800);
//	this->Y_SPIN.SetRange(-800, 800);
//	this->Z_SPIN.SetRange(-800, 800);
//
//	this->X_SPIN.SetPos(0);
//	this->Y_SPIN.SetPos(0);
//	this->Z_SPIN.SetPos(0);
//
//	Image A, B;
//	Color_Palette palette;
//	stringstream ss;
//	string  via;
//	VectorFrame colors;
//	PixelFrame path;
//
//	A.Load_Blank_Canvas(900, 900, palette.White);
//	Point points[8];
//	coordinate d, m;
//	points[0] = { 1,1,1 };
//	points[1] = { 25,1,1 };
//	points[2] = { 25,25,1 };
//	points[3] = { 1,25,1 };
//	points[4] = { 1,1,25 };
//	points[5] = { 25,1,25 };
//	points[6] = { 25,25,25 };
//	points[7] = { 1,25,25 };
//	int cz = 1;
//
//	for (int i = 0; i < 8; i++) {
//		d = point_to_coordinate(points[i]);
//		A.Draw_Circle(400 + d.x, 400 + d.y, 1, palette.Black);
//
//	}
//
//
//	d = point_to_coordinate(points[0]);
//	m = point_to_coordinate(points[6]);
//	A.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//
//
//	m = point_to_coordinate(points[1]);
//	A.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//
//	m = point_to_coordinate(points[3]);
//	A.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//
//	m = point_to_coordinate(points[3]);
//	d = point_to_coordinate(points[5]);
//	A.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//
//	//A.Draw_Circle(400 + m.x, 400 + m.y, 2, palette.Red, "Fill");
//	//A.Draw_Circle(400 + d.x, 400 + d.y, 2, palette.Yellow, "Fill");
//
//	d = point_to_coordinate(points[5]);
//	m = point_to_coordinate(points[4]);
//	A.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//
//	d = point_to_coordinate(points[6]);
//	m = point_to_coordinate(points[7]);
//	A.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//
//	d = point_to_coordinate(points[5]);
//	m = point_to_coordinate(points[6]);
//	A.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//
//	m = point_to_coordinate(points[2]);
//	d = point_to_coordinate(points[1]);
//	A.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//
//	m = point_to_coordinate(points[2]);
//	d = point_to_coordinate(points[3]);
//	A.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//
//	m = point_to_coordinate(points[7]);
//	d = point_to_coordinate(points[1]);
//	A.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//
//
//	m = point_to_coordinate(points[7]);
//	d = point_to_coordinate(points[4]);
//	A.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//
//
//	m = point_to_coordinate(points[4]);
//	d = point_to_coordinate(points[2]);
//	A.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//
//
//	d = point_to_coordinate(points[2]);
//
//	A.Write_Image("G_EVENT");
//
//	ImageView.Load(_T("G_EVENT.jpg"));
//	BitmapV.Attach(ImageView.Detach());
//	pLoadedImage->SetBitmap((HBITMAP)BitmapV);
//
//}



void CVidMFCDlg::OnBnClickedInitbtn()
{
	CImage ImageView;
	CBitmap BitmapView;
	CBitmap BitmapV;

	ImageView.Load(_T("G_EVENT.jpg"));
	BitmapView.Attach(ImageView.Detach());
	pLoadedImage->SetBitmap((HBITMAP)BitmapView);

	Image A, B;
	Color_Palette palette;
	stringstream ss;
	string  via;
	VectorFrame colors;
	PixelFrame path;

	A.Load_Blank_Canvas(900, 900, palette.White);
	Point points[4];
	coordinate d, m;
		
	this->Refresh_Frame();

}

//refresh cube

//void CVidMFCDlg::Refresh_Frame() {
//
//	Color_Palette palette;
//	stringstream ss;
//	string  via;
//	VectorFrame colors;
//	PixelFrame path;
//	CImage ImageView;
//	CBitmap BitmapView;
//	CBitmap BitmapV;
//	CString temp;
//	Point points[8];
//	coordinate d, m;
//	points[0] = { 1,1,1 };
//	points[1] = { 25,1,1 };
//	points[2] = { 25,25,1 };
//	points[3] = { 1,25,1 };
//	points[4] = { 1,1,25 };
//	points[5] = { 25,1,25 };
//	points[6] = { 25,25,25 };
//	points[7] = { 1,25,25 };
//	int cz = 1;
//	int limit = 890;
//	for (int i = 0; i < C.getHeight()*C.getWidth() * 3; i++) {
//		C.Set_Pixel_By_Inedx(i, 255);
//	}
//
//	for (int i = 0; i < 8; i++) {
//		d = point_to_coordinate(points[i]);
//		if (400 + d.y < 897 && 400 + d.y > 2 && 400 + d.x < 897 && 400 + d.x > 2) {
//			C.Draw_Circle(400 + d.x, 400 + d.y, 1, palette.Black);
//		}
//
//	}
//
//
//	d = point_to_coordinate(points[0]);
//	m = point_to_coordinate(points[6]);
//	if (400 + d.y < limit && 400 + d.y > 0 && 400 + m.y < limit && 400 + m.y > 0 && 400 + d.x < 899 && 400 + d.x > 0 && 400 + m.x < limit && 400 + m.x > 0) {
//		C.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//	}
//
//	m = point_to_coordinate(points[1]);
//	if (400 + d.y < limit && 400 + d.y > 0 && 400 + m.y < limit && 400 + m.y > 0 && 400 + d.x < limit && 400 + d.x > 0 && 400 + m.x < limit && 400 + m.x > 0) {
//		C.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//	}
//	m = point_to_coordinate(points[3]);
//	if (400 + d.y < limit && 400 + d.y > 0 && 400 + m.y < limit && 400 + m.y > 0 && 400 + d.x < limit && 400 + d.x > 0 && 400 + m.x < limit && 400 + m.x > 0) {
//		C.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//	}
//	m = point_to_coordinate(points[3]);
//	d = point_to_coordinate(points[5]);
//	if (400 + d.y < limit && 400 + d.y > 0 && 400 + m.y < limit && 400 + m.y > 0 && 400 + d.x < limit && 400 + d.x > 0 && 400 + m.x < limit && 400 + m.x > 0) {
//		C.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//	}
//	//A.Draw_Circle(400 + m.x, 400 + m.y, 2, palette.Red, "Fill");
//	//A.Draw_Circle(400 + d.x, 400 + d.y, 2, palette.Yellow, "Fill");
//
//	d = point_to_coordinate(points[5]);
//	m = point_to_coordinate(points[4]);
//	if (400 + d.y < limit && 400 + d.y > 0 && 400 + m.y < limit && 400 + m.y > 0 && 400 + d.x < limit && 400 + d.x > 0 && 400 + m.x < limit && 400 + m.x > 0) {
//		C.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//	}
//	d = point_to_coordinate(points[6]);
//	m = point_to_coordinate(points[7]);
//	if (400 + d.y < limit && 400 + d.y > 0 && 400 + m.y < limit && 400 + m.y > 0 && 400 + d.x < limit && 400 + d.x > 0 && 400 + m.x < limit && 400 + m.x > 0) {
//		C.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//	}
//	d = point_to_coordinate(points[5]);
//	m = point_to_coordinate(points[6]);
//	if (400 + d.y < limit && 400 + d.y > 0 && 400 + m.y < limit && 400 + m.y > 0 && 400 + d.x < limit && 400 + d.x > 0 && 400 + m.x < limit && 400 + m.x > 0) {
//		C.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//	}
//	m = point_to_coordinate(points[2]);
//	d = point_to_coordinate(points[1]);
//	if (400 + d.y < limit && 400 + d.y > 0 && 400 + m.y < limit && 400 + m.y > 0 && 400 + d.x < limit && 400 + d.x > 0 && 400 + m.x < limit && 400 + m.x > 0) {
//		C.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//	}
//
//	m = point_to_coordinate(points[2]);
//	d = point_to_coordinate(points[3]);
//	if (400 + d.y < limit && 400 + d.y > 0 && 400 + m.y < limit && 400 + m.y > 0 && 400 + d.x < limit && 400 + d.x > 0 && 400 + m.x < limit && 400 + m.x > 0) {
//		C.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//	}
//	m = point_to_coordinate(points[7]);
//	d = point_to_coordinate(points[1]);
//	if (400 + d.y < limit && 400 + d.y > 0 && 400 + m.y < limit && 400 + m.y > 0 && 400 + d.x < limit && 400 + d.x > 0 && 400 + m.x < limit && 400 + m.x > 0) {
//		C.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//	}
//	m = point_to_coordinate(points[7]);
//	d = point_to_coordinate(points[4]);
//	if (400 + d.y < limit && 400 + d.y > 0 && 400 + m.y < limit && 400 + m.y > 0 && 400 + d.x < limit && 400 + d.x > 0 && 400 + m.x < limit && 400 + m.x > 0) {
//		C.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//	}
//
//	m = point_to_coordinate(points[4]);
//	d = point_to_coordinate(points[2]);
//	if (400 + d.y < limit && 400 + d.y > 0 && 400 + m.y < limit && 400 + m.y > 0 && 400 + d.x < limit && 400 + d.x > 0 && 400 + m.x < limit && 400 + m.x > 0) {
//		C.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);
//	}
//
//	d = point_to_coordinate(points[2]);
//
//	C.Write_Image("G_EVENT");
//
//	ImageView.Load(_T("G_EVENT.jpg"));
//	BitmapV.Attach(ImageView.Detach());
//	pLoadedImage->SetBitmap((HBITMAP)BitmapV);
//
//	switch (this->Tab_Select.GetCurSel())
//	{
//	case 0:
//		temp.Format(_T("%lf"), this->Camera.x);
//		this->Cur_X.SetWindowTextW(temp);
//		temp.Format(_T("%lf"), this->Camera.y);
//		this->Cur_Y.SetWindowTextW(temp);
//		temp.Format(_T("%lf"), this->Camera.z);
//		this->Cur_Z.SetWindowTextW(temp);
//		break;
//	case 1:
//		temp.Format(_T("%lf"), this->Teta.x);
//		this->Cur_X.SetWindowTextW(temp);
//		temp.Format(_T("%lf"), this->Teta.y);
//		this->Cur_Y.SetWindowTextW(temp);
//		temp.Format(_T("%lf"), this->Teta.z);
//		this->Cur_Z.SetWindowTextW(temp);
//
//		break;
//	case 2:
//		temp.Format(_T("%lf"), this->E.x);
//		this->Cur_X.SetWindowTextW(temp);
//		temp.Format(_T("%lf"), this->E.y);
//		this->Cur_Y.SetWindowTextW(temp);
//		temp.Format(_T("%lf"), this->E.z);
//		this->Cur_Z.SetWindowTextW(temp);
//
//		break;
//
//
//	default:
//		break;
//	}
//
//}

void CVidMFCDlg::Refresh_Frame() {

	Color_Palette palette;
	stringstream ss;
	string  via;
	VectorFrame colors;
	PixelFrame path;
	CImage ImageView;
	CBitmap BitmapView;
	CBitmap BitmapV;
	CString temp;

	
	coordinate d, m;



	int cz = 1;
	int limit = 890;
	for (int i = 0; i < C.getHeight()*C.getWidth() * 3; i++) {
		C.Set_Pixel_By_Inedx(i, 255);
	}

	//circle drawing at cord point positions 
	for (int i = 0; i < Cord_Sys.Coordinates.size(); i++) {
		d = point_to_coordinate(Cord_Sys.Coordinates[i].Coordinate);
		if (400 + d.y < 897 && 400 + d.y > 2 && 400 + d.x < 897 && 400 + d.x > 2) {
			C.Draw_Circle(400 + d.x, 400 + d.y, 1, palette.Black);
		}

	}


	if(Cord_Sys.Is_Colored()){
		for (auto i : Cord_Sys.Edges) {
			m = point_to_coordinate(Cord_Sys.Coordinates[i.Index_A].Coordinate);
			d = point_to_coordinate(Cord_Sys.Coordinates[i.Index_B].Coordinate);
			if (400 + d.y < limit && 400 + d.y > 0 && 400 + m.y < limit && 400 + m.y > 0 && 400 + d.x < limit && 400 + d.x > 0 && 400 + m.x < limit && 400 + m.x > 0) {
				C.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, i.EdgeColor);
				

			}
		}
	}
	else {
		for (auto i : Cord_Sys.Edges) {
			m = point_to_coordinate(Cord_Sys.Coordinates[i.Index_A].Coordinate);
			d = point_to_coordinate(Cord_Sys.Coordinates[i.Index_B].Coordinate);
			if (400 + d.y < limit && 400 + d.y > 0 && 400 + m.y < limit && 400 + m.y > 0 && 400 + d.x < limit && 400 + d.x > 0 && 400 + m.x < limit && 400 + m.x > 0) {
				C.Draw_Line(400 + d.y, 400 + d.x, 400 + m.y, 400 + m.x, palette.Blue);

			}
		}

	}
	//for (auto i : Cord_Sys.Edges) {
	//	m = point_to_coordinate(Cord_Sys.Coordinates[i.Index_A].Coordinate);
	//	d = point_to_coordinate(Cord_Sys.Coordinates[i.Index_B].Coordinate);
	//	if ( d.y < limit && d.y > 0 && m.y < limit && m.y > 0 &&  d.x < limit && d.x > 0 &&  m.x < limit && m.x > 0) {
	//		C.Draw_Line( d.y, d.x, m.y,  m.x, palette.Blue);

	//	}
	//}


	//end of ploting and moving to visual frame update

	C.Write_Image("G_EVENT");

	ImageView.Load(_T("G_EVENT.jpg"));
	BitmapV.Attach(ImageView.Detach());
	pLoadedImage->SetBitmap((HBITMAP)BitmapV);

	switch (this->Tab_Select.GetCurSel())
	{
	case 0:
		temp.Format(_T("%lf"), this->Camera.x);
		this->Cur_X.SetWindowTextW(temp);
		temp.Format(_T("%lf"), this->Camera.y);
		this->Cur_Y.SetWindowTextW(temp);
		temp.Format(_T("%lf"), this->Camera.z);
		this->Cur_Z.SetWindowTextW(temp);
		break;
	case 1:
		temp.Format(_T("%lf"), this->Teta.x);
		this->Cur_X.SetWindowTextW(temp);
		temp.Format(_T("%lf"), this->Teta.y);
		this->Cur_Y.SetWindowTextW(temp);
		temp.Format(_T("%lf"), this->Teta.z);
		this->Cur_Z.SetWindowTextW(temp);

		break;
	case 2:
		temp.Format(_T("%lf"), this->E.x);
		this->Cur_X.SetWindowTextW(temp);
		temp.Format(_T("%lf"), this->E.y);
		this->Cur_Y.SetWindowTextW(temp);
		temp.Format(_T("%lf"), this->E.z);
		this->Cur_Z.SetWindowTextW(temp);

		break;

	case 3:
		temp.Format(_T("%lf"), this->RotationAngle.x);
		this->Cur_X.SetWindowTextW(temp);
		temp.Format(_T("%lf"), this->RotationAngle.y);
		this->Cur_Y.SetWindowTextW(temp);
		temp.Format(_T("%lf"), this->RotationAngle.z);
		this->Cur_Z.SetWindowTextW(temp);

		break;

	default:
		break;
	}

}




void CVidMFCDlg::OnStnClickedDisplayframe()
{
	// TODO: Add your control notification handler code here
	this->Refresh_Frame();
	DisplayFrame.SetFocus();
}


void CVidMFCDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CVidMFCDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CString x, y, z;
	Input_X.GetWindowTextW(x);
	Input_Y.GetWindowTextW(y);
	Input_Z.GetWindowTextW(z);
	switch (this->Tab_Select.GetCurSel())
	{

	case 0:
		this->Camera.x = _wtoi(x);
		this->Camera.y = _wtoi(y);
		this->Camera.z = _wtoi(z);

		break;

	case 1:
		this->Teta.x = _wtoi(x);
		this->Teta.y = _wtoi(y);
		this->Teta.z = _wtoi(z);

		break;

	case 2:
		this->E.x = _wtoi(x);
		this->E.y = _wtoi(y);
		this->E.z = _wtoi(z);

		break;

	case 3:
		this->RotationAngle.x = _wtoi(x);
		this->RotationAngle.y = _wtoi(y);
		this->RotationAngle.z = _wtoi(z);

		break;
	default:
		break;
	}
	

}


void CVidMFCDlg::OnNMReleasedcaptureXSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	switch (this->Tab_Select.GetCurSel())
	{

	case 0:
		this->Camera.x = this->X_SPIN.GetPos();
	

		break;

	case 1:
		this->Teta.x = this->X_SPIN.GetPos();


		break;

	case 2:
		this->E.x = this->X_SPIN.GetPos();


		break;
	default:
		break;
	}

	this->Refresh_Frame();
}


void CVidMFCDlg::OnDeltaposXSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here


	//switch (this->Tab_Select.GetCurSel())
	//{

	//case 0:
	//	this->Camera.x = this->X_SPIN.GetPos();


	//	break;

	//case 1:
	//	this->Teta.x = this->X_SPIN.GetPos();


	//	break;

	//case 2:
	//	this->E.x = this->X_SPIN.GetPos();


	//	break;
	//default:
	//	break;
	//}

	this->Refresh_Frame();
	*pResult = 0;
}
BOOL CVidMFCDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		CString temp;
		ifstream Reader;
		int b_a;

		

			switch (pMsg->wParam)
			{

			case 0x5A:
			
				switch (this->Tab_Select.GetCurSel())
				{

				case 0:
					this->Camera.x++;
					this->Refresh_Frame();

					break;
				case 1:
					this->Teta.x++;
					//this->RA.x++;
					//this->rotateAX(RA.x);
					this->Refresh_Frame();

					break;
				case 2:
					this->E.x++;
					this->Refresh_Frame();

					break;
				case 3:
					this->RotationAngle.x++;
					this->Refresh_Frame();

					break;

				default:
					break;
				}
			

				break;
			case 0x58:
				switch (this->Tab_Select.GetCurSel())
				{

				case 0:
					this->Camera.y++;
					this->Refresh_Frame();

					break;
				case 1:
					this->Teta.y++;
					//this->RA.y++;
					//rotateAY(RA.y);
					this->Refresh_Frame();

					break;
				case 2:
					this->E.y++;
					this->Refresh_Frame();

					break;
				case 3:
					this->RotationAngle.y++;
					this->Refresh_Frame();

					break;
				default:
					break;
				}

				break;


			case 0x43:
				switch (this->Tab_Select.GetCurSel())
				{

				case 0:
					this->Camera.z++;
					this->Refresh_Frame();

					break;
				case 1:
					this->Teta.z++;
					//this->RA.z++;
					//rotateAZ(1);
					this->Refresh_Frame();

					break;
				case 2:
					this->E.z++;
					this->Refresh_Frame();
					break;
				case 3:
					this->RotationAngle.z++;
					this->Refresh_Frame();
					break;

				default:
					break;
				}

				break;

			case 0x41:
				switch (this->Tab_Select.GetCurSel())
				{

				case 0:
					this->Camera.x--;
					this->Refresh_Frame();

					break;
				case 1:
					this->Teta.x--;
					//RA.x--;
					//rotateAX(RA.x);
					this->Refresh_Frame();

					break;
				case 2:
					this->E.x--;
					this->Refresh_Frame();
					break;

				case 3:
					this->RotationAngle.x--;
					this->Refresh_Frame();
					break;
				default:
					break;
				}


				break;


			case 0x53:
				switch (this->Tab_Select.GetCurSel())
				{

				case 0:
					this->Camera.y--;
					this->Refresh_Frame();

					break;
				case 1:
					this->Teta.y--;
				//	RA.y--;
				//	this->rotateAY(RA.y);
					this->Refresh_Frame();

					break;
				case 2:
					this->E.y--;
					this->Refresh_Frame();
					break;
					case 3:
						this->RotationAngle.y--;
						this->Refresh_Frame();
						break;

				default:
					break;
				}


				break;

			case 0x44:

				switch (this->Tab_Select.GetCurSel())
				{

				case 0:
					this->Camera.z--;
					this->Refresh_Frame();

					break;
				case 1:
					this->Teta.z--;
					//RA.z--;
					//rotateAZ(-1);
					this->Refresh_Frame();

					break;
				case 2:
					this->E.z--;
					this->Refresh_Frame();
					break;
				case 3:
					this->RotationAngle.z--;
					this->Refresh_Frame();
					break;

				default:
					break;
				}

				break;

			default:
				break;
			}
		

	}


	return CDialog::PreTranslateMessage(pMsg);
}


void CVidMFCDlg::OnBnClickedNewpointbtn()
{
	// Create New Point
	CString X, Y, Z, Name;
	this->AddPoint_X_INPUT.GetWindowTextW(X);
	this->AddPoint_Y_INPUT.GetWindowTextW(Y);
	this->AddPoint_Z_INPUT.GetWindowTextW(Z);
	this->AddPoint_Name_INPUT.GetWindowTextW(Name);
	Space_Point temp;
	temp.Name = CT2CA(Name);
	temp.Coordinate.x = _wtoi(X);
	temp.Coordinate.y = _wtoi(Y);
	temp.Coordinate.z = _wtoi(Z);


	this->Cord_Sys.Coordinates.push_back(temp);

	this->AddPoint_X_INPUT.SetWindowTextW(_T(""));
	this->AddPoint_Y_INPUT.SetWindowTextW(_T(""));
	this->AddPoint_Z_INPUT.SetWindowTextW(_T(""));
	this->AddPoint_Name_INPUT.SetWindowTextW(_T(""));

	this->Refresh_Frame();
}


void CVidMFCDlg::OnBnClickedNewedgebtn()
{
	// Add New Edge
	CString NameA, NameB;
	string a, b;
	bool status;
	this->AddEdge_A_INPUT.GetWindowTextW(NameA);
	this->AddEdge_B_INPUT.GetWindowTextW(NameB);
	a = CT2CA(NameA);
	b = CT2CA(NameB);
	status = this->Cord_Sys.Add_Edge(a, b);
	if (status == false) {
		MessageBox(_T("Edge Was Not Added Please Make Sure\n The Edge Exists And The Point Names Are Correct"), _T("Error"), CB_OKAY);
	}
	this->Refresh_Frame();

}


void CVidMFCDlg::OnBnClickedRegistrplotbtn()
{
	// Regist user loaded plot

	if (this->Cord_Sys.Coordinates.size() > 0) {
		this->Cord_Sys.Coordinates.clear();
	}
	if (this->Cord_Sys.Edges.size() > 0) {
		this->Cord_Sys.Edges.clear();
	}
	CString Plot_Path;
	PlotBrowser.GetWindowTextW(Plot_Path);
	ifstream Plot_Import;
	stringstream ss;
	string E1,E2,f_line,p_name,sample;
	bool edge_reg = false,Colored = false;
	double g_x, g_y, g_z;
	int EdgeColor_SN;
	size_t pos,A,B;
	Color_Palette CSET;
	
	Plot_Import.open(CT2A(Plot_Path));

	if (!Plot_Import.is_open()) {
		return;
	}
	getline(Plot_Import, f_line);

	if (f_line == "Vectors") {

		//point registration
		while (edge_reg == false) {
			getline(Plot_Import, f_line);
			if (f_line[0] == 'E') {
				if (f_line[1] == 'C') {
					Colored = true;
				}
				edge_reg = true;
				break;
			}
			else {
				A = f_line.find(",");
				sample = f_line.substr(1, A - 1);
				g_x = stod(sample);

				B = f_line.find(",", A + 1);
				sample = f_line.substr(A + 1, B - 1);
				g_y = stod(sample);
				A = B;

				B = f_line.find(")", A + 1);
				sample = f_line.substr(A + 1, B - 1);
				g_z = stod(sample);

				p_name = f_line.substr(B + 2, f_line.size());
				this->Cord_Sys.Add_Point(g_x, g_y, g_z, p_name);
			}
		}

		//edge registration
		while (getline(Plot_Import, f_line)) {


			if (Colored == true) {
				pos = f_line.find(" ");
				E1 = f_line.substr(0, pos);
				A = f_line.find(" ", pos);
				E2 = f_line.substr(pos + 1, A);

				A = f_line.find(" ", pos + 1);
				sample = f_line.substr(A + 1);
				EdgeColor_SN = stoi(sample);
				this->Cord_Sys.Add_Edge(E1, E2, CSET.Color_Serial_Number[EdgeColor_SN]);

			}
			else {

				pos = f_line.find(" ");
				E1 = f_line.substr(0, pos);
				E2 = f_line.substr(pos + 1, f_line.size());
				this->Cord_Sys.Add_Edge(E1, E2);

			}

		}
	}
	Plot_Import.close();
	this->Refresh_Frame();
}

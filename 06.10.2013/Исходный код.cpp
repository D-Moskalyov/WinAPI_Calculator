#include <windows.h>
#include <string>
#include <limits>
#pragma warning(disable : 4996)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//(-std::numeric_limits<double>::min() < lc && lc < std::numeric_limits<double>::min())

bool check(const long double &lc)
{
	if (-1.79769e+308 < lc && lc < 1.79769e+308)
		return 1;
	return 0;
}

double plus(double a, double b)
{
	long double	la = a,
				lb = b,
				lc = la + lb;

	if(check(lc))
		return static_cast<double>(lc);
	return 0;
}

double minus(double a, double b)
{
	long double	la = a,
				lb = b,
				lc = la - lb;

	if(check(lc))
		return static_cast<double>(lc);
	return 0;
}

double multiply(double a, double b)
{
	long double	la = a,
				lb = b,
				lc = la * lb;

	if(check(lc))
		return static_cast<double>(lc);
	return 0;
}

double divide(double a, double b)
{
	long double	la = a,
				lb = b,
				lc = la / lb;

	if(check(lc))
		return static_cast<double>(lc);
	return 0;
}

HWND buttons[16];

HINSTANCE hInst;

HWND infoEdit;

double result=0, second=0;
int count=0, znak=1;
char buff[20];

char WinName[] = "MainFrame";

int APIENTRY WinMain(HINSTANCE This,		
	HINSTANCE Prev,						
	LPTSTR cmd,					
	int mode)							
{
	HWND hWnd;								
	MSG msg;								
	WNDCLASS wc;							
									
	wc.hInstance = This;		
	wc.lpszClassName = WinName;		
	wc.lpfnWndProc = WndProc;			
	wc.style = CS_HREDRAW | CS_VREDRAW;			
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);	
	wc.lpszMenuName = NULL;	
	wc.cbClsExtra = 0;		
	wc.cbWndExtra = 0;		
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	if(!RegisterClass(&wc)) return 0;	

	hWnd = CreateWindow(WinName, "Culc", WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX , 20, 20, 295, 390, HWND_DESKTOP, NULL, This, NULL);

	ShowWindow(hWnd, mode); 

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
				 WPARAM wParam, LPARAM lParam)
{	

	switch(message){
		case WM_DESTROY:{ PostQuitMessage(0); break;}
		case WM_CREATE:{
			infoEdit = CreateWindow("edit","0",WS_CHILD|WS_VISIBLE|WS_BORDER|ES_RIGHT|ES_READONLY, 10, 30, 265, 20, hWnd,(HMENU)201,hInst,0);
			buttons[0] =  CreateWindow("button","7", WS_CHILD|WS_VISIBLE, 10,70,65,65, hWnd, (HMENU)107, hInst, 0);
			buttons[1] =  CreateWindow("button","8", WS_CHILD|WS_VISIBLE, 75,70,65,65, hWnd, (HMENU)108, hInst, 0);
			buttons[2] =  CreateWindow("button","9", WS_CHILD|WS_VISIBLE, 140,70,65,65, hWnd, (HMENU)109, hInst, 0);
			buttons[3] =  CreateWindow("button","+", WS_CHILD|WS_VISIBLE, 205,70,65,65, hWnd, (HMENU)110, hInst, 0);
			buttons[4] =  CreateWindow("button","4", WS_CHILD|WS_VISIBLE, 10,135,65,65, hWnd, (HMENU)104, hInst, 0);
			buttons[5] =  CreateWindow("button","5", WS_CHILD|WS_VISIBLE, 75,135,65,65, hWnd, (HMENU)105, hInst, 0);
			buttons[6] =  CreateWindow("button","6", WS_CHILD|WS_VISIBLE, 140,135,65,65, hWnd, (HMENU)106, hInst, 0);
			buttons[7] =  CreateWindow("button","-", WS_CHILD|WS_VISIBLE, 205,135,65,65, hWnd, (HMENU)111, hInst, 0);
			buttons[8] =  CreateWindow("button","1", WS_CHILD|WS_VISIBLE, 10,200,65,65, hWnd, (HMENU)101, hInst, 0);
			buttons[9] =  CreateWindow("button","2", WS_CHILD|WS_VISIBLE, 75,200,65,65, hWnd, (HMENU)102, hInst, 0);
			buttons[10] =  CreateWindow("button","3", WS_CHILD|WS_VISIBLE, 140,200,65,65, hWnd, (HMENU)103, hInst, 0);
			buttons[11] =  CreateWindow("button","*", WS_CHILD|WS_VISIBLE, 205,200,65,65, hWnd, (HMENU)112, hInst, 0);
			buttons[12] =  CreateWindow("button","C", WS_CHILD|WS_VISIBLE, 10,265,65,65, hWnd, (HMENU)113, hInst, 0);
			buttons[13] =  CreateWindow("button","0", WS_CHILD|WS_VISIBLE, 75,265,65,65, hWnd, (HMENU)100, hInst, 0);
			buttons[14] =  CreateWindow("button","=", WS_CHILD|WS_VISIBLE, 140,265,65,65, hWnd, (HMENU)114, hInst, 0);
			buttons[15] =  CreateWindow("button","/", WS_CHILD|WS_VISIBLE, 205,265,65,65, hWnd, (HMENU)115, hInst, 0);
			break;
		}
		case WM_COMMAND:{
			if(HIWORD(wParam)==BN_CLICKED){
				switch (LOWORD(wParam)){
					case 100: case 101: case 102: case 103: case 104: 
					case 105: case 106: case 107: case 108: case 109:{
						if(count<9&&second<214748364){
							if(znak==0)	second=0;
							second=second*10+LOWORD(wParam)-100;
							itoa(second, buff, 10);
							SetWindowText(infoEdit, buff); 
							count++;
						}
						break;
					}
					case 110: case 111: case 112: case 115:{
						switch(znak){
							case 0: result=second; break;
							case 1: {   if(plus(result, second))
											result=plus(result, second); 
									else {
										result=0;
										count=0;
										znak=1;
										strcpy(buff, "!Error!");
										SetWindowText(infoEdit, buff); 
									}  
									break;
								}
							case 2: {   if(minus(result, second))
											result=minus(result, second); 
									else {
										result=0;
										count=0;
										znak=1;
										strcpy(buff, "!Error!");
										SetWindowText(infoEdit, buff); 
									}  
									break;
								}
							case 3: {   if(multiply(result, second))
											result=multiply(result, second); 
									else {
										result=0;
										count=0;
										znak=1;
										strcpy(buff, "!Error!");
										SetWindowText(infoEdit, buff); 
									}  
									break;
								}
							case 4: {
									if(second){   
										if(divide(result, second))
											result=divide(result, second); 
										else {
											result=0;
											count=0;
											znak=1;
											strcpy(buff, "!Error!");
											SetWindowText(infoEdit, buff); 
										}  
									}
									else{
										result=0;
										count=0;
										znak=1;
										strcpy(buff, "!Dev by 0!");
										SetWindowText(infoEdit, buff); 
									}
									break;
									}
							default: break;
						};
						if(strcmp(buff, "!Dev by 0!")&&strcmp(buff, "!Error!")){
							sprintf (buff, "%f", result);
							/*MessageBox(NULL, buff, "Title", MB_OK);*/
							while(strrchr(buff, '0')&&(strrchr(buff, '0'))>(strchr(buff, '.')))
								buff[strlen(buff)-1]='\0';
							if(buff[strlen(buff)-1]=='.')
								buff[strlen(buff)-1]='\0';
							SetWindowText(infoEdit, buff); 
							strcpy(buff, "\0");
							count=0;
							second=0;
							if(LOWORD(wParam)==110) znak=1; 
							if(LOWORD(wParam)==111) znak=2; 
							if(LOWORD(wParam)==112) znak=3; 
							if(LOWORD(wParam)==115) znak=4; 
						}
						break;
					}
					case 113:{
						result=0;
						second=0;
						count=0;
						sprintf (buff, "%f", result);
						while(strrchr(buff, '0')&&(strrchr(buff, '0'))>(strchr(buff, '.')))
							buff[strlen(buff)-1]='\0';
						if(buff[strlen(buff)-1]=='.')
							buff[strlen(buff)-1]='\0';
						SetWindowText(infoEdit, buff); 
						znak=1;
						break;
					}
					case 114:{
						switch(znak){
							case 0: result=second; break;
							case 1: {   if(plus(result, second))
											result=plus(result, second); 
									else {
										result=0;
										count=0;
										znak=1;
										strcpy(buff, "!Error!");
										SetWindowText(infoEdit, buff); 
									}  
									break;
								}
							case 2: {   if(minus(result, second))
											result=minus(result, second); 
									else {
										result=0;
										count=0;
										znak=1;
										strcpy(buff, "!Error!");
										SetWindowText(infoEdit, buff); 
									}  
									break;
								}
							case 3: {   if(multiply(result, second))
											result=multiply(result, second); 
									else {
										result=0;
										count=0;
										znak=1;
										strcpy(buff, "!Error!");
										SetWindowText(infoEdit, buff); 
									}  
									break;
								}
							case 4: {
									if(second){   
										if(divide(result, second))
											result=divide(result, second); 
										else {
											result=0;
											count=0;
											znak=1;
											strcpy(buff, "!Error!");
											SetWindowText(infoEdit, buff); 
										}  
									}
									else{
										result=0;
										count=0;
										znak=1;
										strcpy(buff, "!Dev by 0!");
										SetWindowText(infoEdit, buff); 
									}
									break;
									}
							default: break;
						};
						if(strcmp(buff, "!Dev by 0!")&&strcmp(buff, "!Error!")){
							sprintf (buff, "%f", result);
							while(strrchr(buff, '0')&&(strrchr(buff, '0'))>(strchr(buff, '.')))
								buff[strlen(buff)-1]='\0';
							if(buff[strlen(buff)-1]=='.')
								buff[strlen(buff)-1]='\0';
							SetWindowText(infoEdit, buff); 
							count=0;
							second=result;
							znak=0;
						}
						break;
					}
					default: break;
				}
			}	
			break;
		}
		default: break;
	};
	return DefWindowProc(hWnd, message, wParam, lParam);
}
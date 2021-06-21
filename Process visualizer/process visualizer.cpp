/*
 * main.cpp
 *
 *  Created on: 27-Sep-2011
 *      Author:		Omar Asif Shaikh
 *
 */

 /***********************************************************************************************************************************


 keywords: prefix 'F'-FCFS	'S'-SJF		'P'-Priority	'R'-Round Robin

 ************************************************************************************************************************************/
#include<iostream>
 //#include"process.h"
#include<GL/glut.h>
using namespace std;

GLfloat colors[][3] = { {1.0,0.0,0.0}//red
,{1.0,1.0,0.0}//yellow
,{0.0,1.0,0.0}//green
,{0.0,0.0,1.0}//blue
,{1.0,0.0,1.0}//Purple
,{0.0,1.0,1.0}//Cyan
,{0.0,0.0,0.0}//Black
,{1.0,1.0,1.0}//White
};


int Num_Processes, Bsum = 0, Fdp[500], Sdp[500], Pdp[500], Rdp[500];				//Bsum- sum of all process.burst....    <<< Dp for opengl renderer
int pr = 0, a = 0;							//used as flags in input()for arrival time and priority;



class process
{
public:
	//int Pnum;
	int ArrivalTime, BurstTime, Priority;
	int WaitingTime, TurnAroundTime = 0;
	int Fstart, Fend;						//For FCFS
	int RemBurstTime = 0;
	int FWaitingTime, FTurnAroundTime;
	int SWaitingTime, STurnAroundTime;
	int PWaitingTime, PTurnAroundTime;
	int RWaitingTime, RTurnAroundTime;

	process()							//Default constructor
	{
		ArrivalTime = BurstTime = Priority = 0;
		WaitingTime = 0;
		Fstart = Fend = 0;
		FWaitingTime = FTurnAroundTime = 0;
		SWaitingTime = STurnAroundTime = 0;
		PWaitingTime = PTurnAroundTime = 0;
		RWaitingTime = RTurnAroundTime = 0;
	}

};



//process *p;
process P[30];

void input()
{


	cout << "\nIf specifying Arrival time, enter '1' else '0' :";
	cin >> a;
	cout << "\nIf specifying priority, enter '1' else '0' :";
	cin >> pr;

	for (int i = 0; i < Num_Processes; i++)
	{
		cout << "\n\nEnter the details of process " << i + 1 << ":\n";
		cout << "Burst time:";
		cin >> P[i].BurstTime;
		P[i].RemBurstTime = P[i].BurstTime;
		if (a)
		{
			cout << "Arrival Time:";
			cin >> P[i].ArrivalTime;
		}
		if (pr)
		{
			cout << "Priority:";
			cin >> P[i].Priority;
		}

	}
	cout << "\nProcess    \tBurst time\tArrival Time\tPriority";
	for (int i = 0; i < Num_Processes; i++)
	{
		Bsum += P[i].BurstTime;
		cout << "\n" << i + 1 << "\t\t" << P[i].BurstTime << "\t\t" << P[i].ArrivalTime << "\t\t" << P[i].Priority;
	}
	cout << endl;

}
void init()
{
	for (int i = 0; i < Num_Processes; i++)
	{
		P[i].RemBurstTime = P[i].BurstTime;
	}
}

void WaitCal()
{
	int b = 0, index;
	
	init();						//Priority
	while (b < Bsum)
	{
		index = Pdp[b];
		for (int i = 0; i < Num_Processes; i++)
		{
			if (i != index && P[i].RemBurstTime > 0 && P[i].ArrivalTime <= b)
				P[i].PWaitingTime++;

		}
		P[index].RemBurstTime--;
		b++;


	}

	
	//////BOTH WORKING FOR SINGLE ARRAY[Pdp]
}
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	GLfloat BlockSize, x, y, FPx, FPy, SPx, SPy, PPx, PPy, RPx, RPy, Gridx, Gridy{};
	GLint b = 0, index;

	BlockSize = 300 / Bsum;
	FPy = 100;	FPx = 100;
	SPy = 200;	SPx = 100;
	PPy = 300;	PPx = 100;
	RPy = 400;	RPx = 100;


	//Opengl FCFS
	
	//Opengl SJF

	//Opengl Priority
	x = PPx;
	y = PPy;
	b = 0;
	while (b < Bsum)
	{
		index = Pdp[b];
		glColor3fv(colors[index]);
		glBegin(GL_QUADS);
		glVertex2f(x, y);
		glVertex2f(x + BlockSize, y);
		glVertex2f(x + BlockSize, y + 10);
		glVertex2f(x, y + 10);
		glEnd();
		b++;
		x = x + BlockSize;
	}

	//Opengl Round Robin
	



	glFlush();


}
void Display1()
{
	cout << "\n\nFinal Display";
	cout << "\nProcess   \tBurst time\tArrival Time\tPriority\tStart    \tEnd\tWaiting Time";
	for (int i = 0; i < Num_Processes; i++)
	{
		Bsum += P[i].BurstTime;
		cout << "\n" << i + 1 << "\t\t" << P[i].BurstTime << "\t\t" << P[i].ArrivalTime << "\t\t" << P[i].Priority << "\t\t" << P[i].Fstart << "\t\t" << P[i].Fend;
		cout << "\t" << P[i].WaitingTime;
	}
	cout << endl;

}
void Display2()

{
	cout << endl << "FCFS:\t";
	for (int b = 0; b < Bsum; b++)
	{
		cout << Fdp[b];
	}
	cout << endl << "SJF:\t";
	for (int b = 0; b < Bsum; b++)
	{
		cout << Sdp[b];
	}
	cout << endl << "Priority:\t";
	for (int b = 0; b < Bsum; b++)
	{
		cout << Pdp[b];
	}
	cout << endl << "Round Robin:\t";
	for (int b = 0; b < Bsum; b++)
	{
		cout << Rdp[b];
	}
	cout << "\n\nFinal Display";
	cout << "\nProcess   \tBurst time\tArrival Time\tPriority";
	for (int i = 0; i < Num_Processes; i++)
	{
		cout << "\n" << i + 1 << "\t\t" << P[i].BurstTime << "\t\t" << P[i].ArrivalTime << "\t\t" << P[i].Priority;

	}
	cout << endl;
	cout << "\nProcess     \tFWaiting Time  \tFTurnaround Time\tSWaiting Time  \tSTurnaround Time\tPWaiting Time  \tPTurnaround Time\tRWaiting Time  \tRTurnaround Time";
	for (int i = 0; i < Num_Processes; i++)
	{
		cout << "\n" << i + 1 << "\t\t" << P[i].FWaitingTime << "\t\t" << P[i].FTurnAroundTime << "\t\t\t" << P[i].SWaitingTime << "\t\t" << P[i].STurnAroundTime;
		cout << "\t\t\t" << P[i].PWaitingTime << "\t\t" << P[i].PTurnAroundTime << "\t\t\t" << P[i].RWaitingTime << "\t\t" << P[i].RTurnAroundTime;
	}

	cout << endl << "Process 1 Color: Red";
	cout << endl << "Process 2 Color: Yellow";
	cout << endl << "Process 3 Color: Green";
	cout << endl << "Process 4 Color: Blue";
	cout << endl << "Process 5 Color: Purple";
	cout << endl << "Process 6 Color: Cyan";
	cout << endl << "Process 7 Color: Black";

}




void Priority()															//working!!!
{
	int Pind1 = 0;
    int maxp, ch, bctr;
	init();
	cout << "\n Enter 1 if non preemptive for Priority\n";
	cin >> ch;
	if (ch)
	{
		bctr = 0;
		while (bctr < Bsum)
		{
			maxp = 0;
			//non-preemptive
			for (int i = 0; i < Num_Processes; i++)
			{
				if ((P[i].ArrivalTime <= bctr) && (P[i].Priority >= maxp) && (P[i].RemBurstTime > 0))
				{
					Pind1 = i;
					maxp = P[i].Priority;
				}
			}
			for (int i = bctr; i < (bctr + P[Pind1].BurstTime); i++)
			{
				Pdp[i] = Pind1;
			}
			P[Pind1].RemBurstTime = 0;
			bctr += P[Pind1].BurstTime;
		}
	}
	else
	{
		//preemptive
		for (int b = 0; b < Bsum; b++)
		{
			Pind1 = -1;
			maxp = 0;
			for (int i = 0; i < Num_Processes; i++)
			{
				if ((P[i].ArrivalTime <= b) && (P[i].Priority >= maxp) && (P[i].RemBurstTime > 0))
				{
					maxp = P[i].Priority;
					Pind1 = i;
				}
			}
			if (Pind1 >= 0)
			{
				Pdp[b] = Pind1;
				P[Pind1].RemBurstTime--;
			}

		}
	}
}




int main(int argc, char** argv)
{
	//int ch;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);


	glutCreateWindow("Process Scheduler");
	glutDisplayFunc(Display);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0, 1.0, 1.0, 1.0);




	cout << "Welcome to The Process scheduling program!!\n\n";
	cout << "Enter the number of Processes(<=7)";
	cin >> Num_Processes;
	input();
	/***************************************
	//p=new(Num_Processes*sizeof(process));
	cout<<"\n Select your algorithm:\n";

	cout<<"3.Priority Scheduling\n";
	
	cin>>ch;
	switch(ch)
	{
		case 1:
			Fcfs();
			Display2();
			break;
		case 2:
			Sjf();
			Display2();
			break;
		case 3:
			Priority();
			WaitCal();
			Display2();
			break;
		

	}
	WaitCal();
	*********************************************/
	
	if (pr)
		Priority();
	WaitCal();
	Display2();

	glutMainLoop();
	return 0;
}

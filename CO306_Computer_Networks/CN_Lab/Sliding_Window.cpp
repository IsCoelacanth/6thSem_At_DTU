// #include<iostream>
// #include<stdlib.h>
// #include<time.h>
// #include<math.h>
// #define TOT_FRAMES 500
// #define FRAMES_SEND 10
// using namespace std;
// int recv = 0;
// class sel_repeat
// {
// private:
// 	int fr_send_at_instance;
// 	int arr[TOT_FRAMES];
// 	int send[FRAMES_SEND];
// 	int rcvd[FRAMES_SEND];
// 	char rcvd_ack[FRAMES_SEND];
// 	int sw;
// 	int rw;       //tells expected frame
// public:
// 	void input();
// 	void sender(int);
// 	void receiver(int);
// };
// void sel_repeat::input()
// {
// 	int n;     //no. of bits for the frame
// 	int m;    //no. of frames from n bits
// 	int i;
// 	cout << "Number of bits to be sent : ";
// 	cin >> n;
// 	m = pow(2, n);
// 	int t = 0;
// 	fr_send_at_instance = (m / 2);
// 	for (i = 0; i<TOT_FRAMES; i++)
// 	{
// 		arr[i] = t;
// 		t = (t + 1) % m;
// 	}
// 	for (i = 0; i<fr_send_at_instance; i++)
// 	{
// 		send[i] = arr[i];
// 		rcvd[i] = arr[i];
// 		rcvd_ack[i] = 'n';
// 	}
// 	rw = sw = fr_send_at_instance;
// 	sender(m);
// }
// void sel_repeat::sender(int m)
// {
// 	for (int i = 0; i<fr_send_at_instance; i++)
// 	{
// 		if (rcvd_ack[i] == 'n')
// 			cout << "SENT : Frame " << send[i] << " \n";
// 	}
// 	receiver(m);
// }
// void sel_repeat::receiver(int m)
// {
// 	time_t t;
// 	int f, j, f1, a1;
// 	char ch;
// 	srand((unsigned)time(&t));
// 	for (int i = 0; i<fr_send_at_instance; i++)
// 	{
// 		if (rcvd_ack[i] == 'n')
// 		{
// 			f = rand() % 10;
// 			//if f=5 frame is discarded for some reason
// 			//else frame is correctly recieved
// 			if (f != 5)
// 			{
// 				for (int j = 0; j<fr_send_at_instance; j++)
// 					if (rcvd[j] == send[i])
// 					{
// 						cout << "RECIEVED CORRECTLY FRAME : " << rcvd[j] << "\n";
// 						rcvd[j] = arr[rw];
// 						recv++;
// 						rw = (rw + 1) % m;
// 						break;
// 					}
// 				int j;
// 				if (j == fr_send_at_instance)
// 					cout << "DUPLICATE FRAME : " << send[i] << " DELETING\n";
// 				a1 = rand() % 5;
// 				//if al==3 then ack is lost
// 				//else recieved
// 				if (a1 == 3)
// 				{
// 					cout << "\t[ACK] " << send[i] << " LOST\n";
// 					cout << "\tSENDER TIMED OUT \tRESENDING\n";
// 					rcvd_ack[i] = 'n';
// 				}
// 				else
// 				{
// 					cout << "\t[ACK] " << send[i] << " RECIEVED)\n";
// 					rcvd_ack[i] = 'p';
// 				}
// 			}
// 			else
// 			{
// 				int ld = rand() % 2;
// 				//if =0 then frame damaged
// 				//else frame lost
// 				if (ld == 0)
// 				{
// 					cout << " DAMAGED FRAME RECEIVED || FRAME : " << send[i] << " \n";
// 					cout << " Receiver Side : Negative Acknowledgement " << send[i] << " sent\n";
// 				}
// 				else
// 				{
// 					cout << "@Frame Receiver Side : " << send[i] << " is lost\n";
// 					cout << "(Sender Timeout--------> please resend frame)\n";
// 				}
// 				rcvd_ack[i] = 'n';
// 			}
// 		}
// 	}
// 	for (int j = 0; j<fr_send_at_instance; j++)
// 	{
// 		if (rcvd_ack[j] == 'n')
// 			break;
// 	}
// 	int i = 0;
// 	for (int k = j; k<fr_send_at_instance; k++)
// 	{
// 		send[i] = send[k];
// 		if (rcvd_ack[k] == 'n')
// 			rcvd_ack[i] = 'n';
// 		else
// 			rcvd_ack[i] = 'p';
// 		i++;
// 	}
// 	if (i != fr_send_at_instance)
// 	{
// 		for (int k = i; k<fr_send_at_instance; k++)
// 		{
// 			send[k] = arr[sw];
// 			sw = (sw + 1) % m;
// 			rcvd_ack[k] = 'n';
// 		}
// 	}
// 	if (recv == m - 1)
// 		exit(0);
// 	cout << "do want to continue ";
// 	cin >> ch;
// 	cout << "\n";
// 	if (ch == 'y')
// 		sender(m);
// 	else
// 		exit(0);
// }
// int main()
// {
// 	sel_repeat sr;
// 	sr.input();
// }

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

//Global time
int globalTime = 0;

//the area till which the receiver has acknowedged
int receiverAck;  

// To determine the efficiency of the network
float percentageEff;
int numberPacketsLost;

//The sender window. SWP stands for Sender window pointer. The four
//entries are packetNumber, time of generation, time of receipt of acknowledgement, time of timeout
int sender[10][4];
int SWPToSend = 0;
int SWPToReceive = 0;

//Various times for the network
int transmitTime;
int generationTime;
int timeOut;


//This will generate packet
void generate(int genTime,int packetNo)
{
    if(packetNo<11)cout<<"Packet number "<<packetNo<<" is generated at time = "<<genTime<<endl;
    //Entering all values into sended window
    sender[SWPToSend][0] = packetNo;
    sender[SWPToSend][1] = genTime;
    sender[SWPToSend][2] = 0;
    sender[SWPToSend][3] = 0;
    
    
    //Determing if the packet will reach safely
    int randTemp = rand()%100;
    if(randTemp<numberPacketsLost)
    {
        if(packetNo<11)cout<<"This packet will be lost in transit"<<endl<<endl;
        //Setting the time out time
        sender[SWPToSend][3] = genTime+timeOut;
    }
    else
    {
        if(packetNo<11)cout<<"This packet will reach safely"<<endl<<endl;
        //Setting the time at which the acknowledgement will be received
        sender[SWPToSend][2] = genTime+2*transmitTime;
    }
    
}

void goBack()
{
    //Building the senderWindow
    for(int i = 0; i<10; i++)
    {
        for(int j = 0; j<4; j++)
        {
            sender[i][j] = 0;
        }
    }        
                
    int packetNumber = 1;
    while(true)
    {
        bool timeOutOcc = false;
        if(sender[SWPToReceive][2]<=globalTime+generationTime&&sender[SWPToReceive][2]!=0)
        {
            //Packet received is acknowledged
            cout<<"Packet Number "<<sender[SWPToReceive][0]<<" has been acknowledged at time = "<<sender[SWPToReceive][2]<<endl;
            if(sender[SWPToReceive][0]==10)break;
            SWPToReceive = (SWPToReceive+1)%10;
            
        }
        else if(sender[SWPToReceive][3]<=globalTime+generationTime&&sender[SWPToReceive][3]!=0)
        {
            //Some earlier Packet has caused timeout
            cout<<"!!!Time out in packet number "<<sender[SWPToReceive][0]<<" has occured at time = "<<sender[SWPToReceive][3]<<"!!!"<<endl;
            SWPToSend = SWPToReceive;
            packetNumber = sender[SWPToReceive][0];
            timeOutOcc = true;
        }
        
        globalTime = globalTime+generationTime;
        
        if(timeOutOcc)
        {
            globalTime = sender[SWPToReceive][3];
        }        
            
        
        if(sender[SWPToReceive][0]==0)
        {
            generate(globalTime, packetNumber);
            packetNumber++;
            SWPToSend = (SWPToSend+1)%10;
        }    
        else if(sender[(SWPToSend-1+10)%10][0]<11)
        {
            generate(globalTime, packetNumber);
            packetNumber++;
            SWPToSend = (SWPToSend+1)%10;
        }
        
    }
}        
            
int main()
{
    cout<<"Enter the times for different network parameters:"<<endl;
    cout<<"Generation Time (ms):";cin>>generationTime;
    cout<<"Transmission Time (ms):";cin>>transmitTime;               
    cout<<"TimeOut Time (ms):";cin>>timeOut;cout<<endl;
    
    cout<<"Enter The percentage efficiency:";cin>>percentageEff;
    numberPacketsLost = 100 -(int)percentageEff;

    cout<<endl<<"Running Go back N"<<endl;
    for(int i = 0; i<30;i++)cout<<"_";
    cout<<endl<<endl;
    goBack();
    
    system("pause");
    return 0;
} 
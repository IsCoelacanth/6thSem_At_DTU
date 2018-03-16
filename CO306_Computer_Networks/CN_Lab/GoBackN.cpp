#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define EFF 60 // Network efficiency
#define GEN 1 // frequency at which a pakcet is generated.
#define TRN 1 // Transmission time of medium
#define TOUT 2 // Timeout window for the sender
// Time counter for sync
int SysTime = 0;

int LastAckRec;  // The lasy acknowledgement thats been received.

int numberPacketsLost;

int sender[10][4];
// Sender Window Pointer
/* sender[n][0] is packet no.
sender[n][1] is send time of packet.
sender[n][2] is the ack time of packet
sender[n][3] is the timeout time.
*/
int SWPToSend = 0;
int SWPToReceive = 0;



// Packet generator 
void generate(int genTime, int packetNo)
{
	if (packetNo<11)
		cout << "Generated Packet    : " << packetNo << " at time : " << genTime << endl;

	sender[SWPToSend][0] = packetNo;
	sender[SWPToSend][1] = genTime;
	sender[SWPToSend][2] = 0;
	sender[SWPToSend][3] = 0;


	int randTemp = rand() % 100;
	if (randTemp<numberPacketsLost)
	{
		sender[SWPToSend][3] = genTime + TOUT; // packet is lost.
	}
	else
	{
		sender[SWPToSend][2] = genTime + 2 * TRN; // packet reaches safely.
	}

}

void goBack()
{
	//Building the senderWindow
	for (int i = 0; i<10; i++)
	{
		for (int j = 0; j<4; j++)
		{
			sender[i][j] = 0;
		}
	}

	int packetNumber = 1;
	while (true)
	{
		bool TOUTOcc = false;
		if (sender[SWPToReceive][2] <= SysTime + GEN && sender[SWPToReceive][2] != 0)
		{
			//Sending ack
			cout << "Acknowledged packet : " << sender[SWPToReceive][0] << " at time : " << sender[SWPToReceive][2] << endl;
			if (sender[SWPToReceive][0] == 10)
				break;
			SWPToReceive = (SWPToReceive + 1) % 10;

		}
		else if (sender[SWPToReceive][3] <= SysTime + GEN&&sender[SWPToReceive][3] != 0)
		{
			// Timeout detected.
			cout << "Time out at : " << sender[SWPToReceive][3] << " for packet : " << sender[SWPToReceive][0] << endl;
			SWPToSend = SWPToReceive;
			packetNumber = sender[SWPToReceive][0];
			TOUTOcc = true;
		}

		SysTime = SysTime + GEN;

		if (TOUTOcc)
		{
			SysTime = sender[SWPToReceive][3];
		}


		if (sender[SWPToReceive][0] == 0)
		{
			generate(SysTime, packetNumber);
			packetNumber++;
			SWPToSend = (SWPToSend + 1) % 10;
		}
		else if (sender[(SWPToSend - 1 + 10) % 10][0]<11)
		{
			generate(SysTime, packetNumber);
			packetNumber++;
			SWPToSend = (SWPToSend + 1) % 10;
		}

	}
}

int main()
{
	cout << "Go back N sliding window protocol at network efficiency of 60%" << endl;

	numberPacketsLost = 100 - (int)EFF;

	cout << endl << "Running Go back N" << endl;
	for (int i = 0; i<30; i++)
		cout << "_";

	cout << endl << endl;
	goBack();

	return 0;
}
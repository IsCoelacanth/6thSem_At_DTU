#include<windows.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#define TOUT 5
#define M_Seq 1
#define M_Pack 45
//#define increment(k) if(k<M_Seq) k++; else k = 0;

void increment(int &k)
{
	if (k < M_Seq)
		k++;
	else
		k = 0;
}
enum event_type
{
	frame_arr, error, t_out, no_e
};

struct packet
{
	int data;
};

struct frame
{
	int type;
	int seq;
	int acc;
	packet inf;
	int error;
};

frame DATA;

int i = 1; //To hold seq numbers
char turn; //To switch between sender and receiver 
int dc = 0; //To check if connection should be terminated or not.

void from_net_layer(packet &bff)
{
	bff.data = i;
	i++;
}

void to_phy_layer(frame &s)
{
	s.error = rand() % 10; //The probability of getting an error is 0.10
	DATA = s; // The data is now on the physical layer
}

void to_net_layer(packet &bff)
{
	cout << " | Reciver side : Packet No. " << bff.data << " recieved" << endl;
	if (i > M_Pack)
	{
		dc = 1;
		cout << "Disconnected from the network" << endl;
	}
}

void from_phy_layer(frame &bff)
{
	bff = DATA;
}

void Wait_Sender_event(event_type &e)
{
	static int timer = 0;

	if (turn == 's')
	{
		timer++;
		if (timer == TOUT)
		{
			e = t_out;
			cout << "SENDER : Acknowlegement not recieved : TIMEOUT" << endl;
			timer = 0;
			return;
		}
		if (DATA.error == 0)
			e = error;
		else
		{
			timer = 0;
			e = frame_arr;
		}
	}
}

void Wait_Reciever_event(event_type &e)
{
	if (turn == 'r')
	{
		if (DATA.error == 0)
			e = error;
		else
			e = frame_arr;
	}
}

void sender()
{
	static int to_send = 0;
	static frame s;
	packet bff;
	event_type event;
	static int flag = 0;

	if (flag == 0)
	{
		from_net_layer(bff);
		s.inf = bff;
		s.seq = to_send;

		cout << "Sender : Data " << s.inf.data << " Seq No. " << s.seq;
		turn = 'r';
		to_phy_layer(s);
		flag = 1;
	}

	Wait_Sender_event(event);

	if (turn == 's')
	{
		if (event == frame_arr)
		{
			from_net_layer(bff);
			increment(to_send);
			s.inf = bff;
			s.seq = to_send;
			cout << "Sender : Data " << s.inf.data << " Seq No. " << s.seq;
			turn = 'r';
			to_phy_layer(s);
		}
		if (event == t_out)
		{
			cout << "Sender : Resending lost/unacknowledged frame ";
			turn = 'r';
			to_phy_layer(s);
		}
	}
}

void reciever()
{
	static int expected = 0;
	frame r, s;
	event_type event;

	Wait_Reciever_event(event);

	if (turn == 'r')
	{
		if (event == frame_arr)
		{
			from_phy_layer(r);
			if (r.seq == expected)
			{
				to_net_layer(r.inf);
				increment(expected);
			}
			else
				cout << "Resending acknowledgement" << endl;
			turn = 's';
			to_phy_layer(s);

		}

		if (event == error)
		{
			cout << "Corrupted data or lost data, frame not recieved" << endl;
			turn = 's';
		}
	}
}

int main()
{
	while (!dc)
	{
		sender();
		Sleep(200);
		reciever();
	}
	return 0;
}
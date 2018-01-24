# AIM : To implement the data link layer framing methods such as Bit stuffing.

## Introduction and Theory:

Security and error detection are the most prominent features that are to be provided by the application which transfers data from one end to the other. One such mechanism in tracking errors which may add up to the original data during transfer is *"Stuffing"* . 

Stuffing is of two types: 

1) Bit stuffing 

2) Character stuffing

### Bit Stuffing

* In Bit-Stuffing a special bit pattern "01111110" is inserted at the start and end of the bit stream and the patterns are broken up by inserting '0s' at a set window (e.g 5). These newly inserted bits are non informative bits.
* Bit stuffing is used for various purposes, such as for bringing bit streams that do not necessarily have the same or rationally related bit rates up to a common rate, or to fill buffers or frames. The location of the stuffing bits is communicated to the receiving end of the data link, where these extra bits are removed to return the bit streams to their original bit rates or form. Bit stuffing may be used to synchronize several channels before multiplexing or to rate-match two single channels to each other

## Algorithm:

```python
1. insert "01111110" into the input sequence.
2. Start with the original sequence.
3. for every 0:
4.    if it is followed by 6 1's:
5.    	Insert a 0 after the 5th one to break the sequence
6. insert "01111110" into the output sequence's end.
7. return the new sequence.
```

## Code:

```c++
#include<iostream>
#include<string>
using namespace std;

int main()
{
    int len, count;
	string S;
	cout << "Enter the bit sequence : ";
	cin >> S;
	len = S.length();

	for (int i = 0; i < len; i++)
	{
		count = 0;
		for (int j = i; j < (i + 5); j++)
		{
			if (S[j] == '1')
			{
				count++;
			}
		}
		if (count == 5)
		{
			int n1 = len + 2;
			for (; n1 > i+5 ; n1--)
			{
				S[n1] = S[n1 - 1];
			}
			S[i + 5] = '0';
			i += 6;
		}
	}

	cout << "The string after stuffing is : ";
	cout << "01111110 ";
	cout << S;
	cout << "01111110" << endl;
	return 0;
}
```

## Output:

![BitStuffingPic](../outputs/bitstuffing.PNG)

## Findings and Learnings:

1. Bit stuffing allows for the implementation of synchronous multiplexing.
2.  It is also used in run length limited coding to limit the number of consecutive bits of the same value in the data to be transmitted. A bit of the opposite value is inserted after the maximum allowed number of consecutive bits.
3. To recover the original data from the stuffed signal, De-Stuffing is used.
4. Bit stuffing does not ensure that the payload is intact (*i.e.* not corrupted by transmission errors); it is merely a way of attempting to ensure that the transmission starts and ends at the correct places.


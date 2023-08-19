#include <iostream>
#include <cmath>
using namespace std;

int* sender();
int* receiver();

int main()
{
    char input;

    cout << "Sender (s/S) or Receiver (r/R)?" << endl;
    cin >> input;

    input = toupper(input);

    switch (input)
    {
        case 'S':
            cout << "Finding bits to be transmitted." << endl;
            sender();

            break;

        case 'R':
            cout << "Finding the message sent by the sender." << endl;
            receiver();

            break;
    }



    return 0;
}

int* sender()
{
    int bits;
    int redundantBits;
    int parity; //1 for even, 0 for odd


    cout << "How many data bits?" << endl;
    cin >> bits;

    while (pow(2, redundantBits) < (bits + redundantBits + 1))
    {
        redundantBits += 1;
    }

    cout << redundantBits << endl;

    int* set = new int[bits + redundantBits];


    return set;

}

int* receiver()
{
    int* set;

    return set;
}


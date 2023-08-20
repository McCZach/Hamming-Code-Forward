#include <iostream>
#include <cmath>
using namespace std;

int* sender();
int* receiver();

int main()
{
    char input;

    cout << "Sender (S/s) or Receiver (R/r)?" << endl;
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
    int dataBits,
        redundantBits,
        parity;     //1 for odd, 0 for even

    int input;


    cout << "How many data bits?" << endl;
    cin >> dataBits;
    while (pow(2, redundantBits) < (dataBits + redundantBits + 1))
    {
        redundantBits += 1;
    }
    int totalBits = dataBits + redundantBits;
    int* set = new int[totalBits];

    cout << "What is the parity? (1 for odd/0 for even)" << endl;
    cin >> parity;

    int count = 0;
    for (int i = totalBits; i > 0; i--)
    {
        if ((i & (i - 1)) != 0)
        {
            cout << "What is the bit to be transmitted? D" << i << endl;
            cin >> input;
            set[i] = input;
        }
    }

    for (int i = 1; i <= totalBits; i++)
    {
        if ((i & (i - 1)) == 0)
        {
            int* group = new int [dataBits];

            int count = 0;
            int index = i;

            while (count < dataBits)
            {
                int take = i,
                    skip = i;

                while (take > 0)
                {
                    group[count] = set[index];
                    count += 1;
                    index += 1;
                    take -= 1;
                }

                while (skip > 0)
                {
                    index += 1;
                    skip -= 1;
                }
            }
            //Group is properly created

            int numOnes = 0;
            for (int j = 1; j < dataBits; j++)
            {
                if (group[j] == 1)
                    numOnes += 1;
            }

            //Determine rBit based on parity
            int rBit;
            if (parity == 1)
                if (numOnes % 2 == 0)
                    rBit = 1;
                else
                    rBit = 0;
            
            if (parity == 0)
                if (numOnes % 2 == 0)
                    rBit = 0;
                else
                    rBit = 1;

            set[i] = rBit;

            cout << rBit << endl;

            delete [] group;
        }
    }

    cout << "REVERSE" << endl;
    for (int i = totalBits; i > 0; i--)
    {
        cout << set[i] << endl;
    }

    return set;
}

int* receiver()
{
    int* set;

    return set;
}
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

void sender();
void getInput(int& bits, int& par);

void receiver();

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

void sender()
{
    int dataBits,
        redundantBits,
        parity;     //1 for odd, 0 for even

    int input;

    getInput(dataBits, parity);

    while (pow(2, redundantBits) < (dataBits + redundantBits + 1))
    {
        redundantBits += 1;
    }
    int totalBits = dataBits + redundantBits;
    int* set = new int[totalBits];

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
                numOnes += group[j];
            }

            //Determine rBit based on parity
            int rBit;
            rBit = (numOnes + parity) % 2;

            set[i] = rBit;

            delete [] group;
        }
    }

    cout << "Data Transmitted." << endl;
    for (int i = totalBits; i > 0; i--)
    {
        cout << set[i];
    }

}

void getInput(int& bits, int& par)
{
    cout << "How many data bits?" << endl;
    cin >> bits;

    cout << "What is the parity? (1 for odd/0 for even)" << endl;
    cin >> par;
}

void receiver()
{
    int* set,
         errorList;

    int totalBits,
        redundantBits,
        dataBits,
        parity,     //1 for odd, 0 for even
        input;


    cout << "How many total bits were sent?" << endl;
    cin >> totalBits;
    cout << endl;

    cout << "How many bits is the message by sender?" << endl;
    cin >> dataBits;
    cout << endl;

    cout << "What is the parity? (1 for odd/0 for even)" << endl;
    cin >> parity;
    cout << endl;

    set = new int[totalBits];
    redundantBits = (totalBits - dataBits);

    for (int i = totalBits; i > 0; i--)
    {
        cout << "What was the bit transmitted? D" << i << endl;
        cin >> input;
        set[i] = input;
    }

    for (int i = 1; i <= totalBits; i++)
    {
        if ((i & (i - 1)) == 0)
        {
            int* group = new int [dataBits];
            int* indices = new int[dataBits];

            int count = 0;
            int index = i;

            while (count < dataBits)
            {
                int take = i,
                    skip = i;

                while (take > 0)
                {
                    group[count] = set[index];
                    indices[count] = i;
                    
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
                numOnes += group[j];
            }

            if (numOnes % 2 != parity)

           

            delete [] group;
        }
    }
}
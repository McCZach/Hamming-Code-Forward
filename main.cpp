#include <iostream>
#include <cmath>
#include <string>
using namespace std;

#include "AList.h"

void sender();
void getInputSender(int& bits, int& par);

void receiver();
void getInputReciever(int & tBits, int & dBits, int & par);

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

    getInputSender(dataBits, parity);

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

    delete [] set;
}

void getInputSender(int& bits, int& par)
{
    cout << "How many data bits? ";
    cin >> bits;
    cout << endl;

    cout << "What is the parity? (1 for odd/0 for even) ";
    cin >> par;
    cout << endl;
}

void getInputReciever(int & tBits, int & dBits, int & par)
{
    cout << "How many total bits were received? ";
    cin >> tBits;
    cout << endl;

    cout << "How many bits was the message by sender? ";
    cin >> dBits;
    cout << endl;

    cout << "What is the parity? (1 for odd/0 for even) ";
    cin >> par;
    cout << endl;
}

void receiver()
{
    int* set;

    int totalBits,
        dataBits,
        parity,
        redundantBits,
        input,
        errorIndex;

    bool found = false;

    getInputReciever(totalBits, dataBits, parity);

    set = new int[totalBits];

    redundantBits = (totalBits - dataBits);

    AList<int> errorList(dataBits * redundantBits);
    AList<int> indexList(dataBits * redundantBits);

    for(int i = totalBits; i > 0; i--)
    {
        cout << "What was the bit transmitted? D" << i << endl;
        cin >> input;
        set[i] = input;
    }
    cout << endl;

    for (int i = 1; i <= totalBits; i++)
    {
        if ((i & (i - 1)) == 0)
        {
            AList<int> binaryGroup(dataBits);

            int counter = 0,
                index = i;

            while (counter < dataBits)
            {
                int take = i,
                    skip = i;
                
                while (take > 0)
                {
                    binaryGroup.insertBack(set[index]);
                    indexList.insertBack(index);

                    counter += 1;
                    index += 1;
                    take -= 1;
                }

                while (skip > 0)
                {
                    index += 1;
                    skip -= 1;
                }
            }

            int numOnes = 0;
            for (int j = 0; j < dataBits; j++)
            {
                int temp;
                binaryGroup.retrieveAtIndex(temp, j);
                numOnes += temp;
            }

            if (numOnes % 2 != parity)
            {
                for (int k = 0; k < dataBits; k++)
                {
                    int temp;
                    indexList.removeBack(temp);
                    errorList.insertBack(temp);
                }
            }

            binaryGroup.clear();
        }
    }
   
    if (!errorList.isEmpty())
    {
        while(!found)
        {
            int temp;

            for (int i = 0; i < errorList.getNumValues(); i++)
            {
                errorList.retrieveAtIndex(temp, i);

                if (!indexList.retrieve(temp))
                {
                    found = true;
                    errorIndex = temp;
                }
            }
        }

        cout << "ERROR DETECTED IN TRANSMISSION!" << endl;
        cout << "The Index: " << errorIndex << " needs to be flipped!" << endl;
        *(set + errorIndex) += 1;
        *(set + errorIndex) %= 2;
        cout << "THE MESSAGE HAS BEEN FIXED!" << endl;
        cout << "THE CORRECTED MESSAGE IS NOW: ";
        for (int i = totalBits; i > 0; i--)
        {
            cout << *(set + i);
        }

    }

    delete [] set;
}
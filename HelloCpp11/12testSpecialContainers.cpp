//#define MAIN
#ifdef MAIN

#include <iostream>
#include <cstdlib>
#include <stack>
#include <queue>
#include <string>
#include <bitset>
using namespace std;

int main()
{
    cout << "test 1" << endl;
    {
        stack<int> st;
        // push three elements into the stack
        st.push(1);
        st.push(2);
        st.push(3);
        // pop and print two elements from the stack
        cout << st.top() << ' ';
        st.pop();
        cout << st.top() << ' ';
        st.pop();
        // modify top element
        st.top() = 77;
        // push two new elements
        st.push(4);
        st.push(5);
        // pop one element without processing it
        st.pop();
        // pop and print remaining elements
        while (!st.empty()) {
            cout << st.top() << ' ';
            st.pop();
        }
        cout << endl;
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        queue<string> q;
        // insert three elements into the queue
        q.push("These ");
        q.push("are ");
        q.push("more than ");
        // read and print two elements from the queue
        cout << q.front();
        q.pop();
        cout << q.front();
        q.pop();
        // insert two new elements
        q.push("four ");
        q.push("words!");
        // skip one element
        q.pop();
        // read and print two elements
        cout << q.front();
        q.pop();
        cout << q.front() << endl;
        q.pop();
        // print number of elements in the queue
        cout << "number of elements in the queue: " << q.size()
            << endl;
    }
    cout << endl;

    cout << "test 3" << endl;
    {
        priority_queue<float> q;
        // insert three elements into the priority queue
        q.push(66.6);
        q.push(22.2);
        q.push(44.4);
        // read and print two elements
        cout << q.top() << ' ';
        q.pop();
        cout << q.top() << endl;
        q.pop();
        // insert three more elements
        q.push(11.1);
        q.push(55.5);
        q.push(33.3);
        // skip one element
        q.pop();
        // pop and print remaining elements
        while (!q.empty()) {
            cout << q.top() << ' ';
            q.pop();
        }
        cout << endl;
    }
    cout << endl;

    cout << "test 4" << endl;
    {
        const int numColor = 6;
        // enumeration type for the bits
        // - each bit represents a color
        enum Color {
            red, yellow, green, blue, white, black
        };
        // create bitset for all bits/colors
        bitset<numColor> usedColors;
        // set bits for two colors
        usedColors.set(red); // 设置第0 位的值为1
        usedColors.set(blue);// 设置第3 位的值为1
        // print some bitset data
        cout << "bitfield of used colors: " << usedColors << endl;
        cout << "number of used colors: " << usedColors.count() << endl;
        cout << "bitfield of unused colors: " << ~usedColors << endl;
        // if any color is used
        if (usedColors.any()) 
        {
            // loop over all colors
            for (int c = 0; c < numColor; ++c) 
            {
                // if the actual color is used
                if (usedColors[(Color)c]) 
                {
                    cout << c << " 位被使用" << endl;
                }
            }
        }
    }
    cout << endl;

    cout << "test 4" << endl;
    {
        // print some numbers in binary representation
        cout << "267 as binary short: "
            << bitset<numeric_limits<unsigned short>::digits>(267)
            << endl;
        cout << "267 as binary long: "
            << bitset<numeric_limits<unsigned long>::digits>(267)
            << endl;
        cout << "10,000,000 with 24 bits: "
            << bitset<24>(1e7) << endl;
        // write binary representation into string
        string s = bitset<42>(12345678).to_string();
        cout << "12,345,678 with 42 bits: " << s << endl;
        // transform binary representation into integral number
        cout << "\"1000101011\" as number: "
            << bitset<100>("1000101011").to_ullong() << endl;

    }
    cout << endl;

    return EXIT_SUCCESS;
}

#endif
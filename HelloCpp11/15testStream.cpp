#define MAIN
#ifdef MAIN

// 一般在头文件中包含, 而在实现文件中再包含具体用到的头(如 iostream, fstream)
// iosfwd 内含 stream class 的前置声明, 这个文件是必要的
#include <iosfwd> 
#include <iostream>
#include <bitset>
#include <complex>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include <fstream>
using namespace std;
using namespace std;

// test 4
namespace MyLib {
    double readAndProcessSum1(std::istream& strm);
    double readAndProcessSum2(std::istream& strm);
}

// test 6
// forward declarations
void writeCharsetToFile(const string& filename);
void outputFile(const string& filename);

int main()
{
    cout << "test 1" << endl;
    {
        //double x, y; // operands
        //             // print header string
        //cout << "Multiplication of two floating point values" << endl;
        //// read first operand
        //cout << "first operand: ";
        //if (!(cin >> x)) {
        //    // input error
        //    // => error message and exit program with error status
        //    cerr << "error while reading the first floating value"
        //        << endl;
        //    return EXIT_FAILURE;
        //}
        //// read second operand
        //cout << "second operand: ";
        //if (!(cin >> y)) {
        //    // input error
        //    // => error message and exit program with error status
        //    cerr << "error while reading the second floating value"
        //        << endl;
        //    return EXIT_FAILURE;
        //}
        //// print operands and result
        //cout << x << " times " << y << " equals " << x * y << endl;
    }
    cout << endl;

    cout << "test 2" << endl;
    {
        string s("hello");
        cout << s << endl;

        bitset<10> flags(7);
        cout << flags << endl;

        complex<float> c(3.1, 7.4);
        cout << c << endl;
    }
    cout << endl;

    cout << "test 3" << endl;
    {// process and print current date and time:
        //auto now = chrono::system_clock::now();
        //time_t t = chrono::system_clock::to_time_t(now);
        //tm* nowTM = localtime(&t);
        //cout << put_time(nowTM, "date: %x\ntime: %X\n") << endl;
        //// read date:
        //tm* date;
        //cout << "new date: ";
        //cin >> get_time(date, "%x"); // read date
        //if (!cin) {
        //    cerr << "invalid format read" << endl;
        //}

    }
    cout << endl;

    cout << "test 4" << endl;
    {
        //double sum = 0;
        //try {
        //    sum = MyLib::readAndProcessSum1(cin);
        //}
        //catch (const ios::failure& error) {
        //    cerr << "I/O exception: " << error.what() << endl;
        //}
        //catch (const exception& error) {
        //    cerr << "standard exception: " << error.what() << endl;
        //}
        //catch (...) {
        //    cerr << "unknown exception" << endl;
        //}
        //// print sum
        //cout << "sum: " << sum << endl;
    }
    cout << endl;

    cout << "test 5" << endl;
    {
        //char c;
        //// while it is possible to read a character
        //while (cin.get(c)) {
        //    // print it
        //    cout.put(c);
        //}
    }
    cout << endl;

    cout << "test 6" << endl;
    {
        writeCharsetToFile("charset.out");
        outputFile("charset.out");
    }
    cout << endl;

    return EXIT_SUCCESS;
}



namespace MyLib {
    double readAndProcessSum1(std::istream& strm)
    {
        using std::ios;
        double value, sum;
        // save current state of exception flags
        ios::iostate oldExceptions = strm.exceptions();
        // let failbit and badbit throw exceptions
        // - NOTE: failbit is also set at end-of-file
        strm.exceptions(ios::failbit | ios::badbit);
        try {
            // while stream is OK
            // - read value and add it to sum
            sum = 0;
            while (strm >> value) {
                sum += value;
            }
        }
        catch (...) {
            // if exception not caused by end-of-file
            // - restore old state of exception flags
            // - rethrow exception
            if (!strm.eof()) {
                strm.exceptions(oldExceptions); // restore exception flags
                throw; // rethrow
            }
        }
        // restore old state of exception flags
        strm.exceptions(oldExceptions);
        // return sum
        return sum;
    }

    double readAndProcessSum2(std::istream& strm)
    {
        double value, sum;
        // while stream is OK
        // - read value and add it to sum
        sum = 0;
        while (strm >> value) {
            sum += value;
        }
        if (!strm.eof()) {
            throw std::ios::failure
            ("input error in readAndProcessSum()");
        }
        // return sum
        return sum;
    }
}

void writeCharsetToFile(const string& filename)
{
    // open output file
    ofstream file(filename);
    // file opened?
    if (!file) {
        // NO, abort program
        cerr << "can’t open output file \"" << filename << "\""
            << endl;
        exit(EXIT_FAILURE);
    }
    // write character set
    for (int i = 32; i<256; ++i) {
        file << "value: " << setw(3) << i << " "
            << "char: " << static_cast<char>(i) << endl;
    }
} // closes file automatically

void outputFile(const string& filename)
{
    // open input file
    ifstream file(filename);
    // file opened?
    if (!file) {
        // NO, abort program
        cerr << "can’t open input file \"" << filename << "\""
            << endl;
        exit(EXIT_FAILURE);
    }

    // copy file contents to cout
    // mothod 1:
    //char c;
    //while (file.get(c)) {
    //    cout.put(c);
    //}
    // mothod 2:
    // 一次输出所有内容, 将一个"指向 file stream 缓冲区" 的pointer 当作实参传给 operator <<
    cout << file.rdbuf();

} // closes file automatically
#endif
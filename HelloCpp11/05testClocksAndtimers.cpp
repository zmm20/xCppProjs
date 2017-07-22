#define MAIN
#ifdef MAIN

#include <iostream>
#include <vector>
#include <algorithm>
#include <ratio>
#include <chrono>
#include <iomanip>
#include <thread>
#include <string>
#include <ctime>


using namespace std;

template <typename V, typename R>
ostream& operator << (ostream& s, const chrono::duration<V, R>& d)
{
    s << "[" << d.count() << " of " << R::num << "/"
    << R::den << "]";
    return s;
}

template <typename C>
void printClockData();
std::string asString(const std::chrono::system_clock::time_point& tp);

inline chrono::system_clock::time_point makeTimePoint (int year, int mon, int day, int hour, int min, int sec=0);

int main()
{
    cout << "-----------05testClocksAndTimers.cpp-------------" << endl;
    cout << " duration test " << endl;
    cout << "test 1" << endl;
    {
        // ʱ�� ����
        std::chrono::duration<int> twentySeconds(20);
        std::chrono::duration<double, std::ratio<60>> halfAMinute(0.5);
        std::chrono::duration<long, std::ratio<1, 1000>> oneMillisecond(1);
    }
    cout << endl;
    
    cout << "test 2:" << endl;
    {
        std::chrono::seconds twentySeconds(20); // 20 seconds
        cout << twentySeconds << " seconds" << endl;
        std::chrono::hours aDay(24); // 24 hours
        cout << aDay << " days" << endl;
        std::chrono::milliseconds ms(0); // 0 milliseconds
        cout << ms << " milliseconds" << endl;
        
        ms = twentySeconds + aDay; // 86,400,000 milliseconds
        --ms; // 86,399,999 milliseconds
        ms *= 2; // 172,839,998 milliseconds
        cout << ms.count() << " ms" << endl;
        cout << std::chrono::nanoseconds(ms).count() << " ns" << endl << endl;
    }
    cout << endl;
    
    
    cout << "test 3:" << endl;
    {
        std::chrono::seconds sec(55);
        //std::chrono::minutes m1 = sec; // ERROR, ���ǿ��Է���ת��
        std::chrono::minutes m2 = std::chrono::duration_cast<std::chrono::minutes>(sec); // OK
        cout << m2 << " minutes" << endl << endl;
    }
    cout << endl;
    
    
    cout << "test 4:" << endl;
    {
        
        std::chrono::duration<double, std::ratio<60>> halfMin(0.5);
        //std::chrono::seconds s1 = halfMin; // ERROR
        std::chrono::seconds s2 = std::chrono::duration_cast<std::chrono::seconds>(halfMin); // OK
        cout << s2 << " seconds" << endl << endl;
    }
    cout << endl;
    
    
    cout << "test 5:" << endl;
    {
        using namespace std::chrono;
        milliseconds ms(7255042);
        // split into hours, minutes, seconds, and milliseconds
        hours hh = duration_cast<hours>(ms);
        minutes mm = duration_cast<minutes>(ms % chrono::hours(1)); // �ɺ��뵽���ӵ�ת��, �������%, ����Ҫ��duration_cast ��ʾת��
        seconds ss = duration_cast<seconds>(ms % chrono::minutes(1));
        milliseconds msec = duration_cast<milliseconds>(ms % chrono::seconds(1));
        // and print durations and values:
        cout << "raw: " << hh << "::" << mm << "::"
        << ss << "::" << msec << endl;
        cout << " " << setfill('0') << setw(2) << hh.count() << "::"
        << setw(2) << mm.count() << "::"
        << setw(2) << ss.count() << "::"
        << setw(3) << msec.count() << endl << endl;
    }
    cout << endl;
    
    
    // Clock �����һ�� epoch ��һ�� tick ����
    cout << "clock test" << endl;
    cout << "test 6: " << endl;
    {
        std::cout << "system_clock: " << std::endl;
        printClockData<std::chrono::system_clock>();
        std::cout << "\nhigh_resolution_clock: " << std::endl;
        printClockData<std::chrono::high_resolution_clock>();
        std::cout << "\nsteady_clock: " << std::endl;
        printClockData<std::chrono::steady_clock>();
        cout << endl << endl;
    }
    cout << endl;
    
    
    cout << "test 7: " << endl;
    {
        /*
         ע�⣺ �����Ƚϳ����е�2��ʱ����������ֵ�� Ӧ���� steady_clock
         �� ���´���Ҳ���в�ͨ�� ��Ϊ��� clock �ڴ��ڼ䱻������ ��������ȷ
         */
        // auto system_start = chrono::system_clock::now();
        // std::this_thread::sleep_for(chrono::seconds(2)); // ˯2s
        // auto diff = chrono::system_clock::now() - system_start;
        // auto sec2 = chrono::duration_cast<chrono::seconds>(diff);
        // cout << "this program runs: " << sec2.count() << " seconds" << endl << endl;
        
        auto system_start = chrono::steady_clock::now();
        std::this_thread::sleep_for(chrono::seconds(2)); // ˯2s
        auto diff = chrono::steady_clock::now() - system_start;
        auto sec2 = chrono::duration_cast<chrono::seconds>(diff);
        cout << "this program runs: " << sec2.count() << " seconds" << endl << endl;
    }
    cout << endl;
    
    
    cout << "test 8: " << endl;
    {
        // print the epoch of this system clock:
        std::chrono::system_clock::time_point tp;
        std::cout << "epoch: " << asString(tp) << std::endl;
        // print current time:
        tp = std::chrono::system_clock::now();
        std::cout << "now: " << asString(tp) << std::endl;
        // print minimum time of this system clock:
        tp = std::chrono::system_clock::time_point::min();
        std::cout << "min: " << asString(tp) << std::endl;
        // print maximum time of this system clock:
        tp = std::chrono::system_clock::time_point::max();
        std::cout << "max: " << asString(tp) << std::endl;
    }
    cout << endl;
    
    
    cout << "test 9: " << endl;
    {
        // define type for durations that represent day(s):
        // convert to calendar time // skip trailing newline
        typedef chrono::duration<int,ratio<3600*24>> Days;
        // process the epoch of this system clock
        chrono::time_point<chrono::system_clock> tp;
        cout << "epoch: " << asString(tp) << endl;
        // add one day, 23 hours, and 55 minutes
        tp += Days(1) + chrono::hours(23) + chrono::minutes(55);
        cout << "later: " << asString(tp) << endl;
        // process difference from epoch in minutes and days:
        auto diff = tp - chrono::system_clock::time_point();
        cout << "diff:      "
        << chrono::duration_cast<chrono::minutes>(diff).count()
        << " minute(s)" << endl;
        Days days = chrono::duration_cast<Days>(diff);
        cout << "diff: " << days.count() << " day(s)" << endl;
        // subtract one year (hoping it is valid and not a leap year)
        tp -= chrono::hours(24*365);
        cout << "-1 year: " << asString(tp) << endl;
        // subtract 50 years (hoping it is valid and ignoring leap years)
        tp -= chrono::duration<int,ratio<3600*24*365>>(50);
        cout << "-50 years: " << asString(tp) << endl;
        // subtract 50 years (hoping it is valid and ignoring leap years)
        tp -= chrono::duration<int,ratio<3600*24*365>>(50);
        cout << "-50 years: " << asString(tp) << endl << endl;
    }
    
    cout << "test 10" << endl;
    {
        auto tp1 = makeTimePoint(2010,01,01,00,00);
        std::cout << asString(tp1) << std::endl;
        auto tp2 = makeTimePoint(2011,05,23,13,44);
        std::cout << asString(tp2) << std::endl;
    }
}

template <typename C>
void printClockData()
{
    using namespace std;
    cout << "- precision: ";
    // if time unit is less or equal one millisecond
    typedef typename C::period P; // type of time unit
    if (ratio_less_equal<P, milli>::value) {
        // convert to and print as milliseconds
        typedef typename ratio_multiply<P, kilo>::type TT;
        cout << fixed << double(TT::num) / TT::den
        << " milliseconds" << endl;
    }
    else {
        // print as seconds
        cout << fixed << double(P::num) / P::den << " seconds" << endl;
    }
    cout << "- is_steady: " << boolalpha << C::is_steady << endl;
}

std::string asString(const std::chrono::system_clock::time_point& tp)
{
    std::string ts("");
    
    // convert to system time:
    
    /*
     represents the number of seconds since the UNIX epoch, January 1, 1970
     ע�⣺ ֻ��system_clock �ṩ�� to_time_t() ������ ��Ϊ���� clock ������
     system time ��epoch ��Ϊ�����ڲ��� epoch
     */
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    if (t >=0 && t <= numeric_limits<long>::max())
    {// windows os ���û����䱣���� ���ܻᱨ��
        ts = std::ctime(&t); // convert to calendar time
        //ts = std::asctime(std::localtime(&t));
        ts.resize(ts.size() - 1); // skip trailing newline
    }
    else
    {
        ts = "error";
    }
    
    return ts;
    
}

// convert calendar time to timepoint of system clock
std::chrono::system_clock::time_point  makeTimePoint (int year, int mon, int day, int hour, int min, int sec)
{
    struct std::tm t;
    t.tm_sec = sec;
    t.tm_min = min;
    t.tm_hour = hour;
    t.tm_mday = day;
    t.tm_mon = mon-1;
    t.tm_year = year-1900;
    t.tm_isdst = -1;
    std::time_t tt = std::mktime(&t);
    if (tt == -1) {
        throw "no valid system time";
    }
    return std::chrono::system_clock::from_time_t(tt);
}

#endif
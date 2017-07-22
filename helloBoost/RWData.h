#pragma once
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>


class RWData
{
private:
    int m_x;
    boost::shared_mutex rw_mu;

public:
    RWData() :m_x(0) {}

    void write()
    {
        boost::unique_lock<boost::shared_mutex> ul(rw_mu);
        ++m_x;
    }

    void read(int& x)
    {
        boost::shared_lock<boost::shared_mutex> sl(rw_mu);
        x = m_x;
    }
};

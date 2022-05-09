#include "hmstime.h"

HMSTime::HMSTime():H(0), M(0), S(0),t(0){}

HMSTime::HMSTime(int _H, int _M, int _S):H(_H), M(_M), S(_S),t(_H*3600+_M*60+_S){}

HMSTime::HMSTime(int _t):t(_t)
{
    H = _t / 3600;
    _t %= 3600;
    M = _t / 60;
    _t %= 60;
    S = _t;
}

HMSTime::HMSTime(const HMSTime& hms):H(hms.H), M(hms.M), S(hms.S), t(hms.t){}

HMSTime::operator int() const{
    return t;
}

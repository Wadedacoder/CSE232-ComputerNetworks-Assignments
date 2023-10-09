#include "wrapping_integers.hh"

#include <iostream>

using namespace std;


//! Transform an "absolute" 64-bit sequence number (zero-indexed) into a WrappingInt32
//! \param n The input absolute 64-bit sequence number
//! \param isn The initial sequence number
WrappingInt32 wrap(uint64_t n, WrappingInt32 isn) { return isn + uint32_t(n); }

//! Transform a WrappingInt32 into an "absolute" 64-bit sequence number (zero-indexed)
//! \param n The relative sequence number
//! \param isn The initial sequence number
//! \param checkpoint A recent absolute 64-bit sequence number
//! \returns the 64-bit sequence number that wraps to `n` and is closest to `checkpoint`
//!
//! \note Each of the two streams of the TCP connection has its own ISN. One stream
//! runs from the local TCPSender to the remote TCPReceiver and has one ISN,
//! and the other stream runs from the remote TCPSender to the local TCPReceiver and
//! has a different ISN.
uint64_t unwrap(WrappingInt32 n, WrappingInt32 isn, uint64_t checkpoint) {

    uint64_t one32 = 1l << 32; 
    uint32_t difference = (n.raw_value() - isn.raw_value()); // Get the modulo difference
    if(difference >= checkpoint) return difference;
    uint64_t ans = (checkpoint - difference) + (one32 >> 1); // Add half of 2^32 to checkpoint - difference; Round to the nearest multiple of 2^32
    ans = ans - (ans % one32); // Round down to the nearest multiple of 2^32
    ans += difference;
    return ans; 
    // return loop_times;
    }


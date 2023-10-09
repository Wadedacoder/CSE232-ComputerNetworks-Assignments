#include "tcp_receiver.hh"

#include <algorithm>


using namespace std;

void TCPReceiver::segment_received(const TCPSegment &seg) {
    const TCPHeader head = seg.header();
    // ...
    if(!_synReceived && !head.syn) return;
    if(!_synReceived && head.syn) {
        _synReceived = true;
        _isn = head.seqno;
    }

    // --- Hint ------
        // convert the seqno into absolute seqno
    uint64_t checkpoint = _reassembler.ack_index();
    uint64_t abs_seqno = unwrap(head.seqno, _isn, checkpoint);
    uint64_t stream_idx = abs_seqno - _synReceived;
    // --- Hint ------  
    _reassembler.push_substring(seg.payload().copy(), stream_idx, head.fin);

    // ... 
}

optional<WrappingInt32> TCPReceiver::ackno() const {
    if(!_synReceived) return {};

    return wrap(_reassembler.ack_index() + _synReceived + stream_out().input_ended(), _isn); // +1 for SYN and +1 for EOF
}

size_t TCPReceiver::window_size() const { return stream_out().remaining_capacity(); }

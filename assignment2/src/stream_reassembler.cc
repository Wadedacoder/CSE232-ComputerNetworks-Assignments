#include "stream_reassembler.hh"

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity)
    :_output(capacity)
{
    _capacity = capacity;
    _unassembled_bytes = 0;
    _ack_index = 0;
}


//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, size_t index, const bool eof) {
    if(_output.input_ended()) return; 
    if(eof) _output.end_input();
    if(index > _output.bytes_written() + _capacity) return;

    _index.push(index);
    _buffer.insert(pair<size_t, string>(index, data));

    _unassembled_bytes += data.size();
    while(_index.top() == _ack_index){
        string tmp = _buffer[_index.top()];
        _output.write(tmp);
        int size = tmp.size();
        _ack_index += size; 
        _index.pop();
        _unassembled_bytes -= size;
    }
}

size_t StreamReassembler::unassembled_bytes() const { return _unassembled_bytes; }

bool StreamReassembler::empty() const { return unassembled_bytes() == 0; }

size_t StreamReassembler::ack_index() const { return _ack_index; }
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
    _indexofeof = MAX_SIZE;
}


//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, size_t index, const bool eof) {
    if(_output.input_ended()) return; 
    if(index >= _indexofeof || index > _ack_index + _capacity) return;
    size_t end = min(index + data.size(),( _ack_index + _capacity));
    size_t start = max(index, _ack_index);
    for(size_t i = start; i < end; i++)
    {
        if(_buffer[i] == 0)
        {
            // cout << "Writing " << (int) data[i-index] << " to reasems\n";
            _buffer[i] = data[i-index];
            _unassembled_bytes++;
        }
    }
    if(eof){
        _indexofeof = index + data.size();
    }
    while(_buffer.find(_ack_index) != _buffer.end())
    {
        // cout << "Writing " << _buffer[_ack_index] << " with ack " << _ack_index  << " to output\n";
        string tmp;
        tmp += _buffer[_ack_index];
        int written = _output.write(tmp);
        if(written == 0) break;
        // _buffer[_ack_index] = 0;
        _buffer.erase(_ack_index);
        _unassembled_bytes--;
        _ack_index++;
        if(_ack_index >= _indexofeof){
            _output.end_input();
            return;
        }
    }
    if(_ack_index >= _indexofeof){
        _output.end_input();
    }
    return;
        // break;
    }

size_t StreamReassembler::unassembled_bytes() const { return _unassembled_bytes; }

bool StreamReassembler::empty() const { return unassembled_bytes() == 0; }

size_t StreamReassembler::ack_index() const { return _ack_index; }
#include "byte_stream.hh"

#include <algorithm>
#include <iostream>

// You will need to add private members to the class declaration in `byte_stream.hh`

/* Replace all the dummy definitions inside the methods in this file. */


using namespace std;

ByteStream::ByteStream(const size_t capa)
{
    _capacity = capa;
    _bytes_written = 0;
    _bytes_read = 0;
    _input_ended = false;
    _error = false;
    
}

size_t ByteStream::write(const string &data) {
  if(_input_ended)
  {
    return 0;
  }
  int data_transfered = 0;
  for(int i = 0; i < data.size(); i++)
  {
    if(_buffer.size() < _capacity)
    {
      //  cout << "Writing " << data[i] << " to buffer\n";
      _buffer.push_back(data[i]);
      data_transfered++;
    }
  }
  _bytes_written += data_transfered;
  return data_transfered;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
  string ans;
  if(_buffer.size() < len)
  {
    for(int i = 0; i < _buffer.size(); i++)
    {
      ans += _buffer[i];
    }
  }
  else
  {
    for(int i = 0; i < len; i++)
    {
      ans += _buffer[i];
    }
  }
  return ans;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
  if(_buffer.size() > len)
  {
    _bytes_read += len;
    _buffer.erase(_buffer.begin(), _buffer.begin() + len);
  }
  else
  {
    _bytes_read += _buffer.size();
    _buffer.clear();
  }
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
  if(eof())
  {
    return "";
  }
  string ans;
  int limit = min(len, _buffer.size());
  for(int i = 0; i < limit; i++)
  {
    ans += _buffer[i];
  }
  if(_buffer.size() > len)
  {
    _buffer.erase(_buffer.begin(), _buffer.begin() + len);
  }
  else
  {
    _buffer.clear();
  }
  _bytes_read += ans.size();
  return ans;
}

void ByteStream::end_input() { _input_ended = true; }

bool ByteStream::input_ended() const { return _input_ended;}

size_t ByteStream::buffer_size() const {return _buffer.size(); }

bool ByteStream::buffer_empty() const {return _buffer.empty(); }

bool ByteStream::eof() const { return _buffer.empty() && _input_ended; }

size_t ByteStream::bytes_written() const { return _bytes_written; }

size_t ByteStream::bytes_read() const { return _bytes_read;  }

size_t ByteStream::remaining_capacity() const { return _capacity - _buffer.size(); }

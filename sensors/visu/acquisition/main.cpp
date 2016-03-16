#include <iostream>
#include <boost/asio.hpp>

#define DELIM 0xff

float *readFloat(boost::asio::serial_port &serial);

int main(int argc, const char** argv) {

  boost::asio::io_service io;
  boost::asio::serial_port serial(io,"/dev/ttyACM0");
  serial.set_option(boost::asio::serial_port_base::baud_rate(9600));

  char *delimitor = new char, *data = new char[12];
  float *roll , *pitch, *heading;

  while(true) {
    
    do {
      
      boost::asio::read(serial, boost::asio::buffer(delimitor, 1));
      
    } while(*delimitor != DELIM);
    
    boost::asio::read(serial, boost::asio::buffer(data, 12));
    
    roll = reinterpret_cast<float*>(data);
    pitch = reinterpret_cast<float*>(data+4);
    heading = reinterpret_cast<float *>(data+8);
    
    std::cout << "roll : " << *roll
	      << "pitch : " << *pitch
	      << "heading : " << *heading << std::endl;

  }

  serial.close();
  delete delimitor;
  delete [] data;
  
  return 0;

}

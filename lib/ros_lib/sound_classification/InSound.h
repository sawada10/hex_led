#ifndef _ROS_sound_classification_InSound_h
#define _ROS_sound_classification_InSound_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace sound_classification
{

  class InSound : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef bool _in_sound_type;
      _in_sound_type in_sound;

    InSound():
      header(),
      in_sound(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_in_sound;
      u_in_sound.real = this->in_sound;
      *(outbuffer + offset + 0) = (u_in_sound.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->in_sound);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_in_sound;
      u_in_sound.base = 0;
      u_in_sound.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->in_sound = u_in_sound.real;
      offset += sizeof(this->in_sound);
     return offset;
    }

    virtual const char * getType() override { return "sound_classification/InSound"; };
    virtual const char * getMD5() override { return "f32d6de8c2557133abb7e07463b7c5d6"; };

  };

}
#endif

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "../support/globals.hpp"

class Instructions
{
  public:
    void build();

    void init_adc_free_running();
    
    void free_running();
};

#endif

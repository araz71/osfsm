# osfsm
OS by FSM

Sometimes using RTOS in small microcontrollers is impossible and also using many interrupts to manage your processes can make many problems and limitations.
So it is better to use FSMs.
osfsm is based on FSM which helps you to implement your requirements as easy as possible.
jumping, delays, waits and everything you need to use in fsm is prepared in this source.
it helps you to reduce youre codding and ofcourse helps you to use less FLASH/RAM than you implement all fsm by yourelsef.

void mytask(sfsm* fsm) {
  if (fsm->steop == 0) {
    printf("Hello world\r\n");
    fsm_delay(fsm, 1000);  //wait 10ms
  }
}

int main(int argc, char *argv) {
  fsm_init();
  make_fsm(mytask);
  
  while(1) {
    fsm_manager();
  }
}
  

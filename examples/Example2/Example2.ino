#include <Arduino.h>
#include <Streaming.h>
#include <Functor.h>

const long BAUDRATE = 115200;

//Button is a component that provides a functor-based
//callback mechanism, so you can wire it up to whatever you wish

class Button
{
public:
  //ctor takes a functor and stores it away in a member

  Button(const Functor0 & uponClickDoThis) :
    notify(uponClickDoThis)
  {}
  void click()
  {
    //invoke the functor, thus calling back client
    notify();
  }
private:
  //note this is a data member with a verb for a name - matches its
  //function-like usage
  Functor0 notify;
};

class CDPlayer
{
public:
  void play()
  {
    Serial << "Playing" << endl;
  }
  void stop()
  {
    Serial << "Stopped" << endl;
  }
};

void wow()
{
  Serial  << "Wow!" << endl;
}

void setup()
{
  Serial.begin(BAUDRATE);
  delay(1000);

  // makeFunctor from object and ptr-to-member-function
  CDPlayer myCD;
  Button playButton(makeFunctor((Functor0 *)0,myCD,&CDPlayer::play));
  Button stopButton(makeFunctor((Functor0 *)0,myCD,&CDPlayer::stop));
  playButton.click(); //calls myCD.play()
  stopButton.click();  //calls myCD.stop()

  // makeFunctor from pointer-to-function
  Button wowButton(makeFunctor((Functor0 *)0,&wow));
  wowButton.click(); //calls wow()
}

void loop()
{
}

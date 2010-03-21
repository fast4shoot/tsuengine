#include "CInputMgr.h"
#include "macros.h"
#include "const.h"
#include "globals.h"
#include "exceptions.h"
#include "datatypes.h"
#include "CBaseEngine.h"

CInputMgr::CInputMgr(){
  DIObject=NULL;
  DIKeyboardDevice=NULL;
  DIMouseDevice=NULL;
  cursor.set(SCREENWIDTH/2.,SCREENHEIGHT/2.);
  fSensitivity = 1.5f;
  bInverted = false;
  iCurrBuffer=0;
}

CInputMgr::~CInputMgr(){
  if(DIKeyboardDevice != NULL){
    DIKeyboardDevice->Unacquire(); //unacquire device (NEW)
    DIKeyboardDevice->Release();   //release keyboard stuff (NEW)
    DIKeyboardDevice = NULL;       //pointer to NULL (NEW)
  }

  if(DIMouseDevice != NULL){
    DIMouseDevice->Unacquire();
    DIMouseDevice->Release();
    DIMouseDevice = NULL;
  }

  if(DIObject!=NULL){
    DIObject->Release();
    DIObject=NULL;
  }
}

void CInputMgr::init(){

  HANDLEMSFAILURE(DirectInput8Create(appInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&DIObject, NULL))

  HANDLEMSFAILURE( DIObject->CreateDevice(GUID_SysKeyboard, &DIKeyboardDevice, NULL) )
  HANDLEMSFAILURE( DIKeyboardDevice->SetDataFormat(&c_dfDIKeyboard) )
  HANDLEMSFAILURE( DIKeyboardDevice->SetCooperativeLevel(appWindow, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE) )
  HANDLEMSFAILURE( DIKeyboardDevice->Acquire() )

  for(int i=0;i<256;i++){
    keyTimeBuffer[iCurrBuffer][i]=0.;
  }

  for(int i=0;i<256;i++){
    keyRealTimeBuffer[iCurrBuffer][i]=0.;
  }

  HANDLEMSFAILURE( DIObject->CreateDevice(GUID_SysMouse, &DIMouseDevice, NULL) )
  HANDLEMSFAILURE( DIMouseDevice->SetDataFormat(&c_dfDIMouse2) )
  HANDLEMSFAILURE( DIMouseDevice->SetCooperativeLevel(appWindow, DISCL_FOREGROUND | DISCL_EXCLUSIVE) );
  DIMouseDevice->Acquire();

  DIDEVCAPS MouseCapabilities;

  MouseCapabilities.dwSize = sizeof(MouseCapabilities);
  DIMouseDevice->GetCapabilities(&MouseCapabilities);

  if(!(MouseCapabilities.dwFlags & DIDC_ATTACHED)){
    throw GeneralFailure("Mouse not connected!");
  }

  iAxes = MouseCapabilities.dwAxes;
  iButtons = MouseCapabilities.dwButtons;


}

void CInputMgr::update(){
  //switch the buffers
  iCurrBuffer=!iCurrBuffer;

  HANDLEMSFAILURE( DIKeyboardDevice->GetDeviceState(sizeof(keyBuffer[iCurrBuffer]), (LPVOID)&keyBuffer[iCurrBuffer]) )

  for(int i=0;i<256;i++){
    if(keyStillDown(i)){
      keyTimeBuffer[iCurrBuffer][i]+=engine->getTimeDelta();
    }else{
      keyTimeBuffer[iCurrBuffer][i]=0.;
    }
  }

  for(int i=0;i<256;i++){
    if(keyStillDown(i)){
      keyRealTimeBuffer[iCurrBuffer][i]+=engine->getRealTimeDelta();
    }else{
      keyRealTimeBuffer[iCurrBuffer][i]=0.;
    }
  }


  HRESULT hr = DIMouseDevice->GetDeviceState(sizeof(MouseState[0]), (LPVOID)&MouseState[iCurrBuffer]);
  //memcpy(buttonBuffer[iCurrBuffer],MouseState.rgbButtons,8);

  if(hr == DIERR_INPUTLOST  || hr == DIERR_NOTACQUIRED){
    DIMouseDevice -> Unacquire();
    DIMouseDevice -> Acquire();
  }


  cursor.x += MouseState[iCurrBuffer].lX * fSensitivity;
  cursor.y += MouseState[iCurrBuffer].lY * fSensitivity;

  cursor.x=CLIPMINMAX(cursor.x,0,SCREENWIDTH-1);
  cursor.y=CLIPMINMAX(cursor.y,0,SCREENHEIGHT-1);

}

bool CInputMgr::keyDown(int key){
  if(keyBuffer[iCurrBuffer][key] & 0x80){
    return true;
  }
  return false;
}

bool CInputMgr::keyStillDown(int key){
  return (keyBuffer[iCurrBuffer][key] & 0x80) && (keyBuffer[!iCurrBuffer][key] & 0x80);
}

bool CInputMgr::keyPressed(int key){
  return (!(keyBuffer[iCurrBuffer][key] & 0x80) && (keyBuffer[!iCurrBuffer][key] & 0x80));
}

bool CInputMgr::keyDepressed(int key){
  return ((keyBuffer[iCurrBuffer][key] & 0x80) && !(keyBuffer[!iCurrBuffer][key] & 0x80));
}

float CInputMgr::keyTimed(int key){
  return keyTimeBuffer[iCurrBuffer][key];
}

float CInputMgr::keyTimedDelta(int key){
  if(keyTimeBuffer[iCurrBuffer][key] > keyTimeBuffer[!iCurrBuffer][key])
    return keyTimeBuffer[iCurrBuffer][key] - keyTimeBuffer[!iCurrBuffer][key];
  else
    return 0.f;
}

float CInputMgr::keyRealTimed(int key){
  return keyRealTimeBuffer[iCurrBuffer][key];
}

float CInputMgr::keyRealTimedDelta(int key){
  if(keyRealTimeBuffer[iCurrBuffer][key] > keyRealTimeBuffer[!iCurrBuffer][key])
    return keyRealTimeBuffer[iCurrBuffer][key] - keyRealTimeBuffer[!iCurrBuffer][key];
  else
    return 0.f;
}

bool CInputMgr::buttonDown(MouseButton button){
  if(MouseState[iCurrBuffer].rgbButtons[button] & 0x80){
    return true;
  }
  return false;
}

bool CInputMgr::buttonPressed(MouseButton button){
   return (MouseState[iCurrBuffer].rgbButtons[button] & 0x80) && !(MouseState[!iCurrBuffer].rgbButtons[button] & 0x80);
}

bool CInputMgr::buttonDepressed(MouseButton button){
   return !(MouseState[iCurrBuffer].rgbButtons[button] & 0x80) && (MouseState[!iCurrBuffer].rgbButtons[button] & 0x80);
}

/*
//tuhle useless funkci napsal michal špaèek
//UPDATE 11.3.: je fakt totálnì k nièemu
 bool CInputMgr::mouseParanoid() {
     if (a->theyreAfterMe() == true) {
         return true;
     }  else    {
         return null;
     }
 }*/



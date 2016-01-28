/*
 * PushButton.h - Arduino PushButton library
 * Copyright (C) 2016 Yuriy Ustushenko
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the version 3 GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once
#ifndef _PUSH_BUTTON_H_
#define _PUSH_BUTTON_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <inttypes.h>
#include "StateMachine.h"

#ifndef DEBOUNCE_DELAY
#define DEBOUNCE_DELAY 50 // ms
#endif

class PushButton;

enum PushButtonState {
    PUSH_BUTTON_RELEASED = 0,
    PUSH_BUTTON_PRESSED  = 1
};

typedef void (*PushButtonCallback)(PushButton *pb, PushButtonState btnState);

class PushButton : public StateMachine {
    public:
        PushButton(uint8_t pin, bool inverted = false, uint32_t debounceDelay = DEBOUNCE_DELAY) :
            StateMachine((PState) &PushButton::RELEASED),
            _pin(pin),
            _inverted(inverted),
            _debounceDelay(debounceDelay),
            _changed(false),
            _btnState(PUSH_BUTTON_RELEASED),
            _onPress(NULL),
            _onRelease(NULL),
            _onChange(NULL) {
        };
        inline bool isReleased() { return _btnState == PUSH_BUTTON_RELEASED; };
        inline bool isPressed() { return _btnState == PUSH_BUTTON_PRESSED; };
        inline bool isStateChanged() { return _changed; };
        inline PushButtonState getBtnState() { return _btnState; };
        inline void onPress(PushButtonCallback cb) { _onPress = cb; };
        inline void onRelease(PushButtonCallback cb) { _onRelease = cb; };
        inline void onChange(PushButtonCallback cb) { _onChange = cb; };
        virtual void reset() {
            _btnState = PUSH_BUTTON_RELEASED;
            _changed  = false;
            setState((PState) &PushButton::RELEASED);
        };
        State RELEASED();
        State UNSTABLE();
        State PRESSED();

    protected:
        uint8_t            _pin;
        bool               _inverted;
        uint32_t           _debounceDelay;
        bool               _changed;
        PushButtonState    _btnState;
        PushButtonState    _realBtnState();
        PushButtonCallback _onPress;
        PushButtonCallback _onRelease;
        PushButtonCallback _onChange;
};

#endif

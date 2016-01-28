/*
 * PushButton.cpp - Arduino PushButton library
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
#include "PushButton.h"

PushButtonState PushButton::_realBtnState() {
    return _inverted
        ? (digitalRead(_pin) == HIGH)
            ? PUSH_BUTTON_PRESSED
            : PUSH_BUTTON_RELEASED
        : (digitalRead(_pin) == LOW)
            ? PUSH_BUTTON_PRESSED
            : PUSH_BUTTON_RELEASED;
}

State PushButton::RELEASED() {
    _changed = false;
    if (_realBtnState() == PUSH_BUTTON_PRESSED)
        setState((PState) &PushButton::UNSTABLE);
}

State PushButton::UNSTABLE() {
    PushButtonState newBtnState = _realBtnState();
    if (newBtnState == _btnState) {
        setPrevState();
        return;
    }

    if (!isTimeout(_debounceDelay)) {
        return;
    }

    setState((PState) (newBtnState == PUSH_BUTTON_RELEASED
        ? &PushButton::RELEASED
        : &PushButton::PRESSED));
    _btnState = newBtnState;
    _changed  = true;

    if (_onPress && _btnState == PUSH_BUTTON_PRESSED)
        _onPress(this, _btnState);
    if (_onRelease && _btnState == PUSH_BUTTON_RELEASED)
        _onRelease(this, _btnState);
    if (_onChange)
        _onChange(this, _btnState);
}

State PushButton::PRESSED() {
    _changed = false;
    if (_realBtnState() == PUSH_BUTTON_RELEASED)
        setState((PState) &PushButton::UNSTABLE);
}

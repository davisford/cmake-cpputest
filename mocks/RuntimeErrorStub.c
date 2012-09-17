/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
/*- ------------------------------------------------------------------ -*/
/*-    Copyright (c) James W. Grenning -- All Rights Reserved          -*/
/*-    For use by owners of Test-Driven Development for Embedded C,    -*/
/*-    and attendees of Renaissance Software Consulting, Co. training  -*/
/*-    classes.                                                        -*/
/*-                                                                    -*/
/*-    Available at http://pragprog.com/titles/jgade/                  -*/
/*-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3                -*/
/*-                                                                    -*/
/*-    Authorized users may use this source code in your own           -*/
/*-    projects, however the source code may not be used to            -*/
/*-    create training material, courses, books, articles, and         -*/
/*-    the like. We make no guarantees that this source code is        -*/
/*-    fit for any purpose.                                            -*/
/*-                                                                    -*/
/*-    www.renaissancesoftware.net james@renaissancesoftware.net       -*/
/*- ------------------------------------------------------------------ -*/

// Stub implementation of RuntimeError.h 

#include "RuntimeErrorStub.h"
static const char * message = "No Error";
static int parameter = -1;
static const char * file = 0;
static int line = -1;

///
/// Allows us to reset internal stats before each test
///
void RuntimeErrorStub_Reset(void)
{
    message = "No Error";
    parameter = -1;
}

///
/// Get the last error message
/// @return the last error message
///
const char * RuntimeErrorStub_GetLastError(void)
{
    return message;
}

///
/// Implementation of RuntimeError.h - pass a message to be stored in an event log
/// @param m the message to log
/// @param p the parameter position in the function
/// @param f pointer to file
/// @param l the line number
void RuntimeError(const char * m, int p, const char * f, int l)
{
    message = m;
    parameter = p;
    file = f;
    line = l;
}

///
/// Allows tests to get the last parameter position
/// @return the last parameter number
///
int RuntimeErrorStub_GetLastParameter(void)
{
    return parameter;
}
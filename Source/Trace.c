//------------------------------------------------------------------------------
//
// File Name:	Trace.c
// Author(s):	Doug Schilling (dschilling)
// Project:		MyGame
// Course:		CS230S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Trace.h"
#include <stdarg.h>

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

// TODO: Declare a private variable for storing a file handle.
static FILE * traceFile;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the Tracing/Logging module.
void TraceInit()
{
	// TODO: Open "trace.log" for writing (text mode).
	fopen_s(&traceFile, "Data\\trace.log", "wt");

	if (traceFile == 0)
	{
		printf("Failed to open trace.log\n");
	}
}

// Output a message to the Tracing/Logging file.
void TraceMessage(const char * formatString, ...)
{
	UNREFERENCED_PARAMETER(formatString);

	// TODO: Write the message to the Tracing/Logging file.



	if (traceFile)
	{
		va_list arg_ptr;
		va_start(arg_ptr, formatString);
		vfprintf_s(traceFile, formatString, arg_ptr);
		fprintf_s(traceFile, "\n");
		va_end(arg_ptr);
	}
	else
		printf("Failed to print to trace.log\n");

}

// Shutdown the Tracing/Logging module.
void TraceShutdown()
{
	// TODO: Close "trace.log" if it has been opened successfully.
	if (traceFile)
		fclose(traceFile);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------


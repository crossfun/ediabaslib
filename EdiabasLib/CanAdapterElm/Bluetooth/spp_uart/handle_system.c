/****************************************************************************
Copyright (C) Cambridge Silicon Radio Limited 2006-2009
Part of BlueLab 4.1-Release

DESCRIPTION
	Implementation for handling system messages and functionality
	
FILE
	handle_system.c
	
*/

/****************************************************************************
    Header files
*/

#include <print.h>
#include <vm.h>
#include <stream.h>

#include "spp_dev_private.h"
#include "handle_system.h"
#include "spp_uart_parse.h"

/* Message Handlers */

void handleMoreData(sppTaskData* app, Source pSrc)
{
    uint16 lLen = SourceSize(pSrc);

	PRINT(("MESSAGE_MORE_DATA\n"));

    if (app->spp_state == sppDevConnected)
    {
		SourceDrop(pSrc, lLen);
        return;
    }

	if ((pSrc == StreamUartSource()) && (lLen > 0))
	{ /* Uart */				
	    /* Only bother parsing if there is something to parse */
	    while (lLen > 0)
	    {
			/* Keep parsing while we have data in the buffer */
	        if (!spp_parseSource(pSrc, (Task) app))
    	        break;

			/* Check we have more data to parse */
    	    lLen = SourceSize(pSrc);
	    }
	}
	else
	{ /* Unknown source */
		PRINT(("    Unknown/Empty Source \n"));
		SourceDrop(pSrc, lLen);
	}
}

void handleMoreSpace(sppTaskData* app, Sink pSink)
{
	PRINT(("MESSAGE_MORE_SPACE\n"));
}


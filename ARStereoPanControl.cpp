/*	Copyright © 2007 Apple Inc. All Rights Reserved.
	
	Disclaimer: IMPORTANT:  This Apple software is supplied to you by 
			Apple Inc. ("Apple") in consideration of your agreement to the
			following terms, and your use, installation, modification or
			redistribution of this Apple software constitutes acceptance of these
			terms.  If you do not agree with these terms, please do not use,
			install, modify or redistribute this Apple software.
			
			In consideration of your agreement to abide by the following terms, and
			subject to these terms, Apple grants you a personal, non-exclusive
			license, under Apple's copyrights in this original Apple software (the
			"Apple Software"), to use, reproduce, modify and redistribute the Apple
			Software, with or without modifications, in source and/or binary forms;
			provided that if you redistribute the Apple Software in its entirety and
			without modifications, you must retain this notice and the following
			text and disclaimers in all such redistributions of the Apple Software. 
			Neither the name, trademarks, service marks or logos of Apple Inc. 
			may be used to endorse or promote products derived from the Apple
			Software without specific prior written permission from Apple.  Except
			as expressly stated in this notice, no other rights or licenses, express
			or implied, are granted by Apple herein, including but not limited to
			any patent rights that may be infringed by your derivative works or by
			other works in which the Apple Software may be incorporated.
			
			The Apple Software is provided by Apple on an "AS IS" basis.  APPLE
			MAKES NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION
			THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS
			FOR A PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND
			OPERATION ALONE OR IN COMBINATION WITH YOUR PRODUCTS.
			
			IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL
			OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
			SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
			INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION,
			MODIFICATION AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED
			AND WHETHER UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE),
			STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN ADVISED OF THE
			POSSIBILITY OF SUCH DAMAGE.
*/
//==================================================================================================
//	Includes
//==================================================================================================

//	Self Include
#include "ARStereoPanControl.h"

//==================================================================================================
//	ARStereoPanControl
//==================================================================================================

OSDefineMetaClassAndStructors(ARStereoPanControl, IOAudioControl)

bool	ARStereoPanControl::init(SInt32 inCurrentValue, SInt32 inFullLeftValue, SInt32 inCenterValue, SInt32 inFullRightValue, UInt32 inLeftChannelNumber, UInt32 inRightChannelNumber, UInt32 inChannelID, const char* inChannelName, UInt32 inControlID, UInt32 inSubType, UInt32 inUsage, OSDictionary* inProperties)
{
	bool theAnswer = false;
	
	//	allocate an OSNumber to hold the current value
	OSNumber* theCurrentValue = OSNumber::withNumber(inCurrentValue, sizeof(SInt32)*8);
	if(theCurrentValue != NULL)
	{
		//	initialize the super class
		theAnswer = IOAudioControl::init(kIOAudioControlTypeStereoPan, theCurrentValue, inChannelID, inChannelName, inControlID, inSubType, inUsage, inProperties);
		
		//	release the number since we're done with it
		theCurrentValue->release();
		
		//	initialize the rest of the control
		if(theAnswer)
		{
			setFullLeftValue(inFullLeftValue);
			setCenterValue(inCenterValue);
			setFullRightValue(inFullRightValue);
			setLeftChannelNumber(inLeftChannelNumber);
			setRightChannelNumber(inRightChannelNumber);
		}
	}
			
	return theAnswer;
}

void	ARStereoPanControl::free()
{
	IOAudioControl::free();
}

ARStereoPanControl*	ARStereoPanControl::create(SInt32 inCurrentValue, SInt32 inFullLeftValue, SInt32 inCenterValue, SInt32 inFullRightValue, UInt32 inLeftChannelNumber, UInt32 inRightChannelNumber, UInt32 inChannelID, const char* inChannelName, UInt32 inControlID, UInt32 inSubType, UInt32 inUsage)
{
	ARStereoPanControl* theAnswer = new ARStereoPanControl;

	if(theAnswer != NULL)
	{
		if(!theAnswer->init(inCurrentValue, inFullLeftValue, inCenterValue, inFullRightValue, inLeftChannelNumber, inRightChannelNumber, inChannelID, inChannelName, inControlID, inSubType, inUsage, NULL))
		{
			theAnswer->release();
			theAnswer = NULL;
		}
	}

	return theAnswer;
}

SInt32	ARStereoPanControl::getFullLeftValue()
{
	return mFullLeftValue;
}

void	ARStereoPanControl::setFullLeftValue(SInt32 inFullLeftValue)
{
	mFullLeftValue = inFullLeftValue;
	setProperty(kIOAudioStereoPanControlFullLeftValueKey, inFullLeftValue, sizeof(SInt32)*8);
	sendChangeNotification(kIOAudioControlRangeChangeNotification);
}

SInt32	ARStereoPanControl::getCenterValue()
{
	return mCenterValue;
}

void	ARStereoPanControl::setCenterValue(SInt32 inCenterValue)
{
	mCenterValue = inCenterValue;
	setProperty(kIOAudioStereoPanControlCenterValueKey, inCenterValue, sizeof(SInt32)*8);
	sendChangeNotification(kIOAudioControlRangeChangeNotification);
}

SInt32	ARStereoPanControl::getFullRightValue()
{
	return mFullRightValue;
}

void	ARStereoPanControl::setFullRightValue(SInt32 inFullRightValue)
{
	mFullRightValue = inFullRightValue;
	setProperty(kIOAudioStereoPanControlFullRightValueKey, inFullRightValue, sizeof(SInt32)*8);
	sendChangeNotification(kIOAudioControlRangeChangeNotification);
}

UInt32	ARStereoPanControl::getLeftChannelNumber()
{
	return mLeftChannelNumber;
}

void	ARStereoPanControl::setLeftChannelNumber(UInt32 inLeftChannelNumber)
{
	mLeftChannelNumber = inLeftChannelNumber;
	setProperty(kIOAudioStereoPanControlLeftChannelKey, inLeftChannelNumber, sizeof(UInt32)*8);
	sendChangeNotification(kIOAudioControlRangeChangeNotification);
}

UInt32	ARStereoPanControl::getRightChannelNumber()
{
	return mRightChannelNumber;
}

void	ARStereoPanControl::setRightChannelNumber(UInt32 inRightChannelNumber)
{
	mRightChannelNumber = inRightChannelNumber;
	setProperty(kIOAudioStereoPanControlRightChannelKey, inRightChannelNumber, sizeof(SInt32)*8);
	sendChangeNotification(kIOAudioControlRangeChangeNotification);
}

IOReturn	ARStereoPanControl::validateValue(OSObject* inNewValue)
{
	IOReturn theAnswer = kIOReturnBadArgument;
	
	//	cast the value to a number
	OSNumber* theNumber = OSDynamicCast(OSNumber, inNewValue);
	if(theNumber != NULL)
	{
		//	convert the number into an integer
		SInt32 theNewValue = (SInt32)theNumber->unsigned32BitValue();
		
		//	make sure the new value is within the proper range
		if((theNewValue >= mFullLeftValue) && (theNewValue <= mFullRightValue))
		{
			theAnswer = kIOReturnSuccess;
		}
		else
		{
			theAnswer = kIOReturnError;
		}
	}

	return theAnswer;
}

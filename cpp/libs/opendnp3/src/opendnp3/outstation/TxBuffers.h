/**
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
 * more contributor license agreements. See the NOTICE file distributed
 * with this work for additional information regarding copyright ownership.
 * Green Energy Corp licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This project was forked on 01/01/2013 by Automatak, LLC and modifications
 * may have been made to this file. Automatak, LLC licenses these modifications
 * to you under the terms of the License.
 */
#ifndef OPENDNP3_TXBUFFERS_H
#define OPENDNP3_TXBUFFERS_H

#include <openpal/container/DynamicBuffer.h>
#include <opendnp3/app/AppControlField.h>
#include <opendnp3/app/APDUResponse.h>

#include "opendnp3/LayerInterfaces.h"

namespace opendnp3
{

class TxBuffers
{
	
	public:	

	TxBuffers(uint32_t maxTxSize) :
		solTxBuffer(maxTxSize),
		unsolTxBuffer(maxTxSize)
	{}		

	template <class Fun>
	APDUResponse FormatSolicited(const Fun& txFun);	

	template <class Fun>
	APDUResponse FormatUnsolicited(const Fun& txFun);

	openpal::ReadBufferView GetLastSolResponse() const { return lastSolResponse;  }

	private:
			
	openpal::ReadBufferView lastSolResponse;
	openpal::ReadBufferView lastUnsolResponse;

	openpal::DynamicBuffer solTxBuffer;
	openpal::DynamicBuffer unsolTxBuffer;
};

template <class Formatter>
APDUResponse TxBuffers::FormatSolicited(const Formatter& format)
{
	APDUResponse response(solTxBuffer.GetWriteBufferView());
	format(response);
	lastSolResponse = response.ToReadOnly();
	return response;
}

template <class Formatter>
APDUResponse TxBuffers::FormatUnsolicited(const Formatter& format)
{
	APDUResponse response(unsolTxBuffer.GetWriteBufferView());
	format(response);
	lastUnsolResponse = response.ToReadOnly();
	return response;
}


}



#endif


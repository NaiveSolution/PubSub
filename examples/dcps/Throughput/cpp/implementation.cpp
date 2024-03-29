
/*
 *                         Vortex OpenSplice
 *
 *   This software and documentation are Copyright 2006 to  ADLINK
 *   Technology Limited, its affiliated companies and licensors. All rights
 *   reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

#include "implementation.hpp"
#include "entities.cpp"

#include "common/example_utilities.h"

#include <iostream>
#include <iomanip>
#include <map>
#include <string>

namespace examples {
#ifdef GENERATING_EXAMPLE_DOXYGEN
GENERATING_EXAMPLE_DOXYGEN /* workaround doxygen bug */
#endif
namespace dcps { namespace Throughput {

/**
 * @addtogroup examplesdcpsThroughputsacpp The Standalone C++ DCPS API Throughput example
 *
 * The Throughput example measures data throughput in bytes per second. The publisher
 * allows you to specify a payload size in bytes as well as allowing you to specify
 * whether to send data in bursts. The publisher will continue to send data forever
 * unless a time out is specified. The subscriber will receive data and output the
 * total amount received and the data rate in bytes per second. It will also indicate
 * if any samples were received out of order. A maximum number of cycles can be
 * specified and once this has been reached the subscriber will terminate and output
 * totals and averages.
 * @ingroup examplesdcpssacpp
 */
/** @{*/
/** @dir */
/** @file */

namespace sacpp  {

#ifndef _WIN32
struct sigaction oldAction;
#endif
/*
 * Function to handle Ctrl-C presses.
 * @param fdwCtrlType Ctrl signal type
 */
#ifdef _WIN32
static bool CtrlHandler(DWORD fdwCtrlType)
{
    terminated->set_trigger_value(true);
    return true; //Don't let other handlers handle this key
}
#else
static void CtrlHandler(int fdwCtrlType)
{
    terminated->set_trigger_value(true);
}
#endif

#define BYTES_PER_SEC_TO_MEGABITS_PER_SEC 125000

/**
 * This function performs the publisher role in this example.
 * @return 0 if a sample is successfully written, 1 otherwise.
 */
int publisher(int argc, char *argv[])
{
    /* Register handler for Ctrl-C */
#ifdef _WIN32
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, true);
#else
    struct sigaction sat;
    sat.sa_handler = CtrlHandler;
    sigemptyset(&sat.sa_mask);
    sat.sa_flags = 0;
    sigaction(SIGINT,&sat,&oldAction);
#endif

    int result = 0;
    DDS::ReturnCode_t status;
    try
    {
        /**
         * Get the program parameters
         * Parameters: publisher [payloadSize] [burstInterval] [burstSize] [timeOut] [partitionName]
         */
        unsigned long payloadSize = 4096;
        unsigned long burstInterval = 0;
        unsigned long timeOut = 0;
        int burstSize = 1;
        std::string partitionName = "Throughput example";
        if(argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
        {
            DDS::String_var exception = DDS::string_dup(
                "Usage (parameters must be supplied in order):\n"
                "./publisher [payloadSize (bytes)] [burstInterval (ms)] [burstSize (samples)] [timeOut (seconds)] [partitionName]\n"
                "Defaults: \n"
                "./publisher 4096 0 1 0 \"Throughput example\"");
            throw exception;
        }
        if(argc > 1)
        {
            payloadSize = atoi(argv[1]); //The size of the payload in bytes
        }
        if(argc > 2)
        {
            burstInterval = atoi(argv[2]); //The time interval between each burst in ms
        }
        if(argc > 3)
        {
            burstSize = atoi(argv[3]); //The number of samples to send each burst
        }
        if(argc > 4)
        {
            timeOut = atoi(argv[4]); //The number of seconds the publisher should run for (0 = infinite)
        }
        if(argc > 5)
        {
            partitionName = argv[5]; //The name of the partition
        }

        std::cout << "payloadSize: " << payloadSize << " | burstInterval: " << burstInterval
            << " | burstSize: " << burstSize << " | timeOut: " << timeOut
            << " | partitionName: " << partitionName << "\n" << std::endl;

        /** Initialise entities */
        PubEntities e(partitionName.c_str());

        /** Fill the sample payload with data */
        ThroughputModule::DataType sample;
        sample.count = 0;
        sample.payload.length(payloadSize);
        for(unsigned long i = 0; i < payloadSize; i++)
        {
            sample.payload[i] = 'a';
        }

        /** Register the sample instance and write samples repeatedly or until time out */
        DDS::InstanceHandle_t handle = e.writer->register_instance(sample);
        std::cout << "Writing samples..." << std::endl;
        int burstCount = 0;
        bool timedOut = false;
        timeval pubStart = exampleGetTime();
        timeval burstStart = exampleGetTime();
        while(!terminated->get_trigger_value() && !timedOut)
        {
            /** Write data until burst size has been reached */
            if(burstCount < burstSize)
            {
                status = e.writer->write(sample, handle);
                if (!terminated->get_trigger_value()) {
                    CHECK_STATUS_MACRO(status);
                }
                sample.count++;
                burstCount++;
            }
            /** Sleep until burst interval has passed */
            else if(burstInterval)
            {
                timeval time = exampleGetTime();
                unsigned long deltaTime =
                    exampleTimevalToMicroseconds(time - burstStart) / US_IN_ONE_MS;
                if(deltaTime < burstInterval)
                {
                    exampleSleepMilliseconds(burstInterval - deltaTime);
                }
                burstStart = exampleGetTime();
                burstCount = 0;
            }
            else
            {
                burstCount = 0;
            }

            if(timeOut)
            {
                if((exampleTimevalToMicroseconds(exampleGetTime() - pubStart) / US_IN_ONE_SEC) > timeOut)
                {
                    timedOut = true;
                }
            }
        }

        if(terminated->get_trigger_value())
        {
            std::cout << "Terminated, " << sample.count << " samples written." << std::endl;
        }
        else
        {
            std::cout << "Timed out, " << sample.count << " samples written." << std::endl;
        }
    }
    catch(const DDS::String_var& e)
    {
        std::cerr << e.in() << std::endl;
        result = 1;
    }

#ifdef _WIN32
    SetConsoleCtrlHandler(0, false);
#else
    sigaction(SIGINT,&oldAction, 0);
#endif
    return result;
}

/**
 * This function calculates the number of samples received
 *
 * @param count1 the map tracking sample count values
 * @param count2 the map tracking sample count start or previous values
 * @param prevCount if set to true, count2's value should be set to count1 after adding to total
 * @return the number of samples received
 */
unsigned long long samplesReceived(std::map<DDS::InstanceHandle_t, unsigned long long>& count1,
    std::map<DDS::InstanceHandle_t, unsigned long long>& count2, bool prevCount = false)
{
    unsigned long long total = 0;
    for(std::map<DDS::InstanceHandle_t, unsigned long long>::iterator it = count1.begin(); it != count1.end(); it++)
    {
        total += it->second - count2[it->first];
        if(prevCount)
        {
            count2[it->first] = it->second;
        }
    }
    return total;
}

/**
 * This function performs the subscriber role in this example.
 * @return 0 if a sample is successfully read, 1 otherwise.
 */
int subscriber(int argc, char *argv[])
{
    /* Register handler for Ctrl-C */
#ifdef _WIN32
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, true);
#else
    struct sigaction sat;
    sat.sa_handler = CtrlHandler;
    sigemptyset(&sat.sa_mask);
    sat.sa_flags = 0;
    sigaction(SIGINT,&sat,&oldAction);
#endif

    int result = 0;
    DDS::ReturnCode_t status;
    try
    {
        /**
         * Get the program parameters
         * Parameters: subscriber [maxCycles] [pollingDelay] [partitionName]
         */
        unsigned long long maxCycles = 0;
        unsigned long pollingDelay = 0;
        std::string partitionName = "Throughput example";
        if(argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
        {
            DDS::String_var exception = DDS::string_dup(
                "Usage (parameters must be supplied in order):\n"
                "./subscriber [maxCycles (0 = infinite)] [pollingDelay (ms, 0 = event based)] [partitionName]\n"
                "Defaults: \n"
                "./subscriber 0 0 \"Throughput example\"");
            throw exception;
        }
        if(argc > 1)
        {
            maxCycles = atoi(argv[1]); //The number of times to output statistics before terminating
        }
        if(argc > 2)
        {
            pollingDelay = atoi(argv[2]); //The number of ms to wait between reads (0 = event based)
        }
        if(argc > 3)
        {
            partitionName = argv[3]; //The name of the partition
        }

        std::cout << "maxCycles: " << maxCycles << " | pollingDelay: " << pollingDelay
            << " | partitionName: " << partitionName << "\n" << std::endl;

        /** Initialise entities */
        SubEntities e(partitionName.c_str());

        std::map<DDS::InstanceHandle_t, unsigned long long> count;
        std::map<DDS::InstanceHandle_t, unsigned long long> startCount;
        std::map<DDS::InstanceHandle_t, unsigned long long> prevCount;
        unsigned long long outOfOrder = 0;
        unsigned long long received = 0;
        unsigned long long prevReceived = 0;
        timeval time = {0, 0};
        timeval startTime = {0, 0};
        timeval prevTime = {0, 0};
        DDS::ConditionSeq conditions;
        ThroughputModule::DataTypeSeq samples;
        DDS::SampleInfoSeq info;
        unsigned long payloadSize = 0;

        std::cout << "Waiting for samples..." << std::endl;

        /** Loop through until the maxCycles has been reached (0 = infinite) */
        unsigned long long cycles = 0;
        while(!terminated->get_trigger_value() && (maxCycles == 0 || cycles < maxCycles))
        {
            /** If polling delay is set */
            if(pollingDelay)
            {
                /** Sleep before polling again */
                exampleSleepMilliseconds(pollingDelay);
            }
            else
            {
                /** Wait for samples */
                status = e.waitSet->wait(conditions, DDS::DURATION_INFINITE);
                CHECK_STATUS_MACRO(status);
            }

            /** Take samples and iterate through them */
            status = e.reader->take(samples, info, DDS::LENGTH_UNLIMITED,
                                        DDS::ANY_SAMPLE_STATE, DDS::ANY_VIEW_STATE, DDS::ANY_INSTANCE_STATE);
            CHECK_STATUS_MACRO(status);
            for (DDS::ULong i = 0; !terminated->get_trigger_value() && i < samples.length(); i++)
            {
                if(info[i].valid_data)
                {
                    DDS::InstanceHandle_t ph = info[i].publication_handle;
                    /** Check that the sample is the next one expected */
                    if(!startCount[ph] && !count[ph])
                    {
                        count[ph] = samples[i].count;
                        startCount[ph] = samples[i].count;
                    }
                    if(samples[i].count != count[ph])
                    {
                        outOfOrder++;
                    }
                    count[ph] = samples[i].count + 1;

                    /** Add the sample payload size to the total received */
                    payloadSize = samples[i].payload.length();
                    received += payloadSize + 8;
                }
            }

            /** Check that at least one second has passed since the last output */
            time = exampleGetTime();
            if(exampleTimevalToMicroseconds(time) >
                exampleTimevalToMicroseconds(prevTime) + US_IN_ONE_SEC)
            {
                /** If not the first iteration */
                if(exampleTimevalToMicroseconds(prevTime))
                {
                    /**
                    * Calculate the samples and bytes received and the time passed since the
                    * last iteration and output
                    */
                    unsigned long long deltaReceived = received - prevReceived;
                    double deltaTime = (double)exampleTimevalToMicroseconds(time - prevTime) / US_IN_ONE_SEC;

                    std::cout << std::fixed << std::setprecision(2)
                                << "Payload size: " << payloadSize << " | "
                                << "Total received: " << samplesReceived(count, startCount) << " samples, "
                                << received << " bytes | "
                                << "Out of order: " << outOfOrder << " samples | "
                                << "Transfer rate: " << (double)samplesReceived(count, prevCount, true) / deltaTime << " samples/s, "
                                << ((double)deltaReceived / BYTES_PER_SEC_TO_MEGABITS_PER_SEC) / deltaTime << " Mbit/s"
                                << std::endl;
                    cycles++;
                }
                else
                {
                    /** Set the start time if it is the first iteration */
                    prevCount = startCount;
                    startTime = time;
                }
                /** Update the previous values for next iteration */
                prevCount = count;
                prevReceived = received;
                prevTime = time;
            }

            status = e.reader->return_loan(samples, info);
            CHECK_STATUS_MACRO(status);
        }

        /** Output totals and averages */
        double deltaTime = (double)exampleTimevalToMicroseconds(time - startTime) / US_IN_ONE_SEC;
        std::cout << std::fixed << std::setprecision(2)
                  << "\nTotal received: " << samplesReceived(count, startCount) << " samples, "
                  << received << " bytes\n"
                  << "Out of order: " << outOfOrder << " samples\n"
                  << "Average transfer rate: " << (double)samplesReceived(count, startCount) / deltaTime << " samples/s, "
                  << ((double)received / BYTES_PER_SEC_TO_MEGABITS_PER_SEC) / deltaTime << " Mbit/s"
                  << std::endl;
    }
    catch(const DDS::String_var& e)
    {
        std::cerr << e.in() << std::endl;
        result = 1;
    }

#ifdef _WIN32
    SetConsoleCtrlHandler(0, false);
#else
    sigaction(SIGINT,&oldAction, 0);
#endif
    return result;
}

}
}
}
}

EXAMPLE_ENTRYPOINT(DCPS_SACPP_Throughput_publisher, examples::dcps::Throughput::sacpp::publisher)
EXAMPLE_ENTRYPOINT(DCPS_SACPP_Throughput_subscriber, examples::dcps::Throughput::sacpp::subscriber)

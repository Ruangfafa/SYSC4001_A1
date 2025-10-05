/**
 *
 * @file interrupts.cpp
 * @author Sasisekhar Govind
 *
 */

#include<interrupts.hpp>

int main(int argc, char** argv) {

    //vectors is a C++ std::vector of strings that contain the address of the ISR
    //delays  is a C++ std::vector of ints that contain the delays of each device
    //the index of these elemens is the device number, starting from 0
    auto [vectors, delays] = parse_args(argc, argv);
    std::ifstream input_file(argv[1]);

    std::string trace;      //!< string to store single line of trace file
    std::string execution;  //!< string to accumulate the execution output

    /******************ADD YOUR VARIABLES HERE*************************/
	int cur_time = 0;
	double thirdOfDelay, testNumber;
	int runIsrDuration, transferDataDuration, checkErrorsDuration;
    /******************************************************************/

    //parse each line of the input trace file
    while(std::getline(input_file, trace)) {
        auto [activity, duration_intr] = parse_trace(trace);

        /******************ADD YOUR SIMULATION CODE HERE*************************/
		if (activity == "CPU") {
			execution += std::to_string(cur_time) + ", " + std::to_string(1000) + ", CPU burst\n";
			cur_time += 1000;
		}
		
		else if (activity == "SYSCALL") {
			auto [intr_boilerplate_execution, intr_boilerplate_cur_time] = intr_boilerplate(cur_time, duration_intr, 1, vectors);
			execution += intr_boilerplate_execution;
			cur_time = intr_boilerplate_cur_time;
			
			thirdOfDelay = delays[duration_intr] / 3.0;

			
			if (static_cast<int>(thirdOfDelay) == thirdOfDelay) {
				runIsrDuration = transferDataDuration = checkErrorsDuration = static_cast<int>(thirdOfDelay);
			} else {
				testNumber = std::floor(thirdOfDelay) + 0.50;
				if (thirdOfDelay <= testNumber) {
					runIsrDuration = static_cast<int>(std::ceil(thirdOfDelay));
					transferDataDuration = checkErrorsDuration = static_cast<int>(std::floor(thirdOfDelay));
				} else {
					runIsrDuration = transferDataDuration = static_cast<int>(std::ceil(thirdOfDelay));
					checkErrorsDuration = static_cast<int>(std::floor(thirdOfDelay));
				}
			}
			
			execution += std::to_string(cur_time) + ", " + std::to_string(runIsrDuration) + ", run ISR\n";
            cur_time += runIsrDuration;
            execution += std::to_string(cur_time) + ", " + std::to_string(transferDataDuration) + ", transfer data\n";
            cur_time += transferDataDuration;
            execution += std::to_string(cur_time) + ", " + std::to_string(checkErrorsDuration) + ", check errors\n";
            cur_time += checkErrorsDuration;
			
			execution += std::to_string(cur_time) + ", " + std::to_string(1) + ", IRET\n";
			cur_time += 1;
		}
		
		else if (activity == "END_IO") {
			execution += std::to_string(cur_time) + ", " + std::to_string(1) + ", check priority of interrupt\n";
			cur_time += 1;
			execution += std::to_string(cur_time) + ", " + std::to_string(1) + ", check if masked\n";
			cur_time += 1;
			auto [intr_boilerplate_execution, intr_boilerplate_cur_time] = intr_boilerplate(cur_time, duration_intr, 1, vectors);
			execution += intr_boilerplate_execution;
			cur_time = intr_boilerplate_cur_time;
			
			thirdOfDelay = delays[duration_intr] / 3.0;
			
			if (static_cast<int>(thirdOfDelay) == thirdOfDelay) {
				runIsrDuration = transferDataDuration = checkErrorsDuration = static_cast<int>(thirdOfDelay);
			} else {
				testNumber = std::floor(thirdOfDelay) + 0.50;
				if (thirdOfDelay <= testNumber) {
					runIsrDuration = static_cast<int>(std::ceil(thirdOfDelay));
					transferDataDuration = checkErrorsDuration = static_cast<int>(std::floor(thirdOfDelay));
				} else {
					runIsrDuration = transferDataDuration = static_cast<int>(std::ceil(thirdOfDelay));
					checkErrorsDuration = static_cast<int>(std::floor(thirdOfDelay));
				}
			}
			
			execution += std::to_string(cur_time) + ", " + std::to_string(runIsrDuration) + ", run ISR\n";
            cur_time += runIsrDuration;
            execution += std::to_string(cur_time) + ", " + std::to_string(transferDataDuration) + ", transfer data\n";
            cur_time += transferDataDuration;
            execution += std::to_string(cur_time) + ", " + std::to_string(checkErrorsDuration) + ", check errors\n";
            cur_time += checkErrorsDuration;
			
			execution += std::to_string(cur_time) + ", " + std::to_string(1) + ", IRET\n";
			cur_time += 1;
		}
		
		else {}
			


        /************************************************************************/

    }

    input_file.close();

    write_output(execution);

    return 0;
}

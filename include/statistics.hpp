//this code has been downloaded from https://github.com/harumo11/libstatistics 
//credits to the author (harumo11)

//This library is a implementation to calculate for statistics.

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

namespace libstatistics {

	class accumulator {
		public:

			accumulator();
			accumulator(std::vector<double> &vector_data);
			~accumulator();

			unsigned long getSize();
			double getSum();
			double getMean();
			double getVariance();
			double getStandardDeviation();
			double getMediam();
			void reset();
			void add(double new_data);
			void add(std::vector<double> new_vector_data);

		private:
			double sum;
			double mean;
			std::vector<double> data;

	};

}
